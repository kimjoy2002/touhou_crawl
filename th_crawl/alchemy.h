//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: alchemy.h
//
// 내용: 연금술 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ALCHEMY_H__
#define  __ALCHEMY_H__

#include "common.h"


enum ALCHEMY_LIST
{
	ALCT_NONE,
	ALCT_STONE_FIST,
	ALCT_DIAMOND_HARDNESS,
	ALCT_POISON_BODY,
	ALCT_HASTE,
	ALCT_STONE_FORM,
	ALCT_AUTUMN_BLADE,
	ALCT_PHILOSOPHERS_STONE,
	ALCT_MAX

};

int Getalchemytime(ALCHEMY_LIST list_);
void alchemyalmostoff(ALCHEMY_LIST list_);

void alchemyonoff(ALCHEMY_LIST list_,bool onoff_);

#endif // __ALCHEMY_H__



