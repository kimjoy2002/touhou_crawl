//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: spell.cpp
//
// 내용: 스펠사용건
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "player.h"
#include "skill_use.h"
#include "throw.h"
#include "key.h"
#include "environment.h"
#include "mon_infor.h"
#include "projectile.h"
#include "god.h"
#include "dump.h"
#include "tribe.h"
#include "rect.h"


extern int g_menu_select;
extern HANDLE mutx;

int GetSpellMlen(spell_list spell_, bool isplayer)
{ 
	switch(spell_)
	{
	case SPL_SPARK:
		return SpellLength(spell_, isplayer);
	default:
		break;
	}
	return -1;	
}
float GetSpellSector(spell_list spell_)
{
	switch(spell_)
	{
	case SPL_SPARK:
		return 0.5f;
	case SPL_FIRE_SPREAD:
		return 0.4f;
	default:
		break;
	}
	return 0.0f;
}

bool SpellFlagCheck(spell_list skill, skill_flag flag)
{
	switch(skill)
	{
	case SPL_HASTE_OTHER:
		return ((S_FLAG_OTHER_BUF | S_FLAG_SPEAK) & flag);
	case SPL_HEAL_OTHER:
		return ((S_FLAG_HEAL | S_FLAG_OTHER_BUF | S_FLAG_SPEAK) & flag);
	case SPL_MON_TANMAC_SMALL:
	case SPL_MON_TANMAC_MIDDLE:
	case SPL_MON_WATER_GUN:
	case SPL_MOON_GUN:
	case SPL_THROW_SWORD:
	case SPL_THROW_KNIFE:
	case SPL_THROW_RABBIT:
	case SPL_THROW_POTION:
		return (S_FLAG_CLOSE_DANGER | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_LUMINUS_STRIKE:
		return (S_FLAG_SPEAK | S_FLAG_CLOSE_DANGER | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_CONFUSE_CLOUD:
		return ((S_FLAG_CLOUD | S_FLAG_SPEAK) & flag);
	case SPL_POISON_CLOUD:
	case SPL_MEDICINE_CLOUD:
	case SPL_ICE_CLOUD:
	case SPL_TWIST:
		return ((S_FLAG_CLOUD | S_FLAG_SMITE | S_FLAG_SPEAK) & flag);
	case SPL_WHIRLWIND:
		return ((S_FLAG_SMITE | S_FLAG_SPEAK) & flag);
	case SPL_HEAVENLY_STORM:
		return ((S_FLAG_SMITE | S_FLAG_DELAYED) & flag);
	case SPL_FIRE_WALL:
		return ((S_FLAG_CLOUD | S_FLAG_SMITE | S_FLAG_SPEAK | S_FLAG_NO_COM | S_FLAG_NO_TARGET) & flag);	
	case SPL_COLD_BEAM:
	case SPL_FIRE_BOLT:
	case SPL_ICE_BOLT:
	case SPL_VENOM_BOLT:
	case SPL_LASER:
	case SPL_SPARK:
	case SPL_FIRE_SPREAD:
	case SPL_THUNDER_BOLT:
		return (S_FLAG_PENETRATE | S_FLAG_SPEAK | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_HYPER_BEAM:
		return (S_FLAG_PENETRATE | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_SUMMON_BUG:
	case SPL_SUMMON_PENDULUM:
	case SPL_SUMMON_SEKIBANKI:
	case SPL_SUMMON_MOOK:
	case SPL_SUMMON_BIRD:
	case SPL_SUMMON_OPTION:
	case SPL_SUMMON_GOLEM:
	case SPL_SUMMON_UNZAN:
	case SPL_SUMMON_UFO:
	case SPL_SUMMON_LESSOR_DEMON:
	case SPL_SUMMON_DREAM:
	case SPL_DOLLS_WAR:
	case SPL_FAKE_DOLLS_WAR:
	case SPL_SUMMON_RACOON:
	case SPL_SUMMON_YOUKAI:
	case SPL_SUMMON_YOSHIKA:
	case SPL_SUMMON_TRASH:
	case SPL_SUMMON_ELEC_BALL:
		return (S_FLAG_SUMMON | S_FLAG_SPEAK | S_FLAG_IMMEDIATELY) & flag;
	case SPL_SUMMON_ZOMBIE_FAIRY:
	case SPL_SUMMON_NAMAZ:
	case SPL_SUMMON_GHOST:
		return (S_FLAG_SUMMON | S_FLAG_SPEAK | S_FLAG_SMITE) & flag;
	case SPL_SUMMON_UNZAN_PUNCH:
	case SPL_SUMMON_ANCHOR:
	case SPL_KAGUYA_SPELL:
	case SPL_GROW_VINE:
		return (S_FLAG_SUMMON | S_FLAG_SMITE) & flag;
	case SPL_FLAN_BUSIN:
		return (S_FLAG_SUMMON | S_FLAG_IMMEDIATELY) & flag;
	case SPL_CONFUSE:
	case SPL_SLOW:
	case SPL_GLOW:
	case SPL_TELEPORT_OTHER: 
	case SPL_HYPNOSIS:
	case SPL_SELF_INJURY:
	case SPL_ANIMAL_CHANGE:
	case SPL_STASIS:
	case SPL_TRACKING:
		return (S_FLAG_DEBUF | S_FLAG_SPEAK) & flag;
	case SPL_MIND_BENDING:
		return (S_FLAG_DEBUF | S_FLAG_SPEAK | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_SMOKING:
		return (S_FLAG_DEBUF | S_FLAG_SMITE | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_INSANE:
		return (S_FLAG_DEBUF) & flag;
	case SPL_MEGATON_KICK:
		return ((S_FLAG_DELAYED) & flag);
	case SPL_MUTE:		
	case SPL_CHARM:
		return (S_FLAG_NO_COM | S_FLAG_DEBUF | S_FLAG_SPEAK) & flag;		
	case SPL_SELF_HEAL:
		return (S_FLAG_SEIF | S_FLAG_HEAL | S_FLAG_SPEAK) & flag;
	case SPL_SMITE:
	case SPL_KYOKO_SMITE:
	case SPL_STONE_TRAP:
	case SPL_STONE_UPLIFT:
	case SPL_FREEZE:
	case SPL_FIRE_STORM:
	case SPL_BLIZZARD: 
	case SPL_FIELD_VIOLET:
	case SPL_CONTROLED_BLINK:  
	case SPL_UNLUCK:
	case SPL_THUNDER:
	case SPL_PSYCHOKINESIS:
	case SPL_TRASH_RUSH:
	case SPL_SLEEP_SMITE:
	case SPL_TARGET_ELEC:
	case SPL_REIMU_BARRIER:
		return ((S_FLAG_SMITE | S_FLAG_SPEAK) & flag);
	case SPL_WINDFLAW:
		return ((S_FLAG_SMITE | S_FLAG_SPEAK | S_FLAG_DELAYED) & flag);	
	case SPL_MERMAID_SONG:
	case SPL_HOMING_TANMAC:
		return ((S_FLAG_SMITE | S_FLAG_SPEAK | S_FLAG_CLOSE_DANGER) & flag);	
	case SPL_BURST:
	case SPL_MANA_DRAIN:	
	case SPL_BLOOD_SMITE:
	case SPL_AFTERLITE:
	case SPL_DREAM_CALL:
	case SPL_THROW_PLAYER:
	case SPL_CREATE_FOG:
		return ((S_FLAG_SMITE) & flag);
	case SPL_REAPER_MET:
		return ((S_FLAG_CLOSE_DANGER)& flag);
	case SPL_FLAME:		
	case SPL_FROST:
	case SPL_BURN:
	case SPL_FROZEN:
	case SPL_STING:
	case SPL_MAGIC_TANMAC:
	case SPL_FIRE_BALL:
	case SPL_STONE_ARROW: 
	case SPL_KANAME_DRILL:
	case SPL_WATER_CANNON:
	case SPL_SCHEMA_TANMAC:
	case SPL_AIR_STRIKE:
	case SPL_HANIWA_MAGIC_TANMAC:
	case SPL_HANIWA_MAGIC_TANMAC2:
	case SPL_HANIWA_MAGIC_TANMAC3:
		return (S_FLAG_SPEAK | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_THROW_OIL:
		return (S_FLAG_RANGE_ATTACK) & flag;
	case SPL_CANNON:
	case SPL_NESY_CANNON:
	case SPL_THROW_DISH:
	case SPL_THROW_AMULET:
	case SPL_ARROW:
		return (S_FLAG_RANGE_ATTACK) & flag;
	case SPL_JUMP_ATTACK:
	case SPL_WARP_KICK:
	case SPL_TOUGUE:
		return (S_FLAG_CLOSE_DANGER | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_MACRO_BURST:
		return (S_FLAG_CLOUD | S_FLAG_SPEAK | S_FLAG_DIREC ) & flag;
	case SPL_SHOCK:
		return (S_FLAG_SPEAK | S_FLAG_DIREC  | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_CHAIN_LIGHTNING:
		return (S_FLAG_SPEAK | S_FLAG_PENETRATE| S_FLAG_DIREC | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_TELEPORT_SELF:
	case SPL_DISCHARGE:
	case SPL_LEVITATION:
	case SPL_GRAZE:
	case SPL_VEILING:
	case SPL_INVISIBLE:
	case SPL_HASTE:
	case SPL_SILENCE:
	case SPL_SWIFT:
	case SPL_STONE_PUNCH:
	case SPL_DIAMOND_HARDNESS:
	case SPL_POISON_SKIN:
	case SPL_STONE_FORM:
	case SPL_KNIFE_COLLECT:
	case SPL_AUTUMN_BLADE:
	case SPL_PHILOSOPHERS_STONE:
		return (S_FLAG_BUF | S_FLAG_SPEAK | S_FLAG_IMMEDIATELY) & flag;	
	case SPL_HASTE_ALL:
	case SPL_DISCORD:
		return ((S_FLAG_OTHER_BUF | S_FLAG_SPEAK | S_FLAG_IMMEDIATELY) & flag);
	case SPL_HEAL_ALL:
		return ((S_FLAG_HEAL | S_FLAG_OTHER_BUF | S_FLAG_SPEAK | S_FLAG_IMMEDIATELY) & flag);
	case SPL_BLINK:
	case SPL_RECALL:
	case SPL_RABBIT_HORN:
	case SPL_PERFERT_FREEZE: 
	case SPL_DRAW_POWER:
	case SPL_TIME_PARADOX: 
	case SPL_PRIVATE_SQ: 
	case SPL_THE_WORLD:
	case SPL_CALL_HOUND:
	case SPL_ALERT_NOISE: 
	case SPL_SHATTER:
	case SPL_EMERALD_CITY:
	case SPL_PRISM_CALL:
	case SPL_SANTUARY:
	case SPL_MISTIA_SONG:
	case SPL_MESS_CONFUSION:
	case SPL_ALLROUND_TANMAC:
		return (S_FLAG_SPEAK | S_FLAG_IMMEDIATELY) & flag;
	case SPL_SPEAKER_PHONE:
		return (S_FLAG_SPEAK | S_FLAG_IMMEDIATELY | S_FLAG_DELAYED) & flag;	
	case SPL_MOON_COMMUNICATION:
	case SPL_CHANGE:
	case SPL_KOKORO_CHANGE:
	case SPL_CLOSE_DOOR:
		return (S_FLAG_IMMEDIATELY) & flag;	
	case SPL_CURE_POISON:
	case SPL_FIRE_BRAND:
	case SPL_COLD_BRAND:
	case SPL_POISON_BRAND:
	case SPL_SUICIDE_BOMB: //이건 패시브
	case SPL_MAMIZO_EVADE: //이건 패시브
		return (S_FLAG_SPEAK | S_FLAG_IMMEDIATELY | S_FLAG_NO_COM) & flag;
	default:
		return false;
	}
}

int SpellLength(spell_list skill, bool isPlayer)
{
	int length_ = 7;
	switch(skill)
	{
	case SPL_MON_TANMAC_SMALL:
	case SPL_MON_TANMAC_MIDDLE:
	case SPL_MON_WATER_GUN:
	case SPL_FROST:
	case SPL_MEDICINE_CLOUD:
	case SPL_COLD_BEAM:
	case SPL_CONFUSE:
	case SPL_SLOW:
	case SPL_SMITE:
	case SPL_KYOKO_SMITE:
	case SPL_SHOCK:
	case SPL_CHAIN_LIGHTNING:
	case SPL_GLOW:
	case SPL_MAGIC_TANMAC:
	case SPL_TELEPORT_OTHER:
	case SPL_HYPNOSIS:
	case SPL_MUTE:
	case SPL_SELF_INJURY:
	case SPL_CHARM:
	case SPL_SUMMON_UNZAN_PUNCH:
	case SPL_HASTE_OTHER:
	case SPL_HEAL_OTHER:
	case SPL_BURST:
	case SPL_BLIZZARD: 
	case SPL_PERFERT_FREEZE: 
	case SPL_PRIVATE_SQ:
	case SPL_CONTROLED_BLINK:  
	case SPL_MOON_GUN:
	case SPL_MANA_DRAIN:
	case SPL_INSANE:
	case SPL_BLOOD_SMITE:
	case SPL_STASIS:
	case SPL_SCHEMA_TANMAC:
	case SPL_UNLUCK:
	case SPL_MERMAID_SONG:
	case SPL_REAPER_MET:
	case SPL_TRASH_RUSH:
	case SPL_THROW_DISH:
	case SPL_SLEEP_SMITE:
	case SPL_DREAM_CALL:
	case SPL_THROW_SWORD:
	case SPL_THROW_KNIFE:	
	case SPL_THROW_AMULET:
	case SPL_WARP_KICK:
	case SPL_TRACKING:
	case SPL_HOMING_TANMAC:
	case SPL_ARROW:
	case SPL_HANIWA_MAGIC_TANMAC:
	case SPL_HANIWA_MAGIC_TANMAC2:
	case SPL_HANIWA_MAGIC_TANMAC3:
		length_ = 7;
		break;
	case SPL_FLAME:	
	case SPL_STING:
	case SPL_ICE_BOLT:
	case SPL_POISON_CLOUD:
	case SPL_ICE_CLOUD:
	case SPL_LASER:
	case SPL_SPARK:
	case SPL_STONE_UPLIFT:
	case SPL_LUMINUS_STRIKE:
	case SPL_FIRE_STORM:
	case SPL_FIELD_VIOLET:
	case SPL_CANNON:
	case SPL_NESY_CANNON:
	case SPL_THUNDER_BOLT:
	case SPL_TWIST:
	case SPL_FIRE_BOLT:
	case SPL_VENOM_BOLT:
	case SPL_CONFUSE_CLOUD:
	case SPL_SUMMON_ZOMBIE_FAIRY:
	case SPL_STONE_ARROW: 
	case SPL_FIRE_SPREAD:
	case SPL_SUMMON_NAMAZ:
	case SPL_AIR_STRIKE:
	case SPL_SUMMON_ANCHOR:
	case SPL_TARGET_ELEC:
	case SPL_HYPER_BEAM:
	case SPL_KAGUYA_SPELL:
	case SPL_TOUGUE:
	case SPL_THROW_RABBIT:
	case SPL_THROW_POTION:
		length_ = 6;
		break;
	case SPL_FIRE_BALL:
	case SPL_WATER_CANNON:
	case SPL_MIND_BENDING:
	case SPL_FIRE_WALL:
	case SPL_WHIRLWIND:
	case SPL_STONE_TRAP:
	case SPL_ANIMAL_CHANGE:
	case SPL_JUMP_ATTACK:
	case SPL_KANAME_DRILL:
	case SPL_THUNDER:
	case SPL_AFTERLITE:
	case SPL_PSYCHOKINESIS:
	case SPL_WINDFLAW:
	case SPL_THROW_OIL:
	case SPL_GROW_VINE:
	case SPL_SUMMON_GHOST:
	case SPL_ALLROUND_TANMAC:
		length_ = 5;
		break;
	case SPL_SMOKING:
		length_ = 4;
		break;
	case SPL_BURN:
	case SPL_FREEZE:
		length_ = 2;
		break;
	case SPL_FROZEN:
	case SPL_THROW_PLAYER:
	case SPL_MEGATON_KICK:
		length_ = 1;
		break;
	case SPL_SUMMON_BUG:
	case SPL_SELF_HEAL:
	case SPL_BLINK:
	case SPL_CURE_POISON:
	case SPL_SUMMON_MOOK:
	case SPL_FIRE_BRAND:
	case SPL_COLD_BRAND:
	case SPL_POISON_BRAND:	
	case SPL_DISCHARGE:
	case SPL_LEVITATION:
	case SPL_GRAZE:
	case SPL_VEILING:
	case SPL_INVISIBLE:
	case SPL_HASTE:
	case SPL_SILENCE:
	case SPL_SWIFT:
	case SPL_SUMMON_BIRD:
	case SPL_RECALL:
	case SPL_TELEPORT_SELF:
	case SPL_SUMMON_PENDULUM:
	case SPL_SUMMON_SEKIBANKI:
	case SPL_SUMMON_OPTION:
	case SPL_SUMMON_GOLEM:
	case SPL_SUMMON_UNZAN:
	case SPL_SUMMON_UFO:
	case SPL_STONE_PUNCH:
	case SPL_DIAMOND_HARDNESS:
	case SPL_POISON_SKIN:
	case SPL_STONE_FORM:
	case SPL_KNIFE_COLLECT:
	case SPL_FLAN_BUSIN:
	case SPL_SUICIDE_BOMB:
	case SPL_RABBIT_HORN:
	case SPL_SUMMON_LESSOR_DEMON:
	case SPL_DRAW_POWER:
	case SPL_TIME_PARADOX: 
	case SPL_THE_WORLD:
	case SPL_HASTE_ALL:
	case SPL_HEAL_ALL:
	case SPL_MOON_COMMUNICATION:
	case SPL_SUMMON_DREAM:
	case SPL_CALL_HOUND:
	case SPL_DOLLS_WAR:
	case SPL_FAKE_DOLLS_WAR:
	case SPL_ALERT_NOISE: 
	case SPL_CHANGE:
	case SPL_SUMMON_RACOON:
	case SPL_SUMMON_YOUKAI:
	case SPL_MAMIZO_EVADE:
	case SPL_MACRO_BURST:
	case SPL_SHATTER:
	case SPL_SUMMON_YOSHIKA:
	case SPL_EMERALD_CITY:
	case SPL_AUTUMN_BLADE:
	case SPL_PHILOSOPHERS_STONE:
	case SPL_PRISM_CALL:
	case SPL_SUMMON_TRASH:
	case SPL_KOKORO_CHANGE:
	case SPL_SANTUARY:
	case SPL_MISTIA_SONG:
	case SPL_MESS_CONFUSION:
	case SPL_SUMMON_ELEC_BALL:
	case SPL_REIMU_BARRIER:
	case SPL_HEAVENLY_STORM:
	case SPL_DISCORD:
	case SPL_CREATE_FOG:
	case SPL_CLOSE_DOOR:
	case SPL_SPEAKER_PHONE:
	default:
		length_ = 0;
		break;		
	}
	return (isPlayer&&isShootingSprint())?2 *length_ :length_;
}

string SpellString(spell_list skill)
{
	switch(skill)
	{
	case SPL_MON_TANMAC_SMALL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MON_TANMAC_SMALL);
	case SPL_MON_TANMAC_MIDDLE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MON_TANMAC_MIDDLE);
	case SPL_MON_WATER_GUN:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MON_WATER_GUN);
	case SPL_FROST:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FROST);
	case SPL_MEDICINE_CLOUD:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MEDICINE_CLOUD);
	case SPL_COLD_BEAM:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_COLD_BEAM);
	case SPL_CONFUSE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CONFUSE);
	case SPL_SLOW:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SLOW);
	case SPL_SMITE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SMITE);
	case SPL_FLAME:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FLAME);	
	case SPL_SUMMON_BUG:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_BUG);
	case SPL_SELF_HEAL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SELF_HEAL);
	case SPL_BLINK:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_BLINK);
	case SPL_BURN:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_BURN);
	case SPL_FROZEN:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FROZEN);
	case SPL_FIRE_WALL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FIRE_WALL);
	case SPL_FREEZE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FREEZE);
	case SPL_STING:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_STING);
	case SPL_CURE_POISON:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CURE_POISON);
	case SPL_TWIST:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_TWIST);
	case SPL_SUMMON_MOOK:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_MOOK);
	case SPL_FIRE_BRAND:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FIRE_BRAND);
	case SPL_COLD_BRAND:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_COLD_BRAND);
	case SPL_POISON_BRAND:	
		return LocalzationManager::locString(LOC_SYSTEM_SPL_POISON_BRAND);
	case SPL_SHOCK:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SHOCK);
	case SPL_CHAIN_LIGHTNING:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CHAIN_LIGHTNING);
	case SPL_DISCHARGE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_DISCHARGE);
	case SPL_LEVITATION:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_LEVITATION);
	case SPL_GLOW:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_GLOW);
	case SPL_GRAZE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_GRAZE);
	case SPL_VEILING:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_VEILING);
	case SPL_INVISIBLE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_INVISIBLE);
	case SPL_HASTE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HASTE);
	case SPL_SILENCE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SILENCE);
	case SPL_SWIFT:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SWIFT);
	case SPL_MAGIC_TANMAC:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MAGIC_TANMAC);
	case SPL_FIRE_BALL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FIRE_BALL);
	case SPL_FIRE_BOLT:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FIRE_BOLT);
	case SPL_ICE_BOLT:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_ICE_BOLT);
	case SPL_VENOM_BOLT:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_VENOM_BOLT);
	case SPL_CONFUSE_CLOUD:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CONFUSE_CLOUD);
	case SPL_POISON_CLOUD:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_POISON_CLOUD);
	case SPL_ICE_CLOUD:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_ICE_CLOUD);
	case SPL_SUMMON_BIRD:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_BIRD);
	case SPL_RECALL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_RECALL);
	case SPL_TELEPORT_OTHER:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_TELEPORT_OTHER);
	case SPL_TELEPORT_SELF:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_TELEPORT_SELF);
	case SPL_WHIRLWIND:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_WHIRLWIND);
	case SPL_SUMMON_PENDULUM:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_PENDULUM);
	case SPL_SUMMON_SEKIBANKI:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_SEKIBANKI);
	case SPL_WATER_CANNON:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_WATER_CANNON);
	case SPL_KYOKO_SMITE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_KYOKO_SMITE);
	case SPL_SUMMON_OPTION:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_OPTION);
	case SPL_SUMMON_GOLEM:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_GOLEM);
	case SPL_HYPNOSIS:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HYPNOSIS);
	case SPL_MUTE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MUTE);
	case SPL_SELF_INJURY:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SELF_INJURY);
	case SPL_CHARM:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CHARM);
	case SPL_LASER:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_LASER);
	case SPL_SPARK:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SPARK);
	case SPL_SUMMON_UNZAN:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_UNZAN);
	case SPL_SUMMON_UNZAN_PUNCH:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_UNZAN_PUNCH);
	case SPL_SUMMON_ZOMBIE_FAIRY:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_ZOMBIE_FAIRY);
	case SPL_SUMMON_UFO:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_UFO);
	case SPL_HASTE_OTHER:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HASTE_OTHER);
	case SPL_HEAL_OTHER:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HEAL_OTHER);
	case SPL_MIND_BENDING:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MIND_BENDING);
	case SPL_STONE_PUNCH:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_STONE_PUNCH);
	case SPL_STONE_ARROW: 
		return LocalzationManager::locString(LOC_SYSTEM_SPL_STONE_ARROW);
	case SPL_STONE_TRAP:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_STONE_TRAP);
	case SPL_STONE_UPLIFT:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_STONE_UPLIFT);
	case SPL_KANAME_DRILL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_KANAME_DRILL);
	case SPL_DIAMOND_HARDNESS:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_DIAMOND_HARDNESS);
	case SPL_POISON_SKIN:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_POISON_SKIN);
	case SPL_STONE_FORM:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_STONE_FORM);
	case SPL_KNIFE_COLLECT:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_KNIFE_COLLECT);
	case SPL_FLAN_BUSIN:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FLAN_BUSIN);
	case SPL_BURST:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_BURST);
	case SPL_SUICIDE_BOMB:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUICIDE_BOMB);
	case SPL_RABBIT_HORN:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_RABBIT_HORN);
	case SPL_SUMMON_LESSOR_DEMON:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_LESSOR_DEMON);
	case SPL_LUMINUS_STRIKE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_LUMINUS_STRIKE);
	case SPL_FIRE_STORM:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FIRE_STORM);
	case SPL_BLIZZARD: 
		return LocalzationManager::locString(LOC_SYSTEM_SPL_BLIZZARD);
	case SPL_PERFERT_FREEZE: 
		return LocalzationManager::locString(LOC_SYSTEM_SPL_PERFERT_FREEZE);
	case SPL_DRAW_POWER:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_DRAW_POWER);
	case SPL_ANIMAL_CHANGE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_ANIMAL_CHANGE);
	case SPL_FIELD_VIOLET:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FIELD_VIOLET);
	case SPL_TIME_PARADOX: 
		return LocalzationManager::locString(LOC_SYSTEM_SPL_TIME_PARADOX);
	case SPL_PRIVATE_SQ: 
		return LocalzationManager::locString(LOC_SYSTEM_SPL_PRIVATE_SQ);
	case SPL_CONTROLED_BLINK: 
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CONTROLED_BLINK);
	case SPL_THE_WORLD:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THE_WORLD);
	case SPL_HASTE_ALL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HASTE_ALL);
	case SPL_HEAL_ALL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HEAL_ALL);
	case SPL_MOON_COMMUNICATION:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MOON_COMMUNICATION);
	case SPL_MOON_GUN:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MOON_GUN);
	case SPL_SUMMON_DREAM:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_DREAM);
	case SPL_MANA_DRAIN:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MANA_DRAIN);
	case SPL_INSANE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_INSANE);
	case SPL_BLOOD_SMITE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_BLOOD_SMITE);
	case SPL_CALL_HOUND:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CALL_HOUND);
	case SPL_CANNON:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CANNON);
	case SPL_DOLLS_WAR:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_DOLLS_WAR);
	case SPL_FAKE_DOLLS_WAR:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FAKE_DOLLS_WAR);
	case SPL_FIRE_SPREAD:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_FIRE_SPREAD);
	case SPL_STASIS:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_STASIS);
	case SPL_JUMP_ATTACK:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_JUMP_ATTACK);
	case SPL_ALERT_NOISE: 
		return LocalzationManager::locString(LOC_SYSTEM_SPL_ALERT_NOISE);
	case SPL_SUMMON_NAMAZ:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_NAMAZ);		
	case SPL_SCHEMA_TANMAC:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SCHEMA_TANMAC);
	case SPL_CHANGE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CHANGE);
	case SPL_UNLUCK:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_UNLUCK);
	case SPL_THUNDER:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THUNDER);
	case SPL_AIR_STRIKE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_AIR_STRIKE);
	case SPL_SUMMON_RACOON:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_RACOON);
	case SPL_SUMMON_YOUKAI:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_YOUKAI);
	case SPL_MAMIZO_EVADE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MAMIZO_EVADE);
	case SPL_MACRO_BURST:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MACRO_BURST);
	case SPL_SHATTER:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SHATTER);
	case SPL_SUMMON_YOSHIKA:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_YOSHIKA);
	case SPL_NESY_CANNON:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_NESY_CANNON);
	case SPL_MERMAID_SONG:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MERMAID_SONG);
	case SPL_EMERALD_CITY:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_EMERALD_CITY);
	case SPL_AUTUMN_BLADE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_AUTUMN_BLADE);
	case SPL_PHILOSOPHERS_STONE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_PHILOSOPHERS_STONE);
	case SPL_SUMMON_ANCHOR:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_ANCHOR);
	case SPL_REAPER_MET:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_REAPER_MET);
	case SPL_AFTERLITE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_AFTERLITE);
	case SPL_PRISM_CALL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_PRISM_CALL);
	case SPL_PSYCHOKINESIS:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_PSYCHOKINESIS);
	case SPL_SUMMON_TRASH:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_TRASH);
	case SPL_TRASH_RUSH:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_TRASH_RUSH);
	case SPL_KOKORO_CHANGE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_KOKORO_CHANGE);
	case SPL_THUNDER_BOLT:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THUNDER_BOLT);
	case SPL_SANTUARY:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SANTUARY);
	case SPL_MISTIA_SONG:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MISTIA_SONG);
	case SPL_THROW_DISH:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THROW_DISH);
	case SPL_MESS_CONFUSION:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MESS_CONFUSION);
	case SPL_SLEEP_SMITE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SLEEP_SMITE);
	case SPL_TARGET_ELEC:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_TARGET_ELEC);
	case SPL_SUMMON_ELEC_BALL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_ELEC_BALL);
	case SPL_DREAM_CALL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_DREAM_CALL);
	case SPL_HYPER_BEAM:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HYPER_BEAM);
	case SPL_KAGUYA_SPELL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_KAGUYA_SPELL);
	case SPL_THROW_SWORD:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THROW_SWORD);
	case SPL_THROW_KNIFE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THROW_KNIFE);
	case SPL_THROW_PLAYER:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THROW_PLAYER);
	case SPL_THROW_AMULET:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THROW_AMULET);
	case SPL_WARP_KICK:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_WARP_KICK);
	case SPL_REIMU_BARRIER:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_REIMU_BARRIER);
	case SPL_TOUGUE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_TOUGUE);
	case SPL_WINDFLAW:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_WINDFLAW);
	case SPL_SUMMON_GHOST:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SUMMON_GHOST);
	case SPL_MEGATON_KICK:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_MEGATON_KICK);
	case SPL_THROW_OIL:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THROW_OIL);
	case SPL_HEAVENLY_STORM:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HEAVENLY_STORM);
	case SPL_TRACKING:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_TRACKING);
	case SPL_DISCORD:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_DISCORD);
	case SPL_SMOKING:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SMOKING);
	case SPL_CREATE_FOG:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CREATE_FOG);
	case SPL_GROW_VINE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_GROW_VINE);
	case SPL_CLOSE_DOOR:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_CLOSE_DOOR);
	case SPL_SPEAKER_PHONE:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_SPEAKER_PHONE);
	case SPL_HOMING_TANMAC:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HOMING_TANMAC);
	case SPL_ALLROUND_TANMAC:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_ALLROUND_TANMAC);
	case SPL_THROW_RABBIT:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THROW_RABBIT);
	case SPL_THROW_POTION:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_THROW_POTION);
	case SPL_ARROW:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_ARROW);
	case SPL_HANIWA_MAGIC_TANMAC:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HANIWA_MAGIC_TANMAC);
	case SPL_HANIWA_MAGIC_TANMAC2:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HANIWA_MAGIC_TANMAC2);
	case SPL_HANIWA_MAGIC_TANMAC3:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_HANIWA_MAGIC_TANMAC3);
	default:
		return LocalzationManager::locString(LOC_SYSTEM_SPL_UKNOWN);
	}
}
int SpellLevel(spell_list skill)
{
	switch(skill)
	{
	case SPL_MON_TANMAC_SMALL:
	case SPL_BURN:
	case SPL_FROZEN:
	case SPL_STING:
	case SPL_SUMMON_MOOK:
	case SPL_SHOCK:
	case SPL_GLOW:
	case SPL_VEILING:
	case SPL_MAGIC_TANMAC:
	case SPL_HYPNOSIS:
	case SPL_STONE_PUNCH:	
	case SPL_SCHEMA_TANMAC:
		return 1;
	case SPL_FLAME:	
	case SPL_SELF_HEAL:
	case SPL_BLINK:
	case SPL_MON_WATER_GUN:
	case SPL_FROST:
	case SPL_CURE_POISON:
	case SPL_TWIST:
	case SPL_SLOW:
	case SPL_SUMMON_BUG:
	case SPL_FIRE_BRAND:
	case SPL_COLD_BRAND:
	case SPL_LEVITATION:
	case SPL_GRAZE:
	case SPL_SWIFT:
	case SPL_SUMMON_OPTION:
	case SPL_MUTE:
	case SPL_MIND_BENDING:
	case SPL_STONE_ARROW: 
	case SPL_DIAMOND_HARDNESS:
	case SPL_DRAW_POWER:
	case SPL_SPEAKER_PHONE:
	case SPL_HOMING_TANMAC:
	case SPL_ARROW:
	case SPL_HANIWA_MAGIC_TANMAC:
		return 2;
	case SPL_CONFUSE:
	case SPL_FREEZE:
	case SPL_FIRE_WALL:
	case SPL_MON_TANMAC_MIDDLE:
	case SPL_POISON_BRAND:
	case SPL_CONFUSE_CLOUD:
	case SPL_RECALL:
	case SPL_TELEPORT_OTHER:
	case SPL_SUMMON_BIRD:
	case SPL_SELF_INJURY:
	case SPL_STONE_TRAP:
	case SPL_POISON_SKIN:
	case SPL_ALERT_NOISE: 
	case SPL_MERMAID_SONG:
	case SPL_PRISM_CALL:
	case SPL_TARGET_ELEC:
	case SPL_GROW_VINE:
		return 3;
	case SPL_SMITE:
	case SPL_FIRE_BALL:
	case SPL_WHIRLWIND:
	case SPL_DISCHARGE:
	case SPL_SUMMON_PENDULUM:
	case SPL_WATER_CANNON:
	case SPL_SUMMON_GOLEM:
	case SPL_CHARM:
	case SPL_LASER:
	case SPL_KNIFE_COLLECT:
	case SPL_RABBIT_HORN:
	case SPL_TIME_PARADOX: 
	case SPL_AIR_STRIKE:
	case SPL_NESY_CANNON:
	case SPL_MISTIA_SONG:
	case SPL_THROW_DISH:
	case SPL_SLEEP_SMITE:
	case SPL_THROW_KNIFE:
	case SPL_WARP_KICK:
	case SPL_TOUGUE:
	case SPL_WINDFLAW:
	case SPL_CREATE_FOG:
	case SPL_CLOSE_DOOR:
	case SPL_HANIWA_MAGIC_TANMAC2:
		return 4;
	case SPL_SILENCE:
	case SPL_VENOM_BOLT:
	case SPL_POISON_CLOUD:
	case SPL_TELEPORT_SELF:
	case SPL_KYOKO_SMITE:
	case SPL_SUMMON_ZOMBIE_FAIRY:
	case SPL_HASTE_OTHER:
	case SPL_HEAL_OTHER:
	case SPL_SUMMON_LESSOR_DEMON:
	case SPL_ANIMAL_CHANGE:
	case SPL_INSANE:
	case SPL_FAKE_DOLLS_WAR:
	case SPL_STASIS:
	case SPL_JUMP_ATTACK:
	case SPL_THUNDER:
	case SPL_EMERALD_CITY:
	case SPL_STONE_UPLIFT:
	case SPL_SUMMON_ANCHOR:
	case SPL_PSYCHOKINESIS:
	case SPL_SUMMON_TRASH:
	case SPL_THROW_AMULET:
	case SPL_TRACKING:
	case SPL_ALLROUND_TANMAC:
		return 5;
	case SPL_COLD_BEAM:
	case SPL_CHAIN_LIGHTNING:
	case SPL_INVISIBLE:
	case SPL_HASTE:
	case SPL_FIRE_BOLT:
	case SPL_ICE_BOLT:
	case SPL_ICE_CLOUD:
	case SPL_SUMMON_SEKIBANKI:
	case SPL_SUMMON_UNZAN:
	case SPL_SUMMON_UNZAN_PUNCH:
	case SPL_SUMMON_UFO:
	case SPL_KANAME_DRILL:
	case SPL_SUICIDE_BOMB:
	case SPL_PRIVATE_SQ: 
	case SPL_MOON_COMMUNICATION:
	case SPL_MANA_DRAIN:
	case SPL_BLOOD_SMITE:
	case SPL_CHANGE:
	case SPL_MAMIZO_EVADE:
	case SPL_SUMMON_YOSHIKA:
	case SPL_KOKORO_CHANGE:
	case SPL_THUNDER_BOLT:
	case SPL_MESS_CONFUSION:
	case SPL_THROW_SWORD:
	case SPL_SUMMON_GHOST:
	case SPL_DISCORD:
	case SPL_SMOKING:
	case SPL_THROW_RABBIT:
	case SPL_THROW_POTION:
	case SPL_HANIWA_MAGIC_TANMAC3:
		return 6;
	case SPL_MEDICINE_CLOUD:
	case SPL_STONE_FORM:
	case SPL_LUMINUS_STRIKE:
	case SPL_CONTROLED_BLINK: 
	case SPL_FIELD_VIOLET:
	case SPL_MOON_GUN:
	case SPL_SUMMON_DREAM:
	case SPL_CALL_HOUND:
	case SPL_SUMMON_NAMAZ:
	case SPL_SUMMON_RACOON:
	case SPL_SUMMON_YOUKAI:
	case SPL_AUTUMN_BLADE:
	case SPL_REAPER_MET:
	case SPL_SUMMON_ELEC_BALL:
	case SPL_THROW_PLAYER:
	case SPL_THROW_OIL:
		return 7;
	case SPL_SPARK:
	case SPL_BLIZZARD: 
	case SPL_DOLLS_WAR:
	case SPL_HASTE_ALL:
	case SPL_HEAL_ALL:
	case SPL_CANNON:
	case SPL_FIRE_SPREAD:
	case SPL_UNLUCK:
	case SPL_MACRO_BURST:
	case SPL_TRASH_RUSH:
	case SPL_DREAM_CALL:
	case SPL_HYPER_BEAM:
	case SPL_KAGUYA_SPELL:
	case SPL_HEAVENLY_STORM:
	case SPL_MEGATON_KICK:
		return 8;
	case SPL_FLAN_BUSIN:
	case SPL_BURST:
	case SPL_FIRE_STORM:
	case SPL_PERFERT_FREEZE: 
	case SPL_THE_WORLD:
	case SPL_SHATTER:
	case SPL_PHILOSOPHERS_STONE:
	case SPL_AFTERLITE:
	case SPL_SANTUARY:
	case SPL_REIMU_BARRIER:
		return 9;
	default:
		return 0;
	}
}

int SpellNoise(spell_list skill)
{
	switch(skill)
	{
	case SPL_BURN:
	case SPL_FROZEN:
	case SPL_MON_TANMAC_SMALL:
	case SPL_SUMMON_MOOK:
	case SPL_GLOW:
	case SPL_MAGIC_TANMAC:
	case SPL_HYPNOSIS:
	case SPL_BLINK:
	case SPL_SELF_HEAL:
	case SPL_LEVITATION:
	case SPL_GRAZE:
	case SPL_SWIFT:
	case SPL_SILENCE:
	case SPL_STONE_PUNCH:
	case SPL_STONE_TRAP:
	case SPL_DRAW_POWER:
	case SPL_MANA_DRAIN:	
	case SPL_SCHEMA_TANMAC:
	case SPL_CHANGE:
	case SPL_UNLUCK:
	case SPL_MAMIZO_EVADE:
	case SPL_PRISM_CALL:
	case SPL_SLEEP_SMITE:
		return 0;//소음없음
	case SPL_SHOCK:
	case SPL_VEILING:
	case SPL_STING:
	case SPL_FLAME:	
	case SPL_MON_WATER_GUN:
	case SPL_FROST:
	case SPL_CURE_POISON:
	case SPL_TWIST:
	case SPL_SLOW:
	case SPL_SUMMON_BUG:
	case SPL_FIRE_BRAND:
	case SPL_COLD_BRAND:
	case SPL_MUTE:
	case SPL_CONFUSE:
	case SPL_FIRE_WALL:
	case SPL_MIND_BENDING:
	case SPL_STONE_ARROW: 
	case SPL_DIAMOND_HARDNESS:
	case SPL_POISON_SKIN:
	case SPL_STONE_FORM:
	case SPL_KNIFE_COLLECT:
	case SPL_ANIMAL_CHANGE:
	case SPL_TIME_PARADOX: 
	case SPL_PRIVATE_SQ: 
	case SPL_THE_WORLD:
	case SPL_MOON_COMMUNICATION:
	case SPL_INSANE:
	case SPL_BLOOD_SMITE:
	case SPL_STASIS:
	case SPL_JUMP_ATTACK:
	case SPL_AIR_STRIKE:
	case SPL_SUMMON_YOSHIKA:
	case SPL_REAPER_MET:
	case SPL_PSYCHOKINESIS:
	case SPL_KOKORO_CHANGE:
	case SPL_THROW_DISH:
	case SPL_MESS_CONFUSION:
	case SPL_TARGET_ELEC:
	case SPL_THROW_SWORD:
	case SPL_THROW_KNIFE:
	case SPL_THROW_AMULET:
	case SPL_WARP_KICK:
	case SPL_SMOKING:
	case SPL_GROW_VINE:
	case SPL_HOMING_TANMAC:
	case SPL_THROW_POTION:
	case SPL_THROW_RABBIT:
	case SPL_ARROW:
	case SPL_HANIWA_MAGIC_TANMAC:
		return 4; //적은 소음
	case SPL_SUMMON_OPTION:
	case SPL_FREEZE:
	case SPL_MON_TANMAC_MIDDLE:
	case SPL_POISON_BRAND:
	case SPL_CONFUSE_CLOUD:
	case SPL_RECALL:
	case SPL_TELEPORT_OTHER:
	case SPL_SUMMON_BIRD:
	case SPL_SELF_INJURY:
	case SPL_SMITE:
	case SPL_SUMMON_PENDULUM:
	case SPL_WATER_CANNON:
	case SPL_SUMMON_GOLEM:
	case SPL_CHARM:
	case SPL_DISCHARGE:
	case SPL_LASER:
	case SPL_VENOM_BOLT:
	case SPL_POISON_CLOUD:
	case SPL_TELEPORT_SELF:
	case SPL_SUMMON_ZOMBIE_FAIRY:
	case SPL_HASTE_OTHER:
	case SPL_HEAL_OTHER:
	case SPL_COLD_BEAM:
	case SPL_INVISIBLE:
	case SPL_HASTE:
	case SPL_FIRE_BOLT:
	case SPL_ICE_BOLT:
	case SPL_ICE_CLOUD:
	case SPL_SUMMON_SEKIBANKI:
	case SPL_SUMMON_UNZAN:
	case SPL_SUMMON_UNZAN_PUNCH:
	case SPL_SUMMON_UFO:
	case SPL_MEDICINE_CLOUD:
	case SPL_KANAME_DRILL:
	case SPL_FLAN_BUSIN:
	case SPL_SUMMON_LESSOR_DEMON:
	case SPL_LUMINUS_STRIKE:
	case SPL_FIELD_VIOLET:
	case SPL_CONTROLED_BLINK: 
	case SPL_HASTE_ALL:
	case SPL_HEAL_ALL:
	case SPL_MOON_GUN:
	case SPL_SUMMON_DREAM:
	case SPL_DOLLS_WAR:
	case SPL_FAKE_DOLLS_WAR:
	case SPL_SUMMON_NAMAZ:
	case SPL_SUMMON_RACOON:
	case SPL_SUMMON_YOUKAI:
	case SPL_MACRO_BURST:
	case SPL_NESY_CANNON:
	case SPL_MERMAID_SONG:
	case SPL_EMERALD_CITY:
	case SPL_AUTUMN_BLADE:
	case SPL_AFTERLITE:
	case SPL_SUMMON_TRASH:
	case SPL_DREAM_CALL:
	case SPL_THROW_PLAYER:
	case SPL_TOUGUE:
	case SPL_WINDFLAW:
	case SPL_SUMMON_GHOST:
	case SPL_TRACKING:
	case SPL_DISCORD:
	case SPL_CLOSE_DOOR:
	case SPL_ALLROUND_TANMAC:
	case SPL_HANIWA_MAGIC_TANMAC2:
	case SPL_HANIWA_MAGIC_TANMAC3:
		return 8; //기본 소음
	case SPL_FIRE_BALL:
	case SPL_WHIRLWIND:
	case SPL_CHAIN_LIGHTNING:
	case SPL_BURST:
	case SPL_SUICIDE_BOMB:
	case SPL_RABBIT_HORN:
	case SPL_BLIZZARD: 
	case SPL_PERFERT_FREEZE: 
	case SPL_CALL_HOUND:
	case SPL_CANNON:
	case SPL_FIRE_SPREAD:
	case SPL_STONE_UPLIFT:
	case SPL_THUNDER:
	case SPL_PHILOSOPHERS_STONE:
	case SPL_SUMMON_ANCHOR:
	case SPL_TRASH_RUSH:
	case SPL_THUNDER_BOLT:
	case SPL_SUMMON_ELEC_BALL:
	case SPL_HYPER_BEAM:
	case SPL_KAGUYA_SPELL:
	case SPL_MEGATON_KICK:
	case SPL_THROW_OIL:
	case SPL_CREATE_FOG:
		return 12; //상당한 소음 시야밖까지 영향
	case SPL_KYOKO_SMITE:
	case SPL_SPARK:
	case SPL_FIRE_STORM:
	case SPL_SANTUARY:
	case SPL_MISTIA_SONG:
	case SPL_REIMU_BARRIER:
	case SPL_HEAVENLY_STORM:
	case SPL_SPEAKER_PHONE:
		return 16; //굉장한 소음
	case SPL_ALERT_NOISE: 
	case SPL_SHATTER:
		return 24; //대형소음
	default:
		return 0;
	}
}



int SpellSpeed(spell_list skill)
{
	switch(skill)
	{
	case SPL_AIR_STRIKE:
		return 5;
	default:
		return 10;
	}
}
int Spellsize(spell_list skill)
{	
	switch(skill)
	{
	case SPL_FIRE_STORM:
		return 2;
	case SPL_FIRE_BALL:
	case SPL_BURST:
	case SPL_ICE_CLOUD:
	case SPL_STONE_UPLIFT:
	case SPL_POISON_CLOUD:
	case SPL_CONFUSE_CLOUD:
	case SPL_THUNDER:
		return 1;
	default:
		return 0;
	}
}
skill_type SpellSchool(spell_list skill, int num)
{
	switch(skill)
	{
	case SPL_MON_TANMAC_SMALL:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_MON_TANMAC_MIDDLE:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_MON_WATER_GUN:
		return num==0?(SKT_COLD):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FROST:
		return num==0?(SKT_COLD):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_MEDICINE_CLOUD:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_AIR):(SKT_CONJURE);
	case SPL_COLD_BEAM:
		return num==0?(SKT_COLD):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_CONFUSE:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SLOW:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SMITE:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FLAME:
		return num==0?(SKT_FIRE):num==1?(SKT_CONJURE):(SKT_ERROR);	
	case SPL_SUMMON_BUG:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SELF_HEAL:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_BLINK:
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_BURN:
		return num==0?(SKT_FIRE):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_FROZEN:
		return num==0?(SKT_COLD):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FIRE_WALL:
		return num==0?(SKT_FIRE):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_FREEZE:
		return num==0?(SKT_COLD):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_STING:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_CURE_POISON:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_TWIST:
		return num==0?(SKT_AIR):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_SUMMON_MOOK:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FIRE_BRAND:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_FIRE):(SKT_ERROR);
	case SPL_COLD_BRAND:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_COLD):(SKT_ERROR);
	case SPL_POISON_BRAND:	
		return num==0?(SKT_ALCHEMY):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SHOCK:
		return num==0?(SKT_AIR):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_CHAIN_LIGHTNING:
		return num==0?(SKT_AIR):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_DISCHARGE:
		return num==0?(SKT_AIR):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_LEVITATION:
		return num==0?(SKT_AIR):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_GLOW:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_GRAZE:
		return num==0?(SKT_AIR):num==1?(SKT_ALCHEMY):(SKT_ERROR);
	case SPL_VEILING:
		return num==0?(SKT_AIR):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_INVISIBLE:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_HASTE:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SILENCE:
		return num==0?(SKT_MENTAL):num==1?(SKT_AIR):(SKT_ERROR);
	case SPL_SWIFT:
		return num==0?(SKT_AIR):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_MAGIC_TANMAC:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FIRE_BALL:
		return num==0?(SKT_FIRE):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_FIRE_BOLT:
		return num==0?(SKT_FIRE):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_ICE_BOLT:
		return num==0?(SKT_COLD):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_VENOM_BOLT:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_CONFUSE_CLOUD:
		return num==0?(SKT_CONJURE):num==1?(SKT_ALCHEMY):(SKT_AIR);
	case SPL_POISON_CLOUD:
		return num==0?(SKT_CONJURE):num==1?(SKT_ALCHEMY):(SKT_AIR);
	case SPL_ICE_CLOUD:
		return num==0?(SKT_CONJURE):num==1?(SKT_COLD):(SKT_AIR);
	case SPL_SUMMON_BIRD:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_RECALL:
		return num==0?(SKT_SUMMON):num==1?(SKT_TRANS):(SKT_ERROR);
	case SPL_TELEPORT_OTHER:
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_TELEPORT_SELF:
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_WHIRLWIND:
		return num==0?(SKT_CONJURE):num==1?(SKT_AIR):(SKT_ERROR);
	case SPL_SUMMON_PENDULUM:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);		
	case SPL_SUMMON_SEKIBANKI:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);		
	case SPL_WATER_CANNON:
		return num==0?(SKT_COLD):num==1?(SKT_CONJURE):(SKT_ERROR);	
	case SPL_KYOKO_SMITE:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_SUMMON_OPTION:
		return num==0?(SKT_SUMMON):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_SUMMON_GOLEM:
		return num==0?(SKT_SUMMON):num==1?(SKT_ALCHEMY):(SKT_ERROR);
	case SPL_HYPNOSIS:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_MUTE:
		return num==0?(SKT_MENTAL):num==1?(SKT_ALCHEMY):(SKT_ERROR);
	case SPL_SELF_INJURY:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_CHARM:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_LASER:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SPARK:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SUMMON_UNZAN:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SUMMON_UNZAN_PUNCH:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SUMMON_ZOMBIE_FAIRY:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);		
	case SPL_SUMMON_UFO:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_HASTE_OTHER:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_HEAL_OTHER:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_MIND_BENDING:
		return num==0?(SKT_MENTAL):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_STONE_PUNCH:
		return num==0?(SKT_EARTH):num==1?(SKT_ALCHEMY):(SKT_ERROR);
	case SPL_STONE_ARROW: 
		return num==0?(SKT_EARTH):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_STONE_TRAP:
		return num==0?(SKT_EARTH):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_STONE_UPLIFT:
		return num==0?(SKT_EARTH):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_KANAME_DRILL:
		return num==0?(SKT_EARTH):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_DIAMOND_HARDNESS:
		return num==0?(SKT_EARTH):num==1?(SKT_ALCHEMY):(SKT_ERROR);
	case SPL_POISON_SKIN:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_STONE_FORM:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_EARTH):(SKT_ERROR);
	case SPL_KNIFE_COLLECT:
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FLAN_BUSIN:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_BURST:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SUICIDE_BOMB:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_RABBIT_HORN:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SUMMON_LESSOR_DEMON:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_LUMINUS_STRIKE:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FIRE_STORM:
		return num==0?(SKT_FIRE):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_BLIZZARD: 
		return num==0?(SKT_COLD):num==1?(SKT_CONJURE):(SKT_ERROR);
	case SPL_PERFERT_FREEZE: 
		return num==0?(SKT_COLD):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_DRAW_POWER:
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_ANIMAL_CHANGE:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FIELD_VIOLET:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_TIME_PARADOX: 
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_PRIVATE_SQ: 
		return num==0?(SKT_MENTAL):num==1?(SKT_TRANS):(SKT_ERROR);
	case SPL_CONTROLED_BLINK: 
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_THE_WORLD:
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_HASTE_ALL:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_HEAL_ALL:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_MOON_COMMUNICATION:
		return num==0?(SKT_MENTAL):num==1?(SKT_SUMMON):(SKT_ERROR);
	case SPL_MOON_GUN:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SUMMON_DREAM:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_MANA_DRAIN:
		return num==0?(SKT_CONJURE):num==1?(SKT_MENTAL):(SKT_ERROR);
	case SPL_INSANE:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_BLOOD_SMITE:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_CALL_HOUND:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_CANNON:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_DOLLS_WAR:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FAKE_DOLLS_WAR:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_FIRE_SPREAD:
		return num==0?(SKT_FIRE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_STASIS:
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_JUMP_ATTACK:
		return num==0?(SKT_AIR):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_ALERT_NOISE: 
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SUMMON_NAMAZ:
		return num==0?(SKT_SUMMON):num==1?(SKT_EARTH):(SKT_ERROR);	
	case SPL_SCHEMA_TANMAC:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_CHANGE:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_UNLUCK:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_THUNDER:
		return num==0?(SKT_AIR):num==1?(SKT_CONJURE):(SKT_ERROR);	
	case SPL_AIR_STRIKE:
		return num==0?(SKT_AIR):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_SUMMON_RACOON:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_SUMMON_YOUKAI:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_MAMIZO_EVADE:
		return num==0?(SKT_TRANS):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_MACRO_BURST:
		return num==0?(SKT_AIR):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_SHATTER:
		return num==0?(SKT_EARTH):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_SUMMON_YOSHIKA:
		return num==0?(SKT_SUMMON):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_NESY_CANNON:
		return num==0?(SKT_CONJURE):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_MERMAID_SONG:
		return num==0?(SKT_MENTAL):num==1?(SKT_ERROR):(SKT_ERROR);	
	case SPL_EMERALD_CITY:
		return num==0?(SKT_EARTH):num==1?(SKT_ALCHEMY):(SKT_ERROR);
	case SPL_AUTUMN_BLADE:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_PHILOSOPHERS_STONE:
		return num==0?(SKT_ALCHEMY):num==1?(SKT_ERROR):(SKT_ERROR);
	case SPL_SUMMON_ANCHOR:
		return num == 0 ? (SKT_SUMMON) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_REAPER_MET:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_TRANS) : (SKT_ERROR);
	case SPL_AFTERLITE:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_CONJURE) : (SKT_ERROR);
	case SPL_PRISM_CALL:
		return num == 0 ? (SKT_TRANS) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_PSYCHOKINESIS:
		return num == 0 ? (SKT_TRANS) : num == 1 ? (SKT_MENTAL) : (SKT_ERROR);
	case SPL_SUMMON_TRASH:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_TRASH_RUSH:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_KOKORO_CHANGE:
		return num == 0 ? (SKT_ALCHEMY) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_THUNDER_BOLT:
		return num == 0 ? (SKT_AIR) : num == 1 ? (SKT_CONJURE) : (SKT_ERROR);
	case SPL_SANTUARY:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_MISTIA_SONG:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_THROW_DISH:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_MESS_CONFUSION:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_SLEEP_SMITE:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_TARGET_ELEC:
		return num == 0 ? (SKT_AIR) : num == 1 ? (SKT_CONJURE) : (SKT_ERROR);
	case SPL_SUMMON_ELEC_BALL:
		return num == 0 ? (SKT_AIR) : num == 1 ? (SKT_CONJURE) : (SKT_ERROR);
	case SPL_DREAM_CALL:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_TRANS) : (SKT_ERROR);
	case SPL_HYPER_BEAM:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_KAGUYA_SPELL:
		return num == 0 ? (SKT_SUMMON) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_THROW_SWORD:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_THROW_KNIFE:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_THROW_PLAYER:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_EARTH) : (SKT_ERROR);
	case SPL_THROW_AMULET:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_WARP_KICK:
		return num == 0 ? (SKT_TRANS) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_REIMU_BARRIER:
		return num == 0 ? (SKT_TRANS) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_TOUGUE:
		return num == 0 ? (SKT_TRANS) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_WINDFLAW:
		return num == 0 ? (SKT_AIR) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_SUMMON_GHOST:
		return num == 0 ? (SKT_SUMMON) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_MEGATON_KICK:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_THROW_OIL:
		return num == 0 ? (SKT_FIRE) : num == 1 ? (SKT_ALCHEMY) : (SKT_CONJURE);
	case SPL_HEAVENLY_STORM:
		return num == 0 ? (SKT_AIR) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_TRACKING:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_DISCORD:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_SMOKING:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_CREATE_FOG:
		return num == 0 ? (SKT_AIR) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_GROW_VINE:
		return num == 0 ? (SKT_SUMMON) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_CLOSE_DOOR:
		return num == 0 ? (SKT_EARTH) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_SPEAKER_PHONE:
		return num == 0 ? (SKT_MENTAL) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_HOMING_TANMAC:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_ALLROUND_TANMAC:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_THROW_POTION:
		return num == 0 ? (SKT_ALCHEMY) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_THROW_RABBIT:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_ARROW:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_HANIWA_MAGIC_TANMAC:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_HANIWA_MAGIC_TANMAC2:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	case SPL_HANIWA_MAGIC_TANMAC3:
		return num == 0 ? (SKT_CONJURE) : num == 1 ? (SKT_ERROR) : (SKT_ERROR);
	default:
		return SKT_ERROR;
	}
	return SKT_ERROR;
}


int SpellCap(spell_list skill)
{
	switch(skill)
	{
	case SPL_MON_TANMAC_SMALL:
	case SPL_BURN:
	case SPL_FROZEN:
	case SPL_STING:
	case SPL_SUMMON_MOOK:
	case SPL_MAGIC_TANMAC:
	case SPL_HYPNOSIS:
	case SPL_STONE_PUNCH:
		return 25;
	case SPL_MON_TANMAC_MIDDLE:
	case SPL_MON_WATER_GUN:
	case SPL_FROST:
	case SPL_FLAME:
	case SPL_SUMMON_BUG:
	case SPL_SELF_HEAL:
	case SPL_SHOCK:
	case SPL_GLOW:
	case SPL_VEILING:
	case SPL_SUMMON_OPTION:
	case SPL_STONE_ARROW: 
	case SPL_DIAMOND_HARDNESS:	
	case SPL_DRAW_POWER:
		return 50;
	case SPL_CONFUSE:
	case SPL_SLOW:
	case SPL_FIRE_WALL:
	case SPL_TWIST:
	case SPL_FIRE_BRAND:
	case SPL_COLD_BRAND:
	case SPL_POISON_BRAND:
	case SPL_DISCHARGE:
	case SPL_LEVITATION:
	case SPL_GRAZE:
	case SPL_SWIFT:
	case SPL_CONFUSE_CLOUD:
	case SPL_SUMMON_BIRD:
	case SPL_TELEPORT_OTHER:
	case SPL_SUMMON_PENDULUM:
	case SPL_MIND_BENDING:
	case SPL_STONE_TRAP:
	case SPL_POISON_SKIN:
	case SPL_KNIFE_COLLECT:
	case SPL_FREEZE:
	case SPL_HOMING_TANMAC:
		return 75;
	case SPL_MEDICINE_CLOUD:
	case SPL_SMITE:
	case SPL_FIRE_BALL:
	case SPL_WHIRLWIND:
	case SPL_WATER_CANNON:
	case SPL_SELF_INJURY:
	case SPL_KYOKO_SMITE:
	case SPL_MUTE:
	case SPL_STONE_UPLIFT:
	case SPL_SUMMON_ANCHOR:
		return 100;
	case SPL_COLD_BEAM:
	case SPL_CHAIN_LIGHTNING:
	case SPL_SILENCE:
	case SPL_FIRE_BOLT:
	case SPL_ICE_BOLT:
	case SPL_VENOM_BOLT:
	case SPL_POISON_CLOUD:
	case SPL_ICE_CLOUD:
	case SPL_SUMMON_GOLEM:
	case SPL_CHARM:
	case SPL_LASER:
	case SPL_SUMMON_UNZAN:
	case SPL_SUMMON_UNZAN_PUNCH:
	case SPL_SUMMON_ZOMBIE_FAIRY:
	case SPL_HASTE_OTHER:
	case SPL_HEAL_OTHER:
	case SPL_KANAME_DRILL:
	case SPL_SUMMON_LESSOR_DEMON:
	case SPL_TIME_PARADOX: 
	case SPL_THUNDER:
	case SPL_AIR_STRIKE:
	case SPL_EMERALD_CITY:
		return 150;
	case SPL_SUMMON_SEKIBANKI:
	case SPL_SPARK:
	case SPL_SUMMON_UFO:
	case SPL_STONE_FORM:
	case SPL_FLAN_BUSIN:
	case SPL_BURST:
	case SPL_SUICIDE_BOMB:
	case SPL_RABBIT_HORN:
	case SPL_LUMINUS_STRIKE:
	case SPL_FIRE_STORM:
	case SPL_BLIZZARD: 
	case SPL_PERFERT_FREEZE: 
	case SPL_ANIMAL_CHANGE:
	case SPL_FIELD_VIOLET:
	case SPL_PRIVATE_SQ: 
	case SPL_CONTROLED_BLINK: 
	case SPL_THE_WORLD:
	case SPL_HASTE_ALL:
	case SPL_HEAL_ALL:
	case SPL_MOON_COMMUNICATION:
	case SPL_MOON_GUN:
	case SPL_SUMMON_DREAM:
	case SPL_MANA_DRAIN:
	case SPL_INSANE:
	case SPL_BLOOD_SMITE:
	case SPL_CALL_HOUND:
	case SPL_CANNON:
	case SPL_DOLLS_WAR:
	case SPL_FAKE_DOLLS_WAR:
	case SPL_FIRE_SPREAD:
	case SPL_STASIS:
	case SPL_JUMP_ATTACK:
	case SPL_ALERT_NOISE: 
	case SPL_SUMMON_NAMAZ:
	case SPL_SCHEMA_TANMAC:
	case SPL_CHANGE:
	case SPL_UNLUCK:
	case SPL_SUMMON_RACOON:
	case SPL_SUMMON_YOUKAI:
	case SPL_MAMIZO_EVADE:
	case SPL_MACRO_BURST:
	case SPL_SHATTER:
	case SPL_SUMMON_YOSHIKA:
	case SPL_NESY_CANNON:
	case SPL_MERMAID_SONG:
	case SPL_AUTUMN_BLADE:
	case SPL_PHILOSOPHERS_STONE:
	case SPL_REAPER_MET:
	case SPL_AFTERLITE:
	case SPL_PRISM_CALL:
	case SPL_PSYCHOKINESIS:
	case SPL_SUMMON_TRASH:
	case SPL_TRASH_RUSH:
	case SPL_KOKORO_CHANGE:
	case SPL_THUNDER_BOLT:
	case SPL_SANTUARY:
	case SPL_MISTIA_SONG:
	case SPL_THROW_DISH:
	case SPL_MESS_CONFUSION:
	case SPL_SLEEP_SMITE:
	case SPL_SUMMON_ELEC_BALL:
	case SPL_DREAM_CALL:
	case SPL_HYPER_BEAM:
	case SPL_TARGET_ELEC:
	case SPL_KAGUYA_SPELL:
	case SPL_THROW_SWORD:
	case SPL_THROW_KNIFE:
	case SPL_THROW_PLAYER:
	case SPL_THROW_AMULET:
	case SPL_WARP_KICK:
	case SPL_REIMU_BARRIER:
	case SPL_TOUGUE:
	case SPL_WINDFLAW:
	case SPL_SUMMON_GHOST:
	case SPL_MEGATON_KICK:
	case SPL_THROW_OIL:
	case SPL_HEAVENLY_STORM:
	case SPL_TRACKING:
	case SPL_DISCORD:
	case SPL_SMOKING:
	case SPL_CREATE_FOG:
	case SPL_GROW_VINE:
	case SPL_CLOSE_DOOR:
	case SPL_SPEAKER_PHONE:
	case SPL_ALLROUND_TANMAC:
	case SPL_THROW_POTION:
	case SPL_THROW_RABBIT:
	case SPL_ARROW:
	case SPL_HANIWA_MAGIC_TANMAC:
	case SPL_HANIWA_MAGIC_TANMAC2:
	case SPL_HANIWA_MAGIC_TANMAC3:
		return 200;
	default:
	case SPL_BLINK:
	case SPL_CURE_POISON:
	case SPL_INVISIBLE:
	case SPL_HASTE:
	case SPL_RECALL:
	case SPL_TELEPORT_SELF:
		return 0;
	}
}

int SpellDiffer(int level)
{
	switch(level)
	{
	case 1:
		return -6;
	case 2:
		return -2;
	case 3:
		return 1;
	case 4:
		return 4;
	case 5:
		return 8;
	case 6:
		return 11;
	case 7:
		return 14;
	case 8:
		return 17;
	case 9:
		return 21;
	default:
		return 99;
	}
}
int SpellMiscastingLevel(int level_, int fail_)
{
	switch(level_)
	{
	case 1:
		return 0;
	case 2:
		return                           (fail_>=27?1:0);
	case 3:
		return              (fail_>=56?2:(fail_>=24?1:0));
	case 4:
		return (fail_>=70?3:(fail_>=49?2:(fail_>=21?1:0)));
	case 5:
		return (fail_>=60?3:(fail_>=42?2:(fail_>=18?1:0)));
	case 6:
		return (fail_>=50?3:(fail_>=35?2:(fail_>=15?1:0)));
	case 7:
		return (fail_>=40?3:(fail_>=28?2:(fail_>=12?1:0)));
	case 8:
		return (fail_>=30?3:(fail_>=21?2:(fail_>=9?1:0)));
	case 9:
		return (fail_>=20?3:(fail_>=14?2:(fail_>=6?1:0)));
	default:
		return 0;
	}
}
int SpellMiscasting(int miscasting_level_)
{
	random_extraction<int> rand_;
	rand_.push(0);
	if(miscasting_level_>=1)	
		rand_.push(1);
	if(miscasting_level_>=2)	
		rand_.push(2);
	if(miscasting_level_>=3)	
		rand_.push(3);



	switch(rand_.pop())
	{
	case 0:
	default:
		return 0;
	case 1:
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CAST_PANALTY1),true,false,false,CL_small_danger);
		you.StatUpDown(-1,STAT_INT,true);
		return 1;
	case 2:
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CAST_PANALTY2),true,false,false,CL_small_danger);
		you.StatUpDown(-rand_int(2,3),STAT_INT,true);
		return 2;
	case 3:
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_CAST_PANALTY3),true,false,false,CL_small_danger);
		you.StatUpDown(-rand_int(4,7),STAT_INT,true);
		return 3;

	}
}
int SpellHunger(int level)
{
	switch(level)
	{
	case 1:
		return 25;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 150;
	case 5:
		return 250;
	case 6:
		return 350;
	case 7:
		return 500;
	case 8:
		return 700;
	case 9:
		return 900;
	default:
		return 0;
	}

}


bool SpellAiCondition(spell_list skill, monster *mon)
{
	if(mon->s_changed && SpellFlagCheck(skill,S_FLAG_SUMMON))
	{
		return false;
	}


	switch(skill)
	{
	case SPL_GRAZE:
		return (mon->s_graze?false:true);
	case SPL_VEILING:
		return (mon->s_veiling?false:true);
	case SPL_INVISIBLE:
		return (mon->s_invisible?false:true);
	case SPL_HASTE:
		return (mon->s_haste?false:true);
	case SPL_SILENCE:
		return (mon->s_silence?false:true);
	case SPL_TELEPORT_SELF:
		return (mon->hp>mon->max_hp*0.2f || mon->s_tele?false:true);
	case SPL_DISCHARGE:
		return (mon->s_elec ? false : true);
	case SPL_BLINK:
		return (mon->state.GetState() != MS_DECIDE);
	case SPL_MOON_COMMUNICATION:
	case SPL_FIRE_SPREAD:
	case SPL_ALERT_NOISE: 
	case SPL_JUMP_ATTACK:
	case SPL_AFTERLITE:
	case SPL_KOKORO_CHANGE:
	case SPL_BLOOD_SMITE:
		return (mon->s_exhausted ? false : true);
	case SPL_CALL_HOUND:
	{
		if (mon->s_exhausted)
			return false;		
		
		int max_ = 8;
		//콜하운드로 부를 수 있는 한계는 최대 8마리
		for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if (it->isLive() && it->id == MON_HELL_HOUND)
			{
				if (env[current_level].isInSight(it->position)) {
					max_--;
				}
			}
		}
		if (max_ < 0)
			return false;
		return true;
	}
	case SPL_MISTIA_SONG:
		return (mon->s_exhausted || mon->isUserAlly() ?false:true);
	case SPL_SLEEP_SMITE:
		if (!mon->isUserAlly()) {
			if (you.s_sleep < 0)
				return false;\
		}
		return true;
	case SPL_SUMMON_YOSHIKA:
		{

			for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && it->id == MON_YOSIKA)
				{
					if(mon->isMonsterSight((it->position)))
						return false;

				}
			}
			return true;
		}
	case SPL_PRISM_CALL:
	{
		for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if (mon != &(*it)  && it->isLive() && (it->id == MON_LYRICA || it->id == MON_MERLIN || it->id == MON_LUNASA))
			{
				if (!mon->isMonsterSight((it->position)))
					return true;
			}
		}
		return false;
	}
	case SPL_TRASH_RUSH:
	{
		for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if (it->isLive() && it->sm_info.parent_map_id == mon->map_id && it->sm_info.summon_id == GetSummonKind(SPL_SUMMON_TRASH))
			{
				if (mon->isMonsterSight(it->position)) {
					return true;
				}
			}
		}
		return false;
	}
	case SPL_DREAM_CALL:
	{
		if (!env[current_level].isInSight(mon->position))
			return false;
		rect_iterator rect_(you.position, 1, 1);

		bool block = true;
		while (!rect_.end())
		{
			if (env[current_level].isMove((*rect_)) 
				&& env[current_level].isMonsterPos(rect_->x, rect_->y) == NULL) {
				block = false;
				break;
			}
			rect_++;
		}
		if(block == true)
			return false;

		for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if (&(*it) != mon && it->isLive() && it->isCanMove() && it->isAllyMonster(mon))
			{
				if (mon->isMonsterSight(it->position)) {
					return true;
				}
			}
		}
		return false;
	}
	case SPL_SANTUARY:
		return (mon->s_exhausted ? false : (mon->hp>mon->max_hp*0.3f ? false : true));
	case SPL_REIMU_BARRIER:
		return (!mon->s_exhausted && you.god != GT_YUKARI && you.s_dimension == 0);
	case SPL_CREATE_FOG:
		return (you.s_weather>0 || !(current_level >= MISTY_LAKE_LEVEL && current_level <=MISTY_LAKE_LAST_LEVEL)?false:true);
	case SPL_HEAVENLY_STORM:
		return (mon->id == MON_SONBITEN || (mon->id == MON_ENSLAVE_GHOST && mon->id2 == MON_SONBITEN))?true:false;
	case SPL_CLOSE_DOOR:
		if(mon->special_value == 0)
		{
			bool able = false;
			for(int i = 0; i< DG_MAX_X; i++) {
				for(int j = 0; j< DG_MAX_Y; j++) {		
					coord_def target(i,j);	
					if (env[current_level].isInSight(target) && 
					(env[current_level].dgtile[target.x][target.y].isDoor() || env[current_level].dgtile[target.x][target.y].isStair())) {
						unit *unit_ = env[current_level].isMonsterPos(target.x, target.y);
						if(unit_ && (!unit_->isplayer()  && ((monster*)unit_)->flag & M_FLAG_NONE_MOVE))
							continue;

						able = true;
					}
				}
			}
			return able;
		} else {
			return false;
		}
	case SPL_TRACKING:
		return ((!you.s_tracking && !mon->isUserAlly() && mon->target == &you) ?true:false);
	case SPL_THROW_RABBIT:
	{
		rand_rect_iterator rect_(mon->position, 1, 1, true);
		coord_def targetPos =mon->target?mon->target->position:mon->target_pos;
		while(!rect_.end()) {
			if(targetPos != *rect_) {
				unit* unit_ = env[current_level].isMonsterPos(rect_->x, rect_->y, &you, NULL);
				if(unit_ && unit_->isLive() && unit_->isRabbit() && unit_->GetId() != MON_RABIT_GIANT) {
					return true;
				}
			}
			rect_++;
		}
	}
	return false;
	default:
		return true;
	}
}





void Spell_Throw(spell_list spell_, vector<monster>::iterator it2, int smite_);

bool spell_prev_fail() {
	bool silence_ = env[current_level].isSilence(you.position);
	if(you.s_lunatic)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_SPELL),true,false,false,CL_danger);
		return true;
	}
	if (you.s_evoke_ghost) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_SPELL), true, false, false, CL_normal);
		return true;
	}
	if (you.drowned)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_DROWNED_PENALTY_MAGIC), true, false, false, CL_danger);
		return true;
	}
	bool sion_ = (you.god == GT_JOON_AND_SION && !you.GetPunish(GT_JOON_AND_SION) && you.god_value[GT_JOON_AND_SION][0] == 2);
	if (!sion_ && you.power < 100)
	{ //파워 100이하에선 마법을 쓸 수 없다. (시온일 경우 가능)
		printlog(LocalzationManager::locString(LOC_SYSTEM_SPELL_NEED_POWER), true, false, false, CL_danger);
		return true;
	}
	if(you.currentSpellNum)
	{
		if(!you.GetProperty(TPT_FINGER_MAGIC) && silence_)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SILENCE_PENALTY),true,false,false,CL_normal);
			return true;
		}
		if(you.s_confuse)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE_WARNING),true,false,false,CL_normal);
			return true;
		}
	}
	else {
		printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_REMEMBER_SPELL),true,false,false,CL_normal);
		return true;
	}
	return false;
}


void SimpleSpellUse()
{
	if(spell_prev_fail()) {
		return;
	}
	int prevSpell_ = you.prevSpell;
	spell_list prev_spell_id = SPL_NONE;
	if(prevSpell_ != 0) {
		prev_spell_id = (spell_list)you.MemorizeSpell[asctonum(prevSpell_)];
		if(prev_spell_id == SPL_NONE) {
			prevSpell_ = 0;
		}
	}

	vector<int> select_list;
	for(int i = 'a'; (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') ;) {
		if(you.MemorizeSpell[asctonum(i)])
			select_list.push_back(i);
		if(i=='z')
			i = 'A';
		else
			i++;
	}
	if(select_list.size() < 52)
		select_list.push_back('*');
	if(select_list.size() < 52)
		select_list.push_back(VK_ESCAPE);
	printlog(LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_USE_SPELL_FIELD), false, false, true, CL_help);

	printlog(" (",false,false,true,CL_help);
	printlog((joypadUtil::usingPad?LocalzationManager::locString(LOC_SYSTEM_SELECT_WITH_CURSOR):LocalzationManager::locString(LOC_SYSTEM_LETTER)) + ":" + LocalzationManager::locString(LOC_SYSTEM_MAGIC),false,false,true,CL_help);
	printlog(" ",false,false,true,CL_help);
	if(prevSpell_) {
		printlog(joypadUtil::get(LocalzationManager::locString(LOC_SYSTEM_ENTER),GVK_BUTTON_A)+":"+SpellString(prev_spell_id),false,false,true,CL_help, VK_RETURN);
		printlog(" ",false,false,true,CL_help);
	}
	printlog(joypadUtil::get("*?",GVK_BUTTON_A_LONG) + ":" + LocalzationManager::locString(LOC_SYSTEM_ALL_SPELL) ,false,false,true,CL_help, '*');
	printlog(") ",true,false,true,CL_help);
	while(1)
	{

		InputedKey inputedKey;
		startAbilGrid(select_list);

		int key_ = 0;
		g_menu_select = -1;
		while(true) {
			key_ = waitkeyinput(inputedKey,true);
			if(key_ == VK_RIGHT){
				++g_menu_select;
				if(g_menu_select>20+select_list.size()-1 || g_menu_select<20)
					g_menu_select = 20;
				continue;
			} else if (key_ == VK_LEFT) {
				if(--g_menu_select<20)
					g_menu_select = 20+select_list.size()-1;
				continue;
			} else if(key_ == VK_RETURN || key_ == GVK_BUTTON_A) {
				if(g_menu_select >= 20 && g_menu_select < 20+select_list.size()) {
					key_ = select_list[g_menu_select - 20];
					break;
				}
			}
			break;
		}
		g_menu_select = -1;

		endAbilGrid();

		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			int num = asctonum(key_);
			if(spell_list spell_ = (spell_list)you.MemorizeSpell[num])
			{
				deletelog();
				SpellUse(key_, 0, true);
				return;
			}
		}
		else if(key_ == VK_RETURN || key_ == GVK_BUTTON_A) {
			deletelog();
			if(prevSpell_) {
				SpellUse(prevSpell_, 0, true);
			}
			return;
		}
		else if(key_ == '*' || key_ == '?' || key_ == GVK_BUTTON_A_LONG) {
			deletelog();
			SpellUse(0, 0, false);
			return;
		}
		else if(key_ == -1) {
			if(inputedKey.mouse == MKIND_MENU || inputedKey.val1 == SYSCMD_MAGIC) {
				deletelog();
				if(prevSpell_) {
					SpellUse(prevSpell_, 0, true);
				}
				return;
			}
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				if(spell_list spell__ = (spell_list)you.MemorizeSpell[asctonum(inputedKey.val1)])
				{
					WaitForSingleObject(mutx, INFINITE);
					SetText() = GetSpellInfor((spell_list)spell__, true);
					ReleaseMutex(mutx);
					changedisplay(DT_TEXT);
					waitkeyinput();
					changedisplay(DT_GAME);
				}
			} else if(inputedKey.isRightClick()) {
				deletelog();
				return;
			}
		}
		else if(key_ == VK_ESCAPE||
			key_ == GVK_BUTTON_B || 
			key_ == GVK_BUTTON_B_LONG) {
			deletelog();
			return;
		}
	}

}



void SpellUse(char auto_, int auto_direc_, bool only_char)
{
	bool silence_ = env[current_level].isSilence(you.position);
	if(spell_prev_fail()) {
		return;
	}
	if(you.currentSpellNum)
	{
		bool blood_ = false;
		bool use_ = true;
		view_spell(LOC_SYSTEM_DISPLAY_MANAGER_USE_SPELL);
		//changedisplay(DT_SPELL);
		while(1)
		{
			int key_ = auto_;
			InputedKey inputedKey;
			if (key_ == 0)
				key_ = waitkeyinput(inputedKey,true);

			if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
				int char_ = DisplayManager.positionToChar();
				if(char_) {
					if(key_ == GVK_BUTTON_A_LONG) {
						key_ = -1;
						inputedKey.mouse = MKIND_ITEM_DESCRIPTION;
						inputedKey.val1 = char_;
					} else {
						key_ = char_;
					}
				}
			}

			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
				if(spell_list spell_ = (spell_list)you.MemorizeSpell[num])
				{
					if(use_)
					{
						if (you.pure_mp && SpellLevel(spell_) >= you.GetMp())
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_MP_WARN), true, false, false, CL_normal);
							break;
						}
						else if(SpellLevel(spell_)>you.GetMp())
						{
							if(you.GetProperty(TPT_BLOOD_MAGIC) && SpellLevel(spell_)*2<you.GetHp())
							{
								printlog(LocalzationManager::locString(LOC_SYSTEM_BLOOD_MAGIC),true,false,false,CL_danger);	
								blood_ = true;
							}
							else
							{
								printlog(LocalzationManager::locString(LOC_SYSTEM_TOO_LOW_MP),true,false,false,CL_normal);	
								break;
							}
						}
						if(SpellFlagCheck(spell_, S_FLAG_DIREC))
						{
							SetSpellSight(SpellLength(spell_, true),SpellFlagCheck(spell_, S_FLAG_RECT)?2:1);
							changedisplay(DT_GAME);
							coord_def target_;
							int direc_ = Direc_Throw(auto_direc_, &target_);
							if(direc_)
							{
								if(PlayerUseSpell(spell_, false, target_))
								{
									you.prevSpell = key_;
									GodAccpect_UseSpell(spell_);
									if(blood_)
										you.HpUpDown(-2*SpellLevel(spell_),DR_EFFECT);		
									else
										you.MpUpDown(-SpellLevel(spell_));									
									you.doingActionDump(DACT_SPELL, SpellString(spell_));
									//you.SkillTraining(SKT_SPELLCASTING,5);		
									//if(SpellSchool(spell_,0)!=SKT_ERROR)		
									//	you.SkillTraining(SpellSchool(spell_,0),2);
									//if(SpellSchool(spell_,1)!=SKT_ERROR)
									//	you.SkillTraining(SpellSchool(spell_,1),2);
									//if(SpellSchool(spell_,2)!=SKT_ERROR)
									//	you.SkillTraining(SpellSchool(spell_,2),2);
									//you.HungerApply(-you.GetSpellHungry(spell_));
									you.time_delay += you.GetSpellDelay()*SpellSpeed(spell_)/10;
									you.SetBattleCount(30);
									if(!silence_)
										Noise(you.position,you.GetProperty(TPT_FINGER_MAGIC)?SpellNoise(spell_)*0.7f:SpellNoise(spell_));
									
									you.afterSpell(you.GetSpellDelay()*SpellSpeed(spell_)/10);
									you.TurnEnd();
									you.SetPrevAction('z',key_, direc_);
								}
							}
							break;

						}
						else if(!SpellFlagCheck(spell_, S_FLAG_IMMEDIATELY))
						{
							SetSpellSight(SpellLength(spell_, true),SpellFlagCheck(spell_, S_FLAG_RECT)?2:1);
							changedisplay(DT_GAME);
							beam_iterator beam(you.position,you.position);
							projectile_infor infor(SpellLength(spell_, true),false,SpellFlagCheck(spell_, S_FLAG_SMITE),spell_,false);
							auto it = you.item_list.end();
							if(int short_ = Common_Throw(it, you.GetTargetIter(), beam, &infor,GetSpellMlen(spell_, true),GetSpellSector(spell_), (auto_>0 && !only_char)))
							{
								unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
								if(unit_)
									you.youAttack(unit_);
								if(PlayerUseSpell(spell_, short_==2, you.search_pos))
								{		
									you.prevSpell = key_;
									GodAccpect_UseSpell(spell_);
									if(blood_)
										you.HpUpDown(-2*SpellLevel(spell_),DR_EFFECT);		
									else
										you.MpUpDown(-SpellLevel(spell_));	
									you.doingActionDump(DACT_SPELL, SpellString(spell_));
	/*								you.SkillTraining(SKT_SPELLCASTING,5);	*/	
									//if(SpellSchool(spell_,0)!=SKT_ERROR)		
									//	you.SkillTraining(SpellSchool(spell_,0),2);
									//if(SpellSchool(spell_,1)!=SKT_ERROR)
									//	you.SkillTraining(SpellSchool(spell_,1),2);
									//if(SpellSchool(spell_,2)!=SKT_ERROR)
									//	you.SkillTraining(SpellSchool(spell_,2),2);
									//you.HungerApply(-you.GetSpellHungry(spell_));
									you.SetBattleCount(30);
									you.time_delay += you.GetSpellDelay()*SpellSpeed(spell_)/10;
									if(!silence_)
										Noise(you.position,you.GetProperty(TPT_FINGER_MAGIC)?SpellNoise(spell_)*0.7f:SpellNoise(spell_));
									
									you.afterSpell(you.GetSpellDelay()*SpellSpeed(spell_)/10);
									you.TurnEnd();
									you.SetPrevAction('z', key_);
								}
							}
							SetSpellSight(0,0);
							break;
						}			
						else if(SpellFlagCheck(spell_, S_FLAG_IMMEDIATELY))
						{
							changedisplay(DT_GAME);
							if(PlayerUseSpell(spell_, false, you.position))
							{
								you.prevSpell = key_;
								GodAccpect_UseSpell(spell_);
								if(blood_)
									you.HpUpDown(-2*SpellLevel(spell_),DR_EFFECT);		
								else
									you.MpUpDown(-SpellLevel(spell_));	
								you.doingActionDump(DACT_SPELL, SpellString(spell_));
								//you.SkillTraining(SKT_SPELLCASTING,5);		
								//if(SpellSchool(spell_,0)!=SKT_ERROR)		
								//	you.SkillTraining(SpellSchool(spell_,0),2);
								//if(SpellSchool(spell_,1)!=SKT_ERROR)
								//	you.SkillTraining(SpellSchool(spell_,1),2);
								//if(SpellSchool(spell_,2)!=SKT_ERROR)
								//	you.SkillTraining(SpellSchool(spell_,2),2);
								//you.HungerApply(-you.GetSpellHungry(spell_));
								you.SetBattleCount(30);
								you.time_delay += you.GetSpellDelay()*SpellSpeed(spell_)/10;
								if(!silence_)	
									Noise(you.position,you.GetProperty(TPT_FINGER_MAGIC)?SpellNoise(spell_)*0.7f:SpellNoise(spell_));
								
								you.afterSpell(you.GetSpellDelay()*SpellSpeed(spell_)/10);
								you.TurnEnd();
								you.SetPrevAction('z', key_);
							}		
							break;
						}
					}
					else
					{
						int num_ = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
						if(spell_list spell__ = (spell_list)you.MemorizeSpell[num_])
						{
							WaitForSingleObject(mutx, INFINITE);
							SetText() = GetSpellInfor((spell_list)spell__, true);
							ReleaseMutex(mutx);
							changedisplay(DT_TEXT);
							waitkeyinput();

							view_spell(LOC_SYSTEM_DISPLAY_MANAGER_INFO_SPELL);
							//changedisplay(DT_SPELL);
						}
					}
				}
			}
			else if(key_ == VK_DOWN)//-----이동키-------
			{
				DisplayManager.addPosition(1);
			}
			else if(key_ == VK_UP)
			{
				DisplayManager.addPosition(-1);
			}
			else if(key_ == '?' || key_ == GVK_BUTTON_Y)
			{
				if(use_)
				{
					view_spell(LOC_SYSTEM_DISPLAY_MANAGER_INFO_SPELL);
					use_ = false;
				}
				else
				{					
					view_spell(LOC_SYSTEM_DISPLAY_MANAGER_USE_SPELL);
					use_ = true;
				}
			}
			else if(key_ == -1) {
				if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
					if(spell_list spell__ = (spell_list)you.MemorizeSpell[asctonum(inputedKey.val1)])
					{
						WaitForSingleObject(mutx, INFINITE);
						SetText() = GetSpellInfor((spell_list)spell__, true);
						ReleaseMutex(mutx);
						changedisplay(DT_TEXT);
						waitkeyinput();

						view_spell(use_?LOC_SYSTEM_DISPLAY_MANAGER_USE_SPELL:LOC_SYSTEM_DISPLAY_MANAGER_INFO_SPELL);
					}
				}  else if(inputedKey.isRightClick()) {
						break;
					}
				}
			else if(key_ == VK_ESCAPE||
			key_ == GVK_BUTTON_B || 
			key_ == GVK_BUTTON_B_LONG)
				break;
		}
		changedisplay(DT_GAME);
	}
	else
		printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_REMEMBER_SPELL),true,false,false,CL_normal);	
}




void SpellView()
{

	if(you.currentSpellNum)
	{		
		view_spell(LOC_SYSTEM_DISPLAY_MANAGER_INFO_SPELL_SIMPLE);
		//changedisplay(DT_SPELL);
		while(1)
		{
			InputedKey inputedKey;
			int key_ = waitkeyinput(inputedKey,true);
			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
				if(spell_list spell_ = (spell_list)you.MemorizeSpell[num])
				{
					WaitForSingleObject(mutx, INFINITE);
					SetText() = GetSpellInfor((spell_list)spell_, true);
					ReleaseMutex(mutx);
					changedisplay(DT_TEXT);
					waitkeyinput();

					view_spell(LOC_SYSTEM_DISPLAY_MANAGER_INFO_SPELL_SIMPLE);
					//changedisplay(DT_SPELL);
				}
			}
			else if(key_ == -1) {
				if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
					if(spell_list spell__ = (spell_list)you.MemorizeSpell[asctonum(inputedKey.val1)])
					{
						WaitForSingleObject(mutx, INFINITE);
						SetText() = GetSpellInfor((spell_list)spell__, true);
						ReleaseMutex(mutx);
						changedisplay(DT_TEXT);
						waitkeyinput();
						view_spell(LOC_SYSTEM_DISPLAY_MANAGER_INFO_SPELL_SIMPLE);
					}
				}  else if(inputedKey.isRightClick()) {
					break;
				}
			}
			else if(key_ == VK_ESCAPE||
			key_ == GVK_BUTTON_B || 
			key_ == GVK_BUTTON_B_LONG)
				break;
		}
		changedisplay(DT_GAME);
	}
	else
		printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_REMEMBER_SPELL),true,false,false,CL_normal);	
}

