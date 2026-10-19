//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: instance_dungeon.h
//
// 내용: 일회용 인스턴스 서브던전 (컨트롤O에 잡히지 않는 1층짜리 던전)
//
// 새 던전 추가 방법
//  1. instance_dungeon_type 끝(IDG_MAX 바로 앞)에 값을 추가한다. (세이브에 값이 그대로 저장되므로 중간 삽입/삭제 금지)
//  2. instance_dungeon.cpp의 instance_dungeon_list에 정보 한줄을 추가한다.
//  3. 맵을 만드는 함수(make_map)를 만든다. MakeInstanceMapFromPattern으로 아스키 맵을 그대로 쓰거나 직접 env를 채워도 된다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __INSTANCE_DUNGEON_H__
#define __INSTANCE_DUNGEON_H__

#include <vector>
#include <map>
#include <stdio.h>
#include "common.h"
#include "enum.h"
#include "localization.h"

using namespace std;

//인스턴스 던전의 종류
enum instance_dungeon_type
{
	IDG_NONE = -1,
	IDG_FAIRY_TREE = 0, //요정이 사는 거목 (초반, 삼월정)
	IDG_DARK_FOREST_PATH, //어두운 숲길 (초반, 임시)
	IDG_MAYOIGA, //마요이가 (초반, 임시)
	IDG_MAX
};

//던전이 나오는 시기
enum instance_dungeon_tier
{
	IDT_EARLY = 0, //던전 3~5층
	IDT_MIDDLE, //안개의 호수 후반, 홍마관/요괴산/마법의 숲 1층
	IDT_LATE, //짐승길
	IDT_MAX
};

enum instance_dungeon_state
{
	IDS_READY = 0, //아직 들어가지 않음
	IDS_ENTERED, //들어가 있음
	IDS_CLEAR, //클리어함
	IDS_CLOSED //클리어하지 않고 나옴
};

struct instance_dungeon_slot
{
	instance_dungeon_type type;
	int floor; //입구가 있는 층
	coord_def pos; //입구 위치
	instance_dungeon_state state;
	int named_pick;
	instance_dungeon_slot() :type(IDG_NONE), floor(-1), pos(0, 0), state(IDS_READY), named_pick(-1) {};
};

struct instance_dungeon_infor
{
	instance_dungeon_type type;
	instance_dungeon_tier tier;
	LOCALIZATION_ENUM_KEY name;
	const char* id_name;
	vector<monster_index> named;
	void(*make_map)(int floor_, const instance_dungeon_slot& slot_);
	bool(*is_clear)(int floor_);
	bool(*can_choose)();
	bool named_one_of;
};

class instance_dungeon_manager
{
public:
	vector<instance_dungeon_slot> slots;
	int current;

	instance_dungeon_manager() :current(-1) {};
	void init();
	void initForOldSave(); //마이그레이션
	void SaveDatas(FILE* fp);
	void LoadDatas(FILE* fp);

	instance_dungeon_slot* GetSlot(int index_);
	instance_dungeon_slot* GetCurrentSlot();
	int GetSlotIndex(int floor_, const coord_def& pos_);
	void CheckEnterPlaced(int floor_);

	bool CanEnter(int floor_, const coord_def& pos_);
	void Enter(int floor_, const coord_def& pos_);
	void Exit();
	void WizardEnter(instance_dungeon_type type_, int floor_, const coord_def& pos_);
	void TurnEnd();

private:
	void choose(bool old_save_);
};

extern instance_dungeon_manager instance_dungeon;

const instance_dungeon_infor* GetInstanceDungeonInfor(instance_dungeon_type type_);
int GetInstanceBaseFloor(int floor_);
string GetInstanceDungeonName();
instance_dungeon_type GetCurrentInstanceDungeonType();
void map_algorithms_instance(int num);

struct instance_spawn_table
{
	random_extraction<int> all; //'m'
	random_extraction<int> weak; //'n'
	random_extraction<int> strong; //'M'
	random_extraction<int> item; //'i', 'I'
};

struct instance_map_marks
{
	char floor = '.';
	map<char, vector<coord_def>> list;
};

void MakeInstanceMapFromPattern(int floor_, const char* pattern_, int size_x_, int size_y_,
	dungeon_tile_type floor_tex_, dungeon_tile_type wall_tex_, vector<coord_def>* pos_list_ = nullptr,
	instance_spawn_table* table_ = nullptr, instance_map_marks* marks_ = nullptr);

coord_def GetInstancePatternPos(int x_, int y_, int size_x_, int size_y_); //아스키맵의 칸(x_, y_)이 놓이는 맵 좌표
//floor_ 문자 위에 2*2 block_을 count_개 뿌린다
void ScatterInstanceBlocks(string& pattern_, int size_x_, int size_y_, char floor_, char block_, int count_);
//y_min_~y_max_ 줄의 floor_ 문자 중 서로 min_distance_칸 이상 떨어진 위치를 최대 count_개 골라 맵 좌표로 준다.
vector<coord_def> PickInstancePatternPos(const string& pattern_, int size_x_, int size_y_, char floor_,
	int y_min_, int y_max_, int count_, int min_distance_);
//미스티아 루미아 숲 맵
string MakeInstanceStarPattern(int size_, int branch_count_, int wiggle_, int center_radius_, vector<coord_def>* tips_ = nullptr);

void SetFairyTreeTable(instance_spawn_table& table_);
int GetInstanceSpawnMonster(instance_spawn_table& table_, int power_); //그룹이 비어서 못 고르면 -1
bool HasInstanceNamedEvent(int floor_); //아직 등장하지 않은 EVL_INSTANCE_NAMED가 있는지

struct item_infor;
int GetInstanceFloorMonster(int floor_, int power_); //power_: getMonsterFromFloor_flag
void CreateInstanceFloorItem(int floor_, item_infor* item_);
class monster;
monster* AddInstanceMonster(int floor_, int id_, const coord_def& pos_, uint64_t flag_ = 0);

#endif // __INSTANCE_DUNGEON_H__
