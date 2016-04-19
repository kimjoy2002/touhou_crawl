//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: environment.cpp
//
// 내용: 맵과 게임데이터
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"
#include "const.h"
#include "save.h"
#include "map.h"
#include "rect.h"
#include "event.h"
#include "mon_infor.h"
#include "key.h"
#include "smoke.h"
#include "floor.h"
#include "note.h"
#include "beam.h"
#include <set>



environment env[MAXLEVEL];
int current_level=0;
bool tutorial = false;
extern HANDLE mutx;


void stair_info::SaveDatas(FILE *fp)
{
	SaveData<coord_def>(fp, pos);
	SaveData<int>(fp, next_floor);

}
void stair_info::LoadDatas(FILE *fp)
{
	LoadData<coord_def>(fp, pos);
	LoadData<int>(fp, next_floor);

}
environment::environment():floor(0), make(false), all_monster_id(1)
{
	mon_vector.reserve(MON_MAX_IN_FLOOR);
}


environment::~environment()
{
}

void environment::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, floor);
	SaveData<bool>(fp, make);
	SaveData<int>(fp, all_monster_id);
	SaveData<dungeon_tile>(fp, **dgtile, DG_MAX_X * DG_MAX_Y);
	SaveData<coord_def>(fp, *stair_up, 3);
	SaveData<coord_def>(fp, *stair_down, 3);
	SaveData<int>(fp, stair_vector.size());
	for(auto it=stair_vector.begin();it!=stair_vector.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, mon_vector.size());
	for(vector<monster>::iterator it=mon_vector.begin();it!=mon_vector.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, shadow_list.size());
	for(list<shadow>::iterator it=shadow_list.begin();it!=shadow_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, item_list.size());
	for(list<item>::iterator it=item_list.begin();it!=item_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, smoke_list.size());
	for(list<smoke>::iterator it=smoke_list.begin();it!=smoke_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, floor_list.size());
	for(auto it=floor_list.begin();it!=floor_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, event_list.size());
	for(list<events>::iterator it=event_list.begin();it!=event_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
}

void environment::LoadDatas(FILE *fp)
{
	mon_vector.clear();
	shadow_list.clear();
	item_list.clear();
	effect_list.clear();
	LoadData<int>(fp, floor);
	LoadData<bool>(fp, make);
	LoadData<int>(fp, all_monster_id);
	LoadData<dungeon_tile>(fp, **dgtile);
	LoadData<coord_def>(fp, *stair_up);
	LoadData<coord_def>(fp, *stair_down);
	int size_;
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		stair_info temp(coord_def(),0);
		temp.LoadDatas(fp);
		stair_vector.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		monster temp;
		temp.LoadDatas(fp);
		mon_vector.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		shadow temp;
		temp.LoadDatas(fp);
		shadow_list.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		item temp;
		temp.LoadDatas(fp);
		item_list.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		smoke temp;
		temp.LoadDatas(fp);
		smoke_list.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		floor_effect temp;
		temp.LoadDatas(fp);
		floor_list.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		events temp;
		temp.LoadDatas(fp);
		event_list.push_back(temp);
	}

	//----ENV로딩부분에서 임시 타겟팅을 잡아줘야한다.
	
	for(vector<monster>::iterator it=mon_vector.begin();it!=mon_vector.end();it++)
	{
		if((*it).temp_target_map_id !=  -1) //지정할 대상이 있어
		{
			(*it).target = GetMapIDtoUnit((*it).temp_target_map_id);
		}
	}


}

void environment::EnterMap(int num_, deque<monster*> &dq, coord_def pos_)
{
	for(vector<monster>::iterator it =  env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{
		if(it->isLive())
		{
			it->TurnSave();
		}
	}
	int dq_n=0;
	if(!make || env[floor].isBamboo())
	{
		map_algorithms(floor);
		if(!tutorial)
		{
			create_mon(floor, GetLevelMonsterNum(floor,false));
			create_item(floor,  GetLevelMonsterNum(floor,true));
		}	

	}
	if(!make)
	{
		switch(floor)
		{
		case 4:
		case 9:
		case MAX_DUNGEUN_LEVEL:
		case TEMPLE_LEVEL:
		case MISTY_LAKE_LEVEL:
		case MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL:
		case YOUKAI_MOUNTAIN_LEVEL:
		case YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL:
		case SCARLET_LEVEL:
		case SCARLET_LEVEL+MAX_SCARLET_LEVEL:
		case SCARLET_LIBRARY_LEVEL:
		case SCARLET_UNDER_LEVEL:
		case BAMBOO_LEVEL:
		case EIENTEI_LEVEL:
		case SUBTERRANEAN_LEVEL:
		case SUBTERRANEAN_LEVEL+MAX_SUBTERRANEAN_LEVEL:
		case YUKKURI_LEVEL:
		case YUKKURI_LEVEL+MAX_YUKKURI_LEVEL:
		case DEPTH_LEVEL:
		case DREAM_LEVEL:
		case MOON_LEVEL:
		case PANDEMONIUM_LEVEL:
		case HAKUREI_LEVEL:
		case HAKUREI_LEVEL+MAX_HAKUREI_LEVEL:
			{
				char temp2[200];
				sprintf_s(temp2,200,"던전 진행: %s에 들어섰다.",CurrentLevelString(floor));
				AddNote(you.turn,CurrentLevelString(floor),temp2,CL_normal);
			}
			break;
		}
		make = true;
	}
	WaitForSingleObject(mutx, INFINITE);
	int prev_level = current_level;
	if(you.s_silence)
		env[current_level].MakeSilence(you.position, you.s_silence_range, false);
	current_level = floor;
	if(num_>=0 && num_ <3)
		you.SetXY(prev_level>floor?stair_down[num_]:stair_up[num_]);
	else
		you.SetXY(pos_);
	you.prev_position = you.position;
	if(you.s_silence)
		env[current_level].MakeSilence(you.position, you.s_silence_range, true);

	ReleaseMutex(mutx);
	if(monster* temp_unit = (monster*)isMonsterPos(you.position.x,you.position.y,&you))
	{	
		dif_rect_iterator dit(you.position, 3);
		for(;!dit.end();dit++)
		{
			if(env[current_level].isMove(dit->x, dit->y, false) && !env[current_level].isMonsterPos(dit->x,dit->y))
			{
				temp_unit->SetXY(*dit);
				break;
			}
		}
		if(dit.end())
			temp_unit->Teleport();

	}
	
	for(vector<monster>::iterator it =  env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{
		if(it->isLive() && env[current_level].isInSight(it->position))
		{
			it->atkmove(true,true);
			it->atkmove(true,true);
		}
	}


	if(!dq.empty())
	{
		dif_rect_iterator dit(you.position, 3);
		for(;!dit.end();dit++)
		{
			if(movingfloor((*dit), prev_level, dq[dq_n]))
			{
					dq_n++;
			}
			if(dq.size() == dq_n)
				break;
		}
	}
	for(vector<monster>::iterator it =  env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{
		if(it->isLive())
		{
			it->TurnLoad();
		}
	}
	if(floor && !tutorial)
		SaveFile();
	you.resetLOS(false);
}


int environment::isStair(int x_, int y_)
{
	for(int i=0;i<3;i++)
	{
		if(stair_down[i].x == x_ && stair_down[i].y == y_)
			return (i+1);
		if(stair_up[i].x == x_ && stair_up[i].y == y_)
			return -(i+1);
	}
	return 0;
}
int environment::CloseDoor(int x_,int y_)
{
	if(dgtile[x_][y_].isOpenDoor())
	{		
		{
			vector<monster>::iterator it = mon_vector.begin();
			for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
			{
				if((*it).isLive() && (*it).position.x == x_ && (*it).position.y == y_)
				{
					return -1;
				}
			}
		}
		{
			list<item>::iterator it = item_list.begin();
			for(;it != item_list.end() ;it++)
			{
				if((*it).position.x == x_ && (*it).position.y == y_)
				{
					return -1;
				}
			}
		}
		dgtile[x_][y_].CloseDoor();
		return 1;
	}
	else
		return 0;
}
monster* environment::AddMonster(int id_, int flag_, coord_def position_, int time_)
{
	WaitForSingleObject(mutx, INFINITE);
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR;i++,it++)
	{
		if(it == mon_vector.end())
		{
			mon_vector.push_back(monster());
			if(all_monster_id<1)
				all_monster_id = 1;
			ReleaseMutex(mutx);
			mon_vector.back().SetMonster(all_monster_id++, id_, flag_, time_, position_);
			return &(mon_vector.back());
		}
		else if(!(*it).isLive())
		{
			if(all_monster_id<1)
				all_monster_id = 1;
			ReleaseMutex(mutx);
			(*it).SetMonster(all_monster_id++, id_, flag_, time_, position_);
			return &(*it);
		}
	}
	ReleaseMutex(mutx);
	return NULL;
}
monster* environment::AddMonster(monster *mon_, coord_def position_, int time_)
{
	WaitForSingleObject(mutx, INFINITE);
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR;i++,it++)
	{
		if(it == mon_vector.end())
		{
			mon_vector.push_back(*mon_);
			if(all_monster_id<1)
				all_monster_id = 1;
			mon_vector.back().map_id = all_monster_id++;
			mon_vector.back().SetXY(position_);
			mon_vector.back().prev_sight = false;
			ReleaseMutex(mutx);
			return &mon_vector.back();
		}
		else if(!(*it).isLive())
		{
			(*it) = *mon_;
			(*it).map_id = all_monster_id++;
			(*it).SetXY(position_);
			(*it).prev_sight = false;
			ReleaseMutex(mutx);
			return &(*it);
		}
	}
	ReleaseMutex(mutx);
	return false;
}
monster* environment::AddMonster_Summon(int id_, int flag_, coord_def position_, summon_info &info_, int time_ = 0)
{
	monster* mon_ = AddMonster(id_, flag_, position_, time_);
	if(mon_)
	{
		mon_->sm_info = info_;

		if(mon_->sm_info.summon_id != SKD_OTHER && mon_->sm_info.max_num > 0) //최대 소환수가 정해져있는경우
		{
			vector<monster*> temp_list_;
			for( auto it = mon_vector.begin();it != mon_vector.end();it++)
			{
				if(it->isLive() && it->sm_info.summon_id == mon_->sm_info.summon_id && it->sm_info.parent_map_id == mon_->sm_info.parent_map_id && it->summon_time>0)
				{
					temp_list_.push_back(&(*it));
				}
			}
			if(temp_list_.size() > mon_->sm_info.max_num)
			{
				sort(temp_list_.begin(), temp_list_.end(), 
					[](monster* lt,monster* rt){
					return lt->GetMapId() > lt->GetMapId();
				});

				for(int i = temp_list_.size() - mon_->sm_info.max_num; i > 0 ; i--)
				{
					temp_list_[i]->summon_time = 0;
				}
			}
		}
	}
	return mon_;
}
void environment::SummonClear(int map_id_)
{
	if(map_id_ >= 0)
	{		
		for( auto it = mon_vector.begin();it != mon_vector.end();it++)
		{
			if(it->isLive() && it->sm_info.parent_map_id == map_id_ && it->summon_time!=0 && IsIndepend_summoner(it->sm_info.summon_id))
			{
				it->summon_time = 0;
			}
		}
	}
}

void environment::MakeShadow(const coord_def &c, textures *t, shadow_type type_, const string &name_)
{
	if(isBamboo())
		return; //죽림에선 만들지 않는다.
	WaitForSingleObject(mutx, INFINITE);
	list<shadow>::iterator it;
	for(it = shadow_list.begin();;it++)
	{
		if(it == shadow_list.end() || (*it).position.y > c.y || ((*it).position.y == c.y && (*it).position.x > c.x) )
		{
			shadow_list.insert(it,shadow(c,t,type_,name_));
			ReleaseMutex(mutx);
			return;
		}
		else if((*it).position.y == c.y && (*it).position.x == c.x)
		{
			if((*it).type < type_ )
			{
				shadow_list.insert(it,shadow(c,t,type_,name_));
				ReleaseMutex(mutx);
				return;
			}
			else if((*it).type == type_ )
			{
				shadow_list.insert(it,shadow(c,t,type_,name_));				
				shadow_list.erase(it);
				ReleaseMutex(mutx);
				return;
			}
		}
	}
	ReleaseMutex(mutx);
}


bool environment::MakeSmoke(const coord_def &c, textures *t, smoke_type type_, int time_, int expand_, unit* parent_)
{

	if(!isSmokePos(c.x,c.y) && isMove(c.x,c.y,true))
	{
		parent_type pt_temp = PRT_NEUTRAL;
		if(parent_)
		{
			if(parent_->isplayer())
			{
				pt_temp = PRT_PLAYER;
			}
			else
			{
				pt_temp = PRT_ENEMY;
			}
		}
		WaitForSingleObject(mutx, INFINITE);
		smoke_list.push_back(smoke(c, t, type_, time_, expand_, pt_temp));
		ReleaseMutex(mutx);
		return true;
	}
	return false;
}
bool environment::MakeFloorEffect(const coord_def &c, textures *t, textures *t2, floor_type type_, int time_, unit* parent_)
{
	if(!isMove(c.x,c.y,floor_effect::isFly(type_),floor_effect::isSwim(type_),floor_effect::isNoGround(type_)))
		return false;
	
	parent_type pt_temp = PRT_NEUTRAL;
	if(parent_)
	{
		if(parent_->isplayer())
			pt_temp = PRT_PLAYER;
		else
			pt_temp = PRT_ENEMY;
	}

	if(floor_effect* floor_= isFloorEffectPos(c.x,c.y))
	{
		//그 위치에 이미 floor효과가 있으면 덮어씌운다.
		return floor_->Update(t, t2, type_, time_, pt_temp);
		//상위 이펙트로 덮어씌울수도있어?
	}
	else
	{
		WaitForSingleObject(mutx, INFINITE);
		floor_list.push_back(floor_effect(c, t, t2, type_, time_, pt_temp));
		ReleaseMutex(mutx);
		return true;
	}
	return false;
}


bool environment::MakeEvent(int id_, coord_def position_, event_type type_, int count_)
{
	event_list.push_back(events(id_,position_,type_,count_));
	return true;
}

void environment::MakeEffect(const coord_def &c, textures *t, bool over_sight_)
{
	WaitForSingleObject(mutx, INFINITE);
	effect_list.push_back(effect(c,t,over_sight_));
	ReleaseMutex(mutx);
}
void environment::ClearEffect()
{
	WaitForSingleObject(mutx, INFINITE);
	effect_list.clear();
	ReleaseMutex(mutx);
}
void environment::ClearEvent()
{
	event_list.clear();
}
monster* environment::movingfloor(const coord_def &c, int prev_floor_, monster* mon_)
{
	if(env[current_level].isMove(c.x,c.y,mon_->isFly(),mon_->isSwim()) && !env[current_level].isMonsterPos(c.x,c.y) && you.position != c)
	{
		if(monster* temp = env[current_level].AddMonster(mon_, c))
		{/*
			if(temp->s_silence)
				env[current_level].MakeSilence(temp->position, temp->s_silence_range, true);*/
			if(mon_->s_silence)
				env[prev_floor_].MakeSilence(mon_->position, mon_->s_silence_range, false);
			if(temp->id == MON_ENSLAVE_GHOST && you.god == GT_YUYUKO)
			{	
				you.god_value[0] = temp->map_id;
				you.god_value[1] = current_level;
			}
			mon_->hp = 0;
			env[prev_floor_].SummonClear(mon_->map_id);
			return temp;
		}
	}
	return NULL;
}	

item* environment::AddItem(const coord_def &c, item *t, int num_)
{
	WaitForSingleObject(mutx, INFINITE);
	list<item>::iterator it;
	for(it = item_list.begin();;it++)
	{
		if(it == item_list.end() || (*it).position.y > c.y || ((*it).position.y == c.y && (*it).position.x > c.x) )
		{
			t->position = c;
			it = item_list.insert(it,*t);
			if(num_ && it->is_pile && it->num > num_)
			{
				it->weight = (it->weight*num_/it->num);
				it->num = num_;
			}
			ReleaseMutex(mutx);
			return &(*it);
		}
		else if((*it).position.y == c.y && (*it).position.x == c.x && it->is_pile && it->SameItem(*t))
		{
			it->weight += (num_)?(t->weight*num_/t->num):t->weight;
			it->num += num_?num_:t->num;
			ReleaseMutex(mutx);
			return &(*it);
		}
	}
	ReleaseMutex(mutx);
	return NULL;
}



void environment::DeleteItem(const list<item>::iterator it)
{
	WaitForSingleObject(mutx, INFINITE);
	item_list.erase(it);
	ReleaseMutex(mutx);
}
bool environment::DeleteItem(const item *item_)
{
	list<item>::iterator it;
	for(it = item_list.begin();it != item_list.end();it++)
	{
		if(&(*it) == item_)	
		{
			DeleteItem(it);
			return true;
		}
	}
	return false;
}
void environment::ClearShadow()
{
	WaitForSingleObject(mutx, INFINITE);
	list<shadow>::iterator it;
	for(it = shadow_list.begin();it != shadow_list.end();)
	{
		if(env[current_level].isInSight((*it).position))
		{
			list<shadow>::iterator temp;
			temp = it;
			it++;
			shadow_list.erase(temp);
		}
		else
			it++;
	}
	ReleaseMutex(mutx);
}
void environment::ClearShadow(const coord_def &c, shadow_type type_)
{
	
	list<shadow>::iterator it;
	for(it = shadow_list.begin();it != shadow_list.end();)
	{
		if(it->position == c && it->type == type_)
		{
			WaitForSingleObject(mutx, INFINITE);
			list<shadow>::iterator temp;
			temp = it;
			it++;
			shadow_list.erase(temp);
			ReleaseMutex(mutx);
		}
		else
			it++;
	}
}
void environment::CheckFloor()
{
	list<floor_effect>::iterator it;
	for(it = floor_list.begin();it != floor_list.end() ;)
	{
		list<floor_effect>::iterator temp = it++;
		temp->prev_check();
	}
}
void environment::ActionMonster(int delay_)
{
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && !DisableMove(it->position))
		{
			(*it).action(delay_);
		}
	}
}
void environment::ActionMonsterSpecial(int delay_)
{
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && !DisableMove(it->position))
		{
			(*it).special_action(delay_);
		}
	}
}
void environment::ActionSmoke(int delay_)
{
	list<smoke>::iterator it;
	for(it = smoke_list.begin();it != smoke_list.end() ;)
	{
		list<smoke>::iterator temp = it++;
		if(!DisableMove(temp->position) && !temp->action(delay_))
		{
			WaitForSingleObject(mutx, INFINITE);
			smoke_list.erase(temp);
			ReleaseMutex(mutx);
		}
	}
}
void environment::ActionFloor(int delay_)
{
	list<floor_effect>::iterator it;
	for(it = floor_list.begin();it != floor_list.end() ;)
	{
		list<floor_effect>::iterator temp = it++;
		if(!DisableMove(temp->position) && !temp->action(delay_))
		{
			WaitForSingleObject(mutx, INFINITE);
			floor_list.erase(temp);
			ReleaseMutex(mutx);
		}
	}
}
bool environment::ActionEvent(int delay_)
{
	bool return_ = false;
	list<events>::iterator it;
	for(it = event_list.begin();it != event_list.end() ;)
	{
		list<events>::iterator temp = it++;
		if(!DisableMove(temp->position) && !temp->action(delay_))
		{
			event_list.erase(temp);
			return_= true;
		}
	}
	return return_;
}
bool environment::ActionSmokeEffect()
{
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && !DisableMove(it->position))
		{
			if(isSmokePos((*it).position.x,(*it).position.y))
			{
				smoke* temp = isSmokePos2((*it).position.x,(*it).position.y);
				temp->effectSmoke(&(*it));
			}
		}
	}
	if(isSmokePos(you.position.x,you.position.y))
	{
		smoke* temp = isSmokePos2(you.position.x,you.position.y);
		if(temp->effectSmoke(&you))
			return true;
	}
	return false;
}

void environment::ActionItem(int delay_)
{
	list<item>::iterator it;
	it = item_list.begin();
	for(;it != item_list.end() ;)
	{
		item *temp = &(*it);
		it++;
		temp->action(delay_);
	}
}
bool environment::DisableMove(coord_def pos_, bool view_)
{
	if(you.s_dimension)
	{
		if(abs(pos_.x - you.god_value[0])>8 || abs(pos_.y - you.god_value[1])>8)
			return true; //차원고정의 범위 밖에 있다.
	}
	return false;

}
bool environment::MakeSilence(coord_def center_, int length_, bool on_)
{
	length_++;
	for(int i=-length_/2;i<=length_/2;i++) //나중에 원형반복자만들면 고치기?
	{
		for(int j=-length_/2;j<=length_/2;j++)
		{
			if(i*i+j*j<=length_*length_/4)
			{
				if(on_)
					dgtile[center_.x+i][center_.y+j].silence_count++;
				else if(dgtile[center_.x+i][center_.y+j].silence_count>0)
					dgtile[center_.x+i][center_.y+j].silence_count--;

				if(dgtile[center_.x+i][center_.y+j].silence_count)
					dgtile[center_.x+i][center_.y+j].flag |= FLAG_SILENCE;
				else
					dgtile[center_.x+i][center_.y+j].flag &= ~FLAG_SILENCE;
			}
		}
	}
	return true;
	
}

bool environment::MakeViolet(coord_def center_, int length_, bool on_)
{
	length_++;
	for(int i=-length_/2;i<=length_/2;i++) //나중에 원형반복자만들면 고치기?
	{
		for(int j=-length_/2;j<=length_/2;j++)
		{
			if(i*i+j*j<=length_*length_/4)
			{
				if(on_)
					dgtile[center_.x+i][center_.y+j].violet_count++;
				else if(dgtile[center_.x+i][center_.y+j].violet_count>0)
					dgtile[center_.x+i][center_.y+j].violet_count--;

				if(dgtile[center_.x+i][center_.y+j].violet_count)
					dgtile[center_.x+i][center_.y+j].flag |= FLAG_VIOLET;
				else
					dgtile[center_.x+i][center_.y+j].flag &= ~FLAG_VIOLET;
			}
		}
	}
	return true;
	
}



bool environment::MakeNoise(coord_def center_, int length_, const unit* excep_)
{
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && !(*it).isUserAlly() && !(*it).target && distan_coord((*it).position, center_) <= length_*length_ && &(*it) != excep_)
		{
			int block_length_ = length_;
			beam_iterator it2((*it).position,center_);
			while(block_length_ && !it2.end())
			{
				if(!env[current_level].isMove((*it2),true,true))
				{
					block_length_-=3;
					break;
				}
				it2++;
			}
			if(distan_coord((*it).position, center_) <= block_length_*block_length_)
			{
				(*it).target_pos = center_;
				(*it).memory_time = 30;
				(*it).state.StateTransition(MSI_NOISE);
			}
		}
	}
	return true;
}
bool environment::MakeMapping(coord_def center_, int length_, bool passed_, int percent_)
{
	set<coord_def> cd_set;
	cd_set.insert(center_);
	for(int i=-length_; i<=length_; i++)
	{
		for(int j=-length_; j<=length_; j++)
		{
			int abs_ = coord_def(i,j).abs();
			
			if(passed_ && abs_ < (length_+1)*(length_+1))
			{
				coord_def target_ = center_+coord_def(i,j);
				magicmapping(target_.x,target_.y);
			}
			if(!passed_ && abs_ >= (length_-1)*(length_-1) && abs_ < (length_+1)*(length_+1))
			{
				coord_def target_ = center_+coord_def(i,j);

				bool intercept = false;
				bool fail_ = false;
				for(int i=RT_BEGIN;i!=RT_END;i++)
				{
					int length_ = 8;
					beam_iterator it(center_,target_,(round_type)i);
					while(!intercept && !it.end())
					{
						cd_set.insert(*it);
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
						fail_ = true;
						break;
					}
					else
						intercept = false;
					if(fail_)
						break;
				}
			}
		}
	}

	for(auto it= cd_set.begin(); it!= cd_set.end(); it++)
	{
		if(percent_>randA(99))
			magicmapping(it->x,it->y);
	}
	return true;
}
bool environment::isSilence(coord_def pos_)
{
	return dgtile[pos_.x][pos_.y].flag & FLAG_SILENCE;
}
bool environment::isViolet(coord_def pos_)
{
	return dgtile[pos_.x][pos_.y].flag & FLAG_VIOLET;
}
unit* environment::isMonsterPos(int x_,int y_, const unit* excep_, int* map_id_)
{
	if(you.position.x == x_ && you.position.y == y_ && excep_ != &you)
		return &you;
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && (*it).position.x == x_ && (*it).position.y == y_ && &(*it) != excep_)
		{
			if(map_id_)
				(*map_id_) = (*it).map_id;
			return &(*it);
		}
	}
	return NULL;
}
bool environment::isSmokePos(int x_,int y_, bool only_fog)
{
	if(dgtile[x_][y_].flag & (only_fog?FLAG_SIGHT_SMOKE:FLAG_SMOKE))
		return true;
	return false;	
}
floor_effect* environment::isFloorEffectPos(int x_,int y_, const floor_effect* excep_)
{
	list<floor_effect>::iterator it;	
	for(it = floor_list.begin();it != floor_list.end() ;it++)
	{
		if(it->position.x == x_ && it->position.y == y_ &&  &(*it) != excep_)
		{
			return &(*it);
		}
	}
	return false;	
}
smoke* environment::isSmokePos2(int x_,int y_, const smoke* excep_)
{
	list<smoke>::iterator it;
	
	for(it = smoke_list.begin();it != smoke_list.end() ;it++)
	{
		if(it->position.x == x_ && it->position.y == y_ &&  &(*it) != excep_)
		{
			return &(*it);
		}
	}
	return NULL;	
}

int environment::insight_mon(monster_enemy_type type_) //타입은 동맹,적등등.. 나중에 필요하면 조건넣기
{
	int num_=0;
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && (*it).isYourShight())
		{
			if(type_ == MET_ENEMY && ((*it).flag & M_FLAG_UNHARM || (*it).isUserAlly()))
				continue;
			num_++;
		}
	}
	return num_;
}
monster* environment::close_mon(int x_,int y_, monster_enemy_type type_)
{
	int dis_=999;
	monster* return_=NULL;
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && (*it).isYourShight())
		{
			int dis2_=max(abs((*it).position.x-x_),abs((*it).position.y-y_));
			if(type_ == MET_ENEMY && ((*it).flag & M_FLAG_UNHARM || (*it).isUserAlly()))
				continue;
			if(dis_>dis2_){
				dis_= dis2_;
				return_ = &(*it);
			}
		}
	}

	return return_;
}
void environment::item_view_set()
{
	list<item>::iterator it;
	it = item_list.begin();
	for(;it != item_list.end() ;it++)
	{
		if(env[current_level].isInSight((*it).position))
		{
			(*it).not_find = false;
		}
	}
}

int environment::new_item_interupt()
{
	int num_=0;
	int auto_pick=0;//자동줍기가 뷰에 보일경우
	list<item>::iterator it;
	item *itme_[3];
	it = item_list.begin();
	for(;it != item_list.end() ;it++)
	{
		if((*it).not_find && env[current_level].isInSight((*it).position))
		{
			(*it).income_view();
			if(!Auto_Pick_Up(it)) //자동줍기가 아닐경우 
			{
				if(num_<=2)
					itme_[num_] = &(*it);
				num_++;
			}
			else
			{
				auto_pick++;
			}
		}
		
	}
	if(num_)
	{
		if(num_<=3)
		{
			int i;
			for(i = 0; i < num_; i++)
			{
				if(i)
					printlog(itme_[i-1]->GetNameInfor().name_and(true),false,false,false,CL_normal);
				printlog(itme_[i]->GetName(),false,false,false,itme_[i]->item_color());
			}
			printlog(itme_[i-1]->GetNameInfor().name_to(true),false,false,false,CL_normal);
			printlog("발견했다.",true,false,false,CL_normal);
		}
		else
			printlog("여러 아이템을 발견했다.",true,false,false,CL_normal);
	}
	else if(auto_pick) //시야에 자동줍기 템이 있을경우 -1을 리턴. 이것은 정지를 일으키진않지만 템을 줍기위해 방향을 바꾼다.
		return -1;
	return num_;
}

item* environment::close_item(vector<item*> &item_vector_)
{
	int dis_=99;
	item* return_ = NULL;
	list<item>::iterator it;
	it = item_list.begin();
	for(;it != item_list.end() ;it++)
	{
		if(env[current_level].isExplore((*it).position.x, (*it).position.y)/*env[current_level].isInSight((*it).position)*/) //이제 시야 밖에 있는 템도 가져가게?
		{
			int dis2_ = max(abs(you.position.x-(*it).position.x),abs(you.position.y-(*it).position.y));
			if(dis2_ && (*it).isautopick())
			{
				item_vector_.push_back(&(*it));

				
				if(dis2_ && dis2_<dis_){
					dis_ = dis2_;
					return_ = &(*it);
				}
			}
		}
		
	}
	sort(item_vector_.begin(),item_vector_.end(),[&](item* left_, item* right_)
	{
		return max(abs(you.position.x-(*left_).position.x),abs(you.position.y-(*left_).position.y)) < max(abs(you.position.x-(*right_).position.x),abs(you.position.y-(*right_).position.y));
	});
	

	return return_;
}
unit* environment::GetMapIDtoUnit(int Map_id_)
{
	if(Map_id_ == -1) //대상없음
		return NULL;
	else if(Map_id_ == -2) //플레이어
		return &you;
	else{
		
		for(vector<monster>::iterator it=mon_vector.begin();it!=mon_vector.end();it++)
		{
			if(it->GetMapId() == Map_id_)
				return &(*it);
		}
	}
	return NULL; //없을수있나?
}

list<item>::iterator environment::GetPositiontoitem(coord_def position_)
{
	for(list<item>::iterator it = item_list.begin();it!=item_list.end();it++)
	{
		if((*it).position.x == position_.x && (*it).position.y == position_.y)
			return it;
	}
	return item_list.end();
}
list<item>::iterator environment::GetPositiontoitemend(coord_def position_)
{
	list<item>::iterator it;
	int a_ = 0;
	for(it = item_list.begin();it!=item_list.end();it++)
	{
		if((*it).position.x == position_.x && (*it).position.y == position_.y)
			a_ = 1;
		else if(a_ == 1)
			break;
	}
	return it;
}


void SaveFile()
{
	if(game_over)
		return;
	WaitForSingleObject(mutx, INFINITE);
	FILE *fp;
	fp = fopen(save_file.c_str(),"wb");
	SaveData<int>(fp, current_level);
	for(int i = 0; i < MAXLEVEL; i++)
	{
		env[i].SaveDatas(fp);
	}
	you.SaveDatas(fp);
	SaveData<Iden_collect>(fp,iden_list);
	SaveData<int>(fp, unique_list.size());
	for(vector<unique_infor>::iterator it=unique_list.begin();it!=unique_list.end();it++)
	{
		SaveData<unique_infor>(fp, (*it));
	}
	SaveData<map_infor>(fp,map_list);
	save_note.SaveDatas(fp);
	fclose(fp);
	//printlog("저장했습니다.",true,false,false,CL_normal);


	ReleaseMutex(mutx);
}


void LoadFile()
{
	WaitForSingleObject(mutx, INFINITE);
	FILE *fp;
	fp = fopen(save_file.c_str(),"rb");
	LoadData<int>(fp, current_level);

	for(int i = 0; i < MAXLEVEL; i++)
	{
		env[i].LoadDatas(fp);	
	}
	you.LoadDatas(fp);
	LoadData<Iden_collect>(fp,iden_list);
	
	unique_list.clear();
	int size_=0;
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		unique_infor temp;
		LoadData<unique_infor>(fp,temp);
		unique_list.push_back(temp);
	}
	LoadData<map_infor>(fp,map_list);
	save_note.LoadDatas(fp);

	fclose(fp);

	//for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end();it++)
	//{
	//	if(it->isLive() && it->memory_time)
	//	{
	//		it->target = env[current_level].isMonsterPos(it->target_pos.x,it->target_pos.y,&(*it));
	//	}
	//}

	//printlog("불러왔습니다.",true,false,false,CL_normal);
	ReleaseMutex(mutx);
}

float GetDotX(int x)
{
	return 555.0f+x*3;
}
float GetDotY(int y)
{
	return 340.0f+y*3;
}

char* CurrentLevelString(int level)
{
	static char temp[30];
	int level_ = level>=0?level:current_level;
	if(level_<TEMPLE_LEVEL)
		sprintf(temp,"던전 %d층", level_+1);
	else if(level_ == TEMPLE_LEVEL)
		sprintf(temp,"신전");
	else if(level_ >= MISTY_LAKE_LEVEL && level_ <= MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL)
		sprintf(temp,"안개호수 %d층", level_+1-MISTY_LAKE_LEVEL);
	else if(level_ >= YOUKAI_MOUNTAIN_LEVEL && level_ <= YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL)
		sprintf(temp,"요괴의산 %d층", level_+1-YOUKAI_MOUNTAIN_LEVEL);
	else if(level_ >= SCARLET_LEVEL && level_ <= SCARLET_LEVEL+MAX_SCARLET_LEVEL)
		sprintf(temp,"홍마관 %d층", level_+1-SCARLET_LEVEL);
	else if(level_ >= SCARLET_LIBRARY_LEVEL && level_ <= SCARLET_LIBRARY_LEVEL+MAX_SCARLET_LIBRARY_LEVEL)
		sprintf(temp,"홍마관 도서관");
	else if(level_ >= SCARLET_UNDER_LEVEL && level_ <= SCARLET_UNDER_LEVEL+MAX_SCARLET_UNDER_LEVEL)
		sprintf(temp,"홍마관 지하실");
	else if(level_ >= BAMBOO_LEVEL && level_ <= BAMBOO_LEVEL+MAX_BAMBOO_LEVEL)
		sprintf(temp,"미궁의 죽림");
	else if(level_ >= EIENTEI_LEVEL && level_ <= EIENTEI_LEVEL+MAX_EIENTEI_LEVEL)
		sprintf(temp,"영원정");
	else if(level_ >= SUBTERRANEAN_LEVEL && level_ < SUBTERRANEAN_LEVEL+MAX_SUBTERRANEAN_LEVEL)
		sprintf(temp,"지저 %d층", level_+1-SUBTERRANEAN_LEVEL);
	else if(level_ == SUBTERRANEAN_LEVEL+MAX_SUBTERRANEAN_LEVEL)
		sprintf(temp,"작열지옥터");	
	else if(level_ >= YUKKURI_LEVEL && level_ <=  YUKKURI_LAST_LEVEL)
		sprintf(temp,"윳쿠리둥지 %d층", level_+1-YUKKURI_LEVEL);
	else if(level_ >= DEPTH_LEVEL && level_ <=  DEPTH_LAST_LEVEL)
		sprintf(temp,"짐승길 %d층", level_+1-DEPTH_LEVEL);
	else if(level_ >= DREAM_LEVEL && level_ <=  DREAM_LAST_LEVEL)
		sprintf(temp,"꿈의 세계");
	else if(level_ >= MOON_LEVEL && level_ <=  MOON_LAST_LEVEL)
		sprintf(temp,"달의 도시");
	else if(level_ >= PANDEMONIUM_LEVEL && level_ <=  PANDEMONIUM_LAST_LEVEL)
		sprintf(temp,"마계");
	else if(level_ >= HAKUREI_LEVEL && level_ <=  HAKUREI_LAST_LEVEL)
		sprintf(temp,"하쿠레이 %d층", level_+1-HAKUREI_LEVEL);
	else
		sprintf(temp,"알수없는 층");

	return temp;
}
int GetLevelMonsterNum(int level, bool item_)
{
	int level_ = level>=0?level:current_level;
	if(!item_)
	{
		if(level_ == TEMPLE_LEVEL || level_ == BAMBOO_LEVEL)
			return 0;
		else if(level_ >= MISTY_LAKE_LEVEL && level_ <= MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL)
			return 7;
		else
			return 9;
	}
	else{
		if(level_ == TEMPLE_LEVEL || level_ == BAMBOO_LEVEL)
			return 0;
		else
			return 15;
	}

}

void Noise(coord_def center_, int length_, const unit* excep_)
{
	env[current_level].MakeNoise(center_,length_,excep_);
}