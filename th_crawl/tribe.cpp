//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: tribe.h
//
// 내용: 종족 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "tribe.h"
#include "enum.h"
#include "rect.h"
#include "player.h"
#include "mon_infor.h"
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


LOCALIZATION_ENUM_KEY getTribePropertyKey(tribe_proper_type id, int value) {
	return tribe_property(id, value).GetNameKey();
}
string getTribeProperty(tribe_proper_type id, int value) {
	return tribe_property(id, value).GetName();
}
string getTribePropertyInfo(tribe_proper_type id, int value) {
	return tribe_property(id, value).GetDetail();
}

LOCALIZATION_ENUM_KEY tribe_property::GetNameKey()
{
	switch(id)
	{
	case TPT_FIRE_RESIST:
		return LOC_SYSTEM_TRIBE_PROPERTY_FIRE_RESIST;
	case TPT_COLD_RESIST:
		return LOC_SYSTEM_TRIBE_PROPERTY_COLD_RESIST;
	case TPT_ELEC_RESIST:
		return LOC_SYSTEM_TRIBE_PROPERTY_ELEC_RESIST;
	case TPT_POISON_RESIST:
		return LOC_SYSTEM_TRIBE_PROPERTY_POISON_RESIST;
	case TPT_STEALTH:
		return LOC_SYSTEM_TRIBE_PROPERTY_STEALTH;
	case TPT_FLY:
		return LOC_SYSTEM_TRIBE_PROPERTY_FLY;
	case TPT_SWIM:
		return LOC_SYSTEM_TRIBE_PROPERTY_SWIM;
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return LOC_SYSTEM_TRIBE_PROPERTY_SIZE1;
			case -1:
				return LOC_SYSTEM_TRIBE_PROPERTY_SIZE2;
			default:
				return LOC_SYSTEM_TRIBE_PROPERTY_BUG;
			}
		}
	case TPT_HORN:
		return LOC_SYSTEM_TRIBE_PROPERTY_HORN;
	case TPT_GHOST_FOOT:
		return LOC_SYSTEM_TRIBE_PROPERTY_GHOST_FOOT;
	case TPT_CHEUKUMOGAMI:
		return LOC_SYSTEM_TRIBE_PROPERTY_CHEUKUMOGAMI;
	case TPT_HP:
		return LOC_SYSTEM_TRIBE_PROPERTY_HP;
	case TPT_INVISIBLE:
		return LOC_SYSTEM_TRIBE_PROPERTY_INVISIBLE;
	case TPT_POWER_SAVE:
		{
			switch(value)
			{
			case 1:
				return LOC_SYSTEM_TRIBE_PROPERTY_POWER_SAVE1;
			case -1:
				return LOC_SYSTEM_TRIBE_PROPERTY_POWER_SAVE2;
			default:
				return LOC_SYSTEM_TRIBE_PROPERTY_BUG;
			}
		}
	case TPT_9_LIFE:
		return LOC_SYSTEM_TRIBE_PROPERTY_MORE_LIFE;
	case TPT_18_LIFE:
		return LOC_SYSTEM_TRIBE_PROPERTY_MORE_LIFE;
	case TPT_SPEED:
		{
			switch(value)
			{
			case 1:
				return LOC_SYSTEM_TRIBE_PROPERTY_SPEED1;
			case -1:
				return LOC_SYSTEM_TRIBE_PROPERTY_SPEED2;
			default:
				return LOC_SYSTEM_TRIBE_PROPERTY_BUG;
			}
		}
	case TPT_CLAW:
		return LOC_SYSTEM_TRIBE_PROPERTY_CLAW;		
	case TPT_JAW:
		return LOC_SYSTEM_TRIBE_PROPERTY_JAW;	
	case TPT_FOOT:
		return LOC_SYSTEM_TRIBE_PROPERTY_FOOT;
	case TPT_EYE:
		return LOC_SYSTEM_TRIBE_PROPERTY_EYE;
	case TPT_FUR:
		return LOC_SYSTEM_TRIBE_PROPERTY_FUR;
	case TPT_REGEN:
		{
			switch(value)
			{
			case 1:
			case 2:
			case 3:
				return LOC_SYSTEM_TRIBE_PROPERTY_REGEN1;	
			case -1:
			case -2:
			case -3:
				return LOC_SYSTEM_TRIBE_PROPERTY_REGEN2;
			default:
				return LOC_SYSTEM_TRIBE_PROPERTY_BUG;
			}
		}
	case TPT_SLAY:
		return LOC_SYSTEM_TRIBE_PROPERTY_SLAY;
	case TPT_CONFUSE_ATTACK:
		return LOC_SYSTEM_TRIBE_PROPERTY_CONFUSE_ATTACK;
	case TPT_MAGIC_RESIST:
		return LOC_SYSTEM_TRIBE_PROPERTY_MAGIC_RESIST;
	case TPT_SKIN_AC:
		return LOC_SYSTEM_TRIBE_PROPERTY_SKIN_AC;
	case TPT_STR:
		return LOC_SYSTEM_TRIBE_PROPERTY_STR;
	case TPT_EV:
		return LOC_SYSTEM_TRIBE_PROPERTY_EV;
	case TPT_CLOUD:
		return LOC_SYSTEM_TRIBE_PROPERTY_CLOUD;
	case TPT_BREATH:
		return LOC_SYSTEM_TRIBE_PROPERTY_BREATH;
	case TPT_SCALE:
		return LOC_SYSTEM_TRIBE_PROPERTY_SCALE;
	case TPT_GRAZE_CONTROL:
		return LOC_SYSTEM_TRIBE_PROPERTY_GRAZE_CONTROL;
	case TPT_FORCE_OF_NATURE:
		return LOC_SYSTEM_TRIBE_PROPERTY_FORCE_OF_NATURE;
	case TPT_MP_REGEN:
		{
			switch(value)
			{
			case 1:
				return LOC_SYSTEM_TRIBE_PROPERTY_MP_REGEN1;
			case -1:
				return LOC_SYSTEM_TRIBE_PROPERTY_MP_REGEN2;
			default:
				return LOC_SYSTEM_TRIBE_PROPERTY_BUG;
			}
		}
	case TPT_CONFUSE_RESIST:
		return LOC_SYSTEM_TRIBE_PROPERTY_CONFUSE_RESIST;
	case TPT_SPELL_POWER:
		return LOC_SYSTEM_TRIBE_PROPERTY_SPELL_POWER;
	case TPT_FINGER_MAGIC:
		return LOC_SYSTEM_TRIBE_PROPERTY_FINGER_MAGIC;
	case TPT_BLOOD_MAGIC:
		return LOC_SYSTEM_TRIBE_PROPERTY_BLOOD_MAGIC;
	case TPT_TORMENT:
		return LOC_SYSTEM_TRIBE_PROPERTY_TORMENT;
	case TPT_CLOUD_RESIST:
		return LOC_SYSTEM_TRIBE_PROPERTY_CLOUD_RESIST;
	case TPT_SEE_INVI:
		return LOC_SYSTEM_TRIBE_PROPERTY_SEE_INVI;
	case TPT_FIRE_IMUNE:
		return LOC_SYSTEM_TRIBE_PROPERTY_FIRE_IMUNE;
	case TPT_COLD_IMUNE:
		return LOC_SYSTEM_TRIBE_PROPERTY_COLD_IMUNE;
	case TPT_ELEC_IMUNE:
		return LOC_SYSTEM_TRIBE_PROPERTY_ELEC_IMUNE;
	case TPT_PURE_MP:
		return LOC_SYSTEM_TRIBE_PROPERTY_PURE_MP;
	case TPT_PURE_POWER:
		return LOC_SYSTEM_TRIBE_PROPERTY_PURE_POWER;
	case TPT_PURE_LIFE:
		return LOC_SYSTEM_TRIBE_PROPERTY_PURE_LIFE;
	case TPT_PURE_SYSTEM:
		return LOC_SYSTEM_TRIBE_PROPERTY_PURE_SYSTEM;
	case TPT_STG_SPREAD_SHOT:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_SPREAD_SHOT;
	case TPT_STG_TRIPLE_SHOT:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_TRIPLE_SHOT;
	case TPT_STG_BACK_SHOT:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_BACK_SHOT;
	case TPT_STG_LASER_SHOT:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_LASER_SHOT;
	case TPT_STG_SPEED:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_SPEED;
	case TPT_STG_OPTION:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_OPTION;
	case TPT_STG_STATIC_ELECTRONIC:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_STATIC_ELECTRONIC;
	case TPT_STG_SOUL_BOMB:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_SOUL_BOMB;
	case TPT_STG_SHIELD:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_SHIELD;
	case TPT_STG_HP_RECOVERY:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_HP_RECOVERY;
	case TPT_STG_MP_RECOVERY:
		return LOC_SYSTEM_TRIBE_PROPERTY_STG_MP_RECOVERY;
	default:
		break;
	}
	return LOC_SYSTEM_TRIBE_PROPERTY_BUG;
}


string tribe_property::GetName()
{
	switch(id)
	{
	default:
		return LocalzationManager::locString(GetNameKey());
	case TPT_HP:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::formatString(GetNameKey(), PlaceHolderHelper("+30"));
			case 2:
				return LocalzationManager::formatString(GetNameKey(), PlaceHolderHelper("+20"));
			case 1:
				return LocalzationManager::formatString(GetNameKey(), PlaceHolderHelper("+10"));
			case -1:
				return LocalzationManager::formatString(GetNameKey(), PlaceHolderHelper("-10"));
			case -2:
				return LocalzationManager::formatString(GetNameKey(), PlaceHolderHelper("-20"));
			case -3:
				return LocalzationManager::formatString(GetNameKey(), PlaceHolderHelper("-30"));
			default:
				return LocalzationManager::locString(GetNameKey());
			}
		}
	}
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
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FIRE_RESIST1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FIRE_RESIST2);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FIRE_RESIST3);
			case -2:
			case -3:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FIRE_RESIST4);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}
	case TPT_COLD_RESIST:
		{
			switch(value)
			{
			case 3:
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_COLD_RESIST1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_COLD_RESIST2);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_COLD_RESIST3);
			case -2:
			case -3:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_COLD_RESIST4);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}
	case TPT_ELEC_RESIST:
		{
			switch(value)
			{
			case 3:
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_ELEC_RESIST1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_ELEC_RESIST2);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_ELEC_RESIST3);
			case -2:
			case -3:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_ELEC_RESIST4);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}
	case TPT_POISON_RESIST:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_POISON_RESIST);
	case TPT_STEALTH:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STEALTH, PlaceHolderHelper("+3"));
			case 2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STEALTH, PlaceHolderHelper("+2"));
			case 1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STEALTH, PlaceHolderHelper("+1"));
			case -1:
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}	
	case TPT_FLY:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FLY);
	case TPT_SWIM:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SWIM);
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SIZE1);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SIZE2);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}
	case TPT_HORN:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_HORN);
	case TPT_GHOST_FOOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_GHOST_FOOT);
	case TPT_CHEUKUMOGAMI:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_CHEUKUMOGAMI);
	case TPT_HP:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_HP1, PlaceHolderHelper("+30"));
			case 2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_HP2, PlaceHolderHelper("+20"));
			case 1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_HP3, PlaceHolderHelper("+10"));
			case -1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_HP4, PlaceHolderHelper("-10"));
			case -2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_HP5, PlaceHolderHelper("-20"));
			case -3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_HP6, PlaceHolderHelper("-30"));
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}
	case TPT_INVISIBLE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_INVISIBLE);
	case TPT_POWER_SAVE:
		{
			switch(value)
			{
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_POWER_SAVE1);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_POWER_SAVE2);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}
	case TPT_9_LIFE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_9_LIFE);
	case TPT_18_LIFE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_18_LIFE);
	case TPT_SPEED:
		{
			switch(value)
			{
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SPEED1);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SPEED2);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}
	case TPT_CLAW:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_CLAW1);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_CLAW2);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_CLAW3);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}	
	case TPT_JAW:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_JAW);	
	case TPT_FOOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FOOT);
	case TPT_EYE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_EYE);
	case TPT_FUR:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FUR, PlaceHolderHelper("+3"));
	case TPT_REGEN:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_REGEN1, PlaceHolderHelper("+3"));
			case 2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_REGEN1, PlaceHolderHelper("+2"));
			case 1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_REGEN1, PlaceHolderHelper("+1"));
			case -1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_REGEN2, PlaceHolderHelper("-1"));
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}	
	case TPT_SLAY:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SLAY);
	case TPT_CONFUSE_ATTACK:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_CONFUSE_ATTACK);
	case TPT_MAGIC_RESIST:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_MAGIC_RESIST);
	case TPT_SKIN_AC:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SKIN_AC, PlaceHolderHelper("+5"));
	case TPT_STR:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STR, PlaceHolderHelper("+5"));
	case TPT_EV:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_EV, PlaceHolderHelper("+10"));
	case TPT_CLOUD:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_CLOUD);
	case TPT_BREATH:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BREATH);
	case TPT_SCALE:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SCALE1, PlaceHolderHelper("+9"));
			case 2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SCALE2, PlaceHolderHelper("+6"));
			case 1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SCALE3, PlaceHolderHelper("+3"));
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}	
	case TPT_GRAZE_CONTROL:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_GRAZE_CONTROL);
	case TPT_FORCE_OF_NATURE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FORCE_OF_NATURE);
	case TPT_MP_REGEN:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_MP_REGEN1, PlaceHolderHelper("+3"));
			case 2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_MP_REGEN1, PlaceHolderHelper("+2"));
			case 1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_MP_REGEN1, PlaceHolderHelper("+1"));
			case -1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_MP_REGEN2, PlaceHolderHelper("-1"));
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
			}
		}	
	case TPT_CONFUSE_RESIST:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_CONFUSE_RESIST);
	case TPT_SPELL_POWER:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SPELL_POWER);
	case TPT_FINGER_MAGIC:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FINGER_MAGIC);
	case TPT_BLOOD_MAGIC:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BLOOD_MAGIC);
	case TPT_TORMENT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_TORMENT);
	case TPT_CLOUD_RESIST:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_CLOUD_RESIST);
	case TPT_SEE_INVI:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_SEE_INVI);
	case TPT_FIRE_IMUNE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_FIRE_IMUNE);
	case TPT_COLD_IMUNE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_COLD_IMUNE);
	case TPT_ELEC_IMUNE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_ELEC_IMUNE);
	case TPT_PURE_MP:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_PURE_MP);
	case TPT_PURE_POWER:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_PURE_POWER);
	case TPT_PURE_LIFE:
		return value>1?LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_PURE_LIFE1):LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_PURE_LIFE2); 
	case TPT_PURE_SYSTEM:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_PURE_SYSTEM);
	case TPT_STG_SPREAD_SHOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_SPREAD_SHOT);
	case TPT_STG_TRIPLE_SHOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_TRIPLE_SHOT);
	case TPT_STG_BACK_SHOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_BACK_SHOT);
	case TPT_STG_LASER_SHOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_LASER_SHOT);
	case TPT_STG_SPEED:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_SPEED);
	case TPT_STG_OPTION:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_OPTION, PlaceHolderHelper(to_string(value)));
	case TPT_STG_STATIC_ELECTRONIC:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_STATIC_ELECTRONIC);
	case TPT_STG_SOUL_BOMB:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_SOUL_BOMB);
	case TPT_STG_SHIELD:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_SHIELD);
	case TPT_STG_HP_RECOVERY:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_HP_RECOVERY);
	case TPT_STG_MP_RECOVERY:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_STG_MP_RECOVERY);
	default:
		break;
	}
	return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DESCRIBE_BUG);
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
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FIRE_RESIST1, PlaceHolderHelper("3"));
			case 2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FIRE_RESIST1, PlaceHolderHelper("2"));
			case 1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FIRE_RESIST1, PlaceHolderHelper("1"));
			case -1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FIRE_RESIST2, PlaceHolderHelper("1"));
			case -2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FIRE_RESIST2, PlaceHolderHelper("2"));
			case -3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FIRE_RESIST2, PlaceHolderHelper("3"));
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
			}
		}
	case TPT_COLD_RESIST:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_COLD_RESIST1, PlaceHolderHelper("3"));
			case 2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_COLD_RESIST1, PlaceHolderHelper("2"));
			case 1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_COLD_RESIST1, PlaceHolderHelper("1"));
			case -1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_COLD_RESIST2, PlaceHolderHelper("1"));
			case -2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_COLD_RESIST2, PlaceHolderHelper("2"));
			case -3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_COLD_RESIST2, PlaceHolderHelper("3"));
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
			}
		}
	case TPT_ELEC_RESIST:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_ELEC_RESIST1, PlaceHolderHelper("3"));
			case 2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_ELEC_RESIST1, PlaceHolderHelper("2"));
			case 1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_ELEC_RESIST1, PlaceHolderHelper("1"));
			case -1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_ELEC_RESIST2, PlaceHolderHelper("1"));
			case -2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_ELEC_RESIST2, PlaceHolderHelper("2"));
			case -3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_ELEC_RESIST2, PlaceHolderHelper("3"));
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
			}
		}
	case TPT_POISON_RESIST:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_POISON_RESIST);
	case TPT_STEALTH:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STEALTH);
	case TPT_FLY:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FLY);
	case TPT_SWIM:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SWIM);
	case TPT_SIZE:
		{
			switch(value)
			{
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SIZE1);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SIZE2);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
			}
		}
	case TPT_HORN:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_HORN);
	case TPT_GHOST_FOOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_GHOST_FOOT);
	case TPT_CHEUKUMOGAMI:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_CHEUKUMOGAMI, PlaceHolderHelper("5"));
	case TPT_HP:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_HP);
	case TPT_INVISIBLE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_INVISIBLE);
	case TPT_POWER_SAVE:		
		{
			switch(value)
			{
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_POWER_SAVE1);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_POWER_SAVE2);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
			}
		}
	case TPT_9_LIFE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_9_LIFE);
	case TPT_18_LIFE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_18_LIFE);
	case TPT_SPEED:
		{
			switch(value)
			{
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SPEED1);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SPEED2);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
			}
		}
	case TPT_CLAW:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_CLAW);
	case TPT_JAW:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_JAW);	
	case TPT_FOOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FOOT);
	case TPT_EYE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_EYE);
	case TPT_FUR:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FUR, PlaceHolderHelper("3"));
	case TPT_REGEN:
		{
			switch(value)
			{
			case 3:
			case 2:
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_REGEN1);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_REGEN2);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
			}
		}
	case TPT_SLAY:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SLAY, PlaceHolderHelper("+6"));
	case TPT_CONFUSE_ATTACK:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_CONFUSE_ATTACK);
	case TPT_MAGIC_RESIST:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_MAGIC_RESIST);
	case TPT_SKIN_AC:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SKIN_AC, PlaceHolderHelper("5"));
	case TPT_STR:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STR, PlaceHolderHelper("5"));
	case TPT_EV:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_EV, PlaceHolderHelper("10"));
	case TPT_CLOUD:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_CLOUD);
	case TPT_BREATH:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BREATH);
	case TPT_SCALE:
		{
			switch(value)
			{
			case 3:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SCALE1, PlaceHolderHelper("9"));
			case 2:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SCALE2, PlaceHolderHelper("6"));
			case 1:
				return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SCALE3, PlaceHolderHelper("3"));
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
			}
		}	
	case TPT_GRAZE_CONTROL:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_GRAZE_CONTROL);
	case TPT_FORCE_OF_NATURE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FORCE_OF_NATURE);
	case TPT_MP_REGEN:
		{
			switch(value)
			{
			case 3:
			case 2:
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_MP_REGEN1);
			case -1:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_MP_REGEN2);
			default:
				return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
			}
		}
	case TPT_CONFUSE_RESIST:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_CONFUSE_RESIST);
	case TPT_SPELL_POWER:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SPELL_POWER, PlaceHolderHelper("1.3"));
	case TPT_FINGER_MAGIC:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FINGER_MAGIC, PlaceHolderHelper("70"));
	case TPT_BLOOD_MAGIC:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BLOOD_MAGIC);
	case TPT_TORMENT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_TORMENT);
	case TPT_CLOUD_RESIST:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_CLOUD_RESIST);
	case TPT_SEE_INVI:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_SEE_INVI);
	case TPT_FIRE_IMUNE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_FIRE_IMUNE);
	case TPT_COLD_IMUNE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_COLD_IMUNE);
	case TPT_ELEC_IMUNE:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_ELEC_IMUNE);
	case TPT_PURE_MP:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_PURE_MP);
	case TPT_PURE_POWER:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_PURE_POWER);
	case TPT_PURE_LIFE:
		return LocalzationManager::formatString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_PURE_LIFE, PlaceHolderHelper(value>1?"2":"1"));
	case TPT_PURE_SYSTEM:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_PURE_SYSTEM);
	case TPT_STG_SPREAD_SHOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_SPREAD_SHOT);
	case TPT_STG_TRIPLE_SHOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_TRIPLE_SHOT);
	case TPT_STG_BACK_SHOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_BACK_SHOT);
	case TPT_STG_LASER_SHOT:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_LASER_SHOT);
	case TPT_STG_SPEED:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_SPEED);
	case TPT_STG_OPTION:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_OPTION);
	case TPT_STG_STATIC_ELECTRONIC:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_STATIC_ELECTRONIC);
	case TPT_STG_SOUL_BOMB:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_SOUL_BOMB);
	case TPT_STG_SHIELD:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_SHIELD);
	case TPT_STG_HP_RECOVERY:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_HP_RECOVERY);
	case TPT_STG_MP_RECOVERY:
		return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_STG_MP_RECOVERY);
	default:
		break;
	}
	return LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_DETAIL_BUG);
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
	case TPT_STG_SPREAD_SHOT:
	case TPT_STG_TRIPLE_SHOT:
	case TPT_STG_BACK_SHOT:
	case TPT_STG_LASER_SHOT:
	case TPT_STG_SPEED:
	case TPT_STG_OPTION:
	case TPT_STG_STATIC_ELECTRONIC:
	case TPT_STG_SOUL_BOMB:
	case TPT_STG_SHIELD:
	case TPT_STG_HP_RECOVERY:
	case TPT_STG_MP_RECOVERY:
		return CL_green;
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_HEAD_UNEQUIP),true,false,false,CL_danger);
			}
		}
		return;
	case TPT_GHOST_FOOT:
		if(you.equipment[ET_BOOTS])
		{
			if(you.unequip(ET_BOOTS,true))
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_FOOT_UNEQUIP),true,false,false,CL_danger);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_PROPERTY_HAND_UNEQUIP),true,false,false,CL_danger);
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
	case TPT_STG_SPREAD_SHOT:
		return;
	case TPT_STG_TRIPLE_SHOT:
		return;
	case TPT_STG_BACK_SHOT:
		return;
	case TPT_STG_LASER_SHOT:
		return;
	case TPT_STG_SPEED:
		return;
	case TPT_STG_OPTION:
	if(gain_)
	{
		dif_rect_iterator rit(you.position, 3);
		int i = 1;
		int count = value_;
		for (; !rit.end() && i > 0; rit++)
		{
			if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
			{
				monster* mon_ = env[current_level].AddMonster(MON_MAGICAL_STAR, M_FLAG_ALLY, *rit);
				mon_->SetInvincibility(-1, false);
				mon_->spell_lists.clear();
				count--;
				if(count == 0)
					break;
			}
		}
	} else {
		for(auto it = env[current_level].mon_vector.begin();  it != env[current_level].mon_vector.end() ;it++)
		{
			if(it->isLive() && it->id == MON_MAGICAL_STAR && it->isUserAlly() && it->s_invincibility != 0)
			{
				it->dead(PRT_NEUTRAL, false, true);
			}
		}
	}
		return;
	case TPT_STG_STATIC_ELECTRONIC:
		return;
	case TPT_STG_SOUL_BOMB:
		you.Ability(SKL_SOULSHOT,true,!gain_);
		return;
	case TPT_STG_SHIELD:
		if(value_>0) {
			you.SetShield(30,20);
		} else {
			you.SetShield(0,0);
		}
		return;
	case TPT_STG_HP_RECOVERY:
		return;
	case TPT_STG_MP_RECOVERY:
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
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
			if(num < you.property_vector.size())
			{
				WaitForSingleObject(mutx, INFINITE);
				SetText() = LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_PROPERTY) + " : " + you.property_vector[num].GetName();
				SetText() += "\n\n" + LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_EFFECT) + " : " + you.property_vector[num].GetDetail();
				changedisplay(DT_TEXT);
				ReleaseMutex(mutx);
				waitkeyinput();
				changedisplay(DT_PROPERTY);
				changemove(0);
			}
			else
				break;
		}
		else if(key_ == -1) {
			if(inputedKey.isLeftClick() || inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE||
			key_ == GVK_BUTTON_B || 
			key_ == GVK_BUTTON_B_LONG)
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_NECOMATA_FUR),true,false,false,CL_small_danger);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_OARFIGH_SCALE1),true,false,false,CL_small_danger);
			you.DeleteProperty(TPT_SCALE);
			you.SetProperty(TPT_SCALE,2);
		}
		if(level_ == 18)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_OARFIGH_SCALE2),true,false,false,CL_small_danger);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST),true,false,false,CL_small_danger);
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST_1),true,false,false,CL_small_danger);
				you.SetProperty(TPT_CLAW,1);
				oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_CLAW, 1);
				AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
				break;
			case 1:
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI),true,false,false,CL_small_danger);
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI_1),true,false,false,CL_small_danger);
				you.SetProperty(TPT_HORN,1);
				oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_HORN, 1);
				AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
				break;
			case 2:
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON),true,false,false,CL_small_danger);
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON_1),true,false,false,CL_small_danger);
				you.SetProperty(TPT_SCALE,1);
				oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_SCALE, 1);
				AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
				break;
			case 3:
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON),true,false,false,CL_small_danger);
				printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON_1),true,false,false,CL_small_danger);
				you.SetProperty(TPT_MP_REGEN,1);
				oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_MP_REGEN, 1);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST_2_JAW),true,false,false,CL_small_danger);
					you.SetProperty(TPT_JAW,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_JAW, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST_2_FOOT),true,false,false,CL_small_danger);
					you.SetProperty(TPT_FOOT,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_FOOT, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST_2_EYE),true,false,false,CL_small_danger);
					you.SetProperty(TPT_EYE,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_EYE, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 1:
				switch(you.half_youkai[1])
				{
				case 0:	
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI_2_HP),true,false,false,CL_small_danger);
					you.SetProperty(TPT_HP,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_HP, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI_2_POISON),true,false,false,CL_small_danger);
					you.SetProperty(TPT_POISON_RESIST,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_POISON_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI_2_MR),true,false,false,CL_small_danger);
					you.SetProperty(TPT_MAGIC_RESIST,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_MAGIC_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 2:
				switch(you.half_youkai[1])
				{
				case 0:	
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON_2_FIRE),true,false,false,CL_small_danger);
					you.SetProperty(TPT_FIRE_RESIST,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_FIRE_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON_2_COLD),true,false,false,CL_small_danger);
					you.SetProperty(TPT_COLD_RESIST,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_COLD_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON_2_ELEC),true,false,false,CL_small_danger);
					you.SetProperty(TPT_ELEC_RESIST,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_ELEC_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 3:
				switch(you.half_youkai[1])
				{
				case 0:	
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON_2_FLY),true,false,false,CL_small_danger);
					you.SetProperty(TPT_FLY,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_FLY, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON_2_RCONFUSE),true,false,false,CL_small_danger);
					you.SetProperty(TPT_CONFUSE_RESIST,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_CONFUSE_RESIST, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON_2_STEALTH),true,false,false,CL_small_danger);
					you.SetProperty(TPT_STEALTH,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_STEALTH, 1);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST_3_FUR),true,false,false,CL_small_danger);
					you.SetProperty(TPT_FUR,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_FUR, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST_3_SPEED),true,false,false,CL_small_danger);
					you.SetProperty(TPT_SPEED,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_SPEED, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST_3_REGEN),true,false,false,CL_small_danger);
					you.SetProperty(TPT_REGEN,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_REGEN, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 1:
				switch(you.half_youkai[2])
				{
				case 0:	
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI_3_AC),true,false,false,CL_small_danger);
					you.SetProperty(TPT_SKIN_AC,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_SKIN_AC, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI_3_REGEN),true,false,false,CL_small_danger);
					you.SetProperty(TPT_REGEN,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_REGEN, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI_3_STR),true,false,false,CL_small_danger);
					you.SetProperty(TPT_STR,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_STR, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 2:
				switch(you.half_youkai[2])
				{
				case 0:	
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON_3_CLOUD),true,false,false,CL_small_danger);
					you.SetProperty(TPT_CLOUD,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_CLOUD, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON_3_BREATH),true,false,false,CL_small_danger);
					you.SetProperty(TPT_BREATH,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_BREATH, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON_3_SCALE),true,false,false,CL_small_danger);
					you.DeleteProperty(TPT_SCALE);
					you.SetProperty(TPT_SCALE,2);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GROW) << ": " << getTribeProperty(TPT_SCALE, 2);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					switch(you.half_youkai[1])
					{
					case 0:
						you.DeleteProperty(TPT_FIRE_RESIST);
						you.SetProperty(TPT_FIRE_RESIST,2);
						oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GROW) << ": " << getTribeProperty(TPT_FIRE_RESIST, 2);
						AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
						break;
					case 1:
						you.DeleteProperty(TPT_COLD_RESIST);
						you.SetProperty(TPT_COLD_RESIST,2);
						oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GROW) << ": " << getTribeProperty(TPT_COLD_RESIST, 2);
						AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
						break;
					case 2:		
						you.DeleteProperty(TPT_ELEC_RESIST);		
						you.SetProperty(TPT_ELEC_RESIST,2);
						oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GROW) << ": " << getTribeProperty(TPT_ELEC_RESIST, 2);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON_3_SPELL_POWER),true,false,false,CL_small_danger);
					you.SetProperty(TPT_SPELL_POWER,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_SPELL_POWER, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON_3_FINGER_MAGIC),true,false,false,CL_small_danger);
					you.SetProperty(TPT_FINGER_MAGIC,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_FINGER_MAGIC, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 2:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON_3_BLOOD_MAGIC),true,false,false,CL_small_danger);
					you.SetProperty(TPT_BLOOD_MAGIC,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_BLOOD_MAGIC, 1);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST_4_SLAY),true,false,false,CL_small_danger);
					you.SetProperty(TPT_SLAY,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_SLAY, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_BEAST_4_CONFUSE_ATTACK),true,false,false,CL_small_danger);
					you.SetProperty(TPT_CONFUSE_ATTACK,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_CONFUSE_ATTACK, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 1:
				switch(you.half_youkai[3])
				{
				case 0:	
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI_4_HP),true,false,false,CL_small_danger);
					if(you.half_youkai[1]==0)
					{
						you.DeleteProperty(TPT_HP);
						you.SetProperty(TPT_HP,3);
						oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GROW) << ": " << getTribeProperty(TPT_HP, 3);
						AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					}
					else {
						you.SetProperty(TPT_HP, 2);
						oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_HP, 2);
						AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					}
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_ONI_4_EV),true,false,false,CL_small_danger);
					you.SetProperty(TPT_EV,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_EV, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 2:
				switch(you.half_youkai[3])
				{
				case 0:	
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON_4_GRAZE_CONTROL),true,false,false,CL_small_danger);
					you.SetProperty(TPT_GRAZE_CONTROL,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_GRAZE_CONTROL, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DRAGON_4_FORCE_OF_NATURE),true,false,false,CL_small_danger);
					you.SetProperty(TPT_FORCE_OF_NATURE,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_FORCE_OF_NATURE, 1);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				}	
				break;
			case 3:
				switch(you.half_youkai[3])
				{
				case 0:	
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON_4_MP_REGEN),true,false,false,CL_small_danger);
					you.DeleteProperty(TPT_MP_REGEN);
					you.SetProperty(TPT_MP_REGEN,3);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GROW) << ": " << getTribeProperty(TPT_MP_REGEN, 3);
					AddNote(you.turn, CurrentLevelString(), oss.str(), CL_normal);
					break;
				case 1:
					printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_HALFYOUKAI_DEMON_4_TORMENT),true,false,false,CL_small_danger);
					you.SetProperty(TPT_TORMENT,1);
					oss << LocalzationManager::locString(LOC_SYSTEM_NOTE_HALFYOUKAI_MUTANT_GAIN) << ": " << getTribeProperty(TPT_TORMENT, 1);
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
		if(level_%7 == 0)
		{
			randA(2)?(randA(1)?you.StatUpDown(1,STAT_STR):you.StatUpDown(1,STAT_DEX)):you.StatUpDown(1,STAT_INT);
		}
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_TRIBE_GROW_KOISHI_CONFUSE_ATTACK),true,false,false,CL_small_danger);
			you.SetProperty(TPT_CONFUSE_ATTACK,1);
		}
		break;
	default:
		break;
	}
}