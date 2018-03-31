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

	string name;

	int height;
	int width;

	int bgm_volume;
	int se_volume;

private:
	optionManager() {};
public:
	optionManager(string fileName);

	void createNewFile(string fileName);

	int getHeight() { return 600; };
	int getWidth() { return 800; };
	int getHeightCommon() { return height; };
	int getWidthCommon() { return width; };

	int getBgmVolume() { return bgm_volume; };
	int getSeVolume() { return se_volume; };

private:
	string TCHARToString(const TCHAR* ptsz);

};


extern optionManager option_mg;




