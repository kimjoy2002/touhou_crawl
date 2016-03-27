//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: summon.cpp
//
// 내용: 소환물 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "summon.h"
#include "save.h"
#include "skill_use.h"
#include "environment.h"


void summon_info::init()
{
	parent_map_id = -1;
	summon_id = SKD_OTHER;
	max_num = -1;
}

void summon_info::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, parent_map_id);
	SaveData<SUMMON_KIND>(fp, summon_id);
	SaveData<int>(fp, max_num);

}
void summon_info::LoadDatas(FILE *fp)
{
	LoadData<int>(fp, parent_map_id);
	LoadData<SUMMON_KIND>(fp, summon_id);
	LoadData<int>(fp, max_num);
}

bool summon_check(coord_def c, unit* order, bool fly_, bool swim_)
{ //현재 소환되는 위치가 소환사의 거리와 확인하는 함수
	if(!env[current_level].isMove(c.x, c.y, fly_, swim_))
		return false; //움직일수없는 위치는 소환 x
	
	if(env[current_level].isMonsterPos(c.x,c.y)) 
		return false; //이미 몬스터가 있는 위치는 소환 X

	if(order == &you)
	{//소환사가 플레이어라면
		if(!env[current_level].isInSight(c)) //시야내에서만 소환된다.
			return false;
	}
	else if(!order->isplayer())
	{//소환사가 몬스터라면
		//몬스터의 시야를 확인한다.		
		if(!((monster*)order)->isMonsterSight(c))
			return false;
	}
	return true;

}



int GetSummonMaxNumber(spell_list skill)
{
	switch(skill)
	{
	case SPL_SUMMON_MOOK:
		return 5;
	case SPL_SUMMON_BIRD:
		return 4;
	case SPL_SUMMON_BUG:
		return 5;
	case SPL_SUMMON_PENDULUM:
		return 1;
	case SPL_SUMMON_SEKIBANKI:
		return 4;
	case SPL_SUMMON_OPTION:
		return 2;
	case SPL_SUMMON_GOLEM:
		return 1;
	case SPL_SUMMON_UNZAN:
		return 1;
	case SPL_SUMMON_UNZAN_PUNCH:
		return 4;
	case SPL_SUMMON_ZOMBIE_FAIRY:
		return 8;
	case SPL_SUMMON_UFO:
		return 5;
	case SPL_FLAN_BUSIN:
		return 3;
	default:
		return -1;
	}
}


SUMMON_KIND GetSummonKind(spell_list skill)
{
	switch(skill)
	{
	case SPL_SUMMON_MOOK:
		return SKD_SUMMON_MOOK;
	case SPL_SUMMON_BIRD:
		return SKD_SUMMON_BIRD;
	case SPL_SUMMON_BUG:
		return SKD_SUMMON_BUG;
	case SPL_SUMMON_PENDULUM:
		return SKD_SUMMON_PENDULUM;
	case SPL_SUMMON_SEKIBANKI:
		return SKD_SUMMON_SEKIBANKI;
	case SPL_SUMMON_OPTION:
		return SKD_SUMMON_OPTION;
	case SPL_SUMMON_GOLEM:
		return SKD_SUMMON_GOLEM;
	case SPL_SUMMON_UNZAN:
		return SKD_SUMMON_UNZAN;
	case SPL_SUMMON_UNZAN_PUNCH:
		return SKD_SUMMON_UNZAN_PUNCH;
	case SPL_SUMMON_ZOMBIE_FAIRY:
		return SKD_SUMMON_ZOMBIE_FAIRY;
	case SPL_SUMMON_UFO:
		return SKD_SUMMON_UFO;
	case SPL_FLAN_BUSIN:
		return SKD_SUMMON_FLAN;
	default:
		return SKD_OTHER;
	}

}
bool IsIndepend_summoner(SUMMON_KIND skill)
{
	switch(skill)
	{
	case SKD_OTHER:
	default:
		return true;
	}
}