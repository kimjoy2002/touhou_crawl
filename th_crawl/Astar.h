//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Astar.h
//
// 내용: Astar알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ASTAR_H__
#define  __ASTAR_H__

#include "common.h"
#include "enum.h"
#include <queue>

extern int current_level;


typedef struct searchnode
{
	coord_def pos;
	int cfs; //cost from start
	int ctg; //cost to goal
	int tc; //토탈 코스트
	char opcl; //0은 없음 1은 오픈 2는 클로즈
	struct searchnode* parent;
	searchnode():pos(0,0), cfs(0), ctg(0), tc(0), parent(NULL)
	{}
	searchnode(const coord_def& pos_,int cfs_, int ctg_,searchnode* parent_)
	{
		pos = pos_;
		cfs = cfs_;
		ctg = ctg_;
		tc = cfs+ctg;
		parent = parent_;
	}
	searchnode* Set(const coord_def& pos_,int cfs_, int ctg_,searchnode* parent_)
	{
		pos = pos_;
		cfs = cfs_;
		ctg = ctg_;
		tc = cfs+ctg;
		parent = parent_;
		return this;
	}
}searchnode;


bool PathSearch(const coord_def& start,const coord_def&  goal, stack<coord_def>& will_move, search_type type, int floor_ = current_level, bool alway_fly_= false, bool alway_swim_= false);

extern searchnode astar_node[DG_MAX_X][DG_MAX_Y];



#endif // __ASTAR_H__