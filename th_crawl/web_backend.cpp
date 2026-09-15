//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: web_backend.cpp
//
// 내용: web_backend.h 구현. webtiles 디스플레이 리스트 레코더 + 로컬 TCP 서버 + 입력 주입.
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef WEB_TILES

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>

#include "web_backend.h"

#include <array>
#include <atomic>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "json.hpp"
#include "d3dUtility.h"   // KeyInputQueue, InputedKey, MOUSE_KIND, g_keyQueue, hwnd

#pragma comment(lib, "ws2_32.lib")

using json = nlohmann::json;

extern std::unique_ptr<KeyInputQueue> g_keyQueue;
extern HWND hwnd;

namespace {

std::atomic<bool>   g_enabled{ false };
std::atomic<bool>   g_headless{ false };
int                 g_port = 8091;
std::string         g_userDir;    // --userdir <path> (계정별 세이브 디렉터리)
std::string         g_userName;   // --username <name> (계정=캐릭터 이름)
std::string         g_lang;       // --lang <code> (ENG/KOR/JPN)

std::string parseArg(const std::string& cl, const std::string& flag)
{
    size_t u = cl.find(flag);
    if (u == std::string::npos) return "";
    size_t i = u + flag.size();
    while (i < cl.size() && cl[i] == ' ') i++;
    std::string val;
    if (i < cl.size() && cl[i] == '"') {
        i++;
        while (i < cl.size() && cl[i] != '"') val += cl[i++];
    } else {
        while (i < cl.size() && cl[i] != ' ') val += cl[i++];
    }
    return val;
}

// ── 소켓 ──
SOCKET              g_listen = INVALID_SOCKET;
std::atomic<SOCKET> g_client{ INVALID_SOCKET };
std::mutex          g_writeMx;

// ── 아틀라스 SRV -> 이름 ──
std::mutex                                      g_atlasMx;
std::unordered_map<const void*, std::string>    g_atlas;

// ── 마우스(웹 주입) ──
std::mutex                     g_mouseMx;
int                            g_hoverX = 0, g_hoverY = 0;
std::deque<std::array<int,3>>  g_clickQueue;   // {x, y, btn(0=좌,1=우,2=중)}

// ── 현재 프레임(게임 스레드에서 기록) ──
bool        g_recording = false;
json        g_ops = json::array();
int         g_fw = 0, g_fh = 0;
long long   g_seq = 0;

// ── 전송 파이프라인(게임 스레드 ↔ sender 스레드) ──
// 게임 스레드는 endFrame 에서 ops 를 넘기기만 하고(값싼 move), 무거운 직렬화·네트워크 전송은
// sender 스레드가 담당한다. 이렇게 하면 전송 지연이 게임 로직(공유 mutx)을 붙잡지 않는다.
std::mutex              g_sendMx;
std::condition_variable g_sendCv;
json                    g_pendingOps;
int                     g_pendingW = 0, g_pendingH = 0;
long long               g_pendingSeq = 0;
bool                    g_hasPending = false;   // 최신 프레임만 유지(오래된 미전송 프레임은 덮어씀)
std::atomic<bool>       g_forceSend{ false };   // 새 연결 직후 첫 프레임은 중복이어도 강제 전송

// ---- 유틸 ----
std::string baseName(const char* path)
{
    std::string s = path ? path : "";
    size_t p = s.find_last_of("/\\");
    if (p != std::string::npos) s = s.substr(p + 1);
    // 확장자 제거(있다면)
    size_t d = s.find_last_of('.');
    if (d != std::string::npos) s = s.substr(0, d);
    return s;
}

std::string colorHex(unsigned int argb)
{
    // D3DCOLOR = 0xAARRGGBB  ->  "#RRGGBBAA"
    unsigned a = (argb >> 24) & 0xFF, r = (argb >> 16) & 0xFF,
             g = (argb >> 8) & 0xFF,  b = argb & 0xFF;
    char buf[10];
    sprintf_s(buf, sizeof(buf), "#%02x%02x%02x%02x", r, g, b, a);
    return buf;
}

std::string wideToUtf8(const wchar_t* w)
{
    if (!w || !*w) return "";
    int n = WideCharToMultiByte(CP_UTF8, 0, w, -1, nullptr, 0, nullptr, nullptr);
    if (n <= 1) return "";
    std::string s(n - 1, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w, -1, &s[0], n, nullptr, nullptr);
    return s;
}

void pushChar(unsigned int code)
{
    MSG m{};
    m.hwnd = hwnd;
    m.message = WM_CHAR;
    m.wParam = code;
    if (g_keyQueue) g_keyQueue->push(m);
}

void pushKeyDown(unsigned int vk)
{
    MSG m{};
    m.hwnd = hwnd;
    m.message = WM_KEYDOWN;
    m.wParam = vk;
    if (g_keyQueue) g_keyQueue->push(m);
}

void pushKeyUp(unsigned int vk)
{
    MSG m{};
    m.hwnd = hwnd;
    m.message = WM_KEYUP;
    m.wParam = vk;
    if (g_keyQueue) g_keyQueue->push(m);
}

// 브라우저 입력 JSON 한 줄을 게임 입력으로 변환.
void handleInput(const std::string& line)
{
    json j;
    try { j = json::parse(line); } catch (...) { return; }
    std::string t = j.value("t", "");

    // Windows 키 입력 재현: kd = WM_KEYDOWN(+옵션 WM_CHAR), ku = WM_KEYUP.
    // 순서(KEYDOWN 먼저)가 중요 — 게임 waitkeyinput 이 OS 와 동일하게 처리한다.
    if (t == "kd") {
        int vk = j.value("vk", 0);
        if (vk) pushKeyDown((unsigned int)vk);
        if (j.contains("ch") && j["ch"].is_string()) {
            std::string ch = j["ch"].get<std::string>();
            if (!ch.empty()) {
                wchar_t wbuf[4] = {};
                MultiByteToWideChar(CP_UTF8, 0, ch.c_str(), -1, wbuf, 4);
                pushChar((unsigned int)wbuf[0]);
            }
        }
        return;
    }
    if (t == "ku") {
        int vk = j.value("vk", 0);
        if (vk) pushKeyUp((unsigned int)vk);
        return;
    }

    if (t == "key") {
        std::string ch = j.value("ch", "");
        if (ch.empty()) return;
        // UTF-8 첫 글자 -> 유니코드 코드포인트(게임 명령은 ASCII, 한글 입력은 사용 안함)
        wchar_t wbuf[4] = {};
        MultiByteToWideChar(CP_UTF8, 0, ch.c_str(), -1, wbuf, 4);
        pushChar((unsigned int)wbuf[0]);
    }
    else if (t == "vkey") {
        int vk = j.value("vk", 0);
        // 브라우저 keyCode 37~40 == Windows VK_LEFT~VK_DOWN(0x25~0x28)
        if (vk >= 37 && vk <= 40) pushKeyDown((unsigned int)vk);
        else                      pushChar((unsigned int)vk);   // Esc27 / Enter13 / BS8 등
    }
    else if (t == "mmove") {
        std::lock_guard<std::mutex> lk(g_mouseMx);
        g_hoverX = j.value("x", 0);
        g_hoverY = j.value("y", 0);
    }
    else if (t == "mclick") {
        int x = j.value("x", 0), y = j.value("y", 0), b = j.value("btn", 0);
        std::lock_guard<std::mutex> lk(g_mouseMx);
        g_hoverX = x; g_hoverY = y;
        g_clickQueue.push_back({ x, y, b });
    }
    else if (t == "click") {   // 구버전 호환(위치 없는 일반 클릭)
        std::string btn = j.value("btn", "L");
        MOUSE_KIND kind = (btn == "R") ? MKIND_RCLICK : MKIND_LCLICK;
        if (g_keyQueue) g_keyQueue->push(InputedKey(kind, 0, 0));
    }
    // "resize" 등은 무시(브라우저가 논리 해상도로 스케일).
}

// 클라이언트 연결마다 입력을 읽는다. 프레임 송신은 endFrame()이 담당.
// 한 연결의 입력을 읽는다. accept 를 막지 않도록 별도 스레드에서 돈다.
// 이 소켓의 소유자(=닫는 주체)는 오직 이 함수다. (sender/accept 는 shutdown 만 한다)
void readerLoop(SOCKET c)
{
    std::string buf;
    char tmp[2048];
    while (true) {
        int n = recv(c, tmp, sizeof(tmp), 0);
        if (n <= 0) break;   // 상대가 끊었거나(0) shutdown 으로 깨어남(에러)
        buf.append(tmp, n);
        size_t nl;
        while ((nl = buf.find('\n')) != std::string::npos) {
            handleInput(buf.substr(0, nl));
            buf.erase(0, nl + 1);
        }
    }
    SOCKET expected = c;
    g_client.compare_exchange_strong(expected, INVALID_SOCKET);  // 아직 내가 현재면 해제
    closesocket(c);
}

void acceptLoop()
{
    while (true) {
        SOCKET c = accept(g_listen, nullptr, nullptr);
        if (c == INVALID_SOCKET) break;
        // accept 는 절대 막지 않는다: 새 연결을 현재로 삼고, 이전 연결은 shutdown 으로 깨워
        // 그쪽 readerLoop 가 스스로 종료·close 하게 한다. -> 재접속 시 연결이 쌓여 거부되는 문제 해결.
        SOCKET old = g_client.exchange(c);
        if (old != INVALID_SOCKET) shutdown(old, SD_BOTH);
        g_forceSend.store(true);   // 새 브라우저가 붙으면 현재 화면을 즉시(중복이라도) 보내준다
        g_sendCv.notify_one();
        std::thread(readerLoop, c).detach();
    }
}

void sendLine(const std::string& s)
{
    SOCKET c = g_client.load();
    if (c == INVALID_SOCKET) return;
    std::string out = s;
    out.push_back('\n');
    std::lock_guard<std::mutex> lk(g_writeMx);
    size_t off = 0;
    while (off < out.size()) {
        int n = send(c, out.data() + off, (int)(out.size() - off), 0);
        // 전송 실패면 소켓을 닫지 않고 shutdown 만 한다(닫는 건 readerLoop 담당, 이중 close 방지).
        if (n <= 0) { shutdown(c, SD_BOTH); return; }
        off += n;
    }
}

// sender 스레드: 게임 스레드가 넘긴 최신 프레임을 직렬화해 전송한다. 여기서 블로킹돼도
// 게임 로직(공유 mutx)에는 영향이 없다. 변화 없는 프레임은 건너뛴다(정지 시 트래픽 0).
void senderLoop()
{
    std::string lastSent;
    while (true) {
        json ops; int w, h; long long seq;
        {
            std::unique_lock<std::mutex> lk(g_sendMx);
            g_sendCv.wait(lk, [] { return g_hasPending; });
            ops = std::move(g_pendingOps);
            w = g_pendingW; h = g_pendingH; seq = g_pendingSeq;
            g_hasPending = false;
        }
        json frame = {
            {"t", "frame"}, {"seq", seq}, {"w", w}, {"h", h}, {"ops", std::move(ops)}
        };
        std::string s = frame.dump();
        bool force = g_forceSend.exchange(false);
        if (!force && s == lastSent) continue;   // 변화 없으면 전송 생략(단, 새 연결 첫 프레임은 강제)
        lastSent = s;
        sendLine(s);
    }
}

} // namespace

namespace web {

void init(const char* cmdLine)
{
    std::string cl = cmdLine ? cmdLine : "";
    // --headless 는 --webtiles 를 함축한다(창 없이 스트리밍).
    bool wantHeadless = cl.find("--headless") != std::string::npos;
    if (cl.find("--webtiles") == std::string::npos && !wantHeadless) return;
    g_headless.store(wantHeadless);

    size_t p = cl.find("--webport");
    if (p != std::string::npos) {
        int v = atoi(cl.c_str() + p + 9);
        if (v > 0 && v < 65536) g_port = v;
    }

    g_userDir = parseArg(cl, "--userdir");
    g_userName = parseArg(cl, "--username");
    g_lang = parseArg(cl, "--lang");

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return;

    g_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (g_listen == INVALID_SOCKET) return;
    BOOL yes = TRUE;
    setsockopt(g_listen, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(yes));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)g_port);
    InetPtonA(AF_INET, "127.0.0.1", &addr.sin_addr);
    if (::bind(g_listen, (sockaddr*)&addr, sizeof(addr)) != 0) { closesocket(g_listen); g_listen = INVALID_SOCKET; return; }
    if (::listen(g_listen, SOMAXCONN) != 0) { closesocket(g_listen); g_listen = INVALID_SOCKET; return; }

    g_enabled.store(true);
    std::thread(acceptLoop).detach();
    std::thread(senderLoop).detach();   // 프레임 직렬화·전송 전담(게임 스레드와 분리)
}

bool enabled() { return g_enabled.load(); }
bool headless() { return g_headless.load(); }
std::string userDir() { return g_userDir; }
std::string userName() { return g_userName; }
std::string lang() { return g_lang; }

void setStatus(const char* utf8Text)
{
    if (!g_enabled.load() || !utf8Text) return;
    json j = { {"t", "status"}, {"text", utf8Text} };
    sendLine(j.dump());   // 소켓 쓰기는 thread-safe(g_writeMx)
}

// 클릭을 2단계로 전달: (1) 그 위치에 '호버'(btn=0) 한 프레임 → 게임이 MKIND_MAP_CURSOR로
// search_pos 를 먼저 잡음. (2) 다음 프레임에 '클릭'(btn=1) → MKIND_MAP 이 그 위치로 이동.
static bool         g_pendingDown = false;
static std::array<int, 3> g_pendingClick{ 0, 0, 0 };

void nextMouseFrame(int& x, int& y, int& buttons)
{
    std::lock_guard<std::mutex> lk(g_mouseMx);
    if (g_pendingDown) {
        g_pendingDown = false;
        x = g_pendingClick[0]; y = g_pendingClick[1]; buttons = 1 << g_pendingClick[2];  // 클릭 프레임
        return;
    }
    if (!g_clickQueue.empty()) {
        g_pendingClick = g_clickQueue.front();
        g_clickQueue.pop_front();
        g_pendingDown = true;
        x = g_pendingClick[0]; y = g_pendingClick[1]; buttons = 0;   // 먼저 호버 프레임
        return;
    }
    x = g_hoverX; y = g_hoverY; buttons = 0;   // 평소 호버(커서 위치)
}

void registerAtlas(ID3D11ShaderResourceView* srv, const char* name)
{
    if (!srv || !name) return;
    std::lock_guard<std::mutex> lk(g_atlasMx);
    g_atlas[(const void*)srv] = baseName(name);
}

void beginFrame(int logicalW, int logicalH)
{
    g_recording = g_enabled.load() && (g_client.load() != INVALID_SOCKET);
    if (!g_recording) return;
    g_ops = json::array();
    g_fw = logicalW; g_fh = logicalH;
}

void recSprite(ID3D11ShaderResourceView* srv, RECT src,
               float scaleX, float scaleY, float /*rotationDeg*/,
               float centerX, float centerY, unsigned int argb)
{
    if (!g_recording) return;
    int w = src.right - src.left;
    int h = src.bottom - src.top;
    std::string atlas;
    {
        std::lock_guard<std::mutex> lk(g_atlasMx);
        auto it = g_atlas.find((const void*)srv);
        atlas = (it != g_atlas.end()) ? it->second : std::string("?");
    }
    float dx = centerX - (float)(w / 2) * scaleX;
    float dy = centerY - (float)(h / 2) * scaleY;
    g_ops.push_back({
        {"o", "spr"}, {"a", atlas},
        {"s", { src.left, src.top, w, h }},
        {"d", { (int)(dx + 0.5f), (int)(dy + 0.5f) }},
        {"sc", { scaleX, scaleY }},   // 체력바 등 비대칭 스케일 대응
        {"c", colorHex(argb)}
    });
}

void recText(const wchar_t* text, float x, float y, unsigned int argb)
{
    if (!g_recording) return;
    std::string s = wideToUtf8(text);
    if (s.empty()) return;
    g_ops.push_back({
        {"o", "txt"}, {"x", (int)x}, {"y", (int)y},
        {"str", s}, {"c", colorHex(argb)}, {"al", "left"}
    });
}

void endFrame()
{
    if (!g_recording) return;
    g_recording = false;
    {
        std::lock_guard<std::mutex> lk(g_sendMx);
        g_pendingOps = std::move(g_ops);
        g_pendingW = g_fw; g_pendingH = g_fh; g_pendingSeq = ++g_seq;
        g_hasPending = true;   // 직전 미전송 프레임이 있었다면 덮어씀(최신만 전송)
    }
    g_sendCv.notify_one();
}

} // namespace web

#endif // WEB_TILES
