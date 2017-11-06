//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: summon.h
//
// 내용: 소환물 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SUMMON_H__
#define  __SUMMON_H__

#include <stdio.h>
#include "common.h"

enum spell_list;
class unit;


enum SUMMON_KIND
{
	SKD_OTHER,
	SKD_SUMMON_BUG,
	SKD_SUMMON_MOOK,
	SKD_SUMMON_BIRD,
	SKD_SUMMON_PENDULUM,
	SKD_SUMMON_ONBASIRA,
	SKD_SUMMON_SEKIBANKI,
	SKD_SUMMON_OPTION,
	SKD_SUMMON_GOLEM,
	SKD_SUMMON_UNZAN,
	SKD_SUMMON_UNZAN_PUNCH,
	SKD_SUMMON_ZOMBIE_FAIRY,
	SKD_SUMMON_UFO,
	SKD_SUMMON_SHINKI,
	SKD_SUMMON_SWAKO_FLOG,
	SKD_SUMMON_SWAKO_MISYAGUZI,
	SKD_SUMMON_FLAN,
	SKD_SUMMON_LESSOR_DEMON,
	SKD_SUMMON_DREAM,
	SKD_SUMMON_DOLLS_WAR,
	SKD_SUMMON_FAKE_DOLLS_WAR,
	SKD_SUMMON_NAMAZ,
	SKD_SUMMON_RACOON,
	SKD_SUMMON_YOUKAI,
	SKD_SUMMON_ANCHOR,
	SKD_SUMMON_MAI,
	SKD_SUMMON_SATONO
};

class summon_info
{
public:
	int parent_map_id; //소환사의 맵 아이디
	SUMMON_KIND summon_id; //무슨 서먼인가
	int max_num; //소환물 최대 갯수
	summon_info():
	parent_map_id(-1),summon_id(SKD_OTHER),  max_num(-1)
	{}
	summon_info(int parent_map_id_, SUMMON_KIND summon_id_, int max_num_):
	parent_map_id(parent_map_id_),summon_id(summon_id_),  max_num(max_num_)
	{}
	void Setting(int parent_map_id_, SUMMON_KIND summon_id_, int max_num_)
	{
		parent_map_id = parent_map_id_;
		summon_id = summon_id_;
		max_num = max_num_;
	}
	void init();
	
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
};
bool summon_check(coord_def c, coord_def order, bool fly_, bool swim_); //이 위치에 소환해도 되는가?
int GetSummonMaxNumber(spell_list skill);//최대소환갯수
SUMMON_KIND GetSummonKind(spell_list skill);
bool IsIndepend_summoner(SUMMON_KIND skill);//그것은 소환사의죽음에 따라 사라지는가?



#endif // __SUMMON_H__
