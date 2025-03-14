﻿//////////////////////////////////////////////////////////////////////////////////////////////////
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

extern IDirect3DDevice9* Device; //디바이스포인터
extern IDirect3DVertexBuffer9* g_pVB; //버텍스버퍼포인터
extern D3DXMATRIXA16 g_BaseMatrix; //매트릭스포인터
extern LPD3DXSPRITE g_pSprite; //스프라이트포인터 
extern ID3DXFont* g_pfont;
extern HANDLE mutx;
extern HWND hwnd;

display_manager DisplayManager;

DWORD FrameCnt = 0;
float TimeElapsed = 0;
float FPS = 0;

extern bool widesearch; //X커맨드용


int map_effect=0;//잠깐 나오는 맵의 반짝 이벤트





void text_dummy::calculateWitdh() {
	RECT rc={ (LONG)0, (LONG)0, 32*17+16, (LONG)(DisplayManager.fontDesc.Height)};
	g_pfont->DrawTextW(g_pSprite, PreserveTrailingSpaces(text).c_str(), -1, &rc, DT_SINGLELINE | DT_CALCRECT, color);
	width = rc.right;
}

infoBox::infoBox() 
{
	x_size = 240;
	y_size = 80;
	x_comma = 10;
	y_comma = 10;
	draw = false;

}	
stateBox::stateBox(LPD3DXSPRITE pSprite_, ID3DXFont* pfont_, RECT start_rc_):
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

bool Display(float timeDelta)
{
	WaitForSingleObject(mutx, INFINITE);
	CalcFPS(timeDelta);
	if( Device ) 
	{
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
		if(SUCCEEDED(Device->BeginScene())){
			
			g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	
			//ddd
			DisplayManager.draw(g_pSprite, g_pfont);

			g_pSprite->End();

			Device->EndScene();
		}
		Device->Present(0, 0, 0, 0);
	}
	
	ReleaseMutex(mutx);
	return true;
}


display_manager::display_manager():tile_type(0),text_log(),text_sub(),state(DT_TEXT),item_view(), item_vt(IVT_INFOR),
item_view_message("무슨 아이템을 고르겠습니까?"), image(NULL), log_length(1), move(0), max_y(1), sight_type(0), 
spell_sight(0), scale_x(0), scale_y(0)
{
	for(int i=0;i<52;i++)
		item_view[i] = 0;
}
void display_manager::Getfontinfor()
{
	g_pfont->GetDesc(&fontDesc);
	log_length = (option_mg.getHeight()-50) / fontDesc.Height;
}
void display_manager::draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
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
}


int DrawTextUTF8(ID3DXFont* pFont, LPD3DXSPRITE pSprite, LPCWSTR text, int count, LPRECT pRect, DWORD format, D3DCOLOR color) {
    if (!pFont || !text || !pRect) {
        return 0;
    }

    return pFont->DrawTextW(pSprite, text, count, pRect, format, color);
}

int DrawTextUTF8(ID3DXFont* pFont, LPD3DXSPRITE pSprite, const char* text, int count, LPRECT pRect, DWORD format, D3DCOLOR color) {
    if (!pFont || !text || !pRect) {
        return 0;
    }

    // UTF-8 문자열을 UTF-16으로 변환
    std::wstring utf16Text = ConvertUTF8ToUTF16(text);
    if (utf16Text.empty()) {
        return 0;
    }

    // DrawTextW 함수 호출
    return pFont->DrawTextW(pSprite, utf16Text.c_str(), count, pRect, format, color);
}



void display_manager::text_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	if(image)
		image->draw(pSprite,255);
	RECT rc={50, 50-move, option_mg.getWidth(), option_mg.getHeight()};
	DrawTextUTF8(pfont, pSprite, text.c_str(), -1, &rc, DT_NOCLIP,D3DCOLOR_XRGB(200,200,200));
}

void display_manager::spell_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{	
	int i=0;
	RECT rc={50, 50, option_mg.getWidth(), option_mg.getHeight()};
	char temp[100];
	char sp_char = (i<27)?('a'+i):('A'+i-27);
	
	DrawTextUTF8(pfont,pSprite,item_view_message.c_str(), -1, &rc, DT_NOCLIP,CL_normal);
	rc.top += fontDesc.Height*2;


	DrawTextUTF8(pfont,pSprite,"단축키 - 이름", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 200;
	DrawTextUTF8(pfont,pSprite,"학파", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 200;
	DrawTextUTF8(pfont,pSprite,"실패율", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 150;
	DrawTextUTF8(pfont,pSprite,"레벨", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += fontDesc.Height;
	rc.left = 50;
	for(int i=0;i<52;i++)
	{
		if(you.MemorizeSpell[i])
		{
			spell_list spell_ = (spell_list)you.MemorizeSpell[i];
			int miscast_level_ = SpellMiscastingLevel(SpellLevel(spell_), 100-you.GetSpellSuccess(spell_));
			D3DCOLOR spell_color_ = (miscast_level_==3?CL_danger:
				(miscast_level_==2?CL_small_danger:
				(miscast_level_==1?CL_warning:CL_STAT)));

			char sp_char = (i<26)?('a'+i):('A'+i-26);
			sprintf_s(temp,100,"%c      - %s",sp_char,SpellString(spell_));
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, spell_color_);
			rc.left += 200;
			DrawTextUTF8(pfont,pSprite,GetSpellSchoolString(spell_).c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, spell_color_);
			rc.left = 450;
			sprintf_s(temp,100,"%-3d%%",100-you.GetSpellSuccess(spell_));
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, spell_color_);
			rc.left += 150;
			sprintf_s(temp,100,"%d",SpellLevel(spell_));
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, spell_color_);
			rc.top += fontDesc.Height;
			rc.left = 50;


		}
	}
}
void display_manager::iden_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	int num = 0;
	RECT rc = { 30, 10 - move, option_mg.getWidth(), option_mg.getHeight() };
	char temp[100];
	int one_ = 50, two_ = 100;

	DrawTextUTF8(pfont,pSprite, "식별된 아이템 & 자동 줍기 설정", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += 2* fontDesc.Height;

	bool first_ = false;
	for (int i = IDEN_CHECK_START; i < IDEN_CHECK_END; i++) {
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
					sprintf_s(temp, 100, "<물약>");
					DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				img_item_potion[iden_list.potion_list[cur_].color].draw(pSprite, rc.left-24, rc.top+6, 255);
				img_item_potion_kind[min(PT_MAX - 1, max(0, cur_))].draw(pSprite, rc.left-24, rc.top+6, 255);
				sprintf_s(temp, 100, "%c %c %s물약", index, iden_list.autopickup[i]?'+':'-', potion_iden_string[cur_]);
				DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
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
					sprintf_s(temp, 100, "<두루마리>");
					DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				img_item_scroll.draw(pSprite, rc.left - 24, rc.top + 6, 255);
				img_item_scroll_kind[min(SCT_MAX - 1, max(0, cur_))].draw(pSprite, rc.left - 24, rc.top + 6, 255);
				sprintf_s(temp, 100, "%c %c %s두루마리", index, iden_list.autopickup[i] ? '+' : '-', scroll_iden_string[cur_]);
				DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
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
					sprintf_s(temp, 100, "<반지>");
					DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				img_item_ring[iden_list.ring_list[cur_].type].draw(pSprite, rc.left - 24, rc.top + 6, 255);
				img_item_ring_kind[min(RGT_MAX - 1, max(0, cur_))].draw(pSprite, rc.left - 24, rc.top + 6, 255);
				sprintf_s(temp, 100, "%c %c %s반지", index, iden_list.autopickup[i] ? '+' : '-', ring_iden_string[cur_]);
				DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
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
					sprintf_s(temp, 100, "<부적>");
					DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				img_item_amulet.draw(pSprite, rc.left - 24, rc.top + 6, 255);
				img_item_amulet_kind[min(AMT_MAX - 1, max(0, cur_))].draw(pSprite, rc.left - 24, rc.top + 6, 255);
				sprintf_s(temp, 100, "%c %c %s부적", index, iden_list.autopickup[i] ? '+' : '-', amulet_iden_string[cur_]);
				DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
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
					sprintf_s(temp, 100, "<스펠카드>");
					DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				img_item_spellcard.draw(pSprite, rc.left - 24, rc.top + 6, 255);
				sprintf_s(temp, 100, "%c %c %s스펠카드", index, iden_list.autopickup[i] ? '+' : '-', SpellcardName((spellcard_evoke_type)cur_));
				DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
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
					sprintf_s(temp, 100, "<마법책>");
					DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
					rc.top += 3*fontDesc.Height;
					first_ = false;
				}

				rc.left = two_;
				if (cur_ == 0)
				{
					img_item_book[0].draw(pSprite, rc.left - 24, rc.top + 6, 255);
					sprintf_s(temp, 100, "%c %c %s", index, iden_list.autopickup[i] ? '+' : '-', "미확인 마법책");
				}
				else
				{
					img_item_book[cur_ % (RANDOM_BOOK_NUM - 1)].draw(pSprite, rc.left - 24, rc.top + 6, 255);
					sprintf_s(temp, 100, "%c %c %s", index, iden_list.autopickup[i] ? '+' : '-', static_book_list[cur_ - 1].name.c_str());
				}
				DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
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
				sprintf_s(temp, 100, "<기타>");
				DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
				rc.top += 3 * fontDesc.Height;
				first_ = false;
			}
			rc.left = two_;

			if (cur_ == 0)
			{
				img_item_food_p_item.draw(pSprite, rc.left - 24, rc.top + 6, 255);
				sprintf_s(temp, 100, "%c %c %s", index, iden_list.autopickup[i] ? '+' : '-', "P 아이템");
			}
			else if (cur_ == 1)
			{
				img_item_food_bread.draw(pSprite, rc.left - 24, rc.top + 6, 255);
				sprintf_s(temp, 100, "%c %c %s", index, iden_list.autopickup[i] ? '+' : '-', "음식");
			}
			else if (cur_ >= 2)
			{
				GetTanmacBaseGraphic(cur_-2)->draw(pSprite, rc.left - 24, rc.top + 6, 255);
				sprintf_s(temp, 100, "%c %c %s", index, iden_list.autopickup[i] ? '+' : '-', GetTanmacString(cur_-2).name.c_str());
			}
			DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, font_color_);
			rc.top += 2 * fontDesc.Height;
			num++;

		}
	}

	if (num == 0) {
		rc.left = one_;
		DrawTextUTF8(pfont,pSprite, "식별된 아이템이 없습니다.", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.top += fontDesc.Height;
	}

	rc.top += move + 64;
	max_y = (rc.top - option_mg.getHeight()>0 ? rc.top - option_mg.getHeight() : 0);
}
void display_manager::property_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{	
	RECT rc={50, 50, option_mg.getWidth(), option_mg.getHeight()};
	char temp[256];
	int i =0;
	if(you.property_vector.empty())
	{
		DrawTextUTF8(pfont,pSprite,"당신의 특성이 없습니다.", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		return;
	}
	DrawTextUTF8(pfont,pSprite,"당신의 특성들 (알파벳을 누르면 상세한 정보가 나옵니다.)", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += fontDesc.Height*2;
	for(auto it = you.property_vector.begin(); it != you.property_vector.end(); it++)
	{
		char sp_char = (i<26)?('a'+i):('A'+i-26);
		sprintf_s(temp,256,"%c - ",sp_char);
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, it->getColor());
		rc.left += fontDesc.Width*4;
		DrawTextUTF8(pfont,pSprite,it->GetInfor().c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, it->getColor());
		rc.top += fontDesc.Height;
		rc.left = 50;
		i++;
	}
	return;
}
void display_manager::skill2_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{	
	int i=0;
	RECT rc={50, 50, option_mg.getWidth(), option_mg.getHeight()};
	char temp[100];
	char sp_char = (i<27)?('a'+i):('A'+i-27);
	if(move == 0)
		DrawTextUTF8(pfont,pSprite,"어느 스킬을 사용하겠습니까?", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
	else
		DrawTextUTF8(pfont,pSprite,"어느 스킬의 설명을 보시겠습니까?", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
	rc.top += fontDesc.Height;


	DrawTextUTF8(pfont,pSprite,"단축키 - 이름", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 250;
	DrawTextUTF8(pfont,pSprite,"비용", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 200;
	DrawTextUTF8(pfont,pSprite,"성공률", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += fontDesc.Height;
	rc.left = 50;
	for(int i=0;i<52;i++)
	{
		if(you.MemorizeSkill[i])
		{
			skill_list skill_ = (skill_list)you.MemorizeSkill[i];
			char sp_char = i>=26?('A'+i-26):('a'+i);
			sprintf_s(temp,100,"%c      - %s",sp_char,SkillString(skill_));
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += 250;
			{
				int k = sprintf_s(temp,100,"%s",SkillCostString(skill_));
				DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			}
			rc.left = 500;
			sprintf_s(temp,100,"%3d%%",SkillDiffer(skill_));
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.top += fontDesc.Height;
			rc.left = 50;
		}
	}
	rc.left = 50;
	rc.top = option_mg.getHeight() - fontDesc.Height*3;
	{	
		if(move == 0)
			sprintf_s(temp,100,"!나 ?를 눌러서 설명을 볼 수 있습니다.");
		else		
			sprintf_s(temp,100,"!나 ?를 눌러서 스킬 사용을 할 수 있습니다.");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
	}
}

void display_manager::skill_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	RECT rc={50, 50, option_mg.getWidth(), option_mg.getHeight()};
	char temp[100];
	int skt = 0, i=0; 
	char sk_char = 'a';

	sprintf_s(temp, 100, "      스킬명  레벨    현재  적성   비용          스킬명  레벨    현재  적성   비용");
	DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
	rc.top += 2*fontDesc.Height;

	rc.left = 50;

	while(skt < SKT_MAX)
	{
		for(i = 0;i<1;i++)
		{

			sprintf_s(temp,100,"%c %c %8s %4d", you.GetSkillLevel(skt, false)==27 || you.cannotSkillup(skt) ?' ':sk_char,(you.GetSkillLevel(skt, false) ==27 || you.cannotSkillup(skt) ?' ':(you.skill[skt].onoff ==2?'*':(you.skill[skt].onoff ==1?'+':'-'))),skill_string((skill_type)skt), you.GetSkillLevel(skt, true));
			sk_char++;

			D3DCOLOR color_ = you.GetSkillLevel(skt, true) < 27 && !you.cannotSkillup(skt) ?
				(you.bonus_skill[skt]? (you.skill[skt].onoff == 2 ? CL_white_blue : (you.skill[skt].onoff == 1 ? CL_blue : CL_darkblue)) :

				(you.skill[skt].onoff == 2 ? CL_normal : (you.skill[skt].onoff == 1 ? CL_STAT : CL_bad))) :
				you.pure_skill == skt ? CL_junko : CL_warning;
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, color_);
			rc.left += 150;
			//if(move ==0)
			if(you.GetSkillLevel(skt, false)<27 && !you.cannotSkillup(skt))
				sprintf_s(temp,100,"(%2d%%)",GetSkillPercent(you.skill[skt]));
			else 
				sprintf_s(temp,100,"");

			//else if(move == 1)
			//	sprintf_s(temp,100,"%d",you.skill[skt].aptit);
			//else
			//	sprintf_s(temp,100,"%d",you.skill[skt].exper);
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, color_);
			rc.left += 50;
						
			sprintf_s(temp,100,"%3d",you.skill[skt].aptit);
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,GetSkillColor(you.skill[skt].aptit));

			rc.left += 50;
			if (you.GetSkillLevel(skt, false) < 27 && !you.cannotSkillup(skt))
			{
				int base_skill = GetBaseSkillExp();
				int skill_pecent = GetMaxSkillExp(you.skill[skt]);
				float multi_ = exp_to_skill_exp(you.GetSkillLevel(skt, false));

				float value_ = (float)skill_pecent / base_skill;

				sprintf_s(temp, 100, "%3.1f", value_);
				DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
			}
			else if (you.pure_skill == skt)
			{

				DrawTextUTF8(pfont,pSprite, "순화 ", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_junko);

			}
			else
			{
				sprintf_s(temp, 100, " -   ");
				DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
			}

			rc.left += 200;
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
				rc.left = 800;
				rc.top = 50+fontDesc.Height;
			}
		}
		rc.left -= 450*i;
		rc.top += fontDesc.Height;
		skt++;
	}

	rc.left = 50;	
	rc.top += fontDesc.Height*2;
	DrawTextUTF8(pfont,pSprite,item_view_message.c_str(), -1, &rc, DT_NOCLIP,CL_warning);
	rc.top += fontDesc.Height *2;

	if (item_view_message.size() < 1)
	{
		DrawTextUTF8(pfont,pSprite, "현재 당신의 스킬레벨을 확인하고 경험치 분배 비율을 조절할 수 있습니다.", -1, &rc, DT_NOCLIP, CL_normal);
		rc.top += fontDesc.Height * 1;

		DrawTextUTF8(pfont,pSprite, "알파벳 키를 눌러서 원하는 스킬로 경험치를 분배할 수 있습니다.", -1, &rc, DT_NOCLIP, CL_normal);

		rc.top += fontDesc.Height * 2;
		if (wiz_list.wizard_mode == 1)
		{
			char temp[50];
			sprintf_s(temp, 50, "[현재 경험치 패널티 %d]", exp_to_skill_exp(0));
			DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_NOCLIP, CL_help);
		}
	}

}
void display_manager::state_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	RECT rc={30, 10, option_mg.getWidth(), option_mg.getHeight()};
	char temp[100];
	sprintf_s(temp,100,"%s (%d레벨 %s %s %s)",you.user_name.name.c_str(),you.level,tribe_type_string[you.tribe],job_type_string[you.job],you.GetCharNameString()->c_str());
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_warning);
	rc.left += 300;
	sprintf_s(temp,100,"턴: %d",you.turn);	
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 200;
	if(you.god == GT_NONE)
	{
		sprintf_s(temp,100,"무신앙");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	else if (you.god == GT_TENSI)
	{
		sprintf_s(temp, 100, "신앙: %s", GetGodString(you.god));
		DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	else
	{
		sprintf_s(temp,100,"신앙: %s %c%c%c%c%c%c",GetGodString(you.god),pietyLevel(you.piety)>=1?'*':'.',pietyLevel(you.piety)>=2?'*':'.',pietyLevel(you.piety)>=3?'*':'.',pietyLevel(you.piety)>=4?'*':'.',pietyLevel(you.piety)>=5?'*':'.',pietyLevel(you.piety)>=6?'*':'.');
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;		

	sprintf_s(temp,100,"HP: %d/%d",you.GetHp(),you.GetMaxHp());
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"AC:%4d",you.ac);
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"힘  :%4d",you.s_str);
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;		

	if (!you.pure_mp)
	{
		sprintf_s(temp, 100, "MP: %d/%d", you.GetMp(), you.GetMaxMp());
		DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	rc.left += 150;
	sprintf_s(temp,100,"EV:%4d",you.ev);
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"민첩:%4d",you.s_dex);
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;		

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);

	{
		int pow_ = min(you.power, 500);
		sprintf_s(temp, 100, "파워: %d.%02d", pow_ / 100, pow_ % 100);
		DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	rc.left += 150;
	sprintf_s(temp,100,"SH:%4d",you.sh);
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"지능:%4d",you.s_int);
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;		
	rc.top += fontDesc.Height;		

	int resist_ = you.fire_resist - you.uniden_fire_resist;
	if(resist_>=100)
		sprintf_s(temp, 100, "화염저항: ∞");
	else
		sprintf_s(temp,100,"화염저항: %c %c %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'),resist_>=2?'+':(resist_<=-2?'-':'.'),resist_>=3?'+':(resist_<=-3?'-':'.'));
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	resist_ = you.confuse_resist- you.uniden_confuse_resist;
	sprintf_s(temp,100,"혼란저항: %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	sprintf_s(temp,100,"무기: ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_WEAPON])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_WEAPON]->id,you.equipment[ET_WEAPON]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"맨손");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;


	resist_ = you.ice_resist - you.uniden_ice_resist;
	if (resist_ >= 100)
		sprintf_s(temp, 100, "냉기저항: ∞");
	else
		sprintf_s(temp,100,"냉기저항: %c %c %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'),resist_>=2?'+':(resist_<=-2?'-':'.'),resist_>=3?'+':(resist_<=-3?'-':'.'));
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	resist_ = you.invisible_view- you.uniden_invisible_view;
	sprintf_s(temp,100,"투명보기: %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	sprintf_s(temp,100,"탄막: ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.throw_weapon)
	{
		sprintf_s(temp,100,"%c) %s",you.throw_weapon->id,you.throw_weapon->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.throw_weapon->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	resist_ = you.elec_resist - you.uniden_elec_resist;
	if (resist_ >= 100)
		sprintf_s(temp, 100, "전기저항: ∞");
	else
		sprintf_s(temp,100,"전기저항: %c %c %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'),resist_>=2?'+':(resist_<=-2?'-':'.'),resist_>=3?'+':(resist_<=-3?'-':'.'));
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	resist_ = you.power_keep- you.uniden_power_keep;


	if (you.power == 1000) {
		sprintf_s(temp, 100, "파워유지: ∞");
		resist_ = 1;
	}
	else
		sprintf_s(temp,100,"파워유지: %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	sprintf_s(temp,100,"몸통: ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_ARMOR])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_ARMOR]->id,you.equipment[ET_ARMOR]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_ARMOR]->item_color());
	}
	else
	{
		sprintf_s(temp,100,you.isImpossibeEquip(ET_ARMOR, false)?"없음":"착용불가");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	
	resist_ = you.poison_resist - you.uniden_poison_resist;
	sprintf_s(temp,100,"독저항  : %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"방패: ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_SHIELD])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_SHIELD]->id,you.equipment[ET_SHIELD]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_SHIELD]->item_color());
	}
	else
	{
		sprintf_s(temp,100,you.isImpossibeEquip(ET_SHIELD, false)?"없음":"착용불가");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
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
	sprintf_s(temp,100,"마법저항: %s" , resist_text_.c_str());
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"머리: ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_HELMET])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_HELMET]->id,you.equipment[ET_HELMET]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_HELMET]->item_color());
	}
	else
	{
		sprintf_s(temp,100,you.isImpossibeEquip(ET_HELMET, false)?"없음":"착용불가");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	
	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"망토: ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_CLOAK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_CLOAK]->id,you.equipment[ET_CLOAK]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_CLOAK]->item_color());
	}
	else
	{
		sprintf_s(temp,100,you.isImpossibeEquip(ET_CLOAK, false)?"없음":"착용불가");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
	

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"손  : ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_GLOVE])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_GLOVE]->id,you.equipment[ET_GLOVE]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_GLOVE]->item_color());
	}
	else
	{
		sprintf_s(temp,100,you.isImpossibeEquip(ET_GLOVE, false)?"없음":"착용불가");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;


	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"발  : ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_BOOTS])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_BOOTS]->id,you.equipment[ET_BOOTS]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_BOOTS]->item_color());
	}
	else
	{
		sprintf_s(temp,100,you.isImpossibeEquip(ET_BOOTS, false)?"없음":"착용불가");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
	

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"목걸이  : ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*10;
	if(you.equipment[ET_NECK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_NECK]->id,you.equipment[ET_NECK]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_NECK]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

		

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"왼반지  : ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*10;
	if(you.equipment[ET_LEFT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_LEFT]->id,you.equipment[ET_LEFT]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_LEFT]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
			

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"오른반지: ");
	DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*10;
	if(you.equipment[ET_RIGHT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_RIGHT]->id,you.equipment[ET_RIGHT]->GetName().c_str());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_RIGHT]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
	rc.top += fontDesc.Height;



	
	string rune_temp;
	
	rune_temp = "룬:";
	for(int i=0;i<RUNE_HAKUREI_ORB;i++)
	{		
		if(you.rune[i])
		{
			if(i!=0)
				rune_temp += ", ";
			rune_temp += rune_string[i];
		}
	}
	DrawTextUTF8(pfont,pSprite,rune_temp.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;
	
	if(you.rune[RUNE_HAKUREI_ORB])
	{
		DrawTextUTF8(pfont,pSprite,"음양옥", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	else
	{				
	}
	rc.left = 30;
	rc.top += fontDesc.Height;



}

void display_manager::game_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	GetClientRect(hwnd, &windowSize);
	scale_x = (windowSize.right - windowSize.left) / (float)option_mg.getWidthCommon();
	scale_y = (windowSize.bottom - windowSize.top) / (float)option_mg.getHeightCommon();
	infobox.init();
	{
		int i=0;
		RECT rc={32*16+50, 10, option_mg.getWidth(), option_mg.getHeight()};
		char temp[128];
		sprintf_s(temp,128,"%d레벨",you.level);
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*7;
		DrawTextUTF8(pfont,pSprite,you.user_name.name.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		
		if(ReplayClass.play)
		{
			rc.left = 32*16+180;			
			DrawTextUTF8(pfont,pSprite,"*리플레이 중*", -1, &rc, DT_SINGLELINE | DT_NOCLIP, wiz_list.wizard_mode == 1?CL_help:(wiz_list.wizard_mode == 2?CL_magic:CL_warning));
		}
		else if(wiz_list.wizard_mode == 1)
		{
			rc.left = 32*16+180;			
			DrawTextUTF8(pfont,pSprite,"*위자드 모드*", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
		}
		else if(wiz_list.wizard_mode == 2)
		{
			rc.left = 32*16+180;			
			DrawTextUTF8(pfont,pSprite,"*세이브 보존*", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_magic);
		}




		rc.top += fontDesc.Height;
		rc.left = 32*16+50;
		DrawTextUTF8(pfont,pSprite,tribe_type_string[you.tribe], -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*(strlen(tribe_type_string[you.tribe])+1);
		DrawTextUTF8(pfont,pSprite,job_type_string[you.job], -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*(strlen(job_type_string[you.job])+1);
		DrawTextUTF8(pfont,pSprite,you.GetCharNameString()->c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left = 32*16+50;
		rc.top += fontDesc.Height;


		if(you.god == GT_NONE)
		{
			sprintf_s(temp,128,"무신앙");
		}
		else if (you.god == GT_MIKO) 
		{
			sprintf_s(temp, 128, "신앙: %s (인기도 %d%%)", GetGodString(you.god), you.piety/2);
		}
		else if (you.god == GT_TENSI)
		{
			sprintf_s(temp, 128, "신앙: %s", GetGodString(you.god));
		}
		else
		{
			sprintf_s(temp,128,"신앙: %s %c%c%c%c%c%c",GetGodString(you.god),pietyLevel(you.piety)>=1?'*':'.',pietyLevel(you.piety)>=2?'*':'.',pietyLevel(you.piety)>=3?'*':'.',pietyLevel(you.piety)>=4?'*':'.',pietyLevel(you.piety)>=5?'*':'.',pietyLevel(you.piety)>=6?'*':'.');
		}
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);

		rc.top += fontDesc.Height;

		sprintf_s(temp,128,"HP: %d/%d",you.GetHp(),you.GetMaxHp());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
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
			sprintf_s(temp, 128, "MP: %d/%d", you.GetMp(), you.GetMaxMp());
			DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
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



		int left_ =0 ;

		int pow_ = min(you.power,500);
		img_item_food_p_item.draw(pSprite,rc.left+7,rc.top+7,255);
		left_ = sprintf_s(temp,128,"   %d.%02d",pow_/100,pow_%100);
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, you.power == 1000 ? CL_junko :(pow_<=100?CL_danger:(pow_<=200?CL_warning:(pow_==500?CL_good:CL_normal))));
		//임시		
		//rc.left += fontDesc.Width*left_;
		//sprintf_s(temp,50,"%6d",you.hunger);
		//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, you.s_might?CL_white_blue:CL_STAT);
		rc.left = 32*16+50;




		rc.top += fontDesc.Height;
		left_ = sprintf_s(temp,128,"AC:");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;
				
		int temp_buff_value_ = 0;


		left_ = sprintf_s(temp,128,"%4d", you.GetDisplayAc());
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_AC)+ (you.alchemy_buff == ALCT_DIAMOND_HARDNESS)?5:0;
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:CL_STAT);
		rc.left += fontDesc.Width*left_;

		left_ = sprintf_s(temp,128,"    힘  :");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;

		if(you.s_str == you.m_str)
			sprintf_s(temp,128,"%4d",you.s_str);
		else
			sprintf_s(temp,128,"%4d (%2d)",you.s_str,you.m_str);
		
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_STR);
		{
			D3DCOLOR color_ = 
				you.s_str<=0?CL_danger:
				temp_buff_value_>0?CL_white_blue:
				temp_buff_value_<0?CL_small_danger:
				you.s_stat_boost==1?CL_white_puple:
				(you.s_str != you.m_str)?CL_warning:CL_STAT;
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,color_);
			rc.left = 32*16+50;
		}

		rc.top += fontDesc.Height;
		left_ = sprintf_s(temp,128,"EV:");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;

		
		left_ = sprintf_s(temp,128,"%4d", you.GetDisplayEv());
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_EV);
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:CL_STAT);
		rc.left += fontDesc.Width*left_;

		left_ = sprintf_s(temp,128,"    민첩:");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;


		if(you.s_dex == you.m_dex)
			sprintf_s(temp,128,"%4d",you.m_dex);
		else
			sprintf_s(temp,128,"%4d (%2d)",you.s_dex,you.m_dex);
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_DEX);
		{
			D3DCOLOR color_ = 
				you.s_dex<=0?CL_danger:
				temp_buff_value_>0?CL_white_blue:
				temp_buff_value_<0?CL_small_danger:
				you.s_stat_boost==2?CL_white_puple:
				(you.s_dex != you.m_dex)?CL_warning:CL_STAT;
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,color_);
			rc.left = 32*16+50;
		}

		rc.top += fontDesc.Height;
		left_ = sprintf_s(temp,128,"SH:");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;

		left_ = sprintf_s(temp,128,"%4d",you.GetDisplaySh());
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_SH);
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:CL_STAT);
		rc.left += fontDesc.Width*left_;

		left_ = sprintf_s(temp,128,"    지능:");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;



		if(you.s_int == you.m_int)
			sprintf_s(temp,128,"%4d",you.m_int);
		else
			sprintf_s(temp,128,"%4d (%2d)",you.s_int,you.m_int);
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_INT);

		
		{
			D3DCOLOR color_ =
				you.s_int<=0?CL_danger:
				temp_buff_value_>0?CL_white_blue:
				temp_buff_value_<0?CL_small_danger:
				you.s_stat_boost==3?CL_white_puple:
				(you.s_int != you.m_int)?CL_warning:CL_STAT;
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,color_);
			rc.left = 32*16+50;
		}

		rc.top += fontDesc.Height;


		sprintf_s(temp, 128, "부적: ");
		DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width * 6;

		if (you.equipment[ET_NECK])
		{
			item* _item = you.equipment[ET_NECK];
			char temp2[64];
			if (_item->type == ITM_AMULET)
			{
				sprintf_s(temp2, 64, "%s%s", iden_list.amulet_list[_item->value1].iden == 2 ? amulet_iden_string[_item->value1] : amulet_uniden_string[iden_list.amulet_list[_item->value1].type], _item->name.name.c_str());
			}
			sprintf_s(temp, 128, "%c) %s (%d%%)", you.equipment[ET_NECK]->id, temp2, you.getAmuletPercent());
			DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, you.equipment[ET_NECK]->item_color());
		}
		else
		{
			sprintf_s(temp, 128, "없음");
			DrawTextUTF8(pfont,pSprite, temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
		}
		rc.left = 32 * 16 + 50;
		rc.top += fontDesc.Height;

		sprintf_s(temp,128,"무기: ");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*6;
		if(you.equipment[ET_WEAPON])
		{
			sprintf_s(temp,128,"%c) %s",you.equipment[ET_WEAPON]->id,you.equipment[ET_WEAPON]->GetName().c_str());
			int prev_space_=0;
			int one_line = 0;
			int max_len_ = 29;
			for(unsigned int i = 0 ; i < strlen(temp)+1;i++)
			{
				if(temp[i] == ' ')
					prev_space_ = one_line;
				one_line++;
				if(one_line == max_len_)
				{
					if(prev_space_ == 0)
					{
						DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
						rc.left = 32*16+50;
						rc.top +=fontDesc.Height;
						max_len_ = 36;
						break;
					}
					else{
						char tempchar2[128];
						int j = 0;
						for(j = 0; j<prev_space_;j++)
							tempchar2[j] = temp[i - one_line+1+j];
						tempchar2[j] = NULL;			

						DrawTextUTF8(pfont,pSprite,tempchar2, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
						rc.left = 32*16+50;
						rc.top +=fontDesc.Height;
						max_len_ = 36;
					}
					i -= one_line-prev_space_-1;
					one_line = 0;
					prev_space_ = 0;
				}
				else if(i == strlen(temp))
				{
					char tempchar2[128];
					int j = 0;
					for(j = 0; j<one_line;j++)
						tempchar2[j] = temp[i - one_line+1+j];
					tempchar2[j] = NULL;
			
					DrawTextUTF8(pfont,pSprite,tempchar2, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
					rc.left = 32*16+50;
					rc.top +=fontDesc.Height;
					max_len_ = 36;
				}
			}
		}
		else
		{
			sprintf_s(temp,128,"맨손");
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
			rc.left = 32*16+50;
			rc.top +=fontDesc.Height;
		}
		//rc.left -= fontDesc.Width*6;

		//rc.top += fontDesc.Height;
		sprintf_s(temp,128,"탄막: ");
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*6;
		if(you.throw_weapon)
		{
			sprintf_s(temp,128,"%c) %s",you.throw_weapon->id,you.throw_weapon->GetName().c_str());
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.throw_weapon->item_color());
		}
		else
		{
			sprintf_s(temp,128,"없음");
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
		}
		rc.left -= fontDesc.Width*6;




		
		if(you.GetNeedExp(you.level-1) > 0)
		{
			rc.top += fontDesc.Height;
			sprintf_s(temp,128,"다음레벨까지:");
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += fontDesc.Width*14;
		
			sprintf_s(temp,128,"%d%%",(you.exper-you.GetNeedExp(you.level-2))*100/(you.GetNeedExp(you.level-1)-you.GetNeedExp(you.level-2)));
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_STAT);
			rc.left -= fontDesc.Width*14;
		}
		else
		{
			rc.top += fontDesc.Height;
			sprintf_s(temp,128,"최고 레벨");
			DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_warning);

		}


		rc.top += fontDesc.Height;
		sprintf_s(temp,128,"%s",CurrentLevelString());
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*15;
		sprintf_s(temp,128,"턴: %g (%g)",you.real_turn/10.0f, you.prev_real_turn/10.0f);
		DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);		
		rc.left -= fontDesc.Width*15;
		rc.top += fontDesc.Height;
		//sprintf_s(temp,128,"남은스킬경험치: %d",you.skill_exper);
		//DrawTextUTF8(pfont,pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		//rc.top += fontDesc.Height;

		{ //상태이상 표시!
			/*const char *state_str;*/
			/*int hunger = you.GetHunger();
			if(hunger != HT_NORMAL)
			{
				state_str = state_string[hunger];
				DrawTextUTF8(pfont,pSprite,state_str, -1, &rc, DT_SINGLELINE | DT_NOCLIP,hunger==HT_STARVING?CL_danger:(hunger<=HT_HUNGRY?CL_warning:CL_good));
				rc.left += fontDesc.Width*(strlen(state_str)+1);				
			}*/

			stateBox stateDraw(pSprite, pfont, rc);


			if(wiz_list.wizard_mode == 1)
			{
				sprintf_s(temp,128,"위험도(%d)",you.tension_gauge);
				stateDraw.addState(temp, CL_small_danger, "위험도는 얼마나 현재 상황이 위험한지에 대한 수치입니다.", this);
				stateDraw.enter(this);
			}
			if (you.s_weather>0 && you.s_weather_turn)
			{
				D3DCOLOR color_ = CL_normal;
				switch (you.s_weather) {
				case 1:
					stateDraw.addState("안개", color_, "짙은 안개로 인하여 모두의 시야가 급격히 줄어듭니다.", this);
					break;
				case 2:
					stateDraw.addState("천둥번개", color_, "주변에 무작위로 천둥번개가 떨어집니다.", this);
					break;
				case 3:
					stateDraw.addState("쾌청", color_, "주변의 모두가 빛나게되어 회피가 낮아지고 투명이 효과를 잃습니다.", this);
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
				sprintf_s(temp,128,"장비패널티(%d)",you.as_penalty);
				stateDraw.addState(temp, color_,
					you.as_penalty > you.GetPenaltyMinus(3) ? "갑옷과 방패가 너무 무겁습니다! 패널티만큼 회피, 은밀, 마법, 명중, 이동속도가 감소되고, 행동속도가 2배로 느려집니다." : //끔찍
					you.as_penalty>you.GetPenaltyMinus(2) ? "갑옷과 방패의 패널티의 합계입니다. 패널티만큼 회피, 은밀, 마법성공율, 명중, 이동속도가 감소합니다.": //이동패널티
					you.as_penalty>you.GetPenaltyMinus(1) ? "갑옷과 방패의 패널티의 합계입니다. 패널티만큼 회피, 은밀, 마법성공율, 명중이 감소합니다." : //명중
					"갑옷과 방패의 패널티의 합계입니다. 패널티만큼 회피와 은밀, 마법성공율이 감소합니다.", this);
			}
			bool haste_temp_ = false;

			if (you.god == GT_MIKO)
			{
				if (env[current_level].popular == 1) {
					stateDraw.addState("새로운장소", CL_normal, "이 층에선 욕망부르기를 아직 사용하지않았습니다.", this);
				}
				int mikocloak_ = you.isSetMikoBuff(0);
				if (mikocloak_ == 1) {
					stateDraw.addState("빨간망토", CL_danger, "층을 옮기기 전까지 전투력보너스 +6과 체력재생력을 얻고 있습니다.", this);
				}
				else if (mikocloak_ == 2) {
					stateDraw.addState("파랑망토", CL_blue, "층을 옮기기 전까지는 스펠 파워 1.5배와 영력재생력을 얻고 있습니다.", this);
				}
				int ulti_ = you.isSetMikoBuff(1);
				if (ulti_ >= 1 && ulti_ <= 3) {
					stateDraw.addState(ulti_ == 1 ? "인기폭발(체력)":(ulti_ == 2 ? "인기폭발(영력)" : "인기폭발(가속)"),
						CL_miko, 
						ulti_ == 1 ? "최대 체력이 두배가 됩니다."
						: (ulti_ == 2 ? "영력 회복속도가 폭증합니다." : 
							"당신의 모든 행동속도는 1.5배 빨라집니다."), this);
					if (ulti_ == 3) {
						haste_temp_ = true;
					}
				}
				if (you.GetBuffOk(BUFFSTAT_HALO)) {
					stateDraw.addState("후광", CL_normal,
						"주변의 적의 회피를 낮추고 투명을 보이게 하지만 당신의 은밀과 회피도 낮아집니다.", this);
				}
			}
			else if (you.GetPunish(GT_MIKO)) {
				if (you.GetBuffOk(BUFFSTAT_HP) < 0) {
					stateDraw.addState("허약", CL_danger,
						"최대 체력이 절반으로 줄었습니다.", this);
				}
			}
			if (you.god == GT_JOON_AND_SION || you.GetPunish(GT_JOON_AND_SION))
			{
				if (you.god_value[GT_JOON_AND_SION][0] == 1) {
					stateDraw.addState("빙의(죠온)", CL_joon, you.GetPunish(GT_JOON_AND_SION)?"소모품을 사용시 무조건 2~3개씩 낭비하여 사용합니다.":
						"소모품을 사용시 무조건 2~3개씩 낭비하여 사용합니다. 빙의가 풀리면 파워 3.00로 내려갑니다.", this);
				}
				if (you.god_value[GT_JOON_AND_SION][0] == 2) {
					stateDraw.addState("빙의(시온)", CL_sion, you.GetPunish(GT_JOON_AND_SION) ? "줍지않은 소모품은 빠른속도로 사라지며 소모품을 버리면 무조건 사라집니다." : 
						"줍지않은 소모품은 빠른속도로 사라지며 소모품을 버리면 무조건 사라집니다. 파워패널티를 안 받습니다.", this);
				}
			}
			if (you.drowned)
			{
				stateDraw.addState("익사중", CL_danger, "물에 빠졌습니다!", this);
			}
			if (current_level == ZIGURRAT_LEVEL)
			{
				stateDraw.addState("전이제어방해", CL_danger, "이 곳에서는 제어된 순간이동을 할 수 없다. 제어된 순간이동은 무작위 순간이동으로 바뀐다.", this);
			}
			if(you.GetStatPanalty())
			{
				stateDraw.addState("스탯패널티", CL_danger, "스탯이 0이 된 패널티로 모든 행동 딜레이가 2배가 됩니다.", this);
			}
			if(you.s_exhausted)
			{
				stateDraw.addState("피로", CL_warning, "피로한 동안엔 몇몇 행동이 불가능합니다.", this);
			}
			if (you.s_super_graze)
			{
				stateDraw.addState("근성회피", you.s_super_graze>3 ? CL_normal : CL_white_blue, "회피가능한 모든 공격을 100% 회피합니다.", this);
			}
			if(you.s_trans_panalty)
			{
				stateDraw.addState("시공부작용", you.s_trans_panalty <= 2 ? CL_bad : (you.s_trans_panalty<5 ? CL_warning : CL_small_danger), 
					"시공마법의 성공율이 대폭 감소합니다.", this);
			}
			if(you.s_spellcard)
			{
				stateDraw.addState("스펠카드", you.s_spellcard>5 ? CL_white_blue : CL_blue, 
					"당신은 스펠카드를 사용하고 있습니다.", this);
			}
			if(you.s_autumn>0)
			{
				stateDraw.addState("공기화", you.s_autumn>0 ? CL_autumn : CL_danger, 
					"당신은 믿을 수 없을 정도로 은밀합니다.", this);
			}
			if(you.s_wind)
			{
				stateDraw.addState("건신초래풍", CL_white_blue,
					"모든 근접, 원거리공격이 범위 공격이 됩니다.", this);
			}
			if(you.s_knife_collect)
			{
				stateDraw.addState("탄막회수", CL_white_blue,
					"당신이 쏜 탄막 아이템은 던지자마자 인벤토리로 회수됩니다.", this);
			}
			if(you.s_drunken)
			{
				stateDraw.addState("음주", CL_warning,
					"술이 취해있습니다. 올바르게 걷기 힘들며 마법 성공율이 약간 내려갑니다.", this);
			}
			if(you.s_lunatic)
			{
				stateDraw.addState("광기", CL_danger,
					"대부분의 복잡한 행동이 불가능해지지만 근접 공격력이 대폭 상승합니다.", this);
			}
			if(you.s_catch)
			{
				stateDraw.addState("잡기", CL_yuigi,
					"당신은 근접한 상대를 잡고 있습니다. 권능에 부가 효과가 생깁니다.", this);
			}
			if(you.s_ghost)
			{
				stateDraw.addState("유령", you.s_ghost>1 ? CL_white_blue : CL_yuyuko,
					"당신의 주변엔 유령들이 꼬이고 있습니다.", this);
			}
			if(you.s_dimension)
			{
				stateDraw.addState("차원고정", you.s_dimension>3 ? CL_yukari : CL_blue,
				 (you.god == GT_YUKARI)?
						"당신은 현재 차원을 고정시켜 상하좌우의 차원을 넘나들 수 있습니다.":
					"강제로 결계에 의해 차원이 고정되어 지속시간동안 결계 밖으로 나갈 수 없습니다!" , this);
			}
			if(you.s_mirror)
			{
				stateDraw.addState("반사", CL_normal,
					"받은 모든 공격을 상대에게 되돌려 줍니다.", this);
			}
			if(you.s_paradox)
			{
				stateDraw.addState("패러독스", CL_white_blue,
					"탄막이나 일부 마법을 사용하면 연달아 2번 나갑니다.", this);
			}
			if(you.s_the_world)
			{
				stateDraw.addState("시간정지", you.s_the_world>1 ? CL_white_blue : you.s_the_world<0 ? CL_normal : CL_blue,
					"당신을 제외한 모든 물체는 움직일 수 없습니다.", this);
			}
			if(you.s_mana_delay)
			{
				stateDraw.addState("영력회복지연", CL_warning,
					"영력이 자연적으로 회복되지않습니다.", this);
			}
			if (env[current_level].isSilence(you.position))
			{
				stateDraw.addState("침묵", CL_white_blue,
					"당신은 소리를 내어 말하는 것이 불가능합니다. 마법과 두루마리, 일부 권능을 사용할 수 없습니다.", this);
			}
			if(you.s_eirin_poison_time)
			{
				D3DCOLOR color_ = you.s_eirin_poison_time>11 ? CL_small_danger : CL_danger;
				sprintf_s(temp, 128, "부작용(%d)", you.s_eirin_poison);
				stateDraw.addState(temp, color_,
					"시간이 지나면 수치만큼 지속데미지를 받습니다.", this);
			}
			if(you.s_stasis)
			{				
				D3DCOLOR color_ = CL_danger;
				sprintf_s(temp,128,"전이불가");
				stateDraw.addState(temp, color_,
					"전이관련 마법과 아이템을 사용할 수 없습니다.", this);
			}
			if(you.force_turn)
			{				
				D3DCOLOR color_ = you.force_strong?CL_white_blue:CL_danger;
				sprintf_s(temp,128,you.force_strong?"강화":"약화");
				stateDraw.addState(temp, color_,
					you.force_strong ? "당신의 모든 공격과 마법은 강화되었습니다." :
					"당신의 모든 공격과 마법은 약화되었습니다.", this);
			}
			if (you.s_evoke_ghost)
			{
				stateDraw.addState("유령화", CL_normal,
					"당신은 모든 공격을 받지않습니다. 단, 이동 이외의 공격, 마법, 아이템등의 모든 행동을 사용할 수 없습니다.", this);
			}

			



			

			if(you.power<=200)
			{
				bool sion_ = (you.god == GT_JOON_AND_SION && !you.GetPunish(GT_JOON_AND_SION) && you.god_value[GT_JOON_AND_SION][0] == 2);
				stateDraw.addState("파워부족", sion_ ? CL_bad:(you.power <= 100 ? CL_danger : CL_warning),
					sion_ ? "시온이 당신의 파워 패널티를 막고있습니다." :(you.power <= 100 ? "파워가 부족하여 공격력이 매우 약해졌습니다.": "파워가 부족하여 공격력이 약해졌습니다."), this);
			}
			if(you.s_poison)
			{
				stateDraw.addState("독", you.s_poison <= 50 ? CL_warning : (you.s_poison <= 100 ? CL_small_danger : CL_danger),
					"지속적으로 독 데미지를 받고있습니다.", this);
			}
			if(you.s_tele)
			{
				stateDraw.addState("공간", CL_blue,
					"일정 턴이 지나면 같은 층 무작위 위치로 이동됩니다.", this);
			}
			if((you.s_pure_haste || you.s_haste || you.alchemy_buff == ALCT_HASTE) && !you.s_slow)
			{
				if ((you.s_haste || you.alchemy_buff == ALCT_HASTE) && !haste_temp_)
					stateDraw.addState("가속", you.alchemy_buff == ALCT_HASTE ? CL_alchemy : (you.s_haste>10 ? CL_white_blue : CL_blue),
						"당신의 모든 행동속도는 1.5배 빨라집니다.", this);
				else if (you.s_pure_haste)
					stateDraw.addState("살의",CL_junko,
						"당신의 모든 행동속도는 1.5배 빨라집니다. 시야에 적이 안보이게되면 버프가 사라집니다.", this);
			}
			else if(you.s_slow && !(you.s_haste || you.alchemy_buff == ALCT_HASTE))
			{
				stateDraw.addState("감속", CL_danger,
					"당신의 모든 행동속도는 0.7배로 느려집니다.", this);
			}
			else if((you.s_haste || you.alchemy_buff == ALCT_HASTE) && you.s_slow)
			{
				stateDraw.addState("가속+감속", CL_magic,
					"가속과 감속효과를 동시에 받아 안정된 상태입니다.", this);
			}
			if(you.alchemy_buff == ALCT_STONE_FIST)
			{
				stateDraw.addState("돌주먹", CL_alchemy,
					"당신의 다음 맨손 공격은 추가 데미지를 줍니다.", this);
			}
			if(you.alchemy_buff == ALCT_DIAMOND_HARDNESS)
			{
				stateDraw.addState("다이아", CL_alchemy,
					"잠깐동안 추가 방어력을 얻습니다.", this);
			}
			if(you.alchemy_buff == ALCT_POISON_BODY)
			{
				stateDraw.addState("포이즌", CL_alchemy,
					"주변 8타일의 적에게 지속적으로 독 데미지를 줍니다.", this);
			}
			if(you.alchemy_buff == ALCT_STONE_FORM)
			{
				stateDraw.addState("무념무상", CL_alchemy,
					"근접 공격력이 상승하고 받는 데미지가 66%가 되지만 이동속도가 1.3배 느려집니다.", this);
			}
			if(you.alchemy_buff == ALCT_AUTUMN_BLADE)
			{
				stateDraw.addState("블레이드", CL_alchemy,
					"근접 공격력이 3배가 됩니다.", this);
			}
			if(you.alchemy_buff == ALCT_PHILOSOPHERS_STONE)
			{
				stateDraw.addState("현자의돌", CL_alchemy,
					"능력사용(a키)으로 5원소의 마법이 저렴하게 사용가능합니다.", this);
			}
			if(you.s_unluck > 0)
			{
				if(you.s_unluck <= 3)
				{
					stateDraw.addState("흉", CL_warning,
						"당신은 불행합니다! 이 상태는 경험치를 먹어야 사라집니다.", this);
				}
				else if(you.s_unluck <= 6)
				{
					stateDraw.addState("대흉", CL_small_danger,
						"당신은 아주 불행합니다! 이 상태는 경험치를 먹어야 사라집니다.", this);
				}
				else
				{
					stateDraw.addState("불멸", CL_danger,
						"당신은 끔찍하게 불행합니다! 이 상태는 경험치를 먹어야 사라집니다.", this);
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
					sprintf_s(temp,128,"화저%s",(rf_>0? (rf_>1 ? (rf_>2 ? "+++" : "++") : "+") : (rf_<-1 ? (rf_<-2 ? "---" : "--") : "-")));
					stateDraw.addState(temp, rf_>0 ? CL_good : CL_danger,
						(rf_>0 ? "화염 저항이 높아졌습니다." : "화염 저항이 낮아졌습니다."), this);
				}
				if(rc_)
				{
					sprintf_s(temp,128,"냉저%s", (rc_>0 ? (rc_>1 ? (rc_>2 ? "+++" : "++") : "+") : (rc_<-1 ? (rc_<-2 ? "---" : "--") : "-")));
					stateDraw.addState(temp, rc_>0 ? CL_good : CL_danger,
						(rc_>0 ? "냉기 저항이 높아졌습니다." : "냉기 저항이 낮아졌습니다."), this);
				}
				if (re_)
				{
					sprintf_s(temp, 128, "뇌저%s", (re_>0 ? (re_>1 ? (re_>2 ? "+++" : "++") : "+") : (re_<-1 ? (re_<-2 ? "---" : "--") : "-")));
					stateDraw.addState(temp, re_>0 ? CL_good : CL_danger,
						(re_>0 ? "전기 저항이 높아졌습니다." : "전기 저항이 낮아졌습니다."), this);
				}
				if (rp_)
				{
					sprintf_s(temp, 128, "독저%s", rp_>0 ? "+" : "-");
					stateDraw.addState(temp, rp_>0 ? CL_good : CL_danger,
						(rp_>0 ? "독 저항이 높아졌습니다." : "독 저항이 낮아졌습니다."), this);
				}
				if (rconf_)
				{
					sprintf_s(temp, 128, "혼란저%s", rconf_>0 ? "+" : "-");
					stateDraw.addState(temp, rconf_>0 ? CL_good : CL_danger,
						(rconf_ >0 ? "혼란 저항이 높아졌습니다." : "혼란 저항이 낮아졌습니다."), this);
				}
			}


			if(you.s_confuse)
			{
				stateDraw.addState("혼란", CL_danger,
					"이동을 포함한 대부분의 행동을 제대로 할 수 없습니다.", this);
			}
			if(you.s_frozen)
			{
				stateDraw.addState("빙결", you.s_frozen>5 ? CL_blue : CL_bad,
					"이동속도가 저하됩니다.", this);
			}
			if(you.s_elec)
			{
				stateDraw.addState("방전", CL_normal,
					"일정 턴마다 주변의 생물체에게 전기공격이 가해집니다.", this);
			}
			if(you.s_paralyse)
			{
				stateDraw.addState("마비", CL_danger,
					"움직일 수 없습니다!", this);
			}
			if(you.s_levitation)
			{
				stateDraw.addState("비행", you.s_levitation>10 ? CL_white_blue : CL_blue,
					"하늘을 날아 몇몇 지형물체를 뛰어넘을 수 있습니다.", this);
			}
			else if(you.s_glow)
			{
				stateDraw.addState("빛남", CL_white_blue,
					"당신에게 빛이 비춰지고 있어 회피율이 낮아집니다.", this);
			}
			if(you.s_graze && !you.s_super_graze)
			{
				stateDraw.addState("그레이즈", you.s_graze<0 ? CL_normal : you.s_graze>10 ? CL_white_blue : CL_blue,
					"회피 가능한 탄막을 손쉽게 피할 수 있습니다.", this);
			}
			if(you.s_silence)
			{
				stateDraw.addState("정적", you.s_silence>5 ? CL_white_blue : CL_blue,
					"당신은 소리내는 행동을 할 수 없습니다.", this);
			}
			if(you.s_sick)
			{
				stateDraw.addState("병", you.s_sick>50 ? (you.s_sick>100 ? CL_danger : CL_small_danger) : CL_warning,
					"지속시간동안 자연 체력회복이 불가능합니다.", this);
			}
			if(you.s_veiling)
			{
				stateDraw.addState("베일링", CL_normal,
					"당신에게 근접공격을 하려는 상대에게 데미지를 입히고 사라집니다.", this);
			}
			if(you.s_invisible || you.togle_invisible)
			{
				bool glow_ = (you.s_glow || you.GetBuffOk(BUFFSTAT_HALO));
				stateDraw.addState("투명", glow_? CL_bad : (you.togle_invisible ? CL_speak : you.s_invisible>10 ? CL_white_blue : CL_blue),
					glow_? "투명해졌지만 빛나고 있기에 아무런 효과가 없습니다." :"투명해져서 투명을 볼 수 없는 적의 눈에 띄지 않습니다.", this);
			}
			if(you.s_swift)
			{
				stateDraw.addState(you.s_swift>0 ? "신속" : "이속감소", you.s_swift>10 ? CL_white_blue : (you.s_swift>0 ? CL_blue : CL_danger),
					you.s_swift > 0 ? "당신의 이동속도는 빠릅니다." : "당신의 이동속도는 느립니다.", this);
			}
			if(you.s_superman)
			{
				stateDraw.addState("초인", you.s_superman>5 ? CL_white_puple : CL_magic,
					"초인과 같이 이동속도가 빨라졌습니다.", this);
			}
			if(you.s_slaying)
			{
				sprintf_s(temp,128,"전투력(%s%d)",you.s_slaying>0?"+":"",you.s_slaying);
				stateDraw.addState(temp, you.s_slaying>0 ? CL_white_blue : CL_danger,
					"당신의 근접, 탄막공격력이 변화되었습니다.", this);
			}
			if (you.s_none_move)
			{
				stateDraw.addState("이동불가", CL_danger,
					"무엇인가에 잡혀서 이동할 수 없습니다.", this);
			}
			if (you.s_night_sight_turn)
			{
				stateDraw.addState("야맹증", CL_danger,
					"당신은 한치앞도 보이지않습니다. 당신의 시야가 극적으로 줄어듭니다.", this);
			}
			if (you.s_sleep>0)
			{
				sprintf_s(temp, 128, "졸음(%02d)", min(99,you.s_sleep));
				stateDraw.addState(temp, CL_small_danger,
					"졸음이 오고있습니다. 수치가 100이 되면 강제로 잠을 잡니다.", this);
			}
			else if (you.s_sleep<0)
			{
				stateDraw.addState("수면", CL_danger,
					"당신은 잠을 자고 있습니다!", this);
			}
			if (you.s_pure>0 && you.s_pure_turn)
			{
				D3DCOLOR color_ = you.s_pure_turn == -1 ? CL_normal :
					you.s_pure < 10 ? CL_bad :
					you.s_pure < 20 ? CL_darkblue :
					you.s_pure < 30 ? CL_blue : CL_white_blue;
				if(you.s_pure_turn == -1)
					sprintf_s(temp, 128, "순화");
				else
					sprintf_s(temp, 128, "순화(%d단계)", you.s_pure < 10 ? 0 :(you.s_pure <20 ? 1 : (you.s_pure < 30 ? 2 : 3)));
				stateDraw.addState(temp, color_,
					((you.s_pure_turn == -1) || you.GetProperty(TPT_PURE_SYSTEM)) ? "두루마리, 물약을 사용할 수 없습니다. (일부 부여형 두루마리는 가능)" :
					((you.s_pure_turn == -1) || you.s_pure >= 30) ? "스펠카드, 두루마리, 물약을 사용할 수 없습니다. (일부 부여형 두루마리는 가능)" :
					(you.s_pure >= 20) ? "스펠카드, 두루마리를 사용할 수 없습니다. (일부 부여형 두루마리는 가능)" :
					(you.s_pure >= 10) ? "스펠카드를 사용할 수 없습니다." : "당신은 아직 순화의 패널티를 받고있지 않습니다." , this);
			}
		}

	}
	//바탕 타일 그리기
	int x_ = you.GetDisplayPos().x-8;
	int y_ = you.GetDisplayPos().y-8;
	for(int i=0;i<17;i++)
	{
		for(int j=0;j<17;j++)
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
					env[current_level].drawTile(pSprite, i + x_, j + y_, i*32.0f + 20.0f, j*32.0f + 20.0f, you.turn, sight);
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
	//미니맵 그리기
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
							dot_floor.draw(pSprite,GetDotX(i+offset_.x),GetDotY(j+offset_.y),255);
						else
							dot_mapping_floor.draw(pSprite,GetDotX(i+offset_.x),GetDotY(j+offset_.y),255);
						break;
					case DOT_WALL:
						if(env[current_level].isExplore(i,j))
							dot_wall.draw(pSprite,GetDotX(i+offset_.x),GetDotY(j+offset_.y),255);
						else
							dot_mapping_wall.draw(pSprite,GetDotX(i+offset_.x),GetDotY(j+offset_.y),255);
						break;
					case DOT_DOOR:
						dot_door.draw(pSprite,GetDotX(i+offset_.x),GetDotY(j+offset_.y),255);
						break;
					case DOT_UP:
						dot_up.draw(pSprite,GetDotX(i+offset_.x),GetDotY(j+offset_.y),255);
						break;
					case DOT_DOWN:
						dot_down.draw(pSprite,GetDotX(i+offset_.x),GetDotY(j+offset_.y),255);
						break;
					case DOT_TEMPLE:
						dot_temple.draw(pSprite,GetDotX(i+offset_.x),GetDotY(j+offset_.y),255);
						break;
					case DOT_SEA:
						dot_sea.draw(pSprite,GetDotX(i+offset_.x),GetDotY(j+offset_.y),255);
						break;
					}
				}
			}
		}
	}



	//아이템그리기
	{
		list<item>::iterator it; 
		bool many_item = false;
		bool auto_pick_ = false;
		for(it = env[current_level].item_list.begin(); it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++; 
				
			if(it == env[current_level].item_list.end() || (*temp).position != (*it).position)
			{
				if(env[current_level].isInSight((*temp).position))
				{	
					if(abs((*temp).position.x - x_-8)<=8 && abs((*temp).position.y - y_-8)<=8)
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
					dot_item.draw(pSprite, GetDotX((*temp).position.x + offset_.x), GetDotY((*temp).position.y + offset_.y), 255);
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


	//바닥 효과 그리기
	{
	list<floor_effect>::iterator it;
	for (it = env[current_level].floor_list.begin(); it != env[current_level].floor_list.end(); it++)
	{
		if (env[current_level].isInSight((*it).position)) //더 추가해야할거. 볼수있다(투명아님).
		{
			if (abs((*it).position.x - x_ - 8) <= 8 && abs((*it).position.y - y_ - 8) <= 8)
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
				if (abs((*it).position.x - x_ - 8) <= 8 && abs((*it).position.y - y_ - 8) <= 8)
				{
					it->draw(pSprite, pfont, ((*it).position.x - x_)*32.0f + 20.0f, ((*it).position.y - y_)*32.0f + 20.0f);
				}
			}
		}
	}

	//플레이어 그리기
	{
		if (!you.s_timestep && abs(you.position.x - x_ - 8) <= 8 && abs(you.position.y - y_ - 8) <= 8)
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
		dot_player.draw(pSprite, GetDotX(you.position.x + offset_.x), GetDotY(you.position.y + offset_.y), 255);
	}


	//몹그리기
	{
		vector<monster>::iterator it;

		for (it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if ((*it).isLive() && (*it).isYourShight()) //더 추가해야할거. 볼수있다(투명아님).
			{
				if (abs((*it).position.x - x_ - 8) <= 8 && abs((*it).position.y - y_ - 8) <= 8)
				{
					(*it).draw(pSprite, pfont, ((*it).position.x - x_)*32.0f + 20.0f, ((*it).position.y - y_)*32.0f + 20.0f);
				}
				if (!((*it).flag & M_FLAG_UNHARM))
				{
					dot_monster.draw(pSprite, GetDotX((*it).position.x + offset_.x), GetDotY((*it).position.y + offset_.y), 255);
				}
			}
			else if(it->isLive() &&	you.god == GT_SATORI && !you.GetPunish(GT_SATORI) && pietyLevel(you.piety)>=3
				&& GetPositionGap((*it).position.x, (*it).position.y, you.position.x, you.position.y) <= satori_sight()
				)
			{
				if(abs((*it).position.x -x_-8)<=8 && abs((*it).position.y -y_-8)<=8)
				{
					(*it).simple_draw(pSprite,pfont,((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f+20.0f);
				}
				if (!((*it).flag & M_FLAG_UNHARM))
				{
					dot_monster.draw(pSprite, GetDotX((*it).position.x + offset_.x), GetDotY((*it).position.y + offset_.y), 255);

				}
			}
		}
	}
	//그림자 그리기
	{
		list<shadow>::iterator it;
		
		for(it = env[current_level].shadow_list.begin(); it != env[current_level].shadow_list.end(); it++)
		{
			if(abs((*it).position.x -x_-8)<=8 && abs((*it).position.y -y_-8)<=8)
			{
				if(!env[current_level].isInSight((*it).position)) 
				{
					(*it).image->draw(pSprite,((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f+20.0f,D3DCOLOR_XRGB(128,128,128));
				}
			}
			switch((*it).type)
			{
			case SWT_MONSTER:
				if (!(*it).unharm) {
					dot_monster.draw(pSprite, GetDotX((*it).position.x + offset_.x), GetDotY((*it).position.y + offset_.y), 255);
				}
				break;
			case SWT_ITEM:
				dot_item.draw(pSprite,GetDotX((*it).position.x+offset_.x),GetDotY((*it).position.y+offset_.y),255);
				break;
			}
		}
	}

	//안개그리기
	if(you.s_weather >= 1 && you.s_weather_turn > 0)
	{
		for (int i = 0; i < 17; i++)
		{
			for (int j = 0; j < 17; j++)
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
				if(abs((*it).position.x -x_-8)<=8 && abs((*it).position.y -y_-8)<=8)
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
		if(!env[current_level].isBamboo())
			sight_rect.draw(pSprite,GetDotX(x_+8),GetDotY(y_+8),255);
	}




	//광기
	if(you.s_sleep < 0 || you.s_lunatic || map_effect || you.s_evoke_ghost)
	{
		int x_ = you.GetDisplayPos().x-8;
		int y_ = you.GetDisplayPos().y-8;
		for(int i=0;i<17;i++)
		{
			for(int j=0;j<17;j++)
			{
				if(i+x_>=0 && j+y_>=0 && i+x_<DG_MAX_X && j+y_<DG_MAX_Y)
				{
					if((env[current_level].isExplore(i+x_,j+y_) || env[current_level].isMapping(i+x_,j+y_)))
					{	
						bool sight = true;	
					
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
				if (abs((*it).position.x - x_ - 8) <= 8 && abs((*it).position.y - y_ - 8) <= 8)
				{
					RECT rc = { (LONG)(((*it).position.x - x_)*32.0f + 20.0f),(LONG)(((*it).position.y - y_)*32.0f - 10.0f), (LONG)option_mg.getWidth(), (LONG)option_mg.getHeight() };
					rc.left -= fontDesc.Width*(*it).GetName()->name.size() / 2;
					DrawTextUTF8(pfont,pSprite, (*it).GetName()->name.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
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
		for(;it != text_log.text_list.end();it++)
		{			
			RECT rc={ (LONG)x, (LONG)y, 32*17+16, (LONG)(y+fontDesc.Height)};
			DrawTextUTF8(pfont,pSprite, (*it)->text.c_str(), -1, &rc, DT_SINGLELINE , (*it)->color);
			if((*it)->enter)
			{
				x = 0;
				y+=fontDesc.Height;
			}
			else
			{
				x+=(*it)->width;
			}
		}
	}


	if(ReplayClass.play)
	{
		RECT rc={50, 400, option_mg.getWidth(), option_mg.getHeight()};
		DrawTextUTF8(pfont,pSprite,"리플레이 모드중", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
		rc.top += fontDesc.Height;	
		DrawTextUTF8(pfont,pSprite,"(z-일시정지 x-보통속도 c-배속)", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
	}
	drawInfoBox(pSprite, pfont);

}
extern POINT MousePoint;

void stateBox::addState(const char* name, D3DCOLOR color, const char* info, display_manager* display)
{
	int sizeOfName = strlen(name);
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
void display_manager::CheckMouseInfo(LPD3DXSPRITE pSprite, ID3DXFont* pfont, RECT& rc, int width_, int height_, const char* message)
{
	if (MousePoint.x >= rc.left*scale_x && MousePoint.x <= (rc.left + width_)*scale_x &&
		MousePoint.y >= rc.top*scale_y && MousePoint.y <= (rc.top + height_)*scale_y
		)

	{
		infobox.setBox(MousePoint.x/ scale_x, MousePoint.y/ scale_y, message);
	}
}
void display_manager::drawInfoBox(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	if (infobox.draw)
	{
		RECT rc_ = { infobox.x, infobox.y, infobox.x + infobox.x_size, infobox.y + infobox.y_size };
		if (rc_.left + infobox.x_size / 2  > option_mg.getWidthCommon()) {
			int i = rc_.left + infobox.x_size / 2 - option_mg.getWidthCommon();
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
void display_manager::item_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
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
		oss << "<인벤토리>  (아이템 갯수 " << you.item_list.size() << " / 52)";
		DrawTextUTF8(pfont,pSprite,oss.str().c_str(), -1, &rc, DT_NOCLIP,CL_normal);
		rc.top += fontDesc.Height;
		break;
	}
	default:
		break;
	}
	
	DrawTextUTF8(pfont,pSprite,item_view_message.c_str(), -1, &rc, DT_NOCLIP,CL_normal);
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
					DrawTextUTF8(pfont,pSprite,GetItemTypeSting(i), -1, &rc, DT_NOCLIP,CL_help);
					rc.top += 32;
					rc.left += 48;
					exist = true;
				}
				string temp;
				temp+=(*it).id;
				temp+=item_view[asctonum((*it).id)]?(item_num[asctonum((*it).id)]?" # ":" + "):" - ";
				temp+=(*it).GetName().c_str();
				if(equip)
					temp += (equip==1?"(장착)":(equip==2?"(왼손)":"(오른손)"));
				it->draw(pSprite, pfont, rc.left - 24, rc.top + 8);
				//(*it).image->draw(pSprite,rc.left-24,rc.top+8,D3DCOLOR_XRGB(255,255,255));
				DrawTextUTF8(pfont,pSprite,temp.c_str(), -1, &rc, DT_NOCLIP,(*it).item_color());
				rc.top += 32;
			}
		}
	}
	rc.top+=move+64;
	max_y = (rc.top-option_mg.getHeight()>0?rc.top-option_mg.getHeight():0);
}

void display_manager::log_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
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
		for(i = 0;i < view_length && it != text_log.text_list.end();it++)
		{			
			RECT rc={ (LONG)x, (LONG)y, (LONG)(x+(*it)->text.length()*fontDesc.Width), (LONG)(y+fontDesc.Height)};
			DrawTextUTF8(pfont,pSprite, (*it)->text.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, (*it)->color);
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
}

void display_manager::sub_text_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
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
}

void display_manager::start_spellview(char* message_)
{
	WaitForSingleObject(mutx, INFINITE);
	state = DT_SPELL;
	move = 0;
	item_view_message = message_;
	ReleaseMutex(mutx);
}

void display_manager::start_skillview(char* message_)
{
	WaitForSingleObject(mutx, INFINITE);
	state = DT_SKILL;
	move = 0;
	item_view_message = message_;
	ReleaseMutex(mutx);
}


void display_manager::start_itemview(item_view_type type, char* message_)
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
	}
	ReleaseMutex(mutx);
}

int GetDisplayMove()
{
	return DisplayManager.move;
}
void view_item(item_view_type type, char* message_)
{
	DisplayManager.start_itemview(type, message_);
}
void view_spell(char* message_)
{
	DisplayManager.start_spellview(message_);
}
void view_skill(char* message_)
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