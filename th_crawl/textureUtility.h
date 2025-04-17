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
#include <SpriteBatch.h>


bool SpriteDraw(shared_ptr<DirectX::SpriteBatch> pSprite, RECT rc, float scale_x, float scale_y, float rotation, float x, float y, ID3D11ShaderResourceView* texture,D3DCOLOR color);


#endif // __TEXTUREUTILITY_H__