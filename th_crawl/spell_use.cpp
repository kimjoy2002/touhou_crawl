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
#include <algorithm>
#include <math.h>

extern bool wizard_mode;


bool isMonsterhurtSpell(monster* use_, monster* target_, spell_list spell_)
{
	//이 마법이 이 몬스터에게 제대로 듣는지
	//true면 되도록 마법을 쓰는걸 피한다.
	//false면 무시하고 쏜다. (공격이 안 듣거나 자신에 비해서 너무 약하거나)

	if(use_->level - target_->level >= 5)
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
		}
	} 
	
	//각 속성공격에 해당되는데 해당 저항이 없는 경우 위험한 공격임
	if(resist_[RST_POISON] && target_->poison_resist<=0)
		return true;
	if(resist_[RST_ELEC] && target_->elec_resist<=1)
		return true;
	if(resist_[RST_FIRE] && target_->fire_resist<=1)
		return true;
	if(resist_[RST_ICE] && target_->ice_resist<=1)
		return true;

	return false; 

}


bool isBandAlly(monster* order, monster* other)
{//예네들이 협력하는지(버프를 같이 받는지)
	//즉 order가 other에게 버프를 주느지 확인
	//나중엔 자리를 바꿀 수 있는지 등도 고려
	//현재는 버프만 적용이므로 버프쓰는 몹만 고려

	switch(order->id)
	{
	case MON_FAIRY_RED_COMMANDER:
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

	if(SpellLength(skill) && length_ > SpellLength(skill)*SpellLength(skill))
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
					i++;
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
				if(!SpellFlagCheck(skill, S_FLAG_SMITE))
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
	else if(!SpellFlagCheck(skill, S_FLAG_SMITE))
	{
		beam_iterator beam(order->position,order->position);
		if(!CheckThrowPath(order->position,target, beam))
			return false;
		
		for(beam.init();!beam.end();beam++)
		{
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
		}
	}
	else if(SpellFlagCheck(skill, S_FLAG_SMITE))
	{
		beam_iterator beam(order->position,order->position);
		if(!CheckThrowPath(order->position,target, beam))
			return false;
	}
	return true;
}


void BaseBomb(coord_def pos, textures* t_ , attack_infor& att_)
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
		if(summon_check(coord_def(rit->x,rit->y), order, mondata[id_].flag & M_FLAG_FLY, mondata[id_].flag & M_FLAG_SWIM))
		{
			int flag_=M_FLAG_SUMMON;
			if(order->GetParentType() == PRT_PLAYER || order->GetParentType() == PRT_ALLY)
				flag_ |= M_FLAG_ALLY;
			summon_info s_(order->GetMapId(),kind_,max_num_);
			mon_=env[current_level].AddMonster_Summon(id_,flag_,(*rit),s_,time_); //파워에 따라서 조정하기
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
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randA_1(1+pow/3),1+pow/3,17,order,order->GetParentType(),SpellLength(SPL_MON_TANMAC_SMALL),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("탄막",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(rand_int(10,15),beam,temp_infor,NULL);
		return true;
	}
	return false;
}

bool skill_tanmac_middle(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(2,8+pow/8),2*(8+pow/8),14,order,order->GetParentType(),SpellLength(SPL_MON_TANMAC_SMALL),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("탄막",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(rand_int(10,15),beam,temp_infor,NULL);
		return true;
	}
	return false;
}
bool skill_water_gun(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(1,15+pow/4),15+pow/4,12,order,order->GetParentType(),SpellLength(SPL_MON_WATER_GUN),1,BMT_NORMAL,ATT_THROW_WATER,name_infor("물총",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(14,beam,temp_infor,NULL);
		return true;
	}
	return false;
}
bool skill_burn(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(1,12+pow/6),12+pow/6,13,order,order->GetParentType(),SpellLength(SPL_BURN),1,BMT_NORMAL,ATT_THROW_FIRE,name_infor("불꽃",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(17,beam,temp_infor,NULL);
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
		beam_infor temp_infor(randC(1,damage_),damage_,15+pow/15,order,order->GetParentType(),SpellLength(SPL_FLAME),1,BMT_NORMAL,ATT_THROW_FIRE,name_infor("불꽃",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(17,beam,temp_infor,NULL);
		return true;
	}
	return false;
}
bool skill_frozen(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(1,8+pow/6),8+pow/6,99,order,order->GetParentType(),SpellLength(SPL_FROZEN),1,BMT_NORMAL,ATT_THROW_COLD,name_infor("냉기",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(19,beam,temp_infor,NULL);
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
		int damage_ = 13+pow/5-mon_panlty_;
		beam_infor temp_infor(randC(1,damage_),damage_,16+pow/15,order,order->GetParentType(),SpellLength(SPL_FLAME),1,BMT_NORMAL,ATT_THROW_COLD,name_infor("냉기",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(19,beam,temp_infor,NULL); 
		return true;
	}
	return false;
}
bool skill_freeze(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(2,8+pow/6),2*(8+pow/6),99,order,order->GetParentType(),SpellLength(SPL_FREEZE),1,BMT_NORMAL,ATT_THROW_FREEZING,name_infor("냉기",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(19,beam,temp_infor,NULL);
		return true;
	}
	return false;
}
bool skill_sting(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(1,5+pow/6),5+pow/6,13,order,order->GetParentType(),SpellLength(SPL_STING),1,BMT_NORMAL,ATT_THROW_WEAK_POISON,name_infor("독탄막",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(20,beam,temp_infor,NULL); 
		return true;
	}
	return false;
}
bool skill_medicine_cloud(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		MakeCloud(target, img_fog_slow, SMT_SLOW, rand_int(8,10), 4+pow/10,0,5, order);
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
				printlog("이미 누군가 있는 위치에 사용할 수 없습니다.",true,false,false,CL_small_danger);
			return false;
		}
		if(env[current_level].isSmokePos(target.x,target.y))
		{
			if(order->isplayer())
				printlog("구름이 존재하는 곳에 사용할 수 없습니다.",true,false,false,CL_small_danger);
			return false;
		}
		env[current_level].MakeSmoke(target, img_fog_fire, SMT_FIRE, rand_int(7,13)+pow/4,  0, order);
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
				printlog("구름이 존재하는 곳에 사용할 수 없습니다.",true,false,false,CL_small_danger);
			return false;
		}
		env[current_level].MakeSmoke(target, img_fog_normal, SMT_TWIST, rand_int(3,8)+pow/5,  0, order);
		return true;
	}
	return false;
}
bool skill_cold_beam(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(3,4+pow/9),3*(4+pow/9),18,order,order->GetParentType(),SpellLength(SPL_COLD_BEAM),8,BMT_PENETRATE,ATT_THROW_COLD,name_infor("냉동빔",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(18,beam,temp_infor,NULL); //얼음탄막 모양 하나 더 만들고 바꾸기
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
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
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
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
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
			printlog("독이 치료되었다.",true,false,false,CL_normal);
			player_pointer->s_poison = 0;
		}
		else
		{
			printlog("독이 걸려있을때만 사용할 수 있다.",true,false,false,CL_small_danger);
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
		attack_infor temp_att(randA_1(10+pow/8),10+pow/8,99,order,order->GetParentType(),ATT_SMITE,name_infor("강타",false));
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
	return return_;

}
bool skill_fire_bread(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
		{
			printarray(true,false,false,CL_white_blue,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"불타오르기 시작했다.");
			you.equipment[ET_WEAPON]->value5 = WB_FIRE;
			you.equipment[ET_WEAPON]->value6 = rand_int(10,20)+pow/3;
		}
		else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_FIRE && you.equipment[ET_WEAPON]->value6>0)
		{
			printarray(true,false,false,CL_white_blue,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"더욱 더 불타오르기 시작했다.");
			you.equipment[ET_WEAPON]->value6 += rand_int(8,12)+pow/5;
			if(you.equipment[ET_WEAPON]->value6>50)
				you.equipment[ET_WEAPON]->value6 = 50;
		}
		else
		{
			printlog("마법이 듣지 않는다.",true,false,false,CL_normal);
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
			printarray(true,false,false,CL_white_blue,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"냉기를 뿜기 시작했다.");
			you.equipment[ET_WEAPON]->value5 = WB_COLD;
			you.equipment[ET_WEAPON]->value6 = rand_int(10,20)+pow/3;
		}
		else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_COLD && you.equipment[ET_WEAPON]->value6>0)
		{
			printarray(true,false,false,CL_white_blue,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"더욱 냉기를 뿜기 시작했다.");
			you.equipment[ET_WEAPON]->value6 += rand_int(8,12)+pow/5;
			if(you.equipment[ET_WEAPON]->value6>50)
				you.equipment[ET_WEAPON]->value6 = 50;
		}
		else
		{
			printlog("마법이 듣지 않는다.",true,false,false,CL_normal);
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
			printarray(true,false,false,CL_white_blue,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"독을 떨어뜨리기 시작했다.");
			you.equipment[ET_WEAPON]->value5 = WB_POISON;
			you.equipment[ET_WEAPON]->value6 = rand_int(10,20)+pow/3;
		}
		else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_POISON && you.equipment[ET_WEAPON]->value6>0)
		{
			printarray(true,false,false,CL_white_blue,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"더욱 독이 진해졌다.");
			you.equipment[ET_WEAPON]->value6 += rand_int(8,12)+pow/5;
			if(you.equipment[ET_WEAPON]->value6>50)
				you.equipment[ET_WEAPON]->value6 = 50;
		}
		else
		{
			printlog("마법이 듣지 않는다.",true,false,false,CL_normal);
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

		if((*it).isLive())
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
		beam_infor temp_infor(randA_1(9+power/6),9+power/6,99,order,order->GetParentType(),SpellLength(SPL_SHOCK),1,BMT_NORMAL,ATT_THROW_ELEC,name_infor("전기",false));
		ThrowShock(21,order->position,hit_mon->position,temp_infor); 
		Sleep(120);
		env[current_level].ClearEffect();
		return true;
	}
	else
	{
		if(order->isplayer())
			printlog("쏠 방향에 전기가 통하는 적이 없다.",true,false,false,CL_normal);
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

		if((*it).isLive())
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
		beam_infor temp_infor(randA_1(8+power/6),8+power/6,99,order,order->GetParentType(),spell_length_,1,BMT_NORMAL,ATT_THROW_ELEC,name_infor("전기",false));
		ThrowShock(21,order->position,hit_mon->position,temp_infor); 
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

		if((*it).isLive())
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
		beam_infor temp_infor(randC(2,9+power*3/10),2*(9+power*3/10),99,order,order->GetParentType(),spell_length_,1,BMT_NORMAL,ATT_THROW_ELEC,name_infor("전기",false));
		if(ThrowShock(21,(*start),hit_mon->position,temp_infor))
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
		power =  power*4/5;
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
	textures* image_ = &img_fog_fire[0];
	switch(type)
	{
	case ATT_FIRE_BLAST:
	case ATT_BURST:
		image_ = &img_fog_fire[0];
		break;
	case ATT_COLD_BLAST:
		image_ = &img_fog_cold[0];
		break;		
	case ATT_NORMAL_BLAST:
		image_ = &img_fog_normal[0];
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
			if(abs(i)*abs(j)<ball_size && (env[current_level].isInSight(target+i)) && env[current_level].isMove(target.x+i,target.y+j,true))
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
	order->SetElec(15+pow/5);
	return true;
}

bool skill_levitation(int pow, bool short_, unit* order, coord_def target)
{
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
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
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
	order->SetVeiling(10+pow/7,12+pow/4);
	return true;
}

bool skill_invisible(int pow, bool short_, unit* order, coord_def target)
{
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
		int damage_ = 4+pow/3-mon_panlty_;
		beam_infor temp_infor(randA_1(damage_),damage_,99,order,order->GetParentType(),SpellLength(SPL_MAGIC_TANMAC),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("탄막",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));		
		throwtanmac(rand_int(10,15),beam,temp_infor,NULL);
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
		beam_infor temp_infor(0,0,15,order,order->GetParentType(),length_,1,BMT_NORMAL,ATT_THROW_NONE_MASSAGE,name_infor("화염구",false));
		coord_def pos = throwtanmac(16,beam,temp_infor,NULL);
		attack_infor temp_att(randC(3,6+power/12),3*(6+power/12),99,order,order->GetParentType(),ATT_FIRE_BLAST,name_infor("화염구",false));
		BaseBomb(pos, &img_fog_fire[0],temp_att);
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
		int damage_ = 9+pow/7-mon_panlty_;
		beam_infor temp_infor(randC(3,damage_),3*(damage_),19+pow/25,order,order->GetParentType(),SpellLength(SPL_FIRE_BOLT),8,BMT_PENETRATE,ATT_THROW_FIRE,name_infor("화염",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(16,beam,temp_infor,NULL);
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
		int damage_ = 9+pow/7-mon_panlty_;
		beam_infor temp_infor(randC(3,damage_),3*(damage_),19+pow/25,order,order->GetParentType(),SpellLength(SPL_ICE_BOLT),8,BMT_PENETRATE,ATT_THROW_COLD,name_infor("냉기",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(22,beam,temp_infor,NULL);
		return true;
	}
	return false;
}
bool skill_venom_bolt(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(3,6+pow/7),3*(6+pow/7),19,order,order->GetParentType(),SpellLength(SPL_VENOM_BOLT),8,BMT_PENETRATE,ATT_THROW_MIDDLE_POISON,name_infor("맹독",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(23,beam,temp_infor,NULL);
		return true;
	}
	return false;
}
bool skill_confuse_cloud(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	int length_ = ceil(sqrt(pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2)));
	length_ = min(length_,SpellLength(SPL_FIRE_BALL));
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(0,0,10,order,order->GetParentType(),length_,1,BMT_PENETRATE,ATT_THROW_NONE_MASSAGE,name_infor("악취탄",true));
		coord_def pos = throwtanmac(20,beam,temp_infor,NULL, false);
		{
			for(int i=-1;i<=1;i++)
				for(int j=-1;j<=1;j++)
					if(env[current_level].isMove(pos.x+i,pos.y+j,true))
						env[current_level].MakeEffect(coord_def(pos.x+i,pos.y+j),&img_fog_poison[0],false);
			for(int i=-1;i<=1;i++)
				for(int j=-1;j<=1;j++)
						env[current_level].MakeSmoke(coord_def(pos.x+i,pos.y+j),img_fog_poison,SMT_CONFUSE,rand_int(6,12)+randA(power/15),0,&you);

			Sleep(300);
			env[current_level].ClearEffect();

		}
		return true;
	}
	return false;
}
bool skill_poison_cloud(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		MakeCloud(target, img_fog_poison, SMT_POISON, rand_int(8,10), rand_int(7,10)+randA(pow/10),0,5, order);
		return true;
	}
	return false;
}
bool skill_ice_cloud(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
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
	random_shuffle(dq.begin(),dq.end());
	dif_rect_iterator rit(order->position,2);
	int j=0;
	for(int i = 0;!rit.end() && i < dq.size();rit++)
	{
		if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
		{
			dq[i]->SetXY(rit->x,rit->y);
			if(dq[i]->isYourShight())
			{
				printarray(false,false,false,CL_normal,3,dq[i]->GetName()->name.c_str(),dq[i]->GetName()->name_is(true),"리콜되었다.");
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
	if(unit* hit_mon = DebufBeam(SPL_TELEPORT_OTHER, order, target))
	{
		if(hit_mon->CalcuateMR(GetDebufPower(SPL_TELEPORT_OTHER,pow)))
		{
			hit_mon->SetTele(rand_int(3,6));
		}
		else if(hit_mon->isYourShight())
		{					
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}

bool skill_teleport_self(int pow, bool short_, unit* order, coord_def target)
{
	order->SetTele(rand_int(3,6));
	return true;
}


bool skill_whirlwind(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		MakeCloud(target, img_fog_normal, SMT_WHIRLWIND, rand_int(8,10), 3+pow/20,0,5, order);
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
	return return_;

}
bool skill_water_cannon(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(3,5+pow/6),3*(5+pow/6),18,order,order->GetParentType(),SpellLength(SPL_WATER_CANNON),1,BMT_NORMAL,ATT_THROW_WATER,name_infor("수압",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
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
				beam++;
				knockback--;
			}
			if(real_knock_)
			{
				printarray(true,false,false,CL_normal,3,unit_->GetName()->name.c_str(),unit_->GetName()->name_is(true),"튕겨져나갔다.");
			}
		}
		return true;
	}
	return false;
}
bool skill_kyoko_smite(int pow, bool short_, unit* order, coord_def target)
{	
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);
	
	if(target_unit)
	{
		attack_infor temp_att(randA_1(10+pow/4),10+pow/4,99,order,order->GetParentType(),ATT_NOISE,name_infor("굉음",false));
		target_unit->damage(temp_att, true);
		if(randA(10)==0)
			target_unit->SetConfuse(rand_int(5,12));
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
			mon_->LevelUpdown(pow/20);
			return_ = true;
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
				attack_infor temp_att(randC(1,13+pow/6),(13+pow/6),99,NULL,order->GetParentType(),ATT_WALL,name_infor("충돌",true));
				hit_mon->damage(temp_att, true);
			}
			else if(unit_)
			{ //유닛에 부딪히면 둘에게 데미지
				{
					attack_infor temp_att(randC(1,13+pow/6),(13+pow/6),99,unit_,order->GetParentType(),ATT_WALL,name_infor("충돌",true));
					hit_mon->damage(temp_att, true);
				}				
				{
					attack_infor temp_att(randC(1,6+pow/8),(6+pow/8),99,hit_mon,order->GetParentType(),ATT_WALL,name_infor("충돌",true));
					unit_->damage(temp_att, true);
				}
			}
			else
			{
				printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"최면에 걸린채로 움직였다.");
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
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
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
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
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
					printlog("자고 있는 몹은 자해할 수 없다.",true,false,false,CL_normal);
					return false; 
				}
				if(mon_->flag & M_FLAG_NO_ATK){ //공격못하는애가 자해할리가
					
					printlog("이 몬스터는 스스로를 공격할 수 없다.",true,false,false,CL_normal);	
					return false;
				}

				int num_=0;
				for(int i=0;i<3;i++,num_++)
					if(mon_->atk_type[i] == ATT_NONE)
						break;		
				num_ = randA(num_-1);

				int damage_ = 3 + mon_->GetAttack(num_,true);
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
				damage_*=2.5f;
				attack_infor temp_att(damage_,2.5f*you.GetAttack(true),
					99,&you,order->GetParentType(),brand_,name_infor("공격",true));					
				hit_mon->damage(temp_att, true);

			}
		}
		else if(hit_mon->isYourShight())
		{					
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
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
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
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
		beam_infor temp_infor(randC(2,5+pow/8),2*(5+pow/8),18,order,order->GetParentType(),SpellLength(SPL_LASER),8,BMT_PENETRATE,ATT_THROW_NORMAL,name_infor("레이저",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(rand_int(10,15),beam,temp_infor,NULL);
		return true;
	}
	return false;
}

bool skill_spark(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randC(5,5+pow/20),5*(5+pow/20),99,order,order->GetParentType(),SpellLength(SPL_SPARK),8,BMT_PENETRATE,ATT_THROW_FIRE,name_infor("스파크",false));
		ThrowSector(rand_int(10,15),beam,temp_infor,GetSpellSector(SPL_SPARK),[&](coord_def c_){
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
	random_shuffle(target_mon_list.begin(),target_mon_list.end());

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
	random_shuffle(target_mon_list.begin(),target_mon_list.end());

	monster* final_target = target_mon_list.back();
	
	final_target->HpUpDown(rand_int(2+pow/10,10+pow/5),DR_NONE);
	printarray(true,false,false,CL_normal,3,final_target->GetName()->name.c_str(),final_target->GetName()->name_is(true),"회복되었다.");

	return true;

}
bool skill_mind_bending(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randA_1(10+pow/25),10+pow/25,17,order,order->GetParentType(),SpellLength(SPL_MIND_BENDING),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("탄막",true));
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
				printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
			}
			hit_mon->AttackedTarget(order);
		}
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
			printlog("무언가를 든 상태로 사용할 수 없다.",true,false,false,CL_normal);
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
		int damage_ = 17+pow/5.5-mon_panlty_;
		beam_infor temp_infor(randC(1,damage_),damage_,13+pow/15,order,order->GetParentType(),SpellLength(SPL_STONE_ARROW),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("돌멩이",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(26,beam,temp_infor,NULL);
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
			printlog("이 위치에는 깔 수 없다.",true,false,false,CL_normal);
			return false;
		}

		if(order == &you)
			printlog("당신은 바닥에 뾰족한 바위를 깔았다.",true,false,false,CL_normal);
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
						env[current_level].MakeEffect(*rit,&img_fog_normal[0],false);
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
					hit_->damage(attack_infor(randC(3,8+pow/14),3*(8+pow/14),99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor("바위",false)), true);
		
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
		beam_infor temp_infor(randC(3,11+pow/6),3*(11+pow/6),13+pow/20,order,order->GetParentType(),SpellLength(SPL_KANAME_DRILL),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("카나메드릴",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		throwtanmac(28,beam,temp_infor,NULL);
		return true;
	}
	return false;
}
bool skill_diamond_hardness(int pow, bool short_, unit* order, coord_def target)
{
	if(order == &you)
	{
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
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);

	if(env[current_level].isMove(target.x, target.y))
	{
		vector<coord_def> vt_;
		{
			rect_iterator rit(target,1,1);
			for(;!rit.end();rit++)
			{
				if(randA(randA(90))<pow || (*rit) == target)
				{
					if(env[current_level].isMove(rit->x,rit->y))
					{
						env[current_level].MakeEffect(*rit,&img_fog_fire[0],false);
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
					if(hit_->GetId() != MON_FLAN && hit_->GetId() != MON_FLAN_BUNSIN) //플랑은 면역(나중에 폭팔면역추가?)
						hit_->damage(attack_infor(randC(3,6+pow/18),3*(6+pow/18),99,order,order->GetParentType(),ATT_BURST,name_infor("폭발",true)), true);
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
	return return_;

}
bool skill_suicide_bomb(int power, bool short_, unit* order, coord_def target)
{
	if(1)
	{
		
		textures* t_ = &img_fog_fire[0];
		{
			dif_rect_iterator rit(order->position,2);
		
			for(;!rit.end();rit++)
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if(env[current_level].isSight(*rit) && you.isSightnonblocked(*rit))
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
					if(env[current_level].isInSight(*rit) && you.isSightnonblocked(*rit))
					{
						if(unit* hit_ = env[current_level].isMonsterPos(rit->x,rit->y))
						{	
							if(hit_ != order)
							{
								int att_ = randC(4,13+power/20);
								int m_att_ = 4*(13+power/20);

								attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor("폭발",true));
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
			attack_infor temp_att(order->GetHp()/2,order->GetHp()/2,99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor("폭발",true));
			order->damage(temp_att, true);

		}
		return true;
	}
	return false;
}
bool skill_rabbit_horn(int pow, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isBamboo())
	{
		if(map_list.bamboo_rate<((order->GetId() == MON_TEWI)?400:300))
			map_list.bamboo_rate+=order->GetId() == (MON_TEWI?40:20);
		if(order->GetId() == MON_TEWI)
			printlog("테위가 큰소리로 토끼들을 모으고 있다.",false,false,false,CL_small_danger);
		else
			printlog("큰 나팔소리가 토끼들을 끌어모으고 있다.",false,false,false,CL_small_danger);
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
	return return_;
}
void SetSpell(monster_index id, list<spell> *list)
{
	list->clear();
	switch(id)
	{
	case MON_FAIRY_GREEN:
		break;
	case MON_FAIRY_BLUE:
		list->push_back(spell(SPL_MON_TANMAC_SMALL,40));
		break;
	case MON_FAIRY_BLUE_MAGICIAN:
		list->push_back(spell(randA(1)?SPL_FROST:SPL_FLAME,40));
		list->push_back(spell(SPL_BLINK,15));
		break;
	case MON_FAIRY_RED_COMMANDER:
		list->push_back(spell(SPL_HASTE_OTHER,20));
		list->push_back(spell(SPL_HEAL_OTHER,20));
		break;
	case MON_KATPA_GUN:
		list->push_back(spell(SPL_MON_WATER_GUN,90));
		break;
	case MON_KYOUKO:
		list->push_back(spell(SPL_KYOKO_SMITE,50));
		break;
	case MON_CIRNO:
		list->push_back(spell(SPL_COLD_BEAM,15));
		break;
	case MON_WRIGGLE:
		list->push_back(spell(SPL_SUMMON_BUG,20));
		break;
	case MON_MEDICINE:
		list->push_back(spell(SPL_MEDICINE_CLOUD,30));
		break;
	case MON_DIEFAIRY:
		list->push_back(spell(SPL_BLINK,20));
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE,60));
		break;
	case MON_HUMAM_YINYANG:
		list->push_back(spell(SPL_FLAME,15));
		list->push_back(spell(SPL_FROST,15));
		list->push_back(spell(SPL_CONFUSE,5));
		list->push_back(spell(SPL_SLOW,5));
		list->push_back(spell(SPL_BLINK,20));
		break;
	case MON_HUMAM_PRIEST:
		list->push_back(spell(SPL_SMITE,20));
		list->push_back(spell(SPL_SELF_HEAL,10));
		break;
	case MON_CROW_TENGU:
		list->push_back(spell(SPL_GRAZE,30));
		list->push_back(spell(SPL_VEILING,20));
		break;
	case MON_SUNNY:
		list->push_back(spell(SPL_GLOW,10));
		list->push_back(spell(SPL_INVISIBLE,20));
		break;
	case MON_LUNAR:
		list->push_back(spell(SPL_SILENCE,25));
		break;
	case MON_STAR:
		list->push_back(spell(SPL_HASTE,25));
		break;
	case MON_KATPA_WATER_WIZARD:
		list->push_back(spell(SPL_FROST,20));
		list->push_back(spell(SPL_ICE_BOLT,10));
		list->push_back(spell(SPL_BLINK,10));
		list->push_back(spell(SPL_INVISIBLE,7));
		break;
	case MON_YAMABUSH_TENGU:
		list->push_back(spell(SPL_HASTE,20));
		list->push_back(spell(SPL_SMITE,20));
		list->push_back(spell(SPL_SELF_HEAL,10));
		break;
	case MON_SIGMUND:
		list->push_back(spell(SPL_FLAME,20));
		list->push_back(spell(SPL_CONFUSE,10));
		list->push_back(spell(SPL_INVISIBLE,20));
		list->push_back(spell(SPL_MAGIC_TANMAC,20));
		break;
	case MON_AYA:
		list->push_back(spell(SPL_HASTE,30));
		list->push_back(spell(SPL_WHIRLWIND,20));
		list->push_back(spell(SPL_GRAZE,20));
		list->push_back(spell(SPL_VEILING,20));
		list->push_back(spell(SPL_BLINK,20));
		break;
	case MON_WAKASAGI:
		list->push_back(spell(SPL_FROST,30));
		list->push_back(spell(SPL_COLD_BEAM,15));
		list->push_back(spell(SPL_CONFUSE,10));
		break;
	case MON_NAZRIN:
		list->push_back(spell(SPL_SUMMON_PENDULUM,30));
		list->push_back(spell(SPL_MAGIC_TANMAC,20));	
		break;
	case MON_SEKIBANKI_BODY:
		list->push_back(spell(SPL_SUMMON_SEKIBANKI,15));
		break;
	case MON_SEKIBANKI_HEAD:
		list->push_back(spell(SPL_FLAME,15));
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE,10));
		list->push_back(spell(SPL_BLINK,15));
		break;
	case MON_NITORI:
		list->push_back(spell(SPL_WATER_CANNON,20));
		list->push_back(spell(SPL_INVISIBLE,15));
		list->push_back(spell(SPL_MON_WATER_GUN,25));
		break;
	case MON_BENBEN:
		list->push_back(spell(SPL_SLOW,20));
		list->push_back(spell(SPL_BLINK,20));
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE,30));
		break;
	case MON_YATHASI:
		list->push_back(spell(SPL_CONFUSE,20));
		list->push_back(spell(SPL_BLINK,20));
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE,30));
		break;
	case MON_ORIN:
		list->push_back(spell(SPL_FIRE_BALL,20));
		list->push_back(spell(SPL_GRAZE,20));
		list->push_back(spell(SPL_SUMMON_ZOMBIE_FAIRY,10));
		break;
	case MON_ORIN_CAT:
		list->push_back(spell(SPL_BLINK,20));
		break;
	case MON_ICHIRIN:
		list->push_back(spell(SPL_SUMMON_UNZAN,50));
		break;
	case MON_UNZAN:
		list->push_back(spell(SPL_SUMMON_UNZAN_PUNCH,40));
		list->push_back(spell(SPL_LASER,15));
		break;
	case MON_PACHU:
		list->push_back(spell(SPL_HASTE,20));
		list->push_back(spell(SPL_FIRE_BOLT,15));
		list->push_back(spell(SPL_ICE_BOLT,15));
		list->push_back(spell(SPL_VENOM_BOLT,15));
		list->push_back(spell(SPL_CHAIN_LIGHTNING,15));
		list->push_back(spell(SPL_WATER_CANNON,30));
		list->push_back(spell(SPL_BLINK,20));
		break;
	case MON_MAGIC_BOOK:
		{
			int arr_[] = {SPL_FIRE_BOLT, SPL_ICE_BOLT, SPL_VENOM_BOLT, SPL_LASER, SPL_WATER_CANNON,
			SPL_STONE_ARROW, SPL_KANAME_DRILL, SPL_ICE_CLOUD, SPL_POISON_CLOUD, SPL_MIND_BENDING
			};
			//주 공격스킬
			int arr2_[] = {SPL_DISCHARGE, SPL_CONFUSE, SPL_SLOW, SPL_GRAZE, SPL_VEILING,
			SPL_HASTE, SPL_INVISIBLE, SPL_HYPNOSIS
			};
			//보조스킬

			list->push_back(spell(arr_[randA(9)],30));
			
			if(randA(10)<4)
			{
				if(randA(10)<7)
					list->push_back(spell(SPL_BLINK,15));
				else
					list->push_back(spell(arr2_[randA(7)],15));
			}
		}
		break;
	case MON_HOBGOBRIN_LIBRARIAN:
		list->push_back(spell(randA(1)?SPL_INVISIBLE:SPL_HASTE,20));
		list->push_back(spell(randA(1)?SPL_FROST:SPL_FLAME,20));
		list->push_back(spell(randA(1)?SPL_CONFUSE:SPL_SLOW,10));
		list->push_back(spell(randA(1)?SPL_VENOM_BOLT:SPL_FIRE_BALL,10));		
		break;
	case MON_HOBGOBRIN_TEMP:
		list->push_back(spell(SPL_SUMMON_LESSOR_DEMON,20)); //악마소환으로 바꾸기
		//list->push_back(spell(SPL_SUMMON_BIRD,20));
		list->push_back(spell(SPL_SMITE,10));
		break;
	case MON_KOAKUMA:
		list->push_back(spell(SPL_SUMMON_LESSOR_DEMON,10)); //악마소환으로 바꾸기
		list->push_back(spell(SPL_FIRE_BOLT,15));
		list->push_back(spell(SPL_BLINK,20));
		break;
	case MON_MAID_FAIRY:		
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE,30));
		break;
	case MON_SAKUYA:		
		list->push_back(spell(SPL_HASTE,20));
		list->push_back(spell(SPL_SLOW,10));
		list->push_back(spell(SPL_TELEPORT_OTHER,5));
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE,25));
		list->push_back(spell(SPL_BLINK,20));
		break;
	case MON_REMILIA:
		list->push_back(spell(SPL_HASTE,25));		
		break;
	case MON_DRAGON_BABY:
		list->push_back(spell(SPL_FIRE_BOLT,25));		
		break;
	case MON_KASEN:
		list->push_back(spell(SPL_SUMMON_BIRD,30));
		break;
	case MON_YAMAWARO_NINJA:
		list->push_back(spell(SPL_MON_TANMAC_MIDDLE,30));
		break;
	case MON_YAMAWARO_FLAG:		
		list->push_back(spell(SPL_SELF_HEAL,20));
		list->push_back(spell(SPL_HASTE_OTHER,20));
		break;
	case MON_MAGICAL_STAR:
		list->push_back(spell(SPL_MAGIC_TANMAC,15));
		break;
	case MON_KOISHI:
		list->push_back(spell(SPL_HYPNOSIS,30));
		list->push_back(spell(SPL_SELF_INJURY,20));
		list->push_back(spell(SPL_BLINK,20));
		break;
	case MON_NUE:
		list->push_back(spell(SPL_SUMMON_UFO,20));	
		list->push_back(spell(SPL_CHAIN_LIGHTNING,20));
		break;	
	case MON_EVIL_EYE:
		list->push_back(spell(SPL_SHOCK,10));
		break;
	case MON_ELIS:
		list->push_back(spell(SPL_BLINK,10));
		break;
	case MON_LUIZE:
		list->push_back(spell(SPL_ICE_BOLT,25));
		list->push_back(spell(SPL_SELF_HEAL,20));
		break;
	case MON_YUUGENMAGAN:
		list->push_back(spell(SPL_CHAIN_LIGHTNING,50));
		break;
	case MON_YUKI:		
		list->push_back(spell(SPL_ICE_CLOUD,25));
		list->push_back(spell(SPL_ICE_BOLT,25));
		list->push_back(spell(SPL_HASTE,15));
		break;
	case MON_MAI:		
		list->push_back(spell(SPL_FIRE_BALL,25));
		list->push_back(spell(SPL_FIRE_BOLT,25));
		list->push_back(spell(SPL_SMITE,15));
		break;
	case MON_SARIEL:
		list->push_back(spell(SPL_SUMMON_LESSOR_DEMON,30));
		list->push_back(spell(SPL_HASTE_OTHER,15));
		break;
	case MON_SCHEMA_EYE:
		list->push_back(spell(SPL_MAGIC_TANMAC,40));
		break;
	case MON_FLAN:
		list->push_back(spell(SPL_FLAN_BUSIN,30));
		list->push_back(spell(SPL_BURST,12));
		break;
	case MON_FLAN_BUNSIN:
		list->push_back(spell(SPL_BURST,18));
		break;
	case MON_RABIT_BOMB:
		list->push_back(spell(SPL_SUICIDE_BOMB,0));
		break;
	case MON_RABIT_SPEAR:
		break;
	case MON_RABIT_SUPPORT:
		list->push_back(spell(SPL_RABBIT_HORN,20));
		list->push_back(spell(SPL_HASTE_OTHER,30));
		break;
	case MON_RABIT_MAGIC:
		list->push_back(spell(SPL_FROST,25));
		list->push_back(spell(SPL_ICE_BOLT,20));
		list->push_back(spell(SPL_BLINK,30));
		break;
	case MON_TEWI:
		list->push_back(spell(SPL_RABBIT_HORN,15));
		break;
	case MON_CLOWNPIECE:
		list->push_back(spell(SPL_FIRE_BALL,10));
		list->push_back(spell(SPL_CONFUSE,5));
		break;
	case MON_DOREMI:
		list->push_back(spell(SPL_ICE_BOLT,20));
		list->push_back(spell(SPL_MIND_BENDING,20));
		break;
	default:
		break;
	}
}




bool MonsterUseSpell(spell_list skill, bool short_, monster* order, coord_def &target, int pow_)
{
	int power=min(SpellCap(skill),(order->level-3)*5);
	if(pow_ != -1)
		power = pow_;
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
	default:
		return false;
	}
}


bool PlayerUseSpell(spell_list skill, bool short_, coord_def &target)
{
	int power=min(SpellCap(skill),you.GetSpellPower(SpellSchool(skill,0),SpellSchool(skill,1),SpellSchool(skill,2)));
	if(target == you.position && !SpellFlagCheck(skill,S_FLAG_SEIF) && !SpellFlagCheck(skill, S_FLAG_IMMEDIATELY))
	{
		printlog("자살할거야?",true,false,false,CL_small_danger);	
		return false;
	}
	if(!you.isSightnonblocked(target))
	{
		printlog("여긴 막혀있다.",true,false,false,CL_normal);	
		return false;
	}
	if(randA_1(100) > you.GetSpellSuccess(skill))
	{
		printlog("당신은 마법 주문에 실패했다.",true,false,false,CL_normal);
		return true;
	}
	if(wizard_mode)
	{
		char temp[50];
		sprintf_s(temp,50,"스펠파워 %d / %d",power,SpellCap(skill));
		printlog(temp,true,false,false,CL_help);
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
	default:
		return false;
	}
}

