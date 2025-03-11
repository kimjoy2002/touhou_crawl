//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Astar.cpp
//
// 내용: Astar알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////




#include "rect.h"
#include "Astar.h"
#include "environment.h"

searchnode astar_node[DG_MAX_X][DG_MAX_Y];

int PathCost(const coord_def& start,const coord_def&  goal)
{
	return abs(start.x - goal.x)+abs(start.y - goal.y);
}


void priqueue_push(list<searchnode*>& queues,searchnode* data)
{
	if(!queues.empty())
	{
		list<searchnode*>::iterator it;
		for(it = queues.begin();it != queues.end();it++)
		{
			if((*it)->tc>data->tc)
				break;
		}
		queues.insert(it,data);
		data->opcl |= 1;
	}
	else
	{
		queues.insert(queues.begin(),data);
		data->opcl |= 1;

	}
}

bool list_search(list<searchnode*>& queues,searchnode* data)
{
	list<searchnode*>::iterator it;
	for(it = queues.begin();it != queues.end();it++)
	{
		if((*it)->pos == data->pos)
			return true;
	}
	return false;
}

bool PathSearch(const coord_def& start,const coord_def& goal, stack<coord_def>& will_move, search_type type, int floor_, bool alway_fly_, bool alway_swim_)
{
	coord_def ano_goal = start;
	bool is_mapping = env[floor_].isMapping(goal.x,goal.y);
	bool is_explore = (env[floor_].isExplore(goal.x,goal.y) || type >= ST_MONSTER_NORMAL || type == ST_SEARCH);
	bool is_move = (env[floor_].isMove(goal.x,goal.y,alway_fly_,alway_swim_) || type == ST_SEARCH);
	bool is_block = env[floor_].isBlockPos(goal.x, goal.y) && type < ST_MONSTER_NORMAL;
	if(!((is_explore || is_mapping) && is_move && !is_block))
	{
		return false;
	}
	if(type == ST_MAP)
	{
		bool not_good = true;
		rect_iterator it(goal,1,1);
		for(;!it.end();it++)
		{
			if((*it) ==	goal)
				continue;
			if(env[floor_].isMove(it->x,it->y,alway_fly_,alway_swim_))
			{
				not_good = false;
				break;
			}
		}
		if(not_good)
			return false;
	}

	int heuristic = (type == ST_MAP?10:(type != ST_SEARCH?5:0));
	list<searchnode*> Open;
	for(int x=0;x<DG_MAX_X;x++)
	{
		for(int y=0;y<DG_MAX_Y;y++)
		{
			astar_node[x][y].opcl = 0;
		}
	}

	priqueue_push(Open,astar_node[start.x][start.y].Set(start,0,PathCost(start,goal),NULL));//스타트지점을 오픈 푸시

	while(!Open.empty())
	{
		searchnode* node = Open.front();
		Open.pop_front();
		node->opcl &= ~1;
		node->opcl |= 2;
		if((node->pos == goal && type != ST_SEARCH ) || (type == ST_SEARCH && ano_goal !=  start && ano_goal ==  node->pos)) //골인
		{
			searchnode* path = node;
			while(path && path->pos != start)
			{
				will_move.push(path->pos);
				path = path->parent;
			}
			return true;
		}
		else //새로운 정보를 갱신
		{
			rect_iterator it(node->pos,1,1);
			for(;!it.end();it++)
			{
				if((*it) == node->pos)
					continue;
				if(type == ST_MAP && it.isdiagonal())
					continue;
				searchnode* newnode = &astar_node[it->x][it->y];
				int newcost = node->cfs+1;
				bool is_open = (newnode->opcl & 1);
				bool is_close = (newnode->opcl & 2);
				bool is_mapping = env[floor_].isMapping(it->x,it->y);
				bool is_explore = (env[floor_].isExplore(it->x,it->y) || type >= ST_MONSTER_NORMAL);
				bool is_door = (env[floor_].isDoor(it->x,it->y) && type < ST_MONSTER_NORMAL);//열수있는 문이냐
				bool is_forbid = env[floor_].isForbidZone(it->x, it->y) && type < ST_MONSTER_NORMAL;
				bool is_block = env[floor_].isBlockPos(it->x, it->y) && type < ST_MONSTER_NORMAL;
				
				bool is_move = ((is_explore || is_mapping) && (env[floor_].isMove(it->x,it->y,alway_fly_,alway_swim_) || is_door) && !is_forbid && !is_block);
				if(!is_move)
				{
					if(type == ST_SEARCH && !is_explore && ano_goal ==  start && !is_block)
					{
						ano_goal = (*it);
					}
					else
						continue;
				}
				else if((is_open || is_close) && (newnode->cfs <= newcost))
				{
					continue;
				}
				//else   <- 자동탐색때문에 type == ST_SEARCH
				{	
					newnode->Set(coord_def(it->x,it->y),newcost, heuristic*PathCost(coord_def(it->x,it->y),goal),node);
					if(is_close)
					{
						newnode->opcl &= ~2;
					}
					if(is_open)
					{
						Open.remove(newnode);
						priqueue_push(Open,newnode);
					}
					else
					{
						priqueue_push(Open,newnode);
					}
				}
			}
		}
	}
	return false;
}




