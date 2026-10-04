//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: unique_spellcard.cpp
//
// 내용: 네임드 전용 스펠카드 공통 처리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "unique_spellcard.h"
#include "spellcard/flandre_spellcard.h"
#include "environment.h"
#include "display.h"
#include "key.h"
#include "localization.h"
#include "mon_infor.h"
#include "player.h"
#include "save.h"
#include "skill_use.h"
#include "soundmanager.h"
#include "speak.h"

unique_spellcard_info::unique_spellcard_info()
{
	init();
}

void unique_spellcard_info::init()
{
	type = USC_NONE;
	state = USCS_NONE;
	turn = 0;
	max_turn = 0;
	last_turn = -1;
	next_pattern = 0;
	value1 = 0;
	value2 = 0;
	death_reason = PRT_NEUTRAL;
}

void unique_spellcard_info::SaveDatas(FILE *fp)
{
	SaveData<unique_spellcard_type>(fp,type);
	SaveData<unique_spellcard_state>(fp,state);
	SaveData<int>(fp,turn);
	SaveData<int>(fp,max_turn);
	SaveData<int>(fp,last_turn);
	SaveData<int>(fp,next_pattern);
	SaveData<int>(fp,value1);
	SaveData<int>(fp,value2);
	SaveData<parent_type>(fp,death_reason);
}

void unique_spellcard_info::LoadDatas(FILE *fp)
{
	LoadData<unique_spellcard_type>(fp,type);
	LoadData<unique_spellcard_state>(fp,state);
	LoadData<int>(fp,turn);
	LoadData<int>(fp,max_turn);
	LoadData<int>(fp,last_turn);
	LoadData<int>(fp,next_pattern);
	LoadData<int>(fp,value1);
	LoadData<int>(fp,value2);
	LoadData<parent_type>(fp,death_reason);
}

void unique_spellcard::Setup(monster* mon_) const
{
	if(!mon_)
		return;
	mon_->spellcard_info.init();
	mon_->spellcard_info.type = GetType();
	mon_->spellcard_info.state = USCS_READY;
	mon_->spellcard_info.max_turn = GetMaxTurn();
	mon_->spellcard_info.turn = GetMaxTurn();
	mon_->flag |= M_FLAG_NONE_STAIR;
}

unique_spellcard* GetUniqueSpellcardModel(unique_spellcard_type type_)
{
	static flandre_spellcard flandre_;
	switch(type_)
	{
	case USC_FLAN_AND_THEN_WILL_THERE_BE_NONE:
		return &flandre_;
	default:
		return nullptr;
	}
}

namespace
{
	bool HasUniqueSpellcard(int floor_, const monster* except_)
	{
		if(floor_ < 0)
			return false;
		for(const monster& mon_ : env[floor_].mon_vector)
			if(&mon_ != except_ && mon_.hp > 0 &&
				(mon_.spellcard_info.state == USCS_READY || mon_.spellcard_info.state == USCS_ACTIVE))
				return true;
		return false;
	}

	const unique_spellcard* GetMonsterSpellcardModel(monster_index id_)
	{
		for(int type_ = USC_NONE+1; type_ < USC_MAX; type_++)
		{
			const unique_spellcard* model_ = GetUniqueSpellcardModel((unique_spellcard_type)type_);
			if(model_ && model_->GetOwnerId() == id_)
				return model_;
		}
		return nullptr;
	}

	void ClearUniqueSpellcardBullets(int map_id_)
	{
		for(monster& mon_ : env[current_level].mon_vector)
			if(mon_.isLive() && mon_.id == MON_BULLET && mon_.sm_info.parent_map_id == map_id_)
			{
				mon_.will_move.clear();
				mon_.hp = 0;
			}
	}

	void UniqueSpellcardGet(monster* mon_)
	{
		if(!mon_)
			return;
		enterlog();
		LocalzationManager::printLogWithKey(LOC_SYSTEM_UNIQUE_SPELLCARD_GET,true,false,false,CL_magic,
			PlaceHolderHelper(mon_->name.getName()));
		PlaySE("spellcard");
	}

	void FinishUniqueSpellcard(int map_id_)
	{
		monster* mon_ = nullptr;
		for(monster& check_ : env[current_level].mon_vector)
			if(check_.map_id == map_id_ && check_.isLive())
			{
				mon_ = &check_;
				break;
			}
		if(!mon_)
			return;

		parent_type reason_ = mon_->spellcard_info.death_reason;
		unique_spellcard* model_ = GetUniqueSpellcardModel(mon_->spellcard_info.type);
		mon_->spellcard_info.state = USCS_CLEARED;
		mon_->spellcard_info.turn = 0;
		mon_->s_invincibility = 0;
		mon_->hp = 1;
		ClearUniqueSpellcardBullets(map_id_);
		UniqueSpellcardGet(mon_);
		if(model_ && model_->OnFinish(mon_))
			return;
		mon_->dead(reason_,false,false,nullptr);
	}
}

LOCALIZATION_ENUM_KEY GetUniqueSpellcardName(unique_spellcard_type type_)
{
	const unique_spellcard* model_ = GetUniqueSpellcardModel(type_);
	return model_ ? model_->GetName() : LOC_EMPTYSTRING;
}

bool IsUniqueSpellcardUsed(unique_spellcard_type type_)
{
	return type_ != USC_NONE &&
		find(you.used_unique_spellcards.begin(),you.used_unique_spellcards.end(),type_) != you.used_unique_spellcards.end();
}

namespace
{
	void SetUniqueSpellcardUsed(unique_spellcard_type type_)
	{
		if(type_ != USC_NONE && !IsUniqueSpellcardUsed(type_))
			you.used_unique_spellcards.push_back(type_);
	}
}

void SetupUniqueSpellcard(monster* mon_, int floor_)
{
	if(!mon_ || !(mon_->flag & M_FLAG_UNIQUE) || mon_->flag & M_FLAG_SUMMON ||
		HasUniqueSpellcard(floor_,mon_))
		return;

	const unique_spellcard* model_ = GetMonsterSpellcardModel((monster_index)mon_->id);
	if(model_ && !IsUniqueSpellcardUsed(model_->GetType()))
		model_->Setup(mon_);
}

void UniqueSpellcardFirstContact(monster* mon_)
{
	if(!mon_ || mon_->spellcard_info.state != USCS_READY)
		return;
	LocalzationManager::printLogWithKey(LOC_SYSTEM_UNIQUE_SPELLCARD_FOUND,true,false,false,CL_magic,
		PlaceHolderHelper(mon_->name.getName()));
	MoreWait();
}

bool TryActivateUniqueSpellcard(monster* mon_, parent_type reason_, unit* killer_, bool force_)
{
	if(!mon_)
		return false;
	unique_spellcard* model_ = GetUniqueSpellcardModel(mon_->spellcard_info.type);
	if(!model_)
		return false;
	if(mon_->spellcard_info.state == USCS_READY && IsUniqueSpellcardUsed(mon_->spellcard_info.type))
		return false;

	if(mon_->spellcard_info.state == USCS_ACTIVE && !model_->IsInvincible())
	{
		ClearUniqueSpellcardBullets(mon_->map_id);
		mon_->spellcard_info.state = USCS_CLEARED;
		mon_->spellcard_info.turn = 0;
		mon_->spellcard_info.death_reason = reason_;
		UniqueSpellcardGet(mon_);
		return false;
	}
	if(mon_->spellcard_info.state != USCS_READY)
		return false;

	mon_->spellcard_info.state = USCS_ACTIVE;
	SetUniqueSpellcardUsed(mon_->spellcard_info.type);
	mon_->spellcard_info.turn = mon_->spellcard_info.max_turn;
	mon_->spellcard_info.last_turn = -1;
	mon_->spellcard_info.death_reason = reason_;
	mon_->hp = mon_->max_hp;
	mon_->s_poison = 0;
	mon_->s_fire = 0;
	mon_->target = nullptr;
	mon_->memory_time = 0;
	mon_->will_move.clear();
	mon_->state.SetState(MS_NORMAL);
	env[current_level].SummonClear(mon_->map_id);
	if(model_->IsInvincible())
		mon_->s_invincibility = -1;
	model_->OnActivate(mon_);

	LOCALIZATION_ENUM_KEY message_ = LOC_SYSTEM_UNIQUE_SPELLCARD_ACTIVATE;
	LocalzationManager::printLogWithKey(message_,true,false,false,CL_magic,
		PlaceHolderHelper(mon_->name.getName()));
	if(mon_->CanSpeak() && !mon_->s_mute)
	{
		string speak_ = Get_Speak(mon_->id,mon_,force_?MST_SPELLCARD_FORCE:MST_SPELLCARD);
		if(!speak_.empty())
			printlog(speak_,true,false,false,force_?CL_magic:CL_speak);
	}
	PlaySE("spellcard");
	MoreWait();
	return true;
}

bool TryActivateUniqueSpellcardEscape(monster* mon_)
{
	if(!mon_ || mon_->spellcard_info.state != USCS_READY)
		return false;
	unique_spellcard* model_ = GetUniqueSpellcardModel(mon_->spellcard_info.type);
	if(!model_ || !TryActivateUniqueSpellcard(mon_,PRT_NEUTRAL,nullptr,true))
		return false;
	model_->OnEscapeActivate(mon_);
	return true;
}

bool IsUniqueSpellcardHidden(const monster* mon_)
{
	if(!mon_ || mon_->spellcard_info.state != USCS_ACTIVE)
		return false;
	const unique_spellcard* model_ = GetUniqueSpellcardModel(mon_->spellcard_info.type);
	return model_ && model_->IsHidden();
}

monster* GetActiveUniqueSpellcard()
{
	for(monster& mon_ : env[current_level].mon_vector)
		if(mon_.isLive() && mon_.spellcard_info.state == USCS_ACTIVE)
			return &mon_;
	return nullptr;
}

bool IsUniqueSpellcardActive()
{
	return GetActiveUniqueSpellcard() != nullptr;
}

bool CheckUniqueSpellcardFloorMove()
{
	if(!IsUniqueSpellcardActive())
		return true;
	printlog(LocalzationManager::locString(LOC_SYSTEM_UNIQUE_SPELLCARD_STAIR_BLOCK),true,false,false,CL_magic);
	return false;
}

void UniqueSpellcardTurnEnd()
{
	monster* mon_ = GetActiveUniqueSpellcard();
	if(!mon_)
		return;
	if(mon_->spellcard_info.last_turn == -1)
	{
		mon_->spellcard_info.last_turn = you.turn;
		return;
	}
	if(mon_->spellcard_info.last_turn == you.turn)
		return;

	mon_->spellcard_info.last_turn = you.turn;
	if(mon_->spellcard_info.turn > 0)
		mon_->spellcard_info.turn--;

	int map_id_ = mon_->map_id;
	unique_spellcard* model_ = GetUniqueSpellcardModel(mon_->spellcard_info.type);
	if(model_)
		model_->OnTurn(mon_);

	for(monster& check_ : env[current_level].mon_vector)
		if(check_.map_id == map_id_ && check_.isLive())
		{
			if(check_.spellcard_info.turn == 0)
				FinishUniqueSpellcard(map_id_);
			break;
		}
}

bool WizardActivateUniqueSpellcard(unique_spellcard_type type_)
{
	const unique_spellcard* model_ = GetUniqueSpellcardModel(type_);
	if(!model_ || IsUniqueSpellcardActive() || IsUniqueSpellcardUsed(type_))
		return false;

	monster* owner_ = nullptr;
	for(monster& mon_ : env[current_level].mon_vector)
		if(mon_.isLive() && mon_.id == model_->GetOwnerId() && !(mon_.flag & M_FLAG_SUMMON))
		{
			owner_ = &mon_;
			break;
		}
	if(!owner_)
	{
		owner_ = BaseSummon(model_->GetOwnerId(),100,false,false,2,&you,you.position,SKD_OTHER,-1);
		if(!owner_)
			return false;
		owner_->flag &= ~M_FLAG_SUMMON;
		owner_->summon_time = 0;
		owner_->ReturnEnemy();
	}

	model_->Setup(owner_);
	return TryActivateUniqueSpellcard(owner_,PRT_PLAYER,&you);
}
