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
#include <algorithm>
#include <math.h>

extern bool wizard_mode;
extern HANDLE mutx;
extern int map_effect;

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
	case MON_FAIRY_SUN_FLOWER:
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
	else if(!SpellFlagCheck(skill, S_FLAG_SMITE))
	{
		beam_iterator beam(order->position,order->position);
		
		int max_length_ = SpellFlagCheck(skill, S_FLAG_PENETRATE)?SpellLength(skill):beam.GetMaxLength();
		if(!CheckThrowPath(order->position,target, beam))
			return false;
		
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
	else if(SpellFlagCheck(skill, S_FLAG_SMITE))
	{
		beam_iterator beam(order->position,order->position);
		if(!CheckThrowPath(order->position,target, beam))
			return false;
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
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(rand_int(10,15),beam,temp_infor,NULL);
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
		beam_infor temp_infor(randC(2,8+pow/8),2*(8+pow/8),14,order,order->GetParentType(),SpellLength(SPL_MON_TANMAC_SMALL),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("탄막",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		
		for(int i=0;i<(order->GetParadox()?2:1);i++)	
			throwtanmac(rand_int(10,15),beam,temp_infor,NULL);
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
		beam_infor temp_infor(randC(1,15+pow/4),15+pow/4,12,order,order->GetParentType(),SpellLength(SPL_MON_WATER_GUN),1,BMT_NORMAL,ATT_THROW_WATER,name_infor("물총",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(14,beam,temp_infor,NULL);
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
		beam_infor temp_infor(randC(1,12+pow/6),12+pow/6,13,order,order->GetParentType(),SpellLength(SPL_BURN),1,BMT_NORMAL,ATT_THROW_FIRE,name_infor("불꽃",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)	
			throwtanmac(17,beam,temp_infor,NULL);
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
		beam_infor temp_infor(randC(1,damage_),damage_,15+pow/15,order,order->GetParentType(),SpellLength(SPL_FLAME),1,BMT_NORMAL,ATT_THROW_FIRE,name_infor("불꽃",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)	
			throwtanmac(17,beam,temp_infor,NULL);
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
		beam_infor temp_infor(randC(1,8+pow/6),8+pow/6,99,order,order->GetParentType(),SpellLength(SPL_FROZEN),1,BMT_NORMAL,ATT_THROW_COLD,name_infor("냉기",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(19,beam,temp_infor,NULL);
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
		int damage_ = 13+pow/5-mon_panlty_;
		beam_infor temp_infor(randC(1,damage_),damage_,16+pow/15,order,order->GetParentType(),SpellLength(SPL_FROST),1,BMT_NORMAL,ATT_THROW_COLD,name_infor("냉기",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(19,beam,temp_infor,NULL); 
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
		attack_infor temp_att(randC(2,12+pow/6),2*(12+pow/6),99,order,order->GetParentType(),ATT_THROW_FREEZING,name_infor("냉기",false));
		target_unit->damage(temp_att, true);
		//beam_infor temp_infor(randC(2,8+pow/6),2*(8+pow/6),99,order,order->GetParentType(),SpellLength(SPL_FREEZE),1,BMT_NORMAL,ATT_THROW_FREEZING,name_infor("냉기",false));
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
		beam_infor temp_infor(randC(1,5+pow/6),5+pow/6,14+pow/15,order,order->GetParentType(),SpellLength(SPL_STING),1,BMT_NORMAL,ATT_THROW_WEAK_POISON,name_infor("독탄막",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(20,beam,temp_infor,NULL);
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
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(18,beam,temp_infor,NULL); //얼음탄막 모양 하나 더 만들고 바꾸기
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
	if(you.god == GT_YUKARI && order->isplayer())
	{
						
		printlog("유카리는 위험한 전이마법을 금지하고있다. 그래도 쓸건가?(Y/N)",false,false,false,CL_danger);
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			enterlog();
			break;
		case 'N':
		default:
			printlog(" 취소하였다.",true,false,false,CL_normal);
			return false;
		}
	}
	order->Blink(25);
	if(you.god == GT_YUKARI && order->isplayer())
	{
		printlog("유카리는 당신의 위험한 전이마법에 분노했다!",true,false,false,CL_small_danger);
		you.PietyUpDown(-5);
	}
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
	case ATT_FIRE_PYSICAL_BLAST:
		image_ = &img_fog_fire[0];
		break;
	case ATT_COLD_BLAST:
	case ATT_COLD_PYSICAL_BLAST:
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
		int damage_ = 5+pow/3-mon_panlty_;
		beam_infor temp_infor(randA_1(damage_),damage_,99,order,order->GetParentType(),SpellLength(SPL_MAGIC_TANMAC),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("탄막",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));		
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(rand_int(10,15),beam,temp_infor,NULL);	
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
		beam_infor temp_infor(0,0,15,order,order->GetParentType(),length_,1,BMT_NORMAL,ATT_THROW_NONE_MASSAGE,name_infor("화염구",false));

		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{
			coord_def pos = throwtanmac(16,beam,temp_infor,NULL);
			attack_infor temp_att(randC(3,6+power/12),3*(6+power/12),99,order,order->GetParentType(),ATT_FIRE_BLAST,name_infor("화염구",false));
			BaseBomb(pos, &img_fog_fire[0],temp_att);
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
		int damage_ = 9+pow/7-mon_panlty_;
		beam_infor temp_infor(randC(3,damage_),3*(damage_),18+pow/25,order,order->GetParentType(),SpellLength(SPL_FIRE_BOLT),8,BMT_PENETRATE,ATT_THROW_FIRE,name_infor("화염",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(16,beam,temp_infor,NULL);
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
		int damage_ = 9+pow/7-mon_panlty_;
		beam_infor temp_infor(randC(3,damage_),3*(damage_),18+pow/25,order,order->GetParentType(),SpellLength(SPL_ICE_BOLT),8,BMT_PENETRATE,ATT_THROW_COLD,name_infor("냉기",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(22,beam,temp_infor,NULL);
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
		beam_infor temp_infor(randC(3,6+pow/7),3*(6+pow/7),19,order,order->GetParentType(),SpellLength(SPL_VENOM_BOLT),8,BMT_PENETRATE,ATT_THROW_MIDDLE_POISON,name_infor("맹독",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(23,beam,temp_infor,NULL);
		order->SetParadox(0); 
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
		
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{
			
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
		
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{			
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
		attack_infor temp_att(randA_1(10+pow/4),10+pow/4,99,order,order->GetParentType(),ATT_NOISE,name_infor("굉음",false));
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
					if(order->isplayer())
						printlog("자고 있는 몹은 자해할 수 없다.",true,false,false,CL_normal);
					return false; 
				}
				if(mon_->flag & M_FLAG_NO_ATK){ //공격못하는애가 자해할리가
					
					if(order->isplayer())
						printlog("이 몬스터는 스스로를 공격할 수 없다.",true,false,false,CL_normal);	
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
		beam_infor temp_infor(randC(2,7+pow/8),2*(7+pow/8),18,order,order->GetParentType(),SpellLength(SPL_LASER),8,BMT_PENETRATE,ATT_THROW_NORMAL,name_infor("레이저",false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(rand_int(10,15),beam,temp_infor,NULL);
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
		beam_infor temp_infor(randC(5,9+pow/20),5*(9+pow/20),99,order,order->GetParentType(),SpellLength(SPL_SPARK),8,BMT_PENETRATE,ATT_NORMAL_BLAST,name_infor("스파크",false));
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
	if(env[current_level].isInSight(final_target->position))
		printarray(true,false,false,CL_normal,3,final_target->GetName()->name.c_str(),final_target->GetName()->name_is(true),"회복되었다.");

	return true;

}
bool skill_mind_bending(int pow, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randA_1(12+pow/25),12+pow/25,17+pow/15,order,order->GetParentType(),SpellLength(SPL_MIND_BENDING),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("탄막",true));
		
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{			
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
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(26,beam,temp_infor,NULL);
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
		beam_infor temp_infor(randC(3,15+pow/6),3*(15+pow/6),13+pow/20,order,order->GetParentType(),SpellLength(SPL_KANAME_DRILL),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("카나메드릴",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(28,beam,temp_infor,NULL);
		order->SetParadox(0); 
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
bool skill_luminus_strike(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	int length_ = ceil(sqrt(pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2)));
	length_ = min(length_,SpellLength(SPL_FIRE_BALL));
	if(CheckThrowPath(order->position,target,beam))
	{		
		float mon_panlty_ = order->isplayer()?1.0f:0.8f;//몬스터가 쓸때 패널티
		int damage_ = (11+power/6)*mon_panlty_;
		beam_infor temp_infor(randC(3,damage_),3*(damage_),99,order,order->GetParentType(),SpellLength(SPL_LUMINUS_STRIKE),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("광탄",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
		{			
			coord_def pos = throwtanmac(12,beam,temp_infor,NULL);	
			unit* hit_mon = env[current_level].isMonsterPos(pos.x,pos.y,order);
			int max_len_ = max(abs(order->position.x - pos.x),abs( order->position.y - pos.y));
			if(max_len_ >= 3)
			{
				attack_infor temp_att(randC(1,damage_),1*(damage_),99,order,order->GetParentType(),ATT_THROW_NORMAL,name_infor("폭발",true));
				BaseBomb(pos, &img_effect_tanmac_middle[2],temp_att,hit_mon);
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
		textures* t_ = &img_fog_fire[0];
		{
			dif_rect_iterator rit(target,2);
		
			for(;!rit.end();rit++)
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if((!order->isplayer() || env[current_level].isInSight(*rit)) && order->isSightnonblocked(*rit))
					{
						env[current_level].MakeEffect(*rit,t_,false);
					}
				}
		}
		
		printlog("화염폭풍이 터졌다!",false,false,false,CL_normal);
		{
			dif_rect_iterator rit(target,2);
		
			for(;!rit.end();rit++)
			{
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if((!order->isplayer() || env[current_level].isInSight(*rit)) && order->isSightnonblocked(*rit))
					{
						if(unit* hit_ = env[current_level].isMonsterPos(rit->x,rit->y))
						{	
							if(1/*hit_ != order*/)
							{
								int att_ = randC(9,10+power/20);
								int m_att_ = 9*(10+power/20);

								attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_FIRE_PYSICAL_BLAST,name_infor("화염폭풍",true));
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
		return true;
	}
	return false;
}
bool skill_blizzard(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isMove(target.x, target.y, true))
	{
		printlog("눈보라가 휘몰아친다! ",false,false,false,CL_normal);
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

						//		attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_FIRE_PYSICAL_BLAST,name_infor("화염폭풍",true));
						//		hit_->damage(temp_att, true);
						//	}
						//}
						env[current_level].MakeSmoke((*rit), img_blizzard, SMT_BLIZZARD, rand_int(5,10)+power/15,  0, order);
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

bool skill_perfect_freeze(int pow, bool short_, unit* order, coord_def target)
{
	map_effect = 1;
	Sleep(500);
	
	for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it!=env[current_level].mon_vector.end(); it++)
	{	
		if(it->isLive() && env[current_level].isInSight(it->position) && order->isSightnonblocked(it->position))
		{
			int att_ = 12+pow/15;
				
			attack_infor temp_att(randC(5,att_),5*(att_),99,order,order->GetParentType(),ATT_THROW_FREEZING,name_infor("냉기",false));
			it->damage(temp_att, true);
			
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
		char temp[200];
		sprintf_s(temp,200,"%d개의 P템을 한번에 회수했다.",p_tem);
		printlog(temp,true,false,false,CL_normal);
		return true;
	}
	else
	{
		printarray(true,false,false,CL_normal,1,"시야내에 P템이 없다.");
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
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"이미 동물이기에 변신에 걸리지않는다.");
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
				printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"동물로 변해버렸다!");
				
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
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
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
				printarray(true,false,false,CL_normal,1,"층마다 1개의 파장만 조종할 수 있다.");
			return false;
		}
	}
	printlog("보라색의 파장이 생겨났다! ",false,false,false,CL_normal);
	env[current_level].MakeEvent(EVL_VIOLET,coord_def(target.x,target.y),EVT_ALWAYS,rand_int(10,20)+power/10);
	return true;
}
bool skill_time_paradox(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
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
				printarray(true,false,false,CL_normal,3,it->GetName()->name.c_str(),it->GetName()->name_is(true),"저항했다.");
			}
			it->AttackedTarget(order);			
		}
	}
	return true;
}

bool skill_controled_blink(int pow, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;
	if(you.god == GT_YUKARI)
	{
						
		printlog("유카리는 위험한 전이마법을 금지하고있다. 그래도 쓸건가?(Y/N)",false,false,false,CL_danger);
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			enterlog();
			break;
		case 'N':
		default:
			printlog(" 취소하였다.",true,false,false,CL_normal);
			return false;
		}
	}

	if(you.control_blink(you.search_pos))
	{
		if(you.god == GT_YUKARI)
		{
			printlog("유카리는 당신의 위험한 전이마법에 분노했다!",true,false,false,CL_small_danger);
			you.PietyUpDown(-5);
		}
		return true;
	}
	return false;
}

bool skill_the_world(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
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
	random_shuffle(target_mon_list.begin(),target_mon_list.end());

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
	random_shuffle(target_mon_list.begin(),target_mon_list.end());
	
	for(vector<monster*>::iterator it = target_mon_list.begin(); it != target_mon_list.end(); it++)
	{
		monster* final_target = (*it);	
		final_target->HpUpDown(rand_int(2+power/10,10+power/5),DR_NONE);		
		if(env[current_level].isInSight(final_target->position))
			printarray(false,false,false,CL_normal,3,final_target->GetName()->name.c_str(),final_target->GetName()->name_is(true),"회복되었다.");
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

	order->SetCommunication(rand_int(2,4));
	return true;
}
bool skill_moon_gun(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		int damage_ = 6+power/8;
		beam_infor temp_infor(randC(3,damage_),3*damage_,18,order,order->GetParentType(),SpellLength(SPL_MON_TANMAC_SMALL),1,BMT_NORMAL,ATT_THROW_NORMAL,name_infor("총알",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		
		for(int i=0;i<(order->GetParadox()?2:1);i++)	
			throwtanmac(19,beam,temp_infor,NULL);
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
	string speak_; 
	switch(randA(6))
	{
	case 0: //요정
		list_.push_back(MON_FAIRY_GREEN_WARRIOR);
		list_.push_back(MON_FAIRY_BLUE_MAGICIAN);
		list_.push_back(MON_FAIRY_SOCERER);
		list_.push_back(MON_FAIRY_SUN_FLOWER);
		list_.push_back(MON_FAIRY_HERO);
		speak_ = "안개의 호수의 꿈을 불러냈다!";
		break;
	case 1: //요괴산
		list_.push_back(MON_WOLF_TENGU);
		list_.push_back(MON_YAMABUSH_TENGU);
		list_.push_back(MON_HANATACA_TENGU);
		list_.push_back(MON_KATPA_WATER_WIZARD);
		list_.push_back(MON_KATPA_SPEAR);
		speak_ = "요괴의 산의 꿈을 불러냈다!";
		break;
	case 2: //홍마관
		list_.push_back(MON_HOBGOBRIN_MAID);
		list_.push_back(MON_HOBGOBRIN_LIBRARIAN);
		list_.push_back(MON_HOBGOBRIN_TEMP);
		list_.push_back(MON_MAID_FAIRY);
		list_.push_back(MON_CHUPARCABRA);
		speak_ = "홍마관의 꿈을 불러냈다!";
		break;
	case 3: //윳쿠리
		list_.push_back(MON_REIMUYUKKURI);
		list_.push_back(MON_MARISAYUKKURI);
		list_.push_back(MON_AYAYUKKURI);
		list_.push_back(MON_REMILIAYUKKURI);
		list_.push_back(MON_ALICEYUKKURI);
		list_.push_back(MON_YOUMUYUKKURI);
		speak_ = "윳쿠리 둥지의 꿈을 불러냈다!";
		break;
	case 4: //죽림
		list_.push_back(MON_RABIT_BOMB);
		list_.push_back(MON_RABIT_SPEAR);
		list_.push_back(MON_RABIT_SPEAR);
		list_.push_back(MON_RABIT_SUPPORT);
		list_.push_back(MON_RABIT_MAGIC);
		list_.push_back(MON_RABIT_SPEAR);
		speak_ = "미궁의 죽림의 꿈을 불러냈다!";
		break;
	case 5: //지저
		list_.push_back(MON_HAUNT);
		list_.push_back(MON_FIRE_CAR);
		list_.push_back(MON_HELL_SPIDER);
		list_.push_back(MON_BLOOD_HAUNT);
		list_.push_back(MON_HELL_CROW);
		speak_ = "지저의 꿈을 불러냈다!";
		break;
	case 6: //마계
		list_.push_back(MON_SARA);
		list_.push_back(MON_LUIZE);
		list_.push_back(MON_ELIS);
		list_.push_back(MON_EVIL_EYE);
		list_.push_back(MON_LITTLE_IMP);
		speak_ = "마계의 꿈을 불러냈다!";
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
		if(order && env[current_level].isInSight(order->position))
			printarray(true,false,false,CL_magic,3,order->GetName()->name.c_str(),order->GetName()->name_is(true),speak_.c_str());

	}

	return return_;
}
bool skill_mana_drain(int power, bool short_, unit* order, coord_def target)
{
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);
	
	if(target_unit)
	{
		int damage_ = 14+power/8;
		int reduce_damage_ = damage_;
		if(target_unit->isplayer()) //이 공격은 지능으로 감소가 가능하다.
		{
			reduce_damage_ = max(1,reduce_damage_-randA(you.s_int)/2);
			you.MpUpDown(rand_int(-4,-7));
		}
		else //몬스터는 저항력으로 따짐
		{
			monster *mon_ = (monster*)target_unit;
			reduce_damage_ = max(1,randA(mon_->level+mon_->resist*5)/2);
		}
		attack_infor temp_att(randA_1(reduce_damage_),damage_,99,order,order->GetParentType(),ATT_SMITE,name_infor("악몽",true));
		target_unit->damage(temp_att, true);
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
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}
bool skill_blood_smite(int power, bool short_, unit* order, coord_def target)
{
	unit* target_unit = env[current_level].isMonsterPos(target.x, target.y);
	
	if(target_unit)
	{
		int damage_ = target_unit->GetMaxHp()*rand_int(10,20)/100;
		attack_infor temp_att(damage_,damage_,99,order,order->GetParentType(),ATT_BLOOD,name_infor("피의 응시",false));
		target_unit->damage(temp_att, true);
		return true;
	}
	return false;
}
bool skill_call_hound(int power, bool short_, unit* order, coord_def target)
{
	return false;
}
bool skill_canon(int power, bool short_, unit* order, coord_def target)
{
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
			if(id_ == MON_HOURAI)
				order->SetSaved(true);
			return_ = true;
		}
	}
	return return_;
}

bool skill_fire_spread(int power, bool short_, unit* order, coord_def target)
{
	return false;
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
	case MON_ALICEYUKKURI:
		list->push_back(spell(SPL_FAKE_DOLLS_WAR,30));
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
			int arr_[] = {SPL_FIRE_BOLT, SPL_ICE_BOLT, SPL_VENOM_BOLT, SPL_LASER,SPL_STONE_ARROW,
			SPL_KANAME_DRILL, SPL_ICE_CLOUD, SPL_POISON_CLOUD, SPL_MIND_BENDING,SPL_LUMINUS_STRIKE
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
		list->push_back(spell(SPL_MAGIC_TANMAC,20));
		list->push_back(spell(randA(1)?SPL_CONFUSE:SPL_SLOW,10));
		list->push_back(spell(SPL_VENOM_BOLT,15));		
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
	case MON_NAMAZ:
		list->push_back(spell(SPL_STONE_UPLIFT,20));
		break;	
	case MON_LANTERN_YOUKAI:
		list->push_back(spell(SPL_FIRE_SPREAD,30));
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
	case MON_FAIRY_HERO:
		break;
	case MON_FAIRY_SOCERER:
		list->push_back(spell(SPL_ICE_BOLT,20));
		list->push_back(spell(SPL_FIRE_BOLT,20));
		break;
	case MON_FAIRY_SUN_FLOWER:
		list->push_back(spell(SPL_SMITE,15));
		list->push_back(spell(SPL_HASTE_ALL,15));
		list->push_back(spell(SPL_HEAL_ALL,20));
		break;
	case MON_MOON_RABIT_SUPPORT:
		list->push_back(spell(SPL_MOON_COMMUNICATION,20));
		list->push_back(spell(SPL_HASTE_OTHER,15));
		break;
	case MON_MOON_RABIT_ATTACK:
		break;
	case MON_MOON_RABIT_ELITE:
		list->push_back(spell(SPL_MOON_GUN,40));
		break;
	case MON_MAC:
		list->push_back(spell(SPL_SUMMON_DREAM,30));
		list->push_back(spell(SPL_BLINK,15));
		break;
	case MON_NIGHTMARE:
		list->push_back(spell(SPL_MANA_DRAIN,20));
		break;
	case MON_LUNATIC:
		list->push_back(spell(SPL_INSANE,20));
		break;
	case MON_HAUNT:
		break;
	case MON_FIRE_CAR:
		list->push_back(spell(SPL_FIRE_BALL,25));
		list->push_back(spell(SPL_FIRE_BOLT,20));
		break;
	case MON_HELL_SPIDER:
		break;
	case MON_BLOOD_HAUNT:
		list->push_back(spell(SPL_BLOOD_SMITE,15));
		break;
	case MON_HELL_HOUND:
		list->push_back(spell(SPL_CALL_HOUND,15));
		break;
	case MON_DESIRE:
		break;
	case MON_FLOWER_TANK:
		list->push_back(spell(SPL_LASER,30));
		list->push_back(spell(SPL_LUMINUS_STRIKE,15));
		break;
	case MON_EVIL_EYE_TANK:
		list->push_back(spell(SPL_CANNON,15));
		break;
	case MON_SNOW_GIRL:
		list->push_back(spell(SPL_FREEZE,20));
		list->push_back(spell(SPL_COLD_BEAM,15));
		break;
	case MON_LETTY:
		list->push_back(spell(SPL_FREEZE,25));
		list->push_back(spell(SPL_ICE_CLOUD,15));
		break;
	case MON_YORIHIME:
		break;
	case MON_TOYOHIME:
		list->push_back(spell(SPL_ICE_BOLT,15));
		list->push_back(spell(SPL_BLIZZARD,20));
		break;
	case MON_UTSUHO:
		list->push_back(spell(SPL_FIRE_STORM,6));
		list->push_back(spell(SPL_HASTE,15));
		break;
	case MON_SUIKA:
		break;
	case MON_REIMU:
		break;
	case MON_ALICE:
		list->push_back(spell(SPL_DOLLS_WAR,50));
		list->push_back(spell(SPL_TELEPORT_SELF,10));
		break;
	case MON_SEIRAN:
		break;
	case MON_RINGO:
		list->push_back(spell(SPL_MOON_COMMUNICATION,20));
		list->push_back(spell(SPL_HASTE_OTHER,15));
		break;
	case MON_UDONGE:
		list->push_back(spell(SPL_MIND_BENDING,15));
		list->push_back(spell(SPL_FIELD_VIOLET,15));
		break;
	case MON_KAGUYA:
		break;
	case MON_MOKOU:
		break;
	case MON_NESI:
		list->push_back(spell(SPL_WATER_CANNON,30));
		break;
	case MON_SANGHAI:
	case MON_FAKE_SANGHAI:
		break;
	case MON_HOURAI:
	case MON_FAKE_HOURAI:
		list->push_back(spell(SPL_LASER,60));
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
	default:
		return false;
	}
}

