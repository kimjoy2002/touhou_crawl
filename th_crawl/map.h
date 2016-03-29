//////////////////////////////////////////////////////////////////////////////////////////////////
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
	MAX_SUB_DUNGEON
};
enum valut_pattern
{
	VP_FIRST=1000,
	VP_YOUKAI_MOUNTAIN_LAST=VP_FIRST,
	VP_SCARLET_LAST,
	VP_EIENTEI_LAST,
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
	int god_num;
	int bamboo_count;
	int bamboo_rate;
};


typedef struct mapdummy_mon
{
	int id;
	int flag;
	coord_def pos;
	mapdummy_mon():id(0),flag(0),pos(0,0){};
	mapdummy_mon(int id_, int flag_, coord_def pos_):id(id_),flag(flag_),pos(pos_){};
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
	int size_x;
	int size_y;
	int pattern;
	int flag;
	dungeon_tile_type **tiles;
	coord_def m_entrance;
	coord_def m_exit;
	bool connect_enter;
	bool connect_exit;

	list<mapdummy_mon> monster_list;
	list<mapdummy_item> item_list;
	list<mapdummy_event> event_list;
	vector<dungeon_tile_type> sp_tile_list;

	map_dummy(coord_def pos_,bool wall_,int size_x_,int size_y_,int pattern_);
	~map_dummy();
	void patternSet();
	bool collution(const coord_def& point,int size_x_ = 0,int size_y_ = 0);
	bool plus_collution(const coord_def& point,int size_x_,int size_y_);
	void make_map(environment& env_pointer, bool wall_ = true);
	void make_door(environment& env_pointer);
	void mask(environment& env_pointer);
	void SetEnter(coord_def c);
	void SetExit(coord_def c);
	coord_def GetEntrance(){return m_entrance;};
	coord_def GetExit(){return m_exit;};
	void SetConnectEnter(bool ok_){connect_enter=ok_;};
	void SetConnectExit(bool ok_){connect_exit=ok_;};
	bool GetConnect(){return (connect_exit||connect_enter);};
};

extern map_infor map_list;

void initMap();
void map_algorithms(int num);
char* temple_pattern(map_dummy* map);
char* misty_lake_pattern(map_dummy* map);
char* youkai_mountain_pattern(map_dummy* map);
char* scarlet_pattern(map_dummy* map);

char* scarlet_library_pattern(map_dummy* map);
char* scarlet_under_pattern(map_dummy* map);
char* bamboo_pattern(map_dummy* map);
char* subterranean_pattern(map_dummy* map);



char* youkai_last_vault_pattern(map_dummy* map);
char* scarlet_last_vault_pattern(map_dummy* map);
char* eientei_vault_pattern(map_dummy* map);
char* altar_pattern(map_dummy* map, god_type god_);