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

enum key_input_context
{
	KEY_INPUT_DEFAULT = 0,
	KEY_INPUT_MOVEMENT = 1,
	KEY_INPUT_LONG_MOVEMENT = 2,
	KEY_INPUT_MAP_SEARCH = 3,
	KEY_INPUT_PROJECTILE = 4,
	KEY_INPUT_DASH_MODIFIER = 5
};

int waitkeyinput(InputedKey& key, bool direction_ = false, bool immedity_ = false, bool ablecursor = false, bool command_context = false, bool raw_input = false, int movement_context = 0);
int waitkeyinput(bool direction_ = false, bool immedity_ = false, bool ablecursor = false, bool command_context = false, bool raw_input = false, int movement_context = 0);
int waitkeyinput_movement(InputedKey& key, bool ablecursor = false, bool allow_long_move = false, int input_context = KEY_INPUT_DEFAULT);
int waitkeyinput_movement(bool ablecursor = false, bool allow_long_move = false, int input_context = KEY_INPUT_DEFAULT);
void clearKey();
bool ynPromptSimple(LOCALIZATION_ENUM_KEY prompt_key, LOCALIZATION_ENUM_KEY canclePrompt_key, D3DCOLOR promptColor);
bool ynPrompt(LOCALIZATION_ENUM_KEY prompt_key, LOCALIZATION_ENUM_KEY canclePrompt_key, D3DCOLOR promptColor, bool temp, bool uppercase, bool loop, bool log);
bool ynPrompt(string prompt, string canclePrompt, D3DCOLOR promptColor, bool temp, bool isuppercase, bool loop, bool log);
int MoreWait();
bool isKeyinput();
string getKeyboardInputString(bool& cancle);

extern bool game_over;

#endif // __DISPLAY_H__
