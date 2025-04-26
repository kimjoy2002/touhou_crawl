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


extern HWND hwnd;

bool game_over= false;
bool shift_check = false;
bool ctrl_check = false;
int replay_speed = 1;
extern std::atomic<bool> g_shutdownRequested;


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
		throw 0;
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

int waitkeyinput(InputedKey& key, bool direction_, bool immedity_, bool ablecursor)
{
	if(ReplayClass.auto_key == false)
	{
		DWORD time_ = timeGetTime();

		int return_ = waitkeyinput_inter(key, direction_,immedity_, ablecursor);
	
		DWORD time2_ = timeGetTime();

		ReplayClass.SaveReplayInput(immedity_?0:(time2_-time_) , return_, key);

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

			return return_;
		}
		else
			return 0;
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
		if(select==VK_ESCAPE || select==VK_RETURN || select == -1) 
		{
			break;
		}
	}
	deletelog();
	return true;
}