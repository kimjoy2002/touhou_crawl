//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: save.cpp
//
// 내용: 세이브 편의용 함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "save.h"
#include "environment.h"
#include "key.h"
#include "replay.h"
#include "option_manager.h"
#include <shlobj.h>
#include <filesystem>

extern bool saveexit;
extern HANDLE mutx;
extern std::atomic<bool> g_saveandexit;

const wchar_t* saveslot_wstring[3] = {L"save.sav",L"save2.sav",L"save3.sav"};
const char* saveslot_string[3] = {"save.sav","save2.sav","save3.sav"};


std::string app_path;
std::string save_file[3];
std::string user_name_file;
std::string replay_path;
std::string morgue_path;


void init_save_paths() {
    wchar_t appDataPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, appDataPath))) {
        std::filesystem::path base(appDataPath);
        base /= L"AppData\\LocalLow\\TouhouCrawl\\TouhouCrawl";
        std::filesystem::create_directories(base); // 폴더가 없으면 생성

		option_mg.init((base / L"config.ini").string());

		for(int i = 0; i < 3; i++) {
        	save_file[i] = (base / saveslot_wstring[i]).string();
		}
        user_name_file = (base / L"user_name.txt").string();
		replay_path = (base / L"replay").string();
		morgue_path = (base / L"morgue").string();
    } else {
		option_mg.init("./config.ini");

		for(int i = 0; i < 3; i++) {
        	save_file[i] = saveslot_string[i];
		}
        user_name_file ="user_name.txt";
		replay_path = "replay";
		morgue_path = "morgue";

    }
}

void delete_file(int slot)
{
	remove(save_file[slot-1].c_str());
}

void delete_file()
{
	remove(save_file[option_mg.getSaveSlot()-1].c_str());
	saveexit = false;

}
void saveReplay_cpp();
void saveandexit()
{
	if(!ReplayClass.ReplayMode()) {
		saveReplay_cpp();
		game_over = true;
	}
}
void saveReplay_cpp();
void saveandcheckexit()
{
	while(1)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SAVE_QUIT_YN),false,false,false,CL_help);
		printlog(" (",false,false,false,CL_help);
		printlog("Y",false,false,false,CL_help, 'Y');
		printlog("/",false,false,false,CL_help);
		printlog("N",false,false,false,CL_help, 'N');
		printlog(") ",false,false,false,CL_help);
		startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
		
		InputedKey inputedKey;
		switch(waitkeyinput(inputedKey))
		{
		case 'Y':
			enterlog();	
			if(!ReplayClass.ReplayMode()) {
				saveReplay_cpp();
				game_over = true;
			}
			endSelection();
			return;
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				break;
			}
		case 'N':
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE_QUIT),true,false,false,CL_help);
			endSelection();
			return;
		default:
			enterlog();
			printlog(LocalzationManager::locString(LOC_SYSTEM_PLEASE_SELECT_YN),true,false,false,CL_help);
			break;
		}
	}

}
void nosaveandexit()
{	
	while(1)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_NONSAVE_QUIT_YN),false,false,false,CL_help);
		printlog(" (",false,false,false,CL_help);
		printlog("Y",false,false,false,CL_help, 'Y');
		printlog("/",false,false,false,CL_help);
		printlog("N",false,false,false,CL_help, 'N');
		printlog(") ",false,false,false,CL_help);
		startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
		InputedKey inputedKey;
		switch(waitkeyinput(inputedKey))
		{
		case 'Y':
			enterlog();
			you.dead_reason = DR_QUIT;
			GameOver();
			endSelection();
			//delete_file();
			//PostQuitMessage(0);
			return;			
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				break;
			}
		case 'N':
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE_QUIT),true,false,false,CL_help);
			endSelection();
			return;
		default:
			enterlog();
			printlog(LocalzationManager::locString(LOC_SYSTEM_PLEASE_SELECT_YN),true,false,false,CL_help);
			break;
		}
	}
}
bool load_data(const char* path)
{
	if(GetFileAttributes(path) == -1)
	{
		return false;
	}
	else
	{
		LoadFile();
		return true;
	}
}

bool load_data_onlyinfo(string path, players& temp_player)
{
	if(GetFileAttributes(path.c_str()) == -1)
	{
		return false;
	}
	else
	{
		//WaitForSingleObject(mutx, INFINITE);
		FILE *fp;
		std::wstring wfilename = ConvertUTF8ToUTF16(path);
		if (_wfopen_s(&fp, wfilename.c_str(), L"rb") != 0 || !fp) {
			return false;
		}
		LoadData<int>(fp, current_level);
		LoadData<int>(fp, temp_player.level);
		LoadData<tribe_type>(fp, temp_player.tribe);
		LoadData<job_type>(fp, temp_player.job);
		LoadData<unique_starting_type>(fp, temp_player.char_type);
		fclose(fp);
		//ReleaseMutex(mutx);
		return true;
	}
}



bool load_name(const char* path)
{
	if(GetFileAttributes(path) == -1)
	{
		return false;
	}
	else
	{	
		FILE *fp;
		char name[31];

		std::wstring wfilename = ConvertUTF8ToUTF16(user_name_file);

		if(_wfopen_s(&fp, wfilename.c_str(), L"rt") != 0 || !fp)
			return false;
		int i=0,ii=0;		
		int pass = 0;
		for(char c = fgetc(fp); c!=EOF && c!='\n' && c!= '\0' && i<20;i++,c = fgetc(fp))
		{
			if(pass || ('0' <= c && c <='9') || ('A' <= c && c <='Z') || ('a' <= c && c <='z') || (c<0))
			{
				if(pass)
					pass = false;
				else if(c<0)
					pass = true;
				name[ii++] = c;
			}
			else
				continue;
		}
		name[ii] = '\0';
		WaitForSingleObject(mutx, INFINITE);
		you.user_name = string(name);
		ReleaseMutex(mutx);
		if(strcmp(name,"Default"))
			return true;
		else
			return false;
	}
}


bool save_menu(int value_)
{
	char blank[32];
	sprintf_s(blank,32,"            ");

	vector<string> char_info;
	char_info.push_back("");
	char_info.push_back("");
	char_info.push_back("");

	for(int i = 0; i < 3; i++) {
		try {
			players temp_player;
			if(load_data_onlyinfo(save_file[i], temp_player)) {
				ostringstream ss;
				if(!(temp_player.tribe >= 0 && temp_player.tribe < TRI_MAX && temp_player.job >= 0 && temp_player.job < JOB_MAX)) {
					ss << LocalzationManager::locString(LOC_SYSTEM_SAVE_MENU_BROKEN);
				}
				else if(!temp_player.GetCharNameString().empty()) {
					ss << ' ' << LocalzationManager::formatString(LOC_SYSTEM_LEVEL_WITH_NUMBER, PlaceHolderHelper(to_string(temp_player.level))) << ' ' << LocalzationManager::locString(tribe_type_string[temp_player.tribe]) << ' ' << LocalzationManager::locString(job_type_string[temp_player.job]) << ' ' << temp_player.GetCharNameString();
				} 
				else {
					ss << ' ' << LocalzationManager::formatString(LOC_SYSTEM_LEVEL_WITH_NUMBER, PlaceHolderHelper(to_string(temp_player.level))) << ' ' << LocalzationManager::locString(tribe_type_string[temp_player.tribe]) << ' ' << LocalzationManager::locString(job_type_string[temp_player.job]);
				}
				char_info[i] = ss.str();
			}
		} catch(...) {
			char_info[i] = LocalzationManager::locString(LOC_SYSTEM_SAVE_MENU_BROKEN);
		}
	}

	int delete_mode = 0;
	int last_pick_delete = 0;

	while(1)
	{
		deletesub();

		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("======",false,CL_help);
		printsub(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_SAVE),false,CL_help);
		printsub("======",true,CL_help);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("a - " + LocalzationManager::formatString(LOC_SYSTEM_SAVE_MENU_SLOT, PlaceHolderHelper(to_string(1))),false,(delete_mode==2&&last_pick_delete==1)?CL_danger:char_info[0].empty()?CL_bad:CL_normal,'a');
		
		if(!char_info[0].empty()) {
			printsub(char_info[0],false,(delete_mode==2&&last_pick_delete==1)?CL_danger:CL_warning);
		}if(option_mg.getSaveSlot() == 1) {
			printsub(" (" + LocalzationManager::formatString(LOC_SYSTEM_SAVE_MENU_USED) + ")",false,CL_help);
		}
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("b - " + LocalzationManager::formatString(LOC_SYSTEM_SAVE_MENU_SLOT, PlaceHolderHelper(to_string(2))),false,(delete_mode==2&&last_pick_delete==2)?CL_danger:char_info[1].empty()?CL_bad:CL_normal,'b');
		
		if(!char_info[1].empty()) {
			printsub(char_info[1],false,(delete_mode==2&&last_pick_delete==2)?CL_danger:CL_warning);
		}if(option_mg.getSaveSlot() == 2) {
			printsub(" (" + LocalzationManager::formatString(LOC_SYSTEM_SAVE_MENU_USED) + ") ",false,CL_help);
		}
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("c - " + LocalzationManager::formatString(LOC_SYSTEM_SAVE_MENU_SLOT, PlaceHolderHelper(to_string(3))),false,(delete_mode==2&&last_pick_delete==3)?CL_danger:char_info[2].empty()?CL_bad:CL_normal,'b');
		
		if(!char_info[2].empty()) {
			printsub(char_info[2],false,(delete_mode==2&&last_pick_delete==3)?CL_danger:CL_warning);
		}if(option_mg.getSaveSlot() == 3) {
			printsub(" (" + LocalzationManager::formatString(LOC_SYSTEM_SAVE_MENU_USED) + ") ",false,CL_help);
		}
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		if(delete_mode == 2) {
			printsub(LocalzationManager::formatString(LOC_SYSTEM_SAVE_MENU_DELETE_REALLY),false,CL_danger);
		    printsub(" (",false,CL_normal);
		    printsub("Y",false,CL_normal, 'Y');
		    printsub("/",false,CL_normal);
		    printsub("N",false,CL_normal, 'N');
		    printsub(")",false,CL_normal);
		}
		else if(delete_mode == 1) {
			printsub(LocalzationManager::formatString(LOC_SYSTEM_SAVE_MENU_DELETE_SELECT),false,CL_warning);
		} else {
			printsub("x - " + LocalzationManager::formatString(LOC_SYSTEM_SAVE_MENU_DELETE),false,CL_normal,'x');
		}
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("esc - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_BACK),true,CL_normal,VK_ESCAPE);
		
		changedisplay(DT_SUB_TEXT);
		InputedKey inputedKey;
		int input_ = waitkeyinput(inputedKey,true);

		if(input_ >= 'a' && input_ <= 'c')
		{
			if(delete_mode == 0) {
				option_mg.setSaveSlot(input_-'a' + 1);
				continue;
			} else if(delete_mode == 1) {
				if(!char_info[input_-'a'].empty()) {
					last_pick_delete = input_-'a'+ 1;
					delete_mode = 2;
				}
				continue;
			} else if(delete_mode == 2) {
				delete_mode = 1;
				continue;
			}
		}
		else if(input_ == 'x')
		{
			if(delete_mode == 0) {
				delete_mode = 1;
				continue;
			}
		}
		else if(input_ == 'Y')
		{
			if(delete_mode == 2 && (last_pick_delete>=1 && last_pick_delete <=3)) {
				delete_file(last_pick_delete);
				char_info[last_pick_delete-1] = "";
				last_pick_delete = 0;
				delete_mode = 0;
				continue;
			}
		}
		else if((input_ >= 'a' && input_ <= 'z') || (input_ >= 'A' && input_ <= 'Z') )
		{
			if(delete_mode == 2) {
				delete_mode = 1;
				continue;
			}
		}
		else if(input_ == VK_ESCAPE || (input_ == -1 && inputedKey.isRightClick()))
		{
			if(delete_mode == 2) {
				delete_mode = 1;
				continue;
			}
			else if(delete_mode == 1) {
				last_pick_delete = 0;
				delete_mode = 0;
				continue;
			}
			break;
		}
		else if(input_ == -1) {
		}

	}
	changedisplay(DT_SUB_TEXT);

	return false;
}

