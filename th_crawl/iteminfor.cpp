//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: iteminfor.cpp
//
// 내용: 아이템의 정보띄우기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "key.h"
#include "player.h"
#include "beam.h"
#include "monster_texture.h"
#include "skill_use.h"
#include "weapon.h"
#include "armour.h"
#include "evoke.h"
#include "book.h"
#include "option_manager.h"
#include "tribe.h"
#include "dump.h"
#include "god.h"
#include "mon_infor.h"
#include <set>
#include <iomanip> 

extern HANDLE mutx;
extern int shieldPanaltyOfWeapon(item_type type, int weapon_kind);
void discard(list<item>::iterator it, int number);


void GetItemInfor(item *it, bool can_use_, set<char> *key);

void memorize_action(int spell_)
{
	changedisplay(DT_GAME);
	if(spell_ == SPL_NONE)
		printlog(LocalzationManager::locString(LOC_SYSTEM_MEMORIZE_SPELL_NON_EXIST),true,false,false,CL_normal);
	else
	{		
		bool ok_ = true;
		while(ok_)
		{
			printlog(SpellString((spell_list)spell_),false,false,false,CL_normal);
			printlog(" " + LocalzationManager::locString(LOC_SYSTEM_MEMORIZE_SPELL_ASK),false,false,false,CL_help);
			printlog(" (",false,false,false,CL_help);
			printlog("y",false,false,false,CL_help, 'y');
			printlog("/",false,false,false,CL_help);
			printlog("n",false,false,false,CL_help, 'n');
			printlog(") ",false,false,false,CL_help);
			startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
			ostringstream ss;
			ss << " [" <<  LocalzationManager::locString(LOC_SYSTEM_FAILURE_RATE) << ": " << (100-you.GetSpellSuccess(spell_)) << "% " << 
				LocalzationManager::locString(LOC_SYSTEM_REMAIN_SPELLPOINT) << ": " << you.remainSpellPoiont << "]"; 
			
			printlog(ss.str(),true,false,false,CL_warning);
			InputedKey inputedKey;
			switch(waitkeyinput(inputedKey))
			{
			case 'Y':
			case 'y':
			case GVK_BUTTON_A:
			case GVK_BUTTON_A_LONG:
				you.Memorize(spell_);
				endSelection();
				ok_ = false;
				break;
			case -1:
				if(inputedKey.isRightClick()) {
					//ESC PASSTHORUGH
				}
				else {
					break;
				}
			case 'N':
			case 'n':
			case VK_ESCAPE:
			case GVK_BUTTON_B:
			case GVK_BUTTON_B_LONG:
				endSelection();
				printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE),true,false,false,CL_help);
				ok_ = false;
				break;
			default:
				printlog(LocalzationManager::locString(LOC_SYSTEM_PLEASE_SELECT_YN),true,false,false,CL_help);
				break;
			}
		}
	}
	return;

}

//true l이 r보다 크다
bool compareAlphabet(char l_, char r_)
{
	bool l_small = l_ >= 'a' && l_ <= 'z';
	bool r_small = l_ >= 'a' && l_ <= 'z';
	if (l_small && !r_small)
		return false;
	else if(!l_small && r_small)
		return true;
	return l_ > r_;
}

void swap_list_items(list<item>& l, list<item>::iterator a, list<item>::iterator b)
{
	list<item>::iterator aPlus = a;
	++aPlus; // after position of a, will not be invalidated
	l.splice(b, l, a); // move a before b, invalidates a
	l.splice(aPlus, l, b); // move b before aPlus (where A was)
}


void _infor_(string str);

bool iteminfor_(item *item_, bool onlyinfor) {
	int get_item_move_ = getDisplayMove();
	string blank(12,' ');
	while(1)
	{
		set<char> ket_list;
		WaitForSingleObject(mutx, INFINITE);
		deletesub();
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		GetItemInfor(item_, !onlyinfor, &ket_list);
		ReleaseMutex(mutx);
		changedisplay(DT_SUB_TEXT);
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);
		if(item_->type == ITM_BOOK && (key_ >= 'a' && key_ <= 'f'))
		{
			if(int spell_ = item_->GetValue(key_ - 'a'+1))
			{	
				WaitForSingleObject(mutx, INFINITE);
				deletesub();
				printsub("",true,CL_normal);
				printsub("",true,CL_normal);
				printsub("",true,CL_normal);
				printsub(blank,false,CL_normal);
				_infor_(GetSpellInfor((spell_list)spell_));
				_infor_("\n\n");
				if(!onlyinfor) {
					printsub(LocalzationManager::formatString(LOC_SYSTEM_MEMORIZE_HELP, PlaceHolderHelper("m")), false, CL_normal, 'm');
					_infor_("\n");
				}
				ReleaseMutex(mutx);
				int memory_ = waitkeyinput();

				if(memory_ == 'm' && !onlyinfor)
				{
					if (you.isMemorize(spell_)) {
						changedisplay(DT_GAME);
						printlog(LocalzationManager::locString(LOC_SYSTEM_MEMORIZE_SPELL_ALREADY), true, false, false, CL_normal);
						return true;
					}
					memorize_action(spell_);
					return true;
				}
				continue;
			}
		}
		else if (!ket_list.empty())
		{

			if (ket_list.count(key_) >= 1)
			{
				switch (key_)
				{
				case '=': //단축키 바꾸기
				{
					changedisplay(DT_GAME);
					printlog(LocalzationManager::locString(LOC_SYSTEM_ALPHABET_ASK) + " (a-z, A-Z)", true, false, false, CL_help);
					{
						int alphabet_ = waitkeyinput();
						if ((alphabet_ >= 'a' && alphabet_ <= 'z') ||
							(alphabet_ >= 'A' && alphabet_ <= 'Z'))
						{
							list<item>::iterator old_;
							list<item>::iterator new_;
							for (old_ = you.item_list.begin(); old_ != you.item_list.end(); old_++)
							{
								if (old_->id == alphabet_)
								{
									break;
								}
							}
							for (new_ = you.item_list.begin(); new_ != you.item_list.end(); new_++)
							{
								if (new_->id == item_->id)
								{
									break;
								}
							}
							if (new_ == you.item_list.end())
								break;

							if (old_ != you.item_list.end())
							{
								old_->id = item_->id;
								new_->id = alphabet_;
								swap_list_items(you.item_list, old_, new_);

								ostringstream ss;
								ss << old_->id << " - " << old_->GetName() << ", ";
								printlog(ss.str(), false, false, false, old_->item_color());
							}
							else
							{
								list<item>::iterator it;
								for (it = you.item_list.begin(); it != you.item_list.end(); it++)
								{
									if (compareAlphabet(it->id, alphabet_))
									{
										new_->id = alphabet_;
										you.item_list.splice(it, you.item_list, new_);
										break;
									}
								}
								if (it == you.item_list.end())
								{
									new_->id = alphabet_;
									you.item_list.splice(it, you.item_list, new_);
								}
							}
							ostringstream ss;
							ss << new_->id << " - " << new_->GetName() << " ";
							printlog(ss.str(), false, false, false, new_->item_color());
						}
					}
					return true;
				}
				case 'w': //장착	
					changedisplay(DT_GAME);
					if (you.s_lunatic)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY), true, false, false, CL_danger);
						return true;
					}
					if (you.s_evoke_ghost) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY), true, false, false, CL_normal);
						return true;
					}

					if (item_->type >= ITM_WEAPON_FIRST &&item_->type < ITM_WEAPON_LAST)
					{
						if (you.drowned)
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY), true, false, false, CL_danger);
							return true;
						}
						you.equip(item_->id, ET_WEAPON);
					}
					else if (item_->type >= ITM_ARMOR_BODY_FIRST &&item_->type < ITM_ARMOR_LAST)
					{
						if (you.drowned)
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY), true, false, false, CL_danger);
							return true;
						}
						you.equiparmor(item_->id);
					}
					else if (item_->type == ITM_AMULET)
					{
						you.equipjewerly(item_->id);
					}
					else if (item_->type == ITM_RING)
					{
						you.equipjewerly(item_->id);
					}
					return true;
				case 'u': //벗기
					changedisplay(DT_GAME);
					if (you.s_lunatic)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY), true, false, false, CL_danger);
						return true;
					}
					if (you.s_evoke_ghost) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY), true, false, false, CL_normal);
						return true;
					}
					if (item_->type >= ITM_WEAPON_FIRST &&item_->type < ITM_WEAPON_LAST)
					{
						if (you.drowned)
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY), true, false, false, CL_danger);
							return true;
						}
						if (!you.unequip(ET_WEAPON))
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_CURSED_PENALTY), true, false, false, CL_normal);
						}
					}
					else if (item_->type >= ITM_ARMOR_BODY_FIRST &&item_->type < ITM_ARMOR_LAST)
					{
						if (you.drowned)
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY), true, false, false, CL_danger);
							return true;
						}
						you.unequiparmor(item_->id);
					}
					else if (item_->type == ITM_AMULET)
					{
						you.unequipjewerly(item_->id);
					}
					else if (item_->type == ITM_RING)
					{
						you.unequipjewerly(item_->id);
					}
					return true;
				case 'f': //탄막
				{
					changedisplay(DT_GAME);
					you.throw_weapon = item_;
					ostringstream ss;
					ss << item_->id << " - " << item_->GetName() << "(" << LocalzationManager::locString(LOC_SYSTEM_EQUIP_TANMAC) << ") ";
					printlog(ss.str(), false, false, false, item_->item_color());
				}
					return true;
				case 'q': //마시기
					changedisplay(DT_GAME);
					if (you.s_lunatic)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY), true, false, false, CL_danger);
						return true;
					}
					if (you.s_evoke_ghost) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY), true, false, false, CL_normal);
						return true;
					}
					if (you.drowned)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY), true, false, false, CL_danger);
						return true;
					}
					if (you.Drink(item_->id))
					{
						you.time_delay += you.GetNormalDelay();
						you.doingActionDump(DACT_USE, LocalzationManager::locString(LOC_SYSTEM_ITEM_POTION_POTION));
						changedisplay(DT_GAME);
						if (you.god == GT_EIRIN)
						{
							if (randA(2))
							{
								you.PietyUpDown(1);
								you.GiftCount(1);
							}
						}
						you.TurnEnd();
					}
					return true;
				case 'e': //먹기
					changedisplay(DT_GAME);
					if (you.s_lunatic)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY), true, false, false, CL_danger);
						return true;
					}
					if (you.s_evoke_ghost) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY), true, false, false, CL_normal);
						return true;
					}
					if (you.drowned)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY), true, false, false, CL_danger);
						return true;
					}
					you.Eat(item_->id);
					return true;
				case 'r': //읽기
					changedisplay(DT_GAME);
					if (you.s_lunatic)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY), true, false, false, CL_danger);
						return true;
					}
					if (you.s_evoke_ghost) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY), true, false, false, CL_normal);
						return true;
					}
					if (you.drowned)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY), true, false, false, CL_danger);
						return true;
					}
					if(you.Read(item_->id))
					{
						you.doingActionDump(DACT_USE, LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_SCROLL));
						you.time_delay += you.GetNormalDelay();
						changedisplay(DT_GAME);
						you.TurnEnd();
					}
					return true;
				case 'v': //발동
					changedisplay(DT_GAME);
					if (you.s_lunatic)
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY), true, false, false, CL_danger);
						return true;
					}
					if (you.s_evoke_ghost &&
						!(item_->type == ITM_MISCELLANEOUS && item_->value1 == EVK_GHOST_BALL)
						) {
						printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY), true, false, false, CL_normal);
						return true;
					}
					if (you.Evoke(item_->id, false))
					{
						you.time_delay += you.GetNormalDelay();
						you.TurnEnd();
					}
					return true;
				case 'd': //버리기
				case 'D':
					{
						changedisplay(DT_GAME);
						if (you.s_lunatic)
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY), true, false, false, CL_danger);
							return true;
						}
						if (you.s_evoke_ghost) {
							printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY), true, false, false, CL_normal);
							return true;
						}
						bool discard_ = false;
						for (auto it = you.item_list.begin(); it != you.item_list.end(); it++)
						{
							if (&(*it) == item_)
							{
								if (you.possibleunequip(it))
								{
									discard(it, GetItemofNum(it, you.item_list.end()));
									discard_ = true;
									break;
								}
								else
								{
									break;
								}
							}
						}
						if (!discard_)
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_NOT_EXIST), true, false, false, CL_normal);
						}
						return true;
					}
				}
			}
		}
		break;
	}
	if(!onlyinfor) {
		view_item(IVT_INFOR,LOC_SYSTEM_DISPLAY_MANAGER_ITEMINFOR);
		setDisplayMove(get_item_move_);
	}
	return false;
}

bool iteminfor_(int key_, bool onlyinfor) {

	item *item_ = you.GetItem(key_);
	if(item_)
	{
		return iteminfor_(item_, onlyinfor);
	}
	return false;
}


void iteminfor(bool gameover)
{
	view_item(IVT_INFOR,gameover?LOC_SYSTEM_DISPLAY_MANAGER_GAMEOVER:LOC_SYSTEM_DISPLAY_MANAGER_ITEMINFOR);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);

		if(!gameover && (key_ == VK_RETURN || key_ == GVK_BUTTON_A)) {
			int char_ = DisplayManager.positionToChar();
			if(char_) {
				key_ = char_;
			}
		}

		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			int get_item_move_ = getDisplayMove();
			if(iteminfor_(key_, gameover))
				break;
			if(gameover) {
				view_item(IVT_INFOR,LOC_SYSTEM_DISPLAY_MANAGER_GAMEOVER);
				setDisplayMove(get_item_move_);
			}
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			DisplayManager.addPosition(1);
			//changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
			//changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if(key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, gameover))
					break;
				if(gameover) {
					view_item(IVT_INFOR,LOC_SYSTEM_DISPLAY_MANAGER_GAMEOVER);
					setDisplayMove(get_item_move_);
				}
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if (inputedKey.isRightClick() || (inputedKey.isLeftClick() && gameover)) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE ||
				key_ == GVK_BUTTON_B ||
				key_ == GVK_BUTTON_B_LONG || (key_ == VK_RETURN && gameover)) {
			break;
		}
	}
	changedisplay(DT_GAME);
}

void _infor_(string str) {
	string blank(12,' ');	
	
	std::istringstream iss(str);
	std::string line;
	bool first_ = true;
	while (std::getline(iss, line)) {
		if(!first_) {
			printsub("", true, CL_normal);
			printsub(blank, false, CL_normal);
		}
		printsub(line, false, CL_normal);
		first_ =  false;
	}
	if (!str.empty() && str.back() == '\n') {
		printsub("", true, CL_normal);
		printsub(blank, false, CL_normal);
	}
}


void GetItemInfor(item *it, bool can_use_, set<char> *key)
{
	vector<pair<string,int>> use_text_;
	vector<string> key_;
	string blank(12,' ');
	
	printsub(blank,false,CL_normal);
	printsub(it->GetName(),true,it->item_color());
	printsub("",true,CL_normal);
	printsub(blank,false,CL_normal);

	if (can_use_)
	{
		use_text_.push_back({"(=)" + LocalzationManager::locString(LOC_SYSTEM_HOTKEYCHANGE), '='});
		if (key) key->insert('=');
	}
	switch (it->type)
	{
		//case ITM_WEAPON_DAGGER:
		//	_infor_("단검의 일종으로 작은 칼이다. 적을 기습하는데 특히 유용한 무기이다.\n\
		//			  날려서 탄막으로 쓰는 것도 가능하다.\n";
	case ITM_WEAPON_SHORTBLADE:
	case ITM_WEAPON_LONGBLADE:
	case ITM_WEAPON_MACE:
	case ITM_WEAPON_SPEAR:
	case ITM_WEAPON_AXE:
		//case ITM_WEAPON_BOW:
	{
		skill_type ski_ = SKT_MACE;
		switch (it->type)
		{
		case ITM_WEAPON_SHORTBLADE:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SHORTBLADE));
			ski_ = SKT_SHORTBLADE;
			switch (it->value0)
			{
			case 0:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SHORTBLADE_DAGGER));
				break;
			case 1:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SHORTBLADE_THROWING_KNIFE));
				break;
			case 2:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SHORTBLADE_SHORTBLADE_SHORTSWORD));
				break;
			}
			break;
		case ITM_WEAPON_LONGBLADE:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_LONGBLADE));
			ski_ = SKT_LONGBLADE;
			switch (it->value0)
			{
			case 0:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_LONGBLADE_KATANA));
				break;
			case 1:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_LONGBLADE_SCIMITAR));
				break;
			case 2:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_LONGBLADE_GREATSWORD));
				break;
			case 3:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_LONGBLADE_CHAKRAM));
				break;
			}
			break;
		case ITM_WEAPON_MACE:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_MACE));
			switch (it->value0)
			{
			case 0:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_MACE_GOHEI));
				break;
			case 1:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_MACE_BROOMSTICK));
				break;
			case 2:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_MACE_UMBRELLA));
				break;
			case 3:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_MACE_DAUZING_ROD));
				break;
			case 4:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_MACE_ONBASIRA));
				break;
			}
			ski_ = SKT_MACE;
			break;
		case ITM_WEAPON_SPEAR:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SPEAR));
			ski_ = SKT_SPEAR;
			switch (it->value0)
			{
			case 0:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SPEAR_SPEAR));
				break;
			case 1:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SPEAR_JAVELIN));
				break;
			case 2:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SPEAR_SCYTHE));
				break;
			case 3:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SPEAR_TRIDENT));
				break;
			case 4:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_SPEAR_BAMBOO_SPEAR));
				break;
			}
			break;
		case ITM_WEAPON_AXE:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_AXE));
			switch (it->value0)
			{
			case 0:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_AXE_HANDAXE));
				break;
			case 1:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_AXE_BATTLEAXE));
				break;
			case 2:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_AXE_ANCHOR));
				break;
			}
			break;
		default:
			break;
		}

		if (it->value5 && it->value6)
		{
			_infor_("\n\n");
			_infor_(GetBrandInfor((weapon_brand)it->value5));
			_infor_("\n");
		}
		
		{
			//스킬레벨 설명해주기
			ostringstream ss;
			ostringstream temp;

			ss << "\n\n";
			ss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_INFO1,
					PlaceHolderHelper(skill_string(ski_)),
					PlaceHolderHelper(to_string(you.GetSkillLevel(ski_, true))));
			ss << "\n";

			temp << LocalzationManager::locString(LOC_SYSTEM_ATTACK_VALUE) << ": " << it->value2;;
			ss << temp.str();
			if(PrintCharWidth(temp.str()) < 20)
				ss << std::string(20-PrintCharWidth(temp.str()), ' ');
			else
				ss << " ";

			temp.str("");
			temp.clear();
			temp << LocalzationManager::locString(LOC_SYSTEM_HIT_VALUE) << ": " << it->value1;
			ss << temp.str() << "\n";


			temp.str("");
			temp.clear();
			temp << LocalzationManager::locString(LOC_SYSTEM_CURRENT_ATTACK_SPEED) << ": " <<  (max<float>((it->value8)/100, (it->value7 - you.GetSkillLevel(ski_, true) / 2.0f)) / 10.0f);
			ss << temp.str();
			if(PrintCharWidth(temp.str()) < 20)
				ss << std::string(20-PrintCharWidth(temp.str()), ' ');
			else
				ss << " ";


			temp.str("");
			temp.clear();
			temp << "( " << LocalzationManager::locString(LOC_SYSTEM_BASE_ATTACK_SPEED) << ": " << (it->value7 / 10.0f);
			ss << temp.str();
			if(PrintCharWidth(temp.str()) < 20)
				ss << std::string(20-PrintCharWidth(temp.str()), ' ');
			else
				ss << " ";


			temp.str("");
			temp.clear();
			temp << LocalzationManager::locString(LOC_SYSTEM_MINIMUM_ATTACK_SPEED) << ": " << ( it->value8/10.0f) << " )";
			ss << temp.str();

			if (shieldPanaltyOfWeapon(it->type, it->value0)) {
				ss << "\n" << LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_INFO2, 
					PlaceHolderHelper(float_to_string(shieldPanaltyOfWeapon(it->type, it->value0) / 10.0f)));
			}
			_infor_(ss.str());
		}


		if (it->can_throw)
		{
			_infor_("\n\n");
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_INFO3));
			_infor_("\n");
			_infor_(LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_WEAPON_INFO4, 
					PlaceHolderHelper(float_to_string(you.GetThrowDelay((*it).type, false) / 10.0f)),
					PlaceHolderHelper(to_string(you.GetSkillLevel(SKT_TANMAC, true)))));
		}

		{
			_infor_("\n\n");
			_infor_(LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_CAN_ENCHANT, 
					PlaceHolderHelper("+9")));
		}


		if(can_use_)
		{
			if (you.equipment[ET_WEAPON] != it)
			{
				use_text_.push_back({"(w)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP),'w'});
				if (key) key->insert('w');
			}
			else
			{
				use_text_.push_back({"(u)" + LocalzationManager::locString(LOC_SYSTEM_UNEQUIP),'u'});
				if (key) key->insert('u');
			}
			if (it->can_throw)
			{
				use_text_.push_back({"(f)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP_TANMAC),'f'});
				if (key) key->insert('f');
			}
		}
		break;
	}
	case ITM_THROW_TANMAC:
	{
		switch (it->value4)
		{
		default://없음 이거 뜨면 버그
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_TANMAC_BUG));
			break;
		case TMT_AMULET:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_TANMAC_AMULET));
			break;
		case TMT_POISON_NEEDLE:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_TANMAC_POISON_NEEDLE));
			break;
		case TMT_KIKU_COMPRESSER:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_TANMAC_COMPRESSER));
			break;
		case TMT_DOGGOJEO:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_TANMAC_DOGGOJEO));
			break;
		}


		ostringstream ss;
		ostringstream temp;

		ss << "\n\n";
		temp << LocalzationManager::locString(LOC_SYSTEM_ATTACK_VALUE) << ": " << it->value2;;
		ss << temp.str();
		if(PrintCharWidth(temp.str()) < 20)
			ss << std::string(20-PrintCharWidth(temp.str()), ' ');
		else
			ss << " ";

		temp.str("");
		temp.clear();
		temp << LocalzationManager::locString(LOC_SYSTEM_HIT_VALUE) << ": " << it->value1;
		ss << temp.str() << "\n";


		temp.str("");
		temp.clear();
		temp << LocalzationManager::locString(LOC_SYSTEM_CURRENT_TANMAC_SPEED) << ": " <<  (you.GetThrowDelay((*it).type, false) / 10.0f);
		ss << temp.str();
		if(PrintCharWidth(temp.str()) < 20)
			ss << std::string(20-PrintCharWidth(temp.str()), ' ');
		else
			ss << " ";

		temp.str("");
		temp.clear();
		temp << LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_TANMAC_INFO, PlaceHolderHelper(to_string(you.GetSkillLevel(SKT_TANMAC, true))));
		ss << temp.str();
		_infor_(ss.str());

		if (can_use_)
		{
			if (it->can_throw)
			{
				use_text_.push_back({"(f)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP_TANMAC),'f'});
				if (key) key->insert('f');
			}
		}
	}
	break;
	case ITM_ARMOR_BODY_ARMOUR_0:
	case ITM_ARMOR_BODY_ARMOUR_1:
	case ITM_ARMOR_BODY_ARMOUR_2:
	case ITM_ARMOR_BODY_ARMOUR_3:
	{
		switch (it->value5)
		{
		case AMK_NORMAL:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_NORMAL));
			break;
		case AMK_MIKO:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_MIKO));
			break;
		case AMK_WING:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_WING));
			break;
		case AMK_KAPPA:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_KAPPA));
			break;
		case AMK_FIRE:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_FIRE));
			break;
		case AMK_MAID:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_MAID));
			break;
		case AMK_POISON:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_POISON));
			break;
		case AMK_AUTUMN:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_AUTUMN));
			break;
		default:
			break;
		}
		switch (it->type)
		{
		case ITM_ARMOR_BODY_ARMOUR_0:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_MATERIAL0));
			break;
		case ITM_ARMOR_BODY_ARMOUR_1:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_MATERIAL1));
			break;
		case ITM_ARMOR_BODY_ARMOUR_2:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_MATERIAL2));
			break;
		case ITM_ARMOR_BODY_ARMOUR_3:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_MATERIAL3));
			break;
		default:
			break;
		}
		
		ostringstream ss;
		ostringstream temp;
		ss<< "\n\n";

		temp << LocalzationManager::locString(LOC_SYSTEM_DEFAULT_DEFENSE) << ": " << it->value1;;
		ss << temp.str();
		if(PrintCharWidth(temp.str()) < 20)
			ss << std::string(20-PrintCharWidth(temp.str()), ' ');
		else
			ss << " ";

		temp.str("");
		temp.clear();
		temp << LocalzationManager::locString(LOC_SYSTEM_DEFAULT_PENALTY) << ": " << it->value2;
		ss << temp.str();
		if(PrintCharWidth(temp.str()) < 20)
			ss << std::string(20-PrintCharWidth(temp.str()), ' ');
		else
			ss << " ";

		temp.str("");
		temp.clear();
		temp << LocalzationManager::locString(LOC_SYSTEM_MINIMUM_PENALTY) << ": " << it->value3;
		ss << temp.str() << "\n";



		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO1,
			PlaceHolderHelper(LOC_SYSTEM_SKILL_ARMOUR)) << "\n";		

		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO2, 
			PlaceHolderHelper(to_string((it->isiden()?it->value4:0) + (int)(it->value1*(1.0f + you.GetSkillLevel(SKT_ARMOUR, true) / 22.0f)))),
			PlaceHolderHelper(to_string(min(it->value3, it->value2 + you.GetSkillLevel(SKT_ARMOUR, true) / 3))),
			PlaceHolderHelper(LOC_SYSTEM_SKILL_ARMOUR),
			PlaceHolderHelper(to_string(you.GetSkillLevel(SKT_ARMOUR, true)))) << "\n\n";
		
		ss <<  LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO3) << "\n";	

		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO4, 
			PlaceHolderHelper(to_string(you.GetPenaltyMinus(1)))) << "\n";		

		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO5, 
			PlaceHolderHelper(to_string(you.GetPenaltyMinus(2)))) << "\n";		
			
		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO6, 
			PlaceHolderHelper(to_string(you.GetPenaltyMinus(3)))) << "\n\n";
			
		ss << "\n" << LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_CAN_ENCHANT, 
			PlaceHolderHelper("+" + to_string(it->value1)));
		_infor_(ss.str());


		if (can_use_)
		{
			if (you.equipment[ET_ARMOR] != it)
			{
				use_text_.push_back({"(w)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP),'w'});
				if (key) key->insert('w');
			}
			else
			{
				use_text_.push_back({"(u)" + LocalzationManager::locString(LOC_SYSTEM_UNEQUIP),'u'});
				if (key) key->insert('u');
			}
		}
		break;
	}
	case ITM_ARMOR_SHIELD:
	{
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SHIELD));
		
		
		ostringstream ss;
		ostringstream temp;
		ss<< "\n\n";

		temp << LocalzationManager::locString(LOC_SYSTEM_DEFAULT_SHIELD) << ": " << it->value1;;
		ss << temp.str();
		if(PrintCharWidth(temp.str()) < 20)
			ss << std::string(20-PrintCharWidth(temp.str()), ' ');
		else
			ss << " ";
		
		temp.str("");
		temp.clear();
		temp << LocalzationManager::locString(LOC_SYSTEM_DEFAULT_PENALTY) << ": " << it->value2;
		ss << temp.str();
		if(PrintCharWidth(temp.str()) < 20)
			ss << std::string(20-PrintCharWidth(temp.str()), ' ');
		else
			ss << " ";

		temp.str("");
		temp.clear();
		temp << LocalzationManager::locString(LOC_SYSTEM_MINIMUM_PENALTY) << ": " << it->value3;
		ss << temp.str() << "\n";
		
		
		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO1,
			PlaceHolderHelper(LOC_SYSTEM_SKILL_SHIELD)) << "\n";	
		
		
		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_SHIELD_INFO1, 
			PlaceHolderHelper(to_string((it->isiden() ? it->value4 : 0) + (int)(it->value1*(1.0f + (you.s_dex / 5.0f + you.GetSkillLevel(SKT_SHIELD, true)) / 15.0f)*(you.GetProperty(TPT_SLAY)?1.2f:1.0f)))),
			PlaceHolderHelper(to_string(min(it->value3, it->value2 + you.GetSkillLevel(SKT_SHIELD, true) / 3))),
			PlaceHolderHelper(LOC_SYSTEM_SKILL_SHIELD),
			PlaceHolderHelper(to_string(you.GetSkillLevel(SKT_SHIELD, true)))) << "\n\n";
		
		
		ss <<  LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO3) << "\n";	

		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO4, 
			PlaceHolderHelper(to_string(you.GetPenaltyMinus(1)))) << "\n";		

		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO5, 
			PlaceHolderHelper(to_string(you.GetPenaltyMinus(2)))) << "\n";		
			
		ss <<  LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_INFO6, 
			PlaceHolderHelper(to_string(you.GetPenaltyMinus(3)))) << "\n\n";
			
		ss << "\n" << LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_CAN_ENCHANT, 
			PlaceHolderHelper("+" + to_string(it->value1 <= 4 ? 3 : (it->value1 <= 8 ? 6 : 9))));
		_infor_(ss.str());
		

		if (can_use_)
		{
			if (you.equipment[ET_SHIELD] != it)
			{
				use_text_.push_back({"(w)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP),'w'});
				if (key) key->insert('w');
			}
			else
			{
				use_text_.push_back({"(u)" + LocalzationManager::locString(LOC_SYSTEM_UNEQUIP),'u'});
				if (key) key->insert('u');
			}
		}
		break;
	}
	case ITM_ARMOR_HEAD:
	case ITM_ARMOR_CLOAK:
	case ITM_ARMOR_GLOVE:
	case ITM_ARMOR_BOOT:
	{
		switch (it->type)
		{
		case ITM_ARMOR_HEAD:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_HEAD));
			if (can_use_)
			{
				if (you.equipment[ET_HELMET] != it)
				{
					use_text_.push_back({"(w)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP),'w'});
					if (key) key->insert('w');
				}
				else
				{
					use_text_.push_back({"(u)" + LocalzationManager::locString(LOC_SYSTEM_UNEQUIP),'u'});
					if (key) key->insert('u');
				}
			}
			break;
		case ITM_ARMOR_CLOAK:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_CLOAK));
			if (can_use_)
			{
				if (you.equipment[ET_CLOAK] != it)
				{
					use_text_.push_back({"(w)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP),'w'});
					if (key) key->insert('w');
				}
				else
				{
					use_text_.push_back({"(u)" + LocalzationManager::locString(LOC_SYSTEM_UNEQUIP),'u'});
					if (key) key->insert('u');
				}
			}
			break;
		case ITM_ARMOR_GLOVE:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_GLOVE));
			if (can_use_)
			{
				if (you.equipment[ET_GLOVE] != it)
				{
					use_text_.push_back({"(w)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP),'w'});
					if (key) key->insert('w');
				}
				else
				{
					use_text_.push_back({"(u)" + LocalzationManager::locString(LOC_SYSTEM_UNEQUIP),'u'});
					if (key) key->insert('u');
				}
			}
			break;
		case ITM_ARMOR_BOOT:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ARMOUR_GLOVE));
			if (can_use_)
			{
				if (you.equipment[ET_BOOTS] != it)
				{
					use_text_.push_back({"(w)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP),'w'});
					if (key) key->insert('w');
				}
				else
				{
					use_text_.push_back({"(u)" + LocalzationManager::locString(LOC_SYSTEM_UNEQUIP),'u'});
					if (key) key->insert('u');
				}
			}
			break;
		default:
			break;
		}
		
		ostringstream ss;
		ss << "\n\n" << LocalzationManager::locString(LOC_SYSTEM_DEFAULT_DEFENSE) << ": " << it->value1;
		ss << "\n\n" << LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_CAN_ENCHANT, 
			PlaceHolderHelper("+2"));
			
		_infor_(ss.str());
	}
	break;
	case ITM_POTION:
	{
		if (iden_list.potion_list[it->value1].iden)
		{
			switch (it->value1)
			{
			case PT_WATER:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_WATER));
				break;
			case PT_HEAL:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_HEAL));
				break;
			case PT_POISON:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_POISON));
				break;
			case PT_HEAL_WOUND:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_HEAL_WOUND));
				break;
			case PT_MIGHT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_MIGHT));
				break;
			case PT_HASTE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_HASTE));
				break;
			case PT_CONFUSE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_CONFUSE));
				break;
			case PT_SLOW:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_SLOW));
				break;
			case PT_PARALYSIS:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_PARALYSIS));
				break;
			case PT_CLEVER:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_CLEVER));
				break;
			case PT_AGILITY:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_AGILITY));
				break;
			case PT_MAGIC:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_MAGIC));
				break;
			case PT_LEVETATION:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_LEVETATION));
				break;
			case PT_POWER:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_POWER));
				break;
			case PT_DOWN_STAT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_DOWN_STAT));
				break;
			case PT_RECOVER_STAT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_RECOVER_STAT));
				break;
			case PT_ALCOHOL:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_ALCOHOL));
				break;
			default:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_BUG));
				break;
			}
		}
		else
		{
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_POTION_UNKNOWN));
		}
		if (can_use_)
		{
			use_text_.push_back({"(q)" + LocalzationManager::locString(LOC_SYSTEM_DRINK),'q'});
			if (key) key->insert('q');
		}
	}
	break;
	case ITM_FOOD:
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_FOOD));
		if (can_use_)
		{
			use_text_.push_back({"(e)" + LocalzationManager::locString(LOC_SYSTEM_EAT),'e'});
			if (key) key->insert('e');
		}
		break;
	case ITM_SCROLL:
	{
		if (iden_list.scroll_list[it->value1].iden == 3)
		{
			switch (it->value1)
			{
			case SCT_TELEPORT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_TELEPORT));
				break;
			case SCT_IDENTIFY:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_IDENTIFY));
				break;
			case SCT_NONE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_NONE));
				break;
			case SCT_CURSE_WEAPON:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_CURSE_WEAPON));
				break;
			case SCT_CURSE_ARMOUR:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_CURSE_ARMOUR));
				break;
			case SCT_REMOVE_CURSE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_REMOVE_CURSE));
				break;
			case SCT_BLINK:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_BLINK));
				break;
			case SCT_MAPPING:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_MAPPING));
				break;
			case SCT_ENCHANT_WEAPON_1:
			case SCT_ENCHANT_WEAPON_2:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_ENCHANT_WEAPON_));
				break;
			case SCT_ENCHANT_ARMOUR:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_ENCHANT_ARMOUR));
				break;
			case SCT_FOG:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_FOG));
				break;
			case SCT_DETECT_CURSE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_DETECT_CURSE));
				break;
			case SCT_CURSE_JEWELRY:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_CURSE_JEWELRY));
				break;
			case SCT_SILENCE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_SILENCE));
				break;
			case SCT_SOUL_SHOT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_SOUL_SHOT));
				break;
			case SCT_CHARGING:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_CHARGING));
				break;
			case SCT_AMNESIA:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_AMNESIA));
				break;
			case SCT_SANTUARY:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_SANTUARY));
				break;
			case SCT_BRAND_WEAPON:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_BRAND_WEAPON));
				break;
			default:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_BUG));
				break;
			}
		}
		else
		{
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL_UNKNOWN));
		}
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SCROLL));
		if (can_use_)
		{
			use_text_.push_back({"(r)" + LocalzationManager::locString(LOC_SYSTEM_READ),'r'});
			if (key) key->insert('r');
		}
	}
	break;
	case ITM_SPELL:
	{
		if (iden_list.spellcard_list[it->value2].iden == 2)
		{
			switch (it->value2)
			{
			case SPC_V_FIRE:
				_infor_( LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SPELLCARD_FIRE));
				break;
			case SPC_V_ICE:
				_infor_( LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SPELLCARD_ICE));
				break;
			case SPC_V_EARTH:
				_infor_( LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SPELLCARD_EARTH));
				break;
			case SPC_V_AIR:
				_infor_( LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SPELLCARD_AIR));
				break;
			case SPC_V_INVISIBLE:
				_infor_( LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SPELLCARD_INVISIBLE));
				break;
			case SPC_V_METAL:
				_infor_( LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SPELLCARD_METAL));
				break;
			case SPC_V_SUN:
				_infor_( LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SPELLCARD_SUN));
				break;
			default:
				_infor_( LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SPELLCARD_BUG));
				break;
			}
			_infor_("\n");
		}
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_SPELLCARD));
		if (can_use_)
		{
			use_text_.push_back({"(v)" + LocalzationManager::locString(LOC_SYSTEM_EVOKE),'v'});
			if (key) key->insert('v');
		}
	}
	break;
	case ITM_AMULET:
	{
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET));
		if ((it->isArtifact() && it->identify) || iden_list.amulet_list[it->value1].iden == 2)
		{
			switch (it->value1)
			{
			case AMT_PERFECT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_PERFECT));
				break;
			case AMT_BLOSSOM:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_BLOSSOM));
				break;
			case AMT_TIMES:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_TIMES));
				break;
			case AMT_FAITH:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_FAITH));
				break;
			case AMT_WAVE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_WAVE));
				break;
			case AMT_SPIRIT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_SPIRIT));
				break;
			case AMT_GRAZE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_GRAZE));
				break;
			case AMT_WEATHER:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_WEATHER));
				break;
			case AMT_OCCULT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_OCCULT));
				break;
			default:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_BUG));
				break;
			}
		}
		else
		{
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_AMULET_UKNOWN));
		}		

		if (can_use_)
		{
			if (you.equipment[ET_NECK] != it)
			{
				use_text_.push_back({"(w)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP),'w'});
				if (key) key->insert('w');
			}
			else
			{
				use_text_.push_back({"(u)" + LocalzationManager::locString(LOC_SYSTEM_UNEQUIP),'u'});
				if (key) key->insert('u');
			}
		}
	}
	break;
	case ITM_RING:
	{
		if ((it->isArtifact() && it->identify) || iden_list.ring_list[it->value1].iden == 2)
		{
			switch (it->value1)
			{
			case RGT_STR:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_STR));
				break;
			case RGT_DEX:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_DEX));
				break;
			case RGT_INT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_INT));
				break;
			case RGT_HUNGRY:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_HUNGRY));
				break;
			case RGT_FULL:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_FULL));
				break;
			case RGT_TELEPORT:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_TELEPORT));
				break;
			case RGT_POISON_RESIS:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_POISON_RESIS));
				break;
			case RGT_FIRE_RESIS:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_FIRE_RESIS));
				break;
			case RGT_ICE_RESIS:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_ICE_RESIS));
				break;
			case RGT_SEE_INVISIBLE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_SEE_INVISIBLE));
				break;
			case RGT_LEVITATION:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_LEVITATION));
				break;
			case RGT_INVISIBLE:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_INVISIBLE));
				break;
			case RGT_MANA:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_MANA));
				break;
			case RGT_MAGACIAN:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_MAGACIAN));
				break;
			case RGT_AC:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_AC));
				break;
			case RGT_EV:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_EV));
				break;
			case RGT_CONFUSE_RESIS:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_CONFUSE_RESIS));
				break;
			case RGT_ELEC_RESIS:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_ELEC_RESIS));
				break;
			case RGT_MAGIC_RESIS:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_MAGIC_RESIS));
				break;
			default:
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_BUG));
				break;
			}
		}
		else
		{
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RING_UNKNOWN));
		}
		if (can_use_)
		{
			if (you.equipment[ET_RIGHT] != it && you.equipment[ET_LEFT] != it)
			{
				use_text_.push_back({"(w)" + LocalzationManager::locString(LOC_SYSTEM_EQUIP),'w'});
				if (key) key->insert('w');
			}
			else
			{
				use_text_.push_back({"(u)" + LocalzationManager::locString(LOC_SYSTEM_UNEQUIP),'u'});
				if (key) key->insert('u');
			}
		}
	}
	break;
	case ITM_BOOK:
	{

		_infor_(GetBookInfor((book_list)it->value0));
		_infor_("\n\n");
		if (it->identify)
		{
			
			//스킬레벨 설명해주기
			ostringstream ss;
			ostringstream temp;
			
			if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SPELL_NAME)) < 34)
				ss << std::string(34-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SPELL_NAME)), ' ');
			ss << LocalzationManager::locString(LOC_SYSTEM_SPELL_NAME);
			
			if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SCHOOL)) < 30)
				ss << std::string(30-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SCHOOL)), ' ');
			ss << LocalzationManager::locString(LOC_SYSTEM_SCHOOL);
			
			if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_LEVEL)) < 6)
				ss << std::string(6-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_LEVEL)), ' ');
			ss << LocalzationManager::locString(LOC_SYSTEM_LEVEL);
			
			ss << "\n";			
			
			_infor_(ss.str());

			char sp_char = 'a';
			for (int i = 0; i < 8; i++)
			{
				spell_list spell_;
				if ((spell_ = (spell_list)it->GetValue(i + 1)) != SPL_NONE)
				{
					ostringstream ss;
					ss << (sp_char) << " - ";
					
					if(PrintCharWidth(SpellString(spell_)) < 30)
						ss << std::string(30-PrintCharWidth(SpellString(spell_)), ' ');
					ss << SpellString(spell_);
					
					if(PrintCharWidth(GetSpellSchoolString(spell_)) < 30)
						ss << std::string(30-PrintCharWidth(GetSpellSchoolString(spell_)), ' ');
					ss << GetSpellSchoolString(spell_);					
					
					if(PrintCharWidth(to_string(SpellLevel(spell_))) < 6)
						ss << std::string(6-PrintCharWidth(to_string(SpellLevel(spell_))), ' ');
					ss << to_string(SpellLevel(spell_));

					printsub(ss.str(), false, CL_normal, sp_char);
					sp_char++;
					printsub("", true, CL_normal, sp_char);
					printsub(blank, false, CL_normal, sp_char);
				}
			}
		}
	}
	break;
	case ITM_MISCELLANEOUS:
	{
		switch (it->value1)
		{
		case EVK_PAGODA:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_PAGODA));
			break;
		case EVK_AIR_SCROLL:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_AIR_SCROLL));
			break;
		case EVK_DREAM_SOUL:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_DREAM_SOUL));
			break;
		case EVK_BOMB:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_BOMB));
			break;
		case EVK_GHOST_BALL:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_GHOST_BALL));
			break;
		case EVK_SKY_TORPEDO:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_SKY_TORPEDO));
			break;
		case EVK_MAGIC_HAMMER:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_MAGIC_HAMMER));
			break;
		case EVK_CAMERA:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_CAMERA));
			break;
		default:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_BUG));
			break;
		}
		_infor_("\n\n");
		if (it->value1 == EVK_CAMERA) {
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_INFO1));
		}
		else {
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_INFO2));
		}
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_INFO3));
		char temp[100];
		sprintf_s(temp,100, ": %d.%02d\n", Evokeusepower((evoke_kind)it->value1, true) / 100, Evokeusepower((evoke_kind)it->value1, true) % 100);
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_EVOKE_INFO4));
		_infor_(temp);		

		if (can_use_)
		{
			use_text_.push_back({"(v)" + LocalzationManager::locString(LOC_SYSTEM_EVOKE),'v'});
			if (key) key->insert('v');
		}
	}
	break;

	case ITM_GOAL:
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_RUNE));
		break;
	case ITM_ORB:
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_YINYANG_ORB));
		break;
	case ITM_ETC:
		switch (it->value1)
		{
		case EIT_SATORI:
			if (you.god_value[GT_SATORI][0] == 1)
			{
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ETC_SATORI_NOTE1));
			}
			else
			{
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ETC_SATORI_NOTE2));
			}
			break;
		case EIT_CAT_TREE:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ETC_CATNIP));
			break;
		case EIT_BROKEN_CAMERA:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ETC_BROKEN_CAMERA));
			break;
		case EIT_KAPPA_TRASH:
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_ETC_KAPPA_TRASH));
			break;
		case EIT_PHOTO:
		{
			if (it->value2 >= 0 && it->value2 < MON_MAX) {
				_infor_(LocalzationManager::formatString(LOC_SYSTEM_ITEM_DESCRIPTION_PHOTO1, PlaceHolderHelper( mondata[it->value2].name.getName())));
			}
			else {
				_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_PHOTO2));
			}
			_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_PHOTO3));
			break;
		}
		}
		break;
	default:
		_infor_(LocalzationManager::locString(LOC_SYSTEM_ITEM_DESCRIPTION_BUG));
		break;
	}

	if (can_use_)
	{
		if (it->type == ITM_BOOK)
		{
			use_text_.push_back({"(D)" + LocalzationManager::locString(LOC_SYSTEM_DISCARD),'D'});
			if (key) key->insert('D');
		}
		else
		{
			use_text_.push_back({"(d)" + LocalzationManager::locString(LOC_SYSTEM_DISCARD),'d'});
			if (key) key->insert('d');
		}
	}



	if(it->isArtifact() && it->identify)
	{
		_infor_("\n\n");
		for(auto it2 = it->atifact_vector.begin(); it2 != it->atifact_vector.end(); it2++)
		{
			_infor_(GetAtifactInfor((ring_type)it2->kind, it2->value));
			_infor_("\n");
		}
	}


	_infor_("\n\n\n");
	bool first_ = true;
	for(auto& use_text : use_text_) {
		if(!first_) { 
			printsub(", ", false, CL_normal);
		}
		printsub(use_text.first, false, CL_help, use_text.second);
		first_ = false;
	}
	return;

}