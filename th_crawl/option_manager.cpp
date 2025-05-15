//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: option_manager.cpp
//
// 내용: 옵션 매니저의 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "option_manager.h"
#include "steam_api.h"
#include <stdio.h>
#include <sys/stat.h>

optionManager option_mg;


vector<screen_info> able_screens = { 
	{800 ,600},
	{1024, 768},
	{1280, 720}, 
	{1366, 768}, 
	{1440, 900},
	{1680, 1050},
	{1600, 1200}, 
	{1920, 1080},
	{1920, 1200}
};

void optionManager::init(string fileName) {
	this->steam_lang = steam_mg.getSteamLang();
	this->fileName = fileName;
	struct stat stStat = { 0 };

	if (stat(fileName.c_str(), &stStat) == -1){
		createNewFile(fileName);
	}
	{

		TCHAR szBuf[MAX_STR_SIZE] = { 0, };

		GetPrivateProfileString(_T("config"), _T("name"), _T("Default"), szBuf, MAX_STR_SIZE, fileName.c_str());
		name = TCHARToString(szBuf);

		GetPrivateProfileString(_T("config"), _T("height"), _T("720"), szBuf, MAX_STR_SIZE, fileName.c_str());
		height = _tstoi(szBuf);

		GetPrivateProfileString(_T("config"), _T("width"), _T("1280"), szBuf, MAX_STR_SIZE, fileName.c_str());
		width = _tstoi(szBuf);
		
		GetPrivateProfileString(_T("config"), _T("saveslot"), _T("1"), szBuf, MAX_STR_SIZE, fileName.c_str());
		current_saveslot = _tstoi(szBuf);

		if(current_saveslot > 3) {
			current_saveslot = 3;
		} else if(current_saveslot < 1) {
			current_saveslot = 1;
		}

		current_pos = -1;
		int pos_ = -1;
		for(auto& screen : able_screens) {
			if(width < screen.width) {
				current_pos = pos_;
				break;
			} else if (height == screen.height) {
				if(height < screen.height) {
					current_pos = pos_;
					break;
				} else if(height == screen.height) {
					current_pos = pos_+1;
					break;
				}
			}
			pos_++;
		}
		calcTileXY();

		GetPrivateProfileString(_T("config"), _T("fullscreen"), _T("false"), szBuf, MAX_STR_SIZE, fileName.c_str());
		fullscreen = (_tcscmp(szBuf, _T("true")) == 0 || _tcscmp(szBuf, _T("1")) == 0);

		GetPrivateProfileString(_T("config"), _T("bgm_volume"), _T("70"), szBuf, MAX_STR_SIZE, fileName.c_str());
		bgm_volume = _tstoi(szBuf);

		GetPrivateProfileString(_T("config"), _T("se_volume"), _T("70"), szBuf, MAX_STR_SIZE, fileName.c_str());
		se_volume = _tstoi(szBuf);

		// GetPrivateProfileString(_T("config"), _T("server_ip"), _T("joy1999.codns.com"), szBuf, MAX_STR_SIZE, fileName.c_str());
		// server_ip = TCHARToString(szBuf);

		// GetPrivateProfileString(_T("config"), _T("server_port"), _T("12345"), szBuf, MAX_STR_SIZE, fileName.c_str());
		// server_port = _tstoi(szBuf);

		GetPrivateProfileString(_T("config"), _T("language"), _T(steam_lang.c_str()), szBuf, MAX_STR_SIZE, fileName.c_str());
		lang = TCHARToString(szBuf);
	}
}

void optionManager::createNewFile(string fileName) {
	CString strString = _T("Default");
	TCHAR  *tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("name"), tchr, fileName.c_str());

	strString = _T("720");
	tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("height"), tchr, fileName.c_str());

	strString = _T("1280");
	tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("width"), tchr, fileName.c_str());
	
	strString = _T("1");
	tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("saveslot"), tchr, fileName.c_str());

	strString = _T("false");
	fullscreen = (_tcscmp((LPCTSTR)strString, _T("true")) == 0 || _tcscmp((LPCTSTR)strString, _T("1")) == 0);
	WritePrivateProfileString(_T("config"), _T("fullscreen"), tchr, fileName.c_str());

	strString = _T("70");
	tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("bgm_volume"), tchr, fileName.c_str());

	strString = _T("70");
	tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("se_volume"), tchr, fileName.c_str());

	// strString = _T("joy1999.codns.com");
	// tchr = (TCHAR*)(LPCTSTR)strString;
	// WritePrivateProfileString(_T("config"), _T("server_ip"), tchr, fileName.c_str());

	// strString = _T("12345");
	// tchr = (TCHAR*)(LPCTSTR)strString;
	// WritePrivateProfileString(_T("config"), _T("server_port"), tchr, fileName.c_str());

	strString = _T(steam_lang.c_str());
	tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("language"), tchr, fileName.c_str());
}

void optionManager::calcTileXY() {
	tile_max_x=1;
	tile_max_y=1;
	int minimum_check = 320;
	if(width <= 800) {
		minimum_check = 310; //800 보정
	}
	while(width > 32*((tile_max_x+1)*2+1)+minimum_check) {
		tile_max_x++;
	}
	while(height > 32*((tile_max_y+1)*2+1)) {
		tile_max_y++;
	}
}

screen_info optionManager::getNextScreen(int& pos) {
	pos++;
	if(pos<0)
		pos = 0;
	if(pos >= able_screens.size())
		pos = 0;
	return able_screens[pos];
}
void optionManager::setFullscreen(bool full_value) {
    fullscreen = full_value; 

	if(!fileName.empty()) {
        CString strValue = full_value ? _T("true") : _T("false");
        WritePrivateProfileString(_T("config"), _T("fullscreen"), strValue, fileName.c_str());
	}
}

void optionManager::setSaveSlot(int currentsaveslot) {
    current_saveslot = currentsaveslot; 

	if(!fileName.empty()) {
		CString str(to_string(current_saveslot).c_str());
		WritePrivateProfileString(_T("config"), _T("false"), str, fileName.c_str());
	}
}

void optionManager::setWidth(int w_value) {
    width = w_value;  // lang이 string일 경우

	if(!fileName.empty()) {
		CString strW(to_string(w_value).c_str());
		WritePrivateProfileString(_T("config"), _T("width"), strW, fileName.c_str());
	}
}


void optionManager::setHeight(int h_value) {
    height = h_value;  // lang이 string일 경우

	if(!fileName.empty()) {
		CString strH(to_string(h_value).c_str());
		WritePrivateProfileString(_T("config"), _T("height"), strH, fileName.c_str());
	}
}


void optionManager::setLang(const string& lang_value) {
    lang = lang_value;  // lang이 string일 경우

	if(!fileName.empty()) {
		CString strLang(lang_value.c_str());
		WritePrivateProfileString(_T("config"), _T("language"), strLang, fileName.c_str());
	}
}


string optionManager::TCHARToString(const TCHAR* ptsz)
{
	// Handy for converting TCHAR to std::string (char)
	// If the conversion fails, an empty string is returned.
	std::string str;
#ifdef UNICODE
	// calculate the size of the char string required
	// Note: If wcstombs encounters a wide character it cannot convert
	//      to a multibyte character, it returns –1.
	int len = 1 + wcstombs(0, ptsz, 0);
	if (0 == len) return str;

	char* c = new char[len];
	if (NULL == c) throw std::bad_alloc();
	c[0] = '\0';

	wcstombs(c, ptsz, len);
	str = c;
	delete[]c;
#else
	str = ptsz;
#endif
	return str;
}