﻿

#include "common.h"
#include "map.h"
#include "option_manager.h"

#include <random>
#include <ctime>
#include <iostream>
#include <fstream>
#include <DirectXMath.h> 
#include <iomanip>
using namespace std;


extern POINT MousePoint;

extern map_infor map_list;

FILE *fpfpfp = NULL; 
int linelin =0;


std::mt19937 rand_engine;
std::mt19937 rand_engine_nonlogic;




void test_rand(const char* tt)
{

	char test_test[256], test_test2[256];
	

	if(!fpfpfp)
	{
		_wfopen_s(&fpfpfp, L"replay/test_random2.txt", L"rt");
	}
	if(fpfpfp)
		fgets(test_test,256,fpfpfp);
	linelin++;

	FILE *fp;  

if (_wfopen_s(&fp, L"replay/test_random.txt", L"at") != 0 || !fp) {
        return;
    }
	
	fprintf(fp,"|%30s|%ud\n",tt,map_list.random_number);
	
	sprintf_s(test_test2,256,"|%30s|%ud\n",tt,map_list.random_number);
	fclose(fp);



	if(strcmp(test_test,test_test2))
	{
			linelin+=2;
			
			linelin--;
			linelin--;

	}
}

void rand_seed(unsigned int seed_)
{
	rand_engine.seed((unsigned long)(seed_));

}

void init_nonlogic_seed(unsigned int seed_)
{
	rand_engine_nonlogic.seed((unsigned long)(seed_));

}

int LoopSelect(int min, int max, int cur)
{
	if(min	> max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	else if(min == max)
		return min;

	while(!(min <= cur && cur <= max))
	{
		if(cur < min)
			cur+= max-min+1;
		else
			cur-= max-min+1;
	}
	return cur;
}

int CutSelect(int min, int max, int cur)
{
	if(min	> max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	else if(min == max)
		return min;

	return ((cur>max)?max:((cur<min)?min:cur));

}

void log_replay_event(const std::string& message)
{
    //static std::ofstream replay_log("replay_debug.log", std::ios::app);
    //replay_log << message;
}
void init_replay_log() {
   // std::ofstream replay_log("replay_debug.log", std::ios::trunc); // 덮어쓰기
   // replay_log << "----------게임시작-----------";
    // 파일 열어서 비우기만 함
}

inline const char* filename_only(const char* path) {
    const char* slash1 = strrchr(path, '/');
    const char* slash2 = strrchr(path, '\\');
    const char* slash = (slash1 > slash2) ? slash1 : slash2;
    return slash ? slash + 1 : path;
}
void log_message(const char* file, int line, const std::string& message)
{
   // std::ostringstream oss;
   // oss << "[" << filename_only(file) << ":" << line << "] " << message << "\n";
    //log_replay_event(oss.str());
}
void log_key_input(const char* file, int line, const std::string& key_name)
{
   // std::ostringstream oss;
   // oss << "[KEYINPUT] " << key_name << " 입력\n";
    //log_replay_event(oss.str());
}


float rand_float_impl(const char* file, int line, float min, float max)
{
	//char temp_str[64];
	//sprintf_s(temp_str,64,"rand_float(%f,%f)",min,max);
	//test_rand(temp_str);
	
    // 로그 출력 (파일명, 라인번호, 인자, 결과 포함)
    //std::ostringstream oss;
    //oss << "[" << filename_only(file) << ":" << line << "][" << map_list.random_number << "] rand_float(" << min << ","<< max << ") 호출 \n";
    //log_replay_event(oss.str());  // 이건 너가 정의하는 함수로


	if(min == max)
		return min;

	if(min > max)
	{
		float temp = min;
		min = max;
		max = temp;
	}
	//min = (float)(random_number % (int)((max - min)*100 + 1)) /100 + min;
	//random_number = (((random_number*214013L + 2531011L)>>16)&0x7fff);
	rand_seed(map_list.random_number);
	int rand_ = abs((int)rand_engine());
	min = (float)(rand_ % (int)((max - min)*100 + 1)) /100 + min;
	map_list.random_number = rand_;
	
	//min = (float)(map_list.random_number % (int)((max - min)*100 + 1)) /100 + min;

	return min;
}

int rand_int_impl(const char* file, int line, int min, int max)
{
	//char temp_str[64];
	//sprintf_s(temp_str,64,"rand_int(%d,%d)",min,max);
	//test_rand(temp_str);


    //std::ostringstream oss;
   // oss << "[" << filename_only(file) << ":" << line << "][" << map_list.random_number << "] rand_int(" << min << ","<< max << ") 호출 \n";
    //log_replay_event(oss.str());  // 이건 너가 정의하는 함수로

	if(min == max)
		return min;

	if(min > max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	//min = (random_number % (max - min+1)) + min;
	
	rand_seed(map_list.random_number);
	int rand_ = rand_engine();
	min = (rand_engine() % (max - min+1)) + min;
	map_list.random_number = rand_;
	//map_list.random_number = (((map_list.random_number*214013L + 2531011L)>>16)&0x7fff);

	return min;
}


int rand_int_with_nonlogic(int min, int max)
{
	if(min == max)
		return min;

	if(min > max)
	{
		int temp = min;
		min = max;
		max = temp;
	}	
	min = (rand_engine_nonlogic() % (max - min+1)) + min;
	return min;
}


float GetPositionToAngle(float start_x, float start_y, float target_x, float target_y)
{
	return atan2(target_y - start_y, target_x - start_x) * 180 / DirectX::XM_PI;

}

float GetPositionToAngle2(float start_x, float start_y, float target_x, float target_y)
{
	return atan2(target_y - start_y, target_x - start_x);

}

float GetBaseAngle(float angle)
{
	while(angle <= 0 || angle > 360)
	{
		if(angle <= 0)
			angle += 360;
		if(angle > 360)
			angle -= 360;
	}
	return angle;
}
int GetPosToDirec(const coord_def &start, const coord_def &target)
{
	coord_def c = target-start;
	if(c.abs()<=2)
	{
		switch((c.x+1)*10+c.y+1)
		{
		case 00:
			return 7;
		case 10:
			return 0;
		case 20:
			return 1;
		case 01:
			return 6;
		case 11:
			return 0;
		case 21:
			return 2;
		case 02:
			return 5;
		case 12:
			return 4;
		case 22:
			return 3;
		}
	}
	int angle = (int) GetPositionToAngle(start.x,start.y,target.x,target.y);
	angle = (angle+360)%360;
	return GetAngleToDirec(angle);
}
coord_def GetDirecToPos(int pos_)
{
	//701
	//682
	//543
	switch((pos_+8)%8)
	{
	case 7:
		return coord_def(-1,-1);
	case 0:
		return coord_def(0,-1);
	case 1:
		return coord_def(1,-1);
	case 6:
		return coord_def(-1,0);
	case 2:
		return coord_def(1,0);
	case 5:
		return coord_def(-1,1);
	case 4:
		return coord_def(0,1);
	case 3:
		return coord_def(1,1);
	}
	return coord_def(0,0);
}

int GetDirecToChar(int pos_)
{
	switch((pos_+8)%8)
	{
	case 7:
		return 'y';
	case 0:
		return 'k';
	case 1:
		return 'u';
	case 6:
		return 'h';
	case 2:
		return 'l';
	case 5:
		return 'b';
	case 4:
		return 'j';
	case 3:
		return 'n';
	}
	return VK_RETURN;
}

int GetAngleToDirec(int angle)
{
	if(angle>=22 && angle <67)
		return 3;
	else if(angle>=67 && angle < 112)
		return 4;
	else if(angle>=112 && angle < 157)
		return 5;
	else if(angle>=157 && angle < 202)
		return 6;
	else if(angle>=202 && angle < 247)
		return 7;
	else if(angle>=247 && angle < 292)
		return 0;
	else if(angle>=292 && angle < 337)
		return 1;
	else
		return 2;
}

float GetPositionGap(float start_x, float start_y, float target_x, float target_y)
{
	return sqrt((target_x - start_x)*(target_x - start_x)+ (target_y - start_y)*(target_y - start_y));

}
std::set<coord_def> get_forward_5_tiles(coord_def my_pos, coord_def target_pos, bool main_line)
{
    int dx = target_pos.x - my_pos.x;
    int dy = target_pos.y - my_pos.y;

    // 방향 정규화
    if(dx != 0) dx /= abs(dx);
    if(dy != 0) dy /= abs(dy);

    std::set<coord_def> result;

    // 기본 방향 포함
	if(main_line)
	    result.insert(coord_def(my_pos.x + dx, my_pos.y + dy));

    // 좌우로 흐른 대각선 (측면 접근)
    if(dx != 0 && dy != 0) {
        result.insert(coord_def(my_pos.x + dx, my_pos.y));     // 수평
        result.insert(coord_def(my_pos.x, my_pos.y + dy));     // 수직
        result.insert(coord_def(my_pos.x + dx, my_pos.y + dy));  // 정 대각선
        result.insert(coord_def(my_pos.x - dx, my_pos.y + dy));  // 대각 반대쪽
    } else if(dx == 0) { // 수직 진행
        result.insert(coord_def(my_pos.x + 1, my_pos.y + dy));
        result.insert(coord_def(my_pos.x - 1, my_pos.y + dy));
        result.insert(coord_def(my_pos.x + 1, my_pos.y));
        result.insert(coord_def(my_pos.x - 1, my_pos.y));
    } else if(dy == 0) { // 수평 진행
        result.insert(coord_def(my_pos.x + dx, my_pos.y + 1));
        result.insert(coord_def(my_pos.x + dx, my_pos.y - 1));
        result.insert(coord_def(my_pos.x, my_pos.y + 1));
        result.insert(coord_def(my_pos.x, my_pos.y - 1));
    }

    return result;
}


float GetMaxX()
{
	return (float)option_mg.getWidth();
}

float GetMaxY()
{
	return (float)option_mg.getHeight();
}

float GetCenterX()
{
	return (float)option_mg.getWidth()/2;
}

float GetCenterY()
{
	return (float)option_mg.getHeight()/2;
}

/*float round(float x)
{
   return ((x>0) ? floor(x+.5f) : ceil(x-.5f));
}*/
float round_down(float x)
{
   return ((x>0) ? floor(x+0.25f) : ceil(x-0.75f));
}
float round_up(float x)
{
   return ((x>0) ? floor(x+0.75f) : ceil(x-0.25f));
}
float ceil_up(float x)
{
   return ((x>0) ? floor(x+0.999f) : ceil(x-0.001f));
}

string float_to_string(float value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    std::string result = oss.str();

    // 뒤에 붙은 불필요한 0 제거
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);

    // 소수점만 남으면 삭제
    if (!result.empty() && result.back() == '.') {
        result.pop_back();
    }

    return result;
}


unsigned char asctonum(char a)
{
	return (a>='a'&&a<='z')?(a-'a'):((a>='A'&&a<='Z')?(a-'A'+26):0);
}

char numtoasc(int a)
{
	if(a<0 || a >= 52)
		return 0;
	return a<26?a+'a':a+'A';
}

int randA(int x)
{
	if(x>0)
		return rand_int(0,x);
	else
		return 0;
}

int randA_1(int x)
{
	if(x>1)
		return rand_int(1,x);
	else
		return 1;
}

int randA_nonlogic(int x)
{
	if(x>0)
		return rand_int_with_nonlogic(0,x);
	else
		return 0;
}

int randA_1_nonlogic(int x)
{
	if(x>1)
		return rand_int_with_nonlogic(1,x);
	else
		return 1;
}

bool randB(int x, int point)
{
	return (randA(x) <= point);
}

int randC(int dice, int x)
{
	int a=0;
	for(int i=0;i<dice;i++)
		a += randA_1(x);
	return a;
}


int distan_coord(const coord_def& a, const coord_def& b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
	
}

wstring ConvertUTF8ToUTF16(const string& utf8Str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
	std::wstring utf16Str(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, &utf16Str[0], size_needed);
	return utf16Str;
}

string ConvertUTF16ToUTF8(const wstring& utf16Str) {
	if (utf16Str.empty()) return std::string();

	int size_needed = WideCharToMultiByte(CP_UTF8, 0, utf16Str.c_str(), -1, NULL, 0, NULL, NULL);
	std::string utf8Str(size_needed - 1, 0);
	WideCharToMultiByte(CP_UTF8, 0, utf16Str.c_str(), -1, &utf8Str[0], size_needed, NULL, NULL);
	
	return utf8Str;
	
}

bool IsCJKWideChar(wchar_t ch)
{
	return (
		(ch >= 0x1100 && ch <= 0x11FF) ||  // 한글 자모
		(ch >= 0x2E80 && ch <= 0xA4CF) ||  // 중국어·일본어 범위
		(ch >= 0xAC00 && ch <= 0xD7A3) ||  // 한글 완성형 (가~힣)
		(ch >= 0xF900 && ch <= 0xFAFF) ||  // 한중일 호환용 한자
		(ch >= 0xFF01 && ch <= 0xFF60) ||  // 전각 문자 (？！＠ 등)
		(ch >= 0xFFE0 && ch <= 0xFFE6)	 // 전각 기호 (￥ 등)
	);
}
int PrintCharWidth(const wstring& wtext)
{
	int len = 0;
	for (wchar_t ch : wtext)
	{
		if (IsCJKWideChar(ch))
			len+=2;
		else if(ch ==  '\0' || ch == '\n')
			continue;
		else
			len++;
	}
	return len;
}

int PrintCharWidth(const string& text)
{
	wstring wtext = ConvertUTF8ToUTF16(text);
	return PrintCharWidth(wtext);
}


vector<string> SplitStringByFontWidth(const wstring& wtext, int firstLength, int nextLength) {
    vector<string> result;
    string currentToken;
    int currentLength = 0;
    bool isFirstToken = true; 

    for (wchar_t ch : wtext) {
        int charWidth = IsCJKWideChar(ch) ? 2 : 1; 
        int maxLength = isFirstToken ? firstLength : nextLength;

        if (currentLength + charWidth > maxLength) {
            result.push_back(currentToken);
            currentToken.clear();
            currentLength = 0;
            isFirstToken = false; 
        }
        wstring tmp(1, ch);
        string charStr = ConvertUTF16ToUTF8(tmp);
        currentToken.append(charStr);
        currentLength += charWidth;
    }
    
    if (!currentToken.empty()) {
        result.push_back(currentToken);
    }

    return result;
}


vector<string> SplitStringByFontWidth(const string& text, int firstLength, int nextLength) {
    wstring wtext = ConvertUTF8ToUTF16(text); 
    return SplitStringByFontWidth(wtext, firstLength, nextLength);
}

wstring PreserveTrailingSpaces(const wstring& text)
{
	if (text.empty()) return text;

	std::wstring tempText = text;

	for (auto it = tempText.rbegin(); it != tempText.rend(); ++it)
	{
		if (*it == L'\0' || *it == L'\n') continue;
		else if (*it == L' ') {
			*it = L'_'; 
			break;
		}
		else break;
	}

	return tempText;
}

void replaceAll(string& str, const string& from, const string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}