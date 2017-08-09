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

private:
	optionManager() {};
public:
	optionManager(string fileName);

	void createNewFile(string fileName);

	int getHeight() { return height; };
	int getWidth() { return width; };


private:
	string TCHARToString(const TCHAR* ptsz);

};


extern optionManager option_mg;




