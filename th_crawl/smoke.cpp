//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: smoke.cpp
//
// 내용: 연기관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "smoke.h"
#include "save.h"
#include "rect.h"
#include "monster_texture.h"
#include "environment.h"
#include "mon_infor.h"


smoke::smoke()
:image(NULL), position(), type(SMT_NORMAL), time(1), expand(0), parent(PRT_NEUTRAL)
{}

smoke::smoke(const coord_def &c, textures *t, smoke_type type_, int time_, int expand_, parent_type parent_)
:image(t), position(c), type(type_), time(time_), expand(expand_), parent(parent_)
{
	env[current_level].dgtile[c.x][c.y].flag |= FLAG_SMOKE;
	if(sight_inter())
	{
		env[current_level].dgtile[c.x][c.y].flag |= FLAG_SIGHT_SMOKE;
		if(env[current_level].isInSight(c))
			you.sight_reset = true;
	}
	if(type_ == SMT_DARK)
		env[current_level].dgtile[c.x][c.y].flag |= FLAG_DANGER;
}


void smoke::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, texturetoint(image));
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<smoke_type>(fp, type);
	SaveData<int>(fp, time);
	SaveData<int>(fp, expand);
	SaveData<parent_type>(fp, parent);
}

void smoke::LoadDatas(FILE *fp)
{
	int it;
	LoadData<int>(fp, it);
	image = inttotexture(it);
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<smoke_type>(fp, type);
	LoadData<int>(fp, time);
	LoadData<int>(fp, expand);
	LoadData<parent_type>(fp, parent);
}
bool smoke::draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_)
{
	bool return_ = false;
	return_ = image[time>2?(time%2?0:1):(time==1?3:2)].draw(pSprite, x_, y_,200);
	return return_;
}
bool smoke::clear(const coord_def move_)
{	
	if(move_.x != 0 || move_.y != 0)
	{
		env[current_level].dgtile[position.x + move_.x][position.y + move_.y].flag |= FLAG_SMOKE;
		env[current_level].dgtile[position.x + move_.x][position.y + move_.y].flag |= FLAG_SIGHT_SMOKE;
		if(type == SMT_DARK)
			env[current_level].dgtile[position.x + move_.x][position.y + move_.y].flag |= FLAG_DANGER;
	}
	env[current_level].dgtile[position.x][position.y].flag &= ~FLAG_SMOKE;
	env[current_level].dgtile[position.x][position.y].flag &= ~FLAG_SIGHT_SMOKE;
	if(type == SMT_DARK)
		env[current_level].dgtile[position.x][position.y].flag &= ~FLAG_DANGER;
	return true;
}
bool smoke::action(int delay_)
{
	if(time <= 0)
		return false;
	time--;
	if (type == SMT_FIRE && env[current_level].dgtile[position.x][position.y].tile == DG_SEA  && time > 2) {
		time -= 3;
		if (time < 2)
			time = 2;
	}
	if(time<=0)
	{
		clear();
		return false;
	}
	return true;
}
bool smoke::offsetmove(const coord_def &c)
{	
	if(c.x == 0 && c.y == 0)
		return true;
	coord_def temp = position + c;
	if(temp.x >= 0 && temp.x < DG_MAX_X && temp.y >= 0 && temp.y < DG_MAX_Y )
	{
		clear(c);
		position = temp;
		return true;
	}
	else
	{
		clear();
		time = 0;
		return false;
	}
}
string smoke::GetName()
{
	switch(type)
	{
	case SMT_NORMAL:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_NORMAL);
	case SMT_FOG:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_FOG);
	case SMT_FIRE:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_FIRE);
	case SMT_COLD:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_COLD);
	case SMT_ELEC:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_ELEC);
	case SMT_DARK:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_DARK);
	case SMT_SION:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_SION);
	case SMT_POISON:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_POISON);
	case SMT_CONFUSE:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_CONFUSE);
	case SMT_SLOW:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_SLOW);
	case SMT_TWIST:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_TWIST);
	case SMT_WHIRLWIND:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_WHIRLWIND);
	case SMT_CURSE:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_CURSE);
	case SMT_BLIZZARD:
		return LocalzationManager::locString(LOC_SYSTEM_SMOKE_BLIZZARD);
	default:
		return 0;
	}
}

bool smoke::effectSmoke(unit* unit_)
{
	switch(type)
	{
	case SMT_NORMAL:
	case SMT_FOG:
	case SMT_DARK:
	case SMT_SION:
	default:
		return false;
	case SMT_FIRE:
		unit_->damage(attack_infor(rand_int(5,15),15,99,NULL,parent,ATT_CLOUD_FIRE,name_infor(LOC_SYSTEM_SMOKE_FIRE)), true);
		return true;
	case SMT_COLD:
		unit_->damage(attack_infor(rand_int(3,12),12,99,NULL,parent,ATT_CLOUD_COLD,name_infor(LOC_SYSTEM_SMOKE_COLD)), true);
		unit_->SetFrozen(randA_1(7));
		return true;
	case SMT_ELEC:
		unit_->damage(attack_infor(rand_int(7,17),17,99,NULL,parent,ATT_CLOUD_ELEC,name_infor(LOC_SYSTEM_SMOKE_ELEC)), true);
		return true;
	case SMT_TWIST:
		unit_->damage(attack_infor(randA_1(8),8,99,NULL,parent,ATT_CLOUD_NORMAL,name_infor(LOC_SYSTEM_SMOKE_TWIST)), true);
		return true;
	case SMT_WHIRLWIND:
		unit_->damage(attack_infor(randA_1(30),30,99,NULL,parent,ATT_CLOUD_NORMAL,name_infor(LOC_SYSTEM_SMOKE_WHIRLWIND)), true);
		return true;
	case SMT_POISON:
		{
			bool return_ = unit_->SetPoison(rand_int(10,15), 150, false);
			unit_->SetPoisonReason(parent);
			return return_;
		}
	case SMT_CONFUSE:
		{
			bool return_ = false;
			if(unit_->GetPoisonResist()<=0 && randA(20) < max(20-unit_->GetLevel(),1))
				return_ = unit_->SetConfuse(randA(10));
			return return_;
		}
	case SMT_SLOW:
		{
			bool return_ = unit_->SetPoison(rand_int(5,15), 150, false);
			if(!unit_->GetPoisonResist() || (unit_->isplayer() && randA(2)>1))
				return_ = (unit_->SetSlow(randA(10))?true:return_);
			return return_;
		}
	case SMT_CURSE:
		if(!unit_->isplayer() || you.god != GT_HINA)
		{
			unit_->damage(attack_infor(randA_1(5),5,99,NULL,parent,ATT_CLOUD_CURSE,name_infor(LOC_SYSTEM_ATT_CURSE)), true);
			bool return_ = unit_->SetPoison(rand_int(5,10), 150, true);
			if(randA(7)>4)
				return_ = (unit_->SetSlow(randA(10))?true:return_);
			return return_;
		}
		return false;
	case SMT_BLIZZARD:
		{
			if (!unit_->isplayer()) {
				monster* mon_ = (monster*)unit_;
				if(mon_->flag & M_FLAG_RESIST_BLIZARD)
					return false;
			}
		}
		unit_->damage(attack_infor(rand_int(25,35),30,99,NULL,parent,ATT_COLD_PYSICAL_BLAST,name_infor(LOC_SYSTEM_SMOKE_BLIZZARD)), true);
		return true;
	}
	return false;
}
int smoke::danger(unit* unit_, bool first_)
{
	int prev_danger=0, danger_=0;
	if(first_ && env[current_level].isSmokePos(unit_->position.x,unit_->position.y))
	{
		smoke *temp_smoke = env[current_level].isSmokePos2(unit_->position.x,unit_->position.y,this);
		if(temp_smoke)
			prev_danger = temp_smoke->danger(unit_,false);
	}
	switch(type)
	{
	case SMT_FIRE:
		danger_ = unit_->isplayer()?999*unit_->GetFireResist(true):80*unit_->GetFireResist(true);
		return (danger_>prev_danger)?danger_:0;
	case SMT_COLD:
		danger_ = unit_->isplayer()?999*unit_->GetColdResist(true):80*unit_->GetColdResist(true);
		return (danger_>prev_danger)?danger_:0;
	case SMT_ELEC:
		danger_ = unit_->isplayer()?999*unit_->GetElecResist(true):80*unit_->GetElecResist(true);
		return (danger_>prev_danger)?danger_:0;
	case SMT_POISON:
	case SMT_SLOW:
		danger_ = unit_->isplayer()?(unit_->GetPoisonResist()>0?999:0):(unit_->GetPoisonResist()>0?30:0);
		return (danger_>prev_danger)?danger_:0;
	case SMT_TWIST:
		danger_ = unit_->isplayer()?50:(unit_->GetCloudResist()?0:25);
		return (danger_>prev_danger)?danger_:0;
	case SMT_WHIRLWIND:
		danger_ = unit_->isplayer()?100:(unit_->GetCloudResist()?0:50);
		return (danger_>prev_danger)?danger_:0;
	case SMT_CURSE:
		danger_ = unit_->isplayer()?(you.god == GT_HINA?0:50):25;
		return (danger_>prev_danger)?danger_:0;
	case SMT_BLIZZARD:
		danger_ = unit_->isplayer()?999:60+60*unit_->GetColdResist();
		return (danger_>prev_danger)?danger_:0;
	default:
		return 0;
	}
}


int smoke::sight_inter()
{
	switch(type)
	{
	case SMT_FOG:
		return 1;
	case SMT_DARK:
	case SMT_SION:
		return 2;
	default:
		return 0;
	}
}


typedef struct coord_node
{
	coord_def pos;
	int value;
	bool opcl;
	coord_node():pos(),value(0),opcl(false){};
	coord_node* Set(const coord_def& pos_,int value_)
	{
		pos=pos_;
		value=value_;
		return this;
	}
}node;

int PathCostCL(const coord_def& start, const coord_def&  goal)
{
	return ((start.x - goal.x)*(start.x - goal.x)+(start.y - goal.y)*(start.y - goal.y))*10;
}

void priqueue_push(list<coord_node*>& queues,node* data)
{
	list<coord_node*>::iterator it;
	for(it = queues.begin();it != queues.end();it++)
	{
		if((*it)->value > data->value)
			break;
	}
	queues.insert(it,data);
}

coord_node cloud_node[DG_MAX_X][DG_MAX_Y];


bool MakeCloud(const coord_def &c, textures *t, smoke_type type_, int num_, int time_, int expand_, int max_length, unit* parent_)
{
	random_extraction<textures*> rand_t;
	rand_t.push(t);
	return MakeCloud(c, rand_t, type_, num_, time_, 1, expand_, max_length, parent_);
}
bool MakeCloud(const coord_def &c, random_extraction<textures*> rand_t, smoke_type type_, int num_, int time_, int time_updown_, int expand_, int max_length, unit* parent_)
{
	for(int x=0;x<DG_MAX_X;x++)
	{
		for(int y=0;y<DG_MAX_Y;y++)
		{
			cloud_node[x][y].opcl = false;
		}
	}
	list<coord_node*> Open;

	priqueue_push(Open,cloud_node[c.x][c.y].Set(c,0));//스타트지점을 오픈 푸시

	cloud_node[c.x][c.y].opcl = true;
	while(!Open.empty() && num_>0)
	{
		coord_node* node = Open.front();
		Open.pop_front();

		if(env[current_level].MakeSmoke(node->pos, rand_t.choice(), type_, time_+rand_int(-time_updown_, time_updown_), expand_, parent_))
		{
			num_--;
		}
		if(num_>0)
		{
			rect_iterator it(node->pos,1,1);
			for(;!it.end();it++)
			{
				if((*it) == node->pos)
					continue;				
				if(!env[current_level].isMove(it->x,it->y))
					continue;
				if(distan_coord(c,(*it))>=max_length*max_length)
					continue;
				coord_node* newnode = &cloud_node[it->x][it->y];
				if(newnode->opcl)
					continue;
				newnode->opcl = true;
				priqueue_push(Open,newnode->Set((*it),node->value+(it.isdiagonal()?14:10)+randA(10)));
			}
		}
	}
	if(num_>0)
		return false;
	return true;
}