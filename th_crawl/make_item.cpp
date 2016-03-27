//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: make_item.cpp
//
// 내용: 아이템 만들기관련 함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"
#include "item.h"
#include "monster_texture.h"
#include "ring.h"
#include "const.h"
#include "potion.h"
#include "scroll.h"
#include "book.h"
#include "throw.h"
#include "weapon.h"
#include "spellcard.h"
#include <algorithm>

extern HANDLE mutx;
void WeaponMake(item_type type, int good_bad, item_infor* t, int pixed_type = -1);
void ShieldMake(item_type type, int good_bad, item_infor* t);

int armour_stat[5][3] =
{{1,0,0},
{2,-2,0},
{5,-4,-1},
{7,-7,-3},
{10,-11,-4}
};



item* environment::MakeItem(const coord_def &c, const item_infor &t)
{
	return AddItem(c,&item(c,t));
}

item_infor& makePitem(monster_index mon_id, int num, item_infor* t)
{
	t->type = ITM_FOOD;
	t->num = num;
	t->curse = false;
	t->value1 = 0;
	t->value2 = 50;
	t->value3 = 200;
	t->value4 = (int)mon_id;
	t->value5 = rand_int(10,20);
	t->value6 = 0;
	t->is_pile = true;
	t->can_throw = false;
	t->image = &img_item_food_p_item;
	t->name.name = "P템";
	t->name.name_type = true;
	t->name2.name = "";
	t->name2.name_type = true;
	t->weight = 1.0f;
	t->value = 30;
	return (*t);
}

item_infor& makeCustomBook(item_infor* t)
{
	
	t->value0 = 0;
	
	t->type = ITM_BOOK;
	t->num = 1;
	t->curse = false;
	{
		t->name2.name = "떨어진 마법책";
		t->name2.name_type = true;
		t->value0 = 0;
		t->value1 = 0;
		t->value2 = 0;
		t->value3 = 0;
		t->value4 = 0;
		t->value5 = 0;
		t->value6 = 0;
		t->value7 = 0;
		t->value8 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_book[0];
		t->name.name = "떨어진 마법책";
		t->name.name_type = true;
		t->weight = 5.0f;
		t->value = 150;
	}
	return (*t);
}
item_infor& makeitem(item_type type, int good_bad, item_infor* t, int select_)
{
	t->value0 = 0;
	t->type = type;
	t->num = 1;
	t->curse = false;
	t->name2.name = "";
	t->name2.name_type = true;
	if((t->type>=ITM_ARMOR_FIRST && t->type< ITM_ARMOR_LAST))
	{
		int rune_ = abs(t->value4*3);

		if(randA_1(10)<rune_)
		{
			t->name2.name = "룬이 새겨진 ";
			t->name2.name_type = true;
		}
	}
	switch(type)
	{
	case ITM_WEAPON_SHORTBLADE:
	case ITM_WEAPON_LONGBLADE:
	case ITM_WEAPON_MACE:
	case ITM_WEAPON_SPEAR:
	case ITM_WEAPON_AXE:
		WeaponMake(type, good_bad, t,select_);
		break;
	case ITM_THROW_TANMAC:
		MakeTanmac(t,select_);
		break;
	case ITM_ARMOR_BODY_ROBE:
		t->value1 = armour_stat[0][0];
		t->value2 = armour_stat[0][1];
		t->value3 = armour_stat[0][2];
		t->value4 = (randA(2)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_armor_robe;
		t->name.name = "무녀복";
		t->name.name_type = true;
		t->weight = 6.0f;
		t->value = 40;
		break;		
	case ITM_ARMOR_BODY_ARMOUR_0:
		t->value1 = armour_stat[1][0];
		t->value2 = armour_stat[1][1];
		t->value3 = armour_stat[1][2];
		t->value4 = (randA(2)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_armor_armour_0;
		t->name.name = "경갑옷";
		t->name.name_type = true;
		t->weight = 10.0f;
		t->value = 80;
		break;
	case ITM_ARMOR_BODY_ARMOUR_1:
		t->value1 = armour_stat[2][0];
		t->value2 = armour_stat[2][1];
		t->value3 = armour_stat[2][2];
		t->value4 = (randA(2)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_armor_armour_1;
		t->name.name = "중간 중갑옷";
		t->name.name_type = true;
		t->weight = 12.0f;
		t->value = 100;
		break;
	case ITM_ARMOR_BODY_ARMOUR_2:
		t->value1 = armour_stat[3][0];
		t->value2 = armour_stat[3][1];
		t->value3 = armour_stat[3][2];
		t->value4 = (randA(2)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_armor_armour_2;
		t->name.name = "두꺼운 중갑옷";
		t->name.name_type = true;
		t->weight = 15.0f;
		t->value = 200;
		break;
	case ITM_ARMOR_BODY_ARMOUR_3:
		t->value1 = armour_stat[4][0];
		t->value2 = armour_stat[4][1];
		t->value3 = armour_stat[4][2];
		t->value4 = (randA(2)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_armor_armour_3;
		t->name.name = "판금갑옷";
		t->name.name_type = true;
		t->weight = 20.0f;
		t->value = 40;
		break;
	case ITM_ARMOR_SHIELD:
		ShieldMake(type, good_bad, t);
		break;
	case ITM_ARMOR_HEAD:
		t->value1 = 1;
		t->value2 = 0;
		t->value3 = 0;
		t->value4 = (randA(3)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_armor_helmet;
		t->name.name = "리본";
		t->name.name_type = true;
		t->weight = 5.0f;
		t->value = 70;
		break;
	case ITM_ARMOR_CLOAK:
		t->value1 = 1;
		t->value2 = 0;
		t->value3 = 0;
		t->value4 = (randA(3)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_armor_cloak;
		t->name.name = "망토";
		t->name.name_type = false;
		t->weight = 3.0f;
		t->value = 70;
		break;
	case ITM_ARMOR_GLOVE:
		t->value1 = 1;
		t->value2 = 0;
		t->value3 = 0;
		t->value4 = (randA(3)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_armor_glove;
		t->name.name = "장갑";
		t->name.name_type = true;
		t->weight = 2.0f;
		t->value = 70;
		break;
	case ITM_ARMOR_BOOT:
		t->value1 = 1;
		t->value2 = 0;
		t->value3 = 0;
		t->value4 = (randA(3)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_armor_boot;
		t->name.name = "신발";
		t->name.name_type = true;
		t->weight = 4.0f;
		t->value = 70;
		break;
	case ITM_RING:
		t->value1 = select_!=-1?select_:(int)goodbadring(good_bad);
		if(isRingGotValue((ring_type)t->value1))
		{
			t->value2 = rand_int(1,6)*(good_bad>=0?1:-1);
		}
		else
		{
			t->value2 = 1;
		}
		t->value3 = 0;
		t->value4 = 0;
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_ring;
		t->name.name = "반지";
		t->name.name_type = false;
		t->weight = 1.0f;
		t->value = 200;
		break;
	case ITM_SPELL:
		t->value2 = select_!=-1?(spellcard_evoke_type)select_:randA(SPC_V_MAX-1);
		t->value1 = SpellcardMaxCharge((spellcard_evoke_type)t->value2)*rand_float(0.2f,1);
		t->value3 = 0;
		t->value4 = 0;
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_spellcard;
		t->name.name = "스펠카드";
		t->name.name_type = false;
		t->weight = 2.0f;
		t->value = 200;
		break;
	case ITM_SPELLCARD:
		//createSpellCard(good_bad,select_,t);
		//spellcard.cpp에서
		break;
	case ITM_FOOD:
		switch(select_!=-1?select_:randA(1))
		{
		case 0:
			t->value1 = 1;
			t->value2 = 0;
			t->value3 = 0;
			t->value4 = 0;
			t->value5 = 100;
			t->value6 = 0;
			t->is_pile = true;
			t->can_throw = false;
			t->image = &img_item_food_bread;
			t->name.name = "빵";
			t->name.name_type = true;
			t->weight = 2.0f;
			t->value = 30;
			break;
		case 1:	
			t->value1 = 2;
			t->value2 = 0;
			t->value3 = 0;
			t->value4 = 0;
			t->value5 = 30;
			t->value6 = 0;
			t->is_pile = true;
			t->can_throw = false;
			t->num = rand_int(1,3);
			t->image = &img_item_sweet_potato;
			t->name.name = "고구마";
			t->name.name_type = true;
			t->weight = 1.0f*t->num;
			t->value = 30;
			break;
		}
		break;
	case ITM_POTION:
		t->value1 = select_!=-1?select_:(int)goodbadpotion(good_bad);
		t->value2 = 0;
		t->value3 = 0;
		t->value4 = 0;
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = true;
		t->can_throw = false;
		t->image = &img_item_potion[0];
		t->name.name = "물약";
		t->name.name_type = true;
		t->weight = 4.0f;
		t->value = 120;
		break;
	case ITM_SCROLL:
		t->value1 = select_!=-1?select_:(int)goodbadscroll(good_bad);
		t->value2 = 0;
		t->value3 = 0;
		t->value4 = 0;
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = true;
		t->can_throw = false;
		t->image = &img_item_scroll;
		t->name.name = "두루마리";
		t->name.name_type = false;
		t->weight = 2.0f;
		t->value = 120;
		break;		
	case ITM_BOOK:
		{
			int book= select_!=-1?select_:rand_int(BOOK_FIRST,BOOK_LAST-1);	
			t->name2.name = random_book_list[randA(RANDOM_BOOK_NUM-1)];
			t->name2.name_type = true;
			t->value0 = book;
			t->value1 = static_book_list[book].spell[0];
			t->value2 = static_book_list[book].spell[1];
			t->value3 = static_book_list[book].spell[2];
			t->value4 = static_book_list[book].spell[3];
			t->value5 = static_book_list[book].spell[4];
			t->value6 = static_book_list[book].spell[5];
			t->value7 = static_book_list[book].spell[6];
			t->value8 = static_book_list[book].spell[7];
			t->is_pile = false;
			t->can_throw = false;
			t->image = &img_item_book[0];
			t->name.name = static_book_list[book].name;
			t->name.name_type = static_book_list[book].name_back;
			t->weight = 5.0f;
			t->value = static_book_list[book].value;
		}
		break;
	case ITM_GOAL:
		t->value1 = 0;
		t->value2 = 0;
		t->value3 = 0;
		t->value4 = 0;
		t->value5 = 0;
		t->value6 = 0;
		t->is_pile = false;
		t->can_throw = false;
		t->image = &img_item_goal;
		t->name.name = "축하 쪽지";
		t->name.name_type = false;
		t->weight = 1.0f;
		t->value = 10000;
		break;		
	default:
		break;
	}

	if(good_bad && randA(9)+1 <= baditem(t))
	{
		t->curse = true;
	}

	return (*t);
}	

int baditem(const item_infor *item_) //randA(9)+1<=리턴값일때 저주걸림
{
	if(item_->type >= ITM_WEAPON_FIRST && item_->type < ITM_WEAPON_LAST)
	{
		if(1-item_->value3*2-item_->value4*2>0)
			return 1-item_->value3*4-item_->value4*4;
	}
	else if(item_->type >= ITM_ARMOR_FIRST && item_->type < ITM_ARMOR_LAST)
	{
		if(1-item_->value4*2>0)
			return 1-item_->value4*6;
	}
	else if(item_->type == ITM_SPELLCARD)
	{
		return 0;
		//if(isAmuletGotValue((amulet_type)item_->value1) && item_->value2<0)
		//	return 10;
	}
	else if(item_->type == ITM_RING)
	{
		if(item_->value1 == RGT_HUNGRY)
			return 10;
		if(item_->value1 == RGT_TELEPORT)
			return 8;
		if(isRingGotValue((ring_type)item_->value1) && item_->value2<0)
			return 10;
	}
	return 0;
}

item_type RandomWeapon()
{
	int i = randA(4);
	switch(i)
	{
	case 0:
		return ITM_WEAPON_SHORTBLADE;
	case 1:
		return ITM_WEAPON_LONGBLADE;
	case 2:
		return ITM_WEAPON_AXE;
	case 3:
		return ITM_WEAPON_MACE;
	case 4:
		return ITM_WEAPON_SPEAR;
	}
	return ITM_WEAPON_SHORTBLADE;
}




item_infor& CustomItem(item_infor* t, item_type type, textures* graphic, int num, bool pile_, bool curse, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, bool throw_, name_infor name_ , name_infor name2_, float weight, int value)
{
	t->type = type;
	t->num = num;
	t->curse = curse;
	t->value0 = 0;
	t->value1 = v1;
	t->value2 = v2;
	t->value3 = v3;
	t->value4 = v4;
	t->value5 = v5;
	t->value6 = v6;
	t->value7 = v7;
	t->value8 = v8;
	t->is_pile = pile_;
	t->can_throw = throw_;
	t->image = graphic;
	t->name.name = name_.name;
	t->name.name_type = name_.name_type;
	t->name2.name = name2_.name;
	t->name2.name_type = name2_.name_type;
	t->weight = weight;
	t->value = value;
	return (*t);
}



item_infor& CustomSimpleItem(item_infor* t, item_type type, int num, bool curse, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8)
{
	makeitem(type, 0, t);
	t->num = num;
	t->curse = curse;
	t->value0 = 0;
	t->value1 = v1;
	t->value2 = v2;
	t->value3 = v3;
	t->value4 = v4;
	t->value5 = v5;
	t->value6 = v6;
	t->value5 = v7;
	t->value6 = v8;
	return (*t);
}


void WeaponMake(item_type type, int good_bad, item_infor* t, int pixed_type)
{
	t->value0 = 0;
	t->value3 = randA(2)?0:randA(4*good_bad);
	t->value4 = randA(2)?0:randA(4*good_bad);
	t->value5 = (good_bad>0 && randA(2)>1)?randA_1(WB_MAX-1):0;
	t->name2.name = "";
	t->name2.name_type = true;
	int rune_ = abs(t->value3+t->value4)+(t->value5?6:0);

	if(randA_1(10)<rune_)
	{
		t->name2.name = "룬이 새겨진 ";
		t->name2.name_type = true;		
	}

	t->is_pile = false;
	switch(type)
	{
	case ITM_WEAPON_SHORTBLADE:
		{
			int i = pixed_type>0?pixed_type:randA_1(25);
			if(i<=10)
			{
				t->value1 = 4;
				t->value2 = 7;
				t->value6 = 0;
				t->value7 = 10;
				t->value8 = 5;
				t->can_throw = false;
				t->image = &img_item_weapon_dagger;
				t->name.name = "대거";
				t->name.name_type = false; //true 받침있음
				t->weight = 2.0f;
				t->value = 50;
				return;
			}
			else if(i<=20)
			{
				t->value1 = 6;
				t->value2 = 6;
				t->value5 = 0;
				t->value6 = 0;
				t->value7 = 10;
				t->value8 = 5;
				t->can_throw = true;
				t->image = &img_item_weapon_knife;
				t->name.name = "나이프";
				t->name.name_type = false; //true 받침있음
				t->weight = 1.5f;
				t->value = 50;
				return;
			}
			else if(i<=25)
			{
				t->value1 = 2;
				t->value2 = 8;
				t->value6 = 0;
				t->value7 = 13;
				t->value8 = 5;
				t->can_throw = false;
				t->image = &img_item_weapon_shortsword;
				t->name.name = "숏소드";
				t->name.name_type = false; //true 받침있음
				t->weight = 3.0f;
				t->value = 50;
				return;
			}
		}
	case ITM_WEAPON_LONGBLADE:
		{
			int i = pixed_type>0?pixed_type:randA_1(30);
			if(i<=10)
			{
				t->value1 = 1;
				t->value2 = 9;
				t->value6 = 0;
				t->value7 = 13;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_katana;
				t->name.name = "도검";
				t->name.name_type = true; //true 받침있음
				t->weight = 4.0f;
				t->value = 100;
				return;
			}
			else if(i<=20)
			{
				t->value1 = 0;
				t->value2 = 10;
				t->value6 = 0;
				t->value7 = 14;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_scimitar;
				t->name.name = "언월도";
				t->name.name_type = false; //true 받침있음
				t->weight = 5.0f;
				t->value = 120;
				return;
			}
			else if(i<=30)
			{
				t->value1 = -4;
				t->value2 = 14;
				t->value6 = 0;
				t->value7 = 16;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_greatsword;
				t->name.name = "대검";
				t->name.name_type = true; //true 받침있음
				t->weight = 12.0f;
				t->value = 200;
				return;
			}
		}
	case ITM_WEAPON_AXE:
		{		
			int i = pixed_type>0?pixed_type:randA_1(22);
			if(i<=10)
			{
				t->value1 = 2;
				t->value2 = 8;
				t->value6 = 0;
				t->value7 = 13;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_handaxe;
				t->name.name = "손도끼";
				t->name.name_type = false; //true 받침있음
				t->weight = 3.0f;
				t->value = 60;
				return;
			}
			else if(i<=20)
			{
				t->value1 = -1;
				t->value2 = 10;
				t->value6 = 0;
				t->value7 = 14;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_battleaxe;
				t->name.name = "전투도끼";
				t->name.name_type = false; //true 받침있음
				t->weight = 6.0f;
				t->value = 60;
				return;
			}
			else if(i<=22)
			{
				t->value1 = -5;
				t->value2 = 15;
				t->value6 = 0;
				t->value7 = 17;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_anchor;
				t->name.name = "닻";
				t->name.name_type = true; //true 받침있음
				t->weight = 12.0f;
				t->value = 250;
				return;
			}
		}
	case ITM_WEAPON_MACE:
		{		
			int i = pixed_type>0?pixed_type:randA_1(42);
			if(i<=10)
			{
				t->value1 = 4;
				t->value2 = 7;
				t->value6 = 0;
				t->value7 = 13;
				t->value8 = 7;
				t->can_throw = false;
				t->image = randA(1)?&img_item_weapon_gohey:&img_item_weapon_gohey2;
				t->name.name = "고헤이";
				t->name.name_type = false; //true 받침있음
				t->weight = 3.0f;
				t->value = 60;
				return;
			}
			else if(i<=20)
			{
				t->value1 = 0;
				t->value2 = 9;
				t->value6 = 0;
				t->value7 = 14;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_broomstick;
				t->name.name = "빗자루";
				t->name.name_type = false; //true 받침있음
				t->weight = 4.0f;
				t->value = 80;
				return;
			}
			else if(i<=30)
			{
				t->value1 = 2;
				t->value2 = 8;
				t->value6 = 0;
				t->value7 = 13;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_umbrella;
				t->name.name = "우산";
				t->name.name_type = true; //true 받침있음
				t->weight = 3.0f;
				t->value = 50;
				return;
			}
			else if(i<=40)
			{
				t->value1 = -1;
				t->value2 = 10;
				t->value6 = 0;
				t->value7 = 14;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_hammer;
				t->name.name = "해머";
				t->name.name_type = false; //true 받침있음
				t->weight = 5.0f;
				t->value = 140;
				return;
			}
			else if(i<=42)
			{
				t->value1 = -6;
				t->value2 = 18;
				t->value6 = 0;
				t->value7 = 20;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_onbasira;
				t->name.name = "온바시라";
				t->name.name_type = false; //true 받침있음
				t->weight = 20.0f;
				t->value = 300;
				return;
			}
		}
	case ITM_WEAPON_SPEAR:
		{		
			int i = pixed_type>0?pixed_type:randA_1(30);
			if(i<=10)
			{
				t->value1 = 2;
				t->value2 = 8;
				t->value6 = 0;
				t->value7 = 13;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_spear;
				t->name.name = "창";
				t->name.name_type = true; //true 받침있음
				t->weight = 4.0f;
				t->value = 70;
				return;
			}
			else if(i<=20)
			{
				t->value1 = -2;
				t->value2 = 11;
				t->value6 = 0;
				t->value7 = 15;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_scythe;
				t->name.name = "낫";
				t->name.name_type = true; //true 받침있음
				t->weight = 7.0f;
				t->value = 120;
				return;
			}
			else if(i<=30)
			{
				t->value1 = -1;
				t->value2 = 10;
				t->value6 = 0;
				t->value7 = 14;
				t->value8 = 7;
				t->can_throw = false;
				t->image = &img_item_weapon_trident;
				t->name.name = "삼지창";
				t->name.name_type = true; //true 받침있음
				t->weight = 6.0f;
				t->value = 140;
				return;
			}
		}
	default:
		break;
	}
	t->value1 = 0;
	t->value2 = 0;
	t->value5 = 0;
	t->value6 = 0;
	t->value5 = 10;
	t->value6 = 10;
	t->can_throw = true;
	t->image = &img_item_weapon_knife;
	t->name.name = "버그";
	t->name.name_type = false; //true 받침있음
	t->weight = 1.0f;
	t->value = 0;
}



void ShieldMake(item_type type, int good_bad, item_infor* t)
{
	t->value0 = 0;
	t->value3 = 0;
	t->value4 = (randA(3)==1?randA_1(randA_1(2))*(good_bad>=0?1:-1):0);
	t->is_pile = false;
	t->name2.name = "";
	t->name2.name_type = true;
	int i = randA_1(30);
	if(i<=20)
	{
		t->value1 = 3;
		t->value2 = -1;
		t->value5 = 0;
		t->value6 = 0;
		t->can_throw = false;
		t->image = &img_item_weapon_roundshield;
		t->name.name = "나무방패";
		t->name.name_type = false;
		t->weight = 3.0f;
		t->value = 30;
		return;
	}
	else if(i<=28)
	{
		t->value1 = 7;
		t->value2 = -3;
		t->value5 = 0;
		t->value6 = 0;
		t->can_throw = false;
		t->image = &img_item_weapon_shield;
		t->name.name = "철방패";
		t->name.name_type = false;
		t->weight = 5.0f;
		t->value = 100;
		return;
	}
	else
	{
		t->value1 = 12;
		t->value2 = -6;
		t->value5 = 0;
		t->value6 = 0;
		t->can_throw = false;
		t->image = &img_item_weapon_kiteshield;
		t->name.name = "카이트실드";
		t->name.name_type = false;
		t->weight = 10.0f;
		t->value = 250;
		return;
	}
	t->value1 = 0;
	t->value2 = 0;
	t->value5 = 0;
	t->value6 = 0;
	t->can_throw = true;
	t->image = &img_item_weapon_roundshield;
	t->name.name = "버그방패";
	t->name.name_type = false; //true 받침있음
	t->weight = 1.0f;
	t->value = 0;
}





item_type RandomItemType()
{
	int i = randA(85);
	
	if(i<10)
		return RandomWeapon();
	else if(i<20)
		return ITM_ARMOR_BODY_ROBE;
	else if(i<21)
		return ITM_ARMOR_SHIELD;
	else if(i<22)
		return ITM_ARMOR_HEAD;
	else if(i<23)
		return ITM_ARMOR_CLOAK;
	else if(i<24)
		return ITM_ARMOR_GLOVE;
	else if(i<25)
		return ITM_ARMOR_BOOT;
	else if(i<40)
		return ITM_POTION;
	else if(i<55)
		return ITM_SCROLL;
	else if(i<60)
		return ITM_RING;
	else if(i<70)
		return ITM_SPELLCARD;
	else if(i<75)
		return ITM_THROW_TANMAC;
	else
		return ITM_FOOD;
}









void init_identify() //미식별아이템을 구별못하게 섞음
{
	{//물약
		deque<int> dq;
		for(int i=0;i<PT_MAX;i++)
			dq.push_back(i);
		random_shuffle(dq.begin(),dq.end());
		for(int i=0;i<PT_MAX;i++)
		{
			iden_list.potion_list[i].color = dq[i];

		}
	}//끝
	{//두루마리
		deque<int> dq;
		for(int i=0;i<SCT_MAX;i++)
			dq.push_back(i);
		random_shuffle(dq.begin(),dq.end());
		for(int i=0;i<SCT_MAX;i++)
		{
			iden_list.scroll_list[i].type = dq[i];
		}
	}//끝
	{//반지
		deque<int> dq;
		for(int i=0;i<RGT_MAX;i++)
			dq.push_back(i);
		random_shuffle(dq.begin(),dq.end());
		for(int i=0;i<RGT_MAX;i++)
		{
			iden_list.ring_list[i].type = dq[i];
		}
	}//끝
	{//목걸이
		deque<int> dq;
		for(int i=0;i<AMT_MAX;i++)
			dq.push_back(i);
		random_shuffle(dq.begin(),dq.end());
		for(int i=0;i<AMT_MAX;i++)
		{
			iden_list.amulet_list[i].type = dq[i];
		}
	}//끝
}

Iden_collect iden_list;