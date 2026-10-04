//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bullet.h
//
// 내용: 스펠카드용 탄막 공통 처리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SPELLCARD_BULLET_H__
#define __SPELLCARD_BULLET_H__

#include "../common.h"
#include "../enum.h"
#include <list>

class monster;
class textures;

monster* CreateBullet(const coord_def& start_, textures* image_, const std::list<coord_def>& route_,
	int damage_, int hit_, attack_type attack_type_, int speed_ = 10, int life_ = -1, int parent_map_id_ = -1);
monster* CreateBulletToTarget(const coord_def& start_, const coord_def& goal_, textures* image_,
	int damage_, int hit_, attack_type attack_type_, int speed_ = 10, int life_ = -1, int parent_map_id_ = -1);
monster* CreateStraightBullet(const coord_def& start_, int direction_, int distance_, textures* image_,
	int damage_, int hit_, attack_type attack_type_, int speed_ = 10, int life_ = -1, int parent_map_id_ = -1);
bool MoveBullet(monster* mon_);

#endif // __SPELLCARD_BULLET_H__
