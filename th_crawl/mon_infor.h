//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_infor.h
//
// 내용: 몬스터의 정보들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_INFOR_H__
#define  __MON_INFOR_H__

#include "texture.h"
#include "monster_texture.h"
#include "unit.h"

struct mon_infor
{
	int id;
	int level;
	int exper;
	name_infor name;
	textures *image;
	int max_hp;
	int ac;
	int ev;
	int atk[3];
	attack_type atk_type[3];
	name_infor atk_name[3];
	int flag;
	int resist;
	int sense;
	int speed;
};


enum monster_flag
{
	M_FLAG_OPEN_DOOR = 1<<0, //문을 열 수 있는가?
	M_FLAG_FAIRY = 1<<1, //요정인가?
	M_FLAG_UNIQUE  = 1<<2, //네임드인가?
	M_FLAG_FLY = 1<<3, //나는가?
	M_FLAG_NO_ATK = 1<<4, //공격을 하지 않는가?
	M_FLAG_CONFUSE = 1<<5, //항상 혼란상태인가?
	M_FLAG_SUMMON = 1<<6, //소환되었나?
	M_FLAG_SPEAK = 1<<7, //말하는가?
	M_FLAG_ALLY = 1<<8, //동맹인가?
	M_FLAG_SWIM = 1<<9, //수영이 가능한가?
	M_FLAG_CAN_SEE_INVI = 1<<10, //투명을 볼 수 있는가?
	M_FLAG_CANT_GROUND = 1<<11, //지상에 못올라오는가?
	M_FLAG_EVENT = 1<<12, //이벤트로 등장.(나오자마자 주인공을 타겟)
	M_FLAG_LEADER_SUMMON = 1<<13, //오로지 소환사 주변을 멤돈다
	M_FLAG_PASSED_ALLY = 1<<14, //아군의 원거리 공격을 흘린다.
	M_FLAG_PASSED_ENEMY = 1<<15, //적군의 원거리 공격을 흘린다.
	M_FLAG_NONE_MOVE = 1<<16, //움직이지 않는다.
	M_FLAG_UNHARM = 1<<17, //무해한가?
	M_FLAG_INVISIBLE = 1<<18, //영구 투명
	M_FLAG_ANIMAL = 1<<19  //동물
};



/*
{MON_이미지,레벨,경험치,name_infor(이름,true),&img_mons_이미지,체력,AC,EV,
{공격력,공2,공3},{ATT_종류,ATT_NONE,ATT_NONE},{name_infor(이름,true),name_infor(),name_infor()},
플래그,마법저항,지각력,스피드}
*/
const mon_infor mondata[] = {
	{MON_REIMUYUKKURI,2,4,name_infor("윳쿠리레이무",false),&img_mons_reimu_yukkuri,25,0,5,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15},

	{MON_REIMUYUKKURI,2,70,name_infor("윳쿠리레이무",false),&img_mons_reimu_yukkuri,25,0,5,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15},

	{MON_RAT,1,1,name_infor("쥐",false),&img_mons_rat,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,0,10},

	{MON_FAIRY_GREEN,1,2,name_infor("돌격 요정",true),&img_mons_fairy_green,13,0,8,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_FAIRY_BLUE,2,3,name_infor("탄막 요정",true),&img_mons_fairy_blue,8,0,12,
	{1,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_FAIRY_RED,3,5,name_infor("대장 요정",true),&img_mons_fairy_red,21,2,6,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_MOOK,1,2,name_infor("모옥",true),&img_mons_mook,5,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10},

	{MON_MOOK,1,18,name_infor("모옥",true),&img_mons_mook,5,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10},

	{MON_CROW,1,15,name_infor("까마귀",false),&img_mons_crow,17,0,8,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,7},

	{MON_CRANE,5,46,name_infor("두루미",false),&img_mons_crane,33,3,10,
	{8,8,20},{ATT_NORMAL,ATT_NORMAL,ATT_NORMAL},{name_infor("공격",true),name_infor("공격",true),name_infor("쪼기",false)},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10},

	{MON_SPIDER,3,11,name_infor("거미",false),&img_mons_spider,18,1,10,
	{2,2,3},{ATT_NORMAL,ATT_NORMAL,ATT_S_POISON},{name_infor("공격",true),name_infor("공격",true),name_infor("독니",false)},
	M_FLAG_ANIMAL,0,1,10},

	{MON_SNAKE,4,16,name_infor("뱀",true),&img_mons_snake,22,1,10,
	{4,3,0},{ATT_S_POISON,ATT_NORMAL,ATT_NONE},{name_infor("공격",true),name_infor("공격",true),name_infor()},
	M_FLAG_ANIMAL,0,1,7},

	{MON_KATPA,2,7,name_infor("캇파",false),&img_mons_new_kappa,20,2,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM,0,1,10},

	{MON_KATPA_GUN,5,65,name_infor("캇파 사격병",true),&img_mons_katpa_gun,40,1,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM,0,2,10},

	{MON_FAIRY_GREEN_WARRIOR,5,44,name_infor("요정 전사",false),&img_mons_fairy_green_warroir,35,8,6,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10},

	{MON_FAIRY_BLUE_MAGICIAN,7,63,name_infor("요정 법사",false),&img_mons_fairy_blue_magician,25,2,16,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_FAIRY_RED_COMMANDER,8,86,name_infor("요정 지휘관",true),&img_mons_fairy_red_commander,33,0,6,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_RUMIA,6,87,name_infor("루미아",false),&img_named_rumia,40,1,10,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_MISTIA,8,235,name_infor("미스티아",false),&img_named_mistia,60,1,12,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,8},

	{MON_WRIGGLE,7,130,name_infor("리글",true),&img_named_wriggle,50,3,10,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10},

	{MON_CIRNO,9,399,name_infor("치르노",false),&img_named_cirno,99,1,9,
	{15,25,0},{ATT_NORMAL,ATT_COLD,ATT_NONE},{name_infor("공격",true),name_infor("냉기",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10},

	{MON_MEDICINE,9,466,name_infor("메디슨",true),&img_named_medicine,70,2,10,
	{8,12,0},{ATT_S_POISON,ATT_S_POISON,ATT_NONE},{name_infor("독기",false),name_infor("독기",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10},

	{MON_DIEFAIRY,6,170,name_infor("대요정",true),&img_named_diefairy,50,0,15,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_WOMAN,1,0,name_infor("인간여자",false),&img_mons_human_woman,10,1,10,
	{1,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_MAN,2,8,name_infor("인간남자",false),&img_mons_human_man,20,1,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_YINYANG,5,36,name_infor("음양사",false),&img_mons_human_yinyang,30,1,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_PRIEST,5,52,name_infor("법사",false),&img_mons_human_priest,23,1,10,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_SAMURI,8,110,name_infor("사무라이",false),&img_mons_human_samuri,50,6,8,
	{16,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_FIREFLY,2,5,name_infor("반딧불이",false),&img_mons_firefly,18,1,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10},

	{MON_BUTTERFLY,1,0,name_infor("나비",false),&img_mons_butterfly,5,1,20,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_UNHARM | M_FLAG_NO_ATK | M_FLAG_CONFUSE | M_FLAG_ANIMAL,0,1,5},

	{MON_GHOST,1,2,name_infor("유령",true),&img_mons_ghost[0],10,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,12},

	{MON_BAKEKASA,4,21,name_infor("우산요괴",false),&img_mons_bakekasa,20,1,12,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,1,1,10},

	{MON_GREEN_MOOK,2,6,name_infor("초록모옥",true),&img_mons_green_mook,18,0,10,
	{4,4,8},{ATT_NORMAL,ATT_NORMAL,ATT_S_POISON},{name_infor("공격",true),name_infor("공격",true),name_infor("공격",true)},
	M_FLAG_FLY,0,0,10},

	{MON_ORANGE_MOOK,3,11,name_infor("주황모옥",true),&img_mons_orange_mook,22,0,14,
	{9,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10},

	{MON_GRAY_MOOK,4,23,name_infor("회색모옥",true),&img_mons_gray_mook,18,1,10,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10},

	{MON_FROG,7,74,name_infor("개구리",false),&img_mons_frog,60,1,14,
	{16,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SWIM | M_FLAG_ANIMAL,0,0,9},
	
	{MON_BLACK_CAT,8,87,name_infor("검은고양이",false),&img_mons_black_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("할퀴기",false),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7},
	
	{MON_ORANGE_CAT,8,87,name_infor("주황고양이",false),&img_mons_orange_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("할퀴기",false),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7},

	{MON_WHITE_CAT,8,87,name_infor("하얀고양이",false),&img_mons_white_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("할퀴기",false),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7},

	{MON_CROW_TENGU,10,132,name_infor("까마귀텐구",false),&img_mons_crow_tengu,70,3,12,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10},

	{MON_ONI,14,412,name_infor("오니",false),&img_mons_oni,120,10,2,
	{35,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,10},

	{MON_KISUME,5,70,name_infor("키스메",false),&img_named_kisume,30,1,10,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10},

	{MON_CHEN,11,425,name_infor("첸",true),&img_named_chen,85,0,15,
	{15,15,20},{ATT_NORMAL,ATT_NORMAL,ATT_NORMAL},{name_infor("할퀴기",false),name_infor("할퀴기",false),name_infor("할퀴기",false)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,8},

	{MON_KOGASA,7,150,name_infor("코가사",false),&img_named_kogasa,50,1,14,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},

	{MON_SUNNY,4,49,name_infor("써니",false),&img_named_sunny,35,1,10,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_LUNAR,4,49,name_infor("루나",false),&img_named_lunar,30,1,10,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10},

	{MON_STAR,4,49,name_infor("스타",false),&img_named_star,25,1,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,10,10},

	{MON_MARISAYUKKURI,8,70,name_infor("윳쿠리마리사",false),&img_mons_marisa_yukkuri,70,2,5,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15},

	{MON_AYAYUKKURI,12,210,name_infor("키메이마루",false),&img_mons_aya_yukkuri,65,0,16,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,1,1,4},

	{MON_REMILIAYUKKURI,14,340,name_infor("윳쿠리레미랴",false),&img_mons_remila_yukkuri,60,5,12,
	{18,27,0},{ATT_VAMP,ATT_VAMP,ATT_NONE},{name_infor("물기",false),name_infor("물기",false),name_infor()},
	M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,3,1,8}, //나중에 흡혈 공격으로 바꿈

	{MON_ALICEYUKKURI,11,160,name_infor("윳쿠리앨리스",false),&img_mons_alice_yukkuri,100,7,5,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,1,0,15},

	{MON_YOUMUYUKKURI,11,160,name_infor("윳쿠리요우무",false),&img_mons_default,70,2,10,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,10}, //나중에 천천히 추가


	{MON_YAMABIKO,9,62,name_infor("야마비코",false),&img_mons_yamabiko,75,2,10,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR,0,0,10},

	{MON_KATPA_SPEAR,9,130,name_infor("캇파 창병",true),&img_mons_new_kappa_spear,70,5,10,
	{20,0,0},{ATT_SPEAR,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR | M_FLAG_SWIM,0,0,10},

	{MON_KATPA_WATER_WIZARD,10,160,name_infor("캇파 수술사",false),&img_mons_new_kappa_wizard,45,4,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR | M_FLAG_SWIM,1,0,10},

	{MON_YAMABUSH_TENGU,11,262,name_infor("야마부시텐구",false),&img_mons_yamabush_tengu,60,3,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI,1,1,10},


	{MON_HANATACA_TENGU,12,383,name_infor("하나타카텐구",false),&img_mons_hanataca_tengu,78,5,13,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10},


	{MON_BLUE_ONI,13,412,name_infor("아오오니",false),&img_mons_blue_oni,120,10,2,
	{35,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},

	{MON_MUSHROOM,9,132,name_infor("버섯요괴",false),&img_mons_mushroom,50,6,0,
	{20,0,0},{ATT_S_POISON,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,10},

	{MON_KYOUKO,6,100,name_infor("쿄코",false),&img_named_kyouko,35,1,12,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},


	{MON_SIGMUND,3,104,name_infor("지그문트",false),&img_named_sigmund,30,0,11,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},

	{MON_WOLF_TENGU,12,312,name_infor("백랑 텐구",false),&img_mons_default,49,12,2,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,2,13},

	{MON_MOMIZI,12,923,name_infor("모미지",false),&img_named_momizi,132,12,2,
	{32,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,3,10},

	{MON_AYA,15,1421,name_infor("아야",false),&img_named_aya,112,1,14,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,8},

	
	{MON_TEST_KATPA,2,50,name_infor("캇파",false),&img_mons_katpa,20,2,5,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM,0,1,10},

	//여기부터 임시 정보들
	{MON_WAKASAGI,6,100,name_infor("와카사기히메",false),&img_named_wakasagi,40,0,13,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SWIM | M_FLAG_SPEAK | M_FLAG_CANT_GROUND,0,1,10},

	{MON_YAMAME,8,354,name_infor("야마메",false),&img_named_yamame,90,3,6,
	{15,16,24},{ATT_NORMAL,ATT_NONE,ATT_S_POISON},{name_infor("공격",true),name_infor("공격",true),name_infor("독기",false)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},
	
	{MON_NAZRIN,7,270,name_infor("나즈린",true),&img_named_nazrin,45,0,8,
	{14,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},

	{MON_DAUZING,10,1,name_infor("펜듈럼",true),&img_mons_dauzing,80,8,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_FLY,99,0,8},
	
	{MON_YOSIKA,9,360,name_infor("요시카",false),&img_named_yosika,150,1,3,
	{22,30,30},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor("깨물기",false),name_infor("깨물기",false)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,10},
	
	{MON_SEKIBANKI,8,324,name_infor("세키반키",false),&img_named_sekibanki,70,3,9,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,1,10},
	
	{MON_SEKIBANKI_BODY,8,324,name_infor("세키반키",false),&img_named_sekibanki_body,70,10,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_CAN_SEE_INVI,1,0,10},
	
	{MON_SEKIBANKI_HEAD,1,1,name_infor("세키반키",false),&img_named_sekibanki_head,30,0,15,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("물기",false),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI,0,1,10},
	
	{MON_NITORI,13,1088,name_infor("니토리",false),&img_named_nitori,100,8,12,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10},
	
	{MON_KEGERO,10,497,name_infor("카게로",false),&img_named_kagero,120,3,12,
	{30,25,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("물기",false),name_infor("할퀴기",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},
	
	{MON_PARSI,9,325,name_infor("파르시",false),&img_named_parsi,100,8,15,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},
	
	{MON_BENBEN,6,120,name_infor("벤벤",true),&img_named_benben,60,3,3,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10},
	
	{MON_YATHASI,6,120,name_infor("야츠하시",false),&img_named_yathasi,50,0,8,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10},
	
	{MON_ORIN,13,1010,name_infor("오린",true),&img_named_orin,95,1,12,
	{29,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},
	
	{MON_ORIN_CAT,13,1010,name_infor("오린",true),&img_named_orin_cat,70,0,18,
	{21,21,0},{ATT_NORMAL,ATT_FIRE,ATT_NONE},{name_infor("할퀴기",false),name_infor("할퀴기",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,5},
	
	{MON_ZOMBIE_FAIRY,7,83,name_infor("좀비페어리",false),&img_mons_zombiefairy,35,0,12,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10},
	
	{MON_ICHIRIN,13,1240,name_infor("이치린",true),&img_named_ichirin,98,8,2,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},
	
	{MON_UNZAN,13,1,name_infor("운잔",true),&img_named_unzan,150,0,0,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON,99,1,10},
	
	{MON_UNZAN_PUNCH,13,1,name_infor("운잔의 주먹",true),&img_named_unzan_punch[0],30,0,6,
	{32,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("스매쉬",false),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY  | M_FLAG_PASSED_ALLY,99,1,15},
	
	{MON_PACHU,12,923,name_infor("파츄리",false),&img_named_pachu,70,1,5,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,99,1,10},
	
	{MON_MAGIC_BOOK,10,130,name_infor("마법서",false),&img_mons_magic_book[0],50,0,13,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_NO_ATK,99,1,8},
	 
	{MON_HOBGOBRIN,6,42,name_infor("홉고블린",true),&img_mons_hobgobrin,40,1,6,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},
	
	{MON_HOBGOBRIN_MAID,8,92,name_infor("홉고블린 메이드",false),&img_mons_hobgobrin_maid,80,6,6,
	{24,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},

	{MON_HOBGOBRIN_LIBRARIAN,11,120,name_infor("홉고블린 사서",false),&img_mons_hobgobrin_librarian,70,1,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},
	
	{MON_HOBGOBRIN_TEMP,13,210,name_infor("홉고블린 악마술사",true),&img_mons_hobgobrin_temp,70,0,6,
	{11,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},
	
	{MON_MAID_FAIRY,7,71,name_infor("요정 메이드",false),&img_mons_maid_fairy,32,1,12,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10},
	
	{MON_CHUPARCABRA,12,284,name_infor("추파카브라",false),&img_mons_chuparcabra,122,3,14,
	{23,0,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,7},
	
	{MON_KOAKUMA,1,1,name_infor("소악마",false),&img_named_koakuma,60,1,6,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10},
	
	{MON_MEIRIN,8,1,name_infor("홍메이린",true),&img_named_meirin,90,8,6,
	{30,14,14},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("철산고",false),name_infor("공격",true),name_infor("공격",true)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10},
	
	{MON_SAKUYA,13,1072,name_infor("사쿠야",false),&img_named_sakuya,100,1,18,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},
	
	{MON_REMILIA,15,1521,name_infor("레밀리아",false),&img_named_remilia,120,1,20,
	{24,24,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("흡혈",true),name_infor("공격",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,9},
	
	{MON_EAGLE,9,121,name_infor("거대 매",false),&img_mons_eagle,60,1,10,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10},
	
	{MON_TIGER,11,180,name_infor("호랑이",false),&img_mons_tiger,93,3,6,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_ANIMAL ,0,1,10},
	
	{MON_RAIJUU,10,150,name_infor("뇌수",false),&img_mons_raijuu,50,1,8,
	{15,0,0},{ATT_S_POISON,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,8},
	
	{MON_DRAGON_BABY,12,260,name_infor("용의 새끼",false),&img_mons_dragon_baby,10,0,6,
	{14,14,27},{ATT_NORMAL,ATT_NONE,ATT_FIRE},{name_infor("공격",true),name_infor("공격",true),name_infor("물기",false)},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_ANIMAL,1,1,10},
	
	{MON_KASEN,14,872,name_infor("카센",true),&img_named_kasen,150,5,6,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},
	
	{MON_YAMAWARO_NINJA,8,93,name_infor("야마와로 투척병",true),&img_mons_yamawaro_ninja,62,5,7,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},
	
	{MON_YAMAWARO_WAWRRIOR,9,143,name_infor("야마와로 돌격병",true),&img_mons_yamawaro_warrior,80,5,6,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},
	
	{MON_YAMAWARO_FLAG,11,210,name_infor("야마와로 깃발병",true),&img_mons_yamawaro_flag,60,7,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},
		
	{MON_ONBASIRA,1,1,name_infor("온바시라",true),&img_mons_onbasira,60,10,0,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY ,99,0,10},
	
	{MON_RED_UFO,12,180,name_infor("레드 벤토라",false),&img_mons_red_ufo,95,5,10,
	{30,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,9},
	
	{MON_GREEN_UFO,12,180,name_infor("그린 벤토라",false),&img_mons_green_ufo,95,5,10,
	{30,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,9},
		
	{MON_BLUE_UFO,12,180,name_infor("블루 벤토라",false),&img_mons_blue_ufo,95,5,10,
	{30,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,9},
		
	
	{MON_KOISHI,13,880,name_infor("코이시",false),&img_named_koishi,70,3,18,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_INVISIBLE | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,3,1,7},
	{MON_NUE,14,1140,name_infor("누에",false),&img_named_nue,140,10,6,
	{18,25,0},{ATT_SPEAR,ATT_ELEC,ATT_NONE},{name_infor("공격",true),name_infor("공격",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},
	{MON_SANPEI_FIGHTER,12,301,name_infor("산페이파이터",false),&img_mons_sanpei_fighter,120,15,6,
	{26,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("드릴",false),name_infor(),name_infor()},
	M_FLAG_FLY,99,1,8},
	{MON_VAMPIER_BAT,9,124,name_infor("흡혈 박쥐",false),&img_mons_vamp_bat,60,0,20,
	{14,0,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_ANIMAL,0,1,5},
	{MON_DEAGAMA,1,1,name_infor("큰두꺼비",false),&img_mons_dagama,80,10,2,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_SWIM,3,1,10},
	{MON_RABBIT,1,1,name_infor("토끼",false),&img_mons_rabit,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,10},
	{MON_YOKAI_RABBIT,1,1,name_infor("요괴 토끼",false),&img_mons_youkai_rabit,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,1,1,10},
	{MON_NAMAZ,1,1,name_infor("나마즈",false),&img_mons_namaz,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,1,1,10},
	{MON_HELL_CROW,1,1,name_infor("지옥까마귀",false),&img_mons_hell_crow,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,10},
	{MON_RACCON,1,1,name_infor("너구리",false),&img_mons_raccoon,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,10},
	{MON_LANTERN_YOUKAI,1,1,name_infor("제등요괴",false),&img_mons_lantern_youkai,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,2,1,10},
	{MON_YINYAN,1,1,name_infor("음양옥",true),&img_mons_yinyan,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,99,1,10},
	{MON_YUUGENMAGAN,1,1,name_infor("유겐마간",true),&img_mons_yugenmagan,100,12,10,
	{15,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,99,1,10},
	{MON_ELIS,9,135,name_infor("엘리스",false),&img_mons_elise,70,0,12,
	{15,10,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,2,1,6},
	{MON_SARIEL,1,1,name_infor("사리엘",true),&img_mons_sariel,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,99,1,10},
	{MON_SARA,9,135,name_infor("사라",false),&img_mons_sara,85,15,5,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,1,1,10},
	{MON_LUIZE,9,135,name_infor("루이즈",false),&img_mons_louise,75,1,12,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,2,1,10},		
	{MON_YUKI,14,432,name_infor("유키",false),&img_mons_yuki,130,8,15,
	{25,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,2,1,10},		
	{MON_MAI,14,432,name_infor("마이",false),&img_mons_mai,130,8,15,
	{25,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,2,1,10},		
	{MON_YUMEKO,16,672,name_infor("유메코",false),&img_mons_yumeko,180,3,16,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,4,1,10},

	{MON_MAGICAL_STAR,4,1,name_infor("옵션",true),&img_mons_option,30,0,12,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_FLY,99,0,5},

	{MON_GOLEM,8,1,name_infor("골렘",true),&img_mons_golem,80,10,0,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,99,0,10},
	{MON_EVIL_EYE,3,15,name_infor("이블아이",false),&img_mons_evil_eye,20,0,8,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,0,1,10},
	{MON_LITTLE_IMP,3,15,name_infor("마족 자코",false),&img_mons_little_imp,25,1,15,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,0,1,10},
	
	{MON_ENSLAVE_GHOST,1,2,name_infor("유령",true),&img_mons_ghost[0],10,0,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,12},

	{MON_SCHEMA_EYE,4,1,name_infor("변용을 보는 눈",true),&img_mons_schema_eye,30,0,12,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NONE_MOVE  | M_FLAG_CAN_SEE_INVI  | M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_FLY,99,0,10},
	
	{MON_FLAN,21,7999,name_infor("플랑드르",false),&img_named_flandre,230,10,15,
	{31,28,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("흡혈",true),name_infor("공격",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,10},

	{MON_FLAN_BUNSIN,21,0,name_infor("플랑드르의 분신",false),&img_named_flandre,80,5,10,
	{18,15,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("흡혈",true),name_infor("공격",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY,3,1,10},

	
	{MON_RABIT_BOMB,9,20,name_infor("토끼 자폭병",true),&img_mons_bomb_rabbit,12,1,20,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,9},
	
	{MON_RABIT_SPEAR,11,40,name_infor("토끼 죽창병",true),&img_mons_spear_rabbit,35,5,15,
	{28,0,0},{ATT_SPEAR,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},
	
	{MON_RABIT_SUPPORT,12,40,name_infor("토끼 지원병",true),&img_mons_support_rabbit,25,3,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_CAN_SEE_INVI |  M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,2,10},

	{MON_RABIT_MAGIC,10,70,name_infor("토끼 마법사",false),&img_mons_magic_rabbit,30,2,20,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL |  M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},

	
	{MON_TEWI,13,550,name_infor("테위",false),&img_named_tewi,60,3,22,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,8},

	{MON_CLOWNPIECE,15,1220,name_infor("클라운피스",false),&img_named_clownpiece,120,3,18,
	{22,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("횃불",true),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,1,1,8},
	
	{MON_DOREMI,14,904,name_infor("도레미",false),&img_named_doremi,130,8,10,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,3,1,12}
};


bool is_exist_named(monster_index id); //해당 네임드가 출현확정되어있는지
void set_exist_named(monster_index id); //네임드를 출현확정(벌트등으로)
void unset_exist_named(monster_index id);

void create_mon(int floor, int num_);
void init_monster();

struct unique_infor
{
	int id;
	int level;
	unique_infor(int id_=0,int level_=0):id(id_),level(level_){};
};

extern vector<unique_infor> unique_list;
void SetResistMonster(monster* mon);

string GetMonsterInfor(monster *it);

#endif // __MON_INFOR_H__