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
#include "skill_use.h"
#include "floor.h"
#include "beam.h"

int EventOccur(int id, events* event_);

void bamboo_count(int num);
void arena_event(int num);
bool skill_summon_namaz2(int power, bool short_, unit* order, coord_def target);

events::events()
:id(0),position(),type(EVT_ABOVE),prev_sight(false), value(0)
{
}

events::events(int id_, coord_def position_, event_type type_, int count_)
:id(id_),position(position_),type(type_), count(count_),prev_sight(false), value(0)
{
	start();
}



void events::SaveDatas(FILE *fp)
{	
	SaveData<int>(fp, id);
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<event_type>(fp, type);
	SaveData<int>(fp, count);
	SaveData<bool>(fp, prev_sight);
	SaveData<int>(fp, value);
}
void events::LoadDatas(FILE *fp)
{
	LoadData<int>(fp, id);
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<event_type>(fp, type);
	LoadData<int>(fp, count);
	LoadData<bool>(fp, prev_sight);
	LoadData<int>(fp, value);
}

int events::start()
{	
	switch(id)
	{
	case EVL_VIOLET:
		{
			int violet_range = min(10, (count+1) / 2) ;
			env[current_level].MakeViolet(position, violet_range, true);
		}
		break;
	case EVL_SANTUARY:
	{
		int santuary_range = min(10, (count + 1) / 2);
		env[current_level].MakeSantuary(position, santuary_range, true);
	}
	break;
	default:
		break;
	}
	return 0;
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
	if(type == EVT_APPROACH_MIDDLE && distan_coord(position,you.position)<=4)
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
	switch (id)
	{
	case 1:
		printlog("카나코는 말했다 : 문을 열때는 문 옆에서 O키를, 닫을때는 C키로 닫을 수 있지.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 방향키로 밀어서 자동으로 열기도 한단다.", true, false, false, CL_warning);
		return 1;
	case 2:
		printlog("카나코는 말했다 : 키패드의 방향키나 y u b n키로 대각선을 움직여보자.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : o키를 누르면 탐색 안한 지역으로 자동으로 이동하지.", true, false, false, CL_warning);
		return 1;
	case 3:
		printlog("카나코는 말했다 : ,나 g를 눌러서 아이템을 주워서 장착해보렴.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : w키로 무기, W키로 방어구장착, i키는 설명, d키는 버리기야.", true, false, false, CL_warning);
		return 1;
	case 4:
		printlog("카나코는 말했다 : 크롤은 언제나 전투의 연속이지, 공격은 직접 부딪히면 돼.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 약한 상대라도 1:1로 싸우는게 유리하니 골목으로 유인하렴.", true, false, false, CL_warning);
		return 1;
	case 5:
		printlog("카나코는 말했다 : 항상 싸움의 후엔 체력을 채우는 습관을 들이렴.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : .키는 1턴 휴식을, 5키는 100턴 휴식을 할 수 있어.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : m키를 눌러서 나오는 창에선 얻은 스킬 투자 방향을 정할 수 있어.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 파워는 허기조절, 능력사용, 근접데미지 상승에 도움을 주지.", true, false, false, CL_warning);
		return 1;
	case 6:
		printlog("카나코는 말했다 : 계단을 내려갈때는 >키, 올라올땐 <키로 올라올 수 있어.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 이미 정리한 층에선 볼게 없으니 다음 층으로 내려가자.", true, false, false, CL_warning);
		return 1;
	case 7:
		if (you.power > 150)
			you.PowUpDown(-(you.power - 150), true);
		printlog("카나코는 말했다 : 파워가 2.00이하가 되면 공격력이 감소해버린단다.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 적을 잡아서 나오는 P템을 먹거나 음식을 통해서 회복이 가능해.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : e키를 눌러서 빵을 먹으면 파워를 회복할 수 있어.", true, false, false, CL_warning);
		return 1;
	case 8:
		printlog("카나코는 말했다 : 원거리 공격은 언제나 편하지. 부적을 주워보렴.", true, false, false, CL_warning);
		return 1;
	case 9:
		printlog("카나코는 말했다 : 원거리 무기를 던질때는 F키를 누르고 던질 템을 골라.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : f키론 준비되어있는 탄막을 바로 던질 수 있단다.", true, false, false, CL_warning);
		return 1;
	case 10:
		printlog("카나코는 말했다 : 효과를 알 수 없는 장신구와 두루마리군. 일단 사용해보자.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 일단 반지를 주워서 P키로 장착해. R키론 벗을 수 있어.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 두루마리를 읽는건 r키야. 선택창이 뜨면 반지에 사용해봐.", true, false, false, CL_warning);
		return 1;
	case 11:
		printlog("카나코는 말했다 : 하하, 허기의 반지는 전혀 도움이 안되지. d키로 버릴 수 있어.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 물약이 보이는군. 물약은 q키로 먹을 수 있어.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 역시 먹기전엔 효과를 알 수 없고 가끔 나쁜 효과도 있지.", true, false, false, CL_warning);
		return 1;
	case 12:
		you.GiveSkillExp(SKT_SPELLCASTING, 20, true);
		you.GiveSkillExp(SKT_CONJURE, 100, true);
		printlog("카나코는 말했다 : 마법을 배우려면 책에서 주문을 먼저 배워야하지.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 일단 책을 주워서 M키로 마법의탄막을 배워보자.", true, false, false, CL_warning); \
			return 1;
	case 13:
		printlog("카나코는 말했다 : 마법을 사용하기위해선 z키나 Z키를 누르고 사용할수있어.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 방법은 부적던지기와 똑같단다! 자 몹을 마법으로 잡아보렴.", true, false, false, CL_warning);
		return 1;
	case 14:
		printlog("카나코는 말했다 : <키로 다시 위층으로 올라갈 수 있어.", true, false, false, CL_warning);
		return 1;
	case 15:
		printlog("신성한 기운이 감돌고 있다.", true, false, false, CL_normal);
		return 1;
	case 16:
		printlog("카나코는 말했다 : 싸우고난 후엔 5키로 휴식 기억하고있지? 독이 걸렸다면 풀어둬.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 제단을 찾으면 위에서 p키로 기도를 할 수 있어.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 내 신전이니까 한번 믿어보렴. 믿고난후 ^키로 설명이 보여.", true, false, false, CL_warning);
		return 1;
	case 17:
		printlog("카나코는 말했다 : a키를 눌러서 권능을 한번 사용해서 싸워보렴.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 권능은 일정 신앙심이 되면 점점 늘어나게되지.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 특히 내 권능은 신앙심을 일정량 소모하니까 주의해서 써.", true, false, false, CL_warning);
		return 1;
	case 18:
		printlog("카나코는 말했다 : 신마다 신앙심을 얻는 방법이 다르고 싫어하는 것도 있단다.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 나의 경우는 적을 죽일때마다 신앙심이 조금씩 오른단다.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 나 같은 경우는 적을 죽이면 자동으로 신앙심이 오르지.", true, false, false, CL_warning);
		return 1;
	case 19:
		printlog("카나코는 말했다 : 요괴 우산이구나. 머리위에 이름이 새겨진 몹은 네임드란다.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 네임드몹은 보통 적보다 강하지. 수단과 방법을 가리지마.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 그동안 나온 아이템과 방법을 활용해서 잡을 수 있을지 시험해보자.", true, false, false, CL_warning);
		return 1;
	case 20:
		printlog("카나코는 말했다 : 튜토리얼은 여기서 끝이란다 사나에.", true, false, false, CL_warning);
		printlog("카나코는 말했다 : 실제 게임에서는 죽음을 두려워하지말거라!", true, false, false, CL_warning);
		return 1;
	case 21:
		printlog("강력한 광기가 느껴진다. 지금이라도 도망쳐!", true, false, false, CL_small_danger);
		return 1;
	case 22:
		printlog("여긴 분명 만들다 말았군. 못된 제작자 놈!", true, false, false, CL_help);
		return 1;
	case 23:
		printlog("이 곳은 끔찍한 미궁이군! 출구를 찾아야 한다. 아니면 새로운 장소를 찾을지도..?", true, false, false, CL_small_danger);
		return 1;
	case 24:
		return 1;
	case 25:
		printlog("동방크롤에선 모든 무기를 한손이나 양손으로 들 수 있습니다.", true, false, false, CL_warning);
		printlog("단, 몇몇 무기는 양손으로 들때 효율이 많이 떨어집니다.", true, false, false, CL_warning);
		printlog("단검은 양손으로 써도 패널티가 없지만 다우징은 양손시 큰 패널티가 있습니다.", true, false, false, CL_warning);
		return 1;
	case 26:
		printlog("몸통방어구엔 재질과 종류로 나뉘어있고 그외엔 보조방어구와 방패가 있습니다.", true, false, false, CL_warning);
		printlog("갑옷엔 재질에 따라 장비패널티가 존재하여 합산되어 우측창에 표시됩니다.", true, false, false, CL_warning);
		return 1;
	case 27:
		you.GiveSkillExp(SKT_ARMOUR, 1200, true);
		you.GiveSkillExp(SKT_SHIELD, 300, true);
		printlog("이 장비패널티는 힘과 갑옷,방패 스킬에 따라 감소됩니다.", true, false, false, CL_warning);
		printlog("자세한 수치나 정도는 i를 눌러서 자세한 수치를 확인해보세요.", true, false, false, CL_warning);
		return 1;
	case 28:
		printlog("동방크롤엔 활이나 블로우건같은 원거리 무기가 없지만 모두 손으로 던질 수 있습니다.", true, false, false, CL_warning);
		printlog("투척용단검, 투척용창, 철륜은 무기로도 쓸 수 있지만 투척용으로도 사용가능합니다.", true, false, false, CL_warning);
		printlog("소모성 탄막과 투척용 무기 모두 탄막 스킬에 영향을 받습니다.", true, false, false, CL_warning);
		return 1;
	case 29:
		printlog("동방크롤엔 허기의 개념이 없는 대신에 비슷한 P라는 게이지가 존재합니다.", true, false, false, CL_warning);
		printlog("아사는 존재하지않는 대신 2칸이하로 떨어지면 전투패널티가 있습니다.", true, false, false, CL_warning);
		printlog("모든 적은 일정확률로 P템을 떨어뜨리며 이것을 주으면 P가 회복됩니다.", true, false, false, CL_warning);
		return 1;
	case 30:
		printlog("스펠카드는 돌죽의 완드를 대체하는 아이템입니다.", true, false, false, CL_warning);
		printlog("{발동}이 붙은 템은 P를 소모하여 발동하는 영구적인 비소모발동템입니다.", true, false, false, CL_warning);
		printlog("둘다 V로 발동이 가능하며 발동스킬에 영향을 받아 강력해집니다.", true, false, false, CL_warning);
		return 1;
	case 31:
		printlog("부적은 돌죽의 아뮬렛에 대체되는 아이템입니다.", true, false, false, CL_warning);
		printlog("낀 즉시 효과는 없지만 끼고 몬스터를 잡으면 퍼센티지가 채워집니다.", true, false, false, CL_warning);
		printlog("100%가 되면 V키로 효과를 사용가능합니다. 일부는 끼기만 해도 효과가 있습니다.", true, false, false, CL_warning);
		return 1;
	case 32:
		printlog("동방크롤엔 총 10개의 룬이 있고 조트의 방을 대체하는 하쿠레이 신사가 존재하여", true, false, false, CL_warning);
		printlog("조트의 오브를 대체하는 음양옥이란 템을 주워서 탈출하면 게임에서 승리합니다.", true, false, false, CL_warning);
		printlog("모자란 게임이지만 잘 부탁드립니다.", true, false, false, CL_warning);
		return 1;
	case EVL_KISME:
	{
		dif_rect_iterator rit(you.position, 2);
		int i = 1;
		for (; !rit.end() && i > 0; rit++)
		{
			if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_KISME_DROP), true, false, false, CL_small_danger);
				monster *mon_ = env[current_level].AddMonster(MON_KISUME, M_FLAG_EVENT, (*rit));
				mon_->SetStrong(5);
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
		env[current_level].MakeItem(event_->position, makePitem(MON_MOOK, 1, &temp));
	}
	return 1;
	case EVL_FLOOR:
	{
		env[current_level].changeTile(event_->position, env[current_level].base_floor);
	}
	return 1;
	case EVL_DREAM_FLOOR:
	{
		env[current_level].changeTile(event_->position, DG_DREAM_FLOOR);
	}
	return 1;
	case EVL_BAMBOO:
	{
		bamboo_count(current_level);
	}
	return 0;
	case EVL_LUNATICTIME:
	{
		for (int i = -3; i <= 3; i++)
		{
			if (i != 0)
				env[current_level].changeTile(coord_def(event_->position.x + i, event_->position.y + 1), env[current_level].base_floor);
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				env[current_level].changeTile(coord_def(event_->position.x + 4 * (j * 2 - 1), event_->position.y + i * 2), DG_OPEN_DOOR);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i != 1 || j != 1)
					env[current_level].changeTile(coord_def(event_->position.x - 1 + i, event_->position.y + 4 + j), DG_GLASS);
			}
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_LUNATIC_TIME), true, false, false, CL_small_danger);
		env[current_level].MakeNoise(event_->position, 16, NULL);
		you.resetLOS();
		MoreWait();
	}
	return 1;
	case EVL_KOGASA:
	{
		dif_rect_iterator rit(you.position, 2);
		int i = 1;
		for (; !rit.end() && i > 0; rit++)
		{
			if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_KOGASA_DROP), true, false, false, CL_small_danger);
				monster *mon_ = env[current_level].AddMonster(MON_KOGASA, M_FLAG_EVENT, (*rit));
				MoreWait();
				printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_KOGASA_DROP2), true, false, false, CL_normal);
				mon_->SetConfuse(5 + randA(5));
				mon_->SetStrong(5);
				mon_->hp = mon_->hp * 2 / 3;
				i--;
			}
		}
	}
	return 1;
	case EVL_NOISE:
	{
		env[current_level].MakeNoise(event_->position, 8, NULL);
	}
	return 1;
	case EVL_VIOLET:
	{
		int prev_range = min(10, (event_->count + 2) / 2);
		int violet_range = min(10, (event_->count + 1) / 2);
		if (event_->count <= 0)
		{
			env[current_level].MakeViolet(event_->position, prev_range, false);
			return 1;
		}
		else if (prev_range != violet_range)
		{
			env[current_level].MakeViolet(event_->position, prev_range, false);
			env[current_level].MakeViolet(event_->position, violet_range, true);
		}
	}
	return 0;
	case EVL_SANTUARY:
	{
		int prev_range = min(10, (event_->count + 2) / 2);
		int santuary_range = min(10, (event_->count + 1) / 2);
		if (event_->count <= 0)
		{
			env[current_level].MakeSantuary(event_->position, prev_range, false);
			return 1;
		}
		else if (prev_range != santuary_range)
		{
			env[current_level].MakeSantuary(event_->position, prev_range, false);
			env[current_level].MakeSantuary(event_->position, santuary_range, true);
		}
	}
	return 0;
	case EVL_DREAM_MONSTER:
	{
		int arr_[] = { MON_MAC, MON_NIGHTMARE, MON_LUNATIC, MON_BLUE_UFO, MON_MOON_RABIT_ATTACK, MON_MOON_RABIT_SUPPORT, MON_SHEEP
		};
		rand_rect_iterator rit(event_->position, 3, 3);
		int mon_id_ = arr_[randA(6)];
		int i = mon_id_ == MON_SHEEP ? rand_int(3, 4) : (mon_id_ == MON_BLUE_UFO ? 3 : 1);
		int base_ = i;
		for (; !rit.end() && i > 0; rit++)
		{
			if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
			{
				monster *mon_ = env[current_level].AddMonster(mon_id_, 0, (*rit));
				mon_->SetStrong(base_>1?1:3);
				i--;
			}
		}
	}
	return 1;
	case EVL_DREAM_MESSAGE:
	{
		int i = 0;
		for (list<events>::iterator it = env[current_level].event_list.begin(); it != env[current_level].event_list.end(); it++)
		{
			if (it->id == EVL_DREAM_MESSAGE)
				i++;
		}
		switch (i)
		{
		case 5:
			you.resetLOS();
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_DREAM_OPEN1), true, false, false, CL_danger);
			MoreWait();
			break;
		case 4:
			you.resetLOS();
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_DREAM_OPEN2), true, false, false, CL_danger);
			MoreWait();
			break;
		case 3:
			you.resetLOS();
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_DREAM_OPEN3), true, false, false, CL_danger);
			MoreWait();
			break;
		case 2:
			you.resetLOS();
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_DREAM_OPEN4), true, false, false, CL_danger);
			MoreWait();
			break;
		case 1:
			for (int k = 3; k < DG_MAX_X - 3; k++)
			{
				for (int h = 3; h < DG_MAX_Y - 3; h++)
				{
					if (env[current_level].dgtile[k][h].tile == DG_WALL2)
						env[current_level].changeTile(coord_def(k, h), env[current_level].base_floor);
				}
			}
			{
				for (int i = 0; i < DG_MAX_X; i++)
					for (int j = 0; j < DG_MAX_Y; j++)
						env[current_level].magicmapping(i, j);
			}
			while (1)
			{
				int x_ = randA(DG_MAX_X - 1), y_ = randA(DG_MAX_Y - 1);
				if (!env[current_level].isInSight(coord_def(x_, y_)) && env[current_level].dgtile[x_][y_].isFloor() && !(env[current_level].dgtile[x_][y_].flag & FLAG_NO_STAIR))
				{
					env[current_level].changeTile(coord_def(x_, y_), DG_MOON_STAIR);
					env[current_level].stair_vector.push_back(stair_info(coord_def(x_, y_), MOON_LEVEL));
					rand_rect_iterator rect_it(coord_def(x_,y_),1,1);


					while (!rect_it.end()) {
						env[current_level].changeTile((*rect_it), DG_DREAM_FLOOR2);
						rect_it++;
					}



					beam_iterator beam(coord_def(x_, y_), you.position);

					beam.init();
					while (!beam.end()) {
						env[current_level].changeTile((*beam), DG_DREAM_FLOOR2);
						beam++;
					}
					env[current_level].changeTile((*beam), DG_DREAM_FLOOR2);


					if (!is_exist_named(MON_DOREMI)) {
						monster *mon_ = env[current_level].AddMonster(MON_DOREMI, M_FLAG_EVENT, coord_def(x_, y_));
						mon_->SetStrong(5); 
						set_exist_named(MON_DOREMI);
					}

					break;
				}
			}
			you.resetLOS();
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_DREAM_OPEN5), true, false, false, CL_danger);
			MoreWait();
			env[current_level].MakeEvent(EVL_REGEN, coord_def(0, 0), EVT_ALWAYS, 30);
			break;
		}
	}
	return 1;
	case EVL_AGRO:
		if (event_->count <= 0)
		{
			for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
			{
				if (it->isLive())
				{
					it->AttackedTarget(&you);
				}
			}
		}
		return 1;
	case EVL_REGEN:
	{
		float multi_ = 0.0f;
		if (int penalty_turn_ = you.CheckPeanltyTurn(current_level))
		{
			//1000부터 시작해서 5000턴부터 몬스터 2배
			if (penalty_turn_ >= 1000) {
				multi_ += min(penalty_turn_ - 1000, 4000) / 4000.0f;
			}
		}
		if (randA(12-5*multi_) == 0)
		{
			int arr_[] = { MON_MAC, MON_NIGHTMARE, MON_LUNATIC, MON_BLUE_UFO, MON_MOON_RABIT_ATTACK, MON_MOON_RABIT_SUPPORT
			};
			int mon_id_ = arr_[randA(5)];

			while (1)
			{
				int x_ = randA(DG_MAX_X - 1), y_ = randA(DG_MAX_Y - 1);
				if (env[current_level].isMove(x_, y_) && !env[current_level].isMonsterPos(x_, y_) && !env[current_level].isInSight(coord_def(x_, y_)))
				{
					monster *mon_ = env[current_level].AddMonster(mon_id_, 0, coord_def(x_, y_));
					mon_->SetStrong(1);
					mon_->AttackedTarget(&you);
					break;
				}
			}

		}

	}
		return 0;
	case EVL_REGEN2:
	{
		float multi_ = 0.0f;
		if (int penalty_turn_ = you.CheckPeanltyTurn(current_level))
		{
			//1000부터 시작해서 5000턴부터 몬스터 2배
			if (penalty_turn_ >= 1000) {
				multi_ += min(penalty_turn_ - 1000, 4000) / 4000.0f;
			}
		}
		if (randA(50-25*multi_) == 0)
		{
			int arr_[] = { MON_HELL_SPIDER, MON_BLOOD_HAUNT, MON_LANTERN_YOUKAI, MON_HELL_HOUND, MON_ONI, MON_BLUE_ONI
			};
			int mon_id_ = arr_[randA(5)];

			while (1)
			{
				int x_ = randA(DG_MAX_X - 1), y_ = randA(DG_MAX_Y - 1);
				if (env[current_level].isMove(x_, y_) && !env[current_level].isMonsterPos(x_, y_) && !env[current_level].isInSight(coord_def(x_, y_)))
				{
					monster *mon_ = env[current_level].AddMonster(mon_id_, 0, coord_def(x_, y_));
					mon_->SetStrong(1);
					mon_->state.SetState(MS_NORMAL);
					break;
				}
			}

		}
	}
	return 0;
	case EVL_ARENA:
	{
		arena_event(current_level);
	}
	return 0;
	case EVL_NAMAZ:
	{
		int power = min(SpellCap(SPL_SUMMON_NAMAZ), you.GetSpellPower(SpellSchool(SPL_SUMMON_NAMAZ, 0), SpellSchool(SPL_SUMMON_NAMAZ, 1), SpellSchool(SPL_SUMMON_NAMAZ, 2)));
		skill_summon_namaz2(power, false, &you, event_->position);
		return 1;
	}
	return 0;
	case EVL_KOISHI:
	{
		if (event_->count == -1)
		{
			event_->type = EVT_ALWAYS;
			event_->count = 11;
		}
		if (event_->count == 10)
		{
			enterlog();
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_MARY_SAN1), true, false, false, CL_small_danger);
			MoreWait();
			you.SetInter(IT_EVENT);
		}
		if (event_->count == 5)
		{
			enterlog();
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_MARY_SAN2), true, false, false, CL_small_danger);
			MoreWait();
			you.SetInter(IT_EVENT);
		}
		if (event_->count == 0)
		{

			dif_rect_iterator rit(you.position, 2);
			int i = 1;
			for (; !rit.end() && i > 0; rit++)
			{
				if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
				{
					enterlog();
					printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_MARY_SAN3), true, false, false, CL_danger);
					MoreWait();
					monster *mon_ = env[current_level].AddMonster(MON_KOISHI, M_FLAG_EVENT, (*rit));
					mon_->PlusTimeDelay(-mon_->GetWalkDelay()); //코이시는 떨어지고 바로 공격하지않는다.
					mon_->SetStrong(5);
					mon_->SetHaste(20 + randA(20));
					return 1;
				}
			}
			enterlog();
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_MARY_SAN_FAIL), true, false, false, CL_small_danger); //코이시 등장실패
			MoreWait();
			return 1;
		}
	}
	return 0;
	case EVL_KYOKO:
	{
		monster *kyoko_ = env[current_level].AddMonster(MON_KYOUKO, M_FLAG_EVENT, coord_def(0, -5) + event_->position);

		kyoko_->SetStrong(5);
		for (int i = rand_int(2, 4); i > 0; i--)
		{
			item_infor temp;
			env[current_level].MakeItem(coord_def(rand_int(-1, 1), rand_int(-5, -3)) + event_->position, makePitem(MON_HUMAM_MAN, 1, &temp));
		}

		dif_rect_iterator rit(coord_def(0, -3) + event_->position, 1);
		int i = rand_int(2, 4);
		for (; !rit.end() && i > 0; rit++)
		{
			if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
			{
				monster *mon_ = env[current_level].AddMonster(MON_HUMAM_MAN, M_FLAG_EVENT | M_FLAG_NETURALY, (*rit));
				mon_->hp = mon_->hp*rand_int(3, 9) / 10;
				mon_->FoundTarget(kyoko_, mon_->FoundTime());
				mon_->s_fear = 20 + randA(20);
				mon_->SetStrong(1);
				i--;
			}
		}
		kyoko_->CheckSightNewTarget();
	}
	return 1;
	case EVL_AUTUMN:
	{
		int rand_ = randA(1);
		env[current_level].MakeFloorEffect(event_->position, &img_effect_autumn_leave[rand_ * 2], &img_effect_autumn_leave[rand_ * 2 + 1], FLOORT_AUTUMN, rand_int(50, 100), NULL);
	}
	return 1;
	case EVL_SUKIMA:
	{
		textures* t_ = &img_effect_schema[randA(2)];
		env[current_level].MakeFloorEffect(event_->position, t_, t_, FLOORT_SCHEMA, 2, NULL);
	}
	return 0;
	case EVL_RUN_FAIRY:
	{
		monster *sunny_ = env[current_level].AddMonster(MON_SUNNY, M_FLAG_EVENT, coord_def(1, 0) + event_->position);
		monster *star_ = env[current_level].AddMonster(MON_STAR, M_FLAG_EVENT, coord_def(-1, 0) + event_->position);
		monster *lunar_ = env[current_level].AddMonster(MON_LUNAR, M_FLAG_EVENT, coord_def(0, 0) + event_->position);

		sunny_->SetStrong(5);
		star_->SetStrong(5);
		lunar_->SetStrong(5);
		sunny_->s_fear = 30 + randA(20);
		star_->s_fear = 30 + randA(20);
		lunar_->s_fear = 30 + randA(20);
		LocalzationManager::printLogWithKey(LOC_SYSTEM_EVENT_RUN_TRHEEFAIRY,true,false,false,CL_speak,
			 PlaceHolderHelper(star_->GetName()->getName()));
		sunny_->SetInvisible(10);
		lunar_->s_confuse = 5;
		star_->SetHaste(10);

	}
	return 1;
	case EVL_SCALET_TRAP:
	{
		env[current_level].changeTile(coord_def(event_->position.x - 4, event_->position.y + 1), DG_OPEN_DOOR);
		env[current_level].changeTile(coord_def(event_->position.x - 2, event_->position.y + 1), DG_OPEN_DOOR);
		env[current_level].changeTile(coord_def(event_->position.x - 4, event_->position.y - 1), DG_OPEN_DOOR);
		env[current_level].changeTile(coord_def(event_->position.x - 2, event_->position.y - 1), DG_OPEN_DOOR);

		env[current_level].changeTile(coord_def(event_->position.x + 1, event_->position.y), DG_GLASS);

		printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_SCALET_TRAP), true, false, false, CL_small_danger);
		env[current_level].MakeNoise(event_->position, 8, NULL);
	}
	return 1;
	case EVL_KOGASATIME:
	{
		for (int i = -3; i <= 3; i++)
		{
			if (i != 0)
				env[current_level].changeTile(coord_def(event_->position.x + i, event_->position.y + 1), env[current_level].base_floor);
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				env[current_level].changeTile(coord_def(event_->position.x + 4 * (j * 2 - 1), event_->position.y + i * 2), DG_OPEN_DOOR);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i != 1 || j != 1)
					env[current_level].changeTile(coord_def(event_->position.x - 1 + i, event_->position.y + 4 + j), DG_GLASS);
			}
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_KOGASA_TIME1), true, false, false, CL_small_danger);
		env[current_level].MakeNoise(event_->position, 16, NULL);
		you.resetLOS();
		MoreWait();
		printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_KOGASA_TIME2), true, false, false, CL_normal);
	}
	return 1;
	case EVL_HOJOK:
	{
		unit* target_unit = env[current_level].isMonsterPos(event_->position.x - 4, event_->position.y - 1);
		if (target_unit)
		{
			env[current_level].changeTile(coord_def(event_->position.x - 4, event_->position.y), env[current_level].base_floor);
			env[current_level].changeTile(coord_def(event_->position.x - 3, event_->position.y), env[current_level].base_floor);
			env[current_level].changeTile(coord_def(event_->position.x - 3, event_->position.y - 1), env[current_level].base_floor);

			you.resetLOS();
			LocalzationManager::printLogWithKey(LOC_SYSTEM_EVENT_HOJOK1,true,false,false,CL_speak,
				 PlaceHolderHelper(target_unit->GetName()->getName()));
			target_unit->PlusTimeDelay(-target_unit->GetWalkDelay());
			if (!target_unit->isplayer()) {
				((monster*)target_unit)->FoundTarget(&you, ((monster*)target_unit)->FoundTime());
			}
		}
		target_unit = env[current_level].isMonsterPos(event_->position.x + 4, event_->position.y - 1);
		if (target_unit)
		{
			env[current_level].changeTile(coord_def(event_->position.x + 4, event_->position.y), env[current_level].base_floor);
			env[current_level].changeTile(coord_def(event_->position.x + 3, event_->position.y), env[current_level].base_floor);
			env[current_level].changeTile(coord_def(event_->position.x + 3, event_->position.y - 1), env[current_level].base_floor);

			you.resetLOS();
			LocalzationManager::printLogWithKey(LOC_SYSTEM_EVENT_HOJOK2,true,false,false,CL_speak,
				 PlaceHolderHelper(target_unit->GetName()->getName()));
			target_unit->PlusTimeDelay(-target_unit->GetWalkDelay());
			if (!target_unit->isplayer())
				((monster*)target_unit)->FoundTarget(&you, ((monster*)target_unit)->FoundTime());
		}
		return 1;
	}
	case EVL_KOGASA3:
	{
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
				env[current_level].MakeSmoke(coord_def(i + event_->position.x, j + event_->position.y), img_fog_dark, SMT_DARK, rand_int(3, 4), 0, NULL);
		if (distan_coord(you.position, event_->position) <= 2) {
			monster *mon_ = env[current_level].AddMonster(MON_KOGASA, M_FLAG_EVENT, event_->position);
			
			LocalzationManager::printLogWithKey(LOC_SYSTEM_EVENT_KOGASA_SMOKE1,true,false,false,CL_speak,
				PlaceHolderHelper(mon_->GetName()->getName()));
			env[current_level].MakeNoise(event_->position, 12, NULL);
			you.resetLOS();
			MoreWait();
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_KOGASA_TIME2), true, false, false, CL_normal);
			mon_->SetSlow(rand_int(30, 40));
			mon_->SetStrong(5);
			return 1;
		}
		return 0;
	}
	case EVL_MEDI:
	{
		for (rect_iterator rlt(event_->position, 1, 1); !rlt.end(); rlt++) {
			if (env[current_level].isInSight((*rlt)))
			{
				monster *medi_ = env[current_level].AddMonster(MON_MEDICINE, M_FLAG_EVENT, event_->position);

				medi_->SetStrong(5);
				medi_->PlusTimeDelay(-4 * medi_->GetWalkDelay());
				for (rect_iterator rlt2(event_->position, 1, 1); !rlt2.end(); rlt2++) {
					if ((*rlt2) != event_->position)
					{
						random_extraction<int> rand_;
						rand_.push(MON_CROW);
						rand_.push(MON_FAIRY_GREEN);
						rand_.push(MON_FAIRY_BLUE);
						rand_.push(MON_FAIRY_RED);
						rand_.push(MON_KATPA);
						monster *mon_ = env[current_level].AddMonster(rand_.pop(), M_FLAG_EVENT | M_FLAG_NETURALY, (*rlt2));

						mon_->FoundTarget(medi_, mon_->FoundTime());
						mon_->s_poison = 100;
						mon_->SetPoisonReason(PRT_NEUTRAL);
						mon_->s_fear = 20 + randA(20);
						mon_->SetStrong(1);
					}

				}
				return 1;
			}
		}
		return 0;
	}
	case EVL_LOCK_DOOR:
	{
		env[current_level].dgtile[event_->position.x][event_->position.y].flag |= FLAG_DONT_DOOR;
		return 1;
	}
	case EVL_SMOKE:
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (randA(6) == 0)
					env[current_level].MakeSmoke(coord_def(i + event_->position.x, j + event_->position.y), img_fog_normal, SMT_FOG, rand_int(3, 4), 0, NULL);
			}
		}
		return 0;
	}
	case EVL_CHEN:
	{
		for (rect_iterator rlt(event_->position, 1, 1); !rlt.end(); rlt++) {
			if (env[current_level].isInSight((*rlt)))
			{
				monster *chen_ = env[current_level].AddMonster(MON_CHEN, M_FLAG_EVENT, event_->position);

				chen_->SetStrong(5);
				chen_->s_confuse = 15;
				for (rect_iterator rlt2(event_->position, 1, 1); !rlt2.end(); rlt2++) {
					if ((*rlt2).x != event_->position.x && (*rlt2).y != event_->position.y)
					{
						random_extraction<int> rand_;
						rand_.push(MON_ORANGE_CAT);
						rand_.push(MON_BLACK_CAT);
						rand_.push(MON_WHITE_CAT);
						monster *mon_ = env[current_level].AddMonster(rand_.pop(), M_FLAG_EVENT, (*rlt2));

						mon_->SetStrong(1); 
						mon_->s_confuse = 15;
					}
				}
				return 1;
			}
		}
		return 0;
	}
	case EVL_BROKEN_NESI:
	{
		monster *nesi_ = env[current_level].AddMonster(MON_NESI, M_FLAG_EVENT, event_->position);
		nesi_->s_confuse = -1;
		nesi_->exper = nesi_->exper / 2;
		nesi_->SetStrong(1);
		return 1;
	}
	case EVL_FIRE_SMOKE:
	{
		if (event_->count % 2)
			env[current_level].MakeSmoke(coord_def(event_->position.x, event_->position.y), img_fog_fire, SMT_FIRE, rand_int(3, 4), 0, NULL);
		return 0;
	}
	case EVL_COLD_SMOKE:
	{
		if (event_->count % 2)
			env[current_level].MakeSmoke(coord_def(event_->position.x, event_->position.y), img_fog_cold, SMT_COLD, rand_int(3, 4), 0, NULL);
		return 0;
	}
	case EVL_SILENCE:
	{
		int prev_range = min(10, (event_->count + 2) / 2);
		int silence_range = min(10, (event_->count + 1) / 2);
		if (event_->count <= 0)
		{
			env[current_level].MakeSilence(event_->position, prev_range, false);
			return 1;
		}
		else if (prev_range != silence_range)
		{
			env[current_level].MakeSilence(event_->position, prev_range, false);
			env[current_level].MakeSilence(event_->position, silence_range, true);
		}
		return 0;
	}
	case EVL_WATER:
	{
		if (env[current_level].dgtile[event_->position.x][event_->position.y].tile != DG_SEA)
		{
			event_->value = env[current_level].dgtile[event_->position.x][event_->position.y].tile;
			env[current_level].changeTile(event_->position, DG_SEA);
		}
		else if (event_->count <= 0)
		{
			env[current_level].changeTile(event_->position, event_->value ? (dungeon_tile_type)event_->value : DG_SEA);
			return 1;
		}
		return 0;
	}
	case EVL_SION_DELETE:
	{
		int num = 0;
		bool isplural = false;
		string str_ = LocalzationManager::locString(LOC_SYSTEM_EVENT_SION_ITEM);
		list<item>::iterator it, first_it;
		for (it = env[current_level].item_list.begin(); it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++;
			if ((*temp).position.x == event_->position.x && (*temp).position.y == event_->position.y)
			{
				str_ = temp->GetName();
				isplural = (temp->num > 1);
				env[current_level].DeleteItem(temp);
				if (!num++)
					first_it = temp;
			}
			else if (num)
				break;
		}
		if (num == 1) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_EVENT_SION_ITEM_DELETE,true,false,false,CL_small_danger,
				PlaceHolderHelper(str_, isplural));
			you.SetInter(IT_EVENT);
		}
		else if (num > 1) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_EVENT_SION_ITEMS_DELETE), true, false, false, CL_small_danger);
			you.SetInter(IT_EVENT);
		}
		return 1;
	}
	default:
		break;
	}

	return 0;
}