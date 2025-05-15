//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: wiz.cpp
//
// 내용: 위자드모드!!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "smoke.h"
#include "key.h"
#include "rect.h"
#include "mon_infor.h"

#include "spellcard.h"
#include "skill_use.h"
#include "weapon.h"
#include "map.h"
#include "evoke.h"
#include "god.h"
#include "tribe.h"


extern HANDLE mutx;
wiz_infor wiz_list;
extern int create_bamboo_mon();

bool skill_summon_bug(int pow, bool short_, unit* order, coord_def target);

void create_and_kill(int floor, float percent_ = 1.0f) {
	env[floor].MakeMap(true);
	for(vector<monster>::iterator it = env[floor].mon_vector.begin(); it != env[floor].mon_vector.end(); it++)
	{
		if(it->isLive() && percent_ > 0.0f && rand_float(0.0f,1.0f) <= percent_)
			it->dead(PRT_PLAYER,false);
	}
	if(floor != current_level) {
		for(list<item>::iterator it = env[floor].item_list.begin(); it != env[floor].item_list.end(); )
		{
			list<item>::iterator temp = it++;
			if(percent_ > 0.0f && rand_float(0.0f,1.0f) <= percent_)
			{
				env[current_level].AddItem(you.position, &(*temp));
				env[floor].DeleteItem(&(*temp));
			}
		}
	} else {
		for(list<item>::iterator it = env[current_level].item_list.begin(); it != env[current_level].item_list.end(); it++)
		{
			it->position = you.position;
		}
	}
}

void wiz_mode()
{

	if(wiz_list.wizard_mode != 1)
	{

		
		printlog("#### " + LocalzationManager::locString(LOC_SYSTEM_DEBUG_WARN) +" ### ",true,false,false,CL_danger);
		printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_WARN_YN),false,false,false,CL_danger);
		printlog(" (",false,false,false,CL_danger);
		printlog("Y",false,false,false,CL_danger, 'Y');
		printlog("/",false,false,false,CL_danger);
		printlog("N",false,false,false,CL_danger, 'N');
		printlog(") ",false,false,false,CL_danger);
		startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});

		
		int key_ = waitkeyinput();
		switch(key_)
		{
		case 'Y':
			enterlog();
			endSelection();
			break;
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_WIZARD_CANCLE),true,false,false,CL_help);
			endSelection();
			return;
		}

	}



	printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_WHICH),true,false,false,CL_help);
	wiz_list.wizard_mode = 1;
	while(1)
	{
		int key_ = waitkeyinput();
	
		changedisplay(DT_GAME);
		switch (key_)
		{
		case 'D': //맵밝히기
			for (int i = 0; i < DG_MAX_X; i++)
				for (int j = 0; j < DG_MAX_Y; j++)
					env[current_level].magicmapping(i, j);
			break;
		case 'A':
		{
			ostringstream ss;
			ss << "p-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_POTION)
			   << " s-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_SCROLL)
			   << " e-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_EVOCABLE)
			   << " v-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_SPELLCARD)
			   << " r-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_RING)
			   << " b-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_BOOK)
			   << " a-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_ARMOUR)
			   << " R-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET)
			   << " f-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_TANMAC);


			printlog(ss.str(), true, false, false, CL_help);
			printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_ITEM), false, false, false, CL_help);
			key_ = waitkeyinput();
			switch (key_)
			{
			case 'p':
			{
				int list[PT_MAX] = { PT_WATER,	PT_HEAL, PT_POISON,	PT_HEAL_WOUND, PT_MIGHT, PT_HASTE, PT_CONFUSE,
					PT_SLOW, PT_PARALYSIS, PT_CLEVER, PT_AGILITY, PT_MAGIC, PT_LEVETATION, PT_POWER,
					PT_DOWN_STAT, PT_RECOVER_STAT, PT_ALCOHOL };
				LOCALIZATION_ENUM_KEY keylist[PT_MAX] = {
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_WATER_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_HEAL_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_POISON_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_HEAL_WOUND_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_MIGHT_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_HASTE_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_CONFUSE_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_SLOW_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_PARALYSIS_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_CLEVER_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_AGILITY_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_MAGIC_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_LEVETATION_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_POWER_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_DOWN_STAT_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_RECOVER_STAT_SHORT,
					LOC_SYSTEM_ITEM_POTION_POTION_IDEN_ALCOHOL_SHORT
				};
					
				enterlog();
				for(int i = 0; i < PT_MAX; i++) {
					ss.str("");
					ss.clear();
					ss << string(1,(char)('a'+i)) << "-" << LocalzationManager::locString(keylist[i]) << " ";
					printlog(ss.str(), (i==PT_MAX-1?true:false), false, false, CL_help);
				}
				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_POTION), false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 'q')
				{
					for (int i = 0; i < 10; i++)
					{
						item_infor t;
						makeitem(ITM_POTION, 0, &t, list[key_ - 'a']);
						env[current_level].MakeItem(you.position, t);
						enterlog();
					}
				}
				else {
					printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
				}
			}
			return;
			case 's':
			{
				int list[SCT_MAX-1] = { SCT_TELEPORT,SCT_IDENTIFY,SCT_NONE,SCT_CURSE_WEAPON,SCT_CURSE_ARMOUR,SCT_REMOVE_CURSE,
					SCT_BLINK,SCT_MAPPING,SCT_ENCHANT_WEAPON_1,	SCT_ENCHANT_ARMOUR,SCT_FOG,SCT_DETECT_CURSE,
					SCT_CURSE_JEWELRY,SCT_SILENCE,SCT_SOUL_SHOT,SCT_CHARGING,SCT_AMNESIA, SCT_SANTUARY, SCT_BRAND_WEAPON };
				
				LOCALIZATION_ENUM_KEY keylist[SCT_MAX-1] = {
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_TELEPORT_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_IDENTIFY_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_NONE_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_CURSE_WEAPON_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_CURSE_ARMOUR_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_REMOVE_CURSE_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_BLINK_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_MAPPING_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_ENCHANT_WEAPON_1_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_ENCHANT_ARMOUR_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_FOG_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_DETECT_CURSE_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_CURSE_JEWELRY_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_SILENCE_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_SOUL_SHOT_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_CHARGING_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_AMNESIA_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_SANTUARY_SHORT,
					LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_BRAND_WEAPON_SHORT
				};

				enterlog();
				for(int i = 0; i < SCT_MAX-1; i++) {
					ss.str("");
					ss.clear();
					ss << string(1,(char)('a'+i)) << "-" << LocalzationManager::locString(keylist[i]) << " ";
					printlog(ss.str(), (i==SCT_MAX-2?true:false), false, false, CL_help);
				}

				
				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_SCROLL), false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 's')
				{
					for (int i = 0; i < 10; i++)
					{
						item_infor t;
						makeitem(ITM_SCROLL, 0, &t, list[key_ - 'a']);
						env[current_level].MakeItem(you.position, t);
						enterlog();
					}
				}
				else {
					printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
				}
			}
			return;
			case 'e':
			{
				int list[EVK_MAX-1] = { EVK_PAGODA,EVK_AIR_SCROLL,EVK_DREAM_SOUL,EVK_BOMB, EVK_GHOST_BALL, EVK_SKY_TORPEDO, EVK_MAGIC_HAMMER };
				
				LOCALIZATION_ENUM_KEY keylist[EVK_MAX-1] = {
					LOC_SYSTEM_ITEM_EVOKE_PAGODA,
					LOC_SYSTEM_ITEM_EVOKE_AIR_SCROLL,
					LOC_SYSTEM_ITEM_EVOKE_DREAM_SOUL,
					LOC_SYSTEM_ITEM_EVOKE_BOMB,
					LOC_SYSTEM_ITEM_EVOKE_GHOST_BALL,
					LOC_SYSTEM_ITEM_EVOKE_SKY_TORPEDO,
					LOC_SYSTEM_ITEM_EVOKE_MAGIC_HAMMER
				};
				enterlog();
				for(int i = 0; i < EVK_MAX-1; i++) {
					ss.str("");
					ss.clear();
					ss << string(1,(char)('a'+i)) << "-" << LocalzationManager::locString(keylist[i]) << " ";
					printlog(ss.str(), (i==EVK_MAX-2?true:false), false, false, CL_help);
				}
				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_EVOKE), false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 'g')
				{
					item_infor t;
					makeitem(ITM_MISCELLANEOUS, 0, &t, list[key_ - 'a']);
					env[current_level].MakeItem(you.position, t);
					enterlog();
				}
				else {
					printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
				}
			}
			return;
			case 'v':
			{
				int list[SPC_V_MAX] = { SPC_V_FIRE,SPC_V_ICE,SPC_V_EARTH,SPC_V_AIR,SPC_V_INVISIBLE,SPC_V_METAL, SPC_V_SUN };
				
				LOCALIZATION_ENUM_KEY keylist[SPC_V_MAX] = {
					LOC_SYSTEM_SPELLCARD_FIRE,
					LOC_SYSTEM_SPELLCARD_ICE,
					LOC_SYSTEM_SPELLCARD_EARTH,
					LOC_SYSTEM_SPELLCARD_AIR,
					LOC_SYSTEM_SPELLCARD_INVISIBLE,
					LOC_SYSTEM_SPELLCARD_METAL,
					LOC_SYSTEM_SPELLCARD_SUN
				};
				
				enterlog();
				for(int i = 0; i < SPC_V_MAX; i++) {
					ss.str("");
					ss.clear();
					ss << string(1,(char)('a'+i)) << "-" << LocalzationManager::locString(keylist[i]) << " ";
					printlog(ss.str(), (i==SPC_V_MAX-1?true:false), false, false, CL_help);
				}
				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_SPELLCARD), false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 'g')
				{
					item_infor t;
					makeitem(ITM_SPELL, 0, &t, list[key_ - 'a']);
					env[current_level].MakeItem(you.position, t);
					enterlog();
				}
				else {
					printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
				}
			}
			return;
			case 'r':
			{
				int list[RGT_MAX] = { RGT_STR,RGT_DEX,RGT_INT,RGT_HUNGRY,RGT_FULL,RGT_TELEPORT,RGT_POISON_RESIS,
					RGT_FIRE_RESIS,	RGT_ICE_RESIS,RGT_SEE_INVISIBLE/*,RGT_GRAZE*/,RGT_LEVITATION,RGT_INVISIBLE,
					RGT_MANA,RGT_MAGACIAN,RGT_AC,RGT_EV,RGT_CONFUSE_RESIS,	RGT_ELEC_RESIS,RGT_MAGIC_RESIS };
				
				LOCALIZATION_ENUM_KEY keylist[RGT_MAX] = {
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_STR_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_DEX_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_INT_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_HUNGRY_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_FULL_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_TELEPORT_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_POISON_RESIST_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_FIRE_RESIST_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_ICE_RESIST_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_SEE_INVISIBLE_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_LEVITATION_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_INVISIBLE_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_MANA_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_MAGACIAN_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_AC_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_EV_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_CONFUSE_RESIS_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_ELEC_RESIS_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_MAGIC_RESIS_SHORT
				};
				enterlog();
				for(int i = 0; i < RGT_MAX; i++) {
					ss.str("");
					ss.clear();
					ss << string(1,(char)('a'+i)) << "-" << LocalzationManager::locString(keylist[i]) << " ";
					printlog(ss.str(),false, false, false, CL_help);
				}				
				ss.str("");
				ss.clear();
				ss << string(1,'!') << "-" << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT);
				printlog(ss.str(),true, false, false, CL_help);
				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_RING), false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 's')
				{
					item_infor t;
					makeitem(ITM_RING, 0, &t, list[key_ - 'a']);
					env[current_level].MakeItem(you.position, t);
					enterlog();
				}
				else if (key_ == '!')
				{
					item_infor t;
					makeitem(ITM_RING, randA(9) ? 1 : -1, &t);
					t.artifact = true;
					item *it_ = env[current_level].MakeItem(you.position, t);
					MakeArtifact(it_, it_->curse ? -1 : 1);
					enterlog();

				}
				else {
					printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
				}
			}
			return;
			case 'b':
			{
				item_infor t;
				makeitem(ITM_BOOK, 0, &t, -1);
				env[current_level].MakeItem(you.position, t);
			}
			return;
			case 'a':
			{
				item_infor t;
				item_type atype_ = (item_type)rand_int(ITM_ARMOR_BODY_FIRST, ITM_ARMOR_BODY_LAST - 1);
				if (randA(1) == 0)
					atype_ = (item_type)rand_int(ITM_ARMOR_HEAD, ITM_ARMOR_BOOT);
				makeitem(atype_, randA(2) ? 0 : (randA(3) ? 1 : -1), &t);
				if (randA(1))
					t.artifact = true;
				item *it_ = env[current_level].MakeItem(you.position, t);
				if (t.artifact)
					MakeArtifact(it_, it_->curse ? -1 : 1);
			}
			return;
			case 'R':
			{
				int list[AMT_MAX] = { AMT_PERFECT, AMT_BLOSSOM, AMT_TIMES, AMT_FAITH, AMT_WAVE, AMT_SPIRIT, AMT_GRAZE,
					AMT_WEATHER, AMT_OCCULT };
				LOCALIZATION_ENUM_KEY keylist[AMT_MAX] = {
					LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_PERFECT_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_BLOSSOM_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_TIMES_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_FAITH_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_WAVE_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_SPIRIT_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_GRAZE_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_WEATHER_SHORT,
					LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_OCCULT_SHORT
				};
				enterlog();
				for(int i = 0; i < AMT_MAX; i++) {
					ss.str("");
					ss.clear();
					ss << string(1,(char)('a'+i)) << "-" << LocalzationManager::locString(keylist[i]) << " ";
					printlog(ss.str(), (i==AMT_MAX-1?true:false), false, false, CL_help);
				}
				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_AMULET), false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 'i')
				{
					item_infor t;
					makeitem(ITM_AMULET, 0, &t, list[key_ - 'a']);
					env[current_level].MakeItem(you.position, t);
					enterlog();
				}
				else {
					printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
				}
			}
			return;
			case 'f':
			{
				item_infor t;
				makeitem(ITM_THROW_TANMAC, 0, &t, -1);
				env[current_level].MakeItem(you.position, t);
			}
			return;
			default:
				printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
				return;
			}

		}
		case 'H':
			you.HpUpDown(you.GetMaxHp(), DR_EFFECT);
			if(!you.pure_mp)
				you.MpUpDown(you.max_mp);
			you.PowUpDown(500, true);
			break;
		case 'P':
			you.system_exp.value = 0;
			if (you.system_exp.value <= 0) {
				you.system_exp.value = 0;
				item* _item = you.equipment[ET_NECK];
				if (_item && _item->type == ITM_AMULET) {
					chargingFinish((amulet_type)_item->value1, 1);
					if (you.system_exp.value <= 0) {
						if (isCanCharge((amulet_type)_item->value1)) {
							printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_CHARGING_FINISH), true, false, false, CL_white_puple);
						}
						else {
							printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_CHARGING_FINISH_PASSIVE), true, false, false, CL_white_puple);
						}
					}
				}
			}
			break;
		case 'X':
			you.GetExp(you.GetNeedExp(you.level - 1) - you.exper);
			break;
		case '>': //다음층 이동
			if (!environment::isLastFloor(current_level))
			{
				deque<monster*> dq;
				env[current_level + 1].EnterMap(0, dq);
				//you.resetLOS(false);
			}
			break;
		case '<': //이전층 이동	
			if (!environment::isFirstFloor(current_level))
			{
				deque<monster*> dq;
				env[current_level - 1].EnterMap(0, dq);
				//you.resetLOS(false);
			}
			break;
		case 'G': //던전이동	
		{
			deque<monster*> dq;
			dungeon_level next_ = TEMPLE_LEVEL;

			pair<char,LOCALIZATION_ENUM_KEY> keylist[17] = {
				make_pair('d',LOC_SYSTEM_DUNGEON),
				make_pair('t',LOC_SYSTEM_DUNGEON_TEMPLE),
				make_pair('l',LOC_SYSTEM_DUNGEON_MISTYLAKE),
				make_pair('m',LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN),
				make_pair('s',LOC_SYSTEM_DUNGEON_SCARLET),
				make_pair('b',LOC_SYSTEM_DUNGEON_SCARLET_LIBRARY),
				make_pair('u',LOC_SYSTEM_DUNGEON_SCARLET_UNDER),
				make_pair('a',LOC_SYSTEM_DUNGEON_BAMBOO),
				make_pair('e',LOC_SYSTEM_DUNGEON_EINENTEI),
				make_pair('y',LOC_SYSTEM_DUNGEON_YUKKURI),
				make_pair('p',LOC_SYSTEM_DUNGEON_DEPTH),
				make_pair('h',LOC_SYSTEM_DUNGEON_SUBTERRANEAN),
				make_pair('r',LOC_SYSTEM_DUNGEON_DREAM),
				make_pair('o',LOC_SYSTEM_DUNGEON_MOON),
				make_pair('k',LOC_SYSTEM_DUNGEON_PANDEMONIUM),
				make_pair('z',LOC_SYSTEM_DUNGEON_HAKUREI),
				make_pair('!',LOC_SYSTEM_DUNGEON_ZIGURRAT)
			};
			enterlog();
			for(int i = 0; i < 17; i++) {
				ostringstream ss;
				ss << string(1,keylist[i].first) << "-" << LocalzationManager::locString(keylist[i].second) << " ";
				printlog(ss.str(), (i==16?true:false), false, false, CL_help);
			}
			printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_TRAVEL_DUNGEON), false, false, false, CL_help);
			key_ = waitkeyinput();
			switch (key_)
			{
			case 'd':
				next_ = (dungeon_level)0;
				break;
			case 'D':
				next_ = MAX_DUNGEUN_LEVEL;
				break;
			case 't':
			case 'T':
				next_ = TEMPLE_LEVEL;
				break;
			case 'l':
				next_ = MISTY_LAKE_LEVEL;
				break;
			case 'L':
				next_ = MISTY_LAKE_LAST_LEVEL;
				break;
			case 'm':
				next_ = YOUKAI_MOUNTAIN_LEVEL;
				break;
			case 'M':
				next_ = YOUKAI_MOUNTAIN_LAST_LEVEL;
				break;
			case 's':
				next_ = SCARLET_LEVEL;
				break;
			case 'S':
				next_ = SCARLET_LEVEL_LAST_LEVEL;
				break;
			case 'b':
			case 'B':
				next_ = SCARLET_LIBRARY_LEVEL;
				break;
			case 'u':
			case 'U':
				next_ = SCARLET_UNDER_LEVEL;
				break;
			case 'a':
			case 'A':
				next_ = BAMBOO_LEVEL;
				break;
			case 'e':
			case 'E':
				next_ = EIENTEI_LEVEL;
				break;
			case 'h':
				next_ = SUBTERRANEAN_LEVEL;
				break;
			case 'H':
				next_ = SUBTERRANEAN_LEVEL_LAST_LEVEL;
				break;
			case 'y':
				next_ = YUKKURI_LEVEL;
				break;
			case 'Y':
				next_ = YUKKURI_LAST_LEVEL;
				break;
			case 'p':
				next_ = DEPTH_LEVEL;
				break;
			case 'P':
				next_ = DEPTH_LAST_LEVEL;
				break;
			case 'r':
			case 'R':
				next_ = DREAM_LEVEL;
				break;
			case 'o':
			case 'O':
				next_ = MOON_LEVEL;
				break;
			case 'k':
			case 'K':
				next_ = PANDEMONIUM_LEVEL;
				break;
			case 'z':
				next_ = HAKUREI_LEVEL;
				break;
			case 'Z':
				next_ = HAKUREI_LAST_LEVEL;
				break;
			case '!':
				next_ = ZIGURRAT_LEVEL;
				break;
			default:
				printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
				return;
			}
			enterlog();
			env[next_].EnterMap(0, dq);
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_DOWN), true, false, false, CL_normal);
			//you.resetLOS(false);
			break;
		}
		case 'R': //맵 재생성	
		{
			for(int m_id = 0;  m_id < MON_MAX; m_id++) {
				if(mondata[m_id].flag & M_FLAG_UNIQUE)
					unset_exist_named((monster_index)m_id);
			}
			deque<monster*> dq;
			env[current_level].ClearFloor();
			env[current_level].make = false;
			env[current_level].EnterMap(0, dq);
			break;
		}
		case 'b':
			you.Blink(40);
			break;
		case 'w': //날씨발현
		{
			LOCALIZATION_ENUM_KEY keylist[3] = {
				LOC_SYSTEM_BUFF_FOG,
				LOC_SYSTEM_BUFF_THUNDER,
				LOC_SYSTEM_BUFF_SUNNY
			};
			for(int i = 0; i < 3; i++) {
				ostringstream ss;
				ss << string(1,(char)('a'+i)) << "-" << LocalzationManager::locString(keylist[i]) << " ";
				printlog(ss.str(), (i==2?true:false), false, false, CL_help);
			}
			printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_WEATHER), false, false, false, CL_help);
			wiz_list.wizard_mode = true;
			key_ = waitkeyinput();
			switch (key_)
			{
			case 'a':
			case 'A':
				you.SetWeather(1, 100);
				break;
			case 'b':
			case 'B':
				you.SetWeather(2, 100);
				break;
			case 'c':
			case 'C':
				you.SetWeather(3, 100);
				break;
			default:
				break;
			}

		}
		break;
		case 'p':
		{
			dungeon_tile_type next_ = DG_TEMPLE_FIRST;

			pair<char,LOCALIZATION_ENUM_KEY> keylist[20] = {
				make_pair('B',LOC_SYSTEM_GOD_BYAKUREN),
				make_pair('K',LOC_SYSTEM_GOD_KANAKO),
				make_pair('W',LOC_SYSTEM_GOD_SUWAKO),
				make_pair('A',LOC_SYSTEM_GOD_MINORIKO),
				make_pair('M',LOC_SYSTEM_GOD_MIMA),
				make_pair('P',LOC_SYSTEM_GOD_SHINKI),
				make_pair('G',LOC_SYSTEM_GOD_YUUGI),
				make_pair('Z',LOC_SYSTEM_GOD_SHIZUHA),
				make_pair('H',LOC_SYSTEM_GOD_HINA),
				make_pair('Y',LOC_SYSTEM_GOD_YUKARI),
				make_pair('E',LOC_SYSTEM_GOD_EIRIN),
				make_pair('U',LOC_SYSTEM_GOD_YUYUKO),
				make_pair('S',LOC_SYSTEM_GOD_SATORI),
				make_pair('T',LOC_SYSTEM_GOD_TENSI),
				make_pair('R',LOC_SYSTEM_GOD_SEIJA),
				make_pair('L',LOC_SYSTEM_GOD_LILLY),
				make_pair('I',LOC_SYSTEM_GOD_MIKO),
				make_pair('O',LOC_SYSTEM_GOD_OKINA),
				make_pair('J',LOC_SYSTEM_GOD_JUNKO),
				make_pair('X',LOC_SYSTEM_GOD_JOON_AND_SION)
			};
			enterlog();
			for(int i = 0; i < 20; i++) {
				ostringstream ss;
				ss << string(1,keylist[i].first) << "-" << LocalzationManager::locString(keylist[i].second) << " ";
				printlog(ss.str(), (i==19?true:false), false, false, CL_help);
			}
			printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_ALTAR),false,false,false,CL_help);
			key_ = waitkeyinput();
			switch (key_)
			{
			case 'x':
			case 'X':
				next_ = DG_TEMPLE_JOON_AND_SION;
				break;
			case 'b':
			case 'B':
				next_ = DG_TEMPLE_BYAKUREN;
				break;
			case 'k':
			case 'K':
				next_ = DG_TEMPLE_KANAKO;
				break;
			case 'w':
			case 'W':
				next_ = DG_TEMPLE_SUWAKO;
				break;
			case 'a':
			case 'A':
				next_ = DG_TEMPLE_MINORIKO;
				break;
			case 'm':
			case 'M':
				next_ = DG_TEMPLE_MIMA;
				break;
			case 'p':
			case 'P':
				next_ = DG_TEMPLE_SHINKI;
				break;
			case 'g':
			case 'G':
				next_ = DG_TEMPLE_YUUGI;
				break;
			case 'z':
			case 'Z':
				next_ = DG_TEMPLE_SHIZUHA;
				break;
			case 'h':
			case 'H':
				next_ = DG_TEMPLE_HINA;
				break;
			case 'y':
			case 'Y':
				next_ = DG_TEMPLE_YUKARI;
				break;
			case 'e':
			case 'E':
				next_ = DG_TEMPLE_EIRIN;
				break;
			case 'u':
			case 'U':
				next_ = DG_TEMPLE_YUYUKO;
				break;
			case 's':
			case 'S':
				next_ = DG_TEMPLE_SATORI;
				break;
			case 't':
			case 'T':
				next_ = DG_TEMPLE_TENSI;
				break;
			case 'r':
			case 'R':
				next_ = DG_TEMPLE_SEIJA;
				break;
			case 'L':
			case 'l':
				next_ = DG_TEMPLE_LILLY;
				break;
			case 'i':
			case 'I':
				next_ = DG_TEMPLE_MIKO;
				break;
			case 'o':
			case 'O':
				next_ = DG_TEMPLE_OKINA;
				break;
			case 'j':
			case 'J':
				next_ = DG_TEMPLE_JUNKO;
				break;
			default:
				printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
				return;
			}
			enterlog();
			env[current_level].changeTile(you.position, next_);
		}
		break;
		case 'W':
			if (you.s_the_world)
			{
				you.s_the_world = 0;
			}
			else
			{
				you.s_the_world = -1;
			}
			break;
		case 'm': 
		{
			int id_ = 0;
			ostringstream oss;
			oss << LocalzationManager::locString(LOC_SYSTEM_DEBUG_CREATE_MONSTER) << "(0~" << (MON_MAX - 1) << ") :";
			printlog(oss.str(), false, false, false, CL_help);


			while (true) {
				deletelog();
				ostringstream oss;
				oss << id_ << " (" << mondata[id_].name.getName().c_str() << ")";
				printlog(oss.str(), false, false, true, CL_normal);

				InputedKey inputedKey;
				key_ = waitkeyinput(inputedKey,true);
				switch (key_) {
				case 'k':
				case VK_UP:
					id_ += 10;
					break;
				case 'j':
				case VK_DOWN:
					id_ -= 10;;
					break;
				case 'h':
				case VK_LEFT:
					id_--;
					break;
				case 'l':
				case VK_RIGHT:
					id_++;
					break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					id_ = key_ - '0' + id_*10;
					break;
				case VK_RETURN:
					if (monster* mon_ = BaseSummon(id_, 100, false, false, 2, &you, you.position, SKD_OTHER, -1))
					{
						mon_->state.SetState(MS_SLEEP);
						mon_->flag &= ~M_FLAG_SUMMON;
						mon_->ReturnEnemy();
					}
					enterlog();
					return;
				case VK_BACK:
					id_ = id_ / 10;
					break;					
				case -1:
					if(inputedKey.isRightClick()) {
						//ESC PASSTHORUGH
					}
					else {
						break;
					}
				case VK_ESCAPE://esc
					enterlog();
					printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_CANCLE_CREATE_MONSTER), true, false, false, CL_help);
					return;
				}
				if (id_ < 0)
					id_ = 0;
				if (id_ >= MON_MAX)
					id_ = MON_MAX - 1;

			}
		}
		break;
		case '.':
		{
		}
			break;
		case '^':
			if(you.god != GT_SEIJA)
				you.PietyUpDown(10);
			you.GiftCount(10);
			break;
		case 'o':
			you.hp = 1;
			break;
		case 'q':
		{
			D3DCOLOR color_[] = { CL_normal, CL_warning, CL_small_danger, CL_danger, CL_magic, CL_help, CL_alchemy };
			int j = 0;
			for (int i = 0; i < 27; i++) {
				char temp[100];
				_itoa_s(need_skill_exp(i, 100), temp, sizeof(temp), 10);
				printlog(temp, false, false, false, color_[j]);
				printlog(" ", false, false, false, CL_normal);
				if (i == 13)
					enterlog();
				if (i % 5 == 4)
					j++;
			}
			enterlog();
		}
			break;
		case 'C':
			{
				for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
				{
					if(it->isLive() && !(it->flag & M_FLAG_UNHARM))
						it->dead(PRT_PLAYER,false);
				}
				for(list<item>::iterator it = env[current_level].item_list.begin(); it != env[current_level].item_list.end(); it++)
				{
					it->position = you.position;
				}
			}
			break;
		case 'E':
			{
				//---------------------------------------일반던전(안개호수 입구까지)--------------------------------------------
				int prevexp_=0, exp_ = 0;
				for(int i = 0; i <= map_list.dungeon_enter[MISTY_LAKE].floor; i++)
				{
					create_and_kill(i);
				}
				exp_ = you.exper;
				{
					ostringstream oss;
					oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
						PlaceHolderHelper(LocalzationManager::locString(LOC_SYSTEM_DUNGEON) + " " + LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR,PlaceHolderHelper(to_string(map_list.dungeon_enter[MISTY_LAKE].floor+1)))),
						PlaceHolderHelper(to_string(you.level)),
						PlaceHolderHelper(to_string(exp_-prevexp_)));
					printlog(oss.str(),true,false,false,CL_normal);
				}

				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
				key_ = waitkeyinput(true);
				if(key_ != 'y') {
					break;
				}
				//---------------------------------------안개호수--------------------------------------------

				prevexp_ = exp_;
				 
				for(int i = MISTY_LAKE_LEVEL; i <= MISTY_LAKE_LAST_LEVEL; i++)
				{
					create_and_kill(i);
				}
				exp_ = you.exper;
				{
					ostringstream oss;
					oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
						PlaceHolderHelper(LOC_SYSTEM_DUNGEON_MISTYLAKE),
						PlaceHolderHelper(to_string(you.level)),
						PlaceHolderHelper(to_string(exp_-prevexp_)));
					printlog(oss.str(),true,false,false,CL_normal);
				}
				prevexp_ = exp_;

				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
				key_ = waitkeyinput(true);
				if(key_ != 'y') {
					break;
				}
				//----------------------------------------------나머지 던전 (9~15)-------------------------------------------------

				for(int i = map_list.dungeon_enter[MISTY_LAKE].floor+1; i <= MAX_DUNGEUN_LEVEL; i++)
				{
					create_and_kill(i);
				}
				exp_ = you.exper;
				ostringstream oss_;
				oss_ << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
					PlaceHolderHelper(LocalzationManager::locString(LOC_SYSTEM_DUNGEON) + " " + LocalzationManager::locString(LOC_SYSTEM_DUNGEON_LAST_FLOOR)),
					PlaceHolderHelper(to_string(you.level)),
					PlaceHolderHelper(to_string(exp_-prevexp_)));
				printlog(oss_.str(),true,false,false,CL_normal);
				prevexp_ = exp_;


				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
				key_ = waitkeyinput(true);
				if(key_ != 'y') {
					break;
				}
				//----------------------------------------------요괴산-------------------------------------------------

				for(int i = YOUKAI_MOUNTAIN_LEVEL; i <= YOUKAI_MOUNTAIN_LAST_LEVEL; i++)
				{
					create_and_kill(i);
				}
				exp_ = you.exper;
				{
					ostringstream oss;
					oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
						PlaceHolderHelper(LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN),
						PlaceHolderHelper(to_string(you.level)),
						PlaceHolderHelper(to_string(exp_-prevexp_)));
					printlog(oss.str(),true,false,false,CL_normal);
				}
				prevexp_ = exp_;


				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
				key_ = waitkeyinput(true);
				if(key_ != 'y') {
					break;
				}
				//----------------------------------------------홍마관-------------------------------------------------


				for(int i = SCARLET_LEVEL; i <= SCARLET_LEVEL_LAST_LEVEL; i++)
				{
					create_and_kill(i);
				}
				create_and_kill(SCARLET_LIBRARY_LEVEL);

				exp_ = you.exper;
				{
					ostringstream oss;
					oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
						PlaceHolderHelper(LOC_SYSTEM_DUNGEON_SCARLET),
						PlaceHolderHelper(to_string(you.level)),
						PlaceHolderHelper(to_string(exp_-prevexp_)));
					printlog(oss.str(),true,false,false,CL_normal);
				}
				prevexp_ = exp_;
				
				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
				key_ = waitkeyinput(true);
				if(key_ != 'y') {
					break;
				}
				//----------------------------------------------영원정-------------------------------------------------

				{
					env[EIENTEI_LEVEL].MakeMap(true);
					for(int i =0; i < 40;i++) {
						//좀운이 나빴다 치고 40마리 생성
						int id_ = create_bamboo_mon();
						dif_rect_iterator rit(you.position,5,true);
						monster *temp = env[current_level].AddMonster(id_,0,*rit);
						temp->dead(PRT_PLAYER,false);
					}
					create_and_kill(EIENTEI_LEVEL);
				}
				exp_ = you.exper;
				{
					ostringstream oss;
					oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
						PlaceHolderHelper(LOC_SYSTEM_DUNGEON_EINENTEI),
						PlaceHolderHelper(to_string(you.level)),
						PlaceHolderHelper(to_string(exp_-prevexp_)));
					printlog(oss.str(),true,false,false,CL_normal);
				}
				prevexp_ = exp_;
				
				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
				key_ = waitkeyinput(true);
				if(key_ != 'y') {
					break;
				}
				//-----------------------------------------------짐승길--------------------------------------------------

				for(int i = DEPTH_LEVEL; i <= DEPTH_LAST_LEVEL; i++)
				{
					create_and_kill(i);
				}

				exp_ = you.exper;
				{
					ostringstream oss;
					oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
						PlaceHolderHelper(LOC_SYSTEM_DUNGEON_DEPTH),
						PlaceHolderHelper(to_string(you.level)),
						PlaceHolderHelper(to_string(exp_-prevexp_)));
					printlog(oss.str(),true,false,false,CL_normal);
				}
				prevexp_ = exp_;
				
				printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
				key_ = waitkeyinput(true);
				if(key_ != 'y') {
					break;
				}

				random_extraction<int> rand_ext;
				rand_ext.push(0);
				rand_ext.push(1);
				rand_ext.push(2);
				
				bool end_ = false;
				while(rand_ext.GetSize() > 0) {
					int pop_ = rand_ext.pop();
					switch (pop_) {
						default:
							break;
						case 0:
						{
							//-----------------------------------------------달도시--------------------------------------------------

							create_and_kill(DREAM_LEVEL);
							create_and_kill(MOON_LEVEL);

							exp_ = you.exper;
							{
								ostringstream oss;
								oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
									PlaceHolderHelper(LOC_SYSTEM_DUNGEON_MOON),
									PlaceHolderHelper(to_string(you.level)),
									PlaceHolderHelper(to_string(exp_-prevexp_)));
								printlog(oss.str(),true,false,false,CL_normal);
							}
							prevexp_ = exp_;
							
							printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
							key_ = waitkeyinput(true);
							if(key_ != 'y') {
								end_ =  true;
								break;
							}
							break;
						}
						case 1:
						{
							//-----------------------------------------------지저--------------------------------------------------

							for(int i = SUBTERRANEAN_LEVEL; i < SUBTERRANEAN_LEVEL_LAST_LEVEL; i++)
							{
								create_and_kill(i, 0.5f); //절반정도 정리?
							}
							create_and_kill(SUBTERRANEAN_LEVEL_LAST_LEVEL);

							exp_ = you.exper;
							{
								ostringstream oss;
								oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
									PlaceHolderHelper(LOC_SYSTEM_DUNGEON_SUBTERRANEAN),
									PlaceHolderHelper(to_string(you.level)),
									PlaceHolderHelper(to_string(exp_-prevexp_)));
								printlog(oss.str(),true,false,false,CL_normal);
							}
							prevexp_ = exp_;
							
							printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
							key_ = waitkeyinput(true);
							if(key_ != 'y') {
								end_ =  true;
								break;
							}
							break;
						}
						case 2:
						{
							//-----------------------------------------------마계--------------------------------------------------
							int allrune_ = 3;
							while(allrune_)
							{
								env[PANDEMONIUM_LEVEL].ClearFloor();
								env[PANDEMONIUM_LEVEL].make = false;
								if(randA(3)==1) {
									allrune_--;
								} else {
									create_and_kill(PANDEMONIUM_LEVEL, 0.2f); //아주조금만 정리하고 진행
								}
							}
							create_and_kill(PANDEMONIUM_LEVEL+1, 0.8f);
							create_and_kill(PANDEMONIUM_LEVEL+2, 0.8f);
							create_and_kill(PANDEMONIUM_LEVEL+3, 0.8f);

							exp_ = you.exper;
							{
								ostringstream oss;
								oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
									PlaceHolderHelper(LOC_SYSTEM_DUNGEON_PANDEMONIUM),
									PlaceHolderHelper(to_string(you.level)),
									PlaceHolderHelper(to_string(exp_-prevexp_)));
								printlog(oss.str(),true,false,false,CL_normal);
							}
							prevexp_ = exp_;
							
							printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_DUNGEON_CONTINUE) + "(y/n)",true,false,false,CL_help);
							key_ = waitkeyinput(true);
							if(key_ != 'y') {
								end_ =  true;
								break;
							}
							break;
						}
					}
				}
				if(end_)
					break;


				//-----------------------------------------------하쿠레이--------------------------------------------------
				for(int i = HAKUREI_LEVEL; i <= HAKUREI_LAST_LEVEL; i++)
				{
					create_and_kill(i);
				}

				exp_ = you.exper;
				{
					ostringstream oss;
					oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_DUNGEON_CLEAR,
						PlaceHolderHelper(LOC_SYSTEM_DUNGEON_HAKUREI),
						PlaceHolderHelper(to_string(you.level)),
						PlaceHolderHelper(to_string(exp_-prevexp_)));
					printlog(oss.str(),true,false,false,CL_normal);
				}
				prevexp_ = exp_;
				
				//끝!!
			}
			break;
		case 'B':
			god_punish(you.god);
			break;
		case 'e':
		{
			ostringstream oss;
			oss << LocalzationManager::formatString(LOC_SYSTEM_DEBUG_CURRENT_POSITION,
				PlaceHolderHelper(to_string(you.position.x)),
				PlaceHolderHelper(to_string(you.position.y)));
			printlog(oss.str(), true, false, false, CL_magic);
			break;
		}
		case '?'://도움말

			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			printsub("                                   --- " + LocalzationManager::locString(LOC_SYSTEM_DEBUG_COMMAND_HELP) + " ---",true,CL_normal);
			printsub("",true,CL_normal);
			for(TextHelper text_ : LocalzationManager::getHelpWizard()) {
				printsub(text_.text,text_.enter,text_.color);
			}
			changedisplay(DT_SUB_TEXT);
			ReleaseMutex(mutx);
			continue;
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_COMMAND_UNKNOWN),true,false,false,CL_help);
			break;
		}
	return;
	}
}

