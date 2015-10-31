//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: book.cpp
//
// 내용: 책 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "book.h"
#include "skill_use.h"

book_infor static_book_list[BOOK_LAST]=
{
	book_infor("초보 화염술사의 마법책",true,BOOK_FIRE_BASE,300,SPL_BURN,SPL_FLAME,SPL_FIRE_WALL,SPL_FIRE_BALL,SPL_FIRE_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 냉기술사의 마법책",true,BOOK_COLD_BASE,300,SPL_FROZEN,SPL_FROST,SPL_FREEZE,SPL_ICE_CLOUD,SPL_ICE_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 독술사의 마법책",true,BOOK_POISON_BASE,300,SPL_STING,SPL_CURE_POISON,SPL_POISON_SKIN,SPL_CONFUSE_CLOUD,SPL_VENOM_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 마법사의 마법책",true,BOOK_WIZARD_BASE,300,SPL_MAGIC_TANMAC,SPL_BLINK,SPL_DIAMOND_HARDNESS,SPL_SUMMON_OPTION,SPL_CONFUSE_CLOUD,SPL_FIRE_WALL,SPL_NONE,SPL_NONE),
	book_infor("초보 대지술사의 마법책",true,BOOK_EARTH_BASE,30,SPL_STONE_PUNCH,SPL_STONE_ARROW,SPL_STONE_TRAP,SPL_STONE_UPLIFT,SPL_KANAME_DRILL,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 대기술사의 마법책",true,BOOK_AIR_BASE,300,SPL_SHOCK,SPL_LEVITATION, SPL_TWIST,SPL_DISCHARGE,SPL_CHAIN_LIGHTNING,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 소환술사의 마법책",true,BOOK_SUMMON_BASE,300,SPL_SUMMON_MOOK,SPL_SUMMON_OPTION,SPL_SUMMON_BIRD,SPL_SUMMON_GOLEM,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 연금술사의 마법책",true,BOOK_ALCHMIST_BASE,300,SPL_STING,SPL_SUMMON_GOLEM,SPL_VENOM_BOLT,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 심리학자의 마법책",true,BOOK_PSYCHOLOGIST_BASE,300,SPL_HYPNOSIS, SPL_MIND_BENDING, SPL_MUTE, SPL_SELF_INJURY, SPL_CHARM,SPL_NONE ,SPL_NONE,SPL_NONE),
	book_infor("초보 마법전사의 마법책",true,BOOK_BRAND_BASE,400,SPL_VEILING,SPL_DIAMOND_HARDNESS,SPL_POISON_SKIN,SPL_SILENCE,SPL_HASTE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("메이드의 기본소양",true,BOOK_MAID_BASE,400,SPL_BLINK,SPL_SUMMON_OPTION,SPL_KNIFE_COLLECT,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("전격의 마법책",true,BOOK_SHOCK,500,SPL_SHOCK,SPL_LEVITATION,SPL_DISCHARGE,SPL_CHAIN_LIGHTNING,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("원소 연습의 마법책",true,BOOK_PRACTICE,450,SPL_BURN,SPL_FROZEN,SPL_VEILING,SPL_STONE_PUNCH,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("보조의 마법책",true,BOOK_SUB,450,SPL_DIAMOND_HARDNESS,SPL_BLINK,SPL_MIND_BENDING,SPL_SUMMON_BIRD,SPL_STONE_TRAP,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("암살자의 마법책",true,BOOK_STALKING,600,SPL_STING,SPL_CONFUSE,SPL_CONFUSE_CLOUD,SPL_INVISIBLE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("구름의 마법책",true,BOOK_CLOUD,700,SPL_TWIST,SPL_FIRE_WALL,SPL_CONFUSE_CLOUD,SPL_POISON_CLOUD,SPL_ICE_CLOUD,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("파괴의 마법책",true,BOOK_CONJURE,700,SPL_MAGIC_TANMAC,SPL_SUMMON_OPTION,SPL_LASER,SPL_FIRE_BOLT,SPL_ICE_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("매혹의 마법책",true,BOOK_HEX,400,SPL_GLOW,SPL_MUTE,SPL_CONFUSE,SPL_CHARM,SPL_SILENCE,SPL_INVISIBLE,SPL_NONE,SPL_NONE),
	book_infor("방어의 마법책",true,BOOK_DEFENSE,600,SPL_VEILING,SPL_DIAMOND_HARDNESS,SPL_CURE_POISON,SPL_DISCHARGE,SPL_SILENCE,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("강화 주술서",false,BOOK_ENCHANT,700,SPL_DIAMOND_HARDNESS,SPL_FIRE_BALL,SPL_SILENCE,SPL_HASTE,SPL_SUMMON_UFO,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("전이의 마법책",true,BOOK_TRANSITION,500,SPL_BLINK,SPL_TELEPORT_OTHER,SPL_TELEPORT_SELF,SPL_RECALL,SPL_KNIFE_COLLECT,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("텐시의 비전서",false,BOOK_TENSI,1000,SPL_STONE_UPLIFT,SPL_KANAME_DRILL,SPL_STONE_FORM,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("미마의 봉인서",false,BOOK_TEST_ANNIHILATE,1500,SPL_POISON_CLOUD,SPL_CHAIN_LIGHTNING,SPL_FIRE_BOLT,SPL_ICE_BOLT,SPL_KANAME_DRILL,SPL_SPARK,SPL_NONE,SPL_NONE)
};

string random_book_list[RANDOM_BOOK_NUM]=
{
	"빨간 커버의 책",
	"파란 커버의 책",
	"노란 커버의 책",
	"초록 커버의 책",
	"분홍 커버의 책",
	"주황 커버의 책",
	"보라 커버의 책"
};



book_list SchoolToBook(skill_type skill_)
{
	switch(skill_)
	{
	case SKT_ALCHEMY:
		{
			book_list list_[5] = {BOOK_BRAND_BASE,BOOK_SUB,BOOK_DEFENSE,BOOK_ENCHANT,BOOK_ALCHMIST_BASE};
			return list_[randA(4)];
		}
	case SKT_MENTAL:
		{
			book_list list_[3] = {BOOK_STALKING,BOOK_HEX,BOOK_PSYCHOLOGIST_BASE};
			return list_[randA(2)];
		}
	case SKT_CONJURE:
		{
			book_list list_[4] = {BOOK_FIRE_BASE,BOOK_COLD_BASE,BOOK_CLOUD,BOOK_SHOCK};
			return list_[randA(3)];
		}
	case SKT_FIRE:
		{
			book_list list_[1] = {BOOK_FIRE_BASE};
			return list_[randA(0)];
		}
	case SKT_COLD:
		{
			book_list list_[1] = {BOOK_COLD_BASE};
			return list_[randA(0)];
		}
	case SKT_EARTH:
		{
			book_list list_[2] = {BOOK_EARTH_BASE,BOOK_TENSI};
			return list_[randA(0)];			
		}
	case SKT_AIR:
		{
			book_list list_[3] = {BOOK_AIR_BASE,BOOK_DEFENSE,BOOK_CLOUD};
			return list_[randA(2)];
		}
	case SKT_SUMMON:
		{
			book_list list_[1] = {BOOK_SUMMON_BASE};
			return list_[randA(0)];
		}
	//case SKT_POISON:
	//	{
	//		book_list list_[2] = {BOOK_POISON_BASE,BOOK_CLOUD};
	//		return list_[randA(1)];
	//	}
	//case SKT_ELEC:
	//	{
	//		book_list list_[1] = {BOOK_SHOCK};
	//		return list_[randA(0)];
	//	}
	case SKT_TRANS:
		{
			book_list list_[1] = {BOOK_TRANSITION};
			return list_[randA(0)];
		}
	//case SKT_ALCHEMY:
	//case SKT_WATER:
	default:
		{
			return (book_list)randA(BOOK_LAST-1);
		}
	}
} 
