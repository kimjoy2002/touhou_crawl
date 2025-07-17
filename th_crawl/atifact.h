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
	ART_MAX_ATIFACT,
};


enum fixed_artifact_type {
	FIXED_ARTIFACT_NONE,
	FIXED_ARTIFACT_HAKKERO,//미니 팔괘로
	FIXED_ARTIFACT_GUNGNIR, //궁니르
	FIXED_ARTIFACT_ROUKANKEN,//누관검
	FIXED_ARTIFACT_HAKUROUKEN,//백루검
	FIXED_ARTIFACT_KOISHIHAT,//코이시의 모자
	FIXED_ARTIFACT_MIKOCLOAK,//위정자의 망토
	FIXED_ARTIFACT_LUNATICTORCH,//광기의 횃불
	FIXED_ARTIFACT_MOONGEM,//달의 보옥
	FIXED_ARTIFACT_NUCLEARBOOT,//핵융합의 다리
	FIXED_ARTIFACT_CONTROLROD,//제어봉
	FIXED_ARTIFACT_PICKANDSHOVELS,//지네의 삽과 곡괭이
	FIXED_ARTIFACT_SILVERKNIFE,//메이드 특제 나이프
	FIXED_ARTIFACT_FIREFLYCLOAK,//+2 반딧불 망토 {*벌레, 독저항}
	FIXED_ARTIFACT_ICEFAIRYRING,//얼음 요정의 반지 {냉기저항+, 화염저항-, 냉기마법+4}
	FIXED_ARTIFACT_LAEVATEIN,// +11 레바테인 {화염, 불길, AC-4)
	FIXED_ARTIFACT_LILYRING,//은방울꽃 반지 (독면역, AC+5)
	FIXED_ARTIFACT_GALECLOGS,//+0 질풍 나막신 {질풍, EV+4}
	FIXED_ARTIFACT_HELLTSHIRT,//+6 지옥 티셔츠 {STR+6 INT-6 DEX+6}
	FIXED_ARTIFACT_KAPPAFULLARMOR,//+12 풀무장 캇파옷 {+미사일, *자폭, 화염저항+, 냉기저항+}
	FIXED_ARTIFACT_MAIDUNIFORM,//+4 마계 메이드옷 {마법저항, 소환저항, EV+5, INT+5, 마법사}
	FIXED_ARTIFACT_IBUKISAKE,//+7 이부키효 {음주, 체력재생++, 독저항}
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
void MakeArtifact(item* item_, int good_bad_);

std::string GetFixedArtifact(fixed_artifact_type fixed_artifact);
bool IsTypeOfFixedArtifact(fixed_artifact_type fixed_artifact, item_type itemType);
void MakeFixedArtifact(item* item_, fixed_artifact_type fixed_artifact, bool wiz);

#endif // __ATIFACT_H__