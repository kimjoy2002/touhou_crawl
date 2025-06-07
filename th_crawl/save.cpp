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
std::string loading_version_string;

const wchar_t* saveslot_wstring[3] = {L"save.sav",L"save2.sav",L"save3.sav"};


std::wstring app_path_w;
std::wstring save_file_w[3];
std::wstring user_name_file_w;
std::wstring replay_path_w;
std::wstring morgue_path_w;


void init_save_paths() {
    wchar_t appDataPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, appDataPath))) {
        std::filesystem::path base(appDataPath);
        base /= L"AppData\\LocalLow\\TouhouCrawl\\TouhouCrawl";
        std::filesystem::create_directories(base); // 폴더가 없으면 생성

		option_mg.init((base / L"config.ini").wstring());

		for(int i = 0; i < 3; i++) {
        	save_file_w[i] = (base / saveslot_wstring[i]).wstring();
		}
        user_name_file_w = (base / L"user_name.txt").wstring();
		replay_path_w = (base / L"replay").wstring();
		morgue_path_w = (base / L"morgue").wstring();
    } else {
		option_mg.init(L"./config.ini");

		for(int i = 0; i < 3; i++) {
        	save_file_w[i] = saveslot_wstring[i];
		}
        user_name_file_w = L"user_name.txt";
		replay_path_w = L"replay";
		morgue_path_w = L"morgue";

    }
}

void delete_file(int slot)
{
	DeleteFileW(save_file_w[slot-1].c_str());
}

void delete_file()
{
	DeleteFileW(save_file_w[option_mg.getSaveSlot()-1].c_str());
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
	if(ynPrompt(LOC_SYSTEM_SAVE_QUIT_YN, LOC_SYSTEM_CANCLE_QUIT, CL_help, false,true,true,false)) {
		enterlog();	
		if(!ReplayClass.ReplayMode()) {
			saveReplay_cpp();
			game_over = true;
		}
	} else {
		return;
	}
}
void nosaveandexit()
{	
	if(ynPrompt(LOC_SYSTEM_NONSAVE_QUIT_YN, LOC_SYSTEM_CANCLE_QUIT, CL_help, false,true,true,false)) {
		enterlog();
		you.dead_reason = DR_QUIT;
		GameOver();
	} else {
		return;
	}
}
bool load_data(const std::wstring& path)
{
    DWORD attr = GetFileAttributesW(path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES)
    {
        return false;
    }
    else
	{
		LoadFile();
		return true;
	}
}

bool load_data_onlyinfo(wstring path, players& temp_player)
{
    DWORD attr = GetFileAttributesW(path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES)
    {
        return false;
    }
	else
	{
		//WaitForSingleObject(mutx, INFINITE);
		FILE *fp;
		std::wstring wfilename = path;
		if (_wfopen_s(&fp, wfilename.c_str(), L"rb") != 0 || !fp) {
			return false;
		}
		int magic_number;
		LoadData<int>(fp, magic_number); //version 1.11부터 매직넘버로 시작한다
		int current_level_temp;
		if(magic_number != 1999) {
			//ver1.1에선 첫 int가 1999임
			current_level_temp = magic_number;
		} else {
			{
				char temp[256];
				LoadData<char>(fp, *temp);
				//loading_version_string = temp;
			}
			LoadData<int>(fp, current_level_temp);
		}
		LoadData<int>(fp, temp_player.level);
		LoadData<tribe_type>(fp, temp_player.tribe);
		LoadData<job_type>(fp, temp_player.job);
		LoadData<unique_starting_type>(fp, temp_player.char_type);
		fclose(fp);
		//ReleaseMutex(mutx);
		return true;
	}
}



bool load_name(const std::wstring& path)
{
    DWORD attr = GetFileAttributesW(path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES)
    {
        return false;
    }
	else
	{	
		FILE *fp;
		char name[31];

		std::wstring wfilename = user_name_file_w;

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
			if(load_data_onlyinfo(save_file_w[i], temp_player)) {
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
		int input_;
		while(1) {
			input_ = waitkeyinput(inputedKey,true);
			if(input_ == VK_UP)
				DisplayManager.addPosition(-1);
			else if(input_ == VK_DOWN)
				DisplayManager.addPosition(1);
			else if(input_ == VK_RETURN || input_ == GVK_BUTTON_A || input_ == GVK_BUTTON_A_LONG) {
				input_ = DisplayManager.positionToChar();
				break;
			} else {
				break;
			}
		}

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
		else if(input_ == 'Y' || input_ == GVK_BUTTON_A_LONG)
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
		else if(input_ == VK_ESCAPE || 
			input_ == GVK_BUTTON_B || 
			input_ == GVK_BUTTON_B_LONG || (input_ == -1 && inputedKey.isRightClick()))
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

