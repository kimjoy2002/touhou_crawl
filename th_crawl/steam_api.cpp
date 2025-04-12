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