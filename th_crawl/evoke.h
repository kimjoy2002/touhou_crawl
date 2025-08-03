//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: evoke.h
//
// 내용: 발동템들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EVOKE_H__
#define  __EVOKE_H__

#include "enumMapBuilder.h"

enum evoke_kind
{
	EVK_PAGODA,
	EVK_AIR_SCROLL,
	EVK_DREAM_SOUL,
	EVK_BOMB,
	EVK_GHOST_BALL,
	EVK_SKY_TORPEDO,
	EVK_MAGIC_HAMMER,
	EVK_CAMERA,
	EVK_SPEAR,
	EVK_MAX
};

struct item_infor;
class item;

bool isCanGenerate(evoke_kind evk);
bool isFakeEvoke(evoke_kind evk);

bool evoke_evokable(item* item_, bool auto_, int auto_direc_, evoke_kind kind);
int Evokeusepower(evoke_kind skill, bool max_);

void MakeEvokeItem(item_infor* t, int kind_ = -1);
#endif // __EVENT_H__