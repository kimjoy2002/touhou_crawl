//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sprint.cpp
//
// 내용: 스프린트
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "map.h"
#include "skill_use.h"
#include "mon_infor.h"
#include "rand_shuffle.h"
#include "event.h"
#include "note.h"
#include "evoke.h"
#include "armour.h"

enum REWARD_ITEM_TYPE
{
	REWARD_WEAK_POTION,
	REWARD_SCROLL,
	REWARD_POTION,
	REWARD_NECC_RING,
	REWARD_BONUS_FOR_EARLY, //초반에 도움이 될만한 아이템
	REWARD_BONUS_RANDOM, //전체적인 랜덤(포션 두루마리 제외)
	REWARD_BONUS_FOR_MIDDLE, //스펙업에 도움이 될만한 아이템
	REWARD_SPELLCARD,
	REWARD_BOOK,
	REWARD_RING,
	REWARD_RING_ARTI,
	REWARD_AMULET,
	REWARD_ARMOUR,
	REWARD_ARMOUR_ARTI,
	REWARD_ARMOUR2,
	REWARD_SHIELD,
	REWARD_WEAPON,
	REWARD_WEAPON_ARTI,
	REWARD_ARTIFACT,
	REWARD_EVOKE,
	REWARD_TANMAC,
	REWARD_SMALL_SCROLL,
	REWARD_SMALL_POTION,
	REWARD_SMALL_SCPO,
	REWARD_SCALET_RUNE, 
	REWARD_YOUKAI_RUNE,
	REWARD_MOON_RUNE,
	REWARD_PANDE_RUNE,
	REWARD_HELL_RUNE,
	REWARD_GOAL
};



void reward_random_init();

bool reward_item2(int num, REWARD_ITEM_TYPE reward_id, coord_def c);
void set_sprint_map(map_dummy* map_dummy_);

bool PixedMap(map_dummy* map, const char *temp);
bool addMonster_sprint(int num, int mon_id, map_dummy* map);
bool reward_item(int num, REWARD_ITEM_TYPE reward_id, map_dummy* map);


void map_algorithms_sprint(int num)
{	

	reward_random_init();
	for (int x = 0; x < DG_MAX_X; x++)
	{
		for (int y = 0; y < DG_MAX_Y; y++)
		{
			env[num].dgtile[x][y].tile = DG_FLOOR;
		}
	}
	map_dummy sprint_map(num, coord_def(DG_MAX_X/2, DG_MAX_Y/2), true, 1, 1, 0, DG_FLOOR, DG_WALL);
	set_sprint_map(&sprint_map);
	sprint_map.make_map(env[num],true, true);

	//홍마관
	addMonster_sprint(num, MON_HOBGOBRIN_MAID, &sprint_map);
	//3번째방
	addMonster_sprint(num, MON_HOBGOBRIN_TEMP, &sprint_map);

	addMonster_sprint(num, MON_MAGIC_BOOK, &sprint_map);
	reward_item(num, REWARD_BOOK, &sprint_map);
	reward_item(num, REWARD_BOOK, &sprint_map);
	reward_item(num, REWARD_BOOK, &sprint_map);
	//엔터

	addMonster_sprint(num, MON_HOBGOBRIN_MAID, &sprint_map);
	addMonster_sprint(num, MON_HOBGOBRIN_MAID, &sprint_map);
	//3번째방
	addMonster_sprint(num, MON_CHUPARCABRA, &sprint_map);
	//엔터

	//츠구모가미
	reward_item(num, REWARD_ARMOUR2, &sprint_map);
	reward_item(num, REWARD_WEAPON, &sprint_map);
	addMonster_sprint(num, MON_MEDICINE, &sprint_map);
	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ALL), &sprint_map);

	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ONLY_WEAK), &sprint_map);
	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ONLY_WEAK), &sprint_map);

	addMonster_sprint(num, MON_HOBGOBRIN_TEMP, &sprint_map);
	
	addMonster_sprint(num, MON_PACHU, &sprint_map);
	//엔터

	reward_item(num, REWARD_WEAPON, &sprint_map);
	reward_item(num, REWARD_SHIELD, &sprint_map);

	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ONLY_WEAK), &sprint_map);
	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ONLY_WEAK), &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(SCARLET_LEVEL, GMFF_FLAG_ONLY_WEAK), &sprint_map);
	//엔터
	
	//엔터

	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ALL), &sprint_map);

	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ALL), &sprint_map);


	addMonster_sprint(num, getMonsterFromFloor(SCARLET_LEVEL, GMFF_FLAG_ONLY_WEAK), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(SCARLET_LEVEL, GMFF_FLAG_ONLY_WEAK), &sprint_map);

	reward_item(num, REWARD_ARTIFACT, &sprint_map);
	addMonster_sprint(num, MON_VAMPIER_BAT, &sprint_map);

	addMonster_sprint(num, MON_MAGIC_BOOK, &sprint_map);

	reward_item(num, REWARD_BOOK, &sprint_map);
	reward_item(num, REWARD_BOOK, &sprint_map);
	reward_item(num, REWARD_BOOK, &sprint_map);
	//엔터
	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromSpecial(0, GMFF_FLAG_ALL), &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(SCARLET_LEVEL, GMFF_FLAG_ONLY_WEAK), &sprint_map);

	reward_item(num, REWARD_SCALET_RUNE, &sprint_map);
	addMonster_sprint(num, MON_REMILIA, &sprint_map);

	addMonster_sprint(num, MON_WAKASAGI, &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	//엔터

	reward_item(num, REWARD_ARTIFACT, &sprint_map);
	addMonster_sprint(num, MON_VAMPIER_BAT, &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);

	//엔터


	//아직 중앙
	reward_item(num, REWARD_WEAK_POTION, &sprint_map);
	reward_item(num, REWARD_NECC_RING, &sprint_map);
	//깊은층
	reward_item(num, REWARD_ARMOUR2, &sprint_map);
	//엔터

	reward_item(num, REWARD_WEAK_POTION, &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(7, GMFF_FLAG_ALL), &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//깊은층
	addMonster_sprint(num, getMonsterFromFloor(12, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(12, GMFF_FLAG_ALL), &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	//엔터

	//시작
	addMonster_sprint(num, randA(1) ? MON_KATPA: MON_HUMAM_MAN, &sprint_map);
	addMonster_sprint(num, randA(2)? (randA(1) ? MON_SUNNY : MON_STAR):MON_LUNAR, &sprint_map);
	//시작끝
	addMonster_sprint(num, getMonsterFromFloor(8, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	reward_item(num, REWARD_BONUS_FOR_EARLY, &sprint_map);
	//깊은층
	addMonster_sprint(num, getMonsterFromFloor(14, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(14, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	reward_item(num, REWARD_BONUS_FOR_MIDDLE, &sprint_map);

	addMonster_sprint(num, MON_TEWI, &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	//엔터

	addMonster_sprint(num, getMonsterFromFloor(7, GMFF_FLAG_ALL), &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//깊은층
	addMonster_sprint(num, getMonsterFromFloor(12, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(12, GMFF_FLAG_ALL), &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	//엔터

	//아직중앙
	addMonster_sprint(num, getMonsterFromFloor(0, GMFF_FLAG_ONLY_WEAK), &sprint_map);

	addMonster_sprint(num, MON_BUSH, &sprint_map);
	addMonster_sprint(num, MON_BUSH, &sprint_map);
	//깊은층
	reward_item(num, REWARD_NECC_RING, &sprint_map);
	reward_item(num, REWARD_ARMOUR2, &sprint_map);
	//엔터


	reward_item(num, REWARD_SMALL_SCPO, &sprint_map);
	reward_item(num, REWARD_SMALL_SCPO, &sprint_map);


	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(BAMBOO_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	//엔터

	addMonster_sprint(num, getMonsterFromFloor(MISTY_LAKE_LEVEL, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(MISTY_LAKE_LEVEL, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(MISTY_LAKE_LEVEL, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	addMonster_sprint(num, MON_BUSH, &sprint_map);

	addMonster_sprint(num, MON_YAMAWARO_NINJA, &sprint_map);
	//엔터

	addMonster_sprint(num,MON_CIRNO, &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(MISTY_LAKE_LEVEL, GMFF_FLAG_ONLY_STRONG), &sprint_map);

	addMonster_sprint(num, MON_KATPA, &sprint_map);


	addMonster_sprint(num, MON_YAMAWARO_WAWRRIOR, &sprint_map);
	addMonster_sprint(num, MON_YAMAWARO_FLAG, &sprint_map);

	addMonster_sprint(num, MON_SANPEI_FIGHTER, &sprint_map);

	reward_item(num, REWARD_TANMAC, &sprint_map);
	//엔터


	reward_item(num, REWARD_SCROLL, &sprint_map);
	reward_item(num, REWARD_POTION, &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(MISTY_LAKE_LEVEL, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(MISTY_LAKE_LEVEL, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	
	addMonster_sprint(num, MON_KATPA_SPEAR, &sprint_map);
	addMonster_sprint(num, MON_KATPA_WATER_WIZARD, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_AMULET, &sprint_map);
	//엔터


	reward_item(num, REWARD_SCROLL, &sprint_map);
	reward_item(num, REWARD_POTION, &sprint_map);
	
	addMonster_sprint(num, MON_BUSH, &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(MISTY_LAKE_LEVEL, GMFF_FLAG_ONLY_WEAK), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(MISTY_LAKE_LEVEL, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(MISTY_LAKE_LEVEL, GMFF_FLAG_ONLY_WEAK), &sprint_map);

	reward_item(num, REWARD_SMALL_SCPO, &sprint_map);
	reward_item(num, REWARD_SMALL_SCPO, &sprint_map);

	addMonster_sprint(num, MON_CROW_TENGU, &sprint_map);

	addMonster_sprint(num, MON_NESI, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_EVOKE, &sprint_map);
	//엔터

	addMonster_sprint(num, MON_NEMUNO, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	addMonster_sprint(num, MON_HANATACA_TENGU, &sprint_map);
	addMonster_sprint(num, MON_AYA, &sprint_map);
	addMonster_sprint(num, MON_YAMABUSH_TENGU, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_SPELLCARD, &sprint_map);
	//엔터

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_YOUKAI_RUNE, &sprint_map);

	addMonster_sprint(num, MON_NITORI, &sprint_map);

	reward_item(num, REWARD_TANMAC, &sprint_map);
	//엔터


	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_ARTIFACT, &sprint_map);
	reward_item(num, REWARD_PANDE_RUNE, &sprint_map);
	reward_item(num, REWARD_ARTIFACT, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//엔터


	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	//엔터


	addMonster_sprint(num, MON_FLOWER_TANK, &sprint_map);

	addMonster_sprint(num, MON_YUMEKO, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//엔터

	addMonster_sprint(num, MON_YUKI, &sprint_map);
	addMonster_sprint(num, MON_MAI, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	//엔터

	addMonster_sprint(num, MON_LUIZE, &sprint_map);
	addMonster_sprint(num, MON_ELIS, &sprint_map);
	addMonster_sprint(num, MON_SARA, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//엔터


	addMonster_sprint(num, MON_EVIL_EYE_TANK, &sprint_map);

	reward_item(num, REWARD_GOAL, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	//엔터

	addMonster_sprint(num, getMonsterFromFloor(PANDEMONIUM_LEVEL + 3, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(PANDEMONIUM_LEVEL + 3, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//엔터

	addMonster_sprint(num, getMonsterFromFloor(PANDEMONIUM_LEVEL + 3, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);
	addMonster_sprint(num, getMonsterFromFloor(PANDEMONIUM_LEVEL + 3, GMFF_FLAG_ONLY_MIDDLE), &sprint_map);

	addMonster_sprint(num, MON_MOON_RABIT_ATTACK, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, getMonsterFromFloor(DEPTH_LEVEL, GMFF_FLAG_ALL), &sprint_map);
	//엔터

	addMonster_sprint(num, MON_SHEEP, &sprint_map);
	addMonster_sprint(num, MON_SHEEP, &sprint_map);
	addMonster_sprint(num, MON_SHEEP, &sprint_map);

	reward_item(num, REWARD_BONUS_FOR_MIDDLE, &sprint_map);
	reward_item(num, REWARD_ARTIFACT, &sprint_map);
	reward_item(num, REWARD_BONUS_FOR_MIDDLE, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//엔터


	addMonster_sprint(num, MON_MOON_RABIT_SUPPORT, &sprint_map);

	addMonster_sprint(num, MON_YORIHIME, &sprint_map);
	addMonster_sprint(num, MON_TOYOHIME, &sprint_map);
	reward_item(num, REWARD_MOON_RUNE, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//엔터

	addMonster_sprint(num, MON_MOON_RABIT_ELITE, &sprint_map);
	addMonster_sprint(num, MON_MOON_RABIT_ELITE, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//엔터


	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, MON_HELL_SPIDER, &sprint_map);
	addMonster_sprint(num, MON_HELL_CROW, &sprint_map);
	addMonster_sprint(num, MON_HAUNT, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	//엔터


	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, MON_FIRE_CAR, &sprint_map);
	addMonster_sprint(num, MON_BLOOD_HAUNT, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, MON_MOON_RABIT_ATTACK, &sprint_map);
	addMonster_sprint(num, MON_BLUE_UFO, &sprint_map);
	addMonster_sprint(num, MON_LUNATIC, &sprint_map);
	addMonster_sprint(num, MON_GREEN_UFO, &sprint_map);
	//엔터


	reward_item(num, REWARD_HELL_RUNE, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, MON_UTSUHO, &sprint_map);

	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);
	reward_item(num, REWARD_BONUS_RANDOM, &sprint_map);

	addMonster_sprint(num, MON_RED_UFO, &sprint_map);
	addMonster_sprint(num, MON_NIGHTMARE, &sprint_map);
	addMonster_sprint(num, MON_MAC, &sprint_map);
	addMonster_sprint(num, MON_RINGO, &sprint_map);
}


bool addMonster_sprint(int num, int mon_id, map_dummy* map)
{
	coord_def c = map->getNextPos();
	if (c.equals(0, 0))
		return false;

	monster* mon_ = env[num].AddMonster(mon_id, 0, c);
	mon_->SetStrong(mon_->isUnique()?5: 3);
	return true;
}

random_extraction<int> rand_scroll_necessary;

random_extraction<int> rand_scroll_option;
random_extraction<int> rand_potion_option;
random_extraction<int> rand_ring_necessary;
random_extraction<int> rand_spell_card;//스펠카드(땅제외)
random_extraction<int> rand_book;//책
random_extraction<int> rand_ring_option;//반지(골고루)
random_extraction<int> rand_armour2;//보조방어구
random_extraction<int> rand_shield;//보조방어구
random_extraction<int> rand_amulet;//목걸이
random_extraction<int> rand_evoke;//발동템
random_extraction<int> rand_tanmac;//탄막
random_extraction<int> rand_bonus_for_early; //당장 초반에 도움이 될만한 아이템
random_extraction<int> rand_bonus_for_middle; //스펙업에 도움이 되는 아이템
random_extraction<int> rand_bonus_for_random; //랜덤 아이템
void reward_random_init()
{

	for (int i = rand_int(8, 12); i>0; i--)
		rand_scroll_necessary.push(SCT_IDENTIFY,2);
	for (int i = rand_int(8, 12); i>0; i--)
		rand_scroll_necessary.push(SCT_REMOVE_CURSE,2);
	for(int i = rand_int(8,12);i>0;i--)
		rand_scroll_necessary.push(SCT_ENCHANT_WEAPON_1);
	for (int i = rand_int(8, 12); i>0; i--)
		rand_scroll_necessary.push(SCT_ENCHANT_ARMOUR);
	rand_scroll_option.push(SCT_BLINK, 2);
	rand_scroll_option.push(SCT_FOG, 5);
	rand_scroll_option.push(SCT_SILENCE, 2);
	rand_scroll_option.push(SCT_SOUL_SHOT);
	rand_scroll_option.push(SCT_CHARGING, 5);
	rand_scroll_option.push(SCT_AMNESIA, 5);
	rand_scroll_option.push(SCT_BRAND_WEAPON, 2);

	rand_potion_option.push(PT_HEAL, 10);
	rand_potion_option.push(PT_HEAL_WOUND, 8);
	rand_potion_option.push(PT_MIGHT, 3);
	rand_potion_option.push(PT_HASTE, 3);
	rand_potion_option.push(PT_CLEVER, 3);
	rand_potion_option.push(PT_AGILITY, 3);
	rand_potion_option.push(PT_MAGIC, 1);
	rand_potion_option.push(PT_RECOVER_STAT, 5);

	
	rand_ring_necessary.push(RGT_ELEC_RESIS, 1);
	rand_ring_necessary.push(RGT_FIRE_RESIS, 3);
	rand_ring_necessary.push(RGT_ICE_RESIS, 4);
	rand_ring_necessary.push(RGT_POISON_RESIS, 4);
	rand_ring_necessary.push(RGT_SEE_INVISIBLE, 1);
	rand_ring_necessary.push(RGT_MAGIC_RESIS, 1);


	rand_spell_card.push(SPC_V_FIRE, 3);
	rand_spell_card.push(SPC_V_ICE, 3);
	rand_spell_card.push(SPC_V_AIR, 3);
	rand_spell_card.push(SPC_V_METAL, 3);
	rand_spell_card.push(SPC_V_INVISIBLE, 1);
	rand_spell_card.push(SPC_V_SUN, 1);

	for (int i = 0; i < BOOK_LAST; i++) {
		if(i != BOOK_TRANSITION)
			rand_book.push(i);
	}


	rand_ring_option.push(RGT_STR, 1);
	rand_ring_option.push(RGT_DEX, 1);
	rand_ring_option.push(RGT_INT, 1);
	rand_ring_option.push(RGT_INVISIBLE, 1);
	rand_ring_option.push(RGT_MANA, 1);
	rand_ring_option.push(RGT_MAGACIAN, 1);
	rand_ring_option.push(RGT_AC, 1);
	rand_ring_option.push(RGT_EV, 1);
	rand_ring_option.push(RGT_FIRE_RESIS, 1);
	rand_ring_option.push(RGT_ICE_RESIS, 1);
	rand_ring_option.push(RGT_ELEC_RESIS, 1);
	rand_ring_option.push(RGT_CONFUSE_RESIS, 1);
	

	rand_armour2.push(ITM_ARMOR_HEAD, 1);
	rand_armour2.push(ITM_ARMOR_CLOAK, 1);
	rand_armour2.push(ITM_ARMOR_GLOVE, 1);
	rand_armour2.push(ITM_ARMOR_BOOT, 1);

	rand_shield.push(1,3);
	rand_shield.push(28, 3);
	rand_shield.push(30, 1);


	rand_amulet.push(AMT_PERFECT,1);
	rand_amulet.push(AMT_BLOSSOM, 1);
	rand_amulet.push(AMT_TIMES, 1);
	rand_amulet.push(AMT_FAITH, 1);
	rand_amulet.push(AMT_SPIRIT, 1);
	rand_amulet.push(AMT_GRAZE, 1);
	rand_amulet.push(AMT_WEATHER, 1);
	//rand_amulet.push(AMT_POPULAR, 1);
	rand_amulet.push(AMT_OCCULT, 1);
	rand_amulet.push(AMT_OCCULT, 1);

	rand_evoke.push(EVK_PAGODA, 1);
	rand_evoke.push(EVK_AIR_SCROLL, 1);
	rand_evoke.push(EVK_DREAM_SOUL, 1);
	rand_evoke.push(EVK_BOMB, 1);
	rand_evoke.push(EVK_GHOST_BALL, 1);
	
	rand_tanmac.push(TMT_AMULET, 3);
	rand_tanmac.push(TMT_POISON_NEEDLE, 2);
	rand_tanmac.push(TMT_KIKU_COMPRESSER, 1);
	rand_tanmac.push(TMT_DOGGOJEO, 1);

	rand_bonus_for_early.push(REWARD_POTION);
	rand_bonus_for_early.push(REWARD_SPELLCARD);
	rand_bonus_for_early.push(REWARD_TANMAC);

	rand_bonus_for_middle.push(REWARD_RING);
	rand_bonus_for_middle.push(REWARD_AMULET);
	rand_bonus_for_middle.push(REWARD_ARMOUR);
	rand_bonus_for_middle.push(REWARD_WEAPON);
	rand_bonus_for_middle.push(REWARD_BOOK);

	rand_bonus_for_random.push(REWARD_SMALL_SCROLL,4);
	rand_bonus_for_random.push(REWARD_SMALL_POTION,4);
	rand_bonus_for_random.push(REWARD_NECC_RING);
	rand_bonus_for_random.push(REWARD_SPELLCARD);
	rand_bonus_for_random.push(REWARD_TANMAC,2);
	rand_bonus_for_random.push(REWARD_RING,2);
	rand_bonus_for_random.push(REWARD_AMULET);
	rand_bonus_for_random.push(REWARD_ARMOUR,2);
	rand_bonus_for_random.push(REWARD_WEAPON,2);
	rand_bonus_for_random.push(REWARD_BOOK);
}
bool reward_item(int num, REWARD_ITEM_TYPE reward_id, map_dummy* map)
{
	coord_def c = map->getNextPos();
	if (c.equals(0, 0))
		return false;
	return reward_item2( num, reward_id, c);
}

bool reward_item2(int num, REWARD_ITEM_TYPE reward_id, coord_def c)
{

	switch (reward_id) {
		default:
			break; 
		case REWARD_WEAK_POTION:
		{
			for (int i = 1; i > 0; i--) {
				int id_ = -1;
				{
					id_ = rand_potion_option.choice();
				}
				item_infor t;
				makeitem(ITM_POTION, -1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_SCROLL:
			{
				int necc_scroll_num = rand_int(2, 3);
				for (int i = rand_int(3,4); i > 0; i--) {
					int id_ = -1;
					if (i < necc_scroll_num || rand_scroll_necessary.GetSize()) {
						id_ = rand_scroll_necessary.pop();
					}
					else {
						id_ = rand_scroll_option.choice();
					}
					item_infor t;
					makeitem(ITM_SCROLL, -1, &t, id_);
					env[num].MakeItem(c, t);
				}
				break;
			}
		case REWARD_POTION:
		{
			for (int i = rand_int(3, 4); i > 0; i--) {
				int id_ = -1;
				{
					id_ = rand_potion_option.choice();
				}
				item_infor t;
				makeitem(ITM_POTION, -1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_NECC_RING:
		{
			for (int i = 1; i > 0; i--) {
				int id_ = -1;
				if (rand_ring_necessary.GetSize()) {
					id_ = rand_ring_necessary.pop();
				}
				else {
					break;
				}
				item_infor t;
				makeitem(ITM_RING, 1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_BONUS_FOR_EARLY:
		{
			return reward_item2(num, (REWARD_ITEM_TYPE)rand_bonus_for_early.choice(), c);
		}	
		case REWARD_BONUS_FOR_MIDDLE:
		{
			return reward_item2(num, (REWARD_ITEM_TYPE)rand_bonus_for_middle.choice(), c);
		}
		case REWARD_BONUS_RANDOM:
		{
			return reward_item2(num, (REWARD_ITEM_TYPE)rand_bonus_for_random.choice(), c);
		}
		case REWARD_SPELLCARD:
		{
			for (int i = 1; i > 0; i--) {
				int id_ = -1;
				if (rand_spell_card.GetSize()) {
					id_ = rand_spell_card.choice();
				}
				else {
					break;
				}
				item_infor t;
				makeitem(ITM_SPELL, 1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_BOOK:
		{
			for (int i = 1; i > 0; i--) {
				int id_ = -1;
				if (rand_book.GetSize()) {
					id_ = rand_book.pop();
				}
				else {
					break;
				}
				item_infor t;
				makeitem(ITM_BOOK, 1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_RING:
		case REWARD_RING_ARTI:
		{
			for (int i = 1; i > 0; i--) {
				int id_ = -1;
				if (rand_ring_option.GetSize()) {
					id_ = rand_ring_option.pop();
				}
				else {
					break;
				}
				item_infor t;
				makeitem(ITM_RING, 1, &t, id_);
				item* item_ = env[num].MakeItem(c, t);
				if (reward_id == REWARD_RING_ARTI || randA(4) == 0) {
					MakeArtifact(item_, 1);
				}
			}
			break;
		}
		case REWARD_AMULET:
		{
			for (int i = 1; i > 0; i--) {
				int id_ = -1;
				if (rand_amulet.GetSize()) {
					id_ = rand_amulet.pop();
				}
				else {
					break;
				}
				item_infor t;
				makeitem(ITM_AMULET, 1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_ARMOUR:
		case REWARD_ARMOUR_ARTI:
		{
			for (int i = 1; i > 0; i--) {
				item_infor t;
				int kind_ = ITM_ARMOR_BODY_ARMOUR_0 + randA(MTK_MAX - 1);
				int type_ = -1;
				if (randA(2)) {
					if (randA(1)) {
						kind_ = ITM_ARMOR_SHIELD;
						if (rand_shield.GetSize()) {
							type_ = rand_shield.pop();
						}
					}
					else {
						kind_ = rand_int(ITM_ARMOR_HEAD, ITM_ARMOR_BOOT);
					}
				}
				else {
					type_ = GetRandomArmourType(1);
				}
				makeitem((item_type)kind_, randA(1), &t, type_);
				item* item_ = env[num].MakeItem(c, t);
				
				if (reward_id == REWARD_ARMOUR_ARTI || randA(2) == 0) {
					MakeArtifact(item_, 1);
				}

			}
			break;
		}
		case REWARD_ARMOUR2:
		{
			for (int i = 1; i > 0; i--) {
				item_infor t;
				int kind_ = rand_int(ITM_ARMOR_HEAD, ITM_ARMOR_BOOT);
				if (rand_armour2.GetSize()) {
					kind_ = rand_armour2.pop();
				}
				armour_kind type_ = GetRandomArmourType(1);
				makeitem((item_type)kind_, randA(1), &t, type_);
				item* item_ = env[num].MakeItem(c, t);

				if (randA(4) == 0) {
					MakeArtifact(item_, 1);
				}

			}
		break;
		}
		case REWARD_SHIELD:
		{
			for (int i = 1; i > 0; i--) {
				item_infor t;
				int kind_ = ITM_ARMOR_SHIELD;
				int type_ = -1;
				if (rand_shield.GetSize()) {
					type_ = rand_shield.pop();
				}

				makeitem((item_type)kind_, randA(1), &t, type_);
				item* item_ = env[num].MakeItem(c, t);

				if (randA(4) == 0) {
					MakeArtifact(item_, 1);
				}

			}
			break;
		}
		case REWARD_WEAPON:
		case REWARD_WEAPON_ARTI:
		{
			for (int i = 1; i > 0; i--) {
				item_infor t;
				makeitem((item_type)(rand_int(ITM_WEAPON_FIRST, ITM_WEAPON_CLOSE)), randA(1), &t);
				item* item_ = env[num].MakeItem(c, t);
				if (reward_id == REWARD_WEAPON_ARTI || randA(2) == 0) {
					MakeArtifact(item_, 1);
				}
			}
			break;
		}
		case REWARD_ARTIFACT:
		{
			return reward_item2(num, 
				randA(2)? (randA(1)? REWARD_RING_ARTI :REWARD_ARMOUR_ARTI)
				: REWARD_WEAPON_ARTI
				, c);
		}
		case REWARD_EVOKE:
		{
			for (int i = 1; i > 0; i--) {
				int id_ = -1;
				if (rand_evoke.GetSize()) {
					id_ = rand_evoke.pop();
				}
				else {
					id_ = -1;
				}
				item_infor t;
				makeitem(ITM_MISCELLANEOUS, 1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_TANMAC:
		{
			int id_ = randA(TMT_MAX - 1);
			if (rand_tanmac.GetSize()) {
				id_ = rand_tanmac.choice();
			}
			else {
				id_ = -1;
			}
			for (int i = rand_int(1,2); i > 0; i--) {
				item_infor t;
				makeitem(ITM_THROW_TANMAC, 1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_SMALL_SCROLL:
		{
			for (int i = 1; i > 0; i--) {
				int id_ = -1;
				id_ = rand_scroll_option.choice();
				item_infor t;
				makeitem(ITM_SCROLL, -1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_SMALL_POTION:
		{
			for (int i = 1; i > 0; i--) {
				int id_ = -1;
				id_ = rand_potion_option.choice();
				item_infor t;
				makeitem(ITM_POTION, -1, &t, id_);
				env[num].MakeItem(c, t);
			}
			break;
		}
		case REWARD_SMALL_SCPO:
		{
			return reward_item2(num,
				randA(1) ? REWARD_SMALL_SCROLL: REWARD_SMALL_POTION, c);

		}
		case REWARD_SCALET_RUNE:
		{
			item_infor t;
			makeitem(ITM_GOAL, -1, &t, RUNE_SCARLET);
			env[num].MakeItem(c, t);
			break;
		}
		case REWARD_YOUKAI_RUNE:
		{
			item_infor t;
			makeitem(ITM_GOAL, -1, &t, RUNE_YOUKAI_MOUNTAIN);
			env[num].MakeItem(c, t);
			break;
		}
		case REWARD_MOON_RUNE:
		{
			item_infor t;
			makeitem(ITM_GOAL, -1, &t, RUNE_MOON);
			env[num].MakeItem(c, t);
			break;
		}
		case REWARD_PANDE_RUNE:
		{
			item_infor t;
			makeitem(ITM_GOAL, -1, &t, RUNE_PANDEMONIUM_SHINKI);
			env[num].MakeItem(c, t);
			break;
		}
		case REWARD_HELL_RUNE:
		{
			item_infor t;
			makeitem(ITM_GOAL, -1, &t, RUNE_SUBTERRANEAN);
			env[num].MakeItem(c, t);
			break;
		}
		case REWARD_GOAL:
		{
			item_infor t;
			makeitem(ITM_ORB, -1, &t);
			env[num].MakeItem(c, t);
			break;
		}
	}
	return true;
}





const char* create_sprint_map()
{
	return "\
##########################((((((((((((((((((((((((((((((((([[[[[[[[\
##########################(-S-----+-+---S(---S-S-S-S-((((([[_[[__[[\
##########################(S-S----(((--S-(-EE-----EE-(((([[_______[\
#FFF_F___f___f_____FfF__f#(((((+(((((---S+-------S---((([[_[[__[__[\
#FFFFf_____f______F_F____#(S--+-(((((((+((-EE-----EE-(([[_____[[__[\
#FF____f__F_F___f______f_#(SS-((((SS--+-((---S-S-S-S-([[~~[_______[\
#f_f_______FfF___f__f____#(S--+--(SS--(((((((((((((((([_~W[_F_F[[_[\
######################__f#((((((-(SS-(([[[[[[[[[[[[[[[[____F_F_F__[\
#######################+#####(((+((((([__[_[[_[[______[_[______[__[\
#<.#.S.#.+...T#99999#.f_f..S#......S#[______[____[_[_[[________[[_[\
#..#...#S#....#99999#.._..SS#....SSS#[_[[_[__[[_[_____[____[[_F___[\
#+##.#.#S#..S.+.....+....S.S+....SSS+______[______[_[_F______F_[[_[\
#..#.#.#.#....#99999#.._..SS#....SSS#[__[___[[_[___[__[_____[_F___[\
#.S..#...#...T#99999#.F_F..S#......S#[[_[_[[__[_[_[__[[_[_____[[__[\
#######################+#####***+*****[_[___[___[_____[___[__[[___[\
######################___#****_*_*FFT**[[[[[[[[[[[[[[[[__[_F_F_F_F[\
##~___##_FFF~~~~F___#____#*~~_*_***T_F****************[_____[[____[\
#~_FF________~~__________#*~_F***_**_FF****____F___F**[[__[_____[[[\
#FFFF~~_____________~~__##*FF_~__*__***_**___~~~~~_FF**[[_[_______[\
#FF~~~F___####__FFF~~~~###***FF**_***_F__+__~~~W~~~FF***[[__[[____[\
##########################*F****_**F_FFF_*___~~~~~_FF****[[____[__[\
##########################*_+___***FFF___**____F___F******[[___[__[\
##########################*********************************[[[[[[_[\
#################################################################+#\
####....##/////////ppPpppPpp///////##....##S....##..##..##........#\
###......###//=====/P/PPP/P/=====/##..##..##S...S#..S#..S#..S...###\
##....S...+###/////P///p///P/////##..##+#..##S....##..##..##...####\
#..####..##..##/===/P/p/p/P/===/##..##^^##..##S...S#..S#..S#..#####\
#.#...####=#..##///=/=ppp=/=///##..##^^^^##..##S....##..##...######\
##....S..S###..##//=/=///=/=//##..##::^^^^##..##S...S#.,S#..#+.####\
###......##.+#..##/=/p=/=p/=/##..##^^^:::::##..##S....##...##..####\
####....##...##..##//p=/=p//##..##R^^::~~~~:##..##S...S#..##..#####\
#########.....##..##///=///##..##RRR::~~SSS~~##..##S.....##..######\
#..............##..##/=/=/##..##^^R^:~~.S.SS~~##..##S...##..#######\
#...............##..##=/=+#..##^:::::~~.S.S.~~~##..##S.##..########\
#S...S...S...S..S##..##/##..##:^^^^^::~~....~~~~##..####..#########\
#SS....S...S...SS###..###..##::RRRR:^::.~~~~~~~~~##..##..##########\
#SSS.....S....SSS####.....##:::RRRR:^^^::~~~~~~~~~##....###########\
###################################################################";

}
void set_sprint_map(map_dummy* map_dummy_) {
	map_dummy_->size_x = (67 - 1) / 2;
	map_dummy_->size_y = (39 - 1) / 2;

	random_extraction<int> rand_;

	for (int i = DG_TEMPLE_FIRST; i <= DG_TEMPLE_LAST; i++)
		rand_.push(i);
	map_dummy_->sp_tile_list.clear();

	while (rand_.GetSize()) {
		map_dummy_->sp_tile_list.push_back((dungeon_tile_type)rand_.pop());
	}




	PixedMap(map_dummy_, create_sprint_map());
}