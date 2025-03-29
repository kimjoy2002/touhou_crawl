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
#include "note.h"
#include "environment.h"
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


string getTribeProperty(tribe_proper_type id, int value) {
	return tribe_property(id, value).GetName();
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
		{
			switch(value)
			{
			case 1:
				return "파워보존";
			case -1:
				return "피에 굶주림";
			default:
				return "버그파워";
			}
		}
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
	case TPT_JAW:
		return "강한 턱";	
	case TPT_FOOT:
		return "강한 다리";
	case TPT_EYE:
		return "뛰어난 눈";
	case TPT_FUR:
		return "푹신한 털";
	case TPT_REGEN:
		{
			switch(value)
			{
			case 1:
			case 2:
			case 3:
				return "강한 재생력";	
			case -1:
			case -2:
			case -3:
				return "약한 재생력";
			default:
				return "버그재생";
			}
		}
	case TPT_SLAY:
		return "전투감각";
	case TPT_CONFUSE_ATTACK:
		return "허찌르기";
	case TPT_MAGIC_RESIST:
		return "마법저항";
	case TPT_SKIN_AC:
		return "강한 피부";
	case TPT_STR:
		return "힘증가";
	case TPT_EV:
		return "회피증가";
	case TPT_CLOUD:
		return "구름 컨트롤";
	case TPT_BREATH:
		return "브레스";
	case TPT_SCALE:
		return "비늘";
	case TPT_GRAZE_CONTROL:
		return "공기의 흐름";
	case TPT_FORCE_OF_NATURE:
		return "자연의 힘";
	case TPT_MP_REGEN:
		{
			switch(value)
			{
			case 1:
				return "영력 회복 증가";
			case -1:
				return "영력 회복 감소";
			default:
				return "버그영력회복";
			}
		}
	case TPT_CONFUSE_RESIST:
		return "혼란 저항";
	case TPT_SPELL_POWER:
		return "강화 마법";
	case TPT_FINGER_MAGIC:
		return "손짓 마법";
	case TPT_BLOOD_MAGIC:
		return "피의 마법";
	case TPT_TORMENT:
		return "지옥의 고통";
	case TPT_CLOUD_RESIST:
		return "구름 저항";
	case TPT_SEE_INVI:
		return "투명 보기";
	case TPT_FIRE_IMUNE:
		return "화염 면역";
	case TPT_COLD_IMUNE:
		return "냉기 면역";
	case TPT_ELEC_IMUNE:
		return "전기 면역";
	case TPT_PURE_MP:
		return "순수한 마력";
	case TPT_PURE_POWER:
		return "순수한 파워";
	case TPT_PURE_LIFE:
		return "순수한 생명";
	case TPT_PURE_SYSTEM:
		return "순수한 시스템";
	default:
		break;
	}
	return "버그특성";
}
string tribe_property::GetInfor()
{
	switch(id)
	{
	case TPT_FIRE_RESIST:
		{
			switch(value)
			{
			case 3:
			case 2:
				return "당신은 화염에 아주 강하다.";
			case 1:
				return "당신은 화염에 강하다.";
			case -1:
				return "당신은 화염에 약하다";
			case -2:
			case -3:
				return "당신은 화염에 아주 약하다";
			default:
				return "버그화염저항";
			}
		}
	case TPT_COLD_RESIST:
		{
			switch(value)
			{
			case 3:
			case 2:
				return "당신은 냉기에 아주 강하다.";
			case 1:
				return "당신은 냉기에 강하다.";
			case -1:
				return "당신은 냉기에 약하다";
			case -2:
			case -3:
				return "당신은 냉기에 아주 약하다";
			default:
				return "버그냉기저항";
			}
		}
	case TPT_ELEC_RESIST:
		{
			switch(value)
			{
			case 3:
			case 2:
				return "당신은 전기에 아주 강하다.";
			case 1:
				return "당신은 전기에 강하다.";
			case -1:
				return "당신은 전기에 약하다";
			case -2:
			case -3:
				return "당신은 전기에 아주 약하다";
			default:
				return "버그전기저항";
			}
		}
	case TPT_POISON_RESIST:
		return "당신은 독에 강하다.";
	case TPT_STEALTH:
		{
			switch(value)
			{
			case 3:
				return "당신은 은밀하게 움직인다.(+3)";
			case 2:
				return "당신은 은밀하게 움직인다.(+2)";
			case 1:
				return "당신은 은밀하게 움직인다.(+1)";
			case -1:
			default:
				return "버그은밀";
			}
		}	
	case TPT_FLY:
		return "당신은 큰 날개를 가졌다.";
	case TPT_SWIM:
		return "당신은 수영할 수 있다.";
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return "당신은 몸집이 커서 큰 갑옷이 몸에 안 맞는다.";
			case -1:
				return "당신은 몸집이 작아서 큰 갑옷이 몸에 안 맞는다.";
			default:
				return "당신은 몸집이 버그다.";
			}
		}
	case TPT_HORN:
		return "당신은 머리에 뿔이 달려있다.";
	case TPT_GHOST_FOOT:
		return "당신의 망령이기에 다리가 없다.";
	case TPT_CHEUKUMOGAMI:
		return "당신의 본체는 도구이다.";
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
		{
			switch(value)
			{
			case 1:
				return "당신은 P의 자연소모가 느리다.";
			case -1:
				return "당신은 P에 굶주려 있다.";
			default:
				return "버그파워";
			}
		}
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
	case TPT_JAW:
		return "당신은 강한 턱을 지녔다.";	
	case TPT_FOOT:
		return "당신은 도약하기 충분한 강한 다리를 지녔다.";
	case TPT_EYE:
		return "당신은 뛰어난 눈을 가졌다.";
	case TPT_FUR:
		return "당신은 푹신한 털로 덮여있다. (AC+3, 냉기저항 1단계)";
	case TPT_REGEN:
		{
			switch(value)
			{
			case 3:
				return "당신은 체력 재생력이 높다.(+3)";
			case 2:
				return "당신은 체력 재생력이 높다.(+2)";
			case 1:
				return "당신은 체력 재생력이 높다.(+1)";
			case -1:
				return "당신은 체력 재생력이 낮다.(-1)";
			default:
				return "버그재생력";
			}
		}	
	case TPT_SLAY:
		return "당신은 공격과 방패를 다루는 전투감각이 뛰어나다.";
	case TPT_CONFUSE_ATTACK:
		return "당신의 공격은 가끔 상대의 허를 찌른다.";
	case TPT_MAGIC_RESIST:
		return "당신은 마법저항력이 높다.";
	case TPT_SKIN_AC:
		return "당신은 강한 피부를 지녔다. (AC+5)";
	case TPT_STR:
		return "당신은 강한 힘을 지녔다.(힘+5)";
	case TPT_EV:
		return "당신은 초월적인 회피재능이 있다. (EV+10)";
	case TPT_CLOUD:
		return "당신은 구름을 몰고 다닌다.";
	case TPT_BREATH:
		return "당신은 브레스를 쏠 수 있다.";
	case TPT_SCALE:
		{
			switch(value)
			{
			case 3:
				return "당신은 아주 단단한 비늘로 덮여있다. (AC+9)";
			case 2:
				return "당신은 두꺼운 비늘로 덮여있다. (AC+6)";
			case 1:
				return "당신은 비늘로 덮여있다. (AC+3)";
			default:
				return "버그비늘";
			}
		}	
	case TPT_GRAZE_CONTROL:
		return "당신은 공기의 흐름을 다루는 것에 능하다. (그레이즈강화)";
	case TPT_FORCE_OF_NATURE:
		return "당신은 몸에 자연의 힘을 두르고 있다.";
	case TPT_MP_REGEN:
		{
			switch(value)
			{
			case 3:
				return "당신은 영력 재생력이 높다.(+3)";
			case 2:
				return "당신은 영력 재생력이 높다.(+2)";
			case 1:
				return "당신은 영력 재생력이 높다.(+1)";
			case -1:
				return "당신은 영력 재생력이 낮다.(-1)";
			default:
				return "버그재생력";
			}
		}	
	case TPT_CONFUSE_RESIST:
		return "당신은 혼란에 저항이 있다.";
	case TPT_SPELL_POWER:
		return "당신이 쓰는 마법의 힘은 강력해진다.";
	case TPT_FINGER_MAGIC:
		return "당신은 손짓으로 마법을 쓸 수 있다.";
	case TPT_BLOOD_MAGIC:
		return "당신은 영력이 없어도 피를 이용하여 마법을 쓸 수 있다.";
	case TPT_TORMENT:
		return "당신은 지옥의 고통을 불러올 수 있다.";
	case TPT_CLOUD_RESIST:
		return "당신은 구름에 영향을 적게 받는다.";
	case TPT_SEE_INVI:
		return "당신은 투명을 볼 수 있다.";
	case TPT_FIRE_IMUNE:
		return "당신은 화염에 면역이다.";
	case TPT_COLD_IMUNE:
		return "당신은 냉기에 면역이다.";
	case TPT_ELEC_IMUNE:
		return "당신은 전기에 면역이다.";
	case TPT_PURE_MP:
		return "당신의 체력과 영력은 동일시 된다.";
	case TPT_PURE_POWER:
		return "당신은 항상 풀파워다.";
	case TPT_PURE_LIFE:
		return value>1?"당신은 2개의 추가 생명이 남아있다.":"당신은 1개의 추가 생명이 남아있다."; 
	case TPT_PURE_SYSTEM:
		return "당신은 순화 상태에서도 스펠카드를 사용할 수 있으며 부적의 충전속도가 3배가 된다.";
	default:
		break;
	}
	return "이 특성은 버그다.";
}
string tribe_property::GetDetail()
{
	switch(id)
	{
	case TPT_FIRE_RESIST:
		{
			switch(value)
			{
			case 3:
				return "화염 저항이 3단계 증가한다.";
			case 2:
				return "화염 저항이 2단계 증가한다.";
			case 1:
				return "화염 저항이 1단계 증가한다.";
			case -1:
				return "화염 저항이 1단계 감소한다.";
			case -2:
				return "화염 저항이 2단계 감소한다.";
			case -3:
				return "화염 저항이 3단계 감소한다.";
			default:
				return "버그화염저항";
			}
		}
	case TPT_COLD_RESIST:
		{
			switch(value)
			{
			case 3:
				return "냉기 저항이 3단계 증가한다.";
			case 2:
				return "냉기 저항이 2단계 증가한다.";
			case 1:
				return "냉기 저항이 1단계 증가한다.";
			case -1:
				return "냉기 저항이 1단계 감소한다.";
			case -2:
				return "냉기 저항이 2단계 감소한다.";
			case -3:
				return "냉기 저항이 3단계 감소한다.";
			default:
				return "버그냉기저항";
			}
		}
	case TPT_ELEC_RESIST:
		{
			switch(value)
			{
			case 3:
				return "전기 저항이 3단계 증가한다.";
			case 2:
				return "전기 저항이 2단계 증가한다.";
			case 1:
				return "전기 저항이 1단계 증가한다.";
			case -1:
				return "전기 저항이 1단계 감소한다.";
			case -2:
				return "전기 저항이 2단계 감소한다.";
			case -3:
				return "전기 저항이 3단계 감소한다.";
			default:
				return "버그전기저항";
			}
		}
	case TPT_POISON_RESIST:
		return "독 저항이 증가한다.";
	case TPT_STEALTH:
		return "은밀도가 오른다. 은밀한 정도는 수치만큼 곱해진다.";
	case TPT_FLY:
		return "비행을 능력을 통해 키고 끌 수 있다.";
	case TPT_SWIM:
		return "깊은 물에서도 평지처럼 이동해 다닐 수 있다.";
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return "천과 가죽 이외의 몸통 방어구를 입을 수 없다.\n또한 당신의 큰 사이즈는 또한 회피에 패널티를 준다.";
			case -1:
				return "천과 가죽 이외의 몸통 방어구를 입을 수 없다.\n그러나 당신의 작은 사이즈는 회피에 보너스를 준다.";
			default:
				return "천과 가죽 이외의 몸통 방어구를 못입긴 개뿔 버그다.\n제작자에게 신고하자.";
			}
		}
	case TPT_HORN:
		return "뿔에 의한 박치기 공격이 추가된다.\n매 공격마다 일정확률로 박치기가 나가며 맨손으로 싸울때 더 높은 확률로 나간다.\n머리방어구를 착용할 수 없다.";
	case TPT_GHOST_FOOT:
		return "당신의 다리는 유령처럼 존재하지않는다.\n다리방어구를 착용할 수 없다.";
	case TPT_CHEUKUMOGAMI:
		return "당신의 본체인 도구는 버릴 수 없다.\n당신의 본체를 손에 들고 있으면 그 장비와 연관된 스킬이 5증가하는 보너스를 받는다.";
	case TPT_HP:
		return "당신은 유전적으로 체력이 결정되어있다.\n최종 체력치가 수치만큼 곱해진다.";
	case TPT_INVISIBLE:
		return "비전투중일때는 당신은 상시 투명을 유지한다.\n만약 당신이 공격을 시도하면 투명이 풀린다.";
	case TPT_POWER_SAVE:		
		{
			switch(value)
			{
			case 1:
				return "턴이 지남에 따라 소모되는 P의 자연 감소율이 줄어든다.\n또한 가속과 투명에 의한 P 소모폭도 감소한다.";
			case -1:
				return "턴이 지남에 따라 소모되는 P의 자연 감소율이 증가한다.\n또한 가속과 투명에 의한 P 소모폭도 증가한다.";
			default:
				return "버그파워";
			}
		}
	case TPT_9_LIFE:
		return "죽었을때 모든 체력과 영력을 회복하고 큰 폭발과 함께 부활한다.\n이 능력은 레벨 9가 되면 사라진다.";
	case TPT_18_LIFE:
		return "죽었을때 모든 체력과 영력을 회복하고 큰 폭발과 함께 부활한다.\n이 능력은 레벨 18이 되면 사라진다.";
	case TPT_SPEED:
		{
			switch(value)
			{
			case 1:
				return "이동시 다른 종족보다 80%의 딜레이만을 가진다.";
			case -1:
				return "이동시 다른 종족보다 120%의 딜레이를 가진다.";
			default:
				return "이동속도는 놀랍긴 개뿔 버그다.\n제작자에게 신고하자.";
			}
		}
	case TPT_CLAW:
		return "맨손격투시 추가 데미지를 준다.\n장갑을 낄 수 없게 된다.";
	case TPT_JAW:
		return "매 공격마다 일정확률로 깨물기 공격이 들어간다.";	
	case TPT_FOOT:
		return "파워를 사용하여 적에게 순식간에 점프해서 접근할 수 있다.\n연속 사용은 불가능하다.";
	case TPT_EYE:
		return "투명한 적을 볼 수 있다.";
	case TPT_FUR:
		return "방어력이 3증가하고 냉기에 대한 저항을 1단계 얻는다.";
	case TPT_REGEN:
		{
			switch(value)
			{
			case 3:
			case 2:
			case 1:
				return "체력 재생력이 높다.\n플러스 수치가 높을수록 회복력이 빨라진다.";
			case -1:
				return "체력 재생력이 낮다.\n마이너스 수치가 높을수록 회복력이 느려진다.";
			default:
				return "체력 재생력이 놀랍긴 개뿔 버그다.\n제작자에게 신고하자.";
			}
		}
	case TPT_SLAY:
		return "+6의 전투력 보너스와 방패 수치에 보너스를 받는다.";
	case TPT_CONFUSE_ATTACK:
		return "근접공격시 가끔 상대의 허를 찔러서 혼란에 빠뜨린다.\n";
	case TPT_MAGIC_RESIST:
		return "마법저항력이 증가한다.";
	case TPT_SKIN_AC:
		return "방어력이 5 증가한다.";
	case TPT_STR:
		return "힘이 5 증가한다.";
	case TPT_EV:
		return "회피가 10 증가한다.";
	case TPT_CLOUD:
		return "용의 특성으로 발현되어있는 속성 구름에 면역이다.\n또한 공격당할때 해당 속성의 구름을 흩뿌린다.\n";
	case TPT_BREATH:
		return "당신은 용의 특성으로 발현되어있는 속성 브레스를 쏠 수 있다.";
	case TPT_SCALE:
		{
			switch(value)
			{
			case 3:
				return "아주 단단한 비늘에 의해 방어력이 9 증가한다.";
			case 2:
				return "두꺼운 비늘에 의해 방어력이 6 증가한다.";
			case 1:
				return "비늘에 의해 방어력이 3 증가한다.";
			default:
				return "버그비늘";
			}
		}	
	case TPT_GRAZE_CONTROL:
		return "그레이즈를 발동할 수 있고\n 그레이즈의 효율이 2배로 증가한다.";
	case TPT_FORCE_OF_NATURE:
		return "근접공격에 대해 용의 특성으로 발현되어있는 속성으로 반격을 한다.\n만약 해당 속성에 면역이 없는 적이면 저항할 수 없는 감속을 건다.";
	case TPT_MP_REGEN:
		{
			switch(value)
			{
			case 3:
			case 2:
			case 1:
				return "영력 재생력이 높다.\n플러스 수치가 높을수록 회복력이 빨라진다.";
			case -1:
				return "영력 재생력이 낮다.\n마이너스 수치가 높을수록 회복력이 느려진다.";
			default:
				return "영력 재생력이 놀랍긴 개뿔 버그다.\n제작자에게 신고하자.";
			}
		}
	case TPT_CONFUSE_RESIST:
		return "혼란에 대한 저항력이 생긴다.\n또한 광기에도 면역이 된다.";
	case TPT_SPELL_POWER:
		return "모든 마법의 파워가 1.3배가 된다.";
	case TPT_FINGER_MAGIC:
		return "마법 사용에 의한 소음이 70%로 줄어든다.\n침묵에서도 마법을 사용할 수 있다.";
	case TPT_BLOOD_MAGIC:
		return "영력이 부족할때 마법을 사용하면 영력의 2배만큼 체력을 소모하여 마법을 쓸 수 있다.";
	case TPT_TORMENT:
		return "파워를 1칸 소모하여 시야내의 있는 모든 적의 각각의 체력을 절반으로 한다.";
	case TPT_CLOUD_RESIST:
		return "자연현상 그 자체인 당신은 각종 구름의 영향을 적게 받는다.\n구름으로 인해 받는 데미지가 절반이 된다.";
	case TPT_SEE_INVI:
		return "투명한 적을 볼 수 있게 된다.";
	case TPT_FIRE_IMUNE:
		return "당신은 순호의 축복으로 화염에 면역이기에 화염 속성에 데미지를 입지 않는다.";
	case TPT_COLD_IMUNE:
		return "당신은 순호의 축복으로 냉기에 면역이기에 냉기 속성에 데미지를 입지 않는다.";
	case TPT_ELEC_IMUNE:
		return "당신은 순호의 축복으로 전기에 면역이기에 전기 속성에 데미지를 입지 않는다.";
	case TPT_PURE_MP:
		return "당신은 순호의 축복으로 영력과 체력이 동일시 되었다.\n체력과 영력이 동일한 수치로 관리되어 데미지를 입을때, 마법을 사용할때 사용할 수 있다.\n또한 기존의 체력회복력과 영력회복력이 합산되어 더 빠른 회복을 하게된다.";
	case TPT_PURE_POWER:
		return "당신은 순호의 축복으로 항상 풀파워모드이며 떨어지지않는다.";
	case TPT_PURE_LIFE:
		return value>1 ? "당신은 순호의 축복으로 죽어도 다시 부활할 수 있다.\n단, 순호를 배신하여 생긴 죽음은 이 축복으로 상쇄가 불가능하다.\n당신의 추가 생명은 2개 남았다." : 
			"당신은 순호의 축복으로 죽어도 다시 부활할 수 있다.\n단, 순호를 배신하여 생긴 죽음은 이 축복으로 상쇄가 불가능하다.\n당신의 추가 생명은 1개 남았다.";
	case TPT_PURE_SYSTEM:
		return "당신은 순호의 축복으로 슈팅 시스템에서 가져온 아이템 효과가 강화되었다.\n때문에 순화상태에서도 스펠카드가 사용이 가능하게 되었다.\n또한, 평상시보다 부적의 충전속도가 3배로 빨라지게된다.";
	default:
		break;
	}
	return "이 특성은 버그이므로 존재자체가 해악이다.\n제작자에게 신고하자.";
}

D3DCOLOR tribe_property::getColor()
{

	switch (id)
	{
	case TPT_FIRE_IMUNE:
	case TPT_COLD_IMUNE:
	case TPT_ELEC_IMUNE:
	case TPT_PURE_MP:
	case TPT_PURE_POWER:
	case TPT_PURE_LIFE:	
	case TPT_PURE_SYSTEM:
		return CL_junko;
	default:
		break;
	}
	return CL_STAT;
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
		if(you.equipment[ET_HELMET])
		{
			if(you.unequip(ET_HELMET, true))
			{
				printlog("당신이 쓰고있던 머리방어구가 벗겨졌다!",true,false,false,CL_danger);
			}
		}
		return;
	case TPT_GHOST_FOOT:
		if(you.equipment[ET_BOOTS])
		{
			if(you.unequip(ET_BOOTS,true))
			{
				printlog("당신이 쓰고있던 다리방어구가 벗겨졌다!",true,false,false,CL_danger);
			}
		}
		return;
	case TPT_CHEUKUMOGAMI:
		return;
	case TPT_INVISIBLE:
		you.SetTogleInvisible(false);
		return;
	case TPT_POWER_SAVE:
		you.ResistUpDown(value_,RST_POWER);
		return;	
	case TPT_9_LIFE:
		return;
	case TPT_18_LIFE:
		return;
	case TPT_SPEED:
		return;
	case TPT_CLAW:
		if(you.equipment[ET_GLOVE])
		{
			if(you.unequip(ET_GLOVE,true))
			{
				printlog("당신이 쓰고있던 손방어구가 벗겨졌다!",true,false,false,CL_danger);
			}
		}
		return;
	case TPT_JAW:
		return;
	case TPT_FOOT:
		you.Ability(SKL_JUMPING_ATTACK,true,!gain_);
		return;
	case TPT_EYE:
		you.ResistUpDown(value_,RST_INVISIBLE);
		return;
	case TPT_FUR:
		you.AcUpDown(0,value_>0?3:-3);		
		you.ResistUpDown(value_,RST_ICE);
		return;
	case TPT_REGEN:
		return;
	case TPT_SLAY:
		you.ShUpDown(0, 0);
		return;
	case TPT_CONFUSE_ATTACK:
		return;
	case TPT_MAGIC_RESIST:
		you.MRUpDown((value_>0?40:-40));
		return;
	case TPT_SKIN_AC:
		you.AcUpDown(0,value_>0?5:-5);	
		return;
	case TPT_STR:
		you.StatUpDown(value_>0?6:-6, STAT_STR);
		return;
	case TPT_EV:
		you.EvUpDown(0,value_>0?10:-10);
		return;
	case TPT_CLOUD:
		return;
	case TPT_BREATH:
		you.Ability(SKL_BREATH,true,!gain_);
		return;
	case TPT_SCALE:
		you.AcUpDown(0,value_*3);	
		return;
	case TPT_GRAZE_CONTROL:
		{	
			int temp = you.Ability(SKL_GRAZE_OFF,false,true); //그레이즈 해제를 삭제하고 수를 리턴
			temp += you.Ability(SKL_GRAZE,false,true); //그레이즈 발동도 해제하고 수를 리턴

			temp+=value;

			if(!you.s_graze)
				you.SetGraze(-1);
			//int temp = you.Ability(SKL_GRAZE,false,true,1);
			//you.Ability(SKL_GRAZE_OFF,false,false,temp);
			you.Ability((you.s_graze || you.isGrazeAmulet())?SKL_GRAZE_OFF:SKL_GRAZE,false,temp<=0?true:false,temp);
			if(temp <= 0 && you.s_graze && !you.isGrazeAmulet())
			{
				you.s_graze=0; 
			}
		}
		return;
	case TPT_FORCE_OF_NATURE:
		return;
	case TPT_MP_REGEN:
		return;
	case TPT_CONFUSE_RESIST:
		you.ResistUpDown(value_,RST_CONFUSE);
		return;
	case TPT_SPELL_POWER:
		return;
	case TPT_FINGER_MAGIC:
		return;
	case TPT_BLOOD_MAGIC:
		return;
	case TPT_TORMENT:
		you.Ability(SKL_TORMENT,true,!gain_);
		return;
	case TPT_CLOUD_RESIST:
		return;
	case TPT_SEE_INVI:
		you.ResistUpDown(value_, RST_INVISIBLE);
		return;
	case TPT_FIRE_IMUNE:
		you.ResistUpDown(value_, RST_FIRE);
		return;
	case TPT_COLD_IMUNE:
		you.ResistUpDown(value_, RST_ICE);
		return;
	case TPT_ELEC_IMUNE:
		you.ResistUpDown(value_, RST_ELEC);
		return;
	case TPT_PURE_MP:
		if (value_)
			you.pure_mp = true;
		else
			you.pure_mp = false;
		return;
	case TPT_PURE_POWER:
		you.power = 1000;
		return;
	case TPT_PURE_LIFE:
		return;
	case TPT_PURE_SYSTEM:
		return;
	default:
		break;
	}
	return;
}


void PropertyView()
{
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
		you.SetProperty(TPT_REGEN,1);
		you.SetProperty(TPT_MP_REGEN,1);
		you.SetProperty(TPT_STEALTH,1);	
		you.SetProperty(TPT_CLOUD_RESIST,1);		
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
		you.SetProperty(TPT_JAW,1);
		break;
	case TRI_KAPPA:
		you.SetProperty(TPT_HP,-1);
		you.SetProperty(TPT_SWIM,1);
		break;
	case TRI_NECOMATA:
		you.StatUpDown(-2,STAT_STR);
		you.StatUpDown(2,STAT_DEX);
		you.SetProperty(TPT_HP,-2);
		you.SetProperty(TPT_SPEED,1);
		you.SetProperty(TPT_CLAW,1);
		break;
	case TRI_OARFISH:
		you.SetProperty(TPT_HP,2);
		you.SetProperty(TPT_SPEED,-1);
		you.SetProperty(TPT_SWIM,1);
		you.SetProperty(TPT_ELEC_RESIST,1);
		you.SetProperty(TPT_SCALE,1);
		break;
	case TRI_CHEUKUMOGAMI:
		you.SetProperty(TPT_HP,-1);
		you.StatUpDown(1,STAT_STR);
		you.StatUpDown(-2,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		you.SetProperty(TPT_SIZE,-1);
		you.SetProperty(TPT_POISON_RESIST,1);
		//you.SetProperty(TPT_CHEUKUMOGAMI,1);
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
		you.half_youkai[0]=randA(3);
		you.half_youkai[1]=randA(2);
		you.half_youkai[2]=randA(2);
		you.half_youkai[3]=randA(1);
		//you.half_youkai[0]=2;
		//you.half_youkai[1]=2;
		//you.half_youkai[2]=0;
		//you.half_youkai[3]=1;
		break;
	case TRI_WRAITH:
		you.SetProperty(TPT_HP,1);
		you.SetProperty(TPT_COLD_RESIST,1);
		you.SetProperty(TPT_STEALTH,2);
		you.SetProperty(TPT_POISON_RESIST,1);
		you.SetProperty(TPT_GHOST_FOOT,1);
		break;
	case TRI_VAMPIRE:
		you.SetProperty(TPT_HP,1);
		you.SetProperty(TPT_REGEN,2);
		you.SetProperty(TPT_MP_REGEN,-1);
		you.SetProperty(TPT_POWER_SAVE,-1);
		you.SetProperty(TPT_EYE,1);
		you.SetProperty(TPT_BLOOD_MAGIC,1);
		break;
	default:
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
		if(level_ == 15)
		{
			printlog("당신에게 푹신푹신한 털이 자라났다.",true,false,false,CL_small_danger);
			you.SetProperty(TPT_FUR,1);
		}
		break;
	case TRI_OARFISH:
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		if(level_ == 9)
		{
			printlog("당신의 비늘이 단단해졌다.",true,false,false,CL_small_danger);
			you.DeleteProperty(TPT_SCALE);
			you.SetProperty(TPT_SCALE,2);
		}
		if(level_ == 18)
		{
			printlog("당신의 비늘이 더욱 단단해졌다.",true,false,false,CL_small_danger);
			you.DeleteProperty(TPT_SCALE);
			you.SetProperty(TPT_SCALE,3);
		}
		break;
	case TRI_CHEUKUMOGAMI:
		if(level_%5 == 0)
		{
			(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX));
		}
		if(level_%5 == 0)
		{
			you.max_mp--;
			you.mp--;
		}
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
	{
		ostringstream oss;
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		if(level_ == 4)
		{
			switch(you.half_youkai[0])
			{
			case 0:
				printlog("당신에겐 수인의 피가 흐르고 있다! 당신의 특성은 전사에 적합하다.",true,false,false,CL_small_danger);
				printlog("당신에게 손톱이 자라났다.",true,false,false,CL_small_danger);
				you.SetProperty(TPT_CLAW,1);
				oss << "반요 변이발현: " << getTribeProperty(TPT_CLAW, 1);
				AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
				break;
			case 1:
				printlog("당신에겐 오니의 피가 흐르고 있다! 당신의 특성은 강한 맷집으로 이어진다.",true,false,false,CL_small_danger);
				printlog("당신에게 뿔이 자라났다.",true,false,false,CL_small_danger);
				you.SetProperty(TPT_HORN,1);
				oss << "반요 변이발현: " << getTribeProperty(TPT_HORN, 1);
				AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
				break;
			case 2:
				printlog("당신에겐 용의 피가 흐르고 있다! 당신의 특성은 속성을 다루는데 능숙하다.",true,false,false,CL_small_danger);
				printlog("당신에게 비늘이 자라났다.",true,false,false,CL_small_danger);
				you.SetProperty(TPT_SCALE,1);
				oss << "반요 변이발현: " << getTribeProperty(TPT_SCALE, 1);
				AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
				break;
			case 3:
				printlog("당신에겐 악마의 피가 흐르고 있다! 당신의 특성은 마법사용에 집중된다.",true,false,false,CL_small_danger);
				printlog("당신은 마나재생력이 빨라졌다.",true,false,false,CL_small_danger);
				you.SetProperty(TPT_MP_REGEN,1);
				oss << "반요 변이발현: " << getTribeProperty(TPT_MP_REGEN, 1);
				AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
				break;
			}
		}
		if(level_ == 9)
		{
			switch(you.half_youkai[0])
			{
			case 0:
				switch(you.half_youkai[1])
				{
				case 0:	
					printlog("수인의 혈통이 더욱 강해졌다. 당신에게 강한 턱이 자라났다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_JAW,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_JAW, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("수인의 혈통이 더욱 강해졌다. 당신의 다리는 도약할수있을만큼 강해졌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_FOOT,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_FOOT, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog("수인의 혈통이 더욱 강해졌다. 당신의 시력이 좋아졌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_EYE,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_EYE, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 1:
				switch(you.half_youkai[1])
				{
				case 0:	
					printlog("오니의 혈통이 더욱 강해졌다. 당신은 튼튼해졌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_HP,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_HP, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("오니의 혈통이 더욱 강해졌다. 당신은 독에 저항이 생겼다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_POISON_RESIST,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_POISON_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog("오니의 혈통이 더욱 강해졌다. 당신은 마법저항이 높아졌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_MAGIC_RESIST,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_MAGIC_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 2:
				switch(you.half_youkai[1])
				{
				case 0:	
					printlog("용의 혈통이 더욱 강해졌다. 당신은 화염에 저항이 생겼다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_FIRE_RESIST,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_FIRE_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("용의 혈통이 더욱 강해졌다. 당신은 냉기에 저항이 생겼다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_COLD_RESIST,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_COLD_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog("용의 혈통이 더욱 강해졌다. 당신은 전기에 저항이 생겼다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_ELEC_RESIST,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_ELEC_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 3:
				switch(you.half_youkai[1])
				{
				case 0:	
					printlog("악마의 혈통이 더욱 강해졌다. 당신에 큰 날개가 생겼다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_FLY,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_FLY, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("악마의 혈통이 더욱 강해졌다. 당신은 명석해졌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_CONFUSE_RESIST,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_CONFUSE_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog("악마의 혈통이 더욱 강해졌다. 당신은 은밀해졌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_STEALTH,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_STEALTH, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			}
		}
		
		if(level_ == 13)
		{
			switch(you.half_youkai[0])
			{
			case 0:
				switch(you.half_youkai[2])
				{
				case 0:	
					printlog("수인의 혈통이 더욱 강해졌다. 당신에게 푹신푹신한 털이 자라났다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_FUR,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_FUR, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("수인의 혈통이 더욱 강해졌다. 당신의 발이 빨라졌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_SPEED,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_SPEED, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog("수인의 혈통이 더욱 강해졌다. 당신은 강한 재생력이 생겼다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_REGEN,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_REGEN, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 1:
				switch(you.half_youkai[2])
				{
				case 0:	
					printlog("오니의 혈통이 더욱 강해졌다. 당신의 피부는 단단해졌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_SKIN_AC,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_SKIN_AC, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("오니의 혈통이 더욱 강해졌다. 당신은 강한 재생력이 생겼다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_REGEN,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_REGEN, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog("오니의 혈통이 더욱 강해졌다. 당신은 엄청난 힘이 생겼다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_STR,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_STR, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 2:
				switch(you.half_youkai[2])
				{
				case 0:	
					printlog("용의 혈통이 더욱 강해졌다. 당신은 구름을 몰고 다닌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_CLOUD,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_CLOUD, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("용의 혈통이 더욱 강해졌다. 당신은 입에서 브레스를 쏠 수 있다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_BREATH,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_BREATH, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog("용의 혈통이 더욱 강해졌다. 당신의 비늘은 더욱 두꺼워졌다.",true,false,false,CL_small_danger);
					you.DeleteProperty(TPT_SCALE);
					you.SetProperty(TPT_SCALE,2);
					oss << "반요 변이강화: " << getTribeProperty(TPT_SCALE, 2);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					switch(you.half_youkai[1])
					{
					case 0:
						you.DeleteProperty(TPT_FIRE_RESIST);
						you.SetProperty(TPT_FIRE_RESIST,2);
						oss << "반요 변이강화: " << getTribeProperty(TPT_FIRE_RESIST, 2);
						AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
						break;
					case 1:
						you.DeleteProperty(TPT_COLD_RESIST);
						you.SetProperty(TPT_COLD_RESIST,2);
						oss << "반요 변이강화: " << getTribeProperty(TPT_COLD_RESIST, 2);
						AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
						break;
					case 2:		
						you.DeleteProperty(TPT_ELEC_RESIST);		
						you.SetProperty(TPT_ELEC_RESIST,2);
						oss << "반요 변이강화: " << getTribeProperty(TPT_ELEC_RESIST, 2);
						AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
						break;
					}
					break;
				}	
				break;
			case 3:
				switch(you.half_youkai[2])
				{
				case 0:	
					printlog("악마의 혈통이 더욱 강해졌다. 당신의 마법은 더욱 강력해졌다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_SPELL_POWER,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_SPELL_POWER, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("악마의 혈통이 더욱 강해졌다. 당신은 손짓만으로 마법을 영창할 수 있다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_FINGER_MAGIC,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_FINGER_MAGIC, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog("악마의 혈통이 더욱 강해졌다. 당신은 자신의 피로 마법을 영창할 수 있다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_BLOOD_MAGIC,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_BLOOD_MAGIC, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			}
		}
		
		if(level_ == 18)
		{
			switch(you.half_youkai[0])
			{
			case 0:
				switch(you.half_youkai[3])
				{
				case 0:	
					printlog("수인의 마지막 특성이 발현되었다. 당신은 동물적인 전투감각을 깨우쳤다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_SLAY,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_SLAY, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("수인의 마지막 특성이 발현되었다. 당신의 뛰어난 공격은 상대를 혼란하게 만든다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_CONFUSE_ATTACK,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_CONFUSE_ATTACK, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 1:
				switch(you.half_youkai[3])
				{
				case 0:	
					printlog("오니의 마지막 특성이 발현되었다. 당신은 놀랄만큼 튼튼해졌다.",true,false,false,CL_small_danger);
					if(you.half_youkai[1]==0)
					{
						you.DeleteProperty(TPT_HP);
						you.SetProperty(TPT_HP,3);
						oss << "반요 변이강화: " << getTribeProperty(TPT_HP, 3);
						AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					}
					else {
						you.SetProperty(TPT_HP, 2);
						oss << "반요 변이발현: " << getTribeProperty(TPT_HP, 2);
						AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					}
					break;
				case 1:
					printlog("오니의 마지막 특성이 발현되었다. 당신은 초월적인 회피재능에 눈을 떴다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_EV,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_EV, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 2:
				switch(you.half_youkai[3])
				{
				case 0:	
					printlog("용의 마지막 특성이 발현되었다. 당신은 공기의 흐름을 다룰 수 있게 되었다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_GRAZE_CONTROL,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_GRAZE_CONTROL, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("용의 마지막 특성이 발현되었다. 당신은 자연의 힘을 몸에 두르게 되었다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_FORCE_OF_NATURE,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_FORCE_OF_NATURE, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 3:
				switch(you.half_youkai[3])
				{
				case 0:	
					printlog("악마의 마지막 특성이 발현되었다. 당신은 초월적인 영력회복속도를 얻었다.",true,false,false,CL_small_danger);
					you.DeleteProperty(TPT_MP_REGEN);
					you.SetProperty(TPT_MP_REGEN,3);
					oss << "반요 변이강화: " << getTribeProperty(TPT_MP_REGEN, 3);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog("악마의 마지막 특성이 발현되었다. 당신은 지옥의 고통을 불러올 수 있게 되었다.",true,false,false,CL_small_danger);
					you.SetProperty(TPT_TORMENT,1);
					oss << "반요 변이발현: " << getTribeProperty(TPT_TORMENT, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			}
		}
		break;
	}
	case TRI_WRAITH:
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		break;
	case TRI_VAMPIRE:
		if(level_%5 == 0)
		{
			you.max_mp--;
			you.mp--;
		}
		break;
	case TRI_YOKAI:
		if(level_%5 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
		if(level_ == 15 && you.char_type == UNIQ_START_KOISHI)
		{
			printlog("당신의 뛰어난 공격은 상대를 혼란하게 만든다.",true,false,false,CL_small_danger);
			you.SetProperty(TPT_CONFUSE_ATTACK,1);
		}
		break;
	default:
		break;
	}
}