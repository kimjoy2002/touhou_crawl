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
#include <set>

extern HANDLE mutx;
extern int shieldPanaltyOfWeapon(item_type type, int weapon_kind);
void discard(list<item>::iterator it, int number);


string GetItemInfor(item *it, bool can_use_, set<char> *key);

void memorize_action(int spell_)
{
	changedisplay(DT_GAME);
	if(spell_ == SPL_NONE)
		printlog("존재하지 않는 스펠입니다.",true,false,false,CL_normal);
	else
	{		
		bool ok_ = true;
		while(ok_)
		{
			printlog(SpellString((spell_list)spell_),false,false,false,CL_normal);
			printlog(" 주문을 익히시겠습니까? (y/n)",false,false,false,CL_help);
			char temp[128];
			sprintf_s(temp,128," [마법실패율: %d%% 남은 마법 레벨: %d]",100-you.GetSpellSuccess(spell_),you.remainSpellPoiont);

			printlog(temp,true,false,false,CL_warning);
			switch(waitkeyinput())
			{
			case 'Y':
			case 'y':
				you.Memorize(spell_);
				ok_ = false;
				break;
			case 'N':
			case 'n':
			case VK_ESCAPE:
				printlog("취소했다.",true,false,false,CL_help);
				ok_ = false;
				break;
			default:
				printlog("Y와 N중에 선택해주세요.",true,false,false,CL_help);
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


void iteminfor(bool gameover)
{
	view_item(IVT_INFOR,gameover?"당신의 아이템":"무슨 아이템을 확인하겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			item *item_ = you.GetItem(key_);
			if(item_)
			{
				while(1)
				{
					set<char> ket_list;
					WaitForSingleObject(mutx, INFINITE);
					SetText() = GetItemInfor(item_, !gameover, &ket_list);
					ReleaseMutex(mutx);
					changedisplay(DT_TEXT);
					int key_ = waitkeyinput(true);
					if(item_->type == ITM_BOOK && (key_ >= 'a' && key_ <= 'f'))
					{
						if(int spell_ = item_->GetValue(key_ - 'a'+1))
						{	
							WaitForSingleObject(mutx, INFINITE);
							SetText() = GetSpellInfor((spell_list)spell_);
							SetText() += "\n\n";
							SetText() += "m을 누르면 마법을 기억할 수 있습니다.\n";
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
					else if (!ket_list.empty())
					{

						if (ket_list.count(key_) >= 1)
						{
							switch (key_)
							{
							case '=': //단축키 바꾸기
							{
								changedisplay(DT_GAME);
								printlog("무슨 알파벳으로 바꿀거지? (a-z, A-Z)", true, false, false, CL_help);
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

										char temp[100];
										if (old_ != you.item_list.end())
										{
											old_->id = item_->id;
											new_->id = alphabet_;
											swap_list_items(you.item_list, old_, new_);

											sprintf_s(temp, 100, "%c", old_->id);
											printlog(temp, false, false, false, old_->item_color());
											printlog(" - ", false, false, false, old_->item_color());
											printlog(old_->GetName(), false, false, false, old_->item_color());
											printlog(", ", false, false, false, old_->item_color());
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
										sprintf_s(temp, 100, "%c", new_->id);
										printlog(temp, false, false, false, new_->item_color());
										printlog(" - ", false, false, false, new_->item_color());
										printlog(new_->GetName(), false, false, false, new_->item_color());
										printlog(" ", false, false, false, new_->item_color());
									}
								}
								return;
							}
							case 'w': //장착	
								changedisplay(DT_GAME);
								if (you.s_lunatic)
								{
									printlog("광기에 휩싸인 상태로 할 수 없다!", true, false, false, CL_danger);
									return;
								}
								if (you.s_evoke_ghost) {
									printlog("유령 상태에선 할 수 없다. ", true, false, false, CL_normal);
									return;
								}

								if (item_->type >= ITM_WEAPON_FIRST &&item_->type < ITM_WEAPON_LAST)
								{
									if (you.drowned)
									{
										printlog("물에 빠진 상태에선 할 수 없다!", true, false, false, CL_danger);
										return;
									}
									you.equip(item_->id, ET_WEAPON);
								}
								else if (item_->type >= ITM_ARMOR_BODY_FIRST &&item_->type < ITM_ARMOR_LAST)
								{
									if (you.drowned)
									{
										printlog("물에 빠진 상태에선 할 수 없다!", true, false, false, CL_danger);
										return;
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
								return;
							case 'u': //벗기
								changedisplay(DT_GAME);
								if (you.s_lunatic)
								{
									printlog("광기에 휩싸인 상태로 할 수 없다!", true, false, false, CL_danger);
									return;
								}
								if (you.s_evoke_ghost) {
									printlog("유령 상태에선 할 수 없다. ", true, false, false, CL_normal);
									return;
								}
								if (item_->type >= ITM_WEAPON_FIRST &&item_->type < ITM_WEAPON_LAST)
								{
									if (you.drowned)
									{
										printlog("물에 빠진 상태에선 할 수 없다!", true, false, false, CL_danger);
										return;
									}
									if (!you.unequip(ET_WEAPON))
									{
										printlog("저주에 걸려 있어서 장비를 벗을 수 없다.", true, false, false, CL_normal);
									}
								}
								else if (item_->type >= ITM_ARMOR_BODY_FIRST &&item_->type < ITM_ARMOR_LAST)
								{
									if (you.drowned)
									{
										printlog("물에 빠진 상태에선 할 수 없다!", true, false, false, CL_danger);
										return;
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
								return;
							case 'f': //탄막
							{
								changedisplay(DT_GAME);
								you.throw_weapon = item_;
								char temp[100];
								sprintf_s(temp, 100, "%c", item_->id);
								printlog(temp, false, false, false, item_->item_color());
								printlog(" - ", false, false, false, item_->item_color());
								printlog(item_->GetName(), false, false, false, item_->item_color());
								printlog("(탄막) ", false, false, false, item_->item_color());
							}
								return;
							case 'q': //마시기
								changedisplay(DT_GAME);
								if (you.s_lunatic)
								{
									printlog("광기에 휩싸인 상태로 할 수 없다!", true, false, false, CL_danger);
									return;
								}
								if (you.s_evoke_ghost) {
									printlog("유령 상태에선 할 수 없다. ", true, false, false, CL_normal);
									return;
								}
								if (you.drowned)
								{
									printlog("물에 빠진 상태에선 할 수 없다!", true, false, false, CL_danger);
									return;
								}
								if (you.Drink(item_->id))
								{
									you.time_delay += you.GetNormalDelay();
									you.doingActionDump(DACT_USE, "물약");
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
								return;
							case 'e': //먹기
								changedisplay(DT_GAME);
								if (you.s_lunatic)
								{
									printlog("광기에 휩싸인 상태로 할 수 없다!", true, false, false, CL_danger);
									return;
								}
								if (you.s_evoke_ghost) {
									printlog("유령 상태에선 할 수 없다. ", true, false, false, CL_normal);
									return;
								}
								if (you.drowned)
								{
									printlog("물에 빠진 상태에선 할 수 없다!", true, false, false, CL_danger);
									return;
								}
								you.Eat(item_->id);
								return;
							case 'r': //읽기
								changedisplay(DT_GAME);
								if (you.s_lunatic)
								{
									printlog("광기에 휩싸인 상태로 할 수 없다!", true, false, false, CL_danger);
									return;
								}
								if (you.s_evoke_ghost) {
									printlog("유령 상태에선 할 수 없다. ", true, false, false, CL_normal);
									return;
								}
								if (you.drowned)
								{
									printlog("물에 빠진 상태에선 할 수 없다!", true, false, false, CL_danger);
									return;
								}
								if(you.Read(item_->id))
								{
									you.doingActionDump(DACT_USE, "두루마리");
									you.time_delay += you.GetNormalDelay();
									changedisplay(DT_GAME);
									you.TurnEnd();
								}
								return;
							case 'v': //발동
								changedisplay(DT_GAME);
								if (you.s_lunatic)
								{
									printlog("광기에 휩싸인 상태로 할 수 없다!", true, false, false, CL_danger);
									return;
								}
								if (you.s_evoke_ghost &&
									!(item_->type == ITM_MISCELLANEOUS && item_->value1 == EVK_GHOST_BALL)
									) {
									printlog("유령상태에선 할 수 없다. ", true, false, false, CL_normal);
									return;
								}
								if (you.Evoke(item_->id))
								{
									you.time_delay += you.GetNormalDelay();
									you.TurnEnd();
								}
								return;
							case 'd': //버리기
							case 'D':
								{
									changedisplay(DT_GAME);
									if (you.s_lunatic)
									{
										printlog("광기에 휩싸인 상태로 할 수 없다!", true, false, false, CL_danger);
										return;
									}
									if (you.s_evoke_ghost) {
										printlog("유령 상태에선 할 수 없다. ", true, false, false, CL_normal);
										return;
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
										printlog("존재하지 않는 템입니다.", true, false, false, CL_normal);
									}
									return;
								}
							}
						}
					}
					else
						waitkeyinput();
					break;
				}
				view_item(IVT_INFOR,gameover?"당신의 아이템":"무슨 아이템을 확인하겠습니까?");
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
		else if(key_ == VK_ESCAPE || (key_ == VK_RETURN && gameover))
			break;
	}
	changedisplay(DT_GAME);
}

string GetItemInfor(item *it, bool can_use_, set<char> *key)
{
	string use_text_;
	
	string text_ = it->GetName();
	text_ += "\n\n";

	if (can_use_)
	{
		use_text_ += "(=)단축키변경, ";
		if (key) key->insert('=');
	}
	switch (it->type)
	{
		//case ITM_WEAPON_DAGGER:
		//	text_ += "단검의 일종으로 작은 칼이다. 적을 기습하는데 특히 유용한 무기이다.\n\
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
			text_ += "날이 짧은 검이다. 빠른 속도로 공격할 수 있다.\n";
			ski_ = SKT_SHORTBLADE;
			switch (it->value0)
			{
			case 0:
				text_ += "휴대하기 좋은 작은 단검. 직접적인 전투보다 조용히 적의 목을 따버리는데 효율적이다.\n";
				break;
			case 1:
				text_ += "던지는 무기로 최적화된 단검. 근접전투로도 쓸 순 있지만 효율은 떨어진다.\n";
				text_ += "비록 던지고나선 다시 주워야하지만 이를 해결할 수 있다면 유용한 투척수단이 된다.\n";
				break;
			case 2:
				text_ += "다른 단검에 비해선 근접 전투에서도 쓸 수 있을 정도로 날이 긴 무기다.\n";
				text_ += "구지 단검으로 정면전을 하고싶은 사람이라면 쓰게될 것이다.\n";
				break;
			}
			break;
		case ITM_WEAPON_LONGBLADE:
			text_ += "날이 긴 장검이다. 찌르거나 베면서 상대를 공격한다.\n";
			ski_ = SKT_LONGBLADE;
			switch (it->value0)
			{
			case 0:
				text_ += "평범한 도검으로 마땅히 특징이랄게 없을 정도로 쓰기 편한 평범한 검.\n";
				break;
			case 1:
				text_ += "백랑텐구들이 자주 들고다니는 날이 크고 구부러져있는 장검.\n";
				text_ += "날이 훨씬 크기 때문에 보통의 장검보다 더 큰 데미지를 준다.\n";
				break;
			case 2:
				text_ += "아주 거대한 양날이 달린 검. 양손으로도 제대로 들기가 힘들다.\n";
				text_ += "그 크기에 걸맞는 파괴력을 보여주지만 제대로 다루기엔 수련이 필요하다.\n";
				break;
			case 3:
				text_ += "어딘가의 토착신이 자주 사용하는 둥그렇게 날이 달린 투척용 무기.\n";
				text_ += "손으로 빙빙돌려서 던지면 그 회전력으로 다시 자신에게 돌아올 수 도 있다.\n";
				text_ += "이걸 검이라고 볼 수 있을진 모르겠지만 손에 들고 검처럼도 사용할 수 있다.\n";
				break;
			}
			break;
		case ITM_WEAPON_MACE:
			text_ += "뭉툭한 둔기다.\n";
			switch (it->value0)
			{
			case 0:
				text_ += "신사의 무녀들이 제사를 할때 사용하는 제사용구... 였으나\n";
				text_ += "오히려 이 환상향의 무녀들은 물리적인 공격도구로 사용하는 일이 많다.\n";
				text_ += "그렇게 효율적인 무기는 아닐지도 모르지만 시도해볼 가치는 있다.\n";
				break;
			case 1:
				text_ += "마법사들이 흔히 쓰고 다니는 빗자루. 마법력을 올려주거나 그런 용도는 없다.\n";
				text_ += "굳이 빗자루를 고집할 이유는 없지만 마법사는 빗자루라는 특유의 고집인듯 하다.\n";
				text_ += "둔기로서 사용하는게 그나마 활용해볼 수 있다.\n";
				break;
			case 2:
				text_ += "멋쟁이들이 사용한다는 양산. 강한 요괴일수록 양산을 사용하려는 풍조가 있는듯하다.\n";
				text_ += "그렇게 효과적이진않을지 몰라도 강한척을 하고 싶은 사람들이라면 사용해보는게 어떨까?\n";
				break;
			case 3:
				text_ += "보물을 찾는데 도움을 준다고 믿어지는 봉. 그러나 이런 속설은 미신인듯 싶다.\n";
				text_ += "보물을 찾는데 도움은 되지않지만 다루기 쉬운 금속 봉으로 전투에서 쓸 수 있다.\n";
				text_ += "양손으로 다루는데 특화되어있어서, 방패와 함께라면 효율이 떨어진다.\n";
				break;
			case 4:
				text_ += "아주 거대한 기둥으로 이런 것을 무기로 쓰려 생각했다는게 신기할 정도다.\n";
				text_ += "보통 익숙하지만 휘두르는데만 엄청난 시간이 걸릴듯 하다.\n";
				text_ += "맞추기도 쉽지않아보이지만 맞춘다면 엄청난 데미지를 줄 수 있다.\n";
				break;
			}
			ski_ = SKT_MACE;
			break;
		case ITM_WEAPON_SPEAR:
			text_ += "길다란 창이다. 적을 찔러서 공격할 수 있다.\n";
			ski_ = SKT_SPEAR;
			switch (it->value0)
			{
			case 0:
				text_ += "딱히 큰 특징이 없는 평범한 창. 찌르는데 쓸 수 있다.\n";
				break;
			case 1:
				text_ += "던지는데 특화되어있는 거대한 창. 힘껏 던져서 적에게 맞출 수 있다.\n";
				text_ += "근접전투에서도 충분히 사용이 가능하지만 휘두르기엔 적합하지않다.\n";
				break;
			case 2:
				text_ += "사신이 자주 들고다닌다는 거대한 낫.\n";
				text_ += "생각보다 무기로서 사용하기엔 어려워보이는 큰 낫이지만 익숙해지면 나름 강하다.\n";
				break;
			case 3:
				text_ += "날이 3개달린 기다란 작살으로 찍는데 특화된 창이다.\n";
				text_ += "가볍고 쓰기 좋지만 높은 위력은 나오지않는다.\n";
				break;
			case 4:
				text_ += "대나무로 깎아서 만든 창. \n";
				text_ += "아주 평범한 창처럼 보이지만 놀랄만한 위력을 숨기고 있다.\n";
				text_ += "제대로 다루려면 상당한 연습이 필요하다.\n";
				break;
			}
			break;
		case ITM_WEAPON_AXE:
			text_ += "적을 찍을 수 있는 도끼. 거대한 날을 지녔다.\n";
			ski_ = SKT_AXE;
			switch (it->value0)
			{
			case 0:
				text_ += "한손으로 들 수 있는 작은 손도끼다. 큰 위력은 나오지않지만 다루기 쉽다.\n";
				break;
			case 1:
				text_ += "길다란 자루에 큰 도끼날이 달린 거대한 도끼다.\n";
				break;
			case 2:
				text_ += "어딘가의 배유령이 자주 들고다니는 거대한 낯이다.\n";
				text_ += "아주 강력하지만 이런걸 휘두를려면 어마어마한 실력이 필요하다.\n";
				break;
			}
			break;
		}

		if (it->value5 && it->value6)
		{
			text_ += "\n\n";
			text_ += GetBrandInfor((weapon_brand)it->value5);
			text_ += "\n";
		}
		
		{
			//스킬레벨 설명해주기
			char temp[100];
			sprintf_s(temp, 100, "\n\n이 무기는 %s 스킬에 비례하여 강해진다. (현재 %s 스킬 레벨 : %d)", skill_string(ski_), skill_string(ski_), you.GetSkillLevel(ski_, true));
			text_ += temp;

			sprintf_s(temp,100, "\n공격력 : %d       명중력 : %d", it->value2, it->value1);
			text_ += temp;
			sprintf_s(temp,100, "\n현재공격속도 : %g    ( 기본공격속도 : %g       최소공격속도 : %g )", max((it->value8)/100, (it->value7 - you.GetSkillLevel(ski_, true) / 2.0f)) / 10.0f, it->value7 / 10.0f, it->value8/10.0f);
			text_ += temp;
			if (shieldPanaltyOfWeapon(it->type, it->value0)) {
				sprintf_s(temp,100, "\n단, 이 무기는 방패를 들게되면 공격속도가 %g만큼 추가적으로 느려진다.", shieldPanaltyOfWeapon(it->type, it->value0) / 10.0f);
				text_ += temp;
			}
		}


		if (it->can_throw)
		{
			char temp[100];
			sprintf_s(temp,100, "\n\n이 아이템은 근접 무기로도 사용가능하지만 던져서 탄막으로도 사용할 수 있다.");
			text_ += temp;
			sprintf_s(temp,100, "\n이 경우 현재 투척속도는 %g이다. (현재 탄막 스킬 레벨 : %d)", you.GetThrowDelay((*it).type, false) / 10.0f, you.GetSkillLevel(SKT_TANMAC, true));
			text_ += temp;
		}

		{
			char temp[100];
			sprintf_s(temp,100, "\n\n이 아이템은 +9까지 인챈트가 가능하다.");
			text_ += temp;
		}


		if(can_use_)
		{
			if (you.equipment[ET_WEAPON] != it)
			{
				use_text_ += "(w)장착, ";
				if (key) key->insert('w');
			}
			else
			{
				use_text_ += "(u)해제, ";
				if (key) key->insert('u');
			}
			if (it->can_throw)
			{
				use_text_ += "(f)탄막, ";
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
			text_ += "탄막 놀이의 기본이 되는 탄막이다. 적에게 던져서 맞춘다.\n";
			text_ += "문제는 이게 버그 탄막이라는 것이다.\n";
			break;
		case TMT_AMULET:
			text_ += "레이무가 쓰는 이 치사한 아뮬렛에는 고성능의 호밍성능이 붙어있다.\n";
			text_ += "특별한 특징이 없는 탄막이지만 높은 명중율이 자랑이다.\n";
			break;
		case TMT_POISON_NEEDLE:
			text_ += "이것은 던지면서 상대에게 박히는 수리검이다.\n";
			text_ += "데미지는 낮지만 이 수리검에는 특별히 독이 발라져있는것 같다.\n";
			break;
		case TMT_KIKU_COMPRESSER:
			text_ += "캇파들의 발명품중 하나다. 물을 가득 압축하고있는 폭탄이다.\n";
			text_ += "상대에게 던지면 압축되어있던 물이 한번에 터진다.\n";
			text_ += "넓은 범위 공격할 수 있을 것 같다.\n";
			break;
		case TMT_DOGGOJEO:
			text_ += "불교의 승려들이 수행할때 사용했다고 하는 고대 인도의 무기.\n";
			text_ += "평소엔 평범한 손잡이처럼 생겼지만 강한 힘으로 던지면 마력이 방출된다.\n";
			text_ += "다른 탄막과 다르게 적들을 관통하여 공격이 가능하다.\n";
			break;
		}
		char temp[100];
		sprintf_s(temp,100, "\n공격력 : %d       명중력 : %d", it->value2, it->value1);
		text_ += temp;
		sprintf_s(temp,100, "\n현재 투척속도 : %g (현재 탄막 스킬 레벨 : %d)", you.GetThrowDelay((*it).type, false) / 10.0f, you.GetSkillLevel(SKT_TANMAC, true));
		text_ += temp;

		if (can_use_)
		{
			if (it->can_throw)
			{
				use_text_ += "(f)탄막, ";
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
			text_ += "평상시에 입는 편한 옷.\n";
			text_ += "천이 아닌 재질의 갑옷 기본패널티가 상당히 내려간다. \n";
			text_ += "그러나 최소패널티는 다른 옷과 동일하므로 갑옷에 익숙해지면 이점이 없어진다.\n\n";
			break;
		case AMK_MIKO:
			text_ += "무녀들이 입는 옷.\n";
			text_ += "신의 가호를 받아서 정신을 보호해준다. 입고있는 동안 혼란저항이 생긴다.\n\n";
			break;
		case AMK_WING:
			text_ += "용궁의 사자들이 입는다는 날개옷.\n";
			text_ += "전기를 흘려보내는 특징을 가지고 있다. 입고있는 동안 전기저항이 생긴다.\n\n";
			break;
		case AMK_KAPPA:
			text_ += "캇파들이 유니폼처럼 입고 있는 파란색 옷이다.\n";
			text_ += "강의 추위에도 견딜 수 있게 디자인 되어있다. 입고있는 동안 냉기저항이 생긴다.\n\n";
			break;
		case AMK_FIRE:
			text_ += "불쥐의 기운이 서려있는 옷이다.\n";
			text_ += "뜨거운 열에도 견딜 수 있을 것 같다. 입고있는 동안 화염저항이 생긴다.\n\n";
			break;
		case AMK_MAID:
			text_ += "홍마관의 메이드들이 입는 옷.\n";
			text_ += "홍마관 도서관표 특수한 마법적 처리가 되어있다. 입고있는 동안 마법저항이 올라간다.\n\n";
			break;
		case AMK_POISON:
			text_ += "은방울 꽃밭의 인형이 입고 있던 옷이지만 꽤 사이즈가 커서 입을 수 있을 것 같다.\n";
			text_ += "은방울 꽃의 기운이 당신을 보호해준다. 입고있는 동안 독저항이 생긴다.\n\n";
			break;
		case AMK_AUTUMN:
			text_ += "단풍으로 만들어진 옷. 의외로 제대로된 옷이다.\n";
			text_ += "시즈하를 믿고있을때 주변의 풍경에 동화되어서 은밀이 급격하게 올라간다.\n\n";
			break;
		}
		switch (it->type)
		{
		case ITM_ARMOR_BODY_ARMOUR_0:
			text_ += "움직이기 편하게 천으로 되어있는 옷.\n";
			text_ += "잦은 그레이즈에도 끄덕없는 질긴 옷감으로 되어있다!\n";
			break;
		case ITM_ARMOR_BODY_ARMOUR_1:
			text_ += "질긴 재질로 되어있는 옷.\n";
			text_ += "천보단 움직이기 불편하지만 꽤 가볍다.\n";
			break;
		case ITM_ARMOR_BODY_ARMOUR_2:
			text_ += "사슬로 얽혀있는 갑옷.\n";
			text_ += "꽤 단단하지만 판금으로된 갑옷보다는 못하다.\n";
			break;
		case ITM_ARMOR_BODY_ARMOUR_3:
			text_ += "강철로 된 판금을 덧댄 갑옷.\n";
			text_ += "마법과 움직임을 방해하지만 당신의 안전을 책임진다.\n";
			break;
		}
		char temp[100];
		sprintf_s(temp,100, "\n\n기본 방어력 : %d   기본 패널티 : %d   최소 패널티 : %d\n", it->value1, it->value2, it->value3);
		text_ += temp;
		sprintf_s(temp,100, "패널티는 갑옷 스킬을 올릴수록 줄어듭니다. 최소 패널티이하로는 줄일수 없습니다.\n");
		text_ += temp;
		sprintf_s(temp,100, "현재 착용시 방어력: %d     패널티 : %d (현재 갑옷 스킬 레벨 : %d)\n\n", 
			(it->isiden()?it->value4:0) + (int)(it->value1*(1.0f + you.GetSkillLevel(SKT_ARMOUR, true) / 15.0f)),
			min(it->value3, it->value2 + you.GetSkillLevel(SKT_ARMOUR, true) / 3), you.GetSkillLevel(SKT_ARMOUR, true));
		text_ += temp;
		sprintf_s(temp,100, "합계 패널티만큼 회피와 은밀, 마법성공율이 감소합니다.\n");
		text_ += temp;
		sprintf_s(temp,100, "합계 패널티가 %d보다 높으면 패널티만큼 추가적으로 명중율이 감소합니다.\n", you.GetPenaltyMinus(1));
		text_ += temp;
		sprintf_s(temp,100, "합계 패널티가 %d보다 높으면 패널티만큼 이동속도가 감소합니다.\n", you.GetPenaltyMinus(2));
		text_ += temp;
		sprintf_s(temp,100, "합계 패널티가 %d보다 높으면 모든 행동이 2배 딜레이됩니다.\n\n", you.GetPenaltyMinus(3));
		text_ += temp;
		sprintf_s(temp,100, "\n이 아이템은 +%d까지 인챈트가 가능하다.", it->value1);
		text_ += temp;


		if (can_use_)
		{
			if (you.equipment[ET_ARMOR] != it)
			{
				use_text_ += "(w)장착, ";
				if (key) key->insert('w');
			}
			else
			{
				use_text_ += "(u)해제, ";
				if (key) key->insert('u');
			}
		}
		break;
	}
	case ITM_ARMOR_SHIELD:
	{
		text_ += "상대의 공격을 막기 위한 방패. 양손무기를 들고 있으면 장착이 불가능하다.\n";
		text_ += "상대의 탄막을 막는 반칙적인 활용도 가능하다.\n";
		char temp[100];
		sprintf_s(temp,100, "\n\n기본 방어력 : %d   기본 패널티 : %d   최소 패널티 : %d\n", it->value1, it->value2, it->value3);
		text_ += temp;
		sprintf_s(temp,100, "패널티는 방패 스킬을 올릴수록 줄어듭니다. 최소 패널티이하로는 줄일수 없습니다.\n"); 
		text_ += temp;
		sprintf_s(temp,100, "현재 착용시 방어력: %d    패널티 : %d (현재 방패 스킬 레벨 : %d)\n\n",
			(it->isiden() ? it->value4 : 0) + (int)(it->value1*(1.0f + (you.s_dex / 5.0f + you.GetSkillLevel(SKT_SHIELD, true)) / 15.0f)*(you.GetProperty(TPT_SLAY)?1.2f:1.0f)),
			min(it->value3, it->value2 + you.GetSkillLevel(SKT_SHIELD, true) / 3), you.GetSkillLevel(SKT_SHIELD, true));
		text_ += temp;
		sprintf_s(temp,100, "합계 패널티만큼 회피와 은밀, 마법성공율, 은밀이 감소합니다.\n");
		text_ += temp;
		sprintf_s(temp,100, "합계 패널티가 %d보다 높으면 패널티만큼 추가적으로 명중율이 감소합니다.\n", you.GetPenaltyMinus(1));
		text_ += temp;
		sprintf_s(temp,100, "합계 패널티가 %d보다 높으면 패널티만큼 이동속도가 감소합니다.\n", you.GetPenaltyMinus(2));
		text_ += temp;
		sprintf_s(temp,100, "합계 패널티가 %d보다 높으면 모든 행동이 2배 딜레이됩니다.\n\n", you.GetPenaltyMinus(3));
		text_ += temp;
		sprintf_s(temp,100, "이 아이템은 +%d까지 인챈트가 가능하다.", it->value1 <= 4 ? 3 : (it->value1 <= 8 ? 6 : 9));
		text_ += temp;

		if (can_use_)
		{
			if (you.equipment[ET_SHIELD] != it)
			{
				use_text_ += "(w)장착, ";
				if (key) key->insert('w');
			}
			else
			{
				use_text_ += "(u)해제, ";
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
			text_ += "머리에 달 수 있는 장신구. 패션의 기본\n";
			if (can_use_)
			{
				if (you.equipment[ET_HELMET] != it)
				{
					use_text_ += "(w)장착, ";
					if (key) key->insert('w');
				}
				else
				{
					use_text_ += "(u)해제, ";
					if (key) key->insert('u');
				}
			}
			break;
		case ITM_ARMOR_CLOAK:
			text_ += "몸에 두르는 폼나는 망토.\n";
			if (can_use_)
			{
				if (you.equipment[ET_CLOAK] != it)
				{
					use_text_ += "(w)장착, ";
					if (key) key->insert('w');
				}
				else
				{
					use_text_ += "(u)해제, ";
					if (key) key->insert('u');
				}
			}
			break;
		case ITM_ARMOR_GLOVE:
			text_ += "손에 낄 수 있는 장갑이다. 장갑에 저주가 걸려있으면 반지를 빼고 낄 수 없다.\n";
			if (can_use_)
			{
				if (you.equipment[ET_GLOVE] != it)
				{
					use_text_ += "(w)장착, ";
					if (key) key->insert('w');
				}
				else
				{
					use_text_ += "(u)해제, ";
					if (key) key->insert('u');
				}
			}
			break;
		case ITM_ARMOR_BOOT:
			text_ += "발을 보호하는 신발. 던전의 바닥을 맨발로 다니고 싶지않으면 꼭 착용하자.\n";
			if (can_use_)
			{
				if (you.equipment[ET_BOOTS] != it)
				{
					use_text_ += "(w)장착, ";
					if (key) key->insert('w');
				}
				else
				{
					use_text_ += "(u)해제, ";
					if (key) key->insert('u');
				}
			}
			break;
		}
		char temp[100];
		sprintf_s(temp,100, "방어력 : %d", it->value1);
		text_ += temp;
		sprintf_s(temp,100, "\n\n이 아이템은 +2까지 인챈트가 가능하다.");
		text_ += temp;
	}
	break;
	case ITM_POTION:
	{
		if (iden_list.potion_list[it->value1].iden)
		{
			switch (it->value1)
			{
			case PT_WATER:
				text_ += "단순한 맛난 물약이다.\n";
				break;
			case PT_HEAL:
				text_ += "치료 물약이다. 마시면 각종 좋지않은 상태이상에서 회복되고 체력도 회복된다.\n";
				text_ += "효과도 마신 즉시 발휘되는 신비의 물약\n";
				break;
			case PT_POISON:
				text_ += "독이 들어있는 물약이다. 역겨운 맛이 나고 마시면 끔찍한 독에 걸린다.\n";
				break;
			case PT_HEAL_WOUND:
				text_ += "상처를 치료하는 물약이다. 먹으면 순간적으로 많은 체력을 치료한다.\n";
				text_ += "다만 상태이상을 치료하지는 못한다.\n";
				break;
			case PT_MIGHT:
				text_ += "순간적으로 강한 근력을 발휘하게 되는 물약. 공격력도 강해진다.\n";
				break;
			case PT_HASTE:
				text_ += "빠른 속도로 움직이게 도와주는 물약. 이동, 행동 모두 2배속이 된다.\n";
				break;
			case PT_CONFUSE:
				text_ += "마시면 정신에 혼란을 가져다주는 물약.\n";
				text_ += "혼란이 가라앉을때까지 제자리에 서서 가만히 기다리는 것도 방법이다.\n";
				break;
			case PT_SLOW:
				text_ += "움직임이 둔해지는 물약. 모든 이동, 행동이 1/2배속이 된다.\n";
				break;
			case PT_PARALYSIS:
				text_ += "마시면 몇턴간 몸이 마비되는 물약. 위험하다.\n";
				break;
			case PT_CLEVER:
				text_ += "마시면 일시적으로 지능이 높아지는 물약.\n";
				text_ += "지능과 함께 마법성공률, 마법파워도 같이 올라간다.\n";
				break;
			case PT_AGILITY:
				text_ += "마시면 일시적으로 민첩이 높아지는 물약.\n";
				text_ += "민첩과 함께 회피도 올라간다.\n";
				break;
			case PT_MAGIC:
				text_ += "마시면 영력을 순식간에 채워주는 마력의 물약.\n";
				break;
			case PT_LEVETATION:
				text_ += "마시면 일시적으로 비행상태가 되는 물약. 비행상태에서는 깊은물따위를 건널 수 있게된다.\n";
				break;
			case PT_POWER:
				text_ += "마시면 파워가 상승하는 파워의 물약.\n";
				text_ += "마신 즉시 P가 1.00증가하게 된다.\n";
				break;
			case PT_DOWN_STAT:
				text_ += "마시면 일시적으로 능력치가 감소하게 되는 역겨운 물약.\n";
				text_ += "힘 지능 민첩중 무작위 능력치가 일시적으로 감소된다. 시간이 지나면 되돌아 온다.\n";
				break;
			case PT_RECOVER_STAT:
				text_ += "마시면 일시적으로 잃어버린 능력치를 일정량 회복시켜주는 물약.\n";
				break;
			case PT_ALCOHOL:
				text_ += "이것은 술이다. 마시면 취한다.\n";
				text_ += "술에 취한 상태면 똑바로 움직이기 힘들어 진다.\n";
				break;

			default:
				text_ += "이건 버그 물약이다. 끔찍하군!\n";
				break;
			}
		}
		else
		{
			text_ += "뭔가 의심스러운 액체가 들어있는 병. 마셔보지 않고선 알 수 없을 것 같다.\n";
		}
		if (can_use_)
		{
			use_text_ += "(q)마시기, ";
			if (key) key->insert('q');
		}
	}
	break;
	case ITM_FOOD:
		text_ += "먹을 수 있는 음식이다. 던전에 이런 음식들이 떨어져있는 것도 수상하지만 먹을 순 있어 보인다.\n";
		if (can_use_)
		{
			use_text_ += "(e)먹기, ";
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
				text_ += "읽으면 이상한 공간이동을 일으키는 두루마리. 단, 읽자마자 공간이동이 되진 않는다.\n";
				text_ += "몇턴의 준비기간이 필요하다. 공간이동이 걸린 상태에서 읽으면 그 힘을 중화시켜 억제할 수 도 있다.\n";
				break;
			case SCT_IDENTIFY:
				text_ += "식별의 두루마리. 읽고나서 손에 댄 물건을 식별할 수 있게 된다. 매우 중요한 두루마리\n";
				text_ += "모 반요 가게주인의 능력과 매우 흡사하다.\n";
				break;
			case SCT_NONE:
				text_ += "장난꾸러기 요정들이 의미없이 써놓은 낙서군!\n";
				break;
			case SCT_CURSE_WEAPON:
				text_ += "들고있는 무기에 저주를 건다. 저주에 걸린 장비는 저주가 풀리기전까지 해제할 수 없게 된다.\n";
				break;
			case SCT_CURSE_ARMOUR:
				text_ += "들고있는 방어구에 저주를 건다. 저주에 걸린 장비는 저주가 풀리기전까지 해제할 수 없게 된다.\n";
				break;
			case SCT_REMOVE_CURSE:
				text_ += "들고있는 장비의 저주를 해제한다. 기분 나쁨도 사라진다.\n";
				break;
			case SCT_BLINK:
				text_ += "시야내의 임의의 위치에 순간이동을 하게 도와주는 두루마리.\n";
				text_ += "위기탈출용으로 최고의 두루마리다.\n";
				break;
			case SCT_MAPPING:
				text_ += "현재 있는 층의 맵을 밝혀주는 두루마리.\n";
				break;
			case SCT_ENCHANT_WEAPON_1:
			case SCT_ENCHANT_WEAPON_2:
				text_ += "현재 장착되어있는 무기의 공격력과 명중력을 강화시킬 수 있다. 또한 저주도 없애준다.\n";
				break;
			case SCT_ENCHANT_ARMOUR:
				text_ += "선택한 방어구의 방어력을 강화시킬 수 있다. 또한 저주도 없애준다.\n";
				break;
			case SCT_FOG:
				text_ += "연기를 만들어 내는 두루마리.\n";
				text_ += "연기는 상대와 자신의 시야를 가려준다.\n";
				break;
			case SCT_DETECT_CURSE:
				text_ += "소지품중에 저주가 걸린 아이템을 탐지하는 두루마리.\n";
				text_ += "탐지할 아이템이 없어도 식별은 된다.\n";
				break;
			case SCT_CURSE_JEWELRY:
				text_ += "장착하고 있는 장신구에 저주를 거는 두루마리.\n";
				text_ += "반지와 목걸이중 무작위 한개의 장신구에 저주가 걸린다.\n";
				break;
			case SCT_SILENCE:
				text_ += "주변의 소음을 줄이는 두루마리. 일시적으로 정적상태가 된다.\n";
				text_ += "정적범위안에 있는 적은 마법을 사용하지못하며 범위는 시간이 지나면 점점 줄어든다.\n";
				text_ += "단, 자신도 소리를 내야하는 마법과 두루마리, 권능을 사용하지 못하게 된다.\n";
				break;
			case SCT_SOUL_SHOT:
				text_ += "영격을 사용하는 두루마리, 주변의 적에게 저항할 수 없는 짧은 마비를 건다.\n";
				text_ += "효과는 절대적이지만 P를 한칸 강제로 소모하게된다.\n";
				break;
			case SCT_CHARGING:
				text_ += "스펠카드를 충전하는 두루마리. 어느정도 사용한 스펠카드의 충전양을 충전한다.\n";
				text_ += "스펠카드의 최대치가 높을수록 충전하는 양도 늘어난다.\n";
				break;
			case SCT_AMNESIA:
				text_ += "배운 마법을 잊는 망각의 두루마리. 사용시 배우고 있는 마법중에 하나를 선택하여 잊는다.\n";
				text_ += "마법을 배울때 사용한 레벨은 돌려받는다.\n";
				break;
			case SCT_SANTUARY:
				text_ += "읽은 순간 넓은 성역을 펼치는 두루마리. 성역에서는 모든 공격의 데미지를 무효로 한다.\n";
				text_ += "산 속에 사는 어느 야만바가 만들었다고 하는 귀한 두루마리.\n";
				break;
			case SCT_BRAND_WEAPON:
				text_ += "지금 들고 있는 무기에 마법적인 힘을 부여하는 두루마리.\n";
				text_ += "어떤 마법이 부여될지는 알 수 없으며 기존에 부여된 마법적인 힘은 덮어씌워진다.\n";
				break;
			default:
				text_ += "버그의 두루마리. 얼른 제작자에게 버그로 신고해버리자!\n";
				break;
			}
		}
		else
		{
			text_ += "알 수 없는 문자들이 나열되어있는 두루마리.\n";
		}
		text_ += "소리내어서 읽으면 두루마리에 담겨진 미지의 힘을 끌어낼 수 있다.\n";
		if (can_use_)
		{
			use_text_ += "(r)읽기, ";
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
				text_ += "화염의 기운을 담은 스펠카드다.\n";
				text_ += "사용하면 원하는 방향의 넓은 범위로 화염구름을 생성한다.\n";
				text_ += "발동스킬이 높으면 구름의 지속시간이 길어진다.\n";
				break;
			case SPC_V_ICE:
				text_ += "냉기의 기운을 담은 스펠카드다.\n";
				text_ += "상대에게 강력한 냉기공격을 가한다.\n";
				text_ += "발동스킬이 높으면 데미지가 높아진다.\n";
				break;
			case SPC_V_EARTH:
				text_ += "대지의 기운을 담은 스펠카드다.\n";
				text_ += "자체 위력은 낮지만 벽에 부딪히면 벽을 폭발시켜 높은 범위 데미지를 입힌다.\n";
				text_ += "발동스킬이 높으면 데미지가 높아진다.\n";
				break;
			case SPC_V_AIR:
				text_ += "대기의 기운을 담은 스펠카드다.\n";
				text_ += "부채꼴의 넓은 범위에 탄막을 날려 범위내의 적들을 날려버린다.\n";
				text_ += "발동스킬이 높으면 날리는 정도와 위력이 강해진다.\n";
				break;
			case SPC_V_INVISIBLE:
				text_ += "달빛의 기운을 담은 스펠카드다.\n";
				text_ += "사용한 사람을 일정시간 투명하게 만든다.\n";
				text_ += "발동스킬이 높으면 투명의 지속시간이 길어진다.\n";
				break;
			case SPC_V_METAL:
				text_ += "금속의 기운을 담은 스펠카드다.\n";
				text_ += "사용하면 전방으로 철가시를 3연속으로 발사한다.\n";
				text_ += "발동스킬이 높으면 데미지가 높아진다.\n";
				break;
			case SPC_V_SUN:
				text_ += "태양의 기운을 담은 스펠카드다.\n";
				text_ += "사용하면 큰 빛을 발산하여 주변의 적을 빛나게 하고 혼란을 건다.\n";
				text_ += "혼란은 강할수록 저항할 수 있으며 무생물에겐 걸리지않는다.\n";
				text_ += "또한, 흡혈귀에겐 단순한 혼란효과 이상의 데미지를 줄 수 있다고 한다.\n";
				text_ += "발동스킬이 높으면 지속시간과 혼란이 걸릴 확률이 늘어난다.\n";
				break;
			default:
				text_ += "버그의 스펠카드다.\n";
				break;
			}
			text_ += "\n";
		}
		text_ += "스펠카드는 정해진 횟수내에서 마음대로 사용할 수 있으나 초과하면 더이상 사용할 수 없게된다.\n";
		text_ += "정확한 남은 갯수는 식별을 해야 확인할 수 있다. 스펠카드는 발동술에 비례해서 위력이 올라간다.\n";
		if (can_use_)
		{
			use_text_ += "(v)발동, ";
			if (key) key->insert('v');
		}
	}
	break;
	case ITM_AMULET:
	{
		text_ += "미지의 힘이 담겨있는 부적. 기본적으론 아무런 힘도 가지고 있지않는 평범한 부적이지만\n";
		text_ += "착용한 채로 경험치를 얻으면 부적의 충전량이 점점 충전되며 100%가 되면 힘을 발휘한다.\n";
		text_ += "만약 착용하고있는 부적을 벗으면 그 즉시 충전량이 0%로 떨어지므로 주의해야한다.\n\n";
		if (iden_list.amulet_list[it->value1].iden == 2)
		{
			switch (it->value1)
			{
			case AMT_PERFECT:
				text_ += "미래를 체험한다고 하는 에이린의 감주약의 효능이 녹아들어있는 부적.\n";
				text_ += "다른 부적에 비해 아주 느린 속도로 충전이 되지만 힘이 모이면 죽음을 회피할 수 있다.\n";
				text_ += "100%가 된 부적을 착용한 채로 죽게되면 체력이 전부 회복되어 부활한다.\n";
				text_ += "단, 이 방법으로 부활하게되면 부적은 불타 사라지게된다.\n";
				break;
			case AMT_BLOSSOM:
				text_ += "춘설이변에 쓰인 봄의 기운을 모아서 특수한 결계를 발동시킬 수 있는 부적.\n";
				text_ += "착용하고 있으면 주변의 봄의 기운이 모이고 충전이 되면 영격을 발동할 수 있게 된다.\n";
				text_ += "100%가 된 부적을 착용한 채로 v를 누르면 영격이 발동되어 주변의 적을 일정시간 마비시킨다.\n";
				text_ += "발동후에는 충전치가 0%가 되어 다시 충전할 수 있게 된다.\n";
				break;
			case AMT_TIMES:
				text_ += "영야이변을 해결할때 사용된 밤을 멈추는 주술의 힘이 담긴 부적.\n";
				text_ += "착용하고 있으면 주변의 각부가 모이고 충전이 되면 주변의 시간의 흐름보다 빠르게 움직일 수 있다.\n";
				text_ += "100%가 된 부적을 착용한 채로 v를 누르면 가속이 발동한다.\n";
				text_ += "발동후에는 충전치가 0%가 되어 다시 충전할 수 있게 된다.\n";
				break;
			case AMT_FAITH:
				text_ += "신앙의 힘을 모을 수 있는 부적.\n";
				text_ += "착용하고 있으면 주변의 신앙이 모이고 충전이 되면 신들과의 관계가 좋아진다.\n";
				text_ += "100%가 되면 자동으로 현재 신앙심이 조금 오른후 충전치가 다시 0%이 된다.\n";
				text_ += "몇몇 신은 신앙을 모으지않기때문에 이 부적의 효능이 없을 수 있다.\n";
				break;
			case AMT_WAVE:
				text_ += "지령전같은 지하에서도 멀리 있는 상대와 통신이 가능하도록 개조된 부적.\n";
				text_ += "착용하고 있으면 전파수신감도가 점점 좋아지고 충전이 되면 현재 층을 한 눈에 볼 수 있다.\n";
				text_ += "100%가 된 부적을 착용한 채로 v를 누르면 현재 층의 지형을 비추게 된다.\n";
				break;
			case AMT_SPIRIT:
				text_ += "몽전대사묘의 태자를 부활시킬때도 사용되었다던 신령을 담을 수 있는 부적.\n";
				text_ += "착용하고 있으면 주변의 신령이 모이고 충전이 되면 가진 스펠카드에 신령을 불어넣을 수 있다.\n";
				text_ += "100%가 된 부적을 착용한 채로 v를 누르면 가지고 있는 스펠카드 1장을 충전할 수 있다.\n";
				break;
			case AMT_GRAZE:
				text_ += "어느 이변에서나 중요한 그레이즈의 힘이 담긴 부적.\n";
				text_ += "착용하고 있으면 점차 충전이 되고 충전이 끝나면 당신은 탄막괴물이 된다.\n";
				text_ += "100%가 된 부적을 착용한 채로도 상시 그레이즈가 발동되어 원거리 탄막을 일정확률로 피할 수 있고\n";
				text_ += "100%상태에서 v를 누르면 근성회피가 발동되어 회피가능한 공격을 일정턴 100% 회피한다.\n";
				text_ += "그레이즈할때 나는 소리가 기분이 좋다. 그레이즈가 의미없던 시리즈도 있었다고...?\n";
				break;
			case AMT_WEATHER:
				text_ += "어느 불량 천인이 자신의 검의 힘을 부여한 부적.\n";
				text_ += "착용하고 있으면 주변의 기질 구슬을 흡수하고 충전이 끝나면 부적에 숨겨있던 기질이 발동된다.\n";
				text_ += "100%가 된 부적을 착용한 채로 있으면 체력 회복속도가 약간 증가하며\n";
				text_ += "100%상태에서 v를 누르면 체력을 약간 회복할 수 있다.\n";
				break;
			case AMT_OCCULT:
				text_ += "도시전설을 실체화하는 힘을 가진 오컬트볼의 힘이 담긴 부적.\n";
				text_ += "착용하고 있으면 오컬트의 기운을 흡수하고 충전이 끝나면 오컬트의 힘을 방출한다.\n";
				text_ += "100%상태에서 v를 누르면 시야내의 모든 적대적인 소환물을 추방하며\n";
				text_ += "부적안에 숨겨있는 오컬트의 힘을 요괴로서 구현화한다.\n";
				break;
			default:
				text_ += "이 버그 부적은 멋도 없고 효과도 없다.\n";
				break;
			}
		}
		else
		{
			text_ += "이 부적은 아직 무슨 힘을 가지고 있는지 아직 알 수 가 없다.\n";
			text_ += "착용하면 무슨 힘을 숨기고 있는지 알 수 있을 것 같다.\n";
		}		

		if (can_use_)
		{
			if (you.equipment[ET_NECK] != it)
			{
				use_text_ += "(w)장착, ";
				if (key) key->insert('w');
			}
			else
			{
				use_text_ += "(u)해제, ";
				if (key) key->insert('u');
			}
		}
	}
	break;
	case ITM_RING:
	{
		if (iden_list.ring_list[it->value1].iden == 2)
		{
			switch (it->value1)
			{
			case RGT_STR:
				text_ += "손에 낀 착용자의 근력을 강화시키거나 약화시키는 힘의 반지.\n";
				text_ += "그 증감량은 반지의 수치에 달려있다.\n";
				break;
			case RGT_DEX:
				text_ += "손에 낀 착용자의 민첩성을 강화시키거나 약화시키는 민첩의 반지.\n";
				text_ += "그 증감량은 반지의 수치에 달려있다.\n";
				break;
			case RGT_INT:
				text_ += "손에 낀 착용자의 지능을 강화시키거나 약화시키는 지능의 반지.\n";
				text_ += "그 증감량은 반지의 수치에 달려있다.\n";
				break;
			case RGT_HUNGRY:
				text_ += "착용한 자의 자연적인 P템 소모가 빠르게 되는 배고픔의 반지.\n";
				break;
			case RGT_FULL:
				text_ += "미노리코님의 축복이 담겨있는 반지로 착용한 자가 포만감을 느끼게 된다.\n";
				text_ += "신진대사가 느려져서 착용자는 자연적인 P템 소모가 느려지게 된다.\n";
				text_ += "가속이나 투명상태에서의 P소모 가속도 줄여준다.\n";
				break;
			case RGT_TELEPORT:
				text_ += "착용자에게 공간이동의 능력을 부여하는 반지.\n";
				text_ += "그 부작용으로 끼고 있는 동안 무작위의 공간이동이 간간히 발생하게된다.\n";
				break;
			case RGT_POISON_RESIS:
				text_ += "독에 대한 내성을 얻는 반지. 거의 모든 독에 내성이 생긴다.\n";
				break;
			case RGT_FIRE_RESIS:
				text_ += "화염에 대한 저항을 얻는 반지. 총 3단계까지 중첩저항을 얻을 수 있다.\n";
				break;
			case RGT_ICE_RESIS:
				text_ += "냉기에 대한 저항을 얻는 반지. 총 3단계까지 중첩저항을 얻을 수 있다.\n";
				break;
			case RGT_SEE_INVISIBLE:
				text_ += "착용하고 있으면 투명한 적을 볼 수 있게 된다.\n";
				break;
				/*case RGT_GRAZE:
					text_ += "그레이즈를 사용할 수 있는 반지. 착용하면 능력사용에서 그레이즈발동이 생긴다.\n";
					text_ += "그레이즈상태에서는 모든 원거리 공격을 일정확률로 피할 수 있게 된다.\n";
					text_ += "사용에는 발동스킬이 필요하며 P가 약간 소모된다.\n";
					break;*/
			case RGT_LEVITATION:
				text_ += "비행을 사용할 수 있는 반지. 착용하면 능력사용에서 비행발동이 생긴다.\n";
				text_ += "비행상태에서는 깊은물따위를 건널 수 있게된다.\n";
				text_ += "사용에는 발동스킬이 필요하며 P가 약간 소모된다.\n";
				break;
			case RGT_INVISIBLE:
				text_ += "투명을 사용할 수 있는 반지. 착용하면 능력사용에서 투명발동이 생긴다.\n";
				text_ += "투명상태에서는 적에게 들킬 확률이 매우 낮아지게 된다.\n";
				text_ += "투명상태에서는 P의 소모량이 가속되는 단점이 있다.\n";
				text_ += "사용에는 발동스킬이 필요하며 P가 약간 소모된다.\n";
				break;
			case RGT_MANA:
				text_ += "착용시 최대마나가 증가하는 반지.\n";
				text_ += "착용해제시 원래대로 돌아온다.\n";
				break;
			case RGT_MAGACIAN:
				text_ += "착용시 마법성공률과 마법파워를 상승시키는 반지.\n";
				break;
			case RGT_AC:
				text_ += "착용시 방어가 증감하는 반지.\n";
				text_ += "증가감 되는 수치는 반지에 적혀진 숫자와 같다.\n";
				break;
			case RGT_EV:
				text_ += "착용시 회피가 증가하는 반지.\n";
				text_ += "증감 되는 수치는 반지에 적혀진 숫자와 같다.\n";
				break;
			case RGT_CONFUSE_RESIS:
				text_ += "착용시 혼란과 광기에 저항이 생기는 반지.\n";
				break;
			case RGT_ELEC_RESIS:
				text_ += "착용시 전기저항이 올라가는 반지.\n";
				text_ += "완벽하게 막아주진 않지만 상당한 데미지를 줄여준다.\n";
				break;
			case RGT_MAGIC_RESIS:
				text_ += "착용시 마법저항이 올라가는 반지.\n";
				text_ += "마법저항은 데미지를 줄여주진 못하지만 디버프같은 마법으로부터 보호해준다.\n";
				break;
			default:
				text_ += "버그의 힘이 깃든 반지다.\n";
				break;
			}
		}
		else
		{
			text_ += "미지의 힘이 담겨있는 반지.\n";
			text_ += "착용시 바로 그 힘을 알 수 있는 반지도 있는 반면. 눈치채기 힘든 반지도 있다.\n";
		}
		if (can_use_)
		{
			if (you.equipment[ET_RIGHT] != it && you.equipment[ET_LEFT] != it)
			{
				use_text_ += "(w)장착, ";
				if (key) key->insert('w');
			}
			else
			{
				use_text_ += "(u)해제, ";
				if (key) key->insert('u');
			}
		}
	}
	break;
	case ITM_BOOK:
	{

		text_ += GetBookInfor((book_list)it->value0);
		text_ += "\n\n";
		if (it->identify)
		{
			char temp[100], sp_char = 'a';
			sprintf_s(temp,100, "%-34s%-30s%s\n", "마법이름", "학파", "레벨");
			text_ += temp;
			for (int i = 0; i < 8; i++)
			{
				spell_list spell_;
				if ((spell_ = (spell_list)it->GetValue(i + 1)) != SPL_NONE)
				{
					sprintf_s(temp,100, "%c - %-30s%-30s%d\n", sp_char++, SpellString(spell_), GetSpellSchoolString(spell_).c_str(), SpellLevel(spell_));
					text_ += temp;
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
			text_ += "누군가가 잃어버린 보탑. 강력한 힘이 담겨있다.\n";
			text_ += "발동하게되면 안에 모여있던 힘이 레이저의 형태로 발사된다.\n";
			text_ += "발동 스킬이 높아지면 데미지가 높아진다.\n";
			break;
		case EVK_AIR_SCROLL:
			text_ += "어딘가의 주지승이 쓰고 있던 경전. 마법의 힘이 담겨 있다.\n";
			text_ += "발동하게되면 파워를 대가로 사용자의 영력을 순식간에 회복시켜준다.\n";
			text_ += "발동 스킬이 높아지면 회복되는 영력이 많아진다.\n";
			break;
		case EVK_DREAM_SOUL:
			text_ += "꿈의 세계에서 해메고있던 영혼이다.\n";
			text_ += "사용하면 꿈의 세계로부터 환상의 실체화가 잠시동안 가능하다.\n";
			text_ += "어딘가의 지역에 있던 몬스터 무리들이 아군이 되어 소환된다.\n";
			text_ += "발동 스킬이 높아지면 더욱 강한 아군이 소환된다.\n";
			break;
		case EVK_BOMB:
			text_ += "아주 거대한 폭탄. 마법의 힘으로 점화가 가능하다.\n";
			text_ += "발동하게되면 폭탄이 점화되어 목표지점으로 던질 수 있다.\n";
			text_ += "던진 폭탄은 바로 터지진않지만 몇 턴이 지나면 큰 폭발이 일어난다.\n";
			text_ += "폭탄은 한 칸을 차지하며 적에 의해 파괴되면 폭파하지않고 파괴되어버린다.\n";
			text_ += "발동템이므로 사용해도 소모되진않는다. 신비한 마법의 힘이 작용하는 것 같다.\n";
			text_ += "발동 스킬이 높아지면 데미지와 폭탄의 체력이 높아진다.\n";
			break;
		case EVK_GHOST_BALL:
			text_ += "사람없이 등불만 떠다닌다는 괴담의 하나로 유령이 들고다닌다는 등불이다.\n";
			text_ += "발동하여 손에 들면 아무에게도 보이지않고 공격당하지않는 유령화상태가 된다.\n";
			text_ += "발동시 자신의 현재 체력이 30%~70%까지 감소되고 발동된다.\n";
			text_ += "발동중엔 누구에게도 공격을 받는 무적상태지만 체력은 회복되지않고 파워가 빠르게 떨어진다.\n";
			text_ += "한번 더 발동해서 종료하거나 파워가 0이되면 자동으로 종료된다.\n";
			text_ += "유령화상태에선 이동만 가능하여 아이템, 마법, 공격등의 모든 행동이 불가능하다.\n";
			text_ += "만약 당신이 어떤 이유로 파워가 낮아지지 않는다면 오쿠리쵸친은 다른 무언가를 대신 가져갈 것이다.\n";
			text_ += "발동 스킬이 높아지면 발동시 감소되는 체력과 발동중 떨어지는 파워소모가 낮아진다.\n";
			break;
		case EVK_SKY_TORPEDO:
			text_ += "캇파가 물밖에서도 쏠 수 있도록 개량한 어뢰.\n";
			text_ += "잘 생각해보면 미사일과 별반 다를게 없다.\n";
			text_ += "발동 스킬이 높아지면 데미지가 높아진다.\n";
			break;
		case EVK_MAGIC_HAMMER:
			text_ += "소인족이 다룬다고 하는 요술망치. 본래 주인은 오니라고 한다.\n";
			text_ += "사용하면 실로 엄청난 효과들을 원하는대로 파워 1칸만으로 사용할 수 있게 된다.\n";
			text_ += "단, 요술망치를 사용하는것은 큰 위험부담이 따르게되며 사용자를 자멸시킨다고 한다.\n";
			text_ += "요술망치를 사용시 10%의 확률로 정반대의 효과가 발휘될 가능성이 있다.\n";
			break;
		default:
			text_ += "버그를 담은 발동템이다.\n";
			break;
		}
		text_ += "\n\n";
		text_ += "이 템은 횟수제한없이 발동이 가능한 템이다. 당신의 발동스킬에 비례해서 강력함이 결정된다.\n";
		text_ += "V키로 파워를 소모하여 발동할 수 있다.\n\n";
		char temp[100];
		sprintf_s(temp,100, "이 발동템을 사용할때마다 필요한 파워: %d.%02d\n", Evokeusepower((evoke_kind)it->value1, true) / 100, Evokeusepower((evoke_kind)it->value1, true) % 100);
		text_ += temp;

		if (can_use_)
		{
			use_text_ += "(v)발동, ";
			if (key) key->insert('v');
		}
	}
	break;

	case ITM_GOAL:
		text_ += "이것은 각종 던전을 정복한 증거인 룬이다. \n";
		text_ += "3개를 모으면 최심부 하쿠레이 신사의 문을 열 수 있다.\n";
		break;
	case ITM_ORB:
		text_ += "이것은 강대한 힘을 가진 음양옥이다. 신사 내부에 정중하게 모셔져 있다.\n";
		text_ += "이 것을 가지고 탈출하면 이 이변을 끝내거나 엄청난 힘을 얻을 수 있을 것 같다.\n";
		text_ += "어떻게 사용하는지는 당신의 자유이다! 그러나 탈출할때까진 끝이 아니므로 조심하길!\n";
		text_ += "특히 신사의 홍백의 무녀가 눈에 불을 키고 당신을 쫓아올 것이다.\n";
		break;
	case ITM_ETC:
		switch (it->value1)
		{
		case EIT_SATORI:
			if (you.god_value[GT_SATORI][0] == 1)
			{
				text_ += "\"잃어버린 애완동물을 찾습니다. - 코메이지 사토리\"라고 적혀있는 종이다.\n";
				text_ += "당신의 사진이 붙어있다...\n";
			}
			else
			{
				text_ += "\"잃어버린 물건을 찾습니다. - 코메이지 사토리\"라고 적혀있는 종이다.\n";
			}
			break;
		case EIT_CAT_TREE:
			text_ += "개다래 나무다. 그렇게 유용하진않아보이지만 고양이과들은 맥을 못 추는듯하다.\n";
			break;
		case EIT_BROKEN_CAMERA:
			text_ += "부셔져있는 텐구의 카메라다. 아무래도 캇파들이 수리를 위해 보관하고 있는 듯 하다.\n";
			text_ += "심하게 부셔져있기때문에 쓰임새는 전혀 없어보인다.\n";
			break;
		case EIT_KAPPA_TRASH:
			text_ += "캇파들이 쓰고 남은 재료와 공구들이다. 쓰임새는 없을 것 같다.\n";
			break;
		}
		break;
	default:
		text_ += "버그템이다. 제작자에게 신고하자.\n";
		break;
	}

	if (can_use_)
	{
		if (it->type == ITM_BOOK)
		{
			use_text_ += "(D)버리기";
			if (key) key->insert('D');
		}
		else
		{
			use_text_ += "(d)버리기";
			if (key) key->insert('d');
		}
	}



	if(it->isArtifact() && it->identify)
	{
		text_ += "\n\n";
		for(auto it2 = it->atifact_vector.begin(); it2 != it->atifact_vector.end(); it2++)
		{
			text_ += GetAtifactInfor((ring_type)it2->kind, it2->value);
			text_ += "\n";
		}
	}


	text_ += "\n\n\n";
	text_ += use_text_;
	//char temp[100];
	//if(!it->is_pile || it->num == 1)
	//	sprintf_s(temp, 100,"\n\n\n무게 : %g\n",it->weight);
	//else
	//	sprintf_s(temp, 100,"\n\n\n무게 : %g * %d\n",it->weight/it->num,it->num);
	//text_ += temp;
	return text_;

}