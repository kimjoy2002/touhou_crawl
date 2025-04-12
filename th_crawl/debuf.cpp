﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: debuf.cpp
//
// 내용: 디버프 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "debuf.h"
#include "beam.h"
#include "unit.h"
#include "throw.h"
#include "environment.h"




unit* DebufBeam(int spell_length_, unit* order, coord_def target)
{

	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam.init();
		int length = spell_length_;
		unit *hit_mon = NULL;
		while(env[current_level].isMove(*(beam),true) && length>0)
		{
			for(vector<monster>::iterator it=env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
			{
				if((*it).isLive() && (*it).position.x == (*beam).x && (*it).position.y == (*beam).y)
				{
					hit_mon = &(*it);
				}
			}
			if( you.position.x == (*beam).x && you.position.y == (*beam).y)
			{				
				hit_mon = &you;
			}
			length--;
			beam++;
			if(hit_mon)
			{
				if(hit_mon == order && target != hit_mon->position)
				{
					hit_mon = NULL;
					continue;
				}
				return hit_mon;
			}
		}
	}
	return NULL;
}

unit* DebufBeam(spell_list spell_, unit* order, coord_def target)
{
	return DebufBeam(SpellLength(spell_),order, target);
}
unit* DebufBeam(skill_list skill_, unit* order, coord_def target)
{
	return DebufBeam(SkillLength(skill_),order, target);
}

int power_calculate(int resist, int power)
{
	return resist - power;
}
float getDebufPercent(int resist, int power)
{
	int percent_ = power_calculate(resist, power);
	if (percent_ <= 1)
	{
		percent_ = 0;
	}
	else if (percent_ <= 101)
	{
		percent_ = percent_*(percent_ - 1) / 2;
	}
	else if (percent_ <= 200)
	{
		percent_ -= 101;
		percent_ = 5050 + percent_*(199 - percent_) / 2;
	}
	else
	{
		percent_ = 10000;
	}


	return (10000 - percent_) / 100.0f;
}

bool unit::CalcuateMR(int power)
{
	if (wiz_list.wizard_mode == 1)
	{
		char temp[100];
		sprintf_s(temp, 100, "디버프계산: 몬스터(%d) - 파워(%d) < randC(2,100)", GetResist(), power);
		printarray(true, false, false, CL_help, 1, temp);
	}
	return GetMindReading() ? true : power_calculate(GetResist(), power) < randC(2, 100);
}

int GetDebufPower(spell_list skill, int power_)
{
	switch(skill)
	{
	case SPL_CONFUSE:
		return power_-10;
	case SPL_SLOW:
		return power_-10;
	case SPL_GLOW:
		return power_-10;
	case SPL_TELEPORT_OTHER:
		return power_;
	case SPL_HYPNOSIS:
		return power_+40;
	case SPL_MUTE:
		return power_-10;
	case SPL_SELF_INJURY:
		return power_+10;
	case SPL_CHARM:
		return power_;
	case SPL_MIND_BENDING:
		return power_-10;
	case SPL_ANIMAL_CHANGE:
		return power_-10;
	case SPL_PRIVATE_SQ:
		return power_;
	case SPL_INSANE:
		return power_+20;
	case SPL_STASIS:
		return power_+20;
	case SPL_MESS_CONFUSION:
		return power_-10;
	default:
		return power_-10;
	}
}
int GetDebufPower(skill_list skill, int power_)
{
	switch(skill)
	{
	case SKL_SIZUHA_1:
		return power_;
	case SKL_SATORI_1:
		return power_;
	default:
		return power_;
	}
}