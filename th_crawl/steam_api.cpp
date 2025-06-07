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
#include <steam/steam_api.h>

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
	setCurrentInfo(LocalzationManager::locString(tribe_type_string[you.tribe]), LocalzationManager::locString(job_type_string[you.job]), you.GetCharNameString(), you.level, CurrentLevelString());

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