//////////////////////////////////////////////////////////////////////////////////////////////////
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
#include "steam_api.h"
#include "swako.h"
#include "note.h"
#include "rand_shuffle.h"
#include "seija.h"
#include "lilly.h"
#include "tribe.h"
#include "localization.h"
#include <iomanip>
#include <string>

extern HANDLE mutx;

string GetGodString(god_type god)
{
	switch(god)
	{
	case GT_ERROR:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_ERROR);
	case GT_NONE:
	default:
		return "";
	case GT_JOON_AND_SION:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION);
	case GT_BYAKUREN:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN);
	case GT_KANAKO:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO);
	case GT_SUWAKO:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SUWAKO);
	case GT_MINORIKO:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO);
	case GT_MIMA:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA);
	case GT_SHINKI:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI);
	case GT_YUUGI:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI);
	case GT_SHIZUHA:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA);
	case GT_HINA:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_HINA);
	case GT_YUKARI:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI);
	case GT_EIRIN:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN);
	case GT_YUYUKO:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO);
	case GT_SATORI:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI);
	case GT_TENSI:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI);
	case GT_SEIJA:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA);
	case GT_LILLY:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY);
	case GT_MIKO:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO);
	case GT_OKINA:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA);
	case GT_JUNKO:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO);
	}
	return LocalzationManager::locString(LOC_SYSTEM_GOD_ERROR);
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
	default:
		return false;
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
		switch (level)
		{
		case 0:
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY0_ADD), true, false, false, CL_joon_and_sion);
			break;
		case 1:
			you.Ability(SKL_JOON_AND_SION_1, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY1_ADD), true, false, false, CL_joon_and_sion);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY1_REMOVE), true, false, false, CL_joon_and_sion);
			break;
		case 2:
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY2_ADD), true, false, false, CL_joon_and_sion);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY2_REMOVE), true, false, false, CL_joon_and_sion);
			break;
		case 4:
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY4_ADD), true, false, false, CL_joon_and_sion);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY4_REMOVE), true, false, false, CL_joon_and_sion);
			break;
		case 5:
			if (plus)
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY5_ADD), true, false, false, CL_joon_and_sion);
				if (you.god_value[GT_JOON_AND_SION][0] == 1)
					you.Ability(SKL_JOON_AND_SION_2, true, !plus);
				else if (you.god_value[GT_JOON_AND_SION][0] == 2)
					you.Ability(SKL_JOON_AND_SION_3, true, !plus);
			}
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY5_REMOVE), true, false, false, CL_joon_and_sion);
			break;
		case 6:
			if (you.god_value[GT_JOON_AND_SION][0] != 0)
				you.Ability(SKL_JOON_AND_SION_4, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY6_ADD), true, false, false, CL_joon_and_sion);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_GAIN_ABLILITY6_REMOVE), true, false, false, CL_joon_and_sion);
			break;
		}
		return false;
	case GT_BYAKUREN:
		switch(level)
		{
		case 1:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY1_ADD),true,false,false,CL_white_blue);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY1_REMOVE),true,false,false,CL_white_blue);
			break;
		case 2:
			you.remainSpellPoiont+=plus;
			you.Ability(SKL_BYAKUREN_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY2_ADD),true,false,false,CL_white_blue);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY2_REMOVE),true,false,false,CL_white_blue);
			break;
		case 3:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY3_ADD),true,false,false,CL_white_blue);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY3_REMOVE),true,false,false,CL_white_blue);
			break;
		case 4:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY4_ADD),true,false,false,CL_white_blue);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY4_REMOVE),true,false,false,CL_white_blue);
			break;
		case 5:
			you.remainSpellPoiont+=plus;
			you.Ability(SKL_BYAKUREN_2,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY5_ADD),true,false,false,CL_white_blue);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_GAIN_ABLILITY5_REMOVE),true,false,false,CL_white_blue);
			break;
		}
		return false;
	case GT_KANAKO:
		switch(level)
		{
		case 1:
			you.Ability(SKL_KANAKO_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_GAIN_ABLILITY1_ADD),true,false,false,CL_help);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_GAIN_ABLILITY1_REMOVE),true,false,false,CL_help);
			break;
		case 3:
			you.Ability(SKL_KANAKO_2,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_GAIN_ABLILITY3_ADD),true,false,false,CL_help);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_GAIN_ABLILITY3_REMOVE),true,false,false,CL_help);
			break;
		case 5:
			you.Ability(SKL_KANAKO_3,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_GAIN_ABLILITY5_ADD),true,false,false,CL_help);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_GAIN_ABLILITY5_REMOVE),true,false,false,CL_help);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY1_ADD),true,false,false,CL_warning);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY1_REMOVE),true,false,false,CL_warning);
			break;
		case 2:
			you.Ability(SKL_MINORIKO_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY2_ADD),true,false,false,CL_warning);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY2_REMOVE),true,false,false,CL_warning);
			break;
		case 3:
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY3_ADD),true,false,false,CL_warning);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY3_REMOVE),true,false,false,CL_warning);
			break;
		case 4:
			you.Ability(SKL_MINORIKO_2,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY4_ADD),true,false,false,CL_warning);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY4_REMOVE),true,false,false,CL_warning);
			break;
		case 5:
			//if(you.power>=500)
			//{			
			//	you.ResistUpDown(plus,RST_FIRE);
			//	you.ResistUpDown(plus,RST_ICE);
			//}
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY5_ADD),true,false,false,CL_warning);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_GAIN_ABLILITY5_REMOVE),true,false,false,CL_warning);
			break;
		}
		return false;
	case GT_MIMA:
		switch(level)
		{
			case 0:
				you.max_mp+=plus;
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_GAIN_ABLILITY0_ADD),true,false,false,CL_green);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_GAIN_ABLILITY0_REMOVE),true,false,false,CL_green);
				break;
			case 1:
				you.max_mp+=plus;
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_GAIN_ABLILITY1_ADD),true,false,false,CL_green);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_GAIN_ABLILITY1_REMOVE),true,false,false,CL_green);
				break;
			case 2:
				you.max_mp+=plus;
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_GAIN_ABLILITY2_ADD),true,false,false,CL_green);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_GAIN_ABLILITY2_REMOVE),true,false,false,CL_green);
				break;
			case 3:
				mima_gift(BOOK_CONJURE);
				you.max_mp+=plus;
				break;
			case 4:
				you.max_mp+=plus;
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_GAIN_ABLILITY4_ADD),true,false,false,CL_green);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_GAIN_ABLILITY4_REMOVE),true,false,false,CL_green);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_GAIN_ABLILITY1_ADD),true,false,false,CL_white_puple);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_GAIN_ABLILITY4_REMOVE),true,false,false,CL_white_puple);
				break;
			case 2:
				you.Ability(SKL_SHINKI_2,true,!plus);
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_GAIN_ABLILITY2_ADD),true,false,false,CL_white_puple);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_GAIN_ABLILITY2_REMOVE),true,false,false,CL_white_puple);
				break;
			case 3:
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_GAIN_ABLILITY3_ADD),true,false,false,CL_white_puple);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_GAIN_ABLILITY3_REMOVE),true,false,false,CL_white_puple);
				break;
			case 4:
				you.Ability(SKL_SHINKI_3,true,!plus);
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_GAIN_ABLILITY4_ADD),true,false,false,CL_white_puple);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_GAIN_ABLILITY4_REMOVE),true,false,false,CL_white_puple);
				break;
			case 5:
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_GAIN_ABLILITY5_ADD),true,false,false,CL_white_puple);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_GAIN_ABLILITY5_REMOVE),true,false,false,CL_white_puple);
				break;
		}
		return false;
	case GT_YUUGI:
		switch(level)
		{
		case 0:
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY0_ADD),true,false,false,CL_yuigi);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY0_REMOVE),true,false,false,CL_yuigi);
			break;
		case 1:
			you.Ability(SKL_YUUGI_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY1_ADD),true,false,false,CL_yuigi);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY1_REMOVE),true,false,false,CL_yuigi);
			break;
		case 2:
			you.Ability(SKL_YUUGI_2,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY2_ADD),true,false,false,CL_yuigi);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY2_REMOVE),true,false,false,CL_yuigi);
			break;
		case 3:
			you.Ability(SKL_YUUGI_3,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY3_ADD),true,false,false,CL_yuigi);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY3_REMOVE),true,false,false,CL_yuigi);
			break;
		case 4:
			you.Ability(SKL_YUUGI_4,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY4_ADD),true,false,false,CL_yuigi);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY4_REMOVE),true,false,false,CL_yuigi);
			break;
		case 5:
			you.Ability(SKL_YUUGI_5,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY5_ADD),true,false,false,CL_yuigi);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GAIN_ABLILITY5_REMOVE),true,false,false,CL_yuigi);
			break;
		}
		return false;
	case GT_SHIZUHA:
		switch(level)
		{
			case 0:
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY0_ADD),true,false,false,CL_autumn);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY0_REMOVE),true,false,false,CL_autumn);
				break;
			case 1:
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY1_ADD),true,false,false,CL_autumn);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY1_REMOVE),true,false,false,CL_autumn);
				break;
			case 2:
				you.Ability(SKL_SIZUHA_1,true,!plus);
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY2_ADD),true,false,false,CL_autumn);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY2_REMOVE),true,false,false,CL_autumn);
				break;
			case 3:
				you.Ability(SKL_SIZUHA_2,true,!plus);
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY3_ADD),true,false,false,CL_autumn);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY3_REMOVE),true,false,false,CL_autumn);
				break;
			case 4:
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY4_ADD),true,false,false,CL_autumn);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY4_REMOVE),true,false,false,CL_autumn);
				break;
			case 6:
				if(you.god_value[GT_SHIZUHA][0]==0)
				{
					you.Ability(SKL_SIZUHA_3,true,!plus);
					if(plus)
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY6_ADD),true,false,false,CL_autumn);
					else
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_GAIN_ABLILITY6_REMOVE),true,false,false,CL_autumn);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY0_ADD),true,false,false,CL_hina);
			}
			break;
		case 1:
			you.Ability(SKL_HINA_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY1_ADD),true,false,false,CL_hina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY1_REMOVE),true,false,false,CL_hina);
			break;
		case 2:
			you.Ability(SKL_HINA_2,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY2_ADD),true,false,false,CL_hina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY2_REMOVE),true,false,false,CL_hina);
			break;
		case 3:
			you.Ability(SKL_HINA_3,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY3_ADD),true,false,false,CL_hina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY3_REMOVE),true,false,false,CL_hina);
			break;
		case 4:
			you.Ability(SKL_HINA_4,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY4_ADD),true,false,false,CL_hina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY4_REMOVE),true,false,false,CL_hina);
			break;
		case 5:
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY5_ADD),true,false,false,CL_hina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY5_REMOVE),true,false,false,CL_hina);
			break;
		case 6:
			if(you.god_value[GT_HINA][0]==0)
			{
				you.Ability(SKL_HINA_5,true,!plus);
				if(plus)
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY6_ADD),true,false,false,CL_hina);
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_GAIN_ABLILITY6_REMOVE),true,false,false,CL_hina);
			}
			break;
		}
		return false;
	case GT_YUKARI:
		switch(level)
		{
		case 1:
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY1_ADD),true,false,false,CL_yukari);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY1_REMOVE),true,false,false,CL_yukari);
			break;
		case 2:
			you.Ability(SKL_YUKARI_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY2_ADD),true,false,false,CL_yukari);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY2_REMOVE),true,false,false,CL_yukari);
			break;
		case 3:
			you.Ability(SKL_YUKARI_2,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY3_ADD),true,false,false,CL_yukari);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY3_REMOVE),true,false,false,CL_yukari);
			break;
		case 4:
			you.Ability(SKL_YUKARI_3,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY4_ADD),true,false,false,CL_yukari);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY4_REMOVE),true,false,false,CL_yukari);
			break;
		case 5:
			you.Ability(SKL_YUKARI_4,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY5_ADD),true,false,false,CL_yukari);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_GAIN_ABLILITY5_REMOVE),true,false,false,CL_yukari);
			break;
		}
		return false;
	case GT_EIRIN:
		switch(level)
		{
		case 0:
			if(plus)
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY0_ADD),true,false,false,CL_small_danger);
				iden_list.potion_list[PT_POISON].iden = true;
				iden_list.potion_list[PT_DOWN_STAT].iden = true;
				iden_list.potion_list[PT_CONFUSE].iden = true;
				iden_list.potion_list[PT_SLOW].iden = true;
				iden_list.potion_list[PT_PARALYSIS].iden = true;
			}
			else
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY0_REMOVE),true,false,false,CL_small_danger);
			}
			break;
		case 1:
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY1_ADD),true,false,false,CL_small_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY1_REMOVE),true,false,false,CL_small_danger);
			break;
		case 2:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 1);
			you.Ability(SKL_EIRIN_0,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY2_ADD),true,false,false,CL_small_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY2_REMOVE),true,false,false,CL_small_danger);
			break;
		case 3:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 2);
			you.Ability(SKL_EIRIN_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY3_ADD),true,false,false,CL_small_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY3_REMOVE),true,false,false,CL_small_danger);
			break;
		case 4:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 3);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY4_ADD),true,false,false,CL_small_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY4_REMOVE),true,false,false,CL_small_danger);
			break;
		case 5:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 4);
			you.Ability(SKL_EIRIN_2,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY5_ADD),true,false,false,CL_small_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_GAIN_ABLILITY5_REMOVE),true,false,false,CL_small_danger);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GAIN_ABLILITY1_ADD),true,false,false,CL_yuyuko);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GAIN_ABLILITY1_REMOVE),true,false,false,CL_yuyuko);
			break;
		case 2:
			you.Ability(SKL_YUYUKO_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GAIN_ABLILITY2_ADD),true,false,false,CL_yuyuko);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GAIN_ABLILITY2_REMOVE),true,false,false,CL_yuyuko);
			break;
		case 3:
			you.Ability(SKL_YUYUKO_2,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GAIN_ABLILITY3_ADD),true,false,false,CL_yuyuko);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GAIN_ABLILITY3_REMOVE),true,false,false,CL_yuyuko);
			break;
		case 5:
			you.Ability(SKL_YUYUKO_3,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GAIN_ABLILITY5_ADD),true,false,false,CL_yuyuko);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GAIN_ABLILITY5_REMOVE),true,false,false,CL_yuyuko);
			break;
		}
		return false;
	case GT_SATORI:
		switch(level)
		{
		case 0:
			you.ResistUpDown(plus,RST_INVISIBLE);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY0_ADD),true,false,false,CL_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY0_REMOVE),true,false,false,CL_danger);
			break;
		case 1:
			you.Ability(SKL_SATORI_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY1_ADD),true,false,false,CL_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY1_REMOVE),true,false,false,CL_danger);
			break;
		case 2:
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY2_ADD),true,false,false,CL_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY2_REMOVE),true,false,false,CL_danger);
			break;
		case 3:
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY3_ADD),true,false,false,CL_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY3_REMOVE),true,false,false,CL_danger);
			break;
		case 4:
			you.Ability(SKL_SATORI_2,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY4_ADD),true,false,false,CL_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY4_REMOVE),true,false,false,CL_danger);
			break;
		case 5:
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY5_ADD),true,false,false,CL_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_GAIN_ABLILITY5_REMOVE),true,false,false,CL_danger);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GAIN_ABLILITY2_ADD), true, false, false, CL_seija);
			}
			else {
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GAIN_ABLILITY2_REMOVE), true, false, false, CL_seija);
			}
			break;
		case 3:
			you.Ability(SKL_SEIJA_1,true,!plus);
			if (plus) {
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GAIN_ABLILITY3_ADD), true, false, false, CL_seija);
			}
			else {
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GAIN_ABLILITY3_REMOVE),true,false,false,CL_seija);
		    }
			break;
		case 5:
			you.Ability(SKL_SEIJA_2,true,!plus);
			you.Ability(SKL_SEIJA_GIFT, true, true);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GAIN_ABLILITY5_ADD),true,false,false,CL_seija);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GAIN_ABLILITY5_REMOVE),true,false,false,CL_seija);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY1_1_ADD),true,false,false,CL_lilly);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY1_1_REMOVE),true,false,false,CL_lilly);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY1_2_ADD),true,false,false,CL_lilly);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY1_2_REMOVE),true,false,false,CL_lilly);
			break;
		case 2:
			you.Ability(SKL_LILLY_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY_FAIRY_ADD),true,false,false,CL_lilly);
			break;
		case 3:
			you.Ability(SKL_LILLY_1,true,!plus);
			you.Ability(SKL_LILLY_3,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY_FAIRY_ADD),true,false,false,CL_lilly);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY3_ADD),true,false,false,CL_lilly);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY3_REMOVE),true,false,false,CL_lilly);
			break;
		case 4:
			you.Ability(SKL_LILLY_1,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY_FAIRY_ADD),true,false,false,CL_lilly);
			break;
		case 5:
			you.Ability(SKL_LILLY_1,true,!plus);
			you.Ability(SKL_LILLY_4,true,!plus);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY_FAIRY_FINAL_ADD),true,false,false,CL_lilly);
			if(plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY5_ADD),true,false,false,CL_lilly);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_GAIN_ABLILITY5_REMOVE),true,false,false,CL_lilly);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY0_ADD), true, false, false, CL_okina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY0_REMOVE), true, false, false, CL_okina);
			break;
		case 1:
			you.Ability(SKL_OKINA_1, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY1_ADD), true, false, false, CL_okina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY1_REMOVE), true, false, false, CL_okina);
			break;
		case 2:
			you.Ability(SKL_OKINA_2, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY2_ADD), true, false, false, CL_okina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY2_REMOVE), true, false, false, CL_okina);
			break;
		case 3:
			you.Ability(SKL_OKINA_3, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY3_ADD), true, false, false, CL_okina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY3_REMOVE), true, false, false, CL_okina);
			break;
		case 4:
			you.Ability(SKL_OKINA_4, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY4_ADD), true, false, false, CL_okina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY4_REMOVE), true, false, false, CL_okina);
			break;
		case 5:
			you.Ability(SKL_OKINA_5, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY5_ADD), true, false, false, CL_okina);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_GAIN_ABLILITY5_REMOVE), true, false, false, CL_okina);
			break;
		}
		return false;
	case GT_JUNKO:
		switch (level)
		{
		case 1:
			you.Ability(SKL_JUNKO_1, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_GAIN_ABLILITY1_ADD), true, false, false, CL_junko);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_GAIN_ABLILITY1_REMOVE), true, false, false, CL_junko);
			break;
		case 2:
			you.Ability(SKL_JUNKO_2, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_GAIN_ABLILITY2_ADD), true, false, false, CL_junko);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_GAIN_ABLILITY2_REMOVE), true, false, false, CL_junko);
			break;
		case 4:
			you.Ability(SKL_JUNKO_3, true, !plus);
			if (plus)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_GAIN_ABLILITY4_ADD), true, false, false, CL_junko);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_GAIN_ABLILITY4_REMOVE), true, false, false, CL_junko);
			break;
		case 6:
			you.Ability(SKL_JUNKO_4, true, !plus);
			if (plus) {
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_GAIN_ABLILITY6_ADD), true, false, false, CL_junko);
				if (you.god_value[GT_JUNKO][0] == 0)
				{
					random_extraction<int> rand_;
					rand_.push(1);//스킬순화
					rand_.push(2);//저항순화
					rand_.push(3);//마력순화
					rand_.push(4);//파워순화
					if (you.char_type != UNIQ_START_MOKOU)
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_GAIN_ABLILITY6_REMOVE), true, false, false, CL_junko);
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
	default:
		return false;
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //적일때
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_ACCECPT), true, false, false, CL_joon_and_sion);
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
				printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_COMMON_ACCECPT, PlaceHolderHelper(LOC_SYSTEM_GOD_KANAKO)), true, false, false, CL_help);
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
				printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_COMMON_RAGE, PlaceHolderHelper(LOC_SYSTEM_GOD_KANAKO)), true, false, false, CL_small_danger);
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
				printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_COMMON_ACCECPT, PlaceHolderHelper(LOC_SYSTEM_GOD_SUWAKO)), true, false, false, CL_swako);

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
							printlog(LocalzationManager::locString(LOC_SYSTEM_REST_HP), false, false, false, CL_normal);
							you.HpUpDown(randA_1(1 + mon_->level / 2), DR_EFFECT);
						}
						break;
					case SWAKO_2_KILL_MP:
						if (randA(120) < you.piety)
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_REST_MP), false, false, false, CL_normal);
							you.MpUpDown(randA_1(1 + mon_->level / 4));
						}
						break;
					case SWAKO_2_KILL_POWER:
						if (randA(200) < you.piety)
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_RECOVER_POWER), false, false, false, CL_normal);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_LETTY_ACCECPT),true,false,false,CL_warning);
					you.PietyUpDown(5*(isSprint()?5:1));
				}
			}
		}
		return false;
	case GT_MIMA:
		if (type_ == PRT_PLAYER)
		{
			if (!mon_->isUserAlly())
			{ //적일때
				printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_COMMON_ACCECPT, PlaceHolderHelper(LOC_SYSTEM_GOD_MIMA)), false, false, false, CL_green);

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
						printlog(LocalzationManager::locString(LOC_SYSTEM_REST_MP), false, false, false, CL_normal);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_ACCECPT), true, false, false, CL_yuigi);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_LETTY_ACCECPT),true,false,false,CL_autumn);
					you.PietyUpDown(4);
				}
				else
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_ACCECPT),true,false,false,CL_autumn);
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
				printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_COMMON_ACCECPT, PlaceHolderHelper(LOC_SYSTEM_GOD_YUKARI)),true,false,false,CL_yukari);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_ACCECPT), true, false, false, CL_small_danger);
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
					mon2_->id2 = mon2_->id;
					mon2_->id = MON_ENSLAVE_GHOST;
					mon2_->name = name_infor(LOC_SYSTEM_ENSLAVE_GHOST, (monster_index)mon_->id);
					LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_YUYUKO_ENSLAVE_GHOST,true,false,false,CL_normal,
						PlaceHolderHelper(mon_->name.getName()));
					you.god_value[GT_YUYUKO][0] = mon2_->map_id;
					you.god_value[GT_YUYUKO][1] = current_level;

					//유령화되면 냉기저항1단계증가
					if(mon2_->ice_resist<=2)
						mon2_->ice_resist++;
					//독저항이 생긴다.
					mon2_->poison_resist=1;
						
					//그러나 레벨은 내려간다.
					mon2_->LevelUpdown(-2);

					AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_YUYUKO_ENSLAVE_GHOST,PlaceHolderHelper(mon_->name.getName())),CL_yuyuko);
				}
			}
		}
		else if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if(!mon_->isUserAlly())
			{ //적일때
				printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_COMMON_ACCECPT, PlaceHolderHelper(LOC_SYSTEM_GOD_YUYUKO)),true,false,false,CL_yuyuko);
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
				printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_COMMON_ACCECPT, PlaceHolderHelper(LOC_SYSTEM_GOD_OKINA)), true, false, false, CL_okina);
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
					printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_COMMON_ACCECPT, PlaceHolderHelper(LOC_SYSTEM_GOD_JUNKO)), true, false, false, CL_junko);
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
	default:
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
	default:
		return false;
	case GT_JOON_AND_SION:
	{
		if (you.god_value[GT_JOON_AND_SION][0] == 2 && !you.GetPunish(GT_JOON_AND_SION) && pietyLevel(you.piety) >= 2)
		{
			int hp_ = rand_int(you.GetMaxHp() * 6 / 100, you.GetMaxHp() * 10 / 100) + 1;
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_HEAL_FROM_P) + " ", false, false, false, CL_normal);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_HEALED2),false,false,false,CL_normal);
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
	default:
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_COMMON_PROTECT),false,false,false,CL_swako);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_TURN_TELEPORT_SAME),false,false,false,CL_normal);
					else
						printlog(LocalzationManager::locString(LOC_SYSTEM_TURN_TELEPORT),false,false,false,CL_normal);
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
	default:
		return false;
	case GT_YUUGI:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_RAGE_MAGIC),true,false,false,CL_small_danger);
		you.PietyUpDown(-5);
		return false;
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
		if(spell_ == SPL_BLINK || spell_ == SPL_TELEPORT_SELF)
		{			
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_MAGIC_RAGE),true,false,false,CL_small_danger);
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
	default:
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
	default:
		return false;
	case GT_MIKO:
	{
		if (new_dungeon_)
		{
			you.PietyUpDown(-200);
			if (down_ && env[current_level].popular == 1) {
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_ENTER_NEW_DUNGEON), true, false, false, CL_miko);
				you.PietyUpDown(60, true);
			}
			else {
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_ENTER_OUT_DUNGEON), true, false, false, CL_miko);

			}
		}
		else if (down_)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_DOWN_FLOOR), true, false, false, CL_miko);
			you.PietyUpDown(-10);
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_UP_FLOOR), true, false, false, CL_miko);
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
	default:
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
	default:
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
	default:
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
	default:
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABANDON), true,false,false,CL_danger);
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
	default:
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
				LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_PRAY2,true,false,false,CL_warning,
					 PlaceHolderHelper(GetGodString(you.god)));
			}
			if (!God_PraySpeak()) {
				LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_PRAY1,true,false,false,CL_warning,
					 PlaceHolderHelper(GetGodString(you.god)));
			}
		}
	}
	else
	{
		enterlog();
		dungeon_tile_type type = env[current_level].dgtile[you.position.x][you.position.y].tile;		
		if(type >= DG_TEMPLE_FIRST && type <= DG_TEMPLE_LAST)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_PRAY_TEMPLE),true,false,false,CL_warning);
			MoreWait();


			if(type != DG_TEMPLE_SATORI && you.GetPunish((god_type)(type-DG_TEMPLE_FIRST)))
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_NOT_YET_FORGIVE,true,false,false,CL_warning,
					 PlaceHolderHelper(GetGodString((god_type)(type-DG_TEMPLE_FIRST))));

			}
			else
			{
				WaitForSingleObject(mutx, INFINITE);
				deletesub();
				SetDisplayTexture(&img_god_background[(type - DG_TEMPLE_FIRST)]);
				GodInfor((god_type)(type-DG_TEMPLE_FIRST));
				printsub("",true,CL_normal);
				printsub("",true,CL_normal);
				printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_PRAY_TEMPLE_YN),true,CL_help);
				changedisplay(DT_SUB_TEXT);
				ReleaseMutex(mutx);
				bool ok_= true;
				while(ok_)
				{			
					InputedKey inputedKey;
					int select = waitkeyinput(inputedKey);
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
						steam_mg.achievement(ACHIEVEMENT_DUNGEON_OF_FAITH);
						MoreWait();
						ok_ = false;
						break;
					case -1:
						if(inputedKey.isRightClick()) {
							//ESC PASSTHORUGH
						}
						else {
							break;
						}
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_PRAY_AHTEISM),true,false,false,CL_warning);
		}
	}
	you.time_delay += you.GetNormalDelay();
	you.TurnEnd();
	you.SetPrevAction('p');
}



void GodInfor(god_type god)
{
	printsub("                                                    " + LocalzationManager::locString(LOC_SYSTEM_FAITH),true,CL_normal);
	switch(god)
	{
	case GT_SUWAKO:
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SUWAKO_TITLE), true, CL_swako);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_SUWAKO_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_MIMA: {
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_TITLE), true, CL_green);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_YUYUKO: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_TITLE), true, CL_yuyuko);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_JOON_AND_SION: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TITLE), true, CL_joon_and_sion);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_SHINKI: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_TITLE), true, CL_white_puple);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_MINORIKO:
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_TITLE), true, CL_warning);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_SHIZUHA: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_TITLE), true, CL_small_danger);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_EIRIN: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_TITLE), true, CL_small_danger);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_KANAKO: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_TITLE), true, CL_help);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_YUKARI:
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_TITLE), true, CL_yukari);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_HINA: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_TITLE), true, CL_hina);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_SATORI: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_TITLE), true, CL_danger);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_YUUGI:
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_TITLE), true, CL_yuigi);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_TENSI: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TITLE), true, CL_tensi);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_BYAKUREN: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_TITLE), true, CL_white_blue);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_SEIJA: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_TITLE), true, CL_seija);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_LILLY: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_TITLE), true, CL_lilly);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_MIKO: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_TITLE), true, CL_miko);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_OKINA: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_TITLE), true, CL_okina);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	case GT_JUNKO: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_TITLE), true, CL_junko);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	default: 
	{
		printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_BUG_TITLE), true, CL_danger);
		printsub("", true, CL_normal);
		std::string desc = LocalzationManager::locString(LOC_SYSTEM_GOD_BUG_DESCRIPTION);
		size_t pos = 0;
		std::string token;
		std::string delimiter = "\n";
		
		while ((pos = desc.find(delimiter)) != std::string::npos) {
			token = desc.substr(0, pos);
			printsub(token, true, CL_normal);
			desc.erase(0, pos + delimiter.length());
		}
		printsub(desc, true, CL_normal);
		printsub("", true, CL_normal);
		break;
	}
	}
}


void God_show()
{
	const int cost_pos = 90;
	ostringstream ss;
	if(you.god == GT_NONE)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_AHTEISM),true,false,false,CL_normal);
		return;
	}
	deletesub();
	WaitForSingleObject(mutx, INFINITE);
	SetDisplayTexture(&img_god_background[you.god]);
	GodInfor(you.god);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	ss << LocalzationManager::locString(LOC_SYSTEM_GOD_ABLILITES) + ":";
	string cost = "(" + LocalzationManager::locString(LOC_SYSTEM_GOD_ABLILITES) + ")";
	ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;

	printsub(ss.str(),true,CL_normal);
	printsub("",true,CL_normal);
	int level_ = pietyLevel(you.piety);
	switch(you.god)
	{
	case GT_ERROR:
	default:
		break;
	case GT_NONE:
		break;
	case GT_JOON_AND_SION:
		if (level_ >= 0)
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(), true, CL_joon_and_sion);
			if (you.god_value[GT_JOON_AND_SION][0] != 1) {
				printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY1_1), true, CL_joon_and_sion);
			}
			else {
				printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY1_2), true, CL_joon);
			}
			if (you.god_value[GT_JOON_AND_SION][0] != 2) {
				printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY1_3), true, CL_joon_and_sion);
			}
			else {
				printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY1_4), true, CL_sion);
			}
			printsub("", true, CL_normal);
		}
		if (level_ >= 1 && !you.GetPunish(GT_JOON_AND_SION))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ACTIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(), true, you.god_value[GT_JOON_AND_SION][0] == 0?CL_joon_and_sion:CL_bad);
			printsub("", true, CL_normal);
		}
		if (level_ >= 2 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] == 1) {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY3_1);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_joon);
				printsub("", true, CL_normal);
			}
			else if (you.god_value[GT_JOON_AND_SION][0] == 2) {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY3_2);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_sion);
				printsub("", true, CL_normal);
			}
			else {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY3);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		if (level_ >= 4 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] == 1) {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY4_1);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_joon);
				printsub("", true, CL_normal);
			}
			else if (you.god_value[GT_JOON_AND_SION][0] == 2) {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY4_2);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_sion);
				printsub("", true, CL_normal);
			}
			else {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY4);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		if (level_ >= 5 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] == 1) {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY5_1);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON_POSSESSION);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_joon);
				printsub("", true, CL_normal);
			}
			else if (you.god_value[GT_JOON_AND_SION][0] == 2) {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY5_2);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON_POSSESSION);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_sion);
				printsub("", true, CL_normal);
			}
			else {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY5);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON_POSSESSION);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		if (level_ >= 6 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] != 0) {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY6_1);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_joon_and_sion);
				printsub("", true, CL_normal);
			}
			else {
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JOON_AND_SION_ABLILITY6);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		break;
	case GT_BYAKUREN:
		if(level_ >= 1 && !you.GetPunish(GT_BYAKUREN))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_BYAKUREN_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_BYAKUREN))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_BYAKUREN_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_BYAKUREN))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_BYAKUREN_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_BYAKUREN))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_BYAKUREN_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_BYAKUREN))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_BYAKUREN_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		break;
	case GT_KANAKO:
		if(level_ >= 1 && !you.GetPunish(GT_KANAKO))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_KANAKO_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_KANAKO))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_KANAKO_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_KANAKO))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_KANAKO_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_help);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SUWAKO:
		if(level_ >= 1 && !you.GetPunish(GT_SUWAKO))
		{
			ss.str("");
			ss.clear();
			ss << GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][0], SWAKO_SIMPLE_INFOR);
			cost = GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][0], SWAKO_COST);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SUWAKO))
		{
			ss.str("");
			ss.clear();
			ss << GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][1], SWAKO_SIMPLE_INFOR);
			cost = GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][1], SWAKO_COST);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SUWAKO))
		{
			ss.str("");
			ss.clear();
			ss << GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][2], SWAKO_SIMPLE_INFOR);
			cost = GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][2], SWAKO_COST);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SUWAKO))
		{
			ss.str("");
			ss.clear();
			ss << GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][3], SWAKO_SIMPLE_INFOR);
			cost = GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][3], SWAKO_COST);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SUWAKO))
		{
			ss.str("");
			ss.clear();
			ss << GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][4], SWAKO_SIMPLE_INFOR);
			cost = GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][4], SWAKO_COST);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_help);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MINORIKO:
		if(level_ >= 0)
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MINORIKO_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_MINORIKO))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MINORIKO_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_MINORIKO))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MINORIKO_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_MINORIKO))
		{ //이때부터 고구마 선물을 해준다.
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MINORIKO_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_MINORIKO))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MINORIKO_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_FOOD_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_MINORIKO))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MINORIKO_ABLILITY6);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_warning);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MIMA:
		if(level_ >= 0 && !you.GetPunish(GT_MIMA))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIMA_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_MIMA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIMA_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_MIMA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIMA_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_MIMA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIMA_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_green);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SHINKI:
		if(level_ >= 1 && !you.GetPunish(GT_SHINKI))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHINKI_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SHINKI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHINKI_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SHINKI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHINKI_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SHINKI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHINKI_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SHINKI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHINKI_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUUGI:
		if(level_ >= 0 && !you.GetPunish(GT_YUUGI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUUGI_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_YUUGI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUUGI_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_POTION_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUUGI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUUGI_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUUGI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUUGI_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUUGI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUUGI_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_YUUGI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUUGI_ABLILITY6);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUUGI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUUGI_ABLILITY7);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SHIZUHA:
		if(level_ >= 0 && !you.GetPunish(GT_SHIZUHA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHIZUHA_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_SHIZUHA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHIZUHA_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_autumn);
			printsub("",true,CL_normal);
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHIZUHA_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SHIZUHA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHIZUHA_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SHIZUHA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHIZUHA_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SHIZUHA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHIZUHA_ABLILITY6);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 6 && you.god_value[GT_SHIZUHA][0]==0 && !you.GetPunish(GT_SHIZUHA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SHIZUHA_ABLILITY7);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_autumn);
			printsub("",true,CL_normal);
		}
		break;
	case GT_HINA:
		if(level_ >= 0)
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_HINA_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_HINA))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_HINA_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_HINA))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_HINA_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_CURSE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_HINA))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_HINA_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_CURSE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_HINA))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_HINA_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_CURSE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_HINA))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_HINA_ABLILITY6);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 6 && you.god_value[GT_HINA][0]==0 && !you.GetPunish(GT_HINA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_HINA_ABLILITY7);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_hina);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUKARI:
		if(level_ >= 0 && !you.GetPunish(GT_YUKARI))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUKARI_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_YUKARI))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUKARI_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUKARI))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUKARI_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUKARI))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUKARI_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_YUKARI))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUKARI_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUKARI))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUKARI_ABLILITY6);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yukari);
			printsub("",true,CL_normal);
		}
		break;
	case GT_EIRIN:
		if(!you.GetPunish(GT_EIRIN))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_small_danger);
			printsub("",true,CL_normal);
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_POTION);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_small_danger);
			printsub("",true,CL_normal);
			if(level_ >= 1)
			{
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY3);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(),true,CL_small_danger);
				printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY3_1),true,CL_small_danger);
				if(level_ >= 2)
					printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY3_2),true,CL_small_danger);
				if(level_ >= 3)
					printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY3_3),true,CL_small_danger);
				if(level_ >= 4)
					printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY3_4),true,CL_small_danger);
				if(level_ >= 5)
					printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY3_5),true,CL_small_danger);
				entersub();
				printsub("",true,CL_normal);
			}
		}
		if(level_ >= 2 && !you.GetPunish(GT_EIRIN))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_POTION);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_EIRIN))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_EIRIN))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_EIRIN_ABLILITY6);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_MP_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUYUKO:
		if(level_ >= 1 && !you.GetPunish(GT_YUYUKO))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUYUKO_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUYUKO))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUYUKO_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_MP);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUYUKO))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUYUKO_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUYUKO))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_YUYUKO_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SATORI:
		if(level_ >= 0 && !you.GetPunish(GT_SATORI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SATORI_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_SATORI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SATORI_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SATORI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SATORI_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SATORI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SATORI_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SATORI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SATORI_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_TIME_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SATORI))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SATORI_ABLILITY6);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_danger);
			printsub("",true,CL_normal); 
		}
		break;
	case GT_TENSI:
		if(level_ >= 0 && !you.GetPunish(GT_TENSI))
		{ 
			printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_TENSI_ABLILITY),true,CL_tensi);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SEIJA:
		if(level_ >= 1 && !you.GetPunish(GT_SEIJA))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SEIJA_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_seija);
			printsub("",true,CL_normal);
		}
		if (level_ >= 2 && !you.GetPunish(GT_SEIJA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SEIJA_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(), true, CL_seija);
			printsub("", true, CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SEIJA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SEIJA_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_seija);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SEIJA))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SEIJA_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_seija);
			printsub("",true,CL_normal);
		}
		break;
	case GT_LILLY:
		if(level_ >= 1 )
		{ 
			printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_UI_LILLY1),true,CL_lilly);
			printsub("",true,CL_normal);
			for(int i = 0; i < min(5,level_); i++)
			{
				printsub(LocalzationManager::formatString(LOC_SYSTEM_GOD_UI_LILLY1_ALLY,PlaceHolderHelper(std::to_string(i+1))) + " ",false,CL_warning);
				if(you.god_value[GT_LILLY][i])
				{
					int lenght_ =0;
					if(mondata[you.lilly_allys[i].id].flag & M_FLAG_UNIQUE)
					{
						printsub(mondata[you.lilly_allys[i].id].name.getName() + " ",false,CL_normal);
					}
					else
					{
						ostringstream oss;
						oss << LocalzationManager::locString(fairy_name[you.lilly_allys[i].name]) << "(" << mondata[you.lilly_allys[i].id].name.getName() << ") ";
						printsub(oss.str(),false,CL_normal);
					}
					for(;lenght_<25;lenght_++)
						printsub(" ",false,CL_normal);
					{
						
						ostringstream oss;
						oss << LocalzationManager::locString(LOC_SYSTEM_GOD_UI_LILLY1_LEVEL) << " ";
						lenght_ += printsub(oss.str(),false,CL_warning);
						oss.clear();
						oss.str("");
						oss << std::setw(2) << std::setfill(' ') << you.lilly_allys[i].level;
						lenght_ += printsub(oss.str(),false,CL_normal);

					}

					for(;lenght_<40;lenght_++)
						printsub(" ",false,CL_normal);
					printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_UI_LILLY1_STATE) + " ",false,CL_warning);
					printsub(LocalzationManager::locString(you.god_value[GT_LILLY][i]==1?LOC_SYSTEM_GOD_UI_LILLY1_LIVE:LOC_SYSTEM_GOD_UI_LILLY1_REVIVE),true,you.god_value[GT_LILLY][i]==1?CL_white_blue:CL_danger);
				}
				else
				{
					printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_UI_LILLY1_EMPTY),true,CL_bad);
				}
			}
			printsub("",true,CL_normal);
			printsub("",true,CL_normal);
		}
		if(level_ >= 0 && !you.GetPunish(GT_LILLY))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_LILLY_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_LILLY))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_LILLY_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_NONE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_LILLY))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_LILLY_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_LILLY))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_LILLY_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_MP);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_LILLY))
		{ 
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_LILLY_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_MP);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(),true,CL_lilly);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MIKO:
		if (level_ >= 0 && !you.GetPunish(GT_MIKO))
		{
			printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_TIP1), true, CL_normal);
			printsub("    " + LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_TIP1_1), true, CL_miko);
			printsub("    " + LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_TIP1_2), true, CL_miko);
			printsub("    " + LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_TIP1_3), true, CL_miko);
			printsub("", true, CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_TIP2), true, CL_normal);
			printsub("    " + LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_TIP2_1), true, CL_miko);
			printsub("    " + LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_TIP2_2), true, CL_miko);
			printsub("    " + LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_TIP2_3), true, CL_miko);
			printsub("", true, CL_normal);
			{
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_ABLILITY1);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON_FLOOR);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, CL_miko);
			}
			printsub("", true, CL_normal);
			{
				std::ostringstream popcost;
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_ABLILITY2);
				popcost << std::setw(3) << (getMikoPiety(0) / 2);
				cost = LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(popcost.str()) );
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, you.piety >= getMikoPiety(0) ? CL_miko : CL_bad);
			}
			printsub("", true, CL_normal);
			{
				std::ostringstream popcost;
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_ABLILITY3);
				popcost << std::setw(3) << (getMikoPiety(1) / 2);
				cost = LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(popcost.str()) );
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, you.piety >= getMikoPiety(1) ? CL_miko : CL_bad);
			}
			printsub("", true, CL_normal);
			{
				std::ostringstream popcost;
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_ABLILITY4);
				popcost << std::setw(3) << (getMikoPiety(2) / 2);
				cost = LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(popcost.str()) );
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, you.piety >= getMikoPiety(2) ? CL_miko : CL_bad);
			}
			printsub("", true, CL_normal);
			{
				std::ostringstream popcost;
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_ABLILITY5);
				popcost << std::setw(3) << (getMikoPiety(3) / 2);
				cost = LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(popcost.str()) );
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, you.piety >= getMikoPiety(3) ? CL_miko : CL_bad);
			}
			printsub("", true, CL_normal);
			{
				std::ostringstream popcost;
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MIKO_ABLILITY6);
				popcost << std::setw(3) << (getMikoPiety(4) / 2);
				cost = LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(popcost.str()) );
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, you.piety >= getMikoPiety(4) ? CL_miko : CL_bad);
			}
			printsub("", true, CL_normal);
		}
		break;
	case GT_OKINA:
		if (level_ >= 0 && !you.GetPunish(GT_OKINA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_OKINA_ABLILITY1);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(), true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 1 && !you.GetPunish(GT_OKINA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_OKINA_ABLILITY2);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_MP);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(), true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 2 && !you.GetPunish(GT_OKINA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_OKINA_ABLILITY3);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(), true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 3 && !you.GetPunish(GT_OKINA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_OKINA_ABLILITY4);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(), true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 4 && !you.GetPunish(GT_OKINA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_OKINA_ABLILITY5);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(), true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 5 && !you.GetPunish(GT_OKINA))
		{
			ss.str("");
			ss.clear();
			ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_OKINA_ABLILITY6);
			cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY);
			ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
			printsub(ss.str(), true, CL_okina);
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
					ss.str("");
					ss.clear();
					ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_PURITY1);
					cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
					ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
					printsub(ss.str(), true, CL_junko);
					if (you.god_value[GT_JUNKO][3] == 7)
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_PURITY2), true, (you.s_pure_turn && you.s_pure >= 10) ? CL_junko : CL_bad);
					else
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_PURITY3), true, (you.s_pure_turn && you.s_pure >= 10) ? CL_junko : CL_bad);
					printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_PURITY3), true, CL_junko);
					printsub("", true, CL_normal);
				}
				else
				{
					ss.str("");
					ss.clear();
					ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY1);
					cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
					ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
					printsub(ss.str(), true, CL_junko);
					if (level_ >= 0 && !you.GetPunish(GT_JUNKO))
					{
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY1_1), true, (you.s_pure_turn && you.s_pure >= 10) ? CL_junko : CL_bad);
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY1_2), true, (you.s_pure_turn && you.s_pure >= 20) ? CL_junko : CL_bad);
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY1_3), true, (you.s_pure_turn && you.s_pure >= 30) ? CL_junko : CL_bad);
						printsub("", true, CL_normal);
					}
				}
			}
			if (level_ >= 1 && !you.GetPunish(GT_JUNKO))
			{
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY2);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_MP);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, already_pure? CL_bad : CL_junko);
				printsub("", true, CL_normal);
			}
			if (level_ >= 2 && !you.GetPunish(GT_JUNKO))
			{
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY3);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, already_pure ? CL_bad : CL_junko);
				printsub("", true, CL_normal);
			}
			if (level_ >= 4 && !you.GetPunish(GT_JUNKO))
			{
				ss.str("");
				ss.clear();
				ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY4);
				cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
				ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
				printsub(ss.str(), true, already_pure ? CL_bad : CL_junko);
				printsub("", true, CL_normal);
			}
			if (level_ >= 5 && !you.GetPunish(GT_JUNKO))
			{
				if (already_pure)
				{
					printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5_1), true, CL_junko);
					switch (you.god_value[GT_JUNKO][3])
					{
					case 1:
						printsub(LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5_2, PlaceHolderHelper(skill_string((skill_type)you.pure_skill))), true, CL_junko);
						break;
					case 2:
					{
						printsub(LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5_3, PlaceHolderHelper(you.GetProperty(TPT_FIRE_IMUNE)?LOC_SYSTEM_SHORT_FIRE_RESIST:(you.GetProperty(TPT_COLD_IMUNE) ? LOC_SYSTEM_SHORT_COLD_RESIST : (you.GetProperty(TPT_ELEC_IMUNE) ? LOC_SYSTEM_SHORT_ELEC_RESIST : LOC_SYSTEM_BUG)))), true, CL_junko);
						break;
					}
					case 3:
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5_4), true, CL_junko);
						break;
					case 4:
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5_5), true, CL_junko);
						break;
					case 5:
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5_6), true, CL_junko);
						break;
					case 6:
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5_7), true, CL_junko);
						break;
					case 7:
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5_8), true, CL_junko);
						break;
					default:
						printsub(LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5_BUG), true, CL_junko);
						break;
					}
				}
				else
				{
					ss.str("");
					ss.clear();
					ss << LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_JUNKO_ABLILITY5);
					cost = LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON);
					ss << string(cost_pos - PrintCharWidth(ss.str() + cost), ' ') << cost;
					printsub(ss.str(), true, CL_junko);
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
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey, true);
		if(key_ == -1) {
			if (inputedKey.isLeftClick() || inputedKey.isRightClick()) {
				break;
			}
		} else {
			break;
		}
	}
	changedisplay(DT_GAME);
	SetDisplayTexture(NULL);

}
bool God_pray(const list<item>::iterator it)
{
	switch(you.god)
	{
	case GT_ERROR:
	default:
		break;
	case GT_NONE:
		break;
	case GT_JOON_AND_SION:
		break;
	case GT_BYAKUREN:
		break;
	case GT_KANAKO:
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
		if(it->type == ITM_POTION && iden_list.potion_list[it->value1].iden && isGoodPotion((potion_type)it->value1)>0)
		{
			int per_ = randA(100);
			int result_ = (per_<15)?PT_CONFUSE:((per_<41)?PT_POISON:((per_<67)?PT_SLOW:(per_<93)?PT_DOWN_STAT:PT_PARALYSIS));
			
			string prev_ = it->GetNameString();
			it->value1 = result_;
			string next_ = it->GetNameString();
			LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_EIRIN_PRAY_1,true,false,false,CL_small_danger,
				PlaceHolderHelper(prev_), PlaceHolderHelper(next_));
			LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_EIRIN_PRAY_2,true,false,false,CL_small_danger);

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
		printlog("***" + LocalzationManager::locString(LOC_SYSTEM_PUNISH) + "!***",true,false,false,CL_small_danger);
	}
	switch(god)
	{
	case GT_ERROR:
	default:
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_PUNISH_JOON), true, false, false, CL_white_blue);
			break;
		case 1:
			you.god_value[GT_JOON_AND_SION][0] = 2;
			you.god_value[GT_JOON_AND_SION][1] = rand_int(250, 400);
			you.HpUpDown(-you.GetMaxHp() / 2, DR_EFFECT);
			if (!you.pure_mp)
				you.MpUpDown(-you.max_mp / 2);
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_PUNISH_SION), true, false, false, CL_white_blue);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_PUNISH_MP), true,false,false,CL_white_blue);
				break;
			case 1:
				(randA(1)?you.StatUpDown(-rand_int(1,5),STAT_STR,true):you.StatUpDown(-rand_int(3,7),STAT_INT,true));
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_PUNISH_BYAKUREN), true,false,false,CL_white_blue);
				break;
			case 2:
				you.SetSlow(rand_int(80,100));
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_PUNISH_SLOW), true,false,false,CL_white_blue);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_PUNISH_STRIKE), true,false,false,CL_help);
					int damage_ = you.GetHp()*rand_int(40,80)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY,ATT_SMITE,name_infor(LOC_SYSTEM_SKL_KANAKO_1));
					you.damage(temp_att, true);


				}	
				break;
			case 1:
				{
					for(int i = randA(3)+1; i>0 ; i--)
					{
						BaseSummon(MON_ONBASIRA, rand_int(10,30), true, false, 2, NULL, you.position, SKD_OTHER, -1);
					}
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_PUNISH_ONBASIRA), true,false,false,CL_help);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_PUNISH_RECALL), true,false,false,CL_help);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_PUNISH_RECALL_FAIL), true,false,false,CL_help);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_PUNISH_CURSE), true,false,false,CL_swako);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_PUNISH_FROG), true,false,false,CL_swako);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_PUNISH_HUNGER), true,false,false,CL_warning);
				break;
			case 1:
				{
					you.HpUpDown(-max(1, you.GetHp() / 2), DR_EFFECT, NULL);
					you.SetSick(rand_int(80,120));
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_PUNISH_SICK), true,false,false,CL_warning);
					break;
				}
			case 2:
				{
					for(int i=0;i<3;i++)
						you.StatUpDown(-rand_int(1,4),randA(2)?(randA(1)?STAT_STR:STAT_DEX):STAT_INT,true);
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_PUNISH_STAT), true,false,false,CL_warning);
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
					LOCALIZATION_ENUM_KEY key_ = LOC_SYSTEM_ATT_MIMA_MAGIC;
					textures* tex_ = &img_blast[2];
					attack_type type_ = ATT_NORMAL_BLAST;
					int damage_ = 15+you.level*5;
					switch(randA(5))
					{
					case 0:
						{
						key_ = LOC_SYSTEM_ATT_MIMA_FIRE_MAGIC;
						tex_ = &img_blast[0];
						type_ = ATT_FIRE_BLAST;
						break;
						}
					case 1:
						{
						key_ = LOC_SYSTEM_ATT_MIMA_EARTH_MAGIC;
						tex_ = &img_blast[1];
						type_ = ATT_NORMAL_BLAST;
						damage_ = damage_*4/5;
						break;
						}
					case 2:
						{
						key_ = LOC_SYSTEM_ATT_MIMA_ELEC_MAGIC;
						tex_ = &img_blast[2];
						type_ = ATT_ELEC_BLAST;
						break;
						}
					case 3:
						{
						key_ = LOC_SYSTEM_ATT_MIMA_POISION_MAGIC;
						tex_ = &img_blast[3];
						type_ = ATT_POISON_BLAST;
						damage_ = damage_*4/5;
						break;
						}
					case 4:
						{
						key_ = LOC_SYSTEM_ATT_MIMA_ICE_MAGIC;
						tex_ = &img_blast[4];
						type_ = ATT_COLD_BLAST;
						break;
						}
					case 5:
						{
						key_ = LOC_SYSTEM_ATT_MIMA_CONJURE_MAGIC;
						tex_ = &img_blast[5];
						type_ = ATT_AC_REDUCE_BLAST;
						damage_ = damage_*3/5;
						break;
						}
					}
					
					LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_MIMA_PUNISH_MAGIC,true,false,false,CL_green,
						PlaceHolderHelper(key_));
					attack_infor temp_att(randC(3,damage_/3),damage_,99,NULL,PRT_ENEMY,type_,name_infor(key_));
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_PUNISH_SUMMON),true,false,false,CL_white_puple);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_PUNISH_DRINK),true,false,false,CL_yuigi);	
				you.SetConfuse(rand_int(9,30));
				you.SetDrunken(rand_int(50,100));
				break;
			case 1:
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_PUNISH_THROW),true,false,false,CL_yuigi);
					you.Blink(40);
					int damage_ = you.GetHp()*rand_int(30,60)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY, ATT_SMASH,name_infor(LOC_SYSTEM_ATT_GIANTSWING));
					you.damage(temp_att, true);
				}
				break;
			case 2:
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_PUNISH_ONI),true,false,false,CL_yuigi);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_PUNISH_CONFUSE),true,false,false,CL_autumn);	
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
	
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_PUNISH_BACKSTAB),true,false,false,CL_autumn);
					int damage_ = you.GetHp()*rand_int(30,60)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY,ATT_SMITE,name_infor(LOC_SYSTEM_ATT_BACKSTAB));
					you.damage(temp_att, true);
					you.SetBuff(BUFFSTAT_RF,BUFF_AUTUMN_RF,-1,1);
				}
				break;
			case 2:
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_PUNISH_NOISE_AND_DEBUFF),true,false,false,CL_autumn);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_PUNISH_CURSE_SMOKE),true,false,false,CL_hina);
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
					LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_HINA_CURSE_EQUIPMENT1,false,false,false,CL_hina);

					for(int i = 0; i<dq.size() ; i++)
					{
						if(you.equipment[dq[i]])
						{
							string before_name = you.equipment[dq[i]]->GetName(); //저주받기전 이름
							if(you.equipment[dq[i]]->Curse(true,(equip_type)dq[i]))
							{
								enterlog();
								LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_HINA_CURSE_EQUIPMENT2,true,false,false,CL_small_danger,
									you.equipment[dq[i]]->GetNameString());
								curse_ = true;
								break;
							}
						}
					}
					if(!curse_)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_BUT_NOTHING_HAPPEND), true,false,false,CL_hina);

					}
				}
				break;
			case 2:
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_PUNISH_SPIN),true,false,false,CL_hina);	
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_PUNISH_TELEPORT),true,false,false,CL_yukari);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_PUNISH_RECALL),true,false,false,CL_yukari);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_PUNISH_STASIS),true,false,false,CL_yukari);
					}
				}
				break;
			case 2:
				{

					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_PUNISH_EYES),true,false,false,CL_yukari);
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
					LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_EIRIN_PUNISH_POTION,true,false,false,CL_small_danger,
						 PlaceHolderHelper(potion_iden_string[p_]));
					drinkpotion(p_, false);
				}
				break;
			case 1:
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_PUNISH_EXPERIMENT),true,false,false,CL_small_danger);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_PUNISH_GHOST),true,false,false,CL_yuyuko);
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
				
			LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_SEIJA_PUNISH,true,false,false,CL_seija,
				PlaceHolderHelper(GetGodString(god_)));
			
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_PUNISH_WEAK),true,false,false,CL_lilly);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_PUNISH_SUMMON),true,false,false,CL_lilly);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_PUNISH_HP) + " ", false, false, false, CL_miko);
			you.SetBuff(BUFFSTAT_HP, BUFF_DUPLE, -(you.GetMaxHp()/2), time_);
		}
		break;
		case 1:
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_PUNISH_SLOW) + " ", false, false, false, CL_miko);
			you.SetSlow(time_);
		}
		break;
		case 2:
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_PUNISH_RESIST) + " ", false, false, false, CL_miko);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_PUNISH_BACKDANCER),true, false, false, CL_okina);

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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_PUNISH_DRAIN),true, false, false, CL_okina);
						break;
					}
				}
				break;
			case 1:
				{
					you.HpUpDown(-you.GetMaxHp()/2, DR_EFFECT);
					if (!you.pure_mp)
						you.MpUpDown(-you.max_mp/2);
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_PUNISH_DRAIN),true, false, false, CL_okina);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PUNISH_WEAK) + " ",false, false, false, CL_junko);
				you.SetForceStrong(false, time_, true);
			}
			break;
			case 1:
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PUNISH_SLOW) + " ",false, false, false, CL_junko);
				you.SetSlow(time_);
			}
			break;
			case 2:
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PUNISH_STAT) + " ", false, false, false, CL_junko);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GAIN_AC) + " ", false, false, false, CL_white_blue);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_WELCOME), true, false, false, CL_normal);
		return;
	}
	switch (you.god)
	{
	case GT_JOON_AND_SION:
		switch (randA(1))
		{
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_WELCOME1), true, false, false, CL_joon);
			break;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_WELCOME2), true, false, false, CL_sion);
			break;
		}
		break;
	case GT_BYAKUREN:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_WELCOME), true, false, false, CL_white_blue);
		break;
	case GT_KANAKO:
		if(you.char_type == UNIQ_START_SANAE) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_WELCOME_SANAE), true, false, false, CL_help);
		}
		else {
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_WELCOME), true, false, false, CL_help);
		}
		break;
	case GT_SUWAKO:
		if(you.char_type == UNIQ_START_SANAE) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_WELCOME_SANAE), true, false, false, CL_swako);
		}
		else {
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_WELCOME), true, false, false, CL_swako);
		}
		break;
	case GT_MINORIKO:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_WELCOME), true, false, false, CL_warning);
		break;
	case GT_MIMA:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_WELCOME), true, false, false, CL_green);
		break;
	case GT_SHINKI:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_WELCOME), true, false, false, CL_white_puple);
		break;
	case GT_YUUGI:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_WELCOME), true, false, false, CL_yuigi);
		break;
	case GT_SHIZUHA:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_WELCOME), true, false, false, CL_autumn);
		break;
	case GT_HINA:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_WELCOME), true, false, false, CL_hina);
		break;
	case GT_YUKARI:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_WELCOME), true, false, false, CL_yukari);
		break;
	case GT_EIRIN:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_WELCOME), true, false, false, CL_small_danger);
		break;
	case GT_YUYUKO:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_WELCOME), true, false, false, CL_yuyuko);
		break;
	case GT_SATORI:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_WELCOME), true, false, false, CL_danger);
		break;
	case GT_TENSI:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_WELCOME), true, false, false, CL_tensi);
		break;
	case GT_SEIJA:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_WELCOME), true, false, false, CL_seija);
		break;
	case GT_LILLY:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_WELCOME), true, false, false, CL_lilly);
		break;
	case GT_MIKO:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_WELCOME), true, false, false, CL_miko);
		break;
	case GT_OKINA:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_WELCOME), true, false, false, CL_okina);
		break;
	case GT_JUNKO:
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_WELCOME), true, false, false, CL_junko);
		break;
	case GT_ERROR:
	case GT_NONE:
	default:
		printlog(LocalzationManager::locString(LOC_SYSTEM_WELCOME), true, false, false, CL_normal);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_TALK1), true, false, false, CL_white_blue);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_TALK2), true, false, false, CL_white_blue);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_TALK3), true, false, false, CL_white_blue);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_TALK4), true, false, false, CL_white_blue);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_TALK5), true, false, false, CL_white_blue);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_TALK6), true, false, false, CL_white_blue);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BYAKUREN_TALK7), true, false, false, CL_white_blue);
			return true;
		}
	case GT_ERROR:
	case GT_NONE:
	default:
		return false; 
	case GT_JOON_AND_SION:
		switch (level_)
		{
		default:
		case 0:
			if (randA(1))
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK1), true, false, false, CL_joon);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK2), true, false, false, CL_sion);
			return true;
		case 1:
			if (randA(1))
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK3), true, false, false, CL_joon);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK4), true, false, false, CL_sion);
			return true;
		case 2:
			if (randA(1))
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK5), true, false, false, CL_joon);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK6), true, false, false, CL_sion);
			return true;
		case 3:
			if (randA(1))
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK7), true, false, false, CL_joon);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK8), true, false, false, CL_sion);
			return true;
		case 4:
			if (randA(1))
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK9), true, false, false, CL_joon);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK10), true, false, false, CL_sion);
			return true;
		case 5:
			if (randA(1))
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK11), true, false, false, CL_joon);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK12), true, false, false, CL_sion);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_TALK13), false, false, false, CL_joon_and_sion);
			return true;
		}
	case GT_KANAKO:
		if (you.char_type == UNIQ_START_SANAE)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_TALK1), true, false, false, CL_help);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_TALK2), true, false, false, CL_help);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_TALK3), true, false, false, CL_help);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_TALK4), true, false, false, CL_help);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_TALK5), true, false, false, CL_help);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_TALK6), true, false, false, CL_help);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_TALK7), true, false, false, CL_help);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KANAKO_TALK8), true, false, false, CL_help);
			return true;
		}
	case GT_SUWAKO:
		if (you.char_type == UNIQ_START_SANAE)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SUWAKO_TALK1), true, false, false, CL_swako);
			return true;
		}
		switch (randA(4))
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SUWAKO_TALK2), true, false, false, CL_swako);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SUWAKO_TALK3), true, false, false, CL_swako);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SUWAKO_TALK4), true, false, false, CL_swako);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SUWAKO_TALK5), true, false, false, CL_swako);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SUWAKO_TALK6), true, false, false, CL_swako);
			return true;
		}
	case GT_MINORIKO:
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_TALK1), true, false, false, CL_warning);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_TALK2), true, false, false, CL_warning);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_TALK3), true, false, false, CL_warning);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_TALK4), true, false, false, CL_warning);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_TALK5), true, false, false, CL_warning);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_TALK6), true, false, false, CL_warning);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_TALK7), true, false, false, CL_warning);
			return true;
		}
	case GT_MIMA:
		if (you.char_type == UNIQ_START_MARISA)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_TALK1), true, false, false, CL_green);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_TALK2), true, false, false, CL_green);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_TALK3), true, false, false, CL_green);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_TALK4), true, false, false, CL_green);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_TALK5), true, false, false, CL_green);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_TALK6), true, false, false, CL_green);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_TALK7), true, false, false, CL_green);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_TALK8), true, false, false, CL_green);
			return true;
		}
	case GT_SHINKI:
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHINKI_WELCOME), true, false, false, CL_warning);
			return true;
		}
	case GT_YUUGI:
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_TALK1), true, false, false, CL_yuigi);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_TALK2), true, false, false, CL_yuigi);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_TALK3), true, false, false, CL_yuigi);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_TALK4), true, false, false, CL_yuigi);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_TALK5), true, false, false, CL_yuigi);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_TALK6), true, false, false, CL_yuigi);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_TALK7), true, false, false, CL_yuigi);
			return true;
		}
	case GT_SHIZUHA:
		switch (level_)
		{
		default:
		case 0:
		case 1:
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_TALK1), true, false, false, CL_warning);
			return true;
		case 3:
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_TALK2), true, false, false, CL_warning);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_TALK3), true, false, false, CL_autumn);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_TALK4), true, false, false, CL_autumn);
			return true;
		}
	case GT_HINA:
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_TALK1), true, false, false, CL_hina);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_TALK2), true, false, false, CL_hina);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_TALK3), true, false, false, CL_hina);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_TALK4), true, false, false, CL_hina);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_TALK5), true, false, false, CL_hina);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_TALK6), true, false, false, CL_hina);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_TALK7), true, false, false, CL_hina);
			return true;
		}
	case GT_YUKARI:
		if (you.char_type == UNIQ_START_REIMU)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_TALK1), true, false, false, CL_yukari);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_TALK2), true, false, false, CL_yukari);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_TALK3), true, false, false, CL_yukari);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_TALK4), true, false, false, CL_yukari);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_TALK5), true, false, false, CL_yukari);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_TALK6), true, false, false, CL_yukari);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_TALK7), true, false, false, CL_yukari);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_TALK8), true, false, false, CL_yukari);
			return true;
		}
	case GT_EIRIN:
		if (you.char_type == UNIQ_START_MOKOU)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_TALK1), true, false, false, CL_small_danger);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_TALK2), true, false, false, CL_small_danger);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_TALK3), true, false, false, CL_small_danger);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_TALK4), true, false, false, CL_small_danger);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_TALK5), true, false, false, CL_small_danger);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_TALK6), true, false, false, CL_small_danger);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_TALK7), true, false, false, CL_small_danger);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_TALK8), true, false, false, CL_small_danger);
			return true;
		}
	case GT_YUYUKO:
		if (you.char_type == UNIQ_START_MOKOU)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_TALK1), true, false, false, CL_yuyuko);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_TALK2), true, false, false, CL_yuyuko);
			return true;
		case 2:
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_TALK3), true, false, false, CL_yuyuko);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_TALK4), true, false, false, CL_yuyuko);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_TALK5), true, false, false, CL_yuyuko);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_TALK6), true, false, false, CL_yuyuko);
			return true;
		}
	case GT_SATORI:
		switch (level_)
		{
		default:
		case 0:
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_TALK1), true, false, false, CL_warning);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_TALK2), true, false, false, CL_warning);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_TALK3), true, false, false, CL_danger);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_TALK4), true, false, false, CL_warning);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_TALK5), true, false, false, CL_danger);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_TALK6), true, false, false, CL_danger);
			return true;
		}
	case GT_TENSI:
		switch (randA(9))
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK1), true, false, false, CL_tensi);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK2), true, false, false, CL_tensi);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK3), true, false, false, CL_tensi);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK4), true, false, false, CL_tensi);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK5), true, false, false, CL_tensi);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK6), true, false, false, CL_warning);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK7), true, false, false, CL_warning);
			return true;
		case 7:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK8), true, false, false, CL_warning);
			return true;
		case 8:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK9), true, false, false, CL_warning);
			return true;
		case 9:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_TENSI_TALK10), true, false, false, CL_warning);
			return true;
		}
	case GT_SEIJA:
		switch (level_)
		{
		default:
		case 0:
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_TALK1), true, false, false, CL_warning);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_TALK2), true, false, false, CL_warning);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_TALK3), true, false, false, CL_warning);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_TALK4), true, false, false, CL_seija);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_TALK5), true, false, false, CL_seija);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_TALK6), true, false, false, CL_seija);
			return true;
		}
	case GT_LILLY:
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_WELCOME), true, false, false, CL_lilly);
			return true;
		}
	case GT_MIKO:
	{
		level_ = (you.piety/40)+1; //0,1~19,21~39,40~59,60~79,80~99,100
		if(you.piety == 0)
			level_ = 0;
		if(you.isSetMikoBuff(0) && level_ < 3)
			level_ = 3;
		if(you.isSetMikoBuff(1)) {
			level_ = 6;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_TALK1), true, false, false, CL_miko);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_TALK2), true, false, false, CL_miko);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_TALK3), true, false, false, CL_miko);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_TALK4), true, false, false, CL_miko);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_TALK5), true, false, false, CL_miko);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_TALK6), true, false, false, CL_miko);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_TALK7), true, false, false, CL_miko);
			return true;
		}
	}
	case GT_OKINA:
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_TALK1), true, false, false, CL_okina);
			return true;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_TALK2), true, false, false, CL_okina);
			return true;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_TALK3), true, false, false, CL_okina);
			return true;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_TALK4), true, false, false, CL_okina);
			return true;
		case 4:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_TALK5), true, false, false, CL_okina);
			return true;
		case 5:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_TALK6), true, false, false, CL_okina);
			return true;
		case 6:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_TALK7), true, false, false, CL_okina);
			return true;
		}
	case GT_JUNKO:
		switch (level_)
		{
		default:
		case 0:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_TALK), true, false, false, CL_junko);
			return true;
		}
	}
	return false;

}