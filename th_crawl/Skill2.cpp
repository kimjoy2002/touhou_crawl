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
extern HANDLE mutx;


bool SkillFlagCheck(skill_list skill, skill_flag flag)
{
	switch(skill)
	{
	case SKL_KANAKO_2:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_SUMMON) & flag);
	case SKL_KANAKO_1:
	case SKL_YUYUKO_3:
		return ((S_FLAG_SPEAK) & flag);
	case SKL_SWAKO_DIGGING:
		return ((S_FLAG_SPEAK | S_FLAG_UNSIGHT) & flag);
	case SKL_SWAKO_WATER_GUN:
	case SKL_SWAKO_TOUGUE:
		return 0;
	case SKL_EIRIN_0:
		return ((S_FLAG_SPEAK | S_FLAG_CLOUD) & flag);
	case SKL_YUUGI_2:
	case SKL_YUUGI_3:
	case SKL_SATORI_2:
	case SKL_YUYUKO_1:
	case SKL_SWAKO_CURSE:
	case SKL_SWAKO_STATUE:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE) & flag);
	case SKL_SWAKO_JUMP:
		return ((S_FLAG_SMITE | S_FLAG_RECT | S_FLAG_NO_TARGET) & flag);		
	case SKL_YUKARI_2:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_SUKIMA) & flag);
	case SKL_YUKARI_1:
		return ((S_FLAG_SPEAK | S_FLAG_SMITE | S_FLAG_SUMMON | S_FLAG_SUKIMA) & flag);
	case SKL_SATORI_1:
		return ((S_FLAG_SPEAK | S_FLAG_DEBUF | S_FLAG_SMITE) & flag);
	case SKL_KANAKO_3:
	case SKL_EIRIN_1:
	case SKL_EIRIN_2:
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_SIZUHA_2:
	case SKL_MINORIKO_1:
	case SKL_MINORIKO_2:
	case SKL_YUUGI_1:
	case SKL_YUUGI_4:
	case SKL_YUUGI_5:
	case SKL_YUYUKO_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:
	case SKL_SWAKO_SLEEP:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		return ((S_FLAG_SPEAK | S_FLAG_IMMEDIATELY) & flag);	
	case SKL_SWAKO_TEMPLE:
		return ((S_FLAG_IMMEDIATELY) & flag);		
	case SKL_SHINKI_1:
	case SKL_SHINKI_2:
	case SKL_SHINKI_3:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_MISYAGUZI:
		return ((S_FLAG_SPEAK | S_FLAG_IMMEDIATELY | S_FLAG_SUMMON) & flag);
	case SKL_GRAZE:
	case SKL_LEVITATION:
	case SKL_INVISIBLE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
		return ((S_FLAG_IMMEDIATELY) & flag);
	case SKL_NONE:
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
	case SKL_SWAKO_TOUGUE:
		return 5;
	case SKL_KANAKO_1:
	case SKL_EIRIN_0:
	case SKL_YUUGI_3_THROW:
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
	case SKL_YUKARI_4:	
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_SUMMON_FLOG:
	case SKL_SWAKO_RAIN:
	case SKL_SWAKO_SLEEP:
	case SKL_SWAKO_MISYAGUZI:	
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
	default:
		return 0;
	}
}
const char* SkillString(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
		return "건신초래돌";
	case SKL_KANAKO_2:
		return "건신초래어주";
	case SKL_KANAKO_3:
		return "건신초래풍";
	case SKL_GRAZE:
		return "그레이즈 발동";
	case SKL_GRAZE_OFF:
		return "그레이즈 해제";
	case SKL_LEVITATION:
		return "부유 발동";
	case SKL_LEVITATION_OFF:
		return "부유 해제";
	case SKL_INVISIBLE:
		return "투명 발동";
	case SKL_INVISIBLE_OFF:
		return "투명 해제";
	case SKL_EIRIN_0:
		return "물약 던지기";
	case SKL_EIRIN_1:
		return "인체실험";
	case SKL_EIRIN_2:
		return "신체재생";
	case SKL_BYAKUREN_1:
		return "지력강화";
	case SKL_BYAKUREN_2:
		return "각력강화";
	case SKL_SIZUHA_1:
		return "광기의 낙엽";
	case SKL_SIZUHA_2:
		return "단풍 방어구";
	case SKL_MINORIKO_1:
		return "능력치 회복";
	case SKL_MINORIKO_2:
		return "체력 회복";
	case SKL_YUUGI_1:
		return "술 마시기";
	case SKL_YUUGI_2:
		return "저먼 스플렉스";
	case SKL_YUUGI_3:
	case SKL_YUUGI_3_THROW:
		return "집어던지기";
	case SKL_YUUGI_4:
		return "괴멸의 포효";
	case SKL_YUUGI_5:
		return "삼보필살";
	case SKL_SATORI_1:
		return "트라우마";
	case SKL_SATORI_2:
		return "독심술";		
	case SKL_SHINKI_1:
		return "하급 마족 소환";		
	case SKL_SHINKI_2:
		return "중급 마족 소환";		
	case SKL_SHINKI_3:
		return "상급 마족 소환";
	case SKL_YUYUKO_ON:
		return "유령 소환 발동";
	case SKL_YUYUKO_OFF:
		return "유령 소환 해제";
	case SKL_YUYUKO_1:	
		return "유령 조종";	
	case SKL_YUYUKO_2:
		return "유령 소환 가속";	
	case SKL_YUYUKO_3:		
		return "유령 구속";	
	case SKL_YUKARI_1:
		return "변용을 보는 눈";
	case SKL_YUKARI_2:
		return "환상광상혈";
	case SKL_YUKARI_3:
		return "사중결계";
	case SKL_YUKARI_4:
		return "차원고정";	
	case SKL_SWAKO_JUMP:
		return "개구리 점프";	
	case SKL_SWAKO_TEMPLE:
		return "신전 세우기";	
	case SKL_SWAKO_WATER_GUN:
		return "물총";	
	case SKL_SWAKO_TOUGUE:
		return "개구리 혀";	
	case SKL_SWAKO_CURSE:
		return "토착신의 재앙";	
	case SKL_SWAKO_DIGGING:
		return "굴착";	
	case SKL_SWAKO_SUMMON_FLOG:
		return "개구리 소환";	
	case SKL_SWAKO_STATUE:
		return "석상 세우기";	
	case SKL_SWAKO_RAIN:
		return "비 내리기";
	case SKL_SWAKO_SLEEP:
		return "동면";
	case SKL_SWAKO_MISYAGUZI:
		return "미샤구지님 소환";
	case SKL_HINA_1:
		return "액땜";
	case SKL_HINA_2:
		return "무기 저주(강화)";
	case SKL_HINA_3:
		return "방어구 저주(반사)";
	case SKL_HINA_4:
		return "장신구 저주(회복)";
	case SKL_NONE:
	default:
		return "알수없는 능력";
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
	case SKL_YUUGI_1:
	case SKL_SATORI_2:
	case SKL_YUKARI_3:
	case SKL_SWAKO_TEMPLE:
	case SKL_SWAKO_SLEEP:
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
		return 8;
	case SKL_YUUGI_4:
	case SKL_SWAKO_DIGGING:
	case SKL_SWAKO_RAIN:
		return 12;
	case SKL_YUUGI_5:
		return 16;
	case SKL_YUYUKO_ON:	
	case SKL_YUYUKO_OFF:	
	default:
		return 0;
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
		return you.skill[SKT_INVOCATE].level*5;
	case SKL_BYAKUREN_1:
	case SKL_BYAKUREN_2:
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
	case SKL_YUKARI_1:
	case SKL_YUKARI_2:
	case SKL_YUKARI_3:
	case SKL_YUKARI_4:
	case SKL_HINA_1:
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
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
		return you.level*5;
		//return you.skill[SKT_SPELLCASTING].level*5;
	case SKL_SIZUHA_2:
		return you.piety;
	case SKL_LEVITATION:
	case SKL_INVISIBLE:
		return you.skill[SKT_EVOCATE].level*5;
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_NONE:
	default:
		return 0;
	}
}
int SkillDiffer(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
		return SkillDiffer_simple(-4,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_KANAKO_2:
		return SkillDiffer_simple(-2,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_KANAKO_3:
		return SkillDiffer_simple(1,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_EIRIN_0:
		return SkillDiffer_simple(-6,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_EIRIN_1:
		return SkillDiffer_simple(-2,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_EIRIN_2:
		return SkillDiffer_simple(2,SKT_INVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_LEVITATION:
		return SkillDiffer_simple(-4,SKT_EVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_INVISIBLE:
		return SkillDiffer_simple(0,SKT_EVOCATE,SKT_ERROR,SKT_ERROR);
	case SKL_BYAKUREN_1:
		return 100;
		//return SkillDiffer_simple(-3,SKT_SPELLCASTING,SKT_ERROR,SKT_ERROR);
	case SKL_BYAKUREN_2:		
		return 100;
		//return SkillDiffer_simple(1,SKT_SPELLCASTING,SKT_ERROR,SKT_ERROR);
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_SIZUHA_1: //신앙심비례 성공율로 바꿈?
	case SKL_SIZUHA_2:
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
		success_ += you.skill[s1].level;
		num++;
	}	
	if(s2 != -1)
	{
		success_ += you.skill[s2].level;
		num++;
	}
	if(s3 != -1)
	{
		success_ += you.skill[s3].level;
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
		return 0;		
	case SKL_SWAKO_WATER_GUN:
		return 1;
	case SKL_KANAKO_1:
	case SKL_LEVITATION:
	case SKL_SATORI_1:
	case SKL_YUYUKO_1:
	case SKL_YUKARI_1:
	case SKL_SWAKO_JUMP:
	case SKL_SWAKO_TOUGUE:
		return 2;
	case SKL_KANAKO_2:
	case SKL_MINORIKO_1:
	case SKL_YUYUKO_2:
	case SKL_YUKARI_3:
		return 3;
	case SKL_BYAKUREN_2:
	case SKL_SIZUHA_1:
	case SKL_YUKARI_2:
		return 4;
	case SKL_EIRIN_2:
	case SKL_MINORIKO_2:
	case SKL_SATORI_2:
	case SKL_YUYUKO_3:
		return 5;
	case SKL_KANAKO_3:
		return 4;
	case SKL_INVISIBLE:
	case SKL_YUKARI_4:
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		return true;	
	case SKL_SATORI_1:
	case SKL_BYAKUREN_1:
	case SKL_SIZUHA_1:
		if(!check_)
			you.PietyUpDown(-2);
		return true;		
	case SKL_MINORIKO_1:
		if(check_ && you.power<100)
		{
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		if(!check_)
			you.PietyUpDown(-2);
		return true;
	case SKL_KANAKO_1:
		if(!check_)
			you.PietyUpDown(-3);
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(10+randA(5)),true);
		return true;
	case SKL_SWAKO_TEMPLE:
		if(check_ && you.power<100)
		{
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(20+randA(10)),true);
		return true;
	case SKL_SWAKO_CURSE:
		if(check_ && you.power<100)
		{
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("갑옷을 끼고 사용하여야 한다.",true,false,false,CL_small_danger);	
			return false;
		}
		if(!check_)
			you.PietyUpDown(-5);
		return true;
	case SKL_SATORI_2:
		if(!check_)
			you.PietyUpDown(-5);
		return true;
	case SKL_EIRIN_1:
		if(check_ && you.hp <  you.max_hp * 0.1f)
		{
			printlog("이 권능을 사용하기엔 체력이 너무 적다.",true,false,false,CL_small_danger);	
			return false;
		}
		if(!check_)
			you.PietyUpDown(-5);
		return true;
	case SKL_EIRIN_2:
		if(check_ && you.hp ==  you.max_hp)
		{
			printlog("이미 체력이 가득 차 있다.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PietyUpDown(-15);
		return true;		
	case SKL_YUUGI_1:
		if(!check_)
			you.PietyUpDown(-1);
		return true;
	case SKL_MINORIKO_2:
		if(check_ && you.power<100)
		{
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
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
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(10+randA(5)),true);
		return true;
	case SKL_HINA_2:
	case SKL_HINA_3:
	case SKL_HINA_4:
		return true;	
	case SKL_LEVITATION:
		if(check_ && you.power<100)
		{
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(3+randA(5)),true);
		return true;		
	case SKL_INVISIBLE:
		if(check_ && you.power<100)
		{
			printlog("파워 1칸 이상에서 써야한다.",true,false,false,CL_normal);	
			return false;
		}
		if(!check_)
			you.PowUpDown(-(8+randA(10)),true);
		return true;
	case SKL_NONE:
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
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
const char* SkillCostString(skill_list skill)
{
	switch(skill)
	{
	case SKL_KANAKO_1:
		return "(영력 2, 신앙)";		
	case SKL_MINORIKO_1:
		return "(영력 3, P 약간, 신앙)";
	case SKL_BYAKUREN_1:
		return "(신앙)";
	case SKL_YUUGI_1:
		return "(물약, 신앙)";
	case SKL_YUUGI_2:
		return "(신앙, P 소량)";
	case SKL_YUUGI_3:
		return "(신앙, P 소량)";
	case SKL_YUUGI_4:
		return "(신앙, P 약간)";
	case SKL_YUUGI_5:
		return "(신앙, P 대량)";
	case SKL_KANAKO_2:
		return "(영력 3, 신앙)";
	case SKL_BYAKUREN_2:
		return "(영력 4, 신앙)";
	case SKL_KANAKO_3:
		return "(영력 4, 신앙)";
	case SKL_EIRIN_0:
		return "(물약, P 약간)";
	case SKL_EIRIN_1:
		return "(고통, 신앙)";
	case SKL_EIRIN_2:
		return "(고통, 영력 5, 신앙)";	
	case SKL_MINORIKO_2:
		return "(음식, 영력 5, P 대량, 신앙)";	
	case SKL_SIZUHA_1:
		return "(영력 4, 신앙)";
	case SKL_SIZUHA_2:
		return "(신앙)";
	case SKL_LEVITATION:
		return "(영력 2, P 소량)";
	case SKL_INVISIBLE:
		return "(영력 2, P 약간)";
	case SKL_SATORI_1:
		return "(영력 2, 신앙)";	
	case SKL_SATORI_2:
		return "(영력 5, 시간, 신앙)";	
	case SKL_SHINKI_1:
		return "(신앙, P 소량)";
	case SKL_SHINKI_2:
		return "(신앙, P 약간)";
	case SKL_SHINKI_3:
		return "(신앙, P 대량)";
	case SKL_YUYUKO_1:
		return "(영력 2, P 소량)";
	case SKL_YUYUKO_2:
		return "(영력 3, 신앙)";
	case SKL_YUYUKO_3:
		return "(영력 5, 신앙)";
	case SKL_YUKARI_1:
		return "(영력 2, 신앙)";
	case SKL_YUKARI_2:
		return "(영력 4, 신앙)";
	case SKL_YUKARI_3:
		return "(영력 3, 신앙)";
	case SKL_YUKARI_4:
		return "(영력 6, 신앙)";
	case SKL_SWAKO_JUMP:
		return "(영력 2, P 소량)";
	case SKL_SWAKO_TEMPLE:
		return "(P 대량)";
	case SKL_SWAKO_WATER_GUN:
		return "(영력 1)";
	case SKL_SWAKO_TOUGUE:
		return "(영력 2, P 소량)";
	case SKL_SWAKO_CURSE:
		return "(신앙, P 약간)";
	case SKL_SWAKO_DIGGING:
		return "(신앙, P 약간)";
	case SKL_SWAKO_SUMMON_FLOG:
		return "(신앙, P 약간)";
	case SKL_SWAKO_STATUE:
		return "(신앙, P 약간)";
	case SKL_SWAKO_RAIN:
		return "(신앙, P 대량)";
	case SKL_SWAKO_SLEEP:
		return "(신앙, P 대량)";
	case SKL_SWAKO_MISYAGUZI:
		return "(신앙, P 대량)";
	case SKL_HINA_1:
		return "(P 소량)";
	case SKL_HINA_2:
		return "(저주)";
	case SKL_HINA_3:
		return "(저주)";
	case SKL_HINA_4:
		return "(저주)";
	case SKL_YUYUKO_ON:
	case SKL_YUYUKO_OFF:
	case SKL_NONE:
	case SKL_GRAZE:
	case SKL_GRAZE_OFF:
	case SKL_LEVITATION_OFF:
	case SKL_INVISIBLE_OFF:
	default:
		return "(없음)";
	}
}
int GetSpellBombRange(skill_list skill)
{	
	switch(skill)
	{		
	case SKL_YUUGI_3_THROW:
	case SKL_EIRIN_0:
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
		return 1;
	default:
		break;
	}
	return 0;
}



void SkillUse()
{
	if(you.currentSkillNum)
	{	
		int i=0;
		changedisplay(DT_SKILL_USE);
		while(1)
		{
			int key_ = waitkeyinput(true);
			if( (key_ >= 'a' && key_ <= 'z'))
			{
				int num = (key_-'a');
				if(skill_list skill_ = (skill_list)you.MemorizeSkill[num])
				{
					if(!GetDisplayMove()) //스킬사용
					{
						if(SkillMana(skill_)>you.mp)
						{
							printlog("당신의 영력이 모자란다.",true,false,false,CL_normal);	
							break;
						}
						if(!SkillFlagCheck(skill_, S_FLAG_IMMEDIATELY))
						{
							SetSpellSight(SkillLength(skill_),SkillFlagCheck(skill_, S_FLAG_RECT)?2:1);
							changedisplay(DT_GAME);
							beam_iterator beam(you.position,you.position);
							projectile_infor infor(SkillLength(skill_),false,SkillFlagCheck(skill_, S_FLAG_SMITE),skill_,true);
							if(int short_ = Common_Throw(you.item_list.end(), you.GetTargetIter(), beam, &infor))
							{
								unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
								if(unit_)
									you.youAttack(unit_);
								if(UseSkill(skill_, short_==2, you.search_pos))
								{
									SkillPlusCost(skill_,false);
									if(SkillMana(skill_))
										you.mp -= SkillMana(skill_);
									SkillUseTraning(skill_);
									Noise(you.position , SkillNoise(skill_));
									you.time_delay += you.GetNormalDelay();
									you.TurnEnd();
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
										you.mp -= SkillMana(skill_);
								}
								SkillUseTraning(skill_);
								Noise(you.position , SkillNoise(skill_));
								you.time_delay += you.GetNormalDelay();
								you.TurnEnd();
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
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
	}
	else
		printlog("아직 알고있는 능력이 없다.",true,false,false,CL_normal);	
}