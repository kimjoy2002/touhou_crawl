//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_infor.h
//
// 내용: 몬스터의 정보들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_INFOR_H__
#define  __MON_INFOR_H__

#include "unit.h"
#include "texture.h"
#include "monster_texture.h"

struct mon_infor
{
	int id;
	int level;
	int exper;
	name_infor name;
	textures *image;
	int max_hp;
	int ac;
	int ev;
	int atk[3];
	attack_type atk_type[3];
	name_infor atk_name[3];
	int flag;
	int resist;
	int sense;
	int speed;
	char dot;
};


enum monster_flag
{
	M_FLAG_OPEN_DOOR = 1<<0, //문을 열 수 있는가?
	M_FLAG_FAIRY = 1<<1, //요정인가?
	M_FLAG_UNIQUE  = 1<<2, //네임드인가?
	M_FLAG_FLY = 1<<3, //나는가?
	M_FLAG_NO_ATK = 1<<4, //공격을 하지 않는가?
	M_FLAG_CONFUSE = 1<<5, //항상 혼란상태인가?
	M_FLAG_SUMMON = 1<<6, //소환되었나?
	M_FLAG_SPEAK = 1<<7, //말하는가?
	M_FLAG_ALLY = 1<<8, //동맹인가?
	M_FLAG_SWIM = 1<<9, //수영이 가능한가?
	M_FLAG_CAN_SEE_INVI = 1<<10, //투명을 볼 수 있는가?
	M_FLAG_CANT_GROUND = 1<<11, //지상에 못올라오는가?
	M_FLAG_EVENT = 1<<12, //이벤트로 등장.(나오자마자 주인공을 타겟)
	M_FLAG_LEADER_SUMMON = 1<<13, //오로지 소환사 주변을 멤돈다
	M_FLAG_PASSED_ALLY = 1<<14, //아군의 원거리 공격을 흘린다.
	M_FLAG_PASSED_ENEMY = 1<<15, //적군의 원거리 공격을 흘린다.
	M_FLAG_NONE_MOVE = 1<<16, //움직이지 않는다.
	M_FLAG_UNHARM = 1<<17, //무해한가?
	M_FLAG_INVISIBLE = 1<<18, //영구 투명
	M_FLAG_ANIMAL = 1<<19, //동물
	M_FLAG_NETURALY = 1<<20,  //중립. 그러나 원본크롤과는 약간 다르다. 플레이어에겐 적대적이나 몹끼리 싸움
	M_FLAG_NONE_STAIR = 1<<21,
	M_FLAG_CANT_NETURAL = 1<<22, //자연적으로 생성될수 없는. 아레나에서 나올 수 없는 몹
	M_FLAG_INANIMATE = 1<<23, //무생물
	M_FLAG_NO_STATE = 1<<24, //상태 표시 안됨
	M_FLAG_SILENCE = 1 << 25, //침묵에 면역이다.
	M_FLAG_SHIELD = 1 << 26, //지역을 지킨다.
	M_FLAG_RESIST_BLIZARD = 1 << 27
};


enum getMonsterFromFloor_flag
{
	GMFF_FLAG_ALL = 0,
	GMFF_FLAG_ONLY_WEAK,
	GMFF_FLAG_ONLY_STRONG,
	GMFF_FLAG_ONLY_MIDDLE
};

extern const mon_infor mondata[];


bool is_exist_named(monster_index id); //해당 네임드가 출현확정되어있는지
void set_exist_named(monster_index id); //네임드를 출현확정(벌트등으로)
void unset_exist_named(monster_index id);

void create_mon(int floor, int num_);
void init_monster(); 
int getMonsterFromSpecial(int type_, getMonsterFromFloor_flag power_);
int getMonsterFromFloor(int level_, getMonsterFromFloor_flag power_);

struct unique_infor
{
	int id;
	int level;
	unique_infor(int id_=0,int level_=0):id(id_),level(level_){};
};

extern vector<unique_infor> unique_list;
void SetResistMonster(monster* mon);

void GetMonsterInfor(monster *it);

#endif // __MON_INFOR_H__