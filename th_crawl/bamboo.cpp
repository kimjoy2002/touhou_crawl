//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bamboo.cpp
//
// 내용: 미궁의 죽림용 ( 어비스 )
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "map.h"
#include "throw.h"
#include "enum.h"
#include "event.h"
#include "smoke.h"
#include "floor.h"
#include "rect.h"


void map_algorithms_bamboo(int num);
void bamboo_count(int num);




void map_algorithms_bamboo(int num)
{
	int d_x = 10, d_y = 10;
	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			if(randA(10)>1)
			{
				env[num].dgtile[x][y].tile = DG_FLOOR;
			}
			else 
				env[num].dgtile[x][y].tile = DG_WALL;
		}
	}
	int x_ = DG_MAX_X/2;
	int y_ = DG_MAX_Y/2;

	env[num].stair_up[0].x = x_;
	env[num].stair_up[0].y = y_;
	env[num].dgtile[x_][y_].tile = DG_FLOOR;


	
	env[num].MakeEvent(EVL_BAMBOO,coord_def(x_,y_),EVT_ALWAYS);

	map_list.bamboo_count=0;
	map_list.bamboo_rate = 0;
}




void bamboo_count(int num)
{ //플레이어가 맵을 벗어날거같으면 바로 중앙으로 끌어온다.
	int offset_x=0, offset_y=0;
	if(you.position.x<8 || you.position.x>DG_MAX_X-9)
		offset_x = DG_MAX_X/2-you.position.x;
	if(you.position.y<8 || you.position.y>DG_MAX_Y-9)
		offset_y = DG_MAX_Y/2-you.position.y;

	if(offset_x || offset_y) //밖을 벗어남
	{
		//움직여야할것. 맵타일, 몬스터위치, 오브젝트위치, 몹의 타겟팅?
		dungeon_tile tempdgtile[DG_MAX_X][DG_MAX_Y];
		for(int i = 0; i < DG_MAX_X; i++)
		{
			for(int j = 0; j < DG_MAX_Y; j++)
			{
				tempdgtile[i][j] = env[num].dgtile[i][j];
			}
		}


		
		for(int i = 0; i < DG_MAX_X; i++)
		{
			for(int j = 0; j < DG_MAX_Y; j++)
			{
				if(offset_x  > i || offset_x  <= i - DG_MAX_X  || offset_y  > j || offset_y  <= j - DG_MAX_Y )
				{  //새로 만들어야하는 맵	
					if(randA(2000)<1)
					{
						env[num].dgtile[i][j].tile = DG_RETURN_STAIR;
						//map_list.bamboo_count;
					}
					else if(randA(10)>1)
					{
						env[num].dgtile[i][j].init();
						env[num].dgtile[i][j].tile = DG_FLOOR;
					}
					else 
					{
						env[num].dgtile[i][j].init();
						env[num].dgtile[i][j].tile = DG_WALL;
					}
				}
				else
				{ //기존 맵이 움직인다.
					int x_ = i - offset_x, y_ = j - offset_y;

					if(x_ >= 0 && x_ < DG_MAX_X && y_ >= 0 && y_ < DG_MAX_Y )
						env[num].dgtile[i][j] = tempdgtile[x_][y_];
					else
					{						
						env[num].dgtile[i][j].init();
						env[num].dgtile[i][j].tile = DG_SEA; //존재해선안됨(디버깅)
					}
				}
			}
		}

		//이제부턴 옮겨진 지형에 맞게 오브젝트들을 전부 이동시킨다.

		//플레이어
		you.offsetmove(coord_def(offset_x,offset_y));
		//몬스터
		for(vector<monster>::iterator it = env[num].mon_vector.begin() ; it != env[num].mon_vector.end() ; it++)
		{
			if((*it).isLive())
			{
				(*it).offsetmove(coord_def(offset_x,offset_y));
			}
		}
		//안개
		for(list<smoke>::iterator it = env[num].smoke_list.begin();it != env[num].smoke_list.end() ;it++)
		{
			(*it).offsetmove(coord_def(offset_x,offset_y));
		}
		//쉐도우는 쓰지않는다.
		env[num].ClearShadow();
		//아이템		(범위에 벗어나면 삭제도 된다.)
		for(list<item>::iterator it =  env[num].item_list.begin();it !=  env[num].item_list.end() ;)
		{
			item *temp = &(*it);
			it++;
			temp->offsetmove(coord_def(offset_x,offset_y));
		}
		//이펙트		필요없엉
		env[num].ClearEffect();
		//땅효과		
		for(list<floor_effect>::iterator it = env[num].floor_list.begin() ; it != env[num].floor_list.end() ; it++)
		{
			(*it).offsetmove(coord_def(offset_x,offset_y));
		}
		//이벤트는... 필요없어?
		//list<events> event_list;


	}

	if(randA(1000)<map_list.bamboo_rate)
	{ //몬스터를 생성하기시작한다.
		
		int rand_ = randA(100);
		int percent_[] = {5,60,15,20};
		int id_ = MON_RABIT_SPEAR;

		if(map_list.bamboo_rate>100)
		{ //토끼들이 많아지면 지원병은 적어짐
			percent_[1] = 65;
			percent_[2] = 5;
			percent_[3] = 25;
		}
		
		if(rand_<percent_[0])
			id_ = MON_RABIT_BOMB;
		else if(rand_<percent_[0]+percent_[1])
			id_ = MON_RABIT_SPEAR;
		else if(rand_<percent_[0]+percent_[1]+percent_[2])
			id_ = MON_RABIT_SUPPORT;
		else if(rand_<percent_[0]+percent_[1]+percent_[2]+percent_[3])
			id_ = MON_RABIT_MAGIC;
			

		dif_rect_iterator rit(you.position,12,true);
		while(!rit.end())
		{
			coord_def check_pos_ = (*rit);

			if(env[num].isMove(check_pos_.x, check_pos_.y, false) && !env[num].isInSight(check_pos_))
			{
				monster *temp = env[num].AddMonster(id_,0,*rit);
				temp->state.SetState(MS_NORMAL);
				break;
			}
			rit++;
		}


	}



	map_list.bamboo_count++;
	if(map_list.bamboo_count % 100 == 20)
		map_list.bamboo_rate = randA(120);
	

}