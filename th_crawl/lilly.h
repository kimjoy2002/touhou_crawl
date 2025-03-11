//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: lilly.h
//
// 내용: 릴리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __LILLY_H__
#define  __LILLY_H__

#include <string>

using namespace std;


class name_infor;
class monster;
extern name_infor fairy_name[];



enum FAIRY_PERSONAL
{
	FP_NORMALS,
	FP_SHY,
	FP_BRAVE,
	FP_COLD,
	FP_ANNOY,
	FP_MAX
};

enum FAIRY_SPEAK
{
	FS_NORMAL,
	FS_ENTER,
	FS_FAIRY_WAR,
	FS_REVIVE
};

int getMaxFairyName();
const char* fairy_speak(monster* monster_info, int personal, FAIRY_SPEAK type);
void GetFairyExp(int exp);




#endif // __LILLY_H__