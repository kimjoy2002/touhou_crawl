//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: item_action.cpp
//
// 내용: player의 행동들(아이템 관련 행동들)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "key.h"
#include "player.h"
#include "beam.h"
#include "skill_use.h"
#include "monster_texture.h"
#include "spellcard.h"
#include "dump.h"
#include "option_manager.h"
#include <set>

extern HANDLE mutx;
void GetItemInfor(item *it, bool can_use_, set<char> *key);

bool iteminfor_(int key_, bool gameover);

bool pickup_prev_fail(bool no_speak) {
	if(you.s_lunatic)
	{
		if(!no_speak) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_PICKUP),true,false,false,CL_danger);
		}
		return true;
	}
	if (you.s_evoke_ghost) {
		if(!no_speak) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_PICKUP), true, false, false, CL_normal);
		}
		return true;
	}
	return false;
}


void PickUp()
{
	if(pickup_prev_fail(false)) {
		return;
	}
	int num=0;
	list<item>::iterator it, first_it;
	for(it = env[current_level].item_list.begin();it != env[current_level].item_list.end();)
	{
		list<item>::iterator temp = it++;
		if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
		{
			if(isPick(&(*temp)))
			{
				if(!num++)
					first_it = temp;
			}
		}
		else if(num)
			break;
	}
	if(num)
	{
		if(num==1)
			PickUpNum(first_it,1,false);
		else
			PickUpSelect(first_it,num);

	}
}



void PickUpAll(list<item>::iterator it)
{	
	for(;it != env[current_level].item_list.end();)
	{
		list<item>::iterator temp = it++;
		if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
		{
			if(isPick(&(*temp)))
			{
				if(you.additem(&(*temp)))
				{
					env[current_level].DeleteItem(temp);
					you.time_delay += you.GetNormalDelay();
					you.TurnEnd();
				}
			}
		}
	}
}



void PickUpSelect_logic(list<item>::iterator& it) {
	if(you.additem(&(*it)))
	{
		env[current_level].DeleteItem(it);
		you.time_delay+=you.GetNormalDelay();
		you.TurnEnd();
	}
}

void PickUpSelect(list<item>::iterator it, int num)
{	
	for(;it != env[current_level].item_list.end() && num;num--)
	{
		list<item>::iterator temp = it++;
		if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
		{
			if(isPick(&(*temp)))
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_PICKUP_SELECT_ASK, false, false, false, CL_help,
					PlaceHolderHelper((*temp).GetName(), (*temp).item_color(), (*temp).num > 1 ? true : false));
					
					
				// 	PlaceHolderHelper("y"),
				// 	PlaceHolderHelper("n"),
				// 	PlaceHolderHelper("a"),
				// 	PlaceHolderHelper("*?g,")
				// );
				// (Yes:{1} No:{2} All:{3} Choose:{4})
				/// (예:{1} 아니오:{2} 모두:{3} 선택:{4})
				printlog(" (",false,false,false,CL_help);
				printlog(LocalzationManager::locString(LOC_SYSTEM_YES) + ":y",false,false,false,CL_help, 'y');
				printlog(" ",false,false,false,CL_help);
				printlog(LocalzationManager::locString(LOC_SYSTEM_NO) + ":n",false,false,false,CL_help, 'n');
				printlog(" ",false,false,false,CL_help);
				printlog(LocalzationManager::locString(LOC_SYSTEM_ALL) + ":a",false,false,false,CL_help, 'a');
				printlog(" ",false,false,false,CL_help);
				printlog(LocalzationManager::locString(LOC_SYSTEM_SELECT) + ":*?g,",false,false,false,CL_help, '*');
				printlog(") ",true,false,false,CL_help);
				startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N, 'a', '*'});
				InputedKey inputedKey;
				switch(waitkeyinput(inputedKey))
				{
				case -1:
					if(inputedKey.isLeftClick()) {
						//편의를 위해 좌클릭은 아이템을 줍는다
						//ESC PASSTHORUGH
					}
					else {
						break;
					}
				case 'y':
				case 'Y':
					PickUpSelect_logic(temp);
					break;
				case 'a':
					PickUpNum(temp,num,false);
					endSelection();
					return;
				case '*':
				case '?':
				case 'g':
				case ',':
					iteminfor_pick();
					endSelection();
					return;
				case 'o':
					//자동탐색을 넣는다.
					break;
				default:
					break;
				}
				endSelection();
			}
		}
	}
}
bool PickUpNum(list<item>::iterator it, int num, bool no_delay)
{
	while(num>0)
	{
		list<item>::iterator temp = it;
		if(num>1) it++;
		if(isPick(&(*temp)))
		{
			if(you.additem(&(*temp),!no_delay))
			{
				env[current_level].DeleteItem(temp);
				if(!no_delay)
				{
					bool item_delete= false;
					you.time_delay+=you.GetNormalDelay();
					you.TurnEnd(&item_delete);
					if(item_delete)
						return true; //아이템을 줍는 도중 아이템이 삭제되었다.

					switch(you.inter)
					{
					case IT_POISON:
					case IT_TELE:
					case IT_SMOKE:
					case IT_EVENT:
					case IT_DAMAGE:
					case IT_MAX_ITEM:
						return true;
					default:
						break;
					}
				}
			}
			else {
				switch(you.inter)
				{
				case IT_POISON:
				case IT_TELE:
				case IT_SMOKE:
				case IT_EVENT:
				case IT_DAMAGE:
				case IT_MAX_ITEM:
					return true;
				default:
					break;
				}
				return false;
			}
			num--;
		}
	}
	return false;
}

int isPick(const item* t)
{
	return 1;
}




void iteminfor_pick()
{
	view_item(IVT_PICK,LOC_SYSTEM_DISPLAY_MANAGER_PICK);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey, true);

		if(key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
			int char_ = DisplayManager.positionToChar();
			if(char_) {
				if(key_ == GVK_BUTTON_A_LONG) {
					key_ = -1;
					inputedKey.mouse = MKIND_ITEM_DESCRIPTION;
					inputedKey.val1 = char_;
				} else {
					key_ = char_;
				}
			}
		}

		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			CheckKey(key_);
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			DisplayManager.addPosition(1);
		}
		else if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if( key_ == ',' )
		{
			AllCheckKey();
		}
		else if(key_ == VK_RETURN)
		{
			changedisplay(DT_GAME);
			list<item>::iterator it = env[current_level].GetPositiontoitem(you.position);
			list<item>::iterator end = env[current_level].GetPositiontoitemend(you.position);
			for(;it != end;)
			{
				list<item>::iterator temp = it++;
				if(GetItemofKey(temp,end))
				{	
					if(you.additem(&(*temp)))
					{
						env[current_level].DeleteItem(temp);
						you.time_delay+=you.GetNormalDelay();
						you.TurnEnd();
						it = env[current_level].GetPositiontoitem(you.position);
						end = env[current_level].GetPositiontoitemend(you.position);
					}
					else
						break;
				}
			}
			break;
		}
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				int getItemVal = asctonum(inputedKey.val1);
				list<item>::iterator it = env[current_level].GetPositiontoitem(you.position);
				list<item>::iterator end = env[current_level].GetPositiontoitemend(you.position);
				for(;it != end;it++)
				{
					if(getItemVal==0)
					{	
						iteminfor_(&(*it), true);
						break;
					} else {
						getItemVal--;
					}
				}
				rollback_item(IVT_PICK,LOC_SYSTEM_DISPLAY_MANAGER_PICK);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if (inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE ||
				key_ == GVK_BUTTON_B ||
				key_ == GVK_BUTTON_B_LONG)
			break;

	}
	changedisplay(DT_GAME);
}


void discard(list<item>::iterator it, int number)
{
	if (number == 0)
		number = it->num;
	int drop_number = number;
	if (you.god == GT_JOON_AND_SION || you.GetPunish(GT_JOON_AND_SION))
	{
		if ((*it).type == ITM_POTION || (*it).type == ITM_SCROLL) {
			for (int i = 0; i < number; i++) {
				if (you.god_value[GT_JOON_AND_SION][0] == 2 || randA(3) == 0) //25%
					drop_number--;
			}
		}
	}
	if (drop_number >= 1) {
		item *temp2 = env[current_level].AddItem(you.position, &(*it), drop_number);
		temp2->drop = true;
		temp2->waste = 10000; //항상 소멸 정도를 초기화

		LocalzationManager::printLogWithKey(LOC_SYSTEM_DROP_ITEM,drop_number == number,false,false,CL_normal,
			PlaceHolderHelper(temp2->GetName(number), temp2->item_color(), drop_number>1));
	}
	else {
		LocalzationManager::printLogWithKey(LOC_SYSTEM_DROP_ITEM,drop_number == number,false,false,CL_normal,
			PlaceHolderHelper((*it).GetName(number), (*it).item_color(), drop_number>1));
	}
	if(drop_number != number) {
		if(drop_number>=1) {
			printlog(LocalzationManager::formatString(LOC_SYSTEM_DROP_ITEM_SION_ALL, PlaceHolderHelper(std::to_string(number-drop_number))), true, false, false, CL_small_danger);
		}
		else  {
			printlog(LocalzationManager::locString(LOC_SYSTEM_DROP_ITEM_SION_ALL), true, false, false, CL_small_danger);
		}
	}
	you.DeleteItem(it,number);
	changedisplay(DT_GAME);
	you.time_delay+=you.GetNormalDelay();
	you.TurnEnd();
}



void iteminfor_discard()
{	
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_DISCRAD),true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_DISCRAD), true, false, false, CL_normal);
		return;
	}
	int i=0;
	view_item(IVT_DISCARD,LOC_SYSTEM_DISPLAY_MANAGER_DISCARD);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey, true);
		
		if(key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
			int char_ = DisplayManager.positionToChar();
			if(char_) {
				if(key_ == GVK_BUTTON_A_LONG) {
					key_ = -1;
					inputedKey.mouse = MKIND_ITEM_DESCRIPTION;
					inputedKey.val1 = char_;
				} else {
					key_ = char_;
				}
			}
		}

		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			CheckKey(key_,i);
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			DisplayManager.addPosition(1);
		}
		else if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if((key_ >= '0' && key_ <= '9'))
		{
			i= i*10+key_-'0';
		}
		else if(key_ == VK_RETURN || key_ == GVK_BUTTON_B)
		{
			list<item>::iterator it = you.item_list.begin();
			list<item>::iterator end = you.item_list.end();
			for(;it != end;)
			{
				list<item>::iterator temp = it++;
				if(GetItemofKey(temp,end))
				{	
					if(you.possibleunequip(temp))
					{
						discard(temp,GetItemofNum(temp,end));
					}
					else
						break;
				}
			}
			break;
		}
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_DISCARD,LOC_SYSTEM_DISPLAY_MANAGER_DISCARD);
				setDisplayMove(get_item_move_);
			}
			else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			}
			else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			}
			else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE || key_ == GVK_BUTTON_B_LONG)
			break;

	}
	changedisplay(DT_GAME);
}

void fast_discard()
{	
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_DISCRAD),true,false,false,CL_danger);
		return;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_DISCRAD), true, false, false, CL_normal);
		return;
	}
	if(!you.final_item)
		return;
	for(list<item>::iterator it = you.item_list.begin();it != you.item_list.end();it++)
	{
		if(it->id == you.final_item)
		{
			if(you.possibleunequip(it))
			{
				discard(it,you.final_num);
				you.final_item = 0;
			}
			you.SetPrevAction('D');
			return;
		}
	}
}

bool eat_prev_fail() {
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_EAT),true,false,false,CL_danger);
		return true;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_EAT), true, false, false, CL_normal);
		return true;
	}
	if (you.drowned)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY_EAT), true, false, false, CL_danger);
		return true;
	}
	if(you.power >= 500 && !(you.god == GT_MINORIKO))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_ALREADY_FULL_POWER),true,false,false,CL_normal);
		return true;
	}
	return false;
}

void Eatting(char auto_)
{
	if(eat_prev_fail()) {
		return;
	}
	view_item(IVT_FOOD,LOC_SYSTEM_DISPLAY_MANAGER_FOOD);
	while(1)
	{
		int key_ = auto_;
		InputedKey inputedKey;
		if (key_ == 0)
			key_ = waitkeyinput(inputedKey,true);


		if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
			int char_ = DisplayManager.positionToChar();
			if(char_) {
				if(key_ == GVK_BUTTON_A_LONG) {
					key_ = -1;
					inputedKey.mouse = MKIND_ITEM_DESCRIPTION;
					inputedKey.val1 = char_;
				} else {
					key_ = char_;
				}
			}
		}

		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.Eat(key_);
			you.SetPrevAction('e', key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			DisplayManager.addPosition(1);
		}
		else if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
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
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_FOOD);
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_FOOD,LOC_SYSTEM_DISPLAY_MANAGER_FOOD);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE||
				key_ == GVK_BUTTON_B ||
				key_ == GVK_BUTTON_B_LONG)
			break;
	}
	changedisplay(DT_GAME);
}


bool drink_prev_fail() {
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_DRINK),true,false,false,CL_danger);
		return true;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_DRINK), true, false, false, CL_normal);
		return true;
	}
	if (you.drowned)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY_DRINK), true, false, false, CL_danger);
		return true;
	}
	return false;
}

void drink_logic(int key_) {
	if(you.Drink(key_))
	{			
		you.time_delay += you.GetNormalDelay();
		you.doingActionDump(DACT_USE, LocalzationManager::locString(LOC_SYSTEM_ITEM_POTION_POTION));
		changedisplay(DT_GAME);
		if(you.god == GT_EIRIN)
		{
			if(randA(2))
			{
				you.PietyUpDown(1);
				you.GiftCount(1);
			}
		}
		you.SetPrevAction('q', key_);
		you.TurnEnd();
	}
}


void Drinking(char auto_)
{
	if(drink_prev_fail()) {
		return;
	}
	view_item(IVT_POTION,LOC_SYSTEM_DISPLAY_MANAGER_DRINK);
	while(1)
	{
		int key_ = auto_;
		InputedKey inputedKey;
		if(key_ == 0 )
			key_ = waitkeyinput(inputedKey,true);


		if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
			int char_ = DisplayManager.positionToChar();
			if(char_) {
				if(key_ == GVK_BUTTON_A_LONG) {
					key_ = -1;
					inputedKey.mouse = MKIND_ITEM_DESCRIPTION;
					inputedKey.val1 = char_;
				} else {
					key_ = char_;
				}
			}
		}

		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			drink_logic(key_);
			break;
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			DisplayManager.addPosition(1);
		}
		else if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
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
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_DRINK);
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_POTION,LOC_SYSTEM_DISPLAY_MANAGER_DRINK);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE ||
				key_ == GVK_BUTTON_B ||
				key_ == GVK_BUTTON_B_LONG)
		{
			break;
		}
	}
	changedisplay(DT_GAME);
}

bool evoke_prev_fail() {
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY),true,false,false,CL_danger);
		return true;
	}
	return false;
}

void evoke_logic(int key_, char auto_) {
	changedisplay(DT_GAME);
	if(you.Evoke(key_, auto_>0))
	{
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		you.SetPrevAction('v', key_);
	}
}

void Spelllcard_Evoke(char auto_)
{
	if(evoke_prev_fail()) {
		return;
	}
	view_item(IVT_EVOKE,LOC_SYSTEM_DISPLAY_MANAGER_EVOKE);
	while(1)
	{
		int key_ = auto_;
		InputedKey inputedKey;
		if (key_ == 0)
			key_ = waitkeyinput(inputedKey,true);

		if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
			int char_ = DisplayManager.positionToChar();
			if(char_) {
				if(key_ == GVK_BUTTON_A_LONG) {
					key_ = -1;
					inputedKey.mouse = MKIND_ITEM_DESCRIPTION;
					inputedKey.val1 = char_;
				} else {
					key_ = char_;
				}
			}
		}
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			evoke_logic(key_,auto_);
			break;
		//	CheckKey(key_,i);
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			DisplayManager.addPosition(1);
		}
		else if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
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
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_EVOKE);
		else if( key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_EVOKE,LOC_SYSTEM_DISPLAY_MANAGER_EVOKE);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE||
				key_ == GVK_BUTTON_B ||
				key_ == GVK_BUTTON_B_LONG)
		{
			break;
		}
	}
	changedisplay(DT_GAME);
}

void memorize_action(int spell_);

bool read_prev_fail() {
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_READ),true,false,false,CL_danger);
		return true;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_READ), true, false, false, CL_normal);
		return true;
	}
	if (you.drowned)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY_READ), true, false, false, CL_danger);
		return true;
	}
	if(env[current_level].isSilence(you.position))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SILENCE_PENALTY),true,false,false,CL_normal);
		return true;
	}
	return false;
}

void _infor_(string str);

void Memorize_book(int key_) {
	string blank(12,' ');
	item* item_ = you.GetItem(key_);
	if(item_ == nullptr)
		return;
	if(item_->value0>=0)	
	{
		iden_list.books_list[item_->value0] = true;
		item_->identify = true;
	}
	if(item_->value0==-2)
	{					
		item_->identify = true;
	}
	while(1)
	{
		WaitForSingleObject(mutx, INFINITE);
		deletesub();
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		GetItemInfor(item_, false, NULL);
		ReleaseMutex(mutx);
		changedisplay(DT_SUB_TEXT);
		int key_;
		while(1) {
			key_ = waitkeyinput(true);
			if(key_ == VK_UP)
				DisplayManager.addPosition(-1);
			else if(key_ == VK_DOWN)
				DisplayManager.addPosition(1);
			else if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
				key_ = DisplayManager.positionToChar();
				break;
			} else {
				break;
			}
		}
		if( (key_ >= 'a' && key_ <= 'f'))
		{
			if(int spell_ = item_->GetValue(key_ - 'a'+1))
			{
				if (you.isMemorize(spell_)) {
					changedisplay(DT_GAME);
					printlog(LocalzationManager::locString(LOC_SYSTEM_MEMORIZE_SPELL_ALREADY), true, false, false, CL_normal);
					return;
				}
				WaitForSingleObject(mutx, INFINITE);
				deletesub();
				printsub("",true,CL_normal);
				printsub("",true,CL_normal);
				printsub("",true,CL_normal);
				printsub(blank,false,CL_normal);
				_infor_(GetSpellInfor((spell_list)spell_));
				_infor_("\n\n");
				printsub(LocalzationManager::formatString(LOC_SYSTEM_MEMORIZE_HELP, PlaceHolderHelper("m")), false, CL_normal, 'm');
				_infor_("\n");
				ReleaseMutex(mutx);
				int memory_ = waitkeyinput();

				if(memory_ == 'm')
				{
					memorize_action(spell_);
					return;
				}
				continue;
			}	
		}
		view_item(IVT_SCROLL,LOC_SYSTEM_DISPLAY_MANAGER_READ);
		break;
	}
}


void Reading_logic(int key_) {
	item* item_ = you.GetItem(key_);
	if(item_ == nullptr)
		return;
	if(you.Read(key_))
	{
		you.doingActionDump(DACT_USE, LocalzationManager::locString(LOC_SYSTEM_ITEM_CATEGORY_SCROLL));
		you.time_delay += you.GetNormalDelay();
		changedisplay(DT_GAME);
		you.TurnEnd();
		you.SetPrevAction('r', key_);
	}
}

void Reading(char auto_)
{
	if(read_prev_fail()) {
		return;
	}
	view_item(IVT_SCROLL,LOC_SYSTEM_DISPLAY_MANAGER_READ);
	while(1)
	{
		int key_ = auto_;
		InputedKey inputedKey;
		if (key_ == 0)
			key_ = waitkeyinput(inputedKey,true);


		if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
			int char_ = DisplayManager.positionToChar();
			if(char_) {
				if(key_ == GVK_BUTTON_A_LONG) {
					key_ = -1;
					inputedKey.mouse = MKIND_ITEM_DESCRIPTION;
					inputedKey.val1 = char_;
				} else {
					key_ = char_;
				}
			}
		}

		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			item* item_ = you.GetItem(key_);
			if(!item_)
				continue;
			if(item_->type == ITM_BOOK)
			{
				Memorize_book(key_);
			}
			else if(item_->type == ITM_SCROLL)
			{
				Reading_logic(key_);
			}
			break;
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			DisplayManager.addPosition(1);
		}
		else if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
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
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_READ);
		else if(key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_SCROLL,LOC_SYSTEM_DISPLAY_MANAGER_READ);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE||
				key_ == GVK_BUTTON_B ||
				key_ == GVK_BUTTON_B_LONG)
			break;
	}
	changedisplay(DT_GAME);
}