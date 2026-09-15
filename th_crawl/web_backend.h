//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: web_backend.h
//
// 내용: webtiles(웹 브라우저 플레이) 백엔드.
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __WEB_BACKEND_H__
#define __WEB_BACKEND_H__

#ifdef WEB_TILES

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN   // windows.h 가 구버전 winsock.h 를 끌어오지 않도록
#endif
#include <windows.h>
#include <string>

struct ID3D11ShaderResourceView;   // 전방선언(무거운 d3d11 헤더 불필요)

namespace web {

// 커맨드라인(--webtiles [--webport N] [--headless])을 파싱하고, 켜졌으면 리스너/입력 스레드를 띄운다.
void init(const char* cmdLine);
bool enabled();

// --headless: D3D 창/디바이스 없이(모니터·GPU 불필요) 로직만 돌며 스트리밍만 한다.
bool headless();

// --userdir <path>: 계정별 세이브/설정 디렉터리. 비어 있으면 기본 경로 사용.
// (init_save_paths 가 이 값을 세이브 베이스로 쓴다 → 멀티플레이 계정 분리)
std::string userDir();

// --username <name>: 계정 이름(캐릭터 이름으로 사용). 비어 있으면 미설정.
std::string userName();

// --lang <code>: 언어 코드(ENG/KOR/JPN). 비어 있으면 미설정(config 기본값 사용).
std::string lang();

// 현재 진행상황(종족/직업/레벨/위치)을 로비에 표시하기 위해 서버로 전송.
void setStatus(const char* utf8Text);

// 이번 렌더 프레임의 마우스 상태(웹에서 주입). x/y=논리좌표, buttons 비트: 0=좌,1=우,2=중.
// 클릭은 큐에서 한 프레임씩 전달되어 isClicked() 전이가 정확히 잡힌다.
void nextMouseFrame(int& x, int& y, int& buttons);

// 아틀라스 식별: 텍스처 로드시 SRV -> 아틀라스 이름(basename) 등록.
void registerAtlas(ID3D11ShaderResourceView* srv, const char* name);

// 프레임 경계 및 기록(모두 렌더 스레드 Display() 안에서 호출).
void beginFrame(int logicalW, int logicalH);
void recSprite(ID3D11ShaderResourceView* srv, RECT src,
               float scaleX, float scaleY, float rotationDeg,
               float centerX, float centerY, unsigned int argb);
void recText(const wchar_t* text, float x, float y, unsigned int argb);
void endFrame();

} // namespace web

#endif // WEB_TILES
#endif // __WEB_BACKEND_H__
