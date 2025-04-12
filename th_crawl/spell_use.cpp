//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: spell_use.cpp
//
// 내용: 사용하는 스펠들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "unit.h"
#include "skill_use.h"
#include "throw.h"
#include "beam.h"
#include "monster.h"
#include "smoke.h"
#include "mon_infor.h"
#include "rect.h"
#include "player.h"
#include "monster_texture.h"
#include "weapon.h"
#include "environment.h"
#include "debuf.h"
#include "floor.h"
#include "alchemy.h"
#include "map.h"
#include "event.h"
#include "key.h"
#include "rand_shuffle.h"
#include "evoke.h"
#include "armour.h"
#include "tribe.h"
#include "soundmanager.h"
#include <algorithm>
#include <math.h>

extern HANDLE mutx;
extern int map_effect;

bool isMonsterhurtSpell(monster* use_, monster* target_, spell_list spell_)
{
	//이 마법이 이 몬스터에게 제대로 듣는지
	//true면 되도록 마법을 쓰는걸 피한다.
	//false면 무시하고 쏜다. (공격이 안 듣거나 자신에 비해서 너무 약하거나)
	boolean danger_ = false;
	if (use_->isUserAlly() && target_->isUserAlly()) {
		//만약 아군과 적이 모두 아군이면 사용을 안한다.
		//(릴리같은 경우 자살공격을 방지하기 위함)
		danger_ = true;
	}

	if(use_->level - target_->level >= 5 && !danger_)
		return false; //레벨차이가 심하게 난다. 신경쓰지않는다.

	bool resist_[RST_TYPE_MAX];

	for(int i = 0; i<RST_TYPE_MAX;i++)
		resist_[i] = false;

	for(int i = 0; i < 3;i++)
	{
		switch(SpellSchool(spell_,i))
		{				   
		case SKT_AIR:
			resist_[RST_ELEC] = true;
			break;
		case SKT_ALCHEMY:
			resist_[RST_POISON] = true;
			break;
		case SKT_COLD:
			resist_[RST_ICE] = true;
			break;
		case SKT_FIRE:
			resist_[RST_FIRE] = true;
			break;
		default:
			break;
		}
	} 
	
	//각 속성공격에 해당되는데 해당 저항이 없는 경우 위험한 공격임
	if(resist_[RST_POISON] && target_->poison_resist<=0)
		return true;
	if(resist_[RST_ELEC] && (target_->elec_resist<=(danger_ ?2:1)))
		return true;
	if(resist_[RST_FIRE] &&(target_->fire_resist<=(danger_?2:1)))
		return true;
	if(resist_[RST_ICE] && (target_->ice_resist<=(danger_ ?2:1)))
		return true;

	if(!resist_[RST_POISON] && !resist_[RST_ELEC] && !resist_[RST_FIRE] && !resist_[RST_ICE])
		return true; //무속성공격

	return false; 

}


bool isBandAlly(monster* order, monster* other)
{//예네들이 협력하는지(버프를 같이 받는지)
	//즉 order가 other에게 버프를 주느지 확인
	//나중엔 자리를 바꿀 수 있는지 등도 고려
	//현재는 버프만 적용이므로 버프쓰는 몹만 고려

	if(!order->isAllyMonster(other)) //애초에 아군이 아니면 버프를 주지 못함.
		return false;


	switch(order->id)
	{
	case MON_FAIRY_RED_COMMANDER:
	case MON_FAIRY_SUN_FLOWER:
	case MON_SUNNY:
	case MON_LUNAR:
	case MON_STAR:
	case MON_DIEFAIRY:
		if(other->flag & M_FLAG_FAIRY)
			return true;
		else
			return false;
		break;
	case MON_YAMAWARO_FLAG:
		switch(other->id)
		{
		case MON_YAMAWARO_WAWRRIOR:
		case MON_YAMAWARO_NINJA:
			return true;
		default:
			break;
		}
		return false;
	case MON_RABIT_SUPPORT:
		switch(other->id)
		{
		case MON_RABIT_MAGIC:
		case MON_RABIT_BOMB:
		case MON_RABIT_SPEAR:
			return true;
		default:
			break;
		}
		return false;
	case MON_SARIEL:
		switch(other->id)
		{
		case MON_SARA:
		case MON_LUIZE:
		case MON_ELIS:
			return true;
		default:
			break;
		}
		return false;
	case MON_MOON_RABIT_SUPPORT:
	case MON_RINGO:
		switch(other->id)
		{
		case MON_MOON_RABIT_ATTACK:
		case MON_MOON_RABIT_ELITE:
		case MON_SEIRAN:
			return true;
		default:
			break;
		}
		return false;
	case MON_SEIGA:
		if(other->id == MON_YOSIKA)
			return true;
		break;
	default:
		break;
	}
	return false;
}





bool isMonSafeSkill(spell_list skill, monster* order, coord_def &target)
{
	int length_ = pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2);
	if(order->position == target && !SpellFlagCheck(skill, S_FLAG_SEIF))
		return false;

	if (SpellLength(skill) == 1) {
		//사거리1은 특수 취급
		if (length_ > 2)
			return false;

	}
	else if(SpellLength(skill) && length_ > SpellLength(skill)*SpellLength(skill))
		return false;
	if(SpellFlagCheck(skill, S_FLAG_NO_COM))
		return false;
	else if(SpellFlagCheck(skill, S_FLAG_CLOSE_DANGER) && length_ <= 2)
		return false;
	if(SpellFlagCheck(skill, S_FLAG_CLOUD) && env[current_level].isSmokePos(target.x,target.y))
		return false;
	if(SpellFlagCheck(skill, S_FLAG_HEAL) && !SpellFlagCheck(skill, S_FLAG_OTHER_BUF) && order->hp >= order->max_hp)
		return false;
	if(!SpellAiCondition(skill, order))
		return false;
	
	

	if(SpellFlagCheck(skill, S_FLAG_SUMMON))
	{
		if(GetSummonMaxNumber(skill)>0 && order->map_id >=0)
		{
			int i= 0;
			for( auto it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && it->sm_info.parent_map_id == order->map_id && it->sm_info.summon_id == GetSummonKind(skill))
				{
					if (skill == SPL_SUMMON_TRASH) {
						if (order->isMonsterSight(it->position))
							i++;
					}
					else {
						i++;
					}
				}
			}
			if(i >= GetSummonMaxNumber(skill))
				return false;
		}
	}

	if(SpellFlagCheck(skill, S_FLAG_OTHER_BUF))
	{
		bool ok_ = false;
		for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if(&(*it) != order && it->isLive() && isBandAlly(order,&(*it)) && order->isMonsterSight(it->position) &&
				(!SpellFlagCheck(skill, S_FLAG_HEAL) || it->hp < it->max_hp))
			{
				beam_iterator beam(order->position,order->position);
				if(!CheckThrowPath(order->position,it->position, beam))
					continue;
				if(!SpellFlagCheck(skill, S_FLAG_SMITE) && !SpellFlagCheck(skill, S_FLAG_IMMEDIATELY))
				{		
					bool beam_ok_ = true;
					for(beam.init();!beam.end();beam++)
					{
						unit *temp = env[current_level].isMonsterPos((*beam).x,(*beam).y);
						if(temp)
						{
							if(temp->isLive() && temp != &(*it))
							{
								beam_ok_ = false;
								break;
							}
						}
					}	
					if(beam_ok_)
					{
						ok_ = true;		
						break;
					}
				}
				else 
				{
					ok_ = true;		
					break;					
				}
			}
		}
		if(!ok_)
			return false;
	}
	else if(!SpellFlagCheck(skill, S_FLAG_SMITE) && !SpellFlagCheck(skill, S_FLAG_IMMEDIATELY))
	{
		beam_iterator beam(order->position,order->position);
		
		if(!CheckThrowPath(order->position,target, beam))
			return false;
		int max_length_ = SpellFlagCheck(skill, S_FLAG_PENETRATE)?SpellLength(skill):beam.GetMaxLength();
		
		for(beam.init();max_length_>0/*!beam.end()*/;beam++)
		{
			if(!env[current_level].isMove((*beam),true,true))
				break;
			unit *temp = env[current_level].isMonsterPos((*beam).x,(*beam).y);
			if(temp)
			{			
				

				if(temp->isLive() && !temp->isEnemyMonster(order) && !temp->isPassedBullet(order))
				{
					if(!SpellFlagCheck(skill, S_FLAG_PENETRATE))
						return false;
					else if(temp->isplayer() || isMonsterhurtSpell(order,(monster*)temp,skill))
					{
						return false;
					}

				}
			}
			max_length_--;
		}
	}
	else if(SpellFlagCheck(skill, S_FLAG_SMITE) || SpellFlagCheck(skill, S_FLAG_IMMEDIATELY))
	{
		beam_iterator beam(order->position,order->position);
		if(!CheckThrowPath(order->position,target, beam))
			return false;
	}
	
	if(Spellsize(skill))
	{
		int size_ = Spellsize(skill);
		rect_iterator rit(target,size_,size_);

		while(!rit.end())
		{

			unit *temp = env[current_level].isMonsterPos((*rit).x, (*rit).y, order);
			if(temp)
			{	
				if(temp->isLive() && !temp->isEnemyMonster(order) /*&& !temp->isPassedBullet(order)*/)
				{
					if(temp->isplayer() || isMonsterhurtSpell(order,(monster*)temp,skill))
					{
						return false;
					}

				}
			}
			rit++;
		}
		
	}

	return true;
}


void BaseBomb(coord_def pos, textures* t_ , attack_infor& att_, unit* except_)
{
	{
		for(int i=-1;i<=1;i++)
			for(int j=-1;j<=1;j++)
				if(env[current_level].isMove(pos.x+i,pos.y+j,true))
					env[current_level].MakeEffect(coord_def(pos.x+i,pos.y+j),t_,false);
		for(int i=-1;i<=1;i++)
		{
			for(int j=-1;j<=1;j++)
			{				
				if(env[current_level].isMove(pos.x+i,pos.y+j,true))
				{
					if(unit* hit_ = env[current_level].isMonsterPos(pos.x+i,pos.y+j))
					{		
						if(except_ != hit_)
							hit_->damage(att_, true);
					}
				}
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
	}
}


monster* BaseSummon(int id_, int time_, bool targeting_, bool random_, int range_, unit* order, coord_def target, SUMMON_KIND kind_, int max_num_)
{
	monster* mon_= NULL;
	dif_rect_iterator rit(target,range_,random_);
	//rand_rect_iterator rit(target,range_,range_);
	while(!rit.end())
	{
		if(summon_check(coord_def(rit->x,rit->y), target, mondata[id_].flag & M_FLAG_FLY, mondata[id_].flag & M_FLAG_SWIM))
		{
			int flag_=M_FLAG_SUMMON;
			if(order)
			{
				if(order->GetParentType() == PRT_PLAYER || order->GetParentType() == PRT_ALLY)
				{
					flag_ |= M_FLAG_ALLY;
				}
			}

			summon_info s_(order?order->GetMapId():-1,kind_,max_num_);
			mon_=env[current_level].AddMonster_Summon(id_,flag_,(*rit),s_,time_); //파워에 따라서 조정하기

			if(order && !order->isplayer())
			{
				mon_->SetNeutrality(((monster*)order)->s_neutrality);
			}
			//unit* unit_ = env[current_level].isMonsterPos(target.x,target.y,order);
			if(mon_ && targeting_){
				if(env[current_level].isInSight((*rit)))
					mon_->CheckSightNewTarget();
			}
			break;
		}
		rit++;
	}
	return mon_;
}

bool skill_tanmac_small(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if (CheckThrowPath(order->position, target, beam))
	{
		beam_infor temp_infor(randA_1(2 + pow / 3), 2 + pow / 3, 17, order, order->GetParentType(), SpellLength(SPL_MON_TANMAC_SMALL), 1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_TANMAC));
		if (short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if(env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(rand_int(30, 35), beam, temp_infor, NULL);
		}
		order->SetParadox(0);	
		return true;
	}
	return false;
}

bool skill_tanmac_middle(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(2,12+pow/8),2*(12+pow/8),14,order,order->GetParentType(),SpellLength(SPL_MON_TANMAC_MIDDLE),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_TANMAC));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));


		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(rand_int(10, 15), beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_water_gun(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(1,15+pow/4),15+pow/4,12,order,order->GetParentType(),SpellLength(SPL_MON_WATER_GUN),1,BMT_NORMAL,ATT_THROW_WATER,name_infor(LOC_SYSTEM_ATT_WATERGUN));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(34, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_burn(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(1,13+pow/6),13+pow/6,13,order,order->GetParentType(),SpellLength(SPL_BURN),1,BMT_NORMAL,ATT_THROW_FIRE,name_infor(LOC_SYSTEM_ATT_BURN));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("fire");
			}
			throwtanmac(17, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_flame(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		int mon_panlty_ = order->isplayer()?0:4;//몬스터가 쓸때 패널티
		int damage_ = 15+pow/6-mon_panlty_;
		beam_infor temp_infor(randC(1,damage_),damage_,15+pow/15,order,order->GetParentType(),SpellLength(SPL_FLAME),1,BMT_NORMAL,ATT_THROW_FIRE,name_infor(LOC_SYSTEM_ATT_BURN));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("fire");
			}
			throwtanmac(17, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_frozen(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(1,9+pow/6),9+pow/6,99,order,order->GetParentType(),SpellLength(SPL_FROZEN),1,BMT_NORMAL,ATT_THROW_COLD,name_infor(LOC_SYSTEM_ATT_COLD));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("cold");
			}
			throwtanmac(19, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_frost(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		int mon_panlty_ = order->isplayer()?0:4;//몬스터가 쓸때 패널티
		int damage_ = 14+pow/5-mon_panlty_;
		beam_infor temp_infor(randC(1,damage_),damage_,14+pow/15,order,order->GetParentType(),SpellLength(SPL_FROST),1,BMT_NORMAL,ATT_THROW_COLD,name_infor(LOC_SYSTEM_ATT_COLD));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("cold");
			}
			throwtanmac(19, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_freeze(int pow, bool short_, unit* order, coord_def target)
{
	//beam_iterator beam(order->position,order->position);
	//if(CheckThrowPath(order->position,target,beam))
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);
	
	if(target_unit)
	{	
		attack_infor temp_att(randC(2,13+pow/6),2*(13+pow/6),99,order,order->GetParentType(),ATT_THROW_FREEZING,name_infor(LOC_SYSTEM_ATT_COLD));
		target_unit->damage(temp_att, true);
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("cold");
		}
		//beam_infor temp_infor(randC(2,8+pow/6),2*(8+pow/6),99,order,order->GetParentType(),SpellLength(SPL_FREEZE),1,BMT_NORMAL,ATT_THROW_FREEZING,name_infor(LOC_SYSTEM_ATT_COLD));
		//if(short_)
		//	temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		//throwtanmac(19,beam,temp_infor,NULL);
		return true;
	}
	return false;
}
bool skill_sting(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(1,6+pow/6),6+pow/6,14+pow/15,order,order->GetParentType(),SpellLength(SPL_STING),1,BMT_NORMAL,ATT_THROW_WEAK_POISON,name_infor(LOC_SYSTEM_ATT_POISONTANMAC));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(20, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_medicine_cloud(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		MakeCloud(target, img_fog_slow, SMT_SLOW, rand_int(8,10), 4+pow/10,0,5, order);
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("wind");
		}
		return true;
	}
	return false;
}
bool skill_fire_wall(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		if(env[current_level].isMonsterPos(target.x,target.y))
		{
			if(order->isplayer())
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_EXIST_POS),true,false,false,CL_small_danger);
			return false;
		}
		if(env[current_level].isSmokePos(target.x,target.y))
		{
			if(order->isplayer())
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_EXIST_SMOKE),true,false,false,CL_small_danger);
			return false;
		}
		env[current_level].MakeSmoke(target, img_fog_fire, SMT_FIRE, rand_int(7,13)+pow/4,  0, order);

		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("fire");

		}
		return true;
	}
	return false;
}
bool skill_twist(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		if(env[current_level].isSmokePos(target.x,target.y))
		{
			if(order->isplayer())
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_EXIST_SMOKE),true,false,false,CL_small_danger);
			return false;
		}
		env[current_level].MakeSmoke(target, img_fog_tonado, SMT_TWIST, rand_int(3,8)+pow/5,  0, order);

		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("wind");
		}
		return true;
	}
	return false;
}
bool skill_cold_beam(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(3,5+pow/9),3*(5+pow/9),18,order,order->GetParentType(),SpellLength(SPL_COLD_BEAM),8,BMT_PENETRATE,ATT_THROW_COLD,name_infor(LOC_SYSTEM_ATT_COLDBEAM));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("cold");
			}
			throwtanmac(18, beam, temp_infor, NULL); //얼음탄막 모양 하나 더 만들고 바꾸기
		}
		order->SetParadox(0); 
		beam.init();
		int length = 8;
		while(env[current_level].isMove(*(beam),true) && length>0)
		{
			if(!randA(2))
			{
				env[current_level].MakeSmoke((*beam),img_fog_cold,SMT_COLD,rand_int(2,3),0,order);
			}
			length--;
			beam++;
		}
		return true;
	}
	return false;
}

bool skill_summon_bug(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;

	for(int i = randA(1)+1; i>0 ; i--)
	{
		if(BaseSummon((!randA(3)?MON_SPIDER:(randA(1)?MON_FIREFLY:MON_BUTTERFLY)), rand_int(30,60), true, false, 2, order, target, SKD_SUMMON_BUG, GetSummonMaxNumber(SPL_SUMMON_BUG)))
			return_ = true;
	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}

bool skill_confuse(int pow, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = DebufBeam(SPL_CONFUSE, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_CONFUSE,pow)))
		{
			hit_mon->SetConfuse(rand_int(10,20)+randA(pow/10));
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}

bool skill_slow(int pow, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = DebufBeam(SPL_SLOW, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_SLOW,pow)))
		{
			hit_mon->SetSlow(rand_int(15,30)+randA(pow/8));
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}


bool skill_self_heal(int pow, bool short_, unit* order, coord_def target)
{
	order->HpUpDown(rand_int(2+pow/10,10+pow/5),DR_NONE);
	return true;
}

bool skill_blink(int pow, bool short_, unit* order, coord_def target)
{
	if(!order->Tele_check(true, false))
		return false; 
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("blink");
	}
	order->Blink(25);

	return true;
}
bool skill_cure_poison(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		players* player_pointer = (players*)order;
		if(player_pointer->s_poison)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CURE_POISON),true,false,false,CL_normal);
			player_pointer->s_poison = 0;
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_SHOULD_POISON),true,false,false,CL_small_danger);
			return false;
		}
	}
	return true;
}

bool skill_smite(int pow, bool short_, unit* order, coord_def target)
{	
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);
	
	if(target_unit)
	{
		attack_infor temp_att(randA_1(11+pow/7),11+pow/7,99,order,order->GetParentType(),ATT_SMITE,name_infor(LOC_SYSTEM_ATT_SMITE));
		
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("smite");
		}
		target_unit->damage(temp_att, true);
		return true;
	}
	return false;
}
bool skill_summon_mook(int pow, bool short_, unit* order, coord_def target)
{	
	bool return_=false;

	for(int i = 1; i>0 ; i--)
	{
		if(BaseSummon(MON_MOOK, rand_int(30,60), true, false, 2, order, target, SKD_SUMMON_MOOK, GetSummonMaxNumber(SPL_SUMMON_MOOK)))
			return_ = true;
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;

}
bool skill_fire_bread(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_FIRE_BRAND,true,false,false,CL_white_blue,
				 PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
			you.equipment[ET_WEAPON]->value5 = WB_FIRE;
			you.equipment[ET_WEAPON]->value6 = rand_int(10,20)+pow/3; 
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("fire");
			}
		}
		else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_FIRE && you.equipment[ET_WEAPON]->value6>0)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_FIRE_BRAND_MORE,true,false,false,CL_white_blue,
				 PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
			you.equipment[ET_WEAPON]->value6 += rand_int(8,12)+pow/5;
			if(you.equipment[ET_WEAPON]->value6>50)
				you.equipment[ET_WEAPON]->value6 = 50; 
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("fire");
			}
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CANT_BRAND),true,false,false,CL_normal);
		}
	}
	return true;
}
bool skill_cold_bread(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_COLD_BRAND,true,false,false,CL_white_blue,
				 PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
			you.equipment[ET_WEAPON]->value5 = WB_COLD;
			you.equipment[ET_WEAPON]->value6 = rand_int(10,20)+pow/3; 
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("cold");
			}
		}
		else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_COLD && you.equipment[ET_WEAPON]->value6>0)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_COLD_BRAND_MORE,true,false,false,CL_white_blue,
				 PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
			you.equipment[ET_WEAPON]->value6 += rand_int(8,12)+pow/5;
			if(you.equipment[ET_WEAPON]->value6>50)
				you.equipment[ET_WEAPON]->value6 = 50; 
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("cold");
			}
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CANT_BRAND),true,false,false,CL_normal);
		}
	}
	return true;
}

bool skill_poison_bread(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_POISON_BRAND,true,false,false,CL_white_blue,
				 PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
			you.equipment[ET_WEAPON]->value5 = WB_POISON;
			you.equipment[ET_WEAPON]->value6 = rand_int(10,20)+pow/3; 
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("fire");
			}
		}
		else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_POISON && you.equipment[ET_WEAPON]->value6>0)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_POISON_BRAND_MORE,true,false,false,CL_white_blue,
				 PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
			you.equipment[ET_WEAPON]->value6 += rand_int(8,12)+pow/5;
			if(you.equipment[ET_WEAPON]->value6>50)
				you.equipment[ET_WEAPON]->value6 = 50; 
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("fire");
			}
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CANT_BRAND),true,false,false,CL_normal);
		}
	}
	return true;
}

bool skill_elec(int power, bool short_, unit* order, coord_def target)
{
	unit *hit_mon=NULL;
	int conduct=9999;
	int direc = GetPosToDirec(order->position, target);
	for(vector<monster>::iterator it=env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{

		if((*it).isLive() && (*it).elec_resist <= 2)
		{
			int length_ = pow((float)abs(order->position.x-it->position.x),2)+pow((float)abs(order->position.y-it->position.y),2);
			if(!length_ || length_ > SpellLength(SPL_SHOCK)*SpellLength(SPL_SHOCK)) //만약 거리를 벗어날경우 실패한다.
				continue;
			beam_iterator beam(order->position,order->position);
			if(!CheckThrowPath(order->position,it->position, beam))//경로가 제대로 안 세워질경우 실패
				continue;
			int direc2 = GetPosToDirec(order->position, it->position);
			direc2 = min((direc-direc2+8)%8,(direc2-direc+8)%8);
			if(direc2>=2)
				continue;
			int temp = (sqrt((float)length_)*10.0f-direc2*5+rand_int(-10,10))*(2.0f-it->GetElecResist());
			if(conduct>temp || (temp==conduct && randA(1)))
			{
				hit_mon = &(*it);
				conduct = temp;
			}
		}
	}
	while(1) //루프안됨
	{
		int length_ = pow((float)abs(order->position.x-you.position.x),2)+pow((float)abs(order->position.y-you.position.y),2);
		if(!length_ || length_ > SpellLength(SPL_SHOCK)*SpellLength(SPL_SHOCK)) //만약 거리를 벗어날경우 실패한다.
			break;
		beam_iterator beam(order->position,order->position);
		if(!CheckThrowPath(order->position,you.position, beam))//경로가 제대로 안 세워질경우 실패
			break;
		int direc2 = GetPosToDirec(order->position, you.position);
		direc2 = min((direc-direc2+8)%8,(direc2-direc+8)%8);
		if(direc2>=2)
			break;
		int temp = (sqrt((float)length_)*10.0f-direc2*5+rand_int(-10,10))*(2.0f-you.GetElecResist());
		if(conduct>temp || (temp==conduct && randA(1)))
		{
			hit_mon = &you;
			conduct = temp;
		}
		break;
	}

	if(hit_mon)
	{
		
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("elec");
		}
		beam_infor temp_infor(randA_1(10+power/6),10+power/6,99,order,order->GetParentType(),SpellLength(SPL_SHOCK),1,BMT_NORMAL,ATT_THROW_ELEC,name_infor(LOC_SYSTEM_ATT_ELECTRIC));
		ThrowShock(21,order->position,hit_mon->position,temp_infor); 
		Sleep(120);
		env[current_level].ClearEffect(); 
		return true;
	}
	else
	{
		if(order->isplayer())
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ELEC_FAIL),true,false,false,CL_normal);
		return false;
	}
	return true;
}


bool skill_elec_passive(int power, unit* order)
{
	unit *hit_mon=NULL;
	int conduct=9999;
	int spell_length_ = SpellLength(SPL_CHAIN_LIGHTNING)/2;
	for(vector<monster>::iterator it=env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{

		if((*it).isLive() && (*it).elec_resist <= 2)
		{
			int length_ = pow((float)abs(order->position.x-it->position.x),2)+pow((float)abs(order->position.y-it->position.y),2);
			if(!length_ || length_ >spell_length_*spell_length_) //만약 거리를 벗어날경우 실패한다.
				continue;
			beam_iterator beam(order->position,order->position);
			if(!CheckThrowPath(order->position,it->position, beam))//경로가 제대로 안 세워질경우 실패
				continue;
			int temp = (sqrt((float)length_)*10.0f+rand_int(-10,10))*(2.0f-it->GetElecResist());
			if(conduct>temp || (temp==conduct && randA(1)))
			{
				hit_mon = &(*it);
				conduct = temp;
			}
		}
	}
	while(1) //루프안됨
	{
		int length_ = pow((float)abs(order->position.x-you.position.x),2)+pow((float)abs(order->position.y-you.position.y),2);
		if(!length_ || length_ > spell_length_*spell_length_) //만약 거리를 벗어날경우 실패한다.
			break;
		beam_iterator beam(order->position,order->position);
		if(!CheckThrowPath(order->position,you.position, beam))//경로가 제대로 안 세워질경우 실패
			break;
		int temp = (sqrt((float)length_)*10.0f+rand_int(-10,10))*(2.0f-you.GetElecResist());
		if(conduct>temp || (temp==conduct && randA(1)))
		{
			hit_mon = &you;
			conduct = temp;
		}
		break;
	}


	if(hit_mon)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("elec");
		}
		beam_infor temp_infor(randA_1(9+power/3),9+power/3,99,order,order->GetParentType(),spell_length_,1,BMT_NORMAL,ATT_THROW_ELEC,name_infor(LOC_SYSTEM_ATT_ELECTRIC));
		ThrowShock(21,order->position,hit_mon->position,temp_infor); 
		Sleep(120);
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}


bool skill_elec_ball_bomb(int power, unit* order)
{
	unit *hit_mon = NULL;
	int conduct = 9999;
	int spell_length_ = 6;
	for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if ((*it).isLive() && order->isEnemyMonster(&(*it)))
		{
			int length_ = pow((float)abs(order->position.x - it->position.x), 2) + pow((float)abs(order->position.y - it->position.y), 2);
			if (!length_ || length_ >spell_length_*spell_length_) //만약 거리를 벗어날경우 실패한다.
				continue;
			beam_iterator beam(order->position, order->position);
			if (!CheckThrowPath(order->position, it->position, beam))//경로가 제대로 안 세워질경우 실패
				continue;
			int temp = (sqrt((float)length_)*10.0f + rand_int(-10, 10))*(2.0f - it->GetElecResist());
			if (conduct>temp || (temp == conduct && randA(1)))
			{
				hit_mon = &(*it);
				conduct = temp;
			}
		}
	}
	while (1) //루프안됨
	{
		if (order->isUserAlly())
			break;
		int length_ = pow((float)abs(order->position.x - you.position.x), 2) + pow((float)abs(order->position.y - you.position.y), 2);
		if (!length_ || length_ > spell_length_*spell_length_) //만약 거리를 벗어날경우 실패한다.
			break;
		beam_iterator beam(order->position, order->position);
		if (!CheckThrowPath(order->position, you.position, beam))//경로가 제대로 안 세워질경우 실패
			break;
		int temp = (sqrt((float)length_)*10.0f + rand_int(-10, 10))*(2.0f - you.GetElecResist());
		if (conduct>temp || (temp == conduct && randA(1)))
		{
			hit_mon = &you;
			conduct = temp;
		}
		break;
	}


	if (hit_mon)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("elec");
		}
		beam_infor temp_infor(randC(3, 8 + power * 1 / 6), 3 * (8 + power * 1 / 6), 99, order, order->GetParentType(), spell_length_, 1, BMT_NORMAL, ATT_THROW_ELEC, name_infor(LOC_SYSTEM_ATT_ELECTRIC));
		ThrowShock(42, order->position, hit_mon->position, temp_infor);
		Sleep(120);
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}



bool skill_lightning(int power, unit* order, coord_def *start, int& direc, int count)
{
	unit *hit_mon=NULL;
	int conduct=9999, next_direc= direc;
	int spell_length_ = SpellLength(SPL_CHAIN_LIGHTNING)*(count?0.5f:1);
	for(vector<monster>::iterator it=env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{

		if((*it).isLive() && (*it).elec_resist <= 2)
		{
			int length_ = pow((float)abs((*start).x-it->position.x),2)+pow((float)abs((*start).y-it->position.y),2);
			if(!length_ || length_ > spell_length_*spell_length_) //만약 거리를 벗어날경우 실패한다.
				continue;
			beam_iterator beam((*start),order->position);
			if(!CheckThrowPath((*start),it->position, beam))//경로가 제대로 안 세워질경우 실패
				continue;
			int direc2 = GetPosToDirec((*start), it->position);
			int direc3 = min((direc-direc2+8)%8,(direc2-direc+8)%8);
			if(direc3>=3)
				continue;
			int temp = (sqrt((float)length_)*10.0f-direc3*5+rand_int(-10,10))*(2.0f-it->GetElecResist());
			if(conduct>temp || (temp==conduct && randA(1)))
			{
				hit_mon = &(*it);
				conduct = temp;
				next_direc = direc2;
			}
		}
	}
	while(1) //루프안됨
	{
		int length_ = pow((float)abs(start->x-you.position.x),2)+pow((float)abs(start->y-you.position.y),2);
		if(!length_ || length_ > spell_length_*spell_length_) //만약 거리를 벗어날경우 실패한다.
			break;
		beam_iterator beam(*start,*start);
		if(!CheckThrowPath(*start,you.position, beam))//경로가 제대로 안 세워질경우 실패
			break;
		int direc2 = GetPosToDirec(*start, you.position);
		direc2 = min((direc-direc2+8)%8,(direc2-direc+8)%8);
		if(direc2>=2)
			break;
		int temp = (sqrt((float)length_)*10.0f-direc2*5+rand_int(-10,10))*(2.0f-you.GetElecResist());
		if(order != &you && (conduct>temp || (temp==conduct && randA(1))))
		{
			hit_mon = &you;
			conduct = temp;
		}
		break;
	}


	if(hit_mon)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("elec");
		}
		beam_infor temp_infor(randC(2,8+power*1/4),2*(8+power*1/4),99,order,order->GetParentType(),spell_length_,1,BMT_NORMAL,ATT_THROW_ELEC,name_infor(LOC_SYSTEM_ATT_ELECTRIC));
		if(ThrowShock(42,(*start),hit_mon->position,temp_infor))
		{
			(*start) = hit_mon->position;
			direc = next_direc;
			return true;
		}
	}
	else
	{
	}
	return true;
}
bool skill_chain_lightning(int power, bool short_, unit* order, coord_def target)
{
	bool hit_ = false;
	int chain = rand_int(3,6);
	int count = 0;
	int direc = GetPosToDirec(order->position, target);
	coord_def cur = order->position;
	while(chain)
	{
		if(!skill_lightning(power, order, &cur, direc,count++))
		{
			break;
		}
		power =  power*9/10;
		hit_ = true;
		if(chain--<1)
			break;
	}
	Sleep(120);
	env[current_level].ClearEffect();
	return hit_;

}

bool base_bomb(int damage, int max_damage, int size, attack_type type, unit* order, name_infor bomb_name, coord_def target)
{
	//target을 중심으로 터지도록 바꿈..
	textures* image_ = &img_blast[0];
	switch(type)
	{
	case ATT_FIRE_BLAST:
	case ATT_BURST:
	case ATT_FIRE_PYSICAL_BLAST:
	case ATT_SUN_BLAST:
		image_ = &img_blast[0];
		break;
	case ATT_COLD_BLAST:
	case ATT_COLD_PYSICAL_BLAST:
		image_ = &img_blast[4];
		break;		
	case ATT_NORMAL_BLAST:		
	case ATT_AC_REDUCE_BLAST:
	case ATT_ELEC_BLAST:
		image_ = &img_blast[2];
		break;
	case ATT_POISON_BLAST:
		image_ = &img_blast[3];
		break;
	default:
		break;
	}
	int ball_size = size*size;
	if(size == 1)
		ball_size += 1;
	if(size == 3)
		ball_size -= size;
	if(size == 4)
		ball_size -= 2*size;
	for(int i=-1*size;i<=size;i++)
		for(int j=-1*size;j<=size;j++)
			if(abs(i)*abs(j)<ball_size && env[current_level].isMove(target.x+i,target.y+j,true))
				env[current_level].MakeEffect(coord_def(target.x+i,target.y+j),image_,false);
	for(int i=-1*size;i<=size;i++)
	{
		for(int j=-1*size;j<=size;j++)
		{				
			if(abs(i)*abs(j)<ball_size && (!order->isplayer() || env[current_level].isInSight(target+i)) && env[current_level].isMove(target.x+i,target.y+j,true))
			{
				if(unit* hit_ = env[current_level].isMonsterPos(target.x+i,target.y+j))
				{	
					
					if(hit_ != order)
					{
						attack_infor temp_att(damage,max_damage,99,order,order->GetParentType(),type,bomb_name);
						hit_->damage(temp_att,true);
					}
				}
			}
		}
	}
	Sleep(300);
	env[current_level].ClearEffect();

	return false;
}

bool skill_discharge(int pow, bool short_, unit* order, coord_def target)
{
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("elec");
	}
	order->SetElec(15+pow/5);
	return true;
}

bool skill_levitation(int pow, bool short_, unit* order, coord_def target)
{
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("wind");
	}
	order->SetLevitation(rand_int(30,50)+pow/2);
	return true;
}
bool skill_glow(int pow, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = DebufBeam(SPL_GLOW, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_GLOW,pow)))
		{
			hit_mon->SetGlow(rand_int(15,30)+randA(pow/8));
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}

bool skill_graze(int pow, bool short_, unit* order, coord_def target)
{
	order->SetGraze(rand_int(30,50)+pow/2);
	return true;
}

bool skill_veiling(int pow, bool short_, unit* order, coord_def target)
{
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("wind");
	}
	order->SetVeiling(10+pow/7,12+pow/4);
	return true;
}

bool skill_invisible(int pow, bool short_, unit* order, coord_def target)
{
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("spellcard");
	}
	order->SetInvisible(rand_int(30,80));
	return true;
}

bool skill_haste(int pow, bool short_, unit* order, coord_def target)
{
	if(order == &you)
	{
		you.SetAlchemyBuff(ALCT_HASTE,rand_int(30,50)+pow/4);
	}
	else
		order->SetHaste(rand_int(30,80));
	return true;
}
bool skill_silence(int pow, bool short_, unit* order, coord_def target)
{
	order->SetSilence(rand_int(20,30)+pow/10,(4+pow/50)*2);
	return true;
}
bool skill_santuary(int pow, bool short_, unit* order, coord_def target)
{
	if (order && order->GetExhausted())
		return false;
	if (env[current_level].isInSight(target)) {
		soundmanager.playSound("spellcard");
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_SANTUARY), true, false, false, CL_warning);
	}
	env[current_level].MakeEvent(EVL_SANTUARY, coord_def(target.x, target.y), EVT_ALWAYS, rand_int(10, 20));

	if (order && !order->isplayer())
	{
		order->SetExhausted(rand_int(20, 35));
	}
	return true;
}
bool skill_swift(int pow, bool short_, unit* order, coord_def target)
{
	order->SetSwift(rand_int(30,50)+pow/2);
	return true;
}
bool skill_magic_tanmac(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		int mon_panlty_ = order->isplayer()?0:1;//몬스터가 쓸때 패널티
		int damage_ = 6+pow/3-mon_panlty_;
		beam_infor temp_infor(randA_1(damage_),damage_,99,order,order->GetParentType(),SpellLength(SPL_MAGIC_TANMAC),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_TANMAC));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));		
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(rand_int(30, 35), beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_fire_ball(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	int length_ = ceil(sqrt(pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2)));
	length_ = min(length_,SpellLength(SPL_FIRE_BALL));
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(0,0,15,order,order->GetParentType(),length_,1,BMT_NORMAL,ATT_THROW_NONE_MASSAGE,name_infor(LOC_SYSTEM_ATT_FIREBALL));

		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{
			coord_def pos = throwtanmac(16,beam,temp_infor,NULL);
			attack_infor temp_att(randC(3,7+power/12),3*(7+power/12),99,order,order->GetParentType(),ATT_FIRE_BLAST,name_infor(LOC_SYSTEM_ATT_FIREBALL));
			
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("bomb");
			}
			BaseBomb(pos, &img_blast[0],temp_att);
		}
		order->SetParadox(0); 
		return true;
	}
	return false;
}
bool skill_fire_bolt(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		int mon_panlty_ = order->isplayer()?0:2;//몬스터가 쓸때 패널티
		int damage_ = 9+pow/6-mon_panlty_;
		beam_infor temp_infor(randC(3,damage_),3*(damage_),18+pow/25,order,order->GetParentType(),SpellLength(SPL_FIRE_BOLT),8,BMT_PENETRATE,ATT_THROW_FIRE,name_infor(LOC_SYSTEM_ATT_FIRE));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("fire");
			}
			throwtanmac(16, beam, temp_infor, NULL);
		}
		order->SetParadox(0); 
		return true;
	}
	return false;
}
bool skill_ice_bolt(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		int mon_panlty_ = order->isplayer()?0:2;//몬스터가 쓸때 패널티
		int damage_ = 9+pow/6-mon_panlty_;
		beam_infor temp_infor(randC(3,damage_),3*(damage_),18+pow/25,order,order->GetParentType(),SpellLength(SPL_ICE_BOLT),8,BMT_PENETRATE,ATT_THROW_COLD,name_infor(LOC_SYSTEM_ATT_COLD));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("cold");
			}
			throwtanmac(22, beam, temp_infor, NULL);
		}
		order->SetParadox(0); 
		return true;
	}
	return false;
}
bool skill_venom_bolt(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(3,6+pow/6),3*(6+pow/6),19,order,order->GetParentType(),SpellLength(SPL_VENOM_BOLT),8,BMT_PENETRATE,ATT_THROW_MIDDLE_POISON,name_infor(LOC_SYSTEM_ATT_VENOM));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(23, beam, temp_infor, NULL);
		}
		order->SetParadox(0); 
		return true;
	}
	return false;
}
bool skill_confuse_cloud(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	int length_ = ceil(sqrt(pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2)));
	length_ = min(length_,SpellLength(SPL_CONFUSE_CLOUD));
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(0,0,10,order,order->GetParentType(),length_,1,BMT_PENETRATE,ATT_THROW_NONE_MASSAGE,name_infor(LOC_SYSTEM_ATT_CONFUSE_POISON));
		
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			
			coord_def pos = throwtanmac(20,beam,temp_infor,NULL, false);
			{
				for(int k=-1;k<=1;k++)
					for(int j=-1;j<=1;j++)
						if(env[current_level].isMove(pos.x+k,pos.y+j,true))
							env[current_level].MakeEffect(coord_def(pos.x+k,pos.y+j),&img_fog_poison[0],false);
				for(int k=-1;k<=1;k++)
					for(int j=-1;j<=1;j++)
							env[current_level].MakeSmoke(coord_def(pos.x+k,pos.y+j),img_fog_poison,SMT_CONFUSE,rand_int(6,12)+randA(power/15),0,order);

				Sleep(300);
				env[current_level].ClearEffect();

			}
		}
		order->SetParadox(0); 
		
		
		return true;
	}
	return false;
}
bool skill_poison_cloud(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("wind");
		}
		MakeCloud(target, img_fog_poison, SMT_POISON, rand_int(8,10), rand_int(7,10)+randA(pow/10),0,5, order);
		return true;
	}
	return false;
}
bool skill_ice_cloud(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("cold");
		}
		MakeCloud(target, img_fog_cold, SMT_COLD, rand_int(8,10), rand_int(7,10)+randA(pow/10),0,5, order);
		return true;
	}
	return false;
}
bool skill_summon_bird(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	dif_rect_iterator rit(order->position,2);
	int id_ = MON_CROW;
	int time_ = rand_int(20,30)+randA(pow);

	int pow_ = pow/3+randA(pow*2/3);
	int i = 2;

	if(pow_<=20)//까마귀
	{
		//i=(randA_1(20) < pow?3:2);
	}
	else if(pow_<=50)//나중에 까마귀에서 바꾸자
	{
		id_ = MON_CRANE;
		i=1;
	}
	else 
	{
		id_ = MON_EAGLE;
		i=1;
	}

	for(; i>0 ; i--)
	{
		if(BaseSummon(id_, time_, true, false, 2, order, target, SKD_SUMMON_BIRD, GetSummonMaxNumber(SPL_SUMMON_BIRD)))
			return_ = true;
	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}

bool skill_recall(int pow, bool short_, unit* order, coord_def target)
{
	deque<monster*> dq;
	for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
	{
		if(it->isLive() && it->isUserAlly())
		{
			dq.push_back(&(*it));
		}
	}
	rand_shuffle(dq.begin(),dq.end());
	dif_rect_iterator rit(order->position,2);
	int j=0;
	for(int i = 0;!rit.end() && i < dq.size();rit++)
	{
		if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
		{
			dq[i]->SetXY(rit->x,rit->y);
			if(dq[i]->isYourShight())
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RECALL,false,false,false,CL_normal,
					 PlaceHolderHelper(dq[i]->GetName()->getName()));
				j++;
				if(j%3==0)
					enterlog();
			}
			i++;
		}
	}
	return true;
}

bool skill_teleport_other(int pow, bool short_, unit* order, coord_def target)
{
	if(isArena())
		return false;
	if(unit* hit_mon = DebufBeam(SPL_TELEPORT_OTHER, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_TELEPORT_OTHER,pow)))
		{
			hit_mon->SetTele(rand_int(3,6));
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}

bool skill_teleport_self(int pow, bool short_, unit* order, coord_def target)
{
	if(isArena())
		return false;
	if(!order->Tele_check(true, false))
		return false;
	order->SetTele(rand_int(3,6));
	return true;
}


bool skill_whirlwind(int pow, bool short_, unit* order, coord_def target)
{

	if(env[current_level].isMove(target.x, target.y, true))
	{
		
		if (env[current_level].isInSight(target)) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("wind");
			}
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_WHIRLWIND) + " ", false, false, false, CL_normal);
		}
		{
			dif_rect_iterator rit(target,1);
		
			for(;!rit.end();rit++)
			{
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if((!order->isplayer() || env[current_level].isInSight(*rit)) && order->isSightnonblocked(*rit))
					{
						for(list<smoke>::iterator it = env[current_level].smoke_list.begin();it != env[current_level].smoke_list.end() ;it++)
						{
							if(it->position.x == rit->x && it->position.y == rit->y)
							{
								WaitForSingleObject(mutx, INFINITE);
								it->clear();
								env[current_level].smoke_list.erase(it);
								ReleaseMutex(mutx);
								break;
							}
						}
						//if(unit* hit_ = env[current_level].isMonsterPos(rit->x,rit->y))
						//{	
						//	if(hit_ != order)
						//	{
						//		int att_ = randC(9,10+power/20);
						//		int m_att_ = 9*(10+power/20);

						//		attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_FIRE_PYSICAL_BLAST,name_infor(LOC_SYSTEM_ATT_FIRESTORM));
						//		hit_->damage(temp_att, true);
						//	}
						//}
						env[current_level].MakeSmoke((*rit), img_fog_tonado, SMT_WHIRLWIND, 3+pow/20,  0, order);
					}
				}
			}
		}
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}


bool skill_summon_pendulum(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;

	for(int i = 1; i>0 ; i--)
	{
		if(BaseSummon(MON_DAUZING, rand_int(30,60), true, false, 2, order, target, SKD_SUMMON_PENDULUM, GetSummonMaxNumber(SPL_SUMMON_PENDULUM)))
		{
			order->SetSaved(true);
			return_ = true;
		}
	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("cold");
		}
	}
	return return_;
}
bool skill_summon_sekibanki(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	
	int i = pow==200?4:1; 
	for(; i>0 ; i--)
	{
		if(BaseSummon(MON_SEKIBANKI_HEAD, rand_int(90,120), true, true, 2, order, target, SKD_SUMMON_SEKIBANKI, GetSummonMaxNumber(SPL_SUMMON_SEKIBANKI)))
		{
			return_ = true;
		}
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("laugh");
		}
	}
	return return_;

}
bool skill_water_cannon(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(3,5+pow/6),3*(5+pow/6),18,order,order->GetParentType(),SpellLength(SPL_WATER_CANNON),1,BMT_NORMAL,ATT_THROW_WATER,name_infor(LOC_SYSTEM_ATT_WATERPRESSURE));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot_heavy");
			}
			coord_def temp = throwtanmac(22,beam,temp_infor,NULL);
			unit* unit_ = env[current_level].isMonsterPos(temp.x,temp.y,order);		
			if(unit_)
			{
				int knockback = randA(2);
				int real_knock_ = 0;
				while(knockback)
				{
					if(env[current_level].isMove(coord_def(beam->x,beam->y),unit_->isFly(),unit_->isSwim(),false))
					{
						if(!env[current_level].isMonsterPos(beam->x,beam->y))
						{
							unit_->SetXY(coord_def(beam->x,beam->y));
							real_knock_++;
						}
					}
					else
						break;
					beam++;
					knockback--;
				}
				if(real_knock_)
				{
					LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_KNOCKBACK,true,false,false,CL_normal,
						 PlaceHolderHelper(unit_->GetName()->getName()));
				}
			}
		}
		order->SetParadox(0); 
		
		return true;
	}
	return false;
}
bool skill_kyoko_smite(int pow, bool short_, unit* order, coord_def target)
{	
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);
	
	if(target_unit)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("smite");
		}
		attack_infor temp_att(randA_1(10+pow/4),10+pow/4,99,order,order->GetParentType(),ATT_NOISE,name_infor(LOC_SYSTEM_ATT_NOISE));
		target_unit->damage(temp_att, true);
		if(randA(10)==0)
			target_unit->SetConfuse(rand_int(3,6));
		return true;
	}
	return false;
}
bool skill_summon_option(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	
	int i = 1; 
	for(; i>0 ; i--)
	{
		if(monster *mon_ = BaseSummon(MON_MAGICAL_STAR, rand_int(30,60), true, false, 2, order, target, SKD_SUMMON_OPTION, GetSummonMaxNumber(SPL_SUMMON_OPTION)))
		{
			mon_->LevelUpdown(pow/20,5.0f);
			return_ = true;
		}
	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}
bool skill_summon_golem(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	
	int i = 1; 
	for(; i>0 ; i--)
	{
		if(monster *mon_ = BaseSummon(MON_GOLEM, rand_int(60,120), true, false, 2, order, target, SKD_SUMMON_GOLEM, GetSummonMaxNumber(SPL_SUMMON_GOLEM)))
		{
			order->SetSaved(true);
			mon_->LevelUpdown(pow/20);
			return_ = true;
		}
	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}
bool skill_hypnosis(int pow, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = DebufBeam(SPL_HYPNOSIS, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_HYPNOSIS,pow)))
		{
			rand_rect_iterator rit(hit_mon->position,1,1,true);
			unit* unit_ = NULL; //부딪힌 적
			bool hit_ = false; //부딪혔다!

			hit_ = !env[current_level].isMove(coord_def(rit->x,rit->y),hit_mon->isFly(),hit_mon->isSwim(),false);
			unit_= env[current_level].isMonsterPos(rit->x,rit->y);

			if(hit_) //벽에 부딪혔다.
			{
				if (env[current_level].isInSight(order->position)) {
					soundmanager.playSound("stone");
				}
				attack_infor temp_att(randC(1,13+pow/6),(13+pow/6),99,NULL,order->GetParentType(),ATT_WALL,name_infor(LOC_SYSTEM_ATT_CRASH));
				hit_mon->damage(temp_att, true);
			}
			else if(unit_)
			{ //유닛에 부딪히면 둘에게 데미지 
				if (env[current_level].isInSight(order->position)) {
					soundmanager.playSound("stone");
				}
				{
					attack_infor temp_att(randC(1,13+pow/6),(13+pow/6),99,unit_,order->GetParentType(),ATT_WALL,name_infor(LOC_SYSTEM_ATT_CRASH));
					hit_mon->damage(temp_att, true);
				}				
				{
					attack_infor temp_att(randC(1,6+pow/8),(6+pow/8),99,hit_mon,order->GetParentType(),ATT_WALL,name_infor(LOC_SYSTEM_ATT_CRASH));
					unit_->damage(temp_att, true);
				}
			}
			else
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_HYPNOSIS_MOVE,true,false,false,CL_normal,
					 PlaceHolderHelper(hit_mon->GetName()->getName()));
				hit_mon->SetXY(rit->x,rit->y);
			}
			if(randA(4) == 0)
			{
				hit_mon->LostTarget();
			}
			hit_mon->PlusTimeDelay(-hit_mon->GetWalkDelay()); //1턴 행동을 쉰다.

		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		return true;
	}
	return false;
}
bool skill_mute(int pow, bool short_, unit* order, coord_def target)
{ 

	if(unit* hit_mon = DebufBeam(SPL_MUTE, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_MUTE,pow)))
		{
			hit_mon->SetMute(rand_int(20+pow/2,40+pow/2));
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}
bool skill_self_injury(int pow, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = DebufBeam(SPL_SELF_INJURY, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_SELF_INJURY,pow)))
		{ //나중에 추가할것-> 마법을 쓰는 캐릭터는 마법으로 자해할 가능성?
			if(!hit_mon->isplayer())
			{
				monster *mon_ = (monster*) hit_mon;

				if(mon_->state.GetState() == MS_SLEEP)
				{//자고있는데 자해할리가
					if(order->isplayer())
						printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_SELF_INJURY_SLEEP),true,false,false,CL_normal);
					return false; 
				}
				if(mon_->flag & M_FLAG_NO_ATK){ //공격못하는애가 자해할리가
					
					if(order->isplayer())
						printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_SELF_INJURY_CANT),true,false,false,CL_normal);	
					return false;
				}

				int num_=0;
				for(int i=0;i<3;i++,num_++)
					if(mon_->atk_type[i] == ATT_NONE)
						break;		
				num_ = randA(num_-1);

				int damage_ = 10 + mon_->GetAttack(num_,true);
				damage_ = (damage_ + randA(damage_))/2;
				damage_*=2.0f;
				attack_infor temp_att(damage_,2.0f*mon_->GetAttack(num_,true),
					99,mon_,order->GetParentType(),mon_->atk_type[num_],mon_->atk_name[num_]);					
				hit_mon->damage(temp_att, true);
				hit_mon->PlusTimeDelay(-hit_mon->GetWalkDelay()); //1턴 행동을 쉰다.
			}
			else
			{
				attack_type brand_ = ATT_NORMAL;
				if(you.equipment[ET_WEAPON])
					brand_ = (attack_type)GetAttType((weapon_brand)you.equipment[ET_WEAPON]->value5);
				int damage_ = you.GetAttack(false);
				damage_*=1.4f;
				attack_infor temp_att(damage_,1.4f*you.GetAttack(true),
					99,&you,order->GetParentType(),brand_,name_infor(LOC_SYSTEM_ATT_NORMAL));					
				hit_mon->damage(temp_att, true);

			}
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}
bool skill_charm(int pow, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = DebufBeam(SPL_CHARM, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_CHARM,pow)))
		{
			hit_mon->SetCharm(rand_int(20+pow/2,40+pow/2));
			hit_mon->CheckSightNewTarget();
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}

bool skill_laser(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(2,9+pow/8),2*(9+pow/8),18,order,order->GetParentType(),SpellLength(SPL_LASER),8,BMT_PENETRATE,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_LASER));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("laser");
			}
			throwtanmac(29, beam, temp_infor, NULL);
		}
		order->SetParadox(0); 
		return true;
	}
	return false;
}

bool skill_spark(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("spark");
		}
		beam_infor temp_infor(randC(5,9+pow/18),5*(9+pow/18),99,order,order->GetParentType(),SpellLength(SPL_SPARK),8,BMT_PENETRATE,ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_SPARK));
		ThrowSector(46,beam,temp_infor,GetSpellSector(SPL_SPARK),[&](coord_def c_){
		},false);
		return true;
	}
	return false;
}
bool skill_summon_unzan(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	
	int i = 1; 
	for(; i>0 ; i--)
	{
		if(monster *mon_ = BaseSummon(MON_UNZAN, rand_int(100,150), true, false, 2, order, target, SKD_SUMMON_UNZAN, GetSummonMaxNumber(SPL_SUMMON_UNZAN)))
		{
			return_ = true;
		}
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("ufo");
		}
	}
	return return_;

}
bool skill_summon_unzan_punch(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	
	int i = 1; 
	for(; i>0 ; i--)
	{
		if(monster *mon_ = BaseSummon(MON_UNZAN_PUNCH, rand_int(20,30), true, false, 2, order, target, SKD_SUMMON_UNZAN_PUNCH, GetSummonMaxNumber(SPL_SUMMON_UNZAN_PUNCH)))
		{
			mon_->image = &img_named_unzan_punch[randA(3)];
			return_ = true;
		}
	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}
bool skill_summon_zombie_fairy(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	
	int i = 3; 
	for(; i>0 ; i--)
	{
		if(monster *mon_ = BaseSummon(MON_ZOMBIE_FAIRY, rand_int(30,60), true, false, 2, order, target, SKD_SUMMON_ZOMBIE_FAIRY, GetSummonMaxNumber(SPL_SUMMON_ZOMBIE_FAIRY)))
		{
			return_ = true;
		}
	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}

bool skill_summon_ufo(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	
	int i = 1; 
	for(; i>0 ; i--)
	{
		if(monster *mon_ = BaseSummon(randA(2)?(randA(1)?MON_BLUE_UFO:MON_GREEN_UFO):MON_RED_UFO, rand_int(60+pow/4,120+pow/4), true, false, 2, order, target, SKD_SUMMON_UFO, GetSummonMaxNumber(SPL_SUMMON_UFO)))
		{
			return_ = true;
		}
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("ufo");
		}
	}
	return return_;
}
bool skill_haste_other(int pow, bool short_, unit* order, coord_def target)
{	
	if(order->isplayer())
		return false;
	monster* mon_order = (monster*)order;

	vector<monster*> target_mon_list;


	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(&(*it) != order && it->isLive() && isBandAlly(mon_order,&(*it)) && mon_order->isMonsterSight(it->position)/* &&
			(it->s_haste == 0)*/)
		{
			beam_iterator beam(order->position,order->position);
			if(!CheckThrowPath(order->position,it->position, beam))
				continue;
			if(!SpellFlagCheck(SPL_HASTE_OTHER, S_FLAG_SMITE))
			{		
				bool beam_ok_ = true;
				for(beam.init();!beam.end();beam++)
				{
					unit *temp = env[current_level].isMonsterPos((*beam).x,(*beam).y);
					if(temp)
					{
						if(temp->isLive() && temp != &(*it))
						{
							beam_ok_ = false;
							break;
						}
					}
				}	
				if(beam_ok_)
				{
					target_mon_list.push_back(&(*it));
				}
			}
			else 
			{
				target_mon_list.push_back(&(*it));			
			}
		}
	}
	if(target_mon_list.empty())
		return false;
	rand_shuffle(target_mon_list.begin(),target_mon_list.end());

	monster* final_target = target_mon_list.back();

	final_target->SetHaste(rand_int(20+pow/3,40+pow/3));

	return true;
}
bool skill_heal_other(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
		return false;
	monster* mon_order = (monster*)order;

	vector<monster*> target_mon_list;


	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(&(*it) != order && it->isLive() && isBandAlly(mon_order,&(*it)) && mon_order->isMonsterSight(it->position) &&
			(it->hp < it->max_hp))
		{
			beam_iterator beam(order->position,order->position);
			if(!CheckThrowPath(order->position,it->position, beam))
				continue;
			if(!SpellFlagCheck(SPL_HEAL_OTHER, S_FLAG_SMITE))
			{		
				bool beam_ok_ = true;
				for(beam.init();!beam.end();beam++)
				{
					unit *temp = env[current_level].isMonsterPos((*beam).x,(*beam).y);
					if(temp)
					{
						if(temp->isLive() && temp != &(*it))
						{
							beam_ok_ = false;
							break;
						}
					}
				}	
				if(beam_ok_)
				{
					target_mon_list.push_back(&(*it));
				}
			}
			else 
			{
				target_mon_list.push_back(&(*it));			
			}
		}
	}
	if(target_mon_list.empty())
		return false;
	rand_shuffle(target_mon_list.begin(),target_mon_list.end());

	monster* final_target = target_mon_list.back();
	
	final_target->HpUpDown(rand_int(2+pow/10,10+pow/5),DR_NONE);
	if(env[current_level].isInSight(final_target->position)) {
		LocalzationManager::printLogWithKey(LOC_SYSTEM_HEALED,true,false,false,CL_normal,
			PlaceHolderHelper(final_target->GetName()->getName()));
	}

	return true;

}
bool skill_mind_bending(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randA_1(13+pow/25),13+pow/25,17+pow/15,order,order->GetParentType(),SpellLength(SPL_MIND_BENDING),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_TANMAC));
		
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			coord_def c_ =throwtanmac(19,beam,temp_infor,NULL);
			unit* hit_mon = env[current_level].isMonsterPos(c_.x,c_.y,order);
			if(hit_mon)
			{		
				if(hit_mon->CalcuateMR(GetDebufPower(SPL_MIND_BENDING,pow)))
				{
					hit_mon->SetSlow(rand_int(10,20)+randA(pow/12));
				}
				else if(hit_mon->isYourShight())
				{
					LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
						 PlaceHolderHelper(hit_mon->GetName()->getName()));
				}
				hit_mon->AttackedTarget(order);
			}
		}
		order->SetParadox(0); 
		return true;
	}
	return false;
}
bool skill_stone_punch(int pow, bool short_, unit* order, coord_def target)
{
	if(order == &you)
	{
		if(you.equipment[ET_WEAPON])
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_SHOULD_UNARMED),true,false,false,CL_normal);
			return false;
		}
		you.SetAlchemyBuff(ALCT_STONE_FIST,rand_int(8,15)+pow/5);
		return true;
	}
	return false;
}
bool skill_stone_arrow(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		int mon_panlty_ = order->isplayer()?0:4;//몬스터가 쓸때 패널티
		int damage_ = 19+pow/5.5-mon_panlty_;
		beam_infor temp_infor(randC(1,damage_),damage_,13+pow/15,order,order->GetParentType(),SpellLength(SPL_STONE_ARROW),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_STONE));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("stone");
			}
			throwtanmac(26, beam, temp_infor, NULL);
		}
		order->SetParadox(0); 
		return true;
	}
	return false;
}
bool skill_stone_trap(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		if(!env[current_level].isMove(target.x,target.y,floor_effect::isFly(FLOORT_STONE),floor_effect::isSwim(FLOORT_STONE),floor_effect::isNoGround(FLOORT_STONE)))
		{
			if(order->isplayer())
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CANT_TRAP),true,false,false,CL_normal);
			return false;
		}

		if(order == &you)
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_STONE_TRAP),true,false,false,CL_normal);
		env[current_level].MakeFloorEffect(target,&img_effect_rock_trap,&img_effect_rock_trap,FLOORT_STONE,20+pow/4,&you);
		rand_rect_iterator rit(target,1,1);
		for(;!rit.end();rit++)
		{
			if(randA(75)<pow)
			{
				env[current_level].MakeFloorEffect((*rit),&img_effect_rock_trap,&img_effect_rock_trap,FLOORT_STONE,20+pow/4,&you);
			}
		}
		return true;
	}
		
	return false;
}
bool skill_stone_uplift(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("earthquake");
		}
		vector<coord_def> vt_;
		{
			rect_iterator rit(target,1,1);
			for(;!rit.end();rit++)
			{
				if(randA(randA(90))<pow || (*rit) == target)
				{
					textures* t_ = &img_effect_rock_uplift[rand_int(1,4)];
					if((*rit) == target)
						t_ =  &img_effect_rock_uplift[0];
					if(env[current_level].isMove(rit->x,rit->y))
					{
						env[current_level].MakeEffect(*rit,&img_blast[1],false);
						env[current_level].MakeEffect(*rit,t_,false);
						vt_.push_back(*rit);
					}
				}
			}
		}
		for(auto it = vt_.begin();it != vt_.end();it++)
		{
			if(env[current_level].isMove(it->x,it->y))
			{
				if(unit* hit_ = env[current_level].isMonsterPos(it->x,it->y))
				{
					attack_infor attack_infor_(randC(3,8+pow/14),3*(8+pow/14),99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_ROCK));
					hit_->damage(attack_infor_, true);
		
					//hit_->damage(att_, true);
				}

			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}
bool skill_kaname_drill(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		if (!order->isplayer()) //카나메드릴은 너무 쎄서 몬스터 보정이 좀 더 필요
			pow *= 0.7f;
		beam_infor temp_infor(randC(3,18+pow/5),3*(18+pow/5),13+pow/15,order,order->GetParentType(),SpellLength(SPL_KANAME_DRILL),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_KANAMEDRILL));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("stone");
			}
			throwtanmac(28, beam, temp_infor, NULL);
		}
		order->SetParadox(0); 
		return true;
	}
	return false;
}
bool skill_diamond_hardness(int pow, bool short_, unit* order, coord_def target)
{
	if(order == &you)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("stone");
		}
		you.SetAlchemyBuff(ALCT_DIAMOND_HARDNESS,rand_int(30,50)+pow/3);
		return true;
	}
	return false;
}
bool skill_poison_skin(int pow, bool short_, unit* order, coord_def target)
{
	if(order == &you)
	{
		you.SetAlchemyBuff(ALCT_POISON_BODY,rand_int(20,30)+pow/5);
		return true;
	}
	return false;
}
bool skill_stone_form(int pow, bool short_, unit* order, coord_def target)
{
	if(order == &you)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("spellcard");
		}
		you.SetAlchemyBuff(ALCT_STONE_FORM,rand_int(30,50)+pow/3);
		return true;
	}
	return false;
}
bool skill_knife_collect(int pow, bool short_, unit* order, coord_def target)
{
	if(order == &you)
	{
		you.SetKnifeCollect(rand_int(30,50)+pow/3);
		return true;
	}
	return false;
}

bool skill_burst(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("bomb");
		}
		vector<coord_def> vt_;
		{
			rect_iterator rit(target,1,1);
			for(;!rit.end();rit++)
			{
				if(randA(randA(90))<pow || (*rit) == target)
				{
					if(env[current_level].isMove(rit->x,rit->y))
					{
						env[current_level].MakeEffect(*rit,&img_blast[0],false);
						vt_.push_back(*rit);
					}
				}
			}
		}
		for(auto it = vt_.begin();it != vt_.end();it++)
		{
			if(env[current_level].isMove(it->x,it->y))
			{
				if(unit* hit_ = env[current_level].isMonsterPos(it->x,it->y))
				{
					if(hit_->GetId() != MON_FLAN && hit_->GetId() != MON_FLAN_BUNSIN) { //플랑은 면역(나중에 폭팔면역추가?)
						attack_infor attack_infor_(randC(3,6+pow/18),3*(6+pow/18),99,order,order->GetParentType(),ATT_BURST,name_infor(LOC_SYSTEM_ATT_BURST));
						hit_->damage(attack_infor_, true);				
					}
				}
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}

bool skill_summon_flandre(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	
	int i = 3; 
	for(; i>0 ; i--)
	{
		if(BaseSummon(MON_FLAN_BUNSIN, rand_int(90,120), true, true, 2, order, target, SKD_SUMMON_FLAN, GetSummonMaxNumber(SPL_FLAN_BUSIN)))
		{
			return_ = true;
		}
	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("laugh");
		}
	}
	return return_;

}
bool skill_suicide_bomb(int power, bool short_, unit* order, coord_def target)
{
	if(1)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("bomb");
		}
		textures* t_ = &img_blast[0];
		{
			dif_rect_iterator rit(order->position,2);
		
			for(;!rit.end();rit++)
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if(order->isSightnonblocked(*rit))
					{
						env[current_level].MakeEffect(*rit,t_,false);
					}
				}
		}
		
		{
			dif_rect_iterator rit(order->position,2);
		
			for(;!rit.end();rit++)
			{
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if(order->isSightnonblocked(*rit))
					{
						if(unit* hit_ = env[current_level].isMonsterPos(rit->x,rit->y))
						{	
							if(hit_ != order)
							{
								int att_ = randC(4,13+power/20);
								int m_att_ = 4*(13+power/20);

								attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_SUICIDE));
								hit_->damage(temp_att, true);
							}
						}
					}
				}
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		if(!order->isplayer())
		{
			monster* mon_ = (monster*)order;
			mon_->dead(PRT_NEUTRAL,true);
		}
		else
		{
			//attack_infor temp_att(order->GetHp()/2,order->GetHp()/2,99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_BURST));
			//order->damage(temp_att, true);
		}
		return true;
	}
	return false;
}
bool skill_rabbit_horn(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isBamboo() && order && !order->isUserAlly())
	{
		if(map_list.bamboo_rate<((order->GetId() == MON_TEWI)?400:350))
			map_list.bamboo_rate+=(order->GetId() == MON_TEWI)?35:20;
		if(order && env[current_level].isInSight(order->position))
		{
			if(order->GetId() == MON_TEWI)
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_TEWI_HORN),false,false,false,CL_small_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_RABBIT_HORN),false,false,false,CL_small_danger);
		}
		return true;
	}
	return false;

}
bool skill_summon_lessor_demon(int pow, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	
	int i = 1; 
	for(; i>0 ; i--)
	{
		if(monster *mon_ = BaseSummon(randA(2)==0?MON_SARA:(randA(1)?MON_LUIZE:MON_ELIS), rand_int(60,120), true, false, 2, order, target, SKD_SUMMON_LESSOR_DEMON, GetSummonMaxNumber(SPL_SUMMON_LESSOR_DEMON)))
		{
			return_ = true;
		}
	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}
bool skill_luminus_strike(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	int length_ = ceil(sqrt(pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2)));
	length_ = min(length_,SpellLength(SPL_FIRE_BALL));
	if(CheckThrowPath(order->position,target,beam))
	{		
		float mon_panlty_ = order->isplayer()?1.0f:0.8f;//몬스터가 쓸때 패널티
		int damage_ = (14+power/6)*mon_panlty_;
		beam_infor temp_infor(randC(3,damage_),3*(damage_),99,order,order->GetParentType(),SpellLength(SPL_LUMINUS_STRIKE),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_LIGHTTANMAC));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot_heavy");
			}
			coord_def pos = throwtanmac(12,beam,temp_infor,NULL);	
			unit* hit_mon = env[current_level].isMonsterPos(pos.x,pos.y,order);
			int max_len_ = max(abs(order->position.x - pos.x),abs( order->position.y - pos.y));
			if(max_len_ >= 3)
			{
				attack_infor temp_att(randC(1,damage_),1*(damage_),99,order,order->GetParentType(),ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_BURST));
				BaseBomb(pos, &img_blast[2],temp_att,hit_mon);
			}
		}
		order->SetParadox(0); 

		return true;
	}
	return false;
}

bool skill_fire_storm(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("nuke");
		}
		textures* t_ = &img_blast[0];
		{
			dif_rect_iterator rit(target,2);
		
			for(;!rit.end();rit++)
				if(env[current_level].isMove(rit->x,rit->y,true) && env[current_level].PostoCheckSight(target, (*rit), 3))
				{
					if((!order->isplayer() || env[current_level].isInSight(*rit)) && order->isSightnonblocked(*rit))
					{
						env[current_level].MakeEffect(*rit,t_,false);
					}
				}
		}
		
		if(env[current_level].isInSight(target))
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_FIRESTORM) + " ",false,false,false,CL_normal);
		{
			dif_rect_iterator rit(target,2);
		
			for(;!rit.end();rit++)
			{
				if(env[current_level].isMove(rit->x,rit->y,true) && env[current_level].PostoCheckSight(target, (*rit), 3))
				{
					if((!order->isplayer() || env[current_level].isInSight(*rit)) && order->isSightnonblocked(*rit))
					{
						if(unit* hit_ = env[current_level].isMonsterPos(rit->x,rit->y))
						{	
							if(1/*hit_ != order*/)
							{
								int att_ = randC(9,10+power/20);
								int m_att_ = 9*(10+power/20);

								attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_FIRE_PYSICAL_BLAST,name_infor(LOC_SYSTEM_ATT_FIRESTORM));
								hit_->damage(temp_att, true);
							}
						}
						env[current_level].MakeSmoke((*rit), img_fog_fire, SMT_FIRE, rand_int(3,8),  0, order);
					}
				}
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		env[current_level].MakeNoise(target,16,NULL);	
		return true;
	}
	return false;
}
bool skill_blizzard(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("wind");
			soundmanager.playSound("cold");
		}
		if(env[current_level].isInSight(target))
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_BLIZZARD) + " ",false,false,false,CL_normal);
		{
			dif_rect_iterator rit(target,2);
		
			for(;!rit.end();rit++)
			{
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if((!order->isplayer() || env[current_level].isInSight(*rit)) && order->isSightnonblocked(*rit))
					{
						for(list<smoke>::iterator it = env[current_level].smoke_list.begin();it != env[current_level].smoke_list.end() ;it++)
						{
							if(it->position.x == rit->x && it->position.y == rit->y)
							{
								WaitForSingleObject(mutx, INFINITE);
								it->clear();
								env[current_level].smoke_list.erase(it);
								ReleaseMutex(mutx);
								break;
							}
						}
						//if(unit* hit_ = env[current_level].isMonsterPos(rit->x,rit->y))
						//{	
						//	if(hit_ != order)
						//	{
						//		int att_ = randC(9,10+power/20);
						//		int m_att_ = 9*(10+power/20);

						//		attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_FIRE_PYSICAL_BLAST,name_infor(LOC_SYSTEM_ATT_FIRESTORM));
						//		hit_->damage(temp_att, true);
						//	}
						//}
						env[current_level].MakeSmoke((*rit), img_blizzard, SMT_BLIZZARD, rand_int(5,10)+power/15,  0, order);
					}
				}
			}
		}
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}

bool skill_perfect_freeze(int pow, bool short_, unit* order, coord_def target)
{
	map_effect = 1;
	Sleep(500);
	
	for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it!=env[current_level].mon_vector.end(); it++)
	{	
		if(it->isLive() && env[current_level].isInSight(it->position) && order->isSightnonblocked(it->position))
		{
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("timestop");
			}
			int att_ = 10+pow/7;				
			attack_infor temp_att(randC(5,att_),5*(att_),99,order,order->GetParentType(),ATT_COLD_BLAST,name_infor(LOC_SYSTEM_ATT_COLD));
			it->damage(temp_att, true);
			it->SetFrozen(randA(30));			
		}
	}
	map_effect = 0;
	return true;
}

bool skill_draw_power(int pow, bool short_, unit* order, coord_def target)
{	
	int p_tem = 0;
	{
		for(list<item>::iterator it = env[current_level].item_list.begin();it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++;
			if((!order->isplayer() || env[current_level].isInSight(temp->position)) && order->isSightnonblocked(temp->position))
			{
				if(isPick(&(*temp)) && (temp->type == ITM_FOOD && temp->value1 == 0))
				{
					PickUpNum(temp,1,true);
					p_tem++;
				}
			}
		}
	}

	if(p_tem)
	{

		printlog(LocalzationManager::formatString(LOC_SYSTEM_SPELL_P_COLLECT, PlaceHolderHelper(to_string(p_tem))),true,false,false,CL_normal);
		return true;
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_P_COLLECT_NONE), true,false,false,CL_normal);
		return false;
	}
	return true;
}

bool skill_animal_change(int pow, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = DebufBeam(SPL_ANIMAL_CHANGE, order, target))
	{
		
		if(!hit_mon->isplayer() && ((monster*)hit_mon)->flag & M_FLAG_ANIMAL)
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_ANIMAL_CHANGE_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
			return false;
		}

		if(hit_mon->CalcuateMR(GetDebufPower(SPL_ANIMAL_CHANGE,pow)))
		{
			if(!hit_mon->isplayer())
			{
				int animal_id_ = MON_CROW;
				if(hit_mon->GetLevel()<4)
					 animal_id_ = randA(1)?MON_RAT:MON_CROW;
				else if(hit_mon->GetLevel()<8)
					 animal_id_ = randA(1)?MON_CRANE:MON_SNAKE;
				else if(hit_mon->GetLevel()<12)
					 animal_id_ = randA(1)?MON_FROG:MON_ORANGE_CAT;
				else/* if(hit_mon->GetLevel()<16)*/
					 animal_id_ = randA(2)==0?MON_EAGLE:randA(1)?MON_RAIJUU:MON_TIGER;
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_ANIMAL_CHANGE,true,false,false,CL_normal,
				  PlaceHolderHelper(hit_mon->GetName()->getName()));
				
				if(!hit_mon->isplayer() && (order->isplayer() || order->isUserAlly()))
				{
					int flag_ = ((monster*)hit_mon)->flag;
					if(!(flag_ & M_FLAG_SUMMON))
					{
						you.GetExp(((monster*)hit_mon)->exper);
					}
				}
				
				((monster*)hit_mon)->ChangeMonster(animal_id_,M_FLAG_ALLY | M_FLAG_NONE_STAIR);
			}
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}

bool skill_field_violet(int power, bool short_, unit* order, coord_def target)
{
	for(list<events>::iterator it = env[current_level].event_list.begin(); it != env[current_level].event_list.end(); it++)
	{
		if((*it).id == EVL_VIOLET)
		{
			if(order->isplayer())
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ONLY_ONE_FILED),true,false,false,CL_normal);
			return false;
		}
	} 
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("spellcard");
	}
	if(env[current_level].isInSight(target))
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_FILED_VIOLET) + " ",false,false,false,CL_normal);
	env[current_level].MakeEvent(EVL_VIOLET,coord_def(target.x,target.y),EVT_ALWAYS,rand_int(10,20)+power/10);
	return true;
}
bool skill_time_paradox(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if(!randA(5))
			you.SetTransPanalty(1);
		you.SetParadox(rand_int(20,30)+power/4);
	}
	return true;
}
bool skill_private_sq(int power, bool short_, unit* order, coord_def target)
{	
	if(!order->isplayer())
		return false;
	for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it!=env[current_level].mon_vector.end(); it++)
	{	
		if(it->isLive() && &(*it) != order && env[current_level].isInSight(it->position) && order->isSightnonblocked(it->position))
		{			
			if(it->CalcuateMR(GetDebufPower(SPL_PRIVATE_SQ,power)))
			{
				it->SetSlow(rand_int(15,30)+randA(power/8));
			}
			else if(it->isYourShight())
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
					 PlaceHolderHelper(it->GetName()->getName()));
			}
			it->AttackedTarget(order);			
		}
	}
	if(!randA(7))
		you.SetTransPanalty(1);
	return true;
}

bool skill_controled_blink(int pow, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;
	if(!order->Tele_check(true, true))
		return false;	
	if (current_level == ZIGURRAT_LEVEL) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CBLINK_NOT_CONTROL), true, true, false, CL_small_danger);

		switch (waitkeyinput())
		{
		case 'Y':
		case 'y':
			break;
		case 'N':
		case 'n':
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE), true, true, false, CL_normal);
			return false;
		}
		you.Blink(25);
		return true;
	}

	if(you.control_blink(you.search_pos))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("blink");
		}
		you.SetTransPanalty(rand_int(1,2));
		return true;
	}
	return false;
}

bool skill_the_world(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("timestop");
		}
		you.SetTransPanalty(rand_int(3,4));
		you.SetTheWorld(rand_int(5+power/50,max(10,6+power/30)));
	}
	return true;
}

bool skill_haste_all(int power, bool short_, unit* order, coord_def target)
{	
	if(order->isplayer())
		return false;
	monster* mon_order = (monster*)order;

	vector<monster*> target_mon_list;


	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(&(*it) != order && it->isLive() && isBandAlly(mon_order,&(*it)) && mon_order->isMonsterSight(it->position)/* &&
			(it->s_haste == 0)*/)
		{
			beam_iterator beam(order->position,order->position);
			if(!CheckThrowPath(order->position,it->position, beam))
				continue;
			{
				target_mon_list.push_back(&(*it));
			}
		}
	}
	if(target_mon_list.empty())
		return false;
	rand_shuffle(target_mon_list.begin(),target_mon_list.end());

	for(vector<monster*>::iterator it = target_mon_list.begin(); it != target_mon_list.end(); it++)
	{
		monster* final_target = (*it);
		final_target->SetHaste(rand_int(20+power/3,40+power/3));
	}

	return true;
}
bool skill_heal_all(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
		return false;
	monster* mon_order = (monster*)order;

	vector<monster*> target_mon_list;


	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(&(*it) != order && it->isLive() && isBandAlly(mon_order,&(*it)) && mon_order->isMonsterSight(it->position) &&
			(it->hp < it->max_hp))
		{
			beam_iterator beam(order->position,order->position);
			if(!CheckThrowPath(order->position,it->position, beam))
				continue;
			{
				target_mon_list.push_back(&(*it));			
			}
		}
	}
	if(target_mon_list.empty())
		return false;
	rand_shuffle(target_mon_list.begin(),target_mon_list.end());
	
	for(vector<monster*>::iterator it = target_mon_list.begin(); it != target_mon_list.end(); it++)
	{
		monster* final_target = (*it);	
		final_target->HpUpDown(rand_int(2+power/10,10+power/5),DR_NONE);		
		if(env[current_level].isInSight(final_target->position)) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_HEALED,false,false,false,CL_normal,
				PlaceHolderHelper(final_target->GetName()->getName()));
		}
	}

	return true;
}
bool skill_moon_communication(int power, bool short_, unit* order, coord_def target)
{
	if(!order)
		return false;
	if(order->isplayer())
		return false;

	monster *mon_ = (monster*)order;

	if(mon_->flag & M_FLAG_SUMMON)
		return false;

	if(!env[current_level].isInSight(target))
		return false;
	if(order->GetExhausted())
		return false;

	order->SetCommunication(rand_int(3,5));
	return true;
}
bool skill_moon_gun(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		int damage_ = 6+power/8;
		beam_infor temp_infor(randC(3,damage_),3*damage_,18,order,order->GetParentType(),SpellLength(SPL_MON_TANMAC_SMALL),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_BULLET));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(19, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_summon_dream(int power, bool short_, unit* order, coord_def target)
{
	if(order->GetExhausted())
		return false;
	vector<int> list_;
	LOCALIZATION_ENUM_KEY speak_; 
	switch(randA(6))
	{
	case 0: //요정
		list_.push_back(MON_FAIRY_GREEN_WARRIOR);
		list_.push_back(MON_FAIRY_BLUE_MAGICIAN);
		list_.push_back(MON_FAIRY_SOCERER);
		list_.push_back(MON_FAIRY_SUN_FLOWER);
		list_.push_back(MON_FAIRY_HERO);
		speak_ = LOC_SYSTEM_MAGIC_SUMMON_DREAM_LAKE;
		break;
	case 1: //요괴산
		list_.push_back(MON_CROW_TENGU);
		list_.push_back(MON_YAMABUSH_TENGU);
		list_.push_back(MON_HANATACA_TENGU);
		list_.push_back(MON_KATPA_WATER_WIZARD);
		list_.push_back(MON_KATPA_SPEAR);
		speak_ = LOC_SYSTEM_MAGIC_SUMMON_DREAM_MOUNTAIN;
		break;
	case 2: //홍마관
		list_.push_back(MON_HOBGOBRIN_MAID);
		list_.push_back(MON_HOBGOBRIN_LIBRARIAN);
		list_.push_back(MON_HOBGOBRIN_TEMP);
		list_.push_back(MON_MAID_FAIRY);
		list_.push_back(MON_CHUPARCABRA);
		speak_ = LOC_SYSTEM_MAGIC_SUMMON_DREAM_SCARLET;
		break;
	case 3: //윳쿠리
		list_.push_back(MON_REIMUYUKKURI);
		list_.push_back(MON_MARISAYUKKURI);
		list_.push_back(MON_AYAYUKKURI);
		list_.push_back(MON_REMILIAYUKKURI);
		list_.push_back(MON_ALICEYUKKURI);
		list_.push_back(MON_YOUMUYUKKURI);
		speak_ = LOC_SYSTEM_MAGIC_SUMMON_DREAM_YUKKURI;
		break;
	case 4: //죽림
		list_.push_back(MON_RABIT_BOMB);
		list_.push_back(MON_RABIT_SPEAR);
		list_.push_back(MON_RABIT_SPEAR);
		list_.push_back(MON_RABIT_SUPPORT);
		list_.push_back(MON_RABIT_MAGIC);
		list_.push_back(MON_RABIT_SPEAR);
		speak_ = LOC_SYSTEM_MAGIC_SUMMON_DREAM_BAMBOO;
		break;
	case 5: //지저
		list_.push_back(MON_HAUNT);
		list_.push_back(MON_FIRE_CAR);
		list_.push_back(MON_HELL_SPIDER);
		list_.push_back(MON_BLOOD_HAUNT);
		list_.push_back(MON_HELL_CROW);
		speak_ = LOC_SYSTEM_MAGIC_SUMMON_DREAM_SUBTERRANEAN;
		break;
	case 6: //마계
		list_.push_back(MON_SARA);
		list_.push_back(MON_LUIZE);
		list_.push_back(MON_ELIS);
		list_.push_back(MON_EVIL_EYE);
		list_.push_back(MON_LITTLE_IMP);
		speak_ = LOC_SYSTEM_MAGIC_SUMMON_DREAM_PANDEMONIUM;
		break;
	}


	bool return_=false;	
	int i = 5; 
	for(; i>0 ; i--)
	{
		int id_ = list_[randA(list_.size()-1)];
		if(monster *mon_ = BaseSummon(id_, rand_int(30,60), true, false, 2, order, target, SKD_SUMMON_DREAM, GetSummonMaxNumber(SPL_SUMMON_DREAM)))
		{
			return_ = true;
		}
	}
	if(return_)
	{
		order->SetExhausted(rand_int(20,30));
		if(order && env[current_level].isInSight(order->position)) {
			LocalzationManager::printLogWithKey(speak_,true,false,false,CL_magic,
				PlaceHolderHelper(order->GetName()->getName()));
		}

	} 
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}

	return return_;
}
bool skill_mana_drain(int power, bool short_, unit* order, coord_def target)
{
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);
	
	if(target_unit)
	{
		//더 이상 데미지를 주지 않음
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("wind");
		}
		if(target_unit->isplayer()) //이 공격은 지능으로 감소가 가능하다.
		{
			///reduce_damage_ = max(1,reduce_damage_-randA(you.s_int)/2);
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_MANA_DRAIN,true,false,false,CL_small_danger,
				PlaceHolderHelper(order->GetName()->getName()));
			you.MpUpDown(rand_int(-7,-12));
		}
		else //몬스터는 저항력으로 따짐
		{
			//monster *mon_ = (monster*)target_unit;
			//reduce_damage_ = max(1,randA(mon_->level+mon_->resist*5)/2);
		}
		//attack_infor temp_att(randA_1(reduce_damage_),damage_,99,order,order->GetParentType(),ATT_SMITE,name_infor(LOC_SYSTEM_ATT_NIGHTMARE - 없음)); 
		//target_unit->damage(temp_att, true);
		return true;
	}
	return false;
}
bool skill_insane(int power, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = DebufBeam(SPL_INSANE, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_INSANE,power)))
		{
			int time_ = rand_int(5,10)+power/5;
			if(hit_mon->isplayer())
				time_ = time_/2;
			hit_mon->SetLunatic(time_);
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}
bool skill_blood_smite(int power, bool short_, unit* order, coord_def target)
{
	if (order->GetExhausted())
		return false;
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);
	
	if(target_unit)
	{
		if(order && target_unit->isplayer())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_BLOOD_STARE,true,false,false,CL_danger,
				 PlaceHolderHelper(order->GetName()->getName()),
				 PlaceHolderHelper(target_unit->GetName()->getName()));
		}
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("smite");
		}

		int damage_ = target_unit->GetMaxHp()*rand_int(10,20)/100;
		attack_infor temp_att(damage_,damage_,99,order,order->GetParentType(),ATT_BLOOD,name_infor(LOC_SYSTEM_ATT_BLOOD_STARE));
		target_unit->damage(temp_att, true);
		order->SetExhausted(rand_int(3, 5));
		return true;
	}
	return false;
}
bool skill_call_hound(int power, bool short_, unit* order, coord_def target)
{
	if(!order)
		return false;
	if(order->isplayer())
		return false;

	monster *mon_ = (monster*)order;

	if(mon_->flag & M_FLAG_SUMMON)
		return false;

	if(!env[current_level].isInSight(target))
		return false;
	if(order->GetExhausted())
		return false; 
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("howl");
	}

	order->SetCommunication(rand_int(2,4));
	return true;
}
bool skill_canon(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	int length_ = ceil(sqrt(pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2)));
	length_ = min(length_,SpellLength(SPL_CANNON));
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(0,0,15,order,order->GetParentType(),length_,1,BMT_NORMAL,ATT_THROW_NONE_MASSAGE,name_infor(LOC_SYSTEM_ATT_YINYANG_TANMAC));

		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{
			coord_def pos = throwtanmac(12,beam,temp_infor,NULL);
			attack_infor temp_att(randC(3,6+power/12),3*(6+power/12),99,order,order->GetParentType(),ATT_AC_REDUCE_BLAST,name_infor(LOC_SYSTEM_ATT_YINYANG_TANMAC));
			
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("bomb");
			}
			BaseBomb(pos, &img_blast[5],temp_att,order);
		}
		order->SetParadox(0); 
		return true;
	}
	return false;
}
bool skill_dolls_war(int power, bool short_, unit* order, coord_def target)
{	
	bool return_=false;	
	int i = 1; 
	for(; i>0 ; i--)
	{
		if(monster *mon_ = BaseSummon(MON_SANGHAI, rand_int(30,60)+power/2, true, false, 2, order, target, SKD_SUMMON_DOLLS_WAR, GetSummonMaxNumber(SPL_DOLLS_WAR)))
		{
			return_ = true;
		}	
		if(monster *mon_ = BaseSummon(MON_HOURAI, rand_int(30,60)+power/2, true, false, 2, order, target, SKD_SUMMON_DOLLS_WAR, GetSummonMaxNumber(SPL_DOLLS_WAR)))
		{
			order->SetSaved(true);
			return_ = true;
		}
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}
bool skill_fake_dolls_war(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;	
	int i = 1; 
	for(; i>0 ; i--)
	{
		int id_ = randA(1)?MON_FAKE_SANGHAI:MON_FAKE_HOURAI;
		if(monster *mon_ = BaseSummon(id_, rand_int(30,60)+power/2, true, false, 2, order, target, SKD_SUMMON_FAKE_DOLLS_WAR, GetSummonMaxNumber(SPL_FAKE_DOLLS_WAR)))
		{
			if(id_ == MON_FAKE_HOURAI)
				order->SetSaved(true);
			return_ = true;
		}
	}
	return return_;
}

bool skill_fire_spread(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("fire");
		}
		beam_infor temp_infor(0,0,99,order,order->GetParentType(),SpellLength(SPL_FIRE_SPREAD),8,BMT_PENETRATE,ATT_THROW_NONE_MASSAGE,name_infor(LOC_SYSTEM_ATT_SEAOFFIRE));
		ThrowSector(0,beam,temp_infor,GetSpellSector(SPL_FIRE_SPREAD),[&](coord_def c_){
			if(order->isSightnonblocked(c_))
			{
				env[current_level].MakeSmoke(c_, img_fog_fire, SMT_FIRE, rand_int(3,10)+power/10,  0, order);
			}
		},false);

		if(order && !order->isplayer())
		{
			order->SetExhausted(rand_int(3,10));
		}
		return true;
	} 
	return false;
}


bool skill_stasis(int power, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = DebufBeam(SPL_STASIS, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_STASIS,power)))
		{
			hit_mon->SetStasis(rand_int(10,40));
		}
		else if(hit_mon->isYourShight())
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}
bool skill_jump_attack(int power, bool short_, unit* order, coord_def target)
{
	if(!order)
		return false;
	unit* unit_ = (monster*)env[current_level].isMonsterPos(target.x,target.y);
	if(!unit_ && order->isEnemyUnit(unit_)) 
	{
		if(order->isplayer())
			printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_SHOULD_TARGET_ENEMY),true,false,false,CL_normal);	
		return false; //해당 위치에 몬스터가 없다.
	}
	if(order->position.distance_from(unit_->position)<=1)
	{		
		if(order->isplayer())
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_TOO_CLOSE),true,false,false,CL_normal);	
		return false; //해당 위치에 몬스터가 없다.
	}



	rand_rect_iterator rit(target,1,1,true);
	//rand_rect_iterator rit(target,range_,range_);
	while(!rit.end())
	{
		if(env[current_level].isMove(rit->x, rit->y, false, false) && !env[current_level].isMonsterPos(rit->x,rit->y) && env[current_level].isInSight(*rit))
		{
			order->SetXY((*rit));
			
			if (env[current_level].isInSight((*rit))) {
				soundmanager.playSound("howl");
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_JUMP_ATTACK,false,false,false,CL_normal,
					 PlaceHolderHelper(order->GetName()->getName()),
					 PlaceHolderHelper(unit_->GetName()->getName()));
			}
			attack_infor temp_att(order->GetAttack(false),order->GetAttack(true),order->GetHit(),order,order->GetParentType(),ATT_RUSH,name_infor(LOC_SYSTEM_ATT_LEAP));
			unit_->damage(temp_att,false);
			if(order)
			{
				order->SetExhausted(rand_int(3,10));
			}
			return true;
		}
		rit++;
	}
	if(order->isplayer())
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CANT_LEAP),true,false,false,CL_normal);	
	return false; //해당 위치에 몬스터가 없다.
}
bool skill_alert_noise(int power, bool short_, unit* order, coord_def target)
{
	{
		soundmanager.playSound("warning");
		if(order && !order->isplayer())
		{
			order->SetExhausted(rand_int(10,20));
		}
	}
	return false;
}
bool skill_summon_namaz(int power, bool short_, unit* order, coord_def target)
{
	for(list<events>::iterator it = env[current_level].event_list.begin(); it != env[current_level].event_list.end(); it++)
	{
		if((*it).id == EVL_NAMAZ)
		{
			if(order->isplayer())
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ONLY_ONE_NAMAZ) ,true,false,false,CL_normal);
			return false;
		}
	}
	if(env[current_level].isInSight(target))
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_NAMAZ_READY) + " ",false,false,false,CL_normal);
	env[current_level].MakeEvent(EVL_NAMAZ,coord_def(target.x,target.y),EVT_COUNT,4);
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("namaz");
	}
	return true;
}
bool skill_summon_namaz2(int power, bool short_, unit* order, coord_def target)
{
	int length_ = 2;
	if(env[current_level].isMove(target.x, target.y, true))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("earthquake");
		}
		textures* t_ = &img_blast[1];
		{
			dif_rect_iterator rit(target,length_);
		
			for(;!rit.end();rit++)
				if(env[current_level].isMove(rit->x,rit->y,true) && env[current_level].PostoCheckSight(target, (*rit), length_+1))
				{
					env[current_level].MakeEffect(*rit,t_,false);
				}
		}
		
		if(env[current_level].isInSight(target))
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_NAMAZ) + " ",false,false,false,CL_normal);
		{
			dif_rect_iterator rit(target,length_);
		
			for(;!rit.end();rit++)
			{
				if(env[current_level].isMove(rit->x,rit->y,true) && env[current_level].PostoCheckSight(target, (*rit), length_+1))
				{
					if(unit* hit_ = env[current_level].isMonsterPos(rit->x,rit->y))
					{	
						if(1/*hit_ != order*/)
						{
							int att_ = randC(8,6+power/30);
							int m_att_ = 8*(6+power/30);

							attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_SHOCKWAVE));
							hit_->damage(temp_att, true);
						}
					}
				}
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();	
		env[current_level].MakeNoise(target,12,NULL);		
		BaseSummon(MON_NAMAZ, rand_int(20,40)+power/5, false, false, 2, order, target, SKD_SUMMON_NAMAZ, GetSummonMaxNumber(SPL_SUMMON_NAMAZ));
		return true;
	}
	return false;
}



bool skill_schema_tanmac(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		int damage_ = order?1+order->GetLevel():6;
		beam_infor temp_infor(randC(2,damage_/2),damage_,99,order,order->GetParentType(),SpellLength(SPL_MAGIC_TANMAC),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_TANMAC));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));		
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(randA(2) ? (randA(1) ? 19 : 20) : 17, beam, temp_infor, NULL);

		}
		order->SetParadox(0);
		return true;
	}
	return false;
}

bool skill_change(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
		return false;
	monster* mon_order = (monster*)order;

	if(mon_order->id == MON_ENSLAVE_GHOST)
		return false;

	vector<int> target_mon_list;


	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(&(*it) != order && it->isLive() && !it->isUserAlly() && mon_order->isMonsterSight(it->position) &&
			it->id != MON_RACCON && it->id != MON_MAMIZO && it->level + (it->flag & M_FLAG_UNIQUE?3:0) >= mon_order->level)
		{ //아군이면서 둔갑 너구리가 아닐때 자기보다 레벨이 높을때 변신가능.
			beam_iterator beam(order->position,order->position);
			target_mon_list.push_back(it->id);
		}
	}
	if(target_mon_list.empty())
		return false;
	
	sort(target_mon_list.begin(), target_mon_list.end(),[&](const int &lf, const int &rf)
	{
		return mondata[lf].level + (mondata[lf].flag & M_FLAG_UNIQUE?3:0) > mondata[rf].level + (mondata[rf].flag & M_FLAG_UNIQUE?3:0);
	}); //레벨이 높은 순서대로 나열(네임드는 레벨 보정치를 3 높게 잡음)
	
	if(env[current_level].isInSight(mon_order->position)) {
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_DISGUISE,true,false,false,CL_magic,
			PlaceHolderHelper(order->GetName()->getName()),
			PlaceHolderHelper(mondata[target_mon_list[0]].name.getName()));
	}
			
	mon_order->ChangeMonster(target_mon_list[0],0);
	mon_order->flag &= ~M_FLAG_UNIQUE; //유니크 태그는 지운다.	
	mon_order->s_changed = rand_int(20,30);//둔갑턴

	return true;
}

bool skill_unluck(int power, bool short_, unit* order, coord_def target)
{
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);
	
	if(order && target_unit)
	{
		if( target_unit->isplayer())
		{
			you.SetUnluck(3);

			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_UNLUCK,false,false,false,CL_small_danger,
				PlaceHolderHelper(order->GetName()->getName()),
				PlaceHolderHelper(target_unit->GetName()->getName()));
			
			if(you.s_unluck<=3)
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_UNLUCKY1),false,false,false,CL_small_danger);
			else if(you.s_unluck<=6)
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_UNLUCKY2),false,false,false,CL_small_danger);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_UNLUCKY3),false,false,false,CL_danger);

			return true;
		}
		else
		{
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_UNLUCK_TO_MONSTER,true,false,false,CL_small_danger,
				 PlaceHolderHelper(order->GetName()->getName()),
				 PlaceHolderHelper(target_unit->GetName()->getName()),
				 PlaceHolderHelper(target_unit->GetName()->getName()));
			return true;
		}
	}
	return false;
}


bool skill_thunder(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("thunder");
		}
		vector<coord_def> vt_;
		{
			rect_iterator rit(target,1,1);
			for(;!rit.end();rit++)
			{
				if(randA(randA(600))<power+100 || (*rit) == target)
				{
					if(env[current_level].isMove(rit->x,rit->y,true))
					{
						env[current_level].MakeEffect(*rit,&img_blast[2],false);
						vt_.push_back(*rit);
					}
				}
			}
		}
		for(auto it = vt_.begin();it != vt_.end();it++)
		{
			if(env[current_level].isMove(it->x,it->y,true))
			{
				if(unit* hit_ = env[current_level].isMonsterPos(it->x,it->y))
				{
					attack_infor attack_infor_(randC(3,12+power/12),3*(12+power/12),99,order,order->GetParentType(),ATT_ELEC_BLAST,name_infor(LOC_SYSTEM_ATT_THUNDER));
					hit_->damage(attack_infor_, true);
				}
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}
bool skill_air_strike(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("wind");
		}
		int damage_ = 2*(8+power/8);
		beam_infor temp_infor(randC(1,damage_),damage_,15+power/15,order,order->GetParentType(),SpellLength(SPL_AIR_STRIKE),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor(LOC_SYSTEM_ATT_AIRSTRIKE));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(25,beam,temp_infor,NULL);
		order->SetParadox(0); 

		if (!order->isplayer()) 
		{
			monster* mon_ = (monster*)order;

			mon_->time_delay -= mon_->GetSpeed()/2; //2배 빠르게 공격가능
		}

		return true;
	}
	return false;
}
bool skill_summon_racoon(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	dif_rect_iterator rit(order->position,2);
	int id_ = MON_RACCON;
	int time_ = rand_int(20,30)+randA(power);

	int i = 3;

	for(; i>0 ; i--)
	{
		if(BaseSummon(id_, time_, true, false, 2, order, target, SKD_SUMMON_RACOON, GetSummonMaxNumber(SPL_SUMMON_RACOON)))
			return_ = true;
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}
bool skill_summon_youkai(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	dif_rect_iterator rit(order->position,2);
	int time_ = rand_int(10,30)+randA(power)/2;
	random_extraction<int> rand_;
	rand_.push(MON_ONI,2);
	rand_.push(MON_BLUE_ONI,2);
	rand_.push(MON_LANTERN_YOUKAI,3);
	rand_.push(MON_SNOW_GIRL,3);

	int i = 1;
	for(; i>0 ; i--)
	{
		if(BaseSummon(rand_.choice(), time_, true, false, 2, order, target, SKD_SUMMON_YOUKAI, GetSummonMaxNumber(SPL_SUMMON_YOUKAI)))
			return_ = true;
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("cold");
		}
	}
	return return_;
}
bool skill_mamizo_evade(int power, bool short_, unit* order, coord_def target)
{
	return false;
}
bool skill_macro_burst(int power, bool short_, unit* order, coord_def target)
{
	int direc = (GetPosToDirec(order->position, target) + 4)%8;
	int max_length=6;
	
	random_extraction<coord_def> result_;
	for(int i = -max_length; i <=max_length;i++)
	{
		for(int j = -max_length; j <= max_length;j++)
		{			
			coord_def goal_ = order->position+coord_def(i,j);
			int length_ = pow((float)i,2)+pow((float)j,2);

			if(!length_ || length_ > max_length*max_length || length_ < 2*2 )
				continue;
			beam_iterator beam(order->position,order->position);
			
			if(!CheckThrowPath(order->position,goal_, beam))//경로가 제대로 안 세워질경우 실패
				continue;

			int direc2 = GetPosToDirec(order->position, goal_);
			direc2 = min((direc-direc2+8)%8,(direc2-direc+8)%8);
			if(direc2>=2)
				continue;
			
			if(env[current_level].isMove(goal_))
				result_.push(goal_);
		}

	}

	if(result_.GetSize() == 0)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_MACRO_BURST_NEED_SPACE),true,false,false,CL_normal);
		return false;
	}


	if(env[current_level].isMove(target.x, target.y))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("wind");
		}
		vector<coord_def> vt_;
		{
			rect_iterator rit(target,1,1);
			for(;!rit.end();rit++)
			{
				if(/*randA(randA(600))<power+100*/1 || (*rit) == target)
				{
					if(env[current_level].isMove(rit->x,rit->y))
					{
						env[current_level].MakeEffect(*rit,&img_blast[4],false);
						vt_.push_back(*rit);
					}
				}
			}
		}
		
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_MACRO_BURST),true,false,false,CL_normal);

		for(auto it = vt_.begin();it != vt_.end();it++)
		{
			if(env[current_level].isMove(it->x,it->y))
			{
				if(unit* hit_ = env[current_level].isMonsterPos(it->x,it->y,&you))
				{
					attack_infor attack_infor_(randC(4,14+power/12),4*(14+power/12),99,order,order->GetParentType(),ATT_ELEC_BLAST,name_infor(LOC_SYSTEM_ATT_MACROBURST));
					hit_->damage(attack_infor_, true);
					
				}
				env[current_level].MakeSmoke((*it),img_fog_tonado,SMT_WHIRLWIND,rand_int(6,12)+randA(power/15),0,order);
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		
		you.SetXY(result_.pop());
		return true;
	}
	else{
		
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_MACRO_BURST_TARGET_MOVABLE),true,false,false,CL_normal);
		return false;
	}
	return false;
}
bool skill_shatter(int power, bool short_, unit* order, coord_def target)
{
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("earthquake");
	}
	printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_EARTHQUAKE),false,false,false,CL_normal);
	map_effect = 2;
	Sleep(500);
	
	for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it!=env[current_level].mon_vector.end(); it++)
	{	
		if(it->isLive() && env[current_level].isInSight(it->position) && order->isSightnonblocked(it->position))
		{
			int damage_ = 5*(3+power/5);
			if(it->isFly())
				damage_ /= 3;
			attack_infor temp_att(randA(damage_),damage_,99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_EARTHQUAKE));
			it->damage(temp_att, true);			
		}
	}
	
	int max_length=8;
	
	for(int i = -max_length; i <=max_length;i++)
	{
		for(int j = -max_length; j <= max_length;j++)
		{		
			coord_def pos_ = target+coord_def(i,j);
			if(env[current_level].isInSight(pos_) && env[current_level].dgtile[pos_.x][pos_.y].isBreakable() && randA(2) == 0)
			{
				env[current_level].changeTile(coord_def(pos_.x, pos_.y), env[current_level].base_floor);
			}
		}
	}
	map_effect = 0;
	you.resetLOS();
	return true;
}
bool skill_summon_yoshika(int power, bool short_, unit* order, coord_def target)
{
	if(!order || order->isplayer())
		return false;

	monster* seiga_ = (monster*)order;
	monster* yosika = NULL;
	for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
	{
		if(it->isLive() && it->id == MON_YOSIKA)
		{
			if( !seiga_->isMonsterSight((it->position)))
				return false;//이미 요시카가 시야내면 구지 호출할필요가 없ㅇ므
			yosika = &(*it);
			break;
		}
	}
	if(yosika)
	{

		dif_rect_iterator rit(order->position,2);
		if(env[current_level].isMove(rit->x, rit->y, yosika->isFly(), yosika->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) && seiga_->isMonsterSight((*rit)) && seiga_->position != (*rit))
		{
			yosika->SetXY(rit->x,rit->y);
			seiga_->SetSaved(true);
			if(yosika->isYourShight())
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RECALL_YOSHIKA,true,false,false,CL_normal,
					 PlaceHolderHelper(yosika->GetName()->getName()),
					 PlaceHolderHelper(seiga_->GetName()->getName()));
			}
		}
	}
	else
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
		if(monster* mon_=BaseSummon(MON_YOSIKA, 100, false, false, 2, order, order->position, SKD_OTHER, -1))
		{
			mon_->flag &= ~M_FLAG_SUMMON;
			mon_->flag &= ~M_FLAG_UNIQUE;
			seiga_->SetSaved(true);
			//mon_->ReturnEnemy();
			if(mon_->isYourShight())
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_REVIVE_YOSHIKA,true,false,false,CL_normal,
					 PlaceHolderHelper(seiga_->GetName()->getName()),
					 PlaceHolderHelper(mon_->name.getName()));
			}
		}
	}

	return true;
}
bool skill_nesy_cannon(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(3,5+power/6),3*(5+power/6),18,order,order->GetParentType(),SpellLength(SPL_WATER_CANNON),1,BMT_NORMAL,ATT_THROW_WATER,name_infor(LOC_SYSTEM_ATT_WATERPRESSURE));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot_heavy");
			}
			throwtanmac(22,beam,temp_infor,NULL);
		}
		order->SetParadox(0); 
		
		return true;
	}
	return false;
}
bool skill_mermaid_song(int power, bool short_, unit* order, coord_def target)
{
	unit* hit_mon = env[current_level].isMonsterPos(target.x, target.y);
	
	if(order && hit_mon)
	{
		if(hit_mon->isplayer())
		{
			if(you.confuse_resist>0)
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
					 PlaceHolderHelper(hit_mon->GetName()->getName()));
				return true;
			}


			beam_iterator beam(hit_mon->position,order->position);
			if(CheckThrowPath(hit_mon->position,order->position,beam))
			{
				beam.init();

				if(env[current_level].isMove(coord_def(beam->x,beam->y),hit_mon->isFly(),hit_mon->isSwim(),false))
				{
					hit_mon->SetXY(*beam);
					hit_mon->AttackedTarget(order);
					LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_MERMAID_SONG,true,false,false,CL_normal,
						 PlaceHolderHelper(hit_mon->GetName()->getName()),
						 PlaceHolderHelper(order->GetName()->getName()));
					return true;
				}
			}
			return true;
		}
	}
	return false;
}
bool skill_emerald_city(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y))
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("stone");
		}
		vector<coord_def> vt_;
		{
			rect_iterator rit(order->position,1,1);
			for(;!rit.end();rit++)
			{
				if((*rit) != target)
				{
					textures* t_ = &img_effect_emerald_uplift[randA(1)];
					if(env[current_level].isMove(rit->x,rit->y))
					{
						env[current_level].MakeEffect(*rit,&img_blast[3],false);
						env[current_level].MakeEffect(*rit,t_,false);
						vt_.push_back(*rit);
					}
				}
			}
		}
		for(auto it = vt_.begin();it != vt_.end();it++)
		{
			if(env[current_level].isMove(it->x,it->y))
			{
				if(unit* hit_ = env[current_level].isMonsterPos(it->x,it->y))
				{
					int damage_ = 10+power/6;
					attack_infor attack_infor_(randC(3,damage_),3*(damage_),99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_EMERALD));
					hit_->damage(attack_infor_, true);
				}

			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}
bool skill_autumn_blade(int power, bool short_, unit* order, coord_def target)
{
	if(order == &you)
	{
		you.SetAlchemyBuff(ALCT_AUTUMN_BLADE,rand_int(30,50)+power/3);
		return true;
	}
	return false;
}
bool skill_philosophers_stone(int power, bool short_, unit* order, coord_def target)
{
	if(order == &you)
	{
		you.SetAlchemyBuff(ALCT_PHILOSOPHERS_STONE,rand_int(30,50)+power/3);
		return true;
	}
	return false;
}
bool skill_summon_anchor(int power, bool short_, unit* order, coord_def target)
{
	bool return_ = false;

	int i = 1;
	for (; i > 0; i--)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("spellcard");
		}
		if (monster *mon_ = BaseSummon(MON_ANCHOR, rand_int(20, 30), true, false, 2, order, target, SKD_SUMMON_ANCHOR, GetSummonMaxNumber(SPL_SUMMON_ANCHOR)))
		{
			if (env[current_level].isInSight(target))
				printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_ACNHOR) + " ", false, false, false, CL_normal);
			return_ = true;
		}
	}
	return return_;
}
bool skill_reaper_met(int power, bool short_, unit* order, coord_def target)
{
	unit* hit_mon = env[current_level].isMonsterPos(target.x, target.y);

	if (order && hit_mon)
	{
		beam_iterator beam(order->position, hit_mon->position);
		if (CheckThrowPath(order->position, hit_mon->position, beam))
		{
			beam.init();

			if (env[current_level].isMove(coord_def(beam->x, beam->y), hit_mon->isFly(), hit_mon->isSwim(), false) &&
				env[current_level].isMonsterPos(beam->x, beam->y) == NULL)
			{
				if (env[current_level].isInSight(order->position)) {
					soundmanager.playSound("wind");
				}
				hit_mon->SetXY(*beam);
				hit_mon->AttackedTarget(order);
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_TASTE_OF_DEATH,true,false,false,CL_normal,
					 PlaceHolderHelper(hit_mon->GetName()->getName()),
					 PlaceHolderHelper(order->GetName()->getName()));
				hit_mon->SetSwift(rand_int(-30, -20));
				return true;
			}
		}
	}
	return false;

}

bool skill_afterlife(int power, bool short_, unit* order, coord_def target)
{
	if (order->GetExhausted())
		return false;
	unit* hit_mon = env[current_level].isMonsterPos(target.x, target.y);
	if (order && hit_mon)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("sickle");
		}
		int damage_ = hit_mon->GetHp() / 2;
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_AFTERLIFE,true,false,false,CL_small_danger,
			 PlaceHolderHelper(order->GetName()->getName()));
		attack_infor attack_infor_(damage_, damage_, 99, order, order->GetParentType(), ATT_SMITE, name_infor(LOC_SYSTEM_ATT_SHORT_LIFE_EXPECTACNY));
		hit_mon->damage(attack_infor_, true);
		if (order)
		{
			order->SetExhausted(rand_int(10, 15));
		}
		return true;
	}
	return false;
}
bool skill_prism_call(int power, bool short_, unit* order, coord_def target)
{

	if (order->isplayer())
		return false;
	monster* mon_ = (monster*)order;

	printlog(LocalzationManager::locString(LOC_SYSTEM_MAGIC_PRISM_CONCERTO) + " ", false, false, false, CL_normal);
	deque<monster*> dq;
	for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (&(*it) != mon_ && it->isLive() && mon_->isAllyMonster(&(*it)) &&
			(it->GetId() == MON_LYRICA || it->GetId() == MON_MERLIN || it->GetId() == MON_LUNASA))
		{
			dq.push_back(&(*it));
		}
	}
	rand_shuffle(dq.begin(), dq.end());
	dif_rect_iterator rit(order->position, 2);
	int j = 0;
	for (int i = 0; !rit.end() && i < dq.size(); rit++)
	{
		if (env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x, rit->y) && env[current_level].isInSight(coord_def(rit->x, rit->y)) && you.position != (*rit))
		{
			dq[i]->SetXY(rit->x, rit->y);
			if (dq[i]->isYourShight())
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_PRISM_CALL,false,false,false,CL_normal,
					 PlaceHolderHelper(dq[i]->GetName()->getName()));
				j++;
				if (j % 3 == 0)
					enterlog();
			}
			i++;
		}
	}
	return true;
}
bool skill_psychokinesis(int power, bool short_, unit* order, coord_def target)
{
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);

	if (target_unit)
	{
		if (!target_unit->isplayer()) {
			if (((monster*)target_unit)->flag & M_FLAG_NONE_MOVE) {
				if (order->isplayer()) {
					printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_PSYCHOKINESIS_FAIL), true, false, false, CL_normal);
				}
				return false; //이동불가인 적엔 사용 불가
			}
		} 
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("blink");
		}
		target_unit->Blink(25);
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_PSYCHOKINESIS,true,false,false,CL_normal,
			 PlaceHolderHelper(target_unit->GetName()->getName()));
		attack_infor temp_att(randA_1(11 + power / 7), 11 + power / 7, 99, order, order->GetParentType(), ATT_PSYCHO, name_infor(LOC_SYSTEM_ATT_PSYCHOKINESIS));
		target_unit->damage(temp_att, true);
		return true;
	}
	return false;
}
bool skill_summon_trash(int power, bool short_, unit* order, coord_def target)
{
	bool return_ = false;
	int id_ = MON_TRASH;
	int time_ = rand_int(30, 50);

	int i = GetSummonMaxNumber(SPL_SUMMON_TRASH);

	for (; i>0; i--)
	{
		if (monster* mon_ = BaseSummon(id_, time_, true, true, 3, order, target, SKD_SUMMON_TRASH, GetSummonMaxNumber(SPL_SUMMON_TRASH))) {

			mon_->image = &img_mons_trash[randA(3)];
			return_ = true;
		}
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}
bool skill_trash_rush(int power, bool short_, unit* order, coord_def target)
{
	if (order->isplayer())
		return false;
	monster* mon_ = (monster*) order;

	random_extraction<monster*> monster_list;

	for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (it->isLive() && it->sm_info.parent_map_id == mon_->map_id && it->sm_info.summon_id == GetSummonKind(SPL_SUMMON_TRASH))
		{
			if (mon_->isMonsterSight(it->position)) {
				beam_iterator beam(it->position, target);
				if (CheckThrowPath(it->position, target, beam)) {
					beam.init();
					int len_ = 0;
					while (!beam.end())
					{
						unit *unit_ = env[current_level].isMonsterPos(beam->x, beam->y, &you);
						if (unit_)
						{
							break;
						}
						len_++;
						beam++;
					}
					if (beam.end() && len_ != 0) {
						monster_list.push(&(*it));
					}
				}

			}
		}
	}

	int max_ = 0;
	//최대 4개까지 날림
	for (int i = 0; i < 4 && monster_list.GetSize() != 0; i++) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("shoot_heavy");
		}
		if (max_ == 0 && order->isYourShight()) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_TRASH_RUSH), true, false, false, CL_normal);
		}


		monster *trash = monster_list.pop();
		int damage_ = (13 + power / 16);
		beam_iterator beam(trash->position, target);
		beam_infor temp_infor(randC(1, damage_), damage_, 99, order, order->GetParentType(), 8, 1, BMT_PENETRATE, ATT_THROW_NORMAL, trash->name);
		throwtanmac(trash->image, beam, temp_infor, NULL);
		max_++;

		dif_rect_iterator rit(target, 3);

		for (; !rit.end(); rit++)
		{
			if (!env[current_level].isMove(rit->x, rit->y))
				continue; //움직일수없는 위치	
			if (env[current_level].isMonsterPos(rit->x, rit->y))
				continue; //이미 몬스터가 있는 위치

			trash->SetXY(*rit);
			break;
		}
	}
	if(max_)
		return true;
	else	
		return false;
}
bool skill_kokoro_roulette(int power, bool short_, unit* order, coord_def target)
{
	if (order->GetExhausted())
		return false;
	if (order->isplayer())
		return false;
	monster* mon_ = (monster*)order;

	random_extraction<int> rand_kokoro;
	rand_kokoro.push(MON_KOKORO1, (you.GetProperty(TPT_FIRE_IMUNE)?0 :
		(you.fire_resist <=0?100:
		(you.fire_resist == 1 ? 30 :
		(you.fire_resist == 2 ? 10 : 1
		)))));
	rand_kokoro.push(MON_KOKORO2, (you.GetProperty(TPT_COLD_IMUNE) ?0:
		(you.ice_resist <= 0 ? 100 :
		(you.ice_resist == 1 ? 30 :
		(you.ice_resist == 2 ? 10 : 1
		)))));
	rand_kokoro.push(MON_KOKORO3, (you.GetProperty(TPT_ELEC_IMUNE)?0:
		(you.elec_resist <= 0 ? 100 :
		(you.elec_resist == 1 ? 30 :
		(you.elec_resist == 2 ? 10 : 1
		)))));
		

	int id_ = rand_kokoro.pop();
	int mask_ = id_ == MON_KOKORO1 ? MON_MASK_ANGRY: id_ == MON_KOKORO2 ? MON_MASK_SAD: MON_MASK_HAPPY;
	
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("spellcard");
	}
	mon_->ChangeMonster(id_, 0);
	if(id_ == MON_KOKORO1) {
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_KOKORO_ROULETTE_RED,true,false,false,CL_normal,
			PlaceHolderHelper(order->GetName()->getName()));
	} else if(id_ == MON_KOKORO2) {
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_KOKORO_ROULETTE_BLUE,true,false,false,CL_normal,
			PlaceHolderHelper(order->GetName()->getName()));
	} else {
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_KOKORO_ROULETTE_GREEN,true,false,false,CL_normal,
			PlaceHolderHelper(order->GetName()->getName()));
	}
	if (monster* mask_mon_ = BaseSummon(mask_, rand_int(80,100), true, true, 2, order, target, SKD_SUMMON_MASK, GetSummonMaxNumber(SPL_KOKORO_CHANGE))) {

	}
	return true;
}

bool skill_thunder_bolt(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position, order->position);
	if (CheckThrowPath(order->position, target, beam))
	{
		int mon_panlty_ = order->isplayer() ? 0 : 2;//몬스터가 쓸때 패널티
		int damage_ = 11 + pow / 6 - mon_panlty_;
		beam_infor temp_infor(randC(3, damage_), 3 * (damage_), 18 + pow / 25, order, order->GetParentType(), SpellLength(SPL_THUNDER_BOLT), 8, BMT_PENETRATE, ATT_THROW_ELEC, name_infor(LOC_SYSTEM_ATT_THUNDER));
		if (short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("elec");
			}
			throwtanmac(38, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}


bool skill_mistia_song(int pow, bool short_, unit* order, coord_def target)
{
	if (order->GetExhausted())
		return false;
	int turn_ = rand_int(10, 15);
	if (!order->isplayer())
	{
		if (env[current_level].isInSight(target)) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_MYSTIA_SONG) + " ", false, false, false, CL_normal); 
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("laugh");
			}
			you.SetNightSight(1, turn_, false);
			order->SetExhausted(turn_ - rand_int(0, 2));
			return true;
		}
		order->SetExhausted(turn_ - rand_int(0, 2));
		return true;
	}
	order->SetExhausted(rand_int(3, 5));
	return false;
}

bool skill_throw_dish(int pow, bool short_, unit* order, coord_def target)
{
	int damage_ = 11 + pow / 6;
	int hit_ = 12 + pow / 20;
	beam_iterator beam(order->position, order->position);
	if (CheckThrowPath(order->position, target, beam))
	{
		beam_infor temp_infor(randC(1, damage_), damage_, hit_, order, order->GetParentType(), SpellLength(SPL_THROW_DISH), 1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_DISH));
		if (short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(34, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_mess_confusion(int power, bool short_, unit* order, coord_def target)
{
	int i = 0;
	for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (it->isLive() && it->isEnemyUnit(order) && &(*it) != order && order->isSightnonblocked(it->position))
		{
			if (it->CalcuateMR(GetDebufPower(SPL_MESS_CONFUSION, power)))
			{
				it->SetConfuse(rand_int(10, 20) + randA(power / 10));
			}
			else if (it->isYourShight())
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,false,false,false,CL_normal,
					 PlaceHolderHelper(it->GetName()->getName()));
			}
			it->AttackedTarget(order);
			i++;
			if (i % 3 == 0)
				enterlog();
		}
	}
	return true;
}
bool skill_abusion(int power, bool short_, unit* order, coord_def target)
{
	for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (it->isLive() && it->flag & M_FLAG_SUMMON && it->isEnemyUnit(order) && &(*it) != order && order->isSightnonblocked(it->position))
		{
			it->summon_time = 0;
		}
	} 
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("wind");
	}
	return true;
}

bool skill_sleep_smite(int power, bool short_, unit* order, coord_def target)
{
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);

	if (target_unit)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("smite");
		}
		if(order && order->isYourShight()) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_SLEEP_SMITE,false,false,false,CL_normal,
				PlaceHolderHelper(order->GetName()->getName()),
				PlaceHolderHelper(target_unit->GetName()->getName()));
		}
		target_unit->SetSleep(rand_int(15,25));
		return true;
	} 
	return false;
}



bool skill_target_elec(int power, bool short_, unit* order, coord_def target)
{
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);

	if (target_unit)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("elec");
		}
		beam_infor temp_infor(randA_1(10 + power / 6), 10 + power / 6, 99, order, order->GetParentType(), SpellLength(SPL_SHOCK), 1, BMT_NORMAL, ATT_THROW_ELEC, name_infor(LOC_SYSTEM_ATT_ELECTRIC));
		ThrowShock(21, order->position, target_unit->position, temp_infor);
		Sleep(120);
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}

bool skill_summon_elec_ball(int pow, bool short_, unit* order, coord_def target)
{
	bool return_ = false;

	int i = 2;
	for (; i>0; i--)
	{
		if (monster *mon_ = BaseSummon(MON_ELEC_BALL, rand_int(30, 60), true, true, 2, order, target, SKD_OTHER, GetSummonMaxNumber(SPL_SUMMON_ELEC_BALL)))
		{
			mon_->LevelUpdown((pow) / 8, 1.0f);
			return_ = true;
		}
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("elec");
		}
	}
	return return_;
}

bool skill_dream_call(int pow, bool short_, unit* order, coord_def target)
{
	if (order->isplayer())
		return false;
	//항상 플레이어에게만 사용함


	random_extraction<monster*> monster_list;
	monster* mon_ = (monster*)order;


	for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (&(*it) != mon_ && it->isLive() && it->isCanMove() && it->isAllyMonster(mon_))
		{
			if (mon_->isMonsterSight(it->position)) {
				monster_list.push(&(*it), it->level);
			}
		}
	}
	if (monster_list.GetSize() == 0)
		return false;

	rect_iterator rect_(you.position, 1, 1);
	bool send_ = false;
	while (!rect_.end())
	{
		if (env[current_level].isMove((*rect_))
			&& env[current_level].isMonsterPos(rect_->x, rect_->y) == NULL) {
			monster* send_mon_  = monster_list.pop();
			send_mon_->SetXY(*rect_);
			send_ = true;
			if(monster_list.GetSize() == 0)
				break;
		}
		rect_++;
	}
	if (send_ == true) {
		if (env[current_level].isInSight(order->position)) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_DREAM_CALL) + " ", false, false, false, CL_normal);
			soundmanager.playSound("blink");
		}
	}
	return true;
}
bool skill_hyper_beam(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position, order->position);
	if (CheckThrowPath(order->position, target, beam))
	{
		beam_infor temp_infor(randC(4, 12 + pow / 8), 4 * (12 + pow / 8), 20, order, order->GetParentType(), SpellLength(SPL_LASER), 8, BMT_PENETRATE, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_HYPERBEAM));
		if (short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot_heavy");
			}
			throwtanmac(29, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_kaguya_spell(int pow, bool short_, unit* order, coord_def target)
{
	bool return_ = false;
	int time_ = rand_int(10, 20);
	int i = 5;
	for (; i>0; i--)
	{
		if (monster *mon_ = BaseSummon(MON_KAGUYA_QUIZ_0+(5-i), time_, true, true, 3, order, target, SKD_SUMMON_KAGUYA_SPELL, GetSummonMaxNumber(SPL_KAGUYA_SPELL)))
		{
			mon_->PlusTimeDelay(-mon_->GetWalkDelay());
			mon_->SetInvincibility(-1, false);
			return_ = true;
		}
	}
	if (return_) {
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("summon");
		}
	}
	return return_;
}
bool skill_throw_sword(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position, order->position);
	if (CheckThrowPath(order->position, target, beam))
	{
		int damage_ = (8 + pow / 15);
		beam_infor temp_infor(randC(4, damage_), 4*damage_, 16, order, order->GetParentType(), SpellLength(SPL_THROW_SWORD), 1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_SWORD));
		if (short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));


		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("knife");
			}
			throwtanmac(47, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}
bool skill_throw_knife(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position, order->position);
	if (CheckThrowPath(order->position, target, beam))
	{
		int damage_ = (6 + pow / 11);
		beam_infor temp_infor(randC(3, damage_), 3 * damage_, 19, order, order->GetParentType(), SpellLength(SPL_THROW_KNIFE), 1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_KNIFE));
		if (short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));


		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("knife");
			}
			throwtanmac(48, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}

bool skill_throw_player(int pow, bool short_, unit* order, coord_def target)
{
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);

	if (target_unit)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("earthquake");
		}
		target_unit->Blink(40);
		int damage_ = 70;
		attack_infor temp_att(randA_1(damage_), damage_, 99, order, order->GetParentType(), ATT_SMASH, name_infor(LOC_SYSTEM_ATT_THROWING_ATLAS));
		target_unit->damage(temp_att, true);
		return true;
	}
	return false;
}

bool skill_throw_amulet(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position, order->position);
	if (CheckThrowPath(order->position, target, beam))
	{
		int damage_ = (5 + pow / 12);
		beam_infor temp_infor(randC(3, damage_), 3 * damage_, 19, order, order->GetParentType(), SpellLength(SPL_THROW_AMULET), 1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_BILL));
		if (short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));


		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			if (env[current_level].isInSight(order->position)) {
				soundmanager.playSound("shoot");
			}
			throwtanmac(2, beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		return true;
	}
	return false;
}

bool skill_warp_kick(int power, bool short_, unit* order, coord_def target)
{
	if (!order)
		return false;
	unit* unit_ = (monster*)env[current_level].isMonsterPos(target.x, target.y);
	if (!unit_ && order->isEnemyUnit(unit_))
	{
		if (order->isplayer())
			printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_SHOULD_TARGET_ENEMY), true, false, false, CL_normal);
		return false; //해당 위치에 몬스터가 없다.
	}
	if (order->position.distance_from(unit_->position) <= 1)
	{
		if (order->isplayer())
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_TOO_CLOSE), true, false, false, CL_normal);
		return false; //해당 위치에 몬스터가 없다.
	}



	rand_rect_iterator rit(target, 1, 1, true);
	//rand_rect_iterator rit(target,range_,range_);
	while (!rit.end())
	{
		if (env[current_level].isMove(rit->x, rit->y, false, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && env[current_level].isInSight(*rit))
		{
			order->SetXY((*rit));

			if (env[current_level].isInSight((*rit))) {
				soundmanager.playSound("blink");
				LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_DIMENSIONAL_RIFT,false,false,false,CL_normal,
					 PlaceHolderHelper(order->GetName()->getName()),
					 PlaceHolderHelper(unit_->GetName()->getName()));
			}
			attack_infor temp_att(order->GetAttack(false)*1.3f, order->GetAttack(true)*1.3f, order->GetHit(), order, order->GetParentType(), ATT_RUSH, name_infor(LOC_SYSTEM_ATT_DIMENSIONAL_RIFT));
			unit_->damage(temp_att, false);
			return true;
		}
		rit++;
	}
	if (order->isplayer())
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CANT_LEAP), true, false, false, CL_normal);
	return false; //해당 위치에 몬스터가 없다.
}


bool skill_reimu_barrier(int pow, bool short_, unit* order, coord_def target)
{
	if (order->isplayer())
		return false;
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);

	if (target_unit)
	{
		you.search_pos = target;
		you.god_value[GT_YUKARI][0] = target.x;
		you.god_value[GT_YUKARI][1] = target.y;
		you.SetDimension(rand_int(15, 25));
		soundmanager.playSound("timestop");
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_REIMU_BARRIER) + " ", false, false, false, CL_danger);
		//((monster*)order)
		if (order)
		{
			order->SetExhausted(-1);
		}
		return true;
	}
	return false;
}

void SetSpell(monster_index id, monster* mon_, vector<item_infor> *item_list_, bool* random_spell)
{
	list<spell> *list =  &(mon_->spell_lists);
	(*random_spell) = false;
	list->clear();
	switch (id)
	{
	case MON_FAIRY_GREEN:
		break;
	case MON_FAIRY_BLUE:
		list->push_back(spell(SPL_MON_TANMAC_SMALL, 40));
		break;
	case MON_FAIRY_BLUE_MAGICIAN:
		(*random_spell) = true;
		list->push_back(spell(randA(1) ? SPL_FROST : SPL_FLAME, 40));
		list->push_back(spell(SPL_BLINK, 15));
		break;
	case MON_FAIRY_RED_COMMANDER:
		list->push_back(spell(SPL_HASTE_OTHER, 20));
		list->push_back(spell(SPL_HEAL_OTHER, 20));
		break;
	case MON_FAIRY_GREEN_WARRIOR:
		if (randA(9) == 0)
		{
			item_infor t;
			makeitem(ITM_ARMOR_SHIELD, 0, &t, randA(28));
			item_list_->push_back(t);
		}
		break;
	case MON_FAIRY_HERO:
		if (randA(9) == 0)
		{
			item_infor t;
			makeitem(ITM_WEAPON_LONGBLADE, 0, &t, 25);
			item_list_->push_back(t);
		}
		break;
	case MON_BAKEKASA:
		if (randA(9) == 0)
		{
			item_infor t;
			makeitem(ITM_WEAPON_MACE, -1, &t, 30);
			item_list_->push_back(t);
		}
		break;
	case MON_KATPA:
		if (randA(19) == 0)
		{
			item_infor t;
			makeitem((item_type)((int)ITM_ARMOR_BODY_ARMOUR_0 + randA(randA(3))), 0, &t, AMK_KAPPA);
			item_list_->push_back(t);
		}
		break;
	case MON_KATPA_SPEAR:
		if (randA(9) == 0)
		{
			item_infor t;
			makeitem((item_type)((int)ITM_ARMOR_BODY_ARMOUR_0 + randA(3)), 0, &t, AMK_KAPPA);
			item_list_->push_back(t);
		}
		if (randA(5) == 0)
		{
			item_infor t;
			makeitem(ITM_WEAPON_SPEAR, 0, &t, randA(2) ? 5 : 35);
			item_list_->push_back(t);
		}
		break;
	case MON_KATPA_GUN:
		list->push_back(spell(SPL_MON_WATER_GUN, 90));
		break;
	case MON_RUMIA:
	{
		item_infor t;
		makeitem(ITM_ARMOR_HEAD, 1, &t);
		t.image = &img_item_armor_helmet[4];
		t.equip_image = &img_play_item_hat[4];
		t.name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_HEAD_RIBBON);
		item_list_->push_back(t);
		break;
	}
	case MON_KYOUKO:
	{
		list->push_back(spell(SPL_KYOKO_SMITE, 35));
		item_infor t;
		makeitem(ITM_WEAPON_MACE, 1, &t, 20);
		item_list_->push_back(t);
		break;
	}
	case MON_KOGASA:
	{
		item_infor t;
		makeitem(ITM_WEAPON_MACE, 1, &t, 30);
		item_list_->push_back(t);
		break;
	}
	case MON_CIRNO:
		list->push_back(spell(SPL_COLD_BEAM, 15));
		break;
	case MON_WRIGGLE:
		list->push_back(spell(SPL_SUMMON_BUG, 20));
		break;
	case MON_MEDICINE:
	{
		list->push_back(spell(SPL_MEDICINE_CLOUD, 30));
		item_infor t;
		makeitem((item_type)((int)ITM_ARMOR_BODY_ARMOUR_0 + randA(randA(3))), 1, &t, AMK_POISON);
		item_list_->push_back(t);
		break;
	}
	case MON_DIEFAIRY:
		list->push_back(spell(SPL_BLINK, 20));
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE, 60));
		break;
	case MON_HUMAM_MAN:
		if (randA(29) == 0)
		{
			item_infor t;
			makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_NORMAL);
			item_list_->push_back(t);
		}
		break;
	case MON_HUMAM_YINYANG:
		list->push_back(spell(SPL_FLAME, 12));
		list->push_back(spell(SPL_FROST, 12));
		list->push_back(spell(SPL_CONFUSE, 5));
		list->push_back(spell(SPL_SLOW, 5));
		list->push_back(spell(SPL_BLINK, 20));
		if (randA(29) == 0)
		{
			item_infor t;
			makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_NORMAL);
			item_list_->push_back(t);
		}
		break;
	case MON_HUMAM_PRIEST:
		list->push_back(spell(SPL_SMITE, 15));
		list->push_back(spell(SPL_SELF_HEAL, 10));
		if (randA(29) == 0)
		{
			item_infor t;
			makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_NORMAL);
			item_list_->push_back(t);
		}
		break;
	case MON_HUMAM_SAMURI:
		if (randA(9) == 0)
		{
			item_infor t;
			makeitem(randA(2) ? ITM_ARMOR_BODY_ARMOUR_2 : ITM_ARMOR_BODY_ARMOUR_3, 0, &t, AMK_NORMAL);
			item_list_->push_back(t);
		}
		if (randA(9) == 0)
		{
			item_infor t;
			makeitem(ITM_WEAPON_LONGBLADE, 0, &t, 5);
			item_list_->push_back(t);
		}
		break;
	case MON_CROW_TENGU:
		list->push_back(spell(SPL_GRAZE, 30));
		list->push_back(spell(SPL_VEILING, 20));
		break;
	case MON_SUNNY:
		list->push_back(spell(SPL_GLOW, 10));
		list->push_back(spell(SPL_INVISIBLE, 20));
		break;
	case MON_LUNAR:
		list->push_back(spell(SPL_SILENCE, 25));
		break;
	case MON_STAR:
		list->push_back(spell(SPL_HASTE, 25));
		break;
	case MON_ALICEYUKKURI:
		list->push_back(spell(SPL_FAKE_DOLLS_WAR, 40));
		break;
	case MON_YAMABIKO:
		list->push_back(spell(SPL_ALERT_NOISE, 25));
		break;
	case MON_KATPA_WATER_WIZARD:
		list->push_back(spell(SPL_FROST, 15));
		list->push_back(spell(SPL_ICE_BOLT, 20));
		list->push_back(spell(SPL_BLINK, 10));
		list->push_back(spell(SPL_INVISIBLE, 7));
		if (randA(9) == 0)
		{
			item_infor t;
			makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_KAPPA);
			item_list_->push_back(t);
		}
		break;
	case MON_YAMABUSH_TENGU:
		list->push_back(spell(SPL_HASTE, 20));
		list->push_back(spell(SPL_AIR_STRIKE, 20));
		list->push_back(spell(SPL_SELF_HEAL, 10));
		break;
	case MON_FORTUNE_TELLER:
		list->push_back(spell(SPL_FLAME, 20));
		list->push_back(spell(SPL_CONFUSE, 10));
		list->push_back(spell(SPL_INVISIBLE, 7));
		list->push_back(spell(SPL_MAGIC_TANMAC, 20));
		break;

	case MON_MOMIZI:
		{
			{
				item_infor t;
				makeitem(ITM_ARMOR_SHIELD, 1, &t, 25);
				t.image = &img_item_weapon_momizishield;
				t.equip_image = &img_play_item_shield[2];
				item_list_->push_back(t);
			}
			{
				item_infor t;
				makeitem(ITM_WEAPON_LONGBLADE, 1, &t, 20);
				item_list_->push_back(t);
			}
		}
		break;
	case MON_AYA:
		list->push_back(spell(SPL_HASTE, 30));
		list->push_back(spell(SPL_WHIRLWIND, 20));
		list->push_back(spell(SPL_GRAZE, 20));
		list->push_back(spell(SPL_VEILING, 20));
		list->push_back(spell(SPL_BLINK, 20));
		break;
	case MON_WAKASAGI:
		list->push_back(spell(SPL_MERMAID_SONG, 25));
		list->push_back(spell(SPL_COLD_BEAM, 15));
		list->push_back(spell(SPL_CONFUSE, 10));
		break;
	case MON_NAZRIN:
	{
		list->push_back(spell(SPL_SUMMON_PENDULUM, 30));
		list->push_back(spell(SPL_MAGIC_TANMAC, 20));
		item_infor t;
		makeitem(ITM_WEAPON_MACE, 1, &t, 40);
		item_list_->push_back(t);
		break;
	}
	case MON_SEKIBANKI_BODY:
		list->push_back(spell(SPL_SUMMON_SEKIBANKI, 15));
		break;
	case MON_SEKIBANKI_HEAD:
		list->push_back(spell(SPL_FLAME, 15));
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE, 10));
		list->push_back(spell(SPL_BLINK, 15));
		break;
	case MON_NITORI:
	{
		list->push_back(spell(SPL_WATER_CANNON, 30));
		list->push_back(spell(SPL_INVISIBLE, 15));
		list->push_back(spell(SPL_MON_WATER_GUN, 25));
		item_infor t;
		makeitem((item_type)((int)ITM_ARMOR_BODY_ARMOUR_0 + randA(3)), 1, &t, AMK_KAPPA);
		item_list_->push_back(t);
	}
	break;
	case MON_YOUMUYUKKURI:
		if (randA(19) == 0)
		{
			item_infor t;
			makeitem(ITM_WEAPON_LONGBLADE, 0, &t, 5);
			item_list_->push_back(t);
		}
		break;
	case MON_YOUMU:
		{
			item_infor t;
			makeitem(ITM_WEAPON_LONGBLADE, 1, &t, 5);
			item_list_->push_back(t);
		}
		{
			item_infor t;
			makeitem(ITM_WEAPON_SHORTBLADE, 1, &t, 25);
			item_list_->push_back(t);
		}
		break;
	case MON_KEGERO:
		list->push_back(spell(SPL_JUMP_ATTACK, 25));
		break;
	case MON_BENBEN:
		list->push_back(spell(SPL_SLOW, 20));
		list->push_back(spell(SPL_BLINK, 20));
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE, 30));
		break;
	case MON_YATHASI:
		list->push_back(spell(SPL_CONFUSE, 20));
		list->push_back(spell(SPL_BLINK, 20));
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE, 30));
		break;
	case MON_ORIN:
		list->push_back(spell(SPL_FIRE_BALL, 20));
		list->push_back(spell(SPL_GRAZE, 20));
		list->push_back(spell(SPL_SUMMON_ZOMBIE_FAIRY, 10));
		break;
	case MON_ORIN_CAT:
		list->push_back(spell(SPL_BLINK, 20));
		break;
	case MON_ICHIRIN:
		list->push_back(spell(SPL_SUMMON_UNZAN, 50));
		break;
	case MON_UNZAN:
		list->push_back(spell(SPL_SUMMON_UNZAN_PUNCH, 40));
		list->push_back(spell(SPL_LASER, 15));
		break;
	case MON_PACHU:
		list->push_back(spell(SPL_HASTE, 15));
		list->push_back(spell(SPL_FIRE_BOLT, 10));
		list->push_back(spell(SPL_ICE_BOLT, 10));
		list->push_back(spell(SPL_VENOM_BOLT, 10));
		list->push_back(spell(SPL_CHAIN_LIGHTNING, 10));
		list->push_back(spell(SPL_WATER_CANNON, 20));
		list->push_back(spell(SPL_BLINK, 15));
		break;
	case MON_MAGIC_BOOK:
	{
		item_infor t;
		makeCustomBook(&t);
		(*random_spell) = true;
		int arr_[] = { SPL_FIRE_BOLT, SPL_ICE_BOLT, SPL_VENOM_BOLT, SPL_LASER,SPL_STONE_ARROW,
		SPL_KANAME_DRILL, SPL_ICE_CLOUD, SPL_POISON_CLOUD, SPL_MIND_BENDING,SPL_LUMINUS_STRIKE,
		SPL_AIR_STRIKE
		};
		//주 공격스킬
		int arr2_[] = { SPL_DISCHARGE, SPL_CONFUSE, SPL_SLOW, SPL_GRAZE, SPL_VEILING,
		SPL_HASTE, SPL_INVISIBLE, SPL_HYPNOSIS
		};
		//보조스킬

		int add_ = arr_[randA(10)];
		list->push_back(spell(add_, 25));
		t.value1 = add_;
		int color_ = randA(3);
		mon_->image = &img_mons_magic_book[color_];
		t.image = &img_item_book[color_];
		if (randA(10) < 4)
		{
			if (randA(10) < 7)
			{
				list->push_back(spell(SPL_BLINK, 15));
				t.value2 = SPL_BLINK;
			}
			else
			{
				add_ = arr2_[randA(7)];
				list->push_back(spell(add_, 15));
				t.value2 = add_;
			}
		}
		item_list_->push_back(t);
	}
	break;
	case MON_HOBGOBRIN_MAID:
		if (randA(9) == 0)
		{
			item_infor t;
			makeitem((item_type)((int)ITM_ARMOR_BODY_ARMOUR_0 + randA(3)), 0, &t, AMK_MAID);
			item_list_->push_back(t);
		}
		break;
	case MON_HOBGOBRIN_LIBRARIAN:
		list->push_back(spell(SPL_INVISIBLE, 5));
		list->push_back(spell(SPL_MAGIC_TANMAC, 15));
		list->push_back(spell(SPL_SLOW, 10));
		list->push_back(spell(SPL_VENOM_BOLT, 15));
		break;
	case MON_HOBGOBRIN_TEMP:
		list->push_back(spell(SPL_SUMMON_LESSOR_DEMON, 15)); //악마소환으로 바꾸기
		//list->push_back(spell(SPL_SUMMON_BIRD,20));
		list->push_back(spell(SPL_SMITE, 10));
		break;
	case MON_KOAKUMA:
		list->push_back(spell(SPL_SUMMON_LESSOR_DEMON, 10)); //악마소환으로 바꾸기
		list->push_back(spell(SPL_FIRE_BOLT, 15));
		list->push_back(spell(SPL_BLINK, 20));
		break;
	case MON_MAID_FAIRY:
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE, 25));
		if (randA(19) == 0)
		{
			item_infor t;
			makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_MAID);
			item_list_->push_back(t);
		}
		break;
	case MON_SAKUYA:
	{
		list->push_back(spell(SPL_HASTE, 20));
		list->push_back(spell(SPL_SLOW, 10));
		list->push_back(spell(SPL_STASIS, 15));
		list->push_back(spell(SPL_TELEPORT_SELF, 10));
		list->push_back(spell(SPL_THROW_KNIFE, 25));
		list->push_back(spell(SPL_BLINK, 20));
		{
			item_infor t;
			makeitem(ITM_ARMOR_BODY_ARMOUR_0, 1, &t, AMK_MAID);
			item_list_->push_back(t);
		}
		{
			item_infor t;
			makeitem(ITM_WEAPON_SHORTBLADE, 1, &t, 20);
			item_list_->push_back(t);
		}
		break;
	}
	case MON_REMILIA:
		list->push_back(spell(SPL_HASTE, 25));
		break;
	case MON_DRAGON_BABY:
		list->push_back(spell(SPL_FIRE_BOLT, 20));
		break;
	case MON_KASEN:
		list->push_back(spell(SPL_SUMMON_BIRD, 30));
		break;
	case MON_YAMAWARO_NINJA:
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE, 30));
		if(randA(2)==0)
		{
			item_infor t;
			makeitem(ITM_THROW_TANMAC, 0, &t, TMT_POISON_NEEDLE);
			item_list_->push_back(t);
		}
		break;
	case MON_YAMAWARO_FLAG:
		list->push_back(spell(SPL_SELF_HEAL, 20));
		list->push_back(spell(SPL_HASTE_OTHER, 20));
		break;
	case MON_MAGICAL_STAR:
		list->push_back(spell(SPL_MAGIC_TANMAC, 15));
		break;
	case MON_KOISHI:
		list->push_back(spell(SPL_HYPNOSIS, 30));
		list->push_back(spell(SPL_SELF_INJURY, 20));
		list->push_back(spell(SPL_BLINK, 20));
		break;
	case MON_NUE:
		list->push_back(spell(SPL_SUMMON_UFO, 20));
		list->push_back(spell(SPL_CHAIN_LIGHTNING, 20));
		break;
	case MON_NAMAZ:
		list->push_back(spell(SPL_STONE_UPLIFT, 10));
		break;
	case MON_RACCON:
		list->push_back(spell(SPL_CHANGE, 30));
		break;
	case MON_LANTERN_YOUKAI:
		list->push_back(spell(SPL_FIRE_SPREAD, 25));
		break;
	case MON_EVIL_EYE:
		list->push_back(spell(SPL_TARGET_ELEC, 20));
		break;
	case MON_ELIS:
		list->push_back(spell(SPL_BLINK, 10));
		break;
	case MON_LUIZE:
		list->push_back(spell(SPL_ICE_BOLT, 20));
		list->push_back(spell(SPL_SELF_HEAL, 15));
		break;
	case MON_YUUGENMAGAN:
		list->push_back(spell(SPL_THUNDER_BOLT, 30));
		break;
	case MON_YUKI:
		list->push_back(spell(SPL_FIRE_BALL, 20));
		list->push_back(spell(SPL_FIRE_BOLT, 20));
		list->push_back(spell(SPL_SMITE, 10));
		break;
	case MON_MAI:
		list->push_back(spell(SPL_ICE_CLOUD, 20));
		list->push_back(spell(SPL_ICE_BOLT, 20));
		list->push_back(spell(SPL_SELF_HEAL, 10));
		break;
	case MON_SARIEL:
		list->push_back(spell(SPL_SUMMON_LESSOR_DEMON, 25));
		list->push_back(spell(SPL_HASTE_OTHER, 15));
		break;
	case MON_YUMEKO:
		list->push_back(spell(SPL_THROW_SWORD, 30));
		break;
	case MON_SCHEMA_EYE:
		list->push_back(spell(SPL_SCHEMA_TANMAC, 40));
		break;
	case MON_FLAN:
		list->push_back(spell(SPL_FLAN_BUSIN, 30));
		list->push_back(spell(SPL_BURST, 12));
		break;
	case MON_FLAN_BUNSIN:
		list->push_back(spell(SPL_BURST, 18));
		break;
	case MON_RABIT_BOMB:
		list->push_back(spell(SPL_SUICIDE_BOMB, 0));
		break;
	case MON_RABIT_SPEAR:
		if (randA(19) == 0)
		{
			item_infor t;
			makeitem(ITM_WEAPON_SPEAR, 0, &t, 43);
			item_list_->push_back(t);
		}
		break;
	case MON_RABIT_SUPPORT:
		list->push_back(spell(SPL_RABBIT_HORN, 25));
		list->push_back(spell(SPL_HASTE_OTHER, 30));
		break;
	case MON_RABIT_MAGIC:
		list->push_back(spell(SPL_FROST, 25));
		list->push_back(spell(SPL_ICE_BOLT, 20));
		list->push_back(spell(SPL_BLINK, 30));
		break;
	case MON_RAIJUU:
		list->push_back(spell(SPL_TARGET_ELEC, 30));
		break;
	case MON_TEWI:
		list->push_back(spell(SPL_RABBIT_HORN, 15));
		break;
	case MON_CLOWNPIECE:
		list->push_back(spell(SPL_FIRE_BALL, 10));
		list->push_back(spell(SPL_CONFUSE, 5));
		break;
	case MON_DOREMI:
	{
		list->push_back(spell(SPL_SUMMON_DREAM, 40));
		list->push_back(spell(SPL_SLEEP_SMITE, 15));
		list->push_back(spell(SPL_BLINK, 15));
		item_infor t;
		makeitem(ITM_MISCELLANEOUS, 0, &t, EVK_DREAM_SOUL);
		item_list_->push_back(t);
		break;
	}
	case MON_FAIRY_SOCERER:
		list->push_back(spell(SPL_ICE_BOLT, 20));
		list->push_back(spell(SPL_FIRE_BOLT, 20));
		break;
	case MON_FAIRY_SUN_FLOWER:
		list->push_back(spell(SPL_SMITE, 15));
		list->push_back(spell(SPL_HASTE_ALL, 20));
		list->push_back(spell(SPL_HEAL_ALL, 25));
		break;
	case MON_MOON_RABIT_SUPPORT:
		list->push_back(spell(SPL_MOON_COMMUNICATION, 20));
		list->push_back(spell(SPL_HASTE_OTHER, 15));
		break;
	case MON_MOON_RABIT_ATTACK:
		break;
	case MON_MOON_RABIT_ELITE:
		list->push_back(spell(SPL_MOON_GUN, 30));
		break;
	case MON_MAC:
		list->push_back(spell(SPL_SUMMON_DREAM, 25));
		//list->push_back(spell(SPL_BLINK,15));
		break;
	case MON_NIGHTMARE:
		list->push_back(spell(SPL_MANA_DRAIN, 20));
		break;
	case MON_LUNATIC:
		list->push_back(spell(SPL_INSANE, 20));
		break;
	case MON_HAUNT:
		break;
	case MON_FIRE_CAR:
		//list->push_back(spell(SPL_FIRE_BALL,25));
		//list->push_back(spell(SPL_FIRE_BOLT,20));
		break;
	case MON_HELL_SPIDER:
		break;
	case MON_BLOOD_HAUNT:
		list->push_back(spell(SPL_BLOOD_SMITE, 25));
		break;
	case MON_HELL_HOUND:
		list->push_back(spell(SPL_CALL_HOUND, 15));
		break;
	case MON_DESIRE:
	{
		if (mon_->fire_resist > 2) {
			mon_->name = name_infor(LOC_SYSTEM_MON_RED_DESIRE);
			mon_->atk_type[0] = ATT_FIRE_WEAK;
			mon_->image = &img_mons_desire_red;
		}
		else if (mon_->ice_resist > 2) {
			mon_->name = name_infor(LOC_SYSTEM_MON_BLUE_DESIRE);
			mon_->atk_type[0] = ATT_COLD_WEAK;
			mon_->image = &img_mons_desire_blue;
		}
		else if (mon_->elec_resist > 2) {
			mon_->name = name_infor(LOC_SYSTEM_MON_GREEN_DESIRE);
			mon_->atk_type[0] = ATT_ELEC_WEAK;
			mon_->image = &img_mons_desire_green;
		}
	}
	break;
		break;
	case MON_FLOWER_TANK:
		list->push_back(spell(SPL_LASER, 25));
		list->push_back(spell(SPL_LUMINUS_STRIKE, 15));
		break;
	case MON_EVIL_EYE_TANK:
		list->push_back(spell(SPL_CANNON, 21));
		break;
	case MON_SNOW_GIRL:
		list->push_back(spell(SPL_FREEZE, 20));
		list->push_back(spell(SPL_COLD_BEAM, 15));
		break;
	case MON_LETTY:
		list->push_back(spell(SPL_FREEZE, 25));
		list->push_back(spell(SPL_ICE_CLOUD, 15));
		break;
	case MON_YORIHIME:
		break;
	case MON_TOYOHIME:
		list->push_back(spell(SPL_ICE_BOLT, 15));
		list->push_back(spell(SPL_BLIZZARD, 20));
		break;
	case MON_UTSUHO:
		list->push_back(spell(SPL_FIRE_STORM, 6));
		list->push_back(spell(SPL_HASTE, 15));
		break;
	case MON_SUIKA:
		list->push_back(spell(SPL_THROW_PLAYER, 30));
		break;
	case MON_REIMU:
	{
		if (you.char_type == UNIQ_START_REIMU)
		{
			mon_->image = &img_named_reimu2;
		}
		list->push_back(spell(SPL_THROW_AMULET, 15));
		list->push_back(spell(SPL_WARP_KICK, 7));
	}
	break;
	case MON_ALICE:
		list->push_back(spell(SPL_DOLLS_WAR, 40));
		list->push_back(spell(SPL_TELEPORT_SELF, 30));
		break;
	case MON_SEIRAN:
		break;
	case MON_RINGO:
		list->push_back(spell(SPL_MOON_COMMUNICATION, 20));
		list->push_back(spell(SPL_HASTE_OTHER, 15));
		list->push_back(spell(SPL_SELF_HEAL, 15));
		break;
	case MON_UDONGE:
		list->push_back(spell(SPL_MIND_BENDING, 25));
		list->push_back(spell(SPL_FIELD_VIOLET, 15));
		break;
	case MON_KAGUYA:
		list->push_back(spell(SPL_KAGUYA_SPELL, 70));
		break;
	case MON_MOKOU:
		break;
	case MON_NESI:
		list->push_back(spell(SPL_NESY_CANNON, 30));
		break;
	case MON_SANGHAI:
	case MON_FAKE_SANGHAI:
		break;
	case MON_HOURAI:
		list->push_back(spell(SPL_LASER, 60));
		break;
	case MON_FAKE_HOURAI:
		list->push_back(spell(SPL_LASER, 45));
		break;
	case MON_TOKIKO:
	{
		list->push_back(spell(SPL_TWIST, 15));
		list->push_back(spell(SPL_VEILING, 25));
		random_extraction<int> arr_;

		arr_.push(BOOK_TEST_ANNIHILATE);
		arr_.push(BOOK_DEBUF);
		arr_.push(BOOK_MAID_ULTI);
		arr_.push(BOOK_ICE_ULTI);
		arr_.push(BOOK_SUMMON_ULTI);
		arr_.push(BOOK_AIR_ULTI);
		arr_.push(BOOK_ALCHMY_ULTI);

		int add_ = arr_.pop();

		item_infor t;
		makeitem(ITM_BOOK, 0, &t, add_);
		item_list_->push_back(t);
	}
	break;
	case MON_TOZIKO:
		list->push_back(spell(SPL_THUNDER, 20));
		break;
	case MON_FUTO:
		list->push_back(spell(SPL_FIRE_BALL, 15));
		list->push_back(spell(SPL_UNLUCK, 25));
		break;
	case MON_MAMIZO:
		list->push_back(spell(SPL_SUMMON_RACOON, 25));
		list->push_back(spell(SPL_SUMMON_YOUKAI, 15));
		list->push_back(spell(SPL_MAMIZO_EVADE, 0));
		break;
	case MON_SEIGA:
		list->push_back(spell(SPL_SUMMON_YOSHIKA, 40));
		list->push_back(spell(SPL_HASTE_OTHER, 25));
		break;
	case MON_MURASA:
	{
		list->push_back(spell(SPL_SUMMON_ANCHOR, 40));
		list->push_back(spell(SPL_ICE_BOLT, 10));
		list->push_back(spell(SPL_ICE_CLOUD, 25));
		list->push_back(spell(SPL_BLINK, 15));
		item_infor t;
		makeitem(ITM_WEAPON_AXE, 1, &t, 22);
		item_list_->push_back(t);
		break;
	}
	case MON_KEINE:
		list->push_back(spell(SPL_LASER, 35));
		list->push_back(spell(SPL_BLINK, 20));
		list->push_back(spell(SPL_SLOW, 15));
		break;
	case MON_LYRICA:
		list->push_back(spell(SPL_PRISM_CALL, 30));
		list->push_back(spell(SPL_LASER, 35));
		list->push_back(spell(SPL_BLINK, 20));
		break;
	case MON_MERLIN:
		list->push_back(spell(SPL_PRISM_CALL, 30));
		list->push_back(spell(SPL_CONFUSE, 35));
		list->push_back(spell(SPL_BLINK, 20));
		break;
	case MON_LUNASA:
		list->push_back(spell(SPL_PRISM_CALL, 30));
		list->push_back(spell(SPL_SLOW, 35));
		list->push_back(spell(SPL_BLINK, 20));
		break;
	case MON_KOMACHI:
	{
		list->push_back(spell(SPL_REAPER_MET, 40));
		list->push_back(spell(SPL_AFTERLITE, 20));
		item_infor t;
		makeitem(ITM_WEAPON_SPEAR, 1, &t, 30);
		item_list_->push_back(t);
		break;
	}
	case MON_SUMIREKO:
		list->push_back(spell(SPL_SUMMON_TRASH, 30));
		list->push_back(spell(SPL_TRASH_RUSH, 20));
		list->push_back(spell(SPL_PSYCHOKINESIS, 20));
		list->push_back(spell(SPL_BLINK, 30));
		break;
	case MON_KOKORO:
		list->push_back(spell(SPL_KOKORO_CHANGE, 50));
		break;
	case MON_KOKORO1:
		list->push_back(spell(SPL_FIRE_BOLT, 40));
		break;
	case MON_KOKORO2:
		list->push_back(spell(SPL_ICE_BOLT, 40));
		break;
	case MON_KOKORO3:
		list->push_back(spell(SPL_THUNDER_BOLT, 40));
		break;
	case MON_IKU:
		list->push_back(spell(SPL_THUNDER, 20));
		list->push_back(spell(SPL_THUNDER_BOLT, 25));
		list->push_back(spell(SPL_SUMMON_ELEC_BALL, 10));
		break;
	case MON_NEMUNO:
	{
		list->push_back(spell(SPL_SANTUARY, 35));
		item_infor t;
		makeitem(ITM_SCROLL, 0, &t, SCT_SANTUARY);
		item_list_->push_back(t);
		break;
	}
	case MON_NARUMI:
		list->push_back(spell(SPL_STONE_ARROW, 20));
		list->push_back(spell(SPL_KANAME_DRILL, 10));
		break;
	case MON_MISTIA:
		list->push_back(spell(SPL_MISTIA_SONG, 50));
		break;
	case MON_OCCULT_DISK:
		list->push_back(spell(SPL_THROW_DISH, 80));
		break;
	case MON_KUNEKUNE:
		list->push_back(spell(SPL_MESS_CONFUSION, 30));
		break;
	case MON_CURSE_DOLL:
		list->push_back(spell(SPL_SMITE, 10));
		break;
	case MON_DANCING_WEAPON:
	{
		item_infor t;
		makeitem((item_type)(rand_int(ITM_WEAPON_FIRST, ITM_WEAPON_CLOSE)), randA(1), &t);
		item_list_->push_back(t);
		mon_->image = t.image;
	}
	break;
	case MON_DANCING_ARMOUR:
	{
		item_infor t;
		material_kind kind_ = (material_kind)randA(MTK_MAX-1);
		armour_kind type_ = GetRandomArmourType(1);
		makeitem((item_type)(ITM_ARMOR_BODY_ARMOUR_0+ kind_), randA(1), &t, type_);
		item_list_->push_back(t);
		mon_->image = t.image;
		mon_->ac = kind_*2 + 1;
		mon_->ev = (15-kind_*3);
		switch (type_)
		{
		case AMK_MIKO:
			mon_->confuse_resist = 1;
			break;
		case AMK_KAPPA:
			mon_->ice_resist = 1;
			break;
		case AMK_FIRE:
			mon_->fire_resist = 1;
			break;
		case AMK_POISON:
			mon_->poison_resist = 1;
			break;
		case AMK_WING:
			mon_->elec_resist = 1;
			break;
		case AMK_MAID:
			mon_->resist++;
			break;
		default:
			break;
		}
	}
	break;
	case MON_HATATE:
		list->push_back(spell(SPL_VEILING, 20));
		list->push_back(spell(SPL_AIR_STRIKE, 25));
		list->push_back(spell(SPL_BLINK, 25));
		break;
	case MON_DOREKING:
		list->push_back(spell(SPL_SLEEP_SMITE, 20));
		list->push_back(spell(SPL_DREAM_CALL, 30));
		list->push_back(spell(SPL_HYPER_BEAM, 15));
		break;
	case MON_CURIOSITY:
		list->push_back(spell(SPL_DISCHARGE, 50));
		list->push_back(spell(SPL_THUNDER_BOLT, 10));
		break;
	case MON_KAGUYA_QUIZ_0:
		list->push_back(spell(SPL_TARGET_ELEC, 20));
		break;
	case MON_KAGUYA_QUIZ_1:
		list->push_back(spell(SPL_SMITE, 12));
		break;
	case MON_KAGUYA_QUIZ_2:
		list->push_back(spell(SPL_FLAME, 20));
		break;
	case MON_KAGUYA_QUIZ_3:
		list->push_back(spell(SPL_FROST, 20));
		break;
	case MON_KAGUYA_QUIZ_4:
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE, 15));
		break;
	default:
		break;
	}
}




bool MonsterUseSpell(spell_list skill, bool short_, monster* order, coord_def &target, int pow_)
{
	int power=(order->level-3)*8;
	if(pow_ != -1)
		power = pow_;
	if(order->force_turn)
	{
		if(order->force_strong)
			power *= 2;
		else
			power /= 2;
	}
	if (order->s_clever) {
		power *= 1.5f;
		if(wiz_list.wizard_mode == 1) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_DEBUG_CLEVER,false,false,false,CL_danger,
				PlaceHolderHelper(order->GetName()->getName()));
		}

	}
	power=max(0,min(SpellCap(skill),power));
	switch(skill)
	{
	case SPL_MON_TANMAC_SMALL:
		return skill_tanmac_small(power,short_,order,target);
	case SPL_MON_TANMAC_MIDDLE:
		return skill_tanmac_middle(power,short_,order,target);
	case SPL_MON_WATER_GUN:
		return skill_water_gun(power,short_,order,target);
	case SPL_FLAME:
		return skill_flame(power,short_,order,target);
	case SPL_FROST:
		return skill_frost(power,short_,order,target);
	case SPL_MEDICINE_CLOUD:
		return skill_medicine_cloud(power,short_,order,target);
	case SPL_COLD_BEAM:
		return skill_cold_beam(power,short_,order,target);
	case SPL_SUMMON_BUG:
		return skill_summon_bug(power,short_,order,target);
	case SPL_CONFUSE:
		return skill_confuse(power,short_,order,target);
	case SPL_SLOW:
		return skill_slow(power,short_,order,target);
	case SPL_SELF_HEAL:
		return skill_self_heal(power,short_,order,target);
	case SPL_BLINK:
		return skill_blink(power,short_,order,target);
	case SPL_SMITE:
		return skill_smite(power,short_,order,target);
	case SPL_BURN:
		return skill_burn(power,short_,order,target);
	case SPL_FIRE_WALL:
		return skill_fire_wall(power,short_,order,target);
	case SPL_FROZEN:
		return skill_frozen(power,short_,order,target);
	case SPL_FREEZE:
		return skill_freeze(power,short_,order,target);
	case SPL_STING:
		return skill_sting(power,short_,order,target);
	case SPL_CURE_POISON:
		return skill_cure_poison(power,short_,order,target);
	case SPL_TWIST:
		return skill_twist(power,short_,order,target);
	case SPL_SUMMON_MOOK:
		return skill_summon_mook(power,short_,order,target);
	case SPL_SHOCK:
		return skill_elec(power,short_,order,target);
	case SPL_CHAIN_LIGHTNING:
		return skill_chain_lightning(power,short_,order,target);
	case SPL_DISCHARGE:
		return skill_discharge(power,short_,order,target);
	case SPL_GLOW:
		return skill_glow(power,short_,order,target);
	case SPL_GRAZE:
		return skill_graze(power,short_,order,target);
	case SPL_VEILING:
		return skill_veiling(power,short_,order,target);
	case SPL_INVISIBLE:
		return skill_invisible(power,short_,order,target);
	case SPL_HASTE:
		return skill_haste(power,short_,order,target);
	case SPL_SILENCE:
		return skill_silence(power,short_,order,target);
	case SPL_MAGIC_TANMAC:
		return skill_magic_tanmac(power,short_,order,target);
	case SPL_FIRE_BALL:
		return skill_fire_ball(power,short_,order,target);
	case SPL_FIRE_BOLT:
		return skill_fire_bolt(power,short_,order,target);
	case SPL_ICE_BOLT:
		return skill_ice_bolt(power,short_,order,target);
	case SPL_VENOM_BOLT:
		return skill_venom_bolt(power,short_,order,target);
	case SPL_CONFUSE_CLOUD:
		return skill_confuse_cloud(power,short_,order,target);
	case SPL_ICE_CLOUD:
		return skill_ice_cloud(power,short_,order,target);
	case SPL_SUMMON_BIRD:
		return skill_summon_bird(power,short_,order,target);
	case SPL_RECALL:
		return skill_recall(power,short_,order,target);
	case SPL_TELEPORT_OTHER:
		return skill_teleport_other(power,short_,order,target);
	case SPL_TELEPORT_SELF:
		return skill_teleport_self(power,short_,order,target);
	case SPL_WHIRLWIND:
		return skill_whirlwind(power,short_,order,target);
	case SPL_SUMMON_PENDULUM:
		return skill_summon_pendulum(power,short_,order,target);
	case SPL_SUMMON_SEKIBANKI:
		return skill_summon_sekibanki(power,short_,order,target);
	case SPL_WATER_CANNON:
		return skill_water_cannon(power,short_,order,target);
	case SPL_KYOKO_SMITE:
		return skill_kyoko_smite(power,short_,order,target);
	case SPL_SUMMON_OPTION:
		return skill_summon_option(power,short_,order,target);
	case SPL_SUMMON_GOLEM:
		return skill_summon_golem(power,short_,order,target);
	case SPL_HYPNOSIS:
		return skill_hypnosis(power,short_,order,target);
	case SPL_MUTE:
		return skill_mute(power,short_,order,target);
	case SPL_SELF_INJURY:
		return skill_self_injury(power,short_,order,target);
	case SPL_CHARM:
		return skill_charm(power,short_,order,target);
	case SPL_LASER:
		return skill_laser(power,short_,order,target);
	case SPL_SPARK:
		return skill_spark(power,short_,order,target);		
	case SPL_SUMMON_UNZAN:
		return skill_summon_unzan(power,short_,order,target);
	case SPL_SUMMON_UNZAN_PUNCH:
		return skill_summon_unzan_punch(power,short_,order,target);
	case SPL_SUMMON_ZOMBIE_FAIRY:
		return skill_summon_zombie_fairy(power,short_,order,target);
	case SPL_SUMMON_UFO:
		return skill_summon_ufo(power,short_,order,target);
	case SPL_HASTE_OTHER:
		return skill_haste_other(power,short_,order,target);
	case SPL_HEAL_OTHER:
		return skill_heal_other(power,short_,order,target);
	case SPL_MIND_BENDING:
		return skill_mind_bending(power,short_,order,target);
	case SPL_STONE_PUNCH:
		return skill_stone_punch(power,short_,order,target);
	case SPL_STONE_ARROW:
		return skill_stone_arrow(power,short_,order,target); 
	case SPL_STONE_TRAP:
		return skill_stone_trap(power,short_,order,target);
	case SPL_STONE_UPLIFT:
		return skill_stone_uplift(power,short_,order,target);
	case SPL_KANAME_DRILL:
		return skill_kaname_drill(power,short_,order,target);
	case SPL_DIAMOND_HARDNESS:
		return skill_diamond_hardness(power,short_,order,target);
	case SPL_POISON_SKIN:
		return skill_poison_skin(power,short_,order,target);
	case SPL_STONE_FORM:
		return skill_stone_form(power,short_,order,target);
	case SPL_KNIFE_COLLECT:
		return skill_knife_collect(power,short_,order,target);
	case SPL_FLAN_BUSIN:
		return skill_summon_flandre(power,short_,order,target);
	case SPL_BURST:
		return skill_burst(power,short_,order,target);
	case SPL_SUICIDE_BOMB:
		return skill_suicide_bomb(power,short_,order,target);
	case SPL_RABBIT_HORN:
		return skill_rabbit_horn(power,short_,order,target);
	case SPL_SUMMON_LESSOR_DEMON:
		return skill_summon_lessor_demon(power,short_,order,target);	
	case SPL_LUMINUS_STRIKE:
		return skill_luminus_strike(power,short_,order,target);
	case SPL_FIRE_STORM:
		return skill_fire_storm(power,short_,order,target);
	case SPL_BLIZZARD: 
		return skill_blizzard(power,short_,order,target);
	case SPL_PERFERT_FREEZE: 
		return skill_perfect_freeze(power,short_,order,target);
	case SPL_DRAW_POWER:
		return skill_draw_power(power,short_,order,target);
	case SPL_ANIMAL_CHANGE:
		return skill_animal_change(power,short_,order,target);
	case SPL_FIELD_VIOLET:
		return skill_field_violet(power,short_,order,target);
	case SPL_TIME_PARADOX: 
		return skill_time_paradox(power,short_,order,target);
	case SPL_PRIVATE_SQ: 
		return skill_private_sq(power,short_,order,target);
	case SPL_CONTROLED_BLINK: 
		return skill_controled_blink(power,short_,order,target);
	case SPL_THE_WORLD:	
		return skill_the_world(power,short_,order,target);	
	case SPL_HASTE_ALL:
		return skill_haste_all(power,short_,order,target);
	case SPL_HEAL_ALL:	
		return skill_heal_all(power,short_,order,target);	
	case SPL_MOON_COMMUNICATION:
		return skill_moon_communication(power,short_,order,target);	
	case SPL_MOON_GUN:
		return skill_moon_gun(power,short_,order,target);	
	case SPL_SUMMON_DREAM:
		return skill_summon_dream(power,short_,order,target);	
	case SPL_MANA_DRAIN:
		return skill_mana_drain(power,short_,order,target);	
	case SPL_INSANE:
		return skill_insane(power,short_,order,target);	
	case SPL_BLOOD_SMITE:
		return skill_blood_smite(power,short_,order,target);	
	case SPL_CALL_HOUND:
		return skill_call_hound(power,short_,order,target);	
	case SPL_CANNON:
		return skill_canon(power,short_,order,target);	
	case SPL_DOLLS_WAR:
		return skill_dolls_war(power,short_,order,target);	
	case SPL_FAKE_DOLLS_WAR:
		return skill_fake_dolls_war(power,short_,order,target);	
	case SPL_FIRE_SPREAD:
		return skill_fire_spread(power,short_,order,target);			
	case SPL_STASIS:
		return skill_stasis(power,short_,order,target);	
	case SPL_JUMP_ATTACK:
		return skill_jump_attack(power,short_,order,target);
	case SPL_ALERT_NOISE: 
		return skill_alert_noise(power, short_, order, target);
	case SPL_SUMMON_NAMAZ:
		return skill_summon_namaz(power,short_,order,target);
	case SPL_SCHEMA_TANMAC:
		return skill_schema_tanmac(power,short_,order,target);
	case SPL_CHANGE:
		return skill_change(power,short_,order,target);
	case SPL_UNLUCK:
		return skill_unluck(power,short_,order,target);	
	case SPL_THUNDER:
		return skill_thunder(power,short_,order,target);	
	case SPL_AIR_STRIKE:
		return skill_air_strike(power,short_,order,target);	
	case SPL_SUMMON_RACOON:
		return skill_summon_racoon(power,short_,order,target);	
	case SPL_SUMMON_YOUKAI:
		return skill_summon_youkai(power,short_,order,target);	
	case SPL_MAMIZO_EVADE:
		return skill_mamizo_evade(power,short_,order,target);	
	case SPL_MACRO_BURST:
		return skill_macro_burst(power,short_,order,target);	
	case SPL_SHATTER:
		return skill_shatter(power,short_,order,target);	
	case SPL_SUMMON_YOSHIKA:
		return skill_summon_yoshika(power,short_,order,target);	
	case SPL_NESY_CANNON:
		return skill_nesy_cannon(power,short_,order,target);	
	case SPL_MERMAID_SONG:
		return skill_mermaid_song(power,short_,order,target);	
	case SPL_EMERALD_CITY:
		return skill_emerald_city(power,short_,order,target);	
	case SPL_AUTUMN_BLADE:
		return skill_autumn_blade(power,short_,order,target);	
	case SPL_PHILOSOPHERS_STONE:
		return skill_philosophers_stone(power,short_,order,target);	
	case SPL_SUMMON_ANCHOR:
		return skill_summon_anchor(power, short_, order, target);
	case SPL_REAPER_MET:
		return skill_reaper_met(power, short_, order, target);
	case SPL_AFTERLITE:
		return skill_afterlife(power, short_, order, target);
	case SPL_PRISM_CALL:
		return skill_prism_call(power, short_, order, target);
	case SPL_PSYCHOKINESIS:
		return skill_psychokinesis(power, short_, order, target);
	case SPL_SUMMON_TRASH:
		return skill_summon_trash(power, short_, order, target);
	case SPL_TRASH_RUSH:
		return skill_trash_rush(power, short_, order, target);
	case SPL_KOKORO_CHANGE:
		return skill_kokoro_roulette(power, short_, order, target);
	case SPL_THUNDER_BOLT:
		return skill_thunder_bolt(power, short_, order, target);
	case SPL_SANTUARY:
		return skill_santuary(power, short_, order, target);
	case SPL_MISTIA_SONG:
		return skill_mistia_song(power, short_, order, target);
	case SPL_THROW_DISH:
		return skill_throw_dish(power, short_, order, target);
	case SPL_MESS_CONFUSION:
		return skill_mess_confusion(power, short_, order, target);
	case SPL_SLEEP_SMITE:
		return skill_sleep_smite(power, short_, order, target);
	case SPL_TARGET_ELEC:
		return skill_target_elec(power, short_, order, target);
	case SPL_SUMMON_ELEC_BALL:
		return skill_summon_elec_ball(power, short_, order, target);
	case SPL_DREAM_CALL:
		return skill_dream_call(power, short_, order, target);
	case SPL_HYPER_BEAM:
		return skill_hyper_beam(power, short_, order, target);
	case SPL_KAGUYA_SPELL:
		return skill_kaguya_spell(power, short_, order, target);
	case SPL_THROW_SWORD:
		return skill_throw_sword(power, short_, order, target);
	case SPL_THROW_KNIFE:
		return skill_throw_knife(power, short_, order, target);
	case SPL_THROW_PLAYER:
		return skill_throw_player(power, short_, order, target);
	case SPL_THROW_AMULET:
		return skill_throw_amulet(power, short_, order, target);
	case SPL_WARP_KICK:
		return skill_warp_kick(power, short_, order, target);
	case SPL_REIMU_BARRIER:
		return skill_reimu_barrier(power, short_, order, target);
	default:
		return false;
	}
}

bool CheckDangerSpell(int danger_)
{	
	if(danger_>=3)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_TOO_DANGEROURS),false,false,false,CL_danger);
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			enterlog();
			break;
		case 'N':
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_WISDOM),true,false,false,CL_normal);
			return false;
		}
	}
	return true;
}
bool CheckThrowPath(coord_def start,coord_def target, beam_iterator &beam);


bool CheckSucide(coord_def pos, coord_def target, bool self, int size, int smite)
{
	
	if(pos == target && !self)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_ASK_SUICIDE),true,false,false,CL_small_danger);	
		return false;
	}
	beam_iterator beam(pos,target);

	CheckThrowPath(pos,target,beam);




	if(size)
	{
		bool warning_ = false;
		if (!smite) {
			for(beam.init();!beam.end();)
			{
				auto temp_beam = beam++;
				//스마이트형이 아닌경우 부딪히면 터지기 마련이다.
				bool block_ = false;
				if(!env[current_level].isMove(*(beam),true))
				{
					beam = temp_beam;
					target = (*beam);
					block_ = true;
				}

		
				for(vector<monster>::iterator it=env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
				{
					if((*it).isLive() && (*it).position.x == (*temp_beam).x && (*it).position.y == (*temp_beam).y &&
						!(*it).isPassedBullet(&you)
						)
					{
						beam = temp_beam;
						target = (*beam);
						block_ = true;
						break;
					}
				}
				if(block_)
				{
					break;
				}
			}
		}

		if(size == 1)
		{
			rect_iterator rit(target,1,1);
			for(;!rit.end();rit++)
			{
				if((*rit) == you.position)
				{
					warning_ = true;
					break;
				}
			}

		}
		if(size == 2)
		{		
			dif_rect_iterator rit(target,2);
			for(;!rit.end();rit++)
			{
				if((*rit) == you.position)
				{
					warning_ = true;
					break;
				}
			}
		}

		if(warning_)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_SELF_HURT),false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				break;
			case 'N':
			default:
				printlog(" " + LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE),true,false,false,CL_normal);
				return false;
			}

		}
	}



	return true;
}





bool PlayerUseSpell(spell_list skill, bool short_, coord_def &target)
{
	int power=you.GetSpellPower(SpellSchool(skill,0),SpellSchool(skill,1),SpellSchool(skill,2));
	
	
	power=min(SpellCap(skill),max(0,power));

	if(!CheckDangerSpell(SpellMiscastingLevel(SpellLevel(skill),100-you.GetSpellSuccess(skill))))
	{
		return false;
	}
	if(!CheckSucide(you.position,target,SpellFlagCheck(skill,S_FLAG_SEIF) || SpellFlagCheck(skill, S_FLAG_IMMEDIATELY),Spellsize(skill),SpellFlagCheck(skill,S_FLAG_SMITE)))
	{
		return false;
	}
	if(!you.isSightnonblocked(target))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_BLOCK),true,false,false,CL_normal);	
		return false;
	}
	if(SpellFlagCheck(skill,S_FLAG_DELAYED) && you.GetExhausted())
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_EXHAUST),true,false,false,CL_normal);	
		return false;
	}
	if(randA_1(100) > you.GetSpellSuccess(skill))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CAST_FAIL),true,false,false,CL_normal);
		SpellMiscasting(SpellMiscastingLevel(SpellLevel(skill),100-you.GetSpellSuccess(skill)));
		return true;
	}
	if(you.GetPunish(GT_MIMA))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_PUNISH_SPELLDOWN),true,false,false,CL_green);
	}

	if(wiz_list.wizard_mode == 1)
	{
		printlog(LocalzationManager::formatString(LOC_SYSTEM_DEBUG_SPELLPOWER,PlaceHolderHelper(to_string(power)),PlaceHolderHelper(to_string(SpellCap(skill)))),true,false,false,CL_help);
	}
	switch(skill)
	{
	case SPL_MON_TANMAC_SMALL:
		return skill_tanmac_small(power,short_,&you,target);
	case SPL_MON_TANMAC_MIDDLE:
		return skill_tanmac_middle(power,short_,&you,target);
	case SPL_MON_WATER_GUN:
		return skill_water_gun(power,short_,&you,target);
	case SPL_FLAME:
		return skill_flame(power,short_,&you,target);
	case SPL_FROST:
		return skill_frost(power,short_,&you,target);
	case SPL_MEDICINE_CLOUD:
		return skill_medicine_cloud(power,short_,&you,target);
	case SPL_COLD_BEAM:
		return skill_cold_beam(power,short_,&you,target);
	case SPL_SUMMON_BUG:
		return skill_summon_bug(power,short_,&you,target);
	case SPL_CONFUSE:
		return skill_confuse(power,short_,&you,target);
	case SPL_SLOW:
		return skill_slow(power,short_,&you,target);
	case SPL_SELF_HEAL:
		return skill_self_heal(power,short_,&you,target);
	case SPL_BLINK:
		return skill_blink(power,short_,&you,target);
	case SPL_SMITE:
		return skill_smite(power,short_,&you,target);
	case SPL_BURN:
		return skill_burn(power,short_,&you,target);
	case SPL_FIRE_WALL:
		return skill_fire_wall(power,short_,&you,target);
	case SPL_FROZEN:
		return skill_frozen(power,short_,&you,target);
	case SPL_FREEZE:
		return skill_freeze(power,short_,&you,target);
	case SPL_STING:
		return skill_sting(power,short_,&you,target);
	case SPL_CURE_POISON:
		return skill_cure_poison(power,short_,&you,target);
	case SPL_TWIST:
		return skill_twist(power,short_,&you,target);
	case SPL_SUMMON_MOOK:
		return skill_summon_mook(power,short_,&you,target);
	case SPL_FIRE_BRAND:
		return skill_fire_bread(power,short_,&you,target);
	case SPL_COLD_BRAND:
		return skill_cold_bread(power,short_,&you,target);
	case SPL_POISON_BRAND:
		return skill_poison_bread(power,short_,&you,target);
	case SPL_SHOCK:
		return skill_elec(power,short_,&you,target);
	case SPL_CHAIN_LIGHTNING:
		return skill_chain_lightning(power,short_,&you,target);
	case SPL_DISCHARGE:
		return skill_discharge(power,short_,&you,target);
	case SPL_LEVITATION:
		return skill_levitation(power,short_,&you,target);
	case SPL_GLOW:
		return skill_glow(power,short_,&you,target);
	case SPL_GRAZE:
		return skill_graze(power,short_,&you,target);
	case SPL_VEILING:
		return skill_veiling(power,short_,&you,target);
	case SPL_INVISIBLE:
		return skill_invisible(power,short_,&you,target);
	case SPL_HASTE:
		return skill_haste(power,short_,&you,target);
	case SPL_SILENCE:
		return skill_silence(power,short_,&you,target);
	case SPL_SWIFT:
		return skill_swift(power,short_,&you,target);
	case SPL_MAGIC_TANMAC:
		return skill_magic_tanmac(power,short_,&you,target);
	case SPL_FIRE_BALL:
		return skill_fire_ball(power,short_,&you,target);
	case SPL_FIRE_BOLT:
		return skill_fire_bolt(power,short_,&you,target);
	case SPL_ICE_BOLT:
		return skill_ice_bolt(power,short_,&you,target);
	case SPL_VENOM_BOLT:
		return skill_venom_bolt(power,short_,&you,target);
	case SPL_CONFUSE_CLOUD:
		return skill_confuse_cloud(power,short_,&you,target);
	case SPL_POISON_CLOUD:
		return skill_poison_cloud(power,short_,&you,target);
	case SPL_ICE_CLOUD:
		return skill_ice_cloud(power,short_,&you,target);
	case SPL_SUMMON_BIRD:
		return skill_summon_bird(power,short_,&you,target);
	case SPL_RECALL:
		return skill_recall(power,short_,&you,target);
	case SPL_TELEPORT_OTHER:
		return skill_teleport_other(power,short_,&you,target);
	case SPL_TELEPORT_SELF:
		return skill_teleport_self(power,short_,&you,target);
	case SPL_WHIRLWIND:
		return skill_whirlwind(power,short_,&you,target);
	case SPL_SUMMON_PENDULUM:
		return skill_summon_pendulum(power,short_,&you,target);
	case SPL_SUMMON_SEKIBANKI:
		return skill_summon_sekibanki(power,short_,&you,target);
	case SPL_WATER_CANNON:
		return skill_water_cannon(power,short_,&you,target);
	case SPL_KYOKO_SMITE:
		return skill_kyoko_smite(power,short_,&you,target);
	case SPL_SUMMON_OPTION:
		return skill_summon_option(power,short_,&you,target);
	case SPL_SUMMON_GOLEM:
		return skill_summon_golem(power,short_,&you,target);
	case SPL_HYPNOSIS:
		return skill_hypnosis(power,short_,&you,target);
	case SPL_MUTE:
		return skill_mute(power,short_,&you,target);
	case SPL_SELF_INJURY:
		return skill_self_injury(power,short_,&you,target);
	case SPL_CHARM:
		return skill_charm(power,short_,&you,target);
	case SPL_LASER:
		return skill_laser(power,short_,&you,target);
	case SPL_SPARK:
		return skill_spark(power,short_,&you,target);
	case SPL_SUMMON_UNZAN:
		return skill_summon_unzan(power,short_,&you,target);
	case SPL_SUMMON_UNZAN_PUNCH:
		return skill_summon_unzan_punch(power,short_,&you,target);
	case SPL_SUMMON_ZOMBIE_FAIRY:
		return skill_summon_zombie_fairy(power,short_,&you,target);
	case SPL_SUMMON_UFO:
		return skill_summon_ufo(power,short_,&you,target);
	case SPL_HASTE_OTHER:
		return skill_haste_other(power,short_,&you,target);
	case SPL_HEAL_OTHER:
		return skill_heal_other(power,short_,&you,target);
	case SPL_MIND_BENDING:
		return skill_mind_bending(power,short_,&you,target);
	case SPL_STONE_PUNCH:
		return skill_stone_punch(power,short_,&you,target);
	case SPL_STONE_ARROW:
		return skill_stone_arrow(power,short_,&you,target); 
	case SPL_STONE_TRAP:
		return skill_stone_trap(power,short_,&you,target);
	case SPL_STONE_UPLIFT:
		return skill_stone_uplift(power,short_,&you,target);
	case SPL_KANAME_DRILL:
		return skill_kaname_drill(power,short_,&you,target);
	case SPL_DIAMOND_HARDNESS:
		return skill_diamond_hardness(power,short_,&you,target);
	case SPL_POISON_SKIN:
		return skill_poison_skin(power,short_,&you,target);
	case SPL_STONE_FORM:
		return skill_stone_form(power,short_,&you,target);
	case SPL_KNIFE_COLLECT:
		return skill_knife_collect(power,short_,&you,target);
	case SPL_FLAN_BUSIN:
		return skill_summon_flandre(power,short_,&you,target);
	case SPL_BURST:
		return skill_burst(power,short_,&you,target);
	case SPL_SUICIDE_BOMB:
		return skill_suicide_bomb(power,short_,&you,target);
	case SPL_RABBIT_HORN:
		return skill_rabbit_horn(power,short_,&you,target);
	case SPL_SUMMON_LESSOR_DEMON:
		return skill_summon_lessor_demon(power,short_,&you,target);	
	case SPL_LUMINUS_STRIKE:
		return skill_luminus_strike(power,short_,&you,target);
	case SPL_FIRE_STORM:
		return skill_fire_storm(power,short_,&you,target);
	case SPL_BLIZZARD: 
		return skill_blizzard(power,short_,&you,target);
	case SPL_PERFERT_FREEZE: 
		return skill_perfect_freeze(power,short_,&you,target);
	case SPL_DRAW_POWER:
		return skill_draw_power(power,short_,&you,target);
	case SPL_ANIMAL_CHANGE:
		return skill_animal_change(power,short_,&you,target);
	case SPL_FIELD_VIOLET:
		return skill_field_violet(power,short_,&you,target);
	case SPL_TIME_PARADOX: 
		return skill_time_paradox(power,short_,&you,target);
	case SPL_PRIVATE_SQ: 
		return skill_private_sq(power,short_,&you,target);
	case SPL_CONTROLED_BLINK: 
		return skill_controled_blink(power,short_,&you,target);
	case SPL_THE_WORLD:	
		return skill_the_world(power,short_,&you,target);	
	case SPL_HASTE_ALL:
		return skill_haste_all(power,short_,&you,target);
	case SPL_HEAL_ALL:	
		return skill_heal_all(power,short_,&you,target);	
	case SPL_MOON_COMMUNICATION:
		return skill_moon_communication(power,short_,&you,target);	
	case SPL_MOON_GUN:
		return skill_moon_gun(power,short_,&you,target);	
	case SPL_SUMMON_DREAM:
		return skill_summon_dream(power,short_,&you,target);	
	case SPL_MANA_DRAIN:
		return skill_mana_drain(power,short_,&you,target);	
	case SPL_INSANE:
		return skill_insane(power,short_,&you,target);	
	case SPL_BLOOD_SMITE:
		return skill_blood_smite(power,short_,&you,target);	
	case SPL_CALL_HOUND:
		return skill_call_hound(power,short_,&you,target);	
	case SPL_CANNON:
		return skill_canon(power,short_,&you,target);	
	case SPL_DOLLS_WAR:
		return skill_dolls_war(power,short_,&you,target);	
	case SPL_FAKE_DOLLS_WAR:
		return skill_fake_dolls_war(power,short_,&you,target);	
	case SPL_FIRE_SPREAD:
		return skill_fire_spread(power,short_,&you,target);	
	case SPL_STASIS:
		return skill_stasis(power,short_,&you,target);	
	case SPL_JUMP_ATTACK:
		return skill_jump_attack(power,short_,&you,target);
	case SPL_ALERT_NOISE: 
		return skill_alert_noise(power, short_, &you, target);
	case SPL_SUMMON_NAMAZ:
		return skill_summon_namaz(power,short_,&you,target);
	case SPL_SCHEMA_TANMAC:
		return skill_schema_tanmac(power,short_,&you,target);
	case SPL_CHANGE:
		return skill_change(power,short_,&you,target);
	case SPL_UNLUCK:
		return skill_unluck(power,short_,&you,target);	
	case SPL_THUNDER:
		return skill_thunder(power,short_,&you,target);	
	case SPL_AIR_STRIKE:
		return skill_air_strike(power,short_,&you,target);	
	case SPL_SUMMON_RACOON:
		return skill_summon_racoon(power,short_,&you,target);	
	case SPL_SUMMON_YOUKAI:
		return skill_summon_youkai(power,short_,&you,target);	
	case SPL_MAMIZO_EVADE:
		return skill_mamizo_evade(power,short_,&you,target);	
	case SPL_MACRO_BURST:
		return skill_macro_burst(power,short_,&you,target);	
	case SPL_SHATTER:
		return skill_shatter(power,short_,&you,target);	
	case SPL_SUMMON_YOSHIKA:
		return skill_summon_yoshika(power,short_,&you,target);	
	case SPL_NESY_CANNON:
		return skill_nesy_cannon(power,short_,&you,target);	
	case SPL_MERMAID_SONG:
		return skill_mermaid_song(power,short_,&you,target);	
	case SPL_EMERALD_CITY:
		return skill_emerald_city(power,short_,&you,target);	
	case SPL_AUTUMN_BLADE:
		return skill_autumn_blade(power,short_,&you,target);	
	case SPL_PHILOSOPHERS_STONE:
		return skill_philosophers_stone(power,short_,&you,target);
	case SPL_SUMMON_ANCHOR:
		return skill_summon_anchor(power, short_, &you, target);
	case SPL_REAPER_MET:
		return skill_reaper_met(power, short_, &you, target);
	case SPL_AFTERLITE:
		return skill_afterlife(power, short_, &you, target);
	case SPL_PRISM_CALL:
		return skill_prism_call(power, short_, &you, target);
	case SPL_PSYCHOKINESIS:
		return skill_psychokinesis(power, short_, &you, target);
	case SPL_SUMMON_TRASH:
		return skill_summon_trash(power, short_, &you, target);
	case SPL_TRASH_RUSH:
		return skill_trash_rush(power, short_, &you, target);
	case SPL_KOKORO_CHANGE:
		return skill_kokoro_roulette(power, short_, &you, target);
	case SPL_THUNDER_BOLT:
		return skill_thunder_bolt(power, short_, &you, target);
	case SPL_SANTUARY:
		return skill_santuary(power, short_, &you, target);
	case SPL_MISTIA_SONG:
		return skill_mistia_song(power, short_, &you, target);
	case SPL_THROW_DISH:
		return skill_throw_dish(power, short_, &you, target);
	case SPL_MESS_CONFUSION:
		return skill_mess_confusion(power, short_, &you, target);
	case SPL_SLEEP_SMITE:
		return skill_sleep_smite(power, short_, &you, target);
	case SPL_TARGET_ELEC:
		return skill_target_elec(power, short_, &you, target);
	case SPL_SUMMON_ELEC_BALL:
		return skill_summon_elec_ball(power, short_, &you, target);
	case SPL_DREAM_CALL:
		return skill_dream_call(power, short_, &you, target);
	case SPL_HYPER_BEAM:
		return skill_hyper_beam(power, short_, &you, target);
	case SPL_KAGUYA_SPELL:
		return skill_kaguya_spell(power, short_, &you, target);
	case SPL_THROW_SWORD:
		return skill_throw_sword(power, short_, &you, target);
	case SPL_THROW_KNIFE:
		return skill_throw_knife(power, short_, &you, target);
	case SPL_THROW_PLAYER:
		return skill_throw_player(power, short_, &you, target);
	case SPL_THROW_AMULET:
		return skill_throw_amulet(power, short_, &you, target);
	case SPL_WARP_KICK:
		return skill_warp_kick(power, short_, &you, target);
	case SPL_REIMU_BARRIER:
		return skill_reimu_barrier(power, short_, &you, target);
	default:
		return false;
	}
}

