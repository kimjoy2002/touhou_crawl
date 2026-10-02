//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: flandre_spellcard.h
//
// 내용: 플랑드르의 스펠카드
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __FLANDRE_SPELLCARD_H__
#define __FLANDRE_SPELLCARD_H__

#include "../unique_spellcard.h"
#include "../const.h"

class monster;
class textures;

class flandre_spellcard : public unique_spellcard
{
private:
	const int FLANDRE_SPELL_DAMAGE = 25;
	enum
	{
		FLANDRE_PATTERN_STARTED = 1,
		FLANDRE_ESCAPE_ACTIVATE = 2
	};

	coord_def GetAngleGoal(const coord_def& start_, float angle_, int distance_);
	coord_def GetOppositeGoal(const coord_def& center_, const coord_def& start_);
	textures* GetFlandreBulletImage(int type_);
	attack_type GetFlandreBulletAttackType(int type_);
	void SpawnFlandreGrid(monster* owner_, int type_);
public:
	unique_spellcard_type GetType() const override;
	monster_index GetOwnerId() const override;
	LOCALIZATION_ENUM_KEY GetName() const override;
	int GetMaxTurn() const override;
	bool IsInvincible() const override;
	bool IsHidden() const override;
	void OnActivate(monster* mon_) override;
	void OnEscapeActivate(monster* mon_) override;
	void OnTurn(monster* mon_) override;
	bool OnFinish(monster* mon_) override;
};

#endif // __FLANDRE_SPELLCARD_H__
