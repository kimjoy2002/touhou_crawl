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

extern HANDLE mutx;
string GetItemInfor(item *it);


void PickUp()
{		
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 무언가를 주울 수 없다!",true,false,false,CL_danger);
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
void PickUpSelect(list<item>::iterator it, int num)
{	
	for(;it != env[current_level].item_list.end() && num;num--)
	{
		list<item>::iterator temp = it++;
		if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
		{
			if(isPick(&(*temp)))
			{
				printlog((*temp).GetName(),false,false,false,(*temp).item_color());
				printlog("을 줍습니까? (예:y 아니오:n 모두:a 선택:*?g,)",true,false,false,CL_help);
				switch(waitkeyinput())
				{
				case 'y':
				case 'Y':
					if(you.additem(&(*temp)))
					{
						env[current_level].DeleteItem(temp);
						you.time_delay+=you.GetNormalDelay();
						you.TurnEnd();
					}
					break;
				case 'a':
					PickUpNum(temp,num,false);
					return;
				case '*':
				case '?':
				case 'g':
				case ',':
					iteminfor_pick();
					return;
				case 'o':
					//자동탐색을 넣는다.
					break;
				}
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
				}
				return true;
			}
			else
				return false;
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
	view_item(IVT_PICK,"무슨 아이템을 줍겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			CheckKey(key_);
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
		else if(key_ == VK_ESCAPE)
			break;

	}
	changedisplay(DT_GAME);
}


void discard(list<item>::iterator it, int number)
{
	item *temp2 = env[current_level].AddItem(you.position,&(*it),number);	
	temp2->drop = true;
	printlog("당신은 ",false,false,false,CL_normal);					
	printlog(temp2->GetName(number),false,false,false,temp2->item_color());				
	printlog(temp2->GetNameInfor().name_to(true),false,false,false,CL_normal);					
	printlog("내려놓았다.",true,false,false,CL_normal);	
	you.DeleteItem(it,number);
	changedisplay(DT_GAME);
	you.time_delay+=you.GetNormalDelay();
	you.TurnEnd();
}



void iteminfor_discard()
{	
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 무언가를 버릴 수 없다!",true,false,false,CL_danger);
		return;
	}
	int i=0;
	view_item(IVT_DISCARD,"무슨 아이템을 버리겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			CheckKey(key_,i);
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
		else if((key_ >= '0' && key_ <= '9'))
		{
			i= i*10+key_-'0';
		}
		else if(key_ == VK_RETURN)
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
		else if(key_ == VK_ESCAPE)
			break;

	}
	changedisplay(DT_GAME);
}

void fast_discard()
{	
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 무언가를 버릴 수 없다!",true,false,false,CL_danger);
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
			return;
		}
	}
}

void Eatting()
{	
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 먹을 수 없다!",true,false,false,CL_danger);
		return;
	}
	if(you.power >= 500 && !(you.god == GT_MINORIKO))
	{
		printlog("당신은 이미 풀파워다!",true,false,false,CL_normal);
		return;
	}
	view_item(IVT_FOOD,"무엇을 먹겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			you.Eat(key_);
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
			view_item(IVT_SELECT,"무엇을 먹겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}


void Drinking()
{
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 마실 수 없다!",true,false,false,CL_danger);
		return;
	}
	view_item(IVT_POTION,"무엇을 마시겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			if(you.Drink(key_))
			{			
				you.time_delay += you.GetNormalDelay();
				you.doingActionDump(DACT_USE, "물약");
				changedisplay(DT_GAME);
				if(you.god == GT_EIRIN)
				{
					if(randA(2))
					{
						you.PietyUpDown(1);
						you.GiftCount(1);
					}
				}
				you.TurnEnd();
			}
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
			view_item(IVT_SELECT,"무엇을 마시겠습니까?");
		else if(key_ == VK_ESCAPE)
		{
			break;
		}
	}
	changedisplay(DT_GAME);
}

//void Spelllcard_Declare()
//{
//	if(!you.equipment[ET_NECK])
//	{
//		printlog("스펠카드를 장착하고 있지 않다.",true,false,false,CL_normal);
//		return;
//	}
//	if(you.GetSpellcard())
//	{
//		printlog("이미 선언 중이다.",true,false,false,CL_normal);
//		return;
//	}
//	if(declare_spellcard((spellcard_declare_type)you.equipment[ET_NECK]->value1, 20+you.level*5)){
//		int turn_ = spellcard_turn((spellcard_declare_type)you.equipment[ET_NECK]->value1, (spellcard_evoke_type)you.equipment[ET_NECK]->value2, (spellcard_passive_type)you.equipment[ET_NECK]->value3);
//		you.SetSpellcard(turn_);
//		passive_spellcard((spellcard_passive_type)you.equipment[ET_NECK]->value3, you.equipment[ET_NECK]->value4, 1, turn_-1);
//	}
//}

void Spelllcard_Evoke()
{	
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 할 수 없다!",true,false,false,CL_danger);
		return;
	}
	int i=0;
	view_item(IVT_EVOKE,"무슨 아이템을 발동하시겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			if(you.Evoke(key_))
			{
				
				you.time_delay += you.GetNormalDelay();
				you.TurnEnd();
			}
			break;
		//	CheckKey(key_,i);
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
			view_item(IVT_SELECT,"무엇을 발동하시겠습니까?");
		else if(key_ == VK_ESCAPE)
		{
			break;
		}
	}
	changedisplay(DT_GAME);
}
void Reading()
{	
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 읽을 수 없다!",true,false,false,CL_danger);
		return;
	}
	if(env[current_level].isSilence(you.position))
	{
		printlog("당신은 소리를 낼 수 없다.",true,false,false,CL_normal);
		return;
	}
	view_item(IVT_SCROLL,"무엇을 읽겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			item* item_ = you.GetItem(key_);
			if(!item_)
				continue;
			if(item_->type == ITM_BOOK)
			{
				if(item_->value0>=0)	
				{
					iden_list.books_list[item_->value0] = true;
					item_->identify = true;
				}
				while(1)
				{
					WaitForSingleObject(mutx, INFINITE);
					SetText() = GetItemInfor(item_);
					ReleaseMutex(mutx);
					changedisplay(DT_TEXT);
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
					view_item(IVT_SCROLL,"무엇을 읽겠습니까?");
					break;
				}
			}
			else if(item_->type == ITM_SCROLL)
			{
				if(you.Read(key_))
				{
					you.doingActionDump(DACT_USE, "두루마리");
					you.time_delay += you.GetNormalDelay();
					changedisplay(DT_GAME);
					you.TurnEnd();
				}	
			}
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
			view_item(IVT_SELECT,"무엇을 읽겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}