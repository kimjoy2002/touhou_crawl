//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: tribe.h
//
// 내용: 종족 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "tribe.h"
#include "enum.h"
#include "player.h"
#include "skill.h"
#include "save.h"
#include "skill_use.h"
#include "key.h"
extern HANDLE mutx;



void tribe_property::SaveDatas(FILE *fp)
{
	SaveData<tribe_proper_type>(fp, id);
	SaveData<int>(fp, value);

}
void tribe_property::LoadDatas(FILE *fp)
{
	LoadData<tribe_proper_type>(fp, id);
	LoadData<int>(fp, value);
}



string tribe_property::GetName()
{
	switch(id)
	{
	case TPT_FIRE_RESIST:
		return "화염저항";
	case TPT_COLD_RESIST:
		return "냉기저항";
	case TPT_ELEC_RESIST:
		return "전기저항";
	case TPT_POISON_RESIST:
		return "독저항";
	case TPT_STEALTH:
		return "은밀함";
	case TPT_FLY:
		return "비행";
	case TPT_SWIM:
		return "수영";
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return "거대사이즈";
			case -1:
				return "미니사이즈";
			default:
				return "버그사이즈";
			}
		}
	case TPT_HORN:
		return "뿔";
	case TPT_GHOST_FOOT:
		return "유령다리";
	case TPT_CHEUKUMOGAMI:
		return "츠쿠모가미";
	case TPT_HP:
		{
			switch(value)
			{
			case 3:
				return "체력적성(+30%)";
			case 2:
				return "체력적성(+20%)";
			case 1:
				return "체력적성(+10%)";
			case -1:
				return "체력적성(-10%)";
			case -2:
				return "체력적성(-20%)";
			case -3:
				return "체력적성(-30%)";
			default:
				return "버그사이즈";
			}
		}
	case TPT_INVISIBLE:
		return "영구투명";
	case TPT_POWER_SAVE:
		return "파워보존";
	case TPT_9_LIFE:
		return "리저렉션";
	case TPT_18_LIFE:
		return "리저렉션";
	case TPT_SPEED:
		{
			switch(value)
			{
			case 1:
				return "민첩함";
			case -1:
				return "둔함";
			default:
				return "버그이속";
			}
		}
	case TPT_CLAW:
		return "손톱";
	}
	return "버그특성";
}
string tribe_property::GetInfor()
{
	switch(id)
	{
	case TPT_FIRE_RESIST:
		return "당신은 화염에 강하다.";
	case TPT_COLD_RESIST:
		return "당신은 냉기에 강하다.";
	case TPT_ELEC_RESIST:
		return "당신은 전기에 강하다.";
	case TPT_POISON_RESIST:
		return "당신은 독에 강하다.";
	case TPT_STEALTH:
		return "당신은 은밀하게 움직인다.";
	case TPT_FLY:
		return "당신은 큰 날개를 가졌다.";
	case TPT_SWIM:
		return "당신은 수영할 수 있다.";
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return "당신은 몸집이 커서 갑옷이 몸에 안 맞는다.";
			case -1:
				return "당신은 몸집이 작아서 갑옷이 몸에 안 맞는다.";
			default:
				return "당신은 몸집이 버그다.";
			}
		}
	case TPT_HORN:
		return "당신은 머리에 뿔이 달려있다.";
	case TPT_GHOST_FOOT:
		return "당신의 망령이기에 다리가 없다.";
	case TPT_CHEUKUMOGAMI:
		return "당신의 본체는 도구이다.(미구현)";
	case TPT_HP:
		{
			switch(value)
			{
			case 3:
				return "당신은 매우 튼튼하다.(체력 +30%)";
			case 2:
				return "당신은 꽤 튼튼하다.(체력 +20%)";
			case 1:
				return "당신은 튼튼하다.(체력 +10%)";
			case -1:
				return "당신은 연약하다.(체력 -10%)";
			case -2:
				return "당신은 꽤 연약하다.(체력 -20%)";
			case -3:
				return "당신은 매우 연약하다.(체력 -30%)";
			default:
				return "버그사이즈";
			}
		}
	case TPT_INVISIBLE:
		return "무의식인 당신은 항상 투명해져있다.";
	case TPT_POWER_SAVE:
		return "당신은 P의 자연소모가 느리다.";
	case TPT_9_LIFE:
		return "당신은 9레벨이전에 한번 부활할 수 있다.";
	case TPT_18_LIFE:
		return "당신은 18레벨이전에 한번 부활할 수 있다.";
	case TPT_SPEED:
		{
			switch(value)
			{
			case 1:
				return "당신은 이동속도가 빠르다.";
			case -1:
				return "당신은 이동속도는 느리다.";
			default:
				return "버그이속";
			}
		}
	case TPT_CLAW:
		{
			switch(value)
			{
			case 3:
				return "당신은 손톱이 아주 길다.";
			case 2:
				return "당신은 손톱이 상당히 길다.";
			case 1:
				return "당신은 손톱이 길다.";
			default:
				return "버그손톱";
			}
		}
	}
	return "이 특성은 버그다.";
}
string tribe_property::GetDetail()
{
	switch(id)
	{
	case TPT_FIRE_RESIST:
		return "화염 저항이 1단계 증가한다.";
	case TPT_COLD_RESIST:
		return "냉기 저항이 1단계 증가한다.";
	case TPT_ELEC_RESIST:
		return "전기 저항이 증가한다.";
	case TPT_POISON_RESIST:
		return "독 저항이 증가한다.";
	case TPT_STEALTH:
		return "은밀도가 오른다.";
	case TPT_FLY:
		return "비행을 능력을 통해 키고 끌 수 있다.";
	case TPT_SWIM:
		return "깊은 물에서도 평지처럼 이동해 다닐 수 있다.";
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return "천 이외의 몸통 방어구를 입을 수 없다.\n또한 당신의 큰 사이즈는 또한 회피에 패널티를 준다.";
			case -1:
				return "천 이외의 몸통 방어구를 입을 수 없다.\n그러나 당신의 작은 사이즈는 회피에 보너스를 준다.";
			default:
				return "천 이외의 몸통 방어구를 못입긴 개뿔 버그다.\n제작자에게 신고하자.";
			}
		}
	case TPT_HORN:
		return "뿔에 의한 박치기 공격이 추가된다.\n매 공격마다 일정확률로 박치기가 나가며 맨손으로 싸울때 더 높은 확률로 나간다.";
	case TPT_GHOST_FOOT:
		return "다리방어구를 낄 수 없다. (과거엔 그랬다)";
	case TPT_CHEUKUMOGAMI:
		return "당신의 본체인 도구는 버릴 수 없다.\n당신의 본체를 손에 들고 있으면 그 장비와 연관된 스킬이 5증가하는 보너스를 받는다.";
	case TPT_HP:
		return "당신은 유전적으로 체력이 결정되어있다.\n최종 체력치가 수치만큼 곱해진다.";
	case TPT_INVISIBLE:
		return "비전투중일때는 당신은 상시 투명을 유지한다.\n만약 당신이 공격을 시도하면 투명이 풀린다.";
	case TPT_POWER_SAVE:
		return "턴이 지남에 따라 소모되는 P의 자연 감소율이 줄어든다.\n또한 가속과 투명에 의한 P 소모폭도 감소한다.";
	case TPT_9_LIFE:
		return "죽었을때 모든 체력과 영력을 회복하고 큰 폭발과 함께 부활한다.\n이 능력은 레벨 9가 되면 사라진다.";
	case TPT_18_LIFE:
		return "죽었을때 모든 체력과 영력을 회복하고 큰 폭발과 함께 부활한다.\n이 능력은 레벨 18이 되면 사라진다.";
	case TPT_SPEED:
		{
			switch(value)
			{
			case 1:
				return "당신의 이동속도는 빠르다.\n이동시 다른 종족보다 80%의 딜레이만을 가진다.";
			case -1:
				return "당신의 이동속도는 느리다.\n이동시 다른 종족보다 120%의 딜레이를 가진다.";
			default:
				return "당신의 이동속도는 놀랍긴 개뿔 버그다.\n제작자에게 신고하자.";
			}
		}
	case TPT_CLAW:
		return "당신은 손톱이 길게 나있다.\n맨손격투시 추가 데미지를 준다.";
	}
	return "이 특성은 버그이므로 존재자체가 해악이다.\n제작자에게 신고하자.";
}

void tribe_property::gain(bool gain_)
{
	int value_ = gain_?value:-value;
	switch(id)
	{
	case TPT_FIRE_RESIST:
		you.ResistUpDown(value_,RST_FIRE);
		return;
	case TPT_COLD_RESIST:
		you.ResistUpDown(value_,RST_ICE);
		return;
	case TPT_ELEC_RESIST:
		you.ResistUpDown(value_,RST_ELEC);
		return;
	case TPT_POISON_RESIST:
		you.ResistUpDown(value_,RST_POISON);
		return;
	case TPT_STEALTH:
		return;
	case TPT_FLY:
		{
			int temp = you.Ability(SKL_LEVITATION_OFF,false,true);
			you.Ability(SKL_LEVITATION,false,value<=0,value>0?(temp>0?temp+1:0):0);
			if(value<=0 && temp == 1 && you.s_levitation)
			{
				you.s_levitation=0;
			}
			return;
		}
	case TPT_SWIM:
		return;
	case TPT_SIZE:
		return;
	case TPT_HORN:
		return;
	case TPT_GHOST_FOOT:
		return;
	case TPT_CHEUKUMOGAMI:
		return;
	case TPT_INVISIBLE:
		you.SetTogleInvisible(false);
		return;
	case TPT_POWER_SAVE:		
		you.ResistUpDown(1,RST_POWER);
		return;
	}
}


void PropertyView()
{
	int i=0;
	changedisplay(DT_PROPERTY);
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
			if(num < you.property_vector.size())
			{
				WaitForSingleObject(mutx, INFINITE);
				SetText() = "특성 : " + you.property_vector[num].GetName();
				SetText() += "\n\n효과 : " + you.property_vector[num].GetDetail();
				changedisplay(DT_TEXT);
				ReleaseMutex(mutx);
				waitkeyinput();
				changedisplay(DT_PROPERTY);
				changemove(0);
			}
			else
				break;
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
}




void SetTribe(tribe_type select_)
{
	switch(select_)
	{
	case TRI_HUMAN:
		break;
	case TRI_WIZARD:
		you.SetProperty(TPT_HP,-2);
		you.max_mp+=1;
		you.StatUpDown(-2,STAT_STR);
		you.StatUpDown(2,STAT_INT);
		break;
	case TRI_FAIRY:
		you.SetProperty(TPT_HP,-3);
		you.StatUpDown(-2,STAT_STR);
		you.StatUpDown(1,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_SIZE,-1);
		break;
	case TRI_CROWTENGU:
		you.StatUpDown(-1,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_FLY,1);
		break;
	case TRI_WOLFTENGU:
		you.SetProperty(TPT_HP,1);
		you.StatUpDown(2,STAT_STR);
		you.StatUpDown(-1,STAT_INT);
		you.StatUpDown(-1,STAT_DEX);
		break;
	case TRI_KAPPA:
		you.SetProperty(TPT_SWIM,1);
		break;
	case TRI_NECOMATA:
		you.StatUpDown(-2,STAT_STR);
		you.StatUpDown(2,STAT_DEX);
		you.SetProperty(TPT_HP,-2);
		you.SetProperty(TPT_SPEED,1);
		you.SetProperty(TPT_CLAW,1);
		break;
	case TRI_CHEUKUMOGAMI:
		you.SetProperty(TPT_HP,-1);
		you.StatUpDown(-1,STAT_STR);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_POISON_RESIST,1);
		you.SetProperty(TPT_CHEUKUMOGAMI,1);
		break;
	case TRI_ONI:
		you.SetProperty(TPT_HP,3);
		you.StatUpDown(3,STAT_STR);
		you.StatUpDown(-2,STAT_INT);
		you.StatUpDown(-1,STAT_DEX);
		you.SetProperty(TPT_SIZE,1);
		you.SetProperty(TPT_HORN,1);
		break;
	case TRI_HALFYOKAI:
		break;
	case TRI_WRAITH:
		you.SetProperty(TPT_COLD_RESIST,1);
		you.SetProperty(TPT_STEALTH,1);
		you.SetProperty(TPT_POISON_RESIST,1);
		you.SetProperty(TPT_GHOST_FOOT,1);
		break;
	case TRI_VAMPIRE:
		break;
	}
	for(int i=0;i<SKT_MAX;i++)
		you.skill[i].aptit = aptitude[select_][i];
	you.exper_aptit = exp_aptitude[select_];
}

void LevelUpTribe(int level_)
{
	switch(you.tribe)
	{
	case TRI_HUMAN:
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		break;
	case TRI_WIZARD:
		if(level_%4 == 0)
		{
			you.StatUpDown(1,STAT_INT);
		}
		you.max_mp++;
		you.mp++;
		break;
	case TRI_FAIRY:
		if(level_%5 == 0)
		{
			(randA(1)?you.StatUpDown(1,STAT_DEX):you.StatUpDown(1,STAT_INT));
		}
		if(level_%2 == 0)
		{
			you.max_mp++;
			you.mp++;
		}
		break;
	case TRI_CROWTENGU:
		if(level_%5 == 0)
		{
			(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX));
		}
		break;
	case TRI_WOLFTENGU:
		if(level_%4 == 0)
		{
			you.StatUpDown(1,STAT_STR);
		}
		if(level_%3 == 0)
		{
			you.max_mp--;
			you.mp--;
		}
		break;
	case TRI_KAPPA:
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		break;
	case TRI_NECOMATA:
		if(level_%5 == 0)
		{
			you.StatUpDown(1,STAT_DEX);
		}
		if(level_%5 == 0)
		{
			you.max_mp--;
			you.mp--;
		}
		break;
	case TRI_CHEUKUMOGAMI:
		break;
	case TRI_ONI:
		if(level_%3 == 0)
		{
			you.StatUpDown(1,STAT_STR);
		}
		if(level_%2 == 0)
		{
			you.max_mp--;
			you.mp--;
		}
		break;
	case TRI_HALFYOKAI:
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		break;
	case TRI_WRAITH:
		break;
	case TRI_VAMPIRE:
		break;
	}
}