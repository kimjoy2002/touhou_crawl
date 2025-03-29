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
		//공용 신
		return true;
	case 9:
		//뱌쿠렌
		return (god_ == GT_BYAKUREN);
	case 12:
		//스와코
		return (god_ == GT_SUWAKO);
	case 15:
		//스와코
		return (!is_exist_named(MON_CIRNO) && god_ == GT_SUWAKO);
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
		return (!is_exist_named(MON_ORIN) || !is_exist_named(MON_DIEFAIRY))
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
	}
}

int GetMaxAlter(){return 21;};


void makeAunnTemple(map_dummy* map, coord_def c)
{
	//아운은 랜덤하게 제단 생성 맵에 끼어들어서 그 지역을 수호한다.

	if (is_exist_named(MON_AUNN))
		return;
	if (randA(99) < 1) 
	{//확률 1% (그러나 실제로 신전은 16개정도 생기므로 대략 15%정도 확률로 아운이 등장한다.
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
		map->name = "공용제단_다이아문방";
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
		map->name = "공용제단_가로_일자통로";
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
			map->name = "공용제단_기둥";
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
			if(!is_exist_named(MON_ORIN) && (randA(1) || is_exist_named(MON_DIEFAIRY))) {
				map->monster_list.push_back(mapdummy_mon(MON_ORIN,0,coord_def(0,-1)));
				set_exist_named(MON_ORIN);
			}
			else 
			{
				map->monster_list.push_back(mapdummy_mon(MON_DIEFAIRY,0,coord_def(0,-1)));
				set_exist_named(MON_DIEFAIRY);
			}
			makeAunnTemple(map, coord_def(0, 1));
			map->name = "제단_아키샌드";
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
			map->name = "제단_모리야신사";
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
			map->name = "공용제단_작은_방";
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
						
			int i = 3;
			while(i)
			{
				dungeon_tile_type dg_t_ = randomTemple();
				auto it = find(map->sp_tile_list.begin(), map->sp_tile_list.end(),dg_t_);
				if(it != map->sp_tile_list.end())
					continue;
				map->sp_tile_list.push_back(dg_t_);
				i--;
			}
			makeAunnTemple(map, coord_def(0, 0));
			map->name = "공용제단_동서남북";
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
			map->name = "제단_구작결계";
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
			map->monster_list.push_back(mapdummy_mon(randA(2)==0?MON_WHITE_CAT:randA(1)?MON_BLACK_CAT:MON_ORANGE_CAT,0,coord_def(-3,-1)));
			map->monster_list.push_back(mapdummy_mon(randA(2)==0?MON_WHITE_CAT:randA(1)?MON_BLACK_CAT:MON_ORANGE_CAT,0,coord_def(-1,1)));
			map->monster_list.push_back(mapdummy_mon(MON_CROW,0,coord_def(1,-1)));
			map->monster_list.push_back(mapdummy_mon(MON_CROW,0,coord_def(3,1)));
			makeAunnTemple(map, coord_def(0, 3));
			map->name = "제단_사토리_사육터";
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
			map->name = "제단_뱌쿠렌_책선물";
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
			map->name = "제단_에이린_포션";
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
			map->name = "제단_신키_P";
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
			map->name = "제단_스와코_바다";
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
			map->name = "제단_히나_액지형";
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
			map->name = "제단_미노리코_고구마";
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
				map->monster_list.push_back(mapdummy_mon(MON_CIRNO,M_FLAG_NETURALY,coord_def(0,-1)));
				set_exist_named(MON_CIRNO);
			}
			map->monster_list.push_back(mapdummy_mon(MON_FROG,0,coord_def(2,0)));
			map->monster_list.push_back(mapdummy_mon(MON_FROG,0,coord_def(-2,0)));
			map->monster_list.push_back(mapdummy_mon(MON_FROG,0,coord_def(0,0)));
			map->event_list.push_back(mapdummy_event(EVL_NOISE,coord_def(0,0),EVT_SIGHT));
			makeAunnTemple(map, coord_def(0, -3));
			map->name = "제단_스와코_치르노징벌";
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
				map->monster_list.push_back(mapdummy_mon(MON_MISTIA,0,coord_def(0,-1)));
				set_exist_named(MON_MISTIA);
			}
			else 
			{
				map->monster_list.push_back(mapdummy_mon(MON_RABBIT,0,coord_def(0,-1)));
			}
			makeAunnTemple(map, coord_def(0, 1));
			map->name = "제단_유유코_식단";
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
			map->name = "제단_시즈하_단풍";
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
						
			map->monster_list.push_back(mapdummy_mon(MON_ONI,0,coord_def(0,-1)));
			map->monster_list.push_back(mapdummy_mon(MON_BLUE_ONI,M_FLAG_NETURALY,coord_def(0,1)));

			map->sp_tile_list.clear();
			map->sp_tile_list.push_back(DG_TEMPLE_YUUGI);
			makeAunnTemple(map, coord_def(0, -3));
			map->name = "제단_유우기_투기장";
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
			map->name = "제단_유카리_스키마";
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
			map->name = "제단_죠온시온_낚시";
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