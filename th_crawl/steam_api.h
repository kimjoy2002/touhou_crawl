//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: steam_api.h
//
// 내용: STEAM관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __STEAM_API_H__
#define  __STEAM_API_H__

#include <string>
#include <list>

using namespace std;

class steam_manager
{
	bool init = false;
public:
	bool steamInit();
	string getSteamUserName();
	void setCurrentInfo();
	void setCurrentMainMenuInfo();
	void setCurrentInfo(string tribe, string job, string charname, int level, string which);
};

extern steam_manager steam_mg;

#endif // __STEAM_API_H__