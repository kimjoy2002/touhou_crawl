//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: skill.cpp
//
// 내용: skill관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "skill.h"
#include "player.h"

//50 60 70 84 100 120 140 170 200 250

int aptitude[TRI_MAX][SKT_MAX]=
{
//			 전투|맨손|단검|장검|둔기|도끼| 창 |탄막|회피|갑옷|방패|마법|화염|냉기|대지|대기|요술|연금|정신|소환|전이|발동|은밀|
/*인간*/	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },//인간
/*마법사*/	{ -2,  -2,  -1,  -2,  -1,  -3,  -3,   1,   2,  -2,  -2,   3,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   2 },//마법사
/*요정*/	{ -3,  -2,   1,  -2,  -3,  -3,  -1,   2,   4,  -3,  -3,   1,   2,   2,   2,   3,   2,  -2,  -2,  -2,   1,  -2,   3 },//요정
/*카라스텐*/{  1,  -1,   0,   0,   2,   1,   1,   1,   2,  -2,  -1,  -1,  -2,  -2,  -3,   2,   1,  -2,  -1,  -1,   0,   0,   0 },//카라스텐구
/*백랑텐구*/{  2,   0,   0,   2,   2,   2,   1,   1,  -1,   3,   3,  -3,  -2,  -2,   0,  -2,  -2,   0,  -2,  -2,  -2,   1,  -3 },//백랑텐구
/*캇파*/	{  1,   2,  -2,   0,   1,  -1,   3,   0,   2,   0,  -3,   1,  -4,   2,  -2,   0,  -1,  -1,  -1,   0,   0,   3,   0 },//캇파
/*네코마타*/{  1,   3,  -2,  -2,  -2,  -2,  -2,   0,   3,  -3,  -3,   0,  -1,  -1,  -2,   0,   1,   2,   2,  -1,   4,  -1,   4 },//네코마타
/*용궁의사*/{  0,  -1,  -1,  -1,  -1,  -1,  -1,   2,  -1,   0,  -1,   0,   0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   2 },//용궁의사자
/*츠구모가*/{  2,  -1,   1,   1,   1,   1,   1,   2,   1,   1,   1,  -1,  -1,  -1,  -1,  -1,  -1,   1,  -2,   0,  -1,   1,   1 },//츠구모가미
/*오니*/	{  3,   0,  -2,  -1,   2,  -1,  -2,  -2,  -1,  -4,  -3,  -1,   1,  -2,  -1,  -2,  -2,  -2,  -3,  -2,  -3,  -1,  -4 },//오니
/*반요*/	{  0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 },//반요
/*망령*/	{ -2,  -2,   0,  -2,  -2,  -2,  -2,  -2,   0,  -5,  -2,  -1,  -1,   0,  -2,   0,   0,  -3,   3,   1,   2,  -2,   4 },//망령
/*뱀파이어*/{  1,   0,  -1,  -1,  -1,  -1,  -1,  -1,   3,  -2,  -2,   0,   1,   0,   0,   1,   1,  -2,   0,   3,   1,  -2,   3 }, //뱀파이어
/*요괴*/	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 }//요괴
};
int exp_aptitude[TRI_MAX]=
{
/*인간*/	100,
/*마법사*/	140,
/*요정*/	130,
/*카라스텐*/130,	
/*백랑텐구*/120,
/*캇파*/	120,
/*네코마타*/120,
/*용궁의사*/140,
/*츠구모가*/130,
/*오니*/	110,
/*반요*/	160,
/*망령*/	150,
/*뱀파이어*/130,
/*요괴*/	120
};



int AptCal(int aptitu_)
{
	switch(aptitu_)
	{
	case -5:
		return 250;
	case -4:
		return 200;
	case -3:
		return 170;
	case -2:
		return 140;
	case -1:
		return 120;
	case 0:
	default:
		return 100;
	case 1:
		return 84;
	case 2:
		return 70;
	case 3:
		return 60;
	case 4:
		return 50;
	}
}


int need_skill_exp(int level, int aptit)
{ 
	if(level<0) return 0;
	else if(level == 27) return -1;
	return (60+(level)*(30+(level-1)*45))*aptit/100;
}

int exp_to_skill_exp(int level)
{
	//int exp_ = (level<=10?max(1,level):(level-10+7)*(level-10)/2+10);
	int exp2_ = skill_exp_penalty(you.total_skill_exp);
	int exp_ = (exp2_<=12?exp2_: (exp2_-12+7)*(exp2_-12)/2+11);
	if(exp_>250)
		exp_ = 250;
	//exp_ -= randA(4);
	if(exp_<=0)
		exp_ = 1;
	return exp_;
}

int skill_exp_penalty(int total_skill_exp)
{
	int penalty_ = 0;
	int exp_ = (total_skill_exp-500);
	if(total_skill_exp < 33500)
	{
		while(exp_>0)
		{
			exp_ -= (penalty_>13?13:penalty_)*200+300;
			penalty_++;
		}
	}
	else
		penalty_ = (total_skill_exp - 33500)/4000+18;

	return penalty_;
}

string skill_string(skill_type skill)
{
	switch(skill)
	{
	case SKT_FIGHT:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_FIGHT);
		break;
	case SKT_UNWEAPON:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_UNWEAPON);
		break;
	case SKT_SHORTBLADE:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_SHORTBLADE);
		break;
	case SKT_LONGBLADE:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_LONGBLADE);
		break;
	case SKT_MACE:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_MACE);
		break;
	case SKT_AXE:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_AXE);
		break;
	case SKT_SPEAR:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_SPEAR);
		break;
	case SKT_TANMAC:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_TANMAC);
		break;
	case SKT_DODGE:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_DODGE);
		break;
	case SKT_STEALTH:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_STEALTH);
		break;
	case SKT_ARMOUR:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_ARMOUR);
		break;
	case SKT_SHIELD:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_SHIELD);
		break;
	case SKT_SPELLCASTING:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_SPELLCASTING);
		break;
	case SKT_FIRE:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_FIRE);
		break;
	case SKT_COLD:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_COLD);
		break;
	case SKT_EARTH:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_EARTH);
		break;
	case SKT_AIR:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_AIR);
		break;
	case SKT_CONJURE:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_CONJURE);
		break;
	case SKT_ALCHEMY:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_ALCHEMY);
		break;
	case SKT_MENTAL:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_MENTAL);
		break;
	case SKT_SUMMON:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_SUMMON);
		break;
	case SKT_TRANS:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_TRANS);
		break;
	case SKT_EVOCATE:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_EVOCATE);
		break;
	default:
		return LocalzationManager::locString(LOC_SYSTEM_SKILL_UNKNOWN);
		break;
	}
}


int GetBaseSkillExp()
{
	return need_skill_exp(0, 100) - need_skill_exp(-1, 100);
}
int GetMaxSkillExp(const skill_exp_infor &skill)
{
	return need_skill_exp(skill.level, AptCal(skill.aptit)) - need_skill_exp(skill.level - 1, AptCal(skill.aptit));
}
int GetSkillPercent(const skill_exp_infor &skill)
{
	int max_exp = GetMaxSkillExp(skill);
	int cur_exp = skill.exper - need_skill_exp(skill.level-1, AptCal(skill.aptit));
	return cur_exp*100/max_exp;
}
//int GetSkillDisplay(int aptit_)
//{
//	if(aptit_<=50)
//		return 4;
//	else if(aptit_<=60)
//		return 3;
//	else if(aptit_<=70)
//		return 2;
//	else if(aptit_<=84)
//		return 1;
//	else if(aptit_<=100)
//		return 0;
//	else if(aptit_<=120)
//		return -1;
//	else if(aptit_<=140)
//		return -2;
//	else if(aptit_<=170)
//		return -3;
//	else if(aptit_<=200)
//		return -4;
//	else if(aptit_<=250)
//		return -5;
//	else
//		return -6;
//} 

D3DCOLOR GetSkillColor(int aptit_)
{
	switch(aptit_)
	{
	case -5:
		return D3DCOLOR_XRGB(255,0,0);
		break;
	case -4:
		return D3DCOLOR_XRGB(255,50,50);
		break;
	case -3:
		return D3DCOLOR_XRGB(255,100,100);
		break;
	case -2:
		return D3DCOLOR_XRGB(255,150,150);
		break;
	case -1:
		return D3DCOLOR_XRGB(255,200,200);
		break;
	case 0:
	default:
		return D3DCOLOR_XRGB(255,255,255);
		break;
	case 1:
		return D3DCOLOR_XRGB(200,200,255);
		break;
	case 2:
		return D3DCOLOR_XRGB(150,150,255);
		break;
	case 3:
		return D3DCOLOR_XRGB(100,100,255);
		break;
	case 4:
		return D3DCOLOR_XRGB(50,50,255);
		break;
	}
}