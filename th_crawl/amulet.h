//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: amulet.h
//
// 내용: 아뮬렛
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __AMULET_H__
#define  __AMULET_H__


enum amulet_type
{
	AMT_PERFECT = 0, //완전무결, 100%가 되면 부활
	AMT_BLOSSOM, //삼라결계, 100%가 되면 영격발동
	AMT_TIMES, //각부, 100%가 되면 파워생산
	AMT_FAITH, //신앙, 100%가 되면 자동으로 신앙 증가
	AMT_WAVE, //전파, 100%가 되면 영력재생증가 100%가 되면 영력회복
	AMT_SPIRIT, //신령, 100%가 되면 스펠카드 충전
	AMT_GRAZE, //그레이즈, 100%가 되면 그레이즈상태, 발동시 근성회피
	AMT_WEATHER, //날씨, 사용시 무작위 날씨 발동 + 체젠증가
	AMT_OCCULT, //오컬트, 100%가 되면 소환물 추방가능 + 소환하기
	AMT_MAX,
};
//부적은 컨셉플레이에 맞게 바꾸는게 맞을 것 같음
//지우기(너무 범용성있는 경우)
//날씨 (체젠) -> 무작위 날씨 발동 + 체젠증가
//각보 (가속) -> 파워
//전파 (약함) -> 마나 증가


enum occult_type
{
	OCT_NESI = 0,
	OCT_LONG,
	OCT_SHORT,
	OCT_DISH,
	OCT_KUNEKUNE,
	OCT_MAX
};


extern char *amulet_uniden_string[AMT_MAX];
extern const char *amulet_iden_string[AMT_MAX];


int isAmuletGotValue(amulet_type amulet_);
amulet_type goodbadamulet(int good_bad);
int isGoodAmulet(amulet_type kind, int value);
bool equipamulet(amulet_type kind, int value); //리턴값: 식별시 true 미식별시 false
bool unidenequipamulet(amulet_type kind, int value); //리턴값: 식별시 true 미식별시 false
float getAmuletCharge(amulet_type kind);
bool isCanCharge(amulet_type kind);
bool isCanEvoke(amulet_type kind);
bool chargingFinish(amulet_type kind, int value);
bool evokeAmulet(amulet_type kind, int value_);
const char* getOccultName(occult_type kind);

#endif // __AMULET_H__
