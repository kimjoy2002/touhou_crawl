//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: d3dinit.cpp
//
// 내용: 프로그램의 중심 파일
//
//////////////////////////////////////////////////////////////////////////////////////////////////

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


HANDLE endmutx;



extern display_manager DisplayManager;

extern void init_identify();





//
// 초기화 함수
//

bool Setup()
{    

	D3DXFONT_DESC fontDesc;
	ZeroMemory(&fontDesc, sizeof(fontDesc));
	fontDesc.Height = 14;
	fontDesc.Weight = 300;
	fontDesc.Width = 7;
	fontDesc.Quality = DRAFT_QUALITY;
	fontDesc.Italic = false;
	fontDesc.CharSet = HANGUL_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.PitchAndFamily = FF_DONTCARE;
	fontDesc.MipLevels = 1;

	strcpy(fontDesc.FaceName, "바탕체");
	

	D3DXCreateFontIndirect(Device, &fontDesc, &g_pfont);


	if( FAILED(D3DXCreateSprite(Device, &g_pSprite)))
        return false;

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

	texture_title.name = imgfile_title[randA(MAX_TITLE-1)];
	if(!texture_title.loadingEX(Device))
		return false;



	if(!texture_dungeon01.loadingEX(Device))
		return false;
	if(!texture_monster01.loadingEX(Device))
		return false;
	if(!texture_players01.loadingEX(Device))
		return false;
	if(!texture_item01.loadingEX(Device))
		return false;
	if(!texture_item02.loadingEX(Device))
		return false;
	if(!texture_laser.loadingEX(Device))
		return false;
	if(!texture_test.loadingEX(Device))
		return false;
	


	if(!texture_dot_floor.loadingEX(Device))
		return false;
	if(!texture_dot_wall.loadingEX(Device))
		return false;
	if(!texture_dot_monster.loadingEX(Device))
		return false;
	if(!texture_dot_player.loadingEX(Device))
		return false;
	if(!texture_dot_up.loadingEX(Device))
		return false;
	if(!texture_dot_down.loadingEX(Device))
		return false;
	if(!texture_dot_item.loadingEX(Device))
		return false;
	if(!texture_dot_door.loadingEX(Device))
		return false;
	if(!texture_dot_temple.loadingEX(Device))
		return false;
	if(!texture_dot_sea.loadingEX(Device))
		return false;
	if(!texture_dot_mapping_floor.loadingEX(Device))
		return false;
	if(!texture_dot_mapping_wall.loadingEX(Device))
		return false;
	
	if(!texture_sight_rect.loadingEX(Device))
		return false;



	endmutx=CreateMutex(NULL, FALSE, NULL);
	mutx=CreateMutex(NULL, FALSE, NULL);
	DisplayManager.Getfontinfor();
	
	map_list.random_number = (unsigned long)time(NULL);	
	srand((unsigned int)map_list.random_number);
	//rand_seed(map_list.random_number);
	return true;
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
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop();

	Cleanup();

	Device->Release();

	return 0;
}


