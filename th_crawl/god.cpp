//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: god.cpp
//
// 내용: 신관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"
#include "god.h"
#include "key.h"
#include "skill_use.h"
#include "mon_infor.h"
#include "potion.h"
#include "rect.h"
#include "floor.h"
#include "tensi.h"
#include "swako.h"
#include "note.h"
#include "rand_shuffle.h"


extern HANDLE mutx;

const char* GetGodString(god_type god)
{
	switch(god)
	{
	case GT_ERROR:
		return "알수없는신";
	case GT_NONE:
		return "";
	case GT_SHIKIEIKI:
		return "시키에이키";
	case GT_BYAKUREN:
		return "뱌쿠렌";
	case GT_KANAKO:
		return "카나코";
	case GT_SUWAKO:
		return "스와코";
	case GT_MINORIKO:
		return "미노리코";
	case GT_MIMA:
		return "미마";
	case GT_SHINKI:
		return "신키";
	case GT_YUUGI:
		return "유우기";
	case GT_SHIZUHA:
		return "시즈하";
	case GT_HINA:
		return "히나";
	case GT_YUKARI:
		return "유카리";
	case GT_EIRIN:
		return "에이린";
	case GT_YUYUKO:
		return "유유코";
	case GT_SATORI:
		return "사토리";
	case GT_TENSI:
		return "텐시";
	case GT_SEIJA:
		return "세이자";
	case GT_LILLY:
		return "릴리";
	}
	return "모름";
}
bool GetGodString_is(god_type god)
{
	switch(god)
	{
	case GT_ERROR:
		return true;
	case GT_NONE:
		return true;
	case GT_SHIKIEIKI:
		return false;
	case GT_BYAKUREN:
		return true;
	case GT_KANAKO:
		return false;
	case GT_SUWAKO:
		return false;
	case GT_MINORIKO:
		return false;
	case GT_MIMA:
		return false;
	case GT_SHINKI:
		return false;
	case GT_YUUGI:
		return false;
	case GT_SHIZUHA:
		return false;
	case GT_HINA:
		return false;
	case GT_YUKARI:
		return false;
	case GT_EIRIN:
		return true;
	case GT_YUYUKO:
		return false;
	case GT_SATORI:
		return false;
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		return false;
	case GT_LILLY:
		return false;
	}
	return true;
}


int GetGodAbandonValue(god_type god)
{
	return 25;
}

int pietyLevel(int piety)
{
	if(piety<30)
		return 0;
	else if(piety<50)
		return 1;
	else if(piety<75)
		return 2;
	else if(piety<100)
		return 3;
	else if(piety<120)
		return 4;
	else if(piety<160)
		return 5;
	else 
		return 6;
}


bool GetGodAbility(int level, bool plus)
{
	switch(you.god)
	{
	case GT_ERROR:
		return false;
	case GT_NONE:
		return false;
	case GT_SHIKIEIKI:
		return false;
	case GT_BYAKUREN:
		switch(level)
		{
		case 1:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog("히지리는 당신의 배울 수 있는 마법레벨 한계를 늘려준다.",true,false,false,CL_white_blue);
			else
				printlog("더 이상 당신의 배울 수 있는 마법레벨 한계를 늘려주지않는다.",true,false,false,CL_white_blue);
			break;
		case 2:
			you.remainSpellPoiont+=plus;
			you.Ability(SKL_BYAKUREN_1,true,!plus);
			if(plus)
				printlog("당신은 순간적으로 지력을 강화시킬 수 있다.",true,false,false,CL_white_blue);
			else
				printlog("더 이상 순간적인 지력강화를 사용할 수 없다.",true,false,false,CL_white_blue);
			break;
		case 3:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog("당신은 이제 강화된 근력으로 낮은 갑옷패널티의 마법실패율을 무시한다.",true,false,false,CL_white_blue);
			else
				printlog("더이상 근력강화의 축복을 받지 못한다.",true,false,false,CL_white_blue);
			break;
		case 4:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog("히지리는 이제 당신의 강화마법들을 보조해준다.",true,false,false,CL_white_blue);
			else
				printlog("더 이상 강화마법들을 보조받지 못한다.",true,false,false,CL_white_blue);
			break;
		case 5:
			you.remainSpellPoiont+=plus;
			you.Ability(SKL_BYAKUREN_2,true,!plus);
			if(plus)
				printlog("당신은 이제 히지리의 축복으로 초인같은 각력으로 달릴 수 있게 된다.",true,false,false,CL_white_blue);
			else
				printlog("더이상 초인같은 각력을 사용할 수 없다.",true,false,false,CL_white_blue);
			break;
		}
		return false;
	case GT_KANAKO:
		switch(level)
		{
		case 1:
			you.Ability(SKL_KANAKO_1,true,!plus);
			if(plus)
				printlog("당신은 순간적으로 상대에게 돌진할 수 있다.",true,false,false,CL_help);
			else
				printlog("더 이상 순간적인 돌진을 사용할 수 없다.",true,false,false,CL_help);
			break;
		case 3:
			you.Ability(SKL_KANAKO_2,true,!plus);
			if(plus)
				printlog("당신은 기둥을 소환 할 수 있다.",true,false,false,CL_help);
			else
				printlog("더 이상 기둥을 소환 할 수 없다.",true,false,false,CL_help);
			break;
		case 5:
			you.Ability(SKL_KANAKO_3,true,!plus);
			if(plus)
				printlog("당신은 이제 바람을 감은 공격을 할 수 있다.",true,false,false,CL_help);
			else
				printlog("더 이상 바람을 감아 공격할 수 없다.",true,false,false,CL_help);
			break;
		}
		return false;
	case GT_SUWAKO:
		switch(level)
		{
		case 0:
			if(you.suwako_meet == 0)
			{
				you.god_value[GT_SUWAKO][0] = randA(SWAKO_1_LAST-1);
				you.god_value[GT_SUWAKO][1] = randA(SWAKO_2_LAST-1);
				you.god_value[GT_SUWAKO][2] = randA(SWAKO_3_LAST-1);
				you.god_value[GT_SUWAKO][3] = randA(SWAKO_4_LAST-1);
				you.god_value[GT_SUWAKO][4] = randA(SWAKO_5_LAST-1 -2);
				//다른 신을 믿고오면 you.god_value가 초기화될수도 있어... 어쩌지
				you.suwako_meet = 1;
			}
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			GetSwakoAbility(level,plus);
			break;
		}
		return false;
	case GT_MINORIKO:
		switch(level)
		{
		case 1:
			if(plus)
				printlog("당신은 파워가 높을수록 체력과 영력회복속도가 빨라진다.",true,false,false,CL_warning);
			else
				printlog("더 이상 체력과 영력회복속도가 빨라지지않는다.",true,false,false,CL_warning);
			break;
		case 2:
			you.Ability(SKL_MINORIKO_1,true,!plus);
			if(plus)
				printlog("당신은 이제 상태이상과 능력치저하를 회복할 수 있다.",true,false,false,CL_warning);
			else
				printlog("더 이상 상태이상과 능력치저하를 회복할 수 없다.",true,false,false,CL_warning);
			break;
		case 3:
			if(plus)
				printlog("당신은 이제 음식을 빨리 먹을 수 있고 영력을 조금 회복한다.",true,false,false,CL_warning);
			else
				printlog("더 이상 음식을 빨리 먹지 못한다.",true,false,false,CL_warning);
			break;
		case 4:
			you.Ability(SKL_MINORIKO_2,true,!plus);
			if(plus)
				printlog("당신은 이제 음식과 P를 소모하여 체력을 크게 회복할 수 있다.",true,false,false,CL_warning);
			else
				printlog("더 이상 음식으로 체력을 회복할 수 없다.",true,false,false,CL_warning);
			break;
		case 5:
			//if(you.power>=500)
			//{			
			//	you.ResistUpDown(plus,RST_FIRE);
			//	you.ResistUpDown(plus,RST_ICE);
			//}
			if(plus)
				printlog("당신은 이제 음식을 먹은 직후 화염과 냉기에 강해진다.",true,false,false,CL_warning);
			else
				printlog("더 이상 음식을 먹어도 화염과 냉기에 강하지않다.",true,false,false,CL_warning);
			break;
		}
		return false;
	case GT_MIMA:
		switch(level)
		{
			case 0:
				you.max_mp+=plus;
				if(plus)
					printlog("당신은 최대영력이 신앙심에 비례해서 증가한다.",true,false,false,CL_green);
				else
					printlog("당신의 최대영력은 감소했다.",true,false,false,CL_green);
				break;
			case 1:
				you.max_mp+=plus;
				if(plus)
					printlog("당신은 적을 죽였을때 영력을 얻는다.",true,false,false,CL_green);
				else
					printlog("더 이상 적을 죽였을때 영력을 얻지 못한다.",true,false,false,CL_green);
				break;
			case 2:
				you.max_mp+=plus;
				if(plus)
					printlog("미마는 이제 파괴술이 들어간 마법의 위력을 보조한다.",true,false,false,CL_green);
				else
					printlog("더 이상 파괴술 위력을 보조받지 못한다.",true,false,false,CL_green);
				break;
			case 3:
				mima_gift(BOOK_CONJURE);
				you.max_mp+=plus;
				break;
			case 4:
				you.max_mp+=plus;
				if(plus)
					printlog("미마는 이제 파괴술이 들어간 마법의 성공율을 올려준다.",true,false,false,CL_green);
				else
					printlog("더 이상 파괴술 성공율을 보정받지 못한다.",true,false,false,CL_green);
				break;
			case 5:
				mima_gift(BOOK_TEST_ANNIHILATE);
				you.max_mp+=plus;
				break;
			case 6:
				you.max_mp+=plus;
				break;
		}
		return false;
	case GT_SHINKI:
		switch(level)
		{
			case 1:
				you.Ability(SKL_SHINKI_1,true,!plus);
				if(plus)
					printlog("당신은 하급 마족의 작은 무리를 소환할 수 있다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 하급 마족의 작은 무리를 소환할 수 없다.",true,false,false,CL_white_puple);
				break;
			case 2:
				you.Ability(SKL_SHINKI_2,true,!plus);
				if(plus)
					printlog("당신은 위험을 무릅쓰고 신키의 중급 마족을 소환할 수 있다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 중급 마족을 소환할 수 없다.",true,false,false,CL_white_puple);
				break;
			case 3:
				if(plus)
					printlog("신키는 당신을 적대적인 소환수로부터 지켜준다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 적대적인 소환수로부터 보호받지 못한다.",true,false,false,CL_white_puple);
				break;
			case 4:
				you.Ability(SKL_SHINKI_3,true,!plus);
				if(plus)
					printlog("당신은 위험을 무릅쓰고 신키의 상급 마족을 소환할 수 있다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 상급 마족을 소환할 수 없다.",true,false,false,CL_white_puple);
				break;
			case 5:
				if(plus)
					printlog("이제 당신은 P로부터 힘을 얻는다.",true,false,false,CL_white_puple);
				else
					printlog("더 이상 P로부터 힘을 얻지 못한다.",true,false,false,CL_white_puple);
				break;
		}
		return false;
	case GT_YUUGI:
		switch(level)
		{
		case 0:
			if(plus)
				printlog("당신은 취했을때 잘 피할 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 취해도 피하지 못한다.",true,false,false,CL_yuigi);
			break;
		case 1:
			you.Ability(SKL_YUUGI_1,true,!plus);
			if(plus)
				printlog("당신은 물약을 술로 바꿔 마실 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 물약을 술로 바꿔 마실 수 없다.",true,false,false,CL_yuigi);
			break;
		case 2:
			you.Ability(SKL_YUUGI_2,true,!plus);
			if(plus)
				printlog("당신은 적에게 저먼 스플렉스를 걸 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 적에게 저먼 스플렉스를 걸 수 없다.",true,false,false,CL_yuigi);
			break;
		case 3:
			you.Ability(SKL_YUUGI_3,true,!plus);
			if(plus)
				printlog("당신은 적을 집어 던질 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 적을 집어 던질 수 없다.",true,false,false,CL_yuigi);
			break;
		case 4:
			you.Ability(SKL_YUUGI_4,true,!plus);
			if(plus)
				printlog("당신은 오니의 포효를 외칠 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 포효할 수 없다.",true,false,false,CL_yuigi);
			break;
		case 5:
			you.Ability(SKL_YUUGI_5,true,!plus);
			if(plus)
				printlog("당신은 드디어 삼보필살을 사용할 수 있다.",true,false,false,CL_yuigi);
			else
				printlog("더 이상 삼보필살을 사용할 수 없다.",true,false,false,CL_yuigi);
			break;
		}
		return false;
	case GT_SHIZUHA:
		switch(level)
		{
			case 0:
				if(plus)
					printlog("시즈하는 잠에서 깬 적들이 외치는 확률을 크게 줄여준다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 시즈하는 적의 외침을 줄여주지 않는다.",true,false,false,CL_autumn);
				break;
			case 1:
				if(plus)
					printlog("당신은 은밀하게 움직일 수 있는 단풍의 발자취를 남긴다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 당신은 발자취에 단풍을 남기지 못한다.",true,false,false,CL_autumn);
				break;
			case 2:
				you.Ability(SKL_SIZUHA_1,true,!plus);
				if(plus)
					printlog("당신은 단풍위에 있는 몬스터들에게 혼란을 걸 수 있다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 당신은 단풍위의 몬스터들에게 혼란을 걸 수 없다.",true,false,false,CL_autumn);
				break;
			case 3:
				you.Ability(SKL_SIZUHA_2,true,!plus);
				if(plus)
					printlog("당신은 끼고있는 방어구를 단풍 방어구로 만들 수 있다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 당신은 끼고있는 방어구를 단풍 방어구로 만들 수 없다.",true,false,false,CL_autumn);
				break;
			case 4:
				if(plus)
					printlog("당신은 단풍 위를 걸을때 매우 빠르게 움직일 수 있다.",true,false,false,CL_autumn);
				else
					printlog("더 이상 당신은 단풍 위에서 빠르게 움직일 수 없다.",true,false,false,CL_autumn);
				break;
			case 6:
				if(you.god_value[GT_SHIZUHA][0]==0)
				{
					you.Ability(SKL_SIZUHA_3,true,!plus);
					if(plus)
						printlog("당신은 딱 한번 당신의 무기에 단풍의 힘을 불어넣을 수 있다.",true,false,false,CL_autumn);
					else
						printlog("더 이상 당신은 당신의 무기에 단풍의 힘을 불어넣을 수 없다.",true,false,false,CL_autumn);
				}
				break;
		}
		return false;
	case GT_HINA:
		
		switch(level)
		{
		case 0:			
			if(plus)
			{
				for(list<item>::iterator it = you.item_list.begin(); it != you.item_list.end() ; it++)
				{
					it->identify_curse = true;
				}
				printlog("당신은 이제 아이템의 저주를 탐지할 수 있다.",true,false,false,CL_hina);
			}
			break;
		case 1:
			you.Ability(SKL_HINA_1,true,!plus);
			if(plus)
				printlog("당신은 저주걸린 아이템의 마이너스 인챈트를 플러스로 바꿀 수 있다.",true,false,false,CL_hina);
			else
				printlog("더 이상 저주걸린 아이템의 인챈트를 역전할 수 없다.",true,false,false,CL_hina);
			break;
		case 2:
			you.Ability(SKL_HINA_2,true,!plus);
			if(plus)
				printlog("당신은 무기에 저주를 걸어서 강력한 힘을 얻을 수 없다.",true,false,false,CL_hina);
			else
				printlog("더 이상 무기에 저주를 걸어서 힘을 얻을 수 없다.",true,false,false,CL_hina);
			break;
		case 3:
			you.Ability(SKL_HINA_3,true,!plus);
			if(plus)
				printlog("당신은 방어구에 저주를 걸어서 모든 데미지를 반사시킬 수 있다.",true,false,false,CL_hina);
			else
				printlog("더 이상 방어구에 저주를 걸어서 데미지를 반사시킬 수 없다.",true,false,false,CL_hina);
			break;
		case 4:
			you.Ability(SKL_HINA_4,true,!plus);
			if(plus)
				printlog("당신은 장신구에 저주를 걸어서 체력과 영력을 회복할 수 있다.",true,false,false,CL_hina);
			else
				printlog("더 이상 장신구에 저주를 걸어서 체력과 영력을 회복할 수 없다.",true,false,false,CL_hina);
			break;
		case 5:
			if(plus)
				printlog("당신은 이제 저주를 흩뿌리고 다닌다.",true,false,false,CL_hina);
			else
				printlog("더 이상 저주를 흩뿌리고 다니지 않는다.",true,false,false,CL_hina);
			break;
		case 6:
			if(you.god_value[GT_HINA][0]==0)
			{
				you.Ability(SKL_HINA_5,true,!plus);
				if(plus)
					printlog("당신은 딱 한번 당신의 무기에 저주의 힘을 불어넣을 수 있다.",true,false,false,CL_hina);
				else
					printlog("더 이상 당신은 당신의 무기에 저주의 힘을 불어넣을 수 없다.",true,false,false,CL_hina);
			}
			break;
		}
		return false;
		return false;
	case GT_YUKARI:
		switch(level)
		{
		case 1:
			if(plus)
				printlog("당신은 일정 데미지를 받으면 가끔 순간이동된다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 데미지를 받을때 순간이동되지 않는다.",true,false,false,CL_yukari);
			break;
		case 2:
			you.Ability(SKL_YUKARI_1,true,!plus);
			if(plus)
				printlog("당신은 경계로부터 지원사격을 요청할 수 있다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 지원사격을 요청할 수 없다.",true,false,false,CL_yukari);
			break;
		case 3:
			you.Ability(SKL_YUKARI_2,true,!plus);
			if(plus)
				printlog("당신은 경계를 타고 이동할 수 있다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 경계를 타고 이동할 수 없다.",true,false,false,CL_yukari);
			break;
		case 4:
			you.Ability(SKL_YUKARI_3,true,!plus);
			if(plus)
				printlog("당신은 결계를 만들 수 있다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 결계를 만들 수 없다.",true,false,false,CL_yukari);
			break;
		case 5:
			you.Ability(SKL_YUKARI_4,true,!plus);
			if(plus)
				printlog("당신은 차원을 고정시킬 수 있다.",true,false,false,CL_yukari);
			else
				printlog("더 이상 차원을 고정시킬 수 없다.",true,false,false,CL_yukari);
			break;
		}
		return false;
	case GT_EIRIN:
		switch(level)
		{
		case 0:
			if(plus)
			{
				printlog("에이린은 물약작용을 올려준다. 좋은물약위에서 기도하여 나쁜물약을 만들 수 있다.",true,false,false,CL_small_danger);
				iden_list.potion_list[PT_POISON].iden = true;
				iden_list.potion_list[PT_DOWN_STAT].iden = true;
				iden_list.potion_list[PT_CONFUSE].iden = true;
				iden_list.potion_list[PT_SLOW].iden = true;
				iden_list.potion_list[PT_PARALYSIS].iden = true;
			}
			else
			{
				printlog("더 이상 물약의 작용을 올려주지 않는다. 더이상 나쁜 물약을 만들 수 없다.",true,false,false,CL_small_danger);
			}
			break;
		case 1:
			if(plus)
				printlog("당신은 독물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더 이상 독물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 2:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 1);
			you.Ability(SKL_EIRIN_0,true,!plus);
			if(plus)
				printlog("당신은 물약을 던질 수 있다. 이제 능력치감소물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더 이상 물약을 던질 수 없다. 능력치감소물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 3:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 2);
			you.Ability(SKL_EIRIN_1,true,!plus);
			if(plus)
				printlog("당신은 신체개조를 할 수 있다. 당신은 이제 혼란물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더 이상 신체개조를 할 수 없다. 더 이상 혼란물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 4:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 3);
			if(plus)
				printlog("당신은 감속물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더 이상 감속물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 5:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 4);
			you.Ability(SKL_EIRIN_2,true,!plus);
			if(plus)
				printlog("이제 긴급수혈이 가능하다. 이제 마비물약에서 새로운 힘을 얻는다.",true,false,false,CL_small_danger);
			else
				printlog("더이상 긴급수혈을 할 수 없다. 더 이상 마비물약에서 새로운 힘을 얻을 수 없다.",true,false,false,CL_small_danger);
			break;
		case 6:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 5);
			break;
		}
		return false;
	case GT_YUYUKO:
		switch(level)
		{
		case 1:
			if(you.s_ghost == 0)
			{
				if(plus)
				{
					you.SetGhost(1);
				}
				you.Ability(SKL_YUYUKO_ON,true,plus);
				you.Ability(SKL_YUYUKO_OFF,true,!plus);

			}
			else
			{				
				if(!plus)
					you.SetGhost(0);
				you.Ability(SKL_YUYUKO_OFF,true,!plus);
				you.Ability(SKL_YUYUKO_ON,true,plus);
			}
			if(plus)
				printlog("당신 주변엔 항상 유령이 모여든다.",true,false,false,CL_yuyuko);
			else
				printlog("더 이상 당신 주변에 유령이 모여들지 않는다.",true,false,false,CL_yuyuko);
			break;
		case 2:
			you.Ability(SKL_YUYUKO_1,true,!plus);
			if(plus)
				printlog("유령을 원하는 곳으로 이동시킬 수 있다.",true,false,false,CL_yuyuko);
			else
				printlog("더 이상 유령을 이동시킬 수 없다.",true,false,false,CL_yuyuko);
			break;
		case 3:
			you.Ability(SKL_YUYUKO_2,true,!plus);
			if(plus)
				printlog("잠시동안 유령의 빈도를 증가시킬 수 있다.",true,false,false,CL_yuyuko);
			else
				printlog("더 이상 유령의 빈도를 증가시킬 수 없다.",true,false,false,CL_yuyuko);
			break;
		case 5:
			you.Ability(SKL_YUYUKO_3,true,!plus);
			if(plus)
				printlog("적 한명의 영혼을 속박할 수 있다.",true,false,false,CL_yuyuko);
			else
				printlog("더 이상 영혼을 속박할 수 없다.",true,false,false,CL_yuyuko);
			break;
		}
		return false;
	case GT_SATORI:
		switch(level)
		{
		case 0:
			you.ResistUpDown(plus,RST_INVISIBLE);
			if(plus)
				printlog("당신은 이제 투명을 감지할 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 투명을 감지할 수 없다.",true,false,false,CL_danger);
			break;
		case 1:
			you.Ability(SKL_SATORI_1,true,!plus);
			if(plus)
				printlog("당신은 적에게 트라우마를 보여줄 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 적에게 트라우마를 보여줄 수 없다.",true,false,false,CL_danger);
			break;
		case 2:
			if(plus)
				printlog("당신은 적으로부터 던전의 모양을 읽어낼 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 적으로부터 던전의 모양을 읽지 못한다.",true,false,false,CL_danger);
			break;
		case 3:
			if(plus)
				printlog("당신은 주변의 적의 기척을 읽을 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 주변의 적의 기척을 읽을 수 없다.",true,false,false,CL_danger);
			break;
		case 4:
			you.Ability(SKL_SATORI_2,true,!plus);
			if(plus)
				printlog("당신은 적의 생각을 읽어낼 수 있다.",true,false,false,CL_danger);
			else
				printlog("더 이상 생각을 읽을 수 없다.",true,false,false,CL_danger);
			break;
		case 5:
			if(plus)
				printlog("당신은 사토리님의 관리를 직접 받는 소중한 애완동물이다.",true,false,false,CL_danger);
			else
				printlog("더 이상 사토리님은 당신을 직접 관리하지않는다.",true,false,false,CL_danger);
			break;
		}
		return false;
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		return false;
	case GT_LILLY:
		return false;
	}
	return false;
}

bool GodAccpect_KillMonster(monster* mon_, parent_type type_)
{
	switch(you.god)
	{
	case GT_ERROR:
		return false;
	case GT_NONE:
		return false;
	case GT_SHIKIEIKI:
		return false;
	case GT_BYAKUREN:
		return false;
	case GT_KANAKO:
		if(!(mon_->flag & M_FLAG_SUMMON))
		{
			if(type_ == PRT_PLAYER)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					printlog("카나코는 당신의 살생을 기뻐했다.",true,false,false,CL_help);
					if(randA(2))
					{
						you.GiftCount(1);
						you.PietyUpDown(1);
						return true;
					}
				}
				else
				{ //아군일때
					printlog("카나코는 당신의 행동에 분노했다. 참회하라!",true,false,false,CL_small_danger);
					you.PietyUpDown(-5);
					return true;
				}
			}
		}
		return false;
	case GT_SUWAKO:
		if(!(mon_->flag & M_FLAG_SUMMON))
		{
			if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					printlog("스와코는 당신의 살생을 기뻐했다.",true,false,false,CL_swako);
					if(randA(2))
					{
						you.PietyUpDown(1);
					}
					if(!you.GetPunish(GT_SUWAKO) && pietyLevel(you.piety)>=2)
					{
						switch(you.god_value[GT_SUWAKO][1])
						{
						case SWAKO_2_KILL_HP:
							if(randA(200) < you.piety)
							{
								printlog("체력이 회복되었다.",false,false,false,CL_normal);
								you.HpUpDown(randA_1(1+mon_->level/2), DR_EFFECT);
							}
							break;
						case SWAKO_2_KILL_MP:
							if(randA(120) < you.piety)
							{
								printlog("영력이 회복되었다.",false,false,false,CL_normal);
								you.MpUpDown(randA_1(1+mon_->level/4));
							}
							break;
						case SWAKO_2_KILL_POWER:
							if(randA(200) < you.piety)
							{
								printlog("파워가 회복되었다.",false,false,false,CL_normal);
								you.PowUpDown(rand_int(3,5)+randA(mon_->level/4));
							}
							break;
						}
					}
					enterlog();
				}
			}
		}
		return false;
	case GT_MINORIKO:
		if(mon_->id == MON_LETTY &&  !(mon_->flag & M_FLAG_SUMMON))
		{
			if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					printlog("미노리코는 흥분한 상태로 외쳤다.\"바로 그거야!\"",true,false,false,CL_warning);
					you.PietyUpDown(5);
				}
			}
		}
		return false;
	case GT_MIMA:
		if(!(mon_->flag & M_FLAG_SUMMON))
		{
			if(type_ == PRT_PLAYER)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					printlog("미마는 당신의 살생을 기뻐했다.",false,false,false,CL_green);
					if(randA(5)<3)
					{
						you.PietyUpDown(1);
						return true;
					}
					if(!you.GetPunish(GT_MIMA) && pietyLevel(you.piety)>=1)
					{
						if(randA(120) < you.piety)
						{
							printlog("영력이 회복되었다.",false,false,false,CL_normal);
							you.MpUpDown(randA_1(1+mon_->level/3));
						}
					}
					enterlog();
				}
			}
		}
		return false;
	case GT_SHINKI:
		return false;
	case GT_YUUGI:
		if(!(mon_->flag & M_FLAG_SUMMON))
		{
			if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					printlog("유우기는 당신의 승리를 기뻐했다.",true,false,false,CL_yuigi);
					if(randA(2))
					{
						you.PietyUpDown(1);
						return true;
					}
				}
			}
		}
		return false;
	case GT_SHIZUHA:
		if(pietyLevel(you.piety) >=1)
		{
			rand_rect_iterator rit(mon_->position,2,2);
			int i = randA(1+pietyLevel(you.piety)); 
			for(;!rit.end() && i> 0;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y))
				{	
					int rand_ = randA(1);
					env[current_level].MakeFloorEffect(coord_def(rit->x,rit->y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,rand_int(20,30),&you);
				}
				i--;
			}
			int rand_ = randA(1);
			env[current_level].MakeFloorEffect(coord_def(you.position.x,you.position.y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,3+you.piety/20,&you);
			//플레이어 위치에는 무조건 단풍이 세워진다.(일부러 발밑에 단풍까는 플레이를 안해도되게 하기위해)
		}
		if(!(mon_->flag & M_FLAG_SUMMON))
		{
			if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					if(mon_->id == MON_LETTY)
					{
						printlog("시즈하는 박수를 쳤다.\"훌륭해\"",true,false,false,CL_autumn);
						you.PietyUpDown(4);
					}
					else
						printlog("시즈하는 당신의 적이 낙엽처럼 쓰러져가는 것을 기뻐했다.",true,false,false,CL_autumn);
					if(randA(2))
					{
						you.PietyUpDown(1);
						return true;
					}
				}
			}
		}
		return false;
	case GT_HINA:
		return false;
	case GT_YUKARI:
		if(!(mon_->flag & M_FLAG_SUMMON))
		{
			if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					printlog("유카리는 당신의 살생을 기뻐했다.",true,false,false,CL_yukari);
					if(randA(2))
					{
						you.PietyUpDown(1);
						return true;
					}
				}
			}
		}
		return false;
	case GT_EIRIN:
		if(!(mon_->flag & M_FLAG_SUMMON))
		{
			if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					if(randA(3)==0)
					{
						printlog("에이린은 당신의 강함에 관심을 가졌다.",true,false,false,CL_small_danger);
						you.PietyUpDown(1);
						return true;
					}
				}
			}
		}
		return false;
	case GT_YUYUKO:
		if(!(mon_->flag & M_FLAG_SUMMON))
		{
			if(mon_->s_ghost)
			{
				if(you.god_value[GT_YUYUKO][0])
				{
					for(auto it = env[you.god_value[GT_YUYUKO][1]].mon_vector.begin();it != env[you.god_value[GT_YUYUKO][1]].mon_vector.end();it++)
					{
						if(it->isLive() && it->map_id == you.god_value[GT_YUYUKO][0])
						{
							it->summon_time = 0;
						}
					}
				}
				
				{
					monster *mon2_ = BaseSummon(mon_->id, -1, false, false,4,&you, mon_->position, SKD_OTHER, -1);
					if(mon2_)
					{

						mon2_->id = MON_ENSLAVE_GHOST;
						mon2_->name.name += "의 영혼";
						mon2_->name.name_type = true;
						printarray(true,false,false,CL_normal,3,mon_->name.name.c_str(),mon_->name.name_do()," 당신의 동료가 되었다.");
						you.god_value[GT_YUYUKO][0] = mon2_->map_id;
						you.god_value[GT_YUYUKO][1] = current_level;

						//유령화되면 냉기저항1단계증가
						if(mon2_->ice_resist<=2)
							mon2_->ice_resist++;
						//독저항이 생긴다.
						mon2_->poison_resist=1;
						
						//그러나 레벨은 내려간다.
						mon2_->LevelUpdown(-2);

						char temp[200];
						sprintf_s(temp,200,"%s%s구속했다.",mon_->name.name.c_str(),mon_->name.name_to(true));
						AddNote(you.turn,CurrentLevelString(),temp,CL_yuyuko);
					}
				}
			}
			else if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
			{
				if(!mon_->isUserAlly())
				{ //적일때
					printlog("유유코는 당신의 살생을 기뻐했다.",true,false,false,CL_yuyuko);
					if(randA(2))
					{
						you.PietyUpDown(1);
						return true;
					}
				}
			}
		}
		return false;
	case GT_SATORI:
		if(1)
		{
			you.GiftCount(1);
		}
		return false;
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		return false;
	case GT_LILLY:
		return false;
	}
	return false;
}
bool GodAccpect_GetPitem()
{
	switch(you.god)
	{
	case GT_MINORIKO:		
		if(randA(3))
		{
			you.GiftCount(1);
			you.PietyUpDown(1);
			return true;
		}
		break;
	case GT_ERROR:
	case GT_NONE:
	case GT_SHIKIEIKI:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MIMA:
		return false;
	case GT_SHINKI:	
		if(1)
		{
			if(!you.GetPunish(GT_SHINKI) && pietyLevel(you.piety)>=5)
			{
				int hp_ = rand_int(you.max_hp*9/100,you.max_hp*18/100)+1;
				printlog("회복되었다.",false,false,false,CL_normal);
				you.HpUpDown(hp_, DR_EFFECT);
				you.MpUpDown(randA_1(5));
			}
			you.PietyUpDown(1);
			return true;
		}
		break;
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
		return false;
	}
	return false;
}
bool GodAccpect_HPUpDown(int value_,damage_reason reason)
{
	switch(you.god)
	{
	case GT_MINORIKO:		
	case GT_ERROR:
	case GT_NONE:
	case GT_SHIKIEIKI:
	case GT_KANAKO:
		break;
	case GT_SUWAKO:		
		if(!you.GetPunish(GT_SUWAKO) && pietyLevel(you.piety)>=2)
		{
			switch(you.god_value[GT_SUWAKO][1])
			{
			case SWAKO_2_DEAD_PROTECT:
				if(randA(9)<4 && you.hp <= 0 && value_ < 0)
				{
					if(you.hp-value_>0)
					{
						you.hp-=value_;
						printlog("보호되었다!",false,false,false,CL_swako);
					}
				}
				break;
			}
		}
		break;
	case GT_MIMA:
	case GT_SHINKI:	
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
		break;
	case GT_YUKARI:
		if(pietyLevel(you.piety)>=1 && you.hp > 0 && value_ < 0)
		{
			int percent_ = value_ *-100 / you.max_hp;
			int a_ = 0;
			if(randA(percent_+a_)>=8+a_)
			{				
				int left_percent_ = you.hp *-100 / you.max_hp;
					
				if(percent_>=rand_int(25,50) && percent_>left_percent_)
				{
					you.Teleport();
					if(env[current_level].isInSight(you.position))
						printlog("당신은 약간 공간이 어긋난 것을 눈치챘다.",false,false,false,CL_normal);
					else
						printlog("갑자기 당신 주변이 변화했다.",false,false,false,CL_normal);
				}
				else
				{
					you.Blink(30);
				}
			}
		}
		break;
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
		return false;
	}
	return false;
}

bool GodAccpect_UseSpell(spell_list spell_)
{
	switch(you.god)
	{
	case GT_MINORIKO:		
	case GT_ERROR:
	case GT_NONE:
	case GT_SHIKIEIKI:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MIMA:
	case GT_SHINKI:
		return false;
	case GT_YUUGI:
		printlog("유우기는 당신의 마법에 분노했다!",true,false,false,CL_small_danger);
		you.PietyUpDown(-5);
		return false;
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
		if(spell_ == SPL_BLINK || spell_ == SPL_TELEPORT_SELF)
		{			
			printlog("유카리는 당신의 위험한 전이마법 사용에 분노했다!",true,false,false,CL_small_danger);
			you.PietyUpDown(-5);
			return false;
		}
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
		return false;
		return false;
	}
	return false;
}
bool GodAccpect_Practice(int value, skill_type skill_)
{
	switch(you.god)
	{
	case GT_BYAKUREN:
		if(skill_ >= SKT_SPELLCASTING && skill_ <= SKT_ALCHEMY && value>randA(40))
		{
			you.PietyUpDown(1);
			you.GiftCount(1);
			return true;
		}
	case GT_ERROR:
	case GT_NONE:
	case GT_SHIKIEIKI:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
		return false;
	}
	return false;
}
bool GodAccpect_Explore_100()
{
	switch(you.god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_SHIKIEIKI:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
		return false;
	case GT_HINA:
		if(60>randA(100))
		{
			you.PietyUpDown(1);
			return true;
		}
		return false;
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
		return false;
	case GT_SATORI:
		if(50>randA(100))
		{
			you.PietyUpDown(1);
			you.GiftCount(1);
			return true;
		}
		return false;
	case GT_TENSI:
		if(20>randA(100))
		{
			you.GiftCount(1);
		}
		return false;
	case GT_SEIJA:
	case GT_LILLY:
		return false;
	}
	return false;
}
bool GodAccpect_First_contact()
{
		switch(you.god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_SHIKIEIKI:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
		return false;
	case GT_SATORI:
		if(randA(1)==0)
		{
			you.GiftCount(1);
		}
	case GT_TENSI:
		if(1)
		{
			if(randA_1(500)<you.CheckTension())
			{
				you.GiftCount(2);
			}
		}
		return false;
	case GT_SEIJA:
	case GT_LILLY:
		return false;
	}
	return false;
}
bool GodAccpect_turn(int turn)
{
	if(you.GetPunish(GT_KANAKO))
	{		
		{		
			for(auto it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && it->GetId() == MON_ONBASIRA && !it->isUserAlly() && distan_coord(you.position,it->position) <= 2)
				{
					you.SetSlaying(-3);
				}
			}
		}
	}
	if(you.GetPunish(GT_SHIZUHA))
	{
		if(turn>1 && you.prev_position != you.position)
		{
			int rand_ = randA(1);
			env[current_level].MakeFloorEffect(you.prev_position,&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,15,&you);
		}
	}




	switch(you.god)
	{
	case GT_ERROR:
		return false;
	case GT_NONE:
		return false;
	case GT_SHIKIEIKI:
		return false;
	case GT_BYAKUREN:
		return false;
	case GT_KANAKO:
		{		
			for(auto it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && it->GetId() == MON_ONBASIRA && it->isUserAlly() && distan_coord(you.position,it->position) <= 2)
				{
					you.SetSlaying(3);
				}
			}
		}
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SUWAKO:
		{	

			if(you.god == GT_SUWAKO && !you.GetPunish(GT_SUWAKO) && pietyLevel(you.piety)>=2 &&
			you.god_value[GT_SUWAKO][1] == SWAKO_2_SWIM)
			{
				auto tile_ = env[current_level].dgtile[you.position.x][you.position.y].tile;
				if(tile_ == DG_SEA)
					you.SetBuff(BUFFSTAT_EV,BUFF_SUWAKO,8,2);
				else
					you.SetBuff(BUFFSTAT_EV,BUFF_SUWAKO,0,2);
			}
		}
		return false;
	case GT_MINORIKO:
		{
			if(turn%3000 == 0)
			{
				you.PietyUpDown(-1);		
			}
		}
		return false;
	case GT_MIMA:
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SHINKI:
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_YUUGI:
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SHIZUHA:
		{
			if(pietyLevel(you.piety) >=1 && turn>1 && you.prev_position != you.position)
			{
				int rand_ = randA(1);
				env[current_level].MakeFloorEffect(you.prev_position,&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,4+you.piety/10,&you);
			}
			if(turn%2000 == 0)
			{
				you.PietyUpDown(-1);		
			}
		}
		return false;
	case GT_HINA:
		if(pietyLevel(you.piety) >= 5 && !you.GetPunish(GT_HINA))
		{
			int curse_ = 0;
			
			for(equip_type i = ET_FIRST;i!=ET_LAST;i=(equip_type)(i+1))
			{
				if(you.equipment[i])
				{
					if(you.equipment[i]->curse)
						curse_++;
				}
			}
			if(randA(100)<80*curse_/ET_LAST)
			{
				dif_rect_iterator rit(you.position,4,true);
				while(!rit.end())
				{
					coord_def check_pos_ = (*rit);
					
					if(env[current_level].isMove(check_pos_.x, check_pos_.y, false) && env[current_level].isInSight(check_pos_) && you.isSightnonblocked((*rit)))
					{
						env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_CURSE,rand_int(6,8),0,&you);
						break;
					}
					rit++;
				}
			}
		}
		return false;
	case GT_YUKARI:
		if(turn%10 == 0)
		{
			if(1/*randA(100)<20pietyLevel(you.piety) >=1*/)
			{
				dif_rect_iterator rit(you.position,8,true);
				while(!rit.end())
				{
					coord_def check_pos_ = (*rit);

					if(you.s_dimension)
					{
						if(abs(you.god_value[GT_YUKARI][0] - check_pos_.x)>8)
							check_pos_.x += (you.god_value[GT_YUKARI][0] - check_pos_.x)>0?17:-17;
						if(abs(you.god_value[GT_YUKARI][1] - check_pos_.y)>8)
							check_pos_.y += (you.god_value[GT_YUKARI][1] - check_pos_.y)>0?17:-17;
					}


					if(env[current_level].isMove(check_pos_.x, check_pos_.y, false) && env[current_level].isInSight(check_pos_) && you.isSightnonblocked((*rit)))
					{
						textures* t_ = &img_effect_schema[randA(2)];
						env[current_level].MakeFloorEffect(coord_def(check_pos_.x,check_pos_.y),t_,t_,FLOORT_SCHEMA,rand_int(20,30),&you);
						break;
					}
					rit++;
				}
			}
		}

		if(turn%3000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_EIRIN:
		if(turn%4500 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_YUYUKO:
		if(turn%3 == 0)
		{
			if(you.s_ghost && randA(100)<(you.s_ghost>=2?85:5+you.piety/8))
			{
				coord_def c_ = you.position/*+coord_def(rand_int(-6,6),rand_int(-6,6))*/;
				monster *mon_ = BaseSummon(MON_GHOST, rand_int(20,30), false, true,4,&you, c_, SKD_OTHER, -1);
				if(mon_)
				{
					mon_->LevelUpdown(you.level-1,3.0f,1.5f);
					mon_->image = &img_mons_ghost[randA(2)];
				}
			}
		}
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SATORI:
		if(turn%3000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_TENSI:
		if(turn%7 == 0)
		{
			if(randA(1000)<you.CheckTension())
			{
				you.GiftCount(2);
			}
			else if(randA(10)==0)
			{
				you.GiftCount(1);
			}
		}
		return false;
	case GT_SEIJA:
	case GT_LILLY:
		return false;
	}
	return false;
}



int satori_sight()
{
	return pietyLevel(you.piety)*2;
}


void Pray()
{
	if(you.god != GT_NONE)
	{	
		bool sacrifice = false;
		int num = 0;
		for(list<item>::iterator it = env[current_level].item_list.begin();it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++;
			if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
			{
				sacrifice = (God_pray(temp))?true:sacrifice;
				num++;
			}
			else if(num)
				break;
		}
		if(!sacrifice)
			printarray(true,false,false,CL_warning,3,GetGodString(you.god),GetGodString_is(you.god)?"은 ":"는 ","당신의 기도를 받아들였다.");
	}
	else
	{
		enterlog();
		dungeon_tile_type type = env[current_level].dgtile[you.position.x][you.position.y].tile;
		if(type == DG_TEMPLE_SUWAKO && isTutorial() && !you.s_poison)
		{
			printlog("스와코는 말했다 : 던전에서 죽는다고 진짜 죽는건 아니야. 모든 기록은 사라지지만.",true,false,false,CL_warning);
			printlog("스와코는 말했다 : 그래서 크롤의 세계에선 죽는 것도 일이란다! 다음에 보자 사나에!",true,false,false,CL_warning);
			you.SetPoison(150, 150,true);
		}
		
		if(type >= DG_TEMPLE_FIRST && type <= DG_TEMPLE_LAST)
		{
			printlog("당신은 제단에 기도를 드렸다.",true,false,false,CL_warning);
			MoreWait();


			if(type != DG_TEMPLE_SATORI && you.GetPunish((god_type)(type-DG_TEMPLE_FIRST)))
			{
				printarray(true,false,false,CL_warning,3,GetGodString((god_type)(type-DG_TEMPLE_FIRST)),GetGodString_is((god_type)(type-DG_TEMPLE_FIRST))?"은 ":"는 ","아직 당신을 용서하지않았다.");


			}
			else if(type == DG_TEMPLE_SHIKIEIKI)
			{
				printlog("시키에이키는 당신의 입교를 받아주기엔 아직 너무 바쁘다!.",true,false,false,CL_warning);
			}
			else
			{
				WaitForSingleObject(mutx, INFINITE);
				deletesub();
				GodInfor((god_type)(type-DG_TEMPLE_FIRST));
				printsub("",true,CL_normal);
				printsub("",true,CL_normal);
				printsub("신도가 되려면 Y키를, 취소하려면 N키를 누른다.",true,CL_help);
				changedisplay(DT_SUB_TEXT);
				ReleaseMutex(mutx);
				bool ok_= true;
				while(ok_)
				{			
					int select = waitkeyinput();
					switch(select)
					{
					default:
					case '?':
						break;
					case 'Y':
					case 'y':
						changedisplay(DT_GAME);
						you.Belief((god_type)(type-DG_TEMPLE_FIRST),15);
						MoreWait();
					case 'N':
					case 'n':
						ok_ = false;
						break;
					}
				}
				changedisplay(DT_GAME);
			}
		}
		else
		{
			printlog("당신은 삶의 의미에 대해 잠시 생각했다.",true,false,false,CL_warning);
		}

		//switch(type)
		//{
		//case DG_TEMPLE_SHIKIEIKI:
		//	printlog("시키에이키는 말했다 : 최대한 빨리 그 쪽지를 지상으로 가져다주세요.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_BYAKUREN:
		//	printlog("뱌쿠렌은 말했다 : 아아, 크롤의 세계 안에 빛이 가득해.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_KANAKO:
		//	printlog("카나코는 말했다 : 이것은 신앙을 모을 기회입니다.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SUWAKO:
		//	if(isNormalGame() || you.s_poison)
		//	{
		//		printlog("스와코는 말했다 : 아하하, 재미있어졌어.",true,false,false,CL_warning);
		//	}
		//	else
		//	{
		//		printlog("스와코는 말했다 : 던전에서 죽는다고 진짜 죽는건 아니야. 모든 기록은 사라지지만.",true,false,false,CL_warning);
		//		printlog("스와코는 말했다 : 그래서 크롤의 세계에선 죽는 것도 일이란다! 다음에 보자 사나에!",true,false,false,CL_warning);
		//		you.SetPoison(150,true);
		//	}
		//	break;
		//case DG_TEMPLE_MINORIKO:
		//	printlog("미노리코는 말했다 : 던전탐험도 식후경!",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_MIMA:
		//	printlog("미마는 말했다 : 기분좋게 자고있었는데, 어떻게 된거지?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SHINKI:
		//	printlog("신키는 말했다 : 마계도 엉망이야...",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_YUUGI:
		//	printlog("유우기는 말했다 : 강한 녀석들을 많이 보겠는걸!",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SHIZUHA:
		//	printlog("잘 들리지않는 부스럭거리는 소리가 들린다.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_HINA:
		//	printlog("히나는 말했다 : 액이 넘쳐나! 액땜할 시간이야!",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_YUKARI:
		//	printlog("유카리는 말했다 : 내 탓은 아니라구?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_EIRIN:
		//	printlog("에이린은 말했다 : 힘을 원한다면, 나의 실험재료가 되는건 어때?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_YUYUKO:
		//	printlog("유유코는 말했다 : 이왕 이렇게 된거 즐기면 되잖아?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SATORI:
		//	printlog("사토리는 말했다 : 애완동물들은 어디로 갔을까요...",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_TENSI:
		//	printlog("텐시는 미친듯이 웃었다.",true,false,false,CL_warning);
		//	break;
		//default:
		//	printlog("당신은 삶의 의미에 대해 잠시 생각했다.",true,false,false,CL_warning);
		//	break;
		//}
	}
	you.time_delay += you.GetNormalDelay();
	you.TurnEnd();
}



void GodInfor(god_type god)
{
	printsub("                                                    신앙",true,CL_normal);
	switch(god)
	{
	case GT_SUWAKO:
		printsub("모리야 스와코 - 토착신의 정점",true,CL_swako);
		printsub("",true,CL_normal);
		printsub("스와코는 곤(땅)을 창조하는 능력을 가진 토착신이다.",true,CL_normal);
		printsub("스와코는 신자들에게 변덕스러운 권능을 준다.",true,CL_normal);
		printsub("그 때문에 신자들은 다양한 권능을 받을 수 있지만 원하는 권능을 받지는 못한다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_MIMA:
		printsub("미마 - 아득한 꿈에 운명을 맡긴 정신",true,CL_green);
		printsub("",true,CL_normal);
		printsub("미마는 재앙신격인 존재로 악령이다.",true,CL_normal);
		printsub("신도들은 미마의 밑으로 들어가는 것으로 강력한 파괴 마법을 지원받고 전수받는다.",true,CL_normal);
		printsub("특히 그녀의 충실한 추종자가 되었을때 궁극의 파괴 마법인 스파크를 전수받게된다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_YUYUKO:
		printsub("사이교우지 유유코 - 저승누각의 망령소녀",true,CL_yuyuko);
		printsub("",true,CL_normal);
		printsub("유유코는 백옥루에 사는 사이교우지의 아가씨이다.",true,CL_normal);
		printsub("그녀는 죽음을 조종 할 수 있는 강력한 능력을 가지고 있어서 신도들에게 죽음의 힘을 선물해준다.",true,CL_normal);
		printsub("그녀의 신도가 되면 죽음을 다루는 능력과 많은 영혼들을 선물 받을 것이다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SHIKIEIKI:
		printsub("시키에이키 야마자나두 - 낙원의 최고재판장",true,CL_help);
		printsub("",true,CL_normal);
		printsub("시키에이키는 죽은자의 재판을 맡고 있는 환상향의 염라대왕. 그녀는 흑백을 가리는 능력을 가지고 있다.",true,CL_normal);
		printsub("신자들이 선행을 배푸는 것을 유도하며 악한 자들에게 대신 심판을 내리도록 돕는다.",true,CL_normal);
		printsub("까다로운 교칙이 있지만 신자들은 던전의 몬스터들에게 그녀의 설교를 전달할 수 있게된다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SHINKI:
		printsub("신키 - 마계의 신",true,CL_white_puple);
		printsub("",true,CL_normal);
		printsub("신키는 마계의 주인이자 마계를 창조한 마계의 신이다.",true,CL_normal);
		printsub("창조의 능력을 이용해서 신키는 신도들에게 강력한 마족들을 선물한다.",true,CL_normal);
		printsub("또한 신키는 당신을 적대적인 소환수로부터 지켜주거나 P를 모을때마다 체력과 영력을 회복시켜준다.",true,CL_normal);
		printsub("일정수준 이상의 마족들은 당신을 언제라도 배신할 수 있는 걸 염두해야된다.",true,CL_normal);
		printsub("신도들은 P템을 줍는 것으로 신앙심을 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_MINORIKO:
		printsub("아키 미노리코 - 풍족과 수확의 상징",true,CL_warning);
		printsub("미노리코는 가을의 수확을 상징하는 신으로 신도에게 풍족함을 선사한다.",true,CL_normal);
		printsub("신도들은 미노리코에게 풍족한 음식을 내려받게 되고 포만감과 체력을 보장받는다.",true,CL_normal);
		printsub("신도들은 P템을 줍는 것으로 신앙심을 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SHIZUHA:
		printsub("아키 시즈하 - 외로움과 임종의 상징",true,CL_small_danger);
		printsub("",true,CL_normal);
		printsub("아키 시즈하는 단풍의 신이다.",true,CL_normal);
		printsub("시즈하는 신도들의 당신의 존재감을 낮추어 은밀하게 다닐 수 있게 도와준다.",true,CL_normal);
		printsub("그녀의 권능은 암살자들에게 큰 혜택을 주며 중갑옷의 패널티도 크게 상쇄받을 수 있다.",true,CL_normal);
		printsub("시즈하는 시끄러운 자들의 시체가 낙엽처럼 떨어지는 것을 기뻐한다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_EIRIN:
		printsub("야고코로 에이린 - 달의 두뇌",true,CL_small_danger);
		printsub("",true,CL_normal);
		printsub("그녀는 모든 약을 제조할 수 있는 달의 최고의 현자로 천재 약사이다.",true,CL_normal);
		printsub("그녀의 신도로 들어가면 여러가지 물약들을 받게되고 추가적인 효과를 얻게 된다.",true,CL_normal);
		printsub("또한 자신의 몸을 개조하거나 부작용을 감당하는 극적인 치료도 가능해진다.",true,CL_normal);
		printsub("신도는 그녀의 실험대상이 될 각오를 할 수 있다면 그만큼의 보답을 받을 수 있을 것이다.",true,CL_normal);
		printsub("신도는 이로운 물약의 위에서 기도를 하여 포션을 바치거나 물약을 마시는 것으로 신앙심을 얻을 수 있다.",true,CL_normal);
		printsub("또한 자주는 아니지만 적을 죽였을때 가끔씩 신앙심을 얻을 수 도 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_KANAKO:
		printsub("야사카 카나코 - 산판과 호수의 권화",true,CL_help);
		printsub("",true,CL_normal);
		printsub("카나코는 건(하늘)을 창조하는 능력을 가진 신으로 본래는 바람의 신이지만 산의 신으로 모셔지고 있다.",true,CL_normal);
		printsub("그녀는 신자들에게 신앙을 받는 것으로 강력한 전투 능력을 보답한다.",true,CL_normal);
		printsub("특히 근접전사와 원거리탄막으로 싸우는 자에게 큰 도움이 될 것이다.",true,CL_normal);
		printsub("신자들은 계속되는 전투로 그녀에게 신앙을 바쳐야한다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_YUKARI:
		printsub("야쿠모 유카리 - 경계속에 숨은 요괴",true,CL_yukari);
		printsub("야쿠모 유카리는 환상향에서도 이름있는 강력한 경계의 요괴다.",true,CL_normal);
		printsub("유카리의 식신으로 들어가게 되면 그녀에게 경계와 관련된 능력을 얻을 수 있다.",true,CL_normal);
		printsub("강력한 전이능력을 제공받지만 권능을 제외한 다른 전이능력을 금지하고",true,CL_normal);
		printsub("제어하기 힘든 강력한 전이 능력은 역으로 신도를 위험하게 만들수도 있다.",true,CL_normal);
		//printsub("그녀의 신전은 스키마 안쪽이라는 특수한 던전에 주로 존재하며 그녀의 식신들은 여기에서 시작하게 된다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_HINA:
		printsub("카기야마 히나 - 숨어있는 액막이 인형 신",true,CL_hina);
		printsub("",true,CL_normal);
		printsub("히나는 액을 모아서 재앙을 방지하는 재앙신이다.",true,CL_normal);
		printsub("그녀로부터 액을 받아서 저주를 몸에 지니는 것으로 그녀의 권능을 얻을 수 있다.",true,CL_normal);
		printsub("던전을 탐험하는 것으로 신앙심을 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SATORI:
		printsub("코메이지 사토리 - 원령도 두려워하는 소녀",true,CL_danger);
		printsub("",true,CL_normal);
		printsub("사토리는 지령전의 주인으로 마음을 읽는 요괴이다.",true,CL_normal);
		printsub("사토리를 믿는다는 것은 그녀의 펫이 된다는 얘기와도 같고 그녀의 힘을 받을 수 있게 된다.",true,CL_normal);
		printsub("사토리는 방임주의이기때문에 전투에 직접 관련된 능력은 별로 주진 않는다.",true,CL_normal);
		printsub("그러나 그녀의 마음을 읽는 능력으로 던전의 지형 정보를 얻거나 위치를 알아낼 수 있다.",true,CL_normal);
		printsub("또한 상대의 마음 속으로부터 트라우마를 읽어내거나 상대의 생각을 통째로 읽어내 농락할수도 있다.",true,CL_normal);
		printsub("생각을 간파당한 상대는 모든 디버프 마법에 취약해지므로 정신술을 연마한 사람에게 도움이 될 것이다.",true,CL_normal);
		printsub("그녀의 애완동물들은 던전을 탐험하는 것으로 그녀의 호감을 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_YUUGI:
		printsub("호시구마 유우기 - 일컬어지는 괴력난신",true,CL_yuigi);
		printsub("",true,CL_normal);
		printsub("유우기는 지하의 옛도시에 살고 있는 오니이다. 유우기는 괴력난신의 오니로 강력한 힘을 신도에게 준다.",true,CL_normal);
		printsub("그녀의 힘은 근접 전투를 하면서 상대를 매치거나 집어던지는 등 레슬링같은 전투를 해낼 수 있다.",true,CL_normal);
		printsub("또한 오니의 힘으로 포효를 하여 상대를 벙어리로 만들거나 오니의 궁극기 또한 사용할 수 있게 된다.",true,CL_normal);
		printsub("단, 유우기는 신도가 마법의 힘에 의지해 싸우는 것을 싫어한다.",true,CL_normal);
		printsub("그녀의 신앙심은 전투에서 승리하는 것으로 얻을 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_TENSI:
		printsub("히나나이 텐시 - 비상비비상천의 아가씨",true,CL_tensi);
		printsub("",true,CL_normal);
		printsub("텐시는 유정천의 제멋대로인 천인 아가씨이다.",true,CL_normal);
		printsub("그녀는 지루한 천계생활에 따분해하던차 이 이변을 계기로 자신을 믿고자하는 신도들을 장난감처럼 취급한다.",true,CL_normal);
		printsub("텐시는 신도에게 어떠한 권능도 내려주지않는다. 모든 행동은 그녀의 변덕대로 이루어진다. ",true,CL_normal);
		printsub("신도가 항상 위험천만한 전투를 반복하여 그녀의 흥미를 최대한으로 끌어낸다면 강력한 도움을 받을 수 있다.",true,CL_normal);
		printsub("하지만 신도가 안이한 안전을 바란다면 곧 자신의 생각을 후회하게 될 것이다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_BYAKUREN:
		printsub("히지리 뱌쿠렌 - 봉인된 대마법사",true,CL_white_blue);
		printsub("",true,CL_normal);
		printsub("뱌쿠렌은 마계에 봉인되어있었던 대마법사로 환상향에 절인 명련사를 세워 불교의 가르침을 전한다.",true,CL_normal);
		printsub("그녀의 특기는 마법(특히 신체능력을 올리는 마법)이므로 신자들에게 마법을 주로 가르친다.",true,CL_normal);
		printsub("그녀의 권능으로 높은 수준의 지능을 얻거나 빠른 이동이 가능하거나 마법패널티를 상쇄받는다.",true,CL_normal);
		printsub("마법스킬들에 경험치를 투자하는 것으로 신앙심을 벌 수 있다.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SEIJA:
		printsub("키진 세이자 - 역습의 아마노자쿠",true,CL_seija);
		printsub("",true,CL_normal);
		printsub("세이자는 공개수배되어있는 아마노쟈쿠로 다양한 물건들을 들고 도망중이다.",true,CL_seija);
		printsub("세이자와 손을 잡는 것으로 그녀가 훔친 강력한 아이템들을 선물 받을 수 있다.",true,CL_seija);
		printsub("현재 궁지에 몰린 그녀는 세이자는 당신이 한편이 되는 것 자체를 최고로 환영할 것이다.",true,CL_seija);
		printsub("그러나 세이자는 어디까지나 신도를 이용할 생각이므로 당신을 방패로 삼을 것이고",true,CL_seija);
		printsub("그녀는 당신이 이용가치가 없어지면 언제든지 버릴 것이며 그녀를 믿으면 영원히 다른 신들의 질타를 받을 것이다.",true,CL_seija);
		printsub("그녀는 의심이 많고 강자를 싫어하므로 레벨이 9를 넘어가면 더이상 그녀를 믿을 수 없게 된다.",true,CL_seija);
		printsub("",true,CL_normal);
		break;
	case GT_LILLY:
		printsub("릴리 화이트 - 봄을 나르는 요정",true,CL_lilly);
		printsub("",true,CL_lilly);
		printsub("릴리 화이트는 봄을 알리는 요정으로 지나가는 것만으로도 봄꽃을 개화시킨다고한다.",true,CL_lilly);
		printsub("그녀는 요정의 권리를 신장시키기 위해 요정들에게 자신의 힘을 나눠주고있다.",true,CL_lilly);
		printsub("그녀를 믿는 것으로 떠돌이 요정들을 자신의 동료로 끌어모을 수 있다.",true,CL_lilly);
		printsub("동료가 된 요정은 당신이 죽을때까지 죽어도 되살아나면서 당신을 따를 것이다.",true,CL_lilly);
		printsub("릴리 화이트는 무슨 이유에서인지 스펠카드를 쓰는 것을 증오하므로 믿게되면 스펠카드를 쓸 수 없게 된다.",true,CL_lilly);
		printsub("본래 릴리화이트는 요정만의 신이지만 자발적인 다른 종족의 입교는 거부하지않는다.",true,CL_lilly);
		printsub("",true,CL_normal);
		break;
	default:
		printsub("버그신",true,CL_danger);
		printsub("",true,CL_normal);
		printsub("이 신은 버그다!",true,CL_normal);
		printsub("버그신은 게임 플레이에 지대한 영향을 주며 당신에게 깊은 스트레스를 준다.",true,CL_normal);
		printsub("이 신이 존재하는 것만으로도 게임이 크래쉬가 날 수 있으며 당신의 캐릭터를 삭제시킬지도 모른다.",true,CL_normal);
		printsub("버그신의 분노를 가라앉히려면 제작자에게 보고하는 수 밖에 없다.",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("버그신은 동방크롤에서 가장 악한 신이다.",true,CL_danger);
		printsub("",true,CL_normal);
		break;
	}
}


void God_show()
{
	if(you.god == GT_NONE)
	{
		printlog("당신은 아직 신을 믿고 있지 않다.",true,false,false,CL_normal);
		return;
	}
	deletesub();
	WaitForSingleObject(mutx, INFINITE);
	GodInfor(you.god);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("권능들:                                                           (비용)",true,CL_normal);
	printsub("",true,CL_normal);
	int level_ = pietyLevel(you.piety);
	switch(you.god)
	{
	case GT_ERROR:
		break;
	case GT_NONE:
		break;
	case GT_SHIKIEIKI:
		break;
	case GT_BYAKUREN:
		if(level_ >= 1 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("히지리는 당신이 배울 수 있는 마법레벨의 한계를 늘린다.                     (패시브)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("당신은 순간적으로 지능을 강화시킬 수 있다.                                   (신앙)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("당신은 근력이 강화되어 낮은 수준의 갑옷패널티의 마법실패율을 무시한다.     (패시브)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("히지리는 당신의 강화 마법들을 보조해준다.                                  (패시브)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("당신은 순간적으로 각력을 강화시킬 수 있다.                             (영력, 신앙)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		break;
	case GT_KANAKO:
		if(level_ >= 1 && !you.GetPunish(GT_KANAKO))
		{
			printsub("당신은 카나코님의 힘으로 돌진할 수 있다.                    (영력, 신앙)",true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_KANAKO))
		{
			printsub("당신은 카나코님의 기둥을 구현할 수 있다.                    (영력, 신앙)",true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_KANAKO))
		{
			printsub("당신은 카나코님의 바람의 힘을 휘감을 수 있다.               (영력, 신앙)",true,CL_help);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SUWAKO:
		if(level_ >= 1 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][0], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString2((swako_2_power)you.god_value[GT_SUWAKO][1], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString3((swako_3_power)you.god_value[GT_SUWAKO][2], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString4((swako_4_power)you.god_value[GT_SUWAKO][3], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString5((swako_5_power)you.god_value[GT_SUWAKO][4], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MINORIKO:
		if(level_ >= 0)
		{
			printsub("파워가 가득차도 음식을 먹을 수 있고 최대 파워를 오래 유지할 수 있다.       (패시브)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("당신이 파워가 가득차있을수록 체력과 영력회복속도가 빨라진다.               (패시브)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("미노리코는 당신에게 걸린 상태이상과 능력저하를 회복시켜준다.              (P, 신앙)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_MINORIKO))
		{ //이때부터 고구마 선물을 해준다.
			printsub("당신은 음식을 더 빨리 먹을 수 있고 먹을때 영력도 조금 회복한다.            (패시브)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("미노리코는 당신이 가진 음식을 소모하여 체력을 크게 회복할 수 있다.  (P, 음식, 신앙)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("미노리코는 당신이 음식을 먹은 직후 일시적으로 불,냉기저항을 1단계 준다.    (패시브)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MIMA:
		if(level_ >= 0 && !you.GetPunish(GT_MIMA))
		{ 
			printsub("신앙심에 비례해서 최대영력이 올라간다.                                     (패시브)",true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_MIMA))
		{
			printsub("적을 죽였을때 적의 세기에 따라 영력을 얻을 수 있다.                        (패시브)",true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_MIMA))
		{
			printsub("미마는 파괴술이 들어간 마법의 위력을 증가시킨다.                           (패시브)",true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_MIMA))
		{
			printsub("미마는 파괴술이 들어간 마법의 성공율을 증가시킨다.                         (패시브)",true,CL_green);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SHINKI:
		if(level_ >= 1 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("당신은 하급 마족 무리를 소환할 수 있다.                                    (P, 신앙)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("당신은 중급 마족을 소환할 수 있다.                                         (P, 신앙)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("적대적인 소환수의 행동을 일정확률로 방해한다.                               (패시브)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("당신은 상급 마족을 소환할 수 있다.                                         (P, 신앙)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("당신은 P를 주울때마다 체력과 영력이 차오른다.                               (패시브)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUUGI:
		if(level_ >= 0 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("취기가 오른 상태에서 약간의 체력회복력과 높은 회피를 얻는다.                (패시브)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("물약 1개를 술로 바꿔서 마실 수 있다.                                    (물약, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("전투중 가끔 상대를 잡는다. 잡으면 잡기기술을 신앙소모없이 쓸 수 있다.       (패시브)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("상대를 잡아 저먼 스플렉스를 걸 수 있다.                                    (P, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("상대를 잡아 집어 던질 수 있다.                                             (P, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("주변의 상대를 침묵시키는 강력한 포효를 할 수 있다.                         (P, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("오니의 궁극기, 삼보필살을 쓸 수 있다.                                      (P, 신앙)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SHIZUHA:
		if(level_ >= 0 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("시즈하는 적들이 잠에서 깨면서 외치는 확률을 줄여준다.           (패시브)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 움직이거나 적을 죽였을때 단풍잎의 자취를 남긴다.         (패시브)",true,CL_autumn);
			printsub("",true,CL_normal);
			printsub("단풍 위를 걸으면 매우 은밀하게 움직일 수 있다.                  (패시브) ",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 단풍 위에 서있는 모든 적에 혼란을 걸 수 있다.        (영력, 신앙)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 방어구를 단풍방어구로 바꿀 수 있다.                        (신앙)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 단풍 위를 걸을때 매우 빠르게 움직일 수 있다.             (패시브)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 6 && you.god_value[GT_SHIZUHA][0]==0 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("당신은 딱 한번 당신의 무기에 단풍브랜드를 부여할 수 있다.       (한번만)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		break;
	case GT_HINA:
		if(level_ >= 0)
		{ 
			printsub("당신은 시야내의 장비에 저주가 걸려있는지 확인하고 식별할 수 있다.                (패시브)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 장착중인 저주가 걸린 장비의 마이너스 인챈트를 플러스로 바꿀 수 있다.           (P)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 무기에 잠시동안 저주의 힘을 담아 강화 시킬 수 있다.                         (저주)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 방어구에 잠시동안 저주의 힘을 담아 모든 공격을 반사시킬 수 있다.            (저주)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 장신구에 잠시동안 저주의 힘을 담아 생명력을 치유 할 수 있다.                (저주)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_HINA))
		{ 
			printsub("당신은 저주된 아이템을 끼고 있으면 저주를 흩뿌리고 다닌다.                       (패시브)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 6 && you.god_value[GT_HINA][0]==0 && !you.GetPunish(GT_HINA))
		{
			printsub("당신은 딱 한번 당신의 무기에 저주브랜드를 부여할 수 있다.						   (한번만)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUKARI:
		if(level_ >= 0 && !you.GetPunish(GT_YUKARI))
		{
			printsub("틈새가 당신을 지켜본다.                                         (패시브)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 일정 데미지를 입으면 공간이동이 일어난다.                (패시브)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 틈새로부터 사격지원을 받을 수 있다.                  (영력, 신앙)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 틈새를 타고다닐 수 있다.                             (영력, 신앙)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 결계를 만들 수 있다.                                 (영력, 신앙)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUKARI))
		{
			printsub("당신은 잠시동안 차원을 고정시킬 수 있다.                    (영력, 신앙)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		break;
	case GT_EIRIN:
		if(!you.GetPunish(GT_EIRIN))
		{
			printsub("에이린은 물약들의 효과를 상승시켜준다.                          (패시브)",true,CL_small_danger);
			printsub("",true,CL_normal);
			printsub("좋은 물약위에서 기도하는 것으로 나쁜 물약을 만들 수 있다.         (물약)",true,CL_small_danger);
			printsub("",true,CL_normal);
			if(level_ >= 1)
			{
				printsub("당신은 다음의 물약을 마실때 추가 효과를 받는다.                 (패시브)",true,CL_small_danger);
				printsub(" └독물약 : 이동속도가 빨라진다.",true,CL_small_danger);
				if(level_ >= 2)
					printsub(" └능력치감소물약 : 체력을 회복한다.",true,CL_small_danger);
				if(level_ >= 3)
					printsub(" └혼란물약 : 영력을 회복한다.",true,CL_small_danger);
				if(level_ >= 4)
					printsub(" └감속물약 : 투명해진다.",true,CL_small_danger);
				if(level_ >= 5)
					printsub(" └마비물약 : 마비시간이 줄어들고 영격을 사용한다.",true,CL_small_danger);
				entersub();
				printsub("",true,CL_normal);
			}
		}
		if(level_ >= 2 && !you.GetPunish(GT_EIRIN))
		{
			printsub("당신의 물약을 던질 수 있다.                                    (P, 물약)",true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_EIRIN))
		{
			printsub("당신은 신체개조를 통해 능력치를 조절할 수 있다.                   (신앙)",true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_EIRIN))
		{
			printsub("당신은 부작용을 대가로 몸을 재생할 수 있다.              (P, 영력, 신앙)",true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUYUKO:
		if(level_ >= 1 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("당신은 유령을 불러들인다.                                      (패시브)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("원하는 위치에 유령들을 보낼 수 있다.                          (P, 영력)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("잠시동안 유령을 불러들이는 빈도를 높힐 수 있다.            (신앙, 영력)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("적 한명의 영혼을 잡을 수 있다.                             (신앙, 영력)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SATORI:
		if(level_ >= 0 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("당신은 투명을 볼 수 있다.                                       (패시브)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("당신은 상대의 트라우마를 끌어낼 수 있다.                          (신앙)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("당신은 적의 기억속에서 맵의 형태를 읽어낸다.                    (패시브)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("당신은 몹의 기척을 탐지할 수 있다.                              (패시브)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("적 한명의 생각을 완벽하게 독파할 수 있다.                   (시간, 신앙)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("사토리는 가끔 당신에게 먹이를 준다. 위험할수록 자주 준다.       (패시브)",true,CL_danger);
			printsub("",true,CL_normal); 
		}
		break;
	case GT_TENSI:
		if(level_ >= 0 && !you.GetPunish(GT_TENSI))
		{ 
			printsub("텐시의 행동은 예측할 수 없다!                                           ",true,CL_tensi);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SEIJA:
		break;
	case GT_LILLY:
		break;
	}
	changedisplay(DT_SUB_TEXT);
	ReleaseMutex(mutx);
	while(1)
	{
		int key_ = waitkeyinput(true);
		break;
	}
	changedisplay(DT_GAME);

}
bool God_pray(const list<item>::iterator it)
{
	switch(you.god)
	{
	case GT_ERROR:
		break;
	case GT_NONE:
		break;
	case GT_SHIKIEIKI:
		break;
	case GT_BYAKUREN:
		break;
	case GT_KANAKO:
		//if(it->type == ITM_FOOD && it->value1 == 0)
		//{
		//	printlog("P템은 불기둥에 휩싸여 사라졌다. 카나코는 공물을 받아들였다.",true,false,false,CL_small_danger);
		//	env[current_level].DeleteItem(it);
		//	if(randA(1))
		//	{
		//		you.PietyUpDown(1);	
		//		you.GiftCount(1);
		//	}
		//	return true;		
		//}
		break;
	case GT_SUWAKO:
		break;
	case GT_MINORIKO:
		break;
	case GT_MIMA:
		break;
	case GT_SHINKI:
		break;
	case GT_YUUGI:
		break;
	case GT_SHIZUHA:
		break;
	case GT_HINA:
		break;
	case GT_YUKARI:
		break;
	case GT_EIRIN:
		//if(it->type == ITM_FOOD && it->value1 == 0)
		//{
		//	printlog("P템은 불기둥에 휩싸여 사라졌다. 에이린은 공물을 받아들였다.",true,false,false,CL_small_danger);
		//	env[current_level].DeleteItem(it);
		//	you.PietyUpDown(1);	
		//	you.GiftCount(1);
		//	return true;		
		//}
		if(it->type == ITM_POTION && iden_list.potion_list[it->value1].iden && isGoodPotion((potion_type)it->value1)>0)
		{
			int per_ = randA(100);
			int result_ = (per_<15)?PT_CONFUSE:((per_<41)?PT_POISON:((per_<67)?PT_SLOW:(per_<93)?PT_DOWN_STAT:PT_PARALYSIS));
			printarray(false,false,false,CL_small_danger,3,it->GetName().c_str(),it->GetNameInfor().name_is(true),randA(2)?(randA(1)?"연기를 내며 ":"고약한 냄새를 풍기며 "):"빛을 내면서 ");
			it->value1 = result_;
			printarray(true,false,false,CL_small_danger,3,it->GetName().c_str(),it->GetNameInfor().name_by(true),"바뀌었다.");
			printarray(true,false,false,CL_small_danger,1,"에이린은 흡족히 여겼다.");
			you.PietyUpDown(it->num * 2);
			you.GiftCount(it->num * 1);
			return true;
		}
		break;
	case GT_YUYUKO:
		break;
	case GT_SATORI:
		break;
	case GT_TENSI:
		break;
	case GT_SEIJA:
		break;
	case GT_LILLY:
		break;
	}
	return false;		
}
bool god_punish(god_type god)
{

	if(wiz_list.wizard_mode == 1)
	{
		printarray(true,false,false,CL_small_danger,1,"***징벌!***");
	}
	switch(god)
	{
	case GT_ERROR:
		break;
	case GT_NONE:
		break;
	case GT_SHIKIEIKI:
		break;
	case GT_BYAKUREN:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//마나흡수
			rand_.push(1,25);//스탯드레인
			rand_.push(2,25);//슬로우
			switch(rand_.pop())
			{
			case 0:				
				you.MpUpDown(-you.max_mp);
				printarray(true,false,false,CL_white_blue,1,"뱌쿠렌의 분노로 당신의 영력이 흡수되었다!");
				break;
			case 1:
				(randA(1)?you.StatUpDown(-rand_int(1,5),STAT_STR,true):you.StatUpDown(-rand_int(3,7),STAT_INT,true));
				printarray(true,false,false,CL_white_blue,1,"뱌쿠렌의 분노로 당신의 스탯이 감소되었다!");
				break;
			case 2:
				you.SetSlow(rand_int(80,100));
				printarray(true,false,false,CL_white_blue,1,"뱌쿠렌의 분노로 당신은 느려졌다!");
				break;
			}
		}
		break;
	case GT_KANAKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,33);//건신초래돌
			rand_.push(1,33);//온바시라
			rand_.push(2,33);//몹 리콜
			switch(rand_.pop())
			{
			case 0:	
				{
					printarray(true,false,false,CL_help,1,"카나코는 당신에게 강력한 일격을 날렸다!");
					int damage_ = you.GetHp()*rand_int(40,80)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY,ATT_SMITE,name_infor("건신초래 돌",true));
					you.damage(temp_att, true);


				}	
				break;
			case 1:
				{
					for(int i = randA(3)+1; i>0 ; i--)
					{
						BaseSummon(MON_ONBASIRA, rand_int(10,30), true, false, 2, NULL, you.position, SKD_OTHER, -1);
					}
					printarray(true,false,false,CL_help,1,"카나코는 당신에게 온바시라를 꽂았다!");
					env[current_level].MakeNoise(you.position,16,NULL);
					break;
				}
			case 2:
				{
					int max_ = rand_int(3,5);
					deque<monster*> dq;
					for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
					{
						if(it->isLive() && !it->isUserAlly())
						{
							dq.push_back(&(*it));
							max_--;
							if(!max_)
								break;
						}
					}
					rand_shuffle(dq.begin(),dq.end());
					dif_rect_iterator rit(you.position,2,true);
					if(!dq.empty())
					{							
						printarray(true,false,false,CL_help,1,"카나코는 당신을 전투로 강제로 이끌었다!");
						for(int i = 0;!rit.end() && i < dq.size();rit++)
						{
							if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
							{
								dq[i]->SetXY(rit->x,rit->y);
								if(dq[i]->isYourShight())
								{
									dq[i]->AttackedTarget(&you);
								}
								i++;
							}
						}
					}
					else
					{
						printarray(true,false,false,CL_help,1,"카나코는 당신을 전투로 이끌려했지만 적당한 적이 없었다.");
					}
				}
				break;
			}
		}
		break;
	case GT_SUWAKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//저주
			rand_.push(1,50);//개구리
			switch(rand_.pop())
			{
			case 0:	
				{
					you.SetSlow(rand_int(4,20));
					you.SetPoison(rand_int(30,50)+randA(you.level*10),300,true);
					rand_rect_iterator rit(you.position,1,1);
					int smoke_ = rand_int(2,5);
					for(int i = 0; !rit.end() && i < smoke_;rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y, true))
						{
							env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_FOG,rand_int(6,12),0,NULL);
							i++;
						}
					}
					env[current_level].MakeSmoke(you.position,img_fog_dark,SMT_FOG,rand_int(6,12),0,&you);
					printarray(true,false,false,CL_swako,1,"스와코는 당신에게 저주를 내렸다!");
				}
				break;
			case 1:
				{
					int i = rand_int(2,4)+randA(you.level/6); 
					for(; i>0 ; i--)
					{
						if(monster *mon_ = BaseSummon((you.level > 10 && randA(3)==1)?MON_DEAGAMA:MON_FROG, rand_int(60,120), true, true, 2, NULL, you.position, SKD_OTHER, -1))
						{
							if(you.level>5)
								mon_->LevelUpdown(you.level-5);
						}
					}
					printarray(true,false,false,CL_swako,1,"스와코는 당신에게 적대적인 개구리 무리를 선물했다!");
				}
				break;
			}
		}
		break;
	case GT_MINORIKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//파워절반
			rand_.push(1,25);//체력감소와 병
			rand_.push(2,25);//능력치감소
			switch(rand_.pop())
			{
			case 0:				
				you.PowUpDown(-min(you.power,500)/2,true);
				printarray(true,false,false,CL_warning,1,"미노리코는 당신의 배고픔을 가속시켰다!");
				break;
			case 1:
				{
					you.hp=max(1,you.hp/2);	
					you.SetSick(rand_int(80,120));
					printarray(true,false,false,CL_warning,1,"미노리코는 당신의 건강을 빼앗아갔다!");
					break;
				}
			case 2:
				{
					for(int i=0;i<3;i++)
						you.StatUpDown(-rand_int(1,4),randA(2)?(randA(1)?STAT_STR:STAT_DEX):STAT_INT,true);
					printarray(true,false,false,CL_warning,1,"미노리코는 당신의 능력치를 깍아내렸다!");
					break;
				}
			}
		}
		break;
	case GT_MIMA:
		{
			random_extraction<int> rand_;
			rand_.push(0,33);//폭발
			switch(rand_.pop())
			{
			case 0:	
				{
					string str_ = "마법";
					textures* tex_ = &img_blast[2];
					attack_type type_ = ATT_NORMAL_BLAST;
					int damage_ = 15+you.level*5;
					switch(randA(5))
					{
					case 0:
						{
						str_ = "화염 마법";
						tex_ = &img_blast[0];
						type_ = ATT_FIRE_BLAST;
						break;
						}
					case 1:
						{
						str_ = "암석 마법";
						tex_ = &img_blast[1];
						type_ = ATT_NORMAL_BLAST;
						damage_ = damage_*4/5;
						break;
					case 2:
						str_ = "전기 마법";
						tex_ = &img_blast[2];
						type_ = ATT_ELEC_BLAST;
						break;
						}
					case 3:
						{
						str_ = "맹독 마법";
						tex_ = &img_blast[3];
						type_ = ATT_POISON_BLAST;
						damage_ = damage_*4/5;
						break;
						}
					case 4:
						{
						str_ = "냉기 마법";
						tex_ = &img_blast[4];
						type_ = ATT_COLD_BLAST;
						break;
						}
					case 5:
						{
						str_ = "마력";
						tex_ = &img_blast[5];
						type_ = ATT_COLD_BLAST;
						damage_ = damage_*3/5;
						break;
						}
					}
					printarray(true,false,false,CL_green,3,"미마가 강력한 ",str_.c_str(),"을 당신에 겨냥했다!");
					attack_infor temp_att(randC(3,damage_/3),damage_,99,NULL,PRT_ENEMY,type_,name_infor(str_.c_str(),true));
					BaseBomb(you.position, tex_,temp_att);
					env[current_level].MakeNoise(you.position,12,NULL);
				}	
				break;
			}
		}
		break;
	case GT_SHINKI:
		{
			random_extraction<int> rand_;
			rand_.push(0,100);//악마소환
			switch(rand_.pop())
			{
			case 0:
				{
					random_extraction<int> lowmidhigh_[3],perenct_;
					lowmidhigh_[0].push(MON_EVIL_EYE);
					lowmidhigh_[0].push(MON_LITTLE_IMP);
					lowmidhigh_[1].push(MON_LUIZE);
					lowmidhigh_[1].push(MON_ELIS);
					lowmidhigh_[1].push(MON_SARA);
					lowmidhigh_[2].push(MON_YUKI);
					lowmidhigh_[2].push(MON_MAI);
					lowmidhigh_[2].push(MON_YUUGENMAGAN);

					if(you.level<15)	
						perenct_.push(0,30-you.level*2);
					perenct_.push(1,3+you.level);
					if(you.level>13)	
						perenct_.push(2,you.level*3-40);


					int i = rand_int(1,3+you.level/9);
					for(; i>0 ; i--)
					{
						int demon_ = lowmidhigh_[perenct_.choice()].choice();
						if(monster *mon_ = BaseSummon(demon_, rand_int(90,120), true, true, 2, NULL, you.position, SKD_OTHER, -1))
						{
						}
					}
					printarray(true,false,false,CL_white_puple,1,"신키가 적대적인 마계인을 창조해냈다!");
				}
				break;
			}
		}
		break;
	case GT_YUUGI:
		{
			random_extraction<int> rand_;
			rand_.push(0,25);//술
			rand_.push(1,25);//자이언트 스윙
			rand_.push(2,50);//오니 소환
			switch(rand_.pop())
			{
			case 0:			
				printarray(true,false,false,CL_yuigi,1,"유우기가 강한 술을 당신에게 강제로 먹였다!");	
				you.SetConfuse(rand_int(9,30));
				you.SetDrunken(rand_int(50,100));
				break;
			case 1:
				{
					printarray(true,false,false,CL_yuigi,1,"유우기가 당신을 집어던졌다!");
					you.Blink(40);
					int damage_ = you.GetHp()*rand_int(30,60)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY,ATT_SMITE,name_infor("자이언트스윙",true));
					you.damage(temp_att, true);
				}
				break;
			case 2:
				{
					printarray(true,false,false,CL_yuigi,1,"유우기가 당신을 벌하기위해 동료 오니들을 불러냈다!");
					random_extraction<int> oni_;
					oni_.push(MON_ONI);
					oni_.push(MON_BLUE_ONI);
					int i = rand_int(1+you.level/10,1+you.level/5);
					for(; i>0 ; i--)
					{
						int time_ = rand_int(40,60);
						if(monster *mon_ = BaseSummon(oni_.choice(), time_, true, true, 2, NULL, you.position, SKD_OTHER, -1))
						{
							if(randA(99)<max(0,200-you.level*30))
								mon_->SetSlow(time_);
							if(randA(99)<max(0,you.level*4-28))
								mon_->SetMight(time_);
							if(randA(99)<max(0,you.level*5-65))
								mon_->SetHaste(time_);
						}
					}
				}
				break;
			}
		}
		break;
	case GT_SHIZUHA:
		{
			random_extraction<int> rand_;
			rand_.push(0,33);//혼란
			rand_.push(1,33);//암습
			rand_.push(2,33);//슬로우
			switch(rand_.pop())
			{
			case 0:			
				printarray(true,false,false,CL_autumn,1,"시즈하는 당신에 광기의 낙엽을 흩날렸다!");	
				you.SetConfuse(rand_int(12,45), true);
				break;
			case 1:
				{				
					rand_rect_iterator rit(you.position,2,2);
					int i = 5+randA(5); 
					for(;!rit.end() && i> 0;rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y))
						{	
							int rand_ = randA(1);
							env[current_level].MakeFloorEffect(coord_def(rit->x,rit->y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,rand_int(20,30),&you);
						}
						i--;
					}
					int rand_ = randA(1);
					env[current_level].MakeFloorEffect(coord_def(you.position.x,you.position.y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,3+you.piety/20,&you);
	
					printarray(true,false,false,CL_autumn,1,"시즈하가 당신의 등 뒤를 찔렀다!");
					int damage_ = you.GetHp()*rand_int(30,60)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY,ATT_SMITE,name_infor("암습",true));
					you.damage(temp_att, true);
					you.SetBuff(BUFFSTAT_RF,BUFF_AUTUMN_RF,-1,1);
				}
				break;
			case 2:
				{
					printarray(true,false,false,CL_autumn,1,"시즈하가 엄청난 소음과 함께 당신을 지목했다!");
					env[current_level].MakeNoise(you.position,30,NULL);
					int time_ = rand_int(40,60);
					you.SetGlow(time_);
					you.SetSlow(time_);
				}
				break;
			}
		}
		break;
	case GT_HINA:
		{
			random_extraction<int> rand_;
			rand_.push(0,25);//액
			rand_.push(1,50);//장비액
			rand_.push(2,25);//혼란
			switch(rand_.pop())
			{
			case 0:		
				{
					you.SetSlow(rand_int(4,20));
					you.SetPoison(rand_int(20,40)+randA(you.level*8),200,true);
					rand_rect_iterator rit(you.position,1,1);
					int smoke_ = rand_int(3,7);
					for(int i = 0; !rit.end() && i < smoke_;rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y, true))
						{
							env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_CURSE,rand_int(6,12),0,NULL);
							i++;
						}
					}
					env[current_level].MakeSmoke(you.position,img_fog_dark,SMT_CURSE,rand_int(6,12),0,&you);
					printarray(true,false,false,CL_hina,1,"히나는 액을 당신에게 직접 주입했다!");
				}
				break;
			case 1:
				{
					bool curse_ = false;
					deque<int> dq;
					for(int i=ET_FIRST;i<ET_LAST;i++)
					{
						if(i != ET_THROW)
							dq.push_back(i);
					}	
					rand_shuffle(dq.begin(),dq.end());
					printarray(false,false,false,CL_hina,1,"히나는 당신의 장비에 액을 주입했다! ");


					for(int i = 0; i<dq.size() ; i++)
					{
						if(you.equipment[dq[i]])
						{
							string before_name = you.equipment[dq[i]]->GetName(); //저주받기전 이름
							if(you.equipment[dq[i]]->Curse(true,(equip_type)dq[i]))
							{
								enterlog();
								printlog("장착하고 있던 ",false,false,false,CL_small_danger);		
								printlog(before_name,false,false,false,CL_small_danger);	
								printlog(you.equipment[dq[i]]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
								printlog("검게 빛났다.",true,false,false,CL_small_danger);		
								curse_ = true;
								break;
							}
						}
					}
					if(!curse_)
					{
						printarray(true,false,false,CL_hina,1,"그러나 아무일도 일어나지 않았다.");

					}
				}
				break;
			case 2:
				{
					printarray(true,false,false,CL_autumn,1,"히나는 당신을 빙빙 돌렸다!");	
					you.SetConfuse(rand_int(12,45), true);
					break;
				}
			}
		}
		break;
	case GT_YUKARI:
		{
			random_extraction<int> rand_;
			rand_.push(0,25);//공간이동
			rand_.push(1,50);//장비액
			rand_.push(2,25);//혼란
			switch(rand_.pop())
			{
			case 0:		
				{
					you.SetConfuse(rand_int(6,18), true);
					you.Teleport();
					printarray(true,false,false,CL_yukari,1,"유카리는 당신을 강제로 텔레포트 시켰다!");
				}
				break;
			case 1:
				{					
					you.SetStasis(rand_int(20,30));
					int max_ = rand_int(2,3);
					deque<monster*> dq;
					for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
					{
						if(it->isLive() && !it->isUserAlly())
						{
							dq.push_back(&(*it));
							max_--;
							if(!max_)
								break;
						}
					}
					rand_shuffle(dq.begin(),dq.end());
					dif_rect_iterator rit(you.position,2,true);
					if(!dq.empty())
					{							
						printarray(true,false,false,CL_yukari,1,"유카리는 당신의 주변에 몹들을 강제로 이동시켰다!");
						for(int i = 0;!rit.end() && i < dq.size();rit++)
						{
							if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
							{

								dq[i]->SetXY(rit->x,rit->y);
								textures* t_ = &img_effect_schema[randA(2)];
								env[current_level].MakeFloorEffect(coord_def(rit->x,rit->y),t_,t_,FLOORT_SCHEMA,rand_int(20,30),&you);

								if(dq[i]->isYourShight())
								{
									dq[i]->AttackedTarget(&you);
								}
								i++;
							}
						}
					}
					else
					{
						printarray(true,false,false,CL_yukari,1,"유카리는 당신의 공간이동을 막았다!");
					}
				}
				break;
			case 2:
				{

					printarray(true,false,false,CL_yukari,1,"유카리는 당신을 감시하는 이형의 눈을 소환했다!");
					int i = rand_int(2+you.level/8,3+you.level/5);
					for(; i>0 ; i--)
					{
						int time_ = rand_int(40,60);
						if(monster *mon_ = BaseSummon(MON_SCHEMA_EYE, time_, true, true, 3, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level,3);
						}
					}
					break;
				}
			}
		}
		break;
	case GT_EIRIN:
		{
			random_extraction<int> rand_;
			rand_.push(0,66);//물약먹이기
			rand_.push(1,33);//강제실험
			switch(rand_.pop())
			{
			case 0:
				{
					random_extraction<potion_type> potion_;	
					potion_.push(PT_DOWN_STAT);
					potion_.push(PT_PARALYSIS);
					potion_.push(PT_SLOW);
					potion_.push(PT_CONFUSE);
					potion_.push(PT_POISON);
					potion_type p_ = potion_.choice();
					printarray(true,false,false,CL_small_danger,3,"에이린은 당신에게 억지로 ",potion_iden_string[p_],"물약을 먹였다!");
					drinkpotion(p_);
				}
				break;
			case 1:
				{
					printarray(true,false,false,CL_small_danger,1,"에이린이 당신의 몸에 강제로 실험을 했다!");
					you.SetEirinHeal(you.max_hp*rand_int(70,80)/100,true);
					for(int i=0;i<3;i++)
						you.StatUpDown(-rand_int(1,4),randA(2)?(randA(1)?STAT_STR:STAT_DEX):STAT_INT,true);
				}
				break;
			}
		}
		break;
	case GT_YUYUKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//유령
			switch(rand_.pop())
			{
			case 0:
				{
					int i = rand_int(2+randA(you.level/10),5)+randA(you.level/3); 
					for(; i>0 ; i--)
					{
						if(monster *mon_ = BaseSummon(MON_GHOST, rand_int(20,40), true, true, 4, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level-1,4.0f,1.5f);
							mon_->image = &img_mons_ghost[randA(2)];
						}
					}
					printarray(true,false,false,CL_yuyuko,1,"유유코는 당신의 주변에 유령을 끌어모았다!");
				}
				break;
			}
		}
		break;
	case GT_SATORI:
		break;
	case GT_TENSI:
		tensi_action();
		break;
	case GT_SEIJA:
		break;
	case GT_LILLY:
		break;
	}
	return false;		
}