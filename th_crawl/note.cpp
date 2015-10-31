//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: note.cpp
//
// 내용: 노트 저장등
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "note.h"
#include "save.h"

note_class save_note;


note_dummy::note_dummy()
:turn(0), place(""), text(""), color(0)
{
}

note_dummy::note_dummy(int turn_, string place_, string text_, D3DCOLOR color_)
:turn(turn_), place(place_), text(text_), color(color_)
{
}


void note_dummy::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, turn);
	char temp[200];
	sprintf(temp,"%s",place.c_str());
	SaveData<char>(fp,*temp, strlen(temp)+1);
	sprintf(temp,"%s",text.c_str());
	SaveData<char>(fp,*temp, strlen(temp)+1);
	SaveData<D3DCOLOR>(fp, color);
}
void note_dummy::LoadDatas(FILE *fp)
{
	LoadData<int>(fp, turn);
	char temp[200];
	LoadData<char>(fp, *temp);
	place = temp;
	LoadData<char>(fp, *temp);
	text = temp;
	LoadData<D3DCOLOR>(fp, color);
}





note_class::note_class()
{

}

void note_class::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, note_list.size());
	for(list<note_dummy>::iterator it=note_list.begin();it!=note_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
}
void note_class::LoadDatas(FILE *fp)
{
	int size_=0;
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		note_dummy temp;
		temp.LoadDatas(fp);
		note_list.push_back(temp);
	}
}




void AddNote(int turn, string place, string text, D3DCOLOR color)
{
	save_note.note_list.push_back(note_dummy(turn,place,text,color));
}