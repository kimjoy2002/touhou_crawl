//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: map_file.cpp
//
// 내용: 맵을 만드는 함수들(세부)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "map.h"
#include "throw.h"
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
		level_ == SUBTERRANEAN_LEVEL)
		return true;
	return false;
	//if(level_<MAX_DUNGEUN_LEVEL-1 || (level_>=YOUKAI_MOUNTAIN_LEVEL && current_level<YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL) 
	//		|| (level_>=MISTY_LAKE_LEVEL && level_<MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL) 
	//		|| (level_>=SCARLET_LEVEL && level_<SCARLET_LEVEL+MAX_SCARLET_LEVEL) )
	//		return false;
	//return true;
}

bool environment::isLastFloor(int level_)
{
	if( level_ == MAX_DUNGEUN_LEVEL-1 || //?
		level_ == TEMPLE_LEVEL ||
		level_ == YOUKAI_MOUNTAIN_LAST_LEVEL ||
		level_ == MISTY_LAKE_LAST_LEVEL ||
		level_ == SCARLET_LEVEL_LAST_LEVEL ||
		level_ == SCARLET_LIBRARY_LEVEL_LAST_LEVEL ||
		level_ == SCARLET_UNDER_LEVEL_LAST_LEVEL ||
		level_ == BAMBOO_LEVEL_LAST_LEVEL ||
		level_ == EIENTEI_LEVEL_LAST_LEVEL ||
		level_ == SUBTERRANEAN_LEVEL_LAST_LEVEL)
		return true;
	return false;
	//if(level_<MAX_DUNGEUN_LEVEL-1 || (level_>=YOUKAI_MOUNTAIN_LEVEL && current_level<YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL) 
	//		|| (level_>=MISTY_LAKE_LEVEL && level_<MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL) 
	//		|| (level_>=SCARLET_LEVEL && level_<SCARLET_LEVEL+MAX_SCARLET_LEVEL) )
	//		return false;
	//return true;
}


void initMap()
{
	map_list.dungeon_enter[TEMPLE].set(false,0,0,rand_int(2,4));
	map_list.dungeon_enter[MISTY_LAKE].set(false,0,0,rand_int(6,9));
	map_list.dungeon_enter[YOUKAI_MOUNTAIN].set(false,0,0,MISTY_LAKE_LEVEL+rand_int(1,2));
	map_list.dungeon_enter[SCARLET_M].set(false,0,0,MISTY_LAKE_LEVEL+rand_int(3,4));	
	map_list.dungeon_enter[SCARLET_L].set(false,0,0,SCARLET_LEVEL+rand_int(1,2));	
	map_list.dungeon_enter[SCARLET_U].set(false,0,0,SCARLET_LEVEL+3);
	map_list.dungeon_enter[BAMBOO].set(false,0,0,rand_int(10,13));
	map_list.dungeon_enter[SUBTERRANEAN].set(false,0,0,rand_int(12,14));

	map_list.god_num = 10;
	deque<int> dq;
	for(int i=0;i<GT_LAST;i++)
		dq.push_back(i);
	random_shuffle(dq.begin(),dq.end());
	for(int i=0;i<GT_LAST-map_list.god_num;i++)
	{
		map_list.temple[dq[i]].set(false,0,0,rand_int(1,5));
	}
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
	map->tiles[map->m_entrance.x+map->size_x][map->m_entrance.y+map->size_y] = DG_FLOOR;
	map->tiles[map->m_exit.x+map->size_x][map->m_exit.y+map->size_y] = DG_FLOOR;

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
				map->tiles[i][j] = DG_WALL;
			else if((i-map->size_x)*(i-map->size_x) + (j-map->size_y)*(j-map->size_y) > ((map->size_y>map->size_x)?map->size_y:map->size_x)*((map->size_y>map->size_x)?map->size_y:map->size_x))
				map->tiles[i][j] = DG_NONE;
			else
				map->tiles[i][j] = DG_FLOOR;
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
	map->tiles[map->m_entrance.x+map->size_x][map->m_entrance.y+map->size_y] = DG_FLOOR;
	map->tiles[map->m_exit.x+map->size_x][map->m_exit.y+map->size_y] = DG_FLOOR;

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
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_FLOOR;
				break;
			case '#':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_WALL;
				break;
			case '0':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_TEMPLE_STAIR;
				map_list.dungeon_enter[TEMPLE].detected = true;
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
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_FLOOR;
				break;
			case '#':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_WALL;
				break;
			case '0':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_YOUKAI_MOUNTAIN_STAIR;
				map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected = true;
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
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_FLOOR;
				break;
			case '#':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_WALL;
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
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_FLOOR;
				break;
			case '#':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_WALL;
				break;
			case '+':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_CLOSE_DOOR;
				break;	
			case '=':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_GLASS;
				break;
			case '~':
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = DG_SEA;
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
				map->tiles[i%(map->size_x*2+1)][i/(map->size_x*2+1)] = map->sp_tile_list[temp[j]-'0'];

				if(map->sp_tile_list[temp[j]-'0']>= DG_SUB_STAIR_FIRST && map->sp_tile_list[temp[j]-'0'] < DG_SUB_STAIR_MAX)
				{//특수 지형이 만약 서브던젼 계단입구일 경우
					int stiar_enter_ = map->sp_tile_list[temp[j]-'0'] - DG_SUB_STAIR_FIRST;
					map_list.dungeon_enter[stiar_enter_].detected = true;
					map_list.dungeon_enter[stiar_enter_].pos = coord_def(i%(map->size_x*2+1)-map->size_x,i/(map->size_x*2+1)-map->size_y);
					map_list.dungeon_enter[stiar_enter_].pos += map->pos;
				}
				break;
			}
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
	map->tiles[map->m_entrance.x+map->size_x][map->m_entrance.y+map->size_y] = DG_FLOOR;
	map->tiles[map->m_exit.x+map->size_x][map->m_exit.y+map->size_y] = DG_FLOOR;

	int x_=rand_int(1,map->size_x*2-1),y_=rand_int(1,map->size_y*2-1);
	map->tiles[x_][y_] =(dungeon_tile_type)(DG_TEMPLE_FIRST+temple_);
	map_list.temple[temple_].detected = true;
	map_list.temple[temple_].pos = coord_def(x_,y_);

	map->m_entrance+=map->pos;
	map->m_exit+=map->pos;
}

void map_dummy::patternSet()
{
	if(pattern == 0) //서브던전입구의 패턴 = 100+서브던전 | 제단패턴 = 100+서브던전갯수+제단모양
	{
		baseMap(this);
	}
	else if(pattern == 1)
	{
		baseCircleMap(this);
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

