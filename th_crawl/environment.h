//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: environment.h
//
// 내용: 맵과 게임데이터
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ENVIRONMENT_H__
#define  __ENVIRONMENT_H__

#include "enum.h"
#include "common.h"
#include "monster.h"
#include "player.h"
#include "item.h"
#include "texture.h"


class smoke;
class floor_effect;
class events;
class forbid;

enum floor_type;

enum AUTOTILE_KIND {
	AUTOTILE_WALL = 0,
	AUTOTILE_WATER,
	AUTOTILE_MAX
};

class dungeon_tile
{
public:
	dungeon_tile_type tile;
	int flag;
	char silence_count;
	char violet_count;
	char santuary_count;
	char forbid_count;
	char forbid_count2;
	unsigned char autotile_bitmap[AUTOTILE_MAX]; //하나는 벽, 하나는 물
	dungeon_tile():tile(DG_FLOOR),flag(0),silence_count(0),violet_count(0){};
	dungeon_tile(dungeon_tile_type tile_, char flag_){tile = tile_;flag = flag_;};
	void init()
	{
		tile = DG_FLOOR;
		flag = 0;
		silence_count = 0;
		violet_count = 0;
		forbid_count = 0;
		forbid_count2 = 0;
	}
	bool isMove(bool fly_, bool swim_, bool no_ground_)
	{
		return ((!no_ground_ && tile<DG_NONE_MOVE )|| 
			((fly_ || swim_) && tile == DG_SEA) ||
			((fly_) && tile == DG_LAVA));
	
	};
	bool isOpenDoor(){return (tile==DG_OPEN_DOOR);};
	bool isCloseDoor(){return (tile==DG_CLOSE_DOOR);};
	bool isDoor(){return (isCloseDoor() || isOpenDoor());};
	void OpenDoor(){tile=DG_OPEN_DOOR;};
	void CloseDoor(){tile=DG_CLOSE_DOOR;};
	bool isSight(){return (tile<DG_NONE_MOVE || tile >= DG_GLASS);};
	bool isFloor(){return (tile>=DG_FLOOR && tile<=DG_FLOOR_END);};
	bool isBreakable(){return (tile>=DG_WALL && tile<=DG_WALL_END) || (tile >= DG_CLOSE_DOOR && tile <= DG_GLASS);};
	bool isStair(){ return (tile >= DG_DOWN_STAIR && tile <= DG_RETURN_STAIR); };
	bool isTemple(){ return (tile >= DG_TEMPLE_FIRST && tile <= DG_TEMPLE_LAST); };
	bool draw(shared_ptr<DirectX::SpriteBatch> pSprite, float x, float y, D3DCOLOR color, int count_)
	{
		bool temp;
		temp = img_dungeon01[tile].draw(pSprite,x,y,color);
		if(temp && tile>= DG_FLOOR_OBJECT && tile<=DG_OBJECT_END)
		{
			temp = img_dungeon_object[tile-DG_FLOOR_OBJECT][count_%3].draw(pSprite,x,y,color);
		}
		return temp;
	}
	bool draw(shared_ptr<DirectX::SpriteBatch> pSprite, int new_tile, float x, float y, D3DCOLOR color, int count_)
	{
		bool temp;
		temp = img_dungeon01[new_tile].draw(pSprite, x, y, color);
		if (temp && tile >= DG_FLOOR_OBJECT && tile <= DG_OBJECT_END)
		{
			temp = img_dungeon_object[tile - DG_FLOOR_OBJECT][count_ % 3].draw(pSprite, x, y, color);
		}
		return temp;
	}
	bool isNormal()
	{
		return img_dungeon01[tile].isNormal();
	}
	bool isAutoTile(int i)
	{
		switch (i)
		{
		case AUTOTILE_WALL:
			if ((tile >= DG_WALL && tile <= DG_GLASS) || tile == DG_OPEN_DOOR)
				return true;
			break;
		case AUTOTILE_WATER:
			if (tile == DG_SEA || tile == DG_LAVA)
				return true;
			break;
		}
		return false;

	}
	dot_tile_type GetDot();
};


class stair_info
{
public:
	coord_def pos;
	int next_floor;
	stair_info(coord_def pos_, int next_floor_):pos(pos_),next_floor(next_floor_){}
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
};


enum stair_kind 
{
	STAIR_KIND_NOT_STAIR,
	STAIR_KIND_UP_BASE,
	STAIR_KIND_UP_SPECIAL,
	STAIR_KIND_DOWN_BASE,
	STAIR_KIND_DOWN_SPECIAL
};



class environment
{
public:
	int floor;
	bool make;
	int all_monster_id;
	int popular;
	dungeon_tile_type base_floor;
	dungeon_tile_type base_wall;
	dungeon_tile dgtile[DG_MAX_X][DG_MAX_Y];
	coord_def stair_up[3];
	coord_def stair_down[3];
	vector<stair_info> stair_vector; //추가 계단.(나중엔 통합하기)
	vector<monster> mon_vector;
	list<shadow> shadow_list;
	list<item> item_list;
	list<effect> effect_list;
	list<smoke> smoke_list;
	list<floor_effect> floor_list;
	list<events> event_list;
	list<string> speciel_map_name;
	list<forbid> forbid_list;

	
	static bool isFirstFloor(int level_);
	static bool isLastFloor(int level_);

	environment();
	~environment();
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	bool MakeMap(bool return_); //return_ 은 되돌아오는 계단일때 전용(이때는 대나무숲을 만들지 않는다.)
	void EnterMap(int num_, deque<monster*> &dq, coord_def pos_= coord_def(0,0));
	bool isMove(int x_,int y_, bool fly_ = false, bool swim_ = false, bool no_ground_ = false)
	{
		int sight_ = 7;
		if(x_<0 || x_>=DG_MAX_X || y_<0 || y_>=DG_MAX_Y)
			return false;
		if(you.s_dimension)
		{			
			if(abs(x_ - you.god_value[GT_YUKARI][0])>sight_ || abs(y_ - you.god_value[GT_YUKARI][1])>sight_)
				return false; //차원고정의 범위 밖에 있다.
		}

		return dgtile[x_][y_].isMove(fly_, swim_, no_ground_);
	}
	bool isMove(const coord_def &c, bool fly_ = false, bool swim_ = false, bool no_ground_ = false)
	{
		return isMove(c.x,c.y, fly_, swim_, no_ground_);
	}
	bool isInSight(const coord_def &c, bool monster_sight_ = false)
	{
		if(c.x<0 || c.x>=DG_MAX_X || c.y<0 || c.y>=DG_MAX_Y)
			return false;
		if (you.s_night_sight_turn && !monster_sight_ && distan_coord(c,you.position)>2)
			return false;
		return dgtile[c.x][c.y].flag & FLAG_INSIGHT;
	}
	bool isSight(const coord_def &c)
	{
		if(c.x<0 || c.x>=DG_MAX_X || c.y<0 || c.y>=DG_MAX_Y)
			return false;
		if (you.god == GT_OKINA && !you.GetPunish(GT_OKINA)) {
			if (dgtile[c.x][c.y].isCloseDoor()) {
				return true;
			}
		}
		return dgtile[c.x][c.y].isSight();
	}
	bool isExplore(int x_,int y_)
	{
		if(x_<0 || x_>=DG_MAX_X || y_<0 || y_>=DG_MAX_Y)
			return true;
		return dgtile[x_][y_].flag  & FLAG_EXPLORE;
	}
	bool isMapping(int x_, int y_)
	{
		if(x_<0 || x_>=DG_MAX_X || y_<0 || y_>=DG_MAX_Y)
			return true;
		return dgtile[x_][y_].flag  & FLAG_MAPPING;
	}
	bool isDoor(int x_,int y_){
		if(x_<0 || x_>=DG_MAX_X || y_<0 || y_>=DG_MAX_Y)
			return false;
		return dgtile[x_][y_].isDoor();
	}
	bool isMonsterOpen(int x_, int y_) {
		return !(dgtile[x_][y_].flag & FLAG_DONT_DOOR);
	}
	bool isOpenDoor(int x_,int y_){
		if(x_<0 || x_>=DG_MAX_X || y_<0 || y_>=DG_MAX_Y)
			return false;
		return dgtile[x_][y_].isOpenDoor();
	}
	bool isCloseDoor(int x_,int y_){
		if(x_<0 || x_>=DG_MAX_X || y_<0 || y_>=DG_MAX_Y)
			return false;
		return dgtile[x_][y_].isCloseDoor();
	}
	int isStair(int x_, int y_); //실제 계단번지수에 +1을해서 리턴함(※올라가는 계단은 마이너스곱함)

	stair_kind getStairKind(int x_, int y_);
	char getAsciiDot(int x_, int y_);
	string getTileHelp(int x_, int y_);


	bool magicmapping(int x_, int y_);
	bool OpenDoor(int x_,int y_)
	{
		if(dgtile[x_][y_].isCloseDoor())
		{
			dgtile[x_][y_].OpenDoor();
			dgtile[x_][y_].flag &= ~FLAG_DONT_DOOR;
			return true;
		}
		else
			return false;
	}
	int getAutoTileNum(unsigned char bit);
	void calculateAutoTile(coord_def pos, AUTOTILE_KIND kind);
	void allCalculateAutoTile();
	void innerDrawTile(shared_ptr<DirectX::SpriteBatch> pSprite, int tile_x, int tile_y, float x, float y, int count_, D3DCOLOR color_, bool sight);
	void drawTile(shared_ptr<DirectX::SpriteBatch> pSprite, int tile_x, int tile_y, float x, float y, float scale, int count_, bool sight, bool onlyTile, bool draw_mouse);
	bool changeTile(coord_def c, dungeon_tile_type tile, bool noAutoCacul = false);
	int CloseDoor(int x_,int y_); //0은 문없음 1은 닫음 -1은 어딘가 걸려있음
	monster* AddMonster(int id_, int flag_, coord_def position_, int time_ = 0);
	monster* AddMonster(monster *mon_, coord_def position_, int time_ = 0);
	monster* AddMonster_Summon(int id_, int flag_, coord_def position_, summon_info &info_ , int time_);
	void SummonClear(int map_id_);
	void MakeShadow(const coord_def &c, textures *t, int original_id_, shadow_type type_= SWT_MONSTER, const string &name_ = "");
	bool MakeSmoke(const coord_def &c, textures *t, smoke_type type_, int time_, int expand_, unit* parent_ = NULL);
	bool MakeFloorEffect(const coord_def &c, textures *t,textures *t2, floor_type type_, int time_, unit* parent_ = NULL);
	bool MakeEvent(int id_, coord_def position_, event_type type_, int count_ = -1);
	void MakeEffect(const coord_def &c, textures *t, bool over_sight_); //over_sight_ : 시야 밖에서의 이펙트도 볼것인가?
	void ClearEffect();
	void ClearAllShadow();
	void ClearEvent();
	void ClearSmoke();
	void ClearForbid();
	void AllySafeClear(int new_floor_, coord_def pos_); //영구아군(유유코망령, 릴리화이트동료등)이 각종 맵 갈릴때 죽는것을 방지
	void ClearFloor();
	void enterBgm(boolean first_);
	void playBgm();
	monster* movingfloor(const coord_def &c, int prev_floor_, monster* mon_);
	item* MakeItem(const coord_def &c, const item_infor &t, int num_ = 0);
	item* AddItem(const coord_def &c, item *t, int num_ = 0);
	void AddSpecialMapInfo(string string_);
	void DeleteItem(const list<item>::iterator it);
	bool DeleteItem(const item *item_);
	void ClearShadow();
	void ClearShadow(const coord_def &c, shadow_type type_);
	void CheckFloor();
	void ActionMonster(int delay_);
	void ActionMonsterSpecial(int delay_);
	void ActionSmoke(int delay_);
	void ActionFloor(int delay_);
	bool ActionEvent(int delay_);
	bool ActionSmokeEffect();
	bool ActionItem(int delay_);
	bool DisableMove(coord_def pos_, bool view_ = false); //이 위치의 모든 물체는 행동할 수 없다.
	bool MakeSilence(coord_def center_, int length_, bool on_);
	bool MakeViolet(coord_def center_, int length_, bool on_);
	bool MakeSantuary(coord_def center_, int length_, bool on_);
	bool AddForbid(coord_def center_);
	void MakeForbid(coord_def pos, bool center_, bool on_);
	bool MakeForbid(coord_def center_, int length_, bool on_, list<coord_def> &stack_);
	bool CheckForbid(coord_def center_);
	bool ResetForbid();
	bool MakeNoise(coord_def center_, int length_, const unit* excep_);
	bool PostoCheckSight(coord_def center_, coord_def target_, int lengths_, bool s_dimension_=false);
	bool MakeMapping(int percent_);
	bool MakeMapping(coord_def center_, int length_, bool passed_, int percent_);
	bool seeAllMonster();
	bool isSilence(coord_def pos_);
	bool isViolet(coord_def pos_);
	bool isSanctuary(coord_def pos_);
	unit* isMonsterPos(int x_,int y_, const unit* excep_ = NULL, int* map_id_ = NULL);//해당 위치에 이미 몬스터가 있냐 ㅇ벗냐
	shadow* isShadowPos(int x_, int y_);//해당 위치에 그림자있는지 확인
	bool isForbidZone(int x_, int y_);
	bool isBlockPos(int x_, int y_);
	bool isSmokePos(int x_,int y_, bool only_fog = false);//해당 위치에 구름이 있냐 없냐(only_fog는 시야를 가리는 구름만 찾는다.)	
	floor_effect* isFloorEffectPos(int x_,int y_, const floor_effect* excep_ = NULL);
	smoke* isSmokePos2(int x_,int y_, const smoke* excep_ = NULL);//해당 위치에 구름이 있냐 없냐(포인터 리턴)
	monster* getRandomMonster(bool except_melee); //시야내 랜덤 몬스터 리턴
	int insight_mon(monster_enemy_type type_);//시야내 몬스터갯수
	monster* close_mon(int x_,int y_, monster_enemy_type type_);//가장 가까이 있는 몬스터리턴
	void item_view_set();
	int new_item_interupt();//시야에 새로운 아이템있으면 메세지보내고 갯수리턴
	item* close_item(vector<item*> &item_vector_);//가장 가까운 아이템의 정보를 리턴
	unit* GetMapIDtoUnit(int Map_id); //맵아이디로부터 유닛 포인터를 리턴

	list<item>::iterator GetPositiontoitem(coord_def position_);
	list<item>::iterator GetPositiontoitemend(coord_def position_);

	bool isBamboo(){return floor == BAMBOO_LEVEL;};
	int isPandemonium(){return (floor >= PANDEMONIUM_LEVEL && floor <= PANDEMONIUM_LAST_LEVEL)?floor-PANDEMONIUM_LEVEL+1:0;};
};



extern int current_level;
extern environment env[];
bool isTutorial();
bool isNormalGame();
bool isArena();
bool isSprint();
int sprintMulti();

float GetDotX(int x, int dungeon_x, int magnification);
float GetDotY(int offset_, int y, int dungeon_y, int magnification);
string CurrentLevelString(int level = -1);
int GetLevelMonsterNum(int level, bool item_);
void Noise(coord_def center_, int length_, const unit* excep_=NULL);
bool Auto_Pick_Up(list<item>::iterator it);

void SaveFile();
void LoadFile();



class wiz_infor
{
public:
	int wizard_mode;
};

extern wiz_infor wiz_list;

#endif // __ENVIRONMENT_H__