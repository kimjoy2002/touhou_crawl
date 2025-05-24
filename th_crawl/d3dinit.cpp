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
#include "steam_api.h"
#include <wrl/client.h>  


//
// 전역
//
IDirectInput8* Input;
IDirectInputDevice8* Mouse;
HANDLE mutx;
extern HWND hwnd;
extern std::atomic<bool> g_saveandexit;


HANDLE endmutx;

extern display_manager DisplayManager;

extern void init_identify();



Microsoft::WRL::ComPtr<ID3D11SamplerState> g_pPointSampler;

void InitSampler(ID3D11Device* device)
{
    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // ✅ 필터 핵심
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

    device->CreateSamplerState(&sampDesc, &g_pPointSampler);
}



void LoadEmbeddedFont(const std::wstring& fontPath)
{
	int result = AddFontResourceExW(fontPath.c_str(), FR_PRIVATE, NULL);
	if(result == 0){
		::MessageBox(0, "Font Init Fail.", 0, 0);
	}
}

extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pImmediateContext;
shared_ptr<DirectX::SpriteBatch> g_pSprite = NULL; //스프라이트포인터 
shared_ptr<DirectX::SpriteFont> g_pfont = NULL;
Microsoft::WRL::ComPtr<ID3D11BlendState> g_pAlphaBlendState;



bool loading_font(string font_name) {
	std::wstring path = ConvertUTF8ToUTF16("./data/font/" + font_name + "_m.spritefont");
	shared_ptr<DirectX::SpriteFont> temp_font = std::make_shared<DirectX::SpriteFont>(
		g_pd3dDevice,
		path.c_str());
	if(temp_font != nullptr) {
		g_pfont = temp_font;
		return true;
	}
	return false;
}

//
// 초기화 함수
//
bool Setup()
{ 
	bool return_ = true;

	InitSampler(g_pd3dDevice);
	// 글꼴 로드 (.spritefont 방식)
	loading_font(LocalzationManager::getCurrentFont());

	// SpriteBatch 생성
	g_pSprite = std::make_shared<DirectX::SpriteBatch>(g_pImmediateContext);


	// bool return_ = true;
	// D3DXFONT_DESC fontDesc;
	// ZeroMemory(&fontDesc, sizeof(fontDesc));
	// fontDesc.Height = 20;
	// fontDesc.Weight = 500;
	// fontDesc.Width = 8;
	// fontDesc.Quality = CLEARTYPE_QUALITY;
	// fontDesc.Italic = false;
	// fontDesc.CharSet = DEFAULT_CHARSET;
	// fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	// fontDesc.PitchAndFamily = FF_DONTCARE;
	// fontDesc.MipLevels = 1;
	// SpriteBatch 생성
	g_pSprite = std::make_shared<DirectX::SpriteBatch>(g_pImmediateContext);


	D3D11_BLEND_DESC desc = {};
    desc.RenderTarget[0].BlendEnable = TRUE;
    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    g_pd3dDevice->CreateBlendState(&desc, &g_pAlphaBlendState);
	
	texture_title.name = imgfile_title[randA(MAX_TITLE-1)];
	if(!texture_title.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;

	for (int i = 0; i < GT_LAST; i++)
	{
		int size_ = strlen(texture_god[i].name);
		if (size_>1 && !texture_god[i].loading(g_pd3dDevice, g_pImmediateContext))
			return_ = false;
	}

	if(!texture_dungeon01.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dungeon02.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_monster01.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_monster02.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_players01.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_item01.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_item02.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if (!texture_item03.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_laser.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	


	if(!texture_dot_floor.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_wall.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_monster.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_player.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_up.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_down.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_item.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_door.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_temple.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_sea.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_mapping_floor.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	if(!texture_dot_mapping_wall.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;
	
	if(!texture_sight_rect.loading(g_pd3dDevice, g_pImmediateContext))
		return_ = false;



	endmutx=CreateMutex(NULL, FALSE, NULL);
	mutx=CreateMutex(NULL, FALSE, NULL);
	DisplayManager.Getfontinfor();
	return return_;
}

//
// 끝내기 함수
//

void Cleanup()
{
	WaitForSingleObject(endmutx, INFINITE);
	timeEndPeriod(1);
	if (g_pSprite) { g_pSprite = nullptr; }
	if (g_pfont)   { g_pfont = nullptr; }
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

extern std::unique_ptr<KeyInputQueue> g_keyQueue;
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
    case WM_KILLFOCUS:
	{
		MSG fake_msg = {};
		fake_msg.message = WM_KILLFOCUS;
		g_keyQueue->push(fake_msg);
		break;
	}
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
void init_localization();



int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	map_list.random_number = (unsigned long)time(NULL);
	init_nonlogic_seed((unsigned long)time(NULL));
	srand((unsigned int)map_list.random_number);

	g_keyQueue = std::make_unique<KeyInputQueue>();
	steam_mg.steamInit();
	init_save_paths();
	init_localization();
	//random_number = (unsigned int)time(NULL);
	if(!d3d::InitD3D11(hinstance,
		option_mg.getWidth(), option_mg.getHeight(), !option_mg.getFullscreen()))
	{
		::MessageBox(0, "InitD3D11 fail", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, "Init Image fail", 0, 0);
	}
	InitSound(hwnd);

	d3d::EnterMsgLoop();

	Cleanup();

	g_pd3dDevice->Release();
	return 0;
}


