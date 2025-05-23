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
#include "joypad.h"
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

const char *version_string = "ver1.1";
extern int g_tile_size;

void Initialize();


void SetJobs(job_type select_, unique_starting_type type);
void TouhouPlayerble(unique_starting_type type, bool aptit_);
void rightmenu_control();
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
vector<int> g_selected;



bool tutorials(int value_);
bool sprint1s(int value_);
bool sprint2s(int value_);
bool select_named(int value_);
bool select_char(int value_);
bool select_fairy(int value_);
bool select_job(int value_);

void charter_selete(bool first)
{//인간,마법사,요정,카라스텐구,백랑텐구,캇파,반요,츠구모가미,흡혈귀,오니,사신, 달토끼, 천인, 용궁의사자, 유 령, 망령, 소령
	for(int i = 0; i<MAXLEVEL; i++)
		env[i].floor = i;
	
	bool isSteamInit = steam_mg.isInit();

	if(first){
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
		changedisplay(DT_TEXT);
		ReleaseMutex(mutx);
		waitkeyinput();	
		WaitForSingleObject(mutx, INFINITE);
		SetText() += LocalzationManager::locString(LOC_SYSTEM_TITLE_START);
		SetText() += "\n";
		ReleaseMutex(mutx);
		Sleep(500);
		SetDisplayTexture(NULL);
	} else {
		steam_mg.setCurrentMainMenuInfo();
	}
	

	
	init_state();
	MapNode::initMapNode();
	map_list.tutorial = GM_TITLE;

	if(!ReplayClass.play)
	{
		g_selected.clear();
		g_selected.assign(4, 0);
		start_mainmenu();
		if(game_over) {
			return;
		}
		if(!saveexit) {
			ReplayClass.init_class(g_selected);
			ReplayClass.SaveReplayStart();
		}
	} else {
		game_over = false;
		switch(ReplayClass.infor.starting[0]) {
			case 'b':
				tutorials(0);
				break;
			case 'c':
				sprint1s(0);
				break;
			case 'd':
				sprint2s(0);
				//1안씀
				if(ReplayClass.infor.starting[1] == 'b') { //직접픽
					select_char(ReplayClass.infor.starting[2]);
					select_job(ReplayClass.infor.starting[3]);

				} else { //'a'와 기본
					select_named(ReplayClass.infor.starting[2]);
					if(ReplayClass.infor.starting[2] == 7) { //삼월정
						select_fairy(ReplayClass.infor.starting[3]);
					}
				}
				break;
			case 'a'://메인게임
			default:
				if(ReplayClass.infor.starting[1] == 'b') { //직접픽
					select_char(ReplayClass.infor.starting[2]);
					select_job(ReplayClass.infor.starting[3]);

				} else { //'a'와 기본
					select_named(ReplayClass.infor.starting[2]);
					if(ReplayClass.infor.starting[2] == 7) { //삼월정
						select_fairy(ReplayClass.infor.starting[3]);
					}
				}
				break;
		}
	}
	init_replay_log();

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
		LOG_MESSAGE("게임시작!");
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
void stand_action();
void search_monspell_view(monster* mon_);
bool iteminfor_(int key_, bool gameover);
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

bool useAutoTanmac(unit* mon_) {
	if(mon_ == nullptr)
		return false;

	if(!mon_->isEnemyUnit(&you) || mon_->isPassedBullet(&you))
		return false;

	int target_abs_ = (mon_->position - you.position).abs();
	bool unable_throw = throw_prev_fail(true);
	beam_iterator beam(you.position,mon_->position);
	bool cantShoot = true;
	bool canSuicide = you.throw_weapon?(you.throw_weapon->value4 == TMT_KIKU_COMPRESSER):false;
	if(you.useMouseTammac > 0
	 && !unable_throw 
	 && you.throw_weapon
	 && (target_abs_ > 2 || (you.useMouseTammac == 1 && !canSuicide)) 
	 && CheckThrowPath(you.position,mon_->position, beam, false) ) {
		cantShoot = false;
		beam.init();
		while(!beam.end())
		{
			if(monster *unit_ = (monster*)env[current_level].isMonsterPos(beam->x,beam->y, &you))
			{
				if(unit_->isUserAlly() && !unit_->isPassedBullet(&you))						
					cantShoot = true;
				break;
			}
			beam++;
		}
		if(!cantShoot) {
			you.target = ((monster*)mon_)->map_id;
			Quick_Throw(you.GetThrowIter(),you.GetTargetIter(), true);
			return true;
		}
	} 
	return false;
}

void scrollup(bool down) {
	vector<int> ablesize = {23,32,47,64,95,128};


	bool next_ = false;
	if(!down) {
		for(int i = 0; i < ablesize.size();i++) {
			if(g_tile_size == ablesize[i]) {
				next_ = true;
			} else if(next_) {
				int sight_x = option_mg.getTileMaxX();
				int sight_y = option_mg.getTileMaxY();
				float calc_tile_scale = ablesize[i]/32.0f;
				sight_x = (int)(sight_x/calc_tile_scale);
				sight_y = (int)(sight_y/calc_tile_scale+0.3f);
				if(sight_x >= 3 && sight_y >= 3) {
					g_tile_size = ablesize[i];
				}
				break;
			}
		}
	} else {
		for(int i = ablesize.size()-1; i >= 0;i--) {
			if(g_tile_size == ablesize[i]) {
				next_ = true;
			} else if(next_) {
				g_tile_size = ablesize[i];
				break;
			}
		}


	}
}
extern bool shift_check;
extern bool ctrl_check;
extern int replay_speed;
extern int map_effect;
extern bool widesearch;
extern display_manager DisplayManager;
void init_alldata() {
	WaitForSingleObject(mutx, INFINITE);
	//map_list.random_number = (unsigned long)time(NULL);
	//init_nonlogic_seed((unsigned long)time(NULL));
	//srand((unsigned int)map_list.random_number);

	you.init();
	for(int i = 0; i < MAXLEVEL; i++) {
		env[i].init();
	}
	current_level=0;
	unique_list.clear();
	save_note.note_list.clear();
	wiz_list.wizard_mode = false;
	shift_check = false;
	ctrl_check = false;
	widesearch = false;
	saveexit = false;
	map_effect = 0;
	replay_speed = 1;
	//불필요할수있지만 깔끔하게 하기위해서

	iden_list = Iden_collect(); 
	int temp = map_list.random_number;
 	map_list = map_infor();	
	ReplayClass.replay_string = L"";
	map_list.random_number = temp;
	unique_list.clear();
	DisplayManager.initText();
	game_over = false;
	changedisplay(DT_TEXT);
	ReleaseMutex(mutx);
}


void ForMouseClick(MOUSE_KIND mouse_type, int val1, int val2) {
	if(mouse_type == MKIND_MAP) {
		coord_def target_pos(val1, val2);
		if(target_pos == you.position) {
			stand_action();
		}
		else if(env[current_level].insight_mon(MET_ENEMY) || you.s_confuse || you.s_dimension || you.resetLOS() == IT_MAP_DANGER) {
			//한칸씩 이동 
			beam_iterator beam(you.position,target_pos);
			if(CheckThrowPath(you.position,target_pos,beam, true)) {
				beam.init();
				unit *mon_ = env[current_level].isMonsterPos(target_pos.x,target_pos.y,&you);
				int abs_ = ((*beam) - you.position).abs();
				if(useAutoTanmac(mon_)) {
					//do nothing
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
			int abs_ = (target_pos - you.position).abs();
			if(abs_ == 1 || abs_ == 2) {
				beam_iterator beam(you.position,target_pos);
				if(CheckThrowPath(you.position,target_pos,beam, true)) {
					beam.init();
					action_Move(0, (*beam));
				}
				else {
					Long_Move(coord_def(val1, val2), false);
				}
			} else {
				Long_Move(coord_def(val1, val2), false);
			}
		}
	} else if (mouse_type == MKIND_MAP_DESCRIPTION) {
		coord_def target_pos(val1, val2);
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
	} else if (mouse_type == MKIND_ITEM) {
		int key_ = val1;
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
					return;
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
					return;
				}
				if(jewelry_prev_fail()) {
					return;
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
					return;
				}
				else {
					drink_logic(key_);
				}
			}
			else if(item_->isSimpleType(ITMS_BOOK)) {
				//책->읽기
				if(read_prev_fail()) {
					return;
				} else{
					Memorize_book(key_);
					changedisplay(DT_GAME);
				}
			} else if(item_->isSimpleType(ITMS_SCROLL)) {
				//두루마리->읽기
				if(read_prev_fail()) {
					return;
				} else{
					Reading_logic(key_);
				}
			} else if(item_->isSimpleType(ITMS_FOOD)) {
				//음식->먹기
				if(eat_prev_fail()) {
					return;
				} else{
					you.Eat(key_);
				}
			} else if(item_->isSimpleType(ITMS_SPELL)) {
				//스펠카드->발동
				if(evoke_prev_fail()) {
					return;
				} else{
					evoke_logic(key_, 0);
				}
			} else if(item_->isSimpleType(ITMS_MISCELLANEOUS)) {
				//발동템
				if(evoke_prev_fail()) {
					return;
				} else{
					evoke_logic(key_, 0);
				}
			}
		}
	} else if (mouse_type == MKIND_ITEM_DESCRIPTION) {
		int key_ = val1;
		iteminfor_(key_, false);
		changedisplay(DT_GAME);
	} else if(mouse_type == MKIND_SYSTEM) {
		int key_ = val1;
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
				SimpleSpellUse();
				break;
			case SYSCMD_SKILL:
				SkillUse(0);
				break;
			case SYSCMD_SHOUT:
				shout(0);
				break;
			case SYSCMD_DOOR_OPENCLOSE:
				Open_Close_door();
				break;
			case SYSCMD_PRAY:
				Pray();
				break;
			case SYSCMD_MORE_ITEM:
				More_Item_Action();
				break;
			case SYSCMD_AUTOPICKUP:
				auto_pick_onoff(false);
				break;
			case SYSCMD_AUTOTANMAC:
				auto_tanmac_onoff();
				break;
			case SYSCMD_WIDE_SEARCH:
				Wide_Search();
				break;
			case SYSCMD_SKILL_VIEW:
				skill_view();
				break;
			case SYSCMD_MORE_VIEW:
				More_Information_List();
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

	} else if (mouse_type == MKIND_PICK  || mouse_type == MKIND_PICK_DESCRIPTION) {
		if(mouse_type == MKIND_PICK && pickup_prev_fail(false)) {
			return;
		}

		int key_ = val1;
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
			if(mouse_type == MKIND_PICK) {
				PickUpSelect_logic(it);
			}
			else if(mouse_type == MKIND_PICK_DESCRIPTION) {
				iteminfor_(&(*it), true);
				changedisplay(DT_GAME);
			}
		}
	} else if (mouse_type == MKIND_SCROLL_UP) {
		scrollup(false);
	} else if (mouse_type == MKIND_SCROLL_DOWN) {
		scrollup(true);
	}
}





void MainLoop()
{
	while(1)
	{
		if(game_over == true) {
			//초기화 로직
			init_alldata();
			return;
		}

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
				ForMouseClick(inputedKey.mouse, inputedKey.val1, inputedKey.val2);
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
			scrollup(false);
			//VolumeUp();
			break;
		case '-':
			scrollup(true);
			//VolumeDown();
			break;
		case '#':
			if(Dump(0,NULL))
				printlog(LocalzationManager::locString(LOC_SYSTEM_DUMP_SUCCESS),true,false,false,CL_normal);
			break;
		case 'z':
			SimpleSpellUse();
			break;
		case 'Z':
			SpellUse(0, 0, false);
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
		case '0': //입력 디버깅
			getKeyboardInputString();
			enterlog();
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
		case GVK_BUTTON_A://패드 A
			stand_action();
			break;
		case GVK_BUTTON_A_LONG: //패드 A 길게
			long_rest();
			break;
		case GVK_BUTTON_B://패드 B
			escape();
			break;
		case GVK_BUTTON_B_LONG: //패드 B 길게
			Wide_Search();
			break;
		case GVK_BUTTON_X://패드 X
			SimpleSpellUse();
			break;
		case GVK_BUTTON_X_LONG: //패드 X 길게
			SkillUse(0);
			break;
		case GVK_BUTTON_Y://패드 X
			rightmenu_control();
			break;
		case GVK_BUTTON_Y_LONG: //패드 X 길게
			iteminfor();
			break;
		case GVK_LEFT_BUMPER: //왼쪽 범퍼
			auto_battle();
			break;
		case GVK_RIGHT_BUMPER://오른쪽 범퍼
			auto_Move();
			break;
		case GVK_LT: //왼쪽 트리거
			scrollup(true);
			break;
		case GVK_RT://오른쪽 트리거
			scrollup(false);
			break;
		default:
			break;
		}
	}
}

bool g_changefullscreen = false;
extern display_manager DisplayManager;

bool loading_font(string font_name);

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
		printsub(blank,false,CL_warning);
		printsub("a - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_LANGUAGE) + ": " + LocalzationManager::langString(lang),true,CL_normal,'a');
		printsub(blank,false,CL_warning);
		printsub("b - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_RESOLUTION) + ": " + to_string(width_) +" X " +  to_string(height_),true,CL_normal,'b');
		printsub(blank,false,CL_warning);
		printsub("c - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_DISPLAY) + ": " + LocalzationManager::locString(display),true,CL_normal,'c');
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("esc - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_BACK),true,CL_normal,VK_ESCAPE);
		
		changedisplay(DT_SUB_TEXT);
		InputedKey inputedKey;
		int input_;
		while(1) {
			input_ = waitkeyinput(inputedKey,true);
			if(input_ == VK_UP)
				DisplayManager.addPosition(-1);
			else if(input_ == VK_DOWN)
				DisplayManager.addPosition(1);
			else if(input_ == VK_RETURN || input_ == GVK_BUTTON_A || input_ == GVK_BUTTON_A_LONG) {
				input_ = DisplayManager.positionToChar();
				break;
			} else {
				break;
			}
		}

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
		else if(input_ == VK_ESCAPE ||
		input_ == GVK_BUTTON_B ||
		input_ == GVK_BUTTON_B_LONG  || (input_ == -1 && inputedKey.isRightClick()))
		{
			if(lang != LocalzationManager::current_lang) {
				LocalzationManager::init(LocalzationManager::baseLang(), true);
				if(lang != LocalzationManager::baseLang()) {
					LocalzationManager::init(lang, false);
				}
				option_mg.setLang(lang);
				if(!LocalzationManager::getCurrentFont().empty()) {
					loading_font(LocalzationManager::getCurrentFont());
				}
				DisplayManager.Getfontinfor();
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
	changedisplay(DT_SUB_TEXT);

	return false;
}