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

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")
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

const int W_WIDTH = WindowWidth;
const int W_HEIGHT = WindowHeight;


//
// 구조체
//

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





namespace d3d
{
	bool InitD3D(
		HINSTANCE hInstance,       // [in] Application instance.
		int width, int height,     // [in] Backbuffer dimensions.
		bool windowed,             // [in] Windowed (true)or full screen (false).
		D3DDEVTYPE deviceType,     // [in] HAL or REF
		IDirect3DDevice9** device);// [out]The created device.

	int EnterMsgLoop();

	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg, 
		WPARAM wParam,
		LPARAM lParam);

	template<class T> void Release(T t)
	{
		if( t )
		{
			t->Release();
			t = 0;
		}
	}
		
	template<class T> void Delete(T t)
	{
		if( t )
		{
			delete t;
			t = 0;
		}
	}
}

#endif // __d3dUtilityH__