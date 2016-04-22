//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: monster_list.cpp
//
// ����: ������ ������
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "mon_infor.h"




/*
{MON_�̹���,����,����ġ,name_infor(�̸�,true),&img_mons_�̹���,ü��,AC,EV,
{���ݷ�,��2,��3},{ATT_����,ATT_NONE,ATT_NONE},{name_infor(�̸�,true),name_infor(),name_infor()},
�÷���,��������,������,���ǵ�}
*/
const mon_infor mondata[] = {
	{MON_REIMUYUKKURI,2,4,name_infor("���������̹�",false),&img_mons_reimu_yukkuri,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15},

	{MON_REIMUYUKKURI,2,70,name_infor("���������̹�",false),&img_mons_reimu_yukkuri,25,0,5,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15},

	{MON_RAT,1,1,name_infor("��",false),&img_mons_rat,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,0,10},

	{MON_FAIRY_GREEN,1,2,name_infor("���� ����",true),&img_mons_fairy_green,13,0,8,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_FAIRY_BLUE,2,3,name_infor("ź�� ����",true),&img_mons_fairy_blue,8,0,12,
	{1,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_FAIRY_RED,3,5,name_infor("���� ����",true),&img_mons_fairy_red,21,2,6,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_MOOK,1,2,name_infor("���",true),&img_mons_mook,5,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10},

	{MON_MOOK,1,18,name_infor("���",true),&img_mons_mook,5,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10},

	{MON_CROW,1,15,name_infor("���",false),&img_mons_crow,17,0,8,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,7},

	{MON_CRANE,5,116,name_infor("�η��",false),&img_mons_crane,33,3,10,
	{8,8,20},{ATT_NORMAL,ATT_NORMAL,ATT_NORMAL},{name_infor("����",true),name_infor("����",true),name_infor("�ɱ�",false)},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10},

	{MON_SPIDER,3,11,name_infor("�Ź�",false),&img_mons_spider,18,1,10,
	{2,2,3},{ATT_NORMAL,ATT_NORMAL,ATT_S_POISON},{name_infor("����",true),name_infor("����",true),name_infor("����",false)},
	M_FLAG_ANIMAL,0,1,10},

	{MON_SNAKE,4,21,name_infor("��",true),&img_mons_snake,22,1,10,
	{4,3,0},{ATT_S_POISON,ATT_NORMAL,ATT_NONE},{name_infor("����",true),name_infor("����",true),name_infor()},
	M_FLAG_ANIMAL,0,1,7},

	{MON_KATPA,2,7,name_infor("ı��",false),&img_mons_new_kappa,20,2,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM,0,1,10},

	{MON_KATPA_GUN,5,65,name_infor("ı�� ��ݺ�",true),&img_mons_katpa_gun,40,1,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM,0,2,10},

	{MON_FAIRY_GREEN_WARRIOR,5,128,name_infor("���� ����",false),&img_mons_fairy_green_warroir,35,8,6,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10},

	{MON_FAIRY_BLUE_MAGICIAN,7,150,name_infor("���� ����",false),&img_mons_fairy_blue_magician,25,2,16,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_FAIRY_RED_COMMANDER,8,214,name_infor("���� ���ְ�",true),&img_mons_fairy_red_commander,33,0,6,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_RUMIA,6,240,name_infor("��̾�",false),&img_named_rumia,40,1,10,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_MISTIA,8,535,name_infor("�̽�Ƽ��",false),&img_named_mistia,60,1,12,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,8},

	{MON_WRIGGLE,7,350,name_infor("����",true),&img_named_wriggle,50,3,10,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10},

	{MON_CIRNO,9,999,name_infor("ġ����",false),&img_named_cirno,99,1,9,
	{15,25,0},{ATT_NORMAL,ATT_COLD,ATT_NONE},{name_infor("����",true),name_infor("�ñ�",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10},

	{MON_MEDICINE,9,1066,name_infor("�޵�",true),&img_named_medicine,70,2,10,
	{8,12,0},{ATT_S_POISON,ATT_S_POISON,ATT_NONE},{name_infor("����",false),name_infor("����",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,2,1,10},

	{MON_DIEFAIRY,6,570,name_infor("�����",true),&img_named_diefairy,50,0,15,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_WOMAN,1,0,name_infor("�ΰ�����",false),&img_mons_human_woman,10,1,10,
	{1,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_MAN,2,8,name_infor("�ΰ�����",false),&img_mons_human_man,20,1,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_YINYANG,5,66,name_infor("�����",false),&img_mons_human_yinyang,30,1,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_PRIEST,5,92,name_infor("����",false),&img_mons_human_priest,23,1,10,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_HUMAM_SAMURI,8,210,name_infor("�繫����",false),&img_mons_human_samuri,50,6,8,
	{16,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},

	{MON_FIREFLY,2,5,name_infor("�ݵ�����",false),&img_mons_firefly,18,1,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10},

	{MON_BUTTERFLY,1,0,name_infor("����",false),&img_mons_butterfly,5,1,20,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_UNHARM | M_FLAG_NO_ATK | M_FLAG_CONFUSE | M_FLAG_ANIMAL,0,1,5},

	{MON_GHOST,1,2,name_infor("����",true),&img_mons_ghost[0],10,0,10,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,12},

	{MON_BAKEKASA,4,21,name_infor("���䱫",false),&img_mons_bakekasa,20,1,12,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	0,1,1,10},

	{MON_GREEN_MOOK,2,6,name_infor("�ʷϸ��",true),&img_mons_green_mook,18,0,10,
	{4,4,8},{ATT_NORMAL,ATT_NORMAL,ATT_S_POISON},{name_infor("����",true),name_infor("����",true),name_infor("����",true)},
	M_FLAG_FLY,0,0,10},

	{MON_ORANGE_MOOK,3,11,name_infor("��Ȳ���",true),&img_mons_orange_mook,22,0,14,
	{9,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10},

	{MON_GRAY_MOOK,4,23,name_infor("ȸ�����",true),&img_mons_gray_mook,18,1,10,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,10},

	{MON_FROG,7,224,name_infor("������",false),&img_mons_frog,60,1,14,
	{16,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SWIM | M_FLAG_ANIMAL,0,0,9},
	
	{MON_BLACK_CAT,8,287,name_infor("����������",false),&img_mons_black_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("������",false),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7},
	
	{MON_ORANGE_CAT,8,287,name_infor("��Ȳ������",false),&img_mons_orange_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("������",false),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7},

	{MON_WHITE_CAT,8,287,name_infor("�Ͼ������",false),&img_mons_white_cat,40,0,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("������",false),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,7},

	{MON_CROW_TENGU,10,532,name_infor("����ٱ�",false),&img_mons_crow_tengu,70,3,12,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10},

	{MON_ONI,14,1412,name_infor("����",false),&img_mons_oni,120,10,2,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,10},

	{MON_KISUME,5,220,name_infor("Ű����",false),&img_named_kisume,30,1,10,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10},

	{MON_CHEN,11,1325,name_infor("þ",true),&img_named_chen,85,0,15,
	{15,15,20},{ATT_NORMAL,ATT_NORMAL,ATT_NORMAL},{name_infor("������",false),name_infor("������",false),name_infor("������",false)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,8},

	{MON_KOGASA,7,550,name_infor("�ڰ���",false),&img_named_kogasa,50,1,14,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},

	{MON_SUNNY,4,129,name_infor("���",false),&img_named_sunny,35,1,10,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},

	{MON_LUNAR,4,129,name_infor("�糪",false),&img_named_lunar,30,1,10,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10},

	{MON_STAR,4,129,name_infor("��Ÿ",false),&img_named_star,25,1,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,10,10},

	{MON_MARISAYUKKURI,8,470,name_infor("������������",false),&img_mons_marisa_yukkuri,70,2,5,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,15},

	{MON_AYAYUKKURI,12,810,name_infor("Ű���̸���",false),&img_mons_aya_yukkuri,65,0,16,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,1,1,4},

	{MON_REMILIAYUKKURI,14,1440,name_infor("���������̷�",false),&img_mons_remila_yukkuri,60,5,12,
	{18,27,0},{ATT_VAMP,ATT_VAMP,ATT_NONE},{name_infor("����",false),name_infor("����",false),name_infor()},
	M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,3,1,8}, //���߿� ���� �������� �ٲ�

	{MON_ALICEYUKKURI,11,960,name_infor("�������ٸ���",false),&img_mons_alice_yukkuri,100,7,5,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,1,0,15},

	{MON_YOUMUYUKKURI,15,1340,name_infor("��������칫",false),&img_mons_default,90,10,10,
	{32,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,9}, //���߿� õõ�� �߰�


	{MON_YAMABIKO,9,562,name_infor("�߸�����",false),&img_mons_yamabiko,75,2,10,
	{13,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR,0,0,10},

	{MON_KATPA_SPEAR,9,830,name_infor("ı�� â��",true),&img_mons_new_kappa_spear,70,5,10,
	{20,0,0},{ATT_SPEAR,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR | M_FLAG_SWIM,0,0,10},

	{MON_KATPA_WATER_WIZARD,10,960,name_infor("ı�� ������",false),&img_mons_new_kappa_wizard,45,4,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_OPEN_DOOR | M_FLAG_SWIM,1,0,10},

	{MON_YAMABUSH_TENGU,11,1062,name_infor("�߸��ν��ٱ�",false),&img_mons_yamabush_tengu,60,3,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI,1,1,10},


	{MON_HANATACA_TENGU,12,1183,name_infor("�ϳ�Ÿī�ٱ�",false),&img_mons_hanataca_tengu,78,5,13,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10},


	{MON_BLUE_ONI,14,1412,name_infor("�ƿ�����",false),&img_mons_blue_oni,120,10,2,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},

	{MON_MUSHROOM,9,832,name_infor("�����䱫",false),&img_mons_mushroom,50,6,0,
	{20,0,0},{ATT_S_POISON,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK,0,0,10},

	{MON_KYOUKO,6,500,name_infor("����",false),&img_named_kyouko,30,1,12,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},


	{MON_SIGMUND,3,154,name_infor("���׹�Ʈ",false),&img_named_sigmund,30,0,11,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},

	{MON_WOLF_TENGU,12,1312,name_infor("��� �ٱ�",false),&img_mons_default,49,12,2,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,2,13},

	{MON_MOMIZI,12,1923,name_infor("�����",false),&img_named_momizi,132,12,2,
	{32,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,2,3,10},

	{MON_AYA,15,3421,name_infor("�ƾ�",false),&img_named_aya,112,1,14,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,8},

	
	{MON_TEST_KATPA,2,50,name_infor("ı��",false),&img_mons_katpa,20,2,5,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_SWIM,0,1,10},

	//������� �ӽ� ������
	{MON_WAKASAGI,6,300,name_infor("��ī�������",false),&img_named_wakasagi,40,0,13,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SWIM | M_FLAG_SPEAK | M_FLAG_CANT_GROUND,0,1,10},

	{MON_YAMAME,8,854,name_infor("�߸���",false),&img_named_yamame,90,3,6,
	{15,16,24},{ATT_NORMAL,ATT_NONE,ATT_S_POISON},{name_infor("����",true),name_infor("����",true),name_infor("����",false)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},
	
	{MON_NAZRIN,7,570,name_infor("���",true),&img_named_nazrin,45,0,8,
	{14,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},

	{MON_DAUZING,10,1,name_infor("��ⷳ",true),&img_mons_dauzing,80,8,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_FLY,99,0,8},
	
	{MON_YOSIKA,9,960,name_infor("���ī",false),&img_named_yosika,150,1,3,
	{22,30,30},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor("������",false),name_infor("������",false)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,0,10},
	
	{MON_SEKIBANKI,8,824,name_infor("��Ű��Ű",false),&img_named_sekibanki,70,3,9,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_CAN_SEE_INVI,1,1,10},
	
	{MON_SEKIBANKI_BODY,8,824,name_infor("��Ű��Ű",false),&img_named_sekibanki_body,70,10,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_CAN_SEE_INVI,1,0,10},
	
	{MON_SEKIBANKI_HEAD,1,1,name_infor("��Ű��Ű",false),&img_named_sekibanki_head,30,0,15,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",false),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI,0,1,10},
	
	{MON_NITORI,13,2188,name_infor("���丮",false),&img_named_nitori,100,8,12,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,1,1,10},
	
	{MON_KEGERO,10,1297,name_infor("ī�Է�",false),&img_named_kagero,120,3,12,
	{30,25,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",false),name_infor("������",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},
	
	{MON_PARSI,9,925,name_infor("�ĸ���",false),&img_named_parsi,100,8,15,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},
	
	{MON_BENBEN,6,520,name_infor("����",true),&img_named_benben,60,3,3,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10},
	
	{MON_YATHASI,6,520,name_infor("�����Ͻ�",false),&img_named_yathasi,50,0,8,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10},
	
	{MON_ORIN,13,2310,name_infor("����",true),&img_named_orin,95,1,12,
	{29,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},
	
	{MON_ORIN_CAT,13,2310,name_infor("����",true),&img_named_orin_cat,70,0,18,
	{21,21,0},{ATT_NORMAL,ATT_FIRE,ATT_NONE},{name_infor("������",false),name_infor("������",false),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,5},
	
	{MON_ZOMBIE_FAIRY,7,183,name_infor("������",false),&img_mons_zombiefairy,35,0,12,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10},
	
	{MON_ICHIRIN,13,3240,name_infor("��ġ��",true),&img_named_ichirin,98,8,2,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,1,10},
	
	{MON_UNZAN,13,1,name_infor("����",true),&img_named_unzan,150,0,0,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_FLY | M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON,99,1,10},
	
	{MON_UNZAN_PUNCH,13,1,name_infor("������ �ָ�",true),&img_named_unzan_punch[0],30,0,6,
	{32,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("���Ž�",false),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY  | M_FLAG_PASSED_ALLY,99,1,15},
	
	{MON_PACHU,12,1923,name_infor("����",false),&img_named_pachu,70,1,5,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,99,1,10},
	
	{MON_MAGIC_BOOK,10,830,name_infor("������",false),&img_mons_magic_book[0],50,0,13,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_NO_ATK,99,1,8},
	 
	{MON_HOBGOBRIN,6,142,name_infor("ȩ������",true),&img_mons_hobgobrin,40,1,6,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},
	
	{MON_HOBGOBRIN_MAID,8,692,name_infor("ȩ������ ���̵�",false),&img_mons_hobgobrin_maid,80,6,6,
	{24,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},

	{MON_HOBGOBRIN_LIBRARIAN,11,1120,name_infor("ȩ������ �缭",false),&img_mons_hobgobrin_librarian,70,1,10,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},
	
	{MON_HOBGOBRIN_TEMP,13,1510,name_infor("ȩ������ �Ǹ�����",false),&img_mons_hobgobrin_temp,70,0,6,
	{11,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},
	
	{MON_MAID_FAIRY,7,171,name_infor("���� ���̵�",false),&img_mons_maid_fairy,32,1,12,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10},
	
	{MON_CHUPARCABRA,12,1384,name_infor("����ī���",false),&img_mons_chuparcabra,122,3,14,
	{23,0,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,7},
	
	{MON_KOAKUMA,11,1615,name_infor("�ҾǸ�",false),&img_named_koakuma,60,1,6,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10},
	
	{MON_MEIRIN,8,850,name_infor("ȫ���̸�",true),&img_named_meirin,90,8,6,
	{30,14,14},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("ö���",false),name_infor("����",true),name_infor("����",true)},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10},
	
	{MON_SAKUYA,13,3072,name_infor("������",false),&img_named_sakuya,100,1,18,
	{26,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},
	
	{MON_REMILIA,15,4521,name_infor("���и���",false),&img_named_remilia,140,1,20,
	{30,24,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor("����",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,9},
	
	{MON_EAGLE,9,921,name_infor("�Ŵ� ��",false),&img_mons_eagle,80,1,10,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_ANIMAL,0,1,10},
	
	{MON_TIGER,11,1180,name_infor("ȣ����",false),&img_mons_tiger,93,3,6,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_ANIMAL ,0,1,10},
	
	{MON_RAIJUU,10,950,name_infor("����",false),&img_mons_raijuu,60,1,12,
	{18,0,0},{ATT_S_POISON,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,8},
	
	{MON_DRAGON_BABY,15,1260,name_infor("���� ����",false),&img_mons_dragon_baby,90,10,6,
	{14,14,27},{ATT_NORMAL,ATT_NONE,ATT_FIRE},{name_infor("����",true),name_infor("����",true),name_infor("����",false)},
	M_FLAG_SPEAK | M_FLAG_FLY | M_FLAG_ANIMAL,1,1,10},
	
	{MON_KASEN,16,5872,name_infor("ī��",true),&img_named_kasen,150,5,6,
	{38,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},
	
	{MON_YAMAWARO_NINJA,8,593,name_infor("�߸��ͷ� ��ô��",true),&img_mons_yamawaro_ninja,62,5,7,
	{8,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},
	
	{MON_YAMAWARO_WAWRRIOR,9,943,name_infor("�߸��ͷ� ���ݺ�",true),&img_mons_yamawaro_warrior,80,5,6,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},
	
	{MON_YAMAWARO_FLAG,11,1110,name_infor("�߸��ͷ� ��ߺ�",true),&img_mons_yamawaro_flag,60,7,5,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},
		
	{MON_ONBASIRA,1,1,name_infor("�¹ٽö�",true),&img_mons_onbasira,60,10,0,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NONE_MOVE | M_FLAG_NO_ATK | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY ,99,0,10},
	
	{MON_RED_UFO,12,1280,name_infor("���� �����",false),&img_mons_red_ufo,95,5,10,
	{30,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,1,1,9},
	
	{MON_GREEN_UFO,12,1280,name_infor("�׸� �����",false),&img_mons_green_ufo,95,5,10,
	{30,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,1,1,9},
		
	{MON_BLUE_UFO,12,1280,name_infor("���� �����",false),&img_mons_blue_ufo,95,5,10,
	{30,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,1,1,9},
		
	
	{MON_KOISHI,13,3880,name_infor("���̽�",false),&img_named_koishi,70,3,18,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_INVISIBLE | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,3,1,7},
	{MON_NUE,14,4140,name_infor("����",false),&img_named_nue,140,10,6,
	{18,25,0},{ATT_SPEAR,ATT_ELEC,ATT_NONE},{name_infor("����",true),name_infor("����",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},
	{MON_SANPEI_FIGHTER,12,1601,name_infor("������������",false),&img_mons_sanpei_fighter,120,15,6,
	{26,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("�帱",false),name_infor(),name_infor()},
	M_FLAG_FLY,99,1,8},
	{MON_VAMPIER_BAT,9,824,name_infor("���� ����",false),&img_mons_vamp_bat,60,0,20,
	{14,0,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_ANIMAL,0,1,5},
	{MON_DEAGAMA,12,800,name_infor("ū�β���",false),&img_mons_dagama,90,10,2,
	{24,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_SWIM,3,1,10},
	{MON_RABBIT,1,1,name_infor("�䳢",false),&img_mons_rabit,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL,0,1,10},
	{MON_YOKAI_RABBIT,1,1,name_infor("�䱫 �䳢",false),&img_mons_youkai_rabit,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	0,1,1,10},
	{MON_NAMAZ,16,1650,name_infor("������",false),&img_mons_namaz,90,12,2,
	{45,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_SWIM,1,1,10},
	{MON_HELL_CROW,9,374,name_infor("�������",false),&img_mons_hell_crow,48,1,10,
	{20,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_ANIMAL,0,0,7},
	{MON_RACCON,15,1484,name_infor("�ʱ���",false),&img_mons_raccoon,100,1,16,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_ANIMAL,0,1,10},
	{MON_LANTERN_YOUKAI,15,1333,name_infor("����䱫",false),&img_mons_lantern_youkai,88,8,8,
	{25,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,1,10},
	{MON_YINYAN,30,8000,name_infor("�����",true),&img_mons_yinyan,300,0,0,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_FLY | M_FLAG_CAN_SEE_INVI,99,2,9},
	{MON_YUUGENMAGAN,14,2432,name_infor("���ո���",true),&img_mons_yugenmagan,100,12,10,
	{15,0,0},{ATT_ELEC,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,99,1,10},
	{MON_ELIS,9,535,name_infor("������",false),&img_mons_elise,70,0,12,
	{15,10,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,2,1,6},
	{MON_SARIEL,15,2762,name_infor("�縮��",true),&img_mons_sariel,130,10,20,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,3,1,10},
	{MON_SARA,9,435,name_infor("���",false),&img_mons_sara,85,15,5,
	{22,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},
	{MON_LUIZE,9,435,name_infor("������",false),&img_mons_louise,75,1,12,
	{10,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,10},		
	{MON_YUKI,14,2432,name_infor("��Ű",false),&img_mons_yuki,130,8,15,
	{25,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10},		
	{MON_MAI,14,2432,name_infor("����",false),&img_mons_mai,130,8,15,
	{25,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,2,1,10},		
	{MON_YUMEKO,16,5672,name_infor("������",false),&img_mons_yumeko,180,3,16,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE  | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_FLY,4,1,10},

	{MON_MAGICAL_STAR,4,1,name_infor("�ɼ�",true),&img_mons_option,10,0,5,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_FLY,99,0,5},

	{MON_GOLEM,8,1,name_infor("��",true),&img_mons_golem,80,10,0,
	{25,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	0,99,0,10},
	{MON_EVIL_EYE,3,15,name_infor("�̺�����",false),&img_mons_evil_eye,20,0,8,
	{3,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_FLY,0,1,10},
	{MON_LITTLE_IMP,3,15,name_infor("���� ����",false),&img_mons_little_imp,25,1,15,
	{6,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_SPEAK | M_FLAG_FLY,0,1,10},
	
	{MON_ENSLAVE_GHOST,1,2,name_infor("����",true),&img_mons_ghost[0],10,0,10,
	{4,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY,0,0,12},

	{MON_SCHEMA_EYE,4,1,name_infor("������ ���� ��",true),&img_mons_schema_eye,30,0,12,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NONE_MOVE  | M_FLAG_CAN_SEE_INVI  | M_FLAG_NO_ATK | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY | M_FLAG_PASSED_ENEMY | M_FLAG_FLY,99,0,10},
	
	{MON_FLAN,21,12999,name_infor("�ö��帣",false),&img_named_flandre,230,10,15,
	{31,28,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor("����",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_UNIQUE | M_FLAG_SPEAK | M_FLAG_FLY,3,1,10},

	{MON_FLAN_BUNSIN,21,0,name_infor("�ö��帣�� �н�",false),&img_named_flandre,80,5,10,
	{18,15,0},{ATT_VAMP,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor("����",true),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY,3,1,10},

	
	{MON_RABIT_BOMB,9,220,name_infor("�䳢 ������",true),&img_mons_bomb_rabbit,12,1,20,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,9},
	
	{MON_RABIT_SPEAR,11,340,name_infor("�䳢 ��â��",true),&img_mons_spear_rabbit,35,5,15,
	{28,0,0},{ATT_SPEAR,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,1,10},
	
	{MON_RABIT_SUPPORT,12,440,name_infor("�䳢 ������",true),&img_mons_support_rabbit,25,3,15,
	{10,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL | M_FLAG_CAN_SEE_INVI |  M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,0,2,10},

	{MON_RABIT_MAGIC,10,570,name_infor("�䳢 ������",false),&img_mons_magic_rabbit,30,2,20,
	{5,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_ANIMAL |  M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,1,1,10},

	
	{MON_TEWI,13,2150,name_infor("����",false),&img_named_tewi,60,3,22,
	{12,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,2,1,8},

	{MON_CLOWNPIECE,15,3220,name_infor("Ŭ����ǽ�",false),&img_named_clownpiece,120,3,18,
	{22,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("ȶ��",true),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_SPEAK | M_FLAG_FLY,1,1,8},
	
	{MON_DOREMI,14,3904,name_infor("������",false),&img_named_doremi,130,8,10,
	{15,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_UNIQUE | M_FLAG_CAN_SEE_INVI | M_FLAG_OPEN_DOOR | M_FLAG_SPEAK,3,1,12},

	{MON_FAIRY_HERO,12,977,name_infor("���� ����",true),&img_mons_default,120,10,8,
	{28,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,0,10},
	
	{MON_FAIRY_SOCERER,10,651,name_infor("���� ���ɼ���",false),&img_mons_default,49,5,12,
	{7,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},
	
	{MON_FAIRY_SUN_FLOWER,13,1180,name_infor("�عٶ�� ����",true),&img_mons_default,90,8,12,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FAIRY | M_FLAG_FLY | M_FLAG_SPEAK,0,2,10},
	
	{MON_MOON_RABIT_SUPPORT,9,675,name_infor("���䳢 ������",true),&img_mons_default,69,5,8,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,0,2,10},
	
	{MON_MOON_RABIT_ATTACK,13,1034,name_infor("���䳢 ô�ĺ�",true),&img_mons_default,90,10,6,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,0,1,10},

	{MON_MOON_RABIT_ELITE,16,1678,name_infor("���䳢 ������",true),&img_mons_default,128,15,10,
	{39,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,1,1,10},
	
	{MON_MAC,12,1230,name_infor("��",true),&img_mons_default,80,5,12,
	{21,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_ANIMAL,0,2,10},
	
	{MON_NIGHTMARE,15,1712,name_infor("�Ǹ��� ����",true),&img_mons_default,120,12,5,
	{31,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10},
	
	{MON_LUNATIC,13,1374,name_infor("������ ����",true),&img_mons_default,100,12,5,
	{26,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,1,1,10},
	
	{MON_HAUNT,7,254,name_infor("����",true),&img_mons_default,30,3,15,
	{14,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_FLY | M_FLAG_SPEAK,0,1,8},

	{MON_FIRE_CAR,16,1782,name_infor("ȭ��",false),&img_mons_default,150,15,2,
	{40,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK,2,1,8},
	
	{MON_HELL_SPIDER,11,782,name_infor("��������",false),&img_mons_default,80,5,10,
	{25,0,0},{ATT_S_POISON,ATT_NONE,ATT_NONE},{name_infor("����",false),name_infor(),name_infor()},
	M_FLAG_SPEAK | M_FLAG_ANIMAL,0,0,10},
	
	{MON_BLOOD_HAUNT,12,835,name_infor("�ͺ� ����",true),&img_mons_default,95,0,12,
	{20,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},
	
	{MON_HELL_HOUND,9,434,name_infor("������",false),&img_mons_default,65,1,15,
	{29,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",false),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_SPEAK | M_FLAG_ANIMAL,0,1,10},
	
	{MON_DESIRE,1,1,name_infor("����� ���",false),&img_mons_default,10,0,6,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	0,0,1,10},

	{MON_FLOWER_TANK,18,3220,name_infor("�ö�� ����",false),&img_mons_default,12000,10,10,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_NONE_MOVE,99,1,9},
	
	{MON_EVIL_EYE_TANK,25,5043,name_infor("�̺� ���� ����",false),&img_mons_default,150,20,10,
	{0,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI,99,2,9},
	
	{MON_SNOW_GIRL,14,1464,name_infor("����",false),&img_mons_default,77,2,16,
	{27,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_FLY | M_FLAG_SPEAK,0,1,10},
	
	{MON_LETTY,12,1832,name_infor("��Ƽ",false),&img_mons_default,120,9,6,
	{19,0,0},{ATT_COLD,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,1,10},
	
	{MON_YORIHIME,20,7682,name_infor("�丮����",false),&img_mons_default,250,8,18,
	{45,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,5,3,8},

	{MON_TOYOHIME,20,7682,name_infor("�������",false),&img_mons_default,260,18,8,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,5,3,10},
	
	{MON_UTSUHO,23,13456,name_infor("����ȣ",false),&img_mons_default,450,30,2,
	{50,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI  | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,4,3,10},
	
	{MON_SUIKA,22,9760,name_infor("����ī",false),&img_mons_default,350,28,5,
	{60,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,3,1,10},
	
	{MON_REIMU,27,0,name_infor("���̹�",false),&img_mons_default,999,5,50,
	{50,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,99,4,8},
	
	{MON_ALICE,18,8467,name_infor("�ٸ���",false),&img_mons_default,130,10,15,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,2,10},

	{MON_SEIRAN,8,573,name_infor("���̶�",true),&img_mons_default,64,2,11,
	{19,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,0,2,10},
	
	{MON_RINGO,13,1585,name_infor("����",false),&img_mons_default,90,14,6,
	{22,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,1,2,10},
	
	{MON_UDONGE,15,1973,name_infor("���̼�",true),&img_mons_default,110,4,16,
	{30,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE,2,1,10},
	
	{MON_KAGUYA,18,3437,name_infor("ī����",false),&img_mons_default,202,20,1,
	{40,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_FLY | M_FLAG_UNIQUE | M_FLAG_SPEAK,3,1,10},
	
	{MON_MOKOU,16,2735,name_infor("���ڿ�",false),&img_mons_default,180,6,15,
	{50,0,0},{ATT_FIRE,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_UNIQUE | M_FLAG_SPEAK,2,1,10},
	
	{MON_NESI,15,1604,name_infor("�׽�",false),&img_mons_default,120,9,9,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_CAN_SEE_INVI | M_FLAG_SWIM,99,1,10},
	
	{MON_SANGHAI,15,1,name_infor("���� ����",true),&img_mons_default,80,5,22,
	{36,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_PASSED_ALLY,99,1,7},
	
	{MON_HOURAI,15,1,name_infor("���� ����",true),&img_mons_default,120,20,2,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY ,99,1,10},
	
	{MON_FAKE_SANGHAI,9,1,name_infor("���� ���� ����",true),&img_mons_default,40,5,17,
	{18,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_PASSED_ALLY,99,1,7},
	
	{MON_FAKE_HOURAI,9,1,name_infor("���� ���� ����",true),&img_mons_default,80,15,2,
	{2,0,0},{ATT_NORMAL,ATT_NONE,ATT_NONE},{name_infor("����",true),name_infor(),name_infor()},
	M_FLAG_NO_ATK | M_FLAG_OPEN_DOOR | M_FLAG_CAN_SEE_INVI | M_FLAG_LEADER_SUMMON | M_FLAG_PASSED_ALLY ,99,1,10}

};