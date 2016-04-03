//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: event.h
//
// 내용: 이벤트 클래스 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EVENT_H__
#define  __EVENT_H__

#include "common.h"
#include "enum.h"

enum event_list
{
	EVL_KISME=100,
	EVL_SIGHT_P, //시야에 들어와야 생기는 P
	EVL_FLOOR, //땅이 된다
	EVL_BAMBOO, //미궁의죽림
	EVL_LUNATICTIME, //루나틱 타임!
	EVL_KOGASA, //키스메를 따라하는 코가사
	EVL_NOISE//소음
};

class events
{
public:
	int id;
	coord_def position;
	event_type type;
	int count;
	bool prev_sight;

	events();
	events(int id_, coord_def position_, event_type type_, int count_ = -1);
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	int action(int delay_);
};
#endif // __EVENT_H__