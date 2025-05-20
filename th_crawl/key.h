//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: key.h
//
// 내용: 키의 입력 처리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __KEY_H__
#define  __KEY_H__

#include "joypad.h"
#include <queue>
#include <chrono>
#include <string>

using namespace std;

struct InputedKey;

int waitkeyinput(InputedKey& key, bool direction_ = false, bool immedity_ = false, bool ablecursor = false);
int waitkeyinput(bool direction_ = false, bool immedity_ = false, bool ablecursor = false);
int MoreWait();
bool isKeyinput();
string getKeyboardInputString();

extern bool game_over;

#endif // __DISPLAY_H__