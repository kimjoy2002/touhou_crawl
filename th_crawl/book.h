//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: book.h
//
// 내용: 책 관련 정보 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BOOK_H__
#define  __BOOK_H__

#include <string>
#include "enum.h"

using namespace std;



struct book_infor
{
	LOCALIZATION_ENUM_KEY key;
	int id;
	int value;
	int spell[8];
	book_infor(LOCALIZATION_ENUM_KEY key, int id_, int value_, int s1,int s2,int s3,int s4,int s5,int s6,int s7,int s8):
	key(key), id(id_), value(value_)
	{
		spell[0] = s1; spell[1] = s2; spell[2] = s3; spell[3] = s4; spell[4] = s5; spell[5] = s6; spell[6] = s7; spell[7] = s8; 
	}
};


const int RANDOM_BOOK_NUM=7;

extern book_infor static_book_list[BOOK_LAST]; 
extern LOCALIZATION_ENUM_KEY random_book_list[RANDOM_BOOK_NUM];


const char* GetBookInfor(book_list book_);
book_list SchoolToBook(skill_type skill_);



#endif // __BOOK_H__