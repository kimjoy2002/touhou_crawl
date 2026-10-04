//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ice_item.h
//
// 내용: 치르노의 얼음 아이템
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ICE_ITEM_H__
#define __ICE_ITEM_H__

#include "item.h"

enum ice_item_kind
{
	ICE_ITEM_SWORD,
	ICE_ITEM_DAGGER,
	ICE_ITEM_CRASHER,
	ICE_ITEM_SPEAR,
	ICE_ITEM_AXE,
	ICE_ITEM_ICICLE,
	ICE_ITEM_RING,
	ICE_ITEM_CROWN,
	ICE_ITEM_CREAM,
	ICE_ITEM_ARMOUR,
	ICE_ITEM_GLOVES,
	ICE_ITEM_BOOTS,
	ICE_ITEM_CLOAK,
	ICE_ITEM_BOOK,
	ICE_ITEM_FROG,
	ICE_ITEM_MAX
};

item MakeIceItem(ice_item_kind kind_, int power);
LOCALIZATION_ENUM_KEY GetIceItemDescription(item* item_);
bool CreateIceItem(int power);
void ClearIceItemCandidates();

#endif // __ICE_ITEM_H__
