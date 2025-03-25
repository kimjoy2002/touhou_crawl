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
#include "seija.h"
#include "armour.h"
#include "ring.h"




extern HANDLE mutx;


int GetGodGiftTime(god_type god)
{	
	switch(god)
	{
	case GT_ERROR:
	case GT_NONE:
	case GT_SUWAKO:
		return 0;
	case GT_JOON_AND_SION:
		return (you.god_value[GT_JOON_AND_SION][1] == -1)?6:0;
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
	case GT_SEIJA:
		return 10;
	case GT_LILLY:
		return 0;
	}
	return 0;
}
bool GodGift(god_type god, int piety)
{
	switch(god)
	{
	case GT_ERROR:
	case GT_NONE:
		return false;
	case GT_SUWAKO:
		swako_gift(true);
		return true;
	case GT_JOON_AND_SION:
		joon_sion_gift(true);
		return true;
	case GT_MINORIKO:
		if(pietyLevel(you.piety)>=3)
		{
			minoriko_gift(true);
			return true;
		}
		return false;
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_YUYUKO:
		return false;
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
			byakuren_gift(true);
			return true;
		}
		return false;
	case GT_KANAKO:
		if(pietyLevel(you.piety)>=5)
		{
			kanako_gift(true);
			return true;
		}
		return false;
	case GT_MIMA:
		return true;
	case GT_EIRIN:
		if(pietyLevel(you.piety)>=3)
		{
			eirin_gift(true);
			return true;
		}
		return false;
	case GT_SEIJA:
		return seija_gift();
	case GT_LILLY:
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

void swako_gift(bool speak_) {
	item_infor t;
	makeitem(ITM_ARMOR_HEAD, 1, &t);
	t.image = &img_item_armor_helmet[6];
	t.equip_image = &img_play_item_hat[6];
	t.name = name_infor(LOC_SYSTEM_GOD_SWAWKO_HAT);
	item* item_ = env[current_level].MakeItem(you.position, t);
	MakeArtifact(item_, 2);

	bool see_invi_ = false;
	for (auto it = item_->atifact_vector.begin(); it != item_->atifact_vector.end(); it++) {
		if (it->kind == RGT_SEE_INVISIBLE) {
			see_invi_ = true;
		}
	}
	if (!see_invi_) {
		item_->atifact_vector.push_back(atifact_infor(RGT_SEE_INVISIBLE, 1));
	}
	item_->value4 = rand_int(4, 5);

	if (speak_)
	{
		printlog("당신의 발밑에 무언가 나타났다!", true, false, false, CL_dark_good);

		char temp[200];
		sprintf_s(temp, 200, "스와코에게 선물을 받았다.");
		AddNote(you.turn, CurrentLevelString(), temp, CL_help);

		MoreWait();
	}
}
void joon_sion_gift(bool speak_)
{
	if (speak_) {
		printlog("당신은 다시 빙의를 할 수 있다.", true, false, false, CL_joon_and_sion);
		MoreWait();
	}
	you.god_value[GT_JOON_AND_SION][1] = 0;
	you.Ability(SKL_JOON_AND_SION_1, true, false);
}


void minoriko_gift(bool speak_)
{	
	item_infor t;
	env[current_level].MakeItem(you.position,makeitem(ITM_FOOD, 0, &t, 1));
	
	if(speak_)
	{
		printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);

		char temp[200];
		sprintf_s(temp,200,"미노리코에게 선물을 받았다.");
		AddNote(you.turn,CurrentLevelString(),temp,CL_help);

		MoreWait();
	}
}
void byakuren_gift(bool speak_)
{
	int gift_book = -1;
	for(int i = 0; i < 40 && gift_book == -1; i++)
	{
		vector<temp_class> q;
		for(int j=SKT_SPELLCASTING+1; j<SKT_EVOCATE;j++)
		{
			q.push_back(temp_class(you.GetSkillLevel(j, false),you.skill[j].exper,j));
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
	
	if(speak_)
	{
		printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);

		char temp[200];
		sprintf_s(temp,200,"뱌쿠렌에게 선물을 받았다.");
		AddNote(you.turn,CurrentLevelString(),temp,CL_help);

		MoreWait();
	}
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
		if(you.s_str < you.m_str)
		{
			you.StatUpDown(you.m_str-you.s_str,STAT_STR,true);
		}
		if(you.s_dex < you.m_dex)
		{
			you.StatUpDown(you.m_dex-you.s_dex,STAT_DEX,true);
		}
		if(you.s_int < you.m_int)
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



void kanako_gift(bool speak_)
{
	
	random_extraction<int> rand_;

	for(int i=SKT_SHORTBLADE;i<=SKT_SPEAR;i++)
	{
		rand_.push(i-SKT_SHORTBLADE, you.GetSkillLevel(i, true)+1);
	}

	item_infor t;
	item* it = env[current_level].MakeItem(you.position,makeitem((item_type)(rand_.pop()), 1, &t));
	//it->value3 += rand_int(-1,6);
	it->value4 += rand_int(-2,6);
	if(!it->value5 && randA(2)>1)
		it->value5 = GetNewBrand(0); //카나코는 신의 브랜드는 선물하지 않는다.
	if(randA(3) == 0)
		MakeArtifact(it,1);
	if(speak_)
	{
		printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);

		char temp[200];
		sprintf_s(temp,200,"카나코에게 선물을 받았다.");
		AddNote(you.turn,CurrentLevelString(),temp,CL_help);

		MoreWait();
	}

}


item* armour_gift(bool speak_, bool artifact_)
{
	random_extraction<int> rand_;
	rand_.push(0,5); //아머
	rand_.push(1, you.GetSkillLevel(SKT_SHIELD, true)>=1?3:1); //방패
	rand_.push(2,you.equipment[ET_HELMET]==NULL?5:1); //머리
	rand_.push(3,you.equipment[ET_CLOAK]==NULL?5:1); //망토
	rand_.push(4,you.equipment[ET_GLOVE]==NULL?5:1); //손
	rand_.push(5,you.equipment[ET_BOOTS]==NULL?5:1); //발
	item* it = NULL;

	int armour_ = rand_.pop();
	switch(armour_)
	{
	case 0:
		{
			//회피스킬이 갑옷스킬의 2배이상이거나 갑옷이 5레벨미만
			bool dodge_ = (you.GetSkillLevel(SKT_DODGE, true)>you.GetSkillLevel(SKT_ARMOUR, true)*2 || you.GetSkillLevel(SKT_ARMOUR, true) < 5);
			//갑옷스킬이 회피스킬의 2배이상이거나 갑옷이 15레벨이상
			bool heavy_ = (you.GetSkillLevel(SKT_ARMOUR, true)>you.GetSkillLevel(SKT_DODGE, true) *2 || you.GetSkillLevel(SKT_ARMOUR, true) >= 15);
			random_extraction<int> rand2_;

			rand2_.push(ITM_ARMOR_BODY_ARMOUR_0,dodge_?10:1); //로브
			rand2_.push(ITM_ARMOR_BODY_ARMOUR_1,dodge_?8:4); //가죽
			rand2_.push(ITM_ARMOR_BODY_ARMOUR_2,heavy_?8:4); //체인
			rand2_.push(ITM_ARMOR_BODY_ARMOUR_3,heavy_?10:1); //판금
	
			int select_ = rand2_.pop();
			item_infor t;
			it = env[current_level].MakeItem(you.position,makeitem((item_type)select_, 1, &t,randA(AMK_POISON)));

			//it->value4 += randA(randA(it->value1/2)); //추가 인챈트
			if(randA(1) || artifact_) //50%
				MakeArtifact(it,1);
		}
		break;
	case 1:
		{
			random_extraction<int> rand2_;

			rand2_.push(0, you.GetSkillLevel(SKT_SHIELD, true) <=5?5:1); //버클러
			rand2_.push(28, you.GetSkillLevel(SKT_SHIELD, true) >=10?5:1); //실드
			rand2_.push(30, you.GetSkillLevel(SKT_SHIELD, true) >=20?10:1); //카이트
			
			int select_ = rand2_.pop();
			
			item_infor t;
			it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_SHIELD, 1, &t,select_));
						
			if(randA(1) || artifact_) //50%
				MakeArtifact(it,1);
		}
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		{
			random_extraction<int> rand2_;		
			
			item_infor t;
			it = env[current_level].MakeItem(you.position,makeitem((item_type)(ITM_ARMOR_HEAD+armour_-2), 1, &t));

			if(randA(1) || artifact_) //50%
				MakeArtifact(it,1);
		}
		break;
	}




	if(speak_)
	{
		printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);

		MoreWait();
	}

	return it;
}

item* jewelry_gift(bool speak_, bool curse_, bool artifact_)
{
	random_extraction<int> rand_;

	for(int i = 0; i < RGT_MAX; i++)
	{
		if(isGoodRing((ring_type)i,1))
		{			
			rand_.push(i,iden_list.ring_list[i].iden == 2?1:20); //식별된것은 확률이 확 줄어듬
		}
	}
	
	item_infor t;
	item* it = env[current_level].MakeItem(you.position,makeitem(ITM_RING, 1, &t,rand_.pop()));

	if(randA(2) || artifact_) //66%
		MakeArtifact(it,1);

	if (curse_) {
		it->identify_curse = true;
		it->curse = true;
	}


	if(speak_)
	{
		printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);

		MoreWait();
	}

	return it;
}

void eirin_gift(bool speak_)
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
	if(speak_)
	{
		printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);
	
		char temp[200];
		sprintf_s(temp,200,"에이린에게 선물을 받았다.");
		AddNote(you.turn,CurrentLevelString(),temp,CL_help);

		MoreWait();
	}
}