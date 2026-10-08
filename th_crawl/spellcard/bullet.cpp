//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bullet.cpp
//
// 내용: 스펠카드용 탄막 공통 처리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "bullet.h"
#include "../beam.h"
#include "../environment.h"
#include "../mon_infor.h"
#include "../monster.h"
#include "../summon.h"

namespace
{
	void RemoveBullet(monster* mon_)
	{
		if(mon_)
			mon_->hp = 0;
	}

	bool HasNonBulletMonster(const coord_def& pos_, const monster* except_)
	{
		for(const monster& mon_ : env[current_level].mon_vector)
			if(&mon_ != except_ && mon_.hp > 0 && mon_.id != MON_BULLET &&
				!IsUniqueSpellcardHidden(&mon_) && mon_.position == pos_)
				return true;
		return false;
	}
}

monster* CreateBullet(const coord_def& start_, textures* image_, const std::list<coord_def>& route_,
	int damage_, int hit_, attack_type attack_type_, int speed_, int life_, int parent_map_id_)
{
	if(start_.x < 0 || start_.x >= DG_MAX_X || start_.y < 0 || start_.y >= DG_MAX_Y ||
		start_ == you.position || HasNonBulletMonster(start_,nullptr) || route_.empty())
		return nullptr;

	summon_info summon_(parent_map_id_,SKD_OTHER,-1);
	monster* bullet_ = env[current_level].AddMonster_Summon(MON_BULLET,
		M_FLAG_SUMMON | M_FLAG_WAKE | M_FLAG_EVENT | M_FLAG_SILENT_DESPAWN,
		start_,summon_,life_);
	if(!bullet_)
		return nullptr;

	bullet_->image = image_;
	bullet_->atk[0] = damage_;
	bullet_->atk_type[0] = attack_type_;
	bullet_->atk_name[0] = name_infor(LOC_SYSTEM_ATT_TANMAC);
	bullet_->special_value = hit_;
	bullet_->speed = speed_;
	bullet_->will_move = route_;
	bullet_->direction = GetPosToDirec(start_,route_.front());
	return bullet_;
}

monster* CreateBulletToTarget(const coord_def& start_, const coord_def& goal_, textures* image_,
	int damage_, int hit_, attack_type attack_type_, int speed_, int life_, int parent_map_id_)
{
	if(start_ == goal_)
		return nullptr;

	std::list<coord_def> route_;
	beam_iterator beam_(start_,goal_,RT_ROUND);
	while(!beam_.end())
	{
		route_.push_back(*beam_);
		beam_++;
	}
	route_.push_back(goal_);
	return CreateBullet(start_,image_,route_,damage_,hit_,attack_type_,speed_,life_,parent_map_id_);
}

monster* CreateStraightBullet(const coord_def& start_, int direction_, int distance_, textures* image_,
	int damage_, int hit_, attack_type attack_type_, int speed_, int life_, int parent_map_id_)
{
	coord_def delta_ = GetDirecToPos(direction_);
	coord_def goal_(start_.x+delta_.x*distance_,start_.y+delta_.y*distance_);
	return CreateBulletToTarget(start_,goal_,image_,damage_,hit_,attack_type_,speed_,life_,parent_map_id_);
}

bool MoveBullet(monster* mon_)
{
	if(!mon_ || mon_->id != MON_BULLET)
		return false;
	if(mon_->will_move.empty())
	{
		RemoveBullet(mon_);
		return true;
	}

	coord_def next_ = mon_->will_move.front();
	mon_->will_move.pop_front();
	if(next_.x < 0 || next_.x >= DG_MAX_X || next_.y < 0 || next_.y >= DG_MAX_Y)
	{
		RemoveBullet(mon_);
		return true;
	}
	if(next_ == you.position)
	{
		if(mon_->sm_info.parent_map_id == you.GetMapId())
		{
			RemoveBullet(mon_);
			return true;
		}
		attack_infor attack_(mon_->GetAttack(0,false),mon_->GetAttack(0,true),mon_->special_value,
			mon_,PRT_ENEMY,mon_->atk_type[0],mon_->atk_name[0]);
		attack_.no_owner = true;
		you.damage(attack_);
		RemoveBullet(mon_);
		return true;
	}
	if(mon_->sm_info.parent_map_id == you.GetMapId())
	{
		unit* hit_ = env[current_level].isMonsterPos(next_.x,next_.y,mon_);
		if(hit_ && !hit_->isplayer())
		{
			monster* target_ = static_cast<monster*>(hit_);
			if(you.isEnemyUnit(target_))
			{
				attack_infor attack_(mon_->GetAttack(0,false),mon_->GetAttack(0,true),mon_->special_value,
					&you,PRT_PLAYER,mon_->atk_type[0],mon_->atk_name[0]);
				target_->damage(attack_);
			}
			RemoveBullet(mon_);
			return true;
		}
	}
	if(HasNonBulletMonster(next_,mon_))
	{
		RemoveBullet(mon_);
		return true;
	}

	mon_->direction = GetPosToDirec(mon_->position,next_);
	mon_->SetXY(next_);
	return true;
}
