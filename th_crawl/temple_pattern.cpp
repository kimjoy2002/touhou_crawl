//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: temple_pattern.cpp
//
// 내용: 맵 패턴 저장소
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "map.h"
#include "throw.h"
#include "mon_infor.h"
#include "event.h"
#include "armour.h"

void WeaponMake(item_type type, int good_bad, item_infor* t, int pixed_type = -1);

dungeon_tile_type randomTemple()
{
	random_extraction<dungeon_tile_type> rand_;
	
	for(int i=0;i<GT_LAST;i++)
	{
		if(i != GT_SEIJA)
			rand_.push((dungeon_tile_type)(i+DG_TEMPLE_JOON_AND_SION));
	}
	
	return rand_.pop();
}


bool isGodTemple(int id_, god_type god_)
{
	switch(id_)
	{
	default: 
	case 0:
	case 1:
	case 2:
	case 5:
	case 6:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
		//공용 신
		return true;
	case 9:
	case 35:
		//뱌쿠렌
		return (god_ == GT_BYAKUREN);
	case 12:
		//스와코
		return (god_ == GT_SUWAKO);
	case 15:
		//스와코
		return (!is_exist_named(MON_CIRNO) && god_ == GT_SUWAKO);
	case 36:
		//카나코
		return (god_ == GT_KANAKO);
	case 14:
		//미노리코
		return (god_ == GT_MINORIKO);
	case 11:
		//신키
		return (god_ == GT_SHINKI);	
	case 13:
		//히나
		return (god_ == GT_HINA);			
	case 10:
		//에이린
		return (god_ == GT_EIRIN);		
	case 8:
		//사토리
		return (god_ == GT_SATORI);
		//복합 신
	case 3:
		return (!is_exist_named(MON_ORIN) || !is_exist_named(MON_DIEFAIRY) || !is_exist_named(MON_SAKI) )
			&& (god_ == GT_MINORIKO || god_ == GT_SHIZUHA);
	case 7:
		return (god_ != GT_MIMA && god_ != GT_SHINKI);
	case 4:
		return (god_ == GT_KANAKO || god_ == GT_SUWAKO);
	case 16:
		//유유코
		return !is_exist_named(MON_MISTIA) && (god_ == GT_YUYUKO);
	case 17:
		//시즈하
		return (god_ == GT_SHIZUHA);	
	case 18:
		//유기
		return (god_ == GT_YUUGI);
	case 19:
		//유카리
		return (god_ == GT_YUKARI);
	case 20:
		//조온시온
		return (god_ == GT_JOON_AND_SION);
	case 37:
		//릴리
		return (god_ == GT_LILLY);
	case 38:
		//미코
		return (god_ == GT_MIKO);
	case 39:
		//세이자
		return (god_ == GT_SEIJA);
	case 40:
		//오키나
		return (god_ == GT_OKINA);
	case 41:
		//순호
		return !is_exist_named(MON_CLOWNPIECE) && (god_ == GT_JUNKO);
	case 42:
		//미마
		return (god_ == GT_MIMA);
	case 43:
		//텐시
		return (god_ == GT_TENSI);
	case 44:
		//유유코
		return (god_ == GT_YUYUKO);
	}
}

int GetMaxAlter(){return 45;};


void makeAunnTemple(map_dummy* map, coord_def c)
{
	//아운은 랜덤하게 제단 생성 맵에 끼어들어서 그 지역을 수호한다.

	if (is_exist_named(MON_AUNN))
		return;
	if (randA(99) < 2) 
	{//확률 2% (그러나 실제로 신전은 8개정도 생기므로 대략 15%정도 확률로 아운이 등장한다.
		if (!is_exist_named(MON_AUNN)) {
			map->monster_list.push_back(mapdummy_mon(MON_AUNN, 0, c));
			set_exist_named(MON_AUNN);
		}
	}
}


const char* real_altar_pattern(map_dummy* map, int id_)
{
	switch(id_)
	{
	default:
	case 0: //전부
		map->size_x = 3;
		map->size_y = 3;	
		map->m_entrance.x = 0;
		map->m_entrance.y = -map->size_y;
		map->m_exit.x = 0;
		map->m_exit.y = -map->size_y;
		makeAunnTemple(map,coord_def(0, 0));
		map->name = "COMMON_ALTAR_DIAMOND";
		return  "\
###+###\
#..#..#\
#.#+#.#\
##+0+##\
#.#+#.#\
#..#..#\
#######";
	case 1: //전부
		map->size_x = 3;
		map->size_y = 1;	
		map->m_entrance.x = map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = map->size_x;
		map->m_exit.y = 0;
		makeAunnTemple(map, coord_def(0, 0));
		map->name = "COMMON_ALTAR_HORIZONTAL_PATH";
		return  "\
#######\
#0+....\
#######";
		break;
	case 2: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_PILLAR";
			return  "\
.......\
.#.#.#.\
.......\
.#.0.#.\
.......\
.#.#.#.\
.......";
			break;
		}
	case 3: //아키샌드
		{
			map->size_x = 3;
			map->size_y = 2;	
			map->m_entrance.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_exit.y = map->size_y;
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_MINORIKO);
			map->sp_tile_list.push_back(DG_TEMPLE_SHIZUHA);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			random_extraction<monster_index> rand_;
			if(!is_exist_named(MON_ORIN))
				rand_.push(MON_ORIN);
			if(!is_exist_named(MON_DIEFAIRY))
				rand_.push(MON_DIEFAIRY);
			if(!is_exist_named(MON_LUNASA))
				rand_.push(MON_LUNASA);
			if(!is_exist_named(MON_SAKI))
				rand_.push(MON_SAKI);

			if(rand_.GetSize() > 0) {
				monster_index unique_ = rand_.choice();
				map->monster_list.push_back(mapdummy_mon(unique_,M_FLAG_DECORATE,coord_def(0,-1)));
				set_exist_named(unique_);
			}
			else
			{
				map->monster_list.push_back(mapdummy_mon(MON_MOOK,M_FLAG_DECORATE,coord_def(0,-1)));
			}
			makeAunnTemple(map, coord_def(0, 1));
			map->name = "ALTAR_AKISAND";
			return  "\
#######\
#0=.=1#\
#.===.#\
#.....#\
#.....#";
			break;
		}
	case 4: //모리야 신전
		{
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_exit.y = map->size_y;
			map->sp_tile_list.clear();
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			map->sp_tile_list.push_back(randA(1)?DG_TEMPLE_KANAKO:DG_TEMPLE_SUWAKO);
			item_infor t;			
			WeaponMake(ITM_WEAPON_MACE, 0, &t, 1);
			map->item_list.push_back(mapdummy_item(t,coord_def(0,0)));
			makeitem((item_type)randA(ITM_ARMOR_BODY_ARMOUR_3), 0, &t, AMK_MIKO);
			map->item_list.push_back(mapdummy_item(t,coord_def(0,0)));
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "ALTAR_MORIYA";
			return  "\
#######\
#.###.#\
#.#0#.#\
#.....#\
#.#.#.#\
#.....#\
#.....#";
			break;
		}
	case 5: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			makeAunnTemple(map, coord_def(0, 2));
			map->name = "COMMON_ALTAR_SMALL_ROOM";
			return  "\
.......\
.......\
..###..\
..#0#..\
..#+#..\
.......\
.......";
			break;
		}
	case 6: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
						
			dungeon_tile_type god_tile = DG_FLOOR;
			if(map->sp_tile_list.size() > 0)
				god_tile = map->sp_tile_list[0];
			map->sp_tile_list.clear();
			random_extraction<dungeon_tile_type> rand_;
			random_extraction<dungeon_tile_type> rand_2;
			rand_.push(DG_GRAVE);
			rand_.push(DG_STATUE);
			rand_.push(DG_STATUE2);
			rand_.push(DG_SUN_FLOWER);
			rand_.push(DG_TREE);
			rand_.push(DG_LAVA);
			rand_.push(DG_SEA);
			rand_2.push(god_tile);
			rand_2.push(rand_.pop());
			rand_2.push(rand_.pop());
			rand_2.push(rand_.pop());
			map->sp_tile_list.push_back(rand_2.pop());
			map->sp_tile_list.push_back(rand_2.pop());
			map->sp_tile_list.push_back(rand_2.pop());
			map->sp_tile_list.push_back(rand_2.pop());
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_NSEW";
			return  "\
.......\
...1...\
.......\
.0...2.\
.......\
...3...\
.......";
			break;
		}
	case 7: //구작결계
		{
			map->size_x = 3;
			map->size_y = 2;	
			map->m_entrance.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_exit.y = map->size_y;
			map->sp_tile_list.push_back(DG_TEMPLE_MIMA);
			map->sp_tile_list.push_back(DG_TEMPLE_SHINKI);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			makeAunnTemple(map, coord_def(0, 1));
			map->name = "COMMON_ALTAR_OLDBORDER";
			return  "\
#######\
#.1.2.#\
#=====#\
#==0==#\
#.....#";
			break;
		}
	case 8: //사토리사육터
		{
			map->size_x = 6;
			map->size_y = 3;	
			map->m_entrance.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_exit.y = map->size_y;
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_SATORI);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			map->monster_list.push_back(mapdummy_mon(randA(2)==0?MON_WHITE_CAT:randA(1)?MON_BLACK_CAT:MON_ORANGE_CAT,M_FLAG_DECORATE,coord_def(-3,-1)));
			map->monster_list.push_back(mapdummy_mon(randA(2)==0?MON_WHITE_CAT:randA(1)?MON_BLACK_CAT:MON_ORANGE_CAT,M_FLAG_DECORATE,coord_def(-1,1)));
			map->monster_list.push_back(mapdummy_mon(MON_CROW,M_FLAG_DECORATE,coord_def(1,-1)));
			map->monster_list.push_back(mapdummy_mon(MON_CROW,M_FLAG_DECORATE,coord_def(3,1)));
			makeAunnTemple(map, coord_def(0, 3));
			map->name = "ALTAR_SAROTI_FARM";
			return  "\
#############\
#.=========.#\
#.=.....~~=.#\
#.=......~=.#\
#.=.......=.#\
#.=========.#\
#.....0.....#";
			break;
		}
	case 9: //뱌쿠렌 책 선물
		{
			bool hw_ = randA(1);
			map->size_x = 2;
			map->size_y = 1;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_BYAKUREN);
			item_infor t;			
			makeitem(ITM_BOOK, 0, &t, 0);
			map->item_list.push_back(mapdummy_item(t,coord_def(0,0)));
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "ALTAR_BYAKUREN_BOOK";
			return  "\
.....\
..0..\
.....";
			break;
		}
	case 10: //에이린 실험실
		{
			map->size_x = 3;
			map->size_y = 2;	
			map->m_entrance.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_exit.y = -map->size_y;
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_EIRIN);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			item_infor t;			
			makeitem(ITM_POTION, -1, &t);
			map->item_list.push_back(mapdummy_item(t,coord_def(-2,1)));
			makeitem(ITM_POTION, -1, &t);
			map->item_list.push_back(mapdummy_item(t,coord_def(-1,1)));
			makeitem(ITM_POTION, -1, &t);
			map->item_list.push_back(mapdummy_item(t,coord_def(0,1)));
			makeitem(ITM_POTION, -1, &t);
			map->item_list.push_back(mapdummy_item(t,coord_def(1,1)));
			makeitem(ITM_POTION, -1, &t);
			map->item_list.push_back(mapdummy_item(t,coord_def(2,1)));
			makeAunnTemple(map, coord_def(0, -1));
			map->name = "ALTAR_EIRIN_POTION";
			return  "\
#.....#\
#..0..#\
###+###\
#.....#\
#######";
			break;
		}
	case 11: //신키와 P
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
						
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_SHINKI);
			int i = 5;
			while(i)
			{
				coord_def c_(rand_int(-2,2),rand_int(-2,2));
				map->event_list.push_back(mapdummy_event(EVL_SIGHT_P,c_,EVT_SIGHT));
				i--;
			}
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "ALTAR_SHINKI_P_ITEM";
			return  "\
.......\
.......\
.......\
...0...\
.......\
.......\
.......";
			break;
		}
	case 12: //스와코의 바다지형
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
						
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_SUWAKO);
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "ALTAR_SWAKO_SEA";
			return  "\
.......\
.#.~#~.\
.~~.~~.\
.~.0~#.\
..#~.~.\
.~.#~..\
.......";
			break;
		}
	case 13: //히나의 액모양 지형
		{
			bool hw_ = randA(1);
			map->size_x = 6;
			map->size_y = 5;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
						
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_HINA);
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "ALTAR_HINA_VORTEX";
			return  "\
.............\
.............\
...#######...\
..##.....##..\
..#..###..#..\
..#.##0#..#..\
....#....##..\
....##..##...\
.....####....\
.............\
.............";
			break;
		}
	case 14: //미노리코 고구마신전
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
						
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_MINORIKO);
			int i = rand_int(2,3);
			while(i)
			{
				coord_def c_(rand_int(-2,2),rand_int(-2,2));
				item_infor t;			
				makeitem(ITM_FOOD, 0, &t,1);
				map->item_list.push_back(mapdummy_item(t,c_));
				i--;
			}
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "ALTAR_MINORIKO_SWEET_POTATO";
			return  "\
.......\
.......\
.......\
...0...\
.......\
.......\
.......";
			break;
		}
	case 15: //치르노에 징벌을 가하는 스와코
		{
			map->size_x = 5;
			map->size_y = 3;
			map->m_entrance.x = rand_int(1-map->size_x,map->size_x-1);
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = rand_int(1-map->size_x,map->size_x-1);
			map->m_exit.y = -map->size_y;
						
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_SUWAKO);


			if(!is_exist_named(MON_CIRNO)){
				map->monster_list.push_back(mapdummy_mon(MON_CIRNO,M_FLAG_NETURALY | M_FLAG_DECORATE,coord_def(0,-1)));
				set_exist_named(MON_CIRNO);
			}
			map->monster_list.push_back(mapdummy_mon(MON_FROG,M_FLAG_DECORATE,coord_def(2,0)));
			map->monster_list.push_back(mapdummy_mon(MON_FROG,M_FLAG_DECORATE,coord_def(-2,0)));
			map->monster_list.push_back(mapdummy_mon(MON_FROG,M_FLAG_DECORATE,coord_def(0,0)));
			map->event_list.push_back(mapdummy_event(EVL_NOISE,coord_def(0,0),EVT_SIGHT));
			makeAunnTemple(map, coord_def(0, -3));
			map->name = "ALTAR_SWAKO_CIRNO";
			return  "\
#.........#\
#.=======.#\
#.=.~.~.=.#\
#.=~.~.~=.#\
#.=======.#\
#....0....#\
###########";
			break;
		}
	case 16: //유유코식단
		{
			map->size_x = 3;
			map->size_y = 2;	
			map->m_entrance.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x+1,map->size_x-1);
			map->m_exit.y = map->size_y;
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_YUYUKO);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;
			if(!is_exist_named(MON_MISTIA)) {
				map->monster_list.push_back(mapdummy_mon(MON_MISTIA,M_FLAG_DECORATE,coord_def(0,-1)));
				set_exist_named(MON_MISTIA);
			}
			else 
			{
				map->monster_list.push_back(mapdummy_mon(MON_RABBIT,M_FLAG_DECORATE,coord_def(0,-1)));
			}
			makeAunnTemple(map, coord_def(0, 1));
			map->name = "ALTAR_YUYUKO_DINER";
			return  "\
#######\
#.=.=.#\
#.===.#\
#..0..#\
#.....#";
			break;
		}
	case 17: //시즈하 단풍제단
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
						
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_SHIZUHA);
			int i = rand_int(6,8);
			while(i)
			{
				coord_def c_(rand_int(-2,2),rand_int(-2,2));
				if(c_.x == 0 && c_.y == 0)
					continue;
				map->event_list.push_back(mapdummy_event(EVL_AUTUMN,c_,EVT_SIGHT));
				i--;
			}
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "ALTAR_SHIZUHA_AUTUMN";
			return  "\
.......\
.......\
.......\
...0...\
.......\
.......\
.......";
			break;
		}
	case 18: //유우기 싸움
		{
			map->size_x = 5;
			map->size_y = 4;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = rand_int(-map->size_y+1,map->size_y-1);
			map->m_exit.x = map->size_x;
			map->m_exit.y = rand_int(-map->size_y,map->size_y);
						
			map->monster_list.push_back(mapdummy_mon(MON_ONI,M_FLAG_DECORATE,coord_def(0,-1)));
			map->monster_list.push_back(mapdummy_mon(MON_BLUE_ONI,M_FLAG_NETURALY | M_FLAG_DECORATE,coord_def(0,1)));

			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_YUUGI);
			makeAunnTemple(map, coord_def(0, -3));
			map->name = "ALTAR_YUUGI_ARENA";
			return  "\
###########\
.....0.....\
..=======..\
..=.....=..\
..=.....=..\
..=.....=..\
..=======..\
...........\
###########";
			break;
		}
	case 19: //유카리 스키마 제단
		{
			map->size_x = 2;
			map->size_y = 6;
			map->m_entrance.x = rand_int(-map->size_x + 1, map->size_x - 1);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x + 1, map->size_x - 1);
			map->m_exit.y = map->size_y;

			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_YUKARI);
			for (int i = -5; i <= 5; i += 2)
			{
				map->event_list.push_back(mapdummy_event(EVL_SUKIMA, coord_def(-1, i), EVT_APPROACH_SMALL));
				map->event_list.push_back(mapdummy_event(EVL_SUKIMA, coord_def(1, i), EVT_APPROACH_SMALL));
			}
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "ALTAR_YUKARI_SUKIMA";
			return  "\
#####\
#.0.#\
#...#\
#...#\
#...#\
#...#\
#...#\
#...#\
#...#\
#...#\
#...#\
#...#\
#...#";
			break;
		}
	case 20: //죠온&시온 낚시 지형
		{
			map->size_x = 3;
			map->size_y = 6;
			map->m_entrance.x = rand_int(-map->size_x + 2, map->size_x - 2);
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = rand_int(-map->size_x + 2, map->size_x - 2);
			map->m_exit.y = -map->size_y;

			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_JOON_AND_SION);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_STAIR | FLAG_NO_ITEM;

			for (int i = 0; i < 5; i++)
			{
				coord_def c_(1 - (i % 3) , -5 + i * 2);
				item_infor t;
				makeitem(randA(1) ? ITM_SCROLL : ITM_POTION, 0, &t, 1);
				map->event_list.push_back(mapdummy_event(EVL_SION_DELETE, c_, EVT_APPROACH_SMALL));
				map->item_list.push_back(mapdummy_item(t, c_));
			}
			makeAunnTemple(map, coord_def(-1, 5));
			map->name = "ALTAR_JOON_AND_SION_FISHING";
			return  "\
##...##\
###...#\
###...#\
##...##\
#...###\
#...###\
##...##\
###...#\
###...#\
##...##\
#...###\
#.0.###\
#######";
			break;
		}
	case 21: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_FLOWER";
			return  "\
.......\
..._...\
..___..\
._f0f_.\
..___..\
..._...\
.......";
			break;
		}
	case 22: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			makeAunnTemple(map, coord_def(0, 0));
			random_extraction<int> rand_;
			rand_.push(DG_SEA);
			rand_.push(DG_LAVA);
			rand_.push(DG_OIL);
			rand_.push(DG_GLASS);
			map->sp_tile_list.push_back((dungeon_tile_type)rand_.pop());
			map->sp_tile_list.push_back((dungeon_tile_type)rand_.pop());
			map->sp_tile_list.push_back((dungeon_tile_type)rand_.pop());
			map->sp_tile_list.push_back((dungeon_tile_type)rand_.pop());
			map->name = "COMMON_ALTAR_FOUR_PATH";
			return  "\
.......\
..#3#..\
.##3##.\
.11022.\
.##4##.\
..#4#..\
.......";
			break;
		}
	case 23: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_PILLAR2";
			return  "\
.#...#.\
#.....#\
..#.#..\
#..0..#\
..#.#..\
#.....#\
.#...#.";
			break;
		}
	case 24: //전부
		{
			map->size_x = 1;
			map->size_y = 5;
			map->m_entrance.x = rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x, map->size_x);
			map->m_exit.y = map->size_y;
			makeAunnTemple(map, coord_def(0, -4));
			map->name = "COMMON_ALTAR_PATH_OF_TREE";
			return  "\
.0.\
T_T\
._.\
T_T\
._.\
T_T\
._.\
T_T\
._.\
T_T\
._.";
			break;
		}
	case 25: //전부
		{
			map->size_x = 6;
			map->size_y = 4;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = 0;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 0;
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_BRIDGE";
			return  "\
~~~~~~~~~~~~~\
~~~~~~~~~~~~~\
~~~~~~.~~~~~~\
~~~~~...~~~~~\
......0......\
~~~~~...~~~~~\
~~~~~~.~~~~~~\
~~~~~~~~~~~~~\
~~~~~~~~~~~~~";
			break;
		}
	case 26: //전부
		{
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = 0;
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_CROSS";
			return  "\
``#.#``\
``#.#``\
###.###\
#..0..#\
###.###\
``#.#``\
``#.#``";
			break;
		}
	case 27: //전부
		{
			map->size_x = 5;
			map->size_y = 3;	
			map->m_entrance.x = rand_int(-1,1);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-1,1);
			map->m_exit.y = map->size_y;
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_WINDOW";
			return  "\
###########\
#....0....#\
#.###=###.#\
#.#.....#.#\
#.#.....#.#\
#.+.....+.#\
####...####";
			break;
		}
	case 28: //전부
		{
			map->size_x = 1;
			map->size_y = 4;
			map->m_entrance.x = rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x, map->size_x);
			map->m_exit.y = map->size_y;
			makeAunnTemple(map, coord_def(0, 1));
			map->name = "COMMON_ALTAR_MANY_DOOR";
			return  "\
#+#\
#.#\
#+#\
#.#\
#+#\
#.#\
#+#\
#0#\
###";
			break;
		}
	case 29: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 1;
			map->size_y = 1;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):0;
			map->m_entrance.y = hw_?0:(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):0;
			map->m_exit.y = hw_?0:(randA(1)?-map->size_y:map->size_y);
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_STATUE";
			return  "\
B.B\
.0.\
B.B";
			break;
		}
	case 30: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			
			monster_index mon_ = MON_MOOK;
			dungeon_tile_type god_tile = DG_FLOOR;
			if(map->sp_tile_list.size() > 0)
				god_tile = map->sp_tile_list[0];
			switch (god_tile) {
			case DG_TEMPLE_JOON_AND_SION:
				mon_ = MON_BUTTERFLY;
				break;
			case DG_TEMPLE_BYAKUREN:
				mon_ = MON_MAGIC_BOOK;
				break;
			case DG_TEMPLE_KANAKO:
				mon_ = MON_SNAKE;
				break;
			case DG_TEMPLE_SUWAKO:
				mon_ = MON_FROG;
				break;
			case DG_TEMPLE_MINORIKO:
				mon_ = MON_MUSHROOM;
				break;
			case DG_TEMPLE_MIMA:
				mon_ = MON_HAUNT;
				break;
			case DG_TEMPLE_SHINKI:
				mon_ = MON_LITTLE_IMP;
				break;
			case DG_TEMPLE_YUUGI:
				mon_ = MON_BLUE_ONI;
				break;
			case DG_TEMPLE_SHIZUHA:
				mon_ = MON_ORANGE_MOOK;
				break;
			case DG_TEMPLE_HINA:
				mon_ = MON_CURSE_DOLL;
				break;
			case DG_TEMPLE_YUKARI:
				mon_ = MON_SCHEMA_EYE;
				break;
			case DG_TEMPLE_EIRIN:
				mon_ = MON_RABBIT;
				break;
			case DG_TEMPLE_YUYUKO:
				mon_ = MON_GHOST;
				break;
			case DG_TEMPLE_SATORI:
				mon_ = MON_ORANGE_CAT;
				break;
			case DG_TEMPLE_TENSI:
				mon_ = MON_KANAME;
				break;
			case DG_TEMPLE_SEIJA:
				mon_ = MON_DANCING_WEAPON;
				break;
			case DG_TEMPLE_LILLY:
				mon_ = MON_FAIRY_GREEN;
				break;
			case DG_TEMPLE_MIKO:
				mon_ = MON_DESIRE;
				break;
			case DG_TEMPLE_OKINA:
				mon_ = MON_CLOSE_DOOR;
				break;
			case DG_TEMPLE_JUNKO:
				mon_ = MON_LUNATIC;
				break;
			default:
				break;
			}
			
			if(god_tile != DG_FLOOR) {
				map->monster_list.push_back(mapdummy_mon(mon_,M_FLAG_DECORATE,coord_def(0,0)));
			}
			makeAunnTemple(map, coord_def(0, 2));
			map->name = "COMMON_ALTAR_INTHE_GLASS";
			return  "\
.......\
...0...\
..===..\
..=.=..\
..===..\
.......\
.......";
			break;
		}
	case 31: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 1;
			map->size_y = 1;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):0;
			map->m_entrance.y = hw_?0:(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):0;
			map->m_exit.y = hw_?0:(randA(1)?-map->size_y:map->size_y);
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_STATUE2";
			return  "\
...\
.0.\
.&.";
			break;
		}
	case 32: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 2;
			map->size_y = 3;
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_WATER_";
			return  "\
.....\
.~~~.\
.~.~.\
..0..\
.;.;.\
.;;;.\
.....";
			break;
		}
	case 33: //전부
		{
			bool hw_ = randA(1);
			map->size_x = 7;
			map->size_y = 2;	
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			dungeon_tile_type god_tile = DG_FLOOR;
			if(map->sp_tile_list.size() > 0)
				god_tile = map->sp_tile_list[0];
			 map->sp_tile_list.clear();
			random_extraction<dungeon_tile_type> rand_;
			rand_.push(god_tile);
			rand_.push(DG_STATUE);
			rand_.push(DG_STATUE2);
			dungeon_tile_type i1 = rand_.pop();
			dungeon_tile_type i2 = rand_.pop();
			dungeon_tile_type i3 = rand_.pop();
			map->sp_tile_list.push_back(i1);
			if(i1 != DG_STATUE && i1 != DG_STATUE2)
				makeAunnTemple(map, coord_def(-5, 0));
			map->sp_tile_list.push_back(i2);
			if(i2 != DG_STATUE && i2 != DG_STATUE2)
				makeAunnTemple(map, coord_def(0, 0));
			map->sp_tile_list.push_back(i3);
			if(i3 != DG_STATUE && i3 != DG_STATUE2)
				makeAunnTemple(map, coord_def(5, 0));
			map->name = "COMMON_ALTAR_THREE_DOOR";
			return  "\
...............\
.###..###..###.\
.#0#..#1#..#2#.\
.#+#..#+#..#+#.\
...............";
			break;
		}
	case 34: //전부
		{
			map->size_x = 2;
			map->size_y = 3;	
			map->m_entrance.x = rand_int(-map->size_x,-map->size_x);
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = -rand_int(-map->size_x,-map->size_x);
			map->m_exit.y = -map->size_y;
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "COMMON_ALTAR_GLASS_SHOPPING";
			return  "\
.....\
##+##\
.#.#.\
.=0=.\
.#.#.\
.#=#.\
.....";
			break;
		}
	case 35: //뱌쿠렌 도서관
		{
			map->size_x = 5;
			map->size_y = 4;
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			makeAunnTemple(map, coord_def(0, -2));
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_BYAKUREN);
			map->name = "ALTAR_BYAKUREN_LIBRARY";
			return  "\
###########\
#....0....#\
#.EEE.EEE.#\
#.........#\
#.EEE.EEE.#\
#.........#\
#.EEE.EEE.#\
#.........#\
#####+#####";
			break;
		}
	case 36: //카나코 온바시라
		{
			bool hw_ = randA(1);
			map->size_x = 2;
			map->size_y = 2;
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_KANAKO);
			makeAunnTemple(map, coord_def(0, 0));
			map->monster_list.push_back(mapdummy_mon(MON_ONBASIRA,M_FLAG_COMPLETE_NETURALY,coord_def(-1,1)));
			map->monster_list.push_back(mapdummy_mon(MON_ONBASIRA,M_FLAG_COMPLETE_NETURALY,coord_def(1,-1)));
			map->monster_list.push_back(mapdummy_mon(MON_ONBASIRA,M_FLAG_COMPLETE_NETURALY,coord_def(1,1)));
			map->monster_list.push_back(mapdummy_mon(MON_ONBASIRA,M_FLAG_COMPLETE_NETURALY,coord_def(-1,-1)));
			
			map->name = "ALTAR_KANAKO_ONBASHIRA";
			return  "\
.....\
.....\
..0..\
.....\
.....";
			break;
		}
	case 37: //릴리 꽃밭
		{
			map->size_x = 5;
			map->size_y = 4;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = 3;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 3;
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_LILLY);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			makeAunnTemple(map, coord_def(0, 0));
			map->monster_list.push_back(mapdummy_mon(MON_FAIRY_GREEN,M_FLAG_COMPLETE_NETURALY | M_FLAG_SHIELD | M_FLAG_WAKE,coord_def(-1,1)));
			map->monster_list.push_back(mapdummy_mon(MON_FAIRY_GREEN,M_FLAG_COMPLETE_NETURALY | M_FLAG_SHIELD | M_FLAG_WAKE,coord_def(1,-1)));
			map->monster_list.push_back(mapdummy_mon(MON_FAIRY_BLUE,M_FLAG_COMPLETE_NETURALY | M_FLAG_SHIELD | M_FLAG_WAKE,coord_def(1,1)));
			map->monster_list.push_back(mapdummy_mon(MON_FAIRY_RED,M_FLAG_COMPLETE_NETURALY | M_FLAG_SHIELD | M_FLAG_WAKE,coord_def(-1,-1)));
			
			map->name = "ALTAR_LILLY_GARDEN";
			return  "\
###########\
#T__f0f__T#\
#__f___f__#\
#________f#\
#_________#\
#_f__f__f_#\
#_________#\
+____f____+\
###########";
			break;
		}
	case 38: //미코 10개의 욕망
		{
			map->size_x = 5;
			map->size_y = 3;
			map->m_entrance.x = rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x,map->size_x);
			map->m_exit.y = map->size_y;
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_MIKO);
			makeAunnTemple(map, coord_def(0, 2));
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			for(int i = 0; i<9;i++) {
				map->monster_list.push_back(mapdummy_mon(MON_DESIRE,M_FLAG_DECORATE,coord_def(1-map->size_x+i,-1)));
			}
			map->monster_list.push_back(mapdummy_mon(MON_DESIRE,M_FLAG_DECORATE,coord_def(0,0)));
			
			map->name = "ALTAR_MIKO_10_DESIRE";
			return  "\
```````````\
===========\
=.........=\
=====.=====\
....===....\
.....0.....\
...........";
			break;
		}
	case 39: //세이자 신전 바꾸기
		{
			map->size_x = 3;
			map->size_y = 4;	
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			map->sp_tile_list.clear();			
			int i = 9;
			while(i)
			{
				dungeon_tile_type dg_t_ = randomTemple();
				auto it = find(map->sp_tile_list.begin(), map->sp_tile_list.end(),dg_t_);
				if(it != map->sp_tile_list.end())
					continue;
				map->sp_tile_list.push_back(dg_t_);
				map->event_list.push_back(mapdummy_event(EVL_CHANGE_TILE, coord_def(-2+(i%3)*2,-3+(i/3)*2), EVT_APPROACH_SMALL,DG_TEMPLE_SEIJA));
				i--;
			}
			map->name = "ALTAR_SEIJA_CHANGE_TILE";
			return  "\
#######\
#0.1.3#\
#.....#\
#4.5.6#\
#.....#\
#7.8.9#\
#.....#\
#.....#\
###+###";
			break;
		}
	case 40: //오키나 많은 문
		{
			bool hw_ = randA(1);
			map->size_x = 2;
			map->size_y = 2;
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			makeAunnTemple(map,coord_def(0, 0));
			map->name = "ALTAR_OKINA_MANY_DOOR";
			return  "\
+++++\
+++++\
++0++\
+++++\
+++++";
		}
	case 41: //순호와 클라운피스
		{
			bool hw_ = randA(1);
			map->size_x = 4;
			map->size_y = 4;
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_JUNKO);
			makeAunnTemple(map, coord_def(0, -2));
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			if (!is_exist_named(MON_CLOWNPIECE)) {
				map->monster_list.push_back(mapdummy_mon(MON_CLOWNPIECE, M_FLAG_DECORATE | M_FLAG_COMPLETE_NETURALY, coord_def(0, 0)));
				set_exist_named(MON_CLOWNPIECE);
			}
			
			map->name = "ALTAR_JUNKO_CLOWNPIECE";
			return  "\
.........\
....0....\
.=======.\
.=f___T=.\
.=_____=.\
.=____~=.\
.=======.\
.........\
.........";
			break;
		}
	case 42: //미마
		{
			map->size_x = 6;
			map->size_y = 4;
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = -map->size_y;
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_MIMA);
			makeAunnTemple(map, coord_def(0, 3));
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			map->monster_list.push_back(mapdummy_mon(MON_TRASH,M_FLAG_DECORATE | M_FLAG_NETURALY,coord_def(-2,0)));
			map->monster_list.push_back(mapdummy_mon(MON_TRASH,M_FLAG_DECORATE | M_FLAG_NETURALY,coord_def(-3,-1)));
			map->monster_list.push_back(mapdummy_mon(MON_TRASH,M_FLAG_DECORATE | M_FLAG_NETURALY,coord_def(-3,1)));
			map->monster_list.push_back(mapdummy_mon(MON_TRASH,M_FLAG_DECORATE | M_FLAG_NETURALY,coord_def(-1,-1)));
			map->monster_list.push_back(mapdummy_mon(MON_TRASH,M_FLAG_DECORATE | M_FLAG_NETURALY,coord_def(-1,1)));
			map->event_list.push_back(mapdummy_event(EVL_MIMA_SPARK_BOOK,coord_def(3,0),EVT_SIGHT));
			map->name = "ALTAR_MIMA_SPARK_BOOK";
			return  "\
######+######\
#...........#\
#.=========.#\
#.=.......=.#\
#.=.......=.#\
#.=.......=.#\
#.=========.#\
#.....0.....#\
######+######";
			break;
		}
	case 43: //텐시
		{
			bool hw_ = randA(1);
			map->size_x = 5;
			map->size_y = 5;
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_TENSI);
			makeAunnTemple(map, coord_def(0, 0));
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			map->event_list.push_back(mapdummy_event(EVL_TENSI_EARTHQUAKE,coord_def(3,0),EVT_SIGHT));
			map->name = "ALTAR_TENSI_COLLAPSING_WALL";
			return  "\
...........\
.#########.\
.#########.\
.#########.\
.#########.\
.####0####.\
.#########.\
.#########.\
.#########.\
.#########.\
...........";
			break;
		}
	case 45: //유유코
		{
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;
			map->m_entrance.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_entrance.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_?(randA(1)?-map->size_x:map->size_x):rand_int(-map->size_x,map->size_x);
			map->m_exit.y = hw_?rand_int(-map->size_y,map->size_y):(randA(1)?-map->size_y:map->size_y);
			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_YUYUKO);
			makeAunnTemple(map, coord_def(0, 0));
			map->flag = FLAG_NO_STAIR;
			map->monster_list.push_back(mapdummy_mon(MON_GHOST,M_FLAG_COMPLETE_NETURALY | M_FLAG_SHIELD | M_FLAG_WAKE,coord_def(-1,0)));
			map->monster_list.push_back(mapdummy_mon(MON_GHOST,M_FLAG_COMPLETE_NETURALY | M_FLAG_SHIELD | M_FLAG_WAKE,coord_def(-1,-1)));
			map->monster_list.push_back(mapdummy_mon(MON_GHOST,M_FLAG_COMPLETE_NETURALY | M_FLAG_SHIELD | M_FLAG_WAKE,coord_def(1,1)));
			map->name = "ALTAR_YUYUKO_GHOST";
			return  "\
.......\
.......\
.......\
...0...\
.......\
.......\
.......";
			break;
		}
	}
}


const char* altar_pattern(map_dummy* map, god_type god_)
{

	vector<int> id_list;
	
	for(int i = 0; i < GetMaxAlter(); i++)
	{
		if(isGodTemple(i, god_))
			id_list.push_back(i);
	}
	
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back((dungeon_tile_type)(DG_TEMPLE_FIRST+god_));

	return real_altar_pattern(map,id_list[randA(id_list.size()-1)]);
}