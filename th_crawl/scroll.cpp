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
#include "soundmanager.h"
#include "weapon.h"
#include <algorithm>
extern HANDLE mutx;

LOCALIZATION_ENUM_KEY scroll_uniden_string[SCT_MAX]=
{
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN1,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN2,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN3,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN4,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN5,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN6,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN7,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN8,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN9,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN10,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN11,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN12,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN13,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN14,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN15,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN16,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN17,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN18,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN19,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_UNIDEN20
};

LOCALIZATION_ENUM_KEY scroll_iden_string[SCT_MAX]=
{	
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_TELEPORT,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_IDENTIFY,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_NONE,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_CURSE_WEAPON,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_CURSE_ARMOUR,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_REMOVE_CURSE,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_BLINK,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_MAPPING,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_ENCHANT_WEAPON_1,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_ENCHANT_WEAPON_2,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_ENCHANT_ARMOUR,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_FOG,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_DETECT_CURSE,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_CURSE_JEWELRY,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_SILENCE,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_SOUL_SHOT,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_CHARGING,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_AMNESIA,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_SANTUARY,
	LOC_SYSTEM_ITEM_SCROLL_SCROLL_IDEN_BRAND_WEAPON
};



bool identity_scroll(bool pre_iden_); 
void random_identity_scroll();
bool curse_weapon_scroll(bool pre_iden_);
bool curse_armour_scroll(bool pre_iden_);
bool remove_curse_scroll(bool pre_iden_);
bool blink_scroll(bool pre_iden_);
bool enchant_weapon_1_scroll(bool pre_iden_);
bool enchant_weapon_2_scroll(bool pre_iden_);
bool enchant_armour_scroll(bool pre_iden_, bool waste_);
bool fog_scroll(bool pre_iden_);
bool detect_curse_scroll(bool pre_iden_);
bool curse_jewelry_scroll(bool pre_iden_); 
bool skill_silence(int pow, bool short_, unit* order, coord_def target);
bool skill_soul_shot(int power, unit* order, coord_def target);
bool skill_santuary(int pow, bool short_, unit* order, coord_def target);
bool recharging_scroll(bool pre_iden_, bool ablity_, bool waste_);
bool amnesia_scroll(bool pre_iden_);
bool brand_weapon_scroll(bool pre_iden_);




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
		scroll_type list_[4] = {SCT_SILENCE,SCT_SOUL_SHOT,SCT_SANTUARY, SCT_BRAND_WEAPON};
		return list_[randA(3)];
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
	case SCT_SANTUARY:
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
	case SCT_BRAND_WEAPON:
		return 1;
	case SCT_NONE:
		return 0;
	case SCT_CURSE_WEAPON:		
	case SCT_CURSE_ARMOUR:
	case SCT_CURSE_JEWELRY:
		return -1;
	default:
		break;
	}
	return 1;
}




bool readscroll(scroll_type kind, bool pre_iden_, bool waste_)
{
	if (you.s_pure_turn && you.s_pure >= 20)
	{
		if (kind != SCT_ENCHANT_WEAPON_1 &&
			kind != SCT_ENCHANT_WEAPON_2 &&
			kind != SCT_ENCHANT_ARMOUR &&
			kind != SCT_IDENTIFY &&
			kind != SCT_BRAND_WEAPON &&
			kind != SCT_REMOVE_CURSE &&
			kind != SCT_AMNESIA)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_PURITY_PENALTY_SCROLL), true, false, false, CL_normal);
			iden_list.scroll_list[kind].iden = 3;
			return !pre_iden_;
		}
	}


	switch(kind)
	{
	case SCT_TELEPORT:		
		{
		if (waste_) //낭비시엔 의미가 없음
			return true;
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
		bool return_ = true;
		if(waste_)
			random_identity_scroll();
		else
			return_ = identity_scroll(pre_iden_);
		WaitForSingleObject(mutx, INFINITE);
		return return_;
		}
	case SCT_NONE:
		{
		if (waste_) //낭비시엔 의미가 없음
			return true;
		printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_JUST_DOODLE),true,false,false,CL_normal);
		iden_list.scroll_list[kind].iden = 3;
		return true;
		}
	case SCT_CURSE_WEAPON:		
		{
		if (waste_) //낭비시엔 의미가 없음
			return true;
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
		if (waste_) //낭비시엔 의미가 없음
			return true;
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = remove_curse_scroll(pre_iden_);
		return return_;
		}
	case SCT_BLINK:
		{
		ReleaseMutex(mutx);
		bool return_ = blink_scroll(waste_ ? false : pre_iden_);
		if (return_) {
			soundmanager.playSound("blink");
		}
		iden_list.scroll_list[kind].iden = 3;
		WaitForSingleObject(mutx, INFINITE);
		return return_;
		}
	case SCT_MAPPING:
		 {
			if (waste_) //낭비시엔 의미가 없음
				return true;
			iden_list.scroll_list[kind].iden = 3;
			if(env[current_level].isBamboo())
			{				
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_MAPPING_BAMBOO),true,false,false,CL_normal);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_MAPPING_SUCCESS),true,false,false,CL_normal);
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
		bool return_ = enchant_armour_scroll(pre_iden_, waste_);
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
		if (waste_) //낭비시엔 의미가 없음
			return true;
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
		if (waste_) //낭비시엔 의미가 없음
			return true;
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_SOULSHOT) + " ",false,false,false,CL_white_blue);
			soundmanager.playSound("soul_shot");
			skill_soul_shot(0, &you, you.position);
			WaitForSingleObject(mutx, INFINITE);
		}
		else
		{
			if (!waste_) //낭비시엔 의미가 없음
				printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
		}
		return true;
		}
	case SCT_SANTUARY:
	{
		//if (waste_) //낭비시엔 의미가 없음
		//	return true;
		iden_list.scroll_list[kind].iden = 3;
		if (you.power >= 100)
		{
			ReleaseMutex(mutx);
			changedisplay(DT_GAME);
			you.PowUpDown(-100, true);
			skill_santuary(75, false, &you, you.position);
			WaitForSingleObject(mutx, INFINITE);
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND), true, false, false, CL_normal);
		}
		return true;
	}
	case SCT_CHARGING:
		{
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = recharging_scroll(pre_iden_, false, waste_);
		WaitForSingleObject(mutx, INFINITE);
		return return_;
		}
	case SCT_AMNESIA:
		{
		if (waste_) //낭비시엔 의미가 없음
			return true;
		ReleaseMutex(mutx);
		iden_list.scroll_list[kind].iden = 3;
		bool return_ = amnesia_scroll(pre_iden_);
		WaitForSingleObject(mutx, INFINITE);
		return return_;
		}
	case SCT_BRAND_WEAPON:
		{
			iden_list.scroll_list[kind].iden = 3;
			bool return_ = brand_weapon_scroll(pre_iden_);
			return return_;
		}
	default:
		break;
	}
	return true;
}


void random_identity_scroll()
{
	//역병신의 저주로 스크롤 자동 식별
	random_extraction<item *> rand_;

	list<item>::iterator it;
	for (it = you.item_list.begin(); it != you.item_list.end(); it++)
	{
		if (!it->isiden())
			rand_.push(&(*it));
	}
	if (rand_.GetSize() > 0) {
		item* rand_item = rand_.pop();
		if (rand_item != NULL)
		{
			rand_item->Identify();
			std::string temp(1, rand_item->id);
			printlog(temp, false, false, false, rand_item->item_color());
			printlog(" - ", false, false, false, rand_item->item_color());
			printlog(rand_item->GetName(), true, false, false, rand_item->item_color());
		}
	}
}

bool identity_scroll(bool pre_iden_)
{
	if(iden_list.scroll_list[SCT_IDENTIFY].iden == 3)
		view_item(IVT_UNIDEN,LOC_SYSTEM_DISPLAY_MANAGER_IDEN);
	else
		view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_USE_TO);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			item *item_ = you.GetItem(key_);
			if(item_)
			{
				if(!item_->isiden())
				{
					item_->Identify();
					std::string temp(1, item_->id);
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
				view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_IDEN);
			else
				view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_USE_TO);
		}
		else if(key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				if(iden_list.scroll_list[SCT_IDENTIFY].iden == 3)
					rollback_item(IVT_UNIDEN,LOC_SYSTEM_DISPLAY_MANAGER_IDEN);
				else
					rollback_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_USE_TO);
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
			LocalzationManager::printLogWithKey(LOC_SYSTEM_ITEM_SCROLL_CURSE_ITEM,true,false,false,CL_small_danger,
				 PlaceHolderHelper(before_name));
			return true;
		}
		else
		{
			if(pre_iden_){
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_CURSE_ITEM_FAIL),true,false,false,CL_normal);
				return false;
			}
			else{
				printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
				return true;
			}
		}
	}
	else
	{
		if(pre_iden_){
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_CARRYING_WEAPON),true,false,false,CL_normal);
			return false;
		}
		else{
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
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
				LocalzationManager::printLogWithKey(LOC_SYSTEM_ITEM_SCROLL_CURSE_ITEM,true,false,false,CL_small_danger,
					 PlaceHolderHelper(before_name));
				return true;
			}
		}
	}
	if(pre_iden_){
		printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_CURSE_ARMOUR_FAIL),true,false,false,CL_normal);
		return false;
	}
	else{
		printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_REMOVE_CURSE_HINA_FAIL) + " ",false,false,false,CL_hina);						
						printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_REMOVE_CURSE),true,false,false,CL_normal);
		return true;
	}
	else
	{
		if(pre_iden_){
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_REMOVE_CURSE_FAIL),true,false,false,CL_normal);
			return false;
		}
		else{
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
			return true;
		}
	}
}


bool blink_scroll(bool pre_iden_)
{
	changedisplay(DT_GAME);
	if (current_level == ZIGURRAT_LEVEL ) {
		if (pre_iden_) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_BLINK_ZIGURRAT), false, true, false, CL_small_danger);
			printlog(" (",false,true,false,CL_small_danger);
			printlog("y",false,true,false,CL_small_danger, 'y');
			printlog("/",false,true,false,CL_small_danger);
			printlog("n",false,true,false,CL_small_danger, 'n');
			printlog(") ",false,true,false,CL_small_danger);
			startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});

			InputedKey inputedKey;
			switch (waitkeyinput(inputedKey))
			{
			case 'Y':
			case 'y':
				break;				
			case -1:
			case 'N':
			case 'n':
			case VK_ESCAPE:
			default:
				printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE), true, true, false, CL_normal);
				endSelection();
				return false;
			}
			endSelection();
		}
		you.Blink(25);
		return true;
	}


	you.search_pos = you.position;
	you.search = true;
	bool is_move = false;
	startSelection({'v',VK_ESCAPE});
	Search_Move(coord_def(you.position.x,you.position.y), false,VT_BLINK);
	while(1)
	{
		InputedKey inputedKey;
		switch(waitkeyinput(inputedKey))
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
					endSelection();
					you.search = false;
					return false;
				}
				if(you.control_blink(you.search_pos))
				{
					you.search = false;
					deletelog();
					endSelection();
					return true;
				}
			}
			break;			
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				break;
			}
		case VK_ESCAPE:	
			if(pre_iden_){
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_BLINK_CANCLE_ASK),false,true,false,CL_help);
			}
			else{
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_BLINK_CANCLE_WASTE_ASK),false,true,false,CL_help);
			}
			printlog(" (",false,true,false,CL_help);
			printlog("y",false,true,false,CL_help, 'y');
			printlog("/",false,true,false,CL_help);
			printlog("n",false,true,false,CL_help, 'n');
			printlog(") ",false,true,false,CL_help);
			startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
			bool repeat_ = true;
			while(repeat_)
			{
				switch(waitkeyinput())
				{
				case 'Y':
				case 'y':
					deletelog();
					you.search = false;
					endSelection();
					if(pre_iden_){
						return false;
					}
					else{
						return true;
					}
				case 'N':
				case 'n':
					endSelection();
					repeat_ = false;
				default:
					break;
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
			LocalzationManager::printLogWithKey(LOC_SYSTEM_ITEM_SCROLL_ENCHANT_ITEM,true,false,false,CL_good,
				 PlaceHolderHelper(before_name));
			you.equipment[ET_WEAPON]->curse = false;
			you.equipment[ET_WEAPON]->identify_curse = true;
			return true;
		}
		else
		{
			if(pre_iden_){
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_ENCHANT_WEAPON_FAIL),true,false,false,CL_normal);
				return false;
			}
			else{
				printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
				return true;
			}
		}
	}
	else
	{
		if(pre_iden_){
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_CARRYING_WEAPON),true,false,false,CL_normal);
			return false;
		}
		else{
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
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
			LocalzationManager::printLogWithKey(LOC_SYSTEM_ITEM_SCROLL_ENCHANT_ITEM,true,false,false,CL_good,
				 PlaceHolderHelper(before_name));
			you.equipment[ET_WEAPON]->curse = false;
			you.equipment[ET_WEAPON]->identify_curse = true;
			return true;
		}
		else
		{
			if(pre_iden_){
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_ENCHANT_WEAPON_FAIL),true,false,false,CL_normal);
				return false;
			}
			else{
				printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
				return true;
			}
		}
	}
	else
	{
		if(pre_iden_){
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_CARRYING_WEAPON),true,false,false,CL_normal);
			return false;
		}
		else{
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
			return true;
		}
	}
}



bool enchant_armour_scroll(bool pre_iden_, bool waste_)
{
	static int prev_key = 0;

	if (!waste_) {
		if (iden_list.scroll_list[SCT_ENCHANT_ARMOUR].iden == 3)
			view_item(IVT_ARMOR_ENCHANT, LOC_SYSTEM_DISPLAY_MANAGER_ENCHANT_ARMOUR);
		else
			view_item(IVT_SELECT, LOC_SYSTEM_DISPLAY_MANAGER_USE_TO);
	}
	while(1)
	{
		int key_ = 0;

		InputedKey inputedKey;
		if (!waste_) {
			key_ = waitkeyinput(inputedKey,true);
		}
		else if (prev_key != 0) {
			key_ = prev_key;
		}
		else
			return false;
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			prev_key = key_;
			item *item_ = you.GetItem(key_);
			if(item_)
			{
				string before_name = item_->GetName();
				if(item_->Enchant(ET_ARMOR, 1))
				{
					LocalzationManager::printLogWithKey(LOC_SYSTEM_ITEM_SCROLL_ENCHANT_ARMOUR,true,false,false,CL_good,
						 PlaceHolderHelper(before_name));
					item_->curse = false;
					item_->identify_curse = true;
					return true;
				}
				else
				{
					if (!waste_) {
						changedisplay(DT_GAME);
					}
					if(pre_iden_){
						printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_CANT_ENCHANT_ITEM),true,false,false,CL_normal);
						return false;
					}
					else{
						printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
						return true;
					}
				}

			}
		}
		else if (waste_) {
			return false;
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
				view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_ENCHANT_ARMOUR);
			else
				view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_USE_TO);
		}
		else if(key_ == -1) {			
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				if(iden_list.scroll_list[SCT_ENCHANT_ARMOUR].iden == 3)
					rollback_item(IVT_ARMOR_ENCHANT,LOC_SYSTEM_DISPLAY_MANAGER_ENCHANT_ARMOUR);
				else
					rollback_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_USE_TO);
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
	if (!waste_) {
		changedisplay(DT_GAME);
	}
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
	printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_DETECT_CURSE),true,true,false,CL_normal);
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
				LocalzationManager::printLogWithKey(LOC_SYSTEM_ITEM_SCROLL_CURSE_ITEM,true,false,false,CL_small_danger,
					 PlaceHolderHelper(before_name));
				return true;
			}
		}
	}
	if(pre_iden_){
		printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_CURSE_JEWELLY_FAIL),true,false,false,CL_normal);
		return false;
	}
	else{
		printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND),true,false,false,CL_normal);
		return true;
	}
}
bool recharging_scroll(bool pre_iden_, bool ablity_, bool waste_)
{
	static int prev_key = 0;



	if (!waste_) {
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_CHARGE_SPELLCARD_FAIL),true,false,false,CL_normal);
			if(pre_iden_)
				return false;
			else
				return true;
		}
		if (iden_list.scroll_list[SCT_CHARGING].iden == 3 || ablity_)
			view_item(IVT_SPELLCARD, LOC_SYSTEM_DISPLAY_MANAGER_CHARGING_SPELLCARD);
		else
			view_item(IVT_SELECT, LOC_SYSTEM_DISPLAY_MANAGER_USE_TO);
	}
	while(1)
	{
		int key_ = 0;

		InputedKey inputedKey;
		if (!waste_) {
			key_ = waitkeyinput(inputedKey,true);
		}
		else if (prev_key != 0) {
			key_ = prev_key;
		}
		else
			return false;
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			prev_key = key_;
			item *item_ = you.GetItem(key_);
			if(item_)
			{
				if(item_->isChargable())
				{
					int charging_= SpellcardMaxCharge((spellcard_evoke_type)item_->value2) * rand_float(0.3f,0.7f);

					LocalzationManager::printLogWithKey(LOC_SYSTEM_ITEM_SCROLL_CHARGE_SPELLCARD,true,false,false,CL_good,
						PlaceHolderHelper(item_->GetName()));

					item_->value1 += charging_;
					if(item_->value1>SpellcardMaxCharge((spellcard_evoke_type)item_->value2))
						item_->value1 = SpellcardMaxCharge((spellcard_evoke_type)item_->value2);
					item_->value3 = -2; 					

					return true;
				}
				else if (waste_) {
					return true;
				}
			}
		}
		else if (waste_) {
			return false;
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
				view_item(IVT_SPELLCARD,LOC_SYSTEM_DISPLAY_MANAGER_CHARGING_SPELLCARD);
			else
				view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_USE_TO);
		}
		else if(key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				if(iden_list.scroll_list[SCT_CHARGING].iden == 3 || ablity_)
					rollback_item(IVT_SPELLCARD,LOC_SYSTEM_DISPLAY_MANAGER_CHARGING_SPELLCARD);
				else
					rollback_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_USE_TO);
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
		{
			break;
		}
	}
	if (!waste_) {
		changedisplay(DT_GAME);
	}
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
		view_spell(LOC_SYSTEM_DISPLAY_MANAGER_FORGET_SPELL);
		//changedisplay(DT_SPELL);
		while(1)
		{
			InputedKey inputedKey;
			int key_ = waitkeyinput(inputedKey,true);
			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
				if(spell_list spell_ = (spell_list)you.MemorizeSpell[num])
				{				
					
					changedisplay(DT_GAME);
					LocalzationManager::printLogWithKey(LOC_SYSTEM_ITEM_SCROLL_AMNESIA_ASK,false,false,false,CL_help,
						PlaceHolderHelper(SpellString(spell_)));
					printlog(" (",false,false,false,CL_help);
					printlog("y",false,false,false,CL_help, 'y');
					printlog("/",false,false,false,CL_help);
					printlog("n",false,false,false,CL_help, 'n');
					printlog(") ",false,false,false,CL_help);
					startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
					switch(waitkeyinput())
					{
					case 'Y':
					case 'y':
						{
							endSelection();
							changedisplay(DT_GAME);
							WaitForSingleObject(mutx, INFINITE);
							you.MemorizeSpell[num] = 0;
							you.remainSpellPoiont+=SpellLevel(spell_);
							you.currentSpellNum--;
							ReleaseMutex(mutx);
							LocalzationManager::printLogWithKey(LOC_SYSTEM_ITEM_SCROLL_AMNESIA_SUCCESS,true,false,false,CL_normal,
								PlaceHolderHelper(SpellString(spell_)));
							return true;
						}
					case 'N':
					default:
						endSelection();
						view_spell(LOC_SYSTEM_DISPLAY_MANAGER_FORGET_SPELL);
						//changedisplay(DT_SPELL);
						break;
					}
				}
			}
			else if(key_ == -1) {
				if(inputedKey.isRightClick()) {
					break;
				}
			}
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_REMEMBER_SPELL),true,false,false,CL_normal);	
	}

	if(pre_iden_){
		return false;
	}
	else{
		return true;
	}
}


bool brand_weapon_scroll(bool pre_iden_)
{
	if (you.equipment[ET_WEAPON])
	{
		string before_name = you.equipment[ET_WEAPON]->GetName();
		if (you.equipment[ET_WEAPON] && (you.equipment[ET_WEAPON]->type >= ITM_WEAPON_FIRST && you.equipment[ET_WEAPON]->type<ITM_WEAPON_LAST) && !you.equipment[ET_WEAPON]->isArtifact())
		{
			random_extraction<int> random;
			random.push(WB_FIRE, 30);
			random.push(WB_COLD, 30);
			random.push(WB_POISON, 30);
			random.push(WB_MANA_REGEN, 10);
			random.push(WB_FAST_CAST, 10);
			random.push(WB_PROTECT, 20);
			int brand_ = random.pop();
			LOCALIZATION_ENUM_KEY weapon_type = LOC_SYSTEM_ITEM_SCROLL_BRAND_NORMAL;

			switch (brand_)
			{
			case WB_FIRE:
				weapon_type = LOC_SYSTEM_ITEM_SCROLL_BRAND_FIRE;
				break;
			case WB_COLD:
				weapon_type = LOC_SYSTEM_ITEM_SCROLL_BRAND_COLD;
				break;
			case WB_POISON:
				weapon_type = LOC_SYSTEM_ITEM_SCROLL_BRAND_POISON;
				break;
			case WB_MANA_REGEN:
				weapon_type = LOC_SYSTEM_ITEM_SCROLL_BRAND_MANA_REGEN;
				break;
			case WB_FAST_CAST:
				weapon_type = LOC_SYSTEM_ITEM_SCROLL_BRAND_FAST_CAST;
				break;
			case WB_PROTECT:
				weapon_type = LOC_SYSTEM_ITEM_SCROLL_BRAND_PROTECT;
				break;
			}
			
			LocalzationManager::printLogWithKey(weapon_type,true,false,false,CL_magic,
				PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
			you.equipment[ET_WEAPON]->value5 = brand_;
			you.equipment[ET_WEAPON]->value6 = -1;
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_BRAND_WEAPON) + " ", false, false, false, CL_normal);
			return true;
		}
		else
		{
			if (pre_iden_) {
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_BRAND_WEAPON_FAIL) + " ", false, false, false, CL_normal);
				return false;
			}
			else {
				printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND) + " ", false, false, false, CL_normal);
				return true;
			}
		}
	}
	else
	{
		if (pre_iden_) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_CARRYING_WEAPON) + " ", false, false, false, CL_normal);
			return false;
		}
		else {
			printlog(LocalzationManager::locString(LOC_SYSTEM_NOTHING_HAPPEND) + " ", false, false, false, CL_normal);
			return true;
		}
	}
}