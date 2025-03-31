//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: alchemy.cpp
//
// 내용: 연금술 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "alchemy.h"
#include "player.h"
#include "skill_use.h"



bool players::SetAlchemyBuff(ALCHEMY_LIST buff_, int time_)
{
	if(buff_ == alchemy_buff)
	{
		alchemy_time += time_;
		if(Getalchemytime(buff_)<alchemy_time)
			alchemy_time = Getalchemytime(buff_);
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_LONG),false,false,false,CL_white_blue);
	}
	else
	{
		if(alchemy_time)
		{
			alchemyonoff(alchemy_buff,false);
			alchemy_buff = ALCT_NONE;
		}

		alchemy_time = time_;
		if(alchemy_time == 0)
			return false;
		alchemy_buff = buff_;
	
		alchemyonoff(alchemy_buff,true);
	}
	return true;
}
int Getalchemytime(ALCHEMY_LIST list_)
{	
	switch(list_)
	{
	case ALCT_NONE:
	default:
		break;
	case ALCT_STONE_FIST:		
		break;
	case ALCT_DIAMOND_HARDNESS:
		break;
	case ALCT_POISON_BODY:
		break;
	case ALCT_HASTE:
		break;
	case ALCT_STONE_FORM:
		break;
	case ALCT_AUTUMN_BLADE:
		break;
	case ALCT_PHILOSOPHERS_STONE:
		break;
	}
	return 100;
}

void alchemyalmostoff(ALCHEMY_LIST list_)
{	
	switch(list_)
	{
	case ALCT_NONE:
	default:
		break;
	case ALCT_STONE_FIST:		
		break;
	case ALCT_DIAMOND_HARDNESS:
		break;
	case ALCT_POISON_BODY:
		break;
	case ALCT_HASTE:
		if(you.s_haste < 10)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_HASTE_ALMOST_OFF),false,false,false,CL_blue);
		break;
	case ALCT_STONE_FORM:
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_ENLIGHTENMENT_ALMOST_OFF),false,false,false,CL_blue);
		break;
	case ALCT_AUTUMN_BLADE:
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_BLADE_ALMOST_OFF),false,false,false,CL_blue);
		break;
	case ALCT_PHILOSOPHERS_STONE:
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_PHILOSOPHERS_ALMOST_OFF),false,false,false,CL_blue);
		break;
	}
}
void alchemyonoff(ALCHEMY_LIST list_,bool onoff_)
{
	switch(list_)
	{
	case ALCT_NONE:
	default:
		break;
	case ALCT_STONE_FIST:
		if(onoff_)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_STONEFIST_ON),true,false,false,CL_white_blue);
		else
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_STONEFIST_OFF),false,false,false,CL_blue);
		break;
	case ALCT_DIAMOND_HARDNESS:
		you.UpDownBuff(BUFFSTAT_AC,5*(onoff_?1:-1));
		if(onoff_)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_DIAMOND_HARDNESS_ON),true,false,false,CL_white_blue);
		else
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_DIAMOND_HARDNESS_OFF),false,false,false,CL_blue);
		break;
	case ALCT_POISON_BODY:
		if(onoff_)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_POISON_BODY_ON),true,false,false,CL_white_blue);
		else
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_POISON_BODY_OFF),false,false,false,CL_blue);
		break;
	case ALCT_HASTE:
		if(onoff_)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_HASTE_ON),true,false,false,CL_white_blue);
		else if(!you.s_haste)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_HASTE_OFF),false,false,false,CL_blue);
		break;
	case ALCT_STONE_FORM:
		if(onoff_)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_ENLIGHTENMENT_ON),true,false,false,CL_white_blue);
		else
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_ENLIGHTENMENT_OFF),false,false,false,CL_blue);
		break;
	case ALCT_AUTUMN_BLADE:
		if(onoff_)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_BLADE_ON),true,false,false,CL_white_blue);
		else
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_BLADE_OFF),false,false,false,CL_blue);
		break;
	case ALCT_PHILOSOPHERS_STONE:
		you.Ability(SKL_PHILOSOPHERS_1,false,!onoff_);
		you.Ability(SKL_PHILOSOPHERS_2,false,!onoff_);
		you.Ability(SKL_PHILOSOPHERS_3,false,!onoff_);
		you.Ability(SKL_PHILOSOPHERS_4,false,!onoff_);
		you.Ability(SKL_PHILOSOPHERS_5,false,!onoff_);
		if(onoff_)
			printlog(LocalzationManager::formatString(LOC_SYSTEM_SPELL_ALCHEMY_PHILOSOPHERS_ON, PlaceHolderHelper("a")),true,false,false,CL_white_blue);
		else
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ALCHEMY_PHILOSOPHERS_OFF),false,false,false,CL_blue);
		break;

	}
}