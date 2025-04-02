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
LOCALIZATION_ENUM_KEY GetBrandString(weapon_brand brand, bool artifact_)
{
	switch(brand)
	{
		case WB_FIRE:
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_FIRE:LOC_SYSTEM_ITEM_WEAPON_BRAND_FIRE;
		case WB_COLD:
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_COLD:LOC_SYSTEM_ITEM_WEAPON_BRAND_COLD;
		case WB_POISON:
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_POISON:LOC_SYSTEM_ITEM_WEAPON_BRAND_POISON;
		case WB_CURSE:		
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_CURSE:LOC_SYSTEM_ITEM_WEAPON_BRAND_CURSE;
		case WB_WEATHER	:
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_WEATHER:LOC_SYSTEM_ITEM_WEAPON_BRAND_WEATHER;
		case WB_AUTUMN:
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_AUTUMN:LOC_SYSTEM_ITEM_WEAPON_BRAND_AUTUMN;
		case WB_MANA_REGEN:
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_MANA_REGEN:LOC_SYSTEM_ITEM_WEAPON_BRAND_MANA_REGEN;
		case WB_FAST_CAST:
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_FASTCAST:LOC_SYSTEM_ITEM_WEAPON_BRAND_FASTCAST;
		case WB_PROTECT:
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_PROTECT:LOC_SYSTEM_ITEM_WEAPON_BRAND_PROTECT;
		default:
			return !artifact_?LOC_SYSTEM_ITEM_WEAPON_BRAND_OF_BUG:LOC_SYSTEM_ITEM_WEAPON_BRAND_BUG;
	}	

}

string GetBrandInfor(weapon_brand brand)
{
	switch(brand)
	{
		case WB_FIRE:
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_FIRE);
		case WB_COLD:
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_COLD);
		case WB_POISON:
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_POISON);
		case WB_CURSE:		
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_CURSE);
		case WB_WEATHER	:
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_WEATHER);
		case WB_AUTUMN:
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_AUTUMN);
		case WB_MANA_REGEN:
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_MANA_REGEN);
		case WB_FAST_CAST:
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_FASTCAST);
		case WB_PROTECT:
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_PROTECT);
		default:
			return LocalzationManager::locString(LOC_SYSTEM_ITEM_WEAPON_BRAND_DESCRIBE_BUG);	
	}	

}