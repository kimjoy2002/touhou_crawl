//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ring.cpp
//
// 내용: 링과 아뮬렛 정보들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "ring.h"
#include "skill_use.h"
#include "atifact.h"

LOCALIZATION_ENUM_KEY ring_uniden_string[RGT_MAX]=
{
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN1,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN2,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN3,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN4,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN5,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN6,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN7,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN8,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN9,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN10,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN11,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN12,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN13,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN14,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN15,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN16,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN17,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN18,
	LOC_SYSTEM_ITEM_JEWELRY_RING_UNIDEN19
};

LOCALIZATION_ENUM_KEY ring_iden_string[RGT_MAX]=
{	
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_STR,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_DEX,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_INT,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_HUNGRY,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_FULL,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_TELEPORT,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_POISON_RESIST,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_FIRE_RESIST,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_ICE_RESIST,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_SEE_INVISIBLE,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_LEVITATION,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_INVISIBLE,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_MANA,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_MAGACIAN,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_AC,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_EV,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_CONFUSE_RESIS,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_ELEC_RESIS,
	LOC_SYSTEM_ITEM_JEWELRY_RING_IDEN_MAGIC_RESIS
};



int isRingGotValue(ring_type ring_)
{
	return ( ring_ == RGT_STR || ring_ == RGT_DEX || ring_ == RGT_INT ||
		ring_ == RGT_AC || ring_ == RGT_EV
		);
}


ring_type goodbadring(int good_bad)
{
	if (good_bad == 1)
	{
		ring_type list_[6] = { RGT_POISON_RESIS,RGT_FIRE_RESIS,RGT_ICE_RESIS,RGT_ELEC_RESIS, RGT_MAGIC_RESIS, RGT_SEE_INVISIBLE };
		ring_type list2_[11] = { RGT_STR, RGT_DEX, RGT_INT,RGT_FULL/*,RGT_GRAZE*/,RGT_LEVITATION,RGT_INVISIBLE,RGT_MANA,RGT_MAGACIAN,RGT_AC, RGT_EV, RGT_CONFUSE_RESIS};
		if(randA(2)>0)
			return list_[randA(5)];
		else 
			return list2_[randA(10)];
	}
	else if(good_bad>=0)
	{
		ring_type list_[17] = {RGT_STR, RGT_DEX, RGT_INT, RGT_FULL,RGT_POISON_RESIS,RGT_FIRE_RESIS,RGT_ICE_RESIS,
		RGT_SEE_INVISIBLE/*,RGT_GRAZE*/,RGT_LEVITATION,RGT_INVISIBLE,RGT_MANA,RGT_MAGACIAN,RGT_AC, RGT_EV, RGT_CONFUSE_RESIS,
		RGT_ELEC_RESIS, RGT_MAGIC_RESIS
		};
		return list_[randA(16)];
	}
	else
	{
		ring_type list_[5] = {RGT_STR, RGT_DEX, RGT_INT, RGT_HUNGRY, RGT_TELEPORT};
		return list_[randA(4)];
	}
}
int isGoodRing(ring_type kind, int value)
{
	switch(kind)
	{
	case RGT_STR:
	case RGT_DEX:
	case RGT_INT:
		if(value>0)
			return 1;
		else
			return -1;
	case RGT_FULL:
	case RGT_POISON_RESIS:
	case RGT_FIRE_RESIS:
	case RGT_ICE_RESIS:
	case RGT_SEE_INVISIBLE:
	//case RGT_GRAZE:
	case RGT_LEVITATION:
	case RGT_INVISIBLE:
	case RGT_MANA:
	case RGT_MAGACIAN:
	case RGT_ELEC_RESIS:
	case RGT_MAGIC_RESIS:
	case RGT_SKILL_UP:
		return 1;
	case RGT_TELEPORT:
	case RGT_HUNGRY:
		return -1;
	}
	return 1;
}
int isPickableRIng(ring_type kind)
{
	switch(kind)
	{
	case RGT_STR:
	case RGT_DEX:
	case RGT_INT:
	case RGT_FIRE_RESIS:
	case RGT_ICE_RESIS:
	case RGT_MANA:
	case RGT_MAGACIAN:
	case RGT_ELEC_RESIS:
	case RGT_MAGIC_RESIS:
		return 1;
	case RGT_FULL:
	case RGT_POISON_RESIS:
	case RGT_SEE_INVISIBLE:
	//case RGT_GRAZE:
	case RGT_LEVITATION:
	case RGT_INVISIBLE:
	case RGT_TELEPORT:
	case RGT_HUNGRY:
		return -1;
	}
	return 1;
}


bool equipring(ring_type kind, int value)
{
	switch(kind)
	{
	case RGT_STR:
		if(value>0)
			printlog("당신은 강력해졌다.",true,false,false,CL_good);
		else
			printlog("당신은 약해졌다.",true,false,false,CL_small_danger);
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 2;
		break;
	case RGT_DEX:
		if(value>0)
			printlog("당신은 민첩해졌다.",true,false,false,CL_good);
		else
			printlog("당신은 둔해졌다.",true,false,false,CL_small_danger);
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 2;
		break;
	case RGT_INT:
		if(value>0)
			printlog("당신은 똑똑해졌다.",true,false,false,CL_good);
		else
			printlog("당신은 멍청해졌다.",true,false,false,CL_small_danger);
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 2;
		break;
	case RGT_HUNGRY:
	case RGT_FULL:
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 1;
		break;
	case RGT_TELEPORT:
		if(value>0)
			printlog("공간의 일그러짐을 느꼈다.",true,false,false,CL_normal);
		else
			printlog("주변의 공간이 안정되었다.",true,false,false,CL_normal);
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 2;
		break;		
	case RGT_POISON_RESIS:
	case RGT_FIRE_RESIS:
	case RGT_ICE_RESIS:
	case RGT_SEE_INVISIBLE:
	case RGT_ELEC_RESIS:
	case RGT_MAGIC_RESIS:
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 1;
		break;
	/*case RGT_GRAZE:
		{
			if(value>0)
				printlog("탄막을 피하는 감각이 날카로워짐을 느꼈다.",true,false,false,CL_normal);
			if(iden_list.ring_list[kind].iden == 0)
				iden_list.ring_list[kind].iden = 2;
			break;
		}*/
	case RGT_LEVITATION:
		{
			if(value>0)
				printlog("몸이 붕 뜨는 것을 느꼈다.",true,false,false,CL_normal);
			if(iden_list.ring_list[kind].iden == 0)
				iden_list.ring_list[kind].iden = 2;
			break;
		}
	case RGT_INVISIBLE:
		{
			if(value>0)
				printlog("반지에 의해 몸이 깜박거렸다.",true,false,false,CL_normal);
			if(iden_list.ring_list[kind].iden == 0)
				iden_list.ring_list[kind].iden = 2;
			break;
		}
	case RGT_MANA:
		if(value>0)
			printlog("영력이 넘쳐흐르기 시작했다.",true,false,false,CL_normal);
		else
			printlog("영력이 몸속에서 빠져나갔다.",true,false,false,CL_normal);
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 2;
		break;
	case RGT_MAGACIAN:
		if(value>0)
			printlog("당신은 마법 지식이 늘어난 것 같다.",true,false,false,CL_normal);
		else
			printlog("당신의 마법 지식은 빠져갔다.",true,false,false,CL_normal);
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 2;
		break;
	case RGT_AC:
		if(value>0)
			printlog("당신은 보호되고있다.",true,false,false,CL_good);
		else
			printlog("보호가 풀렸다.",true,false,false,CL_small_danger);
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 2;
		break;
	case RGT_EV:
		if(value>0)
			printlog("당신은 재빨라졌다.",true,false,false,CL_good);
		else
			printlog("당신은 둔해졌다.",true,false,false,CL_small_danger);
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 2;
		break;
	case RGT_CONFUSE_RESIS:
		if(iden_list.ring_list[kind].iden == 0)
			iden_list.ring_list[kind].iden = 1;
		break;
	}
	return effectartifact(kind,value);
}


bool unidenequipring(ring_type kind, int value)
{
	switch(kind)
	{
	case RGT_HUNGRY:
		you.UnidenResistUpDown(value*-1,RST_POWER);
		return false;
	case RGT_FULL:
		you.UnidenResistUpDown(value,RST_POWER);
		return false;
	case RGT_POISON_RESIS:
		you.UnidenResistUpDown(value,RST_POISON);
		return true;
	case RGT_FIRE_RESIS:
		you.UnidenResistUpDown(value,RST_FIRE);
		return true;
	case RGT_ICE_RESIS:
		you.UnidenResistUpDown(value,RST_ICE);
		return true;
	case RGT_SEE_INVISIBLE:
		you.UnidenResistUpDown(value,RST_INVISIBLE);
		return true;
	case RGT_ELEC_RESIS:
		you.UnidenResistUpDown(value,RST_ELEC);
		return true;
	}
	return false;
}
