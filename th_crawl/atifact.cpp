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
	case RGT_GRAZE:
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
	case RGT_GRAZE:
		sprintf_s(temp,32,"+그레이즈");
		break;
	case RGT_LEVITATION:
		sprintf_s(temp,32,"+부유");
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
	case RGT_GRAZE:
		sprintf_s(temp,128,"그레이즈를 발동할 수 있다.");
		break;
	case RGT_LEVITATION:
		sprintf_s(temp,128,"부유를 발동할 수 있다.");
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
	case RGT_GRAZE:
		{
			int temp = you.Ability(SKL_GRAZE_OFF,false,true);
			you.Ability(SKL_GRAZE,false,value<=0,value>0?(temp>0?temp+1:0):0);
			if(value<=0 && temp == 1 && you.s_graze)
			{
				you.s_graze=0; 
			}
			return true;
		}
	case RGT_LEVITATION:
		{
			int temp = you.Ability(SKL_LEVITATION_OFF,false,true);
			you.Ability(SKL_LEVITATION,false,value<=0,value>0?(temp>0?temp+1:0):0);
			if(value<=0 && temp == 1 && you.s_levitation)
			{
				you.s_levitation=0; 
			}
			return true;
		}
	case RGT_INVISIBLE:
		{
			int temp = you.Ability(SKL_INVISIBLE_OFF,false,true);
			you.Ability(SKL_INVISIBLE,false,value<=0,value>0?(temp>0?temp+1:0):0);
			if(value<=0 && temp == 1 && you.s_invisible)
			{
				you.s_invisible=0;
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
		you.EvUpDown(value);
		return true;
	case RGT_CONFUSE_RESIS:
		you.ResistUpDown(value,RST_CONFUSE);
		return false;
	case RGT_ELEC_RESIS:
		you.ResistUpDown(value,RST_ELEC);
		break;
	case RGT_MAGIC_RESIS:
		you.MRUpDown(20+value*20);
		break;
	}
	return false;
}



void MakeArtifact(item* item_, int good_bad_)
{
	int num_ = 1+randA(1+randA(3));
	deque<int> temp;
	for(int i=0; i<RGT_MAX; i++)
	{
		temp.push_back(i);
	}
	random_shuffle(temp.begin(),temp.end());
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
		item_->value4 = randA(9)+randA(3)+randA(3)-4;
		item_->value3 = randA(9)+randA(3)+randA(3)-4;
	}		
	if(item_->type>=ITM_ARMOR_FIRST && item_->type< ITM_ARMOR_LAST)
	{
		item_->value4 = randA(item_->value1)+randA(2)+randA(2)-2;
	}
}