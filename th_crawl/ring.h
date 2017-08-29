//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ring.h
//
// 내용: 링과 아뮬렛 관련 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __RING_H__
#define  __RING_H__


#include "player.h"

extern char *ring_uniden_string[RGT_MAX];
extern const char *ring_iden_string[RGT_MAX];


int isRingGotValue(ring_type ring_);
ring_type goodbadring(int good_bad);
int isGoodRing(ring_type kind, int value);
int isPickableRIng(ring_type kind); //2개이상 집어도 되는 링
bool equipring(ring_type kind, int value); //리턴값: 식별시 true 미식별시 false
bool unidenequipring(ring_type kind, int value);



#endif // __RING_H__