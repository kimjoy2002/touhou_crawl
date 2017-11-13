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


extern HANDLE mutx;

int GetSpellMlen(spell_list spell_)
{ 
	switch(spell_)
	{
	case SPL_SPARK:
		return SpellLength(spell_);
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
	case SPL_FIRE_WALL:
		return ((S_FLAG_CLOUD | S_FLAG_SMITE | S_FLAG_SPEAK | S_FLAG_NO_COM | S_FLAG_NO_TARGET) & flag);	
	case SPL_COLD_BEAM:
	case SPL_FIRE_BOLT:
	case SPL_ICE_BOLT:
	case SPL_VENOM_BOLT:
	case SPL_LASER:
	case SPL_SPARK:
	case  SPL_FIRE_SPREAD:
	case SPL_THUNDER_BOLT:
		return (S_FLAG_PENETRATE | S_FLAG_SPEAK | S_FLAG_RANGE_ATTACK) & flag;
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
		return (S_FLAG_SUMMON | S_FLAG_SPEAK | S_FLAG_IMMEDIATELY) & flag;
	case SPL_SUMMON_UNZAN_PUNCH:
	case SPL_SUMMON_ZOMBIE_FAIRY:
	case SPL_SUMMON_NAMAZ:
	case SPL_SUMMON_ANCHOR:
		return (S_FLAG_SUMMON | S_FLAG_SPEAK | S_FLAG_SMITE) & flag;
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
		return (S_FLAG_DEBUF | S_FLAG_SPEAK) & flag;
	case SPL_MIND_BENDING:
		return (S_FLAG_DEBUF | S_FLAG_SPEAK | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_INSANE:
		return (S_FLAG_DEBUF) & flag;
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
		return ((S_FLAG_SMITE | S_FLAG_SPEAK) & flag);	
	case SPL_MERMAID_SONG:
		return ((S_FLAG_SMITE | S_FLAG_SPEAK | S_FLAG_CLOSE_DANGER) & flag);	
	case SPL_BURST:
	case SPL_MANA_DRAIN:	
	case SPL_BLOOD_SMITE:
	case SPL_AFTERLITE:
		return ((S_FLAG_SMITE) & flag);
	case SPL_REAPER_MET:
		return ((S_FLAG_SMITE | S_FLAG_CLOSE_DANGER)& flag);
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
		return (S_FLAG_SPEAK | S_FLAG_RANGE_ATTACK) & flag;
	case SPL_CANNON:
	case SPL_NESY_CANNON:
	case SPL_THROW_DISH:
		return (S_FLAG_RANGE_ATTACK) & flag;
	case SPL_JUMP_ATTACK:
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
		return (S_FLAG_SPEAK | S_FLAG_IMMEDIATELY) & flag;	
	case SPL_MOON_COMMUNICATION:
	case SPL_CHANGE:
	case SPL_KOKORO_CHANGE:
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

int SpellLength(spell_list skill)
{
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
		return 8;
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
		return 7;
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
		return 6;
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
		return 5;
	case SPL_BURN:
	case SPL_FREEZE:
		return 2;
	case SPL_FROZEN:
		return 1;
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
	default:
		return 0;		
	}
}

const char* SpellString(spell_list skill)
{
	switch(skill)
	{
	case SPL_MON_TANMAC_SMALL:
		return "소형 탄막";
	case SPL_MON_TANMAC_MIDDLE:
		return "중형 탄막";
	case SPL_MON_WATER_GUN:
		return "물총";
	case SPL_FROST:
		return "냉기의 탄막";
	case SPL_MEDICINE_CLOUD:
		return "스위트 포이즌";
	case SPL_COLD_BEAM:
		return "냉동빔";
	case SPL_CONFUSE:
		return "혼란";
	case SPL_SLOW:
		return "감속";
	case SPL_SMITE:
		return "강타";
	case SPL_FLAME:
		return "화염의 탄막";	
	case SPL_SUMMON_BUG:
		return "곤충 소환";
	case SPL_SELF_HEAL:
		return "소회복";
	case SPL_BLINK:
		return "블링크";
	case SPL_BURN:
		return "불꽃";
	case SPL_FROZEN:
		return "냉기";
	case SPL_FIRE_WALL:
		return "화염기둥";
	case SPL_FREEZE:
		return "급속 냉동";
	case SPL_STING:
		return "독의 탄막";
	case SPL_CURE_POISON:
		return "독치료";
	case SPL_TWIST:
		return "트위스트";
	case SPL_SUMMON_MOOK:
		return "모옥 소환";
	case SPL_FIRE_BRAND:
		return "화염의 무기";
	case SPL_COLD_BRAND:
		return "냉기의 무기";
	case SPL_POISON_BRAND:	
		return "맹독의 무기";
	case SPL_SHOCK:
		return "전격";
	case SPL_CHAIN_LIGHTNING:
		return "체인 라이트닝";
	case SPL_DISCHARGE:
		return "방전";
	case SPL_LEVITATION:
		return "자기부상";
	case SPL_GLOW:
		return "조명";
	case SPL_GRAZE:
		return "그레이즈";
	case SPL_VEILING:
		return "베일링";
	case SPL_INVISIBLE:
		return "투명";
	case SPL_HASTE:
		return "아드레날린";
	case SPL_SILENCE:
		return "정적";
	case SPL_SWIFT:
		return "신속";
	case SPL_MAGIC_TANMAC:
		return "마법의 탄막";
	case SPL_FIRE_BALL:
		return "화염구";
	case SPL_FIRE_BOLT:
		return "파이어볼트";
	case SPL_ICE_BOLT:
		return "아이스볼트";
	case SPL_VENOM_BOLT:
		return "베놈볼트";
	case SPL_CONFUSE_CLOUD:
		return "악취의 구름";
	case SPL_POISON_CLOUD:
		return "독의 구름";
	case SPL_ICE_CLOUD:
		return "냉기의 구름";
	case SPL_SUMMON_BIRD:
		return "새 소환";
	case SPL_RECALL:
		return "리콜";
	case SPL_TELEPORT_OTHER:
		return "목표의 공간이동";
	case SPL_TELEPORT_SELF:
		return "자신의 공간이동";
	case SPL_WHIRLWIND:
		return "풍선풍";
	case SPL_SUMMON_PENDULUM:
		return "펜듈럼 소환";
	case SPL_SUMMON_SEKIBANKI:
		return "머리 소환";
	case SPL_WATER_CANNON:
		return "워터캐논";
	case SPL_KYOKO_SMITE:
		return "극대 메아리";
	case SPL_SUMMON_OPTION:
		return "옵션 소환";
	case SPL_SUMMON_GOLEM:
		return "골렘 소환";
	case SPL_HYPNOSIS:
		return "최면";
	case SPL_MUTE:
		return "실어증";
	case SPL_SELF_INJURY:
		return "자해";
	case SPL_CHARM:
		return "매료";
	case SPL_LASER:
		return "레이저";
	case SPL_SPARK:
		return "스파크";
	case SPL_SUMMON_UNZAN:
		return "운잔 소환";
	case SPL_SUMMON_UNZAN_PUNCH:
		return "운잔 철권";
	case SPL_SUMMON_ZOMBIE_FAIRY:
		return "좀비페어리 소환";
	case SPL_SUMMON_UFO:
		return "벤토라 소환";
	case SPL_HASTE_OTHER:
		return "아군 가속";
	case SPL_HEAL_OTHER:
		return "아군 회복";
	case SPL_MIND_BENDING:
		return "마인드 벤딩";
	case SPL_STONE_PUNCH:
		return "돌 주먹";
	case SPL_STONE_ARROW: 
		return "바위의 탄막";
	case SPL_STONE_TRAP:
		return "압정 바위";
	case SPL_STONE_UPLIFT:
		return "지반 융기";
	case SPL_KANAME_DRILL:
		return "카나메 드릴";
	case SPL_DIAMOND_HARDNESS:
		return "다이아몬드 하드니스";
	case SPL_POISON_SKIN:
		return "포이즌 바디";
	case SPL_STONE_FORM:
		return "무념무상의 경지";
	case SPL_KNIFE_COLLECT:
		return "탄막 회수";
	case SPL_FLAN_BUSIN:
		return "포 오브 어카인드";
	case SPL_BURST:
		return "폭파";
	case SPL_SUICIDE_BOMB:
		return "자폭";
	case SPL_RABBIT_HORN:
		return "죽림의 나팔";
	case SPL_SUMMON_LESSOR_DEMON:
		return "마족 소환";
	case SPL_LUMINUS_STRIKE:
		return "루미너스 스트라이크";
	case SPL_FIRE_STORM:
		return "화염 폭풍";
	case SPL_BLIZZARD: 
		return "블리자드";
	case SPL_PERFERT_FREEZE: 
		return "퍼펙트 프리즈";
	case SPL_DRAW_POWER:
		return "상단회수";
	case SPL_ANIMAL_CHANGE:
		return "강제동물변화";
	case SPL_FIELD_VIOLET:
		return "필드울트라바이올렛";
	case SPL_TIME_PARADOX: 
		return "타임 패러독스";
	case SPL_PRIVATE_SQ: 
		return "프라이빗 스퀘어";
	case SPL_CONTROLED_BLINK: 
		return "제어 순간이동";
	case SPL_THE_WORLD:
		return "더 월드";
	case SPL_HASTE_ALL:
		return "단체 가속";
	case SPL_HEAL_ALL:
		return "단체 회복";
	case SPL_MOON_COMMUNICATION:
		return "전파 수신";
	case SPL_MOON_GUN:
		return "달의 총";
	case SPL_SUMMON_DREAM:
		return "꿈의 소환";
	case SPL_MANA_DRAIN:
		return "영력흡수";
	case SPL_INSANE:
		return "광기";
	case SPL_BLOOD_SMITE:
		return "피의 응시";
	case SPL_CALL_HOUND:
		return "동료부르기";
	case SPL_CANNON:
		return "거대 대포";
	case SPL_DOLLS_WAR:
		return "돌즈워";
	case SPL_FAKE_DOLLS_WAR:
		return "모조 돌즈워";
	case SPL_FIRE_SPREAD:
		return "화염 분출";
	case SPL_STASIS:
		return "체크메이트";
	case SPL_JUMP_ATTACK:
		return "도약공격";
	case SPL_ALERT_NOISE: 
		return "경고의 메아리";
	case SPL_SUMMON_NAMAZ:
		return "나마즈 소환";		
	case SPL_SCHEMA_TANMAC:
		return "경계 탄막";
	case SPL_CHANGE:
		return "둔갑술";
	case SPL_UNLUCK:
		return "파국의 개문";
	case SPL_THUNDER:
		return "용신의 번개";
	case SPL_AIR_STRIKE:
		return "질풍선";
	case SPL_SUMMON_RACOON:
		return "너구리 탄막변화";
	case SPL_SUMMON_YOUKAI:
		return "백귀야행";
	case SPL_MAMIZO_EVADE:
		return "이승지장변화";
	case SPL_MACRO_BURST:
		return "매크로버스트";
	case SPL_SHATTER:
		return "분쇄";
	case SPL_SUMMON_YOSHIKA:
		return "강령 요시카";
	case SPL_NESY_CANNON:
		return "네시 물대포";
	case SPL_MERMAID_SONG:
		return "인어의 노래";
	case SPL_EMERALD_CITY:
		return "에메랄드 시티";
	case SPL_AUTUMN_BLADE:
		return "어텀 블레이드";
	case SPL_PHILOSOPHERS_STONE:
		return "현자의 돌";
	case SPL_SUMMON_ANCHOR:
		return "침몰 앵커";
	case SPL_REAPER_MET:
		return "사신의마중 체험판";
	case SPL_AFTERLITE:
		return "얼마없는 여생";
	case SPL_PRISM_CALL:
		return "프리즘 콘체르토";
	case SPL_PSYCHOKINESIS:
		return "텔레키네시스";
	case SPL_SUMMON_TRASH:
		return "어번 사이코키네시스";
	case SPL_TRASH_RUSH:
		return "어번 사이코키네시스 사출";
	case SPL_KOKORO_CHANGE:
		return "코코로 룰렛";
	case SPL_THUNDER_BOLT:
		return "썬더볼트";
	case SPL_SANTUARY:
		return "성역";
	case SPL_MISTIA_SONG:
		return "밤참새의 노래";
	case SPL_THROW_DISH:
		return "접시던지기";
	case SPL_MESS_CONFUSION:
		return "광역 혼란";
	default:
		return "알수없는 마법";
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
		return 12; //상당한 소음 시야밖까지 영향
	case SPL_KYOKO_SMITE:
	case SPL_SPARK:
	case SPL_FIRE_STORM:
	case SPL_SANTUARY:
	case SPL_MISTIA_SONG:
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
		return 75;
	case SPL_MEDICINE_CLOUD:
	case SPL_SMITE:
	case SPL_FIRE_BALL:
	case SPL_WHIRLWIND:
	case SPL_WATER_CANNON:
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
	case SPL_SELF_INJURY:
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
		return -5;
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
		printlog("마법 부작용으로 가벼운 현기증을 느꼈다.",true,false,false,CL_small_danger);
		you.StatUpDown(-1,STAT_INT,true);
		return 1;
	case 2:
		printlog("마법 부작용으로 머리에 심한 두통을 느꼈다.",true,false,false,CL_small_danger);
		you.StatUpDown(-rand_int(2,3),STAT_INT,true);
		return 2;
	case 3:
		printlog("마법 부작용으로 머리에 끔찍한 손상이 왔다.",true,false,false,CL_small_danger);
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
	case SPL_MOON_COMMUNICATION:
	case SPL_CALL_HOUND:
	case SPL_FIRE_SPREAD:
	case SPL_ALERT_NOISE: 
	case SPL_JUMP_ATTACK:
	case SPL_AFTERLITE:
	case SPL_KOKORO_CHANGE:
		return (mon->s_exhausted ? false : true);
	case SPL_MISTIA_SONG:
		return (mon->s_exhausted || mon->isUserAlly() ?false:true);
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
	case SPL_SANTUARY:
		return (mon->s_exhausted ? false : (mon->hp>mon->max_hp*0.3f ? false : true));
	default:
		return true;
	}
}





void Spell_Throw(spell_list spell_, vector<monster>::iterator it2, int smite_);

void SpellUse()
{
	bool silence_ = env[current_level].isSilence(you.position);
	if(you.s_lunatic)
	{
		printlog("광기에 휩싸인 상태로 마법은 쓸 수 없다!",true,false,false,CL_danger);
		return;
	}
	if(you.currentSpellNum)
	{
		if(!you.GetProperty(TPT_FINGER_MAGIC) && silence_)
		{
			printlog("당신은 소리를 낼 수 없다.",true,false,false,CL_normal);
			return;
		}
		if(you.s_confuse)
		{
			printlog("당신은 혼란스럽다.",true,false,false,CL_normal);
			return;
		}
		bool blood_ = false;
		bool use_ = true;
		int i=0;
		view_spell("사용할 마법을 선택하세요.  ( ?키로 설명을 볼 수 있다. )");
		//changedisplay(DT_SPELL);
		while(1)
		{
			int key_ = waitkeyinput(true);
			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
				if(spell_list spell_ = (spell_list)you.MemorizeSpell[num])
				{
					if(use_)
					{
						if(SpellLevel(spell_)>you.mp)
						{
							if(you.GetProperty(TPT_BLOOD_MAGIC) && SpellLevel(spell_)<=you.hp)
							{
								printlog("당신은 피를 대가로 마법을 영창했다!",true,false,false,CL_danger);	
								blood_ = true;
							}
							else
							{
								printlog("당신의 영력이 모자란다.",true,false,false,CL_normal);	
								break;
							}
						}
						if(SpellFlagCheck(spell_, S_FLAG_DIREC))
						{
							SetSpellSight(SpellLength(spell_),SpellFlagCheck(spell_, S_FLAG_RECT)?2:1);
							changedisplay(DT_GAME);
							coord_def target_;
							if(Direc_Throw(&target_))
							{
								if(PlayerUseSpell(spell_, false, target_))
								{	
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
									you.TurnEnd();
								}
							}
							break;

						}
						else if(!SpellFlagCheck(spell_, S_FLAG_IMMEDIATELY))
						{
							SetSpellSight(SpellLength(spell_),SpellFlagCheck(spell_, S_FLAG_RECT)?2:1);
							changedisplay(DT_GAME);
							beam_iterator beam(you.position,you.position);
							projectile_infor infor(SpellLength(spell_),false,SpellFlagCheck(spell_, S_FLAG_SMITE),spell_,false);
							if(int short_ = Common_Throw(you.item_list.end(), you.GetTargetIter(), beam, &infor,GetSpellMlen(spell_),GetSpellSector(spell_)))
							{
								unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
								if(unit_)
									you.youAttack(unit_);
								if(PlayerUseSpell(spell_, short_==2, you.search_pos))
								{		
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
									you.TurnEnd();
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
								you.TurnEnd();
							}		
							break;
						}
					}
					else
					{
						int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
						if(spell_list spell_ = (spell_list)you.MemorizeSpell[num])
						{
							WaitForSingleObject(mutx, INFINITE);
							SetText() = GetSpellInfor((spell_list)spell_);
							ReleaseMutex(mutx);
							changedisplay(DT_TEXT);
							waitkeyinput();

							view_spell("설명을 볼 마법을 선택하세요. ( ?키로 마법을 사용 )");
							//changedisplay(DT_SPELL);
						}
					}
				}
			}
			else if(key_ == '?')
			{
				if(use_)
				{
					view_spell("설명을 볼 마법을 선택하세요. ( ?키로 마법을 사용 )");
					use_ = false;
				}
				else
				{					
					view_spell("사용할 마법을 선택하세요.  ( ?키로 설명을 볼 수 있다. )");
					use_ = true;
				}
			}
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
	}
	else
		printlog("아직 알고있는 마법이 없다.",true,false,false,CL_normal);	
}




void SpellView()
{

	if(you.currentSpellNum)
	{
		int i=0;
		
		view_spell("설명을 볼 마법을 선택하세요.");
		//changedisplay(DT_SPELL);
		while(1)
		{
			int key_ = waitkeyinput(true);
			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				int num = (key_ >= 'a' && key_ <= 'z')?(key_-'a'):(key_-'A'+26);
				if(spell_list spell_ = (spell_list)you.MemorizeSpell[num])
				{
					WaitForSingleObject(mutx, INFINITE);
					SetText() = GetSpellInfor((spell_list)spell_);
					ReleaseMutex(mutx);
					changedisplay(DT_TEXT);
					waitkeyinput();

					view_spell("설명을 볼 마법을 선택하세요.");
					//changedisplay(DT_SPELL);
				}
			}
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
	}
	else
		printlog("아직 알고있는 마법이 없다.",true,false,false,CL_normal);	
}

