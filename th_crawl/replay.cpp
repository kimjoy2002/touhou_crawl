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

typedef struct _finddata_t  FILE_SEARCH;


extern const char *version_string;

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




void replay_class::init_class()
{
	DeleteRpy();


	struct tm *t;
	time_t now;
	time(&now);
	t=localtime(&now);
	char filename[512];
	sprintf_s(filename,512,"replay/%s-%04d%02d%02d-%02d%02d%02d.rpy",you.user_name.c_str(),1900+t->tm_year,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	
	replay_string = filename;
	sprintf_s(infor.name,32,"%s",you.user_name.c_str());
	sprintf_s(infor.version,32,"%s",version_string);
	memset(infor.infor,0,256);
	infor.rand_num = map_list.random_number;
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

    _mkdir("replay");  // Windows에서 mkdir 대신 _mkdir 사용

    FILE* fp = nullptr;
    struct tm* t;
    time_t now;
    time(&now);
    t = localtime(&now);

    if (replay_string.empty()) {
        replay_string = "replay/temp.rpy";
    }
	
    std::wstring wfilename = ConvertUTF8ToUTF16(replay_string);

    if (_wfopen_s(&fp, wfilename.c_str(), L"wb") != 0 || !fp) {
        return false;
    }

    fwrite(&infor, sizeof(base_infor), 1, fp);
    fclose(fp);

    return true;
}




bool replay_class::SaveReplayInput(DWORD time_, int key_)
{
    if (!init || play)
        return false;

    if (!replay_string.empty()) {
        FILE* fp = nullptr;
        std::wstring wfilename = ConvertUTF8ToUTF16(replay_string);

        if (_wfopen_s(&fp, wfilename.c_str(), L"ab") == 0 && fp) {
            fwrite(&time_, sizeof(DWORD), 1, fp);
            fwrite(&key_, sizeof(unsigned int), 1, fp);
            fclose(fp);
        }
    }
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
	mkdir("replay");
	
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

bool replay_class::LoadReplayInput(DWORD *time_, int *key_)
{
	if(!init || !play)
		return false;

	if(play_fp)
	{
		fread(time_,sizeof(DWORD),1,play_fp);
		fread(key_,sizeof(unsigned int),1,play_fp);
		
		if(feof(play_fp))
		{
			auto_key = false;
			init = false;
			PostQuitMessage(0);
			return false;
		}
	}
	else
	{
		auto_key = false;
		init = false;
		PostQuitMessage(0);
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
		HANDLE MyHandle = FindFirstFileA("./replay/*.rpy",&findFileData);
		
		
		std::vector<replay_sort> file_vector;
		if(MyHandle != INVALID_HANDLE_VALUE)
		{
			do
			{	
				char filename[512];
				
				sprintf_s(filename,512,"replay/%s",findFileData.cFileName);
				
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
		int max_page=(file_num+9)/10;

		while(1)
		{



			deletesub();

			printsub("",true,CL_normal);
			printsub("",true,CL_normal);
			printsub("",true,CL_normal);
			printsub("",true,CL_normal);
			printsub(blank,false,CL_warning);
			printsub("리플레이 목록!",true,CL_help);
			printsub("",true,CL_normal);
			printsub("",true,CL_normal);


			if(file_num)
			{
				char char_[2] = "a"; 
				for(int i=0;i<10;i++)
				{
					int line_ = 0, cur= page*10+i;

					if(cur+1>file_num)
						break;

						
					SYSTEMTIME stC;
					memset(&stC, 0, sizeof(stC));
					FileTimeToSystemTime(&file_vector[cur].localtime, &stC);
					line_ += printsub(blank,false,CL_warning);				
					line_ += printsub(char_,false,CL_danger);
					line_ += printarraysub(false, CL_normal, 2, " - ",file_vector[cur].path.c_str());

				
					{
						char temp[128] = "                                                     ";
						temp[line_<60?60-line_:1] = 0;
						printsub(temp,false,CL_normal);
					}

					{
						char temp[128];
						sprintf_s(temp,128,"%d년 %d월 %d일 %d시 %d분",stC.wYear, stC.wMonth,stC.wDay, stC.wHour, stC.wMinute);
						printsub(temp,true,CL_help);
					}


					
					line_ += printsub(blank,false,CL_warning);		
					printsub(file_vector[cur].infor,true,CL_green);

					printsub("",true,CL_normal);
					char_[0]++;
				}
			}
			else
			{
			
				printsub(blank,false,CL_warning);
				printsub("파일이 없어요!",true,CL_danger);
				printsub("",true,CL_normal);

			}
			
			{
				char temp[128];
				sprintf_s(temp,128,"%d페이지",page+1);
				printsub(blank,false,CL_warning);
				printsub(temp,true,CL_help);
			}

			changedisplay(DT_SUB_TEXT);
			int input_ = waitkeyinput(true);

			bool out_ = false;
			if(input_ >= 'a' && input_ <= 'l')
			{
				int select_ = page*10+ (input_ - 'a');

				if(select_<file_num)
				{
					char temp[512];
					sprintf_s(temp,512,"replay/%s",file_vector[select_].path.c_str());
					ReplayClass.init_replay(temp);
					ReplayClass.LoadReplayStart();
					out_ = true;
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
			else if(input_ == VK_ESCAPE)

			{
				out_= true;
			}
			if(out_)
				break;
		}


	}
	changedisplay(DT_TEXT);

	return false;
}