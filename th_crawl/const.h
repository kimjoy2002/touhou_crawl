//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: const.h
//
// 내용: const관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __CONST_H__
#define  __CONST_H__



#include "d3dUtility.h"
#include "enum.h"

class name_infor;

extern const char *tribe_type_string[]; //종족스트링
extern const char *job_type_string[]; //직업스트링

extern const bool tribe_string_back[];
extern const bool job_string_back[];


extern const char *dungeon_tile_tribe_type_string[]; //타일스트링

extern const char *state_string[]; //상태이상스트링

extern const char *rune_string[];



extern const D3DCOLOR CL_normal; //색깔
extern const D3DCOLOR CL_bad;
extern const D3DCOLOR CL_verybad;
extern const D3DCOLOR CL_none;
extern const D3DCOLOR CL_help; 
extern const D3DCOLOR CL_good;
extern const D3DCOLOR CL_dark_good;
extern const D3DCOLOR CL_blue;
extern const D3DCOLOR CL_white_blue;
extern const D3DCOLOR CL_tensi;
extern const D3DCOLOR CL_alchemy;
extern const D3DCOLOR CL_green;
extern const D3DCOLOR CL_yuigi;
extern const D3DCOLOR CL_hina;
extern const D3DCOLOR CL_warning;
extern const D3DCOLOR CL_small_danger; 
extern const D3DCOLOR CL_danger; 
extern const D3DCOLOR CL_STAT;
extern const D3DCOLOR CL_speak;
extern const D3DCOLOR CL_magic;
extern const D3DCOLOR CL_white_puple;
extern const D3DCOLOR CL_yuyuko;
extern const D3DCOLOR CL_yukari;
extern const D3DCOLOR CL_swako;
extern const D3DCOLOR CL_autumn;
extern const D3DCOLOR CL_seija;
extern const D3DCOLOR CL_lilly;
extern const name_infor string_that;
extern const name_infor string_something;

extern const char *item_weapon_string;
extern const char *item_throw_string;
extern const char *item_armor_string;
extern const char *item_potion_string;
extern const char *item_food_string;
extern const char *item_scroll_string;
extern const char *item_spell_string;
extern const char *item_jewelry_string;
extern const char *item_book_string;
extern const char *item_miscellaneous_string;
extern const char *item_goal_string;
extern const char *item_other_string;


extern const int level_up_value[];


#endif // __CONST_H__