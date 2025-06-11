
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
#include <wrl/client.h>
#include <imm.h>
#include <XInput.h>



using namespace std::chrono;

bool joypadUtil::usingPad = false;
steady_clock::time_point g_button_press_time[6] = {};
SHORT g_gamepad_xlx[2];
SHORT g_gamepad_xly[2];
boolean g_gamepad_on[2];
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
    if (!usingPad)
        return kbKey;

    GamepadType type = steam_mg.getCurrentGamepadType();

    switch (gamepadKey) {
    case GVK_BUTTON_A:
    case GVK_BUTTON_A_LONG:
    {
        string key_;
        switch (type) {
        case GAMEPAD_PS: key_ = "[x]";
        case GAMEPAD_NINTENDO: key_ = "[B]";
        default: key_ = "[A]";
        }
        return gamepadKey==GVK_BUTTON_A_LONG?(LocalzationManager::formatString(LOC_SYSTEM_JOYPAD_HOLD,PlaceHolderHelper(key_))):key_;
    }
    case GVK_BUTTON_B:
    case GVK_BUTTON_B_LONG:
    {
        string key_;
        switch (type) {
        case GAMEPAD_PS: key_ = "[○]";
        case GAMEPAD_NINTENDO: key_ = "[A]";
        default: key_ = "[B]";
        }
        return gamepadKey==GVK_BUTTON_B_LONG?(LocalzationManager::formatString(LOC_SYSTEM_JOYPAD_HOLD,PlaceHolderHelper(key_))):key_;
    }
    case GVK_BUTTON_X:
    case GVK_BUTTON_X_LONG:
    {
        string key_;
        switch (type) {
        case GAMEPAD_PS: key_ = "[□]";
        case GAMEPAD_NINTENDO: key_ = "[Y]";
        default: key_ = "[X]";
        }
        return gamepadKey==GVK_BUTTON_X_LONG?(LocalzationManager::formatString(LOC_SYSTEM_JOYPAD_HOLD,PlaceHolderHelper(key_))):key_;
    }
    case GVK_BUTTON_Y:
    case GVK_BUTTON_Y_LONG:
    {
        string key_;
        switch (type) {
        case GAMEPAD_PS: key_ = "[△]";
        case GAMEPAD_NINTENDO: key_ = "[X]";
        default: key_ = "[Y]";
        }
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
        return kbKey;
    }
}

void ClickKey(wchar_t key)
{
	if(key == GVK_BUTTON_A) {
		if(g_gamepad_on[0]) {
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
				fake_msg.message = WM_CHAR;
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

        // ABXY 버튼 처리 (짧게/길게)
        for (int i = 0; i < 6; ++i) {
            bool now_pressed = (buttons & BUTTON_MASKS[i]);
            bool was_pressed = (prev_buttons & BUTTON_MASKS[i]);

			if (now_pressed && was_pressed && g_button_press_time[i].time_since_epoch().count()!= 0) {
				auto now = steady_clock::now();
				auto held_duration = duration_cast<milliseconds>(now - g_button_press_time[i]).count();
				
				// 최초 반복 조건 충족
				if (held_duration >= LONG_PRESS_THRESHOLD_MS) {
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
                if(duration < LONG_PRESS_THRESHOLD_MS) {
                    ClickKey(SHORT_KEYS[i]);
                }
            }
        }

        if (buttons & XINPUT_GAMEPAD_DPAD_UP && !(prev_buttons & XINPUT_GAMEPAD_DPAD_UP)) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = VK_UP;
			g_keyQueue->push(fake_msg);
		}

        if (buttons & XINPUT_GAMEPAD_DPAD_DOWN && !(prev_buttons & XINPUT_GAMEPAD_DPAD_DOWN)) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = VK_DOWN;
			g_keyQueue->push(fake_msg);
		}

        if (buttons & XINPUT_GAMEPAD_DPAD_LEFT && !(prev_buttons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = VK_LEFT;
			g_keyQueue->push(fake_msg);
		}

        if (buttons & XINPUT_GAMEPAD_DPAD_RIGHT && !(prev_buttons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			MSG fake_msg = {};
			fake_msg.message = WM_CHAR;
			fake_msg.wParam = VK_RIGHT;
			g_keyQueue->push(fake_msg);
		}
		
        bool now_lt = state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
        if (now_lt && !prev_lt) {
            MSG fake_msg = {};
            fake_msg.message = WM_CHAR;
            fake_msg.wParam = GVK_LT;
            g_keyQueue->push(fake_msg);
        }
        prev_lt = now_lt;

        bool now_rt = state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
        if (now_rt && !prev_rt) {
            MSG fake_msg = {};
            fake_msg.message = WM_CHAR;
            fake_msg.wParam = GVK_RT;
            g_keyQueue->push(fake_msg);
        }
        prev_rt = now_rt;
        
		prev_buttons = buttons;
    }
}
