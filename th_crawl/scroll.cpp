//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: scroll.cpp
//
// 내용: 두루마리
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "scroll.h"
#include "key.h"
#include "smoke.h"
#include "monster_texture.h"
#include "throw.h"
#include <algorithm>
extern HANDLE mutx;

char *scroll_uniden_string[SCT_MAX]=
{
	"ASASVQE가 써있는 ",
	"EFIIEQN가 써있는 ",
	"QEWFQFF가 써있는 ",
	"DIQHQNA가 써있는 ",
	"IVNUXTO가 써있는 ",
	"MDIMIKU가 써있는 ",
	"AFIQHQW가 써있는 ",
	"POIUGAW가 써있는 ",
	"MVDOQUR가 써있는 ",
	"TFJEOTT가 써있는 ",
	"XNEPBIQ가 써있는 ",
	"JUYBLNM가 써있는 ",
	"UNQIFNV가 써있는 ",
	"LVIWBAA가 써있는 ",
	"RWMVXCO가 써있는 ",
	"OFQXLFE가 써있는 "
};

const char *scroll_iden_string[SCT_MAX]=
{	
	"공간이동의 ",
	"식별의 ",
	"낙서 ",
	"무기저주의 ",
	"방어구저주의 ",
	"저주해제의 ",
	"순간이동의 ",
	"지형탐지의 ",
	"무기강화의 ",
	"무기강화의 ",
	"방어구강화의 ",
	"안개의 ",
	"저주탐지의 ",
	"장신구저주의 ",
	"정적의 ",
	"영격 "
};



bool identity_scroll();
bool curse_weapon_scroll();
bool curse_armour_scroll();
bool remove_curse_scroll();
bool blink_scroll();
bool enchant_weapon_1_scroll();
bool enchant_weapon_2_scroll();
bool enchant_armour_scroll();
bool fog_scroll();
bool detect_curse_scroll();
bool curse_jewelry_scroll();
bool skill_silence(int pow, bool short_, unit* order, coord_def target);
bool skill_soul_shot(int power, unit* order, coord_def target);




scroll_type goodbadscroll(int good_bad)
{
	if(good_bad==2)
	{
		scroll_type list_[5] = {SCT_BLINK, SCT_ENCHANT_WEAPON_1/*SCT_ENCHANT_WEAPON_2*/, SCT_ENCHANT_ARMOUR, SCT_FOG, SCT_SOUL_SHOT};
		return list_[randA(4)];
	}
	else if(good_bad==3)
	{
		scroll_type list_[1] = {SCT_SILENCE};
		return list_[randA(0)];
	}
	else //if(good_bad==1)
	{
		scroll_type list_[3] = {SCT_TELEPORT, SCT_IDENTIFY, SCT_REMOVE_CURSE/*SCT_DETECT_CURSE*/};
		return list_[randA(2)];
	}/*
	else
	{
		scroll_type list_[4] = {SCT_NONE, SCT_CURSE_WEAPON, SCT_CURSE_ARMOUR, SCT_CURSE_JEWELRY};
		return list_[randA(3)];
	}*/


}
int isGoodScroll(scroll_type kind)
{	
	switch(kind)
	{
	case SCT_SOUL_SHOT:
		return 3;
	case SCT_TELEPORT:
	case SCT_IDENTIFY:
	case SCT_REMOVE_CURSE:
	case SCT_BLINK:
		return 2;
	case SCT_ENCHANT_WEAPON_1:
	case SCT_ENCHANT_WEAPON_2:
	case SCT_ENCHANT_ARMOUR:
	case SCT_FOG:
	case SCT_MAPPING:
	case SCT_DETECT_CURSE:
	case SCT_SILENCE:
		return 1;
	case SCT_NONE:
		return 0;
	case SCT_CURSE_WEAPON:		
	case SCT_CURSE_ARMOUR:
	case SCT_CURSE_JEWELRY:
		return -1;
	}
	return 1;
}




void readscroll(scroll_type kind)
{
	switch(kind)
	{
	case SCT_TELEPORT:		
		if(you.god == GT_YUKARI)
		{
			if(iden_list.scroll_list[kind].iden != 3)
			{				
				printlog("유카리는 당신의 위험한 전이도구 사용을 한번만 봐주기로 하였다.",true,false,false,CL_small_danger);
			}
			else
			{
				printlog("유카리는 당신의 위험한 전이도구 사용에 분노했다!",true,false,false,CL_small_danger);
				you.PietyUpDown(-5);
			}
		}
		you.SetTele(rand_int(3,6));
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_IDENTIFY:
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		if(identity_scroll())
		{
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  2;
		WaitForSingleObject(mutx, INFINITE);
		return;
	case SCT_NONE:
		printlog("이 두루마리에 써있는 것은 낙서같다.",false,false,false,CL_normal);
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_CURSE_WEAPON:		
		iden_list.scroll_list[kind].iden = 3;
		if(curse_weapon_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_CURSE_ARMOUR:		
		iden_list.scroll_list[kind].iden = 3;
		if(curse_armour_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_REMOVE_CURSE:
		iden_list.scroll_list[kind].iden = 3;
		if(remove_curse_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_BLINK:
		ReleaseMutex(mutx);
		blink_scroll();
		iden_list.scroll_list[kind].iden = 3;
		WaitForSingleObject(mutx, INFINITE);
		return;
	case SCT_MAPPING:
		//죽림에서는 발동되지않는다.
		return;
	case SCT_ENCHANT_WEAPON_1:
		iden_list.scroll_list[kind].iden = 3;
		if(enchant_weapon_1_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_ENCHANT_WEAPON_2:
		iden_list.scroll_list[kind].iden = 3;
		if(enchant_weapon_2_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_ENCHANT_ARMOUR:
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		if(enchant_armour_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  2;
		WaitForSingleObject(mutx, INFINITE);
		return;
	case SCT_FOG:
		fog_scroll();
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_DETECT_CURSE:
		detect_curse_scroll();
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_CURSE_JEWELRY:
		iden_list.scroll_list[kind].iden = 3;
		if(curse_jewelry_scroll())
		{
			iden_list.scroll_list[kind].iden = 3;
		}
		else if(iden_list.scroll_list[kind].iden != 3)
			iden_list.scroll_list[kind].iden =  1;
		return;
	case SCT_SILENCE:
		skill_silence(75, false, &you, you.position);
		iden_list.scroll_list[kind].iden = 3;
		return;
	case SCT_SOUL_SHOT://추가
		iden_list.scroll_list[kind].iden = 3;
		if(you.power >= 100)
		{
			ReleaseMutex(mutx);
			changedisplay(DT_GAME);
			you.PowUpDown(-100,true);
			printlog("팡! ",false,false,false,CL_white_blue);
			skill_soul_shot(0, &you, you.position);
			WaitForSingleObject(mutx, INFINITE);
			iden_list.scroll_list[kind].iden = 3;
		}
		else
		{
			printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
			if(iden_list.scroll_list[kind].iden != 3)
				iden_list.scroll_list[kind].iden =  1;
		}
		return;
	}
}



bool identity_scroll()
{
	if(iden_list.scroll_list[SCT_IDENTIFY].iden == 3)
		view_item(IVT_UNIDEN,"무슨 아이템을 식별시겠습니까?");
	else
		view_item(IVT_SELECT,"무슨 아이템에 사용하시겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			item *item_ = you.GetItem(key_);
			if(item_)
			{
				if(!item_->isiden())
				{
					item_->Identify();
					char temp[2];
					sprintf(temp,"%c",item_->id);
					printlog(temp,false,false,false,item_->item_color());
					printlog(" - ",false,false,false,item_->item_color());
					printlog(item_->GetName(),true,false,false,item_->item_color());
					return true;
				}
				else
				{
					printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
					return false;
				}

			}
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
		{	
			if(iden_list.scroll_list[SCT_IDENTIFY].iden == 3)
				view_item(IVT_SELECT,"무슨 아이템을 식별시겠습니까?");
			else
				view_item(IVT_SELECT,"무슨 아이템에 사용하시겠습니까?");
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}


bool curse_weapon_scroll()
{
	if(you.equipment[ET_WEAPON])
	{
		string before_name = you.equipment[ET_WEAPON]->GetName(); //저주받기전 이름
		if(you.equipment[ET_WEAPON]->Curse(true,ET_WEAPON))
		{
			printlog("장착하고 있던 ",false,false,false,CL_small_danger);	
			printlog(before_name,false,false,false,CL_small_danger);	
			printlog(you.equipment[ET_WEAPON]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
			printlog("검게 빛났다.",true,false,false,CL_small_danger);		
			return true;
		}
		else
		{
			printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
			return false;
		}
	}
	else
	{
		printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
		return false;
	}
}
bool curse_armour_scroll()
{	
	deque<int> dq;
	for(int i=ET_ARMOR;i<ET_ARMOR_END;i++)
		dq.push_back(i);
	random_shuffle(dq.begin(),dq.end());

	for(int i = 0; i<dq.size() ; i++)
	{
		if(you.equipment[dq[i]])
		{
			string before_name = you.equipment[dq[i]]->GetName(); //저주받기전 이름
			if(you.equipment[dq[i]]->Curse(true,(equip_type)dq[i]))
			{
				printlog("장착하고 있던 ",false,false,false,CL_small_danger);		
				printlog(before_name,false,false,false,CL_small_danger);	
				printlog(you.equipment[dq[i]]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
				printlog("검게 빛났다.",true,false,false,CL_small_danger);		
				return true;
			}
			else
			{
				printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
				return false;
			}
		}
	}
	printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
	return false;
}

bool remove_curse_scroll()
{
	bool iden_ = false;
	for(int i = ET_FIRST; i<ET_LAST ; i++)
	{
		if(you.equipment[i])
		{
			if(you.equipment[i]->isRightType((equip_type)i))
			{	
				if(you.equipment[i]->curse)
				{
					you.equipment[i]->curse = false;
					you.equipment[i]->identify_curse = true;
					iden_ = true;
				}

			}
		}
	}
	if(iden_)
	{
		printlog("가지고있던 장비의 저주가 풀렸다.",true,false,false,CL_normal);
		return true;
	}
	else
	{
		printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
		return false;
	}
}


bool blink_scroll()
{
	changedisplay(DT_GAME);
	you.search_pos = you.position;
	you.search = true;
	bool is_move = false;
	Search_Move(coord_def(you.position.x,you.position.y), false,VT_BLINK);
	while(1)
	{
		switch(waitkeyinput())
		{
		case 'j':
			is_move = Search_Move(coord_def(you.position.x,you.position.y-1), false,VT_BLINK);  //위
			break;
		case 'k':
			is_move = Search_Move(coord_def(you.position.x,you.position.y+1), false,VT_BLINK); //아래
			break;
		case 'h':
			is_move = Search_Move(coord_def(you.position.x-1,you.position.y), false,VT_BLINK); //왼쪽
			break;
		case 'l':
			is_move = Search_Move(coord_def(you.position.x+1,you.position.y), false,VT_BLINK); //오른쪽
			break;
		case 'b':
			is_move = Search_Move(coord_def(you.position.x-1,you.position.y+1), false,VT_BLINK);
			break;
		case 'n':
			is_move = Search_Move(coord_def(you.position.x+1,you.position.y+1), false,VT_BLINK);
			break;
		case 'y':
			is_move = Search_Move(coord_def(you.position.x-1,you.position.y-1), false,VT_BLINK);
			break;
		case 'u':
			is_move = Search_Move(coord_def(you.position.x+1,you.position.y-1), false,VT_BLINK);
			break;
		case VK_RETURN:
			if(is_move)
			{
				if(you.control_blink(you.search_pos))
				{
					
					if(you.god == GT_YUKARI)
					{
						printlog("유카리는 당신의 위험한 전이도구 사용에 분노했다!",true,false,false,CL_small_danger);
						you.PietyUpDown(-5);
					}


					you.search = false;
					deletelog();
					return true;
				}
			}
			break;
		case VK_ESCAPE:
			printlog("정말로 순간이동을 취소하시겠습니까? (y/n)",true,true,false,CL_help);
			bool repeat_ = true;
			while(repeat_)
			{
				switch(waitkeyinput())
				{
				case 'Y':
				case 'y':
					deletelog();
					you.search = false;
					return false;
				case 'N':
				case 'n':
					repeat_ = false;
				}
			}
		}
	}
}


bool enchant_weapon_1_scroll()
{
	if(you.equipment[ET_WEAPON])
	{
		string before_name = you.equipment[ET_WEAPON]->GetName();
		if(you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, 1, 0))
		{
			printlog("장착하고 있던 ",false,false,false,CL_good);	
			printlog(before_name,false,false,false,CL_good);	
			printlog(you.equipment[ET_WEAPON]->GetNameInfor().name_do(true),false,false,false,CL_good);
			printlog("빨강색으로 빛났다.",true,false,false,CL_good);
			you.equipment[ET_WEAPON]->curse = false;
			you.equipment[ET_WEAPON]->identify_curse = true;
			return true;
		}
		else
		{
			printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
			return false;
		}
	}
	else
	{
		printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
		return false;
	}
}

bool enchant_weapon_2_scroll()
{
	if(you.equipment[ET_WEAPON])
	{
		string before_name = you.equipment[ET_WEAPON]->GetName();
		if(you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, 0, 1))
		{
			printlog("장착하고 있던 ",false,false,false,CL_good);	
			printlog(before_name,false,false,false,CL_good);	
			printlog(you.equipment[ET_WEAPON]->GetNameInfor().name_do(true),false,false,false,CL_good);
			printlog("빨강색으로 빛났다.",true,false,false,CL_good);
			you.equipment[ET_WEAPON]->curse = false;
			you.equipment[ET_WEAPON]->identify_curse = true;
			return true;
		}
		else
		{
			printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
			return false;
		}
	}
	else
	{
		printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
		return false;
	}
}



bool enchant_armour_scroll()
{
	if(iden_list.scroll_list[SCT_ENCHANT_ARMOUR].iden == 3)
		view_item(IVT_ARMOR_ENCHANT,"무슨 방어구를 강화하시겠습니까?");
	else
		view_item(IVT_SELECT,"무슨 아이템에 사용하시겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			item *item_ = you.GetItem(key_);
			if(item_)
			{
				string before_name = item_->GetName();
				if(item_->Enchant(ET_ARMOR, 1, 0))
				{
					printlog(before_name,false,false,false,CL_good);	
					printlog(item_->GetNameInfor().name_do(true),false,false,false,CL_good);
					printlog("초록색으로 빛났다.",true,false,false,CL_good);
					item_->curse = false;
					item_->identify_curse = true;
					return true;
				}
				else
				{
					printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
					return false;
				}

			}
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
		{	
			if(iden_list.scroll_list[SCT_ENCHANT_ARMOUR].iden == 3)
				view_item(IVT_SELECT,"무슨 방어구를 강화하시겠습니까?");
			else
				view_item(IVT_SELECT,"무슨 아이템에 사용하시겠습니까?");
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}


bool fog_scroll()
{
	MakeCloud(you.position, img_fog_normal, SMT_FOG, rand_int(10,15), rand_int(8,12), 0,5, &you);
	return true;
}

bool detect_curse_scroll()
{
	for(list<item>::iterator it = you.item_list.begin(); it != you.item_list.end() ; it++)
	{
		it->identify_curse = true;
	}
	printlog("인벤토리의 저주를 탐지했다.",true,true,false,CL_normal);
	return true;
}
bool curse_jewelry_scroll()
{
	deque<int> dq;
	for(int i=ET_JEWELRY;i<ET_JEWELRY_END;i++)
		dq.push_back(i);
	random_shuffle(dq.begin(),dq.end());

	for(int i = 0; i<dq.size() ; i++)
	{
		if(you.equipment[dq[i]])
		{
			string before_name = you.equipment[dq[i]]->GetName(); //저주받기전 이름
			if(you.equipment[dq[i]]->Curse(true,(equip_type)dq[i]))
			{
				printlog("장착하고 있던 ",false,false,false,CL_small_danger);		
				printlog(before_name,false,false,false,CL_small_danger);	
				printlog(you.equipment[dq[i]]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
				printlog("검게 빛났다.",true,false,false,CL_small_danger);		
				return true;
			}
			else
			{
				printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
				return false;
			}
		}
	}
	printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
	return false;
}