//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: potion.cpp
//
// 내용: 물약들(이전 물약)
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "potion.h"
#include "god.h"
extern HANDLE mutx;

const char *potion_uniden_string[PT_MAX]=
{
	"새하얀 ",
	"초록색 ",
	"빨강색 ",
	"파랑색 ",
	"노랑색 ",
	"검정색 ",
	"회색 ",
	"분홍색 ",
	"거품낀 초록색 ",
	"거품낀 빨강색 ",
	"거품낀 파랑색 ",
	"거품낀 노랑색 ",
	"거품낀 검정색 ",
	"무색 ",
	"갈색 ",
	"거품낀 회색 ",
	"거품낀 투명한 "
};
const char *potion_iden_string[PT_MAX]=
{
	"그냥 ",
	"치유 ",
	"독 ",
	"체력회복 ",
	"힘 ",
	"가속 ",
	"혼란 ",
	"감속 ",
	"마비 ",
	"지능 ",
	"민첩 ",
	"영력 ",
	"비행 ",
	"파워 ",
	"능력치감소 ",
	"능력치회복 ",
	"술 "
};
bool skill_soul_shot(int power, unit* order, coord_def target);


potion_type goodbadpotion(int good_bad)
{
	if(good_bad==1)
	{
		potion_type list_[3] = {PT_HEAL,PT_HEAL,PT_HEAL_WOUND};
		return list_[randA(2)];
	}
	else if(good_bad==2)
	{
		potion_type list_[7] = {PT_MIGHT,PT_HASTE,PT_CLEVER,PT_AGILITY,PT_LEVETATION,PT_RECOVER_STAT, PT_ALCOHOL};
		return list_[randA(6)];
	}
	else if(good_bad==3)
	{
		potion_type list_[2] = {PT_POWER,PT_MAGIC};
		return list_[randA(1)];
	}
	else
	{
		potion_type list_[6] = {PT_WATER, PT_POISON, PT_CONFUSE, PT_SLOW, PT_PARALYSIS, PT_DOWN_STAT};
		return list_[randA(5)];
	}
}
int isGoodPotion(potion_type kind)
{
	switch(kind)
	{
	case PT_HEAL:
	case PT_HEAL_WOUND:
	case PT_HASTE:
	case PT_POWER:
		return 2;
	case PT_MIGHT:
	case PT_CLEVER:
	case PT_AGILITY:
	case PT_LEVETATION:
	case PT_MAGIC:
	case PT_RECOVER_STAT:
		return 1;
	case PT_WATER:
	case PT_ALCOHOL:
		return 0;
	case PT_CONFUSE:
	case PT_SLOW:
	case PT_POISON:
	case PT_PARALYSIS:
	case PT_DOWN_STAT:
		return -1;
	}
	return 1;
}

void drinkpotion(potion_type kind, bool waste_)
{
	int bonus = (you.god == GT_EIRIN && !you.GetPunish(GT_EIRIN))?1:0;
	switch(kind)
	{
	case PT_WATER:
		printlog("그냥 물약 맛이다.",false,false,false,CL_normal);
		//you.HungerApply(50);
		return;
	case PT_HEAL:
		printlog("치유가 되는 것을 느꼈다.",false,false,false,CL_normal);
		you.HpUpDown(6+randA_1(9+bonus*10),DR_POTION);
		//you.HungerApply(50);
		you.s_confuse = 0;
		you.s_poison = 0;
		you.s_sick = 0;
		return;
	case PT_POISON:
		{
			int time_ = rand_int(25,50+bonus*15);
			bool ok_= false;
			printlog("이 물약은 역겨운 맛이다.",false,false,false,you.poison_resist>0?CL_normal:CL_warning);
			ok_ = you.SetPoison(time_,150,false);
			if(you.equipment[ET_LEFT] && you.equipment[ET_LEFT]->value1 == RGT_POISON_RESIS)
				you.equipment[ET_LEFT]->Identify();
			else if(you.equipment[ET_RIGHT] && you.equipment[ET_RIGHT]->value1 == RGT_POISON_RESIS)
				you.equipment[ET_RIGHT]->Identify();
			if(you.god == GT_EIRIN && !you.GetPunish(GT_EIRIN) && pietyLevel(you.piety)>=1 && ok_)
			{
				enterlog();
				printlog("에이린은 당신이 물약에서 새로운 힘을 끌어오게했다. ",false,false,false,CL_small_danger); 
				you.SetSwift(time_);
			}
			//you.HungerApply(50);
			enterlog();
			return;	
		}
	case PT_HEAL_WOUND:
		printlog("체력이 회복되는 되는 것을 느꼈다.",false,false,false,CL_normal);
		you.HpUpDown(15+bonus*5+randA_1(30+bonus*15),DR_POTION);
		//you.HungerApply(50);
		return;
	case PT_MIGHT:
		you.SetMight(rand_int(50,80)+bonus*30);
		//you.HungerApply(50);
		return;
	case PT_HASTE:
		you.SetHaste(rand_int(50,80)+bonus*30);
		//you.HungerApply(50);
		return;
	case PT_CONFUSE:
		{
			bool ok_= false;
			printlog("이 물약은 멀미나는 맛이다.",false,false,false,you.confuse_resist>0?CL_normal:CL_warning);
			ok_ = you.SetConfuse(rand_int(15,30)+bonus*10);
			if(you.equipment[ET_LEFT] && you.equipment[ET_LEFT]->value1 == RGT_CONFUSE_RESIS)
				you.equipment[ET_LEFT]->Identify();
			if(you.equipment[ET_RIGHT] && you.equipment[ET_RIGHT]->value1 == RGT_CONFUSE_RESIS)
				you.equipment[ET_RIGHT]->Identify();
			if(you.god == GT_EIRIN && !you.GetPunish(GT_EIRIN) && pietyLevel(you.piety)>=3 && ok_)
			{
				enterlog();
				printlog("에이린은 당신이 물약에서 새로운 힘을 끌어오게했다. ",false,false,false,CL_small_danger);  
				printlog("영력이 차오르는 것을 느낀다.",true,false,false,CL_white_blue);
				you.MpUpDown(15+randA_1(15));
			}
			//you.HungerApply(50);
			return;
		}
	case PT_SLOW:
		{
			int time_ = rand_int(50,80)+bonus*30;
			bool ok_= false;
			ok_ = you.SetSlow(time_);
			//you.HungerApply(50);
			if(you.god == GT_EIRIN && !you.GetPunish(GT_EIRIN)  && pietyLevel(you.piety)>=1 && ok_)
			{
				enterlog();
				printlog("에이린은 당신이 물약에서 새로운 힘을 끌어오게했다. ",true,false,false,CL_small_danger); 
				you.SetInvisible(time_);
			}
			return;
		}
	case PT_PARALYSIS:
		{
			bool ok_= false;
			ok_ = you.SetParalyse(randA_1(7-bonus*5));
			//you.HungerApply(50);
			if(you.god == GT_EIRIN && !you.GetPunish(GT_EIRIN)  && pietyLevel(you.piety)>=5 && ok_)
			{
				enterlog();
				printlog("에이린은 물약으로부터의 마비를 막아주고 새로운 힘을 끌어오게했다. ",false,false,false,CL_small_danger);  
				printlog("당신은 폭발했다!",true,false,false,CL_small_danger);
				ReleaseMutex(mutx);
				changedisplay(DT_GAME);
				skill_soul_shot(0, &you, you.position);
				WaitForSingleObject(mutx, INFINITE);
			}
			return;
		}
	case PT_CLEVER:
		you.SetClever(rand_int(50,80)+bonus*30);
		//you.HungerApply(50);
		return;
	case PT_AGILITY:
		you.SetAgility(rand_int(50,80)+bonus*30);
		//you.HungerApply(50);
		return;
	case PT_MAGIC:
		printlog("상당한 영력이 느껴진다.",false,false,false,CL_normal);
		you.MpUpDown(9+bonus*5+randA_1(15));
		//you.HungerApply(50);
		return;
	case PT_LEVETATION:
		you.SetLevitation(rand_int(50,80)+bonus*30);
		//you.HungerApply(50);
		return;
	case PT_POWER:
		printlog("파워가 한단계 상승한 느낌이 든다.",false,false,false,CL_normal);
		you.PowUpDown(100+bonus*100);
		//you.HungerApply(50);
		return;
	case PT_DOWN_STAT:
		{
			printlog("이 물약은 구역질이 난다.",false,false,false,CL_normal);
			int rand_ = randA_1(3);
			randA(2)?(randA(1)?you.StatUpDown(-rand_,STAT_STR,true):you.StatUpDown(-rand_,STAT_DEX,true)):you.StatUpDown(-rand_,STAT_INT,true);
			if(you.god == GT_EIRIN && !you.GetPunish(GT_EIRIN) && pietyLevel(you.piety)>=2)
			{
				enterlog();
				printlog("에이린은 당신이 물약에서 새로운 힘을 끌어오게했다. ",false,false,false,CL_small_danger); 
				printlog("상처가 치료가 되는 것을 느꼈다.",true,false,false,CL_normal);
				you.HpUpDown(15+randA_1(35),DR_POTION);
			}
			//you.HungerApply(50);
			return;
		}
	case PT_RECOVER_STAT:
		{
			bool up_ = false;
			printlog("이 물약에선 깔끔한 맛이 난다.",false,false,false,CL_normal);
			if(you.s_str < you.m_str)
			{
				you.StatUpDown(min(you.m_str-you.s_str,rand_int(1,5)),STAT_STR,true);
				up_ = true;
			}
			if(you.s_dex < you.m_dex)
			{
				you.StatUpDown(min(you.m_dex-you.s_dex,rand_int(1,5)),STAT_DEX,true);
				up_ = true;
			}
			if(you.s_int < you.m_int)
			{
				you.StatUpDown(min(you.m_int-you.s_int,rand_int(1,5)),STAT_INT,true);
				up_ = true;
			}
			if(up_)
				printlog("당신은 잃어버린 능력치를 회복했다.",false,false,false,CL_blue);
			//you.HungerApply(50);
		}
		return;
	case PT_ALCOHOL:
		{
			int turn_ = rand_int(30,50)+bonus*30;
			if(you.god == GT_YUUGI && !you.GetPunish(GT_YUUGI))
				you.SetBuff(BUFFSTAT_EV, BUFF_DUPLE, 10, turn_);
			you.SetDrunken(turn_);
		}
		return;
	}
}