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
IDirect3DDevice9* Device = NULL; //디바이스포인터
IDirect3DVertexBuffer9* g_pVB = NULL; //버텍스버퍼포인터
D3DXMATRIXA16 g_BaseMatrix; //매트릭스포인터
LPD3DXSPRITE g_pSprite = NULL; //스프라이트포인터 
ID3DXFont* g_pfont = NULL;
IDirectInput8* Input;
IDirectInputDevice8* Keyboard;
IDirectInputDevice8* Mouse;
HANDLE mutx;
extern HWND hwnd;


HANDLE endmutx;

extern display_manager DisplayManager;

extern void init_identify();






void LoadEmbeddedFont(const std::wstring& fontPath)
{
	int result = AddFontResourceExW(fontPath.c_str(), FR_PRIVATE, NULL);
	if(result == 0){
		::MessageBox(0, "Font Init Fail. 폰트를 초기화하는데 실패하였습니다.", 0, 0);
	}
}

//
// 초기화 함수
//
bool Setup()
{ 
	LoadEmbeddedFont(L"./data/font/D2Coding-Ver1.3.2-20180524.ttf");

	bool return_ = true;
	D3DXFONT_DESC fontDesc;
	ZeroMemory(&fontDesc, sizeof(fontDesc));
	fontDesc.Height = 20;
	fontDesc.Weight = 500;
	fontDesc.Width = 8;
	fontDesc.Quality = CLEARTYPE_QUALITY;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.PitchAndFamily = FF_DONTCARE;
	fontDesc.MipLevels = 1;

	strcpy_s(fontDesc.FaceName, sizeof(fontDesc.FaceName), "D2Coding");
	

	HRESULT hr = D3DXCreateFontIndirect(Device, &fontDesc, &g_pfont);

    if (FAILED(hr) || g_pfont == nullptr)
    {
		::MessageBox(0, "Font loading fail. 폰트를 로딩하는데 실패했습니다.", 0, 0);
    }

	if( FAILED(D3DXCreateSprite(Device, &g_pSprite)))
		return_ =  false;

	Device->CreateVertexBuffer(
		4 * sizeof(Vertex),
		NULL,
		D3DFVF_XYZ|D3DFVF_TEX1,
		D3DPOOL_MANAGED,
		&g_pVB,
		NULL);

	Vertex* pVertices;

	if(SUCCEEDED(g_pVB->Lock(0,0, (void**)&pVertices, 0))){
		pVertices[0] = Vertex( -1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
		pVertices[1] = Vertex( 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
		pVertices[2] = Vertex( -1.0f, -1.0f, 1.0f, 0.0f, 1.0f);
		pVertices[3] = Vertex( 1.0f, -1.0f, 1.0f, 1.0f, 1.0f);
		g_pVB->Unlock();
	}

	D3DXMatrixIdentity(&g_BaseMatrix);
	map_list.random_number = (unsigned int)time(NULL);
	init_nonlogic_seed((unsigned long)time(NULL));

	texture_title.name = imgfile_title[randA(MAX_TITLE-1)];
	if(!texture_title.loadingEX(Device))
		return_ = false;

	for (int i = 0; i < GT_LAST; i++)
	{
		int size_ = strlen(texture_god[i].name);
		if (size_>1 && !texture_god[i].loadingEX(Device))
			return_ = false;
	}

	if(!texture_dungeon01.loadingEX(Device))
		return_ = false;
	if(!texture_monster01.loadingEX(Device))
		return_ = false;
	if(!texture_players01.loadingEX(Device))
		return_ = false;
	if(!texture_item01.loadingEX(Device))
		return_ = false;
	if(!texture_item02.loadingEX(Device))
		return_ = false;
	if (!texture_item03.loadingEX(Device))
		return_ = false;
	if(!texture_laser.loadingEX(Device))
		return_ = false;
	if(!texture_test.loadingEX(Device))
		return_ = false;
	


	if(!texture_dot_floor.loadingEX(Device))
		return_ = false;
	if(!texture_dot_wall.loadingEX(Device))
		return_ = false;
	if(!texture_dot_monster.loadingEX(Device))
		return_ = false;
	if(!texture_dot_player.loadingEX(Device))
		return_ = false;
	if(!texture_dot_up.loadingEX(Device))
		return_ = false;
	if(!texture_dot_down.loadingEX(Device))
		return_ = false;
	if(!texture_dot_item.loadingEX(Device))
		return_ = false;
	if(!texture_dot_door.loadingEX(Device))
		return_ = false;
	if(!texture_dot_temple.loadingEX(Device))
		return_ = false;
	if(!texture_dot_sea.loadingEX(Device))
		return_ = false;
	if(!texture_dot_mapping_floor.loadingEX(Device))
		return_ = false;
	if(!texture_dot_mapping_wall.loadingEX(Device))
		return_ = false;
	
	if(!texture_sight_rect.loadingEX(Device))
		return_ = false;



	endmutx=CreateMutex(NULL, FALSE, NULL);
	mutx=CreateMutex(NULL, FALSE, NULL);
	DisplayManager.Getfontinfor();
	
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
	d3d::Release(g_pVB);  
	d3d::Release(g_pSprite); 
	d3d::Release(g_pfont);
	if(Keyboard != NULL)
	{
		Keyboard -> Unacquire();
		Keyboard -> Release();
		Keyboard = NULL;
	}
	if(Mouse != NULL)
	{
		Mouse -> Unacquire();
		Mouse -> Release();
		Mouse = NULL;
	}


	if(Input != NULL)
	{
		Input -> Release();
		Input = NULL;
	}
}
//
// 윈도우 프로시저
//

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// 윈메인
//

int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{

	//random_number = (unsigned int)time(NULL);
	if(!d3d::InitD3D(hinstance,
		option_mg.getWidth(), option_mg.getHeight(), true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "D3를 초기화하는데 실패하였습니다.", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, "일부 정상적으로 로딩되지못한 이미지파일이 있습니다.", 0, 0);
	}
	InitSound(hwnd);

	d3d::EnterMsgLoop();

	Cleanup();

	Device->Release();
	return 0;
}


