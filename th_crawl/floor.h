//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: floor.h
//
// 내용: 바닥 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __FLOOR_H__
#define  __FLOOR_H__

#include "enum.h"
#include "common.h"
#include "unit.h"

enum floor_type //아래 있는 것이 우선순위가 높다.
{
	FLOORT_NORMAL = 0,
	FLOORT_AUTUMN,
	FLOORT_STONE,
	FLOORT_SCHEMA,
	FLOORT_MAX
};

class textures;
class unit;

class floor_effect
{
public:
	coord_def position;
	textures *image;
	textures *image2;
	int time;	
	floor_type type;
	parent_type parent;
	
	floor_effect();
	floor_effect(const coord_def &c, textures *t, textures *t2, floor_type type_, int time_, parent_type parent_ = PRT_NEUTRAL);
	
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	bool draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_);
	void prev_check();
	bool action(int delay_);
	void onWalk(unit* unit_);
	int danger(unit* unit_, bool first_ = true);

	bool Update(textures *t, textures *t2, floor_type type_, int time_, parent_type parent_ = PRT_NEUTRAL);

	static bool isFly(floor_type type_); //하늘상 배치(물,용암위 가능)
	static bool isSwim(floor_type type_); //물위 배치가능(물위 가능)
	static bool isNoGround(floor_type type_); //지상 배치불가?

	char* GetName();
};



#endif // __FLOOR_H__