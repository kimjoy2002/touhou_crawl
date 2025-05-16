﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: player_damage.cpp
//
// 내용: player의 데미지 처리 함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "player.h"
#include "unit.h"
#include "environment.h"
#include "beam.h"
#include "potion.h"
#include "scroll.h"
#include "smoke.h"
#include "skill.h"
#include "ring.h"
#include "save.h"
#include "key.h"
#include "weapon.h"
#include "alchemy.h"
#include "throw.h"
#include "tensi.h"
#include "tribe.h"
#include "god.h"
#include "soundmanager.h"


extern HANDLE mutx;
skill_type itemtoskill(item_type type_);
extern int shieldPanaltyOfWeapon(item_type type, int weapon_kind);







int players::GetAttack(bool max_)
{
	float base_atk_ = s_str/3.0f+ s_dex/6.0f;
	float max_atk_=0, min_atk_=0, stab_atk_=0;
	skill_type skill_ = SKT_MACE;

	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->type >= ITM_WEAPON_FIRST && equipment[ET_WEAPON]->type <= ITM_WEAPON_CLOSE)
	{
		skill_ = itemtoskill(equipment[ET_WEAPON]->type);
		if(skill_>SKT_ERROR)
		{
			max_atk_ = equipment[ET_WEAPON]->value2*(equipment[ET_WEAPON]->value4/18.0f+ GetSkillLevel(skill_, true)/20.0f+base_atk_/6.0f);
			min_atk_ = 0;//min(equipment[ET_WEAPON]->value2,skill[skill_].level/2);
		}
		else //여기는 버그 처리. 데미지가 없으면 버그임을 알수있음
		{
			max_atk_ = 0;
			min_atk_ = 0; 
		}
	}
	else if(!equipment[ET_WEAPON]) //맨손임
	{
		skill_ = SKT_UNWEAPON;
		max_atk_ = base_atk_+ GetSkillLevel(skill_, true)*15.0f/20.0f;
		if(GetProperty(TPT_CLAW)>0)
			max_atk_ += 3*GetProperty(TPT_CLAW);
		min_atk_ = 0;
	}
	else
	{
		max_atk_ = base_atk_;
		min_atk_ = 0;
	}
	bool sion_ = (you.god == GT_JOON_AND_SION && !you.GetPunish(GT_JOON_AND_SION) && you.god_value[GT_JOON_AND_SION][0] == 2);
	if(!sion_ && power<=200)
	{ //파워 200이하에서만 파워에 의한 감소를 받는다.
		max_atk_ *= (min(power,500)*0.001f+0.5f);
		min_atk_ *= (min(power,500)*0.001f+0.5f);
	}

	stab_atk_ = max_atk_;



	if(s_might || s_lunatic)
		max_atk_+=randA_1(10);	
	
	if(!equipment[ET_WEAPON] && alchemy_buff == ALCT_STONE_FORM)
		max_atk_+=8;



	max_atk_+=dam_plus;
	if(s_slaying)
	{
		max_atk_+=s_slaying;
	}
	max_atk_ += you.GetBuffOk(BUFFSTAT_DAM);
	if(GetProperty(TPT_SLAY))
	{
		max_atk_+=6;
	}

	if(you.force_turn)
	{
		if(you.force_strong)
			max_atk_*=2;
		else
			max_atk_/=2;
	}
	if(alchemy_buff == ALCT_AUTUMN_BLADE)
	{
		max_atk_ *= 3;
	}




	if(max_atk_<min_atk_)
		max_atk_ = min_atk_;

	int atk_ = rand_int((int)round(min_atk_),(int)round(max_atk_));

	int cacul_max_ = max_atk_;
	
	if(alchemy_buff == ALCT_STONE_FIST)
	{
		atk_+=randA_1(10);	
		cacul_max_ += 10;
	}

	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->value5)//속성브랜드처리
	{
		atk_ = GetPulsDamage((weapon_brand)equipment[ET_WEAPON]->value5,atk_);
		cacul_max_ = GetPulsDamage((weapon_brand)equipment[ET_WEAPON]->value5,cacul_max_);
	}
	

	
	if(wiz_list.wizard_mode == 1 && !max_)
	{
		ostringstream ss;
		ss << "[" << LocalzationManager::locString(LOC_SYSTEM_DEBUG_MAX_DAMAGE) << " " << cacul_max_ << "]";
		printlog(ss.str(),false,false,false,CL_help);
	}


	float plus_max_atk = max_atk_ - stab_atk_;

	//max_atk_*=(1+(skill[skill_].level+skill[SKT_STEALTH].level)*0.1);
	if(equipment[ET_WEAPON] && ( equipment[ET_WEAPON]->type == ITM_WEAPON_SHORTBLADE || equipment[ET_WEAPON]->value5 == WB_AUTUMN))
	{ //단검 암습 보너스
		stab_atk_+=(2+(GetSkillLevel(skill_, true) + GetSkillLevel(SKT_STEALTH, true))/2)*2;
		stab_atk_*=(1+(GetSkillLevel(skill_, true) + GetSkillLevel(SKT_STEALTH, true))*0.1f);
	}
	else
		stab_atk_*=(1+ GetSkillLevel(SKT_STEALTH, true)*0.1f);
	

	max_atk_ = stab_atk_ + plus_max_atk;

	//	max_atk_*=equipment[ET_WEAPON]->GetStabPercent();


	return max_?max_atk_:atk_;
}


int players::GetHit()
{
	int hit_ = 2+s_dex/3+ GetSkillLevel(SKT_FIGHT, true)/4;
	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->type >= ITM_WEAPON_FIRST && equipment[ET_WEAPON]->type <= ITM_WEAPON_CLOSE)
	{
		skill_type skill_ = itemtoskill(equipment[ET_WEAPON]->type);
		if(skill_>SKT_ERROR)
		{
			hit_ += 1 + (equipment[ET_WEAPON]->value1 + equipment[ET_WEAPON]->value4 + GetSkillLevel(skill_, true)/3)*3/4;
		}
		else
		{
			hit_ = -99;
		}
	}
	else if(!equipment[ET_WEAPON])
	{
		hit_ += s_dex/4;
	}
	hit_+=acc_plus;
	if(s_slaying)
	{
		hit_+=s_slaying;
	}
	hit_ += you.GetBuffOk(BUFFSTAT_ACC);
	if(GetProperty(TPT_SLAY))
	{
		hit_+=6;
	}
	if(s_unluck) //명중다운
	{
		hit_-=s_unluck>6?9:(s_unluck>3?7:5);
	}


	if(as_penalty > GetPenaltyMinus(1))
	{//만약 방어패널티때문에 명중이 내려갈 경우
		hit_ -= as_penalty; 
	}
	return hit_;
}
int players::GetAtkDelay()
{
	int delay_ = 6;
	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->type >= ITM_WEAPON_FIRST && equipment[ET_WEAPON]->type <= ITM_WEAPON_CLOSE)
	{
		float real_delay_ = max<float>((equipment[ET_WEAPON]->value8) , 
			(equipment[ET_WEAPON]->value7- GetSkillLevel(itemtoskill(equipment[ET_WEAPON]->type), true)/2.0f));

		if (equipment[ET_SHIELD])
		{
			real_delay_ += shieldPanaltyOfWeapon(equipment[ET_WEAPON]->type, equipment[ET_WEAPON]->value0);
		}



		delay_ = real_delay_+rand_float(0.99f,0.0f);
	}
	else if(equipment[ET_WEAPON])
		delay_ = 10;
		
	return delay_;

}

int players::ReSetASPanlty()
{
	const item* armor_ = equipment[ET_ARMOR], *shield_ = equipment[ET_SHIELD];
	int prev_panlty_ = as_penalty;
	int panlty_ = 0;
	if(armor_)
	{ //아머의 패널티
		int panlty2_ = -armor_->value2;
		panlty2_ -= GetSkillLevel(SKT_ARMOUR, true)/3;
		if(panlty2_ < -armor_->value3)
			panlty2_ = -armor_->value3;
		panlty_ += panlty2_;
	}	
	if(shield_)
	{
		int panlty2_ = -shield_->value2;
		panlty2_ -= GetSkillLevel(SKT_SHIELD, true)/3;
		if(panlty2_ < shield_->value3)
			panlty2_ = shield_->value3;
		panlty_ += panlty2_;
	}
	as_penalty = panlty_;
	EvUpDown(0,prev_panlty_-as_penalty);
	return panlty_;
}
int players::GetPenaltyMinus(int level_)
{
	switch(level_)
	{
	case 1:
		return 2+you.s_str/6;
	case 2:
		return 3+you.s_str/4;
	case 3:
		return 4+you.s_str/3;
	}

	return 0;
}
int players::GetThrowAttack(const item* it, bool max_)
{
	float base_atk_ = 1+s_str/3.0f+s_dex/6.0f;
	float max_atk_=0, min_atk_=0;
	
	
	if(!(it->type>=ITM_THROW_FIRST && it->type<ITM_THROW_LAST))
	{//이것은 장착무기이다..
		max_atk_ = 1+it->value2*(1+base_atk_/10.0f+ GetSkillLevel(SKT_TANMAC, true)/20.0f+it->value4/10.0f);
	}
	else
	{
		max_atk_ = 1+it->value2*(1+base_atk_/10.0f+ GetSkillLevel(SKT_TANMAC, true) /20.0f);
	}

	min_atk_ = min(it->value2/2, GetSkillLevel(SKT_TANMAC, true) /4);
	bool sion_ = (you.god == GT_JOON_AND_SION && !you.GetPunish(GT_JOON_AND_SION) && you.god_value[GT_JOON_AND_SION][0] == 2);
	if(!sion_ && power <= 200)
	{
		max_atk_ *= (min(power,500)*0.001f+0.5f);
		min_atk_ *= (min(power,500)*0.001f+0.5f);
	}
	if(s_might || s_lunatic)
		max_atk_+=randA_1(10);


	
	max_atk_+=dam_plus;
	if(s_slaying)
	{
		max_atk_+=s_slaying;
	}
	max_atk_ += you.GetBuffOk(BUFFSTAT_DAM);
	if(GetProperty(TPT_SLAY))
	{
		max_atk_+=6;
	}
	if(you.force_turn)
	{
		if(you.force_strong)
			max_atk_*=2;
		else
			max_atk_/=2;
	}

	
	if(max_atk_<min_atk_)
		max_atk_ = min_atk_;


	int atk_ = rand_int((int)round(min_atk_),(int)round(max_atk_));
	return max_?(int)round(max_atk_):atk_;
}


int players::GetThrowHit(const item* it)
{
	int hit_ = 3+s_dex/2;	

	if (!(it->type >= ITM_THROW_FIRST && it->type<ITM_THROW_LAST))
	{//이것은 장착무기이다..
		hit_ = 1 + it->value1 + it->value4 + GetSkillLevel(SKT_TANMAC, true) / 2;
	}
	else
	{
		hit_ += it->value1 + it->value3 + GetSkillLevel(SKT_TANMAC, true) / 2;
	}
	
	if(s_knife_collect)
	{
		hit_+=5;
	}
	
	hit_+=acc_plus;
	if(s_slaying)
	{
		hit_+=s_slaying;
	}
	hit_ += you.GetBuffOk(BUFFSTAT_ACC);
	if(GetProperty(TPT_SLAY))
	{
		hit_+=6;
	}
	if(s_unluck) //명중다운
	{
		hit_-=s_unluck>6?9:(s_unluck>3?7:5);
	}


	if(as_penalty > GetPenaltyMinus(1))
	{//만약 방어패널티때문에 명중이 내려갈 경우
		hit_ -= as_penalty; 
	}


	return hit_;
}

attack_weapon_type players::GetAttackType()
{
	if(equipment[ET_WEAPON])
	{
		switch(equipment[ET_WEAPON]->type)
		{	
		case ITM_WEAPON_SHORTBLADE:
			return AWT_SHORTBLADE;
		case ITM_WEAPON_LONGBLADE:
			return AWT_LONGBLADE;
		case ITM_WEAPON_MACE:
			return AWT_MACE;
		case ITM_WEAPON_AXE:
			return AWT_AXE;
		case ITM_WEAPON_SPEAR:
			return AWT_SPEAR;
		default:
			return AWT_NONE;
		}
	}
	return AWT_UNARMOUR;
}





int players::calculate_damage(attack_type &type_, int atk, int max_atk)
{	
	int damage_ = atk;

	if(s_unluck>3 && randA(s_unluck>6?10:20)==0)
	{
		//대흉이상에선 최대 데미지를 맞을 확률이 존재한다.
		//대흉5%  불멸 10%		
		if(wiz_list.wizard_mode == 1)
		{	
			printlog(LocalzationManager::locString(LOC_SYSTEM_DEBUG_FULL_DICE),true,false,false,CL_danger);
		}
		damage_ = max_atk;

	}
	
	int bonus_damage = 0;
	

	switch(type_)
	{
	case ATT_NORMAL:
	case ATT_NOISE:
	case ATT_SPEAR:
	case ATT_FIRE:
	case ATT_FIRE_WEAK:
	case ATT_COLD:
	case ATT_COLD_WEAK:
	case ATT_ELEC:
	case ATT_ELEC_WEAK:
	case ATT_S_POISON:
	case ATT_M_POISON:
	case ATT_SICK:
	case ATT_VAMP:
	case ATT_LUNATIC:
	case ATT_SLEEP:
	case ATT_CURSE:
	case ATT_WEATHER:
	case ATT_AUTUMN:
	case ATT_CHOAS:
	case ATT_THROW_NORMAL:
	case ATT_CLOUD_NORMAL:
	case ATT_CLOUD_CURSE:
	case ATT_VEILING:
	case ATT_RUSH:
	case ATT_WALL:
	case ATT_PSYCHO:
	case ATT_NORMAL_HIT:	
	case ATT_NORMAL_BLAST:
	case ATT_FIRE_BLAST:
	case ATT_COLD_BLAST: 
	case ATT_ELEC_BLAST:
	case ATT_POISON_BLAST:
	case ATT_FIRE_PYSICAL_BLAST:
	case ATT_COLD_PYSICAL_BLAST:
	case ATT_THROW_FIRE:
	case ATT_THROW_FREEZING:
	case ATT_THROW_COLD:
	case ATT_THROW_WATER:
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
	default:
		{//데미지 계산공식
			//최종데미지  :  1d(percent_*damage_) - 0d(ac_dec)
			//percent_:1에서 AC15까지 AC1당 0.010. 15부터 AC30까진 0.01,  AC30후부턴 0.005씩 감소(AC15면 0.85 AC30이면 0.625)
			//ac_dec -> 3, 6, 10, 15, 21, 28, 36, 45, 55에서 1씩 증가
			//는 예전 변수고 지금은 (ac+1)/3이 ac_dec가 된다.
			//최종데미지가 0보다 작으면 0이된다.
			float percent_ = 1.0f;
			int ac_dec=0;
			for(int i = ac; i>0; i--)
				percent_ -= (i<=15?0.008f:(i<=30?0.01f:0.005f));/*
			for(int i = 4, j=3 ; j <= ac ; j+=i++)
				ac_dec++;*/
			ac_dec = (ac+1)/3;
			damage_ = (int)round(damage_*percent_) - randA(ac_dec);
			//damage_ = randA_1((int)round(damage_*percent_)) - randA(ac_dec);
			if(damage_<0)
				damage_ = 0;
		}
		break;		
	case ATT_AC_REDUCE_BLAST:
		{
			float percent_ = 1.0f;
			for(int i = ac/2; i>0; i--)
				percent_ -= (i<=15?0.008f:(i<=30?0.01f:0.005f));
		}
		break;
	case ATT_SUN_BLAST:
	case ATT_CLOUD_FIRE:
	case ATT_CLOUD_COLD:
	case ATT_CLOUD_ELEC:
	case ATT_THROW_ELEC:
	case ATT_THROW_NONE_MASSAGE:
	case ATT_THROW_NONE_DAMAGE:
	case ATT_STONE_TRAP:
	case ATT_SMITE:
	case ATT_SMASH:
	case ATT_BLOOD:	
	case ATT_BURST:
	case ATT_DROWNING:
		break;
	}

	
	switch(type_)
	{
	case ATT_FIRE:
	case ATT_FIRE_WEAK:
		bonus_damage = damage_/3;
		damage_ -= bonus_damage;
		bonus_damage *= GetFireResist();
		break;
	case ATT_COLD:
	case ATT_COLD_WEAK:
		bonus_damage = damage_/3;
		damage_ -= bonus_damage;
		bonus_damage *= GetColdResist();
		break;
	case ATT_ELEC:
	case ATT_ELEC_WEAK:
		bonus_damage = damage_/3;
		damage_ -= bonus_damage;
		bonus_damage *= GetElecResist();
		break;
	case ATT_WEATHER:
		type_ = GetWeatherType(this, damage_, bonus_damage);
		break;
	default:
		break;
	}
	damage_ += bonus_damage;


	switch(type_)
	{
	case ATT_THROW_FIRE:
	case ATT_FIRE_BLAST:
		damage_ *= GetFireResist();
		break;
	case ATT_CLOUD_FIRE:
		damage_ *= GetFireResist(true);
		break;
	case ATT_THROW_COLD:
	case ATT_THROW_FREEZING:
	case ATT_COLD_BLAST: 
		damage_ *= GetColdResist();
		break;
	case ATT_CLOUD_COLD:
		damage_ *= GetColdResist(true);
		break;
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
	case ATT_POISON_BLAST:
		damage_ *= GetPoisonResist()>0?0.5:(GetPoisonResist()<0?1.5:1);
		break;
	case ATT_THROW_ELEC:
	case ATT_ELEC_BLAST:
		damage_ *= GetElecResist();
		break;
	case ATT_CLOUD_ELEC:
		damage_ *= GetElecResist(true);
		break;
	case ATT_FIRE_PYSICAL_BLAST:
		damage_ = damage_/2.0f + damage_*GetFireResist()/2.0f;
		break;
	case ATT_COLD_PYSICAL_BLAST:
		damage_ = damage_/2.0f + damage_*GetColdResist()/2.0f;
		break;
	case ATT_CLOUD_NORMAL:
	case ATT_CLOUD_CURSE:
		damage_ *= GetCloudResist()?0.5f:1.0f;
		break;
	default:
		break;
	}

	if(alchemy_buff == ALCT_STONE_FORM)
		damage_ /= 0.66f;


	return damage_;

}
void players::print_damage_message(attack_infor &a, bool damaged_)
{
	name_infor name_;
	if(a.order)
		name_ = (*a.order->GetName());
	switch(a.type)
	{
	case ATT_NORMAL:
	case ATT_SPEAR:
	case ATT_S_POISON:
	case ATT_M_POISON:
	case ATT_SICK:
	case ATT_VAMP:
	case ATT_LUNATIC:
	case ATT_CURSE:
	case ATT_WEATHER:
	case ATT_AUTUMN:
	case ATT_CHOAS:
	case ATT_THROW_NORMAL:
	case ATT_THROW_FIRE:
	case ATT_THROW_COLD:
	case ATT_THROW_WATER:
	case ATT_THROW_ELEC:
	case ATT_THROW_FREEZING:
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
	case ATT_THROW_NONE_DAMAGE:
	default:
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_NORMAL,false,false,false,a.order->isView()?CL_normal:CL_small_danger,
				 PlaceHolderHelper(name_.getName()),
				 PlaceHolderHelper(a.name.getName()),
				 PlaceHolderHelper(name.getName()));
		}
		break;
	case ATT_SLEEP:
		if (you.s_sleep >= 0)
		{
			if (a.order)
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_NORMAL,false,false,false,a.order->isView()?CL_normal:CL_small_danger,
					 PlaceHolderHelper(name_.getName()),
					 PlaceHolderHelper(a.name.getName()),
					 PlaceHolderHelper(name.getName()));
			}
		}
		else
		{
			if (a.order)
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_DREAM,false,false,false,a.order->isView()?CL_normal:CL_small_danger,
					 PlaceHolderHelper(name_.getName()),
					 PlaceHolderHelper(name.getName()));
			}
		}
		break;
	case ATT_FIRE:
	case ATT_FIRE_WEAK:
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_FIRE,false,false,false,a.order->isView()?CL_normal:CL_small_danger,
				 PlaceHolderHelper(name_.getName()),
				 PlaceHolderHelper(a.name.getName()),
				 PlaceHolderHelper(name.getName()));
		}
		break;
	case ATT_COLD:
	case ATT_COLD_WEAK:
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_COLD,false,false,false,a.order->isView()?CL_normal:CL_small_danger,
				 PlaceHolderHelper(name_.getName()),
				 PlaceHolderHelper(a.name.getName()),
				 PlaceHolderHelper(name.getName()));
		}
		break;
	case ATT_NORMAL_HIT:		
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_GERMAN_SUPLEX,false,false,false,a.order->isView()?CL_normal:CL_small_danger,
				 PlaceHolderHelper(name_.getName()),
				 PlaceHolderHelper(a.name.getName()),
				 PlaceHolderHelper(name.getName()));
		}	
		break;
	case ATT_SMITE:
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_SMITE,false,false,false,CL_normal,
				 PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_SMASH:
		if (a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_SMASH,false,false,false,CL_normal,
				PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_BLOOD:	
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_BLOOD,false,false,false,CL_normal,
				PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_NOISE:
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_NOISE,false,false,false,CL_normal,
				PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_CLOUD_FIRE:
		if(damaged_) {
			
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_CLOUD_FIRE,false,false,false,CL_normal,
				PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_CLOUD_COLD:
		if(damaged_) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_CLOUD_COLD,false,false,false,CL_normal,
				PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_CLOUD_ELEC:
		if(damaged_) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_CLOUD_ELEC,false,false,false,CL_normal,
				PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_STONE_TRAP:
		LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_STONE_TRAP,false,false,false,CL_normal,
			PlaceHolderHelper(GetName()->getName()));
		break;
	case ATT_NORMAL_BLAST:
	case ATT_AC_REDUCE_BLAST:
	case ATT_FIRE_BLAST:
	case ATT_COLD_BLAST: 
	case ATT_FIRE_PYSICAL_BLAST:
	case ATT_ELEC_BLAST:
	case ATT_POISON_BLAST:
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_BLAST,false,false,false,CL_normal,
				 PlaceHolderHelper(GetName()->getName()),
				 PlaceHolderHelper(a.name.getName()));
		}
		break;
	case ATT_SUN_BLAST:
		if (a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_SUN_BLAST,false,false,false,CL_normal,
				 PlaceHolderHelper(GetName()->getName()),
				 PlaceHolderHelper(a.name.getName()));
		}
		break;
	case ATT_COLD_PYSICAL_BLAST:
		LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_BLLIZARD,false,false,false,CL_normal,
			PlaceHolderHelper(GetName()->getName()));
		break;
	case ATT_BURST:
		LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_BURST,false,false,false,CL_normal,
			PlaceHolderHelper(GetName()->getName()));
		break;
	case ATT_CLOUD_NORMAL:
		if(damaged_) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_TWIST,false,false,false,CL_normal,
				PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_CLOUD_CURSE:
		if(damaged_) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_CURSED,false,false,false,CL_normal,
				PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_VEILING:
		LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_VEILING,false,false,false,CL_normal,
			PlaceHolderHelper(GetName()->getName()));
		break;
	case ATT_RUSH:
		LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_RUSH,false,false,false,CL_normal,
			PlaceHolderHelper(GetName()->getName()));
		break;
	case ATT_WALL:
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_BUMP,false,false,false,CL_normal,
				 PlaceHolderHelper(GetName()->getName()),
				 PlaceHolderHelper(name_.getName()));
		}
		else
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_BUMP_WALL,false,false,false,CL_normal,
				PlaceHolderHelper(GetName()->getName()));
		}
		break;
	case ATT_PSYCHO:
		LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_PSYCHO,false,false,false,CL_normal,
			PlaceHolderHelper(GetName()->getName()));
		break;
	case ATT_ELEC:
	case ATT_ELEC_WEAK:
		if(a.order)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_ELEC,false,false,false,a.order->isView()?CL_normal:CL_small_danger,
				 PlaceHolderHelper(name_.getName()),
				 PlaceHolderHelper(a.name.getName()),
				 PlaceHolderHelper(name.getName()));
		}
		break;
	case ATT_DROWNING:
		LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_DROWNING,false,false,false,CL_normal,
			PlaceHolderHelper(GetName()->getName()));
		break;
	case ATT_THROW_NONE_MASSAGE:
		break;
	}			

}
void players::print_no_damage_message(attack_infor &a)
{
	if(a.order)
	{
		switch(a.type)
		{
		case ATT_THROW_NONE_MASSAGE:	
		case ATT_CLOUD_FIRE:
		case ATT_CLOUD_COLD:
		case ATT_CLOUD_ELEC:
		case ATT_CLOUD_NORMAL:
		case ATT_CLOUD_CURSE:
		case ATT_ELEC:
		case ATT_VEILING:
		case ATT_RUSH:
		case ATT_WALL:
		case ATT_STONE_TRAP:
		case ATT_PSYCHO:
		case ATT_THROW_NONE_DAMAGE:
			break;
		default:
		case ATT_NORMAL_HIT:
			printlog(LocalzationManager::locString(LOC_SYSTEM_NO_DAMAGE),true,false,false,CL_normal);
			break;
		}
	}
}
bool players::damage(attack_infor &a, bool perfect_)
{
	int damage_ = calculate_damage(a.type,a.damage,a.max_damage);
	int accuracy_ = a.accuracy;
	float evasion = 0.0f;
	float shield_ = 0.0f;
	bool graze_ = false;
	if (accuracy_ >= 99)
		perfect_ = true;

	if(a.type < ATT_THROW_NORMAL)
	{
		if(s_paralyse)
			damage_ *= 1.2f;
		if (s_sleep < 0)
			damage_ *= 2.0f;
		else if(s_confuse)
			damage_ *= 1.2f;
		else if(a.order && !(a.order)->isView())
		{ //투명일때 조건
			damage_ *= 1.5f;
		}
	}




	if(s_timestep) //완전 무적이 됨
		return false;

	
	if(s_graze && randA(GetProperty(TPT_GRAZE_CONTROL)?2:5) == 0)
	{
		if(a.type >= ATT_THROW_NORMAL && a.type < ATT_THROW_LAST)
			graze_ = true;
	}

	if(s_glow || you.GetBuffOk(BUFFSTAT_HALO))
		accuracy_+=5; //빛날경우 명중 증가
	if(a.order && a.order->GetMindReading())
	{
		accuracy_/=3; //이 대상은 간파한 상대다.
	}

	if(a.order && !isView((monster*)a.order))
	{
		accuracy_-=5;
	}



	{//회피률 계산공식
	//최종회피률 :  edit_ev/(edit_ev+accuracy_)
	//edit_ev:1에서 EV15까지 EV1당 0.8. 15부터 AC30까진 1,  AC30후부턴 1.5씩 증가
	//저회피패널터: 만약 accuracy_>edit_ev일경우 최종회피률에서 edit_ev/accuracy_을 곱한다. 단 0.5가 최소치
	//최종값이 0보다적을 경우 0이 된다.
		float edit_ev=0;
		for(int i = ev; i>0; i--)
			edit_ev += (i<=15?0.8f:(i<=30?1:1.5f));
		evasion = edit_ev/(edit_ev+accuracy_);
		if(accuracy_>edit_ev)
			evasion *= max(0.5f,edit_ev/accuracy_);
		if(evasion<0)
			evasion = 0;
		if (you.s_sleep<0 || you.s_paralyse)
			evasion = 0;
		if(evasion>0.95f)
			evasion = 0.95f;
	}

	if(wiz_list.wizard_mode == 1)
	{		
		char temp[50];
		sprintf_s(temp,50,"a-%d A-%d, H-%d hit-%d%%",a.damage,a.max_damage,a.accuracy,(int)(100-evasion*100));
		printlog(temp,true,false,false,CL_danger);
	}
	you.SetInter(IT_DAMAGE);

	{//실드 공식
     //breaking 기본 30
	 //만약 그레이즈가능한 공격일 경우 5을 뺀다.
     // (SH / breaking+SH)의 확률로 가드!
	 //단 실드가 통하지 않는 공격일경우 최종확률이 0이됨(나중에 넣기)
		float breaking = 75;
		if(a.type >= ATT_THROW_NORMAL && a.type < ATT_THROW_LAST)
			breaking -= 15;
		shield_ = (float)sh/(sh+breaking);
		if(a.type >= ATT_NO_GUARD)
			shield_ = 0;
		if(you.s_sleep<0 || you.s_paralyse)
			shield_ = 0;
		//볼트형 가드안되게 하려면 어떻게?
	}


	name_infor name_;
	if(a.order)	
		name_ = (*a.order->GetName());
	if((randA(1000)>=evasion*1000 && !graze_ && !you.s_super_graze) || perfect_)
	{	
		if(randA(1000)>shield_*1000 || perfect_)
		{
			if (env[current_level].isSanctuary(position) || s_evoke_ghost)
			{
				//성역에선 모든 데미지가 0
				damage_ = 0;
			}
			print_damage_message(a,damage_!=0);

			if (s_sleep < 0 && a.type == ATT_SLEEP)
			{
				a.damage = damage_;
				dead_order = &a;
				HpUpDown(-1, DR_SLEEP);
			}
			else if(damage_)
			{
				enterlog();
				a.damage = damage_;
				dead_order = &a;
				HpUpDown(-damage_,DR_HITTING);

				if (hp > 0) {
					if(a.type == ATT_DROWNING)
						soundmanager.playSound("water");
					else
						soundmanager.playSound("damaged");
				}

				dead_order = NULL;

				if(GetProperty(TPT_CLOUD) && damage_ > randA(2))
				{
					int max_num_ = min(10,damage_*40/ GetMaxHp());
					burstCloud(half_youkai[1], rand_int(max(0,max_num_-2),max_num_));
				}
				if(s_mirror && GetHp()>0 && a.order)
				{
					a.order->HpUpDown(-damage_,DR_MIRROR, this);	
					//a.order->damage(attack_infor(randA_1(s_value_veiling),s_value_veiling,99,NULL,GetParentType(),ATT_VEILING,name_infor(LOC_SYSTEM_VEILING)), true);
				}
				if(damage_/3 > 0 && a.type == ATT_VAMP && randA(2) == 0)
				{
					if(a.order)
					{
						a.order->HpUpDown(damage_/3,DR_EFFECT);	
						LocalzationManager::printLogWithKey(LOC_SYSTEM_HIT_VAMP,true,false,false,CL_normal,
							 PlaceHolderHelper(a.order->GetName()->getName()),
							 PlaceHolderHelper(name.getName()));
					}
				}
				if (a.type == ATT_LUNATIC && randA(2) == 0) {
					SetLunatic(rand_int(3,8));	
				}

				//SkillTraining(SKT_ARMOUR,3);
			}
			else
			{
				print_no_damage_message(a);
				//SkillTraining(SKT_ARMOUR,2);
			}

			
			if(a.type == ATT_S_POISON && randA(1))
				SetPoison(15+randA(10), 50, false);
			if(a.type == ATT_M_POISON && randA(1))
				SetPoison(40+randA(15), 100, false);
			if(a.type == ATT_SICK && randA(1))
			{

				SetPoison(40+randA(15), 100, false);
				SetSick(rand_int(10,20));
			}
			if(a.type == ATT_THROW_WEAK_POISON)
				SetPoison(20+randA(10), 50, false);
			if(a.type == ATT_THROW_MIDDLE_POISON)
				SetPoison(40+randA(15), 100, false);
			if(a.type == ATT_THROW_STRONG_POISON)
				SetPoison(70+randA(20), 150, true);
			if(a.type == ATT_POISON_BLAST)
				SetPoison(70+randA(20), 150, true);
			if (a.type == ATT_SLEEP) {
				SetSleep(rand_int(10, 25));
			}
			if(a.type == ATT_THROW_FREEZING)
			{
				int frozen_ = randA_1(10);
				frozen_*=GetColdResist();
				SetFrozen(frozen_);

			}
			if (a.type == ATT_FIRE_WEAK) {
				you.SetBuff(BUFFSTAT_RF, BUFF_WEAK_RF, -1, rand_int(30,50));
			}
			if (a.type == ATT_COLD_WEAK) {
				you.SetBuff(BUFFSTAT_RC, BUFF_WEAK_RC, -1, rand_int(30, 50));
			}
			if (a.type == ATT_ELEC_WEAK) {
				you.SetBuff(BUFFSTAT_RE, BUFF_WEAK_RE, -1, rand_int(30, 50));
			}



			if(a.type == ATT_CURSE && randA(1))
			{	
				SetPoison(15+randA(25), 150, true);
				if(randA(3)==1)
					SetSlow(10+randA(10));
				SetPoisonReason(a.p_type);
			}
			if(a.type == ATT_CHOAS)
			{
				GetChoas(this,damage_);
			}

			if(s_veiling && GetHp()>0)
			{
				if(a.order && a.type >=ATT_NORMAL && a.type < ATT_THROW_NORMAL)
				{
					attack_infor attack_infor_(randA_1(s_value_veiling),s_value_veiling,99,this,GetParentType(),ATT_VEILING,name_infor(LOC_SYSTEM_VEILING));
					a.order->damage(attack_infor_, true);
					s_veiling = 0;
					s_value_veiling = 0;
				}
			}

			if(GetProperty(TPT_FORCE_OF_NATURE) && GetHp()>0 && randA(1))
			{
				if(a.order && a.type >=ATT_NORMAL && a.type < ATT_THROW_NORMAL)
				{
					switch(half_youkai[1])
					{
					case 0:
					{
						attack_infor attack_infor_(randC(5,3),randC(5,3),99,NULL,GetParentType(),ATT_CLOUD_FIRE,name_infor(LOC_SYSTEM_ATT_FIRE));
						a.order->damage(attack_infor_, true);
						if(a.order->GetFireResist()>=1.0f){
							a.order->SetSlow(10+randA(5));
						}
						break;
					}
					case 1:
					{
						attack_infor attack_infor_(randC(5,3),randC(5,3),99,NULL,GetParentType(),ATT_CLOUD_COLD,name_infor(LOC_SYSTEM_ATT_COLD));
						a.order->damage(attack_infor_, true);
						if(a.order->GetColdResist()>=1.0f){
							a.order->SetSlow(10+randA(5));
						}
						break;
					}
					case 2:
					{
						attack_infor attack_infor_(randC(5,3),randC(5,3),99,NULL,GetParentType(),ATT_CLOUD_ELEC,name_infor(LOC_SYSTEM_ATT_ELEC));
						a.order->damage(attack_infor_, true);
						if(a.order->GetElecResist()>=1.0f){
							a.order->SetSlow(10+randA(5));
						}
						break;
					}
					}
				}
			}
				
		}
		else
		{
			if (wiz_list.wizard_mode == 1)
			{
				printlog(LocalzationManager::formatString(LOC_SYSTEM_DEBUG_SHIELD_VAULE, PlaceHolderHelper(to_string(shield_))), true, false, false, CL_danger);
			}
			if(a.order)	
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_FIGHT_BLOCK,true,false,false,a.order->isView()?CL_bad:CL_small_danger,
					PlaceHolderHelper(name.getName()),
					PlaceHolderHelper(name_.getName()),
					PlaceHolderHelper(a.name.getName()));
				soundmanager.playSound("block");
			}
		}
	}
	else
	{
		if (a.order)
		{
			if (!graze_ || you.s_super_graze) {
				LocalzationManager::printLogWithKey(LOC_SYSTEM_FIGHT_EVADE,true,false,false,a.order->isView()?CL_bad:CL_small_danger,
					PlaceHolderHelper(name.getName()),
					PlaceHolderHelper(name_.getName()),
					PlaceHolderHelper(a.name.getName()));
			}
			else {
				LocalzationManager::printLogWithKey(LOC_SYSTEM_FIGHT_GRAZE,true,false,false,a.order->isView()?CL_bad:CL_small_danger,
					PlaceHolderHelper(name.getName()),
					PlaceHolderHelper(name_.getName()),
					PlaceHolderHelper(a.name.getName()));
			}
			soundmanager.playSound("evade");
			//if(GetArmourPanlty()<=2)
			//	SkillTraining(SKT_DODGE,3+GetArmourPanlty());
		}
		if(a.order)
		{
			if(!a.order->isView() && you.auto_pickup>0)
				auto_pick_onoff(true);
		}
		return false;
	}
	if(a.order)
	{
		if(!a.order->isView() && you.auto_pickup>0)
			auto_pick_onoff(true);
	}
	return true;
}