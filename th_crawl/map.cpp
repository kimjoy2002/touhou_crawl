﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: map.cpp
//
// 내용: 지형제작 알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "map.h"
#include "throw.h"
#include "enum.h"
#include "mon_infor.h"
#include "event.h"
#include "armour.h"
#include "evoke.h"
#include "zigurrat.h"





map_dummy::map_dummy(int floor_, coord_def pos_,bool wall_,int size_x_,int size_y_,int pattern_, dungeon_tile_type floor_tex_,dungeon_tile_type wall_tex_):
floor(floor_), pos(pos_),wall(wall_),size_x(size_x_),size_y(size_y_),pattern(pattern_),flag(0), m_entrance(0,0),m_exit(0,0),floor_tex(floor_tex_),wall_tex(wall_tex_),
connect_enter(false),connect_exit(false)
{
	//if(!pattern_)
	//{
	//	tiles = new dungeon_tile_type*[size_x*2+1];
	//	for(int i=0;i<size_x*2+1;i++)
	//		tiles[i] = new dungeon_tile_type[size_y*2+1];
	//
	//	for(int i = 0;i<size_x*2+1;i++)
	//	{
	//		for(int j = 0;j<size_y*2+1;j++)
	//		{
	//			tiles[i][j] = DG_FLOOR;
	//		}
	//	}
	//	if(randA(1))
	//	{
	//		m_entrance.x = rand_int(-size_x,size_x);
	//		m_entrance.y = (randA(1)?-size_y-1:size_y+1);
	//	}
	//	else
	//	{
	//		m_entrance.x = (randA(1)?-size_x-1:size_x+1);
	//		m_entrance.y = rand_int(-size_y,size_y);
	//	}
	//	if(randA(1))
	//	{
	//		m_exit.x = rand_int(-size_x,size_x);
	//		m_exit.y = (randA(1)?-size_y-1:size_y+1);
	//	}
	//	else
	//	{
	//		m_exit.x = (randA(1)?-size_x-1:size_x+1);
	//		m_exit.y = rand_int(-size_y,size_y);
	//	}
	//	m_entrance+=pos;
	//	m_exit+=pos;
	//}
	//else
	patternSet();
}
map_dummy::~map_dummy()
{
	for(int i=0;i<size_x;i++)
		delete[] tiles[i];
	delete[] tiles;
}

bool map_dummy::collution(const coord_def& point,int size_x_,int size_y_)
{
	return ( abs(point.x-pos.x) <= size_x_ + size_x + 1 && abs(point.y-pos.y) <= size_y_ + size_y + 1 );
}
bool map_dummy::plus_collution(const coord_def& point,int size_x_,int size_y_)
{
	return ((abs(point.x-pos.x) <= size_x_ + size_x + -1 && abs(point.y-pos.y) == size_y_ + size_y + 1 ) || (abs(point.x-pos.x) == size_x_ + size_x + 1 && abs(point.y-pos.y) <= size_y_ + size_y + -1 ));
}
void map_dummy::make_map(environment& env_pointer, bool wall_, bool stair_input_)
{	
	int stait_up_num = 0;
	int stait_down_num = 0;
	for(int i = -size_x;i<=size_x;i++)
	{
		for(int j = -size_y;j<=size_y;j++)
		{			
			if(i+pos.x<0 || i+pos.x>DG_MAX_X||j+pos.y<0 || j+pos.y>DG_MAX_X)
			{
				break;
			}
			else if(tiles[i+size_x][j+size_y] != DG_NONE)
			{
				env_pointer.dgtile[i+pos.x][j+pos.y].tile = tiles[i+size_x][j+size_y];
				if (stair_input_ && env_pointer.dgtile[i + pos.x][j + pos.y].tile == DG_UP_STAIR)
				{
					if (stait_up_num <= 2) {
						env_pointer.stair_up[stait_up_num].x = i + pos.x;
						env_pointer.stair_up[stait_up_num].y = j + pos.y;
						stait_up_num++;
					}
				}
				else if (stair_input_ && env_pointer.dgtile[i + pos.x][j + pos.y].tile == DG_DOWN_STAIR)
				{ 
					if (stait_down_num <= 2) {
						env_pointer.stair_down[stait_down_num].x = i + pos.x;
						env_pointer.stair_down[stait_down_num].y = j + pos.y;
						stait_down_num++;
					}
				}
				else if(env_pointer.dgtile[i+pos.x][j+pos.y].tile >= DG_SUB_STAIR_FIRST && env_pointer.dgtile[i+pos.x][j+pos.y].tile < DG_SUB_STAIR_MAX)
				{
					env_pointer.stair_vector.push_back(stair_info(coord_def(i+pos.x,j+pos.y),tiles[i+size_x][j+size_y]));
				}
				if(flag)
					env_pointer.dgtile[i+pos.x][j+pos.y].flag |= flag;
			}
		}
	}
	for(list<mapdummy_mon>::iterator it = monster_list.begin();it!=monster_list.end();it++)
	{
		monster* mon_ = env_pointer.AddMonster(it->id,it->flag,it->pos+pos,0);
		mon_->SetStrong(mon_->isUnique()?5:1);
	}
	for (auto it = pos_list.begin(); it != pos_list.end(); it++) {
		it->operator+=(pos);
	}
	for(list<mapdummy_item>::iterator it = item_list.begin();it!=item_list.end();it++)
	{
		item* item_ = env_pointer.MakeItem(it->pos+pos,it->id);
		
		if((*it).id.artifact)
		{
			if((item_->type>=ITM_WEAPON_FIRST && item_->type< ITM_WEAPON_LAST)||(item_->type>=ITM_ARMOR_FIRST && item_->type< ITM_ARMOR_LAST)||(item_->type>=ITM_JEWELRY_FIRST && item_->type< ITM_JEWELRY_LAST))
			{ //아티펙트 만들기
					MakeArtifact(item_,item_->curse?-1:1);
			}
		}
	}
	for(list<mapdummy_event>::iterator it = event_list.begin();it!=event_list.end();it++)
	{
		env_pointer.MakeEvent(it->id,it->position+pos,it->type);
	}


	
}
void map_dummy::make_door(environment& env_pointer)
{
	env_pointer.dgtile[m_entrance.x][m_entrance.y].tile = DG_CLOSE_DOOR;
	env_pointer.dgtile[m_exit.x][m_exit.y].tile = DG_CLOSE_DOOR;
}
void map_dummy::mask(environment& env_pointer, bool wall_)
{
	for(int i = -size_x;i<=size_x;i++)
	{
		for(int j = -size_y;j<=size_y;j++)
		{
			if(tiles[i+size_x][j+size_y] != DG_NONE)
			{
				if(wall_ || (i != -size_x && i != size_x && j != size_y && j != -size_y))
					env_pointer.dgtile[i+pos.x][j+pos.y].tile = wall_tex;
			}
		}
	}
	env_pointer.dgtile[m_entrance.x][m_entrance.y].tile = DG_FLOOR2;
	env_pointer.dgtile[m_exit.x][m_exit.y].tile = DG_FLOOR2;
}
void map_dummy::eventmapmake(environment& env_pointer, int count, bool wall_)
{
	for(int i = -size_x;i<=size_x;i++)
	{
		for(int j = -size_y;j<=size_y;j++)
		{			
			if(i+pos.x<0 || i+pos.x>DG_MAX_X||j+pos.y<0 || j+pos.y>DG_MAX_X)
			{
				break;
			}
			else if(tiles[i+size_x][j+size_y] != DG_NONE)
			{
				env_pointer.MakeEvent(EVL_DREAM_FLOOR, pos+coord_def(i,j), EVT_COUNT,count);
				//env_pointer.dgtile[i+pos.x][j+pos.y].tile = tiles[i+size_x][j+size_y];
				if(flag)
					env_pointer.dgtile[i+pos.x][j+pos.y].flag |= flag;
			}
		}
	}
}

void map_dummy::SetEnter(coord_def c)
{
	if(wall)
		tiles[m_entrance.x-pos.x+size_x][m_entrance.y-pos.y+size_y] = wall_tex;
	m_entrance = c;
	tiles[m_entrance.x-pos.x+size_x][m_entrance.y-pos.y+size_y] = floor_tex;
}
void map_dummy::SetExit(coord_def c)
{
	if(wall)
		tiles[m_exit.x-pos.x+size_x][m_exit.y-pos.y+size_y] = wall_tex;
	m_exit = c;
	tiles[m_exit.x-pos.x+size_x][m_exit.y-pos.y+size_y] = floor_tex;
}
coord_def map_dummy::getNextPos()
{
	if (pos_list.empty())
		return coord_def(0,0);
	coord_def c = pos_list.front();
	pos_list.pop_front();
	return c;
}

void make_lake(int num, int repeat, boolean lava);

void map_algorithms01(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);
void map_algorithms02(int num, int piece, int weight, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);
void map_algorithms03(int repeat_,int size_mn_,int size_mx_, int m_size_, int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);
void map_algorithms_library(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);
void map_algorithms_under(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);
void map_algorithms_bamboo(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);
void map_algorithms_temple(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);
void map_algorithms_tuto01(int num);
void map_algorithms_tuto02(int num);
void map_algorithms_tuto03(int num);
void map_algorithms_arena(int num);
void map_algorithms_sprint(int num);
void map_algorithms_okina(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);

void map_algorithms(int num)
{
	if(isNormalGame())
	{
		if(num == 0)
		{
			//map_algorithms03(MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL);
			map_algorithms02(num,0,0,DG_FLOOR,DG_WALL);

		}
		else if(num<MAX_DUNGEUN_LEVEL)
		{
			if(randA(1))
				map_algorithms01(num,DG_FLOOR,DG_WALL);
			else
				map_algorithms02(num,randA(10),0,DG_FLOOR,DG_WALL);
		}
		else if(num == TEMPLE_LEVEL)
		{
			map_algorithms_temple(num,DG_FLOOR,DG_WALL);
		}
		else if(num >= YOUKAI_MOUNTAIN_LEVEL && num <= YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL)
		{
			map_algorithms02(num,10,0,DG_GRASS,DG_STONE_WALL);
		}
		else if(num >= MISTY_LAKE_LEVEL && num <= MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL)
		{
			map_algorithms03(120,3,5,9, num,DG_GRASS,DG_WALL);
			make_lake(num, 100, false);
		}
		else if(num == SCARLET_LIBRARY_LEVEL)
		{
			map_algorithms_library(num,DG_FLOOR,DG_RED_WALL);
		}
		else if(num == SCARLET_UNDER_LEVEL)
		{
			map_algorithms_under(num,DG_FLOOR,DG_RED_WALL);
		}
		else if(num == BAMBOO_LEVEL)
		{
			map_algorithms_bamboo(num,DG_GRASS,DG_BAMBOO_WALL);
		}
		else if(num == EIENTEI_LEVEL)
		{
			map_algorithms02(num, 5,15,DG_GRASS,DG_WALL);
		}
		else if(num >= SUBTERRANEAN_LEVEL && num <= SUBTERRANEAN_LEVEL_LAST_LEVEL)
		{
			map_algorithms01(num, DG_HELL_FLOOR, DG_HELL_WALL);
			if (num == SUBTERRANEAN_LEVEL_LAST_LEVEL) {
				make_lake(num, 50, true);
			}
		}
		else if(num >= YUKKURI_LEVEL && num < YUKKURI_LAST_LEVEL)
		{
			map_algorithms03(70,3,4,12, num,DG_GRASS,DG_WALL);
		}
		else if(num == YUKKURI_LAST_LEVEL)
		{
			map_algorithms03(80,5,7,12, num,DG_GRASS,DG_WALL);
		}
		else if(num >= DEPTH_LEVEL && num <= DEPTH_LAST_LEVEL)
		{
			if(randA(1))
				map_algorithms01(num,DG_FLOOR,DG_WALL);
			else
				map_algorithms02(num,randA(10),0,DG_FLOOR,DG_WALL);
		}
		else if(num == MOON_LEVEL)
		{
			//map_algorithms01(num,DG_FLOOR,DG_WALL);
			map_algorithms02(num,10,0,DG_FLOOR,DG_SEA);
		}
		else if(num >= HAKUREI_LEVEL && num <= HAKUREI_LAST_LEVEL)
		{
			map_algorithms01(num,DG_FLOOR,DG_WALL);
		}
		else if(num == PANDEMONIUM_LEVEL)
		{
			env[num].AllySafeClear(map_list.dungeon_enter[PANDEMONIUM].floor, map_list.dungeon_enter[PANDEMONIUM].pos);
			env[num].ClearFloor();
			map_algorithms02(num,10,0,(dungeon_tile_type)(DG_PANDE_FLOOR1 + randA(6)), (dungeon_tile_type)(DG_PANDE_WALL1 + randA(6)));
		}
		else if(num>PANDEMONIUM_LEVEL && num<=PANDEMONIUM_LAST_LEVEL)
		{
			env[num].ClearFloor();
			dungeon_tile_type floor_ = DG_FLOOR;
			dungeon_tile_type wall_ = DG_FLOOR;

			if (num == PANDEMONIUM_LEVEL + 1)
			{
				floor_ = DG_PANDE_FLOOR7;
				wall_ = DG_PANDE_WALL7;
			}
			else if (num == PANDEMONIUM_LEVEL + 2)
			{
				floor_ = DG_PANDE_FLOOR5;
				wall_ = DG_PANDE_WALL5;
			}
			else if (num == PANDEMONIUM_LEVEL + 3)
			{
				floor_ = DG_PANDE_FLOOR1;
				wall_ = DG_PANDE_WALL1;
			}
			map_algorithms02(num,5,0, floor_, wall_);
		}
		else if(num >= SCARLET_LEVEL && num <= SCARLET_LEVEL_LAST_LEVEL)
		{
			map_algorithms01(num,DG_FLOOR,DG_RED_WALL);
		}
		else if(num == DREAM_LEVEL)
		{			
			env[num].ClearFloor();
			map_algorithms02(num,3,-40,DG_DREAM_FLOOR,DG_WALL2);
		}
		else if (num == OKINA_LEVEL)
		{
			map_algorithms_okina(num, DG_FLOOR, DG_METAL_WALL);
		}
		else if (num == ZIGURRAT_LEVEL) {
			env[num].ClearFloor();
			map_algorithms_zigurrat(num);
		}
		else
		{
			map_algorithms01(num,DG_FLOOR,DG_WALL);
		}
	}
	else if(map_list.tutorial == GM_TUTORIAL)
	{
		if(num == 0 )
			map_algorithms_tuto01(num);
		else
			map_algorithms_tuto02(num);

	}
	else if(map_list.tutorial == GM_TUTORIAL2)
	{
		map_algorithms_tuto03(num);
	}
	else if(isArena())//아레나1
	{
		map_algorithms_arena(num);
	}
	else if (isSprint())
	{
		map_algorithms_sprint(num);
	}
}

void calcul_spe_enter(int floor, vector<int> &vector_)
{
	for(int i=0;i<MAX_SUB_DUNGEON;i++)
	{
		if(map_list.dungeon_enter[i].floor == floor)
		{
			vector_.push_back(100+i);
		}
	}
	for(int i=0;i<GT_LAST;i++)
	{
		if(map_list.temple[i].floor == floor)
		{
			vector_.push_back(100+MAX_SUB_DUNGEON+i);
		}
	}
	if(floor != 0 && floor != YUKKURI_LAST_LEVEL && floor != DREAM_LEVEL)
	{ //테스트
		int i = rand_int(1, 2);
		for(int j = 0; j < i; j++)
			vector_.push_back(10+floor);	
	}
	if(floor == YOUKAI_MOUNTAIN_LAST_LEVEL)
	{
		vector_.push_back(VP_YOUKAI_MOUNTAIN_LAST);			
	}
	if(floor == SCARLET_LEVEL_LAST_LEVEL)
	{
		vector_.push_back(VP_SCARLET_LAST);		
	}
	if(floor == EIENTEI_LEVEL_LAST_LEVEL)
	{
		vector_.push_back(VP_EIENTEI_LAST);		
	}
	if(floor == PANDEMONIUM_LEVEL+1)
	{
		vector_.push_back(VP_PANDEMONIUM_1_LAST);		
	}
	if(floor == PANDEMONIUM_LEVEL+2)
	{
		vector_.push_back(VP_PANDEMONIUM_2_LAST);		
	}
	if(floor == PANDEMONIUM_LEVEL+3)
	{
		vector_.push_back(VP_PANDEMONIUM_3_LAST);		
	}
	if(floor == YUKKURI_LAST_LEVEL)
	{
		vector_.push_back(VP_YUKKURI_LAST);		
	}
	if(floor == MOON_LAST_LEVEL)
	{
		vector_.push_back(VP_MOON_LAST);		
	}
	if(floor == SUBTERRANEAN_LEVEL_LAST_LEVEL)
	{
		vector_.push_back(VP_SUBTERRANEAN_LAST);		
	}
	if(floor == HAKUREI_LAST_LEVEL)
	{
		vector_.push_back(VP_HAKUREI_LAST);

	}
	if(0)
	{
		for(int i=0;i<10;i++)
		{
			//vector_.push_back(100+MAX_SUB_DUNGEON+(1?GT_YUKARI:GT_YUYUKO));
			vector_.push_back(10+floor);
		}
	}

	return;
}

void make_lake(int num, int repeat, boolean lava)
{
	bool no_lake_ = false;
	for(int j=0;j<repeat;j++) //무한반복 제거용
	{
		bool success= true;
		int r_size_x = rand_int(2,5);
		int r_size_y = r_size_x==2?rand_int(3,5):(randA(3)?r_size_x:2);
		int m_size=10;
		coord_def temp_coord(randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size,randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size);		
		

		for(int x_ = temp_coord.x-r_size_x+1; x_ < temp_coord.x+r_size_x; x_++)
		{
			for(int y_ = temp_coord.y-r_size_y+1; y_ < temp_coord.y+r_size_y; y_++)
			{
				if(!(env[num].dgtile[x_][y_].tile >= DG_FLOOR && env[num].dgtile[x_][y_].tile <= DG_FLOOR_END || env[num].dgtile[x_][y_].tile == DG_SEA || env[num].dgtile[x_][y_].tile == DG_LAVA))
				{
					no_lake_ = true;
					x_ = temp_coord.x+r_size_x-1;
					y_ = temp_coord.y+r_size_y-1;
				}
			}
		}
		if(!no_lake_)
		{
			int stuck_ = 0;
			for(int x_ = temp_coord.x-r_size_x+1; x_ < temp_coord.x+r_size_x; x_++){
				if(!(env[num].dgtile[x_][temp_coord.y-r_size_y].tile >= DG_FLOOR && env[num].dgtile[x_][temp_coord.y-r_size_y].tile <= DG_FLOOR_END)){
					stuck_++;
					break;
				}
			}
			for(int x_ = temp_coord.x-r_size_x+1; x_ < temp_coord.x+r_size_x; x_++){
				if(!(env[num].dgtile[x_][temp_coord.y+r_size_y].tile >= DG_FLOOR && env[num].dgtile[x_][temp_coord.y+r_size_y].tile <= DG_FLOOR_END)){
					stuck_++;
					break;
				}
			}
			for(int y_ = temp_coord.y-r_size_y+1; y_ < temp_coord.y+r_size_y; y_++){
				if(!(env[num].dgtile[temp_coord.x-r_size_x][y_].tile >= DG_FLOOR && env[num].dgtile[temp_coord.x-r_size_x][y_].tile <= DG_FLOOR_END)){
					stuck_++;
					break;
				}
			}
			for(int y_ = temp_coord.x-r_size_x+1; y_ < temp_coord.y+r_size_y; y_++){
				if(!(env[num].dgtile[temp_coord.x+r_size_x][y_].tile >= DG_FLOOR && env[num].dgtile[temp_coord.x+r_size_x][y_].tile <= DG_FLOOR_END)){
					stuck_++;
					break;
				}
			}
			if(stuck_ >= 2)
				no_lake_ = true;

		}

		if(no_lake_)
		{
			no_lake_ = false;
			continue;
		}
		else
		{
			
			for(int x_ = temp_coord.x-r_size_x+1; x_ < temp_coord.x+r_size_x; x_++)
			{
				for(int y_ = temp_coord.y-r_size_y+1; y_ < temp_coord.y+r_size_y; y_++)
				{
					if(x_ == temp_coord.x-r_size_x+1 || x_ == temp_coord.x+r_size_x-1)
						if(y_ == temp_coord.y-r_size_y+1 || y_ == temp_coord.y+r_size_y-1)
							continue;
					env[num].dgtile[x_][y_].tile = lava? DG_LAVA : DG_SEA;
				}
			}
		}
	}

	if (!lava)
	{

		for (int i = rand_int(30, 40); i > 0; i--)
		{
			int x_ = randA(DG_MAX_X - 1), y_ = randA(DG_MAX_Y - 1), limit_ = 10000;
			while (!env[num].isMove(x_, y_, false, false, false) ||
				(env[num].dgtile[x_][y_].flag & FLAG_NO_MONSTER) ||
				env[num].isMonsterPos(x_, y_) || env[num].isStair(x_, y_))
			{
				if (limit_-- < 0)
					break;
				x_ = randA(DG_MAX_X - 1), y_ = randA(DG_MAX_Y - 1);
			}
			if (limit_ <= 0)
				continue;
			if (env[num].AddMonster(MON_BUSH, 0, coord_def(x_, y_)))
			{
				continue;
			}
		}
	}
}

void hell_map_make_last(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex 	,
	vector<map_dummy*> &vec_map,
	vector<map_dummy*> &vec_special_map, int door_percent_)
{

	
	for(int i = 0;i<DG_MAX_X;i++)
	{
		for(int j = 0;j<DG_MAX_Y;j++)
		{
			int offset_ = 4;
			if(i<offset_ || i>=DG_MAX_X-offset_ || j < offset_ || j>=DG_MAX_Y-offset_)
				env[num].dgtile[i][j].tile = wall_tex; //다시 전부 벽으로
			else
				env[num].dgtile[i][j].tile = floor_tex; //다시 전부 벽으로
		}
	}
	
	for(auto it = vec_special_map.begin(); it != vec_special_map.end() ; it++)
		vec_map.push_back(*it);

	for(auto it=vec_map.begin();it!=vec_map.end();it++) 
	{//방을 만든다.
		(*it)->make_map(env[num],true);
		if(!(*it)->pattern && randA(10)>=door_percent_)
			(*it)->make_door(env[num]);
	}


	for (auto it=vec_map.begin();it!=vec_map.end();it++)
		delete *it;

	
	for(int i=0;i<6;i++)
	{
		while(1)
		{
			int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
			if(env[num].dgtile[x][y].isFloor()  && !(env[num].dgtile[x][y].flag & FLAG_NO_STAIR) )
			{
				if(i>2)
				{
					env[num].stair_up[i-3].x = x;
					env[num].stair_up[i-3].y = y;
					env[num].dgtile[x][y].tile = DG_RETURN_STAIR;
				}
				else
				{
					env[num].stair_down[i].x = x;
					env[num].stair_down[i].y = y;
					if(!environment::isLastFloor(num))
						env[num].dgtile[x][y].tile = DG_DOWN_STAIR;	
					
				}
				break;
			}
		}
	}


}
void common_map_make_last(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex 	,
	vector<map_dummy*> &vec_map,
	vector<map_dummy*> &vec_special_map , 
	bool check_room_mask_, bool first_path_, bool make_path_, bool make_wall_, int door_percent_)
{
	vector<map_dummy*>::iterator it;

	
	stack<coord_def> path_stack;

	
	{
		if(check_room_mask_ || !make_path_)
		{
			for(it=vec_map.begin();it!=vec_map.end();it++)  //방들을 마스크주기
				(*it)->mask(env[num]);
		}
	
		vector<map_dummy*>::iterator it;
		for(it=vec_special_map.begin();it!=vec_special_map.end();it++)  //방들을 마스크주기
			(*it)->mask(env[num]);


		map_dummy* temp = vec_map.back();

		for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
		{
			if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
			{
				path_stack.push((*it)->GetEntrance());
				(*it)->SetConnectExit(true);
				temp->SetConnectEnter(true);
			}
			temp = (*it);
		}
		for(it=vec_map.begin();it!=vec_map.end();it++) 
		{
			if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
			{
				if(!check_room_mask_)
					path_stack.push((*it)->GetEntrance());
				(*it)->SetConnectExit(true);
				temp->SetConnectEnter(true);
			}
			temp = (*it);
			if(!make_path_)
				break;
		}
		
		for(auto it2 = vec_special_map.begin(); it2 != vec_special_map.end() ; it2++)
			vec_map.push_back(*it2);

		if(!check_room_mask_)
		{
			vector<map_dummy*>::iterator it2 = vec_map.begin();
			for(it=vec_map.begin();it!=vec_map.end();it++)  //연결이 안된 방들을 다시 연결시도
			{
				for(;!(*it)->GetConnect() && it2 != vec_map.end();it2++)
				{
					if(it == it2)
						continue;
					if(PathSearch((*it)->GetEntrance(),(*it2)->GetExit(),path_stack,ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
					{
						(*it)->SetConnectEnter(true);
						temp->SetConnectExit(true);
					}				
				}
			}
		}

	}

		




	//bool first_path_ = true; //true일때 도로부터 칠함
	//bool make_path_ = true; //도로를 칠함(first_path_ 무효)
	//bool make_wall_ = true; //방마다 벽을 만든다.
	//int door_percent_ = randA(10); //방마다 문이 붙을 확률 (11이상으로 안생김)







	
	/*if(make_path_)*/
	first_path_ = true;

	for(int i = 0;i<DG_MAX_X;i++)
		for(int j = 0;j<DG_MAX_Y;j++)
			env[num].dgtile[i][j].tile = wall_tex; //다시 전부 벽으로


	
	bool make_room_ = true;
	do
	{
		if(!make_room_)
			first_path_ = true;


		if(make_path_ && first_path_)
		{
			while(!path_stack.empty())
			{
				coord_def path_temp = path_stack.top();
				env[num].dgtile[path_temp.x][path_temp.y].tile = floor_tex; //저장한 도로를 칠하기
				path_stack.pop();
			}
		}

		if(make_room_)
		{
			int percent_ = door_percent_;
			for(it=vec_map.begin();it!=vec_map.end();it++) 
			{//방을 만든다.
				(*it)->make_map(env[num],make_wall_);
				if(!(*it)->pattern && randA(10)>=door_percent_)
					(*it)->make_door(env[num]);
			}
			make_room_ = false;
		}

	}while(!first_path_);
	//
	//for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
	//{//방을 만든다.
	//	(*it)->make_map(env[num], false);
	//}

	//
	//for (it=vec_special_map.begin();it!=vec_special_map.end();it++)
	//	delete *it;


	for (it=vec_map.begin();it!=vec_map.end();it++)
		delete *it;

	
	for(int i=0;i<6;i++)
	{
		while(1)
		{
			int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
			if(env[num].dgtile[x][y].isFloor()  && !(env[num].dgtile[x][y].flag & FLAG_NO_STAIR) )
			{
				if(i>2)
				{
					if(i==3 || !environment::isFirstFloor(num) || env[num].isPandemonium())
					{
						env[num].stair_up[i-3].x = x;
						env[num].stair_up[i-3].y = y;
						if ( !env[num].isPandemonium() || (randA(4)==0 || (i == 3 && num != PANDEMONIUM_LEVEL)))
						{
							if( num != 0 && environment::isFirstFloor(num))
								env[num].dgtile[x][y].tile = DG_RETURN_STAIR;
							else
								env[num].dgtile[x][y].tile = DG_UP_STAIR;
						}
					}
				}
				else
				{
					env[num].stair_down[i].x = x;
					env[num].stair_down[i].y = y;
					if(!environment::isLastFloor(num))
						env[num].dgtile[x][y].tile = DG_DOWN_STAIR;	
					else if(env[num].isPandemonium())
					{
						env[num].dgtile[x][y].tile = DG_PANDEMONIUM_STAIR;	
						env[num].stair_vector.push_back(stair_info(coord_def(x,y),PANDEMONIUM_LEVEL));
					}
					
				}
				break;
			}
		}
	}

}


void dream_map_make_last(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex 	,
	vector<map_dummy*> &vec_map,
	vector<map_dummy*> &vec_special_map , 
	bool check_room_mask_, bool first_path_, bool make_path_, bool make_wall_, int door_percent_)
{
	const int divide_ = 5;
	const int dream_count_ = 200;
	vector<map_dummy*>::iterator it=vec_map.begin();

	
	stack<coord_def> path_stack[divide_];

	
	map_dummy*  temp=vec_map.front();


	for(int i = 0 ; i < divide_; i++)
	{
		vector<map_dummy*>::iterator it2=it;
		
		for(int k = 0;k<DG_MAX_X;k++)
		{
			for(int h = 0;h<DG_MAX_Y;h++)
			{
				env[num].dgtile[k][h].tile = floor_tex;
			}
		}



		
		{
			int j =0;
			for(;it!=vec_map.end();it++)  //방들을 마스크주기
			{
				if(check_room_mask_ || !make_path_)
					(*it)->mask(env[num],false);
				j++;
				if(i != divide_ -1 && j>vec_map.size()/divide_)
				{
					if(i == 0)	
						temp = (*it);
					it++;
					break;
				}
			}
		}

		
		int j =0;
		for(;it2!=vec_map.end();it2++) 
		{
			if(PathSearch(temp->GetEntrance(),(*it2)->GetExit(),path_stack[i],ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
			{
				if(!check_room_mask_)
					path_stack[i].push((*it2)->GetEntrance());
				(*it2)->SetConnectExit(true);
				temp->SetConnectEnter(true);
			}
			else
			{

				temp = (*it2);
			}
			temp = (*it2);
			if(!make_path_)
				break;
			j++;
			if(i != divide_ -1 &&   j>vec_map.size()/divide_)
			{
				temp = (*it2);
				it2++;
				break;
			}
		}		
	}

	
	first_path_ = true;
	
	for(int k = 0;k<DG_MAX_X;k++)
	{
		for(int h = 0;h<DG_MAX_Y;h++)
		{
			env[num].dgtile[k][h].tile = wall_tex; //다시 전부 벽으로
		}
	}

	
	
	bool make_room_ = true;
	do
	{
		if(!make_room_)
			first_path_ = true;


		if(make_path_ && first_path_)
		{
			for(int i = 0 ; i < divide_ ; i++)
			{
				while(!path_stack[i].empty())
				{
					coord_def path_temp = path_stack[i].top();
					if(i==0)
						env[num].dgtile[path_temp.x][path_temp.y].tile = floor_tex; //저장한 도로를 칠하기
					else 
						env[num].MakeEvent(EVL_DREAM_FLOOR, path_temp, EVT_COUNT,dream_count_*i);
					path_stack[i].pop();
				}
			}
		}
		
		for(int k=0;k<divide_;k++)
			env[num].MakeEvent(EVL_AGRO, coord_def(0,0), EVT_COUNT,dream_count_*(k+1));


		if(make_room_)
		{
			int percent_ = door_percent_;
			it=vec_map.begin();
			for(int i = 0 ; i < divide_ ; i++)
			{
				int j =0;
				for(;it!=vec_map.end();it++) 
				{//방을 만든다.
					if(i==0)
						(*it)->make_map(env[num],make_wall_);
					else
					{
						(*it)->eventmapmake(env[num],i*dream_count_,make_wall_);
						
						for(int k = rand_int(0,3); k >0 ; k--)
						{
							env[num].MakeEvent(EVL_DREAM_MONSTER, (*it)->pos, EVT_COUNT,dream_count_*i);
						}

					}
					j++;
					if(i != divide_ -1 &&   j>vec_map.size()/divide_)
					{
						it++;
						break;
					}
				}
			}
			make_room_ = false;
		}

	}while(!first_path_);
	//
	//for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
	//{//방을 만든다.
	//	(*it)->make_map(env[num], false);
	//}

	//
	for (it=vec_special_map.begin();it!=vec_special_map.end();it++)
		delete *it;
	for(int k=0;k<divide_;k++)
		env[num].MakeEvent(EVL_DREAM_MESSAGE, coord_def(0,0), EVT_COUNT,dream_count_*(k+1));
	
	for (it=vec_map.begin();it!=vec_map.end();it++)
		delete *it;

	
	
	for(int i=0;i<6;i++)
	{
		while(1)
		{
			int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
			if(env[num].dgtile[x][y].isFloor()  && !(env[num].dgtile[x][y].flag & FLAG_NO_STAIR) )
			{
				if(i>2)
				{
					env[num].stair_up[i-3].x = x;
					env[num].stair_up[i-3].y = y;
					/*if( num != 0 && environment::isFirstFloor(num))
						env[num].dgtile[x][y].tile = DG_RETURN_STAIR;
					else
						env[num].dgtile[x][y].tile = DG_UP_STAIR;*/
				}
				else
				{
					env[num].stair_down[i].x = x;
					env[num].stair_down[i].y = y;
					//if(!environment::isLastFloor(num))
					//	env[num].dgtile[x][y].tile = DG_DOWN_STAIR;	
				}
				break;
			}
		}
	}
}



void print_special_map(int floor_, vector<map_dummy*> &map_vector)
{
	enterlog();
	int count_ = 0;
	for (auto it = map_vector.begin(); it != map_vector.end(); it++)
	{
		if (count_ == 0)
		{
			if (wiz_list.wizard_mode == 1)
			{
				printlog("특수지형:", false, false, false, CL_danger);
			}
		}
		if ((*it)->name.size() > 0)
		{
			env[floor_].AddSpecialMapInfo((*it)->name);
			if (wiz_list.wizard_mode == 1)
			{
				printlog((*it)->name.c_str(), false, false, false, CL_danger);
				printlog(", ", false, false, false, CL_danger);
			}
		}
		count_++;
		if(count_ % 4 == 0)
			enterlog();
	}
	enterlog();
}


void setBaseFloorWall(int floor_, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex)
{
	env[floor_].base_floor = floor_tex;
	env[floor_].base_wall = wall_tex;
}


void map_algorithms01(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex)
{
	vector<map_dummy*> vec_map;
	vector<map_dummy*> vec_special_map;
	vector<int> special_enter;
	calcul_spe_enter(num,special_enter);
	

	vec_map.reserve(32);


	

	int rand_dummy = rand_int(20,30);
	int check_ = special_enter.size();
	for(int i=0;i<rand_dummy;i++) //rand_dummy만큼의 맵더미를 생산
	{
		int repeat = 10;
		int pattern_ = 0;
		bool special_ = false;
		if(!special_enter.empty())
		{
			special_ = true;
			repeat = 9999;//특수패턴은 (거의)무한반복시킴
			pattern_ = special_enter.back();
			special_enter.pop_back();
		}
		for(int j=0;j<repeat;j++) //무한반복 제거용
		{
			bool success= true;	
			int r_size_x = rand_int(3,8);
			int r_size_y = rand_int(3,8);
			int m_size=5;
			coord_def temp_coord(randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size,randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size);		
			
			map_dummy* temp = new map_dummy(num, temp_coord, true,r_size_x,r_size_y, pattern_,floor_tex,wall_tex); //랜덤한 맵더미

			vector<map_dummy*>::iterator it;
			for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
			{
				if((*it)->collution(temp_coord,temp->size_x,temp->size_y) || (*it)->plus_collution(temp_coord,temp->size_x,temp->size_y)) //맵더미충돌시엔 만들지 않음
				{
					success = false;
					break;
				}
			}	
			for (it=vec_map.begin();it!=vec_map.end();it++) 
			{
				if((*it)->collution(temp_coord,temp->size_x,temp->size_y) || (*it)->plus_collution(temp_coord,temp->size_x,temp->size_y)) //맵더미충돌시엔 만들지 않음
				{
					success = false;
					break;
				}
			}	
			if(success) //겹치지 않을때 맵더미푸쉬
			{
				if (special_) {
					vec_special_map.push_back(temp);
					check_--;
				}
				else
					vec_map.push_back(temp);
				break;
			}
			else
			{
				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
				continue;
			}
		}
	}
	if (check_ != 0) {
		//무조건 특수지형은 만들어져야한다. 안 만들어지면 아예 처음부터 시작
		for (auto it = vec_special_map.begin(); it != vec_special_map.end(); it++)
			delete *it;
		for (auto it = vec_map.begin(); it != vec_map.end(); it++)
			delete *it;
		return map_algorithms01(num, floor_tex, wall_tex);
	}
	print_special_map(num, vec_special_map);
	setBaseFloorWall(num, floor_tex, wall_tex);

	if(num >= SUBTERRANEAN_LEVEL && num <= SUBTERRANEAN_LEVEL_LAST_LEVEL)
	{
		hell_map_make_last(num, 	
		floor_tex,wall_tex,
		vec_map,
		vec_special_map, 
		randA(10));
		
		env[num].MakeEvent(EVL_REGEN2, coord_def(0,0), EVT_ALWAYS,230);
	}
	else
		common_map_make_last(num, 	
		floor_tex,wall_tex,
		vec_map,
		vec_special_map, 
		true,true, true, true, you.god == GT_OKINA ? 0 : randA(10));
}
void map_algorithms02(int num, int piece, int weight, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex)
{
	vector<map_dummy*> vec_map;
	vector<map_dummy*> vec_special_map;
	vector<int> special_enter;
	calcul_spe_enter(num,special_enter);

	int prev_x=0;
	int prev_y=0;
	int step = 0;

	int check_ = special_enter.size();
	int rand_dummy = special_enter.size();
	for(int i=0;i<rand_dummy;i++) //rand_dummy만큼의 맵더미를 생산
	{	
		int repeat = 10;
		int pattern_ = 1;
		bool special_ = false;
		if(!special_enter.empty())
		{
			special_ = true;
			repeat = 9999;//특수패턴은 (거의)무한반복시킴
			pattern_ = special_enter.back();
			special_enter.pop_back();
		}
		for(int j=0;j<repeat;j++) //무한반복 제거용
		{
			bool success= true;
			int r_size_x = rand_int(2+piece/3,4+piece/3);
			int r_size_y = rand_int(2+piece/3,4+piece/3);
			int m_size=5;
			coord_def temp_coord(randA(DG_MAX_X-(6+2)*2-1-m_size*2)+6+2+m_size,randA(DG_MAX_Y-(6+2)*2-1-m_size*2)+6+2+m_size);	
			if(pattern_ == VP_EIENTEI_LAST)
			{
				temp_coord.x = DG_MAX_X/2;
				temp_coord.y = DG_MAX_Y/2;
			}
			map_dummy* temp = new map_dummy(num,temp_coord, false,r_size_x,r_size_y,pattern_,floor_tex,wall_tex); //랜덤한 맵더미
			
			


			vector<map_dummy*>::iterator it;
			for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
			{
				if((*it)->collution(temp_coord,temp->size_x,temp->size_y) || (*it)->plus_collution(temp_coord,temp->size_x,temp->size_y)) //맵더미충돌시엔 만들지 않음
				{
					success = false;
					break;
				}
			}		
			if(success) //겹치지 않을때 맵더미푸쉬
			{
				vec_special_map.push_back(temp);
				check_--;
				break;
			}
			else
			{
				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
				continue;
			}
		}
	}
	if (check_ != 0) {
		//무조건 특수지형은 만들어져야한다. 안 만들어지면 아예 처음부터 시작
		for (auto it = vec_special_map.begin(); it != vec_special_map.end(); it++)
			delete *it;
		for (auto it = vec_map.begin(); it != vec_map.end(); it++)
			delete *it;
		return map_algorithms02(num, piece, weight, floor_tex, wall_tex);
	}


	for(int i=0;i<25-piece- weight;i++)
	{
		int j=0;
		for(;j<(i==0?9999:20);j++) //무한반복 제거용
		{
			bool success= true;
			int next_x=0,next_y=0;
			int r_size_x = rand_int(1+piece/3,4+piece/3);
			int r_size_y = rand_int(1+piece/3,4+piece/3);
			int m_size=5;
			if(step != 1)
				next_x = randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size;
			else
				next_x = prev_x+rand_int(-r_size_x+1,r_size_x-1);

			if(step != -1)
				next_y = randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size;
			else
				next_y = prev_y+rand_int(-r_size_y+1,r_size_y-1);

			coord_def temp_coord(next_x,next_y);		
			map_dummy* temp = new map_dummy(num,temp_coord, false,r_size_x,r_size_y,0,floor_tex,wall_tex); //랜덤한 맵더미

			if(step)
			{
				if(step == 1)
				{
					temp->SetEnter(coord_def(next_x,prev_y>next_y?next_y+r_size_y-1:next_y-r_size_y+1));
				}
				else
				{
					temp->SetEnter(coord_def(prev_x>next_x?next_x+r_size_x-1:next_x-r_size_x+1,next_y));
				}
			}

			

			if (!(temp->pos.x - temp->size_x >= 0 &&
				temp->pos.x + temp->size_x < DG_MAX_X &&
				temp->pos.y - temp->size_y >= 0 &&
				temp->pos.y + temp->size_y < DG_MAX_Y)
				) {
				success = false;
			}


			vector<map_dummy*>::iterator it;
			if(success && piece < 4+randA(3))
			{
				for (it=vec_map.begin();it!=vec_map.end();it++) 
				{
					if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
					{
						success = false;
						break;
					}
				}
			}
			if (success)
			{
				for (it = vec_special_map.begin(); it != vec_special_map.end(); it++)
				{
					if ((*it)->collution(temp_coord, r_size_x, r_size_y) || (*it)->plus_collution(temp_coord, r_size_x, r_size_y)) //맵더미충돌시엔 만들지 않음
					{
						success = false;
						break;
					}
				}
			}
			if(success) //겹치지 않을때 맵더미푸쉬
			{
				step = (step!=-1)?-1:1;
				prev_x = next_x+rand_int(-r_size_x+1,r_size_x-1);
				prev_y = next_y+rand_int(-r_size_y+1,r_size_y-1);
				temp->SetExit(coord_def(prev_x,prev_y));
				vec_map.push_back(temp);
				break;
			}
			else
			{
				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
				continue;
			}
		}
		if(j==0)
		{
			step = 0;	
		}
	}

	print_special_map(num, vec_special_map);
	setBaseFloorWall(num, floor_tex, wall_tex);
	
	if(num == DREAM_LEVEL)
		dream_map_make_last(num, 	
		floor_tex,wall_tex,
		vec_map,
		vec_special_map, 
		false, true, true, false, you.god == GT_OKINA ? 0 : randA(10));
	else
		common_map_make_last(num, 
		floor_tex,wall_tex,
		vec_map,
		vec_special_map, 
		false, false, true, false, 11);



}






void map_algorithms03(int repeat_,int size_mn_,int size_mx_, int m_size_,int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex)
{
	vector<map_dummy*> vec_map;
	vector<map_dummy*> vec_special_map;
	vector<int> special_enter;
	calcul_spe_enter(num,special_enter);

	int prev_x=0;
	int prev_y=0;
	int step = 0;

	

	for(int i=0;i<repeat_;i++)
	{
		int j=0;
		for(;j<50;j++) //무한반복 제거용
		{
			bool success= false;
			int next_x=0,next_y=0;
			int r_size_x = rand_int(size_mn_,size_mx_);
			int r_size_y = r_size_x;
			int m_size=m_size_;
			if(step != 1)
				next_x = randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size;
			else
				next_x = prev_x+rand_int(-r_size_x+1,r_size_x-1);

			if(step != -1)
				next_y = randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size;
			else
				next_y = prev_y+rand_int(-r_size_y+1,r_size_y-1);

			coord_def temp_coord(next_x,next_y);		
			map_dummy* temp = new map_dummy(num,temp_coord, false,r_size_x,r_size_y,1,floor_tex,wall_tex); //랜덤한 맵더미

			if(step)
			{
				if(step == 1)
				{
					temp->SetEnter(coord_def(next_x,prev_y>next_y?next_y+r_size_y-1:next_y-r_size_y+1));
				}
				else
				{
					temp->SetEnter(coord_def(prev_x>next_x?next_x+r_size_x-1:next_x-r_size_x+1,next_y));
				}
			}

			
			vector<map_dummy*>::iterator it;
			if(vec_map.empty())
				success = true;

			for (it=vec_map.begin();it!=vec_map.end();it++) 
			{
				if(distan_coord(temp->pos,(*it)->pos)<=(temp->size_x+(*it)->size_x+1)*(temp->size_x+(*it)->size_x+1))
				{
					success = true;
					break;
				}
			}
			//for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
			//{
			//	if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
			//	{
			//		success = false;
			//		break;
			//	}
			//}
			if(success) //겹치지 않을때 맵더미푸쉬
			{
				step = (step!=-1)?-1:1;
				prev_x = next_x+rand_int(-r_size_x+1,r_size_x-1);
				prev_y = next_y+rand_int(-r_size_y+1,r_size_y-1);
				temp->SetExit(coord_def(prev_x,prev_y));
				vec_map.push_back(temp);
				break;
			}
			else
			{
				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
				continue;
			}
		}
		if(j==0)
		{
			step = 0;	
		}
	}


	int rand_dummy = special_enter.size();
	int check_ = rand_dummy;
	for(int i=0;i<rand_dummy;i++) //rand_dummy만큼의 맵더미를 생산
	{	
		int repeat = 10;
		int pattern_ = 1;
		bool special_ = false;
		if(!special_enter.empty())
		{
			special_ = true;
			repeat = 9999;//특수패턴은 (거의)무한반복시킴
			pattern_ = special_enter.back();
			special_enter.pop_back();
		}
		for(int j=0;j<repeat;j++) //무한반복 제거용
		{
			bool success= false;
			int r_size_x = rand_int(3,8);
			int r_size_y = rand_int(3,8);
			int m_size=20;
			coord_def temp_coord(randA(DG_MAX_X-(6+2)*2-1-m_size*2)+6+2+m_size,randA(DG_MAX_Y-(6+2)*2-1-m_size*2)+6+2+m_size);		

			if(j==0 && pattern_ == VP_YUKKURI_LAST)
				temp_coord = coord_def(DG_MAX_X/2, DG_MAX_Y/2);


			map_dummy* temp = new map_dummy(num,temp_coord, false,r_size_x,r_size_y,pattern_,floor_tex,wall_tex); //랜덤한 맵더미
			
			vector<map_dummy*>::iterator it;
			for (it=vec_map.begin();it!=vec_map.end();it++) 
			{
				if(distan_coord(temp->pos,(*it)->pos)<=(temp->size_x+(*it)->size_x+1)*(temp->size_x+(*it)->size_x+1))
				{
					success = true;
					break;
				}
			}
			for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
			{
				if((*it)->collution(temp_coord,temp->size_x,temp->size_y) || (*it)->plus_collution(temp_coord,temp->size_x,temp->size_y)) //맵더미충돌시엔 만들지 않음
				{
					success = false;
					break;
				}
			}


			if(success) //겹치지 않을때 맵더미푸쉬
			{
				vec_special_map.push_back(temp);
				check_--;
				break;
			}
			else
			{
				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
				continue;
			}
		}
	}
	if (check_ != 0) {
		//무조건 특수지형은 만들어져야한다. 안 만들어지면 아예 처음부터 시작
		for (auto it = vec_special_map.begin(); it != vec_special_map.end(); it++)
			delete *it;
		for (auto it = vec_map.begin(); it != vec_map.end(); it++)
			delete *it;
		return map_algorithms03(repeat_, size_mn_, size_mx_, m_size_, num, floor_tex, wall_tex);
	}


	print_special_map(num, vec_special_map);
	setBaseFloorWall(num, floor_tex, wall_tex);
	
	common_map_make_last(num, 	
	floor_tex,wall_tex,
	vec_map,
	vec_special_map, 
	false, false, false, false, 11);


}

void map_algorithms_library(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex)
{
	int d_x = 10, d_y = 10;
	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			if(abs(x-DG_MAX_X/2)<DG_MAX_X/2-d_x && abs(y-DG_MAX_Y/2)<DG_MAX_Y/2-d_y)
			{
				env[num].dgtile[x][y].tile = floor_tex;
			}
			else 
				env[num].dgtile[x][y].tile = wall_tex;
		}
	}
	int a_ = rand_int(0,1)*2-1;
	int b_ = rand_int(0,1)*2-1;
	int x_ = DG_MAX_X/2-(DG_MAX_X/2-d_x-1)*a_;
	int y_ = DG_MAX_Y/2-(DG_MAX_Y/2-d_y-1)*b_;

	env[num].stair_up[0].x = x_;
	env[num].stair_up[0].y = y_;
	env[num].dgtile[x_][y_].tile = DG_RETURN_STAIR;
	//env[num].stair_up[1].x = DG_MAX_X/2;
	//env[num].stair_up[1].y = DG_MAX_Y/2+29;
	//env[num].dgtile[DG_MAX_X/2][DG_MAX_Y/2+29].tile = DG_RETURN_STAIR;
	//env[num].stair_up[2].x = DG_MAX_X/2+1;
	//env[num].stair_up[2].y = DG_MAX_Y/2+28;
	//env[num].dgtile[DG_MAX_X/2+1][DG_MAX_Y/2+28].tile = DG_RETURN_STAIR;


	for(int i = d_y+3; i < DG_MAX_Y-d_y; i+=3)
	{
		int length_ = rand_int(10,30);
		int offset_= rand_int(0,length_);

		for(int j =  d_x+3; j < DG_MAX_X-d_x-2; j++)
		{
			if(offset_%length_ >2)
			{
				if(!(abs(j-DG_MAX_X/2)<10 && abs(i-DG_MAX_Y/2)<5))
				{
					env[num].dgtile[j][i].tile = DG_BOOK_WALL;
				}
			}

			offset_++;
		}
	}	
	if(!is_exist_named(MON_PACHU)){
		monster* mon_ = env[num].AddMonster(MON_PACHU,0,coord_def(DG_MAX_X/2,DG_MAX_Y/2));
		mon_->SetStrong(5);
		set_exist_named(MON_PACHU);
	}
	

	for(int i=rand_int(6,9); i >0; i--)
	{		
		item_infor t;
		env[num].MakeItem(coord_def(DG_MAX_X/2+rand_int(-9,9),DG_MAX_Y/2+rand_int(-4,4)),makeitem(ITM_BOOK, 0, &t));
	}
	setBaseFloorWall(num, floor_tex, wall_tex);


}



void map_algorithms_under(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex)
{
	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			if((x-DG_MAX_X/2)*(x-DG_MAX_X/2) + (y-DG_MAX_Y/2)*(y-DG_MAX_Y/2) < 12*12)
			{
				env[num].dgtile[x][y].tile = floor_tex;
			}
			else 
				env[num].dgtile[x][y].tile = wall_tex;
		}
	}


	env[num].stair_up[0].x = DG_MAX_X/2-1;
	env[num].stair_up[0].y = DG_MAX_Y/2+11;
	env[num].dgtile[DG_MAX_X/2-1][DG_MAX_Y/2+11].tile = DG_RETURN_STAIR;

	env[num].MakeEvent(21,coord_def(DG_MAX_X/2-1,DG_MAX_Y/2+11),EVT_SIGHT);

	
	item_infor t;
	makeitem(ITM_GOAL, 0, &t, RUNE_SCARLET_UNDER);	
	env[num].MakeItem(coord_def(DG_MAX_X/2,DG_MAX_Y/2-6),t);

	if(!is_exist_named(MON_FLAN)){
		monster* mon_ = env[num].AddMonster(MON_FLAN,0,coord_def(DG_MAX_X/2,DG_MAX_Y/2));
		mon_->SetStrong(5);
		set_exist_named(MON_FLAN);
	}
	setBaseFloorWall(num, floor_tex, wall_tex);
}

void map_algorithms_temple(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex)
{
	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			if((x-DG_MAX_X/2)*(x-DG_MAX_X/2) + (y-DG_MAX_Y/2)*(y-DG_MAX_Y/2) < 15*15)
			{
				env[num].dgtile[x][y].tile = floor_tex;
			}
			else if(abs(x-DG_MAX_X/2)<2 && y>DG_MAX_Y/2 && y<DG_MAX_Y/2+30)
			{
				env[num].dgtile[x][y].tile = floor_tex;
			}
			else 
				env[num].dgtile[x][y].tile = wall_tex;
		}
	}


	env[num].stair_up[0].x = DG_MAX_X/2-1;
	env[num].stair_up[0].y = DG_MAX_Y/2+28;
	env[num].dgtile[DG_MAX_X/2-1][DG_MAX_Y/2+28].tile = DG_RETURN_STAIR;
	env[num].stair_up[1].x = DG_MAX_X/2;
	env[num].stair_up[1].y = DG_MAX_Y/2+29;
	env[num].dgtile[DG_MAX_X/2][DG_MAX_Y/2+29].tile = DG_RETURN_STAIR;
	env[num].stair_up[2].x = DG_MAX_X/2+1;
	env[num].stair_up[2].y = DG_MAX_Y/2+28;
	env[num].dgtile[DG_MAX_X/2+1][DG_MAX_Y/2+28].tile = DG_RETURN_STAIR;

	env[num].MakeEvent(15,coord_def(DG_MAX_X/2,DG_MAX_Y/2+29),EVT_SIGHT);



	random_extraction<dungeon_tile_type> temple_;
	
	for(int i=DG_TEMPLE_JOON_AND_SION;i<=DG_TEMPLE_LAST;i++)
	{
		if (i != DG_TEMPLE_SEIJA)// && i != DG_TEMPLE_OKINA && i != DG_TEMPLE_JUNKO)
			temple_.push((dungeon_tile_type)i);
	}
	//temple_.push(DG_STATUE);


	for(int i=1; i<21; i++)
	{
		float x = round((float)DG_MAX_X/2+sin(i*18.0f/180.0f*D3DX_PI)*10.0f);
		float y = round((float)DG_MAX_Y/2+cos(i*18.0f/180.0f*D3DX_PI)*-10.0f);
		env[num].dgtile[(int)x][(int)y].tile = temple_.pop();
	}
	setBaseFloorWall(num, floor_tex, wall_tex);
}
void map_algorithms_okina(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex)
{

	for (int x = 0; x<DG_MAX_X; x++)
	{
		for (int y = 0; y<DG_MAX_Y; y++)
		{
			if (((x - DG_MAX_X / 2) > -7 && (x - DG_MAX_X / 2) < 7) && 
				((y - DG_MAX_Y / 2) > -7 && (y - DG_MAX_Y / 2) < 7))
			{
				env[num].dgtile[x][y].tile = floor_tex;
			}
			else
				env[num].dgtile[x][y].tile = wall_tex;
		}
	}

	env[num].stair_up[0].x = DG_MAX_X / 2;
	env[num].stair_up[0].y = DG_MAX_Y / 2;
	env[num].dgtile[DG_MAX_X / 2][DG_MAX_Y / 2].tile = DG_RETURN_STAIR;

	env[num].dgtile[DG_MAX_X / 2][DG_MAX_Y / 2 - 4].tile = DG_TEMPLE_OKINA;



	env[num].AddMonster(MON_MAI2, M_FLAG_ALLY, coord_def(DG_MAX_X / 2+4, DG_MAX_Y / 2))->SetInvincibility(-1, false);
	env[num].AddMonster(MON_SATONO, M_FLAG_ALLY, coord_def(DG_MAX_X / 2 - 4, DG_MAX_Y / 2))->SetInvincibility(-1, false);
	setBaseFloorWall(num, floor_tex, wall_tex);
}









void map_algorithms_tuto01(int num)
{
	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			if(x>=5 && x <=9 && y>=5 && y<=9) //첫째방
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x>=9 && x <=12 && y==7) //길목
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x>=12 && x <=16 && y>=5 && y<=9) //둘째방
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==14 && y==10) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x==15 && y==16) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if((x>=10 && x <=18 && y>=11 && y<=16) && (x+y == 25 || x+y == 28 || x+y == 31)) //지그재그
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if((x==11 && y==16) || (x==18 && y==12)) //지그재그
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x>=15 && x <=20  && y>=17 && y<=19) //셋째방(무기와 갑옷)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==21 && y==18) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=22 && x <=23 && y==18) //길목
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x>=24 && x <=26  && y>=17 && y<=19) //넷째방(몬스터)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==27 && y==18) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=28 && x <=30  && y>=17 && y<=19) //다섯째방(계단)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x>=10 && x <=13  && y>=21 && y<=23) //여섯째방(부적)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==14 && y==22) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=15 && x<=20  && y>=21 && y<=23) //일곱번째방(몬스터)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==21 && y==22) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=22 && x <=26  && y>=21 && y<=23) //여덟번째방(반지, 두루마리)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==27 && y==22) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=28 && x <=32  && y>=21 && y<=23) //아홉번째방(물약)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==33 && y==22) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=34 && x <=38  && y>=21 && y<=23) //열번째방(책과 마법)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==37 && y==24) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=36 && x <=38  && y>=25 && y<=30) //마법테스트(몹)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==37 && y==31) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=36 && x <=38  && y>=32 && y<=34) //신전
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==35 && y==33) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=33 && x <=34  && y==33) //
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x>=30 && x <=32  && y>=32 && y<=34) //캇파
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==29 && y==33) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=26 && x <=28  && y>=32 && y<=34)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==27 && y==31) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=26 && x <=28 && y>=26 && y<=30) //마지막 네임드
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==29 && y==26) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=30 && x <=34 && y>=25 && y<=30) //마지막방
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==34 && y==31) //마지막방
				env[num].dgtile[x][y].tile = DG_UP_STAIR;
			else
				env[num].dgtile[x][y].tile = DG_WALL;
		}
	}

	env[num].MakeEvent(1,coord_def(14,10),EVT_SIGHT);
	env[num].MakeEvent(2,coord_def(14,11),EVT_ABOVE);
	env[num].MakeEvent(3,coord_def(17,18),EVT_SIGHT);
	env[num].MakeEvent(4,coord_def(25,18),EVT_SIGHT);
	env[num].MakeEvent(5,coord_def(29,18),EVT_SIGHT);
	env[num].MakeEvent(6,coord_def(29,18),EVT_ABOVE);
	env[num].MakeEvent(8,coord_def(12,22),EVT_SIGHT);
	env[num].MakeEvent(9,coord_def(17,22),EVT_SIGHT);
	env[num].MakeEvent(10,coord_def(24,22),EVT_SIGHT);
	env[num].MakeEvent(11,coord_def(30,22),EVT_SIGHT);


	env[num].MakeEvent(12,coord_def(36,22),EVT_SIGHT);
	env[num].MakeEvent(13,coord_def(37,29),EVT_SIGHT);
	env[num].MakeEvent(16,coord_def(37,33),EVT_SIGHT);
	env[num].MakeEvent(17,coord_def(31,33),EVT_SIGHT);
	env[num].MakeEvent(18,coord_def(27,33),EVT_SIGHT);
	env[num].MakeEvent(19,coord_def(27,27),EVT_SIGHT);
	env[num].MakeEvent(20,coord_def(34,31),EVT_SIGHT);



	env[num].stair_up[0].x = 7;
	env[num].stair_up[0].y = 7;

	env[num].stair_up[1].x = 34;
	env[num].stair_up[1].y = 31;





	item_infor t;
	t.type = ITM_WEAPON_MACE;
	t.num = 1;
	t.curse = false;
	t.is_pile = false;
	t.value1 = 4;
	t.value2 = 7;
	t.value3 = 0;
	t.value4 = 1;
	t.value5 = 0;
	t.value6 = 0;
	t.value7 = 13;
	t.value8 = 7;
	t.can_throw = false;
	t.image = &img_item_weapon_gohey2;
	t.name.name = "고헤이";
	t.name.name_type = false; //true 받침있음
	t.name2.name = "";
	t.name2.name_type = true;
	t.weight = 3.0f;
	t.value = 60;


	env[num].MakeItem(coord_def(16,18),t);

	
	//t.type = ITM_ARMOR_BODY_ARMOUR_0;
	//t.num = 1;
	//t.curse = false;
	//t.value1 = 1;
	//t.value2 = 0;
	//t.value3 = 0;
	//t.value4 = 0;
	//t.value5 = 0;
	//t.value6 = 0;
	//t.is_pile = false;
	//t.can_throw = false;
	//t.name.name = "무녀복";
	//t.image = &img_item_armor_robe_sanae;
	//t.name.name_type = true;
	//t.name2.name = "";
	//t.name2.name_type = true;
	//t.weight = 6.0f;
	//t.value = 40;
	
	{
		item* i = env[num].MakeItem(coord_def(18,18),makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_MIKO));
		i->image = &img_item_armor_robe_sanae;
		i->equip_image = &img_play_item_body[11];
	}
	

	env[num].AddMonster(MON_EVENT_MOOK,0,coord_def(25,18));
	env[num].AddMonster(MON_EVENT_MOOK,0,coord_def(25,17));
	env[num].AddMonster(MON_EVENT_MOOK,0,coord_def(25,19));
	env[num].AddMonster(MON_EVENT_MOOK,0,coord_def(26,18));

	env[num].AddMonster(MON_EVENT_REIMUYUKKURI,0,coord_def(18,22));

	env[num].AddMonster(MON_SPIDER,0,coord_def(37,29));

	env[num].AddMonster(MON_TEST_KATPA,0,coord_def(31,32));
	env[num].AddMonster(MON_TEST_KATPA,0,coord_def(31,33));
	env[num].AddMonster(MON_TEST_KATPA,0,coord_def(31,34));



	env[num].AddMonster(MON_KOGASA,0,coord_def(27,27));

	env[current_level].MakeItem(coord_def(12,22),makeitem(ITM_THROW_TANMAC, 0, &t, TMT_AMULET));

	env[num].MakeItem(coord_def(23,22),makeitem(ITM_RING, -1, &t, RGT_HUNGRY));
	env[num].MakeItem(coord_def(24,22),makeitem(ITM_SCROLL, 0, &t, SCT_REMOVE_CURSE));
	env[num].MakeItem(coord_def(24,22),makeitem(ITM_SCROLL, 0, &t, SCT_REMOVE_CURSE));
	env[num].MakeItem(coord_def(24,22),makeitem(ITM_SCROLL, 0, &t, SCT_REMOVE_CURSE));
	env[num].MakeItem(coord_def(25,22),makeitem(ITM_SCROLL, 0, &t, SCT_IDENTIFY));
	env[num].MakeItem(coord_def(25,22),makeitem(ITM_SCROLL, 0, &t, SCT_IDENTIFY));
	env[num].MakeItem(coord_def(25,22),makeitem(ITM_SCROLL, 0, &t, SCT_IDENTIFY));

	env[num].MakeItem(coord_def(30,22),makeitem(ITM_POTION, 0, &t, PT_MIGHT));
	env[num].MakeItem(coord_def(30,22),makeitem(ITM_POTION, 0, &t, PT_MIGHT));

	env[num].MakeItem(coord_def(37,22),makeitem(ITM_BOOK, 0, &t, BOOK_WIZARD_BASE));


	env[num].stair_down[0].x = 29;
	env[num].stair_down[0].y = 18;
	env[num].dgtile[29][18].tile = DG_DOWN_STAIR;
	env[num].stair_down[1].x = 11;
	env[num].stair_down[1].y = 22;
	env[num].dgtile[11][22].tile = DG_DOWN_STAIR;

	env[num].dgtile[37][33].tile = DG_TEMPLE_KANAKO;

	you.GiveSkillExp(SKT_FIGHT,90,false);
	you.GiveSkillExp(SKT_MACE,45,false);
	you.GiveSkillExp(SKT_TANMAC,70,false);
	you.GiveSkillExp(SKT_DODGE,50,false);
}








void map_algorithms_tuto02(int num)
{
	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			if(x>=28 && x <=29  && y==31)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==30 && y==31) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=31 && x <=33  && y>=30 && y<=32)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else if(x==34 && y==31) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x>=35 && x <=36  && y==31)
				env[num].dgtile[x][y].tile = DG_FLOOR;
			else
				env[num].dgtile[x][y].tile = DG_WALL;
		}
	}

	env[num].MakeEvent(7,coord_def(32,31),EVT_APPROACH_SMALL);
	env[num].MakeEvent(14,coord_def(36,31),EVT_ABOVE);
	
	item_infor t;
	env[num].MakeItem(coord_def(32,31),makeitem(ITM_FOOD, 0, &t, 0));

	env[num].stair_up[0].x = 28;
	env[num].stair_up[0].y = 31;
	env[num].dgtile[28][31].tile = DG_UP_STAIR;

	env[num].stair_up[1].x = 36;
	env[num].stair_up[1].y = 31;
	env[num].dgtile[36][31].tile = DG_UP_STAIR;

}





void map_algorithms_tuto03(int num)
{
	
	item_infor t;

	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{

			if(x==10 && y==7) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x==16 && y==7) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x==22 && y==7) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x==28 && y==7) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x==34 && y==7) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x==40 && y==7) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x==46 && y==7) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x==52 && y==7) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if (x == 58 && y == 7) //문
				env[num].dgtile[x][y].tile = DG_CLOSE_DOOR;
			else if(x==59 && y==7) //계단
				env[num].dgtile[x][y].tile = DG_UP_STAIR;
			
			
			else if(x>=5 && x <=9 && y>=5 && y<=9) //첫째방
				env[num].dgtile[x][y].tile = DG_FLOOR;

			else if(x>=11 && x <=15 && y>=5 && y<=9) //둘째방
				env[num].dgtile[x][y].tile = DG_FLOOR;
			
			else if(x>=17 && x <=21 && y>=5 && y<=9) //셋째방
				env[num].dgtile[x][y].tile = DG_FLOOR;
			
			else if(x>=23 && x <=27 && y>=5 && y<=9) //넷째방
				env[num].dgtile[x][y].tile = DG_FLOOR;
			
			else if(x>=29 && x <=33 && y>=5 && y<=9) //다섯째방
				env[num].dgtile[x][y].tile = DG_FLOOR;

			
			else if(x>=35 && x <=39 && y>=5 && y<=9) //여섯째방
				env[num].dgtile[x][y].tile = DG_FLOOR;
			
			else if(x>=41 && x <=45 && y>=5 && y<=9) //일곱째방
				env[num].dgtile[x][y].tile = DG_FLOOR;
			
			else if(x>=47 && x <=51 && y>=5 && y<=9) //여덟째방
				env[num].dgtile[x][y].tile = DG_FLOOR;

			else if (x >= 53 && x <= 57 && y >= 5 && y <= 9) //여덟째방
				env[num].dgtile[x][y].tile = DG_FLOOR;
			
			else if(x>=5 && x <=59 && y==7) //길목
				env[num].dgtile[x][y].tile = DG_FLOOR;

			else
				env[num].dgtile[x][y].tile = DG_WALL;
		}
	}




	
	env[num].stair_up[0].x = 7;
	env[num].stair_up[0].y = 7;

	

	env[num].MakeEvent(24,coord_def(7,7),EVT_SIGHT);

	env[num].MakeEvent(25,coord_def(13,7),EVT_SIGHT);	
	env[num].MakeItem(coord_def(12,7),makeitem(ITM_WEAPON_SHORTBLADE, 0, &t, 10));
	env[num].MakeItem(coord_def(14,7),makeitem(ITM_WEAPON_MACE, 0, &t, 40));
	
	env[num].MakeEvent(26,coord_def(19,7),EVT_SIGHT);
	env[num].MakeItem(coord_def(18,7),makeitem(ITM_ARMOR_BODY_ARMOUR_2, 0, &t, 0));
	env[num].MakeItem(coord_def(20,7),makeitem(ITM_ARMOR_SHIELD, 0, &t, 0));

	env[num].MakeEvent(27,coord_def(25,7),EVT_SIGHT);

	env[num].MakeEvent(28,coord_def(31,7),EVT_SIGHT);
	env[num].MakeItem(coord_def(30,7),makeitem(ITM_THROW_TANMAC, 0, &t, TMT_AMULET));
	env[num].MakeItem(coord_def(32,7),makeitem(ITM_WEAPON_LONGBLADE, 0, &t, 30));
	
	env[num].MakeEvent(29,coord_def(37,7),EVT_SIGHT);
	env[num].MakeEvent(EVL_SIGHT_P,coord_def(37,6),EVT_SIGHT);
	env[num].MakeEvent(EVL_SIGHT_P,coord_def(37,8),EVT_SIGHT);	

	env[num].MakeEvent(30,coord_def(43,7),EVT_SIGHT);
	env[num].MakeItem(coord_def(42,7),makeitem(ITM_SPELL, 0, &t, SPC_V_FIRE));
	env[num].MakeItem(coord_def(44,7),makeitem(ITM_MISCELLANEOUS, 0, &t, EVK_PAGODA));


	env[num].MakeEvent(31, coord_def(49, 7), EVT_SIGHT);
	env[num].MakeItem(coord_def(48, 7), makeitem(ITM_AMULET, 0, &t, AMT_TIMES));
	env[num].MakeItem(coord_def(50, 7), makeitem(ITM_AMULET, 0, &t, AMT_GRAZE));
	
	env[num].MakeEvent(32,coord_def(55,7),EVT_SIGHT);
	env[num].MakeItem(coord_def(54,7),makeitem(ITM_GOAL, 0, &t, RUNE_YOUKAI_MOUNTAIN));
	env[num].MakeItem(coord_def(56,7),makeitem(ITM_ORB, 0, &t, 0));


	env[num].stair_up[1].x = 59;
	env[num].stair_up[1].y = 7;
}