//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: d3dUtility.cpp
//
// 내용: 다이렉트X 유틸 정의 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "environment.h"
#include "replay.h"
#include "option_manager.h"
#include "key.h"
#include "soundmanager.h"
#include <wrl/client.h>
#include <imm.h>
#include <XInput.h>
#pragma comment(lib, "xinput9_1_0.lib")


using namespace std::chrono;

ID3D11Device*           g_pd3dDevice = nullptr;
ID3D11DeviceContext*    g_pImmediateContext = nullptr;
IDXGISwapChain*         g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
extern shared_ptr<DirectX::SpriteBatch> g_pSprite;
extern shared_ptr<DirectX::SpriteFont> g_pfont;

extern const char *version_string;

extern HANDLE endmutx;
extern bool Display(float timeDelta);
extern void init_localization();
extern void charter_selete(bool first);
extern void MainLoop();
extern void Initialize();
std::atomic<bool> g_shutdownRequested = false;
std::atomic<bool> g_saveandexit = false;

DIMOUSESTATE PreviousMouseState;
DIMOUSESTATE CurrentMouseState;
POINT MousePoint;
char string[20];
char string2[10];

int g_ThreadCnt=0;
extern HANDLE mutx;
bool saveexit = false;



HWND hwnd = 0;



void GetWindowSizeFromClientSize(DWORD dwStyle, BOOL bMenuFlag, int cx, int cy, int& wx, int& wy) {
	RECT rc;
	SetRect(&rc, 0, 0, cx, cy);

	if((dwStyle & WS_OVERLAPPED) == WS_OVERLAPPED) dwStyle |= WS_CAPTION;

	AdjustWindowRect(&rc, dwStyle, bMenuFlag);

	if(dwStyle & WS_VSCROLL) {
		rc.right += GetSystemMetrics(SM_CXVSCROLL);
	}
	if(dwStyle & WS_HSCROLL) {
		rc.bottom += GetSystemMetrics(SM_CYHSCROLL);
	}
	wx = rc.right - rc.left;
	wy = rc.bottom - rc.top;
}


void InputInitialize(HINSTANCE hinstance);
void InputUpdate();
unsigned int WINAPI SoundLoop(void *arg);
unsigned int WINAPI GameLoop(void *arg);
unsigned int WINAPI DrawLoop(void *arg);
unsigned int WINAPI GameInnerLoop();
bool d3d::InitD3D11(HINSTANCE hInstance, int width, int height, bool windowed){
    WNDCLASS wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = d3d::WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = "D3D11WindowClass";
    RegisterClass(&wc);

	int winWidth, winHeight;
	GetWindowSizeFromClientSize(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		FALSE, width, height, winWidth, winHeight);
	char temp[64];
	sprintf_s(temp,64,"touhou crawl %s",version_string);
    hwnd = CreateWindow("D3D11WindowClass", temp, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, winWidth, winHeight, nullptr, nullptr, hInstance, nullptr);

    if (!hwnd) return false;

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = windowed;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; 

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
        &sd, &g_pSwapChain, &g_pd3dDevice, nullptr, &g_pImmediateContext);

    if (FAILED(hr)) return false;

    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr)) return false;

    hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr)) return false;

    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);

    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pImmediateContext->RSSetViewports(1, &vp);

    ShowWindow(hwnd, SW_SHOW);
	InputInitialize(hInstance);
    UpdateWindow(hwnd);

    return true;
}

void OnResize(int width, int height)
{
    if (g_pImmediateContext) g_pImmediateContext->OMSetRenderTargets(0, 0, 0);
    if (g_pRenderTargetView) g_pRenderTargetView->Release();


	if (option_mg.getFullscreen()) {
		DXGI_OUTPUT_DESC outputDesc;
		Microsoft::WRL::ComPtr<IDXGIOutput> output;
		g_pSwapChain->GetContainingOutput(&output);
		output->GetDesc(&outputDesc);
		width = outputDesc.DesktopCoordinates.right - outputDesc.DesktopCoordinates.left;
		height = outputDesc.DesktopCoordinates.bottom - outputDesc.DesktopCoordinates.top;
	}

    HRESULT hr = g_pSwapChain->ResizeBuffers(
        1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, 0);
    if (FAILED(hr)) return;

    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    if (FAILED(hr)) return;

    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
    pBackBuffer->Release();

    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);

    // 새로운 해상도에 맞춰 뷰포트 재설정
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pImmediateContext->RSSetViewports(1, &vp);

	if (!option_mg.getFullscreen()) {
		// 창 모드 전환 시 윈도우 스타일 복원
		SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
		
		RECT rc = { 0, 0, option_mg.getWidth(), option_mg.getHeight() };
		AdjustWindowRect(&rc, GetWindowLong(hwnd, GWL_STYLE), FALSE);
		SetWindowPos(hwnd, HWND_NOTOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
		ShowWindow(hwnd, SW_RESTORE);  // 창 다시 활성화
	}
}


void ToggleFullscreen(bool fullscreen)
{
    if (!g_pSwapChain || !g_pd3dDevice) return;

    UINT width = option_mg.getWidth();
    UINT height = option_mg.getHeight();

    // 디스플레이 해상도 전환
    if (fullscreen)
    {
        DXGI_MODE_DESC targetMode = {};
        targetMode.Width = width;
        targetMode.Height = height;
        targetMode.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        targetMode.RefreshRate.Numerator = 60;
        targetMode.RefreshRate.Denominator = 1;

        Microsoft::WRL::ComPtr<IDXGIOutput> output;
        if (SUCCEEDED(g_pSwapChain->GetContainingOutput(&output)))
        {
            DXGI_MODE_DESC closestMode = {};
            if (SUCCEEDED(output->FindClosestMatchingMode(&targetMode, &closestMode, g_pd3dDevice)))
            {
                g_pSwapChain->ResizeTarget(&closestMode);
            }
        }

        g_pSwapChain->SetFullscreenState(TRUE, nullptr);
    }
    else
    {
        DXGI_MODE_DESC windowedMode = {};
        windowedMode.Width = width;
        windowedMode.Height = height;
        windowedMode.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        windowedMode.RefreshRate.Numerator = 60;
        windowedMode.RefreshRate.Denominator = 1;

        g_pSwapChain->ResizeTarget(&windowedMode);
        g_pSwapChain->SetFullscreenState(FALSE, nullptr);
    }

    Sleep(50); // 전환 대기 (안 하면 버퍼 접근 실패할 수 있음)

    if (g_pRenderTargetView) {
        g_pRenderTargetView->Release();
        g_pRenderTargetView = nullptr;
    }

    // 스왑체인 버퍼 리사이즈
    HRESULT hr = g_pSwapChain->ResizeBuffers(
        0, width, height, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
    if (FAILED(hr)) return;


    // 렌더타겟 및 뷰포트 재설정
    if (g_pImmediateContext) g_pImmediateContext->OMSetRenderTargets(0, 0, 0);
    if (g_pRenderTargetView) { g_pRenderTargetView->Release(); g_pRenderTargetView = nullptr; }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    if (FAILED(hr)) return;

    g_pd3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &g_pRenderTargetView);
    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);

    D3D11_VIEWPORT vp = {};
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    g_pImmediateContext->RSSetViewports(1, &vp);


	if (!option_mg.getFullscreen()) {
		// 창 모드 전환 시 윈도우 스타일 복원
		SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
		
		RECT rc = { 0, 0, option_mg.getWidth(), option_mg.getHeight() };
		AdjustWindowRect(&rc, GetWindowLong(hwnd, GWL_STYLE), FALSE);
		SetWindowPos(hwnd, HWND_NOTOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
		ShowWindow(hwnd, SW_RESTORE);  // 창 다시 활성화
	}
}



steady_clock::time_point g_button_press_time[4] = {};
SHORT g_gamepad_xlx[2];
SHORT g_gamepad_xly[2];
boolean g_gamepad_on[2];
steady_clock::time_point g_repeat_start_time[6] = {};
steady_clock::time_point g_last_repeat_emit[6] = {};
WORD prev_buttons;
constexpr WORD BUTTON_MASKS[6] = {
    XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_Y, XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER
};
constexpr wchar_t SHORT_KEYS[4] = {
    GVK_BUTTON_A, GVK_BUTTON_B, GVK_BUTTON_X, GVK_BUTTON_Y, GVK_LEFT_BUMPER, GVK_RIGHT_BUMPER
};
constexpr wchar_t LONG_KEYS[4] = {
    GVK_BUTTON_A_LONG, GVK_BUTTON_B_LONG, GVK_BUTTON_X_LONG, GVK_BUTTON_Y_LONG, GVK_LEFT_BUMPER, GVK_RIGHT_BUMPER
};
// 눌렀다 뗐을 때 500ms 이상이면 롱프레스
constexpr int LONG_PRESS_THRESHOLD_MS = 500;
constexpr int INITIAL_REPEAT_DELAY_MS = 400;  // 첫 입력 이후 대기 시간
constexpr int REPEAT_INTERVAL_MS = 50;        // 반복 주기
constexpr bool ENABLE_REPEAT_FOR[6] = {
    true,  // A
    false, // B
    false, // X
    false, // Y
    true,  // LB
    false  // RB
};


void ProcessGamepadInput()
{
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    if (XInputGetState(0, &state) == ERROR_SUCCESS)
    {
        WORD buttons = state.Gamepad.wButtons;

        // 아날로그 스틱 (예시: 좌측)
        g_gamepad_xlx[0] = state.Gamepad.sThumbLX;
        g_gamepad_xly[0] = state.Gamepad.sThumbLY;
        if (abs(g_gamepad_xlx[0]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || abs(g_gamepad_xly[0]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			g_gamepad_on[0] = true;
		else 
			g_gamepad_on[0] = false;
        g_gamepad_xlx[1] = state.Gamepad.sThumbRX;
        g_gamepad_xly[1] = state.Gamepad.sThumbRY;
        if (abs(g_gamepad_xlx[1]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || abs(g_gamepad_xly[1]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			g_gamepad_on[1] = true;
		else 
			g_gamepad_on[1] = false;

        // ABXY 버튼 처리 (짧게/길게)
        for (int i = 0; i < 6; ++i) {
            bool now_pressed = (buttons & BUTTON_MASKS[i]);
            bool was_pressed = (prev_buttons & BUTTON_MASKS[i]);

			if (now_pressed && was_pressed && ENABLE_REPEAT_FOR[i]) {
				auto now = steady_clock::now();
				auto held_duration = duration_cast<milliseconds>(now - g_button_press_time[i]).count();
				
				// 최초 반복 조건 충족
				if (held_duration >= INITIAL_REPEAT_DELAY_MS) {
					auto since_last_emit = duration_cast<milliseconds>(now - g_last_repeat_emit[i]).count();
					if (since_last_emit >= REPEAT_INTERVAL_MS) {
						g_last_repeat_emit[i] = now;

						if(BUTTON_MASKS[i] == GVK_BUTTON_A) {
							if(g_gamepad_on[0] && (duration < LONG_PRESS_THRESHOLD_MS)) {
								float angle = atan2f((float)g_gamepad_xly[0], (float)g_gamepad_xlx[0]); // 라디안: -π ~ π

								// 8방향 분할
								char vi_key = 0;
								if (angle >= -3.14159f * 7/8 && angle < -3.14159f * 5/8)       vi_key = 'b'; // 좌상
								else if (angle >= -3.14159f * 5/8 && angle < -3.14159f * 3/8)  vi_key = 'j'; // 상
								else if (angle >= -3.14159f * 3/8 && angle < -3.14159f * 1/8)  vi_key = 'n'; // 우상
								else if (angle >= -3.14159f * 1/8 && angle <  3.14159f * 1/8)  vi_key = 'l'; // 우
								else if (angle >=  3.14159f * 1/8 && angle <  3.14159f * 3/8)  vi_key = 'u'; // 우하
								else if (angle >=  3.14159f * 3/8 && angle <  3.14159f * 5/8)  vi_key = 'k'; // 하
								else if (angle >=  3.14159f * 5/8 && angle <  3.14159f * 7/8)  vi_key = 'y'; // 좌하
								else                                                         vi_key = 'h'; // 좌

								if (vi_key) {
									MSG fake_msg = {};
									fake_msg.message = WM_CHAR;
									fake_msg.wParam = vi_key;
									g_keyQueue->push(fake_msg);
								}
							} 
						} 
						else {
							MSG fake_msg = {};
							fake_msg.message = WM_CHAR;
							fake_msg.wParam = SHORT_KEYS[i];
							g_keyQueue->push(fake_msg);
						}
					}
				}
			}


            if (now_pressed && !was_pressed) {
                // 버튼을 처음 누름 → 시간 기록
                g_button_press_time[i] = steady_clock::now();
            }
            else if (!now_pressed && was_pressed) {
                // 버튼을 뗌 → 경과 시간 계산
                auto now = steady_clock::now();
                auto duration = duration_cast<milliseconds>(now - g_button_press_time[i]).count();
                g_button_press_time[i] = steady_clock::time_point(); // 초기화

				if(BUTTON_MASKS[i] == GVK_BUTTON_A && g_gamepad_on[0] && (duration < LONG_PRESS_THRESHOLD_MS)) {
					float angle = atan2f((float)g_gamepad_xly[0], (float)g_gamepad_xlx[0]); // 라디안: -π ~ π

					// 8방향 분할
					char vi_key = 0;
					if (angle >= -3.14159f * 7/8 && angle < -3.14159f * 5/8)       vi_key = 'b'; // 좌상
					else if (angle >= -3.14159f * 5/8 && angle < -3.14159f * 3/8)  vi_key = 'j'; // 상
					else if (angle >= -3.14159f * 3/8 && angle < -3.14159f * 1/8)  vi_key = 'n'; // 우상
					else if (angle >= -3.14159f * 1/8 && angle <  3.14159f * 1/8)  vi_key = 'l'; // 우
					else if (angle >=  3.14159f * 1/8 && angle <  3.14159f * 3/8)  vi_key = 'u'; // 우하
					else if (angle >=  3.14159f * 3/8 && angle <  3.14159f * 5/8)  vi_key = 'k'; // 하
					else if (angle >=  3.14159f * 5/8 && angle <  3.14159f * 7/8)  vi_key = 'y'; // 좌하
					else                                                         vi_key = 'h'; // 좌

					if (vi_key) {
						MSG fake_msg = {};
						fake_msg.message = WM_CHAR;
						fake_msg.wParam = vi_key;
						g_keyQueue->push(fake_msg);
					}
				} else {	
					MSG fake_msg = {};
					fake_msg.message = WM_CHAR;
					fake_msg.wParam = (duration >= LONG_PRESS_THRESHOLD_MS) ? LONG_KEYS[i] : SHORT_KEYS[i];
					g_keyQueue->push(fake_msg);
				}
            }
        }

        if (buttons & XINPUT_GAMEPAD_DPAD_UP && !(prev_buttons & XINPUT_GAMEPAD_DPAD_UP)) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = VK_UP;
			g_keyQueue->push(fake_msg);
		}

        if (buttons & XINPUT_GAMEPAD_DPAD_DOWN && !(prev_buttons & XINPUT_GAMEPAD_DPAD_DOWN)) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = VK_DOWN;
		}

        if (buttons & XINPUT_GAMEPAD_DPAD_LEFT && !(prev_buttons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = VK_LEFT;
		}

        if (buttons & XINPUT_GAMEPAD_DPAD_RIGHT && !(prev_buttons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = VK_RIGHT;
		}
		
        if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = GVK_LT;
		}

        if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = GVK_RT;
		}
			
		prev_buttons = buttons;
    }
}



extern bool g_changefullscreen;
int d3d::EnterMsgLoop()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	timeBeginPeriod(1);
	unsigned int thid;
	unsigned int thid_sound;
	unsigned int thid_draw;

	int g_ignoreWMCharCount = 0;
	g_ThreadCnt = 4;
	_beginthreadex(NULL, 0, GameLoop,NULL,0,&thid);
	_beginthreadex(NULL, 0, SoundLoop, NULL, 0, &thid_sound);
	_beginthreadex(NULL, 0, DrawLoop, NULL, 0, &thid_draw);
	while(msg.message != WM_QUIT && !g_saveandexit)
	{
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			if(msg.message == WM_SYSKEYDOWN && (msg.wParam == VK_RETURN && (msg.lParam & (1 << 29))) ) {
				// Alt + Enter 감지
				option_mg.setFullscreen(!option_mg.getFullscreen());
				g_changefullscreen = true;
			} else {
				if (msg.message == WM_QUIT)
					break;
				if(msg.message == WM_KEYDOWN || (msg.message == WM_KEYUP && (msg.wParam == VK_SHIFT || msg.wParam == VK_CONTROL)))
					g_keyQueue->push(msg);
				if(msg.message == WM_KILLFOCUS)
					g_keyQueue->push(msg);

			    if(msg.message == WM_CHAR && g_ignoreWMCharCount == 0)
			 		g_keyQueue->push(msg);
				else if(msg.message == WM_CHAR && g_ignoreWMCharCount > 0) {
					g_ignoreWMCharCount--;
				}
				if(msg.message == WM_IME_COMPOSITION) {
					if (msg.lParam & GCS_RESULTSTR) {
						HIMC hIMC = ImmGetContext(hwnd);
						if (hIMC) {
							LONG len = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, nullptr, 0);
							if (len > 0) {
								std::wstring resultStr(len / sizeof(wchar_t), 0);
								ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, &resultStr[0], len);
				
								// UTF-8로 변환해서 큐에 넣기
								MSG fake_msg = {};
								fake_msg.message = WM_CHAR; // 우리는 내부적으로 WM_CHAR처럼 처리
								for (wchar_t ch : resultStr) {
									fake_msg.wParam = ch;
									g_keyQueue->push(fake_msg);
								}
								g_ignoreWMCharCount = len;
							}
							ImmReleaseContext(hwnd, hIMC);
						}
					}
				}
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
        }
		ProcessGamepadInput();
		Sleep(1);
		if(g_ThreadCnt < 3)
			break;
    }
	g_shutdownRequested = true;
	msg.message = WM_QUIT;
	g_keyQueue->push(msg);
	int i=0;
	while(g_ThreadCnt > 0 && i++ <= 50)
		Sleep(200);
	if(i>50)
		::MessageBox(0, "Thread Exit Fail", 0, 0);
	return msg.wParam;
}






unsigned int WINAPI DrawLoop(void *arg)
{
	__try
	{
		__try
		{
			while (!g_shutdownRequested)
			{
				if(!Display(0))
				{
					::MessageBox(0, "Display Error", 0, 0);
				}
				InputUpdate();
				Sleep(16);
			}
			return 1;
		}
		__except (1)
		{
		}
	}
	__finally
	{
		g_ThreadCnt--;
	}
    g_pSwapChain->SetFullscreenState(FALSE, NULL);
	g_pd3dDevice->Release();
	g_pImmediateContext->Release();
	g_pSwapChain->Release();
	g_pRenderTargetView->Release();
	return 0;
}

unsigned int WINAPI SoundLoop(void *arg)
{
	__try
	{
		__try
		{
			while (!g_shutdownRequested)
			{
				// if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				// {
				// 	if (msg.message == WM_QUIT)
				// 		break;
				// }

				UpdateBGM();

				Sleep(16);
				/*
				currTime = timeGetTime();
				while (currTime - lastTime < 16)
				{
					currTime = timeGetTime();
				}
				lastTime = currTime;*/
			}
			return 1;
		}
		__except (1)
		{
		}
	}
	__finally
	{
		g_ThreadCnt--;
	}
	return 0;
}


unsigned int ExceptionGameLoop() {
	try {
		return GameInnerLoop();
	}
	catch(std::exception& e) {
		std::string msg = "exception occurs! : ";
		msg += e.what();
		::MessageBoxA(0, msg.c_str(), "Error", MB_OK | MB_ICONERROR);
	}
	return 0;
}


void saveReplay_cpp() {
	if(saveexit && isNormalGame() && !ReplayClass.ReplayMode())
		SaveFile();
	else if(isArena())
	{
		{
			ReplayClass.StopReplay(LocalzationManager::formatString(LOC_SYSTEM_REPLAY_TITLE_ARENA, 
				PlaceHolderHelper(to_string(you.level)),
				PlaceHolderHelper(you.user_name)));
		}
	}
	else if (isSprint())
	{
		ReplayClass.StopReplay(LocalzationManager::locString(LOC_SYSTEM_REPLAY_TITLE_SPRINT));
	}
	else if(!isNormalGame())
	{
		ReplayClass.DeleteRpy();
	}
}


unsigned int WINAPI GameLoop(void *arg)
{
	__try
	{
		__try
		{
			return ExceptionGameLoop();
		}
		__except(1)
		{
		}
	}
	__finally
	{
		saveReplay_cpp();
		g_ThreadCnt-=2;
	}
	return 0;
}


unsigned int WINAPI GameInnerLoop()
{
	bool first = true;
	while(1) {
		charter_selete(first);
		MainLoop();
		first = false;
	}
	return 0;
}

//디바이스
extern IDirectInput8* Input;
extern IDirectInputDevice8* Mouse;
void InputInitialize(HINSTANCE hinstance)
{
    if (FAILED(DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&Input, NULL))) {
        MessageBoxA(nullptr, "DirectInput8Create failed!", "Error", MB_ICONERROR);
        return;
    }
    if (FAILED(Input->CreateDevice(GUID_SysMouse, &Mouse, NULL))) {
        MessageBoxA(nullptr, "CreateDevice (Mouse) failed!", "Error", MB_ICONERROR);
        return;
    }
	Mouse -> SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	Mouse -> SetDataFormat(&c_dfDIMouse);
	Mouse -> Acquire();
}

bool one_turn_click = true;

bool isInScreen() {
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
		POINT clientPos = cursorPos;
	ScreenToClient(hwnd, &clientPos);
	if (clientPos.x < 0 || clientPos.y < 0 || clientPos.x >= clientRect.right || clientPos.y >= clientRect.bottom) {
		return true; // 밖이면 무시
	}
	return false;

}

bool isClicked(MOUSE_BUTTON button) {
	if(!one_turn_click || GetForegroundWindow() != hwnd) {
		return false;
	}


	if(button == LEFT_CLICK) {
		if(isInScreen()) {
			return false;
		}
		if((!(PreviousMouseState.rgbButtons[0] & 0x80) && (CurrentMouseState.rgbButtons[0] & 0x80))) {
			one_turn_click = false;
			return true;
		}
	}
	else if(button == RIGHT_CLICK) {
		if(isInScreen()) {
			return false;
		}
		if((!(PreviousMouseState.rgbButtons[1] & 0x80) && (CurrentMouseState.rgbButtons[1] & 0x80))) {
			one_turn_click = false;
			return true;
		}
	}
	else if(button == MIDDLE_CLICK) {
		if(isInScreen()) {
			return false;
		}
		if((!(PreviousMouseState.rgbButtons[2] & 0x80) && (CurrentMouseState.rgbButtons[2] & 0x80))) {
			one_turn_click = false;
			return true;
		}
	}
	else if(button == MIDDLE_UP) {
		if((CurrentMouseState.lZ > 0)) {
			one_turn_click = false;
			return true;
		}
	}
	else if(button == MIDDLE_DOWN) {
		if((CurrentMouseState.lZ < 0)) {
			one_turn_click = false;
			return true;
		}
	}
	return false;
}




void InputUpdate()
{
    if (!Mouse) return;

	Mouse -> Acquire();
	PreviousMouseState = CurrentMouseState;
	HRESULT hr = Mouse -> GetDeviceState(sizeof(DIMOUSESTATE), &CurrentMouseState);

    if (FAILED(hr)) {
        ZeroMemory(&CurrentMouseState, sizeof(CurrentMouseState));
    }

	GetCursorPos(&MousePoint);
	ScreenToClient(hwnd, &MousePoint);
	one_turn_click = true;
}