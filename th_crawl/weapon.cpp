//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: weapon.h
//
// 내용: 무기 관련 함수들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "weapon.h"
#include "enum.h"
#include "common.h"
#include "player.h"


int GetNewBrand(int rare_weigth_)
{
	if(randA(99)>=rare_weigth_)
	{
		int arr_[] = {WB_FIRE,WB_COLD,WB_POISON,WB_PROTECT};
		return arr_[randA(3)];
	}
	else
	{
		int arr_[] = {WB_CURSE,WB_AUTUMN,WB_WEATHER,WB_MANA_REGEN,WB_FAST_CAST,WB_PROTECT};
		return arr_[randA(5)];
	}
	return WB_NORMAL;

}

int GetPulsDamage(weapon_brand brand, int damage)
{
	switch(brand)
	{
		case WB_FIRE:
		case WB_COLD:
			damage += damage/3;
			break;
		case WB_WEATHER:
			if (you.s_weather) {
				damage += damage / 2;
			}
			break;
		default:
			break;
	}
	return damage;
}
int GetAttType(weapon_brand brand)
{
	int att_type = ATT_NORMAL;
	switch(brand)
	{
		case WB_FIRE:
			att_type = ATT_FIRE;
			break;
		case WB_COLD:
			att_type = ATT_COLD;
			break;
		case WB_POISON:
			att_type = ATT_S_POISON;
			break;
		case WB_CURSE:	
			att_type = ATT_CURSE;		
			break;
		case WB_WEATHER:
			att_type = ATT_WEATHER;
			break;
		case WB_AUTUMN:
			att_type = ATT_AUTUMN;
			break;
		case WB_MANA_REGEN:
		case WB_FAST_CAST:
		case WB_PROTECT:
		default:
			break;
	}
	return att_type;	
}
const char* GetBrandString(weapon_brand brand, bool artifact_)
{
	switch(brand)
	{
		case WB_FIRE:
			return !artifact_?"화염의 ":"화염";	
		case WB_COLD:
			return !artifact_?"냉기의 ":"냉기";
		case WB_POISON:
			return !artifact_?"맹독의 ":"맹독";	
		case WB_CURSE:		
			return !artifact_?"저주의 ":"저주";	
		case WB_WEATHER	:
			return !artifact_?"비상의 ":"비상";	
		case WB_AUTUMN:
			return !artifact_?"단풍의 ":"단풍";	
		case WB_MANA_REGEN:
			return !artifact_?"영력회복의 ":"영력회복";	
		case WB_FAST_CAST:
			return !artifact_?"고속영창의 ":"고속영창";	
		case WB_PROTECT:
			return !artifact_?"보호의 ":"보호";	
		default:
			return !artifact_?"알수없는 ":"버그";	
	}	

}


const char* GetBrandInfor(weapon_brand brand)
{
	switch(brand)
	{
		case WB_FIRE:
			return "이 무기는 화염으로 덮여있다. 데미지에 1/3의 추가 화염 데미지를 더한다.";
		case WB_COLD:
			return "이 무기는 냉기가 휘감겨있다. 데미지에 1/3의 추가 냉기 데미지를 더한다.";
		case WB_POISON:
			return "이 무기는 맹독이 발라져있다. 공격한 적을 중독시킨다.";
		case WB_CURSE:		
			return "이 무기는 저주가 뿜어져나오고 있다. 공격한 적에 저항할 수 없는 독과 일정확률로 감속을 건다.";
		case WB_WEATHER	:
			return "이 무기는 다양한 속성의 공격이 무작위로 베어나온다. 날씨가 발현중이라면 50%의 추가 데미지를 준다.";
		case WB_AUTUMN:
			return "이 무기는 단검 수준의 암습이 가능하게 되고 이미 단검인 경우엔 깨어난 적도 암습할 수 있다.";
		case WB_MANA_REGEN:
			return "들고있는것만으로 영력의 회복속도를 늘려준다.";
		case WB_FAST_CAST:
			return "이 무기는 들고있는것만으로도 당신의 모든 마법 영창시간을 80%로 줄여준다.";
		case WB_PROTECT:
			return "이 무기는 들고있는것만으로도 당신의 AC를 5 증가시켜준다.";
		default:
			return "이 무기는 버그의 브랜드를 두르고 있다. 신고하세요!";	
	}	

}