//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: spellcard.h
//
// 내용: 스펠카드 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SPELLCARD_H__
#define  __SPELLCARD_H__


#include "player.h"

struct item_infor;
enum skill_flag;

//
//bool declare_spellcard(spellcard_declare_type kind, int power);
bool evoke_spellcard(spellcard_evoke_type kind, int power, bool fail_, bool iden_, bool auto_);//fail_은 무조건 실패 iden_은 미식별상태에서 조준실패시 true리턴
//bool passive_spellcard(spellcard_passive_type kind, int power, int value, int turn_);
//int spellcard_turn(spellcard_declare_type kind1, spellcard_evoke_type kind2, spellcard_passive_type kind3);

float SpellcardSector(spellcard_evoke_type skill);
void createSpellCard(int goodbad, int select_, item_infor* t);
const char* SpellcardName(spellcard_evoke_type skill);
int SpellcardMaxCharge(spellcard_evoke_type skill);

bool base_bomb(int damage, int max_damage, int size, attack_type type, unit* order, name_infor bomb_name, coord_def target);
bool skill_lightning(int power, unit* order, coord_def *start, int& direc, int count);

bool SpellcardFlagCheck(spellcard_evoke_type skill, skill_flag flag);

#endif // __SPELLCARD_H__
