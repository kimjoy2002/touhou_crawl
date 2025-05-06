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
#include "mon_infor.h"

extern HANDLE mutx;

void map_algorithms_bamboo(int num);
void bamboo_count(int num);




void map_algorithms_bamboo(int num, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex)
{
	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			if(randA(10)>1)
			{
				env[num].dgtile[x][y].tile = floor_tex;
			}
			else 
				env[num].dgtile[x][y].tile = wall_tex;
		}
	}
	int x_ = DG_MAX_X/2;
	int y_ = DG_MAX_Y/2;

	env[num].stair_up[0].x = x_;
	env[num].stair_up[0].y = y_;
	env[num].dgtile[x_][y_].tile = floor_tex;


	env[num].ClearEvent();
	env[num].MakeEvent(EVL_BAMBOO,coord_def(x_,y_),EVT_ALWAYS);
	env[num].MakeEvent(23,coord_def(x_,y_),EVT_SIGHT);

	map_list.bamboo_count=0;
	map_list.bamboo_rate = 0;
}


int create_bamboo_mon() {
	random_extraction<int> percent_;
	percent_.push(MON_RABIT_BOMB,5+max(map_list.bamboo_count/50-10,0));//파밍방지 폭탄병의 수가 점점 많아진다

	if(map_list.bamboo_rate<=200)
	{
		percent_.push(MON_RABIT_SPEAR,60);//창병
		percent_.push(MON_RABIT_SUPPORT,15);//지원병
		percent_.push(MON_RABIT_MAGIC,20);//마법사
	}
	else
	{ //토끼들이 많아지면 지원병은 적어짐
		percent_.push(MON_RABIT_SPEAR,65);//창병
		percent_.push(MON_RABIT_SUPPORT,5);//지원병
		percent_.push(MON_RABIT_MAGIC,25);//마법사

	}
	return percent_.pop();
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
		WaitForSingleObject(mutx, INFINITE);
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
					if(randA(18000 - 15*min(map_list.bamboo_count,1100))<(map_list.bamboo_tewi?2:1))
					{
						env[num].dgtile[i][j].init();
						env[num].dgtile[i][j].tile = DG_EIENTEI_STAIR;

					}
					else if(randA(map_list.bamboo_tewi?2000:4000)<1)
					{
						env[num].dgtile[i][j].init();
						env[num].dgtile[i][j].tile = DG_RETURN_STAIR;
						//map_list.bamboo_count;
					}
					else if(randA(10)>1)
					{
						env[num].dgtile[i][j].init();
						env[num].dgtile[i][j].tile = DG_GRASS;
					}
					else 
					{
						env[num].dgtile[i][j].init();
						env[num].dgtile[i][j].tile = DG_BAMBOO_WALL;
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
				if((*it).offsetmove(coord_def(offset_x,offset_y)) == false)
				{
					if(it->id == MON_TEWI)
					{
						unset_exist_named(MON_TEWI);
					}
				}
			}
		}
		//안개
		for(list<smoke>::iterator it = env[num].smoke_list.begin();it != env[num].smoke_list.end() ;it++)
		{
			(*it).offsetmove(coord_def(offset_x,offset_y));
		}
		//쉐도우는 쓰지않는다.
		env[num].ClearAllShadow();
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

		env[num].allCalculateAutoTile();
		ReleaseMutex(mutx);

	}

	if(randA(500)<1)
	{
		
		if(!is_exist_named(MON_TEWI)){
			dif_rect_iterator rit(you.position,12,true);
			while(!rit.end())
			{
				coord_def check_pos_ = (*rit);

				if(env[num].isMove(check_pos_.x, check_pos_.y, false) && !env[num].isInSight(check_pos_))
				{
					monster *temp = env[num].AddMonster(MON_TEWI,0,coord_def(DG_MAX_X/2,DG_MAX_Y/2));
					temp->state.SetState(MS_NORMAL);
					set_exist_named(MON_TEWI);
					break;
				}
				rit++;
			}
		}
	}

	if(randA(1000)<map_list.bamboo_rate)
	{ //몬스터를 생성하기시작한다.
		
		int id_ = create_bamboo_mon();

		dif_rect_iterator rit(you.position,12,true);
		while(!rit.end())
		{
			coord_def check_pos_ = (*rit);

			if(env[num].isMove(check_pos_.x, check_pos_.y, false) && !env[num].isInSight(check_pos_))
			{
				monster *temp = env[num].AddMonster(id_,0,*rit);
				if(id_ == MON_RABIT_BOMB)
				{
					int level_up_ = min(max(map_list.bamboo_count/300-2,0),10);
					temp->LevelUpdown(level_up_);
				}
				temp->state.SetState(MS_NORMAL);
				break;
			}
			rit++;
		}


	}



	map_list.bamboo_count++;
	if(map_list.bamboo_count % 120 == 20)
	{
		int grade_ = min(map_list.bamboo_count/20,200); //시간이 흐를수록 점점 죽림이 거세진다
		map_list.bamboo_rate = rand_int(60,120)+grade_;

	}
	

}