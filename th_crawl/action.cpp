//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: action.cpp
//
// 내용: player의 행동들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <set>
#include <algorithm>
#include "environment.h"
#include "display.h"
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
using namespace std::tr1;


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
	//이렇게 해도되려나?

	you.search = false;
	if(env[current_level].insight_mon(MET_ENEMY))
	{
		printlog("시야안에 몬스터가 있다.",true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.s_confuse)
	{
		printlog("당신은 혼란스럽다.",true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.s_dimension)
	{
		printlog("차원이 고정된 상태에서는 지원되지않는다.",true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.resetLOS() == IT_MAP_DANGER)
	{
		printlog("시야안에 위험 요소가 있다.",true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(!PathSearch(you.position,c,you.will_move,ST_NORMAL))
	{
		printlog("그곳으로 이동할 수 없다.",true,false,false,CL_normal);	
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
		printlog("시야안에 몬스터가 없다.",true,false,false,CL_small_danger);
		return;
	}
	if(you.s_confuse)
	{
		printlog("당신은 혼란스럽다.",true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.GetHp() <= you.GetDangerHp())
	{
		printlog("자동전투하기엔 당신의 체력이 너무 적다.",true,false,false,CL_small_danger);
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
		printlog("공격할 수 있는 몬스터가 없다.",true,false,false,CL_small_danger);
		return;
	}


}

void auto_Move()
{	
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 할 수 없다!",true,false,false,CL_danger);
		return;
	}
	you.search = false;
	/*if(you.GetHunger() == HT_STARVING)	
	{
		printlog("배고픈 상태다.",false,false,false,CL_danger);
		if(you.power>=100)
			printlog("c를 눌러서 허기를 채워라!",true,false,false,CL_danger);
		else
			printlog("무언가를 먹어라!",true,false,false,CL_danger);
		return;
	}*/
	if(env[current_level].insight_mon(MET_ENEMY))
	{
		printlog("시야안에 몬스터가 있다.",true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.s_dimension)
	{
		printlog("차원이 고정된 상태에서는 지원되지않는다.",true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(env[current_level].isBamboo())
	{
		printlog("이 곳에서는 자동으로 탐색할 수 없어 보인다.",true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.s_confuse)
	{
		printlog("당신은 혼란스럽다.",true,false,false,CL_small_danger);
		while(!you.will_move.empty()){you.will_move.pop();}	
		return;
	}
	if(you.resetLOS() == IT_MAP_DANGER)
	{
		printlog("시야안에 위험 요소가 있다.",true,false,false,CL_small_danger);
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
		
		if(PathSearch(you.position,you.position,you.will_move,ST_SEARCH))
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
	printlog("탐색 완료",true,false,false,CL_normal);
}

void long_rest()
{	
	//if(you.GetHunger() == HT_STARVING)
	//{
	//	printlog("배고픈 상태다.",false,false,false,CL_danger);
	//	if(you.power>=100)
	//		printlog("c를 눌러서 허기를 채워라!",true,false,false,CL_danger);
	//	else
	//		printlog("무언가를 먹어라!",true,false,false,CL_danger);
	//	return;
	//}
	if(env[current_level].insight_mon(MET_ENEMY))
	{
		printlog("시야안에 몬스터가 있다.",true,false,false,CL_small_danger);
		return;
	}
	you.SetPrevAction('5');
	printlog("휴식을 시작합니다.",true,false,false,CL_bad);
	for(int i=0;i<100;i++)
	{		
		you.time_delay += you.GetNormalDelay();
		switch(you.TurnEnd())
		{
		case IT_HP_RECOVER:
			printlog("체력이 회복되었다.",true,false,false,CL_normal);
			return;
		case IT_MP_RECOVER:
			if(!you.pure_mp)
				printlog("영력이 회복되었다.",true,false,false,CL_normal);
			else
				printlog("체력이 회복되었다.", true, false, false, CL_normal);
			return;
		case IT_MAP_DANGER:
			printlog("시야안에 위험 요소가 있다.",true,false,false,CL_small_danger);
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
	printlog("휴식 완료",true,false,false,CL_normal);
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
			printlog("시야안에 몬스터가 있다.",true,false,false,CL_small_danger);
			while(!you.will_move.empty()){you.will_move.pop();}
			return false;
		}
		if(you.s_confuse)
		{
			printlog("당신은 혼란스럽다.",true,false,false,CL_small_danger);
			while(!you.will_move.empty()){you.will_move.pop();}	
			return false;
		}
		if(you.s_dimension)
		{
			printlog("차원이 고정된 상태에서는 지원되지않는다.",true,false,false,CL_small_danger);
			while(!you.will_move.empty()){you.will_move.pop();}	
			return false;
		}
		env[current_level].item_view_set();

		right_move = Move(temp);

		switch(you.inter)
		{
		case IT_MAP_DANGER:
			printlog("시야안에 위험 요소가 있다.",true,false,false,CL_small_danger);
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
				printlog("시야안에 몬스터가 있다.",true,false,false,CL_small_danger);
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
			printlog("(명령어: v - 설명   . - 탐색   e - 위험구역설정)",true,false,true,CL_help);	
		else
			printlog("(명령어: v - 설명   . - 탐색   <,> - 빠른 계단찾기   e - 위험구역설정)",true,false,true,CL_help);	

	}
	else if(type_ == VT_THROW || type_ == VT_DEBUF || type_ == VT_SATORI)
	{
		printlog("(명령어: v - 설명)",true,false,true,CL_help);	
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
				printlog("몬스터: ",false,false,true,CL_help);
				string s;
				s = (*it).name.name;
				printlog(s,false,false,true,CL_normal);
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

						sprintf_s(temp, 64, "성공확률: %.0f%%", percent_);
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
							sprintf_s(temp, 64, "불가능");
						else
							sprintf_s(temp, 64, "%d턴", turn_);

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
				printlog("많은 아이템들",true,false,true,CL_normal);
			}
		}
	}

	if(!(env[current_level].isInSight(you.search_pos)))
	{
		string s = "보이지 않는 곳";
		printlog(s,true,false,true,CL_normal);
		return_ = 0;
	}
	if(env[current_level].isExplore(you.search_pos.x,you.search_pos.y) || env[current_level].isMapping(you.search_pos.x,you.search_pos.y))
	{//지형확인
		
		string s = "[지형: ";
		s += dungeon_tile_tribe_type_string[env[current_level].dgtile[you.search_pos.x][you.search_pos.y].tile];
		if(env[current_level].isSilence(you.search_pos))
			s += " (정적)";
		if(env[current_level].isViolet(you.search_pos))
			s += " (바이올렛필드)";
		if (env[current_level].isSanctuary(you.search_pos))
			s += " (성역)";
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
	if(move_type = you.move(c))
	{
		if(move_type != 1) //한칸이라도 이동했을때
		{
			//아이템이 땅에 있으면 메세지 출력
			int num=0;
			bool type = false;
			if(env[current_level].dgtile[you.position.x][you.position.y].tile >= DG_DOWN_STAIR && env[current_level].dgtile[you.position.x][you.position.y].tile <= DG_SEA-1)
			{
				printlog(dungeon_tile_tribe_type_string[env[current_level].dgtile[you.position.x][you.position.y].tile],false,false,false,CL_normal);
				printlog("의 위에 서있다. ", false,false,false,CL_normal);
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
					printlog("여기엔 ",false,false,false,CL_normal);
					printlog((*start_it).GetName(),false,false,false,(*start_it).item_color());
					printlog((*start_it).GetNameInfor().name_do(true),false,false,false,CL_normal);
					printlog("있다. (,키로 줍기)",true,false,false,CL_normal);
				}
				else if(num<=4)
				{
					printlog("여기엔 다음과 같은 물건이 있다. (,키로 줍기)",true,false,false,CL_normal);
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
					printlog("여기엔 여러개의 물건이 있다. (,키로 줍기)",true,false,false,CL_normal);
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

void escape() //행동들을 취소함
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
		printlog("어느 쪽 문을 닫을꺼지?",true,false,false,CL_help);
		
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
			printlog("문을 닫았다. ",false,false,false,CL_normal);
			you.time_delay += you.GetNormalDelay();
			you.TurnEnd();
		}
		else if(close_ == -1)
		{
			printlog("무엇인가가 닫을려는데 방해되고 있다.",true,false,false,CL_normal);
		}
		else
		{
			printlog("그곳엔 닫을 수 있는 것이 없다!",true,false,false,CL_normal);
		}
		you.SetPrevAction('C');
	}
	else
	{
		printlog("근처에 닫을만한 것이 없다.",true,false,false,CL_normal);
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
		printlog("어느 쪽 문을 열꺼지?",true,false,false,CL_help);
		
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
			printlog("그곳엔 열 수 있는 것이 없다!",true,false,false,CL_normal);
		}		
		else if(result > 0)
			you.TurnEnd();
		you.SetPrevAction('O');
	}
	else
	{
		printlog("근처에 열만한 것이 없다.",true,false,false,CL_normal);
		you.SetPrevAction('O');
	}
	
}



bool CheckDimension()
{

	while(1)
	{
		printlog("계단을 이용하면 차원고정이 풀립니다. 진짜로 이용합니까?(Y/N)",false,false,false,CL_help);
		switch(waitkeyinput())
		{
		case 'Y':
			you.s_dimension = 0;
			enterlog();
			return true;
		case 'N':
		default:
			printlog(" 계속하도록!",true,false,false,CL_help);
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
			printlog("여긴 정말 위험해보인다. 그래도 내려갈거야?(Y/N)",false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				return true;
			case 'N':
			default:
				printlog(" 현명하군!",true,false,false,CL_help);
				return false;
			}
		}
		break;
	case DG_SCARLET_U_STAIR:
		if(down)
		{
			printlog("여긴 정말 위험해보인다. 그래도 내려갈거야?(Y/N)",false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				return true;
			case 'N':
			default:
				printlog(" 현명하군!",true,false,false,CL_help);
				return false;
			}
		}
		break;
	case DG_BAMBOO_STAIR:
		if(down)
		{
			printlog("이 곳은 들어가면 나오기 힘들어보인다. 그래도 내려갈거야?(Y/N)",false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				return true;
			case 'N':
			default:
				printlog(" 좋은 선택이야!",true,false,false,CL_help);
				return false;
			}
		}
		break;
	case DG_PANDEMONIUM_STAIR:
		if(down)
		{
			if(!(current_level >= PANDEMONIUM_LEVEL && current_level <= PANDEMONIUM_LAST_LEVEL))
			{
				printlog("이 곳은 들어가면 나오기 힘들어보인다. 그래도 내려갈거야?(Y/N)",false,false,false,CL_danger);
				switch(waitkeyinput())
				{
				case 'Y':
				case 'y':
					enterlog();
					return true;
				case 'N':
				default:
					printlog(" 좋은 선택이야!",true,false,false,CL_help);
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
					printlog("여기서 빠져나가면 이 층의 룬은 다신 얻을 수 없다. 정말로 나갈거야?(Y/N)",false,false,false,CL_danger);
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
			printlog("이 곳은 룬은 없지만 한번만 들어갈 수 있는 악몽의 던전이다. 준비되었어? (Y/N)", true, false, false, CL_danger);
			switch (waitkeyinput())
			{
			case 'Y':
			case 'y':
				if (you.ziggurat_level) {
					printlog("이미 들어간 적이 있으면 더 이상 들어갈 수 없어! ", true, false, false, CL_help);
					return false;
				}
				enterlog();
				return true;
			case 'N':
			default:
				printlog("좀 더 신중히 준비하도록!", true, false, false, CL_help);
				return false;
			}
		}
		break;
	case DG_DREAM_STAIR:
		if(down)
		{
			printlog("이 곳은 들어가면 나오기 힘들어보인다. 그래도 내려갈거야?(Y/N)",false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				return true;
			case 'N':
			default:
				printlog(" 좋은 선택이야!",true,false,false,CL_help);
				return false;
			}
		}
		break;
	case DG_HAKUREI_STAIR:
		if(down)
		{
			if(you.haveGoal()<3)
			{
				printlog("이 곳을 들어가기위해선 3개의 룬이 필요하다!",true,false,false,CL_normal);
				return false;
			}
			else 
			{
				printlog("당신은 3개의 룬을 입구에 꽂았다. 소음을 일으키며 문이 열렸다!",true,false,false,CL_normal);
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
			printlog("여기선 올라갈 수 없다.",true,false,false,CL_normal);
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
					printlog("계단을 내려왔다.",true,false,false,CL_normal);
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
			printlog("더 이상 내려갈 수 없다.",true,false,false,CL_normal);
		}
		break;
	case STAIR_KIND_DOWN_SPECIAL:
		if(!down)
		{
			printlog("여기선 올라갈 수 없다.",true,false,false,CL_normal);
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
			printlog("계단을 내려왔다.",true,false,false,CL_normal);
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
			printlog("여기선 내려갈 수 없다.",true,false,false,CL_normal);
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
					printlog("계단을 올라왔다.",true,false,false,CL_normal);
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
					printlog("음양옥을 줍기전까진, 당신은 게임 패배로 인정될거야. 그래도 나갈거야?(Y/N)",true,false,false,CL_danger);
				}
				else
				{
					printlog("정말로 던전을 탈출하겠습니까?(Y/N)",true,false,false,CL_normal);

				}				
				
				int direc = waitkeyinput(true);
				if(direc == 'Y')
				{
					you.dead_reason = DR_ESCAPE;
					GameOver();
					break;
				}
				printlog("계속 탐험하도록!",true,false,false,CL_normal);	
			}
		}
		break;
	case STAIR_KIND_UP_SPECIAL:
		if(down)
		{
			printlog("여기선 내려갈 수 없다.",true,false,false,CL_normal);
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
			printlog("던전으로 돌아왔다.",true,false,false,CL_normal);
			GodAccpect_Stair(false, true);
			soundmanager.playSound("stair");
			//you.resetLOS(false);
			you.TurnEnd();
			break;
		}
		break;
	default:
		printlog("여기엔 계단이 없다.",true,false,false,CL_normal);
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
			view_skill("최소한 하나의 스킬을 켜야됩니다!");
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
	SetText() = "  <얻어야할 룬>\n\n\n";



	for(int i = 0; i<RUNE_HAKUREI_ORB;i++)
	{
		remain = 10;
		remain -= strlen(rune_string[i]);
		for(;remain>0;remain--)
			SetText() += " ";
		SetText() += rune_string[i];
		SetText() += "의 룬 :";


		if(you.rune[i])
		{
			SetText() += " 획득";
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
		SetText() += "음양옥을 얻었습니다! 탈출하세요!\n";
	}
	else
	{
		SetText() += "아직 음양옥을 얻지 못했습니다.\n\n";
		SetText() += "룬을 3개이상먹으면 음양옥이 있는 하쿠레이 신사의 문이 열립니다.";
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
		}						//-----이동키끝-------
		else
			break;

	}
	changedisplay(DT_GAME);

}

void Weapon_Show()
{
	deletelog();
	char temp [100];
	printlog("무기: ",false,false,true,CL_normal);
	if(you.equipment[ET_WEAPON])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_WEAPON]->id,you.equipment[ET_WEAPON]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_WEAPON]->item_color());
	}
	else
	{
		printlog("맨손",true,false,true,CL_normal);
	}


	printlog("탄막: ",false,false,true,CL_normal);
	if(you.throw_weapon)
	{
		sprintf_s(temp,100,"%c) %s",you.throw_weapon->id,you.throw_weapon->GetName().c_str());
		printlog(temp,true,false,true,you.throw_weapon->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
	}
}

void Armour_Show()
{
	deletelog();
	char temp [100];
	printlog("몸통: ",false,false,true,CL_normal);
	if(you.equipment[ET_ARMOR])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_ARMOR]->id,you.equipment[ET_ARMOR]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_ARMOR]->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
	}

	printlog("방패: ",false,false,true,CL_normal);
	if(you.equipment[ET_SHIELD])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_SHIELD]->id,you.equipment[ET_SHIELD]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_SHIELD]->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
	}	
	
	printlog("머리: ",false,false,true,CL_normal);
	if(you.equipment[ET_HELMET])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_HELMET]->id,you.equipment[ET_HELMET]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_HELMET]->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
	}

	
	printlog("망토: ",false,false,true,CL_normal);
	if(you.equipment[ET_CLOAK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_CLOAK]->id,you.equipment[ET_CLOAK]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_CLOAK]->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
	}

	printlog("손: ",false,false,true,CL_normal);
	if(you.equipment[ET_GLOVE])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_GLOVE]->id,you.equipment[ET_GLOVE]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_GLOVE]->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
	}

	printlog("발: ",false,false,true,CL_normal);
	if(you.equipment[ET_BOOTS])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_BOOTS]->id,you.equipment[ET_BOOTS]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_BOOTS]->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
	}


}




void Amulet_Show()
{
	deletelog();
	char temp [100];
	printlog("목걸이  : ",false,false,true,CL_normal);
	if(you.equipment[ET_NECK])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_NECK]->id,you.equipment[ET_NECK]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_NECK]->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
	}

	printlog("왼반지  : ",false,false,true,CL_normal);
	if(you.equipment[ET_LEFT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_LEFT]->id,you.equipment[ET_LEFT]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_LEFT]->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
	}
	
	printlog("오른반지: ",false,false,true,CL_normal);
	if(you.equipment[ET_RIGHT])
	{
		sprintf_s(temp,100,"%c) %s",you.equipment[ET_RIGHT]->id,you.equipment[ET_RIGHT]->GetName().c_str());
		printlog(temp,true,false,true,you.equipment[ET_RIGHT]->item_color());
	}
	else
	{
		printlog("없음",true,false,true,CL_normal);
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
		printlog("당신의 방어구는 편한 편이다. ",false,false,false,CL_normal);
		break;
	case 2:
		printlog("당신의 방어구는 불편하다. ",false,false,false,CL_normal);
		break;
	case 3:
		printlog("당신의 방어구는 매우 불편하다. ",false,false,false,CL_normal);
		break;
	case 4:
	default:
		printlog("방어구가 당신을 입고있다. ",false,false,false,CL_normal);
		break;
	}/*
	switch(you.GetShieldPanlty())
	{
	case 0:
		break;
	case 1:
		printlog("당신의 방패는 편한 편이다.",false,false,false,CL_normal);
		break;
	case 2:
	case 3:
		printlog("당신의 방패는 약간 불편하다.",false,false,false,CL_normal);
		break;
	case 4:
		printlog("당신의 방패는 불편하다.",false,false,false,CL_normal);
		break;
	case 5:
	case 6:
		printlog("당신의 방패는 매우 불편하다.",false,false,false,CL_normal);
		break;
	default:
		printlog("당신은 방패에 끌려다닌다.",false,false,false,CL_normal);
		break;
	}*/
	enterlog();
}
void Experience_Show()
{
	char temp [100];
	sprintf_s(temp,100,"당신은 %d레벨 %s %s입니다.", you.level, tribe_type_string[you.tribe], job_type_string[you.job]);
	printlog(temp,true,false,false,CL_normal);
	if(you.GetNeedExp(you.level-1) > 0)
	{
		sprintf_s(temp,100,"다음 레벨까지 %d의 경험치가 남았습니다.",you.GetNeedExp(you.level-1) - you.exper);
		printlog(temp,true,false,false,CL_normal);
	}
	else
	{
		sprintf_s(temp,100,"당신은 현재 최고 레벨에 도달해있습니다.");
		printlog(temp,true,false,false,CL_normal);
	}
}

//bool Eat_Power()
//{
//	if(HT_NORMAL <= you.GetHunger())
//	{
//		printlog("당신은 아직 배고프지 않다.",true,false,false,CL_normal);
//		return false;
//	}
//	else if(you.power < 100)
//	{
//		printlog("파워가 부족하다.",true,false,false,CL_normal);
//		return false;
//	}
//	printlog("P를 1 소모하여 만복도를 채우시겠습니까?(y/n)",true,false,false,CL_help);
//	int temp = waitkeyinput();
//	if(temp == 'y' || temp == 'Y')
//	{
//		you.PowUpDown(-100, true);
//		you.HungerApply(3000);
//		printlog("당신은 포만감을 느꼈다.",true,false,false,CL_normal);
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
	printsub("<던전 진행도>",true,CL_warning);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub(blank,false,CL_warning);
	printsub("던전 ",false,CL_warning);
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
	printsub("│",true,CL_normal);
	if(floor_>=3) //신전등장
	{
		if(map_list.dungeon_enter[TEMPLE].detected)
		{
			printsub(blank,false,CL_warning);
			printsub("├",false,CL_normal);
			printsub("신전 ",false,CL_warning);			
			sprintf_s(temp,32,"(%2d/%2d) ",env[TEMPLE_LEVEL].make?1:0,1);
			printsub(temp,false,CL_normal);
				
			sprintf_s(temp,32,"던전 %d층",map_list.dungeon_enter[TEMPLE].floor+1);
			printsub(temp,true,CL_help);
			printsub(blank,false,CL_warning);
			printsub("│",true,CL_normal);
		}
		else
		{
			printsub(blank,false,CL_warning);
			printsub("├",false,CL_normal);
			printsub("신전 ",false,CL_bad);
			printsub("던전 3층~6층",true,CL_STAT);
			printsub(blank,false,CL_warning);
			printsub("│",true,CL_normal);
		}
	}	
	if(floor_>=8) //안개의호수
	{
		if(map_list.dungeon_enter[MISTY_LAKE].detected)
		{
			printsub(blank,false,CL_warning);
			printsub("├",false,CL_normal);
			printsub("안개의 호수 ",false,CL_warning);
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
				
			sprintf_s(temp,32,"던전 %d층",map_list.dungeon_enter[MISTY_LAKE].floor+1);
			printsub(temp,true,CL_help);

			if(floor2_>=2) //요괴의산
			{
				if(map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected)
				{
					printsub(blank,false,CL_warning);
					printsub("│├",false,CL_normal);
					printsub("요괴의 산 ",false,CL_warning);
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
				
					sprintf_s(temp,32,"안개의 호수 %d층  ",map_list.dungeon_enter[YOUKAI_MOUNTAIN].floor+1-MISTY_LAKE_LEVEL);
					printsub(temp,false,CL_help);

					//***룬있음
					sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_YOUKAI_MOUNTAIN]);
					printsub(temp,true,you.rune[RUNE_YOUKAI_MOUNTAIN]?CL_magic:CL_bad);
					//***룬끝

					if(floor3_>=MAX_YOUKAI_MOUNTAIN_LEVEL+1) //윳쿠리굴
					{
						if(map_list.dungeon_enter[YUKKURI_D].detected)
						{
							printsub(blank,false,CL_warning);
							printsub("││└",false,CL_normal);
							printsub("윳쿠리둥지 ",false,CL_warning);
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
				
							sprintf_s(temp,32,"요괴의 산 %d층  ",map_list.dungeon_enter[YUKKURI_D].floor+1-YOUKAI_MOUNTAIN_LEVEL);
							printsub(temp,false,CL_help);

							//***룬있음
							sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_YUKKURI]);
							printsub(temp,true,you.rune[RUNE_YUKKURI]?CL_magic:CL_bad);
							//***룬끝

							printsub(blank,false,CL_warning);
							printsub("││",true,CL_normal);
						}
						else
						{
							printsub(blank,false,CL_warning);
							printsub("││└",false,CL_normal);
							printsub("윳쿠리둥지 ",false,CL_bad);
							printsub("요괴의 산 4층",true,CL_STAT);
							printsub(blank,false,CL_warning);
							printsub("││",true,CL_normal);
						}
					}
					else
					{
						printsub(blank,false,CL_warning);
						printsub("││",true,CL_normal);
					}
				}
				else
				{
					printsub(blank,false,CL_warning);
					printsub("│├",false,CL_normal);
					printsub("요괴의 산 ",false,CL_bad);
					printsub("안개의 호수 2층~3층",true,CL_STAT);
					printsub(blank,false,CL_warning);
					printsub("│",true,CL_normal);
				}


				
				if(floor2_>=4) //홍마관
				{
					if(map_list.dungeon_enter[SCARLET_M].detected)
					{
						printsub(blank,false,CL_warning);
						printsub("│└",false,CL_normal);
						printsub("홍마관 ",false,CL_warning);
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
				
						sprintf_s(temp,32,"안개의 호수 %d층  ",map_list.dungeon_enter[SCARLET_M].floor+1-MISTY_LAKE_LEVEL);
						printsub(temp,false,CL_help);

						//***룬있음
						sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_SCARLET]);
						printsub(temp,true,you.rune[RUNE_SCARLET]?CL_magic:CL_bad);
						//***룬끝
						
						if(floor3_>=2) //도서관
						{
							if(map_list.dungeon_enter[SCARLET_L].detected)
							{
								printsub(blank,false,CL_warning);
								printsub("│　├",false,CL_normal);
								printsub("홍마관 도서관 ",false,CL_warning);
				
								sprintf_s(temp,32,"홍마관 %d층  ",map_list.dungeon_enter[SCARLET_L].floor+1-SCARLET_LEVEL);
								printsub(temp,true,CL_help);
							}
							else
							{
								printsub(blank,false,CL_warning);
								printsub("│　├",false,CL_normal);
								printsub("홍마관 도서관 ",false,CL_bad);
								printsub("홍마관 2층~3층",true,CL_STAT);
							}
						}
						if(floor3_>=4) //지하실
						{
							if(map_list.dungeon_enter[SCARLET_U].detected)
							{
								printsub(blank,false,CL_warning);
								printsub("│　└",false,CL_normal);
								printsub("홍마관 지하실 ",false,CL_warning);
				

								sprintf_s(temp,32,"홍마관 %d층  ",map_list.dungeon_enter[SCARLET_U].floor+1-SCARLET_LEVEL);
								printsub(temp,false,CL_help);

								//***룬있음
								sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_SCARLET_UNDER]);
								printsub(temp,true,you.rune[RUNE_SCARLET_UNDER]?CL_magic:CL_bad);
								//***룬끝
							}
							else
							{
								printsub(blank,false,CL_warning);
								printsub("│　└",false,CL_normal);
								printsub("홍마관 지하실 ",false,CL_bad);
								printsub("홍마관 4층",true,CL_STAT);
							}
						}

						printsub(blank,false,CL_warning);
						printsub("│",true,CL_normal);
					}
					else
					{
						printsub(blank,false,CL_warning);
						printsub("│└",false,CL_normal);
						printsub("홍마관 ",false,CL_bad);
						printsub("안개의 호수 4층~5층",true,CL_STAT);
						printsub(blank,false,CL_warning);
						printsub("│",true,CL_normal);
					}

				}

			}
			else
			{
				printsub(blank,false,CL_warning);
				printsub("│",true,CL_normal);
			}
		}
		else
		{
			printsub(blank,false,CL_warning);
			printsub("├",false,CL_normal);
			printsub("안개의 호수 ",false,CL_bad);
			printsub("던전 8층~10층",true,CL_STAT);
			printsub(blank,false,CL_warning);
			printsub("│",true,CL_normal);
		}
	}
	
	if(floor_>=11) //미궁의 죽림
	{
		if(map_list.dungeon_enter[BAMBOO].detected)
		{
			printsub(blank,false,CL_warning);
			printsub("├",false,CL_normal);
			printsub("미궁의 죽림 ",false,CL_warning);
				
			sprintf_s(temp,32,"던전 %d층  ",map_list.dungeon_enter[BAMBOO].floor+1);
			printsub(temp,true,CL_help);

			{
				if(env[EIENTEI_LEVEL].make)
				{
					printsub(blank,false,CL_warning);
					printsub("│└",false,CL_normal);
					printsub("영원정 ",false,CL_warning);
				
					sprintf_s(temp,32,"미궁의 죽림  ");
					printsub(temp,false,CL_help);

					//***룬있음
					sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_EIENTEI]);
					printsub(temp,true,you.rune[RUNE_EIENTEI]?CL_magic:CL_bad);
					//***룬끝
				}
				else
				{
					printsub(blank,false,CL_warning);
					printsub("│└",false,CL_normal);
					printsub("영원정 ",false,CL_bad);
					printsub("미궁의 죽림",true,CL_STAT);
				}
			}

			printsub(blank,false,CL_warning);
			printsub("│",true,CL_normal);
		}
		else
		{
			printsub(blank,false,CL_warning);
			printsub("├",false,CL_normal);
			printsub("미궁의 죽림 ",false,CL_bad);
			printsub("던전 11층~14층",true,CL_STAT);
			printsub(blank,false,CL_warning);
			printsub("│",true,CL_normal);
		}
	}




	
	if(floor_==MAX_DUNGEUN_LEVEL+1) //짐승길
	{
		if(map_list.dungeon_enter[DEPTH].detected)
		{
			printsub(blank,false,CL_warning);
			printsub("요괴짐승길 ",false,CL_warning);
				
			
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

			sprintf_s(temp,32,"던전 %d층  ",map_list.dungeon_enter[DEPTH].floor+1);
			printsub(temp,true,CL_help);

			printsub(blank,false,CL_warning);
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
							printsub(blank,false,CL_warning);
							printsub("├",false,CL_normal);
							printsub("꿈의 세계 ",false,CL_warning);
				
							sprintf_s(temp,32,"짐승길 %d층  ",map_list.dungeon_enter[DREAM_D].floor+1-DEPTH_LEVEL);
							printsub(temp,true,CL_help);
						
							if(env[DREAM_LEVEL].make)
							{
								if(env[MOON_LEVEL].make) //달의 도시
								{
									printsub(blank,false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub("달의 도시 ",false,CL_warning);
				
									sprintf_s(temp,32,"꿈의 세계  ");
									printsub(temp,false,CL_help);

									//***룬있음
									sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_MOON]);
									printsub(temp,true,you.rune[RUNE_MOON]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub("달의 도시 ",false,CL_bad);
									printsub("꿈의 세계 ",true,CL_STAT);
								}
							}
							printsub(blank,false,CL_warning);
							printsub("│",true,CL_normal);
						}
						else
						{
							printsub(blank,false,CL_warning);
							printsub("├",false,CL_normal);
							printsub("꿈의 세계 ",false,CL_bad);
							printsub("짐승길 2층~4층",true,CL_STAT);
							printsub(blank,false,CL_warning);
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
							printsub(blank,false,CL_warning);
							printsub("├",false,CL_normal);
							printsub("지저 ",false,CL_warning);
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
				
							sprintf_s(temp,32,"짐승길 %d층  ",map_list.dungeon_enter[SUBTERRANEAN].floor+1-DEPTH_LEVEL);
							printsub(temp,true,CL_help);

							if(env[SUBTERRANEAN_LEVEL].make)
							{
								if(env[SUBTERRANEAN_LEVEL_LAST_LEVEL].make) //작열지옥터
								{
									printsub(blank,false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub("작열지옥터 ",false,CL_warning);
				
									sprintf_s(temp,32,"지저 최하층  ");
									printsub(temp,false,CL_help);

									//***룬있음
									sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_SUBTERRANEAN]);
									printsub(temp,true,you.rune[RUNE_SUBTERRANEAN]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub("작열지옥터 ",false,CL_bad);
									printsub("지저 최하층 ",true,CL_STAT);
								}
							}


							printsub(blank,false,CL_warning);
							printsub("│",true,CL_normal);
						}
						else
						{
							printsub(blank,false,CL_warning);
							printsub("├",false,CL_normal);
							printsub("지저 ",false,CL_bad);
							printsub("짐승길 2층~4층",true,CL_STAT);
							printsub(blank,false,CL_warning);
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
							printsub(blank,false,CL_warning);
							printsub("├",false,CL_normal);
							printsub("마계 ",false,CL_warning);
				
							sprintf_s(temp,32,"짐승길 %d층  ",map_list.dungeon_enter[PANDEMONIUM].floor+1-DEPTH_LEVEL);
							printsub(temp,true,CL_help);

							if(env[PANDEMONIUM_LEVEL].make)
							{
								if(env[PANDEMONIUM_LEVEL+1].make) //법계
								{
									printsub(blank,false,CL_warning);
									printsub("│├",false,CL_normal);
									printsub("법계 ",false,CL_warning);
				
									sprintf_s(temp,32,"마계  ");
									printsub(temp,false,CL_help);

									//***룬있음
									sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_PANDEMONIUM_MAGIC]);
									printsub(temp,true,you.rune[RUNE_PANDEMONIUM_MAGIC]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("│├",false,CL_normal);
									printsub("법계 ",false,CL_bad);
									printsub("마계 ",true,CL_STAT);
								}
								if(env[PANDEMONIUM_LEVEL+2].make) //빙결세계
								{
									printsub(blank,false,CL_warning);
									printsub("│├",false,CL_normal);
									printsub("빙결세계 ",false,CL_warning);
				
									sprintf_s(temp,32,"마계  ");
									printsub(temp,false,CL_help);

									//***룬있음
									sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_PANDEMONIUM_ICE]);
									printsub(temp,true,you.rune[RUNE_PANDEMONIUM_ICE]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("│├",false,CL_normal);
									printsub("빙결세계 ",false,CL_bad);
									printsub("마계 ",true,CL_STAT);
								}
								if(env[PANDEMONIUM_LEVEL+3].make) //판데모니엄
								{
									printsub(blank,false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub("판데모니엄 ",false,CL_warning);
				
									sprintf_s(temp,32,"마계  ");
									printsub(temp,false,CL_help);

									//***룬있음
									sprintf_s(temp,32,"*%s의 룬* ",rune_string[RUNE_PANDEMONIUM_SHINKI]);
									printsub(temp,true,you.rune[RUNE_PANDEMONIUM_SHINKI]?CL_magic:CL_bad);
									//***룬끝
								}
								else
								{
									printsub(blank,false,CL_warning);
									printsub("│└",false,CL_normal);
									printsub("판데모니엄 ",false,CL_bad);
									printsub("마계 ",true,CL_STAT);
								}
							}
							printsub(blank,false,CL_warning);
							printsub("│",true,CL_normal);
						}
						else
						{
							printsub(blank,false,CL_warning);
							printsub("├",false,CL_normal);
							printsub("마계 ",false,CL_bad);
							printsub("짐승길 2층~4층",true,CL_STAT);
							printsub(blank,false,CL_warning);
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
					printsub(blank,false,CL_warning);
					printsub("하쿠레이신사 ",false,CL_warning);
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
				
					sprintf_s(temp,32,"짐승길 %d층  ",map_list.dungeon_enter[HAKUREI_D].floor+1-DEPTH_LEVEL);
					printsub(temp,false,CL_help);

					//***룬있음
					sprintf_s(temp,32,"*%s* ",rune_string[RUNE_HAKUREI_ORB]);
					printsub(temp,true,you.rune[RUNE_HAKUREI_ORB]?CL_danger:CL_bad);
					//***룬끝
				}
				else
				{
					printsub(blank,false,CL_warning);
					printsub("하쿠레이신사 ",false,CL_bad);
					printsub("짐승길 5층",true,CL_STAT);
				}
			}
		}
		else
		{
			printsub(blank,false,CL_warning);
			printsub("요괴짐승길 ",false,CL_bad);
			printsub("던전 15층",true,CL_STAT);
		}




	}


	
	ReleaseMutex(mutx);
	
	changedisplay(DT_SUB_TEXT);
	waitkeyinput(true);
	changedisplay(DT_GAME);
	deletesub();

}




void memorize_action(int spell_);



void run_spell() //만약 마법레벨이 52개를 넘어간다면 배울수없다?
{		
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 할 수 없다!",true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog("유령 상태에선 마법을 배울 수 없다. ", true, false, false, CL_normal);
		return;
	}
	//if(you.skill[SKT_SPELLCASTING].level == 0)
	//{
	//	printlog("당신은 아직 주문을 배울 수 없다!",true,false,false,CL_normal);
	//	return;
	//}
	deletesub();
	for(int i=0;i<2;i++)
		printsub("",true,CL_STAT); 
	{	
		char temp[100];
		sprintf_s(temp,100,"당신은 %d개의 마법을 배우고 있으며 %d의 마법 레벨이 남았다.",you.currentSpellNum,you.remainSpellPoiont);
		printsub(temp,true,CL_help);
	}
	for(int i=0;i<1;i++)
		printsub("",true,CL_STAT); 
	printsub("       단축키 - 이름               학파                          실패율              레벨",true,CL_STAT);
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
				printlog("이미 기억하고있는 마법입니다. ", true, false, false, CL_normal);
				return;
			}

			memorize_action(spell_);
			/*
			changedisplay(DT_GAME);
			if(spell_ == SPL_NONE)
				printlog("존재하지 않는 스펠입니다.",true,false,false,CL_normal);
			else
			{		
				bool ok_ = true;
				while(ok_)
				{
					printlog(SpellString((spell_list)spell_),false,false,false,CL_normal);
					printlog(" 주문을 익히시겠습니까? (y/n)",true,false,false,CL_help);
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
						printlog("Y와 N중에 선택해주세요.",true,false,false,CL_help);
						break;
					}
				}
			}*/
			break;
		}
		else if(key_ == VK_UP)
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
		printlog("당신은 소리를 낼 수 없다.",true,false,false,CL_normal);
		return;
	}
	int rare_shout = 0;
	string shout_ = "소리 지르기";
	if(randA(10)<1)
	{
		rare_shout = randA_1(5);
		switch(rare_shout)
		{
		case 1:
			shout_ = "왁! ";
			break;
		case 2:
			shout_ = "야호! ";
			break;
		case 3:
			shout_ = "우와아! ";
			break;
		case 4:
			shout_ = "우어어어ㅓ어어! ";
			break;
		case 5:
			shout_ = "와! ";
			break;
		}
	}
	if (you.drowned)
	{
		rare_shout = 1;
		shout_ = "살려줘! ";
	}

	if (auto_ == 0) {
		printlog("무엇을 외치겠습니까?", true, false, false, CL_help);
		printlog("t - ", false, false, false, CL_normal);
		printlog(shout_, true, false, false, CL_normal);
		printlog("아군에게 명령 : a - 공격해라!   s - 공격을 멈춰!", true, false, false, CL_normal);
		printlog("                w - 대기해라.   f - 따라와라.", true, false, false, CL_normal);
		printlog("그외의 키 - 조용히 한다.", true, false, false, CL_normal);
	}

	int key_ = auto_;
	if (key_ == 0)
		key_ = waitkeyinput(true);
	switch(key_)
	{
	case 't':
		if(!rare_shout)
			printlog("당신은 소리를 쳐서 주의를 끌었다.",true,false,false,CL_normal);
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
				printlog("누구를 공격하게 명령하시겠습니까?", true, false, false, CL_help);
			}
			beam_iterator beam(you.position,you.position);
			projectile_infor infor(8,false,true);
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
					printlog("공격!",true,false,false,CL_normal);
					you.time_delay += you.GetNormalDelay();
					you.TurnEnd();
					Noise(you.position, 12);
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
				it->state.SetState(MS_FOLLOW);
			}
		}
		printlog("멈춰!",true,false,false,CL_normal);
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		Noise(you.position, 12);
		you.SetPrevAction('t', 's');
		break;
	case 'w':
		printlog("기다려!(미구현)",true,false,false,CL_normal);
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		Noise(you.position, 12);
		you.SetPrevAction('t', 'w');
		break;
	case 'f':
		printlog("따라와!(미구현)",true,false,false,CL_normal);
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		Noise(you.position, 12);
		you.SetPrevAction('t', 'f');
		break;
	default:
		printlog("아무것도 외치지 않았다.",true,false,false,CL_normal);
		break;
	}
}

void auto_pick_onoff(bool auto_)
{
	if((you.auto_pickup==0) || (!auto_ && you.auto_pickup==-1))
	{
		printlog("자동 줍기를 활성화했다.",true,false,false,CL_normal);
		you.auto_pickup = 1;
	}
	else
	{
		printlog("자동 줍기를 해제했다. (Ctrl + a 키로 다시 활성화 가능)",true,false,false,CL_small_danger);
		you.auto_pickup = auto_?0:-1;
	}
}


void floorMove()
{
	int current_level_ = current_level;
	dungeon_level next_ = TEMPLE_LEVEL;


	list<pair<char, string>> enter_;
	enter_.push_back(pair<char, string>('d', "던전"));
	if (map_list.dungeon_enter[TEMPLE].detected)
		enter_.push_back(pair<char, string>('t', "신전"));
	if (map_list.dungeon_enter[MISTY_LAKE].detected)
		enter_.push_back(pair<char, string>('l', "안개의 호수"));
	if (map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected)
		enter_.push_back(pair<char, string>('m', "요괴의 산"));
	if (map_list.dungeon_enter[SCARLET_M].detected)
		enter_.push_back(pair<char, string>('s', "홍마관"));
	if (map_list.dungeon_enter[SCARLET_L].detected)
		enter_.push_back(pair<char, string>('b', "홍마관도서관"));
	if (map_list.dungeon_enter[SCARLET_U].detected)
		enter_.push_back(pair<char, string>('u', "홍마관지하"));
	if (map_list.dungeon_enter[BAMBOO].detected)
		enter_.push_back(pair<char, string>('a', "미궁의죽림"));
	if (map_list.dungeon_enter[YUKKURI_D].detected)
		enter_.push_back(pair<char, string>('y', "윳쿠리둥지"));
	if (map_list.dungeon_enter[DEPTH].detected)
		enter_.push_back(pair<char, string>('p', "짐승길"));
	if (map_list.dungeon_enter[SUBTERRANEAN].detected)
		enter_.push_back(pair<char, string>('h', "지령전"));
	if (map_list.dungeon_enter[DREAM_D].detected)
		enter_.push_back(pair<char, string>('r', "꿈의 세계"));
	if (map_list.dungeon_enter[PANDEMONIUM].detected)
		enter_.push_back(pair<char, string>('k', "마계"));
	if (map_list.dungeon_enter[HAKUREI_D].detected)
		enter_.push_back(pair<char, string>('z', "하쿠레이신사"));
	/* 지구랏은 아직
	if (map_list.dungeon_enter[ZIGURRAT].detected)
		enter_.push_back(pair<char, string>('z', "하쿠레이신사"));*/

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
	//printlog("d - 던전     t - 신전      l - 안개의 호수     m - 요괴의 산     s - 홍마관", true, false, false, CL_help);
	//printlog("b - 홍마관도서관   u - 홍마관지하   a - 미궁의죽림  e - 영원정   y - 윳쿠리둥지 ", true, false, false, CL_help);
	//printlog("p - 짐승길  h - 지령전  r - 꿈의 세계 o - 달의 세계  k - 마계  z - 하쿠레이신사", true, false, false, CL_help);
	printlog("어느 던전으로 이동해볼까? (대문자로 마지막층)", false, false, false, CL_help);
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
		printlog(" 취소", true, false, false, CL_help);
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
		printlog(" 취소", true, false, false, CL_help);
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