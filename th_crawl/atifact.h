//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: atifact.h
//
// 내용: 아티펙트 구현
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ATIFACT_H__
#define  __ATIFACT_H__

#include "enum.h"
#include <stdio.h>
#include <string>

class item;


enum artifact_type
{
	ART_STR = 0,
	ART_DEX,
	ART_INT,
	ART_HUNGRY,
	ART_FULL,
	ART_TELEPORT,
	ART_POISON_RESIS,
	ART_FIRE_RESIS,
	ART_ICE_RESIS,
	ART_SEE_INVISIBLE,
	ART_LEVITATION,
	ART_INVISIBLE,
	ART_MANA,
	ART_MAGACIAN,
	ART_AC,
	ART_EV,
	ART_CONFUSE_RESIS,
	ART_ELEC_RESIS,
	ART_MAGIC_RESIS,
	ART_SKILL_UP,
	ART_MAGICBOOST,
	ART_ANTIOVERHEAT,
	ART_PENTAN,
	ART_COUNTER,
	ART_PERMAINVI,
	ART_UNCONSCIOUS,
	ART_LUNATIC,
	ART_HALO,
	ART_RAD,
	ART_FIREBALL,
	ART_GLUTTON,
	ART_BUG,
	ART_POISONIMMUNE,
	ART_SWIFT,
	ART_MISSLE,
	ART_SELFDESTRUCT,
	ART_SUMMONRESIST,
	ART_DRUNK,
	ART_SLAY,
	ART_HP_REGEN,
	ART_LESS_POWER,
	ART_CURSE,
	ART_HEAVY,
	ART_WEATHER_TRIGGER,
	ART_WHIRLWIND,
	ART_INFINITE_REACH,
	ART_PULL,
	ART_UNKNOWN_POWER,
	ART_SWIM,
	ART_INSTANT_DEATH,
	ART_KNOCKAWAY,
	ART_JUMP,
	ART_RETURN,
	ART_KICK,
	ART_MAX_HP,
	ART_DIVE,
	ART_MAX_ATIFACT,
};


enum fixed_artifact_type {
	FIXED_ARTIFACT_NONE,
	FIXED_ARTIFACT_HAKKERO, //+0 미니팔괘로 (마력증폭, 과열방지, 영력, 화염저항++)
	FIXED_ARTIFACT_GUNGNIR, //+6 궁니르 (관통, 힘+6, EV+6)
	FIXED_ARTIFACT_ROUKANKEN, //+8 누관검 (냉기, 냉기저항+, 민첩+5)
	FIXED_ARTIFACT_HAKUROUKEN, //+5 백루검 (반격, 냉기저항+, 전투력+5)
	FIXED_ARTIFACT_KOISHIHAT, //+3 코이시의 모자 (영구투명, 무의식, 전기저항+, 혼란저항, *전이)
	FIXED_ARTIFACT_MIKOCLOAK, //-1 위정자의 망토 (화염저항+, 냉기저항+, 전기저항+, 마법저항, 투명감지, 포만감)
	FIXED_ARTIFACT_LUNATICTORCH, //+13 광기의 횃불 (화염, *광기, 후광, 마법사, 화염저항++)
	FIXED_ARTIFACT_MOONGEM, //달의 보옥 (정화, 혼란저항, 마법저항)
	FIXED_ARTIFACT_NUCLEARBOOT, //+6 핵융합의 다리 (방사능, 화염저항++, 전기저항+)
	FIXED_ARTIFACT_CONTROLROD, //+7 제어봉 (화염구, 화염저항+, 혼란저항)
	FIXED_ARTIFACT_PICKANDSHOVELS, //+3 지네의 삽 곡괭이 (맹독, 폭식, 허기, 독저항+)
	FIXED_ARTIFACT_SILVERKNIFE, //+9 메이드 특제 나이프 (은, EV+8, 마법저항, 시공마법+4)
	FIXED_ARTIFACT_FIREFLYCLOAK, //+2 반딧불 망토 (*벌레, 독저항+)
	FIXED_ARTIFACT_ICEFAIRYRING, //얼음 요정의 반지 (냉기저항+, 지능-9, 냉기마법+9)
	FIXED_ARTIFACT_LAEVATEIN, //+11 레바테인 (화염+, AC-4)
	FIXED_ARTIFACT_LILYRING, //은방울꽃 반지 (AC+5, 독면역)
	FIXED_ARTIFACT_GALECLOGS, //+0 질풍 나막신 (질풍, EV+4)
	FIXED_ARTIFACT_HELLTSHIRT, //+6 지옥 티셔츠 (힘/민첩/지능 중 2종+6, 1종-6)
	FIXED_ARTIFACT_KAPPAFULLARMOR, //+12 풀무장 캇파옷 (냉기저항+, 화염저항++, +미사일, *자폭)
	FIXED_ARTIFACT_MAIDUNIFORM, //+4 마계 메이드옷 (마법저항, 소환물저항, EV+5, 지능+5, 마법사)
	FIXED_ARTIFACT_IBUKISAKE, //+7 이부키효 (음주, 체력재생+++, 독저항+)
	FIXED_ARTIFACT_SHINING_NEEDLE_SWORD, //+2 빛나는 휘침검 (혼란저항, 힘-3, EV+6, 독저항+)
	FIXED_ARTIFACT_SWORD_OF_SCARLET_PERCEPTION, //+7 비상의 검 (비상, *날씨, 전기저항++)
	FIXED_ARTIFACT_GOLIATH_SWORD, //+6 골리앗 대검 (훨윈드, 무거움)
	FIXED_ARTIFACT_REAPER_SCYTHE, //+6 사신의 낫 (사거리+∞, 끌어당기기, 전투력-3)
	FIXED_ARTIFACT_UNIDENTIFIED_TRIDENT, //+0~+8 정체불명의 삼지창 / +9 대요괴 누에의 삼지창 (식별로 밝혀진 효과)
	FIXED_ARTIFACT_SUNKEN_ANCHOR, //+9 침수의 닻 (침수, 수영, 냉기저항++)
	FIXED_ARTIFACT_YAMANBA_CLEAVER, //+8 야만바의 식칼 (파워++, 힘+5)
	FIXED_ARTIFACT_BUTTERFLY_FAN, //+4 사접의 부채 (즉사, 투명감지)
	FIXED_ARTIFACT_RED_MALLET, //+4 붉게 물든 떡메 (날리기, 혼란저항)
	FIXED_ARTIFACT_IMMOVABLE_LIBRARY, //+2 지식과 그늘의 로브 (마법사, 마력증폭)
	FIXED_ARTIFACT_FULLMOON_DRESS, //+5 만월 늑대옷 (냉기저항+, 혼란저항, +도약)
	FIXED_ARTIFACT_HANIWA_ARMOUR, //+15 하니와 석갑옷 (전기저항+)
	FIXED_ARTIFACT_OCCULT_CLOAK, //+0 오컬트 망토 (영력, 마법사, 마법저항)
	FIXED_ARTIFACT_PEACH_HAT, //+4 복숭아 모자 (체력재생+++)
	FIXED_ARTIFACT_BOUNDARY_GLOVES, //+0 경계요괴의 긴 장갑 (탄막+3, 반환)
	FIXED_ARTIFACT_COWGIRL_BOOTS, //+3 카우걸 부츠 (*발차기)
	FIXED_ARTIFACT_STOPWATCH, //특제 스톱워치 (시간정지, EV+6, 마법저항)
	FIXED_ARTIFACT_SNAKE_RING, //뱀의 반지 (힘+4, 체력+15)
	FIXED_ARTIFACT_FROG_RING, //개구리의 반지 (독저항+, +잠수, 수영, *저주)
	FIXED_ARTIFACT_MAX
};

class atifact_infor
{
public:
	int kind;
	int value;

	atifact_infor(int kind_, int value_);
	atifact_infor();
	~atifact_infor();
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
};

artifact_type ring_to_artifact(ring_type kind);
std::string GetAtifactString(std::string lang, artifact_type ring_, int value_);
std::string GetAtifactInfor(artifact_type ring_, int value_);
bool CantBothArtifact(artifact_type left, artifact_type right);
int isGenerateRandart(artifact_type ring_, item_type type);
bool effectartifact(artifact_type kind, int value);
void MakeArtifact(item* item_, int good_bad_, bool cant_fixed = false);

std::string GetFixedArtifact(fixed_artifact_type fixed_artifact, int enchant = 0);
bool IsTypeOfFixedArtifact(fixed_artifact_type fixed_artifact, item_type itemType);
void MakeFixedArtifact(item* item_, fixed_artifact_type fixed_artifact, bool wiz);

#endif // __ATIFACT_H__
