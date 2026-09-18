//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: time_paradox.cpp
//
// 내용: 탄막 회수와 시간의 분신
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "time_paradox.h"
#include "player.h"
#include "environment.h"
#include "skill_use.h"
#include "throw.h"
#include "rect.h"
#include "soundmanager.h"
#include "monster_texture.h"
#include "mon_infor.h"


static monster* GetTimeParadox()
{
	for(monster& mon_ : env[current_level].mon_vector)
	{
		if(mon_.id == MON_TIME_PARADOX && mon_.isLive() && mon_.isUserAlly() &&
			mon_.special_value > 0 && mon_.summon_time > 0 && mon_.isYourShight())
			return &mon_;
	}
	return NULL;
}

static bool TimeParadoxSafe(monster* mon_, coord_def target_, int length_, int radius_, beam_iterator& beam_)
{
	if(target_ == mon_->position || !env[current_level].isInSight(target_) ||
		GetPositionGap(mon_->position.x,mon_->position.y,target_.x,target_.y) >= length_+1 ||
		!CheckThrowPath(mon_->position,target_,beam_))
		return false;
	// 빗나가거나 관통했을 때의 경로도 확인한다.
	for(beam_.init();;beam_++)
	{
		coord_def pos_ = *beam_;
		if(GetPositionGap(mon_->position.x,mon_->position.y,pos_.x,pos_.y) >= length_+1)
			break;
		if(max(abs(pos_.x-you.position.x),abs(pos_.y-you.position.y)) <= radius_)
			return false;
		for(monster& other_ : env[current_level].mon_vector)
		{
			if(&other_ != mon_ && other_.isLive() && !you.isEnemyUnit(&other_) &&
				max(abs(pos_.x-other_.position.x),abs(pos_.y-other_.position.y)) <= radius_)
				return false;
		}
		if(!env[current_level].isMove(pos_.x,pos_.y,true))
			break;
	}
	beam_.init();
	return true;
}

static void UseTimeParadox(monster* mon_, int cost_)
{
	mon_->special_value -= cost_;
	if(mon_->special_value <= 0 && mon_->isLive())
		mon_->dead(PRT_NEUTRAL,false,true);
}

static bool TimeParadoxSectorSafe(monster* mon_, coord_def target_, spell_list skill_)
{
	float angle_ = atan2((float)(target_.y-mon_->position.y),(float)(target_.x-mon_->position.x));
	int length_ = SpellLength(skill_,false);
	auto in_sector_ = [&](coord_def pos_)
	{
		int dx_ = pos_.x-mon_->position.x, dy_ = pos_.y-mon_->position.y;
		if(dx_*dx_+dy_*dy_ >= (length_+1)*(length_+1))
			return false;
		if(skill_ == SPL_SHOCK)
		{
			int direction_ = GetPosToDirec(mon_->position,target_);
			int other_ = GetPosToDirec(mon_->position,pos_);
			return min((direction_-other_+8)%8,(other_-direction_+8)%8) < 2;
		}
		return cos(atan2((float)dy_,(float)dx_)-angle_) >= cos(GetSpellSector(skill_));
	};
	if(in_sector_(you.position))
		return false;
	for(monster& other_ : env[current_level].mon_vector)
	{
		if(&other_ != mon_ && other_.isLive() && !you.isEnemyUnit(&other_) && in_sector_(other_.position))
			return false;
	}
	return true;
}

static bool TimeParadoxChainSafe(monster* mon_, coord_def target_)
{
	vector<pair<coord_def,int>> positions_;
	positions_.push_back(make_pair(mon_->position,GetPosToDirec(mon_->position,target_)));
	// 연쇄 대상이 무작위이므로 가능한 경로에 아군이 있으면 사용하지 않는다.
	for(int count_ = 0; count_ < 6 && !positions_.empty(); count_++)
	{
		vector<pair<coord_def,int>> next_;
		set<pair<int,int>> checked_;
		int length_ = SpellLength(SPL_CHAIN_LIGHTNING,false)*(count_?0.5f:1.0f);
		for(auto& pos_ : positions_)
		{
			auto reachable_ = [&](coord_def target_pos_, int angle_)
			{
				int dx_ = target_pos_.x-pos_.first.x, dy_ = target_pos_.y-pos_.first.y;
				int direction_ = GetPosToDirec(pos_.first,target_pos_);
				if((dx_ == 0 && dy_ == 0) || dx_*dx_+dy_*dy_ > length_*length_ ||
					min((direction_-pos_.second+8)%8,(pos_.second-direction_+8)%8) >= angle_)
					return false;
				beam_iterator beam_(pos_.first,target_pos_);
				return CheckThrowPath(pos_.first,target_pos_,beam_);
			};
			if(reachable_(you.position,2))
				return false;
			for(monster& other_ : env[current_level].mon_vector)
			{
				if(!other_.isLive() || other_.elec_resist > 2 || !reachable_(other_.position,3))
					continue;
				if(!you.isEnemyUnit(&other_))
					return false;
				int direction_ = GetPosToDirec(pos_.first,other_.position);
				if(checked_.insert(make_pair(other_.map_id,direction_)).second)
					next_.push_back(make_pair(other_.position,direction_));
			}
		}
		positions_.swap(next_);
	}
	return true;
}

void TimeParadoxThrow(item* item_, coord_def target_, const beam_infor& infor_, int graphic_type)
{
	monster* mon_ = GetTimeParadox();
	if(!mon_)
		return;
	beam_infor echo_ = infor_;
	echo_.order = mon_;
	echo_.p_type = mon_->GetParentType();
	echo_.damage = echo_.damage*4/5;
	echo_.max_damage = echo_.max_damage*4/5;
	echo_.length = min(you.getThrowLength(),(int)ceil(GetPositionGap(mon_->position.x,mon_->position.y,target_.x,target_.y)));
	bool kiku_ = item_->type >= ITM_THROW_FIRST && item_->type < ITM_THROW_LAST && item_->value4 == TMT_KIKU_COMPRESSER;
	beam_iterator beam_(mon_->position,target_);
	if(!TimeParadoxSafe(mon_,target_,echo_.length,kiku_?1:0,beam_))
		return;
	if(item_->type == ITM_WEAPON_SHORTBLADE && item_->value0 == 1)
		PlaySE("knife");
	vector<beam_iterator> sides_;
	if(IsSakuyaKnife(item_))
	{
		for(beam_iterator side_ : GetSakuyaKnifeBeams(mon_->position,target_,you.getThrowLength()))
		{
			if(TimeParadoxSafe(mon_,side_.target,you.getThrowLength(),0,side_))
				sides_.push_back(side_);
		}
		ThrowSakuyaKnives(beam_,sides_,echo_,item_,true,graphic_type);
	}
	else
	{
		coord_def hit_ = throwtanmac(graphic_type,beam_,echo_,item_,true,true);
		if(kiku_)
		{
			int power_ = you.GetSkillLevel(SKT_TANMAC,true)*5;
			attack_infor attack_(randC(3,5+power_/8)*4/5,3*(5+power_/8)*4/5,99,mon_,mon_->GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_KIKU_SPRAY));
			BaseBomb(hit_,&img_fog_cold[0],attack_);
		}
	}
	UseTimeParadox(mon_,1);
}

void TimeParadoxSpell(spell_list skill_, int power_, coord_def target_)
{
	// 지점 지정, 소환, 강화 마법은 복제하지 않는다.
	int radius_ = 0;
	switch(skill_)
	{
	case SPL_FIRE_BALL:
	case SPL_LUMINUS_STRIKE:
	case SPL_CANNON:
	case SPL_THROW_OIL:
	case SPL_THROW_BUCKET:
	case SPL_HANIWA_MAGIC_TANMAC:
	case SPL_HANIWA_MAGIC_TANMAC2:
	case SPL_HANIWA_MAGIC_TANMAC3:
		radius_ = 1;
		break;
	case SPL_MON_TANMAC_SMALL:
	case SPL_MON_TANMAC_MIDDLE:
	case SPL_MON_WATER_GUN:
	case SPL_FLAME:
	case SPL_FROST:
	case SPL_STING:
	case SPL_SHOCK:
	case SPL_CHAIN_LIGHTNING:
	case SPL_SPARK:
	case SPL_FIRE_SPREAD:
	case SPL_COLD_BEAM:
	case SPL_MAGIC_TANMAC:
	case SPL_FIRE_BOLT:
	case SPL_ICE_BOLT:
	case SPL_VENOM_BOLT:
	case SPL_WATER_CANNON:
	case SPL_LASER:
	case SPL_STONE_ARROW:
	case SPL_SCHEMA_TANMAC:
	case SPL_MOON_GUN:
	case SPL_NESY_CANNON:
	case SPL_THUNDER_BOLT:
	case SPL_THROW_DISH:
	case SPL_HYPER_BEAM:
	case SPL_THROW_SWORD:
	case SPL_THROW_KNIFE:
	case SPL_THROW_AMULET:
	case SPL_ARROW:
	case SPL_ACID_BOLT:
	case SPL_THROW_STAR:
	case SPL_HOMING_TANMAC:
	case SPL_ALLROUND_TANMAC:
		break;
	default:
		return;
	}
	monster* mon_ = GetTimeParadox();
	int cost_ = max(1,(SpellLevel(skill_)+1)/2);
	if(!mon_)
		return;
	int length_ = (int)ceil(GetPositionGap(mon_->position.x,mon_->position.y,target_.x,target_.y));
	if(GetLengthFromCenter(target_.x,target_.y,mon_->position.x,mon_->position.y) > SpellLength(skill_,false))
		return;
	if(skill_ == SPL_SPARK || skill_ == SPL_FIRE_SPREAD || skill_ == SPL_SHOCK)
	{
		if(!TimeParadoxSectorSafe(mon_,target_,skill_))
			return;
	}
	if(skill_ == SPL_CHAIN_LIGHTNING && !TimeParadoxChainSafe(mon_,target_))
		return;
	if(skill_ == SPL_COLD_BEAM)
		length_ = max(length_,12); // 냉기 구름은 짧은 발사와 별도로 8칸에 남는다.
	if(skill_ == SPL_THROW_BUCKET)
		length_ = SpellLength(skill_,false);
	beam_iterator beam_(mon_->position,target_);
	if(!TimeParadoxSafe(mon_,target_,length_,radius_,beam_))
		return;
	if(skill_ == SPL_HOMING_TANMAC)
	{
		unit* target_unit_ = env[current_level].isMonsterPos(target_.x,target_.y);
		if(!target_unit_ || !you.isEnemyUnit(target_unit_))
			return;
		int count_ = 0;
		for(monster& other_ : env[current_level].mon_vector)
			if(other_.isLive())
				count_++;
		if(count_ > MON_MAX_IN_FLOOR-2)
			return;
	}
	if(skill_ == SPL_ALLROUND_TANMAC)
	{
		for(monster& other_ : env[current_level].mon_vector)
		{
			int distance_ = (int)ceil(GetPositionGap(mon_->position.x,mon_->position.y,other_.position.x,other_.position.y));
			if(other_.isLive() && other_.isYourShight() && you.isEnemyUnit(&other_) &&
				GetLengthFromCenter(other_.position.x,other_.position.y,mon_->position.x,mon_->position.y) <= SpellLength(skill_,false))
			{
				beam_iterator other_beam_(mon_->position,other_.position);
				if(!TimeParadoxSafe(mon_,other_.position,distance_,0,other_beam_))
					return;
			}
		}
	}
	if(MonsterUseSpell(skill_,true,mon_,target_,power_/2))
		UseTimeParadox(mon_,cost_);
}
