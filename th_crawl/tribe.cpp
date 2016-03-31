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
		return "부유를 능력을 통해 키고 끌 수 있다.";
	case TPT_SWIM:
		return "깊은 물에서도 평지처럼 이동해 다닐 수 있다.";
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return "로브 이외의 몸통 방어구를 입을 수 없다.";
			case -1:
				return "로브 이외의 몸통 방어구를 입을 수 없다.";
			default:
				return "로브 이외의 몸통 방어구를 못입긴 개뿔 버그다.\n제작자에게 신고하자.";
			}
		}
	case TPT_HORN:
		return "머리방어구를 낄 수 없다. 또한 뿔에 의한 박치기 공격이 추가된다.\n매 공격마다 일정확률로 박치기가 나가며 맨손으로 싸울때 더 높은 확률로 나간다.";
	case TPT_GHOST_FOOT:
		return "다리방어구를 낄 수 없다.";
	case TPT_CHEUKUMOGAMI:
		return "당신의 본체인 도구는 버릴 수 없다.\n당신의 본체를 손에 들고 있으면 그 장비와 연관된 스킬이 5증가하는 보너스를 받는다.";
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
		you.max_hp-=2;
		you.max_mp+=1;
		you.StatUpDown(-2,STAT_STR);
		you.StatUpDown(2,STAT_INT);
		break;
	case TRI_FAIRY:
		you.max_hp-=2;
		you.StatUpDown(-2,STAT_STR);
		you.StatUpDown(1,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_SIZE,-1);

		break;
	case TRI_CROWTENGU:
		you.max_hp+=1;
		you.StatUpDown(-1,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_FLY,1);
		break;
	case TRI_WOLFTENGU:
		you.max_hp+=2;
		you.StatUpDown(2,STAT_STR);
		you.StatUpDown(-1,STAT_INT);
		you.StatUpDown(-1,STAT_DEX);
		break;
	case TRI_KAPPA:
		you.max_hp+=1;
		you.SetProperty(TPT_SWIM,1);
		break;
	case TRI_CHEUKUMOGAMI:
		you.max_hp-=1;
		you.StatUpDown(-1,STAT_STR);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_POISON_RESIST,1);
		you.SetProperty(TPT_CHEUKUMOGAMI,1);
		break;
	case TRI_ONI:
		you.max_hp+=3;
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
		if(level_%3 != 0)
		{
			you.max_hp--;
			you.hp--;
		}
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
		you.max_hp--;
		you.hp--;
		break;
	case TRI_CROWTENGU:
		if(level_%5 == 0)
		{
			(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX));
		}
		if(level_%3 == 0)
		{
			you.max_hp++;
			you.hp++;
		}
		break;
	case TRI_WOLFTENGU:
		if(level_%4 == 0)
		{
			you.StatUpDown(1,STAT_STR);
		}
		if(level_%2 == 0)
		{
			you.max_hp++;
			you.hp++;
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
		if(level_%3 == 0)
		{
			you.max_hp++;
			you.hp++;
		}
		break;
	case TRI_CHEUKUMOGAMI:
		if(level_%3 == 0)
		{
			you.max_hp--;
			you.hp--;
		}
		break;
	case TRI_ONI:
		if(level_%3 == 0)
		{
			you.StatUpDown(1,STAT_STR);
		}
		you.max_hp++;
		you.hp++;
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