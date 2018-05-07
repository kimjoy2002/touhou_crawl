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
	{MON_REIMUYUKKURI,2,4,name_infor("윳쿠리레이무",false),&img_mons_reimu_yukkuri,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15,'y'},

	{MON_REIMUYUKKURI,2,70,name_infor("윳쿠리레이무",false),&img_mons_reimu_yukkuri,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,0,0,15,'y'},

	{MON_RAT,1,1,name_infor("쥐",false),&img_mons_rat,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,0,10,'r'},

	{MON_FAIRY_GREEN,1,2,name_infor("돌격 요정",true),&img_mons_fairy_green,13,0,8,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f'},

	{MON_FAIRY_BLUE,2,3,name_infor("탄막 요정",true),&img_mons_fairy_blue,8,0,12,
	{1,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f'},

	{MON_FAIRY_RED,3,5,name_infor("대장 요정",true),&img_mons_fairy_red,21,2,6,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f'},

	{MON_MOOK,1,2,name_infor("모옥",true),&img_mons_mook,5,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10,'m'},

	{MON_MOOK,1,18,name_infor("모옥",true),&img_mons_mook,5,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_CANT_NETURAL,0,0,10,'m' },

	{MON_CROW,2,4,name_infor("까마귀",false),&img_mons_crow,17,0,8,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,7,'c' },

	{MON_CRANE,5,116,name_infor("두루미",false),&img_mons_crane,30,3,10,
	{8,8,20},{ATT_NORMAL,ATT_NORMAL,ATT_NORMAL},{name_infor("공격",true),name_infor("공격",true),name_infor("쪼기",false)},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10,'C' },

	{MON_SPIDER,3,11,name_infor("거미",false),&img_mons_spider,18,1,10,
	{2,2,3},{ATT_NORMAL,ATT_NORMAL,ATT_S_POISON},{name_infor("공격",true),name_infor("공격",true),name_infor("독니",false)},
	M_FLAG_ANIMAL,0,1,10,'s'},

	{MON_SNAKE,4,21,name_infor("뱀",true),&img_mons_snake,22,1,10,
	{4,3,0},{ATT_S_POISON,ATT_NORMAL,ATT_NONE},{name_infor("공격",true),name_infor("공격",true),name_infor()},
	M_FLAG_ANIMAL,0,1,7,'s'},

	{MON_KATPA,2,7,name_infor("캇파",false),&img_mons_new_kappa,20,2,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM,0,1,10,'k'},

	{MON_KATPA_GUN,5,65,name_infor("캇파 사격병",true),&img_mons_katpa_gun,40,1,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM | M_FLAG_CANT_NETURAL,0,2,10,'k'},

	{MON_FAIRY_GREEN_WARRIOR,5,128,name_infor("요정 전사",false),&img_mons_fairy_green_warroir,35,8,6,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'f'},

	{MON_FAIRY_BLUE_MAGICIAN,7,150,name_infor("요정 법사",false),&img_mons_fairy_blue_magician,25,2,16,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f' },

	{MON_FAIRY_RED_COMMANDER,8,214,name_infor("요정 지휘관",true),&img_mons_fairy_red_commander,33,0,6,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'f' },

	{MON_RUMIA,6,240,name_infor("루미아",false),&img_named_rumia,40,1,10,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'&' },

	{MON_MISTIA,8,535,name_infor("미스티아",false),&img_named_mistia,55,1,12,
	{11,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,8,'&' },

	{MON_WRIGGLE,7,350,name_infor("리글",true),&img_named_wriggle,50,3,10,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'&' },

	{MON_CIRNO,9,999,name_infor("치르노",false),&img_named_cirno,99,1,9,
	{15,25,0},{ATT_NORMAL,ATT_COLD,ATT_NONE},{name_infor("공격",true),name_infor("냉기",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10,'&' },

	{MON_MEDICINE,9,1066,name_infor("메디슨",true),&img_named_medicine,70,2,10,
	{8,12,0},{ATT_S_POISON,ATT_M_POISON,ATT_NONE},{name_infor("독기",false),name_infor("독기",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10,'&' },

	{MON_DIEFAIRY,6,570,name_infor("대요정",true),&img_named_diefairy,50,0,15,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'&' },

	{MON_HUMAM_WOMAN,1,0,name_infor("인간여자",false),&img_mons_human_woman,10,1,10,
	{1,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,0,1,10,'h'},

	{MON_HUMAM_MAN,2,8,name_infor("인간남자",false),&img_mons_human_man,20,1,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h'},

	{MON_HUMAM_YINYANG,4,66,name_infor("음양사",false),&img_mons_human_yinyang,30,1,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h'},

	{MON_HUMAM_PRIEST,5,92,name_infor("법사",false),&img_mons_human_priest,23,1,10,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h'},

	{MON_HUMAM_SAMURI,8,210,name_infor("사무라이",false),&img_mons_human_samuri,50,6,8,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h'},

	{MON_FIREFLY,2,5,name_infor("반딧불이",false),&img_mons_firefly,18,1,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10,'s'},

	{MON_BUTTERFLY,1,0,name_infor("나비",false),&img_mons_butterfly,5,1,20,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_UNHARM | M_FLAG_NO_ATK | M_FLAG_CONFUSE | M_FLAG_ANIMAL | M_FLAG_CANT_NETURAL,0,1,5,'b'},

	{MON_GHOST,1,2,name_infor("유령",true),&img_mons_ghost[0],10,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_CANT_NETURAL,0,0,12,'g'},

	{MON_BAKEKASA,4,21,name_infor("우산요괴",false),&img_mons_bakekasa,20,1,12,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	0,1,1,10,'('},

	{MON_GREEN_MOOK,2,6,name_infor("초록모옥",true),&img_mons_green_mook,18,0,10,
	{4,4,8},{ATT_NORMAL,ATT_NORMAL,ATT_S_POISON},{name_infor("공격",true),name_infor("공격",true),name_infor("공격",true)},
	M_FLAG_FLY,0,0,10,'m'},

	{MON_ORANGE_MOOK,3,11,name_infor("주황모옥",true),&img_mons_orange_mook,22,0,14,
	{9,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10,'m' },

	{MON_GRAY_MOOK,4,23,name_infor("회색모옥",true),&img_mons_gray_mook,18,1,10,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10,'m' },

	{MON_FROG,7,224,name_infor("개구리",false),&img_mons_frog,60,1,14,
	{16,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SWIM | M_FLAG_ANIMAL,0,0,9,'f' },
	
	{MON_BLACK_CAT,8,237,name_infor("검은고양이",false),&img_mons_black_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("할퀴기",false),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7,'c'},
	
	{MON_ORANGE_CAT,8,237,name_infor("주황고양이",false),&img_mons_orange_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("할퀴기",false),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7,'c' },

	{MON_WHITE_CAT,8,237,name_infor("하얀고양이",false),&img_mons_white_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("할퀴기",false),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7,'c' },

	{MON_CROW_TENGU,10,532,name_infor("까마귀텐구",false),&img_mons_crow_tengu,70,3,12,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10,'t' },

	{MON_ONI,14,1412,name_infor("오니",false),&img_mons_oni,120,10,2,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,10,'O' },

	{MON_KISUME,5,220,name_infor("키스메",false),&img_named_kisume,30,1,10,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10,'&' },

	{MON_CHEN,11,1325,name_infor("첸",true),&img_named_chen,85,0,15,
	{15,15,20},{ATT_NORMAL,ATT_NORMAL,ATT_NORMAL},{name_infor("할퀴기",false),name_infor("할퀴기",false),name_infor("할퀴기",false)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,8,'&' },

	{MON_KOGASA,7,550,name_infor("코가사",false),&img_named_kogasa,50,1,14,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },

	{MON_SUNNY,4,129,name_infor("써니",false),&img_named_sunny,35,1,10,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'&' },

	{MON_LUNAR,4,129,name_infor("루나",false),&img_named_lunar,30,1,10,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10,'&' },

	{MON_STAR,4,129,name_infor("스타",false),&img_named_star,25,1,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,10,10,'&' },

	{MON_MARISAYUKKURI,8,270,name_infor("윳쿠리마리사",false),&img_mons_marisa_yukkuri,70,2,5,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15,'y'},

	{MON_AYAYUKKURI,12,610,name_infor("키메이마루",false),&img_mons_aya_yukkuri,65,0,16,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,1,1,4,'Y'},

	{MON_REMILIAYUKKURI,14,1040,name_infor("윳쿠리레미랴",false),&img_mons_remila_yukkuri,60,5,12,
	{18,30,0},{ATT_VAMP,ATT_VAMP,ATT_NONE},{name_infor("물기",false),name_infor("물기",false),name_infor()},
	M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,3,1,8,'Y' }, //나중에 흡혈 공격으로 바꿈

	{MON_ALICEYUKKURI,11,660,name_infor("윳쿠리앨리스",false),&img_mons_alice_yukkuri,100,7,5,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,2,0,15,'Y' },

	{MON_YOUMUYUKKURI,15,840,name_infor("윳쿠리요우무",false),&img_mons_youmu_yukkuri,90,10,10,
	{36,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,0,9,'Y' }, //나중에 천천히 추가


	{MON_YAMABIKO,9,562,name_infor("야마비코",false),&img_mons_yamabiko,75,2,10,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR,0,0,10,'d' },

	{MON_KATPA_SPEAR,9,730,name_infor("캇파 창병",true),&img_mons_new_kappa_spear,70,5,10,
	{24,0,0},{ATT_SPEAR,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR | M_FLAG_SWIM,0,0,10,'K' },

	{MON_KATPA_WATER_WIZARD,10,860,name_infor("캇파 수술사",false),&img_mons_new_kappa_wizard,45,4,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR | M_FLAG_SWIM | M_FLAG_CAN_SEE_INVI,2,1,10,'K' },

	{MON_YAMABUSH_TENGU,11,1062,name_infor("야마부시텐구",false),&img_mons_yamabush_tengu,60,3,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI,1,1,10,'T' },


	{MON_HANATACA_TENGU,12,1183,name_infor("하나타카텐구",false),&img_mons_hanataca_tengu,78,5,13,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10,'T' },


	{MON_BLUE_ONI,14,1412,name_infor("아오오니",false),&img_mons_blue_oni,120,10,2,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,10,'O' },

	{MON_MUSHROOM,8,272,name_infor("버섯요괴",false),&img_mons_mushroom,30,6,0,
	{9,0,0},{ATT_S_POISON,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,0,12,'m' },

	{MON_KYOUKO,6,500,name_infor("쿄코",false),&img_named_kyouko,30,1,12,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },


	{MON_FORTUNE_TELLER,3,154,name_infor("점쟁이",false),&img_named_sigmund,30,0,11,
	{9,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,1,1,10,'&' },

	{MON_WOLF_TENGU,12,1312,name_infor("백랑 텐구",false),&img_mons_default,49,12,2,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,2,13,'t' },

	{MON_MOMIZI,12,1923,name_infor("모미지",false),&img_named_momizi,132,12,2,
	{32,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,3,10,'&' },

	{MON_AYA,15,3421,name_infor("아야",false),&img_named_aya,112,1,14,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,8,'&' },

	{MON_TEST_KATPA,2,50,name_infor("캇파",false),&img_mons_katpa,20,2,5,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM | M_FLAG_CANT_NETURAL,0,1,10,'k' },

	//여기부터 임시 정보들
	{MON_WAKASAGI,6,300,name_infor("와카사기히메",false),&img_named_wakasagi,40,0,13,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SWIM | M_FLAG_CANT_NETURAL | M_FLAG_SPEAK | M_FLAG_CANT_GROUND,0,1,10,'&' },

	{MON_YAMAME,8,854,name_infor("야마메",false),&img_named_yamame,90,3,6,
	{15,16,24},{ATT_NORMAL,ATT_NONE,ATT_SICK},{name_infor("공격",true),name_infor("공격",true),name_infor("독기",false)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },
	
	{MON_NAZRIN,7,570,name_infor("나즈린",true),&img_named_nazrin,45,0,8,
	{14,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,1,10,'&' },

	{MON_DAUZING,10,1,name_infor("펜듈럼",true),&img_mons_dauzing,80,8,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,8,'*' },
	
	{MON_YOSIKA,9,0,name_infor("요시카",false),&img_named_yosika,150,1,3,
	{22,30,30},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor("깨물기",false),name_infor("깨물기",false)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,10,'&' },
	
	{MON_SEKIBANKI,8,824,name_infor("세키반키",false),&img_named_sekibanki,70,3,9,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,1,10,'&' },
	
	{MON_SEKIBANKI_BODY,8,824,name_infor("세키반키",false),&img_named_sekibanki_body,70,10,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_CAN_SEE_INVI | M_FLAG_CANT_NETURAL,1,0,10,'&' },
	
	{MON_SEKIBANKI_HEAD,1,1,name_infor("세키반키",false),&img_named_sekibanki_head,30,0,15,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("물기",false),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_CANT_NETURAL,0,1,10,'*' },
	
	{MON_NITORI,13,2188,name_infor("니토리",false),&img_named_nitori,100,8,12,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10,'&' },
	
	{MON_KEGERO,10,1297,name_infor("카게로",false),&img_named_kagero,120,3,12,
	{30,25,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("물기",false),name_infor("할퀴기",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },
	
	{MON_PARSI,9,925,name_infor("파르시",false),&img_named_parsi,100,8,15,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },
	
	{MON_BENBEN,6,520,name_infor("벤벤",true),&img_named_benben,60,3,3,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_NONE_STAIR,2,1,10,'&' },
	
	{MON_YATHASI,6,520,name_infor("야츠하시",false),&img_named_yathasi,50,0,8,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_NONE_STAIR,2,1,10,'&' },
	
	{MON_ORIN,13,2310,name_infor("오린",true),&img_named_orin,95,1,12,
	{29,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10,'&' },
	
	{MON_ORIN_CAT,13,2310,name_infor("오린",true),&img_named_orin_cat,70,0,18,
	{21,21,0},{ATT_NORMAL,ATT_FIRE,ATT_NONE},{name_infor("할퀴기",false),name_infor("할퀴기",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,1,1,5,'c' },
	
	{MON_ZOMBIE_FAIRY,7,183,name_infor("좀비페어리",false),&img_mons_zombiefairy,35,0,12,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10,'z' },
	
	{MON_ICHIRIN,13,3240,name_infor("이치린",true),&img_named_ichirin,98,8,2,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },
	
	{MON_UNZAN,13,1,name_infor("운잔",true),&img_named_unzan,150,0,0,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_CANT_NETURAL,99,1,10,'U' },
	
	{MON_UNZAN_PUNCH,13,1,name_infor("운잔의 주먹",true),&img_named_unzan_punch[0],30,0,6,
	{35,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("스매쉬",false),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY  | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL,99,1,15,'P' },
	
	{MON_PACHU,12,1923,name_infor("파츄리",false),&img_named_pachu,70,1,5,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,99,1,10,'&' },
	
	{MON_MAGIC_BOOK,10,830,name_infor("마법서",false),&img_mons_magic_book[0],50,0,13,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_NO_ATK | M_FLAG_INANIMATE,99,1,8,':' },
	 
	{MON_HOBGOBRIN,6,142,name_infor("홉고블린",true),&img_mons_hobgobrin,40,1,6,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'h' },
	
	{MON_HOBGOBRIN_MAID,8,692,name_infor("홉고블린 메이드",false),&img_mons_hobgobrin_maid,80,6,6,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10,'h' },

	{MON_HOBGOBRIN_LIBRARIAN,11,1120,name_infor("홉고블린 사서",false),&img_mons_hobgobrin_librarian,70,1,10,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,1,10,'h' },
	
	{MON_HOBGOBRIN_TEMP,13,1510,name_infor("홉고블린 악마술사",false),&img_mons_hobgobrin_temp,70,0,6,
	{11,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,1,10,'h' },
	
	{MON_MAID_FAIRY,8,171,name_infor("요정 메이드",false),&img_mons_maid_fairy,32,1,12,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10,'m' },
	
	{MON_CHUPARCABRA,12,1384,name_infor("추파카브라",false),&img_mons_chuparcabra,122,3,14,
	{23,0,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,1,7,'C' },
	
	{MON_KOAKUMA,11,1615,name_infor("소악마",false),&img_named_koakuma,60,1,6,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10,'&' },
	
	{MON_MEIRIN,8,850,name_infor("홍메이린",true),&img_named_meirin,90,8,6,
	{30,14,14},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("철산고",false),name_infor("공격",true),name_infor("공격",true)},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10,'&' },
	
	{MON_SAKUYA,13,3072,name_infor("사쿠야",false),&img_named_sakuya,100,1,18,
	{26,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10,'&' },
	
	{MON_REMILIA,15,4521,name_infor("레밀리아",false),&img_named_remilia,140,1,20,
	{30,24,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("흡혈",true),name_infor("공격",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,9,'&' },
	
	{MON_EAGLE,9,921,name_infor("거대 매",false),&img_mons_eagle,80,1,10,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_ANIMAL | M_FLAG_CAN_SEE_INVI,0,1,10,'C'},
	
	{MON_TIGER,11,1180,name_infor("호랑이",false),&img_mons_tiger,93,3,6,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_ANIMAL ,0,1,10,'C'},
	
	{MON_RAIJUU,10,950,name_infor("뇌수",false),&img_mons_raijuu,60,1,12,
	{18,0,0},{ATT_M_POISON,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,8,'C'},
	
	{MON_DRAGON_BABY,15,1260,name_infor("용의 새끼",false),&img_mons_dragon_baby,90,10,6,
	{14,14,27},{ATT_NORMAL,ATT_NONE,ATT_FIRE},{name_infor("공격",true),name_infor("공격",true),name_infor("물기",false)},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_ANIMAL | M_FLAG_CAN_SEE_INVI,1,1,10,'D' },
	
	{MON_KASEN,16,5872,name_infor("카센",true),&img_named_kasen,150,5,6,
	{38,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10,'&' },
	
	{MON_YAMAWARO_NINJA,8,593,name_infor("야마와로 투척병",true),&img_mons_yamawaro_ninja,62,5,7,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'Y' },
	
	{MON_YAMAWARO_WAWRRIOR,9,943,name_infor("야마와로 돌격병",true),&img_mons_yamawaro_warrior,75,5,6,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'Y' },
	
	{MON_YAMAWARO_FLAG,11,1110,name_infor("야마와로 깃발병",true),&img_mons_yamawaro_flag,60,7,5,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10,'Y' },
		
	{MON_ONBASIRA,1,1,name_infor("온바시라",true),&img_mons_onbasira,60,10,0,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,10,'!' },
	
	{MON_RED_UFO,12,1280,name_infor("레드 벤토라",false),&img_mons_red_ufo,76,5,10,
	{25,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_INANIMATE,1,1,9,'U' },
	
	{MON_GREEN_UFO,12,1280,name_infor("그린 벤토라",false),&img_mons_green_ufo,76,5,10,
	{25,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_INANIMATE,1,1,9,'U' },
		
	{MON_BLUE_UFO,12,1280,name_infor("블루 벤토라",false),&img_mons_blue_ufo,76,5,10,
	{25,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_INANIMATE,1,1,9,'U' },
		
	
	{MON_KOISHI,13,3880,name_infor("코이시",false),&img_named_koishi,70,3,18,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_INVISIBLE | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,3,1,7,'&' },
	{MON_NUE,14,4140,name_infor("누에",false),&img_named_nue,140,10,6,
	{18,25,0},{ATT_SPEAR,ATT_ELEC,ATT_NONE},{name_infor("공격",true),name_infor("공격",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10,'&' },
	{MON_SANPEI_FIGHTER,12,1601,name_infor("산페이파이터",false),&img_mons_sanpei_fighter,120,15,6,
	{26,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("드릴",false),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_INANIMATE,99,1,8,'8' },
	{MON_VAMPIER_BAT,9,824,name_infor("흡혈 박쥐",false),&img_mons_vamp_bat,60,0,20,
	{14,0,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_ANIMAL,0,1,5,'b' },
	{MON_DEAGAMA,12,800,name_infor("큰두꺼비",false),&img_mons_dagama,90,10,2,
	{24,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_SWIM,3,1,10,'C' },
	{MON_RABBIT,3,5,name_infor("토끼",false),&img_mons_rabit,20,0,15,
	{9,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_CANT_NETURAL,0,1,10,'R' },
	{MON_YOKAI_RABBIT,1,1,name_infor("요괴 토끼",false),&img_mons_youkai_rabit,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CANT_NETURAL,1,1,10,'R' },
	{MON_NAMAZ,16,1650,name_infor("나마즈",false),&img_mons_namaz,90,12,2,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_SWIM,1,1,12,'N' },
	{MON_HELL_CROW,9,374,name_infor("지옥까마귀",false),&img_mons_hell_crow,48,1,10,
	{20,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,0,7,'c' },
	{MON_RACCON,7,224,name_infor("둔갑너구리",false),&img_mons_raccoon,60,1,16,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_ANIMAL,0,1,10,'X' },
	{MON_LANTERN_YOUKAI,15,1333,name_infor("제등요괴",false),&img_mons_lantern_youkai,88,8,8,
	{25,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,1,10,'P' },
	{MON_YINYAN,30,8000,name_infor("음양옥",true),&img_mons_yinyan,300,0,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,2,9,'*' },
	{MON_YUUGENMAGAN,14,2432,name_infor("유겐마간",true),&img_mons_yugenmagan,100,12,10,
	{15,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,99,1,10,'1' },
	{MON_ELIS,9,535,name_infor("엘리스",false),&img_mons_elise,70,0,12,
	{15,10,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,2,1,6,'2' },
	{MON_SARIEL,15,2762,name_infor("사리엘",true),&img_mons_sariel,130,10,20,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,3,1,10,'1' },
	{MON_SARA,9,435,name_infor("사라",false),&img_mons_sara,85,15,5,
	{22,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10,'2' },
	{MON_LUIZE,9,435,name_infor("루이즈",false),&img_mons_louise,75,1,12,
	{10,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,10,'2' },
	{MON_YUKI,14,2432,name_infor("유키",false),&img_mons_yuki,130,8,15,
	{25,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10,'1' },
	{MON_MAI,14,2432,name_infor("마이",false),&img_mons_mai,130,8,15,
	{25,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10,'1' },
	{MON_YUMEKO,19,5672,name_infor("유메코",false),&img_mons_yumeko,250,3,16,
	{60,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_UNIQUE  | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,4,1,10,'&' },

	{MON_MAGICAL_STAR,4,1,name_infor("옵션",true),&img_mons_option,10,0,5,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,5,'*' },

	{MON_GOLEM,8,1,name_infor("골렘",true),&img_mons_golem,80,10,0,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,10,'8' },
	{MON_EVIL_EYE,3,15,name_infor("이블아이",false),&img_mons_evil_eye,20,0,8,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,0,1,10,'3' },
	{MON_LITTLE_IMP,3,15,name_infor("마족 자코",false),&img_mons_little_imp,25,1,15,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10,'3' },
	
	{MON_ENSLAVE_GHOST,1,2,name_infor("유령",true),&img_mons_ghost[0],10,0,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_CANT_NETURAL,0,0,12,'g' },

	{MON_SCHEMA_EYE,1,1,name_infor("변용을 보는 눈",true),&img_mons_schema_eye,10,0,12,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NONE_MOVE  | M_FLAG_CAN_SEE_INVI  | M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,10,'e' },
	
	{MON_FLAN,21,12999,name_infor("플랑드르",false),&img_named_flandre,230,10,15,
	{31,28,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("흡혈",true),name_infor("공격",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,10,'&' },

	{MON_FLAN_BUNSIN,21,0,name_infor("플랑드르의 분신",false),&img_named_flandre,80,5,10,
	{18,15,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("흡혈",true),name_infor("공격",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY | M_FLAG_CANT_NETURAL,3,1,10,'&' },

	
	{MON_RABIT_BOMB,9,10,name_infor("토끼 자폭병",true),&img_mons_bomb_rabbit,12,1,20,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,9,'R' },
	
	{MON_RABIT_SPEAR,11,240,name_infor("토끼 죽창병",true),&img_mons_spear_rabbit,35,5,15,
	{28,0,0},{ATT_SPEAR,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10,'R' },
	
	{MON_RABIT_SUPPORT,12,440,name_infor("토끼 지원병",true),&img_mons_support_rabbit,25,3,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_CAN_SEE_INVI |  M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,2,10,'R' },

	{MON_RABIT_MAGIC,10,570,name_infor("토끼 마법사",false),&img_mons_magic_rabbit,30,2,20,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL |  M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10,'R' },

	
	{MON_TEWI,13,2150,name_infor("테위",false),&img_named_tewi,60,3,22,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,8,'&' },

	{MON_CLOWNPIECE,15,3220,name_infor("클라운피스",false),&img_named_clownpiece,120,3,18,
	{22,22,0},{ATT_FIRE,ATT_LUNATIC,ATT_NONE},{name_infor("횃불",true),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,1,1,8,'&' },
	
	{ MON_DOREMI,14,3904,name_infor("도레미",false),&img_named_doremi,120,8,10,
	{12,12,0},{ATT_SLEEP,ATT_NORMAL,ATT_NONE},{name_infor("몽혼",true),name_infor("공격",true),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK, 3, 1, 12,'&' },

	{MON_FAIRY_HERO,12,977,name_infor("요정 영웅",true),&img_mons_fairy_green_hero,120,10,8,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10,'F' },
	
	{MON_FAIRY_SOCERER,10,651,name_infor("요정 정령술사",false),&img_mons_fairy_green_socerer,49,5,12,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'F' },
	
	{MON_FAIRY_SUN_FLOWER,13,1180,name_infor("해바라기 요정",true),&img_mons_fairy_green_himawari,90,8,12,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,1,2,10,'F' },
	
	{MON_MOON_RABIT_SUPPORT,9,675,name_infor("달토끼 지원병",true),&img_mons_moon_rabbit_supporter,49,5,8,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,0,2,10,'R' },
	
	{MON_MOON_RABIT_ATTACK,12,334,name_infor("달토끼 척후병",true),&img_mons_moon_rabbit_attack,85,10,6,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,0,1,10,'R' },

	{MON_MOON_RABIT_ELITE,16,1678,name_infor("달토끼 정예병",true),&img_mons_moon_rabbit_elite,128,15,10,
	{39,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,1,1,10,'R' },
	
	{MON_MAC,12,1230,name_infor("맥",true),&img_mons_mac,60,5,10,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_ANIMAL,0,2,10,'D' },
	
	{MON_NIGHTMARE,15,1712,name_infor("악몽의 조각",true),&img_mons_nightmare,70,12,5,
	{31,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'%' },
	
	{MON_LUNATIC,13,1374,name_infor("광기의 조각",true),&img_mons_lunatic,90,12,5,
	{26,0,0},{ATT_LUNATIC,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'%' },
	
	{MON_HAUNT,7,254,name_infor("원령",true),&img_mons_haunt[0],30,3,15,
	{14,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_SPEAK,0,1,8,'g' },

	{MON_FIRE_CAR,16,1782,name_infor("화차",false),&img_mons_fire_car,150,15,2,
	{40,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,1,8,'8' },
	
	{MON_HELL_SPIDER,11,782,name_infor("츠치구모",false),&img_mons_hell_spider,80,5,10,
	{25,0,0},{ATT_SICK,ATT_NONE,ATT_NONE},{name_infor("독니",false),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_ANIMAL,0,0,10,'S' },
	
	{MON_BLOOD_HAUNT,12,835,name_infor("핏빛 원령",true),&img_mons_blood_haunt,55,0,12,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'G' },
	
	{MON_HELL_HOUND,9,254,name_infor("지옥개",false),&img_mons_hell_dog,68,4,15,
	{29,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("물기",false),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_ANIMAL,0,1,10,'D' },
	
	{MON_DESIRE,1,1,name_infor("욕망의 덩어리",false),&img_mons_default,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_CANT_NETURAL,0,1,10,'%' },

	{MON_FLOWER_TANK,18,3220,name_infor("플라워 전차",false),&img_mons_flower_tank[1],90,10,10,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_INANIMATE,99,1,9,'8' },
	
	{MON_EVIL_EYE_TANK,25,5043,name_infor("이블 아이 전차",false),&img_mons_evil_eye_tank,150,20,10,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_INANIMATE,99,2,9,'8' },
	
	{MON_SNOW_GIRL,14,1464,name_infor("설녀",false),&img_mons_snow_girl,77,2,16,
	{27,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'G' },
	
	{MON_LETTY,12,1832,name_infor("레티",false),&img_named_letty,120,9,6,
	{19,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10,'&' },
	
	{MON_YORIHIME,20,7682,name_infor("요리히메",false),&img_named_yorihime,250,8,18,
	{45,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,5,3,8,'&' },

	{MON_TOYOHIME,20,7682,name_infor("토요히메",false),&img_named_toyohime,260,18,8,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,5,3,10,'&' },
	
	{MON_UTSUHO,23,13456,name_infor("우츠호",false),&img_named_utsuho,450,30,2,
	{50,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,4,3,10,'&' },
	
	{MON_SUIKA,22,9760,name_infor("스이카",false),&img_named_suika,350,28,5,
	{60,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,3,1,10,'&' },
	
	{MON_REIMU,27,0,name_infor("레이무",false),&img_named_reimu,999,5,50,
	{50,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,99,4,8,'&' },
	
	{MON_ALICE,18,8467,name_infor("앨리스",false),&img_named_alice,130,10,15,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,2,10,'&' },

	{MON_SEIRAN,8,573,name_infor("세이란",true),&img_named_seiran,64,2,11,
	{19,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,2,10,'&' },
	
	{MON_RINGO,13,1585,name_infor("링고",false),&img_named_ringo,90,14,6,
	{22,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,2,10,'&' },
	
	{MON_UDONGE,15,1973,name_infor("레이센",true),&img_named_udonge,110,4,16,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE,2,1,10,'&' },
	
	{MON_KAGUYA,18,3437,name_infor("카구야",false),&img_named_kaguya,202,20,1,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SHIELD | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,3,1,12,'&' },
	
	{MON_MOKOU,16,2735,name_infor("모코우",false),&img_mons_default,180,6,15,
	{50,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10,'&' },
	
	{MON_NESI,15,1604,name_infor("네시",false),&img_mons_nesi,120,9,9,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_NONE_STAIR | M_FLAG_CAN_SEE_INVI | M_FLAG_SWIM | M_FLAG_CANT_GROUND,99,1,10,'8' },
	
	{MON_SANGHAI,15,1,name_infor("상해 인형",true),&img_mons_sanghai[0],80,5,22,
	{36,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,1,7,'d' },
	
	{MON_HOURAI,15,1,name_infor("봉래 인형",true),&img_mons_hourai[0],120,20,2,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,1,10,'d' },
	
	{MON_FAKE_SANGHAI,12,1,name_infor("모조 상해 인형",true),&img_mons_sanghai[1],60,5,17,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,1,7,'d' },
	
	{MON_FAKE_HOURAI,12,1,name_infor("모조 봉래 인형",true),&img_mons_hourai[1],90,15,2,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,1,10,'d' },
	
	{MON_TOKIKO,11,1205,name_infor("책읽는 요괴",false),&img_mons_tokiko,92,1,15,
	{16,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'&' },

	
	{MON_TOZIKO,15,3905,name_infor("토지코",false),&img_mons_toziko,115,5,15,
	{29,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor("전격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'&' },

	{MON_FUTO,16,4605,name_infor("후토",false),&img_mons_futo,130,1,20,
	{14,25,0},{ATT_NORMAL,ATT_NORMAL,ATT_NONE},{name_infor("접시",false),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,8,'&' },

	{MON_MAMIZO,19,7205,name_infor("마미조",false),&img_mons_mamizo,210,15,2,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,3,1,10,'&' },

	{MON_SEIGA,17,6205,name_infor("세이가",false),&img_mons_seiga,170,10,8,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("공격",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_NONE_STAIR,1,1,12,'&' },

	{ MON_CLOSE_DOOR, 1, 0, name_infor("잠긴 문", true), &img_mons_close_door, 1, 10, 0,
	{ 0, 0, 0 }, { ATT_NONE, ATT_NONE, ATT_NONE }, { name_infor(), name_infor(), name_infor() },
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE | M_FLAG_NO_STATE, 99, 0, 10 ,'&' },

	{ MON_MURASA,17, 6510,name_infor("무라사",false),&img_named_murasa,160,5,12,
	{ 19,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SWIM | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_KEINE,15,4212,name_infor("케이네",false),&img_named_keine,140,10,5,
	{ 14,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,3,3,10,'&' },

	{ MON_KEINE2,15,4212,name_infor("백택 케이네",false),&img_named_keine2,140,0,15,
	{ 30,30,55 },{ ATT_NORMAL,ATT_NORMAL,ATT_NORMAL },{ name_infor("공격",true), name_infor("공격",true), name_infor("박치기",false) },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,1,0,7,'&' },

	{ MON_YOUMU,21,9465,name_infor("요우무",false),&img_named_youmu,230,0,20,
	{ 38,46,0 },{ ATT_NORMAL,ATT_NORMAL,ATT_NONE },{ name_infor("백루검",true),name_infor("루관검",true),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,5,'&' },

	{ MON_LYRICA,13,1624,name_infor("리리카",false),&img_named_lyrica,68,1,15,
	{ 16,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_STAIR | M_FLAG_FLY | M_FLAG_SPEAK,3,1,10,'&' },

	//메를랑과 루나사는 디버프를 위한 HD 보정
	{ MON_MERLIN,16,1642,name_infor("메를랑",true),&img_named_merlin,72,5,5,
	{ 12,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_STAIR | M_FLAG_FLY | M_FLAG_SPEAK,3,1,10,'&' },

	{ MON_LUNASA,17,1890,name_infor("루나사",false),&img_named_lunasa,81,2,10,
	{ 15,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_STAIR | M_FLAG_FLY | M_FLAG_SPEAK,3,1,10,'&' },

	{ MON_KOMACHI,21,9218,name_infor("코마치",false),&img_named_komachi,310,15,3,
	{ 40,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("낫",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,0,13,'&' },

	{ MON_IKU,15,4162,name_infor("이쿠",false),&img_named_iku,85,10,20,
	{ 20,30,0 },{ ATT_NORMAL,ATT_ELEC,ATT_NONE },{ name_infor("공격",true),name_infor("옷깃",true),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_LARVA,6,1,name_infor("라바",false),&img_named_larva,35,2,7,
	{ 7,0,0 },{ ATT_S_POISON,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10,'&' },

	{ MON_NEMUNO,10,1221,name_infor("네무노",false),&img_named_nemuno,90,15,2,
	{ 16,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("칼",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },

	{ MON_AUNN,6,350,name_infor("아운",true),&img_named_aunn,38,15,2,
	{ 8,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SHIELD | M_FLAG_SPEAK,3,1,10,'&' },

	{ MON_NARUMI,10,1405,name_infor("나루미",false),&img_named_narumi,70,30,0,
	{ 19,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,12,'&' },

	{ MON_MAI2,1,0,name_infor("마이",false),&img_named_mai,10,1,12,
	{ 0, 0, 0 }, { ATT_NONE, ATT_NONE, ATT_NONE }, { name_infor(), name_infor(), name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_NO_ATK | M_FLAG_UNIQUE | M_FLAG_CANT_NETURAL | M_FLAG_CONFUSE | M_FLAG_FLY | M_FLAG_SPEAK, 2, 1, 10,'&' },

	{ MON_SATONO,1,0,name_infor("사토노",false),&img_named_satono,10,1,12,
	{ 0, 0, 0 }, { ATT_NONE, ATT_NONE, ATT_NONE }, { name_infor(), name_infor(), name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_NO_ATK | M_FLAG_UNIQUE | M_FLAG_CANT_NETURAL | M_FLAG_CONFUSE | M_FLAG_FLY | M_FLAG_SPEAK, 2, 1, 10,'&' },

	{ MON_KOKORO,17,1,name_infor("코코로",false),&img_named_kokoro[0],170,9,12,
	{ 20,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_KOKORO1,17,1,name_infor("코코로",false),&img_named_kokoro[1],170,9,12,
	{ 30,0,0 },{ ATT_FIRE,ATT_NONE,ATT_NONE },{ name_infor("부채",false),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_KOKORO2,17,1,name_infor("코코로",false),&img_named_kokoro[2],170,9,12,
	{ 30,0,0 },{ ATT_COLD,ATT_NONE,ATT_NONE },{ name_infor("부채",false),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_KOKORO3,17,1,name_infor("코코로",false),&img_named_kokoro[3],170,9,12,
	{ 30,0,0 },{ ATT_ELEC,ATT_NONE,ATT_NONE },{ name_infor("부채",false),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10,'&' },

	{ MON_SUMIREKO,20,9429,name_infor("스미레코",false),&img_named_sumireko,200,1,15,
	{ 16,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_SILENCE | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10 ,'&' },

	{ MON_ANCHOR,1,1,name_infor("닻",true),&img_mons_anchor,100,15,0,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,99,0,10,'A' },

	{ MON_MASK_ANGRY,10,1,name_infor("분노의 가면",true),&img_mons_mask_angry,50,0,20,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE | M_FLAG_FLY,1,1,10,'*' },

	{ MON_MASK_SAD,10,1,name_infor("슬픔의 가면",true),&img_mons_mask_sad,50,0,20,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE | M_FLAG_FLY,1,1,10,'*' },

	{ MON_MASK_HAPPY,10,1,name_infor("기쁨의 가면",true),&img_mons_mask_happy,50,0,20,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE | M_FLAG_FLY,1,1,10,'*' },

	{ MON_TRASH,1,1,name_infor("쓰레기 더미",false),&img_mons_trash[0],100,10,0,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,1,1,10,'*' },

	{ MON_OCCULT_LONG,1,1,name_infor("팔척귀신",true),&img_mons_occult_long,45,10,3,
	{ 15,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,3,1,10,'G' },

	{ MON_OCCULT_DISK,1,1,name_infor("반쵸사라야시키",false),&img_mons_occult_disk,25,1,15,
	{ 5,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,2,1,10,'G' },

	{ MON_OCCULT_SMALL,1,1,name_infor("리틀 그린맨",false),&img_mons_occult_small,15,0,10,
	{ 6,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CANT_NETURAL,1,1,8,'g' },

	{ MON_KUNEKUNE,1,1,name_infor("쿠네쿠네",false),&img_mons_occult_kunekune,1,0,0,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_SILENCE | M_FLAG_NONE_MOVE | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,1,1,10,'g' },

	{ MON_KANAME,1,1,name_infor("요석",true),&img_mons_kaname,1,0,0,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_NO_ATK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_PASSED_ALLY | M_FLAG_NONE_MOVE | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE,1,1,10,'*' },

	{ MON_SHEEP,10,675,name_infor("꿈꾸는 양",true),&img_mons_sheep,55,1,10,
	{ 8,0,0 },{ ATT_SLEEP,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_ANIMAL | M_FLAG_SPEAK, 0, 1, 10 ,'Y' },

	{ MON_BEE,1,1,name_infor("벌",true),&img_mons_bee,1,0,0,
	{ 1,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10,'b' },

	{ MON_BUSH,1,0,name_infor("풀",true),&img_mons_bush,50,0,0,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
	 M_FLAG_NONE_STAIR | M_FLAG_NONE_MOVE | M_FLAG_NO_STATE | M_FLAG_INANIMATE | M_FLAG_UNHARM | M_FLAG_NO_ATK  | M_FLAG_CANT_NETURAL,99,1,10,'W' },

	 { MON_SION, 1, 0, name_infor("시온", true), &img_mons_sion, 1, 8, 0,
	 { 0,0,0}, { ATT_NONE,ATT_NONE,ATT_NONE }, {name_infor(),name_infor(),name_infor() },
		M_FLAG_NONE_STAIR | M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_UNIQUE | M_FLAG_PASSED_ENEMY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_UNHARM , 99, 1, 10 ,'&' },

	{ MON_CURSE_DOLL, 8, 140, name_infor("저주받은 인형", true), &img_mons_cursed_doll, 30, 1, 12,
	{ 4,0,0 }, { ATT_NORMAL,ATT_NONE,ATT_NONE }, { name_infor("공격",true),name_infor(),name_infor() },
		M_FLAG_OPEN_DOOR  | M_FLAG_INANIMATE, 1, 1, 10,'d' },

	{ MON_DANCING_WEAPON, 10, 870, name_infor("무기의 츠구모가미", true), &img_mons_default, 50, 0, 14,
		{ 19,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
		M_FLAG_FLY | M_FLAG_INANIMATE, 1, 1, 9 ,'(' },

	{ MON_DANCING_ARMOUR, 10, 870, name_infor("갑옷의 츠구모가미", true), &img_mons_default, 80, 10, 2,
		{ 15,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
		M_FLAG_FLY | M_FLAG_PASSED_ALLY |  M_FLAG_INANIMATE, 5, 1, 10,']' },

	{ MON_ELEC_BALL, 1, 0, name_infor("전기구체", true), &img_blast[2], 10, 0, 10,
	{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
		M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_CONFUSE |
		M_FLAG_PASSED_ENEMY | M_FLAG_FLY | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE, 99, 0, 10,'*' },

	{ MON_HATATE, 10, 1221, name_infor("하타테", false), &img_named_hatate, 75, 2, 20,
		{ 7,0,0 },{ ATT_NORMAL,ATT_NONE,ATT_NONE },{ name_infor("공격",true),name_infor(),name_infor() },
		M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10,'&' },

	{ MON_BOMB, 1, 0, name_infor("매직봄", true), &img_item_evo_bomb, 10, 0, 10,
		{ 0,0,0 },{ ATT_NONE,ATT_NONE,ATT_NONE },{ name_infor(),name_infor(),name_infor() },
		M_FLAG_NONE_MOVE | M_FLAG_NONE_STAIR | M_FLAG_NO_ATK | M_FLAG_CANT_NETURAL | M_FLAG_INANIMATE, 99, 0, 10,'*' }
		
};
