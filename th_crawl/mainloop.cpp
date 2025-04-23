//////////////////////////////////////////////////////////////////////////////////////////////////
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
#include "steam_api.h"
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


string getDefaultLang() {
	string lang = option_mg.getLang();
    std::transform(lang.begin(), lang.end(), lang.begin(), ::toupper);

	if(!lang.empty()) {
		return lang;
	} else {
		return LocalzationManager::baseLang();
	}
}


void init_localization() {
	LocalzationManager::initLocalization();
	LocalzationManager::init(LocalzationManager::baseLang(), true);
	string defaultLang = getDefaultLang();
	if(defaultLang != LocalzationManager::baseLang()) {
		LocalzationManager::init(defaultLang, false);
	}
}



void charter_selete()
{//인간,마법사,요정,카라스텐구,백랑텐구,캇파,반요,츠구모가미,흡혈귀,오니,사신, 달토끼, 천인, 용궁의사자, 유 령, 망령, 소령
	for(int i = 0; i<MAXLEVEL; i++)
		env[i].floor = i;
	
	bool isSteamInit = steam_mg.steamInit();

	WaitForSingleObject(mutx, INFINITE);
	SetText() = LocalzationManager::locString(LOC_SYSTEM_TITLE_TOUHOUCRAWL);
	SetText() += " ";
	SetText() += version_string;
	SetText() += "\n";
	SetText() += LocalzationManager::locString(LOC_SYSTEM_TITLE_SHORTINFO);
	SetText() += "\n\n";
	string user_name = steam_mg.getSteamUserName();
	steam_mg.setCurrentMainMenuInfo();
	if (user_name.size() != 0)
	{
		you.user_name = user_name;
	}

	SetText() += LocalzationManager::formatString(LOC_SYSTEM_TITLE_YOUR_NAME, PlaceHolderHelper(you.user_name));
	SetText() += "\n";
	SetText() += LocalzationManager::locString(isSteamInit?LOC_SYSTEM_STEAM_INIT_SUCCESS:LOC_SYSTEM_STEAM_INIT_FAIL);
	SetText() += "\n";

	SetDisplayTexture(&img_title);
	ReleaseMutex(mutx);
	waitkeyinput();	
	WaitForSingleObject(mutx, INFINITE);
	SetText() += LocalzationManager::locString(LOC_SYSTEM_TITLE_START);
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
		steam_mg.setCurrentInfo();
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
		steam_mg.setCurrentInfo();
	}
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
		steam_mg.setCurrentInfo();
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
		steam_mg.setCurrentInfo();
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

void search_monspell_view(monster* mon_);
void iteminfor_(int key_, bool gameover);
bool weapon_prev_fail();
bool armor_prev_fail();
bool jewelry_prev_fail();
bool pickup_prev_fail(bool no_speak);
bool throw_prev_fail(bool no_speak);
bool drink_prev_fail();
bool read_prev_fail();
bool eat_prev_fail();
bool evoke_prev_fail();
void Memorize_book(int key_);
void drink_logic(int key_);
void Reading_logic(int key_);
void evoke_logic(int key_, char auto_);
void auto_tanmac_onoff();
void PickUpSelect_logic(list<item>::iterator& it);

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
		InputedKey inputedKey;
		int char_ = waitkeyinput(inputedKey);

		you.prev_hp[1] = you.GetHp();
		you.prev_mp[1] = you.GetMp();


		switch(char_)
		{
		case -1:
			{
				if(inputedKey.mouse == MKIND_MAP) {
					coord_def target_pos(inputedKey.val1, inputedKey.val2);
					if(target_pos == you.position) {
						dungeon_tile_type tile_type = env[current_level].dgtile[you.position.x][you.position.y].tile;
						stair_kind stair_kind = env[current_level].getStairKind(target_pos.x, target_pos.y);

						bool unable_pickup = pickup_prev_fail(true);
						int pick_num=0;
						list<item>::iterator it;
						for(it = env[current_level].item_list.begin();it != env[current_level].item_list.end();)
						{
							list<item>::iterator temp = it++;
							if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
							{
								if(isPick(&(*temp)))
								{
									pick_num++;
								}
							}
							else if(pick_num)
								break;
						}

						//우선순위(아이템>계단>신전>1턴휴식)
						if(!unable_pickup && pick_num > 0) {
							PickUp();
						} else if(stair_kind != STAIR_KIND_NOT_STAIR) {
							switch(stair_kind) {
							case STAIR_KIND_DOWN_BASE:
							case STAIR_KIND_DOWN_SPECIAL:
								Stair_move(true);
								break;
							case STAIR_KIND_UP_BASE:
							case STAIR_KIND_UP_SPECIAL:
								Stair_move(false);
								break;
							default:
								break;
							}
						}
						else if(tile_type >= DG_TEMPLE_FIRST && tile_type <= DG_TEMPLE_LAST)
						{ 
							Pray();
						} else {
							action_turn_skip();
						}
					}
					else if(env[current_level].insight_mon(MET_ENEMY) || you.s_confuse || you.s_dimension || you.resetLOS() == IT_MAP_DANGER) {
						//한칸씩 이동 
						beam_iterator beam(you.position,target_pos);
						if(CheckThrowPath(you.position,target_pos,beam, true)) {
							beam.init();
							int target_abs_ = (target_pos - you.position).abs();
							int abs_ = ((*beam) - you.position).abs();
							bool unable_throw = throw_prev_fail(true);
							if(env[current_level].isMonsterPos(target_pos.x,target_pos.y,&you) 
							 && you.useMouseTammac > 0
							 && !unable_throw 
							 && you.throw_weapon
							 && (target_abs_ > 2 || you.useMouseTammac == 1) ) {
								Quick_Throw(you.GetThrowIter(),you.GetTargetIter(), true);
							} else if(abs_ == 1 || abs_ == 2) {
								action_Move(0, (*beam));
							} else {
								printlog(LocalzationManager::formatString(LOC_SYSTEM_DEBUG_POSITION_BUG,
								   PlaceHolderHelper(to_string(you.position.x)),
								   PlaceHolderHelper(to_string(you.position.y)),
								   PlaceHolderHelper(to_string((*beam).x)),
								   PlaceHolderHelper(to_string((*beam).y))) ,true,false,false,CL_danger);
							}
						}
					} else {
						Long_Move(coord_def(inputedKey.val1, inputedKey.val2));
					}
				} else if (inputedKey.mouse == MKIND_MAP_DESCRIPTION) {
					coord_def target_pos(inputedKey.val1, inputedKey.val2);
					if(unit *unit_ = env[current_level].isMonsterPos(target_pos.x,target_pos.y, &you))
					{
						if(!unit_->isplayer() && unit_->isView() && env[current_level].isInSight(target_pos))
						{
							search_monspell_view((monster*)unit_);
							changedisplay(DT_GAME);
						}
					} else {
						//아이템 있는지 확인
						list<item>::iterator last = env[current_level].item_list.end();
						list<item>::iterator it;

						for(it = env[current_level].item_list.begin(); it != env[current_level].item_list.end();it++)
						{
							if(it->position == target_pos) {
								last = it;
							} else if(last != env[current_level].item_list.end()) {
								break;
							}
						}
						
						if(last != env[current_level].item_list.end()) {
							iteminfor_(&(*last), true);
							changedisplay(DT_GAME);
						}
					}
				} else if (inputedKey.mouse == MKIND_ITEM) {
					int key_ = inputedKey.val1;
					item *item_ = you.GetItem(key_);
					if(item_)
					{
						if(item_->isSimpleType(ITMS_WEAPON))
						{
							if(weapon_prev_fail())
							{
								return;
							}
							//무기->장착
							else if(you.isequip(item_)>0) {
								you.unequip(ET_WEAPON);
							} else {
								you.equip(key_,ET_WEAPON);
							}
						}
						else if(item_->isSimpleType(ITMS_ARMOR)) {
							//방어구->장착
							if(armor_prev_fail()) {
								break;
							}
							else if(you.isequip(item_)>0) {
								you.unequiparmor(key_);
							}
							else {
								you.equiparmor(key_);
							}
						}
						else if(item_->isSimpleType(ITMS_JEWELRY)) {
							//목걸이,반지->장착
							//충전된 목걸이는 발동
							if(item_->type == ITM_AMULET && 
								you.equipment[ET_NECK] == item_ &&
								isCanEvoke((amulet_type)(*item_).value1) &&
								you.getAmuletPercent()) {
								evoke_logic(key_, 0);
								break;
							}
							if(jewelry_prev_fail()) {
								break;
							}
							else if(you.isequip(item_)>0) {
								you.unequipjewerly(key_);
							}
							else {
								you.equipjewerly(key_);
							}
						}
						else if(item_->isSimpleType(ITMS_THROW)) {
							//탄막->주탄막으로 교체
							if(you.throw_weapon == item_) {
								you.throw_weapon = nullptr;
							} else {
								you.throw_weapon = item_;
							}
						}
						else if(item_->isSimpleType(ITMS_POTION)) {
							//포션->마시기
							if(drink_prev_fail()) {
								break;
							}
							else {
								drink_logic(key_);
							}
						}
						else if(item_->isSimpleType(ITMS_BOOK)) {
							//책->읽기
							if(read_prev_fail()) {
								break;
							} else{
								Memorize_book(key_);
								changedisplay(DT_GAME);
							}
						} else if(item_->isSimpleType(ITMS_SCROLL)) {
							//두루마리->읽기
							if(read_prev_fail()) {
								break;
							} else{
								Reading_logic(key_);
							}
						} else if(item_->isSimpleType(ITMS_FOOD)) {
							//음식->먹기
							if(eat_prev_fail()) {
								break;
							} else{
								you.Eat(key_);
							}
						} else if(item_->isSimpleType(ITMS_SPELL)) {
							//스펠카드->발동
							if(evoke_prev_fail()) {
								break;
							} else{
								evoke_logic(key_, 0);
							}
						} else if(item_->isSimpleType(ITMS_MISCELLANEOUS)) {
							//발동템
							if(evoke_prev_fail()) {
								break;
							} else{
								evoke_logic(key_, 0);
							}
						}
					}
				} else if (inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
					int key_ = inputedKey.val1;
					iteminfor_(key_, false);
					changedisplay(DT_GAME);
				} else if(inputedKey.mouse == MKIND_SYSTEM) {
					int key_ = inputedKey.val1;
					switch(key_) {
						case SYSCMD_AUTOTRAVEL:
							auto_Move();
							break;
						case SYSCMD_AUTOATTACK:
							auto_battle();
							break;
						case SYSCMD_100REST:
							long_rest();
							break;
						case SYSCMD_MAGIC:
							SpellUse(0, 0);
							break;
						case SYSCMD_SKILL:						
							SkillUse(0);
							break;
						case SYSCMD_SHOUT:
							shout(0);
							break;
						case SYSCMD_SKILL_VIEW:
							skill_view();
							break;
						case SYSCMD_AUTOPICKUP:
							auto_pick_onoff(false);
							break;
						case SYSCMD_AUTOTANMAC:
							auto_tanmac_onoff();
							break;
						case SYSCMD_HELP:
							Help_Show();
							break;
						case SYSCMD_QUIT:
							saveandcheckexit();
							break;
						default: 
							break;
					}

				} else if (inputedKey.mouse == MKIND_PICK  || inputedKey.mouse == MKIND_PICK_DESCRIPTION) {
					if(inputedKey.mouse == MKIND_PICK && pickup_prev_fail(false)) {
						break;
					}

					int key_ = inputedKey.val1;
					list<item>::iterator it;

					for(it = env[current_level].item_list.begin(); it != env[current_level].item_list.end();it++)
					{
						if(it->position == you.position) {
							if(key_ == 0) {
								break;
							} else {
								key_--;
							}
						}
					}
					if(it != env[current_level].item_list.end()) {
						if(inputedKey.mouse == MKIND_PICK) {
							PickUpSelect_logic(it);
						}
						else if(inputedKey.mouse == MKIND_PICK_DESCRIPTION) {
							iteminfor_(&(*it), true);
							changedisplay(DT_GAME);
						}
					}
				}
				//마우스
			}
			break;
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
		case '_': //스팀 디버깅
			steam_mg.debugText();
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

bool g_changefullscreen = false;

bool option_menu(int value_)
{
	char blank[32];
	sprintf_s(blank,32,"            ");

	string lang = LocalzationManager::current_lang;
	LOCALIZATION_ENUM_KEY display = option_mg.getFullscreen()?LOC_SYSTEM_OPTION_MENU_FULLSCREEN:LOC_SYSTEM_OPTION_MENU_WINDOWED;
	LOCALIZATION_ENUM_KEY origin_display = display;  
	int width_ = option_mg.getWidth();
	int height_ = option_mg.getHeight();
	int origin_w = width_, origin_h = height_;
	int current_pos_ = option_mg.getCurrentPos();
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
		printsub("a - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_LANGUAGE) + ": " + LocalzationManager::langString(lang),true,CL_normal,'a');
		printsub("b - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_RESOLUTION) + ": " + to_string(width_) +" X " +  to_string(height_),true,CL_normal,'b');
		printsub("c - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_DISPLAY) + ": " + LocalzationManager::locString(display),true,CL_normal,'c');
		printsub("",true,CL_normal);
		printsub("esc - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_BACK),true,CL_normal,VK_ESCAPE);
		
		changedisplay(DT_SUB_TEXT);
		InputedKey inputedKey;
		int input_ = waitkeyinput(inputedKey,true);

		if(input_ >= 'a' && input_ <= 'c')
		{
			if(input_ == 'a') {
				lang = LocalzationManager::getNextLang(lang);
			}
			else if(input_ == 'b') {
				auto next_resolution = option_mg.getNextScreen(current_pos_);
				width_ = next_resolution.width;
				height_ = next_resolution.height;
			}
			else if(input_ == 'c') {
				display = (display==LOC_SYSTEM_OPTION_MENU_WINDOWED)?LOC_SYSTEM_OPTION_MENU_FULLSCREEN:LOC_SYSTEM_OPTION_MENU_WINDOWED;
			}
		}
		else if(input_ == VK_ESCAPE || (input_ == -1 && inputedKey.isRightClick()))
		{
			if(lang != LocalzationManager::current_lang) {
				LocalzationManager::init(LocalzationManager::baseLang(), true);
				if(lang != LocalzationManager::baseLang()) {
					LocalzationManager::init(lang, false);
				}
				option_mg.setLang(lang);
			}
			bool should_reload = false;
			if( origin_w != width_ || origin_h != height_) {
				option_mg.setWidth(width_);
				option_mg.setHeight(height_);
				option_mg.calcTileXY();
				should_reload = true;
			}
			if(origin_display != display) {
				should_reload = true;
			}
			if(should_reload) {
				if(display == LOC_SYSTEM_OPTION_MENU_FULLSCREEN) {
					option_mg.setFullscreen(true);
					g_changefullscreen = true;
	
				}else if(display == LOC_SYSTEM_OPTION_MENU_WINDOWED) {
					option_mg.setFullscreen(false);
					g_changefullscreen = true;
				}
			}

			
			break;
		}
		else if(input_ == -1) {
		}

	}
	changedisplay(DT_TEXT);

	return false;
}