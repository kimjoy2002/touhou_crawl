//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: flandre_spellcard.cpp
//
// 내용: 플랑드르의 스펠카드
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "flandre_spellcard.h"
#include "bullet.h"
#include "../environment.h"
#include "../mon_infor.h"
#include "../monster.h"
#include "../monster_texture.h"
#include "../soundmanager.h"

coord_def flandre_spellcard::GetAngleGoal(const coord_def& start_, float angle_, int distance_)
{
	float radian_ = GetDegToRad(angle_);
	return coord_def(start_.x+(int)round(cos(radian_)*distance_),
		start_.y+(int)round(sin(radian_)*distance_));
}
coord_def flandre_spellcard::GetOppositeGoal(const coord_def& center_, const coord_def& start_)
{
	return coord_def(center_.x*2-start_.x,center_.y*2-start_.y);
}
textures* flandre_spellcard::GetFlandreBulletImage(int type_)
{
	const int image_index_[3] = {0,4,3};
	return &img_bullet[image_index_[type_%3]];
}
attack_type flandre_spellcard::GetFlandreBulletAttackType(int type_)
{
	const attack_type attack_type_[3] = {ATT_FIRE,ATT_COLD,ATT_ELEC};
	return attack_type_[type_%3];
}
void flandre_spellcard::SpawnFlandreGrid(monster* owner_, int type_)
{
	const int hit_ = 99;
	const int radius_ = 8;
	const int interval_ = 3;
	const float yellow_angle_ = 45.0f;
	const attack_type attack_type_ = GetFlandreBulletAttackType(type_);
	const coord_def center_ = you.position;
	const int phase_ = ((owner_->spellcard_info.max_turn-owner_->spellcard_info.turn)/5)%interval_;
	const int offset_radius_ = type_ == 2 ? radius_*2 : radius_ + rand_int(-1,1);
	int line_index_ = 0;
	for(int offset_ = -offset_radius_+phase_; offset_ <= offset_radius_; offset_ += interval_)
	{
		coord_def top_(center_.x+offset_,center_.y-radius_);
		coord_def bottom_(center_.x+offset_,center_.y+radius_);
		coord_def left_(center_.x-radius_,center_.y+offset_);
		coord_def right_(center_.x+radius_,center_.y+offset_);
		if(type_ == 0) {
			CreateBulletToTarget(top_,GetOppositeGoal(center_,top_),GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
			CreateBulletToTarget(bottom_,GetOppositeGoal(center_,bottom_),GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
			CreateBulletToTarget(left_,GetOppositeGoal(center_,left_),GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
			CreateBulletToTarget(right_,GetOppositeGoal(center_,right_),GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
		}
		else if(type_ == 1) {
			CreateStraightBullet(top_,4,2*radius_,GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
			CreateStraightBullet(bottom_+coord_def(1,0),0,2*radius_,GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
			CreateStraightBullet(left_,2,2*radius_,GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
			CreateStraightBullet(right_+coord_def(0,1),6,2*radius_,GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
		}
		else
		{
			float turn_angle_ = line_index_%2 == 0 ? -yellow_angle_ : yellow_angle_;
			CreateBulletToTarget(top_,GetAngleGoal(top_,90.0f+turn_angle_,2*radius_),GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
			CreateBulletToTarget(bottom_,GetAngleGoal(bottom_,270.0f+turn_angle_,2*radius_),GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
			CreateBulletToTarget(left_,GetAngleGoal(left_,turn_angle_,2*radius_),GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
			CreateBulletToTarget(right_,GetAngleGoal(right_,180.0f+turn_angle_,2*radius_),GetFlandreBulletImage(type_),FLANDRE_SPELL_DAMAGE,hit_,attack_type_,10,-1,owner_->map_id);
		}
		line_index_++;
	}
	PlaySE("shoot_heavy");
}

unique_spellcard_type flandre_spellcard::GetType() const
{
	return USC_FLAN_AND_THEN_WILL_THERE_BE_NONE;
}

monster_index flandre_spellcard::GetOwnerId() const
{
	return MON_FLAN;
}

LOCALIZATION_ENUM_KEY flandre_spellcard::GetName() const
{
	return LOC_SYSTEM_UNIQUE_SPELLCARD_FLAN_NAME;
}

int flandre_spellcard::GetMaxTurn() const
{
	return 99;
}

bool flandre_spellcard::IsInvincible() const
{
	return true;
}

bool flandre_spellcard::IsHidden() const
{
	return true;
}

void flandre_spellcard::OnActivate(monster* mon_)
{
	mon_->spellcard_info.next_pattern = 15;
	mon_->spellcard_info.value1 = 0;
	mon_->spellcard_info.value2 = 0;
}

void flandre_spellcard::OnEscapeActivate(monster* mon_)
{
	mon_->spellcard_info.value2 |= FLANDRE_ESCAPE_ACTIVATE;
}

void flandre_spellcard::OnTurn(monster* mon_)
{
	int elapsed_ = mon_->spellcard_info.max_turn-mon_->spellcard_info.turn;
	// if(mon_->spellcard_info.turn > 45 && elapsed_ >= mon_->spellcard_info.next_pattern)
	// {
	// 	int next_interval_ = max(5,15-min(10,elapsed_/5));
	// 	mon_->spellcard_info.next_pattern = elapsed_+next_interval_;
	// 	SpawnFlandreBat(mon_);
	// }
	// else 
	if(!(mon_->spellcard_info.value2&FLANDRE_PATTERN_STARTED) || elapsed_ >= mon_->spellcard_info.next_pattern)
	{
		int type_ = mon_->spellcard_info.value1%3;
		mon_->spellcard_info.value1++;
		mon_->spellcard_info.value2 |= FLANDRE_PATTERN_STARTED;
		int next_interval_ = max(5,10-min(5,elapsed_/15));
		mon_->spellcard_info.next_pattern = elapsed_+next_interval_;
		SpawnFlandreGrid(mon_,type_);
	}
}

bool flandre_spellcard::OnFinish(monster* mon_)
{
	if(!(mon_->spellcard_info.value2&FLANDRE_ESCAPE_ACTIVATE))
		return false;

	vector<coord_def> able_;
	for(int radius_ = 2; radius_ <= 8; radius_++)
	{
		for(int x_ = -radius_; x_ <= radius_; x_++)
			for(int y_ = -radius_; y_ <= radius_; y_++)
			{
				if(max(abs(x_),abs(y_)) != radius_)
					continue;
				coord_def pos_ = you.position+coord_def(x_,y_);
				if(pos_.x < 0 || pos_.x >= DG_MAX_X || pos_.y < 0 || pos_.y >= DG_MAX_Y ||
					!env[current_level].isMove(pos_,false,false) ||
					env[current_level].isMonsterPos(pos_.x,pos_.y,mon_))
					continue;
				able_.push_back(pos_);
			}
		if(!able_.empty())
			break;
	}
	if(!able_.empty())
		mon_->SetXY(able_[randA((int)able_.size()-1)]);
	mon_->hp = mon_->max_hp;
	mon_->target = nullptr;
	mon_->memory_time = 0;
	mon_->will_move.clear();
	mon_->state.SetState(MS_NORMAL);
	mon_->SetDazed(rand_int(10,20),false);
	return true;
}
