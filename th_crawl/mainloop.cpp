//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mainloop.h
//
// 내용: 주게임루프
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "environment.h"
#include "display.h"
#include "key.h"
#include "save.h"
#include "player.h"
#include "beam.h"
#include "monster_texture.h"
#include "map.h"
#include "dump.h"
#include "god.h"
#include "throw.h"
#include "skill_use.h"
#include "note.h"
#include "tribe.h"
#include "network.h"





extern bool saveexit;

extern HANDLE mutx;

const char *version_string = "ver0.66";


void Initialize();


void SetJob(job_type select_, string name_);
void TouhouPlayerble(const string name_, bool aptit_);
skill_type itemtoskill(item_type type_);


void Test_char_init(item_type item_, int bonus)
{

	item_infor t;

	t.type = item_;
	t.num = 1;
	t.curse = false;
	t.value3 = (int)(bonus == 6);
	t.value4 = (int)(bonus == 6);
	t.is_pile = false;
	t.name2.name = "";
	t.name2.name_type = true;
	switch(item_)
	{
	case ITM_WEAPON_SHORTBLADE:
		t.value1 = 4;
		t.value2 = 7;
		t.value5 = 0;
		t.value6 = 0;
		t.value7 = 10;
		t.value8 = 5;
		t.can_throw = true;
		t.image = &img_item_weapon_dagger;
		t.name.name = "대거";
		t.name.name_type = false; //true 받침있음
		t.weight = 2.0f;
		t.value = 50;
		break;
	case ITM_WEAPON_AXE:	
		t.value1 = 2;
		t.value2 = 8;
		t.value5 = 0;
		t.value6 = 0;
		t.value7 = 13;
		t.value8 = 7;
		t.can_throw = true;
		t.image = &img_item_weapon_handaxe;
		t.name.name = "손도끼";
		t.name.name_type = false; //true 받침있음
		t.weight = 3.0f;
		t.value = 60;
		break;
	case ITM_WEAPON_MACE:
		t.value1 = 4;
		t.value2 = 7;
		t.value5 = 0;
		t.value6 = 0;
		t.value7 = 13;
		t.value8 = 7;
		t.can_throw = false;
		t.image = randA(1)?&img_item_weapon_gohey:&img_item_weapon_gohey2;
		t.name.name = "고헤이";
		t.name.name_type = false; //true 받침있음
		t.weight = 3.0f;
		t.value = 60;
		break;
	case ITM_WEAPON_SPEAR:
		t.value1 = 2;
		t.value2 = 8;
		t.value5 = 12;
		t.value6 = 0;
		t.value7 = 13;
		t.value8 = 7;
		t.can_throw = true;
		t.image = &img_item_weapon_spear;
		t.name.name = "창";
		t.name.name_type = true; //true 받침있음
		t.weight = 4.0f;
		t.value = 70;
		break;
	}
	item *it;
	if(item_ != ITM_LAST)
	{
		it = env[current_level].MakeItem(you.position,t);
		it->identify = true;
		it->identify_curse = true;
		you.additem(it,false);
		you.equip('a',ET_WEAPON,false);
		env[current_level].DeleteItem(it);
	}


	t.type = ITM_ARMOR_BODY_ARMOUR_0;
	t.num = 1;
	t.curse = false;
	t.value1 = 1;
	t.value2 = 0;
	t.value3 = 0;
	t.value4 = (int)(bonus == 6);
	t.value5 = 0;
	t.value6 = 0;
	t.is_pile = false;
	t.can_throw = false;
	t.image = &img_item_armor_robe;
	t.name.name = "무녀복";
	t.name.name_type = true;
	t.weight = 6.0f;
	t.value = 40;

	it = env[current_level].MakeItem(you.position,t);
	it->identify = true;
	it->identify_curse = true;
	you.additem(it,false);
	you.equiparmor(item_ != ITMS_LAST?'b':'a',false);
	env[current_level].DeleteItem(it);

	t.type = ITM_FOOD;
	t.num = 1;
	t.curse = false;
	t.value1 = 1;
	t.value2 = 0;
	t.value3 = 0;
	t.value4 = 0;
	t.value5 = 100;
	t.value6 = 0;
	t.is_pile = true;
	t.can_throw = false;
	t.image = &img_item_food_bread;
	t.name.name = "빵";
	t.name.name_type = true;
	t.weight = 5.0f;
	t.value = 30;
	it = env[current_level].MakeItem(you.position,t);
	you.additem(it,false);
	env[current_level].DeleteItem(it);

	switch(bonus)
	{
	case 1:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, 1));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, 1));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, 3));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.potion_list[PT_HEAL].iden = true;
		iden_list.potion_list[PT_HEAL_WOUND].iden = true;
		break;
	case 2:		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_MIGHT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_MIGHT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.potion_list[PT_MIGHT].iden = true;
		break;
	case 3:		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_HASTE));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.potion_list[PT_HASTE].iden = true;
		break;
	case 4:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_TELEPORT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_TELEPORT));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_IDENTIFY));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		iden_list.scroll_list[SCT_TELEPORT].iden = 3;
		iden_list.scroll_list[SCT_IDENTIFY].iden = 3;
		break;
	case 5:	
		it = env[current_level].MakeItem(you.position,makeitem(ITM_THROW_TANMAC, 0, &t, 30));
		(*it).identify = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		break;	
	}


	skill_type s_type_ = (item_ != ITM_LAST)?itemtoskill(item_):SKT_UNWEAPON;


	you.GiveSkillExp(SKT_FIGHT,s_type_==SKT_SHORTBLADE?20:30,false);
	you.GiveSkillExp(s_type_,s_type_==SKT_UNWEAPON?80:s_type_==SKT_SHORTBLADE?30:45,false);
	if(bonus == 5)
		you.GiveSkillExp(SKT_TANMAC,70,false);
	you.GiveSkillExp(SKT_DODGE,50,false);
	if(s_type_==SKT_SHORTBLADE)
	{
		you.GiveSkillExp(SKT_STEALTH,30,false);
		//you.GiveSkillExp(SKT_BACKSTAB,30,false);
	}
}


extern void start_mainmenu();

void charter_selete()
{//인간,마법사,요정,카라스텐구,백랑텐구,캇파,반요,츠구모가미,흡혈귀,오니,사신, 달토끼, 천인, 용궁의사자, 유 령, 망령, 소령
	for(int i = 0; i<MAXLEVEL; i++)
		env[i].floor = i;
	

	WaitForSingleObject(mutx, INFINITE);
	SetText() = "touhou crawl ";
	SetText() += version_string;
	SetText() += "\n동방프로젝트와 던전크롤의 동인게임\n\n";
	if(load_name(user_name_file.c_str()))
	{
		SetText() += "당신의 이름은 \"";
		SetText() += you.user_name.name;
		SetText() += "\" 이다.\n";
	}
	else
	{
		SetText() += "당신의 이름은 \"";
		SetText() += you.user_name.name;
		SetText() += "\" 이다.\n";
		SetText() += "user_name.txt에서 당신의 이름을 바꿀 수 있어.\n";

	}
	SetDisplayTexture(&img_title);
	ReleaseMutex(mutx);
	waitkeyinput();	
	WaitForSingleObject(mutx, INFINITE);
	SetText() += "시작한다!\n";
	ReleaseMutex(mutx);
	Sleep(500);
	SetDisplayTexture(NULL);
	
	start_mainmenu();

	//bool main_= true;
	//while(main_)
	//{
	//	main_ =false;
	//	WaitForSingleObject(mutx, INFINITE);
	//	SetText() = "간단 메뉴.\n\n\n";
	//	SetText() += "a - 게임시작\n";
	//	SetText() += "b - 튜토리얼";
	//	ReleaseMutex(mutx);
	//	bool loop_= true;
	//	while(loop_)
	//	{
	//		int select = waitkeyinput(true);
	//		if(select>='a' && select<='b')
	//		{
	//			switch(select)
	//			{
	//			case 'a':
	//				tutorial = false;
	//				loop_ = false;
	//				break;
	//			case 'b':
	//				tutorial = true;
	//				loop_ = false;
	//				break;
	//			break;
	//			}
	//		}
	//	}

	//	if(!tutorial && !load_data(save_file.c_str()))
	//	{
	//		bool sub_main_ = true;
	//		while(sub_main_)
	//		{
	//			sub_main_ = false;
	//			bool touhouable_ = false;
	//			WaitForSingleObject(mutx, INFINITE);
	//			SetText() = "무슨 모드로 시작할거야?\n\n\n";

	//			SetText() += "a - 동방 캐릭터로 시작하기 (EASY)\n\n";
	//			SetText() += "b - 직접 캐릭터 생성하기 (NORMAL)\n\n";
	//			ReleaseMutex(mutx);
	//	
	//			while(1)
	//			{
	//				int select = waitkeyinput();
	//				if(select>='a' && select<='b')
	//				{
	//					WaitForSingleObject(mutx, INFINITE);
	//					if( select == 'a')
	//					{
	//						SetText() += "제일 좋은 것을 부탁해.\n";
	//						touhouable_ = true;
	//					}
	//					else if(select == 'b')
	//					{
	//						SetText() += "괜찮다. 문제없어.\n";
	//						touhouable_ = false;
	//					}
	//					else if(select == VK_ESCAPE)
	//					{
	//						ReleaseMutex(mutx);
	//						main_ = true;
	//						break;
	//					}

	//					ReleaseMutex(mutx);
	//					Sleep(300);
	//					break;
	//				}
	//			}
	//			if(main_)
	//				break;

	//			if(touhouable_)
	//			{
	//				WaitForSingleObject(mutx, INFINITE);
	//				SetText() = "캐릭터를 선택합니다.\n\n\n\n";
	//				SetText() += "a - 인간 무녀 레이무\n\n";
	//				SetText() += " 안티패턴 초 유도형. 비겁한 호밍무녀로 모든 적을 섬멸하자!\n";
	//				SetText() += " 적성보너스) 탄막적성 +3, 회피적성 +3\n";
	//				SetText() += " 보너스) 리본, 24개의 호밍아뮬렛, 신은 믿고 시작하지않는다.\n\n\n";
	//				SetText() += "b - 인간 마법사 마리사\n\n";
	//				SetText() += " : 무한관통 & 상시공격형. 탄막은 파워! 보이자마자 죽이자!\n";
	//				SetText() += " 적성보너스) 주문시전적성 +2, 파괴마법적성 +3, 회피적성 +1\n";
	//				SetText() += " 보너스) +2,+2 빗자루, 영력의 반지, 파괴의 마법책\n\n\n";
	//				SetText() += "c - 인간 무녀 사나에\n\n";
	//				SetText() += " : 고위력 & 광범위 작렬형. 스와코님의 말씀대로!\n";
	//				SetText() += " 적성보너스) 전투적성 +2, 회피적성 +1, 발동적성 +3\n";
	//				SetText() += " 보너스)  대지의 스펠카드(9), 대기의 스펠카드(9), 스와코를 믿고 시작한다.\n\n\n";
	//				SetText() += "d - 백랑텐구 전사 모미지\n\n";
	//				SetText() += " : 자동탐색 & 자동공격형. O와 TAB이 당신을 지켜줄지어니\n";
	//				SetText() += " 적성보너스) 장검적성 +1\n";
	//				SetText() += " 보너스) +2,+2 언월도, +2 철방패, +2 중간 중갑옷, 상처치료물약 2개, 힘물약 2개, 투명감지 반지\n\n\n";

	//				ReleaseMutex(mutx);
	//		
	//				while(1)
	//				{
	//					int select = waitkeyinput();
	//					if(select>='a' && select<='d')
	//					{
	//						switch( select )
	//						{
	//						case 'a':						
	//						default:
	//							you.tribe = TRI_HUMAN;
	//							you.job = JOB_SHAMAN;
	//							you.char_name.name = "레이무";
	//							you.char_name.name_type = false;
	//							you.image = &img_play_reimu;
	//							break;
	//						case 'b':
	//							you.tribe = TRI_HUMAN;
	//							you.job = JOB_WIZARD;
	//							you.char_name.name = "마리사";
	//							you.char_name.name_type = false;
	//							you.image = &img_play_marisa;
	//							break;
	//						case 'c':
	//							you.tribe = TRI_HUMAN;
	//							you.job = JOB_SHAMAN;
	//							you.char_name.name = "사나에";
	//							you.char_name.name_type = false;
	//							you.image = &img_play_sanae;
	//							break;
	//						case 'd':
	//							you.tribe = TRI_WOLFTENGU;
	//							you.job = JOB_WARRIOR;
	//							you.char_name.name = "모미지";
	//							you.char_name.name_type = false;
	//							you.image = &img_play_momizi;
	//							break;
	//						}						
	//						WaitForSingleObject(mutx, INFINITE);
	//						SetText() += "Kill Them All!\n";
	//						ReleaseMutex(mutx);
	//						Sleep(300);
	//						break;
	//					}
	//				}
	//			}
	//			else
	//			{		
	//				WaitForSingleObject(mutx, INFINITE);
	//				SetText() = "종족을 선택합니다.\n\n\n";
	//				for(int i=0;i<TRI_MAX;i++)
	//				{
	//					char temp[64];
	//					sprintf_s(temp,"%c - %s",'a'+i,tribe_type_string[i]);
	//					int remain_num_ = 23-strlen(temp);
	//					SetText() += temp;
	//					if(i%2 ==0)
	//					{
	//						for(int j=0;j<remain_num_;j++)
	//							SetText() += " ";
	//					}
	//					if(i%2 == 1 || i == TRI_MAX-1)
	//					{
	//						SetText() += "\n";
	//					}
	//				}
	//				ReleaseMutex(mutx);
	//				while(1)
	//				{
	//					int select = waitkeyinput();
	//					if(select>='a' && select<'a'+TRI_MAX)
	//					{
	//						you.tribe = (tribe_type)(select - 'a');
	//						WaitForSingleObject(mutx, INFINITE);
	//						SetText() += "그런 종족으로 괜찮은가?\n";
	//						ReleaseMutex(mutx);
	//						Sleep(300);
	//						break;
	//					}
	//				}
	//				WaitForSingleObject(mutx, INFINITE);
	//				SetText() = "직업을 선택합니다.\n\n\n";
	//				for(int i=0;i<JOB_MAX;i++)
	//				{
	//					char temp[64];
	//					sprintf_s(temp,"%c - %s",'a'+i,job_type_string[i]);
	//					int remain_num_ = 23-strlen(temp);
	//					SetText() += temp;
	//					if(i%2 ==0)
	//					{
	//						for(int j=0;j<remain_num_;j++)
	//							SetText() += " ";
	//					}			
	//					if(i%2 == 1 || i == JOB_MAX-1)
	//					{
	//						SetText() += "\n";
	//					}
	//				}
	//				ReleaseMutex(mutx);
	//				while(1)
	//				{
	//					int select = waitkeyinput();
	//					if(select>='a' && select<'a'+JOB_MAX)
	//					{
	//						you.job = (job_type)(select - 'a');
	//						WaitForSingleObject(mutx, INFINITE);
	//						SetText() += "좋은 선택이다.\n";
	//						ReleaseMutex(mutx);
	//						Sleep(300);
	//						break;
	//					}
	//				}



	//				you.image = &img_play_normal;
	//				you.char_name.name = "";
	//				//you.SetXY(DG_MAX_X/2, DG_MAX_Y/2);


	//			}
	//		}
	//		if(main_)
	//			continue;


	//if(isTutorial())
	//{
	//	//you.image = &img_play_sanae;
	//	//you.char_name.name = "사나에";
	//	//you.tribe = TRI_HUMAN;
	//	//you.job = JOB_SHAMAN;
	//	//SetTribe(you.tribe);
	//	//you.CalcuHP();
	//	//env[current_level].EnterMap(0,deque<monster*>());	
	//	//printlog("카나코는 말했다 : 환영한다, 사나에! 이번 튜토리얼은 내가 담당하지.",true,false,false,CL_warning);
	//	//printlog("카나코는 말했다 : 지나간 말은 컨트롤+P로 로그를 확인하고 궁금한건 ?를 눌러.",true,false,false,CL_warning);
	//	//printlog("카나코는 말했다 : 일단 h j k l나 방향키로 움직일 수 있어. 대소문자에 조심해.",true,false,false,CL_warning);
	//	////you.resetLOS(false);
	//}
	if(isNormalGame() && !saveexit)
	{
		char temp[200];
		sprintf_s(temp,200,"%s, %s %s %s. 던전의 탐험을 시작했다.", you.user_name.name.c_str(),tribe_type_string[you.tribe],job_type_string[you.job],you.GetCharNameString()->c_str());
		AddNote(you.turn,CurrentLevelString(),temp,CL_normal);

		SetTribe(you.tribe);
		TouhouPlayerble(you.char_name.name, true);
		SetJob(you.job,you.char_name.name);
		TouhouPlayerble(you.char_name.name, false);
		/*Test_char_init(item_, bonus);*/
		you.CalcuHP();
		Initialize();
	}
	changedisplay(DT_GAME);
	saveexit = true;
}


void Initialize()
{
	env[current_level].EnterMap(0,deque<monster*>());

	printlog("환상향에 온걸 환영한다!",true,false,false,CL_normal);
	//you.resetLOS(false);

}



void MainLoop()
{
	int a=0,b=0;
	while(1)
	{
		you.player_move = true;

		if(you.s_timestep)
		{
			turn_skip();
			Sleep(16);
			continue;
		}

		switch(waitkeyinput())
		{
		case 'j':
			Move(coord_def(you.position.x,you.position.y-1));  //위
			break;
		case 'k':
			Move(coord_def(you.position.x,you.position.y+1)); //아래
			break;
		case 'h':
			Move(coord_def(you.position.x-1,you.position.y)); //왼쪽
			break;
		case 'l':
			Move(coord_def(you.position.x+1,you.position.y)); //오른쪽
			break;
		case 'b':
			Move(coord_def(you.position.x-1,you.position.y+1));
			break;
		case 'n':
			Move(coord_def(you.position.x+1,you.position.y+1));
			break;
		case 'y':
			Move(coord_def(you.position.x-1,you.position.y-1));
			break;
		case 'u':
			Move(coord_def(you.position.x+1,you.position.y-1));
			break;
		case 'x': //주위탐색
			Search();
			break;
		case 's': //턴스킵
		case '.': //턴스킵
			turn_skip();
			break;
		case 'g':
		case ',': //줍기
			PickUp();
			break;
		case 'i': //아이템확인
			iteminfor();
			break;	
		case 'd': //아이템버리기
			iteminfor_discard();
			break;
		case 'D': //마지막에 먹은 아이템 버리기
			fast_discard();
			break;
		case 'w': //무기장착
			Equip_Weapon();
			break;
		case 'W': //방어구장착
			Equip_Armor();
			break;
		case 'T': //방어구해제
			Unequip_Armor();
			break;
		case 'C': //문닫기
			Close_door();
			break;
		case 'O': //문열기
			Open_door();
			break;
		case 'o': //자동이동
			auto_Move();
			break;
		case '5': //100턴넘기기
			long_rest();
			break;
		case 0x88: //컨트롤P - 로그
			view_log();
			break;
		case 'e': //먹기
			Eatting();
			break;
		case 'q': //마시기
			Drinking();
			break;
		case 'r': //읽기
			Reading();
			break;
		case 'm': //스킬정보창
			skill_view();
			break;
		case 'P': //장신구장착
			Equip_Jewelry();
			break;
		case 'R': //장신구해제
			Unequip_Jewelry();
			break;
		case 'S': //체크후 종료
			saveandcheckexit();
			break;
		case 0x89: //강제종료
			nosaveandexit();
			break;
		case 0x8A: //저장과 종료
			saveandexit();
			break;
		case 'X': //넓은탐색
			Wide_Search();
			break;
		case 'f': //던지기(빠른)
			Quick_Throw(you.GetThrowIter(),you.GetTargetIter());
			break;
		case 'F': //던지기(선택)
			Select_Throw();
			break;
		case '\\': //식별템 확인
			Iden_Show();
			break;
		case '>':
			Stair_move(true);
			break;
		case '<':
			Stair_move(false);
			break;
		case '%':
			stat_view();
			break;
		case '}':
			Weapon_Show();
			break;
		case '[':
			Armour_Show();
			break;
		case '\"':
			Amulet_Show();
			break;
		case '@':
			Simple_State_Show();
			break;
		case 'N':
			//sendScore();
			break;
		case 'E':
			Experience_Show();
			break;
		//case 'c':
		//	Spelllcard_Declare();
		//	//Eat_Power();
		//	break;
		case 'v':
		case 'V':
			Spelllcard_Evoke();
			break;
		case 'p':
			Pray();
			break;
		case '#':
			if(isNormalGame() && Dump(0))
				printlog("덤프에 성공했습니다.",true,false,false,CL_normal);
			break;
		case 'Z':
		case 'z':
			SpellUse();
			break;
		case 'I':
			SpellView();
			break;
		case 'a':
			SkillUse();
			break;
		case 'A':
			PropertyView();
			break;
		case 'M':
			run_spell();
			break;
		case 't':
			shout();
			break;
		case '^':
			God_show();
			break;
		case '&': //위자드모드!
			//waitkeyinput();
			wiz_mode();
			break;
		case '_':
			save_mode();
			break;
		case 0x8B:
			auto_pick_onoff(false);
			break;
		case '?'://도움말
			Help_Show();
			break;
		case VK_ESCAPE://esc
			escape();
			break;
		case VK_TAB:
			auto_battle();
			break;
		}
	}
}