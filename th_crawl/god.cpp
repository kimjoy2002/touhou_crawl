﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: god.cpp
//
// 내용: 신관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"
#include "god.h"
#include "key.h"
#include "skill_use.h"
#include "mon_infor.h"
#include "potion.h"
#include "rect.h"
#include "floor.h"
#include "tensi.h"
#include "swako.h"
#include "note.h"
#include "rand_shuffle.h"
#include "seija.h"
#include "lilly.h"
#include "tribe.h"


extern HANDLE mutx;

const char* GetGodString(god_type god)
{
	switch(god)
	{
	case GT_ERROR:
		return "알수없는신";
	case GT_NONE:
		return "";
	case GT_JOON_AND_SION:
		return "죠온&시온";
	case GT_BYAKUREN:
		return "뱌쿠렌";
	case GT_KANAKO:
		return "카나코";
	case GT_SUWAKO:
		return "스와코";
	case GT_MINORIKO:
		return "미노리코";
	case GT_MIMA:
		return "미마";
	case GT_SHINKI:
		return "신키";
	case GT_YUUGI:
		return "유우기";
	case GT_SHIZUHA:
		return "시즈하";
	case GT_HINA:
		return "히나";
	case GT_YUKARI:
		return "유카리";
	case GT_EIRIN:
		return "에이린";
	case GT_YUYUKO:
		return "유유코";
	case GT_SATORI:
		return "사토리";
	case GT_TENSI:
		return "텐시";
	case GT_SEIJA:
		return "세이자";
	case GT_LILLY:
		return "릴리";
	case GT_MIKO:
		return "미코";
	case GT_OKINA:
		return "오키나";
	case GT_JUNKO:
		return "순호";
	}
	return "모름";
}
bool GetGodString_is(god_type god)
{
	switch(god)
	{
	case GT_ERROR:
		return true;
	case GT_NONE:
		return true;
	case GT_JOON_AND_SION:
		return true;
	case GT_BYAKUREN:
		return true;
	case GT_KANAKO:
		return false;
	case GT_SUWAKO:
		return false;
	case GT_MINORIKO:
		return false;
	case GT_MIMA:
		return false;
	case GT_SHINKI:
		return false;
	case GT_YUUGI:
		return false;
	case GT_SHIZUHA:
		return false;
	case GT_HINA:
		return false;
	case GT_YUKARI:
		return false;
	case GT_EIRIN:
		return true;
	case GT_YUYUKO:
		return false;
	case GT_SATORI:
		return false;
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		return false;
	case GT_LILLY:
		return false;
	case GT_MIKO:
		return false;
	case GT_OKINA:
		return false;
	case GT_JUNKO:
		return false;
	}
	return true;
}


int GetGodAbandonValue(god_type god)
{
	return 25;
}

int getPietyPercent(int type, int strong) {
	int percen_ = randA(99);

	switch(type)
	{
	default:
	case 0: //randA(2) 66%
		switch(strong)
		{
		default:
		case 1: return percen_<33 ?1:0;
		case 2: return percen_<50 ? 1 : 0;
		case 3: return percen_<75 ? 1 : 0;
		case 4: return percen_<90 ? 1 : 0;
		case 5: return percen_<100 ? 1 : 0;
		}
	case 1: //50%
		switch (strong)
		{
		default:
		case 1: return percen_<25 ? 1 : 0;
		case 2: return percen_<35 ? 1 : 0;
		case 3: return percen_<66 ? 1 : 0;
		case 4: return percen_<75 ? 1 : 0;
		case 5: return percen_<100 ? 1 : 0;
		}

	case 2: //25%
		switch (strong)
		{
		default:
		case 1: return percen_<10 ? 1 : 0;
		case 2: return percen_<20 ? 1 : 0;
		case 3: return percen_<40 ? 1 : 0;
		case 4: return percen_<60 ? 1 : 0;
		case 5: return percen_<100 ? 1 : 0;
		}
	case 3: //미코 전용
		switch (strong)
		{
		default:
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 4;
		case 5: return 10;
		}
	}
	return 1;
}

int pietyLevel(int piety)
{
	if(piety<30)
		return 0;
	else if(piety<50)
		return 1;
	else if(piety<75)
		return 2;
	else if(piety<100)
		return 3;
	else if(piety<120)
		return 4;
	else if(piety<160)
		return 5;
	else 
		return 6;
}


bool GetGodAbility(int level, bool plus)
{
	switch(you.god)
	{
	case GT_ERROR:
		return false;
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
		switch (level)
		{
		case 0:
			if (plus)
				printlog("당신은 역병신과 빈곤신의 저주로 소모품을 낭비하며 잃어버린다.", true, false, false, CL_joon_and_sion);
			break;
		case 1:
			you.Ability(SKL_JOON_AND_SION_1, true, !plus);
			if (plus)
				printlog("당신은 이제 죠온이나 시온을 빙의할 수 있다.", true, false, false, CL_joon_and_sion);
			else
				printlog("더 이상 당신은 이제 죠온이나 시온을 빙의할 수 없다.", true, false, false, CL_joon_and_sion);
			break;
		case 2:
			if (plus)
				printlog("빙의상태에서 빙의된 신에 따라 파워를 이용한 효과를 얻게 된다.", true, false, false, CL_joon_and_sion);
			else
				printlog("더 이상 빙의상태에서 파워를 이용한 효과를 얻을 수 없다.", true, false, false, CL_joon_and_sion);
			break;
		case 4:
			if (plus)
				printlog("빙의상태에서 빙의된 신에 따라 소모품을 이용한 효과를 얻게 된다.", true, false, false, CL_joon_and_sion);
			else
				printlog("더 이상 빙의상태에서 소모품을 이용한 효과를 얻을 수 없다.", true, false, false, CL_joon_and_sion);
			break;
		case 5:
			if (plus)
			{
				printlog("빙의할때마다 한번만 빙의된 신의 필살기를 사용할 수 있다.", true, false, false, CL_joon_and_sion);
				if (you.god_value[GT_JOON_AND_SION][0] == 1)
					you.Ability(SKL_JOON_AND_SION_2, true, !plus);
				else if (you.god_value[GT_JOON_AND_SION][0] == 2)
					you.Ability(SKL_JOON_AND_SION_3, true, !plus);
			}
			else
				printlog("더 이상 빙의된 신의 필살기를 사용할 수 없다.", true, false, false, CL_joon_and_sion);
			break;
		case 6:
			if (you.god_value[GT_JOON_AND_SION][0] != 0)
				you.Ability(SKL_JOON_AND_SION_4, true, !plus);
			if (plus)
				printlog("이제 당신은 무조건 이길 수 있는 최흉최악의 전법을 사용할 수 있다.", true, false, false, CL_joon_and_sion);
			else
				printlog("더 이상 최흉최악의 전법을 사용할 수 없다.", true, false, false, CL_joon_and_sion);
			break;
		}
		return false;
	case GT_BYAKUREN:
		switch(level)
		{
		case 1:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog("히지리는 당신의 배울 수 있는 마법레벨 한계를 늘려준다.",true,false,false,CL_white_blue);
			else
				printlog("더 이상 당신의 배울 수 있는 마법레벨 한계를 늘려주지않는다.",true,false,false,CL_white_blue);
			break;
		case 2:
			you.remainSpellPoiont+=plus;
			you.Ability(SKL_BYAKUREN_1,true,!plus);
			if(plus)
				printlog("당신은 순간적으로 지력을 강화시킬 수 있다.",true,false,false,CL_white_blue);
			else
				printlog("더 이상 순간적인 지력강화를 사용할 수 없다.",true,false,false,CL_white_blue);
			break;
		case 3:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog("당신은 이제 강화된 근력으로 낮은 갑옷패널티의 마법실패율을 무시한다.",true,false,false,CL_white_blue);
			else
				printlog("더이상 근력강화의 축복을 받지 못한다.",true,false,false,CL_white_blue);
			break;
		case 4:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog("히지리는 이제 당신의 강화마법들을 보조해준다.",true,false,false,CL_white_blue);
			else
				printlog("더 이상 강화마법들을 보조받지 못한다.",true,false,false,CL_white_blue);
			break;
		case 5:
			you.remainSpellPoiont+=plus;
			you.Ability(SKL_BYAKUREN_2,true,!plus);
			if(plus)
				printlog("당신은 이제 히지리의 축복으로 초인같은 각력으로 달릴 수 있게 된다.",true,false,false,CL_white_blue);
			else
				printlog("더이상 초인같은 각력을 사용할 수 없다.",true,false,false,CL_white_blue);
			break;
		}
		return false;
	case GT_KANAKO:
		switch(level)
		{
		case 1:
			you.Ability(SKL_KANAKO_1,true,!plus);
			if(plus)
				printlog("당신은 순간적으로 상대에게 돌진할 수 있다.",true,false,false,CL_help);
			else
				printlog("더 이상 순간적인 돌진을 사용할 수 없다.",true,false,false,CL_help);
			break;
		case 3:
			you.Ability(SKL_KANAKO_2,true,!plus);
			if(plus)
				printlog("당신은 기둥을 소환 할 수 있다.",true,false,false,CL_help);
			else
				printlog("더 이상 기둥을 소환 할 수 없다.",true,false,false,CL_help);
			break;
		case 5:
			you.Ability(SKL_KANAKO_3,true,!plus);
			if(plus)
				printlog("당신은 이제 바람을 감은 공격을 할 수 있다.",true,false,false,CL_help);
			else
				printlog("더 이상 바람을 감아 공격할 수 없다.",true,false,false,CL_help);
			break;
		}
		return false;
	case GT_SUWAKO:
		switch(level)
		{
		case 0:
			if(you.suwako_meet == 0)
			{
				you.god_value[GT_SUWAKO][0] = randA(SWAKO_1_LAST-1);
				you.god_value[GT_SUWAKO][1] = randA(SWAKO_2_LAST-1);
				you.god_value[GT_SUWAKO][2] = randA(SWAKO_3_LAST-1);
				you.god_value[GT_SUWAKO][3] = randA(SWAKO_4_LAST-1);
				you.god_value[GT_SUWAKO][4] = randA(SWAKO_5_LAST-1);
				you.suwako_meet = 1;
			}
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			GetSwakoAbility(level,plus);
			break;
		}
		return false;
	case GT_MINORIKO:
		switch(level)
		{
		case 1:
			if(plus)
				printlog("당신은 파워가 높을수록 체력과 영력회복속도가 빨라진다.",true,false,false,CL_warning);
			else
				printlog("더 이상 체력과 영력회복속도가 빨라지지않는다.",true,false,false,CL_warning);
			break;
		case 2:
			you.Ability(SKL_MINORIKO_1,true,!plus);
			if(plus)
				printlog("당신은 이제 상태이상과 능력치저하를 회복할 수 있다.",true,false,false,CL_warning);
			else
				printlog("더 이상 상태이상과 능력치저하를 회복할 수 없다.",true,false,false,CL_warning);
			break;
		case 3:
			if(plus)
				printlog("당신은 이제 음식을 빨리 먹을 수 있고 영력을 조금 회복한다.",true,false,false,CL_warning);
			else
				printlog("더 이상 음식을 빨리 먹지 못한다.",true,false,false,CL_warning);
			break;
		case 4:
			you.Ability(SKL_MINORIKO_2,true,!plus);
			if(plus)
				printlog("당신은 이제 음식과 P를 소모하여 체력을 크게 회복할 수 있다.",true,false,false,CL_warning);
			else
				printlog("더 이상 음식으로 체력을 회복할 수 없다.",true,false,false,CL_warning);
			break;
		case 5:
			//if(you.power>=500)
			//{			
			//	you.ResistUpDown(plus,RST_FIRE);
			//	you.ResistUpDown(plus,RST_ICE);
			//}
			if(plus)
				printlog("당신은 이제 음식을 먹은 직후 화염과 냉기에 강해진다.",true,false,false,CL_warning);
			else
				printlog("더 이상 음식을 먹어도 화염과 냉기에 강하지않다.",true,false,false,CL_warning);
			break;
		}
		return false;
	case GT_MIMA:
		switch(level)
		{
			case 0:
				you.max_mp+=plus;
				if(plus)
					printlog("당신은 최대영력이 신앙심에 비례해서 증가한다.",true,false,false,CL_green);
				else
					printlog("당신의 최대영력은 감소했다.",true,false,false,CL_green);
				break;
			case 1:
				you.max_mp+=plus;
				if(plus)
					printlog("당신은 적을 죽였을때 영력을 얻는다.",true,false,false,CL_green);
				else
					printlog("더 이상 적을 죽였을때 영력을 얻지 못한다.",true,false,false,CL_green);
				break;
			case 2:
				you.max_mp+=plus;
				if(plus)
					printlog("미마는 이제 파괴술이 들어간 마법의 위력을 보조한다.",true,false,false,CL_green);
				else
					printlog("더 이상 파괴술 위력을 보조받지 못한다.",true,false,false,CL_green);
				break;
			case 3:
				mima_gift(BOOK_CONJURE);
				you.max_mp+=plus;
				break;
			case 4:
				you.max_mp+=plus;
				if(plus)
					printlog("미마는 이제 파괴술이 들어간 마법의 성공율을 올려준다.",true,false,false,CL_green);
				else
					printlog("더 이상 파괴술 성공율을 보정받지 못한다.",true,false,false,CL_green);
				break;
			case 5:
				mima_gift(BOOK_TEST_ANNIHILATE);
				you.max_mp+=plus;
				break;
			case 6:
				you.max_mp+=plus;
				break;
		}
		return false;
	case GT_SHINKI:
		switch(level)
		{
			case 1:
				you.Ability(SKL_SHINKI_1,true,!plus);
				if(plus)
					printlog("당신은 하급 마족의 작은 무리를 소환할 수 있다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 하급 마족의 작은 무리를 소환할 수 없다.",true,false,false,CL_white_puple);
				break;
			case 2:
				you.Ability(SKL_SHINKI_2,true,!plus);
				if(plus)
					printlog("당신은 위험을 무릅쓰고 신키의 중급 마족을 소환할 수 있다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 중급 마족을 소환할 수 없다.",true,false,false,CL_white_puple);
				break;
			case 3:
				if(plus)
					printlog("신키는 당신을 적대적인 소환수로부터 지켜준다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 적대적인 소환수로부터 보호받지 못한다.",true,false,false,CL_white_puple);
				break;
			case 4:
				you.Ability(SKL_SHINKI_3,true,!plus);
				if(plus)
					printlog("당신은 위험을 무릅쓰고 신키의 상급 마족을 소환할 수 있다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 상급 마족을 소환할 수 없다.",true,false,false,CL_white_puple);
				break;
			case 5:
				if(plus)
					printlog("이제 당신은 P로부터 힘을 얻는다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 P로부터 힘을 얻지 못한다.",true,false,false,CL_white_puple);
				break;
		}
		return false;
	case GT_YUUGI:
		switch(level)
		{
		case 0:
			if(plus)
				printlog("당신은 취했을때 잘 피할 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 취해도 피하지 못한다.",true,false,false,CL_yuigi);
			break;
		case 1:
			you.Ability(SKL_YUUGI_1,true,!plus);
			if(plus)
				printlog("당신은 물약을 술로 바꿔 마실 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 물약을 술로 바꿔 마실 수 없다.",true,false,false,CL_yuigi);
			break;
		case 2:
			you.Ability(SKL_YUUGI_2,true,!plus);
			if(plus)
				printlog("당신은 적에게 저먼 스플렉스를 걸 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 적에게 저먼 스플렉스를 걸 수 없다.",true,false,false,CL_yuigi);
			break;
		case 3:
			you.Ability(SKL_YUUGI_3,true,!plus);
			if(plus)
				printlog("당신은 적을 집어 던질 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 적을 집어 던질 수 없다.",true,false,false,CL_yuigi);
			break;
		case 4:
			you.Ability(SKL_YUUGI_4,true,!plus);
			if(plus)
				printlog("당신은 오니의 포효를 외칠 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 포효할 수 없다.",true,false,false,CL_yuigi);
			break;
		case 5:
			you.Ability(SKL_YUUGI_5,true,!plus);
			if(plus)
				printlog("당신은 드디어 삼보필살을 사용할 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 삼보필살을 사용할 수 없다.",true,false,false,CL_yuigi);
			break;
		}
		return false;
	case GT_SHIZUHA:
		switch(level)
		{
			case 0:
				if(plus)
					printlog("시즈하는 잠에서 깬 적들이 외치는 확률을 크게 줄여준다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 시즈하는 적의 외침을 줄여주지 않는다.",true,false,false,CL_autumn);
				break;
			case 1:
				if(plus)
					printlog("당신은 은밀하게 움직일 수 있는 단풍의 발자취를 남긴다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 당신은 발자취에 단풍을 남기지 못한다.",true,false,false,CL_autumn);
				break;
			case 2:
				you.Ability(SKL_SIZUHA_1,true,!plus);
				if(plus)
					printlog("당신은 단풍위에 있는 몬스터들에게 혼란을 걸 수 있다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 당신은 단풍위의 몬스터들에게 혼란을 걸 수 없다.",true,false,false,CL_autumn);
				break;
			case 3:
				you.Ability(SKL_SIZUHA_2,true,!plus);
				if(plus)
					printlog("당신은 끼고있는 방어구를 단풍 방어구로 만들 수 있다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 당신은 끼고있는 방어구를 단풍 방어구로 만들 수 없다.",true,false,false,CL_autumn);
				break;
			case 4:
				if(plus)
					printlog("당신은 단풍 위를 걸을때 매우 빠르게 움직일 수 있다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 당신은 단풍 위에서 빠르게 움직일 수 없다.",true,false,false,CL_autumn);
				break;
			case 6:
				if(you.god_value[GT_SHIZUHA][0]==0)
				{
					you.Ability(SKL_SIZUHA_3,true,!plus);
					if(plus)
						printlog("당신은 딱 한번 당신의 무기에 단풍의 힘을 불어넣을 수 있다.",true,false,false,CL_autumn);
					else
						printlog("더 이상 당신은 당신의 무기에 단풍의 힘을 불어넣을 수 없다.",true,false,false,CL_autumn);
				}
				break;
		}
		return false;
	case GT_HINA:
		
		switch(level)
		{
		case 0:			
			if(plus)
			{
				for(list<item>::iterator it = you.item_list.begin(); it != you.item_list.end() ; it++)
				{
					it->identify_curse = true;
				}
				printlog("당신은 이제 아이템의 저주를 탐지할 수 있다.",true,false,false,CL_hina);
			}
			break;
		case 1:
			you.Ability(SKL_HINA_1,true,!plus);
			if(plus)
				printlog("당신은 저주걸린 아이템의 마이너스 인챈트를 플러스로 바꿀 수 있다.",true,false,false,CL_hina);
			else
				printlog("더 이상 저주걸린 아이템의 인챈트를 역전할 수 없다.",true,false,false,CL_hina);
			break;
		case 2:
			you.Ability(SKL_HINA_2,true,!plus);
			if(plus)
				printlog("당신은 무기에 저주를 걸어서 강력한 힘을 얻을 수 있다.",true,false,false,CL_hina);
			else
				printlog("더 이상 무기에 저주를 걸어서 힘을 얻을 수 없다.",true,false,false,CL_hina);
			break;
		case 3:
			you.Ability(SKL_HINA_3,true,!plus);
			if(plus)
				printlog("당신은 방어구에 저주를 걸어서 모든 데미지를 반사시킬 수 있다.",true,false,false,CL_hina);
			else
				printlog("더 이상 방어구에 저주를 걸어서 데미지를 반사시킬 수 없다.",true,false,false,CL_hina);
			break;
		case 4:
			you.Ability(SKL_HINA_4,true,!plus);
			if(plus)
				printlog("당신은 장신구에 저주를 걸어서 체력과 영력을 회복할 수 있다.",true,false,false,CL_hina);
			else
				printlog("더 이상 장신구에 저주를 걸어서 체력과 영력을 회복할 수 없다.",true,false,false,CL_hina);
			break;
		case 5:
			if(plus)
				printlog("당신은 이제 저주를 흩뿌리고 다닌다.",true,false,false,CL_hina);
			else
				printlog("더 이상 저주를 흩뿌리고 다니지 않는다.",true,false,false,CL_hina);
			break;
		case 6:
			if(you.god_value[GT_HINA][0]==0)
			{
				you.Ability(SKL_HINA_5,true,!plus);
				if(plus)
					printlog("당신은 딱 한번 당신의 무기에 저주의 힘을 불어넣을 수 있다.",true,false,false,CL_hina);
				else
					printlog("더 이상 당신은 당신의 무기에 저주의 힘을 불어넣을 수 없다.",true,false,false,CL_hina);
			}
			break;
		}
		return false;
	case GT_YUKARI:
		switch(level)
		{
		case 1:
			if(plus)
				printlog("당신은 일정 데미지를 받으면 가끔 순간이동된다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 데미지를 받을때 순간이동되지 않는다.",true,false,false,CL_yukari);
			break;
		case 2:
			you.Ability(SKL_YUKARI_1,true,!plus);
			if(plus)
				printlog("당신은 경계로부터 지원사격을 요청할 수 있다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 지원사격을 요청할 수 없다.",true,false,false,CL_yukari);
			break;
		case 3:
			you.Ability(SKL_YUKARI_2,true,!plus);
			if(plus)
				printlog("당신은 경계를 타고 이동할 수 있다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 경계를 타고 이동할 수 없다.",true,false,false,CL_yukari);
			break;
		case 4:
			you.Ability(SKL_YUKARI_3,true,!plus);
			if(plus)
				printlog("당신은 결계를 만들 수 있다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 결계를 만들 수 없다.",true,false,false,CL_yukari);
			break;
		case 5:
			you.Ability(SKL_YUKARI_4,true,!plus);
			if(plus)
				printlog("당신은 차원을 고정시킬 수 있다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 차원을 고정시킬 수 없다.",true,false,false,CL_yukari);
			break;
		}
		return false;
	case GT_EIRIN:
		switch(level)
		{
		case 0:
			if(plus)
			{
				printlog("에이린은 물약작용을 올려준다. 좋은물약위에서 기도하여 나쁜물약을 만들 수 있다.",true,false,false,CL_small_danger);
				iden_list.potion_list[PT_POISON].iden = true;
				iden_list.potion_list[PT_DOWN_STAT].iden = true;
				iden_list.potion_list[PT_CONFUSE].iden = true;
				iden_list.potion_list[PT_SLOW].iden = true;
				iden_list.potion_list[PT_PARALYSIS].iden = true;
			}
			else
			{
				printlog("더 이상 물약의 작용을 올려주지 않는다. 더이상 나쁜 물약을 만들 수 없다.",true,false,false,CL_small_danger);
			}
			break;
		case 1:
			if(plus)
				printlog("당신은 독물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더 이상 독물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 2:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 1);
			you.Ability(SKL_EIRIN_0,true,!plus);
			if(plus)
				printlog("당신은 물약을 던질 수 있다. 이제 능력치감소물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더 이상 물약을 던질 수 없다. 능력치감소물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 3:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 2);
			you.Ability(SKL_EIRIN_1,true,!plus);
			if(plus)
				printlog("당신은 신체개조를 할 수 있다. 당신은 이제 혼란물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더 이상 신체개조를 할 수 없다. 더 이상 혼란물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 4:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 3);
			if(plus)
				printlog("당신은 감속물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더 이상 감속물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 5:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 4);
			you.Ability(SKL_EIRIN_2,true,!plus);
			if(plus)
				printlog("이제 긴급수혈이 가능하다. 이제 마비물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더이상 긴급수혈을 할 수 없다. 더 이상 마비물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 6:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 5);
			break;
		}
		return false;
	case GT_YUYUKO:
		switch(level)
		{
		case 1:
			if(you.s_ghost == 0)
			{
				if(plus)
				{
					you.SetGhost(1);
				}
				you.Ability(SKL_YUYUKO_ON,true,plus);
				you.Ability(SKL_YUYUKO_OFF,true,!plus);

			}
			else
			{				
				if(!plus)
					you.SetGhost(0);
				you.Ability(SKL_YUYUKO_OFF,true,!plus);
				you.Ability(SKL_YUYUKO_ON,true,plus);
			}
			if(plus)
				printlog("당신 주변엔 항상 유령이 모여든다.",true,false,false,CL_yuyuko);
			else
				printlog("더 이상 당신 주변에 유령이 모여들지 않는다.",true,false,false,CL_yuyuko);
			break;
		case 2:
			you.Ability(SKL_YUYUKO_1,true,!plus);
			if(plus)
				printlog("유령을 원하는 곳으로 이동시킬 수 있다.",true,false,false,CL_yuyuko);
			else
				printlog("더 이상 유령을 이동시킬 수 없다.",true,false,false,CL_yuyuko);
			break;
		case 3:
			you.Ability(SKL_YUYUKO_2,true,!plus);
			if(plus)
				printlog("잠시동안 유령의 빈도를 증가시킬 수 있다.",true,false,false,CL_yuyuko);
			else
				printlog("더 이상 유령의 빈도를 증가시킬 수 없다.",true,false,false,CL_yuyuko);
			break;
		case 5:
			you.Ability(SKL_YUYUKO_3,true,!plus);
			if(plus)
				printlog("적 한명의 영혼을 속박할 수 있다.",true,false,false,CL_yuyuko);
			else
				printlog("더 이상 영혼을 속박할 수 없다.",true,false,false,CL_yuyuko);
			break;
		}
		return false;
	case GT_SATORI:
		switch(level)
		{
		case 0:
			you.ResistUpDown(plus,RST_INVISIBLE);
			if(plus)
				printlog("당신은 이제 투명을 감지할 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 투명을 감지할 수 없다.",true,false,false,CL_danger);
			break;
		case 1:
			you.Ability(SKL_SATORI_1,true,!plus);
			if(plus)
				printlog("당신은 적에게 트라우마를 보여줄 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 적에게 트라우마를 보여줄 수 없다.",true,false,false,CL_danger);
			break;
		case 2:
			if(plus)
				printlog("당신은 적으로부터 던전의 모양을 읽어낼 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 적으로부터 던전의 모양을 읽지 못한다.",true,false,false,CL_danger);
			break;
		case 3:
			if(plus)
				printlog("당신은 주변의 적의 기척을 읽을 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 주변의 적의 기척을 읽을 수 없다.",true,false,false,CL_danger);
			break;
		case 4:
			you.Ability(SKL_SATORI_2,true,!plus);
			if(plus)
				printlog("당신은 적의 생각을 읽어낼 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 생각을 읽을 수 없다.",true,false,false,CL_danger);
			break;
		case 5:
			if(plus)
				printlog("당신은 사토리님의 관리를 직접 받는 소중한 애완동물이다.",true,false,false,CL_danger);
			else
				printlog("더 이상 사토리님은 당신을 직접 관리하지않는다.",true,false,false,CL_danger);
			break;
		}
		return false;
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		if(level>=1 && level<=5) //세이자 스탯 뻥
		{			
			you.StatUpDown(plus?2:-2,STAT_STR);
			you.StatUpDown(plus?2:-2,STAT_INT);
			you.StatUpDown(plus?2:-2,STAT_DEX);
		}
		switch(level)
		{
		case 0:
		{
			you.Ability(SKL_SEIJA_GIFT, true, !plus);
			break;
		}
		case 2:
			if (plus) {
				printlog("세이자는 당신의 징벌로부터의 도주를 돕는다.", true, false, false, CL_seija);
			}
			else {
				printlog("세이자는 더 이상 징벌로부터 당신을 돕지 않는다.", true, false, false, CL_seija);
			}
			break;
		case 3:
			you.Ability(SKL_SEIJA_1,true,!plus);
			if (plus) {
				printlog("당신은 위치를 뒤집을 수 있다.", true, false, false, CL_seija);
			}
			else {
				printlog("더 이상 위치를 뒤집을 수 없다.",true,false,false,CL_seija);
		    }
			break;
		case 5:
			you.Ability(SKL_SEIJA_2,true,!plus);
			you.Ability(SKL_SEIJA_GIFT, true, true);
			if(plus)
				printlog("당신은 이제 모두의 시야를 뒤집을 수 있다.",true,false,false,CL_seija);
			else
				printlog("더 이상 모두의 시야를 뒤집을 수 없다.",true,false,false,CL_seija);
			break;
		}
		return false;
	case GT_LILLY:
		switch(level)
		{
		case 1:
			you.Ability(SKL_LILLY_1,true,!plus);
			you.Ability(SKL_LILLY_2,true,!plus);
			if(plus)
				printlog("당신은 이제 요정들을 동료로 권유할 수 있다.",true,false,false,CL_lilly);
			else
				printlog("더 이상 요정을 동료로 권유할 수 없다.",true,false,false,CL_lilly);
			if(plus)
				printlog("당신은 이제 요정들을 근처로 호출할 수 있다.",true,false,false,CL_lilly);
			else
				printlog("더 이상 요정을 호출할 수 없다.",true,false,false,CL_lilly);
			break;
		case 2:
			you.Ability(SKL_LILLY_1,true,!plus);
			if(plus)
				printlog("당신은 이제 한명의 요정을 더 권유할 수 있다.",true,false,false,CL_lilly);
			break;
		case 3:
			you.Ability(SKL_LILLY_1,true,!plus);
			you.Ability(SKL_LILLY_3,true,!plus);
			if(plus)
				printlog("당신은 이제 한명의 요정을 더 권유할 수 있다.",true,false,false,CL_lilly);
			if(plus)
				printlog("당신은 이제 요정을 치유 할 수 있다.",true,false,false,CL_lilly);
			else
				printlog("더 이상 요정을 치유 할 수 없다.",true,false,false,CL_lilly);
			break;
		case 4:
			you.Ability(SKL_LILLY_1,true,!plus);
			if(plus)
				printlog("당신은 이제 한명의 요정을 더 권유할 수 있다.",true,false,false,CL_lilly);
			break;
		case 5:
			you.Ability(SKL_LILLY_1,true,!plus);
			you.Ability(SKL_LILLY_4,true,!plus);
			if(plus)
				printlog("당신은 마지막 동료가 될 요정을 권유할 수 있다.",true,false,false,CL_lilly);
			if(plus)
				printlog("당신은 이제 일시적으로 자신의 힘을 요정들에게 나눠줄 수 있다.",true,false,false,CL_lilly);
			else
				printlog("더 이상 요정대전쟁을 벌일 수 없다.",true,false,false,CL_lilly);
			break;
		}
		return false;
	case GT_MIKO:
		switch (level)
		{
		case 0:
			you.Ability(SKL_MIKO_1, true, !plus);
			you.Ability(SKL_MIKO_2, true, !plus);
			you.Ability(SKL_MIKO_3, true, !plus);
			you.Ability(SKL_MIKO_4, true, !plus);
			you.Ability(SKL_MIKO_5, true, !plus);
			you.Ability(SKL_MIKO_6, true, !plus);
			break;
		}
		return false;
	case GT_OKINA:
		switch (level)
		{
		case 0:
			if (plus)
				printlog("당신은 이제 문을 자유자재로 넘나들며 투시할 수 있다.", true, false, false, CL_okina);
			else
				printlog("더 이상 문을 자유자재로 드나들 수 없다.", true, false, false, CL_okina);
			break;
		case 1:
			you.Ability(SKL_OKINA_1, true, !plus);
			if (plus)
				printlog("당신은 이제 원하는 벽에 문을 만들 수 있다.", true, false, false, CL_okina);
			else
				printlog("더 이상 문을 만들어 낼 수 없다.", true, false, false, CL_okina);
			break;
		case 2:
			you.Ability(SKL_OKINA_2, true, !plus);
			if (plus)
				printlog("당신은 이제 멀리 떨어진 열린 문을 강제로 닫아 잠글 수 있다.", true, false, false, CL_okina);
			else
				printlog("더 이상 문을 강제로 닫을 수 없다.", true, false, false, CL_okina);
			break;
		case 3:
			you.Ability(SKL_OKINA_3, true, !plus);
			if (plus)
				printlog("당신은 이제 적의 등 뒤에 백도어를 만들어 이동할 수 있다.", true, false, false, CL_okina);
			else
				printlog("더 이상 적의 등뒤에 백도어를 만들 수 없다.", true, false, false, CL_okina);
			break;
		case 4:
			you.Ability(SKL_OKINA_4, true, !plus);
			if (plus)
				printlog("당신은 이제 크레이지 백댄서즈를 호출할 수 있다.", true, false, false, CL_okina);
			else
				printlog("더 이상 크레이지 백댄서즈를 호출할 수 없다.", true, false, false, CL_okina);
			break;
		case 5:
			you.Ability(SKL_OKINA_5, true, !plus);
			if (plus)
				printlog("당신은 이제 등 뒤의 문을 열고 도망칠 수 있다.", true, false, false, CL_okina);
			else
				printlog("더 이상 등 뒤의 문으로 도망칠 수 없다.", true, false, false, CL_okina);
			break;
		}
		return false;
	case GT_JUNKO:
		switch (level)
		{
		case 1:
			you.Ability(SKL_JUNKO_1, true, !plus);
			if (plus)
				printlog("당신은 이제 단순한 탄막을 쏠 수 있다.", true, false, false, CL_junko);
			else
				printlog("더 이상 당신은 단순한 탄막을 쏠 수 없다.", true, false, false, CL_junko);
			break;
		case 2:
			you.Ability(SKL_JUNKO_2, true, !plus);
			if (plus)
				printlog("당신은 이제 순수한 힘을 얻을 수 있다.", true, false, false, CL_junko);
			else
				printlog("더 이상 당신은 순수한 힘을 얻을 수 없다.", true, false, false, CL_junko);
			break;
		case 4:
			you.Ability(SKL_JUNKO_3, true, !plus);
			if (plus)
				printlog("당신은 이제 순수한 살의를 지닐 수 있다.", true, false, false, CL_junko);
			else
				printlog("더 이상 당신은 순수한 살의를 지닐 수 없다.", true, false, false, CL_junko);
			break;
		case 6:
			you.Ability(SKL_JUNKO_4, true, !plus);
			if (plus) {
				printlog("당신은 이제 순화할 수 있다.", true, false, false, CL_junko);
				if (you.god_value[GT_JUNKO][0] == 0)
				{
					random_extraction<int> rand_;
					rand_.push(1);//스킬순화
					rand_.push(2);//저항순화
					rand_.push(3);//마력순화
					rand_.push(4);//파워순화
					if (you.char_name.name.compare("모코우"))
						rand_.push(5); //생명순화
					rand_.push(6);//장비순화
					rand_.push(7);//시스템 순화 
					you.god_value[GT_JUNKO][0] = rand_.pop();
					you.god_value[GT_JUNKO][1] = rand_.pop();
					you.god_value[GT_JUNKO][2] = rand_.pop();
				}
				MoreWait();
			}
			else
				printlog("더 이상 당신은 순화할 수 없다.", true, false, false, CL_junko);
			break;
		}
		return false;
	}
	return false;
}

bool GodAccpect_KillMonster(monster* mon_, parent_type type_)
{
	switch(you.god)
	{
	case GT_ERROR:
		return false;
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //적일때
				printlog("죠온과 시온은 적의 지갑을 강탈하는 것을 기뻐했다.", true, false, false, CL_joon_and_sion);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.GiftCount(1);
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_BYAKUREN:
		return false;
	case GT_KANAKO:
		if (type_ == PRT_PLAYER)
		{
			if (!mon_->isUserAlly())
			{ //적일때
				printlog("카나코는 당신의 살생을 기뻐했다.", true, false, false, CL_help);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.GiftCount(1);
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
			else
			{ //아군일때
				printlog("카나코는 당신의 행동에 분노했다. 참회하라!", true, false, false, CL_small_danger);
				you.PietyUpDown(-5);
				return true;
			}
		}
		return false;
	case GT_SUWAKO:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //적일때
				printlog("스와코는 당신의 살생을 기뻐했다.", true, false, false, CL_swako);

				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
					}
				}
				if (!you.GetPunish(GT_SUWAKO) && pietyLevel(you.piety) >= 2)
				{
					switch (you.god_value[GT_SUWAKO][1])
					{
					case SWAKO_2_KILL_HP:
						if (randA(200) < you.piety)
						{
							printlog("체력이 회복되었다.", false, false, false, CL_normal);
							you.HpUpDown(randA_1(1 + mon_->level / 2), DR_EFFECT);
						}
						break;
					case SWAKO_2_KILL_MP:
						if (randA(120) < you.piety)
						{
							printlog("영력이 회복되었다.", false, false, false, CL_normal);
							you.MpUpDown(randA_1(1 + mon_->level / 4));
						}
						break;
					case SWAKO_2_KILL_POWER:
						if (randA(200) < you.piety)
						{
							printlog("파워가 회복되었다.", false, false, false, CL_normal);
							you.PowUpDown(rand_int(3, 5) + randA(mon_->level / 4));
						}
						break;
					}
				}
				enterlog();
				return true;
			}
		}
		return false;
	case GT_MINORIKO:
		if(mon_->id == MON_LETTY)
		{
			if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					printlog("미노리코는 흥분한 상태로 외쳤다.\"바로 그거야!\"",true,false,false,CL_warning);
					you.PietyUpDown(5*isSprint()?5:1);
				}
			}
		}
		return false;
	case GT_MIMA:
		if (type_ == PRT_PLAYER)
		{
			if (!mon_->isUserAlly())
			{ //적일때
				printlog("미마는 당신의 살생을 기뻐했다.", false, false, false, CL_green);

				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(1, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				if (!you.GetPunish(GT_MIMA) && pietyLevel(you.piety) >= 1)
				{
					if (randA(120) < you.piety)
					{
						printlog("영력이 회복되었다.", false, false, false, CL_normal);
						you.MpUpDown(randA_1(1 + mon_->level / 3));
					}
				}
				enterlog();
				return return_;
			}
		}
		return false;
	case GT_SHINKI:
		return false;
	case GT_YUUGI:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //적일때
				printlog("유우기는 당신의 승리를 기뻐했다.", true, false, false, CL_yuigi);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_SHIZUHA:
		if(pietyLevel(you.piety) >=1)
		{
			rand_rect_iterator rit(mon_->position,2,2);
			int i = randA(1+pietyLevel(you.piety)); 
			for(;!rit.end() && i> 0;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y))
				{	
					int rand_ = randA(1);
					env[current_level].MakeFloorEffect(coord_def(rit->x,rit->y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,rand_int(20,30),&you);
				}
				i--;
			}
			int rand_ = randA(1);
			env[current_level].MakeFloorEffect(coord_def(you.position.x,you.position.y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,3+you.piety/20,&you);
			//플레이어 위치에는 무조건 단풍이 세워진다.(일부러 발밑에 단풍까는 플레이를 안해도되게 하기위해)
		}
		if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if(!mon_->isUserAlly())
			{ //적일때
				if(mon_->id == MON_LETTY)
				{
					printlog("시즈하는 박수를 쳤다.\"훌륭해\"",true,false,false,CL_autumn);
					you.PietyUpDown(4);
				}
				else
					printlog("시즈하는 당신의 적이 낙엽처럼 쓰러져가는 것을 기뻐했다.",true,false,false,CL_autumn);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_HINA:
		return false;
	case GT_YUKARI:
		if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if(!mon_->isUserAlly())
			{ //적일때
				printlog("유카리는 당신의 살생을 기뻐했다.",true,false,false,CL_yukari);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_EIRIN:
		if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if(!mon_->isUserAlly())
			{ //적일때
				{
					bool return_ = false;
					for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
						if (getPietyPercent(2, mon_->SetStrong()))
						{
							you.GiftCount(1);
							you.PietyUpDown(1);
							return_ = true;
						}
					}
					if(return_)
						printlog("에이린은 당신의 강함에 관심을 가졌다.", true, false, false, CL_small_danger);
					return return_;
				}
			}
		}
		return false;
	case GT_YUYUKO:
		if(mon_->s_ghost)
		{
			if(you.god_value[GT_YUYUKO][0])
			{
				for(auto it = env[you.god_value[GT_YUYUKO][1]].mon_vector.begin();it != env[you.god_value[GT_YUYUKO][1]].mon_vector.end();it++)
				{
					if(it->isLive() && it->map_id == you.god_value[GT_YUYUKO][0])
					{
						it->summon_time = 0;
					}
				}
			}
				
			{
				monster *mon2_ = BaseSummon(mon_->id, -1, false, false,4,&you, mon_->position, SKD_OTHER, -1);
				if(mon2_)
				{

					mon2_->id = MON_ENSLAVE_GHOST;
					mon2_->name.name += "의 영혼";
					mon2_->name.name_type = true;
					printarray(true,false,false,CL_normal,3,mon_->name.name.c_str(),mon_->name.name_do()," 당신의 동료가 되었다.");
					you.god_value[GT_YUYUKO][0] = mon2_->map_id;
					you.god_value[GT_YUYUKO][1] = current_level;

					//유령화되면 냉기저항1단계증가
					if(mon2_->ice_resist<=2)
						mon2_->ice_resist++;
					//독저항이 생긴다.
					mon2_->poison_resist=1;
						
					//그러나 레벨은 내려간다.
					mon2_->LevelUpdown(-2);

					char temp[200];
					sprintf_s(temp,200,"%s%s구속했다.",mon_->name.name.c_str(),mon_->name.name_to(true));
					AddNote(you.turn,CurrentLevelString(),temp,CL_yuyuko);
				}
			}
		}
		else if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if(!mon_->isUserAlly())
			{ //적일때
				printlog("유유코는 당신의 살생을 기뻐했다.",true,false,false,CL_yuyuko);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_SATORI:
		you.GiftCount(1);
		return false;
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		return false;
	case GT_LILLY:
		return false;
	case GT_MIKO:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //적일때
				int base = getPietyPercent(3, mon_->SetStrong());
				for (int i = 0; i < (isSprint() ? sprintMulti()*base : base); i++) {
					you.PietyUpDown(1);
				}
				return true;
			}
		}
	case GT_OKINA:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //적일때
				printlog("오키나는 당신의 살생을 기뻐했다.", true, false, false, CL_okina);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_JUNKO:
		if (!(mon_->flag & M_FLAG_SUMMON))
		{
			if (type_ == PRT_PLAYER)
			{
				if (!mon_->isUserAlly())
				{ //적일때
					printlog("순호는 당신의 살생을 기뻐했다.", true, false, false, CL_junko);
					bool return_ = false;
					for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
						if (getPietyPercent(2, mon_->SetStrong()))
						{
							you.GiftCount(1);
							you.PietyUpDown(1);
							return_ = true;
						}
					}
					return return_;
				}
			}
		}
		return false;
	}
	return false;
}
bool GodAccpect_Entering()
{
	switch(you.god)
	{
	case GT_MINORIKO:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MIMA:
	case GT_SHINKI:	
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		printlog(seija_talk(GT_NONE, 0),true,false,false,CL_seija);
		return true;
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_GetPitem()
{
	switch(you.god)
	{
	case GT_MINORIKO:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (randA(3))
			{
				you.GiftCount(1);
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		return return_;
	}
	case GT_ERROR:
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
	{
		if (you.god_value[GT_JOON_AND_SION][0] == 2 && !you.GetPunish(GT_JOON_AND_SION) && pietyLevel(you.piety) >= 2)
		{
			int hp_ = rand_int(you.GetMaxHp() * 6 / 100, you.GetMaxHp() * 10 / 100) + 1;
			printlog("P로부터 회복하였다. ", false, false, false, CL_normal);
			you.HpUpDown(hp_, DR_EFFECT);
			return true;
		}
	}
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MIMA:
		return false;
	case GT_SHINKI:	
		if(1)
		{
			if(!you.GetPunish(GT_SHINKI) && pietyLevel(you.piety)>=5)
			{
				int hp_ = rand_int(you.GetMaxHp() *9/100,you.GetMaxHp() *18/100)+1;
				printlog("회복되었다. ",false,false,false,CL_normal);
				you.HpUpDown(hp_, DR_EFFECT);
				you.MpUpDown(randA_1(5));
			}
			bool return_ = false;
			for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
				{
					you.PietyUpDown(1);
					return_ = true;
				}
			}
			return return_;
		}
		break;
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_HPUpDown(int value_,damage_reason reason)
{
	switch(you.god)
	{
	case GT_MINORIKO:		
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
		break;
	case GT_SUWAKO:		
		if(!you.GetPunish(GT_SUWAKO) && pietyLevel(you.piety)>=2)
		{
			switch(you.god_value[GT_SUWAKO][1])
			{
			case SWAKO_2_DEAD_PROTECT:
				if(randA(9)<4 && you.GetHp() <= 0 && value_ < 0)
				{
					if(you.GetHp() -value_>0)
					{
						you.hp-=value_;
						printlog("보호되었다!",false,false,false,CL_swako);
					}
				}
				break;
			}
		}
		break;
	case GT_MIMA:
	case GT_SHINKI:	
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
		break;
	case GT_YUKARI:
		if(pietyLevel(you.piety)>=1 && you.GetHp() > 0 && value_ < 0)
		{
			int percent_ = value_ *-100 / you.GetMaxHp();
			int a_ = 0;
			if(randA(percent_+a_)>=8+a_)
			{				
				int left_percent_ = you.GetHp() *-100 / you.GetMaxHp();
					
				if(percent_>=rand_int(25,50) && percent_>left_percent_)
				{
					you.Teleport();
					if(env[current_level].isInSight(you.position))
						printlog("당신은 약간 공간이 어긋난 것을 눈치챘다.",false,false,false,CL_normal);
					else
						printlog("갑자기 당신 주변이 변화했다.",false,false,false,CL_normal);
				}
				else
				{
					you.Blink(30);
				}
			}
		}
		break;
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}

bool GodAccpect_UseSpell(spell_list spell_)
{
	switch(you.god)
	{
	case GT_MINORIKO:		
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MIMA:
	case GT_SHINKI:
		return false;
	case GT_YUUGI:
		printlog("유우기는 당신의 마법에 분노했다!",true,false,false,CL_small_danger);
		you.PietyUpDown(-5);
		return false;
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
		if(spell_ == SPL_BLINK || spell_ == SPL_TELEPORT_SELF)
		{			
			printlog("유카리는 당신의 위험한 전이마법 사용에 분노했다!",true,false,false,CL_small_danger);
			you.PietyUpDown(-5);
			return false;
		}
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_Practice(int value, skill_type skill_)
{
	switch(you.god)
	{
	case GT_BYAKUREN:
		/*
		if(skill_ >= SKT_SPELLCASTING && skill_ <= SKT_ALCHEMY && value>randA(40))
		{
			bool return_ = false;
			for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
				{
					you.GiftCount(1);
					you.PietyUpDown(1);
					return_ = true;
				}
			}
			return return_;
		}*/
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_Stair(bool down_, bool new_dungeon_)
{

	switch (you.god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
		return false;
	case GT_MIKO:
	{
		if (new_dungeon_)
		{
			you.PietyUpDown(-200);
			if (down_ && env[current_level].popular == 1) {
				printlog("새로운 던전에 진입하면서 새로운 인기도로 시작한다.", true, false, false, CL_miko);
				you.PietyUpDown(60, true);
			}
			else {
				printlog("던전을 옮기면서 인기도가 초기화되었다.", true, false, false, CL_miko);

			}
		}
		else if (down_)
		{
			printlog("층을 옮기면서 인기도가 조금 내려갔다.", true, false, false, CL_miko);
			you.PietyUpDown(-10);
		}
		else
		{
			printlog("계단을 타고 올라가면서 인기도가 크게 내려갔다", true, false, false, CL_miko);
			you.PietyUpDown(-30);
		}
	}
	break;
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;

}
bool GodAccpect_Explore_100()
{
	switch(you.god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
		return false;
	case GT_HINA:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (60 > randA(100))
			{
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		return return_;
	}
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
		return false;
	case GT_SATORI:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (50 > randA(100))
			{
				you.GiftCount(1);
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		return return_;
	}
	case GT_TENSI:
		if(20>randA(100))
		{//텐시는 스프린트를 어떻게?
			you.GiftCount(1);
		}
		return false;
	case GT_SEIJA:
		return false;
	case GT_LILLY:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (50 > randA(100))
			{
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		if (5 > randA(100))
		{
			random_extraction<int> rand_;
			rand_.push(0);
			rand_.push(1);
			rand_.push(2);
			rand_.push(3);
			rand_.push(4);
			for (int i = 0; i < 5; i++)
			{
				int next_ = rand_.pop();
				if (you.god_value[GT_LILLY][next_] == 1)
				{
					for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
					{
						if (it->isLive() && (*it).isUserAlly() && it->map_id == you.lilly_allys[next_].map_id && current_level == you.lilly_allys[next_].floor  &&  env[current_level].isInSight(coord_def(it->position.x, it->position.y)) && it->CanSpeak())
						{
							printlog(fairy_speak(&(*it), you.lilly_allys[next_].personality, FS_NORMAL), true, false, false, CL_normal);
							return true;
						}
					}
				}
			}

		}
		return return_;
	}
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_Exp_get()
{
	switch(you.god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
		return false;
	case GT_SEIJA:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (randA(2))
			{
				you.GiftCount(1);
				return_ = true;
			}
		}
		return return_;
	}
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_First_contact()
{
	switch(you.god)
	{
	case GT_BYAKUREN:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) 
		{
			if (randA(7) < 3)
			{
				you.GiftCount(1);
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		return return_;
	}
	return false;
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
		return false;
	case GT_SATORI: //사토리와 텐시는 조절?
		if(randA(1)==0)
		{
			you.GiftCount(1);
		}
		return false;
	case GT_TENSI:
		if(1)
		{
			if(randA_1(500)<you.CheckTension())
			{
				you.GiftCount(2);
			}
		}
		return false;
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_Abandon(god_type god)
{
	switch(god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_SEIJA:
		return false;
	case GT_LILLY:		
		{
			int k = 0;
			for(int i = 0; i < 5; i++)
			{
				if(you.god_value[GT_LILLY][i] == 1)
				{
					for(auto it = env[you.lilly_allys[i].floor].mon_vector.begin(); it != env[you.lilly_allys[i].floor].mon_vector.end();it++)
					{
						if(it->isLive() && it->isUserAlly() && it->map_id == you.lilly_allys[i].map_id)
						{
							it->ReturnEnemy();
							k++;
							break;
						}
					}
				}

			}
			if(k>0)
			{
				printarray(true,false,false,CL_danger,1,"릴리를 배신하여 모든 동료 요정이 당신에게 등을 돌렸다!");
			}
		}
		return false;
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_turn(int turn)
{
	if(you.GetPunish(GT_SHIZUHA))
	{
		if(turn>1 && you.prev_position != you.position)
		{
			int rand_ = randA(1);
			env[current_level].MakeFloorEffect(you.prev_position,&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,15,&you);
		}
	}




	switch(you.god)
	{
	case GT_ERROR:
		return false;
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
		return false;
	case GT_BYAKUREN:
		return false;
	case GT_KANAKO:
		{		
			for(auto it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && it->GetId() == MON_ONBASIRA && it->isUserAlly() && distan_coord(you.position,it->position) <= 2)
				{
					you.SetSlaying(3);
				}
			}
		}
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SUWAKO:
		{	

			if(you.god == GT_SUWAKO && !you.GetPunish(GT_SUWAKO) && pietyLevel(you.piety)>=2 &&
			you.god_value[GT_SUWAKO][1] == SWAKO_2_SWIM)
			{
				auto tile_ = env[current_level].dgtile[you.position.x][you.position.y].tile;
				if(tile_ == DG_SEA)
					you.SetBuff(BUFFSTAT_EV,BUFF_SUWAKO,8,2);
				else
					you.SetBuff(BUFFSTAT_EV,BUFF_SUWAKO,0,2);
			}
		}
		return false;
	case GT_MINORIKO:
		{
			if(turn%3000 == 0)
			{
				you.PietyUpDown(-1);		
			}
		}
		return false;
	case GT_MIMA:
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SHINKI:
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_YUUGI:
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SHIZUHA:
		{
			if(pietyLevel(you.piety) >=1 && turn>1 && you.prev_position != you.position)
			{
				int rand_ = randA(1);
				env[current_level].MakeFloorEffect(you.prev_position,&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,4+you.piety/10,&you);
			}
			if(turn%2000 == 0)
			{
				you.PietyUpDown(-1);		
			}
		}
		return false;
	case GT_HINA:
		if(pietyLevel(you.piety) >= 5 && !you.GetPunish(GT_HINA))
		{
			int curse_ = 0;
			
			for(equip_type i = ET_FIRST;i!=ET_LAST;i=(equip_type)(i+1))
			{
				if(you.equipment[i])
				{
					if(you.equipment[i]->curse)
						curse_++;
				}
			}
			if(randA(100)<80*curse_/ET_LAST)
			{
				dif_rect_iterator rit(you.position,4,true);
				while(!rit.end())
				{
					coord_def check_pos_ = (*rit);
					
					if(env[current_level].isMove(check_pos_.x, check_pos_.y, false) && env[current_level].isInSight(check_pos_) && you.isSightnonblocked((*rit)))
					{
						env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_CURSE,rand_int(6,8),0,&you);
						break;
					}
					rit++;
				}
			}
		}
		return false;
	case GT_YUKARI:
		if(turn%10 == 0)
		{
			if(1/*randA(100)<20pietyLevel(you.piety) >=1*/)
			{
				dif_rect_iterator rit(you.position,8,true);
				while(!rit.end())
				{
					coord_def check_pos_ = (*rit);

					if(you.s_dimension)
					{
						if(abs(you.god_value[GT_YUKARI][0] - check_pos_.x)>8)
							check_pos_.x += (you.god_value[GT_YUKARI][0] - check_pos_.x)>0?17:-17;
						if(abs(you.god_value[GT_YUKARI][1] - check_pos_.y)>8)
							check_pos_.y += (you.god_value[GT_YUKARI][1] - check_pos_.y)>0?17:-17;
					}


					if(env[current_level].isMove(check_pos_.x, check_pos_.y, false) && env[current_level].isInSight(check_pos_) && you.isSightnonblocked((*rit)))
					{
						textures* t_ = &img_effect_schema[randA(2)];
						env[current_level].MakeFloorEffect(coord_def(check_pos_.x,check_pos_.y),t_,t_,FLOORT_SCHEMA,rand_int(20,30),&you);
						break;
					}
					rit++;
				}
			}
		}

		if(turn%3000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_EIRIN:
		if(turn%4500 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_YUYUKO:
		if(turn%3 == 0)
		{
			if(you.s_ghost && randA(100)<(you.s_ghost>=2?85:5+you.piety/8))
			{
				coord_def c_ = you.position/*+coord_def(rand_int(-6,6),rand_int(-6,6))*/;
				monster *mon_ = BaseSummon(MON_GHOST, rand_int(20,30), false, true,4,&you, c_, SKD_OTHER, -1);
				if(mon_)
				{
					mon_->LevelUpdown(you.level-1,3.0f,1.5f);
					mon_->image = &img_mons_ghost[randA(2)];
				}
			}
		}
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SATORI:
		if(turn%3000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_TENSI:
		if(turn%7 == 0)
		{
			if(randA(1000)<you.CheckTension())
			{
				you.GiftCount(2);
			}
			else if(randA(10)==0)
			{
				you.GiftCount(1);
			}
		}
		return false;
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
		return false;
	case GT_OKINA:
		if (turn % 1000 == 0)
		{
			you.PietyUpDown(-1);
		}
		return false;
	case GT_JUNKO:
		return false;
	}
	return false;
}



int satori_sight()
{
	return pietyLevel(you.piety)*2;
}


void Pray()
{
	if(you.god != GT_NONE)
	{	
		bool sacrifice = false;
		int num = 0;
		for(list<item>::iterator it = env[current_level].item_list.begin();it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++;
			if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
			{
				sacrifice = (God_pray(temp))?true:sacrifice;
				num++;
			}
			else if(num)
				break;
		}
		if (!sacrifice) {
			if (you.GetPunish(you.god)) {
				printarray(true, false, false, CL_warning, 3, GetGodString(you.god), GetGodString_is(you.god)?"은 ":"는 ", "심기가 불편해보인다.");
			}
			if (!God_PraySpeak()) {
				printarray(true, false, false, CL_warning, 2, GetGodString(you.god),"에게 당신은 기도헀다.");
			}
		}
	}
	else
	{
		enterlog();
		dungeon_tile_type type = env[current_level].dgtile[you.position.x][you.position.y].tile;
		if(type == DG_TEMPLE_SUWAKO && isTutorial() && !you.s_poison)
		{
			printlog("스와코는 말했다 : 던전에서 죽는다고 진짜 죽는건 아니야. 모든 기록은 사라지지만.",true,false,false,CL_warning);
			printlog("스와코는 말했다 : 그래서 크롤의 세계에선 죽는 것도 일이란다! 다음에 보자 사나에!",true,false,false,CL_warning);
			you.SetPoison(150, 150,true);
		}
		
		if(type >= DG_TEMPLE_FIRST && type <= DG_TEMPLE_LAST)
		{
			printlog("당신은 제단에 기도를 드렸다.",true,false,false,CL_warning);
			MoreWait();


			if(type != DG_TEMPLE_SATORI && you.GetPunish((god_type)(type-DG_TEMPLE_FIRST)))
			{
				printarray(true,false,false,CL_warning,3,GetGodString((god_type)(type-DG_TEMPLE_FIRST)),GetGodString_is((god_type)(type-DG_TEMPLE_FIRST))?"은 ":"는 ","아직 당신을 용서하지않았다.");


			}
			/*else if (type == DG_TEMPLE_MIKO)
			{
				printlog("이 신은 당신의 입교를 받아주기엔 아직 너무 바쁘다!.",true,false,false,CL_warning);
			}*/
			else
			{
				WaitForSingleObject(mutx, INFINITE);
				deletesub();
				SetDisplayTexture(&img_god_background[(type - DG_TEMPLE_FIRST)]);
				GodInfor((god_type)(type-DG_TEMPLE_FIRST));
				printsub("",true,CL_normal);
				printsub("",true,CL_normal);
				printsub("신도가 되려면 Y키를, 취소하려면 N키를 누른다.",true,CL_help);
				changedisplay(DT_SUB_TEXT);
				ReleaseMutex(mutx);
				bool ok_= true;
				while(ok_)
				{			
					int select = waitkeyinput();
					switch(select)
					{
					default:
					case '?':
						break;
					case 'Y':
					case 'y':
						changedisplay(DT_GAME);
						SetDisplayTexture(NULL);
						you.Belief((god_type)(type-DG_TEMPLE_FIRST),15);
						MoreWait();
					case 'N':
					case 'n':
					case VK_ESCAPE:
						ok_ = false;
						break;
					}
				}
				changedisplay(DT_GAME);
				SetDisplayTexture(NULL);
			}
		}
		else
		{
			printlog("당신은 삶의 의미에 대해 잠시 생각했다.",true,false,false,CL_warning);
		}

		//switch(type)
		//{
		//case DG_TEMPLE_SHIKIEIKI:
		//	printlog("시키에이키는 말했다 : 최대한 빨리 그 쪽지를 지상으로 가져다주세요.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_BYAKUREN:
		//	printlog("뱌쿠렌은 말했다 : 아아, 크롤의 세계 안에 빛이 가득해.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_KANAKO:
		//	printlog("카나코는 말했다 : 이것은 신앙을 모을 기회입니다.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SUWAKO:
		//	if(isNormalGame() || you.s_poison)
		//	{
		//		printlog("스와코는 말했다 : 아하하, 재미있어졌어.",true,false,false,CL_warning);
		//	}
		//	else
		//	{
		//		printlog("스와코는 말했다 : 던전에서 죽는다고 진짜 죽는건 아니야. 모든 기록은 사라지지만.",true,false,false,CL_warning);
		//		printlog("스와코는 말했다 : 그래서 크롤의 세계에선 죽는 것도 일이란다! 다음에 보자 사나에!",true,false,false,CL_warning);
		//		you.SetPoison(150,true);
		//	}
		//	break;
		//case DG_TEMPLE_MINORIKO:
		//	printlog("미노리코는 말했다 : 던전탐험도 식후경!",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_MIMA:
		//	printlog("미마는 말했다 : 기분좋게 자고있었는데, 어떻게 된거지?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SHINKI:
		//	printlog("신키는 말했다 : 마계도 엉망이야...",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_YUUGI:
		//	printlog("유우기는 말했다 : 강한 녀석들을 많이 보겠는걸!",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SHIZUHA:
		//	printlog("잘 들리지않는 부스럭거리는 소리가 들린다.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_HINA:
		//	printlog("히나는 말했다 : 액이 넘쳐나! 액땜할 시간이야!",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_YUKARI:
		//	printlog("유카리는 말했다 : 내 탓은 아니라구?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_EIRIN:
		//	printlog("에이린은 말했다 : 힘을 원한다면, 나의 실험재료가 되는건 어때?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_YUYUKO:
		//	printlog("유유코는 말했다 : 이왕 이렇게 된거 즐기면 되잖아?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SATORI:
		//	printlog("사토리는 말했다 : 애완동물들은 어디로 갔을까요...",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_TENSI:
		//	printlog("텐시는 미친듯이 웃었다.",true,false,false,CL_warning);
		//	break;
		//default:
		//	printlog("당신은 삶의 의미에 대해 잠시 생각했다.",true,false,false,CL_warning);
		//	break;
		//}
	}
	you.time_delay += you.GetNormalDelay();
	you.TurnEnd();
	you.SetPrevAction('p');
}



void GodInfor(god_type god)
{
	printsub("                                                    신앙",true,CL_normal);
	switch(god)
	{
	case GT_SUWAKO:
		printsub("모리야 스와코 - 토착신의 정점",true,CL_swako);
		printsub("",true,CL_normal);
		printsub("스와코는 곤(땅)을 창조하는 능력을 가진 토착신이다.",true,CL_normal);
		printsub("스와코는 신자들에게 변덕스러운 권능을 준다.",true,CL_normal);
		printsub("그 때문에 신자들은 다양한 권능을 받을 수 있지만 원하는 권능을 받지는 못한다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_MIMA:
		printsub("미마 - 아득한 꿈에 운명을 맡긴 정신",true,CL_green);
		printsub("",true,CL_normal);
		printsub("미마는 재앙신격인 존재로 악령이다.",true,CL_normal);
		printsub("신도들은 미마의 밑으로 들어가는 것으로 강력한 파괴 마법을 지원받고 전수받는다.",true,CL_normal);
		printsub("특히 그녀의 충실한 추종자가 되었을때 궁극의 파괴 마법인 스파크를 전수받게된다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_YUYUKO:
		printsub("사이교우지 유유코 - 저승누각의 망령소녀",true,CL_yuyuko);
		printsub("",true,CL_normal);
		printsub("유유코는 백옥루에 사는 사이교우지의 아가씨이다.",true,CL_normal);
		printsub("그녀는 죽음을 조종 할 수 있는 강력한 능력을 가지고 있어서 신도들에게 죽음의 힘을 선물해준다.",true,CL_normal);
		printsub("그녀의 신도가 되면 죽음을 다루는 능력과 많은 영혼들을 선물 받을 것이다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_JOON_AND_SION:
		printsub("요리가미 죠온 & 시온 - 최흉최악의 자매",true, CL_joon_and_sion);
		printsub("",true,CL_normal);
		printsub("낭비와 빈곤의 자매 신으로 믿는 신자에게 불운을 가져다준다.",true,CL_normal);
		printsub("죠온은 재산을 낭비시키는 역병신, 시온은 믿는 자를 빈곤하게 만드는 빈곤신으로서",true,CL_normal);
		printsub("믿는 것만으로도 소모품을 낭비하고 잃어버리는 불행이 생기게 될 것이다.",true,CL_normal);
		printsub("그럼에도 둘을 신앙한다면 직접 빙의하는 것으로 직접적으로 그녀들의 권능들을 사용하게 된다.", true, CL_normal);
		printsub("그녀들의 권능은 강력하지만, 빙의와 동시에 그에 따른 그녀들의 불운도 더욱 강해질것이다.", true, CL_normal);
		printsub("신도들은 다른 적들을 죽여서 그들의 돈을 갈취하는 것으로 신앙심을 얻을 수 있다.", true, CL_normal);
		printsub("", true, CL_normal);
		break;
	case GT_SHINKI:
		printsub("신키 - 마계의 신",true,CL_white_puple);
		printsub("",true,CL_normal);
		printsub("신키는 마계의 주인이자 마계를 창조한 마계의 신이다.",true,CL_normal);
		printsub("창조의 능력을 이용해서 신키는 신도들에게 강력한 마족들을 선물한다.",true,CL_normal);
		printsub("또한 신키는 당신을 적대적인 소환수로부터 지켜주거나 P를 모을때마다 체력과 영력을 회복시켜준다.",true,CL_normal);
		printsub("일정수준 이상의 마족들은 당신을 언제라도 배신할 수 있는 걸 염두해야된다.",true,CL_normal);
		printsub("신도들은 P템을 줍는 것으로 신앙심을 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_MINORIKO:
		printsub("아키 미노리코 - 풍족과 수확의 상징",true,CL_warning);
		printsub("미노리코는 가을의 수확을 상징하는 신으로 신도에게 풍족함을 선사한다.",true,CL_normal);
		printsub("신도들은 미노리코에게 풍족한 음식을 내려받게 되고 포만감과 체력을 보장받는다.",true,CL_normal);
		printsub("신도들은 P템을 줍는 것으로 신앙심을 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SHIZUHA:
		printsub("아키 시즈하 - 외로움과 임종의 상징",true,CL_small_danger);
		printsub("",true,CL_normal);
		printsub("아키 시즈하는 단풍의 신이다.",true,CL_normal);
		printsub("시즈하는 신도들의 당신의 존재감을 낮추어 은밀하게 다닐 수 있게 도와준다.",true,CL_normal);
		printsub("그녀의 권능은 암살자들에게 큰 혜택을 주며 중갑옷의 패널티도 크게 상쇄받을 수 있다.",true,CL_normal);
		printsub("시즈하는 시끄러운 자들의 시체가 낙엽처럼 떨어지는 것을 기뻐한다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_EIRIN:
		printsub("야고코로 에이린 - 달의 두뇌",true,CL_small_danger);
		printsub("",true,CL_normal);
		printsub("그녀는 모든 약을 제조할 수 있는 달의 최고의 현자로 천재 약사이다.",true,CL_normal);
		printsub("그녀의 신도로 들어가면 여러가지 물약들을 받게되고 추가적인 효과를 얻게 된다.",true,CL_normal);
		printsub("또한 자신의 몸을 개조하거나 부작용을 감당하는 극적인 치료도 가능해진다.",true,CL_normal);
		printsub("신도는 그녀의 실험대상이 될 각오를 할 수 있다면 그만큼의 보답을 받을 수 있을 것이다.",true,CL_normal);
		printsub("신도는 이로운 물약의 위에서 기도를 하여 포션을 바치거나 물약을 마시는 것으로 신앙심을 얻을 수 있다.",true,CL_normal);
		printsub("또한 자주는 아니지만 적을 죽였을때 가끔씩 신앙심을 얻을 수 도 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_KANAKO:
		printsub("야사카 카나코 - 산판과 호수의 권화",true,CL_help);
		printsub("",true,CL_normal);
		printsub("카나코는 건(하늘)을 창조하는 능력을 가진 신으로 본래는 바람의 신이지만 산의 신으로 모셔지고 있다.",true,CL_normal);
		printsub("그녀는 신자들에게 신앙을 받는 것으로 강력한 전투 능력을 보답한다.",true,CL_normal);
		printsub("특히 근접전사와 원거리탄막으로 싸우는 자에게 큰 도움이 될 것이다.",true,CL_normal);
		printsub("신자들은 계속되는 전투로 그녀에게 신앙을 바쳐야한다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_YUKARI:
		printsub("야쿠모 유카리 - 경계속에 숨은 요괴",true,CL_yukari);
		printsub("야쿠모 유카리는 환상향에서도 이름있는 강력한 경계의 요괴다.",true,CL_normal);
		printsub("유카리의 식신으로 들어가게 되면 그녀에게 경계와 관련된 능력을 얻을 수 있다.",true,CL_normal);
		printsub("강력한 전이능력을 제공받지만 권능을 제외한 다른 전이능력을 금지하고",true,CL_normal);
		printsub("제어하기 힘든 강력한 전이 능력은 역으로 신도를 위험하게 만들수도 있다.",true,CL_normal);
		//printsub("그녀의 신전은 스키마 안쪽이라는 특수한 던전에 주로 존재하며 그녀의 식신들은 여기에서 시작하게 된다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_HINA:
		printsub("카기야마 히나 - 숨어있는 액막이 인형 신",true,CL_hina);
		printsub("",true,CL_normal);
		printsub("히나는 액을 모아서 재앙을 방지하는 재앙신이다.",true,CL_normal);
		printsub("그녀로부터 액을 받아서 저주를 몸에 지니는 것으로 그녀의 권능을 얻을 수 있다.",true,CL_normal);
		printsub("던전을 탐험하는 것으로 신앙심을 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SATORI:
		printsub("코메이지 사토리 - 원령도 두려워하는 소녀",true,CL_danger);
		printsub("",true,CL_normal);
		printsub("사토리는 지령전의 주인으로 마음을 읽는 요괴이다.",true,CL_normal);
		printsub("사토리를 믿는다는 것은 그녀의 펫이 된다는 얘기와도 같고 그녀의 힘을 받을 수 있게 된다.",true,CL_normal);
		printsub("사토리는 방임주의이기때문에 전투에 직접 관련된 능력은 별로 주진 않는다.",true,CL_normal);
		printsub("그러나 그녀의 마음을 읽는 능력으로 던전의 지형 정보를 얻거나 위치를 알아낼 수 있다.",true,CL_normal);
		printsub("또한 상대의 마음 속으로부터 트라우마를 읽어내거나 상대의 생각을 통째로 읽어내 농락할수도 있다.",true,CL_normal);
		printsub("생각을 간파당한 상대는 모든 디버프 마법에 취약해지므로 정신술을 연마한 사람에게 도움이 될 것이다.",true,CL_normal);
		printsub("그녀의 애완동물들은 던전을 탐험하는 것으로 그녀의 호감을 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_YUUGI:
		printsub("호시구마 유우기 - 일컬어지는 괴력난신",true,CL_yuigi);
		printsub("",true,CL_normal);
		printsub("유우기는 지하의 옛도시에 살고 있는 오니이다. 유우기는 괴력난신의 오니로 강력한 힘을 신도에게 준다.",true,CL_normal);
		printsub("그녀의 힘은 근접 전투를 하면서 상대를 매치거나 집어던지는 등 레슬링같은 전투를 해낼 수 있다.",true,CL_normal);
		printsub("또한 오니의 힘으로 포효를 하여 상대를 벙어리로 만들거나 오니의 궁극기 또한 사용할 수 있게 된다.",true,CL_normal);
		printsub("단, 유우기는 신도가 마법의 힘에 의지해 싸우는 것을 싫어한다.",true,CL_normal);
		printsub("그녀의 신앙심은 전투에서 승리하는 것으로 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_TENSI:
		printsub("히나나이 텐시 - 비상비비상천의 아가씨",true,CL_tensi);
		printsub("",true,CL_normal);
		printsub("텐시는 유정천의 제멋대로인 천인 아가씨이다.",true,CL_normal);
		printsub("그녀는 지루한 천계생활에 따분해하던차 이 이변을 계기로 자신을 믿고자하는 신도들을 장난감처럼 취급한다.",true,CL_normal);
		printsub("텐시는 신도에게 어떠한 권능도 내려주지않는다. 모든 행동은 그녀의 변덕대로 이루어진다. ",true,CL_normal);
		printsub("신도가 항상 위험천만한 전투를 반복하여 그녀의 흥미를 최대한으로 끌어낸다면 강력한 도움을 받을 수 있다.",true,CL_normal);
		printsub("하지만 신도가 안이한 안전을 바란다면 곧 자신의 생각을 후회하게 될 것이다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_BYAKUREN:
		printsub("히지리 뱌쿠렌 - 봉인된 대마법사",true,CL_white_blue);
		printsub("",true,CL_normal);
		printsub("뱌쿠렌은 마계에 봉인되어있었던 대마법사로 환상향에 절인 명련사를 세워 불교의 가르침을 전한다.",true,CL_normal);
		printsub("그녀의 특기는 마법(특히 신체능력을 올리는 마법)이므로 신자들에게 마법을 주로 가르친다.",true,CL_normal);
		printsub("그녀의 권능으로 높은 수준의 지능을 얻거나 빠른 이동이 가능하거나 마법패널티를 상쇄받는다.",true,CL_normal);
		printsub("신도는 만나보지못한 새로운 사람들을 만나는 것으로 신앙심을 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SEIJA:
		printsub("키진 세이자 - 역습의 아마노자쿠",true,CL_seija);
		printsub("",true,CL_normal);
		printsub("세이자는 공개수배되어있는 아마노자쿠로 다양한 물건들을 들고 도망중이다.",true,CL_normal);
		printsub("세이자와 손을 잡는 것으로 그녀가 훔친 강력한 아이템들을 선물 받을 수 있다.",true,CL_normal);
		printsub("현재 궁지에 몰린 그녀는 세이자는 당신이 한편이 되는 것 자체를 최고로 환영할 것이다.",true,CL_normal);
		printsub("그러나 세이자는 어디까지나 신도를 이용할 생각이므로 당신을 방패로 삼을 것이고",true,CL_normal);
		printsub("그녀는 당신이 이용가치가 없어지면 언제든지 버릴 것이며 그녀를 믿으면 영원히 다른 신들의 질타를 받을 것이다.",true,CL_normal);
		printsub("그녀는 의심이 많고 강자를 싫어하므로 레벨이 9를 넘어가면 더이상 그녀를 믿을 수 없게 된다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_LILLY:
		printsub("릴리 화이트 - 봄을 나르는 요정",true,CL_lilly);
		printsub("",true,CL_lilly);
		printsub("릴리 화이트는 봄을 알리는 요정으로 지나가는 것만으로도 봄꽃을 개화시킨다고한다.",true,CL_normal);
		printsub("그녀는 요정의 권리를 신장시키기 위해 요정들에게 자신의 힘을 나눠주고있다.",true,CL_normal);
		printsub("그녀를 믿는 것으로 떠돌이 요정들을 자신의 동료로 끌어모을 수 있다.",true,CL_normal);
		printsub("동료가 된 요정은 당신이 죽을때까지 죽어도 되살아나면서 당신을 따를 것이다.",true,CL_normal);
		printsub("당신은 얻은 경험치를 일부를 동료 요정들에 나눠줘야하며 경험치를 받은 요정들은 당신과 함께 성장한다. ",true,CL_normal);
		printsub("본래 릴리화이트는 요정만의 신이지만 자발적인 다른 종족의 입교는 거부하지않는다.",true,CL_normal);
		printsub("릴리화이트는 이 세상을 탐험하는 것을 좋아한다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_MIKO:
		printsub("토요사토미미노 미코 - 우주를 관장하는 전능 도사", true, CL_miko);
		printsub("", true, CL_miko);
		printsub("토요사토미미노 미코는 몽전대사묘의 성인으로 욕망을 읽는 능력을 지녔다.", true, CL_normal);
		printsub("그녀를 믿는 신도는 신앙심이 아닌 인기도를 자원으로 사용하게된다.", true, CL_normal);
		printsub("인기도는 빠른 속도로 오르며 적들의 욕망을 읽거나 죽임으로서 인기도를 모을 수 있지만", true, CL_normal);
		printsub("층을 올라가거나 서브던전이 바뀌면 인기도가 떨어지며 권능은 인기도를 크게 소모하게 된다.", true, CL_normal);
		printsub("미코의 권능인 도술은 반영구적이며 지속시간없이 유지되지만 층을 이동할 경우 사라진다.", true, CL_normal);
		printsub("", true, CL_miko);
		break;
	case GT_OKINA:
		printsub("마타라 오키나 - 궁극의 절대비신", true, CL_okina);
		printsub("", true, CL_okina);
		printsub("마타라 오키나는 배후에 숨어있는 비신으로 자세한 정체는 알려져있지않다.", true, CL_normal);
		printsub("그녀는 자신의 일을 맡길 부하를 찾고있으며, 당신이 그 일을 할수도 있다.", true, CL_normal);
		printsub("그녀의 신도가 되는 것으로 그녀의 문을 만드는 힘을 이용한 권능을 받을 수 있다.", true, CL_normal);
		printsub("문을 자유자재로 타고다닐수도있고, 적의 등뒤에서 갑자기 등장할수도 있다.", true, CL_normal);
		printsub("또한 다른 동료들을 부르는 것으로 생명력과 정신력을 끌어올릴수도 있다.", true, CL_normal);
		printsub("그녀는 전투에서 승리하여 신의 존재감을 널리 알리는 것을 좋아한다.", true, CL_normal);
		printsub("", true, CL_okina);
		break;
	case GT_JUNKO:
		printsub("순호", true, CL_junko);
		printsub("", true, CL_junko);
		printsub("순호는 원한이 순화된 신령으로 자신의 원한을 갚기위해 신도를 모집하고 있다.", true, CL_normal);
		printsub("그녀의 신도가 된다면 단순하지만 강력한 순화의 능력을 받을 수 있다.", true, CL_normal);
		printsub("그녀의 권능은 신앙심도 소모하지않지만 사용하게되면 일시적으로 순화상태에 빠지고", true, CL_normal);
		printsub("순화 단계가 올라갈수록 소모품의 사용에 제한되는 패널티가 생긴다.", true, CL_normal);
		printsub("기본적으로 권능에 의한 순화상태는 시간이 지나면 돌아오지만 순호가 아끼는 신도에게는 영구적인 순화를 내릴 수 있다.", true, CL_normal);
		printsub("그녀의 축복은 너무 무겁기에 패널티도 크고 배신조차 허용되지않지만 그에 비견할만한 새로운 축복이 내려진다.", true, CL_normal);
		printsub("그녀는 원한을 갚기위해 보이는 적을 모조리 죽이는 것을 좋아한다.", true, CL_normal);
		break;
	default:
		printsub("버그신",true,CL_danger);
		printsub("",true,CL_normal);
		printsub("이 신은 버그다!",true,CL_normal);
		printsub("버그신은 게임 플레이에 지대한 영향을 주며 당신에게 깊은 스트레스를 준다.",true,CL_normal);
		printsub("이 신이 존재하는 것만으로도 게임이 크래쉬가 날 수 있으며 당신의 캐릭터를 삭제시킬지도 모른다.",true,CL_normal);
		printsub("버그신의 분노를 가라앉히려면 제작자에게 보고하는 수 밖에 없다.",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("버그신은 동방크롤에서 가장 악한 신이다.",true,CL_danger);
		printsub("",true,CL_normal);
		break;
	}
}


void God_show()
{
	if(you.god == GT_NONE)
	{
		printlog("당신은 아직 신을 믿고 있지 않다.",true,false,false,CL_normal);
		return;
	}
	deletesub();
	WaitForSingleObject(mutx, INFINITE);
	SetDisplayTexture(&img_god_background[you.god]);
	GodInfor(you.god);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("권능들:                                                           (비용)",true,CL_normal);
	printsub("",true,CL_normal);
	int level_ = pietyLevel(you.piety);
	switch(you.god)
	{
	case GT_ERROR:
		break;
	case GT_NONE:
		break;
	case GT_JOON_AND_SION:
		if (level_ >= 0)
		{
			printsub("당신은 역병신과 빈곤신의 저주를 받고 있다.                                            (패시브)", true, CL_joon_and_sion);
			if (you.god_value[GT_JOON_AND_SION][0] != 1) {
				printsub(" └ 당신은 소모품을 사용할때 가끔 2~3개를 한번에 소모한다.", true, CL_joon_and_sion);
			}
			else {
				printsub(" └ 당신은 소모품을 사용할때 무조건 2~3개를 한번에 소모한다. (강화됨)", true, CL_joon);
			}
			if (you.god_value[GT_JOON_AND_SION][0] != 2) {
				printsub(" └ 줍지않은 소모품은 천천히 사라져간다. 소모품을 버리면 일정 확률로 사라진다.", true, CL_joon_and_sion);
			}
			else {
				printsub(" └ 줍지않은 소모품은 빠른 속도로 사라져간다. 소모품을 버리면 무조건 사라진다. (강화됨)", true, CL_sion);
			}
			printsub("", true, CL_normal);
		}
		if (level_ >= 1 && !you.GetPunish(GT_JOON_AND_SION))
		{
			printsub("당신은 잠시동안 죠온이나 시온을 빙의할 수 있다.                                       (액티브)", true, you.god_value[GT_JOON_AND_SION][0] == 0?CL_joon_and_sion:CL_bad);
			printsub("", true, CL_normal);
		}
		if (level_ >= 2 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] == 1) {
				printsub("죠온이 빙의한 동안엔 모든 데미지가 증폭되며 데미지를 줄때마다 파워가 소모된다.        (패시브)", true, CL_joon);
				printsub("", true, CL_normal);
			}
			else if (you.god_value[GT_JOON_AND_SION][0] == 2) {
				printsub("시온이 빙의한 동안엔 파워를 주워도 파워가 오르지 않는 대신 체력을 회복한다.           (패시브)", true, CL_sion);
				printsub("", true, CL_normal);
			}
			else {
				printsub("빙의를 하게되면 죠온이나 시온이 당신의 파워를 이용한다.                               (패시브)", true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		if (level_ >= 4 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] == 1) {
				printsub("죠온이 빙의한 동안엔 소모품을 낭비하면 무작위 버프를 얻는다.                          (패시브)", true, CL_joon);
				printsub("", true, CL_normal);
			}
			else if (you.god_value[GT_JOON_AND_SION][0] == 2) {
				printsub("시온이 빙의한 동안엔 사망시 소모품을 대량으로 잃는 대신 죽음을 무효로 한다.           (패시브)", true, CL_sion);
				printsub("", true, CL_normal);
			}
			else {
				printsub("빙의를 하게되면 죠온이나 시온이 당신의 소모품을 이용한다.                             (패시브)", true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		if (level_ >= 5 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] == 1) {
				printsub("당신은 시야내 적에게 혼란과 데미지를 줄 수 있다.                               (빙의시 한번만)", true, CL_joon);
				printsub("", true, CL_normal);
			}
			else if (you.god_value[GT_JOON_AND_SION][0] == 2) {
				printsub("당신은 시야내 적에게 감속을 건 후에 시야를 가리는 안개를 뿌릴 수 있다.         (빙의시 한번만)", true, CL_sion);
				printsub("", true, CL_normal);
			}
			else {
				printsub("빙의를 하게되면 죠온이나 시온의 범위 권능을 사용할 수 있다.                    (빙의시 한번만)", true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		if (level_ >= 6 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] != 0) {
				printsub("당신은 빈곤신을 상대에 빙의시키는 필승의 전략을 사용할 수 있다.                         (신앙)", true, CL_joon_and_sion);
				printsub("", true, CL_normal);
			}
			else {
				printsub("빙의를 하게되면 최흉최악의 전략을 사용할 수 있다.                                       (신앙)", true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		break;
	case GT_BYAKUREN:
		if(level_ >= 1 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("히지리는 당신이 배울 수 있는 마법레벨의 한계를 늘린다.                     (패시브)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("당신은 순간적으로 지능을 강화시킬 수 있다.                                   (신앙)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("당신은 근력이 강화되어 낮은 수준의 갑옷패널티의 마법실패율을 무시한다.     (패시브)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("히지리는 당신의 강화 마법들을 보조해준다.                                  (패시브)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("당신은 순간적으로 각력을 강화시킬 수 있다.                             (영력, 신앙)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		break;
	case GT_KANAKO:
		if(level_ >= 1 && !you.GetPunish(GT_KANAKO))
		{
			printsub("당신은 카나코님의 힘으로 돌진할 수 있다.                    (영력, 신앙)",true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_KANAKO))
		{
			printsub("당신은 카나코님의 기둥을 구현할 수 있다.                    (영력, 신앙)",true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_KANAKO))
		{
			printsub("당신은 카나코님의 바람의 힘을 휘감을 수 있다.               (영력, 신앙)",true,CL_help);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SUWAKO:
		if(level_ >= 1 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][0], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString2((swako_2_power)you.god_value[GT_SUWAKO][1], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString3((swako_3_power)you.god_value[GT_SUWAKO][2], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString4((swako_4_power)you.god_value[GT_SUWAKO][3], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString5((swako_5_power)you.god_value[GT_SUWAKO][4], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MINORIKO:
		if(level_ >= 0)
		{
			printsub("파워가 가득차도 음식을 먹을 수 있고 최대 파워를 오래 유지할 수 있다.       (패시브)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("당신이 파워가 가득차있을수록 체력과 영력회복속도가 빨라진다.               (패시브)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("미노리코는 당신에게 걸린 상태이상과 능력저하를 회복시켜준다.              (P, 신앙)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_MINORIKO))
		{ //이때부터 고구마 선물을 해준다.
			printsub("당신은 음식을 더 빨리 먹을 수 있고 먹을때 영력도 조금 회복한다.            (패시브)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("미노리코는 당신이 가진 음식을 소모하여 체력을 크게 회복할 수 있다.  (P, 음식, 신앙)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("미노리코는 당신이 음식을 먹은 직후 일시적으로 불,냉기저항을 1단계 준다.    (패시브)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MIMA:
		if(level_ >= 0 && !you.GetPunish(GT_MIMA))
		{ 
			printsub("신앙심에 비례해서 최대영력이 올라간다.                                     (패시브)",true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_MIMA))
		{
			printsub("적을 죽였을때 적의 세기에 따라 영력을 얻을 수 있다.                        (패시브)",true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_MIMA))
		{
			printsub("미마는 파괴술이 들어간 마법의 위력을 증가시킨다.                           (패시브)",true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_MIMA))
		{
			printsub("미마는 파괴술이 들어간 마법의 성공율을 증가시킨다.                         (패시브)",true,CL_green);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SHINKI:
		if(level_ >= 1 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("당신은 하급 마족 무리를 소환할 수 있다.                                    (P, 신앙)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("당신은 중급 마족을 소환할 수 있다.                                         (P, 신앙)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("적대적인 소환수의 행동을 일정확률로 방해한다.                               (패시브)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("당신은 상급 마족을 소환할 수 있다.                                         (P, 신앙)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("당신은 P를 주울때마다 체력과 영력이 차오른다.                               (패시브)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUUGI:
		if(level_ >= 0 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("취기가 오른 상태에서 약간의 체력회복력과 높은 회피를 얻는다.                (패시브)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("물약 1개를 술로 바꿔서 마실 수 있다.                                    (물약, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("전투중 가끔 상대를 잡는다. 잡으면 잡기기술을 신앙소모없이 쓸 수 있다.       (패시브)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("상대를 잡아 저먼 스플렉스를 걸 수 있다.                                    (P, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("상대를 잡아 집어 던질 수 있다.                                             (P, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("주변의 상대를 침묵시키는 강력한 포효를 할 수 있다.                         (P, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("오니의 궁극기, 삼보필살을 쓸 수 있다.                                      (P, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SHIZUHA:
		if(level_ >= 0 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("시즈하는 적들이 잠에서 깨면서 외치는 확률을 줄여준다.           (패시브)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 움직이거나 적을 죽였을때 단풍잎의 자취를 남긴다.         (패시브)",true,CL_autumn);
			printsub("",true,CL_normal);
			printsub("단풍 위를 걸으면 매우 은밀하게 움직일 수 있다.                  (패시브) ",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 단풍 위에 서있는 모든 적에 혼란을 걸 수 있다.        (영력, 신앙)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 방어구를 단풍방어구로 바꿀 수 있다.                        (신앙)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 단풍 위를 걸을때 매우 빠르게 움직일 수 있다.             (패시브)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 6 && you.god_value[GT_SHIZUHA][0]==0 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 딱 한번 당신의 무기에 단풍브랜드를 부여할 수 있다.       (한번만)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		break;
	case GT_HINA:
		if(level_ >= 0)
		{ 
			printsub("당신은 시야내의 장비에 저주가 걸려있는지 확인하고 식별할 수 있다.                (패시브)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 장착중인 저주가 걸린 장비의 마이너스 인챈트를 플러스로 바꿀 수 있다.           (P)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 무기에 잠시동안 저주의 힘을 담아 강화 시킬 수 있다.                         (저주)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 방어구에 잠시동안 저주의 힘을 담아 모든 공격을 반사시킬 수 있다.            (저주)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 장신구에 잠시동안 저주의 힘을 담아 생명력을 치유 할 수 있다.                (저주)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 저주된 아이템을 끼고 있으면 저주를 흩뿌리고 다닌다.                       (패시브)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 6 && you.god_value[GT_HINA][0]==0 && !you.GetPunish(GT_HINA))
		{
			printsub("당신은 딱 한번 당신의 무기에 저주브랜드를 부여할 수 있다.						   (한번만)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUKARI:
		if(level_ >= 0 && !you.GetPunish(GT_YUKARI))
		{
			printsub("틈새가 당신을 지켜본다.                                         (패시브)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 일정 데미지를 입으면 공간이동이 일어난다.                (패시브)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 틈새로부터 사격지원을 받을 수 있다.                  (영력, 신앙)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 틈새를 타고다닐 수 있다.                             (영력, 신앙)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 결계를 만들 수 있다.                                 (영력, 신앙)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 잠시동안 차원을 고정시킬 수 있다.                    (영력, 신앙)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		break;
	case GT_EIRIN:
		if(!you.GetPunish(GT_EIRIN))
		{
			printsub("에이린은 물약들의 효과를 상승시켜준다.                          (패시브)",true,CL_small_danger);
			printsub("",true,CL_normal);
			printsub("좋은 물약위에서 기도하는 것으로 나쁜 물약을 만들 수 있다.         (물약)",true,CL_small_danger);
			printsub("",true,CL_normal);
			if(level_ >= 1)
			{
				printsub("당신은 다음의 물약을 마실때 추가 효과를 받는다.                 (패시브)",true,CL_small_danger);
				printsub(" └독물약 : 이동속도가 빨라진다.",true,CL_small_danger);
				if(level_ >= 2)
					printsub(" └능력치감소물약 : 체력을 회복한다.",true,CL_small_danger);
				if(level_ >= 3)
					printsub(" └혼란물약 : 영력을 회복한다.",true,CL_small_danger);
				if(level_ >= 4)
					printsub(" └감속물약 : 투명해진다.",true,CL_small_danger);
				if(level_ >= 5)
					printsub(" └마비물약 : 마비시간이 줄어들고 영격을 사용한다.",true,CL_small_danger);
				entersub();
				printsub("",true,CL_normal);
			}
		}
		if(level_ >= 2 && !you.GetPunish(GT_EIRIN))
		{
			printsub("당신의 물약을 던질 수 있다.                                    (P, 물약)",true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_EIRIN))
		{
			printsub("당신은 신체개조를 통해 능력치를 조절할 수 있다.                   (신앙)",true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_EIRIN))
		{
			printsub("당신은 부작용을 대가로 몸을 재생할 수 있다.              (P, 영력, 신앙)",true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUYUKO:
		if(level_ >= 1 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("당신은 유령을 불러들인다.                                      (패시브)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("원하는 위치에 유령들을 보낼 수 있다.                          (P, 영력)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("잠시동안 유령을 불러들이는 빈도를 높힐 수 있다.            (신앙, 영력)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("적 한명의 영혼을 잡을 수 있다.                             (신앙, 영력)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SATORI:
		if(level_ >= 0 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("당신은 투명을 볼 수 있다.                                       (패시브)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("당신은 상대의 트라우마를 끌어낼 수 있다.                          (신앙)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("당신은 적의 기억속에서 맵의 형태를 읽어낸다.                    (패시브)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("당신은 몹의 기척을 탐지할 수 있다.                              (패시브)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("적 한명의 생각을 완벽하게 독파할 수 있다.                   (시간, 신앙)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("사토리는 가끔 당신에게 먹이를 준다. 위험할수록 자주 준다.       (패시브)",true,CL_danger);
			printsub("",true,CL_normal); 
		}
		break;
	case GT_TENSI:
		if(level_ >= 0 && !you.GetPunish(GT_TENSI))
		{ 
			printsub("텐시의 행동은 예측할 수 없다!                                           ",true,CL_tensi);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SEIJA:
		if(level_ >= 1 && !you.GetPunish(GT_SEIJA))
		{ 
			printsub("당신은 세이자로부터 스탯을 강화받고있다.                        (패시브)",true,CL_seija);
			printsub("",true,CL_normal);
		}
		if (level_ >= 2 && !you.GetPunish(GT_SEIJA))
		{
			printsub("징벌에 의한 추격으로부터 당신을 돕는다.                         (패시브)", true, CL_seija);
			printsub("", true, CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SEIJA))
		{
			printsub("원하는 상대방과 위치를 뒤집을 수 있다.                               (P)",true,CL_seija);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SEIJA))
		{ 
			printsub("모든 적, 아군의 시야를 뒤집을 수 있다.                               (P)",true,CL_seija);
			printsub("",true,CL_normal);
		}
		break;
	case GT_LILLY:
		if(level_ >= 1 )
		{ 
			printsub("===당신의 동료 요정===",true,CL_lilly);
			printsub("",true,CL_normal);
			for(int i = 0; i < min(5,level_); i++)
			{
				char temp[100];
				sprintf_s(temp,100,"%d번째 동료: ",i+1);
				printsub(temp,false,CL_warning);
				if(you.god_value[GT_LILLY][i])
				{
					int lenght_ =0;
					if(mondata[you.lilly_allys[i].id].flag & M_FLAG_UNIQUE)
					{
						lenght_ = sprintf_s(temp,100,"%s ",mondata[you.lilly_allys[i].id].name.name.c_str());
						printsub(temp,false,CL_normal);
					}
					else
					{
						lenght_ = sprintf_s(temp,100,"%s(%s) ",fairy_name[you.lilly_allys[i].name].name.c_str(),mondata[you.lilly_allys[i].id].name.name.c_str());
						printsub(temp,false,CL_normal);
					}
					for(;lenght_<25;lenght_++)
						printsub(" ",false,CL_normal);
					lenght_ += printsub("레벨: ",false,CL_warning);
					sprintf_s(temp,100,"%2d",you.lilly_allys[i].level);
					lenght_ += printsub(temp,false,CL_normal);

					for(;lenght_<40;lenght_++)
						printsub(" ",false,CL_normal);
					printsub("상태: ",false,CL_warning);
					sprintf_s(temp,100,"%s",you.god_value[GT_LILLY][i]==1?"생존":"부활대기중");
					printsub(temp,true,you.god_value[GT_LILLY][i]==1?CL_white_blue:CL_danger);
				}
				else
				{
					printsub("공석",true,CL_bad);
				}
			}
			printsub("",true,CL_normal);
			printsub("",true,CL_normal);
		}
		if(level_ >= 0 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("요정에 경험치를 나눠주며 죽은 요정도 경험치를 먹으면 부활한다.  (패시브)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("당신은 요정들을 동료로 권유할 수 있다.                            (없음)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("당신은 요정들을 근처로 호출할 수 있다.                            (영력)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("당신은 동료 요정을 치유할 수 있다.                             (P, 영력)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("당신은 요정들에게 힘을 나눠줄 수 있다.                         (P, 영력)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MIKO:
		if (level_ >= 0 && !you.GetPunish(GT_MIKO))
		{
			printsub("인기도는 다음 행동을 할 경우 올라간다.", true, CL_normal);
			printsub("    적을 죽인다. 강할수록 더 많이 올라간다.", true, CL_miko);
			printsub("    욕망모으기를 이용해 시야내의 적들의 욕망을 모은다.", true, CL_miko);
			printsub("    새로운 서브던전에 입장한다.", true, CL_miko);
			printsub("", true, CL_normal);
			printsub("인기도는 다음 행동을 할 경우 내려간다.", true, CL_normal);
			printsub("    층을 옮긴다. 올라갈수록 더 많은 인기도가 떨어진다.", true, CL_miko);
			printsub("    서브던전을 옮긴다. 모든 인기도가 떨어진다.", true, CL_miko);
			printsub("    미코의 권능을 사용한다.", true, CL_miko);
			printsub("", true, CL_normal);
			printsub("주변의 적들로부터 인기도를 모을 수 있다.                 (층마다 한번만)", true, CL_miko);
			printsub("", true, CL_normal);
			char temp[256];
			sprintf_s(temp, 256, "빠른 속도로 랜덤한 순간이동을 할 수 있다.                  (인기도 %3d%%)", getMikoPiety(0) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(0) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
			sprintf_s(temp, 256, "해당 층에서 주변을 비추는 후광을 얻을 수 있다.             (인기도 %3d%%)", getMikoPiety(1) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(1) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
			sprintf_s(temp, 256, "해당 층에서 원하는 저항을 얻을 수 있다.                    (인기도 %3d%%)", getMikoPiety(2) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(2) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
			sprintf_s(temp, 256, "해당 층에서 원하는 전투능력을 강화시킬 수 있다.            (인기도 %3d%%)", getMikoPiety(3) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(3) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
			sprintf_s(temp, 256, "해당 층에서의 궁극의 축복을 받을 수 있다.                  (인기도 %3d%%)", getMikoPiety(4) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(4) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
		}
		break;
	case GT_OKINA:
		if (level_ >= 0 && !you.GetPunish(GT_OKINA))
		{
			printsub("당신은 자유자재로 문의 이동과 투시가 가능하다.                  (패시브)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 1 && !you.GetPunish(GT_OKINA))
		{
			printsub("당신은 원하는 벽에 문을 만들 수 있다.                           (P, 영력)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 2 && !you.GetPunish(GT_OKINA))
		{
			printsub("당신은 문을 강제로 닫고 잠글 수 있다.                        (신앙, 영력)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 3 && !you.GetPunish(GT_OKINA))
		{
			printsub("당신은 적의 등뒤로 이동할 수 있다.                           (신앙, 영력)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 4 && !you.GetPunish(GT_OKINA))
		{
			printsub("당신은 크레이지 백댄서를 불러올 수 있다.                           (신앙)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 5 && !you.GetPunish(GT_OKINA))
		{
			printsub("당신은 언제든지 등뒤에 있는 문을 열고 탈출 할 수 있다.       (신앙, 영력)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		break;
	case GT_JUNKO:
		{

			bool already_pure = you.god_value[GT_JUNKO][3] != 0;
			if (level_ >= 0)
			{
				if (already_pure)
				{
					printsub("당신은 순호의 축복에 의해 영구적으로 순화되었다.                 (패시브)", true, CL_junko);
					if (you.god_value[GT_JUNKO][3] == 7)
						printsub(" └당신은 일부 두루마리, 물약을 사용할 수 없다.", true, (you.s_pure_turn && you.s_pure >= 10) ? CL_junko : CL_bad);
					else
						printsub(" └당신은 스펠카드, 일부 두루마리, 물약을 사용할 수 없다.", true, (you.s_pure_turn && you.s_pure >= 10) ? CL_junko : CL_bad);
					printsub(" └당신은 모든 스탯이 5 증가한다.", true, CL_junko);
					printsub("", true, CL_normal);
				}
				else
				{
					printsub("순호의 힘은 강력하지만 당신을 일시적으로 순화시킨다.             (패시브)", true, CL_junko);
					if (level_ >= 0 && !you.GetPunish(GT_JUNKO))
					{
						printsub(" └1단계: 당신은 스펠카드를 사용할 수 없다.", true, (you.s_pure_turn && you.s_pure >= 10) ? CL_junko : CL_bad);
						printsub(" └2단계: 당신은 일부 두루마리의 효과를 사용할 수 없다.", true, (you.s_pure_turn && you.s_pure >= 20) ? CL_junko : CL_bad);
						printsub(" └3단계: 당신은 물약의 효과를 받지 않는다.", true, (you.s_pure_turn && you.s_pure >= 30) ? CL_junko : CL_bad);
						printsub("", true, CL_normal);
					}
				}
			}
			if (level_ >= 1 && !you.GetPunish(GT_JUNKO))
			{
				printsub("당신은 단순하지만 강력한 탄막을 날릴 수 있다.                  (P, 영력)", true, already_pure? CL_bad : CL_junko);
				printsub("", true, CL_normal);
			}
			if (level_ >= 2 && !you.GetPunish(GT_JUNKO))
			{
				printsub("당신은 순수한 힘을 얻을 수 있다.                                  (신앙)", true, already_pure ? CL_bad : CL_junko);
				printsub("", true, CL_normal);
			}
			if (level_ >= 4 && !you.GetPunish(GT_JUNKO))
			{
				printsub("당신은 순수한 살의를 얻을 수 있다.                                (신앙)", true, already_pure ? CL_bad : CL_junko);
				printsub("", true, CL_normal);
			}
			if (level_ >= 5 && !you.GetPunish(GT_JUNKO))
			{
				if (already_pure)
				{
					printsub("당신은 순호의 축복으로 영구적으로 순화되었다.", true, CL_junko);
					char temp[100];
					switch (you.god_value[GT_JUNKO][3])
					{
					case 1:
						sprintf_s(temp, 100, " └스킬순화: 당신의 %s 스킬레벨은 캐릭터 레벨과 항상 같다. ", skill_string((skill_type)you.pure_skill));
						printsub(temp, true, CL_junko);
						break;
					case 2:
					{
						sprintf_s(temp, 100, " └저항순화: 당신의 %s 저항은 면역이다. ", you.GetProperty(TPT_FIRE_IMUNE)?"화염":(you.GetProperty(TPT_COLD_IMUNE) ? "냉기" : (you.GetProperty(TPT_ELEC_IMUNE) ? "전기" : "버그")));
						printsub(temp, true, CL_junko);
						break;
					}
					case 3:
						sprintf_s(temp, 100, " └마력순화: 당신의 체력과 영력은 동일시된다. ");
						printsub(temp, true, CL_junko);
						break;
					case 4:
						sprintf_s(temp, 100, " └파워순화: 당신은 항상 풀파워다. ");
						printsub(temp, true, CL_junko);
						break;
					case 5:
						sprintf_s(temp, 100, " └생명순화: 당신은 추가 목숨을 받았다. ");
						printsub(temp, true, CL_junko);
						break;
					case 6:
						sprintf_s(temp, 100, " └장비순화: 당신은 가지고 있던 장비를 순화했다. ");
						printsub(temp, true, CL_junko);
						break;
					case 7:
						sprintf_s(temp, 100, " └시스템순화: 당신은 스펠카드 사용이 허가되고 부적의 충전속도가 3배가 되었다. ");
						printsub(temp, true, CL_junko);
						break;
					default:
						printsub(" └알수없는 버그 순화", true, CL_junko);
						break;
					}
				}
				else
				{
					printsub("당신은 순호의 축복으로 영구적으로 순화할 수 있다.               (한번만)", true, CL_junko);
				}
				printsub("", true, CL_normal);
			}
			break;
		}
	}
	changedisplay(DT_SUB_TEXT);
	ReleaseMutex(mutx);
	while(1)
	{
		int key_ = waitkeyinput(true);
		break;
	}
	changedisplay(DT_GAME);
	SetDisplayTexture(NULL);

}
bool God_pray(const list<item>::iterator it)
{
	switch(you.god)
	{
	case GT_ERROR:
		break;
	case GT_NONE:
		break;
	case GT_JOON_AND_SION:
		break;
	case GT_BYAKUREN:
		break;
	case GT_KANAKO:
		//if(it->type == ITM_FOOD && it->value1 == 0)
		//{
		//	printlog("P템은 불기둥에 휩싸여 사라졌다. 카나코는 공물을 받아들였다.",true,false,false,CL_small_danger);
		//	env[current_level].DeleteItem(it);
		//	if(randA(1))
		//	{
		//		you.PietyUpDown(1);	
		//		you.GiftCount(1);
		//	}
		//	return true;		
		//}
		break;
	case GT_SUWAKO:
		break;
	case GT_MINORIKO:
		break;
	case GT_MIMA:
		break;
	case GT_SHINKI:
		break;
	case GT_YUUGI:
		break;
	case GT_SHIZUHA:
		break;
	case GT_HINA:
		break;
	case GT_YUKARI:
		break;
	case GT_EIRIN:
		//if(it->type == ITM_FOOD && it->value1 == 0)
		//{
		//	printlog("P템은 불기둥에 휩싸여 사라졌다. 에이린은 공물을 받아들였다.",true,false,false,CL_small_danger);
		//	env[current_level].DeleteItem(it);
		//	you.PietyUpDown(1);	
		//	you.GiftCount(1);
		//	return true;		
		//}
		if(it->type == ITM_POTION && iden_list.potion_list[it->value1].iden && isGoodPotion((potion_type)it->value1)>0)
		{
			int per_ = randA(100);
			int result_ = (per_<15)?PT_CONFUSE:((per_<41)?PT_POISON:((per_<67)?PT_SLOW:(per_<93)?PT_DOWN_STAT:PT_PARALYSIS));
			printarray(false,false,false,CL_small_danger,3,it->GetName().c_str(),it->GetNameInfor().name_is(true),randA(2)?(randA(1)?"연기를 내며 ":"고약한 냄새를 풍기며 "):"빛을 내면서 ");
			it->value1 = result_;
			printarray(true,false,false,CL_small_danger,3,it->GetName().c_str(),it->GetNameInfor().name_by(true),"바뀌었다.");
			printarray(true,false,false,CL_small_danger,1,"에이린은 흡족히 여겼다.");
			you.PietyUpDown(it->num * 2);
			you.GiftCount(it->num * 1);
			return true;
		}
		break;
	case GT_YUYUKO:
		break;
	case GT_SATORI:
		break;
	case GT_TENSI:
		break;
	case GT_SEIJA:
		break;
	case GT_LILLY:
		break;
	case GT_MIKO:
		break;
	case GT_OKINA:
		break;
	case GT_JUNKO:
		break;
	}
	return false;		
}
bool god_punish(god_type god)
{
	bool summon_ = false;

	if(wiz_list.wizard_mode == 1)
	{
		printarray(true,false,false,CL_small_danger,1,"***징벌!***");
	}
	switch(god)
	{
	case GT_ERROR:
		break;
	case GT_NONE:
		break;
	case GT_JOON_AND_SION:
	{
		random_extraction<int> rand_;
		rand_.push(0, 50);//죠온이 강제 빙의하면서 파워 감소
		rand_.push(1, 50);//시온이 강제 빙의하면서 체력 영력 감소
		switch (rand_.pop())
		{
		case 0:
			you.god_value[GT_JOON_AND_SION][0] = 1;
			you.god_value[GT_JOON_AND_SION][1] = rand_int(250, 400);
			you.PowUpDown(-100);
			printarray(true, false, false, CL_white_blue, 1, "죠온이 당신에게 강제로 빙의하였다! 파워가 감소하였다!");
			break;
		case 1:
			you.god_value[GT_JOON_AND_SION][0] = 2;
			you.god_value[GT_JOON_AND_SION][1] = rand_int(250, 400);
			you.HpUpDown(-you.GetMaxHp() / 2, DR_EFFECT);
			if (!you.pure_mp)
				you.MpUpDown(-you.max_mp / 2);
			printarray(true, false, false, CL_white_blue, 1, "시온이 당신에게 강제로 빙의하였다! 체력과 영력을 잃었다!");
			break;
		}
	}
	break;
	case GT_BYAKUREN:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//마나흡수
			rand_.push(1,25);//스탯드레인
			rand_.push(2,25);//슬로우
			switch(rand_.pop())
			{
			case 0:
				you.MpUpDown(!you.pure_skill? -you.GetMaxMp(): -you.GetMaxMp()/2);
				printarray(true,false,false,CL_white_blue,1,"뱌쿠렌의 분노로 당신의 영력이 흡수되었다!");
				break;
			case 1:
				(randA(1)?you.StatUpDown(-rand_int(1,5),STAT_STR,true):you.StatUpDown(-rand_int(3,7),STAT_INT,true));
				printarray(true,false,false,CL_white_blue,1,"뱌쿠렌의 분노로 당신의 스탯이 감소되었다!");
				break;
			case 2:
				you.SetSlow(rand_int(80,100));
				printarray(true,false,false,CL_white_blue,1,"뱌쿠렌의 분노로 당신은 느려졌다!");
				break;
			}
		}
		break;
	case GT_KANAKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,33);//건신초래돌
			rand_.push(1,33);//온바시라
			rand_.push(2,33);//몹 리콜
			switch(rand_.pop())
			{
			case 0:	
				{
					printarray(true,false,false,CL_help,1,"카나코는 당신에게 강력한 일격을 날렸다!");
					int damage_ = you.GetHp()*rand_int(40,80)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY,ATT_SMITE,name_infor("건신초래 돌",true));
					you.damage(temp_att, true);


				}	
				break;
			case 1:
				{
					for(int i = randA(3)+1; i>0 ; i--)
					{
						BaseSummon(MON_ONBASIRA, rand_int(10,30), true, false, 2, NULL, you.position, SKD_OTHER, -1);
					}
					printarray(true,false,false,CL_help,1,"카나코는 당신에게 온바시라를 꽂았다!");
					env[current_level].MakeNoise(you.position,16,NULL);
					break;
				}
			case 2:
				{
					int max_ = rand_int(3,5);
					deque<monster*> dq;
					for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
					{
						if(it->isLive() && !it->isUserAlly())
						{
							dq.push_back(&(*it));
							max_--;
							if(!max_)
								break;
						}
					}
					rand_shuffle(dq.begin(),dq.end());
					dif_rect_iterator rit(you.position,2,true);
					if(!dq.empty())
					{							
						printarray(true,false,false,CL_help,1,"카나코는 당신을 전투로 강제로 이끌었다!");
						summon_ = true;
						for(int i = 0;!rit.end() && i < dq.size();rit++)
						{
							if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
							{
								dq[i]->SetXY(rit->x,rit->y);
								if(dq[i]->isYourShight())
								{
									dq[i]->AttackedTarget(&you);
								}
								i++;
							}
						}
					}
					else
					{
						printarray(true,false,false,CL_help,1,"카나코는 당신을 전투로 이끌려했지만 적당한 적이 없었다.");
					}
				}
				break;
			}
		}
		break;
	case GT_SUWAKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//저주
			rand_.push(1,50);//개구리
			switch(rand_.pop())
			{
			case 0:	
				{
					you.SetSlow(rand_int(4,20));
					you.SetPoison(rand_int(30,50)+randA(you.level*10),300,true);
					rand_rect_iterator rit(you.position,1,1);
					int smoke_ = rand_int(2,5);
					for(int i = 0; !rit.end() && i < smoke_;rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y, true))
						{
							env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_FOG,rand_int(6,12),0,NULL);
							i++;
						}
					}
					env[current_level].MakeSmoke(you.position,img_fog_dark,SMT_FOG,rand_int(6,12),0,&you);
					printarray(true,false,false,CL_swako,1,"스와코는 당신에게 저주를 내렸다!");
				}
				break;
			case 1:
				{
					int i = rand_int(2,4)+randA(you.level/6); 
					for(; i>0 ; i--)
					{
						if(monster *mon_ = BaseSummon((you.level > 10 && randA(3)==1)?MON_DEAGAMA:MON_FROG, rand_int(60,120), true, true, 2, NULL, you.position, SKD_OTHER, -1))
						{
							if(you.level>5)
								mon_->LevelUpdown(you.level-5);
						}
					}
					summon_ = true;
					printarray(true,false,false,CL_swako,1,"스와코는 당신에게 적대적인 개구리 무리를 선물했다!");
				}
				break;
			}
		}
		break;
	case GT_MINORIKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//파워절반
			rand_.push(1,25);//체력감소와 병
			rand_.push(2,25);//능력치감소
			switch(rand_.pop())
			{
			case 0:				
				you.PowUpDown(-min(you.power,500)/2,true);
				printarray(true,false,false,CL_warning,1,"미노리코는 당신의 배고픔을 가속시켰다!");
				break;
			case 1:
				{
					you.HpUpDown(-max(1, you.GetHp() / 2), DR_EFFECT, NULL);
					you.SetSick(rand_int(80,120));
					printarray(true,false,false,CL_warning,1,"미노리코는 당신의 건강을 빼앗아갔다!");
					break;
				}
			case 2:
				{
					for(int i=0;i<3;i++)
						you.StatUpDown(-rand_int(1,4),randA(2)?(randA(1)?STAT_STR:STAT_DEX):STAT_INT,true);
					printarray(true,false,false,CL_warning,1,"미노리코는 당신의 능력치를 깍아내렸다!");
					break;
				}
			}
		}
		break;
	case GT_MIMA:
		{
			random_extraction<int> rand_;
			rand_.push(0,33);//폭발
			switch(rand_.pop())
			{
			case 0:	
				{
					string str_ = "마법";
					textures* tex_ = &img_blast[2];
					attack_type type_ = ATT_NORMAL_BLAST;
					int damage_ = 15+you.level*5;
					switch(randA(5))
					{
					case 0:
						{
						str_ = "화염 마법";
						tex_ = &img_blast[0];
						type_ = ATT_FIRE_BLAST;
						break;
						}
					case 1:
						{
						str_ = "암석 마법";
						tex_ = &img_blast[1];
						type_ = ATT_NORMAL_BLAST;
						damage_ = damage_*4/5;
						break;
					case 2:
						str_ = "전기 마법";
						tex_ = &img_blast[2];
						type_ = ATT_ELEC_BLAST;
						break;
						}
					case 3:
						{
						str_ = "맹독 마법";
						tex_ = &img_blast[3];
						type_ = ATT_POISON_BLAST;
						damage_ = damage_*4/5;
						break;
						}
					case 4:
						{
						str_ = "냉기 마법";
						tex_ = &img_blast[4];
						type_ = ATT_COLD_BLAST;
						break;
						}
					case 5:
						{
						str_ = "마력";
						tex_ = &img_blast[5];
						type_ = ATT_COLD_BLAST;
						damage_ = damage_*3/5;
						break;
						}
					}
					printarray(true,false,false,CL_green,3,"미마가 강력한 ",str_.c_str(),"을 당신에 겨냥했다!");
					attack_infor temp_att(randC(3,damage_/3),damage_,99,NULL,PRT_ENEMY,type_,name_infor(str_.c_str(),true));
					BaseBomb(you.position, tex_,temp_att);
					env[current_level].MakeNoise(you.position,12,NULL);
				}	
				break;
			}
		}
		break;
	case GT_SHINKI:
		{
			random_extraction<int> rand_;
			rand_.push(0,100);//악마소환
			switch(rand_.pop())
			{
			case 0:
				{
					random_extraction<int> lowmidhigh_[3],perenct_;
					lowmidhigh_[0].push(MON_EVIL_EYE);
					lowmidhigh_[0].push(MON_LITTLE_IMP);
					lowmidhigh_[1].push(MON_LUIZE);
					lowmidhigh_[1].push(MON_ELIS);
					lowmidhigh_[1].push(MON_SARA);
					lowmidhigh_[2].push(MON_YUKI);
					lowmidhigh_[2].push(MON_MAI);
					lowmidhigh_[2].push(MON_YUUGENMAGAN);

					if(you.level<15)	
						perenct_.push(0,30-you.level*2);
					perenct_.push(1,3+you.level);
					if(you.level>13)	
						perenct_.push(2,you.level*3-40);


					int i = rand_int(1,3+you.level/9);
					for(; i>0 ; i--)
					{
						int demon_ = lowmidhigh_[perenct_.choice()].choice();
						if(monster *mon_ = BaseSummon(demon_, rand_int(90,120), true, true, 2, NULL, you.position, SKD_OTHER, -1))
						{
						}
					}
					summon_ = true;
					printarray(true,false,false,CL_white_puple,1,"신키가 적대적인 마계인을 창조해냈다!");
				}
				break;
			}
		}
		break;
	case GT_YUUGI:
		{
			random_extraction<int> rand_;
			rand_.push(0,25);//술
			rand_.push(1,25);//자이언트 스윙
			rand_.push(2,50);//오니 소환
			switch(rand_.pop())
			{
			case 0:			
				printarray(true,false,false,CL_yuigi,1,"유우기가 강한 술을 당신에게 강제로 먹였다!");	
				you.SetConfuse(rand_int(9,30));
				you.SetDrunken(rand_int(50,100));
				break;
			case 1:
				{
					printarray(true,false,false,CL_yuigi,1,"유우기가 당신을 집어던졌다!");
					you.Blink(40);
					int damage_ = you.GetHp()*rand_int(30,60)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY, ATT_SMASH,name_infor("자이언트스윙",true));
					you.damage(temp_att, true);
				}
				break;
			case 2:
				{
					printarray(true,false,false,CL_yuigi,1,"유우기가 당신을 벌하기위해 동료 오니들을 불러냈다!");
					random_extraction<int> oni_;
					oni_.push(MON_ONI);
					oni_.push(MON_BLUE_ONI);
					int i = rand_int(1+you.level/10,1+you.level/5);
					summon_ = true;
					for(; i>0 ; i--)
					{
						int time_ = rand_int(40,60);
						if(monster *mon_ = BaseSummon(oni_.choice(), time_, true, true, 2, NULL, you.position, SKD_OTHER, -1))
						{
							if(randA(99)<max(0,200-you.level*30))
								mon_->SetSlow(time_);
							if(randA(99)<max(0,you.level*4-28))
								mon_->SetMight(time_);
							if(randA(99)<max(0,you.level*5-65))
								mon_->SetHaste(time_);
						}
					}
				}
				break;
			}
		}
		break;
	case GT_SHIZUHA:
		{
			random_extraction<int> rand_;
			rand_.push(0,33);//혼란
			rand_.push(1,33);//암습
			rand_.push(2,33);//슬로우
			switch(rand_.pop())
			{
			case 0:			
				printarray(true,false,false,CL_autumn,1,"시즈하는 당신에 광기의 낙엽을 흩날렸다!");	
				you.SetConfuse(rand_int(12,45), true);
				break;
			case 1:
				{				
					rand_rect_iterator rit(you.position,2,2);
					int i = 5+randA(5); 
					for(;!rit.end() && i> 0;rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y))
						{	
							int rand_ = randA(1);
							env[current_level].MakeFloorEffect(coord_def(rit->x,rit->y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,rand_int(20,30),&you);
						}
						i--;
					}
					int rand_ = randA(1);
					env[current_level].MakeFloorEffect(coord_def(you.position.x,you.position.y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,3+you.piety/20,&you);
	
					printarray(true,false,false,CL_autumn,1,"시즈하가 당신의 등 뒤를 찔렀다!");
					int damage_ = you.GetHp()*rand_int(30,60)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY,ATT_SMITE,name_infor("암습",true));
					you.damage(temp_att, true);
					you.SetBuff(BUFFSTAT_RF,BUFF_AUTUMN_RF,-1,1);
				}
				break;
			case 2:
				{
					printarray(true,false,false,CL_autumn,1,"시즈하가 엄청난 소음과 함께 당신을 지목했다!");
					env[current_level].MakeNoise(you.position,30,NULL);
					int time_ = rand_int(40,60);
					you.SetGlow(time_);
					you.SetSlow(time_);
				}
				break;
			}
		}
		break;
	case GT_HINA:
		{
			random_extraction<int> rand_;
			rand_.push(0,25);//액
			rand_.push(1,50);//장비액
			rand_.push(2,25);//혼란
			switch(rand_.pop())
			{
			case 0:		
				{
					you.SetSlow(rand_int(4,20));
					you.SetPoison(rand_int(20,40)+randA(you.level*8),200,true);
					rand_rect_iterator rit(you.position,1,1);
					int smoke_ = rand_int(3,7);
					for(int i = 0; !rit.end() && i < smoke_;rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y, true))
						{
							env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_CURSE,rand_int(6,12),0,NULL);
							i++;
						}
					}
					env[current_level].MakeSmoke(you.position,img_fog_dark,SMT_CURSE,rand_int(6,12),0,&you);
					printarray(true,false,false,CL_hina,1,"히나는 액을 당신에게 직접 주입했다!");
				}
				break;
			case 1:
				{
					bool curse_ = false;
					deque<int> dq;
					for(int i=ET_FIRST;i<ET_LAST;i++)
					{
						if(i != ET_THROW)
							dq.push_back(i);
					}	
					rand_shuffle(dq.begin(),dq.end());
					printarray(false,false,false,CL_hina,1,"히나는 당신의 장비에 액을 주입했다! ");


					for(int i = 0; i<dq.size() ; i++)
					{
						if(you.equipment[dq[i]])
						{
							string before_name = you.equipment[dq[i]]->GetName(); //저주받기전 이름
							if(you.equipment[dq[i]]->Curse(true,(equip_type)dq[i]))
							{
								enterlog();
								printlog("장착하고 있던 ",false,false,false,CL_small_danger);		
								printlog(before_name,false,false,false,CL_small_danger);	
								printlog(you.equipment[dq[i]]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
								printlog("검게 빛났다.",true,false,false,CL_small_danger);		
								curse_ = true;
								break;
							}
						}
					}
					if(!curse_)
					{
						printarray(true,false,false,CL_hina,1,"그러나 아무일도 일어나지 않았다.");

					}
				}
				break;
			case 2:
				{
					printarray(true,false,false,CL_autumn,1,"히나는 당신을 빙빙 돌렸다!");	
					you.SetConfuse(rand_int(12,45), true);
					break;
				}
			}
		}
		break;
	case GT_YUKARI:
		{
			random_extraction<int> rand_;
			rand_.push(0,25);//공간이동
			rand_.push(1,50);//장비액
			rand_.push(2,25);//혼란
			switch(rand_.pop())
			{
			case 0:		
				{
					you.SetConfuse(rand_int(6,18), true);
					you.Teleport();
					printarray(true,false,false,CL_yukari,1,"유카리는 당신을 강제로 텔레포트 시켰다!");
				}
				break;
			case 1:
				{					
					you.SetStasis(rand_int(20,30));
					int max_ = rand_int(2,3);
					deque<monster*> dq;
					for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
					{
						if(it->isLive() && !it->isUserAlly())
						{
							dq.push_back(&(*it));
							max_--;
							if(!max_)
								break;
						}
					}
					rand_shuffle(dq.begin(),dq.end());
					dif_rect_iterator rit(you.position,2,true);
					if(!dq.empty())
					{
						summon_ = true;
						printarray(true,false,false,CL_yukari,1,"유카리는 당신의 주변에 몹들을 강제로 이동시켰다!");
						for(int i = 0;!rit.end() && i < dq.size();rit++)
						{
							if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
							{

								dq[i]->SetXY(rit->x,rit->y);
								textures* t_ = &img_effect_schema[randA(2)];
								env[current_level].MakeFloorEffect(coord_def(rit->x,rit->y),t_,t_,FLOORT_SCHEMA,rand_int(20,30),&you);

								if(dq[i]->isYourShight())
								{
									dq[i]->AttackedTarget(&you);
								}
								i++;
							}
						}
					}
					else
					{
						printarray(true,false,false,CL_yukari,1,"유카리는 당신의 공간이동을 막았다!");
					}
				}
				break;
			case 2:
				{

					printarray(true,false,false,CL_yukari,1,"유카리는 당신을 감시하는 이형의 눈을 소환했다!");
					summon_ = true;
					int i = rand_int(2+you.level/8,3+you.level/5);
					for(; i>0 ; i--)
					{
						int time_ = rand_int(40,60);
						if(monster *mon_ = BaseSummon(MON_SCHEMA_EYE, time_, true, true, 3, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level,3);
						}
					}
					break;
				}
			}
		}
		break;
	case GT_EIRIN:
		{
			random_extraction<int> rand_;
			rand_.push(0,66);//물약먹이기
			rand_.push(1,33);//강제실험
			switch(rand_.pop())
			{
			case 0:
				{
					random_extraction<potion_type> potion_;	
					potion_.push(PT_DOWN_STAT);
					potion_.push(PT_PARALYSIS);
					potion_.push(PT_SLOW);
					potion_.push(PT_CONFUSE);
					potion_.push(PT_POISON);
					potion_type p_ = potion_.choice();
					printarray(true,false,false,CL_small_danger,3,"에이린은 당신에게 억지로 ",potion_iden_string[p_],"물약을 먹였다!");
					drinkpotion(p_, false);
				}
				break;
			case 1:
				{
					printarray(true,false,false,CL_small_danger,1,"에이린이 당신의 몸에 강제로 실험을 했다!");
					you.SetEirinHeal(you.GetMaxHp()*rand_int(70,80)/100,true);
					for(int i=0;i<3;i++)
						you.StatUpDown(-rand_int(1,4),randA(2)?(randA(1)?STAT_STR:STAT_DEX):STAT_INT,true);
				}
				break;
			}
		}
		break;
	case GT_YUYUKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//유령
			switch(rand_.pop())
			{
			case 0:
				{
					int i = rand_int(2+randA(you.level/10),5)+randA(you.level/3); 
					for(; i>0 ; i--)
					{
						if(monster *mon_ = BaseSummon(MON_GHOST, rand_int(20,40), true, true, 4, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level-1,4.0f,1.5f);
							mon_->image = &img_mons_ghost[randA(2)];
						}
					}
					summon_ = true;
					printarray(true,false,false,CL_yuyuko,1,"유유코는 당신의 주변에 유령을 끌어모았다!");
				}
				break;
			}
		}
		break;
	case GT_SATORI:
		break;
	case GT_TENSI:
		tensi_action();
		break;
	case GT_SEIJA:
		{
			god_type god_ = GT_SEIJA;
				
			while(god_ == GT_SEIJA || god_ == GT_SATORI)
				god_ = (god_type)rand_int(GT_BYAKUREN,GT_LILLY);
			printarray(true,false,false,CL_seija,3,"세이자는 당신과 ",GetGodString(god_),"의 관계를 이간질했다!");
			
			you.PunishUpDown(rand_int(3,4),god_);
		}
		break;
	case GT_LILLY:
		{
			random_extraction<int> rand_;
			rand_.push(0,35);//약화
			rand_.push(1,65);//요정소환
			switch(rand_.pop())
			{
			case 0:		
				{
					you.SetForceStrong(false, rand_int(20,40),true);
					printarray(true,false,false,CL_lilly,1,"릴리는 당신의 힘을 빼앗았다!");
				}
				break;
			case 1:
				{
					random_extraction<int> id_;
					id_.push(MON_FAIRY_GREEN,50);
					id_.push(MON_FAIRY_BLUE,30);
					id_.push(MON_FAIRY_RED,20);
					int i =rand_int(3,5); 
					for(; i>0 ; i--)
					{
						int level_ =rand_int(rand_int(1,you.level),you.level); 

						if(monster *mon_ = BaseSummon(id_.choice(), rand_int(60,120), true, true, 3, NULL, you.position, SKD_OTHER, -1))
						{						
							while(level_ > mon_->level)
							{
								mon_->LevelUpdown(1,6.0f,1.0f);
								switch(mon_->id)
								{
								case MON_FAIRY_GREEN:
									if(mon_->level >= 5)
										mon_->ChangeMonster(MON_FAIRY_GREEN_WARRIOR,0);
									break;
								case MON_FAIRY_BLUE:
									if(mon_->level >= 7)
										mon_->ChangeMonster(MON_FAIRY_BLUE_MAGICIAN,0);
									break;
								case MON_FAIRY_RED:
									if(mon_->level >= 8)
										mon_->ChangeMonster(MON_FAIRY_RED_COMMANDER,0);
									break;
								case MON_FAIRY_GREEN_WARRIOR:
									if(mon_->level >= 12)
										mon_->ChangeMonster(MON_FAIRY_HERO,0);
									break;
								case MON_FAIRY_BLUE_MAGICIAN:
									if(mon_->level >= 10)
										mon_->ChangeMonster(MON_FAIRY_SOCERER,0);
									break;
								case MON_FAIRY_RED_COMMANDER:
									if(mon_->level >= 13)
										mon_->ChangeMonster(MON_FAIRY_GREEN_WARRIOR,0);
									break;
								}
							}
							mon_->SetForceStrong(true, 100,false);
						}
					}
					summon_ = true;
					printarray(true,false,false,CL_lilly,1,"릴리는 당신에게 적대적인 요정의 무리를 소환했다!");
				}
				break;
			}
		}
		break;
	case GT_MIKO:
	{
		random_extraction<int> rand_;
		rand_.push(0, 33);//허약
		rand_.push(1, 33);//감속
		rand_.push(2, 33);//스탯빼앗기
		int time_ = rand_int(80, 160);
		env[current_level].MakeNoise(you.position, 20, NULL);
		switch (rand_.pop())
		{
		case 0:
		{
			printarray(false, false, false, CL_miko, 1, "미코는 당신의 체력을 빼앗아갔다! ");
			you.SetBuff(BUFFSTAT_HP, BUFF_DUPLE, -(you.GetMaxHp()/2), time_);
		}
		break;
		case 1:
		{
			printarray(false, false, false, CL_junko, 1, "미코는 당신을 느리게했다! ");
			you.SetSlow(time_);
		}
		break;
		case 2:
		{
			printarray(false, false, false, CL_junko, 1, "미코는 당신의 저항을 낮추었다! ");
			you.SetBuff(BUFFSTAT_RF, BUFF_MIKO_RF_MINUS, -1, time_);
			you.SetBuff(BUFFSTAT_RC, BUFF_MIKO_RC_MINUS, -1, time_);
		}
		break;
		}
	}
	break;
	case GT_OKINA:
		{
			random_extraction<int> rand_;
			rand_.push(0, 50);//마이, 사토노 소환
			rand_.push(1, 50);//체력, 영력감소
			switch (rand_.pop())
			{
			case 0:
				{
					int isYourSight = 0;
					deque<monster*> dq;
					for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
					{
						if (it->isLive() && !it->isUserAlly())
						{
							if (it->isYourShight()){
								isYourSight++;
							}
						}
					}

					if (isYourSight)
					{
						printarray(true, false, false, CL_okina, 1, "오키나는 백댄서를 불러냈다!");

						int time_ = rand_int(40, 60);
						if (monster *mon_ = BaseSummon(MON_MAI2, time_, true, true, 3, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level, 6);
						}
						if (monster *mon_ = BaseSummon(MON_SATONO, time_, true, true, 3, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level, 6);
						}
						break;
					}
					else
					{
						//아무도 시야내에 없으면 백댄서를 부르지않는다(의미가 없음)
						you.HpUpDown(-you.GetMaxHp() / 2, DR_EFFECT);
						if(!you.pure_mp)
							you.MpUpDown(-you.max_mp / 2);
						printarray(true, false, false, CL_okina, 1, "오키나의 분노로 당신의 체력과 영력이 흡수되었다!");
						break;
					}
				}
				break;
			case 1:
				{
					you.HpUpDown(-you.GetMaxHp()/2, DR_EFFECT);
					if (!you.pure_mp)
						you.MpUpDown(-you.max_mp/2);
					printarray(true, false, false, CL_okina, 1, "오키나의 분노로 당신의 체력과 영력이 흡수되었다!");
					break;
				}
				break;
			}
		}
		break;
	case GT_JUNKO:
		{
			random_extraction<int> rand_;
			rand_.push(0, 33);//약화
			rand_.push(1, 33);//감속
			rand_.push(2, 33);//스탯빼앗기
			int time_ = rand_int(50, 80);
			you.SetPureTurn(randA(1)?30:20, time_);
			switch (rand_.pop())
			{
			case 0:
			{
				printarray(false, false, false, CL_junko, 1, "순호는 당신의 힘을 약화하였다! ");
				you.SetForceStrong(false, time_, true);
			}
			break;
			case 1:
			{
				printarray(false, false, false, CL_junko, 1, "순호는 당신의 속도를 빼앗았다! ");
				you.SetSlow(time_);
			}
			break;
			case 2:
			{
				printarray(false, false, false, CL_junko, 1, "순호는 당신의 능력치를 빼앗았다! ");
				for (int i = 0; i<3; i++)
					you.StatUpDown(-rand_int(1, 2), randA(2) ? (randA(1) ? STAT_STR : STAT_DEX) : STAT_INT, true);
			}
			break;
			}
		}
		break;
	}

	if (summon_) {
		if (you.god == GT_SEIJA 
			&& pietyLevel(you.piety) >= 2
			&& !you.GetPunish(GT_SEIJA)) {
			printlog(seija_summon_buff(), true, false, false, CL_seija);
			you.SetHaste(rand_int(20, 40));
		}
	}


	return false;		
}


void createGold(coord_def c, int num) {
	rand_rect_iterator rit(c, 2, 2);
	int i = num;
	for (; !rit.end() && i> 0; rit++)
	{
		if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y))
		{
			int rand_ = randA(2);
			env[current_level].MakeFloorEffect(coord_def(rit->x, rit->y), &img_effect_gold_floor[rand_], &img_effect_gold_floor[rand_],  FLOORT_GOLD, rand_int(20, 30), &you);
		}
		i--;
	}
}

void joonRandomBuff() {
	//가속
	//힘
	//민첩
	//지능
	//AC증가
	random_extraction<int> rand_;

	rand_.push(0);
	rand_.push(1);
	rand_.push(2);
	rand_.push(3);
	rand_.push(4);
	//rand_.push(5);

	switch (rand_.pop())
	{
	case 0:
		you.SetHaste(rand_int(30, 60));
		break;
	case 1:
		you.SetMight(rand_int(30, 60));
		break;
	case 2:
		you.SetAgility(rand_int(30, 60));
		break;
	case 3:
		you.SetClever(rand_int(30, 60));
		break;
	case 4:
		printlog("당신은 단단해졌다. ", false, false, false, CL_white_blue);
		you.SetBuff(BUFFSTAT_AC, BUFF_JOON_AC, 8, rand_int(30, 60));
		break;
	}
	enterlog();
}
bool sionResurrection() {
	random_extraction<char> rand_;
	for (auto it = you.item_list.begin(); it != you.item_list.end(); it++) {
		if ((*it).type == ITM_POTION || (*it).type == ITM_SCROLL) {
			for(int i = 0; i < it->num; i++)
				rand_.push(it->id);
		}
	}

	if (randA(99) < rand_.GetSize() * 10)
	{
		
		for (int i = 0; i < 10; i++)
		{
			char key_ = rand_.pop();
			list<item>::iterator it;
			for (it = you.item_list.begin(); it != you.item_list.end(); it++)
			{
				if ((*it).id == key_)
				{
					you.DeleteItem(it, 1);
					break;
				}
			}
			if (rand_.GetSize() == 0)
				break;
		}
		return true;
	}
	return false;
}

void godAutoPickUp(god_type god_, bool belive_) {

	switch (god_)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
		break;
	case GT_YUUGI:
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_ALCOHOL] = belive_;
		break;
	case GT_SHIZUHA:
	case GT_HINA:
		break;
	case GT_YUKARI:
		iden_list.autopickup[IDEN_CHECK_SCROLL_START + SCT_BLINK] = !belive_;
		iden_list.autopickup[IDEN_CHECK_SCROLL_START + SCT_TELEPORT] = !belive_;
		//공간이동
		break;
	case GT_EIRIN:
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_POISON] = belive_;
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_PARALYSIS] = belive_;
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_CONFUSE] = belive_;
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_SLOW] = belive_;
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_DOWN_STAT] = belive_;
		//포션 다 주워
		break;
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
	default:
		break;
	}
}


int getMikoPiety(int kind) {
	switch (kind){
		case 0:
			return 4;
		case 1:
			return 10;
		case 2:
			return 30;
		case 3:
			return 100;
		case 4:
			return 200;
	}
	return 0;
}


void printReEnter()
{
	if (you.GetPunish(you.god)) {
		printlog("환상향에 돌아온걸 환영한다!", true, false, false, CL_normal);
		return;
	}
	switch (you.god)
	{
	case GT_BYAKUREN:
		printlog("히지리: 어서오세요. 신도여", true, false, false, CL_white_blue);
		break;
	case GT_JOON_AND_SION:
		switch (randA(1))
		{
		case 0:
			printlog("죠온: 한푼도 남김없이 모두 털어버리자고!", true, false, false, CL_joon);
			break;
		case 1:
			printlog("시온: 배고파...", true, false, false, CL_sion);
			break;
		}
		break;
	case GT_KANAKO:
		//사나에전용 대사 필요
		printlog("카나코: 끊임없는 전투로 신앙을 보이도록 하여라!", true, false, false, CL_help);
		break;
	case GT_SUWAKO:
		printlog("스와코: 하하하! 재밌어졌어", true, false, false, CL_swako);
		break;
	case GT_MINORIKO:
		printlog("미노리코: 이 땅에 가을의 축복을!", true, false, false, CL_warning);
		break;
	case GT_MIMA:
		printlog("미마: 압도적인 마법으로!", true, false, false, CL_green);
		break;
	case GT_SHINKI:
		printlog("신키에게 P와 영혼을!", true, false, false, CL_warning);
		break;
	case GT_YUUGI:
		printlog("유우기: 더 강한 상대를 찾아라!", true, false, false, CL_yuigi);
		break;
	case GT_SHIZUHA:
		printlog("시즈하: 인기 있는 녀석은 모두 죽여라...", true, false, false, CL_small_danger);
		break;
	case GT_HINA:
		printlog("히나: 그럼 액땜작업을 계속 하겠어", true, false, false, CL_hina);
		break;
	case GT_YUKARI:
		printlog("유카리: 돌아왔구나", true, false, false, CL_yukari);
		break;
	case GT_EIRIN:
		printlog("에이린: 새로운 실험체가 필요해졌어", true, false, false, CL_small_danger);
		break;
	case GT_YUYUKO:
		printlog("유유코: 차라도 한잔 할래?", true, false, false, CL_yuyuko);
		break;
	case GT_SATORI:
		printlog("사토리: 마음대로 뛰어 노세요. 던전은 넓으니까요.", true, false, false, CL_danger);
		break;
	case GT_TENSI:
		printlog("텐시: 천계는 지루해! 넌 날 재밌게 해줄거지?", true, false, false, CL_tensi);
		break;
	case GT_SEIJA:
		printlog("세이자: 자, 레지스탕스 활동의 개시다!", true, false, false, CL_seija);
		break;
	case GT_LILLY:
		printlog("릴리: 봄이에요!", true, false, false, CL_lilly);
		break;
	case GT_MIKO:
		printlog("미코: 모두의 욕망을 들어보도록 하지!", true, false, false, CL_miko);
		break;
	case GT_OKINA:
		printlog("오키나: 이 세계에서 나를 각인시키도록 ", true, false, false, CL_okina);
		break;
	case GT_JUNKO:
		printlog("순호: 상아여, 보고 있는가?", true, false, false, CL_junko);
		break;
	case GT_ERROR:
	case GT_NONE:
	default:
		printlog("환상향에 돌아온걸 환영한다!", true, false, false, CL_normal);
		break;
	}


}










bool God_PraySpeak()
{
	int level_ = pietyLevel(you.piety);
	switch (you.god)
	{
	case GT_BYAKUREN:
		switch (level_)
		{
		default:
		case 0:
			printlog("히지리: 아아, 법의 세계에 빛이 가득해", true, false, false, CL_white_blue);
			return true;
		case 1:
			printlog("히지리: 우리 절은 인간과 요괴를 차별하지않는답니다.", true, false, false, CL_white_blue);
			return true;
		case 2:
			printlog("히지리: 고된 수행은 마음을 깨끗하게 하지요.", true, false, false, CL_white_blue);
			return true;
		case 3:
			printlog("히지리: 당신의 노력은 결실을 맺을거랍니다.", true, false, false, CL_white_blue);
			return true;
		case 4:
			printlog("히지리: 비록 마법을 쓰는자라도 몸을 단련해야합니다.", true, false, false, CL_white_blue);
			return true;
		case 5:
			printlog("히지리: 당신이 배운 불교의 가르침을 모두에게 전하세요.", true, false, false, CL_white_blue);
			return true;
		case 6:
			printlog("히지리: 어서오세요. 진정한 부처님의 제자여", true, false, false, CL_white_blue);
			return true;
		}
	case GT_ERROR:
	case GT_NONE:
		return false; 
	case GT_JOON_AND_SION:
		switch (level_)
		{
		default:
		case 0:
			if (randA(1))
				printlog("죠온: 새로운 호구... 아니 고객이 왔네!", true, false, false, CL_joon);
			else
				printlog("시온: 배고프다...", true, false, false, CL_sion);
			return true;
		case 1:
			if (randA(1))
				printlog("죠온: 좀 더 팍팍 써도 된다고", true, false, false, CL_joon);
			else
				printlog("시온: 밥은 어딨어?", true, false, false, CL_sion);
			return true;
		case 2:
			if (randA(1))
				printlog("죠온: 저기 새 명품 핸드백이 사고싶은데 말이야", true, false, false, CL_joon);
			else
				printlog("시온: 왜 역병신인 우리를 믿고있는거야?", true, false, false, CL_sion);
			return true;
		case 3:
			if (randA(1))
				printlog("죠온: 응? 카드가 필요해?", true, false, false, CL_joon);
			else
				printlog("시온: 불우이웃돕기는 어때?", true, false, false, CL_sion);
			return true;
		case 4:
			if (randA(1))
				printlog("죠온: 아끼다 죽을바엔 모두 써버려!", true, false, false, CL_joon);
			else
				printlog("시온: 최근엔 배고파도 즐거워", true, false, false, CL_sion);
			return true;
		case 5:
			if (randA(1))
				printlog("죠온: 우리들이라면 모두를 털어버릴 수 있어!", true, false, false, CL_joon);
			else
				printlog("시온: 나도 도움이 될 수 있을까?", true, false, false, CL_sion);
			return true;
		case 6:
			printlog("죠온&시온: 최흉최악의 자매의 힘을 보여주지! ", false, false, false, CL_joon_and_sion);
			return true;
		}
	case GT_KANAKO:
		if (you.char_name.name.compare("사나에") == 0)
		{
			printlog("카나코: 무리는 하지말렴. 사나에", true, false, false, CL_help);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog("카나코: 끊임없는 전투로 신앙을 증명하거라", true, false, false, CL_help);
			return true;
		case 1:
			printlog("카나코: 나를 부른 이는 누구인가?", true, false, false, CL_help);
			return true;
		case 2:
			printlog("카나코: 신앙을 방해하는 자는 모두 제거하라", true, false, false, CL_help);
			return true;
		case 3:
			printlog("카나코: 그대의 신앙에는 힘으로서 보답하지", true, false, false, CL_help);
			return true;
		case 4:
			printlog("카나코: 산의 신앙을 더욱 더 퍼트리도록", true, false, false, CL_help);
			return true;
		case 5:
			printlog("카나코: 한때 전투의 신으로 불렸던 몸. 그 힘을 느끼게해주지", true, false, false, CL_help);
			return true;
		case 6:
			printlog("카나코: 진정한 전투의 화신이여 앞으로 나아가라!", true, false, false, CL_help);
			return true;
		}
	case GT_SUWAKO:
		if (you.char_name.name.compare("사나에") == 0)
		{
			printlog("스와코: 요괴퇴치의 시간이야 사나에!", true, false, false, CL_swako);
			return true;
		}
		switch (randA(4))
		{
		default:
		case 0:
			printlog("스와코: 응? 나 불렀어?", true, false, false, CL_swako);
			return true;
		case 1:
			printlog("스와코: 최근의 신도들은 원하는게 많다니깐", true, false, false, CL_swako);
			return true;
		case 2:
			printlog("스와코: 내가 재앙신인걸 잊지말아~", true, false, false, CL_swako);
			return true;
		case 3:
			printlog("스와코: 좀 더 노력하라고~", true, false, false, CL_swako);
			return true;
		case 4:
			printlog("스와코: 걱정하지마, 충분히 힘은 줄테니깐", true, false, false, CL_swako);
			return true;
		}
	case GT_MINORIKO:
		switch (level_)
		{
		default:
		case 0:
			printlog("미노리코: 당신도 가을에 반한거야?", true, false, false, CL_warning);
			return true;
		case 1:
			printlog("미노리코: 수확을 위해선 그만큼의 노력이 필요한거야", true, false, false, CL_warning);
			return true;
		case 2:
			printlog("미노리코: 가을은 정말 아름다운 계절이야!", true, false, false, CL_warning);
			return true;
		case 3:
			printlog("미노리코: 내가 준 고구마는 입맛에 맞아?", true, false, false, CL_warning);
			return true;
		case 4:
			printlog("미노리코: 배는 든든하게 하고 다니지?", true, false, false, CL_warning);
			return true;
		case 5:
			printlog("미노리코: 쌓아올린 모든 노력을 풍년으로 보답할때야!", true, false, false, CL_warning);
			return true;
		case 6:
			printlog("미노리코: 가을의 사도여! 나아가서 가을의 위대함을 알려라!", true, false, false, CL_warning);
			return true;
		}
	case GT_MIMA:
		if (you.char_name.name.compare("마리사") == 0)
		{
			printlog("미마: 오랫만이네, 잘 지내고 있어?", true, false, false, CL_green);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog("미마: 새로운 입교 희망자인가?", true, false, false, CL_green);
			return true;
		case 1:
			printlog("미마: 사실 최근엔 제자는 받지않았었지만 특별케이스야", true, false, false, CL_green);
			return true;
		case 2:
			printlog("미마: 마법의 기본은 파워다. 적어두도록", true, false, false, CL_green);
			return true;
		case 3:
			printlog("미마: 선수필승. 먼저 공격한 쪽이 이긴다.", true, false, false, CL_green);
			return true;
		case 4:
			printlog("미마: 내 궁극의 마법이 궁금한가?", true, false, false, CL_green);
			return true;
		case 5:
			printlog("미마: 더 이상 내가 가르쳐줄 마법은 없다.", true, false, false, CL_green);
			return true;
		case 6:
			printlog("미마: 마법의 힘으로 길을 열어라!", true, false, false, CL_green);
			return true;
		}
	case GT_SHINKI:
		switch (level_)
		{
		default:
		case 0:
			printlog("신키에게 P와 영혼을! ", true, false, false, CL_warning);
			return true;
		}
	case GT_YUUGI:
		switch (level_)
		{
		default:
		case 0:
			printlog("유우기: 넌 얼마나 강하지?", true, false, false, CL_yuigi);
			return true;
		case 1:
			printlog("유우기: 강한 적과 붙어서 너의 강함을 증명해!", true, false, false, CL_yuigi);
			return true;
		case 2:
			printlog("유우기: 난 거짓말을 하는 녀석이 싫어", true, false, false, CL_yuigi);
			return true;
		case 3:
			printlog("유우기: 술은 많이 마실 수 있어?", true, false, false, CL_yuigi);
			return true;
		case 4:
			printlog("유우기: 네가 싸우는걸 보면 왠지 즐거운데!", true, false, false, CL_yuigi);
			return true;
		case 5:
			printlog("유우기: 나중에 나랑 한번 싸워보지않을래?", true, false, false, CL_yuigi);
			return true;
		case 6:
			printlog("유우기: 다음엔 술자리에 초대할테니 꼭 살아서 돌아오라고!", true, false, false, CL_yuigi);
			return true;
		}
	case GT_SHIZUHA:
		switch (level_)
		{
		default:
		case 0:
		case 1:
		case 2:
			printlog("시즈하는 조용히 당신을 보고있다.", true, false, false, CL_warning);
			return true;
		case 3:
		case 4:
			printlog("시즈하는 당신의 기도에 고개를 끄덕였다.", true, false, false, CL_warning);
			return true;
		case 5:
			printlog("시즈하: ...이제 우리들의 차례야...", true, false, false, CL_small_danger);
			return true;
		case 6:
			printlog("시즈하: 다음 인기투표는 꼭 부탁할게", true, false, false, CL_small_danger);
			return true;
		}
	case GT_HINA:
		switch (level_)
		{
		default:
		case 0:
			printlog("히나: 이 곳엔 재액이 가득해", true, false, false, CL_hina);
			return true;
		case 1:
			printlog("히나: 조금씩 조금씩 액땜을 해나가자", true, false, false, CL_hina);
			return true;
		case 2:
			printlog("히나: 액땜을 방해하는 녀석들은 배제해도 좋아", true, false, false, CL_hina);
			return true;
		case 3:
			printlog("히나: 더욱 더 많은 저주를 모으도록 해", true, false, false, CL_hina);
			return true;
		case 4:
			printlog("히나: 나에겐 그동안 누구도 말을 걸어주지않았어", true, false, false, CL_hina);
			return true;
		case 5:
			printlog("히나: 저주를 모으는 작업은 외로운거지", true, false, false, CL_hina);
			return true;
		case 6:
			printlog("히나: 너는 나와 끝까지 같이 있어줄거지?", true, false, false, CL_hina);
			return true;
		}
	case GT_YUKARI:
		if (you.char_name.name.compare("레이무") == 0)
		{
			printlog("유카리: 환상향의 무녀의 본분이 뭔지 기억하고있지?", true, false, false, CL_yukari);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog("유카리: 당신이 나의 새로운 식신?", true, false, false, CL_yukari);
			return true;
		case 1:
			printlog("유카리: 환상향은 모든 것을 수용해", true, false, false, CL_yukari);
			return true;
		case 2:
			printlog("유카리: 결계의 보수작업이 필요해", true, false, false, CL_yukari);
			return true;
		case 3:
			printlog("유카리: 사태의 원인을 알기위해서라도 더 많은 정보가 필요해", true, false, false, CL_yukari);
			return true;
		case 4:
			printlog("유카리: 당신만 믿고있어. 도움이 필요하면 말해", true, false, false, CL_yukari);
			return true;
		case 5:
			printlog("유카리: 내 힘을 받으면 더 이상 경계의 유무는 무의미해", true, false, false, CL_yukari);
			return true;
		case 6:
			printlog("유카리: 당신만이 할 수 있는 일이야", true, false, false, CL_yukari);
			return true;
		}
	case GT_EIRIN:
		if (you.char_name.name.compare("모코우") == 0)
		{
			printlog("에이린: 최근에도 공주님과는 사이좋게 지내나요?", true, false, false, CL_small_danger);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog("에이린: 새로운 실험체가 필요해...", true, false, false, CL_small_danger);
			return true;
		case 1:
			printlog("에이린: 이 약을 먹어보고 부작용은 없었어?", true, false, false, CL_small_danger);
			return true;
		case 2:
			printlog("에이린: 좀 더 많은 표본이 필요해", true, false, false, CL_small_danger);
			return true;
		case 3:
			printlog("에이린: 독을 알면 약도 만들 수 있는거야", true, false, false, CL_small_danger);
			return true;
		case 4:
			printlog("에이린: 부작용을 두려워하지마. 효과는 확실해", true, false, false, CL_small_danger);
			return true;
		case 5:
			printlog("에이린: 내가 준 약이라면 실패하지않을거야", true, false, false, CL_small_danger);
			return true;
		case 6:
			printlog("에이린: 이것이 너의 새로운 모습이야", true, false, false, CL_small_danger);
			return true;
		}
	case GT_YUYUKO:
		if (you.char_name.name.compare("모코우") == 0)
		{
			printlog("유유코: 불로불사인 당신이 왜 날 믿는거야?", true, false, false, CL_yuyuko);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
		case 1:
			printlog("유유코: 새로운 식단은 아직이니?", true, false, false, CL_yuyuko);
			return true;
		case 2:
		case 3:
			printlog("유유코: 좀 더 느긋하게 있어도 좋아.", true, false, false, CL_yuyuko);
			return true;
		case 4:
			printlog("유유코: 유령은 차갑고 귀엽지않아?", true, false, false, CL_yuyuko);
			return true;
		case 5:
			printlog("유유코: 친구들은 마음에 들어?", true, false, false, CL_yuyuko);
			return true;
		case 6:
			printlog("유유코: 물론 죽더라도 영혼은 함께란다", true, false, false, CL_yuyuko);
			return true;
		}
	case GT_SATORI:
		switch (level_)
		{
		default:
		case 0:
		case 1:
			printlog("사토리는 당신에게 큰 관심이 없다. ", true, false, false, CL_warning);
			return true;
		case 2:
			printlog("사토리는 당신에게 미소지었다. ", true, false, false, CL_warning);
			return true;
		case 3:
			printlog("사토리: 애완동물의 재롱은 언제나 보기 좋군요.", true, false, false, CL_danger);
			return true;
		case 4:
			printlog("사토리는 당신을 쓰다듬었다. ", true, false, false, CL_warning);
			return true;
		case 5:
			printlog("사토리: 오늘의 사료는 입맛에 맞나요?", true, false, false, CL_danger);
			return true;
		case 6:
			printlog("사토리: 다음에 같이 산책하러 가지 않을래요?", true, false, false, CL_danger);
			return true;
		}
	case GT_TENSI:
		switch (randA(9))
		{
		default:
		case 0:
			printlog("텐시: 뭐야! 지금 바빠!", true, false, false, CL_tensi);
			return true;
		case 1:
			printlog("텐시: 기도하는거만으로 요행을 바라는건 너무 이기적이지 않아?", true, false, false, CL_tensi);
			return true;
		case 2:
			printlog("텐시: 재미있는 일은 없는거야?", true, false, false, CL_tensi);
			return true;
		case 3:
			printlog("텐시: 오랫만에 지진을 일으켜볼까...", true, false, false, CL_tensi);
			return true;
		case 4:
			printlog("텐시: 한번만 더 귀찮게하면 돌을 던질꺼야!", true, false, false, CL_tensi);
			return true;
		case 5:
			printlog("텐시는 당신에게 돌을 던졌다.", true, false, false, CL_warning);
			return true;
		case 6:
			printlog("텐시는 당신을 보고 키득키득 웃고있다.", true, false, false, CL_warning);
			return true;
		case 7:
			printlog("텐시는 당신을 보고 따분한듯 하품하고 있다.", true, false, false, CL_warning);
			return true;
		case 8:
			printlog("텐시는 당신의 기도를 무시했다.", true, false, false, CL_warning);
			return true;
		case 9:
			printlog("텐시는 산갈치로 당신의 머리를 때렸다.", true, false, false, CL_warning);
			return true;
		}
	case GT_SEIJA:
		switch (level_)
		{
		default:
		case 0:
		case 1:
			printlog("세이자는 당신의 기도를 무시했다.", true, false, false, CL_warning);
			return true;
		case 2:
			printlog("세이자는 당신에 큰 관심이 없어보인다.", true, false, false, CL_warning);
			return true;
		case 3:
			printlog("세이자의 표정은 그다지 안 좋아보인다.", true, false, false, CL_warning);
			return true;
		case 4:
			printlog("세이자: 반칙이라도 살아남는다면 그걸로 충분해", true, false, false, CL_seija);
			return true;
		case 5:
			printlog("세이자: 레지스탕스 생활은 마음에 들어?", true, false, false, CL_seija);
			return true;
		case 6:
			printlog("세이자: 우린 최고의 파트너야 친구!", true, false, false, CL_seija);
			return true;
		}
	case GT_LILLY:
		return false;
	case GT_MIKO:
		return false;
	case GT_OKINA:
		switch (level_)
		{
		default:
		case 0:
			printlog("오키나: 네가 제 수행원으로 맡는지 테스트해볼거야.", true, false, false, CL_okina);
			return true;
		case 1:
			printlog("오키나: 면접은 없어, 실전 테스트로 채용을 결정하지", true, false, false, CL_okina);
			return true;
		case 2:
			printlog("오키나: 나의 존재는 항상 알려져야만 한다", true, false, false, CL_okina);
			return true;
		case 3:
			printlog("오키나: 등 뒤의 문으로 내 힘을 받도록 해라", true, false, false, CL_okina);
			return true;
		case 4:
			printlog("오키나: 슬슬 마이와 사토노는 해방시켜줄까 생각중이다", true, false, false, CL_okina);
			return true;
		case 5:
			printlog("오키나: 실로 네 부하에 맞는 인재로구나. 합격이다!", true, false, false, CL_okina);
			return true;
		case 6:
			printlog("오키나: 보라! 들으라! 말하라! 비신의 진정한 마력을 받아라!", true, false, false, CL_okina);
			return true;
		}
	case GT_JUNKO:
		switch (level_)
		{
		default:
		case 0:
			printlog("순호: 상아여 보고있는가!", true, false, false, CL_junko);
			return true;
		}
	}
	return false;

}