//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: scroll.h
//
// 내용: scroll관련 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SCROLL_H__
#define  __SCROLL_H__


#include "player.h"
#include "item.h"


enum scroll_type
{
	SCT_TELEPORT = 0,
	SCT_IDENTIFY,
	SCT_NONE,
	SCT_CURSE_WEAPON,
	SCT_CURSE_ARMOUR,
	SCT_REMOVE_CURSE,
	SCT_BLINK,
	SCT_MAPPING,
	SCT_ENCHANT_WEAPON_1,
	SCT_ENCHANT_WEAPON_2,
	SCT_ENCHANT_ARMOUR,
	SCT_FOG,
	SCT_DETECT_CURSE,
	SCT_CURSE_JEWELRY,
	SCT_SILENCE,
	SCT_SOUL_SHOT,
	SCT_CHARGING,
	SCT_AMNESIA,
	SCT_SANTUARY,
	SCT_BRAND_WEAPON,
	SCT_MAX
};



scroll_type goodbadscroll(int good_bad);

extern char *scroll_uniden_string[SCT_MAX]; //스크롤 스트링
extern const char *scroll_iden_string[SCT_MAX];

int isGoodScroll(scroll_type kind);
bool readscroll(scroll_type kind, bool pre_iden_, bool waste_);

#endif // __SCROLL_H__