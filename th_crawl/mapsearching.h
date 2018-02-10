//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mapsearching.h
//
// 내용: 맵 서칭 알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


#include <string>
#include <list>
#include <queue>
#include <map>

using namespace std;

class MapNode //현재 이어지는 맵 노드 탐색
{
	list<MapNode*> state_map; //이어지는 맵 노드들
	int map_id;
	int max_level;
	int unique_id;
	string name;
	map<int, int> floor_map;

public:
	MapNode(const char* name, int map_id_, int max_level_);

	void addNode(MapNode* node, int floor);
	void addStair(MapNode* node, int floor);

	static void initMapNode();
	static MapNode* getFirstNode();
	static MapNode* getNode(int level_);
	static void testLoopAllNode();
	static bool searchRoad(int start_level, int goal_level, queue<list<coord_def>>* stairMap);

	int getMapId() { return map_id; };
	int getUniqueId() { return unique_id; };
	string getName() { return name; };
	bool isCurrentFloor(int level);
	int getFloorStair(int dungeon);
	bool getFloorStairToStack(queue<list<coord_def>> *stairMap, int dungeon);

	list<MapNode*>* getMap() { return &state_map; };
};


