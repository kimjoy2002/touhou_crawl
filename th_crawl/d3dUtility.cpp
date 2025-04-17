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


ID3D11Device*           g_pd3dDevice = nullptr;
ID3D11DeviceContext*    g_pImmediateContext = nullptr;
IDXGISwapChain*         g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;

extern const char *version_string;

extern HANDLE endmutx;
extern bool Display(float timeDelta);
extern void init_localization();
extern void charter_selete();
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

	char temp[64];
	sprintf_s(temp,64,"touhou crawl %s",version_string);
    hwnd = CreateWindow("D3D11WindowClass", temp, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);

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


int d3d::EnterMsgLoop()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	timeBeginPeriod(1);
	unsigned int thid;
	unsigned int thid_sound;
	unsigned int thid_draw;

	g_ThreadCnt = 4;
	_beginthreadex(NULL, 0, GameLoop,NULL,0,&thid);
	_beginthreadex(NULL, 0, SoundLoop, NULL, 0, &thid_sound);
	_beginthreadex(NULL, 0, DrawLoop, NULL, 0, &thid_draw);
	while(msg.message != WM_QUIT && !g_saveandexit)
	{
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
			if(msg.message == WM_KEYDOWN || msg.message == WM_CHAR || (msg.message == WM_KEYUP && (msg.wParam == VK_SHIFT || msg.wParam == VK_CONTROL)))
          	    g_keyQueue->push(msg);
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
        }
		Sleep(1);
		InputUpdate();
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
	init_localization();
	charter_selete();
	MainLoop();
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
}