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
#include <imm.h>

#pragma comment(lib, "imm32.lib")

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

enum GamepadVirtualKey : wchar_t
{
    GVK_BUTTON_A       = 0xE001,
    GVK_BUTTON_A_LONG  = 0xE002,
    GVK_BUTTON_B       = 0xE003,
    GVK_BUTTON_B_LONG  = 0xE004,
    GVK_BUTTON_X       = 0xE005,
    GVK_BUTTON_X_LONG  = 0xE006,
    GVK_BUTTON_Y       = 0xE007,
    GVK_BUTTON_X_LONG  = 0xE008,
    GVK_LEFT_BUMPER    = 0xE009,
    GVK_RIGHT_BUMPER   = 0xE00A,
    GVK_LT             = 0xE00B, // Left Trigger
    GVK_RT             = 0xE00C, // Right Trigger
    GVK_BACK           = 0xE00D,
    GVK_START          = 0xE00E
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
	MKIND_ITEM_DESCRIPTION, //아이템을 우클릭
	MKIND_PICK, //줍기
	MKIND_PICK_DESCRIPTION, //줍지않고 정보보기
	MKIND_SYSTEM, //시스템키
	MKIND_MENU, //특정 메뉴 클릭
	MKIND_LCLICK,
	MKIND_RCLICK,
	MKIND_MCLICK,
	MKIND_SCROLL_UP,
	MKIND_SCROLL_DOWN,
	MKIND_MAP_CURSOR //맵위에 마우스를 올린다(리플레이에서 저장하면 안되는 정보.)
};


enum SYSTEM_COMMAND_KIND {
	SYSCMD_AUTOTRAVEL = 0,
	SYSCMD_AUTOATTACK,
	SYSCMD_100REST,
	SYSCMD_MAGIC,
	SYSCMD_SKILL,
	SYSCMD_SHOUT,
	SYSCMD_DOOR_OPENCLOSE,
	SYSCMD_PRAY,
	SYSCMD_MORE_ITEM,
	SYSCMD_C_10,
	SYSCMD_AUTOPICKUP,
	SYSCMD_AUTOTANMAC,
	SYSCMD_WIDE_SEARCH,
	SYSCMD_SKILL_VIEW,
	SYSCMD_MORE_VIEW,
	SYSCMD_HELP,
	SYSCMD_QUIT,
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

	bool isLeftClick() {
		return (mouse == MKIND_MAP || mouse==MKIND_ITEM || mouse==MKIND_PICK || mouse==MKIND_SYSTEM || mouse==MKIND_LCLICK || mouse==MKIND_MENU);
	}
	bool isRightClick() {
		return (mouse == MKIND_MAP_DESCRIPTION || mouse==MKIND_ITEM_DESCRIPTION || mouse==MKIND_PICK_DESCRIPTION || mouse==MKIND_RCLICK);
	}
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