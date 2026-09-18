//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: time_paradox.h
//
// 내용: 탄막 회수와 시간의 분신
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TIME_PARADOX_H__
#define __TIME_PARADOX_H__

#include "unit.h"

class item;
enum spell_list;

void TimeParadoxThrow(item* item_, coord_def target_, const beam_infor& infor_, int graphic_type);
void TimeParadoxSpell(spell_list skill_, int power_, coord_def target_);

#endif // __TIME_PARADOX_H__
