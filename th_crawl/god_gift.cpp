//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: god.cpp
//
// 내용: 신관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"
#include "god.h"
#include "key.h"
#include "skill_use.h"
#include "mon_infor.h"
#include "potion.h"
#include "skill.h"
#include "player.h"
#include "book.h"
#include "weapon.h"
#include "note.h"
#include "tensi.h"



extern HANDLE mutx;

void minoriko_gift();
void byakuren_gift();
void kanako_gift();
void eirin_gift();

int GetGodGiftTime(god_type god)
{	
	switch(god)
	{
	case GT_ERROR:
	case GT_NONE:
	case GT_SHIKIEIKI:
	case GT_SUWAKO:
		return 0;
	case GT_MINORIKO:
		return 30;
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_YUYUKO:
		return 0;
	case GT_SATORI:
		return 10;
	case GT_TENSI:
		return 5;
	case GT_BYAKUREN:
		return 40;
	case GT_KANAKO:
		return 40;
	case GT_MIMA:
		return 30;
	case GT_EIRIN:
		return 15;
	}
	return 0;
}
bool GodGift(god_type god, int piety)
{
	switch(god)
	{
	case GT_ERROR:
	case GT_NONE:
	case GT_SHIKIEIKI:
	case GT_SUWAKO:
	case GT_MINORIKO:
		if(pietyLevel(you.piety)>=3)
		{
			minoriko_gift();
			return true;
		}
		return false;
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_YUYUKO:
	case GT_SATORI:
		if(pietyLevel(you.piety)>=5)
		{
			satori_gift();
			return true;
		}
		return false;
	case GT_TENSI:
		{
			tensi_action();
			return true;
		}
		return false;
	case GT_BYAKUREN:
		if(pietyLevel(you.piety)>=5)
		{
			byakuren_gift();
			return true;
		}
		return false;
	case GT_KANAKO:
		if(pietyLevel(you.piety)>=5)
		{
			kanako_gift();
			return true;
		}
		return false;
	case GT_MIMA:
		return true;
	case GT_EIRIN:
		if(pietyLevel(you.piety)>=3)
		{
			eirin_gift();
			return true;
		}
		return false; 
	}
	return false;
}


class temp_class 
{
public:
	int level;
	int exp;
	int skills;
	temp_class():level(0),exp(0),skills(0){};
	temp_class(int a,int b,int c):level(a),exp(b),skills(c){};
};



struct compare { 
	bool operator()(const temp_class &a,const temp_class &b) const
	{return (a.level != b.level)?a.level < b.level:a.exp<a.exp;}
};
void minoriko_gift()
{	
	item_infor t;
	env[current_level].MakeItem(you.position,makeitem(ITM_FOOD, 0, &t, 1));
	
	printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);

	char temp[200];
	sprintf_s(temp,200,"미노리코에게 선물을 받았다.");
	AddNote(you.turn,CurrentLevelString(),temp,CL_help);

	MoreWait();
}
void byakuren_gift()
{
	int gift_book = -1;
	for(int i = 0; i < 40 && gift_book == -1; i++)
	{
		vector<temp_class> q;
		for(int j=SKT_SPELLCASTING+1; j<SKT_EVOCATE;j++)
		{
			q.push_back(temp_class(you.skill[j].level,you.skill[j].exper,j));
		}
		sort(q.begin(),q.end(),compare());
		for(int j=SKT_SPELLCASTING+1; j<SKT_EVOCATE;j++)
		{
			if(q.back().level == 0 )
				break;
			int skill_ = q.back().skills;
			int book_ = SchoolToBook((skill_type)skill_);
			if(randA(3)>0 && !iden_list.books_list[book_])
			{
				gift_book = book_;
				break;
			}	
			q.pop_back();
		}
	}
	item_infor t;
	env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, gift_book));
	
	printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);

	char temp[200];
	sprintf_s(temp,200,"뱌쿠렌에게 선물을 받았다.");
	AddNote(you.turn,CurrentLevelString(),temp,CL_help);

	MoreWait();
}

void mima_gift(book_list book_)
{
	if(!iden_list.books_list[book_])
	{
		item_infor t;
		env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, book_));
		
		printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);

		char temp[200];
		sprintf_s(temp,200,"미마에게 선물을 받았다.");
		AddNote(you.turn,CurrentLevelString(),temp,CL_help);
		MoreWait();
	}
}
void satori_gift()
{
	printlog("사토리님이 당신에게 먹이를 주셨다!",false,false,false,CL_green);
	if(1)
	{//체력회복
		you.HpUpDown(5+randA_1(25),DR_POTION);
	}
	if(1)
	{//마나회복
		you.MpUpDown(9+randA_1(15));
	}
	if(randA(1))
	{//능력치회복 
		you.s_paralyse = 0;
		you.s_confuse = 0;
		you.s_poison = 0;
		you.s_sick = 0;
	}
	if(randA(2)==0)
	{//파워업
		you.PowUpDown(50);
	}
	if(randA(4)==0)
	{//능력치회복
		if(you.s_str != you.m_str)
		{
			you.StatUpDown(you.m_str-you.s_str,STAT_STR,true);
		}
		if(you.s_dex != you.m_dex)
		{
			you.StatUpDown(you.m_dex-you.s_dex,STAT_DEX,true);
		}
		if(you.s_int != you.m_int)
		{
			you.StatUpDown(you.m_int-you.s_int,STAT_INT,true);
		}
	}
	if(randA(9)==0)
	{//지능업
		you.SetClever(rand_int(50,80));
		//you.HungerApply(50);
	}
	if(randA(9)==0)
	{//민첩업
		you.SetAgility(rand_int(50,80));
	}
	if(randA(9)==0)
	{//힘업
		you.SetMight(rand_int(50,80));
	}
}



void kanako_gift()
{
	int result_weapon = SKT_SHORTBLADE;
	int total = 0;
	int percent[SKT_SPEAR - SKT_SHORTBLADE+1];
	for(int i=SKT_SHORTBLADE;i<=SKT_SPEAR;i++)
	{
		percent[i-SKT_SHORTBLADE] = you.skill[i].level+1;
		total += percent[i-SKT_SHORTBLADE];
	}

	total = randA_1(total);

	for(int i=SKT_SHORTBLADE;i<=SKT_SPEAR;i++)
	{
		if(total<=percent[i-SKT_SHORTBLADE])
		{
			result_weapon = i-SKT_SHORTBLADE;
			break;
		}
		total -= percent[i-SKT_SHORTBLADE];
	}

	item_infor t;
	item* it = env[current_level].MakeItem(you.position,makeitem((item_type)result_weapon, 1, &t));
	//it->value3 += rand_int(-1,6);
	it->value4 += rand_int(-2,6);
	if(!it->value5 && randA(2)>1)
		it->value5 = GetNewBrand(0); //카나코는 신의 브랜드는 선물하지 않는다.
	if(randA(3) == 0)
		MakeArtifact(it,1);
	printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);

	char temp[200];
	sprintf_s(temp,200,"카나코에게 선물을 받았다.");
	AddNote(you.turn,CurrentLevelString(),temp,CL_help);

	MoreWait();

}




void eirin_gift()
{
	potion_type type_= goodbadpotion(randA(5)<2?-1:randA(2)>1?1:(randA(60)?2:3));
	int num = 1;


	if(type_ == PT_WATER)
		num = randA_1(10);
	if(type_ == PT_HEAL || type_ == PT_DOWN_STAT || type_ == PT_POISON || type_ == PT_RECOVER_STAT)
		num = randA_1(3);
	if(type_ == PT_HEAL_WOUND || type_ == PT_CONFUSE || type_ == PT_SLOW)
		num = randA_1(2);

	item_infor t;
	for(int i=0;i<num;i++)
		env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t,(int)type_));
	printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);
	
	char temp[200];
	sprintf_s(temp,200,"에이린에게 선물을 받았다.");
	AddNote(you.turn,CurrentLevelString(),temp,CL_help);

	MoreWait();
}