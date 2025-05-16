//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: throw.h
//
// 내용: 탄막던지기 관련 함수 & 탄막 그래픽 처리 등등
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __THROW_H__
#define  __THROW_H__

#include "beam.h"
#include "item.h"
#include <functional>

struct projectile_infor;
enum weapon_brand;

class sector_check
{
public:
	coord_def pos;
	int length;
	sector_check(coord_def pos_,int length_):pos(pos_), length(length_){}
};


int Search_Move(const coord_def &c, bool wide, view_type type_ = VT_NORMAL, int value_ = 0);

int GetTanmacGraphicType(tanmac_type type);
textures* GetTanmacBaseGraphic(int type);
textures* GetBorderGraphic(coord_def center, coord_def target, int size_x, int size_y, int count);
LOCALIZATION_ENUM_KEY GetTanmacKey(int type);
attack_type GetTanmacAttackType(tanmac_type type);
attack_type GetWeapontoTanmac(weapon_brand brand);
bool TanmacDeleteRand(tanmac_type type, bool isCanDelete_);
void MakeTanmac(item_infor* t, int select_);




list<item>::iterator ThrowSelect();
bool CheckThrowPath(coord_def start,coord_def target, beam_iterator &beam, bool passdoor = false);
void paintpath(coord_def c_,beam_iterator &beam, list<item>::iterator item_, bool set, projectile_infor* infor_, int m_len, float sector_);

coord_def throwtanmac(textures* t_, beam_iterator& beam, const beam_infor &infor_, item* item_, bool effect_delete = true, bool mimic_ = false);
coord_def throwtanmac(int graphic_type,beam_iterator& beam, const beam_infor &infor_, item* item_, bool effect_delete = true, bool mimic_ = false);
bool ThrowShock(int graphic_type, const coord_def &start, const coord_def &target, const beam_infor &infor_);
bool ThrowSector(int graphic_type,beam_iterator& beam, const beam_infor &infor_, float sector_ , function<void(coord_def)> func_, bool reverse_, bool effect_delete = true);

void Quick_Throw(list<item>::iterator it, vector<monster>::iterator it2, bool auto_);
void Select_Throw();

#endif // __THROW_H__