﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: item.cpp
//
// 내용: 아이템 관련 함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "item.h"
#include "monster_texture.h"
#include "const.h"
#include "potion.h"
#include "player.h"
#include "scroll.h"
#include "ring.h"
#include "save.h"
#include "weapon.h"
#include "environment.h"
#include "book.h"
#include "spellcard.h"
#include "note.h"
#include "tribe.h"
#include "armour.h"
#include "amulet.h"




item_infor::item_infor(item* item_):name(item_->name), name2(item_->second_name) ,image(item_->image),type(item_->type),weight(item_->weight),
value(item_->value), is_pile(item_->is_pile), num(item_->num), can_throw(item_->can_throw), value1(item_->value1), value2(item_->value2),
value3(item_->value3), value4(item_->value4), value5(item_->value5), value6(item_->value6), value7(item_->value7), value8(item_->value8), curse(item_->curse), artifact(item_->isArtifact())
{};

item_infor::item_infor(item* item_, int num_):name(item_->name), name2(item_->second_name) ,image(item_->image),type(item_->type),weight(item_->weight*num_/item_->num),
value(item_->value), is_pile(item_->is_pile), num(num_), can_throw(item_->can_throw), value1(item_->value1), value2(item_->value2),
value3(item_->value3), value4(item_->value4), value5(item_->value5), value6(item_->value6), value7(item_->value7), value8(item_->value8), curse(item_->curse), artifact(item_->isArtifact())
{};






item::item()
:name(LOC_SYSTEM_NONE_STRING), second_name(LOC_NONE), image(NULL), equip_image(NULL), position(0,0),prev_position(0,0), type(ITM_WEAPON_FIRST), weight(0), value(0),
is_pile(false), num(0), id('a'), prev_sight(false), not_find(true), now_find(false), curse(false), identify(false), identify_curse(false), 
can_throw(false), drop(false), throw_item(false), hamme_gift(false), waste(10000), delay_turn(0), value0(0), value1(0), value2(0), value3(0), value4(0), value5(0), value6(0), value7(0), value8(0),
atifact_vector()
{

}

item::item(const coord_def &c, const item_infor &t)
:id('a')
{	
	name = t.name;
	second_name = t.name2;

	position = c;
	prev_position = c;
	image = t.image;
	equip_image = t.equip_image;
	type = t.type;
	weight = t.weight;
	value = t.value;
	is_pile = t.is_pile;
	num = t.num;
	prev_sight = false;
	not_find = true;
	now_find = false;
	curse = t.curse;
	identify = false;
	if((type >= ITM_THROW_FIRST && type < ITM_THROW_LAST) || type == ITM_POTION ||type == ITM_FOOD||type == ITM_SCROLL||type == ITM_SPELL||type == ITM_MISCELLANEOUS)
		identify_curse = true;
	else
		identify_curse = false;
	can_throw = t.can_throw;
	drop = false;
	throw_item = false;
	hamme_gift = false;
	value0 = t.value0;
	value1 = t.value1;
	value2 = t.value2;
	value3 = t.value3;
	value4 = t.value4;
	value5 = t.value5;
	value6 = t.value6;
	value7 = t.value7;
	value8 = t.value8;
	waste = 10000;

}
void item_infor::SaveDatas(FILE *fp)
{
	name.SaveDatas(fp);
	name2.SaveDatas(fp);	
	SaveData<int>(fp, texturetoint(image));
	SaveData<int>(fp, texturetoint(equip_image));
	SaveData<item_type>(fp, type);
	SaveData<float>(fp, weight);
	SaveData<int>(fp, value);
	SaveData<bool>(fp, is_pile);
	SaveData<int>(fp, num);	
	SaveData<bool>(fp, can_throw);
	SaveData<int>(fp, value0);
	SaveData<int>(fp, value1);
	SaveData<int>(fp, value2);
	SaveData<int>(fp, value3);
	SaveData<int>(fp, value4);
	SaveData<int>(fp, value5);
	SaveData<int>(fp, value6);
	SaveData<int>(fp, value7);
	SaveData<int>(fp, value8);	
	SaveData<bool>(fp, curse);
	SaveData<bool>(fp, artifact);
}
void item_infor::LoadDatas(FILE *fp)
{
	name.LoadDatas(fp);
	name2.LoadDatas(fp);	
	int it; 
	LoadData<int>(fp, it);
	image = inttotexture(it);
	LoadData<int>(fp, it);
	equip_image = inttotexture(it);
	LoadData<item_type>(fp, type);
	LoadData<float>(fp, weight);
	LoadData<int>(fp, value);
	LoadData<bool>(fp, is_pile);
	LoadData<int>(fp, num);	
	LoadData<bool>(fp, can_throw);
	LoadData<int>(fp, value0);
	LoadData<int>(fp, value1);
	LoadData<int>(fp, value2);
	LoadData<int>(fp, value3);
	LoadData<int>(fp, value4);
	LoadData<int>(fp, value5);
	LoadData<int>(fp, value6);
	LoadData<int>(fp, value7);
	LoadData<int>(fp, value8);	
	LoadData<bool>(fp, curse);
	LoadData<bool>(fp, artifact);
}
void item::SaveDatas(FILE *fp)
{
	name.SaveDatas(fp);
	second_name.SaveDatas(fp); 
	SaveData<int>(fp, texturetoint(image));
	SaveData<int>(fp, texturetoint(equip_image));
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<int>(fp, prev_position.x);
	SaveData<int>(fp, prev_position.y);
	SaveData<item_type>(fp, type);
	SaveData<float>(fp, weight);
	SaveData<int>(fp, value);
	SaveData<bool>(fp, is_pile);
	SaveData<int>(fp, num);
	SaveData<char>(fp, id);
	SaveData<bool>(fp, prev_sight);
	SaveData<bool>(fp, not_find);
	SaveData<bool>(fp, now_find);
	SaveData<bool>(fp, curse);
	SaveData<bool>(fp, identify);
	SaveData<bool>(fp, identify_curse);
	SaveData<bool>(fp, can_throw);
	SaveData<bool>(fp, drop);
	SaveData<bool>(fp, throw_item);
	SaveData<bool>(fp, hamme_gift);
	SaveData<int>(fp, waste);
	SaveData<int>(fp, delay_turn);
	SaveData<int>(fp, value0);
	SaveData<int>(fp, value1);
	SaveData<int>(fp, value2);
	SaveData<int>(fp, value3);
	SaveData<int>(fp, value4);
	SaveData<int>(fp, value5);
	SaveData<int>(fp, value6);
	SaveData<int>(fp, value7);
	SaveData<int>(fp, value8);
	
	SaveData<int>(fp, atifact_vector.size());
	for(vector<atifact_infor>::iterator it=atifact_vector.begin();it!=atifact_vector.end();it++)
	{
		(*it).SaveDatas(fp);
	}

	
}
void item::LoadDatas(FILE *fp)
{
	name.LoadDatas(fp);
	second_name.LoadDatas(fp);
	int it;
	LoadData<int>(fp, it);
	image = inttotexture(it);
	LoadData<int>(fp, it);
	equip_image = inttotexture(it);
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<int>(fp, prev_position.x);
	LoadData<int>(fp, prev_position.y);
	LoadData<item_type>(fp, type);
	LoadData<float>(fp, weight);
	LoadData<int>(fp, value);
	LoadData<bool>(fp, is_pile);
	LoadData<int>(fp, num);
	LoadData<char>(fp, id);
	LoadData<bool>(fp, prev_sight);
	LoadData<bool>(fp, not_find);
	LoadData<bool>(fp, now_find);
	LoadData<bool>(fp, curse);
	LoadData<bool>(fp, identify);
	LoadData<bool>(fp, identify_curse);
	LoadData<bool>(fp, can_throw);
	LoadData<bool>(fp, drop);
	LoadData<bool>(fp, throw_item);
	LoadData<bool>(fp, hamme_gift);
	LoadData<int>(fp, delay_turn);
	LoadData<int>(fp, waste);
	LoadData<int>(fp, value0);
	LoadData<int>(fp, value1);
	LoadData<int>(fp, value2);
	LoadData<int>(fp, value3);
	LoadData<int>(fp, value4);
	LoadData<int>(fp, value5);
	LoadData<int>(fp, value6);
	LoadData<int>(fp, value7);
	LoadData<int>(fp, value8);

	int size_;
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		atifact_infor temp;
		temp.LoadDatas(fp);
		atifact_vector.push_back(temp);
	}
}

string item::GetName(int num_)
{
	bool overwriteName = false;
	string temp;

	if(type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST)
	{	
		if(identify)
		{
			std::ostringstream ss;
			ss << (value4 >= 0 ? '+' : '-') << abs(value4) << " ";
			temp += ss.str();
		}
		else if(!value6 && !second_name.isEmpty())
		{
			temp += second_name.getName() + " ";
		}
	}
	if(type>=ITM_ARMOR_FIRST && type<ITM_ARMOR_LAST)
	{		
		if(identify)
		{
			std::ostringstream ss;
			ss << (value4 >= 0 ? '+' : '-') << abs(value4) << " ";
			temp += ss.str();
		}
		else if(!second_name.isEmpty())
		{
			temp += second_name.getName() + " ";
		}
	}

	if(type==ITM_POTION) {		
		if(iden_list.potion_list[value1].iden)  {
			temp += LocalzationManager::locString(potion_iden_string[value1]);
		} else {
			temp += LocalzationManager::locString(potion_uniden_string[iden_list.potion_list[value1].color]);				
		}
		overwriteName = true;
	}
	if(type==ITM_SCROLL) {
		if(iden_list.scroll_list[value1].iden == 3)  {
			temp += LocalzationManager::locString(scroll_iden_string[value1]);
		} else {
			temp += LocalzationManager::locString(scroll_uniden_string[iden_list.scroll_list[value1].type]);				
		}
		overwriteName = true;
	}
	if(type==ITM_RING)
	{			
		if(!isArtifact())
		{
			if(isRingGotValue((ring_type)value1) && iden_list.ring_list[value1].iden == 2 && identify)
			{
				if(iden_list.ring_list[value1].iden == 2)  {
					temp += LocalzationManager::formatString(ring_iden_string[value1], PlaceHolderHelper((value2>=0?"+":"-")+ to_string(abs(value2)) + " "));
				} else {
					temp += LocalzationManager::formatString(ring_uniden_string[iden_list.ring_list[value1].type], PlaceHolderHelper((value2>=0?"+":"-")+ to_string(abs(value2)) + " "));				
				}
			} else if(iden_list.ring_list[value1].iden == 2)  {
				temp += LocalzationManager::locString(ring_iden_string[value1]);
			} else {
				temp += LocalzationManager::locString(ring_uniden_string[iden_list.ring_list[value1].type]);				
			}
			overwriteName = true;
		}
		else if(!second_name.isEmpty())
		{
			temp += second_name.getName() + " ";
		}
	}
	




	if(type==ITM_SPELL)
	{
		if(iden_list.spellcard_list[value2].iden == 2)
			temp+=SpellcardName((spellcard_evoke_type)value2);
	}
	if(type==ITM_AMULET)
	{
		if(iden_list.amulet_list[value1].iden == 2)  {
			temp += LocalzationManager::locString(amulet_iden_string[value1]);
		} else {
			temp += LocalzationManager::locString(amulet_uniden_string[iden_list.amulet_list[value1].type]);
		}
		overwriteName = true;
	}
	if(!isArtifact() && type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST && value6)
	{
		temp += LocalzationManager::formatString(GetBrandString((weapon_brand)value5, false), PlaceHolderHelper(name.getName()));
		overwriteName = true;
	}
	if(!overwriteName) {
		temp += name.getName();
	}


	if(identify_curse && ((type>=ITM_WEAPON_FIRST && type< ITM_WEAPON_LAST)||(type>=ITM_ARMOR_FIRST && type< ITM_ARMOR_LAST)||(type>=ITM_JEWELRY_FIRST && type< ITM_JEWELRY_LAST)))
	{
		if( (((type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST) || (type>=ITM_ARMOR_FIRST && type< ITM_ARMOR_LAST)) && !identify) || curse || (type>=ITM_JEWELRY_FIRST && type< ITM_JEWELRY_LAST))
		{
			if(curse || !isArtifact()) {
				if(curse) {
					temp = LocalzationManager::formatString(LOC_SYSTEM_ITEM_CURSED,
						PlaceHolderHelper(temp));
				} else {					
					temp = LocalzationManager::formatString(LOC_SYSTEM_ITEM_UNCURSED,
						PlaceHolderHelper(temp));
				}
			}
		}
	}
	if(is_pile && num >1 && num_ != -2)
	{
		temp = LocalzationManager::formatString(LOC_SYSTEM_ITEM_PILED, 
			PlaceHolderHelper(to_string(num_!=-1?num_!=0?num_:num:num)),
			PlaceHolderHelper(temp));
	}

	if (type == ITM_AMULET)
	{
		if (iden_list.amulet_list[value1].iden == 2 && value1 == AMT_OCCULT && value3 > 0) {
			temp += " {";
			temp += getOccultName((occult_type)value2);
			temp += "}";
		}
	}
	if(!isArtifact() && ((type==ITM_SCROLL && iden_list.scroll_list[value1].iden == 1) || (type==ITM_RING && iden_list.ring_list[value1].iden == 1)))
		temp += "("+LocalzationManager::locString(LOC_SYSTEM_ITEM_USED)+")";
	if(!isArtifact() && (type==ITM_SCROLL && iden_list.scroll_list[value1].iden == 2))
		temp += "("+LocalzationManager::locString(LOC_SYSTEM_ITEM_SELECTED_USED)+")";
	if(type==ITM_SPELL)
	{
		if(identify)
		{
			char temp2[32];
			sprintf_s(temp2,32,"(%d/%d)",value1,SpellcardMaxCharge((spellcard_evoke_type)value2));
			temp += temp2;
		}
		if(!identify && value3)
		{
			std::ostringstream ss;
			if(value3>0)
				ss<<"("<<LocalzationManager::formatString(LOC_SYSTEM_ITEM_SPELLCARD_USED, PlaceHolderHelper(to_string(value3))) << ")";
			else if(value3 == -1)
				ss<<"("<<LocalzationManager::locString(LOC_SYSTEM_ITEM_SPELLCARD_EMPTY) << ")";
			else if(value3 == -2)
				ss<<"("<<LocalzationManager::locString(LOC_SYSTEM_ITEM_SPELLCARD_CHARGED) << ")";
			temp += ss.str();
		}
	}
	if(type==ITM_MISCELLANEOUS)
	{
		temp += " {" + LocalzationManager::locString(LOC_SYSTEM_ITEM_EVOKE) + "}";
	}
	if (type == ITM_AMULET && you.equipment[ET_NECK] == this)
	{
		std::ostringstream ss;
		ss << " (" << you.getAmuletPercent() << "%%)";  // ostringstream 사용
		temp += ss.str();
	}
	
	if(isArtifact() && ((type>=ITM_WEAPON_FIRST && type< ITM_WEAPON_LAST)||(type>=ITM_ARMOR_FIRST && type< ITM_ARMOR_LAST)||(type>=ITM_JEWELRY_FIRST && type< ITM_JEWELRY_LAST)))
	{ //아티펙트!
		if(identify)
		{
			string arti_ = " {";
			bool base_ = false;
			if(type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST && value6)
			{
				arti_ += LocalzationManager::locString(GetBrandString((weapon_brand)value5, true));
				base_ = true;
			}
			if(type==ITM_RING)
			{			
				arti_ += GetAtifactString((ring_type)value1,value2);
				base_ = true;
			}
			if(type >= ITM_ARMOR_BODY_FIRST && type < ITM_ARMOR_BODY_LAST)
			{
				int t_ = ArmourExceptopn((armour_kind)value5);
				if(t_ != -1)
				{
					arti_ += GetAtifactString((ring_type)t_,1);
					base_ = true;
				}
			}
			for(auto it = atifact_vector.begin(); it != atifact_vector.end(); it++)
			{
				if(base_)
					arti_ += ", ";
				else
					base_ = true;
				arti_ += GetAtifactString((ring_type)it->kind,it->value);
			}
			arti_ += "}";
			temp+=arti_;
		}
		else
		{
			temp+=" {"+ LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT) +"}";
		}
	}


	if (type == ITM_BOOK && !iden_list.books_list[value0]) {
		temp = second_name.getName() + " ";
	}

	return temp;
}

string item::GetNameString() {
	if(type == ITM_BOOK && !identify)
		return second_name.getName();
	else
		return name.getName();
}

name_infor item::GetNameInfor()
{
	if(type == ITM_BOOK && !identify)
		return second_name;
	else
		return name;
}
textures* item::GetEquipTexture()
{
	return equip_image;
}
const D3DCOLOR item::item_color()	
{	
	D3DCOLOR return_ = CL_STAT;

	switch(type)
	{
	case ITM_POTION:
		if (you.s_pure_turn && you.s_pure >= 30)
		{
			return_ = CL_bad;
		}
		else if(iden_list.potion_list[value1].iden)
		{
			int color_ = isGoodPotion((potion_type)value1);
			return_ = (color_ == 3)?CL_magic:((color_ == 2)?CL_warning:((color_ == 1)?CL_help:((color_ == 0)?CL_bad:((color_ == -1)?CL_small_danger:(CL_STAT)))));
		}
		break;
	case ITM_SCROLL:
		if(iden_list.scroll_list[value1].iden == 3)
		{
			int color_ = isGoodScroll((scroll_type)value1);
			return_ = (color_ == 3)?CL_magic:((color_ == 2)?CL_warning:((color_ == 1)?CL_help:((color_ == 0)?CL_bad:((color_ == -1)?CL_small_danger:(CL_STAT)))));

			if (you.s_pure_turn && you.s_pure >= 20)
			{
				if (value1 != SCT_ENCHANT_WEAPON_1 &&
					value1 != SCT_ENCHANT_WEAPON_2 &&
					value1 != SCT_ENCHANT_ARMOUR &&
					value1 != SCT_IDENTIFY &&
					value1 != SCT_BRAND_WEAPON &&
					value1 != SCT_REMOVE_CURSE &&
					value1 != SCT_AMNESIA)
					return_ = CL_bad;
			}

			if(you.god == GT_YUKARI && (value1 == SCT_TELEPORT || value1 == SCT_BLINK))
			{
				return_ = CL_danger;
			}
		}
		break;
	case ITM_RING:
		if(iden_list.ring_list[value1].iden == 2) //식별안되도 색깔로 구별가능?
		{
			int color_ = isGoodRing((ring_type)value1, identify?value2:1);
			return_ = (color_ == 0)?CL_bad:((color_ == -1)?CL_small_danger:CL_STAT);
		}
		break;
	case ITM_SPELL:
		if (you.s_pure_turn && you.s_pure >= 10 && !you.GetProperty(TPT_PURE_SYSTEM))
		{
			return_ = CL_bad;
		}
		else if(iden_list.spellcard_list[value2].iden ==2 &&
			value2 == SPC_V_SUN && you.tribe == TRI_VAMPIRE){
			return_ = CL_magic;
		}
		break;
	case ITM_AMULET:
		if(iden_list.amulet_list[value1].iden == 2)
		{
			int color_ = isGoodAmulet((amulet_type)value1, identify?value2:1);
			return_ = (color_ == 0)?CL_bad:((color_ == -1)?CL_small_danger: CL_STAT);
		}
		break;
	default:
		break;
	}
	if(((type>=ITM_WEAPON_FIRST && type< ITM_WEAPON_LAST)||(type>=ITM_ARMOR_FIRST && type< ITM_ARMOR_LAST)) && !second_name.isEmpty() && !identify)
	{
		return_ = CL_white_blue;
	}

	if(identify_curse && ((type>=ITM_WEAPON_FIRST && type< ITM_WEAPON_LAST)||(type>=ITM_ARMOR_FIRST && type< ITM_ARMOR_LAST)||(type>=ITM_JEWELRY_FIRST && type< ITM_JEWELRY_LAST)))
	{ //저주식별된상태에 무기,방어구, 장신구일때
		if(return_ == CL_STAT || curse)
		{ //ㅇㅇ
			return_ = curse?CL_danger:CL_good;
		}
	}

	if(isArtifact())
	{
		if(return_ != CL_danger)
			return_ = CL_normal;
	}
	if((type>=ITM_ARMOR_FIRST && type< ITM_ARMOR_LAST) && !you.isImpossibeEquip(GetArmorType(),false))
	{
		return_ = CL_bad;
	}
	if(GetArmorType() == ET_ARMOR && type >= ITM_ARMOR_BODY_ARMOUR_2 && type <= ITM_ARMOR_BODY_ARMOUR_3 )
	{
		int your_size_ = you.GetProperty(TPT_SIZE);
		if(your_size_>0)
		{
			return_ = CL_bad;
		}
		else if(your_size_<0)
		{
			return_ = CL_bad;
		}
	}

	return return_;
}



bool item::draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_)
{
	if (image) {
		bool return_ = image->draw(pSprite, x_, y_, 255);
		if (type == ITM_POTION) {
			if (iden_list.potion_list[value1].iden) {
				img_item_potion_kind[min(PT_MAX-1,max(0,value1))].draw(pSprite, x_, y_, 255);
			}

		}
		else if (type == ITM_SCROLL) {
			if (iden_list.scroll_list[value1].iden == 3) {
				img_item_scroll_kind[min(SCT_MAX - 1, max(0, value1))].draw(pSprite, x_, y_, 255);
			}
		}
		else if (type == ITM_AMULET) {
			if (iden_list.amulet_list[value1].iden) {
				img_item_amulet_kind[min(AMT_MAX - 1, max(0, value1))].draw(pSprite, x_, y_, 255);
			}
		}
		else if (type == ITM_RING) {
			if (iden_list.ring_list[value1].iden && !isArtifact()) {
				img_item_ring_kind[min(RGT_MAX - 1, max(0, value1))].draw(pSprite, x_, y_, 255);
			}
		}
		return return_;
	}
	else
		return false;
}


bool item::isSimpleType(item_type_simple type_)
{
	switch(type_)
	{
	case ITMS_WEAPON:
		return (type>=ITM_WEAPON_FIRST && type<=ITM_WEAPON_LAST);
		break;
	case ITMS_THROW:
		return (type>=ITM_THROW_FIRST && type<=ITM_THROW_LAST);
		break;
	case ITMS_ARMOR:
		return (type>=ITM_ARMOR_FIRST && type<=ITM_ARMOR_LAST);
		break;
	case ITMS_POTION:
		return (type==ITM_POTION);
		break;
	case ITMS_FOOD:
		return (type==ITM_FOOD);
		break;
	case ITMS_SCROLL:
		return (type==ITM_SCROLL);
		break;
	case ITMS_SPELL:
		return (type==ITM_SPELL);
		break;
	case ITMS_JEWELRY:
		return (type>=ITM_JEWELRY_FIRST && type<=ITM_JEWELRY_LAST);
		break;
	case ITMS_BOOK:
		return (type>=ITM_BOOK_FIRST && type<=ITM_BOOK_LAST);
		break;
	case ITMS_MISCELLANEOUS:
		return (type==ITM_MISCELLANEOUS);
		break;
	case ITMS_GOAL:
		return (type==ITM_GOAL || type==ITM_ORB);
		break;
	case ITMS_OTHER:
		return (type == ITM_ETC);
		break;
	default:
		return false;
		break;
	}
}
bool item::isRightType(equip_type type_)
{
	switch(type_)
	{
	case ET_WEAPON:
		return (type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST);
	case ET_THROW:
		return true;
	case ET_ARMOR:
		return (type>=ITM_ARMOR_BODY_FIRST && type<ITM_ARMOR_BODY_LAST);
	case ET_SHIELD:
		return (type == ITM_ARMOR_SHIELD);
	case ET_HELMET:
		return (type == ITM_ARMOR_HEAD);
	case ET_CLOAK:
		return (type == ITM_ARMOR_CLOAK);
	case ET_GLOVE:
		return (type == ITM_ARMOR_GLOVE);
	case ET_BOOTS:
		return (type == ITM_ARMOR_BOOT);
	case ET_NECK:
		return (type == ITM_AMULET);
	case ET_LEFT:
	case ET_RIGHT:
		return (type == ITM_RING);
	default:
		return false;
	}
}

equip_type item::GetArmorType()
{
	if(type>=ITM_ARMOR_BODY_FIRST && type<ITM_ARMOR_BODY_LAST)
		return ET_ARMOR;
	else if(type == ITM_ARMOR_SHIELD)
		return ET_SHIELD;
	else if(type == ITM_ARMOR_HEAD)
		return ET_HELMET;
	else if(type == ITM_ARMOR_CLOAK)
		return ET_CLOAK;
	else if(type == ITM_ARMOR_GLOVE)
		return ET_GLOVE;
	else if(type == ITM_ARMOR_BOOT)
		return ET_BOOTS;
	else if(type == ITM_AMULET)
		return ET_NECK;
	else
		return ET_WEAPON;
}

bool item::SameItem(const item &item_)
{
	if(type == ITM_GOAL)
		return (type == item_.type && value2 == item_.value2 && value3 == item_.value3 && value4 == item_.value4 && value5 == item_.value5 && value6 == item_.value6 &&  value7 == item_.value7 && value8 == item_.value8);
	else
		return (type == item_.type && value1 == item_.value1 && value2 == item_.value2 && value3 == item_.value3 && value4 == item_.value4 && value5 == item_.value5 && value6 == item_.value6 &&  value7 == item_.value7 && value8 == item_.value8);
}
float item::GetStabPercent()
{
	//if(type >= ITM_WEAPON_FIRST && type <= ITM_WEAPON_CLOSE)
		return 1.0f;
	//float base = 1.0f;
	//switch(type)
	//{
	//case ITM_WEAPON_SHORTBLADE:
	//	base*=2.0f;
	//case ITM_WEAPON_LONGBLADE:
	//	base*=1.4f;
	//case ITM_WEAPON_MACE:
	//case ITM_WEAPON_AXE:
	//case ITM_WEAPON_SPEAR:
	//	base*=1.0f;
	//}
	////if(value5>12)
	////	base += (value5-12)*-0.05f;
	//if(base<0.5f)
	//	base = 0.5f;
	//return base;
}
int item::GetValue(int i)
{
	switch(i)
	{
	case 1:
		return value1;
	case 2:
		return value2;
	case 3:
		return value3;
	case 4:
		return value4;
	case 5:
		return value5;
	case 6:
		return value6;
	case 7:
		return value7;
	case 8:
		return value8;
	default:
		return 0;
	}
}
void item::TurnSave()
{
	delay_turn = you.turn;
}
void item::TurnLoad()
{ //나중에 주인공 근처로 옮겨오는것도 생각한다.
	int temp_turn = you.turn - delay_turn;
	if (now_find)
	{
		if (you.god == GT_JOON_AND_SION)
		{
			waste -= (you.god_value[GT_JOON_AND_SION][0] == 2 ? 100 : 10) * temp_turn;
		}
	}
}
bool item::isweapon()
{
	return (type >= ITM_WEAPON_FIRST && type < ITM_WEAPON_LAST);
}

bool item::isarmor()
{
	return (type >= ITM_ARMOR_FIRST && type < ITM_ARMOR_LAST);
}
bool item::isjewerly()
{
	return (type >= ITM_JEWELRY_FIRST && type < ITM_JEWELRY_LAST);
}
bool item::isring()
{
	return (type == ITM_RING);
}
bool item::isiden()
{
	if(type == ITM_POTION)
	{
		return iden_list.potion_list[value1].iden;
	}
	else if(type == ITM_SCROLL)
	{
		return (iden_list.scroll_list[value1].iden == 3);
	}	
	else if(type == ITM_BOOK)
	{
		return identify;
	}
	else if(type == ITM_RING)
	{
		return identify && identify_curse && iden_list.ring_list[value1].iden == 2;

	}
	else if (type == ITM_AMULET)
	{
		if (value1 == AMT_OCCULT && value3 == 0) {
			return false;
		}
		return identify && identify_curse;

	}
	else if(type >= ITM_THROW_FIRST && type <= ITM_THROW_LAST)
	{
		return true;
	}
	else if(type == ITM_FOOD)
	{
		return true;
	}
	else if(type == ITM_MISCELLANEOUS)
	{
		return true;
	}

	else if(type == ITM_GOAL ||	type == ITM_ORB)
	{
		return true;
	}
	else if(type == ITM_ETC)
	{
		return true;
	}



	return (identify && identify_curse);
}
bool item::isautopick()
{
	if(drop)
		return false;
	if(throw_item)
		return true;
	switch(type)
	{
	case ITM_POTION:
		if(iden_list.potion_list[value1].iden)
		{	
			return iden_list.autopickup[value1 + IDEN_CHECK_POTION_START];
			/*if(isGoodPotion((potion_type)value1)>0 || you.god == GT_EIRIN || (you.god == GT_YUUGI && value1 == PT_ALCOHOL))
			{
				return true;
			}
			else
				return false;*/
		}
		else
			return true;
	case ITM_FOOD:
		return iden_list.autopickup[(value1==0?0:1) + IDEN_CHECK_ETC_START];
	case ITM_SCROLL:
		if(iden_list.scroll_list[value1].iden == 3)
		{
			return iden_list.autopickup[value1 + IDEN_CHECK_SCROLL_START];
			/*if(you.god == GT_YUKARI && (value1 == SCT_TELEPORT || value1 == SCT_BLINK))
			{
				return false;
			}
			else if(isGoodScroll((scroll_type)value1)>0)
			{
				return true;
			}
			else
				return false;*/
		}
		else
			return true;
	case ITM_SPELL:
		if (iden_list.spellcard_list[value1].iden == 2)
		{
			return iden_list.autopickup[value1 + IDEN_CHECK_SPC_START];
		}
		return true;
	case ITM_AMULET:
		if (iden_list.amulet_list[value1].iden == 2)
		{
			return iden_list.autopickup[value1 + IDEN_CHECK_AMULET_START];
		}
		else
			return true;
	case ITM_RING:
		if(iden_list.ring_list[value1].iden == 2)
		{
			return iden_list.autopickup[value1 + IDEN_CHECK_RING_START];
			/*if(isGoodRing((ring_type)value1,identify?value2:1)>0)
			{
				if(isPickableRIng((ring_type)value1)>0)
					return true;
				else
					return false;
			}
			else
				return false;*/
		}
		else
			return true;
	case ITM_BOOK:
	{
		if (iden_list.books_list[value0]) {
			return iden_list.autopickup[value0 + 1 + IDEN_CHECK_BOOK_START];
		}
		return iden_list.autopickup[IDEN_CHECK_BOOK_START];
	}
	case ITM_MENUAL:
		return true;
	case ITM_THROW_TANMAC:
		return iden_list.autopickup[value4 + 2 +IDEN_CHECK_ETC_START];
	default:
		break;
	}
	return false;
}

bool item::isArtifact()
{
	return !atifact_vector.empty();
}
bool item::isChargable()
{
	if(type == ITM_SPELL)
	{
		if(value1<SpellcardMaxCharge((spellcard_evoke_type)value2))
			return true;
	}
	return false;

}
bool item::isEvokable()
{
	if (type == ITM_SPELL || type == ITM_MISCELLANEOUS)
		return true;
	if (type == ITM_AMULET) {
		if (isCanEvoke((amulet_type)value1) && you.equipment[ET_NECK] == this && you.getAmuletPercent() >= 100) {
			return true;
		}
	}
	return false;

}
void item::Identify()
{
	bool prev_iden = identify;
	identify = true;
	identify_curse = true;
	switch(type)
	{
	case ITM_RING:
		if(!isArtifact())
			iden_list.ring_list[value1].iden = 2;
		if(!prev_iden && you.isequip(this))
			unidenequipring((ring_type)value1, value2*(-1));
		you.auto_equip_iden();
		break;
	case ITM_SPELL:		
		iden_list.spellcard_list[value2].iden = 2;
		break;
	case ITM_AMULET:
		iden_list.amulet_list[value1].iden = 2;
		if(!prev_iden && you.isequip(this))
			unidenequipamulet((amulet_type)value1, value2*(-1));
		you.auto_equip_iden();
		if(value1 == AMT_OCCULT) 
		{
			value3++;
		}
		break;
	case ITM_SCROLL:
		iden_list.scroll_list[value1].iden = 3;
		break;
	case ITM_POTION:
		iden_list.potion_list[value1].iden = true;
		break;
	case ITM_BOOK:
		if (value0 >= 0) {
			iden_list.books_list[value0] = true;
		}
		break;
	default:
		break;
	}
	if(type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST && value5 && value6)
	{
		value6 = -1;
	}
}
void item::autoIdentify()
{
	if(type == ITM_RING)
	{
		if(iden_list.ring_list[value1].iden == 2)
			Identify();
	}
	if(type == ITM_AMULET)
	{
		equipIdentify();
	}
}
void item::equipIdentify()
{
	if (type == ITM_AMULET)
	{
		bool prev_iden = identify;
		identify = true;
		identify_curse = true;
		iden_list.amulet_list[value1].iden = 2;
		if (!prev_iden && you.isequip(this))
			unidenequipamulet((amulet_type)value1, value2*(-1));
		you.auto_equip_iden();
	}
	else {
		Identify();
	}
}
void item::income_view()
{
	if(you.god == GT_HINA && !you.GetPunish(GT_HINA))
	{
		identify_curse = true;
		if(curse)
		{
			Identify();
		}
	}
}
bool item::Curse(bool equip_,equip_type kind_)
{
	if(curse)
		return false;
	bool possible_curse_= false;
	if(!equip_ && ((type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST)||(type>=ITM_ARMOR_FIRST && type<ITM_ARMOR_LAST)||(type>=ITM_JEWELRY_FIRST && type<ITM_JEWELRY_LAST)))
		possible_curse_ = true;
	else if(equip_ && kind_ == ET_WEAPON && (type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST))
		possible_curse_ = true;
	else if(equip_ && (kind_ >= ET_ARMOR && kind_ < ET_ARMOR_END ) && (type>=ITM_ARMOR_FIRST && type<ITM_ARMOR_LAST))
		possible_curse_ = true;
	else if(equip_ && (kind_ >= ET_JEWELRY && kind_ < ET_JEWELRY_END ) && (type>=ITM_JEWELRY_FIRST && type<ITM_JEWELRY_LAST))
		possible_curse_ = true;
	if(possible_curse_)
	{
		identify_curse = true;
		curse = true;
		return true;
	}
	else
		return false;

}
bool item::isEnhantable()
{
	if(type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST)
	{
		if(curse)
			return true;
		if(isArtifact())
			return false;
		if(value4<9)
			return true;
	}	
	else if((type>=ITM_ARMOR_FIRST && type<ITM_ARMOR_LAST))
	{
		if(curse)
			return true;
		if(isArtifact())
			return false;
		int max_enchant = 2;
		if(type>=ITM_ARMOR_BODY_FIRST && type < ITM_ARMOR_BODY_LAST)
		{
			max_enchant = value1;
		}
		else if(type == ITM_ARMOR_SHIELD)
		{
			if(value1 <= 4)
				max_enchant = 3;
			else if(value1 <= 8)
				max_enchant = 6;
			else
				max_enchant = 9;
		}
		if(value4<max_enchant)
			return true;
	}
	return false;
}
bool item::Enchant(equip_type kind_, int acc_)
{
	bool enchant_ = curse?true:false; //저주걸린템은 무조건 인챈트

	if(isArtifact())
		return enchant_; //아티펙트는 인챈트 무시

	if(kind_ == ET_WEAPON && (type>=ITM_WEAPON_FIRST && type<ITM_WEAPON_LAST))
	{
		while(acc_ && value4<9)
		{
			value4++;
			enchant_ = true;
			acc_--;
		}
	}
	else if(kind_ == ET_ARMOR && (type>=ITM_ARMOR_FIRST && type<ITM_ARMOR_LAST))
	{
		int max_enchant = 2;
		if(type>=ITM_ARMOR_BODY_FIRST && type < ITM_ARMOR_BODY_LAST)
		{
			max_enchant = value1;
		}
		else if(type == ITM_ARMOR_SHIELD)
		{
			if(value1 <= 4)
				max_enchant = 3;
			else if(value1 <= 8)
				max_enchant = 6;
			else
				max_enchant = 9;
		}

		while(acc_ && value4<max_enchant) //높을수록 확률 낮추기
		{
			value4++;
			if(type != ITM_ARMOR_SHIELD) 
			{
				if(you.equipment[GetArmorType()] == this)
					you.AcUpDown(0,1);
			}
			else
			{
				if(you.equipment[GetArmorType()] == this)
					you.ShUpDown(0,1);
			}

			enchant_ = true;
			acc_--;
		}
	}
	return enchant_;
}
bool item::pick()
{
	bool return_ = false;
	drop = false;
	if (throw_item) {
		if(type != ITM_THROW_TANMAC && can_throw)
			return_ = true;
		throw_item = false;
	}
	prev_sight = false;
	//if(type == ITM_GOAL && value1 ==0)
	//{
	//	printlog("당신은 룬을 주웠다!",true,false,false,CL_good);
	//	char temp[200];
	//	sprintf_s(temp,200,"룬을 얻었다.");
	//	AddNote(you.turn,CurrentLevelString(),temp,CL_warning);
	//	value1++;
	//}
	//if(type == ITM_ORB && value1 ==0)
	//{
	//	printlog("당신은 음양옥을 주웠다. 던전1층으로 가지고 올라가면 승리한다!",true,false,false,CL_good);
	//	char temp[200];
	//	sprintf_s(temp,200,"음양옥을 얻었다.");
	//	AddNote(you.turn,CurrentLevelString(),temp,CL_warning);
	//	value1++;
	//}
	return return_;
}
int item::action(int delay_)
{
	if(env[current_level].isInSight(position))
	{
		income_view();
		prev_sight = true;
		if(now_find)
			not_find = false;
		now_find = true;


		if(!identify)
		{
			if(type==ITM_POTION && iden_list.potion_list[value1].iden)
				identify = true;
			else if(type==ITM_SCROLL && iden_list.scroll_list[value1].iden == 3)
				identify = true;
			else if(type==ITM_RING && !isArtifact() && iden_list.ring_list[value1].iden == 2 && !isRingGotValue((ring_type)value1))
				identify = true;
			//else if(type==ITM_SPELLCARD && iden_list.scroll_list[value1].iden == 2 && !isAmuletGotValue((amulet_type)value1))
			//	identify = true;
		}

	}
	else if(prev_sight)
	{
		env[current_level].MakeShadow(prev_position,image, value1,SWT_ITEM,GetName());
		prev_sight = false;
	}
	if (now_find)
	{
		if (you.god == GT_JOON_AND_SION || you.GetPunish(GT_JOON_AND_SION))
		{
			if (type == ITM_POTION || type == ITM_SCROLL) {
				waste -= you.god_value[GT_JOON_AND_SION][0] == 2 ? 100 : 10; //기본 1000턴후에 사라짐
				//시온일땐 100턴후 사라지도록?
				if (waste <= 0) {
					env[current_level].DeleteItem(this);
					return 0;
				}
			}
		}
	}
	if(type == ITM_FOOD && value1 == 0)
	{
		value3--;
		if(value3 == 0)
		{
			env[current_level].DeleteItem(this);
			return 0;
		}
	}
	if (type == ITM_ETC && value1 == EIT_CAT_TREE) 
	{
		for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if (it->isLive() && distan_coord(it->position, position) <= 2) {
				if (it->id == MON_CHEN ||
					it->id == MON_ORIN ||
					it->id == MON_ORIN_CAT ||
					it->id == MON_ORANGE_CAT ||
					it->id == MON_WHITE_CAT ||
					it->id == MON_BLACK_CAT)
					it->s_confuse = 15;
			}
		}
		if (you.tribe == TRI_NECOMATA && distan_coord(you.position, position) <= 2) {
			if (you.s_drunken == 0) {
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_ETC_CATNIP_CONFUSE),true,false,false, CL_warning);
			}
			you.s_drunken = 15;
		}
	}

	prev_position = position;
	return 1;
}

bool item::offsetmove(const coord_def &c)
{		
	position += c;
	if(position.x >= 0 && position.x < DG_MAX_X && position.y >= 0 && position.y < DG_MAX_Y )
		return true;
	else
	{
		env[current_level].DeleteItem(this);
		return false;
	}
}


string GetItemTypeSting(item_type_simple type)
{
	switch(type)
	{
	case ITMS_WEAPON:
		return LocalzationManager::locString(item_weapon_string);
	case ITMS_THROW:
		return LocalzationManager::locString(item_throw_string);
	case ITMS_ARMOR:
		return LocalzationManager::locString(item_armor_string);
	case ITMS_POTION:
		return LocalzationManager::locString(item_potion_string);
	case ITMS_FOOD:
		return LocalzationManager::locString(item_food_string);
	case ITMS_SCROLL:
		return LocalzationManager::locString(item_scroll_string);
	case ITMS_SPELL:
		return LocalzationManager::locString(item_spell_string);
	case ITMS_JEWELRY:
		return LocalzationManager::locString(item_jewelry_string);
	case ITMS_BOOK:
		return LocalzationManager::locString(item_book_string);
	case ITMS_MISCELLANEOUS:
		return LocalzationManager::locString(item_miscellaneous_string);
	case ITMS_GOAL:
		return LocalzationManager::locString(item_goal_string);
	case ITMS_OTHER:
		return LocalzationManager::locString(item_other_string);
	default:
		return LocalzationManager::locString(item_miscellaneous_string);
	}
}