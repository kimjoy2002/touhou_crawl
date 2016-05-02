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
#include "const.h"
#include "tribe.h"
#include "alchemy.h"
#include "tensi.h"
extern bool wizard_mode;

extern IDirect3DDevice9* Device; //디바이스포인터
extern IDirect3DVertexBuffer9* g_pVB; //버텍스버퍼포인터
extern D3DXMATRIXA16 g_BaseMatrix; //매트릭스포인터
extern LPD3DXSPRITE g_pSprite; //스프라이트포인터 
extern ID3DXFont* g_pfont;
extern HANDLE mutx;


display_manager DisplayManager;

DWORD FrameCnt = 0;
float TimeElapsed = 0;
float FPS = 0;

extern bool widesearch; //X커맨드용


int map_effect=0;//잠깐 나오는 맵의 반짝 이벤트


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
item_view_message("무슨 아이템을 고르겠습니까?"), image(NULL), log_length(1), move(0), max_y(1), sight_type(0), spell_sight(0)
{
	for(int i=0;i<52;i++)
		item_view[i] = 0;
}
void display_manager::Getfontinfor()
{
	g_pfont->GetDesc(&fontDesc);
	log_length = (WindowHeight-50) / fontDesc.Height;
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
void display_manager::text_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	if(image)
		image->draw(pSprite,255);
	RECT rc={50, 50-move, WindowWidth, WindowHeight};
	pfont->DrawTextA(pSprite,text.c_str(), -1, &rc, DT_NOCLIP,D3DCOLOR_XRGB(200,200,200));
}
void display_manager::spell_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{	
	int i=0;
	RECT rc={50, 50, WindowWidth, WindowHeight};
	char temp[100];
	char sp_char = (i<27)?('a'+i):('A'+i-27);
	pfont->DrawTextA(pSprite,"단축키 - 이름", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 200;
	pfont->DrawTextA(pSprite,"학파", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 200;
	pfont->DrawTextA(pSprite,"성공률", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 150;
	pfont->DrawTextA(pSprite,"레벨", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += fontDesc.Height;
	rc.left = 50;
	for(int i=0;i<52;i++)
	{
		if(you.MemorizeSpell[i])
		{
			spell_list spell_ = (spell_list)you.MemorizeSpell[i];
			char sp_char = (i<26)?('a'+i):('A'+i-26);
			sprintf_s(temp,100,"%c      - %s",sp_char,SpellString(spell_));
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += 200;
			pfont->DrawTextA(pSprite,GetSpellSchoolString(spell_).c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left = 450;
			sprintf_s(temp,100,"%-3d%%",you.GetSpellSuccess(spell_));
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += 150;
			sprintf_s(temp,100,"%d",SpellLevel(spell_));
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.top += fontDesc.Height;
			rc.left = 50;


		}
	}
}
void display_manager::property_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{	
	RECT rc={50, 50, WindowWidth, WindowHeight};
	char temp[256];
	int i =0;
	if(you.property_vector.empty())
	{
		pfont->DrawTextA(pSprite,"당신의 특성이 없습니다.", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		return;
	}
	pfont->DrawTextA(pSprite,"당신의 특성들 (알파벳을 누르면 상세한 정보다 나옵니다.)", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += fontDesc.Height*2;
	for(auto it = you.property_vector.begin(); it != you.property_vector.end(); it++)
	{
		char sp_char = (i<26)?('a'+i):('A'+i-26);
		sprintf_s(temp,256,"%c - ",sp_char);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*4;
		pfont->DrawTextA(pSprite,it->GetInfor().c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.top += fontDesc.Height;
		rc.left = 50;
		i++;
	}
	return;
}
void display_manager::skill2_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{	
	int i=0;
	RECT rc={50, 50, WindowWidth, WindowHeight};
	char temp[100];
	char sp_char = (i<27)?('a'+i):('A'+i-27);
	if(move == 0)
		pfont->DrawTextA(pSprite,"어느 스킬을 사용하겠습니까?", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
	else
		pfont->DrawTextA(pSprite,"어느 스킬의 설명을 보시겠습니까?", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
	rc.top += fontDesc.Height;


	pfont->DrawTextA(pSprite,"단축키 - 이름", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 250;
	pfont->DrawTextA(pSprite,"비용", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.left += 200;
	pfont->DrawTextA(pSprite,"성공률", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
	rc.top += fontDesc.Height;
	rc.left = 50;
	for(int i=0;i<26;i++)
	{
		if(you.MemorizeSkill[i])
		{
			skill_list skill_ = (skill_list)you.MemorizeSkill[i];
			char sp_char = ('a'+i);
			sprintf_s(temp,100,"%c      - %s",sp_char,SkillString(skill_));
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.left += 250;
			{
				int k = sprintf_s(temp,100,"%s",SkillCostString(skill_));
				pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			}
			rc.left = 500;
			sprintf_s(temp,100,"%3d%%",SkillDiffer(skill_));
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
			rc.top += fontDesc.Height;
			rc.left = 50;
		}
	}
	rc.left = 50;
	rc.top = WindowHeight - fontDesc.Height*3;
	{	
		if(move == 0)
			sprintf_s(temp,100,"!나 ?를 눌러서 설명을 볼 수 있습니다.");
		else		
			sprintf_s(temp,100,"!나 ?를 눌러서 스킬 사용을 할 수 있습니다.");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_help);
	}
}

void display_manager::skill_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	RECT rc={50, 50, WindowWidth, WindowHeight};
	char temp[100];
	int skt = 0, i=0;
	char sk_char = 'a';
	while(skt < SKT_MAX)
	{
		for(i = 0;i<1;i++)
		{

			sprintf_s(temp,100,"%c %c %8s %3d",you.skill[skt].level==27?' ':sk_char,(you.skill[skt].level==27?' ':(you.skill[skt].onoff?'+':'-')),skill_string((skill_type)skt),you.skill[skt].level);
			sk_char++;
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.skill[skt].level<27?(you.skill[skt].onoff?CL_STAT:CL_bad):CL_warning);
			rc.left += 150;
			//if(move ==0)
			if(you.skill[skt].level<27)
				sprintf_s(temp,100,"(%2d%%)",GetSkillPercent(you.skill[skt]));
			else 
				sprintf_s(temp,100,"");

			//else if(move == 1)
			//	sprintf_s(temp,100,"%d",you.skill[skt].aptit);
			//else
			//	sprintf_s(temp,100,"%d",you.skill[skt].exper);
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, you.skill[skt].level<27?(you.skill[skt].onoff?CL_STAT:CL_bad):CL_warning);
			rc.left += 50;
						
			sprintf_s(temp,100,"%3d",you.skill[skt].aptit);
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,GetSkillColor(you.skill[skt].aptit));
			


			rc.left += 250;
			if(sk_char == 'z'+1)
				sk_char = 'A';
			if(sk_char == 'p')
			{
				rc.left = 800;
				rc.top = 50-fontDesc.Height;
			}
		}
		rc.left -= 450*i;
		rc.top += fontDesc.Height;
		skt++;
	}
}
void display_manager::state_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	RECT rc={30, 10, WindowWidth, WindowHeight};
	char temp[100];
	sprintf_s(temp,100,"%s (%d레벨 %s %s %s)",you.user_name.name.c_str(),you.level,tribe_type_string[you.tribe],job_type_string[you.job],you.GetCharNameString()->c_str());
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_warning);
	rc.left += 300;
	sprintf_s(temp,100,"턴: %d",you.turn);	
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 200;
	if(you.god == GT_NONE)
	{
		sprintf_s(temp,100,"무신앙");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	else
	{
		sprintf_s(temp,100,"신앙: %s %c%c%c%c%c%c",GetGodString(you.god),pietyLevel(you.piety)>=1?'*':'.',pietyLevel(you.piety)>=2?'*':'.',pietyLevel(you.piety)>=3?'*':'.',pietyLevel(you.piety)>=4?'*':'.',pietyLevel(you.piety)>=5?'*':'.',pietyLevel(you.piety)>=6?'*':'.');
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;		

	sprintf_s(temp,100,"HP: %d/%d",you.hp,you.max_hp);
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"AC:%4d",you.ac);
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"힘  :%4d",you.s_str);
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;		

	sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp);
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"EV:%4d",you.ev);
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"민첩:%4d",you.s_dex);
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;		

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"SH:%4d",you.sh);
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"지능:%4d",you.s_int);
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left = 30;
	rc.top += fontDesc.Height;		
	rc.top += fontDesc.Height;		

	int resist_ = you.fire_resist - you.uniden_fire_resist;
	sprintf_s(temp,100,"화염저항: %c %c %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'),resist_>=2?'+':(resist_<=-2?'-':'.'),resist_>=3?'+':(resist_<=-3?'-':'.'));
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	resist_ = you.confuse_resist- you.uniden_confuse_resist;
	sprintf_s(temp,100,"혼란저항: %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	sprintf_s(temp,100,"무기: ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_WEAPON])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_WEAPON]->id,you.equipment[ET_WEAPON]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"맨손");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;


	resist_ = you.ice_resist - you.uniden_ice_resist;
	sprintf_s(temp,100,"냉기저항: %c %c %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'),resist_>=2?'+':(resist_<=-2?'-':'.'),resist_>=3?'+':(resist_<=-3?'-':'.'));
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	resist_ = you.invisible_view- you.uniden_invisible_view;
	sprintf_s(temp,100,"투명보기: %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	sprintf_s(temp,100,"탄막: ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.throw_weapon)
	{
		sprintf_s(temp,100,"%c) %s",you.throw_weapon->id,you.throw_weapon->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.throw_weapon->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;


	resist_ = you.poison_resist - you.uniden_poison_resist;
	sprintf_s(temp,100,"독저항  : %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	resist_ = you.power_keep- you.uniden_power_keep;
	sprintf_s(temp,100,"파워유지: %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	sprintf_s(temp,100,"몸통: ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_ARMOR])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_ARMOR]->id,you.equipment[ET_ARMOR]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_ARMOR]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;


	resist_ = you.elec_resist - you.uniden_elec_resist;
	sprintf_s(temp,100,"전기저항: %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"방패: ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_SHIELD])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_SHIELD]->id,you.equipment[ET_SHIELD]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_SHIELD]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	
	//resist_ = you.poison_resist - you.uniden_poison_resist;
	//sprintf_s(temp,100,"독저항  : %c" ,resist_>=1?'+':(resist_<=-1?'-':'.'));
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, resist_>0?CL_good:(resist_<0?CL_danger:CL_normal));
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"머리: ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_HELMET])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_HELMET]->id,you.equipment[ET_HELMET]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_HELMET]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

	
	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"망토: ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_CLOAK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_CLOAK]->id,you.equipment[ET_CLOAK]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_CLOAK]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
	

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"손  : ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_GLOVE])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_GLOVE]->id,you.equipment[ET_GLOVE]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_GLOVE]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;


	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"발  : ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*6;
	if(you.equipment[ET_BOOTS])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_BOOTS]->id,you.equipment[ET_BOOTS]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_BOOTS]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
	

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"목걸이  : ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*10;
	if(you.equipment[ET_NECK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_NECK]->id,you.equipment[ET_NECK]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_NECK]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;

		

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"왼반지  : ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*10;
	if(you.equipment[ET_LEFT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_LEFT]->id,you.equipment[ET_LEFT]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_LEFT]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
			

	//sprintf_s(temp,100,"MP: %d/%d",you.mp,you.max_mp); //여기엔 돈이
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	//sprintf_s(temp,100,"SH:%4d",you.sh);
	//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += 150;
	sprintf_s(temp,100,"오른반지: ");
	pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);
	rc.left += fontDesc.Width*10;
	if(you.equipment[ET_RIGHT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_RIGHT]->id,you.equipment[ET_RIGHT]->GetName().c_str());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_RIGHT]->item_color());
	}
	else
	{
		sprintf_s(temp,100,"없음");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_bad);
	}
	rc.left = 30;
	rc.top += fontDesc.Height;
}

void display_manager::game_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	{
		int i=0;
		RECT rc={32*16+50, 10, WindowWidth, WindowHeight};
		char temp[128];
		sprintf_s(temp,128,"%d레벨",you.level);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*7;
		pfont->DrawTextA(pSprite,you.user_name.name.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.top += fontDesc.Height;
		rc.left -= fontDesc.Width*7;
		pfont->DrawTextA(pSprite,tribe_type_string[you.tribe], -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*(strlen(tribe_type_string[you.tribe])+1);
		pfont->DrawTextA(pSprite,job_type_string[you.job], -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*(strlen(job_type_string[you.job])+1);
		pfont->DrawTextA(pSprite,you.GetCharNameString()->c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left = 32*16+50;
		rc.top += fontDesc.Height;


		if(you.god == GT_NONE)
		{
			sprintf_s(temp,128,"무신앙");
		}
		else
		{
			sprintf_s(temp,128,"신앙: %s %c%c%c%c%c%c",GetGodString(you.god),pietyLevel(you.piety)>=1?'*':'.',pietyLevel(you.piety)>=2?'*':'.',pietyLevel(you.piety)>=3?'*':'.',pietyLevel(you.piety)>=4?'*':'.',pietyLevel(you.piety)>=5?'*':'.',pietyLevel(you.piety)>=6?'*':'.');
		}
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);

		rc.top += fontDesc.Height;

		sprintf_s(temp,128,"HP: %d/%d",you.hp,you.max_hp);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*14;
		{
			int Hp_bar = max(you.hp*18/you.max_hp,you.prev_hp*18/you.max_hp);
			int s_Hp_bar = min(you.hp*18/you.max_hp,you.prev_hp*18/you.max_hp);
			D3DCOLOR color_ = (you.hp*18/you.max_hp>you.prev_hp*18/you.max_hp)?CL_dark_good:CL_danger;

			for(i = 0;i<s_Hp_bar;i++)
			{
				pfont->DrawTextA(pSprite,"=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_good);
				rc.left += fontDesc.Width;
			}
			for(;i<Hp_bar;i++)
			{
				pfont->DrawTextA(pSprite,"=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, color_);
				rc.left += fontDesc.Width;
			}
			for(;i<18;i++)
			{
				pfont->DrawTextA(pSprite,"=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_bad);
				rc.left += fontDesc.Width;
			}
		}
		rc.left -= fontDesc.Width*32;


		rc.top += fontDesc.Height;
		sprintf_s(temp,128,"MP: %d/%d",you.mp,you.max_mp);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		if(you.max_mp)
		{
			rc.left += fontDesc.Width*14;
			for(i = 0;i<you.mp*18/you.max_mp;i++)
			{
				pfont->DrawTextA(pSprite,"=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_good);
				rc.left += fontDesc.Width;
			}
			for(;i<18;i++)
			{
				pfont->DrawTextA(pSprite,"=", -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_bad);
				rc.left += fontDesc.Width;
			}
			rc.left -= fontDesc.Width*32;
		}



		int left_ =0 ;

		rc.top += fontDesc.Height;
		int pow_ = min(you.power,500);
		img_item_food_p_item.draw(pSprite,rc.left+7,rc.top+7,255);
		left_ = sprintf_s(temp,128,"   %d.%02d",pow_/100,pow_%100);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, pow_<=100?CL_danger:(pow_<=200?CL_warning:(pow_==500?CL_good:CL_normal)));
		//임시		
		//rc.left += fontDesc.Width*left_;
		//sprintf_s(temp,50,"%6d",you.hunger);
		//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, you.s_might?CL_white_blue:CL_STAT);
		rc.left = 32*16+50;




		rc.top += fontDesc.Height;
		left_ = sprintf_s(temp,128,"AC:");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;
				
		int temp_buff_value_ = 0;


		left_ = sprintf_s(temp,128,"%4d",you.ac);
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_AC)+ (you.alchemy_buff == ALCT_DIAMOND_HARDNESS)?5:0;
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:CL_STAT);
		rc.left += fontDesc.Width*left_;

		left_ = sprintf_s(temp,128,"    힘  :");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;

		if(you.s_str == you.m_str)
			sprintf_s(temp,128,"%4d",you.s_str);
		else
			sprintf_s(temp,128,"%4d (%2d)",you.s_str,you.m_str);
		
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_STR);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:(you.s_str != you.m_str)?CL_warning:CL_STAT);
		rc.left = 32*16+50;

		rc.top += fontDesc.Height;
		left_ = sprintf_s(temp,128,"EV:");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;

		
		left_ = sprintf_s(temp,128,"%4d",you.ev);
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_EV);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:CL_STAT);
		rc.left += fontDesc.Width*left_;

		left_ = sprintf_s(temp,128,"    민첩:");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;


		if(you.s_dex == you.m_dex)
			sprintf_s(temp,128,"%4d",you.m_dex);
		else
			sprintf_s(temp,128,"%4d (%2d)",you.s_dex,you.m_dex);
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_DEX);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:(you.s_dex != you.m_dex)?CL_warning:CL_STAT);
		rc.left = 32*16+50;

		rc.top += fontDesc.Height;
		left_ = sprintf_s(temp,128,"SH:");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;

		left_ = sprintf_s(temp,128,"%4d",you.sh);
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_SH);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:CL_STAT);
		rc.left += fontDesc.Width*left_;

		left_ = sprintf_s(temp,128,"    지능:");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*left_;



		if(you.s_int == you.m_int)
			sprintf_s(temp,128,"%4d",you.m_int);
		else
			sprintf_s(temp,128,"%4d (%2d)",you.s_int,you.m_int);
		temp_buff_value_ = you.GetBuffOk(BUFFSTAT_INT);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, temp_buff_value_>0?CL_white_blue:temp_buff_value_<0?CL_small_danger:(you.s_int != you.m_int)?CL_warning:CL_STAT);
		rc.left = 32*16+50;

		rc.top += fontDesc.Height;
		sprintf_s(temp,128,"무기: ");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
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
						pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
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

						pfont->DrawTextA(pSprite,tempchar2, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
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
			
					pfont->DrawTextA(pSprite,tempchar2, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.equipment[ET_WEAPON]->item_color());
					rc.left = 32*16+50;
					rc.top +=fontDesc.Height;
					max_len_ = 36;
				}
			}
		}
		else
		{
			sprintf_s(temp,128,"맨손");
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
			rc.left = 32*16+50;
			rc.top +=fontDesc.Height;
		}
		//rc.left -= fontDesc.Width*6;

		//rc.top += fontDesc.Height;
		sprintf_s(temp,128,"탄막: ");
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*6;
		if(you.throw_weapon)
		{
			sprintf_s(temp,128,"%c) %s",you.throw_weapon->id,you.throw_weapon->GetName().c_str());
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.throw_weapon->item_color());
		}
		else
		{
			sprintf_s(temp,128,"없음");
			pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
		}
		rc.left -= fontDesc.Width*6;

		rc.top += fontDesc.Height;
		sprintf_s(temp,128,"%s",CurrentLevelString());
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		rc.left += fontDesc.Width*15;
		sprintf_s(temp,128,"턴: %g (%g)",you.real_turn/10.0f, you.prev_real_turn/10.0f);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);		
		rc.left -= fontDesc.Width*15;
		rc.top += fontDesc.Height;
		//sprintf_s(temp,128,"남은스킬경험치: %d",you.skill_exper);
		//pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_STAT);
		//rc.top += fontDesc.Height;

		{ //상태이상 표시!
			/*const char *state_str;*/
			/*int hunger = you.GetHunger();
			if(hunger != HT_NORMAL)
			{
				state_str = state_string[hunger];
				pfont->DrawTextA(pSprite,state_str, -1, &rc, DT_SINGLELINE | DT_NOCLIP,hunger==HT_STARVING?CL_danger:(hunger<=HT_HUNGRY?CL_warning:CL_good));
				rc.left += fontDesc.Width*(strlen(state_str)+1);				
			}*/
			if(wizard_mode)
			{
				sprintf_s(temp,128,"위험도(%d)",you.tension_gauge);
				pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_small_danger);
				//rc.left += fontDesc.Width*(13+(you.as_penalty>9?1:0));	
				rc.left = 32*16+50;
				rc.top +=fontDesc.Height;
			}
			if(you.as_penalty>0)
			{
				D3DCOLOR color_ = you.as_penalty>you.GetPenaltyMinus(3)?CL_danger: //끔찍
					you.as_penalty>you.GetPenaltyMinus(2)?CL_small_danger: //이동패널티
					you.as_penalty>you.GetPenaltyMinus(1)?CL_warning: //명중
					CL_bad;
				sprintf_s(temp,128,"장비패널티(%d)",you.as_penalty);
				pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,color_);
				//rc.left += fontDesc.Width*(13+(you.as_penalty>9?1:0));	
				rc.left = 32*16+50;
				rc.top +=fontDesc.Height;
			}
			if(you.GetStatPanalty())
			{
				pfont->DrawTextA(pSprite,"스탯패널티", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_danger);
				rc.left += fontDesc.Width*11;
			}
			if(you.s_trans_panalty)
			{
				pfont->DrawTextA(pSprite,"시공부작용", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_trans_panalty<=3?CL_bad:(you.s_trans_panalty<10?CL_warning:CL_small_danger));
				rc.left += fontDesc.Width*11;
			}
			if(you.s_spellcard)
			{
				pfont->DrawTextA(pSprite,"스펠카드", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_spellcard>5?CL_white_blue:CL_blue);
				rc.left += fontDesc.Width*9;	
			}
			if(you.s_autumn)
			{
				pfont->DrawTextA(pSprite,"공기화", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_autumn);
				rc.left += fontDesc.Width*7;
			}
			if(you.s_wind)
			{
				pfont->DrawTextA(pSprite,"건신초래풍", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_white_blue);
				rc.left += fontDesc.Width*11;
			}
			if(you.s_knife_collect)
			{
				pfont->DrawTextA(pSprite,"탄막회수", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_white_blue);
				rc.left += fontDesc.Width*9;
			}
			if(you.s_drunken)
			{
				pfont->DrawTextA(pSprite,"음주", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_warning);
				rc.left += fontDesc.Width*5;
			}
			if(you.s_lunatic)
			{
				pfont->DrawTextA(pSprite,"광기", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_danger);
				rc.left += fontDesc.Width*5;
			}
			if(you.s_catch)
			{
				pfont->DrawTextA(pSprite,"잡기", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_yuigi);
				rc.left += fontDesc.Width*5;

			}
			if(you.s_ghost)
			{
				pfont->DrawTextA(pSprite,"유령", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_ghost>1?CL_white_blue:CL_yuyuko);
				rc.left += fontDesc.Width*5;
			}
			if(you.s_dimension)
			{
				pfont->DrawTextA(pSprite,"차원고정", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_dimension>3?CL_yukari:CL_blue);
				rc.left += fontDesc.Width*9;
			}
			if(you.s_mirror)
			{
				pfont->DrawTextA(pSprite,"반사", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
				rc.left += fontDesc.Width*5;

			}
			if(you.s_paradox)
			{
				pfont->DrawTextA(pSprite,"패러독스", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_white_blue);
				rc.left += fontDesc.Width*9;
			}
			if(you.s_the_world)
			{
				pfont->DrawTextA(pSprite,"시간정지", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_the_world>1?CL_white_blue:CL_blue);
				rc.left += fontDesc.Width*9;
			}
			

			if(you.power<=200)
			{
				pfont->DrawTextA(pSprite,"파워부족", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.power<=100?CL_danger:CL_warning);
				rc.left += fontDesc.Width*9;
			}
			if(you.s_poison)
			{
				pfont->DrawTextA(pSprite,"독", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_poison<=50?CL_warning:(you.s_poison<=100?CL_small_danger:CL_danger));
				rc.left += fontDesc.Width*3;	
			}
			if(you.s_tele)
			{
				pfont->DrawTextA(pSprite,"공간", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_blue);
				rc.left += fontDesc.Width*5;	
			}
			if((you.s_haste || you.alchemy_buff == ALCT_HASTE) && !you.s_slow)
			{
				pfont->DrawTextA(pSprite,"가속", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.alchemy_buff == ALCT_HASTE?CL_alchemy:(you.s_haste>10?CL_white_blue:CL_blue));
				rc.left += fontDesc.Width*5;	
			}
			else if(you.s_slow && !(you.s_haste || you.alchemy_buff == ALCT_HASTE))
			{
				pfont->DrawTextA(pSprite,"감속", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_danger);
				rc.left += fontDesc.Width*5;	
			}
			else if((you.s_haste || you.alchemy_buff == ALCT_HASTE) && you.s_slow)
			{
				pfont->DrawTextA(pSprite,"가속+감속", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_magic);
				rc.left += fontDesc.Width*10;	

			}
			if(you.alchemy_buff == ALCT_STONE_FIST)
			{				
				pfont->DrawTextA(pSprite,"돌주먹", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_alchemy);
				rc.left += fontDesc.Width*7;	
			}
			if(you.alchemy_buff == ALCT_DIAMOND_HARDNESS)
			{
				pfont->DrawTextA(pSprite,"다이아", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_alchemy);
				rc.left += fontDesc.Width*7;
			}
			if(you.alchemy_buff == ALCT_POISON_BODY)
			{				
				pfont->DrawTextA(pSprite,"포이즌", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_alchemy);
				rc.left += fontDesc.Width*7;	
			}
			if(you.alchemy_buff == ALCT_STONE_FORM)
			{				
				pfont->DrawTextA(pSprite,"무념무상", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_alchemy);
				rc.left += fontDesc.Width*9;	
			}



			if(you.s_confuse)
			{
				pfont->DrawTextA(pSprite,"혼란", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_danger);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_frozen)
			{
				pfont->DrawTextA(pSprite,"빙결", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_frozen>5?CL_blue:CL_bad);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_elec)
			{
				pfont->DrawTextA(pSprite,"방전", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_paralyse)
			{
				pfont->DrawTextA(pSprite,"마비", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_danger);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_levitation)
			{
				pfont->DrawTextA(pSprite,"부유", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_levitation>10?CL_white_blue:CL_blue);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_glow)
			{
				pfont->DrawTextA(pSprite,"발광", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_white_blue);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_graze)
			{
				pfont->DrawTextA(pSprite,"그레이즈", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_graze<0?CL_normal:you.s_graze>10?CL_white_blue:CL_blue);
				rc.left += fontDesc.Width*9;	
			}
			if(you.s_silence)
			{
				pfont->DrawTextA(pSprite,"정적", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_silence>5?CL_white_blue:CL_blue);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_sick)
			{
				pfont->DrawTextA(pSprite,"병", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_sick>50?(you.s_sick>100?CL_danger:CL_small_danger):CL_warning);
				rc.left += fontDesc.Width*3;	
			}
			if(you.s_veiling)
			{
				pfont->DrawTextA(pSprite,"베일링", -1, &rc, DT_SINGLELINE | DT_NOCLIP,CL_normal);
				rc.left += fontDesc.Width*7;	
			}
			if(you.s_invisible || you.togle_invisible)
			{
				pfont->DrawTextA(pSprite,"투명", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.togle_invisible?CL_speak:you.s_invisible>10?CL_white_blue:CL_blue);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_swift)
			{
				pfont->DrawTextA(pSprite,"신속", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_swift>10?CL_white_blue:CL_blue);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_superman)
			{
				pfont->DrawTextA(pSprite,"초인", -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_superman>5?CL_white_puple:CL_magic);
				rc.left += fontDesc.Width*5;	
			}
			if(you.s_slaying)
			{
				sprintf_s(temp,128,"전투력(%s%d)",you.s_slaying>0?"+":"",you.s_slaying);
				pfont->DrawTextA(pSprite,temp, -1, &rc, DT_SINGLELINE | DT_NOCLIP,you.s_slaying>0?CL_white_blue:CL_danger);
				rc.left += fontDesc.Width*(11+(you.s_slaying>9?1:0));
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
					
					if(!env[current_level].isExplore(i+x_,j+y_))
						env[current_level].dgtile[i+x_][j+y_].draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,D3DCOLOR_XRGB(160,160,255),you.turn);
					else if(env[current_level].dgtile[i+x_][j+y_].flag & FLAG_LIGHT)
						env[current_level].dgtile[i+x_][j+y_].draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,D3DCOLOR_XRGB(255,255,0),you.turn);
					else if(env[current_level].isInSight(coord_def(i+x_,j+y_)) && sight)
						env[current_level].dgtile[i+x_][j+y_].draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,D3DCOLOR_XRGB(255,255,255),you.turn);
					else
						env[current_level].dgtile[i+x_][j+y_].draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,D3DCOLOR_XRGB(128,128,128),you.turn);

					if(env[current_level].isInSight(coord_def(i+x_,j+y_)) && env[current_level].dgtile[i+x_][j+y_].flag & FLAG_SILENCE)
						img_effect_slience.draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,D3DCOLOR_ARGB(128,0,255,255));
					if(env[current_level].isInSight(coord_def(i+x_,j+y_)) && env[current_level].dgtile[i+x_][j+y_].flag & FLAG_VIOLET)
						img_effect_slience.draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,D3DCOLOR_ARGB(128,255,128,255));
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
							if(!env[current_level].isMonsterPos((*temp).position.x,(*temp).position.y))
							{
								img_effect_auto_pick.draw(pSprite,((*temp).position.x-x_)*32.0f+20.0f,((*temp).position.y-y_)*32.0f+20.0f,255);
							}
						}
					}
					dot_item.draw(pSprite,GetDotX((*temp).position.x+offset_.x),GetDotY((*temp).position.y+offset_.y),255);
				}
				many_item = false;
				auto_pick_ = false;
			}
			else
			{
				many_item = true;
				if(it == env[current_level].item_list.end() && (*temp).isautopick())
					auto_pick_ = true;
			}
		}
	}	


	//바닥 효과 그리기
	{
		list<floor_effect>::iterator it; 
		for(it = env[current_level].floor_list.begin(); it != env[current_level].floor_list.end();it++)
		{
			if(env[current_level].isInSight((*it).position)) //더 추가해야할거. 볼수있다(투명아님).
			{
				if(abs((*it).position.x -x_-8)<=8 && abs((*it).position.y -y_-8)<=8)
				{
					it->draw(pSprite,pfont,((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f+20.0f);
				}
			}
		}
	}
	
	//연기그리기
	{
		list<smoke>::iterator it; 
		for(it = env[current_level].smoke_list.begin(); it != env[current_level].smoke_list.end();it++)
		{
			if(env[current_level].isInSight((*it).position)) //더 추가해야할거. 볼수있다(투명아님).
			{
				if(abs((*it).position.x -x_-8)<=8 && abs((*it).position.y -y_-8)<=8)
				{
					it->draw(pSprite,pfont,((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f+20.0f);
				}
			}
		}
	}

	//플레이어 그리기
	{
		if(!you.s_timestep && abs(you.position.x - x_-8)<=8 && abs(you.position.y - y_-8)<=8)
		{
			you.image->draw(pSprite,(you.position.x-x_)*32.0f+20.0f,(you.position.y-y_)*32.0f+20.0f,255);
			if( you.GetHp() != you.GetMaxHp())
			{
				float max_rate_= (1/3.0f);

				int temp1_ = max(0,you.GetHp()) *32 / you.GetMaxHp();
				float hp_rate_ = (max_rate_ * temp1_);
				int hp_offset_ = (temp1_+1)/2-16;

				
				int temp2_ = max(0,you.prev_hp) *32 / you.GetMaxHp();
				float p_hp_rate_ = (max_rate_ * temp2_);
				int p_hp_offset_ = (temp2_+1)/2 -16;
				
				dot_floor.draw(pSprite,(you.position.x-x_)*32.0f+20.0f,(you.position.y-y_)*32.0f+36.0f,0.0f,max_rate_ * 32.0f,0.5f,255);
				dot_monster.draw(pSprite,(you.position.x-x_)*32.0f+20.0f+p_hp_offset_,(you.position.y-y_)*32.0f+36.0f,0.0f,p_hp_rate_,0.5f,255);
				dot_item.draw(pSprite,(you.position.x-x_)*32.0f+20.0f+hp_offset_,(you.position.y-y_)*32.0f+36.0f,0.0f,hp_rate_,0.5f,255);
			}
		}
		dot_player.draw(pSprite,GetDotX(you.position.x+offset_.x),GetDotY(you.position.y+offset_.y),255);
	}


	//몹그리기
	{
		vector<monster>::iterator it;
		
		for(it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if((*it).isLive() && (*it).isYourShight()) //더 추가해야할거. 볼수있다(투명아님).
			{
				if(abs((*it).position.x -x_-8)<=8 && abs((*it).position.y -y_-8)<=8)
				{
					(*it).draw(pSprite,pfont,((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f+20.0f);
					if((*it).isUnique() || (*it).image == &img_mons_default)
					{
						RECT rc={((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f-10.0f, WindowWidth, WindowHeight};
						rc.left -= fontDesc.Width*(*it).GetName()->name.size()/2;
						pfont->DrawTextA(pSprite,(*it).GetName()->name.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, CL_normal);	
					}
				}
				dot_monster.draw(pSprite,GetDotX((*it).position.x+offset_.x),GetDotY((*it).position.y+offset_.y),255);
			}
			else if(it->isLive() &&	you.god == GT_SATORI && !you.punish[GT_SATORI] && pietyLevel(you.piety)>=3
				&& GetPositionGap((*it).position.x, (*it).position.y, you.position.x, you.position.y) <= satori_sight()
				)
			{
				if(abs((*it).position.x -x_-8)<=8 && abs((*it).position.y -y_-8)<=8)
				{
					(*it).simple_draw(pSprite,pfont,((*it).position.x-x_)*32.0f+20.0f,((*it).position.y-y_)*32.0f+20.0f);
				}
				dot_monster.draw(pSprite,GetDotX((*it).position.x+offset_.x),GetDotY((*it).position.y+offset_.y),255);
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
				dot_monster.draw(pSprite,GetDotX((*it).position.x+offset_.x),GetDotY((*it).position.y+offset_.y),255);
				break;
			case SWT_ITEM:
				dot_item.draw(pSprite,GetDotX((*it).position.x+offset_.x),GetDotY((*it).position.y+offset_.y),255);
				break;
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
	if(you.s_lunatic || map_effect)
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
						else if(you.s_lunatic)
							img_effect_lunatic.draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,80);
							
							//env[current_level].dgtile[i+x_][j+y_].draw(pSprite,i*32.0f+20.0f,j*32.0f+20.0f,D3DCOLOR_XRGB(160,160,255));
					}
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
			RECT rc={x, y, 32/**16+16*/, y+fontDesc.Height};
			pfont->DrawTextA(pSprite, (*it)->text.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, (*it)->color);
			if((*it)->enter)
			{
				x = 0;
				y+=fontDesc.Height;
			}
			else
			{
				x+=(*it)->text.length()*fontDesc.Width;
			}
		}
	}
}
void display_manager::item_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
	RECT rc={30, 10-move, WindowWidth, WindowHeight};
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
	case IVT_CURSE_ENCHANT:
		char temp[50];
		sprintf_s(temp,50,"<인벤토리>  (아이템 갯수 %d / 52)", you.item_list.size()/*,you.item_weight,you.max_item_weight*/);
		pfont->DrawTextA(pSprite,temp, -1, &rc, DT_NOCLIP,CL_normal);
		rc.top += fontDesc.Height;
		break;
	default:
		break;
	}
	
	pfont->DrawTextA(pSprite,item_view_message.c_str(), -1, &rc, DT_NOCLIP,CL_normal);
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
	case IVT_SPELLCARD:
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
		if((item_vt == IVT_EQ_WEAPON && i != ITMS_WEAPON) || 
			((item_vt == IVT_EQ_ARMOR || item_vt == IVT_UEQ_ARMOR || item_vt == IVT_ARMOR || item_vt == IVT_ARMOR_ENCHANT)  && i != ITMS_ARMOR)
			)
			continue;
		if(item_vt == IVT_FOOD && i != ITMS_FOOD)
			continue;
		if(item_vt == IVT_POTION && i != ITMS_POTION)
			continue;
		if(item_vt == IVT_SCROLL && i != ITMS_SCROLL && i != ITMS_BOOK)
			continue;
		if( (item_vt == IVT_EQ_JEWELRY || item_vt == IVT_UEQ_JEWELRY ) && i != ITMS_JEWELRY)
			continue;
		if(item_vt == IVT_SPELLCARD && i != ITMS_SPELL)
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

				if(item_vt == IVT_ARMOR_ENCHANT && !(*it).isEnhantable())
					continue;				
				if(item_vt == IVT_CURSE_ENCHANT && ( !(it->curse) || !(it->identify_curse)))
					continue;				


				if(!exist)
				{
					rc.top += 16;
					rc.left -= 48;
					pfont->DrawTextA(pSprite,GetItemTypeSting(i), -1, &rc, DT_NOCLIP,CL_help);
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
				(*it).image->draw(pSprite,rc.left-24,rc.top+8,D3DCOLOR_XRGB(255,255,255));
				pfont->DrawTextA(pSprite,temp.c_str(), -1, &rc, DT_NOCLIP,(*it).item_color());
				rc.top += 32;
			}
		}
	}
	rc.top+=move+64;
	max_y = (rc.top-WindowHeight>0?rc.top-WindowHeight:0);
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
			RECT rc={x, y, x+(*it)->text.length()*fontDesc.Width, y+fontDesc.Height};
			pfont->DrawTextA(pSprite, (*it)->text.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, (*it)->color);
			if((*it)->enter)
			{
				x = 0;
				y+=fontDesc.Height;
				i++;
			}
			else
			{
				x+=(*it)->text.length()*fontDesc.Width;
			}
		}
	}
}

void display_manager::sub_text_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont)
{
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
			RECT rc={x, y, x+(*it)->text.length()*fontDesc.Width, y+fontDesc.Height};
			pfont->DrawTextA(pSprite, (*it)->text.c_str(), -1, &rc, DT_SINGLELINE | DT_NOCLIP, (*it)->color);
			if((*it)->enter)
			{
				x = 0;
				y+=fontDesc.Height;
				i++;
			}
			else
			{
				x+=(*it)->text.length()*fontDesc.Width;
			}
		}
	}
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