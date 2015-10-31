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

void Equip_Weapon()
{
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
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"무슨 무기를 장착하시겠습니까?");
		else if(key_ == '-')
		{
			you.unequip(ET_WEAPON);
			break;
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);

}


void Equip_Armor()
{
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
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
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
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
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
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"무슨 장신를 장착하겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Unequip_Jewelry()
{
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
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"무슨 장신구를 벗겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}




