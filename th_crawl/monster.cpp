//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: monster.cpp
//
// 내용: 몹의 함수정의
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







coord_def inttodirec(int direc, int x_=0, int y_=0);


monster::monster() 
: map_id(-1), id(0), level(1), exper(0), name("없음",true), image(NULL),  hp(0), hp_recov(0), max_hp(0), prev_position(0,0), prev_sight(false),
ac(0), ev(0), flag(0), resist(0), sense(0), s_poison(0),poison_reason(PRT_NEUTRAL),s_tele(0), s_might(0), s_haste(0), s_confuse(0), s_slow(0),s_frozen(0) ,s_ally(0),
s_elec(0), s_paralyse(0), s_glow(0), s_graze(0), s_silence(0), s_silence_range(0), s_sick(0), s_veiling(0), s_value_veiling(0), s_invisible(0),s_saved(0), s_mute(0), s_catch(0),
s_ghost(0),
s_fear(0), s_mind_reading(0), s_lunatic(0), s_neutrality(0), s_communication(0), s_exhausted(0),
	summon_time(0), summon_parent(PRT_NEUTRAL),poison_resist(0),fire_resist(0),ice_resist(0),elec_resist(0),confuse_resist(0), time_delay(0), 
	speed(10), memory_time(0), first_contact(true), delay_turn(0), target(NULL), temp_target_map_id(-1), target_pos(), 
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
	SaveData<int>(fp, s_poison);	
	SaveData<parent_type>(fp, poison_reason);
	SaveData<int>(fp, s_tele);
	SaveData<int>(fp, s_might);
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
	SaveData<int>(fp, summon_time);
	SaveData<parent_type>(fp, summon_parent);
	SaveData<int>(fp, poison_resist);
	SaveData<int>(fp, fire_resist);
	SaveData<int>(fp, ice_resist);
	SaveData<int>(fp, elec_resist);
	SaveData<int>(fp, confuse_resist);
	SaveData<int>(fp, time_delay);
	SaveData<int>(fp, speed);
	SaveData<int>(fp, memory_time);
	SaveData<bool>(fp, first_contact);	
	SaveData<int>(fp, delay_turn);
	//SaveData<int>(fp, will_move); //구현힘듬
	//SaveData<int>(fp, target);  //마찬가지이유
	//temp_target_map_id 이 변수는 저장할 필요가 없다.
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
	LoadData<int>(fp, s_poison);
	LoadData<parent_type>(fp, poison_reason);
	LoadData<int>(fp, s_tele);
	LoadData<int>(fp, s_might);
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
	LoadData<int>(fp, summon_time);
	LoadData<parent_type>(fp, summon_parent);
	LoadData<int>(fp, poison_resist);
	LoadData<int>(fp, fire_resist);
	LoadData<int>(fp, ice_resist);
	LoadData<int>(fp, elec_resist);
	LoadData<int>(fp, confuse_resist);
	LoadData<int>(fp, time_delay);
	LoadData<int>(fp, speed);
	LoadData<int>(fp, memory_time);
	LoadData<bool>(fp, first_contact);	
	LoadData<int>(fp, delay_turn);
	//LoadData<int>(fp, will_move);
	//LoadData<int>(fp, target); 타겟 변수는 여기서 호출하진 않는다.
	LoadData<int>(fp, temp_target_map_id);
	sm_info.LoadDatas(fp);


	LoadData<int>(fp, target_pos.x);
	LoadData<int>(fp, target_pos.y);
	LoadData<int>(fp, direction);
	base_state_setup(state,MS_NORMAL);
	monster_state ms_;
	LoadData<monster_state>(fp, ms_);
	state.SetState(ms_);
	int size_=0;
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		spell temp;
		LoadData<spell>(fp, temp);
		spell_lists.push_back(temp);
	}
	LoadData<bool>(fp, random_spell);	
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
	prev_sight = false;
	ac = 0;
	ev = 0;
	flag = 0;
	resist = 0;
	sense = 0;
	s_poison = 0;
	poison_reason = PRT_NEUTRAL;
	s_tele = 0;
	s_might = 0;
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
	summon_time = 0;
	summon_parent = PRT_NEUTRAL;
	poison_resist = 0;
	fire_resist = 0;
	ice_resist = 0;
	elec_resist = 0;
	confuse_resist = 0;
	time_delay = 0;
	speed = 0; 
	memory_time = 0; 
	first_contact = true;
	delay_turn = 0;
	while(!will_move.empty())
		will_move.pop();
	target = NULL;
	temp_target_map_id = -1;
	target_pos.x = 0;
	target_pos.y = 0;
	direction =0;
	state.SetState(MS_SLEEP);
	spell_lists.clear();
	random_spell = false;
}
bool monster::SetMonster(int map_id_, int id_, int flag_, int time_, coord_def position_, bool init_)
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
		SetXY(position_);
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
	}
	SetResistMonster(this);

	if(flag & M_FLAG_CONFUSE)
		s_confuse = 10;
	if(flag & M_FLAG_INVISIBLE)
		s_invisible = -1;
	
	SetSpell((monster_index)id_, &spell_lists,&random_spell);
	return true;
}	
bool monster::ChangeMonster( int id_, int flag_)
{
	float hp_per_ = (float)(hp) / max_hp;
	bool summon_ = (flag & M_FLAG_SUMMON)?true:false;
	SetMonster(map_id,id_,flag_,summon_time,position,false);
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
		if(you.god == GT_SATORI && !you.punish[GT_SATORI] && pietyLevel(you.piety)>=2  &&  id != MON_KOISHI)
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
					int x_ = randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
					if(env[current_level].isMove(x_,y_,isFly(), isSwim(), flag & M_FLAG_CANT_GROUND))
					{ //fly와 swim이 이 캐릭터 설정으로 되어있는건 이 캐릭터가 가볼수있는 위치였다. 라는것
						env[current_level].MakeMapping(coord_def(x_,y_),rand_int(min_size_,max_size_),false,percent_);
						break;
					}
					max_--;
				}
			}
			
		}
	}
	if(wiz_list.wizard_mode)
	{		
		char temp[200];
		float percent_=1.0f, detect_ = you.GetStealth()==-1?1.0f:((float)GetDetect()+1)/(you.GetStealth()+1);
		if(detect_<0 || detect_>1.0f)
			detect_ = 1.0f;
		int length__ = max(abs(you.position.x-position.x),abs(you.position.y-position.y));
		for(int i = 0; i < length__; i++)
			percent_ *= 1.0f-detect_;
		sprintf_s(temp,200,"들킬확률-RandB(%d,%d) 즉%f%% (최종 암살 성공율%f%%)",you.GetStealth(),GetDetect(),100.0f*detect_, percent_*100.0f);
		printlog(temp,true,false,false,CL_danger);
	}

	first_contact = false;
}
void monster::TurnSave()
{
	delay_turn = you.turn;
}
void monster::TurnLoad()
{ //나중에 주인공 근처로 옮겨오는것도 생각한다.
	int temp_turn = you.turn-delay_turn;
	if(s_poison-temp_turn>0)
		s_poison-=temp_turn;
	else
		s_poison = 0;

	if(s_might-temp_turn>0)
		s_might-=temp_turn;
	else
		s_might = 0;

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

	if(s_fear-temp_turn>0)
		s_fear-=temp_turn;
	else
		s_fear =0;
	
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
	else
		s_exhausted =0;

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
	if(position.x == x_ && position.y == y_)
		return;
	if(s_silence)
		env[current_level].MakeSilence(position, s_silence_range, false);
	if(s_catch)
		you.SetCatch(NULL);
	position.set(x_,y_);
	for(auto it = env[current_level].floor_list.begin(); it != env[current_level].floor_list.end();it++)
	{
		if(it->position == position)
			it->onWalk(this);
	}
	if(s_silence)
		env[current_level].MakeSilence(position, s_silence_range, true);
}
void monster::SetXY(coord_def pos_)
{
	SetXY(pos_.x,pos_.y);
}
void monster::LevelUpdown(int level_, float hp_, float atk_)
{

	//레벨다운은 나중에 구현해본다.
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
void monster::CheckSightNewTarget()
{
	if(isUserAlly())
	{		
		if(target && !target->isplayer())
		{//적이 이미 있는 경우
			if(target->isLive() && isEnemyMonster((monster*)target))
				return;	//해당적이 죽지않았으면서 적몬스터이면 구지 바꿀 필요가 없다. 
		}

					
		{ //여기부터 시야내 몬스터찾기 시작

			vector<monster>::iterator it;
			it = env[current_level].mon_vector.begin();
			for(int i=0;i<MON_MAX_IN_FLOOR && it != env[current_level].mon_vector.end() ;i++,it++)
			{
				if((*it).isLive() && isEnemyMonster(&(*it)) && (*it).isView(this) && ((env[current_level].isInSight((*it).position) && (flag & M_FLAG_SUMMON) ) || isMonsterSight((*it).position)) )
				{
					if(!(flag & M_FLAG_SUMMON) || env[current_level].isInSight(position) )
					{
						FoundTarget(&(*it),30);
						break;
					}
				}
			}
		}
	}
	else
	{
		unit* prev_target_ = target;
		int distant_ = 999;//적일땐 거리가 중요하다.
		if(target)
		{//적이 이미 있는 경우
			if(!target->isplayer())
			{
				if(target->isLive() && isEnemyMonster((monster*)target))
				{
					distant_ = distan_coord(target->position, position);	//해당적이 죽지않았으면서 적몬스터이면 구지 바꿀 필요가 없다. 
					distant_ = max(1,distant_-1); //뭔가에 막혀있으면 우선순위가 낮아짐 구현하기
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

		{ //여기부터 시야내 몬스터찾기 시작
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



		if(env[current_level].isInSight(position) && you.isView(this) && !you.s_timestep)
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
			FoundTarget(prev_target_,30);
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
	if(!isView() && you.hp > 0)
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
	case ATT_COLD:
	case ATT_S_POISON:
	case ATT_M_POISON:
	case ATT_SICK:
	case ATT_THROW_NORMAL:
	case ATT_VAMP:
	case ATT_CURSE:
	case ATT_WEATHER:
	case ATT_AUTUMN:
	case ATT_CHOAS:
	case ATT_CLOUD_NORMAL:
	case ATT_VEILING:
	case ATT_RUSH:
	case ATT_WALL:
	case ATT_NORMAL_HIT:
	case ATT_NORMAL_BLAST:
	case ATT_FIRE_BLAST:
	case ATT_COLD_BLAST: 
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
	case ATT_ELEC:
	case ATT_THROW_ELEC:
		damage_ *= GetElecResist();
		break;
	case ATT_CLOUD_FIRE:
	case ATT_CLOUD_COLD:
	case ATT_THROW_NONE_MASSAGE:
	case ATT_STONE_TRAP:
	case ATT_SMITE:
	case ATT_BLOOD:
	case ATT_BURST:
		break;
	}
	switch(type_)
	{
	case ATT_FIRE:
		bonus_damage = damage_*0.25f;
		damage_ -= bonus_damage;
		bonus_damage *= GetFireResist();
		break;
	case ATT_COLD:
		bonus_damage = damage_*0.25f;
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
	case ATT_CLOUD_FIRE:
	case ATT_FIRE_BLAST:
	case ATT_COLD_BLAST: 
		damage_ *= GetFireResist();
		break;
	case ATT_THROW_COLD:
	case ATT_CLOUD_COLD:
	case ATT_THROW_FREEZING:
		damage_ *= GetColdResist();
		break;
	case ATT_THROW_WEAK_POISON:
	case ATT_THROW_MIDDLE_POISON:
	case ATT_THROW_STRONG_POISON:
		damage_ *= GetPoisonResist()>0?0.5:(GetPoisonResist()<0?1.5:1);
		break;
	case ATT_FIRE_PYSICAL_BLAST:
		damage_ = damage_/2.0f + damage_*GetFireResist()/2.0f;
		break;
	case ATT_COLD_PYSICAL_BLAST:
		damage_ = damage_/2.0f + damage_*GetColdResist()/2.0f;
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
		default:
			if(a.order)
				printarray(false,false,false,CL_normal,6,name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),"에게 명중했다.");
			break;
		case ATT_FIRE:
			if(a.order)
				printarray(false,false,false,CL_normal,6,name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),"에게 명중하고 불타올랐다.");
			break;
		case ATT_COLD:
			if(a.order)
				printarray(false,false,false,CL_normal,6,name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),"에게 명중하고 얼어붙었다.");
			break;
		case ATT_NORMAL_HIT:			
			if(a.order)
				printarray(false,false,false,CL_normal,6,name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),"에게 들어갔다.");
			break;
		case ATT_SMITE:
			if(a.order)
			{
				printarray(false,false,false,CL_normal,4,"무엇인가 ",GetName()->name.c_str(),GetName()->name_to(true),"강타했다.");
			}
			break;
		case ATT_BLOOD:	
			if(a.order)
			{
				printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"의 피가 터져나왔다.");
			}
			break;
		case ATT_NOISE:
			if(a.order)
			{
				printarray(false,false,false,CL_normal,3,"굉음이 ",GetName()->name.c_str(),"의 달팽이관을 강타했다.");
			}
			break;
		case ATT_CLOUD_FIRE:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"화염에 휩싸였다.");
			break;
		case ATT_CLOUD_COLD:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"얼어붙었다.");
			break;			
		case ATT_STONE_TRAP:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"뾰족한 바위를 밟았다.");
			break;			
		case ATT_FIRE_BLAST:
		case ATT_COLD_BLAST: 
		case ATT_NORMAL_BLAST:
		case ATT_AC_REDUCE_BLAST:
		case ATT_FIRE_PYSICAL_BLAST:
			if(a.order)
			{
				printarray(false,false,false,CL_normal,4,GetName()->name.c_str(),GetName()->name_is(true),a.name.name.c_str(),"의 폭발에 휘말렸다.");
			}
			break;
		case ATT_COLD_PYSICAL_BLAST:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"눈보라에 휘말렸다.");
			break;			
		case ATT_BURST:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"폭발했다.");
			break;
		case ATT_CLOUD_NORMAL:
			break;
		case ATT_VEILING:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"바람 갑옷에 베였다.");
			break;
		case ATT_RUSH:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"맞았다.");
			break;
		case ATT_WALL:			
			if(a.order)
			{
				printarray(false,false,false,CL_normal,5,GetName()->name.c_str(),GetName()->name_is(true),name_.name.c_str(),name_.name_and(true),"부딪혔다.");
			}
			else
			{
				printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"벽에 부딪혔다.");
			}
			break;
		case ATT_ELEC:
			if(!GetElecResist())
				break;
		case ATT_THROW_ELEC:
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"감전되었다.");
			break;
		case ATT_THROW_NONE_MASSAGE:
			break;
		}
	}
	else
	{
		if(a.order)
		{
			switch(a.order->GetAttackType())
			{	
			case AWT_SHORTBLADE:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"뒤에서 꿰뚫었다.");
				break;
			case AWT_LONGBLADE:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"뒤에서 잘라냈다.");
				break;
			case AWT_MACE:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"뒤에서 내리쳤다.");
				break;
			case AWT_AXE:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"뒤에서 찍었다.");
				break;
			case AWT_SPEAR:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),name.name.c_str(),name.name_to(true),"뒤에서 꿰뚫었다.");
				break;
			case AWT_UNARMOUR:
			case AWT_NONE:
			default:
				printarray(false,false,false,CL_normal,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"뒤에서 기습했다.");
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
	case ATT_COLD:
	case ATT_S_POISON:
	case ATT_M_POISON:
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
		printlog("그러나 아무런 데미지도 주지 못했다",true,false,false,CL_normal);
		break;
	case ATT_CLOUD_FIRE:
	case ATT_CLOUD_COLD:
	case ATT_CLOUD_NORMAL:
	case ATT_ELEC:
	case ATT_VEILING:
	case ATT_RUSH:
	case ATT_WALL:
	case ATT_THROW_NONE_MASSAGE:
	case ATT_STONE_TRAP:
		break;
	}
}

bool monster::damage(attack_infor &a, bool perfect_)
{
	int back_stab = 0;
	if(a.type < ATT_THROW_NORMAL)
	{ //백스탭레벨  3-맥스데미지 2-간간히 크리데미지 1-아주 드문 크리데미지
		if(state.GetState() == MS_SLEEP || state.GetState() == MS_REST)
			back_stab = 3;
		else if(s_confuse || s_fear || s_paralyse)
			back_stab = 2;
		else if(a.order && !(a.order)->isView(this))
		{ //투명일때 조건
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
		back_stab = 2; //간파시 암습가능
	if(back_stab == 2 && randA(3))
		back_stab = 0; //75%의 확률로 2레벨 암습은 실패
	if(back_stab == 1 && randA(9))
		back_stab = 0; //90% 1레벨 암습은 실패



	int damage_ = calculate_damage(a.type,a.damage,a.max_damage, back_stab);
	int accuracy_ = a.accuracy;
	bool sight_ = isYourShight();
	bool graze_ = false;
	



	if(s_graze && randA(5) == 0)
	{
		if(a.type >= ATT_THROW_NORMAL && a.type < ATT_THROW_LAST)
			graze_ = true;
	}


	if(s_glow)
		accuracy_+=5; //빛날경우 명중 증가
	if(GetMindReading() && a.order == &you)
		accuracy_+=10; //간파당했다.
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


	if(wiz_list.wizard_mode)
	{		
		if(damage_>0)
		{
			char temp[50];
			sprintf_s(temp,50,"실데미지-%d 공격-%d 암습-%d 명중-%d 명중률-%d%%",damage_,a.damage,a.max_damage,a.accuracy,percent_);
			printlog(temp,true,false,false,CL_help);
		}
	}

	if((randA(100) <= percent_ && !graze_) || back_stab == 3 || perfect_)
	{
		if(s_saved){
			auto it = env[current_level].mon_vector.begin();
			for( ;it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && it->isSaveSummoner(this))
				{
					if(sight_)
					{
						char temp[128];
						sprintf_s(temp,128,"%s%s %s%s 감쌌다!",it->GetName()->name.c_str(),it->GetName()->name_is(), GetName()->name.c_str(),GetName()->name_to());
						printlog(temp,true,false,false,CL_magic);
					}
					PositionSwap(&(*it));
					return it->damage(a,perfect_);
					break;
				}
			}
		}

		if(sight_)
		{
			print_damage_message(a, back_stab);
		}
		
		if(damage_)
		{
			enterlog();
			hp-=damage_;
			if(damage_/3 > 0 && a.type == ATT_VAMP && randA(2) == 0)
			{
				if(a.order)
				{
					a.order->HpUpDown(damage_/3,DR_EFFECT);	
					if(sight_)
						printarray(true,false,false,CL_normal,4,a.order->GetName()->name.c_str(),a.order->GetName()->name_is(true), GetName()->name.c_str(),"의 체력을 흡수했다.");
			
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
					a.order->damage(attack_infor(randA_1(s_value_veiling),s_value_veiling,99,NULL,GetParentType(),ATT_VEILING,name_infor("베일링",true)), true);
					s_veiling = 0;
					s_value_veiling = 0;
				}
			}
			if(hp<=0)
			{
				if(a.order)
				{
					if(sight_)
						printarray(true,false,false,CL_danger,5,name_.name.c_str(),name_.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"죽였다.");
					else if(a.p_type == PRT_PLAYER || a.p_type == PRT_ALLY)
					{
						printlog("경험이 증가하는 것을 느꼈다.",true,false,false,CL_normal);
						if(!isView() && env[current_level].isInSight(position) && (you.auto_pickup==0))
							auto_pick_onoff(true);
					}
				}

				dead(a.p_type, !(a.order));
			}

		}
		else
		{
			if(sight_)
				print_no_damage_message(a);
		}
		//독은 데미지를 주지않아도 들어가야함
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


		
		AttackedTarget(a.order);
	}
	else
	{
		if(a.order && sight_)
		{			
			if(!graze_)
				printarray(true,false,false,CL_bad,7,name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"빗나갔다.");
			else
				printarray(true,false,false,CL_bad,7,name_.name.c_str(),"의 ",a.name.name.c_str(),a.name.name_is(true),GetName()->name.c_str(),GetName()->name_to(true),"그레이즈되었다.");
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
	return_ = image->draw(pSprite, x_, y_,id == MON_ENSLAVE_GHOST?128:255);
	if(return_)
	{
		if(monster_state_simple state_ = GetSimpleState())
		{
			if(statetotexture(state_))
				return_ = statetotexture(state_)->draw(pSprite,x_,y_,255);
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
		env[current_level].isMove(position.x+x_mov,position.y+y_mov,isFly(), isSwim(), false/*flag & M_FLAG_CANT_GROUND*/))
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
				if(((*it).isEnemyMonster(this) || s_confuse)) //적일때
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
				else
				{
					if((*it).isAllyMonster(this))
					{
						return 0;
					}
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
	else if(env[current_level].isDoor(position.x+x_mov,position.y+y_mov) && flag & M_FLAG_OPEN_DOOR )
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
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"문을 열었다.");
				}
				else
				{
					printlog("문이 열렸다.",true,false,false,CL_normal);
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
		if(randA(30)==1)
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
		random_shuffle(dq.begin(),dq.end());
		for(int i=0;i<8;i++)
		{
			if(env[current_level].isMove(inttodirec(dq[i],position.x,position.y),isFly(), isSwim(), flag & M_FLAG_CANT_GROUND)) //나는 몹은 2번째인자
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

	if(!only_move && !s_confuse && !s_mute && !s_fear && !s_lunatic)
	{
		if(target && target->position == target_pos)
		{
			list<spell>::iterator it = spell_lists.begin();
			for(;it != spell_lists.end();it++)
			{
				if(randA_1(100)<=it->percent)
				{
					if(isMonSafeSkill((spell_list)it->num,this,target_pos))
					{
						if(SpellFlagCheck((spell_list)it->num,S_FLAG_SPEAK) && flag & M_FLAG_SPEAK)
						{
							if(env[current_level].isSilence(position))
								continue;
							enterlog();
							char* c_ = Get_Speak(id,this,MST_MAGIC);
							if( c_  && (env[current_level].isInSight(position)))
								printlog(c_,true,false,false,CL_magic);
						}
						if(MonsterUseSpell((spell_list)it->num,false,this,SpellFlagCheck((spell_list)it->num,S_FLAG_IMMEDIATELY)?position:target_pos))
						{
							Noise(position,SpellNoise((spell_list)it->num),this);
							return true;
						}
					}
				}			
			}
		}
	}

	if(flag & M_FLAG_LEADER_SUMMON && flag & M_FLAG_SUMMON )
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
			move_ = MoveToPos(position+coord_def(x_,y_), only_move);
			if(!move_)
			{
				s_fear = 0;
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
			{ //벽에 막히면 8방향 랜덤으로 방향틈
				deque<int> dq;
				for(int i=0;i<8;i++)
					dq.push_back(i);
				random_shuffle(dq.begin(),dq.end());
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
bool monster::dead(parent_type reason_, bool message_, bool remove_)
{
	bool sight_ = false;
	if(isYourShight())
		sight_ = true;
	if(s_silence)
		env[current_level].MakeSilence(position, s_silence_range, false);
	if(s_catch)	
		you.SetCatch(NULL);
	if(message_ && !remove_)
	{
		if(sight_)
			printarray(false,false,false,CL_danger,3,GetName()->name.c_str(),GetName()->name_is(true),"죽었다. ");
		else if((reason_ == PRT_PLAYER || reason_ == PRT_ALLY) && !(flag & M_FLAG_SUMMON))
		{
			printlog("경험이 증가하는 것을 느꼈다.",true,false,false,CL_normal);
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
			if(you.god_value[0] == map_id && you.god_value[1] == current_level)
			{
				char temp[200];
				sprintf_s(temp,200,"%s%s죽었다.",name.name.c_str(),name.name_do(true));
				AddNote(you.turn,CurrentLevelString(),temp,CL_yuyuko);
				you.god_value[0] = 0;
				you.god_value[1] = 0;
			}
			else
			{
				char temp[200];
				sprintf_s(temp,200,"you god_value(%d, %d) mon value(%d, %d)",
					you.god_value[0] ,you.god_value[1],
					map_id, current_level);
				printarray(true,false,false,CL_danger,3,"※영혼구속 버그 : ",GetName()->name.c_str(), temp);
			}
		}
	}


	if(!(flag & M_FLAG_SUMMON) && !remove_)
	{
		if(reason_ == PRT_PLAYER) //플레이어가 죽였다.
		{
			you.GetExp(exper);
		}
		else if(reason_ == PRT_ALLY) //동맹이 죽였다.
		{
			you.GetExp(exper/*(exper+1)/2*/); //더이상 동맹으로 경험치 절반은 되지않는다.
		}
		if(!randA(1))
		{
			item_infor temp;
			env[current_level].MakeItem(position,makePitem((monster_index)id, 1, &temp));
		}
		if(id == MON_MAGIC_BOOK)
		{
			item_infor t;
			item *it2;
			it2 = env[current_level].MakeItem(position,makeCustomBook(&t));
			list<spell>::iterator it = spell_lists.begin();
			if(it != spell_lists.end()){
				it2->value1 = it->num;
				it++;
			}
			if(it != spell_lists.end()){
				it2->value2 = it->num;
				it++;
			}
			if(it != spell_lists.end()){
				it2->value3 = it->num;
				it++;
			}
		}
	}
	if(flag & M_FLAG_UNIQUE && !remove_)
	{
		if(reason_ == PRT_PLAYER || reason_ == PRT_ALLY)
		{
			char temp[200];
			sprintf_s(temp,200,"네임드 %s%s 죽였다.",name.name.c_str(),name.name_to());
			AddNote(you.turn,CurrentLevelString(),temp,CL_normal);
		}
		else
		{
			char temp[200];
			sprintf_s(temp,200,"네임드 %s%s 죽었다.",name.name.c_str(),name.name_to());
			AddNote(you.turn,CurrentLevelString(),temp,CL_normal);

		}
	}
	if(!remove_)
		GodAccpect_KillMonster(this,reason_);
	return true;
}
int monster::action(int delay_)
{	
	bool is_sight = false;
	if(env[current_level].isInSight(position))
	{
		if(first_contact)
			FirstContact();
		is_sight = true; //현재 눈에 보이는지
	}
	else
	{
		if(you.god == GT_SATORI && !you.punish[GT_SATORI] && pietyLevel(you.piety)>=3 &&
			GetPositionGap(position.x, position.y, you.position.x, you.position.y) <= satori_sight())
		{
			env[current_level].magicmapping(position.x,position.y);
			env[current_level].ClearShadow(position, SWT_MONSTER);
		}
	}




	time_delay+=delay_ * rand_int(9,11) / 10; //움직임 randomizing
	if(flag & M_FLAG_CONFUSE)
		s_confuse = 10;
	if(flag & M_FLAG_SUMMON && summon_time>=0)
	{
		if((summon_time--)<=0)
		{
			hp = 0;
			env[current_level].MakeSmoke(position, img_fog_normal, SMT_NORMAL, 4, 0, this);
			if(is_sight)
				printarray(true,false,false,CL_bad,3,GetName()->name.c_str(),GetName()->name_is(true),"연기 속으로 사라졌다.");
			
			env[current_level].SummonClear(map_id);
			return 0;
		}
	}

	while(time_delay>GetSpeed())
	{
		if(s_poison)
		{
			if(poison_percent(s_poison))
			{
				hp -= randA_1(3)*poison_damage(s_poison);
				if(hp<=0)
				{
					dead(poison_reason, true); //아직 플레이어의 독은 없다.
					return 1;
				}
			}
			s_poison-=randA_1(3);
			if(s_poison<0)
				s_poison = 0;
			if(is_sight && isView())
			{
				if(!s_poison)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"독에서 회복되었다.");
			}
		}	

		if(s_might)
		{
			s_might--;
			if(is_sight && isView())
			{
				if(!s_might)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더 이상 힘이 강하지 않다.");
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
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더 이상 빠르지 않다.");
			}
		}

		
		if(s_confuse)
		{
			s_confuse--;
			if(is_sight && isView())
			{
				if(!s_confuse)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"혼란스러움을 떨쳐냈다.");
			}
		}
		if(s_slow)
		{
			s_slow--;
			if(is_sight && isView())
			{
				if(!s_slow)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더 이상 느리지 않다.");
			}
		}
		if(s_frozen)
		{
			s_frozen--;
			if(is_sight && isView())
			{
				if(!s_frozen)
					printarray(true,false,false,CL_normal,2,GetName()->name.c_str(),"의 얼음이 녹았다.");
			}
		}	
		if(s_ally>0)
		{
			s_ally--;
			if(is_sight && isView())
			{
				if(!s_ally)
						printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더이상 매료상태가 아니다.");
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
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"방전을 멈췄다.");
			}
		}
		if(s_paralyse)
		{
			s_paralyse--;
			if(is_sight && isView())
			{
				if(!s_paralyse)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"다시 움직일 수 있게 되었다.");
			}
		}
		if(s_glow)
		{
			s_glow--;
			if(is_sight && isView())
			{
				if(!s_glow)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"빛나는 것을 멈췄다.");
			}
		}
		if(s_graze>0)
		{
			s_graze--;
			if(is_sight && isView())
			{
				if(!s_graze)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더 이상 그레이즈를 하지 않는다.");
			}
		}
		if(s_sick)
		{
			s_sick--;
			if(is_sight && isView())
			{
				if(!s_sick)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더 이상 아프지 않다.");
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
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_to(true),"감싸는 정적이 사라졌다.");
			}
		}
		if(s_veiling)
		{
			s_veiling--;
			if(is_sight && isView())
			{
				if(!s_veiling)
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_to(true),"휘감던 바람이 사라졌다.");
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
						printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_to(true),"투명이 풀렸다.");
					else
					{
						printarray(true,false,false,CL_small_danger,3,GetName()->name.c_str(),GetName()->name_to(true),"투명이 풀리면서 모습을 드러냈다.");
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
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더 이상 벙어리가 아니다.");
				}
			}
		}
		
		if(s_fear)
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
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더 이상 영혼이 붙잡혀있지않다.");
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
					printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더 이상 미치지 않았다.");
				}
			}
		}

		if(s_exhausted)
		{
			s_exhausted--;
		}






		if(s_communication)
		{
			s_communication--;
			if(!s_communication)
			{
				s_exhausted = rand_int(40,50);
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
						if(temp_>49 && env[current_level].isMove(check_pos_.x, check_pos_.y, false) && (!target->isplayer() || env[current_level].isInSight(check_pos_)) 
							&& target->isSightnonblocked((*rit)))
						{

							if(monster* mon_=BaseSummon(MON_HELL_HOUND, rand_int(20,30), false, false, 2, this, check_pos_, SKD_OTHER, -1))
							{
								mon_->SetExhausted(rand_int(5,50));
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
				printarray(true,false,false,CL_magic,3,GetName()->name.c_str(),GetName()->name_is(true),"동료를 끌어모으고 있다.");
			}
		}
		else if(!s_paralyse)
		{
			if(target) //투명몹을 상대할때
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

			if(state.GetState() == MS_ATACK && isUserAlly() && target == &you)
			{
				state.SetState(MS_FOLLOW);
			}
			if((flag & M_FLAG_SUMMON)  && isUserAlly() && !env[current_level].isInSight(target_pos) )
			{
				state.SetState(MS_FOLLOW);

			}

			switch(state.GetState())
			{
			case MS_NORMAL:
				longmove();
				if(randA(9)) //보통은 플레이어만 찾는다.(빠른 처리를 위해)
					sightcheck(is_sight);
				else
					CheckSightNewTarget();
				break;
			case MS_SLEEP:
			case MS_REST:
				if(isUserAlly())
				{
					state.SetState(MS_FOLLOW);
					break;
				}
				target = NULL;
				if(is_sight && you_detect())//시야 안에 있을때 스텔스 체크
				{
					FoundTarget(&you,30);
					int percent_ = 1;
					if(you.god == GT_SHIZUHA && !you.punish[GT_SHIZUHA] )
						percent_ = 4;
					if(flag & M_FLAG_SPEAK && randA(percent_)==0 && (env[current_level].isInSight(position)) && !env[current_level].isSilence(position))
					{
						if(char* c_ = Get_Speak(id,this,MST_FOUND)){
							printlog(c_,true,false,false,CL_speak);
							Noise(position,5,this);
						}
					}	
				}
				break;
			case MS_ATACK:
				if(isUserAlly() && target && memory_time)
				{
					target_pos = target->position;
				}
				if(you.s_timestep && (target == &you || !target) && !isUserAlly())
				{
					memory_time = 0;
					target = NULL;						
					state.StateTransition(MSI_LOST);
				}
				else if(is_sight && you.isView(this) && !isUserAlly())
				{ //적인데 시야 안에 있으면서 플레이어가 보이는 상태
					CheckSightNewTarget();
					//FoundTarget(&you,30);
					if(flag & M_FLAG_SUMMON && you.god == GT_SHINKI && !you.punish[GT_SHINKI] && pietyLevel(you.piety)>=3)
					{
						//신키는 소환수를 방해한다.
						if(randA(1))
							break;
					}

					if(flag & M_FLAG_SPEAK && (env[current_level].isInSight(position)) && !env[current_level].isSilence(position) && randB(1000,(flag & M_FLAG_UNIQUE)?33:3)){//몬스터 말하기
						
						if(s_confuse || s_lunatic)
						{
							if(char* c_ = Get_Speak(id,this,MST_CONFUSE))
								printlog(c_,true,false,false,CL_speak);	
						}
						else
						{
							if(char* c_ = Get_Speak(id,this,MST_NORMAL))
								printlog(c_,true,false,false,CL_speak);	
						}
					}

				}
				else if(!isUserAlly())
				{//적인데 시야안에 없거나 플레이어가 보이지 않는 상태
					if(memory_time>0)
					{
						CheckSightNewTarget();
						memory_time--;
					}
					else
					{
						target = NULL;
						state.StateTransition(MSI_LOST);
					}
				}
				else
				{
					memory_time=30;
				}
				atkmove(is_sight);
				if(!is_sight && env[current_level].isInSight(position))
				{ //플레이어를 발견하게된다.
					if(target == &you)
						FoundTarget(target,30);
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
			}
		}
		special_action(is_sight);
		time_delay-=GetSpeed();
		if(!isLive())
			break;
	}


	bool in_sight_ = env[current_level].isInSight(position);

	if(in_sight_)
		prev_sight = true;
	else if(prev_sight)
	{
		if(isView() && !(you.god == GT_SATORI && !you.punish[GT_SATORI] && pietyLevel(you.piety)>=3 &&
			GetPositionGap(position.x, position.y, you.position.x, you.position.y) <= satori_sight()))
			env[current_level].MakeShadow(prev_position,image);
		prev_sight = false;
	}
	



	prev_position = position;
	return 0;
}
void monster::sightcheck(bool is_sight_)
{	
	if(!isUserAlly() )
	{
		if(is_sight_ && you_detect())//시야 안에 있을때 스텔스 체크
		{
			FoundTarget(&you,30);
		}
	}
}

void monster::special_action(int delay_)
{

	switch(id)
	{
	case MON_RUMIA:
		for(int i = -1;i<2;i++)
			for(int j = -1;j<2;j++)
				env[current_level].MakeSmoke(coord_def(i+position.x,j+position.y),img_fog_dark,SMT_DARK,rand_int(3,4),0,this);
		break;
	case MON_FIRE_CAR:
		if(!isUserAlly())
		{
			for(int i = -1;i<2;i++){
				for(int j = -1;j<2;j++){
					if(i!=0 || j!=0)
						env[current_level].MakeSmoke(coord_def(i+position.x,j+position.y),img_fog_fire,SMT_FIRE,1,0,this);
				}
			}
		}
		break;
	case MON_YAMAME:
		if(env[current_level].isInSight(position) && randA(2) == 0 && !isArena() && !isUserAlly())
		{
			you.SetSick(10);
		}
		break;
	case MON_TEWI:
		if(env[current_level].isInSight(position) && hp<max_hp/2 && randA(3) == 0 && !isUserAlly())
		{
			SetFear(rand_int(20,40));
		}
		break;
	case MON_CLOWNPIECE:
		if(env[current_level].isInSight(position) && !you.s_lunatic && randA(4) == 0 && !isArena() && !isUserAlly())
		{
			you.SetLunatic(rand_int(5,15));
		}
		break;
	case MON_RED_UFO:
	case MON_GREEN_UFO:
	case MON_BLUE_UFO:
		if(randA(10)==0){
			ChangeMonster(randA(2)?randA(1)?MON_RED_UFO:MON_GREEN_UFO:MON_BLUE_UFO,0);
		}
		break;
	case MON_SEKIBANKI:
		if(env[current_level].isInSight(position) && randA(2)==0 &&
			state.GetState() == MS_ATACK && !s_mute)
		{
			if(!env[current_level].isSilence(position)  && flag & M_FLAG_SPEAK){
				enterlog();
				char* c_ = Get_Speak(id,this,MST_MAGIC);
				if( c_  && (env[current_level].isInSight(position)))
					printlog(c_,true,false,false,CL_magic);
			}
			MonsterUseSpell(SPL_SUMMON_SEKIBANKI, false,this,target_pos,200);
			ChangeMonster(MON_SEKIBANKI_BODY,0);
		}
	case MON_SEKIBANKI_BODY:
		if(!(env[current_level].isInSight(position)) && randA(2)==0)
		{
			env[current_level].SummonClear(map_id);
			ChangeMonster(MON_SEKIBANKI,0);
		}
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"독에 걸렸다.");
		else
			printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"의 독은 심해졌다.");
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
			printarray(true,false,false,CL_normal,2,GetName()->name.c_str(),"의 주변 공간이 불안정해졌다.");
		}
		else
		{
			printarray(true,false,false,CL_normal,2,GetName()->name.c_str(),"의 주변 공간은 안정을 되찾았다.");
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
			printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"힘이 강해졌다.");
		}
		else
			printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"힘이 더욱 강해졌다.");
	}
	s_might += might_;
	if(s_might>100)
		s_might = 100;
	return true;
}
bool monster::SetClever(int clever_)
{
	return false;
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"빨라졌다.");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"빨라졌다.");
	}
	s_haste += haste_;
	if(s_haste>100)
		s_haste = 100;
	return true;
}
bool monster::SetConfuse(int confuse_)
{	
	if(!confuse_)
		return false;
	if(confuse_resist>0)
		return false;

	if(isYourShight())
	{
		if(!s_confuse)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"혼란스러워졌다.");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더욱 혼란스러워졌다.");
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"느려졌다.");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더욱 느려졌다.");
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"얼어붙어 움직임이 둔해졌다.");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더욱 얼어붙어 움직임이 둔해졌다.");
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"매료되었다.");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더욱 매료되었다.");
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"방전되고있다.");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"방전되고있다.");
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
		printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"마비되었다.");
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
bool monster::SetGlow(int glow_)
{
	if(!glow_)
		return false;
	if(isYourShight())
	{
		if(!s_glow)
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"빛나고있다.");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"더욱 빛나고있다.");
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"그레이즈를 하기 시작했다.");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"그레이즈를 하기 시작했다.");
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
			printarray(true,false,false,CL_small_danger,3,GetName()->name.c_str(),GetName()->name_is(true),"주변의 소리를 지웠다.");
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"병에 걸렸다.");
		else
			printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"의 병은 심해졌다.");
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"바람을 감쌌다.");
		else
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_to(true),"감싸는 바람이 강해졌다.");
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
				printarray(true,false,false,CL_normal,3,prev_name,prev_name_is,"투명하게 변한다.");
			else
				printarray(true,false,false,CL_normal,3,prev_name,prev_name_is,"더욱 투명하게 변한다.");
		}
		else
		{
			printarray(true,false,false,CL_small_danger,3,prev_name,prev_name_is,"투명해지면서 사라졌다.");
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
			printarray(false,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"벙어리가 되었다.");
		else
			printarray(false,false,false,CL_normal,2,GetName()->name.c_str(),"의 침묵이 길어졌다.");
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
	if(flag & M_FLAG_SUMMON)
	{
		printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true)," 이미 종속되어있다.");	
		return false;
	}
	if(isYourShight())
	{
		printarray(true,false,false,CL_yuyuko,2,GetName()->name.c_str(),"의 영혼이 붙잡혔다.");
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
	if(!fear_)
		return false;
	if(isYourShight())
	{
		if(!s_fear)
			printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"공포에 질렸다.");
	}
	s_fear += fear_;
	if(s_fear>50)
		s_fear = 50;
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
				printarray(true,false,false,CL_normal,2,GetName()->name.c_str(),"의 생각을 알게되어 친해졌다.");
			else
				printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"마음을 간파당했다.");
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
			printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"광기에 휩싸였다.");
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
				printarray(true,false,false,CL_magic,3,GetName()->name.c_str(),GetName()->name_is(true),"동료에 도움을 청하는 전파를 보내기 시작했다.");
				break;
			case MON_HELL_HOUND:
				printarray(true,false,false,CL_small_danger,2,GetName()->name.c_str(),"의 소리에 이끌려 또 다른 지옥개들이 몰려오기 시작한다.");
				break;
			default:
				printarray(true,false,false,CL_magic,3,GetName()->name.c_str(),GetName()->name_is(true),"동료를 끌어모으고 있다.");
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
			memory_time=30;
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
		int x_ = randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
		if(env[current_level].isMove(x_,y_,isFly(), isSwim(), flag & M_FLAG_CANT_GROUND) && !env[current_level].isMonsterPos(x_,y_))
		{
			env[current_level].MakeSmoke(position, img_fog_normal, SMT_NORMAL, 4, 0, this);
			SetXY(x_, y_);
			bool curr_sight_ = isYourShight();
			if(prev_sight_ && !curr_sight_)
				printarray(true,false,false,CL_normal,3,GetName()->name.c_str(),GetName()->name_is(true),"공간이동을 통해 시야에서 사라졌다.");
			else if(!prev_sight_ && curr_sight_)
				printarray(true,false,false,CL_small_danger,3,GetName()->name.c_str(),GetName()->name_do(true),"갑자기 나타났다.");

			return true;
		}
	}

}
int monster::GetResist()
{
	return 40+level * 5 + (resist+1) * 20;
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
	return randB(you.GetStealth(),GetDetect());
}
bool monster::isYourShight()
{
	return ((env[current_level].isInSight(position)) && isView());
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
	{ //이것은 중립탄환이다.
		if(flag & M_FLAG_PASSED_ENEMY)
			return true;
		else 
			return false;
	}
	else if(order == &you)
	{ //이것이 플레이어의 탄환일때
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
	{ //이것이 몬스터의 탄환일때
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

			if(length_ == 0) //시야가 다 달았다.
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
			return false; //공격불가능한 위치
		}
		else
			intercept = false;
	}
	return true;
}
bool monster::isMonsterSight(coord_def c)
{	
	bool intercept = false;
	for(int i=RT_BEGIN;i!=RT_END;i++)
	{
		int length_ = 8;
		beam_iterator it(position,c,(round_type)i);
		while(!intercept && !it.end())
		{
			if(length_ == 0) //시야가 다 달았다.
			{
				intercept = true;
				break;
			}
			if(!env[current_level].isSight((*it)))
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
			return false; //몬스터에게 보이지않는 위치
		}
		else
			intercept = false;
	}
	return true;
}
bool monster::CanChase()
{
	if(state.GetState() == MS_REST || state.GetState() == MS_SLEEP || state.GetState() == MS_NORMAL)
		return false;
	if(s_confuse)
		return false;
	if(s_mind_reading && s_ally && flag & M_FLAG_ANIMAL)
		return false;
	if( flag & M_FLAG_NONE_STAIR)
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
int monster::GetAttack(int num_, bool max_)
{
	int atk_ = randA(atk[num_]);
	if(max_)
		atk_ = atk[num_];
	if(s_lunatic || s_might)
		atk_ *= 1.5f;
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
			if(sm_info.parent_map_id == order->GetMapId() && randA(1)){
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
	return false;
}
float monster::GetFireResist()
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
float monster::GetColdResist()
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
float monster::GetElecResist()
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

monster_state_simple monster::GetSimpleState()
{
	monster_state_simple temp = MSS_NONE;

	if(state.GetState() == MS_NORMAL)
		temp = MSS_WANDERING;
	if(state.GetState() == MS_ATACK && target != &you)
		temp = MSS_WANDERING;
	if(s_haste)
		temp = MSS_HASTE;
	if(s_poison)
		temp = MSS_POISON;
	if(s_fear)
		temp = MSS_FEAR;
	if(s_confuse)
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
bool monster::GetStateString(monster_state_simple state_, char* string_)
{
	switch(state_)
	{
	case MSS_NONE:
		if(state.GetState() == MS_NORMAL)
		{
			return true;
		}
		else
			return false;
	case MSS_SLEEP:
		if(state.GetState() == MS_SLEEP)
		{
			sprintf(string_,"수면");
			return true;
		}
		else if(state.GetState() == MS_REST)
		{
			sprintf(string_,"휴식");
			return true;
		}
		else
			return false;
	case MSS_WANDERING:
		if(state.GetState() == MS_NORMAL)
		{
			sprintf(string_,"탐험중");
			return true;
		}
		else
			return false;
	case MSS_NO_NOTICE:
		if(state.GetState() == MS_ATACK && !isUserAlly() && target != &you)
		{
			sprintf(string_,"발각안됨");
			return true;
		}
		else
			return false;
	case MSS_CONFUSE:
		if(s_confuse)
		{
			sprintf(string_,"혼란");
			return true;
		}
		else
			return false;
	case MSS_POISON:
		if(s_poison)
		{
			sprintf(string_,"독");
			return true;
		}
		else
			return false;
	case MSS_SCARY:
		return false;
	case MSS_HASTE:
		if(s_haste && !s_slow)
		{
			sprintf(string_,"가속");
			return true;
		}
		else
			return false;
	case MSS_SLOW:
		if(s_slow && !s_haste)
		{
			sprintf(string_,"감속");
			return true;
		}
		else
			return false;
	case MSS_SMOKE_ABOVE:
		if(env[current_level].isSmokePos(position.x,position.y))
		{
			smoke* smoke_= env[current_level].isSmokePos2(position.x,position.y);
			sprintf(string_,smoke_->GetName());
			return true;
		}
		return false;
	case MSS_SUMMON:
		if(flag & M_FLAG_SUMMON)
		{
			sprintf(string_,"소환");
			return true;
		}
		return false;
	case MSS_FROZEN:
		if(s_frozen)
		{
			sprintf(string_,"빙결");
			return true;
		}
		return false;
	case MSS_ALLY:
		if(isUserAlly())
		{
			sprintf(string_,"우호");
			return true;
		}
		return false;
	case MSS_ELEC:
		if(s_elec)
		{
			sprintf(string_,"방전");
			return true;
		}
		return false;
	case MSS_PARALYSE:
		if(s_paralyse)
		{
			sprintf(string_,"마비");
			return true;

		}
		return false;
	case MSS_GLOW:
		if(s_glow)
		{
			sprintf(string_,"발광");
			return true;
		}
		return false;
	case MSS_GRAZE:
		if(s_graze)
		{
			sprintf(string_,"그레이즈");
			return true;
		}
		return false;
	case MSS_SILENCE:
		if(env[current_level].isSilence(position))
		{
			sprintf(string_,"정적");
			return true;
		}
		return false;
	case MSS_SICK:
		if(s_sick)
		{
			sprintf(string_,"병");
			return true;
		}
		return false;
	case MSS_VEILING:
		if(s_veiling)
		{
			sprintf(string_,"베일링");
			return true;
		}
		return false;
	case MSS_INVISIVLE:
		if(s_invisible)
		{
			sprintf(string_,"투명");
			return true;
		}
		return false;
	case MSS_TELE:
		if(s_tele)
		{
			sprintf(string_,"공간불안정");
			return true;
		}
		return false;
	case MSS_MUTE:
		if(s_mute)
		{
			sprintf(string_,"벙어리");
			return true;
		}
		return false;
	case MSS_CATCH:
		if(s_catch)
		{
			sprintf(string_,"잡힘");
			return true;
		}
		return false;
	case MSS_GHOST:
		if(s_ghost)
		{
			sprintf(string_,"영혼구속");
			return true;
		}
		return false;
	case MSS_FEAR:
		if(s_fear)
		{
			sprintf(string_,"공포");
			return true;
		}
		return false;
	case MSS_MIND_READING:
		if(s_mind_reading)
		{
			sprintf(string_,"간파");
			return true;
		}
		return false;
	case MSS_LUNATIC:
		if(s_lunatic)
		{
			sprintf(string_,"광기");
			return true;
		}
		return false;
	case MSS_COMMUNICATION:
		if(s_communication)
		{
			sprintf(string_,"동료부르기");
			return true;
		}
		return false;
	default:
		return false;
	}
}
void shadow::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, texturetoint(image));
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<shadow_type>(fp, type);
	char temp[100];
	sprintf(temp,"%s",name.c_str());
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