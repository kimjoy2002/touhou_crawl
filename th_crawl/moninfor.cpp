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
	_infor_("\n\n\n");

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
	if(it->flag & M_FLAG_INANIMATE) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_INANIMATE));
		_infor_("\n");
	}
	if(it->flag & M_FLAG_RESIST_BLIZARD) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_RESIST_BLIZARD));
		_infor_("\n");
	}
	
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
	if (it->flag & M_FLAG_SILENCE) {
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SILENCE));
		_infor_("\n");
	}


	
	if(it->flag & M_FLAG_SUMMON)
	{
		_infor_("\n\n");
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_SUMMONED));
		_infor_("\n");
	}
	if (it->dream)
	{
		_infor_("\n");
		_infor_(LocalzationManager::locString(LOC_SYSTEM_MONSTER_DESCRIPTION_DREAM_IMMUN));
		_infor_("\n");
	}

	if(!it->spell_lists.empty())
	{
		_infor_("\n\n\n");
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