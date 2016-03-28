//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: event.cpp
//
// 내용: 이벤트 처리에 관한 함수, 클래스 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "event.h"
#include "environment.h"
#include "save.h"
#include "rect.h"
#include "key.h"
#include "mon_infor.h"

int EventOccur(int id, events* event_);

void bamboo_count(int num);

events::events()
:id(0),position(),type(EVT_ABOVE),prev_sight(false)
{
}

events::events(int id_, coord_def position_, event_type type_, int count_)
:id(id_),position(position_),type(type_),prev_sight(false), count(count_)
{
}



void events::SaveDatas(FILE *fp)
{	
	SaveData<int>(fp, id);
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<event_type>(fp, type);
	SaveData<int>(fp, count);
	SaveData<bool>(fp, prev_sight);
}
void events::LoadDatas(FILE *fp)
{
	LoadData<int>(fp, id);
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<event_type>(fp, type);
	LoadData<int>(fp, count);
	LoadData<bool>(fp, prev_sight);
}

int events::action(int delay_)
{
	bool is_sight = false;
	if(env[current_level].isInSight(position))
		is_sight = true; //현재 눈에 보이는지

	if(count>=0)
	{
		count--;
		if(type == EVT_COUNT && count<=0)
		{			
			if(EventOccur(id,this))
				return 0;
		}
	}
	if(type == EVT_SIGHT && is_sight && !prev_sight)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_ABOVE && position == you.position)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_APPROACH_SMALL && distan_coord(position,you.position)<=2)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_APPROACH_MIDDLE && distan_coord(position,you.position)<=10)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_ALWAYS)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(is_sight)
		prev_sight = true;
	else if(prev_sight)
		prev_sight = false;
	return 1;
	
}






int EventOccur(int id, events* event_) //1이 적용하고 끝내기
{
	enterlog();
	switch(id)
	{
	case 1:
		printlog("카나코는 말했다 : 문을 열때는 문 옆에서 O키를, 닫을때는 C키로 닫을 수 있지.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 방향키로 밀어서 자동으로 열기도 한단다.",true,false,false,CL_warning);
		return 1;
	case 2:
		printlog("카나코는 말했다 : 키패드의 방향키나 y u b n키로 대각선을 움직여보자.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : o키를 누르면 탐색 안한 지역으로 자동으로 이동하지.",true,false,false,CL_warning);
		return 1;
	case 3:
		printlog("카나코는 말했다 : ,나 g를 눌러서 아이템을 주워서 장착해보렴.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : w키로 무기, W키로 방어구장착, i키는 설명, d키는 버리기야.",true,false,false,CL_warning);\
		return 1;
	case 4:
		printlog("카나코는 말했다 : 크롤은 언제나 전투의 연속이지, 공격은 직접 부딪히면 돼.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 약한 상대라도 1:1로 싸우는게 유리하니 골목으로 유인하렴.",true,false,false,CL_warning);
		return 1;
	case 5:
		printlog("카나코는 말했다 : 항상 싸움의 후엔 체력을 채우는 습관을 들이렴.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : .키는 1턴휴식을, 5키는 100턴 휴식을 할 수 있어.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 그리고 몬스터가 떨군 P템은 꼭 주워서 파워를 채우도록 해.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 파워는 허기조절, 능력사용, 근접데미지 상승에 도움을 주지.",true,false,false,CL_warning);
		return 1;
	case 6:
		printlog("카나코는 말했다 : 계단을 내려갈때는 >키, 올라올땐 <키로 올라올 수 있어.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 이미 정리한 층에선 볼게 없으니 다음 층으로 내려가자.",true,false,false,CL_warning);
		return 1;
	case 7:
		if(you.power>150)
			you.PowUpDown(-(you.power-150),true);
		printlog("카나코는 말했다 : 파워가 2.00이하가 되면 공격력이 감소해버린단다.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 적을 잡아서 P템을 먹는게 제일 좋지만 음식을 통해서도 회복이 가능하지.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : e키를 눌러서 빵을 먹으면 파워를 회복할 수 있어.",true,false,false,CL_warning);
		return 1;
	case 8:
		printlog("카나코는 말했다 : 원거리 공격은 언제나 편하지. 부적을 주워보렴.",true,false,false,CL_warning);
		return 1;
	case 9:
		printlog("카나코는 말했다 : 원거리 무기를 던질때는 F키를 누르고 던질 템을 골라.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : f키론 준비되어있는 탄막을 바로 던질 수 있단다.",true,false,false,CL_warning);
		return 1;
	case 10:
		printlog("카나코는 말했다 : 효과를 알 수 없는 장신구와 두루마리군. 일단 사용해보자.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 일단 반지를 주워서 P키로 장착해. R키론 벗을 수 있어.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 두루마리를 읽는건 r키야. 선택창이 뜨면 반지에 사용해봐.",true,false,false,CL_warning);
		return 1;
	case 11:
		printlog("카나코는 말했다 : 하하, 허기의 반지는 전혀 도움이 안되지. d키로 버릴 수 있어.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 물약이 보이는군. 물약은 q키로 먹을 수 있어.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 역시 먹기전엔 효과를 알 수 없고 가끔 나쁜 효과도 있지.",true,false,false,CL_warning);
		return 1;
	case 12:
	you.GiveSkillExp(SKT_SPELLCASTING,20,true);
	you.GiveSkillExp(SKT_CONJURE,100,true);
		printlog("카나코는 말했다 : 마법을 배우려면 주문시전스킬이 1렙이상 필요하지.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 일단 책을 주워서 M키로 마법의탄막을 배워보자.",true,false,false,CL_warning);\
		return 1;
	case 13:
		printlog("카나코는 말했다 : 마법을 사용하기위해선 z키나 Z키를 누르고 사용할수있어.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 방법은 부적던지기와 똑같단다! 자 몹을 마법으로 잡아보렴.",true,false,false,CL_warning);
		return 1;
	case 14:
		printlog("카나코는 말했다 : <키로 다시 위층으로 올라갈 수 있어.",true,false,false,CL_warning);
		return 1;
	case 15:
		printlog("신성한 기운이 감돌고 있다.",true,false,false,CL_normal);
		return 1;
	case 16:
		printlog("카나코는 말했다 : 싸우고난 후엔 5키로 휴식 기억하고있지? 독이 걸렸다면 풀어둬.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 제단을 찾으면 위에서 p키로 기도를 할 수 있어.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 내 신전이니까 한번 믿어보렴. 믿고난후 ^키로 설명이 보여.",true,false,false,CL_warning);
		return 1;
	case 17:
		printlog("카나코는 말했다 : a키를 눌러서 권능을 한번 사용해서 싸워보렴.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 권능은 일정 신앙심이 되면 점점 늘어나게되지.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 특히 내 권능은 신앙심을 일정량 소모하니까 주의해서 써.",true,false,false,CL_warning);
		return 1;
	case 18:
		printlog("카나코는 말했다 : 신마다 신앙심을 얻는 방법이 다르고 싫어하는 것도 있단다.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 나의 경우는 적을 죽일때마다 신앙심이 조금씩 오른단다.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 나 같은 경우는 적을 죽이면 자동으로 신앙심이 오르지.",true,false,false,CL_warning);
		return 1;
	case 19:
		printlog("카나코는 말했다 : 요괴 우산이구나. 머리위에 이름이 새겨진 몹은 네임드란다.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 네임드몹은 보통 적보다 강하지. 수단과 방법을 가리지마.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 그동안 나온 아이템과 방법을 활용해서 잡을 수 있을지 시험해보자.",true,false,false,CL_warning);
		return 1;
	case 20:
		printlog("카나코는 말했다 : 튜토리얼은 여기서 끝이란다 사나에.",true,false,false,CL_warning);
		printlog("카나코는 말했다 : 실제 게임에서는 죽음을 두려워하지말거라!",true,false,false,CL_warning);
		return 1;


	case EVL_KISME:
		{
			dif_rect_iterator rit(you.position,2);
			int i = 1; 
			for(;!rit.end() && i> 0;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y) && you.position != (*rit))
				{
					printlog("하늘에서 키스메가 떨어졌다!",true,false,false,CL_small_danger);
					monster *mon_ = env[current_level].AddMonster(MON_KISUME,M_FLAG_EVENT,(*rit));
					mon_->PlusTimeDelay(-mon_->GetWalkDelay()); //키스메는 떨어지고 바로 공격하지않는다.
					MoreWait();
					i--;
				}
			}
		}
		return 1;
	case EVL_SIGHT_P:
		{
			item_infor temp;
			env[current_level].MakeItem(event_->position,makePitem(MON_MOOK, 1, &temp));
		}
		return 1;
	case EVL_FLOOR:
		{			
			env[current_level].dgtile[event_->position.x][event_->position.y].tile = DG_FLOOR;
		}
		return 1;
	case EVL_BAMBOO:
		{			
			bamboo_count(current_level);
		}
		return 0;
	default:
		break;
	}

	return 0;
}