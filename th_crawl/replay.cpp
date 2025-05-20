//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: replay.cpp
//
// 내용: 리플레이
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include <direct.h>
#include <stdio.h>
#include <io.h> 
#include <time.h>
#include "replay.h"
#include "map.h"
#include "save.h"
#include "key.h"
#include <windows.h>
extern std::atomic<bool> g_saveandexit;

typedef struct _finddata_t  FILE_SEARCH;


extern const char *version_string;
extern string replay_path;

replay_class ReplayClass;

replay_class::~replay_class()
{
	if(play_fp)
		fclose(play_fp);
}


void replay_class::DeleteRpy()
{
	if(!replay_string.empty()){		
		remove(replay_string.c_str());
		replay_string.clear();
	}
    input_buffer.clear();
}

void replay_class::SaveDatas(FILE *fp)
{
	char temp[1024];
	sprintf_s(temp,1024,"%s",replay_string.c_str());
	SaveData<char>(fp,*temp, strlen(temp)+1);

	SaveData<base_infor>(fp,infor);
	
	SaveData<bool>(fp,init);
	SaveData<bool>(fp,play);
	SaveData<bool>(fp,auto_key);
	FlushReplayInput();
}
void replay_class::LoadDatas(FILE *fp)
{
	DeleteRpy();
	char temp[1024];
	LoadData<char>(fp, *temp);
	replay_string = temp;
	
	LoadData<base_infor>(fp,infor);
	
	LoadData<bool>(fp,init);
	LoadData<bool>(fp,play);
	LoadData<bool>(fp,auto_key);
}




void replay_class::init_class(std::vector<int>& init_starting)
{
	DeleteRpy();
	struct tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);
	char filename[512];
	sprintf_s(filename,512, (replay_path + "/%s-%04d%02d%02d-%02d%02d%02d.rpy").c_str(),you.user_name.c_str(),1900+t.tm_year,t.tm_mon+1,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec);
	
	replay_string = filename;
	sprintf_s(infor.name,64,"%s",you.user_name.c_str());
	sprintf_s(infor.version,32,"%s",version_string);
	memset(infor.infor,0,256);
	infor.rand_num = map_list.random_number;
    infor.starting[0] = init_starting[0];
	infor.starting[1] = init_starting[1];
	infor.starting[2] = init_starting[2];
	infor.starting[3] = init_starting[3];
	init = true;
}
void replay_class::init_replay(const char* name)
{
	DeleteRpy();

	replay_string = name;
	
	play = true;
	auto_key = true;
}

bool replay_class::SaveReplayStart()
{
    if (!init || play)
        return false;

    _mkdir(replay_path.c_str());  // Windows에서 mkdir 대신 _mkdir 사용

    FILE* fp = nullptr;
    struct tm t;
    time_t now;
    time(&now);
	localtime_s(&t, &now);

    if (replay_string.empty()) {
        replay_string = replay_path + "/temp.rpy";
    }
	
    std::wstring wfilename = ConvertUTF8ToUTF16(replay_string);

    if (_wfopen_s(&fp, wfilename.c_str(), L"wb") != 0 || !fp) {
        return false;
    }

    fwrite(&infor, sizeof(base_infor), 1, fp);
    fclose(fp);

    return true;
}




bool replay_class::SaveReplayInput(DWORD time_, int key_, InputedKey inputedkey)
{
    if (!init || play)
        return false;

    input_buffer.push_back({time_, key_, inputedkey});
    return true;
}
bool replay_class::FlushReplayInput()
{
    if (input_buffer.empty() || replay_string.empty())
        return false;

    FILE* fp = nullptr;
    std::wstring wfilename = ConvertUTF8ToUTF16(replay_string);

    if (_wfopen_s(&fp, wfilename.c_str(), L"ab") != 0 || !fp)
        return false;

    for (const auto& entry : input_buffer) {
        fwrite(&entry.time_, sizeof(DWORD), 1, fp);
        fwrite(&entry.key_, sizeof(int), 1, fp);
        if (entry.key_ == -1) {
            fwrite(&entry.inputedkey.mouse, sizeof(int), 1, fp);
            fwrite(&entry.inputedkey.val1, sizeof(int), 1, fp);
            fwrite(&entry.inputedkey.val2, sizeof(int), 1, fp);
        }
    }

    fclose(fp);
    input_buffer.clear();
    return true;
}




bool replay_class::LoadReplayStart()
{
	if(replay_string.empty())
	{
		auto_key = false;
		play = false;
		init = false;
		return false;
	}

	char filename[512];
	_mkdir(replay_path.c_str());
	
	sprintf_s(filename,512,"%s",replay_string.c_str());

	
	std::wstring wfilename = ConvertUTF8ToUTF16(filename);

	if (_wfopen_s(&play_fp, wfilename.c_str(), L"rb") != 0 || !play_fp) {
		auto_key = false;
		play = false;
		init = false;
		return false;
	}

	fread(&infor,sizeof(base_infor),1,play_fp);

	if(!strcmp(version_string,infor.version))
	{
		you.user_name = string(infor.name);
		map_list.random_number = infor.rand_num;
		srand(map_list.random_number);
		//rand_seed(map_list.random_number);



		play = true;
		init = true;
		auto_key = true;
		return true;
	}
	else
	{
		play = false;
		auto_key = false;
		init = false;
		return false;
	}

}

bool replay_class::LoadReplayInput(DWORD *time_, int *key_, InputedKey& inputedkey)
{
	if(!init || !play)
		return false;

	if(play_fp)
	{
		fread(time_,sizeof(DWORD),1,play_fp);
		fread(key_,sizeof(int),1,play_fp);		
		if(*key_ == -1) {
			fread(&(inputedkey.mouse), sizeof(int), 1, play_fp);
			fread(&(inputedkey.val1), sizeof(int), 1, play_fp);
			fread(&(inputedkey.val2), sizeof(int), 1, play_fp);
		}

		if(feof(play_fp))
		{
			auto_key = false;
			init = false;
			game_over = true;
			play = false;
			return false;
		}
	}
	else
	{
		auto_key = false;
		init = false;
		game_over = true;
		play = false;
		return false;
	}
	return true;

}


bool replay_class::StopReplay(string str)
{
	if(play)
	{//만약 리플레이모드로 실행중일때!
		auto_key = false;
		init = false;
	}
	else if(init)
	{//그게 아니면 리플레이 저장중일것이다.
		FlushReplayInput();
		strcpy_s(infor.infor,256,str.c_str());
		
		char filename[512];
		FILE *fp;  
		sprintf_s(filename,512,"%s",replay_string.c_str());

		std::wstring wfilename = ConvertUTF8ToUTF16(filename);

		if(_wfopen_s(&fp, wfilename.c_str(), L"r+b") == 0 && fp)
		{
			//rewind(fp);
			fwrite(&infor,sizeof(base_infor),1,fp);
			//rewind(fp);
			fclose(fp);
			replay_string = "";
		}
	}
	return true;


}


class replay_sort
{
public:
	string path;	
	string infor;	
	FILETIME localtime;
	replay_sort(string path_,string infor_,FILETIME localtime_):path(path_),infor(infor_),localtime(localtime_){};


	bool operator<(const replay_sort &t) const {
		return CompareFileTime(&localtime,&t.localtime)>0;
    }
};



bool replay_menu(int value_)
{
	char blank[32];
	sprintf_s(blank,32,"            ");


	
	{



	
		WIN32_FIND_DATAA findFileData;
		HANDLE MyHandle = FindFirstFileA((replay_path + "/*.rpy").c_str(),&findFileData);
		
		
		std::vector<replay_sort> file_vector;
		if(MyHandle != INVALID_HANDLE_VALUE)
		{
			do
			{	
				char filename[512];
				
				sprintf_s(filename,512,(replay_path + "/%s").c_str(),findFileData.cFileName);
				
				std::wstring wfilename = ConvertUTF8ToUTF16(filename);
				FILE *fp;
				base_infor temp_infor;
				if(_wfopen_s(&fp, wfilename.c_str(), L"rb") == 0 && fp)
				{
					fread(&temp_infor,sizeof(base_infor),1,fp);
					fclose(fp);
					if(strcmp(temp_infor.version,version_string)==0 && strcmp(filename, ReplayClass.replay_string.c_str()) && temp_infor.infor[0] != 0)
					{
						FILETIME localtime_;
						FileTimeToLocalFileTime(&findFileData.ftCreationTime,&localtime_);


						file_vector.push_back(replay_sort(findFileData.cFileName,temp_infor.infor,localtime_));



					}
				}
			}while(FindNextFileA(MyHandle,&findFileData)!=0 );



			

		}

		sort(file_vector.begin(),file_vector.end());
		int page=0;
		int file_num=file_vector.size();
		int max_page=(file_num+6)/7;

		while(1)
		{



			deletesub();

			printsub("",true,CL_normal);
			printsub("",true,CL_normal);
			printsub("",true,CL_normal);
			printsub(blank,false,CL_warning);
			printsub(LocalzationManager::locString(LOC_SYSTEM_REPLAY_LIST),true,CL_help);
			printsub("",true,CL_normal);
			printsub("",true,CL_normal);


			if(file_num)
			{
				char char_ = 'a'; 
				for(int i=0;i<7;i++)
				{
					int cur= page*7+i;

					if(cur+1>file_num)
						break;

					ostringstream ss;
					ss << char_ << " - " << file_vector[cur].path;
					SYSTEMTIME stC;
					memset(&stC, 0, sizeof(stC));
					FileTimeToSystemTime(&file_vector[cur].localtime, &stC);
					printsub(ss.str(),false,CL_normal,char_);

				
					if(60 - PrintCharWidth(ss.str()) > 0) {
						printsub(string(60 - PrintCharWidth(ss.str()), ' '), false, CL_normal);
					} else {
						printsub(" ", false, CL_normal);
					}

					{
						ostringstream ss;
						ss << LocalzationManager::formatString(LOC_SYSTEM_REPLAY_TIMELINE,
							PlaceHolderHelper(to_string(stC.wYear)),
							PlaceHolderHelper(to_string(stC.wMonth)),
							PlaceHolderHelper(to_string(stC.wDay)),
							PlaceHolderHelper(to_string(stC.wHour)),
							PlaceHolderHelper(to_string(stC.wMinute)));
						printsub(ss.str(),true,CL_help);
					}


					
					printsub(blank,false,CL_warning);		
					printsub(file_vector[cur].infor,true,CL_green);

					printsub("",true,CL_normal);
					char_++;
				}
			}
			else
			{
			
				printsub(blank,false,CL_warning);
				printsub(LocalzationManager::locString(LOC_SYSTEM_REPLAY_NOTEXIST),true,CL_danger);
				printsub("",true,CL_normal);

			}
			
			{
				printsub(blank,false,CL_warning);
				printsub("←",false,CL_danger, VK_LEFT);
				printsub("  ",false,CL_warning);
				printsub(LocalzationManager::formatString(LOC_SYSTEM_REPLAY_PAGE, PlaceHolderHelper(to_string(page+1))),false,CL_help);
				printsub("  ",false,CL_warning);
				printsub("→",true,CL_danger, VK_RIGHT);
			}
			printsub("",true,CL_normal);
			printsub("esc - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_BACK),true,CL_normal,VK_ESCAPE);
		
			changedisplay(DT_SUB_TEXT);
			InputedKey inputedKey;
			int input_ = waitkeyinput(inputedKey,true);

			bool out_ = false;
			if(input_ >= 'a' && input_ <= 'h')
			{
				int select_ = page*7+ (input_ - 'a');

				if(select_<file_num)
				{
					char temp[512];
					sprintf_s(temp,512,(replay_path + "/%s").c_str(),file_vector[select_].path.c_str());
					ReplayClass.init_replay(temp);
					ReplayClass.LoadReplayStart();
					game_over = true;
					return true;
				}
			}
			else if(input_ == VK_LEFT)
			{
				if(page>0)
					page--;
			}
			else if(input_ == VK_RIGHT)
			{
				if(max_page>page+1)
					page++;
			}
			else if(input_ == -1) {
				if(inputedKey.mouse == MKIND_SCROLL_UP) {
					if(page>0)
						page--;
				} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
					if(max_page>page+1)
						page++;
				}
				else if(inputedKey.isRightClick()) {
					out_ = true;
				}
			}
			else if(input_ == VK_ESCAPE ||
				input_ ==  GVK_BUTTON_B ||
				input_ ==  GVK_BUTTON_B_LONG)

			{
				out_= true;
			}
			if(out_)
				break;
		}


	}
	changedisplay(DT_SUB_TEXT);

	return false;
}


