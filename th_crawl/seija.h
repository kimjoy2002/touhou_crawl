//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: seija.h
//
// 내용: 세이자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SEIJA_H__
#define  __SEIJA_H__

#include <iostream>

enum god_type;
using namespace std;

bool seija_gift();

void seija_real_gift(int next_);
string seija_talk(god_type god_, int piety);

string seija_god_string(int god, int num);
string seija_summon_buff();


#endif // __SEIJA_H__