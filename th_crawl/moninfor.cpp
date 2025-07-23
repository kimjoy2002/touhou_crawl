//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: moninfor.cpp
//
// 내용: 몬스터의 정보띄우기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "monster.h"
#include "mon_infor.h"
#include "skill_use.h"
#include "player.h"
#include "debuf.h"
#include <iomanip> 

extern HANDLE mutx;


void _infor_(string str);

bool maybeUpgrade(int mon_id) {
	switch(mon_id) {
		case MON_GHOST:
		case MON_ONBASIRA:
		case MON_MAGICAL_STAR:
		case MON_GOLEM:
		case MON_SCHEMA_EYE:
		case MON_CLOSE_DOOR:
		case MON_KUNEKUNE:
		case MON_KANAME:
		case MON_HANIWA:
		case MON_SECURIRY_DOOR:
		case MON_COGWHEEL:
			return true;
	}
	return false;
}


LOCALIZATION_ENUM_KEY getKeyOfAttack(attack_type type) {
	switch(type) {
	case ATT_FIRE:
	case ATT_FIREPLUS:
		return LOC_SYSTEM_ATT_INFO_FIRE;
	case ATT_COLD:
		return LOC_SYSTEM_ATT_INFO_COLD;
	case ATT_ELEC:
		return LOC_SYSTEM_ATT_INFO_ELEC;
	case ATT_FIRE_WEAK:
	case ATT_COLD_WEAK:
	case ATT_ELEC_WEAK:
		return LOC_SYSTEM_ATT_INFO_DOWN_RESIST;
	case ATT_S_POISON:
	case ATT_M_POISON:
		return LOC_SYSTEM_ATT_INFO_POISON;
	case ATT_SLOW_POISON:
		return LOC_SYSTEM_ATT_INFO_POISON_SLOW;
	case ATT_SICK:
		return LOC_SYSTEM_ATT_INFO_POISON_SICK;
	case ATT_VAMP:
		return LOC_SYSTEM_ATT_INFO_VAMP;
	case ATT_LUNATIC:
		return LOC_SYSTEM_ATT_INFO_LUNATIC;
	case ATT_SLEEP:
		return LOC_SYSTEM_ATT_INFO_SLEEP;
	case ATT_BEARTRAP:
		return LOC_SYSTEM_ATT_INFO_BEARTRAP;
	default:
		break;
	}
	return LOC_NONE;
}



void GetMonsterInfor(monster *it)
{
	string blank(12,' ');
	
	deletesub();
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub(blank,false,CL_normal);

	
	_infor_(it->GetNameString());
	_infor_("\n\n");

	
	if (it->dream) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_DREAM));
	}
	else {
		_infor_(LocalzationManager::monDecsriptionString((monster_index)it->id));
	}
	_infor_("\n\n");

	set<LOCALIZATION_ENUM_KEY> all_key;
	if(maybeUpgrade(it->id)) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ABOUT_SPEC_MAYBE));
		_infor_("\n");
	} else if(it->id >= 0 && it->id < MON_MAX) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ABOUT_SPEC));
		_infor_("\n");
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ABOUT_MAX_HP));
		_infor_(": ");
		_infor_(std::to_string(mondata[it->id].max_hp));
		_infor_("\n");
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ABOUT_AC));
		_infor_(": ");
		_infor_(std::to_string(mondata[it->id].ac));
		_infor_("\n");
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ABOUT_EV));
		_infor_(": ");
		_infor_(std::to_string(mondata[it->id].ev));
		_infor_("\n");
		if(!(mondata[it->id].flag & M_FLAG_NO_ATK)) {
			int aver_damage = 0;
			int max_damage = 0;
			int att_ = 0;
			for(int i = 0; i < 3;i++) {
				if(mondata[it->id].atk_type[i] != ATT_NONE) {
					aver_damage+=mondata[it->id].atk[i];
					if(mondata[it->id].atk[i] > max_damage)
						max_damage = mondata[it->id].atk[i];
					all_key.insert(getKeyOfAttack(mondata[it->id].atk_type[i]));
					att_ ++;
				}
			}
			if(aver_damage > 0 && att_ > 0 ) {
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ABOUT_DAMAGE));
				_infor_(": ");
				float value = (int)(aver_damage / att_) / 2.0f;
				std::ostringstream oss;
				oss << std::fixed << std::setprecision((value == (int)value) ? 0 : 1) << value;
				_infor_(oss.str());
				_infor_(" (1~");
				_infor_(std::to_string((int)(max_damage)));
				_infor_(")");
				_infor_("\n");
			}
		}
	}

	_infor_("\n");

	if(it->id == MON_REIMU)
	{
		_infor_(LocalzationManager::formatString(LOC_SYSTEM_MONSTER_DESCRIPTION_REIMU_CONTINUE, PlaceHolderHelper(to_string(max(0,you.reimu_level - 1)))));
		_infor_("\n");
	}

	{
		int mon_level_ = it->level;
		if (it->flag & M_FLAG_UNIQUE)
			mon_level_ += 3;
		int you_level_ = you.level+3;

		if (you_level_ - mon_level_*3 > 3)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_WEAKER));
		else if (you_level_ - mon_level_*2 > 0)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_WEAK));
		else if (you.level - mon_level_ > 0)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_STRONG));
		else
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_STRONGER));
		_infor_("\n");
	}

	for( auto key : all_key) {
		if(key != LOC_NONE) {
			_infor_(LocalzationManager::locString(key));
			_infor_("\n");
		}
	}


	if(it->poison_resist)
	{
		if(it->poison_resist>0)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_POISON_RESIST));
		else
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_POISON_WEAKNESS));
		_infor_("\n");
	}
	if(it->fire_resist)
	{
		if(it->fire_resist==1)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_FIRE_RESIST));
		else if(it->fire_resist==2)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_FIRE_RESIST_MORE));
		else if(it->fire_resist>=3)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_FIRE_IMMUN));
		else
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_FIRE_WEAKNESS));
		_infor_("\n");
	}
	if(it->ice_resist)
	{
		if(it->ice_resist==1)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_COLD_RESIST));
		else if(it->ice_resist==2)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_COLD_RESIST_MORE));
		else if(it->ice_resist>=3)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_COLD_IMMUN));
		else
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_COLD_WEAKNESS));
		_infor_("\n");
	}
	if(it->elec_resist)
	{
		if(it->elec_resist==1)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_ELEC_RESIST));
		else if(it->elec_resist==2)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_ELEC_RESIST_MORE));
		else if(it->elec_resist>=3)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_ELEC_IMMUN));
		else
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_ELEC_WEAKNESS));
		_infor_("\n");
	}



	if(it->confuse_resist)
	{
		if(it->confuse_resist>0) {
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_CONFUSE_RESIST));
			_infor_("\n");
		}
	}
	if(it->wind_resist)
	{
		if(it->wind_resist>0) {
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_WIND_RESIST));
			_infor_("\n");
		}
	}
	if(it->speed != 10)
	{
		if(it->speed<=5)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED1));
		else if(it->speed<=7)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED2));
		else if(it->speed<=9)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED3));
		else if(it->speed<=13)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED4));
		else if(it->speed<=18)
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED5));
		else
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED6));
		_infor_("\n");
	}
	if(it->isFly()) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_CAN_FLY));
		_infor_("\n");
	}
	if (it->isSwim()) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_CAN_SWIM));
		_infor_("\n");
	}
	if(it->flag & M_FLAG_CAN_SEE_INVI) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_CAN_SEE_INVISIBLE));
		_infor_("\n");
	}
	if(it->flag & M_FLAG_SPEAR_ATTACK) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEAR_ATTACK));
		_infor_("\n");
	}
	if(it->flag & M_FLAG_INANIMATE) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_INANIMATE));
		_infor_("\n");
	}
	if(it->flag & M_FLAG_RESIST_BLIZARD) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_RESIST_BLIZARD));
		_infor_("\n");
	}
	
	if (it->flag & M_FLAG_SILENCE) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SILENCE));
		_infor_("\n");
	}

	bool enter_ = false;
	if(it->flag & M_FLAG_SUMMON)
	{
		if(!enter_) {
			_infor_("\n");
			enter_ = true;
		}
		_infor_("\n");
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SUMMONED));
		_infor_("\n");
	}
	if(it->flag & M_FLAG_COMPLETE_NETURALY)
	{
		if(!enter_) {
			_infor_("\n");
			enter_ = true;
		}
		_infor_("\n");
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_COMPLETE_NATURAL));
		_infor_("\n");
	}
	if (it->dream)
	{
		if(!enter_) {
			_infor_("\n");
			enter_ = true;
		}
		_infor_("\n");
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_DREAM_IMMUN));
		_infor_("\n");
	}

	_infor_("\n");
	if(it->resist >= 99) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_DEBUFF_IMMUN));
		_infor_("\n");
	}
	else
	{
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MAGICRESIST));
		_infor_(": ");
		for (int i = 0; i < 10; i++ ) {
			if (it->GetResist() > 110 + i * 20) {
				_infor_("#");
			}
			else {
				_infor_(".");
			}
		}
		_infor_("\n");
	}

	if(!it->spell_lists.empty())
	{
		_infor_("\n\n");
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_USE_MAGIC));
		_infor_("\n\n");


		if(!it->isUserAlly() && it->random_spell)
		{
			_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_RANDOM_MAGIC));
			_infor_("\n");
		}
		else
		{
			int i = 0;
			for(auto its = it->spell_lists.begin(); its != it->spell_lists.end(); its++)
			{
				ostringstream ss;
				char sp_char = (i<27)?('a'+i):('A'+i-27);
				spell_list spell_ = (spell_list)its->num;
				
				ss << sp_char << " - " << SpellString(spell_);
			
				if(SpellFlagCheck(spell_, S_FLAG_DEBUF))
				{
					int value_ = GetDebufPower(spell_, min(SpellCap(spell_),(it->level-3)*5));
					float percent_ = getDebufPercent (you.GetResist(), value_);
					ss << " (" << std::fixed << std::setprecision(0) << percent_ << "%)";
				}
				printsub(ss.str(), false, CL_normal, sp_char);

				_infor_("\n");
				i++;
			}
		}

	}


	return;

}