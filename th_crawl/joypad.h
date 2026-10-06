

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: joypad.h
//
// 내용: 조이패드 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __joypad_H__
#define __joypad_H__

#include <iostream>

enum GamepadType {
    GAMEPAD_XBOX,
    GAMEPAD_PS,
    GAMEPAD_NINTENDO,
    GAMEPAD_UNKNOWN
};

enum PromptType {
    PROMPT_NONE,
    PROMPT_YN
};

enum GamepadVirtualKey : wchar_t
{
    GVK_BUTTON_A       = 0xE001,
    GVK_BUTTON_A_LONG  = 0xE002,
    GVK_BUTTON_B       = 0xE003,
    GVK_BUTTON_B_LONG  = 0xE004,
    GVK_BUTTON_X       = 0xE005,
    GVK_BUTTON_X_LONG  = 0xE006,
    GVK_BUTTON_Y       = 0xE007,
    GVK_BUTTON_Y_LONG  = 0xE008,
    GVK_LEFT_BUMPER    = 0xE009,
    GVK_RIGHT_BUMPER   = 0xE00A,
    GVK_LT             = 0xE00B, // Left Trigger
    GVK_RT             = 0xE00C, // Right Trigger
    GVK_BACK           = 0xE00D,
    GVK_START          = 0xE00E
};

// 아날로그 스틱 이동은 사용자가 바꾼 vi 이동키와 구분되어야 한다.
constexpr unsigned int GAMEPAD_DIRECTION_MESSAGE = 0x8037;
constexpr unsigned int GAMEPAD_DPAD_MESSAGE = 0x8038;


class joypadUtil {
    static bool isGamepadConnected();
public:
    static bool usingPad;
    static bool isUsingPad();
    static void initJoypad();
    static std::string get(const std::string& kbKey, wchar_t gamepadKey, PromptType promptType = PROMPT_NONE);
	static std::string getRawGamepad(wchar_t gamepadKey);
};
void ProcessGamepadInput();

#endif // __joypad_H__
