//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: wiz.cpp
//
// 내용: 위자드모드!!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "smoke.h"
#include "key.h"
#include "mon_infor.h"

#include "spellcard.h"
#include "skill_use.h"
#include "weapon.h"
#include "map.h"
#include "evoke.h"
#include "god.h"
#include "tribe.h"


extern HANDLE mutx;
wiz_infor wiz_list;


bool skill_summon_bug(int pow, bool short_, unit* order, coord_def target);

void wiz_mode()
{

	if(wiz_list.wizard_mode != 1)
	{

		
		printlog("#### 경고! 위자드모드는 점수등록이 안되며 재미를 큰폭으로 떨어뜨립니다. ### ",true,false,false,CL_danger);
		printlog("진짜로 킬꺼야? (Y/N) ",false,false,false,CL_danger);

		
		int key_ = waitkeyinput();
		switch(key_)
		{
		case 'Y':
			enterlog();
			break;
		default:
			printlog("위자드모드를 취소",true,false,false,CL_help);
			return;
		}

	}



	printlog("<위자드모드> 어느 명령어?  ( ? - 도움말 )",true,false,false,CL_help);
	wiz_list.wizard_mode = 1;
	while(1)
	{
		int key_ = waitkeyinput();
	
		changedisplay(DT_GAME);
		switch (key_)
		{
		case 'D': //맵밝히기
			for (int i = 0; i < DG_MAX_X; i++)
				for (int j = 0; j < DG_MAX_Y; j++)
					env[current_level].magicmapping(i, j);
			break;
		case 'f': //연기
			//for(int i = -1;i<2;i++)
			//	for(int j = -1;j<2;j++)
			//		env[current_level].MakeSmoke(coord_def(i+you.position.x,j+you.position.y),img_fog_fire,SMT_NORMAL,10,0,&you);
			MakeCloud(you.position, img_fog_thunder, SMT_ELEC, rand_int(8, 10), rand_int(80, 120), 0, 5, &you);
			break;
		case 'A':
		{
			printlog("p-포션 s-스크롤 e-발동템 v-스펠카드 r-반지 b-책 a-방어구 R-목걸이", true, false, false, CL_help);
			printlog("어느 아이템을 얻어볼까?", false, false, false, CL_help);
			key_ = waitkeyinput();
			switch (key_)
			{
			case 'p':
			{
				int list[] = { PT_WATER,	PT_HEAL, PT_POISON,	PT_HEAL_WOUND, PT_MIGHT, PT_HASTE, PT_CONFUSE,
					PT_SLOW, PT_PARALYSIS, PT_CLEVER, PT_AGILITY, PT_MAGIC, PT_LEVETATION, PT_POWER,
					PT_DOWN_STAT, PT_RECOVER_STAT, PT_ALCOHOL };
				enterlog();
				printlog("a-물 b-치유 c-독 d-체력회복 e-힘 f-가속 g-혼란 h-감속 i-마비", true, false, false, CL_help);
				printlog("j-지능 k-민첩 l-영력 m-비행 n-파워 o-능력치감소 p-능력치회복 q-술", true, false, false, CL_help);
				printlog("어느 포션을 얻어볼까?", false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 'q')
				{
					for (int i = 0; i < 10; i++)
					{
						item_infor t;
						makeitem(ITM_POTION, 0, &t, list[key_ - 'a']);
						env[current_level].MakeItem(you.position, t);
						enterlog();
					}
				}
				else {
					printlog(" 취소", true, false, false, CL_help);
				}
			}
			return;
			case 's':
			{
				int list[] = { SCT_TELEPORT,SCT_IDENTIFY,SCT_NONE,SCT_CURSE_WEAPON,SCT_CURSE_ARMOUR,SCT_REMOVE_CURSE,
					SCT_BLINK,SCT_MAPPING,SCT_ENCHANT_WEAPON_1,	SCT_ENCHANT_ARMOUR,SCT_FOG,SCT_DETECT_CURSE,
					SCT_CURSE_JEWELRY,SCT_SILENCE,SCT_SOUL_SHOT,SCT_CHARGING,SCT_AMNESIA };
				enterlog();
				printlog("a-텔포 b-식별 c-낙서 d-무기저주 e-방어구저주 f-저주해제 g-순간이동 h-마법지도", true, false, false, CL_help);
				printlog("i-무기강화 j-방어구강화 k-연기 l-저주감지 m-장신구저주 n-정적 o-영격 p-스펠충전", true, false, false, CL_help);
				printlog("q-망각", true, false, false, CL_help);
				printlog("어느 스크롤을 얻어볼까?", false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 'q')
				{
					for (int i = 0; i < 10; i++)
					{
						item_infor t;
						makeitem(ITM_SCROLL, 0, &t, list[key_ - 'a']);
						env[current_level].MakeItem(you.position, t);
						enterlog();
					}
				}
				else {
					printlog(" 취소", true, false, false, CL_help);
				}
			}
			return;
			case 'e':
			{
				int list[] = { EVK_PAGODA,EVK_AIR_SCROLL,EVK_DREAM_SOUL };
				enterlog();
				printlog("a-보탑 b-에어두루마리 c-몽혼", true, false, false, CL_help);
				printlog("어느 발동템을 얻어볼까?", false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 'c')
				{
					item_infor t;
					makeitem(ITM_MISCELLANEOUS, 0, &t, list[key_ - 'a']);
					env[current_level].MakeItem(you.position, t);
					enterlog();
				}
				else {
					printlog(" 취소", true, false, false, CL_help);
				}
			}
			return;
			case 'v':
			{
				int list[] = { SPC_V_FIRE,SPC_V_ICE,SPC_V_EARTH,SPC_V_AIR,SPC_V_INVISIBLE };
				enterlog();
				printlog("a-화염 b-냉기 c-대지 d-대기 e-투명", true, false, false, CL_help);
				printlog("어느 스펠카드를 얻어볼까?", false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 'e')
				{
					item_infor t;
					makeitem(ITM_SPELL, 0, &t, list[key_ - 'a']);
					env[current_level].MakeItem(you.position, t);
					enterlog();
				}
				else {
					printlog(" 취소", true, false, false, CL_help);
				}
			}
			return;
			case 'r':
			{
				int list[] = { RGT_STR,RGT_DEX,RGT_INT,RGT_HUNGRY,RGT_FULL,RGT_TELEPORT,RGT_POISON_RESIS,
					RGT_FIRE_RESIS,	RGT_ICE_RESIS,RGT_SEE_INVISIBLE/*,RGT_GRAZE*/,RGT_LEVITATION,RGT_INVISIBLE,
					RGT_MANA,RGT_MAGACIAN,RGT_AC,RGT_EV,RGT_CONFUSE_RESIS,	RGT_ELEC_RESIS,RGT_MAGIC_RESIS };
				enterlog();
				printlog("a-힘 b-민첩 c-지능 d-허기 e-만복도 f-공간이동 g-독저항 h-화염저항", true, false, false, CL_help);
				printlog("i-냉기저항 j-투명보기 k-비행 l-투명 m-영력 n-마법사 o-방어", true, false, false, CL_help);
				printlog("p-회피 q-혼란저항 r-전기저항 s-마법저항 !-아티펙트", true, false, false, CL_help);
				printlog("어느 반지를 얻어볼까?", false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 's')
				{
					item_infor t;
					makeitem(ITM_RING, 0, &t, list[key_ - 'a']);
					env[current_level].MakeItem(you.position, t);
					enterlog();
				}
				else if (key_ == '!')
				{
					item_infor t;
					makeitem(ITM_RING, randA(9) ? 1 : -1, &t);
					t.artifact = true;
					item *it_ = env[current_level].MakeItem(you.position, t);
					MakeArtifact(it_, it_->curse ? -1 : 1);
					enterlog();

				}
				else {
					printlog(" 취소", true, false, false, CL_help);
				}
			}
			return;
			case 'b':
			{
				item_infor t;
				makeitem(ITM_BOOK, 0, &t, -1);
				env[current_level].MakeItem(you.position, t);
			}
			return;
			case 'a':
			{
				item_infor t;
				item_type atype_ = (item_type)rand_int(ITM_ARMOR_BODY_FIRST, ITM_ARMOR_BODY_LAST - 1);
				if (randA(1) == 0)
					atype_ = (item_type)rand_int(ITM_ARMOR_HEAD, ITM_ARMOR_BOOT);
				makeitem(atype_, randA(2) ? 0 : (randA(3) ? 1 : -1), &t);
				if (randA(1))
					t.artifact = true;
				item *it_ = env[current_level].MakeItem(you.position, t);
				if (t.artifact)
					MakeArtifact(it_, it_->curse ? -1 : 1);
			}
			return;
			case 'R':
			{
				int list[] = { AMT_PERFECT, AMT_BLOSSOM, AMT_TIMES, AMT_FAITH, AMT_WAVE, AMT_SPIRIT, AMT_GRAZE,
					AMT_WEATHER, AMT_POPULAR, AMT_OCCULT };
				enterlog();
				printlog("a-완전무결 b-삼라결계 c-각부 d-신앙 e-전파 f-신령 g-그레이즈 h-기질", true, false, false, CL_help);
				printlog("i-인기 j-오컬트", true, false, false, CL_help);
				printlog("어느 부적을 얻어볼까?", false, false, false, CL_help);
				key_ = waitkeyinput();
				if (key_ >= 'a' && key_ <= 'j')
				{
					item_infor t;
					makeitem(ITM_AMULET, 0, &t, list[key_ - 'a']);
					env[current_level].MakeItem(you.position, t);
					enterlog();
				}
				else {
					printlog(" 취소", true, false, false, CL_help);
				}
			}
			return;
			default:
				printlog(" 취소", true, false, false, CL_help);
				return;
			}

		}
		case 'H':
			you.HpUpDown(you.max_hp, DR_EFFECT);
			you.MpUpDown(you.max_mp);
			you.PowUpDown(500, true);
			break;
		case 'g':
			printlog("용의 마지막 특성이 발현되었다. 당신은 공기의 흐름을 다룰 수 있게 되었다.", true, false, false, CL_small_danger);
			you.SetProperty(TPT_GRAZE_CONTROL, 1);
			break;
		case 'P':
			you.system_exp.value = 0;
			if (you.system_exp.value <= 0) {
				you.system_exp.value = 0;
				item* _item = you.equipment[ET_NECK];
				if (_item && _item->type == ITM_AMULET) {
					chargingFinish((amulet_type)_item->value1, 1);
					if (you.system_exp.value <= 0) {
						if (isCanCharge((amulet_type)_item->value1)) {
							printlog("부적의 힘이 모두 채워졌다! 이제 원할때 v로 발동할 수 있다.", true, false, false, CL_white_puple);
						}
						else {
							printlog("부적의 힘이 모두 채워졌다!", true, false, false, CL_white_puple);
						}
					}
				}
			}
			break;
		case 'X':
			you.GetExp(you.GetNeedExp(you.level - 1) - you.exper);
			break;
		case '>': //다음층 이동
			if (!environment::isLastFloor(current_level))
			{
				deque<monster*> dq;
				env[current_level + 1].EnterMap(0, dq);
				//you.resetLOS(false);
			}
			break;
		case '<': //이전층 이동	
			if (!environment::isFirstFloor(current_level))
			{
				deque<monster*> dq;
				env[current_level - 1].EnterMap(0, dq);
				//you.resetLOS(false);
			}
			break;
		case 'G': //던전이동	
		{
			deque<monster*> dq;
			dungeon_level next_ = TEMPLE_LEVEL;
			printlog("d - 던전     t - 신전      l - 안개의 호수     m - 요괴의 산     s - 홍마관", true, false, false, CL_help);
			printlog("b - 홍마관도서관   u - 홍마관지하   a - 미궁의죽림  e - 영원정   y - 윳쿠리둥지 ", true, false, false, CL_help);
			printlog("p - 짐승길  h - 지령전  r - 꿈의 세계 o - 달의 세계  k - 마계  z - 하쿠레이신사", true, false, false, CL_help);
			printlog("어느 던전으로 이동해볼까? (대문자로 마지막층)", false, false, false, CL_help);
			key_ = waitkeyinput();
			switch (key_)
			{
			case 'd':
				next_ = (dungeon_level)0;
				break;
			case 'D':
				next_ = MAX_DUNGEUN_LEVEL;
				break;
			case 't':
			case 'T':
				next_ = TEMPLE_LEVEL;
				break;
			case 'l':
				next_ = MISTY_LAKE_LEVEL;
				break;
			case 'L':
				next_ = MISTY_LAKE_LAST_LEVEL;
				break;
			case 'm':
				next_ = YOUKAI_MOUNTAIN_LEVEL;
				break;
			case 'M':
				next_ = YOUKAI_MOUNTAIN_LAST_LEVEL;
				break;
			case 's':
				next_ = SCARLET_LEVEL;
				break;
			case 'S':
				next_ = SCARLET_LEVEL_LAST_LEVEL;
				break;
			case 'b':
			case 'B':
				next_ = SCARLET_LIBRARY_LEVEL;
				break;
			case 'u':
			case 'U':
				next_ = SCARLET_UNDER_LEVEL;
				break;
			case 'a':
			case 'A':
				next_ = BAMBOO_LEVEL;
				break;
			case 'e':
			case 'E':
				next_ = EIENTEI_LEVEL;
				break;
			case 'h':
				next_ = SUBTERRANEAN_LEVEL;
				break;
			case 'H':
				next_ = SUBTERRANEAN_LEVEL_LAST_LEVEL;
				break;
			case 'y':
				next_ = YUKKURI_LEVEL;
				break;
			case 'Y':
				next_ = YUKKURI_LAST_LEVEL;
				break;
			case 'p':
				next_ = DEPTH_LEVEL;
				break;
			case 'P':
				next_ = DEPTH_LAST_LEVEL;
				break;
			case 'r':
			case 'R':
				next_ = DREAM_LEVEL;
				break;
			case 'o':
			case 'O':
				next_ = MOON_LEVEL;
				break;
			case 'k':
			case 'K':
				next_ = PANDEMONIUM_LEVEL;
				break;
			case 'z':
				next_ = HAKUREI_LEVEL;
				break;
			case 'Z':
				next_ = HAKUREI_LAST_LEVEL;
				break;
			default:
				printlog(" 취소", true, false, false, CL_help);
				return;
			}
			enterlog();
			env[next_].EnterMap(0, dq);
			printlog("계단을 내려왔다.", true, false, false, CL_normal);
			//you.resetLOS(false);
			break;
		}
		case 'b':
			you.Blink(40);
			break;
		case 's':
			//skill_summon_bug(10,false,&you,you.position);		
			if (you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact())
			{
				you.equipment[ET_WEAPON]->value5 = WB_CURSE;
				you.equipment[ET_WEAPON]->value6 = -1;
			}
			else
			{
				printlog("마법이 듣지 않는다.", true, false, false, CL_normal);
			}
			break;
		case 'w':
			//skill_summon_bug(100,&you,you.position);		
			you.SetBuff((stat_up)rand_int(BUFFSTAT_STR, BUFFSTAT_EV), BUFF_DUPLE, rand_int(-3, 3), 10);
			break;
		case 'p':
		{
			dungeon_tile_type next_ = DG_TEMPLE_FIRST;
			printlog("B - 뱌쿠렌     K - 카나코  W - 스와코   A - 미노리코", true, false, false, CL_help);
			printlog("M - 미마       P - 신키    G - 유우기   Z - 시즈하  H - 히나     Y - 유카리 ", true, false, false, CL_help);
			printlog("E - 에이린     U - 유유코  S - 사토리   T - 텐시    J - 세이자   L - 릴리", true, false, false, CL_help);
			printlog("어떤 신전을 만들까?", false, false, false, CL_help);
			wiz_list.wizard_mode = true;
			key_ = waitkeyinput();
			switch (key_)
			{
				//case 'x':
				//case 'X':
				//	next_ = DG_TEMPLE_SHIKIEIKI;
				//	break;
			case 'b':
			case 'B':
				next_ = DG_TEMPLE_BYAKUREN;
				break;
			case 'k':
			case 'K':
				next_ = DG_TEMPLE_KANAKO;
				break;
			case 'w':
			case 'W':
				next_ = DG_TEMPLE_SUWAKO;
				break;
			case 'a':
			case 'A':
				next_ = DG_TEMPLE_MINORIKO;
				break;
			case 'm':
			case 'M':
				next_ = DG_TEMPLE_MIMA;
				break;
			case 'p':
			case 'P':
				next_ = DG_TEMPLE_SHINKI;
				break;
			case 'g':
			case 'G':
				next_ = DG_TEMPLE_YUUGI;
				break;
			case 'z':
			case 'Z':
				next_ = DG_TEMPLE_SHIZUHA;
				break;
			case 'h':
			case 'H':
				next_ = DG_TEMPLE_HINA;
				break;
			case 'y':
			case 'Y':
				next_ = DG_TEMPLE_YUKARI;
				break;
			case 'e':
			case 'E':
				next_ = DG_TEMPLE_EIRIN;
				break;
			case 'u':
			case 'U':
				next_ = DG_TEMPLE_YUYUKO;
				break;
			case 's':
			case 'S':
				next_ = DG_TEMPLE_SATORI;
				break;
			case 't':
			case 'T':
				next_ = DG_TEMPLE_TENSI;
				break;
			case 'j':
			case 'J':
				next_ = DG_TEMPLE_SEIJA;
				break;
			case 'L':
			case 'l':
				next_ = DG_TEMPLE_LILLY;
				break;
			default:
				printlog(" 취소", true, false, false, CL_help);
				return;
			}
			enterlog();
			env[current_level].dgtile[you.position.x][you.position.y].tile = next_;
		}
		break;
		case 'W':
			if (you.s_the_world)
			{
				you.s_the_world = 0;
			}
			else
			{
				you.s_the_world = -1;
			}
			break;
		case '!':
		{
			you.Memorize(SPL_DISCHARGE, true);
		}
		break;
		/*case 'M':
			if(monster* mon_=BaseSummon(MON_LUNAR, 100, false, false, 2, &you, you.position, SKD_OTHER, -1))
			{
				mon_->state.SetState(MS_SLEEP);
				mon_->flag &= ~M_FLAG_SUMMON;
				mon_->ReturnEnemy();
			}
			if(monster* mon_=BaseSummon(MON_STAR, 100, false, false, 2, &you, you.position, SKD_OTHER, -1))
			{
				mon_->state.SetState(MS_SLEEP);
				mon_->flag &= ~M_FLAG_SUMMON;
				mon_->ReturnEnemy();
			}
			if(monster* mon_=BaseSummon(MON_SUNNY, 100, false, false, 2, &you, you.position, SKD_OTHER, -1))
			{
				mon_->state.SetState(MS_SLEEP);
				mon_->flag &= ~M_FLAG_SUMMON;
				mon_->ReturnEnemy();
			}
			break;*/
		case 'm': 
			{
				  key_ = waitkeyinput();

				 
				  if (monster* mon_ = BaseSummon(key_ == 'z' ? MON_KOISHI :MON_MURASA+ key_ - 'a', 100, false, false, 2, &you, you.position, SKD_OTHER, -1))
				  {
					  mon_->state.SetState(MS_SLEEP);
					  mon_->flag &= ~M_FLAG_SUMMON;
					  mon_->hp = 10;
					  mon_->ReturnEnemy();
				  }
			}
			break;
		case '^':
			if(you.god != GT_SEIJA)
				you.PietyUpDown(10);
			you.GiftCount(10);
			break;
		case 'o':
			you.hp = 1;
			break;
		case 'C':
			{
				for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
				{
					if(it->isLive())
						it->dead(PRT_PLAYER,false);
				}
				for(list<item>::iterator it = env[current_level].item_list.begin(); it != env[current_level].item_list.end(); it++)
				{
					it->position = you.position;
				}
			}
			break;
		case 'E':
			{
				int prevexp_=0, exp_ = 0;
				for(int i = 0; i <= map_list.dungeon_enter[MISTY_LAKE].floor; i++)
				{
					env[i].MakeMap(true);				
					for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
					{
						if(it->isLive())
							it->dead(PRT_PLAYER,false);
					}
				}
				exp_ = you.exper;
				char temp[200];
				sprintf_s(temp,200,"일반던전 %d층까지 레벨:%d (경험치양 %d)",map_list.dungeon_enter[MISTY_LAKE].floor+1, you.level,exp_-prevexp_);
				printlog(temp,true,false,false,CL_normal);
				prevexp_ = exp_;
				 
				for(int i = MISTY_LAKE_LEVEL; i <= MISTY_LAKE_LAST_LEVEL; i++)
				{
					env[i].MakeMap(true);				
					for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
					{
						if(it->isLive())
							it->dead(PRT_PLAYER,false);
					}
				}
				exp_ = you.exper;
				sprintf_s(temp,200,"안개호수클리어 레벨:%d (경험치양 %d)", you.level,exp_-prevexp_);
				printlog(temp,true,false,false,CL_normal);
				prevexp_ = exp_;


				for(int i = map_list.dungeon_enter[MISTY_LAKE].floor+1; i <= MAX_DUNGEUN_LEVEL; i++)
				{
					env[i].MakeMap(true);				
					for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
					{
						if(it->isLive())
							it->dead(PRT_PLAYER,false);
					}
				}
				exp_ = you.exper;
				sprintf_s(temp,200,"남은던전 클리어 레벨:%d (경험치양 %d)", you.level,exp_-prevexp_);
				printlog(temp,true,false,false,CL_normal);
				prevexp_ = exp_;


				for(int i = YOUKAI_MOUNTAIN_LEVEL; i <= YOUKAI_MOUNTAIN_LAST_LEVEL; i++)
				{
					env[i].MakeMap(true);				
					for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
					{
						if(it->isLive())
							it->dead(PRT_PLAYER,false);
					}
				}
				exp_ = you.exper;
				sprintf_s(temp,200,"요괴의산 클리어 레벨:%d (경험치양 %d)", you.level,exp_-prevexp_);
				printlog(temp,true,false,false,CL_normal);
				prevexp_ = exp_;

				for(int i = SCARLET_LEVEL; i <= SCARLET_LEVEL_LAST_LEVEL; i++)
				{
					env[i].MakeMap(true);				
					for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
					{
						if(it->isLive())
							it->dead(PRT_PLAYER,false);
					}
				}
				exp_ = you.exper;
				sprintf_s(temp,200,"홍마관 클리어 레벨:%d (경험치양 %d)", you.level,exp_-prevexp_);
				printlog(temp,true,false,false,CL_normal);
				prevexp_ = exp_;
			}
			break;
		case 'B':
			god_punish(you.god);
			break;
		case '?'://도움말

			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			printsub("                             --- 위자드모드 커맨드 목록 ---",true,CL_normal);
			printsub("",true,CL_normal);
			printsub(" X      - 1레벨업                         ",true,CL_normal);
			printsub(" H      - 체력 영력 파워 회복             ",true,CL_normal);
			printsub(" G      - 장소이동                        ",true,CL_normal);
			printsub(" p      - 제단 생성                       ",true,CL_normal);
			printsub(" ^      - 신앙심 10증가                   ",true,CL_normal);
			printsub(" >      - 아랫층으로 내려가기             ",true,CL_normal);
			printsub(" <      - 윗층으로 올라가기               ",true,CL_normal);
			printsub(" A      - 아이템생성(베타)                ",true,CL_normal);
			printsub(" W      - 시간정지                        ",true,CL_normal);
			printsub(" D      - 매직맵핑                        ",true,CL_normal);
			printsub(" b      - 블링크                          ",true,CL_normal);
			printsub("                                         ",true,CL_normal);
			printsub(" 이외의 커맨드는 불안정하니 비추천        ",true,CL_normal);
			changedisplay(DT_SUB_TEXT);
			ReleaseMutex(mutx);
			continue;
		default:
			printlog("없는 명령어",true,false,false,CL_help);
			break;
		}
	return;
	}
}


void save_mode()
{
	
	if(wiz_list.wizard_mode == 0)
	{

		
		printlog("#### 경고! 이 모드는 온라인점수등록이 안됩니다! 치트로 취급됩니다! ### ",true,false,false,CL_danger);
		printlog("#### 세이브는 층이동시, 수동저장시에 저장됩니다. ### ",true,false,false,CL_danger);
		printlog("진짜로 킬꺼야? (Y/N) ",false,false,false,CL_danger);
			
		int key_ = waitkeyinput();
		switch(key_)
		{
		case 'Y':
			enterlog();
			break;
		default:
			printlog("세이브보존모드를 취소",true,false,false,CL_help);
			return;
		}


		wiz_list.wizard_mode = 2;
	}
	else if(wiz_list.wizard_mode == 1)
	{		
		printlog("위자드모드에서 세이브보존모드로 이동하더라도 점수등록은 되지않습니다.",true,false,false,CL_danger);
		printlog("바꿀꺼야? (Y/N) ",false,false,false,CL_danger);


		int key_ = waitkeyinput();
		switch(key_)
		{
		case 'Y':
			enterlog();
			break;
		default:
			printlog("취소",true,false,false,CL_help);
			return;
		}

		wiz_list.wizard_mode = 2;
	}
	else  if(wiz_list.wizard_mode == 2)
	{	
		printlog("이미 당신은 세이브보존모드다. 이 모드에선 세이브파일이 삭제되지않는다. ",true,false,false,CL_normal);
	}

	return;

}