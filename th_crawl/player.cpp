//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: player.cpp
//
// 내용: player관련 함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "player.h"
#include "unit.h"
#include "environment.h"
#include "beam.h"
#include "potion.h"
#include "scroll.h"
#include "smoke.h"
#include "skill.h"
#include "skill_use.h"
#include "mon_infor.h"
#include "ring.h"
#include "save.h"
#include "key.h"
#include "weapon.h"
#include "god.h"
#include "throw.h"
#include "note.h"
#include "spellcard.h"
#include "rect.h"
#include "tribe.h"
#include "floor.h"
#include "alchemy.h"
#include "tensi.h"
#include "swako.h"
#include "dump.h"
#include "armour.h"
#include "evoke.h"


players you;
extern HANDLE mutx;
skill_type itemtoskill(item_type type_);
extern bool widesearch; //X커맨드용

void name_infor::SaveDatas(FILE *fp)
{
	char temp[100];
	sprintf(temp,"%s",name.c_str());
	SaveData<char>(fp,*temp, strlen(temp)+1);
	SaveData<bool>(fp, name_type);
}	

void name_infor::LoadDatas(FILE *fp)
{
	char temp[100];
	LoadData<char>(fp, *temp);
	name = temp;
	LoadData<bool>(fp, name_type);
}

players::players():
prev_position(0,0), name("당신",true), char_name("레이무",false), user_name("이름없음",true), image(NULL), tribe(TRI_FIRST), job(JOB_FIRST),
hp(10), prev_hp(10), max_hp(10), hp_recov(0), mp(0),prev_mp(0), max_mp(0), mp_recov(0), power(300),	power_decre(0), level(1), exper(0), exper_recovery(10), exper_aptit(10), skill_exper(0), 
ac(0), ev(10), sh(0),real_ac(0),bonus_ac(0), real_ev(10), bonus_ev(0),real_sh(0), bonus_sh(0), s_str(10), s_dex(10), s_int(10), m_str(10), m_dex(10), m_int(10), acc_plus(0), dam_plus(0),
as_penalty(0), magic_resist(0), tension_gauge(0), tension_turn(false), search(false), search_pos(0,0), item_weight(0), max_item_weight(350),prev_action(ACTT_NONE) , equipment(), time_delay(0), speed(10),
turn(0), real_turn(0), prev_real_turn(0), player_move(false), explore_map(0)/*, hunger(7000), hunger_per_turn(0)*/, 
final_item(0), final_num(0), auto_pickup(1), inter(IT_NONE), 
s_poison(0),s_tele(0), s_might(0), s_clever(0), s_agility(0), s_haste(0), s_confuse(0), s_slow(0),s_frozen(0),
s_elec(0), s_paralyse(0), s_levitation(0), s_glow(0), s_graze(0), s_silence(0), s_silence_range(0), s_sick(0), s_veiling(0), s_value_veiling(0), s_invisible(0), s_swift(0), 
 s_mana_regen(0), s_superman(0), s_spellcard(0), s_slaying(0), s_autumn(0), s_wind(0), s_knife_collect(0), s_drunken(0), s_catch(0), s_ghost(0),
 s_dimension(0), s_timestep(0),  s_mirror(0), s_lunatic(0), s_paradox(0), s_trans_panalty(0), s_the_world(0), s_mana_delay(0),
 s_stat_boost(0), s_stat_boost_value(0), s_eirin_poison(0), s_eirin_poison_time(0),
 alchemy_buff(ALCT_NONE), alchemy_time(0),
teleport_curse(false), magician_bonus(0), poison_resist(0),fire_resist(0),ice_resist(0),elec_resist(0),confuse_resist(0), invisible_view(0), power_keep(0), togle_invisible(false), battle_count(0),
uniden_poison_resist(0), uniden_fire_resist(0), uniden_ice_resist(0), uniden_elec_resist(0),uniden_confuse_resist(0), uniden_invisible_view(0), uniden_power_keep(0)
,total_skill_exp(0), remainSpellPoiont(1), currentSpellNum(0),currentSkillNum(0),god(GT_NONE), gift_count(0), piety(0), god_turn(0), suwako_meet(0),
sight_reset(false), target(NULL), throw_weapon(NULL),dead_order(NULL), dead_reason(DR_NONE)
{
	for(int i=0;i<52;i++)
		MemorizeSpell[i] = 0;
	for(int i=0;i<27;i++)
		MemorizeSkill[i] = 0;
	for(int i=0;i<27;i++)
		MemorizeSkill_num[i] = 0;
	for(int i=0;i<GT_LAST;i++)
		punish[i]=0;
	for(int i=0;i<5;i++)
		god_value[i]=0;
	for(int i=0;i<ET_LAST;i++)
		equipment[i] = NULL;

}

players::~players()
{
}
void players::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<int>(fp, prev_position.x);
	SaveData<int>(fp, prev_position.y);
	name.SaveDatas(fp);
	char_name.SaveDatas(fp);
	user_name.SaveDatas(fp);
	SaveData<int>(fp, texturetoint(image));
	SaveData<tribe_type>(fp, tribe);
	SaveData<job_type>(fp, job);
	SaveData<int>(fp, hp);
	SaveData<int>(fp, max_hp);
	SaveData<int>(fp, hp_recov);
	SaveData<int>(fp, mp);
	SaveData<int>(fp, max_mp);
	SaveData<int>(fp, mp_recov);
	SaveData<int>(fp, power);
	SaveData<int>(fp, power_decre);
	SaveData<int>(fp, level);
	SaveData<int>(fp, exper);
	SaveData<int>(fp, exper_recovery);
	SaveData<int>(fp, exper_aptit);
	SaveData<int>(fp, skill_exper);
	SaveData<int>(fp, ac);
	SaveData<int>(fp, ev);
	SaveData<int>(fp, sh);
	SaveData<int>(fp, real_ac);
	SaveData<int>(fp, bonus_ac);
	SaveData<int>(fp, real_ev);
	SaveData<int>(fp, bonus_ev);	
	SaveData<int>(fp, real_sh);
	SaveData<int>(fp, bonus_sh);
	SaveData<int>(fp, s_str);
	SaveData<int>(fp, s_dex);
	SaveData<int>(fp, s_int);
	SaveData<int>(fp, m_str);
	SaveData<int>(fp, m_dex);
	SaveData<int>(fp, m_int);
	SaveData<int>(fp, acc_plus);
	SaveData<int>(fp, dam_plus);
	SaveData<int>(fp, as_penalty);
	SaveData<int>(fp, magic_resist);
	SaveData<int>(fp, tension_gauge);
	SaveData<bool>(fp, tension_turn);
		
	SaveData<int>(fp, buff_list.size());
	for(list<buff_class>::iterator it=buff_list.begin();it!=buff_list.end();it++)
	{
		SaveData<buff_class>(fp, (*it));
	}

	SaveData<int>(fp, item_list.size());
	for(list<item>::iterator it=item_list.begin();it!=item_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}

	SaveData<int>(fp, property_vector.size());
	for(auto it=property_vector.begin();it!=property_vector.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	
	SaveData<int>(fp, action_vector.size());
	for(auto it=action_vector.begin();it!=action_vector.end();it++)
	{
		(*it).SaveDatas(fp);
	}

	SaveData<float>(fp, item_weight);
	SaveData<float>(fp, max_item_weight);
	SaveData<action_type>(fp, prev_action);
	for(int i=0;i<ET_LAST;i++)
	{
		SaveData<char>(fp, equipment[i]?equipment[i]->id:0);
	}
	SaveData<int>(fp, time_delay);
	SaveData<int>(fp, speed);
	SaveData<int>(fp, turn);
	SaveData<int>(fp, real_turn);
	SaveData<int>(fp, prev_real_turn);
	SaveData<bool>(fp, player_move);
	SaveData<int>(fp,explore_map);

	//SaveData<int>(fp, hunger);
	//SaveData<int>(fp, hunger_per_turn);
	SaveData<int>(fp, auto_pickup);
	SaveData<interupt_type>(fp, inter);
	SaveData<int>(fp, s_poison);
	SaveData<int>(fp, s_tele);
	SaveData<int>(fp, s_might);
	SaveData<int>(fp, s_clever);
	SaveData<int>(fp, s_agility);
	SaveData<int>(fp, s_haste);
	SaveData<int>(fp, s_confuse);
	SaveData<int>(fp, s_slow);
	SaveData<int>(fp, s_frozen);
	SaveData<int>(fp, s_elec);
	SaveData<int>(fp, s_paralyse);
	SaveData<int>(fp, s_levitation);
	SaveData<int>(fp, s_glow);
	SaveData<int>(fp, s_graze);
	SaveData<int>(fp, s_silence);
	SaveData<int>(fp, s_silence_range);
	SaveData<int>(fp, s_sick);
	SaveData<int>(fp, s_veiling);
	SaveData<int>(fp, s_value_veiling); 
	SaveData<int>(fp, s_invisible);
	SaveData<int>(fp, s_swift);
	SaveData<int>(fp, s_mana_regen);
	SaveData<int>(fp, s_superman);
	SaveData<int>(fp, s_spellcard);
	SaveData<int>(fp, s_slaying);
	SaveData<int>(fp, s_autumn);
	SaveData<int>(fp, s_wind);
	SaveData<int>(fp, s_knife_collect);
	SaveData<int>(fp, s_drunken);
	SaveData<int>(fp, s_catch);
	SaveData<int>(fp, s_ghost);
	SaveData<int>(fp, s_dimension);
	SaveData<int>(fp, s_timestep);
	SaveData<int>(fp, s_mirror);
	SaveData<int>(fp, s_lunatic);
	SaveData<int>(fp, s_paradox);
	SaveData<int>(fp, s_trans_panalty);
	SaveData<int>(fp, s_the_world);
	SaveData<int>(fp, s_mana_delay);
	SaveData<int>(fp, s_stat_boost);
	SaveData<int>(fp, s_stat_boost_value);
	SaveData<int>(fp, s_eirin_poison);
	SaveData<int>(fp, s_eirin_poison_time);

	
	SaveData<ALCHEMY_LIST>(fp, alchemy_buff);
	SaveData<int>(fp, alchemy_time);

	
	SaveData<int>(fp, teleport_curse);
	SaveData<int>(fp, magician_bonus);
	SaveData<int>(fp, poison_resist);
	SaveData<int>(fp, fire_resist);
	SaveData<int>(fp, ice_resist);
	SaveData<int>(fp, elec_resist);
	SaveData<int>(fp, confuse_resist);
	SaveData<int>(fp, invisible_view);	
	SaveData<int>(fp, power_keep);
	SaveData<bool>(fp, togle_invisible);
	SaveData<int>(fp, battle_count);
	SaveData<int>(fp, uniden_poison_resist);
	SaveData<int>(fp, uniden_fire_resist);
	SaveData<int>(fp, uniden_ice_resist);
	SaveData<int>(fp, uniden_elec_resist);
	SaveData<int>(fp, uniden_confuse_resist);
	SaveData<int>(fp, uniden_invisible_view);
	SaveData<int>(fp, uniden_power_keep);
	SaveData<int>(fp, total_skill_exp);
	SaveData<skill_exp_infor>(fp, *skill, SKT_MAX);	
	SaveData<int>(fp, *MemorizeSpell,52);
	SaveData<int>(fp, remainSpellPoiont);
	SaveData<int>(fp, currentSpellNum);
	SaveData<int>(fp, *MemorizeSkill,52);
	SaveData<int>(fp, *MemorizeSkill_num,52);
	SaveData<int>(fp, currentSkillNum);
	SaveData<god_type>(fp, god);
	SaveData<int>(fp, gift_count);
	SaveData<int>(fp, piety);
	SaveData<int>(fp, *punish, GT_LAST);
	SaveData<int>(fp, god_turn);
	SaveData<int>(fp, *god_value, 5);
	SaveData<int>(fp, suwako_meet); 
	SaveData<char>(fp, throw_weapon?throw_weapon->id:0);
}
void players::LoadDatas(FILE *fp)
{
	item_list.clear();

	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<int>(fp, prev_position.x);
	LoadData<int>(fp, prev_position.y);
	name.LoadDatas(fp);
	char_name.LoadDatas(fp);
	user_name.LoadDatas(fp);
	int it;
	LoadData<int>(fp, it);
	image = inttotexture(it);
	LoadData<tribe_type>(fp, tribe);
	LoadData<job_type>(fp, job);
	LoadData<int>(fp, hp);
	prev_hp = hp;
	LoadData<int>(fp, max_hp);
	LoadData<int>(fp, hp_recov);
	LoadData<int>(fp, mp);
	prev_mp = mp;
	LoadData<int>(fp, max_mp);
	LoadData<int>(fp, mp_recov);
	LoadData<int>(fp, power);
	LoadData<int>(fp, power_decre);
	LoadData<int>(fp, level);
	LoadData<int>(fp, exper);
	LoadData<int>(fp, exper_recovery);	
	LoadData<int>(fp, exper_aptit);
	LoadData<int>(fp, skill_exper);
	LoadData<int>(fp, ac);
	LoadData<int>(fp, ev);
	LoadData<int>(fp, sh);
	LoadData<int>(fp, real_ac);
	LoadData<int>(fp, bonus_ac);
	LoadData<int>(fp, real_ev);
	LoadData<int>(fp, bonus_ev);	
	LoadData<int>(fp, real_sh);
	LoadData<int>(fp, bonus_sh);
	LoadData<int>(fp, s_str);
	LoadData<int>(fp, s_dex);
	LoadData<int>(fp, s_int);
	LoadData<int>(fp, m_str);
	LoadData<int>(fp, m_dex);
	LoadData<int>(fp, m_int);
	LoadData<int>(fp, acc_plus);
	LoadData<int>(fp, dam_plus);
	LoadData<int>(fp, as_penalty);
	LoadData<int>(fp, magic_resist);
	LoadData<int>(fp, tension_gauge);
	LoadData<bool>(fp, tension_turn);

	

	int size_=0;
		
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		buff_class temp;
		LoadData<buff_class>(fp, temp);
		buff_list.push_back(temp);
	}

	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		item temp;
		temp.LoadDatas(fp);
		item_list.push_back(temp);
	}
	
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		tribe_property temp;
		temp.LoadDatas(fp);
		property_vector.push_back(temp);
	}

	
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		action_class temp;
		temp.LoadDatas(fp);
		action_vector.push_back(temp);
	}

	

	LoadData<float>(fp, item_weight);
	LoadData<float>(fp, max_item_weight);
	LoadData<action_type>(fp, prev_action);
	for(int i=0;i<ET_LAST;i++)
	{
		char temp_id_=0;
		item *temp_ = NULL;
		LoadData<char>(fp, temp_id_);
		list<item>::iterator it;
		for(it = item_list.begin(); temp_id_ && it != item_list.end();it++)
		{
			if((*it).id == temp_id_)
			{
				temp_ = &(*it);
				break;
			}
		}
		equipment[i] = temp_;
	}
	LoadData<int>(fp, time_delay);
	LoadData<int>(fp, speed);
	LoadData<int>(fp, turn);
	LoadData<int>(fp, real_turn);
	LoadData<int>(fp, prev_real_turn);
	LoadData<bool>(fp, player_move);
	LoadData<int>(fp,explore_map);
	//LoadData<int>(fp, hunger);
	//LoadData<int>(fp, hunger_per_turn);
	LoadData<int>(fp, auto_pickup);
	LoadData<interupt_type>(fp, inter);
	LoadData<int>(fp, s_poison);
	LoadData<int>(fp, s_tele);
	LoadData<int>(fp, s_might);
	LoadData<int>(fp, s_clever);
	LoadData<int>(fp, s_agility);
	LoadData<int>(fp, s_haste);
	LoadData<int>(fp, s_confuse);
	LoadData<int>(fp, s_slow);
	LoadData<int>(fp, s_frozen);
	LoadData<int>(fp, s_elec);
	LoadData<int>(fp, s_paralyse);
	LoadData<int>(fp, s_levitation);
	LoadData<int>(fp, s_glow);
	LoadData<int>(fp, s_graze);
	LoadData<int>(fp, s_silence);
	LoadData<int>(fp, s_silence_range);
	LoadData<int>(fp, s_sick);
	LoadData<int>(fp, s_veiling);
	LoadData<int>(fp, s_value_veiling);
	LoadData<int>(fp, s_invisible);
	LoadData<int>(fp, s_swift);
	LoadData<int>(fp, s_mana_regen);
	LoadData<int>(fp, s_superman);
	LoadData<int>(fp, s_spellcard);
	LoadData<int>(fp, s_slaying);
	LoadData<int>(fp, s_autumn);
	LoadData<int>(fp, s_wind);
	LoadData<int>(fp, s_knife_collect);
	LoadData<int>(fp, s_drunken);
	LoadData<int>(fp, s_catch);
	LoadData<int>(fp, s_ghost);
	LoadData<int>(fp, s_dimension);
	LoadData<int>(fp, s_timestep);
	LoadData<int>(fp, s_mirror);
	LoadData<int>(fp, s_lunatic);
	LoadData<int>(fp, s_paradox);
	LoadData<int>(fp, s_trans_panalty);
	LoadData<int>(fp, s_the_world);
	LoadData<int>(fp, s_mana_delay);	
	LoadData<int>(fp, s_stat_boost);
	LoadData<int>(fp, s_stat_boost_value);
	LoadData<int>(fp, s_eirin_poison);
	LoadData<int>(fp, s_eirin_poison_time);
	

	LoadData<ALCHEMY_LIST>(fp, alchemy_buff);
	LoadData<int>(fp, alchemy_time);
	
	LoadData<int>(fp, teleport_curse);
	LoadData<int>(fp, magician_bonus);
	LoadData<int>(fp, poison_resist);
	LoadData<int>(fp, fire_resist);
	LoadData<int>(fp, ice_resist);
	LoadData<int>(fp, elec_resist);
	LoadData<int>(fp, confuse_resist);
	LoadData<int>(fp, invisible_view);
	LoadData<int>(fp, power_keep);
	LoadData<bool>(fp, togle_invisible);
	LoadData<int>(fp, battle_count);		
	LoadData<int>(fp, uniden_poison_resist);
	LoadData<int>(fp, uniden_fire_resist);
	LoadData<int>(fp, uniden_ice_resist);
	LoadData<int>(fp, uniden_elec_resist);
	LoadData<int>(fp, uniden_confuse_resist);
	LoadData<int>(fp, uniden_invisible_view);
	LoadData<int>(fp, uniden_power_keep);
	LoadData<int>(fp, total_skill_exp);
	LoadData<skill_exp_infor>(fp, *skill);
	LoadData<int>(fp, *MemorizeSpell);
	LoadData<int>(fp, remainSpellPoiont);
	LoadData<int>(fp, currentSpellNum);
	LoadData<int>(fp, *MemorizeSkill);
	LoadData<int>(fp, *MemorizeSkill_num);
	LoadData<int>(fp, currentSkillNum);
	LoadData<god_type>(fp, god);
	LoadData<int>(fp, gift_count);
	LoadData<int>(fp, piety);
	LoadData<int>(fp, *punish);
	LoadData<int>(fp, god_turn);
	LoadData<int>(fp, *god_value);
	LoadData<int>(fp, suwako_meet);
	{
		char temp_id_=0;
		item *temp_ = NULL;
		LoadData<char>(fp, temp_id_);
		list<item>::iterator it;
		for(it = item_list.begin(); temp_id_ && it != item_list.end();it++)
		{
			if((*it).id == temp_id_)
			{
				temp_ = &(*it);
				break;
			}
		}
		throw_weapon = temp_;
	}
}

bool players::isLive()
{
	return true;
}
bool players::isSwim()
{
	if(god == GT_SUWAKO && !punish[GT_SUWAKO] && pietyLevel(piety)>=2 &&
		god_value[1] == SWAKO_2_SWIM)
		return true;
	if(GetProperty(TPT_SWIM))
		return true;
	else
		return false;
};
void players::SetX(int x_)
{
	SetXY(x_, position.y);
}
void players::SetY(int y_)
{
	SetXY(position.x, y_);
}
void players::SetXY(int x_, int y_)
{
	if(position.x == x_ && position.y == y_)
	{
		resetLOS();
		return;
	}
	if(s_silence)
		env[current_level].MakeSilence(position, s_silence_range, false);
	if(s_catch)	
		SetCatch(NULL);
	position.set(x_,y_);
	for(auto it = env[current_level].floor_list.begin(); it != env[current_level].floor_list.end();it++)
	{
		if(it->position == position)
			it->onWalk(this);
	}
	if(s_silence)
		env[current_level].MakeSilence(position, s_silence_range, true);	
	resetLOS();
}
void players::SetXY(coord_def pos_)
{
	SetXY(pos_.x,pos_.y);
}
coord_def players::GetDisplayPos()
{
	if(!s_dimension)
	{
		return widesearch?search_pos:position;
	}
	else
	{
		return coord_def(god_value[0],god_value[1]);
	}
}
int players::move(short_move x_mov, short_move y_mov)
{
	if(!x_mov && !y_mov)
		return 0;
	int drunken_ = randA(10);
	if(s_confuse || (s_drunken && drunken_==0))
	{
		do
		{
			x_mov = (short_move)rand_int(MV_BACK,MV_FRONT);
			y_mov = (short_move)rand_int(MV_BACK,MV_FRONT);
		}while(x_mov == MV_NONE && y_mov == MV_NONE);
	}

	int move_x_ =  position.x+x_mov, move_y_ = position.y+y_mov;
	
	if(you.s_dimension)
	{
		if(abs(move_x_ - you.god_value[0])>8)
		{
			    move_x_ +=move_x_ - you.god_value[0]>0?-17:17;
		}
		if(abs(move_y_ - you.god_value[1])>8)
		{
			    move_y_ +=move_y_ - you.god_value[1]>0?-17:17;
		}
	}

	if(1)//env[current_level].isMove(position.x+x_mov,position.y+y_mov,isFly()))
	{

		monster* mon_ = (monster*)env[current_level].isMonsterPos(move_x_,move_y_,this);



		if(mon_)
		{
			if(mon_->isUserAlly() && !(mon_->flag & M_FLAG_NONE_MOVE))
			{
				if(env[current_level].isMove(move_x_,move_y_,isFly(),isSwim()))
				{
					PositionSwap(mon_);								
					printlog("위치를 서로 바꿨다. ",false,false,false,CL_bad);
					return 2;
				}
				else
					return 0;
			}
			else if(mon_->isUserAlly() && (mon_->flag & M_FLAG_NONE_MOVE))
			{
				printlog("이동할 수 없다.",true,false,false,CL_normal);
				return 0;
			}
			attack_type brand_ = ATT_NORMAL;
			if(equipment[ET_WEAPON])
				brand_ = (attack_type)GetAttType((weapon_brand)equipment[ET_WEAPON]->value5);
			attack_infor temp_att(GetAttack(false),GetAttack(true),GetHit(),this,GetParentType(),brand_,alchemy_buff == ALCT_STONE_FIST?name_infor("돌주먹",true):name_infor("공격",true));
			if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->type >= ITM_WEAPON_FIRST && equipment[ET_WEAPON]->type <= ITM_WEAPON_CLOSE)
			{					
				doingActionDump(DACT_MELEE, skill_string(itemtoskill(equipment[ET_WEAPON]->type)));
				//나중에 무기 이름으로 바꾸기
			}
			else if(!equipment[ET_WEAPON])
			{
				doingActionDump(DACT_MELEE, skill_string(SKT_UNWEAPON));
			}
			else
			{
				doingActionDump(DACT_MELEE, "엉터리");
			}


			if(mon_->damage(temp_att))
			{
				if(mon_->isLive()&& you.god == GT_YUUGI && !you.punish[GT_YUUGI] && pietyLevel(you.piety)>=2 && randA(10) == 0)
				{
					printarray(false,false,false,CL_yuigi,3,mon_->GetName()->name.c_str(),mon_->GetName()->name_to(true),"잡았다.");
					you.SetCatch(mon_);
				}
				if(alchemy_buff == ALCT_STONE_FIST)
				{
					alchemy_buff = ALCT_NONE;
					alchemy_time = 0;
				}
			}
			you.SetBattleCount(30);
			youAttack(mon_);
			if(mon_->isLive() && you.GetProperty(TPT_HORN))
			{
				int attack_ = 8;
				int hit_ = 12+level/3;
				if((equipment[ET_WEAPON] && randA(3)<1) || (!equipment[ET_WEAPON] && randA(2)<1))
				{//무기가 있으면 25%로 무기가 없으면 33%의 확률로 박치기가 나간다.
					attack_infor temp_att(randA_1(attack_),attack_,hit_,this,GetParentType(),ATT_NORMAL,name_infor("박치기",false));
					mon_->damage(temp_att, false);
				}
			}
			if(s_wind)
			{					
				for(rect_iterator rlt(you.position,1,1);!rlt.end();rlt++)
				{
					unit *unit_ = env[current_level].isMonsterPos(rlt->x,rlt->y,&you);
					if(unit_ && unit_ != mon_ && !unit_->isUserAlly())
					{
						unit_->damage(temp_att, false);

					}
				}
			}


			time_delay += GetAtkDelay();
			return 1;
		}
		if(env[current_level].isSmokePos(move_x_,move_y_))
		{
			smoke* temp_smoke = env[current_level].isSmokePos2(move_x_,move_y_);
			if(hp<temp_smoke->danger(this))
			{		
				printlog("정말 들어갈거야?(y/n) ",false,false,false,CL_danger);
				bool loop_ = true;
				you.SetInter(IT_SMOKE);
				while(loop_)
				{
					switch(waitkeyinput())
					{
					case 'Y':
					case 'y':
						loop_ = false;
						enterlog();
						break;
					case 'N':
					case 'n':
					case VK_ESCAPE:
						loop_ = false;
						printlog("위험해!",true,false,false,CL_normal);
						return 0;
					default:
						break;
					}
				}
			}
		}
		if(floor_effect* temp_floor = env[current_level].isFloorEffectPos(move_x_,move_y_))
		{
			if(hp<temp_floor->danger(this))
			{
				printlog("정말 들어갈거야?(y/n) ",false,false,false,CL_danger);
				bool loop_ = true;
				
				you.SetInter(IT_SMOKE);
				while(loop_)
				{
					switch(waitkeyinput())
					{
					case 'Y':
					case 'y':
						loop_ = false;
						enterlog();
						break;
					case 'N':
					case 'n':
					case VK_ESCAPE:
						loop_ = false;
						printlog("위험해!",true,false,false,CL_normal);
						return 0;
					default:
						break;
					}
				}
			}
		}
		if(env[current_level].isMove(move_x_,move_y_,isFly(),isSwim()))
		{
			SetXY(coord_def(move_x_,move_y_));
			time_delay += GetWalkDelay();//이동속도만큼 이동
			prev_action = ACTT_WALK;
			return 2;
		}
	}
	if(env[current_level].isDoor(move_x_,move_y_))
	{
		coord_def temp(move_x_,move_y_);
		return OpenDoor(temp);
	}
	else
	{
		if(s_confuse || (s_drunken && drunken_==0))
		{
			printlog("아얏!",true,false,false,CL_normal);
			time_delay += GetWalkDelay();
			return 1;
		}
		return 0;
	}
}

int players::move(const coord_def &c)
{
	return move((c.x>position.x?MV_FRONT:(c.x==position.x?MV_NONE:MV_BACK)),(c.y>position.y?MV_FRONT:(c.y==position.y?MV_NONE:MV_BACK)));
}
bool players::offsetmove(const coord_def &c)
{		
	position += c;
	if(position.x >= 0 && position.x < DG_MAX_X && position.y >= 0 && position.y < DG_MAX_Y )
	{
		resetLOS(false);
		return true;
	}
	else
		return false;
}
void players::youAttack(unit* unit_)
{
	for(auto it = env[current_level].mon_vector.begin();  it != env[current_level].mon_vector.end() ;it++)
	{
		if(it->isLive() && it->isUserAlly())
		{
			if(it->target && !it->target->isplayer())
			{//적이 이미 있는 경우
				if(it->target->isLive() && it->isEnemyMonster((monster*)it->target))
					break;	//해당적이 죽지않았으면서 적몬스터이면 구지 바꿀 필요가 없다. 
			}
			if(!unit_->isplayer() && it->isEnemyMonster((monster*)unit_))
			{
				if(it->state.GetState() == MS_FOLLOW)
				{							
					it->FoundTarget(unit_,30);
					it->state.SetState(MS_ATACK);
				}

			}
	
		}

	}

}

bool players::OpenDoor(const coord_def &c)
{
	if(env[current_level].isDoor(c.x,c.y))
	{
		if(env[current_level].OpenDoor(c.x,c.y))
		{
			printlog("문을 열었다.",false,false,false,CL_normal);
			time_delay += GetWalkDelay();
			return 1;
		}
		else
			return 0;
	}
	else
	{
		return 0;
	}
}
void players::CalcuHP()
{
	int fight_=skill[SKT_FIGHT].level;
	int level_=level;
	int aptit_=10+GetProperty(TPT_HP);
	int next_hp_ = floor((8 + floor((1+3*fight_)/2.0f)+floor(9*level_/2.0f)+floor(fight_*level_/14.0f))*(aptit_/10.0f));
	hp = hp*next_hp_/max_hp;
	prev_hp = hp;
	max_hp = next_hp_;
}
int players::GetThrowDelay(item_type type_)
{
	return 10;
}
int players::GetSpellDelay()
{
	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->value5 == WB_FAST_CAST)
		return 8;
	return 10;
}
int players::GetNormalDelay()
{
	return 10;
}
int players::GetWalkDelay()
{
	int speed_ = s_superman?3:(speed-(s_swift?2:0));
	if(speed_<3)
		speed_ = 3;
	if(as_penalty>GetPenaltyMinus(2))
		speed_ += 1+as_penalty/2;
	if(alchemy_buff == ALCT_STONE_FORM)
		speed_ *= 1.5f;
	if(s_frozen)
		speed_+=(s_frozen+1)*speed_/20;
	return speed_;
}
int players::GetSpellPower(int s1_, int s2_, int s3_)
{
	int power_ = 0, num = 0;
	if(s1_ != -1)
	{
		power_ += 2*skill[s1_].level;
		num++;
	}	
	if(s2_ != -1)
	{
		power_ += 2*skill[s2_].level;
		num++;
	}
	if(s3_ != -1)
	{
		power_ += 2*skill[s3_].level;
		num++;
	}
	if(num)
		power_/=num;
	power_+=skill[SKT_SPELLCASTING].level/2;
	if(s_clever)
		power_+=4;

	if(you.god == GT_MIMA && !you.punish[GT_MIMA] && pietyLevel(you.piety)>=2 &&
		(s1_ == SKT_CONJURE || s2_ == SKT_CONJURE || s3_ == SKT_CONJURE))
		power_+=4;


	power_*=s_int/10.0f;
	return power_;
}
int players::GetSpellSuccess(int spell_)
{
	int s1_=SpellSchool((spell_list)spell_,0), s2_=SpellSchool((spell_list)spell_,1), s3_=SpellSchool((spell_list)spell_,2);
	int num = 0;
	float success_ = 0;
	int differ_ = SpellDiffer(SpellLevel((spell_list)spell_));
	if(s1_ != -1)
	{
		success_ += skill[s1_].level;
		num++;
	}	
	if(s2_ != -1)
	{
		success_ += skill[s2_].level;
		num++;
	}
	if(s3_ != -1)
	{
		success_ += skill[s3_].level;
		num++;
	}
	if(num)
		success_/=num;
	if(s_clever)
		success_+=2;
	if(magician_bonus)
		success_+=2;
	if(s_drunken)
		success_-=2;
	if(you.god == GT_BYAKUREN && !you.punish[GT_BYAKUREN] && pietyLevel(you.piety)>=4 && SpellFlagCheck((spell_list)spell_ ,S_FLAG_BUF))
		success_ += 2;
	if(you.god == GT_MIMA && !you.punish[GT_MIMA] && pietyLevel(you.piety)>=2 &&
		(s1_ == SKT_CONJURE || s2_ == SKT_CONJURE || s3_ == SKT_CONJURE))
		success_ += 2;


	if(you.s_trans_panalty && (s1_ == SKT_TRANS || s2_ == SKT_TRANS || s3_ == SKT_TRANS))
	{
		success_ -= you.s_trans_panalty;
	}


	success_+=s_int/5.0f+skill[SKT_SPELLCASTING].level/2;

	//if(equipment[ET_ARMOR])
	//{
	//	differ_ -= min(0,equipment[ET_ARMOR]->value2+(!GetArmourPanlty()?1:0));
	//	differ_ += 2*max(0,GetArmourPanlty()-1);
	//}
	if(you.as_penalty>0)
	{
		if(!(you.god == GT_BYAKUREN && !you.punish[GT_BYAKUREN] && pietyLevel(you.piety)>=3) || (as_penalty > GetPenaltyMinus(1)))
			differ_ += as_penalty*2;
	}

	success_ = max(0,(success_-differ_<=14)?(success_-differ_)*(2*14+(success_-differ_-1)*-1.07)/2:99);
	return success_;

}
int players::GetSpellHungry(int spell_)
{
	int hungry_ = SpellHunger(SpellLevel((spell_list)spell_));
	hungry_ -= s_int*skill[SKT_SPELLCASTING].level;
	if(hungry_<0)
		hungry_=0;
	return hungry_;
}
int players::GetStealth()
{
	int stealth_ = s_dex*3+skill[SKT_STEALTH].level*15+(s_agility?50:0);
	if(equipment[ET_ARMOR])
	{
		if(you.god == GT_SHIZUHA && equipment[ET_ARMOR]->value5 == AMK_AUTUMN)
			stealth_ += 150;
	}
	stealth_ += 50*GetProperty(TPT_STEALTH);
	stealth_ -= you.as_penalty*10; //은밀 감소
	return stealth_;
}	
int players::GetBuffOk(stat_up stat_)
{
	int value_ = 0;
	for(list<buff_class>::iterator it=buff_list.begin();it!=buff_list.end();it++)
	{
		if(it->stat==stat_){
			value_+= it->value;
		}
	}

	switch(stat_){
	case BUFFSTAT_STR:
		return value_+(s_might?5:0);
		break;
	case BUFFSTAT_INT:
		return value_+(s_clever?5:0);
		break;
	case BUFFSTAT_DEX:
		return value_+(s_agility?5:0);
		break;
	case BUFFSTAT_HP:
	case BUFFSTAT_MP:
	case BUFFSTAT_POW:
	case BUFFSTAT_AC:
	case BUFFSTAT_SH:
	case BUFFSTAT_EV:
	case BUFFSTAT_ACC:
	case BUFFSTAT_DAM:
	case BUFFSTAT_RF:
	case BUFFSTAT_RC:
		return value_;
		break;
	}
	return 0;
}
//hunger_type players::GetHunger()
//{
//	if(hunger<=1000)
//		return HT_STARVING;
//	else if(hunger<=1500)
//		return HT_NEARSTARVING;
//	else if(hunger<=2100)
//		return HT_VERYHUNGRY;
//	else if(hunger<=2600)
//		return HT_HUNGRY;
//	else if(hunger<=7000)
//		return HT_NORMAL;
//	else if(hunger<=9000)
//		return HT_FULL;
//	else if(hunger<=11000)
//		return HT_VERYFULL;
//	else
//		return HT_ENGORGED;
//}
int players::HpRecoverDelay(int delay_)
{
	float base_ = (((float)rand_int(270,330))/(max_hp+7.0f)+delay_)*10;

	//ex 20이면 20턴당 1회복 100턴간 5회복
	//10이번 100턴간 10회복
	//즉 100/ hp_recov가 100턴동안 회복량
	//만약 100턴간 10회복을 추가하려고하면
	//20일때 15가 되야되니까 20->6
	//10일때 20이 되어야하니까 10->5
	float cacul_ = 1000.0f/base_; //100턴당 회복량.

	if(god == GT_MINORIKO && !punish[GT_MINORIKO] && pietyLevel(piety)>=1)
	{
		int piety_ = (pietyLevel(you.piety)+1)/2;
		cacul_ += (piety_*5+(piety_*5*max_hp/100.f))*max(power-200,0)/300;
	}
	if(god == GT_YUUGI && !punish[GT_YUUGI] && s_drunken )
	{
		cacul_ += 100.0f;

	}


	hp_recov +=  1000.0f/cacul_ + rand_float(0,0.99f);

	return hp_recov;
}
interupt_type players::HpRecover(int delay_)
{
	if(1/*hp<max_hp*/)
	{
		hp_recov -= delay_;
		while((hp_recov)<=0)
		{
			bool already_ = (hp == max_hp);
			HpUpDown(1,DR_NONE);
			HpRecoverDelay(0);
			if(hp == max_hp && !already_)
				return IT_HP_RECOVER;
		}
	}
	return IT_NONE;
}
bool skill_suicide_bomb(int power, bool short_, unit* order, coord_def target);
void deadlog();
int players::HpUpDown(int value_,damage_reason reason, unit *order_)
{
	prev_hp = hp;
	if(value_<0 && max_hp/2 <= -value_)
		printlog("악! 이건 정말로 아프다!",true,false,false,CL_danger);

	if(order_)
	{
		dead_order->name = *order_->GetName();
		dead_order->damage = value_;
		dead_order->max_damage = value_;
		dead_order->order = order_;
		dead_order->p_type = order_->GetParentType();
		dead_order->accuracy = 99;
		dead_order->type = ATT_NONE;
	}

	hp+= value_;
	GodAccpect_HPUpDown(value_,reason);
	if(hp >= max_hp)
	{
		hp = max_hp;		
	}	
	if(hp<=0)
	{
		if(GetProperty(TPT_9_LIFE))
		{
			
			deadlog();
			printlog("리저렉션!",true,false,false,CL_white_blue);
			skill_suicide_bomb(level*8,false,&you,position);
			MoreWait();
			hp = max_hp;
			mp = max_mp;
			image = &img_play_mokou[1];
			DeleteProperty(TPT_9_LIFE);
		}
		else if(GetProperty(TPT_18_LIFE))
		{			
			deadlog();
			printlog("리저렉션!",true,false,false,CL_white_blue);
			skill_suicide_bomb(level*8,false,&you,position);
			MoreWait();
			hp = max_hp;
			mp = max_mp;
			image = &img_play_mokou[2];
			DeleteProperty(TPT_18_LIFE);
		}
		else if(wiz_list.wizard_mode)
		{
			MoreWait();
			printlog("죽어? (Y/N)",true,false,false,CL_help);
			wiz_list.wizard_mode = true;
			int key_ = waitkeyinput();
			switch(key_)
			{
			case 'Y':
				break;
			default:
				hp = max_hp;
				break;
			}
		}
		if(hp<=0)
		{
			dead_reason = reason;
			GameOver();
		}
	}
	return value_;
}
int players::MpRecoverDelay(int delay_,bool set_)
{
	float base_ =  (((float)rand_int(80,120))/(max_mp/4+7.0f)+delay_)*10;

	float cacul_ = 1000/base_; //100턴당 회복량.

	if(s_mana_regen)
		cacul_ +=100;

	
	if(you.god == GT_MINORIKO && !you.punish[GT_MINORIKO] && pietyLevel(you.piety)>=1)
	{
		int piety_ = pietyLevel(you.piety);
		cacul_ += piety_*2+(piety_*max_mp/40.f)*max(power-200,0)/300;
	}


	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->value5 == WB_MANA_REGEN && !you.s_mana_delay)
	{
		cacul_ +=30;
	}

	if(set_)
		mp_recov =  1000.0f/cacul_ + rand_float(0,0.99f);
	else
		mp_recov +=  1000.0f/cacul_ + rand_float(0,0.99f);

	return mp_recov;
}
interupt_type players::MpRecover(int delay_)
{
	if(1/*hp<max_hp*/)
	{
		mp_recov -= delay_;
		while((mp_recov)<=0)
		{
			bool already_ = (mp == max_mp);
			MpUpDown(1);
			MpRecoverDelay(0);
			

			if(mp == max_mp && !already_)
				return IT_MP_RECOVER;
		}
	}
	return IT_NONE;
}
int players::MpUpDown(int value_)
{
	prev_mp = mp;
	mp+= value_;
	if(mp >= max_mp)
	{
		mp = max_mp;		
	}	
	if(mp<=0)
	{
		mp = 0;
	}
	return mp;
}
int players::AcUpDown(int value_, int bonus_)
{
	real_ac += value_;
	bonus_ac += bonus_;
	float temp_ac = (float)real_ac*(1.0f+skill[SKT_ARMOUR].level/15.0f);
	ac = (int)temp_ac+bonus_ac; 
	return ac;
}
int players::EvUpDown(int value_, int bonus_)
{
	real_ev += value_;
	bonus_ev += bonus_;
	int size_ = -2*GetProperty(TPT_SIZE);
	ev = 3+size_+ real_ev*(8+s_dex)/(32.0f-size_) + bonus_ev;
	return ev;
}
int players::ShUpDown(int value_, int bonus_)
{
	real_sh += value_;
	bonus_sh += bonus_;
	float temp_sh = (float)real_sh*(1.0f+(s_dex/5.0f+skill[SKT_SHIELD].level)/15.0f);
	sh = (int)temp_sh+bonus_sh;
	return sh;
}
int players::CheckTension()
{
	if(!tension_turn)
	{
		tension_gauge = GetHazard();
		tension_turn = true;
	}
	return tension_gauge;
}
void players::UpDownBuff(stat_up stat_, int value_)
{
	switch(stat_){
	case BUFFSTAT_STR:
		StatUpDown(value_, STAT_STR);
		break;
	case BUFFSTAT_INT:
		StatUpDown(value_, STAT_INT);
		break;
	case BUFFSTAT_DEX:
		StatUpDown(value_, STAT_DEX);
		break;
	case BUFFSTAT_HP:
	case BUFFSTAT_MP:
	case BUFFSTAT_POW:
		//미구현
		break;
	case BUFFSTAT_AC:
		AcUpDown(0,value_);
		break;
	case BUFFSTAT_SH:
		ShUpDown(0,value_);
		break;
	case BUFFSTAT_EV:
		EvUpDown(0,value_);
		break;
	case BUFFSTAT_ACC:
	case BUFFSTAT_DAM:
		//미구현
		break;
	case BUFFSTAT_RF:
		you.ResistUpDown(value_,RST_FIRE);
		break;
	case BUFFSTAT_RC:
		you.ResistUpDown(value_,RST_ICE);
		break;
	}
}
void players::doingActionDump(dump_action_type type_, string name_)
{
	
	for(auto it=action_vector.begin();it!=action_vector.end();it++)
	{
		if(it->type == type_ && it->name.compare(name_) == 0){
			it->plus(level);
			return;
		}
	}
	auto it=action_vector.begin();
	for(;it!=action_vector.end();it++)
	{
		if(it->type > type_)
			break;

	}

	action_vector.insert(it, action_class(type_,name_,level));
	return;
}
int players::PowDecreaseDelay(int delay_)
{
	power_decre += (rand_int(25,30)+delay_)*10;
	if(power_keep>0)
	{
		power_decre*=2;
	}
	else if(power_keep<0)
	{
		power_decre/=2;
	}

	if(s_haste)
	{
		if(s_haste)
			power_decre/=power_keep?5:20;
	}
	if(s_invisible || togle_invisible)
	{
		if(s_invisible || togle_invisible)
			power_decre/=power_keep?5:20;
	}
	return power_decre;
}
interupt_type players::PowDecrease(int delay_)
{
	if(power>0)
	{
		power_decre-=delay_;
		while((power_decre)<=0)
		{
			PowUpDown(-1);
			PowDecreaseDelay(0);
			if(power == 0)
				return IT_NONE;
		}
	}
	return IT_NONE;
}
int players::PowUpDown(int value_, bool big_)
{
	bool full_power_ = power>=500?true:false;

	if(big_ && value_<0 && power>500)
		power = 500;
	power+=value_;
	if(power>530+(you.god == GT_MINORIKO?20:0))
		power = 530+(you.god == GT_MINORIKO?20:0);
	else if(power<0)
		power = 0;

	//if(you.god == GT_MINORIKO && !you.punish[GT_MINORIKO] && pietyLevel(you.piety)>=5)
	//{
	//	if(full_power_ && !(power>=500))
	//	{			
	//		you.ResistUpDown(-1,RST_FIRE);
	//		you.ResistUpDown(-1,RST_ICE);
	//	}
	//	else if(!full_power_ && power>=500)
	//	{
	//		
	//		you.ResistUpDown(1,RST_FIRE);
	//		you.ResistUpDown(1,RST_ICE);
	//	}
	//}

	return power;
}
bool players::StatUpDown(int value_, stat_type stat_, bool temp_)
{
	switch(stat_)
	{
	case STAT_STR:
		s_str+=value_;
		if(!temp_)
			m_str+=value_;
		max_item_weight+= value_*25;
		break;
	case STAT_DEX:
		s_dex+=value_;
		if(!temp_)
			m_dex+=value_;
		ShUpDown(0,0);
		EvUpDown(0,0);
		break;
	case STAT_INT:
		s_int+=value_;
		if(!temp_)
			m_int+=value_;
		break;
	}
	ReSetASPanlty();
	return true;
}
bool players::ResistUpDown(int value_, resist_type resist_)
{
	switch(resist_)
	{	
	case RST_POISON:
		poison_resist += value_;
		break;
	case RST_FIRE:
		fire_resist += value_;
		break;
	case RST_ICE:
		ice_resist += value_;
		break;
	case RST_ELEC:
		elec_resist += value_;
		break;
	case RST_CONFUSE:
		confuse_resist += value_;
		break;
	case RST_INVISIBLE:
		invisible_view += value_;
		if(you.auto_pickup==0)
				auto_pick_onoff(true);
		break;
	case RST_POWER:
		power_keep += value_;
		break;
	}
	return true;
}
bool players::UnidenResistUpDown(int value_, resist_type resist_)
{
	switch(resist_)
	{	
	case RST_POISON:
		uniden_poison_resist += value_;
		break;
	case RST_FIRE:
		uniden_fire_resist += value_;
		break;
	case RST_ICE:
		uniden_ice_resist += value_;
		break;
	case RST_ELEC:
		uniden_elec_resist += value_;
		break;
	case RST_CONFUSE:
		uniden_confuse_resist += value_;
		break;
	case RST_INVISIBLE:
		uniden_invisible_view += value_;
		break;
	case RST_POWER:
		uniden_power_keep += value_;
		break;
	}
	return true;
}
//interupt_type players::HungerApply(int hunger_)
//{
//	hunger_type temp = GetHunger();
//	if(!hunger_)
//	{
//		hunger -= hunger_per_turn>0?hunger_per_turn:1;
//	}
//	else
//	{
//		hunger += hunger_;
//		if(hunger>12000)
//			hunger = 12000;
//	}
//	if(hunger<=0)
//	{
//		dead_reason = DR_HUNGRY;
//		GameOver();
//	}
//	if(temp !=  GetHunger())
//	{
//		switch(GetHunger())
//		{	
//			case HT_STARVING:
//				printlog("굶어죽기 일보직전이다!",true,false,false,CL_danger);
//				break;
//			case HT_NEARSTARVING:
//				printlog("배고파서 쓰러질 것 같다.",true,false,false,CL_warning);
//				break;
//			case HT_VERYHUNGRY:
//				printlog("상당한 배고픔을 느꼈다.",true,false,false,CL_warning);
//				break;
//			case HT_HUNGRY:
//				printlog("당신은 배고파졌다.",true,false,false,CL_warning);
//				break;
//			case HT_NORMAL:
//			case HT_FULL:
//			case HT_VERYFULL:
//			case HT_ENGORGED:
//				break;
//		}
//		return IT_HUNGRY;
//	}
//	return IT_NONE;
//}


bool players::GetExp(int exper_, bool speak_)
{
	bool level_up_ = false;
	exper += exper_;
	skill_exper += exper_;
	ExpRecovery(exper_);
	while(GetNeedExp(level-1) >=0 && GetNeedExp(level-1) <= exper)
	{
		LevelUp(speak_);
		level_up_ = true;
	}
	SkillTraining(speak_);
	return level_up_;
}
void players::ExpRecovery(int exper_)
{	
	exper_recovery -= exper_;
	if(exper_recovery<=0)
	{//일정 경험치를 먹어서 경험치 회복이 이루어짐
		//남은 경험치의 10% 가량을 먹을때마다 1씩
		//초반엔 빠르게 오르므로 그 수치도 많은편(+10 상수치 플러스)
		exper_recovery = GetNeedExp(max(level-2,0))/10+10;


		//여기부터 경험치를 먹으면 생기는 일
		if(s_trans_panalty) //시공부작용의 감소
			s_trans_panalty--;

		if(wiz_list.wizard_mode)
		{
			printlog("일정량의 스킬 경험치 획득",true,false,false,CL_help);
		}

	}
}
int players::GetNeedExp(int level_)
{
	return level_up_value[level_]*exper_aptit/100;
}
bool players::GiveSkillExp(skill_type skill_, int exp_, bool speak_)
{
	if(!speak_)
	{
		you.skill[skill_].onoff = true;
	}
	if(skill_ == SKT_ERROR)
	{
		printlog("스킬경험치에 에러가 발생했습니다.",true,false,false,CL_danger);
		return false;
	}
	int need_exp = need_skill_exp(skill[skill_].level,AptCal(skill[skill_].aptit));

	if(need_exp == -1)
	{
		you.skill[skill_].onoff = false;
		return false;
	}

	int up_point = (exp_*10)/exp_to_skill_exp(skill[skill_].level);
	if(up_point<0)
		up_point = 0;
	skill[skill_].exper += up_point;
	total_skill_exp+=exp_;
	GodAccpect_Practice(up_point,skill_);
	if(need_exp <= skill[skill_].exper)
	{
		char temp[50];
		int exp_pool = (skill[skill_].exper - need_exp)*exp_to_skill_exp(skill[skill_].level)/10;
		skill[skill_].level+=1;
		skill[skill_].exper = need_exp;
		if(skill[skill_].level == 27)
		{			
			you.skill[skill_].onoff = false;
		}

		if(speak_)
		{
			enterlog();
			sprintf_s(temp,50,"%s 스킬레벨이 올랐다! 스킬레벨 %d",skill_string(skill_),skill[skill_].level);
			printlog(temp,true,false,false,CL_good);
			if(skill[skill_].level == 1 || skill[skill_].level % 5 == 0 || skill[skill_].level == 27)
			{
				char temp2[200];
				sprintf_s(temp2,200,"스킬 %s의 레벨업. 스킬레벨 %d",skill_string(skill_),skill[skill_].level);
				AddNote(you.turn,CurrentLevelString(),temp2,CL_normal);
			}
		}
		if(skill_ == SKT_FIGHT)
		{
			CalcuHP();
		}
		else if(skill_ == SKT_DODGE)
		{
			//EvUpDown((level<=5?level%3==1:(level<=12?level%2==0:(level<=20?level%3:(1))))); 뭐에쓰려고한거지
			EvUpDown(1,0);
		}
		else if(skill_ == SKT_ARMOUR)
		{
			AcUpDown(0,0);
			ReSetASPanlty();
		}
		else if(skill_ == SKT_SHIELD)
		{
			ShUpDown(0,0);
			ReSetASPanlty();
		}
		else if(skill_ == SKT_SPELLCASTING)
		{
			remainSpellPoiont+=2;
		}
		if(skill_ == SKT_SPELLCASTING || skill_ == SKT_EVOCATE)
		{
			//최대 마나는 나중에 손보자...
			//일단 3렙마다 최대마나 1증가
			if(skill[skill_].level % 3 == 0)
			{
				if((skill[skill_].level > skill[SKT_SPELLCASTING].level) || skill_ == SKT_SPELLCASTING)
				{
					if((skill[skill_].level > skill[SKT_EVOCATE].level) || skill_ == SKT_EVOCATE)
					{
						mp++;
						max_mp++;
					}
				}
			}
		}



		GiveSkillExp(skill_, exp_pool, speak_);
		return true;
	}
	return false;
}
bool players::SkillTraining(skill_type skill_, int percent_)
{
	if(randA((percent_*(skill[skill_].onoff?1:10))-1)>0)
		return false;
	int exper_ = exp_to_skill_exp(skill[skill_].level);
	if(exper_>skill_exper) //남은 경험치가 필요경험치보다 적을때
	{
		if(1 > skill_exper*10/exper_) //경험치 업이 의미없을때
			return false;
		exper_ = skill_exper;//약간의 경험치만
	}
	if(exper_>0)
	{
		skill_exper -= exper_;
		return GiveSkillExp(skill_,exper_);
	}
	return false;
}
bool players::SkillTraining(bool speak)
{
	int sum = 0, exp;
	for(int i = 0; i < SKT_MAX; i++)
	{
		if(skill[i].onoff){
			sum++;
		}
	}
	if(sum == 0)
		return false;
	exp = skill_exper/sum;
	for(int i = 0; i < SKT_MAX; i++)
	{
		int remain_exp = exp;
		while(skill[i].onoff && remain_exp>0){
			int exper_ = exp_to_skill_exp(skill[i].level);
			if(exper_>remain_exp) //남은 경험치가 필요경험치보다 적을때
			{
				if(1 > remain_exp*10/exper_) //경험치 업이 의미없을때				
					break;
				exper_ = remain_exp;//약간의 경험치만
			}

			if(exper_ > 0)
			{
				remain_exp -= exper_;
				skill_exper -= exper_;
				GiveSkillExp((skill_type)i,exper_,speak);
			}
		}
	}
	return true;
}
bool players::SetPoison(int poison_, int max_, bool strong_)
{
	if(!poison_)
		return false;
	if(poison_resist>0 && !strong_)
		return false;
	if(s_poison >= max_)
		return false;
	else if(poison_resist<0)
		poison_*=2;
	else if(poison_resist>0 && strong_)
		poison_/=3;

	if(!s_poison)
		printlog("당신은 독에 걸렸다.",false,false,false,CL_small_danger);
	else
		printlog("당신의 독은 심해졌다.",false,false,false,CL_small_danger);

	s_poison += poison_;
	if(s_poison>150)
		s_poison = 150;
	if(s_poison>max_)
		s_poison = max_;
	return true;
}

bool players::SetTele(int tele_)
{
	if(!tele_)
		return false;
	if(!s_tele)
	{
		printlog("당신은 공간의 불안정함을 느꼈다.",false,false,false,CL_white_blue);
		s_tele = tele_;
	}
	else
	{
		printlog("당신 주위의 공간은 안정되었다.",false,false,false,CL_normal);
		s_tele = 0;
	}
	return true;
}
bool players::SetMight(int might_)
{
	if(!might_)
		return false;
	if(!s_might)
	{
		printlog("당신은 강력해졌다.",false,false,false,CL_white_blue);
		StatUpDown(5, STAT_STR);
	}
	else
	{
		printlog("당신의 더욱 더 강력해졌다.",false,false,false,CL_white_blue);

	}
	s_might += might_;
	if(s_might>100)
		s_might = 100;
	return true;
}
bool players::SetClever(int clever_)
{
	if(!clever_)
		return false;
	if(!s_clever)
	{
		printlog("당신은 똑똑해졌다.",false,false,false,CL_white_blue);
		StatUpDown(5, STAT_INT);
	}
	else
	{
		printlog("당신은 더욱 더 똑똑해졌다.",false,false,false,CL_white_blue);

	}
	s_clever += clever_;
	if(s_clever>100)
		s_clever = 100;
	return true;
}
bool players::SetAgility(int agility_)
{
	if(!agility_)
		return false;
	if(!s_agility)
	{
		printlog("당신은 민첩해졌다.",false,false,false,CL_white_blue);
		StatUpDown(5, STAT_DEX);
		EvUpDown(0,5);
	}
	else
	{
		printlog("당신의 더욱 더 민첩해졌다.",false,false,false,CL_white_blue);

	}
	s_agility += agility_;
	if(s_agility>100)
		s_agility = 100;
	return true;
}
bool players::SetHaste(int haste_)
{
	if(!haste_)
		return false;
	if(!s_haste)
		printlog("당신은 빨라졌다.",false,false,false,CL_white_blue);
	else
	{
		printlog("당신의 가속은 좀 더 길어졌다.",false,false,false,CL_white_blue);
	}
	s_haste += haste_;
	power_decre = 0;
	if(s_haste>100)
		s_haste = 100;
	return true;
}
bool players::SetConfuse(int confuse_)
{
	if(!confuse_)
		return false;
	if(confuse_resist>0)
		return false;
	confuse_ /= 3; //플레이어는 혼란시간이 적다


	if(!s_confuse)
		printlog("당신은 혼란스러워졌다.",false,false,false,CL_small_danger);
	else
	{
		printlog("당신의 더욱 더 혼란스러워졌다.",false,false,false,CL_small_danger);
		confuse_ /=2;
	}
	s_confuse += confuse_;
	if(s_confuse>10)
		s_confuse = 10;
	return true;
}
bool players::SetSlow(int slow_)
{	
	if(!slow_)
		return false;
	if(!s_slow)
		printlog("당신은 느려졌다.",false,false,false,CL_small_danger);
	else
	{
		printlog("당신의 더욱 더 느려졌다.",false,false,false,CL_small_danger);
		slow_ /=2;
	}
	s_slow += slow_;
	if(s_slow>100)
		s_slow = 100;
	return true;
}
bool players::SetFrozen(int frozen_)
{	
	if(!frozen_)
		return false;
	if(randA_1(5)<ice_resist*2)
		return false;
		
	if(!s_frozen)
		printlog("당신은 몸이 얼어붙어 움직이기 힘들어졌다.",false,false,false,CL_small_danger);
	else
	{
		printlog("당신의 더욱 몸이 얼어붙어 움직이기 힘들어졌다.",false,false,false,CL_small_danger);
		frozen_ /=2;
	}
	s_frozen += frozen_;
	if(s_frozen>25)
		s_frozen = 25;
	return true;
}
bool players::SetElec(int elec_)
{	
	if(!elec_)
		return false;
	if(!s_elec)
		printlog("당신은 전기를 방출하기 시작했다.",false,false,false,CL_white_blue);
	else
	{
		printlog("당신은 더 오랫동안 전기를 방출한다.",false,false,false,CL_white_blue);
	}
	s_elec += elec_;
	if(s_elec>40)
		s_elec = 40;
	return true;
}
bool players::SetParalyse(int paralyse_)
{	
	if(!paralyse_ || s_paralyse)
		return false;

	printlog("당신은 마비되었다.",false,false,false,CL_small_danger);

	s_paralyse += paralyse_;
	if(s_paralyse>100)
		s_paralyse = 100;
	return true;
}
bool players::SetLevitation(int levitation_)
{
	if(!levitation_)
		return false;
	if(!s_levitation)
		printlog("당신은 공중에 뜨기 시작했다.",false,false,false,CL_white_blue);
	else
	{
		printlog("당신은 더 오랫동안 공중에 뜨게 되었다.",false,false,false,CL_white_blue);
	}
	s_levitation += levitation_;
	if(s_levitation>100)
		s_levitation = 100;
	return true;
}
bool players::SetGlow(int glow_)
{
	if(!glow_)
		return false;
	if(!s_glow)
		printlog("당신은 빛을 내기 시작했다.",false,false,false,CL_small_danger);
	else
	{
		printlog("당신은 더 강한 빛을 내고 있다.",false,false,false,CL_small_danger);
		glow_ /=2;
	}
	s_glow += glow_;
	if(s_glow>100)
		s_glow = 100;
	return true;
}
bool players::SetGraze(int graze_)
{
	if(!graze_)
		return false;
	if(!s_graze)
		printlog("당신의 탄막을 피하는 감각이 좋아졌다.",false,false,false,CL_white_blue);
	else
	{
		printlog("당신의 탄막을 피하는 감각이 지속된다.",false,false,false,CL_white_blue);
	}
	if(graze_>0)
		s_graze += graze_;
	else
		s_graze = graze_;
	if(s_graze>100)
		s_graze = 100;
	return true;
}
bool players::SetSilence(int silence_, int silence_range_)
{
	if(!silence_)
		return false;
	if(!s_silence)
		printlog("당신은 주변의 소리를 지웠다.",false,false,false,CL_white_blue);
	else
		printlog("당신은 주변의 소리를 지웠다.",false,false,false,CL_white_blue);
	if(s_silence)
		env[current_level].MakeSilence(position, s_silence_range, false);
	s_silence_range = silence_range_;
	s_silence += silence_;
	env[current_level].MakeSilence(position, s_silence_range, true);
	if(s_silence>50)
		s_silence = 50;
	return true;
}
bool players::SetSick(int sick_)
{
	if(!sick_)
		return false;
	if(!s_sick)
		printlog("당신은 아파졌다.",false,false,false,CL_small_danger);
	else
	{
		printlog("당신은 더욱 아파졌다.",false,false,false,CL_small_danger);
	}
	s_sick += sick_;
	if(s_sick>200)
		s_sick = 200;
	return true;
}
bool players::SetVeiling(int veiling_, int value_)
{
	if(!veiling_)
		return false;
	if(!s_veiling)
		printlog("당신 주변에 바람이 휘감긴다.",false,false,false,CL_white_blue);
	else
	{
		printlog("당신 주변에 휘감긴 바람이 좀 더 오래간다.",false,false,false,CL_white_blue);
	}
	s_veiling += veiling_;
	s_value_veiling = value_;
	if(s_veiling>20)
		s_veiling = 20;
	return true;
}
bool players::SetInvisible(int invisible_)
{
	if(!invisible_)
		return false;
	if(!s_invisible)
		printlog("당신은 투명해졌다.",false,false,false,CL_white_blue);
	else
	{
		printlog("당신은 더 오래 투명해졌다.",false,false,false,CL_white_blue);
	}
	s_invisible += invisible_;
	power_decre = 0;
	if(s_invisible>100)
		s_invisible = 100;
	return true;
}
bool players::SetTogleInvisible(bool off_)
{
	if(off_ || togle_invisible){
		togle_invisible = false;
		return false;
	}
	else{
		togle_invisible = true;
		power_decre = 0;
		return true;
	}
}
bool players::SetBattleCount(int count_)
{
	if(count_<0)
		return false;
	if(battle_count == 0 && count_>0)
	{
		ChangeBattleCount(true);
	}
	else if(battle_count>0 && count_ ==0)
	{
		ChangeBattleCount(false);
	}
	battle_count = count_;
	return true;
}
void players::ChangeBattleCount(bool on_)
{
	//배틀카운터 자체는 바뀌지않은 상태임을 유의한다.
	if(GetProperty(TPT_INVISIBLE))
	{
		if(on_)
			you.SetTogleInvisible(true);
		else
			you.SetTogleInvisible(false);
	}
}
bool players::SetSwift(int swift_)
{
	if(!swift_)
		return false;
	if(s_superman)
		return false;

	if(!s_swift)
		printlog("당신은 다리가 빨라졌다.",false,false,false,CL_white_blue);
	else
	{
		printlog("당신은 더 오래 달릴 수 있다.",false,false,false,CL_white_blue);
	}
	s_swift += swift_;
	if(s_swift>100)
		s_swift = 100;
	return true;
}
bool players::SetManaRegen(int mana_regen_)
{
	if(!mana_regen_)
		return false;
	s_mana_regen += mana_regen_;
	mp_recov = GetNormalDelay();
	if(s_mana_regen>100)
		s_mana_regen = 100;
	return true;
}
bool players::SetSuperMan(int superman_)
{
	if(!superman_)
		return false;
	if(!s_superman)
		printlog("당신은 다리가 엄청나게 빨라졌다.",false,false,false,CL_white_blue);
	else
	{
		printlog("당신은 더 오래 달릴 수 있다.",false,false,false,CL_white_blue);
	}
	s_superman += superman_;
	s_swift = 0;
	if(s_superman>50)
		s_superman = 50;
	return true;
}
bool players::SetSlaying(int slaying_)
{
	if(!slaying_)
		return false;
	s_slaying += slaying_;
	return true;
}
bool players::SetAutumn(int autumn_)
{
	if(!autumn_)
		return false;
	s_autumn = autumn_;
	return true;
}
bool players::SetWind(int s_wind_)
{
	if(!s_wind_)
		return false;
	if(!s_wind)
		printlog("당신의 주변에 바람이 휘감겼다.",false,false,false,CL_white_blue);
	else
	{
		printlog("당신의 주변에 바람이 더 휘감겼다.",false,false,false,CL_white_blue);
	}
	s_wind += s_wind_;
	if(s_wind>200)
		s_wind = 200;
	return true;
}
bool players::SetKnifeCollect(int s_knife_collect_)
{
	if(!s_knife_collect_)
		return false;
	if(!s_knife_collect)
		printlog("당신은 자동으로 탄막을 회수하기 시작한다.",false,false,false,CL_white_blue);
	else
	{
		printlog("탄막을 회수하는 시간이 길어졌다.",false,false,false,CL_white_blue);
	}
	s_knife_collect += s_knife_collect_;
	if(s_knife_collect>100)
		s_knife_collect = 100;
	return true;
}

bool players::SetDrunken(int s_drunken_)
{
	if(!s_drunken_)
		return false;
	if(!s_drunken)
		printlog("당신은 취했다.",false,false,false,CL_warning);
	else
	{
		printlog("당신은 더욱 더 취했다.",false,false,false,CL_warning);
	}
	s_drunken += s_drunken_;
	if(s_drunken>100)
		s_drunken = 100;
	return true;
}

bool players::SetLunatic(int s_lunatic_)
{
	if(!s_lunatic_)
		return false;
	if(confuse_resist>0)
		return false;
	if(!s_lunatic)
		printlog("당신은 광기에 휩싸였다.",false,false,false,CL_danger);
	else
	{
		//printlog("당신은 더욱 더 미쳤다.",false,false,false,CL_warning);
	}
	s_lunatic = s_lunatic_;
	if(s_lunatic>20)
		s_lunatic = 20;
	return true;
}

bool players::SetCatch(monster* unit_)
{
	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(it->s_catch)
			it->s_catch = 0;
		//원래 잡고 있던걸 해제
	}
	if(!unit_)
	{
		s_catch = 0;
		return true;
	}
	s_catch = 1;
	unit_->s_catch = true;

	return true;
}
bool players::SetGhost(int ghost_)
{
	s_ghost = ghost_;
	return true;
}
bool players::SetDimension(int dimension_)
{
	s_dimension = dimension_;
	return true;
}

bool players::SetTimeStep(int timestep_)
{
	s_timestep = timestep_;
	return true;
}
bool players::SetMirror(int mirror_)
{
	printlog("당신은 모든 데미지를 반사한다.",false,false,false,CL_white_blue);
	s_mirror = mirror_;
	return true;

}
bool players::SetParadox(int s_paradox_)
{
	if(s_paradox_)
		printlog("당신은 도플갱어를 통해 탄막을 연달아 발사할 준비가 되었다.",true,false,false,CL_white_blue);
	s_paradox = s_paradox_;
	return true;

}

bool players::SetTransPanalty(int s_trans_panalty_)
{
	if(!s_trans_panalty_)
		return false;

	if(s_trans_panalty_<3)
		printlog("약간의 시공간 부작용을 받았다.",true,false,false,CL_bad);
	else if(s_trans_panalty_<5)
		printlog("상당한 시공간 부작용을 받았다.",true,false,false,CL_normal);
	else
		printlog("어마어마한 시공간 부작용을 받았다.",true,false,false,CL_small_danger);
	s_trans_panalty += s_trans_panalty_;
	return true;
}
bool players::SetTheWorld(int s_the_world_)
{
	if(!s_the_world_)
		return false;
	if(!s_the_world)
		printlog("더 월드!",false,false,false,CL_white_blue);
	else
	{
	}
	s_the_world = s_the_world_;
	if(s_the_world>20)
		s_the_world = 20;
	return true;
}
bool players::SetManaDelay(int s_mana_delay_)
{
	if(!s_mana_delay_)
		return false;

	s_mana_delay = s_mana_delay_;

	return true;
}
bool players::SetBuff(stat_up stat_, buff_type id_, int value_, int turn_)
{
	if(id_ != BUFF_DUPLE){
		for(list<buff_class>::iterator it=buff_list.begin();it!=buff_list.end();it++)
		{
			if(it->id == id_){ //id가 겹치면 기존의 버프를 덮어 씌운다.
			
				UpDownBuff(it->stat,-1*it->value);
				it->stat = stat_;
				it->turn = turn_;
				it->value = value_;
				UpDownBuff(it->stat,it->value);
				return true;
			}
		}
	}
	buff_list.push_back(buff_class(stat_, id_, value_, turn_));
	
	UpDownBuff(stat_,value_);

	return false;
}
bool players::SetProperty(tribe_proper_type type_, int value_)
{
	property_vector.push_back(tribe_property(type_, value_));
	property_vector.back().gain(true);
	return true;
}
bool players::SetStatBoost(int sdi_, int value_)
{
	if(s_stat_boost)
	{
		you.StatUpDown(s_stat_boost_value*(s_stat_boost==1?-2:1),STAT_STR);
		you.StatUpDown(s_stat_boost_value*(s_stat_boost==2?-2:1),STAT_DEX);
		you.StatUpDown(s_stat_boost_value*(s_stat_boost==3?-2:1),STAT_INT);
	}
	//이전 스탯보너스 되돌리기

	s_stat_boost = sdi_;
	s_stat_boost_value = value_;

	
	if(s_stat_boost)
	{
		you.StatUpDown(s_stat_boost_value*(s_stat_boost==1?2:-1),STAT_STR);
		you.StatUpDown(s_stat_boost_value*(s_stat_boost==2?2:-1),STAT_DEX);
		you.StatUpDown(s_stat_boost_value*(s_stat_boost==3?2:-1),STAT_INT);
	}
	return true;

}
bool players::SetEirinHeal(int value_)
{

	int real_value_ = min(max_hp-hp, value_);
	
	//수치만큼 힐하기
	
	you.HpUpDown(real_value_,DR_EFFECT);

	s_eirin_poison += real_value_;
	s_eirin_poison_time = rand_int(100,200);

	return true;

}
int players::GetInvisible()
{
	return s_invisible;
}
int players::GetResist()
{
	return level * 6 + 100+magic_resist;
}
int players::GetProperty(tribe_proper_type type_)
{
	for(auto it = property_vector.begin(); it != property_vector.end(); it++)
	{
		if(it->id == type_)
		{
			return it->value;
		}
	}
	return 0;
}
int players::DeleteProperty(tribe_proper_type type_)
{
	for(auto it = property_vector.begin(); it != property_vector.end(); it++)
	{
		if(it->id == type_)
		{
			int temp = it->value;
			property_vector.erase(it);
			return temp;
		}
	}
	return 0;
}
bool players::Teleport()
{
	while(1)
	{
		int x_ = randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
		if(env[current_level].isMove(x_,y_) && !env[current_level].isMonsterPos(x_,y_))
		{
			env[current_level].MakeSmoke(position, img_fog_normal, SMT_NORMAL, 4, 0, this);
			SetXY(x_,y_);
			return true;
		}
	}
}
bool players::Blink(int time_)
{
	int x_ = position.x, temp_x_ = x_, prev_x=x_;
	int y_ = position.y, temp_y_ = y_, prev_y=y_;
	//xy_ : 현재 블링크에 도착할 위치(예정)  
	//temp_xy_ : 블링크할 위치를 미리 찾아서 이동가능한지 확인한다.
	//prev_xy_ : 블링크 할 수 있는 안전한 위치 저장(만약 xy_가 끝까지 안전한 위치를 못찾을 경우)
	for(int i=0;i<time_+10;i++)
	{
		temp_x_=x_+rand_int(-1,1);
		temp_y_=y_+rand_int(-1,1);
		if(env[current_level].isMove(temp_x_,temp_y_,true))
		{
			x_ = temp_x_;
			y_ = temp_y_;
			if((i>=time_ || i%5 == 0) && env[current_level].isMove(x_,y_,false) && !env[current_level].isMonsterPos(x_,y_) && !(you.position.x == x_ && you.position.y == y_) && !env[current_level].isSmokePos(x_,y_))
			{
				prev_x = x_;
				prev_y = y_;
				if(i>=time_)
				{					
					break;
				}
			}
		}
	}
	env[current_level].MakeSmoke(position, img_fog_normal, SMT_NORMAL, 4, 0, this);
	SetXY(coord_def(prev_x,prev_y));
	return true;
}
bool players::control_blink(const coord_def &c)
{
	if(env[current_level].isMove(c.x,c.y) && !env[current_level].isMonsterPos(c.x,c.y))
	{
		env[current_level].MakeSmoke(position, img_fog_normal, SMT_NORMAL, 4, 0, this);
		SetXY(c.x,c.y);
		return true;
	}
	return false;
}
void players::LevelUp(bool speak_)
{
	level++;
	if(speak_)
	{
		char temp[50];
		sprintf_s(temp,50,"당신의 레벨이 올랐다! 레벨 %d",you.level);
		printlog(temp,true,false,false,CL_good);
		MoreWait();
	}
	if(level%3 == 0)
	{
		if(speak_)
		{
			bool end_ = false;
			printlog("당신의 올릴 능력치를 고르세요. (S)tr - 힘, (D)ex - 민첩, (I)nt - 지능",true,false,false,CL_help);
			while(!end_)
			{
				switch(waitkeyinput())
				{
				case 'S':
				case 's':
					you.StatUpDown(1,STAT_STR);
					printlog("강력해졌다.",true,false,false,CL_good);
					end_ = true;
					break;
				case 'D':
				case 'd':
					you.StatUpDown(1,STAT_DEX);
					printlog("민첩해졌다.",true,false,false,CL_good);
					end_ = true;
					break;
				case 'I':
				case 'i':
					you.StatUpDown(1,STAT_INT);
					printlog("똑똑해졌다.",true,false,false,CL_good);
					end_ = true;
					break;
				}
			}
		}
		else
		{
			if(you.s_str > you.s_dex && you.s_str > you.s_int)
				you.StatUpDown(1,STAT_STR);
			else if(you.s_dex > you.s_str && you.s_dex > you.s_int)
				you.StatUpDown(1,STAT_DEX);
			else
				you.StatUpDown(1,STAT_INT);
		}
	}

	if(level == 9 && GetProperty(TPT_9_LIFE))
	{
		printlog("당신은 충분히 성장하여 부활능력을 하나 잃었다.",true,false,false,CL_small_danger);
		image = &img_play_mokou[1];
		DeleteProperty(TPT_9_LIFE);
	}
	if(level == 18 && GetProperty(TPT_18_LIFE))
	{
		printlog("당신은 충분히 성장하여 부활능력을 모두 잃었다.",true,false,false,CL_small_danger);
		image = &img_play_mokou[2];
		DeleteProperty(TPT_18_LIFE);
	}

	CalcuHP();
	max_mp += 1;
	mp += 1;
	if(level % 3 == 0)
	{
		max_mp += 1;
		mp += 1;

	}


	remainSpellPoiont++;
	LevelUpTribe(level);
	
	if(speak_)
	{
		char temp[200];
		sprintf_s(temp,200,"레벨업 : 레벨 %2d. HP: %4d/%4d , MP: %4d/%4d", level,hp,max_hp,mp,max_mp);
		AddNote(you.turn,CurrentLevelString(),temp,CL_good);
	}
}
list<item>::iterator players::GetThrowIter()
{
	list<item>::iterator it = you.item_list.begin();
	for(;it != you.item_list.end();it++)
	{
		if(&(*it) == throw_weapon)
			break;
	}
	return it;

}
vector<monster>::iterator players::GetTargetIter()
{
	vector<monster>::iterator it = env[current_level].mon_vector.begin();
	for(;it != env[current_level].mon_vector.end();it++)
	{
		if((*it).isLive() && (*it).map_id == target && (*it).isYourShight() && !(*it).isUserAlly())
			break;
	}
	return it;
}

interupt_type players::resetLOS(bool speak_)
{
	interupt_type interrupt_ = IT_NONE;
	for(int x=0;x<DG_MAX_X;x++)
	{
		for(int y=0;y<DG_MAX_Y;y++)
		{
			//if(abs(position.x-x)+abs(position.y-y)>8)

			bool out_of_sight = pow((float)abs(position.x-x),2)+pow((float)abs(position.y-y),2)>64;
			if((out_of_sight && !you.s_dimension) || env[current_level].DisableMove(coord_def(x,y),true))
			{
				env[current_level].dgtile[x][y].flag = env[current_level].dgtile[x][y].flag & ~FLAG_INSIGHT;

				if(env[current_level].isBamboo())
				{
					env[current_level].dgtile[x][y].flag = env[current_level].dgtile[x][y].flag & ~FLAG_EXPLORE;
				}
			}
			else
			{
				bool intercept = false;
				for(int i=RT_BEGIN;i!=RT_END;i++)
				{
					coord_def goal_ = coord_def(x,y);
					if(you.s_dimension && out_of_sight)
					{
						if(abs(position.x - goal_.x)>8)
							goal_.x += (position.x - goal_.x)>0?17:-17;
						if(abs(position.y - goal_.y)>8)
							goal_.y += (position.y - goal_.y)>0?17:-17;
					}
					if(distan_coord(position,goal_)>64)
					{
						env[current_level].dgtile[x][y].flag = env[current_level].dgtile[x][y].flag & ~FLAG_INSIGHT;
						if(env[current_level].isBamboo())
						{
							env[current_level].dgtile[x][y].flag = env[current_level].dgtile[x][y].flag & ~FLAG_EXPLORE;
						}
						intercept = true;
						break;	
					}
					beam_iterator it(you.position,goal_,(round_type)i);




					int block_cloud=2;
					while(!intercept && !it.end())
					{
						
						coord_def check_pos_ = (*it);
						
						if(you.s_dimension && out_of_sight)
						{
							if(abs(you.god_value[0] - check_pos_.x)>8)
								check_pos_.x += (you.god_value[0] - check_pos_.x)>0?17:-17;
							if(abs(you.god_value[1] - check_pos_.y)>8)
								check_pos_.y += (you.god_value[1] - check_pos_.y)>0?17:-17;
						}


						if(!env[current_level].isSight(check_pos_))
						{
							intercept = true;
							break;					
						}
						if(env[current_level].isSmokePos(check_pos_.x,check_pos_.y,true))
						{
							smoke* smoke_ = env[current_level].isSmokePos2(check_pos_.x,check_pos_.y);
							if(smoke_->sight_inter())
							{
								block_cloud-=smoke_->sight_inter();
								if(!block_cloud)
								{
									intercept = true;
									break;
								}
							}
						}
						it++;
					}
					if(intercept == false)
						break;
					else if(i == RT_END - 1)
					{
						env[current_level].dgtile[x][y].flag = env[current_level].dgtile[x][y].flag & ~FLAG_INSIGHT;
						if(env[current_level].isBamboo())
						{
							env[current_level].dgtile[x][y].flag = env[current_level].dgtile[x][y].flag & ~FLAG_EXPLORE;
						}
					}
					else
						intercept = false;
				}
				if(!intercept)
				{
					coord_def check_pos_ = coord_def(x,y);
						
					//if(you.s_dimension && out_of_sight)
					//{
					//	if(abs(you.god_value[0] - check_pos_.x)>8)
					//		check_pos_.x += (you.god_value[0] - check_pos_.x)>0?-17:17;
					//	if(abs(you.god_value[1] - check_pos_.y)>8)
					//		check_pos_.y += (you.god_value[1] - check_pos_.y)>0?-17:17;
					//}
					

					env[current_level].dgtile[check_pos_.x][check_pos_.y].flag |= FLAG_INSIGHT;
					if(!(env[current_level].dgtile[check_pos_.x][check_pos_.y].flag & FLAG_EXPLORE))
					{
						if(explore_map++ % 100 == 0)
						{
							GodAccpect_Explore_100();
						}
						env[current_level].dgtile[check_pos_.x][check_pos_.y].flag |= FLAG_EXPLORE;
						switch(env[current_level].dgtile[check_pos_.x][check_pos_.y].tile)
						{
						case DG_DOWN_STAIR:
						case DG_UP_STAIR:
						case DG_RETURN_STAIR:
						case DG_TEMPLE_STAIR:							
						case DG_MISTY_LAKE_STAIR:
						case DG_YOUKAI_MOUNTAIN_STAIR:
						case DG_SCARLET_STAIR:							
						case DG_SCARLET_L_STAIR:
						case DG_SCARLET_U_STAIR:
						case DG_BAMBOO_STAIR:
						case DG_EIENTEI_STAIR:
						case DG_SUBTERRANEAN_STAIR:
						case DG_YUKKURI_STAIR:
						case DG_DEPTH_STAIR:
						case DG_DREAM_STAIR:
						case DG_MOON_STAIR:		
						case DG_PANDEMONIUM_STAIR:	
						case DG_HAKUREI_STAIR:
						case DG_TEMPLE_SHIKIEIKI:
						case DG_TEMPLE_BYAKUREN:
						case DG_TEMPLE_KANAKO:
						case DG_TEMPLE_SUWAKO:
						case DG_TEMPLE_MINORIKO:
						case DG_TEMPLE_MIMA:
						case DG_TEMPLE_SHINKI:
						case DG_TEMPLE_YUUGI:
						case DG_TEMPLE_SHIZUHA:
						case DG_TEMPLE_HINA:
						case DG_TEMPLE_YUKARI:
						case DG_TEMPLE_EIRIN:
						case DG_TEMPLE_YUYUKO:
						case DG_TEMPLE_SATORI:
						case DG_TEMPLE_TENSI:
							if(speak_)
							{
								printlog(dungeon_tile_tribe_type_string[env[current_level].dgtile[check_pos_.x][check_pos_.y].tile],false,false,false,CL_normal);
								printlog("을 발견했다.",true,false,false,CL_normal);	
							}
							interrupt_ = IT_MAP_FIND;
							break;
						default:
							break;
						}
					}
					if(env[current_level].dgtile[check_pos_.x][check_pos_.y].flag & FLAG_DANGER)
						interrupt_ = IT_MAP_DANGER;
				}
			}

			
			env[current_level].dgtile[x][y].flag = env[current_level].dgtile[x][y].flag & ~FLAG_LIGHT;


		}

	}
	return interrupt_;
	//테스트
	/*beam_iterator it(you.position,coord_def(5,6));
	while(!it.end())
	{
		env[current_level].dgtile[(*it).x][(*it).y].flag = env[current_level].dgtile[(*it).x][(*it).y].flag | FLAG_LIGHT;
		it++;
	}*/
}


void players::MakeLOSPattern() 
{
	//만들고나서 안거지만 던전크롤은 이 알고리즘으로 동작하지않는다.
	//쓰지말것
	FILE *f;
	f= fopen("shadowpattern.txt","wt");
	int yy_ = 0;

	char arrays[9][9];
	while(yy_<=8)
	{
		for(int xx_ = 0;xx_<=8;xx_++)
		{
			for(int sss=0;sss<=8;sss++)
			{
				for(int qqq=0;qqq<=8;qqq++)
				{
					arrays[sss][qqq] = false;
				}
			}

			for(int y=0;y<=8;y++)
			{
				for(int x=0;x<=8;x++)
				{
					bool intercept = false;
					for(int i=RT_BEGIN;i!=RT_END;i++)
					{
						beam_iterator it(coord_def(0,0),coord_def(x,y),(round_type)i);
						while(!intercept && !it.end())
						{
							if((*it).x == xx_ && (*it).y == yy_)
							{
								intercept = true;
								break;
							}
							it++;
						}
						if(intercept == false)
							break;
						else if(i!=RT_END-1)
							intercept = false;
					}
					if(intercept)
					{
						arrays[x][y] = true;
					}
				}
			}
			
			fprintf(f,"(%d,%d)",xx_,yy_);
			for(int y=0;y<=8;y++)
			{
				for(int x=0;x<=8;x++)
				{				
					if(arrays[x][y])
					{
						fprintf(f," %d-%d",x,y);
					}
				}
			}
			fprintf(f,"\n");
			//패턴저장
		}
		yy_++;
	}
	fclose(f);

}



int players::additem(item *t, bool speak_) //1이상이 성공, 0이하가 실패
{
	WaitForSingleObject(mutx, INFINITE);
	char num='a';
	list<item>::iterator it;
	if(t->type == ITM_FOOD && t->value1 == 0)
	{
		PowUpDown(t->value5);
		if(speak_)
			printlog("P가 증가했다.",false,false,false,CL_normal);
		ReleaseMutex(mutx);
		GodAccpect_GetPitem();
		return 1;
	}

	if(t->is_pile)
	{
		for(it = item_list.begin(); it != item_list.end() ;it++)
		{
			if(t->SameItem(*it))
			{				
				//if(max_item_weight >= item_weight + t->weight)
				//{
					it->weight += t->weight;
					item_weight += t->weight;
					it->num += t->num;
					if(speak_)
					{
						char temp[2];
						sprintf(temp,"%c",it->id);
						printlog(temp,false,false,false,it->item_color());
						printlog(" - ",false,false,false,it->item_color());
						printlog(it->GetName(),true,false,false,it->item_color());
					}
					t->pick();
					final_item = it->id;
					final_num = t->num;
					ReleaseMutex(mutx);
					return 1;
				//}
				//else
				//{
				//	printlog("더 가지기엔 너무 무겁다!",true,false,false,CL_normal);
				//	ReleaseMutex(mutx);
				//	return 0;
				//}
			}
		}
	}
	//for(;num == 'Z';num++)
	//{
	//	bool check_ = false;
	//	for(it = item_list.begin(); it != item_list.end() ;it++)
	//	{
	//		if((*it).id == num)
	//		{
	//			check_ = true;
	//			break;
	//		}
	//	}
	//	if(check_ == false)
	//		break;
	//	if(num=='z')
	//		num = 'A'-1;
	//}
	for(it = item_list.begin(); it != item_list.end() && num != 'Z'+1;it++,num++)
	{
		if((*it).id != num)
			break;
		if(num=='z')
			num = 'A'-1;
	}
	if((num >= 'a' && num <= 'z') || (num >= 'A' && num <= 'Z'))
	{
		//if(max_item_weight >= item_weight + t->weight)
		//{
			t->id = num;
			item_weight += t->weight;
			list<item>::iterator it_temp = item_list.insert(it,*t);
			if(!throw_weapon && t->can_throw)
			{
				throw_weapon = &(*it_temp);
			}
			if(speak_)
			{
				char temp[2];
				sprintf(temp,"%c",(*t).id);
				printlog(temp,false,false,false,(*t).item_color());
				printlog(" - ",false,false,false,(*t).item_color());
				printlog((*t).GetName(),true,false,false,(*t).item_color());
			}
			it_temp->pick();
			final_item = t->id;
			final_num = t->num;
			ReleaseMutex(mutx);
			return 1;
		//}
		//else
		//{
		//	printlog("더 가지기엔 너무 무겁다!",true,false,false,CL_normal);
		//	ReleaseMutex(mutx);
		//	return 0;
		//}
	}
	else
	{
		printlog("가질 수 있는 갯수를 초과했다.",true,false,false,CL_normal);
		ReleaseMutex(mutx);
		return 0;
	}
}

bool players::DeleteItem(const list<item>::iterator it, int num_)
{
	WaitForSingleObject(mutx, INFINITE);
	if(num_>0 && it->is_pile && it->num > num_)
	{
		item_weight -= (it->weight)* num_ /(it->num);
		it->weight -= (it->weight)* num_ /(it->num) ;
		it->num -= num_;
	}
	else
	{
		for(int i=ET_FIRST; i<ET_LAST;i++)
		{
			if(equipment[i] == &(*it))
				equipment[i] = NULL;
		}
		if(throw_weapon == &(*it))
			throw_weapon = NULL;
		item_weight -= it->weight;
		item_list.erase(it);
		ReleaseMutex(mutx);
		return 1;
	}
	ReleaseMutex(mutx);

	return 0;
}

bool players::Eat(char id_)
{
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if((*it).id == id_)
		{
			WaitForSingleObject(mutx, INFINITE);
			if((*it).type == ITM_FOOD)
			{
				if(!you.isequip(it))
				{
					//if(it->value1 == 0 && GetHunger() >= HT_NORMAL)
					//{
					//	printlog("당신은 아직 배고프지 않다.",true,false,false,CL_normal);
					//	ReleaseMutex(mutx);
					//	return false;		
					//}
					if((*it).value1 == 0)
						(*it).value3 = 100;
					printlog("음식을 먹기 시작했다.",true,false,false,CL_bad);
					time_delay += you.GetNormalDelay();
					TurnEnd();
					
					if(you.god == GT_MINORIKO && !you.punish[GT_MINORIKO] && pietyLevel(you.piety)>=5)
					{
						int rand_num_ =  rand_int(80,100);
						you.SetBuff(BUFFSTAT_RF,BUFF_MINORIKO_RF,1,rand_num_);
						you.SetBuff(BUFFSTAT_RC,BUFF_MINORIKO_RC,1,rand_num_);
					}
					if(you.god == GT_MINORIKO && !you.punish[GT_MINORIKO] && pietyLevel(you.piety)>=3)
					{
						you.MpUpDown(2+(*it).value5/30+randA(3+(*it).value5/10));
					}
					else
					{
						time_delay += you.GetNormalDelay();
						TurnEnd();
						time_delay += you.GetNormalDelay();
						TurnEnd();
					}
					printlog("음식을 전부 먹었다.",false,false,false,CL_normal);
					PowUpDown((*it).value5);
					DeleteItem(it,1);
					enterlog();
					ReleaseMutex(mutx);
					return true;		
				}
				else
				{
					printlog("장착중인 아이템이다.",true,false,false,CL_normal);
					ReleaseMutex(mutx);
					return false;		
				}		
			}
			else
			{
				printlog("이건 음식이 아니다.",true,false,false,CL_normal);
				ReleaseMutex(mutx);
				return false;				
			}
		}
	}
	printlog("존재하지 않는 아이템",true,false,false,CL_normal);
	ReleaseMutex(mutx);
	return false;
}
bool players::Drink(char id_)
{
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if((*it).id == id_)
		{
			WaitForSingleObject(mutx, INFINITE);
			if((*it).type == ITM_POTION)
			{
				if(!you.isequip(it))
				{
					drinkpotion((potion_type)(*it).value1);
					
					if(iden_list.potion_list[(*it).value1].iden == false)
					{		
						printarray(false,false,false,CL_normal,3,"이것은 ",potion_iden_string[(*it).value1],"물약이다. ");		
					}
					iden_list.potion_list[(*it).value1].iden = true;
					(*it).identify = true;
					DeleteItem(it,1);
					enterlog();
					ReleaseMutex(mutx);
					return true;	
				}
				else
				{
					printlog("장착중인 아이템이다.",true,false,false,CL_normal);
					ReleaseMutex(mutx);
					return false;		
				}					
			}
			else
			{
				printlog("이건 마실 수 없다.",true,false,false,CL_normal);
				ReleaseMutex(mutx);
				return false;				
			}
		}
	}
	printlog("존재하지 않는 아이템",true,false,false,CL_normal);
	return false;
}
bool players::Evoke(char id_)
{
	for(auto it = item_list.begin(); it != item_list.end(); it++)
	{
		if((*it).id == id_)
		{
			WaitForSingleObject(mutx, INFINITE);
			if((*it).type == ITM_SPELL)
			{
				if(((*it).identify || (*it).value3 == -1) && !(*it).value1)
				{
					printlog("남은 횟수가 없다.",true,false,false,CL_normal);
					ReleaseMutex(mutx);
					return false;	
				}
				ReleaseMutex(mutx);
				int bonus_pow_ = 20+max(you.level*3+skill[SKT_EVOCATE].level*2 , skill[SKT_EVOCATE].level*5);
				if(evoke_spellcard((spellcard_evoke_type)(*it).value2, bonus_pow_,(*it).value1 == 0, iden_list.spellcard_list[(*it).value2].iden == 2))
				{
					WaitForSingleObject(mutx, INFINITE);
					if(!(*it).value1)
					{
						printlog("남은 횟수가 없다.",true,false,false,CL_normal);
						(*it).value3 = -1; //-1이면 비어있는것이 확정
						ReleaseMutex(mutx);
						return true;
					}
					iden_list.spellcard_list[(*it).value2].iden = 2;
					(*it).value1--;
					if((*it).value3<0)
						(*it).value3 = 0;
					(*it).value3++;//사용예측 횟수를 늘린다.
					ReleaseMutex(mutx);
					
					you.doingActionDump(DACT_EVOKE, (*it).name.name);
					return true;
				}
				return false;
			}
			if((*it).type == ITM_MISCELLANEOUS)
			{
				ReleaseMutex(mutx);

				if(evoke_evokable((evoke_kind)(*it).value1))
				{					
					you.doingActionDump(DACT_EVOKE, (*it).name.name);
					return true;
				}
			}
			else
			{
				printlog("이것은 발동할 수 없다.",true,false,false,CL_normal);
				ReleaseMutex(mutx);
				return false;	
			}
		}
	}
	printlog("존재하지 않는 아이템",true,false,false,CL_normal);
	ReleaseMutex(mutx);
	return false;
}
bool players::Read(char id_)
{
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if((*it).id == id_)
		{
			if(!you.isequip(it))
			{
				WaitForSingleObject(mutx, INFINITE);
				if((*it).type == ITM_SCROLL)
				{

					printarray(true,false,false,CL_normal,3,it->GetName(-2).c_str(),it->GetNameInfor().name_to(true),"읽었다.");
					bool pre_iden_ = (iden_list.scroll_list[(*it).value1].iden == 3);
					bool use_ = readscroll((scroll_type)(*it).value1, pre_iden_);
					
					if(!use_)
					{		
						ReleaseMutex(mutx);
						return false;		
					}

					if(iden_list.scroll_list[(*it).value1].iden == 3)
					{
						if(!pre_iden_)
							printarray(true,false,false,CL_normal,3,"이것은 ",it->GetName().c_str(),it->GetNameInfor().name_type?"이다":"다.");

						(*it).identify = true;

					}
					//if(!you.skill[SKT_SPELLCASTING].level)
					//	SkillTraining(SKT_SPELLCASTING,1);

					DeleteItem(it,1);
					enterlog();
					ReleaseMutex(mutx);
					return true;	
				}
				else
				{
					printlog("이건 읽을 수 없다.",true,false,false,CL_normal);
					ReleaseMutex(mutx);
					return false;		
				}							
			}
			else
			{
				printlog("장착중인 아이템이다.",true,false,false,CL_normal);
				ReleaseMutex(mutx);
				return false;				
			}
		}
	}
	printlog("존재하지 않는 아이템",true,false,false,CL_normal);
	return false;
}
bool players::Memorize(int spell_, bool immediately)
{
	if(spell_ <= SPL_NONE || spell_ > SPL_MAX)
		return false;
	int skill_level_ = SpellLevel((spell_list)spell_);
	
	if(you.skill[SKT_SPELLCASTING].level == 0)
	{
		printlog("당신은 아직 주문을 배울 수 없다!",true,false,false,CL_normal);
		return false;
	}
	if(!immediately && you.level<skill_level_)
	{
		printlog("이 주문을 배우기엔 레벨이 모자란다.",true,false,false,CL_normal);
		return false;
	}
	if(you.remainSpellPoiont<skill_level_)
	{
		char temp[100];
		sprintf_s(temp,100,"남은 마법 레벨이 %d만큼 모자란다.",skill_level_-you.remainSpellPoiont);
		printlog(temp,true,false,false,CL_normal);
		return false;
	}
	if(currentSpellNum == 52)
	{
		printlog("당신은 더 이상 주문을 기억할 공간이 없다.",true,false,false,CL_normal);
		return false;
	}
	if(!immediately)
	{
		printlog("마법을 익히기 시작했다.",true,false,false,CL_bad);
		for(int i=0;i<skill_level_;i++)//맞아서 취소되기 추가
		{
			time_delay += you.GetNormalDelay();
			TurnEnd();
		}
		if(0/*randA_1(100)>GetSpellSuccess(spell_)*/)
		{
			printlog("주문을 익히는데 실패했다.",true,false,false,CL_normal);
			return false;		
		}
		printlog("주문을 익히는데 성공했다.",true,false,false,CL_normal);

		char temp[200];
		sprintf_s(temp,200,"주문 기억 : %d레벨 %s",SpellLevel((spell_list)spell_),SpellString((spell_list)spell_));
		AddNote(you.turn,CurrentLevelString(),temp,CL_normal);
	}
	you.remainSpellPoiont-=skill_level_;
	you.MemorizeSpell[currentSpellNum++] = spell_;
	return true;
}
int players::Ability(int skill_, bool god_, bool unset_, int immediately)
{
	int set_=-1;
	for(int i=(god_?0:5);i<26;i++)
	{
		if(MemorizeSkill[i] == skill_)
		{
			set_ = i;
			break;
		}
	}
	if(set_ == -1 && !unset_)
	{
		for(int i=(god_?0:5);i<26;i++)
		{
			if(!MemorizeSkill[i])
			{
				set_ = i;
				break;
			}
		}
	}
	
	if(!unset_) //추가
	{
		if(set_ != -1)
		{
			int temp = MemorizeSkill_num[set_];
			MemorizeSkill[set_] = skill_;
			MemorizeSkill_num[set_]=(immediately)?(immediately):(MemorizeSkill_num[set_]+1);
			if(temp == 0)
				currentSkillNum++;
			return MemorizeSkill_num[set_];
		}
	}
	else //삭제
	{
		if(set_ != -1)
		{
			int temp = MemorizeSkill_num[set_]--;
			if(immediately || MemorizeSkill_num[set_] == 0)
			{
				MemorizeSkill_num[set_] = 0;
				MemorizeSkill[set_] = 0;
				if(temp)
					currentSkillNum--;
			}
			return temp;
		}
	}
	return 0;
}
bool players::Belief(god_type god_, int piety_, bool speak_)
{
	if(god_<GT_FIRST || god_>=GT_LAST)
	{
		if(speak_)
			printlog("존재하지 않는 신입니다.",true,false,false,CL_danger);
		return false;
	}
	if(god != GT_NONE)
	{
		if(god == god_)
		{
			if(speak_)
				printlog("이미 믿고 있는 신입니다.",true,false,false,CL_normal);
			return false;
		}		
		PietyUpDown(0,true);
		PunishUpDown(GetGodAbandonValue(god),god);
	}
	else	
		PietyUpDown(0,true);
	god = god_;
	god_turn = 0;
	if(speak_)
	{
		char temp[100];
		sprintf_s(temp,100,"%s의 신도가 되었다.",GetGodString(god));	
		printlog(temp,true,false,false,CL_help);	
	}
	{
		char temp[200];
		sprintf_s(temp,200,"%s의 신도가 되었다.",GetGodString(god));
		AddNote(you.turn,CurrentLevelString(),temp,CL_help);
	}
	GetGodAbility(0, true);
	PietyUpDown(isTutorial()?160:piety_,true);
	if(isTutorial())
	{
		gift_count=30;
	}
	return true;

}
bool players::PietyUpDown(int piety_, bool absolutely_)
{
	int prev_ = pietyLevel(piety);
	piety = absolutely_?piety_:piety_+piety;
	if(piety<0)
		piety = 0;
	else if(piety>200)
		piety = 200;
	int next_ = pietyLevel(piety);
	int differ_ = prev_>next_?-1:1;
	if(prev_!=next_) //????
	{
		for(int i = prev_; i != next_;i+=differ_)
		{
			GetGodAbility(i+(differ_==1),(differ_==1));
		}
	}
	return false;
}
bool players::GiftCount(int value_)
{
	if(!GetGodGiftTime(god))
		return false;

	if((gift_count-=value_)<=0)
	{
		GodGift(god,piety);
		gift_count = GetGodGiftTime(god);
		return true;
	}
	return false;
}
bool players::PunishUpDown(int punish_, god_type god_ , bool absolutely_ )
{
	if(god_ == GT_NONE)
		god_ = god;
	punish[god_] = absolutely_?punish_:punish_+punish[god_];
	char temp[100];
	sprintf_s(temp,100,"%s의 분노를 느꼈다.",GetGodString(god_));
	printlog(temp,true,false,false,CL_danger);
	return true;
	
}
bool players::Throw(list<item>::iterator it, coord_def target_pos_, bool short_, beam_iterator& beam)
{
	//던질때 장비된 아이템이면 장비가 풀리도록 만들어야함
	//저주받은 템은 던질 수 없다!
	if((*it).can_throw)
	{
		int type_ = 0;
		int pentan_ = s_wind?8:1;
		beam_type beam_type_ = s_wind?BMT_PENETRATE:BMT_NORMAL;
		beam_infor temp_infor(GetThrowAttack(&(*it),false),GetThrowAttack(&(*it),true),GetThrowHit(&(*it)),this,GetParentType(),8,pentan_,beam_type_,ATT_THROW_NORMAL,(*it).GetNameInfor());
		if((*it).type >= ITM_THROW_FIRST && (*it).type < ITM_THROW_LAST )
		{
			type_ = GetTanmacGraphicType((tanmac_type)(*it).value4);
			temp_infor.type2 = GetTanmacAttackType((tanmac_type)(*it).value4);
		}
		else
		{
			if((*it).value5)
				temp_infor.type2 = GetWeapontoTanmac((weapon_brand)(*it).value5);
		}

		if((*it).type >= ITM_THROW_FIRST && (*it).type < ITM_THROW_LAST && (*it).value4 == TMT_KIKU_COMPRESSER)
		{ //키쿠이치 컴프레서 전용

			int length_ = ceil(sqrt(pow((float)abs(you.position.x-target_pos_.x),2)+pow((float)abs(you.position.y-target_pos_.y),2)));
	
			temp_infor.length = length_;
			for(int i=0;i<(you.GetParadox()?2:1);i++)
			{
				coord_def c_ = throwtanmac(type_,beam,temp_infor,&(*it));
				int power_ = skill[SKT_TANMAC].level*5;
				attack_infor temp_att(randC(3,5+power_/8),3*(5+power_/8),99,&you,you.GetParentType(),ATT_NORMAL_BLAST,name_infor("물보라",false));
				BaseBomb(c_,&img_fog_cold[0],temp_att);
			}
		}
		else
		{
			int length_ = ceil(sqrt(pow((float)abs(you.position.x-target_pos_.x),2)+pow((float)abs(you.position.y-target_pos_.y),2)));
		
			if(short_)
				temp_infor.length = length_;
			for(int i=0;i<(you.GetParadox()?2:1);i++)
			{
				throwtanmac(type_,beam,temp_infor,&(*it));
			}
		}
		you.SetParadox(0);

				
		doingActionDump(DACT_SHOOT, (*it).name.name);


		time_delay += GetThrowDelay((*it).type);
		if((!s_knife_collect || TanmacDeleteRand((tanmac_type)(*it).value4)) && DeleteItem(it,1))
		{
			list<item>::iterator it2;
			for(it2=you.item_list.begin(); it2 != you.item_list.end(); it2++)
			{
				if((*it2).can_throw && you.equipment[ET_WEAPON] != &(*it2))
				{
					throw_weapon = &(*it2);
					break;
				}
			}
		}
		return true;
	}
	return false;
}
item* players::GetItem(char id_)
{
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if((*it).id == id_)
			return &(*it);
	}
	return NULL;
}
list<item>::iterator players::GetItemIterator(char id_)
{
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if((*it).id == id_)
			return it;
	}
	return item_list.end();
}
bool players::equip(char id_, equip_type type_, bool speak_)
{
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if((*it).id == id_)
			return equip(it,type_,speak_);
	}
	printlog("존재하지 않는 아이템",true,false,false,CL_normal);
	return 0;
}
void players::auto_equip_iden()
{
	for(equip_type i = ET_JEWELRY;i!=ET_JEWELRY_END;i=(equip_type)(i+1))
	{
		if(equipment[i] && !equipment[i]->identify)
		{
			equipment[i]->autoIdentify();
		}
	}
}
bool players::equip(list<item>::iterator &it, equip_type type_, bool speak_)
{
	for(equip_type i = ET_FIRST;i!=ET_LAST;i=(equip_type)(i+1))
	{
		if(equipment[i] == &(*it))
		{
			if(i == type_)
				printlog("이미 장착하고 있다.",true,false,false,CL_normal);
			else
				printlog("이 아이템은 이미 사용중이다.",true,false,false,CL_normal);
			return 0;
		}
	}

	if(type_ == ET_ARMOR && it->type >= ITM_ARMOR_BODY_ARMOUR_1 && it->type <= ITM_ARMOR_BODY_ARMOUR_3 )
	{
		int your_size_ = GetProperty(TPT_SIZE);
		if(your_size_>0)
		{
			printlog("당신은 이 방어구를 착용하기엔 몸이 너무 크다.",true,false,false,CL_normal);
			return 0;
		}
		if(your_size_<0)
		{
			printlog("당신은 이 방어구를 착용하기엔 몸이 너무 작다.",true,false,false,CL_normal);
			return 0;
		}
	}
	/*if(type_ == ET_HELMET &&GetProperty(TPT_HORN) )
	{
		printlog("당신의 뿔이 이 장비를 쓰는걸 방해한다.",true,false,false,CL_normal);
		return 0;
	}
	if(type_ == ET_BOOTS &&GetProperty(TPT_GHOST_FOOT) )
	{
		printlog("당신은 다리가 없다!",true,false,false,CL_normal);
		return 0;
	}*/
	


	WaitForSingleObject(mutx, INFINITE);
	if((*it).isRightType(type_))
	{
		if(!unequip(type_))
		{
			printlog("저주에 걸려 있어서 장비를 벗을 수 없다.",true,false,false,CL_normal);
			ReleaseMutex(mutx);
			return 0;
		}
		//자동식별 추가
		(*it).Identify();

		equip_stat_change(&(*it), type_, true);
		equipment[type_] = &(*it);
		ReSetASPanlty();
		if(type_ == ET_WEAPON)
		{
			if(alchemy_buff == ALCT_STONE_FIST)
			{
				alchemy_buff = ALCT_NONE;
				alchemy_time = 0;
			}
		}

		if(type_ != ET_WEAPON || ((*it).type >= ITM_WEAPON_FIRST && (*it).type < ITM_WEAPON_LAST)) //무기를 장착했을때
		{
			if(equipment[type_]->curse)
				printlog("헉! 이 아이템은 끔찍하게 차갑다.",true,false,false,CL_small_danger);
			equipment[type_]->identify_curse = true;
		}
		if(throw_weapon == &(*it)) //만약 던지는 무기로 설정된 아이템을 착용했을 경우
		{	
			throw_weapon = NULL;
			list<item>::iterator it2 = you.item_list.begin();
			for(;it2 != you.item_list.begin(); it2++)
			{
				if((*it2).can_throw && you.equipment[ET_WEAPON] != &(*it2))
				{
					throw_weapon = &(*it2);
					break;
				}
			}
		}
		if(speak_)
		{
			char temp[2];
			sprintf(temp,"%c",(*it).id);
			printlog(temp,false,false,false,(*it).item_color());
			printlog(" - ",false,false,false,(*it).item_color());
			printlog((*it).GetName(),false,false,false,(*it).item_color());
			printlog(" (장착)",true,false,false,(*it).item_color());

			
			if(type_ == ET_ARMOR)
				time_delay += 5*you.GetNormalDelay();
			else if(type_ >= ET_SHIELD && type_ < ET_LAST)
				time_delay += 3*you.GetNormalDelay();
			else
				time_delay += you.GetNormalDelay();


			if(type_ == ET_ARMOR)
			{
				int penalty_ = you.as_penalty>you.GetPenaltyMinus(3)?4: //끔찍
					you.as_penalty>you.GetPenaltyMinus(2)?3: //이동패널티
					you.as_penalty>you.GetPenaltyMinus(1)?2: //명중
					you.as_penalty?1:0;
				switch(penalty_/*you.GetArmourPanlty()*/)
				{
				case 0:
				case 1:
					break;
				case 2:
					printlog("불편한 방어구는 당신의 명중에 영향을 준다. ",true,false,false,CL_warning);
					break;
				case 3:
					printlog("불편한 방어구는 당신의 이동속도와 명중에 영향을 준다. ",true,false,false,CL_small_danger);
					break;
				case 4:
				default:
					printlog("방어구로 인해 극심한 패널티를 받고 있다. ",true,false,false,CL_danger);
					break;
				}
			}

		}
		ReleaseMutex(mutx);
		if(speak_)
			TurnEnd();
		return 1;
	}
	else
	{
		printlog("그렇게 장착할 수 없다.",true,false,false,CL_normal);
		ReleaseMutex(mutx);
		return 0;
	}
}


bool players::equiparmor(char id_, bool speak_)
{
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if((*it).id == id_)
		{
			if(!(*it).isarmor())
			{
				printlog("이 아이템은 방어구가 아니다.",true,false,false,CL_normal);
				return 0;
			}
			return equip(it,(*it).GetArmorType(),speak_);
		}
	}
	printlog("존재하지 않는 아이템",true,false,false,CL_normal);
	return 0;
}


bool players::equipjewerly(char id_)
{
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if((*it).id == id_)
		{
			if(!(*it).isjewerly())
			{
				printlog("이 아이템은 장신구가 아니다.",true,false,false,CL_normal);
				return 0;
			}
			if(&(*it) == equipment[ET_LEFT] || &(*it) == equipment[ET_RIGHT])
			{
				printlog("이미 장착하고 있는 장신구다.",true,false,false,CL_normal);
				return 0;
			}
			if(s_spellcard && (*it).isRightType(ET_NECK))
			{
				printlog("스펠카드 선언중엔 스펠카드 탈착이 불가능하다.",true,false,false,CL_normal);
				return 0;
			}

			equip_type type_ = ET_JEWELRY;
			if((*it).isring())
			{
				if(equipment[ET_LEFT] && equipment[ET_RIGHT])
				{
					char temp[2];
					changedisplay(DT_GAME);
					printlog("< 또는 ",false,false,false,CL_normal);
					sprintf(temp,"%c",equipment[ET_LEFT]->id);
					printlog(temp,false,false,false,CL_normal);
					printlog(" - ",false,false,false,CL_normal);
					printlog(equipment[ET_LEFT]->GetName(),false,false,false,equipment[ET_LEFT]->item_color());
					printlog("; > 또는 ",false,false,false,CL_normal);
					sprintf(temp,"%c",equipment[ET_RIGHT]->id);
					printlog(temp,false,false,false,CL_normal);
					printlog(" - ",false,false,false,CL_normal);
					printlog(equipment[ET_RIGHT]->GetName(),false,false,false,equipment[ET_RIGHT]->item_color());
					printlog(";",true,false,false,CL_normal);
					while(1)
					{
						int key_ = waitkeyinput(true);
						if(key_ == '<' || key_ == equipment[ET_LEFT]->id)
						{
							type_ = ET_LEFT;
							break;
						}
						else if(key_ == '>' || key_ == equipment[ET_RIGHT]->id)
						{
							type_ = ET_RIGHT;
							break;
						}	
						else if(key_ == VK_ESCAPE)
						{
							return 0;
						}								
					}
				}
				else if(equipment[ET_LEFT])
					type_ = ET_RIGHT;
				else
					type_ = ET_LEFT;
			}
			return equip(it,type_);
		}
	}
	printlog("존재하지 않는 아이템",true,false,false,CL_normal);
	return 0;
}




bool players::unequip(char id_)
{
	for(equip_type i = ET_FIRST;i!=ET_LAST;i=(equip_type)(i+1) )
	{
		if(equipment[i] && equipment[i]->id == id_)
		{
			return unequip(i);
		}
	}
	printlog("벗을 아이템이 없다.",true,false,false,CL_normal);
	return 0;
}


bool players::unequip(list<item>::iterator it, equip_type type_)
{
	return unequip((*it).id);
}

bool players::possibleunequip(list<item>::iterator it)
{
	for(equip_type i = ET_FIRST;i!=ET_LAST;i=(equip_type)(i+1))
	{
		if(equipment[i] == &(*it))
		{
			if(!unequip(i))
			{
				printlog("저주에 걸려 있어서 장비를 벗을 수 없다.",true,false,false,CL_normal);
				return 0;
			}
			break;
		}
	}	
	return 1;
}

int players::isequip(list<item>::iterator it)
{
	for(equip_type i = ET_FIRST;i!=ET_LAST;i=(equip_type)(i+1))
	{
		if(equipment[i] == &(*it))
		{
			if(i == ET_LEFT)
				return 2;
			else if(i == ET_RIGHT)
				return 3;
			else
				return 1;
		}
	}	
	return 0;
}
int players::isequip(item* item_)
{
	for(equip_type i = ET_FIRST;i!=ET_LAST;i=(equip_type)(i+1))
	{
		if(equipment[i] == item_)
		{
			if(i == ET_LEFT)
				return 2;
			else if(i == ET_RIGHT)
				return 3;
			else
				return 1;
		}
	}	
	return 0;
}
int players::haveGoal()
{
	int goal_ = 0;
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if(it->type == ITM_GOAL)
		{
			goal_+=it->num;
		}
	}
	return goal_;
}
int players::haveOrb()
{
	int goal_ = 0;
	list<item>::iterator it;
	for(it = item_list.begin(); it != item_list.end();it++)
	{
		if(it->type == ITM_ORB)
		{
			goal_+=it->num;
		}
	}
	return goal_;
	
}
bool players::unequip(equip_type type_)
{
	if(equipment[type_])
	{
		if(equipment[type_]->curse && (type_ != ET_WEAPON || (equipment[type_]->type >= ITM_WEAPON_FIRST && equipment[type_]->type < ITM_WEAPON_LAST)))
		{
			if(!equipment[type_]->identify_curse)
				equipment[type_]->identify_curse = true;
			return false;
		}
		WaitForSingleObject(mutx, INFINITE);
		equip_stat_change(equipment[type_], type_, false);
		if(type_ == ET_ARMOR)
			time_delay += 5*you.GetNormalDelay();
		else if(type_ >= ET_SHIELD && type_ < ET_LAST)
			time_delay += 3*you.GetNormalDelay();
		else
			time_delay += you.GetNormalDelay();
		printlog(equipment[type_]->GetName(),false,false,false,equipment[type_]->item_color());
		printarray(true,false,false,CL_normal,2,equipment[type_]->GetNameInfor().name_to(true),"벗었다.");
		equipment[type_] = NULL;
		ReSetASPanlty();
		ReleaseMutex(mutx);
		TurnEnd();
	}
	return true;
}

bool players::unequiparmor(char id_)
{
	for(equip_type i = ET_ARMOR;i!=ET_ARMOR_END;i=(equip_type)(i+1))
	{
		if(equipment[i] && equipment[i]->id == id_)
		{
			if(!unequip(i))
			{
				printlog("저주에 걸려 있어서 장비를 벗을 수 없다.",true,false,false,CL_normal);
				return 0;
			}
			return 1;
		}
	}
	printlog("그것을 입고 있지 않다!",true,false,false,CL_normal);
	return 0;
}

bool players::unequipjewerly(char id_)
{
	for(equip_type i = ET_JEWELRY;i!=ET_JEWELRY_END;i=(equip_type)(i+1))
	{
		if(equipment[i] && equipment[i]->id == id_)
		{
			if(s_spellcard && equipment[i]->isRightType(ET_NECK))
			{
				printlog("스펠카드 선언중엔 스펠카드 탈착이 불가능하다.",true,false,false,CL_normal);
				return 0;
			}

			if(!unequip(i))
			{
				printlog("저주에 걸려 있어서 장비를 벗을 수 없다.",true,false,false,CL_normal);
				return 0;
			}
			return 1;
		}
	}
	printlog("그것을 입고 있지 않다!",true,false,false,CL_normal);
	return 0;
}




void players::equip_stat_change(item *it, equip_type where_, bool equip_bool)
{
	int plus_=(equip_bool?1:-1);
		
	if((*it).type>=ITM_WEAPON_FIRST && (*it).type<ITM_WEAPON_LAST && (*it).value5)
	{
		if(equip_bool)
		{
			if((*it).value6 == 0)
				(*it).value6 = -1;
			switch((*it).value5)
			{
			case WB_FIRE:			
				printlog("무기가 불로 타오르기 시작했다.",true,false,false,CL_white_blue);
				break;
			case WB_COLD:			
				printlog("무기가 차가운 냉기를 내뿜기 시작했다.",true,false,false,CL_white_blue);
				break;		
			case WB_POISON:			
				printlog("무기에서 독이 떨어지기 시작했다.",true,false,false,CL_white_blue);	
				break;
			case WB_CURSE:		
				printlog("무기는 저주의 힘으로 가득 차있다.",true,false,false,CL_hina);	
				break;
			case WB_WEATHER	:
				printlog("무기에서 비상의 기운이 뿜어져나온다.",true,false,false,CL_tensi);	
				break;
			case WB_AUTUMN:
				printlog("무기에서 쓸쓸하고도 종말적인 기운이 느껴진다.",true,false,false,CL_autumn);	
				break;
			case WB_MANA_REGEN:
				SetManaDelay(1);
				printlog("영력의 흐름이 느껴진다. 익숙해지려면 시간이 걸릴 것 같다.",true,false,false,CL_white_blue);	
				break;
			case WB_FAST_CAST:
				printlog("머리회전이 빨라진 느낌이 든다.",true,false,false,CL_white_blue);	
				break;
			case WB_PROTECT:
				AcUpDown(0,5);
				printlog("보호받는 기분이 든다.",true,false,false,CL_white_blue);	
				break;
			default:			
				printlog("이 무기는 버그를 내뿜고있다.",true,false,false,CL_danger);	
				break;		
			}
		}
		else
		{
			if((*it).value6 > 1)
			{
				(*it).value6 = 0;
				(*it).value5 = 0;
			}
			else
			{
				switch((*it).value5)
				{
				case WB_FIRE:			
					printlog("무기가 타오르는 것을 멈췄다.",true,false,false,CL_normal);
					break;
				case WB_COLD:			
					printlog("무기에서 나오던 냉기가 그쳤다.",true,false,false,CL_normal);
					break;		
				case WB_POISON:			
					printlog("더이상 무기에서 독이 떨어지지 않는다.",true,false,false,CL_normal);	
					break;
				case WB_CURSE:		
					printlog("무기에서 저주의 힘이 약해졌다.",true,false,false,CL_normal);	
					break;
				case WB_WEATHER	:
					printlog("무기에서 비상의 기운은 더이상 느껴지지않는다.",true,false,false,CL_normal);	
					break;
				case WB_AUTUMN:
					printlog("무기는 더이상 쓸쓸해보이지 않는다.",true,false,false,CL_normal);	
					break;
				case WB_MANA_REGEN:
					printlog("영력의 흐름이 사라졌다.",true,false,false,CL_white_blue);	
					break;
				case WB_FAST_CAST:
					printlog("머리회전이 다시 둔해졌다.",true,false,false,CL_white_blue);	
					break;
				case WB_PROTECT:
					AcUpDown(0,-5);
					printlog("보호가 사라졌다.",true,false,false,CL_white_blue);	
					break;
				default:			
					printlog("방금 무기는 버그에 걸려있다.",true,false,false,CL_danger);	
					break;		
				}
			}
		}

	}

	if((*it).type>=ITM_ARMOR_FIRST && (*it).type<ITM_ARMOR_LAST && where_ >= ET_ARMOR && where_ < ET_ARMOR_END)
	{
		if((*it).type == ITM_ARMOR_SHIELD)
		{
			ShUpDown((*it).value1 * plus_, (*it).value4 * plus_);
			//EvUpDown((*it).value2 * plus_);
		}
		else
		{
			AcUpDown((*it).value1 * plus_, (*it).value4 * plus_);
			//EvUpDown((*it).value2 * 1.5f * plus_);
			if(where_ == ET_ARMOR)
				equipArmour((armour_kind)(*it).value5, plus_);


			if(where_ == ET_ARMOR && !strncmp((*it).name.name.c_str(),"단풍",4))
			{
				ResistUpDown(-1*plus_,RST_FIRE);
			}
		}


		it->identify = true;
	}
	else if((*it).type == ITM_RING && (where_ == ET_LEFT || where_ == ET_RIGHT))
	{
		bool iden_ = equipring((ring_type)(*it).value1, (*it).value2*plus_);
		if(!(*it).isArtifact())
		{
			if(iden_ && !(*it).identify)
				(*it).identify = true;
			(*it).autoIdentify();
			if(!(*it).identify)
				unidenequipring((ring_type)(*it).value1, (*it).value2*plus_);
		}
		else
		{
			(*it).identify = true;
		}
	}
	//else if((*it).type == ITM_SPELLCARD && where_ == ET_NECK)
	//{	
	//	if(!(*it).identify)
	//		(*it).identify = true;
	//	(*it).autoIdentify();
	//	//bool iden_ = equipamulet((amulet_type)(*it).value1, (*it).value2*plus_);
	//	//if(iden_ && !(*it).identify)
	//	//	(*it).identify = true;
	//	//(*it).autoIdentify();
	//	//if(!(*it).identify)
	//	//	unidenequipamulet((amulet_type)(*it).value1, (*it).value2*plus_);
	//}
	
	if((*it).isArtifact())
	{
		for(auto it2 = (*it).atifact_vector.begin(); it2 != (*it).atifact_vector.end(); it2++)
		{
			effectartifact((ring_type)it2->kind, it2->value * plus_);
		}
		(*it).identify = true;
	}

}
float players::GetFireResist()
{
	if(fire_resist <= -2)
		return 2;
	else if(fire_resist == -1)
		return 1.5f;
	else if(fire_resist == 1)
		return 0.5f;
	else if(fire_resist == 2)
		return 0.2f;
	else if(fire_resist >= 3)
		return 0.1f;
	else
		return 1;
}
float players::GetColdResist()
{
	if(ice_resist <= -2)
		return 2;
	else if(ice_resist == -1)
		return 1.5f;
	else if(ice_resist == 1)
		return 0.5f;
	else if(ice_resist == 2)
		return 0.2f;
	else if(ice_resist >= 3)
		return 0.1f;
	else
		return 1;
}
float players::GetElecResist()
{
	if(elec_resist>0)
		return 1.0f/3.0f;
	else
		return 1.0f;
}

bool players::isView(const monster* monster_info)
{
	
	if(isArena())
		return false;
	if((you.s_invisible || you.togle_invisible) && !(monster_info->flag & M_FLAG_CAN_SEE_INVI)) //투명?
		return false;
	return true;
}


skill_type itemtoskill(item_type type_)
{
	switch(type_)
	{
	case ITM_WEAPON_SHORTBLADE:
		return SKT_SHORTBLADE;
	case ITM_WEAPON_LONGBLADE:
		return SKT_LONGBLADE;
	case ITM_WEAPON_MACE:
		return SKT_MACE;
	case ITM_WEAPON_AXE:
		return SKT_AXE;
	case ITM_WEAPON_SPEAR:
		return SKT_SPEAR;
	//case ITM_WEAPON_BOW:
	//	return SKT_BOW;
	default:
		return SKT_ERROR;
	}
}