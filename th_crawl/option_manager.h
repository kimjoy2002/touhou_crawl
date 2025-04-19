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
#include <vector>

#define MAX_STR_SIZE 260

using namespace std;


struct screen_info {
	int width;
	int height;
	screen_info(int width, int height):width(width),height(height){}
};

class optionManager {
	string fileName;
	string name;

	int current_pos;
	int height;
	int width;
	int tile_max_x = 8;
	int tile_max_y = 8;
	bool fullscreen;

	int bgm_volume;
	int se_volume;

	string lang;

public:
	optionManager() {};
	void init(string fileName);

	void createNewFile(string fileName);
	void calcTileXY();
	screen_info getNextScreen(int& pos);

	string getName() { return name; };


	int getWidth() { return width; };
	int getHeight() { return height; };
	void setWidth(int w_value);
	void setHeight(int h_value);
	int getTileMaxX() { return tile_max_x; };
	int getTileMaxY() { return tile_max_y; };
	int getCurrentPos() { return current_pos; };
	bool getFullscreen() { return fullscreen; };
	void setFullscreen(bool lang_value);


	int getBgmVolume() { return bgm_volume; };
	int getSeVolume() { return se_volume; };

	void setLang(const string& lang_value);
	string getLang() { return lang; };

private:
	string TCHARToString(const TCHAR* ptsz);

};


extern optionManager option_mg;




