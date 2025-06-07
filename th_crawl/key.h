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
#include "common.h"
#include "enumMapBuilder.h"
#include <queue>
#include <chrono>
#include <string>

using namespace std;

struct InputedKey;

int waitkeyinput(InputedKey& key, bool direction_ = false, bool immedity_ = false, bool ablecursor = false);
int waitkeyinput(bool direction_ = false, bool immedity_ = false, bool ablecursor = false);
bool ynPromptSimple(LOCALIZATION_ENUM_KEY prompt_key, LOCALIZATION_ENUM_KEY canclePrompt_key, D3DCOLOR promptColor);
bool ynPrompt(LOCALIZATION_ENUM_KEY prompt_key, LOCALIZATION_ENUM_KEY canclePrompt_key, D3DCOLOR promptColor, bool temp, bool uppercase, bool loop, bool log);
bool ynPrompt(string prompt, string canclePrompt, D3DCOLOR promptColor, bool temp, bool isuppercase, bool loop, bool log);
int MoreWait();
bool isKeyinput();
string getKeyboardInputString();

extern bool game_over;

#endif // __DISPLAY_H__