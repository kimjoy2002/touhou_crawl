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


int GetAtifactValue(ring_type ring_, int good_bad_)
{	
	int a_ = good_bad_>=0?1:-1;
	static char temp[32];
	switch(ring_)
	{
	case RGT_STR:
	case RGT_DEX:
	case RGT_INT:
	case RGT_AC:
	case RGT_EV:
			return (1+randA(5))*a_;
	case RGT_HUNGRY:
	case RGT_FULL:
	case RGT_TELEPORT:
	case RGT_POISON_RESIS:
	case RGT_SEE_INVISIBLE:
	//case RGT_GRAZE:
	case RGT_LEVITATION:
	case RGT_INVISIBLE:
	case RGT_MANA:
	case RGT_MAGACIAN:
	case RGT_CONFUSE_RESIS:
	case RGT_ELEC_RESIS:
			return 1;
	case RGT_FIRE_RESIS:
	case RGT_ICE_RESIS:
		return a_>0?(randA(4)?1:(randA(10)?2:3)):-1;
	case RGT_MAGIC_RESIS:
		return randA(2)?1:rand_int(2,3);
	case RGT_SKILL_UP:
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
	}
	return 1;
}

const char* GetAtifactString(ring_type ring_, int value_)
{	
	static char temp[32];
	switch(ring_)
	{
	case RGT_STR:
		sprintf_s(temp,32,"힘%s%d",value_<0?"":"+",value_);
		break;
	case RGT_DEX:
		sprintf_s(temp,32,"민첩%s%d",value_<0?"":"+",value_);
		break;
	case RGT_INT:
		sprintf_s(temp,32,"지능%s%d",value_<0?"":"+",value_);
		break;
	case RGT_HUNGRY:
		sprintf_s(temp,32,"허기");
		break;
	case RGT_FULL:
		sprintf_s(temp,32,"포만감");
		break;
	case RGT_TELEPORT:
		sprintf_s(temp,32,"*전이");
		break;
	case RGT_POISON_RESIS:
		sprintf_s(temp,32,"독저항%s",value_>0?"+":"-");
		break;
	case RGT_FIRE_RESIS:
		sprintf_s(temp,32,"화염저항%s",(value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			)))))));
		break;
	case RGT_ICE_RESIS:
		sprintf_s(temp,32,"냉기저항%s",(value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			)))))));
		break;
	case RGT_SEE_INVISIBLE:
		sprintf_s(temp,32,"투명감지");
		break;
	//case RGT_GRAZE:
	//	sprintf_s(temp,32,"+그레이즈");
	//	break;
	case RGT_LEVITATION:
		sprintf_s(temp,32,"+비행");
		break;
	case RGT_INVISIBLE:
		sprintf_s(temp,32,"+투명");
		break;
	case RGT_MANA:
		sprintf_s(temp,32,"영력");
		break;
	case RGT_MAGACIAN:
		sprintf_s(temp,32,"마법사");
		break;
	case RGT_AC:
		sprintf_s(temp,32,"AC%s%d",value_<0?"":"+",value_);
		break;
	case RGT_EV:
		sprintf_s(temp,32,"EV%s%d",value_<0?"":"+",value_);
		break;
	case RGT_CONFUSE_RESIS:
		sprintf_s(temp,32,"혼란저항");
		break;
	case RGT_ELEC_RESIS:
		sprintf_s(temp,32,"전기저항");
		break;
	case RGT_MAGIC_RESIS:
		sprintf_s(temp,32,"마법저항");
		break;
	case RGT_SKILL_UP:
		sprintf_s(temp, 32, "%s+%d", skill_string((skill_type)(value_ %100)), value_/100);
	}
	return temp;
}


const char* GetAtifactInfor(ring_type ring_, int value_)
{	
	static char temp[128];
	switch(ring_)
	{
	case RGT_STR:
		sprintf_s(temp,128,"힘이 수치만큼 증감한다.(%s%d)",value_<0?"":"+",value_);
		break;
	case RGT_DEX:
		sprintf_s(temp,128,"민첩이 수치만큼 증감한다.(%s%d)",value_<0?"":"+",value_);
		break;
	case RGT_INT:
		sprintf_s(temp,128,"지능이 수치만큼 증감한다.(%s%d)",value_<0?"":"+",value_);
		break;
	case RGT_HUNGRY:
		sprintf_s(temp,128,"파워가 빠른 속도로 소모된다.");
		break;
	case RGT_FULL:
		sprintf_s(temp,128,"파워가 천천히 소모된다.");
		break;
	case RGT_TELEPORT:
		sprintf_s(temp,128,"무작위로 공간이동을 한다.");
		break;
	case RGT_POISON_RESIS:
		sprintf_s(temp,128,"%s",value_>0?"독에 면역이 생긴다.":"독에 취약해진다.");
		break;
	case RGT_FIRE_RESIS:
		sprintf_s(temp,128,"화염저항이 증감한다.(%s)",(value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			)))))));
		break;
	case RGT_ICE_RESIS:
		sprintf_s(temp,128,"냉기저항이 증감한다.(%s)",(value_==3?"+++":
			(value_==2?"++":
			(value_==1?"+":
			(value_==-1?"-":
			(value_==-2?"--":
			(value_==-3?"---":"?"
			)))))));
		break;
	case RGT_SEE_INVISIBLE:
		sprintf_s(temp,128,"투명을 감지할 수 있다.");
		break;
	//case RGT_GRAZE:
	//	sprintf_s(temp,128,"그레이즈를 발동할 수 있다.");
	//	break;
	case RGT_LEVITATION:
		sprintf_s(temp,128,"비행을 발동할 수 있다.");
		break;
	case RGT_INVISIBLE:
		sprintf_s(temp,128,"투명을 발동할 수 있다.");
		break;
	case RGT_MANA:
		sprintf_s(temp,128,"영력의 최대치가 올라간다.");
		break;
	case RGT_MAGACIAN:
		sprintf_s(temp,128,"마법성공율이 올라간다.");
		break;
	case RGT_AC:
		sprintf_s(temp,128,"방어가 증감한다.(%s%d)",value_<0?"":"+",value_);
		break;
	case RGT_EV:
		sprintf_s(temp,128,"회피가 증감한다.(%s%d)",value_<0?"":"+",value_);
		break;
	case RGT_CONFUSE_RESIS:
		sprintf_s(temp,128,"혼란에 저항이 생긴다.");
		break;
	case RGT_ELEC_RESIS:
		sprintf_s(temp,128,"전기에 저항이 생긴다.");
		break;
	case RGT_MAGIC_RESIS:
		sprintf_s(temp,128,"마법 저항이 생긴다.(%d)",20+value_*20);
		break;
	case RGT_SKILL_UP:
		sprintf_s(temp, 128, "지정된 스킬레벨이 올라간다.(%s+%d)", skill_string((skill_type)(value_ % 100)), value_ / 100);
		break;

	}
	return temp;
}


bool effectartifact(ring_type kind, int value)
{
	switch(kind)
	{
	case RGT_STR:
		you.StatUpDown(value, STAT_STR);
		return true;
	case RGT_DEX:
		you.StatUpDown(value, STAT_DEX);
		return true;
	case RGT_INT:
		you.StatUpDown(value, STAT_INT);
		return true;
	case RGT_HUNGRY:
		you.ResistUpDown(value*-1,RST_POWER);
		return false;
	case RGT_FULL:
		you.ResistUpDown(value,RST_POWER);
		return false;
	case RGT_TELEPORT:
		you.teleport_curse += value;
		return true;		
	case RGT_POISON_RESIS:
		you.ResistUpDown(value,RST_POISON);
		return false;
	case RGT_FIRE_RESIS:
		you.ResistUpDown(value,RST_FIRE);
		return false;
	case RGT_ICE_RESIS:
		you.ResistUpDown(value,RST_ICE);
		return false;
	case RGT_SEE_INVISIBLE:
		you.ResistUpDown(value,RST_INVISIBLE);
		return false;
	/*case RGT_GRAZE:
		{	
			int temp = you.Ability(SKL_GRAZE_OFF,false,true); //그레이즈 해제를 삭제하고 수를 리턴
			temp += you.Ability(SKL_GRAZE,false,true); //그레이즈 발동도 해제하고 수를 리턴

			temp+=value;
			you.Ability(you.s_graze?SKL_GRAZE_OFF:SKL_GRAZE,false,temp<=0?true:false,temp);
			if(temp <= 0 && you.s_graze && !you.isGrazeAmulet())
			{
				you.s_graze=0; 
			}
			return true;
		}*/
	case RGT_LEVITATION:
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
	case RGT_INVISIBLE:
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
	case RGT_MANA:
		you.max_mp += 9*value;
		if(you.mp > you.max_mp)
			you.mp = you.max_mp;
		return true;
	case RGT_MAGACIAN:
		you.magician_bonus += value;
		return false;
	case RGT_AC:
		you.AcUpDown(0,value);
		return true;
	case RGT_EV:
		you.EvUpDown(0,value);
		return true;
	case RGT_CONFUSE_RESIS:
		you.ResistUpDown(value,RST_CONFUSE);
		return false;
	case RGT_ELEC_RESIS:
		you.ResistUpDown(value,RST_ELEC);
		break;
	case RGT_MAGIC_RESIS:
		you.MRUpDown((value>0?1:-1)*(20+abs(value)*20));
		break;
	case RGT_SKILL_UP:
	{
		int value_ = abs(value);
		you.BonusSkillUpDown(value_ % 100, (value>0?1:-1) *value_ / 100);

	}
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
		return RGT_CONFUSE_RESIS;
	case AMK_WING:
		return RGT_ELEC_RESIS;
	case AMK_KAPPA:
		return RGT_ICE_RESIS;
	case AMK_FIRE:
		return RGT_FIRE_RESIS;
	case AMK_MAID:
		return RGT_MAGIC_RESIS;
	case AMK_POISON:
		return RGT_POISON_RESIS;
	case AMK_AUTUMN:
		break;		
	}
	return -1;
}



void MakeArtifact(item* item_, int good_bad_)
{
	int num_ = 1+randA(good_bad_ +randA(3));
	deque<int> temp;
	for(int i=0; i<RGT_MAX_ATIFACT; i++)
	{
		if(item_->type >= ITM_ARMOR_BODY_FIRST && item_->type < ITM_ARMOR_BODY_LAST)
		{
			if(ArmourExceptopn((armour_kind)item_->value5) == i)
				continue;
		}
		if (isSprint() && 
			(i == RGT_TELEPORT || i == RGT_HUNGRY || i == RGT_FULL || i == RGT_LEVITATION)) {
			continue;;
		}

		temp.push_back(i);
	}
	rand_shuffle(temp.begin(),temp.end());
	for(int i = 0; i < num_ ; i++)
	{
		if(item_->value1 != temp[i] || item_->type != ITM_RING)
		{
			int gb_ = randA(3)?good_bad_:good_bad_*-1;
			item_->atifact_vector.push_back(atifact_infor(temp[i],GetAtifactValue((ring_type)temp[i],gb_)));
		}
		else
			num_++;
	}

	if(item_->type>=ITM_WEAPON_FIRST && item_->type<ITM_WEAPON_LAST)
	{
		item_->value4 = randA(9);
		item_->value4 += randA(3);
		item_->value4 += randA(2 + good_bad_)-4;
	}		
	if(item_->type>=ITM_ARMOR_FIRST && item_->type< ITM_ARMOR_LAST)
	{
		item_->value4 = randA(item_->value1);
		item_->value4 += randA(2);
		item_->value4 += randA(1+good_bad_)-2;
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
	item_->second_name.name = "아티펙트 ";
	item_->second_name.name_type = false;

}