//////////////////////////////////////////////////////////////////////////////////////////////////
//
// ÆÄÀÏÀÌ¸§: equip_action.cpp
//
// ³»¿ë: playerÀÇ Çàµ¿µé(ÀåÂø °ü·Ã Çàµ¿µé)
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
	if(you.s_lunatic)
	{
		printlog("±¤±â¿¡ ÈÛ½ÎÀÎ »óÅÂ·Î ¹«±â¸¦ ¹Ù²Ü ¼ö ¾ø´Ù!",true,false,false,CL_danger);
		return;
	}

	view_item(IVT_EQ_WEAPON,"¹«½¼ ¹«±â¸¦ ÀåÂøÇÏ½Ã°Ú½À´Ï±î?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.equip(key_,ET_WEAPON);
			break;
		}
		else if(key_ == VK_DOWN)//-----ÀÌµ¿Å°-------
		{
			changemove(32);  //À§
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //¾Æ·¡
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----ÀÌµ¿Å°³¡-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"¹«½¼ ¹«±â¸¦ ÀåÂøÇÏ½Ã°Ú½À´Ï±î?");
		else if(key_ == '-')
		{
			if(!you.unequip(ET_WEAPON))
			{				
				printlog("ÀúÁÖ¿¡ °É·Á ÀÖ¾î¼­ Àåºñ¸¦ ¹şÀ» ¼ö ¾ø´Ù.",true,false,false,CL_normal);
			}
			break;
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);

}


void Equip_Armor()
{
	if(you.s_lunatic)
	{
		printlog("±¤±â¿¡ ÈÛ½ÎÀÎ »óÅÂ·Î ¹æ¾î±¸¸¦ ¹Ù²Ü ¼ö ¾ø´Ù!",true,false,false,CL_danger);
		return;
	}
	view_item(IVT_EQ_ARMOR,"¹«½¼ ¹æ¾î±¸¸¦ ÀåÂøÇÏ°Ú½À´Ï±î?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.equiparmor(key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----ÀÌµ¿Å°-------
		{
			changemove(32);  //À§
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //¾Æ·¡
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----ÀÌµ¿Å°³¡-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"¹«½¼ ¹æ¾î±¸¸¦ ÀåÂøÇÏ°Ú½À´Ï±î?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Unequip_Armor()
{	
	if(you.s_lunatic)
	{
		printlog("±¤±â¿¡ ÈÛ½ÎÀÎ »óÅÂ·Î ¹æ¾î±¸¸¦ ¹şÀ» ¼ö ¾ø´Ù!",true,false,false,CL_danger);
		return;
	}
	view_item(IVT_UEQ_ARMOR,"¹«½¼ ¹æ¾î±¸¸¦ ¹ş°Ú½À´Ï±î?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			
			changedisplay(DT_GAME);
			you.unequiparmor(key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----ÀÌµ¿Å°-------
		{
			changemove(32);  //À§
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //¾Æ·¡
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----ÀÌµ¿Å°³¡-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"¹«½¼ ¹æ¾î±¸¸¦ ¹ş°Ú½À´Ï±î?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}



void Equip_Jewelry()
{	
	if(you.s_lunatic)
	{
		printlog("±¤±â¿¡ ÈÛ½ÎÀÎ »óÅÂ·Î ¹İÁö¸¦ ³¥ ¼ö ¾ø´Ù!",true,false,false,CL_danger);
		return;
	}
	view_item(IVT_EQ_JEWELRY,"¹«½¼ Àå½Å±¸¸¦ ÀåÂøÇÏ°Ú½À´Ï±î?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.equipjewerly(key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----ÀÌµ¿Å°-------
		{
			changemove(32);  //À§
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //¾Æ·¡
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----ÀÌµ¿Å°³¡-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"¹«½¼ Àå½Å±¸¸¦ ÀåÂøÇÏ°Ú½À´Ï±î?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Unequip_Jewelry()
{	
	if(you.s_lunatic)
	{
		printlog("±¤±â¿¡ ÈÛ½ÎÀÎ »óÅÂ·Î ¹İÁö¸¦ ¹şÀ» ¼ö ¾ø´Ù!",true,false,false,CL_danger);
		return;
	}
	view_item(IVT_UEQ_JEWELRY,"¹«½¼ Àå½Å±¸¸¦ ¹ş°Ú½À´Ï±î?");
	while(1)
	{
		int key_ = waitkeyinput();
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.unequipjewerly(key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----ÀÌµ¿Å°-------
		{
			changemove(32);  //À§
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //¾Æ·¡
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----ÀÌµ¿Å°³¡-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"¹«½¼ Àå½Å±¸¸¦ ¹ş°Ú½À´Ï±î?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}




