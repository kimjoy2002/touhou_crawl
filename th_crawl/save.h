//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: save.h
//
// 내용: 세이브 편의용 함수(템플릿!)
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef  __SAVE_H__
#define  __SAVE_H__

#include <stdio.h>

#include <iostream>

extern std::wstring save_file_w[3];
extern std::wstring user_name_file_w;


extern const char *version_string;
extern std::string loading_version_string;

bool isPrevVersion(const std::string& versionstring, const std::string& targetstring);


template <typename T>
void SaveData(FILE *fp, const T &input, int size = 1)
{
	char *var;
	fprintf(fp, "%d ",(int)sizeof(T)*size);
	var = (char*)(&input);
	for(unsigned int i=0;i<(unsigned int)sizeof(T)*size;i++)
	{
		fputc(var[i],fp);
	}
}

template <typename T>
void LoadData(FILE *fp, T &output)
{
	char *temp = (char*)(&output);
	int size;
	fscanf_s(fp, "%d",&size);
	fgetc(fp);
	//temp = new char[sizeof(T)];
	for(int i=0;i<size;i++)
	{
		int temp_int = fgetc(fp);
		if(temp_int != -1)
		{
			temp[i] = temp_int;
		}
		else
		{
			temp[i] = 0;
		}
	}
	//delete[] temp;
}
void delete_file();
void saveandexit();
void saveandcheckexit();
void nosaveandexit();
bool load_data(const std::wstring& path);
bool load_name(const std::wstring& path);


#endif // __SAVE_H__