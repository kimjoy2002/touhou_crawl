//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: monster.cpp
//
// ����: ���� �Լ�����
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "monster.h"
#include "mon_infor.h"
#include "environment.h"
#include "speak.h"
#include "beam.h"
#include "save.h"
#include "god.h"
#include "skill_use.h"
#include "smoke.h"
#include "floor.h"
#include "note.h"
#include "tensi.h"
#include "map.h"
#include "rect.h"
#include "tribe.h"
#include "rand_shuffle.h"
#include "soundmanager.h"







coord_def inttodirec(int direc, int x_=0, int y_=0);
bool evoke_bomb(int power, bool short_, unit* order, coord_def target);

monster::monster() 
: map_id(-1), id(0), level(1), exper(0), name("����",true), image(NULL),  hp(0), hp_recov(0), max_hp(0), prev_position(0,0), first_position(0,0), prev_sight(false),
ac(0), ev(0), flag(0), resist(0), sense(0), dream(false), s_poison(0), poison_reason(PRT_NEUTRAL), s_tele(0), s_might(0), s_clever(0), s_haste(0), s_confuse(0), s_slow(0), s_frozen(0), s_ally(0),
s_elec(0), s_paralyse(0), s_glow(0), s_graze(0), s_silence(0), s_silence_range(0), s_sick(0), s_veiling(0), s_value_veiling(0), s_invisible(0),s_saved(0), s_mute(0), s_catch(0),
s_ghost(0),
s_fear(0), s_mind_reading(0), s_lunatic(0), s_neutrality(0), s_communication(0), s_exhausted(0),
force_strong(false), force_turn(0), s_changed(0), s_invincibility(0), debuf_boost(0),
	summon_time(0), summon_parent(PRT_NEUTRAL),poison_resist(0),fire_resist(0),ice_resist(0),elec_resist(0),confuse_resist(0),wind_resist(0), time_delay(0), 
	speed(10), memory_time(0), first_contact(true), strong(1), delay_turn(0), target(NULL), temp_target_map_id(-1), target_pos(),
	direction(0), sm_info(), state(MS_NORMAL), random_spell(false)
{	
	base_state_setup(state,MS_SLEEP);
}
void monster::SaveDatas(FILE *fp)
{	
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<int>(fp, map_id);
	SaveData<int>(fp, id);
	SaveData<int>(fp, level);
	SaveData<int>(fp, exper);
	name.SaveDatas(fp);
	SaveData<int>(fp, texturetoint(image));
	SaveData<int>(fp, hp);
	SaveData<int>(fp, hp_recov);
	SaveData<int>(fp, max_hp);
	SaveData<int>(fp, prev_position.x);
	SaveData<int>(fp, prev_position.y);
	SaveData<int>(fp, first_position.x);
	SaveData<int>(fp, first_position.y);
	SaveData<bool>(fp, prev_sight);
	SaveData<int>(fp, ac);
	SaveData<int>(fp, ev);
	for(int i=0;i<3;i++)
	{
		SaveData<int>(fp, atk[i]);
		SaveData<attack_type>(fp, atk_type[i]);
		atk_name[i].SaveDatas(fp);
	}
	SaveData<int>(fp, flag);
	SaveData<int>(fp, resist);
	SaveData<int>(fp, sense);
	SaveData<bool>(fp, dream);
	SaveData<int>(fp, s_poison);	
	SaveData<parent_type>(fp, poison_reason);
	SaveData<int>(fp, s_tele);
	SaveData<int>(fp, s_might);
	SaveData<int>(fp, s_clever);
	SaveData<int>(fp, s_haste);
	SaveData<int>(fp, s_confuse);
	SaveData<int>(fp, s_slow);
	SaveData<int>(fp, s_frozen);
	SaveData<int>(fp, s_ally);
	SaveData<int>(fp, s_elec);
	SaveData<int>(fp, s_paralyse);
	SaveData<int>(fp, s_glow);
	SaveData<int>(fp, s_graze);
	SaveData<int>(fp, s_silence);
	SaveData<int>(fp, s_silence_range);
	SaveData<int>(fp, s_sick);
	SaveData<int>(fp, s_veiling);
	SaveData<int>(fp, s_value_veiling);
	SaveData<int>(fp, s_invisible);
	SaveData<bool>(fp, s_saved);
	SaveData<int>(fp, s_mute);
	SaveData<int>(fp, s_catch);
	SaveData<int>(fp, s_ghost);
	SaveData<int>(fp, s_fear);
	SaveData<int>(fp, s_mind_reading);
	SaveData<int>(fp, s_lunatic);
	SaveData<int>(fp, s_neutrality);
	SaveData<int>(fp, s_communication);
	SaveData<int>(fp, s_exhausted);
	SaveData<bool>(fp, force_strong);
	SaveData<int>(fp, force_turn);
	SaveData<int>(fp, s_changed);
	SaveData<int>(fp, s_invincibility);
	SaveData<int>(fp, debuf_boost);
	SaveData<int>(fp, summon_time);
	SaveData<parent_type>(fp, summon_parent);
	SaveData<int>(fp, poison_resist);
	SaveData<int>(fp, fire_resist);
	SaveData<int>(fp, ice_resist);
	SaveData<int>(fp, elec_resist);
	SaveData<int>(fp, confuse_resist);
	SaveData<int>(fp, wind_resist);
	SaveData<int>(fp, time_delay);
	SaveData<int>(fp, speed);
	SaveData<int>(fp, memory_time);
	SaveData<bool>(fp, first_contact);
	SaveData<int>(fp, strong);
	SaveData<int>(fp, delay_turn);

	SaveData<int>(fp, will_move.size());

	for (int i = will_move.size(); i > 0; i--) {
		coord_def pop_ = will_move.front();
		SaveData<int>(fp, pop_.x);
		SaveData<int>(fp, pop_.y);
		will_move.pop_front();
	}
	//SaveData<int>(fp, target);  //������������
	//temp_target_map_id �� ������ ������ �ʿ䰡 ����.
	if(target)
		SaveData<int>(fp, target->GetMapId());
	else
		SaveData<int>(fp, -1);
	
	sm_info.SaveDatas(fp);
	SaveData<int>(fp, target_pos.x);
	SaveData<int>(fp, target_pos.y);
	SaveData<int>(fp, direction);
	SaveData<monster_state>(fp, state.GetState());
	SaveData<int>(fp, spell_lists.size());
	for(list<spell>::iterator it=spell_lists.begin();it!=spell_lists.end();it++)
	{
		SaveData<spell>(fp,(*it));
	}
	SaveData<bool>(fp, random_spell);	
	
	SaveData<int>(fp, item_lists.size());
	for(auto it=item_lists.begin();it!=item_lists.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	
}
void monster::LoadDatas(FILE *fp)
{
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<int>(fp, map_id);
	LoadData<int>(fp, id);
	LoadData<int>(fp, level);
	LoadData<int>(fp, exper);
	name.LoadDatas(fp);
	int it;
	LoadData<int>(fp, it);
	image = inttotexture(it);
	LoadData<int>(fp, hp);
	LoadData<int>(fp, hp_recov);
	LoadData<int>(fp, max_hp);
	LoadData<int>(fp, prev_position.x);
	LoadData<int>(fp, prev_position.y);
	LoadData<int>(fp, first_position.x);
	LoadData<int>(fp, first_position.y);
	LoadData<bool>(fp, prev_sight);
	LoadData<int>(fp, ac);
	LoadData<int>(fp, ev);
	for(int i=0;i<3;i++)
	{
		LoadData<int>(fp, atk[i]);
		LoadData<attack_type>(fp, atk_type[i]);
		atk_name[i].LoadDatas(fp);
	}
	LoadData<int>(fp, flag);
	LoadData<int>(fp, resist);
	LoadData<int>(fp, sense);
	LoadData<bool>(fp, dream);
	LoadData<int>(fp, s_poison);
	LoadData<parent_type>(fp, poison_reason);
	LoadData<int>(fp, s_tele);
	LoadData<int>(fp, s_might);
	LoadData<int>(fp, s_clever);
	LoadData<int>(fp, s_haste);
	LoadData<int>(fp, s_confuse);
	LoadData<int>(fp, s_slow);
	LoadData<int>(fp, s_frozen);
	LoadData<int>(fp, s_ally);
	LoadData<int>(fp, s_elec);
	LoadData<int>(fp, s_paralyse);
	LoadData<int>(fp, s_glow);
	LoadData<int>(fp, s_graze);
	LoadData<int>(fp, s_silence);
	LoadData<int>(fp, s_silence_range);
	LoadData<int>(fp, s_sick);
	LoadData<int>(fp, s_veiling);
	LoadData<int>(fp, s_value_veiling);
	LoadData<int>(fp, s_invisible);
	LoadData<bool>(fp, s_saved);
	LoadData<int>(fp, s_mute);	
	LoadData<int>(fp, s_catch);
	LoadData<int>(fp, s_ghost);
	LoadData<int>(fp, s_fear);
	LoadData<int>(fp, s_mind_reading);
	LoadData<int>(fp, s_lunatic);
	LoadData<int>(fp, s_neutrality);
	LoadData<int>(fp, s_communication);
	LoadData<int>(fp, s_exhausted);
	LoadData<bool>(fp, force_strong);
	LoadData<int>(fp, force_turn);
	LoadData<int>(fp, s_changed);
	LoadData<int>(fp, s_invincibility);
	LoadData<int>(fp, debuf_boost);
	LoadData<int>(fp, summon_time);
	LoadData<parent_type>(fp, summon_parent);
	LoadData<int>(fp, poison_resist);
	LoadData<int>(fp, fire_resist);
	LoadData<int>(fp, ice_resist);
	LoadData<int>(fp, elec_resist);
	LoadData<int>(fp, confuse_resist);
	LoadData<int>(fp, wind_resist);
	LoadData<int>(fp, time_delay);
	LoadData<int>(fp, speed);
	LoadData<int>(fp, memory_time);
	LoadData<bool>(fp, first_contact);
	LoadData<int>(fp, strong);
	LoadData<int>(fp, delay_turn);



	int size_ = 0;
	LoadData<int>(fp, size_);

	for (int i = size_; i > 0; i--) {
		coord_def pop_;
		LoadData<int>(fp, pop_.x);
		LoadData<int>(fp, pop_.y);
		will_move.push_back(pop_);
	}
	//LoadData<int>(fp, will_move);
	//LoadData<int>(fp, target); Ÿ�� ������ ���⼭ ȣ������ �ʴ´�.
	LoadData<int>(fp, temp_target_map_id);
	sm_info.LoadDatas(fp);


	LoadData<int>(fp, target_pos.x);
	LoadData<int>(fp, target_pos.y);
	LoadData<int>(fp, direction);
	base_state_setup(state,MS_NORMAL);
	monster_state ms_;
	LoadData<monster_state>(fp, ms_);
	state.SetState(ms_);
	size_=0;
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		spell temp;
		LoadData<spell>(fp, temp);
		spell_lists.push_back(temp);
	}
	LoadData<bool>(fp, random_spell);	
	
	size_=0;
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		item_infor temp;
		temp.LoadDatas(fp);
		item_lists.push_back(temp);
	}
}
void monster::ReTarget()
{

}
void monster::init()
{ 
	map_id=-1;
	id=0;
	level=1;
	exper=0;
	image = NULL;
	hp = 0;
	hp_recov =0;
	max_hp=0;
	prev_position.x = 0;
	prev_position.y = 0;
	first_position.x = 0;
	first_position.y = 0;
	prev_sight = false;
	ac = 0;
	ev = 0;
	flag = 0;
	resist = 0;
	sense = 0; 
	dream = false;
	s_poison = 0;
	poison_reason = PRT_NEUTRAL;
	s_tele = 0;
	s_might = 0;
	s_clever = 0;
	s_haste = 0;
	s_confuse = 0;
	s_slow = 0;
	s_frozen = 0;
	s_ally = 0;
	s_elec = 0;
	s_paralyse = 0;
	s_glow = 0;
	s_graze = 0;
	s_silence = 0;
	s_silence_range = 0;
	s_sick = 0;
	s_veiling = 0;
	s_value_veiling = 0;
	s_invisible = 0;
	s_saved= false;
	s_mute = 0;
	s_catch = 0;
	s_ghost = 0;
	s_fear=0;
	s_mind_reading =0;
	s_lunatic=0;
	s_neutrality=0;
	s_communication=0;
	s_exhausted=0;
	force_strong=false;
	force_turn=0;
	s_changed = 0;
	s_invincibility = 0;
	debuf_boost = 0;
	summon_time = 0;
	summon_parent = PRT_NEUTRAL;
	poison_resist = 0;
	fire_resist = 0;
	ice_resist = 0;
	elec_resist = 0;
	confuse_resist = 0;
	wind_resist = 0;
	time_delay = 0;
	speed = 0; 
	memory_time = 0; 
	first_contact = true;
	strong = 1;
	delay_turn = 0;
	while(!will_move.empty())
		will_move.pop_back();
	target = NULL;
	temp_target_map_id = -1;
	target_pos.x = 0;
	target_pos.y = 0;
	direction =0;
	state.SetState(MS_SLEEP);
	spell_lists.clear();
	random_spell = false;
	item_lists.clear();
}
bool monster::SetMonster(int map_num_, int map_id_, int id_, int flag_, int time_, coord_def position_, bool init_)
{
	if(id_ < 0 || id_ > MON_MAX)
		return false;
	if(position_.x<0 || position_.x > DG_MAX_X || position_.y <0 || position_.y >DG_MAX_Y)
		return false;

	if(init_)
		init();
		
	map_id = map_id_;
	id = mondata[id_].id;
	level  = mondata[id_].level;
	exper = mondata[id_].exper;
	if (isSprint()) {
		exper *= sprintMulti();
	}
	name = mondata[id_].name;
	image = mondata[id_].image;
	hp = mondata[id_].max_hp;
	max_hp = mondata[id_].max_hp;
	ac = mondata[id_].ac;
	ev = mondata[id_].ev;
	speed = mondata[id_].speed;
	flag = mondata[id_].flag | flag_;
	resist = mondata[id_].resist;
	sense = mondata[id_].sense;
	for(int i=0;i<3;i++)
	{
		atk[i] = mondata[id_].atk[i];
		atk_type[i] = mondata[id_].atk_type[i];
		atk_name[i] = mondata[id_].atk_name[i];
	}
	if(init_)
	{
		summon_time = time_;
		direction = rand_int(0,7);
		if(flag & M_FLAG_SUMMON)
		{
			if(flag & M_FLAG_LEADER_SUMMON)
				state.SetState(MS_FOLLOW);
			else
				state.SetState(MS_ATACK);
		}
		SetXY(map_num_, position_.x, position_.y);
		first_position = position_;
		if(flag & M_FLAG_ALLY)
		{
			s_ally = -1;
			state.SetState(MS_FOLLOW);
		//	if(env[current_level].isInSight(position))
		//		CheckSightNewTarget();
		}
		if(flag & M_FLAG_EVENT)
		{
			target = &you;
			target_pos = you.position;
			state.SetState(MS_ATACK);
		}
		if(flag & M_FLAG_NETURALY)
		{
			s_neutrality = 1;
		}
		if (flag & M_FLAG_NONE_MOVE && flag & M_FLAG_UNHARM)
		{
			env[map_num_].dgtile[position_.x][position_.y].flag |= FLAG_BLOCK;
		}


	}
	SetResistMonster(this);

	if(flag & M_FLAG_CONFUSE)
		s_confuse = 10;
	if(flag & M_FLAG_INVISIBLE)
		s_invisible = -1;
	
	SetSpell((monster_index)id_, this,&item_lists,&random_spell);
	return true;
}	
bool monster::ChangeMonster( int id_, int flag_)
{
	float hp_per_ = (float)(hp) / max_hp;
	bool summon_ = (flag & M_FLAG_SUMMON)?true:false;
	SetMonster(current_level,map_id,id_,flag_,summon_time,position,false);
	if(summon_)
		flag |= M_FLAG_SUMMON;
	if(flag & M_FLAG_ALLY)
	{
		s_ally = -1;
		state.SetState(MS_FOLLOW);
	}
	hp = hp_per_ * max_hp;
	return true;
}
void monster::FirstContact()
{
	if(!first_contact)
		return;
	if(id == MON_TEWI)
	{
		map_list.bamboo_tewi = true;
	}
	if(!(flag & M_FLAG_SUMMON))
	{
		GodAccpect_First_contact();
		if(you.god == GT_SATORI && !you.GetPunish(GT_SATORI) && pietyLevel(you.piety)>=2  &&  id != MON_KOISHI)
		{
			int num_ = rand_int(1,pietyLevel(you.piety)-1);
			int max_size_ = 8;
			int min_size_ = 4;
			int percent_ = 80;
			for(int i=0;i<num_;i++)
			{
				int max_ = 10000;
				while(max_)
				{
					int x_ = randA(DG_MAX_X - 1);
					int y_ = randA(DG_MAX_Y - 1);
					if(env[current_level].isMove(x_,y_,isFly(), isSwim(), flag & M_FLAG_CANT_GROUND))
					{ //fly�� swim�� �� ĳ���� �������� �Ǿ��ִ°� �� ĳ���Ͱ� �������ִ� ��ġ����. ��°�
						env[current_level].MakeMapping(coord_def(x_,y_),rand_int(min_size_,max_size_),false,percent_);
						break;
					}
					max_--;
				}
			}
			
		}
	}
	if(wiz_list.wizard_mode == 1)
	{		
		char temp[200];
		float percent_=1.0f, detect_ = you.GetStealth()==-1?1.0f:((float)GetDetect()+1)/(you.GetStealth()+1);
		if(detect_<0 || detect_>1.0f)
			detect_ = 1.0f;
		int length__ = max(abs(you.position.x-position.x),abs(you.position.y-position.y));
		for(int i = 0; i < length__; i++)
			percent_ *= 1.0f-detect_;
		sprintf_s(temp,200,"��ųȮ��-RandB(%d,%d) ��%f%% (���� �ϻ� ������%f%%)",you.GetStealth(),GetDetect(),100.0f*detect_, percent_*100.0f);
		printlog(temp,true,false,false,CL_danger);
	}
	if(flag & M_FLAG_UNIQUE && !(flag & M_FLAG_SUMMON) && id != MON_ENSLAVE_GHOST )
	{		
		char temp[200];
		sprintf_s(temp,200,"���ӵ� %s%s �߰��ߴ�.",name.name.c_str(),name.name_to());
		AddNote(you.turn,CurrentLevelString(),temp,CL_normal);
	}
	first_contact = false;
}
void monster::TurnSave()
{
	delay_turn = you.turn;
}
void monster::TurnLoad()
{ //���߿� ���ΰ� ��ó�� �Űܿ��°͵� �����Ѵ�.
	int temp_turn = you.turn-delay_turn;
	if(s_poison-temp_turn>0)
		s_poison-=temp_turn;
	else
		s_poison = 0;

	if(s_might-temp_turn>0)
		s_might-=temp_turn;
	else
		s_might = 0;

	if (s_clever - temp_turn > 0)
		s_clever -= temp_turn;
	else
		s_clever = 0;

	if(s_tele-temp_turn>0)
		s_tele-=temp_turn;
	else
		s_tele = 0;

	if(s_haste-temp_turn>0)
		s_haste-=temp_turn;
	else
		s_haste = 0;

	if(s_confuse-temp_turn>0)
		s_confuse-=temp_turn;
	else
		s_confuse = 0;

	if(s_slow-temp_turn>0)
		s_slow-=temp_turn;
	else
		s_slow = 0;

	if(s_frozen-temp_turn>0)
		s_frozen-=temp_turn;
	else
		s_frozen = 0;
	
	if(s_ally != -1 )
	{
		if(s_ally-temp_turn>0)
			s_ally-=temp_turn;
		else
			s_ally = 0;
	}
	

	if(s_elec-temp_turn>0)
		s_elec-=temp_turn;
	else
		s_elec = 0;

	if(s_paralyse-temp_turn>0)
		s_paralyse-=temp_turn;
	else
		s_paralyse = 0;

	if(s_glow-temp_turn>0)
		s_glow-=temp_turn;
	else
		s_glow = 0;

	if(s_graze-temp_turn>0)
		s_graze-=temp_turn;
	else
		s_graze = 0;

	if(s_sick-temp_turn>0)
		s_sick-=temp_turn;
	else
		s_sick = 0;

	

	if(s_silence)
	{
		s_silence-=temp_turn;
		if(s_silence<=0)
		{		
			env[current_level].MakeSilence(position, s_silence_range, false);
			s_silence=0;
			s_silence_range = 0;
		}
		else if((s_silence-5)/2 < s_silence_range)
		{
			env[current_level].MakeSilence(position, s_silence_range, false);
			s_silence_range = (s_silence-5)/2 >0 ? (s_silence-5)/2 : 0;
			env[current_level].MakeSilence(position, s_silence_range, true);
		}
	}
	if(s_veiling-temp_turn>0)
		s_veiling-=temp_turn;
	else
		s_veiling = 0;

	if(s_invisible-temp_turn>0)
		s_invisible-=temp_turn;
	else if(s_invisible>0)
		s_invisible = 0;

	if(s_mute-temp_turn>0)
		s_mute-=temp_turn;
	else
		s_mute =0;

	if (s_fear != -1) {
		if (s_fear - temp_turn > 0)
			s_fear -= temp_turn;
	else
			s_fear = 0;
	}

	if(s_ghost-temp_turn>0)
		s_ghost-=temp_turn;
	else
		s_ghost =0;
	
	if(s_lunatic-temp_turn>0)
		s_lunatic-=temp_turn;
	else
		s_lunatic =0;
	
	if(s_communication-temp_turn>0)
		s_communication-=temp_turn;
	else
		s_communication =0;

	if(s_exhausted-temp_turn>0)
		s_exhausted-=temp_turn;
	else if(s_exhausted > 0)
		s_exhausted =0;
	
	if(force_turn-temp_turn>0)
		force_turn-=temp_turn;
	else
		force_turn =0;

	//s_changed �а��� �ٸ� ���� �����͵� �ð� ������ �ȵǰ�(ó���� ����)

	if (s_invincibility != -1)
	{
		if (s_invincibility - temp_turn > 0)
			s_invincibility -= temp_turn;
		else
			s_invincibility = 0;
	}

	if(flag & M_FLAG_CONFUSE)
		s_confuse = 10;

	if(!s_sick)
		HpRecover(temp_turn);
	if(flag & M_FLAG_SUMMON && summon_time>=0)
	{
		summon_time -= temp_turn;
		if(summon_time<0)
			summon_time = 0;
		if(summon_time<=0)
			hp = 0;
	}
}
void monster::SetX(int x_)
{
	SetXY(x_, position.y);
}
void monster::SetY(int y_)
{
	SetXY(position.x, y_);
}
void monster::SetXY(int x_, int y_)
{
	SetXY(current_level, x_, y_);
}
void monster::SetXY(int map_num_, int x_, int y_)
{
	if(position.x == x_ && position.y == y_)
		return;
	if(s_silence)
		env[map_num_].MakeSilence(position, s_silence_range, false);
	if(s_catch)
		you.SetCatch(NULL);

	if (flag & M_FLAG_NONE_MOVE && flag & M_FLAG_UNHARM)
	{
		env[map_num_].dgtile[position.x][position.y].flag &= ~FLAG_BLOCK;
	}


	position.set(x_,y_);
	for(auto it = env[map_num_].floor_list.begin(); it != env[map_num_].floor_list.end();it++)
	{
		if(it->position == position)
			it->onWalk(this);
	}
	if(s_silence)
		env[map_num_].MakeSilence(position, s_silence_range, true);

	if (flag & M_FLAG_NONE_MOVE && flag & M_FLAG_UNHARM)
	{
		env[map_num_].dgtile[position.x][position.y].flag |= FLAG_BLOCK;
	}

}
void monster::SetXY(coord_def pos_)
{
	SetXY(pos_.x,pos_.y);
}
char monster::getAsciiDot() 
{
	if (id < 0)
		return '?';
	return mondata[id].dot;
}
void monster::LevelUpdown(int level_, float hp_, float atk_)
{

	//�����ٿ��� ���߿� �����غ���.
	if(level_ <= 0)
		return;
	while(level_>0)
	{
		level++;
		int up_hp_ = hp_+rand_float(0,0.99f);
		int up_atk_ = atk_+rand_float(0,0.99f);

		hp+=up_hp_;
		max_hp+=up_hp_;

		for(int i = 0; i<3;i++)
		{
			if(mondata[id].atk[i])
			{
				atk[i] += up_atk_;
			}
		}
		level_--;
	}

}
void monster::FoundTarget(unit* unit_, int time_)
{
	target = unit_;
	memory_time = time_;
	target_pos = unit_->position;
	state.StateTransition(MSI_FOUND);
}
int monster::FoundTime()
{
	return (flag & M_FLAG_SHIELD) ? 10 : 30;
}
void monster::CheckSightNewTarget()
{
	if(isUserAlly())
	{		
		if(target && !target->isplayer())
		{//���� �̹� �ִ� ���
			if(target->isLive() && isEnemyMonster((monster*)target))
				return;	//�ش����� �����ʾ����鼭 �������̸� ���� �ٲ� �ʿ䰡 ����. 
		}

					
		{ //������� �þ߳� ����ã�� ����

			vector<monster>::iterator it;
			it = env[current_level].mon_vector.begin();
			for(int i=0;i<MON_MAX_IN_FLOOR && it != env[current_level].mon_vector.end() ;i++,it++)
			{
				if((*it).isLive() && isEnemyMonster(&(*it)) && (*it).isView(this) && ((env[current_level].isInSight((*it).position, true) && (flag & M_FLAG_SUMMON) ) || isMonsterSight((*it).position)) 
					&& !((*it).flag & M_FLAG_UNHARM))
				{
					if(!(flag & M_FLAG_SUMMON) || env[current_level].isInSight(position, true) )
					{
						FoundTarget(&(*it), FoundTime());
						break;
					}
				}
			}
		}
	}
	else
	{
		unit* prev_target_ = target;
		int distant_ = 999;//���϶� �Ÿ��� �߿��ϴ�.
		if(target)
		{//���� �̹� �ִ� ���
			if(!target->isplayer())
			{
				if(target->isLive() && isEnemyMonster((monster*)target))
				{
					distant_ = distan_coord(target->position, position);	//�ش����� �����ʾ����鼭 �������̸� ���� �ٲ� �ʿ䰡 ����. 
					distant_ = max(1,distant_-1); //������ ���������� �켱������ ������ �����ϱ�
				}
				else
					prev_target_ = NULL;
			}
			else
			{
				distant_ = distan_coord(target->position, position);
				distant_ = max(s_lunatic?2:1,distant_-(s_lunatic?1:30));
			}
		}

		{ //������� �þ߳� ����ã�� ����
			vector<monster>::iterator it;
			it = env[current_level].mon_vector.begin();
			for(int i=0;i<MON_MAX_IN_FLOOR && it != env[current_level].mon_vector.end() ;i++,it++)
			{
				if((*it).isLive() && &(*it) != this && isEnemyMonster(&(*it))  && (*it).isView(this) && isMonsterSight((*it).position) )
				{

					
					int check_dis_ = distan_coord(it->position, position);
					if((*it).id == MON_FAKE_HOURAI || (*it).id == MON_HOURAI )
						check_dis_ = max(s_lunatic?1:0,check_dis_-(s_lunatic?1:30));


					if(check_dis_ <= distant_)
					{
						prev_target_ = &(*it);
						distant_ = check_dis_;
					}
				}
			}
		}



		if(env[current_level].isInSight(position, true) && you.isView(this) && !you.s_timestep)
		{
			if(state.GetState() == MS_ATACK ||  you_detect())
			{
				int temp = max(s_lunatic?1:0,distan_coord(you.position, position)-(s_lunatic?0:30)+(isSightnonblocked(you.position)?0:60));
				if(distant_ == 999 || temp  < distant_)
				{
					prev_target_ = &you;
					distant_ = distan_coord(you.position, position)-3;
				}
			}
		}

		if(prev_target_ && isMonsterSight(prev_target_->position))
			FoundTarget(prev_target_, FoundTime());
	}
}
bool monster::ReturnEnemy()
{
	if(s_ally == 0)
		return false;
	
	s_ally = 0;
	flag &= ~M_FLAG_ALLY;
	return true;
}
const name_infor* monster::GetName()
{
	if((!env[current_level].isInSight(position) || !isView()) && you.hp > 0)
		return &string_that;
	return &name;
}
const string* monster::GetNameString()
{
	if(!isView())
		return &(string_that.name);
	return &(name.name);
}
bool monster::isFly()
{
	return (flag & M_FLAG_FLY);
}
bool monster::isSwim()
{
	return (flag & M_FLAG_SWIM);
}
int monster::calculate_damage(attack_type &type_, int atk, int max_atk, int back_stab)
{
	int damage_ = back_stab==3?max_atk:back_stab>=1?max(randA(max_atk),atk):atk;

	int bonus_damage = 0;

	switch(type_)
	{
	case ATT_NORMAL:
	case ATT_SPEAR:
	case ATT_NOISE:
	case ATT_FIRE:
	case ATT_FIRE_WEAK:
	case ATT_COLD:
	case ATT_COLD_WEAK:
	case ATT_ELEC:
	case ATT_ELEC_WEAK:
	case ATT_S_POISON:
	case ATT_M_POISON:
	case ATT_SICK:
	case ATT_THROW_NORMAL:
	case ATT_VAMP:
	case ATT_LUNATIC:
	case ATT_SLEEP:
	case ATT_CURSE:
	case ATT_WEATHER:
	case ATT_AUTUMN:
	case ATT_CHOAS:
	case ATT_CLOUD_NORMAL:
	case ATT_CLOUD_CURSE:
	case ATT_VEILING:
	case ATT_RUSH:
	case ATT_WALL:
	case ATT_PSYCHO:
	case ATT_NORMAL_HIT:
	case ATT_NORMAL_BLAST:
	case ATT_FIRE_BLAST:
	case ATT_COLD_BLAST: 
	case ATT_ELEC_BLAST:
	case ATT_POISON_BLAST:
	case ATT_FIRE_PYSICAL_BLAST:
	case ATT_COLD_PYSICAL_BLAST: 
	case ATT_THROW_FIRE:
	case ATT_THROW_COLD:
	case ATT_THROW_WATER:
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
	default:
		damage_ -= randA(ac);
		if(damage_<0)
			damage_ = 0;
		break;
	case ATT_AC_REDUCE_BLAST:
		damage_ -= randA(ac/2);
		if(damage_<0)
			damage_ = 0;
		break;
	case ATT_SUN_BLAST:
	case ATT_CLOUD_FIRE:
	case ATT_CLOUD_COLD:
	case ATT_CLOUD_ELEC:
	case ATT_THROW_NONE_MASSAGE:
	case ATT_THROW_NONE_DAMAGE:
	case ATT_STONE_TRAP:
	case ATT_SMITE:
	case ATT_SMASH:
	case ATT_BLOOD:
	case ATT_BURST:
	case ATT_DROWNING:
		break;
	}
	switch(type_)
	{
	case ATT_FIRE:
	case ATT_FIRE_WEAK:
		bonus_damage = damage_ / 3;
		damage_ -= bonus_damage;
		bonus_damage *= GetFireResist();
		break;
	case ATT_COLD:
	case ATT_COLD_WEAK:
		bonus_damage = damage_ / 3;
		damage_ -= bonus_damage;
		bonus_damage *= GetColdResist();
		break;
	case ATT_ELEC:
	case ATT_ELEC_WEAK:
		bonus_damage = damage_ / 3;
		damage_ -= bonus_damage;
		bonus_damage *= GetColdResist();
		break;
	case ATT_WEATHER:
		type_ = GetWeatherType(this, damage_, bonus_damage);
		break;
	}
	damage_ += bonus_damage;

	switch(type_)
	{
	case ATT_THROW_FIRE:
	case ATT_FIRE_BLAST:
		damage_ *= GetFireResist();
		break;
	case ATT_CLOUD_FIRE:
		damage_ *= GetFireResist(true);
		break;
	case ATT_THROW_COLD:
	case ATT_THROW_FREEZING:
	case ATT_COLD_BLAST: 
		damage_ *= GetColdResist();
		break;
	case ATT_CLOUD_COLD:
		damage_ *= GetColdResist(true);
		break;
	case ATT_THROW_ELEC:
	case ATT_ELEC_BLAST:
		damage_ *= GetElecResist();
		break;
	case ATT_CLOUD_ELEC:		
		damage_ *= GetElecResist(true);
		break;
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
	case ATT_POISON_BLAST:
		damage_ *= GetPoisonResist()>0?0.5:(GetPoisonResist()<0?1.5:1);
		break;
	case ATT_FIRE_PYSICAL_BLAST:
		damage_ = damage_/2.0f + damage_*GetFireResist()/2.0f;
		break;
	case ATT_COLD_PYSICAL_BLAST:
		damage_ = damage_/2.0f + damage_*GetColdResist()/2.0f;
		break;
	case ATT_CLOUD_NORMAL:
		damage_ *= GetCloudResist()?0.0f:1.0f;
		break;
	case ATT_CLOUD_CURSE:
		break;
	}
	return damage_;
}
void monster::print_damage_message(attack_infor &a, bool back_stab)
{
	name_infor name_;
	if(a.order)
		name_ = (*a.order->GetName());


	if(!back_stab)
	{
		switch(a.type)
		{
		case ATT_NORMAL:
		case ATT_SPEAR:
		case ATT_S_POISON:
		case ATT_M_POISON:
		case ATT_SICK:
		case ATT_VAMP:
		case ATT_LUNATIC:
		case ATT_CURSE:
		case ATT_WEATHER:
		case ATT_AUTUMN:
		case ATT_CHOAS:
		case ATT_THROW_NORMAL:
		case ATT_THROW_FIRE:
		case ATT_THROW_COLD:
		case ATT_THROW_WATER:
		case ATT_THROW_FREEZING:
		case ATT_THROW_WEAK_POISON:
		case ATT_THROW_MIDDLE_POISON:
		case ATT_THROW_STRONG_POISON:
		case ATT_THROW_NONE_DAMAGE:
		default:
			if(a.order)
				printarray(false,false,false,CL_normal,6,name_.name.c_str(),"�� ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),"���� �����ߴ�. ");
			break;
		case ATT_SLEEP:
			if (state.GetState() != MS_SLEEP)
			{
				if (a.order)
				{
					printarray(false, false, false, CL_normal, 6, name_.name.c_str(), "�� ", a.name.name.c_str(), a.name.name_is(true), GetName()->name.c_str(), "���� �����ߴ�. ");
					
				}
			}
			else
			{
				if (a.order)
				{
					printarray(false, false, false, CL_normal , 4, name_.name.c_str(), name_.name_is(true), GetName()->name.c_str(), "�� ���� �Ծ���. ");
				}
			}
			break;
		case ATT_FIRE:
		case ATT_FIRE_WEAK:
			if(a.order)
				printarray(false,false,false,CL_normal,6,name_.name.c_str(),"�� ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),"���� �����ϰ� ��Ÿ�ö���. ");
			break;
		case ATT_COLD:
		case ATT_COLD_WEAK:
			if(a.order)
				printarray(false,false,false,CL_normal,6,name_.name.c_str(),"�� ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),"���� �����ϰ� ���پ���. ");
			break;
		case ATT_NORMAL_HIT:			
			if(a.order)
				printarray(false,false,false,CL_normal,6,name_.name.c_str(),"�� ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),"���� ����. ");
			break;
		case ATT_SMITE:
			if(a.order)
			{
				printarray(false,false,false,CL_normal,4,"�����ΰ� ",GetName()->name.c_str(),GetName()->name_to(true),"��Ÿ�ߴ�. ");
			}
			break;
		case ATT_SMASH:
			if (a.order)
			{
				printarray(false, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "��������� �ٴڿ� ���ذ�������. ");
			}
			break;
		case ATT_BLOOD:	
			if(a.order)
			{
				printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"�� �ǰ� �������Դ�. ");
			}
			break;
		case ATT_NOISE:
			if(a.order)
			{
				printarray(false,false,false,CL_normal,3,"������ ",GetName()->name.c_str(),"�� �����̰��� ��Ÿ�ߴ�. ");
			}
			break;
		case ATT_CLOUD_FIRE:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"ȭ���� �۽ο���. ");
			break;
		case ATT_CLOUD_COLD:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���پ���. ");
			break;		
		case ATT_CLOUD_ELEC:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�����Ǿ���. ");
			break;				
		case ATT_STONE_TRAP:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"������ ������ ��Ҵ�. ");
			break;			
		case ATT_FIRE_BLAST:
		case ATT_COLD_BLAST: 
		case ATT_NORMAL_BLAST:
		case ATT_AC_REDUCE_BLAST:
		case ATT_FIRE_PYSICAL_BLAST:
		case ATT_ELEC_BLAST:
		case ATT_POISON_BLAST:
			if(a.order)
			{
				printarray(false,false,false,CL_normal,4,GetName()->name.c_str(),GetName()->name_is(true),a.name.name.c_str(),"�� ���߿� �ָ��ȴ�. ");
			}
			break;
		case ATT_SUN_BLAST:
			if (a.order)
			{
				printarray(false, false, false, CL_normal, 4, GetName()->name.c_str(), GetName()->name_is(true), a.name.name.c_str(), "�� ���� Ÿ����. ");
			}
			break;
		case ATT_COLD_PYSICAL_BLAST:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"������ �ָ��ȴ�. ");
			break;			
		case ATT_BURST:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�����ߴ�. ");
			break;
		case ATT_CLOUD_NORMAL:
		case ATT_CLOUD_CURSE:
			break;
		case ATT_VEILING:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�ٶ� ���ʿ� ������. ");
			break;
		case ATT_RUSH:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�¾Ҵ�. ");
			break;
		case ATT_WALL:			
			if(a.order)
			{
				printarray(false,false,false,CL_normal,5,GetName()->name.c_str(),GetName()->name_is(true),name_.name.c_str(),name_.name_and(true),"�ε�����. ");
			}
			else
			{
				printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� �ε�����. ");
			}
			break;
		case ATT_PSYCHO:
			printarray(false, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "�ٴڿ� ���ذ�������. ");
			break;
		case ATT_ELEC:
		case ATT_ELEC_WEAK:
			if (a.order)
				printarray(false, false, false, CL_normal, 6, name_.name.c_str(), "�� ", a.name.name.c_str(), a.name.name_is(true), GetName()->name.c_str(), "���� �����ϰ� �����Ǿ���. ");
			break;
		case ATT_THROW_ELEC:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�����Ǿ���. ");
			break;
		case ATT_DROWNING:
			printarray(false, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "���� ������. ");
			break;
		case ATT_THROW_NONE_MASSAGE:
			break;
		}
	}
	else
	{
		if(a.order)
		{
			if(a.type == ATT_SLEEP && state.GetState() == MS_SLEEP)
			{
				printarray(false, false, false, CL_normal , 4, name_.name.c_str(), name_.name_is(true), GetName()->name.c_str(), "�� ���� �Ծ���. ");
				return;
			}
			switch(a.order->GetAttackType())
			{	
			case AWT_SHORTBLADE:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"�ڿ��� ��վ���. ");
				break;
			case AWT_LONGBLADE:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"�ڿ��� �߶�´�. ");
				break;
			case AWT_MACE:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"�ڿ��� �����ƴ�. ");
				break;
			case AWT_AXE:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"�ڿ��� �����. ");
				break;
			case AWT_SPEAR:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),name.name.c_str(),name.name_to(true),"�ڿ��� ��վ���. ");
				break;
			case AWT_UNARMOUR:
			case AWT_NONE:
			default:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"�ڿ��� ����ߴ�. ");
				break;
			}
		}
	}
}

void monster::print_no_damage_message(attack_infor &a)
{
	switch(a.type)
	{
	case ATT_NORMAL:
	case ATT_SPEAR:
	case ATT_FIRE:
	case ATT_FIRE_WEAK:
	case ATT_COLD:
	case ATT_COLD_WEAK:
	case ATT_ELEC:
	case ATT_ELEC_WEAK:
	case ATT_S_POISON:
	case ATT_M_POISON:
	case ATT_LUNATIC:
	case ATT_SLEEP:
	case ATT_SICK:
	case ATT_VAMP:
	case ATT_CURSE:
	case ATT_WEATHER:
	case ATT_AUTUMN:
	case ATT_CHOAS:
	case ATT_THROW_NORMAL:
	case ATT_THROW_FIRE:
	case ATT_THROW_COLD:
	case ATT_THROW_WATER:
	case ATT_THROW_FREEZING:
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
	case ATT_THROW_ELEC:
	case ATT_NORMAL_HIT:	
	default:
		printlog("�׷��� �ƹ��� �������� ���� ���ߴ�",true,false,false,CL_normal);
		break;
	case ATT_CLOUD_FIRE:
	case ATT_CLOUD_COLD:
	case ATT_CLOUD_ELEC:
	case ATT_CLOUD_NORMAL:
	case ATT_CLOUD_CURSE:
	case ATT_PSYCHO:
	case ATT_VEILING:
	case ATT_RUSH:
	case ATT_WALL:
	case ATT_THROW_NONE_MASSAGE:
	case ATT_THROW_NONE_DAMAGE:
	case ATT_STONE_TRAP:
		break;
	}
}

bool monster::damage(attack_infor &a, bool perfect_)
{
	int back_stab = 0;
	if(a.type < ATT_THROW_NORMAL)
	{ //�齺�Ƿ���  3-�ƽ������� 2-������ ũ�������� 1-���� �幮 ũ��������
		if(state.GetState() == MS_SLEEP || state.GetState() == MS_REST)
			back_stab = 3;
		else if(s_confuse || s_fear || s_paralyse)
			back_stab = 2;
		else if(a.order && !(a.order)->isView(this))
		{ //�����϶� ����
			back_stab = 2;
		}		
		else if(s_lunatic)
			back_stab = 1;

	}
	if(a.type == ATT_AUTUMN && back_stab == 0)
	{
		if(a.order && a.order->isplayer())
		{
			if(you.equipment[ET_WEAPON] && you.equipment[ET_WEAPON]->type == ITM_WEAPON_SHORTBLADE )
			{
				back_stab = 1;
			}
		}
	}
	if(back_stab<=1 && GetMindReading() && a.order == &you)
		back_stab = 2; //���Ľ� �Ͻ�����
	if(back_stab == 2 && randA(3))
		back_stab = 0; //75%�� Ȯ���� 2���� �Ͻ��� ����
	if(back_stab == 1 && randA(9))
		back_stab = 0; //90% 1���� �Ͻ��� ����

	bool player_joon_punch_ = false;

	if (/*a.type < ATT_THROW_NORMAL &&*/ a.order && a.order->isplayer() && you.god == GT_JOON_AND_SION && !you.GetPunish(GT_JOON_AND_SION)
		&& you.god_value[GT_JOON_AND_SION][0] == 1 && pietyLevel(you.piety) >= 2 &&
		you.power >= 10 )
	{
		//������ �̾��µ� ������
		player_joon_punch_ = true;
	}

	if (player_joon_punch_)
	{
		//�ҿ� ������ �ν�Ʈ 1.3~1.9�� (�žӽɺ��)
		float multi_= rand_float(1.3f, 1.3f + 0.1f*pietyLevel(you.piety));
		a.damage *= multi_;
		a.max_damage *= multi_;
	}



	int damage_ = calculate_damage(a.type,a.damage,a.max_damage, back_stab);
	int accuracy_ = a.accuracy;
	bool sight_ = isYourShight();
	bool only_invisible_ = ((env[current_level].isInSight(position, true)) && !isView());
	bool graze_ = false;
	



	if(s_graze && randA(5) == 0)
	{
		if(a.type >= ATT_THROW_NORMAL && a.type < ATT_THROW_LAST)
			graze_ = true;
	}


	if(s_glow)
		accuracy_+=5; //������� ���� ����
	if(GetMindReading() && a.order == &you)
		accuracy_+=10; //���Ĵ��ߴ�.
	if(a.order)
	{
		if(a.order->isplayer() && !isView())
		{
			accuracy_ -=5;
		}

		if(!a.order->isplayer() && !isView((monster*)a.order))
		{
			accuracy_ -=5;
		}
	}


	name_infor name_;
	if(a.order)
		name_ = (*a.order->GetName());
	int percent_ = min(100,max(10,55+(accuracy_-GetEv())*(accuracy_>GetEv()?3.5f:3)));



	if(wiz_list.wizard_mode == 1)
	{		
		if(damage_>0)
		{
			char temp[100];
			sprintf_s(temp,100,"�ǵ�����-%d ����-%d �Ͻ�-%d ����-%d ���߷�-%d%%",damage_,a.damage,a.max_damage,a.accuracy,percent_);
			printlog(temp,true,false,false,CL_help);
		}
	}

	if (s_invincibility) {
		damage_ = 0;
	}

	if((randA(100) <= percent_ && !graze_) || back_stab == 3 || perfect_)
	{
		if(s_saved){
			auto it = env[current_level].mon_vector.begin();
			for( ;it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && env[current_level].dgtile[position.x][position.y].isMove(it->isFly(),it->isSwim(),false) && it->isSaveSummoner(this))
				{
					if(sight_ || only_invisible_)
					{
						char temp[128];
						sprintf_s(temp,128,"%s%s %s%s ���մ�!",it->GetName()->name.c_str(),it->GetName()->name_is(), GetName()->name.c_str(),GetName()->name_to());
						printlog(temp,true,false,false,CL_magic);
					}
					PositionSwap(&(*it));
					return it->damage(a,perfect_);
					break;
				}
			}
		}
		
		if(back_stab != 3 && isHaveSpell(SPL_MAMIZO_EVADE) && randA(4) == 0)
		{ //20%�� Ȯ���� ������ ��ȿ�ϰ� ��ũ			
			if(sight_ || only_invisible_)
			{
				printarray(true,false,false,CL_magic,3,GetName()->name.c_str(),name.name_is(true),"�������� ��ȭ�Ͽ� ������ ���ߴ�!");
			}
			Blink(10);
			return false;
		}
		if (env[current_level].isSanctuary(position))
		{
			//�������� ��� �������� 0
			damage_ = 0;
		}



		if(sight_ || only_invisible_)
		{
			print_damage_message(a, back_stab);
		}
		




		if (a.type == ATT_SLEEP && state.GetState() == MS_SLEEP)
		{
			HpUpDown(-1, DR_SLEEP);
		}
		else if(damage_)
		{
			if ((sight_ || only_invisible_) && a.type < ATT_THROW_NORMAL) {
				soundmanager.playSound("hit");
			}

			enterlog();
			
			hp-=damage_;
			if(damage_/3 > 0 && a.type == ATT_VAMP && randA(2) == 0)
			{
				if(a.order)
				{
					a.order->HpUpDown(damage_/3,DR_EFFECT);	
					if(sight_ || only_invisible_)
						printarray(true,false,false,CL_normal,4,a.order->GetName()->name.c_str(),a.order->GetName()->name_is(true), GetName()->name.c_str(),"�� ü���� ����ߴ�.");
			
				}
			}
			if (a.type == ATT_LUNATIC && randA(2) == 0) {
				SetLunatic(rand_int(3, 8));
			}
			if (id == MON_LARVA)
			{
				if (a.order) {
					if (distan_coord(position, a.order->position) <= 2)
					{
						smoke_type could_ = randA(1) ? SMT_POISON : SMT_CONFUSE;
						env[current_level].MakeSmoke(a.order->position, could_==SMT_POISON?img_fog_poison: img_fog_poison, could_, rand_int(5, 7), 0, this);
					}

				}
			}
			if(id == MON_MUSHROOM && (randA(1) || hp<=0) )
			{
				for(int i=-1;i<=1;i++){
					for(int j=-1;j<=1;j++){
							env[current_level].MakeSmoke(coord_def(position.x+i,position.y+j),img_fog_poison,SMT_POISON,rand_int(3,6),0,this);
					}
				}
			}

			if(a.type == ATT_THROW_FREEZING)
			{
				int frozen_ = randA_1(10);
				frozen_*=GetColdResist();
				SetFrozen(frozen_);
			}
			if(s_veiling)
			{
				if(a.order && a.type >=ATT_NORMAL && a.type < ATT_THROW_NORMAL)
				{
					a.order->damage(attack_infor(randA_1(s_value_veiling),s_value_veiling,99,this,GetParentType(),ATT_VEILING,name_infor("���ϸ�",true)), true);
					s_veiling = 0;
					s_value_veiling = 0;
				}
			}
			if (player_joon_punch_)
			{
				you.PowUpDown(-rand_int(1, 10), true);
				createGold(position, rand_int(1, 2));
			}
			if(hp<=0)
			{
				if (sight_) {
					if (flag & M_FLAG_UNIQUE && id != MON_ENSLAVE_GHOST) {
						soundmanager.playSound("kill_named");
					}
					else {
						soundmanager.playSound("kill");
					}
				}
				if(a.order)
				{
					if (sight_) {
						{
							char* c_ = Get_Speak(id, this, MST_DEAD);
							if (c_)
								printlog(c_, true, false, false, CL_normal);
						}

						if (id == MON_REIMU) {
							printarray(true, false, false, CL_danger, 3, GetName()->name.c_str(), GetName()->name_is(true), "ƴ�������� �������.");
						}
						else {
							printarray(true, false, false, CL_danger, 5, name_.name.c_str(), name_.name_is(true), GetName()->name.c_str(), GetName()->name_to(true), flag & M_FLAG_INANIMATE ? "�ı��Ǿ���. " : "�׾���. ");
						}

					}
					else if(a.p_type == PRT_PLAYER || a.p_type == PRT_ALLY)
					{
						printlog("������ �����ϴ� ���� ������.",true,false,false,CL_normal);
						if(!isView() && env[current_level].isInSight(position) && (you.auto_pickup==0))
							auto_pick_onoff(true);
					}
				}

				dead(a.p_type, !(a.order));
			}

			

			if(id == MON_SEIGA && randA(3) )
			{ //���̰��� ������ ���ϸ� ���� �� �ִ� ���� ���´�.
				rand_rect_iterator rect_(position,1,1);
				while(!rect_.end())
				{
					if(!env[current_level].dgtile[(*rect_).x][(*rect_).y].isMove(true,true,false))
					{
						SetXY((*rect_));
						PlusTimeDelay(-2*GetSpeed());
						break;
					}
					rect_++;
				}
			}


		}
		else
		{
			if(sight_ || only_invisible_)
				print_no_damage_message(a);
		}
		//���� �������� �����ʾƵ� ������
		if(a.type == ATT_S_POISON && randA(1))
		{
			SetPoison(15+randA(10), 50, false);
			SetPoisonReason(a.p_type);
		}
		if(a.type == ATT_M_POISON && randA(1))
		{
			SetPoison(40+randA(15), 100, false);
			SetPoisonReason(a.p_type);
		}
		if(a.type == ATT_SICK && randA(1))
		{
			SetPoison(40+randA(15), 100, false);
			SetSick(rand_int(10,20));
			SetPoisonReason(a.p_type);
		}
		if(a.type == ATT_THROW_WEAK_POISON)
		{
			SetPoison(10+randA(15), 50, false);
			SetPoisonReason(a.p_type);
		}
		if(a.type == ATT_THROW_MIDDLE_POISON)
		{
			SetPoison(40+randA(15), 100, false);
			SetPoisonReason(a.p_type);
		}
		if(a.type == ATT_THROW_STRONG_POISON)
		{
			SetPoison(70+randA(20), 150, true);
			SetPoisonReason(a.p_type);
		}
		if(a.type == ATT_POISON_BLAST)
		{
			SetPoison(70+randA(20), 150, true);
			SetPoisonReason(a.p_type);
		}
		if(a.type == ATT_CURSE && randA(1))
		{	
			SetPoison(15+randA(25), 150, true);
			if(randA(3)==1)
				SetSlow(10+randA(10));
		}
		if(a.type == ATT_CHOAS)
		{
			GetChoas(this,damage_);
		}
		
		if(a.type == ATT_CHOAS)
		{
			GetChoas(this,damage_);
		}
		if(damage_ && a.order == &you)
		{
			if(a.type >= ATT_NORMAL && a.type < ATT_THROW_NORMAL && you.GetProperty(TPT_CONFUSE_ATTACK) && randA(4) == 0)
			{
				if(!confuse_resist)
				{
					printarray(false,false,false,CL_normal,3,"����� ������ ",GetName()->name.c_str(),"�� �㸦 �񷶴�! ");
					SetConfuse(rand_int(2,4));
				}
			}

		}

		//���ڴ°� ���ݴ��� �Ŀ� �����
		if (a.type == ATT_SLEEP) {
			SetSleep(rand_int(10, 25));
		}
		else {
			AttackedTarget(a.order);

		}
	}
	else
	{
		if(a.order && (sight_ || only_invisible_))
		{			
			if(!graze_)
				printarray(true,false,false,CL_bad,7,name_.name.c_str(),"�� ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"��������.");
			else
				printarray(true,false,false,CL_bad,7,name_.name.c_str(),"�� ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"�׷�����Ǿ���.");
		}
		return false;
	}
	return true;
}
bool monster::simple_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_)
{
	bool return_ = false;
	return_ = image->draw(pSprite, x_, y_,D3DCOLOR_XRGB(120,120,255));
	return return_;
}
bool monster::draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_)
{
	bool return_ = false;
	if (s_glow) {
		img_effect_halo.draw(pSprite, x_, y_, 127);
	}
	if (s_veiling) {
		img_effect_veiling.draw(pSprite, x_, y_, 255);
	}

	return_ = image->draw(pSprite, x_, y_,id == MON_ENSLAVE_GHOST?128:255);
	if (id == MON_DANCING_ARMOUR || id == MON_DANCING_WEAPON) {
		img_mons_dancing_weapon.draw(pSprite, x_, y_, 255);
	}
	if (return_ && !(flag & M_FLAG_NO_STATE))
	{

		int offset_ = 0;
		for (monster_state_simple mss = MSS_SLEEP; mss < MSS_MAX; mss = (monster_state_simple)(mss + 1))
		{
			if (isSimpleState(mss))
			{
				if (statetotexture(mss)) {
					return_ = statetotexture(mss)->draw(pSprite, x_ + offset_, y_, 255);
					offset_ -= 5;
				}
			}
		}
	}
	if(return_)
	{
		int hp_ = hp*5/max_hp;
		if(hp_>=0 && hp_<5)
			return_ = img_hp_graphic[hp_].draw(pSprite,x_,y_+12,255);
	}
	return return_;
}
bool monster::smartmove(short_move x_mov, short_move y_mov, int num_)
{
	if(num_<=0)
		return false;
	if (!isCanMove())
		return false;

	if(state.GetState() == MS_ATACK)
	{//���ݻ����̸鼭
		if(target)
		{//Ÿ���� �������ְ�
			if(max(abs(position.x - target->position.x),abs(position.y -  target->position.y))<=1)
			{//Ÿ�ٰ� �Ÿ��� 1ĭ�̸��϶�
				rand_rect_iterator new_pos_(target->position,1,1,true);

				while(!new_pos_.end())
				{
					if(max(abs(position.x - new_pos_->x),abs(position.y -  new_pos_->y))<=1)
					{//�����ϼ��ִ� ��ġ
						if(env[current_level].isMove(new_pos_->x, new_pos_->y, isFly(), isSwim(),flag & M_FLAG_CANT_GROUND))
						{ //�̵��Ҽ��ִ� ��ġ��.				
							unit *unit_ = env[current_level].isMonsterPos(new_pos_->x, new_pos_->y);
							if(unit_)
							{//��ų �� �ִ� ��������
								if(unit_ != this && !unit_->isplayer() && ((monster*)unit_)->isAllyMonster(this))
								{
									if(!((monster*)unit_)->smartmove(x_mov,y_mov, num_-1)){ //��Ű�� ����
										
										new_pos_++;
										continue;
									}
								}
								else
								{
									new_pos_++;
									continue;
								}
							}

							//������ �� ������ �����δ�.
							SetXY(coord_def(new_pos_->x,new_pos_->y));
							PlusTimeDelay(-GetSpeed());
							return true;
						}

					}
					new_pos_++;
				}
			}

		}
	}
	return false;
}

int monster::move(short_move x_mov, short_move y_mov, bool only_move)
{	
	if(!x_mov && !y_mov)
		return 0;
	if(s_confuse)
	{
		do
		{
			x_mov = (short_move)rand_int(MV_BACK,MV_FRONT);
			y_mov = (short_move)rand_int(MV_BACK,MV_FRONT);
		}while(x_mov == MV_NONE && y_mov == MV_NONE);
	}

	if(!(flag & M_FLAG_NONE_MOVE) &&
		env[current_level].isMove(position.x+x_mov,position.y+y_mov,isFly() || s_confuse, isSwim(), false/*flag & M_FLAG_CANT_GROUND*/))
	{
		if(env[current_level].isSmokePos(position.x+x_mov,position.y+y_mov))
		{
			smoke* temp_smoke = env[current_level].isSmokePos2(position.x+x_mov,position.y+y_mov);
			if(hp<temp_smoke->danger(this))
				return 0;
		}
		if(floor_effect* temp_floor = env[current_level].isFloorEffectPos(position.x+x_mov,position.y+y_mov))
		{
			if(hp<temp_floor->danger(this))
				return 0;
		}

		if((you.position.x  == position.x+x_mov && you.position.y  == position.y+y_mov))
		{
			if(only_move)
				return 0;
			if(you.s_timestep)
				return 0;
			if(isUserAlly())
				return 0;
			if(flag & M_FLAG_NO_ATK)
				return 1;
			int num_=0;
			for(int i=0;i<3;i++,num_++)
				if(atk_type[i] == ATT_NONE)
					break;
			if(isHaveSpell(SPL_SUICIDE_BOMB))
			{
				MonsterUseSpell(SPL_SUICIDE_BOMB, false, this, you.position);
				return 1;
			}
			else if(num_)
			{
				num_ = randA(num_-1);
				attack_infor temp_att(GetAttack(num_,false),GetAttack(num_,true),GetHit(),this,GetParentType(),atk_type[num_],atk_name[num_]);
				you.damage(temp_att);			
				enterlog();
				return 1;
			}
			return 0;
		}
		for(vector<monster>::iterator it=env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
		{
			if((*it).isLive() && (*it).position.x == position.x+x_mov && (*it).position.y == position.y+y_mov)
			{
				if(((*it).isEnemyMonster(this) || s_confuse || (*it).id == MON_BUSH)) //���϶�
				{
					if(only_move)
						return 0;
					if(flag & M_FLAG_NO_ATK)
						return 1;
					int num_=0;
					for(int i=0;i<3;i++,num_++)
						if(atk_type[i] == ATT_NONE)
							break;
					if(isHaveSpell(SPL_SUICIDE_BOMB))
					{
						MonsterUseSpell(SPL_SUICIDE_BOMB, false, this, you.position);
						return 1;
					}
					else if(num_)
					{
						num_ = randA(num_-1);
						attack_infor temp_att(GetAttack(num_,false),GetAttack(num_,true),GetHit(),this,GetParentType(),atk_type[num_],atk_name[num_]);
						(*it).damage(temp_att);
						enterlog();
						return 1;
					}
					return 0;
				}
				else if (id == MON_SUMIREKO && !it->isplayer() && it->isAllyMonster(this))
				{
					if (distan_coord(position, target_pos) > 16)
					{
						//���̷��� Ư�� ���
						//���̷��ڴ� ���� �Ÿ��� �־����� �ڽ��� ��ȯ�� ��������̿� �ڸ� ��ȯ�� �����ϴ�.
						if (it->sm_info.parent_map_id == map_id &&
							it->sm_info.summon_id == GetSummonKind(SPL_SUMMON_TRASH))
						{
							it->SetXY(coord_def(position.x, position.y));
							SetXY(coord_def(position.x + x_mov, position.y + y_mov));
							return 2;
						}
						else
							return 0;
					}
					else
						return 0;
				}
				else
				{
					if(!(flag & M_FLAG_LEADER_SUMMON) && (*it).isAllyMonster(this) && randA(4) == 0)
					{
						if(!(*it).smartmove(x_mov, y_mov, 2))
						{
							return 0;
						}
					}
					else
						return 0;
				}
			}
		}
		if(flag & M_FLAG_CANT_GROUND && !env[current_level].isMove(position.x+x_mov,position.y+y_mov,isFly(), isSwim(), flag & M_FLAG_CANT_GROUND))
		{
			if(s_confuse)
			{
				return 1;
			}
			return 0;
		}

		SetXY(coord_def(position.x+x_mov,position.y+y_mov));

		return 2;
	}
	else if(env[current_level].isDoor(position.x+x_mov,position.y+y_mov) && flag & M_FLAG_OPEN_DOOR && env[current_level].isMonsterOpen(position.x + x_mov, position.y + y_mov))
	{
		coord_def temp(position.x+x_mov,position.y+y_mov);
		return OpenDoor(temp);
	}
	else
	{		
		if(s_confuse)
		{
			return 1;
		}
		return 0;
	}
}
int monster::move(const coord_def &c, bool only_move)
{
	return move((c.x>position.x?MV_FRONT:(c.x==position.x?MV_NONE:MV_BACK)),(c.y>position.y?MV_FRONT:(c.y==position.y?MV_NONE:MV_BACK)), only_move);
}
bool monster::offsetmove(const coord_def &c)
{		
	position += c;
	target_pos += c;
	if(position.x >= 0 && position.x < DG_MAX_X && position.y >= 0 && position.y < DG_MAX_Y )
		return true;
	else
	{
		dead(PRT_NEUTRAL, false, true);
		return false;
	}
}
bool monster::OpenDoor(const coord_def &c)
{
	if(env[current_level].isDoor(c.x,c.y))
	{
		if(env[current_level].OpenDoor(c.x,c.y))
		{
			if(env[current_level].isInSight(c))
			{
				if(env[current_level].isInSight(position))
				{
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� ������.");
				}
				else
				{
					printlog("���� ���ȴ�.",true,false,false,CL_normal);
				}
				you.resetLOS();
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



int monster::longmove()
{
	if(move(inttodirec(direction,position.x,position.y), false))
	{
		if(randA(15)==1)
			direction = rand_int(0,7);
	}
	else
	{	
		deque<int> dq;
		for(int i=0;i<8;i++)
			if(i != direction || randA(2) == 1)
				dq.push_back(i);
		if(dq.size() == 7)
			dq.push_back(direction);
		rand_shuffle(dq.begin(),dq.end());
		for(int i=0;i<8;i++)
		{
			if(env[current_level].isMove(inttodirec(dq[i],position.x,position.y),isFly(), isSwim(), flag & M_FLAG_CANT_GROUND)) //���� ���� 2��°����
			{
				direction = dq[i];
			}
		}
	}


	//if(will_move.empty())
	//{
	//	//PathSearch(position,you.position,will_move,ST_MONSTER_NORMAL);
	//}

	//if(will_move.empty())
	//{
	//	state.StateTransition(MSI_REST);
	//	return 0;
	//}
	//else
	//{
	//	int re = 0;
	//	coord_def temp = will_move.top();
	//	re = move(temp);
	//	will_move.pop();
	//	return re;
	//}
	return true;
}
int monster::atkmove(int is_sight, bool only_move)
{
	int move_ = 0;
	
	//if(target || memory_time)
	//{
	//	if(target && !(target->isplayer()))
	//		target_pos = target->position;
	//}

	if(!only_move && !s_confuse && !s_fear && !s_lunatic)
	{
		if(target && target->position == target_pos)
		{
			list<spell>::iterator it = spell_lists.begin();
			for(;it != spell_lists.end();it++)
			{
				spell_list id_ = (spell_list)(it->num);
				int percent_ = it->percent;
				if (s_clever  && percent_<90){
					percent_ = percent_*1.5f;
					if (percent_ > 90)
						percent_ = 90;
				}
				if(randA_1(100)<=percent_)
				{
					if(isMonSafeSkill(id_,this,target_pos))
					{
						if (SpellFlagCheck(id_, S_FLAG_SPEAK) && flag & M_FLAG_SPEAK)
						{
							if (env[current_level].isSilence(position) || s_mute)
							{
								if (!(flag & M_FLAG_SILENCE))
									continue;
							}
							else
							{
								enterlog();
								char* c_ = Get_Speak(id, this, MST_MAGIC);
								if (c_ && (env[current_level].isInSight(position)))
									printlog(c_, true, false, false, CL_magic);
							}
						}
						if(MonsterUseSpell(id_,false,this,SpellFlagCheck(id_,S_FLAG_IMMEDIATELY)?position:target_pos))
						{
							Noise(position,SpellNoise(id_),this); //������ ������� �ٸ� ���ͷ� �а��� �� �־�. it�� ����ϸ� �ȵ�
							return true;
						}
					}
				}			
			}
		}
	}

	if (flag & M_FLAG_LEADER_SUMMON && flag & M_FLAG_SUMMON)
	{
		if(sm_info.parent_map_id >= 0)
		{
			auto it = env[current_level].mon_vector.begin();
			for( ;it != env[current_level].mon_vector.end();it++)
			{
				if(sm_info.parent_map_id == it->map_id)
				{
					move_ = MoveToPos(it->position, only_move);
					break;
				}
			}
		}
		else if(sm_info.parent_map_id == -2)
		{
			move_ = MoveToPos(you.position, only_move);
		}

	}
	else if(target || memory_time)
	{
		if(!target)
		{
			//if(distan_coord(you.position,position)<=5)
			//{
			//	target_pos = you.position;
			//	if(memory_time<10)
			//		memory_time = 10;
			//}
		}
		coord_def c = target_pos-position;
		if(!s_fear)
			move_ = MoveToPos(target_pos, only_move);
		if(s_fear)
		{
			int x_ =  (target_pos.x-position.x)>0?-1:(target_pos.x-position.x)<0?1:0;
			int y_ =  (target_pos.y-position.y)>0?-1:(target_pos.y-position.y)<0?1:0;
			int direc_ = GetPosToDirec(position, position+coord_def(x_,y_));
			int arr_[] = {0,-1,1,-2,2};
			for(int i=0;i<5;i++)
			{
				move_ = MoveToPos(position+GetDirecToPos(direc_+arr_[i]), only_move);
				if (!move_ && i == 4 && s_fear > 0)
				{
					s_fear = 0;
				}
				else if(move_)
					break;

			}
		}
		//else if(target_pos == position && target)
		//{
		//	target_pos = target->position;
		//}
		else if(target_pos == position/* && !target*/)
		{
			target_pos = target_pos+c;
			if(!env[current_level].isMove(target_pos.x,target_pos.y,isFly(), isSwim(), flag & M_FLAG_CANT_GROUND))
			{ //���� ������ 8���� �������� ����ƴ
				deque<int> dq;
				for(int i=0;i<8;i++)
					dq.push_back(i);
				rand_shuffle(dq.begin(),dq.end());
				for(int i=0;i<8;i++)
				{
					if(env[current_level].isMove(inttodirec(dq[i],position.x,position.y),isFly(), isSwim(), flag & M_FLAG_CANT_GROUND))
					{
						target_pos = inttodirec(dq[i],position.x,position.y);
						break;
					}
				}
			}
		}
	}
	return move_;
}


bool monster::isCanMove()
{
	if(state.GetState() == MS_SLEEP)
		return false;
	if (s_paralyse)
		return false;
	if (flag & M_FLAG_NONE_MOVE)
		return false;

	return true;
}
bool monster::isHaveSpell(spell_list sp)
{
	
	for(list<spell>::iterator it=spell_lists.begin();it!=spell_lists.end();it++)
	{
		if(sp == (*it).num)
			return true;
	}
	return false;
}
int monster::MoveToPos(coord_def pos_, bool only_move)
{
	int move_ = 0;
	close_beam_iterator it(position,pos_);
	for(;!it.end() && !move_;it++)
	{
		move_ = move((*it), only_move);
	}
	return move_;
}
bool monster::isView()
{
	if(!s_glow && s_invisible && !you.invisible_view && !s_ally)
		return false;
	return true;
}
bool monster::isView(const monster* monster_info)
{
	if(!s_glow && s_invisible && !(monster_info->flag & M_FLAG_CAN_SEE_INVI) && !isAllyMonster(monster_info))
		return false;
	return true;

}
bool monster::CanSpeak()
{
	if((!env[current_level].isSilence(position))  && flag & M_FLAG_SPEAK)
	{
		return true;
	}
	return false;
}
bool monster::dead(parent_type reason_, bool message_, bool remove_)
{
	bool sight_ = false;
	if(isYourShight())
		sight_ = true;
	if(s_silence)
		env[current_level].MakeSilence(position, s_silence_range, false);	
	if (flag & M_FLAG_NONE_MOVE && flag & M_FLAG_UNHARM)
	{
		env[current_level].dgtile[position.x][position.y].flag &= ~FLAG_BLOCK;
	}
	if(s_catch)	
		you.SetCatch(NULL);
	if(s_changed) //������ �ʱ����� ���ƿ�
	{
		ChangeMonster(MON_RACCON,0);
	}



	if (message_ && !remove_)
	{
		if (sight_){
			if (flag & M_FLAG_UNIQUE && id != MON_ENSLAVE_GHOST) {
				soundmanager.playSound("kill_named");
			}
			else {
				soundmanager.playSound("kill");
			}
			{
				char* c_ = Get_Speak(id, this, MST_DEAD);
				if (c_)
					printlog(c_, true, false, false, CL_normal);
			}

			printarray(false, false, false, CL_danger, 3, GetName()->name.c_str(), GetName()->name_is(true), 
				id == MON_REIMU ? "ƴ�������� �������." : (flag & M_FLAG_INANIMATE ?"�ı��Ǿ���. ":"�׾���. "));

			if ((reason_ == PRT_PLAYER || reason_ == PRT_ALLY) && !(flag & M_FLAG_SUMMON) && s_fear == -1) {
				printlog("���ǻ���� ������ ����ġ�� ���� �� ����. ", true, false, false, CL_normal);
			}
		}
		else if((reason_ == PRT_PLAYER || reason_ == PRT_ALLY) && !(flag & M_FLAG_SUMMON) && s_fear != -1)
		{
			printlog("������ �����ϴ� ���� ������. ",true,false,false,CL_normal);
			if(!isView() && env[current_level].isInSight(position) && (you.auto_pickup==0))
				auto_pick_onoff(true);
		}
	}

	if(!remove_)
		env[current_level].SummonClear(map_id);
	
	hp = 0;

	
	if(isArena())
		return true;

	if(id == MON_ENSLAVE_GHOST)
	{
		if(summon_time == -1)
		{
			if(you.god_value[GT_YUYUKO][0] == map_id && you.god_value[GT_YUYUKO][1] == current_level)
			{
				char temp[200];
				sprintf_s(temp,200,"%s%s�׾���.",name.name.c_str(),name.name_do(true));
				AddNote(you.turn,CurrentLevelString(),temp,CL_yuyuko);
				you.god_value[GT_YUYUKO][0] = 0;
				you.god_value[GT_YUYUKO][1] = 0;
			}
			else
			{
				char temp[200];
				sprintf_s(temp,200,"you god_value(%d, %d) mon value(%d, %d)",
					you.god_value[GT_YUYUKO][0] ,you.god_value[GT_YUYUKO][1],
					map_id, current_level);
				printarray(true,false,false,CL_danger,3,"�ؿ�ȥ���� ���� : ",GetName()->name.c_str(), temp);
			}
		}
	}

	if(id == MON_YATHASI || id == MON_BENBEN)
	{
		bool benben_ = (id == MON_BENBEN);
		for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end();it++)
		{
			if(it->isLive() && ((it->id == MON_YATHASI && benben_) || (it->id == MON_BENBEN && !benben_)))
			{				
				if(it->isYourShight())
				{
					printarray(true,false,false,CL_small_danger,3,it->name.name.c_str(),it->name.name_is(true),"�г뿡 �Ҹ��ƴ�. �ڽ��� �ɷ¿� �����Ͽ���!");
				}
				else
				{
					printarray(true,false,false,CL_small_danger,1,"�ָ��� �г뿡 �� ����� �����.");
				}
				it->LevelUpdown(5,5.0f,0.0f);

				if(it->id == MON_YATHASI)
				{
					it->spell_lists.push_back(spell(SPL_INVISIBLE,20));
				}
				else if(it->id == MON_BENBEN)
				{
					it->spell_lists.push_back(spell(SPL_HASTE,20));
				}
				break;
			}
		}
	}



	for(int i = 0; i < 5; i++)
	{
		if(you.god_value[GT_LILLY][i] == 1)
		{
			if(you.lilly_allys[i].map_id == map_id && you.lilly_allys[i].floor == current_level)
			{
				you.god_value[GT_LILLY][i] = 2;
				you.lilly_allys[i].cooldown = rand_int(2,4); //��Ȱ�غ�
			}
		}
	}



	if(!(flag & M_FLAG_SUMMON) && !remove_ && !(flag & M_FLAG_UNHARM))
	{
		if (reason_ == PRT_PLAYER && s_fear != -1) //�÷��̾ �׿���.
		{
			you.GetExp(exper);
		}
		else if (reason_ == PRT_ALLY && s_fear != -1) //������ �׿���.
		{
			you.GetExp(exper/*(exper+1)/2*/); //���̻� �������� ����ġ ������ �����ʴ´�.
		}
		if(!randA(1+you.GetPunish(GT_SHINKI)?1:0) && !isArena())
		{
			item_infor temp;
			env[current_level].MakeItem(position,makePitem((monster_index)id, 1, &temp));
		}
		if (s_ally != -1 && !isArena())
		{
			if (!item_lists.empty())
			{
				for (auto it = item_lists.begin(); it != item_lists.end(); it++)
				{
					item *it2;
					it2 = env[current_level].MakeItem(position, (*it));;
				}
			}
		}
		//if(id == MON_MAGIC_BOOK)
		//{
		//	item_infor t;
		//	item *it2;
		//	it2 = env[current_level].MakeItem(position,makeCustomBook(&t));
		//	list<spell>::iterator it = spell_lists.begin();
		//	if(it != spell_lists.end()){
		//		it2->value1 = it->num;
		//		it++;
		//	}
		//	if(it != spell_lists.end()){
		//		it2->value2 = it->num;
		//		it++;
		//	}
		//	if(it != spell_lists.end()){
		//		it2->value3 = it->num;
		//		it++;
		//	}
		//}
	}
	if(flag & M_FLAG_UNIQUE && id != MON_ENSLAVE_GHOST && !remove_)
	{
		if(reason_ == PRT_PLAYER || reason_ == PRT_ALLY)
		{
			char temp[200];
			sprintf_s(temp,200,"���ӵ� %s%s �׿���.",name.name.c_str(),name.name_to());
			AddNote(you.turn,CurrentLevelString(),temp,CL_normal);
		}
		else
		{
			char temp[200];
			sprintf_s(temp,200,"���ӵ� %s%s �׾���.",name.name.c_str(),name.name_is());
			AddNote(you.turn,CurrentLevelString(),temp,CL_normal);

		}
	}
	if (!(flag & M_FLAG_SUMMON) && !remove_ && !(flag & M_FLAG_UNHARM))
		GodAccpect_KillMonster(this,reason_);
	return true;
}
int monster::action(int delay_)
{	
	bool is_sight = false;
	if(env[current_level].isInSight(position, true))
	{
		if(first_contact)
			FirstContact();
		is_sight = true; //���� ���� ���̴���
	}
	else
	{
		if(you.god == GT_SATORI && !you.GetPunish(GT_SATORI) && pietyLevel(you.piety)>=3 &&
			GetPositionGap(position.x, position.y, you.position.x, you.position.y) <= satori_sight())
		{
			env[current_level].magicmapping(position.x,position.y);
			env[current_level].ClearShadow(position, SWT_MONSTER);
		}
	}




	time_delay+=delay_ * rand_int(9,11) / 10; //������ randomizing
	if(flag & M_FLAG_CONFUSE)
		s_confuse = 10;
	if(flag & M_FLAG_SUMMON && summon_time>=0)
	{
		if((summon_time--)<=0)
		{
			hp = 0;
			if (id == MON_CLOSE_DOOR) {
				env[current_level].changeTile(position, DG_CLOSE_DOOR);
				if (is_sight)
					printarray(true, false, false, CL_okina, 3, GetName()->name.c_str(), GetName()->name_is(true), "����� ������ ���ƿԴ�.");
			}
			else {
				env[current_level].MakeSmoke(position, img_fog_normal, SMT_NORMAL, 4, 0, this);
				if (is_sight && id != MON_TRASH) {
					printarray(true, false, false, CL_bad, 3, GetName()->name.c_str(), GetName()->name_is(true), "���� ������ �������.");
					soundmanager.playSound("kill_banashed");
				}
			}
			env[current_level].SummonClear(map_id);
			return 0;
		}
	}

	while(time_delay>GetSpeed())
	{
		if(s_poison)
		{
			if (poison_percent(s_poison) && !s_invincibility)
			{
				hp -= randA_1(3)*poison_damage(s_poison);
				if(hp<=0)
				{
					dead(poison_reason, true); //���� �÷��̾��� ���� ����.
					return 1;
				}
			}
			s_poison-=randA_1(3);
			if(s_poison<0)
				s_poison = 0;
			if(is_sight && isView())
			{
				if(!s_poison)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"������ ȸ���Ǿ���.");
			}
		}	

		if(s_might)
		{
			s_might--;
			if(is_sight && isView())
			{
				if(!s_might)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�� �̻� ���� ������ �ʴ�.");
			}
		}
		if (s_clever)
		{
			s_clever--;
			if (is_sight && isView())
			{
				//if (!s_clever)
				//	printarray(true, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "�� �̻� �� ������ �ʴ�.");
			}
		}
		if(s_tele)
		{
			if(s_tele == 1)
			{
				Teleport();
			}
			if(s_tele)
				s_tele--;
		}
		if(s_haste)
		{
			s_haste--;
			if(is_sight && isView())
			{
				if(!s_haste)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�� �̻� ������ �ʴ�.");
			}
		}

		
		if(s_confuse)
		{
			s_confuse--;
			if(is_sight && isView())
			{
				if(!s_confuse)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"ȥ���������� ���ĳ´�.");
			}
		}
		if(s_slow)
		{
			s_slow--;
			if(is_sight && isView())
			{
				if(!s_slow)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�� �̻� ������ �ʴ�.");
			}
		}
		if(s_frozen)
		{
			s_frozen--;
			if(is_sight && isView())
			{
				if(!s_frozen)
					printarray(true,false,false,CL_normal,2,GetName()->name.c_str(),"�� ������ ��Ҵ�.");
			}
		}	
		if(s_ally>0)
		{
			s_ally--;
			if(is_sight && isView())
			{
				if(!s_ally)
						printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���̻� �ŷ���°� �ƴϴ�.");
			}
		}	
		

		if(s_elec)
		{		
			int power_=min(SpellCap(SPL_SHOCK),level*5);
			if(randA(6)<2)
				skill_elec_passive(power_,this);
			s_elec--;
			if(is_sight && isView())
			{
				if(!s_elec)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"������ �����.");
			}
		}
		if(s_paralyse)
		{
			s_paralyse--;
			if(is_sight && isView())
			{
				if(!s_paralyse)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�ٽ� ������ �� �ְ� �Ǿ���.");
			}
		}
		if(s_glow)
		{
			if (!((is_sight && you.GetBuffOk(BUFFSTAT_HALO)) || (is_sight && you.s_weather==3 && you.s_weather_turn>0)))
			{
				s_glow--;
				if (is_sight && isView())
				{
					if (!s_glow)
						printarray(true, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "������ ���� �����.");
				}
			}
		}
		else if ((is_sight && you.GetBuffOk(BUFFSTAT_HALO)) || (is_sight && you.s_weather == 3 && you.s_weather_turn>0))
		{
			s_glow = 1;
		}

		if(s_graze>0)
		{
			s_graze--;
			if(is_sight && isView())
			{
				if(!s_graze)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�� �̻� �׷���� ���� �ʴ´�.");
			}
		}
		if(s_sick)
		{
			s_sick--;
			if(is_sight && isView())
			{
				if(!s_sick)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�� �̻� ������ �ʴ�.");
			}
		}	
		if(s_silence)
		{
			s_silence--;
	
			if((s_silence-5)/2 < s_silence_range)
			{
				env[current_level].MakeSilence(position, s_silence_range, false);
				s_silence_range = (s_silence-5)/2 >0 ? (s_silence-5)/2 : 0;
				env[current_level].MakeSilence(position, s_silence_range, true);
			}
			if(!s_silence)	
				env[current_level].MakeSilence(position, s_silence_range, false);
	
			if(is_sight && isView())
			{
				if(!s_silence)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_to(true),"���δ� ������ �������.");
			}
		}
		if(s_veiling)
		{
			s_veiling--;
			if(is_sight && isView())
			{
				if(!s_veiling)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_to(true),"�ְ��� �ٶ��� �������.");
			}
		}
		if(s_invisible>0)
		{
			bool prev_view_ = isYourShight();
			s_invisible--;
			if(is_sight && isView())
			{
				if(!s_invisible)
				{
					if(prev_view_)
						printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"������ Ǯ�ȴ�.");
					else
					{
						printarray(true,false,false,CL_small_danger,3,GetName()->name.c_str(),GetName()->name_is(true),"������ Ǯ���鼭 ����� �巯�´�.");
						if(you.auto_pickup==0)
							auto_pick_onoff(true);
					}
				}
			}
		}
		if(s_mute)
		{
			s_mute--;
			if(is_sight && isView())
			{
				if(!s_mute)
				{
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�� �̻� ����� �ƴϴ�.");
				}
			}
		}
		
		if(s_fear > 0)
		{
			s_fear--;
		}
		if(s_ghost)
		{
			s_ghost--;
			if(is_sight && isView())
			{
				if(!s_ghost)
				{
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�� �̻� ��ȥ�� �����������ʴ�.");
				}
			}
		}
		
		if(env[current_level].isViolet(position))
			SetLunatic(2);
		if(s_lunatic)
		{
			s_lunatic--;
			if(is_sight && isView())
			{
				if(!s_lunatic)
				{
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�� �̻� ��ġ�� �ʾҴ�.");
				}
			}
		}

		if(s_exhausted>0)
		{
			s_exhausted--;
		}
		
		if(force_turn)
		{
			force_turn--;
			if(is_sight && isView())
			{
				if(!force_turn)
				{
					if(force_strong)
						printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"�� ��ȭ�� ������. ");
					else
						printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"�� ��ȭ�� ������. ");
				}
			}
		}
		if(s_changed)
		{
			s_changed--;
			if(!s_changed)
			{
				if(is_sight && isView())
				{
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�а��� Ǯ���� �ʱ����� ���ƿԴ�.");
				}
				ChangeMonster(MON_RACCON,0);
			}
		}

		if (s_invincibility > 0)
		{

			s_invincibility--;
			if (!s_invincibility)
			{
				if (is_sight && isView())
				{
					printarray(true, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "�� �̻� ������ �ƴϴ�.");
				}
			}
		}


		if(s_communication)
		{
			s_communication--;
			if(!s_communication)
			{
				s_exhausted = rand_int(40,50);
				if (id == MON_MOON_RABIT_SUPPORT && !isUserAlly())
					s_exhausted = -1;
			}


			switch(id)
			{
			case MON_MOON_RABIT_SUPPORT:
				if(monster* mon_=BaseSummon(MON_MOON_RABIT_ATTACK, rand_int(20,30), false, false, 2, this, position, SKD_OTHER, -1))
				{
					if(!isUserAlly())
					{
						mon_->flag &= ~M_FLAG_SUMMON;
					}
					mon_->exper = 0;
					mon_->SetHaste(rand_int(10, 30));
				}
				break;
			case MON_HELL_HOUND:
				if(target)
				{
					dif_rect_iterator rit(target->position,8,true);
					while(!rit.end())
					{
						coord_def check_pos_ = (*rit);
						int temp_ = pow((float)abs(check_pos_.x-target->position.x),2)+pow((float)abs(check_pos_.y-target->position.y),2);
						if(temp_>49 && env[current_level].isMove(check_pos_.x, check_pos_.y, false) && (!target->isplayer() || env[current_level].isInSight(check_pos_, true)) 
							&& target->isSightnonblocked((*rit)))
						{

							if(monster* mon_=BaseSummon(MON_HELL_HOUND, rand_int(20,30), false, false, 2, this, check_pos_, SKD_OTHER, -1))
							{
								mon_->exper = exper / 2;
								exper -= mon_->exper;
								mon_->SetExhausted(rand_int(10,30));
								mon_->AttackedTarget(target);
								if(!isUserAlly())
								{
									mon_->flag &= ~M_FLAG_SUMMON;
								}
							}
							break;
						}
						rit++;
					}
				}
				break;
			default:
				printarray(true,false,false,CL_magic,3,GetName()->name.c_str(),GetName()->name_is(true),"���Ḧ ��������� �ִ�.");
			}
		}
		else if(!s_paralyse)
		{
			if(target) //������� ����Ҷ�
			{	
				if(!target->isView(this))
				{
					target = NULL;

				}
				//if(target->isplayer() && player_invisible)
				//{
				//}
				//else if(!target->isplayer() && target->GetInvisible() && !(flag & M_FLAG_CAN_SEE_INVI))
				//{
				//	target = NULL;
				//}
			}
			if(!s_sick)
				HpRecover();
			if(target && !target->isLive())
			{
				target = NULL;
				if(isUserAlly())
				{
					if(is_sight)
						CheckSightNewTarget();
					if(!target)
					{
						state.SetState(MS_FOLLOW);
					}
				}
				else
				{
					if(!s_fear)
						CheckSightNewTarget();
					if(!target)
						state.StateTransition(MSI_LOST);
				}
			}

			if(flag & M_FLAG_LEADER_SUMMON && flag & M_FLAG_SUMMON)
			{
				if(state.GetState() == MS_NORMAL)
				{
					state.SetState(MS_FOLLOW);
				}
			}
			if(state.GetState() == MS_ATACK && isUserAlly() && (target == NULL ||target == &you))
			{
				target = &you;
				state.SetState(MS_FOLLOW);
			}
			if((flag & M_FLAG_SUMMON)  && isUserAlly() && !env[current_level].isInSight(target_pos, true) )
			{
				state.SetState(MS_FOLLOW);

			}

			switch (state.GetState())
			{
			case MS_NORMAL:
				longmove();
				if (flag & M_FLAG_SHIELD || isUserAlly()) {
					if (distan_coord(position, first_position) > 4 * 4)
					{
						//�� ���� �ڸ��� ��Ű�� ���� ���� �ڸ��� ���ư���.
						stack<coord_def> will_move_;
						will_move.clear();
						if (PathSearch(position, first_position, will_move_, ST_MONSTER_NORMAL, current_level, isFly(), isSwim()))
						{
							while (!will_move_.empty())
							{
								will_move.push_front(will_move_.top());
								will_move_.pop();
							}
							state.StateTransition(MSI_SEARCH);
						}
						else {
							first_position = position;
						}
					}
				}
				if (randA(9)) //������ �÷��̾ ã�´�.(���� ó���� ����)
					sightcheck(is_sight);
				else
					CheckSightNewTarget();
				break;
			case MS_SLEEP:
			case MS_REST:
				if (isUserAlly())
				{
					state.SetState(MS_FOLLOW);
					break;
				}
				target = NULL;
				if (is_sight && you_detect())//�þ� �ȿ� ������ ���ڽ� üũ
				{
					FoundTarget(&you, FoundTime());
					int percent_ = 1;
					if (you.god == GT_SHIZUHA && !you.GetPunish(GT_SHIZUHA))
						percent_ = 4;
					if (flag & M_FLAG_SPEAK && randA(percent_) == 0 && (env[current_level].isInSight(position)) && !env[current_level].isSilence(position))
					{
						if (char* c_ = Get_Speak(id, this, MST_FOUND)) {
							printlog(c_, true, false, false, CL_speak);
							Noise(position, 12, this);
						}
					}
				}
				break;
			case MS_ATACK:
				if (isUserAlly() && target && memory_time)
				{
					target_pos = target->position;
				}
				if (you.s_timestep && (target == &you || !target) && !isUserAlly())
				{
					memory_time = 0;
					target = NULL;
					state.StateTransition(MSI_LOST);
				}
				else if (is_sight && you.isView(this) && !isUserAlly())
				{ //���ε� �þ� �ȿ� �����鼭 �÷��̾ ���̴� ����
					if (!s_fear)
						CheckSightNewTarget();
					//FoundTarget(&you,FoundTime());
					if (flag & M_FLAG_SUMMON && you.god == GT_SHINKI && !you.GetPunish(GT_SHINKI) && pietyLevel(you.piety) >= 3)
					{
						//��Ű�� ��ȯ���� �����Ѵ�.
						if (randA(1))
							break;
					}

					if (flag & M_FLAG_SPEAK && (env[current_level].isInSight(position)) && !env[current_level].isSilence(position) && randB(1000, (flag & M_FLAG_UNIQUE) ? 66 : 3)) {//���� ���ϱ�

						if (s_confuse || s_lunatic)
						{
							if (char* c_ = Get_Speak(id, this, MST_CONFUSE))
								printlog(c_, true, false, false, CL_speak);
						}
						else if (!s_fear)
						{
							if (char* c_ = Get_Speak(id, this, MST_NORMAL))
								printlog(c_, true, false, false, CL_speak);
						}
					}

				}
				else if (!isUserAlly())
				{//���ε� �þ߾ȿ� ���ų� �÷��̾ ������ �ʴ� ����
					if (memory_time > 0)
					{
						if (!s_fear)
							CheckSightNewTarget();
						memory_time--;
					}
					else
					{
						target = NULL;

						if (flag & M_FLAG_SHIELD) {
							//�� ���� �ڸ��� ��Ű�� ���� ���� �ڸ��� ���ư���.
							stack<coord_def> will_move_;
							will_move.clear();
							if (PathSearch(position, first_position, will_move_, ST_MONSTER_NORMAL, current_level, isFly(), isSwim()))
							{
								while (!will_move_.empty())
								{
									will_move.push_front(will_move_.top());
									will_move_.pop();
								}
								state.StateTransition(MSI_SEARCH);
							}
							else
								state.StateTransition(MSI_LOST);
						}
						else {
							state.StateTransition(MSI_LOST);
						}
					}
				}
				else
				{
					memory_time = FoundTime();
				}
				if (state.GetState() != MS_FIND)
				{
					atkmove(is_sight);
					if (!is_sight && env[current_level].isInSight(position, true))
					{ //�÷��̾ �߰��ϰԵȴ�.
						if (target == &you)
							FoundTarget(target, FoundTime());
					}
				}
				break;
			case MS_FOLLOW:
				if(you.s_timestep && sm_info.parent_map_id < 0)
				{	
					state.StateTransition(MSI_LOST);
				}
				else if(sm_info.parent_map_id >= 0)
				{
					auto it = env[current_level].mon_vector.begin();
					for( ;it != env[current_level].mon_vector.end();it++)
					{
						if(sm_info.parent_map_id == it->map_id)
						{
							MoveToPos(it->position, false);
							break;
						}
					}
					if(it == env[current_level].mon_vector.end())
					{
						flag &= ~M_FLAG_LEADER_SUMMON;
						state.StateTransition(MSI_LOST);
					}
				}
				else
					MoveToPos(you.position, false);				
				sightcheck(is_sight);
				break;
			case MS_FIND:
				{
					if (will_move.empty())
					{
						state.StateTransition(MSI_REST);
					}
					else {
						coord_def c_ = will_move.back();
						will_move.pop_back();
						int success_ = MoveToPos(c_, false);
						if (success_ != 2) //�̵�����
						{
							will_move.push_back(c_);
						}
						if (is_sight && !isUserAlly() && you_detect())//�þ� �ȿ� ������ ���ڽ� üũ
						{
							FoundTarget(&you, FoundTime());
							int percent_ = 1;
							if (you.god == GT_SHIZUHA && !you.GetPunish(GT_SHIZUHA))
								percent_ = 4;
							if (flag & M_FLAG_SPEAK && randA(percent_) == 0 && (env[current_level].isInSight(position)) && !env[current_level].isSilence(position))
							{
								if (char* c_ = Get_Speak(id, this, MST_FOUND)) {
									printlog(c_, true, false, false, CL_speak);
									Noise(position, 12, this);
								}
							}
						}
					}
				}
				break;
			}
		}
		special_action(is_sight, false);
		time_delay-=GetSpeed();
		if (!is_sight && s_fear == -1) {
			//���ǻ���� ���ʹ� �þ߹ۿ� ������ �����
			dead(PRT_NEUTRAL, false, true);
		}

		if(!isLive())
			break;
	}


	bool in_sight_ = env[current_level].isInSight(position);

	if(in_sight_)
		prev_sight = true;
	else if(prev_sight)
	{
		if(isView() && !(you.god == GT_SATORI && !you.GetPunish(GT_SATORI) && pietyLevel(you.piety)>=3 &&
			GetPositionGap(position.x, position.y, you.position.x, you.position.y) <= satori_sight()))
			env[current_level].MakeShadow(prev_position,image, id);
		prev_sight = false;
	}
	



	prev_position = position;

	if (env[current_level].dgtile[position.x][position.y].tile == DG_SEA &&
		!isFly() && !isSwim())
	{
		printarray(false, false, false, CL_danger, 3, GetName()->name.c_str(), GetName()->name_is(true), "���� ������. ");
		dead(PRT_PLAYER, true);
	}
	else if (env[current_level].dgtile[position.x][position.y].tile == DG_LAVA &&
		!isFly())
	{
		printarray(false, false, false, CL_danger, 3, GetName()->name.c_str(), GetName()->name_is(true), "��Ͽ� ������. ");
		dead(PRT_PLAYER, true);
	}




	return 0;
}
void monster::sightcheck(bool is_sight_)
{	
	if(!isUserAlly() )
	{
		if(is_sight_ && you_detect())//�þ� �ȿ� ������ ���ڽ� üũ
		{
			FoundTarget(&you, FoundTime());
		}
	}
}

void monster::special_action(int delay_, bool smoke_)
{

	switch (id)
	{
	case MON_RUMIA:
		if (smoke_){
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
					env[current_level].MakeSmoke(coord_def(i + position.x, j + position.y), img_fog_dark, SMT_DARK, rand_int(3, 4), 0, this);
		}
		break;
	case MON_FIRE_CAR:
		if (smoke_){
			if (!isUserAlly() && current_level != ZIGURRAT_LEVEL)
			{
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						if (i != 0 || j != 0)
							env[current_level].MakeSmoke(coord_def(i + position.x, j + position.y), img_fog_fire, SMT_FIRE, 1, 0, this);
					}
				}
			}
		}
		break;
	case MON_YAMAME:
		if (!smoke_){
			if (env[current_level].isInSight(position, true) && randA(2) == 0 && !isArena() && !isUserAlly())
			{
				you.SetSick(10);
			}
		}
		break;
	case MON_TEWI:
		if (!smoke_){
			if (env[current_level].isInSight(position, true) && hp < max_hp / 2 && randA(3) == 0 && !isUserAlly())
			{
				SetFear(rand_int(20, 40));
			}
		}
		break;
	case MON_CLOWNPIECE:
		if (!smoke_){
			if (env[current_level].isInSight(position, true) && !you.s_lunatic && randA(5) == 0 && !isArena() && !isUserAlly())
			{
				you.SetLunatic(rand_int(5, 10));
			}
		}
		break;
	case MON_RED_UFO:
	case MON_GREEN_UFO:
	case MON_BLUE_UFO:
		if (!smoke_){
			if (randA(10) == 0) {
				ChangeMonster(randA(2) ? randA(1) ? MON_RED_UFO : MON_GREEN_UFO : MON_BLUE_UFO, 0);
			}
		}
		break;
	case MON_SEKIBANKI:
		if (!smoke_){
			if (env[current_level].isInSight(position, true) && randA(2) == 0 &&
				state.GetState() == MS_ATACK && !s_mute)
			{
				if (!env[current_level].isSilence(position) && flag & M_FLAG_SPEAK) {
					enterlog();
					char* c_ = Get_Speak(id, this, MST_MAGIC);
					if (c_ && (env[current_level].isInSight(position)))
						printlog(c_, true, false, false, CL_magic);
				}
				MonsterUseSpell(SPL_SUMMON_SEKIBANKI, false, this, target_pos, 200);
				ChangeMonster(MON_SEKIBANKI_BODY, 0);
			}
		}
		break;
	case MON_SEKIBANKI_BODY:
		if (!smoke_){
			if (!(env[current_level].isInSight(position, true)) && randA(2) == 0)
			{
				env[current_level].SummonClear(map_id);
				ChangeMonster(MON_SEKIBANKI, 0);
			}
		}
		break;
	case MON_KEINE:
		if (!smoke_){
			if (hp <= max_hp / 2) {
				if (env[current_level].isInSight(position))
					printlog("ü���� ���� ���̳װ� �������� ��ȭ�Ͽ���! ", true, false, false, CL_magic);
				ChangeMonster(MON_KEINE2, 0);
			}
		}
		break;
	case MON_KEINE2:
		if (!smoke_){
			if (hp == max_hp) {
				ChangeMonster(MON_KEINE, 0);
			}
		}
		break;
	case MON_KOKORO1:
	case MON_KOKORO2:
	case MON_KOKORO3:
	{
		for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if (it->isLive() &&
				((it->id == MON_MASK_ANGRY && id == MON_KOKORO1) ||
				(it->id == MON_MASK_SAD && id == MON_KOKORO2) ||
					(it->id == MON_MASK_HAPPY && id == MON_KOKORO3)
					)) {

				return;
			}
		}

		SetExhausted(rand_int(4, 8));
		ChangeMonster(MON_KOKORO, 0);

		break;
	}
	case MON_MAI2:
		if (!smoke_){
			if (env[current_level].isInSight(position, true) && !isArena() && isUserAlly())
			{
				you.HpUpDown(rand_int(3, 4), DR_NONE);
			}
			for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
			{
				if (it->isLive() && isAllyMonster(&(*it)) && distan_coord(it->position, position) <= 8*8 && isMonsterSight(it->position)){
					int heal = it->max_hp / 10;
					it->HpUpDown(heal, DR_NONE);
				}
			}
		}
		break;
	case MON_SATONO:
		if (!smoke_){
			if (env[current_level].isInSight(position, true) && !isArena() && isUserAlly())
			{
				you.MpUpDown(randA(3) ? 1 : rand_int(1, 2));
			}
			for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
			{
				if (it->isLive() && isAllyMonster(&(*it)) && distan_coord(it->position, position) <= 8 * 8 && isMonsterSight(it->position)){
					it->SetClever(2);
					//it->MpUpDown(randA(3) ? 1 : rand_int(1, 2));
				}
			}
		}
		break;
	case MON_ELEC_BALL:
	{
		if (!smoke_) {
			exper++; //�ӽ� ����
			if (exper == 3) {
				skill_elec_ball_bomb(level * 5, this);
				summon_time = 0;
				hp = 0;
				env[current_level].MakeSmoke(position, img_fog_normal, SMT_NORMAL, 4, 0, this);
				env[current_level].SummonClear(map_id);
			}
		}
	}
		break;
	case MON_BOMB:
	{
		if (!smoke_) {
			exper++; //�ӽ� ����
			if (exper == 3) {
				env[current_level].MakeNoise(position, 20, NULL);
				evoke_bomb(level * 5, false, this, position);
				summon_time = 0;
				hp = 0;
				env[current_level].SummonClear(map_id);
			}
		}
	}
	break;
	default:
		break;
	}
}
bool monster::SetPoisonReason(parent_type type_)
{
	poison_reason = type_;
	return true;
}
bool monster::SetPoison(int poison_, int max_, bool strong_)
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

	if(isYourShight())
	{
		if(!s_poison)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� �ɷȴ�. ");
		else
			printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"�� ���� ��������. ");
	}

	s_poison += poison_;
	if(s_poison>150)
		s_poison = 150;
	if(s_poison>max_)
		s_poison = max_;
	return true;
}
int monster::HpRecoverDelay()
{
	hp_recov +=  (((float)rand_int(180,220))/(max_hp+5))*10+1;
	return hp_recov;
}
bool monster::HpRecover(int turn_)
{
	if(hp<max_hp)
	{
		hp_recov -= speed*turn_;
		while((hp_recov)<=0)
		{
			hp++;
			HpRecoverDelay();
			if(hp == max_hp)
			{
				hp_recov = 0;
				HpRecoverDelay();
				return true;
			}
		}
	}
	return false;
}
int monster::HpUpDown(int value_,damage_reason reason, unit *order_)
{
	if (s_invincibility) {
		return 0;
	}
	hp+= value_;
	if(hp >= max_hp)
	{
		hp = max_hp;		
	}	
	if(hp<=0)
	{
		dead(order_?order_->GetParentType():PRT_NEUTRAL,order_?true:false);
	}
	return value_;
}
bool monster::SetTele(int tele_)
{
	if(!tele_)
		return false;
	if(isYourShight())
	{
		if(!s_tele)
		{
			printarray(true,false,false,CL_normal,2,GetName()->name.c_str(),"�� �ֺ� ������ �Ҿ���������. ");
		}
		else
		{
			printarray(true,false,false,CL_normal,2,GetName()->name.c_str(),"�� �ֺ� ������ ������ ��ã�Ҵ�. ");
		}
	}
	if(!s_tele)
		s_tele = tele_;
	else
		s_tele = 0;

	return true;
}
bool monster::SetMight(int might_)
{
	if(!might_)
		return false;
	if(isYourShight())
	{
		if(!s_might)
		{
			printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� ��������. ");
		}
		else
			printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� ���� ��������. ");
	}
	s_might += might_;
	if(s_might>100)
		s_might = 100;
	return true;
}
bool monster::SetClever(int clever_)
{
	if (!clever_)
	return false;
	s_clever = clever_;
	if (s_clever>100)
		s_clever = 100;
	return true;
}
bool monster::SetAgility(int agility_)
{
	return false;
}
bool monster::SetHaste(int haste_)
{	
	if(!haste_)
		return false;
	if(isYourShight())
	{
		if(!s_haste)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"��������. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"��������. ");
	}
	s_haste += haste_;
	if(s_haste>100)
		s_haste = 100;
	return true;
}
bool monster::SetConfuse(int confuse_, bool strong_)
{	
	if(!confuse_)
		return false;
	if(!strong_ && confuse_resist>0)
		return false;

	if(isYourShight())
	{
		if(!s_confuse)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"ȥ������������. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� ȥ������������. ");
	}
	s_confuse += confuse_;
	if(s_confuse>50)
		s_confuse = 50;
	return true;
}
bool monster::SetSlow(int slow_)
{
	if(!slow_)
		return false;
	if(isYourShight())
	{
		if(!s_slow)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"��������. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� ��������. ");
	}
	s_slow += slow_;
	if(s_slow>100)
		s_slow = 100;
	return true;
}

bool monster::SetFrozen(int frozen_)
{	
	if(!frozen_)
		return false;
	if(randA_1(3)<ice_resist*2)
		return false;
		
	if(isYourShight())
	{
		if(!s_frozen)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���پ� �������� ��������. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� ���پ� �������� ��������. ");
	}
	s_frozen += frozen_;
	if(s_frozen>25)
		s_frozen = 25;
	return true;
}
bool monster::SetCharm(int charm_)
{	
	if(!charm_)
		return false;

	if(isYourShight())
	{
		if(!s_ally)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�ŷ�Ǿ���. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� �ŷ�Ǿ���. ");
	}
	s_ally += charm_;
	if(s_ally>200)
		s_ally = 200;
	return true;
}

bool monster::SetElec(int elec_)
{
	if(!elec_)
		return false;
	if(isYourShight())
	{
		if(!s_elec)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�����ǰ��ִ�. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�����ǰ��ִ�. ");
	}
	s_elec += elec_;
	if(s_elec>40)
		s_elec = 40;
	return true;
}
bool monster::SetParalyse(int paralyse_)
{	
	if(!paralyse_ && s_paralyse)
		return false;
		
	if(isYourShight())
	{
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"����Ǿ���. ");
	}
	s_paralyse += paralyse_;
	if(s_paralyse>100)
		s_paralyse = 100;
	return true;
}
bool monster::SetLevitation(int levitation_)
{
	return false;
}
bool monster::SetGlow(int glow_, bool no_speak)
{
	if(!glow_)
		return false;
	if(isYourShight() && !no_speak)
	{
		if(!s_glow)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�������ִ�. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� �������ִ�.");
	}
	s_glow += glow_;
	if(s_glow>100)
		s_glow = 100;
	return true;
}
bool monster::SetGraze(int graze_)
{	
	if(!graze_)
		return false;
	if(isYourShight())
	{
		if(!s_graze)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�׷���� �ϱ� �����ߴ�. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�׷���� �ϱ� �����ߴ�. ");
	}
	s_graze += graze_;
	if(s_graze>100)
		s_graze = 100;
	return true;
}
bool monster::SetSilence(int silence_, int silence_range_)
{
	if(!silence_)
		return false;
	if(isYourShight())
	{
		if(!s_silence)
			printarray(true,false,false,CL_small_danger,3,GetName()->name.c_str(),GetName()->name_is(true),"�ֺ��� �Ҹ��� ������.");
	}
	if(s_silence)
		env[current_level].MakeSilence(position, s_silence_range, false);
	s_silence_range = silence_range_;
	s_silence += silence_;
	env[current_level].MakeSilence(position, s_silence_range, true);
	if(s_silence>80)
		s_silence = 80;
	return true;
}
bool monster::SetSick(int sick_)
{
	if(!sick_)
		return false;
	if(isYourShight())
	{
		if(!s_sick)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���� �ɷȴ�. ");
		else
			printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"�� ���� ��������. ");
	}
	s_sick += sick_;
	if(s_sick>200)
		s_sick = 200;
	return true;
}
bool monster::SetVeiling(int veiling_, int value_)
{
	if(!veiling_)
		return false;
	if(isYourShight())
	{
		if(!s_veiling)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�ٶ��� ���մ�. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_to(true),"���δ� �ٶ��� ��������. ");
	}
	s_veiling += veiling_;
	s_value_veiling = value_;
	if(s_veiling>20)
		s_veiling = 20;
	return true;
}
bool monster::SetInvisible(int invisible_)
{
	if(!invisible_)
		return false;
	bool prev_view_ = isYourShight();
	int prev_invisible_ = s_invisible;
	const char *prev_name = GetName()->name.c_str();
	const char *prev_name_is = GetName()->name_is(true);

	
	s_invisible += invisible_;
	if(s_invisible>100)
		s_invisible = 100;

	if(prev_view_)
	{
		if(isYourShight())
		{
			if(!prev_invisible_)
				printarray(true,false,false,CL_normal,3,prev_name,prev_name_is,"�����ϰ� ���Ѵ�. ");
			else
				printarray(true,false,false,CL_normal,3,prev_name,prev_name_is,"���� �����ϰ� ���Ѵ�. ");
		}
		else
		{
			printarray(true,false,false,CL_small_danger,3,prev_name,prev_name_is,"���������鼭 �������. ");
			if(you.auto_pickup>0)
				auto_pick_onoff(true);
		}
	}
	return true;
}
bool monster::SetMute(int mute_)
{
	if(!mute_)
		return false;
	if(isYourShight())
	{
		if(!s_mute)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"����� �Ǿ���. ");
		else
			printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"�� ħ���� �������. ");
	}
	s_mute += mute_;
	if(s_mute>100)
		s_mute = 100;
	return true;
}
bool monster::SetGhost(int ghost_)
{
	if(!ghost_)
		return false;
	if(flag & M_FLAG_INANIMATE)
	{		
		printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�������̱⿡ ��ȥ�� ����. ");	
		return false;
	}
	if (id == MON_REIMU)
	{
		printlog("������ ���� ����� ��� �����κ��� �ӹڵ����ʴ´�.", true, false, false, CL_normal);
		return false;
	}

	if (dream)
	{
		printarray(true, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "���� �ֹ��̱⿡ �ӹ��� �� ����. ");
		return false;
	}

	if(flag & M_FLAG_SUMMON)
	{
		printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�̹� ���ӵǾ��ִ�. ");	
		return false;
	}
	if(isYourShight())
	{
		printarray(true,false,false,CL_yuyuko,2,GetName()->name.c_str(),"�� ��ȥ�� ��������. ���ӽð����� ������ ����� ���ᰡ �ȴ�. ");
	}
	s_ghost += ghost_;
	if(s_ghost>100)
		s_ghost = 100;
	return true;

}
bool monster::SetSaved(int saved_)
{
	s_saved = saved_;
	return true;
}

bool monster::SetSwift(int swift_)
{
	return false;
}
bool monster::SetFear(int fear_)
{
	if (!fear_ && s_fear == -1)
		return false;
	if (fear_ == -1)
	{
		if (isYourShight())
		{
			if (!s_fear)
				printarray(false, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "������ ������ ���Ǹ� ���� ����ߴ�. ");
	}

		s_fear = fear_;
	}
	else
	{
		if (isYourShight())
		{
			if (!s_fear)
				printarray(false, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "������ ���ȴ�. ");
		}
	s_fear += fear_;
		if (s_fear > 50)
		s_fear = 50;
	}
	return true;
}

bool monster::SetMindReading(int mind_)
{
	if(!mind_)
		return false;
	if(isYourShight())
	{
		if(!s_mind_reading){			
			if(flag & M_FLAG_ANIMAL)
				printarray(true,false,false,CL_normal,2,GetName()->name.c_str(),"�� ������ �˰ԵǾ� ģ������. ");
			else
				printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"������ ���Ĵ��ߴ�. ");
		}
	}
	s_mind_reading = mind_;
	if(flag & M_FLAG_ANIMAL)
	{
		s_ally= -1;
		CheckSightNewTarget();
	}
	return true;
}
bool monster::SetLunatic(int lunatic_)
{
	if(!lunatic_)
		return false;
	if(confuse_resist>0)
		return false;
	if(isYourShight())
	{
		if(!s_lunatic)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"���⿡ �۽ο���. ");
	}
	s_lunatic = lunatic_;
	if(s_lunatic>20)
		s_lunatic = 20;
	return true;
}

bool monster::SetNeutrality(int s_neutrality_)
{
	s_neutrality = s_neutrality_;
	return true;
}

bool monster::SetCommunication(int s_communication_)
{
	if(!s_communication_)
		return false;
	if(isYourShight())
	{
		if(!s_communication)
		{
			switch(id)
			{
			case MON_MOON_RABIT_SUPPORT:
				printarray(true,false,false,CL_magic,3,GetName()->name.c_str(),GetName()->name_is(true),"���ῡ ������ û�ϴ� ���ĸ� ������ �����ߴ�. ");
				break;
			case MON_HELL_HOUND:
				printarray(true,false,false,CL_small_danger,2,GetName()->name.c_str(),"�� �Ҹ��� �̲��� �� �ٸ� ���������� �������� �����Ѵ�. ");
				break;
			default:
				printarray(true,false,false,CL_magic,3,GetName()->name.c_str(),GetName()->name_is(true),"���Ḧ ��������� �ִ�. ");
			}

		}
	}
	s_communication = s_communication_;
	return true;
}
bool monster::SetExhausted(int s_exhausted_)
{
	if(!s_exhausted_)
		return false;
	s_exhausted = s_exhausted_;
	return true;
}
bool monster::SetForceStrong(bool force_, int turn_, bool speak_)
{
	if(!turn_)
		return false;
	
	if(isYourShight() && speak_)
	{
		if(!force_)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"��ȭ�Ǿ���. ");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"��ȭ�Ǿ���. ");
	}

	force_strong = force_;
	force_turn = turn_;
	return true;
}

bool monster::SetInvincibility(int s_invincibility_, bool speak_)
{
	if (!s_invincibility_)
		return false;
	if (isYourShight() && speak_)
	{
		printarray(false, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "�������°� �Ǿ���. ");
	}
	s_invincibility = s_invincibility_;
	return true;
}
bool monster::SetDebufPlus(int s_debuf_)
{
	debuf_boost =  s_debuf_;
	return debuf_boost;
}
bool monster::SetSleep(int s_sleep_)
{
	if (s_sleep_ >= randA_1(100)) {

		if(isYourShight() && state.GetState() != MS_SLEEP)
			printarray(false, false, false, CL_normal, 3, GetName()->name.c_str(), GetName()->name_is(true), "�ῡ ������. ");
		state.SetState(MS_SLEEP);
		return true;
	}
	return false;
}
bool monster::AttackedTarget(unit *order_)
{	
	if(order_)
	{
		if(order_->isplayer())
		{
			//if(back_stab)
			//	you.SkillTraining(SKT_BACKSTAB,1);
			if(state.GetState() != MS_ATACK || !target)
			{
				target = &you;
				target_pos = you.position;
			}
		}
		else
		{
			if(state.GetState() != MS_ATACK || !target)
			{
				target = order_;
				target_pos = order_->position;
			}
			memory_time= FoundTime();
		}
		if(state.GetState() == MS_SLEEP) //�ڰ������� ����鼭 ��ĥ �� ����
		{			
			int percent_ = 1;
			if(you.god == GT_SHIZUHA && !you.GetPunish(GT_SHIZUHA) )
				percent_ = 4;
			if(flag & M_FLAG_SPEAK && randA(percent_)==0 && !env[current_level].isSilence(position))
			{
				Noise(position,12,this);
				if(env[current_level].isInSight(position))
				{
					if(char* c_ = Get_Speak(id,this,MST_FOUND)){
						printlog(c_,true,false,false,CL_speak);
					}
				}
			}	
		}

		state.StateTransition(MSI_ATACKED);
	}
	else
	{
		if(state.GetState() != MS_ATACK)
			target = NULL;
		state.StateTransition(MSI_WAKE);
	}
	return true;
};
bool monster::Blink(int time_)
{
	int x_ = position.x, temp_x_ = x_, prev_x=x_;
	int y_ = position.y, temp_y_ = y_, prev_y=y_;
	//xy_ : ���� ��ũ�� ������ ��ġ(����)  
	//temp_xy_ : ��ũ�� ��ġ�� �̸� ã�Ƽ� �̵��������� Ȯ���Ѵ�.
	//prev_xy_ : ��ũ �� �� �ִ� ������ ��ġ ����(���� xy_�� ������ ������ ��ġ�� ��ã�� ���)
	for(int i=0;i<time_+10;i++)
	{
		temp_x_=x_+rand_int(-1,1);
		temp_y_=y_+rand_int(-1,1);
		if(env[current_level].isMove(temp_x_,temp_y_,true))
		{
			x_ = temp_x_;
			y_ = temp_y_;
			if((i>=time_ || i%5 == 0) && env[current_level].isMove(x_,y_,isFly(), isSwim(), flag & M_FLAG_CANT_GROUND) && !env[current_level].isMonsterPos(x_,y_) && !(you.position.x == x_ && you.position.y == y_) && !env[current_level].isSmokePos(x_,y_))
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
	SetXY(prev_x, prev_y);
	return true;
}
int monster::GetInvisible()
{
	return s_invisible;
}
bool monster::Teleport()
{
	bool prev_sight_ = isYourShight();
	while(1)
	{
		int x_ = randA(DG_MAX_X - 1);
		int y_ = randA(DG_MAX_Y - 1);
		if(env[current_level].isMove(x_,y_,isFly(), isSwim(), flag & M_FLAG_CANT_GROUND) && !env[current_level].isMonsterPos(x_,y_))
		{
			env[current_level].MakeSmoke(position, img_fog_normal, SMT_NORMAL, 4, 0, this);
			SetXY(x_, y_);
			bool curr_sight_ = isYourShight();
			if(prev_sight_ && !curr_sight_)
				printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"�����̵��� ���� �þ߿��� �������. ");
			else if(!prev_sight_ && curr_sight_)
				printarray(true,false,false,CL_small_danger,3,GetName()->name.c_str(),GetName()->name_do(true),"���ڱ� ��Ÿ����. ");

			return true;
		}
	}

}
int monster::GetResist()
{
	return 70+level * 5 + (resist+1) * 25;
}
int monster::GetDetect()
{
	int detect_ = 10+level*(1.5f+sense);
	if(!you.isView(this))
		detect_ -= (you.s_invisible>10 || you.togle_invisible)?70:20;
	if(you.s_autumn)
		detect_ -= 40;
	if(detect_<=0)
		return 0;
	return detect_;
}
bool monster::you_detect()
{
	if(isArena())
		return false;
	if (you.god == GT_OKINA) {
		//��Ű����� ������ �����Ҷ� ������ �ʾƾ� ��
		if (isMonsterSight(you.position, true) == false)
			return false;
	}

	return randB(you.GetStealth(),GetDetect());
}
bool monster::isYourShight()
{
	return ((env[current_level].isInSight(position)) && isView());
}
bool monster::isEnemyUnit(unit* unit_info)
{
	if(unit_info->isplayer())
	{
		return !isUserAlly();
	}
	else
	{
		return isEnemyMonster((monster*)unit_info);
	}
}
bool monster::isEnemyMonster(const monster* monster_info)
{
	if(isUserAlly() && monster_info->isUserAlly())
	{
		if(s_lunatic)
			return true;
		return false;
	}
	if(!isUserAlly() && !(monster_info->isUserAlly()))
	{
		if(s_lunatic ||	(s_neutrality != monster_info->s_neutrality))
			return true;
		return false;
	}
	return true;
}
bool monster::isPassedBullet(unit* order)
{
	
	if(!order)
	{ //�̰��� �߸�źȯ�̴�.
		if(flag & M_FLAG_PASSED_ENEMY)
			return true;
		else 
			return false;
	}
	else if(order == &you)
	{ //�̰��� �÷��̾��� źȯ�϶�
		if(isUserAlly() && flag & M_FLAG_PASSED_ALLY)
			return true;
		else if(isUserAlly() && flag & M_FLAG_PASSED_ENEMY)
			return false;
		else if(flag & M_FLAG_PASSED_ENEMY)
			return true;
		else
			return false;
	}
	else
	{ //�̰��� ������ źȯ�϶�
		if(flag & M_FLAG_PASSED_ENEMY  && isEnemyMonster((monster*)order))
			return true;
		else if(flag & M_FLAG_PASSED_ALLY  && isAllyMonster((monster*)order))
			return true;
		else
			return false;
	}
	return false;
}
bool monster::isAllyMonster(const monster* monster_info)
{
	if(isUserAlly() && monster_info->isUserAlly())
	{
		if(s_lunatic)
			return false;
		return true;
	}
	if(!isUserAlly() && !(monster_info->isUserAlly()))
	{
		if(s_lunatic ||	(s_neutrality != monster_info->s_neutrality))
			return false;
		return true;
	}
	return false;
}
bool monster::isUserAlly() const
{
	return s_ally;
}
bool monster::isSightnonblocked(coord_def c)
{
	bool intercept = false;
	for(int i=RT_BEGIN;i!=RT_END;i++)
	{
		int length_ = 8;
		beam_iterator it(position,c,(round_type)i);
		while(!intercept && !it.end())
		{
						
			coord_def check_pos_ = (*it);

			if(length_ == 0) //�þ߰� �� �޾Ҵ�.
			{
				intercept = true;
				break;
			}
			if(!env[current_level].isMove(check_pos_,true,true))
			{
				intercept = true;
				break;
			}
			it++;
			length_--;
		}
		if(intercept == false)
			break;
		else if(i == RT_END - 1)
		{
			return false; //���ݺҰ����� ��ġ
		}
		else
			intercept = false;
	}
	return true;
}
bool monster::isMonsterSight(coord_def c, boolean okina)
{	
	bool intercept = false;
	for(int i=RT_BEGIN;i!=RT_END;i++)
	{
		int length_ = 8;
		beam_iterator it(position,c,(round_type)i);
		int block_cloud = 2;
		while(!intercept && !it.end())
		{
			coord_def check_pos_ = (*it);
			if(length_ == 0) //�þ߰� �� �޾Ҵ�.
			{
				intercept = true;
				break;
			}
			if (!env[current_level].isSight(check_pos_) || (okina && env[current_level].isCloseDoor(check_pos_.x, check_pos_.y)))
			{
				intercept = true;
				break;
			}
			if (you.s_weather == 1 && you.s_weather_turn > 0) {
				//�Ȱ�ȿ���� �׻� �þ߸� ����
				block_cloud--;
				if (block_cloud < 0)
				{
					intercept = true;
					break;
				}
			}
			if (env[current_level].isSmokePos(check_pos_.x, check_pos_.y, true))
			{
				smoke* smoke_ = env[current_level].isSmokePos2(check_pos_.x, check_pos_.y);
				if (smoke_ && smoke_->sight_inter())
				{
					block_cloud -= smoke_->sight_inter();
					if (block_cloud < 0)
					{
						intercept = true;
						break;
					}
				}
			}
			it++;
			length_--;
		}
		if(intercept == false)
			break;
		else if(i == RT_END - 1)
		{
			return false; //���Ϳ��� �������ʴ� ��ġ
		}
		else
			intercept = false;
	}
	return true;
}
bool monster::CanChase()
{
	if(state.GetState() == MS_REST || state.GetState() == MS_SLEEP || state.GetState() == MS_NORMAL || state.GetState() == MS_FIND)
		return false;
	if(s_confuse)
		return false;
	if(s_mind_reading && s_ally && flag & M_FLAG_ANIMAL)
		return false;
	if( flag & M_FLAG_NONE_STAIR)
		return false;
	if (!isCanMove())
		return false;
	if (flag & M_FLAG_SHIELD)
		return false;
	return true;	
}
parent_type monster::GetParentType()
{
	return (isUserAlly() || s_lunatic)?PRT_ALLY:PRT_ENEMY;
}
bool monster::isUnique()
{
	return flag & M_FLAG_UNIQUE;
}
attack_weapon_type monster::GetAttackType()
{
	return AWT_NONE;
}
int monster::GetSpeed()
{
	return (s_haste?0.7f:1)*(s_slow?1.5f:1)*speed+(s_frozen+2)*speed/30;;
}
int monster::GetAttack(bool max_)
{
	int num_=0;
	for(int i=0;i<3;i++,num_++)
		if(atk_type[i] == ATT_NONE)
			break;

	if(num_ == 0)
		return 0;				

	num_ = randA(num_-1);

	return GetAttack(num_, max_);
}
int monster::GetAttack(int num_, bool max_)
{
	int atk_ = randA(atk[num_]);
	if(max_)
		atk_ = atk[num_];
	if(s_lunatic || s_might)
		atk_ *= 1.5f;
	if(force_turn)
	{
		if(force_strong)
			atk_*=2;
		else
			atk_/=2;
	}
	return atk_;
}
int monster::GetHit()
{
	int hit_ = level/3+8;
	return hit_;
}
int monster::GetEv()
{
	int ev_ = ev;
	if(s_confuse)
		ev_/=2;
	if(s_paralyse)
		ev_ = 0;
	return ev_;
}
bool monster::isSaveSummoner(unit* order)
{
	if(id == MON_DAUZING || id == MON_HOURAI || id == MON_FAKE_HOURAI){
		if(distan_coord(position, order->position) <=2)
		{
			if(sm_info.parent_map_id == order->GetMapId() && randA(2)){
				return true;
			}
		}
	}
	if(id == MON_GOLEM){
		if(distan_coord(position, order->position) <=2)
		{
			if(sm_info.parent_map_id == order->GetMapId() && randA(5)==0){
				return true;
			}
		}
	}
	if(id == MON_YOSIKA){
		if(distan_coord(position, order->position) <=2)
		{
			if(sm_info.parent_map_id == order->GetMapId() && randA(2)==0){
				return true;
			}
		}
	}
	return false;
}
float monster::GetFireResist(bool cloud_)
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
		return 0;
	else
		return 1;
}
float monster::GetColdResist(bool cloud_)
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
		return 0;
	else
		return 1;
}
float monster::GetElecResist(bool cloud_)
{
	if(elec_resist == 1)
		return 2.0f/3.0f;
	else if(elec_resist == 2)
		return 1.0f/3.0f;
	else if(elec_resist >= 3)
		return 0;
	else
		return 1;
}
bool monster::GetCloudResist()
{
	return wind_resist;
}

bool monster::isSimpleState(monster_state_simple state_)
{
	monster_state_simple temp = MSS_NONE;
	switch (state_)
	{
		case MSS_WANDERING:
			return (!isUserAlly() && state.GetState() == MS_NORMAL) || (!isUserAlly() && state.GetState() == MS_ATACK && target != &you)
				|| (!isUserAlly() && state.GetState() == MS_FIND);
		case MSS_SLOW:
			return (s_slow != 0) && s_haste == 0;
		case MSS_HASTE:
			return (s_haste != 0) && s_slow == 0;
		case MSS_POISON:
			return (s_poison != 0);
		case MSS_FEAR:
			return (s_fear != 0);
		case MSS_CONFUSE:
			return (s_confuse != 0 && (flag & M_FLAG_CONFUSE) == 0);
		case MSS_LUNATIC:
			return (s_lunatic != 0);
		case MSS_SLEEP:
			return (state.GetState() == MS_SLEEP || state.GetState() == MS_REST);
		case MSS_PARALYSE:
			return (s_paralyse != 0);
		case MSS_SUMMON:
			return ((flag & M_FLAG_SUMMON) != 0);
		case MSS_ALLY:
			return (isUserAlly());
	}
	return false;
}
monster_state_simple monster::GetSimpleState()
{
	monster_state_simple temp = MSS_NONE;

	if(state.GetState() == MS_NORMAL)
		temp = MSS_WANDERING;
	if (state.GetState() == MS_FIND)
		temp = MSS_WANDERING;
	if(!isUserAlly() && state.GetState() == MS_ATACK && target != &you)
		temp = MSS_WANDERING;
	if((s_slow != 0) && s_haste == 0)
		temp = MSS_SLOW;
	if((s_haste != 0) && s_slow == 0)
		temp = MSS_HASTE;
	if(s_poison)
		temp = MSS_POISON;
	if(s_fear)
		temp = MSS_FEAR;
	if (s_confuse && (flag & M_FLAG_CONFUSE) == 0)
		temp = MSS_CONFUSE;
	if(s_lunatic)
		temp = MSS_LUNATIC;
	if(state.GetState() == MS_SLEEP ||state.GetState() == MS_REST)
		temp = MSS_SLEEP;
	if(s_paralyse)
		temp = MSS_PARALYSE;
	if(flag & M_FLAG_SUMMON)
		temp = MSS_SUMMON;
	if(isUserAlly())
		temp = MSS_ALLY;
	return temp;
}
D3DCOLOR monster::GetStateString(monster_state_simple state_, char* string_)
{
	switch(state_)
	{
	case MSS_NONE:
		if(state.GetState() == MS_NORMAL)
		{
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_SLEEP:
		if(state.GetState() == MS_SLEEP)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		else if(state.GetState() == MS_REST)
		{
			sprintf_s(string_,30,"�޽�");
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_WANDERING:
		if(state.GetState() == MS_NORMAL || state.GetState() == MS_FIND)
		{
			sprintf_s(string_,30,"Ž����");
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_NO_NOTICE:
		if(state.GetState() == MS_ATACK && !isUserAlly() && target != &you)
		{
			sprintf_s(string_,30,"�߰��ȵ�");
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_CONFUSE:
		if (s_confuse && (flag & M_FLAG_CONFUSE) == 0)
		{
			sprintf_s(string_,30,"ȥ��");
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_POISON:
		if(s_poison)
		{
			sprintf_s(string_,30,"��");
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_SCARY:
		return CL_none;
	case MSS_MIGHT:
		if(s_might)
		{
			sprintf_s(string_,30,"����ȭ");
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_CLEVER:
		if (s_clever)
		{
			sprintf_s(string_,30, "���°�ȭ");
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_HASTE:
		if(s_haste && !s_slow)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_SLOW:
		if(s_slow && !s_haste)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		else
			return CL_none;
	case MSS_SMOKE_ABOVE:
		if(env[current_level].isSmokePos(position.x,position.y))
		{
			smoke* smoke_= env[current_level].isSmokePos2(position.x,position.y);
			sprintf_s(string_,30,smoke_->GetName());
			return CL_normal;
		}
		return CL_none;
	case MSS_SUMMON:
		if(flag & M_FLAG_SUMMON )
		{
			sprintf_s(string_,30,"��ȯ");
			return CL_normal;
		}
		return CL_none;
	case MSS_FROZEN:
		if(s_frozen)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		return CL_none;
	case MSS_ALLY:
		if(isUserAlly())
		{
			sprintf_s(string_,30,"��ȣ");
			return CL_normal;
		}
		return CL_none;
	case MSS_ELEC:
		if(s_elec)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		return CL_none;
	case MSS_PARALYSE:
		if(s_paralyse)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;

		}
		return CL_none;
	case MSS_GLOW:
		if(s_glow)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		return CL_none;
	case MSS_GRAZE:
		if(s_graze)
		{
			sprintf_s(string_,30,"�׷�����");
			return CL_normal;
		}
		return CL_none;
	case MSS_SILENCE:
		if(env[current_level].isSilence(position))
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		return CL_none;
	case MSS_SICK:
		if(s_sick)
		{
			sprintf_s(string_,30,"��");
			return CL_normal;
		}
		return CL_none;
	case MSS_VEILING:
		if(s_veiling)
		{
			sprintf_s(string_,30,"���ϸ�");
			return CL_normal;
		}
		return CL_none;
	case MSS_INVISIVLE:
		if(s_invisible)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		return CL_none;
	case MSS_TELE:
		if(s_tele)
		{
			sprintf_s(string_,30,"�����Ҿ���");
			return CL_normal;
		}
		return CL_none;
	case MSS_MUTE:
		if(s_mute)
		{
			sprintf_s(string_,30,"���");
			return CL_normal;
		}
		return CL_none;
	case MSS_CATCH:
		if(s_catch)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		return CL_none;
	case MSS_GHOST:
		if(s_ghost)
		{
			sprintf_s(string_,30,"��ȥ����");
			return CL_normal;
		}
		return CL_none;
	case MSS_FEAR:
		if(s_fear)
		{
			if (s_fear>0)
			sprintf_s(string_,30,"����");
			else
				sprintf_s(string_,30, "���ǻ��");
			return CL_normal;
		}
		return CL_none;
	case MSS_MIND_READING:
		if(s_mind_reading)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		return CL_none;
	case MSS_LUNATIC:
		if(s_lunatic)
		{
			sprintf_s(string_,30,"����");
			return CL_normal;
		}
		return CL_none;
	case MSS_COMMUNICATION:
		if(s_communication)
		{
			sprintf_s(string_,30,"����θ���");
			return CL_normal;
		}
		return CL_none;
	case MSS_FORCE:
		if(force_turn)
		{
			if(force_strong)
				sprintf_s(string_,30,"��ȭ");
			else				
				sprintf_s(string_,30,"��ȭ");
			return CL_normal;
		}
		return CL_none;
	case MSS_CHANGED:
		if(s_changed)
		{
			sprintf_s(string_,30,"�а���");
			return CL_normal;
		}
		return CL_none;
	case MSS_INVINCIBILITY:
		if (s_invincibility)
		{
			sprintf_s(string_,30, "����");
			return CL_normal;
		}
		return CL_none;
	case MSS_HP:
	{
		int hp_ = hp * 5 / max_hp;
		switch (hp_)
		{
		case 0:
			sprintf_s(string_,30, "�ױ� ����");
			return CL_danger;
		case 1:
			sprintf_s(string_,30, "�ɰ��� �λ�");
			return CL_small_danger;
		case 2:
			sprintf_s(string_,30, "����� �λ�");
			return CL_warning;
		case 3:
			sprintf_s(string_,30, "������ �λ�");
			return CL_good;
		case 4:
			sprintf_s(string_,30, "���� ������");
			return CL_dark_good;
		}
		return CL_none;
	}
	default:
		return CL_none;
	}
	return CL_none;
}

shadow::shadow(const coord_def &c, textures *t, int original_id_, shadow_type type_, string name_)
{
	position = c;
	image = t;
	type = type_; 
	original_id = original_id_; 
	if (type_ == SWT_MONSTER && original_id_ >= 0 && original_id_<MON_MAX &&
		mondata[original_id_].flag & M_FLAG_UNHARM) 
	{
		unharm = true;
	}
	else
	{
		unharm = false;
	}
	name = name_;
};




void shadow::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, texturetoint(image));
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<shadow_type>(fp, type); 
	SaveData<int>(fp, original_id);
	SaveData<bool>(fp, unharm);
	
	char temp[100];
	sprintf_s(temp, 100,"%s",name.c_str());
	SaveData<char>(fp,*temp, strlen(temp)+1);
}
void shadow::LoadDatas(FILE *fp)
{
	int it;
	LoadData<int>(fp, it);
	image = inttotexture(it);
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<shadow_type>(fp, type);
	LoadData<int>(fp, original_id);
	LoadData<bool>(fp, unharm);
	char temp[100];
	LoadData<char>(fp, *temp);
	name = temp;
}


coord_def inttodirec(int direc, int x_, int y_)
{
	int x=x_,y=y_;
	if(direc>=1 && direc<4)
		x += 1;
	else if(direc>=5 && direc<8)
		x -= 1;
	
	if(direc<2 || direc >=7)
		y -= 1;
	else if(direc>=3 && direc < 6)
		y += 1;
	return coord_def(x,y);
}