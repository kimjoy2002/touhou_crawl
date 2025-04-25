//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: item.h
//
// 내용: 아이템 클래스 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ITEM_H__
#define  __ITEM_H__

#include "enum.h"
#include "unit.h"
#include "texture.h"
#include "atifact.h"
#include "scroll.h"
#include "amulet.h"

class item;

struct item_infor
{
	name_infor name;
	name_infor name2;
	textures *image;
	textures *equip_image;
	item_type type;
	float weight;
	int value;
	bool is_pile;
	int num;
	bool can_throw;

	int value0;
	int value1;
	int value2;
	int value3;
	int value4;
	int value5;
	int value6;
	int value7;
	int value8;

	bool curse;

	bool artifact;
	item_infor():name(LOC_SYSTEM_NONE_STRING), name2(LOC_NONE) ,image(NULL), equip_image(NULL),type(ITM_WEAPON_FIRST),weight(0),value(0),is_pile(false),
		num(1),value0(0),value1(0),value2(0),value3(0),value4(0),value5(0),value6(0), value7(0), value8(0)
		, curse(false), artifact(false)
	{};
	item_infor(item* item_);
	item_infor(item* item_, int num_);

	
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);

};


struct potion_iden
{
	bool iden;
	int color;
	potion_iden():
	iden(false), color(0)
	{};
};
struct scroll_iden
{
	char iden; //1은 사용함, 2는 선택사용함, 3은 식별
	int type;
	scroll_iden():
	iden(false), type(0)
	{};
};
struct ring_iden
{
	char iden; //1은 사용함, 2는 식별
	int type;
	ring_iden():
	iden(false), type(0)
	{};
};
struct amulet_iden
{
	char iden; //1은 사용함, 2는 식별
	int type;
	amulet_iden():
	iden(false), type(0)
	{};
};
struct spellcard_iden
{
	char iden; //1은 사용함, 2는 식별
	int type;
	spellcard_iden():
	iden(false), type(0)
	{};
};

enum iden_check
{
	IDEN_CHECK_START = 0,
	IDEN_CHECK_POTION_START = IDEN_CHECK_START,

	IDEN_CHECK_POTION_END = PT_MAX,
	IDEN_CHECK_SCROLL_START = IDEN_CHECK_POTION_END,

	IDEN_CHECK_SCROLL_END = IDEN_CHECK_SCROLL_START + SCT_MAX,

	IDEN_CHECK_RING_START = IDEN_CHECK_SCROLL_END,

	IDEN_CHECK_RING_END = IDEN_CHECK_RING_START + RGT_MAX,

	IDEN_CHECK_AMULET_START = IDEN_CHECK_RING_END,

	IDEN_CHECK_AMULET_END = IDEN_CHECK_AMULET_START + AMT_MAX,

	IDEN_CHECK_SPC_START = IDEN_CHECK_AMULET_END,

	IDEN_CHECK_SPC_END = IDEN_CHECK_SPC_START + SPC_V_MAX,

	IDEN_CHECK_BOOK_START = IDEN_CHECK_SPC_END,

	IDEN_CHECK_BOOK_END = IDEN_CHECK_BOOK_START + 1 + BOOK_LAST, //1은 미감정 책

	IDEN_CHECK_ETC_START = IDEN_CHECK_BOOK_END,

	IDEN_CHECK_ETC_END = IDEN_CHECK_ETC_START +  2 + TMT_MAX, //2은 P아이템, 음식

	IDEN_CHECK_END = IDEN_CHECK_ETC_END
};

class Iden_collect
{
public:
	potion_iden potion_list[PT_MAX];
	scroll_iden scroll_list[SCT_MAX];
	ring_iden ring_list[RGT_MAX];
	amulet_iden amulet_list[AMT_MAX];
	spellcard_iden spellcard_list[SPC_V_MAX];
	bool books_list[BOOK_LAST];
	bool autopickup[IDEN_CHECK_END];
};


class item
{
public:
	name_infor name;
	name_infor second_name;
	textures *image;
	textures *equip_image;
	coord_def position;
	coord_def prev_position;
	item_type type;
	float weight;
	int value;
	bool is_pile;
	int num;
	char id;
	bool prev_sight;
	bool not_find;
	bool now_find;
	bool curse;
	bool identify;
	bool identify_curse;
	bool can_throw; 
	bool drop;
	bool throw_item;
	bool hamme_gift; //망치의 반대효과가 발동되면 전부 뺏어감
	int waste;
	int delay_turn;

	int value0; //비상용 - 책-종류(이 것은 필요한 아이템아니면 사용하지 않는 변수다.)

	
	int value1; //value1 - 무기,탄막-명중력 방어구-AC 방패-SH 음식,물약,스크롤,링-종류 책-마법 스펠카드-횟수 발동템-종류
	
	int value2; //value2 - 무기,탄막-공격력 방어구,방패-EV  음식-만복도 링-수치 스펠카드-종류 아뮬렛-(오컬트)

	int value3;	//value3 - 방어구-최소 EV패널티 탄막-인챈트 음식-신선도 스펠카드-사용예측횟수 아뮬렛-오컬트발동여부
	
	int value4; //value4 - 무기-인챈트 방어구-AC+ 방패-SH+ 탄막-종류 음식(p템)-몬스터id 

	int value5;	//value5 - 무기-속성 방어구-저항 음식-pow상승치
	
	int value6; //value6 - 속성인챈트 시간. 0이면 미확인.-1이면 식별+무한, 양수면 식별+유한

	int value7; //value7 - 무기 - 최대공속
	
	int value8; //value8 - 무기 - 최소공속

	
	vector<atifact_infor> atifact_vector;

	item();
	item(const coord_def &c, const item_infor &t);
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	
	string GetName(int num_ = -1, bool simple_ = false);
	string GetNameString();
	name_infor GetNameInfor();
	textures *GetEquipTexture();
	const D3DCOLOR item_color();
	bool draw(shared_ptr<DirectX::SpriteBatch> pSprite, shared_ptr<DirectX::SpriteFont> pfont, float x_, float y_);

	bool isSimpleType(item_type_simple type_); //해당 타입이 맞나 확인한다.
	bool isRightType(equip_type type_); //해당 부위에 장착할 수 있는지 확인한다.
	equip_type GetArmorType();//방어구 타입으로 리턴한다.
	bool SameItem(const item &item_);
	float GetStabPercent();
	int GetValue(int i);

	void TurnSave();//다른층으로 도망쳤다.
	void TurnLoad();//다른층에서 도망왔다.

	bool isweapon();
	bool isarmor();
	bool isjewerly();
	bool isring();
	bool isiden();
	bool isautopick();
	bool isArtifact();
	bool isChargable();
	bool isEvokable();

	bool Curse(bool equip_,equip_type kind_);
	bool isEnhantable();
	bool Enchant(equip_type kind_, int acc_);
	bool pick(); //리턴값은 던지기 무기일때

	void Identify();//걍식별
	void autoIdentify();//장신구계열의 자동식별
	void equipIdentify();
	void income_view(); //시야에 들어오다.

	int action(int delay_);
	bool offsetmove(const coord_def &c);

};


item_infor& makeCustomBook(item_infor* t);
item_infor& makeitem(item_type type, int good_bad, item_infor* t, int select_ = -1);
item_infor& makePitem(monster_index mon_id, int num, item_infor* t);
item_infor& CustomItem(item_infor* t, item_type type, textures* graphic, textures* equip_graphic, int num, bool pile_, bool curse, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, bool throw_, name_infor name_, name_infor name2_, float weight, int value);
item_infor& CustomSimpleItem(item_infor* t, item_type type, int num, bool curse, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8);
int baditem(const item_infor *item_);
item_type RandomItemType();

string GetItemTypeSting(item_type_simple type);


bool GetItemofKey(list<item>::iterator it,list<item>::iterator it2);
int GetItemofNum(list<item>::iterator it,list<item>::iterator it2);
 
list<item>::iterator GetKeytoItem(char key_);


bool iteminfor_(item* item_, bool onlyinfor);
bool iteminfor_(int key_, bool onlyinfor);
void init_identify();
item_infor& CreateFloorItem(int floor, item_infor* item_);
void create_item(int floor, int num_);


extern Iden_collect iden_list;

#endif // __PLAYER_H__