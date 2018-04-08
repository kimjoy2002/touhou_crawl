//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: map_file.cpp
//
// 내용: 맵을 만드는 함수들(세부)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "map.h"
#include "throw.h"
#include "rand_shuffle.h"
#include "mon_infor.h"
#include <algorithm>

map_infor map_list;


bool environment::isFirstFloor(int level_)
{
	if( level_ == 0 || //?
		level_ == TEMPLE_LEVEL ||
		level_ == YOUKAI_MOUNTAIN_LEVEL ||
		level_ == MISTY_LAKE_LEVEL ||
		level_ == SCARLET_LEVEL ||
		level_ == SCARLET_LIBRARY_LEVEL ||
		level_ == SCARLET_UNDER_LEVEL ||
		level_ == BAMBOO_LEVEL ||
		level_ == EIENTEI_LEVEL ||
		level_ == SUBTERRANEAN_LEVEL ||		
		level_ == YUKKURI_LEVEL ||
		level_ == DEPTH_LEVEL ||
		level_ == DREAM_LEVEL ||
		level_ == MOON_LEVEL ||
		(level_ >= PANDEMONIUM_LEVEL && level_ <= PANDEMONIUM_LAST_LEVEL)||
		level_ == HAKUREI_LEVEL ||
		level_ == OKINA_LEVEL
		) 
		return true;
	return false;
	//if(level_<MAX_DUNGEUN_LEVEL || (level_>=YOUKAI_MOUNTAIN_LEVEL && current_level<YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL) 
	//		|| (level_>=MISTY_LAKE_LEVEL && level_<MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL) 
	//		|| (level_>=SCARLET_LEVEL && level_<SCARLET_LEVEL+MAX_SCARLET_LEVEL) )
	//		return false;
	//return true;
}

bool environment::isLastFloor(int level_)
{
	if( level_ == MAX_DUNGEUN_LEVEL || //?
		level_ == TEMPLE_LEVEL ||
		level_ == YOUKAI_MOUNTAIN_LAST_LEVEL ||
		level_ == MISTY_LAKE_LAST_LEVEL ||
		level_ == SCARLET_LEVEL_LAST_LEVEL ||
		level_ == SCARLET_LIBRARY_LEVEL_LAST_LEVEL ||
		level_ == SCARLET_UNDER_LEVEL_LAST_LEVEL ||
		level_ == BAMBOO_LEVEL_LAST_LEVEL ||
		level_ == EIENTEI_LEVEL_LAST_LEVEL ||
		level_ == SUBTERRANEAN_LEVEL_LAST_LEVEL ||
		level_ == YUKKURI_LAST_LEVEL ||
		level_ == DEPTH_LAST_LEVEL ||
		level_ == DREAM_LAST_LEVEL ||
		level_ == MOON_LAST_LEVEL ||
		(level_ >= PANDEMONIUM_LEVEL && level_ <= PANDEMONIUM_LAST_LEVEL )||
		level_ == HAKUREI_LAST_LEVEL ||
		level_ == OKINA_LEVEL)
		return true;
	return false;
	//if(level_<MAX_DUNGEUN_LEVEL || (level_>=YOUKAI_MOUNTAIN_LEVEL && current_level<YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL) 
	//		|| (level_>=MISTY_LAKE_LEVEL && level_<MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL) 
	//		|| (level_>=SCARLET_LEVEL && level_<SCARLET_LEVEL+MAX_SCARLET_LEVEL) )
	//		return false;
	//return true;
}


bool isTutorial()
{
	return map_list.tutorial == GM_TUTORIAL || map_list.tutorial == GM_TUTORIAL2;
}

bool isNormalGame()
{
	return map_list.tutorial == GM_NORMAL;
}

bool isArena()
{
	return map_list.tutorial == GM_SPRINT1_AREANA;

}
bool isSprint()
{
	return map_list.tutorial == GM_SPRINT2_MINISTAGE;
}
int sprintMulti()
{
	return 7;
}

void initMap()
{
	map_list.dungeon_enter[TEMPLE].set(false,0,0,rand_int(2,5));
	map_list.dungeon_enter[MISTY_LAKE].set(false,0,0,rand_int(7,9));
	map_list.dungeon_enter[YOUKAI_MOUNTAIN].set(false,0,0,MISTY_LAKE_LEVEL+rand_int(1,2));
	map_list.dungeon_enter[SCARLET_M].set(false,0,0,MISTY_LAKE_LEVEL+rand_int(3,4));	
	map_list.dungeon_enter[SCARLET_L].set(false,0,0,SCARLET_LEVEL+rand_int(1,2));	
	map_list.dungeon_enter[SCARLET_U].set(false,0,0,SCARLET_LEVEL_LAST_LEVEL);
	map_list.dungeon_enter[BAMBOO].set(false,0,0,rand_int(10,13));
	map_list.dungeon_enter[SUBTERRANEAN].set(false,0,0,DEPTH_LEVEL+rand_int(1,3));



	map_list.dungeon_enter[YUKKURI_D].set(false,0,0,YOUKAI_MOUNTAIN_LAST_LEVEL);	
	map_list.dungeon_enter[DEPTH].set(false,0,0,MAX_DUNGEUN_LEVEL);	
	map_list.dungeon_enter[DREAM_D].set(false,0,0,DEPTH_LEVEL+rand_int(1,3));
	//map_list.dungeon_enter[MOON_D].set(false,0,0,rand_int(10,13));
	map_list.dungeon_enter[PANDEMONIUM].set(false,0,0,DEPTH_LEVEL+rand_int(1,3));
	map_list.dungeon_enter[HAKUREI_D].set(false,0,0,DEPTH_LAST_LEVEL);

	map_list.god_num = 10;
	map_list.bamboo_count = 0;
	map_list.bamboo_rate = 0;
	//map_list.tutorial = 0;
	map_list.bamboo_tewi = false;
	deque<int> dq;
	for(int i=0;i<GT_LAST;i++)
	{
		if(i != GT_SEIJA) //세이자는 무조건 나온다.
			dq.push_back(i);
	}
	rand_shuffle(dq.begin(),dq.end());
	for(int i=0;i<GT_LAST-map_list.god_num;i++)
	{
		map_list.temple[dq[i]].set(false,0,0,rand_int(1,5));
	}
	map_list.temple[GT_SEIJA].set(false,0,0,rand_int(1,5));
	//map_list.temple[GT_SUWAKO].set(false,0,0,0);
}



void baseMap(map_dummy* map)
{
	map->tiles = new dungeon_tile_type*[map->size_x*2+1];
	for(int i=0;i<map->size_x*2+1;i++)
		map->tiles[i] = new dungeon_tile_type[map->size_y*2+1];

	for(int i = 0;i<map->size_x*2+1;i++)
	{
		for(int j = 0;j<map->size_y*2+1;j++)
		{
			if(map->wall && (i==0 || j==0 || i==map->size_x*2 || j==map->size_y*2))
				map->tiles[i][j] = map->wall_tex;
			else
				map->tiles[i][j] = map->floor_tex;
		}
	}
	if(randA(1))
	{
		map->m_entrance.x = rand_int(-map->size_x+1,map->size_x-1);
		map->m_entrance.y = (randA(1)?-map->size_y:map->size_y);
	}
	else
	{
		map->m_entrance.x = (randA(1)?-map->size_x:map->size_x);
		map->m_entrance.y = rand_int(-map->size_y+1,map->size_y-1);
	}
	if(randA(1))
	{
		map->m_exit.x = rand_int(-map->size_x+1,map->size_x-1);
		map->m_exit.y = (randA(1)?-map->size_y:map->size_y);
	}
	else
	{
		map->m_exit.x = (randA(1)?-map->size_x:map->size_x);
		map->m_exit.y = rand_int(-map->size_y+1,map->size_y-1);
	}
	map->tiles[map->m_entrance.x+map->size_x][map->m_entrance.y+map->size_y] = map->floor_tex;
	map->tiles[map->m_exit.x+map->size_x][map->m_exit.y+map->size_y] = map->floor_tex;

	map->m_entrance+=map->pos;
	map->m_exit+=map->pos;
}
void baseCircleMap(map_dummy* map)
{
	map->tiles = new dungeon_tile_type*[map->size_x*2+1];
	for(int i=0;i<map->size_x*2+1;i++)
		map->tiles[i] = new dungeon_tile_type[map->size_y*2+1];

	for(int i = 0;i<map->size_x*2+1;i++)
	{
		for(int j = 0;j<map->size_y*2+1;j++)
		{
			if(map->wall && (i==0 || j==0 || i==map->size_x*2 || j==map->size_y*2))
				map->tiles[i][j] = map->wall_tex;
			else if((i-map->size_x)*(i-map->size_x) + (j-map->size_y)*(j-map->size_y) > ((map->size_y>map->size_x)?map->size_y:map->size_x)*((map->size_y>map->size_x)?map->size_y:map->size_x))
				map->tiles[i][j] = DG_NONE;
			else
				map->tiles[i][j] = map->floor_tex;
		}
	}
	if(randA(1))
	{
		map->m_entrance.x = 0;
		map->m_entrance.y = (randA(1)?-map->size_y:map->size_y);
	}
	else
	{
		map->m_entrance.x = (randA(1)?-map->size_x:map->size_x);
		map->m_entrance.y = 0;
	}
	if(randA(1))
	{
		map->m_exit.x = 0;
		map->m_exit.y = (randA(1)?-map->size_y:map->size_y);
	}
	else
	{
		map->m_exit.x = (randA(1)?-map->size_x:map->size_x);
		map->m_exit.y = 0;
	}
	map->tiles[map->m_entrance.x+map->size_x][map->m_entrance.y+map->size_y] = map->floor_tex;
	map->tiles[map->m_exit.x+map->size_x][map->m_exit.y+map->size_y] = map->floor_tex;

	map->m_entrance+=map->pos;
	map->m_exit+=map->pos;
}





void TempleEnterMap(map_dummy* map)
{

	char *temp = temple_pattern(map);
	map->tiles = new dungeon_tile_type*[map->size_x*2+1];
	for(int i=0;i<map->size_x*2+1;i++)
		map->tiles[i] = new dungeon_tile_type[map->size_y*2+1];


	for(int i=0,j=0;temp[j]!='\0';j++)
	{
		if(i>=(map->size_x*2+1)*(map->size_y*2+1))
		{
			break;
		}
		if(temp[j]!=' ')
		{
			switch(temp[j])
			{
			case '.':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = map->floor_tex;
				break;
			case '#':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = map->wall_tex;
				break;
			case '0':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_TEMPLE_STAIR;
				//map_list.dungeon_enter[TEMPLE].detected = true;
				map_list.dungeon_enter[TEMPLE].pos = coord_def(i%(map->size_x*2+1)-map->size_x,i/(map->size_x*2+1)-map->size_y);
				map_list.dungeon_enter[TEMPLE].pos += map->pos;
				break;
			case '+':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_CLOSE_DOOR;
				break;
			default:
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_FLOOR2;
				break;
			}
			i++;
		}	
	}
	map->m_entrance+=map->pos;
	map->m_exit+=map->pos;
}


void YoukaiEnterMap(map_dummy* map)
{

	char *temp = temple_pattern(map);
	map->tiles = new dungeon_tile_type*[map->size_x*2+1];
	for(int i=0;i<map->size_x*2+1;i++)
		map->tiles[i] = new dungeon_tile_type[map->size_y*2+1];


	for(int i=0,j=0;temp[j]!='\0';j++)
	{
		if(i>=(map->size_x*2+1)*(map->size_y*2+1))
		{
			break;
		}
		if(temp[j]!=' ')
		{
			switch(temp[j])
			{
			case '.':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = map->floor_tex;
				break;
			case '#':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = map->wall_tex;
				break;
			case '0':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_YOUKAI_MOUNTAIN_STAIR;
				//map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected = true;
				map_list.dungeon_enter[YOUKAI_MOUNTAIN].pos = coord_def(i%(map->size_x*2+1)-map->size_x,i/(map->size_x*2+1)-map->size_y);
				map_list.dungeon_enter[YOUKAI_MOUNTAIN].pos += map->pos;
				break;
			case '+':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_CLOSE_DOOR;
				break;
			default:
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_FLOOR2;
				break;
			}
			i++;
		}	
	}
	map->m_entrance+=map->pos;
	map->m_exit+=map->pos;
}


bool CommonValutMap(map_dummy* map, int pattern)
{
	char *temp;
	switch(pattern)
	{
	case VP_YOUKAI_MOUNTAIN_LAST:
		temp = youkai_last_vault_pattern(map);
		break;
	case VP_SCARLET_LAST:
		temp = scarlet_last_vault_pattern(map);
		break;
	case VP_EIENTEI_LAST:
		temp = eientei_vault_pattern(map);
		break;
	case VP_PANDEMONIUM_1_LAST:
		temp = pandemonium_baykuren_last_vault_pattern(map);
		break;
	case VP_PANDEMONIUM_2_LAST:
		temp = pandemonium_ice_last_vault_pattern(map);
		break;
	case VP_PANDEMONIUM_3_LAST:
		temp = pandemonium_shinki_last_vault_pattern(map);
		break;
	case VP_YUKKURI_LAST:
		temp = yukkuri_last_vault_pattern(map);
		break;
	case VP_MOON_LAST:
		temp = moon_last_vault_pattern(map);
		break;
	case VP_SUBTERRANEAN_LAST:
		temp = subterranean_last_vault_pattern(map);
		break;
	case VP_HAKUREI_LAST:
		temp = hakurei_last_vault_pattern(map);
	default:
		return false;
	}
	map->tiles = new dungeon_tile_type*[map->size_x*2+1];
	for(int i=0;i<map->size_x*2+1;i++)
		map->tiles[i] = new dungeon_tile_type[map->size_y*2+1];


	for(int i=0,j=0;temp[j]!='\0';j++)
	{
		if(i>=(map->size_x*2+1)*(map->size_y*2+1))
		{
			break;
		}
		if(temp[j]!=' ')
		{
			switch(temp[j])
			{
			case '.':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = map->floor_tex;
				break;
			case '#':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = map->wall_tex;
				break;
			case 'O':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_TEMPLE_KANAKO;
				break;
			case '+':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_CLOSE_DOOR;
				break;
			default:
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_FLOOR2;
				break;
			}
			i++;
		}	
	}
	map->m_entrance+=map->pos;
	map->m_exit+=map->pos;

	return true;
}




bool PixedMap(map_dummy* map, char *temp)
{
	int sp_tile_index = 0;

	map->tiles = new dungeon_tile_type*[map->size_x*2+1];
	for(int i=0;i<map->size_x*2+1;i++)
		map->tiles[i] = new dungeon_tile_type[map->size_y*2+1];


	for(int i=0,j=0;temp[j]!='\0';j++)
	{
		if(i>=(map->size_x*2+1)*(map->size_y*2+1))
		{
			break;
		}
		if(temp[j]!=' ')
		{
			switch (temp[j])
			{
			case '`':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_NONE;
				break;
			case '.':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = map->floor_tex;
				break;
			case '#':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = map->wall_tex;
				break;
			case ',':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_FLOOR;
				break;
			case '^':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_DREAM_FLOOR;
				break;
			case '-':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_FLOOR2;
				break;
			case '_':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_GRASS;
				break;
			case '/':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_PANDE_FLOOR1;
				break;
			case 'P':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_PANDE_WALL1;
				break;
			case '@':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_WALL;
				break;
			case '*':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_STONE_WALL;
				break;
			case '$':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_METAL_WALL;
				break;
			case '[':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_BAMBOO_WALL;
				break;
			case ':':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_WALL2;
				break;
			case '(':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_RED_WALL;
				break;
			case 'T':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_TREE;
				break;
			case 'f':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_SUN_FLOWER;
				break;
			case '+':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_CLOSE_DOOR;
				break;
			case '=':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_GLASS;
				break;
			case '&':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_STATUE;
				break;
			case 'B':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_STATUE2;
				break;
			case 'E':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_BOOK_WALL;
				break;
			case '~':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_SEA;
				break;
			case ';':
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_LAVA;
				break;
			case 'i': //각 던전에서 드랍되는 아이템을 넣음
			case 'I': //여러개
			{
				int num_ = temp[j] == 'I' ? rand_int(3, 4) : 1;
				for (int k = 0; k < num_; k++) {
					item_infor t;
					CreateFloorItem(map->floor, &t);
					map->item_list.push_back(mapdummy_item(t, coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y)));
					map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = map->floor_tex;
				}
			}
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
			{
				int index_ = temp[j] !='9' ?temp[j] - '0':sp_tile_index++;
				if (map->sp_tile_list.size() <= index_)
				{
					map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = map->floor_tex;
					break;
				}

				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = map->sp_tile_list[index_];
				if (map->sp_tile_list[index_] == DG_WALL) {
					map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = map->wall_tex;
				}
				else if (map->sp_tile_list[index_] == DG_FLOOR) {
					map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = map->floor_tex;
				}
				else if (map->sp_tile_list[index_] >= DG_SUB_STAIR_FIRST && map->sp_tile_list[index_] < DG_SUB_STAIR_MAX)
				{//특수 지형이 만약 서브던젼 계단입구일 경우
					int stiar_enter_ = map->sp_tile_list[index_] - DG_SUB_STAIR_FIRST;
					if (stiar_enter_ >= SUBTERRANEAN)
						stiar_enter_--;
					if (stiar_enter_ >= PANDEMONIUM)
						stiar_enter_--;
					//map_list.dungeon_enter[stiar_enter_].detected = true;
					map_list.dungeon_enter[stiar_enter_].pos = coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y);
					map_list.dungeon_enter[stiar_enter_].pos += map->pos;
				}
				break;
			}
			case 'n':
			case 'm':
			case 'M':
			{
				//그 층에 일반적으로 나오는 몹들
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = map->floor_tex;
				int mon_ = getMonsterFromFloor(map->floor, (temp[j] == 'm' ? GMFF_FLAG_ALL : (temp[j] == 'n' ? GMFF_FLAG_ONLY_WEAK : (temp[j] == 'M' ? GMFF_FLAG_ONLY_STRONG : GMFF_FLAG_ALL))));
				if (mon_ != -1) {
					map->monster_list.push_back(mapdummy_mon(mon_, 0, coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y)));
				}
				break;
			}
			case 'd':
			case 'D':
			{
				//꿈몹
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_DREAM_FLOOR;
				int mon_ = getMonsterFromFloor(DREAM_LEVEL, (temp[j] == 'd' ? GMFF_FLAG_ALL : (temp[j] == 'D' ? GMFF_FLAG_ONLY_STRONG : GMFF_FLAG_ALL)));
				if (mon_ != -1) {
					map->monster_list.push_back(mapdummy_mon(mon_, 0, coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y)));
				}
				break;
			}
			case 'h':
			case 'H':
			{
				//지저몹
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_PANDE_FLOOR1;
				int mon_ = getMonsterFromFloor(SUBTERRANEAN_LEVEL, (temp[j] == 'd' ? GMFF_FLAG_ALL : (temp[j] == 'D' ? GMFF_FLAG_ONLY_STRONG : GMFF_FLAG_ALL)));
				if (mon_ != -1) {
					map->monster_list.push_back(mapdummy_mon(mon_, 0, coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y)));
				}
				break;
			}
			case '>':
			{
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_DOWN_STAIR;
			}
			break;
			case '<':
			{
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_UP_STAIR;
			}
			break;
			case 'S':
			{
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = map->floor_tex;
				map->pos_list.push_back(coord_def(coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y)));
			}
			break;
			case 'F':
			{
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_GRASS;
				map->pos_list.push_back(coord_def(coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y)));
			}
			break;
			case 'W':
			{
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_SEA;
				map->pos_list.push_back(coord_def(coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y)));
			}
			break;
			case 'R':
			{
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_DREAM_FLOOR;
				map->pos_list.push_back(coord_def(coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y)));
			}
			break;
			case 'p':
			{
				map->tiles[i % (map->size_x * 2 + 1)][i / (map->size_x * 2 + 1)] = DG_PANDE_FLOOR1;
				map->pos_list.push_back(coord_def(coord_def(i % (map->size_x * 2 + 1) - map->size_x, i / (map->size_x * 2 + 1) - map->size_y)));
			}
			break;
			default:
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_FLOOR2;
				break;
			}
			i++;
		}	
	}
	map->m_entrance+=map->pos;
	map->m_exit+=map->pos;

	return true;
}




void TempleMap(map_dummy* map, int temple_)
{
	map->tiles = new dungeon_tile_type*[map->size_x*2+1];
	for(int i=0;i<map->size_x*2+1;i++)
		map->tiles[i] = new dungeon_tile_type[map->size_y*2+1];

	for(int i = 0;i<map->size_x*2+1;i++)
	{
		for(int j = 0;j<map->size_y*2+1;j++)
		{
			if(i==0 || j==0 || i==map->size_x*2 || j==map->size_y*2)
				map->tiles[i][j] = DG_WALL;
			else
				map->tiles[i][j] = DG_FLOOR;
		}
	}
	if(randA(1))
	{
		map->m_entrance.x = rand_int(-map->size_x+1,map->size_x-1);
		map->m_entrance.y = (randA(1)?-map->size_y:map->size_y);
	}
	else
	{
		map->m_entrance.x = (randA(1)?-map->size_x:map->size_x);
		map->m_entrance.y = rand_int(-map->size_y+1,map->size_y-1);
	}
	if(randA(1))
	{
		map->m_exit.x = rand_int(-map->size_x+1,map->size_x-1);
		map->m_exit.y = (randA(1)?-map->size_y:map->size_y);
	}
	else
	{
		map->m_exit.x = (randA(1)?-map->size_x:map->size_x);
		map->m_exit.y = rand_int(-map->size_y+1,map->size_y-1);
	}
	map->tiles[map->m_entrance.x+map->size_x][map->m_entrance.y+map->size_y] = map->floor_tex;
	map->tiles[map->m_exit.x+map->size_x][map->m_exit.y+map->size_y] = map->floor_tex;

	int x_=rand_int(1,map->size_x*2-1),y_=rand_int(1,map->size_y*2-1);
	map->tiles[x_][y_] =(dungeon_tile_type)(DG_TEMPLE_FIRST+temple_);
	//map_list.temple[temple_].detected = true;
	map_list.temple[temple_].pos = coord_def(x_,y_);

	map->m_entrance+=map->pos;
	map->m_exit+=map->pos;
}

void map_dummy::patternSet()
{
	if(pattern == 0) //서브던전입구의 패턴 = 100+서브던전 | 제단패턴 = 100+서브던전갯수+제단모양
					//10이상 100미만: 10에 floor를 더한 만큼의 층에서의 통상특수패턴
	{				//결정되는 패턴 1000+
		baseMap(this);
	}
	else if(pattern == 1)
	{
		baseCircleMap(this);
	}
	else if(pattern >= 10 && pattern < 100)
	{
		PixedMap(this, common_base_pattern(pattern-10, this));
	}
	else if(pattern == 100+TEMPLE) //교회
	{
		//TempleEnterMap(this);
		PixedMap(this, temple_pattern(this));
	}
	else if(pattern == 100+MISTY_LAKE) //안개호수
	{
		PixedMap(this, misty_lake_pattern(this));
	}
	else if(pattern == 100+YOUKAI_MOUNTAIN) //요괴산
	{
		//YoukaiEnterMap(this);		
		PixedMap(this, youkai_mountain_pattern(this));
	}
	else if(pattern == 100+SCARLET_M) //홍마관
	{
		PixedMap(this, scarlet_pattern(this));
	}
	
	else if(pattern == 100+SCARLET_L) //도서관
	{
		PixedMap(this, scarlet_library_pattern(this));
	}
	else if(pattern == 100+SCARLET_U) //지하실
	{
		PixedMap(this, scarlet_under_pattern(this));
	}
	else if(pattern == 100+BAMBOO) //미궁의죽림
	{
		PixedMap(this, bamboo_pattern(this));
	}
	else if(pattern == 100+SUBTERRANEAN) //지저
	{
		PixedMap(this, subterranean_pattern(this));
	}
	else if(pattern == 100+YUKKURI_D) //윳쿠리
	{
		PixedMap(this, yukkuri_pattern(this));
	}
	else if(pattern == 100+DEPTH) //짐승길
	{
		PixedMap(this, depth_pattern(this));
	}
	else if(pattern == 100+DREAM_D) //꿈의세계
	{
		PixedMap(this, dream_pattern(this));
	}
	else if(pattern == 100+PANDEMONIUM) //마계
	{
		PixedMap(this, pandemonium_pattern(this));
	}
	else if(pattern == 100+HAKUREI_D) //하쿠레이
	{
		PixedMap(this, hakurei_pattern(this));
	}
	
	
	else if(pattern >= 100+MAX_SUB_DUNGEON && pattern < 100+MAX_SUB_DUNGEON+GT_LAST)
	{
		if(randA(3))
			PixedMap(this, altar_pattern((this),(god_type)(pattern-100-MAX_SUB_DUNGEON)));
		else
			TempleMap(this,pattern-100-MAX_SUB_DUNGEON);
	}
	else if(pattern >= VP_FIRST)
	{
		switch(pattern)
		{
		case VP_YOUKAI_MOUNTAIN_LAST:
			PixedMap(this, youkai_last_vault_pattern(this));
			//temp = youkai_last_vault_pattern(map);
			break;
		case VP_SCARLET_LAST:
			PixedMap(this, scarlet_last_vault_pattern(this));
			//temp = youkai_last_vault_pattern(map);
			break;
		case VP_EIENTEI_LAST:
			PixedMap(this, eientei_vault_pattern(this));
			//temp = youkai_last_vault_pattern(map);
			break;
		case VP_PANDEMONIUM_1_LAST:
			PixedMap(this, pandemonium_baykuren_last_vault_pattern(this));
			break;
		case VP_PANDEMONIUM_2_LAST:
			PixedMap(this, pandemonium_ice_last_vault_pattern(this));
			break;
		case VP_PANDEMONIUM_3_LAST:
			PixedMap(this, pandemonium_shinki_last_vault_pattern(this));
			break;
		case VP_YUKKURI_LAST:
			PixedMap(this, yukkuri_last_vault_pattern(this));
			break;
		case VP_MOON_LAST:
			PixedMap(this, moon_last_vault_pattern(this));
			break;
		case VP_SUBTERRANEAN_LAST:
			PixedMap(this, subterranean_last_vault_pattern(this));
			break;
		case VP_HAKUREI_LAST:
			PixedMap(this, hakurei_last_vault_pattern(this));
			break;
		default:
			baseMap(this);
			break;
		}
		//if(!CommonValutMap(this,pattern))
		//	baseMap(this);
			
	}
	else
	{
		baseMap(this);
	}
}

