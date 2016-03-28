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
char* smoke::GetName()
{
	switch(type)
	{
	case SMT_NORMAL:
		return "옅은 연기";
	case SMT_FOG:
		return "안개 구름";
	case SMT_FIRE:
		return "화염 구름";
	case SMT_COLD:
		return "냉기 구름";
	case SMT_DARK:
		return "암흑 구름";
	case SMT_POISON:
		return "독 구름";
	case SMT_CONFUSE:
		return "혼란 구름";
	case SMT_SLOW:
		return "스위트 포이즌";
	case SMT_TWIST:
		return "트위스트";
	case SMT_WHIRLWIND:
		return "회오리바람";
	case SMT_CURSE:
		return "저주 구름";
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
	default:
		return false;
	case SMT_FIRE:
		unit_->damage(attack_infor(rand_int(10,25),25,99,NULL,parent,ATT_CLOUD_FIRE,name_infor("화염 구름",true)), true);
		return true;
	case SMT_COLD:
		unit_->damage(attack_infor(rand_int(10,25),25,99,NULL,parent,ATT_CLOUD_COLD,name_infor("냉기 구름",true)), true);
		unit_->SetFrozen(randA_1(7));
		return true;
	case SMT_TWIST:
		unit_->damage(attack_infor(randA_1(8),8,99,NULL,parent,ATT_CLOUD_NORMAL,name_infor("트위스트",false)), true);
		return true;
	case SMT_WHIRLWIND:
		if(unit_->GetId() != MON_AYA && unit_->GetId() != MON_CROW_TENGU && unit_->GetId() != MON_YAMABUSH_TENGU && unit_->GetId() != MON_HANATACA_TENGU)
		{
			unit_->damage(attack_infor(randA_1(30),20,99,NULL,parent,ATT_CLOUD_NORMAL,name_infor("회오리바람",true)), true);
			return true;
		}
		return false;
	case SMT_POISON:
		{
			bool return_ = unit_->SetPoison(rand_int(10,25), 150, false);
			unit_->SetPoisonReason(parent);
			return return_;
		}
	case SMT_CONFUSE:
		{
			bool return_ = false;
			if(unit_->GetPoisonResist()<=0)
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
			unit_->damage(attack_infor(randA_1(5),5,99,NULL,parent,ATT_CLOUD_NORMAL,name_infor("저주",false)), true);
			bool return_ = unit_->SetPoison(rand_int(5,10), 150, true);
			if(randA(7)>4)
				return_ = (unit_->SetSlow(randA(10))?true:return_);
			return return_;
		}
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
		danger_ = unit_->isplayer()?999:80*unit_->GetFireResist();
		return (danger_>prev_danger)?danger_:0;
	case SMT_COLD:
		danger_ = unit_->isplayer()?999:80*unit_->GetColdResist();
		return (danger_>prev_danger)?danger_:0;
	case SMT_POISON:
	case SMT_SLOW:
		danger_ = unit_->isplayer()?(unit_->GetPoisonResist()>0?999:0):(unit_->GetPoisonResist()>0?30:0);
		return (danger_>prev_danger)?danger_:0;
	case SMT_TWIST:
		danger_ = unit_->isplayer()?50:25;
		return (danger_>prev_danger)?danger_:0;
	case SMT_WHIRLWIND:
		danger_ = unit_->isplayer()?100:(unit_->GetId()!= MON_AYA?50:0);
		return (danger_>prev_danger)?danger_:0;
	case SMT_CURSE:
		danger_ = unit_->isplayer()?(you.god == GT_HINA?0:50):25;
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

		if(env[current_level].MakeSmoke(node->pos, t, type_, time_+rand_int(-1,1), expand_, parent_))
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