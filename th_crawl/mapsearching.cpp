﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mapsearching.cpp
//
// 내용: 맵 서칭 알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "const.h"
#include "display.h"
#include "common.h"
#include "mapsearching.h"
#include "enumMapBuilder.h"
#include "map.h"

int seqence = 0;



/*
ㅏ일반던전
ㅣㅏ안개의호수
ㅣㅣㅏ홍마관
ㅣㅣㅣㅏ도서관
ㅣㅣㅣㄴ지하실
ㅣㅣㄴ요괴의산
ㅣㅣ  ㄴ윳쿠리굴
ㅣㄴ미궁의죽림
ㅣ  ㄴ영원정
짐승굴
ㅏ꿈의세계
ㅏ마계
ㅏ지저
ㄴ하쿠레이신사
*/

MapNode mapNode_normal(LOC_SYSTEM_DUNGEON, 0, MAX_DUNGEUN_LEVEL);
MapNode mapNode_temple(LOC_SYSTEM_DUNGEON_TEMPLE, TEMPLE_LEVEL, 1);
MapNode mapNode_misty(LOC_SYSTEM_DUNGEON_MISTYLAKE, MISTY_LAKE_LEVEL, MAX_MISTY_LAKE_LEVEL);
MapNode mapNode_scarlet(LOC_SYSTEM_DUNGEON_SCARLET, SCARLET_LEVEL, MAX_SCARLET_LEVEL);
MapNode mapNode_library(LOC_SYSTEM_DUNGEON_SCARLET_LIBRARY, SCARLET_LIBRARY_LEVEL, MAX_SCARLET_LIBRARY_LEVEL);
MapNode mapNode_flan(LOC_SYSTEM_DUNGEON_SCARLET_UNDER, SCARLET_UNDER_LEVEL, MAX_SCARLET_UNDER_LEVEL);
MapNode mapNode_moun(LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN, YOUKAI_MOUNTAIN_LEVEL, MAX_YOUKAI_MOUNTAIN_LEVEL);
MapNode mapNode_yukku(LOC_SYSTEM_DUNGEON_YUKKURI, YUKKURI_LEVEL, MAX_YUKKURI_LEVEL);
MapNode mapNode_bamboo(LOC_SYSTEM_DUNGEON_BAMBOO, BAMBOO_LEVEL, MAX_BAMBOO_LEVEL);
MapNode mapNode_eien(LOC_SYSTEM_DUNGEON_EINENTEI, EIENTEI_LEVEL, MAX_EIENTEI_LEVEL);
MapNode mapNode_depth(LOC_SYSTEM_DUNGEON_DEPTH, DEPTH_LEVEL, MAX_DEPTH_LEVEL);
MapNode mapNode_dream(LOC_SYSTEM_DUNGEON_DREAM, DREAM_LEVEL, MAX_DREAM_LEVEL);
MapNode mapNode_moon(LOC_SYSTEM_DUNGEON_MOON, MOON_LEVEL, MAX_MOON_LEVEL);
MapNode mapNode_pande(LOC_SYSTEM_DUNGEON_PANDEMONIUM, PANDEMONIUM_LEVEL, MAX_PANDEMONIUM_LEVEL);
MapNode mapNode_hell(LOC_SYSTEM_DUNGEON_SUBTERRANEAN, SUBTERRANEAN_LEVEL, MAX_SUBTERRANEAN_LEVEL);
MapNode mapNode_haku(LOC_SYSTEM_DUNGEON_HAKUREI, HAKUREI_LEVEL, MAX_HAKUREI_LEVEL);
MapNode mapNode_zigurrat(LOC_SYSTEM_DUNGEON_ZIGURRAT, ZIGURRAT_LEVEL, 1);


MapNode::MapNode(LOCALIZATION_ENUM_KEY key, int map_id_, int max_level_):
map_id(map_id_), max_level(max_level_), key(key)
{
	unique_id = ++seqence;
}


void MapNode::addNode(MapNode* node, int floor)
{
	floor_map.insert(pair<int, int>(node->getMapId(), floor));
	state_map.push_back(node);
}

void MapNode::addStair(MapNode* node, int floor)
{
	floor_map.insert(pair<int, int>(node->getMapId(), floor));
	//state_map.push_back(node);
}



void MapNode::initMapNode()
{
	mapNode_normal = MapNode(LOC_SYSTEM_DUNGEON, 0, MAX_DUNGEUN_LEVEL);
	mapNode_temple = MapNode(LOC_SYSTEM_DUNGEON_TEMPLE, TEMPLE_LEVEL, 1);
	mapNode_misty = MapNode(LOC_SYSTEM_DUNGEON_MISTYLAKE, MISTY_LAKE_LEVEL, MAX_MISTY_LAKE_LEVEL);
	mapNode_scarlet = MapNode(LOC_SYSTEM_DUNGEON_SCARLET, SCARLET_LEVEL, MAX_SCARLET_LEVEL);
	mapNode_library = MapNode(LOC_SYSTEM_DUNGEON_SCARLET_LIBRARY, SCARLET_LIBRARY_LEVEL, MAX_SCARLET_LIBRARY_LEVEL);
	mapNode_flan = MapNode(LOC_SYSTEM_DUNGEON_SCARLET_UNDER, SCARLET_UNDER_LEVEL, MAX_SCARLET_UNDER_LEVEL);
	mapNode_moun = MapNode(LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN, YOUKAI_MOUNTAIN_LEVEL, MAX_YOUKAI_MOUNTAIN_LEVEL);
	mapNode_yukku = MapNode(LOC_SYSTEM_DUNGEON_YUKKURI, YUKKURI_LEVEL, MAX_YUKKURI_LEVEL);
	mapNode_bamboo = MapNode(LOC_SYSTEM_DUNGEON_BAMBOO, BAMBOO_LEVEL, MAX_BAMBOO_LEVEL);
	mapNode_eien = MapNode(LOC_SYSTEM_DUNGEON_EINENTEI, EIENTEI_LEVEL, MAX_EIENTEI_LEVEL);
	mapNode_depth = MapNode(LOC_SYSTEM_DUNGEON_DEPTH, DEPTH_LEVEL, MAX_DEPTH_LEVEL);
	mapNode_dream = MapNode(LOC_SYSTEM_DUNGEON_DREAM, DREAM_LEVEL, MAX_DREAM_LEVEL);
	mapNode_moon = MapNode(LOC_SYSTEM_DUNGEON_MOON, MOON_LEVEL, MAX_MOON_LEVEL);
	mapNode_pande = MapNode(LOC_SYSTEM_DUNGEON_PANDEMONIUM, PANDEMONIUM_LEVEL, MAX_PANDEMONIUM_LEVEL);
	mapNode_hell = MapNode(LOC_SYSTEM_DUNGEON_SUBTERRANEAN, SUBTERRANEAN_LEVEL, MAX_SUBTERRANEAN_LEVEL);
	mapNode_haku = MapNode(LOC_SYSTEM_DUNGEON_HAKUREI, HAKUREI_LEVEL, MAX_HAKUREI_LEVEL);
	mapNode_zigurrat = MapNode(LOC_SYSTEM_DUNGEON_ZIGURRAT, ZIGURRAT_LEVEL, 1);

	mapNode_normal.addNode(&mapNode_temple, TEMPLE);
	mapNode_normal.addNode(&mapNode_misty, MISTY_LAKE);
	mapNode_normal.addNode(&mapNode_bamboo, BAMBOO);
	mapNode_normal.addNode(&mapNode_depth, DEPTH);
	mapNode_normal.addStair(&mapNode_eien, BAMBOO); //되돌아오는 계단

	mapNode_temple.addNode(&mapNode_normal, -1); //돌아옴

	mapNode_misty.addNode(&mapNode_normal, -1); //돌아옴
	mapNode_misty.addNode(&mapNode_scarlet, SCARLET_M);
	mapNode_misty.addNode(&mapNode_moun, YOUKAI_MOUNTAIN);

	mapNode_scarlet.addNode(&mapNode_misty, -1); //돌아옴
	mapNode_scarlet.addNode(&mapNode_library, SCARLET_L);
	mapNode_scarlet.addNode(&mapNode_flan, SCARLET_U);

	mapNode_library.addNode(&mapNode_scarlet, -1); //돌아옴

	mapNode_flan.addNode(&mapNode_scarlet, -1); //돌아옴

	mapNode_moun.addNode(&mapNode_misty, -1); //돌아옴
	mapNode_moun.addNode(&mapNode_yukku, YUKKURI_D);

	mapNode_yukku.addNode(&mapNode_moun, -1); //돌아옴

	//mapNode_bamboo.addNode(&mapNode_normal);
	mapNode_bamboo.addStair(&mapNode_normal, -1);//일방동행

	mapNode_eien.addNode(&mapNode_normal, -1); //돌아옴

	mapNode_depth.addNode(&mapNode_normal, -1); //돌아옴
	mapNode_depth.addNode(&mapNode_dream, DREAM_D);
	mapNode_depth.addNode(&mapNode_pande, PANDEMONIUM);
	mapNode_depth.addNode(&mapNode_hell, SUBTERRANEAN);
	mapNode_depth.addNode(&mapNode_haku, HAKUREI_D);
	mapNode_depth.addNode(&mapNode_zigurrat, ZIGURRAT);
	mapNode_normal.addStair(&mapNode_moon, DREAM_D); //되돌아오는 계단

	//mapNode_dream.addNode(&mapNode_normal);
	mapNode_dream.addStair(&mapNode_depth, -1);//일방동행

	mapNode_moon.addNode(&mapNode_depth, -1); //돌아옴

	//mapNode_pande.addNode(&mapNode_depth);
	mapNode_pande.addStair(&mapNode_depth, -1);//일방동행


	mapNode_hell.addNode(&mapNode_depth, -1); //돌아옴

	mapNode_haku.addNode(&mapNode_depth, -1); //돌아옴

	mapNode_zigurrat.addNode(&mapNode_depth, -1); //돌아옴
	
}


MapNode* MapNode::getFirstNode()
{
	return &mapNode_normal;
}


MapNode* MapNode::getNode(int level_)
{
	if (level_ < TEMPLE_LEVEL)
		return &mapNode_normal;
	else if (level_ == TEMPLE_LEVEL)
		return &mapNode_temple;
	else if (level_ >= MISTY_LAKE_LEVEL && level_ <= MISTY_LAKE_LEVEL + MAX_MISTY_LAKE_LEVEL)
		return &mapNode_misty;
	else if (level_ >= YOUKAI_MOUNTAIN_LEVEL && level_ <= YOUKAI_MOUNTAIN_LEVEL + MAX_YOUKAI_MOUNTAIN_LEVEL)
		return &mapNode_moun;
	else if (level_ >= SCARLET_LEVEL && level_ <= SCARLET_LEVEL + MAX_SCARLET_LEVEL)
		return &mapNode_scarlet;
	else if (level_ >= SCARLET_LIBRARY_LEVEL && level_ <= SCARLET_LIBRARY_LEVEL + MAX_SCARLET_LIBRARY_LEVEL)
		return &mapNode_library;
	else if (level_ >= SCARLET_UNDER_LEVEL && level_ <= SCARLET_UNDER_LEVEL + MAX_SCARLET_UNDER_LEVEL)
		return &mapNode_flan;
	else if (level_ >= BAMBOO_LEVEL && level_ <= BAMBOO_LEVEL + MAX_BAMBOO_LEVEL)
		return &mapNode_bamboo;
	else if (level_ >= EIENTEI_LEVEL && level_ <= EIENTEI_LEVEL + MAX_EIENTEI_LEVEL)
		return &mapNode_eien;
	else if (level_ >= SUBTERRANEAN_LEVEL && level_ <= SUBTERRANEAN_LEVEL + MAX_SUBTERRANEAN_LEVEL)
		return &mapNode_hell;
	else if (level_ >= YUKKURI_LEVEL && level_ <= YUKKURI_LAST_LEVEL)
		return &mapNode_yukku;
	else if (level_ >= DEPTH_LEVEL && level_ <= DEPTH_LAST_LEVEL)
		return &mapNode_depth;
	else if (level_ >= DREAM_LEVEL && level_ <= DREAM_LAST_LEVEL)
		return &mapNode_dream;
	else if (level_ >= MOON_LEVEL && level_ <= MOON_LAST_LEVEL)
		return &mapNode_moon;
	else if (level_ >= PANDEMONIUM_LEVEL && level_ <= PANDEMONIUM_LEVEL + 3)
		return &mapNode_pande;
	else if (level_ >= HAKUREI_LEVEL && level_ <= HAKUREI_LAST_LEVEL)
		return &mapNode_haku;
	else if (level_ == ZIGURRAT_LEVEL)
		return &mapNode_zigurrat;
	else
		return NULL;
}

bool MapNode::isCurrentFloor(int level)
{
	return (level >= map_id) && (level <= map_id + max_level);
}



int MapNode::getFloorStair(int dungeon)
{
	map<int, int>::iterator floor_ = floor_map.find(dungeon);
	if (floor_ == floor_map.end()) {
		return -1;
	}

	if ((*floor_).second == -1)
	{
		return map_id;
	}
	return map_list.dungeon_enter[(*floor_).second].floor;
}

bool SetStairToStack(queue<list<coord_def>> *stairMap, int start_level, bool up) {
	list<coord_def> new_stair;
	if (up)
	{
		for (int i = 0; i < 3; i++)
		{
			if ((env[start_level].isExplore(env[start_level].stair_up[i].x, env[start_level].stair_up[i].y) ||
				env[start_level].isMapping(env[start_level].stair_up[i].x, env[start_level].stair_up[i].y))
				&& env[start_level].isStair(env[start_level].stair_up[i].x, env[start_level].stair_up[i].y))
			{
				new_stair.push_back(env[start_level].stair_up[i]);
			}
		}
	}
	else //down
	{
		if (!environment::isLastFloor(start_level))
		{
			for (int i = 0; i < 3; i++)
			{
				if ((env[start_level].isExplore(env[start_level].stair_down[i].x, env[start_level].stair_down[i].y) ||
					env[start_level].isMapping(env[start_level].stair_down[i].x, env[start_level].stair_down[i].y))
					&& env[start_level].isStair(env[start_level].stair_down[i].x, env[start_level].stair_down[i].y))
				{
					new_stair.push_back(env[start_level].stair_down[i]);
				}
			}
		}
	}
	if (new_stair.empty())
		return false;
	stairMap->push(new_stair);
	return true;
}


bool MapNode::getFloorStairToStack(queue<list<coord_def>> *stairMap, int dungeon)
{
	list<coord_def> new_stair;
	map<int, int>::iterator floor_ = floor_map.find(dungeon);
	if (floor_ == floor_map.end()) {
		return false;
	}

	if ((*floor_).second == -1)
	{
		return SetStairToStack(stairMap, map_id, true);
	}

	coord_def stair_ = map_list.dungeon_enter[(*floor_).second].pos;

	if ((env[map_list.dungeon_enter[(*floor_).second].floor].isExplore(stair_.x, stair_.y) ||
		env[map_list.dungeon_enter[(*floor_).second].floor].isMapping(stair_.x, stair_.y))
		&& env[map_list.dungeon_enter[(*floor_).second].floor].isStair(stair_.x, stair_.y))
	{
		new_stair.push_back(stair_);
		stairMap->push(new_stair);
		return true;
	}
	else
		return false;


}

void testLoopAndPrint(MapNode* node, int prev, int depth)
{
	auto *list = node->getMap();
	auto it = list->begin();
	for (; it != node->getMap()->end(); it++)
	{
		if (prev != (*it)->getUniqueId())
		{
			testLoopAndPrint((*it), node->getUniqueId(), depth + 1);
		}
	}

}
void MapNode::testLoopAllNode()
{
	enterlog();
	testLoopAndPrint(getFirstNode(), -1, 0);
}



bool getShortCut(stack<MapNode*>* stack_, MapNode* node, MapNode* goal, int prev, int depth)
{
	auto *list = node->getMap();
	auto it = list->begin();
	for (; it != node->getMap()->end(); it++)
	{
		if (prev != (*it)->getUniqueId())
		{
			if ((*it) == goal) {
				stack_->push((*it));
				return true;
			}


			if (getShortCut(stack_, (*it), goal, node->getUniqueId(), depth + 1))
			{
				stack_->push((*it));
				return true;
			}
		}
	}
	return false;
}






bool MapNode::searchRoad(int start_level, int goal_level, queue<list<coord_def>>* stairMap)
{
	MapNode* start = getNode(start_level);
	MapNode* goal = getNode(goal_level);
	stack<MapNode*> stackMap;
	
	enterlog();
	if (start == NULL || goal == NULL)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_UKNOWN) + " ", false, false, false, CL_help);
		return false;
	}

	bool return_ = getShortCut(&stackMap, start, goal, -1, 0);
	stackMap.push(start);

	if(return_)
	{
		enterlog();
		while (!stackMap.empty()) {
			MapNode* current_dungeon = stackMap.top();
			stackMap.pop();
			if (stackMap.empty())
			{
				break;
			}
			MapNode* next_dungeon = stackMap.top();


			while (current_dungeon->isCurrentFloor(start_level))
			{

				int stair_level = current_dungeon->getFloorStair(next_dungeon->getMapId());
				if (stair_level == start_level) 
				{
					int next_floor = next_dungeon->getFloorStair(current_dungeon->getMapId());
					if (next_floor == -1) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_CANT_FINE_PATH), true, false, false, CL_help);
						return false;
					}

					if (!current_dungeon->getFloorStairToStack(stairMap, next_dungeon->getMapId())) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_CANT_FINE_PATH), false, false, false, CL_help);
						return false;
					}

					
					start_level = next_floor;
					break;
				}
				else if (stair_level > start_level)
				{
					if (!SetStairToStack(stairMap, start_level, false))
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_CANT_FINE_PATH), false, false, false, CL_help);
						return false;
					}
					start_level++;
				}
				else
				{
					if(!SetStairToStack(stairMap, start_level, true))
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_CANT_FINE_PATH), false, false, false, CL_help);
						return false;
					}
					start_level--;
				}
			}
			//char temp[100];
			//sprintf_s(temp, 100, "(>)");
			//printlog(temp, false, false, false, CL_magic);
		}
	}





	if(return_)
	{
		return true;
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DUNGEON_CANT_FINE_PATH), false, false, false, CL_help);
		return false;
	}
}
