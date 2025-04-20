//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: skill.cpp
//
// 내용: 스킬사용건
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "player.h"
#include "skill_use.h"
#include "throw.h"
#include "key.h"
#include "environment.h"
#include "mon_infor.h"
#include "projectile.h"
#include "god.h"
#include "dump.h"
extern HANDLE mutx;


bool SkillFlagCheck(skill_list skill, skill_flag flag)
{
	switch(skill)
	{
	case SKL_KANAKO_2:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_SUMMON | S_FLAG_GOD) & flag);
	case SKL_KANAKO_1:
	case SKL_YUYUKO_3:
	case SKL_OKINA_3:
	case SKL_JUNKO_1:
	case SKL_JOON_AND_SION_4:
		return ((S_FLAG_SPEAK | S_FLAG_GOD) & flag);
	case SKL_OKINA_1:
		return ((S_FLAG_SPEAK | S_FLAG_NO_TARGET | S_FLAG_GOD) & flag);
	case SKL_SWAKO_DIGGING:
		return ((S_FLAG_SPEAK | S_FLAG_UNSIGHT | S_FLAG_GOD) & flag);
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
		return (S_FLAG_GOD & flag);
	case SKL_EIRIN_0:
		return ((S_FLAG_SPEAK | S_FLAG_CLOUD | S_FLAG_GOD) & flag);
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_SATORI_2:
	case SKL_YUYUKO_1:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_STATUE:
	case SKL_YUKARI_4:
	case SKL_SEIJA_1:
	case SKL_LILLY_1:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_GOD) & flag);
	case SKL_OKINA_2: //문전용으로 변경
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_NO_TARGET | S_FLAG_GOD) & flag);
	case SKL_SWAKO_JUMP:
		return ((S_FLAG_SMITE | S_FLAG_RECT | S_FLAG_NO_TARGET | S_FLAG_GOD) & flag);		
	case SKL_YUKARI_2:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_SUKIMA | S_FLAG_GOD) & flag);
	case SKL_LILLY_3:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_OTHER_BUF | S_FLAG_GOD) & flag);
	case SKL_YUKARI_1:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_SUMMON | S_FLAG_SUKIMA | S_FLAG_GOD) & flag);
	case SKL_SATORI_1:
		return ((S_FLAG_SPEAK | S_FLAG_DEBUF | S_FLAG_SMITE | S_FLAG_GOD) & flag);
	case SKL_KANAKO_3:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_SIZUHA_2:
	case SKL_SIZUHA_3:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_YUUGI_1:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_YUYUKO_2:
	case SKL_YUKARI_3:
	case SKL_SWAKO_SLEEP:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
	case SKL_HINA_5:
	case SKL_SEIJA_2:
	case SKL_LILLY_2:
	case SKL_LILLY_4:
	case SKL_OKINA_4:
	case SKL_OKINA_5:
	case SKL_JUNKO_2:
	case SKL_JUNKO_3:
	case SKL_JUNKO_4:
	case SKL_JOON_AND_SION_1:
	case SKL_JOON_AND_SION_OFF:
	case SKL_JOON_AND_SION_2:
	case SKL_JOON_AND_SION_3:
	case SKL_MIKO_1:
	case SKL_MIKO_2:
	case SKL_MIKO_3:
	case SKL_MIKO_4:
	case SKL_MIKO_5:
	case SKL_MIKO_6:
		return ((S_FLAG_SPEAK | S_FLAG_IMMEDIATELY | S_FLAG_GOD) & flag);
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_2:	
	case SKL_PHILOSOPHERS_3:
		return (S_FLAG_RANGE_ATTACK) & flag;
	case SKL_PHILOSOPHERS_4:
		return (S_FLAG_IMMEDIATELY) & flag;
	case SKL_PHILOSOPHERS_5:
		return (S_FLAG_SMITE) & flag;
	case SKL_SWAKO_TEMPLE:
		return ((S_FLAG_IMMEDIATELY | S_FLAG_GOD) & flag);		
	case SKL_SHINKI_1:
	case SKL_SHINKI_2:
	case SKL_SHINKI_3:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_MISYAGUZI:
		return ((S_FLAG_SPEAK | S_FLAG_IMMEDIATELY | S_FLAG_SUMMON | S_FLAG_GOD) & flag);
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_SEIJA_GIFT:
		return ((S_FLAG_IMMEDIATELY | S_FLAG_GOD) & flag);
	case SKL_GRAZE:
	case SKL_LEVITATION:
	case SKL_INVISIBLE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_TORMENT:
	case SKL_ABANDON_GOD:
		return ((S_FLAG_IMMEDIATELY) & flag);
	case SKL_NONE:
	case SKL_BREATH:
		return ((S_FLAG_DELAYED) & flag);
	case SKL_JUMPING_ATTACK:
		return ((S_FLAG_SMITE | S_FLAG_DELAYED) & flag);
	default:
		return false;
	}
}
int SkillLength(skill_list skill)
{
	switch(skill)
	{		
	case SKL_SWAKO_JUMP:
		 return 2;
	case SKL_KANAKO_2:
		return 3;
	case SKL_JUMPING_ATTACK:
		return 4;
	case SKL_SWAKO_TOUGUE:
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_2:
		return 5;
	case SKL_PHILOSOPHERS_3:
	case SKL_OKINA_3:
		return 6;
	case SKL_KANAKO_1:
	case SKL_EIRIN_0:
	case SKL_YUUGI_3_THROW:
	case SKL_PHILOSOPHERS_5:
	case SKL_JUNKO_1:
		return 7;
	case SKL_SATORI_1:
	case SKL_SATORI_2:
	case SKL_YUYUKO_1:
	case SKL_YUYUKO_3:
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_STATUE:
	case SKL_YUKARI_4:	
	case SKL_BREATH:
	case SKL_SEIJA_1:
	case SKL_LILLY_1:
	case SKL_LILLY_3:
	case SKL_OKINA_1:
	case SKL_OKINA_2:
	case SKL_JOON_AND_SION_4:
		return 8;
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
		return 1;
	case SKL_KANAKO_3:
	case SKL_GRAZE:
	case SKL_LEVITATION:
	case SKL_INVISIBLE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_SIZUHA_2:
	case SKL_SIZUHA_3:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_NONE:
	case SKL_YUUGI_1:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:		
	case SKL_SHINKI_1:
	case SKL_SHINKI_2:
	case SKL_SHINKI_3:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_YUYUKO_2:
	case SKL_YUKARI_3:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:	
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
	case SKL_HINA_5:
	case SKL_TORMENT:
	case SKL_ABANDON_GOD:
	case SKL_SEIJA_GIFT:
	case SKL_SEIJA_2:
	case SKL_LILLY_2:
	case SKL_LILLY_4:
	case SKL_PHILOSOPHERS_4:
	case SKL_OKINA_4:
	case SKL_OKINA_5:
	case SKL_JUNKO_2:
	case SKL_JUNKO_3:
	case SKL_JUNKO_4:
	case SKL_JOON_AND_SION_1:
	case SKL_JOON_AND_SION_OFF:
	case SKL_JOON_AND_SION_2:
	case SKL_JOON_AND_SION_3:
	case SKL_MIKO_1:
	case SKL_MIKO_2:
	case SKL_MIKO_3:
	case SKL_MIKO_4:
	case SKL_MIKO_5:
	case SKL_MIKO_6:
	default:
		return 0;
	}
}
string SkillString(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_KANAKO_1);
	case SKL_KANAKO_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_KANAKO_2);
	case SKL_KANAKO_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_KANAKO_3);
	case SKL_GRAZE:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_GRAZE);
	case SKL_GRAZE_OFF:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_GRAZE_OFF);
	case SKL_LEVITATION:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_LEVITATION);
	case SKL_LEVITATION_OFF:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_LEVITATION_OFF);
	case SKL_INVISIBLE:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_INVISIBLE);
	case SKL_INVISIBLE_OFF:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_INVISIBLE_OFF);
	case SKL_EIRIN_0:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_EIRIN_0);
	case SKL_EIRIN_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_EIRIN_1);
	case SKL_EIRIN_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_EIRIN_2);
	case SKL_BYAKUREN_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_BYAKUREN_1);
	case SKL_BYAKUREN_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_BYAKUREN_2);
	case SKL_SIZUHA_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SIZUHA_1);
	case SKL_SIZUHA_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SIZUHA_2);
	case SKL_SIZUHA_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SIZUHA_3);
	case SKL_MINORIKO_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_MINORIKO_1);
	case SKL_MINORIKO_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_MINORIKO_2);
	case SKL_YUUGI_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUUGI_1);
	case SKL_YUUGI_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUUGI_2);
	case SKL_YUUGI_3:
	case SKL_YUUGI_3_THROW:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUUGI_3);
	case SKL_YUUGI_4:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUUGI_4);
	case SKL_YUUGI_5:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUUGI_5);
	case SKL_SATORI_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SATORI_1);
	case SKL_SATORI_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SATORI_2);		
	case SKL_SHINKI_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SHINKI_1);		
	case SKL_SHINKI_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SHINKI_2);		
	case SKL_SHINKI_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SHINKI_3);
	case SKL_YUYUKO_ON:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUYUKO_ON);
	case SKL_YUYUKO_OFF:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUYUKO_OFF);
	case SKL_YUYUKO_1:	
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUYUKO_1);
	case SKL_YUYUKO_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUYUKO_2);
	case SKL_YUYUKO_3:		
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUYUKO_3);
	case SKL_YUKARI_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUKARI_1);
	case SKL_YUKARI_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUKARI_2);
	case SKL_YUKARI_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUKARI_3);
	case SKL_YUKARI_4:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_YUKARI_4);
	case SKL_SWAKO_JUMP:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_JUMP);
	case SKL_SWAKO_TEMPLE:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_TEMPLE);
	case SKL_SWAKO_WATER_GUN:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_WATER_GUN);
	case SKL_SWAKO_TOUGUE:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_TOUGUE);
	case SKL_SWAKO_CURSE:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_CURSE);
	case SKL_SWAKO_DIGGING:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_DIGGING);
	case SKL_SWAKO_SUMMON_FLOG:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_SUMMON_FLOG);
	case SKL_SWAKO_STATUE:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_STATUE);
	case SKL_SWAKO_RAIN:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_RAIN);
	case SKL_SWAKO_SLEEP:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_SLEEP);
	case SKL_SWAKO_MISYAGUZI:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SWAKO_MISYAGUZI);
	case SKL_HINA_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_HINA_1);
	case SKL_HINA_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_HINA_2);
	case SKL_HINA_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_HINA_3);
	case SKL_HINA_4:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_HINA_4);
	case SKL_HINA_5:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_HINA_5);
	case SKL_JUMPING_ATTACK:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JUMPING_ATTACK);
	case SKL_BREATH:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_BREATH);
	case SKL_TORMENT:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_TORMENT);
	case SKL_ABANDON_GOD:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_ABANDON_GOD);
	case SKL_SEIJA_GIFT:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SEIJA_GIFT);
	case SKL_SEIJA_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SEIJA_1);
	case SKL_SEIJA_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_SEIJA_2);
	case SKL_LILLY_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_LILLY_1);
	case SKL_LILLY_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_LILLY_2);
	case SKL_LILLY_3:		
		return LocalzationManager::locString(LOC_SYSTEM_SKL_LILLY_3);
	case SKL_LILLY_4:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_LILLY_4);
	case SKL_PHILOSOPHERS_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_PHILOSOPHERS_1);
	case SKL_PHILOSOPHERS_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_PHILOSOPHERS_2);
	case SKL_PHILOSOPHERS_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_PHILOSOPHERS_3);
	case SKL_PHILOSOPHERS_4:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_PHILOSOPHERS_4);
	case SKL_PHILOSOPHERS_5:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_PHILOSOPHERS_5);
	case SKL_OKINA_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_OKINA_1);
	case SKL_OKINA_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_OKINA_2);
	case SKL_OKINA_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_OKINA_3);
	case SKL_OKINA_4:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_OKINA_4);
	case SKL_OKINA_5:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_OKINA_5);
	case SKL_JUNKO_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JUNKO_1);
	case SKL_JUNKO_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JUNKO_2);
	case SKL_JUNKO_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JUNKO_3);
	case SKL_JUNKO_4:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JUNKO_4);
	case SKL_JOON_AND_SION_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JOON_AND_SION_1);
	case SKL_JOON_AND_SION_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JOON_AND_SION_2);
	case SKL_JOON_AND_SION_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JOON_AND_SION_3);
	case SKL_JOON_AND_SION_4:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JOON_AND_SION_4);
	case SKL_JOON_AND_SION_OFF:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_JOON_AND_SION_OFF);
	case SKL_MIKO_1:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_MIKO_1);
	case SKL_MIKO_2:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_MIKO_2);
	case SKL_MIKO_3:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_MIKO_3);
	case SKL_MIKO_4:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_MIKO_4);
	case SKL_MIKO_5:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_MIKO_5);
	case SKL_MIKO_6:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_MIKO_6);
	case SKL_NONE:
	default:
		return LocalzationManager::locString(LOC_SYSTEM_SKL_UKNOWN);
	}
}
int SkillCap(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
	case SKL_KANAKO_2:
	case SKL_KANAKO_3:
	case SKL_EIRIN_0:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_SIZUHA_2:
	case SKL_SIZUHA_3:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_YUUGI_1:
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_SATORI_1:
	case SKL_SATORI_2:	
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	case SKL_YUYUKO_1:	
	case SKL_YUYUKO_2:	
	case SKL_YUYUKO_3:	
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
	case SKL_HINA_5:
	case SKL_BREATH:
	case SKL_SEIJA_1:
	case SKL_SEIJA_2:
	case SKL_LILLY_1:
	case SKL_LILLY_2:
	case SKL_LILLY_3:
	case SKL_LILLY_4:
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_2:
	case SKL_PHILOSOPHERS_3:
	case SKL_PHILOSOPHERS_4:
	case SKL_PHILOSOPHERS_5:
	case SKL_OKINA_1:
	case SKL_OKINA_2:
	case SKL_OKINA_3:
	case SKL_OKINA_4:
	case SKL_OKINA_5:
	case SKL_JUNKO_1:
	case SKL_JUNKO_2:
	case SKL_JUNKO_3:
	case SKL_JUNKO_4:
	case SKL_JOON_AND_SION_1:
	case SKL_JOON_AND_SION_2:
	case SKL_JOON_AND_SION_3:
	case SKL_JOON_AND_SION_4:
	case SKL_JOON_AND_SION_OFF:
		return 200;
	case SKL_LEVITATION:
		return 75;
	case SKL_INVISIBLE:
		return 100;
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_OFF:
	case SKL_YUYUKO_ON:
	case SKL_NONE:
	case SKL_JUMPING_ATTACK:
	case SKL_TORMENT:
	case SKL_ABANDON_GOD:
	case SKL_SEIJA_GIFT:
	case SKL_MIKO_1:
	case SKL_MIKO_2:
	case SKL_MIKO_3:
	case SKL_MIKO_4:
	case SKL_MIKO_5:
	case SKL_MIKO_6:
	default:
		return 0;
	}
}
int SkillNoise(skill_list skill)
{
	switch(skill)
	{
	case SKL_GRAZE:
	case SKL_LEVITATION:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_NONE:
	case SKL_INVISIBLE:
	case SKL_SIZUHA_1:
	case SKL_SIZUHA_2:
	case SKL_SIZUHA_3:
	case SKL_YUUGI_1:
	case SKL_SATORI_2:
	case SKL_YUKARI_3:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_SLEEP:
	case SKL_HINA_5:
	case SKL_ABANDON_GOD:
	case SKL_SEIJA_GIFT:
	case SKL_LILLY_1:
	case SKL_LILLY_2:
	case SKL_OKINA_1:
	case SKL_OKINA_3:
	case SKL_OKINA_4:
	case SKL_OKINA_5:
	case SKL_JOON_AND_SION_1:
	case SKL_JOON_AND_SION_OFF:
	case SKL_MIKO_2:
	case SKL_MIKO_3:
	case SKL_MIKO_4:
	case SKL_MIKO_5:
		return 0;
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_SATORI_1:
	case SKL_YUYUKO_1:
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:	
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
	case SKL_JUMPING_ATTACK:
	case SKL_BREATH:
	case SKL_SEIJA_1:
	case SKL_LILLY_3:
	case SKL_PHILOSOPHERS_3:
	case SKL_OKINA_2:
	case SKL_JUNKO_1:
	case SKL_JUNKO_2:
	case SKL_JUNKO_3:
	case SKL_JUNKO_4:
		return 4;
	case SKL_KANAKO_1:
	case SKL_KANAKO_2:
	case SKL_KANAKO_3:
	case SKL_EIRIN_0:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:	
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	case SKL_YUYUKO_2:	
	case SKL_YUYUKO_3:
	case SKL_YUKARI_4:	
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_MISYAGUZI:
	case SKL_LILLY_4:
	case SKL_PHILOSOPHERS_2:
	case SKL_PHILOSOPHERS_4:
	case SKL_JOON_AND_SION_4:
	case SKL_MIKO_1:
	case SKL_MIKO_6:
		return 8;
	case SKL_YUUGI_4:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_RAIN:
	case SKL_TORMENT:
	case SKL_SEIJA_2:
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_5:
	case SKL_JOON_AND_SION_2:
	case SKL_JOON_AND_SION_3:
		return 12;
	case SKL_YUUGI_5:
		return 16;
	case SKL_YUYUKO_ON:	
	case SKL_YUYUKO_OFF:
	default:
		return 0;
	}

}
int SkillSpeed(skill_list skill)
{
	switch (skill)
	{
	case SKL_PHILOSOPHERS_3:
		return 5;
	default:
		return 10;
	}
}
int SkillPow(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
	case SKL_KANAKO_2:
	case SKL_KANAKO_3:
	case SKL_EIRIN_0:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_SIZUHA_3:
	case SKL_YUUGI_1:
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_SATORI_2:
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	case SKL_YUYUKO_1:
	case SKL_YUYUKO_2:
	case SKL_YUYUKO_3:
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
	case SKL_HINA_5:
	case SKL_OKINA_1:
	case SKL_OKINA_2:
	case SKL_OKINA_3:
	case SKL_OKINA_4:
	case SKL_OKINA_5:
	case SKL_JOON_AND_SION_1:
	case SKL_JOON_AND_SION_OFF:
	case SKL_MIKO_1:
	case SKL_MIKO_2:
	case SKL_MIKO_3:
	case SKL_MIKO_4:
	case SKL_MIKO_5:
	case SKL_MIKO_6:
		//신앙심으로 바꾸기
		return you.piety;
	case SKL_SIZUHA_1:
	case SKL_SATORI_1:
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:
	case SKL_JUMPING_ATTACK:
	case SKL_BREATH:
	case SKL_TORMENT:
	case SKL_ABANDON_GOD:
	case SKL_SEIJA_GIFT:
	case SKL_SEIJA_1:
	case SKL_SEIJA_2:
	case SKL_LILLY_1:
	case SKL_LILLY_2:
	case SKL_LILLY_3:
	case SKL_LILLY_4:
	case SKL_JUNKO_1:
	case SKL_JUNKO_2:
	case SKL_JUNKO_3:
	case SKL_JUNKO_4:
	case SKL_JOON_AND_SION_2:
	case SKL_JOON_AND_SION_3:
	case SKL_JOON_AND_SION_4:
		return you.level*5;
		//return you.skill[SKT_SPELLCASTING].level*5;
	case SKL_SIZUHA_2:
		return you.piety;
	case SKL_LEVITATION:
	case SKL_INVISIBLE:
		return you.GetSkillLevel(SKT_EVOCATE, true) *5;
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_NONE:
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_2:
	case SKL_PHILOSOPHERS_3:
	case SKL_PHILOSOPHERS_4:
	case SKL_PHILOSOPHERS_5:
	default:
		return 0;
	}
}
int SkillDiffer(skill_list skill)
{
	switch(skill)
	{
	case SKL_LEVITATION:
		return SkillDiffer_simple(-4,SKT_EVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_INVISIBLE:
		return SkillDiffer_simple(0,SKT_EVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_BYAKUREN_1:
		return 100;
		//return SkillDiffer_simple(-3,SKT_SPELLCASTING,SKT_ERROR,SKT_ERROR);
	case SKL_BYAKUREN_2:		
		return 100;
		
	case SKL_SIZUHA_1: //디버프
	case SKL_SATORI_1:

		//return SkillDiffer_simple(1,SKT_SPELLCASTING,SKT_ERROR,SKT_ERROR);
	case SKL_KANAKO_1:
		//return SkillDiffer_simple(-4,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_KANAKO_2:
		//return SkillDiffer_simple(-2,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_KANAKO_3:
		//return SkillDiffer_simple(1,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_EIRIN_0:
		//return SkillDiffer_simple(-6,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_EIRIN_1:
		//return SkillDiffer_simple(-2,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_EIRIN_2:
		//return SkillDiffer_simple(2,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_SIZUHA_2:
	case SKL_SIZUHA_3:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_YUUGI_1:
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_SATORI_2:
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	case SKL_YUYUKO_1:
	case SKL_YUYUKO_2:
	case SKL_YUYUKO_3:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
	case SKL_HINA_5:
	case SKL_JUMPING_ATTACK:
	case SKL_BREATH:
	case SKL_TORMENT:
	case SKL_ABANDON_GOD:
	case SKL_SEIJA_GIFT:
	case SKL_SEIJA_1:
	case SKL_SEIJA_2:
	case SKL_LILLY_1:
	case SKL_LILLY_2:
	case SKL_LILLY_3:
	case SKL_LILLY_4:
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_2:
	case SKL_PHILOSOPHERS_3:
	case SKL_PHILOSOPHERS_4:
	case SKL_PHILOSOPHERS_5:
	case SKL_OKINA_1:
	case SKL_OKINA_2:
	case SKL_OKINA_3:
	case SKL_OKINA_4:
	case SKL_OKINA_5:
	case SKL_JUNKO_1:
	case SKL_JUNKO_2:
	case SKL_JUNKO_3:
	case SKL_JUNKO_4:
	case SKL_JOON_AND_SION_1:
	case SKL_JOON_AND_SION_2:
	case SKL_JOON_AND_SION_3:
	case SKL_JOON_AND_SION_4:
	case SKL_JOON_AND_SION_OFF:
	case SKL_MIKO_1:
	case SKL_MIKO_2:
	case SKL_MIKO_3:
	case SKL_MIKO_4:
	case SKL_MIKO_5:
	case SKL_MIKO_6:
		return 100;
	case SKL_NONE:
	default:
		return 0;
	}
}
int SkillDiffer_simple(int differ, skill_type s1, skill_type s2, skill_type s3)
{
	int num = 0;
	float success_ = 0;
	if(s1 != -1)
	{
		success_ += you.GetSkillLevel(s1, true);
		num++;
	}	
	if(s2 != -1)
	{
		success_ += you.GetSkillLevel(s2, true);
		num++;
	}
	if(s3 != -1)
	{
		success_ += you.GetSkillLevel(s3, true);
		num++;
	}
	if(num)
		success_/=num;
	
	success_ = max(0,(success_-differ<=14)?(success_-differ)*(2*14+(success_-differ-1)*-1.07)/2:99);
	return success_;
}




int SkillMana(skill_list skill)
{
	switch(skill)
	{
	case SKL_BYAKUREN_1:
	case SKL_EIRIN_0:
	case SKL_GRAZE:
	case SKL_YUUGI_1:
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_STATUE:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
	case SKL_HINA_5:
	case SKL_SIZUHA_3:
	case SKL_SATORI_1:
	case SKL_SATORI_2:
	case SKL_JUMPING_ATTACK:
	case SKL_BREATH:
	case SKL_ABANDON_GOD:
	case SKL_SEIJA_GIFT:
	case SKL_SEIJA_1:
	case SKL_SEIJA_2:
	case SKL_LILLY_1:
	case SKL_OKINA_4:
	case SKL_JUNKO_4:
	case SKL_JOON_AND_SION_1:
	case SKL_JOON_AND_SION_4:
	case SKL_JOON_AND_SION_OFF:
	case SKL_MINORIKO_2:
	case SKL_MIKO_1:
	case SKL_MIKO_2:
	case SKL_MIKO_3:
	case SKL_MIKO_4:
	case SKL_MIKO_5:
	case SKL_MIKO_6:
		return 0;		
	case SKL_SWAKO_WATER_GUN:
	case SKL_JUNKO_1:
		return 1;
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_2:
	case SKL_PHILOSOPHERS_3:
	case SKL_PHILOSOPHERS_4:
	case SKL_PHILOSOPHERS_5:
		return 1;
	case SKL_KANAKO_1:
	case SKL_LEVITATION:
	case SKL_YUYUKO_1:
	case SKL_YUKARI_1:
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_TOUGUE:
	case SKL_INVISIBLE:
	case SKL_LILLY_2:
	case SKL_OKINA_1:
	case SKL_OKINA_2:
		return 2;
	case SKL_KANAKO_2:
	case SKL_MINORIKO_1:
	case SKL_YUYUKO_2:
	case SKL_YUKARI_3:
	case SKL_LILLY_3:
	case SKL_OKINA_3:
	case SKL_JUNKO_2:
		return 3;
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_YUKARI_2:
		return 4;
	case SKL_EIRIN_2:
	case SKL_YUYUKO_3:
	case SKL_LILLY_4:
	case SKL_JUNKO_3:
	case SKL_JOON_AND_SION_2:
	case SKL_JOON_AND_SION_3:
		return 5;
	case SKL_KANAKO_3:
		return 4;
	case SKL_YUKARI_4:
	case SKL_TORMENT:
	case SKL_OKINA_5:
		return 6;
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_NONE:
	case SKL_EIRIN_1:
	case SKL_SIZUHA_2:
	case SKL_SHINKI_1:	
	case SKL_SHINKI_2:	
	case SKL_SHINKI_3:
	default:
		return 0;
	}
}
bool SkillPlusCost(skill_list skill,bool check_)
{ //return false는 코스트를 실패한것이다.
	//check_는 소모 안하고 체크만
	switch(skill)
	{
	case SKL_EIRIN_0:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		return true;	
	case SKL_SATORI_1:
		if(!check_)
			you.PietyUpDown(-1);
	case SKL_SIZUHA_1:
		if(!check_)
			you.PietyUpDown(-2);
		return true;	
	case SKL_BYAKUREN_1:
		if(!check_)
			you.PietyUpDown(-3);	
	case SKL_MINORIKO_1:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		if(!check_)
			you.PietyUpDown(-2);
		return true;
	case SKL_KANAKO_1:
		if(!check_)
			you.PietyUpDown(-2);
		return true;
	case SKL_KANAKO_2:
	case SKL_BYAKUREN_2:
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_KANAKO_3:
		if(!check_)
			you.PietyUpDown(-4);
		return true;	
	case SKL_YUYUKO_1:	
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(10+randA(5)),true);
		return true;	
	case SKL_YUYUKO_2:	
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_YUYUKO_3:	
		if(!check_)
			you.PietyUpDown(-4);
		return true;		
	case SKL_YUKARI_1:
		if(!check_)
			you.PietyUpDown(-2);
		return true;
	case SKL_YUKARI_2:
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_YUKARI_3:
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_YUKARI_4:
		if(!check_)
			you.PietyUpDown(-6);
		return true;		
	case SKL_SWAKO_JUMP:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(10+randA(5)),true);
		return true;
	case SKL_SWAKO_TEMPLE:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-100,true);
		return true;
	case SKL_SWAKO_WATER_GUN:
		return true;
	case SKL_SWAKO_TOUGUE:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		return true;
	case SKL_SWAKO_CURSE:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(30+randA(20)),true);
			you.PietyUpDown(-3);
		}
		return true;
	case SKL_SWAKO_DIGGING:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(30+randA(20)),true);
			you.PietyUpDown(-3);
		}
		return true;
	case SKL_SWAKO_SUMMON_FLOG:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(30+randA(20)),true);
			you.PietyUpDown(-4);
		}
		return true;
	case SKL_SWAKO_STATUE:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(40+randA(20)),true);
			you.PietyUpDown(-3);
		}
		return true;
	case SKL_SWAKO_RAIN:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-6);
		}
		return true;
	case SKL_SWAKO_SLEEP:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-8);
		}
		return true;
	case SKL_SWAKO_MISYAGUZI:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-6);
		}
		return true;
	case SKL_SHINKI_1:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		if(!check_)
			you.PietyUpDown(-1);
		return true;
	case SKL_SHINKI_2:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(30+randA(20)),true);
		if(!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_SHINKI_3:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-5);
		}
		return true;
	case SKL_SIZUHA_2:
		if(check_ && !you.equipment[ET_ARMOR])
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_AUTUMN_ARMOUR_SHOULD),true,false,false,CL_small_danger);	
			return false;
		}
		if(!check_)
			you.PietyUpDown(-5);
		return true;
	case SKL_SIZUHA_3:
		if(check_ && !you.equipment[ET_WEAPON])
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BREAND_SHOULD_WEAPON),true,false,false,CL_small_danger);	
			return false;
		}
		return true;
	case SKL_SATORI_2:
		if(!check_)
			you.PietyUpDown(-5);
		return true;
	case SKL_EIRIN_1:
		if(!check_)
			you.PietyUpDown(-5);
		return true;
	case SKL_EIRIN_2:
		if(check_ && you.GetHp() ==  you.GetMaxHp())
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_HEAL_MAX),true,false,false,CL_normal);	
			return false;
		}
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-10);
		}
		return true;		
	case SKL_YUUGI_1:
		if(!check_)
			you.PietyUpDown(-1);
		return true;
	case SKL_MINORIKO_2:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-6);
		}
		return true;	
	case SKL_YUUGI_2:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(10+randA(5)),true);
			//you.PietyUpDown(-3);
		}
		return true;	
	case SKL_YUUGI_3:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(12+randA(8)),true);
			//you.PietyUpDown(-4);
		}
		return true;	
	case SKL_YUUGI_4:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-(20+randA(10)),true);
			you.PietyUpDown(-5);
		}
		return true;	
	case SKL_YUUGI_5:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
			you.PietyUpDown(-10);
		}
		return true;			
	case SKL_HINA_1:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(10+randA(5)),true);
		return true;
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		return true;
	case SKL_HINA_5:
		if(check_ && !you.equipment[ET_WEAPON])
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_BREAND_SHOULD_WEAPON),true,false,false,CL_small_danger);	
			return false;
		}
		return true;	
	case SKL_LEVITATION:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(3+randA(5)),true);
		return true;		
	case SKL_INVISIBLE:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		return true;
	case SKL_JUMPING_ATTACK:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(15)),true);
		return true;
	case SKL_BREATH:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(10+randA(10)),true);
		return true;
	case SKL_TORMENT:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
		}
		return true;
	case SKL_SEIJA_1:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(15)),true);
		return true;
	case SKL_SEIJA_2:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
		}
		return true;
	case SKL_LILLY_1:
	case SKL_LILLY_2:
		return true;
	case SKL_LILLY_3:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(15)),true);
		return true;
	case SKL_LILLY_4:
		if(check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE),true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
		{
			you.PowUpDown(-100,true);
		}
		return true;
	case SKL_OKINA_1:
		if (check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE), true, false, false, CL_normal);
			return false;
		}
		if (!check_)
		{
			you.PowUpDown(-(25 + randA(10)), true);
		}
		return true;
	case SKL_OKINA_2:
		if (!check_)
			you.PietyUpDown(-2);
		return true;
	case SKL_OKINA_3:
		if (!check_)
			you.PietyUpDown(-3);
		return true;
	case SKL_OKINA_4:
		if (!check_)
			you.PietyUpDown(-4);
		return true;
	case SKL_OKINA_5:
		if (!check_)
			you.PietyUpDown(-15);
		return true;
	case SKL_JUNKO_1:
		if (check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE), true, false, false, CL_normal);
			return false;
		}
		if (!check_)
			you.PowUpDown(-(10 + randA(5)), true);
		return true;
	case SKL_JUNKO_2:
		if (check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE), true, false, false, CL_normal);
			return false;
		}
		if (!check_)
			you.PowUpDown(-(40 + randA(20)), true);
		return true;
	case SKL_JUNKO_3:
		if (check_ && you.power<100)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SHOULD_P_OVER_ONE), true, false, false, CL_normal);
			return false;
		}
		if (!check_)
			you.PowUpDown(-(70 + randA(30)), true);
		return true;
	case SKL_JOON_AND_SION_4:
	{
		if (!check_)
			you.PietyUpDown(-(you.piety - 120));
	}
	case SKL_MIKO_1:
	{
		//TODO 층마다 한번만 사용가능하도록?
		return true;
	}
	case SKL_MIKO_2:
	{
		if (check_ && you.piety < getMikoPiety(0))
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULAR_LACK), true, false, false, CL_normal);
			return false;
		}
		if (!check_)
			you.PietyUpDown(-getMikoPiety(0));
		return true;
	}
	case SKL_MIKO_3:
	{
		if (check_ && you.piety < getMikoPiety(1))
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULAR_LACK), true, false, false, CL_normal);
			return false;
		}
		if (!check_)
			you.PietyUpDown(-getMikoPiety(1));
		return true;
	}
	case SKL_MIKO_4:
	{
		if (check_ && you.piety < getMikoPiety(2))
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULAR_LACK), true, false, false, CL_normal);
			return false;
		}
		if (!check_)
			you.PietyUpDown(-getMikoPiety(2));
		return true;
	}
	case SKL_MIKO_5:
	{
		if (check_ && you.piety < getMikoPiety(3))
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULAR_LACK), true, false, false, CL_normal);
			return false;
		}
		if (!check_)
			you.PietyUpDown(-getMikoPiety(3));
		return true;
	}
	case SKL_MIKO_6:
	{
		if (check_ && you.piety < getMikoPiety(4))
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULAR_LACK), true, false, false, CL_normal);
			return false;
		}
		if (!check_)
			you.PietyUpDown(-getMikoPiety(4));
		return true;
	}
	case SKL_JOON_AND_SION_1:
	case SKL_JOON_AND_SION_2:
	case SKL_JOON_AND_SION_3:
	case SKL_JOON_AND_SION_OFF:
	case SKL_JUNKO_4:
	case SKL_NONE:
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_ABANDON_GOD:
	case SKL_SEIJA_GIFT:
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_2:
	case SKL_PHILOSOPHERS_3:
	case SKL_PHILOSOPHERS_4:
	case SKL_PHILOSOPHERS_5:
	default:
		return true;
	}
}
void SkillUseTraning(skill_list skill)
{
	//switch(skill)
	//{
	//case SKL_KANAKO_1:
	//case SKL_KANAKO_2:
	//case SKL_KANAKO_3:
	//case SKL_EIRIN_1:
	//case SKL_EIRIN_2:
	//	you.SkillTraining(SKT_INVOCATE,1);
	//	return;		
	//case SKL_BYAKUREN_1:
	//case SKL_BYAKUREN_2:
	//	you.SkillTraining(SKT_ENCHARM,1);
	//	return;		
	//case SKL_GRAZE:
	//case SKL_LEVITATION:
	//case SKL_INVISIBLE:
	//	you.SkillTraining(SKT_EVOCATE,1);
	//	return;		
	//case SKL_NONE:
	//case SKL_GRAZE_OFF:
	//case SKL_LEVITATION_OFF:
	//case SKL_INVISIBLE_OFF:
	//default:
	//	return;
	//}
}
string SkillCostString(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_MINORIKO_1:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_MP_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_BYAKUREN_1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
	case SKL_YUUGI_1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_POTION_AND_PIETY);
	case SKL_YUUGI_2:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_LITTLE_AND_PIETY);
	case SKL_YUUGI_3:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_LITTLE_AND_PIETY);
	case SKL_YUUGI_4:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_PIETY);
	case SKL_YUUGI_5:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_PIETY);
	case SKL_KANAKO_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_BYAKUREN_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_KANAKO_3:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_EIRIN_0:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_POTION);
	case SKL_EIRIN_1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
	case SKL_EIRIN_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_MP_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_MINORIKO_2:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_FOOD_AND_PIETY);
	case SKL_SIZUHA_1:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_SIZUHA_2:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
	case SKL_SIZUHA_3:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON);
	case SKL_LEVITATION:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_LITTLE_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_INVISIBLE:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_SATORI_1:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_SATORI_2:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_TIME_AND_PIETY);
	case SKL_SHINKI_1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_LITTLE_AND_PIETY);
	case SKL_SHINKI_2:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_PIETY);
	case SKL_SHINKI_3:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_PIETY);
	case SKL_YUYUKO_1:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_LITTLE_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_YUYUKO_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_YUYUKO_3:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_YUKARI_1:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_YUKARI_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_YUKARI_3:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_YUKARI_4:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_SWAKO_JUMP:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_LITTLE_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_SWAKO_TEMPLE:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_BIG);
	case SKL_SWAKO_WATER_GUN:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_SWAKO_TOUGUE:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_LITTLE_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_SWAKO_CURSE:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_PIETY);
	case SKL_SWAKO_DIGGING:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_PIETY);
	case SKL_SWAKO_SUMMON_FLOG:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_PIETY);
	case SKL_SWAKO_STATUE:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_PIETY);
	case SKL_SWAKO_RAIN:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_PIETY);
	case SKL_SWAKO_SLEEP:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_PIETY);
	case SKL_SWAKO_MISYAGUZI:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_PIETY);
	case SKL_HINA_1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_LITTLE);
	case SKL_HINA_2:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_CURSE);
	case SKL_HINA_3:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_CURSE);
	case SKL_HINA_4:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_CURSE);
	case SKL_HINA_5:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON);
	case SKL_JUMPING_ATTACK:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_SOME);
	case SKL_BREATH:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_LITTLE);
	case SKL_TORMENT:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_SEIJA_1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_SOME);
	case SKL_SEIJA_2:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_P_BIG);
	case SKL_LILLY_1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_NONE);
	case SKL_LILLY_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_LILLY_3:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_LILLY_4:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_2:
	case SKL_PHILOSOPHERS_3:
	case SKL_PHILOSOPHERS_4:
	case SKL_PHILOSOPHERS_5:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_OKINA_1:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_OKINA_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_OKINA_3:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_OKINA_4:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
	case SKL_OKINA_5:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_MP_AND_PIETY_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_JUNKO_1:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_LITTLE_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_JUNKO_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_SOME_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_JUNKO_3:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_P_BIG_AND_MP_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_JOON_AND_SION_1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_NONE);
	case SKL_JOON_AND_SION_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON_POSSESSION_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_JOON_AND_SION_3:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON_POSSESSION_N, PlaceHolderHelper(to_string(SkillMana(skill))));
	case SKL_JOON_AND_SION_4:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_PIETY);
	case SKL_JOON_AND_SION_OFF:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_NONE);
	case SKL_MIKO_1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_ONCE_UPON_FLOOR);
	case SKL_MIKO_2:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(to_string(getMikoPiety(0)/2)));
	case SKL_MIKO_3:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(to_string(getMikoPiety(1)/2)));
	case SKL_MIKO_4:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(to_string(getMikoPiety(2)/2)));
	case SKL_MIKO_5:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(to_string(getMikoPiety(3)/2)));
	case SKL_MIKO_6:
		return LocalzationManager::formatString(LOC_SYSTEM_GOD_SHOW_POPULAR, PlaceHolderHelper(to_string(getMikoPiety(4)/2)));
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_NONE:
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_ABANDON_GOD:
	case SKL_SEIJA_GIFT:
	default:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_SHOW_NONE);
	}
}
int GetSpellBombRange(skill_list skill)
{	
	switch(skill)
	{		
	case SKL_YUUGI_3_THROW:
	case SKL_EIRIN_0:
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_5:
		return 1;
	default:
		break;
	}
	return 0;
}
int GetSpellBombRange(spell_list spell)
{
	switch(spell)
	{
	case SPL_FIRE_BALL:
	case SPL_CONFUSE_CLOUD:
	case SPL_STONE_TRAP:
	case SPL_STONE_UPLIFT:
	case SPL_THUNDER:
		return 1;
	default:
		break;
	}
	return 0;
}



void SkillUse(char auto_)
{	
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY),true,false,false,CL_danger);
		return;
	}
	if(you.currentSkillNum)
	{
		changedisplay(DT_SKILL_USE);
		while(1)
		{
			int key_ = auto_;
			InputedKey inputedKey;
			if (key_ == 0)
				key_ = waitkeyinput(inputedKey,true);
			if( (key_ >= 'a' && key_ <= 'z') ||  (key_ >= 'A' && key_ <= 'Z'))
			{
				int num = (key_ >= 'A' && key_ <= 'Z')?(key_-'A'+26):(key_-'a');
				if(skill_list skill_ = (skill_list)you.MemorizeSkill[num])
				{
					if(!GetDisplayMove()) //스킬사용
					{
						if(you.pure_mp && SkillMana(skill_)>=you.GetMp())
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_MP_WARN), true, false, false, CL_normal);
							break;
						}
						else if(SkillMana(skill_)>you.GetMp())
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_TOO_LOW_MP),true,false,false,CL_normal);	
							break;
						}
						if(!SkillFlagCheck(skill_, S_FLAG_IMMEDIATELY))
						{
							SetSpellSight(SkillLength(skill_),SkillFlagCheck(skill_, S_FLAG_RECT)?2:1);
							changedisplay(DT_GAME);
							beam_iterator beam(you.position,you.position);
							projectile_infor infor(SkillLength(skill_),false,SkillFlagCheck(skill_, S_FLAG_SMITE),skill_,true);
							auto it = you.item_list.end();
							if(int short_ = Common_Throw(it, you.GetTargetIter(), beam, &infor,-1,0.0f, auto_>0))
							{
								unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
								if(unit_)
									you.youAttack(unit_);
								if(UseSkill(skill_, short_==2, you.search_pos))
								{
									SkillPlusCost(skill_,false);
									if(SkillMana(skill_))
										you.MpUpDown(-SkillMana(skill_));
												
									you.doingActionDump(SkillFlagCheck(skill_, S_FLAG_GOD)?DACT_INVOKE:DACT_EVOKE, SkillString(skill_));
									SkillUseTraning(skill_);
									Noise(you.position , SkillNoise(skill_));
									you.SetBattleCount(30);
									you.time_delay += you.GetNormalDelay()*SkillSpeed(skill_) / 10;
									you.TurnEnd();
									you.SetPrevAction('a', key_);
								}
							}
							SetSpellSight(0,0);
							break;
						}			
						if(SkillFlagCheck(skill_, S_FLAG_IMMEDIATELY))
						{
							changedisplay(DT_GAME);
							if(int succece_ =  UseSkill(skill_, false, you.position))
							{
								if(succece_ != 2)
								{ //2는 사용에 실패한것이다. 마법이 아니면 사용에 실패하면 턴만 소모
									SkillPlusCost(skill_,false);
									if(SkillMana(skill_))
										you.MpUpDown(-SkillMana(skill_));
								}

								you.doingActionDump(SkillFlagCheck(skill_, S_FLAG_GOD)?DACT_INVOKE:DACT_EVOKE, SkillString(skill_));
								SkillUseTraning(skill_);
								Noise(you.position , SkillNoise(skill_));
								you.SetBattleCount(30);
								you.time_delay += you.GetNormalDelay()*SkillSpeed(skill_) / 10;
								you.TurnEnd();
								you.SetPrevAction('a', key_);
							}		
							break;
						}
					}
					else //설명보기
					{
						WaitForSingleObject(mutx, INFINITE);
						SetText() = GetSkillInfor(skill_);
						changedisplay(DT_TEXT);
						ReleaseMutex(mutx);
						waitkeyinput();
						changedisplay(DT_SKILL_USE);
						changemove(0);
					}
				}
			}
			else if(key_ == '!' || key_ == '?')
			{
				changemove(0);
			}
			else if(key_ == -1) {
				if(inputedKey.mouse == MKIND_RCLICK) {
					break;
				}
			}
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
	}
	else
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_DONT_HAVE),true,false,false,CL_normal);	
}