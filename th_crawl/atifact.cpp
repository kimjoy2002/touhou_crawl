//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: atifact.cpp
//
// 내용: 아티펙트 구현
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "atifact.h"
#include "ring.h"
#include "skill_use.h"
#include "save.h"
#include "armour.h"
#include "rand_shuffle.h"
#include "environment.h"
#include "weapon.h"

int GetMaterial(material_kind kind_, armour_value ac_);

atifact_infor::atifact_infor(int kind_, int value_)
	:kind(kind_), value(value_)
{

}
atifact_infor::atifact_infor()
:kind(0), value(1)
{

}
atifact_infor::~atifact_infor()
{

}
void atifact_infor::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, kind);
	SaveData<int>(fp, value);
}
void atifact_infor::LoadDatas(FILE *fp)
{
	LoadData<int>(fp, kind);
	LoadData<int>(fp, value);
}


int GetAtifactValue(artifact_type ring_, int good_bad_)
{	
	int a_ = good_bad_>=0?1:-1;
	switch(ring_)
	{
	case ART_STR:
	case ART_DEX:
	case ART_INT:
	case ART_AC:
	case ART_EV:
	case ART_SLAY:
			return (1+randA(5))*a_;
	case ART_HUNGRY:
	case ART_FULL:
	case ART_TELEPORT:
	case ART_POISON_RESIS:
	case ART_SEE_INVISIBLE:
	case ART_LEVITATION:
	case ART_INVISIBLE:
	case ART_MANA:
	case ART_MAGACIAN:
	case ART_CONFUSE_RESIS:
	case ART_MAGICBOOST:
	case ART_ANTIOVERHEAT:
	case ART_PENTAN:
	case ART_COUNTER:
	case ART_PERMAINVI:
	case ART_UNCONSCIOUS:
	case ART_LUNATIC:
	case ART_HALO:
	case ART_RAD:
	case ART_FIREBALL:
	case ART_GLUTTON:
	case ART_BUG:
	case ART_POISONIMMUNE:
	case ART_SWIFT:
	case ART_MISSLE:
	case ART_SELFDESTRUCT:
	case ART_SUMMONRESIST:
	case ART_DRUNK:
	case ART_HP_REGEN:
	case ART_CURSE:
	case ART_HEAVY:
	case ART_LESS_POWER:
		return 1;
	case ART_FIRE_RESIS:
	case ART_ICE_RESIS:
	case ART_ELEC_RESIS:
		return a_>0?(randA(4)?1:(randA(10)?2:3)):-1;
	case ART_MAGIC_RESIS:
		return randA(2)?1:rand_int(2,3);
	case ART_SKILL_UP:
		{
			int skill_ = 0;
			do
			{
				skill_ = randA(SKT_MAX - 1);
			} while (skill_ == SKT_FIGHT || skill_ == SKT_SPELLCASTING || skill_ == SKT_DODGE ||
				skill_ == SKT_ARMOUR || skill_ == SKT_SHIELD || skill_ == SKT_MAGIC_DEVICE);
			skill_ += randA_1(4) * 100;
			return skill_;
		}
	default:
		break;
	}
	return 1;
}

string GetAtifactString(std::string lang, artifact_type ring_, int value_)
{	
    std::ostringstream oss;
	switch(ring_)
	{
	case ART_STR:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_STR, PlaceHolderHelper(((value_ < 0) ? "" : "+") + to_string(value_)));
		break;
	case ART_DEX:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_DEX, PlaceHolderHelper(((value_ < 0) ? "" : "+") + to_string(value_)));
		break;
	case ART_INT:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_INT, PlaceHolderHelper(((value_ < 0) ? "" : "+") + to_string(value_)));
		break;
	case ART_HUNGRY:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_HUNGRY);
		break;
	case ART_FULL:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_FULL);
		break;
	case ART_TELEPORT:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_TELEPORT);
		break;
	case ART_POISON_RESIS:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_POISON_RESIST, PlaceHolderHelper((value_>0?"+":"-")));
		break;
	case ART_FIRE_RESIS:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_FIRE_RESIST, PlaceHolderHelper((value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			))))))));
		break;
	case ART_ICE_RESIS:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_COLD_RESIST, PlaceHolderHelper((value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			))))))));
		break;
	case ART_SEE_INVISIBLE:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_SEE_INVISIBLE);
		break;
	case ART_LEVITATION:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_FLIGHT);
		break;
	case ART_INVISIBLE:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_INVISIBLE);
		break;
	case ART_MANA:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_MANA);
		break;
	case ART_MAGACIAN:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_MAGICIAN);
		break;
	case ART_AC:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_AC, PlaceHolderHelper((value_<0?"":"+") + to_string(value_)));
		break;
	case ART_EV:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_EV, PlaceHolderHelper((value_<0?"":"+") + to_string(value_)));
		break;
	case ART_CONFUSE_RESIS:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_CONFUSE_RESIST);
		break;
	case ART_ELEC_RESIS:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_ELEC_RESIST, PlaceHolderHelper((value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			))))))));
		break;
	case ART_MAGIC_RESIS:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_MAGIC_RESIST);
		break;
	case ART_MAGICBOOST:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_HAKKERO_MAGICBOOST);
		break;
	case ART_ANTIOVERHEAT:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_HAKKERO_ANTIOVERHEAT);
		break;
	case ART_PENTAN:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_GUNGNIR_PENTAN);
		break;
	case ART_COUNTER:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_HAKUROUKEN_COUNTER);
		break;
	case ART_PERMAINVI:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_KOISHIHAT_PERMAINVI);
		break;
	case ART_UNCONSCIOUS:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_KOISHIHAT_UNCONSCIOUS);
		break;
	case ART_LUNATIC:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_LUNATICTORCH_LUNATIC);
		break;
	case ART_HALO:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_LUNATICTORCH_HALO);
		break;
	case ART_RAD:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_NUCLEARBOOT_RAD);
		break;
	case ART_FIREBALL:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_CONTROLROD_FIREBALL);
		break;
	case ART_GLUTTON:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_PICKANDSHOVELS_GLUTTON);
		break;
	case ART_BUG:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_FIREFLYCLOAK_BUG);
		break;
	case ART_POISONIMMUNE:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_LILYRING_POISONIMMUNE);
		break;
	case ART_SWIFT:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_GALECLOGS_SWIFT);
		break;
	case ART_MISSLE:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_KAPPAFULLARMOR_MISSILE);
		break;
	case ART_SELFDESTRUCT:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_KAPPAFULLARMOR_SELFDESTRUCT);
		break;
	case ART_SUMMONRESIST:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_MAIDUNIFORM_SUMMONRES);
		break;
	case ART_DRUNK:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_IBUKISAKE_DRUNK);
		break;
	case ART_SLAY:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_SLAY, PlaceHolderHelper(((value_ < 0) ? "" : "+") + to_string(value_)));
		break;
	case ART_HP_REGEN:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_HP_REGEN, PlaceHolderHelper((value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			))))))));
		break;
	case ART_LESS_POWER:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_POWER,
			PlaceHolderHelper(value_ < 0 ? string(-value_, '+') : string(value_, '-')));
		break;
	case ART_CURSE:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_CURSE);
		break;
	case ART_HEAVY:
		oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_HEAVY);
		break;
	case ART_WEATHER_TRIGGER: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_WEATHER_TRIGGER); break;
	case ART_WHIRLWIND: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_WHIRLWIND); break;
	case ART_INFINITE_REACH: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_INFINITE_REACH); break;
	case ART_PULL: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_PULL); break;
	case ART_UNKNOWN_POWER: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_UNKNOWN_POWER); break;
	case ART_SWIM: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_SWIM); break;
	case ART_INSTANT_DEATH: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_INSTANT_DEATH); break;
	case ART_KNOCKAWAY: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_KNOCKAWAY); break;
	case ART_JUMP: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_JUMP); break;
	case ART_RETURN: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_RETURN); break;
	case ART_KICK: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_KICK); break;
	case ART_MAX_HP:
		oss << LocalzationManager::formatString(lang, LOC_SYSTEM_ITEM_ARTIFACT_MAX_HP,
			PlaceHolderHelper((value_ < 0 ? "" : "+") + to_string(value_)));
		break;
	case ART_DIVE: oss << LocalzationManager::locString(lang, LOC_SYSTEM_ITEM_ARTIFACT_DIVE); break;
	case ART_SKILL_UP:
		oss << skill_string((skill_type)(value_ %100)) << "+" << value_/100;
		break;
	default:
		break;
	}
	return oss.str();
}


std::string GetAtifactInfor(artifact_type ring_, int value_)
{
    std::ostringstream oss;
	switch(ring_)
	{
	case ART_STR:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_STR,
			PlaceHolderHelper((value_<0?"":"+") + to_string(value_)));
		break;
	case ART_DEX:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_DEX,
			PlaceHolderHelper((value_<0?"":"+") + to_string(value_)));
		break;
	case ART_INT:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_INT,
			PlaceHolderHelper((value_<0?"":"+") + to_string(value_)));
		break;
	case ART_HUNGRY:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_HUNGRY);
		break;
	case ART_FULL:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_FULL);
		break;
	case ART_TELEPORT:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_TELEPORT);
		break;
	case ART_POISON_RESIS:
		oss << LocalzationManager::locString(value_>0?LOC_SYSTEM_ITEM_ARTIFACT_INFO_POISON_RESIST_GOOD:LOC_SYSTEM_ITEM_ARTIFACT_INFO_POISON_RESIST_BAD);
		break;
	case ART_FIRE_RESIS:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_FIRE_RESIST,
			PlaceHolderHelper((value_==3?"+++":
				(value_==2?"++":
				(value_==1?"+":
				(value_==-1?"-":
				(value_==-2?"--":
				(value_==-3?"---":"?"
				))))))));
		break;
	case ART_ICE_RESIS:	
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_COLD_RESIST,
			PlaceHolderHelper((value_==3?"+++":
				(value_==2?"++":
				(value_==1?"+":
				(value_==-1?"-":
				(value_==-2?"--":
				(value_==-3?"---":"?"
				))))))));
		break;
	case ART_SEE_INVISIBLE:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_SEE_INVISIBLE);
		break;
	case ART_LEVITATION:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_FLIGHT);
		break;
	case ART_INVISIBLE:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_INVISIBLE);
		break;
	case ART_MANA:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_MANA);
		break;
	case ART_MAGACIAN:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_MAGICIAN);
		break;
	case ART_AC:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_AC,
			PlaceHolderHelper((value_<0?"":"+") + to_string(value_)));
		break;
	case ART_EV:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_EV,
			PlaceHolderHelper((value_<0?"":"+") + to_string(value_)));
		break;
	case ART_CONFUSE_RESIS:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_CONFUSE_RESIST);
		break;
	case ART_ELEC_RESIS:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_ELEC_RESIST,
			PlaceHolderHelper((value_==3?"+++":
				(value_==2?"++":
				(value_==1?"+":
				(value_==-1?"-":
				(value_==-2?"--":
				(value_==-3?"---":"?"
				))))))));
		break;
	case ART_MAGIC_RESIS:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_MAGIC_RESIST,
			PlaceHolderHelper(to_string(20+value_*20)));
		break;
	case ART_MAGICBOOST:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HAKKERO_MAGICBOOST_INFO);
		break;
	case ART_ANTIOVERHEAT:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HAKKERO_ANTIOVERHEAT_INFO);
		break;
	case ART_PENTAN:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_GUNGNIR_PENTAN_INFO);
		break;
	case ART_COUNTER:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HAKUROUKEN_COUNTER_INFO);
		break;
	case ART_PERMAINVI:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_KOISHIHAT_PERMAINVI_INFO);
		break;
	case ART_UNCONSCIOUS:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_KOISHIHAT_UNCONSCIOUS_INFO);
		break;
	case ART_LUNATIC:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_LUNATICTORCH_LUNATIC_INFO);
		break;
	case ART_HALO:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_LUNATICTORCH_HALO_INFO);
		break;
	case ART_RAD:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_NUCLEARBOOT_RAD_INFO);
		break;
	case ART_FIREBALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_CONTROLROD_FIREBALL_INFO);
		break;
	case ART_GLUTTON:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_PICKANDSHOVELS_GLUTTON_INFO);
		break;
	case ART_BUG:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_FIREFLYCLOAK_BUG_INFO);
		break;
	case ART_POISONIMMUNE:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_LILYRING_POISONIMMUNE_INFO);
		break;
	case ART_SWIFT:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_GALECLOGS_SWIFT_INFO);
		break;
	case ART_MISSLE:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_KAPPAFULLARMOR_MISSILE_INFO);
		break;
	case ART_SELFDESTRUCT:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_KAPPAFULLARMOR_SELFDESTRUCT_INFO);
		break;
	case ART_SUMMONRESIST:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_MAIDUNIFORM_SUMMONRES_INFO);
		break;
	case ART_DRUNK:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_IBUKISAKE_DRUNK_INFO);
		break;
	case ART_SLAY:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_SLAY, PlaceHolderHelper(((value_ < 0) ? "" : "+") + to_string(value_)));
		break;
	case ART_HP_REGEN:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_HP_REGEN, PlaceHolderHelper((value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			))))))));
		break;
	case ART_LESS_POWER:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_POWER,
			PlaceHolderHelper((value_ > 0 ? "-" : "+") + to_string(abs(value_))));
		break;
	case ART_CURSE:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_CURSE);
		break;
	case ART_HEAVY:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_HEAVY, PlaceHolderHelper("0.1"));
		break;
	case ART_WEATHER_TRIGGER: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_WEATHER_TRIGGER); break;
	case ART_WHIRLWIND: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_WHIRLWIND); break;
	case ART_INFINITE_REACH: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_INFINITE_REACH); break;
	case ART_PULL: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_PULL); break;
	case ART_UNKNOWN_POWER: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_UNKNOWN_POWER); break;
	case ART_SWIM: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_SWIM); break;
	case ART_INSTANT_DEATH: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_INSTANT_DEATH); break;
	case ART_KNOCKAWAY: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_KNOCKAWAY); break;
	case ART_JUMP: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_JUMP); break;
	case ART_RETURN: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_RETURN); break;
	case ART_KICK: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_KICK); break;
	case ART_MAX_HP:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_MAX_HP,
			PlaceHolderHelper((value_ < 0 ? "" : "+") + to_string(value_)));
		break;
	case ART_DIVE: oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_DIVE); break;
	case ART_SKILL_UP:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_SKILL_UP,
			PlaceHolderHelper(skill_string((skill_type)(value_ % 100)) + to_string(value_ / 100)));
		break;
	default:
		break;
	}
	return oss.str();
}


artifact_type ring_to_artifact(ring_type kind)
{
	switch(kind)
	{
	case RGT_STR:
		return ART_STR;
	case RGT_DEX:
		return ART_DEX;
	case RGT_INT:
		return ART_INT;
	case RGT_HUNGRY:
		return ART_HUNGRY;
	case RGT_FULL:
		return ART_FULL;
	case RGT_TELEPORT:
		return ART_TELEPORT;
	case RGT_POISON_RESIS:
		return ART_POISON_RESIS;
	case RGT_FIRE_RESIS:
		return ART_FIRE_RESIS;
	case RGT_ICE_RESIS:
		return ART_ICE_RESIS;
	case RGT_SEE_INVISIBLE:
		return ART_SEE_INVISIBLE;
	case RGT_LEVITATION:
		return ART_LEVITATION;
	case RGT_INVISIBLE:
		return ART_INVISIBLE;
	case RGT_MANA:
		return ART_MANA;
	case RGT_MAGACIAN:
		return ART_MAGACIAN;
	case RGT_AC:
		return ART_AC;
	case RGT_EV:
		return ART_EV;
	case RGT_CONFUSE_RESIS:
		return ART_CONFUSE_RESIS;
	case RGT_ELEC_RESIS:
		return ART_ELEC_RESIS;
	case RGT_MAGIC_RESIS:
		return ART_MAGIC_RESIS;
	default:
		break;
	}
	return ART_POISON_RESIS;
}





int isGenerateRandart(artifact_type type_, item_type type) {
	switch(type_) {
		case ART_STR:
		case ART_DEX:
		case ART_INT:
		case ART_HUNGRY:
		case ART_FULL:
		case ART_POISON_RESIS:
		case ART_FIRE_RESIS:
		case ART_ICE_RESIS:
		case ART_SEE_INVISIBLE:
		case ART_LEVITATION:
		case ART_MANA:
		case ART_CONFUSE_RESIS:
		case ART_ELEC_RESIS:
		case ART_MAGIC_RESIS:
			return 10;
		case ART_AC:
		case ART_EV:
		case ART_MAGACIAN:
		case ART_INVISIBLE:
			return 7;
		case ART_SKILL_UP:
		case ART_SLAY:
			return 3;
		case ART_LESS_POWER:
		case ART_CURSE:
		case ART_HEAVY:
		case ART_TELEPORT:
			return 2;
		case ART_HP_REGEN:
		{
			if(type == ITM_RING) {
				return 0;
			}
			return 3;
		}
		case ART_MAGICBOOST:
		case ART_ANTIOVERHEAT:
		case ART_PENTAN:
		case ART_COUNTER:
		case ART_PERMAINVI:
		case ART_UNCONSCIOUS:
		case ART_LUNATIC:
		case ART_HALO:
		case ART_RAD:
		case ART_FIREBALL:
		case ART_GLUTTON:
		case ART_BUG:
		case ART_POISONIMMUNE:
		case ART_SWIFT:
		case ART_MISSLE:
		case ART_SELFDESTRUCT:
		case ART_SUMMONRESIST:
		case ART_DRUNK:
		default:
			return 0;
	}
}

bool effectartifact(artifact_type kind, int value)
{
	switch(kind)
	{
	case ART_STR:
		you.StatUpDown(value, STAT_STR);
		return true;
	case ART_DEX:
		you.StatUpDown(value, STAT_DEX);
		return true;
	case ART_INT:
		you.StatUpDown(value, STAT_INT);
		return true;
	case ART_HUNGRY:
		you.ResistUpDown(value*-1,RST_POWER);
		return false;
	case ART_FULL:
		you.ResistUpDown(value,RST_POWER);
		return false;
	case ART_TELEPORT:
		you.teleport_curse += value;
		return true;
	case ART_POISON_RESIS:
		you.ResistUpDown(value,RST_POISON);
		return false;
	case ART_FIRE_RESIS:
		you.ResistUpDown(value,RST_FIRE);
		return false;
	case ART_ICE_RESIS:
		you.ResistUpDown(value,RST_ICE);
		return false;
	case ART_SEE_INVISIBLE:
		you.ResistUpDown(value,RST_INVISIBLE);
		return false;
	case ART_LEVITATION:
		{
			int temp = you.Ability(SKL_LEVITATION_OFF,false,true);
			temp += you.Ability(SKL_LEVITATION,false,true);

			temp+=value;
			you.Ability(you.s_levitation?SKL_LEVITATION_OFF:SKL_LEVITATION,false,temp<=0?true:false,temp);
			if(temp <= 0 && you.s_levitation)
			{
				you.s_levitation=0; 
			}
			return true;
		}
	case ART_INVISIBLE:
		{
			int temp = you.Ability(SKL_INVISIBLE_OFF,false,true);
			temp += you.Ability(SKL_INVISIBLE,false,true);

			temp+=value;
			you.Ability(you.s_invisible?SKL_INVISIBLE_OFF:SKL_INVISIBLE,false,temp<=0?true:false,temp);
			if(temp <= 0 && you.s_invisible)
			{
				you.s_invisible=0; 
			}
			if(you.GetArtifactProperty(ART_PERMAINVI) > 0)
			{
				you.s_invisible = -1;
			}
			return true;
		}
	case ART_MANA:
		you.max_mp += 9*value;
		if(you.mp > you.max_mp)
			you.mp = you.max_mp;
		return true;
	case ART_MAGACIAN:
		you.magician_bonus += value;
		return false;
	case ART_AC:
		you.AcUpDown(0,value);
		return true;
	case ART_EV:
		you.EvUpDown(0,value);
		return true;
	case ART_CONFUSE_RESIS:
		you.ResistUpDown(value,RST_CONFUSE);
		return false;
	case ART_ELEC_RESIS:
		you.ResistUpDown(value,RST_ELEC);
		return false;
	case ART_MAGIC_RESIS:
		you.MRUpDown((value>0?1:-1)*(20+abs(value)*20));
		return false;
	case ART_MAGICBOOST:
		return true;
	case ART_ANTIOVERHEAT:
		return true;
	case ART_PENTAN:
		return true;
	case ART_COUNTER:
		return true;
	case ART_PERMAINVI:
		you.s_invisible = value>0?-1:0;
		return true;
	case ART_UNCONSCIOUS:
		return true;
	case ART_LUNATIC:
		break;
	case ART_HALO:
		env[current_level].MakeHalo(you.position, 4, value> 0);
		return true;
	case ART_RAD:
		break;
	case ART_FIREBALL:
		{
			you.Ability(SKL_FIREBALL,false,value<0);
			return true;
		}
	case ART_GLUTTON:
		return true;
	case ART_BUG:
		return true;
	case ART_POISONIMMUNE:
		you.ResistUpDown(value*1000,RST_POISON);
		return true;
	case ART_SWIFT:
		you.speed -= value*2;
		return true;
	case ART_MISSLE:
		{
			you.Ability(SKL_MISSLE,false,value<0);
			return true;
		}
	case ART_SELFDESTRUCT:
		break;
	case ART_SUMMONRESIST:
		return true;
	case ART_DRUNK:
		break;
	case ART_SLAY:
		you.s_slaying += value;
		return false;
	case ART_HP_REGEN:
		you.s_regen += value;
		return false;
	case ART_LESS_POWER:
		you.max_power -= value * 100;
		if(you.GetMaxPower()+30 < you.power) {
			you.power = you.GetMaxPower()+30;
		}
		return false;
	case ART_CURSE:
		break;
	case ART_HEAVY:
		break;
	case ART_JUMP:
		you.Ability(SKL_JUMPING_ATTACK,false,value < 0);
		return true;
	case ART_DIVE:
		if(value < 0 && you.IsDiving())
			you.EndDive();
		you.Ability(SKL_DIVE,false,value < 0);
		return true;
	case ART_MAX_HP:
	{
		int prev_hp = you.hp;
		int prev_max_hp = you.max_hp;
		you.UpDownBuff(BUFFSTAT_HP, value);
		if(prev_max_hp > 0)
			you.hp = prev_hp > 0 ? max(1, min(you.max_hp, (prev_hp * you.max_hp + prev_max_hp / 2) / prev_max_hp)) : 0;
		return true;
	}
	case ART_WEATHER_TRIGGER:
	case ART_WHIRLWIND:
	case ART_INFINITE_REACH:
	case ART_PULL:
	case ART_UNKNOWN_POWER:
	case ART_SWIM:
	case ART_INSTANT_DEATH:
	case ART_KNOCKAWAY:
	case ART_RETURN:
	case ART_KICK:
		return true;
	case ART_SKILL_UP:
	{
		int value_ = abs(value);
		you.BonusSkillUpDown(value_ % 100, (value>0?1:-1) *value_ / 100);

	}
		return true;
	default:
		break;
	}
	return false;
}

bool CantBothArtifact(artifact_type left, artifact_type right) {
	if((left == ART_HUNGRY && right == ART_FULL)|| (left == ART_FULL  && right == ART_HUNGRY))
		return true;
	return false;
}




int ArmourExceptopn(armour_kind type)
{	
	switch(type)
	{
	case AMK_NORMAL:		
		break;		
	case AMK_MIKO:
		return ART_CONFUSE_RESIS;
	case AMK_WING:
		return ART_ELEC_RESIS;
	case AMK_KAPPA:
		return ART_ICE_RESIS;
	case AMK_FIRE:
		return ART_FIRE_RESIS;
	case AMK_MAID:
		return ART_MAGIC_RESIS;
	case AMK_POISON:
		return ART_POISON_RESIS;
	case AMK_AUTUMN:
		break;
	default:
		break;
	}
	return -1;
}



void MakeArtifact(item* item_, int good_bad_, bool cant_fixed)
{
	if(good_bad_ > 0 && !cant_fixed) {
		random_extraction<fixed_artifact_type> able_fixed_arti;
		for(int i = 1; i < FIXED_ARTIFACT_MAX; i++) {
			if(!iden_list.fixed_artifact[i] && IsTypeOfFixedArtifact((fixed_artifact_type)i, item_->type)) {
				able_fixed_arti.push((fixed_artifact_type)i);
			}
		}
		if(able_fixed_arti.GetSize()>0) {
			//고정아티 존재함
			//기본 고정아티 확률 1/10
			if(randA(13-3*good_bad_) == 0) {
				item_->item_tag.clear();
				MakeFixedArtifact(item_, able_fixed_arti.pop(), false);
				item_->item_tag.push_back(LOC_SYSTEM_TAG_FIXDART);
				return;
			}
		}
	}

	int num_ = 1+randA(good_bad_ +randA(3));
	random_extraction<artifact_type> temp;
	vector<artifact_type> check;
	for(int i=0; i<ART_MAX_ATIFACT; i++)
	{
		if(item_->type >= ITM_ARMOR_BODY_FIRST && item_->type < ITM_ARMOR_BODY_LAST)
		{
			if(ArmourExceptopn((armour_kind)item_->value5) == i)
				continue;
		}
		if (isSprint() && 
			(i == ART_TELEPORT || i == ART_HUNGRY || i == ART_FULL || i == ART_LEVITATION)) {
			continue;
		}
		if(isGenerateRandart((artifact_type)i, item_->type ) <= 0) {
			continue;
		}
		bool cantgene = false;
		for(auto already_ : check) {
			if(CantBothArtifact(already_, (artifact_type)i)) {
				cantgene = true;
			}
		}
		if(cantgene) {
			continue;
		}
		check.push_back((artifact_type)i);
		temp.push((artifact_type)i, isGenerateRandart((artifact_type)i, item_->type ));
	}
	
	for(int i = 0; i < num_ ; i++)
	{
		int poped_ = temp.pop();
		if(ring_to_artifact((ring_type)item_->value1) != poped_ || item_->type != ITM_RING)
		{
			int gb_ = randA(3)?good_bad_:good_bad_*-1;
			item_->atifact_vector.push_back(atifact_infor(poped_,GetAtifactValue((artifact_type)poped_,gb_)));
		}
		else
			num_++;
	}

	if(item_->type>=ITM_WEAPON_FIRST && item_->type<ITM_WEAPON_LAST)
	{
		item_->value4 = randA(9)+randA(3)+randA(2 + good_bad_)-4;
		//item_->value3 = randA(9)+randA(3)+randA(3)-4;
	}		
	if(item_->type>=ITM_ARMOR_FIRST && item_->type< ITM_ARMOR_LAST)
	{
		item_->value4 = randA(item_->value1)+randA(2)+randA(1+good_bad_)-2;
	}
	if(item_->type >= ITM_ARMOR_BODY_FIRST && item_->type < ITM_ARMOR_BODY_LAST)
	{
		int armour_image_ = GetArmourImageIndex((armour_kind)item_->value5);
		material_kind material_ = (material_kind)(item_->type-ITM_ARMOR_BODY_ARMOUR_0);
		if(armour_image_ >= 0)
		{
			item_->image = &img_item_artifact_armor_special[armour_image_][material_];
			item_->equip_image = &img_play_item_artifact_body[armour_image_];
		}
		else if((armour_kind)item_->value5 == AMK_NORMAL)
		{
			item_->image = material_ == MTK_PLATE ? &img_item_artifact_armor_armour_3 :
				material_ == MTK_CHAIN ? &img_item_artifact_armor_armour_2 :
				material_ == MTK_LEATHER ? &img_item_artifact_armor_armour_1 : &img_item_artifact_armor_armour_0;
		}
	}
	else if(item_->type == ITM_ARMOR_CLOAK)
	{
		item_->image = &img_item_artifact_armor_cloak;
		item_->equip_image = &img_play_item_artifact_cloak;
	}
	else if(item_->type == ITM_ARMOR_GLOVE)
	{
		item_->image = &img_item_artifact_armor_glove;
		item_->equip_image = &img_play_item_artifact_glove;
	}
	else if(item_->type == ITM_ARMOR_BOOT)
	{
		item_->image = &img_item_artifact_armor_boot;
		item_->equip_image = &img_play_item_artifact_boot;
	}
	else if(item_->type == ITM_ARMOR_HEAD)
	{
		for(int i=0;i<6;i++)
		{
			if(item_->image == &img_item_armor_helmet[i])
			{
				item_->image = &img_item_artifact_armor_helmet[i];
				item_->equip_image = &img_play_item_artifact_hat[i];
				break;
			}
		}
	}

	if (item_->type >= ITM_WEAPON_FIRST && item_->type<ITM_WEAPON_LAST)
	{
		if (item_->image == &img_item_weapon_shortsword)
			item_->image = &img_item_artifact_shortsword;
		else if (item_->image == &img_item_weapon_bamboo_spear)
			item_->image = &img_item_artifact_bamboo_spear;
		else if (item_->image == &img_item_weapon_hammer)
			item_->image = &img_item_artifact_hammer;
		else if (item_->image == &img_item_weapon_onbasira)
			item_->image = &img_item_artifact_onbasira;
		else if (item_->image == &img_item_weapon_gohey)
			item_->image = &img_item_artifact_gohey;
		else if (item_->image == &img_item_weapon_dagger)
			item_->image = &img_item_artifact_dagger;
		else if (item_->image == &img_item_weapon_katana)
			item_->image = &img_item_artifact_katana;
		else if (item_->image == &img_item_weapon_scimitar)
			item_->image = &img_item_artifact_scimitar;
		else if (item_->image == &img_item_weapon_greatsword)
			item_->image = &img_item_artifact_greatsword;
		else if (item_->image == &img_item_weapon_broomstick)
			item_->image = &img_item_artifact_broomstick;
		else if (item_->image == &img_item_weapon_handaxe)
			item_->image = &img_item_artifact_handaxe;
		else if (item_->image == &img_item_weapon_battleaxe)
			item_->image = &img_item_artifact_battleaxe;
		else if (item_->image == &img_item_weapon_anchor)
			item_->image = &img_item_artifact_anchor;
		else if (item_->image == &img_item_weapon_spear)
			item_->image = &img_item_artifact_spear;
		else if (item_->image == &img_item_weapon_scythe)
			item_->image = &img_item_artifact_scythe;
		else if (item_->image == &img_item_weapon_trident)
			item_->image = &img_item_artifact_trident;
		else if (item_->image == &img_item_weapon_chakram)
			item_->image = &img_item_artifact_chakram;
		else if (item_->image == &img_item_weapon_umbrella)
			item_->image = &img_item_artifact_umbrella;
		else if (item_->image == &img_item_weapon_knife)
			item_->image = &img_item_artifact_knife;
		else if (item_->image == &img_item_weapon_dauzing_rod)
			item_->image = &img_item_artifact_dauzing_rod;
		else if (item_->image == &img_item_weapon_javelin)
			item_->image = &img_item_artifact_javelin;
	}
	if (item_->type == ITM_RING)
	{
		item_->image = &img_item_artifact_ring;
	}
	if (item_->type == ITM_AMULET)
	{
		item_->image = &img_item_artifact_amulet;
	}
	item_->item_tag.push_back(LOC_SYSTEM_TAG_RANDART);
	item_->second_name= name_infor(LOC_SYSTEM_ITEM_ARTIFACT);
	item_->artifact_guid = randA(~(1 << 31));

}


std::string GetFixedArtifact(fixed_artifact_type fixed_artifact, int enchant) {
	switch(fixed_artifact) {
	case FIXED_ARTIFACT_HAKKERO:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HAKKERO_DESCRIBE);
	case FIXED_ARTIFACT_GUNGNIR:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_GUNGNIR_DESCRIBE);
	case FIXED_ARTIFACT_ROUKANKEN:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_ROUKANKEN_DESCRIBE);
	case FIXED_ARTIFACT_HAKUROUKEN:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HAKUROUKEN_DESCRIBE);
	case FIXED_ARTIFACT_KOISHIHAT:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_KOISHIHAT_DESCRIBE);
	case FIXED_ARTIFACT_MIKOCLOAK:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_MIKOCLOAK_DESCRIBE);
	case FIXED_ARTIFACT_LUNATICTORCH:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_LUNATICTORCH_DESCRIBE);
	case FIXED_ARTIFACT_MOONGEM:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_MOONGEM_DESCRIBE);
	case FIXED_ARTIFACT_NUCLEARBOOT:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_NUCLEARBOOT_DESCRIBE);
	case FIXED_ARTIFACT_CONTROLROD:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_CONTROLROD_DESCRIBE);
	case FIXED_ARTIFACT_PICKANDSHOVELS:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_PICKANDSHOVELS_DESCRIBE);
	case FIXED_ARTIFACT_SILVERKNIFE:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_SILVERKNIFE_DESCRIBE);
	case FIXED_ARTIFACT_FIREFLYCLOAK:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_FIREFLYCLOAK_DESCRIBE);
	case FIXED_ARTIFACT_ICEFAIRYRING:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_ICEFAIRYRING_DESCRIBE);
	case FIXED_ARTIFACT_LAEVATEIN:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_LAEVATEIN_DESCRIBE);
	case FIXED_ARTIFACT_LILYRING:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_LILYRING_DESCRIBE);
	case FIXED_ARTIFACT_GALECLOGS:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_GALECLOGS_DESCRIBE);
	case FIXED_ARTIFACT_HELLTSHIRT:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HELLTSHIRT_DESCRIBE);
	case FIXED_ARTIFACT_KAPPAFULLARMOR:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_KAPPAFULLARMOR_DESCRIBE);
	case FIXED_ARTIFACT_MAIDUNIFORM:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_MAIDUNIFORM_DESCRIBE);
	case FIXED_ARTIFACT_IBUKISAKE:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_IBUKISAKE_DESCRIBE);
	case FIXED_ARTIFACT_SHINING_NEEDLE_SWORD: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_SHINING_NEEDLE_SWORD_DESCRIBE);
	case FIXED_ARTIFACT_SWORD_OF_SCARLET_PERCEPTION: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_SWORD_OF_SCARLET_PERCEPTION_DESCRIBE);
	case FIXED_ARTIFACT_GOLIATH_SWORD: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_GOLIATH_SWORD_DESCRIBE);
	case FIXED_ARTIFACT_REAPER_SCYTHE: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_REAPER_SCYTHE_DESCRIBE);
	case FIXED_ARTIFACT_UNIDENTIFIED_TRIDENT:
		return LocalzationManager::locString(enchant >= 9 ? LOC_SYSTEM_ITEM_ARTIFACT_UNIDENTIFIED_TRIDENT_DESCRIBE3 :
			(enchant >= 5 ? LOC_SYSTEM_ITEM_ARTIFACT_UNIDENTIFIED_TRIDENT_DESCRIBE2 : LOC_SYSTEM_ITEM_ARTIFACT_UNIDENTIFIED_TRIDENT_DESCRIBE1));
	case FIXED_ARTIFACT_SUNKEN_ANCHOR: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_SUNKEN_ANCHOR_DESCRIBE);
	case FIXED_ARTIFACT_YAMANBA_CLEAVER: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_YAMANBA_CLEAVER_DESCRIBE);
	case FIXED_ARTIFACT_BUTTERFLY_FAN: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_BUTTERFLY_FAN_DESCRIBE);
	case FIXED_ARTIFACT_RED_MALLET: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_RED_MALLET_DESCRIBE);
	case FIXED_ARTIFACT_IMMOVABLE_LIBRARY: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_IMMOVABLE_LIBRARY_DESCRIBE);
	case FIXED_ARTIFACT_FULLMOON_DRESS: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_FULLMOON_DRESS_DESCRIBE);
	case FIXED_ARTIFACT_HANIWA_ARMOUR: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HANIWA_ARMOUR_DESCRIBE);
	case FIXED_ARTIFACT_OCCULT_CLOAK: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_OCCULT_CLOAK_DESCRIBE);
	case FIXED_ARTIFACT_PEACH_HAT: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_PEACH_HAT_DESCRIBE);
	case FIXED_ARTIFACT_BOUNDARY_GLOVES: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_BOUNDARY_GLOVES_DESCRIBE);
	case FIXED_ARTIFACT_COWGIRL_BOOTS: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_COWGIRL_BOOTS_DESCRIBE);
	case FIXED_ARTIFACT_STOPWATCH: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_STOPWATCH_DESCRIBE);
	case FIXED_ARTIFACT_SNAKE_RING: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_SNAKE_RING_DESCRIBE);
	case FIXED_ARTIFACT_FROG_RING: return LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_FROG_RING_DESCRIBE);
	default:
		break;
	}
	return "";
}


bool IsTypeOfFixedArtifact(fixed_artifact_type fixed_artifact, item_type itemType) {
	switch(fixed_artifact) {
	case FIXED_ARTIFACT_HAKKERO:
		return itemType==ITM_WEAPON_MACE;
	case FIXED_ARTIFACT_GUNGNIR:
		return itemType==ITM_WEAPON_SPEAR;
	case FIXED_ARTIFACT_ROUKANKEN:
		return itemType==ITM_WEAPON_LONGBLADE;
	case FIXED_ARTIFACT_HAKUROUKEN:
		return itemType==ITM_ARMOR_SHIELD;
	case FIXED_ARTIFACT_KOISHIHAT:
		return itemType==ITM_ARMOR_HEAD;
	case FIXED_ARTIFACT_MIKOCLOAK:
		return itemType==ITM_ARMOR_CLOAK;
	case FIXED_ARTIFACT_LUNATICTORCH:
		return itemType==ITM_WEAPON_MACE;
	case FIXED_ARTIFACT_MOONGEM:
		return itemType==ITM_AMULET;
	case FIXED_ARTIFACT_NUCLEARBOOT:
		return itemType==ITM_ARMOR_BOOT;
	case FIXED_ARTIFACT_CONTROLROD:
		return itemType==ITM_WEAPON_MACE;
	case FIXED_ARTIFACT_PICKANDSHOVELS:
		return itemType==ITM_WEAPON_AXE;
	case FIXED_ARTIFACT_SILVERKNIFE:
		return itemType==ITM_WEAPON_SHORTBLADE;
	case FIXED_ARTIFACT_FIREFLYCLOAK:
		return itemType==ITM_ARMOR_CLOAK;
	case FIXED_ARTIFACT_ICEFAIRYRING:
		return itemType==ITM_RING;
	case FIXED_ARTIFACT_LAEVATEIN:
		return itemType==ITM_WEAPON_LONGBLADE;
	case FIXED_ARTIFACT_LILYRING:
		return itemType==ITM_RING;
	case FIXED_ARTIFACT_GALECLOGS:
		return itemType==ITM_ARMOR_BOOT;
	case FIXED_ARTIFACT_HELLTSHIRT:
		return itemType==ITM_ARMOR_BODY_ARMOUR_0;
	case FIXED_ARTIFACT_KAPPAFULLARMOR:
		return itemType==ITM_ARMOR_BODY_ARMOUR_3;
	case FIXED_ARTIFACT_MAIDUNIFORM:
		return itemType==ITM_ARMOR_BODY_ARMOUR_2;
	case FIXED_ARTIFACT_IBUKISAKE:
		return itemType==ITM_ARMOR_SHIELD;
	case FIXED_ARTIFACT_SHINING_NEEDLE_SWORD: return itemType == ITM_WEAPON_SHORTBLADE;
	case FIXED_ARTIFACT_SWORD_OF_SCARLET_PERCEPTION:
	case FIXED_ARTIFACT_GOLIATH_SWORD: return itemType == ITM_WEAPON_LONGBLADE;
	case FIXED_ARTIFACT_REAPER_SCYTHE:
	case FIXED_ARTIFACT_UNIDENTIFIED_TRIDENT: return itemType == ITM_WEAPON_SPEAR;
	case FIXED_ARTIFACT_SUNKEN_ANCHOR:
	case FIXED_ARTIFACT_YAMANBA_CLEAVER: return itemType == ITM_WEAPON_AXE;
	case FIXED_ARTIFACT_BUTTERFLY_FAN:
	case FIXED_ARTIFACT_RED_MALLET: return itemType == ITM_WEAPON_MACE;
	case FIXED_ARTIFACT_IMMOVABLE_LIBRARY: return itemType == ITM_ARMOR_BODY_ARMOUR_0;
	case FIXED_ARTIFACT_FULLMOON_DRESS: return itemType == ITM_ARMOR_BODY_ARMOUR_2;
	case FIXED_ARTIFACT_HANIWA_ARMOUR: return itemType == ITM_ARMOR_BODY_ARMOUR_3;
	case FIXED_ARTIFACT_OCCULT_CLOAK: return itemType == ITM_ARMOR_CLOAK;
	case FIXED_ARTIFACT_PEACH_HAT: return itemType == ITM_ARMOR_HEAD;
	case FIXED_ARTIFACT_BOUNDARY_GLOVES: return itemType == ITM_ARMOR_GLOVE;
	case FIXED_ARTIFACT_COWGIRL_BOOTS: return itemType == ITM_ARMOR_BOOT;
	case FIXED_ARTIFACT_STOPWATCH: return itemType == ITM_AMULET;
	case FIXED_ARTIFACT_SNAKE_RING:
	case FIXED_ARTIFACT_FROG_RING: return itemType == ITM_RING;
	default:
		return false;
	}
}


void MakeFixedArtifact(item* item_, fixed_artifact_type fixed_artifact, bool wiz) {
	item_->fixed_artifact = fixed_artifact;
	item_->identify = true;
	item_->identify_curse = true;
	item_->atifact_vector.clear();
	if(!wiz) {
		iden_list.fixed_artifact[fixed_artifact] = true;
	}
	auto fixed_weapon = [&](item_type type, int kind, int hit, int damage, int enchant,
		int max_delay, int min_delay, bool throwable, textures* image, LOCALIZATION_ENUM_KEY name) {
		item_->type = type;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = kind;
		item_->value1 = hit;
		item_->value2 = damage;
		item_->value3 = 0;
		item_->value4 = enchant;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = max_delay;
		item_->value8 = min_delay;
		item_->can_throw = throwable;
		item_->image = image;
		item_->equip_image = NULL;
		item_->name = name_infor(name);
		item_->item_tag.push_back(LOC_SYSTEM_TAG_WEAPON);
		item_->item_tag.push_back(type == ITM_WEAPON_SHORTBLADE ? LOC_SYSTEM_TAG_WEAPON_SHORTBLADE :
			(type == ITM_WEAPON_LONGBLADE ? LOC_SYSTEM_TAG_WEAPON_LONGBLADE :
			(type == ITM_WEAPON_MACE ? LOC_SYSTEM_TAG_WEAPON_MACE :
			(type == ITM_WEAPON_AXE ? LOC_SYSTEM_TAG_WEAPON_AXE : LOC_SYSTEM_TAG_WEAPON_SPEAR))));
		if(throwable)
			item_->item_tag.push_back(LOC_SYSTEM_TAG_THROWABLE);
		item_->weight = 5.0f;
		item_->value = 800;
		item_->curse = false;
	};
	auto fixed_armour = [&](item_type type, int ac, int max_ev, int min_ev, int enchant,
		textures* image, LOCALIZATION_ENUM_KEY name, LOCALIZATION_ENUM_KEY tag) {
		item_->type = type;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 0;
		item_->value1 = ac;
		item_->value2 = max_ev;
		item_->value3 = min_ev;
		item_->value4 = enchant;
		item_->value5 = 0;
		item_->value6 = item_->value7 = item_->value8 = 0;
		item_->can_throw = false;
		item_->image = image;
		item_->equip_image = NULL;
		item_->name = name_infor(name);
		item_->item_tag.push_back(LOC_SYSTEM_TAG_ARMOUR);
		item_->item_tag.push_back(tag);
		item_->weight = type >= ITM_ARMOR_HEAD ? 3.0f : 10.0f;
		item_->value = 800;
		item_->curse = false;
	};
	auto fixed_jewelry = [&](item_type type, int kind, textures* image, LOCALIZATION_ENUM_KEY name) {
		item_->type = type;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 0;
		item_->value1 = kind;
		item_->value2 = 1;
		item_->value3 = item_->value4 = item_->value5 = item_->value6 = item_->value7 = item_->value8 = 0;
		item_->can_throw = false;
		item_->image = image;
		item_->equip_image = NULL;
		item_->name = name_infor(name);
		item_->item_tag.push_back(LOC_SYSTEM_TAG_JEWELRY);
		item_->item_tag.push_back(type == ITM_RING ? LOC_SYSTEM_TAG_RING : LOC_SYSTEM_TAG_AMULET);
		item_->weight = 1.0f;
		item_->value = 800;
		item_->curse = false;
	};
	switch(fixed_artifact) {
	case FIXED_ARTIFACT_HAKKERO:
		fixed_weapon(ITM_WEAPON_MACE, 0, 4, 7, 0, 10, 5, false, &img_item_fixed_artifact_hakkero, LOC_SYSTEM_ITEM_ARTIFACT_HAKKERO_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[0];
		item_->weight = 0.2f;
		item_->value = 900;
		item_->atifact_vector.push_back(atifact_infor(ART_MAGICBOOST,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ANTIOVERHEAT,1));
		item_->atifact_vector.push_back(atifact_infor(ART_MANA,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,2));
		break;
	case FIXED_ARTIFACT_GUNGNIR:
		fixed_weapon(ITM_WEAPON_SPEAR, 4, -3, 15, 6, 18, 7, true, &img_item_fixed_artifact_gungnir, LOC_SYSTEM_ITEM_ARTIFACT_GUNGNIR_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[1];
		item_->weight = 8.0f;
		item_->value = 900;
		item_->atifact_vector.push_back(atifact_infor(ART_PENTAN,1));
		item_->atifact_vector.push_back(atifact_infor(ART_STR,6));
		item_->atifact_vector.push_back(atifact_infor(ART_EV,6));
		break;
	case FIXED_ARTIFACT_ROUKANKEN:
		fixed_weapon(ITM_WEAPON_LONGBLADE, 0, 1, 9, 8, 13, 7, false, &img_item_fixed_artifact_roukanken, LOC_SYSTEM_ITEM_ARTIFACT_ROUKANKEN_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[2];
		item_->value5 = WB_COLD;
		item_->value6 = -1;
		item_->weight = 4.0f;
		item_->value = 600;
		item_->atifact_vector.push_back(atifact_infor(ART_ICE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_DEX,5));
		break;
	case FIXED_ARTIFACT_HAKUROUKEN:
		fixed_armour(ITM_ARMOR_SHIELD, 3, -1, 0, 5, &img_item_fixed_artifact_hakurouken, LOC_SYSTEM_ITEM_ARTIFACT_HAKUROUKEN_NAME, LOC_SYSTEM_TAG_SHIELD);
		item_->equip_image = &img_play_item_fixed_artifact[3];
		item_->weight = 3.0f;
		item_->value = 300;
		item_->atifact_vector.push_back(atifact_infor(ART_COUNTER,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ICE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_SLAY,5));
		break;
	case FIXED_ARTIFACT_KOISHIHAT:
		fixed_armour(ITM_ARMOR_HEAD, 1, 0, 0, 3, &img_item_fixed_artifact_koishihat, LOC_SYSTEM_ITEM_ARTIFACT_KOISHIHAT_NAME, LOC_SYSTEM_TAG_HEAD);
		item_->equip_image = &img_play_item_fixed_artifact[4];
		item_->value = 500;
		item_->atifact_vector.push_back(atifact_infor(ART_PERMAINVI,1));
		item_->atifact_vector.push_back(atifact_infor(ART_UNCONSCIOUS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ELEC_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_CONFUSE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_TELEPORT,1));
		break;
	case FIXED_ARTIFACT_MIKOCLOAK:
		fixed_armour(ITM_ARMOR_CLOAK, 1, 0, 0, -1, &img_item_fixed_artifact_mikocloak, LOC_SYSTEM_ITEM_ARTIFACT_MIKOCLOAK_NAME, LOC_SYSTEM_TAG_CLOAK);
		item_->equip_image = &img_play_item_fixed_artifact[5];
		item_->weight = 5.0f;
		item_->value = 600;
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ICE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ELEC_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGIC_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_SEE_INVISIBLE,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FULL,1));
		break;
	case FIXED_ARTIFACT_LUNATICTORCH:
		fixed_weapon(ITM_WEAPON_MACE, 2, 2, 8, 13, 13, 7, false, &img_item_fixed_artifact_lunatictorch, LOC_SYSTEM_ITEM_ARTIFACT_LUNATICTORCH_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[6];
		item_->value5 = WB_FIRE;
		item_->value6 = -1;
		item_->value = 600;
		item_->atifact_vector.push_back(atifact_infor(ART_LUNATIC,1));
		item_->atifact_vector.push_back(atifact_infor(ART_HALO,1));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGACIAN,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,2));
		break;
	case FIXED_ARTIFACT_MOONGEM:
		fixed_jewelry(ITM_AMULET, AMT_PURIFTY, &img_item_fixed_artifact_moongem, LOC_SYSTEM_ITEM_ARTIFACT_MOONGEM_NAME);
		item_->value2 = 0;
		item_->value = 400;
		item_->atifact_vector.push_back(atifact_infor(ART_CONFUSE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGIC_RESIS,2));
		break;
	case FIXED_ARTIFACT_NUCLEARBOOT:
		fixed_armour(ITM_ARMOR_BOOT, 1, 0, 0, 6, &img_item_fixed_artifact_nuclearboot, LOC_SYSTEM_ITEM_ARTIFACT_NUCLEARBOOT_NAME, LOC_SYSTEM_TAG_FOOT);
		item_->equip_image = &img_play_item_fixed_artifact[7];
		item_->weight = 4.0f;
		item_->value = 450;
		item_->atifact_vector.push_back(atifact_infor(ART_RAD,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,2));
		item_->atifact_vector.push_back(atifact_infor(ART_ELEC_RESIS,1));
		break;
	case FIXED_ARTIFACT_CONTROLROD:
		fixed_weapon(ITM_WEAPON_MACE, 4, -6, 18, 7, 21, 8, false, &img_item_fixed_artifact_controlrod, LOC_SYSTEM_ITEM_ARTIFACT_CONTROLROD_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[8];
		item_->weight = 20.0f;
		item_->value = 1200;
		item_->atifact_vector.push_back(atifact_infor(ART_FIREBALL,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_CONFUSE_RESIS,1));
		break;
	case FIXED_ARTIFACT_PICKANDSHOVELS:
		fixed_weapon(ITM_WEAPON_AXE, 2, -5, 15, 3, 17, 7, false, &img_item_fixed_artifact_pickandshovels, LOC_SYSTEM_ITEM_ARTIFACT_PICKANDSHOVELS_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[9];
		item_->value5 = WB_POISON;
		item_->value6 = -1;
		item_->weight = 12.0f;
		item_->value = 1100;
		item_->atifact_vector.push_back(atifact_infor(ART_GLUTTON,1));
		item_->atifact_vector.push_back(atifact_infor(ART_HUNGRY,1));
		item_->atifact_vector.push_back(atifact_infor(ART_POISON_RESIS,1));
		break;
	case FIXED_ARTIFACT_SILVERKNIFE:
		fixed_weapon(ITM_WEAPON_SHORTBLADE, 1, 5, 7, 9, 10, 5, true, &img_item_fixed_artifact_silverknife, LOC_SYSTEM_ITEM_ARTIFACT_SILVERKNIFE_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[10];
		item_->value5 = WB_SILVER;
		item_->value6 = -1;
		item_->weight = 1.5f;
		item_->value = 500;
		item_->atifact_vector.push_back(atifact_infor(ART_EV,8));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGIC_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_SKILL_UP,SKT_TRANS+400));
		break;
	case FIXED_ARTIFACT_FIREFLYCLOAK:
		fixed_armour(ITM_ARMOR_CLOAK, 1, 0, 0, 2, &img_item_fixed_artifact_fireflycloak, LOC_SYSTEM_ITEM_ARTIFACT_FIREFLYCLOAK_NAME, LOC_SYSTEM_TAG_CLOAK);
		item_->equip_image = &img_play_item_fixed_artifact[11];
		item_->weight = 5.0f;
		item_->value = 300;
		item_->atifact_vector.push_back(atifact_infor(ART_BUG,1));
		item_->atifact_vector.push_back(atifact_infor(ART_POISON_RESIS,1));
		break;
	case FIXED_ARTIFACT_ICEFAIRYRING:
		fixed_jewelry(ITM_RING, RGT_ICE_RESIS, &img_item_fixed_artifact_icefairyring, LOC_SYSTEM_ITEM_ARTIFACT_ICEFAIRYRING_NAME);
		item_->value = 500;
		item_->atifact_vector.push_back(atifact_infor(ART_INT,-9));
		item_->atifact_vector.push_back(atifact_infor(ART_SKILL_UP,SKT_COLD+900));
		break;
	case FIXED_ARTIFACT_LAEVATEIN:
		fixed_weapon(ITM_WEAPON_LONGBLADE, 2, -4, 14, 11, 16, 7, false, &img_item_fixed_artifact_laevatein, LOC_SYSTEM_ITEM_ARTIFACT_LAEVATEIN_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[12];
		item_->value5 = WB_FIREPLUS;
		item_->value6 = -1;
		item_->weight = 12.0f;
		item_->value = 950;
		item_->atifact_vector.push_back(atifact_infor(ART_AC,-4));
		break;
	case FIXED_ARTIFACT_LILYRING:
		fixed_jewelry(ITM_RING, RGT_AC, &img_item_fixed_artifact_lilyring, LOC_SYSTEM_ITEM_ARTIFACT_LILYRING_NAME);
		item_->value2 = 5;
		item_->value = 400;
		item_->atifact_vector.push_back(atifact_infor(ART_POISONIMMUNE,1));
		break;
	case FIXED_ARTIFACT_GALECLOGS:
		fixed_armour(ITM_ARMOR_BOOT, 1, 0, 0, 0, &img_item_fixed_artifact_galeclogs, LOC_SYSTEM_ITEM_ARTIFACT_GALECLOGS_NAME, LOC_SYSTEM_TAG_FOOT);
		item_->equip_image = &img_play_item_fixed_artifact[13];
		item_->weight = 4.0f;
		item_->value = 300;
		item_->atifact_vector.push_back(atifact_infor(ART_SWIFT,1));
		item_->atifact_vector.push_back(atifact_infor(ART_EV,4));
		break;
	case FIXED_ARTIFACT_HELLTSHIRT:
	{
		fixed_armour(ITM_ARMOR_BODY_ARMOUR_0, GetMaterial(MTK_ROBE,AMV_AC), GetMaterial(MTK_ROBE,AMV_MAX_EV), GetMaterial(MTK_ROBE,AMV_MIN_EV), 6, &img_item_fixed_artifact_helltshirt, LOC_SYSTEM_ITEM_ARTIFACT_HELLTSHIRT_NAME, LOC_SYSTEM_TAG_BODY);
		item_->equip_image = &img_play_item_fixed_artifact[14];
		item_->item_tag.push_back(LOC_SYSTEM_TAG_BODY0);
		item_->value5 = AMK_NORMAL;
		item_->weight = 6.0f;
		item_->value = 500;
		int rand_ = rand_int(0,2);
		item_->atifact_vector.push_back(atifact_infor(ART_STR,6*(rand_==0?-1:1)));
		item_->atifact_vector.push_back(atifact_infor(ART_DEX,6*(rand_==1?-1:1)));
		item_->atifact_vector.push_back(atifact_infor(ART_INT,6*(rand_==2?-1:1)));
		break;
	}
	case FIXED_ARTIFACT_KAPPAFULLARMOR:
		fixed_armour(ITM_ARMOR_BODY_ARMOUR_3, GetMaterial(MTK_PLATE,AMV_AC), GetMaterial(MTK_PLATE,AMV_MAX_EV), GetMaterial(MTK_PLATE,AMV_MIN_EV), 12, &img_item_fixed_artifact_kappafullarmor, LOC_SYSTEM_ITEM_ARTIFACT_KAPPAFULLARMOR_NAME, LOC_SYSTEM_TAG_BODY);
		item_->equip_image = &img_play_item_fixed_artifact[15];
		item_->item_tag.push_back(LOC_SYSTEM_TAG_BODY3);
		item_->value5 = AMK_KAPPA;
		item_->weight = 30.0f;
		item_->value = 1200;
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,2));
		item_->atifact_vector.push_back(atifact_infor(ART_MISSLE,1));
		item_->atifact_vector.push_back(atifact_infor(ART_SELFDESTRUCT,1));
		break;
	case FIXED_ARTIFACT_MAIDUNIFORM:
		fixed_armour(ITM_ARMOR_BODY_ARMOUR_2, GetMaterial(MTK_CHAIN,AMV_AC), GetMaterial(MTK_CHAIN,AMV_MAX_EV), GetMaterial(MTK_CHAIN,AMV_MIN_EV), 4, &img_item_fixed_artifact_maiduniform, LOC_SYSTEM_ITEM_ARTIFACT_MAIDUNIFORM_NAME, LOC_SYSTEM_TAG_BODY);
		item_->equip_image = &img_play_item_fixed_artifact[16];
		item_->item_tag.push_back(LOC_SYSTEM_TAG_BODY2);
		item_->value5 = AMK_MAID;
		item_->weight = 16.0f;
		item_->value = 900;
		item_->atifact_vector.push_back(atifact_infor(ART_SUMMONRESIST,1));
		item_->atifact_vector.push_back(atifact_infor(ART_EV,5));
		item_->atifact_vector.push_back(atifact_infor(ART_INT,5));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGACIAN,1));
		break;
	case FIXED_ARTIFACT_IBUKISAKE:
		fixed_armour(ITM_ARMOR_SHIELD, 7, -3, 0, 7, &img_item_fixed_artifact_ibukisake, LOC_SYSTEM_ITEM_ARTIFACT_IBUKISAKE_NAME, LOC_SYSTEM_TAG_SHIELD);
		item_->equip_image = &img_play_item_fixed_artifact[17];
		item_->weight = 5.0f;
		item_->value = 500;
		item_->atifact_vector.push_back(atifact_infor(ART_DRUNK,1));
		item_->atifact_vector.push_back(atifact_infor(ART_HP_REGEN,3));
		item_->atifact_vector.push_back(atifact_infor(ART_POISON_RESIS,1));
		break;
	case FIXED_ARTIFACT_SHINING_NEEDLE_SWORD:
		fixed_weapon(ITM_WEAPON_SHORTBLADE, 0, 4, 8, 2, 10, 5, false, &img_item_fixed_artifact_shining_needle_sword, LOC_SYSTEM_ITEM_ARTIFACT_SHINING_NEEDLE_SWORD_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[18];
		item_->weight = 2.0f;
		item_->atifact_vector.push_back(atifact_infor(ART_CONFUSE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_STR, -3));
		item_->atifact_vector.push_back(atifact_infor(ART_EV, 6));
		item_->atifact_vector.push_back(atifact_infor(ART_POISON_RESIS, 1));
		break;
	case FIXED_ARTIFACT_SWORD_OF_SCARLET_PERCEPTION:
		fixed_weapon(ITM_WEAPON_LONGBLADE, 0, 1, 9, 7, 13, 7, false, &img_item_fixed_artifact_sword_of_scarlet_perception, LOC_SYSTEM_ITEM_ARTIFACT_SWORD_OF_SCARLET_PERCEPTION_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[19];
		item_->value5 = WB_WEATHER;
		item_->value6 = -1;
		item_->atifact_vector.push_back(atifact_infor(ART_WEATHER_TRIGGER, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_ELEC_RESIS, 2));
		break;
	case FIXED_ARTIFACT_GOLIATH_SWORD:
		fixed_weapon(ITM_WEAPON_LONGBLADE, 2, -4, 14, 6, 16, 7, false, &img_item_fixed_artifact_goliath_sword, LOC_SYSTEM_ITEM_ARTIFACT_GOLIATH_SWORD_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[20];
		item_->weight = 18.0f;
		item_->atifact_vector.push_back(atifact_infor(ART_WHIRLWIND, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_HEAVY, 1));
		break;
	case FIXED_ARTIFACT_REAPER_SCYTHE:
		fixed_weapon(ITM_WEAPON_SPEAR, 2, -2, 12, 6, 15, 7, false, &img_item_fixed_artifact_reaper_scythe, LOC_SYSTEM_ITEM_ARTIFACT_REAPER_SCYTHE_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[21];
		item_->weight = 9.0f;
		item_->atifact_vector.push_back(atifact_infor(ART_INFINITE_REACH, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_PULL, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_SLAY, -3));
		break;
	case FIXED_ARTIFACT_UNIDENTIFIED_TRIDENT:
		fixed_weapon(ITM_WEAPON_SPEAR, 3, 0, 11, 0, 14, 7, false, &img_item_fixed_artifact_unidentified_trident, LOC_SYSTEM_ITEM_ARTIFACT_UNIDENTIFIED_TRIDENT_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[22];
		item_->atifact_vector.push_back(atifact_infor(ART_UNKNOWN_POWER, 18));
		break;
	case FIXED_ARTIFACT_SUNKEN_ANCHOR:
		fixed_weapon(ITM_WEAPON_AXE, 2, -5, 15, 9, 17, 7, false, &img_item_fixed_artifact_sunken_anchor, LOC_SYSTEM_ITEM_ARTIFACT_SUNKEN_ANCHOR_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[23];
		item_->value5 = WB_FLOOD;
		item_->value6 = -1;
		item_->weight = 15.0f;
		item_->atifact_vector.push_back(atifact_infor(ART_SWIM, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_ICE_RESIS, 2));
		break;
	case FIXED_ARTIFACT_YAMANBA_CLEAVER:
		fixed_weapon(ITM_WEAPON_AXE, 0, 2, 8, 8, 13, 7, true, &img_item_fixed_artifact_yamanba_cleaver, LOC_SYSTEM_ITEM_ARTIFACT_YAMANBA_CLEAVER_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[24];
		item_->weight = 4.0f;
		item_->atifact_vector.push_back(atifact_infor(ART_LESS_POWER, -2));
		item_->atifact_vector.push_back(atifact_infor(ART_STR, 5));
		break;
	case FIXED_ARTIFACT_BUTTERFLY_FAN:
		fixed_weapon(ITM_WEAPON_MACE, 2, 2, 8, 4, 13, 7, false, &img_item_fixed_artifact_butterfly_fan, LOC_SYSTEM_ITEM_ARTIFACT_BUTTERFLY_FAN_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[25];
		item_->weight = 3.0f;
		item_->atifact_vector.push_back(atifact_infor(ART_INSTANT_DEATH, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_SEE_INVISIBLE, 1));
		break;
	case FIXED_ARTIFACT_RED_MALLET:
		fixed_weapon(ITM_WEAPON_MACE, 4, -4, 16, 4, 19, 8, false, &img_item_fixed_artifact_red_mallet, LOC_SYSTEM_ITEM_ARTIFACT_RED_MALLET_NAME);
		item_->equip_image = &img_play_item_fixed_artifact[26];
		item_->weight = 16.0f;
		item_->atifact_vector.push_back(atifact_infor(ART_KNOCKAWAY, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_CONFUSE_RESIS, 1));
		break;
	case FIXED_ARTIFACT_IMMOVABLE_LIBRARY:
		fixed_armour(ITM_ARMOR_BODY_ARMOUR_0, GetMaterial(MTK_ROBE, AMV_AC), GetMaterial(MTK_ROBE, AMV_MAX_EV), GetMaterial(MTK_ROBE, AMV_MIN_EV), 2, &img_item_fixed_artifact_immovable_library, LOC_SYSTEM_ITEM_ARTIFACT_IMMOVABLE_LIBRARY_NAME, LOC_SYSTEM_TAG_BODY);
		item_->equip_image = &img_play_item_fixed_artifact[27];
		item_->item_tag.push_back(LOC_SYSTEM_TAG_BODY0);
		item_->atifact_vector.push_back(atifact_infor(ART_MAGACIAN, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGICBOOST, 1));
		break;
	case FIXED_ARTIFACT_FULLMOON_DRESS:
		fixed_armour(ITM_ARMOR_BODY_ARMOUR_2, GetMaterial(MTK_CHAIN, AMV_AC), GetMaterial(MTK_CHAIN, AMV_MAX_EV), GetMaterial(MTK_CHAIN, AMV_MIN_EV), 5, &img_item_fixed_artifact_fullmoon_dress, LOC_SYSTEM_ITEM_ARTIFACT_FULLMOON_DRESS_NAME, LOC_SYSTEM_TAG_BODY);
		item_->equip_image = &img_play_item_fixed_artifact[28];
		item_->item_tag.push_back(LOC_SYSTEM_TAG_BODY2);
		item_->atifact_vector.push_back(atifact_infor(ART_ICE_RESIS, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_CONFUSE_RESIS, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_JUMP, 1));
		break;
	case FIXED_ARTIFACT_HANIWA_ARMOUR:
		fixed_armour(ITM_ARMOR_BODY_ARMOUR_3, GetMaterial(MTK_PLATE, AMV_AC), GetMaterial(MTK_PLATE, AMV_MAX_EV), GetMaterial(MTK_PLATE, AMV_MIN_EV), 15, &img_item_fixed_artifact_haniwa_armour, LOC_SYSTEM_ITEM_ARTIFACT_HANIWA_ARMOUR_NAME, LOC_SYSTEM_TAG_BODY);
		item_->equip_image = &img_play_item_fixed_artifact[29];
		item_->item_tag.push_back(LOC_SYSTEM_TAG_BODY3);
		item_->atifact_vector.push_back(atifact_infor(ART_ELEC_RESIS, 1));
		break;
	case FIXED_ARTIFACT_OCCULT_CLOAK:
		fixed_armour(ITM_ARMOR_CLOAK, 1, 0, 0, 0, &img_item_fixed_artifact_occult_cloak, LOC_SYSTEM_ITEM_ARTIFACT_OCCULT_CLOAK_NAME, LOC_SYSTEM_TAG_CLOAK);
		item_->equip_image = &img_play_item_fixed_artifact[30];
		item_->atifact_vector.push_back(atifact_infor(ART_MANA, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGACIAN, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGIC_RESIS, 1));
		break;
	case FIXED_ARTIFACT_PEACH_HAT:
		fixed_armour(ITM_ARMOR_HEAD, 1, 0, 0, 4, &img_item_fixed_artifact_peach_hat, LOC_SYSTEM_ITEM_ARTIFACT_PEACH_HAT_NAME, LOC_SYSTEM_TAG_HEAD);
		item_->equip_image = &img_play_item_hat[7];
		item_->atifact_vector.push_back(atifact_infor(ART_HP_REGEN, 3));
		break;
	case FIXED_ARTIFACT_BOUNDARY_GLOVES:
		fixed_armour(ITM_ARMOR_GLOVE, 1, 0, 0, 0, &img_item_fixed_artifact_boundary_gloves, LOC_SYSTEM_ITEM_ARTIFACT_BOUNDARY_GLOVES_NAME, LOC_SYSTEM_TAG_HAND);
		item_->equip_image = &img_play_item_fixed_artifact[31];
		item_->atifact_vector.push_back(atifact_infor(ART_SKILL_UP, SKT_TANMAC + 300));
		item_->atifact_vector.push_back(atifact_infor(ART_RETURN, 1));
		break;
	case FIXED_ARTIFACT_COWGIRL_BOOTS:
		fixed_armour(ITM_ARMOR_BOOT, 1, 0, 0, 3, &img_item_fixed_artifact_cowgirl_boots, LOC_SYSTEM_ITEM_ARTIFACT_COWGIRL_BOOTS_NAME, LOC_SYSTEM_TAG_FOOT);
		item_->equip_image = &img_play_item_fixed_artifact[32];
		item_->atifact_vector.push_back(atifact_infor(ART_KICK, 1));
		break;
	case FIXED_ARTIFACT_STOPWATCH:
		fixed_jewelry(ITM_AMULET, AMT_TIME_STOP, &img_item_fixed_artifact_stopwatch, LOC_SYSTEM_ITEM_ARTIFACT_STOPWATCH_NAME);
		item_->atifact_vector.push_back(atifact_infor(ART_EV, 6));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGIC_RESIS, 1));
		break;
	case FIXED_ARTIFACT_SNAKE_RING:
		fixed_jewelry(ITM_RING, RGT_STR, &img_item_fixed_artifact_snake_ring, LOC_SYSTEM_ITEM_ARTIFACT_SNAKE_RING_NAME);
		item_->value2 = 4;
		item_->atifact_vector.push_back(atifact_infor(ART_MAX_HP, 15));
		break;
	case FIXED_ARTIFACT_FROG_RING:
		fixed_jewelry(ITM_RING, RGT_POISON_RESIS, &img_item_fixed_artifact_frog_ring, LOC_SYSTEM_ITEM_ARTIFACT_FROG_RING_NAME);
		item_->atifact_vector.push_back(atifact_infor(ART_DIVE, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_SWIM, 1));
		item_->atifact_vector.push_back(atifact_infor(ART_CURSE, 1));
		break;
	default:
		break;
	}
}
