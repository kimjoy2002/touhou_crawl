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
	book_infor("초보 대기술사의 마법책",true,BOOK_AIR_BASE,300,SPL_SHOCK,SPL_LEVITATION, SPL_TWIST,SPL_DISCHARGE,SPL_THUNDER,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 소환술사의 마법책",true,BOOK_SUMMON_BASE,300,SPL_SUMMON_MOOK,SPL_SUMMON_OPTION,SPL_SUMMON_BIRD,SPL_SUMMON_GOLEM,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 연금술사의 마법책",true,BOOK_ALCHMIST_BASE,300,SPL_STONE_PUNCH,SPL_DIAMOND_HARDNESS,SPL_POISON_SKIN,SPL_SUMMON_GOLEM,SPL_EMERALD_CITY,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("초보 심리학자의 마법책",true,BOOK_PSYCHOLOGIST_BASE,300,SPL_HYPNOSIS, SPL_MIND_BENDING, SPL_MUTE, SPL_SELF_INJURY, SPL_CHARM,SPL_NONE ,SPL_NONE,SPL_NONE),
	book_infor("초보 마법전사의 마법책",true,BOOK_BRAND_BASE,400,SPL_VEILING,SPL_DIAMOND_HARDNESS,SPL_POISON_SKIN,SPL_SILENCE,SPL_HASTE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("메이드의 기본소양",true,BOOK_MAID_BASE,400,SPL_BLINK,SPL_SUMMON_OPTION,SPL_KNIFE_COLLECT,SPL_TIME_PARADOX,SPL_PRIVATE_SQ,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("전격의 마법책",true,BOOK_SHOCK,500,SPL_SHOCK,SPL_LEVITATION,SPL_DISCHARGE,SPL_THUNDER,SPL_CHAIN_LIGHTNING,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("원소 연습의 마법책",true,BOOK_PRACTICE,450,SPL_BURN,SPL_FROZEN,SPL_VEILING,SPL_STONE_PUNCH,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("보조의 마법책",true,BOOK_SUB,450,SPL_DRAW_POWER,SPL_DIAMOND_HARDNESS,SPL_BLINK,SPL_MIND_BENDING,SPL_SUMMON_BIRD,SPL_STONE_TRAP,SPL_NONE,SPL_NONE),
	book_infor("암살자의 마법책",true,BOOK_STALKING,600,SPL_STING,SPL_CONFUSE,SPL_CONFUSE_CLOUD,SPL_INVISIBLE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("구름의 마법책",true,BOOK_CLOUD,700,SPL_TWIST,SPL_FIRE_WALL,SPL_CONFUSE_CLOUD,SPL_POISON_CLOUD,SPL_ICE_CLOUD,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("파괴의 마법책",true,BOOK_CONJURE,700,SPL_MAGIC_TANMAC,SPL_SUMMON_OPTION,SPL_LASER,SPL_FIRE_BOLT,SPL_ICE_BOLT,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("매혹의 마법책",true,BOOK_HEX,400,SPL_GLOW,SPL_MUTE,SPL_CONFUSE,SPL_CHARM,SPL_SILENCE,SPL_INVISIBLE,SPL_NONE,SPL_NONE),
	book_infor("방어의 마법책",true,BOOK_DEFENSE,600,SPL_VEILING,SPL_DIAMOND_HARDNESS,SPL_CURE_POISON,SPL_DISCHARGE,SPL_SILENCE,SPL_FIELD_VIOLET,SPL_NONE,SPL_NONE),	
	book_infor("풍수지리학 개요",false,BOOK_ENCHANT,700,SPL_AIR_STRIKE,SPL_FREEZE,SPL_STONE_UPLIFT,SPL_FIRE_BALL,SPL_HASTE,SPL_SUMMON_UFO,SPL_NONE,SPL_NONE),
	book_infor("전이의 마법책",true,BOOK_TRANSITION,500,SPL_DRAW_POWER,SPL_BLINK,SPL_TELEPORT_OTHER,SPL_TELEPORT_SELF,SPL_RECALL,SPL_KNIFE_COLLECT,SPL_NONE,SPL_NONE),	
	book_infor("텐시의 비전서",false,BOOK_TENSI,1000,SPL_STONE_UPLIFT,SPL_KANAME_DRILL,SPL_STONE_FORM,SPL_SUMMON_NAMAZ,SPL_SHATTER,SPL_NONE,SPL_NONE,SPL_NONE),	
	book_infor("미마의 봉인서",false,BOOK_TEST_ANNIHILATE,1500,SPL_LUMINUS_STRIKE,SPL_SPARK,SPL_FIRE_STORM,SPL_PERFERT_FREEZE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("정신 지배학",true,BOOK_DEBUF,1500,SPL_ANIMAL_CHANGE,SPL_PRIVATE_SQ,SPL_INVISIBLE,SPL_FIELD_VIOLET,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("메이드 비전서",false,BOOK_MAID_ULTI,1500,SPL_PRIVATE_SQ,SPL_CONTROLED_BLINK,SPL_THE_WORLD,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("얼음요정 비전서",false,BOOK_ICE_ULTI,1500,SPL_ICE_BOLT,SPL_ICE_CLOUD,SPL_BLIZZARD,SPL_PERFERT_FREEZE,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("앨리스의 마도서",false,BOOK_SUMMON_ULTI,1500,SPL_SUMMON_UFO,SPL_SUMMON_YOUKAI,SPL_SUMMON_NAMAZ,SPL_DOLLS_WAR,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("텐구의 활극 만화",false,BOOK_AIR_ULTI,1500,SPL_VEILING,SPL_TWIST,SPL_AIR_STRIKE,SPL_MACRO_BURST,SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE),
	book_infor("마그눔 오푸스",false,BOOK_ALCHMY_ULTI,1500,SPL_EMERALD_CITY,SPL_STONE_FORM,SPL_AUTUMN_BLADE,SPL_PHILOSOPHERS_STONE, SPL_NONE,SPL_NONE,SPL_NONE,SPL_NONE)
	
};

string random_book_list[RANDOM_BOOK_NUM]=
{
	"빨간 커버의 책",
	"초록 커버의 책",
	"파란 커버의 책",
	"노란 커버의 책",
	"분홍 커버의 책",
	"주황 커버의 책",
	"보라 커버의 책"
};





const char* GetBookInfor(book_list book_)
{
	switch(book_)
	{
	default:
	case BOOK_CUSTOM_BOOK:
		return "다양한 마법이 들어 있는 책.\n이름있는 책은 아닌 것 같지만 배울만한 마법은 있어보인다.\n";
	case BOOK_FIRE_BASE:
		return "화염에 대한 기초적인 마법이 들어 있는 책\n화염마법에 입문하고 싶은 당신에게 추천\n";
	case BOOK_COLD_BASE:
		return "냉기에 대한 기초적인 마법이 들어 있는 책\n냉기마법에 입문하고 싶은 당신에게 추천\n";
	case BOOK_POISON_BASE:
		return "독에 대한 기초적인 마법이 들어 있는 책\n독마법에 입문하고 싶은 당신에게 추천\n";
	case BOOK_WIZARD_BASE:
		return "다양하고 가성비 좋은 저레벨 마법들이 들어 있는 책\n고레벨은 없지만 구성이 알차다.\n";
	case BOOK_EARTH_BASE:
		return "대지에 대한 기초적인 마법이 들어 있는 책\n대지마법에 입문하고 싶은 당신에게 추천\n";
	case BOOK_AIR_BASE:
		return "대기에 대한 기초적인 마법이 들어 있는 책\n대기마법에 입문하고 싶은 당신에게 추천\n";
	case BOOK_SUMMON_BASE:
		return "소환에 대한 기초적인 마법이 들어 있는 책\n소환마법에 입문하고 싶은 당신에게 추천\n";
	case BOOK_ALCHMIST_BASE:
		return "연금술을 가르치는 책\n마법을 통해서 간단한 연금술을 시험해볼 수 있는 것 같다.\n";
	case BOOK_PSYCHOLOGIST_BASE:
		return "정신을 조종하는 기초적인 마법이 들어 있는 책\n심리마법에 입문하고 싶은 당신에게 추천\n";
	case BOOK_BRAND_BASE:
		return "초보 마전사를 위해 만들어진 마법책\n전사들에게 유용한 마법들로 구성이 되어있다.\n";
	case BOOK_MAID_BASE:
		return "메이드들이 기본적으로 가져야할 소양이라고 적혀있다. 홍마관에서 배포중이다.\n메이드의 길은 멀고도 험하다.\n";
	case BOOK_SHOCK:
		return "다양한 전기마법이 적혀있는 마법책\n만지기만해도 짜릿짜릿하다.\n";
	case BOOK_PRACTICE:
		return "간단한 원소연습을 할 수 있게 되어있는 마법책\n하지만 빅토리댄스는 이제 없다고!\n";
	case BOOK_SUB:
		return "다양한 보조마법이 적혀있는 마법책.\n마법사 입문에 좋아보인다.\n";
	case BOOK_STALKING:
		return "마법암살자를 꿈꾸는 사람들을 위한 마법책\n아직은 마법이 모자라보인다.\n";
	case BOOK_CLOUD:
		return "구름을 만드는 노하우가 적혀있는 마법책\n왠지 책도 축축해보인다.\n";
	case BOOK_CONJURE:
		return "강력한 파괴의 기초 마법이 적혀있는 책\n탄막은 파워!\n";
	case BOOK_HEX:
		return "정신마법계열의 마법이 적혀있는 책\n요괴들은 정신공격에 약하다고들 한다.\n";
	case BOOK_DEFENSE:
		return "다양한 방어 주문이 들어있는 책\n살아남는 것은 제일 중요하다.\n";
	case BOOK_ENCHANT:
		return "풍수지리에 해박한 모노노베노 후토가 편찬한 책.\n바람을 다루는 것부터 대지를 일으키는 일, 물을 다루면서 운기를 다루는 법이 적혀있다\n 왜인지 방화하는 법에 대한 세세한 부록이 끼워져있다.\n";
	case BOOK_TRANSITION:
		return "전이에 관련된 마법이 적혀있는 마법책\n시공간을 다루는 것엔 큰 위험이 따른다.\n";
	case BOOK_TENSI:
		return "불량천인 텐시가 직접 자필한 마법책\n예측불가인 그녀지만 그녀의 대지를 다루는 기술은 배울만하다.\n";
	case BOOK_TEST_ANNIHILATE:
		return "미마가 적은 궁극의 파괴술서\n모든 파괴법사가 꿈꾸고있는 그 책이다.\n";
	case BOOK_DEBUF:
		return "지저세계에 살고있는 사토리가 적은 정신을 지배하는 법\n왠지 책에게 마음을 읽히고 있는 듯한 느낌이다.\n";
	case BOOK_MAID_ULTI:
		return "홍마관의 메이드장이 유능한 메이드를 길러내기 위해 만들었다는 그 책이다.\n홍마관엔 사쿠야이외에 유능한 메이드가 없을뿐더러 아무도 책을 이해하지 못했기에 전설로만 남겨진 책이다.\n마법 뿐만이 아니라 청소하는 법, 빨래하는 법등이 부록으로 적혀있다.\n";
	case BOOK_ICE_ULTI:
		return "호수에 살고있는 모 얼음 요정이 직접 자신의 최강을 증명하기위해 적인 책이다.\n책은 그림책처럼 그림과 함께 구불구불한 글씨로 설명이 되어있다.\n굉장히 추상적으로 설명되어있기에 오히려 이해하기 어렵다. 이해하려면 놀라운 이해력이 있어야될것같다.\n";
	case BOOK_SUMMON_ULTI:
		return "마법의 숲에 살고있는 인형술사가 자주 들고다니는 책이라고 한다.\n정교하고 섬세하게 설명되어있는 많은 인형을 다루는 법은 소환술에도 응용할 수 있을 것 같다.\n무섭게도 폭약다루는 법, 상대를 저주하는 법도 적혀있다. 이 부분은 못본척하자.\n";
	case BOOK_AIR_ULTI:
		return "텐구가 주인공인 박진감 넘치는 모험 만화.\n 내용도 재밌지만 이 만화의 주인공이 쓰는 기술은 따라해 볼 수 있을 것 같다.\n";
	case BOOK_ALCHMY_ULTI:
		return "어느 저택안에있는 큰 도서관에 꽂혀있던 연금술의 모든 것이 적혀있는 마도서.\n알아보기 힘들고 애매하게 적혀있어서 연금술의 대가가 아니면 내용을 이해하는건 힘들어보인다.\n적혀있는 지저분한 낙서로봐선 이 책의 원 주인도 내용을 잘 이해하지 못했던거같다.\n";
	}
}

book_list SchoolToBook(skill_type skill_)
{
	switch(skill_)
	{
	case SKT_ALCHEMY:
		{
			random_extraction<book_list> list_;
			list_.push(BOOK_BRAND_BASE,10);
			list_.push(BOOK_SUB,10);
			list_.push(BOOK_DEFENSE,10);
			list_.push(BOOK_ENCHANT,2);
			list_.push(BOOK_ALCHMIST_BASE,10);
			list_.push(BOOK_ALCHMY_ULTI,5);			
			return list_.pop();
		}
	case SKT_MENTAL:
		{
			random_extraction<book_list> list_;
			list_.push(BOOK_STALKING,10);
			list_.push(BOOK_HEX,10);
			list_.push(BOOK_PSYCHOLOGIST_BASE,10);
			list_.push(BOOK_DEBUF,3);
			return list_.pop();
		}
	case SKT_CONJURE:
		{
			random_extraction<book_list> list_;
			list_.push(BOOK_FIRE_BASE,10);
			list_.push(BOOK_COLD_BASE,10);
			list_.push(BOOK_CLOUD,10);
			list_.push(BOOK_SHOCK,10);
			list_.push(BOOK_TEST_ANNIHILATE,2);
			return list_.pop();
		}
	case SKT_FIRE:
		{
			random_extraction<book_list> list_;
			list_.push(BOOK_FIRE_BASE,10);
			list_.push(BOOK_ENCHANT,2);
			return list_.pop();
		}
	case SKT_COLD:
		{
			random_extraction<book_list> list_;
			list_.push(BOOK_COLD_BASE,10);
			list_.push(BOOK_ICE_ULTI,3);
			list_.push(BOOK_ENCHANT,2);
			return list_.pop();
		}
	case SKT_EARTH:
		{
			random_extraction<book_list> list_;
			list_.push(BOOK_EARTH_BASE,10);
			list_.push(BOOK_TENSI,3);
			list_.push(BOOK_ENCHANT,2);
			return list_.pop();			
		}
	case SKT_AIR:
		{
			random_extraction<book_list> list_;
			list_.push(BOOK_AIR_BASE,10);
			list_.push(BOOK_DEFENSE,10);
			list_.push(BOOK_CLOUD,10);
			list_.push(BOOK_ENCHANT,2);
			list_.push(BOOK_AIR_ULTI,5);
			
			return list_.pop();
		}
	case SKT_SUMMON:
		{
			random_extraction<book_list> list_;
			list_.push(BOOK_SUMMON_BASE,10);
			list_.push(BOOK_ENCHANT,2);
			list_.push(BOOK_SUMMON_ULTI,3);
			return list_.pop();
		}
	case SKT_TRANS:
		{
			random_extraction<book_list> list_;
			list_.push(BOOK_TRANSITION,10);
			list_.push(BOOK_MAID_ULTI,3);
			return list_.pop();
		}
	default:
		{
			return (book_list)randA(BOOK_LAST-1);
		}
	}
} 
