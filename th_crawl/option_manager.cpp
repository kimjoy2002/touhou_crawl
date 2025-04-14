//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: option_manager.cpp
//
// 내용: 옵션 매니저의 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "option_manager.h"
#include <stdio.h>
#include <sys/stat.h>

optionManager option_mg;

void optionManager::init(string fileName) {
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

		GetPrivateProfileString(_T("config"), _T("bgm_volume"), _T("70"), szBuf, MAX_STR_SIZE, fileName.c_str());
		bgm_volume = _tstoi(szBuf);

		GetPrivateProfileString(_T("config"), _T("se_volume"), _T("70"), szBuf, MAX_STR_SIZE, fileName.c_str());
		se_volume = _tstoi(szBuf);

		// GetPrivateProfileString(_T("config"), _T("server_ip"), _T("joy1999.codns.com"), szBuf, MAX_STR_SIZE, fileName.c_str());
		// server_ip = TCHARToString(szBuf);

		// GetPrivateProfileString(_T("config"), _T("server_port"), _T("12345"), szBuf, MAX_STR_SIZE, fileName.c_str());
		// server_port = _tstoi(szBuf);

		GetPrivateProfileString(_T("config"), _T("language"), _T("ENG"), szBuf, MAX_STR_SIZE, fileName.c_str());
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

	strString = _T("ENG");
	tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("language"), tchr, fileName.c_str());
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