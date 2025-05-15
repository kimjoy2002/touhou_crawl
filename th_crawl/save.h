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

extern std::string save_file[3];
extern std::string user_name_file;

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
bool load_data(const char* path);
bool load_name(const char* path);


#endif // __SAVE_H__