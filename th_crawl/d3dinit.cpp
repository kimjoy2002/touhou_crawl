//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: d3dinit.cpp
//
// 내용: 프로그램의 중심 파일
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>

#include "d3dUtility.h"
#include "textureUtility.h"
#include "texture.h"
#include "display.h"
#include "mon_infor.h"
#include "map.h"
#include "stdlib.h"
#include "time.h"
#include "FSM.h"
#include "option_manager.h"
#include "soundmanager.h"


//
// 전역
//
IDirect3DDevice9Ex* DeviceEx = NULL; //디바이스포인터
IDirect3DVertexBuffer9* g_pVB = NULL; //버텍스버퍼포인터
D3DXMATRIXA16 g_BaseMatrix; //매트릭스포인터
LPD3DXSPRITE g_pSprite = NULL; //스프라이트포인터 
ID3DXFont* g_pfont = NULL;
IDirectInput8* Input;
IDirectInputDevice8* Keyboard;
IDirectInputDevice8* Mouse;
HANDLE mutx;
extern HWND hwnd;
extern std::atomic<bool> g_saveandexit;


HANDLE endmutx;

extern display_manager DisplayManager;

extern void init_identify();






void LoadEmbeddedFont(const std::wstring& fontPath)
{
	int result = AddFontResourceExW(fontPath.c_str(), FR_PRIVATE, NULL);
	if(result == 0){
		::MessageBox(0, "Font Init Fail.", 0, 0);
	}
}

//
// 초기화 함수
//
bool Setup()
{ 
	bool return_ = true;
	LoadEmbeddedFont(L"./data/font/D2Coding-Ver1.3.2-20180524.ttf");

	return_ = DisplayManager.createResources(DeviceEx);
	map_list.random_number = (unsigned int)time(NULL);
	init_nonlogic_seed((unsigned long)time(NULL));

	endmutx=CreateMutex(NULL, FALSE, NULL);
	mutx=CreateMutex(NULL, FALSE, NULL);
	
	map_list.random_number = (unsigned long)time(NULL);
	init_nonlogic_seed((unsigned long)time(NULL));
	srand((unsigned int)map_list.random_number);
	return return_;
}

//
// 끝내기 함수
//

void Cleanup()
{
	WaitForSingleObject(endmutx, INFINITE);
	timeEndPeriod(1); 
	DisplayManager.releaseResources();//폰트 스프라이트
}
//
// 윈도우 프로시저
//

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		g_saveandexit = true;
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}
extern void init_save_paths();
//
// 윈메인
//
HINSTANCE g_hinstance;
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	g_hinstance = hinstance;
	g_keyQueue = std::make_unique<KeyInputQueue>();
	init_save_paths();
	//random_number = (unsigned int)time(NULL);
	if(!d3d::InitD3D(hinstance,
		option_mg.getWidth(), option_mg.getHeight(), !option_mg.getFullscreen(), D3DDEVTYPE_HAL, &DeviceEx))
	{
		::MessageBox(0, "InitD3D fail", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, "Init Image fail", 0, 0);
	}
	InitSound(hwnd);

	d3d::EnterMsgLoop();

	Cleanup();

	DeviceEx->Release();
	return 0;
}


