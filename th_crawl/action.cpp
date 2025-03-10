//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: action.cpp
//
// ����: player�� �ൿ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <set>
#include <algorithm>
#include "environment.h"
#include "display.h"
#include "localization.h"
#include "key.h"
#include "player.h"
#include "beam.h"
#include "mon_infor.h"
#include "monster_texture.h"
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

int action_Move(int command, const coord_def &c)
{
	if (you.search)
		return Search_Move(c, widesearch);
	else {
		you.SetPrevAction(command);
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




void Long_Move(const coord_def &c)
{
	while(!you.will_move.empty())
		you.will_move.pop();
	//�̷��� �ص��Ƿ���?

	you.search = false;
	if(env[current_level].insight_mon(MET_ENEMY))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LOS_MON),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.s_confuse)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE),true,false,false,CL_small_danger);
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
	if(!PathSearch(you.position,c,you.will_move,ST_NORMAL))
	{
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
		action_Move('k', coord_def(you.position.x, you.position.y - 1));  //��
		break;
	case 'j':
		action_Move('j', coord_def(you.position.x, you.position.y + 1)); //�Ʒ�
		break;
	case 'h':
		action_Move('h', coord_def(you.position.x - 1, you.position.y)); //����
		break;
	case 'l':
		action_Move('l', coord_def(you.position.x + 1, you.position.y)); //������
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
	case 's': //�Ͻ�ŵ
		action_turn_skip();
		break;
	case 'D': //�������� ���� ������ ������
		fast_discard();
		break;
	case 'C': //���ݱ�
		Close_door();
		break;
	case 'O': //������
		Open_door();
		break;
	case 'o': //�ڵ��̵�
		auto_Move();
		break;
	case '5': //100�ϳѱ��
		long_rest();
		break;
	case 'e': //�Ա�
		Eatting(you.prev_action_key.item);
		break;
	case 'q': //���ñ�
		Drinking(you.prev_action_key.item);
		break;
	case 'r': //�б�
		Reading(you.prev_action_key.item);
		break;
	case 'f': //������
		Quick_Throw(you.GetThrowIter(), you.GetTargetIter(), true);  //TODO
		break;
	case 'v':
		Spelllcard_Evoke(you.prev_action_key.item); //TODO
		break;
	case 'p':
		Pray(); 
		break;
	case 'z':
		SpellUse(you.prev_action_key.item, you.prev_action_key.num); //TODO
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



void auto_battle()
{
	if(!env[current_level].insight_mon(MET_ENEMY))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LOS_NOMON),true,false,false,CL_small_danger);
		return;
	}
	if(you.s_confuse)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE),true,false,false,CL_small_danger);
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
		for(int i=RT_BEGIN;i!=RT_END;i++)
		{
			beam_iterator it(you.position,mon_->position,(round_type)i);
			if(env[current_level].dgtile[(*it).x][(*it).y].isMove(true,false,false))
			{
				Move((*it));
				you.SetPrevAction(VK_TAB);
				return;
			}
			else
			{
			}
		}
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_AUTOBATTLE_NOMON),true,false,false,CL_small_danger);
		return;
	}


}

void auto_Move()
{	
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY),true,false,false,CL_danger);
		return;
	}
	you.search = false;
	/*if(you.GetHunger() == HT_STARVING)	
	{
		printlog("����� ���´�.",false,false,false,CL_danger);
		if(you.power>=100)
			printlog("c�� ������ ��⸦ ä����!",true,false,false,CL_danger);
		else
			printlog("���𰡸� �Ծ��!",true,false,false,CL_danger);
		return;
	}*/
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.resetLOS() == IT_MAP_DANGER)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_MAP_DANGER),true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
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
						return;
					}
					back_ = true;
				}
			}
		}
		if(back_)
			continue;
		
		if(PathSearch(you.position,you.position,you.will_move,ST_SEARCH, current_level, false, you.isSwim()))
		{
			if(!stack_move(true))
			{
				return;
			}
		}
		else
			break;
	}
	while(!you.will_move.empty()){you.will_move.pop();}
	printlog(LocalzationManager::locString(LOC_SYSTEM_DONE_EXPLORE),true,false,false,CL_normal);
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
		//case IT_HUNGRY:
		case IT_STAT:
		case IT_POISON:
		case IT_TELE:
		case IT_SMOKE:
		case IT_EVENT:
		case IT_DAMAGE:
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE),true,false,false,CL_small_danger);
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
		//case IT_HUNGRY:
		case IT_STAT:
		case IT_POISON:
		case IT_TELE:
		case IT_SMOKE:
		case IT_EVENT:
		case IT_DAMAGE:
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
			//���乫���� ��� ��θ� ����.
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
	int return_ = 1;
	if((c.x > you.position.x && you.search_pos.x < DG_MAX_X-1 && wide && !you.s_dimension) 
		|| (!you.s_dimension && c.x > you.position.x && you.search_pos.x < you.position.x + 8)
		|| (you.s_dimension && c.x > you.position.x && you.search_pos.x < you.god_value[GT_YUKARI][0] + 8))
		you.search_pos.x+= c.x - you.position.x;
	else if((c.x < you.position.x && you.search_pos.x > 0 && wide && !you.s_dimension) 
		|| (!you.s_dimension && c.x < you.position.x && you.search_pos.x > you.position.x - 8)
		|| (you.s_dimension && c.x < you.position.x && you.search_pos.x > you.god_value[GT_YUKARI][0] - 8))
		you.search_pos.x-= you.position.x - c.x ;
	if((c.y > you.position.y && you.search_pos.y < DG_MAX_Y-1 && wide && !you.s_dimension) 
		|| (!you.s_dimension && c.y > you.position.y && you.search_pos.y < you.position.y + 8)
		|| (you.s_dimension && c.y > you.position.y && you.search_pos.y < you.god_value[GT_YUKARI][1] + 8))
		you.search_pos.y+= c.y - you.position.y;
	else if((c.y < you.position.y && you.search_pos.y > 0 && wide && !you.s_dimension) 
		|| (!you.s_dimension && c.y < you.position.y && you.search_pos.y > you.position.y - 8)
		|| (you.s_dimension && c.y < you.position.y && you.search_pos.y > you.god_value[GT_YUKARI][1] - 8))
		you.search_pos.y-= you.position.y -c.y;



	if(type_ == VT_NORMAL)
	{	
		deletelog();
		if(!wide)
			//"(��ɾ�: v - ����   . - Ž��   e - ���豸������)"
			printlog(LocalzationManager::formatString("({0}: {1} - {2}   {3} - {4}   {5} - {6})",PlaceHolderHelper(LOC_SYSTEM_COMMAND), "v",PlaceHolderHelper(LOC_SYSTEM_DESCRIPTION), ".",PlaceHolderHelper(LOC_SYSTEM_EXPLORE), "e",PlaceHolderHelper(LOC_SYSTEM_DANGER)),true,false,true,CL_help);	
		else
			//"(��ɾ�: v - ����   . - Ž��   <,> - ���� ���ã��   e - ���豸������)"
			printlog(LocalzationManager::formatString("({0}: {1} - {2}   {3} - {4}   {5},{6} - {7}   {8} - {9})", PlaceHolderHelper(LOC_SYSTEM_COMMAND), "v",PlaceHolderHelper(LOC_SYSTEM_DESCRIPTION), ".",PlaceHolderHelper(LOC_SYSTEM_EXPLORE), "<", ">", PlaceHolderHelper(LOC_SYSTEM_STAIR_TRAVEL), "e",PlaceHolderHelper(LOC_SYSTEM_DANGER)),true,false,true,CL_help);	

	}
	else if(type_ == VT_THROW || type_ == VT_DEBUF || type_ == VT_SATORI)
	{
		//"(��ɾ�: v - ����)"
		printlog(LocalzationManager::formatString("({0}: {1} - {2})",PlaceHolderHelper(LOC_SYSTEM_COMMAND), "v", PlaceHolderHelper(LOC_SYSTEM_DESCRIPTION)),true,false,true,CL_help);	
	}
	else
		deletelog();

	if(env[current_level].isInSight(you.search_pos))
	{//����Ȯ��
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
						char temp[30];
						D3DCOLOR color_ = (*it).GetStateString(mss, temp);
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
							printlog(temp, false, false, true, color_);
						}
					}
					if (state_)
						printlog(")", false, false, true, CL_normal);
					if (type_ == VT_DEBUF)
					{
						printlog("(", false, false, true, CL_normal);
						char temp[64];
						float percent_ = getDebufPercent((*it).GetResist(), value_);
						if (it->s_mind_reading)
							percent_ = 0;

						sprintf_s(temp, 64, "%s: %.0f%%", LocalzationManager::locString(LOC_SYSTEM_SUCCESS_PERCENT), percent_);
						printlog(temp, false, false, true, CL_normal);
						printlog(")", false, false, true, CL_normal);
					}
					else if (type_ == VT_SATORI && !it->s_mind_reading)
					{
						printlog("(", false, false, true, CL_normal);
						char temp[64];

						int turn_ = 2 + it->level / 3 + it->resist * 3;

						turn_ = max(1, turn_ - you.level / 4);

						if (turn_ >= 20 || it->id == MON_KOISHI)
							sprintf_s(temp, 64, LocalzationManager::locString(LOC_SYSTEM_IMPOSSIBLE).c_str());
						else
							sprintf_s(temp, 64, "%d%s", turn_, LocalzationManager::locString(turn_>1?LOC_SYSTEM_TURNS:LOC_SYSTEM_TURN));

						printlog(temp, false, false, true, CL_normal);
						printlog(")", false, false, true, CL_normal);

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
	{//������Ȯ��
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
	{//����Ȯ��
		
		string s = "[" + LocalzationManager::locString(LOC_SYSTEM_TERRAIN) +": ";
		s += dungeon_tile_tribe_type_string[env[current_level].dgtile[you.search_pos.x][you.search_pos.y].tile];
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
	//���� ����.. �ǵ����̸� ��������
	return true;
}
int Player_Move(const coord_def &c)
{
	int move_type; //0�� �̵��Ұ�. 1�� �̵����� ����(�ַ� ����). 2�� �̵�����
	bool pick_ups = false;
	coord_def tempPos = you.position;
	if(move_type = you.move(c))
	{
		if(move_type != 1) //��ĭ�̶� �̵�������
		{
			//�������� ���� ������ �޼��� ���
			int num=0;
			bool type = false;
			if(env[current_level].dgtile[you.position.x][you.position.y].tile >= DG_DOWN_STAIR && env[current_level].dgtile[you.position.x][you.position.y].tile <= DG_SEA-1)
			{
				printlog(LocalzationManager::formatString(LOC_SYSTEM_ON_THE_TERRAIN, dungeon_tile_tribe_type_string[env[current_level].dgtile[you.position.x][you.position.y].tile]), false,false,false,CL_normal);
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
						if(!PickUpNum(temp,1,false))
							break;
						pick_ups = true;
						{ //�������� �ֿﶧ P�� ������� ƨ�� ���ɼ��� �ִ�.
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
					// printlog("���⿣ ",false,false,false,CL_normal);
					// printlog((*start_it).GetName(),false,false,false,(*start_it).item_color());
					// printlog((*start_it).GetNameInfor().name_do(true),false,false,false,CL_normal);
					// printlog("�ִ�. (,Ű�� �ݱ�)",true,false,false,CL_normal);
				}
				else if(num<=4)
				{
					printlog("���⿣ ������ ���� ������ �ִ�. (,Ű�� �ݱ�)",true,false,false,CL_normal);
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
					printlog("���⿣ �������� ������ �ִ�. (,Ű�� �ݱ�)",true,false,false,CL_normal);
				}
			}



			if (you.god == GT_OKINA && !you.GetPunish(GT_OKINA)) {
				//��Ű���� ������ ���� �ڵ����� ����
				if (env[current_level].isDoor(tempPos.x, tempPos.y)){
					int close_ = 0;
					if ((close_ = env[current_level].CloseDoor(tempPos.x, tempPos.y)) == 1)
					{
						//���� �ݰ� �Ұ� �ֳ�?
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
		SetText() = GetMonsterInfor(mon_);
		ReleaseMutex(mutx);
		changedisplay(DT_TEXT);
		int key_ = waitkeyinput(true);
						
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
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
					loop_ = true;
					break;
				}
				num--;
			}
							
		}
	}
}
void Search()
{
	you.search_pos = you.position;
	you.search = true;
	Search_Move(coord_def(you.position.x,you.position.y), false);
	while(1)
	{
		switch(waitkeyinput())
		{
		case 'k':
			Move(coord_def(you.position.x,you.position.y-1));  //��
			break;
		case 'j':
			Move(coord_def(you.position.x,you.position.y+1)); //�Ʒ�
			break;
		case 'h':
			Move(coord_def(you.position.x-1,you.position.y)); //����
			break;
		case 'l':
			Move(coord_def(you.position.x+1,you.position.y)); //������
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
			Move(coord_def(you.position.x, you.position.y - 8));  //��
			break;
		case 'J':
			Move(coord_def(you.position.x, you.position.y + 8)); //�Ʒ�
			break;
		case 'H':
			Move(coord_def(you.position.x - 8, you.position.y)); //����
			break;
		case 'L':
			Move(coord_def(you.position.x + 8, you.position.y)); //������
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
			if (!env[current_level].isBamboo())
			{
				env[current_level].AddForbid(you.search_pos);
			}
			break;
		case '.': 
		case VK_RETURN:
			you.search = false;
			Long_Move(you.search_pos);
		case VK_ESCAPE:
		case 'x':
			deletelog();
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
		switch(waitkeyinput())
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
			Move(coord_def(you.position.x,you.position.y-1));  //��
			break;
		case 'j':
			Move(coord_def(you.position.x,you.position.y+1)); //�Ʒ�
			break;
		case 'h':
			Move(coord_def(you.position.x-1,you.position.y)); //����
			break;
		case 'l':
			Move(coord_def(you.position.x+1,you.position.y)); //������
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
			Move(coord_def(you.position.x,you.position.y-8));  //��
			break;
		case 'J':
			Move(coord_def(you.position.x,you.position.y+8)); //�Ʒ�
			break;
		case 'H':
			Move(coord_def(you.position.x-8,you.position.y)); //����
			break;
		case 'L':
			Move(coord_def(you.position.x+8,you.position.y)); //������
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
			if (!env[current_level].isBamboo())
			{
				env[current_level].AddForbid(you.search_pos);
			}
			break;
		case '.': 
		case VK_RETURN:
			widesearch = false;
			you.search = false;
			deletelog();
			Long_Move(you.search_pos);
			return;
		default:
			deletelog();
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

void escape() //�ൿ���� �����
{
	if(you.search)
	{
		deletelog();
		you.search = false;
		widesearch = false;
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
		printlog("��� �� ���� ��������?",true,false,false,CL_help);
		
		while(door_num>1)
		{
			switch(waitkeyinput())
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
			}
		}
	}
	
	if(door_num==1)
	{
		int close_= 0;
		if((close_ = env[current_level].CloseDoor(temp.x,temp.y)) == 1)
		{				
			printlog("���� �ݾҴ�. ",false,false,false,CL_normal);
			you.time_delay += you.GetNormalDelay();
			you.TurnEnd();
		}
		else if(close_ == -1)
		{
			printlog("�����ΰ��� �������µ� ���صǰ� �ִ�.",true,false,false,CL_normal);
		}
		else
		{
			printlog("�װ��� ���� �� �ִ� ���� ����!",true,false,false,CL_normal);
		}
		you.SetPrevAction('C');
	}
	else
	{
		printlog("��ó�� �������� ���� ����.",true,false,false,CL_normal);
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
		printlog("��� �� ���� ������?",true,false,false,CL_help);
		
		while(door_num>1)
		{
			switch(waitkeyinput())
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
			}
		}
	}
	if(door_num==1)
	{
		int result = you.OpenDoor(temp, false);
		if(result == 0)
		{
			printlog("�װ��� �� �� �ִ� ���� ����!",true,false,false,CL_normal);
		}		
		else if(result > 0)
			you.TurnEnd();
		you.SetPrevAction('O');
	}
	else
	{
		printlog("��ó�� ������ ���� ����.",true,false,false,CL_normal);
		you.SetPrevAction('O');
	}
	
}



bool CheckDimension()
{
	if (you.god != GT_YUKARI) {
		printlog("���� ���� ����� �̿��� �� ����!", true, false, false, CL_danger);
		return false;
	}


	while(1)
	{
		printlog("����� �̿��ϸ� ���������� Ǯ���ϴ�. ��¥�� �̿��մϱ�?(Y/N)",false,false,false,CL_help);
		switch(waitkeyinput())
		{
		case 'Y':
			you.s_dimension = 0;
			enterlog();
			return true;
		case 'N':
		default:
			printlog(" ����ϵ���!",true,false,false,CL_help);
			return false;
		}
	}
}
bool warning(dungeon_tile_type type, bool down)
{//���޽����� �ִ� ��
	
	switch(type)
	{
	case DG_YUKKURI_STAIR:
		if(down)
		{
			printlog("���� ���� �����غ��δ�. �׷��� �������ž�?(Y/N)",false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				return true;
			case 'N':
			default:
				printlog(" �����ϱ�!",true,false,false,CL_help);
				return false;
			}
		}
		break;
	case DG_SCARLET_U_STAIR:
		if(down)
		{
			printlog("���� ���� �����غ��δ�. �׷��� �������ž�?(Y/N)",false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				return true;
			case 'N':
			default:
				printlog(" �����ϱ�!",true,false,false,CL_help);
				return false;
			}
		}
		break;
	case DG_BAMBOO_STAIR:
		if(down)
		{
			printlog("�� ���� ���� ������ �����δ�. �׷��� �������ž�?(Y/N)",false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				return true;
			case 'N':
			default:
				printlog(" ���� �����̾�!",true,false,false,CL_help);
				return false;
			}
		}
		break;
	case DG_PANDEMONIUM_STAIR:
		if(down)
		{
			if(!(current_level >= PANDEMONIUM_LEVEL && current_level <= PANDEMONIUM_LAST_LEVEL))
			{
				printlog("�� ���� ���� ������ �����δ�. �׷��� �������ž�?(Y/N)",false,false,false,CL_danger);
				switch(waitkeyinput())
				{
				case 'Y':
				case 'y':
					enterlog();
					return true;
				case 'N':
				default:
					printlog(" ���� �����̾�!",true,false,false,CL_help);
					return false;
				}
			}
		}
		//break; ���� �ǵ���Ͼ��� �̾���
	case DG_RETURN_STAIR:
		if(current_level > PANDEMONIUM_LEVEL && current_level <= PANDEMONIUM_LAST_LEVEL)
		{
			if((type == DG_PANDEMONIUM_STAIR && down ) || (type == DG_RETURN_STAIR && !down ) )
			{
				if(!you.rune[RUNE_PANDEMONIUM_MAGIC + current_level - PANDEMONIUM_LEVEL-1])
				{
					printlog("���⼭ ���������� �� ���� ���� �ٽ� ���� �� ����. ������ �����ž�?(Y/N)",false,false,false,CL_danger);
					switch(waitkeyinput())
					{
					case 'Y':
					case 'y':
						enterlog();
						return true;
					case 'N':
					default:
						printlog(" OK!",true,false,false,CL_help);
						return false;
					}
				}
			}
		}
		break;
	case DG_ZIGURRAT_STAIR:
		if (down && current_level != ZIGURRAT_LEVEL)
		{
			printlog("�� ���� ���� ������ �ѹ��� �� �� �ִ� �Ǹ��� �����̴�. �غ�Ǿ���? (Y/N)", true, false, false, CL_danger);
			switch (waitkeyinput())
			{
			case 'Y':
			case 'y':
				if (you.ziggurat_level) {
					printlog("�̹� �� ���� ������ �� �̻� �� �� ����! ", true, false, false, CL_help);
					return false;
				}
				enterlog();
				return true;
			case 'N':
			default:
				printlog("�� �� ������ �غ��ϵ���!", true, false, false, CL_help);
				return false;
			}
		}
		break;
	case DG_DREAM_STAIR:
		if(down)
		{
			printlog("�� ���� ���� ������ �����δ�. �׷��� �������ž�?(Y/N)",false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				return true;
			case 'N':
			default:
				printlog(" ���� �����̾�!",true,false,false,CL_help);
				return false;
			}
		}
		break;
	case DG_HAKUREI_STAIR:
		if(down)
		{
			if(you.haveGoal()<3)
			{
				printlog("�� ���� �������ؼ� 3���� ���� �ʿ��ϴ�!",true,false,false,CL_normal);
				return false;
			}
			else 
			{
				printlog("����� 3���� ���� �Ա��� �ȾҴ�. ������ ����Ű�� ���� ���ȴ�!",true,false,false,CL_normal);
				MoreWait();
			}
		}
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
			printlog("���⼱ �ö� �� ����.",true,false,false,CL_normal);
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
					printlog("����� �����Դ�.",true,false,false,CL_normal);
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
			printlog("�� �̻� ������ �� ����.",true,false,false,CL_normal);
		}
		break;
	case STAIR_KIND_DOWN_SPECIAL:
		if(!down)
		{
			printlog("���⼱ �ö� �� ����.",true,false,false,CL_normal);
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
			}

			env[next_].EnterMap(0,dq); 
			printlog("����� �����Դ�.",true,false,false,CL_normal);
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
			printlog("���⼱ ������ �� ����.",true,false,false,CL_normal);
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
					printlog("����� �ö�Դ�.",true,false,false,CL_normal);
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
				if(you.haveGoal())
				{
					printlog("������� �ݱ�������, ����� ���� �й�� �����ɰž�. �׷��� �����ž�?(Y/N)",true,false,false,CL_danger);
				}
				else
				{
					printlog("������ ������ Ż���ϰڽ��ϱ�?(Y/N)",true,false,false,CL_normal);

				}				
				
				int direc = waitkeyinput(true);
				if(direc == 'Y')
				{
					you.dead_reason = DR_ESCAPE;
					GameOver();
					break;
				}
				printlog("��� Ž���ϵ���!",true,false,false,CL_normal);	
			}
		}
		break;
	case STAIR_KIND_UP_SPECIAL:
		if(down)
		{
			printlog("���⼱ ������ �� ����.",true,false,false,CL_normal);
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
				env[floor_return].MakeMap(true); //����� ������� �Ա��� ã�� ���� �̸� �����.
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
				//���������� ������ ������ 1������ �ʱ�ȭ
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
			printlog("�������� ���ƿԴ�.",true,false,false,CL_normal);
			GodAccpect_Stair(false, true);
			soundmanager.playSound("stair");
			//you.resetLOS(false);
			you.TurnEnd();
			break;
		}
		break;
	default:
		printlog("���⿣ ����� ����.",true,false,false,CL_normal);
		break;
	}
}



void view_log()
{
	changedisplay(DT_LOG);
	while(1)
	{
		switch(waitkeyinput(true))
		{
		case VK_UP:
			changemove(1);  //��
			continue;
		case VK_DOWN:
			changemove(-1); //�Ʒ�
			continue;
		case VK_PRIOR:
			changemove(DisplayManager.log_length);
			continue;
		case VK_NEXT:
			changemove(-DisplayManager.log_length);
			continue;
		}
		break;
	}
	changedisplay(DT_GAME);
}

void skill_view()
{
	view_skill("");
	int move_ = 1;
	bool ok_ = false;
	do
	{
		while(1)
		{
			int key_ = waitkeyinput(true);
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
			view_skill("�ּ��� �ϳ��� ��ų�� �Ѿߵ˴ϴ�!");
	}
	while(!ok_);

	changedisplay(DT_GAME);
}
void stat_view()
{
	changedisplay(DT_STATE);
	while(1)
	{
		int key_ = waitkeyinput(true);
		break;
	}
	changedisplay(DT_GAME);
}


void rune_Show()
{
	if(!isNormalGame())
		return;
	int remain = 10;
	SetText() = "  <������ ��>\n\n\n";



	for(int i = 0; i<RUNE_HAKUREI_ORB;i++)
	{
		remain = 10;
		remain -= strlen(rune_string[i]);
		for(;remain>0;remain--)
			SetText() += " ";
		SetText() += rune_string[i];
		SetText() += "�� �� :";


		if(you.rune[i])
		{
			SetText() += " ȹ��";
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
		SetText() += "������� ������ϴ�! Ż���ϼ���!\n";
	}
	else
	{
		SetText() += "���� ������� ���� ���߽��ϴ�.\n\n";
		SetText() += "���� 3���̻������ ������� �ִ� ������ �Ż��� ���� �����ϴ�.";
	}


	
	changedisplay(DT_TEXT);

	while(1)
	{
		int key_ = waitkeyinput(true);		
		break;
	}
	changedisplay(DT_GAME);
}



void Iden_Show()
{
	int line = 1, num=0;
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
		
		int key_ = waitkeyinput(true);
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
		else if(key_ == VK_DOWN)//-----�̵�Ű-------
		{
			changemove(32);  //��
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //�Ʒ�
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----�̵�Ű��-------
		else
			break;

	}
	changedisplay(DT_GAME);

}

void Weapon_Show()
{
	deletelog();
	char temp [100];
	printlog("����: ",false,false,true,CL_normal);
	if(you.equipment[ET_WEAPON])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_WEAPON]->id,you.equipment[ET_WEAPON]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_WEAPON]->item_color());
	}
	else
	{
		printlog("�Ǽ�",true,false,true,CL_normal);
	}


	printlog("ź��: ",false,false,true,CL_normal);
	if(you.throw_weapon)
	{
		sprintf_s(temp,100,"%c) %s",you.throw_weapon->id,you.throw_weapon->GetName().c_str());
		printlog(temp,true,false,true,you.throw_weapon->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}
}

void Armour_Show()
{
	deletelog();
	char temp [100];
	printlog("����: ",false,false,true,CL_normal);
	if(you.equipment[ET_ARMOR])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_ARMOR]->id,you.equipment[ET_ARMOR]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_ARMOR]->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}

	printlog("����: ",false,false,true,CL_normal);
	if(you.equipment[ET_SHIELD])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_SHIELD]->id,you.equipment[ET_SHIELD]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_SHIELD]->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}	
	
	printlog("�Ӹ�: ",false,false,true,CL_normal);
	if(you.equipment[ET_HELMET])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_HELMET]->id,you.equipment[ET_HELMET]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_HELMET]->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}

	
	printlog("����: ",false,false,true,CL_normal);
	if(you.equipment[ET_CLOAK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_CLOAK]->id,you.equipment[ET_CLOAK]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_CLOAK]->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}

	printlog("��: ",false,false,true,CL_normal);
	if(you.equipment[ET_GLOVE])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_GLOVE]->id,you.equipment[ET_GLOVE]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_GLOVE]->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}

	printlog("��: ",false,false,true,CL_normal);
	if(you.equipment[ET_BOOTS])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_BOOTS]->id,you.equipment[ET_BOOTS]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_BOOTS]->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}


}




void Amulet_Show()
{
	deletelog();
	char temp [100];
	printlog("�����  : ",false,false,true,CL_normal);
	if(you.equipment[ET_NECK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_NECK]->id,you.equipment[ET_NECK]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_NECK]->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}

	printlog("�޹���  : ",false,false,true,CL_normal);
	if(you.equipment[ET_LEFT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_LEFT]->id,you.equipment[ET_LEFT]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_LEFT]->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}
	
	printlog("��������: ",false,false,true,CL_normal);
	if(you.equipment[ET_RIGHT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_RIGHT]->id,you.equipment[ET_RIGHT]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_RIGHT]->item_color());
	}
	else
	{
		printlog("����",true,false,true,CL_normal);
	}
}

void Simple_State_Show()
{	
	int penalty_ = you.as_penalty>you.GetPenaltyMinus(3)?4: //����
					you.as_penalty>you.GetPenaltyMinus(2)?3: //�̵��г�Ƽ
					you.as_penalty>you.GetPenaltyMinus(1)?2: //����
					you.as_penalty?1:0;
	switch(penalty_/*you.GetArmourPanlty()*/)
	{
	case 0:
		break;
	case 1:
		printlog("����� ���� ���� ���̴�. ",false,false,false,CL_normal);
		break;
	case 2:
		printlog("����� ���� �����ϴ�. ",false,false,false,CL_normal);
		break;
	case 3:
		printlog("����� ���� �ſ� �����ϴ�. ",false,false,false,CL_normal);
		break;
	case 4:
	default:
		printlog("���� ����� �԰��ִ�. ",false,false,false,CL_normal);
		break;
	}/*
	switch(you.GetShieldPanlty())
	{
	case 0:
		break;
	case 1:
		printlog("����� ���д� ���� ���̴�.",false,false,false,CL_normal);
		break;
	case 2:
	case 3:
		printlog("����� ���д� �ణ �����ϴ�.",false,false,false,CL_normal);
		break;
	case 4:
		printlog("����� ���д� �����ϴ�.",false,false,false,CL_normal);
		break;
	case 5:
	case 6:
		printlog("����� ���д� �ſ� �����ϴ�.",false,false,false,CL_normal);
		break;
	default:
		printlog("����� ���п� �����ٴѴ�.",false,false,false,CL_normal);
		break;
	}*/
	enterlog();
}
void Experience_Show()
{
	char temp [100];
	sprintf_s(temp,100,"����� %d���� %s %s�Դϴ�.", you.level, tribe_type_string[you.tribe], job_type_string[you.job]);
	printlog(temp,true,false,false,CL_normal);
	if(you.GetNeedExp(you.level-1) > 0)
	{
		sprintf_s(temp,100,"���� �������� %d�� ����ġ�� ���ҽ��ϴ�.",you.GetNeedExp(you.level-1) - you.exper);
		printlog(temp,true,false,false,CL_normal);
	}
	else
	{
		sprintf_s(temp,100,"����� ���� �ְ� ������ �������ֽ��ϴ�.");
		printlog(temp,true,false,false,CL_normal);
	}
}

//bool Eat_Power()
//{
//	if(HT_NORMAL <= you.GetHunger())
//	{
//		printlog("����� ���� ������� �ʴ�.",true,false,false,CL_normal);
//		return false;
//	}
//	else if(you.power < 100)
//	{
//		printlog("�Ŀ��� �����ϴ�.",true,false,false,CL_normal);
//		return false;
//	}
//	printlog("P�� 1 �Ҹ��Ͽ� �������� ä��ðڽ��ϱ�?(y/n)",true,false,false,CL_help);
//	int temp = waitkeyinput();
//	if(temp == 'y' || temp == 'Y')
//	{
//		you.PowUpDown(-100, true);
//		you.HungerApply(3000);
//		printlog("����� �������� ������.",true,false,false,CL_normal);
//		you.time_delay += 10;
//		you.TurnEnd();
//		return true;
//	}
//	return false;
//}

void dungeonView()
{
	if(!isNormalGame())
		return;

	char temp[32];
	char blank[32];
	sprintf_s(blank,32,"            ");

	int floor_ = 0;
	deletesub();
	WaitForSingleObject(mutx, INFINITE);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub(blank,false,CL_warning);
	printsub("<���� ���൵>",true,CL_warning);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub(blank,false,CL_warning);
	printsub("���� ",false,CL_warning);
	for(int i=0;i<=MAX_DUNGEUN_LEVEL;i++)
	{
		if(env[i].make)
			floor_++;
		else
			break;
	}	
	sprintf_s(temp,32,"(%2d/%2d)",floor_,MAX_DUNGEUN_LEVEL+1);
	printsub(temp,true,CL_normal);
	printsub(blank,false,CL_warning);
	printsub("��",true,CL_normal);
	if(floor_>=3) //��������
	{
		if(map_list.dungeon_enter[TEMPLE].detected)
		{
			printsub(blank,false,CL_warning);
			printsub("��",false,CL_normal);
			printsub("���� ",false,CL_warning);			
			sprintf_s(temp,32,"(%2d/%2d) ",env[TEMPLE_LEVEL].make?1:0,1);
			printsub(temp,false,CL_normal);
				
			sprintf_s(temp,32,"���� %d��",map_list.dungeon_enter[TEMPLE].floor+1);
			printsub(temp,true,CL_help);
			printsub(blank,false,CL_warning);
			printsub("��",true,CL_normal);
		}
		else
		{
			printsub(blank,false,CL_warning);
			printsub("��",false,CL_normal);
			printsub("���� ",false,CL_bad);
			printsub("���� 3��~6��",true,CL_STAT);
			printsub(blank,false,CL_warning);
			printsub("��",true,CL_normal);
		}
	}	
	if(floor_>=8) //�Ȱ���ȣ��
	{
		if(map_list.dungeon_enter[MISTY_LAKE].detected)
		{
			printsub(blank,false,CL_warning);
			printsub("��",false,CL_normal);
			printsub("�Ȱ��� ȣ�� ",false,CL_warning);
			int floor2_ = 0;	
			for(int i=MISTY_LAKE_LEVEL;i<=MISTY_LAKE_LAST_LEVEL;i++)
			{
				if(env[i].make)
					floor2_++;
				else
					break;
			}
			sprintf_s(temp,32,"(%2d/%2d) ",floor2_,MAX_MISTY_LAKE_LEVEL+1);
			printsub(temp,false,CL_normal);
				
			sprintf_s(temp,32,"���� %d��",map_list.dungeon_enter[MISTY_LAKE].floor+1);
			printsub(temp,true,CL_help);

			if(floor2_>=2) //�䱫�ǻ�
			{
				if(map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected)
				{
					printsub(blank,false,CL_warning);
					printsub("����",false,CL_normal);
					printsub("�䱫�� �� ",false,CL_warning);
					int floor3_ = 0;	
					for(int i=YOUKAI_MOUNTAIN_LEVEL;i<=YOUKAI_MOUNTAIN_LAST_LEVEL;i++)
					{
						if(env[i].make)
							floor3_++;
						else
							break;
					}
					sprintf_s(temp,32,"(%2d/%2d) ",floor3_,MAX_YOUKAI_MOUNTAIN_LEVEL+1);
					printsub(temp,false,CL_normal);
				
					sprintf_s(temp,32,"�Ȱ��� ȣ�� %d��  ",map_list.dungeon_enter[YOUKAI_MOUNTAIN].floor+1-MISTY_LAKE_LEVEL);
					printsub(temp,false,CL_help);

					//***������
					sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_YOUKAI_MOUNTAIN]);
					printsub(temp,true,you.rune[RUNE_YOUKAI_MOUNTAIN]?CL_magic:CL_bad);
					//***�鳡

					if(floor3_>=MAX_YOUKAI_MOUNTAIN_LEVEL+1) //������
					{
						if(map_list.dungeon_enter[YUKKURI_D].detected)
						{
							printsub(blank,false,CL_warning);
							printsub("������",false,CL_normal);
							printsub("�������� ",false,CL_warning);
							int floor4_ = 0;	
							for(int i=YUKKURI_LEVEL;i<=YUKKURI_LAST_LEVEL;i++)
							{
								if(env[i].make)
									floor4_++;
								else
									break;
							}
							sprintf_s(temp,32,"(%2d/%2d) ",floor4_,MAX_YUKKURI_LEVEL+1);
							printsub(temp,false,CL_normal);
				
							sprintf_s(temp,32,"�䱫�� �� %d��  ",map_list.dungeon_enter[YUKKURI_D].floor+1-YOUKAI_MOUNTAIN_LEVEL);
							printsub(temp,false,CL_help);

							//***������
							sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_YUKKURI]);
							printsub(temp,true,you.rune[RUNE_YUKKURI]?CL_magic:CL_bad);
							//***�鳡

							printsub(blank,false,CL_warning);
							printsub("����",true,CL_normal);
						}
						else
						{
							printsub(blank,false,CL_warning);
							printsub("������",false,CL_normal);
							printsub("�������� ",false,CL_bad);
							printsub("�䱫�� �� 4��",true,CL_STAT);
							printsub(blank,false,CL_warning);
							printsub("����",true,CL_normal);
						}
					}
					else
					{
						printsub(blank,false,CL_warning);
						printsub("����",true,CL_normal);
					}
				}
				else
				{
					printsub(blank,false,CL_warning);
					printsub("����",false,CL_normal);
					printsub("�䱫�� �� ",false,CL_bad);
					printsub("�Ȱ��� ȣ�� 2��~3��",true,CL_STAT);
					printsub(blank,false,CL_warning);
					printsub("��",true,CL_normal);
				}


				
				if(floor2_>=4) //ȫ����
				{
					if(map_list.dungeon_enter[SCARLET_M].detected)
					{
						printsub(blank,false,CL_warning);
						printsub("����",false,CL_normal);
						printsub("ȫ���� ",false,CL_warning);
						int floor3_ = 0;	
						for(int i=SCARLET_LEVEL;i<=SCARLET_LEVEL_LAST_LEVEL;i++)
						{
							if(env[i].make)
								floor3_++;
							else
								break;
						}
						sprintf_s(temp,32,"(%2d/%2d) ",floor3_,MAX_SCARLET_LEVEL+1);
						printsub(temp,false,CL_normal);
				
						sprintf_s(temp,32,"�Ȱ��� ȣ�� %d��  ",map_list.dungeon_enter[SCARLET_M].floor+1-MISTY_LAKE_LEVEL);
						printsub(temp,false,CL_help);

						//***������
						sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_SCARLET]);
						printsub(temp,true,you.rune[RUNE_SCARLET]?CL_magic:CL_bad);
						//***�鳡
						
						if(floor3_>=2) //������
						{
							if(map_list.dungeon_enter[SCARLET_L].detected)
							{
								printsub(blank,false,CL_warning);
								printsub("������",false,CL_normal);
								printsub("ȫ���� ������ ",false,CL_warning);
				
								sprintf_s(temp,32,"ȫ���� %d��  ",map_list.dungeon_enter[SCARLET_L].floor+1-SCARLET_LEVEL);
								printsub(temp,true,CL_help);
							}
							else
							{
								printsub(blank,false,CL_warning);
								printsub("������",false,CL_normal);
								printsub("ȫ���� ������ ",false,CL_bad);
								printsub("ȫ���� 2��~3��",true,CL_STAT);
							}
						}
						if(floor3_>=4) //���Ͻ�
						{
							if(map_list.dungeon_enter[SCARLET_U].detected)
							{
								printsub(blank,false,CL_warning);
								printsub("������",false,CL_normal);
								printsub("ȫ���� ���Ͻ� ",false,CL_warning);
				

								sprintf_s(temp,32,"ȫ���� %d��  ",map_list.dungeon_enter[SCARLET_U].floor+1-SCARLET_LEVEL);
								printsub(temp,false,CL_help);

								//***������
								sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_SCARLET_UNDER]);
								printsub(temp,true,you.rune[RUNE_SCARLET_UNDER]?CL_magic:CL_bad);
								//***�鳡
							}
							else
							{
								printsub(blank,false,CL_warning);
								printsub("������",false,CL_normal);
								printsub("ȫ���� ���Ͻ� ",false,CL_bad);
								printsub("ȫ���� 4��",true,CL_STAT);
							}
						}

						printsub(blank,false,CL_warning);
						printsub("��",true,CL_normal);
					}
					else
					{
						printsub(blank,false,CL_warning);
						printsub("����",false,CL_normal);
						printsub("ȫ���� ",false,CL_bad);
						printsub("�Ȱ��� ȣ�� 4��~5��",true,CL_STAT);
						printsub(blank,false,CL_warning);
						printsub("��",true,CL_normal);
					}

				}

			}
			else
			{
				printsub(blank,false,CL_warning);
				printsub("��",true,CL_normal);
			}
		}
		else
		{
			printsub(blank,false,CL_warning);
			printsub("��",false,CL_normal);
			printsub("�Ȱ��� ȣ�� ",false,CL_bad);
			printsub("���� 8��~10��",true,CL_STAT);
			printsub(blank,false,CL_warning);
			printsub("��",true,CL_normal);
		}
	}
	
	if(floor_>=11) //�̱��� �׸�
	{
		if(map_list.dungeon_enter[BAMBOO].detected)
		{
			printsub(blank,false,CL_warning);
			printsub("��",false,CL_normal);
			printsub("�̱��� �׸� ",false,CL_warning);
				
			sprintf_s(temp,32,"���� %d��  ",map_list.dungeon_enter[BAMBOO].floor+1);
			printsub(temp,true,CL_help);

			{
				if(env[EIENTEI_LEVEL].make)
				{
					printsub(blank,false,CL_warning);
					printsub("����",false,CL_normal);
					printsub("������ ",false,CL_warning);
				
					sprintf_s(temp,32,"�̱��� �׸�  ");
					printsub(temp,false,CL_help);

					//***������
					sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_EIENTEI]);
					printsub(temp,true,you.rune[RUNE_EIENTEI]?CL_magic:CL_bad);
					//***�鳡
				}
				else
				{
					printsub(blank,false,CL_warning);
					printsub("����",false,CL_normal);
					printsub("������ ",false,CL_bad);
					printsub("�̱��� �׸�",true,CL_STAT);
				}
			}

			printsub(blank,false,CL_warning);
			printsub("��",true,CL_normal);
		}
		else
		{
			printsub(blank,false,CL_warning);
			printsub("��",false,CL_normal);
			printsub("�̱��� �׸� ",false,CL_bad);
			printsub("���� 11��~14��",true,CL_STAT);
			printsub(blank,false,CL_warning);
			printsub("��",true,CL_normal);
		}
	}




	
	if(floor_==MAX_DUNGEUN_LEVEL+1) //���±�
	{
		if(map_list.dungeon_enter[DEPTH].detected)
		{
			printsub(blank,false,CL_warning);
			printsub("�䱫���±� ",false,CL_warning);
				
			
			int floor2_ = 0;	
			for(int i=DEPTH_LEVEL;i<=DEPTH_LAST_LEVEL;i++)
			{
				if(env[i].make)
					floor2_++;
				else
					break;
			}
			sprintf_s(temp,32,"(%2d/%2d) ",floor2_,MAX_DEPTH_LEVEL+1);
			printsub(temp,false,CL_normal);

			sprintf_s(temp,32,"���� %d��  ",map_list.dungeon_enter[DEPTH].floor+1);
			printsub(temp,true,CL_help);

			printsub(blank,false,CL_warning);
			printsub("��",true,CL_normal);

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
						unsee))//���� ����
					{

						if(map_list.dungeon_enter[DREAM_D].detected)
						{
							printsub(blank,false,CL_warning);
							printsub("��",false,CL_normal);
							printsub("���� ���� ",false,CL_warning);
				
							sprintf_s(temp,32,"���±� %d��  ",map_list.dungeon_enter[DREAM_D].floor+1-DEPTH_LEVEL);
							printsub(temp,true,CL_help);
						
							if(env[DREAM_LEVEL].make)
							{
								if(env[MOON_LEVEL].make) //���� ����
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("���� ���� ",false,CL_warning);
				
									sprintf_s(temp,32,"���� ����  ");
									printsub(temp,false,CL_help);

									//***������
									sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_MOON]);
									printsub(temp,true,you.rune[RUNE_MOON]?CL_magic:CL_bad);
									//***�鳡
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("���� ���� ",false,CL_bad);
									printsub("���� ���� ",true,CL_STAT);
								}
							}
							printsub(blank,false,CL_warning);
							printsub("��",true,CL_normal);
						}
						else
						{
							printsub(blank,false,CL_warning);
							printsub("��",false,CL_normal);
							printsub("���� ���� ",false,CL_bad);
							printsub("���±� 2��~4��",true,CL_STAT);
							printsub(blank,false,CL_warning);
							printsub("��",true,CL_normal);
						}
						see_[0] = true;
					}

					if(!see_[1] && ((map_list.dungeon_enter[SUBTERRANEAN].detected && 					
						map_list.dungeon_enter[SUBTERRANEAN].floor - DEPTH_LEVEL == level_)  || 
						unsee))//����
					{
						if(map_list.dungeon_enter[SUBTERRANEAN].detected)
						{
							printsub(blank,false,CL_warning);
							printsub("��",false,CL_normal);
							printsub("���� ",false,CL_warning);
							int floor3_ = 0;	
							for(int i=SUBTERRANEAN_LEVEL;i<=SUBTERRANEAN_LEVEL_LAST_LEVEL;i++)
							{
								if(env[i].make)
									floor3_++;
								else
									break;
							}
							sprintf_s(temp,32,"(%2d/%2d) ",floor3_,MAX_SUBTERRANEAN_LEVEL+1);
							printsub(temp,false,CL_normal);
				
							sprintf_s(temp,32,"���±� %d��  ",map_list.dungeon_enter[SUBTERRANEAN].floor+1-DEPTH_LEVEL);
							printsub(temp,true,CL_help);

							if(env[SUBTERRANEAN_LEVEL].make)
							{
								if(env[SUBTERRANEAN_LEVEL_LAST_LEVEL].make) //�ۿ�������
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("�ۿ������� ",false,CL_warning);
				
									sprintf_s(temp,32,"���� ������  ");
									printsub(temp,false,CL_help);

									//***������
									sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_SUBTERRANEAN]);
									printsub(temp,true,you.rune[RUNE_SUBTERRANEAN]?CL_magic:CL_bad);
									//***�鳡
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("�ۿ������� ",false,CL_bad);
									printsub("���� ������ ",true,CL_STAT);
								}
							}


							printsub(blank,false,CL_warning);
							printsub("��",true,CL_normal);
						}
						else
						{
							printsub(blank,false,CL_warning);
							printsub("��",false,CL_normal);
							printsub("���� ",false,CL_bad);
							printsub("���±� 2��~4��",true,CL_STAT);
							printsub(blank,false,CL_warning);
							printsub("��",true,CL_normal);
						}
						see_[1] = true;
					}


					if(!see_[2] && ((map_list.dungeon_enter[PANDEMONIUM].detected && 					
						map_list.dungeon_enter[PANDEMONIUM].floor - DEPTH_LEVEL == level_)  || 
						unsee))//����
					{
						if(map_list.dungeon_enter[PANDEMONIUM].detected)
						{
							printsub(blank,false,CL_warning);
							printsub("��",false,CL_normal);
							printsub("���� ",false,CL_warning);
				
							sprintf_s(temp,32,"���±� %d��  ",map_list.dungeon_enter[PANDEMONIUM].floor+1-DEPTH_LEVEL);
							printsub(temp,true,CL_help);

							if(env[PANDEMONIUM_LEVEL].make)
							{
								if(env[PANDEMONIUM_LEVEL+1].make) //����
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("���� ",false,CL_warning);
				
									sprintf_s(temp,32,"����  ");
									printsub(temp,false,CL_help);

									//***������
									sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_PANDEMONIUM_MAGIC]);
									printsub(temp,true,you.rune[RUNE_PANDEMONIUM_MAGIC]?CL_magic:CL_bad);
									//***�鳡
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("���� ",false,CL_bad);
									printsub("���� ",true,CL_STAT);
								}
								if(env[PANDEMONIUM_LEVEL+2].make) //���Ἴ��
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("���Ἴ�� ",false,CL_warning);
				
									sprintf_s(temp,32,"����  ");
									printsub(temp,false,CL_help);

									//***������
									sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_PANDEMONIUM_ICE]);
									printsub(temp,true,you.rune[RUNE_PANDEMONIUM_ICE]?CL_magic:CL_bad);
									//***�鳡
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("���Ἴ�� ",false,CL_bad);
									printsub("���� ",true,CL_STAT);
								}
								if(env[PANDEMONIUM_LEVEL+3].make) //�ǵ���Ͼ�
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("�ǵ���Ͼ� ",false,CL_warning);
				
									sprintf_s(temp,32,"����  ");
									printsub(temp,false,CL_help);

									//***������
									sprintf_s(temp,32,"*%s�� ��* ",rune_string[RUNE_PANDEMONIUM_SHINKI]);
									printsub(temp,true,you.rune[RUNE_PANDEMONIUM_SHINKI]?CL_magic:CL_bad);
									//***�鳡
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("����",false,CL_normal);
									printsub("�ǵ���Ͼ� ",false,CL_bad);
									printsub("���� ",true,CL_STAT);
								}
							}
							printsub(blank,false,CL_warning);
							printsub("��",true,CL_normal);
						}
						else
						{
							printsub(blank,false,CL_warning);
							printsub("��",false,CL_normal);
							printsub("���� ",false,CL_bad);
							printsub("���±� 2��~4��",true,CL_STAT);
							printsub(blank,false,CL_warning);
							printsub("��",true,CL_normal);
						}
						see_[2] = true;
					}
				}
			}

			if(floor2_ >= MAX_DEPTH_LEVEL+1)
			{
				if(map_list.dungeon_enter[HAKUREI_D].detected)
				{
					printsub(blank,false,CL_warning);
					printsub("�����̽Ż� ",false,CL_warning);
					int floor4_ = 0;	
					for(int i=HAKUREI_LEVEL;i<=HAKUREI_LAST_LEVEL;i++)
					{
						if(env[i].make)
							floor4_++;
						else
							break;
					}
					sprintf_s(temp,32,"(%2d/%2d) ",floor4_,MAX_HAKUREI_LEVEL+1);
					printsub(temp,false,CL_normal);
				
					sprintf_s(temp,32,"���±� %d��  ",map_list.dungeon_enter[HAKUREI_D].floor+1-DEPTH_LEVEL);
					printsub(temp,false,CL_help);

					//***������
					sprintf_s(temp,32,"*%s* ",rune_string[RUNE_HAKUREI_ORB]);
					printsub(temp,true,you.rune[RUNE_HAKUREI_ORB]?CL_danger:CL_bad);
					//***�鳡
				}
				else
				{
					printsub(blank,false,CL_warning);
					printsub("�����̽Ż� ",false,CL_bad);
					printsub("���±� 5��",true,CL_STAT);
				}
			}
		}
		else
		{
			printsub(blank,false,CL_warning);
			printsub("�䱫���±� ",false,CL_bad);
			printsub("���� 15��",true,CL_STAT);
		}




	}


	
	ReleaseMutex(mutx);
	
	changedisplay(DT_SUB_TEXT);
	waitkeyinput(true);
	changedisplay(DT_GAME);
	deletesub();

}




void memorize_action(int spell_);



void run_spell() //���� ���������� 52���� �Ѿ�ٸ� ��������?
{		
	if(you.s_lunatic)
	{
		printlog("���⿡ �۽��� ���·� �� �� ����!",true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog("���� ���¿��� ������ ��� �� ����. ", true, false, false, CL_normal);
		return;
	}
	//if(you.skill[SKT_SPELLCASTING].level == 0)
	//{
	//	printlog("����� ���� �ֹ��� ��� �� ����!",true,false,false,CL_normal);
	//	return;
	//}
	deletesub();
	for(int i=0;i<2;i++)
		printsub("",true,CL_STAT); 
	{	
		char temp[100];
		sprintf_s(temp,100,"����� %d���� ������ ���� ������ %d�� ���� ������ ���Ҵ�.",you.currentSpellNum,you.remainSpellPoiont);
		printsub(temp,true,CL_help);
	}
	for(int i=0;i<1;i++)
		printsub("",true,CL_STAT); 
	printsub("       ����Ű - �̸�               ����                          ������              ����",true,CL_STAT);
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

		char temp[500];
		int i = 0;
		i += sprintf_s(temp,500,"       %c      - %s",sp_char,SpellString((spell_list)it->second));
		for(;i<250/7;i++)
			temp[i] = ' ';
		for(int j=0;j<3 && SpellSchool((spell_list)it->second,j) != SKT_ERROR;j++)
		{
			if(j)
			{
				i += sprintf_s(temp+i,500-i,"/");
			}
			i += sprintf_s(temp+i,500-i,"%s",skill_string(SpellSchool((spell_list)it->second,j)));
		}
		for(;i<450/7;i++)
			temp[i] = ' ';
		i += sprintf_s(temp+i,500-i,"%3d%%",it->first);
		for(;i<600/7;i++)
			temp[i] = ' ';
		i += sprintf_s(temp+i,500-i,"%d",SpellLevel((spell_list)it->second));
		printsub(temp,true,you.CanMemorizeSpell(it->second)?spell_color_:CL_bad);
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
		int key_ = waitkeyinput(true);
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
				printlog("�̹� ����ϰ��ִ� �����Դϴ�. ", true, false, false, CL_normal);
				return;
			}

			memorize_action(spell_);
			/*
			changedisplay(DT_GAME);
			if(spell_ == SPL_NONE)
				printlog("�������� �ʴ� �����Դϴ�.",true,false,false,CL_normal);
			else
			{		
				bool ok_ = true;
				while(ok_)
				{
					printlog(SpellString((spell_list)spell_),false,false,false,CL_normal);
					printlog(" �ֹ��� �����ðڽ��ϱ�? (y/n)",true,false,false,CL_help);
					switch(waitkeyinput())
					{
					case 'Y':
					case 'y':
						you.Memorize(spell_);
						ok_ = false;
						break;
					case 'N':
					case 'n':
					case VK_ESCAPE:
						ok_ = false;
						break;
					default:
						printlog("Y�� N�߿� �������ּ���.",true,false,false,CL_help);
						break;
					}
				}
			}*/
			break;
		}
		else if(key_ == VK_UP)
		{
			changemove(1);  //��
		}
		else if(key_ == VK_DOWN)
		{
			changemove(-1); //�Ʒ�
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(DisplayManager.log_length);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(-DisplayManager.log_length);
		}
		else if(key_ == VK_ESCAPE)
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
		printlog("����� �Ҹ��� �� �� ����.",true,false,false,CL_normal);
		return;
	}
	int rare_shout = 0;
	string shout_ = "�Ҹ� ������";
	if(randA(50)<1)
	{
		rare_shout = randA_1(5);
		switch(rare_shout)
		{
		case 1:
			shout_ = "������������! ";
			break;
		case 2:
			shout_ = "�ȳ��ϼ���! ";
			break;
		case 3:
			shout_ = "����! ";
			break;
		case 4:
			shout_ = "��ȣ! ";
			break;
		case 5:
			shout_ = "��! ";
			break;
		}
	}
	if (you.drowned)
	{
		rare_shout = 1;
		shout_ = "�����! ";
	}

	if (auto_ == 0) {
		printlog("������ ��ġ�ڽ��ϱ�?", true, false, false, CL_help);
		printlog("t - ", false, false, false, CL_normal);
		printlog(shout_, true, false, false, CL_normal);
		printlog("�Ʊ����� ��� : a - �����ض�!   s - ������ ����!", true, false, false, CL_normal);
		printlog("                w - ����ض�.   f - ����Ͷ�.", true, false, false, CL_normal);
		printlog("�׿��� Ű - ������ �Ѵ�.", true, false, false, CL_normal);
	}

	int key_ = auto_;
	if (key_ == 0)
		key_ = waitkeyinput(true);
	switch(key_)
	{
	case 't':
		if(!rare_shout)
			printlog("����� �Ҹ��� �ļ� ���Ǹ� ������.",true,false,false,CL_normal);
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
				printlog("������ �����ϰ� ����Ͻðڽ��ϱ�?", true, false, false, CL_help);
			}
			beam_iterator beam(you.position,you.position);
			projectile_infor infor(8,false,true, -3);
			if(Common_Throw(you.item_list.end(), you.GetTargetIter(), beam, &infor,-1, 0.0f, auto_>0))
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
							}
						}
					}
					printlog("����!",true,false,false,CL_normal);
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
			}
		}
		printlog("����!",true,false,false,CL_normal);
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
				it->state.SetState(MS_NORMAL);
			}
		}
		printlog("��ٷ�!",true,false,false,CL_normal);
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
			}
		}
		printlog("�����!",true,false,false,CL_normal);
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		you.SetPrevAction('t', 'f');
		break;
	default:
		printlog("�ƹ��͵� ��ġ�� �ʾҴ�.",true,false,false,CL_normal);
		break;
	}
}

void auto_pick_onoff(bool auto_)
{
	if((you.auto_pickup==0) || (!auto_ && you.auto_pickup==-1))
	{
		printlog("�ڵ� �ݱ⸦ Ȱ��ȭ�ߴ�.",true,false,false,CL_normal);
		you.auto_pickup = 1;
	}
	else
	{
		printlog("�ڵ� �ݱ⸦ �����ߴ�. (Ctrl + a Ű�� �ٽ� Ȱ��ȭ ����)",true,false,false,CL_small_danger);
		you.auto_pickup = auto_?0:-1;
	}
}


void floorMove()
{
	int current_level_ = current_level;
	dungeon_level next_ = TEMPLE_LEVEL;


	list<pair<char, string>> enter_;
	enter_.push_back(pair<char, string>('d', "����"));
	if (map_list.dungeon_enter[TEMPLE].detected)
		enter_.push_back(pair<char, string>('t', "����"));
	if (map_list.dungeon_enter[MISTY_LAKE].detected)
		enter_.push_back(pair<char, string>('l', "�Ȱ��� ȣ��"));
	if (map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected)
		enter_.push_back(pair<char, string>('m', "�䱫�� ��"));
	if (map_list.dungeon_enter[SCARLET_M].detected)
		enter_.push_back(pair<char, string>('s', "ȫ����"));
	if (map_list.dungeon_enter[SCARLET_L].detected)
		enter_.push_back(pair<char, string>('b', "ȫ����������"));
	if (map_list.dungeon_enter[SCARLET_U].detected)
		enter_.push_back(pair<char, string>('u', "ȫ��������"));
	if (map_list.dungeon_enter[BAMBOO].detected)
		enter_.push_back(pair<char, string>('a', "�̱����׸�"));
	if (map_list.dungeon_enter[YUKKURI_D].detected)
		enter_.push_back(pair<char, string>('y', "��������"));
	if (map_list.dungeon_enter[DEPTH].detected)
		enter_.push_back(pair<char, string>('p', "���±�"));
	if (map_list.dungeon_enter[SUBTERRANEAN].detected)
		enter_.push_back(pair<char, string>('h', "������"));
	if (map_list.dungeon_enter[DREAM_D].detected)
		enter_.push_back(pair<char, string>('r', "���� ����"));
	if (map_list.dungeon_enter[PANDEMONIUM].detected)
		enter_.push_back(pair<char, string>('k', "����"));
	if (map_list.dungeon_enter[HAKUREI_D].detected)
		enter_.push_back(pair<char, string>('z', "�����̽Ż�"));
	/* �������� ����
	if (map_list.dungeon_enter[ZIGURRAT].detected)
		enter_.push_back(pair<char, string>('z', "�����̽Ż�"));*/

	int num_ = 0;
	for (auto it = enter_.begin(); it != enter_.end(); it++) {
		char temp[100];
		sprintf_s(temp, 100, "%c - %s  ", it->first, it->second.c_str());
		printlog(temp, false, false, false, CL_help);
		num_++;
		if (num_ == 5) {
			enterlog();
			num_ = 0;
		}
	}
	enterlog();
	//printlog("d - ����     t - ����      l - �Ȱ��� ȣ��     m - �䱫�� ��     s - ȫ����", true, false, false, CL_help);
	//printlog("b - ȫ����������   u - ȫ��������   a - �̱����׸�  e - ������   y - �������� ", true, false, false, CL_help);
	//printlog("p - ���±�  h - ������  r - ���� ���� o - ���� ����  k - ����  z - �����̽Ż�", true, false, false, CL_help);
	printlog("��� �������� �̵��غ���? (�빮�ڷ� ��������)", false, false, false, CL_help);
	int key_ = waitkeyinput();

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
		printlog(" ���", true, false, false, CL_help);
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
		printlog(" ���", true, false, false, CL_help);
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

			Long_Move(next_);
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