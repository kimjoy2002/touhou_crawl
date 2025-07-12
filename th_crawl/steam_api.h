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
#include <vector>
#include <mutex>
#include <steam/steam_api.h>
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

struct ScoreEntry {
    std::string username;
    int score;
    int level;
    int tribe;
    int job;
    int charname;
    int turn;
    int last_damage;
    int damage_source;
    int damage_reason;
    int rune;
    int hp;
    int max_hp;
    int god;
    int version;
    int timestamp;
    int dungeon_level;
    int att_type;
};


class steam_manager
{
private:
	bool init = false;
    SteamLeaderboard_t m_CurrentLeaderboard = NULL;
    CCallResult<steam_manager, LeaderboardFindResult_t> m_callFindLeaderboard;
	CCallResult<steam_manager, LeaderboardScoresDownloaded_t> m_callDownloadLeaderboard;
    std::mutex score_mutex;
	std::vector<ScoreEntry> m_tempEntries;
	bool m_scoreReceived = false;

	const char* getAchievementId(achievement_enum enum_);

	std::shared_ptr<ScoreEntry> ready_score = nullptr;

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
	
	bool sendScore(const ScoreEntry& entry);
	bool getScoreBoard(std::vector<ScoreEntry>& out_entries);
	void OnFindLeaderboard(LeaderboardFindResult_t* pResult, bool bIOFailure);
	void OnFindLeaderboardForQuery(LeaderboardFindResult_t* pResult, bool bIOFailure);
	void OnDownloadLeaderboard(LeaderboardScoresDownloaded_t* pResult, bool bIOFailure);
	void debugText();
};

extern steam_manager steam_mg;

#endif // __STEAM_API_H__