//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: monster_list.cpp
//
// 내용: 몬스터의 정보들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "mon_infor.h"




/*
{MON_이미지,레벨,경험치,name_infor(이름,true),&img_mons_이미지,체력,AC,EV,
{공격력,공2,공3},{ATT_종류,ATT_NONE,ATT_NONE},{name_infor(이름,true),name_infor(),name_infor()},
플래그,마법저항,지각력,스피드}
*/
const mon_infor mondata[] = {
	{MON_REIMUYUKKURI,2,4,name_infor(MON_REIMUYUKKURI),&img_mons_reimu_yukkuri,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15,'y'},

	{MON_REIMUYUKKURI,2,70,name_infor(MON_REIMUYUKKURI),&img_mons_reimu_yukkuri,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,0,0,15,'y'},

	{MON_RAT,1,1,name_infor(MON_RAT),&img_mons_rat,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,0,10,'r'},

	{MON_FAIRY_GREEN,1,2,name_infor(MON_FAIRY_GREEN),&img_mons_fairy_green,13,0,8,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f'},

	{MON_FAIRY_BLUE,2,3,name_infor(MON_FAIRY_BLUE),&img_mons_fairy_blue,8,0,12,
	{1,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f'},

	{MON_FAIRY_RED,3,5,name_infor(MON_FAIRY_RED),&img_mons_fairy_red,21,2,6,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f'},

	{MON_MOOK,1,2,name_infor(MON_MOOK),&img_mons_mook,5,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10,'m'},

	{MON_MOOK,1,18,name_infor(MON_MOOK),&img_mons_mook,5,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_CANT_NETURAL,0,0,10,'m' },

	{MON_CROW,2,4,name_infor(MON_CROW),&img_mons_crow,17,0,8,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,7,'c' },

	{MON_CRANE,5,116,name_infor(MON_CRANE),&img_mons_crane,30,3,10,
	{8,8,20},{ATT_NORMAL,ATT_NORMAL,ATT_NORMAL},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_PECK)},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10,'C' },

	{MON_SPIDER,3,11,name_infor(MON_SPIDER),&img_mons_spider,18,1,10,
	{2,2,3},{ATT_NORMAL,ATT_NORMAL,ATT_S_POISON},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_VENOM_TEETH)},
	M_FLAG_ANIMAL,0,1,10,'s'},

	{MON_SNAKE,4,21,name_infor(MON_SNAKE),&img_mons_snake,22,1,10,
	{4,3,0},{ATT_S_POISON,ATT_NORMAL,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor()},
	M_FLAG_ANIMAL,0,1,7,'s'},

	{MON_KATPA,2,7,name_infor(MON_KATPA),&img_mons_new_kappa,20,2,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM,0,1,10,'k'},

	{MON_KATPA_GUN,5,65,name_infor(MON_KATPA_GUN),&img_mons_katpa_gun,40,1,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM | M_FLAG_CANT_NETURAL,0,2,10,'k'},

	{MON_FAIRY_GREEN_WARRIOR,5,128,name_infor(MON_FAIRY_GREEN_WARRIOR),&img_mons_fairy_green_warroir,35,8,6,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'f'},

	{MON_FAIRY_BLUE_MAGICIAN,7,150,name_infor(MON_FAIRY_BLUE_MAGICIAN),&img_mons_fairy_blue_magician,25,2,16,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f' },

	{MON_FAIRY_RED_COMMANDER,8,214,name_infor(MON_FAIRY_RED_COMMANDER),&img_mons_fairy_red_commander,33,0,6,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f' },

	{MON_RUMIA,6,240,name_infor(MON_RUMIA),&img_named_rumia,40,1,10,
	{14,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'&' },

	{MON_MISTIA,8,535,name_infor(MON_MISTIA),&img_named_mistia,55,1,12,
	{11,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,8,'&' },

	{MON_WRIGGLE,7,350,name_infor(MON_WRIGGLE),&img_named_wriggle,50,3,10,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'&' },

	{MON_CIRNO,9,999,name_infor(MON_CIRNO),&img_named_cirno,99,1,9,
	{15,25,0},{ATT_NORMAL,ATT_COLD,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_COLD),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10,'&' },

	{MON_MEDICINE,9,1066,name_infor(MON_MEDICINE),&img_named_medicine,75,2,10,
	{8,12,0},{ATT_S_POISON,ATT_M_POISON,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_POISON),name_infor(LOC_SYSTEM_ATT_POISON),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10,'&' },

	{MON_DIEFAIRY,6,570,name_infor(MON_DIEFAIRY),&img_named_diefairy,50,0,15,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'&' },

	{MON_HUMAM_WOMAN,1,0,name_infor(MON_HUMAM_WOMAN),&img_mons_human_woman,10,1,10,
	{1,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,0,1,10,'h'},

	{MON_HUMAM_MAN,2,8,name_infor(MON_HUMAM_MAN),&img_mons_human_man,20,1,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h'},

	{MON_HUMAM_YINYANG,4,66,name_infor(MON_HUMAM_YINYANG),&img_mons_human_yinyang,30,1,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h'},

	{MON_HUMAM_PRIEST,5,92,name_infor(MON_HUMAM_PRIEST),&img_mons_human_priest,23,1,10,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h'},

	{MON_HUMAM_SAMURI,8,210,name_infor(MON_HUMAM_SAMURI),&img_mons_human_samuri,50,6,8,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h'},

	{MON_FIREFLY,2,5,name_infor(MON_FIREFLY),&img_mons_firefly,18,1,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10,'s'},

	{MON_BUTTERFLY,1,0,name_infor(MON_BUTTERFLY),&img_mons_butterfly,5,1,20,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_UNHARM | M_FLAG_NO_ATK | M_FLAG_CONFUSE | M_FLAG_ANIMAL | M_FLAG_CANT_NETURAL,0,1,5,'b'},

	{MON_GHOST,1,2,name_infor(MON_GHOST),&img_mons_ghost[0],10,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_CANT_NETURAL,0,0,12,'g'},

	{MON_BAKEKASA,4,21,name_infor(MON_BAKEKASA),&img_mons_bakekasa,20,1,12,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	0,1,1,10,'('},

	{MON_GREEN_MOOK,2,6,name_infor(MON_GREEN_MOOK),&img_mons_green_mook,18,0,10,
	{4,4,8},{ATT_NORMAL,ATT_NORMAL,ATT_S_POISON},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_NORMAL)},
	M_FLAG_FLY,0,0,10,'m'},

	{MON_ORANGE_MOOK,3,11,name_infor(MON_ORANGE_MOOK),&img_mons_orange_mook,22,0,14,
	{9,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10,'m' },

	{MON_GRAY_MOOK,4,23,name_infor(MON_GRAY_MOOK),&img_mons_gray_mook,18,1,10,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10,'m' },

	{MON_FROG,7,224,name_infor(MON_FROG),&img_mons_frog,60,1,14,
	{16,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SWIM | M_FLAG_ANIMAL,0,0,9,'f' },
	
	{MON_BLACK_CAT,8,237,name_infor(MON_BLACK_CAT),&img_mons_black_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_CLAW),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7,'c'},
	
	{MON_ORANGE_CAT,8,237,name_infor(MON_ORANGE_CAT),&img_mons_orange_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_CLAW),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7,'c' },

	{MON_WHITE_CAT,8,237,name_infor(MON_WHITE_CAT),&img_mons_white_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_CLAW),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7,'c' },

	{MON_CROW_TENGU,10,532,name_infor(MON_CROW_TENGU),&img_mons_crow_tengu,70,3,12,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10,'t' },

	{MON_ONI,14,1412,name_infor(MON_ONI),&img_mons_oni,120,10,2,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,10,'O' },

	{MON_KISUME,5,220,name_infor(MON_KISUME),&img_named_kisume,30,1,10,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10,'&' },

	{MON_CHEN,11,1325,name_infor(MON_CHEN),&img_named_chen,85,0,15,
	{15,15,20},{ATT_NORMAL,ATT_NORMAL,ATT_NORMAL},{name_infor(LOC_SYSTEM_ATT_CLAW),name_infor(LOC_SYSTEM_ATT_CLAW),name_infor(LOC_SYSTEM_ATT_CLAW)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,8,'&' },

	{MON_KOGASA,7,550,name_infor(MON_KOGASA),&img_named_kogasa,50,1,14,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },

	{MON_SUNNY,4,129,name_infor(MON_SUNNY),&img_named_sunny,35,1,10,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'&' },

	{MON_LUNAR,4,129,name_infor(MON_LUNAR),&img_named_lunar,30,1,10,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10,'&' },

	{MON_STAR,4,129,name_infor(MON_STAR),&img_named_star,25,1,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,10,10,'&' },

	{MON_MARISAYUKKURI,8,270,name_infor(MON_MARISAYUKKURI),&img_mons_marisa_yukkuri,70,2,5,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15,'y'},

	{MON_AYAYUKKURI,12,610,name_infor(MON_AYAYUKKURI),&img_mons_aya_yukkuri,65,0,16,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK,1,1,4,'Y'},

	{MON_REMILIAYUKKURI,14,1040,name_infor(MON_REMILIAYUKKURI),&img_mons_remila_yukkuri,60,5,12,
	{18,30,0},{ATT_VAMP,ATT_VAMP,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_BITE),name_infor(LOC_SYSTEM_ATT_BITE),name_infor()},
	M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,3,1,8,'Y' }, //나중에 흡혈 공격으로 바꿈

	{MON_ALICEYUKKURI,11,660,name_infor(MON_ALICEYUKKURI),&img_mons_alice_yukkuri,100,7,5,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK,2,0,15,'Y' },

	{MON_YOUMUYUKKURI,15,840,name_infor(MON_YOUMUYUKKURI),&img_mons_youmu_yukkuri,90,10,10,
	{36,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,0,9,'Y' }, //나중에 천천히 추가


	{MON_YAMABIKO,9,562,name_infor(MON_YAMABIKO),&img_mons_yamabiko,75,2,10,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR,0,0,10,'d' },

	{MON_KATPA_SPEAR,9,730,name_infor(MON_KATPA_SPEAR),&img_mons_new_kappa_spear,70,5,10,
	{24,0,0},{ATT_SPEAR,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR | M_FLAG_SWIM,0,0,10,'K' },

	{MON_KATPA_WATER_WIZARD,10,860,name_infor(MON_KATPA_WATER_WIZARD),&img_mons_new_kappa_wizard,45,4,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR | M_FLAG_SWIM | M_FLAG_CAN_SEE_INVI,2,1,10,'K' },

	{MON_YAMABUSH_TENGU,11,1062,name_infor(MON_YAMABUSH_TENGU),&img_mons_yamabush_tengu,60,3,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI,1,1,10,'T' },


	{MON_HANATACA_TENGU,12,1183,name_infor(MON_HANATACA_TENGU),&img_mons_hanataca_tengu,78,5,13,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10,'T' },


	{MON_BLUE_ONI,14,1412,name_infor(MON_BLUE_ONI),&img_mons_blue_oni,120,10,2,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,10,'O' },

	{MON_MUSHROOM,8,272,name_infor(MON_MUSHROOM),&img_mons_mushroom,30,6,0,
	{9,0,0},{ATT_S_POISON,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,0,12,'m' },

	{MON_KYOUKO,6,500,name_infor(MON_KYOUKO),&img_named_kyouko,30,1,11,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },


	{MON_FORTUNE_TELLER,3,154,name_infor(MON_FORTUNE_TELLER),&img_named_sigmund,30,0,11,
	{9,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,1,1,10,'&' },

	{MON_WOLF_TENGU,12,1312,name_infor(MON_WOLF_TENGU),&img_mons_default,49,12,2,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,2,13,'t' },

	{MON_MOMIZI,12,1923,name_infor(MON_MOMIZI),&img_named_momizi,142,12,2,
	{32,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,3,10,'&' },

	{MON_AYA,15,3421,name_infor(MON_AYA),&img_named_aya,118,1,14,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,8,'&' },

	{MON_TEST_KATPA,2,50,name_infor(MON_TEST_KATPA),&img_mons_katpa,20,2,5,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM | M_FLAG_CANT_NETURAL,0,1,10,'k' },

	//여기부터 임시 정보들
	{MON_WAKASAGI,7,300,name_infor(MON_WAKASAGI),&img_named_wakasagi,50,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SWIM | M_FLAG_CANT_NETURAL | M_FLAG_SPEAK | M_FLAG_CANT_GROUND,0,1,10,'&' },

	{MON_YAMAME,8,854,name_infor(MON_YAMAME),&img_named_yamame,95,3,11,
	{15,16,28},{ATT_NORMAL,ATT_NONE,ATT_SICK},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_POISON)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },
	
	{MON_NAZRIN,7,570,name_infor(MON_NAZRIN),&img_named_nazrin,45,0,10,
	{17,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,1,10,'&' },

	{MON_DAUZING,10,1,name_infor(MON_DAUZING),&img_mons_dauzing,80,8,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,8,'*' },
	
	{MON_YOSIKA,9,0,name_infor(MON_YOSIKA),&img_named_yosika,150,3,3,
	{22,30,30},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_CRUNCH),name_infor(LOC_SYSTEM_ATT_CRUNCH)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,10,'&' },
	
	{MON_SEKIBANKI,8,824,name_infor(MON_SEKIBANKI),&img_named_sekibanki,78,3,9,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,1,10,'&' },
	
	{MON_SEKIBANKI_BODY,8,824,name_infor(MON_SEKIBANKI_BODY),&img_named_sekibanki_body,78,10,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_CAN_SEE_INVI | M_FLAG_CANT_NETURAL,1,0,10,'&' },
	
	{MON_SEKIBANKI_HEAD,1,1,name_infor(MON_SEKIBANKI_HEAD),&img_named_sekibanki_head,30,0,15,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_BITE),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_CANT_NETURAL,0,1,10,'*' },
	
	{MON_NITORI,13,2188,name_infor(MON_NITORI),&img_named_nitori,105,8,12,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10,'&' },
	
	{MON_KEGERO,10,1297,name_infor(MON_KEGERO),&img_named_kagero,130,3,12,
	{36,25,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_BITE),name_infor(LOC_SYSTEM_ATT_CLAW),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },
	
	{MON_PARSI,9,925,name_infor(MON_PARSI),&img_named_parsi,130,8,15,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },
	
	{MON_BENBEN,6,520,name_infor(MON_BENBEN),&img_named_benben,67,3,3,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_NONE_STAIR,2,1,10,'&' },
	
	{MON_YATHASI,6,520,name_infor(MON_YATHASI),&img_named_yathasi,58,0,8,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_NONE_STAIR,2,1,10,'&' },
	
	{MON_ORIN,13,2310,name_infor(MON_ORIN),&img_named_orin,115,1,12,
	{29,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10,'&' },
	
	{MON_ORIN_CAT,13,2310,name_infor(MON_ORIN_CAT),&img_named_orin_cat,70,0,25,
	{21,21,0},{ATT_NORMAL,ATT_FIRE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_CLAW),name_infor(LOC_SYSTEM_ATT_CLAW),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,1,1,5,'c' },
	
	{MON_ZOMBIE_FAIRY,7,183,name_infor(MON_ZOMBIE_FAIRY),&img_mons_zombiefairy,35,0,12,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10,'z' },
	
	{MON_ICHIRIN,13,3240,name_infor(MON_ICHIRIN),&img_named_ichirin,128,9,2,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },
	
	{MON_UNZAN,13,1,name_infor(MON_UNZAN),&img_named_unzan,150,0,0,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_CANT_NETURAL,99,1,10,'U' },
	
	{MON_UNZAN_PUNCH,13,1,name_infor(MON_UNZAN_PUNCH),&img_named_unzan_punch[0],30,0,6,
	{35,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_SMASH),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY  | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL,99,1,15,'P' },
	
	{MON_PACHU,13,1923,name_infor(MON_PACHU),&img_named_pachu,70,1,5,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,99,1,10,'&' },
	
	{MON_MAGIC_BOOK,10,830,name_infor(MON_MAGIC_BOOK),&img_mons_magic_book[0],50,0,13,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_INANIMATE,99,1,8,':' },
	 
	{MON_HOBGOBRIN,6,142,name_infor(MON_HOBGOBRIN),&img_mons_hobgobrin,40,1,6,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h' },
	
	{MON_HOBGOBRIN_MAID,8,692,name_infor(MON_HOBGOBRIN_MAID),&img_mons_hobgobrin_maid,80,6,6,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10,'h' },

	{MON_HOBGOBRIN_LIBRARIAN,11,1120,name_infor(MON_HOBGOBRIN_LIBRARIAN),&img_mons_hobgobrin_librarian,70,1,10,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,1,10,'h' },
	
	{MON_HOBGOBRIN_TEMP,13,1510,name_infor(MON_HOBGOBRIN_TEMP),&img_mons_hobgobrin_temp,70,0,6,
	{11,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,1,10,'h' },
	
	{MON_MAID_FAIRY,8,171,name_infor(MON_MAID_FAIRY),&img_mons_maid_fairy,32,1,12,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10,'m' },
	
	{MON_CHUPARCABRA,12,1384,name_infor(MON_CHUPARCABRA),&img_mons_chuparcabra,122,3,14,
	{23,0,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,1,7,'C' },
	
	{MON_KOAKUMA,11,1615,name_infor(MON_KOAKUMA),&img_named_koakuma,68,1,8,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10,'&' },
	
	{MON_MEIRIN,8,850,name_infor(MON_MEIRIN),&img_named_meirin,105,8,6,
	{30,14,14},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_BODYCHECK),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_NORMAL)},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10,'&' },
	
	{MON_SAKUYA,13,3072,name_infor(MON_SAKUYA),&img_named_sakuya,130,1,20,
	{26,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,1,10,'&' },
	
	{MON_REMILIA,15,4521,name_infor(MON_REMILIA),&img_named_remilia,200,1,22,
	{34,24,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_DRAIN),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,9,'&' },
	
	{MON_EAGLE,9,921,name_infor(MON_EAGLE),&img_mons_eagle,80,1,10,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_ANIMAL | M_FLAG_CAN_SEE_INVI,0,1,10,'C'},
	
	{MON_TIGER,11,1180,name_infor(MON_TIGER),&img_mons_tiger,93,3,6,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_ANIMAL ,0,1,10,'C'},
	
	{MON_RAIJUU,10,950,name_infor(MON_RAIJUU),&img_mons_raijuu,60,1,12,
	{18,0,0},{ATT_M_POISON,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,8,'C'},
	
	{MON_DRAGON_BABY,15,1260,name_infor(MON_DRAGON_BABY),&img_mons_dragon_baby,90,10,6,
	{14,14,27},{ATT_NORMAL,ATT_NONE,ATT_FIRE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_BITE)},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_ANIMAL | M_FLAG_CAN_SEE_INVI,1,1,10,'D' },
	
	{MON_KASEN,16,5872,name_infor(MON_KASEN),&img_named_kasen,210,7,6,
	{38,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,1,10,'&' },
	
	{MON_YAMAWARO_NINJA,8,593,name_infor(MON_YAMAWARO_NINJA),&img_mons_yamawaro_ninja,62,5,7,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'Y' },
	
	{MON_YAMAWARO_WAWRRIOR,9,943,name_infor(MON_YAMAWARO_WAWRRIOR),&img_mons_yamawaro_warrior,75,5,6,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'Y' },
	
	{MON_YAMAWARO_FLAG,11,1110,name_infor(MON_YAMAWARO_FLAG),&img_mons_yamawaro_flag,60,7,5,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10,'Y' },
		
	{MON_ONBASIRA,1,1,name_infor(MON_ONBASIRA),&img_mons_onbasira,60,10,0,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,10,'!' },
	
	{MON_RED_UFO,12,1280,name_infor(MON_RED_UFO),&img_mons_red_ufo,76,5,10,
	{25,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_INANIMATE,1,1,9,'U' },
	
	{MON_GREEN_UFO,12,1280,name_infor(MON_GREEN_UFO),&img_mons_green_ufo,76,5,10,
	{25,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_INANIMATE,1,1,9,'U' },
		
	{MON_BLUE_UFO,12,1280,name_infor(MON_BLUE_UFO),&img_mons_blue_ufo,76,5,10,
	{25,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_INANIMATE,1,1,9,'U' },
		
	
	{MON_KOISHI,13,3880,name_infor(MON_KOISHI),&img_named_koishi,75,3,18,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_INVISIBLE | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,3,1,7,'&' },
	{MON_NUE,14,4140,name_infor(MON_NUE),&img_named_nue,140,10,6,
	{18,25,0},{ATT_SPEAR,ATT_ELEC,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,1,10,'&' },
	{MON_SANPEI_FIGHTER,12,1601,name_infor(MON_SANPEI_FIGHTER),&img_mons_sanpei_fighter,120,15,6,
	{26,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_DRILL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_INANIMATE,99,1,8,'8' },
	{MON_VAMPIER_BAT,9,824,name_infor(MON_VAMPIER_BAT),&img_mons_vamp_bat,60,0,20,
	{14,0,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_ANIMAL,0,1,5,'b' },
	{MON_DEAGAMA,12,800,name_infor(MON_DEAGAMA),&img_mons_dagama,90,10,2,
	{24,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_SWIM,3,1,10,'C' },
	{MON_RABBIT,3,5,name_infor(MON_RABBIT),&img_mons_rabit,20,0,15,
	{9,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_CANT_NETURAL,0,1,10,'R' },
	{MON_YOKAI_RABBIT,1,1,name_infor(MON_YOKAI_RABBIT),&img_mons_youkai_rabit,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_CANT_NETURAL,1,1,10,'R' },
	{MON_NAMAZ,16,1650,name_infor(MON_NAMAZ),&img_mons_namaz,90,12,2,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_SWIM,1,1,12,'N' },
	{MON_HELL_CROW,9,374,name_infor(MON_HELL_CROW),&img_mons_hell_crow,48,1,10,
	{20,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,0,7,'c' },
	{MON_RACCON,7,224,name_infor(MON_RACCON),&img_mons_raccoon,60,1,16,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_ANIMAL,0,1,10,'X' },
	{MON_LANTERN_YOUKAI,15,1333,name_infor(MON_LANTERN_YOUKAI),&img_mons_lantern_youkai,88,8,8,
	{25,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,1,10,'P' },
	{MON_YINYAN,30,8000,name_infor(MON_YINYAN),&img_mons_yinyan,300,0,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,2,9,'*' },
	{MON_YUUGENMAGAN,14,2432,name_infor(MON_YUUGENMAGAN),&img_mons_yugenmagan,100,12,10,
	{15,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,99,1,10,'1' },
	{MON_ELIS,9,535,name_infor(MON_ELIS),&img_mons_elise,70,0,12,
	{15,10,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,2,1,6,'2' },
	{MON_SARIEL,15,2762,name_infor(MON_SARIEL),&img_mons_sariel,130,10,20,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,3,1,10,'1' },
	{MON_SARA,9,435,name_infor(MON_SARA),&img_mons_sara,85,15,5,
	{22,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10,'2' },
	{MON_LUIZE,9,435,name_infor(MON_LUIZE),&img_mons_louise,75,1,12,
	{10,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,10,'2' },
	{MON_YUKI,14,2432,name_infor(MON_YUKI),&img_mons_yuki,130,8,15,
	{25,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10,'1' },
	{MON_MAI,14,2432,name_infor(MON_MAI),&img_mons_mai,130,8,15,
	{25,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10,'1' },
	{MON_YUMEKO,19,5672,name_infor(MON_YUMEKO),&img_mons_yumeko,350,3,18,
	{60,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE  | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,4,1,10,'&' },

	{MON_MAGICAL_STAR,4,1,name_infor(MON_MAGICAL_STAR),&img_mons_option,10,0,5,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,5,'*' },

	{MON_GOLEM,8,1,name_infor(MON_GOLEM),&img_mons_golem,80,10,0,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,10,'8' },
	{MON_EVIL_EYE,3,15,name_infor(MON_EVIL_EYE),&img_mons_evil_eye,20,0,8,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,0,1,10,'3' },
	{MON_LITTLE_IMP,3,15,name_infor(MON_LITTLE_IMP),&img_mons_little_imp,25,1,15,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10,'3' },
	
	{MON_ENSLAVE_GHOST,1,2,name_infor(MON_ENSLAVE_GHOST),&img_mons_ghost[0],10,0,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_CANT_NETURAL,0,0,12,'g' },

	{MON_SCHEMA_EYE,1,1,name_infor(MON_SCHEMA_EYE),&img_mons_schema_eye,10,0,12,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NONE_MOVE  | M_FLAG_CAN_SEE_INVI  | M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,10,'e' },
	
	{MON_FLAN,21,12999,name_infor(MON_FLAN),&img_named_flandre,230,10,15,
	{31,28,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_DRAIN),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,10,'&' },

	{MON_FLAN_BUNSIN,21,0,name_infor(MON_FLAN_BUNSIN),&img_named_flandre,80,5,10,
	{18,15,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_DRAIN),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY | M_FLAG_CANT_NETURAL,3,1,10,'&' },

	
	{MON_RABIT_BOMB,9,10,name_infor(MON_RABIT_BOMB),&img_mons_bomb_rabbit,12,1,20,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,9,'R' },
	
	{MON_RABIT_SPEAR,11,240,name_infor(MON_RABIT_SPEAR),&img_mons_spear_rabbit,35,5,15,
	{28,0,0},{ATT_SPEAR,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'R' },
	
	{MON_RABIT_SUPPORT,12,440,name_infor(MON_RABIT_SUPPORT),&img_mons_support_rabbit,25,3,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_CAN_SEE_INVI |  M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,2,10,'R' },

	{MON_RABIT_MAGIC,10,570,name_infor(MON_RABIT_MAGIC),&img_mons_magic_rabbit,30,2,20,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_ANIMAL |  M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10,'R' },

	
	{MON_TEWI,13,2150,name_infor(MON_TEWI),&img_named_tewi,70,3,22,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,8,'&' },

	{MON_CLOWNPIECE,15,3220,name_infor(MON_CLOWNPIECE),&img_named_clownpiece,120,3,18,
	{22,22,0},{ATT_FIRE,ATT_LUNATIC,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_TORCH),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,1,1,8,'&' },
	
	{ MON_DOREMI,14,3904,name_infor(MON_DOREMI),&img_named_doremi,120,8,10,
	{12,12,0},{ATT_SLEEP,ATT_NORMAL,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_DREAM),name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK, 3, 1, 12,'&' },

	{MON_FAIRY_HERO,12,977,name_infor(MON_FAIRY_HERO),&img_mons_fairy_green_hero,120,10,8,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10,'F' },
	
	{MON_FAIRY_SOCERER,10,651,name_infor(MON_FAIRY_SOCERER),&img_mons_fairy_green_socerer,49,5,12,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'F' },
	
	{MON_FAIRY_SUN_FLOWER,13,1180,name_infor(MON_FAIRY_SUN_FLOWER),&img_mons_fairy_green_himawari,90,8,12,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,1,2,10,'F' },
	
	{MON_MOON_RABIT_SUPPORT,9,675,name_infor(MON_MOON_RABIT_SUPPORT),&img_mons_moon_rabbit_supporter,49,5,8,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,0,2,10,'R' },
	
	{MON_MOON_RABIT_ATTACK,12,334,name_infor(MON_MOON_RABIT_ATTACK),&img_mons_moon_rabbit_attack,85,10,6,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,0,1,10,'R' },

	{MON_MOON_RABIT_ELITE,16,1678,name_infor(MON_MOON_RABIT_ELITE),&img_mons_moon_rabbit_elite,128,15,10,
	{39,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,1,1,10,'R' },
	
	{MON_MAC,12,1230,name_infor(MON_MAC),&img_mons_mac,60,5,10,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_ANIMAL,0,2,10,'D' },
	
	{MON_NIGHTMARE,15,1712,name_infor(MON_NIGHTMARE),&img_mons_nightmare,112,12,5,
	{33,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,1,1,10,'%' },
	
	{MON_LUNATIC,13,1374,name_infor(MON_LUNATIC),&img_mons_lunatic,90,12,5,
	{26,0,0},{ATT_LUNATIC,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,1,1,10,'%' },
	
	{MON_HAUNT,7,254,name_infor(MON_HAUNT),&img_mons_haunt[0],30,3,15,
	{14,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_SPEAK,0,1,8,'g' },

	{MON_FIRE_CAR,16,1782,name_infor(MON_FIRE_CAR),&img_mons_fire_car,150,15,2,
	{40,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,1,8,'8' },
	
	{MON_HELL_SPIDER,11,782,name_infor(MON_HELL_SPIDER),&img_mons_hell_spider,80,5,10,
	{25,0,0},{ATT_SICK,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_VENOM_TEETH),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_ANIMAL,0,0,10,'S' },
	
	{MON_BLOOD_HAUNT,12,835,name_infor(MON_BLOOD_HAUNT),&img_mons_blood_haunt,55,0,12,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'G' },
	
	{MON_HELL_HOUND,9,512,name_infor(MON_HELL_HOUND),&img_mons_hell_dog,68,4,15,
	{29,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_BITE),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_ANIMAL,0,1,10,'D' },
	
	{MON_DESIRE,9,297,name_infor(MON_DESIRE),&img_mons_desire_red,40,1,20,
	{18,0,0},{ ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_SPEAK,0,1,7,'%' },

	{MON_FLOWER_TANK,18,3220,name_infor(MON_FLOWER_TANK),&img_mons_flower_tank[1],90,10,10,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_INANIMATE,99,1,9,'8' },
	
	{MON_EVIL_EYE_TANK,28,5043,name_infor(MON_EVIL_EYE_TANK),&img_mons_evil_eye_tank,130,20,10,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_INANIMATE,99,2,9,'8' },
	
	{MON_SNOW_GIRL,14,1464,name_infor(MON_SNOW_GIRL),&img_mons_snow_girl,77,2,16,
	{27,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'G' },
	
	{MON_LETTY,14,1832,name_infor(MON_LETTY),&img_named_letty,150,11,6,
	{19,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10,'&' },
	
	{MON_YORIHIME,20,7682,name_infor(MON_YORIHIME),&img_named_yorihime,250,8,18,
	{52,52,0},{ ATT_FIRE,ATT_ELEC,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_FIRE_SWORD),name_infor(LOC_SYSTEM_ATT_ELEC_SWORD),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI | M_FLAG_RESIST_BLIZARD | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,5,3,8,'&' },

	{MON_TOYOHIME,20,7682,name_infor(MON_TOYOHIME),&img_named_toyohime,260,18,8,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI | M_FLAG_RESIST_BLIZARD | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,5,3,10,'&' },
	
	{MON_UTSUHO,24,13456,name_infor(MON_UTSUHO),&img_named_utsuho,450,30,2,
	{50,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,4,3,10,'&' },
	
	{MON_SUIKA,23,9760,name_infor(MON_SUIKA),&img_named_suika,350,28,5,
	{60,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,3,1,10,'&' },
	
	{MON_REIMU,20,0,name_infor(MON_REIMU),&img_named_reimu,190,5,40,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_UNIQUE | M_FLAG_SPEAK,99,4,8,'&' },
	
	{MON_ALICE,18,8467,name_infor(MON_ALICE),&img_named_alice,160,10,15,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,2,10,'&' },

	{MON_SEIRAN,8,573,name_infor(MON_SEIRAN),&img_named_seiran,64,2,11,
	{19,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,2,10,'&' },
	
	{MON_RINGO,13,1585,name_infor(MON_RINGO),&img_named_ringo,110,14,6,
	{22,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,2,10,'&' },
	
	{MON_UDONGE,15,1973,name_infor(MON_UDONGE),&img_named_udonge,150,4,16,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE,2,1,10,'&' },
	
	{MON_KAGUYA,18,3437,name_infor(MON_KAGUYA),&img_named_kaguya,202,20,1,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_PASSED_ALLY | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,3,1,12,'&' },
	
	{MON_MOKOU,16,2735,name_infor(MON_MOKOU),&img_mons_default,180,6,15,
	{50,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10,'&' },
	
	{MON_NESI,15,1604,name_infor(MON_NESI),&img_mons_nesi,120,9,9,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_NONE_STAIR | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE | M_FLAG_CAN_SEE_INVI | M_FLAG_SWIM | M_FLAG_CANT_GROUND,99,1,10,'8' },
	
	{MON_SANGHAI,15,1,name_infor(MON_SANGHAI),&img_mons_sanghai[0],80,5,22,
	{36,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,1,7,'d' },
	
	{MON_HOURAI,15,1,name_infor(MON_HOURAI),&img_mons_hourai[0],120,20,2,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,1,10,'d' },
	
	{MON_FAKE_SANGHAI,10,1,name_infor(MON_FAKE_SANGHAI),&img_mons_sanghai[1],60,5,17,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,1,7,'d' },
	
	{MON_FAKE_HOURAI,10,1,name_infor(MON_FAKE_HOURAI),&img_mons_hourai[1],90,15,2,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,1,10,'d' },
	
	{MON_TOKIKO,11,1205,name_infor(MON_TOKIKO),&img_mons_tokiko,112,1,15,
	{16,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'&' },

	
	{MON_TOZIKO,15,3905,name_infor(MON_TOZIKO),&img_mons_toziko,135,5,15,
	{29,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_ELEC),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'&' },

	{MON_FUTO,16,4605,name_infor(MON_FUTO),&img_mons_futo,145,1,20,
	{14,25,0},{ATT_NORMAL,ATT_NORMAL,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_DISH),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,8,'&' },

	{MON_MAMIZO,19,7205,name_infor(MON_MAMIZO),&img_mons_mamizo,210,15,2,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,3,1,10,'&' },

	{MON_SEIGA,17,6205,name_infor(MON_SEIGA),&img_mons_seiga,170,12,10,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_NONE_STAIR,1,1,12,'&' },

	{ MON_CLOSE_DOOR, 1, 0, name_infor(MON_CLOSE_DOOR), &img_mons_close_door, 1, 10, 0,
	{ 0, 0, 0 }, { ATT_NONE, ATT_NONE, ATT_NONE }, { name_infor(), name_infor(), name_infor() },
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE | M_FLAG_NO_STATE, 99, 0, 10 ,'&' },

	{ MON_MURASA,17, 6510,name_infor(MON_MURASA),&img_named_murasa,180,5,15,
	{ 22,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SWIM | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_KEINE,15,4212,name_infor(MON_KEINE),&img_named_keine,150,12,5,
	{ 14,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,3,3,10,'&' },

	{ MON_KEINE2,15,4212,name_infor(MON_KEINE2),&img_named_keine2,150,0,18,
	{ 30,30,55 },{ ATT_NORMAL,ATT_NORMAL,ATT_NORMAL },{ name_infor(LOC_SYSTEM_ATT_NORMAL), name_infor(LOC_SYSTEM_ATT_NORMAL), name_infor(LOC_SYSTEM_ATT_HEADBUTT) },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,1,0,7,'&' },

	{ MON_YOUMU,21,9465,name_infor(MON_YOUMU),&img_named_youmu,250,0,20,
	{ 38,46,0 },{ ATT_NORMAL,ATT_NORMAL,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_HAKUROUKEN),name_infor(LOC_SYSTEM_ATT_ROUKANKEN),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,5,'&' },

	{ MON_LYRICA,13,1624,name_infor(MON_LYRICA),&img_named_lyrica,72,1,15,
	{ 16,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_STAIR | M_FLAG_FLY | M_FLAG_SPEAK,3,1,10,'&' },

	//메를랑과 루나사는 디버프를 위한 HD 보정
	{ MON_MERLIN,16,1642,name_infor(MON_MERLIN),&img_named_merlin,75,5,5,
	{ 12,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_STAIR | M_FLAG_FLY | M_FLAG_SPEAK,3,1,10,'&' },

	{ MON_LUNASA,17,1890,name_infor(MON_LUNASA),&img_named_lunasa,85,2,10,
	{ 15,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_STAIR | M_FLAG_FLY | M_FLAG_SPEAK,3,1,10,'&' },

	{ MON_KOMACHI,21,9218,name_infor(MON_KOMACHI),&img_named_komachi,310,15,3,
	{ 42,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_SICKLE),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,0,13,'&' },

	{ MON_IKU,15,4162,name_infor(MON_IKU),&img_named_iku,115,10,20,
	{ 20,30,0 },{ ATT_NORMAL,ATT_ELEC,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(LOC_SYSTEM_ATT_ROBE),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_LARVA,6,1,name_infor(MON_LARVA),&img_named_larva,35,2,7,
	{ 7,0,0 },{ ATT_S_POISON,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'&' },

	{ MON_NEMUNO,10,1221,name_infor(MON_NEMUNO),&img_named_nemuno,105,15,2,
	{ 18,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_CLEAVER),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },

	{ MON_AUNN,6,350,name_infor(MON_AUNN),&img_named_aunn,38,15,2,
	{ 8,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SHIELD | M_FLAG_SPEAK,3,1,10,'&' },

	{ MON_NARUMI,10,1405,name_infor(MON_NARUMI),&img_named_narumi,70,30,0,
	{ 19,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,12,'&' },

	{ MON_MAI2,1,0,name_infor(MON_MAI2),&img_named_mai,10,1,12,
	{ 0, 0, 0 }, { ATT_NONE, ATT_NONE, ATT_NONE }, { name_infor(), name_infor(), name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_NO_ATK | M_FLAG_UNIQUE | M_FLAG_CANT_NETURAL | M_FLAG_CONFUSE | M_FLAG_FLY | M_FLAG_SPEAK, 2, 1, 10,'&' },

	{ MON_SATONO,1,0,name_infor(MON_SATONO),&img_named_satono,10,1,12,
	{ 0, 0, 0 }, { ATT_NONE, ATT_NONE, ATT_NONE }, { name_infor(), name_infor(), name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_NO_ATK | M_FLAG_UNIQUE | M_FLAG_CANT_NETURAL | M_FLAG_CONFUSE | M_FLAG_FLY | M_FLAG_SPEAK, 2, 1, 10,'&' },

	{ MON_KOKORO,17,1,name_infor(MON_KOKORO),&img_named_kokoro[0],190,9,12,
	{ 20,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_KOKORO1,17,1,name_infor(MON_KOKORO1),&img_named_kokoro[1],190,9,12,
	{ 30,0,0 },{ ATT_FIRE,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_FAN),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_KOKORO2,17,1,name_infor(MON_KOKORO2),&img_named_kokoro[2],190,9,12,
	{ 30,0,0 },{ ATT_COLD,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_FAN),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_KOKORO3,17,1,name_infor(MON_KOKORO3),&img_named_kokoro[3],190,9,12,
	{ 30,0,0 },{ ATT_ELEC,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_FAN),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_SUMIREKO,20,9429,name_infor(MON_SUMIREKO),&img_named_sumireko,200,1,15,
	{ 16,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SILENCE | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10 ,'&' },

	{ MON_ANCHOR,1,1,name_infor(MON_ANCHOR),&img_mons_anchor,100,15,0,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,10,'A' },

	{ MON_MASK_ANGRY,10,1,name_infor(MON_MASK_ANGRY),&img_mons_mask_angry,50,0,20,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE | M_FLAG_FLY,1,1,10,'*' },

	{ MON_MASK_SAD,10,1,name_infor(MON_MASK_SAD),&img_mons_mask_sad,50,0,20,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE | M_FLAG_FLY,1,1,10,'*' },

	{ MON_MASK_HAPPY,10,1,name_infor(MON_MASK_HAPPY),&img_mons_mask_happy,50,0,20,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE | M_FLAG_FLY,1,1,10,'*' },

	{ MON_TRASH,1,1,name_infor(MON_TRASH),&img_mons_trash[0],100,10,0,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,1,1,10,'*' },

	{ MON_OCCULT_LONG,1,1,name_infor(MON_OCCULT_LONG),&img_mons_occult_long,45,10,3,
	{ 15,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,3,1,10,'G' },

	{ MON_OCCULT_DISK,1,1,name_infor(MON_OCCULT_DISK),&img_mons_occult_disk,25,1,15,
	{ 5,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,2,1,10,'G' },

	{ MON_OCCULT_SMALL,1,1,name_infor(MON_OCCULT_SMALL),&img_mons_occult_small,15,0,10,
	{ 6,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,1,1,8,'g' },

	{ MON_KUNEKUNE,1,1,name_infor(MON_KUNEKUNE),&img_mons_occult_kunekune,1,0,0,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_SILENCE | M_FLAG_NONE_MOVE | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,1,1,10,'g' },

	{ MON_KANAME,1,1,name_infor(MON_KANAME),&img_mons_kaname,1,0,0,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_PASSED_ALLY | M_FLAG_NONE_MOVE | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,1,1,10,'*' },

	{ MON_SHEEP,10,675,name_infor(MON_SHEEP),&img_mons_sheep,55,1,10,
	{ 8,0,0 },{ ATT_SLEEP,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_ANIMAL | M_FLAG_SPEAK, 0, 1, 10 ,'Y' },

	{ MON_BEE,1,1,name_infor(MON_BEE),&img_mons_bee,1,0,0,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'b' },

	{ MON_BUSH,1,0,name_infor(MON_BUSH),&img_mons_bush,50,0,0,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
	 M_FLAG_NONE_STAIR | M_FLAG_NONE_MOVE | M_FLAG_NO_STATE | M_FLAG_INANIMATE | M_FLAG_UNHARM | M_FLAG_NO_ATK  | M_FLAG_CANT_NETURAL,99,1,10,'W' },

	 { MON_SION, 1, 0, name_infor(MON_SION), &img_mons_sion, 1, 8, 0,
	 { 0,0,0}, { ATT_NONE,ATT_NONE,ATT_NONE }, {name_infor(),name_infor(),name_infor() },
		M_FLAG_NONE_STAIR | M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_UNIQUE | M_FLAG_PASSED_ENEMY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_UNHARM , 99, 1, 10 ,'&' },

	{ MON_CURSE_DOLL, 8, 140, name_infor(MON_CURSE_DOLL), &img_mons_cursed_doll, 30, 1, 12,
	{ 4,0,0 }, { ATT_NORMAL,ATT_NONE,ATT_NONE }, { name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
		M_FLAG_OPEN_DOOR  | M_FLAG_INANIMATE, 1, 1, 10,'d' },

	{ MON_DANCING_WEAPON, 10, 870, name_infor(MON_DANCING_WEAPON), &img_mons_default, 50, 0, 14,
		{ 19,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
		M_FLAG_FLY | M_FLAG_INANIMATE, 1, 1, 9 ,'(' },

	{ MON_DANCING_ARMOUR, 10, 870, name_infor(MON_DANCING_ARMOUR), &img_mons_default, 80, 10, 2,
		{ 15,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
		M_FLAG_FLY | M_FLAG_PASSED_ALLY |  M_FLAG_INANIMATE, 5, 1, 10,']' },

	{ MON_ELEC_BALL, 1, 0, name_infor(MON_ELEC_BALL), &img_blast[2], 10, 0, 10,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
		M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_CONFUSE |
		M_FLAG_PASSED_ENEMY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE, 99, 0, 10,'*' },

	{ MON_HATATE, 10, 1221, name_infor(MON_HATATE), &img_named_hatate, 85, 2, 22,
		{ 7,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
		M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },

	{ MON_BOMB, 1, 0, name_infor(MON_BOMB), &img_item_evo_bomb, 10, 0, 10,
		{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
		M_FLAG_NONE_MOVE | M_FLAG_NONE_STAIR | M_FLAG_NO_ATK | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE, 99, 0, 10,'*' },
	
	{ MON_DOREKING, 30, 9999, name_infor(MON_DOREKING), &img_named_doreking, 500, 22, 10,
	{ 40,0,0 }, { ATT_NORMAL,ATT_NONE,ATT_NONE }, { name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	 M_FLAG_NONE_STAIR | M_FLAG_CANT_NETURAL | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_SILENCE | M_FLAG_INANIMATE, 99, 0, 10, 'D' },
	
	{ MON_CURIOSITY, 14, 1008, name_infor(MON_CURIOSITY), &img_mons_curiosity, 130, 20, 5,
	{ 25,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
		M_FLAG_CAN_SEE_INVI | M_FLAG_INANIMATE | M_FLAG_SILENCE, 99, 2, 10, '8' },

	{MON_KAGUYA_QUIZ_0, 12, 1, name_infor(MON_KAGUYA_QUIZ_0), &img_mon_kaguya_quiz[0], 10, 0, 5,
	{ 0,0,0 }, { ATT_NONE,ATT_NONE,ATT_NONE }, { name_infor(),name_infor(),name_infor() },
		M_FLAG_NO_ATK | M_FLAG_NONE_MOVE | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_SILENCE | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE, 99, 0, 10, '*' },

	{ MON_KAGUYA_QUIZ_1, 12, 1, name_infor(MON_KAGUYA_QUIZ_1), &img_mon_kaguya_quiz[1], 10, 0, 5,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
		M_FLAG_NO_ATK | M_FLAG_NONE_MOVE | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_SILENCE | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE, 99, 0, 10, '*' },

	{ MON_KAGUYA_QUIZ_2, 12, 1, name_infor(MON_KAGUYA_QUIZ_2), &img_mon_kaguya_quiz[2], 10, 0, 5,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
		M_FLAG_NO_ATK | M_FLAG_NONE_MOVE | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_SILENCE | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE, 99, 0, 10, '*' },

	{ MON_KAGUYA_QUIZ_3, 12, 1, name_infor(MON_KAGUYA_QUIZ_3), &img_mon_kaguya_quiz[3], 10, 0, 5,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
		M_FLAG_NO_ATK | M_FLAG_NONE_MOVE | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_SILENCE | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE, 99, 0, 10, '*' },

	{ MON_KAGUYA_QUIZ_4, 15, 1, name_infor(MON_KAGUYA_QUIZ_4), &img_mon_kaguya_quiz[4], 10, 0, 5,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
		M_FLAG_NO_ATK | M_FLAG_NONE_MOVE | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_SILENCE | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE, 99, 0, 10, '*' },

	{ MON_MISYAGUZI,15,1604,name_infor(MON_MISYAGUZI),&img_mons_misyaguzi,160,9,9,
	{ 49,0,0 },{ ATT_CURSE,ATT_NONE,ATT_NONE },{ name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor() },
	M_FLAG_CAN_SEE_INVI | M_FLAG_SWIM,99,1,10,'8' },
	
	{MON_EIKA,2,4,name_infor(MON_EIKA),&img_mons_eika,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{ MON_STONETOWER,1,0,name_infor(MON_STONETOWER),&img_mons_stonetower[0],50,0,0,
		{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
		 M_FLAG_NONE_STAIR | M_FLAG_NONE_MOVE | M_FLAG_NO_STATE | M_FLAG_INANIMATE | M_FLAG_UNHARM | M_FLAG_NO_ATK  | M_FLAG_CANT_NETURAL,99,1,10,'W' },

	{MON_URUMI,2,4,name_infor(MON_URUMI),&img_mons_urumi,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},
	
	{MON_KUTAKA,2,4,name_infor(MON_KUTAKA),&img_mons_kutaka,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{MON_YACHIE,2,4,name_infor(MON_YACHIE),&img_mons_yachie,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{MON_MAYUMI,2,4,name_infor(MON_MAYUMI),&img_mons_mayumi,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{MON_SAKI,2,4,name_infor(MON_SAKI),&img_mons_saki,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{MON_YUMA,2,4,name_infor(MON_YUMA),&img_mons_yuma,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{MON_ENOKO,2,4,name_infor(MON_ENOKO),&img_mons_enoko,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{MON_CHIYARI,2,4,name_infor(MON_CHIYARI),&img_mons_chiyari,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{MON_SONBITEN,2,4,name_infor(MON_SONBITEN),&img_mons_sonbiten,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{MON_HISAMI,2,4,name_infor(MON_HISAMI),&img_mons_hisami,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},

	{MON_TSUKASA,2,4,name_infor(MON_TSUKASA),&img_mons_tsukasa,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor(LOC_SYSTEM_ATT_NORMAL),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,15,'y'},
		
};
