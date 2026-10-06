
//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: d3dUtility.cpp
//
// 내용: 다이렉트X 유틸 정의 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "environment.h"
#include "replay.h"
#include "steam_api.h"
#include "option_manager.h"
#include "joypad.h"
#include "key.h"
#include "soundmanager.h"
#include "keyconfig.h"
#include <wrl/client.h>
#include <imm.h>
#include <XInput.h>



using namespace std::chrono;

bool joypadUtil::usingPad = false;
steady_clock::time_point g_button_press_time[6] = {};
SHORT g_gamepad_xlx[2];
SHORT g_gamepad_xly[2];
boolean g_gamepad_on[2];
bool g_dash_modifier_active = false;
bool g_dash_modifier_used = false;
bool g_prev_dash_modifier_active = false;
char g_prev_dash_direction = 0;
steady_clock::time_point g_repeat_start_time[6] = {};
steady_clock::time_point g_last_repeat_emit[6] = {};
WORD prev_buttons;
constexpr WORD BUTTON_MASKS[6] = {
    XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_Y, XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER
};
constexpr wchar_t SHORT_KEYS[6] = {
    GVK_BUTTON_A, GVK_BUTTON_B, GVK_BUTTON_X, GVK_BUTTON_Y, GVK_LEFT_BUMPER, GVK_RIGHT_BUMPER
};
constexpr wchar_t LONG_KEYS[6] = {
    GVK_BUTTON_A_LONG, GVK_BUTTON_B_LONG, GVK_BUTTON_X_LONG, GVK_BUTTON_Y_LONG, GVK_LEFT_BUMPER, GVK_RIGHT_BUMPER
};
// 눌렀다 뗐을 때 500ms 이상이면 롱프레스
constexpr int LONG_PRESS_THRESHOLD_MS = 500;
constexpr int REPEAT_INTERVAL_MS = 50;        // 반복 주기
constexpr bool ENABLE_REPEAT_FOR[6] = {
    false,  // A
    false, // B
    false, // X
    false, // Y
    true,  // LB
    true  // RB
};

static char GamepadDirectionFromStick(SHORT x, SHORT y)
{
	if(abs(x) <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && abs(y) <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return 0;
	float angle = atan2f(static_cast<float>(y), static_cast<float>(x));
	if(angle >= -3.14159f * 7 / 8 && angle < -3.14159f * 5 / 8) return 'b';
	if(angle >= -3.14159f * 5 / 8 && angle < -3.14159f * 3 / 8) return 'j';
	if(angle >= -3.14159f * 3 / 8 && angle < -3.14159f * 1 / 8) return 'n';
	if(angle >= -3.14159f * 1 / 8 && angle <  3.14159f * 1 / 8) return 'l';
	if(angle >=  3.14159f * 1 / 8 && angle <  3.14159f * 3 / 8) return 'u';
	if(angle >=  3.14159f * 3 / 8 && angle <  3.14159f * 5 / 8) return 'k';
	if(angle >=  3.14159f * 5 / 8 && angle <  3.14159f * 7 / 8) return 'y';
	return 'h';
}

static char GamepadDirectionFromDpad(WORD buttons)
{
	bool up = (buttons & XINPUT_GAMEPAD_DPAD_UP) != 0;
	bool down = (buttons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
	bool left = (buttons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
	bool right = (buttons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
	if(up == down) up = down = false;
	if(left == right) left = right = false;
	if(up && left) return 'y';
	if(up && right) return 'u';
	if(down && left) return 'b';
	if(down && right) return 'n';
	if(up) return 'k';
	if(down) return 'j';
	if(left) return 'h';
	if(right) return 'l';
	return 0;
}

static char DashDirection(char direction)
{
	switch(direction)
	{
	case 'k': return 'K'; case 'j': return 'J';
	case 'h': return 'H'; case 'l': return 'L';
	case 'b': return 'B'; case 'n': return 'N';
	case 'y': return 'Y'; case 'u': return 'U';
	default: return 0;
	}
}

static void PushGamepadDirection(char direction, bool dash)
{
	char key = dash ? DashDirection(direction) : direction;
	if(!key)
		return;
	MSG fake_msg = {};
	fake_msg.message = GAMEPAD_DIRECTION_MESSAGE;
	fake_msg.wParam = key;
	g_keyQueue->push(fake_msg);
}

static bool IsDashModifierPhysicalKey(int short_key, int long_key = 0)
{
	return keybind_mg.is_gamepad_dash_key(short_key) ||
		(long_key != 0 && keybind_mg.is_gamepad_dash_key(long_key));
}

static bool IsDashModifierDown(const XINPUT_STATE& state)
{
	WORD buttons = state.Gamepad.wButtons;
	for(int i = 0; i < 6; ++i)
		if(IsDashModifierPhysicalKey(SHORT_KEYS[i], LONG_KEYS[i]) && (buttons & BUTTON_MASKS[i]))
			return true;
	if(IsDashModifierPhysicalKey(GVK_LT) && state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return true;
	if(IsDashModifierPhysicalKey(GVK_RT) && state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return true;
	if(IsDashModifierPhysicalKey(GVK_BACK) && (buttons & XINPUT_GAMEPAD_BACK))
		return true;
	if(IsDashModifierPhysicalKey(GVK_START) && (buttons & XINPUT_GAMEPAD_START))
		return true;
	return false;
}

bool joypadUtil::isUsingPad() {
    if(option_mg.getInputPrompt() == 0) {
        return usingPad;
    }
    return option_mg.getInputPrompt()==2?true:false;
}
void joypadUtil::initJoypad() {
    usingPad = isGamepadConnected();
}
bool joypadUtil::isGamepadConnected() {
    // XInput 사용 예시
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    return (XInputGetState(0, &state) == ERROR_SUCCESS);
}

std::string joypadUtil::get(const std::string& kbKey, wchar_t gamepadKey, PromptType promptType) {
    if (!isUsingPad())
        return kbKey;

    gamepadKey = static_cast<wchar_t>(keybind_mg.physical_gamepad_key(gamepadKey));
	std::string result = getRawGamepad(gamepadKey);
	return result.empty() ? kbKey : result;
}

std::string joypadUtil::getRawGamepad(wchar_t gamepadKey) {
    GamepadType type = steam_mg.getCurrentGamepadType();

    switch (gamepadKey) {
    case GVK_BUTTON_A:
    case GVK_BUTTON_A_LONG:
    {
		string key_ = type == GAMEPAD_PS ? "[x]" : type == GAMEPAD_NINTENDO ? "[B]" : "[A]";
        return gamepadKey==GVK_BUTTON_A_LONG?(LocalzationManager::formatString(LOC_SYSTEM_JOYPAD_HOLD,PlaceHolderHelper(key_))):key_;
    }
    case GVK_BUTTON_B:
    case GVK_BUTTON_B_LONG:
    {
		string key_ = type == GAMEPAD_PS ? "[○]" : type == GAMEPAD_NINTENDO ? "[A]" : "[B]";
        return gamepadKey==GVK_BUTTON_B_LONG?(LocalzationManager::formatString(LOC_SYSTEM_JOYPAD_HOLD,PlaceHolderHelper(key_))):key_;
    }
    case GVK_BUTTON_X:
    case GVK_BUTTON_X_LONG:
    {
		string key_ = type == GAMEPAD_PS ? "[□]" : type == GAMEPAD_NINTENDO ? "[Y]" : "[X]";
        return gamepadKey==GVK_BUTTON_X_LONG?(LocalzationManager::formatString(LOC_SYSTEM_JOYPAD_HOLD,PlaceHolderHelper(key_))):key_;
    }
    case GVK_BUTTON_Y:
    case GVK_BUTTON_Y_LONG:
    {
		string key_ = type == GAMEPAD_PS ? "[△]" : type == GAMEPAD_NINTENDO ? "[X]" : "[Y]";
        return gamepadKey==GVK_BUTTON_Y_LONG?(LocalzationManager::formatString(LOC_SYSTEM_JOYPAD_HOLD,PlaceHolderHelper(key_))):key_;
    }
    case GVK_LEFT_BUMPER:
        return (type == GAMEPAD_PS) ? "[L1]" : "[LB]";

    case GVK_RIGHT_BUMPER:
        return (type == GAMEPAD_PS) ? "[R1]" : "[RB]";

    case GVK_LT:
        return (type == GAMEPAD_PS) ? "[L2]" : "[LT]";

    case GVK_RT:
        return (type == GAMEPAD_PS) ? "[R2]" : "[RT]";

    case GVK_BACK:
        return (type == GAMEPAD_PS) ? "[Share]" : "[Back]";

    case GVK_START:
        return (type == GAMEPAD_PS) ? "[Options]" : "[Start]";

    default:
		return "";
    }
}

void ClickKey(wchar_t key)
{
	if(keybind_mg.gamepad_command_for_physical(key) == GVK_BUTTON_A) {
		if(g_gamepad_on[0]) {
			if(g_dash_modifier_used)
				return;
			if(g_dash_modifier_active)
			{
				PushGamepadDirection(GamepadDirectionFromStick(g_gamepad_xlx[0], g_gamepad_xly[0]), true);
				g_dash_modifier_used = true;
				return;
			}
			float angle = atan2f((float)g_gamepad_xly[0], (float)g_gamepad_xlx[0]); // 라디안: -π ~ π

			// 8방향 분할
			char vi_key = 0;
			if (angle >= -3.14159f * 7/8 && angle < -3.14159f * 5/8)       vi_key = 'b'; // 좌상
			else if (angle >= -3.14159f * 5/8 && angle < -3.14159f * 3/8)  vi_key = 'j'; // 상
			else if (angle >= -3.14159f * 3/8 && angle < -3.14159f * 1/8)  vi_key = 'n'; // 우상
			else if (angle >= -3.14159f * 1/8 && angle <  3.14159f * 1/8)  vi_key = 'l'; // 우
			else if (angle >=  3.14159f * 1/8 && angle <  3.14159f * 3/8)  vi_key = 'u'; // 우하
			else if (angle >=  3.14159f * 3/8 && angle <  3.14159f * 5/8)  vi_key = 'k'; // 하
			else if (angle >=  3.14159f * 5/8 && angle <  3.14159f * 7/8)  vi_key = 'y'; // 좌하
			else                                                         vi_key = 'h'; // 좌

			if (vi_key) {
				MSG fake_msg = {};
				fake_msg.message = GAMEPAD_DIRECTION_MESSAGE;
				fake_msg.wParam = vi_key;
				g_keyQueue->push(fake_msg);
			}
		} else {
            MSG fake_msg = {};
            fake_msg.message = WM_CHAR;
            fake_msg.wParam = key;
            g_keyQueue->push(fake_msg);
        }
	} 
	else {
		MSG fake_msg = {};
		fake_msg.message = WM_CHAR;
		fake_msg.wParam = key;
		g_keyQueue->push(fake_msg);
	}
}

static bool prev_lt = false, prev_rt = false;

void ProcessGamepadInput()
{
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    if (XInputGetState(0, &state) == ERROR_SUCCESS)
    {
        WORD buttons = state.Gamepad.wButtons;

        // 아날로그 스틱 (예시: 좌측)
        g_gamepad_xlx[0] = state.Gamepad.sThumbLX;
        g_gamepad_xly[0] = state.Gamepad.sThumbLY;
        if (abs(g_gamepad_xlx[0]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || abs(g_gamepad_xly[0]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			g_gamepad_on[0] = true;
		else 
			g_gamepad_on[0] = false;
        g_gamepad_xlx[1] = state.Gamepad.sThumbRX;
        g_gamepad_xly[1] = state.Gamepad.sThumbRY;
        if (abs(g_gamepad_xlx[1]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || abs(g_gamepad_xly[1]) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			g_gamepad_on[1] = true;
		else 
			g_gamepad_on[1] = false;

		g_dash_modifier_active = IsDashModifierDown(state);
		char dash_direction = GamepadDirectionFromStick(g_gamepad_xlx[0], g_gamepad_xly[0]);
		if(!dash_direction)
			dash_direction = GamepadDirectionFromDpad(buttons);
		if(g_dash_modifier_active && dash_direction &&
			(!g_prev_dash_modifier_active || dash_direction != g_prev_dash_direction))
		{
			PushGamepadDirection(dash_direction, true);
			g_dash_modifier_used = true;
		}

        // ABXY 버튼 처리 (짧게/길게)
        for (int i = 0; i < 6; ++i) {
            bool now_pressed = (buttons & BUTTON_MASKS[i]);
            bool was_pressed = (prev_buttons & BUTTON_MASKS[i]);
			bool dash_modifier_button = IsDashModifierPhysicalKey(SHORT_KEYS[i], LONG_KEYS[i]);

			if (now_pressed && was_pressed && g_button_press_time[i].time_since_epoch().count()!= 0) {
				auto now = steady_clock::now();
				auto held_duration = duration_cast<milliseconds>(now - g_button_press_time[i]).count();
				
				// 최초 반복 조건 충족
				if (held_duration >= LONG_PRESS_THRESHOLD_MS && !(dash_modifier_button && g_dash_modifier_used)) {
                    if(ENABLE_REPEAT_FOR[i] || (i == 0 && g_gamepad_on[0]) ) {
                        //반복입력 가능한 키는 스틱+a(특수처리) 와 l1, r1
                        auto since_last_emit = duration_cast<milliseconds>(now - g_last_repeat_emit[i]).count();
                        if (since_last_emit >= REPEAT_INTERVAL_MS) {
                            g_last_repeat_emit[i] = now;
                            ClickKey(SHORT_KEYS[i]);
                        }
                    } else {
                        ClickKey(LONG_KEYS[i]);
                        g_button_press_time[i] = steady_clock::time_point(); // 초기화
                    }
				}
			}


            if (now_pressed && !was_pressed) {
                // 버튼을 처음 누름 → 시간 기록
                g_button_press_time[i] = steady_clock::now();
                g_last_repeat_emit[i] = steady_clock::now();
            }
            else if (!now_pressed && was_pressed) {
                // 버튼을 뗌 → 경과 시간 계산
                auto now = steady_clock::now();
                auto duration = duration_cast<milliseconds>(now - g_button_press_time[i]).count();
                g_button_press_time[i] = steady_clock::time_point();
                g_last_repeat_emit[i] = steady_clock::time_point();
                if(duration < LONG_PRESS_THRESHOLD_MS && !(dash_modifier_button && g_dash_modifier_used)) {
                    ClickKey(SHORT_KEYS[i]);
                }
            }
        }

        if (!g_dash_modifier_active && (buttons & XINPUT_GAMEPAD_DPAD_UP) && !(prev_buttons & XINPUT_GAMEPAD_DPAD_UP)) {
			MSG fake_msg = {};
			fake_msg.message = GAMEPAD_DPAD_MESSAGE;
			fake_msg.wParam = VK_UP;
			g_keyQueue->push(fake_msg);
		}

        if (!g_dash_modifier_active && (buttons & XINPUT_GAMEPAD_DPAD_DOWN) && !(prev_buttons & XINPUT_GAMEPAD_DPAD_DOWN)) {
			MSG fake_msg = {};
			fake_msg.message = GAMEPAD_DPAD_MESSAGE;
			fake_msg.wParam = VK_DOWN;
			g_keyQueue->push(fake_msg);
		}

        if (!g_dash_modifier_active && (buttons & XINPUT_GAMEPAD_DPAD_LEFT) && !(prev_buttons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			MSG fake_msg = {};
			fake_msg.message = GAMEPAD_DPAD_MESSAGE;
			fake_msg.wParam = VK_LEFT;
			g_keyQueue->push(fake_msg);
		}

        if (!g_dash_modifier_active && (buttons & XINPUT_GAMEPAD_DPAD_RIGHT) && !(prev_buttons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			MSG fake_msg = {};
			fake_msg.message = GAMEPAD_DPAD_MESSAGE;
			fake_msg.wParam = VK_RIGHT;
			g_keyQueue->push(fake_msg);
		}
		
        bool now_lt = state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
        if (now_lt && !prev_lt && !(g_dash_modifier_active && IsDashModifierPhysicalKey(GVK_LT))) {
            MSG fake_msg = {};
            fake_msg.message = WM_CHAR;
            fake_msg.wParam = GVK_LT;
            g_keyQueue->push(fake_msg);
        }
        prev_lt = now_lt;

        bool now_rt = state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
        if (now_rt && !prev_rt && !(g_dash_modifier_active && IsDashModifierPhysicalKey(GVK_RT))) {
            MSG fake_msg = {};
            fake_msg.message = WM_CHAR;
            fake_msg.wParam = GVK_RT;
            g_keyQueue->push(fake_msg);
        }
        prev_rt = now_rt;
        
		g_prev_dash_modifier_active = g_dash_modifier_active;
		g_prev_dash_direction = g_dash_modifier_active ? dash_direction : 0;
		prev_buttons = buttons;
		if(!g_dash_modifier_active)
			g_dash_modifier_used = false;
    }
}
