//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: seija.cpp
//
// 내용: 세이자 내용
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "seija.h"
#include "environment.h"
#include "enum.h"
#include "skill_use.h"
#include "key.h"
#include "god.h"
#include "note.h"
#include "weapon.h"
#include "potion.h"
#include "evoke.h"
#include "book.h"




bool seija_gift()
{
	int seija_level_ = 7-pietyLevel(you.piety);

	if(seija_level_ == 6)
	{
		printlog(seija_talk(GT_NONE, seija_level_), true,false,false,CL_seija);
		
		MoreWait();
		
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_ABANDONED,true,false,false,CL_danger,
			PlaceHolderHelper(GetGodString(you.god)));
	
		//you.PunishUpDown(30, you.god , true);

		AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_GOD_ABANDONED, PlaceHolderHelper(GetGodString(you.god))),CL_small_danger);

		for(int level_ = pietyLevel(you.piety);level_>=0;level_--)
			GetGodAbility(level_, false);
		you.Ability(SKL_ABANDON_GOD,true,true);
		you.god = GT_NONE;

		item_infor t;
		env[current_level].MakeItem(you.position, makeitem(ITM_MISCELLANEOUS, 0, &t, EVK_MAGIC_HAMMER));
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_FINAL_GIFT), true, false, false, CL_dark_good);
		return true;
	}

	int temp = you.Ability(SKL_SEIJA_GIFT,true,true);
	
	if(temp)
	{	
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_TIMEOUT),true,false,false,CL_small_danger);
		MoreWait();
		printlog(seija_talk(GT_NONE, seija_level_), true,false,false,CL_seija);
		you.StepUpDownPiety(-1);
		return true;
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_ON) + " ",false,false,false,CL_seija);
		printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_SEIJA_GIFT_HELP, PlaceHolderHelper("a")),true,false,false,CL_help);
		MoreWait();

		you.Ability(SKL_SEIJA_GIFT,true,false);
		return true;

	}
}

string seija_god_string(int god, int num) {

	switch (god)
	{
	case GT_BYAKUREN:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_BYAKUREN1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_BYAKUREN2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_BYAKUREN3);
		}
	case GT_JOON_AND_SION:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_JOON_AND_SION1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_JOON_AND_SION2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_JOON_AND_SION3);
		}
	case GT_KANAKO:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_KANAKO1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_KANAKO2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_KANAKO3);
		}
	case GT_SUWAKO:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SUWAKO1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SUWAKO2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SUWAKO3);
		}
	case GT_MINORIKO:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_MINORIKO1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_MINORIKO2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_MINORIKO3);
		
		}
	case GT_MIMA:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_MIMA1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_MIMA2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_MIMA3);
		}
	case GT_SHINKI:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SHINKI1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SHINKI2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SHINKI3);
		}
	case GT_YUUGI:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YUUGI1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YUUGI2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YUUGI3);
		}
	case GT_SHIZUHA:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SHIZUHA1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SHIZUHA2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SHIZUHA3);
		}
	case GT_HINA:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_HINA1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_HINA2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_HINA3);
		}
	case GT_YUKARI:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YUKARI1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YUKARI2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YUKARI3);
		}
	case GT_EIRIN:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_EIRIN1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_EIRIN2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_EIRIN3);
		}
	case GT_YUYUKO:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YUYUKO1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YUYUKO2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YUYUKO3);
		}
	case GT_SATORI:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SATORI1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SATORI2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SATORI3);
		}
	case GT_TENSI:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_TENSI1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_TENSI2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_TENSI3);
		}
	case GT_SEIJA:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SEIJA1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_SEIJA2);
		case 2: return LocalzationManager::locString(LOC_EMPTYSTRING);
		}
	case GT_LILLY:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_LILLY1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_LILLY2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_LILLY3);
		}
	case GT_MIKO:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_MIKO1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_MIKO2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_MIKO3);
		}
	case GT_OKINA:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_OKINA1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_OKINA2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_OKINA3);
		}
	case GT_JUNKO:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_JUNKO1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_JUNKO2);
		case 2: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_JUNKO3);
		}
	case GT_ERROR:
	case GT_NONE:
	default:
		switch (num) {
		case 0: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_DEFAULT1);
		case 1: return LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_DEFAULT2);
		case 2: return LocalzationManager::locString(LOC_EMPTYSTRING);
		}
	
	}
	return LocalzationManager::locString(LOC_SYSTEM_BUG);
}


void seija_real_gift(int key_)
{	
	switch(key_)
	{
		case GT_BYAKUREN: //무작위 책 2~4개
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{
					random_extraction<int> rand_;

					for(int j=SKT_SPELLCASTING+1; j<SKT_EVOCATE;j++)
					{
						rand_.push(i, you.GetSkillLevel(j, false)>15?15:(you.GetSkillLevel(j, false)>1?5:1));
					}
					book_list book_ = BOOK_FIRST;
					for(int j=SKT_SPELLCASTING+1; j<SKT_EVOCATE;j++)
					{
						book_ = SchoolToBook((skill_type)rand_.pop());
						if(!iden_list.books_list[book_])
						{
							break;
						}
					}
					
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, book_));
				}
			}
			break;
		case GT_KANAKO: //무작위 무기 3~5개
			{
				for(int i = rand_int(3,5); i > 0; i--)
				{
					kanako_gift(false);
				}
			}
			break;
		case GT_SUWAKO: //무작위 스펠카드 2~4개
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_SPELL, 0, &t, randA(SPC_V_MAX-1)));
				}
			}
			break;
		case GT_MINORIKO: //고구마 10~30개
			{
				for(int i = 10; i > 0; i--)
				{	
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_FOOD, 0, &t, 1));
				}
			}
			break;
		case GT_MIMA: //미마의 봉인서
			{
				for(int i = 1; i > 0; i--)
				{	
					item_infor t;
					item *it = env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, BOOK_TEST_ANNIHILATE));
					it->Identify();
				}
			}
			break;
		case GT_SHINKI: //영격두루마리 2~4장
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{	
					item_infor t;
					item *it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_SOUL_SHOT));
					it->Identify();
				}
			}
			break;
		case GT_YUUGI:
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{	
					armour_gift(false, false);
				}
			}
			break;
		case GT_SHIZUHA:
			{
				random_extraction<int> rand_;

				for(int i=SKT_SHORTBLADE;i<=SKT_SPEAR;i++)
				{
					rand_.push(i-SKT_SHORTBLADE, you.GetSkillLevel(i, false) +1);
				}
				item_infor t;
				item* it = env[current_level].MakeItem(you.position,makeitem((item_type)(rand_.pop()), randA(2)?1:0, &t));
				it->value5 = WB_AUTUMN;
			}
			break;
		case GT_HINA:
			{
				for(int i = rand_int(2,3); i > 0; i--)
				{	
					jewelry_gift(false, true, false);
				}
			}
			break;
		case GT_YUKARI://공간두루마리 3~7장 순간이동두루마리 0~3장
			{
				for(int i = rand_int(3,7); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_TELEPORT));
					it->Identify();
				}
				for(int i = rand_int(0,3); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_BLINK));
					it->Identify();
				}
			}
			break;
		case GT_EIRIN: //포션 6~12개
			{
				for(int i = rand_int(6,12); i > 0; i--)
				{					
					potion_type type_= goodbadpotion(randA(2)>1?1:(randA(60)?2:3));
					
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t,(int)type_));
				}
			}
			break;
		case GT_YUYUKO: //무작위 발동템 2개
			{
				random_extraction<int> rand_;

				for (int i = 0; i < EVK_MAX; i++) {
					if (i != EVK_MAGIC_HAMMER && i != EVK_SKY_TORPEDO && i != EVK_CAMERA
						) {
						rand_.push(i);
					}
				}
				for(int i = 2; i > 0; i--)
				{
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_MISCELLANEOUS, 0, &t,rand_.pop()));
				}
			}
			break;
		case GT_SATORI: //식별두루마리 7~12개
			{
				for(int i = rand_int(7,12); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_IDENTIFY));
					it->Identify();
				}
			}
			break;
		case GT_TENSI: //무작위 아이템 4~8개... 무려 던전 1층의!!
			{				
				for(int i = rand_int(4,8); i > 0; i--)
				{	
					item_infor t;
					env[current_level].MakeItem(you.position,CreateFloorItem(0,&t));
				}
			}
			break;
		case GT_LILLY: //탄막뭉치
			{				
				for(int i = rand_int(4,7); i > 0; i--)
				{	
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_THROW_TANMAC, 0, &t));
				}
			}
			break;
		case GT_JOON_AND_SION:
		{
			for (int i = 2; i > 0; i--)
			{
				item_infor t;
				env[current_level].MakeItem(you.position, makeitem(ITM_AMULET, 0, &t));
			}
		}
		break;
		case GT_MIKO:
		{
			for (int i = 1; i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_ARMOR_CLOAK, 0, &t));
				MakeArtifact(it, 3); //다른 아이템보다 효과가 좋음
			}
		}
		break;
		case GT_OKINA:
		{
			for (int i = rand_int(2,4); i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_SCROLL, 0, &t, SCT_SANTUARY));
				it->Identify();
			}
		}
		break;
		case GT_JUNKO:
		{
			for (int i = rand_int(3, 6); i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_SCROLL, 0, &t, SCT_ENCHANT_WEAPON_1));
				it->Identify();
			}
			for (int i = rand_int(2, 3); i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_SCROLL, 0, &t, SCT_ENCHANT_ARMOUR));
				it->Identify();
			}
		}
		break;
	}
}

string seija_summon_buff() {

	switch (randA(9))
	{
	case 0:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF1);
	case 1:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF2);
	case 2:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF3);
	case 3:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF4);
	case 4:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF5);
	case 5:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF6);
	case 6:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF7);
	case 7:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF8);
	case 8:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF9);
	case 9:
		return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF10);
	}

	return LocalzationManager::locString(LOC_SYSTEM_SEIJA_SUMMON_BUFF1);
}


string seija_talk(god_type god_, int piety)
{
	if(piety >= 1 && piety <= 3)
	{
		switch(god_)
		{
		case GT_ERROR:
		case GT_NONE:
		case GT_SEIJA:
		default:
			break;
		case GT_JOON_AND_SION:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_JOON_AND_SION1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_JOON_AND_SION2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_JOON_AND_SION3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_JOON_AND_SION4);
			}
			break;
		case GT_BYAKUREN:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_BYAKUREN1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_BYAKUREN2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_BYAKUREN3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_BYAKUREN4);
			}
			break;
		case GT_KANAKO:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_KANAKO1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_KANAKO2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_KANAKO3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_KANAKO4);
			}
			break;
		case GT_SUWAKO:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SUWAKO1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SUWAKO2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SUWAKO3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SUWAKO4);
			}
			break;
		case GT_MINORIKO:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MINORIKO1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MINORIKO2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MINORIKO3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MINORIKO4);
			}
			break;
		case GT_MIMA:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MIMA1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MIMA2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MIMA3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MIMA4);
			}
			break;
		case GT_SHINKI:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SHINKI1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SHINKI2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SHINKI3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SHINKI4);
			}
			break;
		case GT_YUUGI:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUUGI1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUUGI2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUUGI3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUUGI4);
			}
			break;
		case GT_SHIZUHA:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SHIZUHA1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SHIZUHA2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SHIZUHA3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SHIZUHA4);
			}
			break;
		case GT_HINA:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_HINA1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_HINA2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_HINA3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_HINA4);
			}
			break;
		case GT_YUKARI:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUKARI1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUKARI2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUKARI3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUKARI4);
			}
			break;
		case GT_EIRIN:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_EIRIN1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_EIRIN2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_EIRIN3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_EIRIN4);
			}
			break;
		case GT_YUYUKO:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUYUKO1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUYUKO2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUYUKO3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_YUYUKO4);
			}
			break;
		case GT_SATORI:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SATORI1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SATORI2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SATORI3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_SATORI4);
			}
			break;
		case GT_TENSI:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_TENSI1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_TENSI2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_TENSI3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_TENSI4);
			}
			break;
		case GT_LILLY:
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_LILLY1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_LILLY2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_LILLY3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_LILLY4);
			}
			break;
		case GT_MIKO:
			switch (randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MIKO1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MIKO2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MIKO3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_MIKO4);
			}
			break;
		case GT_OKINA:
			switch (randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_OKINA1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_OKINA2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_OKINA3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_OKINA4);
			}
			break;
		case GT_JUNKO:
			switch (randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_JUNKO1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_JUNKO2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_JUNKO3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_GOD_JUNKO4);
			}
			break;
		}
	}

	switch(piety)
	{
	case 0:
		switch(randA(4))
		{
		case 0:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_WELCOME1);
		case 1:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_WELCOME2);
		case 2:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_WELCOME3);
		case 3:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_WELCOME4);
		case 4:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_WELCOME5);
		}
		break;		
	case 1:
	case 2:
	case 3:
		switch(randA(5))
		{
		case 0:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_REFUSE_ITEM1);
		case 1:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_REFUSE_ITEM2);
		case 2:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_REFUSE_ITEM3);
		case 3:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_REFUSE_ITEM4);
		case 4:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_REFUSE_ITEM5);
		case 5:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_REFUSE_ITEM6);
		}
		break;		
	case 4:
		if(god_ == GT_NONE)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DOUBT_REFUSE_ITEM1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DOUBT_REFUSE_ITEM2);
			}
		}
		else
		{			
			switch(randA(6))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DOUBT1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DOUBT2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DOUBT3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DOUBT4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DOUBT5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DOUBT6);
			case 6:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DOUBT7);
			}	
		}
		break;	
	case 5:		
		if(god_ == GT_NONE)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST_ITEM1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST_ITEM2);
			}
		}
		else
		{
			switch(randA(6))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST6);
			case 6:
				return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST7);
			}
		}
		break;	
	case 6: //세이자의 배신
		switch(randA(6))
		{
		case 0:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDONED1);
		case 1:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDONED2);
		case 2:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDONED3);
		case 3:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDONED4);
		case 4:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDONED5);
		case 5:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDONED6);
		case 6:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDONED7);
		}
		break;			
	case 7:		//세이자를 배신
		switch(randA(3))
		{
		case 0:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDON1);
		case 1:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDON2);
		case 2:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDON3);
		case 3:
			return LocalzationManager::locString(LOC_SYSTEM_SEIJA_ABANDON4);
		}
		break;	
	}

	
	return LocalzationManager::locString(LOC_SYSTEM_SEIJA_DISTRUST1);
}
