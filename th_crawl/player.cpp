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
#include "map.h"
#include "lilly.h"
#include "soundmanager.h"


players you;
extern HANDLE mutx;
extern map_infor map_list;
skill_type itemtoskill(item_type type_);
int shieldPanaltyOfWeapon(item_type type, int weapon_kind);
extern bool widesearch; //X커맨드용

void name_infor::SaveDatas(FILE *fp)
{
	char temp[100];
	sprintf_s(temp,100,"%s",name.c_str());
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
hp(10), max_hp(10), hp_recov(0), mp(0), max_mp(0), mp_recov(0), pure_mp(false), power(300),	power_decre(0), level(1), exper(0), exper_recovery(10), exper_aptit(10), skill_exper(0), system_exp(1,1),
ac(0), ev(10), sh(0),real_ac(0),bonus_ac(0), real_ev(10), bonus_ev(0),real_sh(0), bonus_sh(0), s_str(10), s_dex(10), s_int(10), m_str(10), m_dex(10), m_int(10), acc_plus(0), dam_plus(0),
as_penalty(0), magic_resist(0), tension_gauge(0), tension_turn(false), already_swap(false), ziggurat_level(0),
reimu_level(0), reimu_turn(0) , search(false), search_pos(0,0), item_weight(0), max_item_weight(350),prev_action(ACTT_NONE),
prev_action_key(), equipment(), time_delay(0), speed(10),
turn(0), real_turn(0), prev_real_turn(0), player_move(false), explore_map(0)/*, hunger(7000), hunger_per_turn(0)*/, 
final_item(0), final_num(0), auto_pickup(1), inter(IT_NONE), 
s_poison(0),s_tele(0), s_might(0), s_clever(0), s_agility(0), s_haste(0), s_pure_haste(0), s_confuse(0), s_slow(0),s_frozen(0),
s_elec(0), s_paralyse(0), s_levitation(0), s_glow(0), s_graze(0), s_silence(0), s_silence_range(0), s_sick(0), s_veiling(0), s_value_veiling(0), s_invisible(0), s_swift(0), 
 s_mana_regen(0), s_superman(0), s_spellcard(0), s_slaying(0), s_autumn(0), s_wind(0), s_knife_collect(0), s_drunken(0), s_catch(0), s_ghost(0),
 s_dimension(0), s_timestep(0),  s_mirror(0), s_lunatic(0), s_paradox(0), s_trans_panalty(0), s_the_world(0), s_mana_delay(0),
 s_stat_boost(0), s_stat_boost_value(0), s_eirin_poison(0), s_eirin_poison_time(0), s_exhausted(0), s_stasis(0),
force_strong(false), force_turn(0), s_unluck(0), s_super_graze(0), s_none_move(0), s_night_sight(0), s_night_sight_turn(0), s_sleep(0),
s_pure(0),s_pure_turn(0), drowned(false), s_weather(0), s_weather_turn(0), s_evoke_ghost(0), alchemy_buff(ALCT_NONE), alchemy_time(0),
teleport_curse(false), magician_bonus(0), poison_resist(0),fire_resist(0),ice_resist(0),elec_resist(0),confuse_resist(0), invisible_view(0), power_keep(0), 
togle_invisible(false), battle_count(0), youMaxiExp(false),
uniden_poison_resist(0), uniden_fire_resist(0), uniden_ice_resist(0), uniden_elec_resist(0),uniden_confuse_resist(0), uniden_invisible_view(0), uniden_power_keep(0)
,total_skill_exp(0), pure_skill(-1), remainSpellPoiont(1), currentSpellNum(0),currentSkillNum(0),god(GT_NONE), gift_count(0), piety(0), god_turn(0), suwako_meet(0),
sight_reset(false), target(NULL), throw_weapon(NULL),dead_order(NULL), dead_reason(DR_NONE)
{
	for(int i=0;i<2;i++)
		prev_hp[i] = hp;
	for(int i=0;i<2;i++)
		prev_mp[i] = mp;
	for (int i = 0; i<SKT_MAX; i++)
		bonus_skill[i] = 0;
	for(int i=0;i<52;i++)
		MemorizeSpell[i] = 0;
	for(int i=0;i<52;i++)
		MemorizeSkill[i] = 0;
	for(int i=0;i<52;i++)
		MemorizeSkill_num[i] = 0;
	for (int i = 0; i<4; i++)
		penalty_turn[i] = 0;
	//for(int i=0;i<GT_LAST;i++)
	//	punish[i]=0;
	for(int i=0;i<GT_LAST;i++)
		for(int j=0;j<5;j++)
			god_value[i][j]=0;
	for(int i=0;i<4;i++)
		half_youkai[i]=0;
	for(int i=0;i<RUNE_MAX;i++)
		rune[i]=0;
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
	SaveData<bool>(fp, pure_mp);
	SaveData<int>(fp, power);
	SaveData<int>(fp, power_decre);
	SaveData<int>(fp, level);
	SaveData<int>(fp, exper);
	SaveData<int>(fp, exper_recovery);
	SaveData<int>(fp, exper_aptit);
	SaveData<int>(fp, skill_exper);
	SaveData<current_max>(fp, system_exp);
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
	SaveData<bool>(fp, already_swap);
	SaveData<int>(fp, ziggurat_level);
	SaveData<int>(fp, reimu_level);
	SaveData<int>(fp, reimu_turn);

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
	SaveData<prev_action_struct>(fp, prev_action_key);

	
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
	SaveData<int>(fp, *penalty_turn, 4); //너무 오래있을때 패널티
	SaveData<char>(fp, final_item);
	SaveData<int>(fp, final_num);

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
	SaveData<int>(fp, s_pure_haste);
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
	SaveData<int>(fp, s_exhausted);
	SaveData<int>(fp, s_stasis);
	SaveData<bool>(fp, force_strong);
	SaveData<int>(fp, force_turn);
	SaveData<int>(fp, s_unluck);
	SaveData<int>(fp, s_super_graze);
	SaveData<int>(fp, s_none_move);
	SaveData<int>(fp, s_night_sight);
	SaveData<int>(fp, s_night_sight_turn);
	SaveData<int>(fp, s_sleep);
	SaveData<int>(fp, s_pure);
	SaveData<int>(fp, s_pure_turn);
	SaveData<bool>(fp, drowned);
	SaveData<int>(fp, s_weather);
	SaveData<int>(fp, s_weather_turn);
	SaveData<int>(fp, s_evoke_ghost);
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
	SaveData<bool>(fp, youMaxiExp);
	SaveData<int>(fp, uniden_poison_resist);
	SaveData<int>(fp, uniden_fire_resist);
	SaveData<int>(fp, uniden_ice_resist);
	SaveData<int>(fp, uniden_elec_resist);
	SaveData<int>(fp, uniden_confuse_resist);
	SaveData<int>(fp, uniden_invisible_view);
	SaveData<int>(fp, uniden_power_keep);
	SaveData<int>(fp, total_skill_exp);
	SaveData<skill_exp_infor>(fp, *skill, SKT_MAX);
	SaveData<int>(fp, *bonus_skill, SKT_MAX);
	SaveData<int>(fp, pure_skill);
	SaveData<int>(fp, *MemorizeSpell,52);
	SaveData<int>(fp, remainSpellPoiont);
	SaveData<int>(fp, currentSpellNum);
	SaveData<int>(fp, *MemorizeSkill,52);
	SaveData<int>(fp, *MemorizeSkill_num,52);
	SaveData<int>(fp, currentSkillNum);
	SaveData<god_type>(fp, god);
	SaveData<int>(fp, gift_count);
	SaveData<int>(fp, piety);
	SaveData<punish_struct>(fp, *punish, GT_LAST);
	SaveData<int>(fp, god_turn);
	for(int i=0;i<GT_LAST;i++)
		SaveData<int>(fp, *(god_value[i]), 5);
	SaveData<lilly_ally>(fp, *lilly_allys, 5);	
	SaveData<int>(fp, suwako_meet);
	SaveData<int>(fp, *half_youkai, 4);	
	SaveData<int>(fp, *rune, RUNE_MAX);		
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
	prev_hp[0] = hp;
	prev_hp[1] = hp;
	LoadData<int>(fp, max_hp);
	LoadData<int>(fp, hp_recov);
	LoadData<int>(fp, mp);
	prev_mp[0] = mp;
	prev_mp[1] = mp;
	LoadData<int>(fp, max_mp); 
	LoadData<int>(fp, mp_recov);
	LoadData<bool>(fp, pure_mp);
	LoadData<int>(fp, power);
	LoadData<int>(fp, power_decre);
	LoadData<int>(fp, level);
	LoadData<int>(fp, exper);
	LoadData<int>(fp, exper_recovery);	
	LoadData<int>(fp, exper_aptit);
	LoadData<int>(fp, skill_exper);
	LoadData<current_max>(fp, system_exp);
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
	LoadData<bool>(fp, already_swap);
	LoadData<int>(fp, ziggurat_level);
	LoadData<int>(fp, reimu_level);
	LoadData<int>(fp, reimu_turn);
	

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
	LoadData<prev_action_struct>(fp, prev_action_key);
	for(int i=0;i<ET_LAST;i++)
	{
		char temp_id_=0;
		item *temp_ = NULL;
		LoadData<char>(fp, temp_id_);
		list<item>::iterator itw;
		for(itw = item_list.begin(); temp_id_ && itw != item_list.end();itw++)
		{
			if((*itw).id == temp_id_)
			{
				temp_ = &(*itw);
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
	LoadData<int>(fp, *penalty_turn);
	LoadData<char>(fp, final_item);
	LoadData<int>(fp, final_num);
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
	LoadData<int>(fp, s_pure_haste);
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
	LoadData<int>(fp, s_exhausted);
	LoadData<int>(fp, s_stasis);
	LoadData<bool>(fp, force_strong);
	LoadData<int>(fp, force_turn);
	LoadData<int>(fp, s_unluck); 
	LoadData<int>(fp, s_super_graze);
	LoadData<int>(fp, s_none_move);
	LoadData<int>(fp, s_night_sight); 
	LoadData<int>(fp, s_night_sight_turn);
	LoadData<int>(fp, s_sleep);
	LoadData<int>(fp, s_pure);
	LoadData<int>(fp, s_pure_turn);
	LoadData<bool>(fp, drowned);
	LoadData<int>(fp, s_weather);
	LoadData<int>(fp, s_weather_turn);
	LoadData<int>(fp, s_evoke_ghost);
	

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
	LoadData<bool>(fp, youMaxiExp);
	LoadData<int>(fp, uniden_poison_resist);
	LoadData<int>(fp, uniden_fire_resist);
	LoadData<int>(fp, uniden_ice_resist);
	LoadData<int>(fp, uniden_elec_resist);
	LoadData<int>(fp, uniden_confuse_resist);
	LoadData<int>(fp, uniden_invisible_view);
	LoadData<int>(fp, uniden_power_keep);
	LoadData<int>(fp, total_skill_exp);
	LoadData<skill_exp_infor>(fp, *skill);
	LoadData<int>(fp, *bonus_skill);
	LoadData<int>(fp, pure_skill);
	LoadData<int>(fp, *MemorizeSpell);
	LoadData<int>(fp, remainSpellPoiont);
	LoadData<int>(fp, currentSpellNum);
	LoadData<int>(fp, *MemorizeSkill);
	LoadData<int>(fp, *MemorizeSkill_num);
	LoadData<int>(fp, currentSkillNum);
	LoadData<god_type>(fp, god);
	LoadData<int>(fp, gift_count);
	LoadData<int>(fp, piety);
	LoadData<punish_struct>(fp, *punish);
	LoadData<int>(fp, god_turn);
	for(int i=0;i<GT_LAST;i++)
		LoadData<int>(fp, *(god_value[i]));
	LoadData<lilly_ally>(fp, *lilly_allys);	
	LoadData<int>(fp, suwako_meet);
	LoadData<int>(fp, *half_youkai);
	LoadData<int>(fp, *rune);		
	{
		char temp_id_=0;
		item *temp_ = NULL;
		LoadData<char>(fp, temp_id_);
		list<item>::iterator itw;
		for(itw = item_list.begin(); temp_id_ && itw != item_list.end();itw++)
		{
			if((*itw).id == temp_id_)
			{
				temp_ = &(*itw);
				break;
			}
		}
		throw_weapon = temp_;
	}
}

bool players::Draw(LPD3DXSPRITE pSprite, float x_, float y_)
{
	if (s_glow || you.GetBuffOk(BUFFSTAT_HALO)) {
		img_effect_halo.draw(pSprite, x_, y_, 127);
	}
	if (s_veiling) {
		img_effect_veiling.draw(pSprite, x_, y_, 255);
	}
	if (!GetCharNameString()->empty())
	{
		if (you.image) {
			return you.image->draw(pSprite, x_, y_, 255);
		}
	}
	else if (you.tribe == TRI_FAIRY)
	{
		item* t;
		t = you.equipment[ET_CLOAK];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
		if (you.image) {
			you.image->draw(pSprite, x_, y_, 255);
		}
		t = you.equipment[ET_HELMET];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
		t = you.equipment[ET_WEAPON];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
		t = you.equipment[ET_SHIELD];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
	}
	else
	{
		item* t;
		t = you.equipment[ET_CLOAK];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
		if (you.image) {
			you.image->draw(pSprite, x_, y_, 255);
		}
		t = you.equipment[ET_GLOVE];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
		t = you.equipment[ET_BOOTS];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
		t = you.equipment[ET_ARMOR];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
		t = you.equipment[ET_HELMET];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
		t = you.equipment[ET_WEAPON];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
		t = you.equipment[ET_SHIELD];
		if (t && t->equip_image)
			t->equip_image->draw(pSprite, x_, y_, 255);
	}
	return false;
}
bool players::isLive()
{
	return true;
}
bool players::isSwim()
{
	if(god == GT_SUWAKO && !GetPunish(GT_SUWAKO) && pietyLevel(piety)>=2 &&
		god_value[GT_SUWAKO][1] == SWAKO_2_SWIM)
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
void players::SetPrevAction(int key, char item, int num)
{
	prev_action_key.key = key;
	prev_action_key.item = item;
	prev_action_key.num = num;
}
void players::maybeAction()
{
	you.prev_hp[0] = you.prev_hp[1];
	you.prev_mp[0] = you.prev_mp[1];
}
coord_def players::GetDisplayPos()
{
	if(!s_dimension)
	{
		return widesearch?search_pos:position;
	}
	else
	{
		return coord_def(god_value[GT_YUKARI][0],god_value[GT_YUKARI][1]);
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
	
	if(you.s_dimension && (you.god == GT_YUKARI))
	{
		if(abs(move_x_ - you.god_value[GT_YUKARI][0])>8)
		{
			    move_x_ +=move_x_ - you.god_value[GT_YUKARI][0]>0?-17:17;
		}
		if(abs(move_y_ - you.god_value[GT_YUKARI][1])>8)
		{
			    move_y_ +=move_y_ - you.god_value[GT_YUKARI][1]>0?-17:17;
		}
	}

	if(env[current_level].isMove(position.x+x_mov,position.y+y_mov,true))
	{

		monster* mon_ = (monster*)env[current_level].isMonsterPos(move_x_,move_y_,this);



		if(mon_)
		{
			if(mon_->isUserAlly() && !(mon_->flag & M_FLAG_NONE_MOVE))
			{
				if(env[current_level].isMove(position.x, position.y, mon_->isFly(), mon_->isSwim(), mon_->flag & M_FLAG_CANT_GROUND) && env[current_level].isMove(move_x_,move_y_,isFly(),isSwim() || drowned))
				{
					PositionSwap(mon_);								
					printlog("위치를 서로 바꿨다. ",false,false,false,CL_bad);
					time_delay += GetWalkDelay();//이동속도만큼 이동
					prev_action = ACTT_WALK;
					return 2;
				}
				else
					return 0;
			}
			else if(mon_->isUserAlly() && (mon_->flag & M_FLAG_NONE_MOVE))
			{
				printlog("이동할 수 없다.",true,false,false,CL_normal);
				you.SetInter(IT_MAP_FIND);
				return 0;
			}

			if (s_evoke_ghost) {
				printlog("유령 상태에선 적을 공격할 수 없다. ", true, false, false, CL_normal);
				return 0;
			}



			attack_type brand_ = ATT_NORMAL;
			if(equipment[ET_WEAPON])
				brand_ = (attack_type)GetAttType((weapon_brand)equipment[ET_WEAPON]->value5);
			attack_infor temp_att(GetAttack(false),GetAttack(true),GetHit(),this,GetParentType(),brand_,alchemy_buff == ALCT_STONE_FIST?name_infor("돌주먹",true):name_infor("공격",true));
			if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->type >= ITM_WEAPON_FIRST && equipment[ET_WEAPON]->type <= ITM_WEAPON_CLOSE)
			{
				doingActionDump(DACT_MELEE, equipment[ET_WEAPON]->name.name);
				//doingActionDump(DACT_MELEE, skill_string(itemtoskill(equipment[ET_WEAPON]->type)));
				//나중에 무기 이름으로 바꾸기
			}
			else if(!equipment[ET_WEAPON])
			{
				doingActionDump(DACT_MELEE, "맨손");
				//doingActionDump(DACT_MELEE, skill_string(SKT_UNWEAPON));
			}
			else
			{
				doingActionDump(DACT_MELEE, "엉터리");
			}


			if(mon_->damage(temp_att))
			{
				if(mon_->isLive()&& you.god == GT_YUUGI && !you.GetPunish(GT_YUUGI) && pietyLevel(you.piety)>=2 && randA(10) == 0)
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
				int attack_ = 10;
				int hit_ = 12+level/3;
				if((equipment[ET_WEAPON] && randA(3)<1) || (!equipment[ET_WEAPON] && randA(2)<1))
				{//무기가 있으면 25%로 무기가 없으면 33%의 확률로 박치기가 나간다.
					attack_infor temp_att_(randA_1(attack_),attack_,hit_,this,GetParentType(),ATT_NORMAL,name_infor("박치기",false));
					mon_->damage(temp_att_, false);
				}
			}
			if(mon_->isLive() && you.GetProperty(TPT_JAW))
			{
				int attack_ = 10;
				int hit_ = 12+level/3;
				if(randA(3)<1)
				{
					attack_infor temp_att_(randA_1(attack_),attack_,hit_,this,GetParentType(),ATT_NORMAL,name_infor("깨물기",false));
					mon_->damage(temp_att_, false);
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



		if(s_none_move)
		{//온바시라 방해!			
			printlog("움직일수 없다! 무엇인가 당신을 고정시키고있다!",true,false,false,CL_danger);
			return 0;
		}

		if (env[current_level].isForbidZone(move_x_, move_y_) && !env[current_level].isForbidZone(you.position.x, you.position.y))
		{
			printlog("정말 들어갈거야?(y/n) ", false, false, false, CL_danger);
			bool loop_ = true;
			you.SetInter(IT_MAP_DANGER);
			while (loop_)
			{
				switch (waitkeyinput())
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
					printlog("잘 생각했다.", true, false, false, CL_normal);
					return 0;
				default:
					break;
				}
			}
		}
		else if(env[current_level].isSmokePos(move_x_,move_y_))
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
		else if(floor_effect* temp_floor = env[current_level].isFloorEffectPos(move_x_,move_y_))
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
		if (env[current_level].isDoor(move_x_, move_y_))
		{
			if (you.GetPunish(GT_OKINA) && GetHazard()>=100 && randA(1))
			{
				env[current_level].changeTile(coord_def(move_x_, move_y_), DG_FLOOR);
				//적이 서있으면 강제로 비키도록 한다.

				if (monster *mon__ = BaseSummon(MON_CLOSE_DOOR, 30 + randA_1(30), true, false, 0, NULL, coord_def(move_x_, move_y_), SKD_OTHER, -1))
				{
					mon__->LevelUpdown(you.level, 6);
					printlog("오키나가 문을 잠가버렸다!", true, false, false, CL_small_danger);
					return true;
				}

				time_delay += GetWalkDelay();//이동속도만큼 이동
				return 1;
			}
		}


		

		if(env[current_level].isMove(move_x_,move_y_,isFly(),isSwim()) ||
			(drowned && (env[current_level].dgtile[move_x_][move_y_].tile == DG_SEA ||
				env[current_level].dgtile[move_x_][move_y_].tile == DG_LAVA)
			))
		{
			SetXY(coord_def(move_x_,move_y_));
			time_delay += GetWalkDelay();//이동속도만큼 이동
			prev_action = ACTT_WALK;
			return 2;
		}
	}
	if(env[current_level].isDoor(move_x_,move_y_))
	{
		coord_def temp(move_x_, move_y_);
		if (you.god == GT_OKINA && !you.GetPunish(GT_OKINA)) {
			if (OpenDoor(temp, true) < 0)
				return 0;
			if (s_slaying<0)
			{//온바시라 방해!			
				printlog("움직일수 없다! 온바시라가 당신을 고정시키고있다!", true, false, false, CL_danger);
				return 0;
			}
			if (env[current_level].isMove(move_x_, move_y_, isFly(), isSwim() || drowned))
			{
				SetXY(coord_def(move_x_, move_y_));
				time_delay += GetWalkDelay();//이동속도만큼 이동
				prev_action = ACTT_WALK;
				return 2;
			}
		}
		else {
			return OpenDoor(temp, false) > 0;
		}
	}
	else {
		if (s_confuse || (s_drunken && drunken_ == 0))
		{
			printlog("아얏!", true, false, false, CL_normal);
			time_delay += GetWalkDelay();
			return 1;
		}
	}
	return 0;
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
					it->FoundTarget(unit_,it->FoundTime());
					it->state.SetState(MS_ATACK);
				}

			}
	
		}

	}

}

int players::OpenDoor(const coord_def &c, bool no_turn)
{
	if(env[current_level].isDoor(c.x,c.y))
	{
		if (env[current_level].isForbidZone(c.x, c.y) && !env[current_level].isForbidZone(you.position.x, you.position.y))
		{
			printlog("정말 열거야?(y/n) ", false, false, false, CL_danger);
			bool loop_ = true;
			while (loop_)
			{
				switch (waitkeyinput())
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
					printlog("잘 생각했다.", true, false, false, CL_normal);
					return -1;
				default:
					break;
				}
			}
		}

		if(env[current_level].OpenDoor(c.x,c.y))
		{
			env[current_level].CheckForbid(c);
			if (no_turn == false) {
				printlog("문을 열었다. ", false, false, false, CL_normal);
				time_delay += GetWalkDelay();
			}
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
	int fight_= GetSkillLevel(SKT_FIGHT, true);
	int level_=level;
	int aptit_=10+GetProperty(TPT_HP);
	int next_hp_ = floor((8 + floor((1+3*fight_)/2.0f)+floor(9*level_/2.0f)+floor(fight_*level_/14.0f))*(aptit_/10.0f));
	hp = hp*next_hp_/max_hp;
	max_hp = next_hp_;
}
int players::GetHp()
{ 
	if(pure_mp)
		return hp+mp;
	else
		return hp;
};
int players::GetMaxHp() 
{
	if (pure_mp)
		return max_hp + max_mp;
	else
		return max_hp; 
};
int players::GetDangerHp() 
{
	return GetMaxHp() * 3 / 10;
}
int players::GetMp() 
{
	if (pure_mp)
		return hp + mp;
	else
		return mp; 
};
int players::GetMaxMp() 
{
	if (pure_mp)
		return max_hp + max_mp;
	else
		return max_mp; 
};
int players::GetDisplayEv()
{
	return (you.s_sleep<0 || you.s_paralyse) ? 0 : ev;
}
int players::GetDisplayAc()
{
	return ac;
}
int players::GetDisplaySh()
{
	return (you.s_sleep<0 || you.s_paralyse) ? 0 : sh;
}
int players::GetThrowDelay(item_type type_, bool random_)
{
	float real_delay_ = 14; //기본 딜레이 14
	int skill_ = GetSkillLevel(SKT_TANMAC, true);

	real_delay_ = real_delay_
		-  (min(8,skill_)/ 2.0f )
		- ((skill_>8) ? (skill_ -8)/4.0f:0);
	//최소 딜레이 6
	//투척 8이 되어야 딜레이가 10
	//그 이후 딜레이는 투척레벨 4마다 1씩 줄어듬
	//최소 딜레이 6까지 가려면 투척레벨 22는 필요
	int delay_ = real_delay_;
	if(random_)
		delay_ += rand_float(0.99f, 0.0f);
	return delay_;
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
	int speed_ = s_superman?3:(speed-(s_swift>0?2:(s_swift<0?-6:0)));
	if(GetProperty(TPT_SPEED)==1)
		speed_ = speed_*8/10;
	else if(GetProperty(TPT_SPEED)==-1)
		speed_ = speed_*12/10;
	if(speed_<3)
		speed_ = 3;
	if(as_penalty>GetPenaltyMinus(2))
		speed_ += 1+as_penalty/2;
	if(alchemy_buff == ALCT_STONE_FORM)
		speed_ *= 1.3f;
	if(s_frozen)
		speed_+=(s_frozen+1)*speed_/20;
	if (drowned)
		speed_ += 10;
	return speed_;
}
int players::GetSpellPower(int s1_, int s2_, int s3_)
{
	int power_ = 0, num = 0;
	if(s1_ != -1)
	{
		power_ += 2* GetSkillLevel(s1_, true);
		num++;
	}	
	if(s2_ != -1)
	{
		power_ += 2* GetSkillLevel(s2_, true);
		num++;
	}
	if(s3_ != -1)
	{
		power_ += 2* GetSkillLevel(s3_, true);
		num++;
	}
	if(num)
		power_/=num;
	power_+= GetSkillLevel(SKT_SPELLCASTING, true)/2;

	if(s_clever)
		power_+=4;

	if(you.god == GT_MIMA && !you.GetPunish(GT_MIMA) && pietyLevel(you.piety)>=2 &&
		(s1_ == SKT_CONJURE || s2_ == SKT_CONJURE || s3_ == SKT_CONJURE))
		power_+=4;

	
	if(you.force_turn)
	{
		if(you.force_strong)
			power_ *= 2;
		else
			power_ /= 2;
	}
	if(you.GetPunish(GT_MIMA))
	{
		power_/=2;
	}



	power_*=s_int/10.0f;

	
	if(GetProperty(TPT_SPELL_POWER)>0)
	{
		power_*=1.3f;
	}
	if (you.GetBuffOk(BUFFSTAT_SPL_POW))
	{
		power_ *= 1.5f;
	}

	power_*=1.5f; //마법인헨서 기본으로 딸려있도록


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
		success_ += GetSkillLevel(s1_, true);
		num++;
	}	
	if(s2_ != -1)
	{
		success_ += GetSkillLevel(s2_, true);
		num++;
	}
	if(s3_ != -1)
	{
		success_ += GetSkillLevel(s3_, true);
		num++;
	}
	if(num)
		success_/=num;
	if(s_clever)
		success_+=2;
	if(magician_bonus)
		success_+=1+1*magician_bonus;
	if(s_drunken)
		success_-=2;
	if(you.god == GT_BYAKUREN && !you.GetPunish(GT_BYAKUREN) && pietyLevel(you.piety)>=4 && SpellFlagCheck((spell_list)spell_ ,S_FLAG_BUF))
		success_ += 2;
	if(you.god == GT_MIMA && !you.GetPunish(GT_MIMA) && pietyLevel(you.piety)>=2 &&
		(s1_ == SKT_CONJURE || s2_ == SKT_CONJURE || s3_ == SKT_CONJURE))
		success_ += 2;


	if(you.s_trans_panalty && (s1_ == SKT_TRANS || s2_ == SKT_TRANS || s3_ == SKT_TRANS))
	{
		success_ -= you.s_trans_panalty;
	}


	success_+=s_int/6.0f+ GetSkillLevel(SKT_SPELLCASTING, true)/4;

	//if(equipment[ET_ARMOR])
	//{
	//	differ_ -= min(0,equipment[ET_ARMOR]->value2+(!GetArmourPanlty()?1:0));
	//	differ_ += 2*max(0,GetArmourPanlty()-1);
	//}
	if (you.as_penalty > 0)
	{
		if (!(you.god == GT_BYAKUREN && !you.GetPunish(GT_BYAKUREN) && pietyLevel(you.piety) >= 3) || (as_penalty > GetPenaltyMinus(1)))
		{
			if (as_penalty > GetPenaltyMinus(1)) {
				differ_ += as_penalty * 2;
			}
			else {
				//갑옷 방해도가 낮을때는 마법방해가 그정도로 높지않음
				differ_ += as_penalty;
			}

		}
	}

	success_ = max(0,(success_-differ_<=14)?(success_-differ_)*(2*14+(success_-differ_-1)*-1.07)/2:99);
	if(you.GetPunish(GT_BYAKUREN))
		success_ = success_*95/100;
	return success_;

}
int players::GetSpellHungry(int spell_)
{
	int hungry_ = SpellHunger(SpellLevel((spell_list)spell_));
	hungry_ -= s_int*GetSkillLevel(SKT_SPELLCASTING, true);
	if(hungry_<0)
		hungry_=0;
	return hungry_;
}
int players::GetStealth()
{
	int stealth_ = s_dex*3+ GetSkillLevel(SKT_STEALTH, true)*15+(s_agility?50:0);
	if(equipment[ET_ARMOR])
	{
		if(you.god == GT_SHIZUHA && equipment[ET_ARMOR]->value5 == AMK_AUTUMN)
			stealth_ += 150;
	}

	stealth_ += 50*GetProperty(TPT_STEALTH);
	stealth_ -= you.as_penalty*10; //은밀 감소
	if ((you.s_glow || you.GetBuffOk(BUFFSTAT_HALO))) {
		stealth_ /= 2;
	}
	if(you.GetPunish(GT_SHIZUHA))
	{
		stealth_ /= 2;
	}
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
	case BUFFSTAT_RE:
	case BUFFSTAT_RP:
	case BUFFSTAT_RCONF:
	case BUFFSTAT_SPL_POW:
	case BUFFSTAT_REGEN:
	case BUFFSTAT_MREGEN:
	case BUFFSTAT_HASTE:
	case BUFFSTAT_HALO:
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
	float base_ = (((float)rand_int(240,300))/(max(max_hp,40)+7.0f)+delay_)*10;

	//ex 20이면 20턴당 1회복 100턴간 5회복
	//10이번 100턴간 10회복
	//즉 100/ hp_recov가 100턴동안 회복량
	//만약 100턴간 10회복을 추가하려고하면
	//20일때 15가 되야되니까 20->6
	//10일때 20이 되어야하니까 10->5
	float cacul_ = 1000.0f/base_; //100턴당 회복량.

	if(god == GT_MINORIKO && !GetPunish(GT_MINORIKO) && pietyLevel(piety)>=1)
	{
		int piety_ = (pietyLevel(you.piety)+1)/2;
		cacul_ += (piety_*5+(piety_*5*max_hp/100.f))*max(power-200,0)/300;
	}
	if(god == GT_YUUGI && !GetPunish(GT_YUUGI) && s_drunken )
	{
		cacul_ += 100.0f;
	}
	//if (you.equipment[ET_NECK] && you.equipment[ET_NECK]->value1 == AMT_WEATHER && you.getAmuletPercent() >= 100) {
	//	cacul_ += max_hp/2;
	//}
	{
		cacul_ += 100 * you.GetBuffOk(BUFFSTAT_REGEN);
	}
	if(GetProperty(TPT_REGEN)>0)
	{
		cacul_ += 40*GetProperty(TPT_REGEN);
	}
	else if(GetProperty(TPT_REGEN)<0)
	{
		cacul_ *= 0.7f;
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
			bool already_ = (GetHp() == GetMaxHp());
			HpUpDown(1,DR_NONE);
			HpRecoverDelay(0);
			if(GetHp() == GetMaxHp() && !already_)
				return IT_HP_RECOVER;
		}
	}
	return IT_NONE;
}
bool skill_suicide_bomb(int power, bool short_, unit* order, coord_def target);
void deadlog();
void resurectionlog(char* reason);
int players::HpUpDown(int value_,damage_reason reason, unit *order_)
{
	int prev_value_ = value_;
	if (value_ > 0 && s_evoke_ghost) {
		//유령화 상태에선 체력이 회복되지않음.
		return prev_value_;
	}

	if(value_<0 && GetMaxHp()/2 <= -value_)
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
	if (s_sleep < 0 && value_ < 0 && reason != DR_SLEEP) {
		printlog("데미지에 의해 잠에서 깼다! ", false, false, false, CL_white_blue);
		s_sleep = 0;
	}
	if (pure_mp && value_ < 0 && mp > 0)
	{
		int temp_value_ = value_+mp;
		mp = max(0, mp + value_);
		value_ = temp_value_;
		if (value_ >= 0)
			return prev_value_;
	}
	int prev_hp_ = GetHp();
	hp+= value_;
	GodAccpect_HPUpDown(value_,reason);
	if(hp >= max_hp)
	{
		int plus_ = hp - max_hp;
		if (pure_mp && mp < max_mp)
		{
			mp = min(mp + plus_, max_mp);
		}
		hp = max_hp;		
	}	


	if(hp<=0)
	{
		if (equipment[ET_NECK] && equipment[ET_NECK]->value1 == AMT_PERFECT && getAmuletPercent() >= 100)
		{
			deadlog();
			soundmanager.playSound("gameover");
			MoreWait();
			resurectionlog("완전 무결의 부적");
			printlog("그러나 완전 무결의 부적이 부숴지면서 힘이 돌아오는 것을 느꼈다!", true, false, false, CL_white_blue);
			hp = max_hp;
			mp = max_mp;
			for (list<item>::iterator it = item_list.begin(); it != item_list.end(); it++)
			{
				if (&(*it) == equipment[ET_NECK]) {
					you.resetAmuletPercent((amulet_type)equipment[ET_NECK]->value1);
					DeleteItem(it);
					break;
				}
			}
		}
		else if(GetProperty(TPT_9_LIFE))
		{
			deadlog();
			soundmanager.playSound("gameover");
			resurectionlog("리저렉션");
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
			soundmanager.playSound("gameover");
			resurectionlog("리저렉션");
			printlog("리저렉션!",true,false,false,CL_white_blue);
			skill_suicide_bomb(level*8,false,&you,position);
			MoreWait();
			hp = max_hp;
			mp = max_mp;
			image = &img_play_mokou[2];
			DeleteProperty(TPT_18_LIFE);
		}
		else if (GetProperty(TPT_PURE_LIFE) && reason != DR_JUNKO)
		{
			deadlog();
			soundmanager.playSound("gameover");
			resurectionlog("순호의 생명순화");
			printlog("죽어가던 당신의 생명력이 돌아왔다!", true, false, false, CL_white_blue);
			MoreWait();
			hp = max_hp;
			mp = max_mp;
			int life_ = GetProperty(TPT_PURE_LIFE);
			if (life_ > 1) {
				DeleteProperty(TPT_PURE_LIFE);
				SetProperty(TPT_PURE_LIFE, 1);
			}
			else {
				DeleteProperty(TPT_PURE_LIFE);
			}
		}
		else if (you.god == GT_JOON_AND_SION
			&& you.god_value[GT_JOON_AND_SION][0] == 2
			&& pietyLevel(you.piety) >= 4
			&& !you.GetPunish(GT_JOON_AND_SION)
			&& sionResurrection())
		{
			deadlog();
			soundmanager.playSound("gameover");
			MoreWait();
			resurectionlog("시온");
			printlog("시온이 당신의 소모품을 대가로 당신을 부활시켰다!", true, false, false, CL_sion);
			random_extraction<textures*> rand_t;
			rand_t.push(img_fog_sion[0], 3);
			rand_t.push(img_fog_sion[1], 1);
			rand_t.push(img_fog_sion[2], 1);
			MakeCloud(you.position, rand_t, SMT_SION, 9, rand_int(10, 25), 3, 0, 4, &you);
			hp = max_hp / 10;
		}
		else if(wiz_list.wizard_mode == 1)
		{
			MoreWait();
			printlog("죽어? (Y/N)",true,false,false,CL_help);
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
			soundmanager.playSound("gameover");
			GameOver();
		}
	}
	else if (prev_value_ < 0 &&  GetHp() <= GetDangerHp()) {
		if (prev_hp_ > GetDangerHp()) {
			soundmanager.playSound("lowhp");
			printlog("============ 낮은 체력 경고 ============", true, false, false, CL_danger);
		}
	}



	return prev_value_;
}
int players::MpRecoverDelay(int delay_,bool set_)
{
	float base_ =  (((float)rand_int(80,120))/(max(max_mp,10)/4+7.0f)+delay_)*10;

	float cacul_ = 1000/base_; //100턴당 회복량.

	if(s_mana_regen)
		cacul_ +=100;

	
	if(you.god == GT_MINORIKO && !you.GetPunish(GT_MINORIKO) && pietyLevel(you.piety)>=1)
	{
		int piety_ = pietyLevel(you.piety);
		cacul_ += piety_*2+(piety_*max_mp/40.f)*max(power-200,0)/300;
	}





	if(equipment[ET_WEAPON] && equipment[ET_WEAPON]->value5 == WB_MANA_REGEN && !you.s_mana_delay)
	{
		cacul_ +=25;
	}
	{
		cacul_ += 50 * you.GetBuffOk(BUFFSTAT_MREGEN);
	}
	if (you.equipment[ET_NECK] && you.equipment[ET_NECK]->value1 == AMT_WAVE && you.getAmuletPercent() >= 100) {
		cacul_ += 15;
	}
	if(GetProperty(TPT_MP_REGEN)>0)
	{
		cacul_ +=15*GetProperty(TPT_MP_REGEN)-5;
	}
	else if(GetProperty(TPT_MP_REGEN)<0)
	{
		cacul_ *= 0.7f;
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
			bool already_ = (GetMp() == GetMaxMp());
			MpUpDown(1);
			MpRecoverDelay(0);
			

			if(GetMp() == GetMaxMp() && !already_)
				return IT_MP_RECOVER;
		}
	}
	return IT_NONE;
}
int players::MpUpDown(int value_)
{
	if (pure_mp)
	{
		HpUpDown(value_, DR_MP, NULL);
		return mp;
	}
	else 
	{
		mp += value_;
		if (mp >= max_mp)
		{
			mp = max_mp;
		}
		if (mp <= 0)
		{
			mp = 0;
		}
		return mp;
	}
}
int players::AcUpDown(int value_, int bonus_)
{
	real_ac += value_;
	bonus_ac += bonus_;
	float temp_ac = (float)real_ac*(1.0f+ GetSkillLevel(SKT_ARMOUR, true)/15.0f);
	ac = (int)temp_ac+bonus_ac; 
	return ac;
}
int players::EvUpDown(int value_, int bonus_)
{
	real_ev += value_;
	bonus_ev += bonus_;
	int size_ = -2*GetProperty(TPT_SIZE);
	ev = 3+size_+ real_ev*(12+s_dex)/(32.0f-size_) + bonus_ev;
	return ev;
}
int players::ShUpDown(int value_, int bonus_)
{
	real_sh += value_;
	bonus_sh += bonus_;
	float temp_sh = (float)real_sh*(1.0f+(s_dex/5.0f+ GetSkillLevel(SKT_SHIELD, true))/15.0f);
	if(GetProperty(TPT_SLAY))
	{
		temp_sh *= 1.2f;
	}
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
		if (value_ > 0)
			hp += value_;
		max_hp += value_;
		if (hp > max_hp) {
			hp = max_hp;
		}
		break;
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
	case BUFFSTAT_RE:
		you.ResistUpDown(value_, RST_ELEC);
		break;
	case BUFFSTAT_RP:
		you.ResistUpDown(value_, RST_POISON);
		break;
	case BUFFSTAT_RCONF:
		you.ResistUpDown(value_, RST_CONFUSE);
		break;
	case BUFFSTAT_SPL_POW:
		break;
	case BUFFSTAT_REGEN:
		break;
	case BUFFSTAT_MREGEN:
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
	int up_ = (rand_int(25,30)+delay_)*10;
	if(power_keep>0)
	{
		up_*=2;
	}
	else if(power_keep<0)
	{
		up_/=2;
	}

	if(s_haste || s_pure_haste || GetBuffOk(BUFFSTAT_HASTE))
	{
		up_/=up_>0?5:(up_<0?30:20);
	}
	if(s_invisible || togle_invisible)
	{
		up_/=up_>0?5:(up_<0?30:20);
	}
	if(up_<0)
		up_ = 1;
	
	power_decre += up_;
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
	if (GetProperty(TPT_PURE_POWER))
		return power; //풀파워 모드면 떨어지지않음

	bool full_power_ = power>=500?true:false;

	if(big_ && value_<0 && power>500)
		power = 500;
	power+=value_;
	if(power>530+(you.god == GT_MINORIKO?20:0))
		power = 530+(you.god == GT_MINORIKO?20:0);
	else if(power<0)
		power = 0;

	//if(you.god == GT_MINORIKO && !you.GetPunish(GT_MINORIKO) && pietyLevel(you.piety)>=5)
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
	if(value_ == 0)
		return false;
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
void players::BonusSkillUpDown(int skill_, int value_)
{
	bonus_skill[skill_] += value_;
}
void players::SetPureSkill(int skill_)
{
	pure_skill = skill_;
	skill[skill_].onoff = 0;
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
	if (exper_ < 0)
		return false;
	bool level_up_ = false;

	if (int penalty_turn_= CheckPeanltyTurn(current_level)) {
		if (penalty_turn_ >= 1000) {
			float penalty_ = (1.0f - min(penalty_turn_ - 1000, 4000) / 5000.0f);
			exper_ = exper_*penalty_;
			//패널티 경험치는 1000턴부터 감소하기 시작하여 5000턴에서 20%
		}
	}
	if (current_level == ZIGURRAT_LEVEL)
	{
		exper_ = exper_ / 3; //지구랏에선 경험치 33%

	}
	if(you.god == GT_LILLY)
	{
		exper_ = max(1,exper_*0.7f);
		GetFairyExp(max(1,exper_/2));
	} 

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

void players::FairyRevive(bool speak_)
{


	if (you.god == GT_LILLY)
	{
		for (int i = 0; i < 5; i++)
		{
			if (you.god_value[GT_LILLY][i] == 2)
			{
				you.lilly_allys[i].cooldown--;
				if (you.lilly_allys[i].cooldown <= 0)
				{
					//부활!					
					dif_rect_iterator rit(you.position, 2);
					for (; !rit.end(); rit++)
					{
						if (env[current_level].isMove(rit->x, rit->y, true, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && env[current_level].isInSight(coord_def(rit->x, rit->y)) && you.position != (*rit))
						{
							monster* mon_ = env[current_level].AddMonster(you.lilly_allys[i].id, M_FLAG_ALLY, coord_def(rit->x, rit->y));
							if (!(mon_->flag & M_FLAG_UNIQUE))
							{
								mon_->name.name = fairy_name[you.lilly_allys[i].name].name;
								mon_->name.name_type = fairy_name[you.lilly_allys[i].name].name_type;
							}
							if (mon_->isYourShight() && speak_)
							{
								printarray(true, false, false, CL_lilly, 3, mon_->name.name.c_str(), mon_->name.name_is(true), "부활했다!");
								if (mon_->CanSpeak())
									printlog(fairy_speak(mon_, you.lilly_allys[i].personality, FS_REVIVE), true, false, false, CL_normal);
							}
							if (mon_->id == MON_LUNAR && you.char_name.name.compare("써니") == 0) {
								mon_->spell_lists.clear();
								mon_->spell_lists.push_back(spell(SPL_SELF_HEAL, 25));
							}
							while (you.lilly_allys[i].level > mon_->level)
							{
								mon_->LevelUpdown(1, 6.0f, 1.0f);
								switch (mon_->id)
								{
								case MON_SUNNY:
									if (mon_->level == 13)
										mon_->spell_lists.push_back(spell(SPL_LASER, 20));
									break;
								case MON_LUNAR:							
									if (mon_->level == 13)
										mon_->spell_lists.push_back(spell(SPL_SMITE, 20));
									break;
								case MON_STAR:
									if (mon_->level == 13)
										mon_->spell_lists.push_back(spell(SPL_HASTE_OTHER, 20));
									break;
								case MON_DIEFAIRY:
									if (mon_->level == 13)
										mon_->spell_lists.push_back(spell(SPL_HEAL_OTHER, 20));
									break;
								}
							}

							you.lilly_allys[i].map_id = mon_->map_id;
							you.lilly_allys[i].floor = current_level;
							you.god_value[GT_LILLY][i] = 1;
							break;
						}
					}


				}
			}
		}
	}
}

int players::getAmuletPercent()
{
	return 100 * (system_exp.maxi - system_exp.value) / system_exp.maxi;
}

void players::ExpRecovery(int exper_)
{
	if (system_exp.value > 0) {
		system_exp.value -= (you.GetProperty(TPT_PURE_SYSTEM))?3*exper_:exper_;
		if (system_exp.value <= 0) {
			system_exp.value = 0;
			item* _item = you.equipment[ET_NECK];
			if (_item && _item->type == ITM_AMULET){
				chargingFinish((amulet_type)_item->value1, 1);
				if (system_exp.value <= 0) {
					soundmanager.playSound("charge");
					if (isCanCharge((amulet_type)_item->value1)) {
						printlog("부적의 힘이 모두 채워졌다! 이제 원할때 v로 발동할 수 있다.", true, false, false, CL_white_puple);
					}
					else {
						printlog("부적의 힘이 모두 채워졌다!", true, false, false, CL_white_puple);
					}
				}
			}
		}
	}
	exper_recovery -= exper_;
	if(exper_recovery<=0)
	{//일정 경험치를 먹어서 경험치 회복이 이루어짐
		//남은 경험치의 10% 가량을 먹을때마다 1씩
		//초반엔 빠르게 오르므로 그 수치도 많은편(+15 상수치 플러스)
		exper_recovery = (GetNeedExp(max(level-1,0)) - GetNeedExp(max(level-2,0)))/7+15;


		//여기부터 경험치를 먹으면 생기는 일
		if(s_trans_panalty) //시공부작용의 감소
			s_trans_panalty--;


		random_extraction<int> recover_;
		if(s_str < m_str)
			recover_.push(0,1);
		if(s_dex < m_dex)
			recover_.push(1,1);
		if(s_int < m_int)
			recover_.push(2,1);

		if(recover_.GetSize())
		{
			switch(recover_.pop())
			{
			case 0:
				s_str++;
				printlog("잃어버린 힘이 회복되었다.",false,false,false,CL_blue);
				break;
			case 1:
				s_dex++;
				printlog("잃어버린 민첩이 회복되었다.",false,false,false,CL_blue);
				break;
			case 2:
				s_int++;
				printlog("잃어버린 지능이 회복되었다.",false,false,false,CL_blue);
				break;
			}
		}

		
		if(s_unluck)
		{
			s_unluck--;

			if(s_unluck>6 && randA(1)) //불멸에서 50%의 확률로 UFO가 떨어진다.
			{
				random_extraction<int> ufo_;
				ufo_.push(MON_RED_UFO);
				ufo_.push(MON_BLUE_UFO);
				ufo_.push(MON_GREEN_UFO);
				int i = rand_int(2,3);
				for(; i>0 ; i--)
				{
					int time_ = rand_int(20,60);
					if(monster *mon_ = BaseSummon(ufo_.choice(), time_, true, true, 2, NULL, you.position, SKD_OTHER, -1))
					{
					}
				}
				printlog("이럴수가! 하늘에서 UFO가 떨어졌다!",true,false,false,CL_danger);
				enterlog();
			}
			if(!s_unluck)
			{
				printlog("당신의 운세는 정상으로 돌아왔다.",true,false,false,CL_blue);
			}

		}

		FairyRevive(true);


		if(wiz_list.wizard_mode == 1)
		{
			printlog("일정량의 스킬 경험치 획득",true,false,false,CL_help);
		}

		for(int i=0;i<GT_LAST;i++)
		{

			if(punish[i].number && !punish[i].punish)
			{
				//god_punish((god_type)i);
				punish[i].punish = true;
/*
				if(punish[i]==0)
				{

					
					printarray(true,false,false,CL_white_blue,4,"당신은 ", GetGodString((god_type)i),GetGodString_is((god_type)i)?"으로부터 ":"로부터 ","용서받았다.");
	
	
					char temp[200];
					sprintf_s(temp,200,"%s%s 용서받았다.",GetGodString((god_type)i),GetGodString_is((god_type)i)?"으로부터":"로부터");
					AddNote(you.turn,CurrentLevelString(),temp,CL_small_danger);


				}*/
			}
		}
		GodAccpect_Exp_get();

	}
}
void players::CheckPunish(int delay_)
{
	for(int i=0;i<GT_LAST;i++)
	{
		if(punish[i].number)
		{
			punish[i].turn -= delay_;
			if(punish[i].turn<=0)
			{
				if(punish[i].punish)
				{					
					god_punish((god_type)i);
					SetInter(IT_EVENT);
					punish[i].punish = false;
					punish[i].number--;

					if(punish[i].number == 0)
					{						
						printarray(true,false,false,CL_white_blue,4,"당신은 ", GetGodString((god_type)i),GetGodString_is((god_type)i)?"으로부터 ":"로부터 ","용서받았다.");
	
						char temp[200];
						if(you.god==GT_SATORI)
							sprintf_s(temp,200,"%s%s 포기했다.",GetGodString((god_type)i),GetGodString_is((god_type)i)?"은":"는");
						else
							sprintf_s(temp,200,"%s%s 용서받았다.",GetGodString((god_type)i),GetGodString_is((god_type)i)?"으로부터":"로부터");
						AddNote(you.turn,CurrentLevelString(),temp,CL_small_danger);
					}

				}
				punish[i].turn = rand_int(500,100);
			}
		}
	}

}
int players::GetNeedExp(int level_)
{
	if(level_<0)
		return 0;
	return level_up_value[level_]*exper_aptit/100;
}
bool players::GiveSkillExp(skill_type skill_, int exp_, bool speak_)
{
	if(!speak_)
	{
		you.skill[skill_].onoff = 1;
	}
	if (you.cannotSkillup(skill_))
	{
		you.skill[skill_].onoff = 0;
		return false;
	}
	if(skill_ == SKT_ERROR)
	{
		printlog("스킬경험치에 에러가 발생했습니다.",true,false,false,CL_danger);
		return false;
	}
	int need_exp = need_skill_exp(GetSkillLevel(skill_, false),AptCal(skill[skill_].aptit));

	if(need_exp == -1)
	{
		you.skill[skill_].onoff = 0;
		youMaxiExp = true;
		bool allMax = true;
		for (int i = 0; i < SKT_MAX; i++)
		{
			if (!you.cannotSkillup(i) && you.GetSkillLevel(i, false) < 27 )
			{
				allMax = false;
			}
			if (you.skill[i].onoff >= 1)
			{
				youMaxiExp = false;
				break;
			}
		}
		if (allMax == true)
			youMaxiExp = false;
		return false;
	}
	int exp_panalty = exp_to_skill_exp(GetSkillLevel(skill_, false));
	int up_point = (exp_*(4+min(6,exp_panalty)))/exp_panalty;

	if(up_point<0)
		up_point = 0;
	skill[skill_].exper += up_point;
	total_skill_exp+=exp_;
	GodAccpect_Practice(up_point,skill_);
	if(need_exp <= skill[skill_].exper)
	{
		char temp[50];
		int exp_pool = (skill[skill_].exper - need_exp)*exp_panalty/10;
		skill[skill_].level+=1;
		skill[skill_].exper = need_exp;
		if(skill[skill_].level >= 27)
		{			
			you.skill[skill_].onoff = 0;
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
			//그냥 렙마다; 최대마나 1증가
			if(GetSkillLevel(skill_, false) % 3 == 0 || GetSkillLevel(skill_, false) >= 5)
			{
				if((GetSkillLevel(skill_, false) > GetSkillLevel(SKT_SPELLCASTING, false)) || skill_ == SKT_SPELLCASTING)
				{
					if((skill[skill_].level > GetSkillLevel(SKT_EVOCATE, false)) || skill_ == SKT_EVOCATE)
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

void players::EndTurnForPenalty()
{
	if (current_level == BAMBOO_LEVEL)
	{
		penalty_turn[0]++;
	}
	else if (current_level == DREAM_LEVEL)
	{
		penalty_turn[1]++;
	}
	else if (current_level >= PANDEMONIUM_LEVEL && current_level <= PANDEMONIUM_LAST_LEVEL)
	{
		penalty_turn[2]++;
	}
	else if (current_level >= SUBTERRANEAN_LEVEL && current_level <= SUBTERRANEAN_LEVEL_LAST_LEVEL)
	{
		penalty_turn[3]++;
	}
}
int players::CheckPeanltyTurn(int level_)
{
	if (level_ == BAMBOO_LEVEL)
	{
		return penalty_turn[0];
	}
	else if (level_ == DREAM_LEVEL)
	{
		return penalty_turn[1];
	}
	else if (level_ >= PANDEMONIUM_LEVEL && level_ <= PANDEMONIUM_LAST_LEVEL)
	{
		return penalty_turn[2];
	}
	else if (level_ >= SUBTERRANEAN_LEVEL && level_ <= SUBTERRANEAN_LEVEL_LAST_LEVEL)
	{
		return penalty_turn[3];
	}
	return 0;
}


bool players::SkillTraining(skill_type skill_, int percent_)
{
	if(randA((percent_*(skill[skill_].onoff>=1?1:10))-1)>0)
		return false;
	int exper_ = exp_to_skill_exp(GetSkillLevel(skill_, false));
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
			sum+=skill[i].onoff;
		}
	}
	if(sum == 0)
		return false;
	exp = skill_exper/sum;
	for(int i = 0; i < SKT_MAX; i++)
	{
		int remain_exp = exp;
		if(skill[i].onoff==2)
			remain_exp *= 2;
		while(skill[i].onoff && remain_exp>0){
			int exper_ = exp_to_skill_exp(GetSkillLevel(i, false));
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
		printlog("당신은 독에 걸렸다. ",false,false,false,CL_small_danger);
	else
		printlog("당신의 독은 심해졌다. ",false,false,false,CL_small_danger);

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
		printlog("당신은 공간의 불안정함을 느꼈다. ",false,false,false,CL_white_blue);
		s_tele = tele_;
	}
	else
	{
		printlog("당신 주위의 공간은 안정되었다. ",false,false,false,CL_normal);
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
		printlog("당신은 강력해졌다. ",false,false,false,CL_white_blue);
		StatUpDown(5, STAT_STR);
	}
	else
	{
		printlog("당신의 더욱 더 강력해졌다. ",false,false,false,CL_white_blue);

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
		printlog("당신은 똑똑해졌다. ",false,false,false,CL_white_blue);
		StatUpDown(5, STAT_INT);
	}
	else
	{
		printlog("당신은 더욱 더 똑똑해졌다. ",false,false,false,CL_white_blue);

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
		printlog("당신은 민첩해졌다. ",false,false,false,CL_white_blue);
		StatUpDown(5, STAT_DEX);
		EvUpDown(0,5);
	}
	else
	{
		printlog("당신의 더욱 더 민첩해졌다. ",false,false,false,CL_white_blue);

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
		printlog("당신은 빨라졌다. ",false,false,false,CL_white_blue);
	else
	{
		printlog("당신의 가속은 좀 더 길어졌다. ",false,false,false,CL_white_blue);
	}
	s_haste += haste_;
	power_decre = 0;
	if(s_haste>100)
		s_haste = 100;
	return true;
}

bool players::SetPureHaste(int haste_)
{
	if (!haste_)
		return false;
	if (!s_pure_haste)
		printlog("당신은 살의에 의해 빨라졌다. ", false, false, false, CL_white_blue);
	else
	{
		printlog("당신의 살의는 좀 더 길어졌다. ", false, false, false, CL_white_blue);
	}
	s_pure_haste += haste_;
	power_decre = 0;
	if (s_pure_haste>100)
		s_pure_haste = 100;
	return true;
}

bool players::SetConfuse(int confuse_, bool strong_)
{
	if(!confuse_)
		return false;
	if(!strong_ && confuse_resist>0)
		return false;
	confuse_ /= 2; //플레이어는 혼란시간이 적다


	if(!s_confuse)
		printlog("당신은 혼란스러워졌다. ",false,false,false,CL_small_danger);
	else
	{
		printlog("당신의 더욱 더 혼란스러워졌다. ",false,false,false,CL_small_danger);
		confuse_ /=2;
	}
	s_confuse += confuse_;
	if(s_confuse>20)
		s_confuse = 20;
	return true;
}
bool players::SetSlow(int slow_)
{	
	if(!slow_)
		return false;
	if(!s_slow)
		printlog("당신은 느려졌다. ",false,false,false,CL_small_danger);
	else
	{
		printlog("당신의 더욱 더 느려졌다. ",false,false,false,CL_small_danger);
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
		printlog("당신은 몸이 얼어붙어 움직이기 힘들어졌다. ",false,false,false,CL_small_danger);
	else
	{
		printlog("당신의 더욱 몸이 얼어붙어 움직이기 힘들어졌다. ",false,false,false,CL_small_danger);
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
		printlog("당신은 전기를 방출하기 시작했다. ",false,false,false,CL_white_blue);
	else
	{
		printlog("당신은 더 오랫동안 전기를 방출한다. ",false,false,false,CL_white_blue);
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

	printlog("당신은 마비되었다. ",false,false,false,CL_small_danger);

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
		printlog("당신은 공중에 뜨기 시작했다. ",false,false,false,CL_white_blue);
	else
	{
		printlog("당신은 더 오랫동안 공중에 뜨게 되었다. ",false,false,false,CL_white_blue);
	}
	s_levitation += levitation_;
	if(s_levitation>100)
		s_levitation = 100;
	return true;
}
bool players::SetGlow(int glow_, bool no_speak)
{
	if(!glow_)
		return false;
	if(!s_glow)
		printlog("당신은 빛을 내기 시작했다. ",false,false,false,CL_small_danger);
	else
	{
		printlog("당신은 더 강한 빛을 내고 있다. ",false,false,false,CL_small_danger);
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
		printlog("당신의 탄막을 피하는 감각이 좋아졌다. ",false,false,false,CL_white_blue);
	else
	{
		printlog("당신의 탄막을 피하는 감각이 지속된다. ",false,false,false,CL_white_blue);
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
		printlog("당신은 주변의 소리를 지웠다. ",false,false,false,CL_white_blue);
	else
		printlog("당신은 주변의 소리를 지웠다. ",false,false,false,CL_white_blue);
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
		printlog("당신은 아파졌다. ",false,false,false,CL_small_danger);
	else
	{
		printlog("당신은 더욱 아파졌다. ",false,false,false,CL_small_danger);
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
		printlog("당신 주변에 바람이 휘감긴다. ",false,false,false,CL_white_blue);
	else
	{
		printlog("당신 주변에 휘감긴 바람이 좀 더 오래간다. ",false,false,false,CL_white_blue);
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
		printlog("당신은 투명해졌다. ",false,false,false,CL_white_blue);
	else
	{
		printlog("당신은 더 오래 투명해졌다. ",false,false,false,CL_white_blue);
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
		
		SetInter(IT_STAT);
	}
}
bool players::SetSwift(int swift_)
{
	if (!swift_)
		return false;
	if (s_superman)
		return false;

	if (!s_swift) {
		if (swift_>0) {
			printlog("당신은 다리가 빨라졌다. " , false, false, false, CL_white_blue);
		}
		else {
			printlog("당신은 다리가 느려졌다. ", false, false, false, CL_small_danger);
		}
	}
	else
	{
		if (swift_ > 0) {
			if(s_swift > 0)
				printlog("당신은 더 오래 달릴 수 있다. ", false, false, false, CL_white_blue);
			else 
				printlog("당신은 느린 걸음을 고쳐세웠다. ", false, false, false, CL_white_blue);
		}
		else {
			if (s_swift > 0)
				printlog("당신은 가볍던 발이 무거워진 것을 느꼈다. ", false, false, false, CL_small_danger);
			else
				printlog("당신은 다리가 더욱 느려졌다. ", false, false, false, CL_small_danger);
		}
	}
	s_swift += swift_;
	if(s_swift>100)
		s_swift = 100;
	if (s_swift<-100)
		s_swift = -100;
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
		printlog("당신은 다리가 엄청나게 빨라졌다. ",false,false,false,CL_white_blue);
	else
	{
		printlog("당신은 더 오래 달릴 수 있다. ",false,false,false,CL_white_blue);
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
		printlog("당신의 주변에 바람이 휘감겼다. ",false,false,false,CL_white_blue);
	else
	{
		printlog("당신의 주변에 바람이 더 휘감겼다. ",false,false,false,CL_white_blue);
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
		printlog("당신은 자동으로 탄막을 회수하기 시작한다. ",false,false,false,CL_white_blue);
	else
	{
		printlog("탄막을 회수하는 시간이 길어졌다. ",false,false,false,CL_white_blue);
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
		printlog("당신은 취했다. ",false,false,false,CL_warning);
	else
	{
		printlog("당신은 더욱 더 취했다. ",false,false,false,CL_warning);
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
		printlog("당신은 광기에 휩싸였다. ",false,false,false,CL_danger);
	else
	{
		//printlog("당신은 더욱 더 미쳤다. ",false,false,false,CL_warning);
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
	printlog("당신은 모든 데미지를 반사한다. ",false,false,false,CL_white_blue);
	s_mirror = mirror_;
	return true;

}
bool players::SetParadox(int s_paradox_)
{
	if(s_paradox_)
		printlog("당신은 도플갱어를 통해 탄막을 연달아 발사할 준비가 되었다. ",true,false,false,CL_white_blue);
	s_paradox = s_paradox_;
	return true;

}

bool players::SetTransPanalty(int s_trans_panalty_)
{
	if(!s_trans_panalty_)
		return false;

	if(s_trans_panalty_<3)
		printlog("약간의 시공간 부작용을 받았다. ",true,false,false,CL_bad);
	else if(s_trans_panalty_<5)
		printlog("상당한 시공간 부작용을 받았다. ",true,false,false,CL_normal);
	else
		printlog("어마어마한 시공간 부작용을 받았다. ",true,false,false,CL_small_danger);
	s_trans_panalty += s_trans_panalty_;
	return true;
}
bool players::SetTheWorld(int s_the_world_)
{
	if(!s_the_world_)
		return false;
	if(!s_the_world)
		printlog("더 월드! ",false,false,false,CL_white_blue);
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
int players::isSetMikoBuff(int temp_)
{
	for (list<buff_class>::iterator it = buff_list.begin(); it != buff_list.end(); it++)
	{
		if (temp_ == 0) {
			//미코 망토
			if (it->id == BUFF_MIKO_REGEN)
				return 1; //빨간망토
			if (it->id == BUFF_MIKO_MREGEN)
				return 2; //파랑망토
		}
		else if (temp_ == 1) {
			//미코 궁극
			if (it->id == BUFF_MIKO_ULTI) {
				if (it->stat == BUFFSTAT_HP)
					return 1;
				else if (it->stat == BUFFSTAT_MREGEN)
					return 2;
				else if (it->stat == BUFFSTAT_HASTE)
					return 3;
			}
		}
		else if (temp_ == 2) {
			//미코 징벌
			if (it->id == BUFF_MIKO_RF_MINUS || it->id == BUFF_MIKO_RC_MINUS) {
				return 1;
			}
		}
	}
	return 0;
}
int players::reSetMikoBuff()
{
	int num = 0;

	for (list<buff_class>::iterator it = buff_list.begin(); it != buff_list.end(); )
	{
		auto temp = it++;
		if (temp->id >= BUFF_MIKO_START && temp->id <= BUFF_MIKO_END)
		{
			UpDownBuff(temp->stat, -1 * temp->value);
			buff_list.erase(temp);
			num++;
		}
	}
	return num;
}
bool players::SetBuff(stat_up stat_, buff_type id_, int value_, int turn_)
{
	if(id_ != BUFF_DUPLE){
		for(list<buff_class>::iterator it=buff_list.begin();it!=buff_list.end();it++)
		{
			if(it->id == id_){ //id가 겹치면 기존의 버프를 덮어 씌운다.
				if (turn_ == 0) {
					//삭제
					UpDownBuff(it->stat, -1 * it->value);
					buff_list.erase(it);
				}
				else {
					UpDownBuff(it->stat, -1 * it->value);
					it->stat = stat_;
					it->turn = turn_;
					it->value = value_;
					UpDownBuff(it->stat, it->value);
				}
				return true;
			}
		}
	}
	if (turn_ == 0) {
		return false;
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
bool players::SetEirinHeal(int value_, bool punish_)
{

	int real_value_ = min(GetMaxHp() - GetHp(), value_);
	
	//수치만큼 힐하기

	if(!punish_)
	{	
		you.HpUpDown(real_value_,DR_EFFECT);

	}
	else
	{
		real_value_ = value_;
	}

	s_eirin_poison += real_value_;
	s_eirin_poison_time = rand_int(100,200);

	return true;

}
bool players::SetExhausted(int s_exhausted_)
{
	s_exhausted = s_exhausted_;
	return true;
}

bool players::SetStasis(int s_stasis_)
{
	if(!s_stasis_)
		return false;
	if(!s_drunken)
		printlog("당신은 전이를 방해받았다.",false,false,false,CL_small_danger);
	else
	{
		printlog("당신의 전이 방해는 더욱 길어졌다.",false,false,false,CL_small_danger);
	}
	s_stasis += s_stasis_;
	if(s_stasis>100)
		s_stasis = 100;
	return true;
}

bool players::SetForceStrong(bool force_, int turn_, bool speak_)
{
	if(!turn_)
		return false;
	
	if(speak_)
	{
		if(!force_)
			printlog("당신은 공격과 마법의 위력이 대폭 감소했다. ",true,false,false,CL_small_danger);
		else
		{
			printlog("당신의 공격과 마법의 위력은 대폭 증가했다. ", true,false,false,CL_white_blue);
		}
	}

	force_strong = force_;
	force_turn = turn_;
	return true;
}
bool players::SetUnluck(int s_unluck_)
{
	s_unluck += s_unluck_;
	if(s_unluck > 10)
		s_unluck = 10;
	return true;
}

bool players::SetSuperGraze(int s_super_graze_)
{
	s_super_graze += s_super_graze_;
	return true;
}
bool players::SetNoneMove(int s_none_move_)
{
	s_none_move += s_none_move_;
	return true;
}
bool players::SetNightSight(int value_, int turn_, bool stong_)
{
	if (!turn_)
		return false;
	if (!stong_ && (you.invisible_view))
		return false;
	if(!s_night_sight_turn)
		printlog("당신의 눈은 침침해졌다.", false, false, false, CL_small_danger);
	else if(s_night_sight_turn && s_night_sight > value_)
		printlog("당신의 눈은 더욱 더 침침해졌다!", false, false, false, CL_small_danger);
	s_night_sight = value_;
	s_night_sight_turn = turn_;
	return true;
}
bool players::SetSleep(int value_)
{
	if (s_sleep < 0 || value_ < 0)
		return false;

	s_sleep += value_;

	if (s_sleep > 99) {
		s_sleep = -10;
		printlog("당신은 잠에 빠졌다!", true, false, false, CL_danger);
		MoreWait();
	}
	return true;
}
bool players::SetPureTurn(int value_, int turn_)
{
	if (!turn_)
		return false;
	s_pure += value_;
	if (s_pure_turn != -1 && (s_pure_turn < turn_  || turn_ == -1))
		s_pure_turn = turn_;
	return true;
}
bool players::SetWeather(int value_, int turn_)
{
	if (!turn_)
		return false;
	s_weather = value_;
	if (s_weather_turn != -1 && (s_weather_turn < turn_ || turn_ == -1))
		s_weather_turn = turn_; 
	if (s_weather == 3 && s_weather_turn > 0) {
		s_glow = 1;
	}
	resetLOS();
	return true;
}
bool players::SetEvokeGhost(int turn_)
{
	s_evoke_ghost = turn_;
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
bool players::GetPunish(god_type god_)
{
	if (god_ < 0)
		return false;
	return punish[god_].number;
}
int players::GetSkillLevel(int skill_, bool bonus_)
{
	if (pure_skill == skill_)
		return you.level;

	int return_ = skill[skill_].level;

	if (bonus_) {
		return_+=bonus_skill[skill_];
	}
	if (return_ > 27)
		return_ = 27;
	return return_;	
}
bool players::cannotSkillup(int skill_)
{
	if (pure_skill == skill_)
		return true;

	return false;
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
			it->gain(false);
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
	return false;
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
bool players::Tele_check(bool preiden_, bool ctele_)
{
	//이 함수는 의도적으로 전이를 하려할때 경고메시지 혹은 취소 시키는 용도로 쓴다.
	//true는 이 전이를 허용한것, false는 비 허용
	
			
	
	if(s_stasis)
	{
		printlog("당신은 전이방해도중에 전이를 사용할 수 없다.",true,false,false,CL_normal);
		return false;
	}

	if(you.god == GT_YUKARI)
	{
		if(!preiden_)
		{				
			printlog("유카리는 당신의 위험한 전이도구 사용을 한번만 봐주기로 하였다.",true,false,false,CL_small_danger);
		}		
		else
		{
			changedisplay(DT_GAME);
			printlog("유카리는 위험한 전이를 금지하고있다. 그래도 쓸건가?(Y/N)",false,false,false,CL_danger);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				enterlog();
				if(you.god == GT_YUKARI)
				{
					printlog("유카리는 당신의 위험한 전이마법에 분노했다!",true,false,false,CL_small_danger);
					you.PietyUpDown(-5);
				}
				break;
			case 'N':
			default:
				printlog(" 취소하였다.",true,false,false,CL_normal);
				return false;
			}
		}
	}


	return true;
}
void players::LevelUp(bool speak_)
{
	level++;
	if(speak_)
	{
		char temp[50];
		sprintf_s(temp,50,"당신의 레벨이 올랐다! 레벨 %d",you.level);
		printlog(temp,true,false,false,CL_good);
		soundmanager.playSound("levelup");
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

	max_mp += 1;
	mp += 1;
	if(level % 3 == 0)
	{
		max_mp += 1;
		mp += 1;

	}


	remainSpellPoiont++;
	LevelUpTribe(level);
	CalcuHP();
	
	if(speak_)
	{
		if (!you.pure_mp)
		{
			char temp[200];
			sprintf_s(temp, 200, "레벨업 : 레벨 %2d. HP: %4d/%4d , MP: %4d/%4d", level, GetHp(), GetMaxHp(), GetMp(), GetMaxMp());
			AddNote(you.turn, CurrentLevelString(), temp, CL_good);
		}
		else
		{
			char temp[200];
			sprintf_s(temp, 200, "레벨업 : 레벨 %2d. HP: %4d/%4d", level, GetHp(), GetMaxHp());
			AddNote(you.turn, CurrentLevelString(), temp, CL_good);
		}
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
			if((out_of_sight && !(you.s_dimension && you.god == GT_YUKARI)) || env[current_level].DisableMove(coord_def(x,y),true))
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
					if((you.s_dimension && you.god == GT_YUKARI) && out_of_sight)
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
						
						if((you.s_dimension && you.god == GT_YUKARI) && out_of_sight)
						{
							if(abs(you.god_value[GT_YUKARI][0] - check_pos_.x)>8)
								check_pos_.x += (you.god_value[GT_YUKARI][0] - check_pos_.x)>0?17:-17;
							if(abs(you.god_value[GT_YUKARI][1] - check_pos_.y)>8)
								check_pos_.y += (you.god_value[GT_YUKARI][1] - check_pos_.y)>0?17:-17;
						}


						if(!env[current_level].isSight(check_pos_))
						{
							intercept = true;
							break;					
						}
						if (you.s_weather == 1 && you.s_weather_turn > 0) {
							//안개효과로 항상 시야를 줄임
							block_cloud--;
							if (block_cloud <= 0)
							{
								intercept = true;
								break;
							}
						}
						if(env[current_level].isSmokePos(check_pos_.x,check_pos_.y,true))
						{
							smoke* smoke_ = env[current_level].isSmokePos2(check_pos_.x,check_pos_.y);
							if(smoke_ && smoke_->sight_inter())
							{
								block_cloud-=smoke_->sight_inter();
								if(block_cloud <= 0)
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
						
					//if((you.s_dimension && you.god == GT_YUKARI) && out_of_sight)
					//{
					//	if(abs(you.god_value[GT_YUKARI][0] - check_pos_.x)>8)
					//		check_pos_.x += (you.god_value[GT_YUKARI][0] - check_pos_.x)>0?-17:17;
					//	if(abs(you.god_value[GT_YUKARI][1] - check_pos_.y)>8)
					//		check_pos_.y += (you.god_value[GT_YUKARI][1] - check_pos_.y)>0?-17:17;
					//}
					

					env[current_level].dgtile[check_pos_.x][check_pos_.y].flag |= FLAG_INSIGHT;
					if(!(env[current_level].dgtile[check_pos_.x][check_pos_.y].flag & FLAG_EXPLORE))
					{
						if(explore_map++ % 100 == 0)
						{
							GodAccpect_Explore_100();
						}
						env[current_level].dgtile[check_pos_.x][check_pos_.y].flag |= FLAG_EXPLORE;
						env[current_level].CheckForbid(check_pos_);
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
						case DG_TEMPLE_JOON_AND_SION:
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
						case DG_TEMPLE_SEIJA:
						case DG_TEMPLE_LILLY:
						case DG_TEMPLE_MIKO:
						case DG_TEMPLE_OKINA:
						case DG_TEMPLE_JUNKO:
						case DG_ZIGURRAT_STAIR:
							switch(env[current_level].dgtile[check_pos_.x][check_pos_.y].tile)
							{								
							case DG_TEMPLE_STAIR:									
								map_list.dungeon_enter[TEMPLE].detected = true;
								break;
							case DG_MISTY_LAKE_STAIR:									
								map_list.dungeon_enter[MISTY_LAKE].detected = true;
								break;
							case DG_YOUKAI_MOUNTAIN_STAIR:	
								map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected = true;
								break;
							case DG_SCARLET_STAIR:	
								map_list.dungeon_enter[SCARLET_M].detected = true;		
								break;				
							case DG_SCARLET_L_STAIR:
								map_list.dungeon_enter[SCARLET_L].detected = true;		
								break;				
							case DG_SCARLET_U_STAIR:
								map_list.dungeon_enter[SCARLET_U].detected = true;		
								break;				
							case DG_BAMBOO_STAIR:
								map_list.dungeon_enter[BAMBOO].detected = true;		
								break;				
							case DG_EIENTEI_STAIR:	
								break;				
							case DG_SUBTERRANEAN_STAIR:
								map_list.dungeon_enter[SUBTERRANEAN].detected = true;		
								break;
							case DG_YUKKURI_STAIR:
								map_list.dungeon_enter[YUKKURI_D].detected = true;		
								break;
							case DG_DEPTH_STAIR:
								map_list.dungeon_enter[DEPTH].detected = true;		
								break;
							case DG_DREAM_STAIR:
								map_list.dungeon_enter[DREAM_D].detected = true;		
								break;
							case DG_MOON_STAIR:				
								break;
							case DG_PANDEMONIUM_STAIR:
								map_list.dungeon_enter[PANDEMONIUM].detected = true;		
								break;	
							case DG_HAKUREI_STAIR:
								map_list.dungeon_enter[HAKUREI_D].detected = true;		
								break;
							case DG_ZIGURRAT_STAIR:
								map_list.dungeon_enter[ZIGURRAT].detected = true;
								break;
							}

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
	env[current_level].ResetForbid();



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
		bool sion_ = (you.god == GT_JOON_AND_SION &&
			you.god_value[GT_JOON_AND_SION][0] == 2 &&
			!you.GetPunish(GT_JOON_AND_SION) &&
			pietyLevel(you.piety) >= 2);
		if (!sion_)
		{
			PowUpDown(t->value5);
			if (speak_)
				printlog("P가 증가했다.", false, false, false, CL_normal);
		}
		ReleaseMutex(mutx);
		if (speak_)
			soundmanager.playSound("pickup");
		GodAccpect_GetPitem();
		return 1;
	}

	if(t->type == ITM_GOAL)
	{
		char temp[200];
		sprintf_s(temp,200,"당신은 %s의 룬을 주웠다! ( ]키로 그동안 얻은 룬을 표시 )",rune_string[t->value1]);
		printlog(temp,true,false,false,CL_good);
		sprintf_s(temp,200,"%s의 룬을 얻었다.",rune_string[t->value1]);
		AddNote(you.turn,CurrentLevelString(),temp,CL_warning);
		rune[t->value1]++;
		ReleaseMutex(mutx);
		if (speak_)
			soundmanager.playSound("rune");
		return 1;
	}
	if(t->type == ITM_ORB)
	{
		
		printlog("당신은 음양옥을 주웠다. 던전1층으로 가지고 올라가면 승리한다!",true,false,false,CL_good);
		char temp[200];
		sprintf_s(temp,200,"음양옥을 얻었다.");
		AddNote(you.turn,CurrentLevelString(),temp,CL_warning);
		ReleaseMutex(mutx);
		if (speak_)
			soundmanager.playSound("rune");
		reimu_turn = 100;
		rune[RUNE_HAKUREI_ORB]++;
		return 1;
	}
	if(t->type == ITM_BOOK)
	{
		t->Identify(); //책은 항상 줍자마자 식별
	}
	if (t->type == ITM_THROW_TANMAC)
	{
		//던지기 아이템은 줍는순간 자동 줍기가 켜진다.
		if (!t->throw_item) {
			int cur = IDEN_CHECK_ETC_START + t->value4;
			iden_list.autopickup[cur+2] = true;
		}
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
						sprintf_s(temp,2,"%c",it->id);
						printlog(temp,false,false,false,it->item_color());
						printlog(" - ",false,false,false,it->item_color());
						printlog(it->GetName(),false,false,false,it->item_color());

						if(t->num)
						{
							printlog(" (",false,false,false,CL_normal);
							char temp_[16];
							sprintf_s(temp_, 16,"%d",t->num);
							printlog(temp_,false,false,false,CL_normal);
							printlog("개 획득)",true,false,false,CL_normal);
						}
					}
					if (t->pick())
						you.throw_weapon = &(*it);
					final_item = it->id;
					final_num = t->num;
					ReleaseMutex(mutx);
					if (speak_)
						soundmanager.playSound("pickup");
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
				sprintf_s(temp, 2,"%c",(*t).id);
				printlog(temp,false,false,false,(*t).item_color());
				printlog(" - ",false,false,false,(*t).item_color());
				printlog((*t).GetName(),true,false,false,(*t).item_color());
			}
			if (it_temp->pick()) {
				throw_weapon = &(*it_temp);
			}

			final_item = t->id;
			final_num = t->num;
			ReleaseMutex(mutx);
			if (speak_)
				soundmanager.playSound("pickup");
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
					soundmanager.playSound("powerup");
					time_delay += you.GetNormalDelay();
					TurnEnd();
					
					if(you.god == GT_MINORIKO && !you.GetPunish(GT_MINORIKO) && pietyLevel(you.piety)>=5)
					{
						int rand_num_ =  rand_int(80,100);
						you.SetBuff(BUFFSTAT_RF,BUFF_MINORIKO_RF,1,rand_num_);
						you.SetBuff(BUFFSTAT_RC,BUFF_MINORIKO_RC,1,rand_num_);
					}
					if(you.god == GT_MINORIKO && !you.GetPunish(GT_MINORIKO) && pietyLevel(you.piety)>=3)
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
	if (you.s_pure_turn && you.s_pure >= 20)
	{
		printlog("당신은 물약의 맛을 느끼기엔 너무 순화되어있다.", true, false, false, CL_normal);
		return false;
	}

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
					int use_num_ = 1;
					if(!you.GetPunish(GT_EIRIN) || randA(1))
					{
						if (you.god == GT_JOON_AND_SION || you.GetPunish(GT_JOON_AND_SION))
						{
							if (you.god_value[GT_JOON_AND_SION][0] == 1 || randA(3) == 0)
							{
								use_num_ = rand_int(2, 3);
							}
						}
						if (use_num_ > it->num)
							use_num_ = it->num;
						if (use_num_ <= 0)
						{
							ReleaseMutex(mutx);
							return false;
						}

						soundmanager.playSound("potion");
						drinkpotion((potion_type)(*it).value1, false);

						if (use_num_ > 1) {
							for (int i = 1; i < use_num_; i++) {
								enterlog();
								drinkpotion((potion_type)(*it).value1, true);
							}
							if (you.god == GT_JOON_AND_SION
								&& you.god_value[GT_JOON_AND_SION][0] == 1
								&& pietyLevel(you.piety) >= 4
								&& !you.GetPunish(GT_JOON_AND_SION))
							{
								joonRandomBuff();
							}
						}

						if(iden_list.potion_list[(*it).value1].iden == false)
						{		
							printarray(false,false,false,CL_normal,3,"이것은 ",potion_iden_string[(*it).value1],"물약이다. ");		
						}
						iden_list.potion_list[(*it).value1].iden = true;
						(*it).identify = true;
					}
					else
					{
						printarray(true,false,false,CL_small_danger,1,"에이린이 당신이 마실 물약을 그냥 물로 만들어버렸다!");
						drinkpotion(PT_WATER, false);
					}

					if (use_num_ > 1) {
						enterlog();
						char temp[100];
						sprintf_s(temp, 100, "역병신의 저주로 인해 %d개의 %s%s 낭비하여 사용하였다.", use_num_, it->GetName(-2).c_str(), it->GetNameInfor().name_to());
						printarray(true, false, false, CL_small_danger, 1, temp);
					}
					DeleteItem(it, use_num_);
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
bool players::Evoke(char id_, bool auto_)
{



	for(auto it = item_list.begin(); it != item_list.end(); it++)
	{
		if((*it).id == id_)
		{
			if (you.s_evoke_ghost &&
				!((*it).type == ITM_MISCELLANEOUS && (*it).value1 == EVK_GHOST_BALL)
				) {
				printlog("유령상태에선 오쿠리쵸친을 제외한 아이템을 발동하는건 불가능해! ", true, false, false, CL_normal);
				return false;
			}
			WaitForSingleObject(mutx, INFINITE);
			if((*it).type == ITM_SPELL)
			{
				if(((*it).identify || (*it).value3 == -1) && (*it).value1 <= 0)
				{
					printlog("남은 횟수가 없다.",true,false,false,CL_normal);
					ReleaseMutex(mutx);
					return false;	
				}
				ReleaseMutex(mutx);
				int bonus_pow_ = 11+max(you.level*3+ GetSkillLevel(SKT_EVOCATE, true)*4 , GetSkillLevel(SKT_EVOCATE, true) * 7);
				if(evoke_spellcard((spellcard_evoke_type)(*it).value2, bonus_pow_,(*it).value1 == 0, iden_list.spellcard_list[(*it).value2].iden == 2, auto_))
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

				if(evoke_evokable(auto_, 0, (evoke_kind)(*it).value1))
				{
					you.doingActionDump(DACT_EVOKE, (*it).name.name);
					return true;
				}
				else {
					return false;
				}
			}
			if ((*it).type == ITM_AMULET)
			{
				if (equipment[ET_NECK] != &(*it))
				{
					printlog("끼고있는 부적만을 발동할 수 있다.", true, false, false, CL_normal);
					ReleaseMutex(mutx);
					return false;
				}
				if (!isCanEvoke((amulet_type)(*it).value1))
				{
					printlog("이 부적은 발동할 수 있는 부적이 아니다.", true, false, false, CL_normal);
					ReleaseMutex(mutx);
					return false;
				}
				if (you.getAmuletPercent() < 100)
				{
					printlog("부적의 충전율이 100%가 되어야 발동할 수 있다.", true, false, false, CL_normal);
					ReleaseMutex(mutx);
					return false;
				}
				ReleaseMutex(mutx);
				if (evokeAmulet((amulet_type)(*it).value1, (*it).value2)) {
					(*it).value3++;
					you.doingActionDump(DACT_EVOKE, (*it).name.name);
					resetAmuletPercent((amulet_type)(*it).value1);
					return true;
				}
				else
					return false;


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

					soundmanager.playSound("scroll");
					printarray(true,false,false,CL_normal,3,it->GetName(-2).c_str(),it->GetNameInfor().name_to(true),"읽었다.");
					bool pre_iden_ = (iden_list.scroll_list[(*it).value1].iden == 3);
					int use_num_ = 1;
					if (you.god == GT_JOON_AND_SION || you.GetPunish(GT_JOON_AND_SION))
					{
						if (you.god_value[GT_JOON_AND_SION][0] == 1 || randA(3) >= 0)
						{
							use_num_ = rand_int(2, 3);
						}
					}
					if (use_num_ > it->num )
						use_num_ = it->num;
					if (use_num_ <= 0)
					{
						ReleaseMutex(mutx);
						return false;
					}

					bool use_ = readscroll((scroll_type)(*it).value1, pre_iden_, false);
					if(!use_)
					{		
						ReleaseMutex(mutx);
						return false;		
					}
					else if(use_num_ > 1){
						for(int i = 1; i < use_num_; i++)
							readscroll((scroll_type)(*it).value1, true, true);
						if (you.god == GT_JOON_AND_SION
							&& you.god_value[GT_JOON_AND_SION][0] == 1
							&& pietyLevel(you.piety) >= 4
							&& !you.GetPunish(GT_JOON_AND_SION))
						{
							joonRandomBuff();
						}
					}

					if(iden_list.scroll_list[(*it).value1].iden == 3)
					{
						if(!pre_iden_)
							printarray(true,false,false,CL_normal,3,"이것은 ",it->GetName(-2).c_str(),it->GetNameInfor().name_type?"이다":"다.");
						if (use_num_ > 1) {
							char temp[100];
							sprintf_s(temp, 100, "역병신의 저주로 인해 %d개의 %s%s 낭비하여 사용하였다.", use_num_, it->GetName(-2).c_str(), it->GetNameInfor().name_to());
							printarray(true, false, false, CL_small_danger, 1, temp);
						}
						(*it).identify = true;
					}
					//if(!you.skill[SKT_SPELLCASTING].level)
					//	SkillTraining(SKT_SPELLCASTING,1);

					DeleteItem(it, use_num_);
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
	
	//if(you.skill[SKT_SPELLCASTING].level == 0)
	//{
	//	printlog("당신은 아직 주문을 배울 수 없다!",true,false,false,CL_normal);
	//	return false;
	//}
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
	for(int i = 0; i < 52; i++){
		if(!you.MemorizeSpell[i]){
			you.MemorizeSpell[i] = spell_;
			break;
		}
	}
	currentSpellNum++;
	return true;
}
bool players::isMemorize(int spell)
{
	for (int i = 0; i < 52; i++) {
		if (you.MemorizeSpell[i] == spell)
		{
			return true;
		}
	}
	return false;
}
int players::Ability(int skill_, bool god_, bool unset_, int immediately)
{
	int set_=-1;
	for(int i=(skill_==SKL_ABANDON_GOD?26+'Q'-'A':(god_?0:5));i<52;i++)
	{
		if(MemorizeSkill[i] == skill_)
		{
			set_ = i;
			break;
		}
	}
	if(set_ == -1 && !unset_)
	{
		for(int i=(skill_==SKL_ABANDON_GOD?26+'Q'-'A':(god_?0:5));i<52;i++)
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

	
	if(you.god_value[GT_SEIJA][0] == 1)
	{		
		if(speak_)
			printlog("배신자에겐 입교란 없다!",true,false,false,CL_danger);
		return false;
	}
	if(god == GT_SEIJA && you.level >= 10)
	{
		printlog("세이자는 레벨9가 넘어간 강자를 신도로 받지 않습니다.",true,false,false,CL_small_danger);
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
	if(god == GT_SATORI)
	{
		if(you.punish[god].number)
			printlog("사토리는 당신과의 재회를 기뻐했다.",true,false,false,CL_help);
		else
			printlog("사토리의 애완동물이 되었다.",true,false,false,CL_help);	

	}
	else if(speak_)
	{
		char temp[100];
		sprintf_s(temp,100,"%s의 신도가 되었다.",GetGodString(god));	
		printlog(temp,true,false,false,CL_help);	
	}


	if(speak_)
		soundmanager.playSound("god");

	if(god == GT_SATORI)
	{
		if(you.punish[god].number)
			AddNote(you.turn,CurrentLevelString(),"사토리와 재회했다.",CL_help);
		else
			AddNote(you.turn,CurrentLevelString(),"사토리의 애완동물이 되었다.",CL_help);

	}
	else
	{
		char temp[200];
		sprintf_s(temp,200,"%s의 신도가 되었다.",GetGodString(god));
		AddNote(you.turn,CurrentLevelString(),temp,CL_help);
	}
	you.punish[god].number = 0;
	you.punish[god].punish = false;
	
	gift_count = GetGodGiftTime(god);

	GodAccpect_Entering();


	if(god == GT_SEIJA)
	{
		you.god_value[GT_SEIJA][0] = 1;
	}



	you.Ability(SKL_ABANDON_GOD,true,false);
	GetGodAbility(0, true);
	PietyUpDown(
		god == GT_MIKO ? 0 :
		(isTutorial() || god == GT_SEIJA)?160:piety_,true);
	godAutoPickUp(god, true);
	if(isTutorial())
	{
		gift_count=30;
	}



	return true;

}
bool players::StepUpDownPiety(int level_)
{
	while(level_)
	{
		int prev_ = pietyLevel(piety);
		int next_ = prev_;
		
		if((prev_ == 0 && level_ < 0) || (prev_ == 6 && level_ > 0))
			break;

		while(prev_ == next_)
		{
			PietyUpDown(level_>0?1:-1);
			next_ = pietyLevel(piety);
		}
		return true;
	}
	return false;
}
bool players::PietyUpDown(int piety_, bool absolutely_)
{
	int prev_piety_ = piety;
	int prev_ = pietyLevel(piety);
	piety = absolutely_?piety_:piety_+piety;
	if(piety<0)
		piety = 0;
	else if (piety >= 200) {
		if (prev_piety_ != 200) {
			if (you.god == GT_MIKO) {
				enterlog();
				soundmanager.playSound("spellcard");
				printlog("인기 폭발!", true, false, false, CL_miko);
			}
		}

		piety = 200;
	}
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
		if(GodGift(god,piety))
			SetInter(IT_EVENT);
		gift_count = GetGodGiftTime(god);
		return true;
	}
	return false;
}
bool players::PunishUpDown(int punish_, god_type god_ , bool absolutely_ )
{
	if(god_ == GT_NONE)
		god_ = god;
	punish[god_].number = absolutely_?punish_:punish_+punish[god_].number;
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
		
		bool kiku_ = ((*it).type >= ITM_THROW_FIRST && (*it).type < ITM_THROW_LAST && (*it).value4 == TMT_KIKU_COMPRESSER);
		
		if(!CheckSucide(you.position, target_pos_, false,kiku_?1:0 , false))
			return false;


		int type_ = 0;
		int pentan_ = s_wind?8:1;
		tanmac_type tanmac_type_ = TMT_WEAPON;
		beam_type beam_type_ = s_wind?BMT_PENETRATE:BMT_NORMAL;
		if ((*it).type == ITM_THROW_TANMAC && (*it).value4 == TMT_DOGGOJEO) {
			pentan_ = 8;
			beam_type_ = BMT_PENETRATE;
		}
		beam_infor temp_infor(GetThrowAttack(&(*it),false),GetThrowAttack(&(*it),true),GetThrowHit(&(*it)),this,GetParentType(),8,pentan_,beam_type_,ATT_THROW_NORMAL,(*it).GetNameInfor());
		if((*it).type >= ITM_THROW_FIRST && (*it).type < ITM_THROW_LAST )
		{
			tanmac_type_ = (tanmac_type)(*it).value4;
			type_ = GetTanmacGraphicType(tanmac_type_);
			temp_infor.type2 = GetTanmacAttackType(tanmac_type_);
		}
		else
		{
			if((*it).value5)
				temp_infor.type2 = GetWeapontoTanmac((weapon_brand)(*it).value5);
		}

		if(kiku_)
		{ //키쿠이치 컴프레서 전용

			int length_ = ceil(sqrt(pow((float)abs(you.position.x-target_pos_.x),2)+pow((float)abs(you.position.y-target_pos_.y),2)));
	
			temp_infor.length = length_;
			for(int i=0;i<(you.GetParadox()?2:1);i++)
			{
				soundmanager.playSound("throw");
				coord_def c_ = throwtanmac(type_,beam,temp_infor,&(*it));
				int power_ = GetSkillLevel(SKT_TANMAC, true)*5;
				attack_infor temp_att(randC(3,5+power_/8),3*(5+power_/8),99,&you,you.GetParentType(),ATT_NORMAL_BLAST,name_infor("물보라",false));
				soundmanager.playSound("bomb"); 
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
				soundmanager.playSound("shoot");
				throwtanmac(type_,beam,temp_infor,&(*it), true, (you.GetParadox()&&i==0)?true:false);
			}
		}
		you.SetParadox(0);

		doingActionDump(DACT_SHOOT, (*it).name.name);


		time_delay += GetThrowDelay((*it).type);
		if((!s_knife_collect || TanmacDeleteRand(tanmac_type_, false)) && DeleteItem(it,1))
		{
			if (throw_weapon == NULL)
			{
				list<item>::iterator it2;
				for (it2 = you.item_list.begin(); it2 != you.item_list.end(); it2++)
				{
					if ((*it2).can_throw && you.equipment[ET_WEAPON] != &(*it2))
					{
						throw_weapon = &(*it2);
						break;
					}
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
bool players::isGrazeAmulet()
{
	if (equipment[ET_NECK]) {
		if (equipment[ET_NECK]->value1 == AMT_GRAZE && getAmuletPercent() >= 100) {
			return true;
		}
	}
	return false;
}
void players::resetAmuletPercent(amulet_type type_)
{
	int level_ = level;
	if (level_ == 27)
		level_--;
	system_exp.value = (GetNeedExp(max(level_ - 1, 0)) - GetNeedExp(max(level_ - 2, 0))) + 10;
	system_exp.value *= getAmuletCharge(type_);
	system_exp.maxi = system_exp.value;
	chargingFinish(type_, -1);
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

	if(type_ == ET_ARMOR && it->type >= ITM_ARMOR_BODY_ARMOUR_2 && it->type <= ITM_ARMOR_BODY_ARMOUR_3 )
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
	if(!isImpossibeEquip(type_, true))
		return 0;


	if((*it).isRightType(type_))
	{
		if(!unequip(type_))
		{
			if (equipment[type_] && equipment[type_]->curse)
				printlog("저주에 걸려 있어서 장비를 벗을 수 없다.",true,false,false,CL_normal);
			return 0;
		}
		if(speak_)
			soundmanager.playSound("equip");
		WaitForSingleObject(mutx, INFINITE);
		//자동식별 추가
		(*it).equipIdentify();

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
		if (type_ == ET_NECK)
		{
			resetAmuletPercent((amulet_type)(*it).value1);
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
			sprintf_s(temp,2,"%c",(*it).id);
			printlog(temp,false,false,false,(*it).item_color());
			printlog(" - ",false,false,false,(*it).item_color());
			printlog((*it).GetName(),false,false,false,(*it).item_color());
			printlog(" (장착)",true,false,false,(*it).item_color());

			
			if(type_ == ET_ARMOR)
				time_delay += 5*you.GetNormalDelay();
			else if(type_ >= ET_SHIELD && type_ <= ET_BOOTS)
				time_delay += 3*you.GetNormalDelay();
			else
				time_delay += you.GetNormalDelay()/2;

			if (type_ == ET_WEAPON)
			{
				already_swap = false;
			}

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

			if (type_ == ET_SHIELD || type_ == ET_WEAPON)
			{
				if (you.equipment[ET_WEAPON] && you.equipment[ET_SHIELD])
				{
					enterlog();
					switch (shieldPanaltyOfWeapon(you.equipment[ET_WEAPON]->type, you.equipment[ET_WEAPON]->value0))
					{
					case 0:
						break;
					case 1:
						printlog("방패와 무기를 함께 착용했다. (공격속도 0.1 느려짐)", true, false, false, CL_normal);
						break;
					case 2:
						printlog("이 무기는 방패와 같이 쓰기엔 약간 불편하다. (공격속도 0.2 느려짐)", true, false, false, CL_small_danger);
						break;
					case 3:
						printlog("이 무기는 방패와 같이 쓰기엔 아주 버겁다. (공격속도 0.3 느려짐)", true, false, false, CL_danger);
						break;
					}

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
				if(equipment[ET_LEFT] && equipment[ET_RIGHT] && (!equipment[ET_LEFT]->curse && !equipment[ET_RIGHT]->curse))
				{
					char temp[2];
					changedisplay(DT_GAME);
					printlog("< 또는 ",false,false,false,CL_normal);
					sprintf_s(temp,2,"%c",equipment[ET_LEFT]->id);
					printlog(temp,false,false,false,CL_normal);
					printlog(" - ",false,false,false,CL_normal);
					printlog(equipment[ET_LEFT]->GetName(),true,false,false,equipment[ET_LEFT]->item_color());
					printlog("> 또는 ",false,false,false,CL_normal);
					sprintf_s(temp,2,"%c",equipment[ET_RIGHT]->id);
					printlog(temp,false,false,false,CL_normal);
					printlog(" - ",false,false,false,CL_normal);
					printlog(equipment[ET_RIGHT]->GetName(),true,false,false,equipment[ET_RIGHT]->item_color());
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
				else if (equipment[ET_LEFT] && equipment[ET_RIGHT]) {
					if (equipment[ET_LEFT]->curse && equipment[ET_RIGHT]->curse) {
						printlog("모든 아이템이 저주에 걸려있다.", true, false, false, CL_normal);
						return 0;
					}
					else if (equipment[ET_LEFT]->curse)
						type_ = ET_RIGHT;
					else if (equipment[ET_RIGHT]->curse)
						type_ = ET_LEFT;

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
	for(int i=0;i<RUNE_HAKUREI_ORB;i++)
	{

		if(rune[i]>0)
			goal_++;
	}

	return goal_;
}
int players::haveOrb()
{
	int goal_ = 0;

	if(rune[RUNE_HAKUREI_ORB])
		goal_++;
	return goal_;
	
}
bool players::isImpossibeEquip(equip_type type_, bool massage_)
{
	if(type_ == ET_HELMET && GetProperty(TPT_HORN) )
	{
		if(massage_)
			printlog("당신의 뿔이 이 장비를 쓰는걸 방해한다.",true,false,false,CL_normal);
		return false;
	}
	if(type_ == ET_BOOTS &&GetProperty(TPT_GHOST_FOOT) )
	{
		if(massage_)
			printlog("당신은 다리가 없다!",true,false,false,CL_normal);
		return false;
	}
	if(type_ == ET_GLOVE &&GetProperty(TPT_CLAW) )
	{
		if(massage_)
			printlog("당신의 손톱때문에 장갑을 낄 수 없다!",true,false,false,CL_normal);
		return false;
	}
	return true;
}
bool players::unequip(equip_type type_, bool force_)
{
	if(equipment[type_])
	{
		if(!force_ && equipment[type_]->curse && (type_ != ET_WEAPON || (equipment[type_]->type >= ITM_WEAPON_FIRST && equipment[type_]->type < ITM_WEAPON_LAST)))
		{
			if(!equipment[type_]->identify_curse)
				equipment[type_]->identify_curse = true;
			return false;
		}

		if (!force_ && type_ == ET_NECK && getAmuletPercent() > 0)
		{
			printlog("정말로 충전이 되어있는 부적을 벗습니까? 충전율이 사라집니다! (y/n)", true, false, false, CL_small_danger);
			bool repeat_ = true;
			while (repeat_)
			{
				switch (waitkeyinput())
				{
				case 'Y':
				case 'y':
					repeat_ = false;
					break;
				case 'N':
				case 'n':
					printlog("계속하도록. ", false, false, false, CL_normal);
					return false;
				}
			}
		}

		WaitForSingleObject(mutx, INFINITE);
		equip_stat_change(equipment[type_], type_, false);
		if(!force_)
		{
			if(type_ == ET_ARMOR)
				time_delay += 5*you.GetNormalDelay();
			else if(type_ >= ET_SHIELD && type_ <= ET_BOOTS)
				time_delay += 3*you.GetNormalDelay();
			else
				time_delay += you.GetNormalDelay()/2;
			printlog(equipment[type_]->GetName(),false,false,false,equipment[type_]->item_color());
			printarray(true,false,false,CL_normal,2,equipment[type_]->GetNameInfor().name_to(true),"벗었다.");
		}
		equipment[type_] = NULL;
		ReSetASPanlty();
		ReleaseMutex(mutx);
		if(!force_)
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
				if(equipment[i]->curse)
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
			/*if(s_spellcard && equipment[i]->isRightType(ET_NECK))
			{
				printlog("스펠카드 선언중엔 스펠카드 탈착이 불가능하다.",true,false,false,CL_normal);
				return 0;
			}*/

			if(!unequip(i))
			{
				if (equipment[i]->curse)
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
				(*it).Curse(true,ET_WEAPON);
				printlog("무기는 저주의 힘으로 가득 차있다.",true,false,false,CL_hina);	
				break;
			case WB_WEATHER	:
				printlog("무기에서 비상의 기운이 뿜어져나온다.",true,false,false,CL_tensi);	
				break;
			case WB_AUTUMN:
				printlog("무기에서 쓸쓸하고도 종말적인 기운이 느껴진다.",true,false,false,CL_autumn);	
				break;
			case WB_MANA_REGEN:
				//SetManaDelay(1);
				printlog("영력의 흐름이 느껴진다.",true,false,false,CL_white_blue);	
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
float players::GetFireResist(bool cloud_)
{
	float return_ =  1.0f;
	if(cloud_)
	{
		if(GetProperty(TPT_CLOUD) && half_youkai[1] == 0)
		{			
			return 0;
		}
	}
	if (GetProperty(TPT_FIRE_IMUNE))
	{
		return 0;
	}

	if(fire_resist <= -2)
		return_ *= 2;
	else if(fire_resist == -1)
		return_ *= 1.5f;
	else if(fire_resist == 1)
		return_ *= 0.5f;
	else if(fire_resist == 2)
		return_ *= 0.25f;
	else if(fire_resist >= 3)
		return_ *= 0.125f;


	if(GetCloudResist())
		return_ *= 0.5f;

	return return_;
}
float players::GetColdResist(bool cloud_)
{
	float return_ =  1.0f;
	if(cloud_)
	{
		if(GetProperty(TPT_CLOUD) && half_youkai[1] == 1)
		{			
			return 0;
		}		
	}
	if (GetProperty(TPT_COLD_IMUNE))
	{
		return 0;
	}
	if(ice_resist <= -2)
		return_ *= 2;
	else if(ice_resist == -1)
		return_ *= 1.5f;
	else if(ice_resist == 1)
		return_ *= 0.5f;
	else if(ice_resist == 2)
		return_ *= 0.25f;
	else if(ice_resist >= 3)
		return_ *= 0.125f;


	if(GetCloudResist())
		return_ *= 0.5f;

	return return_;
}
float players::GetElecResist(bool cloud_)
{
	float return_ =  1.0f;
	if(cloud_)
	{
		if(GetProperty(TPT_CLOUD) && half_youkai[1] == 2)
		{			
			return 0;
		}		
	}
	if (GetProperty(TPT_ELEC_IMUNE))
	{
		return 0;
	}
	if(elec_resist <= -2)
		return_ *= 2;
	else if(elec_resist == -1)
		return_ *= 1.5f;
	else if(elec_resist == 1)
		return_ *= 0.5f;
	else if(elec_resist == 2)
		return_ *= 0.25f;
	else if(elec_resist >= 3)
		return_ *= 0.125f;


	if(GetCloudResist())
		return_ *= 0.5f;

	return return_;
}
bool players::GetCloudResist()
{
	return GetProperty(TPT_CLOUD_RESIST);
}


void players::burstCloud(int kind_, int rate_)
{	
	textures *t_ = img_fog_normal;
	smoke_type smoke_ = SMT_FOG;
	switch(kind_)
	{
	case 0:
		smoke_ = SMT_FIRE;
		t_ = img_fog_fire;
		break;
	case 1:
		smoke_ = SMT_COLD;
		t_ = img_fog_cold;
		break;
	case 2:
		smoke_ = SMT_ELEC;
		t_ = img_fog_thunder;
		break;
	default:
		return;
	}

	for(int i = 0; i < rate_; i++)
	{
		dif_rect_iterator rit(you.position,4,true);
		while(!rit.end())
		{
			coord_def check_pos_ = (*rit);
					
			if(check_pos_ != you.position && env[current_level].isMove(check_pos_.x, check_pos_.y, false) && env[current_level].isInSight(check_pos_) && you.isSightnonblocked((*rit)))
			{
				env[current_level].MakeSmoke(*rit,t_,smoke_,rand_int(6,8),0,&you);
				break;
			}
			rit++;
		}
	}
}
bool players::isView(const monster* monster_info)
{
	
	if(isArena() || s_evoke_ghost)
		return false;
	if((you.s_invisible || you.togle_invisible) && 
		!(you.s_glow && you.GetBuffOk(BUFFSTAT_HALO)) &&
		!(monster_info->flag & M_FLAG_CAN_SEE_INVI)) //투명?
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