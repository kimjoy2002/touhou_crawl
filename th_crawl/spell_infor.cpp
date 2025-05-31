//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: spell_infor.cpp
//
// 내용: 마법과 스킬의 정보
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "key.h"
#include "player.h"
#include "skill_use.h"



string GetSpellInfor(spell_list spell, bool isPlayer)
{
	ostringstream oss;
	oss << SpellString(spell) << "\n\n";
	switch(spell)
	{
	case SPL_NONE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_NONE);
		break;
	case SPL_MON_TANMAC_SMALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MON_TANMAC_SMALL);
		break;
	case SPL_MON_TANMAC_MIDDLE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MON_TANMAC_MIDDLE);
		break;
	case SPL_MON_WATER_GUN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MON_WATER_GUN);
		break;
	case SPL_FLAME:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FLAME);
		break;
	case SPL_FROST:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FROST);
		break;	
	case SPL_MEDICINE_CLOUD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MEDICINE_CLOUD);
		break;
	case SPL_COLD_BEAM:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_COLD_BEAM);
		break;
	case SPL_SUMMON_BUG:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_BUG);
		break;
	case SPL_CONFUSE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CONFUSE);
		break;
	case SPL_SLOW:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SLOW);
		break;
	case SPL_SELF_HEAL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SELF_HEAL);
		break;
	case SPL_BLINK:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_BLINK);
		break;
	case SPL_SMITE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SMITE);
		break;
	case SPL_BURN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_BURN);
		break;
	case SPL_FIRE_WALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FIRE_WALL);
		break;
	case SPL_FROZEN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FROZEN);
		break;
	case SPL_FREEZE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FREEZE);
		break;
	case SPL_STING:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_STING);
		break;
	case SPL_CURE_POISON:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CURE_POISON);
		break;
	case SPL_TWIST:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_TWIST);
		break;
	case SPL_SUMMON_MOOK:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_MOOK);
		break;
	case SPL_FIRE_BRAND:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FIRE_BRAND);
		break;
	case SPL_COLD_BRAND:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_COLD_BRAND);
		break;
	case SPL_POISON_BRAND:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_POISON_BRAND);
		break;
	case SPL_SHOCK:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SHOCK);
		break;
	case SPL_CHAIN_LIGHTNING:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CHAIN_LIGHTNING);
		break;
	case SPL_DISCHARGE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_DISCHARGE);
		break;
	case SPL_LEVITATION:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_LEVITATION);
		break;
	case SPL_GLOW:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_GLOW);
		break;
	case SPL_GRAZE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_GRAZE);
		break;
	case SPL_VEILING:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_VEILING);
		break;
	case SPL_INVISIBLE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_INVISIBLE);
		break;
	case SPL_HASTE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_HASTE);
		break;
	case SPL_SILENCE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SILENCE);
		break;
	case SPL_SWIFT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SWIFT);
		break;
	case SPL_MAGIC_TANMAC:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MAGIC_TANMAC);
		break;
	case SPL_FIRE_BALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FIRE_BALL);
		break;
	case SPL_FIRE_BOLT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FIRE_BOLT);
		break;
	case SPL_ICE_BOLT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_ICE_BOLT);
		break;
	case SPL_VENOM_BOLT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_VENOM_BOLT);
		break;
	case SPL_CONFUSE_CLOUD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CONFUSE_CLOUD);
		break;
	case SPL_POISON_CLOUD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_POISON_CLOUD);
		break;
	case SPL_ICE_CLOUD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_ICE_CLOUD);
		break;
	case SPL_SUMMON_BIRD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_BIRD);
		break;
	case SPL_RECALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_RECALL);
		break;
	case SPL_TELEPORT_OTHER:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_TELEPORT_OTHER);
		break;
	case SPL_TELEPORT_SELF:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_TELEPORT_SELF);
		break;
	case SPL_WHIRLWIND:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_WHIRLWIND);
		break;
	case SPL_SUMMON_PENDULUM:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_PENDULUM);
		break;
	case SPL_SUMMON_SEKIBANKI:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_SEKIBANKI);
		break;
	case SPL_WATER_CANNON:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_WATER_CANNON);
		break;
	case SPL_KYOKO_SMITE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_KYOKO_SMITE);
		break;
	case SPL_SUMMON_OPTION:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_OPTION);
		break;
	case SPL_SUMMON_GOLEM:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_GOLEM);
		break;
	case SPL_HYPNOSIS:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_HYPNOSIS);
		break;
	case SPL_MUTE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MUTE);
		break;
	case SPL_SELF_INJURY:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SELF_INJURY);
		break;
	case SPL_CHARM:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CHARM);
		break;
	case SPL_LASER:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_LASER);
		break;
	case SPL_SPARK:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SPARK);
		break;
	case SPL_SUMMON_UNZAN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_UNZAN);
		break;
	case SPL_SUMMON_UNZAN_PUNCH:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_UNZAN_PUNCH);
		break;
	case SPL_SUMMON_ZOMBIE_FAIRY:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_ZOMBIE_FAIRY);
		break;
	case SPL_SUMMON_UFO:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_UFO);
		break;
	case SPL_HASTE_OTHER:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_HASTE_OTHER);
		break;
	case SPL_HEAL_OTHER:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_HEAL_OTHER);
		break;
	case SPL_MIND_BENDING:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MIND_BENDING);
		break;
	case SPL_STONE_PUNCH:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_STONE_PUNCH);
		break;
	case SPL_STONE_ARROW:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_STONE_ARROW);
		break;
	case SPL_STONE_TRAP:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_STONE_TRAP);
		break;
	case SPL_STONE_UPLIFT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_STONE_UPLIFT);
		break;
	case SPL_KANAME_DRILL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_KANAME_DRILL);
		break;
	case SPL_DIAMOND_HARDNESS:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_DIAMOND_HARDNESS);
		break;
	case SPL_POISON_SKIN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_POISON_SKIN);
		break;
	case SPL_STONE_FORM:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_STONE_FORM);
		break;
	case SPL_KNIFE_COLLECT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_KNIFE_COLLECT);
		break;
	case SPL_FLAN_BUSIN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FLAN_BUSIN);
		break;
	case SPL_BURST:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_BURST);
		break;
	case SPL_SUICIDE_BOMB:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUICIDE_BOMB);
		break;
	case SPL_RABBIT_HORN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_RABBIT_HORN);
		break;
	case SPL_SUMMON_LESSOR_DEMON:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_LESSOR_DEMON);
		break;
	case SPL_LUMINUS_STRIKE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_LUMINUS_STRIKE);
		break;
	case SPL_FIRE_STORM:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FIRE_STORM);
		break;
	case SPL_BLIZZARD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_BLIZZARD);
		break;
	case SPL_PERFERT_FREEZE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_PERFERT_FREEZE);
		break;
	case SPL_DRAW_POWER:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_DRAW_POWER);
		break;
	case SPL_ANIMAL_CHANGE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_ANIMAL_CHANGE);
		break;
	case SPL_FIELD_VIOLET:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FIELD_VIOLET);
		break;
	case SPL_TIME_PARADOX:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_TIME_PARADOX);
		break;
	case SPL_PRIVATE_SQ:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_PRIVATE_SQ);
		break;
	case SPL_CONTROLED_BLINK:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CONTROLED_BLINK);
		break;
	case SPL_THE_WORLD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_THE_WORLD);
		break;
	case SPL_HASTE_ALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_HASTE_ALL);
		break;
	case SPL_HEAL_ALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_HEAL_ALL);
		break;
	case SPL_MOON_COMMUNICATION:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MOON_COMMUNICATION);
		break;
	case SPL_MOON_GUN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MOON_GUN);
		break;
	case SPL_SUMMON_DREAM:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_DREAM);
		break;
	case SPL_MANA_DRAIN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MANA_DRAIN);
		break;
	case SPL_INSANE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_INSANE);
		break;
	case SPL_BLOOD_SMITE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_BLOOD_SMITE);
		break;
	case SPL_CALL_HOUND:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CALL_HOUND);
		break;
	case SPL_CANNON:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CANNON);
		break;
	case SPL_DOLLS_WAR:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_DOLLS_WAR);
		break;
	case SPL_FAKE_DOLLS_WAR:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FAKE_DOLLS_WAR);
		break;
	case SPL_FIRE_SPREAD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_FIRE_SPREAD);
		break;
	case SPL_STASIS:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_STASIS);
		break;
	case SPL_JUMP_ATTACK:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_JUMP_ATTACK);
		break;
	case SPL_ALERT_NOISE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_ALERT_NOISE);
		break;
	case SPL_SUMMON_NAMAZ:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_NAMAZ);
		break;
	case SPL_SCHEMA_TANMAC:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SCHEMA_TANMAC);
		break;
	case SPL_CHANGE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CHANGE);
		break;
	case SPL_UNLUCK:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_UNLUCK);
		break;	
	case SPL_THUNDER:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_THUNDER);
		break;
	case SPL_AIR_STRIKE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_AIR_STRIKE);
		break;
	case SPL_SUMMON_RACOON:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_RACOON);
		break;
	case SPL_SUMMON_YOUKAI:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_YOUKAI);
		break;
	case SPL_MAMIZO_EVADE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MAMIZO_EVADE);
		break;
	case SPL_MACRO_BURST:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MACRO_BURST);
		break;
	case SPL_SHATTER:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SHATTER);
		break;
	case SPL_SUMMON_YOSHIKA:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_YOSHIKA);
		break;
	case SPL_NESY_CANNON:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_NESY_CANNON);
		break;
	case SPL_MERMAID_SONG:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MERMAID_SONG);
		break;
	case SPL_EMERALD_CITY:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_EMERALD_CITY);
		break;
	case SPL_AUTUMN_BLADE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_AUTUMN_BLADE);
		break;
	case SPL_PHILOSOPHERS_STONE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_PHILOSOPHERS_STONE);
		break;
	case SPL_SUMMON_ANCHOR:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_ANCHOR);
		break;
	case SPL_REAPER_MET:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_REAPER_MET);
		break;
	case SPL_AFTERLITE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_AFTERLITE);
		break;
	case SPL_PRISM_CALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_PRISM_CALL);
		break;
	case SPL_PSYCHOKINESIS:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_PSYCHOKINESIS);
		break;
	case SPL_SUMMON_TRASH:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_TRASH);
		break;
	case SPL_TRASH_RUSH:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_TRASH_RUSH);
		break;
	case SPL_KOKORO_CHANGE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_KOKORO_CHANGE);
		break;
	case SPL_THUNDER_BOLT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_THUNDER_BOLT);
		break;
	case SPL_SANTUARY:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SANTUARY);
		break;
	case SPL_MISTIA_SONG:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MISTIA_SONG);
		break;
	case SPL_THROW_DISH:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_THROW_DISH);
		break;
	case SPL_MESS_CONFUSION:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MESS_CONFUSION);
		break;
	case SPL_SLEEP_SMITE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SLEEP_SMITE);
		break;
	case SPL_TARGET_ELEC:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_TARGET_ELEC);
		break;
	case SPL_SUMMON_ELEC_BALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_ELEC_BALL);
		break;
	case SPL_DREAM_CALL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_DREAM_CALL);
		break;
	case SPL_HYPER_BEAM:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_HYPER_BEAM);
		break;
	case SPL_KAGUYA_SPELL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_KAGUYA_SPELL);
		break;
	case SPL_THROW_SWORD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_THROW_SWORD);
		break;
	case SPL_THROW_KNIFE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_THROW_KNIFE);
		break;
	case SPL_THROW_PLAYER:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_THROW_PLAYER);
		break;
	case SPL_THROW_AMULET:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_THROW_AMULET);
		break;
	case SPL_WARP_KICK:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_WARP_KICK);
		break;
	case SPL_REIMU_BARRIER:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_REIMU_BARRIER);
		if (you.god == GT_YUKARI) {
			oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_REIMU_BARRIER_YUKARI);
		}
		break;
	case SPL_TOUGUE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_TOUGUE);
		break;
	case SPL_WINDFLAW:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_WINDFLAW);
		break;
	case SPL_SUMMON_GHOST:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SUMMON_GHOST);
		break;	
	case SPL_MEGATON_KICK:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_MEGATON_KICK);
		break;	
	case SPL_THROW_OIL:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_THROW_OIL);
		break;	
	case SPL_HEAVENLY_STORM:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_HEAVENLY_STORM);
		break;	
	case SPL_TRACKING:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_TRACKING);
		break;	
	case SPL_DISCORD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_DISCORD);
		break;	
	case SPL_SMOKING:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SMOKING);
		break;	
	case SPL_CREATE_FOG:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CREATE_FOG);
		break;	
	case SPL_GROW_VINE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_GROW_VINE);
		break;	
	case SPL_CLOSE_DOOR:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CLOSE_DOOR);
		break;	
	case SPL_SPEAKER_PHONE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_SPEAKER_PHONE);
		break;	
	default:
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_UKNOWN);
		break;
	}
	oss << "\n";

	if ((SpellSchool(spell, 0) == SKT_ALCHEMY ||
		SpellSchool(spell, 1) == SKT_ALCHEMY ||
		SpellSchool(spell, 2) == SKT_ALCHEMY)
		&& SpellFlagCheck(spell, S_FLAG_BUF))
	{
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_ALCHEMY);
	}

	if (SpellFlagCheck(spell, S_FLAG_SUMMON))
	{
		if (GetSummonMaxNumber(spell) > 0)
		{
			oss << LocalzationManager::formatString(LOC_SYSTEM_SPL_DESCRIBE_SUMMONING, PlaceHolderHelper(to_string(GetSummonMaxNumber(spell))));
		}
	}
	if (!SpellFlagCheck(spell, S_FLAG_SPEAK))
	{
		oss << LocalzationManager::locString(LOC_SYSTEM_SPL_DESCRIBE_CAN_USE_SILIENCE);
	}

	oss << "\n\n";

	oss << LocalzationManager::formatString(LOC_SYSTEM_LEVEL_WITH_NUMBER, PlaceHolderHelper(to_string(SpellLevel(spell))));
	oss << "     ";
	oss << LocalzationManager::locString(LOC_SYSTEM_SCHOOL) + ": ";
	oss << GetSpellSchoolString(spell);
	oss << "\n";
	oss << LocalzationManager::locString(LOC_SYSTEM_NOISE) << ": ";
	switch (SpellNoise(spell)) {
	case 0:
		oss << LocalzationManager::locString(LOC_SYSTEM_NOISE_NONE);
		break;
	case 4:
		oss << LocalzationManager::locString(LOC_SYSTEM_NOISE_QUIET);
		break;
	case 8:
		oss << LocalzationManager::locString(LOC_SYSTEM_NOISE_MODERATE);
		break;
	case 12:
		oss << LocalzationManager::locString(LOC_SYSTEM_NOISE_LOUD);
		break;
	case 16:
		oss << LocalzationManager::locString(LOC_SYSTEM_NOISE_VERY_LOUD);
		break;
	case 24:
		oss << LocalzationManager::locString(LOC_SYSTEM_NOISE_DEAFENING);
		break;
	}
	oss << "\n";
	if (int length_ = SpellLength(spell,isPlayer)) {
		oss << LocalzationManager::locString(LOC_SYSTEM_RANGE) << ": " << length_ << " " << (length_<=1 ?  LocalzationManager::locString(LOC_SYSTEM_TILE): LocalzationManager::locString(LOC_SYSTEM_TILES));
	}
	oss << "\n";
	return oss.str();
}

string GetSkillInfor(skill_list skill)
{
	ostringstream oss;
	oss << SkillString(skill) << "\n\n";
	switch(skill)
	{
	case SKL_NONE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_NONE);
		break;
	case SKL_KANAKO_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_KANAKO_1);
		break;
	case SKL_KANAKO_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_KANAKO_2);
		break;
	case SKL_KANAKO_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_KANAKO_3);
		break;
	case SKL_GRAZE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_GRAZE);
		break;
	case SKL_GRAZE_OFF:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_GRAZE_OFF);
		break;
	case SKL_LEVITATION:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_LEVITATION);
		break;
	case SKL_LEVITATION_OFF:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_LEVITATION_OFF);
		break;
	case SKL_INVISIBLE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_INVISIBLE);
		break;
	case SKL_INVISIBLE_OFF:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_INVISIBLE_OFF);
		break;
	case SKL_EIRIN_0:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_EIRIN_0);
		break;
	case SKL_EIRIN_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_EIRIN_1);
		break;
	case SKL_EIRIN_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_EIRIN_2);
		break;
	case SKL_BYAKUREN_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_BYAKUREN_1);
		break;
	case SKL_BYAKUREN_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_BYAKUREN_2);
		break;
	case SKL_SIZUHA_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SIZUHA_1);
		break;
	case SKL_SIZUHA_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SIZUHA_2);
		break;		
	case SKL_SIZUHA_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SIZUHA_3);
		break;		
	case SKL_MINORIKO_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_MINORIKO_1);
		break;		
	case SKL_MINORIKO_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_MINORIKO_2);
		break;
	case SKL_YUUGI_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUUGI_1);
		break;		
	case SKL_YUUGI_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUUGI_2);
		break;		
	case SKL_YUUGI_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUUGI_3);
		break;		
	case SKL_YUUGI_4:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUUGI_4);
		break;		
	case SKL_YUUGI_5:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUUGI_5);
		break;	
	case SKL_SATORI_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SATORI_1);
		break;		
	case SKL_SATORI_2:	
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SATORI_2);
		break;		
	case SKL_SHINKI_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SHINKI_1);
		break;
	case SKL_SHINKI_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SHINKI_2);
		break;
	case SKL_SHINKI_3:	
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SHINKI_3);
		break;		
	case SKL_YUYUKO_ON:	
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUYUKO_ON);
		break;		
	case SKL_YUYUKO_OFF:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUYUKO_OFF);
		break;		
	case SKL_YUYUKO_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUYUKO_1);
		break;
	case SKL_YUYUKO_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUYUKO_2);
		break;
	case SKL_YUYUKO_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUYUKO_3);
		break;
	case SKL_YUKARI_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUKARI_1);
		break;
	case SKL_YUKARI_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUKARI_2);
		break;
	case SKL_YUKARI_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUKARI_3);
		break;
	case SKL_YUKARI_4:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_YUKARI_4);
		break;
	case SKL_SWAKO_JUMP:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_JUMP);
		break;
	case SKL_SWAKO_TEMPLE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_TEMPLE);
		break;
	case SKL_SWAKO_WATER_GUN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_WATER_GUN);
		break;
	case SKL_SWAKO_TOUGUE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_TOUGUE);
		break;
	case SKL_SWAKO_CURSE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_CURSE);
		break;
	case SKL_SWAKO_DIGGING:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_DIGGING);
		break;
	case SKL_SWAKO_SUMMON_FLOG:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_SUMMON_FLOG);
		break;
	case SKL_SWAKO_STATUE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_STATUE);
		break;
	case SKL_SWAKO_RAIN:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_RAIN);
		break;
	case SKL_SWAKO_SLEEP:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_SLEEP);
		break;
	case SKL_SWAKO_MISYAGUZI:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SWAKO_MISYAGUZI);
		break;
	case SKL_HINA_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_HINA_1);
		break;
	case SKL_HINA_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_HINA_2);
		break;
	case SKL_HINA_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_HINA_3);
		break;
	case SKL_HINA_4:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_HINA_4);
		break;
	case SKL_HINA_5:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_HINA_5);
		break;		
	case SKL_JUMPING_ATTACK: 
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_JUMPING_ATTACK);
		break;
	case SKL_BREATH:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_BREATH);
		break;
	case SKL_TORMENT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_TORMENT);
		break;
	case SKL_ABANDON_GOD:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_ABANDON_GOD);
		break;
	case SKL_SEIJA_GIFT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SEIJA_GIFT);
		break;
	case SKL_SEIJA_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SEIJA_1);
		break;
	case SKL_SEIJA_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SEIJA_2);
		break;
	case SKL_LILLY_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_LILLY_1);
		break;
	case SKL_LILLY_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_LILLY_2);
		break;
	case SKL_LILLY_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_LILLY_3);
		break;
	case SKL_LILLY_4:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_LILLY_4);
		break;
	case SKL_OKINA_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_OKINA_1);
		break;
	case SKL_OKINA_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_OKINA_2);
		break;
	case SKL_OKINA_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_OKINA_3);
		break;
	case SKL_OKINA_4:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_OKINA_4);
		break;
	case SKL_OKINA_5:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_OKINA_5);
		break;
	case SKL_JUNKO_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_JUNKO_1);
		break;
	case SKL_JUNKO_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_JUNKO_2);
		break;
	case SKL_JUNKO_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_JUNKO_3);
		break;
	case SKL_JUNKO_4:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_JUNKO_4);
		break;
	case SKL_JOON_AND_SION_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_JOON_AND_SION_1);
		break;
	case SKL_JOON_AND_SION_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_JOON_AND_SION_2);
		break;
	case SKL_JOON_AND_SION_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_JOON_AND_SION_3);
		break;
	case SKL_JOON_AND_SION_4:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_JOON_AND_SION_4);
		break;
	case SKL_JOON_AND_SION_OFF:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_JOON_AND_SION_OFF);
		break;
	case SKL_MIKO_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_MIKO_1);
		break;
	case SKL_MIKO_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_MIKO_2);
		break;
	case SKL_MIKO_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_MIKO_3);
		break;
	case SKL_MIKO_4:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_MIKO_4);
		break;
	case SKL_MIKO_5:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_MIKO_5);
		break;
	case SKL_MIKO_6:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_MIKO_6);
		break;
	case SKL_PHILOSOPHERS_1:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_PHILOSOPHERS_1);
		break;
	case SKL_PHILOSOPHERS_2:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_PHILOSOPHERS_2);
		break;
	case SKL_PHILOSOPHERS_3:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_PHILOSOPHERS_3);
		break;
	case SKL_PHILOSOPHERS_4:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_PHILOSOPHERS_4);
		break;
	case SKL_PHILOSOPHERS_5:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_PHILOSOPHERS_5);
		break;
	case SKL_SOULSHOT:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SOULSHOT);
		break;
	case SKL_SUPER_GRAZE:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_SUPER_GRAZE);
		break;
	default:
		oss << LocalzationManager::locString(LOC_SYSTEM_SKL_DESCRIBE_UKNOWN);
		break;
	}
	return oss.str();
}



string GetSpellSchoolString(spell_list spell)
{
    std::ostringstream oss;
	for(int i=0;i<3 && SpellSchool(spell,i) != SKT_ERROR;i++)
	{
        if (i > 0)
            oss << "/";
		oss << skill_string(SpellSchool(spell, i));
	}
	return oss.str();
}