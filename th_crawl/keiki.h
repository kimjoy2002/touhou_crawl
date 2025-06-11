//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: keiki.h
//
// 내용: 케이키 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __KEIKI_H__
#define  __KEIKI_H__

#include "common.h"
#include "enumMapBuilder.h"

using namespace std;


class monster;

enum haniwa_abil_key {
	HANIWA_A_SWORD,
	HANIWA_A_DOUBLE_SWORD,
	HANIWA_A_SPEAR,
	HANIWA_A_BOW,
	HANIWA_A_SHIELD1,
	HANIWA_A_SHIELD2,
	HANIWA_A_EXPLOSION,
	HANIWA_A_ARMY1,
	HANIWA_A_ARMY2,
	HANIWA_A_CLEAVE,
	HANIWA_A_FIRE_ENCHANT,
	HANIWA_A_COLD_ENCHANT,
	HANIWA_A_ELEC_ENCHANT,
	HANIWA_A_POISON_ENCHANT,
	HANIWA_A_SLOW_ENCHANT,
	HANIWA_A_TANMAC,
	HANIWA_A_FIRE_TANMAC,
	HANIWA_A_COLD_TANMAC,
	HANIWA_A_ELEC_TANMAC,
	HANIWA_A_MIDDLE_TANMAC,
	HANIWA_A_BIG_TANMAC,
	HANIWA_A_BURST_TANMAC,
	HANIWA_A_BLINK,
	HANIWA_A_SLOW,
	HANIWA_A_CONFUSE,
	HANIWA_A_PENTAN,
	HANIWA_A_HASTE,
	HANIWA_A_MAGICIAN,
	HANIWA_A_CREATE_P,
	HANIWA_A_CREATE_WEAPON,
	HANIWA_A_CREATE_WEAPON_ARTIFACT,
	HANIWA_A_CREATE_ARMOUR,
	HANIWA_A_CREATE_ARMOUR_ARTIFACT,
	HANIWA_A_CREATE_POTION,
	HANIWA_A_CREATE_SCROLL,
	HANIWA_A_WARN_NAMED,
	HANIWA_A_IDEN,
	HANIWA_A_HEAL,
	HANIWA_A_HARDEN1,
	HANIWA_A_HARDEN2,
	HANIWA_A_HARDEN3,
	HANIWA_A_FAST_REVIVE,
	HANIWA_A_HORSE,
	HANIWA_A_FLY,
	HANIWA_A_TALK,
	HANIWA_A_GIRL,
	HANIWA_A_MAX
};

enum haniwa_abil_type {
	HANIWA_T_COMBAT,
	HANIWA_T_MAGIC,
	HANIWA_T_SUPPORT,
	HANIWA_T_COMMON
};



class haniwa_abil {
public:
	LOCALIZATION_ENUM_KEY name;
	LOCALIZATION_ENUM_KEY infor;
	
	haniwa_abil_type type;
	int cost;
	int percent;
	
	vector<haniwa_abil_key> must_abil;
	vector<haniwa_abil_key> need_abil;
	vector<haniwa_abil_key> except_abil;
	
	haniwa_abil(LOCALIZATION_ENUM_KEY name, LOCALIZATION_ENUM_KEY infor, haniwa_abil_type type, int cost, int percent, vector<haniwa_abil_key> must_abil, vector<haniwa_abil_key> need_abil, vector<haniwa_abil_key> except_abil);
	
	string getCostString();

public:
	static const int max_piety = 160;

	static random_extraction<haniwa_abil_key> getAbleHaniwaAbils();

	static bool has_abil(haniwa_abil_key key);
	static bool set_abil(haniwa_abil_key key);
	static int getMaxHaniwa();

	static monster* createHaniwa(int index, bool first_);
	static void upgradeHaniwa(monster* mon);
	static void upgradeHaniwa();
	static void haniwaDraw(float x_, float y_, float scale_);
};

bool keiki_gift();
extern haniwa_abil haniwa_abil_list[HANIWA_A_MAX];

#endif // __KEIKI_H__