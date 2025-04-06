//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: floor.cpp
//
// 내용: 바닥 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "floor.h"
#include "save.h"
#include "rect.h"
#include "monster_texture.h"
#include "environment.h"
#include "god.h"



floor_effect::floor_effect()
: position(), image(NULL), image2(NULL), time(1), type(FLOORT_NORMAL), parent(PRT_NEUTRAL)
{}
floor_effect::floor_effect(const coord_def &c, textures *t, textures *t2, floor_type type_, int time_, parent_type parent_)
: position(c), image(t), image2(t2), time(time_*10), type(type_), parent(parent_)
{
}
	
void floor_effect::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, texturetoint(image));
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<floor_type>(fp, type);
	SaveData<int>(fp, time);
	SaveData<parent_type>(fp, parent);
}
void floor_effect::LoadDatas(FILE *fp)
{
	int it;
	LoadData<int>(fp, it);
	image = inttotexture(it);
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<floor_type>(fp, type);
	LoadData<int>(fp, time);
	LoadData<parent_type>(fp, parent);
}
bool floor_effect::draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_)
{
	bool return_ = false;
	if(time>0)
	{
		if(image)
			return_ = image->draw(pSprite, x_, y_,255);
	}
	else
	{
		if(image2)
			return_ = image2->draw(pSprite, x_, y_,255);
	}
	return return_;
}
void floor_effect::prev_check()
{	
	if(time<=0)
	{
		return;
	}	
	switch(type)
	{
	case FLOORT_AUTUMN:
		if(you.position == position && you.god == GT_SHIZUHA && !you.GetPunish(GT_SHIZUHA))
		{
			if(you.prev_action == ACTT_WALK && pietyLevel(you.piety) >= 4){
				you.time_delay *= 0.7;
			}
		}
		break;
	case FLOORT_NORMAL:
	default:
		break;
	}
}
bool floor_effect::action(int delay_)
{
	if(time<=0)
	{
		return false;
	}	
	time-= delay_;


	switch(type)
	{
	case FLOORT_AUTUMN:
		if(you.position == position && you.god == GT_SHIZUHA && !you.GetPunish(GT_SHIZUHA))
		{
			you.SetAutumn(1);
			if(you.prev_action == ACTT_WALK && pietyLevel(you.piety) >= 4){
				you.time_delay *= 0.7;
			}
		}
		if(you.position == position && you.GetPunish(GT_SHIZUHA))
		{
			you.SetAutumn(-1);
			you.SetBuff(BUFFSTAT_RF,BUFF_AUTUMN_RF,-1,1);
		}
		break;
	case FLOORT_NORMAL:
	default:
		break;
	}

	return true;
}
bool floor_effect::offsetmove(const coord_def &c)
{		
	position += c;
	if(position.x >= 0 && position.x < DG_MAX_X && position.y >= 0 && position.y < DG_MAX_Y )
		return true;
	else
	{
		time = 0;
		return false;
	}
}
void floor_effect::onWalk(unit* unit_)
{
	switch(type)
	{
	case FLOORT_STONE:
	/*	if(unit* it = env[current_level].isMonsterPos(position.x,position.y))
		{*/
			//if(it->GetPrevPos() != position)
			//{
		if(!unit_->isFly()) {
			attack_infor attack_infor_(rand_int(8,14),15,99,NULL,parent,ATT_STONE_TRAP,name_infor(LOC_SYSTEM_ATT_STONE_TACK));
			unit_->damage(attack_infor_, true);
		}
				/*return true;*/
		//	}
		//}
		break;		
	case FLOORT_AUTUMN:
		if(unit_->isplayer() && you.GetPunish(GT_SHIZUHA))
		{
			env[current_level].MakeNoise(you.position,20,NULL);
			
			if(!you.s_autumn)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_MAKE_NOISE), true,false,false,CL_autumn);
		}
		break;	
	case FLOORT_NORMAL:
	default:
		break;
	}
}
bool floor_effect::Update(textures *t, textures *t2, floor_type type_, int time_, parent_type parent_)
{
	time_*=10;
	if(type_>= type)
	{//덮어 씌운다.
		if(type_== type && parent == parent_ &&time_<time)
		{//시간이 짧아지는 경우는 덮어씌우지않음
			return false;
		}
		image = t;
		image2 = t2;
		type = type_;
		parent = parent_;
		time = time_;
	}
	return false;
}
bool floor_effect::isFly(floor_type type_)
{
	return false;
}
bool floor_effect::isSwim(floor_type type_)
{
	return false;
}
bool floor_effect::isNoGround(floor_type type_)
{
	return false;
}
int floor_effect::danger(unit* unit_, bool first_)
{
	int danger_=0;
	if(first_ && env[current_level].isSmokePos(unit_->position.x,unit_->position.y))
	{
		return 0;
		/*smoke *temp_smoke = env[current_level].isSmokePos2(unit_->position.x,unit_->position.y,this);
		if(temp_smoke)
			prev_danger = temp_smoke->danger(unit_,false);*/
	}
	switch(type)
	{
	case FLOORT_STONE:
		danger_ = 0/* unit_->isFly()?0:( unit_->isplayer()?999:8)*/; //이 함정은 괜히 몬스터가 피하면짜증을 불러들일수있음.

		//다만 다른 길이 있으면 우회하는정도는 생각해봄
		return danger_;
	default:
		return 0;
	}
}
		
string floor_effect::GetName()
{
	switch(type)
	{
	case FLOORT_AUTUMN:
		return LocalzationManager::locString(LOC_SYSTEM_FLOOR_EFFECT_AUTUMN);
	case FLOORT_STONE:
		return LocalzationManager::locString(LOC_SYSTEM_FLOOR_EFFECT_STONE);
	case FLOORT_SCHEMA:
		return LocalzationManager::locString(LOC_SYSTEM_FLOOR_EFFECT_SCHEMA);
	case FLOORT_GOLD:
		return LocalzationManager::locString(LOC_SYSTEM_FLOOR_EFFECT_GOLD);
	case FLOORT_NORMAL:
	default:
		return "";
	}
}