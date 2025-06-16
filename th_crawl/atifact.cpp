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
	case ART_ELEC_RESIS:
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
	case ART_SILVER:
			return 1;
	case ART_FIRE_RESIS:
	case ART_ICE_RESIS:
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
				skill_ == SKT_ARMOUR || skill_ == SKT_SHIELD || skill_ == SKT_EVOCATE);
			skill_ += randA_1(4) * 100;
			return skill_;
		}
	default:
		break;
	}
	return 1;
}

string GetAtifactString(artifact_type ring_, int value_)
{	
    std::ostringstream oss;
	switch(ring_)
	{
	case ART_STR:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_STR, PlaceHolderHelper(((value_ < 0) ? "" : "+") + to_string(value_)));
		break;
	case ART_DEX:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_DEX, PlaceHolderHelper(((value_ < 0) ? "" : "+") + to_string(value_)));
		break;
	case ART_INT:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_INT, PlaceHolderHelper(((value_ < 0) ? "" : "+") + to_string(value_)));
		break;
	case ART_HUNGRY:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HUNGRY);
		break;
	case ART_FULL:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_FULL);
		break;
	case ART_TELEPORT:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_TELEPORT);
		break;
	case ART_POISON_RESIS:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_POISON_RESIST, PlaceHolderHelper((value_>0?"+":"-")));
		break;
	case ART_FIRE_RESIS:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_FIRE_RESIST, PlaceHolderHelper((value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			))))))));
		break;
	case ART_ICE_RESIS:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_COLD_RESIST, PlaceHolderHelper((value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			))))))));
		break;
	case ART_SEE_INVISIBLE:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_SEE_INVISIBLE);
		break;
	case ART_LEVITATION:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_FLIGHT);
		break;
	case ART_INVISIBLE:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INVISIBLE);
		break;
	case ART_MANA:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_MANA);
		break;
	case ART_MAGACIAN:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_MAGICIAN);
		break;
	case ART_AC:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_AC, PlaceHolderHelper((value_<0?"":"+") + to_string(value_)));
		break;
	case ART_EV:
		oss << LocalzationManager::formatString(LOC_SYSTEM_ITEM_ARTIFACT_EV, PlaceHolderHelper((value_<0?"":"+") + to_string(value_)));
		break;
	case ART_CONFUSE_RESIS:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_CONFUSE_RESIST);
		break;
	case ART_ELEC_RESIS:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_ELEC_RESIST);
		break;
	case ART_MAGIC_RESIS:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_MAGIC_RESIST);
		break;
	case ART_MAGICBOOST:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HAKKERO_MAGICBOOST);
		break;
	case ART_ANTIOVERHEAT:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HAKKERO_ANTIOVERHEAT);
		break;
	case ART_PENTAN:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_GUNGNIR_PENTAN);
		break;
	case ART_COUNTER:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_HAKUROUKEN_COUNTER);
		break;
	case ART_PERMAINVI:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_KOISHIHAT_PERMAINVI);
		break;
	case ART_UNCONSCIOUS:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_KOISHIHAT_UNCONSCIOUS);
		break;
	case ART_LUNATIC:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_LUNATICTORCH_LUNATIC);
		break;
	case ART_HALO:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_LUNATICTORCH_HALO);
		break;
	case ART_RAD:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_NUCLEARBOOT_RAD);
		break;
	case ART_FIREBALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_CONTROLROD_FIREBALL);
		break;
	case ART_GLUTTON:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_PICKANDSHOVELS_GLUTTON);
		break;
	case ART_SILVER:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_SILVERKNIFE_SILVER);
		break;
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
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_INFO_ELEC_RESIST);
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
	case ART_SILVER:
		oss << LocalzationManager::locString(LOC_SYSTEM_ITEM_ARTIFACT_SILVERKNIFE_SILVER_INFO);
		break;
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
				you.s_levitation=0; 
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
		break;
	case ART_MAGIC_RESIS:
		you.MRUpDown((value>0?1:-1)*(20+abs(value)*20));
		break;
	case ART_MAGICBOOST:
		break;
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
	case ART_SILVER:
		break;
	case ART_SKILL_UP:
	{
		int value_ = abs(value);
		you.BonusSkillUpDown(value_ % 100, (value>0?1:-1) *value_ / 100);

	}
		break;
	default:
		break;
	}
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



void MakeArtifact(item* item_, int good_bad_)
{
	int num_ = 1+randA(good_bad_ +randA(3));
	deque<int> temp;
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

		temp.push_back(i);
	}
	rand_shuffle(temp.begin(),temp.end());
	for(int i = 0; i < num_ ; i++)
	{
		if(item_->value1 != temp[i] || item_->type != ITM_RING)
		{
			int gb_ = randA(3)?good_bad_:good_bad_*-1;
			item_->atifact_vector.push_back(atifact_infor(temp[i],GetAtifactValue((artifact_type)temp[i],gb_)));
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
	item_->second_name= name_infor(LOC_SYSTEM_ITEM_ARTIFACT);

}


std::string GetFixedArtifact(fixed_artifact_type fixed_artifact) {
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
	default:
		break;
	}
	return "";
}

void MakeFixedArtifact(item* item_, fixed_artifact_type fixed_artifact) {
	item_->fixed_artifact = fixed_artifact;
	item_->identify = true;
	item_->identify_curse = true;
	switch(fixed_artifact) {
	case FIXED_ARTIFACT_HAKKERO:
		item_->type = ITM_WEAPON_MACE;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 0;
		item_->value1 = 4;
		item_->value2 = 7;
		item_->value3 = 0;
		item_->value4 = 0;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = 10;
		item_->value8 = 5;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_hakkero;
		item_->equip_image = &img_play_item_fixed_artifact[0];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_HAKKERO_NAME);
		item_->weight = 0.2f;
		item_->value = 900;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_MAGICBOOST,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ANTIOVERHEAT,1));
		item_->atifact_vector.push_back(atifact_infor(ART_MANA,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,2));
		break;
	case FIXED_ARTIFACT_GUNGNIR:
		item_->type = ITM_WEAPON_SPEAR;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 4;
		item_->value1 = -3;
		item_->value2 = 15;
		item_->value3 = 0;
		item_->value4 = 6;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = 18;
		item_->value8 = 7;
		item_->can_throw = true;
		item_->image = &img_item_fixed_artifact_gungnir;
		item_->equip_image = &img_play_item_fixed_artifact[1];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_GUNGNIR_NAME);
		item_->weight = 8.0f;
		item_->value = 900;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_PENTAN,1));
		item_->atifact_vector.push_back(atifact_infor(ART_STR,6));
		item_->atifact_vector.push_back(atifact_infor(ART_EV,6));
		break;
	case FIXED_ARTIFACT_ROUKANKEN:
		item_->type = ITM_WEAPON_LONGBLADE;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 0;
		item_->value1 = 1;
		item_->value2 = 9;
		item_->value3 = 0;
		item_->value4 = 8;
		item_->value5 = 2;
		item_->value6 = -1;
		item_->value7 = 13;
		item_->value8 = 7;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_roukanken;
		item_->equip_image = &img_play_item_fixed_artifact[2];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_ROUKANKEN_NAME);
		item_->weight = 4.0f;
		item_->value = 600;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_ICE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_DEX,5));
		break;
	case FIXED_ARTIFACT_HAKUROUKEN:
		item_->type = ITM_ARMOR_SHIELD;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 0;
		item_->value1 = 3;
		item_->value2 = -1;
		item_->value3 = 0;
		item_->value4 = 5;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = 0;
		item_->value8 = 0;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_hakurouken;
		item_->equip_image = &img_play_item_fixed_artifact[3];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_HAKUROUKEN_NAME);
		item_->weight = 3.0f;
		item_->value = 300;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_COUNTER,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ICE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_STR,5));
		break;
	case FIXED_ARTIFACT_KOISHIHAT:
		item_->type = ITM_ARMOR_HEAD;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 0;
		item_->value1 = 1;
		item_->value2 = 0;
		item_->value3 = 0;
		item_->value4 = 3;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = 0;
		item_->value8 = 0;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_koishihat;
		item_->equip_image = &img_play_item_fixed_artifact[4];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_KOISHIHAT_NAME);
		item_->weight = 3.0f;
		item_->value = 500;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_PERMAINVI,1));
		item_->atifact_vector.push_back(atifact_infor(ART_UNCONSCIOUS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ELEC_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_CONFUSE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_TELEPORT,1));
		break;
	case FIXED_ARTIFACT_MIKOCLOAK:
		item_->type = ITM_ARMOR_CLOAK;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 0;
		item_->value1 = 1;
		item_->value2 = 0;
		item_->value3 = 0;
		item_->value4 = -1;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = 0;
		item_->value8 = 0;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_mikocloak;
		item_->equip_image = &img_play_item_fixed_artifact[5];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_MIKOCLOAK_NAME);
		item_->weight = 5.0f;
		item_->value = 600;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ICE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_ELEC_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGIC_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_SEE_INVISIBLE,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FULL,1));
		break;
	case FIXED_ARTIFACT_LUNATICTORCH:
		item_->type = ITM_WEAPON_MACE;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 2;
		item_->value1 = 2;
		item_->value2 = 8;
		item_->value3 = 0;
		item_->value4 = 13;
		item_->value5 = 1;
		item_->value6 = -1;
		item_->value7 = 13;
		item_->value8 = 7;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_lunatictorch;
		item_->equip_image = &img_play_item_fixed_artifact[6];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_LUNATICTORCH_NAME);
		item_->weight = 5.0f;
		item_->value = 600;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_LUNATIC,1));
		item_->atifact_vector.push_back(atifact_infor(ART_HALO,1));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGACIAN,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,2));
		break;
	case FIXED_ARTIFACT_MOONGEM:
		item_->type = ITM_AMULET;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 0;
		item_->value1 = AMT_BLOSSOM; //TODO
		item_->value2 = 0;
		item_->value3 = 0;
		item_->value4 = 0;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = 0;
		item_->value8 = 0;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_moongem;
		item_->equip_image = NULL;
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_MOONGEM_NAME);
		item_->weight = 1.0f;
		item_->value = 400;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_CONFUSE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGIC_RESIS,2));
		break;
	case FIXED_ARTIFACT_NUCLEARBOOT:
		item_->type = ITM_ARMOR_BOOT;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 0;
		item_->value1 = 1;
		item_->value2 = 0;
		item_->value3 = 0;
		item_->value4 = 1;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = 0;
		item_->value8 = 0;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_nuclearboot;
		item_->equip_image = &img_play_item_fixed_artifact[7];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_NUCLEARBOOT_NAME);
		item_->weight = 4.0f;
		item_->value = 450;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_RAD,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_LEVITATION,1));
		item_->atifact_vector.push_back(atifact_infor(ART_AC,5));
		break;
	case FIXED_ARTIFACT_CONTROLROD:
		item_->type = ITM_WEAPON_MACE;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 4;
		item_->value1 = -6;
		item_->value2 = 18;
		item_->value3 = 0;
		item_->value4 = 7;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = 21;
		item_->value8 = 8;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_controlrod;
		item_->equip_image = &img_play_item_fixed_artifact[8];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_CONTROLROD_NAME);
		item_->weight = 20.0f;
		item_->value = 1200;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_FIREBALL,1));
		item_->atifact_vector.push_back(atifact_infor(ART_FIRE_RESIS,3));
		break;
	case FIXED_ARTIFACT_PICKANDSHOVELS:
		item_->type = ITM_WEAPON_AXE;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 2;
		item_->value1 = -5;
		item_->value2 = 15;
		item_->value3 = 0;
		item_->value4 = 3;
		item_->value5 = 3;
		item_->value6 = -1;
		item_->value7 = 17;
		item_->value8 = 7;
		item_->can_throw = false;
		item_->image = &img_item_fixed_artifact_pickandshovels;
		item_->equip_image = &img_play_item_fixed_artifact[9];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_PICKANDSHOVELS_NAME);
		item_->weight = 12.0f;
		item_->value = 1100;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_GLUTTON,1));
		item_->atifact_vector.push_back(atifact_infor(ART_HUNGRY,1));
		item_->atifact_vector.push_back(atifact_infor(ART_POISON_RESIS,1));
		break;
	case FIXED_ARTIFACT_SILVERKNIFE:
		item_->type = ITM_WEAPON_SHORTBLADE;
		item_->is_pile = false;
		item_->num = 1;
		item_->value0 = 1;
		item_->value1 = 5;
		item_->value2 = 6;
		item_->value3 = 0;
		item_->value4 = 9;
		item_->value5 = 0;
		item_->value6 = 0;
		item_->value7 = 10;
		item_->value8 = 5;
		item_->can_throw = true;
		item_->image = &img_item_fixed_artifact_silverknife;
		item_->equip_image = &img_play_item_fixed_artifact[10];
		item_->name = name_infor(LOC_SYSTEM_ITEM_ARTIFACT_SILVERKNIFE_NAME);
		item_->weight = 1.5f;
		item_->value = 500;
		item_->curse = false;
		item_->atifact_vector.push_back(atifact_infor(ART_SILVER,1));
		item_->atifact_vector.push_back(atifact_infor(ART_EV,8));
		item_->atifact_vector.push_back(atifact_infor(ART_MAGIC_RESIS,1));
		item_->atifact_vector.push_back(atifact_infor(ART_SKILL_UP,SKT_TRANS+400));
		break;
	default:
		break;
	}
}