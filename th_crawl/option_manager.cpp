//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: option_manager.cpp
//
// 내용: 옵션 매니저의 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "option_manager.h"
#include "steam_api.h"
#include "common.h"
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
std::string wcharToUtf8(const wchar_t* wstr);

void optionManager::init(wstring fileName) {
	this->steam_lang = steam_mg.getSteamLang();
	this->fileName = fileName;
	struct _stat64i32  stStat = { 0 };

	if (_wstat(fileName.c_str(), &stStat) == -1){
		createNewFile(fileName);
	}
	{

		wchar_t szBuf[MAX_STR_SIZE] = { 0, };

		GetPrivateProfileStringW(_T(L"config"), _T(L"name"), _T(L"Default"), szBuf, MAX_STR_SIZE, fileName.c_str());
		name = wcharToUtf8(szBuf);

		GetPrivateProfileStringW(_T(L"config"), _T(L"height"), _T(L"720"), szBuf, MAX_STR_SIZE, fileName.c_str());
		height =  std::stoi(szBuf);

		GetPrivateProfileStringW(_T(L"config"), _T(L"width"), _T(L"1280"), szBuf, MAX_STR_SIZE, fileName.c_str());
		width =   std::stoi(szBuf);
		
		GetPrivateProfileStringW(_T(L"config"), _T(L"saveslot"), _T(L"1"), szBuf, MAX_STR_SIZE, fileName.c_str());
		current_saveslot =  std::stoi(szBuf);

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

		GetPrivateProfileStringW(_T(L"config"), _T(L"fullscreen"), _T(L"false"), szBuf, MAX_STR_SIZE, fileName.c_str());
		fullscreen =  (wcscmp(szBuf, L"true") == 0 || wcscmp(szBuf, L"1") == 0);

		GetPrivateProfileStringW(_T(L"config"), _T(L"bgm_volume"), _T(L"70"), szBuf, MAX_STR_SIZE, fileName.c_str());
		bgm_volume = std::stoi(szBuf);

		GetPrivateProfileStringW(_T(L"config"), _T(L"se_volume"), _T(L"70"), szBuf, MAX_STR_SIZE, fileName.c_str());
		se_volume = std::stoi(szBuf);

		// GetPrivateProfileString(_T("config"), _T("server_ip"), _T("joy1999.codns.com"), szBuf, MAX_STR_SIZE, fileName.c_str());
		// server_ip = TCHARToString(szBuf);

		// GetPrivateProfileString(_T("config"), _T("server_port"), _T("12345"), szBuf, MAX_STR_SIZE, fileName.c_str());
		// server_port = _tstoi(szBuf);

		GetPrivateProfileStringW(_T(L"config"), _T(L"language"), _T(ConvertUTF8ToUTF16(steam_lang).c_str()), szBuf, MAX_STR_SIZE, fileName.c_str());
		lang = wcharToUtf8(szBuf);
	}
}

void optionManager::createNewFile(wstring fileName) {
	std::wstring name_w = L"Default";
	WritePrivateProfileStringW(_T(L"config"), _T(L"name"), name_w.c_str(), fileName.c_str());

	std::wstring height_w = L"720";
	WritePrivateProfileStringW(_T(L"config"), _T(L"height"), height_w.c_str(), fileName.c_str());

	std::wstring width_w = L"1280";
	WritePrivateProfileStringW(_T(L"config"), _T(L"width"), width_w.c_str(), fileName.c_str());
	
	std::wstring saveslot_w = L"1";
	WritePrivateProfileStringW(_T(L"config"), _T(L"saveslot"), saveslot_w.c_str(), fileName.c_str());

	std::wstring fullscreen_w = L"false";
	fullscreen = false;
	WritePrivateProfileStringW(_T(L"config"), _T(L"fullscreen"), fullscreen_w.c_str(), fileName.c_str());

	std::wstring bgm_volume_w = L"70";
	WritePrivateProfileStringW(_T(L"config"), _T(L"bgm_volume"), bgm_volume_w.c_str(), fileName.c_str());

	std::wstring se_volume_w = L"70";
	WritePrivateProfileStringW(_T(L"config"), _T(L"se_volume"), se_volume_w.c_str(), fileName.c_str());

	std::wstring steam_lang_w = ConvertUTF8ToUTF16(steam_lang);
	WritePrivateProfileStringW(_T(L"config"), _T(L"language"), steam_lang_w.c_str(), fileName.c_str());
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
        CStringW strValue = full_value ? _T(L"true") : _T(L"false");
        WritePrivateProfileStringW(_T(L"config"), _T(L"fullscreen"), strValue, fileName.c_str());
	}
}

void optionManager::setSaveSlot(int currentsaveslot) {
    current_saveslot = currentsaveslot; 

	if(!fileName.empty()) {
		CStringW str(to_string(current_saveslot).c_str());
		WritePrivateProfileStringW(_T(L"config"), _T(L"false"), str, fileName.c_str());
	}
}

void optionManager::setWidth(int w_value) {
    width = w_value;  // lang이 string일 경우

	if(!fileName.empty()) {
		CStringW strW(to_string(w_value).c_str());
		WritePrivateProfileStringW(_T(L"config"), _T(L"width"), strW, fileName.c_str());
	}
}


void optionManager::setHeight(int h_value) {
    height = h_value;  // lang이 string일 경우

	if(!fileName.empty()) {
		CStringW strH(to_string(h_value).c_str());
		WritePrivateProfileStringW(_T(L"config"), _T(L"height"), strH, fileName.c_str());
	}
}


void optionManager::setLang(const string& lang_value) {
    lang = lang_value;  // lang이 string일 경우

	if(!fileName.empty()) {
		CStringW strLang(lang_value.c_str());
		WritePrivateProfileStringW(_T(L"config"), _T(L"language"), strLang, fileName.c_str());
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

std::string wcharToUtf8(const wchar_t* wstr)
{
    if (!wstr) return "";

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    if (size_needed <= 0) return "";

    std::string result(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &result[0], size_needed, nullptr, nullptr);
    result.pop_back(); // remove null terminator

    return result;
}