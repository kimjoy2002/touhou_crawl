﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mainloop.h
//
// 내용: 주게임루프
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "environment.h"
#include "display.h"
#include "key.h"
#include "save.h"
#include "player.h"
#include "beam.h"
#include "monster_texture.h"
#include "map.h"
#include "dump.h"
#include "god.h"
#include "throw.h"
#include "skill_use.h"
#include "note.h"
#include "tribe.h"
#include "network.h"
#include "replay.h"
#include "mon_infor.h"
#include "mapsearching.h"
#include "soundmanager.h"
#include "localization.h"

#include "option_manager.h"




extern bool saveexit;

extern HANDLE mutx;

const char *version_string = "ver1.0";


void Initialize();


void SetJobs(job_type select_, unique_starting_type type);
void TouhouPlayerble(unique_starting_type type, bool aptit_);
skill_type itemtoskill(item_type type_);


void Test_char_init(item_type item_, int bonus)
{

	item_infor t;

	t.type = item_;
	t.num = 1;
	t.curse = false;
	t.value3 = (int)(bonus == 6);
	t.value4 = (int)(bonus == 6);
	t.is_pile = false;
	t.name2 = name_infor(LOC_NONE);
	switch(item_)
	{
	case ITM_WEAPON_SHORTBLADE:
		t.value1 = 4;
		t.value2 = 7;
		t.value5 = 0;
		t.value6 = 0;
		t.value7 = 10;
		t.value8 = 5;
		t.can_throw = true;
		t.image = &img_item_weapon_dagger;
		t.name = name_infor(LOC_SYSTEM_ITEM_WEAPON_SHORTBLADE_DAGGER);
		t.weight = 2.0f;
		t.value = 50;
		break;
	case ITM_WEAPON_AXE:	
		t.value1 = 2;
		t.value2 = 8;
		t.value5 = 0;
		t.value6 = 0;
		t.value7 = 13;
		t.value8 = 7;
		t.can_throw = true;
		t.image = &img_item_weapon_handaxe;
		t.name = name_infor(LOC_SYSTEM_ITEM_WEAPON_AXE_HANDAXE);
		t.weight = 3.0f;
		t.value = 60;
		break;
	case ITM_WEAPON_MACE:
		t.value1 = 4;
		t.value2 = 7;
		t.value5 = 0;
		t.value6 = 0;
		t.value7 = 13;
		t.value8 = 7;
		t.can_throw = false;
		t.image = randA(1)?&img_item_weapon_gohey:&img_item_weapon_gohey2;
		t.name = name_infor(LOC_SYSTEM_ITEM_WEAPON_MACE_GOHEI);
		t.weight = 3.0f;
		t.value = 60;
		break;
	case ITM_WEAPON_SPEAR:
		t.value1 = 2;
		t.value2 = 8;
		t.value5 = 12;
		t.value6 = 0;
		t.value7 = 13;
		t.value8 = 7;
		t.can_throw = true;
		t.image = &img_item_weapon_spear;
		t.name = name_infor(LOC_SYSTEM_ITEM_WEAPON_SPEAR_SPEAR);
		t.weight = 4.0f;
		t.value = 70;
		break;
	default:
		break;
	}
	item *it;
	if(item_ != ITM_LAST)
	{
		it = env[current_level].MakeItem(you.position,t);
		it->identify = true;
		it->identify_curse = true;
		you.additem(it,false);
		you.equip('a',ET_WEAPON,false);
		env[current_level].DeleteItem(it);
	}


	t.type = ITM_ARMOR_BODY_ARMOUR_0;
	t.num = 1;
	t.curse = false;
	t.value1 = 1;
	t.value2 = 0;
	t.value3 = 0;
	t.value4 = (int)(bonus == 6);
	t.value5 = 0;
	t.value6 = 0;
	t.is_pile = false;
	t.can_throw = false;
	t.image = &img_item_armor_robe;
	t.name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_MIKO, LOC_SYSTEM_ITEM_ARMOUR_M_ROBE);
	t.weight = 6.0f;
	t.value = 40;

	it = env[current_level].MakeItem(you.position,t);
	it->identify = true;
	it->identify_curse = true;
	you.additem(it,false);
	you.equiparmor(item_ != ITM_LAST?'b':'a',false);
	env[current_level].DeleteItem(it);

	t.type = ITM_FOOD;
	t.num = 1;
	t.curse = false;
	t.value1 = 1;
	t.value2 = 0;
	t.value3 = 0;
	t.value4 = 0;
	t.value5 = 100;
	t.value6 = 0;
	t.is_pile = true;
	t.can_throw = false;
	t.image = &img_item_food_bread;
	t.name = name_infor(LOC_SYSTEM_ITEM_FOOD_BREAD);
	t.weight = 5.0f;
	t.value = 30;
	it = env[current_level].MakeItem(you.position,t);
	you.additem(it,false);
	env[current_level].DeleteItem(it);

	switch(bonus)
	{
	case 1:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, 1));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, 1));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, 3));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.potion_list[PT_HEAL].iden = true;
		iden_list.potion_list[PT_HEAL_WOUND].iden = true;
		break;
	case 2:		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_MIGHT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_MIGHT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.potion_list[PT_MIGHT].iden = true;
		break;
	case 3:		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_HASTE));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.potion_list[PT_HASTE].iden = true;
		break;
	case 4:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_TELEPORT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_TELEPORT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_IDENTIFY));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.scroll_list[SCT_TELEPORT].iden = 3;
		iden_list.scroll_list[SCT_IDENTIFY].iden = 3;
		break;
	case 5:	
		it = env[current_level].MakeItem(you.position,makeitem(ITM_THROW_TANMAC, 0, &t, 30));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		break;	
	}


	skill_type s_type_ = (item_ != ITM_LAST)?itemtoskill(item_):SKT_UNWEAPON;


	you.GiveSkillExp(SKT_FIGHT,s_type_==SKT_SHORTBLADE?20:30,false);
	you.GiveSkillExp(s_type_,s_type_==SKT_UNWEAPON?80:s_type_==SKT_SHORTBLADE?30:45,false);
	if(bonus == 5)
		you.GiveSkillExp(SKT_TANMAC,70,false);
	you.GiveSkillExp(SKT_DODGE,50,false);
	if(s_type_==SKT_SHORTBLADE)
	{
		you.GiveSkillExp(SKT_STEALTH,30,false);
		//you.GiveSkillExp(SKT_BACKSTAB,30,false);
	}
}


void addItem_temp(item_type item_type_, int item_id, int num);
extern void start_mainmenu();


LOCALIZATION_TYPE getDefaultLang() {
	string lang = option_mg.getLang();
    std::transform(lang.begin(), lang.end(), lang.begin(), ::tolower);

	if(lang == "eng") {
		return LOCALIZATION_TYPE::LOCALIZATION_TYPE_ENG;
	}
	else if (lang == "kor") {
		return LOCALIZATION_TYPE::LOCALIZATION_TYPE_KOR;
	} else {
		return LOCALIZATION_TYPE::LOCALIZATION_TYPE_ENG;
	}
}


void init_localization() {
	LocalzationManager::init(LOCALIZATION_TYPE::LOCALIZATION_TYPE_DEFAULT, true);
	if(getDefaultLang() != LOCALIZATION_TYPE::LOCALIZATION_TYPE_DEFAULT) {
		LocalzationManager::init(getDefaultLang(), false);
	}
}



void charter_selete()
{//인간,마법사,요정,카라스텐구,백랑텐구,캇파,반요,츠구모가미,흡혈귀,오니,사신, 달토끼, 천인, 용궁의사자, 유 령, 망령, 소령
	for(int i = 0; i<MAXLEVEL; i++)
		env[i].floor = i;
	

	WaitForSingleObject(mutx, INFINITE);
	SetText() = LocalzationManager::locString(LOC_SYSTEM_TITLE_TOUHOUCRAWL);
	SetText() += " ";
	SetText() += version_string;
	SetText() += "\n";
	SetText() += LocalzationManager::locString(LOC_SYSTEM_TITLE_SHORTINFO);
	SetText() += "\n\n";
	string user_name = option_mg.getName();
	if (user_name.size() != 0)
	{
		you.user_name = user_name;
	}

	SetText() += LocalzationManager::formatString(LOC_SYSTEM_TITLE_YOUR_NAME, PlaceHolderHelper(you.user_name));
	SetText() += "\n";

	SetDisplayTexture(&img_title);
	ReleaseMutex(mutx);
	waitkeyinput();	
	WaitForSingleObject(mutx, INFINITE);
	SetText() += LocalzationManager::locString(LOC_SYSTEM_TITLE_SHORTINFO);
	SetText() += "\n";
	ReleaseMutex(mutx);
	Sleep(500);
	SetDisplayTexture(NULL);
	
	
	{
		ReplayClass.init_class();
		ReplayClass.SaveReplayStart();
	}
	
	init_state();
	MapNode::initMapNode();
	map_list.tutorial = GM_TITLE;

	start_mainmenu();

	if(!saveexit)
	{
		init_identify();
		init_monster();
		initMap();
		wiz_list.wizard_mode = 0;
	}
	else {
		printReEnter();
		env[current_level].playBgm();

	}
	if(map_list.tutorial == GM_TITLE)
		map_list.tutorial = GM_NORMAL;


	if(isNormalGame() && !saveexit)
	{
		AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_START,
			PlaceHolderHelper(you.user_name),
			PlaceHolderHelper(LocalzationManager::locString(tribe_type_string[you.tribe])),
			PlaceHolderHelper(LocalzationManager::locString(job_type_string[you.job])),
			PlaceHolderHelper(you.GetCharNameString())),CL_normal);

		SetTribe(you.tribe);
		TouhouPlayerble(you.char_type, true);
		SetJobs(you.job,you.char_type);
		TouhouPlayerble(you.char_type, false);
		/*Test_char_init(item_, bonus);*/
		you.CalcuHP();
		Initialize();
	}
	else if(map_list.tutorial == GM_TUTORIAL)
	{		
		you.image = &img_play_sanae;
		you.char_type = UNIQ_START_SANAE;
		you.tribe = TRI_HUMAN;
		you.job = JOB_SHAMAN;
		SetTribe(you.tribe);
		you.CalcuHP();
		deque<monster*> dq;
		env[current_level].EnterMap(0,dq);	
		printlog(LocalzationManager::locString(LOC_SYSTEM_TUTORIAL_START1),true,false,false,CL_warning);
		printlog(LocalzationManager::locString(LOC_SYSTEM_TUTORIAL_START2),true,false,false,CL_warning);
		printlog(LocalzationManager::locString(LOC_SYSTEM_TUTORIAL_START3),true,false,false,CL_warning);
	}
	// else if(map_list.tutorial == GM_TUTORIAL2)
	// {
	// 	you.image = &img_play_sanae;
	// 	you.char_type = UNIQ_START_SANAE;
	// 	you.tribe = TRI_HUMAN;
	// 	you.job = JOB_SHAMAN;
	// 	SetTribe(you.tribe);
	// 	you.CalcuHP();
	// 	deque<monster*> dq;
	// 	env[current_level].EnterMap(0,dq);	
	// 	printlog("안녕하세요. Dungeon Crawl Stone Soup (이하 돌죽) 팬게임 동방크롤입니다.",true,false,false,CL_warning);
	// 	printlog("여기에선 돌죽 경험자분을 위한 튜토리얼입니다.",true,false,false,CL_warning);
	// }
	else if(map_list.tutorial == GM_SPRINT1_AREANA)
	{
		you.image = &img_play_sanae;
		you.char_type = UNIQ_START_SANAE;
		you.tribe = TRI_HUMAN;
		you.job = JOB_SHAMAN;
		SetTribe(you.tribe);
		you.CalcuHP();
		deque<monster*> dq;
		env[current_level].EnterMap(0,dq);	
	
		item_infor t;
		item *it;
		it = env[current_level].MakeItem(you.position,makeitem(ITM_RING,1,&t,RGT_SEE_INVISIBLE));	
		it->Identify();
		you.additem(it,false);
		you.equip('a',ET_LEFT,false);
		env[current_level].DeleteItem(it);

		printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_START1),true,false,false,CL_help);
		printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_START2),true,false,false,CL_help);
	}
	else if (map_list.tutorial == GM_SPRINT2_MINISTAGE)
	{
		AddNote(you.turn, CurrentLevelString(), LocalzationManager::formatString(LOC_SYSTEM_NOTE_START,
			PlaceHolderHelper(you.user_name),
			PlaceHolderHelper(LocalzationManager::locString(tribe_type_string[you.tribe])),
			PlaceHolderHelper(LocalzationManager::locString(job_type_string[you.job])),
			PlaceHolderHelper(you.GetCharNameString())), CL_normal);

		SetTribe(you.tribe);
		TouhouPlayerble(you.char_type, true);
		SetJobs(you.job, you.char_type);
		TouhouPlayerble(you.char_type, false);
		/*Test_char_init(item_, bonus);*/
		you.CalcuHP();
		Initialize();

		addItem_temp(ITM_POTION, PT_HASTE, 1);
		addItem_temp(ITM_POTION, PT_MIGHT, 1);
		addItem_temp(ITM_POTION, PT_AGILITY, 1);
		addItem_temp(ITM_POTION, PT_HEAL_WOUND, 1);
		addItem_temp(ITM_POTION, PT_MAGIC, 1);
		addItem_temp(ITM_POTION, PT_HEAL, 2);

		addItem_temp(ITM_SCROLL, SCT_BLINK, 1);
		/*you.image = &img_play_sanae;
		you.char_name.name = "사나에";
		you.tribe = TRI_HUMAN;
		you.job = JOB_SHAMAN;
		SetTribe(you.tribe);
		you.CalcuHP();
		env[current_level].EnterMap(0, deque<monster*>());

		item_infor t;
		item *it;
		it = env[current_level].MakeItem(you.position, makeitem(ITM_RING, 1, &t, RGT_SEE_INVISIBLE));
		it->Identify();
		you.additem(it, false);
		you.equip('a', ET_LEFT, false);
		env[current_level].DeleteItem(it);*/
	}



	changedisplay(DT_GAME);
	saveexit = true;
}

void addItem_temp(item_type item_type_, int item_id, int num_)
{
	item_infor t;
	item *it;
	item_infor itme_ = makeitem(item_type_, 1, &t, item_id);
	itme_.num = num_;
	it = env[current_level].MakeItem(you.position, itme_);
	it->Identify();
	you.additem(it, false);
	//you.equip('a', ET_LEFT, false);
	env[current_level].DeleteItem(it);
}




void Initialize()
{
	deque<monster*> dq;
	env[current_level].EnterMap(0,dq);

	printlog(LocalzationManager::locString(LOC_SYSTEM_WELCOME_FIRST),true,false,false,CL_normal);
	//you.resetLOS(false);
	you.FairyRevive(false);
}


void MainLoop()
{
	while(1)
	{
		you.player_move = true;

		if(you.s_timestep)
		{
			turn_skip();
			Sleep(16);
			continue;
		}


		while (you.youMaxiExp) {
			enterlog();
			printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_MASTER), true, false, false, CL_normal);
			MoreWait();

			skill_view();
			you.youMaxiExp = false;
		}
		int char_ = waitkeyinput();

		you.prev_hp[1] = you.GetHp();
		you.prev_mp[1] = you.GetMp();


		switch(char_)
		{
		case 'k':
			action_Move('k', coord_def(you.position.x,you.position.y-1));  //위
			break;
		case 'j':
			action_Move('j', coord_def(you.position.x,you.position.y+1)); //아래
			break;
		case 'h':
			action_Move('h', coord_def(you.position.x-1,you.position.y)); //왼쪽
			break;
		case 'l':
			action_Move('l', coord_def(you.position.x+1,you.position.y)); //오른쪽
			break;
		case 'b':
			action_Move('b', coord_def(you.position.x-1,you.position.y+1));
			break;
		case 'n':
			action_Move('n', coord_def(you.position.x+1,you.position.y+1));
			break;
		case 'y':
			action_Move('y', coord_def(you.position.x-1,you.position.y-1));
			break;
		case 'u':
			action_Move('u', coord_def(you.position.x+1,you.position.y-1));
			break;
		case 'x': //주위탐색
			Search();
			break;
		case 's': //턴스킵
		case '.': //턴스킵
			action_turn_skip();
			break;
		case 'g':
		case ',': //줍기
			PickUp();
			break;
		case 'i': //아이템확인
			iteminfor();
			break;	
		case 'd': //아이템버리기
			iteminfor_discard();
			break;
		case 'D': //마지막에 먹은 아이템 버리기
			fast_discard();
			break;
		case 'w': //무기장착
			Equip_Weapon();
			break;
		case 'W': //방어구장착
			Equip_Armor();
			break;
		case 'T': //방어구해제
			Unequip_Armor();
			break;
		case 'C': //문닫기
			Close_door();
			break;
		case 'O': //문열기
			Open_door();
			break;
		case 'o': //자동이동
			auto_Move();
			break;
		case '5': //100턴넘기기
			long_rest();
			break;
		case 0x88: //컨트롤P - 로그
			view_log();
			break;
		case 15: //컨트롤o
			if(isNormalGame())
				dungeonView();
			break;
		case 'e': //먹기
			Eatting(0);
			break;
		case 'q': //마시기
			Drinking(0);
			break;
		case 'r': //읽기
			Reading(0);
			break;
		case 'm': //스킬정보창
			skill_view();
			break;
		case 'P': //장신구장착
			Equip_Jewelry();
			break;
		case 'R': //장신구해제
			Unequip_Jewelry();
			break;
		case 'S': //체크후 종료
			saveandcheckexit();
			break;
		case 0x07: //전체층 이동
			if (isNormalGame())
				floorMove();
			break;
		case 0x89: //강제종료
			nosaveandexit();
			break;
		case 0x8A: //저장과 종료
			saveandexit();
			break;
		case 'X': //넓은탐색
			Wide_Search();
			break;
		case 'f': //던지기(빠른)
			Quick_Throw(you.GetThrowIter(),you.GetTargetIter(), false);
			break;
		case 'F': //던지기(선택)
			Select_Throw();
			break;
		case '\\': //식별템 확인
			Iden_Show();
			break;
		case '>':
			Stair_move(true);
			break;
		case '<':
			Stair_move(false);
			break;
		case '%':
			stat_view();
			break;
		case '}':
			Weapon_Show();
			break;
		case '[':
			Armour_Show();
			break;
		case ']':
			rune_Show();
			break;
		case '\"':
			Amulet_Show();
			break;
		case '@':
			Simple_State_Show();
			break;
		case 'N':
			//sendScore();
			break;
		case 'E':
			Experience_Show();
			break;
		//case 'c':
		//	Spelllcard_Declare();
		//	//Eat_Power();
		//	break;
		case 'v':
		case 'V':
			Spelllcard_Evoke(0);
			break;
		case 'p':
			Pray();
			break;
		case '+':
			VolumeUp();
			break;
		case '-':
			VolumeDown();
			break;
		case '#':
			if(Dump(0,NULL))
				printlog(LocalzationManager::locString(LOC_SYSTEM_DUMP_SUCCESS),true,false,false,CL_normal);
			break;
		case 'Z':
		case 'z':
			SpellUse(0, 0);
			break;
		case 'I':
			SpellView();
			break;
		case 'a':
			SkillUse(0);
			break;
		case 'A':
			PropertyView();
			break;
		case 'M':
			run_spell();
			break;
		case 't':
			shout(0);
			break;
		case '^':
			God_show();
			break;
		case '\'':
			weapon_swap();
			break;
		case '&': //위자드모드!
			//waitkeyinput();
			wiz_mode();
			break;
		case '_':
			save_mode();
			break;
		case 0x8B:
			auto_pick_onoff(false);
			break;
		case '?'://도움말
			Help_Show();
			break;
		case VK_ESCAPE://esc
			escape();
			break;
		case VK_TAB:
			auto_battle();
			break;
		case '`':
			repeat_action();
			break;
		default:
			break;
		}
	}
}



bool option_menu(int value_)
{
	char blank[32];
	sprintf_s(blank,32,"            ");

	while(1)
	{
		deletesub();

		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("======",false,CL_help);
		printsub(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_OPTION),false,CL_help);
		printsub("======",true,CL_help);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub(LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_LANGUAGE),true,CL_normal);
		printsub("",true,CL_normal);
		printsub(LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_ESC),true,CL_normal);
		
		changedisplay(DT_SUB_TEXT);
		int input_ = waitkeyinput(true);

		if(input_ >= 'a' && input_ <= 'a')
		{
			if(input_ == 'a') {
				int cur = (int)LocalzationManager::current_lang;

				cur++;
				if(cur == LOCALIZATION_TYPE::LOCALIZATION_TYPE_MAX)  {
					cur = 0;
				}
				
				LocalzationManager::init(LOCALIZATION_TYPE::LOCALIZATION_TYPE_DEFAULT, true);
				if((LOCALIZATION_TYPE)cur != LOCALIZATION_TYPE::LOCALIZATION_TYPE_DEFAULT) {
					LocalzationManager::init((LOCALIZATION_TYPE)cur, false);
				}
				option_mg.setLang(getLocalizationString((LOCALIZATION_TYPE)cur));
			}
		}
		else if(input_ == VK_ESCAPE)
		{
			break;
		}

	}
	changedisplay(DT_TEXT);

	return false;
}