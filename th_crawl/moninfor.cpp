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


string GetMonsterInfor(monster *it)
{
	string text_ = it->GetNameString();
	text_ += "\n\n";

	if (it->dream) {
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_DREAM);
	}
	else {
		text_+=LocalzationManager::monDecsriptionString((monster_index)it->id);
	}
	text_ += "\n\n\n";

	if(it->id == MON_REIMU)
	{
		text_ += LocalzationManager::formatString(LOC_SYSTEM_MONSTER_DESCRIPTION_REIMU_CONTINUE, PlaceHolderHelper(to_string(max(0,you.reimu_level - 1))));
		text_ += "\n";
	}

	{
		int mon_level_ = it->level;
		if (it->flag & M_FLAG_UNIQUE)
			mon_level_ += 3;
		int you_level_ = you.level+3;

		if (you_level_ - mon_level_*3 > 3)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_WEAKER);
		else if (you_level_ - mon_level_*2 > 0)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_WEAK);
		else if (you.level - mon_level_ > 0)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_STRONG);
		else
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_STRONGER);
		text_ += "\n";
	}



	if(it->poison_resist)
	{
		if(it->poison_resist>0)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_POISON_RESIST);
		else
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_POISON_WEAKNESS);
		text_ += "\n";
	}
	if(it->fire_resist)
	{
		if(it->fire_resist==1)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_FIRE_RESIST);
		else if(it->fire_resist==2)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_FIRE_RESIST_MORE);
		else if(it->fire_resist>=3)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_FIRE_IMMUN);
		else
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_FIRE_WEAKNESS);
		text_ += "\n";
	}
	if(it->ice_resist)
	{
		if(it->ice_resist==1)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_COLD_RESIST);
		else if(it->ice_resist==2)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_COLD_RESIST_MORE);
		else if(it->ice_resist>=3)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_COLD_IMMUN);
		else
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_COLD_WEAKNESS);
		text_ += "\n";
	}
	if(it->elec_resist)
	{
		if(it->elec_resist==1)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_ELEC_RESIST);
		else if(it->elec_resist==2)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_ELEC_RESIST_MORE);
		else if(it->elec_resist>=3)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_ELEC_IMMUN);
		else
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_ELEC_WEAKNESS);
		text_ += "\n";
	}



	if(it->confuse_resist)
	{
		if(it->confuse_resist>0) {
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_CONFUSE_RESIST);
			text_ += "\n";
		}
	}
	if(it->wind_resist)
	{
		if(it->wind_resist>0) {
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_WIND_RESIST);
			text_ += "\n";
		}
	}
	if(it->speed != 10)
	{
		if(it->speed<=5)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED1);
		else if(it->speed<=7)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED2);
		else if(it->speed<=9)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED3);
		else if(it->speed<=13)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED4);
		else if(it->speed<=18)
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED5);
		else
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SPEED6);
		text_ += "\n";
	}
	if(it->isFly()) {
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_CAN_FLY);
		text_ += "\n";
	}
	if (it->isSwim()) {
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_CAN_SWIM);
		text_ += "\n";
	}
	if(it->flag & M_FLAG_CAN_SEE_INVI) {
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_CAN_SEE_INVISIBLE);
		text_ += "\n";
	}
	if(it->flag & M_FLAG_INANIMATE) {
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_INANIMATE);
		text_ += "\n";
	}
	if(it->flag & M_FLAG_RESIST_BLIZARD) {
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_RESIST_BLIZARD);
		text_ += "\n";
	}
	
	if(it->resist >= 99) {
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_DEBUFF_IMMUN);
		text_ += "\n";
	}
	else
	{
		text_ += LocalzationManager::locString(LOC_SYSTEM_MAGIC_RESIST);
		text_ += ": ";
		for (int i = 0; i < 10; i++ ) {
			if (it->GetResist() > 110 + i * 20) {
				text_ += "#";
			}
			else {
				text_ += ".";
			}
		}
		text_ += "\n";
	}
	if (it->flag & M_FLAG_SILENCE) {
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SILENCE);
		text_ += "\n";
	}


	
	if(it->flag & M_FLAG_SUMMON)
	{
		text_ += "\n\n";
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SUMMONED);
		text_ += "\n";
	}
	if (it->dream)
	{
		text_ += "\n";
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_DREAM_IMMUN);
		text_ += "\n";
	}

	if(!it->spell_lists.empty())
	{
		text_ += "\n\n\n";
		text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_USE_MAGIC);
		text_ += "\n\n";


		if(!it->isUserAlly() && it->random_spell)
		{
			text_ += LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_RANDOM_MAGIC);
			text_ += "\n";
		}
		else
		{
			int i = 0;
			ostringstream ss;
			for(auto its = it->spell_lists.begin(); its != it->spell_lists.end(); its++)
			{
				char sp_char = (i<27)?('a'+i):('A'+i-27);
				spell_list spell_ = (spell_list)its->num;
				
				ss << sp_char << " - " << SpellString(spell_);
			
				if(SpellFlagCheck(spell_, S_FLAG_DEBUF))
				{
					int value_ = GetDebufPower(spell_, min(SpellCap(spell_),(it->level-3)*5));
					float percent_ = getDebufPercent (you.GetResist(), value_);
					ss << " (" << std::fixed << std::setprecision(0) << percent_ << "%)";
				}

				ss << "\n";
				i++;
			}
			text_ += ss;
		}

	}


	return text_;

}