//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: dump.h
//
// 내용: 덤프해여
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __DUMP_H__
#define  __DUMP_H__

#include <stdio.h>
#include <iostream>
#include "enum.h"
#include "unit.h"

enum dump_action_type
{
	DACT_NONE = -1,
	DACT_MELEE,
	DACT_SHOOT,
	DACT_SPELL,
	DACT_INVOKE,
	DACT_EVOKE,
	DACT_USE,
	DACT_MAX
};

using namespace std;

class action_class
{
public:
	dump_action_type type;
	string name;
	int num[27];
	
	action_class();
	action_class(dump_action_type type_, string name_, int level_);
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	void plus(int level_){num[level_-1]++;}
};

string GetDumpActionString(dump_action_type type_);


void GetDeathReason(stringstream& death_reason, damage_reason dead_reason, int att_type, attack_infor* dead_order, int mon_id, int damage, int level, bool orb, int rune, int ziggurat_level);

bool Dump(int type, wstring *filename_);


#endif // __DUMP_H__
