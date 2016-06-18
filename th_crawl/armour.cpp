//////////////////////////////////////////////////////////////////////////////////////////////////
//
// ÆÄÀÏÀÌ¸§: armour.cpp
//
// ³»¿ë: °©¿Ê
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "armour.h"
#include "item.h"
#include "monster_texture.h""
#include "player.h"



int GetMaterial(material_kind kind_, armour_value ac_)
{
	switch(kind_)
	{
	case MTK_ROBE: //Ãµ
		return ac_==AMV_AC? 3
			:(ac_==AMV_MAX_EV? 0 
			:(ac_==AMV_MIN_EV? 0
			:0));
	case MTK_LEATHER: //°¡Á×
		return ac_==AMV_AC? 5
			:(ac_==AMV_MAX_EV? -2 
			:(ac_==AMV_MIN_EV? -1
			:0));
	case MTK_CHAIN: //»ç½½
		return ac_==AMV_AC? 8
			:(ac_==AMV_MAX_EV? -6 
			:(ac_==AMV_MIN_EV? -3
			:0));
	case MTK_PLATE: //ÆÇ±Ý
		return ac_==AMV_AC? 13
			:(ac_==AMV_MAX_EV? -11 
			:(ac_==AMV_MIN_EV? -4
			:0));
	}

	return 0;
}


string GetMaterialString(material_kind kind_)
{
	switch(kind_)
	{
	case MTK_ROBE: //Ãµ
		return "Ãµ";
	case MTK_LEATHER: //°¡Á×
		return "°¡Á×";
	case MTK_CHAIN: //»ç½½
		return "»ç½½";
	case MTK_PLATE: //ÆÇ±Ý
		return "ÆÇ±Ý";
	}
	return 0;
}



void MakeBaseArmour(armour_kind type, material_kind material, item_infor* t)
{
	//°øÅë
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
		t->image = &img_mons_default;
		t->name.name = GetMaterialString(material);
		t->name.name += " Æò»ó¿Ê";
		t->name.name_type = true;
		t->weight = 6.0f*(material*0.5+1);
		t->value = 40+(material*20);
		break;		
	case AMK_MIKO:
		t->image = &img_item_armor_robe;
		t->name.name = GetMaterialString(material);
		t->name.name += " ¹«³à¿Ê";
		t->name.name_type = true;
		t->weight = 6.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;		
	case AMK_WING:
		t->image = &img_mons_default;
		t->name.name = GetMaterialString(material);
		t->name.name += " ³¯°³¿Ê";
		t->name.name_type = true;
		t->weight = 3.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;		
	case AMK_KAPPA:
		t->image = &img_mons_default;
		t->name.name = GetMaterialString(material);
		t->name.name += " Ä±ÆÄ¿Ê";
		t->name.name_type = true;
		t->weight = 8.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;		
	case AMK_FIRE:
		t->image = &img_mons_default;
		t->name.name = GetMaterialString(material);
		t->name.name += " ºÒÁã¿Ê";
		t->name.name_type = true;
		t->weight = 8.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;		
	case AMK_MAID:
		t->image = &img_mons_default;
		t->name.name = GetMaterialString(material);
		t->name.name += " ¸ÞÀÌµå¿Ê";
		t->name.name_type = true;
		t->weight = 8.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;		
	case AMK_POISON:
		t->image = &img_mons_default;
		t->name.name = GetMaterialString(material);
		t->name.name += " ÀÎÇü¿Ê";
		t->name.name_type = true;
		t->weight = 6.0f*(material*0.5+1);
		t->value = 80+(material*20);
		break;	
	}
}





armour_kind GetRandomArmourType(int good_bad)
{
	if(randA(good_bad>0?2:(good_bad==0?3:4)))
		return AMK_NORMAL;

	return (armour_kind) randA(AMK_MAX-1);

}



void MakeArmourEnchant(int good_bad, item_infor* t)
{
	if(good_bad==0)
		return;

	t->value4 = (randA(2)==1?rand_int(1,2)*(good_bad>=0?1:-1):0);

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
	}

}