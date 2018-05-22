//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: seija.cpp
//
// 내용: 세이자 내용
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "seija.h"
#include "environment.h"
#include "enum.h"
#include "skill_use.h"
#include "key.h"
#include "god.h"
#include "note.h"
#include "weapon.h"
#include "potion.h"
#include "evoke.h"
#include "book.h"




bool seija_gift()
{
	int seija_level_ = 7-pietyLevel(you.piety);

	if(seija_level_ == 6)
	{
		printlog(seija_talk(GT_NONE, seija_level_), true,false,false,CL_seija);
		
		MoreWait();
		
		printarray(true,false,false,CL_danger,3,"당신은 ", GetGodString(you.god), "로부터 버려졌다!");
	
		//you.PunishUpDown(30, you.god , true);
	
		char temp[200];
		sprintf_s(temp,200,"%s로부터 버려졌다.",GetGodString(you.god));
		AddNote(you.turn,CurrentLevelString(),temp,CL_small_danger);

		for(int level_ = pietyLevel(you.piety);level_>=0;level_--)
			GetGodAbility(level_, false);
		you.Ability(SKL_ABANDON_GOD,true,true);
		you.god = GT_NONE;

		item_infor t;
		env[current_level].MakeItem(you.position, makeitem(ITM_MISCELLANEOUS, 0, &t, EVK_MAGIC_HAMMER));
		printlog("...세이자가 마지막 선물로 요술망치를 주고 갔다.", true, false, false, CL_dark_good);
		return true;
	}

	int temp = you.Ability(SKL_SEIJA_GIFT,true,true);
	
	if(temp)
	{	
		printlog("선물을 받지않은지 너무 오랜시간이 지나서 선물이 취소되었다.",true,false,false,CL_small_danger);
		MoreWait();
		printlog(seija_talk(GT_NONE, seija_level_), true,false,false,CL_seija);
		you.StepUpDownPiety(-1);
		return true;
	}
	else
	{
		printlog("이제 세이자로부터 선물을 요구할 수 있다. ",false,false,false,CL_seija);
		printlog("(a키로 선물을 요청)",true,false,false,CL_help);
		MoreWait();

		you.Ability(SKL_SEIJA_GIFT,true,false);
		return true;

	}
}
const char* seija_god_string(int god, int num) {

	switch (god)
	{
	case GT_BYAKUREN:
		switch (num) {
		case 0: return "뱌쿠렌: 무작위 마법책을 몇 권 받습니다.";
		case 1: return "뱌쿠렌은 징벌로 당신을 느리게하거나 영력이나 스탯을 일시적으로 감소시킵니다.";
		case 2: return "또한 뱌쿠렌의 징벌중엔 항상 일정 확률로 시전한 마법이 실패합니다.";
		}
	case GT_JOON_AND_SION:
		switch (num) {
		case 0: return "죠온&시온: 무작위 부적을 약간 받습니다.";
		case 1: return "죠온과 시온은 당신의 아이템을 낭비하고 잃어버리도록 만듭니다.";
		case 2: return "또한 징벌로 당신에게 강제로 빙의되어 체력, 영력이나 파워를 잃게 만듭니다.";
		}
	case GT_KANAKO:
		switch (num) {
		case 0: return "카나코: 무작위 무작위 무기를 여럿을 받습니다.";
		case 1: return "카나코는 징벌로 당신에게 데미지를 주거나 온바시라를 꽂아서 발을 묶거나";
		case 2: return "던전의 적대적인 몬스터들을 당신의 주위로 불러들이기도 합니다.";
		}
	case GT_SUWAKO:
		switch (num) {
		case 0: return "스와코: 스펠카드를 몇 개 받습니다.";
		case 1: return "스와코는 당신에게 저주를 걸어 저항할 수 없는 감속과 독을 걸거나";
		case 2: return "당신의 주변에 적대적인 개구리들을 소환합니다.";
		}
	case GT_MINORIKO:
		switch (num) {
		case 0: return "미노리코: 다수의 고구마를 받습니다.";
		case 1: return "미노리코는 징벌로 당신의 파워를 절반으로 만들거나 건강을 빼앗아";
		case 2: return "병에 걸리게하기도하며 능력치를 일시적으로 감소시킬 수 있습니다.";
		}
	case GT_MIMA:
		switch (num) {
		case 0: return "미마: 미마의 봉인서를 받습니다.";
		case 1: return "미마는 징벌로 당신에게 다양한 속성의 파괴마법을 직접 날립니다.";
		case 2: return "또한 미마에 징벌을 받는 동안엔 모든 마법의 파워가 절반이 됩니다.";
		}
	case GT_SHINKI:
		switch (num) {
		case 0: return "신키: 영격두루마리 몇개를 받습니다.";
		case 1: return "신키는 징벌로 당신의 주변에 적대적인 마계인들을 소환합니다.";
		case 2: return "또한 징벌중엔 적이 P아이템을 떨어뜨릴 확률을 낮춥니다.";
		}
	case GT_YUUGI:
		switch (num) {
		case 0: return "유우기: 무작위 방어구를 여럿 받습니다.";
		case 1: return "유우기는 당신을 강제로 취하게 만들거나 데미지와 함께 집어던지거나";
		case 2: return "당신 주변에 강력한 오니를 소환하기도 합니다.";
		}
	case GT_SHIZUHA:
		switch (num) {
		case 0: return "시즈하: 단풍브랜드의 무기를 받습니다.";
		case 1: return "시즈하는 징벌로 당신을 혼란시키거나 큰 데미지를 주거나 큰 소음과 함께";
		case 2: return "당신을 감속시킵니다. 단풍잎을 밟으면 큰 소음이 나며 화염에 약해집니다.";
		}
	case GT_HINA:
		switch (num) {
		case 0: return "히나: 무작위 반지를 여럿 받습니다.";
		case 1: return "히나는 징벌로 당신에 저항불가능한 독과 감속을 걸거나 당신의 장비에 저주를";
		case 2: return "걸기도하며 혼란을 겁니다. 징벌중엔 저주해제는 항상 실패할 가능성이 생깁니다.";
		}
	case GT_YUKARI:
		switch (num) {
		case 0: return "유카리: 공간이동 소모품을 여럿을 받습니다.";
		case 1: return "유카리는 징벌로 혼란과 함께 공간이동을 시키거나 공간이동을 금지시킨후 주변에";
		case 2: return "적들을 불러오기도하며 이형의 눈을 소환시키기도 합니다.";
		}
	case GT_EIRIN:
		switch (num) {
		case 0: return "에이린: 무작위 물약 더미를 받습니다.";
		case 1: return "에이린은 당신에 나쁜 물약을 먹이거나 당신에게 수상한 실험을 하여 부작용을";
		case 2: return "남깁니다. 또한 징벌중에 당신이 마시는 물약의 효과가 일정 확률로 사라집니다.";
		}
	case GT_YUYUKO:
		switch (num) {
		case 0: return "유유코: 무작위 발동템들을 받습니다.";
		case 1: return "유유코는 징벌로 당신의 주변에 많은 적대적인 유령들을 소환시킵니다.";
		case 2: return "소환되는 유령들은 당신이 강해질수록 강해집니다.";
		}
	case GT_SATORI:
		switch (num) {
		case 0: return "사토리: 식별두루마리 여럿을 받습니다.";
		case 1: return "사토리는 당신을 징벌하진 않지만 무언가를 찾는 전단지를 던전에 뿌립니다.";
		case 2: return "이 일정시간동안 뿌려지는 전단지는 던전의 아이템과 교체되어 생성됩니다.";
		}
	case GT_TENSI:
		switch (num) {
		case 0: return "텐시: 무작위 아이템을 여럿 받습니다.";
		case 1: return "텐시는 징벌일지라도 당신을 언제나 가지고 놀 것입니다.";
		case 2: return "그 징벌은 평소의 텐시의 행동보다 조금 더 나쁜 효과일 확률이 높습니다.";
		}
	case GT_SEIJA:
		switch (num) {
		case 0: return "세이자: 나로부터 받을 것은 없다!";
		case 1: return "아마 이 선택지는 버그입니다.";
		case 2: return "";
		}
	case GT_LILLY:
		switch (num) {
		case 0: return "릴리: 탄막 뭉치를 받습니다";
		case 1: return "릴리는 징벌로 당신의 주변에 적대적인 요정들을 소환하거나";
		case 2: return "당신을 약화시켜 일시적으로 공격력과 마법의 파워를 절반으로 낮춥니다.";
		}
	case GT_MIKO:
		switch (num) {
		case 0: return "미코: 아티펙트 망토를 하나 받습니다.";
		case 1: return "미코는 징벌로 당신의 최대체력을 일시적으로 절반으로 줄이거나";
		case 2: return "감속을 걸거나 화염과 냉기저항을 일시적으로 한단계 낮춥니다.";
		}
	case GT_OKINA:
		switch (num) {
		case 0: return "오키나: 약간의 성역 두루마리를 받습니다.";
		case 1: return "오키나는 당신의 주변에 적대적인 백댄서를 소환하여 주변의 몬스터들을";
		case 2: return "응원하거나 당신의 체력과 영력을 흡수합니다.";
		}
	case GT_JUNKO:
		switch (num) {
		case 0: return "순호: 무기강화와 방어구강화 두루마리를 여럿 받습니다.";
		case 1: return "순호는 징벌로 당신을 약화시키거나 감속을 시키거나 당신의 능력치를";
		case 2: return "일시적으로 감소시킵니다.";
		}
	case GT_ERROR:
	case GT_NONE:
	default:
		switch (num) {
		case 0: return "버그신: 이것을 선택하면 죽습니다.";
		case 1: return "대부분은 버그입니다.";
		case 2: return "";
		}
	
	}
	return "버그";
}


void seija_real_gift(int key_)
{	
	switch(key_)
	{
		case GT_BYAKUREN: //무작위 책 2~4개
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{
					random_extraction<int> rand_;

					for(int j=SKT_SPELLCASTING+1; j<SKT_EVOCATE;j++)
					{
						rand_.push(i, you.GetSkillLevel(j, false)>15?15:(you.GetSkillLevel(j, false)>1?5:1));
					}
					book_list book_ = BOOK_FIRST;
					for(int j=SKT_SPELLCASTING+1; j<SKT_EVOCATE;j++)
					{
						book_ = SchoolToBook((skill_type)rand_.pop());
						if(!iden_list.books_list[book_])
						{
							break;
						}
					}
					
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, book_));
				}
			}
			break;
		case GT_KANAKO: //무작위 무기 3~5개
			{
				for(int i = rand_int(3,5); i > 0; i--)
				{
					kanako_gift(false);
				}
			}
			break;
		case GT_SUWAKO: //무작위 스펠카드 2~4개
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_SPELL, 0, &t, randA(SPC_V_MAX-1)));
				}
			}
			break;
		case GT_MINORIKO: //고구마 10~30개
			{
				for(int i = 10; i > 0; i--)
				{	
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_FOOD, 0, &t, 1));
				}
			}
			break;
		case GT_MIMA: //미마의 봉인서
			{
				for(int i = 1; i > 0; i--)
				{	
					item_infor t;
					item *it = env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, BOOK_TEST_ANNIHILATE));
					it->Identify();
				}
			}
			break;
		case GT_SHINKI: //영격두루마리 2~4장
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{	
					item_infor t;
					item *it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_SOUL_SHOT));
					it->Identify();
				}
			}
			break;
		case GT_YUUGI:
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{	
					armour_gift(false, false);
				}
			}
			break;
		case GT_SHIZUHA:
			{
				random_extraction<int> rand_;

				for(int i=SKT_SHORTBLADE;i<=SKT_SPEAR;i++)
				{
					rand_.push(i-SKT_SHORTBLADE, you.GetSkillLevel(i, false) +1);
				}
				item_infor t;
				item* it = env[current_level].MakeItem(you.position,makeitem((item_type)(rand_.pop()), randA(2)?1:0, &t));
				it->value5 = WB_AUTUMN;
			}
			break;
		case GT_HINA:
			{
				for(int i = rand_int(2,3); i > 0; i--)
				{	
					jewelry_gift(false, true, false);
				}
			}
			break;
		case GT_YUKARI://공간두루마리 3~7장 순간이동두루마리 0~3장
			{
				for(int i = rand_int(3,7); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_TELEPORT));
					it->Identify();
				}
				for(int i = rand_int(0,3); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_BLINK));
					it->Identify();
				}
			}
			break;
		case GT_EIRIN: //포션 6~12개
			{
				for(int i = rand_int(6,12); i > 0; i--)
				{					
					potion_type type_= goodbadpotion(randA(2)>1?1:(randA(60)?2:3));
					
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t,(int)type_));
				}
			}
			break;
		case GT_YUYUKO: //무작위 발동템 2개
			{
				random_extraction<int> rand_;

				for (int i = 0; i < EVK_MAX; i++) {
					if (i != EVK_MAGIC_HAMMER && i != EVK_SKY_TORPEDO && i != EVK_CAMERA
						) {
						rand_.push(i);
					}
				}
				for(int i = 2; i > 0; i--)
				{
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_MISCELLANEOUS, 0, &t,rand_.pop()));
				}
			}
			break;
		case GT_SATORI: //식별두루마리 7~12개
			{
				for(int i = rand_int(7,12); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_IDENTIFY));
					it->Identify();
				}
			}
			break;
		case GT_TENSI: //무작위 아이템 4~8개... 무려 던전 1층의!!
			{				
				for(int i = rand_int(4,8); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,CreateFloorItem(0,&t));
				}
			}
			break;
		case GT_LILLY: //탄막뭉치
			{				
				for(int i = rand_int(4,7); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_THROW_TANMAC, 0, &t));
				}
			}
			break;
		case GT_JOON_AND_SION:
		{
			for (int i = 2; i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_AMULET, 0, &t));
			}
		}
		break;
		case GT_MIKO:
		{
			for (int i = 1; i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_ARMOR_CLOAK, 0, &t));
				MakeArtifact(it, 3); //다른 아이템보다 효과가 좋음
			}
		}
		break;
		case GT_OKINA:
		{
			for (int i = rand_int(2,4); i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_SCROLL, 0, &t, SCT_SANTUARY));
				it->Identify();
			}
		}
		break;
		case GT_JUNKO:
		{
			for (int i = rand_int(3, 6); i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_SCROLL, 0, &t, SCT_ENCHANT_WEAPON_1));
				it->Identify();
			}
			for (int i = rand_int(2, 3); i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_SCROLL, 0, &t, SCT_ENCHANT_ARMOUR));
				it->Identify();
			}
		}
		break;
	}
}

const char* seija_summon_buff() {

	switch (randA(9))
	{
	case 0:
		return "세이자: 도망쳐!";
	case 1:
		return "세이자: 정면전은 승산이 없다고!";
	case 2:
		return "세이자: 발을 빠르게 해줄테니까 잘 도망쳐보라고";
	case 3:
		return "세이자: 그 놈들은 느림보니까 따돌려버려!";
	case 4:
		return "세이자: 싸울 생각은 아니지?";
	case 5:
		return "세이자: 벌써 추격이 붙었나";
	case 6:
		return "세이자: 언제나의 추격자들일뿐이야, 따돌리자고";
	case 7:
		return "세이자: 수로 밀어붙이다니 반칙아니야?";
	case 8:
		return "세이자: 그래봤자 너희들은 우릴 잡을 수 없지";
	case 9:
		return "세이자: 너넨 질리지도 않냐!";
	}

	return "세이자: 이대로 도망쳐!";
}


const char* seija_talk(god_type god_, int piety)
{
	if(piety >= 1 && piety <= 3)
	{
		switch(god_)
		{
		
		case GT_JOON_AND_SION:
			switch(randA(3))
			{
			case 0:
				return "세이자: 그 녀석들의 물건은 별로 가지고싶지않은데 너라도 쓸래?";
			case 1:
				return "세이자: 그 녀석들은 어차피 역병신이니 내가 안 훔쳤어도 잃어버릴거야";
			case 2:
				return "세이자: 나보다 미움 받는 애들은 흔치않은데 말이지";
			case 3:
				return "세이자: 별로 가까이 가고싶지 않은 녀석들이란 말이지";
			}
			break;
		case GT_BYAKUREN:
			switch(randA(3))
			{
			case 0:
				return "세이자: 요괴, 인간에게 평등하게? 딱봐도 위선자의 느낌이 나는군!";
			case 1:
				return "세이자: 절에 물건을 훔치러갔을때 술이 잔뜩 놓여있었다고! 파계승 집단이 분명해!";
			case 2:
				return "세이자: 그 절에 있었던 마법책들이야. 숨어들어가다가 야마비코 하나가 짖어서 혼났다니깐";
			case 3:
				return "세이자: 그 곳의 주지승에겐 위험한 분위기가 흘러나왔지만... 잘 도망쳐왔지!";
			}
			break;
		case GT_KANAKO:
			switch(randA(3))
			{
			case 0:
				return "세이자: 뱀의 혀처럼 말재간이 뛰어난 신이었지. 나에겐 설득은 안통하지만 말이야";
			case 1:
				return "세이자: 이 많은 고물들이 쓸모가 있을까? 원한다면 주겠지만";
			case 2:
				return "세이자: 그 신 말이야. 센스가 촌스럽다고 센스가";
			case 3:
				return "세이자: 그 기둥으로부터 도망치는건 꽤 어려웠지... 잘 피해보라고!";
			}
			break;
		case GT_SUWAKO:
			switch(randA(3))
			{
			case 0:
				return "세이자: 이런 꼬맹이도 신이었던거야? 그렇게 쎄보이진않았는데";
			case 1:
				return "세이자: 그 곳엔 개구리가 참 많았지. 별로 좋아하진 않는데 말이야";
			case 2:
				return "세이자: 그 재앙신. 보기보단 위험하다고";
			case 3:
				return "세이자: 이 물건엔 재앙이 따라오는데 괜찮겠어?";
			}
			break;
		case GT_MINORIKO:
			switch(randA(3))
			{
			case 0:
				return "세이자: 뭐 도망생활이라도 밥은 챙겨먹어야지. 여기 좀 나눠줄게";
			case 1:
				return "세이자: 난 이제 고구마는 질려서말이야, 나눠줄까 생각하고 있었다고";
			case 2:
				return "세이자: 이 고구마들은 그 풍년의 신에게... 어라? 이름이 뭐였지?";
			case 3:
				return "세이자: 배고팠나보지? 좀 나눠주지";
			}
			break;
		case GT_MIMA:
			switch(randA(3))
			{
			case 0:
				return "세이자: 궁극의 마법이 적혀있다고 하더군. 소중하게 쓰라고";
			case 1:
				return "세이자: 이게 그 스파크인지 뭔지가 적혀있는 책인가? 반칙수준이라고 그 마법";
			case 2:
				return "세이자: 악령? 악령이 쓴 책이라고? 읽으면 저주받는건 아니겠지?";
			case 3:
				return "세이자: 물건 보는 눈은 있구만 그래. 이건 좀 귀한 책이지";
			}
			break;
		case GT_SHINKI:
			switch(randA(3))
			{
			case 0:
				return "세이자: 마계의 신? 그 어벙벙하게 생긴 녀석이?";
			case 1:
				return "세이자: 생각보다 마계가 멀쩡해서 놀랐다고. 기분나쁘게 생긴 괴물을 생각했는데";
			case 2:
				return "세이자: 마계는 길을 잃기 쉽다고. 혹시 가게되면 조심하는게 좋을껄";
			case 3:
				return "세이자: 마족들이 진절머리나도록 쫓아오더라고... 이걸 줄테니 좀 따돌려 줄래?";
			}
			break;
		case GT_YUUGI:
			switch(randA(3))
			{
			case 0:
				return "세이자: 오니의 상대는 피하고 싶어서 말이지. 있는 힘껏 도망치라고";
			case 1:
				return "세이자: 이 갑옷들은 오니들의 보물중 하나지. 나에게 걸리면 금방이라고";
			case 2:
				return "세이자: 갑옷은 필요해질꺼야. 오니의 주먹을 정면으로 맞고 버티려면 말이지";
			case 3:
				return "세이자: 난 오니들에게 미움받는 성격같아서 말이야. 좀 대신 상대해줬으면 하는데";
			}
			break;
		case GT_SHIZUHA:
			switch(randA(3))
			{
			case 0:
				return "세이자: 단풍은 떨어지면 보잘것 없지. 너도 그렇게 생각하지?";
			case 1:
				return "세이자: 존재감이 없을거 같은 신이었지. 자 받아";
			case 2:
				return "세이자: 글쎄 이걸 가져올때 누가 꼭 지켜보고있다는 느낌이 들었단 말이야?";
			case 3:
				return "세이자: 역시 싸움은 몰래 등뒤에서 찌르는게 최고지. 너도 그렇게 생각하지?";
			}
			break;
		case GT_HINA:
			switch(randA(3))
			{
			case 0:
				return "세이자: 마침 이런 저주받은 물건은 나도 필요없었어. 전부 줄게";
			case 1:
				return "세이자: 꽤 값이 나가는 반지같아 보이긴하는데, 끼면 소름끼칠거같고 싫어";
			case 2:
				return "세이자: 일부러 자신의 장비에 저주를 거는 사람이 있다고? 에이 설마";
			case 3:
				return "세이자: 필요하면 주겠지만 저주는 조심하라고 ";
			}
			break;
		case GT_YUKARI:
			switch(randA(3))
			{
			case 0:
				return "세이자: 이 기분나쁜 요괴랑은 별로 연관되고 싶지 않았는데";
			case 1:
				return "세이자: 이 물건들을 훔치러갔을때 이 요괴는 잠자고있었지";
			case 2:
				return "세이자: 도망칠때는 이 공간이동 아이템만한게 없지. 유용하게 쓰라고";
			case 3:
				return "세이자: 공간이동은 유용하지만 멀미가 심하단말이야. 우웩";
			}
			break;
		case GT_EIRIN:
			switch(randA(3))
			{
			case 0:
				return "세이자: 그 약사의 집에서 훔쳐온 물약들이야. 무슨 물약인지는 잘 모르겠지만";
			case 1:
				return "세이자: 약사라면서? 왜 그렇게 독을 많이 가지고 있는 거지?";
			case 2:
				return "세이자: 그 약사의 방에 처음 보는 이상한 실험도구도 잔뜩있었어. 위험해보여서 무시했지";
			case 3:
				return "세이자: 상황을 타개하는데는 물약만큼 든든한게 없지. 너도 조심하라고!";
			}
			break;
		case GT_YUYUKO:
			switch(randA(3))
			{
			case 0:
				return "세이자: 그 긴 계단에 다시 올라가고 싶진 않더라";
			case 1:
				return "세이자: 이 물건을 훔치고 나서부턴 유령이 지겹게 꼬이더군";
			case 2:
				return "세이자: 죽음을 다루는 망령? 불길하네";
			case 3:
				return "세이자: 유령정도는 쉽게 따돌릴 수 있겠지? 믿는다고 파트너";
			}
			break;
		case GT_SATORI:
			switch(randA(3))
			{
			case 0:
				return "세이자: 마음을 읽는 요괴라... 기분 나쁜 요괴구만";
			case 1:
				return "세이자: 애완동물을 기르는건지 방목하는건지 잘 모르겠네";
			case 2:
				return "세이자: 별로 강해보이진않은 녀석이었어. 다시 만나긴 싫지만";
			case 3:
				return "세이자: 나만큼 미움 받는 녀석이라고? 별로 동료의식은 안느끼지만 말이야";
			}
			break;
		case GT_TENSI:
			switch(randA(3))
			{
			case 0:
				return "세이자: 이런 녀석을 믿는 사람이 있다고? 취향 참 독특하구만";
			case 1:
				return "세이자: 하늘에서 돌에 맞지 않게 조심하라구";
			case 2:
				return "세이자: 이런 잡동사니가 필요한거야? 너도 참 특이하군";
			case 3:
				return "세이자: 천인의 물건치곤 값싸보이는 물건 뿐이었어";
			}
			break;
		case GT_LILLY:
			switch(randA(3))
			{
			case 0:
				return "세이자: 요정? 권리 신장? 무슨 말도 안되는 얘기를 하는걸까?";
			case 1:
				return "세이자: 요정과 벌레는 비슷하지~ 죽여도 죽여도 계속 귀찮게구는 점 말이야";
			case 2:
				return "세이자: 요정의 물건이 도움이 될진 모르겠지만 훔쳐왔어. 어떻게든 써보라고";
			case 3:
				return "세이자: 주변도 보지않고 폭격해대는 요정이었어. 민폐라고 이거";
			}
			break;
		case GT_MIKO:
			switch (randA(3))
			{
			case 0:
				return "세이자: 그 잘난 녀석이 아끼는 망토를 하나 가져왔지";
			case 1:
				return "세이자: 난 더 마음에 드는 망토가 있어서 말이지, 이건 너 줄게";
			case 2:
				return "세이자: 겉으론 위대한 척해도 속으론 약삭빠른 녀석이지. 난 알 수 있어";
			case 3:
				return "세이자: 빨간 망토? 파란 망토? 그런건 잘 모르겠는데";
			}
			break;
		case GT_OKINA:
			switch (randA(3))
			{
			case 0:
				return "세이자: 그 이상한 춤을 추는 무리를 따돌리느라 진땀 뺏다고";
			case 1:
				return "세이자: 그런 놈의 부하따위 될까보냐";
			case 2:
				return "세이자: 이 아이템을 쓰면 일시적으로 무적이 된다던데 잘 써보라고";
			case 3:
				return "세이자: 등 뒤에 문이 있길래 들어가보고 이걸 훔쳐왔지";
			}
			break;
		case GT_JUNKO:
			switch (randA(3))
			{
			case 0:
				return "세이자: 역시 아이템 강화는 가장 중요하지?";
			case 1:
				return "세이자: 계속 누굴 죽인다고 중얼거리다니 기분나쁜 놈이네";
			case 2:
				return "세이자: 순화가 축복이라고? 아이템을 쓰질못한다면 무슨 소용인거지?";
			case 3:
				return "세이자: 순수한 힘엔 못미치지만 우리에겐 머리와 아이템이 있지";
			}
			break;
		}
	}

	switch(piety)
	{
	case 0:
		switch(randA(4))
		{
		case 0:
			return "세이자: 새로운 레지스탕스의 탄생이군! 환영한다!";
		case 1:
			return "세이자: 우린 최고의 팀이 될거야!";
		case 2:
			return "세이자: 콧대만 높은 그 녀석들에게 한방 먹이자고!";
		case 3:
			return "세이자: 하극상의 시작이다!";
		case 4:
			return "세이자: 약자에게 힘을! 강자에겐 벌을!";
		}
		break;		
	case 1:
	case 2:
	case 3:
		switch(randA(5))
		{
		case 0:
			return "세이자: 정말? 아이템이 필요하지않은거야? 그 자신감 싫진 않아";
		case 1:
			return "세이자: 물론 선물은 받지않아도 좀 도와줄거지?";
		case 2:
			return "세이자: 사양할 필요는 없는데 말이지";
		case 3:
			return "세이자: 필요없다는걸로 알겠어 파트너";
		case 4:
			return "세이자: 후회하지말라고";
		case 5:
			return "세이자: 그럼 이 보물은 내가 가지고 있지";
		}
		break;		
	case 4:
		if(god_ == GT_NONE)
		{
			switch(randA(1))
			{
			case 0:
				return "세이자: 정말로 필요없어?";
			case 1:
				return "세이자: 기껏 내 보물을 준다는데 왜 싫다는거지?";
			}
		}
		else
		{			
			switch(randA(6))
			{
			case 0:
				return "세이자: (이거 수지가 안 맞는거 아닐까?)";
			case 1:
				return "세이자: 나 덕분에 여기까지 왔다고 생각해";
			case 2:
				return "세이자: 흠... 여기 받아";
			case 3:
				return "세이자: (이건 좀 아까운데...)";
			case 4:
				return "세이자: (이 물건보다 이 녀석이 더 유용할거같진 않은데...)";
			case 5:
				return "세이자: 역시 이건 좀 아까운... 아, 아무것도 아니야";
			case 6:
				return "세이자: (생각해보니 내가 손해를 보고 있잖아 이거)";
			}	
		}
		break;	
	case 5:		
		if(god_ == GT_NONE)
		{
			switch(randA(1))
			{
			case 0:
				return "세이자: 이봐, 말해봐. 무슨 속셈이 있는거지?";
			case 1:
				return "세이자: 네가 뭘 생각하는지 알 수가 없군";
			}
		}
		else
		{
			switch(randA(6))
			{
			case 0:
				return "세이자: ...";
			case 1:
				return "세이자는 심기가 불편한듯 하다.";
			case 2:
				return "세이자: ...역시 아무리 생각해도 내가 손해야";
			case 3:
				return "세이자: (그러고보니 선물을 신도에게 주다가 배신당하는 신이 있다고 들었는걸)";
			case 4:
				return "세이자: 흥... 그 얼굴 왠지 짜증나는걸";
			case 5:
				return "세이자: (내가 이용당하고 있는게 아닐까 이거?)";
			case 6:
				return "세이자: (배신 당하기 전에 배신한다... 이게 내 신조였지)";
			}
		}
		break;	
	case 6: //세이자의 배신
		switch(randA(6))
		{
		case 0:
			return "세이자: 잘 들어. 난 뼈속까지 아마노자쿠다! 나에게 동료란 없어!";
		case 1:
			return "세이자: 역시 넌 적이었어. 넌 약자의 편이 아니야!";
		case 2:
			return "세이자: 너도 날 배신할 생각이었지? 아니야! 내가 널 배신할거다!";
		case 3:
			return "세이자: 이용당하다 버려진 녀석은 바로 너다! 이 멍청아! 내가 널 이용한거야!";
		case 4:
			return "세이자: 너도 내 보물이 탐나서 온거지? 내가 그 속셈을 모를 줄 알고?";
		case 5:
			return "세이자: 아마노자쿠에게 동료란 없어! 넌 처음부터 이용당한거뿐이지!";
		case 6:
			return "세이자: 그동안 널 파트너라고 했던말은 다 거짓말이다. 왜냐면 난 아마노자쿠니까!";
		}
		break;			
	case 7:		//세이자를 배신
		switch(randA(3))
		{
		case 0:
			return "세이자: 뭐? 네가 날 배신해? 그게 그렇게 쉽게 될거같아?";
		case 1:
			return "세이자: 그랬군. 역시 동료는 필요없는 거였어. 넌 끔찍하게 죽을거야!";
		case 2:
			return "세이자: 이 아마노자쿠를 이용하려하다니 간도 크구나!";
		case 3:
			return "세이자: 후회하게 해주마!";
		}
		break;	
	}

	
	return "세이자: ...";
}
