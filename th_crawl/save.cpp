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

std::string save_file;
std::string user_name_file;
std::string replay_path;
std::string morgue_path;


void init_save_paths() {
    wchar_t appDataPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, appDataPath))) {
        std::filesystem::path base(appDataPath);
        base /= L"AppData\\LocalLow\\TouhouCrawl\\TouhouCrawl";
        std::filesystem::create_directories(base); // 폴더가 없으면 생성

        save_file = (base / L"save.sav").string();
        user_name_file = (base / L"user_name.txt").string();
		replay_path = (base / L"replay").string();
		morgue_path = (base / L"morgue").string();

		option_mg.init((base / L"config.ini").string());
    } else {
        save_file = "save.sav";
        user_name_file ="user_name.txt";
		replay_path = "replay";
		morgue_path = "morgue";

		option_mg.init("./config.ini");
    }
}


void delete_file()
{
	remove(save_file.c_str());
	saveexit = false;

}
void saveandexit()
{
	if(!ReplayClass.ReplayMode())
		g_saveandexit = true;
}
void saveandcheckexit()
{
	while(1)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SAVE_QUIT_YN),false,false,false,CL_help);
		switch(waitkeyinput())
		{
		case 'Y':
			enterlog();	
			if(!ReplayClass.ReplayMode())
				g_saveandexit = true;
			return;
		case 'N':
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE_QUIT),true,false,false,CL_help);
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
		switch(waitkeyinput())
		{
		case 'Y':
			enterlog();
			you.dead_reason = DR_QUIT;
			GameOver();
			//delete_file();
			//PostQuitMessage(0);
			return;
		case 'N':
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE_QUIT),true,false,false,CL_help);
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