//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: option_manager.h
//
// 내용: 옵션 매니저의 설정
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <tchar.h>
#include <atlstr.h>
#include <windows.h> 

#define MAX_STR_SIZE 260

using namespace std;
class optionManager {
	string fileName;
	string name;

	int height;
	int width;

	int bgm_volume;
	int se_volume;

	string lang;

private:
	optionManager() {};
public:
	optionManager(string fileName);

	void createNewFile(string fileName);

	string getName() { return name; };


	int getHeight() { return height; };
	int getWidth() { return width; };
	int getHeightCommon() { return height; };
	int getWidthCommon() { return width; };

	int getBgmVolume() { return bgm_volume; };
	int getSeVolume() { return se_volume; };

	void setLang(const string& lang_value);
	string getLang() { return lang; };

private:
	string TCHARToString(const TCHAR* ptsz);

};


extern optionManager option_mg;




