//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: weapon.h
//
// 내용: 무기 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __WEAPON_H__
#define  __WEAPON_H__



enum weapon_brand
{
	WB_NORMAL =0,
	WB_FIRE,
	WB_COLD,
	WB_POISON,
	WB_CURSE,
	WB_WEATHER,
	WB_AUTUMN,
	WB_MANA_REGEN,
	WB_FAST_CAST,
	WB_PROTECT,
	WB_MAX
};

int GetNewBrand(int rare_weigth_); //브랜드가 나올 확률
int GetPulsDamage(weapon_brand brand, int damage);
int GetAttType(weapon_brand brand);
const char* GetBrandString(weapon_brand brand, bool artifact_);
const char* GetBrandInfor(weapon_brand brand);


#endif // __WEAPON_H__