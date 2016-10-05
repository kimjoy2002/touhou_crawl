//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: god.h
//
// 내용: 신에 대한 간략 정보
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __GOD_H__
#define  __GOD_H__

#include "enum.h"

enum spell_list;

enum GOD_CHECK_TYPE
{
	GCT_KILL,
	GCT_GETPITEM,
	GCT_SPELL,
	GCT_PRACTICE,
	GCT_EXPLORE,
	GCT_FIRST,
	GCT_TURN
};



const char* GetGodString(god_type god);
bool GetGodString_is(god_type god);
int GetGodAbandonValue(god_type god);
int pietyLevel(int piety);
int GetGodGiftTime(god_type god);
void mima_gift(book_list book_);
void satori_gift();
bool GodGift(god_type god, int piety);
bool GetGodAbility(int level, bool plus);
void GodInfor(god_type god);
void God_show();
bool God_pray(const list<item>::iterator it);
bool god_punish(god_type god);

bool GodAccpect_KillMonster(monster* mon_, parent_type type_);
bool GodAccpect_Entering();
bool GodAccpect_GetPitem();
bool GodAccpect_HPUpDown(int value_,damage_reason reason);
bool GodAccpect_UseSpell(spell_list spell_);
bool GodAccpect_Practice(int value, skill_type skill_);
bool GodAccpect_Explore_100();
bool GodAccpect_Exp_get();
bool GodAccpect_First_contact();
bool GodAccpect_Abandon(god_type god);
bool GodAccpect_turn(int turn);

int satori_sight();

void Pray();

void minoriko_gift(bool speak_);
void byakuren_gift(bool speak_);
void kanako_gift(bool speak_);
void armour_gift(bool speak_);
void jewelry_gift(bool speak_);
void eirin_gift(bool speak_);


#endif // __GOD_H__
