//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: arena.cpp
//
// 내용: 아레나
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "map.h"
#include "skill_use.h"
#include "mon_infor.h"
#include "event.h"
#include "note.h"


int makeMonsterid(int min_level, int max_level)
{
	while(1)
	{
		vector<int> mon_list_;

		for(int i = 0; i < MON_MAX; i++)
		{
			int char_level= (mondata[i].flag & M_FLAG_UNIQUE) ? mondata[i].level*1.5f : mondata[i].level;
			if(!(mondata[i].flag & M_FLAG_CANT_NETURAL)
				&& !(mondata[i].flag & M_FLAG_CANT_GROUND)
				&&  char_level>= min_level && char_level <= max_level)
			{
				mon_list_.push_back(i);
			}
		}

		//sort(mon_list_.begin(), mon_list_.end(),[&](const int &lf, const int &rf)
		//{
		//	return mondata[lf].level < mondata[rf].level;
		//});

	
		if(mon_list_.empty())
		{
			min_level--;
			max_level++;
			continue;
		}
		else
		{
			return mon_list_[randA(mon_list_.size()-1)];
		}

	}

}




void createarenamon(int num, int mon_id_ ,bool left)
{
	int x_ = 0, y_ = 0;
	do
	{
		x_ = DG_MAX_X/2+(left?-3:3)+rand_int(-1,1), y_ = DG_MAX_Y/2+rand_int(-2,2);
	}
	while(!env[num].isMove(x_,y_) || env[current_level].isMonsterPos(x_,y_));

	monster *mon_ = env[num].AddMonster(mon_id_,left?M_FLAG_NETURALY:0,coord_def(x_,y_));
	mon_->state.SetState(MS_NORMAL);
}


void SeleteArenaMonster(int num, int level)
{
	int base_level_ = level+2;
	int range_min_ = 2, range_max_ = 2;

	range_min_ += level/8;
	range_max_ += level/8;

	
	vector<int> team_list_[2];

	
	AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_ARENA, PlaceHolderHelper(to_string(level))),CL_help);


	for(int i = 0; i<2; i++)
	{
		int num_ =	randA_1(randA_1(1+ level/3));


		int temp_base_level_ = base_level_;
		
		if(num_ > 1 )
			temp_base_level_ = (temp_base_level_ * (18 - num_) /24);

	

		temp_base_level_ = temp_base_level_ - (num_-1);
		int temp_range_min_ = range_min_ - (num_-1)/3;
		int temp_range_max_ = range_max_/*+ (num_-1)/4*/;

		for(int j=0; j < num_; j++)
		{
			team_list_[i].push_back(makeMonsterid(temp_base_level_-temp_range_min_,temp_base_level_+temp_range_max_));

		}


		sort(team_list_[i].begin(), team_list_[i].end(),[&](const int &lf, const int &rf)
		{
			return mondata[lf].level < mondata[rf].level;
		});

		if(i==1)//두 팀이 완벽히 동일구성일때 막아야됨
		{
			bool same = true;
			if(team_list_[0].size() == team_list_[1].size())
			{
				for(int j=0; j < team_list_[0].size(); j++)
				{
					if(team_list_[0][j] != team_list_[1][j])
						same = false;
				}
			}
			else
				same = false;

			if(same)
			{
				range_min_ -= 1;
				range_max_ += 1;
				team_list_[1].clear();
				i = 0;
			}
		}	
	}


	
	for(int i = 0; i<2; i++)
	{
		


		for(int j=0; j < team_list_[i].size(); j++)
		{
			AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(i==0?LOC_SYSTEM_NOTE_ARENA_TEAM_LEFT:LOC_SYSTEM_NOTE_ARENA_TEAM_RIGHT, 
				PlaceHolderHelper(mondata[team_list_[i][j]].name.getName())),CL_green);
			createarenamon(num, team_list_[i][j], i == 0);
		}
		if(i==0)
			AddNote(you.turn,CurrentLevelString(),"vs",CL_green);
	}
}




void arena_event(int num)
{
	if(map_list.bamboo_count == 10)
	{
		
		if(you.level == 27)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_CLEAR),true,false,false,CL_help);
			AddNote(you.turn,CurrentLevelString(),LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_WIN),CL_help);
		}
		else
		{
			auto it = env[num].mon_vector.begin();
			for( ;it != env[num].mon_vector.end();it++)
			{
				if(it->isLive())
				{
					(*it).dead(PRT_NEUTRAL, false, true);
				}
			}


			for(int i = DG_MAX_Y/2 - 7; i <= DG_MAX_Y/2 + 7; i++)
			{
				if(i >=DG_MAX_Y/2 - 3 && i <= DG_MAX_Y/2 + 3)
					env[num].dgtile[DG_MAX_X/2][i].tile = DG_GLASS;
				else
					env[num].dgtile[DG_MAX_X/2][i].tile = DG_GRASS;
			}
			env[num].allCalculateAutoTile();

			SeleteArenaMonster(num, you.level);

			map_list.bamboo_rate = 0;
			
			if(you.level == 26)
				printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_LAST_BATTLE),true,false,false,CL_normal);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_CHOOSE),true,false,false,CL_normal);
		}

	}
	
	if(map_list.bamboo_count == 20)
	{
		for(int i = DG_MAX_Y/2 - 7; i <= DG_MAX_Y/2 + 7; i++)
		{
			if(i >= DG_MAX_Y/2 - 2 && i <= DG_MAX_Y/2 + 2)
				env[num].dgtile[DG_MAX_X/2][i].tile = DG_FLOOR;
			else
				env[num].dgtile[DG_MAX_X/2][i].tile = DG_GLASS;
		}
		env[num].allCalculateAutoTile();
		if(you.position.x == DG_MAX_X/2)
			you.Blink(1);
		
		printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_START),true,false,false,CL_normal);
	}

	
	if(map_list.bamboo_count > 20 && map_list.bamboo_rate == 0)
	{
		bool left_dead_ = true;
		bool right_dead_ = true;

		auto it = env[num].mon_vector.begin();
		for( ;it != env[num].mon_vector.end();it++)
		{
			if(it->isLive())
			{
				if(it->s_neutrality == 1)
				{
					left_dead_ = false;
				}
				if(it->s_neutrality == 0)
				{
					right_dead_ = false;
				}
			}
		}

		if(left_dead_ && !right_dead_)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_RIGHT_WIN),true,false,false,CL_help);
			if(you.position.x > DG_MAX_X/2)
			{
				map_list.bamboo_count = -10;
				you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
				AddNote(you.turn,CurrentLevelString(),
					LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_SUCCESS) + " " + LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_WIN_RIGHT)
					,CL_normal);
			}
			else
			{
				AddNote(you.turn,CurrentLevelString(),
					LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_FAIL) + " " + LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_WIN_RIGHT)
					,CL_danger);
				map_list.god_num++;
				if(map_list.god_num<3)
				{
					char temp[200];
					sprintf_s(temp,200,"오답이다! 남은 기회 %d",3-map_list.god_num);
					printlog(temp,true,false,false,CL_danger);
					AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_ARENA_LEFT_LIFE, PlaceHolderHelper(to_string(3-map_list.god_num))) ,CL_danger);
					map_list.bamboo_count = -10;
				}
				else
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_FAIL),true,false,false,CL_danger);
					map_list.bamboo_count = 121;
				}
		

			}
			map_list.bamboo_rate = 1;
		}
		if(!left_dead_ && right_dead_)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_LEFT_WIN),true,false,false,CL_help);	
			if(you.position.x < DG_MAX_X/2)
			{
				map_list.bamboo_count = -10;
				you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
				AddNote(you.turn,CurrentLevelString(),
					LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_SUCCESS) + " " + LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_WIN_LEFT)
					,CL_normal);
			}
			else
			{
				AddNote(you.turn,CurrentLevelString(),
					LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_FAIL) + " " + LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_WIN_LEFT)
					,CL_danger);
				map_list.god_num++;
				if(map_list.god_num<3)
				{
					char temp[200];
					sprintf_s(temp,200,"오답이다! 남은 기회 %d",3-map_list.god_num);
					printlog(temp,true,false,false,CL_danger);
					AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_ARENA_LEFT_LIFE, PlaceHolderHelper(to_string(3-map_list.god_num))),CL_danger);
					map_list.bamboo_count = -10;
				}
				else
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_FAIL),true,false,false,CL_danger);
					map_list.bamboo_count = 121;
				}

			}
			map_list.bamboo_rate = 2;
		}
		if(left_dead_ && right_dead_)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_DRAW),true,false,false,CL_help);	
			map_list.bamboo_count = -10;		
			map_list.bamboo_rate = 3;
			AddNote(you.turn,CurrentLevelString(),LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_DRAW),CL_small_danger);
		}

	}

	if(map_list.bamboo_count == 120)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_ARENA_TIMEOVER),true,false,false,CL_help);	
		map_list.bamboo_count = -10;		
		map_list.bamboo_rate = 3;
		AddNote(you.turn,CurrentLevelString(),LocalzationManager::locString(LOC_SYSTEM_NOTE_ARENA_TIMEOVER),CL_small_danger);

		auto it = env[num].mon_vector.begin();
		for( ;it != env[num].mon_vector.end();it++)
		{
			if(it->isLive())
			{
				(*it).dead(PRT_NEUTRAL, true);
			}
		}

	}

	
	if(map_list.bamboo_count == 130)
	{
		printlog(LocalzationManager::formatString(LOC_SYSTEM_ARENA_TIMEOVER,
			PlaceHolderHelper(to_string(you.level)),
			PlaceHolderHelper("?:")),true,false,false,CL_help);
		AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_ARENA_FINAL_SCORE, PlaceHolderHelper(to_string(you.level))),CL_danger);
	}


	map_list.bamboo_count++;


}




void map_algorithms_arena(int num)
{
	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			if((x-DG_MAX_X/2)*(x-DG_MAX_X/2) + (y-DG_MAX_Y/2)*(y-DG_MAX_Y/2) < 8*8)
			{
				if(x-DG_MAX_X/2 == 0)
					env[num].dgtile[x][y].tile = DG_GRASS;
				else
					env[num].dgtile[x][y].tile = DG_FLOOR;
			}
			else 
				env[num].dgtile[x][y].tile = DG_WALL;
			
			if( x-DG_MAX_X/2 >= -5 && x-DG_MAX_X/2 <= 5)
			{
				
				if(y-DG_MAX_Y/2 >= -3 && y-DG_MAX_Y/2 <= 3)
				{
					if( x-DG_MAX_X/2 == -5 || x-DG_MAX_X/2 == 5 || y-DG_MAX_Y/2 == -3 || y-DG_MAX_Y/2 == 3)
					{
						env[num].dgtile[x][y].tile = DG_GLASS;

					}
					if(x-DG_MAX_X/2 == 0)
					{
						env[num].dgtile[x][y].tile = DG_GLASS;

					}
				}
			}
		}
	}



	
	env[num].stair_up[0].x = DG_MAX_X/2;
	env[num].stair_up[0].y = DG_MAX_Y/2+5;
	map_list.god_num=0;
	env[num].MakeEvent(EVL_ARENA,coord_def(0,0),EVT_ALWAYS);
}