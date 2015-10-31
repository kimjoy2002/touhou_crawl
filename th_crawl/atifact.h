//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: atifact.h
//
// 내용: 아티펙트 구현
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ATIFACT_H__
#define  __ATIFACT_H__

#include "enum.h"
#include <stdio.h>

class item;


class atifact_infor
{
public:
	int kind;
	int value;

	atifact_infor(int kind_, int value_);
	atifact_infor();
	~atifact_infor();
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
};


const char* GetAtifactString(ring_type ring_, int value_);
const char* GetAtifactInfor(ring_type ring_, int value_);
bool effectartifact(ring_type kind, int value);
void MakeArtifact(item* item_, int good_bad_);

#endif // __ATIFACT_H__