//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: display.h
//
// 내용: 맵의 출력관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __DISPLAY_H__
#define  __DISPLAY_H__

#include <string>
#include <list>
#include "enum.h"

using namespace std;

class textures;


class text_dummy
{
public:
	wstring text;
	float width;
	bool enter;
	bool log;
	bool temp;
	D3DCOLOR color;


	text_dummy(string text_):text(ConvertUTF8ToUTF16(text_)),enter(true),log(false),color(D3DCOLOR_RGBA(0, 0, 0, 255)){calculateWitdh();};
	text_dummy(string text_, bool enter_, bool log_, bool temp_):text(ConvertUTF8ToUTF16(text_)),enter(enter_),log(log_),temp(temp_),color(D3DCOLOR_RGBA(255, 255, 255, 255)){calculateWitdh();};
	text_dummy(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_):text(ConvertUTF8ToUTF16(text_)),enter(enter_),log(log_),temp(temp_),color(color_){calculateWitdh();};

	void calculateWitdh();
};

class text_manager
{
public:
	list<text_dummy*> text_list;
	int length;
	int short_len;
	bool enter;

	text_manager():length(0),short_len(0),enter(true){};
	~text_manager();
	bool add_text(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_);
	void SetShowLength(int num){if(short_len>num){short_len = num;}};
	void DeleteTemp();	
	void SetEnter();
	void reset();
};

class infoBox
{
public:
	int x;
	int y;
	int x_size;
	int y_size;
	int x_comma;
	int y_comma;
	bool draw;
	string info;
	infoBox();
	void setBox(int x_, int y_, string info_) {
		x = x_;
		y = y_;
		info = info_;
		draw = true;
	}
	void init() { draw = false; }
};


class display_manager
{
public:
	int tile_type;
	text_manager text_log;
	text_manager text_sub;
	D3DXFONT_DESC fontDesc;
	string text;
	display_type state;
	RECT windowSize;
	float scale_x;
	float scale_y;

	char item_view[52];
	int item_num[52];
	item_view_type item_vt;
	LOCALIZATION_ENUM_KEY item_view_message;

	textures *image;

	int log_length;
	int move;
	int max_y;
	int sight_type;
	int spell_sight;

	infoBox infobox;

	display_manager();
	void releaseResources();
	void onLostResources();
	bool createResources(IDirect3DDevice9Ex* Device);
	void Getfontinfor();
	void draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void text_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void skill_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void spell_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void iden_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void property_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void skill2_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void state_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void game_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void item_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void log_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void sub_text_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
	void start_spellview(LOCALIZATION_ENUM_KEY message_);
	void start_skillview(LOCALIZATION_ENUM_KEY message_);
	void start_itemview(item_view_type type, LOCALIZATION_ENUM_KEY message_);
	void CheckMouseInfo(LPD3DXSPRITE pSprite, ID3DXFont* pfont, RECT& rc, int width_, int height_, string message);
	void drawInfoBox(LPD3DXSPRITE pSprite, ID3DXFont* pfont);
};

class stateBox
{
	LPD3DXSPRITE pSprite;
	ID3DXFont* pfont;
	RECT start_rc;
	RECT rc;
	int width;
	int current;
public:
	stateBox(LPD3DXSPRITE pSprite_, ID3DXFont* pfont_, RECT start_rc_);
	void addState(string name, D3DCOLOR color, string info, display_manager* display);
	void enter(display_manager* display);
};

extern DIMOUSESTATE CurrentMouseState;

void changedisplay(display_type set); 
int getDisplayMove();
void setDisplayMove(int move_);
void changemove(int var);
int GetDisplayMove();
string& SetText();
void printlog(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_);
void deletelog();
void enterlog();
void printarray(bool enter_, bool log_, bool temp_, D3DCOLOR color_, int num_, ...);

int printsub(string text_, bool enter_, D3DCOLOR color_);
int printsub_blank(int final_index, int next_index);
int printsub_utf8witdh(string text_, bool enter_, D3DCOLOR color_);
void deletesub();
void entersub();
int printarraysub(bool enter_, D3DCOLOR color_, int num_, ...);

void SetSpellSight(int sight, int sight_type_);


void SetDisplayTexture(textures *texture_);

void view_item(item_view_type type, LOCALIZATION_ENUM_KEY message_ = LOC_SYSTEM_DISPLAY_MANAGER_NORMAL_ITEM);
void view_spell(LOCALIZATION_ENUM_KEY message_);
void view_skill(LOCALIZATION_ENUM_KEY message_);
void CheckKey(char key_, int num_ = 0);
void AllCheckKey();
#endif // __DISPLAY_H__