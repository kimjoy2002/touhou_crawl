﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: armour.cpp
//
// 내용: 갑옷
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "armour.h"
#include "item.h"
#include "monster_texture.h"
#include "player.h"



int GetMaterial(material_kind kind_, armour_value ac_)
{
	switch(kind_)
	{
	case MTK_ROBE: //천
		return ac_==AMV_AC? 3
			:(ac_==AMV_MAX_EV? 0 
			:(ac_==AMV_MIN_EV? 0
			:0));
	case MTK_LEATHER: //가죽
		return ac_==AMV_AC? 5
			:(ac_==AMV_MAX_EV? -2 
			:(ac_==AMV_MIN_EV? -1
			:0));
	case MTK_CHAIN: //사슬
		return ac_==AMV_AC? 8
			:(ac_==AMV_MAX_EV? -6 
			:(ac_==AMV_MIN_EV? -3
			:0));
	case MTK_PLATE: //판금
		return ac_==AMV_AC? 13
			:(ac_==AMV_MAX_EV? -11 
			:(ac_==AMV_MIN_EV? -4
			:0));
	}

	return 0;
}


LOCALIZATION_ENUM_KEY GetMaterialStringKey(material_kind kind_)
{
	switch(kind_)
	{
	case MTK_ROBE: //천
		return LOC_SYSTEM_ITEM_ARMOUR_M_ROBE;
	case MTK_LEATHER: //가죽
		return LOC_SYSTEM_ITEM_ARMOUR_M_LEATHER;
	case MTK_CHAIN: //사슬
		return LOC_SYSTEM_ITEM_ARMOUR_M_CHAIN;
	case MTK_PLATE: //판금
		return LOC_SYSTEM_ITEM_ARMOUR_M_PLATE;
	}
	return LOC_SYSTEM_ITEM_ARMOUR_M_ROBE;
}



void MakeBaseArmour(armour_kind type, material_kind material, item_infor* t)
{
	//공통
	t->value1 = GetMaterial(material,AMV_AC);
	t->value2 = GetMaterial(material,AMV_MAX_EV);
	t->value3 = GetMaterial(material,AMV_MIN_EV);
	t->value4 = 0;
	t->value5 = type;
	t->value6 = 0;	
	t->is_pile = false;
	t->can_throw = false;


	switch(type)
	{
	case AMK_NORMAL:
		t->image = material==MTK_PLATE?&img_item_armor_armour_3:
			material==MTK_CHAIN?&img_item_armor_armour_2:
			material==MTK_LEATHER?&img_item_armor_armour_1:&img_item_armor_armour_0;
		t->equip_image = material == MTK_PLATE ? &img_play_item_body[4] :
			material == MTK_CHAIN ? &img_play_item_body[3] :
			material == MTK_LEATHER ? &img_play_item_body[2] : &img_play_item_body[1];
		t->name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_NORMAL, GetMaterialStringKey(material));
		t->value2 +=(material>=MTK_LEATHER)?((material>=MTK_CHAIN)?2:1):0;
		t->weight = 6.0f*(material*0.5+1);
		t->value = 40+(material*20);
		break;		
	case AMK_MIKO:
	{
		t->image = &img_item_armor_robe;
		t->equip_image = &img_play_item_body[10];
		t->name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_MIKO, GetMaterialStringKey(material));
		t->weight = 6.0f*(material*0.5 + 1);
		t->value = 80 + (material * 20);
		break;
	}
	case AMK_WING:
		t->image = &img_item_armor_relec;
		t->equip_image = &img_play_item_body[12];
		t->name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_WING, GetMaterialStringKey(material));
		t->weight = 3.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;		
	case AMK_KAPPA:
		t->image = &img_item_armor_rcold;
		t->equip_image = &img_play_item_body[13];
		t->name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_KAPPA, GetMaterialStringKey(material));
		t->weight = 8.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;		
	case AMK_FIRE:
		t->image = &img_item_armor_rfire;
		t->equip_image = &img_play_item_body[14];
		t->name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_FIRE, GetMaterialStringKey(material));
		t->weight = 8.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;		
	case AMK_MAID:
		t->image = &img_item_armor_rmagic;
		t->equip_image = &img_play_item_body[15];
		t->name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_MAID, GetMaterialStringKey(material));
		t->weight = 8.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;		
	case AMK_POISON:
		t->image = &img_item_armor_rpois;
		t->equip_image = &img_play_item_body[16];
		t->name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_POISON, GetMaterialStringKey(material));
		t->weight = 6.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;	
	case AMK_AUTUMN:
		t->image = &img_item_autumn_armour[material+1];
		t->equip_image = &img_play_item_body[5 + material + 1];
		t->name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_AUTUMN, GetMaterialStringKey(material));
		t->weight = 6.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;	
	}
}





armour_kind GetRandomArmourType(int good_bad)
{
	if(randA(good_bad>0?2:(good_bad==0?3:4)))
		return AMK_NORMAL;

	return (armour_kind) randA(AMK_POISON);

}



void MakeArmourEnchant(int good_bad, item_infor* t)
{
	t->value4 = good_bad?rand_int(1,t->value1/2)*(good_bad>=0?1:-1):0;

	if(good_bad)
	{
		t->name2 = name_infor(LOC_SYSTEM_ITEM_ARMOUR_RUNED);
	}

}
void equipArmour(armour_kind type, int value)
{
	switch(type)
	{
	case AMK_NORMAL:		
		break;		
	case AMK_MIKO:
		you.ResistUpDown(value,RST_CONFUSE);
		break;		
	case AMK_WING:
		you.ResistUpDown(value,RST_ELEC);
		break;		
	case AMK_KAPPA:
		you.ResistUpDown(value,RST_ICE);
		break;		
	case AMK_FIRE:
		you.ResistUpDown(value,RST_FIRE);
		break;		
	case AMK_MAID:
		you.MRUpDown(value*40);
		break;		
	case AMK_POISON:
		you.ResistUpDown(value,RST_POISON);
		break;	
	case AMK_AUTUMN:
		break;		
	}
}