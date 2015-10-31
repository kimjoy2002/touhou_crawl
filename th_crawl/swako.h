//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: swako.h
//
// 내용: 스와코 권능 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SWAKO_H__
#define  __SWAKO_H__



enum swako_1_power //신앙이 들지않는 사용형 권능들
{
	SWAKO_1_JUMP=0, //점프
	SWAKO_1_TEMPLE, //신전세우기
	SWAKO_1_WATER_GUN, //물총
	SWAKO_1_TONGUE, //개구리 혀
	SWAKO_1_LAST
};
enum swako_2_power //효율이 좋은 패시브 권능들
{
	SWAKO_2_KILL_HP=0, //죽일때 체력회복
	SWAKO_2_KILL_MP, //죽일때 마나회복
	SWAKO_2_KILL_POWER, //죽일때 파워상승
	SWAKO_2_SWIM, //수영한다. 수영중엔 능력치의 상승
	SWAKO_2_DEAD_PROTECT, //죽음으로부터의 보호
	SWAKO_2_LAST
};

enum swako_3_power //신앙을 소모하는 사용형 권능
{
	SWAKO_3_CURSE=0, //토착신의재앙(감속,독)
	SWAKO_3_DIGGING, //굴착
	SWAKO_3_SUMMON_FLOG, //개구리소환(레벨비례 강함)
	SWAKO_3_STATUE, //길을 막는 개구리석상소환
	SWAKO_3_LAST
};

enum swako_4_power //저항을 준다
{
	SWAKO_4_COLD_RESIST=0, //냉기저항
	SWAKO_4_FIRE_RESIST, //화염저항
	SWAKO_4_AC, //추가 AC
	SWAKO_4_CONFUSE_RESIST, //혼란저항
	SWAKO_4_POISON_RESIST, //독저항
	SWAKO_4_LAST
};

enum swako_5_power //최종권능
{
	SWAKO_5_RAIN=0, //주변을 물바다로 만든다. 아군 개구리가 소환된다. 
	SWAKO_5_SLEEP, //동면. 턴을 지내고 체력마나가 조금 회복한다. 
	SWAKO_5_MISYAGUZI, //미샤구지님을 소환한다. 
	SWAKO_5_SWAKO_HAT, //스와코님의 모자를 받는다.(되돌리기 불가능)
	SWAKO_5_LAST
};

enum swako_string //무슨 정보가 필요한가
{
	SWAKO_NAME=0, //이름
	SWAKO_SIMPLE_INFOR, //신앙창에서 보여주는 정보
	SWAKO_GET_STRING, //권능을 얻었을때 정보
	SWAKO_UNGET_STRING, //권능이 사라졌을때 정보
	SWAKO_STRING
};


const char* GetSwakoString1(swako_1_power power, swako_string kind);
const char* GetSwakoString2(swako_2_power power, swako_string kind);
const char* GetSwakoString3(swako_3_power power, swako_string kind);
const char* GetSwakoString4(swako_4_power power, swako_string kind);
const char* GetSwakoString5(swako_5_power power, swako_string kind);


bool GetSwakoAbility(int level, bool plus);

#endif // __SWAKO_H__