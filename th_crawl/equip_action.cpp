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

void Equip_Weapon()
{
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 무기를 바꿀 수 없다!",true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog("유령 상태에선 무기를 바꿀 수 없다. ", true, false, false, CL_normal);
		return;
	}
	if (you.drowned)
	{
		printlog("물에 빠진 상태에선 무기를 바꿀 수 없다!", true, false, false, CL_danger);
		return;
	}

	view_item(IVT_EQ_WEAPON,"무슨 무기를 장착하시겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput();
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
			view_item(IVT_SELECT,"무슨 무기를 장착하시겠습니까?");
		else if(key_ == '-')
		{
			if(!you.unequip(ET_WEAPON))
			{				
				printlog("저주에 걸려 있어서 장비를 벗을 수 없다.",true,false,false,CL_normal);
			}
			break;
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);

}


void weapon_swap()
{
	if (you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 할 수 없다!", true, false, false, CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog("유령 상태에선 장비를 바꿀 수 없다. ", true, false, false, CL_normal);
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
void Equip_Armor()
{
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 방어구를 바꿀 수 없다!",true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog("유령 상태에선 방어구를 바꿀 수 없다. ", true, false, false, CL_normal);
		return;
	}
	if (you.drowned)
	{
		printlog("물에 빠진 상태에선 방어구를 바꿀 수 없다!", true, false, false, CL_danger);
		return;
	}
	view_item(IVT_EQ_ARMOR,"무슨 방어구를 장착하겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput();
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
			view_item(IVT_SELECT,"무슨 방어구를 장착하겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Unequip_Armor()
{	
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 방어구를 벗을 수 없다!",true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog("유령 상태에선 방어구를 벗을 수 없다. ", true, false, false, CL_normal);
		return;
	}
	view_item(IVT_UEQ_ARMOR,"무슨 방어구를 벗겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput();
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
			view_item(IVT_SELECT,"무슨 방어구를 벗겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}



void Equip_Jewelry()
{	
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 장신구를 낄 수 없다!",true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog("유령 상태에선 장신구를 낄 수 없다. ", true, false, false, CL_normal);
		return;
	}
	view_item(IVT_EQ_JEWELRY,"무슨 장신구를 장착하겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput();
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
			view_item(IVT_SELECT,"무슨 장신구를 장착하겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Unequip_Jewelry()
{	
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 장신구를 벗을 수 없다!",true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog("유령 상태에선 장신구를 벗을 수 없다. ", true, false, false, CL_normal);
		return;
	}
	view_item(IVT_UEQ_JEWELRY,"무슨 장신구를 벗겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput();
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
			view_item(IVT_SELECT,"무슨 장신구를 벗겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}




