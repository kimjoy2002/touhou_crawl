//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: steam_api.cpp
//
// 내용: 노트 저장등
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "steam_api.h"
#include "option_manager.h"
#include "localization.h"
#include "environment.h"
#include "const.h"
#include "player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iosfwd>

steam_manager steam_mg;


bool steam_manager::steamInit() {
	if(0)
		return false;
	bool result_ = SteamAPI_Init();
	if(result_ == true) {
		init = true;
	}

	return result_;
}

string steam_manager::getSteamUserName() {
	if(!init)
		return option_mg.getName();
	string name = SteamFriends()->GetPersonaName();
	return name;
}

void steam_manager::setCurrentInfo() {
	setCurrentInfo(LocalzationManager::locString(you.getTribeString()), LocalzationManager::locString(job_type_string[you.job]), you.GetCharNameString(), you.level, CurrentLevelString());

}
void steam_manager::setCurrentMainMenuInfo() {
	setCurrentInfo("","","",0,"");
}
void steam_manager::setCurrentInfo(string tribe, string job, string charname, int level, string which) {
	if(!init)
		return;

	std::ostringstream charInfo;
	if(tribe.empty() && job.empty()) {
		SteamFriends()->SetRichPresence("steam_display", "#MainMenu");
		return;
	}
	else if(!charname.empty())
		charInfo << charname;
	else
	charInfo << tribe << " " << job;
		

	bool current_ = SteamFriends()->SetRichPresence("steam_display", "#Playing");
	current_ = SteamFriends()->SetRichPresence("charinfo", charInfo.str().c_str());
	current_ = SteamFriends()->SetRichPresence("level", to_string(level).c_str());
	current_ = SteamFriends()->SetRichPresence("floor", which.c_str());
}

const char* steam_manager::getAchievementId(achievement_enum enum_) {
    switch (enum_) {
        case ACHIEVEMENT_DUNGEON_OF_FAITH:
            return "ACHIEVEMENT_DUNGEON_OF_FAITH";
	    case ACHIEVEMENT_PERFECT_INK_BLACK_DUNGEON:
            return "ACHIEVEMENT_PERFECT_INK_BLACK_DUNGEON";
	    case ACHIEVEMENT_DUNGEON_HARVESTER:
            return "ACHIEVEMENT_DUNGEON_HARVESTER";
	    case ACHIEVEMENT_PURELY_DUNGEON_HELL:
            return "ACHIEVEMENT_PURELY_DUNGEON_HELL";
	    case ACHIEVEMENT_NIGHTMARE_OF_DUNGEON:
            return "ACHIEVEMENT_NIGHTMARE_OF_DUNGEON";
	    case ACHIEVEMENT_DUNGEON_JUDGEMENT:
            return "ACHIEVEMENT_DUNGEON_JUDGEMENT";
	    case ACHIEVEMENT_DUNGEONS_GAME_OF_LIFE:
            return "ACHIEVEMENT_DUNGEONS_GAME_OF_LIFE";
	    case ACHIEVEMENT_BOUNDARY_OF_SHOOTING_AND_ROGUELIKE:
            return "ACHIEVEMENT_BOUNDARY_OF_SHOOTING_AND_ROGUELIKE";
	    case ACHIEVEMENT_DOOR_TO_THE_HIDDEN_DUNGEON:
            return "ACHIEVEMENT_DOOR_TO_THE_HIDDEN_DUNGEON";
	    case ACHIEVEMENT_MOON_FALLING:
            return "ACHIEVEMENT_MOON_FALLING";
	    case ACHIEVEMENT_DUNGEON_REINCARNATION:
            return "ACHIEVEMENT_DUNGEON_REINCARNATION";
	    case ACHIEVEMENT_ASDD:
            return "ACHIEVEMENT_ASDD";
	    case ACHIEVEMENT_END_OF_THE_DUNGEON:
            return "ACHIEVEMENT_END_OF_THE_DUNGEON";
        default:
            return "";
    }
}

std::string mapSteamLangToIso3(const std::string& steamLang) {
    static const std::unordered_map<std::string, std::string> langMap = {
        {"english", "ENG"},
        {"koreana", "KOR"},
        {"japanese", "JPN"},
        {"schinese", "ZHS"},
        {"tchinese", "ZHT"},
        {"german", "DEU"},
        {"french", "FRA"},
        {"spanish", "SPA"},
        {"russian", "RUS"},
        {"portuguese", "POR"},
        {"brazilian", "POR"},
        {"polish", "POL"},
        {"thai", "THA"},
        {"vietnamese", "VIE"},
        {"italian", "TIE"},
        {"turkish", "TUR"}
    };

    auto it = langMap.find(steamLang);
    if(it != langMap.end()) {
		return it->second;
	}
	else if (steamLang.length() >= 3){
		std::string result = steamLang.substr(0, 3); 
		std::transform(result.begin(), result.end(), result.begin(), ::toupper);
		return result;
	} else {
		return "ENG";
	}
}


string steam_manager::getSteamLang() {
	if(!init)
		return "ENG";

    const char* lang = SteamApps()->GetCurrentGameLanguage();
	if(lang != nullptr) {
		return mapSteamLangToIso3(lang);
	}
	return "ENG";
}



GamepadType steam_manager::getCurrentGamepadType() {
	if(!init || !SteamInput())
        return GAMEPAD_XBOX;

    InputHandle_t handles[STEAM_INPUT_MAX_COUNT];
    int count = SteamInput()->GetConnectedControllers(handles);
    if (count == 0) return GAMEPAD_UNKNOWN;

    ESteamInputType type = SteamInput()->GetInputTypeForHandle(handles[0]);
    switch (type) {
    case k_ESteamInputType_XBox360Controller:
    case k_ESteamInputType_XBoxOneController:
        return GAMEPAD_XBOX;
    case k_ESteamInputType_PS4Controller:
    case k_ESteamInputType_PS5Controller:
        return GAMEPAD_PS;
    case k_ESteamInputType_SwitchJoyConPair:
    case k_ESteamInputType_SwitchJoyConSingle:
    case k_ESteamInputType_SwitchProController:
        return GAMEPAD_NINTENDO;
    default:
        return GAMEPAD_UNKNOWN;
    }
}


void steam_manager::achievement(achievement_enum achievement) {
	if(!init)
		return;
	if(wiz_list.wizard_mode == 1 || wiz_list.wizard_mode == 2)
		return;


	const char* id = getAchievementId(achievement);
	if (id == nullptr || strlen(id) == 0)
		return;

	bool success = SteamUserStats()->SetAchievement(id);
	if (success) {
		SteamUserStats()->StoreStats(); // 실제 저장
	}
}

bool steam_manager::IncrementStat(const char* statName, int32 delta) {
    int32 current = 0;
    if (!SteamUserStats()->GetStat(statName, &current))
        return false;

    current += delta;
    return SteamUserStats()->SetStat(statName, current);
}

void steam_manager::addStats(bool win, unique_starting_type char_type, tribe_type tribe, job_type job)
{
    if (!SteamUserStats()) return;

    // 시작 캐릭터가 없는 일반 플레이
    if (char_type == UNIQ_START_NONE)
    {
        std::string tribe_play = "Stat_Play_Tribe_" + std::string(GetTribeStatString(tribe));
        std::string job_play   = "Stat_Play_Job_"   + std::string(GetJobStatString(job));

        IncrementStat(tribe_play.c_str(), 1);
        IncrementStat(job_play.c_str(), 1);

        if (win) {
            std::string tribe_win = "Stat_Win_Tribe_" + std::string(GetTribeStatString(tribe));
            std::string job_win   = "Stat_Win_Job_"   + std::string(GetJobStatString(job));

            IncrementStat(tribe_win.c_str(), 1);
            IncrementStat(job_win.c_str(), 1);
        }
    }
    // 시작 캐릭터가 지정된 특수 플레이
    else
    {
        std::string start_play = "Stat_Play_Start_" + std::string(GetUniqueStartStatString(char_type));
        IncrementStat(start_play.c_str(), 1);

        if (win) {
            std::string start_win = "Stat_Win_Start_" + std::string(GetUniqueStartStatString(char_type));
            IncrementStat(start_win.c_str(), 1);
        }
    }

    SteamUserStats()->StoreStats(); // 실제 저장 반영
}


void steam_manager::debugText() {
	if(!init) {
		printlog("스팀에 연결되어있지않습니다.",true,false,false,CL_help);
		return;
	}
    printlog("=== 현재 스팀 정보 ===", true, false, false, CL_help);

    const char* name = SteamFriends()->GetPersonaName();
    printlog("유저 이름: " + std::string(name), false, false, false, CL_help);

    uint32 appID = SteamUtils()->GetAppID();
    printlog(" 앱 ID: " + std::to_string(appID), false, false, false, CL_help);

    // 언어 설정
    const char* lang = SteamApps()->GetCurrentGameLanguage();
    printlog(" 게임 언어: " + std::string(lang), false, false, false, CL_help);

    // 언어 설정
    const char* langs = SteamApps()->GetAvailableGameLanguages();
    printlog(" 가능한 게임 언어: " + std::string(langs), false, false, false, CL_help);

	enterlog();

    printlog("달성된 도전과제 목록:", true, false, false, CL_help);
    int count = 0;

    for (int i = 0; i < static_cast<int>(ACHIEVEMENT_MAX); ++i) {
        achievement_enum ach = static_cast<achievement_enum>(i);
        const char* id = getAchievementId(ach);
        bool achieved = false;

        if (SteamUserStats()->GetAchievement(id, &achieved) && achieved) {
            printlog("- " + std::string(id), true, false, false, CL_help);
            count++;
        }
    }

    if (count == 0) {
        printlog("달성된 도전과제가 없습니다.", true, false, false, CL_help);
    }
}

bool steam_manager::sendScore(const ScoreEntry& entry)
{
    if (!init) return false;
    std::lock_guard<std::mutex> lock(score_mutex);
    
    if (m_CurrentLeaderboard == 0)
    {
        SteamAPICall_t hAPICall = SteamUserStats()->FindOrCreateLeaderboard(
            "touhoucrawl_scoreboard",
            k_ELeaderboardSortMethodDescending,
            k_ELeaderboardDisplayTypeNumeric
        );
        ready_score = std::make_shared<ScoreEntry>(entry);
        m_callFindLeaderboard.Set(hAPICall, this, &steam_manager::OnFindLeaderboard);
        return false;
    }


    int timestamp = static_cast<int>(std::time(nullptr));
    // 리더보드 핸들 얻
    int details[16] = {
        entry.level,         // 0
        entry.tribe,         // 1
        entry.job,           // 2
        entry.charname,      // 3
        entry.turn,          // 4
        entry.last_damage,   // 5
        entry.damage_source, // 6
        entry.damage_reason, // 7
        entry.rune,          // 8
        entry.hp,            // 9
        entry.max_hp,        // 10
        entry.god,           // 11
        entry.version,       // 12
        timestamp,           // 13
        entry.dungeon_level, // 14
        entry.att_type       // 15 
    };

    // 스코어 업로드 (score + details)
    SteamUserStats()->UploadLeaderboardScore(
        m_CurrentLeaderboard,
        k_ELeaderboardUploadScoreMethodKeepBest,
        entry.score,
        details,
        16
    );
    return true;
}

void steam_manager::OnFindLeaderboard(LeaderboardFindResult_t* pResult, bool bIOFailure)
{
    if (bIOFailure || !pResult->m_bLeaderboardFound) {
        return;
    }

    m_CurrentLeaderboard = pResult->m_hSteamLeaderboard;

    if(ready_score) {
        ScoreEntry retry = *ready_score;
        ready_score = nullptr;
        sendScore(retry);
    }
}

bool steam_manager::getScoreBoard(std::vector<ScoreEntry>& out_entries)
{
    if (!init) return false;



    // 1. 리더보드 핸들이 없다면 요청
    if (m_CurrentLeaderboard == 0)
    {
        SteamAPICall_t hAPICall = SteamUserStats()->FindOrCreateLeaderboard(
            "touhoucrawl_scoreboard",
            k_ELeaderboardSortMethodDescending,
            k_ELeaderboardDisplayTypeNumeric
        );

        m_scoreReceived = false;
        m_callFindLeaderboard.Set(hAPICall, this, &steam_manager::OnFindLeaderboardForQuery);

        int count = 60 * 10; // 10초 대기
        while (count-- > 0)
        {
            SteamAPI_RunCallbacks();
            Sleep(16);
            std::lock_guard<std::mutex> lock(score_mutex);
            if (m_scoreReceived && m_CurrentLeaderboard != 0) break;
        }

        if (m_CurrentLeaderboard == 0)
        {
            return false;
        }
    }

    {
        std::lock_guard<std::mutex> lock(score_mutex);
        m_tempEntries.clear();
        m_scoreReceived = false;
    }

    SteamAPICall_t hAPICall = SteamUserStats()->DownloadLeaderboardEntries(
        m_CurrentLeaderboard,
        k_ELeaderboardDataRequestGlobal,
        1, 10
    );

    m_callDownloadLeaderboard.Set(hAPICall, this, &steam_manager::OnDownloadLeaderboard);

    int count = 60 * 10; // 10초 대기 (16ms * 600회)
    while (count-- > 0) {
        SteamAPI_RunCallbacks();
        Sleep(16);

        std::lock_guard<std::mutex> lock(score_mutex);
        if (m_scoreReceived) {
            out_entries = m_tempEntries;
            return true;
        }
    }

    return false; // timeout
}

void steam_manager::OnFindLeaderboardForQuery(LeaderboardFindResult_t* pResult, bool bIOFailure) {
    if (!bIOFailure && pResult->m_bLeaderboardFound)
    {
        m_CurrentLeaderboard = pResult->m_hSteamLeaderboard;
    }
    m_scoreReceived = true;  // 결과 도착
}

void steam_manager::OnDownloadLeaderboard(LeaderboardScoresDownloaded_t* pResult, bool bIOFailure) {
    if (bIOFailure || !pResult || pResult->m_cEntryCount <= 0) {
        m_scoreReceived = true;
        return;
    }

    m_tempEntries.clear();
    for (int i = 0; i < pResult->m_cEntryCount; ++i)
    {
        LeaderboardEntry_t entry;
        int details[16] = {};
        if (SteamUserStats()->GetDownloadedLeaderboardEntry(
            pResult->m_hSteamLeaderboardEntries, i, &entry, details, 16))
        {
            ScoreEntry score;
            score.username = SteamFriends()->GetFriendPersonaName(entry.m_steamIDUser);
            score.score = entry.m_nScore;
            score.level = details[0];
            score.tribe = details[1];
            score.job = details[2];
            score.charname = details[3];
            score.turn = details[4];
            score.last_damage = details[5];
            score.damage_source = details[6];
            score.damage_reason = details[7];
            score.rune = details[8];
            score.hp = details[9];
            score.max_hp = details[10];
            score.god = details[11];
            score.version = details[12];
            score.timestamp = details[13];
            score.dungeon_level= details[14];
            score.att_type = details[15];

            m_tempEntries.push_back(score);
        }
    }

    m_scoreReceived = true;
}