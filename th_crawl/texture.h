//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: texture.h
//
// 내용: texture클래스 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __TEXTRUE_H__
#define  __TEXTRUE_H__

#include "d3dUtility.h"
#include "textureUtility.h"
#include "texture.h"
#include "Fliename.h"
class TextureFile
{
public:
	LPCSTR name;
	IDirect3DTexture9* pTexture;
	TextureFile(LPCSTR _name);
	~TextureFile();
	bool loading(IDirect3DDevice9* Device);
	bool loadingEX(IDirect3DDevice9* Device);
};

class textures
{
private:
	TextureFile* texture;
	int alpha;
	bool normal;
protected:
	RECT rect;
public:
	textures(TextureFile* _texture, int left, int top, int right, int bottom, int alphas);
	textures(TextureFile* _texture, int mon_num, int alphas);
	textures(TextureFile* _texture, int mon_num);
	textures(TextureFile* _texture);
	~textures();
	bool draw(LPD3DXSPRITE pSprite, int alphas);
	bool draw(LPD3DXSPRITE pSprite, float x, float y, int alphas);
	bool draw(LPD3DXSPRITE pSprite, float x, float y, D3DCOLOR color);
	bool draw(LPD3DXSPRITE pSprite, float x, float y, float rotation, int alphas);
	bool draw(LPD3DXSPRITE pSprite, float x, float y, float rotation, float scale_x, float scale_y, D3DCOLOR color);
	bool draw(LPD3DXSPRITE pSprite, float x, float y, float rotation, float scale_x, float scale_y, int alphas);
	bool draw(LPD3DXSPRITE pSprite, RECT rc, int alphas);
	bool isNormal() { return normal; }
};




extern TextureFile texture_dungeon01;
extern TextureFile texture_monster01;
extern TextureFile texture_players01;
extern TextureFile texture_test;
extern TextureFile texture_item01;
extern TextureFile texture_item02;
extern TextureFile texture_item03;
extern TextureFile texture_laser;
extern TextureFile texture_dot_floor;
extern TextureFile texture_dot_wall;
extern TextureFile texture_dot_monster;
extern TextureFile texture_dot_player;
extern TextureFile texture_dot_up;
extern TextureFile texture_dot_down;
extern TextureFile texture_dot_item;
extern TextureFile texture_dot_door;
extern TextureFile texture_dot_temple;
extern TextureFile texture_dot_sea;
extern TextureFile texture_dot_mapping_floor;
extern TextureFile texture_dot_mapping_wall;
extern TextureFile texture_sight_rect;
extern TextureFile texture_title;
extern TextureFile texture_god[];

extern textures img_dungeon01[];
extern textures img_dungeon_object[][3];
extern textures img_monster01[];
extern textures img_item01[];
extern textures img_laser[];
extern textures img_thunder[];




extern textures dot_floor;
extern textures dot_wall;
extern textures dot_monster;
extern textures dot_player;
extern textures dot_up;
extern textures dot_down;
extern textures dot_item;
extern textures dot_door;
extern textures dot_temple;
extern textures dot_sea;
extern textures dot_mapping_floor;
extern textures dot_mapping_wall;
extern textures sight_rect;
extern textures explore_forbid_small;
extern textures explore_forbid_big;

#endif // __TEXTRUE_H__