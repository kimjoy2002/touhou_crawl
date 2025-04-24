//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: equip_action.cpp
//
// 내용: player의 행동들(장착 관련 행동들)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "key.h"
#include "player.h"
#include "beam.h"
#include "monster_texture.h"
#include "option_manager.h"

bool weapon_prev_fail() {
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_SWAP_WEAPON),true,false,false,CL_danger);
		return true;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_SWAP_WEAPON), true, false, false, CL_normal);
		return true;
	}
	if (you.drowned)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY_WEAPON), true, false, false, CL_danger);
		return true;
	}
	return false;
}

void Equip_Weapon()
{
	if(weapon_prev_fail())
	{
		return;
	}
	view_item(IVT_EQ_WEAPON,LOC_SYSTEM_DISPLAY_MANAGER_EQ_WEAPON);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.equip(key_,ET_WEAPON);
			break;
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_EQ_WEAPON);
		else if(key_ == '-')
		{
			if(!you.unequip(ET_WEAPON))
			{				
				printlog(LocalzationManager::locString(LOC_SYSTEM_CURSED_PENALTY),true,false,false,CL_normal);
			}
			break;
		}
		else if( key_ == -1) {			
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_EQ_WEAPON,LOC_SYSTEM_DISPLAY_MANAGER_EQ_WEAPON);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);

}


void weapon_swap()
{
	if(weapon_prev_fail())
	{
		return;
	}
	item* aitem_ = you.GetItem('a');
	item* bitem_ = you.GetItem('b');
	if (aitem_ && !aitem_->isRightType(ET_WEAPON))
		aitem_ = NULL;
	if (bitem_ && !bitem_->isRightType(ET_WEAPON))
		bitem_ = NULL;
	bool equipAitem_ = false;
	//장착한 무기가 a가 아니면 a로 a면 b로 바꿈
	//a가 맨손인 경우는 어쩌지?

	if (you.equipment[ET_WEAPON])
	{
		if(you.equipment[ET_WEAPON]->id == 'a')
			equipAitem_ = false;
		else
		{
			equipAitem_ = true;
			you.already_swap = true;
		}

	}
	else {
		if (you.already_swap)
		{
			equipAitem_ = false;
		}
		else
		{
			equipAitem_ = true;
			you.already_swap = true;
		}

	}

	if(equipAitem_)
	{
		if (aitem_)
			you.equip('a', ET_WEAPON);
		else if (you.equipment[ET_WEAPON])
			you.unequip(ET_WEAPON);
	}
	else
	{
		if (bitem_)
			you.equip('b', ET_WEAPON);
		else if (you.equipment[ET_WEAPON])
			you.unequip(ET_WEAPON);
	}
	you.SetPrevAction('\'');
}


bool armor_prev_fail(){
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_SWAP_ARMOUR),true,false,false,CL_danger);
		return true;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_SWAP_ARMOUR), true, false, false, CL_normal);
		return true;
	}
	if (you.drowned)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY_ARMOUR), true, false, false, CL_danger);
		return true;
	}
	return false;
}


void Equip_Armor()
{
	if(armor_prev_fail()) {
		return;
	}
	view_item(IVT_EQ_ARMOR,LOC_SYSTEM_DISPLAY_MANAGER_EQ_ARMOUR);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.equiparmor(key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_EQ_ARMOUR);
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_EQ_ARMOR,LOC_SYSTEM_DISPLAY_MANAGER_EQ_ARMOUR);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Unequip_Armor()
{	
	if(armor_prev_fail()) {
		return;
	}
	view_item(IVT_UEQ_ARMOR,LOC_SYSTEM_DISPLAY_MANAGER_UEQ_ARMOUR);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			
			changedisplay(DT_GAME);
			you.unequiparmor(key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_UEQ_ARMOUR);
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_UEQ_ARMOR,LOC_SYSTEM_DISPLAY_MANAGER_UEQ_ARMOUR);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}

bool jewelry_prev_fail() {
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_EQUIP_JEWELRY),true,false,false,CL_danger);
		return true;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_EQUIP_JEWELRY), true, false, false, CL_normal);
		return true;
	}
	return false;
}


void Equip_Jewelry()
{
	if(jewelry_prev_fail()) {
		return;
	}
	view_item(IVT_EQ_JEWELRY,LOC_SYSTEM_DISPLAY_MANAGER_EQ_JEWELRY);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.equipjewerly(key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_EQ_JEWELRY);
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_EQ_JEWELRY,LOC_SYSTEM_DISPLAY_MANAGER_EQ_JEWELRY);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Unequip_Jewelry()
{
	if(jewelry_prev_fail()) {
		return;
	}
	view_item(IVT_UEQ_JEWELRY,LOC_SYSTEM_DISPLAY_MANAGER_UEQ_JEWELRY);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.unequipjewerly(key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_UEQ_JEWELRY);
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_UEQ_JEWELRY,LOC_SYSTEM_DISPLAY_MANAGER_UEQ_JEWELRY);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}




