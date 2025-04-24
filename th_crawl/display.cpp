//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: display.cpp
//
// 내용: 크롤의 출력
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "textureUtility.h"
#include "environment.h"
#include "texture.h"
#include "display.h"
#include "monster_texture.h"
#include "player.h"
#include "skill.h"
#include "skill_use.h"
#include "smoke.h"
#include "god.h"
#include "floor.h"
#include "option_manager.h"
#include "const.h"
#include "tribe.h"
#include "alchemy.h"
#include "tensi.h"
#include "replay.h"
#include "potion.h"
#include "scroll.h"
#include "ring.h"
#include "book.h"
#include "spellcard.h"
#include "throw.h"
#include "mon_infor.h"
#include "localization.h"
#include <sstream>
#include <iomanip>
#include <wrl/client.h>  

extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pImmediateContext;
extern IDXGISwapChain*         g_pSwapChain;
extern ID3D11RenderTargetView* g_pRenderTargetView;
extern shared_ptr<DirectX::SpriteBatch> g_pSprite; //스프라이트포인터 
extern shared_ptr<DirectX::SpriteFont> g_pfont;
extern HANDLE mutx;
extern HWND hwnd;

extern POINT MousePoint;

display_manager DisplayManager;

DWORD FrameCnt = 0;
float TimeElapsed = 0;
float FPS = 0;

extern bool widesearch; //X커맨드용


int map_effect=0;//잠깐 나오는 맵의 반짝 이벤트





void text_dummy::calculateWitdh() {
	if (!g_pfont) return;

	DirectX::XMVECTOR sizeVec = g_pfont->MeasureString(PreserveTrailingSpaces(text).c_str());
	DirectX::XMFLOAT2 size;
	DirectX::XMStoreFloat2(&size, sizeVec);

	width = size.x;
}

infoBox::infoBox() 
{
	x_size = 240;
	y_size = 80;
	x_comma = 10;
	y_comma = 10;
	draw = false;

}	
stateBox::stateBox(shared_ptr<DirectX::SpriteBatch> pSprite_, shared_ptr<DirectX::SpriteFont> pfont_, RECT start_rc_):
pSprite(pSprite_), pfont(pfont_), start_rc(start_rc_), rc(start_rc_),
width(34), current(0)
{
}
//
// 프레임계산 함수
//
void CalcFPS(float timeDelta)
{
	FrameCnt++;
	TimeElapsed += timeDelta;
	if(TimeElapsed >= 1.0f)
	{
		 FPS = (float)FrameCnt / TimeElapsed;

		 TimeElapsed = 0.0f;
		 FrameCnt = 0;
	}
}


extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pImmediateContext;
extern IDXGISwapChain*         g_pSwapChain;
extern ID3D11RenderTargetView* g_pRenderTargetView;

extern Microsoft::WRL::ComPtr<ID3D11SamplerState> g_pPointSampler;



extern bool g_changefullscreen;
void OnResize(int width, int height);
void ToggleFullscreen(bool fullscreen);

bool Display(float timeDelta)
{
	WaitForSingleObject(mutx, INFINITE);

	
	if(g_changefullscreen) {
		g_changefullscreen = false;
		ToggleFullscreen(option_mg.getFullscreen());
	}

	CalcFPS(timeDelta);
	if (g_pImmediateContext && g_pRenderTargetView)
	{
		// Clear background (검정색)
		const float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, clearColor);

		g_pSprite->Begin(
            DirectX::SpriteSortMode_Deferred,
            nullptr,
            g_pPointSampler.Get(), // ✅ POINT filtering
            nullptr, nullptr);

		DisplayManager.draw(g_pSprite, g_pfont);
		
		g_pSprite->End();

		g_pSwapChain->Present(1, 0);
	}
	
	ReleaseMutex(mutx);
	return true;
}


display_manager::display_manager():tile_type(0),text_log(),text_sub(),state(DT_TEXT),
scale_x(0), scale_y(0),item_view(), item_vt(IVT_INFOR), item_view_message(LOC_SYSTEM_DISPLAY_MANAGER_NORMAL_ITEM), image(NULL),
log_length(1), move(0), max_y(1), sight_type(0), spell_sight(0)
{
	for(int i=0;i<52;i++)
		item_view[i] = 0;
}
void display_manager::Getfontinfor()
{
	if (!g_pfont) return;

	// 예시 텍스트로 평균적인 너비/높이 측정
	std::wstring sample = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	DirectX::XMVECTOR sizeVec = g_pfont->MeasureString(sample.c_str());
	DirectX::XMFLOAT2 size;
	DirectX::XMStoreFloat2(&size, sizeVec);

	// 폰트 높이 = 문자열 높이
	// 폰트 폭 = 평균 글자 폭 = 전체 폭 / 글자 수
	fontDesc.Height = size.y;
	fontDesc.Width = size.x / sample.length();
	fontDesc.Size = fontDesc.Height; // 실제 폰트 크기와 거의 일치

	// 로그 영역 크기 계산
	log_length = (option_mg.getHeight() - 50) / fontDesc.Height;
}


int display_manager::convertClickable(int id) {
	switch(id) {
		case SPECIAL_CLINKABLE_Y:
			return 'Y';
		case SPECIAL_CLINKABLE_N:
			return 'N';
		default:
			return id;
	}
}

textures* display_manager::getSelectTexure(int id) {
	if(id >= 'a' && id <= 'z') {
		return &img_command_alphabet_small[id - 'a'];
	}
	else if(id >= 'A' && id <= 'Z') {
		return &img_command_alphabet_large[id - 'A'];
	}
	else if(id >= '0' && id <= '9') {
		return &img_command_number[id - '0'];
	}


	switch(id) {
		case SPECIAL_CLINKABLE_Y:
			return &img_command_Y;
		case SPECIAL_CLINKABLE_N:
			return &img_command_N;
		case 'Y':
			return &img_command_Y;
		case 'N':
			return &img_command_N;
		case VK_ESCAPE:
			return &img_command_X;
		case '<':
			return &img_command_number[10];
		case '>':
			return &img_command_number[11];
		case '=':
			return &img_command_number[12];
		case '?':
			return &img_command_number[13];
		case '!':
			return &img_command_number[14];
		case '*':
			return &img_command_number[15];
		case '(':
			return &img_command_number[16];
		case ')':
			return &img_command_number[17];
		case '+':
			return &img_command_number[18];
		case '^':
			return &img_command_number[19];
		case '#':
			return &img_command_number[20];
		case '&':
			return &img_command_number[21];
		case '-':
			return &img_command_number[22];
		case '.':
			return &img_command_number[23];
		case ',':
			return &img_command_number[24];
		default:
			return &img_command_number[13];
	}
}

void common_mouse_logic() {
	if(isClicked(LEFT_CLICK)) {
		g_keyQueue->push(InputedKey(MKIND_LCLICK,0,0));
	} else if (isClicked(RIGHT_CLICK)) {
		g_keyQueue->push(InputedKey(MKIND_RCLICK,0,0));
	} 
	// else if(isClickedMIDDLE_CLICK)) { //필요없을지도
	// 	g_keyQueue->push(InputedKey(MKIND_MCLICK,0,0));
	// }
}


void display_manager::draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	switch(state)
	{
		case DT_TEXT:
			text_draw(pSprite,pfont);
			break;
		case DT_SKILL:
			skill_draw(pSprite,pfont);
			break;
		case DT_STATE:
			state_draw(pSprite,pfont);
			break;
		case DT_GAME:
			game_draw(pSprite,pfont);
			break;
		case DT_ITEM:
			item_draw(pSprite,pfont);
			break;
		case DT_LOG:
			log_draw(pSprite,pfont);
			break;
		case DT_SPELL:
			spell_draw(pSprite,pfont);
			break;
		case DT_IDEN:
			iden_draw(pSprite, pfont);
			break;
		case DT_SKILL_USE:
			skill2_draw(pSprite,pfont);
			break;
		case DT_SUB_TEXT:
			sub_text_draw(pSprite,pfont);
			break;
		case DT_PROPERTY:
			property_draw(pSprite,pfont);
			break;
	}
	common_mouse_logic();
}

int DrawTextUTF8(shared_ptr<DirectX::SpriteFont> pFont, shared_ptr<DirectX::SpriteBatch> pSprite, LPCWSTR text, int count, LPRECT pRect, DWORD format, D3DCOLOR color) {
    if (!pFont || !text || !pRect) {
        return 0;
    }

	std::wstring wtext(text);

    // 문자열 길이 제한
    if (count >= 0 && count < (int)wtext.size()) {
        wtext = wtext.substr(0, count);
    }

    // 색상 변환
    DirectX::XMVECTOR colorVec = D3DCOLOR_to_XMVECTOR(color);

    // 문자열 크기 측정
    DirectX::XMVECTOR sizeVec = pFont->MeasureString(wtext.c_str());
    DirectX::XMFLOAT2 size;
    DirectX::XMStoreFloat2(&size, sizeVec);

    // 정렬 계산
    float x = (float)pRect->left;
    float y = (float)pRect->top;

    if (format & DT_CENTER)
        x = (pRect->left + pRect->right - size.x) / 2.0f;
    else if (format & DT_RIGHT)
        x = (float)pRect->right - size.x;

    if (format & DT_VCENTER)
        y = (pRect->top + pRect->bottom - size.y) / 2.0f;
    else if (format & DT_BOTTOM)
        y = (float)pRect->bottom - size.y;

    // Draw
    pFont->DrawString(pSprite.get(), wtext.c_str(), { x, y }, colorVec);

    return (int)wtext.size();  // 반환값은 출력한 글자 수
}


int DrawTextUTF8(shared_ptr<DirectX::SpriteFont> pFont, shared_ptr<DirectX::SpriteBatch> pSprite, const char* text, int count, LPRECT pRect, DWORD format, D3DCOLOR color) {
    if (!pFont || !text || !pRect) {
        return 0;
    }

    // UTF-8 → UTF-16 변환
    std::wstring wtext = ConvertUTF8ToUTF16(text);
    if (wtext.empty()) return 0;
	return DrawTextUTF8(pFont, pSprite, wtext.c_str(), count, pRect, format, color);
}

int DrawTextUTF8(shared_ptr<DirectX::SpriteFont> pFont, shared_ptr<DirectX::SpriteBatch> pSprite, const std::string& text, int count, LPRECT pRect, DWORD format, D3DCOLOR color) {
    return DrawTextUTF8(pFont, pSprite, text.c_str(), count, pRect, format, color);
}

void display_manager::text_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	if(image)
		image->draw(pSprite,255);
	RECT rc={50, 50-move, option_mg.getWidth(), option_mg.getHeight()};
	DrawTextUTF8(pfont, pSprite, text.c_str(), -1, &rc, DT_NOCLIP,D3DCOLOR_XRGB(200,200,200));
	if(isClicked(MIDDLE_UP)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_UP,0,0));
	} else if(isClicked(MIDDLE_DOWN)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_DOWN,0,0));
	}
}

void display_manager::spell_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	RECT rc={50, 50, option_mg.getWidth(), option_mg.getHeight()};
	stringstream ss;

	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(item_view_message), -1, &rc, DT_NOCLIP,CL_normal);
	rc.top += fontDesc.Height*2;

	DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_HOTKEY), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 50;
	ss << "- " << LocalzationManager::locString(LOC_SYSTEM_NAME);
	DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 150;
	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_SCHOOL), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 250;
	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_FAILURE_RATE), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 150;
	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_LEVEL), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += fontDesc.Height;
	rc.left = 50;
	for(int i=0;i<52;i++)
	{
		if(you.MemorizeSpell[i])
		{
			RECT rc2={ rc.left, rc.top,  rc.right, (LONG)(rc.top+fontDesc.Height)};
			spell_list spell_ = (spell_list)you.MemorizeSpell[i];
			int miscast_level_ = SpellMiscastingLevel(SpellLevel(spell_), 100-you.GetSpellSuccess(spell_));
			D3DCOLOR spell_color_ = (miscast_level_==3?CL_danger:
				(miscast_level_==2?CL_small_danger:
				(miscast_level_==1?CL_warning:CL_STAT)));

			char sp_char = (i<26)?('a'+i):('A'+i-26);
			ss.str("");
			ss.clear();
			ss << sp_char;
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, spell_color_);
			rc.left += 50;
			ss.str("");
			ss.clear();
			ss << "- " << SpellString(spell_);
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, spell_color_);
			rc.left += 150;
			DrawTextUTF8(pfont,pSprite,GetSpellSchoolString(spell_).c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, spell_color_);
			rc.left = 500;
			ss.str("");
			ss.clear();
			ss << setw(3) << left << (100 - you.GetSpellSuccess(spell_)) << "%";
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, spell_color_);
			rc.left += 150;
			ss.str("");
			ss.clear();
			ss << SpellLevel(spell_);
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, spell_color_);
			
			rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;			
			if (MousePoint.x > rc2.left && MousePoint.x <= rc2.right &&
				MousePoint.y > rc2.top && MousePoint.y <= rc2.bottom){
				DrawRectOutline(pSprite, rc2, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
				
				if(isClicked(LEFT_CLICK)) {						
					MSG msg;
					msg.message = WM_CHAR;
					msg.wParam = convertClickable(sp_char);
					g_keyQueue->push(InputedKey(msg));
				}
				else if(isClicked(RIGHT_CLICK)) {
					g_keyQueue->push(InputedKey(MKIND_ITEM_DESCRIPTION,sp_char,0));
				}
			}
			
			rc.top += fontDesc.Height;
			rc.left = 50;
		}
	}
}
void display_manager::iden_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	int num = 0;
	RECT rc = { 30, 10 - move, option_mg.getWidth(), option_mg.getHeight() };
	stringstream ss;
	int one_ = 50, two_ = 100;

	DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_IDEN_VIEW).c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += 2* fontDesc.Height;

	bool first_ = false;
	for (int i = IDEN_CHECK_START; i < IDEN_CHECK_END; i++) {
		RECT rc2={ two_, rc.top,  rc.right,  rc.bottom};
		char index = 'a', current;
		D3DCOLOR font_color_ = iden_list.autopickup[i]?CL_normal:CL_bad;
		for (current = num; current >= 26; current -= 26) {
			if (index == 'a')
				index = 'A';
			else
				index = 'a';
		}

		index += current;
		if (i >= IDEN_CHECK_POTION_START && i < IDEN_CHECK_POTION_END) {
			int cur_ = i - IDEN_CHECK_POTION_START;
			if (i == IDEN_CHECK_POTION_START) {
				first_ = true;
			}
			if (iden_list.potion_list[cur_].iden)
			{
				if (first_)
				{
					rc.left = one_;
					rc.top += fontDesc.Height;
					ss.str("");
					ss.clear();
					ss << "<" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_POTION) << ">";
					DrawTextUTF8(pfont,pSprite, ss.str() , -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				rc2=rc;
				img_item_potion[iden_list.potion_list[cur_].color].draw(pSprite, rc.left-24, rc.top+6, 255);
				img_item_potion_kind[min(PT_MAX - 1, max(0, cur_))].draw(pSprite, rc.left-24, rc.top+6, 255);

				ss.str("");
				ss.clear();
				ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << LocalzationManager::locString(potion_iden_string[cur_]);

				DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
				rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
				rc.top += 2*fontDesc.Height;
				num++;
			}
		}
		else if (i >= IDEN_CHECK_SCROLL_START && i < IDEN_CHECK_SCROLL_END) {
			int cur_ = i - IDEN_CHECK_SCROLL_START;
			if (i == IDEN_CHECK_SCROLL_START) {
				first_ = true;
			}
			if (iden_list.scroll_list[cur_].iden == 3)
			{
				if (first_)
				{
					rc.left = one_;
					rc.top += fontDesc.Height;
					ss.str("");
					ss.clear();
					ss << "<" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_SCROLL) << ">";
					DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				rc2=rc;
				img_item_scroll.draw(pSprite, rc.left - 24, rc.top + 6, 255);
				img_item_scroll_kind[min(SCT_MAX - 1, max(0, cur_))].draw(pSprite, rc.left - 24, rc.top + 6, 255);
				
				ss.str("");
				ss.clear();
				ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << LocalzationManager::locString(scroll_iden_string[cur_]);

				DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
				rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
				rc.top += 2*fontDesc.Height;
				num++;
			}
		}
		else if (i >= IDEN_CHECK_RING_START && i < IDEN_CHECK_RING_END) {
			int cur_ = i - IDEN_CHECK_RING_START;
			if (i == IDEN_CHECK_RING_START) {
				first_ = true;
			}
			if (iden_list.ring_list[cur_].iden == 2)
			{
				if (first_)
				{
					rc.left = one_;
					rc.top += fontDesc.Height;
					ss.str("");
					ss.clear();
					ss << "<" << LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_RING) << ">";
					DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				rc2=rc;
				img_item_ring[iden_list.ring_list[cur_].type].draw(pSprite, rc.left - 24, rc.top + 6, 255);
				img_item_ring_kind[min(RGT_MAX - 1, max(0, cur_))].draw(pSprite, rc.left - 24, rc.top + 6, 255);
				
				ss.str("");
				ss.clear();
				ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << LocalzationManager::formatString(ring_iden_string[cur_], PlaceHolderHelper(""));
				DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
				rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
				rc.top += 2*fontDesc.Height;
				num++;
			}
		}
		else if (i >= IDEN_CHECK_AMULET_START && i < IDEN_CHECK_AMULET_END) {
			int cur_ = i - IDEN_CHECK_AMULET_START;
			if (i == IDEN_CHECK_AMULET_START) {
				first_ = true;
			}
			if (iden_list.amulet_list[cur_].iden == 2)
			{
				if (first_)
				{
					rc.left = one_;
					rc.top += fontDesc.Height;
					ss.str("");
					ss.clear();
					ss << "<" << LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET) << ">";
					DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				rc2=rc;
				img_item_amulet.draw(pSprite, rc.left - 24, rc.top + 6, 255);
				img_item_amulet_kind[min(AMT_MAX - 1, max(0, cur_))].draw(pSprite, rc.left - 24, rc.top + 6, 255);
				
				
				ss.str("");
				ss.clear();
				ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << LocalzationManager::locString(amulet_iden_string[cur_]);
				DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
				rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
				rc.top += 2*fontDesc.Height;
				num++;
			}
		}
		else if (i >= IDEN_CHECK_SPC_START && i < IDEN_CHECK_SPC_END) {
			int cur_ = i - IDEN_CHECK_SPC_START;
			if (i == IDEN_CHECK_SPC_START) {
				first_ = true;
			}
			if (iden_list.spellcard_list[cur_].iden == 2)
			{
				if (first_)
				{
					rc.left = one_;
					rc.top += fontDesc.Height;
					ss.str("");
					ss.clear();
					ss << "<" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_SPELLCARD) << ">";
					DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				rc2=rc;
				img_item_spellcard.draw(pSprite, rc.left - 24, rc.top + 6, 255);

				ss.str("");
				ss.clear();
				ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << SpellcardName((spellcard_evoke_type)cur_) << LocalzationManager::locString(LOC_SYSTEM_SPELLCARD);
				DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
				rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
				rc.top += 2*fontDesc.Height;
				num++;
			}
		}
		else if (i >= IDEN_CHECK_BOOK_START && i < IDEN_CHECK_BOOK_END) {
			int cur_ = i - IDEN_CHECK_BOOK_START;
			if (i == IDEN_CHECK_BOOK_START) {
				first_ = true;
			}
			if (cur_ == 0 || iden_list.books_list[cur_ - 1])
			{
				if (first_)
				{
					rc.left = one_;
					rc.top += fontDesc.Height;
					ss.str("");
					ss.clear();
					ss << "<" << LocalzationManager::locString(LOC_SYSTEM_ITEM_BOOK_MAGICBOOK) << ">";
					DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				rc2=rc;
				ss.str("");
				ss.clear();
				if (cur_ == 0)
				{
					img_item_book[0].draw(pSprite, rc.left - 24, rc.top + 6, 255);
					ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << LocalzationManager::locString(LOC_SYSTEM_ITEM_BOOK_UNIDEN_MAGICBOOK);
				}
				else
				{
					img_item_book[cur_ % (RANDOM_BOOK_NUM - 1)].draw(pSprite, rc.left - 24, rc.top + 6, 255);
					ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << LocalzationManager::locString(static_book_list[cur_ - 1].key);
				}
				DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
				rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
				rc.top += 2*fontDesc.Height;
				num++;
			}
		}
		else if (i >= IDEN_CHECK_ETC_START && i < IDEN_CHECK_ETC_END) {
			int cur_ = i - IDEN_CHECK_ETC_START;
			if (i == IDEN_CHECK_ETC_START) {
				first_ = true;
			}
			if (first_)
			{
				rc.left = one_;
				rc.top += fontDesc.Height;
				ss.str("");
				ss.clear();
				ss << "<" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_OTHER) << ">";
				DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
				rc.top += 3 * fontDesc.Height;
				first_ = false;
			}
			rc.left = two_;
			rc2=rc;

			ss.str("");
			ss.clear();
			if (cur_ == 0)
			{
				img_item_food_p_item.draw(pSprite, rc.left - 24, rc.top + 6, 255);
				ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << LocalzationManager::locString(LOC_SYSTEM_ITEM_FOOD_P_ITEM);
			}
			else if (cur_ == 1)
			{
				img_item_food_bread.draw(pSprite, rc.left - 24, rc.top + 6, 255);
				ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_FOOD);
			}
			else if (cur_ >= 2)
			{
				GetTanmacBaseGraphic(cur_-2)->draw(pSprite, rc.left - 24, rc.top + 6, 255);
				ss << index << ' ' << (iden_list.autopickup[i] ? '+' : '-') << ' ' << LocalzationManager::locString(GetTanmacKey(cur_-2));
			}
			DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
			rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
			rc.top += 2 * fontDesc.Height;
			num++;

		}
		
		
			
		if (MousePoint.x > rc2.left && MousePoint.x <= rc2.right &&
			MousePoint.y > rc2.top && MousePoint.y <= rc2.bottom){
			DrawRectOutline(pSprite, rc2, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
			
			if(isClicked(LEFT_CLICK)) {						
				MSG msg;
				msg.message = WM_CHAR;
				msg.wParam = convertClickable(index);
				g_keyQueue->push(InputedKey(msg));
			}
		}
	}

	if (num == 0) {
		rc.left = one_;
		DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_NO_IDEN).c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.top += fontDesc.Height;
	}

	rc.top += move + 64;
	max_y = (rc.top - option_mg.getHeight()>0 ? rc.top - option_mg.getHeight() : 0);
	if(isClicked(MIDDLE_UP)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_UP,0,0));
	} else if(isClicked(MIDDLE_DOWN)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_DOWN,0,0));
	}
}
void display_manager::property_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{	
	RECT rc={50, 50, option_mg.getWidth(), option_mg.getHeight()};
	int i =0;
	if(you.property_vector.empty())
	{
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_NO_PROPERTY).c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		return;
	}
	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_PROPERTY_VIEW).c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += fontDesc.Height*2;
	for(auto it = you.property_vector.begin(); it != you.property_vector.end(); it++)
	{
		RECT rc2={rc.left, rc.top,  rc.right,  rc.bottom};
		stringstream ss;
		char sp_char = (i<26)?('a'+i):('A'+i-26);
		ss << sp_char << " - " << it->GetInfor();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, it->getColor());
		rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
		
		if (MousePoint.x > rc2.left && MousePoint.x <= rc2.right &&
			MousePoint.y > rc2.top && MousePoint.y <= rc2.bottom){
			DrawRectOutline(pSprite, rc2, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
			
			if(isClicked(LEFT_CLICK) || isClicked(RIGHT_CLICK)) {						
				MSG msg;
				msg.message = WM_CHAR;
				msg.wParam = convertClickable(sp_char);
				g_keyQueue->push(InputedKey(msg));
			}
		}
		
		
		rc.top += fontDesc.Height;
		rc.left = 50;
		i++;
	}
	return;
}
void display_manager::skill2_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	RECT rc={50, 50, option_mg.getWidth(), option_mg.getHeight()};

	stringstream ss;

	if(move == 0)
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_SKILL_VIEW_USE).c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
	else
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_SKILL_VIEW_INFO).c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
	rc.top += fontDesc.Height;


	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_HOTKEY), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 50;
	ss << "- " << LocalzationManager::locString(LOC_SYSTEM_NAME);
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 200;
	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_COST), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 200;
	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_SUCCESS_RATE), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += fontDesc.Height;
	rc.left = 50;
	for(int i=0;i<52;i++)
	{
		if(you.MemorizeSkill[i])
		{
			
			skill_list skill_ = (skill_list)you.MemorizeSkill[i];
			char sp_char = i>=26?('A'+i-26):('a'+i);
			ss.str("");
			ss.clear();
			ss << sp_char;
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += 50;
			ss.str("");
			ss.clear();
			ss << "- " << SkillString(skill_);
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += 200;
			{
				ss.str("");
				ss.clear();
				ss << SkillCostString(skill_);
				DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			}
			rc.left = 500;
			ss.str("");
			ss.clear();
			ss << std::setw(3) << std::right << SkillDiffer(skill_) << "%";
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			
			RECT rc2={50, rc.top,  (LONG)(rc.left + PrintCharWidth(ss.str())*fontDesc.Width), (LONG)(rc.top+fontDesc.Height)};
		
			if (MousePoint.x > rc2.left && MousePoint.x <= rc2.right &&
				MousePoint.y > rc2.top && MousePoint.y <= rc2.bottom){
				DrawRectOutline(pSprite, rc2, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
				
				if(isClicked(LEFT_CLICK)) {						
					MSG msg;
					msg.message = WM_CHAR;
					msg.wParam = convertClickable(sp_char);
					g_keyQueue->push(InputedKey(msg));
				}
				else if(isClicked(RIGHT_CLICK)) {
					g_keyQueue->push(InputedKey(MKIND_ITEM_DESCRIPTION,sp_char,0));
				}
			}
			
			rc.top += fontDesc.Height;
			rc.left = 50;
		}
	}
	rc.left = 50;
	rc.top = option_mg.getHeight() - fontDesc.Height*3;
	{
		DrawTextUTF8(pfont,pSprite,(move == 0 ?
			(LocalzationManager::formatString(LOC_SYSTEM_DISPLAY_MANAGER_SKILL_HELP_INFO, PlaceHolderHelper("!"), PlaceHolderHelper("?"))):
			(LocalzationManager::formatString(LOC_SYSTEM_DISPLAY_MANAGER_SKILL_HELP_USE, PlaceHolderHelper("!"), PlaceHolderHelper("?")))
		), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
	}
}

void display_manager::skill_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	RECT rc={50, 50, option_mg.getWidth(), option_mg.getHeight()};
	int skt = 0, i=0; 
	char sk_char = 'a';

	ostringstream ss;

	int max_skillname = 10;
	for(int i = SKT_FIGHT; i < SKT_MAX; i++) {
		max_skillname = min(20, max(max_skillname, PrintCharWidth(skill_string((skill_type)i))));
	}

	int dif[6] = {4, 10, 5, 6, 7, 11};
	if(dif[1] < max_skillname)
		dif[1] = max_skillname;
	int offset[6];
	for(int j = 0; j < 6; j++) {
		offset[j] = dif[j]*fontDesc.Width;
	}

	rc.left += offset[0];
	ss.str("");
	ss.clear();
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SKILL_NAME)) < (dif[1]-2))
		ss << std::string((dif[1]-2)-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SKILL_NAME)), ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_SKILL_NAME);
	DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.left += offset[1];
	DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_LEVEL), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.left += offset[2];	
	ss.str("");
	ss.clear();
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_CURRENT_EXP)) < (dif[3]-1))
		ss << std::string((dif[3]-1)-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_CURRENT_EXP)), ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_CURRENT_EXP);
	DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.left += offset[3];
	DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_ATTIT), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.left += offset[4];
	DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_COST), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.left += offset[5];
	rc.left += offset[0];
	ss.str("");
	ss.clear();
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SKILL_NAME)) < (dif[1]-2))
		ss << std::string((dif[1]-2)-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SKILL_NAME)), ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_SKILL_NAME);
	DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.left += offset[1];
	DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_LEVEL), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.left += offset[2];
	ss.str("");
	ss.clear();
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_CURRENT_EXP)) < (dif[3]-1))
		ss << std::string((dif[3]-1)-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_CURRENT_EXP)), ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_CURRENT_EXP);
	DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.left += offset[3];
	DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_ATTIT), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.left += offset[4];
	DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_COST), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	
	rc.top += 2*fontDesc.Height;

	rc.left = 50;

	while(skt < SKT_MAX)
	{
		for(i = 0;i<1;i++)
		{
			RECT rc2={ rc.left, rc.top,  rc.right, (LONG)(rc.top+fontDesc.Height)};
			D3DCOLOR color_ = you.GetSkillLevel(skt, true) < 27 && !you.cannotSkillup(skt) ?
				(you.bonus_skill[skt]? (you.skill[skt].onoff == 2 ? CL_white_blue : (you.skill[skt].onoff == 1 ? CL_blue : CL_darkblue)) :

				(you.skill[skt].onoff == 2 ? CL_normal : (you.skill[skt].onoff == 1 ? CL_STAT : CL_bad))) :
				you.pure_skill == skt ? CL_junko : CL_warning;
			ss.str("");
			ss.clear();
			ss << ((you.GetSkillLevel(skt, false)==27 || you.cannotSkillup(skt)) ?' ':sk_char) << ' ' << ((you.GetSkillLevel(skt, false) ==27 || you.cannotSkillup(skt) )?' ':(you.skill[skt].onoff ==2?'*':(you.skill[skt].onoff ==1?'+':'-')));
			sk_char++;
			DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, color_);
			rc.left += offset[0];
			ss.str("");
			ss.clear();
			if(PrintCharWidth(skill_string((skill_type)skt)) < (dif[1]-2))
				ss << std::string((dif[1]-2)-PrintCharWidth(skill_string((skill_type)skt)), ' ');
			ss << skill_string((skill_type)skt);
			DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, color_);
			rc.left += offset[1];
			ss.str("");
			ss.clear();
			ss << std::setw(2) << std::right << you.GetSkillLevel(skt, true);
			DrawTextUTF8(pfont,pSprite,	ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, color_);
			rc.left += offset[2];
			ss.str("");
			ss.clear();
			if(you.GetSkillLevel(skt, false)<27 && !you.cannotSkillup(skt))
				ss << "(" << std::setw(2) << std::right << GetSkillPercent(you.skill[skt]) << "%)";
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, color_);
			rc.left += offset[3];
			ss.str("");
			ss.clear();
			ss << std::setw(3) << std::right << you.skill[skt].aptit;
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,GetSkillColor(you.skill[skt].aptit));
			rc.left += offset[4];
			
			ss.str("");
			ss.clear();
			if (you.GetSkillLevel(skt, false) < 27 && !you.cannotSkillup(skt))
			{
				int base_skill = GetBaseSkillExp();
				int skill_pecent = GetMaxSkillExp(you.skill[skt]);
				exp_to_skill_exp(you.GetSkillLevel(skt, false));

				float value_ = (float)skill_pecent / base_skill;

				ss << std::fixed << std::setw(3) << std::setprecision(1) << value_;
				DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
			
				rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
			}
			else if (you.pure_skill == skt)
			{
				DrawTextUTF8(pfont,pSprite,  LocalzationManager::locString(LOC_SYSTEM_SKILL_JUNKA), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_junko);
			
				rc2.right = rc.left + PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SKILL_JUNKA))*fontDesc.Width;
			}
			else
			{
				ss << " -";
				DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
				rc2.right = rc.left + PrintCharWidth(ss.str())*fontDesc.Width;
			}
			
			if (MousePoint.x > rc2.left && MousePoint.x <= rc2.right &&
				MousePoint.y > rc2.top && MousePoint.y <= rc2.bottom){
				DrawRectOutline(pSprite, rc2, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
				
				if(isClicked(LEFT_CLICK)) {						
					MSG msg;
					msg.message = WM_CHAR;
					msg.wParam = convertClickable(sk_char-1);
					g_keyQueue->push(InputedKey(msg));
				}
				else if(isClicked(RIGHT_CLICK)) {
					g_keyQueue->push(InputedKey(MKIND_ITEM_DESCRIPTION,sk_char-1,0));
				}
			}
			
			

			if(sk_char == 'z'+1)
				sk_char = 'A';
			switch (skt)
			{
			case SKT_FIGHT:
			case SKT_TANMAC - 1:
			case SKT_TANMAC:
			case SKT_SPELLCASTING:
			case SKT_EVOCATE-1:
				rc.top += fontDesc.Height;
				break;
			default:
				break;
			}


			if(skt == SKT_SPELLCASTING - 1)
			{
				rc.left += offset[0]+offset[1]+offset[2]+offset[3]+offset[4]+offset[5];
				rc.top = 50+fontDesc.Height;
			}
		}
		rc.left -= offset[0]+offset[1]+offset[2]+offset[3]+offset[4];
		rc.top += fontDesc.Height;
		skt++;
	}

	rc.left = 50;	
	rc.top += fontDesc.Height*2;
	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(item_view_message).c_str(), -1, &rc, DT_NOCLIP,CL_warning);
	rc.top += fontDesc.Height *2;

	if (LocalzationManager::locString(item_view_message).size() < 1)
	{
		DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_ATTITUDE_HELP1), -1, &rc, DT_NOCLIP, CL_normal);
		rc.top += fontDesc.Height * 1;

		DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_ATTITUDE_HELP2), -1, &rc, DT_NOCLIP, CL_normal);

		rc.top += fontDesc.Height * 2;
		if (wiz_list.wizard_mode == 1)
		{
			DrawTextUTF8(pfont,pSprite,  LocalzationManager::formatString(LOC_SYSTEM_DISPLAY_MANAGER_ATTITUDE_DEBUG, PlaceHolderHelper(to_string(exp_to_skill_exp(0)))), -1, &rc, DT_NOCLIP, CL_help);
		}
	}

}
void display_manager::state_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	RECT rc={30, 10, option_mg.getWidth(), option_mg.getHeight()};
	ostringstream ss;
	ss.str("");
	ss.clear();
	ss << you.user_name << " (" << LocalzationManager::formatString(LOC_SYSTEM_LEVEL_WITH_NUMBER, PlaceHolderHelper(to_string(you.level))) << ' '
	   << LocalzationManager::locString(tribe_type_string[you.tribe]) << ' ' << LocalzationManager::locString(job_type_string[you.job]) << ' ' <<you.GetCharNameString() << ')';

	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_warning);
	rc.left += 350;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_TURNS) << ": " << you.turn;
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 200;
	if(you.god == GT_NONE)
	{
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_AHTEISM), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	else if (you.god == GT_TENSI)
	{
		ss.str("");
		ss.clear();
		ss << LocalzationManager::locString(LOC_SYSTEM_FAITH) << ": " << GetGodString(you.god);
		DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	else
	{
		ss.str("");
		ss.clear();
		ss << LocalzationManager::locString(LOC_SYSTEM_FAITH) << ": " << GetGodString(you.god) << ' ' 
			<< (pietyLevel(you.piety)>=1?'*':'.') << (pietyLevel(you.piety)>=2?'*':'.') << (pietyLevel(you.piety)>=3?'*':'.') << (pietyLevel(you.piety)>=4?'*':'.') << (pietyLevel(you.piety)>=5?'*':'.') << (pietyLevel(you.piety)>=6?'*':'.');
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	ss.str("");
	ss.clear();
	ss << "HP: " << you.GetHp() << "/" << you.GetMaxHp();
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << "AC:" << std::setw(4) << std::right << you.ac;
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 200;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_STR);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_STR)) < 4)
		ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_STR)), ' ');
	ss << ":" << std::setw(4) << std::right << you.s_str;
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;		

	if (!you.pure_mp)
	{
		ss.str("");
		ss.clear();
		ss << "MP: " << you.GetMp() << "/" << you.GetMaxMp();
		DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << "EV:" << std::setw(4) << std::right << you.ev;
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 200;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX)) < 4)
		ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX)), ' ');
	ss << ":" << std::setw(4) << std::right << you.s_dex;
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;		

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);

	{
		int pow_ = min(you.power, 500);
		ss.str("");
		ss.clear();
		ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER);
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER)) < 4)
			ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER)), ' ');
		ss << ":" << pow_ / 100 << "." << std::setfill('0') << std::setw(2) << pow_ % 100;
		ss << std::setfill(' ');
		DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << "SH:" << std::setw(4) << std::right << you.sh;
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 200;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_INT);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_INT)) < 4)
		ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_INT)), ' ');
	ss << ":" << std::setw(4) << std::right << you.s_int;
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;		
	rc.top += fontDesc.Height;		

	int resist_ = you.fire_resist - you.uniden_fire_resist;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_FIRE_RESIST);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_FIRE_RESIST)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_FIRE_RESIST)), ' ');
	if(resist_>=100) {
		ss << ": ∞";
	}
	else {
		ss << ": " << (resist_>=1?'+':(resist_<=-1?'-':'.')) << ' ' << (resist_>=2?'+':(resist_<=-2?'-':'.')) << ' ' << (resist_>=3?'+':(resist_<=-3?'-':'.'));
	}
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	resist_ = you.confuse_resist- you.uniden_confuse_resist;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_CONFUSE_RESIST);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_CONFUSE_RESIST)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_CONFUSE_RESIST)), ' ');
	ss << ": " << (resist_>=1?'+':(resist_<=-1?'-':'.'));
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_WEAPON) << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_WEAPON])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_WEAPON]->id << ") " << you.equipment[ET_WEAPON]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
	}
	else
	{
		ss.str("");
		ss.clear();
		ss << LocalzationManager::locString(LOC_SYSTEM_UI_UNARMED);
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;


	resist_ = you.ice_resist - you.uniden_ice_resist;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_COLD_RESIST);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_COLD_RESIST)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_COLD_RESIST)), ' ');
	if(resist_>=100) {
		ss << ": ∞";
	}
	else {
		ss << ": " << (resist_>=1?'+':(resist_<=-1?'-':'.')) << ' ' << (resist_>=2?'+':(resist_<=-2?'-':'.')) << ' ' << (resist_>=3?'+':(resist_<=-3?'-':'.'));
	}
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	resist_ = you.invisible_view- you.uniden_invisible_view;	
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_SEE_INVISIBLE);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_SEE_INVISIBLE)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_SEE_INVISIBLE)), ' ');
	ss << ": " << (resist_>=1?'+':(resist_<=-1?'-':'.'));
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_TANMAC) << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.throw_weapon)
	{
		ss.str("");
		ss.clear();
		ss << you.throw_weapon->id << ") " << you.throw_weapon->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.throw_weapon->item_color());
	}
	else
	{
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_UI_NONE), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	resist_ = you.elec_resist - you.uniden_elec_resist;	
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_ELEC_RESIST);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_ELEC_RESIST)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_ELEC_RESIST)), ' ');
	if(resist_>=100) {
		ss << ": ∞";
	}
	else {
		ss << ": " << (resist_>=1?'+':(resist_<=-1?'-':'.')) << ' ' << (resist_>=2?'+':(resist_<=-2?'-':'.')) << ' ' << (resist_>=3?'+':(resist_<=-3?'-':'.'));
	}
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	resist_ = you.power_keep- you.uniden_power_keep;

	
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER_KEEP);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER_KEEP)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER_KEEP)), ' ');
	if(you.power == 1000) {
		ss << ": ∞";
	}
	else {
		ss << ": " << (resist_>=1?'+':(resist_<=-1?'-':'.'));
	}
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_BODY) << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_ARMOR])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_ARMOR]->id << ") " << you.equipment[ET_ARMOR]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_ARMOR]->item_color());
	}
	else
	{
		DrawTextUTF8(pfont,pSprite,you.isImpossibeEquip(ET_ARMOR, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	
	resist_ = you.poison_resist - you.uniden_poison_resist;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_POISON_RESIST);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POISON_RESIST)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POISON_RESIST)), ' ');
	ss << ": " << (resist_>=1?'+':(resist_<=-1?'-':'.'));
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_SHIELD) << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_SHIELD])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_SHIELD]->id << ") " << you.equipment[ET_SHIELD]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_SHIELD]->item_color());
	}
	else
	{
		DrawTextUTF8(pfont,pSprite, you.isImpossibeEquip(ET_SHIELD, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	





	string resist_text_ = "";
	{
		for (int i = 0; i < 10; i++) {
			if (you.GetResist() > 110 + i * 20) {
				resist_text_ += "#";
			}
			else {
				resist_text_ += ".";
			}
		}
	}
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_MAGICRESIST);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_MAGICRESIST)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_MAGICRESIST)), ' ');
	ss << ": " << resist_text_;
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_HEAD) << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_HELMET])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_HELMET]->id << ") " << you.equipment[ET_HELMET]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_HELMET]->item_color());
	}
	else
	{
		DrawTextUTF8(pfont,pSprite,you.isImpossibeEquip(ET_HELMET, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	
	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_CLOAK) << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_CLOAK])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_CLOAK]->id << ") " << you.equipment[ET_CLOAK]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_CLOAK]->item_color());
	}
	else
	{
		DrawTextUTF8(pfont,pSprite,you.isImpossibeEquip(ET_CLOAK, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
	

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_HAND) << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_GLOVE])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_GLOVE]->id << ") " << you.equipment[ET_GLOVE]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_GLOVE]->item_color());
	}
	else {
		DrawTextUTF8(pfont,pSprite,you.isImpossibeEquip(ET_GLOVE, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;


	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_FOOT) << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_BOOTS])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_BOOTS]->id << ") " << you.equipment[ET_BOOTS]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_BOOTS]->item_color());
	}
	else
	{
		DrawTextUTF8(pfont,pSprite,you.isImpossibeEquip(ET_BOOTS, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
	

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_AMULET);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_AMULET)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_AMULET)), ' ');
	ss << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_NECK])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_NECK]->id << ") " << you.equipment[ET_NECK]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_NECK]->item_color());
	}
	else
	{
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_UI_NONE), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

		

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_LEFT_RING);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_LEFT_RING)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_LEFT_RING)), ' ');
	ss << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_LEFT])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_LEFT]->id << ") " << you.equipment[ET_LEFT]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_LEFT]->item_color());
	}
	else
	{
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_UI_NONE), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
			

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_RIGHT_RING);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_RIGHT_RING)) < 8)
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_RIGHT_RING)), ' ');
	ss << ": ";
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*(PrintCharWidth(ss.str()));
	if(you.equipment[ET_RIGHT])
	{
		ss.str("");
		ss.clear();
		ss << you.equipment[ET_RIGHT]->id << ") " << you.equipment[ET_RIGHT]->GetName();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_RIGHT]->item_color());
	}
	else
	{
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_UI_NONE), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
	rc.top += fontDesc.Height;



	
	ss.str("");
	ss.clear();
	ss << LocalzationManager::locString(LOC_SYSTEM_ITEM_RUNE_RUNE) << ": ";
	for(int i=0;i<RUNE_HAKUREI_ORB;i++)
	{		
		if(you.rune[i])
		{
			if(i!=0)
				ss << ", ";
			ss <<  LocalzationManager::locString(rune_string[i]);
		}
	}
	DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;
	
	if(you.rune[RUNE_HAKUREI_ORB])
	{
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_ITEM_YINYANG), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	else
	{				
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

}

void display_manager::game_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	int sight_x = option_mg.getTileMaxX();
	int sight_y = option_mg.getTileMaxY();
	int buff_start_y = 340;//추후 버프 위치에 맞춰짐
	ostringstream ss;
	GetClientRect(hwnd, &windowSize);
	scale_x = (windowSize.right - windowSize.left) / (float)option_mg.getWidth();
	scale_y = (windowSize.bottom - windowSize.top) / (float)option_mg.getHeight();
	infobox.init();
	{
		int i=0;
		RECT rc={32*(sight_x*2)+50, 10, option_mg.getWidth(), option_mg.getHeight()};
		ss.str("");
		ss.clear();
		ss << LocalzationManager::formatString(LOC_SYSTEM_LEVEL_WITH_NUMBER, PlaceHolderHelper(to_string(you.level)));
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*(2 + PrintCharWidth(ss.str()));
		DrawTextUTF8(pfont,pSprite,you.user_name.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		
		if(ReplayClass.play)
		{
			rc.left = 32*(sight_x*2)+180;
			ss.str("");
			ss.clear();
			ss << "*" << LocalzationManager::locString(LOC_SYSTEM_REPLAY_MODE) << "*";
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, wiz_list.wizard_mode == 1?CL_help:(wiz_list.wizard_mode == 2?CL_magic:CL_warning));
		}
		else if(wiz_list.wizard_mode == 1)
		{
			rc.left = 32*(sight_x*2)+180;
			ss.str("");
			ss.clear();
			ss << "*" << LocalzationManager::locString(LOC_SYSTEM_WIZARD_MODE) << "*";
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
		}
		else if(wiz_list.wizard_mode == 2)
		{
			rc.left = 32*(sight_x*2)+180;
			ss.str("");
			ss.clear();
			ss << "*" << LocalzationManager::locString(LOC_SYSTEM_SAVEREMAIN_MODE) << "*";			
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
		}




		rc.top += fontDesc.Height;
		rc.left = 32*(sight_x*2)+50;
		if(you.char_type == UNIQ_START_NONE) {
			string tribe_string = LocalzationManager::locString(tribe_type_string[you.tribe]);
			DrawTextUTF8(pfont,pSprite,tribe_string.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += fontDesc.Width*(PrintCharWidth(tribe_string)+1);
			string job_string = LocalzationManager::locString(job_type_string[you.job]);
			DrawTextUTF8(pfont,pSprite,job_string.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += fontDesc.Width*(PrintCharWidth(job_string)+1);
		} else {
			DrawTextUTF8(pfont,pSprite,you.GetCharNameString().c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += fontDesc.Width*(PrintCharWidth(you.GetCharNameString())+3);//조금 띄어씀
		}

		ss.str("");
		ss.clear();
		if(you.god == GT_NONE)
		{
			ss << LocalzationManager::locString(LOC_SYSTEM_AHTEISM);
		}
		else if (you.god == GT_MIKO) 
		{
			ss << GetGodString(you.god) << " (" <<  LocalzationManager::locString(LOC_SYSTEM_POULARITY) << ' ' << you.piety/2 << "%)";
		}
		else if (you.god == GT_TENSI)
		{
			ss << GetGodString(you.god);
		}
		else
		{
			ss << GetGodString(you.god) << ' ' 
				<< (pietyLevel(you.piety)>=1?'*':'.') << (pietyLevel(you.piety)>=2?'*':'.') << (pietyLevel(you.piety)>=3?'*':'.') << (pietyLevel(you.piety)>=4?'*':'.') << (pietyLevel(you.piety)>=5?'*':'.') << (pietyLevel(you.piety)>=6?'*':'.');
		}
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left = 32*(sight_x*2)+50;
		rc.top += fontDesc.Height;

		ss.str("");
		ss.clear();
		ss << "HP: " << you.GetHp() << "/" << you.GetMaxHp();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*14;
		{
			int Hp_bar = max(you.GetHp() *18/you.GetMaxHp(),min(you.prev_hp[0],you.GetMaxHp())*18/you.GetMaxHp());
			int s_Hp_bar = min(you.GetHp() *18/you.GetMaxHp(),min(you.prev_hp[0],you.GetMaxHp())*18/you.GetMaxHp());
			D3DCOLOR color_ = (you.GetHp() *18/you.GetMaxHp()>min(you.prev_hp[0],you.GetMaxHp())*18/you.GetMaxHp())?(!you.pure_mp ? CL_dark_good :CL_black_junko):CL_danger;

			for(i = 0;i<s_Hp_bar;i++)
			{
				DrawTextUTF8(pfont,pSprite,"=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, !you.pure_mp?CL_good:CL_junko);
				rc.left += fontDesc.Width;
			}
			for(;i<Hp_bar;i++)
			{
				DrawTextUTF8(pfont,pSprite,"=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, color_);
				rc.left += fontDesc.Width;
			}
			for(;i<18;i++)
			{
				DrawTextUTF8(pfont,pSprite,"=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_bad);
				rc.left += fontDesc.Width;
			}
		}
		rc.left -= fontDesc.Width*32;


		rc.top += fontDesc.Height;
		if (!you.pure_mp)
		{
			ss.str("");
			ss.clear();
			ss << "MP: " << you.GetMp() << "/" << you.GetMaxMp();
			DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			if (you.GetMaxMp())
			{
				rc.left += fontDesc.Width * 14;
				for (i = 0; i < you.GetMp() * 18 / you.GetMaxMp(); i++)
				{
					DrawTextUTF8(pfont,pSprite, "=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_blue);
					rc.left += fontDesc.Width;
				}
				for (; i < 18; i++)
				{
					DrawTextUTF8(pfont,pSprite, "=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_bad);
					rc.left += fontDesc.Width;
				}
				rc.left -= fontDesc.Width * 32;
			}
			rc.top += fontDesc.Height;
		}



		int pow_ = min(you.power,500);
		img_item_food_p_item.draw(pSprite,rc.left+7,rc.top+7,255);

		ss.str("");
		ss.clear();
		ss << "   " << pow_ / 100 << "." << std::setfill('0') << std::setw(2) << pow_ % 100;
		DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, you.power == 1000 ? CL_junko :(pow_<=100?CL_danger:(pow_<=200?CL_warning:(pow_==500?CL_good:CL_normal))));
		//임시		
		//rc.left += fontDesc.Width*left_;
		//sprintf_s(temp,50,"%6d",you.hunger);
		//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, you.s_might?CL_white_blue:CL_STAT);
		rc.left = 32*(sight_x*2)+50;




		rc.top += fontDesc.Height;
		ss.str("");
		ss.clear();
		ss << "AC  :";
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());
				
		int temp_buff_value_ = 0;


		ss.str("");
		ss.clear();
		ss << std::setfill(' ') << std::setw(4) << you.GetDisplayAc();
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_AC)+ ((you.alchemy_buff == ALCT_DIAMOND_HARDNESS)?5:0);
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, (temp_buff_value_>0?CL_white_blue:(temp_buff_value_<0?CL_small_danger:CL_STAT)));
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());


		ss.str("");
		ss.clear();
		ss << "  ";
		ss << "EV  :";
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());

		ss.str("");
		ss.clear();
		ss << std::setfill(' ') << std::setw(4) << you.GetDisplayEv();
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_EV);
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:CL_STAT);
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());


		ss.str("");
		ss.clear();
		ss << "  ";
		ss << "SH  :";
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());

		ss.str("");
		ss.clear();
		ss << std::setfill(' ') << std::setw(4) << you.GetDisplaySh();
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_SH);
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:CL_STAT);



		rc.left = 32*(sight_x*2)+50;
		rc.top += fontDesc.Height;

		ss.str("");
		ss.clear();
		ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_STR);
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_STR)) < 4)
			ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_STR)), ' ');
		ss << ":" ;
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());


		ss.str("");
		ss.clear();
		ss << std::setfill(' ') << std::setw(4) << you.s_str;
		if(you.s_str != you.m_str) {
			ss << " (" << std::setw(2) << you.m_str <<")";
		}
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_STR);
		{
			D3DCOLOR color_ = 
				you.s_str<=0?CL_danger:
				temp_buff_value_>0?CL_white_blue:
				temp_buff_value_<0?CL_small_danger:
				you.s_stat_boost==1?CL_white_puple:
				(you.s_str != you.m_str)?CL_warning:CL_STAT;
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,color_);
			rc.left += fontDesc.Width*PrintCharWidth(ss.str());
		}


		ss.str("");
		ss.clear();
		ss << "  ";
		ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX);
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX)) < 4)
			ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX)), ' ');
		ss << ":" ;
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());


		ss.str("");
		ss.clear();
		ss << std::setfill(' ') << std::setw(4) << you.s_dex;
		if(you.s_dex != you.m_dex) {
			ss << " (" << std::setw(2) << you.m_dex <<")";
		}
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_DEX);
		{
			D3DCOLOR color_ = 
				you.s_dex<=0?CL_danger:
				temp_buff_value_>0?CL_white_blue:
				temp_buff_value_<0?CL_small_danger:
				you.s_stat_boost==2?CL_white_puple:
				(you.s_dex != you.m_dex)?CL_warning:CL_STAT;
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,color_);
			rc.left += fontDesc.Width*PrintCharWidth(ss.str());
		}


		ss.str("");
		ss.clear();
		ss << "  ";
		ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_INT);
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_INT)) < 4)
			ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_INT)), ' ');
		ss << ":" ;
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());


		ss.str("");
		ss.clear();
		ss << std::setfill(' ') << std::setw(4) << you.s_int;
		if(you.s_int != you.m_int) {
			ss << " (" << std::setw(2) << you.m_int <<")";
		}
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_INT);
		{
			D3DCOLOR color_ =
				you.s_int<=0?CL_danger:
				temp_buff_value_>0?CL_white_blue:
				temp_buff_value_<0?CL_small_danger:
				you.s_stat_boost==3?CL_white_puple:
				(you.s_int != you.m_int)?CL_warning:CL_STAT;
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,color_);
			rc.left = 32*(sight_x*2)+50;
		}

		rc.top += fontDesc.Height;


		ss.str("");
		ss.clear();
		ss << LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET);
		ss << ": " ;
		DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width * PrintCharWidth(ss.str());

		if (you.equipment[ET_NECK])
		{
			ss.str("");
			ss.clear();
			item* _item = you.equipment[ET_NECK];
			if (_item->type == ITM_AMULET)
			{
				//ss << you.equipment[ET_NECK]->id << ") " << LocalzationManager::formatString(iden_list.amulet_list[_item->value1].iden == 2 ? amulet_iden_string[_item->value1] : amulet_uniden_string[iden_list.amulet_list[_item->value1].type], PlaceHolderHelper(""))
				// << "(" << to_string(you.getAmuletPercent()) << "%)";
				ss << _item->id << ") " << _item->GetName();
			} else {
				ss << _item->id << ") " << _item->GetName();
			}
			DrawTextUTF8(pfont,pSprite, ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, _item->item_color());
		}
		else
		{
			DrawTextUTF8(pfont,pSprite, LocalzationManager::locString(LOC_SYSTEM_UI_NONE), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
		}
		rc.left = 32*(sight_x*2) + 50;
		rc.top += fontDesc.Height;
		
		ss.str("");
		ss.clear();
		ss << LocalzationManager::locString(LOC_SYSTEM_UI_WEAPON);
		ss << ": " ;
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());
		if(you.equipment[ET_WEAPON])
		{
			ss.str("");
			ss.clear();
			ss << you.equipment[ET_WEAPON]->id << ") " << you.equipment[ET_WEAPON]->GetName();

			vector<string> tokens = SplitStringByFontWidth(ss.str(), 26, 34);

			for (const string& token : tokens ) {
				DrawTextUTF8(pfont,pSprite,token, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
				rc.left = 32*(sight_x*2)+50;
				rc.top +=fontDesc.Height;
			}
		}
		else
		{
			DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_UI_UNARMED), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
			rc.left = 32*(sight_x*2)+50;
			rc.top +=fontDesc.Height;
		}
		//rc.left -= fontDesc.Width*6;

		//rc.top += fontDesc.Height;
		ss.str("");
		ss.clear();
		ss << LocalzationManager::locString(LOC_SYSTEM_UI_TANMAC);
		ss << ": " ;
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*PrintCharWidth(ss.str());
		if(you.throw_weapon)
		{
			ss.str("");
			ss.clear();
			ss << you.throw_weapon->id << ") " << you.throw_weapon->GetName();

			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.throw_weapon->item_color());
		}
		else
		{
			DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_UI_NONE), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
		}
		rc.left = 32*(sight_x*2)+50;




		
		if(you.GetNeedExp(you.level-1) > 0)
		{
			rc.top += fontDesc.Height;
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_REMAIN_EXP);
			ss << ":" ;
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += fontDesc.Width*PrintCharWidth(ss.str());
		
			ss.str("");
			ss.clear();
			ss << (you.exper-you.GetNeedExp(you.level-2))*100/(you.GetNeedExp(you.level-1)-you.GetNeedExp(you.level-2)) << "%";
			DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_STAT);
			rc.left = 32*(sight_x*2)+50;
		}
		else
		{
			rc.top += fontDesc.Height;
			DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_MAX_LEVEL), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_warning);

		}


		rc.top += fontDesc.Height;
		ss.str("");
		ss.clear();
		ss << CurrentLevelString();
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*max(15, PrintCharWidth(ss.str()) + 1) ;
		
		
		ss.str("");
		ss.clear();
		ss << LocalzationManager::locString(LOC_SYSTEM_TURNS) << ": " << you.real_turn/10.0f << " (" << you.prev_real_turn/10.0f << ")"; 
		DrawTextUTF8(pfont,pSprite,ss.str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);	
		rc.left = 32*(sight_x*2)+50;
		rc.top += fontDesc.Height;
		buff_start_y = rc.top;
		{ 
			stateBox stateDraw(pSprite, pfont, rc);


			if(wiz_list.wizard_mode == 1)
			{
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_DEBUG_RISK) << "(" << you.tension_gauge << ")"; 
				stateDraw.addState(ss.str(), CL_small_danger, LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RISK), this);
				stateDraw.enter(this);
			}
			if (you.s_weather>0 && you.s_weather_turn)
			{
				D3DCOLOR color_ = CL_normal;
				switch (you.s_weather) {
				case 1:
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_FOG), color_, LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_FOG), this);
					break;
				case 2:
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_THUNDER), color_, LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_THUNDER), this);
					break;
				case 3:
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_SUNNY), color_, LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_SUNNY), this);
					break;
				}
				stateDraw.enter(this);
			}
			if(you.as_penalty>0)
			{
				D3DCOLOR color_ = you.as_penalty>you.GetPenaltyMinus(3)?CL_danger: //끔찍
					you.as_penalty>you.GetPenaltyMinus(2)?CL_small_danger: //이동패널티
					you.as_penalty>you.GetPenaltyMinus(1)?CL_warning: //명중
					CL_bad;
		
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_BUFF_EQUIP_PENALTY) << "(" << you.as_penalty << ")"; 
				stateDraw.addState(ss.str(), color_,
					you.as_penalty > you.GetPenaltyMinus(3) ?  LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_EQUIP_PENALTY1) : //끔찍
					you.as_penalty>you.GetPenaltyMinus(2) ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_EQUIP_PENALTY2): //이동패널티
					you.as_penalty>you.GetPenaltyMinus(1) ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_EQUIP_PENALTY3) : //명중
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_EQUIP_PENALTY4), this);
			}
			bool haste_temp_ = false;

			if (you.god == GT_MIKO)
			{
				if (env[current_level].popular == 1) {
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_MIKO_NEWPLACE), CL_normal, LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_MIKO_NEWPLACE), this);
				}
				int mikocloak_ = you.isSetMikoBuff(0);
				if (mikocloak_ == 1) {
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_MIKO_REDCLOAK), CL_danger, LocalzationManager::formatString(LOC_SYSTEM_BUFF_DESCRIBE_MIKO_REDCLOAK, PlaceHolderHelper("+6")), this);
				}
				else if (mikocloak_ == 2) {
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_MIKO_BLUECLOAK), CL_blue, LocalzationManager::formatString(LOC_SYSTEM_BUFF_DESCRIBE_MIKO_BLUECLOAK, PlaceHolderHelper("1.5")), this);
				}
				int ulti_ = you.isSetMikoBuff(1);
				if (ulti_ >= 1 && ulti_ <= 3) {
					stateDraw.addState(ulti_ == 1 ?LocalzationManager::locString(LOC_SYSTEM_BUFF_MIKO_ULT1):(ulti_ == 2 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_MIKO_ULT2) : LocalzationManager::locString(LOC_SYSTEM_BUFF_MIKO_ULT3)),
						CL_miko, 
						ulti_ == 1 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_MIKO_ULT1)
						: (ulti_ == 2 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_MIKO_ULT2) : 
						LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_MIKO_ULT3)), this);
					if (ulti_ == 3) {
						haste_temp_ = true;
					}
				}
				if (you.GetBuffOk(BUFFSTAT_HALO)) {
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_MIKO_HALO), CL_normal,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_MIKO_HALO), this);
				}
			}
			else if (you.GetPunish(GT_MIKO)) {
				if (you.GetBuffOk(BUFFSTAT_HP) < 0) {
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_MIKO_PUNISH), CL_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_MIKO_PUNISH), this);
				}
			}
			if (you.god == GT_JOON_AND_SION || you.GetPunish(GT_JOON_AND_SION))
			{
				if (you.god_value[GT_JOON_AND_SION][0] == 1) {
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_JOON), CL_joon, you.GetPunish(GT_JOON_AND_SION)?LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_JOON1):
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_JOON2), this);
				}
				if (you.god_value[GT_JOON_AND_SION][0] == 2) {
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_SION), CL_sion, you.GetPunish(GT_JOON_AND_SION) ?LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_SION1) : 
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_SION2), this);
				}
			}
			if (you.drowned)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_DROWNING), CL_danger, LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_DROWNING), this);
			}
			if (current_level == ZIGURRAT_LEVEL)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_CTELE_INTERUPT), CL_danger, LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_CTELE_INTERUPT), this);
			}
			if(you.GetStatPanalty())
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_PANALTY), CL_danger,  LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_PANALTY), this);
			}
			if(you.s_exhausted)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_EXHAUTED), CL_warning,  LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_EXHAUTED), this);
			}
			if (you.s_super_graze)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SUPER_GRAZE), you.s_super_graze>3 ? CL_normal : CL_white_blue, LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SUPER_GRAZE), this);
			}
			if(you.s_trans_panalty)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_TRANS_PANALTY), you.s_trans_panalty <= 2 ? CL_bad : (you.s_trans_panalty<5 ? CL_warning : CL_small_danger), 
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_TRANS_PANALTY), this);
			}
			if(you.s_spellcard)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SPELLCARD), you.s_spellcard>5 ? CL_white_blue : CL_blue, 
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SPELLCARD), this);
			}
			if(you.s_autumn>0)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_AUTMMN_INVISIBLE), you.s_autumn>0 ? CL_autumn : CL_danger, 
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_AUTMMN_INVISIBLE), this);
			}
			if(you.s_wind)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_KANAKO_WIND), CL_white_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_KANAKO_WIND), this);
			}
			if(you.s_knife_collect)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_KNIFECOLLECT), CL_white_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_KNIFECOLLECT), this);
			}
			if(you.s_drunken)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_DRUNKEN), CL_warning,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_DRUNKEN), this);
			}
			if(you.s_lunatic)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_LUNATIC), CL_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_LUNATIC), this);
			}
			if(you.s_catch)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_CATCH), CL_yuigi,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_CATCH), this);
			}
			if(you.s_ghost)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_GHOST), you.s_ghost>1 ? CL_white_blue : CL_yuyuko,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_GHOST), this);
			}
			if(you.s_dimension)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_DIMENSION), you.s_dimension>3 ? CL_yukari : CL_blue,
				 (you.god == GT_YUKARI)?
				 	LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_DIMENSION1):
					 LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_DIMENSION2), this);
			}
			if(you.s_mirror)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_MIRROR), CL_normal,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_MIRROR), this);
			}
			if(you.s_paradox)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_PARADOX), CL_white_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_PARADOX), this);
			}
			if(you.s_the_world)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_THE_WORLD), you.s_the_world>1 ? CL_white_blue : you.s_the_world<0 ? CL_normal : CL_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_THE_WORLD), this);
			}
			if(you.s_mana_delay)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_MANA_DELAY), CL_warning,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_MANA_DELAY), this);
			}
			if (env[current_level].isSilence(you.position))
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SILENCE_FIELD), CL_white_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SILENCE_FIELD), this);
			}
			if(you.s_eirin_poison_time)
			{
				D3DCOLOR color_ = you.s_eirin_poison_time>11 ? CL_small_danger : CL_danger;
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_BUFF_EIRIN_POISON) << "(" << you.tension_gauge << ")"; 
				stateDraw.addState(ss.str(), color_,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_EIRIN_POISON), this);
			}
			if(you.s_stasis)
			{				
				D3DCOLOR color_ = CL_danger;
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STASIS), color_,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STASIS), this);
			}
			if(you.force_turn)
			{				
				D3DCOLOR color_ = you.force_strong?CL_white_blue:CL_danger;
				stateDraw.addState(you.force_strong?LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_ENHANCE):LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_WEAKENING), color_,
					you.force_strong ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_ENHANCE) :
						LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_WEAKENING), this);
			}
			if (you.s_evoke_ghost)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_GHOSTFORM), CL_normal,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_GHOSTFORM), this);
			}

			



			

			if(you.power<=200)
			{
				bool sion_ = (you.god == GT_JOON_AND_SION && !you.GetPunish(GT_JOON_AND_SION) && you.god_value[GT_JOON_AND_SION][0] == 2);
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_POWER_PANALTY), sion_ ? CL_bad:(you.power <= 100 ? CL_danger : CL_warning),
					sion_ ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_POWER_PANALTY_SION) :(you.power <= 100 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_POWER_PANALTY2): LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_POWER_PANALTY1)), this);
			}
			if(you.s_poison)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_POISON), you.s_poison <= 50 ? CL_warning : (you.s_poison <= 100 ? CL_small_danger : CL_danger),
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_POISON), this);
			}
			if(you.s_tele)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_TELE), CL_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_TELE), this);
			}
			if((you.s_pure_haste || you.s_haste || you.alchemy_buff == ALCT_HASTE) && !you.s_slow)
			{
				if ((you.s_haste || you.alchemy_buff == ALCT_HASTE) && !haste_temp_)
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_HASTE), you.alchemy_buff == ALCT_HASTE ? CL_alchemy : (you.s_haste>10 ? CL_white_blue : CL_blue),
						LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_HASTE), this);
				else if (you.s_pure_haste)
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_MURDEROUS),CL_junko,
						LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_MURDEROUS), this);
			}
			else if(you.s_slow && !(you.s_haste || you.alchemy_buff == ALCT_HASTE))
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SLOW), CL_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SLOW), this);
			}
			else if((you.s_haste || you.alchemy_buff == ALCT_HASTE) && you.s_slow)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_HASTE_SLOW), CL_magic,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_HASTE_SLOW), this);
			}
			if(you.alchemy_buff == ALCT_STONE_FIST)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_STONEFIST), CL_alchemy,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_STONEFIST), this);
			}
			if(you.alchemy_buff == ALCT_DIAMOND_HARDNESS)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_DIAMOND), CL_alchemy,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_DIAMOND), this);
			}
			if(you.alchemy_buff == ALCT_POISON_BODY)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_POISON_BODY), CL_alchemy,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_POISON_BODY), this);
			}
			if(you.alchemy_buff == ALCT_STONE_FORM)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_ENLIGHTENMENT), CL_alchemy,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_ENLIGHTENMENT), this);
			}
			if(you.alchemy_buff == ALCT_AUTUMN_BLADE)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_AUTUMN_BLADE), CL_alchemy,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_AUTUMN_BLADE), this);
			}
			if(you.alchemy_buff == ALCT_PHILOSOPHERS_STONE)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_PHILOSOPHERS), CL_alchemy,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_PHILOSOPHERS), this);
			}
			if(you.s_unluck > 0)
			{
				if(you.s_unluck <= 3)
				{
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_UNLUCKY1), CL_warning,
						LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_UNLUCKY1), this);
				}
				else if(you.s_unluck <= 6)
				{
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_UNLUCKY2), CL_small_danger,
						LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_UNLUCKY2), this);
				}
				else
				{
					stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_UNLUCKY3), CL_danger,
						LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_UNLUCKY3), this);
				}
			}

		
			{
				int rf_ = you.GetBuffOk(BUFFSTAT_RF);
				int rc_ = you.GetBuffOk(BUFFSTAT_RC);
				int re_ = you.GetBuffOk(BUFFSTAT_RE);
				int rp_ = you.GetBuffOk(BUFFSTAT_RP);
				int rconf_ = you.GetBuffOk(BUFFSTAT_RCONF);
				if(rf_)
				{
					ss.str("");
					ss.clear();
					ss << LocalzationManager::formatString(LOC_SYSTEM_BUFF_RFIRE, PlaceHolderHelper((rf_>0? (rf_>1 ? (rf_>2 ? "+++" : "++") : "+") : (rf_<-1 ? (rf_<-2 ? "---" : "--") : "-")))); 
					stateDraw.addState(ss.str(), rf_>0 ? CL_good : CL_danger,
						(rf_>0 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RFIRE_UP) : LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RFIRE_DOWN)), this);
				}
				if(rc_)
				{
					ss.str("");
					ss.clear();
					ss << LocalzationManager::formatString(LOC_SYSTEM_BUFF_RCOLD, PlaceHolderHelper((rc_>0 ? (rc_>1 ? (rc_>2 ? "+++" : "++") : "+") : (rc_<-1 ? (rc_<-2 ? "---" : "--") : "-")))); 
					stateDraw.addState(ss.str(), rc_>0 ? CL_good : CL_danger,
						(rc_>0 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RCOLD_UP) : LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RCOLD_DOWN)), this);
				}
				if (re_)
				{
					ss.str("");
					ss.clear();
					ss << LocalzationManager::formatString(LOC_SYSTEM_BUFF_RELEC, PlaceHolderHelper((re_>0 ? (re_>1 ? (re_>2 ? "+++" : "++") : "+") : (re_<-1 ? (re_<-2 ? "---" : "--") : "-"))));
					stateDraw.addState(ss.str(), re_>0 ? CL_good : CL_danger,
						(re_>0 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RELEC_UP) : LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RELEC_DOWN)), this);
				}
				if (rp_)
				{
					ss.str("");
					ss.clear();
					ss << LocalzationManager::formatString(LOC_SYSTEM_BUFF_RPOIS, PlaceHolderHelper(rp_>0 ? "+" : "-"));
					stateDraw.addState(ss.str(), rp_>0 ? CL_good : CL_danger,
						(rp_>0 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RPOIS_UP) : LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RPOIS_DOWN)), this);
				}
				if (rconf_)
				{
					ss.str("");
					ss.clear();
					ss << LocalzationManager::formatString(LOC_SYSTEM_BUFF_RCONF, PlaceHolderHelper(rconf_>0 ? "+" : "-"));
					stateDraw.addState(ss.str(), rconf_>0 ? CL_good : CL_danger,
						(rconf_ >0 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RCONF_UP)  : LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_RCONF_DOWN)), this);
				}
			}


			if(you.s_confuse)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_CONFUSE), CL_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_CONFUSE), this);
			}
			if(you.s_frozen)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_FROZEN), you.s_frozen>5 ? CL_blue : CL_bad,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_FROZEN), this);
			}
			if(you.s_elec)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_ELEC), CL_normal,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_ELEC), this);
			}
			if(you.s_paralyse)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_PARALYSE), CL_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_PARALYSE), this);
			}
			if(you.s_levitation)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_LEVITATION), you.s_levitation>10 ? CL_white_blue : CL_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_LEVITATION), this);
			}
			else if(you.s_glow)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_GLOW), CL_white_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_GLOW), this);
			}
			if(you.s_graze && !you.s_super_graze)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_GRAZE), you.s_graze<0 ? CL_normal : you.s_graze>10 ? CL_white_blue : CL_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_GRAZE), this);
			}
			if(you.s_silence)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SILENCE), you.s_silence>5 ? CL_white_blue : CL_blue,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SILENCE), this);
			}
			if(you.s_sick)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SICK), you.s_sick>50 ? (you.s_sick>100 ? CL_danger : CL_small_danger) : CL_warning,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SICK), this);
			}
			if(you.s_veiling)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_VEILING), CL_normal,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_VEILING), this);
			}
			if(you.s_invisible || you.togle_invisible)
			{
				bool glow_ = (you.s_glow || you.GetBuffOk(BUFFSTAT_HALO));
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_INVISIBLE), glow_? CL_bad : (you.togle_invisible ? CL_speak : you.s_invisible>10 ? CL_white_blue : CL_blue),
					glow_? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_INVISIBLE_MEANLESS) : LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_INVISIBLE), this);
			}
			if(you.s_swift)
			{
				stateDraw.addState(you.s_swift>0 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SWIFT) : LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SLUGGISH), you.s_swift>10 ? CL_white_blue : (you.s_swift>0 ? CL_blue : CL_danger),
					you.s_swift > 0 ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SWIFT) : LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SLUGGISH), this);
			}
			if(you.s_superman)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SUPERMAN), you.s_superman>5 ? CL_white_puple : CL_magic,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SUPERMAN), this);
			}
			if(you.s_slaying)
			{
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_BUFF_SLAY) << "(" << (you.s_slaying>0?"+":"") << you.s_slaying<< ")"; 
				
				stateDraw.addState(ss.str(), you.s_slaying>0 ? CL_white_blue : CL_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_SLAY), this);
			}
			if (you.s_none_move)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_NONE_MOVE), CL_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_NONE_MOVE), this);
			}
			if (you.s_night_sight_turn)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_NIGHT_SIGHT), CL_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_NIGHT_SIGHT), this);
			}
			if (you.s_sleep>0)
			{
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_BUFF_SLEEPING) << "(" << std::setfill('0') << std::setw(2) << min(99,you.s_sleep) << ")"; 
			
				stateDraw.addState(ss.str(), CL_small_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_SLEEPING), this);
			}
			else if (you.s_sleep<0)
			{
				stateDraw.addState(LocalzationManager::locString(LOC_SYSTEM_BUFF_STAT_SLEEP), CL_danger,
					LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_STAT_SLEEP), this);
			}
			if (you.s_pure>0 && you.s_pure_turn)
			{
				D3DCOLOR color_ = you.s_pure_turn == -1 ? CL_normal :
					you.s_pure < 10 ? CL_bad :
					you.s_pure < 20 ? CL_darkblue :
					you.s_pure < 30 ? CL_blue : CL_white_blue;

				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_BUFF_JUNKA);
				if(you.s_pure_turn != -1) {
					ss << "(" <<LocalzationManager::formatString(LOC_SYSTEM_LEVEL_WITH_NUMBER, PlaceHolderHelper(to_string(you.s_pure < 10 ? 0 :(you.s_pure <20 ? 1 : (you.s_pure < 30 ? 2 : 3))))) << ")";
				}
				stateDraw.addState(ss.str(), color_,
					((you.s_pure_turn == -1) || you.GetProperty(TPT_PURE_SYSTEM)) ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_JUNKA1) :
					((you.s_pure_turn == -1) || you.s_pure >= 30) ?LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_JUNKA2) :
					(you.s_pure >= 20) ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_JUNKA3) :
					(you.s_pure >= 10) ? LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_JUNKA4) : LocalzationManager::locString(LOC_SYSTEM_BUFF_DESCRIBE_JUNKA0) , this);
			}
		}
	}
	bool already_draw = false;
	//텍스트 클릭용 사전 루프
	if(!text_log.text_list.empty())
	{
		list<text_dummy*>::iterator it;
		it = text_log.text_list.end();
		it--;
		int i = text_log.short_len;
		while(i)
		{
			if(it == text_log.text_list.begin())
				break;
			it--;
			if((*it)->enter)
			{
				i--;
				if(i<=0)
				{
					it++;
					break;
				}
			}
		}
		float x = 0, y = 0;
		for(;it != text_log.text_list.end();)
		{
			if((*it)->clickable > 0) {
				RECT rc2={ (LONG)x, (LONG)y, (LONG)(x+(*it)->width), (LONG)(y+fontDesc.Height)};
				if (MousePoint.x > rc2.left && MousePoint.x <= rc2.right &&
					MousePoint.y > rc2.top && MousePoint.y <= rc2.bottom){
					if(isClicked(LEFT_CLICK)) {
						MSG msg;
						msg.message = WM_CHAR;
						msg.wParam =(*it)->clickable;
						g_keyQueue->push(InputedKey(msg));
					}
					already_draw = true;
				}
			}
			if((*it)->enter)
			{
				x = 0;
				y+=fontDesc.Height;
				it++;
			}
			else
			{
				bool first_ = (x == 0);
				x+=(*it)->width;
				it++;
				if(!first_ && it != text_log.text_list.end() && (x+(*it)->width) > 32*(sight_x*2+1)+16) {
					x = 0;
					y+=fontDesc.Height;
				}
			}
		}
	}
	
	
	

	//바탕 타일 그리기
	int x_ = you.GetDisplayPos().x-sight_x;
	int y_ = you.GetDisplayPos().y-sight_y;
	for(int i=0;i<(sight_x*2+1);i++)
	{
		for(int j=0;j<(sight_y*2+1);j++)
		{
			if(i+x_>=0 && j+y_>=0 && i+x_<DG_MAX_X && j+y_<DG_MAX_Y)
			{
				if((env[current_level].isExplore(i+x_,j+y_) || env[current_level].isMapping(i+x_,j+y_)))
				{	
					bool sight = true;	
					int length_ = (i+x_-you.position.x)*(i+x_-you.position.x)+(j+y_-you.position.y)*(j+y_-you.position.y);
					if(length_<3)
						length_ = 1;
					if(spell_sight)
					{
							
						if(sight_type == 1 && length_ >spell_sight*spell_sight)
							sight = false;
						else if(sight_type == 2 && spell_sight<max(abs(i+x_-you.position.x) ,abs(j+y_-you.position.y)))
						{
							sight = false;
						}
					}
					env[current_level].drawTile(pSprite, i + x_, j + y_, i*32.0f + 20.0f, j*32.0f + 20.0f, 1.0f, you.turn, sight, false, !already_draw);
				}
				if (env[current_level].dgtile[i + x_][j + y_].flag & FLAG_FORBID)
				{
					if (env[current_level].dgtile[i + x_][j + y_].forbid_count2)
						explore_forbid_big.draw(pSprite, i*32.0f + 20.0f, j*32.0f + 20.0f, D3DCOLOR_ARGB(120, 255, 255, 255));
					else if (env[current_level].dgtile[i + x_][j + y_].forbid_count)
						explore_forbid_small.draw(pSprite, i*32.0f + 20.0f, j*32.0f + 20.0f, D3DCOLOR_ARGB(80, 255, 255, 255));
				}
			}
		}
	}
	
	coord_def offset_ = coord_def();
	if(env[current_level].isBamboo())
	{
		offset_.x = DG_MAX_X/2 - you.position.x;
		offset_.y = DG_MAX_Y/2 - you.position.y;
	}
	int dot_start_y = buff_start_y + 2*fontDesc.Height;
	int dot_size = 0;
	int greed_max_x = 10;
	int greed_max_y = 8;
	int max_minimap_y = buff_start_y + 2*fontDesc.Height;

	for(int dot_size_= 1; dot_size_ <=4; dot_size_++) {
		int start_y = option_mg.getHeight() - (32*greed_max_y+10);
		if(start_y > GetDotY(dot_start_y, DG_MAX_Y, sight_y, dot_size_)) {
			dot_size = dot_size_;
			max_minimap_y = GetDotY(dot_start_y, DG_MAX_Y, sight_y, dot_size_);
		}
	}

	//미니맵 그리기
	if(dot_size > 0)
	{
		for(int i=0;i<DG_MAX_X;i++)
		{
			for(int j=0;j<DG_MAX_Y;j++)
			{
				if(env[current_level].isExplore(i,j) || env[current_level].isMapping(i,j))
				{
					switch(env[current_level].dgtile[i][j].GetDot())
					{
					case DOT_FLOOR:
						if(env[current_level].isExplore(i,j))
							dot_floor.draw(pSprite,GetDotX(i+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,j+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
						else
							dot_mapping_floor.draw(pSprite,GetDotX(i+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,j+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
						break;
					case DOT_WALL:
						if(env[current_level].isExplore(i,j))
							dot_wall.draw(pSprite,GetDotX(i+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,j+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
						else
							dot_mapping_wall.draw(pSprite,GetDotX(i+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,j+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
						break;
					case DOT_DOOR:
						dot_door.draw(pSprite,GetDotX(i+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,j+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
						break;
					case DOT_UP:
						dot_up.draw(pSprite,GetDotX(i+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,j+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
						break;
					case DOT_DOWN:
						dot_down.draw(pSprite,GetDotX(i+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,j+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
						break;
					case DOT_TEMPLE:
						dot_temple.draw(pSprite,GetDotX(i+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,j+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
						break;
					case DOT_SEA:
						dot_sea.draw(pSprite,GetDotX(i+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,j+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
						break;
					default:
						break;
					}
				}
			}
		}
	}


	list<item>::iterator floor_items = env[current_level].item_list.end(); 

	//아이템그리기
	{
		list<item>::iterator it; 
		bool many_item = false;
		bool auto_pick_ = false;
		for(it = env[current_level].item_list.begin(); it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++; 
			
			if((*temp).position == you.position && floor_items == env[current_level].item_list.end()) {
				floor_items = temp;
			}
			if(it == env[current_level].item_list.end() || (*temp).position != (*it).position)
			{
				if(env[current_level].isInSight((*temp).position))
				{
					if(abs((*temp).position.x - x_-sight_x)<=sight_x && abs((*temp).position.y - y_-sight_y)<=sight_y)
					{
						if((*temp).isautopick())
							auto_pick_ = true;
						(*temp).draw(pSprite,pfont,((*temp).position.x-x_)*32.0f+20.0f,((*temp).position.y-y_)*32.0f+20.0f);

						if(many_item)
						{
							if(!env[current_level].isMonsterPos((*temp).position.x,(*temp).position.y))
							{
								img_state_wardering.draw(pSprite,((*temp).position.x-x_)*32.0f+20.0f,((*temp).position.y-y_)*32.0f+20.0f,255);
							}
						}
						if(auto_pick_)
						{
							unit* unit_ = env[current_level].isMonsterPos((*temp).position.x, (*temp).position.y);
							if(!unit_ || (!unit_->isView()))
							{
								img_effect_auto_pick.draw(pSprite, ((*temp).position.x - x_)*32.0f + 20.0f, ((*temp).position.y - y_)*32.0f + 20.0f, 255);
							}
						}
					}
					if(dot_size > 0)
						dot_item.draw(pSprite, GetDotX((*temp).position.x + offset_.x,sight_x,dot_size), GetDotY(dot_start_y,(*temp).position.y + offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size, 255);
				}
				many_item = false;
				auto_pick_ = false;
			}
			else
			{
				many_item = true;
				if (it == env[current_level].item_list.end() && (*temp).isautopick())
					auto_pick_ = true;
			}
		}
	}

	//아이템 박스 그리기
	{
		// scale_x = (windowSize.right - windowSize.left) / (float)option_mg.getWidth();
		// scale_y = (windowSize.bottom - windowSize.top) / (float)option_mg.getHeight();
		// infobox.init();
		// {
		// 	int i=0;
		// 	RECT rc={32*(sight_x*2)+50, 10, option_mg.getWidth(), option_mg.getHeight()};
		int start_x = 32*(sight_x*2)+52;
		int start_y = max_minimap_y+16;

		int tile_count = 0;
		auto it = you.item_list.begin();
		for(int j = 0; j < greed_max_y; j++) {
			for(int i = 0; i < greed_max_x; i++) {
				if(tile_count < 20) {
					if(selection_vector.size() > 0) {
						textures* pixel_ = &img_command_empty;
						
						if(selection_vector.size() > tile_count) {
							pixel_ = getSelectTexure(selection_vector[tile_count]);
						}
						int x_ = start_x+i*32, y_ = start_y+j*32;

						pixel_->draw(pSprite,x_,y_,255);
						
						if(pixel_ != &img_command_empty) {
							if (MousePoint.x > x_ - 16 && MousePoint.x <= x_ + 16 &&
								MousePoint.y > y_ - 16 && MousePoint.y <= y_ + 16){
								img_effect_select.draw(pSprite, x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));
								if(isClicked(LEFT_CLICK)) {
									MSG msg;
									msg.message = WM_CHAR;
									msg.wParam = convertClickable(selection_vector[tile_count]);
									g_keyQueue->push(InputedKey(msg));
								}
							}
						}
					} else {					
						//명령어들
						textures* pixel_ = &img_command_empty;
						switch(tile_count) {
							case SYSCMD_AUTOTRAVEL: pixel_ = &img_command_autotravel; break;
							case SYSCMD_AUTOATTACK: pixel_ = &img_command_autoattack; break;
							case SYSCMD_100REST: pixel_ = &img_command_100sleep; break;
							case SYSCMD_MAGIC: pixel_ = &img_command_magic; break;
							case SYSCMD_SKILL: pixel_ = &img_command_skill; break;
							case SYSCMD_SHOUT: pixel_ = &img_command_shout; break;
							case SYSCMD_DOOR_OPENCLOSE: pixel_ = &img_command_door; break;
							case SYSCMD_PRAY: pixel_ = &img_command_pray; break;
							case SYSCMD_MORE_ITEM: pixel_ = &img_command_more_item; break;
							case SYSCMD_AUTOPICKUP: pixel_ = (you.auto_pickup>0?&img_command_pickon:&img_command_pickoff); break;
							case SYSCMD_AUTOTANMAC: pixel_ = (you.useMouseTammac==2?&img_command_tanmac_auto:(you.useMouseTammac==1?&img_command_tanmac_on:&img_command_tanmac_off)); break;
							case SYSCMD_SKILL_VIEW: pixel_ = &img_command_skill_view; break;
							case SYSCMD_MORE_VIEW: pixel_ = &img_command_more_view; break;
							case SYSCMD_HELP: pixel_ = &img_command_help; break;
							case SYSCMD_QUIT: pixel_ = &img_command_quit; break;
							default: break;
						}
						int x_ = start_x+i*32, y_ = start_y+j*32;

						pixel_->draw(pSprite,x_,y_,255);
						if (MousePoint.x > x_ - 16 && MousePoint.x <= x_ + 16 &&
							MousePoint.y > y_ - 16 && MousePoint.y <= y_ + 16){
							img_effect_select.draw(pSprite, x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));
							if(isClicked(LEFT_CLICK)) {
								g_keyQueue->push(InputedKey(MKIND_SYSTEM,tile_count,0));
							}
						}
					}
				}
				else if(tile_count>=20 && tile_count < 72) {
					bool equip_ = false, curse = false, throw_ = false, evokable = false;
					int x_ = start_x+i*32, y_ = start_y+j*32+10;
					if(it != you.item_list.end()) {
						equip_ = (you.isequip(it)>0);
						throw_ = (you.throw_weapon == &(*it));
						curse = it->curse;
						if(it->type == ITM_AMULET && equip_ /* && isCanEvoke((amulet_type)(*it).value1) 발동하지않아도 표시하면 좋을듯*/ && you.getAmuletPercent() >= 100) {
							evokable = true;
						}
					}
					if(equip_) {
						if(evokable) {
							img_item_evokable_itembox.draw(pSprite,x_,y_,255);
						}
						else if(curse) {
							img_item_curse_itembox.draw(pSprite,x_,y_,255);
						} 
						else {
							img_item_equip_itembox.draw(pSprite,x_,y_,255);
						}
					} 
					else if(throw_) {
						img_item_select_itembox.draw(pSprite,x_,y_,255);
					} else {
						img_item_empty_itembox.draw(pSprite,x_,y_,255);
					}
					if(it != you.item_list.end()) {
						it->draw(pSprite,pfont,x_,y_);						
						{ //마우스
							if (MousePoint.x > x_ - 16 && MousePoint.x <= x_ + 16 &&
								MousePoint.y > y_ - 16 && MousePoint.y <= y_ + 16){
								img_effect_select.draw(pSprite, x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));
								if(isClicked(LEFT_CLICK)) {
									g_keyQueue->push(InputedKey(MKIND_ITEM,it->id,0));
								}
								else if(isClicked(RIGHT_CLICK)) {
									g_keyQueue->push(InputedKey(MKIND_ITEM_DESCRIPTION,it->id,0));
								}
							}

						}
						it++;
					}
				} else {
					int x_ = start_x+i*32, y_ = start_y+j*32+10;
					env[current_level].drawTile(pSprite, you.position.x, you.position.y, x_, y_, 1.0f, you.turn, true, true, false);
					if(floor_items != env[current_level].item_list.end()) {
						if(floor_items->position == you.position ) {
							floor_items->draw(pSprite,pfont,x_,y_);
							if (MousePoint.x > x_ - 16 && MousePoint.x <= x_ + 16 &&
								MousePoint.y > y_ - 16 && MousePoint.y <= y_ + 16){
								img_effect_select.draw(pSprite, x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));
								if(isClicked(LEFT_CLICK)) {
									g_keyQueue->push(InputedKey(MKIND_PICK,tile_count-72,0));
								}
								else if(isClicked(RIGHT_CLICK)) {
									g_keyQueue->push(InputedKey(MKIND_PICK_DESCRIPTION,tile_count-72,0));
								}
							}
							floor_items++;
						}
					}
				}
				tile_count++;
			}
		}
	}


	//바닥 효과 그리기
	{
	list<floor_effect>::iterator it;
	for (it = env[current_level].floor_list.begin(); it != env[current_level].floor_list.end(); it++)
	{
		if (env[current_level].isInSight((*it).position)) //더 추가해야할거. 볼수있다(투명아님).
		{
			if (abs((*it).position.x - x_ - sight_x) <= sight_x && abs((*it).position.y - y_ - sight_y) <= sight_y)
			{
				it->draw(pSprite, pfont, ((*it).position.x - x_)*32.0f + 20.0f, ((*it).position.y - y_)*32.0f + 20.0f);
			}
		}
	}
	}

	//연기그리기
	{
		list<smoke>::iterator it;
		for (it = env[current_level].smoke_list.begin(); it != env[current_level].smoke_list.end(); it++)
		{
			if (env[current_level].isInSight((*it).position)) //더 추가해야할거. 볼수있다(투명아님).
			{
				if (abs((*it).position.x - x_ - sight_x) <= sight_x && abs((*it).position.y - y_ - sight_y) <= sight_y)
				{
					it->draw(pSprite, pfont, ((*it).position.x - x_)*32.0f + 20.0f, ((*it).position.y - y_)*32.0f + 20.0f);
				}
			}
		}
	}

	//플레이어 그리기
	{
		if (!you.s_timestep && abs(you.position.x - x_ - sight_x) <= sight_x && abs(you.position.y - y_ - sight_y) <= sight_y)
		{
			you.Draw(pSprite, (you.position.x - x_)*32.0f + 20.0f, (you.position.y - y_)*32.0f + 20.0f);
			if (you.GetHp() != you.GetMaxHp())
			{
				float max_rate_ = (1 / 3.0f);

				int temp1_ = max(0, you.GetHp()) * 32 / you.GetMaxHp();
				float hp_rate_ = (max_rate_ * temp1_);
				int hp_offset_ = (temp1_ + 1) / 2 - 16;


				int temp2_ = max(0, min(you.prev_hp[0], you.GetMaxHp())) * 32 / you.GetMaxHp();
				float p_hp_rate_ = (max_rate_ * temp2_);
				int p_hp_offset_ = (temp2_ + 1) / 2 - 16;

				dot_floor.draw(pSprite, (you.position.x - x_)*32.0f + 20.0f, (you.position.y - y_)*32.0f + 36.0f, 0.0f, max_rate_ * 32.0f, 0.5f, 255);
				dot_monster.draw(pSprite, (you.position.x - x_)*32.0f + 20.0f + p_hp_offset_, (you.position.y - y_)*32.0f + 36.0f, 0.0f, p_hp_rate_, 0.5f, 255);
				dot_item.draw(pSprite, (you.position.x - x_)*32.0f + 20.0f + hp_offset_, (you.position.y - y_)*32.0f + 36.0f, 0.0f, hp_rate_, 0.5f, 255);
			}
			if (!you.pure_mp && you.GetMp() != you.GetMaxMp())
			{
				float max_rate_ = (1 / 3.0f);

				int temp1_ = max(0, you.GetMp()) * 32 / you.GetMaxMp();
				float mp_rate_ = (max_rate_ * temp1_);
				int mp_offset_ = (temp1_ + 1) / 2 - 16;

				dot_floor.draw(pSprite, (you.position.x - x_)*32.0f + 20.0f, (you.position.y - y_)*32.0f + 38.0f, 0.0f, max_rate_ * 32.0f, 0.5f, 255);
				dot_up.draw(pSprite, (you.position.x - x_)*32.0f + 20.0f + mp_offset_, (you.position.y - y_)*32.0f + 38.0f, 0.0f, mp_rate_, 0.5f, 255);
			}

		}
		if(dot_size > 0)
			dot_player.draw(pSprite, GetDotX(you.position.x + offset_.x,sight_x,dot_size), GetDotY(dot_start_y,you.position.y + offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size, 255);
	}


	//몹그리기
	{
		vector<monster>::iterator it;

		for (it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if ((*it).isLive() && (*it).isYourShight()) //더 추가해야할거. 볼수있다(투명아님).
			{
				if (abs((*it).position.x - x_ - sight_x) <= sight_x && abs((*it).position.y - y_ - sight_y) <= sight_y)
				{
					(*it).draw(pSprite, pfont, ((*it).position.x - x_)*32.0f + 20.0f, ((*it).position.y - y_)*32.0f + 20.0f);
				}
				if (!((*it).flag & M_FLAG_UNHARM))
				{
					if(dot_size > 0) {
						dot_monster.draw(pSprite, GetDotX((*it).position.x + offset_.x,sight_x,dot_size), GetDotY(dot_start_y,(*it).position.y + offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size, 255);
					}
				}
			}
			else if(it->isLive() &&	you.god == GT_SATORI && !you.GetPunish(GT_SATORI) && pietyLevel(you.piety)>=3
				&& GetPositionGap((*it).position.x, (*it).position.y, you.position.x, you.position.y) <= satori_sight()
				)
			{
				if(abs((*it).position.x -x_-sight_x)<=sight_x && abs((*it).position.y -y_-sight_y)<=sight_y)
				{
					(*it).simple_draw(pSprite,pfont,((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f+20.0f);
				}
				if (!((*it).flag & M_FLAG_UNHARM))
				{
					if(dot_size > 0) {
						dot_monster.draw(pSprite, GetDotX((*it).position.x + offset_.x,sight_x,dot_size), GetDotY(dot_start_y,(*it).position.y + offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size, 255);
					}
				}
			}
		}
	}
	//그림자 그리기
	{
		list<shadow>::iterator it;
		
		for(it = env[current_level].shadow_list.begin(); it != env[current_level].shadow_list.end(); it++)
		{
			if(abs((*it).position.x -x_-sight_x)<=sight_x && abs((*it).position.y -y_-sight_y)<=sight_y)
			{
				if(!env[current_level].isInSight((*it).position)) 
				{
					(*it).image->draw(pSprite,((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f+20.0f,D3DCOLOR_XRGB(128,128,128));
				}
			}
			if(dot_size > 0) {
				switch((*it).type)
				{
				case SWT_MONSTER:
					if (!(*it).unharm) {
						dot_monster.draw(pSprite, GetDotX((*it).position.x + offset_.x,sight_x,dot_size), GetDotY(dot_start_y,(*it).position.y + offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size, 255);
					}
					break;
				case SWT_ITEM:
					dot_item.draw(pSprite,GetDotX((*it).position.x+offset_.x,sight_x,dot_size),GetDotY(dot_start_y,(*it).position.y+offset_.y,sight_y,dot_size),0.0f,(float)dot_size,(float)dot_size,255);
					break;
				}
			}
		}
	}

	//안개그리기
	if(you.s_weather >= 1 && you.s_weather_turn > 0)
	{
		for (int i = 0; i < (sight_x*2+1); i++)
		{
			for (int j = 0; j < (sight_y*2+1); j++)
			{
				if (i + x_ >= 0 && j + y_ >= 0 && i + x_ < DG_MAX_X && j + y_ < DG_MAX_Y)
				{
					if (env[current_level].isSight(coord_def(i + x_, j + y_)) && env[current_level].isInSight(coord_def(i + x_, j + y_)))
					{
						switch (you.s_weather) {
						case 1:
							img_effect_fog.draw(pSprite, i*32.0f + 20.0f, j*32.0f + 20.0f, D3DCOLOR_ARGB(100, 255, 255, 255));
							break;
						case 2:
							img_effect_rain.draw(pSprite, i*32.0f + 20.0f, j*32.0f + 20.0f, D3DCOLOR_ARGB(50, 255, 255, 255));
							break;
						case 3:
							img_effect_sun.draw(pSprite, i*32.0f + 20.0f, j*32.0f + 20.0f, D3DCOLOR_ARGB(20, 255, 255, 255));
							break;
						}

					}
				}
			}
		}
	}

	//이펙트그리기
	{
		list<effect>::iterator it;		
		for(it = env[current_level].effect_list.begin(); it != env[current_level].effect_list.end(); it++)
		{
			if((*it).over_sight || env[current_level].isInSight((*it).position))
			{
				if(abs((*it).position.x -x_-sight_x)<=sight_x && abs((*it).position.y -y_-sight_y)<=sight_y)
				{
					(*it).image->draw(pSprite,((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f+20.0f, 255);
				}
			}
		}
	}

	if(you.search)
	{
		img_effect_select.draw(pSprite,(you.search_pos.x-x_)*32.0f+20.0f,(you.search_pos.y-y_)*32.0f+20.0f,D3DCOLOR_XRGB(255,255,255));
	}

	{ //테두리
		if(!env[current_level].isBamboo() && dot_size > 0) {
			sight_rect.draw(pSprite,GetDotX(x_+sight_x,sight_x,dot_size),GetDotY(dot_start_y,y_+sight_y,sight_y,dot_size),0.0f,sight_x/24.0f*dot_size,sight_y/24.0f*dot_size,255);
		}
	}




	//광기
	if(you.s_sleep < 0 || you.s_lunatic || map_effect || you.s_evoke_ghost)
	{
		int x_ = you.GetDisplayPos().x-sight_x;
		int y_ = you.GetDisplayPos().y-sight_y;
		for(int i=0;i<(sight_x*2+1);i++)
		{
			for(int j=0;j<(sight_y*2+1);j++)
			{
				if(i+x_>=0 && j+y_>=0 && i+x_<DG_MAX_X && j+y_<DG_MAX_Y)
				{
					if((env[current_level].isExplore(i+x_,j+y_) || env[current_level].isMapping(i+x_,j+y_)))
					{					
						//if(!env[current_level].isExplore(i+x_,j+y_))
						if(map_effect==1)
							img_effect_freeze.draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,80);
						else if (you.s_sleep < 0)
							img_effect_sleep.draw(pSprite, i*32.0f + 20.0f, j*32.0f + 20.0f, 100);
						else if(you.s_lunatic)
							img_effect_lunatic.draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,80);
						else if(map_effect==2)
							img_effect_gold.draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,80);
						else if (map_effect == 3)
							img_effect_sion.draw(pSprite, i*32.0f + 20.0f, j*32.0f + 20.0f, 80);
						else if (you.s_evoke_ghost)
							img_effect_white.draw(pSprite, i*32.0f + 20.0f, j*32.0f + 20.0f, D3DCOLOR_ARGB(80, 80, 0, 100));
							//env[current_level].dgtile[i+x_][j+y_].draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,D3DCOLOR_XRGB(160,160,255));
					}
				}
			}
		}
	}




	//네임드 이름만 그리기
	{
		vector<monster>::iterator it;
		for (it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if ((*it).isLive() && (*it).isYourShight() && ((*it).isUnique() || (*it).image == &img_mons_default)) //더 추가해야할거. 볼수있다(투명아님).
			{
				if (abs((*it).position.x - x_ - sight_x) <= sight_x && abs((*it).position.y - y_ - sight_y) <= sight_y)
				{
					RECT rc = { (LONG)(((*it).position.x - x_)*32.0f + 20.0f),(LONG)(((*it).position.y - y_)*32.0f - 10.0f), (LONG)option_mg.getWidth(), (LONG)option_mg.getHeight() };
					rc.left -= fontDesc.Width*(*it).GetName()->getName().size() / 2;
					DrawTextUTF8(pfont,pSprite, (*it).GetName()->getName().c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
				}
			}
		}
	}

	//텍스트(위쪽에 숏로그)그리기
	if(!text_log.text_list.empty())
	{
		list<text_dummy*>::iterator it;
		it = text_log.text_list.end();
		it--;
		int i = text_log.short_len;
		while(i)
		{
			if(it == text_log.text_list.begin())
				break;
			it--;
			if((*it)->enter)
			{
				i--;
				if(i<=0)
				{
					it++;
					break;
				}
			}
		}
		float x = 0, y = 0;
		for(;it != text_log.text_list.end();)
		{			
			RECT rc={ (LONG)x, (LONG)y, 32*(sight_x*2+1)+16, (LONG)(y+fontDesc.Height)};
			DrawTextUTF8(pfont,pSprite, (*it)->text.c_str(), -1, &rc, DT_SINGLELINE , (*it)->color);
			if((*it)->clickable > 0) {
				RECT rc2={ (LONG)x, (LONG)y, (LONG)(x+(*it)->width), (LONG)(y+fontDesc.Height)};
				if (MousePoint.x > rc2.left && MousePoint.x <= rc2.right &&
					MousePoint.y > rc2.top && MousePoint.y <= rc2.bottom){
					DrawRectOutline(pSprite, rc2, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
				}
			}
			if((*it)->enter)
			{
				x = 0;
				y+=fontDesc.Height;
				it++;
			}
			else
			{
				bool first_ = (x == 0);
				x+=(*it)->width;
				it++;
				if(!first_ && it != text_log.text_list.end() && (x+(*it)->width) > 32*(sight_x*2+1)+16) {
					x = 0;
					y+=fontDesc.Height;
				}
			}
		}
	}


	if(ReplayClass.play)
	{
		RECT rc={50, 400, option_mg.getWidth(), option_mg.getHeight()};
		DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(LOC_SYSTEM_REPLAYING), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
		rc.top += fontDesc.Height;	
		DrawTextUTF8(pfont,pSprite,LocalzationManager::formatString(LOC_SYSTEM_REPLAY_KEY_HELP, PlaceHolderHelper("z"), PlaceHolderHelper("x"), PlaceHolderHelper("c")), -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
	}
	drawInfoBox(pSprite, pfont);

}
extern POINT MousePoint;

void stateBox::addState(string name, D3DCOLOR color, string info, display_manager* display)
{
	int sizeOfName = PrintCharWidth(name);
	if (current + (sizeOfName + 1) > width)
	{
		enter(display);
	}
	DrawTextUTF8(pfont,pSprite, name, -1, &rc, DT_SINGLELINE | DT_NOCLIP, color);
	display->CheckMouseInfo(pSprite, pfont, rc, display->fontDesc.Width * sizeOfName, display->fontDesc.Height, info);
	rc.left += display->fontDesc.Width * (sizeOfName+1);
	current += (sizeOfName + 1);
}
void stateBox::enter(display_manager* display)
{
	rc.left = start_rc.left;
	rc.top += display->fontDesc.Height;
	current = 0;
}
void display_manager::CheckMouseInfo(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont, RECT& rc, int width_, int height_, string message)
{
	if (MousePoint.x >= rc.left*scale_x && MousePoint.x <= (rc.left + width_)*scale_x &&
		MousePoint.y >= rc.top*scale_y && MousePoint.y <= (rc.top + height_)*scale_y
		)

	{
		infobox.setBox(MousePoint.x/ scale_x, MousePoint.y/ scale_y, message);
	}
}
void display_manager::drawInfoBox(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	if (infobox.draw)
	{
		RECT rc_ = { infobox.x, infobox.y, infobox.x + infobox.x_size, infobox.y + infobox.y_size };
		if (rc_.left + infobox.x_size / 2  > option_mg.getWidth()) {
			int i = rc_.left + infobox.x_size / 2 - option_mg.getWidth();
			rc_.left -= i;
			rc_.right -= i;
		}


		dot_floor.draw(pSprite, (float)rc_.left, (float)rc_.top, 0.0f, infobox.x_size / 3.0f, infobox.y_size / 3.0f, D3DCOLOR_ARGB(200, 255, 255, 255));
		rc_.left -= infobox.x_size / 2 - infobox.x_comma;
		rc_.top -= infobox.y_size / 2 - infobox.y_comma;
		rc_.right -= infobox.x_size / 2 + infobox.x_comma;
		rc_.bottom -= infobox.y_size / 2 + infobox.y_comma;
		DrawTextUTF8(pfont,pSprite, infobox.info.c_str(), -1, &rc_, DT_WORDBREAK, CL_none);
	}
}
void display_manager::item_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	RECT rc={30, 10-move, option_mg.getWidth(), option_mg.getHeight()};
	string s;
	switch(item_vt)
	{
	case IVT_INFOR:
	case IVT_DISCARD:
	case IVT_SELECT:
	case IVT_EQ_WEAPON:
	case IVT_EQ_ARMOR:
	case IVT_UEQ_ARMOR:
	case IVT_FOOD:
	case IVT_POTION:
	case IVT_SCROLL:
	case IVT_EQ_JEWELRY:
	case IVT_UEQ_JEWELRY:
	case IVT_UNIDEN:
	case IVT_THROW:
	case IVT_ARMOR:
	case IVT_ARMOR_ENCHANT:
	case IVT_SPELLCARD:
	case IVT_EVOKE:
	case IVT_CURSE_ENCHANT:
	{
    	std::ostringstream oss;
		oss << "<"<< LocalzationManager::locString(LOC_SYSTEM_INVENTORY) <<">  (" << LocalzationManager::locString(LOC_SYSTEM_INVENTORY_ITEM) <<" " << you.item_list.size() << " / 52)";
		DrawTextUTF8(pfont,pSprite,oss.str().c_str(), -1, &rc, DT_NOCLIP,CL_normal);
		rc.top += fontDesc.Height;
		break;
	}
	default:
		break;
	}
	
	DrawTextUTF8(pfont,pSprite,LocalzationManager::locString(item_view_message).c_str(), -1, &rc, DT_NOCLIP,CL_normal);
	rc.top += fontDesc.Height*2;
	rc.left += 32;

	list<item>::iterator first,end; //여기서 아이템반복자의 시작과 끝을 결정해준다. 좀 무식함
	int error_ = false;
	switch(item_vt)
	{
	case IVT_INFOR:
	case IVT_DISCARD:
	case IVT_SELECT:
	case IVT_EQ_WEAPON:
	case IVT_EQ_ARMOR:
	case IVT_UEQ_ARMOR:
	case IVT_FOOD:
	case IVT_POTION:
	case IVT_SCROLL:
	case IVT_EQ_JEWELRY:
	case IVT_UEQ_JEWELRY:
	case IVT_UNIDEN:
	case IVT_THROW:
	case IVT_ARMOR:
	case IVT_ARMOR_ENCHANT:
	case IVT_PURE_ITEM:
	case IVT_SPELLCARD:
	case IVT_EVOKE:
	case IVT_CURSE_ENCHANT:
		first = you.item_list.begin();
		end = you.item_list.end();
		break;
	case IVT_PICK:
		{
			bool s = false;
			char id_='a';
			list<item>::iterator temp;
			for(temp = env[current_level].item_list.begin();temp != env[current_level].item_list.end();temp++)
			{
				if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
				{
					if(!s)
					{
						first = temp;
						s = true;
					}
					(*temp).id = id_;
					id_++;
					if(id_ == 'Z'+1)
						id_ = 'a';
					if(id_ == 'z'+1)
						id_ = 'A';
				}
				else if(s)
					break;
			}
			if(!s)
				error_ = true;
			end = temp;
			break;
		}
	default:
		return;
		break;
	}

	for(item_type_simple i = ITMS_FIRST ; !error_ && i != ITMS_LAST ; i=(item_type_simple)(i+1))
	{
		if(((item_vt == IVT_EQ_WEAPON)&& i != ITMS_WEAPON) ||
			((item_vt == IVT_EQ_ARMOR || item_vt == IVT_UEQ_ARMOR || item_vt == IVT_ARMOR || item_vt == IVT_ARMOR_ENCHANT)  && i != ITMS_ARMOR)
			)
			continue;
		if(item_vt == IVT_PURE_ITEM && (i != ITMS_WEAPON && i != ITMS_ARMOR))
			continue;
		if(item_vt == IVT_FOOD && i != ITMS_FOOD)
			continue;
		if(item_vt == IVT_POTION && i != ITMS_POTION)
			continue;
		if(item_vt == IVT_SCROLL && i != ITMS_SCROLL && i != ITMS_BOOK)
			continue;
		if( (item_vt == IVT_EQ_JEWELRY || item_vt == IVT_UEQ_JEWELRY ) && i != ITMS_JEWELRY)
			continue;
		if (item_vt == IVT_SPELLCARD && i != ITMS_SPELL) {
			continue;
		}
		if(item_vt == IVT_EVOKE && i != ITMS_SPELL && i != ITMS_MISCELLANEOUS && i != ITMS_JEWELRY)
			continue;
		if(item_vt == IVT_CURSE_ENCHANT && (i != ITMS_WEAPON && i != ITMS_ARMOR))
			continue;


		bool exist = false;
		list<item>::iterator it;
		for(it = first; it!=end;it++)
		{
			if((*it).isSimpleType(i))
			{
				int equip = you.isequip(it);
				if(item_vt == IVT_UEQ_ARMOR && !equip)
					continue;
				if(item_vt == IVT_UEQ_JEWELRY && !equip)
					continue;
				if(item_vt == IVT_UNIDEN && (*it).isiden())
					continue;
				if(item_vt == IVT_THROW && !(*it).can_throw)
					continue;
				if(item_vt == IVT_SPELLCARD && !(*it).isChargable())
					continue;				
				if(item_vt == IVT_ARMOR_ENCHANT && !(*it).isEnhantable())
					continue;				
				if (item_vt == IVT_CURSE_ENCHANT && (!(it->curse) || !(it->identify_curse)))
					continue;
				if (item_vt == IVT_EVOKE && !(*it).isEvokable())
					continue;


				if(!exist)
				{
					rc.top += 16;
					rc.left -= 48;
					DrawTextUTF8(pfont,pSprite,GetItemTypeSting(i).c_str(), -1, &rc, DT_NOCLIP,CL_help);
					rc.top += 32;
					rc.left += 48;
					exist = true;
				}

				


				string temp;
				temp+=(*it).id;
				temp+=item_view[asctonum((*it).id)]?(item_num[asctonum((*it).id)]?" # ":" + "):" - ";
				temp+=(*it).GetName().c_str();
				if(equip)
					temp += (equip==1?("(" + LocalzationManager::locString(LOC_SYSTEM_EQUIP) + ")"):
					(equip==2?("(" + LocalzationManager::locString(LOC_SYSTEM_LEFT_HAND) + ")"):
					("(" + LocalzationManager::locString(LOC_SYSTEM_RIGHT_HAND) + ")")));
				it->draw(pSprite, pfont, rc.left - 24, rc.top + 8);
				//(*it).image->draw(pSprite,rc.left-24,rc.top+8,D3DCOLOR_XRGB(255,255,255));
				DrawTextUTF8(pfont,pSprite,temp.c_str(), -1, &rc, DT_NOCLIP,(*it).item_color());

				RECT rc2={ rc.left - 40, rc.top - 8, (LONG)(rc.left+PrintCharWidth(temp)*fontDesc.Width)+8,  rc.top + 24};
				if (MousePoint.x > rc2.left && MousePoint.x <= rc2.right &&
					MousePoint.y > rc2.top && MousePoint.y <= rc2.bottom){
					DrawRectOutline(pSprite, rc2, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
					
					if(isClicked(LEFT_CLICK)) {						
						MSG msg;
						msg.message = WM_CHAR;
						msg.wParam = convertClickable((*it).id);
						g_keyQueue->push(InputedKey(msg));
					}
					else if(isClicked(RIGHT_CLICK)) {
						g_keyQueue->push(InputedKey(MKIND_ITEM_DESCRIPTION,(*it).id,0));
					}
				}
				rc.top += 32;
			}
		}
	}
	rc.top+=move+64;
	max_y = (rc.top-option_mg.getHeight()>0?rc.top-option_mg.getHeight():0);
	if(isClicked(LEFT_CLICK)) {
		MSG msg;
		msg.message = WM_CHAR;
		msg.wParam = convertClickable(VK_RETURN);
		g_keyQueue->push(InputedKey(msg));
	}
	else if(isClicked(MIDDLE_UP)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_UP,0,0));
	} else if(isClicked(MIDDLE_DOWN)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_DOWN,0,0));
	}
}

void display_manager::log_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	//텍스트(위쪽에 숏로그)그리기
	if(!text_log.text_list.empty())
	{
		list<text_dummy*>::iterator it;
		it = text_log.text_list.end();
		it--;
		int view_length = log_length;
		int i = view_length+(move>0?move:0);
		while(i)
		{
			if(it == text_log.text_list.begin())
				break;
			it--;
			if((*it)->enter)
			{
				i--;
				if(i<=0)
				{
					it++;
					break;
				}
			}
		}
		float x = 0, y = 0;
		for(i = 0;i < view_length && it != text_log.text_list.end();)
		{
			int max_length = option_mg.getWidth();
			RECT rc={ (LONG)x, (LONG)y, (LONG)(x+(*it)->text.length()*fontDesc.Width), (LONG)(y+fontDesc.Height)};
			DrawTextUTF8(pfont,pSprite, (*it)->text.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, (*it)->color);
			if((*it)->enter)
			{
				x = 0;
				y+=fontDesc.Height;
				i++;
				it++;
			}
			else
			{
				bool first_ = (x == 0);
				x+=(*it)->width;
				it++;
				if(!first_  && it != text_log.text_list.end() && (x+(*it)->width) > max_length) {
					x = 0;
					y+=fontDesc.Height;
				}
			}
		}
	}
	
	if(isClicked(MIDDLE_UP)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_UP,0,0));
	} else if(isClicked(MIDDLE_DOWN)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_DOWN,0,0));
	}
}

void display_manager::sub_text_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont)
{
	if (image)
		image->draw(pSprite, 255);
	//텍스트(위쪽에 숏로그)그리기
	if(!text_sub.text_list.empty())
	{
		list<text_dummy*>::iterator it;
		it = text_sub.text_list.end();
		it--;
		int view_length = log_length;
		int i = view_length+(move>0?move:0);
		while(i)
		{
			if(it == text_sub.text_list.begin())
				break;
			it--;
			if((*it)->enter)
			{
				i--;
				if(i<=0)
				{
					it++;
					break;
				}
			}
		}
		float x = 0, y = 0;
		for(i = 0;i < view_length && it != text_sub.text_list.end();it++)
		{			
			RECT rc={ (LONG)x, (LONG)y, (LONG)(x+(*it)->width), (LONG)(y+fontDesc.Height)};
			DrawTextUTF8(pfont,pSprite, (*it)->text.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, (*it)->color);
			
			if((*it)->clickable > 0) {				
				if (MousePoint.x > rc.left && MousePoint.x <= rc.right &&
					MousePoint.y > rc.top && MousePoint.y <= rc.bottom){
					DrawRectOutline(pSprite, rc, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
					if(isClicked(LEFT_CLICK)) {
						MSG msg;
						msg.message = WM_CHAR;
						msg.wParam = (*it)->clickable;
						g_keyQueue->push(InputedKey(msg));
					} else if(isClicked(RIGHT_CLICK)) {
						g_keyQueue->push(InputedKey(MKIND_ITEM_DESCRIPTION,(*it)->clickable,0));
					}
				}
			}
			
			
			if((*it)->enter)
			{
				x = 0;
				y+=fontDesc.Height;
				i++;
			}
			else
			{
				x+=(*it)->width;
			}
		}
	}
	
	if(isClicked(MIDDLE_UP)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_UP,0,0));
	} else if(isClicked(MIDDLE_DOWN)) {
		g_keyQueue->push(InputedKey(MKIND_SCROLL_DOWN,0,0));
	} else if (isClicked(RIGHT_CLICK)) {
		MSG msg;
		msg.message = WM_CHAR;
		msg.wParam = VK_ESCAPE;
		g_keyQueue->push(InputedKey(msg));
	} 
}

void display_manager::start_spellview(LOCALIZATION_ENUM_KEY message_)
{
	WaitForSingleObject(mutx, INFINITE);
	state = DT_SPELL;
	move = 0;
	item_view_message = message_;
	ReleaseMutex(mutx);
}

void display_manager::start_skillview(LOCALIZATION_ENUM_KEY message_)
{
	WaitForSingleObject(mutx, INFINITE);
	state = DT_SKILL;
	move = 0;
	item_view_message = message_;
	ReleaseMutex(mutx);
}


void display_manager::start_itemview(item_view_type type, LOCALIZATION_ENUM_KEY message_)
{
	WaitForSingleObject(mutx, INFINITE);
	for(int i=0;i<52;i++)
		item_view[i] = 0;
	for(int i=0;i<52;i++)
		item_num[i] = 0;
	state = DT_ITEM;
	move= 0;
	item_vt = type;
	item_view_message = message_;
	ReleaseMutex(mutx);
}

bool display_manager::DrawRectOutline(std::shared_ptr<DirectX::SpriteBatch> spriteBatch, const RECT& rc, int thickness, D3DCOLOR color){
    if (!spriteBatch) return false;

    float left   = (float)rc.left;
    float right  = (float)rc.right;
    float top    = (float)rc.top;
    float bottom = (float)rc.bottom;
    float width  = right - left;
    float height = bottom - top;

    dot_player.draw(spriteBatch, left, top, 0.0f, width, (float)thickness, color);
    dot_player.draw(spriteBatch, left, bottom, 0.0f, width+1, (float)thickness, color);
    dot_player.draw(spriteBatch, left, top, 0.0f, (float)thickness, height, color);
    dot_player.draw(spriteBatch, right, top, 0.0f, (float)thickness, height+1, color);

    return true;
}



void changedisplay(display_type set)
{
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.state = set;
	DisplayManager.move = 0;
	if(set == DT_LOG)
		DisplayManager.max_y = DisplayManager.text_log.length-DisplayManager.log_length;
	else if(set == DT_SUB_TEXT)
		DisplayManager.max_y = DisplayManager.text_sub.length-DisplayManager.log_length;		
	else if(set == DT_SKILL)
		DisplayManager.max_y = 2;
	else
		DisplayManager.max_y = 0;
	ReleaseMutex(mutx);
}

int getDisplayMove()
{
	return DisplayManager.move;
}

void setDisplayMove(int move_)
{
	DisplayManager.move = move_;
}


void changemove(int var)
{
	WaitForSingleObject(mutx, INFINITE);
	switch(DisplayManager.state)
	{
		case DT_TEXT:
			DisplayManager.move = CutSelect(0, DisplayManager.max_y, DisplayManager.move+var);
			break;
		case DT_LOG:
		case DT_SUB_TEXT:
		case DT_ITEM:
		case DT_SKILL:
		case DT_IDEN:
			DisplayManager.move = CutSelect(0, DisplayManager.max_y, DisplayManager.move+var);
			break;
		case DT_SKILL_USE:
			DisplayManager.move = DisplayManager.move?0:1;
			break;
		default:
			break;
	}
	ReleaseMutex(mutx);
}

int GetDisplayMove()
{
	return DisplayManager.move;
}
void view_item(item_view_type type, LOCALIZATION_ENUM_KEY message_)
{
	DisplayManager.start_itemview(type, message_);
}
void rollback_item(item_view_type type, LOCALIZATION_ENUM_KEY message_)
{
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.state = DT_ITEM;
	DisplayManager.move= 0;
	DisplayManager.item_vt = type;
	DisplayManager.item_view_message = message_;
	ReleaseMutex(mutx);
}
void view_spell(LOCALIZATION_ENUM_KEY message_)
{
	DisplayManager.start_spellview(message_);
}
void view_skill(LOCALIZATION_ENUM_KEY message_)
{
	DisplayManager.start_skillview(message_);
}

void CheckKey(char key_, int num_)
{
	int i = asctonum(key_);
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.item_view[i] = DisplayManager.item_view[i]?0:1;
	DisplayManager.item_num[i] =  DisplayManager.item_view[i]?num_:0;
	ReleaseMutex(mutx);
	return;
}
void AllCheckKey()
{
	WaitForSingleObject(mutx, INFINITE);
	for(int i=0;i<52;i++)
		DisplayManager.item_view[i] = DisplayManager.item_view[i]?0:1;
	for(int i=0;i<52;i++)
		DisplayManager.item_num[i] =  0;
	ReleaseMutex(mutx);
	return;
}
bool GetItemofKey(list<item>::iterator it,list<item>::iterator it2)
{
	if(it == it2)
		return false;
	return DisplayManager.item_view[asctonum((*it).id)]?true:false;
}
int GetItemofNum(list<item>::iterator it,list<item>::iterator it2)
{
	if(it == it2)
		return false;
	return DisplayManager.item_num[asctonum((*it).id)];
}
list<item>::iterator GetKeytoItem(char key_)
{
	list<item>::iterator it = you.item_list.begin();
	for(;it!= you.item_list.end();it++)
	{
		if((*it).id == key_)
			break;
	}
	return it;
}


void SetDisplayTexture(textures *texture_)
{
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.image = texture_;
	ReleaseMutex(mutx);
}