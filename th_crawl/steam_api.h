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
#include "joypad.h"

using namespace std;

enum achievement_enum {
	ACHIEVEMENT_DUNGEON_OF_FAITH,
	ACHIEVEMENT_PERFECT_INK_BLACK_DUNGEON,
	ACHIEVEMENT_DUNGEON_HARVESTER,
	ACHIEVEMENT_PURELY_DUNGEON_HELL,
	ACHIEVEMENT_NIGHTMARE_OF_DUNGEON,
	ACHIEVEMENT_DUNGEON_JUDGEMENT,
	ACHIEVEMENT_DUNGEONS_GAME_OF_LIFE,
	ACHIEVEMENT_BOUNDARY_OF_SHOOTING_AND_ROGUELIKE,
	ACHIEVEMENT_MAX
};


class steam_manager
{
private:
	bool init = false;

	const char* getAchievementId(achievement_enum enum_);

public:
	bool steamInit();
	bool isInit(){return init;};
	string getSteamUserName();
	void setCurrentInfo();
	void setCurrentMainMenuInfo();
	void setCurrentInfo(string tribe, string job, string charname, int level, string which);
	string getSteamLang();
	GamepadType getCurrentGamepadType();
	void achievement(achievement_enum achievement);
	
	void debugText();
};

extern steam_manager steam_mg;

#endif // __STEAM_API_H__