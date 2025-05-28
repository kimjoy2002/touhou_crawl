//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: action.cpp
//
// 내용: player의 행동들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <set>
#include <algorithm>
#include <iomanip>
#include "environment.h"
#include "display.h"
#include "localization.h"
#include "key.h"
#include "joypad.h"
#include "player.h"
#include "beam.h"
#include "mon_infor.h"
#include "monster_texture.h"
#include "tribe.h"
#include "dump.h"
#include "Astar.h"
#include "rect.h"
#include "potion.h"
#include "scroll.h"
#include "smoke.h"
#include "ring.h"
#include "map.h"
#include "skill_use.h"
#include "floor.h"
#include "projectile.h"
#include "spellcard.h"
#include "throw.h"
#include "rand_shuffle.h"
#include "option_manager.h"
#include "soundmanager.h"
#include "book.h"
#include "debuf.h"
#include "mapsearching.h"
#include "god.h"

#include <algorithm>
#include <random>
#include <iterator>
#include <ctime>
#include <iostream>

using namespace std;


extern HANDLE mutx;



int Player_Move(const coord_def &c);
bool stack_move(bool auto_);

extern display_manager DisplayManager;
bool widesearch = false;
bool sample_dimention = false;
extern int g_menu_select;
extern int greed_max_x;
extern int greed_max_y;

int action_Move(int command, const coord_def &c)
{
	if (you.search)
		return Search_Move(c, widesearch);
	else {
		if(command > 0) {
			you.SetPrevAction(command);
		}
		return Player_Move(c);
	}
}



int Move(const coord_def &c)
{
	if(you.search)
		return Search_Move(c,widesearch);
	else
		return Player_Move(c);
}




void Long_Move(const coord_def &c, bool speak_)
{
	while(!you.will_move.empty())
		you.will_move.pop();
	//이렇게 해도되려나?

	you.search = false;
	if(env[current_level].insight_mon(MET_ENEMY))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LOS_MON),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.s_confuse)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE_WARNING),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.s_dimension)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DIMENSTION),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.resetLOS() == IT_MAP_DANGER)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_MAP_DANGER),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(!PathSearch(you.position,c,you.will_move,ST_NORMAL,current_level,you.isFly(),you.isSwim()))
	{
		if(speak_)
			printlog(LocalzationManager::locString(LOC_SYSTEM_UNABLE_MOVE),true,false,false,CL_normal);	
	}
	stack_move(false);
}

void repeat_action()
{
	int key_ = you.prev_action_key.key;

	switch (key_)
	{
	case 'k':
		action_Move('k', coord_def(you.position.x, you.position.y - 1));  //위
		break;
	case 'j':
		action_Move('j', coord_def(you.position.x, you.position.y + 1)); //아래
		break;
	case 'h':
		action_Move('h', coord_def(you.position.x - 1, you.position.y)); //왼쪽
		break;
	case 'l':
		action_Move('l', coord_def(you.position.x + 1, you.position.y)); //오른쪽
		break;
	case 'b':
		action_Move('b', coord_def(you.position.x - 1, you.position.y + 1));
		break;
	case 'n':
		action_Move('n', coord_def(you.position.x + 1, you.position.y + 1));
		break;
	case 'y':
		action_Move('y', coord_def(you.position.x - 1, you.position.y - 1));
		break;
	case 'u':
		action_Move('u', coord_def(you.position.x + 1, you.position.y - 1));
		break;
	case 's': //턴스킵
		action_turn_skip();
		break;
	case 'D': //마지막에 먹은 아이템 버리기
		fast_discard();
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
	case 'e': //먹기
		Eatting(you.prev_action_key.item);
		break;
	case 'q': //마시기
		Drinking(you.prev_action_key.item);
		break;
	case 'r': //읽기
		Reading(you.prev_action_key.item);
		break;
	case 'f': //던지기
		Quick_Throw(you.GetThrowIter(), you.GetTargetIter(), true);  //TODO
		break;
	case 'v':
		Spelllcard_Evoke(you.prev_action_key.item); //TODO
		break;
	case 'p':
		Pray(); 
		break;
	case 'z':
		SpellUse(you.prev_action_key.item, you.prev_action_key.num, false); //TODO
		break;
	case 'a':
		SkillUse(you.prev_action_key.item); //TODO
		break;
	case 't':
		shout(you.prev_action_key.item); //TODO
		break;
	case '\'':
		weapon_swap(); //TODO
		break;
	case VK_TAB:
		auto_battle(); //TODO
		break;
	default:
		break;
	}
}

bool throw_prev_fail(bool no_speak);
bool useAutoTanmac(unit* mon_);
bool pickup_prev_fail(bool no_speak);

void stand_action()
{
	dungeon_tile_type tile_type = env[current_level].dgtile[you.position.x][you.position.y].tile;
	stair_kind stair_kind = env[current_level].getStairKind(you.position.x, you.position.y);

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
		if(isShootingSprint()){
			you.shooing_fire();
		}
		action_turn_skip();
	}
}


void auto_battle()
{
	if(!env[current_level].insight_mon(MET_ENEMY))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LOS_NOMON),true,false,false,CL_small_danger);
		return;
	}
	if(you.s_confuse)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE_WARNING),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.GetHp() <= you.GetDangerHp())
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_AUTOBATTLE_DANGERHP),true,false,false,CL_small_danger);
		return;
	}

	monster* mon_ = env[current_level].close_mon(you.position.x,you.position.y, MET_ENEMY);
	if(mon_)
	{
		if(useAutoTanmac(mon_)) {
			you.SetPrevAction(VK_TAB);
			return;
		}
		else {
			for(int i=RT_BEGIN;i!=RT_END;i++)
			{
				beam_iterator it(you.position,mon_->position,(round_type)i);
				if(env[current_level].dgtile[(*it).x][(*it).y].isMove(true,false,false))
				{
					Move((*it));
					you.SetPrevAction(VK_TAB);
					return;
				}
			}
		}
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_AUTOBATTLE_NOMON),true,false,false,CL_small_danger);
		return;
	}


}

bool g_auto = false;

void auto_Move()
{
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY),true,false,false,CL_danger);
		return;
	}
	you.search = false;
	if(env[current_level].insight_mon(MET_ENEMY))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LOS_MON),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.s_dimension)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DIMENSTION),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(env[current_level].isBamboo())
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_AUTOTRAVEL_BAMBOO),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.s_confuse)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE_WARNING),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.resetLOS() == IT_MAP_DANGER)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_MAP_DANGER),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	g_auto = true;
	you.SetPrevAction('o');
	while(1)
	{
		bool back_ = false;
		if(you.auto_pickup>0){
			vector<item*> close_item_vector_;
			env[current_level].close_item(close_item_vector_);
			for(int i=0;i < close_item_vector_.size(); i++)
			{
				item* sight_item = close_item_vector_[i];

				if(!PathSearch(you.position,sight_item->position,you.will_move,ST_NORMAL,current_level,false,you.isSwim()))
				{
				}
				else{
					if(!stack_move(true))
					{
						g_auto = false;
						return;
					}
					back_ = true;
					break;
				}
			}
		}
		if(back_)
			continue;
		
		if(PathSearch(you.position,you.position,you.will_move,ST_SEARCH, current_level, false, you.isSwim()))
		{
			if(!stack_move(true))
			{
				g_auto = false;
				return;
			}
		}
		else
			break;
	}
	while(!you.will_move.empty()){you.will_move.pop();}
	printlog(LocalzationManager::locString(LOC_SYSTEM_DONE_EXPLORE),true,false,false,CL_normal);
	g_auto = false;
}

void long_rest()
{
	if(env[current_level].insight_mon(MET_ENEMY))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LOS_MON),true,false,false,CL_small_danger);
		return;
	}
	you.SetPrevAction('5');
	printlog(LocalzationManager::locString(LOC_SYSTEM_REST_START),true,false,false,CL_bad);
	for(int i=0;i<100;i++)
	{		
		you.time_delay += you.GetNormalDelay();
		switch(you.TurnEnd())
		{
		case IT_HP_RECOVER:
			printlog(LocalzationManager::locString(LOC_SYSTEM_REST_HP),true,false,false,CL_normal);
			return;
		case IT_MP_RECOVER:
			if(!you.pure_mp)
				printlog(LocalzationManager::locString(LOC_SYSTEM_REST_MP),true,false,false,CL_normal);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_REST_HP), true, false, false, CL_normal);
			return;
		case IT_MAP_DANGER:
			printlog(LocalzationManager::locString(LOC_SYSTEM_MAP_DANGER),true,false,false,CL_small_danger);
			return;
		case IT_MAP_FIND:
		case IT_DECO_MONSTER_FIND:
		//case IT_HUNGRY:
		case IT_STAT:
		case IT_POISON:
		case IT_TELE:
		case IT_SMOKE:
		case IT_EVENT:
		case IT_DAMAGE:
		case IT_MAX_ITEM:
			return;
		default:
			break;
		}
		if(env[current_level].insight_mon(MET_ENEMY))
			return;
		if(waitkeyinput(false, true))
			return;
	}
	printlog(LocalzationManager::locString(LOC_SYSTEM_REST_DONE),true,false,false,CL_normal);
}


bool stack_move(bool auto_)
{
	while(!you.will_move.empty())
	{
		int right_move = 0;
		coord_def temp = you.will_move.top();

		if(waitkeyinput(false, true))
			return false;
		if(env[current_level].insight_mon(MET_ENEMY))
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_LOS_MON),true,false,false,CL_small_danger);
			while(!you.will_move.empty()){you.will_move.pop();}
			return false;
		}
		if(you.s_confuse)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE_WARNING),true,false,false,CL_small_danger);
			while(!you.will_move.empty()){you.will_move.pop();}	
			return false;
		}
		if(you.s_dimension)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_DIMENSTION),true,false,false,CL_small_danger);
			while(!you.will_move.empty()){you.will_move.pop();}	
			return false;
		}
		env[current_level].item_view_set();

		right_move = Move(temp);

		switch(you.inter)
		{
		case IT_MAP_DANGER:
			printlog(LocalzationManager::locString(LOC_SYSTEM_MAP_DANGER),true,false,false,CL_small_danger);
			return false;
		case IT_ITEM_PICKUP:
		case IT_MAP_FIND:
		case IT_DECO_MONSTER_FIND:
		//case IT_HUNGRY:
		case IT_STAT:
		case IT_POISON:
		case IT_TELE:
		case IT_SMOKE:
		case IT_EVENT:
		case IT_DAMAGE:
		case IT_MAX_ITEM:
			return false;
		default:
			break;
		}

		int item_interupt_ = env[current_level].new_item_interupt();
		if(item_interupt_ > 0)
		{
			while(!you.will_move.empty()){you.will_move.pop();}
			if(env[current_level].insight_mon(MET_ENEMY))
				printlog(LocalzationManager::locString(LOC_SYSTEM_LOS_MON),true,false,false,CL_small_danger);
			return false;
		}
		else if(item_interupt_<-1){
			//오토무빙일 경우 경로를 종료.
			if(auto_ && you.auto_pickup>0){
				while(!you.will_move.empty()){you.will_move.pop();}
				return true;
			}
		}

		if(right_move == 2)
			you.will_move.pop();
		else if(right_move == 0)
			while(!you.will_move.empty()){you.will_move.pop();}

			
		Sleep(20);
	}
	return true;
}


int Search_Move(const coord_def &c, bool wide, view_type type_, int value_)
{
	int sight_ = 7;
	int sight_x = option_mg.getTileMaxX();
	int sight_y = option_mg.getTileMaxY();
	int return_ = 1;
	if((c.x > you.position.x && you.search_pos.x < DG_MAX_X-1 && wide && !you.s_dimension) 
		|| (!you.s_dimension && c.x > you.position.x && you.search_pos.x < you.position.x + sight_x)
		|| (you.s_dimension && c.x > you.position.x && you.search_pos.x < you.god_value[GT_YUKARI][0] + sight_))
		you.search_pos.x+= c.x - you.position.x;
	else if((c.x < you.position.x && you.search_pos.x > 0 && wide && !you.s_dimension) 
		|| (!you.s_dimension && c.x < you.position.x && you.search_pos.x > you.position.x - sight_x)
		|| (you.s_dimension && c.x < you.position.x && you.search_pos.x > you.god_value[GT_YUKARI][0] - sight_))
		you.search_pos.x-= you.position.x - c.x ;
	if((c.y > you.position.y && you.search_pos.y < DG_MAX_Y-1 && wide && !you.s_dimension) 
		|| (!you.s_dimension && c.y > you.position.y && you.search_pos.y < you.position.y + sight_y)
		|| (you.s_dimension && c.y > you.position.y && you.search_pos.y < you.god_value[GT_YUKARI][1] + sight_))
		you.search_pos.y+= c.y - you.position.y;
	else if((c.y < you.position.y && you.search_pos.y > 0 && wide && !you.s_dimension) 
		|| (!you.s_dimension && c.y < you.position.y && you.search_pos.y > you.position.y - sight_y)
		|| (you.s_dimension && c.y < you.position.y && you.search_pos.y > you.god_value[GT_YUKARI][1] - sight_))
		you.search_pos.y-= you.position.y -c.y;



	if(type_ == VT_NORMAL)
	{	
		deletelog();
		if(!wide) {
			printlog(LocalzationManager::formatString("({0}: ",PlaceHolderHelper(LOC_SYSTEM_COMMAND)),false,false,true,CL_help);
			printlog(LocalzationManager::formatString("{0} - {1}", PlaceHolderHelper("v"), PlaceHolderHelper(LOC_SYSTEM_DESCRIPTION)),false,false,true,CL_help, 'v');
			printlog("   ",false,false,true,CL_help);
			printlog(LocalzationManager::formatString("{0} - {1}", PlaceHolderHelper("."), PlaceHolderHelper(LOC_SYSTEM_EXPLORE)),false,false,true,CL_help, '.');
			printlog("   ",false,false,true,CL_help);
			printlog(LocalzationManager::formatString("{0} - {1}", PlaceHolderHelper("e"), PlaceHolderHelper(LOC_SYSTEM_DANGER)),false,false,true,CL_help, 'e');
			printlog(")",true,false,true,CL_help);
		}
		else {
			printlog(LocalzationManager::formatString("({0}: ",PlaceHolderHelper(LOC_SYSTEM_COMMAND)),false,false,true,CL_help);
			printlog(LocalzationManager::formatString("{0} - {1}", PlaceHolderHelper("v"), PlaceHolderHelper(LOC_SYSTEM_DESCRIPTION)),false,false,true,CL_help, 'v');
			printlog("   ",false,false,true,CL_help);
			printlog(LocalzationManager::formatString("{0} - {1}", PlaceHolderHelper("."), PlaceHolderHelper(LOC_SYSTEM_EXPLORE)),false,false,true,CL_help, '.');
			printlog("   ",false,false,true,CL_help);
			printlog("<",false,false,true,CL_help,'<');
			printlog(",",false,false,true,CL_help);
			printlog(LocalzationManager::formatString("> - {0}", PlaceHolderHelper(LOC_SYSTEM_STAIR_TRAVEL)),false,false,true,CL_help, '>');
			printlog("   ",false,false,true,CL_help);
			printlog(LocalzationManager::formatString("{0} - {1}", PlaceHolderHelper("e"), PlaceHolderHelper(LOC_SYSTEM_DANGER)),false,false,true,CL_help, 'e');
			printlog(")",true,false,true,CL_help);
		}
	}
	else if(type_ == VT_THROW || type_ == VT_DEBUF || type_ == VT_SATORI)
	{
		printlog(LocalzationManager::formatString("({0}: ",PlaceHolderHelper(LOC_SYSTEM_COMMAND)),false,false,true,CL_help);
		printlog(LocalzationManager::formatString("{1} - {2}",PlaceHolderHelper(LOC_SYSTEM_COMMAND), "v", PlaceHolderHelper(LOC_SYSTEM_DESCRIPTION)),false,false,true,CL_help, 'v');	
		printlog(")",true,false,true,CL_help);
	}
	else
		deletelog();

	if(env[current_level].isInSight(you.search_pos))
	{//몬스터확인
		bool mon_ok = false;
		for(vector<monster>::iterator it=env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
		{
			if((*it).isLive() && (*it).isView() && (*it).position.x == you.search_pos.x && (*it).position.y == you.search_pos.y)
			{
				printlog(LocalzationManager::formatString("{0}: ", PlaceHolderHelper(LOC_SYSTEM_MONSTER)),false,false,true,CL_help);
				printlog((*it).name.getName(),false,false,true,CL_normal);
				bool state_ = false;
				if (!((*it).flag & M_FLAG_NO_STATE))
				{
					for (monster_state_simple mss = MSS_SLEEP; mss < MSS_MAX; mss = (monster_state_simple)(mss + 1))
					{
						ostringstream ss;
						D3DCOLOR color_ = (*it).GetStateString(mss, ss);
						if (color_ != CL_none)
						{
							if (!state_)
							{
								printlog("(", false, false, true, CL_normal);
								state_ = true;
							}
							else
							{
								printlog(", ", false, false, true, CL_normal);
							}
							printlog(ss.str(), false, false, true, color_);
						}
					}
					if (state_)
						printlog(")", false, false, true, CL_normal);
					if (type_ == VT_DEBUF)
					{
						float percent_ = getDebufPercent((*it).GetResist(), value_);
						if (it->s_mind_reading)
							percent_ = 0;
						ostringstream oss;
						oss.precision(0);
						oss << std::fixed; 
						oss << "(";
						oss << LocalzationManager::locString(LOC_SYSTEM_SUCCESS_PERCENT) << ": " << std::round(100-percent_) << "%";
						oss << ")";
						printlog(oss.str(), false, false, true, CL_normal);
					}
					else if (type_ == VT_SATORI && !it->s_mind_reading)
					{
						ostringstream oss;
						oss <<"(";

						int turn_ = 2 + it->level / 3 + it->resist * 3;
						turn_ = max(1, turn_ - you.level / 4);

						if (turn_ >= 20 || it->id == MON_KOISHI) {
							oss << LocalzationManager::locString(LOC_SYSTEM_IMPOSSIBLE);
						}
						else {
							oss << turn_ << LocalzationManager::locString(turn_>1?LOC_SYSTEM_TURNS:LOC_SYSTEM_TURN);
						}
						oss <<")";

						printlog(oss.str(), false, false, true, CL_normal);

					}
				}
				printlog(" ",true,false,true,CL_normal);
				mon_ok = true;
				return_ = 0;
				break;
			}
		}
		if(!mon_ok && env[current_level].isSmokePos(you.search_pos.x,you.search_pos.y))
		{
			smoke* smoke_ = env[current_level].isSmokePos2(you.search_pos.x,you.search_pos.y);
			printlog(smoke_->GetName(),true,false,true,CL_normal);
		}
	}


	if(type_ == VT_NORMAL && env[current_level].isInSight(you.search_pos))
	{//아이템확인
		string s;
		int num=0;
		list<item>::iterator it,start_it;
		for(it = env[current_level].item_list.begin();it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++;
			if((*temp).position.x == you.search_pos.x && (*temp).position.y == you.search_pos.y)
			{
				if(!num)
				{
					start_it = temp;
				}
				num++;
			}
			else if(num)
				break;
		}
		if(num)
		{
			if(num<=5)
			{
				while(num--)
				{
					printlog((*start_it).GetName(),false,false,true,(*start_it).item_color());
					printlog("; ",false,false,true,CL_normal);
					start_it++;
				}
				printlog("",true,false,true,CL_normal);
			}
			else
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_MANY_ITEMS),true,false,true,CL_normal);
			}
		}
	}

	if(!(env[current_level].isInSight(you.search_pos)))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_TERRAIN_UNSEEN),true,false,true,CL_normal);
		return_ = 0;
	}
	if(env[current_level].isExplore(you.search_pos.x,you.search_pos.y) || env[current_level].isMapping(you.search_pos.x,you.search_pos.y))
	{//지형확인
		
		string s = "[" + LocalzationManager::locString(LOC_SYSTEM_TERRAIN) +": ";
		s += LocalzationManager::locString(dungeon_tile_tribe_type_string[env[current_level].dgtile[you.search_pos.x][you.search_pos.y].tile]);
		if(env[current_level].isSilence(you.search_pos))
			s += " (" + LocalzationManager::locString(LOC_SYSTEM_TERRAIN) + ")";
		if(env[current_level].isViolet(you.search_pos))
			s += " (" + LocalzationManager::locString(LOC_SYSTEM_TERRAIN_VIOLET) + ")";
		if (env[current_level].isSanctuary(you.search_pos))
			s += " (" + LocalzationManager::locString(LOC_SYSTEM_TERRAIN_SANCTUARY) + ")";
		floor_effect* floor_ = env[current_level].isFloorEffectPos(you.search_pos.x,you.search_pos.y);
		if(env[current_level].isInSight(coord_def(you.search_pos.x,you.search_pos.y)) && floor_)
		{
			s += " (";
			s += floor_->GetName();
			s += ")";
		}
		s += "]";
		printlog(s,true,false,true,CL_normal);

		if(!env[current_level].isMove(you.search_pos.x,you.search_pos.y))
			return_ = 0;
	}
	enterlog();
	return return_;
}
bool Auto_Pick_Up(list<item>::iterator it)
{
	if(!(you.auto_pickup>0))
		return false;
	if(!it->isautopick())
		return false;
	if(you.s_confuse)
		return false;
	if(env[current_level].insight_mon(MET_ENEMY))
		return false;
	//if(you.resetLOS() == IT_MAP_DANGER)
	//	return false; 
	//느린 연산.. 되도록이면 쓰지말자
	return true;
}
int Player_Move(const coord_def &c)
{
	int move_type; //0은 이동불가. 1은 이동하진 않음(주로 공격). 2는 이동했음
	bool pick_ups = false;
	coord_def tempPos = you.position;
	move_type = you.move(c);
	if(move_type)
	{
		if(move_type != 1) //한칸이라도 이동했을때
		{
			//아이템이 땅에 있으면 메세지 출력
			int num=0;
			if(env[current_level].dgtile[you.position.x][you.position.y].tile >= DG_DOWN_STAIR && env[current_level].dgtile[you.position.x][you.position.y].tile <= DG_SEA-1)
			{
				printlog(LocalzationManager::formatString(LOC_SYSTEM_ON_THE_TERRAIN, PlaceHolderHelper(dungeon_tile_tribe_type_string[env[current_level].dgtile[you.position.x][you.position.y].tile])), false,false,false,CL_normal);
				printlog(env[current_level].getTileHelp(you.position.x, you.position.y), true, false, false, CL_normal);
				
			}
				
			list<item>::iterator it,start_it;
			for(it = env[current_level].item_list.begin();it != env[current_level].item_list.end();)
			{
				list<item>::iterator temp = it++;

				if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
				{
					if(!Auto_Pick_Up(temp) || you.s_lunatic || you.s_evoke_ghost)
					{
						if(!num)
							start_it = temp;
						num++;
					}
					else
					{
						if(PickUpNum(temp,1,false))
							break;
						pick_ups = true;
						{ //아이템을 주울때 P가 사라지면 튕길 가능성이 있다.
							it = env[current_level].item_list.begin();
							num = 0;
						}

					}
				}
				else if(num)
					break;
			}
			if(num)
			{
				if(num==1)
				{
					LocalzationManager::printLogWithKey((*start_it).num > 1 ? LOC_SYSTEM_ON_THE_ITEM_MULTIPLE:LOC_SYSTEM_ON_THE_ITEM_SINGLE ,true,false,false,CL_normal, PlaceHolderHelper((*start_it).GetName(), (*start_it).item_color(), (*start_it).num>1));
				}
				else if(num<=4)
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_ON_THE_ITEM_SOME),true,false,false,CL_normal);
					while(num>0)
					{
						printlog((*start_it).GetName(),false,false,false,(*start_it).item_color());
						printlog("; ",num>1?false:true,false,false,CL_normal);
						start_it++;
						num--;
					}
				}
				else
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_ON_THE_ITEM_MANY),true,false,false,CL_normal);
				}
			}



			if (you.god == GT_OKINA && !you.GetPunish(GT_OKINA)) {
				//오키나면 지나온 문은 자동으로 닫음
				if (env[current_level].isDoor(tempPos.x, tempPos.y)){
					int close_ = 0;
					if ((close_ = env[current_level].CloseDoor(tempPos.x, tempPos.y)) == 1)
					{
						//문을 닫고 할게 있나?
					}
				}

			}
		}
		you.TurnEnd();
		if(pick_ups)
			you.SetInter(IT_ITEM_PICKUP);
	}
	return move_type;
}
void search_monspell_view(monster* mon_)
{
	bool loop_ = true;
					
	while(loop_)
	{
		loop_ = false;
		WaitForSingleObject(mutx, INFINITE);
		GetMonsterInfor(mon_);
		ReleaseMutex(mutx);
		changedisplay(DT_SUB_TEXT);
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey, true);

		if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
			key_ = DisplayManager.positionToChar();
		}

		if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
			loop_ = true;
		}
		else if(key_ == VK_DOWN)
		{
			DisplayManager.addPosition(1);
			loop_ = true;
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(DisplayManager.log_length);
			loop_ = true;
		}
		else if(key_ == VK_NEXT)
		{
			changemove(-DisplayManager.log_length);
			loop_ = true;
		} else if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
			for(auto it = mon_->spell_lists.begin();it != mon_->spell_lists.end();it++)
			{
				if(num == 0)
				{
					WaitForSingleObject(mutx, INFINITE);
					SetText() = GetSpellInfor((spell_list)it->num);
					ReleaseMutex(mutx);
					changedisplay(DT_TEXT);
					waitkeyinput();
					changedisplay(DT_SUB_TEXT);
					loop_ = true;
					break;
				}
				num--;
			}			
		} 
		else if (key_ == -1) {
			if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(1);  //아래
				loop_ = true;
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(-1);  //위
				loop_ = true;
			} 
		}	
	}
}
void Search()
{
	you.search_pos = you.position;
	you.search = true;
	startSelection({'v', '.', 'e', VK_ESCAPE});
	Search_Move(coord_def(you.position.x,you.position.y), false);
	while(1)
	{
		InputedKey inputedKey;
		switch(waitkeyinput(inputedKey,false,false, true))
		{
		case 'k':
			Move(coord_def(you.position.x,you.position.y-1));  //위
			break;
		case 'j':
			Move(coord_def(you.position.x,you.position.y+1)); //아래
			break;
		case 'h':
			Move(coord_def(you.position.x-1,you.position.y)); //왼쪽
			break;
		case 'l':
			Move(coord_def(you.position.x+1,you.position.y)); //오른쪽
			break;
		case 'b':
			Move(coord_def(you.position.x-1,you.position.y+1));
			break;
		case 'n':
			Move(coord_def(you.position.x+1,you.position.y+1));
			break;
		case 'y':
			Move(coord_def(you.position.x-1,you.position.y-1));
			break;
		case 'u':
			Move(coord_def(you.position.x+1,you.position.y-1));
			break;
		case 'K':
			Move(coord_def(you.position.x, you.position.y - 8));  //위
			break;
		case 'J':
			Move(coord_def(you.position.x, you.position.y + 8)); //아래
			break;
		case 'H':
			Move(coord_def(you.position.x - 8, you.position.y)); //왼쪽
			break;
		case 'L':
			Move(coord_def(you.position.x + 8, you.position.y)); //오른쪽
			break;
		case 'B':
			Move(coord_def(you.position.x - 8, you.position.y + 8));
			break;
		case 'N':
			Move(coord_def(you.position.x + 8, you.position.y + 8));
			break;
		case 'Y':
			Move(coord_def(you.position.x - 8, you.position.y - 8));
			break;
		case 'U':
			Move(coord_def(you.position.x + 8, you.position.y - 8));
			break;
		case GVK_BUTTON_A_LONG:
		case 'v':
			if(unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y))
			{
				if(!unit_->isplayer() && unit_->isView() && env[current_level].isInSight(you.search_pos))
				{					
					search_monspell_view((monster*)unit_);
					changedisplay(DT_GAME);
				}
			}
			break;
		case 'E':
		case 'e':
		case GVK_BUTTON_X:
			if (!env[current_level].isBamboo())
			{
				env[current_level].AddForbid(you.search_pos);
			}
			break;
		case '.': 
		case VK_RETURN:
		case GVK_BUTTON_A:
			deletelog();
			you.search = false;
			Long_Move(you.search_pos, true);
			return;
		case -1:
			if(inputedKey.mouse == MKIND_MAP_CURSOR) {
				you.search_pos = coord_def(inputedKey.val1, inputedKey.val2);
				Move(coord_def(you.position.x,you.position.y));
				break;
			}
			else if(inputedKey.mouse == MKIND_MAP) {
				deletelog();
				endSelection();
				you.search = false;
				Long_Move(you.search_pos, true);
				return;
			}
			else if(inputedKey.mouse == MKIND_MAP_DESCRIPTION) {
				if(unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y))
				{
					if(!unit_->isplayer() && unit_->isView() && env[current_level].isInSight(you.search_pos))
					{					
						search_monspell_view((monster*)unit_);
						changedisplay(DT_GAME);
						break;
					}
				} else {
					//ESC PASSTHORUGH
				}
			}
			else if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				break;
			}
		case VK_ESCAPE:
   		case GVK_BUTTON_B:
   		case GVK_BUTTON_B_LONG:
		case 'x':
			deletelog();
			endSelection();
			you.search = false;
			return;
		}
	}
}

struct stair_struct
{
	coord_def pos;
	int dis;
	stair_struct():pos(0,0),dis(999999){};
	stair_struct(coord_def pos_,int dis_):pos(pos_),dis(dis_){};
};


void Wide_Search()
{
	you.search_pos = you.position;
	widesearch = true;
	you.search = true;
	Search_Move(coord_def(you.position.x,you.position.y), true);
	list<stair_struct> down_distans,up_distans;
	while(1)
	{
		InputedKey inputedKey;
		startSelection({'v', '.', '<', '>', 'e', VK_ESCAPE});
		switch(waitkeyinput(inputedKey))
		{
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
			break;
		case 'k':
			Move(coord_def(you.position.x,you.position.y-1));  //위
			break;
		case 'j':
			Move(coord_def(you.position.x,you.position.y+1)); //아래
			break;
		case 'h':
			Move(coord_def(you.position.x-1,you.position.y)); //왼쪽
			break;
		case 'l':
			Move(coord_def(you.position.x+1,you.position.y)); //오른쪽
			break;
		case 'b':
			Move(coord_def(you.position.x-1,you.position.y+1));
			break;
		case 'n':
			Move(coord_def(you.position.x+1,you.position.y+1));
			break;
		case 'y':
			Move(coord_def(you.position.x-1,you.position.y-1));
			break;
		case 'u':
			Move(coord_def(you.position.x+1,you.position.y-1));
			break;
		case 'K':
			Move(coord_def(you.position.x,you.position.y-8));  //위
			break;
		case 'J':
			Move(coord_def(you.position.x,you.position.y+8)); //아래
			break;
		case 'H':
			Move(coord_def(you.position.x-8,you.position.y)); //왼쪽
			break;
		case 'L':
			Move(coord_def(you.position.x+8,you.position.y)); //오른쪽
			break;
		case 'B':
			Move(coord_def(you.position.x-8,you.position.y+8));
			break;
		case 'N':
			Move(coord_def(you.position.x+8,you.position.y+8));
			break;
		case 'Y':
			Move(coord_def(you.position.x-8,you.position.y-8));
			break;
		case 'U':
			Move(coord_def(you.position.x+8,you.position.y-8));
			break;
		case '>':
		case GVK_RIGHT_BUMPER:
			if(down_distans.empty())
			{
				if(!environment::isLastFloor(current_level))
				{
					for(int i = 0;i<3;i++)
					{	
						stack<coord_def> stacks;
						if((env[current_level].isExplore(env[current_level].stair_down[i].x,env[current_level].stair_down[i].y) ||
							env[current_level].isMapping(env[current_level].stair_down[i].x,env[current_level].stair_down[i].y)
							)
							&& env[current_level].isStair(env[current_level].stair_down[i].x,env[current_level].stair_down[i].y)
							&& env[current_level].stair_down[i] != you.position
							&& PathSearch(you.position,env[current_level].stair_down[i],stacks,ST_NORMAL))
						{
							list<stair_struct>::iterator it=down_distans.begin();
							for(;it!=down_distans.end();it++)
							{
								if(it->dis > stacks.size())
									break;
							}
							down_distans.insert(it,stair_struct(env[current_level].stair_down[i],stacks.size()));
						}
					}
				}
				for(auto it = env[current_level].stair_vector.begin();it != env[current_level].stair_vector.end(); it++)
				{
					
					stack<coord_def> stacks;
					if((env[current_level].isExplore(it->pos.x,it->pos.y) ||
						env[current_level].isMapping(it->pos.x,it->pos.y) 
						)
						&& it->pos != you.position
						&& PathSearch(you.position,it->pos,stacks,ST_NORMAL))
					{
						list<stair_struct>::iterator it2=down_distans.begin();
						for(;it2!=down_distans.end();it2++)
						{
							if(it2->dis > stacks.size())
								break;
						}
						down_distans.insert(it2,stair_struct(it->pos,stacks.size()));
					}
				}
			}
			if(!down_distans.empty())
			{
				you.search_pos = down_distans.front().pos;
				Move(coord_def(you.position.x,you.position.y));
				down_distans.push_back(down_distans.front());
				down_distans.pop_front();
			}
			break;
		case '<':
		case GVK_LEFT_BUMPER:
			if(up_distans.empty())
			{
				for(int i = 0;i<3;i++)
				{	
					stack<coord_def> stacks;
					if((env[current_level].isExplore(env[current_level].stair_up[i].x,env[current_level].stair_up[i].y)  ||
						env[current_level].isMapping(env[current_level].stair_up[i].x,env[current_level].stair_up[i].y)
						)
						&& env[current_level].isStair(env[current_level].stair_up[i].x,env[current_level].stair_up[i].y)

						&& env[current_level].stair_up[i] != you.position
						&& PathSearch(you.position,env[current_level].stair_up[i],stacks,ST_NORMAL))
					{
						list<stair_struct>::iterator it=up_distans.begin();
						for(;it!=up_distans.end();it++)
						{
							if(it->dis > stacks.size())
								break;
						}
						up_distans.insert(it,stair_struct(env[current_level].stair_up[i],stacks.size()));
					}
				}
			}
			if(!up_distans.empty())
			{
				you.search_pos = up_distans.front().pos;
				up_distans.push_back(up_distans.front());
				up_distans.pop_front();
			}
			break;
		case 'v': 
		case GVK_BUTTON_A_LONG:
			if(unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y))
			{
				if(!unit_->isplayer() && unit_->isView() && env[current_level].isInSight(you.search_pos))
				{
					search_monspell_view((monster*)unit_);
					changedisplay(DT_GAME);
				}
			}
			break;
		case 'E':
		case 'e':
		case GVK_BUTTON_X:
			if (!env[current_level].isBamboo())
			{
				env[current_level].AddForbid(you.search_pos);
			}
			break;
		case '.': 
		case VK_RETURN:
		case GVK_BUTTON_A:
			widesearch = false;
			you.search = false;
			deletelog();
			endSelection();
			Long_Move(you.search_pos, true);
			return;
		case -1:
			if(inputedKey.mouse == MKIND_MAP) {
				coord_def mouse_position = coord_def(inputedKey.val1, inputedKey.val2);
				if(you.search_pos == mouse_position) {
					if(unit *unit_ = env[current_level].isMonsterPos(mouse_position.x,mouse_position.y))
					{
						if(!unit_->isplayer() && unit_->isView() && env[current_level].isInSight(mouse_position))
						{
							search_monspell_view((monster*)unit_);
							changedisplay(DT_GAME);
							break;
						}
					} 
					widesearch = false;
					you.search = false;
					deletelog();
					endSelection();
					Long_Move(you.search_pos, true);
					return;
				} else {
					you.search_pos = mouse_position;
					Move(coord_def(you.position.x,you.position.y));
					break;
				}
			}
			else if(inputedKey.mouse == MKIND_MAP_DESCRIPTION) {
				coord_def mouse_position = coord_def(inputedKey.val1, inputedKey.val2);
				if(unit *unit_ = env[current_level].isMonsterPos(mouse_position.x,mouse_position.y))
				{
					if(!unit_->isplayer() && unit_->isView() && env[current_level].isInSight(mouse_position))
					{
						search_monspell_view((monster*)unit_);
						changedisplay(DT_GAME);
					}
					break;
				} else {
					//ESC PASSTHORUGH
				}
			}
			else if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				break;
			}
		default:
			deletelog();
			endSelection();
			widesearch = false;
			you.search = false;
			return;
		}
	}
}



void turn_skip()
{
	you.time_delay += you.GetNormalDelay();
	you.TurnEnd();
}
void action_turn_skip()
{
	turn_skip();
	you.SetPrevAction('s');
}

void escape() //행동들을 취소함
{
	if(you.search)
	{
		deletelog();
		you.search = false;
		widesearch = false;
	}
}

void Open_Close_door()
{
	int door_num= 0;
	coord_def temp;
	rect_iterator it(you.position,1,1);
	for(;!it.end();it++)
	{
		if((*it) == you.position)
			continue;
		if(env[current_level].isOpenDoor((*it).x,(*it).y) || env[current_level].isCloseDoor((*it).x,(*it).y))
		{
			temp = (*it);
			door_num++;
		}
	}
	if(door_num>1)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_ASK_DOOR),true,false,false,CL_help);
		
		while(door_num>1)
		{
			InputedKey inputedKey;
			switch(waitkeyinput(inputedKey))
			{
			case 'k':
				temp = coord_def(you.position.x,you.position.y-1);
				door_num = 1;
				break;
			case 'j':
				temp = coord_def(you.position.x,you.position.y+1);
				door_num = 1;
				break;
			case 'h':
				temp = coord_def(you.position.x-1,you.position.y);
				door_num = 1;
				break;
			case 'l':
				temp = coord_def(you.position.x+1,you.position.y);
				door_num = 1;
				break;
			case 'y':
				temp = coord_def(you.position.x-1,you.position.y-1);
				door_num = 1;
				break;
			case 'u':
				temp = coord_def(you.position.x+1,you.position.y-1);
				door_num = 1;
				break;
			case 'b':
				temp = coord_def(you.position.x-1,you.position.y+1);
				door_num = 1;
				break;
			case 'n':
				temp = coord_def(you.position.x+1,you.position.y+1);
				door_num = 1;
				break;
			case VK_ESCAPE:
			case GVK_BUTTON_B:
			case GVK_BUTTON_B_LONG:
			case -1:
				{
					if(inputedKey.mouse == MKIND_MAP) {
						coord_def target_pos(inputedKey.val1, inputedKey.val2);
						int target_abs_ = (target_pos - you.position).abs();
						if(target_abs_ > 0 && target_abs_ <= 2) {							
							temp = target_pos;
							door_num = 1;
						}
					} else if (inputedKey.isRightClick()) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE),true,false,false,CL_normal);
						return;
					}
				}
				break;
			default:
				break;
			}
		}
	}
	
	if(door_num==1 && env[current_level].isOpenDoor(temp.x,temp.y))
	{
		int close_= 0;
		if((close_ = env[current_level].CloseDoor(temp.x,temp.y)) == 1)
		{
			if(env[current_level].isInSight(temp))
				soundmanager.playSound("door");
			printlog(LocalzationManager::locString(LOC_SYSTEM_CLOSE_DOOR) + " ",false,false,false,CL_normal);
			you.time_delay += you.GetNormalDelay();
			you.TurnEnd();
		}
		else if(close_ == -1)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_CLOSE_DOOR_FAIL),true,false,false,CL_normal);
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_CLOSE_DOOR_EMPTY),true,false,false,CL_normal);
		}
		you.SetPrevAction('C');
	}
	else if(door_num==1 && env[current_level].isCloseDoor(temp.x,temp.y))
	{
		int result = you.OpenDoor(temp, false);
		if(result == 0)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_OPEN_DOOR_EMPTY),true,false,false,CL_normal);
		}
		else if(result > 0)
			you.TurnEnd();
		you.SetPrevAction('O');
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DOOR_NONE),true,false,false,CL_normal);
	}
}

void Close_door()
{
	int door_num= 0;
	coord_def temp;
	rect_iterator it(you.position,1,1);
	for(;!it.end();it++)
	{
		if((*it) == you.position)
			continue;
		if(env[current_level].isOpenDoor((*it).x,(*it).y))
		{
			temp = (*it);
			door_num++;
		}
	}
	if(door_num>1)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_ASK_CLOSE_DOOR),true,false,false,CL_help);
		
		while(door_num>1)
		{
			InputedKey inputedKey;
			switch(waitkeyinput(inputedKey))
			{
			case 'k':
				temp = coord_def(you.position.x,you.position.y-1);
				door_num = 1;
				break;
			case 'j':
				temp = coord_def(you.position.x,you.position.y+1);
				door_num = 1;
				break;
			case 'h':
				temp = coord_def(you.position.x-1,you.position.y);
				door_num = 1;
				break;
			case 'l':
				temp = coord_def(you.position.x+1,you.position.y);
				door_num = 1;
				break;
			case 'y':
				temp = coord_def(you.position.x-1,you.position.y-1);
				door_num = 1;
				break;
			case 'u':
				temp = coord_def(you.position.x+1,you.position.y-1);
				door_num = 1;
				break;
			case 'b':
				temp = coord_def(you.position.x-1,you.position.y+1);
				door_num = 1;
				break;
			case 'n':
				temp = coord_def(you.position.x+1,you.position.y+1);
				door_num = 1;
				break;
			case VK_ESCAPE:
			case GVK_BUTTON_B:
			case GVK_BUTTON_B_LONG:
			case -1:
				{
					if(inputedKey.mouse == MKIND_MAP) {
						coord_def target_pos(inputedKey.val1, inputedKey.val2);
						int target_abs_ = (target_pos - you.position).abs();
						if(target_abs_ > 0 && target_abs_ <= 2) {							
							temp = target_pos;
							door_num = 1;
						}
					} else if (inputedKey.isRightClick()) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE),true,false,false,CL_normal);
						return;
					}
				}
				break;
			default:
				break;
			}
		}
	}
	
	if(door_num==1)
	{
		int close_= 0;
		if((close_ = env[current_level].CloseDoor(temp.x,temp.y)) == 1)
		{
			if(env[current_level].isInSight(temp))
				soundmanager.playSound("door");
			printlog(LocalzationManager::locString(LOC_SYSTEM_CLOSE_DOOR) + " ",false,false,false,CL_normal);
			you.time_delay += you.GetNormalDelay();
			you.TurnEnd();
		}
		else if(close_ == -1)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_CLOSE_DOOR_FAIL),true,false,false,CL_normal);
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_CLOSE_DOOR_EMPTY),true,false,false,CL_normal);
		}
		you.SetPrevAction('C');
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_CLOSE_DOOR_NONE),true,false,false,CL_normal);
		you.SetPrevAction('C');
	}
}


void Open_door()
{
	int door_num= 0;
	coord_def temp;
	rect_iterator it(you.position,1,1);
	for(;!it.end();it++)
	{
		if((*it) == you.position)
			continue;
		if(env[current_level].isCloseDoor((*it).x,(*it).y))
		{
			temp = (*it);
			door_num++;
		}
	}
	if(door_num>1)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_ASK_OPEN_DOOR),true,false,false,CL_help);
		
		while(door_num>1)
		{
			InputedKey inputedKey;
			switch(waitkeyinput(inputedKey))
			{
			case 'k':
				temp = coord_def(you.position.x,you.position.y-1);
				door_num = 1;
				break;
			case 'j':
				temp = coord_def(you.position.x,you.position.y+1);
				door_num = 1;
				break;
			case 'h':
				temp = coord_def(you.position.x-1,you.position.y);
				door_num = 1;
				break;
			case 'l':
				temp = coord_def(you.position.x+1,you.position.y);
				door_num = 1;
				break;
			case 'y':
				temp = coord_def(you.position.x-1,you.position.y-1);
				door_num = 1;
				break;
			case 'u':
				temp = coord_def(you.position.x+1,you.position.y-1);
				door_num = 1;
				break;
			case 'b':
				temp = coord_def(you.position.x-1,you.position.y+1);
				door_num = 1;
				break;
			case 'n':
				temp = coord_def(you.position.x+1,you.position.y+1);
				door_num = 1;
				break;
			case VK_ESCAPE:
			case GVK_BUTTON_B:
			case GVK_BUTTON_B_LONG:
			case -1:
				{
					if(inputedKey.mouse == MKIND_MAP) {
						coord_def target_pos(inputedKey.val1, inputedKey.val2);
						int target_abs_ = (target_pos - you.position).abs();
						if(target_abs_ > 0 && target_abs_ <= 2) {							
							temp = target_pos;
							door_num = 1;
						}
					} else if (inputedKey.isRightClick()) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE),true,false,false,CL_normal);
						return;
					}
				}
				break;
			default:
				break;
			}
		}
	}
	if(door_num==1)
	{
		int result = you.OpenDoor(temp, false);
		if(result == 0)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_OPEN_DOOR_EMPTY),true,false,false,CL_normal);
		}		
		else if(result > 0)
			you.TurnEnd();
		you.SetPrevAction('O');
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_OPEN_DOOR_NONE),true,false,false,CL_normal);
		you.SetPrevAction('O');
	}
	
}



bool CheckDimension()
{
	if (you.god != GT_YUKARI) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_DIMENSION_STAIR), true, false, false, CL_danger);
		return false;
	}


	while(1)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DIMENSION_STAIT_WARN),false,false,false,CL_help);
		printlog(" (",false,false,false,CL_help);
		printlog("Y",false,false,false,CL_help, 'Y');
		printlog("/",false,false,false,CL_help);
		printlog("N",false,false,false,CL_help, 'N');
		printlog(") ",false,false,false,CL_help);
		startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
		switch(waitkeyinput())
		{
		case 'Y':
    	case GVK_BUTTON_A_LONG:
			you.s_dimension = 0;
			enterlog();
			endSelection();
			return true;
		case 'N':
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_CONTINUE_CRAWL),true,false,false,CL_help);
			endSelection();
			return false;
		}
	}
}
bool warning(dungeon_tile_type type, bool down)
{//경고메시지를 주는 곳
	
	switch(type)
	{
	case DG_YUKKURI_STAIR:
		if(down)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_SUBDUNGEON_WARN),false,false,false,CL_danger);
			printlog(" (",false,false,false,CL_danger);
			printlog("y",false,false,false,CL_danger, 'y');
			printlog("/",false,false,false,CL_danger);
			printlog("n",false,false,false,CL_danger, 'n');
			printlog(") ",false,false,false,CL_danger);
			startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
			case GVK_BUTTON_A:
			case GVK_BUTTON_A_LONG:
				enterlog();
				endSelection();
				return true;
			case 'N':
			default:
				printlog(LocalzationManager::locString(LOC_SYSTEM_WISDOM),true,false,false,CL_help);
				endSelection();
				return false;
			}
		}
		break;
	case DG_SCARLET_U_STAIR:
		if(down)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_SUBDUNGEON_WARN),false,false,false,CL_danger);
			printlog(" (",false,false,false,CL_danger);
			printlog("y",false,false,false,CL_danger, 'y');
			printlog("/",false,false,false,CL_danger);
			printlog("n",false,false,false,CL_danger, 'n');
			printlog(") ",false,false,false,CL_danger);
			startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
			case GVK_BUTTON_A:
			case GVK_BUTTON_A_LONG:
				enterlog();
				endSelection();
				return true;
			case 'N':
			default:
				printlog(LocalzationManager::locString(LOC_SYSTEM_WISDOM),true,false,false,CL_help);
				endSelection();
				return false;
			}
		}
		break;
	case DG_BAMBOO_STAIR:
		if(down)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_SUBDUNGEON_MAZE),false,false,false,CL_danger);
			printlog(" (",false,false,false,CL_danger);
			printlog("y",false,false,false,CL_danger, 'y');
			printlog("/",false,false,false,CL_danger);
			printlog("n",false,false,false,CL_danger, 'n');
			printlog(") ",false,false,false,CL_danger);
			startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
			case GVK_BUTTON_A:
			case GVK_BUTTON_A_LONG:
				enterlog();
				endSelection();
				return true;
			case 'N':
			default:
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOOD_CHOICE),true,false,false,CL_help);
				endSelection();
				return false;
			}
		}
		break;
	case DG_PANDEMONIUM_STAIR:
		if(down)
		{
			if(!(current_level >= PANDEMONIUM_LEVEL && current_level <= PANDEMONIUM_LAST_LEVEL))
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_SUBDUNGEON_MAZE),false,false,false,CL_danger);
				printlog(" (",false,false,false,CL_danger);
				printlog("y",false,false,false,CL_danger, 'y');
				printlog("/",false,false,false,CL_danger);
				printlog("n",false,false,false,CL_danger, 'n');
				printlog(") ",false,false,false,CL_danger);
				startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
				switch(waitkeyinput())
				{
				case 'Y':
				case 'y':
				case GVK_BUTTON_A:
				case GVK_BUTTON_A_LONG:
					enterlog();
					endSelection();
					return true;
				case 'N':
				default:
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOOD_CHOICE),true,false,false,CL_help);
					endSelection();
					return false;
				}
			}
		}
		//break; 없음 판데모니엄도 이어짐
	case DG_RETURN_STAIR:
		if(current_level > PANDEMONIUM_LEVEL && current_level <= PANDEMONIUM_LAST_LEVEL)
		{
			if((type == DG_PANDEMONIUM_STAIR && down ) || (type == DG_RETURN_STAIR && !down ) )
			{
				if(!you.rune[RUNE_PANDEMONIUM_MAGIC + current_level - PANDEMONIUM_LEVEL-1])
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_SUBDUNGEON_RUNE),false,false,false,CL_danger);
					printlog(" (",false,false,false,CL_danger);
					printlog("y",false,false,false,CL_danger, 'y');
					printlog("/",false,false,false,CL_danger);
					printlog("n",false,false,false,CL_danger, 'n');
					printlog(") ",false,false,false,CL_danger);
					startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
					switch(waitkeyinput())
					{
					case 'Y':
					case 'y':
					case GVK_BUTTON_A:
					case GVK_BUTTON_A_LONG:
						enterlog();
						endSelection();
						return true;
					case 'N':
					default:
						printlog(LocalzationManager::locString(LOC_SYSTEM_OK),true,false,false,CL_help);
						endSelection();
						return false;
					}
				}
			}
		}
		break;
	case DG_ZIGURRAT_STAIR:
		if (down && current_level != ZIGURRAT_LEVEL)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_SUBDUNGEON_ZIGURRAT), false, false, false, CL_danger);
			printlog(" (",false,false,false,CL_danger);
			printlog("y",false,false,false,CL_danger, 'y');
			printlog("/",false,false,false,CL_danger);
			printlog("n",false,false,false,CL_danger, 'n');
			printlog(") ",false,false,false,CL_danger);
			startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
			switch (waitkeyinput())
			{
			case 'Y':
			case 'y':
			case GVK_BUTTON_A:
			case GVK_BUTTON_A_LONG:
				if (you.ziggurat_level) {
					printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_SUBDUNGEON_ZIGURRAT_ALREADY), true, false, false, CL_help);
					endSelection();
					return false;
				}
				enterlog();
				endSelection();
				return true;
			case 'N':
			default:
				printlog(LocalzationManager::locString(LOC_SYSTEM_NEED_PREPARATION), true, false, false, CL_help);
				endSelection();
				return false;
			}
		}
		break;
	case DG_DREAM_STAIR:
		if(down)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_SUBDUNGEON_MAZE),false,false,false,CL_danger);
			printlog(" (",false,false,false,CL_danger);
			printlog("y",false,false,false,CL_danger, 'y');
			printlog("/",false,false,false,CL_danger);
			printlog("n",false,false,false,CL_danger, 'n');
			printlog(") ",false,false,false,CL_danger);
			startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
			case GVK_BUTTON_A:
			case GVK_BUTTON_A_LONG:
				enterlog();
				endSelection();
				return true;
			case 'N':
			default:
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOOD_CHOICE),true,false,false,CL_help);
				endSelection();
				return false;
			}
		}
		break;
	case DG_HAKUREI_STAIR:
		if(down)
		{
			if(you.haveGoal()<3)
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_THREE_RUNE),true,false,false,CL_normal);
				return false;
			}
			else 
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_THREE_RUNE_OPEN),true,false,false,CL_normal);
				MoreWait();
			}
		}
		break;
	default:
		break;
	}
	return true;
}



void Stair_move_all() {

	switch (dungeon_tile_type type = env[current_level].dgtile[you.position.x][you.position.y].tile)
	{
	case DG_DOWN_STAIR:
	case DG_TEMPLE_STAIR:
	case DG_MISTY_LAKE_STAIR:
	case DG_YOUKAI_MOUNTAIN_STAIR:
	case DG_SCARLET_STAIR:
	case DG_SCARLET_L_STAIR:
	case DG_SCARLET_U_STAIR:
	case DG_BAMBOO_STAIR:
	case DG_EIENTEI_STAIR:
	case DG_SUBTERRANEAN_STAIR:
	case DG_YUKKURI_STAIR:
	case DG_DEPTH_STAIR:
	case DG_DREAM_STAIR:
	case DG_MOON_STAIR:
	case DG_PANDEMONIUM_STAIR:
	case DG_HAKUREI_STAIR:
	case DG_ZIGURRAT_STAIR:
		Stair_move(true);
		break;
	case DG_UP_STAIR:
	case DG_RETURN_STAIR:
		Stair_move(false);
		break;
	default:
		break;
	}
}



void Stair_move(bool down)
{
	dungeon_tile_type type = env[current_level].dgtile[you.position.x][you.position.y].tile;
	switch(env[current_level].getStairKind(you.position.x, you.position.y))
	{
	case STAIR_KIND_DOWN_BASE:
		if(!down)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_CANT_UP),true,false,false,CL_normal);
			break;
		}




		if(!environment::isLastFloor(current_level))
		{
			if(!warning(type, down))
			{
				return;
			}
			if(you.s_dimension)
			{
				if(!CheckDimension())					
					return;
			}


			if(you.s_catch)
				you.SetCatch(NULL);
			for(int i=0;i<3;i++)
			{
				if(env[current_level].stair_down[i] == you.position)
				{		
					deque<monster*> dq;
					for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
					{
						if(it->isLive() && distan_coord(it->position,you.position) <=2 && it->CanChase())
						{
							dq.push_back(&(*it));
						}
					}
					rand_shuffle(dq.begin(),dq.end());
					you.time_delay += you.GetNormalDelay();
					you.TurnEnd();
					you.time_delay += you.GetNormalDelay();
					you.TurnEnd();
					env[current_level+1].EnterMap(i,dq);
					printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_DOWN),true,false,false,CL_normal);
					GodAccpect_Stair(true, false);
					soundmanager.playSound("stair");
					//you.resetLOS(false);
					you.TurnEnd();
					break;
				}
			}
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_LOWEST_DOWN),true,false,false,CL_normal);
		}
		break;
	case STAIR_KIND_DOWN_SPECIAL:
		if(!down)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_CANT_UP),true,false,false,CL_normal);
			break;
		}
		{
			if(!warning(type, down))
			{
				return;
			}

			if(you.s_dimension)
			{
				if(!CheckDimension())					
					return;
			}

			if(you.s_catch)
				you.SetCatch(NULL);
			deque<monster*> dq;
			for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && distan_coord(it->position,you.position) <=2 && it->CanChase())
				{
					dq.push_back(&(*it));
				}
			}
			rand_shuffle(dq.begin(),dq.end());
			you.time_delay += you.GetNormalDelay();
			you.TurnEnd();
			dungeon_level next_ = TEMPLE_LEVEL;
			switch(type)
			{
				case DG_TEMPLE_STAIR:
					next_ = TEMPLE_LEVEL;
					break;
				case DG_MISTY_LAKE_STAIR:
					next_ = MISTY_LAKE_LEVEL;
					break;
				case DG_YOUKAI_MOUNTAIN_STAIR:
					next_ = YOUKAI_MOUNTAIN_LEVEL;
					break;
				case DG_SCARLET_STAIR:
					next_ = SCARLET_LEVEL;
					break;
				case DG_SCARLET_L_STAIR:
					next_ = SCARLET_LIBRARY_LEVEL;
					break;			
				case DG_SCARLET_U_STAIR:
					next_ = SCARLET_UNDER_LEVEL;
					break;			
				case DG_BAMBOO_STAIR:
					next_ = BAMBOO_LEVEL;
					break;
				case DG_EIENTEI_STAIR:					
					next_ = EIENTEI_LEVEL;
					break;			
				case DG_SUBTERRANEAN_STAIR:
					next_ = SUBTERRANEAN_LEVEL;
					break;
				case DG_YUKKURI_STAIR:
					next_ = YUKKURI_LEVEL;
					break;					
				case DG_DEPTH_STAIR:
					next_ = DEPTH_LEVEL;
					break;			
				case DG_DREAM_STAIR:
					next_ = DREAM_LEVEL;
					if (env[next_].make == true)
					{
						next_ = MOON_LEVEL;
					}
					break;			
				case DG_MOON_STAIR:					
					next_ = MOON_LEVEL;
					break;			
				case DG_PANDEMONIUM_STAIR:					
					next_ = PANDEMONIUM_LEVEL;
					{
						if(randA(3)==1)
						{
							int rare_ = rand_int(1,MAX_PANDEMONIUM_LEVEL);
							for(int i = 0 ; i < MAX_PANDEMONIUM_LEVEL; i++)
							{
								int temp_=(PANDEMONIUM_LEVEL+((rare_+i)%MAX_PANDEMONIUM_LEVEL)+1);
								if(env[temp_].make == false)
								{
									next_ = (dungeon_level)temp_;
									break;
								}
							}
						}
					}
					break;
				case DG_ZIGURRAT_STAIR:
					next_ = ZIGURRAT_LEVEL;
					break;
				case DG_HAKUREI_STAIR:
					next_ = HAKUREI_LEVEL;
					break;			
				default:
					break;
			}

			env[next_].EnterMap(0,dq); 
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_DOWN),true,false,false,CL_normal);
			GodAccpect_Stair(true, true);
			soundmanager.playSound("stair");
			//you.resetLOS(false);
			you.TurnEnd();
			break;
		}
		break;
	case STAIR_KIND_UP_BASE:
		if(down)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_CANT_DOWN),true,false,false,CL_normal);
			break;
		}
		if(current_level>0)
		{			
			if(!warning(type, down))
			{
				return;
			}
			if(you.s_dimension)
			{
				if(!CheckDimension())					
					return;
			}

			if(you.s_catch)
				you.SetCatch(NULL);
			for(int i=0;i<3;i++)
			{
				if(env[current_level].stair_up[i] == you.position)
				{	
					deque<monster*> dq;
					for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
					{
						if(it->isLive() && distan_coord(it->position,you.position) <=2 && it->CanChase())
						{
							dq.push_back(&(*it));
						}
					}
					rand_shuffle(dq.begin(),dq.end());
					you.time_delay += you.GetNormalDelay();
					you.TurnEnd();
					env[current_level-1].EnterMap(i,dq);
					printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_UP),true,false,false,CL_normal);
					GodAccpect_Stair(false, false);
					soundmanager.playSound("stair");
					//you.resetLOS(false);
					you.TurnEnd();
					break;
				}
			}
		}
		else
		{


			if(you.haveOrb())
			{				
				you.dead_reason = DR_ESCAPE;
				GameOver();
				break;
			}
			else
			{
				if(!you.haveGoal())
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_ESCAPE_WARN) + " ",false,false,false,CL_danger);
				}
				else
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_ESCAPE_LAST_QUESTION) + " ",false,false,false,CL_normal);

				}
				printlog("(",false,false,false,you.haveGoal()?CL_normal:CL_danger);
				printlog("Y",false,false,false,you.haveGoal()?CL_normal:CL_danger, 'Y');
				printlog("/",false,false,false,you.haveGoal()?CL_normal:CL_danger);
				printlog("N",false,false,false,you.haveGoal()?CL_normal:CL_danger, 'N');
				printlog(")",false,false,false,you.haveGoal()?CL_normal:CL_danger);
				startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
				
				int direc = waitkeyinput(true);
				endSelection();
				if(direc == 'Y'  || direc == GVK_BUTTON_A_LONG)
				{
					you.dead_reason = DR_ESCAPE;
					GameOver();
					break;
				}
				printlog(LocalzationManager::locString(LOC_SYSTEM_CONTINUE_EXPRO),true,false,false,CL_normal);
			}
		}
		break;
	case STAIR_KIND_UP_SPECIAL:
		if(down)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_CANT_DOWN),true,false,false,CL_normal);
			break;
		}
		{
			if(!warning(type, down))
			{
				return;
			}
			if(you.s_dimension)
			{
				if(!CheckDimension())					
					return;
			}

			if(you.s_catch)
				you.SetCatch(NULL);
			int floor_return=0;
			coord_def pos_return(0,0);

			
			switch(current_level)
			{
			case TEMPLE_LEVEL:
				floor_return = map_list.dungeon_enter[TEMPLE].floor;
				env[floor_return].MakeMap(true); //역행시 서브던전 입구를 찾기 위해 미리 만든다.
				pos_return = map_list.dungeon_enter[TEMPLE].pos;
				break;
			case MISTY_LAKE_LEVEL:
				floor_return = map_list.dungeon_enter[MISTY_LAKE].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[MISTY_LAKE].pos;
				break;
			case YOUKAI_MOUNTAIN_LEVEL:
				floor_return = map_list.dungeon_enter[YOUKAI_MOUNTAIN].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[YOUKAI_MOUNTAIN].pos;
				break;
			case SCARLET_LEVEL:
				floor_return = map_list.dungeon_enter[SCARLET_M].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[SCARLET_M].pos;
				break;				
			case SCARLET_LIBRARY_LEVEL:
				floor_return = map_list.dungeon_enter[SCARLET_L].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[SCARLET_L].pos;
				break;
			case SCARLET_UNDER_LEVEL: 
				floor_return = map_list.dungeon_enter[SCARLET_U].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[SCARLET_U].pos;
				break;				
			case BAMBOO_LEVEL: 
				floor_return = map_list.dungeon_enter[BAMBOO].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[BAMBOO].pos;
				break;			
			case EIENTEI_LEVEL: 
				floor_return = map_list.dungeon_enter[BAMBOO].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[BAMBOO].pos;
				break;
			//case SUBTERRANEAN_LEVEL: 
			//	floor_return = map_list.dungeon_enter[SUBTERRANEAN].floor;
			//	env[floor_return].MakeMap(true);
			//	pos_return = map_list.dungeon_enter[SUBTERRANEAN].pos;
			//	break;
			case YUKKURI_LEVEL:
				floor_return = map_list.dungeon_enter[YUKKURI_D].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[YUKKURI_D].pos;
				break;				
			case DEPTH_LEVEL:
				floor_return = map_list.dungeon_enter[DEPTH].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[DEPTH].pos;
				break;	
			case DREAM_LEVEL:
				floor_return = map_list.dungeon_enter[DREAM_D].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[DREAM_D].pos;
				break;	
			case MOON_LEVEL:
				floor_return = map_list.dungeon_enter[DREAM_D].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[DREAM_D].pos;
				break;
			case PANDEMONIUM_LEVEL:
			case PANDEMONIUM_LEVEL+1:
			case PANDEMONIUM_LEVEL+2:
			case PANDEMONIUM_LEVEL+3:
				floor_return = map_list.dungeon_enter[PANDEMONIUM].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[PANDEMONIUM].pos;
				break;
			case HAKUREI_LEVEL:
				floor_return = map_list.dungeon_enter[HAKUREI_D].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[HAKUREI_D].pos;
				break;
			case ZIGURRAT_LEVEL:
				floor_return = map_list.dungeon_enter[ZIGURRAT].floor;
				//지구랏에서 나오면 지구랏 1층으로 초기화
				//you.ziggurat_level = 0;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[ZIGURRAT].pos;
				break;

			}
			if(current_level>=SUBTERRANEAN_LEVEL && current_level<=SUBTERRANEAN_LEVEL_LAST_LEVEL)
			{
				floor_return = map_list.dungeon_enter[SUBTERRANEAN].floor;
				env[floor_return].MakeMap(true);
				pos_return = map_list.dungeon_enter[SUBTERRANEAN].pos;
			}
			if (current_level == OKINA_LEVEL) {
				floor_return = you.god_value[GT_OKINA][0];// map_list.dungeon_enter[SUBTERRANEAN].floor;
				env[floor_return].MakeMap(true);
				pos_return = coord_def(you.god_value[GT_OKINA][1], you.god_value[GT_OKINA][2]);//map_list.dungeon_enter[SUBTERRANEAN].pos;
				//floor_return = map_list.dungeon_enter[SUBTERRANEAN].floor;
				//env[floor_return].MakeMap(true);
				//pos_return = map_list.dungeon_enter[SUBTERRANEAN].pos;

			}

			deque<monster*> dq;
			for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && distan_coord(it->position,you.position) <=2 && it->CanChase())
				{
					dq.push_back(&(*it));
				}
			}
			rand_shuffle(dq.begin(),dq.end());
			you.time_delay += you.GetNormalDelay();
			you.TurnEnd();
			env[floor_return].EnterMap(-1,dq,pos_return);
			printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_RETURN),true,false,false,CL_normal);
			GodAccpect_Stair(false, true);
			soundmanager.playSound("stair");
			//you.resetLOS(false);
			you.TurnEnd();
			break;
		}
		break;
	default:
		printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_EMPTY),true,false,false,CL_normal);
		break;
	}
}



void view_log()
{
	changedisplay(DT_LOG);
	while(1)
	{
		InputedKey inputedKey;
		switch(waitkeyinput(inputedKey, true))
		{
		case VK_UP:
			changemove(1);  //위
			continue;
		case VK_DOWN:
			changemove(-1); //아래
			continue;
		case VK_PRIOR:
			changemove(DisplayManager.log_length);
			continue;
		case VK_NEXT:
			changemove(-DisplayManager.log_length);
			continue;
		case -1:
		{
			if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(1);
				continue;
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(-1);
				continue;
			} 
		}
		}
		break;
	}
	changedisplay(DT_GAME);
}

void skill_view()
{
	view_skill(LOC_EMPTYSTRING);
	int move_ = 1;
	bool ok_ = false;
	do
	{
		while(1)
		{
			InputedKey inputedKey;
			int key_ = waitkeyinput(inputedKey,true);

			if(key_ == VK_RETURN || key_ == GVK_BUTTON_A) {
				key_ = DisplayManager.positionToChar();
			}

			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				int num = (key_ >= 'a' && key_ <= 'z')?key_-'a':key_-'A'+26;
				if (num < SKT_MAX && you.GetSkillLevel(num,false) < 27 && !you.cannotSkillup(num))
				{
					you.skill[num].onoff = (you.skill[num].onoff+1)%3;
				}
			}
			else if(key_ == '!')
			{
				changemove(move_);
				move_ = move_==1?-1:1;
			}
			else if(key_ == VK_DOWN)//-----이동키-------
			{
				DisplayManager.addPosition(1);
			}
			else if(key_ == VK_UP)
			{
				DisplayManager.addPosition(-1);
			}
			else if(key_ == VK_RIGHT)//-----이동키-------
			{
				DisplayManager.addPosition(SKT_SPELLCASTING);
			}
			else if(key_ == VK_LEFT)
			{
				DisplayManager.addPosition(-SKT_SPELLCASTING);
			}
			else if(key_ == -1) {
				if(inputedKey.mouse == MKIND_SCROLL_UP) {
					changemove(-32);  //아래
				} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
					changemove(32);  //위
				} else if (inputedKey.isRightClick()) {
					break;
				}
			}
			else if(!key_)
			{

			}
			else
				break;
		}
		bool allMax = true;
		for(int i = 0; i < SKT_MAX; i++)
		{
			if (you.GetSkillLevel(i, false) < 27)
			{
				allMax = false;
			}
			if(you.skill[i].onoff >= 1)
			{
				ok_ = true;
				break;	
			}
		}
		if (allMax == true)
			ok_ = true;
		if(ok_==false)
			view_skill(LOC_SYSTEM_SKILL_LEAST_ONE);
	}
	while(!ok_);

	changedisplay(DT_GAME);
}
void stat_view()
{
	changedisplay(DT_STATE);
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
}

void ForMouseClick(MOUSE_KIND mouse_type, int val1, int val2);


void rightmenu_control()
{
	g_menu_select = you.lastSelectMenu;
	while(1)
	{
		InputedKey inputedKey;
		int input = waitkeyinput(inputedKey, true);
		switch(input)
		{
		case VK_UP:
			if(g_menu_select >= greed_max_x) {
				g_menu_select -= greed_max_x;
			}
			continue;
		case VK_DOWN:
			if(g_menu_select < greed_max_x*(greed_max_y-1)-1) {
				g_menu_select += greed_max_x;
			}
			continue;
		case VK_LEFT:
			if(g_menu_select > 0) {
				g_menu_select--;
			}
			continue;
		case VK_RIGHT:
			if(g_menu_select < greed_max_x*greed_max_y-1) {
				g_menu_select++;
			}
			continue;
		case VK_RETURN:
		case '?':
		case GVK_BUTTON_A://패드 A
		case GVK_BUTTON_A_LONG: //패드 A 길게
		{
			if(g_menu_select == -1){
				break;
			}
			bool long_ = (input == GVK_BUTTON_A_LONG) || (input == '?');
			if(g_menu_select < 20 && !long_) {
				int temp = g_menu_select;
				you.lastSelectMenu = g_menu_select;
				g_menu_select = -1;
				if(temp == SYSCMD_MORE_ITEM || temp == SYSCMD_MORE_VIEW) {
					g_menu_select = 0;
				}
				ForMouseClick(MKIND_SYSTEM, temp, 0);
				return;
			} else if(g_menu_select>=20 && g_menu_select < 72) {
				int item_index = g_menu_select-20;
				for(auto it = you.item_list.begin(); it != you.item_list.end(); it++) {
					if(item_index-- == 0) {
						you.lastSelectMenu = g_menu_select;
						g_menu_select = -1;
						ForMouseClick(long_?MKIND_ITEM_DESCRIPTION:MKIND_ITEM, it->id, 0);
						return;
					}
				}
			} else {
				int item_index = g_menu_select-72;
				//땅에 떨어진거 줍기
				list<item>::iterator floor_items = env[current_level].item_list.end(); 
				for(auto it = env[current_level].item_list.begin(); it != env[current_level].item_list.end();)
				{
					list<item>::iterator temp = it++; 
					
					if((*temp).position == you.position) {
						floor_items = temp;
						break;
					}
				}
				
				if(floor_items != env[current_level].item_list.end()) {
					if(floor_items->position == you.position ) {
						if(item_index-- == 0) {
							you.lastSelectMenu = g_menu_select;
							g_menu_select = -1;
							ForMouseClick(long_?MKIND_PICK_DESCRIPTION:MKIND_PICK, item_index+1, 0);
							return;
						}
						floor_items++;
					}
				}
			}
			break;
		}
		case VK_ESCAPE:
		default:
			break;
		case -1:
			ForMouseClick(inputedKey.mouse, inputedKey.val1, inputedKey.val2);
			break;
		// {
		// 	if(inputedKey.mouse == MKIND_SCROLL_UP) {
		// 		changemove(1);
		// 		continue;
		// 	} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
		// 		changemove(-1);
		// 		continue;
		// 	} 
		// }
		}
		break;
	}
	g_menu_select = -1;
}



void rune_Show()
{
	if(!isNormalGame())
		return;
	int remain = 10;
	SetText() = "  <" + LocalzationManager::locString(LOC_SYSTEM_UI_RUNE_TITLE) + ">\n\n\n";



	for(int i = 0; i<RUNE_HAKUREI_ORB;i++)
	{
		remain = 15;
		remain -= PrintCharWidth(LocalzationManager::locString(rune_string[i]));
		for(;remain>0;remain--)
			SetText() += " ";
		SetText() += LocalzationManager::formatString(LOC_SYSTEM_UI_RUNE_NAME, PlaceHolderHelper(rune_string[i]));
		SetText() += " :";


		if(you.rune[i])
		{
			SetText() += " " + LocalzationManager::locString(LOC_SYSTEM_UI_RUNE_GAIN);
		}
		else
		{
			SetText() += " X";
		}
		SetText() += "\n\n";
	}
	SetText() += "\n\n\n";
	
	if(you.rune[RUNE_HAKUREI_ORB])
	{
		SetText() += LocalzationManager::locString(LOC_SYSTEM_UI_RUNE_WIN) + "\n";
	}
	else
	{
		SetText() += LocalzationManager::locString(LOC_SYSTEM_UI_RUNE_NOT_WIN) + "\n\n";
		SetText() += LocalzationManager::locString(LOC_SYSTEM_UI_RUNE_WIN_CONDITION);
	}


	
	changedisplay(DT_TEXT);

	while(1)
	{
		waitkeyinput(true);		
		break;
	}
	changedisplay(DT_GAME);
}



void Iden_Show()
{
	vector<int> curList;

	for (int i = IDEN_CHECK_START; i < IDEN_CHECK_END; i++) {
		if (i >= IDEN_CHECK_POTION_START && i < IDEN_CHECK_POTION_END) {
			int cur = i - IDEN_CHECK_POTION_START;
			if (iden_list.potion_list[cur].iden)
				curList.push_back(i);
		}
		else if (i >= IDEN_CHECK_SCROLL_START && i < IDEN_CHECK_SCROLL_END) {
			int cur = i - IDEN_CHECK_SCROLL_START;
			if (iden_list.scroll_list[cur].iden == 3)
				curList.push_back(i);
		}
		else if (i >= IDEN_CHECK_RING_START && i < IDEN_CHECK_RING_END) {
			int cur = i - IDEN_CHECK_RING_START;
			if (iden_list.ring_list[cur].iden == 2)
				curList.push_back(i);
		}
		else if (i >= IDEN_CHECK_AMULET_START && i < IDEN_CHECK_AMULET_END) {
			int cur = i - IDEN_CHECK_AMULET_START;
			if (iden_list.amulet_list[cur].iden == 2)
				curList.push_back(i);
		}
		else if (i >= IDEN_CHECK_SPC_START && i < IDEN_CHECK_SPC_END) {
			int cur = i - IDEN_CHECK_SPC_START;
			if (iden_list.spellcard_list[cur].iden == 2)
				curList.push_back(i);
		}
		else if (i >= IDEN_CHECK_BOOK_START && i < IDEN_CHECK_BOOK_END) {
			int cur = i - IDEN_CHECK_BOOK_START;
			if (cur == 0 || iden_list.books_list[cur-1])
				curList.push_back(i);
		}
		else if (i >= IDEN_CHECK_ETC_START && i < IDEN_CHECK_ETC_END) {
			curList.push_back(i);
		}
	}



	

	changedisplay(DT_IDEN);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey, true);
		int offseta_ = max(((DisplayManager.move + 1000) / 2000),0)*52;
		int offsetb_ = max((DisplayManager.move / 2000), 0) * 52;
		if ((key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z'))
		{
			int num = ((key_ >= 'a' && key_ <= 'z') ? (key_ - 'a') + offseta_ : (key_ - 'A' + 26) + offsetb_);
			if (curList.size() >= num + 1)
			{
				iden_list.autopickup[curList[num]] = !iden_list.autopickup[curList[num]];
			}
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}	//-----이동키끝-------
		else if(key_ == -1) {
			if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if (inputedKey.isRightClick()) {
				break;
			}
		}
		else
			break;

	}
	changedisplay(DT_GAME);

}

void Weapon_Show()
{
	deletelog();
	char temp [100];
	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_WEAPON) + ": ",false,false,true,CL_normal);
	if(you.equipment[ET_WEAPON])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_WEAPON]->id,you.equipment[ET_WEAPON]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_WEAPON]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_UNARMED),true,false,true,CL_normal);
	}


	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_TANMAC) + ": ",false,false,true,CL_normal);
	if(you.throw_weapon)
	{
		sprintf_s(temp,100,"%c) %s",you.throw_weapon->id,you.throw_weapon->GetName().c_str());
		printlog(temp,true,false,true,you.throw_weapon->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE),true,false,true,CL_normal);
	}
}

void Armour_Show()
{
	deletelog();
	char temp [100];
	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_BODY) + ": ",false,false,true,CL_normal);
	if(you.equipment[ET_ARMOR])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_ARMOR]->id,you.equipment[ET_ARMOR]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_ARMOR]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE) ,true,false,true,CL_normal);
	}

	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_SHIELD) + ": ",false,false,true,CL_normal);
	if(you.equipment[ET_SHIELD])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_SHIELD]->id,you.equipment[ET_SHIELD]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_SHIELD]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE),true,false,true,CL_normal);
	}	
	
	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_HEAD) + ": ",false,false,true,CL_normal);
	if(you.equipment[ET_HELMET])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_HELMET]->id,you.equipment[ET_HELMET]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_HELMET]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE),true,false,true,CL_normal);
	}

	
	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_CLOAK) + ": ",false,false,true,CL_normal);
	if(you.equipment[ET_CLOAK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_CLOAK]->id,you.equipment[ET_CLOAK]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_CLOAK]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE),true,false,true,CL_normal);
	}

	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_HAND) + ": ",false,false,true,CL_normal);
	if(you.equipment[ET_GLOVE])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_GLOVE]->id,you.equipment[ET_GLOVE]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_GLOVE]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE),true,false,true,CL_normal);
	}

	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_FOOT) + ": ",false,false,true,CL_normal);
	if(you.equipment[ET_BOOTS])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_BOOTS]->id,you.equipment[ET_BOOTS]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_BOOTS]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE),true,false,true,CL_normal);
	}


}




void Amulet_Show()
{
	deletelog();
	char temp [100];
	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_AMULET) + "  : ",false,false,true,CL_normal);
	if(you.equipment[ET_NECK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_NECK]->id,you.equipment[ET_NECK]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_NECK]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE),true,false,true,CL_normal);
	}

	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_LEFT_RING) + "  : ",false,false,true,CL_normal);
	if(you.equipment[ET_LEFT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_LEFT]->id,you.equipment[ET_LEFT]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_LEFT]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE),true,false,true,CL_normal);
	}
	
	printlog(LocalzationManager::locString(LOC_SYSTEM_UI_RIGHT_RING) +  + ": ",false,false,true,CL_normal);
	if(you.equipment[ET_RIGHT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_RIGHT]->id,you.equipment[ET_RIGHT]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_RIGHT]->item_color());
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UI_NONE),true,false,true,CL_normal);
	}
}

void Simple_State_Show()
{	
	int penalty_ = you.as_penalty>you.GetPenaltyMinus(3)?4: //끔찍
					you.as_penalty>you.GetPenaltyMinus(2)?3: //이동패널티
					you.as_penalty>you.GetPenaltyMinus(1)?2: //명중
					you.as_penalty?1:0;
	switch(penalty_/*you.GetArmourPanlty()*/)
	{
	case 0:
		break;
	case 1:
		printlog(LocalzationManager::locString(LOC_SYSTEM_EQUIP_PANALTY1) + " ",false,false,false,CL_normal);
		break;
	case 2:
		printlog(LocalzationManager::locString(LOC_SYSTEM_EQUIP_PANALTY2) + " ",false,false,false,CL_normal);
		break;
	case 3:
		printlog(LocalzationManager::locString(LOC_SYSTEM_EQUIP_PANALTY3) + " ",false,false,false,CL_normal);
		break;
	case 4:
	default:
		printlog(LocalzationManager::locString(LOC_SYSTEM_EQUIP_PANALTY4) + " ",false,false,false,CL_normal);
		break;
	}
	enterlog();
}
void Experience_Show()
{
	printlog(LocalzationManager::formatString(LOC_SYSTEM_EXPERIENCE_SHOW_LEVEL,
		PlaceHolderHelper(to_string(you.level)),
		PlaceHolderHelper(tribe_type_string[you.tribe]),
		PlaceHolderHelper(job_type_string[you.job])),true,false,false,CL_normal);
	if(you.GetNeedExp(you.level-1) > 0)
	{
		printlog(LocalzationManager::formatString(LOC_SYSTEM_EXPERIENCE_SHOW_REMAIN,
			PlaceHolderHelper(to_string(you.GetNeedExp(you.level-1) - you.exper))),true,false,false,CL_normal);
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_EXPERIENCE_SHOW_MAX),true,false,false,CL_normal);
	}
}


void dungeonView()
{
	if(!isNormalGame())
		return;

	std::ostringstream oss;
	std::ostringstream blank;
	blank << "            ";

	int floor_ = 0;
	deletesub();
	WaitForSingleObject(mutx, INFINITE);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub(blank.str(),false,CL_warning);
	printsub("<" + LocalzationManager::locString(LOC_SYSTEM_UI_DUNGEON_VIEW) + ">",true,CL_warning);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub(blank.str(),false,CL_warning);
	printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON) + " ",false,CL_warning);
	for(int i=0;i<=MAX_DUNGEUN_LEVEL;i++)
	{
		if(env[i].make)
			floor_++;
		else
			break;
	}
	oss<<'('<<setw(2)<<setfill(' ')<<floor_<<'/'<<setw(2)<<setfill(' ')<<(MAX_DUNGEUN_LEVEL + 1)<<')';
	printsub(oss.str(),true,CL_normal);
	printsub(blank.str(),false,CL_warning);
	printsub("│",true,CL_normal);
	if(floor_>=3) //신전등장
	{
		if(map_list.dungeon_enter[TEMPLE].detected)
		{
			printsub(blank.str(),false,CL_warning);
			printsub("├",false,CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_TEMPLE) + " ",false,CL_warning);
			oss.str("");
			oss.clear();
			oss<<'('<<setw(2)<<setfill(' ')<<(env[TEMPLE_LEVEL].make?1:0)<<"/1)";
			printsub(oss.str(),false,CL_normal);
			oss.str("");
			oss.clear();
			oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[TEMPLE].floor+1)));
			printsub(oss.str(),true,CL_help);
			printsub(blank.str(),false,CL_warning);
			printsub("│",true,CL_normal);
		}
		else
		{
			printsub(blank.str(),false,CL_warning);
			printsub("├",false,CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_TEMPLE) + " ",false,CL_bad);
			oss.str("");
			oss.clear();
			oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON)<<' '<<
				LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("3"))<<'~' <<
				LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("6"));
			printsub(oss.str(),true,CL_STAT);
			printsub(blank.str(),false,CL_warning);
			printsub("│",true,CL_normal);
		}
	}	
	if(floor_>=8) //안개의호수
	{
		if(map_list.dungeon_enter[MISTY_LAKE].detected)
		{
			printsub(blank.str(),false,CL_warning);
			printsub("├",false,CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MISTYLAKE) + " ",false,CL_warning);
			int floor2_ = 0;	
			for(int i=MISTY_LAKE_LEVEL;i<=MISTY_LAKE_LAST_LEVEL;i++)
			{
				if(env[i].make)
					floor2_++;
				else
					break;
			}
			oss.str("");
			oss.clear();
			oss<<'('<<setw(2)<<setfill(' ')<<floor2_<<'/'<<setw(2)<<setfill(' ')<<(MAX_MISTY_LAKE_LEVEL+1)<<')';
			printsub(oss.str(),false,CL_normal);
				
			oss.str("");
			oss.clear();
			oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[MISTY_LAKE].floor+1)))<<' ';
			printsub(oss.str(),true,CL_help);

			if(floor2_>=2) //요괴의산
			{
				if(map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected)
				{
					printsub(blank.str(),false,CL_warning);
					printsub("│├",false,CL_normal);
					printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN) + " ",false,CL_warning);
					int floor3_ = 0;	
					for(int i=YOUKAI_MOUNTAIN_LEVEL;i<=YOUKAI_MOUNTAIN_LAST_LEVEL;i++)
					{
						if(env[i].make)
							floor3_++;
						else
							break;
					}
					oss.str("");
					oss.clear();
					oss<<'('<<setw(2)<<setfill(' ')<<floor3_<<'/'<<setw(2)<<setfill(' ')<<(MAX_YOUKAI_MOUNTAIN_LEVEL+1)<<')';
					printsub(oss.str(),false,CL_normal);
				
					oss.str("");
					oss.clear();
					oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MISTYLAKE)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[YOUKAI_MOUNTAIN].floor+1-MISTY_LAKE_LEVEL)))<<' ';
					printsub(oss.str(),false,CL_help);

					//***룬있음
					oss.str("");
					oss.clear();
					oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_YOUKAI_MOUNTAIN])<<"* ";
					printsub(oss.str(),true,you.rune[RUNE_YOUKAI_MOUNTAIN]?CL_magic:CL_bad);
					//***룬끝

					if(floor3_>=MAX_YOUKAI_MOUNTAIN_LEVEL+1) //윳쿠리굴
					{
						if(map_list.dungeon_enter[YUKKURI_D].detected)
						{
							printsub(blank.str(),false,CL_warning);
							printsub("││└",false,CL_normal);
							printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YUKKURI) + " ",false,CL_warning);
							int floor4_ = 0;	
							for(int i=YUKKURI_LEVEL;i<=YUKKURI_LAST_LEVEL;i++)
							{
								if(env[i].make)
									floor4_++;
								else
									break;
							}
							oss.str("");
							oss.clear();
							oss<<'('<<setw(2)<<setfill(' ')<<floor4_<<'/'<<setw(2)<<setfill(' ')<<(MAX_YUKKURI_LEVEL+1)<<')';
							printsub(oss.str(),false,CL_normal);
				
							oss.str("");
							oss.clear();
							oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[YUKKURI_D].floor+1-YOUKAI_MOUNTAIN_LEVEL)))<<"  ";
							printsub(oss.str(),false,CL_help);

							//***룬있음
							oss.str("");
							oss.clear();
							oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_YUKKURI])<<"* ";
							printsub(oss.str(),true,you.rune[RUNE_YUKKURI]?CL_magic:CL_bad);
							//***룬끝

							printsub(blank.str(),false,CL_warning);
							printsub("││",true,CL_normal);
						}
						else
						{
							printsub(blank.str(),false,CL_warning);
							printsub("││└",false,CL_normal);
							printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YUKKURI) +  " ",false,CL_bad);
							oss.str("");
							oss.clear();
							oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN)<<' '<<
								LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("4"));
							printsub(oss.str(),true,CL_STAT);
							printsub(blank.str(),false,CL_warning);
							printsub("││",true,CL_normal);
						}
					}
					else
					{
						printsub(blank.str(),false,CL_warning);
						printsub("││",true,CL_normal);
					}
				}
				else
				{
					printsub(blank.str(),false,CL_warning);
					printsub("│├",false,CL_normal);
					printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN) + " ",false,CL_bad);
					
					oss.str("");
					oss.clear();
					oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MISTYLAKE)<<' '<<
						LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("2")) << '~' <<
						LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("3"));
					printsub(oss.str(),true,CL_STAT);
					printsub(blank.str(),false,CL_warning);
					printsub("││",true,CL_normal);
				}


				
				if(floor2_>=4) //홍마관
				{
					if(map_list.dungeon_enter[SCARLET_M].detected)
					{
						printsub(blank.str(),false,CL_warning);
						printsub("│└",false,CL_normal);
						printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET) + " ",false,CL_warning);
						int floor3_ = 0;	
						for(int i=SCARLET_LEVEL;i<=SCARLET_LEVEL_LAST_LEVEL;i++)
						{
							if(env[i].make)
								floor3_++;
							else
								break;
						}
						oss.str("");
						oss.clear();
						oss<<'('<<setw(2)<<setfill(' ')<<floor3_<<'/'<<setw(2)<<setfill(' ')<<(MAX_SCARLET_LEVEL+1)<<')';
						printsub(oss.str(),false,CL_normal);
				
						oss.str("");
						oss.clear();
						oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MISTYLAKE)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[SCARLET_M].floor+1-MISTY_LAKE_LEVEL)))<<"  ";
						printsub(oss.str(),false,CL_help);

						//***룬있음
						oss.str("");
						oss.clear();
						oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_SCARLET])<<"* ";
						printsub(oss.str(),true,you.rune[RUNE_SCARLET]?CL_magic:CL_bad);
						//***룬끝
						
						if(floor3_>=2) //도서관
						{
							if(map_list.dungeon_enter[SCARLET_L].detected)
							{
								printsub(blank.str(),false,CL_warning);
								printsub("│  ├",false,CL_normal);
								printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET_LIBRARY) + " ",false,CL_warning);
								oss.str("");
								oss.clear();
								oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET)<<' '<<
									LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[SCARLET_L].floor+1-SCARLET_LEVEL)));
								printsub(oss.str(),true,CL_help);
							}
							else
							{
								printsub(blank.str(),false,CL_warning);
								printsub("│  ├",false,CL_normal);
								printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET_LIBRARY) + " ",false,CL_bad);
								oss.str("");
								oss.clear();
								oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET)<<' '<<
									LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("2")) << '~' <<
									LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("3"));
								printsub(oss.str(),true,CL_STAT);
							}
						}
						if(floor3_>=4) //지하실
						{
							if(map_list.dungeon_enter[SCARLET_U].detected)
							{
								printsub(blank.str(),false,CL_warning);
								printsub("│  └",false,CL_normal);
								printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET_UNDER) + " ",false,CL_warning);
				

								oss.str("");
								oss.clear();
								oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[SCARLET_U].floor+1-SCARLET_LEVEL)))<<"  ";
								printsub(oss.str(),false,CL_help);

								//***룬있음
								oss.str("");
								oss.clear();
								oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_SCARLET_UNDER])<<"* ";
								printsub(oss.str(),true,you.rune[RUNE_SCARLET_UNDER]?CL_magic:CL_bad);
								//***룬끝
							}
							else
							{
								printsub(blank.str(),false,CL_warning);
								printsub("│  └",false,CL_normal);
								printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET_UNDER) + " ",false,CL_bad);
								
								oss.str("");
								oss.clear();
								oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET)<<' '<<
									LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("4"));
								printsub(oss.str(),true,CL_STAT);
							}
						}

						printsub(blank.str(),false,CL_warning);
						printsub("│",true,CL_normal);
					}
					else
					{
						printsub(blank.str(),false,CL_warning);
						printsub("│└",false,CL_normal);
						printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET) + " ",false,CL_bad);
						oss.str("");
						oss.clear();
						oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MISTYLAKE)<<' '<<
							LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("4")) << '~' <<
							LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("5"));
						printsub(oss.str(),true,CL_STAT);
						printsub(blank.str(),false,CL_warning);
						printsub("│",true,CL_normal);
					}

				}

			}
			else
			{
				printsub(blank.str(),false,CL_warning);
				printsub("│",true,CL_normal);
			}
		}
		else
		{
			printsub(blank.str(),false,CL_warning);
			printsub("├",false,CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MISTYLAKE) + " ",false,CL_bad);
			oss.str("");
			oss.clear();
			oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON)<<' '<<
				LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("8")) << '~' <<
				LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("10"));
			printsub(oss.str(),true,CL_STAT);
			printsub(blank.str(),false,CL_warning);
			printsub("│",true,CL_normal);
		}
	}
	
	if(floor_>=11) //미궁의 죽림
	{
		if(map_list.dungeon_enter[BAMBOO].detected)
		{
			printsub(blank.str(),false,CL_warning);
			printsub("├",false,CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_BAMBOO) + " ",false,CL_warning);
			

			oss.str("");
			oss.clear();
			oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[BAMBOO].floor+1)));
			printsub(oss.str(),true,CL_help);

			{
				if(env[EIENTEI_LEVEL].make)
				{
					printsub(blank.str(),false,CL_warning);
					printsub("│└",false,CL_normal);
					printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_EINENTEI) + " ",false,CL_warning);
				
					printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_BAMBOO) + "  ",false,CL_help);

					//***룬있음
					oss.str("");
					oss.clear();
					oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_EIENTEI])<<"* ";
					printsub(oss.str(),true,you.rune[RUNE_EIENTEI]?CL_magic:CL_bad);
					//***룬끝
				}
				else
				{
					printsub(blank.str(),false,CL_warning);
					printsub("│└",false,CL_normal);
					printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_EINENTEI) + " ",false,CL_bad);
					printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_BAMBOO),true,CL_STAT);
				}
			}

			printsub(blank.str(),false,CL_warning);
			printsub("│",true,CL_normal);
		}
		else
		{
			printsub(blank.str(),false,CL_warning);
			printsub("├",false,CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_BAMBOO) + " ",false,CL_bad);
			oss.str("");
			oss.clear();
			oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON)<<' '<<
				LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("11")) << '~' <<
				LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("14"));
			printsub(oss.str(),true,CL_STAT);
			printsub(blank.str(),false,CL_warning);
			printsub("│",true,CL_normal);
		}
	}




	
	if(floor_==MAX_DUNGEUN_LEVEL+1) //짐승길
	{
		if(map_list.dungeon_enter[DEPTH].detected)
		{
			printsub(blank.str(),false,CL_warning);
			printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH) + " ",false,CL_warning);
				
			
			int floor2_ = 0;	
			for(int i=DEPTH_LEVEL;i<=DEPTH_LAST_LEVEL;i++)
			{
				if(env[i].make)
					floor2_++;
				else
					break;
			}
			oss.str("");
			oss.clear();
			oss<<'('<<setw(2)<<setfill(' ')<<floor2_<<'/'<<setw(2)<<setfill(' ')<<(MAX_DEPTH_LEVEL+1)<<')';
			printsub(oss.str(),false,CL_normal);

			oss.str("");
			oss.clear();
			oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[DEPTH].floor+1)))<<"  ";
			printsub(oss.str(),true,CL_help);

			printsub(blank.str(),false,CL_warning);
			printsub("│",true,CL_normal);

			bool see_[3];

			for(int i = 0 ; i < 3; i++)
				see_[i]=false;
			if(floor2_>=2)
			{
				for(int level_=0;level_<floor2_+1;level_++)
				{
					bool unsee = (level_ == floor2_);
					if(!see_[0] && ((map_list.dungeon_enter[DREAM_D].detected && 					
						map_list.dungeon_enter[DREAM_D].floor - DEPTH_LEVEL == level_)  || 
						unsee))//꿈의 세계
					{

						if(map_list.dungeon_enter[DREAM_D].detected)
						{
							printsub(blank.str(),false,CL_warning);
							printsub("├",false,CL_normal);
							printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DREAM) + " ",false,CL_warning);
				


							oss.str("");
							oss.clear();
							oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[DREAM_D].floor+1-DEPTH_LEVEL)))<<"  ";
							printsub(oss.str(),true,CL_help);
						
							if(env[DREAM_LEVEL].make)
							{
								if(env[MOON_LEVEL].make) //달의 도시
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MOON) + " ",false,CL_warning);
				
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DREAM) + "  ",false,CL_help);

									//***룬있음
									oss.str("");
									oss.clear();
									oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_MOON])<<"* ";
									printsub(oss.str(),true,you.rune[RUNE_MOON]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MOON) + " ",false,CL_bad);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DREAM) + " ",true,CL_STAT);
								}
							}
							printsub(blank.str(),false,CL_warning);
							printsub("│",true,CL_normal);
						}
						else
						{
							printsub(blank.str(),false,CL_warning);
							printsub("├",false,CL_normal);
							printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DREAM) + " ",false,CL_bad);
							
							oss.str("");
							oss.clear();
							oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH)<<' '<<
								LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("2")) << '~' <<
								LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("4"));
							printsub(oss.str(),true,CL_STAT);
							printsub(blank.str(),false,CL_warning);
							printsub("│",true,CL_normal);
						}
						see_[0] = true;
					}

					if(!see_[1] && ((map_list.dungeon_enter[SUBTERRANEAN].detected && 					
						map_list.dungeon_enter[SUBTERRANEAN].floor - DEPTH_LEVEL == level_)  || 
						unsee))//지저
					{
						if(map_list.dungeon_enter[SUBTERRANEAN].detected)
						{
							printsub(blank.str(),false,CL_warning);
							printsub("├",false,CL_normal);
							printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SUBTERRANEAN) + " ",false,CL_warning);
							int floor3_ = 0;	
							for(int i=SUBTERRANEAN_LEVEL;i<=SUBTERRANEAN_LEVEL_LAST_LEVEL;i++)
							{
								if(env[i].make)
									floor3_++;
								else
									break;
							}
							oss.str("");
							oss.clear();
							oss<<'('<<setw(2)<<setfill(' ')<<floor3_<<'/'<<setw(2)<<setfill(' ')<<(MAX_SUBTERRANEAN_LEVEL+1)<<')';
							printsub(oss.str(),false,CL_normal);
				
							oss.str("");
							oss.clear();
							oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[SUBTERRANEAN].floor+1-DEPTH_LEVEL)))<<"  ";
							printsub(oss.str(),true,CL_help);

							if(env[SUBTERRANEAN_LEVEL].make)
							{
								if(env[SUBTERRANEAN_LEVEL_LAST_LEVEL].make) //작열지옥터
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SUBRERRANEAN_LAST) + " ",false,CL_warning);
				
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SUBRERRANEAN_LAST) + " " + LocalzationManager::locString(LOC_SYSTEM_DUNGEON_LAST_FLOOR) + "  ",false,CL_help);

									//***룬있음
									oss.str("");
									oss.clear();
									oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_SUBTERRANEAN])<<"* ";
									printsub(oss.str(),true,you.rune[RUNE_SUBTERRANEAN]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SUBRERRANEAN_LAST) + " ",false,CL_bad);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SUBRERRANEAN_LAST) + " " + LocalzationManager::locString(LOC_SYSTEM_DUNGEON_LAST_FLOOR) + " ",true,CL_STAT);
								}
							}


							printsub(blank.str(),false,CL_warning);
							printsub("│",true,CL_normal);
						}
						else
						{
							printsub(blank.str(),false,CL_warning);
							printsub("├",false,CL_normal);
							printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SUBTERRANEAN) + " ",false,CL_bad);
							oss.str("");
							oss.clear();
							oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH)<<' '<<
								LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("2")) << '~' <<
								LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("4"));
							printsub(oss.str(),true,CL_STAT);
							printsub(blank.str(),false,CL_warning);
							printsub("│",true,CL_normal);
						}
						see_[1] = true;
					}


					if(!see_[2] && ((map_list.dungeon_enter[PANDEMONIUM].detected && 					
						map_list.dungeon_enter[PANDEMONIUM].floor - DEPTH_LEVEL == level_)  || 
						unsee))//마계
					{
						if(map_list.dungeon_enter[PANDEMONIUM].detected)
						{
							printsub(blank.str(),false,CL_warning);
							printsub("├",false,CL_normal);
							printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM) + " ",false,CL_warning);
				
							oss.str("");
							oss.clear();
							oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[PANDEMONIUM].floor+1-DEPTH_LEVEL)))<<"  ";
							printsub(oss.str(),true,CL_help);

							if(env[PANDEMONIUM_LEVEL].make)
							{
								if(env[PANDEMONIUM_LEVEL+1].make) //법계
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│├",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_HOKKAI) + " ",false,CL_warning);
				
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM) + "  ",false,CL_help);

									//***룬있음
									oss.str("");
									oss.clear();
									oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_PANDEMONIUM_MAGIC])<<"* ";
									printsub(oss.str(),true,you.rune[RUNE_PANDEMONIUM_MAGIC]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│├",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_HOKKAI) + " ",false,CL_bad);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM) + " ",true,CL_STAT);
								}
								if(env[PANDEMONIUM_LEVEL+2].make) //빙결세계
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│├",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_FROZEN_FIELD) + " ",false,CL_warning);
				
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM) + "  ",false,CL_help);

									//***룬있음
									oss.str("");
									oss.clear();
									oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_PANDEMONIUM_ICE])<<"* ";
									printsub(oss.str(),true,you.rune[RUNE_PANDEMONIUM_ICE]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│├",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_FROZEN_FIELD) + " ",false,CL_bad);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM) + " ",true,CL_STAT);
								}
								if(env[PANDEMONIUM_LEVEL+3].make) //판데모니엄
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM_LAST) + " ",false,CL_warning);
				
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM) + "  ",false,CL_help);

									//***룬있음
									oss.str("");
									oss.clear();
									oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_PANDEMONIUM_SHINKI])<<"* ";
									printsub(oss.str(),true,you.rune[RUNE_PANDEMONIUM_SHINKI]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank.str(),false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM_LAST) + " ",false,CL_bad);
									printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM) + " ",true,CL_STAT);
								}
							}
							printsub(blank.str(),false,CL_warning);
							printsub("│",true,CL_normal);
						}
						else
						{
							printsub(blank.str(),false,CL_warning);
							printsub("├",false,CL_normal);
							printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM) + " ",false,CL_bad);
							
							oss.str("");
							oss.clear();
							oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH)<<' '<<
								LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("2")) << '~' <<
								LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("4"));
							printsub(oss.str(),true,CL_STAT);
							printsub(blank.str(),false,CL_warning);
							printsub("│",true,CL_normal);
						}
						see_[2] = true;
					}
				}
			}

			if(floor2_ >= MAX_DEPTH_LEVEL+1)
			{
				if(map_list.dungeon_enter[HAKUREI_D].detected)
				{
					printsub(blank.str(),false,CL_warning);
					printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_HAKUREI) + " ",false,CL_warning);
					int floor4_ = 0;	
					for(int i=HAKUREI_LEVEL;i<=HAKUREI_LAST_LEVEL;i++)
					{
						if(env[i].make)
							floor4_++;
						else
							break;
					}
					oss.str("");
					oss.clear();
					oss<<'('<<setw(2)<<setfill(' ')<<floor4_<<'/'<<setw(2)<<setfill(' ')<<(MAX_HAKUREI_LEVEL+1)<<')';
					printsub(oss.str(),false,CL_normal);
				
					oss.str("");
					oss.clear();
					oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH)<<' '<<LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(map_list.dungeon_enter[HAKUREI_D].floor+1-DEPTH_LEVEL)))<<"  ";
					printsub(oss.str(),false,CL_help);

					//***룬있음
					oss.str("");
					oss.clear();
					oss<<"*"<<LocalzationManager::locString(rune_string[RUNE_HAKUREI_ORB])<<"* ";
					printsub(oss.str(),true,you.rune[RUNE_HAKUREI_ORB]?CL_danger:CL_bad);
					//***룬끝
				}
				else
				{
					printsub(blank.str(),false,CL_warning);
					printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_HAKUREI) + " ",false,CL_bad);
					oss.str("");
					oss.clear();
					oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH)<<' '<<
						LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("5"));
					printsub(oss.str(),true,CL_STAT);
				}
			}
		}
		else
		{
			printsub(blank.str(),false,CL_warning);
			printsub(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH) + " ",false,CL_bad);
			oss.str("");
			oss.clear();
			oss<<LocalzationManager::locString(LOC_SYSTEM_DUNGEON)<<' '<<
				LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper("15"));
			printsub(oss.str(),true,CL_STAT);
		}




	}


	
	ReleaseMutex(mutx);
	
	changedisplay(DT_SUB_TEXT);
	
	setDisplayMove(DisplayManager.max_y);
	
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey, true);

		if(key_ == VK_UP)
		{
			changemove(1);  //위
		}
		else if(key_ == VK_DOWN)
		{
			changemove(-1); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(DisplayManager.log_length);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(-DisplayManager.log_length);
		}
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(1);  //위
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(-1); //아래
			} else if(inputedKey.isLeftClick() || inputedKey.isRightClick()) {
				break;
			}
		}
		else
		{
			break;
		}
	}


	changedisplay(DT_GAME);
	deletesub();

}


void More_Item_Action()
{
	const int max_command = 13;
	vector<int> selectionList;
	pair<pair<int,char>,LOCALIZATION_ENUM_KEY> command_list[max_command] = {
		make_pair(make_pair(SPECIAL_CLINKABLE_INVENTORY,'i'),LOC_SYSTEM_INVENTORY),
		make_pair(make_pair(SPECIAL_CLINKABLE_DISCARD,'d'),LOC_SYSTEM_DISCARD),
		make_pair(make_pair(SPECIAL_CLINKABLE_EAT,'e'),LOC_SYSTEM_EAT),
		make_pair(make_pair(SPECIAL_CLINKABLE_READ,'r'),LOC_SYSTEM_READ),
		make_pair(make_pair(SPECIAL_CLINKABLE_DRINK,'q'),LOC_SYSTEM_DRINK),
		make_pair(make_pair(SPECIAL_CLINKABLE_THROW,'F'),LOC_SYSTEM_THROW),
		make_pair(make_pair(SPECIAL_CLINKABLE_EVOKE,'V'),LOC_SYSTEM_EVOKE),		
		make_pair(make_pair(SPECIAL_CLINKABLE_EQUIP_WEAPON,'w'),LOC_SYSTEM_EQUIP_WEAPON),
		make_pair(make_pair(SPECIAL_CLINKABLE_UNEQUIP_WEAPON,'-'),LOC_SYSTEM_UNEQUIP_WEAPON),
		make_pair(make_pair(SPECIAL_CLINKABLE_EQUIP_ARMOUR,'W'),LOC_SYSTEM_EQUIP_ARMOUR),
		make_pair(make_pair(SPECIAL_CLINKABLE_UNEQUIP_ARMOUR,'T'),LOC_SYSTEM_UNEQUIP_ARMOUR),
		make_pair(make_pair(SPECIAL_CLINKABLE_EQUIP_JEWELRY,'P'),LOC_SYSTEM_EQUIP_JEWELRY),
		make_pair(make_pair(SPECIAL_CLINKABLE_UNEQUIP_JEWELRY,'R'),LOC_SYSTEM_UNEQUIP_JEWELRY)
	};
	
	enterlog();
	printlog("<<<" + LocalzationManager::locString(LOC_SYSTEM_ITEM_COMMAND) + ">>>",true,false,true,CL_help);
	
	bool first_ = true;
	for(int i = 0; i < max_command; i++) {
		if(!first_)
			printlog(" ",false,false,true,CL_normal);
		ostringstream ss;
		ss << command_list[i].first.second << "-" <<  LocalzationManager::locString(command_list[i].second);
		printlog(ss.str(),false,false,true,CL_normal,command_list[i].first.second);
		first_ = false;
		selectionList.push_back(command_list[i].first.first);
	}
	
	selectionList.push_back(VK_ESCAPE);
	bool loop_ = true;
	startSelection(selectionList);
	while(loop_) {
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey, true);

		if(key_ == VK_RETURN || key_ == '?' || key_ == GVK_BUTTON_A)
		{
			if(g_menu_select != -1 && g_menu_select <= max_command) {
				if(g_menu_select == max_command) {
					key_ = VK_ESCAPE;
				}
				else {
					key_ = command_list[g_menu_select].first.second;
				}
			} 
		}

		switch(key_)
		{
		case VK_UP:
			if(g_menu_select >= greed_max_x) {
				g_menu_select -= greed_max_x;
			}
			if(g_menu_select==-1)
				g_menu_select = 0;
			continue;
		case VK_DOWN:
			if(g_menu_select >= 0 && g_menu_select < greed_max_x-1) {
				g_menu_select += greed_max_x;
			}
			if(g_menu_select==-1)
				g_menu_select = 0;
			continue;
		case VK_LEFT:
			if(g_menu_select > 0) {
				g_menu_select--;
			}
			if(g_menu_select==-1)
				g_menu_select = 0;
			continue;
		case VK_RIGHT:
			if(g_menu_select >= 0 && g_menu_select < greed_max_x*2-1) {
				g_menu_select++;
			}
			if(g_menu_select==-1)
				g_menu_select = 0;
			continue;
		case 'i':
			endSelection();
			deletelog();
			iteminfor();
			g_menu_select = -1;
			return;
		case 'd':
			endSelection();
			deletelog();
			iteminfor_discard();
			g_menu_select = -1;
			return;
		case 'e':
			endSelection();
			deletelog();
			Eatting(0);
			g_menu_select = -1;
			return;
		case 'r':
			endSelection();
			deletelog();
			Reading(0);
			g_menu_select = -1;
			return;
		case 'q':
			endSelection();
			deletelog();
			Drinking(0);
			g_menu_select = -1;
			return;
		case 'F':
			endSelection();
			deletelog();
			Select_Throw();
			g_menu_select = -1;
			return;
		case 'V':
			endSelection();
			deletelog();
			Spelllcard_Evoke(0);
			g_menu_select = -1;
			return;
		case 'w':
			endSelection();
			deletelog();
			Equip_Weapon();
			g_menu_select = -1;
			return;
		case '-':
			endSelection();
			deletelog();
			if(!you.unequip(ET_WEAPON))
			{				
				printlog(LocalzationManager::locString(LOC_SYSTEM_CURSED_PENALTY),true,false,false,CL_normal);
			}
			g_menu_select = -1;
			return;
		case 'W':
			endSelection();
			deletelog();
			Equip_Armor();
			g_menu_select = -1;
			return;
		case 'T':
			endSelection();
			deletelog();
			Unequip_Armor();
			g_menu_select = -1;
			return;
		case 'P':
			endSelection();
			deletelog();
			Equip_Jewelry();
			g_menu_select = -1;
			return;
		case 'R':
			endSelection();
			deletelog();
			Unequip_Jewelry();
			g_menu_select = -1;
			return;
		case -1:
			{
				if(inputedKey.isRightClick()) {
					//breakthrough
				} else {
					break;
				}
			}
		case VK_ESCAPE:
		case GVK_BUTTON_B:
		case GVK_BUTTON_B_LONG:
			loop_ = false;
			break;
		default:
			break;
		}
	}
	endSelection();
	deletelog();
	g_menu_select = -1;
}


void More_Information_List()
{
	const int max_command = 10;
	vector<int> selectionList;
	pair<pair<int,char>,LOCALIZATION_ENUM_KEY> command_list[max_command] = {
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_CHARACTER,'@'),LOC_SYSTEM_INFORMATION_CHARACTER),
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_FAITH,'^'),LOC_SYSTEM_INFORMATION_FAITH),
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_INDENTIFY,'\\'),LOC_SYSTEM_INFORMATION_INDENTIFY),
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_PROPERTY,'A'),LOC_SYSTEM_INFORMATION_PROPERTY),
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_SPELL,'I'),LOC_SYSTEM_INFORMATION_SPELL),
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_LEARN_SPELL,'M'),LOC_SYSTEM_INFORMATION_LEARN_SPELL),
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_RUNE,']'),LOC_SYSTEM_INFORMATION_RUNE),
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_DUNGEON,'O'),LOC_SYSTEM_INFORMATION_DUNGEON),
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_LOG,'P'),LOC_SYSTEM_INFORMATION_LOG),
		make_pair(make_pair(SPECIAL_CLINKABLE_INFORMATION_DUMP,'#'),LOC_SYSTEM_INFORMATION_DUMP)
	};
	
	enterlog();
	printlog("<<<" + LocalzationManager::locString(LOC_SYSTEM_INFORMATION_COMMAND) + ">>>",true,false,true,CL_help);
	
	bool first_ = true;
	for(int i = 0; i < max_command; i++) {
		if(!isNormalGame() && command_list[i].second == LOC_SYSTEM_INFORMATION_DUNGEON)
			continue;
		if(!first_)
			printlog(" ",false,false,true,CL_normal);
		ostringstream ss;
		ss << command_list[i].first.second << "-" <<  LocalzationManager::locString(command_list[i].second);
		printlog(ss.str(),false,false,true,CL_normal,command_list[i].first.second);
		first_ = false;
		selectionList.push_back(command_list[i].first.first);
	}
	selectionList.push_back(VK_ESCAPE);
	bool loop_ = true;
	startSelection(selectionList);
	while(loop_) {		
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);

		if(key_ == VK_RETURN || key_ == '?' || key_ == GVK_BUTTON_A)
		{
			if(g_menu_select != -1 && g_menu_select <= max_command) {
				if(g_menu_select == max_command) {
					key_ = VK_ESCAPE;
				}
				else {
					key_ = command_list[g_menu_select].first.second;
				}
			} 
		}

		switch(key_)
		{
		case VK_UP:
			if(g_menu_select >= greed_max_x) {
				g_menu_select -= greed_max_x;
			}
			if(g_menu_select==-1)
				g_menu_select = 0;
			continue;
		case VK_DOWN:
			if(g_menu_select >= 0 && g_menu_select < greed_max_x-1) {
				g_menu_select += greed_max_x;
			}
			if(g_menu_select==-1)
				g_menu_select = 0;
			continue;
		case VK_LEFT:
			if(g_menu_select > 0) {
				g_menu_select--;
			}
			if(g_menu_select==-1)
				g_menu_select = 0;
			continue;
		case VK_RIGHT:
			if(g_menu_select >= 0 && g_menu_select < greed_max_x*2-1) {
				g_menu_select++;
			}
			if(g_menu_select==-1)
				g_menu_select = 0;
			continue;
		case '@':
			endSelection();
			deletelog();
			stat_view();
			g_menu_select = -1;
			return;
		case '^':
			endSelection();
			deletelog();
			God_show();
			g_menu_select = -1;
			return;
		case '\\':
			endSelection();
			deletelog();
			Iden_Show();
			g_menu_select = -1;
			return;
		case 'A':
			endSelection();
			deletelog();
			PropertyView();
			g_menu_select = -1;
			return;
		case 'I':
			endSelection();
			deletelog();
			SpellView();
			g_menu_select = -1;
			return;
		case 'M':
			endSelection();
			deletelog();
			run_spell();
			g_menu_select = -1;
			return;
		case ']':
			endSelection();
			deletelog();
			rune_Show();
			g_menu_select = -1;
			return;
		case 'O':
			endSelection();
			deletelog();
			if(isNormalGame())
				dungeonView();
			g_menu_select = -1;
			return;
		case 'P':
			endSelection();
			deletelog();
			view_log();
			g_menu_select = -1;
			return;
		case '#':
			endSelection();
			deletelog();
			if(Dump(0,NULL))
				printlog(LocalzationManager::locString(LOC_SYSTEM_DUMP_SUCCESS),true,false,false,CL_normal);
			g_menu_select = -1;
			return;
		case -1:
			{
				if(inputedKey.isRightClick()) {
					//breakthrough
				} else {
					break;
				}
			}
		case VK_ESCAPE:
		case GVK_BUTTON_B:
		case GVK_BUTTON_B_LONG:
			loop_ = false;
			break;
		default:
			break;
		}
	}
	endSelection();
	deletelog();
	g_menu_select = -1;
}




void memorize_action(int spell_);



void run_spell() //만약 마법레벨이 52개를 넘어간다면 배울수없다?
{		
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY),true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_LEARN_SPELL), true, false, false, CL_normal);
		return;
	}
	deletesub();
	for(int i=0;i<2;i++)
		printsub("",true,CL_STAT); 
	{	
		printsub(LocalzationManager::formatString(LOC_SYSTEM_UI_LEARN_SPELL_REMAIN, PlaceHolderHelper(to_string(you.currentSpellNum)),
			PlaceHolderHelper(to_string(you.remainSpellPoiont))),true,CL_help);
	}
	for(int i=0;i<1;i++)
		printsub("",true,CL_STAT);

	int offset[5] = {7, 14, 35, 65, 85};
	int cur_ = 0;

	cur_ = printsub_blank(0, offset[0]);
	cur_ += printsub_utf8witdh(LocalzationManager::locString(LOC_SYSTEM_HOTKEY),false,CL_STAT);
	cur_ = printsub_blank(cur_, offset[1]);
	cur_ += printsub_utf8witdh("- " + LocalzationManager::locString(LOC_SYSTEM_NAME),false,CL_STAT);
	cur_ = printsub_blank(cur_, offset[2]);
	cur_ += printsub_utf8witdh(LocalzationManager::locString(LOC_SYSTEM_SCHOOL),false,CL_STAT);
	cur_ = printsub_blank(cur_, offset[3]);
	cur_ += printsub_utf8witdh(LocalzationManager::locString(LOC_SYSTEM_FAILURE_RATE),false,CL_STAT);
	cur_ = printsub_blank(cur_, offset[4]);
	printsub(LocalzationManager::locString(LOC_SYSTEM_LEVEL),true,CL_STAT);




	set<int> set_skill;
	multimap<int,int> map_skill;


	for(list<item>::iterator it = you.item_list.begin();it!=you.item_list.end();it++)
	{
		if(it->type == ITM_BOOK)
		{
			if(it->value0>=0)
			{
				iden_list.books_list[it->value0] = true;
				it->identify = true;
			}
			if(it->value0==-2)
			{
				it->identify = true;
			}
			if(it->value1 != SPL_NONE && !you.isMemorizeSpell(it->value1))
				set_skill.insert(it->value1);
			if(it->value2 != SPL_NONE && !you.isMemorizeSpell(it->value2))
				set_skill.insert(it->value2);
			if(it->value3 != SPL_NONE && !you.isMemorizeSpell(it->value3))
				set_skill.insert(it->value3);
			if(it->value4 != SPL_NONE && !you.isMemorizeSpell(it->value4))
				set_skill.insert(it->value4);
			if(it->value5 != SPL_NONE && !you.isMemorizeSpell(it->value5))
				set_skill.insert(it->value5);
			if(it->value6 != SPL_NONE && !you.isMemorizeSpell(it->value6))
				set_skill.insert(it->value6);
			if(it->value7 != SPL_NONE && !you.isMemorizeSpell(it->value7))
				set_skill.insert(it->value7);
			if(it->value8 != SPL_NONE && !you.isMemorizeSpell(it->value8))
				set_skill.insert(it->value8);
		}
	}
	for (set<int>::iterator it=set_skill.begin();it!=set_skill.end();it++) 
		map_skill.insert(pair<int,int>(100-you.GetSpellSuccess((*it)),(*it)));

	char sp_char='a';
	for (multimap<int,int>::iterator it=map_skill.begin();it!=map_skill.end();it++) 
	{

		int miscast_level_ = SpellMiscastingLevel(SpellLevel((spell_list)it->second), 100-you.GetSpellSuccess((spell_list)it->second));
		D3DCOLOR spell_color_ = (miscast_level_==3?CL_danger:
			(miscast_level_==2?CL_small_danger:
			(miscast_level_==1?CL_warning:CL_STAT)));
		if(!you.CanMemorizeSpell(it->second)) {
			spell_color_ = CL_bad;
		}
		ostringstream oss;

		add_stringblank(oss, offset[0]);
		oss << std::string(1, sp_char);
		add_stringblank(oss, offset[1]);
		oss << "- " << SpellString((spell_list)it->second);
		add_stringblank(oss, offset[2]);
		for(int j=0;j<3 && SpellSchool((spell_list)it->second,j) != SKT_ERROR;j++)
		{
			if(j)
			{
				oss << "/";
			}
			oss << skill_string(SpellSchool((spell_list)it->second,j));
		}
		add_stringblank(oss, offset[3]);
		{
			oss << std::setw(3) << it->first << '%';
		}
		add_stringblank(oss, offset[4]);
		oss << to_string(SpellLevel((spell_list)it->second));
		printsub(oss.str(),true,spell_color_, sp_char);





		if(sp_char=='z')
			sp_char = 'A';
		else if(sp_char=='Z')
			break;
		else
			sp_char++;
	}


	changedisplay(DT_SUB_TEXT);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey, true);

		if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
			int char_ = DisplayManager.positionToChar();
			if(char_) {
				if(key_ == GVK_BUTTON_A_LONG) {
					inputedKey.mouse = MKIND_ITEM_DESCRIPTION;
					inputedKey.val1 = char_;
					key_ = -1;
				} else {
					key_ = char_;
				}
			}
		}

		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
			int spell_ = SPL_NONE;
			for (multimap<int,int>::iterator it=map_skill.begin();it!=map_skill.end();it++) 
			{
				if(!(num--))
				{
					spell_ = it->second;
					break;
				}
			}
			if (you.isMemorize(spell_)) {
				changedisplay(DT_GAME);
				printlog(LocalzationManager::locString(LOC_SYSTEM_MEMORIZE_SPELL_ALREADY), true, false, false, CL_normal);
				return;
			}

			memorize_action(spell_);
			break;
		}
		else if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
		}
		else if(key_ == VK_DOWN)
		{
			DisplayManager.addPosition(1);
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(DisplayManager.log_length);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(-DisplayManager.log_length);
		}
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {				
				int num = asctonum(inputedKey.val1);
				int spell_ = SPL_NONE;
				for (multimap<int,int>::iterator it=map_skill.begin();it!=map_skill.end();it++) 
				{
					if(!(num--))
					{
						spell_ = it->second;
						break;
					}
				}
				if(spell_ != SPL_NONE)
				{
					WaitForSingleObject(mutx, INFINITE);					
					int get_item_move_ = getDisplayMove();
					SetText() = GetSpellInfor((spell_list)spell_);
					ReleaseMutex(mutx);
					changedisplay(DT_TEXT);
					waitkeyinput();
					changedisplay(DT_SUB_TEXT);
					setDisplayMove(get_item_move_);
				}
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(1);  //위
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(-1); //아래
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE || 
			key_ ==GVK_BUTTON_B ||
			key_ ==GVK_BUTTON_B_LONG)
		{
			break;
		}
	}
	changedisplay(DT_GAME);
	deletesub();
}
void shout(char auto_)
{	
	if(env[current_level].isSilence(you.position))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SILENCE_PENALTY),true,false,false,CL_normal);
		return;
	}
	int rare_shout = 0;
	string shout_ = LocalzationManager::locString(LOC_SYSTEM_SHOUT);
	if(randA(50)<1)
	{
		rare_shout = randA_1(5);
		switch(rare_shout)
		{
		case 1:
			shout_ = LocalzationManager::locString(LOC_SYSTEM_SHOUT_RARE1);
			break;
		case 2:
			shout_ = LocalzationManager::locString(LOC_SYSTEM_SHOUT_RARE2);
			break;
		case 3:
			shout_ = LocalzationManager::locString(LOC_SYSTEM_SHOUT_RARE3);
			break;
		case 4:
			shout_ = LocalzationManager::locString(LOC_SYSTEM_SHOUT_RARE4);
			break;
		case 5:
			shout_ = LocalzationManager::locString(LOC_SYSTEM_SHOUT_RARE5);
			break;
		}
	}
	if (you.drowned)
	{
		rare_shout = 1;
		shout_ = LocalzationManager::locString(LOC_SYSTEM_SHOUT_DROWNED);
	}

	if (auto_ == 0) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_SHOUT_MENU), true, false, false, CL_help);
		printlog("t - " + shout_, true, false, false, CL_normal, 't');
		{
			ostringstream oss;
			oss << LocalzationManager::locString(LOC_SYSTEM_SHOUT_MENU_ALLY) << " : ";
			printlog(oss.str(), false, false, false, CL_normal);
		}
		printlog("a - " + LocalzationManager::locString(LOC_SYSTEM_SHOUT_MENU_ATTACK), false, false, false, CL_normal, 'a');
		printlog("   ", false, false, false, CL_normal);
		printlog("s - " + LocalzationManager::locString(LOC_SYSTEM_SHOUT_MENU_STOP), true, false, false, CL_normal, 's');
		{
			ostringstream oss;
			oss << "                ";
			printlog(oss.str(), false, false, false, CL_normal);
		}
		printlog("w - " + LocalzationManager::locString(LOC_SYSTEM_SHOUT_MENU_WAIT), false, false, false, CL_normal, 'w');
		printlog("   ", false, false, false, CL_normal);
		printlog("f - " + LocalzationManager::locString(LOC_SYSTEM_SHOUT_MENU_COME), true, false, false, CL_normal, 'f');
		{
			ostringstream oss;
			oss << LocalzationManager::locString(LOC_SYSTEM_SHOUT_MENU_OTHRE) << " - " << LocalzationManager::locString(LOC_SYSTEM_SHOUT_MENU_SILENCE);
			printlog(oss.str(), true, false, false, CL_normal, VK_ESCAPE);
		}
		startSelection({'t', 'a', 's', 'w', 'f', VK_ESCAPE});
	}

	int key_ = auto_;
	g_menu_select = -1;


	if (key_ == 0) {
		while(true) {
			key_ = waitkeyinput(true);

			if(key_ == VK_RIGHT){
				if(++g_menu_select>5)
					g_menu_select = 0;
				continue;
			} else if (key_ == VK_LEFT) {
				if(--g_menu_select<0)
					g_menu_select = 5;
				continue;
			} else if(key_ == VK_RETURN || key_ == GVK_BUTTON_A) {
				switch(g_menu_select) {
					case 0:
						key_ = 't';
						break;
					case 1:
						key_ = 'a';
						break;
					case 2:
						key_ = 's';
						break;
					case 3:
						key_ = 'w';
						break;
					case 4:
						key_ = 'f';
						break;
					default:
						break;
				}
			}
			endSelection();
			break;
		}
	}
	g_menu_select = -1;


	
	switch(key_)
	{
	case 't':
		if(!rare_shout)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOUT_FINISH),true,false,false,CL_normal);
		else
			printlog(shout_,true,false,false,CL_normal);
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		Noise(you.position, 12);
		you.SetPrevAction('t', 't');
		break;
	case 'a':	
		{
			if (auto_ == 0) {
				printlog(LocalzationManager::locString(LOC_SYSTEM_SHOUT_WHO), true, false, false, CL_help);
			}
			beam_iterator beam(you.position,you.position);
			projectile_infor infor(8,false,true, -3);
			auto it = you.item_list.end();
			if(Common_Throw(it, you.GetTargetIter(), beam, &infor,-1, 0.0f, auto_>0))
			{
				if(unit* target = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y))
				{
					if(!target->isUserAlly())
					{
						for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
						{
							if(it->isLive() && it->isUserAlly() && env[current_level].isInSight(it->position) && target != &(*it))
							{
							
								it->FoundTarget(target, it->FoundTime());
								it->state.SetState(MS_ATACK);
								it->will_move.clear();
							}
						}
					}
					printlog(LocalzationManager::locString(LOC_SYSTEM_SHOUT_ATTACK),true,false,false,CL_normal);
					you.time_delay += you.GetNormalDelay();
					you.TurnEnd();
					//Noise(you.position, 12);
					you.SetPrevAction('t', 'a');
				}
			}
			break;
		}
	case 's':
		for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
		{
			if(it->isLive() && it->isUserAlly() && env[current_level].isInSight(it->position))
			{
				it->target = NULL;
				it->target_pos = you.position;
				it->state.SetState(MS_NORMAL);
				it->will_move.clear();
			}
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_SHOUT_STOP),true,false,false,CL_normal);
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		//Noise(you.position, 12);
		you.SetPrevAction('t', 's');
		break;
	case 'w':
		for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if (it->isLive() && it->isUserAlly() && env[current_level].isInSight(it->position))
			{
				it->target = NULL;
				it->first_position = it->position;
				//it->target_pos = you.position;
				it->state.SetState(MS_WAIT);
				it->will_move.clear();
			}
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_SHOUT_WAIT),true,false,false,CL_normal);
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		you.SetPrevAction('t', 'w');
		break;
	case 'f':
		for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if (it->isLive() && it->isUserAlly() && env[current_level].isInSight(it->position))
			{
				it->state.SetState(MS_FOLLOW);
				it->will_move.clear();
			}
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_SHOUT_COME),true,false,false,CL_normal);
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		you.SetPrevAction('t', 'f');
		break;
	default:
	case GVK_BUTTON_B:
	case GVK_BUTTON_B_LONG:
		printlog(LocalzationManager::locString(LOC_SYSTEM_SHOUT_CANCLE),true,false,false,CL_normal);
		break;
	}
}

void auto_pick_onoff(bool auto_)
{
	if((you.auto_pickup==0) || (!auto_ && you.auto_pickup==-1))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_AUTOPICKUP_ON),true,false,false,CL_normal);
		you.auto_pickup = 1;
	}
	else
	{
		printlog(LocalzationManager::formatString(LOC_SYSTEM_AUTOPICKUP_OFF, PlaceHolderHelper("Ctrl + a")),true,false,false,CL_small_danger);
		you.auto_pickup = auto_?0:-1;
	}
}


void auto_tanmac_onoff()
{
	if(you.useMouseTammac == 0)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_AUTOTANMAC_ON),true,false,false,CL_help);
		you.useMouseTammac = 1;
	}
	else if(you.useMouseTammac == 1)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_AUTOTANMAC_AUTO),true,false,false,CL_help);
		you.useMouseTammac = 2;
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_AUTOTANMAC_OFF),true,false,false,CL_help);
		you.useMouseTammac = 0;
	}
}

void floorMove()
{
	dungeon_level next_ = TEMPLE_LEVEL;


	list<pair<char, string>> enter_;
	enter_.push_back(pair<char, string>('d',  LocalzationManager::locString(LOC_SYSTEM_DUNGEON)));
	if (map_list.dungeon_enter[TEMPLE].detected)
		enter_.push_back(pair<char, string>('t', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_TEMPLE)));
	if (map_list.dungeon_enter[MISTY_LAKE].detected)
		enter_.push_back(pair<char, string>('l', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MISTYLAKE)));
	if (map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected)
		enter_.push_back(pair<char, string>('m', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN)));
	if (map_list.dungeon_enter[SCARLET_M].detected)
		enter_.push_back(pair<char, string>('s', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET)));
	if (map_list.dungeon_enter[SCARLET_L].detected)
		enter_.push_back(pair<char, string>('b', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET_LIBRARY)));
	if (map_list.dungeon_enter[SCARLET_U].detected)
		enter_.push_back(pair<char, string>('u', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET_UNDER)));
	if (map_list.dungeon_enter[BAMBOO].detected)
		enter_.push_back(pair<char, string>('a', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_BAMBOO)));
	if (map_list.dungeon_enter[YUKKURI_D].detected)
		enter_.push_back(pair<char, string>('y', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YUKKURI)));
	if (map_list.dungeon_enter[DEPTH].detected)
		enter_.push_back(pair<char, string>('p', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH)));
	if (map_list.dungeon_enter[SUBTERRANEAN].detected)
		enter_.push_back(pair<char, string>('h', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SUBTERRANEAN)));
	if (map_list.dungeon_enter[DREAM_D].detected)
		enter_.push_back(pair<char, string>('r', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DREAM)));
	if (map_list.dungeon_enter[PANDEMONIUM].detected)
		enter_.push_back(pair<char, string>('k', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM)));
	if (map_list.dungeon_enter[HAKUREI_D].detected)
		enter_.push_back(pair<char, string>('z', LocalzationManager::locString(LOC_SYSTEM_DUNGEON_HAKUREI)));

	int num_ = 0;
	std::vector<int> listkey;
	for (auto it = enter_.begin(); it != enter_.end(); it++) {
		char temp[100];
		sprintf_s(temp, 100, "%c - %s  ", it->first, it->second.c_str());
		printlog(temp, false, false, false, CL_help, it->first);
		listkey.push_back(it->first);
		num_++;
		if (num_ == 5) {
			enterlog();
			num_ = 0;
		}
	}
	startSelection(listkey);

	enterlog();
	printlog(LocalzationManager::locString(LOC_SYSTEM_AUTOEXPLORE_WHERE), false, false, false, CL_help);
	int key_ = waitkeyinput();
	endSelection();

	bool ok_ = false;
	for (auto it = enter_.begin(); it != enter_.end(); it++) 
	{
		if (key_ == it->first || key_ == (it->first - 'a' + 'A'))
		{
			ok_ = true;
			break;
		}
	}
	if (!ok_) {
		printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
		return;
	}



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
	default:
		printlog(" " + LocalzationManager::locString(LOC_SYSTEM_CANCLE), true, false, false, CL_help);
		return;
	}


	queue<list<coord_def>> stairMap;
	if (MapNode::searchRoad(current_level, (int)next_, &stairMap)) {

		while (!stairMap.empty()) {
			list<coord_def> list_ = stairMap.front();
			enterlog();
			coord_def next_;
			int length = 9999;
			for (auto it = list_.begin(); it != list_.end(); it++)
			{
				stack<coord_def> stacks;
				if ((env[current_level].isExplore(it->x, it->y) ||
					env[current_level].isMapping(it->x, it->y)
					)
					&& env[current_level].isStair(it->x, it->y)
					&& PathSearch(you.position, *it, stacks, ST_NORMAL))
				{
					if (length > stacks.size()) {
						next_ = (*it);
						length = stacks.size();
					}
				}
			}

			Long_Move(next_, true);
			if (you.position == next_) {
				switch (env[current_level].getStairKind(you.position.x, you.position.y)) 
				{
				case STAIR_KIND_NOT_STAIR:
					return;
				case STAIR_KIND_UP_BASE:
				case STAIR_KIND_UP_SPECIAL:
					Stair_move(false);
					break;
				case STAIR_KIND_DOWN_BASE:
				case STAIR_KIND_DOWN_SPECIAL:
					Stair_move(true);
					break;
				}
			}
			else {
				return;
			}
			stairMap.pop();
		}
	}

}