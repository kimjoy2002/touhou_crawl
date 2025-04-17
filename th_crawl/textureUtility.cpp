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

extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pImmediateContext;

//
// 텍스쳐를 그린다.
//

bool SpriteDraw(shared_ptr<DirectX::SpriteBatch> pSprite, RECT rc, float scale_x, float scale_y, float rotation_deg, float x, float y, ID3D11ShaderResourceView* texture,D3DCOLOR color)
{
    using namespace DirectX;

    // 색상 변환
    XMVECTOR colorVec = D3DCOLOR_to_XMVECTOR(color);

    // 회전 라디안 단위
    float rotation = XMConvertToRadians(rotation_deg);

    // 중심점 (원래 rc 중심이 origin)
    XMFLOAT2 origin = {
        floorf((float)(rc.right - rc.left) / 2.0f),
        floorf((float)(rc.bottom - rc.top) / 2.0f)
    };
    // 스케일, 위치
    XMFLOAT2 scale = { scale_x, scale_y };
    XMFLOAT2 position = {
        floorf(x) + 0.5f,
        floorf(y) + 0.5f
    };

    // Draw
    pSprite->Draw(
        texture,
        position,
        &rc,
        colorVec,
        rotation,
        origin,
        scale
    );

    return true;
}