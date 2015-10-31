//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: textureUtility.h
//
// 내용: 그리기 함수 선언 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __TEXTUREUTILITY_H__
#define  __TEXTUREUTILITY_H__

#include "d3dUtility.h"

bool TextureRotate(float z);

bool TexturePosition(float x, float y);

bool TextureScale(float x,float y);

bool DrawTexture(IDirect3DTexture9* g_pTempTexture);

bool SpriteDraw(LPD3DXSPRITE pSprite, RECT rc, float scale_x, float scale_y, float rotation, float x, float y, IDirect3DTexture9* texture,D3DCOLOR color);


#endif // __TEXTUREUTILITY_H__