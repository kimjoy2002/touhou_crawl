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

extern HANDLE mutx;



string GetItemInfor(item *it);

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
					WaitForSingleObject(mutx, INFINITE);
					SetText() = GetItemInfor(item_);
					ReleaseMutex(mutx);
					changedisplay(DT_TEXT);
					if(item_->type == ITM_BOOK)
					{
						int key_ = waitkeyinput(true);
						if( (key_ >= 'a' && key_ <= 'f'))
						{
							if(int spell_ = item_->GetValue(key_ - 'a'+1))
							{	
								WaitForSingleObject(mutx, INFINITE);
								SetText() = GetSpellInfor((spell_list)spell_);
								ReleaseMutex(mutx);
								waitkeyinput();
								continue;
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
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----이동키끝-------
		else if(key_ == VK_ESCAPE || (key_ == VK_RETURN && gameover))
			break;
	}
	changedisplay(DT_GAME);
}

string GetItemInfor(item *it)
{
	string text_ = it->GetName();
	text_ += "\n\n";
	switch(it->type)
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
			switch(it->type)
			{
			case ITM_WEAPON_SHORTBLADE:
				text_ += "날이 짧은 검이다. 빠른 속도로 공격할 수 있다.\n";
				ski_ = SKT_SHORTBLADE;
				break;
			case ITM_WEAPON_LONGBLADE:
				text_ += "날이 긴 장검이다. 찌르거나 베면서 상대를 공격한다.\n";
				ski_ = SKT_LONGBLADE;
				break;
			case ITM_WEAPON_MACE:
				text_ += "뭉툭한 둔기다.\n";
				ski_ = SKT_MACE;
				break;
			case ITM_WEAPON_SPEAR:
				text_ += "길다란 창이다. 적을 찔러서 공격할 수 있다.\n";
				ski_ = SKT_SPEAR;
				break;
			case ITM_WEAPON_AXE:
				text_ += "적을 찍을 수 있는 도끼. 거대한 날을 지녔다.\n";
				ski_ = SKT_AXE;
				break;
			//case ITM_WEAPON_BOW:
			//	text_ += "화살을 걸고 멀리 있는 적에게 날릴 수 있는 활이다. 화살이 없으면 의미가 없다.\n";
			//	break;
			}


			
			if(it->value5 && it->value6)
			{
				text_ += "\n\n";
				text_ += GetBrandInfor((weapon_brand)it->value5);
				text_ += "\n";
			}

			char temp[100];
			sprintf(temp,"\n공격력 : %d       명중력 : %d",it->value2,it->value1);
			text_ += temp;
			sprintf(temp,"\n현재공격속도 : %g%%    ( 기본공격속도 : %d0%%       최소공격속도 : %d0%% )",max((it->value8) , (it->value7-you.skill[ski_].level/2.0f))*10,it->value7,it->value8);
			text_ += temp;
			if(it->throw_item)
			{
				sprintf(temp,"\n이 아이템은 던질 수 있다.");
				text_ += temp;
			}
			sprintf(temp,"\n\n이 아이템은 +9까지 인챈트가 가능하다.");
			text_ += temp;
			break;
		}
	case ITM_THROW_TANMAC:
		{
			switch(it->value4)
			{
			default://없음 이거 뜨면 버그
				text_ += "탄막 놀이의 기본이 되는 탄막이다. 적에게 던져서 맞춘다.\n";
				text_ += "문제는 이게 버그 탄막이라는 것이다.\n";
				break;
			case TMT_BILL:
				text_ += "탄막 놀이의 기본이 되는 탄막이다. 적에게 던져서 맞춘다.\n";
				text_ += "이 부적은 강하진 않지만 원거리에서 적을 공격할 수 있다.\n";
				break;
			case TMT_AMULET:
				text_ += "레이무가 쓰는 이 치사한 아뮬렛에는 고성능의 호밍성능이 붙어있다.\n";
				text_ += "거의 필중으로 맞출 수 있는 것이 자랑이다.\n";
				break;			
			case TMT_POISON_NEEDLE:
				text_ += "이것은 던지면서 상대에게 박히는 침이다.\n";
				text_ += "데미지는 낮지만 이 침에는 특별히 독이 발라져있는것 같다.\n";
				break;
			case TMT_KIKU_COMPRESSER:
				text_ += "캇파들의 발명품중 하나다. 물을 가득 압축하고있는 폭탄이다.\n";
				text_ += "상대에게 던지면 압축되어있던 물이 한번에 터진다.\n";
				text_ += "넓은 범위 공격할 수 있을 것 같다.\n";
				break;
			}
			char temp[100];
			sprintf(temp,"\n공격력 : %d       명중력 : %d",it->value2,it->value1);
			text_ += temp;
		}
		break;
	case ITM_ARMOR_BODY_ARMOUR_0:
	case ITM_ARMOR_BODY_ARMOUR_1:
	case ITM_ARMOR_BODY_ARMOUR_2:
	case ITM_ARMOR_BODY_ARMOUR_3:
		{
			switch(it->value5)
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
			switch(it->type)
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
			sprintf(temp,"\n\n방어력 : %d   기본패널티 : %d   최소패널티 : %d\n\n",it->value1,it->value2,it->value3);
			text_ += temp;
			sprintf(temp,"\n\n패널티는 갑옷스킬을 올릴수록 줄어듭니다. 최소패널티이하로는 줄일수 없습니다.\n\n");
			text_ += temp;
			sprintf(temp,"합계 패널티만큼 회피와 은밀, 마법성공율이 감소합니다.\n");
			text_ += temp;
			sprintf(temp,"합계 패널티가 %d보다 높으면 패널티만큼 추가적으로 명중율이 감소합니다.\n", you.GetPenaltyMinus(1));
			text_ += temp;
			sprintf(temp,"합계 패널티가 %d보다 높으면 패널티만큼 이동속도가 감소합니다.\n", you.GetPenaltyMinus(2));
			text_ += temp;
			sprintf(temp,"합계 패널티가 %d보다 높으면 모든 행동이 2배 딜레이됩니다.\n\n", you.GetPenaltyMinus(3));
			text_ += temp;
			sprintf(temp,"\n이 아이템은 +%d까지 인챈트가 가능하다.", it->value1);
			text_ += temp;
			break;
		}
	case ITM_ARMOR_SHIELD:
		{
		text_ += "상대의 공격을 막기 위한 방패. 양손무기를 들고 있으면 장착이 불가능하다.\n";
		text_ += "상대의 탄막을 막는 반칙적인 활용도 가능하다.\n";
		char temp[100];
		sprintf(temp,"방어력 : %d   기본패널티 : %d   최소패널티 : %d\n\n",it->value1,it->value2,it->value3);
		text_ += temp;
		sprintf(temp,"패널티는 방패스킬을 올릴수록 줄어듭니다. 최소패널티이하로는 줄일수 없습니다.\n\n");
		text_ += temp;
		sprintf(temp,"합계 패널티만큼 회피와 은밀, 마법성공율, 은밀이 감소합니다.\n", you.s_str/4);
		text_ += temp;
		sprintf(temp,"합계 패널티가 %d보다 높으면 패널티만큼 추가적으로 명중율이 감소합니다.\n", you.GetPenaltyMinus(1));
		text_ += temp;
		sprintf(temp,"합계 패널티가 %d보다 높으면 패널티만큼 이동속도가 감소합니다.\n", you.GetPenaltyMinus(2));
		text_ += temp;
		sprintf(temp,"합계 패널티가 %d보다 높으면 모든 행동이 2배 딜레이됩니다.\n\n", you.GetPenaltyMinus(3));
		text_ += temp;
		sprintf(temp,"이 아이템은 +%d까지 인챈트가 가능하다.",it->value1<=4?3:(it->value1<=8?6:9));
		text_ += temp;
		break;
		}
	case ITM_POTION:
		{
			if(iden_list.potion_list[it->value1].iden)
			{
				switch(it->value1)
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
					text_ += "마시면 일시적으로 잃어버린 능력치를 바로 회복시켜주는 물약.\n";
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
		}
		break;
	case ITM_FOOD:
		text_ += "먹을 수 있는 음식이다. 던전에 이런 음식들이 떨어져있는 것도 수상하지만 먹을 순 있어 보인다.\n";
		break;
	case ITM_SCROLL:
		{
			if(iden_list.scroll_list[it->value1].iden == 3)
			{
				switch(it->value1)
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
		}
		break;
	case ITM_SPELL:
		{
			if(iden_list.spellcard_list[it->value2].iden == 2)
			{
				switch(it->value2)
				{
				case SPC_V_FIRE:
					text_ += "화염의 기운을 담은 스펠카드다.\n";
					text_ += "상대에게 강력한 화염공격을 가한다.\n";
					break;
				case SPC_V_ICE:
					text_ += "냉기의 기운을 담은 스펠카드다.\n";
					text_ += "상대에게 강력한 냉기공격을 가한다.\n";
					break;
				case SPC_V_EARTH:
					text_ += "대지의 기운을 담은 스펠카드다.\n";
					text_ += "자체 위력은 낮지만 벽에 부딪히면 벽을 폭발시켜 높은 범위 데미지를 입힌다.\n";
					break;
				case SPC_V_AIR:
					text_ += "대기의 기운을 담은 스펠카드다.\n";
					text_ += "부채꼴의 넓은 범위에 탄막을 날려 범위내의 적들을 날려버린다.\n";
					break;
				case SPC_V_INVISIBLE:
					text_ += "사용한 사람을 투명하게 만드는 스펠카드다.\n";
					break;
				default:
					text_ += "버그의 스펠카드다.\n";
					break;
				}				
				text_ += "\n";
			}
			text_ += "스펠카드는 정해진 횟수내에서 마음대로 사용할 수 있으나 초과하면 더이상 사용할 수 없게된다.\n";
			text_ += "정확한 남은 갯수는 식별을 해야 확인할 수 있다. 스펠카드는 발동술에 비례해서 위력이 올라간다.\n";
		}
		break;
	case ITM_SPELLCARD:
		{
			text_ += "미지의 힘이 담겨있는 스펠카드.\n";
			text_ += "천차만별의 스펠카드가 있으며 각각 고유의 능력을 각각 가지고 있다.\n";
			text_ += "착용된 스펠카드는 'c'로 선언이 가능하면 선언도중에는 'v'로 고유능력을 사용할 수 있다.\n";
			text_ += "단 스펠카드는 많은 P를 필요로 하여 착용할때, 선언할때, 고유능력을 사용할때 P의 소모가 극심하다.\n";
			//if(iden_list.amulet_list[it->value1].iden == 2)
			//{
			//	switch(it->value1)
			//	{
			//	//case AMT_AC:
			//	//	text_ += "목에 건 착용자의 방어를 강화시키거나 약화시키는 방어의 목걸이.\n";
			//	//	text_ += "그 증감량은 목걸이의 수치에 달려있다.\n";
			//	//	break;
			//	//case AMT_EV:
			//	//	text_ += "목에 건 착용자에게 회피를 잘하게 만들거나 둔하게 만드는 회피의 목걸이.\n";
			//	//	text_ += "그 증감량은 목걸이의 수치에 달려있다.\n";
			//	//	break;
			//	//case AMT_CONFUSE_RESIS:
			//	//	text_ += "혼란에 대한 저항을 주는 목걸이이다.\n";
			//	//	break;
			//	//case AMT_INACCURACY:
			//	//	text_ += "이 목걸이를 착용하고 있으면 명중률이 감소한다.\n";
			//	//	break;
			//	//case AMT_POWER_KEEP:
			//	//	text_ += "이 목걸이는 당신의 P소모를 감소시켜준다.\n";
			//	//	text_ += "P가 3이하일때 감소량을 감소시키고 가속이나 투명상태에서의 P소모 가속도 줄여준다.\n";
			//	//	break;
			//	default:
			//		text_ += "이 버그 목걸이는 멋도 없고 효과도 없다.\n";
			//		break;
			//	}
			//}
			//else
			//{
			//	text_ += "미지의 힘이 담겨있는 목걸이.\n";
			//	text_ += "착용시 바로 그 힘을 알 수 있는 목걸이도 있는 반면. 눈치채기 힘든 목걸이도 있다.\n";
			//}
		}
		break;
	case ITM_RING:
		{
			if(iden_list.ring_list[it->value1].iden == 2)
			{
				switch(it->value1)
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
				case RGT_GRAZE:
					text_ += "그레이즈를 사용할 수 있는 반지. 착용하면 능력사용에서 그레이즈발동이 생긴다.\n";
					text_ += "그레이즈상태에서는 모든 원거리 공격을 일정확률로 피할 수 있게 된다.\n";
					text_ += "사용에는 발동스킬이 필요하며 P가 약간 소모된다.\n";
					break;
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
		}
		break;
	case ITM_BOOK:
		{
			text_ += "책이다.\n\n\n";
			if(it->identify)
			{
				char temp[100], sp_char='a';
				sprintf(temp,"%-34s%-30s%s\n","마법이름","학파","레벨");
				text_ += temp;
				for(int i=0;i<8;i++)
				{
					spell_list spell_;
					if((spell_ = (spell_list)it->GetValue(i+1)) != SPL_NONE)
					{
						sprintf(temp,"%c - %-30s%-30s%d\n",sp_char++,SpellString(spell_),GetSpellSchoolString(spell_).c_str(),SpellLevel(spell_));
						text_ += temp;
					}
				}
			}
		}
		break;
	case ITM_MISCELLANEOUS:
		{
			switch(it->value1)
			{
			case EVK_PAGODA:
				text_ += "누군가가 잃어버린 보탑. 강력한 힘이 담겨있다.\n";
				text_ += "발동하게되면 안에 모여있던 힘이 레이저의 형태로 발사된다.\n";
				break;
			case EVK_AIR_SCROLL:
				text_ += "어딘가의 주지승이 쓰고 있던 경전. 마법의 힘이 담겨 있다.\n";
				text_ += "발동하게되면 파워를 대가로 사용자의 영력을 순식간에 회복시켜준다.\n";
				break;
			case EVK_DREAM_SOUL:
				text_ += "꿈의 세계에서 해메고있던 영혼이다.\n";
				text_ += "사용하면 꿈의 세계로부터 환상의 실체화가 잠시동안 가능하다.\n";
				text_ += "어딘가의 지역에 있던 몬스터 무리들이 아군이 되어 소환된다.\n";
				break;
			default:
				text_ += "버그를 담은 발동템이다.\n";
				break;
			}
			text_ += "\n\n";					
			text_ += "이 템은 횟수제한없이 발동이 가능한 템이다. 당신의 발동스킬에 비례해서 강력함이 결정된다.\n";
			text_ += "V키로 파워를 소모하여 발동할 수 있다.\n\n";
			char temp[100];
			sprintf(temp,"이 발동템을 사용할때마다 필요한 파워: %d.%02d\n",Evokeusepower((evoke_kind)it->value1,true)/100,Evokeusepower((evoke_kind)it->value1,true)%100);
			text_ += temp;

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
	default:
		text_ += "버그템이다. 제작자에게 신고하자.\n";
		break;
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

	//char temp[100];
	//if(!it->is_pile || it->num == 1)
	//	sprintf(temp,"\n\n\n무게 : %g\n",it->weight);
	//else
	//	sprintf(temp,"\n\n\n무게 : %g * %d\n",it->weight/it->num,it->num);
	//text_ += temp;
	return text_;

}