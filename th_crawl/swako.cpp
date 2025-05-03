//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: swako.cpp
//
// 내용: 스와코 권능 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "swako.h"
#include "player.h"
#include "skill_use.h"
#include "god.h"



string GetSwakoString1(swako_1_power power, swako_string kind)
{
	if(you.god_value[GT_SUWAKO][5] < 1) {
		if(kind == SWAKO_SIMPLE_INFOR) {
			return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY_UNKNOWN);
		}
		else if(kind == SWAKO_COST) {
			return "";
		}
	}
	switch(power)
	{
	case SWAKO_1_JUMP:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_JUMP);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY1_JUMP);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_MP);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY1_JUMP_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY1_JUMP_REMOVE);
		}
		break;
	case SWAKO_1_TEMPLE:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_TEMPLE);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY1_TEMPLE);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY1_TEMPLE_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY1_TEMPLE_REMOVE);
		}
		break;
	case SWAKO_1_WATER_GUN:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_WATER_GUN);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY1_WATER_GUN);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_MP);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY1_WATER_GUN_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY1_WATER_GUN_REMOVE);
		}
		break;
	case SWAKO_1_TONGUE:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_TOUGUE);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY1_TONGUE);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_MP);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY1_TONGUE_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY1_TONGUE_REMOVE);
		}
		break;
	case SWAKO_1_LAST:
		break;
	}
	return LocalzationManager::locString(LOC_SYSTEM_BUG);
}

string GetSwakoString2(swako_2_power power, swako_string kind)
{
	if(you.god_value[GT_SUWAKO][5] < 2) {
		if(kind == SWAKO_SIMPLE_INFOR) {
			return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY_UNKNOWN);
		}
		else if(kind == SWAKO_COST) {
			return "";
		}
	}
	switch(power)
	{
	case SWAKO_2_KILL_HP:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_KILL_HP);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY2_KILL_HP);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_KILL_HP_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_KILL_HP_REMOVE);
		}
		break;
	case SWAKO_2_KILL_MP:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_KILL_MP);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY2_KILL_MP);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_KILL_MP_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_KILL_MP_REMOVE);
		}
		break;
	case SWAKO_2_KILL_POWER:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_KILL_POWER);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY2_KILL_POWER);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_KILL_POWER_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_KILL_POWER_REMOVE);
		}
		break;
	case SWAKO_2_SWIM:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_SWIM);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY2_SWIM);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_SWIM_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_SWIM_REMOVE);
		}
		break;
	case SWAKO_2_DEAD_PROTECT:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_DEAD_PROTECT);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY2_DEAD_PROTECT);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_DEAD_PROTECT_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY2_DEAD_PROTECT_REMOVE);
		}
		break;
	case SWAKO_2_LAST:
		break;
	}
	return LocalzationManager::locString(LOC_SYSTEM_BUG);
}

string GetSwakoString3(swako_3_power power, swako_string kind)
{
	if(you.god_value[GT_SUWAKO][5] < 3) {
		if(kind == SWAKO_SIMPLE_INFOR) {
			return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY_UNKNOWN);
		}
		else if(kind == SWAKO_COST) {
			return "";
		}
	}
	switch(power)
	{
	case SWAKO_3_CURSE:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_CURSE);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY3_CURSE);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY3_CURSE_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY3_CURSE_REMOVE);
		}
		break;
	case SWAKO_3_DIGGING:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_DIGGING);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY3_DIGGING);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY3_DIGGING_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY3_DIGGING_REMOVE);
		}
		break;
	case SWAKO_3_SUMMON_FLOG:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_SUMMON_FLOG);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY3_SUMMON_FLOG);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY3_SUMMON_FLOG_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY3_SUMMON_FLOG_REMOVE);
		}
		break;
	case SWAKO_3_STATUE:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_STATUE);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY3_STATUE);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY3_STATUE_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY3_STATUE_REMOVE);
		}
		break;
	case SWAKO_3_LAST:
		break;
	}
	return LocalzationManager::locString(LOC_SYSTEM_BUG);
}

string GetSwakoString4(swako_4_power power, swako_string kind)
{
	if(you.god_value[GT_SUWAKO][5] < 4) {
		if(kind == SWAKO_SIMPLE_INFOR) {
			return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY_UNKNOWN);
		}
		else if(kind == SWAKO_COST) {
			return "";
		}
	}

	switch(power)
	{
	case SWAKO_4_COLD_RESIST:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_COLD_RESIST);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY4_COLD_RESIST);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_COLD_RESIST_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_COLD_RESIST_REMOVE);
		}
		break;
	case SWAKO_4_FIRE_RESIST:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_FIRE_RESIST);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY4_FIRE_RESIST);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_FIRE_RESIST_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_FIRE_RESIST_REMOVE);
		}
		break;
	case SWAKO_4_AC:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_AC);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY4_AC);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_AC_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_AC_REMOVE);
		}
		break;
	case SWAKO_4_CONFUSE_RESIST:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_CONF_RESIST);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY4_CONFUSE_RESIST);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_CONFUSE_RESIST_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_CONFUSE_RESIST_REMOVE);
		}
		break;
	case SWAKO_4_POISON_RESIST:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_POISON_RESIST);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY4_POISON_RESIST);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PASSIVE);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_POISON_RESIST_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY4_POISON_RESIST_REMOVE);
		}
		break;
	case SWAKO_4_LAST:
		break;
	}
	return LocalzationManager::locString(LOC_SYSTEM_BUG);
}

string GetSwakoString5(swako_5_power power, swako_string kind)
{
	if(you.god_value[GT_SUWAKO][5] < 5) {
		if(kind == SWAKO_SIMPLE_INFOR) {
			return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY_UNKNOWN);
		}
		else if(kind == SWAKO_COST) {
			return "";
		}
	}
	switch(power)
	{
	case SWAKO_5_RAIN:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_RAIN);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY5_RAIN);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY5_RAIN_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY5_RAIN_REMOVE);
		}
		break;
	case SWAKO_5_SLEEP:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_SLEEP);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY5_SLEEP);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY5_SLEEP_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY5_SLEEP_REMOVE);
		}
		break;
	case SWAKO_5_MISYAGUZI:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_MISYAGUZI);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY5_MISYAGUZI);
		case SWAKO_COST: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_AND_PIETY);
		case SWAKO_GET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY5_MISYAGUZI_ADD);
		case SWAKO_UNGET_STRING: return LocalzationManager::locString(LOC_SYSTEM_GOD_SWAKO_GAIN_ABLILITY5_MISYAGUZI_REMOVE);
		}
		break;
	case SWAKO_5_SWAKO_HAT:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_SWAKO_HAT);
		case SWAKO_SIMPLE_INFOR: return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_SWAKO_ABLILITY5_SWAKO_HAT);
		case SWAKO_COST: return "";
		case SWAKO_GET_STRING: return "";
		case SWAKO_UNGET_STRING: return "";
		}
		break;
	case SWAKO_5_LAST:
		break;
	}
	return LocalzationManager::locString(LOC_SYSTEM_BUG);
}

bool GetSwakoAbility(int level, bool plus)
{
	switch(level)
	{
	case 1:
		if(you.god_value[GT_SUWAKO][5] < 1)
			you.god_value[GT_SUWAKO][5] = 1;
		switch(you.god_value[GT_SUWAKO][0])
		{
		case SWAKO_1_JUMP:	
			you.Ability(SKL_SWAKO_JUMP,true,!plus);
			break;
		case SWAKO_1_TEMPLE:
			you.Ability(SKL_SWAKO_TEMPLE,true,!plus);
			break;
		case SWAKO_1_WATER_GUN:
			you.Ability(SKL_SWAKO_WATER_GUN,true,!plus);
			break;
		case SWAKO_1_TONGUE:
			you.Ability(SKL_SWAKO_TOUGUE,true,!plus);
			break;
		}
		if(plus)
			printlog(GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][0],SWAKO_GET_STRING),true,false,false,CL_swako);	
		else
			printlog(GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][0],SWAKO_UNGET_STRING),true,false,false,CL_swako);
		break;
	case 2:
		if(you.god_value[GT_SUWAKO][5] < 2)
			you.god_value[GT_SUWAKO][5] = 2;
		switch(you.god_value[GT_SUWAKO][1])
		{
		case SWAKO_2_KILL_HP:	
			break;
		case SWAKO_2_KILL_MP:
			break;
		case SWAKO_2_KILL_POWER:
			break;
		case SWAKO_2_SWIM:
			break;
		case SWAKO_2_DEAD_PROTECT:
			break;
		}
		if(plus)
			printlog(GetSwakoString2((swako_2_power)you.god_value[GT_SUWAKO][1],SWAKO_GET_STRING),true,false,false,CL_swako);	
		else
			printlog(GetSwakoString2((swako_2_power)you.god_value[GT_SUWAKO][1],SWAKO_UNGET_STRING),true,false,false,CL_swako);
		break;
	case 3:
		if(you.god_value[GT_SUWAKO][5] < 3)
			you.god_value[GT_SUWAKO][5] = 3;
		switch(you.god_value[GT_SUWAKO][2])
		{
		case SWAKO_3_CURSE:	
			you.Ability(SKL_SWAKO_CURSE,true,!plus);
			break;
		case SWAKO_3_DIGGING:
			you.Ability(SKL_SWAKO_DIGGING,true,!plus);
			break;
		case SWAKO_3_SUMMON_FLOG:
			you.Ability(SKL_SWAKO_SUMMON_FLOG,true,!plus);
			break;
		case SWAKO_3_STATUE:
			you.Ability(SKL_SWAKO_STATUE,true,!plus);
			break;
		}
		if(plus)
			printlog(GetSwakoString3((swako_3_power)you.god_value[GT_SUWAKO][2],SWAKO_GET_STRING),true,false,false,CL_swako);	
		else
			printlog(GetSwakoString3((swako_3_power)you.god_value[GT_SUWAKO][2],SWAKO_UNGET_STRING),true,false,false,CL_swako);
		break;
	case 4:
		if(you.god_value[GT_SUWAKO][5] < 4)
			you.god_value[GT_SUWAKO][5] = 4;
		switch(you.god_value[GT_SUWAKO][3])
		{
		case SWAKO_4_COLD_RESIST:	
			you.ResistUpDown(plus?1:-1,RST_ICE);
			break;
		case SWAKO_4_FIRE_RESIST:
			you.ResistUpDown(plus?1:-1,RST_FIRE);
			break;
		case SWAKO_4_AC:
			you.AcUpDown(0,plus?5:-5);
			break;
		case SWAKO_4_CONFUSE_RESIST:
			you.ResistUpDown(plus?1:-1,RST_CONFUSE);
			break;
		case SWAKO_4_POISON_RESIST:
			you.ResistUpDown(plus?1:-1,RST_POISON);
			break;
		}
		if(plus)
			printlog(GetSwakoString4((swako_4_power)you.god_value[GT_SUWAKO][3],SWAKO_GET_STRING),true,false,false,CL_swako);	
		else
			printlog(GetSwakoString4((swako_4_power)you.god_value[GT_SUWAKO][3],SWAKO_UNGET_STRING),true,false,false,CL_swako);
		break;
	case 5:
		if(you.god_value[GT_SUWAKO][5] < 5)
			you.god_value[GT_SUWAKO][5] = 5;
		switch(you.god_value[GT_SUWAKO][4])
		{
		case SWAKO_5_RAIN:	
			you.Ability(SKL_SWAKO_RAIN,true,!plus);
			break;
		case SWAKO_5_SLEEP:
			you.Ability(SKL_SWAKO_SLEEP,true,!plus);
			break;
		case SWAKO_5_MISYAGUZI:
			you.Ability(SKL_SWAKO_MISYAGUZI,true,!plus);
			break;
		case SWAKO_5_SWAKO_HAT:
			if (you.suwako_meet == 1 && plus) {
				GodGift(GT_SUWAKO, you.piety);
				you.suwako_meet = 2;
			}
			return true;
		}
		if((swako_5_power)you.god_value[GT_SUWAKO][4] != SWAKO_5_SWAKO_HAT)
		{
			if(plus)
				printlog(GetSwakoString5((swako_5_power)you.god_value[GT_SUWAKO][4],SWAKO_GET_STRING),true,false,false,CL_swako);	
			else
				printlog(GetSwakoString5((swako_5_power)you.god_value[GT_SUWAKO][4],SWAKO_UNGET_STRING),true,false,false,CL_swako);
		}
		break;
	}
	return true;
}