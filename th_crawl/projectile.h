//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: projectile.h
//
// 내용: 발사처리(발사물 경로 선택과정)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __PROJECTILE_H__
#define  __PROJECTILE_H__

#include "item.h"
#include "monster.h"
#include "beam.h"


struct projectile_infor
{
	int length;
	bool isitem;
	bool smite;
	int spell;
	bool skill; //스킬일때(true면 스킬, false면 마법)
	projectile_infor(int length_,bool isitem_,bool smite_, int spell_ = -1, bool skill_=false):length(length_),isitem(isitem_),smite(smite_),spell(spell_),skill(skill_){};
};


int Common_Throw(list<item>::iterator& it, vector<monster>::iterator it2, beam_iterator& beam, projectile_infor* infor_, int m_len_= -1, float sector_ = 0);
bool Direc_Throw(coord_def* c);

#endif // __PROJECTILE_H__