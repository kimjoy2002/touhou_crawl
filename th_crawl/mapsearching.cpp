//////////////////////////////////////////////////////////////////////////////////////////////////
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
#include "map.h"

int seqence = 0;



/*
ㅏ일반던전
ㅣㅏ안개의호수
ㅣㅣㅏ홍마관
ㅣㅣㅣㅏ도서관
ㅣㅣㅣㄴ지하실
ㅣㅣㄴ요괴의산
ㅣㅣ　ㄴ윳쿠리굴
ㅣㄴ미궁의죽림
ㅣ　ㄴ영원정
짐승굴
ㅏ꿈의세계
ㅏ마계
ㅏ지저
ㄴ하쿠레이신사
*/

MapNode mapNode_normal("일반던전", 0, MAX_DUNGEUN_LEVEL);
MapNode mapNode_temple("신전", TEMPLE_LEVEL, 1);
MapNode mapNode_misty("안개의호수", MISTY_LAKE_LEVEL, MAX_MISTY_LAKE_LEVEL);
MapNode mapNode_scarlet("홍마관", SCARLET_LEVEL, MAX_SCARLET_LEVEL);
MapNode mapNode_library("도서관", SCARLET_LIBRARY_LEVEL, MAX_SCARLET_LIBRARY_LEVEL);
MapNode mapNode_flan("지하실", SCARLET_UNDER_LEVEL, MAX_SCARLET_UNDER_LEVEL);
MapNode mapNode_moun("요괴의산", YOUKAI_MOUNTAIN_LEVEL, MAX_YOUKAI_MOUNTAIN_LEVEL);
MapNode mapNode_yukku("윳쿠리굴", YUKKURI_LEVEL, MAX_YUKKURI_LEVEL);
MapNode mapNode_bamboo("미궁의죽림", BAMBOO_LEVEL, MAX_BAMBOO_LEVEL);
MapNode mapNode_eien("영원정", EIENTEI_LEVEL, MAX_EIENTEI_LEVEL);
MapNode mapNode_depth("짐승길", DEPTH_LEVEL, MAX_DEPTH_LEVEL);
MapNode mapNode_dream("꿈의세계", DREAM_LEVEL, MAX_DREAM_LEVEL);
MapNode mapNode_moon("달의세계", MOON_LEVEL, MAX_MOON_LEVEL);
MapNode mapNode_pande("마계", PANDEMONIUM_LEVEL, MAX_PANDEMONIUM_LEVEL);
MapNode mapNode_hell("지저", SUBTERRANEAN_LEVEL, MAX_SUBTERRANEAN_LEVEL);
MapNode mapNode_haku("하쿠레이신사", HAKUREI_LEVEL, MAX_HAKUREI_LEVEL);
MapNode mapNode_zigurrat("꿈의세계 루나틱", ZIGURRAT_LEVEL, 1);


MapNode::MapNode(const char* name_, int map_id_, int max_level_):
name(name_), map_id(map_id_), max_level(max_level_)
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
	//char temp[100];
	//sprintf_s(temp, 100, "테스트) %d번째 - %s", node->getUniqueId(), node->getName().c_str());
	//for (int i = 0; i<depth; i++)
	//	printlog("ㄴ", false, false, false, CL_help);
	//printlog(temp, true, false, false, CL_help);


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
				//char temp[100];
				//sprintf_s(temp, 100, "도착) %s", (*it)->getName().c_str());
				//printlog(temp, true, false, false, CL_help);
				stack_->push((*it));
				return true;
			}


			if (getShortCut(stack_, (*it), goal, node->getUniqueId(), depth + 1))
			{
				//char temp[100];
				//sprintf_s(temp, 100, "역추적) %s" , (*it)->getName().c_str());
				//printlog(temp, true, false, false, CL_help);
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
		printlog("알 수 없는 위치.", false, false, false, CL_help);
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
				//char temp[100];
				//sprintf_s(temp, 100, "[도착]%d", start_level);
				//printlog(temp, false, false, false, CL_magic);
				break;
			}
			MapNode* next_dungeon = stackMap.top();


			while (current_dungeon->isCurrentFloor(start_level))
			{
				//char temp[100];
				//sprintf_s(temp, 100, "%d-", start_level);
				//printlog(temp, false, false, false, CL_magic);

				int stair_level = current_dungeon->getFloorStair(next_dungeon->getMapId());
				if (stair_level == start_level) 
				{
					int next_floor = next_dungeon->getFloorStair(current_dungeon->getMapId());
					if (next_floor == -1) {
						printlog("가는 길을 알 수 없습니다.", true, false, false, CL_help);
						return false;
					}

					if (!current_dungeon->getFloorStairToStack(stairMap, next_dungeon->getMapId())) {
						printlog("가는 길을 알 수 없습니다.", false, false, false, CL_help);
						return false;
					}

					
					start_level = next_floor;
					break;
				}
				else if (stair_level > start_level)
				{
					if (!SetStairToStack(stairMap, start_level, false))
					{
						printlog("가는 길을 알 수 없습니다.", false, false, false, CL_help);
						return false;
					}
					start_level++;
				}
				else
				{
					if(!SetStairToStack(stairMap, start_level, true))
					{
						printlog("가는 길을 알 수 없습니다.", false, false, false, CL_help);
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
		//printlog("위치를 정상적으로 찾았습니다.", false, false, false, CL_help);
		return true;
	}
	else
	{
		printlog("그 곳까지 가는 길을 알 수 없습니다.", false, false, false, CL_help);
		return false;
	}
}
