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
#include "event.h"
#include "evoke.h"



dungeon_tile_type randomTemple();

char* common_enter_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		map->size_x = 3;
		map->size_y = 3;	
		map->m_entrance.x = map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = -map->size_x;
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



char* common_base_pattern(int floor_, map_dummy* map)
{
	while(1)
	{

		switch(randA(37))
		{
		default:
		case 0:
			map->size_x = 5;
			map->size_y = 3;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = -2;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 2;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
###########\
+.###.....#\
#.###.###.#\
#.###.###.#\
#.###.###.#\
#.....###.+\
###########";
			break;
		case 1:
			{
			bool hw_ = randA(1);
			map->size_x = 4;
			map->size_y = 4;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
#.#.#.#.#\
.#.#.#.#.\
#.#.#.#.#\
.#.#.#.#.\
#.#.#.#.#\
.#.#.#.#.\
#.#.#.#.#\
.#.#.#.#.\
#.#.#.#.#";
			}
		case 2:
			{
				bool hw_ = randA(1);
				map->size_x = 5;
				map->size_y = 5;	
				map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				hw_ = randA(1);
				map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
				return  "\
...........\
...___.....\
..__~___...\
.._~_~~__..\
..__~~~__..\
.._~~[~~__.\
.._~~~~_~_.\
..__~_____.\
...___.....\
...........\
...........";
				break;		
			}
		case 3: //루나틱 타임
			{
				if(is_exist_named(MON_CLOWNPIECE))
					break;
				if(floor_ < 9 || floor_ > 15)
					break;
				map->size_x = 6;
				map->size_y = 5;	
				map->m_entrance.x = 0;
				map->m_entrance.y = map->size_y;
				map->m_exit.x = 0;
				map->m_exit.y = map->size_y;
				map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
				if(!is_exist_named(MON_CLOWNPIECE)){
					map->monster_list.push_back(mapdummy_mon(MON_CLOWNPIECE,0,coord_def(0,1)));
					set_exist_named(MON_CLOWNPIECE);
				}
				for(int i = 0; i<5 ; i++)
				{
					for(int j = 0; j<2; j++)
					{
						int id_ = (randA(5)==0?MON_FAIRY_RED_COMMANDER:randA(1)?(randA(1)?MON_FAIRY_BLUE:MON_FAIRY_BLUE_MAGICIAN):(randA(1)?MON_FAIRY_GREEN:MON_FAIRY_GREEN_WARRIOR));
						map->monster_list.push_back(mapdummy_mon(id_,0,coord_def(5*(j*2-1),-4+i*2)));
					}
				}
				map->event_list.push_back(mapdummy_event(EVL_LUNATICTIME,coord_def(0,-4),EVT_SIGHT));
				return  "\
#############\
#.#.......#.#\
######+######\
#.#.......#.#\
###.......###\
#.#..###..#.#\
###..#.#..###\
#.#..###..#.#\
###.......###\
#.#.......#.#\
######+######";
				break;	
			}
		case 4:
			map->size_x = 8;
			map->size_y = 3;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = rand_int(-1,1);
			map->m_exit.x = map->size_x;
			map->m_exit.y = rand_int(-1,1);
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
#################\
~~~~~~~~~~~~~~~~~\
.................\
.................\
.................\
~~~~~~~~~~~~~~~~~\
#################";
			break;
		case 5:
			{
				bool hw_ = randA(1);
				map->size_x = 2;
				map->size_y = 2;	
				map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				hw_ = randA(1);
				map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
				return  "\
.....\
.$$$.\
.$$$.\
.$$$.\
.....";			
			}
		case 6: //풀뿌리 요괴 네트워크
			{
				if(!((floor_ >= 10 && floor_ <=MAX_DUNGEUN_LEVEL) ||
					(floor_ >= MISTY_LAKE_LEVEL && floor_ <=MISTY_LAKE_LAST_LEVEL) ||
					(floor_ >= EIENTEI_LEVEL && floor_ <=EIENTEI_LEVEL_LAST_LEVEL) ||
					(floor_ >= DEPTH_LEVEL && floor_ <=DEPTH_LAST_LEVEL)))
					break;
				if((is_exist_named(MON_WAKASAGI) || (is_exist_named(MON_KEGERO) && is_exist_named(MON_SEKIBANKI))))
					break;
				bool hw_ = randA(1);
				map->size_x = 3;
				map->size_y = 3;	
				map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				hw_ = randA(1);
				map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
				if(!is_exist_named(MON_WAKASAGI)){
					map->monster_list.push_back(mapdummy_mon(MON_WAKASAGI,0,coord_def(0,2)));
					set_exist_named(MON_WAKASAGI);
				}
				if(!is_exist_named(MON_KEGERO)){
					map->monster_list.push_back(mapdummy_mon(MON_KEGERO,0,coord_def(0,0)));
					set_exist_named(MON_KEGERO);
				}
				else if(!is_exist_named(MON_SEKIBANKI)){
					map->monster_list.push_back(mapdummy_mon(MON_SEKIBANKI,0,coord_def(0,0)));
					set_exist_named(MON_SEKIBANKI);
				}

				return  "\
.......\
.~~~~~.\
.~...~.\
.~...~.\
.~...~.\
.~~~~~.\
.......";			
			}
		case 7: //쿄코미스치 콘서트
			{
				if(floor_ < 4)
					break;
				if(is_exist_named(MON_KYOUKO) || is_exist_named(MON_MISTIA))
					break;
				map->size_x = 4;
				map->size_y = 3;	
				map->m_entrance.x = 0;
				map->m_entrance.y = map->size_y;
				map->m_exit.x = 0;
				map->m_exit.y = map->size_y;
				map->flag = FLAG_NO_STAIR;
				if(!is_exist_named(MON_KYOUKO)){
					map->monster_list.push_back(mapdummy_mon(MON_KYOUKO,0,coord_def(-1,-1)));
					set_exist_named(MON_KYOUKO);
				}
				if(!is_exist_named(MON_MISTIA)){
					map->monster_list.push_back(mapdummy_mon(MON_MISTIA,0,coord_def(1,-1)));
					set_exist_named(MON_MISTIA);
				}

				return  "\
$$$$$$$$$\
$$.....$$\
$...$...$\
$.......$\
$.......$\
$$.....$$\
$$$...$$$";			
			}
		case 8:
			map->size_x = 2;
			map->size_y = 5;	
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = -map->size_y;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
##.##\
##.##\
##.##\
##.##\
##.##\
##.##\
##.##\
##.##\
##.##\
##.##\
##.##";
			break;
		case 9: //코가사 급습
			{
				map->size_x = 2;
				map->size_y = 2;	
				map->m_entrance.x = map->size_x;
				map->m_entrance.y = -map->size_y;
				map->m_exit.x = -map->size_x;
				map->m_exit.y = map->size_y;
				if(!is_exist_named(MON_KOGASA) && (floor_ >= 1 && floor_ <= 4)){
					map->event_list.push_back(mapdummy_event(EVL_KOGASA,coord_def(0,0),EVT_APPROACH_SMALL));
					set_exist_named(MON_KOGASA);
				}
				return  "\
####.\
#....\
#...#\
#...#\
..###";			
			}
		case 10: //요정대전쟁
			if(floor_ < 5)
				break;
			if(is_exist_named(MON_SUNNY)|| is_exist_named(MON_CIRNO))
			{
				break;
			}
			map->size_x = 6;
			map->size_y = 5;	
			map->m_entrance.x = 0;
			map->m_entrance.y =  map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			if(!is_exist_named(MON_CIRNO)){
				map->monster_list.push_back(mapdummy_mon(MON_CIRNO,M_FLAG_NETURALY,coord_def(-3,-1)));
				set_exist_named(MON_CIRNO);
			}
			if(!is_exist_named(MON_SUNNY)){
				map->monster_list.push_back(mapdummy_mon(MON_STAR,0,coord_def(3,1)));
				map->monster_list.push_back(mapdummy_mon(MON_LUNAR,0,coord_def(3,0)));
				map->monster_list.push_back(mapdummy_mon(MON_SUNNY,0,coord_def(2,1)));
				set_exist_named(MON_SUNNY);
			}
			map->event_list.push_back(mapdummy_event(EVL_NOISE,coord_def(0,0),EVT_SIGHT));
			return  "\
#############\
#...........#\
#.====+====.#\
#.=.......=.#\
#.=.......=.#\
#.=.......=.#\
#.=.......=.#\
#.=========.#\
#...........#\
#...........#\
######+######";
			break;
		case 11:
			map->size_x = 4;
			map->size_y = 3;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = 0;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 0;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
#########\
##.....##\
#...#...#\
...###...\
#...#...#\
##.....##\
#########";
			break;
		case 12:
			{
			map->size_x = 3;
			map->size_y = 3;	
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
.......\
...$...\
...$...\
.$$$$$.\
...$...\
...$...\
.......";
			break;
			}
		case 13:
			map->size_x = 4;
			map->size_y = 4;	
			map->m_entrance.x = 0;
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
####.####\
#.#.#.#.#\
##.....##\
#.......#\
##.....##\
#.......#\
##.....##\
#.#.#.#.#\
####.####";
			break;
		case 14:
			map->size_x = 4;
			map->size_y = 6;	
			map->m_entrance.x = rand_int(-3,-1);
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = rand_int(1,3);
			map->m_exit.y = map->size_y;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
#...#####\
##...####\
###...###\
####...##\
#####...#\
####...##\
###...###\
##...####\
#...#####\
##...####\
###...###\
####...##\
#####...#";
			break;
		case 15:
			{
			bool hw_ = randA(1);
			map->size_x = 6;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->monster_list.push_back(mapdummy_mon(MON_REIMUYUKKURI,0,coord_def(3,-1)));	
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
..[.[........\
...[[...####.\
........#..#.\
..~~~...##+#.\
.~~~~~.......\
..~~~...[[...\
.............";
			break;
			}
		case 16:
			map->size_x = 4;
			map->size_y = 4;	
			map->m_entrance.x = 0;
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = -map->size_y;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
####+####\
#.......#\
#.......#\
#.......#\
####....#\
#..#....#\
#..+....#\
#..#....#\
#########";
			break;
		case 17:
			{
			map->size_x = 3;
			map->size_y = 3;	
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
.......\
.#+###.\
.#.+.+.\
.###+#.\
.+.+.#.\
.###+#.\
.......";
			break;
			}
		case 18:
			map->size_x = 4;
			map->size_y = 3;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = 0;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 0;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
#########\
#.......#\
#.$$$$$.#\
..$......\
#.$$$$$.#\
#.......#\
#########";
			break;
		case 19:
			map->size_x = 7;
			map->size_y = 3;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = rand_int(-1,1);
			map->m_exit.x = map->size_x;
			map->m_exit.y = rand_int(-1,1);
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
###############\
....=.....=....\
.=..=..=..=..=.\
.=.....=.....=.\
.=..=..=..=..=.\
....=.....=....\
###############";
			break;
		case 20: //보탑을 찾은 나즈린
			{
			if(floor_ < 7)
				break;
			if(is_exist_named(MON_NAZRIN))
				break;
			map->size_x = 4;
			map->size_y = 4;	
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			if(!is_exist_named(MON_NAZRIN)){
				map->monster_list.push_back(mapdummy_mon(MON_NAZRIN,0,coord_def(0,-2)));
				set_exist_named(MON_NAZRIN);
			}
			
			item_infor t;
			makeitem(ITM_MISCELLANEOUS, 0, &t, EVK_PAGODA);
			map->item_list.push_back(mapdummy_item(t,coord_def(0,0)));		

			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			return  "\
#########\
#.......#\
#.......#\
#..===..#\
#..=.=..#\
#..===..#\
#.......#\
#.......#\
####+####";
			break;
			}
		case 21: //공포의 쿄코
			if(!(floor_ >= 3 && floor_ <= 5))
				break;
			if(is_exist_named(MON_KYOUKO))
				break;
			map->size_x = 4;
			map->size_y = 7;	
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			if(!is_exist_named(MON_KYOUKO)){
				map->event_list.push_back(mapdummy_event(EVL_KYOKO,coord_def(0,0),EVT_SIGHT));
				set_exist_named(MON_KYOUKO);
			}
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			return  "\
#########\
#$$$$$$$#\
#$$...$$#\
#$.....$#\
#$.....$#\
#$$...$$#\
###...###\
###...###\
###...###\
###...###\
###...###\
###...###\
###...###\
###...###\
####+####";
			break;
		case 22:
			{
			if(floor_ > 14)
				break;
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
.......\
..~~~..\
.~~~~~.\
.~~~~~.\
.~~~~~.\
..~~~..\
.......";
			break;
			}
		case 23:
			{
			if(floor_ > 14)
				break;
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 2;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->flag = FLAG_NO_ITEM;
			return  "\
.......\
.$$$$$.\
.$iii$.\
.$===$.\
.......";
			break;
			}
		case 24:
			{
			if(floor_ > 14)
				break;
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
...#...\
...#...\
...#...\
###+###\
...#...\
...#...\
...#...";
			break;
			}
		case 25:
			{
			if(floor_ > 14)
				break;
			bool hw_ = randA(1);
			map->size_x = 5;
			map->size_y = 4;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			return  "\
...........\
..~~~~~~~..\
..~~~~~~~..\
.~~~..~~~~.\
.~~~....~~.\
.~~~~..~~~.\
..~~~~~~~..\
..~~~~~~~..\
...........";
			break;
			}
		case 26: //UFO그리기
			{
			if(floor_ > 14)
				break;
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 2;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);

			
			int id_ = MON_RED_UFO;
			map->monster_list.push_back(mapdummy_mon(id_,0,coord_def(-1,0)));
			map->monster_list.push_back(mapdummy_mon(id_,0,coord_def(0,0)));
			map->monster_list.push_back(mapdummy_mon(id_,0,coord_def(1,0)));
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			return  "\
.......\
.=====.\
.=...=.\
.=====.\
.......";
			break;
			}
		case 27: //도망쳐 페어리
			if(!(floor_ >= DEPTH_LEVEL && floor_ <= DEPTH_LAST_LEVEL))
				break;
			if(is_exist_named(MON_SUNNY))
			{
				break;
			}
			map->size_x = 3;
			map->size_y = 2;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = 0;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 0;
			if(!is_exist_named(MON_SUNNY)){
				map->event_list.push_back(mapdummy_event(EVL_RUN_FAIRY,coord_def(0,0),EVT_SIGHT));
				set_exist_named(MON_SUNNY);
				set_exist_named(MON_STAR);
				set_exist_named(MON_LUNAR);
			}
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			return  "\
#######\
#.....#\
+.....+\
#.....#\
#######";
			break;
		case 28: //홍마관 책 트랩
			{
			if(!(floor_ >= SCARLET_LEVEL && floor_ <= SCARLET_LEVEL_LAST_LEVEL))
				break;
			
			map->size_x = 4;
			map->size_y = 3;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = 0;
			map->m_exit.x = -map->size_x;
			map->m_exit.y = 0;

			map->event_list.push_back(mapdummy_event(EVL_SCALET_TRAP,coord_def(1,0),EVT_ABOVE));
			map->monster_list.push_back(mapdummy_mon(MON_GOLEM,0,coord_def(-1,-2)));
			map->monster_list.push_back(mapdummy_mon(MON_GOLEM,0,coord_def(-3,-2)));
			map->monster_list.push_back(mapdummy_mon(MON_GOLEM,0,coord_def(-1,2)));
			map->monster_list.push_back(mapdummy_mon(MON_GOLEM,0,coord_def(-3,2)));
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			item_infor t;
			makeitem(ITM_BOOK, 0, &t, -1);
			map->item_list.push_back(mapdummy_item(t,coord_def(3,0)));	
			return  "\
#########\
#.#.#####\
#########\
........#\
#########\
#.#.#####\
#########";
			break;
			}
		case 29: //요괴의산 수족관
			{
			if(!(floor_ >= YOUKAI_MOUNTAIN_LEVEL && floor_ <= YOUKAI_MOUNTAIN_LAST_LEVEL))
				break;	

			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			
			if(!is_exist_named(MON_WAKASAGI)){
				map->monster_list.push_back(mapdummy_mon(MON_WAKASAGI,0,coord_def(0,0)));
				set_exist_named(MON_WAKASAGI);
			}
			else
			{
				map->monster_list.push_back(mapdummy_mon(MON_NESI,0,coord_def(0,0)));

			}
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			return  "\
.......\
.=====.\
.=~~~=.\
.=~~~=.\
.=~~~=.\
.=====.\
.......";
			break;
			}
		case 30: //코가사 타임
			{
				if(is_exist_named(MON_KOGASA))
					break;
				if(floor_ < 5 || floor_ > 12)
					break;
				map->size_x = 6;
				map->size_y = 5;	
				map->m_entrance.x = 0;
				map->m_entrance.y = map->size_y;
				map->m_exit.x = 0;
				map->m_exit.y = map->size_y;
				map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
				if(!is_exist_named(MON_KOGASA)){
					map->monster_list.push_back(mapdummy_mon(MON_KOGASA,0,coord_def(0,1)));
					set_exist_named(MON_KOGASA);
				}
				for(int i = 0; i<5 ; i++)
				{
					for(int j = 0; j<2; j++)
					{
						if(randA(2)==1)
							map->monster_list.push_back(mapdummy_mon(MON_BAKEKASA,0,coord_def(5*(j*2-1),-4+i*2)));
					}
				}
				map->event_list.push_back(mapdummy_event(EVL_KOGASATIME,coord_def(0,-4),EVT_SIGHT));
				return  "\
#############\
#.#.......#.#\
######+######\
#.#.......#.#\
###.......###\
#.#..###..#.#\
###..#.#..###\
#.#..###..#.#\
###.......###\
#.#.......#.#\
######+######";
				break;	
			}
		case 31:
			{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
.......\
.#.#.#.\
.......\
.#.#.#.\
.......\
.#.#.#.\
.......";
			break;
			}
		case 32:
			{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
#######\
#.....#\
#.....#\
#.....#\
#.....#\
#.&.&.#\
###.###";
			break;
			}
		case 33:
			{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 2;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = 0;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 0;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
#######\
EEEEEEE\
.......\
EEEEEEE\
#######";
			break;
			}
		case 34:
			{
			bool hw_ = randA(1);
			map->size_x = 2;
			map->size_y = 3;	
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = -map->size_y;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			return  "\
#E.E#\
#E.E#\
#E.E#\
#E.E#\
#E.E#\
#E.E#\
#E.E#";
			break;
			}
		case 35:
			{
				bool hw_ = randA(1);
				map->size_x = 2;
				map->size_y = 3;	
				map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				hw_ = randA(1);
				map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
				return  "\
.....\
.~~~.\
.~~~.\
.~~~.\
..&..\
.....\
.....";			
			}
		case 36: //숨겨진 보물창고
			{
				if(floor_ < 5)
					break;
				map->size_x = 4;
				map->size_y = 2;
				map->m_entrance.x = 0;
				map->m_entrance.y = -map->size_y;
				map->m_exit.x = 0;
				map->m_exit.y = -map->size_y;
				map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
				for(int i =0;i<3;i++)
				{
					item_infor t;
					makeitem(ITM_BOOK, 0, &t, -1);
					map->item_list.push_back(mapdummy_item(t,coord_def(rand_int(-2,2),rand_int(-1,0))));	
				}

				return  "\
####&####\
#E.....E#\
#E.....E#\
#EEEEEEE#\
#########";			
			}
		case 37:
			{
				bool hw_ = randA(1);
				map->size_x = 2;
				map->size_y = 2;	
				map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				hw_ = randA(1);
				map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
				map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
				/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
				map->sp_tile_list.push_back(randomTemple());
				return  "\
.....\
.###.\
.#0#.\
.#&#.\
.....";			
			}
		}
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
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
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
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
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
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
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
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
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
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
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
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
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
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
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
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
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
char* yukkuri_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_YUKKURI_STAIR);
	return common_enter_pattern(map);
}
char* depth_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_DEPTH_STAIR);
	return common_enter_pattern(map);
}
char* dream_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_DREAM_STAIR);
	return common_enter_pattern(map);
}
char* pandemonium_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_PANDEMONIUM_STAIR);
	return common_enter_pattern(map);
}
char* hakurei_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_HAKUREI_STAIR);
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
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
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
	switch(randA(1))
	{
	default:
	case 0:
		{
		map->size_x = 8;
		map->size_y = 8;	
		map->m_entrance.x = 0;
		map->m_entrance.y = map->size_y;
		map->m_exit.x = 0;
		map->m_exit.y = map->size_y;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, RUNE_YOUKAI_MOUNTAIN);
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
#...#.$$$i$.#...#\
#...#.ii$i$.....#\
#...#.$$.$$.#...#\
#.....$i$ii.#...#\
#...#.$i$$$.#...#\
#...#.......#...#\
#...#####.###...#\
#...............#\
##.............##\
###...........###\
#######...#######";	
		break;
		}
	case 1:
		{
		bool hw_ = randA(1);
		map->size_x = 8;
		map->size_y = 8;	
		map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
		map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
		map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, RUNE_YOUKAI_MOUNTAIN);
		map->item_list.push_back(mapdummy_item(t,coord_def(5*(randA(1)*2-1),5*(randA(1)*2-1))));

		if(!is_exist_named(MON_NITORI)){
			map->monster_list.push_back(mapdummy_mon(MON_NITORI,0,coord_def(0,0)));
			set_exist_named(MON_NITORI);
		}
		
		map->monster_list.push_back(mapdummy_mon(MON_SANPEI_FIGHTER,0,coord_def(4,-3)));	
		map->monster_list.push_back(mapdummy_mon(MON_NESI,0,coord_def(3,4)));		
		map->monster_list.push_back(mapdummy_mon(MON_SANPEI_FIGHTER,0,coord_def(-4,3)));		
		map->monster_list.push_back(mapdummy_mon(MON_NESI,0,coord_def(-3,-4)));	


		int mon_num_ = 6;
		while(mon_num_)
		{
			coord_def c_(rand_int(-4,4),rand_int(-4,4));
			auto it = find_if(map->monster_list.begin(),map->monster_list.end(),
				[c_](mapdummy_mon &v)->bool{
					return v.pos == c_;
				}
			);
			if(it == map->monster_list.end())
			{
				map->monster_list.push_back(mapdummy_mon(randA(2)?MON_KATPA_SPEAR:MON_KATPA_WATER_WIZARD,0,c_));
				mon_num_--;
			}
		}
		return  "\
.................\
.................\
..$$$$.....$$$$..\
..$.i$$$+$$$i.$..\
..$i.~~~.~~~.i$..\
..$$~.~~.~~.~$$..\
...$~~.~.~.~~$...\
...$~~~.~.~~~$...\
...+...~~~...+...\
...$~~~.~.~~~$...\
...$~~.~.~.~~$...\
..$$~.~~.~~.~$$..\
..$i.~~~.~~~.i$..\
..$.i$$$+$$$i.$..\
..$$$$.....$$$$..\
.................\
.................";	
		break;
		}
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
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, RUNE_SCARLET);
		map->item_list.push_back(mapdummy_item(t,coord_def(0,-4)));
		if(!is_exist_named(MON_REMILIA)){
			map->monster_list.push_back(mapdummy_mon(MON_REMILIA,0,coord_def(0,-2)));
			set_exist_named(MON_REMILIA);
		}

		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_MAID,0,coord_def(-6,-5)));		
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_LIBRARIAN,0,coord_def(-4,-5)));
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_LIBRARIAN,0,coord_def(4,-5)));
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_MAID,0,coord_def(6,-5)));				
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_TEMP,0,coord_def(-1,7)));
		map->monster_list.push_back(mapdummy_mon(MON_HOBGOBRIN_TEMP,0,coord_def(1,7)));
		map->monster_list.push_back(mapdummy_mon(MON_CHUPARCABRA,0,coord_def(0,5)));			
		map->monster_list.push_back(mapdummy_mon(MON_VAMPIER_BAT,0,coord_def(-3,1)));	
		map->monster_list.push_back(mapdummy_mon(MON_VAMPIER_BAT,0,coord_def(3,1)));	


		return  "\
#######+++#######\
#...............#\
#...............#\
#.....$$$$$.....#\
#...$$$i.i$$$...#\
#++$$iii$iii$$++#\
#..$.........$..#\
#..$.........$..#\
#..$.........$..#\
#..$.........$..#\
#..$.........$..#\
#++$$$$$+$$$$$++#\
#......$.$......#\
#...............#\
##.............##\
###...........###\
#################";	
		break;
	}
}

char* eientei_vault_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		{
		
		bool hw_ = randA(1);
		map->size_x = 35;
		map->size_y = 9;	
		map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
		map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
		map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);

		map->flag = FLAG_NO_STAIR | FLAG_NO_MONSTER | FLAG_NO_ITEM;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, RUNE_EIENTEI);
		map->item_list.push_back(mapdummy_item(t,coord_def(28,2)));		
		//map->event_list.push_back(mapdummy_event(22,coord_def(28,2),EVT_SIGHT));




		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-22,-6)));		
		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-20,-6)));		
		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-18,-6)));		
		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-16,-6)));		
		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-14,-6)));		
		
		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-22,-2)));		
		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-20,-2)));		
		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-18,-2)));		
		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-16,-2)));		
		map->monster_list.push_back(mapdummy_mon(randA(4)==0?MON_RABIT_BOMB:randA(2)?MON_RABIT_SPEAR:MON_RABIT_MAGIC,0,coord_def(-14,-2)));	

		
		if(!is_exist_named(MON_UDONGE)){
			map->monster_list.push_back(mapdummy_mon(MON_UDONGE,0,coord_def(-6,-3)));
			set_exist_named(MON_UDONGE);
		}		
		if(!is_exist_named(MON_KAGUYA)){
			map->monster_list.push_back(mapdummy_mon(MON_KAGUYA,0,coord_def(23,1)));
			set_exist_named(MON_KAGUYA);
		}



		return  "\
.......................................................................\
.......................................................................\
.....$$$$$$$$$$$$$$$$$$$$==$$$$$$$$$==$$$$$$$$$$$$$$$$$$$$$$$$$$$......\
.....$,,,,,,$i$i$i$i$i$,,,,,,,,,,,,,,,,,$,,,,,,,,,,,,,,,,,,,,,,,$......\
.....$,,,,,,$+$+$+$+$+$,,,,,,,,,,,,,,,,,$,,,,,,,,,,,,$$$$$$$$$$+$......\
.....$,,,,,,+,,,,,,,,,+,,,,,,,,,,,,,,,,,+,,,,,,,,,,,,$,,,,,,,,,,$......\
.....$,,,,,,$+$+$+$+$+$,,,,,,,,,,,,,,,,,$,,,,,,,,,,,,$,,,,,,,,,,$......\
.....$,,,,,,$i$i$i$i$i$,,,,,,,,,,,,,,,,,$,,,,,,,,,,,,$+$$$$$$$$$$......\
.....$$+$$$$$$$$$$$$$$$$$==$$$$$$$$$==$$$$$$$$$$$$$$$$,,,,,,,,,,$......\
.....$,,,,,,,,,,$....................................$,,,,,,,,,,$......\
.....$,,,,,,,,,,$........................[...........$,,,,,,,,,,$......\
.....$,,,,,,,,,,$.....[[........~~~~~~~.......[......$,,,,,,,,,,$......\
.....$$$$$++$$$$$..............~~~~~~~~~.............$$$$$$$$$$$$......\
...........................[..~~~~~~~~~~~..............................\
...................[.....[.....~~~~~~~~~.............[[................\
...................[............~~~~~~~......[.........................\
.................................................[.....................\
.................................[.....................................\
.......................................................................";
		break;
		}
	}
}

char* pandemonium_baykuren_last_vault_pattern(map_dummy* map)
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
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, RUNE_PANDEMONIUM_MAGIC);
		map->item_list.push_back(mapdummy_item(t,coord_def(2,-3)));
		map->sp_tile_list.push_back(DG_TEMPLE_BYAKUREN);
		if(!is_exist_named(MON_NAZRIN)){
			map->monster_list.push_back(mapdummy_mon(MON_NAZRIN,0,coord_def(-5,6)));
			set_exist_named(MON_NAZRIN);
		}
		if(!is_exist_named(MON_ICHIRIN)){
			map->monster_list.push_back(mapdummy_mon(MON_ICHIRIN,0,coord_def(-5,-5)));
			set_exist_named(MON_ICHIRIN);
		}
		int mon_num_ = 10;
		int yugen_ = 2;
		while(mon_num_)
		{
			coord_def c_(rand_int(-2,2),rand_int(-1,1));
			auto it = find_if(map->monster_list.begin(),map->monster_list.end(),
				[c_](mapdummy_mon &v)->bool{
					return v.pos == c_;
				}
			);
			if(it == map->monster_list.end())
			{
				map->monster_list.push_back(mapdummy_mon((yugen_--)>0?MON_YUUGENMAGAN:randA(1)?MON_ELIS:MON_SARA,0,c_));
				mon_num_--;
			}
		}
		return  "\
$$$$$$$$$$$$$$$$$\
$$$...........$$$\
$$.............$$\
$.....$$$$$$....$\
$....$$....$$...$\
$...$$...$..$...$\
$...$....$$.$...$\
$...$...0...$...$\
$...$.......$...$\
$...$......$$...$\
$...$.....$$$...$\
$...$...........$\
$...$$..........$\
$....$$$........$\
$$.....$$$.....$$\
$$$......$$...$$$\
$$$$$$$...$$$$$$$";	
		break;
	}
}





char* pandemonium_ice_last_vault_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		map->size_x = 10;
		map->size_y = 7;	
		map->m_entrance.x = 0;
		map->m_entrance.y = map->size_y;
		map->m_exit.x = 0;
		map->m_exit.y = -map->size_y;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, RUNE_PANDEMONIUM_ICE);
		map->item_list.push_back(mapdummy_item(t,coord_def(0,-1)));
		map->monster_list.push_back(mapdummy_mon(MON_YUKI,0,coord_def(-3,-1)));	
		map->monster_list.push_back(mapdummy_mon(MON_YUKI,0,coord_def(-3,1)));	
		map->monster_list.push_back(mapdummy_mon(MON_MAI,0,coord_def(3,-1)));	
		map->monster_list.push_back(mapdummy_mon(MON_MAI,0,coord_def(3,1)));		
	
		return  "\
##~~~~~~~..~~~~~~~~##\
#~~~~~~~.~~~~~~~~~~~#\
~~~~~~~.~~~~~~~~~~~~~\
~~~~~~.~~~~~~~~~~~~~~\
~~~~~...........~~~~~\
~~~~..$$$$$$$$$..~~~~\
~~~~.$$..i.i..$$.~~~~\
~~~~.$..iiiii..$.~~~~\
~~~~.$$..iii..$$.~~~~\
~~~~..$$$$+$$$$..~~~~\
~~~~~...........~~~~~\
~~~~~~~~~~~~~~.~~~~~~\
~~~~~~~~~~~~~.~~~~~~~\
#~~~~~~~~~~~.~~~~~~~#\
##~~~~~~~~..~~~~~~~##";
		break;
	}
}



char* pandemonium_shinki_last_vault_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		map->size_x = 8;
		map->size_y = 10;	
		map->m_entrance.x = 0;
		map->m_entrance.y = map->size_y;
		map->m_exit.x = 0;
		map->m_exit.y = map->size_y;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, RUNE_PANDEMONIUM_SHINKI);
		map->item_list.push_back(mapdummy_item(t,coord_def(0,-9)));
		map->sp_tile_list.push_back(DG_TEMPLE_SHINKI);
		if(!is_exist_named(MON_YUMEKO)){
			map->monster_list.push_back(mapdummy_mon(MON_YUMEKO,0,coord_def(0,-4)));
			set_exist_named(MON_YUMEKO);
		}
		map->monster_list.push_back(mapdummy_mon(MON_YUKI,0,coord_def(-3,-1)));	
		map->monster_list.push_back(mapdummy_mon(MON_MAI,0,coord_def(3,-1)));	
		int mon_num_ = 6;
		while(mon_num_)
		{
			int hw_ = randA(1);
			coord_def c_(hw_?rand_int(4,7):rand_int(-4,-7),rand_int(6,8));
			auto it = find_if(map->monster_list.begin(),map->monster_list.end(),
				[c_](mapdummy_mon &v)->bool{
					return v.pos == c_;
				}
			);
			if(it == map->monster_list.end())
			{
				map->monster_list.push_back(mapdummy_mon(randA(1)?MON_SARA:MON_LUIZE,0,c_));
				mon_num_--;
			}
		}
		return  "\
$$$$$$$$$$$$$$$$$\
$.##iiii.iiii##.$\
$...##iiiii##...$\
$#....$$$$$....#$\
$.##.$$.0.$$.##.$\
$...$$.....$$...$\
$.##.........##.$\
$#..$$.....$$..#$\
$....$$$.$$$....$\
$..=...=.=...=..$\
$..=...=.=...=..$\
$..=...=.=...=..$\
$..=...=.=...=..$\
$...=.=...=.=...$\
$...=.=...=.=...$\
$...=.=...=.=...$\
$....=.....=....$\
$....=.....=....$\
$....=.....=....$\
$...=.=...=.=...$\
$$$$=.=...=.=$$$$";	
		break;
	}
}




	
char* yukkuri_last_vault_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		bool hw_ = randA(1);
		map->size_x = 15;
		map->size_y = 13;
		map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
		map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
		map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);

		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, RUNE_YUKKURI);
		map->item_list.push_back(mapdummy_item(t,coord_def(3,3)));
		int mon_num_ = 5;
		while(mon_num_)
		{
			coord_def c_(rand_int(2,-2),rand_int(1,-4));
			auto it = find_if(map->monster_list.begin(),map->monster_list.end(),
				[c_](mapdummy_mon &v)->bool{
					return v.pos == c_;
				}
			);
			if(it == map->monster_list.end())
			{
				map->monster_list.push_back(mapdummy_mon(randA(1)?MON_ALICEYUKKURI:MON_YOUMUYUKKURI,0,c_));
				mon_num_--;
			}
		}
		return  "\
...............................\
...............................\
...............................\
...............................\
...............................\
...............................\
.........$...........$.........\
..........$.........$..........\
...........$.......$...........\
........$$$$$.....$$$$$........\
.......$$iii$.....$iii$$.......\
......$.$iii$.....$iii$.$......\
......$.$iii$.....$iii$.$......\
.........$$$$.....$$$$.........\
...............................\
...........$$$$$$$$$...........\
............$iiiii.$...........\
............$iiiiii$...........\
.............$iiiii$...........\
..............$$$$$............\
...............................\
...............................\
...............................\
...............................\
...............................\
...............................\
...............................";	
		break;
	}
}









char* moon_last_vault_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		bool hw_ = randA(1);
		map->size_x = 7;
		map->size_y = 7;
		map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
		map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
		map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);

		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		item_infor t;
		makeitem(ITM_GOAL, 0, &t, RUNE_MOON);
		map->item_list.push_back(mapdummy_item(t,coord_def(5*(randA(1)*2-1),5*(randA(1)*2-1))));
		if(!is_exist_named(MON_YORIHIME)){
			map->monster_list.push_back(mapdummy_mon(MON_YORIHIME,0,coord_def(1,0)));
			set_exist_named(MON_YORIHIME);
		}
		if(!is_exist_named(MON_TOYOHIME)){
			map->monster_list.push_back(mapdummy_mon(MON_TOYOHIME,0,coord_def(-1,0)));
			set_exist_named(MON_TOYOHIME);
		}
		int mon_num_ = 4;
		while(mon_num_)
		{
			coord_def c_(rand_int(4,-4),rand_int(2,-2));
			auto it = find_if(map->monster_list.begin(),map->monster_list.end(),
				[c_](mapdummy_mon &v)->bool{
					return v.pos == c_;
				}
			);
			if(it == map->monster_list.end())
			{
				map->monster_list.push_back(mapdummy_mon(MON_MOON_RABIT_ELITE,0,c_));
				mon_num_--;
			}
		}
		return  "\
...............\
.$$$.......$$$.\
.$.$$$$+$$$$.$.\
.$$.........$$.\
..$.........$..\
..$...iii...$..\
..$..iiiii..$..\
..+..iiiii..+..\
..$..iiiii..$..\
..$...iii...$..\
..$.........$..\
.$$.........$$.\
.$.$$$$+$$$$.$.\
.$$$.......$$$.\
...............";	
		break;
	}
}




	
char* subterranean_last_vault_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		{
			bool hw_ = randA(1);
			map->size_x = 10;
			map->size_y = 10;
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);

			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			int item_ = randA(2);
			{
				item_infor t;
				makeitem(ITM_GOAL, 0, &t, RUNE_SUBTERRANEAN);
				map->item_list.push_back(mapdummy_item(t,item_==0?coord_def(0,6):(item_==1?coord_def(5,-3):coord_def(-5,-3))));		
			}
			{
				item_infor t;
				makeitem(ITM_POTION, 0, &t);
				map->item_list.push_back(mapdummy_item(t,item_==2?coord_def(0,6):(item_==0?coord_def(5,-3):coord_def(-5,-3))));
			}
			{
				item_infor t;
				makeitem(ITM_POTION, 0, &t);
				map->item_list.push_back(mapdummy_item(t,item_==1?coord_def(0,6):(item_==2?coord_def(5,-3):coord_def(-5,-3))));
			}

			if(!is_exist_named(MON_UTSUHO)){
				map->monster_list.push_back(mapdummy_mon(MON_UTSUHO,0,coord_def(0,0)));
				set_exist_named(MON_UTSUHO);
			}

			return  "\
.....................\
.......#######.......\
.....##.......##.....\
....#...........#....\
...#.$$$.....$$$.#...\
..#.$$i$$...$$i$$.#..\
..#.$iii$$.$$iii$.#..\
.#.$$.i..$.$..i.$$.#.\
.#.$ii....$....ii$.#.\
.#.$i....$.$....i$.#.\
.#.$$$$$$...$$$$$$.#.\
.#.......$.$.......#.\
.#......$.$.$......#.\
.#.....$$...$$.....#.\
..#...$$.....$$...#..\
..#..$$iiiiiii$$..#..\
...#.$$$ii.ii$$$.#...\
....#..$$$$$$$..#....\
.....##.......##.....\
.......#######.......\
.....................";	
		break;
		}
	}
}



char* hakurei_last_vault_pattern(map_dummy* map)
{
	switch(randA(0))
	{
	default:
	case 0:
		{
			map->size_x = 9;
			map->size_y = 9;
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = -2;
			map->m_exit.x = -map->size_x;
			map->m_exit.y = -2;

			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			{
				item_infor t;
				makeitem(ITM_ORB, 0, &t, 0);
				map->item_list.push_back(mapdummy_item(t,coord_def(-4,-2)));		
			}

			
			int mon_num_ = 2;
			while(mon_num_)
			{
				coord_def c_(rand_int(-1,-7),rand_int(0,5));
				auto it = find_if(map->monster_list.begin(),map->monster_list.end(),
					[c_](mapdummy_mon &v)->bool{
						return v.pos == c_;
					}
				);
				if(it == map->monster_list.end())
				{
					map->monster_list.push_back(mapdummy_mon(MON_EVIL_EYE_TANK,0,c_));
					mon_num_--;
				}
			}

			mon_num_ = 2;
			while(mon_num_)
			{
				coord_def c_(rand_int(1,7),rand_int(0,-5));
				auto it = find_if(map->monster_list.begin(),map->monster_list.end(),
					[c_](mapdummy_mon &v)->bool{
						return v.pos == c_;
					}
				);
				if(it == map->monster_list.end())
				{
					map->monster_list.push_back(mapdummy_mon(MON_EVIL_EYE_TANK,0,c_));
					mon_num_--;
				}
			}
			return  "\
#####$$$$$$$$$#####\
###$$$.......$$$###\
##$$...........$$##\
#$$.............$$#\
#$...............$#\
$$...............$$\
$..$$$$$..........$\
..$$...$$.........$\
$$$.....$$.......$$\
$$.......$.......$$\
$$.......$$.....$.$\
$.........$$...$$.$\
$..........$$$$$..$\
$$...............$$\
#$...............$#\
#$$.............$$#\
##$$...........$$##\
###$$$.......$$$###\
#####$$$$$$$$$#####";	
		break;
		}
	}
}