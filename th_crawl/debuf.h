//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: debuf.h
//
// 내용: 디버프 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __DEBUF_H__
#define  __DEBUF_H__

#include "skill_use.h"
#include "common.h"

class unit;

unit* DebufBeam(spell_list spell_, unit* order, coord_def target);
unit* DebufBeam(skill_list skill_, unit* order, coord_def target);
int GetDebufPower(spell_list skill, int power_);//디버프의 파워
int GetDebufPower(skill_list skill, int power_);//디버프의 파워(스킬들)


#endif // __DEBUF_H__