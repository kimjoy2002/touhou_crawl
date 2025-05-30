﻿//////////////////////////////////////////////////////////////////////////////////////////////////
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



string GetGodString(god_type god);
int GetGodAbandonValue(god_type god);
int pietyLevel(int piety);
int GetGodGiftTime(god_type god);
D3DCOLOR GetGodColor(god_type god, int value = 0);
void mima_gift(book_list book_);
void satori_gift();
bool GodGift(god_type god, int piety);
bool GetGodAbility(int level, bool plus);
void GodInfor(god_type god);
void God_show();
bool God_pray(const list<item>::iterator it);
bool god_punish(god_type god);
void createGold(coord_def c, int num);
void joonRandomBuff();
bool sionResurrection();
int getMikoPiety(int kind);
void godAutoPickUp(god_type god_, bool belive_);

bool GodAccpect_KillMonster(monster* mon_, parent_type type_);
bool GodAccpect_Entering();
bool GodAccpect_GetPitem();
bool GodAccpect_HPUpDown(int value_,damage_reason reason);
bool GodAccpect_UseSpell(spell_list spell_);
bool GodAccpect_Practice(int value, skill_type skill_);
bool GodAccpect_Stair(bool down_, bool new_dungeon_);
bool GodAccpect_Explore_100();
bool GodAccpect_Exp_get();
bool GodAccpect_First_contact();
bool GodAccpect_Abandon(god_type god);
bool GodAccpect_turn(int turn);

int satori_sight();

void Pray();
void printReEnter();
bool God_PraySpeak();
void swako_gift(bool speak_);
void joon_sion_gift(bool speak_);
void minoriko_gift(bool speak_);
void byakuren_gift(bool speak_);
void kanako_tanmac_gift(bool speak_);
void kanako_gift(bool speak_);
item* armour_gift(bool speak_, bool artifact_);
item* jewelry_gift(bool speak_, bool curse_, bool artifact_);
void eirin_gift(bool speak_);


#endif // __GOD_H__
