//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: d3dUtility.cpp
//
// 내용: 다이렉트X 유틸 정의 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "environment.h"



//디바이스
extern IDirectInput8* Input;
extern IDirectInputDevice8* Keyboard;
extern IDirectInputDevice8* Mouse;
extern const char *version_string;

extern HANDLE endmutx;
extern bool Display(float timeDelta);
extern void charter_selete();
extern void MainLoop();
extern void Initialize();


char PreviousKeyboardState[256];
char CurrentKeyboardState[256];
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
unsigned int WINAPI GameLoop(void *arg);
unsigned int WINAPI GameInnerLoop();
bool d3d::InitD3D(
	HINSTANCE hInstance,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9** device)
{
	//
	// 윈도우창을 생성한다.
	//


	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)d3d::WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "Direct3D9App";

	if( !RegisterClass(&wc) ) 
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}
		
	char temp[50];

	
	int frameX, frameY;
	//int captionY;
	//frameX = GetSystemMetrics(SM_CXFRAME);
	//frameY = GetSystemMetrics(SM_CYFRAME);
	//captionY = GetSystemMetrics(SM_CYCAPTION);
	GetWindowSizeFromClientSize(WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,false,WindowWidth,WindowHeight,frameX,frameY);

	sprintf_s(temp,50,"touhou crawl %s",version_string);
	hwnd = ::CreateWindow("Direct3D9App", temp, 
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			0, 0, frameX/*WindowWidth + 6*/, frameY/*WindowHeight + 32*/,
		0, 0 , hInstance, 0); 

	if( !hwnd )
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}


	::ShowWindow(hwnd, SW_SHOW);
	InputInitialize(hInstance);
	::UpdateWindow(hwnd);

	//
	// 다이렉트3d 초기화
	//

	HRESULT hr = 0;

	// Step 1: Create the IDirect3D9 object.

	IDirect3D9* d3d9 = 0;
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    if( !d3d9 )
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	// Step 2: Check for hardware vp.

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.
 
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth            = width;
	d3dpp.BackBufferHeight           = height;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow              = hwnd;
	d3dpp.Windowed                   = windowed;
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 4: 

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		deviceType,         // device type
		hwnd,               // window associated with device
		vp,                 // vertex processing
	    &d3dpp,             // present parameters
	    device);            // return created device

	if( FAILED(hr) )
	{
		// 실패시 16비트 깊이로 다시시도?!
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		
		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hwnd,
			vp,
			&d3dpp,
			device);

		if( FAILED(hr) )
		{
			d3d9->Release(); // d3d9를 풀어준다.
			::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	(*device)->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);  //앞뒤 모두 그린다.
	//(*device)->SetRenderState(D3DRS_LIGHTING, FALSE);  //광원효과를 무시한다.(안주면 전부 거매)
    (*device)->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*device)->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    (*device)->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);


	d3d9->Release(); // d3d9를 풀어준다.
	
	return true;
}

int d3d::EnterMsgLoop()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	timeBeginPeriod(1);
	unsigned int thid;

	g_ThreadCnt++;
	_beginthreadex(NULL, 0, GameLoop,NULL,0,&thid);
	while(msg.message != WM_QUIT)
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_KEYDOWN || msg.message == WM_CHAR || (msg.message == WM_KEYUP && (msg.wParam == VK_SHIFT || msg.wParam == VK_CONTROL)))
				PostThreadMessage(thid,msg.message,msg.wParam,msg.lParam);
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		Sleep(16);	
		if(!Display(0))
		{
			::MessageBox(0, "디스플레이 에러", 0, 0);
		}
		if(!g_ThreadCnt)
			break;
		//if(0)
		//{
		//	PostQuitMessage(0);
		//}
    }
	PostThreadMessage(thid,WM_QUIT,msg.wParam,msg.lParam);
	int i=0;
	while(g_ThreadCnt > 0 && i++ <= 50)
		Sleep(200);
	if(i>50)
		::MessageBox(0, "쓰레드 종료 실패", 0, 0);
	return msg.wParam;
}
unsigned int WINAPI GameLoop(void *arg)
{
	__try
	{
		__try
		{
			return GameInnerLoop();
		}
		__except(1)
		{
		}
	}
	__finally
	{
		if(saveexit && !tutorial)
			SaveFile();
		g_ThreadCnt--;
	}
	return 0;
}


unsigned int WINAPI GameInnerLoop()
{
	srand((unsigned int)time(NULL));
	charter_selete();
	MainLoop();
	return 0;
}

void InputInitialize(HINSTANCE hinstance)
{
	DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&Input, NULL);

	Input -> CreateDevice(GUID_SysKeyboard, &Keyboard, NULL);
	Input -> CreateDevice(GUID_SysMouse, &Mouse, NULL);

	Keyboard -> SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	Keyboard -> SetDataFormat(&c_dfDIKeyboard);
	Keyboard -> Acquire();

	Mouse -> SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	Mouse -> SetDataFormat(&c_dfDIMouse);
	Mouse -> Acquire();

	Keyboard -> GetDeviceState(sizeof(char) * 256, &CurrentKeyboardState);
	Mouse -> GetDeviceState(sizeof(DIMOUSESTATE), &CurrentMouseState);
}


void InputUpdate()
{
	Keyboard -> Acquire();
	Mouse -> Acquire();


	CopyMemory(PreviousKeyboardState, CurrentKeyboardState, sizeof(char) * 256);;
	Keyboard -> GetDeviceState(sizeof(char) * 256, &CurrentKeyboardState);

	PreviousMouseState = CurrentMouseState;
	Mouse -> GetDeviceState(sizeof(DIMOUSESTATE), &CurrentMouseState);

	GetCursorPos(&MousePoint);

	ScreenToClient(hwnd, &MousePoint);

	//itoa(MousePoint.x, string, 10);
	//itoa(MousePoint.y, string2, 10);
	//strcat(string, ", ");
	//strcat(string, string2);
	//SetWindowText(WindowHandle, string);


	//if(PreviousKeyboardState[DIK_ESCAPE] == 0 && CurrentKeyboardState[DIK_ESCAPE] == -0x80)
	//{
	//	EscEsc();
	//}


}