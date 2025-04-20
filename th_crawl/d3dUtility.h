//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: d3dUtility.h
//
// 내용: 다이렉트X 유틸 선언 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __d3dUtilityH__
#define __d3dUtilityH__
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif


#include <string>
#include <sstream>
#include "common.h"
#include <dinput.h>
#include <mutex>
#include <queue>
#include <condition_variable>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "steam_api64")
#pragma comment(lib, "winmm")
#pragma comment(lib, "WS2_32")

#pragma comment (lib, "dxguid")
#pragma comment (lib, "dinput8")
//
// 상수
//
#pragma warning (disable:4244)
#pragma warning (disable:4800)
#pragma warning (disable:4091)
#pragma warning (disable:4018)
#pragma warning (disable:4996)



//
// 구조체
//

enum MOUSE_BUTTON {
	LEFT_CLICK,
	RIGHT_CLICK,
	MIDDLE_CLICK,
	MIDDLE_UP,
	MIDDLE_DOWN
};

struct Vertex{
	Vertex(){}
	Vertex(float x, float y, float z)
	{
		_x = x; _y = y; _z = z;
	}
	Vertex(float x, float y, float z, float u, float v)
	{
		_x = x; _y = y; _z = z; tu = u; tv = v;
	}
	float _x, _y, _z;
	float tu, tv;
};

enum MOUSE_KIND {
	MKIND_NONE,
	MKIND_MAP, //맵을 클릭
	MKIND_MAP_DESCRIPTION, //맵을 우클릭
	MKIND_ITEM, //아이템창을 클릭
	MKIND_ITEM_DESCRIPTION, //맵을 우클릭
	MKIND_PICK, //줍기
	MKIND_PICK_DESCRIPTION, //줍지않고 정보보기
	MKIND_SYSTEM, //시스템키
	MKIND_MENU, //특정 메뉴 클릭
	MKIND_LCLICK,
	MKIND_RCLICK,
	MKIND_MCLICK,
	MKIND_SCROLL_UP,
	MKIND_SCROLL_DOWN
};


enum SYSTEM_COMMAND_KIND {
	SYSCMD_AUTOTRAVEL = 0,
	SYSCMD_AUTOATTACK,
	SYSCMD_100REST,
	SYSCMD_MAGIC,
	SYSCMD_SKILL,
	SYSCMD_C_6,
	SYSCMD_C_7,
	SYSCMD_C_8,
	SYSCMD_C_9,
	SYSCMD_C_10,
	SYSCMD_SKILL_VIEW,
	SYSCMD_AUTOPICKUP,
	SYSCMD_AUTOTANMAC,
	SYSCMD_HELP,
	SYSCMD_QUIT,
	SYSCMD_C_16,
	SYSCMD_C_17,
	SYSCMD_C_18,
	SYSCMD_C_19,
	SYSCMD_C_20,
	SYSCMD_MAX
};


struct InputedKey {
    MSG key;
	MOUSE_KIND mouse = MKIND_NONE;
	int val1 = 0;
	int val2 = 0;

	InputedKey(){};
	InputedKey(MSG key):key(key){};
	InputedKey(MOUSE_KIND mouse,int val1,int val2):mouse(mouse),val1(val1),val2(val2){};
};

struct TimedKey {
    InputedKey key;
    std::chrono::steady_clock::time_point timestamp;
};

class KeyInputQueue {
public:
	void push(MSG key);
    void push(InputedKey key);
    InputedKey pop(int timeout_ms = 500); // timeout_ms: 허용된 최대 지연 시간
    bool try_pop(InputedKey& key);
    bool empty();

private:
    std::queue<TimedKey> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

extern std::unique_ptr<KeyInputQueue>  g_keyQueue;


extern ID3D11Device*           g_pd3dDevice;
extern ID3D11DeviceContext*    g_pImmediateContext;
extern IDXGISwapChain*         g_pSwapChain;
extern ID3D11RenderTargetView* g_pRenderTargetView;


namespace d3d
{
    bool InitD3D11(HINSTANCE hInstance, int width, int height, bool windowed);

	int EnterMsgLoop();

	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg, 
		WPARAM wParam,
		LPARAM lParam);

}



bool isClicked(MOUSE_BUTTON button);

#endif // __d3dUtilityH__