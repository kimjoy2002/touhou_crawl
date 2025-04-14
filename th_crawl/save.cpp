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

extern bool saveexit;
extern HANDLE mutx;
extern std::atomic<bool> g_saveandexit;

string save_file = "save.dat";
string user_name_file = "user_name.txt";

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