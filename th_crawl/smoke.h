//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: smoke.h
//
// 내용: 연기 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SMOKE_H__
#define  __SMOKE_H__

#include "enum.h"
#include "common.h"
#include "texture.h"
#include "unit.h"



class smoke
{
public:
	coord_def position;
	textures *image;
	smoke_type type;
	int time;
	int expand;
	parent_type parent;
	smoke();
	smoke(const coord_def &c, textures *t, smoke_type type_, int time_, int expand_, parent_type parent_ = PRT_NEUTRAL);
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	bool draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_);
	bool clear(const coord_def move_ = coord_def());
	bool action(int delay_);
	bool offsetmove(const coord_def &c);
	int sight_inter();
	string GetName();
	bool effectSmoke(unit* unit_);
	int danger(unit* unit_, bool first_ = true);
};

bool MakeCloud(const coord_def &c, textures *t, smoke_type type_, int num_, int time_, int expand_, int max_length, unit* parent_ = NULL);
bool MakeCloud(const coord_def &c, random_extraction<textures*> rand_t, smoke_type type_, int num_, int time_, int time_updown_, int expand_, int max_length, unit* parent_ = NULL);

#endif // __SMOKE_H__