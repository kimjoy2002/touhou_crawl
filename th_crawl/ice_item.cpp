//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ice_item.cpp
//
// 내용: 치르노의 얼음 아이템
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "ice_item.h"
#include "environment.h"
#include "weapon.h"
#include "armour.h"
#include "ring.h"
#include "book.h"
#include "skill_use.h"
#include "key.h"
#include "rect.h"

extern HANDLE mutx;
extern int g_menu_select;

item MakeIceItem(ice_item_kind kind_, int power)
{
	power = max(50,min(200,power));
	int quality_ = power - 50;
	item_infor t;
	switch(kind_)
	{
	case ICE_ITEM_SWORD:
		makeitem(ITM_WEAPON_LONGBLADE,0,&t,25);
		break;
	case ICE_ITEM_DAGGER:
		makeitem(ITM_WEAPON_SHORTBLADE,0,&t,10);
		break;
	case ICE_ITEM_CRASHER:
		makeitem(ITM_WEAPON_MACE,0,&t,43);
		t.weight = 15.0f;
		t.value7 = 19;
		break;
	case ICE_ITEM_SPEAR:
		makeitem(ITM_WEAPON_SPEAR,0,&t,40);
		break;
	case ICE_ITEM_AXE:
		makeitem(ITM_WEAPON_AXE,0,&t,20);
		break;
	case ICE_ITEM_ICICLE:
		makeitem(ITM_THROW_TANMAC,0,&t,TMT_ICICLE);
		t.num = rand_int(6 + quality_/15,10 + quality_/10);
		t.weight = 0.5f*t.num;
		break;
	case ICE_ITEM_RING:
		makeitem(ITM_RING,0,&t);
		t.value1 = RGT_ICE_RESIS;
		t.value2 = 1;
		break;
	case ICE_ITEM_CROWN:
		makeitem(ITM_ARMOR_HEAD,0,&t);
		t.equip_image = &img_play_item_hat[0];
		break;
	case ICE_ITEM_CREAM:
		makeitem(ITM_FOOD,0,&t,5);
		t.num = rand_int(2 + quality_*4/150,3 + quality_*6/150);
		t.weight = 1.0f*t.num;
		break;
	case ICE_ITEM_ARMOUR:
		makeitem(ITM_ARMOR_BODY_ARMOUR_1,0,&t,AMK_NORMAL);
		t.value1++;
		break;
	case ICE_ITEM_GLOVES:
		makeitem(ITM_ARMOR_GLOVE,0,&t);
		break;
	case ICE_ITEM_BOOTS:
		makeitem(ITM_ARMOR_BOOT,0,&t);
		break;
	case ICE_ITEM_CLOAK:
		makeitem(ITM_ARMOR_CLOAK,0,&t);
		break;
	case ICE_ITEM_BOOK:
	{
		makeCustomBook(&t);
		set<int> spells_;
		random_extraction<int> cold_;
		for(int i=0;i<BOOK_LAST;i++)
		{
			for(int j=0;j<8;j++)
			{
				spell_list spell_ = (spell_list)static_book_list[i].spell[j];
				if(spell_ == SPL_NONE || SpellLevel(spell_) > 2 + quality_*7/150)
					continue;
				if(!spells_.insert(spell_).second)
					continue;
				for(int k=0;k<3;k++)
				{
					if(SpellSchool(spell_,k) == SKT_COLD)
					{
						cold_.push(spell_);
						break;
					}
				}
			}
		}
		t.value1 = cold_.GetSize()?cold_.pop():SPL_FROST;
		random_extraction<int> other_;
		for(int spell_ : spells_)
		{
			if(spell_ != t.value1)
				other_.push(spell_);
		}
		if(quality_ >= 75 && other_.GetSize())
			t.value2 = other_.pop();
		if(quality_ >= 150 && other_.GetSize())
			t.value3 = other_.pop();
		break;
	}
	case ICE_ITEM_FROG:
		makeitem(ITM_MISCELLANEOUS,0,&t,EVK_FROZEN_FROG);
		break;
	default:
		return item();
	}

	LOCALIZATION_ENUM_KEY names_[ICE_ITEM_MAX] = {
		LOC_SYSTEM_ITEM_ICE_SWORD,
		LOC_SYSTEM_ITEM_ICE_DAGGER,
		LOC_SYSTEM_ITEM_ICE_CRASHER,
		LOC_SYSTEM_ITEM_ICE_SPEAR,
		LOC_SYSTEM_ITEM_ICE_AXE,
		LOC_SYSTEM_ITEM_ICE_ICICLE,
		LOC_SYSTEM_ITEM_ICE_RING,
		LOC_SYSTEM_ITEM_ICE_CROWN,
		LOC_SYSTEM_ITEM_ICE_CREAM,
		LOC_SYSTEM_ITEM_ICE_ARMOUR,
		LOC_SYSTEM_ITEM_ICE_GLOVES,
		LOC_SYSTEM_ITEM_ICE_BOOTS,
		LOC_SYSTEM_ITEM_ICE_CLOAK,
		LOC_SYSTEM_ITEM_ICE_BOOK,
		LOC_SYSTEM_ITEM_EVOKE_ICE_FROG
	};
	t.name = name_infor(names_[kind_]);
	t.name2 = name_infor();
	t.image = &img_item_ice[kind_];
	item item_(you.position,t);
	if(item_.isweapon() || item_.isarmor() || item_.isring())
	{
		artifact_type penalty_ = ART_MAX_ATIFACT;
		if(randA(1) == 0)
		{
			random_extraction<artifact_type> penalties_;
			penalties_.push(ART_FIRE_RESIS,6);
			penalties_.push(ART_STR);
			penalties_.push(ART_DEX);
			penalties_.push(ART_INT);
			penalty_ = penalties_.pop();
		}
		random_extraction<artifact_type> properties_;
		if(penalty_ != ART_FIRE_RESIS)
			properties_.push(ART_FIRE_RESIS,1);
		properties_.push(ART_ELEC_RESIS,3);
		properties_.push(ART_POISON_RESIS,3);
		properties_.push(ART_MAGIC_RESIS,3);
		properties_.push(ART_CONFUSE_RESIS,3);
		if(!item_.isring())
			properties_.push(ART_ICE_RESIS,3);
		if(quality_ >= 40)
		{
			if(penalty_ != ART_STR)
				properties_.push(ART_STR,3);
			if(penalty_ != ART_DEX)
				properties_.push(ART_DEX,3);
			if(penalty_ != ART_INT)
				properties_.push(ART_INT,3);
			properties_.push(ART_AC,3);
			properties_.push(ART_EV,3);
		}
		int num_ = rand_int(1,2) + quality_/50;
		// 반지의 기본 냉기저항도 옵션 하나로 센다.
		if(item_.isring())
			num_ = max(1,num_-1);
		for(int i=0;i<num_ && properties_.GetSize();i++)
		{
			artifact_type prop_ = properties_.pop();
			int value_ = 1;
			if(prop_ == ART_STR || prop_ == ART_DEX || prop_ == ART_INT ||
				prop_ == ART_AC || prop_ == ART_EV)
				value_ = rand_int(1,1+quality_/40);
			item_.atifact_vector.push_back(atifact_infor(prop_,value_));
		}
		if(penalty_ != ART_MAX_ATIFACT)
			item_.atifact_vector.push_back(atifact_infor(penalty_,-1));
		item_.artifact_guid = randA(~(1 << 31));
		item_.item_tag.push_back(LOC_SYSTEM_TAG_RANDART);
		item_.second_name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT);
		if(item_.isweapon())
		{
			item_.value5 = WB_COLD;
			item_.value6 = -1;
			item_.value4 = rand_int(quality_/50,quality_*9/150);
		}
		else if(item_.isarmor())
			item_.value4 = rand_int(0,quality_*item_.value1/150);
	}
	item_.identify = true;
	item_.identify_curse = true;
	return item_;
}

LOCALIZATION_ENUM_KEY GetIceItemDescription(item* item_)
{
	switch(item_->name.getSystemKey())
	{
	case LOC_SYSTEM_ITEM_ICE_SWORD:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_SWORD;
	case LOC_SYSTEM_ITEM_ICE_DAGGER:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_DAGGER;
	case LOC_SYSTEM_ITEM_ICE_CRASHER:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_CRASHER;
	case LOC_SYSTEM_ITEM_ICE_SPEAR:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_SPEAR;
	case LOC_SYSTEM_ITEM_ICE_AXE:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_AXE;
	case LOC_SYSTEM_ITEM_ICE_ICICLE:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_ICICLE;
	case LOC_SYSTEM_ITEM_ICE_RING:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_RING;
	case LOC_SYSTEM_ITEM_ICE_CROWN:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_CROWN;
	case LOC_SYSTEM_ITEM_ICE_CREAM:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_CREAM;
	case LOC_SYSTEM_ITEM_ICE_ARMOUR:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_ARMOUR;
	case LOC_SYSTEM_ITEM_ICE_GLOVES:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_GLOVES;
	case LOC_SYSTEM_ITEM_ICE_BOOTS:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_BOOTS;
	case LOC_SYSTEM_ITEM_ICE_CLOAK:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_CLOAK;
	case LOC_SYSTEM_ITEM_ICE_BOOK:
		return LOC_SYSTEM_ITEM_DESCRIPTION_ICE_BOOK;
	default:
		return LOC_NONE;
	}
}

bool CreateIceItem(int power)
{
	if(power <= 0)
		return false;
	random_extraction<ice_item_kind> kinds_;
	for(int i=0;i<ICE_ITEM_MAX;i++)
		kinds_.push((ice_item_kind)i);
	item items_[3];
	for(int i=0;i<3;i++)
	{
		items_[i] = MakeIceItem(kinds_.pop(),power);
		items_[i].id = 'a'+i;
	}
	bool examine_ = false;
	bool redraw_ = true;
	changedisplay(DT_GAME);
	g_menu_select = -1;
	while(true)
	{
		if(redraw_)
		{
			WaitForSingleObject(mutx,INFINITE);
			deletelog();
			printlog(LocalzationManager::locString(examine_?LOC_SYSTEM_CIRNO_ICE_CREATE_EXAMINE:LOC_SYSTEM_CIRNO_ICE_CREATE_SELECT)+" ",false,false,true,CL_help);
			printlog("? - "+LocalzationManager::locString(examine_?LOC_SYSTEM_CIRNO_ICE_CREATE_SELECT_MODE:LOC_SYSTEM_CIRNO_ICE_CREATE_EXAMINE_MODE),false,false,true,CL_help,'?');
			printlog(" / ",false,false,true,CL_help);
			printlog("Esc - "+LocalzationManager::locString(LOC_SYSTEM_CANCLE),true,false,true,CL_help,VK_ESCAPE);
			for(int i=0;i<3;i++)
				printlog(string(1,'a'+i)+" - "+items_[i].GetName(),true,false,true,items_[i].item_color(),'a'+i);
			startSelection({'a','b','c'},true);
			ReleaseMutex(mutx);
			redraw_ = false;
		}
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);
		bool description_ = examine_;
		if(key_ == VK_ESCAPE || key_ == GVK_BUTTON_B || key_ == GVK_BUTTON_B_LONG)
		{
			endSelection();
			deletelog();
			g_menu_select = -1;
			return false;
		}
		if(key_ == '?')
		{
			examine_ = !examine_;
			redraw_ = true;
			continue;
		}
		if(key_ == VK_DOWN || key_ == VK_UP || key_ == VK_RIGHT || key_ == VK_LEFT)
		{
			if(key_ == VK_DOWN || key_ == VK_RIGHT)
				g_menu_select = (g_menu_select+1)%3;
			else
				g_menu_select = g_menu_select < 0?2:(g_menu_select+2)%3;
			continue;
		}
		if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG)
		{
			description_ = description_ || key_ == GVK_BUTTON_A_LONG;
			key_ = g_menu_select >= 0 && g_menu_select < 3?'a'+g_menu_select:0;
		}
		if(key_ == -1 && inputedKey.mouse == MKIND_ITEM_DESCRIPTION)
		{
			key_ = inputedKey.val1;
			description_ = true;
		}
		if(key_ < 'a' || key_ > 'c')
			continue;
		int select_ = key_ - 'a';
		if(description_)
		{
			endSelection();
			iteminfor_(&items_[select_],true);
			changedisplay(DT_GAME);
			redraw_ = true;
			continue;
		}
		endSelection();
		deletelog();
		printlog(items_[select_].GetName(),true,false,true,CL_help);
		if(ynPrompt(LOC_SYSTEM_CIRNO_ICE_CREATE_CONFIRM,LOC_SYSTEM_CANCLE_EX,CL_help,true,false,false,false))
		{
			deletelog();
			g_menu_select = -1;
			env[current_level].AddItem(you.position,&items_[select_]);
			return true;
		}
		redraw_ = true;
	}
}
