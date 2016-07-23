//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: makechar.cpp
//
// 내용: 캐릭터 만들기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "enum.h"
#include "player.h"
#include "key.h"
#include "book.h"
#include "monster_texture.h"
#include "skill_use.h"
#include "environment.h"
#include "weapon.h"
#include "mon_infor.h"
#include "tribe.h"
#include "armour.h"
#include "evoke.h"




extern int armour_stat[5][3];

enum start_item_type
{
	SIT_SHORTBLADE=0,
	SIT_LONGBLADE1,
	SIT_LONGBLADE,
	SIT_MACE,
	SIT_AXE,
	SIT_SPEAR,
	SIT_GOHEY,
	SIT_SICKLE,
	SIT_BROOM,
	SIT_ROBE,
	SIT_KAPPA_ROBE,
	SIT_MIKO,
	SIT_MAID,
	SIT_CLOAK,
	SIT_ARMOUR_0,
	SIT_ARMOUR_1,
	SIT_SMALL_SHIELD,
	SIT_MIDDLE_SHIELD,
	SIT_FOOD,
	SIT_BOOK,
	SIT_THROWING_KNIFE,
	SIT_TANMAC,
	SIT_SPECIAL_TANMAC,
	SIT_MIGHT_POTION,
	SIT_RECHARGING_SCROLL,
	SIT_TEST_POTION,
	SIT_TEST_RING,
	SIT_TEST_SCROLL
};




void MakeStartItem(start_item_type select_, int num);


skill_type WeaponSelect(int num)
{
		SetText() = "원하시는 무기를 선택합니다.\n\n\n";
		SetText() += "a - 단검\n";
		SetText() += "b - 도끼\n";
		SetText() += "c - 둔기\n";
		SetText() += "d - 창\n";
		SetText() += "e - 장검\n";

		while(1)
		{
			int select = waitkeyinput(true);
			if(select>='a' && select<='e')
			{
				switch(select)
				{
				case 'a':
					MakeStartItem(SIT_SHORTBLADE,num);
					return SKT_SHORTBLADE;
				case 'b':
					MakeStartItem(SIT_AXE,num);
					return SKT_AXE;
				case 'c':
					MakeStartItem(SIT_MACE,num);
					return SKT_MACE;
				case 'd':
					MakeStartItem(SIT_SPEAR,num);
					return SKT_SPEAR;
				case 'e':
					MakeStartItem(SIT_LONGBLADE1,num);
					return SKT_LONGBLADE;
				}
				break;
			}
		}
		return SKT_ERROR;
}


god_type FanaticSelect()
{
		SetText() = "누구의 광신도가 될건가?\n\n\n";
		SetText() += "a - 텐시\n";
		SetText() += "b - 유카리\n";

		while(1)
		{
			int select = waitkeyinput(true);
			if(select>='a' && select<='b')
			{
				switch(select)
				{
				case 'a':
					return GT_TENSI;
				case 'b':
					return GT_YUKARI;
				}
				break;
			}
		}
		return GT_TENSI;
}



void MakeStartItem(start_item_type select_, int num)
{
	item_infor t;
	item *it;
	switch(select_)
	{
	case SIT_SHORTBLADE:
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_WEAPON_SHORTBLADE,&img_item_weapon_dagger,1,false,false,4,7,0,0,0,0,10,5,false,name_infor("대거",false),name_infor("",true),2.0f,50));
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_SHORTBLADE, 0, &t, 5));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equip('a'+num,ET_WEAPON,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_LONGBLADE1:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_LONGBLADE, 0, &t, 5));	
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equip('a'+num,ET_WEAPON,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_LONGBLADE:
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_WEAPON_LONGBLADE,&img_item_weapon_katana,1,false,false,1,9,0,0,0,0,13,7,false,name_infor("도검",true),name_infor("",true),4.0f,100));
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_LONGBLADE, 0, &t, 15));	
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equip('a'+num,ET_WEAPON,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_MACE:
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_WEAPON_MACE,&img_item_weapon_gohey,1,false,false,4,7,0,0,0,0,13,7,false,name_infor("고헤이",false),name_infor("",true),3.0f,60));
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_MACE, 0, &t, 5));	
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equip('a'+num,ET_WEAPON,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_AXE:
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_WEAPON_AXE,&img_item_weapon_handaxe,1,false,false,2,8,0,0,0,0,13,7,false,name_infor("손도끼",false),name_infor("",true),3.0f,60));
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_AXE, 0, &t, 5));	
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equip('a'+num,ET_WEAPON,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_SPEAR:
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_WEAPON_SPEAR,&img_item_weapon_spear,1,false,false,2,8,0,0,0,0,13,7,false,name_infor("창",true),name_infor("",true),4.0f,70));
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_SPEAR, 0, &t, 5));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equip('a'+num,ET_WEAPON,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_GOHEY:
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_WEAPON_MACE,&img_item_weapon_gohey,1,false,false,4,7,1,1,0,0,13,7,false,name_infor("고헤이",false),name_infor("",true),3.0f,60));
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_MACE, 0, &t, 5));	
		//it->value3 = 1;
		it->value4 = 1;
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equip('a'+num,ET_WEAPON,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_SICKLE:
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_WEAPON_SPEAR,&img_item_weapon_spear,1,false,false,2,8,1,1,0,0,13,7,false,name_infor("창",true),name_infor("",true),4.0f,70));
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_SPEAR, 0, &t, 15));	
		//it->value3 = 2;
		it->value4 = 3;
		it->curse = true;
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equip('a'+num,ET_WEAPON,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_BROOM:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_MACE, 0, &t, 15));	
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equip('a'+num,ET_WEAPON,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_ROBE:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_NORMAL));	
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_ARMOR_BODY_ARMOUR_0,&img_item_armor_robe,1,false,false,armour_stat[0][0],armour_stat[0][1],armour_stat[0][2],0,0,0,0,0,false,name_infor("무녀복",true),name_infor("",true),6.0f,40));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equiparmor('a'+num,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_KAPPA_ROBE:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_KAPPA));	
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_ARMOR_BODY_ARMOUR_0,&img_item_armor_robe,1,false,false,armour_stat[0][0],armour_stat[0][1],armour_stat[0][2],0,0,0,0,0,false,name_infor("무녀복",true),name_infor("",true),6.0f,40));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equiparmor('a'+num,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_MIKO:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_MIKO));	
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_ARMOR_BODY_ARMOUR_0,&img_item_armor_robe,1,false,false,armour_stat[0][0],armour_stat[0][1],armour_stat[0][2],0,0,0,0,0,false,name_infor("무녀복",true),name_infor("",true),6.0f,40));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equiparmor('a'+num,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_MAID:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_BODY_ARMOUR_0, 0, &t, AMK_MAID));	
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_ARMOR_BODY_ARMOUR_0,&img_item_armor_robe,1,false,false,armour_stat[0][0],armour_stat[0][1],armour_stat[0][2],0,0,0,0,0,false,name_infor("무녀복",true),name_infor("",true),6.0f,40));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equiparmor('a'+num,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_CLOAK:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_CLOAK, 0, &t, -1));	
		it->value4 = 0;
		it->curse = false;
		it->Identify();
		you.additem(it,false);
		you.equip('a'+num,ET_CLOAK,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_ARMOUR_0:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_BODY_ARMOUR_1, 0, &t, AMK_NORMAL));	
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_ARMOR_BODY_ARMOUR_0,&img_item_armor_armour_0,1,false,false,armour_stat[1][0],armour_stat[1][1],armour_stat[1][2],0,0,0,0,0,false,name_infor("경갑옷",true),name_infor("",true),6.0f,40));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equiparmor('a'+num,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_ARMOUR_1:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_BODY_ARMOUR_2, 0, &t, AMK_NORMAL));	
		//it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_ARMOR_BODY_ARMOUR_1,&img_item_armor_armour_1,1,false,false,armour_stat[2][0],armour_stat[2][1],armour_stat[2][2],0,0,0,0,0,false,name_infor("중간 중갑옷",true),name_infor("",true),6.0f,40));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equiparmor('a'+num,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_SMALL_SHIELD:
		it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_ARMOR_SHIELD,&img_item_weapon_roundshield,1,false,false,3,-1,0,0,0,0,0,0,false,name_infor("나무방패",false),name_infor("",true),3.0f,30));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equiparmor('a'+num,false);
		env[current_level].DeleteItem(it);	
		break;	
	case SIT_MIDDLE_SHIELD:
		it = env[current_level].MakeItem(you.position,CustomItem(&t,ITM_ARMOR_SHIELD,&img_item_weapon_shield,1,false,false,7,-3,0,0,0,0,0,0,false,name_infor("철방패",false),name_infor("",true),5.0f,100));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		you.equiparmor('a'+num,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_FOOD:	
		it = env[current_level].MakeItem(you.position,makeitem(ITM_FOOD, 0, &t, 0));
		(*it).identify = true;
		(*it).identify_curse = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_BOOK:
		{
			int book_ = rand_int(BOOK_FIRST,BOOK_SHOCK);
			switch(you.job)
			{
			case JOB_WIZARD:
				book_ = BOOK_WIZARD_BASE;
				break;
			case JOB_FIRE_WIZARD:
				book_ = BOOK_FIRE_BASE;
				break;
			case JOB_COLD_WIZARD:
				book_ = BOOK_COLD_BASE;
				break;
			case JOB_EARTH_WIZARD:
				book_ = BOOK_EARTH_BASE;
				break;
			case JOB_AIR_WIZARD:
				book_ = BOOK_AIR_BASE;
				break;
			case JOB_SUMMON_WIZARD:
				book_ = BOOK_SUMMON_BASE;
				break;
			case JOB_CRUSADER:
				book_ = BOOK_BRAND_BASE;
				break;
			case JOB_PSYCHOLOGIST:
				book_ = BOOK_PSYCHOLOGIST_BASE;
				break;
			case JOB_ALCHEMIST:
				book_ = BOOK_ALCHMIST_BASE;
				break;
			case JOB_MADE:
				book_ = BOOK_MAID_BASE;
				break;
			default:
				break;
			}
			it = env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, book_));
			(*it).identify = true;
			(*it).identify_curse = true;
			you.additem(it,false);
			env[current_level].DeleteItem(it);	
		}
		break;
	case SIT_THROWING_KNIFE:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_SHORTBLADE, 0, &t, 15));
		//it->value3 = 2;
		it->value4 = 2;
		it->identify = true;
		it->identify_curse = true;
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_TANMAC:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_THROW_TANMAC, 0, &t, TMT_BILL));
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_SPECIAL_TANMAC:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_THROW_TANMAC, 0, &t, TMT_POISON_NEEDLE));
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_MIGHT_POTION:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_MIGHT));
		it->Identify();
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_MIGHT));
		it->Identify();
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_RECHARGING_SCROLL:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SPELL, 0, &t, SPC_V_ICE));
		it->value1 = 9;
		it->Identify();
		you.additem(it,false);
		env[current_level].DeleteItem(it);		
		break;
	case SIT_TEST_POTION:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_ALCOHOL));
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_ALCOHOL));
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		break;
	case SIT_TEST_RING:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_RING,1,&t,RGT_GRAZE));		
		//it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_BODY_ARMOUR_0,1,&t));	
		//MakeArtifact(it,1);
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		break;
	case SIT_TEST_SCROLL:
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_ENCHANT_ARMOUR));
		you.additem(it,false);
		env[current_level].DeleteItem(it);
		it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_ENCHANT_ARMOUR));
		you.additem(it,false);
		env[current_level].DeleteItem(it);	
		break;
	}
}





void SetJob(job_type select_, string name_)
{
	int nse =  ceil(need_skill_exp(0,AptCal(you.skill[SKT_SPELLCASTING].aptit))/10.0f); //need_spellcast_exp;
	switch(select_)
	{	
	case JOB_WARRIOR:
		you.max_hp+=2;
		you.StatUpDown(5,STAT_STR);
		you.StatUpDown(-6,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		if(name_.compare("모미지")) //모미지는 특수한 시작
		{
			you.GiveSkillExp(WeaponSelect(0),60,false);
			if(!you.GetProperty(TPT_SIZE))
			{
				MakeStartItem(SIT_ARMOUR_1,1);
				MakeStartItem(SIT_MIDDLE_SHIELD,2);		
				//MakeStartItem(SIT_TEST_POTION,3);	

			}
			else
			{
				MakeStartItem(SIT_ARMOUR_0,1);
				MakeStartItem(SIT_CLOAK,2);
				MakeStartItem(SIT_MIDDLE_SHIELD,3);	
			}
		}
		else
		{
			MakeStartItem(SIT_LONGBLADE,0);
			you.GiveSkillExp(SKT_LONGBLADE,60,false);
			MakeStartItem(SIT_ARMOUR_1,1);
			MakeStartItem(SIT_SMALL_SHIELD,2);

		}
		you.GiveSkillExp(SKT_FIGHT,30,false);
		you.GiveSkillExp(SKT_ARMOUR,70,false);
		you.GiveSkillExp(SKT_SHIELD,60,false);
		break;
	case JOB_WIZARD:
		you.max_hp-=2;
		you.max_mp+=5;
		you.StatUpDown(6,STAT_INT);
		you.StatUpDown(-6,STAT_STR);
		MakeStartItem(SIT_ROBE,0);
		if(name_.compare("마리사")) //마리사는 이 책을 얻지 않는다.
			MakeStartItem(SIT_BOOK,1);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,60),false);
		you.GiveSkillExp(SKT_CONJURE,20,false);
		you.GiveSkillExp(SKT_TRANS,20,false);
			you.Memorize(SPL_MAGIC_TANMAC,true);
		break;
	case JOB_SHAMAN:
		you.max_hp+=1;
		you.max_mp+=1;
		you.StatUpDown(1,STAT_STR);
		you.StatUpDown(-2,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		MakeStartItem(SIT_GOHEY,0);
		MakeStartItem(SIT_MIKO,1);
		you.GiveSkillExp(SKT_MACE,120,false);
		you.GiveSkillExp(SKT_FIGHT,60,false);
		you.GiveSkillExp(SKT_DODGE,50,false);
		if(name_.compare("사나에") == 0) //레이무는 믿지않는다.
			you.Belief(GT_SUWAKO,35,false);
		else if(name_.compare("레이무")) //레이무는 믿지않는다.
			you.Belief(GT_KANAKO,35,false);
		break;
	case JOB_GLADIATOR:
		you.max_hp+=2;
		you.StatUpDown(2,STAT_STR);
		you.StatUpDown(-4,STAT_INT);
		you.StatUpDown(2,STAT_DEX);
		you.GiveSkillExp(WeaponSelect(0),60,false);
		MakeStartItem(SIT_ARMOUR_0,1);
		MakeStartItem(SIT_SMALL_SHIELD,2);
		MakeStartItem(SIT_TANMAC,3);
		you.GiveSkillExp(SKT_FIGHT,30,false);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_TANMAC,30,false);
		you.GiveSkillExp(SKT_SHIELD,30,false);
		break;
	case JOB_MONK:
		you.max_hp+=2;
		you.StatUpDown(-1,STAT_STR);
		you.StatUpDown(-2,STAT_INT);
		you.StatUpDown(3,STAT_DEX);
		MakeStartItem(SIT_ROBE,0);
		you.GiveSkillExp(SKT_FIGHT,60,false);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_UNWEAPON,90,false);
		break;
	case JOB_CRUSADER: //강화전사인지, 요술전사인지 선택하게하기
		you.max_hp+=1;
		you.max_mp+=1;
		you.GiveSkillExp(WeaponSelect(0),30,false);
		MakeStartItem(SIT_ARMOUR_0,1);
		MakeStartItem(SIT_BOOK,2);
		you.GiveSkillExp(SKT_FIGHT,30,false);
		you.GiveSkillExp(SKT_DODGE,20,false);
		you.GiveSkillExp(SKT_ARMOUR,20,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,30),false);
		you.GiveSkillExp(SKT_ALCHEMY,30,false);
		you.GiveSkillExp(SKT_AIR,30,false);
		you.Memorize(SPL_VEILING,true);
		break;
	case JOB_BERSERKER:
		you.max_hp+=2;
		you.StatUpDown(5,STAT_STR);
		you.StatUpDown(-7,STAT_INT);
		you.StatUpDown(2,STAT_DEX);
		MakeStartItem(SIT_AXE,0);
		MakeStartItem(SIT_ROBE,1);
		MakeStartItem(SIT_MIGHT_POTION,2);	
		you.GiveSkillExp(SKT_FIGHT,60,false);
		you.GiveSkillExp(SKT_AXE,60,false);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_ARMOUR,30,false);	
		break;
	case JOB_FIRE_WIZARD:
		you.max_hp-=1;
		you.max_mp+=3;
		you.StatUpDown(-5,STAT_STR);
		you.StatUpDown(4,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		MakeStartItem(SIT_ROBE,0);
		MakeStartItem(SIT_BOOK,1);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,20),false);
		you.GiveSkillExp(SKT_CONJURE,20,false);
		you.GiveSkillExp(SKT_FIRE,60,false);
		you.Memorize(SPL_BURN,true);
		break;
	case JOB_COLD_WIZARD:
		you.max_hp-=1;
		you.max_mp+=3;
		you.StatUpDown(-5,STAT_STR);
		you.StatUpDown(4,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		MakeStartItem(SIT_ROBE,0);
		MakeStartItem(SIT_BOOK,1);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,20),false);
		you.GiveSkillExp(SKT_CONJURE,20,false);
		you.GiveSkillExp(SKT_COLD,60,false);
		you.Memorize(SPL_FROZEN,true);
		break;
	case JOB_EARTH_WIZARD:
		you.max_hp-=1;
		you.max_mp+=3;
		you.StatUpDown(-5,STAT_STR);
		you.StatUpDown(4,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		MakeStartItem(SIT_ROBE,0);
		MakeStartItem(SIT_BOOK,1);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,20),false);
		you.GiveSkillExp(SKT_ALCHEMY,20,false);
		you.GiveSkillExp(SKT_EARTH,60,false);
		you.Memorize(SPL_STONE_PUNCH,true);
		break;
	case JOB_AIR_WIZARD:
		you.max_mp+=2;
		you.StatUpDown(-3,STAT_STR);
		you.StatUpDown(2,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		MakeStartItem(SIT_GOHEY,0);
		MakeStartItem(SIT_ROBE,1);
		MakeStartItem(SIT_BOOK,2);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,20),false);
		you.GiveSkillExp(SKT_AIR,80,false);
		you.Memorize(SPL_SHOCK,true);
		break;/*
	case JOB_WATER_WIZARD:
		you.max_hp-=1;
		you.max_mp+=3;
		you.StatUpDown(-5,STAT_STR);
		you.StatUpDown(4,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		MakeStartItem(SIT_ROBE,0);
		MakeStartItem(SIT_FOOD,1);
		MakeStartItem(SIT_BOOK,2);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,20),false);
		you.GiveSkillExp(SKT_COLD,120,false);
		break;*/
	case JOB_SUMMON_WIZARD:
		you.max_hp-=1;
		you.max_mp+=3;
		you.StatUpDown(-5,STAT_STR);
		you.StatUpDown(4,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		MakeStartItem(SIT_ROBE,0);
		MakeStartItem(SIT_BOOK,1);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,20),false);
		you.GiveSkillExp(SKT_SUMMON,80,false);
		you.Memorize(SPL_SUMMON_MOOK,true);		
		break;
	//case JOB_POISON_WIZARD:
	//	you.max_hp-=1;
	//	you.max_mp+=3;
	//	you.StatUpDown(-5,STAT_STR);
	//	you.StatUpDown(4,STAT_INT);
	//	you.StatUpDown(1,STAT_DEX);
	//	MakeStartItem(SIT_ROBE,0);
	//	MakeStartItem(SIT_FOOD,1);
	//	MakeStartItem(SIT_BOOK,2);
	//	you.GiveSkillExp(SKT_DODGE,30,false);
	//	you.GiveSkillExp(SKT_STEALTH,30,false);
	//	you.GiveSkillExp(SKT_SPELLCASTING,max(nse,20),false);
	//	you.GiveSkillExp(SKT_ALCHEMY,60,false);
	//	you.GiveSkillExp(SKT_CONJURE,60,false);
	//	you.Memorize(SPL_STING,true);
	//	break;
	//case JOB_ELECTRIC_WIZARD:
	//	you.max_hp-=1;
	//	you.max_mp+=3;
	//	you.StatUpDown(-5,STAT_STR);
	//	you.StatUpDown(4,STAT_INT);
	//	you.StatUpDown(1,STAT_DEX);
	//	MakeStartItem(SIT_ROBE,0);
	//	MakeStartItem(SIT_FOOD,1);
	//	MakeStartItem(SIT_BOOK,2);
	//	you.GiveSkillExp(SKT_DODGE,30,false);
	//	you.GiveSkillExp(SKT_STEALTH,30,false);
	//	you.GiveSkillExp(SKT_SPELLCASTING,max(nse,20),false);
	//	you.GiveSkillExp(SKT_CONJURE,20,false);
	//	you.GiveSkillExp(SKT_AIR,60,false);
	//	you.Memorize(SPL_SHOCK,true);
	//	break;
	case JOB_ALCHEMIST:
		you.max_hp+=2;
		you.max_mp+=1;
		you.StatUpDown(-1,STAT_STR);
		you.StatUpDown(1,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		MakeStartItem(SIT_ROBE,0);
		MakeStartItem(SIT_BOOK,1);
		you.GiveSkillExp(SKT_FIGHT,30,false);
		you.GiveSkillExp(SKT_UNWEAPON,90,false);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,30),false);
		you.GiveSkillExp(SKT_ALCHEMY,30,false);
		you.Memorize(SPL_STONE_PUNCH,true);		
		break;
	case JOB_PSYCHOLOGIST:
		you.max_hp-=1;
		you.max_mp+=3;
		you.StatUpDown(-5,STAT_STR);
		you.StatUpDown(4,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		MakeStartItem(SIT_SHORTBLADE,0);
		MakeStartItem(SIT_ROBE,1);
		MakeStartItem(SIT_BOOK,2);
		you.GiveSkillExp(SKT_DODGE,60,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_SPELLCASTING,max(nse,30),false);
		you.GiveSkillExp(SKT_MENTAL,80,false);
		you.Memorize(SPL_HYPNOSIS,true);		
		break;
	case JOB_REAPER:
		you.max_hp+=1;
		you.max_hp+=1;
		you.StatUpDown(2,STAT_STR);
		you.StatUpDown(4,STAT_INT);
		you.StatUpDown(2,STAT_DEX);
		MakeStartItem(SIT_SICKLE,0);
		MakeStartItem(SIT_ROBE,1);
		you.GiveSkillExp(SKT_SPEAR,140,false);
		you.GiveSkillExp(SKT_FIGHT,30,false);
		you.GiveSkillExp(SKT_DODGE,30,false);
		break;
	case JOB_FANATIC:
		you.max_hp+=1;
		you.max_hp+=1;
		you.StatUpDown(2,STAT_STR);
		you.StatUpDown(-4,STAT_INT);
		you.StatUpDown(2,STAT_DEX);
		you.GiveSkillExp(WeaponSelect(0),60,false);
		MakeStartItem(SIT_ARMOUR_0,1);
		you.Belief(FanaticSelect(),35,false);
		you.GiveSkillExp(SKT_FIGHT,90,false);
		you.GiveSkillExp(SKT_ARMOUR,30,false);
		you.GiveSkillExp(SKT_DODGE,30,false);
		break;
	case JOB_ASSASSIN:
		you.max_hp+=2;
		you.StatUpDown(-2,STAT_STR);
		you.StatUpDown(-2,STAT_INT);
		you.StatUpDown(4,STAT_DEX);
		MakeStartItem(SIT_SHORTBLADE,0);
		MakeStartItem(SIT_ROBE,1);
		MakeStartItem(SIT_SPECIAL_TANMAC,2);
		you.GiveSkillExp(SKT_SHORTBLADE,45,false);
		you.GiveSkillExp(SKT_FIGHT,30,false);
		you.GiveSkillExp(SKT_TANMAC,30,false);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_STEALTH,75,false);
		break;
	case JOB_FARMER:
		you.max_hp+=2;
		you.StatUpDown(3,STAT_STR);
		you.StatUpDown(-4,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		you.GiveSkillExp(WeaponSelect(0),60,false);
		MakeStartItem(SIT_ROBE,1);
		MakeStartItem(SIT_FOOD,2);
		MakeStartItem(SIT_FOOD,2);
		MakeStartItem(SIT_FOOD,2);
		you.Belief(GT_MINORIKO,35,false);
		you.GiveSkillExp(SKT_FIGHT,60,false);
		you.GiveSkillExp(SKT_DODGE,40,false);
		break;
	case JOB_MADE:
		you.max_hp+=2;		
		MakeStartItem(SIT_BROOM,0);
		MakeStartItem(SIT_MAID,1);
		MakeStartItem(SIT_BOOK,2);
		MakeStartItem(SIT_THROWING_KNIFE,3);
		MakeStartItem(SIT_THROWING_KNIFE,4);
		MakeStartItem(SIT_THROWING_KNIFE,5);
		MakeStartItem(SIT_THROWING_KNIFE,6);
		you.GiveSkillExp(SKT_FIGHT,30,false);
		you.GiveSkillExp(SKT_MACE,30,false);
		you.GiveSkillExp(SKT_DODGE,30,false);
		you.GiveSkillExp(SKT_TANMAC,60,false);
		you.GiveSkillExp(SKT_STEALTH,30,false);
		you.GiveSkillExp(SKT_TRANS,30,false);
		break;
	case JOB_ENGINEER:
		you.max_hp+=2;
		you.StatUpDown(2,STAT_STR);
		you.StatUpDown(-3,STAT_INT);
		you.StatUpDown(1,STAT_DEX);
		
		if(name_.compare("니토리"))
		{			
			you.GiveSkillExp(WeaponSelect(0),60,false);
			MakeStartItem(SIT_ROBE,1);
		}
		else
		{
			MakeStartItem(SIT_MACE,0);
			you.GiveSkillExp(SKT_MACE,60,false);
			MakeStartItem(SIT_KAPPA_ROBE,1);			
		}

		MakeStartItem(SIT_RECHARGING_SCROLL,2);
		you.GiveSkillExp(SKT_FIGHT,40,false);
		you.GiveSkillExp(SKT_DODGE,40,false);
		you.GiveSkillExp(SKT_EVOCATE,60,false);
		break;
	case JOB_MISSING:
		you.max_mp+=1;
		MakeStartItem(SIT_AXE,0);
		MakeStartItem(SIT_ROBE,1);
		MakeStartItem(SIT_FOOD,2);
		//?
		break;
	}
	you.skill_exper = 25;
	you.hp=you.max_hp;
	you.prev_hp[0] = you.hp;
	you.prev_hp[1] = you.hp;
	you.mp=you.max_mp;
	you.prev_mp[0] = you.mp;
	you.prev_mp[1] = you.mp;
}



void TouhouPlayerble(const string name_, bool aptit_)
{
	item_infor t;
	item *it;
	if(name_.compare("레이무")==0)
	{	
		if(aptit_)
		{
			you.skill[SKT_TANMAC].aptit +=3;
			you.skill[SKT_DODGE].aptit +=3;
		}
		else
		{	
			it = env[current_level].MakeItem(you.position,makeitem(ITM_ARMOR_HEAD, 0, &t, -1));	
			it->value4 = 0;
			it->curse = false;
			it->Identify();
			you.additem(it,false);
			you.equip('a'+2,ET_HELMET,false);
			env[current_level].DeleteItem(it);
			for(int i = 0; i <4; i++)
			{
				it = env[current_level].MakeItem(you.position,makeitem(ITM_THROW_TANMAC, 0, &t, TMT_AMULET));
				you.additem(it,false);
				env[current_level].DeleteItem(it);	
			}
			you.skill[SKT_TANMAC].onoff = true;

			

			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
		}
	}

	else if(name_.compare("마리사")==0)
	{
		if(aptit_)
		{
			you.skill[SKT_SPELLCASTING].aptit +=2;
			you.skill[SKT_CONJURE].aptit +=3;
			you.skill[SKT_DODGE].aptit +=1;
		}
		else
		{			
			it = env[current_level].MakeItem(you.position,makeitem(ITM_WEAPON_MACE, 0, &t, 15));	
			(*it).identify = true;
			(*it).identify_curse = true;
			//it->value3 = 2;
			it->Enchant(ET_WEAPON, 2);
			you.additem(it,false);
			you.equip('a'+1,ET_WEAPON,false);
			env[current_level].DeleteItem(it);

			it = env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, BOOK_CONJURE));
			(*it).identify = true;
			(*it).identify_curse = true;
			you.additem(it,false);
			env[current_level].DeleteItem(it);	
			
			it = env[current_level].MakeItem(you.position,makeitem(ITM_RING,1,&t,RGT_MANA));	
			it->Identify();
			you.additem(it,false);
			you.equip('a'+3,ET_LEFT,false);
			env[current_level].DeleteItem(it);

			
			you.skill[SKT_TRANS].onoff = false;


			you.mp = you.max_mp;

			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);

			
			//you.Memorize(SPL_CONTROLED_BLINK,true);		
		}
	}
	else if(name_.compare("사나에")==0)
	{
		if(aptit_)
		{
			you.skill[SKT_FIGHT].aptit +=2;
			you.skill[SKT_DODGE].aptit +=1;
			you.skill[SKT_EVOCATE].aptit +=3;
		}
		else
		{		
			it = env[current_level].MakeItem(you.position,makeitem(ITM_SPELL, 0, &t, SPC_V_EARTH));
			it->value1 = 9;
			it->Identify();
			you.additem(it,false);
			env[current_level].DeleteItem(it);
			it = env[current_level].MakeItem(you.position,makeitem(ITM_SPELL, 0, &t, SPC_V_AIR));
			it->value1 = 9;
			it->Identify();
			you.additem(it,false);
			env[current_level].DeleteItem(it);	
			you.skill[SKT_EVOCATE].onoff = true;


			
			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
		}

	}
	else if(name_.compare("모미지")==0)
	{
		if(aptit_)
		{
			you.skill[SKT_LONGBLADE].aptit +=1;
		}
		else
		{
			if(you.equipment[ET_WEAPON]){
				//you.equipment[ET_WEAPON]->value3 = 2;
				you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, 2);
			}
			if(you.equipment[ET_ARMOR]){
				you.equipment[ET_ARMOR]->Enchant(ET_ARMOR, 2);
			}
			if(you.equipment[ET_SHIELD]){
				you.equipment[ET_SHIELD]->Enchant(ET_SHIELD, 2);
			}
			it = env[current_level].MakeItem(you.position,makeitem(ITM_RING,1,&t,RGT_SEE_INVISIBLE));	
			it->Identify();
			you.additem(it,false);
			you.equip('a'+3,ET_LEFT,false);
			env[current_level].DeleteItem(it);

			for(int i = 0; i < 2; i++)
			{				
				it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_HEAL_WOUND));
				it->Identify();
				you.additem(it,false);
				env[current_level].DeleteItem(it);	
				it = env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t, PT_MIGHT));
				it->Identify();
				you.additem(it,false);
				env[current_level].DeleteItem(it);				
			}
			set_exist_named(MON_MOMIZI);	


			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
			
		}
	}
	else if(name_.compare("코이시")==0)
	{
		if(aptit_)
		{
			you.skill[SKT_SHORTBLADE].aptit +=2;
			you.skill[SKT_MENTAL].aptit +=2;
		}
		else
		{		

			
			you.SetProperty(TPT_INVISIBLE,1);
			you.SetProperty(TPT_POWER_SAVE,1);

			you.skill[SKT_TANMAC].onoff = false;
			set_exist_named(MON_KOISHI);	
			
			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
		}

	}
	else if(name_.compare("모코우")==0)
	{
		if(aptit_)
		{
			you.skill[SKT_FIGHT].aptit +=2;
			you.skill[SKT_FIRE].aptit +=2;
		}
		else
		{					
			you.SetProperty(TPT_HP,2);
			you.SetProperty(TPT_9_LIFE,1);
			you.SetProperty(TPT_18_LIFE,1);
			set_exist_named(MON_MOKOU);	


			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
		}

	}
	else if(name_.compare("니토리")==0)
	{
		if(aptit_)
		{
			you.skill[SKT_MACE].aptit +=2;
			you.skill[SKT_EVOCATE].aptit +=1;
		}
		else
		{					
			it = env[current_level].MakeItem(you.position,makeitem(ITM_MISCELLANEOUS, 0, &t, EVK_PAGODA));
			you.additem(it,false);
			env[current_level].DeleteItem(it);
			set_exist_named(MON_NITORI);	


			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
			you.GetExp(you.GetNeedExp(you.level-1) - you.exper,false);
		}

	}
}