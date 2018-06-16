//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: map_pattern.cpp
//
// ����: �� ���� �����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "map.h"
#include "throw.h"
#include "mon_infor.h"
#include "event.h"
#include "evoke.h"
#include "rect.h"



dungeon_tile_type randomTemple(); 
char* pande_pattern(map_dummy* map);

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
		map->name = "����_��������Ա�";
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
	if (floor_ >= PANDEMONIUM_LEVEL && floor_ <= PANDEMONIUM_LAST_LEVEL)
		return pande_pattern(map);

	random_extraction<int> randomPattern;
	//randomPattern.push(0, 1);
	//randomPattern.push(63, 100);
	for (int i = 0; i <= 63; i++)
	{
		int base_pe = 1;
		if (i == 39 || i == 41)
			base_pe = 3; //��� Ư�� ��������
		randomPattern.push(i,base_pe);
	}
	while(randomPattern.GetSize())
	{
		

		switch(randomPattern.pop())
		{
		default:
		case 0:
			map->size_x = 5;
			map->size_y = 3;	
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = -2;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 2;
			map->name = "�⺻_S����";
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
			map->name = "�⺻_�ٵ���";
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
				map->name = "�⺻_��";
				return  "\
...........\
...___.....\
..__~___...\
.._~_~~__..\
..__~~~__..\
.._~~T~~__.\
.._~~~~_~_.\
..__~_____.\
...___.....\
...........\
...........";
				break;		
			}
		case 3: //�糪ƽ Ÿ��
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
				map->name = "Ŭ����ǽ�_�糪ƽŸ��";
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
			map->name = "�⺻_�����ϼ���";
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
				map->name = "�⺻_33��ö��";
				return  "\
.....\
.$$$.\
.$$$.\
.$$$.\
.....";			
			}
		case 6: //Ǯ�Ѹ� �䱫 ��Ʈ��ũ
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
				map->name = "Ǯ�Ѹ�_��Ʈ��ũ";
				return  "\
.......\
.~~~~~.\
.~...~.\
.~...~.\
.~...~.\
.~~~~~.\
.......";			
			}
		case 7: //���ڹ̽�ġ �ܼ�Ʈ
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
				map->name = "����_�̽�ġ_�ܼ�Ʈ";
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
			map->name = "�⺻_����������";
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
		case 9: //�ڰ��� �޽�
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
				map->name = "�ڰ���_�޽�";
				return  "\
####.\
#....\
#...#\
#...#\
..###";			
			}
		case 10: //����������
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
			map->name = "����������";
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
			map->name = "�⺻_��������";
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
			map->name = "�⺻_��ö���ڰ�";
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
			map->name = "�⺻_���Թ�";
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
			map->name = "�⺻_����_������׹�";
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
			map->name = "�⺻_������";
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
			map->name = "�⺻_����ִ�_��";
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
			map->name = "�⺻_����_����";
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
			map->name = "�⺻_��_��ö��";
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
			map->name = "�⺻_����_�������";
			return  "\
###############\
....=.....=....\
.=..=..=..=..=.\
.=.....=.....=.\
.=..=..=..=..=.\
....=.....=....\
###############";
			break;
		case 20: //��ž�� ã�� ���
			{
			if (!(floor_ >= 7 && floor_ <= 14))
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
			map->name = "���_��ž�߰�";
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
		case 21: //������ ����
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
			map->name = "����_�л���";
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
			map->name = "�ʹ�_����_����";
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
			map->name = "�ʹ�_��ö_�����ۻ���";
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
			map->name = "�ʹ�_���ں�_���";
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
			map->name = "�ʹ�_����_��";
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
		case 26: //UFO�׸���
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
			map->name = "�ʹ�_�����_��ȣ��";
			return  "\
.......\
.=====.\
.=...=.\
.=====.\
.......";
			break;
			}
		case 27: //������ ��
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
			map->name = "�����_����";
			return  "\
#######\
#.....#\
+.....+\
#.....#\
#######";
			break;
		case 28: //ȫ���� å Ʈ��
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
			map->name = "ȫ����_å_Ʈ��";
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
		case 29: //�䱫�ǻ� ������
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
			map->name = "�䱫�ǻ�_������";
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
		case 30: //�ڰ��� Ÿ��
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
				map->name = "�ڰ���_����������Ÿ��";
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
			map->name = "�⺻_������յ�";
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
			map->name = "�⺻_�����";
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
			map->name = "�⺻_����_å���";
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
			map->name = "�⺻_����_å���";
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
				map->name = "�⺻_����_����";
				return  "\
.....\
.~~~.\
.~~~.\
.~~~.\
..&..\
.....\
.....";			
			}
		case 36: //������ ����â��
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
				map->name = "�⺻_������_å��";
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
				map->name = "�⺻_������_����";
				return  "\
.....\
.###.\
.#0#.\
.#&#.\
.....";			
			}
		case 38: //����� ��������
			{
				if (is_exist_named(MON_NARUMI))
					break;
				if (!(floor_ >= YOUKAI_MOUNTAIN_LEVEL && floor_ <= YOUKAI_MOUNTAIN_LAST_LEVEL))
					break;
				map->size_x = 3;
				map->size_y = 3;
				map->m_entrance.x = -map->size_x;
				map->m_entrance.y = 0;
				map->m_exit.x = map->size_x;
				map->m_exit.y = 0;
				if (!is_exist_named(MON_NARUMI)) {
					map->monster_list.push_back(mapdummy_mon(MON_NARUMI, 0, coord_def(2, 2)));
					set_exist_named(MON_NARUMI);
				}
				map->name = "�����_�䱫��_���󺸻�";
				return  "\
TTT.TTT\
TB...BT\
T..~..T\
..~~~..\
T..~..T\
TB....T\
TTT.TTT";
			}
		case 39: //�׹��� ��������
			{
				if (is_exist_named(MON_NEMUNO) && is_exist_named(MON_HATATE))
					break;
				if (!(floor_ >= YOUKAI_MOUNTAIN_LEVEL && floor_ <= YOUKAI_MOUNTAIN_LEVEL+3))
					break;
				map->size_x = 6;
				map->size_y = 2;
				map->m_entrance.x = map->size_x;
				map->m_entrance.y = 0;
				map->m_exit.x = map->size_x;
				map->m_exit.y = 0;
				random_extraction<monster_index> rad_;

				if (!is_exist_named(MON_NEMUNO))
					rad_.push(MON_NEMUNO);
				if (!is_exist_named(MON_HATATE))
					rad_.push(MON_HATATE);
				{
					monster_index mon_ = rad_.pop();
					map->monster_list.push_back(mapdummy_mon(mon_, 0, coord_def(-4, 0)));
					set_exist_named(mon_);
				}
				map->flag = FLAG_NO_STAIR;
				map->event_list.push_back(mapdummy_event(EVL_LOCK_DOOR, coord_def(-2, 0), EVT_ALWAYS));
				map->name = "�׹�����Ÿ��_�ݸ���";
				return  "\
$$$$$TTTTTTTT\
$...$TTT.TTTT\
$...+.T.T.TT.\
$...$T.TTT..T\
$$$$$TTTTTTTT";
			}
		case 40: //��� ��������
			{
				if (is_exist_named(MON_LARVA))
					break;
				if (!((floor_ >= 7 && floor_ <= 10) ||
					(floor_ >= MISTY_LAKE_LEVEL && floor_ <= MISTY_LAKE_LEVEL + 2)))
					break;
				bool hw_ = randA(1);
				map->size_x = 3;
				map->size_y = 3;
				map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
				map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
				hw_ = randA(1);
				map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
				map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
				/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
				if (!is_exist_named(MON_LARVA)) {
					map->monster_list.push_back(mapdummy_mon(MON_LARVA, 0, coord_def(0, 0)));
					set_exist_named(MON_LARVA);
				}
				map->monster_list.push_back(mapdummy_mon(MON_BUTTERFLY, 0, coord_def(-1, -1)));
				map->monster_list.push_back(mapdummy_mon(MON_BUTTERFLY, 0, coord_def(1, -1)));
				map->monster_list.push_back(mapdummy_mon(MON_BUTTERFLY, 0, coord_def(-1, 1)));
				map->monster_list.push_back(mapdummy_mon(MON_BUTTERFLY, 0, coord_def(1, 1)));
				map->name = "���_�����";
				return  "\
..._...\
.T___T.\
._____.\
_______\
._____.\
.T___T.\
..._...";
				break;
			}
		case 41:
		{//ȣ������
			if (is_exist_named(MON_FUTO) || is_exist_named(MON_TOZIKO))
				break;
			if (!(floor_ >= DEPTH_LEVEL && floor_ <= DEPTH_LAST_LEVEL))
				break;
			map->size_x = 5;
			map->size_y = 4;
			map->m_entrance.x = rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x, map->size_x);
			map->m_exit.y = map->size_y;
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			map->sp_tile_list.push_back(DG_TEMPLE_MIKO);

			if (true || !is_exist_named(MON_TOZIKO)) {
				map->monster_list.push_back(mapdummy_mon(MON_TOZIKO, 0, coord_def(-4, -3)));
				set_exist_named(MON_TOZIKO);
			}
			if (true || !is_exist_named(MON_FUTO)) {
				map->monster_list.push_back(mapdummy_mon(MON_FUTO, 0, coord_def(4, -3)));
				set_exist_named(MON_FUTO);
			}
			map->event_list.push_back(mapdummy_event(EVL_HOJOK, coord_def(0, -2), EVT_APPROACH_MIDDLE));
			map->name = "ȣ������";
			return  "\
$$$$$$$$$$$\
$.$iiiii$.$\
$$$.iii.$$$\
$.........$\
$....0....$\
$.........$\
$.........$\
$.........$\
$.........$";
			break;
		}
		case 42: //�ڰ��� ��¦�Ȱ�
		{
			if (is_exist_named(MON_KOGASA))
				break;
			if (!(floor_ >= 2 && floor_ <= 4))
				break;
			bool hw_ = randA(1);
			map->size_x = 2;
			map->size_y = 2;
			map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			if (!is_exist_named(MON_KOGASA)) {
				map->event_list.push_back(mapdummy_event(EVL_KOGASA3, coord_def(0, 0), EVT_ALWAYS));
				set_exist_named(MON_KOGASA);
			}
			map->name = "�ڰ���_����";
			return  "\
.....\
.....\
.....\
.....\
.....";
		}
		case 43: //�޵�
		{
			if (is_exist_named(MON_MEDICINE))
				break;
			if (!(floor_ >= 8 && floor_ <= 14))
				break;
			map->size_x = 4;
			map->size_y = 4;
			map->m_entrance.x = rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = rand_int(-map->size_x, map->size_x);
			map->m_exit.y = map->size_y;
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			if (!is_exist_named(MON_MEDICINE)) {
				map->event_list.push_back(mapdummy_event(EVL_MEDI, coord_def(0, 0), EVT_ALWAYS));
				set_exist_named(MON_MEDICINE);
			}
			map->name = "�޵�_�뷮�л�";
			return  "\
#.......#\
#.......#\
#.~~~~~.#\
#.~___~.#\
#._____.#\
#.~___~.#\
#.~~~~~.#\
#.......#\
#.......#";
		}
		case 44:
		{
			bool hw_ = randA(1);
			map->size_x = 2;
			map->size_y = 2;
			map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			item_infor t;
			makeitem(ITM_FOOD, 0, &t);
			map->item_list.push_back(mapdummy_item(t, coord_def(0, 1)));
			map->name = "�⺻_���󺸻�_����";
			return  "\
.....\
.###.\
.#B#.\
.....\
.....";
		}
		case 45:
		{
			if (!((floor_ >= 8 && floor_ <= 14) ||
				(floor_ >= MISTY_LAKE_LEVEL && floor_ <= MISTY_LAKE_LAST_LEVEL)
				))
				break;
			map->size_x = 3;
			map->size_y = 3;
			map->m_entrance.x = map->size_x;
			map->m_entrance.y = 0;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 0;
			map->flag = FLAG_NO_MONSTER  | FLAG_NO_STAIR;
			random_extraction<int> rand_;

			if(randA(1))
			{
				rand_.push(MON_FAIRY_GREEN, 3);
				rand_.push(MON_FAIRY_BLUE, 3);
				rand_.push(MON_FAIRY_RED, 3);
				rand_.push(MON_FAIRY_GREEN_WARRIOR, 2);
				rand_.push(MON_FAIRY_RED_COMMANDER);
			}
			else
			{
				rand_.push(MON_HUMAM_MAN, 5);
				rand_.push(MON_HUMAM_YINYANG, 2);
				rand_.push(MON_HUMAM_PRIEST, 1);
				rand_.push(MON_HUMAM_SAMURI, 1);
			}

			for (rect_iterator rlt2(coord_def(0,0), 2, 2); !rlt2.end(); rlt2++) {
				map->monster_list.push_back(mapdummy_mon(rand_.choice(), 0, (*rlt2)));
			}
			map->event_list.push_back(mapdummy_event(EVL_LOCK_DOOR, coord_def(3, 0), EVT_ALWAYS));
			map->name = "�ʹ�_�Ȱ�ȣ��_������_��";
			return  "\
#######\
#.....#\
#.....#\
#.....+\
#.....#\
#.....#\
#######";
		}
		case 46:
		{
			if (!(floor_ <= 14))
				break;
			map->size_x = 4;
			map->size_y = 4;
			bool hw_ = randA(1);
			map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			map->flag = FLAG_NO_STAIR;
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			map->name = "�ʹ�_����_������";
			return  "\
.........\
.........\
..$$..$..\
...$$$$..\
...i=i...\
..$$$$...\
..$..$$..\
.........\
.........";
			break;
		}
		case 47:
		{
			if (!(floor_ <= 14))
				break;
			map->size_x = 7;
			map->size_y = 3;
			bool hw_ = randA(1);
			map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			map->flag = FLAG_NO_STAIR | FLAG_NO_MONSTER | FLAG_NO_ITEM;
			random_extraction<int> rand_;
			rand_.push(MON_FAIRY_GREEN, 3);
			rand_.push(MON_MOOK, 3);
			rand_.push(MON_CROW, 3);
			rand_.push(MON_FAIRY_GREEN_WARRIOR, 1);
			rand_.push(MON_CRANE, 1);
			rand_.push(MON_ORANGE_MOOK, 1);
			for (int i = 0; i < 5; i++)
			{
				map->monster_list.push_back(mapdummy_mon(rand_.choice(), 0, coord_def(-4+i*2,0)));
			}
			map->name = "�ʹ�_������_����";
			return  "\
...............\
.#############.\
.#############.\
.##i#i#i#i#i##.\
.#############.\
.#############.\
...............";
			break;
		}
		case 48:
		{
			if (!(floor_ <= 14))
				break;
			bool hw_ = randA(1);
			map->size_x = 2;
			map->size_y = 2;
			map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			/*map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM;*/
			map->event_list.push_back(mapdummy_event(EVL_SMOKE, coord_def(0, 0), EVT_ALWAYS));
			map->name = "�ʹ�_��õ";
			return  "\
.....\
.~~~.\
.~~~.\
.~~~.\
.....";
		}
		case 49:
		{
			if (is_exist_named(MON_WRIGGLE))
				break;
			if (!(floor_ >= 3 && floor_ <= 6))
				break;
			bool hw_ = randA(1);
			map->size_x = 3;
			map->size_y = 3;
			map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			map->flag = FLAG_NO_STAIR | FLAG_NO_MONSTER;
			random_extraction<int> rand_;
			rand_.push(MON_BUTTERFLY, 2);
			rand_.push(MON_SPIDER, 2);
			rand_.push(MON_FIREFLY, 3);
			if (!is_exist_named(MON_WRIGGLE)) {
				map->monster_list.push_back(mapdummy_mon(MON_WRIGGLE, 0, coord_def(0, 0)));
				set_exist_named(MON_WRIGGLE);
			}
			for (rect_iterator rlt2(coord_def(0, 0), 1, 1); !rlt2.end(); rlt2++) {
				if((*rlt2).x != 0 || (*rlt2).y != 0)
					map->monster_list.push_back(mapdummy_mon(rand_.choice(), 0, (*rlt2)));
			}
			map->event_list.push_back(mapdummy_event(EVL_LOCK_DOOR, coord_def(-2, 0), EVT_ALWAYS));
			map->name = "����_����������";
			return  "\
.......\
.=====.\
.=...=.\
.+...=.\
.=...=.\
.=====.\
.......";
		}
		case 50: 
		{
			if (is_exist_named(MON_CHEN))
				break;
			if (!(floor_ >=  5 && floor_ <= 8))
				break;
			bool hw_ = randA(1);
			map->size_x = 2;
			map->size_y = 2;
			map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			if (!is_exist_named(MON_CHEN)) {
				map->event_list.push_back(mapdummy_event(EVL_CHEN, coord_def(0, 0), EVT_ALWAYS));
				set_exist_named(MON_CHEN);
			}
			item_infor t;
			makeitem(ITM_ETC, 0, &t, EIT_CAT_TREE);
			map->item_list.push_back(mapdummy_item(t, coord_def(0, 0)));
			map->name = "þ_���ٷ�����";
			return  "\
.....\
.....\
.....\
.....\
.....";
		}
		case 51:
		{
			if (!(floor_ >= 7 && floor_ <= 14))
				break;
			if (is_exist_named(MON_NAZRIN))
				break;
			map->size_x = 4;
			map->size_y = 4;
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			if (!is_exist_named(MON_NAZRIN)) {
				map->monster_list.push_back(mapdummy_mon(MON_NAZRIN, 0, coord_def(-2, -2)));
				set_exist_named(MON_NAZRIN);
			}
			item_infor t;
			makeitem(ITM_FOOD, 0, &t,2);
			map->item_list.push_back(mapdummy_item(t, coord_def(-2, -2)));
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			map->name = "���_���������";
			return  "\
#########\
#......$#\
#..=....#\
#===....#\
#.......#\
#.......#\
#.......#\
#......T#\
####+####";
			break;
		}
		case 52: //�׽� ������
		{
			if (!(floor_ >= YOUKAI_MOUNTAIN_LEVEL && floor_ <= YOUKAI_MOUNTAIN_LAST_LEVEL))
				break;
			map->size_x = 3;
			map->size_y = 3;
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = 0;
			map->m_exit.x = -map->size_x;
			map->m_exit.y = 0;
			map->flag = FLAG_NO_MONSTER | FLAG_NO_STAIR;
			map->monster_list.push_back(mapdummy_mon(MON_KATPA, 0, coord_def(2, 0)));
			map->monster_list.push_back(mapdummy_mon(MON_KATPA_SPEAR, 0, coord_def(2, -1)));
			map->monster_list.push_back(mapdummy_mon(MON_KATPA_WATER_WIZARD, 0, coord_def(2, 1)));
			map->event_list.push_back(mapdummy_event(EVL_BROKEN_NESI, coord_def(1, 0), EVT_SIGHT));
			map->event_list.push_back(mapdummy_event(EVL_LOCK_DOOR, coord_def(2, 0), EVT_ALWAYS));
			map->name = "�䱫��_�׽ü�����";
			return  "\
$$$$$$$\
$.....$\
$.~~~.$\
+.~~~.$\
$.~~~.$\
$.....$\
$$$$$$$";
		}
		case 53:
		{
			if (!(floor_ >= YOUKAI_MOUNTAIN_LEVEL && floor_ <= YOUKAI_MOUNTAIN_LAST_LEVEL))
				break;
			map->size_x = 4;
			map->size_y = 4;
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;

			map->monster_list.push_back(mapdummy_mon(MON_KATPA, 0, coord_def(-2, 0)));

			random_extraction<int> rand_;
			rand_.push(0);
			rand_.push(1);
			rand_.push(2);
			for (int i = 0; i < 4; i++)
			{
				item_infor t;
				switch(rand_.choice())
				{
				case 0:
					makeitem(ITM_FOOD, 0, &t, 3);
					break;
				case 1:
					makeitem(ITM_ETC, 0, &t, EIT_BROKEN_CAMERA);
					break;
				case 2:
					makeitem(ITM_ETC, 0, &t, EIT_KAPPA_TRASH);
					break;

				}
				map->item_list.push_back(mapdummy_item(t, coord_def(i*2-3, -3)));
			}
			map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
			map->name = "�䱫��_ı�ĸ�Ʈ";
			return  "\
#########\
#.i.i.i.#\
#######+#\
#.......#\
#..=....#\
#===....#\
#.......#\
#......T#\
####+####";
			break;
		}
		case 54:
		{
			if (!(floor_ >= SCARLET_LEVEL && floor_ <= SCARLET_LEVEL_LAST_LEVEL))
				break;
			bool hw_ = randA(1);
			map->size_x = 4;
			map->size_y = 4;
			map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			hw_ = randA(1);
			map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
			map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
			if (randA(1))
			{
				map->monster_list.push_back(mapdummy_mon(MON_VAMPIER_BAT, 0, coord_def(-1, -1)));
				map->monster_list.push_back(mapdummy_mon(MON_VAMPIER_BAT, 0, coord_def(0, 0)));
				map->monster_list.push_back(mapdummy_mon(MON_VAMPIER_BAT, 0, coord_def(1, -1)));
			}
			else
			{
				map->monster_list.push_back(mapdummy_mon(MON_CHUPARCABRA, 0, coord_def(0, 0)));
			}
			map->flag = FLAG_NO_ITEM | FLAG_NO_STAIR;
			map->name = "ȫ����_�ֿϵ���_�츮";
			return  "\
.........\
.........\
..=====..\
..=...=..\
..=...=..\
..=====..\
.........\
.........\
.........";
			break;
		}
		case 55: //���� ������
		{
			if (!(floor_ >= SCARLET_LEVEL && floor_ <= SCARLET_LEVEL_LAST_LEVEL))
				break;
			map->size_x = 3;
			map->size_y = 6;
			map->m_entrance.x = rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = map->size_y;
			map->m_exit.x = rand_int(-map->size_x, map->size_x);
			map->m_exit.y = map->size_y;
			map->flag = FLAG_NO_MONSTER | FLAG_NO_STAIR;
			map->monster_list.push_back(mapdummy_mon(MON_MAGIC_BOOK, 0, coord_def(-2, -5)));
			map->monster_list.push_back(mapdummy_mon(MON_MAGIC_BOOK, 0, coord_def(2, -5)));
			item_infor t;
			makeitem(ITM_BOOK, 0, &t, -1);
			map->item_list.push_back(mapdummy_item(t, coord_def(0, -5)));
			map->name = "ȫ����_����_������";
			return  "\
#######\
#.....#\
#.E.E.#\
#.E.E.#\
#.,.,.#\
#.E.E.#\
#.E.E.#\
#.....#\
#.E.E.#\
#.E.E.#\
#.....#\
#.E.E.#\
#.E.E.#";
		}
		case 56: //�Ŵ��� ���Ա�
		{
			if (!(floor_ >= MISTY_LAKE_LEVEL && floor_ <= MISTY_LAKE_LAST_LEVEL))
				break;
			map->size_x = 10;
			map->size_y = 5;
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = -2;
			map->m_exit.x = map->size_x;
			map->m_exit.y = 4;
			map->flag = FLAG_NO_STAIR;
			map->name = "�Ȱ�ȣ��_�Ŵ���_��";
			return  "\
`````TTTTTTTT````````\
``TTTT......TTTTT````\
`TT.............TT```\
.T.............TT````\
T...........TTTT`````\
T........TTTT````````\
TT......TT```````````\
`TT......TTTTTTTTTT``\
``TTT.............TTT\
````TTTTTTTTT........\
````````````TTTTTTTTT\
";

		}
		case 57: //ȣ��
		{
			if (!(floor_ >= MISTY_LAKE_LEVEL && floor_ <= MISTY_LAKE_LAST_LEVEL))
				break;
			map->size_x = 5;
			map->size_y = 3;
			map->m_entrance.x = 0;
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			map->flag = FLAG_NO_STAIR;
			map->name = "�Ȱ�ȣ��_¡�˴ٸ�";
			return  "\
``~~~.~T~``\
`~~~~~.~~~`\
`~~~~T~.~~~\
`~~~~~.~~~~\
~~~T~.~T~~`\
~~~~.~~~~~`\
``~T~.~~~``";
		}
		case 58:
		{
			if (!(floor_ >= MISTY_LAKE_LEVEL && floor_ <= MISTY_LAKE_LAST_LEVEL))
				break;
			map->size_x = 2;
			map->size_y = 2;
			map->m_entrance.x = rand_int(-map->size_x, map->size_x);
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = rand_int(-map->size_x, map->size_x);
			map->m_exit.y = map->size_y;
			map->name = "�Ȱ�ȣ��_����_��";
			return  "\
T.T.T\
``.``\
T.T.T\
``.``\
T.T.T";
		}
		case 59:
		{
			if (!(floor_ >= MISTY_LAKE_LEVEL && floor_ <= MISTY_LAKE_LAST_LEVEL))
				break;
			map->size_x = 2;
			map->size_y = 2;
			map->m_entrance.x = 1;
			map->m_entrance.y = -map->size_y;
			map->m_exit.x = -1;
			map->m_exit.y = map->size_y;
			map->name = "�Ȱ�ȣ��_����_��";
			return  "\
```.`\
``.T.\
`.TT.\
.TT.`\
`..``";
		}
		case 60: 
		{
			if (!(floor_ >= MISTY_LAKE_LEVEL && floor_ <= MISTY_LAKE_LAST_LEVEL))
				break;
			map->size_x = 4;
			map->size_y = 3;
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			map->name = "�Ȱ�ȣ��_��_����_����";
			return  "\
`TTTTTTT`\
TT.....TT\
T..~~~..T\
T..~~~..T\
T...~...T\
TT.....TT\
`TT...TT`";
		}
		case 61:
		{
			if (!(floor_ >= SCARLET_LEVEL && floor_ <= SCARLET_LEVEL_LAST_LEVEL))
				break;
			map->size_x = 4;
			map->size_y = 3;
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					map->event_list.push_back(mapdummy_event((i+j)%2? EVL_COLD_SMOKE:EVL_FIRE_SMOKE, coord_def(i*2-3, j*2-3), EVT_ALWAYS));
				}
			}
			map->name = "ȫ����_���º���_���ô�";
			return  "\
.........\
..=====..\
..=...=..\
..=.i.=..\
..=...=..\
..==.==..\
.........";
		}
		case 62:
		{
			map->size_x = 4;
			map->size_y = 3;
			map->m_entrance.x = 0;
			map->m_entrance.y = map->size_y;
			map->m_exit.x = 0;
			map->m_exit.y = map->size_y;
			map->name = "�⺻_���̾Ƹ��_��";
			return  "\
```#.#```\
``#...#``\
`#.....#`\
#.......#\
`#.....#`\
``#...#``\
```#.#```";
		}
		case 63:
		{
			map->size_x = 7;
			map->size_y = 2;
			map->m_entrance.x = -map->size_x;
			map->m_entrance.y = rand_int(-map->size_y, map->size_y);
			map->m_exit.x = map->size_x;
			map->m_exit.y = rand_int(-map->size_y, map->size_y);
			map->name = "�⺻_����_�𷡽ð��";
			return  "\
...#`````##....\
....###`.......\
........`#.....\
.....##```#....\
...##``````#...";
		}
		}
	}
	return NULL;
}


char* pande_pattern(map_dummy* map)
{

	switch (randA(21))
	{
	default:
	case 0:
		map->size_x = 3;
		map->size_y = 3;
		map->m_entrance.x = -map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = map->size_x;
		map->m_exit.y = 0;
		map->flag = FLAG_NO_STAIR;
		map->name = "����_X�ڹ�";
		return  "\
###.###\
##...##\
#.#.#.#\
...#...\
#.#.#.#\
##...##\
###.###";
		break;
	case 1:
	{
		bool hw_ = randA(1);
		map->size_x = 5;
		map->size_y = 5;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->flag = FLAG_NO_STAIR;
		map->name = "����_������";
		return  "\
=.=.=.=.=.=\
...........\
=.........=\
...........\
=...m.m...=\
.....M.....\
=...m.m...=\
...........\
=.........=\
...........\
=.=.=.=.=.=";
		break;
	}
	case 2:
		map->size_x = 3;
		map->size_y = 4;
		map->m_entrance.x = 2;
		map->m_entrance.y = -map->size_y;
		map->m_exit.x = -2;
		map->m_exit.y = map->size_y;
		map->flag = FLAG_NO_STAIR;
		map->name = "����_����_������";
	return  "\
#####.#\
#.....#\
#+#####\
#.....#\
#.mMm.#\
#.....#\
#####+#\
#.....#\
#.#####";
	case 3:
	{
		bool hw_ = randA(1);
		map->size_x = 5;
		map->size_y = 5;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		//map->flag = FLAG_NO_STAIR;
		map->name = "����_���̾Ƹ���";
		map->sp_tile_list.clear();
		int rand_ = randA(3);
		for (int i = 0; i < 4; i++) {
			if(rand_ == i)
				map->sp_tile_list.push_back(DG_CLOSE_DOOR);
			else
				map->sp_tile_list.push_back(DG_WALL);
		}
		return  "\
...........\
....#0#....\
...##.##...\
..##.m.##..\
.##.mim.##.\
.3.miiim.1.\
.##.mim.##.\
..##.m.##..\
...##.##...\
....#2#....\
...........";
		break;
	}
	case 4:
	{
		map->size_x = 4;
		map->size_y = 6;
		map->m_entrance.x = -1;
		map->m_entrance.y = map->size_y;
		map->m_exit.x = 1;
		map->m_exit.y = map->size_y;
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_N��";
		return  "\
$$$$$$$$$\
$...M...$\
$.$+++$.$\
$.=...=.$\
$n=...=n$\
$m=...=m$\
$m=...=m$\
$m=...=m$\
$n=...=n$\
$.=...=.$\
$+$...$+$\
$I$...$I$\
$$$...$$$";
		break;
	}
	case 5:
	{
		map->size_x = 7;
		map->size_y = 7;
		map->m_entrance.x = rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = -map->size_y;
		map->m_exit.x = rand_int(-map->size_x, map->size_x);
		map->m_exit.y = -map->size_y;
		map->name = "����_�������";
		return  "\
#.............#\
#.............#\
#.###########.#\
#.#.........#.#\
#.#.#m.m.m#.#.#\
#.#.#.....#.#.#\
#.#.#.###.#.#.#\
#.#.#.#I#.#.#.#\
#.#.#.#M#.#.#.#\
#.#.#.....#.#.#\
#.#.#######.#.#\
#.#.........#.#\
#.#n.n.n.n.n#.#\
#.............#\
###############";
		break;
	}
	case 6:
	{
		bool hw_ = randA(1);
		map->size_x = 7;
		map->size_y = 7;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_������";
		return  "\
...............\
#.....###.....#\
..###.....###..\
#.....###.....#\
..###.....###..\
#.....###.....#\
..###.....###..\
#.....###.....#\
..###.....###..\
#.....###.....#\
..###.....###..\
#.....###.....#\
..###.....###..\
#.....###.....#\
...............";
		break;
	}
	case 7:
	{
		bool hw_ = randA(1);
		map->size_x = 6;
		map->size_y = 6;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_���ڰ�";
		return  "\
.............\
.....#.#.....\
.....#.#.....\
.....#.#.....\
.....#.#.....\
.#####.#####.\
.............\
.#####.#####.\
.....#.#.....\
.....#.#.....\
.....#.#.....\
.....#.#.....\
.............";
		break;
	}
	case 8:
	{
		bool hw_ = randA(1);
		map->size_x = 6;
		map->size_y = 6;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_Ŭ�ι�_������";
		return  "\
.............\
.............\
....#...#....\
...##...##...\
..####+####..\
....#...#....\
....+...+....\
....#...#....\
..####+####..\
...##...##...\
....#...#....\
.............\
.............";
		break;
	}
	case 9:
	{
		bool hw_ = randA(1);
		map->size_x = 6;
		map->size_y = 6;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->flag = FLAG_NO_ITEM | FLAG_NO_STAIR;
		random_extraction<int> rand_ext_;
		rand_ext_.push(0);
		rand_ext_.push(1);
		rand_ext_.push(2);
		rand_ext_.push(3);
		int rand_ = rand_ext_.pop();
		int rand2_ = rand_ext_.pop();
		for (int i = 0; i < 4; i++) {
			if (rand_ == i || rand2_ == i) {
				map->sp_tile_list.push_back(DG_FLOOR);
			}
			else {
				map->sp_tile_list.push_back(DG_SEA);
			}
		}
		for (int i = 4; i < 8; i++) {
			if (rand_+4 == i || rand2_+4 == i) {
				map->sp_tile_list.push_back(DG_CLOSE_DOOR);
			}
			else {
				map->sp_tile_list.push_back(DG_GLASS);
			}
		}
		map->name = "����_����";
		return  "\
.............\
....==4==....\
...==~0~==...\
..==~~0~~==..\
.==~~~0~~~==.\
.=~~~~0~~~~=.\
.51111i33337.\
.=~~~~2~~~~=.\
.==~~~2~~~==.\
..==~~2~~==..\
...==~2~==...\
....==6==....\
.............";
		break;
	}
	case 10:
	{
		bool hw_ = randA(1);
		map->size_x = 7;
		map->size_y = 7;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_����";
		int add_ = randA(6);
		for (int i = 0; i < 7; i++) {
			map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_FLOOR1+((i+ add_)%7)));
		}
		return  "\
666666666666666\
655555555555556\
654444444444456\
654333333333456\
654322222223456\
654321111123456\
654321000123456\
654321000123456\
654321000123456\
654321111123456\
654322222223456\
654333333333456\
654444444444456\
655555555555556\
666666666666666";
		break;
	}
	case 11:
	{
		map->size_x = 7;
		map->size_y = 7;
		map->m_entrance.x = -map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = map->size_x;
		map->m_exit.y = 0;		
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_��������";
		int add_ = randA(6);
		for (int i = 0; i < 7; i++) {
			map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_WALL1 + ((i + add_) % 7)));
		}
		return  "\
000002222244444\
0...02...24...4\
0.m.++.m.++.m.4\
0...02...24...4\
00+0022+2244+44\
11+11.....66+66\
1...1.....6...6\
+.m.+..M..+.m.+\
1...1.....6...6\
11+11.....66+66\
55+5533+3311+11\
5...53...31...1\
5.m.++.m.++.m.1\
5...53...31...1\
555553333311111";
		break;
	}
	case 12:
	{
		bool hw_ = randA(1);
		map->size_x = 4;
		map->size_y = 4;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_ȣ��_����";
		map->sp_tile_list.push_back(randomTemple());
		return  "\
.........\
.........\
..~~~~~..\
..~~~~~..\
..~~0~~..\
..~~~~~..\
..~~~~~..\
.........\
.........";
		break;
	}
	case 13:
	{
		bool hw_ = randA(1);
		map->size_x = 4;
		map->size_y = 4;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_���ٸ���";
		int rand_ = randA(3);
		int rand2_ = randA(6);
		for (int i = 0; i < 4; i++) {
			if (rand_ == i)
				map->sp_tile_list.push_back(DG_CLOSE_DOOR);
			else
				map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_WALL1 + rand2_));
		}
		map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_WALL1 + rand2_));
		map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_FLOOR1 + rand2_));
		return  "\
.........\
.4440444.\
.4555554.\
.4555554.\
.3555551.\
.4555554.\
.4555554.\
.4442444.\
.........";
		break;
	}
	case 14:
	{
		bool hw_ = randA(1);
		map->size_x = 4;
		map->size_y = 4;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_���ٸ���_����";
		int rand_ = randA(3);
		int rand2_ = randA(6);
		for (int i = 0; i < 4; i++) {
			if (rand_ == i)
				map->sp_tile_list.push_back(DG_CLOSE_DOOR);
			else
				map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_WALL1 + rand2_));
		}
		map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_WALL1 + rand2_));
		return  "\
.........\
.4440444.\
.4.....4.\
.4.mmm.4.\
.3.mMm.1.\
.4.mmm.4.\
.4.....4.\
.4442444.\
.........";
		break;
	}
	case 15:
	{
		bool hw_ = randA(1);
		map->size_x = 5;
		map->size_y = 5;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_����������";
		map->event_list.push_back(mapdummy_event(EVL_LOCK_DOOR, coord_def(0, 3), EVT_ALWAYS));
		map->event_list.push_back(mapdummy_event(EVL_LOCK_DOOR, coord_def(0, -2), EVT_ALWAYS));
		return  "\
...........\
..$&&&&&$..\
..$iiiii$..\
..$$$+$$$..\
..$&M.M&$..\
..$m.m.m$..\
..$.mmm.$..\
..$.....$..\
..$$$+$$$..\
...........\
...........";
		break;
	}
	case 16:
		map->size_x = 3;
		map->size_y = 3;
		map->m_entrance.x = 0;
		map->m_entrance.y = -map->size_y;
		map->m_exit.x = 0;
		map->m_exit.y = map->size_y;
		//map->flag = FLAG_NO_STAIR;
		map->name = "����_������_��_��";
		return  "\
###.###\
#.....#\
#..#..#\
#+#=#+#\
#..#..#\
#.....#\
###.###";
		break;
	case 17:
	{
		map->size_x = 7;
		map->size_y = 4;
		map->m_entrance.x = map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = -map->size_x;
		map->m_exit.y = 0;
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_����_���";
		return  "\
===#########===\
=m=#########=M=\
==+.........+==\
##...........##\
.+...........+.\
##...........##\
==+.........+==\
=M=#########=m=\
===#########===";
		break;
	}
	case 18:
	{
		map->size_x = 6;
		map->size_y = 7;
		map->m_entrance.x = rand_int(-1, 1);
		map->m_entrance.y = map->size_y;
		map->m_exit.x = rand_int(-1,1);
		map->m_exit.y = map->size_y;
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		random_extraction<int> rand_ext_;
		rand_ext_.push(0);
		rand_ext_.push(1);
		rand_ext_.push(2);
		rand_ext_.push(3);
		rand_ext_.push(4);
		rand_ext_.push(5);
		rand_ext_.push(6);
		for (int i = 0; i < 3; i++) {
			int rand_ = rand_ext_.pop();
			map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_WALL1 + rand_));
			map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_FLOOR1 + rand_));
		}
		map->name = "����_����ݸ�";
		return  "\
````00000````\
````01110````\
2222011104444\
2333011105554\
233300+005554\
2333+...+5554\
22222...44444\
````#...#````\
````#...#````\
````#...#````\
````#...#````\
````#...#````\
````#...#````\
````#...#````\
````#...#````";
		break;
	}
	case 19:
	{
		map->size_x = 7;
		map->size_y = 5;
		map->m_entrance.x = map->size_x;
		map->m_entrance.y = 0;
		map->m_exit.x = -map->size_x;
		map->m_exit.y = 0;
		//map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_��Ʈ_���";
		return  "\
```````````````\
`$``#######``=`\
````#.....#````\
```##.....##```\
####.......####\
...............\
####.......####\
```##.....##```\
````#.....#````\
`~``#######``&`\
```````````````";
		break;
	}
	case 20:
	{
		bool hw_ = randA(1);
		map->size_x = 4;
		map->size_y = 4;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_�޹�";
		int rand_ = randA(3);
		for (int i = 0; i < 4; i++) {
			if (rand_ == i)
				map->sp_tile_list.push_back(DG_CLOSE_DOOR);
			else
				map->sp_tile_list.push_back((dungeon_tile_type)(DG_WALL2));
		}
		map->sp_tile_list.push_back((dungeon_tile_type)(DG_WALL2));
		return  "\
.........\
..44044..\
.44^^^44.\
.4^d^d^4.\
.3^^D^^1.\
.4^d^d^4.\
.44^^^44.\
..44244..\
.........";
		break;
	}
	case 21:
	{
		bool hw_ = randA(1);
		map->size_x = 6;
		map->size_y = 6;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_������";
		int rand_ = randA(3);
		for (int i = 0; i < 4; i++) {
			if (rand_ == i)
				map->sp_tile_list.push_back(DG_CLOSE_DOOR);
			else
				map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_WALL1));
		}
		map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_WALL1));
		map->sp_tile_list.push_back((dungeon_tile_type)(DG_PANDE_FLOOR1));
		return  "\
.............\
.444.....444.\
.454.....454.\
.45444044454.\
.45555555554.\
.455h555h554.\
.15555H55552.\
.455h555h554.\
.45555555554.\
.45444344454.\
.454.....454.\
.444.....444.\
..............";
		break;
	}
	case 999:
	{
		bool hw_ = randA(1);
		map->size_x = 7;
		map->size_y = 7;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->name = "����_���ø�";
		return  "\
...............\
...............\
...............\
...............\
...............\
...............\
...............\
.......M.......\
...............\
...............\
...............\
...............\
...............\
...............\
...............";
		break;
	}
	}
}






char* temple_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_TEMPLE_STAIR); //0�� ���� �Ա��� ģ��.
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
		map->name = "����_���̾Ƹ��_�Ա�";
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
		map->name = "����_����_�罽�Ա�";
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
		map->name = "����_ȸ�����Ա�";
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
		map->name = "����_�����Ա�";
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
		map->name = "����_�������Ա�";
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
			map->name = "����_ȣ���Ա�";
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
			map->name = "����_����Ա�"; 
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
			map->name = "����_4��_�������Ա�";
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

char* lake_enter_pattern(map_dummy* map)
{
	switch (randA(0))
	{
	default:
	case 0:
		bool hw_ = randA(1);
		map->size_x = 3;
		map->size_y = 3;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->name = "�Ȱ���_ȣ��_�Ա�";
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		rand_rect_iterator rand_coord(coord_def(0, 0), map->size_x-1, map->size_y-1);
		for (int i = 0; i < 10; i++) {
			map->monster_list.push_back(mapdummy_mon(MON_BUSH, 0, (*rand_coord)));
			if ((++rand_coord).end())
				break;
		}
		map->event_list.push_back(mapdummy_event(EVL_SMOKE, coord_def(0, 0), EVT_ALWAYS));
		return "\
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


char* youkai_enter_pattern(map_dummy* map)
{
	switch (randA(0))
	{
	default:
	case 0:
		bool hw_ = randA(1);
		map->size_x = 4;
		map->size_y = 4;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->name = "�䱫��_��_�Ա�";
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		return "\
.........\
...***...\
..*****..\
.***.***.\
.**.0.**.\
.*.....*.\
.**...**.\
..**.**..\
.........";
		break;
	}
}

char* yukkuri_enter_pattern(map_dummy* map)
{
	switch (randA(0))
	{
	default:
	case 0:
		bool hw_ = randA(1);
		map->size_x = 3;
		map->size_y = 3;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->name = "����_��_�Ա�";
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		map->monster_list.push_back(mapdummy_mon(MON_REIMUYUKKURI, 0, coord_def(-1, 0)));
		map->monster_list.push_back(mapdummy_mon(MON_REIMUYUKKURI, 0, coord_def(1, 0)));
		map->monster_list.push_back(mapdummy_mon(MON_MARISAYUKKURI, 0, coord_def(0, -1)));
		map->event_list.push_back(mapdummy_event(EVL_LOCK_DOOR, coord_def(0, 2), EVT_ALWAYS));
		return "\
.......\
.=====.\
.=...=.\
.=.0.=.\
.=...=.\
.==+==.\
.......";
		break;
	}
}


char* dream_enter_pattern(map_dummy* map)
{
	switch (randA(0))
	{
	default:
	case 0:
		bool hw_ = randA(1);
		map->size_x = 3;
		map->size_y = 3;
		map->m_entrance.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_entrance.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		hw_ = randA(1);
		map->m_exit.x = hw_ ? (randA(1) ? -map->size_x : map->size_x) : rand_int(-map->size_x, map->size_x);
		map->m_exit.y = hw_ ? rand_int(-map->size_y, map->size_y) : (randA(1) ? -map->size_y : map->size_y);
		map->name = "����_����_�Ա�";
		map->flag = FLAG_NO_MONSTER | FLAG_NO_ITEM | FLAG_NO_STAIR;
		return "\
....^..\
.^..^.^\
..^^^..\
.^^0^..\
^.^^^^.\
^...^..\
..^...^";
		break;
	}
}


char* misty_lake_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_MISTY_LAKE_STAIR);
	return lake_enter_pattern(map);
}
char* youkai_mountain_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_YOUKAI_MOUNTAIN_STAIR);
	return youkai_enter_pattern(map);
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
	return yukkuri_enter_pattern(map);
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
	return dream_enter_pattern(map);
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
char* zigurrat_pattern(map_dummy* map)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_ZIGURRAT_STAIR);
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
		map->name = "ȫ����_�⺻�Ա�";
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
			int tempx_ = rand_int(5, 6);
			int tempy_ = rand_int(5, 6);
			coord_def c_(hw_?rand_int(-6,6): tempx_*(randA(1)*2-1),hw_? tempy_*(randA(1)*2-1):rand_int(-6,6));
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
		map->name = "�䱫��_�ƾ�_��";
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
		map->name = "�䱫��_���丮_��";
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

		map->name = "ȫ����_�⺻_��";
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


		map->name = "������_�⺻_��";

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
		map->name = "����_����_��";
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

		map->name = "����_���Ἴ��_��";
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
		map->name = "����_�ǵ���Ͼ�_��";
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
		map->name = "����_�⺻_��";
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
		map->name = "�޵���_�⺻_��";
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

			map->name = "����_�⺻_��";
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
			map->name = "������_�⺻_�����";
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