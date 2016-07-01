//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: skill_use.h
//
// 내용: 스킬 스펠(예정)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SKILL_USE_H__
#define  __SKILL_USE_H__


#include "monster.h"
#include "enum.h"

enum spell_list
{
	SPL_NONE = 0,
	SPL_MON_TANMAC_SMALL,
	SPL_MON_TANMAC_MIDDLE,
	SPL_MON_WATER_GUN, 
	SPL_FLAME,	SPL_FROST,	SPL_MEDICINE_CLOUD,	SPL_COLD_BEAM,	SPL_SUMMON_BUG,	SPL_CONFUSE,	SPL_SLOW,
	SPL_SELF_HEAL,	SPL_BLINK,	SPL_SMITE,	SPL_BURN,	SPL_FIRE_WALL,	SPL_FROZEN,	SPL_FREEZE,	SPL_STING,
	SPL_CURE_POISON,	SPL_TWIST,	SPL_SUMMON_MOOK,	SPL_FIRE_BRAND,	SPL_COLD_BRAND,	SPL_POISON_BRAND,
	SPL_SHOCK,	SPL_CHAIN_LIGHTNING,	SPL_DISCHARGE,	SPL_LEVITATION,	SPL_GLOW,	SPL_GRAZE,	SPL_VEILING,
	SPL_INVISIBLE,	SPL_HASTE,	SPL_SILENCE,	SPL_SWIFT,	SPL_MAGIC_TANMAC,	SPL_FIRE_BALL,	SPL_FIRE_BOLT,
	SPL_ICE_BOLT,	SPL_VENOM_BOLT,	SPL_CONFUSE_CLOUD,	SPL_POISON_CLOUD,	SPL_ICE_CLOUD,	SPL_SUMMON_BIRD,
	SPL_RECALL, SPL_TELEPORT_OTHER, SPL_TELEPORT_SELF, SPL_WHIRLWIND, SPL_SUMMON_PENDULUM, SPL_SUMMON_SEKIBANKI,
	SPL_WATER_CANNON, SPL_KYOKO_SMITE, SPL_SUMMON_OPTION, SPL_SUMMON_GOLEM,
	SPL_HYPNOSIS, SPL_MUTE, SPL_SELF_INJURY, SPL_CHARM, SPL_LASER, SPL_SPARK,
	SPL_SUMMON_UNZAN, SPL_SUMMON_UNZAN_PUNCH, SPL_SUMMON_ZOMBIE_FAIRY, SPL_SUMMON_UFO,
	SPL_HASTE_OTHER, SPL_HEAL_OTHER, SPL_MIND_BENDING,
	SPL_STONE_PUNCH, SPL_STONE_ARROW, SPL_STONE_TRAP, SPL_STONE_UPLIFT, SPL_KANAME_DRILL,
	SPL_DIAMOND_HARDNESS, SPL_POISON_SKIN, SPL_STONE_FORM,
	SPL_KNIFE_COLLECT, SPL_FLAN_BUSIN, SPL_BURST, SPL_SUICIDE_BOMB,SPL_RABBIT_HORN,
	SPL_SUMMON_LESSOR_DEMON,
	SPL_LUMINUS_STRIKE, SPL_FIRE_STORM, SPL_BLIZZARD, SPL_PERFERT_FREEZE, SPL_DRAW_POWER, SPL_ANIMAL_CHANGE,
	SPL_FIELD_VIOLET, SPL_TIME_PARADOX, SPL_PRIVATE_SQ, SPL_CONTROLED_BLINK, SPL_THE_WORLD,
	SPL_HASTE_ALL, SPL_HEAL_ALL, SPL_MOON_COMMUNICATION, SPL_MOON_GUN, SPL_SUMMON_DREAM, SPL_MANA_DRAIN, SPL_INSANE,
	SPL_BLOOD_SMITE, SPL_CALL_HOUND, SPL_CANNON, SPL_DOLLS_WAR, SPL_FAKE_DOLLS_WAR, SPL_FIRE_SPREAD,
	SPL_STASIS, SPL_JUMP_ATTACK, SPL_ALERT_NOISE, SPL_SUMMON_NAMAZ,
	SPL_MAX
};

enum skill_list
{
	SKL_NONE = 0,
	SKL_KANAKO_1,
	SKL_KANAKO_2,
	SKL_KANAKO_3,
	SKL_GRAZE,
	SKL_GRAZE_OFF,
	SKL_LEVITATION,
	SKL_LEVITATION_OFF,
	SKL_INVISIBLE,
	SKL_INVISIBLE_OFF,
	SKL_EIRIN_0,
	SKL_EIRIN_1,
	SKL_EIRIN_2,
	SKL_BYAKUREN_1,
	SKL_BYAKUREN_2,
	SKL_MINORIKO_1,
	SKL_MINORIKO_2,
	SKL_SIZUHA_1,
	SKL_SIZUHA_2,
	SKL_SIZUHA_3,
	SKL_YUUGI_1,
	SKL_YUUGI_2,
	SKL_YUUGI_3,
	SKL_YUUGI_3_THROW,
	SKL_YUUGI_4,
	SKL_YUUGI_5,
	SKL_SATORI_1,
	SKL_SATORI_2,
	SKL_SHINKI_1,
	SKL_SHINKI_2,
	SKL_SHINKI_3,
	SKL_YUYUKO_ON,
	SKL_YUYUKO_OFF,
	SKL_YUYUKO_1,
	SKL_YUYUKO_2,
	SKL_YUYUKO_3,
	SKL_YUKARI_1,
	SKL_YUKARI_2,
	SKL_YUKARI_3,
	SKL_YUKARI_4,
	SKL_SWAKO_JUMP,
	SKL_SWAKO_TEMPLE,
	SKL_SWAKO_WATER_GUN,
	SKL_SWAKO_TOUGUE,
	SKL_SWAKO_CURSE,
	SKL_SWAKO_DIGGING,
	SKL_SWAKO_SUMMON_FLOG,
	SKL_SWAKO_STATUE,
	SKL_SWAKO_RAIN,
	SKL_SWAKO_SLEEP,
	SKL_SWAKO_MISYAGUZI,
	SKL_HINA_1,
	SKL_HINA_2,
	SKL_HINA_3,
	SKL_HINA_4,
	SKL_HINA_5,
	SKL_MAX
};

enum skill_flag
{
	S_FLAG_SMITE = 1<<0, //스마이트식인가? false: 빔형태
	S_FLAG_PENETRATE = 1<<1, //관통되나?
	S_FLAG_CLOSE_DANGER = 1<<2, //근접사용시 위험한가?
	S_FLAG_SEIF = 1<<3, //자신에게 사용할수있는가?
	S_FLAG_CLOUD = 1<<4, //구름식인가? (구름식이 이미 상대 위에 있다면 쏘지않는다.)
	S_FLAG_HEAL = 1<<5, //회복
	S_FLAG_DEBUF = 1<<6, //디버프기
	S_FLAG_SUMMON = 1<<7, //소환기
	S_FLAG_SPEAK = 1<<8, //주문이 필요한가
	S_FLAG_IMMEDIATELY = 1<<9, //시전즉시 발동하는가?
	S_FLAG_DIREC = 1<<10, //방향으로 발동하는가? (S_FLAG_IMMEDIATELY와 중첩불가)
	S_FLAG_NO_COM = 1<<11, //AI가 사용하지않는 기술인가?
	S_FLAG_TOGLE = 1<<12, //토글형 기술인지?(한번 사용하면 잊거나 다시 사용할때까지 꺼지지않음)
	S_FLAG_BUF = 1<<13, //버프기
	S_FLAG_OTHER_BUF = 1<<14, //남을 버프시켜주는 기술(보통 ai용)
	S_FLAG_RANGE_ATTACK = 1<<15, //이 것은 (주로 ai가) 사거리안에 올때 공격가능한 기술이다.
	S_FLAG_SUKIMA = 1<<16, //스키마용
	S_FLAG_RECT = 1<<17, //사각형 시야
	S_FLAG_NO_TARGET = 1<<18, //몬스터를 타겟으로 잡지않는다.
	S_FLAG_UNSIGHT = 1<<19, //시야에 가려도 사용가능.
	S_FLAG_GOD = 1<<20 //신의 스킬
};

float GetSpellSector(spell_list spell_);
bool SpellFlagCheck(spell_list skill, skill_flag flag);
int SpellLength(spell_list skill);
bool isMonsterhurtSpell(monster* use_, monster* target_, spell_list spell_);
bool isMonSafeSkill(spell_list skill, monster* order, coord_def &target);
const char* SpellString(spell_list skill);
int SpellCap(spell_list skill);
int SpellLevel(spell_list skill);
int SpellNoise(spell_list skill);
int SpellSpeed(spell_list skill);
int SpellDiffer(int level);
int SpellHunger(int level);
skill_type SpellSchool(spell_list skill, int num);
bool SpellAiCondition(spell_list skill, const monster *mon); //인공지능이 마법을 쓰는 추가 조건(true가 사용가능 false가 사용불가)




bool SkillFlagCheck(skill_list skill, skill_flag flag);
int SkillLength(skill_list skill);
const char* SkillString(skill_list skill); //스킬 이름
int SkillCap(skill_list skill);//스킬파워 상한
int SkillNoise(skill_list skill); //스킬 소음
int SkillPow(skill_list skill);//스킬의 파워를 리턴
int SkillDiffer(skill_list skill);//100을 최고로 성공률을 리턴한다.
int SkillDiffer_simple(int differ, skill_type s1, skill_type s2, skill_type s3);//간단한 성공률 공식을 세운다.
int SkillMana(skill_list skill);//사용에 드는 마나를 계산
bool SkillPlusCost(skill_list skill,bool check_);//추가적인 코스트 
void SkillUseTraning(skill_list skill);
const char* SkillCostString(skill_list skill);//코스트표현문장

monster* BaseSummon(int id_, int time_, bool targeting_, bool random_, int range_, unit* order, coord_def target, SUMMON_KIND kind_, int max_num_);
void BaseBomb(coord_def pos, textures* t_, attack_infor& att_, unit* except_ = NULL);
int GetSpellBombRange(skill_list skill);//폭발넓이
int GetSpellBombRange(spell_list spell);


bool skill_elec_passive(int power, unit* order);




void SetSpell(monster_index id, list<spell> *list, bool* random_spell);


bool MonsterUseSpell(spell_list skill, bool short_, monster* order, coord_def &target, int pow_ = -1);
bool PlayerUseSpell(spell_list skill, bool short_, coord_def &target);
int UseSkill(skill_list skill, bool short_, coord_def &target);
void SpellUse();
void SpellView();
void SkillUse();


string GetSpellInfor(spell_list spell);
string GetSkillInfor(skill_list skill);
string GetSpellSchoolString(spell_list spell);


#endif // __SKILL_USE_H__