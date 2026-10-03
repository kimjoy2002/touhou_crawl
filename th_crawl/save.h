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

#include <algorithm>
#include <cstring>
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

inline bool LoadDataBytes(FILE *fp, void *output, size_t capacity)
{
	if(!fp || !output || feof(fp))
		return false;

	int size = 0;
	if(fscanf_s(fp, "%d", &size) != 1 || size < 0)
		return false;
	if(fgetc(fp) == EOF)
		return false;

	char *temp = static_cast<char*>(output);
	size_t stored_size = static_cast<size_t>(size);
	size_t copy_size = std::min(stored_size, capacity);
	size_t read_size = fread(temp, 1, copy_size, fp);
	if(read_size < copy_size)
	{
		memset(temp + read_size, 0, copy_size - read_size);
		return false;
	}

	size_t remain = stored_size - copy_size;
	if(remain > 0)
	{
		if(fseek(fp, static_cast<long>(remain), SEEK_CUR) != 0)
			return false;
	}
	return stored_size <= capacity;
}

template <typename T>
bool LoadData(FILE *fp, T &output)
{
	return LoadDataBytes(fp, &output, sizeof(T));
}

template <typename T, size_t N>
bool LoadData(FILE *fp, T (&output)[N])
{
	return LoadDataBytes(fp, output, sizeof(output));
}

std::string loadString(FILE* fp);

void delete_file();
void saveandexit();
void saveandcheckexit();
void nosaveandexit();
bool load_data(const std::wstring& path);
bool load_name(const std::wstring& path);


#endif // __SAVE_H__
