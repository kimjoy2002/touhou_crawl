//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: scroll.cpp
//
// 내용: 두루마리
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "key.h"
#include "smoke.h"
#include "monster_texture.h"
#include "throw.h"
#include "spellcard.h"
#include "environment.h"
#include "skill_use.h"
#include "rand_shuffle.h"
#include "option_manager.h"
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
	"OFQXLFE가 써있는 ",
	"DQFQEFS가 써있는 ",
	"BAHJDQU가 써있는 "
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
	"영격 ",
	"스펠카드충전의 ",
	"망각의 "
};



bool identity_scroll(bool pre_iden_);
bool curse_weapon_scroll(bool pre_iden_);
bool curse_armour_scroll(bool pre_iden_);
bool remove_curse_scroll(bool pre_iden_);
bool blink_scroll(bool pre_iden_);
bool enchant_weapon_1_scroll(bool pre_iden_);
bool enchant_weapon_2_scroll(bool pre_iden_);
bool enchant_armour_scroll(bool pre_iden_);
bool fog_scroll(bool pre_iden_);
bool detect_curse_scroll(bool pre_iden_);
bool curse_jewelry_scroll(bool pre_iden_);
bool skill_silence(int pow, bool short_, unit* order, coord_def target);
bool skill_soul_shot(int power, unit* order, coord_def target);
bool recharging_scroll(bool pre_iden_, bool ablity_);
bool amnesia_scroll(bool pre_iden_);




scroll_type goodbadscroll(int good_bad)
{
	if(good_bad==2)
	{
		scroll_type list_[7] = {SCT_BLINK, SCT_ENCHANT_WEAPON_1/*SCT_ENCHANT_WEAPON_2*/, SCT_ENCHANT_ARMOUR, SCT_FOG,
			SCT_CHARGING, SCT_MAPPING,SCT_AMNESIA};
		return list_[randA(6)];
	}
	else if(good_bad==3)
	{
		scroll_type list_[2] = {SCT_SILENCE,SCT_SOUL_SHOT};
		return list_[randA(1)];
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
	case SCT_CHARGING:
	case SCT_AMNESIA:
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




bool readscroll(scroll_type kind, bool pre_iden_)
{
	switch(kind)
	{
	case SCT_TELEPORT:		
		{
		iden_list.scroll_list[kind].iden = 3;
		ReleaseMutex(mutx);
		if(!you.Tele_check(pre_iden_, false))
			return false;
		WaitForSingleObject(mutx, INFINITE);
		bool return_ = you.SetTele(rand_int(3,6));
		return return_;
		}
	case SCT_IDENTIFY:
		{
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = identity_scroll(pre_iden_);
		WaitForSingleObject(mutx, INFINITE);
		return return_;
		}
	case SCT_NONE:
		{
		printlog("이 두루마리에 써있는 것은 낙서같다.",false,false,false,CL_normal);
		iden_list.scroll_list[kind].iden = 3;
		return true;
		}
	case SCT_CURSE_WEAPON:		
		{
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = curse_weapon_scroll(pre_iden_);
		return return_;
		}
	case SCT_CURSE_ARMOUR:	
		{
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = curse_armour_scroll(pre_iden_);
		return return_;
		}
	case SCT_REMOVE_CURSE:
		{
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = remove_curse_scroll(pre_iden_);
		return return_;
		}
	case SCT_BLINK:
		{
		ReleaseMutex(mutx);
		bool return_ = blink_scroll(pre_iden_);
		iden_list.scroll_list[kind].iden = 3;
		WaitForSingleObject(mutx, INFINITE);
		return return_;
		}
	case SCT_MAPPING:
		 {
			 iden_list.scroll_list[kind].iden = 3;
			if(env[current_level].isBamboo())
			{				
				printlog("지형탐지는 미궁의 죽림에선 효과를 보지 못한다.",true,false,false,CL_normal);
				if(pre_iden_){
					return false;
				}
				else{
					return true;
				}
			}
			else
			{
				env[current_level].MakeMapping(100);	
				printlog("당신은 현재 층을 감지해냈다.",true,false,false,CL_normal);
			}
			return true;
		 }
	case SCT_ENCHANT_WEAPON_1:
		{
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = enchant_weapon_1_scroll(pre_iden_);
		return return_;
		}
	case SCT_ENCHANT_WEAPON_2:
		{
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = enchant_weapon_2_scroll(pre_iden_);
		return return_;
		}
	case SCT_ENCHANT_ARMOUR:
		{
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = enchant_armour_scroll(pre_iden_);
		WaitForSingleObject(mutx, INFINITE);
		return return_;
		}
	case SCT_FOG:
		{
		bool return_ = fog_scroll(pre_iden_);
		iden_list.scroll_list[kind].iden = 3;
		return return_;
		}
	case SCT_DETECT_CURSE:
		{
		bool return_ = detect_curse_scroll(pre_iden_);
		iden_list.scroll_list[kind].iden = 3;
		return return_;
		}
	case SCT_CURSE_JEWELRY:
		{
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = curse_jewelry_scroll(pre_iden_);
		return return_;
		}
	case SCT_SILENCE:
		{
		skill_silence(75, false, &you, you.position);
		iden_list.scroll_list[kind].iden = 3;
		return true;
		}
	case SCT_SOUL_SHOT://추가
		{
		iden_list.scroll_list[kind].iden = 3;
		if(you.power >= 100)
		{
			ReleaseMutex(mutx);
			changedisplay(DT_GAME);
			you.PowUpDown(-100,true);
			printlog("팡! ",false,false,false,CL_white_blue);
			skill_soul_shot(0, &you, you.position);
			WaitForSingleObject(mutx, INFINITE);
		}
		else
		{
			printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
		}
		return true;
		}
	case SCT_CHARGING:
		{
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = recharging_scroll(pre_iden_, false);
		WaitForSingleObject(mutx, INFINITE);
		return return_;
		}
	case SCT_AMNESIA:
		{
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = amnesia_scroll(pre_iden_);
		WaitForSingleObject(mutx, INFINITE);
		return return_;
		}
	}
	return true;
}



bool identity_scroll(bool pre_iden_)
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
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
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
	if(pre_iden_){
		return false;
	}
	else{
		return true;
	}
}


bool curse_weapon_scroll(bool pre_iden_)
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
			if(pre_iden_){
				printlog("이 아이템은 저주를 더 걸 수 없다.",true,false,false,CL_normal);
				return false;
			}
			else{
				printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
				return true;
			}
		}
	}
	else
	{
		if(pre_iden_){
			printlog("무기를 끼고 있지 않다.",true,false,false,CL_normal);
			return false;
		}
		else{
			printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
			return true;
		}
	}
}
bool curse_armour_scroll(bool pre_iden_)
{	
	deque<int> dq;
	for(int i=ET_ARMOR;i<ET_ARMOR_END;i++)
		dq.push_back(i);
	rand_shuffle(dq.begin(),dq.end());

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
		}
	}
	if(pre_iden_){
		printlog("저주걸 수 있는 방어구를 끼고 있지 않다.",true,false,false,CL_normal);
		return false;
	}
	else{
		printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
		return true;
	}
}

bool remove_curse_scroll(bool pre_iden_)
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
					if(iden_==false && you.GetPunish(GT_HINA) && randA(2))
					{
						printlog("히나가 당신의 액땜을 방해했다! ",false,false,false,CL_hina);						
						printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
						return true;
					}
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
		if(pre_iden_){
			printlog("저주가 걸린 장비가 없다.",true,false,false,CL_normal);
			return false;
		}
		else{
			printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
			return true;
		}
	}
}


bool blink_scroll(bool pre_iden_)
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
		case 'k':
			is_move = Search_Move(coord_def(you.position.x,you.position.y-1), false,VT_BLINK);  //위
			break;
		case 'j':
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
				if(!you.Tele_check(pre_iden_, true))
				{
					deletelog();
					you.search = false;
					return false;
				}
				if(you.control_blink(you.search_pos))
				{
					you.search = false;
					deletelog();
					return true;
				}
			}
			break;
		case VK_ESCAPE:	
			if(pre_iden_){
				printlog("정말로 순간이동을 취소하시겠습니까? (y/n)",true,true,false,CL_help);
			}
			else{
				printlog("정말로 순간이동을 취소하시겠습니까? 스크롤은 사라집니다! (y/n)",true,true,false,CL_help);
			}
			bool repeat_ = true;
			while(repeat_)
			{
				switch(waitkeyinput())
				{
				case 'Y':
				case 'y':
					deletelog();
					you.search = false;
					if(pre_iden_){
						return false;
					}
					else{
						return true;
					}
				case 'N':
				case 'n':
					repeat_ = false;
				}
			}
		}
	}

}


bool enchant_weapon_1_scroll(bool pre_iden_)
{
	if(you.equipment[ET_WEAPON])
	{
		string before_name = you.equipment[ET_WEAPON]->GetName();
		if(you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, 1))
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
			if(pre_iden_){
				printlog("더 이상 강화 할 수 없는 무기다.",true,false,false,CL_normal);
				return false;
			}
			else{
				printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
				return true;
			}
		}
	}
	else
	{
		if(pre_iden_){
			printlog("장비한 무기가 없다.",true,false,false,CL_normal);
			return false;
		}
		else{
			printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
			return true;
		}
	}
}

bool enchant_weapon_2_scroll(bool pre_iden_)
{
	if(you.equipment[ET_WEAPON])
	{
		string before_name = you.equipment[ET_WEAPON]->GetName();
		if(you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, 1))
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
			if(pre_iden_){
				printlog("더 이상 강화 할 수 없는 무기다.",true,false,false,CL_normal);
				return false;
			}
			else{
				printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
				return true;
			}
		}
	}
	else
	{
		if(pre_iden_){
			printlog("장비한 무기가 없다.",true,false,false,CL_normal);
			return false;
		}
		else{
			printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
			return true;
		}
	}
}



bool enchant_armour_scroll(bool pre_iden_)
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
				if(item_->Enchant(ET_ARMOR, 1))
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
					if(pre_iden_){
						printlog("이 아이템은 강화할 수 없다.",true,false,false,CL_normal);
						return false;
					}
					else{
						printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
						return true;
					}
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
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
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
	if(pre_iden_){
		return false;
	}
	else{
		return true;
	}
}


bool fog_scroll(bool pre_iden_)
{
	MakeCloud(you.position, img_fog_normal, SMT_FOG, rand_int(10,15), rand_int(8,12), 0,5, &you);
	return true;
}

bool detect_curse_scroll(bool pre_iden_)
{
	for(list<item>::iterator it = you.item_list.begin(); it != you.item_list.end() ; it++)
	{
		it->identify_curse = true;
	}
	printlog("인벤토리의 저주를 탐지했다.",true,true,false,CL_normal);
	return true;
}
bool curse_jewelry_scroll(bool pre_iden_)
{
	deque<int> dq;
	for(int i=ET_JEWELRY;i<ET_JEWELRY_END;i++)
		dq.push_back(i);
	rand_shuffle(dq.begin(),dq.end());

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
		}
	}
	if(pre_iden_){
		printlog("저주걸 수 있는 장신구가 없다.",true,false,false,CL_normal);
		return false;
	}
	else{
		printlog("아무 일도 일어나지않았다.",true,false,false,CL_normal);
		return true;
	}
}
bool recharging_scroll(bool pre_iden_, bool ablity_)
{
	bool ok_ = false;
	for(auto it = you.item_list.begin();it != you.item_list.end(); it++)
	{
		if((*it).isSimpleType(ITMS_SPELL) && (*it).isChargable())
		{
			ok_ = true;
			break;
		}
	}
	if(!ok_)
	{
		printlog("당신의 소지품에 충전할 수 있는 스펠카드가 없다.",true,false,false,CL_normal);
		if(pre_iden_)
			return false;
		else
			return true;
	}



	if(iden_list.scroll_list[SCT_CHARGING].iden == 3 || ablity_)
		view_item(IVT_SPELLCARD,"무슨 스펠카드를 충전하시겠습니까?");
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
				if(item_->isChargable())
				{
					int charging_= SpellcardMaxCharge((spellcard_evoke_type)item_->value2) * rand_float(0.3f,0.7f);

					printlog(item_->GetName(),false,false,false,CL_good);	
					printlog(item_->GetNameInfor().name_do(true),false,false,false,CL_good);
					printlog("충전되었다.",true,false,false,CL_good);

					item_->value1 += charging_;
					if(item_->value1>SpellcardMaxCharge((spellcard_evoke_type)item_->value2))
						item_->value1 = SpellcardMaxCharge((spellcard_evoke_type)item_->value2);
					item_->value3 = -2; 					

					return true;
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
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if(key_ == '*')
		{	
			if(iden_list.scroll_list[SCT_CHARGING].iden == 3 || ablity_)
				view_item(IVT_SPELLCARD,"무슨 스펠카드를 충전하시겠습니까?");
			else
				view_item(IVT_SELECT,"무슨 아이템에 사용하시겠습니까?");
		}
		else if(key_ == VK_ESCAPE)
		{
			break;
		}
	}
	changedisplay(DT_GAME);
	if(pre_iden_){
		return false;
	}
	else{
		return true;
	}
}
bool amnesia_scroll(bool pre_iden_)
{
	

	if(you.currentSpellNum)
	{
		int i=0;
		view_spell("잊을 마법을 선택하세요. ( ?키로 설명을 볼 수 있다. )");
		//changedisplay(DT_SPELL);
		while(1)
		{
			int key_ = waitkeyinput(true);
			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
				if(spell_list spell_ = (spell_list)you.MemorizeSpell[num])
				{				
					
					changedisplay(DT_GAME);
					printarray(true,false,false,CL_help,2,SpellString(spell_)," 마법을 잊겠습니까? (Y/N)");
					switch(waitkeyinput())
					{
					case 'Y':
					case 'y':
						{
							changedisplay(DT_GAME);
							WaitForSingleObject(mutx, INFINITE);
							you.MemorizeSpell[num] = 0;
							you.remainSpellPoiont+=SpellLevel(spell_);
							you.currentSpellNum--;
							ReleaseMutex(mutx);
							printarray(true,false,false,CL_normal,3,"당신은 ",SpellString(spell_)," 마법을 잊었다.");	
							return true;
						}
					case 'N':
					default:
						view_spell("잊을 마법을 선택하세요.  ( ?키로 설명을 볼 수 있다. )");
						//changedisplay(DT_SPELL);
						break;
					}
				}
			}
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
	}
	else
	{
		printlog("아직 알고있는 마법이 없다.",true,false,false,CL_normal);	
	}

	if(pre_iden_){
		return false;
	}
	else{
		return true;
	}
}