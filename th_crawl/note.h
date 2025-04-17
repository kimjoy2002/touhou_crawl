//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: note.h
//
// 내용: 저장하는 노트
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NOTE_H__
#define  __NOTE_H__

#include <string>
#include <list>
#include "common.h"

using namespace std;

class note_dummy
{
public:
	int turn;
	string place;
	string text;
	D3DCOLOR color;

	note_dummy();
	note_dummy(int turn_, string place_, string text_, D3DCOLOR color_);
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
};


class note_class
{
public:
	list<note_dummy> note_list;
	note_class();
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
};


extern note_class save_note;


void AddNote(int turn, string place, string text, D3DCOLOR color);



#endif // __NOTE_H__