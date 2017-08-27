//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: option_manager.cpp
//
// 내용: 옵션 매니저의 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "option_manager.h"
#include <stdio.h>

optionManager option_mg("./config.ini");

optionManager::optionManager(string fileName) {
	struct stat stStat = { 0 };

	if (stat(fileName.c_str(), &stStat) == -1){
		createNewFile(fileName);
	}
	{

		TCHAR szBuf[MAX_STR_SIZE] = { 0, };

		GetPrivateProfileString(_T("config"), _T("name"), _T("이름없음"), szBuf, MAX_STR_SIZE, fileName.c_str());
		name = TCHARToString(szBuf);

		GetPrivateProfileString(_T("config"), _T("height"), _T("600"), szBuf, MAX_STR_SIZE, fileName.c_str());
		height = _tstoi(szBuf);

		GetPrivateProfileString(_T("config"), _T("width"), _T("800"), szBuf, MAX_STR_SIZE, fileName.c_str());
		width = _tstoi(szBuf);
	}
}

void optionManager::createNewFile(string fileName) {
	CString strString = _T("이름없음");
	TCHAR  *tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("name"), tchr, fileName.c_str());

	strString = _T("600");
	tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("height"), tchr, fileName.c_str());

	strString = _T("800");
	tchr = (TCHAR*)(LPCTSTR)strString;
	WritePrivateProfileString(_T("config"), _T("width"), tchr, fileName.c_str());

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