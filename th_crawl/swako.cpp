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



const char* GetSwakoString1(swako_1_power power, swako_string kind)
{
	switch(power)
	{
	case SWAKO_1_JUMP:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_JUMP);
		case SWAKO_SIMPLE_INFOR: return "당신은 짧은 거리를 점프할 수 있다.                             (P, 영력)";
		case SWAKO_GET_STRING: return "당신은 이제 짧은 거리를 점프할 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 짧은 거리를 점프할 수 없다.";
		}
		break;
	case SWAKO_1_TEMPLE:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_TEMPLE);
		case SWAKO_SIMPLE_INFOR: return "당신은 신전을 세워 신앙심을 벌 수 있다.                              (P)";
		case SWAKO_GET_STRING: return "당신은 이제 신전을 세울 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 신전을 세울 수 없다.";
		}
		break;
	case SWAKO_1_WATER_GUN:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_WATER_GUN);
		case SWAKO_SIMPLE_INFOR: return "당신은 멀리있는 적에 물의 탄막을 날릴 수 있다.                    (영력)";
		case SWAKO_GET_STRING: return "당신은 이제 물총을 날릴 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 물총을 날릴 수 없다.";
		}
		break;
	case SWAKO_1_TONGUE:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_TOUGUE);
		case SWAKO_SIMPLE_INFOR: return "당신은 멀리있는 적을 끌어 당길 수 있다.                        (P, 영력)";
		case SWAKO_GET_STRING: return "당신은 이제 멀리있는 적을 끌어당길 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 적을 끌어당길 수 없다.";
		}
		break;
	case SWAKO_1_LAST:
		break;
	}
	return "버그";
}

const char* GetSwakoString2(swako_2_power power, swako_string kind)
{
	switch(power)
	{
	case SWAKO_2_KILL_HP:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "죽일때 체력회복";
		case SWAKO_SIMPLE_INFOR: return "당신은 적을 죽일때마다 확률적으로 체력을 회복한다.              (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 적을 죽임으로 체력을 회복할 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 적을 죽여서 체력을 회복할 수 없다.";
		}
		break;
	case SWAKO_2_KILL_MP:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "죽일때 영력회복";
		case SWAKO_SIMPLE_INFOR: return "당신은 적을 죽일때마다 영력을 회복한다.                         (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 적을 죽임으로 영력을 회복할 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 적을 죽여서 영력을 회복할 수 없다.";
		}
		break;
	case SWAKO_2_KILL_POWER:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "죽일때 파워회복";
		case SWAKO_SIMPLE_INFOR: return "당신은 적을 죽일때마다 확률적으로 파워를 회복한다.              (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 적을 죽임으로 파워를 회복할 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 적을 죽여서 파워를 회복할 수 없다.";
		}
		break;
	case SWAKO_2_SWIM:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "수영";
		case SWAKO_SIMPLE_INFOR: return "당신은 수영할 수 있다. 물에서 회피 보너스를 얻는다.             (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 수영할 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 이제 맥주병이다.";
		}
		break;
	case SWAKO_2_DEAD_PROTECT:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "죽음으로부터의 보호";
		case SWAKO_SIMPLE_INFOR: return "스와코가 가끔 당신을 죽음으로부터 보호한다.                     (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 스와코로부터 보호받는다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 스와코로부터 보호받을 수 없다.";
		}
		break;
	case SWAKO_2_LAST:
		break;
	}
	return "버그";
}

const char* GetSwakoString3(swako_3_power power, swako_string kind)
{
	switch(power)
	{
	case SWAKO_3_CURSE:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_CURSE);
		case SWAKO_SIMPLE_INFOR: return "당신은 상대에 재앙을 걸 수 있다.                               (P, 신앙)";
		case SWAKO_GET_STRING: return "당신은 이제 상대를 저주할 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 저주를 걸 수 없다.";
		}
		break;
	case SWAKO_3_DIGGING:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_DIGGING);
		case SWAKO_SIMPLE_INFOR: return "당신은 벽을 무너뜨릴 수 있다.                                  (P, 신앙)";
		case SWAKO_GET_STRING: return "당신은 이제 벽을 무너뜨릴 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 벽을 무너뜨릴 수 없다.";
		}
		break;
	case SWAKO_3_SUMMON_FLOG:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_SUMMON_FLOG);
		case SWAKO_SIMPLE_INFOR: return "당신은 개구리 동료를 소환할 수 있다.                           (P, 신앙)";
		case SWAKO_GET_STRING: return "당신은 이제 개구리를 소환할 수 있다";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 개구리를 소환할 수 없다.";
		}
		break;
	case SWAKO_3_STATUE:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_STATUE);
		case SWAKO_SIMPLE_INFOR: return "당신은 일정시간동안 석상을 세울 수 있다.                       (P, 신앙)";
		case SWAKO_GET_STRING: return "당신은 이제 귀여운 개구리 석상을 세울 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 개구리 석상을 세울 수 없다.";
		}
		break;
	case SWAKO_3_LAST:
		break;
	}
	return "버그";
}

const char* GetSwakoString4(swako_4_power power, swako_string kind)
{
	switch(power)
	{
	case SWAKO_4_COLD_RESIST:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "냉기 저항";
		case SWAKO_SIMPLE_INFOR: return "당신은 냉기에 저항이 있다.                                      (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 냉기에 강하다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 냉기에 강하지 않다.";
		}
		break;
	case SWAKO_4_FIRE_RESIST:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "화염 저항";
		case SWAKO_SIMPLE_INFOR: return "당신은 화염에 저항이 있다.                                      (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 화염에 강하다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 화염에 강하지 않다.";
		}
		break;
	case SWAKO_4_AC:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "피부 강화";
		case SWAKO_SIMPLE_INFOR: return "당신은 AC가 증가한다.                                           (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 피부가 단단해졌다.";
		case SWAKO_UNGET_STRING: return "당신의 피부는 물렁해졌다.";
		}
		break;
	case SWAKO_4_CONFUSE_RESIST:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "혼란 저항";
		case SWAKO_SIMPLE_INFOR: return "당신은 혼란에 저항이 있다.                                      (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 멀미를 하지 않는다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 멀미에 강하지 않다.";
		}
		break;
	case SWAKO_4_POISON_RESIST:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "독 저항";
		case SWAKO_SIMPLE_INFOR: return "당신은 독에 저항이 있다.                                        (패시브)";
		case SWAKO_GET_STRING: return "당신은 이제 독에 강하다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 독에 강하지 않다.";
		}
		break;
	case SWAKO_4_LAST:
		break;
	}
	return "버그";
}

const char* GetSwakoString5(swako_5_power power, swako_string kind)
{
	switch(power)
	{
	case SWAKO_5_RAIN:		
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_RAIN);
		case SWAKO_SIMPLE_INFOR: return "당신은 주변을 물바다로 만들 수 있다.                           (P, 신앙)";
		case SWAKO_GET_STRING: return "당신은 이제 거대한 비를 내리게 할 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 비를 내릴 수 없다.";
		}
		break;
	case SWAKO_5_SLEEP:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_SLEEP);
		case SWAKO_SIMPLE_INFOR: return "당신은 땅속에 숨어서 동면을 취할 수 있다.                      (P, 신앙)";
		case SWAKO_GET_STRING: return "당신은 이제 동면을 한다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 동면을 하지 않는다.";
		}
		break;
	case SWAKO_5_MISYAGUZI:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_MISYAGUZI);
		case SWAKO_SIMPLE_INFOR: return "당신은 미샤구지님을 소환할 수 있다.                            (P, 신앙)";
		case SWAKO_GET_STRING: return "당신은 이제 무시무시한 미샤구지님을 소환할 수 있다.";
		case SWAKO_UNGET_STRING: return "당신은 더 이상 미샤구지님을 소환할 수 없다.";
		}
		break;
	case SWAKO_5_SWAKO_HAT:
		switch(kind)
		{
		case SWAKO_NAME: case SWAKO_STRING: return "스와코님의 모자";
		case SWAKO_SIMPLE_INFOR: return "당신은 스와코님의 귀여운 모자를 받았다.";
		case SWAKO_GET_STRING: return "";
		case SWAKO_UNGET_STRING: return "";
		}
		break;
	case SWAKO_5_LAST:
		break;
	}
	return "버그";
}

bool GetSwakoAbility(int level, bool plus)
{
	switch(level)
	{
	case 1:
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