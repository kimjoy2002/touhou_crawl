//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: tribe.h
//
// 내용: 종족 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __TRIBE_H__
#define  __TRIBE_H__

#include <string>
#include "d3dUtility.h"

using namespace std;

enum tribe_type;

enum tribe_proper_type
{
	TPT_FIRE_RESIST,
	TPT_COLD_RESIST,
	TPT_ELEC_RESIST,
	TPT_POISON_RESIST,
	TPT_STEALTH,
	TPT_FLY,	
	TPT_SWIM,
	TPT_SIZE,
	TPT_HORN,
	TPT_GHOST_FOOT,
	TPT_CHEUKUMOGAMI,
	TPT_HP,
	TPT_INVISIBLE,
	TPT_POWER_SAVE,
	TPT_9_LIFE,
	TPT_18_LIFE,
	TPT_SPEED,
	TPT_CLAW,
	TPT_JAW,
	TPT_FOOT,
	TPT_EYE,
	TPT_FUR,
	TPT_REGEN,
	TPT_SLAY,	
	TPT_CONFUSE_ATTACK,
	TPT_MAGIC_RESIST,
	TPT_SKIN_AC,
	TPT_STR,
	TPT_EV,
	TPT_CLOUD,
	TPT_BREATH,
	TPT_SCALE,
	TPT_GRAZE_CONTROL,
	TPT_FORCE_OF_NATURE,
	TPT_MP_REGEN,
	TPT_CONFUSE_RESIST,
	TPT_SPELL_POWER,
	TPT_FINGER_MAGIC,
	TPT_BLOOD_MAGIC,
	TPT_TORMENT,
	TPT_CLOUD_RESIST,
	TPT_SEE_INVI,
	TPT_FIRE_IMUNE,
	TPT_COLD_IMUNE,
	TPT_ELEC_IMUNE,
	TPT_PURE_MP,
	TPT_PURE_POWER,
	TPT_PURE_LIFE,
	TPT_MAX
};



class tribe_property
{
public:
	tribe_proper_type id;
	int value;
	tribe_property():id(TPT_FIRE_RESIST),value(0){}
	tribe_property(tribe_proper_type id_, int value_):id(id_),value(value_){}
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);

	string GetName();
	string GetInfor();
	string GetDetail();
	D3DCOLOR getColor();
	void gain(bool gain_);
};




void SetTribe(tribe_type select_);
void PropertyView();
void LevelUpTribe(int level_);





#endif // __TRIBE_H__