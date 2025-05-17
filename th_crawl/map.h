﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: map.h
//
// 내용: 지형제작 알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "enum.h"


enum sub_dungeon
{
	TEMPLE=0,
	MISTY_LAKE,
	YOUKAI_MOUNTAIN,
	SCARLET_M,	
	SCARLET_L,
	SCARLET_U,
	BAMBOO,
	//EIENTEI,
	SUBTERRANEAN,	
	YUKKURI_D,
	DEPTH,
	DREAM_D,
	//MOON_D,
	PANDEMONIUM,
	HAKUREI_D,
	ZIGURRAT,
	MAX_SUB_DUNGEON
};
enum valut_pattern
{
	VP_FIRST=1000,
	VP_YOUKAI_MOUNTAIN_LAST=VP_FIRST,
	VP_SCARLET_LAST,
	VP_EIENTEI_LAST,
	VP_PANDEMONIUM_1_LAST,
	VP_PANDEMONIUM_2_LAST,
	VP_PANDEMONIUM_3_LAST,
	VP_YUKKURI_LAST,
	VP_MOON_LAST,
	VP_SUBTERRANEAN_LAST,
	VP_HAKUREI_LAST,
	VP_LAST
};

struct pos_infor
{
	bool detected;
	coord_def pos;
	int floor;
	pos_infor():detected(false),pos(0,0),floor(-1){};
	void set(bool detected_,int x_,int y_,int floor_){detected=detected_;pos.x=x_;pos.y=y_;floor=floor_;};
};

class map_infor
{
public:
	pos_infor dungeon_enter[MAX_SUB_DUNGEON];
	pos_infor temple[GT_LAST];
	int tutorial;
	int god_num;
	int bamboo_count;
	int bamboo_rate;
	bool bamboo_tewi;
	unsigned int random_number;
};


typedef struct mapdummy_mon
{
	int id;
	uint64_t flag;
	coord_def pos;
	mapdummy_mon():id(0),flag(0),pos(0,0){};
	mapdummy_mon(int id_, uint64_t flag_, coord_def pos_):id(id_),flag(flag_),pos(pos_){};
}mapdummy_mon;


typedef struct mapdummy_item
{
	item_infor id;
	coord_def pos;
	mapdummy_item():id(),pos(0,0){};
	mapdummy_item(item_infor& id_, coord_def pos_):id(id_),pos(pos_){};
}mapdummy_item;

typedef struct mapdummy_event
{
	int id;	
	coord_def position;
	event_type type;
	mapdummy_event():id(),position(0,0),type(EVT_ABOVE){};
	mapdummy_event(int id_, coord_def position_, event_type type_):id(id_),position(position_),type(type_){};
}mapdummy_event;



class map_dummy
{
public:
	coord_def pos;
	bool wall;
	int floor;
	int size_x;
	int size_y;
	int pattern;
	int flag;
	dungeon_tile_type **tiles;
	coord_def m_entrance;
	coord_def m_exit;
	bool connect_enter;
	bool connect_exit;
	dungeon_tile_type floor_tex;
	dungeon_tile_type wall_tex;
	string name;

	list<mapdummy_mon> monster_list;
	list<mapdummy_item> item_list;
	list<mapdummy_event> event_list;
	vector<dungeon_tile_type> sp_tile_list;
	list<coord_def> pos_list;

	map_dummy(int floor_, coord_def pos_,bool wall_,int size_x_,int size_y_,int pattern_, dungeon_tile_type floor_tex_, dungeon_tile_type wall_tex_);
	~map_dummy();
	void patternSet(); 
	bool collution(const coord_def& point,int size_x_ = 0,int size_y_ = 0);
	bool plus_collution(const coord_def& point,int size_x_,int size_y_);
	void make_map(environment& env_pointer, bool wall_ = true, bool stair_input_ = false);
	void make_door(environment& env_pointer);
	void mask(environment& env_pointer, bool wall_ = true);
	void eventmapmake(environment& env_pointer, int count, bool wall_ = true);
	void SetEnter(coord_def c);
	void SetExit(coord_def c);
	coord_def GetEntrance(){return m_entrance;};
	coord_def GetExit(){return m_exit;};
	void SetConnectEnter(bool ok_){connect_enter=ok_;};
	void SetConnectExit(bool ok_){connect_exit=ok_;};
	bool GetConnect(){return (connect_exit||connect_enter);};
	coord_def getNextPos();
};

extern map_infor map_list;

void initMap();
void map_algorithms(int num);
const char* common_base_pattern(int floor_, map_dummy* map);
const char* temple_pattern(map_dummy* map);
const char* misty_lake_pattern(map_dummy* map);
const char* youkai_mountain_pattern(map_dummy* map);
const char* scarlet_pattern(map_dummy* map);

const char* scarlet_library_pattern(map_dummy* map);
const char* scarlet_under_pattern(map_dummy* map);
const char* bamboo_pattern(map_dummy* map);
const char* subterranean_pattern(map_dummy* map);

const char* yukkuri_pattern(map_dummy* map);
const char* depth_pattern(map_dummy* map);
const char* dream_pattern(map_dummy* map);
const char* pandemonium_pattern(map_dummy* map);
const char* hakurei_pattern(map_dummy* map);
const char* zigurrat_pattern(map_dummy* map);




const char* youkai_last_vault_pattern(map_dummy* map);
const char* scarlet_last_vault_pattern(map_dummy* map);
const char* eientei_vault_pattern(map_dummy* map);
const char* pandemonium_baykuren_last_vault_pattern(map_dummy* map);
const char* pandemonium_ice_last_vault_pattern(map_dummy* map);
const char* pandemonium_shinki_last_vault_pattern(map_dummy* map);
const char* yukkuri_last_vault_pattern(map_dummy* map);
const char* moon_last_vault_pattern(map_dummy* map);
const char* subterranean_last_vault_pattern(map_dummy* map);
const char* hakurei_last_vault_pattern(map_dummy* map);
const char* altar_pattern(map_dummy* map, god_type god_);