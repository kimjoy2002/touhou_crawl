//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: tensi.h
//
// 내용: 텐시 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __TENSI_H__
#define  __TENSI_H__

#include <iostream>

using namespace std;


enum tensi_do_list
{
	TENSI_NOTHING,
	TENSI_POTION,
	TENSI_SUMMON,
	TENSI_TELE,
	TENSI_EARTHQUAKE,
	TENSI_MUNYUM,
	TENSI_BURST,
	TENSI_WEAPON,
	TENSI_KANAME,
	TENSI_FIELD,
	TENSI_BLIND,
	TENSI_BUFF_DEBUFF,
	TENSI_SUCIDE,
	TENSI_WEATHER_FOG,
	TENSI_WEATHER_THUNDER,
	TENSI_WEATHER_SUN
};

enum weather_list
{
	WTL_NONE=0,
	WTL_FIRE,
	WTL_COLD,
	WTL_EARTH,
	WTL_AIR,
	WTL_POISON,
	WTL_CHOAS,
	WTL_MAX
};
enum attack_type;
class unit;
attack_type GetWeatherType(unit* unit_, int damage_, int &bonus_damage_);
int GetChoas(unit* unit_, int damage_);

int GetHazard(); //현재의 위험도를 계산
void tensi_action();

string tensi_talk(bool good_, tensi_do_list list_);


#endif // __TENSI_H__