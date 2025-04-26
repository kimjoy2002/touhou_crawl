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
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include "enum.h"

using namespace std;

class textures;


enum SPECIAL_CLINKABLE { 
	SPECIAL_CLINKABLE_START = 1000,
	SPECIAL_CLINKABLE_Y = SPECIAL_CLINKABLE_START,
	SPECIAL_CLINKABLE_N,
	SPECIAL_CLINKABLE_INFORMATION_CHARACTER,
	SPECIAL_CLINKABLE_INFORMATION_FAITH,
	SPECIAL_CLINKABLE_INFORMATION_INDENTIFY,
	SPECIAL_CLINKABLE_INFORMATION_PROPERTY,
	SPECIAL_CLINKABLE_INFORMATION_SPELL,
	SPECIAL_CLINKABLE_INFORMATION_LEARN_SPELL,
	SPECIAL_CLINKABLE_INFORMATION_RUNE,
	SPECIAL_CLINKABLE_INFORMATION_DUNGEON,
	SPECIAL_CLINKABLE_INFORMATION_LOG,
	SPECIAL_CLINKABLE_INFORMATION_DUMP,
	SPECIAL_CLINKABLE_INVENTORY,
	SPECIAL_CLINKABLE_DISCARD,
	SPECIAL_CLINKABLE_EAT,
	SPECIAL_CLINKABLE_READ,
	SPECIAL_CLINKABLE_DRINK,
	SPECIAL_CLINKABLE_THROW,
	SPECIAL_CLINKABLE_EVOKE,		
	SPECIAL_CLINKABLE_EQUIP_WEAPON,
	SPECIAL_CLINKABLE_UNEQUIP_WEAPON,
	SPECIAL_CLINKABLE_EQUIP_ARMOUR,
	SPECIAL_CLINKABLE_UNEQUIP_ARMOUR,
	SPECIAL_CLINKABLE_EQUIP_JEWELRY,
	SPECIAL_CLINKABLE_UNEQUIP_JEWELRY
};





class text_dummy
{
public:
	wstring text;
	float width;
	bool enter;
	bool log;
	bool temp;
	D3DCOLOR color;
	int clickable;


	text_dummy(string text_):text(ConvertUTF8ToUTF16(text_)),enter(true),log(false),color(D3DCOLOR_RGBA(0, 0, 0, 255)),clickable(0){calculateWitdh();};
	text_dummy(string text_, bool enter_, bool log_, bool temp_):text(ConvertUTF8ToUTF16(text_)),enter(enter_),log(log_),temp(temp_),color(D3DCOLOR_RGBA(255, 255, 255, 255)),clickable(0){calculateWitdh();};
	text_dummy(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_):text(ConvertUTF8ToUTF16(text_)),enter(enter_),log(log_),temp(temp_),color(color_),clickable(0){calculateWitdh();};
	text_dummy(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_, int clickable):text(ConvertUTF8ToUTF16(text_)),enter(enter_),log(log_),temp(temp_),color(color_),clickable(clickable){calculateWitdh();};

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
	bool add_text(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_, int char_ = 0);
	void SetShowLength(int num){if(short_len>num){short_len = num;}};
	void DeleteTemp();	
	void SetEnter();
	void reset();
	void removeClickable();
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


struct FontInfo {
    float Size;        // 폰트 크기 (픽셀 단위)
    float Width;       // 글자 가로 폭 (평균값 or 고정폭 기준)
    float Height;      // 글자 높이

    FontInfo() = default;
    FontInfo(float size_, float width_, float height_)
        : Size(size_), Width(width_), Height(height_){}
};

class display_manager
{
public:
	int tile_type;
	text_manager text_log;
	text_manager text_sub;
	FontInfo fontDesc;
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
	
	vector<int> selection_vector;
	vector<int> spell_skill_vector;

	int log_length;
	int move;
	int max_y;
	int sight_type;
	int spell_sight;
	coord_def prev_map_view;

	infoBox infobox;

	display_manager();
	void Getfontinfor();
	int convertClickable(int id);
	textures* getSelectTexure(int id);
	void draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void text_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void skill_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void spell_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void iden_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void property_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void skill2_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void state_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void game_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void item_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void log_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void sub_text_draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	void start_spellview(LOCALIZATION_ENUM_KEY message_);
	void start_skillview(LOCALIZATION_ENUM_KEY message_);
	void start_itemview(item_view_type type, LOCALIZATION_ENUM_KEY message_);
	void CheckMouseInfo(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont, RECT& rc, int width_, int height_, string message);
	void drawInfoBox(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont);
	bool DrawRectOutline(std::shared_ptr<DirectX::SpriteBatch> spriteBatch, const RECT& rc, int thickness, D3DCOLOR color);
};

class stateBox
{
	shared_ptr<DirectX::SpriteBatch> pSprite;
	shared_ptr<DirectX::SpriteFont> pfont;
	RECT start_rc;
	RECT rc;
	int width;
	int current;
public:
	stateBox(shared_ptr<DirectX::SpriteBatch> pSprite_, shared_ptr<DirectX::SpriteFont> pfont_, RECT start_rc_);
	void addState(string name, D3DCOLOR color, string info, display_manager* display);
	void enter(display_manager* display);
};

extern DIMOUSESTATE CurrentMouseState;

string getCilnkableString(int kind);
string getCommandString(int kind, int value);
void changedisplay(display_type set); 
int getDisplayMove();
void setDisplayMove(int move_);
void changemove(int var);
int GetDisplayMove();
string& SetText();
void printlog(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_);
void printlog(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_, int char_);
void deletelog();
void enterlog();
void printarray(bool enter_, bool log_, bool temp_, D3DCOLOR color_, int num_, ...);

int printsub(string text_, bool enter_, D3DCOLOR color_);
int printsub(string text_, bool enter_, D3DCOLOR color_, int char_);
int printsub_blank(int final_index, int next_index);
void add_stringblank(ostringstream& oss, int next_index);
int printsub_utf8witdh(string text_, bool enter_, D3DCOLOR color_);
void deletesub();
void entersub();
void startSelection(vector<int> select_list);
void endSelection();
void startAbilGrid(vector<int> select_list);
void endAbilGrid();

int printarraysub(bool enter_, D3DCOLOR color_, int num_, ...);

void SetSpellSight(int sight, int sight_type_);


void SetDisplayTexture(textures *texture_);

void view_item(item_view_type type, LOCALIZATION_ENUM_KEY message_ = LOC_SYSTEM_DISPLAY_MANAGER_NORMAL_ITEM);
void rollback_item(item_view_type type, LOCALIZATION_ENUM_KEY message_);
void view_spell(LOCALIZATION_ENUM_KEY message_);
void view_skill(LOCALIZATION_ENUM_KEY message_);
void CheckKey(char key_, int num_ = 0);
void AllCheckKey();
#endif // __DISPLAY_H__