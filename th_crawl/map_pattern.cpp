//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: map_pattern.cpp
//
// 내용: 맵 패턴 저장소
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "map.h"
#include "throw.h"
#include "mon_infor.h"



char* common_enter_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		map->size_x = 3;
		map->size_y = 3;	
		map->m_entrance.x = -map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = map->size_x;
		map->m_exit.y = 0;
		/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
		return  "\
#######\
#.....#\
#.....#\
+..0..+\
#.....#\
#.....#\
#######";
		break;
	}
}



char* temple_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_TEMPLE_STAIR); //0은 템플 입구로 친다.
	switch(randA(7))
	{
	default:
	case 0:
		map->size_x = 3;
		map->size_y = 3;	
		map->m_entrance.x = -map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = map->size_x;
		map->m_exit.y = 0;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
		return  "\
###.###\
##...##\
#.....#\
+..0..+\
#.....#\
##...##\
###.###";
		break;
	case 1:
		map->size_x = 10;
		map->size_y = 2;
		map->m_entrance.x = -map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = -map->size_x;
		map->m_exit.y = 0;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
		return  "\
#####################\
#.....#.....#.....###\
+..#.....#.....#..0##\
#.....#.....#.....###\
#####################";
		break;
	case 2:
		map->size_x = 5;
		map->size_y = 4;
		map->m_entrance.x = 4;
		map->m_entrance.y = -map->size_y;
		map->m_exit.x = 4;
		map->m_exit.y = -map->size_y;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
		return  "\
#########.#\
#.......#.#\
#.#####.#.#\
#.#...#.#.#\
#.#.#0#.#.#\
#.#.###.#.#\
#.#.....#.#\
#.#######.#\
#.........#\
###########";
		break;
	case 3:
		map->size_x = 3;
		map->size_y = 3;
		map->m_entrance.x = -map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = map->size_x;
		map->m_exit.y = 0;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
		return  "\
###.###\
#.#.#.#\
###+###\
..+0+..\
###+###\
#.#.#.#\
###.###";
		break;
	case 4:
		map->size_x = 3;
		map->size_y = 2;
		map->m_entrance.x = 0;
		map->m_entrance.y = -map->size_y;
		map->m_exit.x = 0;
		map->m_exit.y = -map->size_y;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
		return  "\
===+===\
=~=0=~=\
=~===~=\
=~~~~~=\
=======";
		break;
	case 5:
		{
			bool hw_ = randA(1);
			map->size_x = 4;
			map->size_y = 4;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			return  "\
.........\
...~~~...\
..~~~~~..\
.~~~~~~~.\
.~~~0~~~.\
.~~~~.~~.\
..~~.~~..\
...~~....\
.........";
			break;		
		}
	case 6:
		{
			bool hw_ = randA(1);
			map->size_x = 6;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			map->monster_list.push_back(mapdummy_mon(randA(2)==0?MON_MOOK:randA(1)?MON_GREEN_MOOK:MON_GRAY_MOOK,0,coord_def(-3,1)));
			map->monster_list.push_back(mapdummy_mon(randA(2)==0?MON_MOOK:randA(1)?MON_GREEN_MOOK:MON_GRAY_MOOK,0,coord_def(-1,-1)));
			map->monster_list.push_back(mapdummy_mon(randA(2)==0?MON_MOOK:randA(1)?MON_GREEN_MOOK:MON_GRAY_MOOK,0,coord_def(1,1)));
			map->monster_list.push_back(mapdummy_mon(randA(2)==0?MON_MOOK:randA(1)?MON_GREEN_MOOK:MON_GRAY_MOOK,0,coord_def(3,-1)));
			return  "\
.............\
.===========.\
.=.........=.\
.=....0....=.\
.=.........=.\
.=====+=====.\
.............";
			break;
		}
	case 7:
		{
			bool hw_ = randA(1);
			map->size_x = 4;
			map->size_y = 4;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			return  "\
.........\
.===.===.\
.=~=.=~=.\
.===.===.\
....0....\
.===.===.\
.=~=.=~=.\
.===.===.\
.........";
		}
	}
}


char* misty_lake_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_MISTY_LAKE_STAIR);
	return common_enter_pattern(map);
}
char* youkai_mountain_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_YOUKAI_MOUNTAIN_STAIR);
	return common_enter_pattern(map);
}

char* scarlet_library_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_SCARLET_L_STAIR);
	return common_enter_pattern(map);
}
char* scarlet_under_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_SCARLET_U_STAIR);
	return common_enter_pattern(map);
}
char* bamboo_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_BAMBOO_STAIR);
	return common_enter_pattern(map);
}
char* subterranean_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_SUBTERRANEAN_STAIR);
	return common_enter_pattern(map);
}


char* scarlet_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_SCARLET_STAIR);	
	switch(randA(0))
	{
	default:
	case 0:
		map->size_x = 3;
		map->size_y = 3;	
		map->m_entrance.x = 0;
		map->m_entrance.y = map->size_y;
		map->m_exit.x = 0;
		map->m_exit.y = map->size_y;
		if(!is_exist_named(MON_MEIRIN)){
			map->monster_list.push_back(mapdummy_mon(MON_MEIRIN,0,coord_def(0,2)));
			set_exist_named(MON_MEIRIN);
		}
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
		return  "\
#######\
#..0..#\
###.###\
#.#+#.#\
#.....#\
#.....#\
###.###";
		break;
	}
}



char* youkai_last_vault_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		map->size_x = 8;
		map->size_y = 8;	
		map->m_entrance.x = 0;
		map->m_entrance.y = map->size_y;
		map->m_exit.x = 0;
		map->m_exit.y = map->size_y;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, 0);
		map->item_list.push_back(mapdummy_item(t,coord_def(0,0)));
		if(!is_exist_named(MON_AYA)){
			map->monster_list.push_back(mapdummy_mon(MON_AYA,0,coord_def(0,0)));
			set_exist_named(MON_AYA);
		}
		int mon_num_ = 10;
		while(mon_num_)
		{
			int hw_ = randA(1);
			coord_def c_(hw_?rand_int(-6,6):rand_int(5,6)*(randA(1)*2-1),hw_?rand_int(5,6)*(randA(1)*2-1):rand_int(-6,6));
			auto it = find_if(map->monster_list.begin(),map->monster_list.end(),
				[c_](mapdummy_mon &v)->bool{
					return v.pos == c_;
				}
			);
			if(it == map->monster_list.end())
			{
				map->monster_list.push_back(mapdummy_mon(randA(1)?MON_CROW_TENGU:randA(1)?MON_HANATACA_TENGU:MON_YAMABUSH_TENGU,0,c_));
				mon_num_--;
			}
		}
		return  "\
#################\
###...........###\
##.............##\
#...............#\
#...###.#####...#\
#...#.......#...#\
#...#.###.#.#...#\
#...#...#.#.....#\
#...#.##.##.#...#\
#.....#.#...#...#\
#...#.#.###.#...#\
#...#.......#...#\
#...#####.###...#\
#...............#\
##.............##\
###...........###\
#######...#######";	
		break;
	}
}





char* scarlet_last_vault_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		map->size_x = 8;
		map->size_y = 8;	
		map->m_entrance.x = 0;
		map->m_entrance.y = -map->size_y;
		map->m_exit.x = 0;
		map->m_exit.y = -map->size_y;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, 0);
		map->item_list.push_back(mapdummy_item(t,coord_def(0,-4)));
		if(!is_exist_named(MON_REMILIA)){
			map->monster_list.push_back(mapdummy_mon(MON_REMILIA,0,coord_def(0,-2)));
			set_exist_named(MON_REMILIA);
		}

		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_MAID,0,coord_def(-6,-5)));		
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_LIBRARIAN,0,coord_def(-4,-5)));
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN,0,coord_def(-2,-6)));
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN,0,coord_def(2,-6)));		
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_LIBRARIAN,0,coord_def(4,-5)));
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_MAID,0,coord_def(6,-5)));		
		map->monster_list.push_back(mapdummy_mon(MON_MAID_FAIRY,0,coord_def(-7,0)));
		map->monster_list.push_back(mapdummy_mon(MON_MAID_FAIRY,0,coord_def(-6,0)));
		map->monster_list.push_back(mapdummy_mon(MON_MAID_FAIRY,0,coord_def(7,0)));
		map->monster_list.push_back(mapdummy_mon(MON_MAID_FAIRY,0,coord_def(6,0)));		
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_MAID,0,coord_def(-6,5)));		
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_TEMP,0,coord_def(-1,7)));
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_TEMP,0,coord_def(1,7)));
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_MAID,0,coord_def(6,5)));	
		map->monster_list.push_back(mapdummy_mon(MON_CHUPARCABRA,0,coord_def(0,5)));			
		map->monster_list.push_back(mapdummy_mon(MON_VAMPIER_BAT,0,coord_def(-3,1)));	
		map->monster_list.push_back(mapdummy_mon(MON_VAMPIER_BAT,0,coord_def(3,1)));	


		return  "\
#######+++#######\
#...............#\
#...............#\
#.....#####.....#\
#...###...###...#\
#++##...#...##++#\
#..#.........#..#\
#..#.........#..#\
#..#.........#..#\
#..#.........#..#\
#..#.........#..#\
#++#####+#####++#\
#......#.#......#\
#...............#\
##.............##\
###...........###\
#################";	
		break;
	}
}