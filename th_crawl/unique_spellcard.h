//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: unique_spellcard.h
//
// 내용: 네임드 전용 스펠카드
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __UNIQUE_SPELLCARD_H__
#define __UNIQUE_SPELLCARD_H__

#include <stdio.h>
#include "enum.h"

class monster;
class unit;

class unique_spellcard_info
{
public:
	unique_spellcard_type type;
	unique_spellcard_state state;
	int turn;
	int max_turn;
	int last_turn;
	int next_pattern;
	int value1;
	int value2;
	parent_type death_reason;

	unique_spellcard_info();
	void init();
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
};

class unique_spellcard
{
public:
	virtual ~unique_spellcard() = default;
	virtual unique_spellcard_type GetType() const = 0;
	virtual monster_index GetOwnerId() const = 0;
	virtual LOCALIZATION_ENUM_KEY GetName() const = 0;
	virtual int GetMaxTurn() const = 0;
	virtual bool IsInvincible() const { return false; }
	virtual bool IsHidden() const { return false; }
	virtual void OnActivate(monster* mon_) {}
	virtual void OnEscapeActivate(monster* mon_) {}
	virtual void OnTurn(monster* mon_) {}
	virtual bool OnFinish(monster* mon_) { return false; }

	void Setup(monster* mon_) const;
};

unique_spellcard* GetUniqueSpellcardModel(unique_spellcard_type type_);
void SetupUniqueSpellcard(monster* mon_, int floor_);
void UniqueSpellcardFirstContact(monster* mon_);
bool TryActivateUniqueSpellcard(monster* mon_, parent_type reason_, unit* killer_, bool force_ = false);
bool TryActivateUniqueSpellcardEscape(monster* mon_);
bool IsUniqueSpellcardHidden(const monster* mon_);
bool IsUniqueSpellcardUsed(unique_spellcard_type type_);
monster* GetActiveUniqueSpellcard();
bool IsUniqueSpellcardActive();
bool CheckUniqueSpellcardFloorMove();
void UniqueSpellcardTurnEnd();
bool WizardActivateUniqueSpellcard(unique_spellcard_type type_);
LOCALIZATION_ENUM_KEY GetUniqueSpellcardName(unique_spellcard_type type_);

#endif // __UNIQUE_SPELLCARD_H__
