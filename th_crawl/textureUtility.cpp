//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: textureUtility.cpp
//
// 내용: 그리기 함수 정의 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "textureUtility.h"
#include "option_manager.h"


//
// extern
//

extern IDirect3DDevice9* Device; //디바이스포인터
extern IDirect3DVertexBuffer9* g_pVB; //버텍스버퍼포인터
extern D3DXMATRIXA16 g_BaseMatrix; //매트릭스포인터

//
// 텍스쳐를 회전시킨다.
//

bool TextureRotate(float z)
{
	z = z*D3DX_PI/180;
	D3DXMATRIXA16 MatrixA;
	D3DXMatrixIdentity(&MatrixA);
	D3DXMatrixRotationYawPitchRoll(&MatrixA, 0, 0, z);
	D3DXMatrixMultiply(&g_BaseMatrix, &g_BaseMatrix, &MatrixA);
	return true;
}

//
// 텍스쳐의 위치를 정한다.
//

bool TexturePosition(float x, float y)
{
	x /= option_mg.getWidth()/2;
	y /= -option_mg.getHeight()/2;
	D3DXMATRIXA16 MatrixA;
	D3DXMatrixIdentity(&MatrixA);
	D3DXMatrixTranslation(&MatrixA, x, y, 0.0f);
	D3DXMatrixMultiply(&g_BaseMatrix, &g_BaseMatrix, &MatrixA);
	return true;
}

//
// 텍스쳐의 크기를 정한다.
//

bool TextureScale(float x,float y)
{
	D3DXMATRIXA16 MatrixA;
	D3DXMatrixIdentity(&MatrixA);
	D3DXMatrixScaling(&MatrixA, x, y, 1);
	D3DXMatrixMultiply(&g_BaseMatrix, &g_BaseMatrix, &MatrixA);
	return true;
}


//
// 텍스쳐를 그린다.
//

bool DrawTexture(IDirect3DTexture9* g_pTempTexture)
{
	Device->SetTransform(D3DTS_WORLD, &g_BaseMatrix);
	Device->SetTexture(0, g_pTempTexture);
	Device->SetStreamSource(0,g_pVB,0,sizeof(Vertex));
	Device->SetFVF(D3DFVF_XYZ|D3DFVF_TEX1);
	if(SUCCEEDED(Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2)))
	{
		D3DXMatrixIdentity(&g_BaseMatrix);
		return true;
	}
	else
	{
		D3DXMatrixIdentity(&g_BaseMatrix);
		return false;
	}
}


bool SpriteDraw(LPD3DXSPRITE pSprite, RECT rc, float scale_x, float scale_y, float rotation, float x, float y, IDirect3DTexture9* texture,D3DCOLOR color)
{
	rotation = rotation*D3DX_PI/180;

	D3DXMATRIX matRotation, matScale, matMultiply;

	D3DXMatrixScaling(&matScale,scale_x,scale_y,1);
	D3DXMatrixRotationZ(&matRotation, rotation);
	D3DXMatrixMultiply(&matMultiply,&matScale,&matRotation);

	matMultiply._41 = x;
	matMultiply._42 = y;
	pSprite->SetTransform(&matMultiply);

	D3DXVECTOR3 Pos((float)(rc.right-rc.left)/2, (float)(rc.bottom-rc.top)/2, 0);

	if(FAILED(pSprite->Draw(texture, &rc, &Pos, NULL, color)))
		return false;

	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationZ(&matRotation, 0.0f);
	D3DXMatrixMultiply(&matMultiply, &matRotation, &matScale);
	pSprite->SetTransform(&matRotation);

	return true;
}