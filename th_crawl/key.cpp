//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: key.cpp
//
// 내용: 키의 입력 처리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "const.h"
#include "display.h"
#include "d3dUtility.h"
#include "key.h"
#include "replay.h"
#include <conio.h>
#include <windows.h>
#include <string>

extern HWND hwnd;

bool game_over= false;
bool shift_check = false;
bool ctrl_check = false;
int replay_speed = 1;
extern std::atomic<bool> g_shutdownRequested;


void saveReplay_cpp();
std::unique_ptr<KeyInputQueue> g_keyQueue;

bool isKeyinput(bool ablecursor)
{
	while(1) {
		InputedKey inputedKey;
		if(g_keyQueue->try_pop(inputedKey)) {
			if(!ablecursor && inputedKey.mouse == MKIND_MAP_CURSOR) {
			}
			else {
				return true;
			}
		}
		else 
			return false;
	}
}

int waitkeyinput_inter(InputedKey& inputedKey, bool direction_, bool immedity_, bool ablecursor)
{
	if(immedity_)
	{
		if(isKeyinput(ablecursor))
			return 1;
		else
			return 0;
	}

	
	if(game_over)
		return VK_ESCAPE;
	while(!g_shutdownRequested) 
	{
		do {
			inputedKey = g_keyQueue->pop();
		} while(!ablecursor && inputedKey.mouse == MKIND_MAP_CURSOR);

		if(inputedKey.mouse == MKIND_NONE) {

			MSG msg = inputedKey.key;
			if(msg.message == WM_CHAR)
			{
				if(msg.wParam == 1) //A+컨트롤
				{
					//if(shift_check)
						return 0x8B; //0x8B은 컨트롤A
				}
				if(msg.wParam == 16) //p+컨트롤
				{
					//if(shift_check)
						return 0x88; //0x88은 컨트롤p
				}
				else if(msg.wParam == 17 ) //Q+컨트롤
				{
					//if(shift_check)
						return 0x89; //0x89은 컨트롤Q
				}
				else if(msg.wParam == 19) //S+컨트롤
				{
					//if(shift_check)
						return 0x8A; //0x8A은 컨트롤S
				}
				return msg.wParam; //엔터13 esc 27
			}
			else if(msg.message == WM_KEYDOWN)
			{
				switch(msg.wParam)
				{
				case '8':
					if(direction_ || shift_check) break; //원래는 if(direction_)만있었는데 뭔가 꼬임
					return (shift_check)?'*':'k';
				case VK_UP:
				case VK_NUMPAD8:
					if(direction_) return VK_UP;
					return (shift_check) ? 'K' : 'k';
					break;
				case '4':
					if(direction_ || shift_check) break;
					return (shift_check)?'$':'h';
				case VK_LEFT:
				case VK_NUMPAD4:	
					if(direction_) return VK_LEFT;
					return (shift_check) ? 'H' : 'h';
					break;
				case '6':
					if(direction_ || shift_check) break;
					return (shift_check)?'^':'l';
				case VK_RIGHT:
				case VK_NUMPAD6:	
					if(direction_) return VK_RIGHT;
					return (shift_check) ? 'L' : 'l';
					break;
				case '2':
					if(direction_ || shift_check) break;
					return (shift_check)?'@':'j';
				case VK_DOWN:
				case VK_NUMPAD2:	
					if(direction_) return VK_DOWN;
					return (shift_check) ? 'J' : 'j';
					break;			
				case '1':		
					if(direction_ || shift_check) break;
					return (shift_check)?'!':'b';
				case VK_NUMPAD1:	
				case 35:
					return (shift_check) ? 'B' : 'b';
				case '3':		
					if(direction_ || shift_check) break;
					return (shift_check)?'#':'n';
				case 34:
					if(direction_) return 34;
				case VK_NUMPAD3:	
					return (shift_check) ? 'N' : 'n';
				case '7':	
					if(direction_ || shift_check) break;
					return (shift_check)?'&':'y';
				case VK_NUMPAD7:	
				case 36:
					return (shift_check) ? 'Y' : 'y';
				case '9':	
					if(direction_ || shift_check) break;
					return (shift_check)?'(':'u';	
				case 33:
					if(direction_) return 33;
				case VK_NUMPAD9:	
					return (shift_check) ? 'U' : 'u';
				default:
					break;
				}			
				if(msg.wParam == VK_SHIFT)
					shift_check = true;
				if(msg.wParam == VK_CONTROL)
					ctrl_check = true;
	
			}
			else if(msg.message == WM_KEYUP)
			{
				if(msg.wParam == VK_SHIFT)
					shift_check = false;
				if(msg.wParam == VK_CONTROL)
					ctrl_check = false;
			}
			else if(msg.message == WM_KILLFOCUS) {
				shift_check = false;
				ctrl_check = false;
			}
		} else {
			return -1; //키보드 입력
		}
	}
	if(g_shutdownRequested)
	{
		throw 0;
	}
	return 0;
}

int waitkeyinput(bool direction_, bool immedity_, bool ablecursor) {
	InputedKey temp;
	return waitkeyinput(temp, direction_,  immedity_, ablecursor);
}



std::string utf8_from_codepoint(int codepoint) {
    std::string result;
    if (codepoint <= 0x7F) {
        // 1바이트 UTF-8 (ASCII)
        result.push_back(static_cast<char>(codepoint));
    } else if (codepoint <= 0x7FF) {
        // 2바이트 UTF-8
        result.push_back(static_cast<char>(0xC0 | ((codepoint >> 6) & 0x1F)));
        result.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
    } else if (codepoint <= 0xFFFF) {
        // 3바이트 UTF-8
        result.push_back(static_cast<char>(0xE0 | ((codepoint >> 12) & 0x0F)));
        result.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
        result.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
    } else if (codepoint <= 0x10FFFF) {
        // 4바이트 UTF-8
        result.push_back(static_cast<char>(0xF0 | ((codepoint >> 18) & 0x07)));
        result.push_back(static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F)));
        result.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
        result.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
    }
    return result;
}


std::string inputedkey_to_string(int key_, const InputedKey& input) {
    std::ostringstream oss;

    if (key_ == -1) {
        // 마우스 입력
        oss << "Mouse["
            << static_cast<int>(input.mouse) << "]("
            << input.val1 << ", "
            << input.val2 << ")";
    } else {
        // 키보드 입력 (key_는 int이므로 유니코드로 취급)
        oss << "Key[" << key_;

        std::string utf8Char = utf8_from_codepoint(key_);
        if (!utf8Char.empty()) {  // 변환 결과가 있으면
            oss << " ('" << utf8Char << "')";
        }
        oss << "]";
    }

    return oss.str();
}


int waitkeyinput(InputedKey& key, bool direction_, bool immedity_, bool ablecursor)
{
	if(ReplayClass.auto_key == false)
	{
		DWORD time_ = timeGetTime();

		int return_ = waitkeyinput_inter(key, direction_,immedity_, ablecursor);
	
		DWORD time2_ = timeGetTime();

		ReplayClass.SaveReplayInput(immedity_?0:(time2_-time_) , return_, key);
		LOG_KEY_INPUT(inputedkey_to_string(return_,key));

		return return_;
	}
	else
	{
		DWORD delay_;
		int return_;
		InputedKey inputedkey;
		MSG msg;
		bool get_ = g_keyQueue->try_pop(inputedkey);

		if(get_ == true)
		{
			if(inputedkey.mouse == MKIND_NONE) {
				msg = inputedkey.key;
				switch(msg.wParam)
				{
				case 'x':
					replay_speed = 1;
					break;
				case 'c':
					replay_speed = 0;
					break;
				case 'z':
					while(!g_shutdownRequested)
					{
						get_ = g_keyQueue->try_pop(inputedkey);
	
						if(get_ == true) {							
							if(inputedkey.mouse == MKIND_NONE) {
								msg = inputedkey.key;
								if(msg.message == WM_CHAR)
								{
									if(msg.wParam == 'z' || msg.wParam == 'x' || msg.wParam == 'c')
									{
										if (msg.wParam == 'x')
											replay_speed = 1;
										else if (msg.wParam == 'c')
											replay_speed = 0;
										break;
									}
								}
							}

						}
						Sleep(1);
					}
					break;
				}
			}
		}

		if(game_over || g_shutdownRequested)
		{
			throw 0;
		}
		if(ReplayClass.LoadReplayInput(&delay_,&return_, key))
		{
			if(delay_>0)
			{
				for(int i = 0; i <(replay_speed==1?min(1000,(int)delay_):0); i++)
					Sleep(1);
			}
			LOG_KEY_INPUT(inputedkey_to_string(return_,key));

			return return_;
		}
		else
			return 0;
	}
}

void EraseLastUTF8Char(string& s) {
    if (s.empty()) return;
    size_t i = s.size() - 1;
    while (i > 0 && (s[i] & 0xC0) == 0x80) --i;
    s.erase(i);
}


string GetClipboardTextUTF8() {
    if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) return "";
    if (!OpenClipboard(nullptr)) return "";

    string result;
    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (hData) {
        wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
        if (pszText) {
            wstring wideText(pszText);
            GlobalUnlock(hData);
            result = ConvertUTF16ToUTF8(wideText);
        }
    }
    CloseClipboard();
    return result;
}

string getKeyboardInputString() {
    string temp;

    while (true) {
        InputedKey inputed;
        int input_ = waitkeyinput(inputed);


		if(input_ == -1) {
			//무시
		}
        else if (input_ == VK_RETURN) {
			deletelog();
			printlog(temp, false, false, false, CL_normal);
            return temp;
        }
        else if (input_ == VK_BACK) {
            EraseLastUTF8Char(temp);
        }
        else {
            wchar_t wc = static_cast<wchar_t>(input_);
            if (wc >= 1 && wc <= 26) continue; // Ctrl + 문자 무시
            temp += ConvertUTF16ToUTF8(wstring(1, wc));
        }
        // else if (inputed.key.message == WM_KEYDOWN) { 리플레이에서 쓸 수 없음
        //     if (inputed.key.wParam == 'V' && ctrl_check) {
        //         string clipText = GetClipboardTextUTF8();
        //         temp += clipText;
        //     }
        // }
        deletelog();
        printlog(temp, false, false, true, CL_normal);
    }
}

void KeyInputQueue::push(InputedKey key) {
	std::unique_lock<std::mutex> lock(mutex_);
	queue_.push({ key, std::chrono::steady_clock::now() });
	cv_.notify_one();
}

void KeyInputQueue::push(MSG key) {
	push(InputedKey(key));
}

InputedKey KeyInputQueue::pop(int timeout_ms) {
	std::unique_lock<std::mutex> lock(mutex_);

	while (true) {
		while (queue_.empty()) {
			cv_.wait(lock);
		}

		auto now = std::chrono::steady_clock::now();

		while (!queue_.empty()) {
			TimedKey tk = queue_.front();
			if (std::chrono::duration_cast<std::chrono::milliseconds>(now - tk.timestamp).count() <= timeout_ms) {
				queue_.pop();
				return tk.key;
			}
			else {
				queue_.pop();
			}
		}
	}
}

bool KeyInputQueue::try_pop(InputedKey& key) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) return false;

    key = queue_.front().key;
    queue_.pop();
    return true;
}

bool KeyInputQueue::empty() {
	std::lock_guard<std::mutex> lock(mutex_);
	return queue_.empty();
}


int MoreWait()
{
	printlog("----------" + LocalzationManager::locString(LOC_SYSTEM_MORE) + "----------",true,false,true,CL_normal);
	while(1)
	{
		InputedKey inputedKey;
		int select = waitkeyinput(inputedKey);
		//마우스도 지정
		if(select==VK_ESCAPE || select==VK_RETURN || 
		select== GVK_BUTTON_A ||
		select== GVK_BUTTON_A_LONG ||
		select== GVK_BUTTON_B || 
		select== GVK_BUTTON_B_LONG || select == -1) 
		{
			break;
		}
	}
	deletelog();
	return true;
}