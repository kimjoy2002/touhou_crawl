//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: god.cpp
//
// ����: �Ű���
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"
#include "god.h"
#include "key.h"
#include "skill_use.h"
#include "mon_infor.h"
#include "potion.h"
#include "rect.h"
#include "floor.h"
#include "tensi.h"
#include "swako.h"
#include "note.h"
#include "rand_shuffle.h"
#include "seija.h"
#include "lilly.h"
#include "tribe.h"


extern HANDLE mutx;

const char* GetGodString(god_type god)
{
	switch(god)
	{
	case GT_ERROR:
		return "�˼����½�";
	case GT_NONE:
		return "";
	case GT_JOON_AND_SION:
		return "�ҿ�&�ÿ�";
	case GT_BYAKUREN:
		return "����";
	case GT_KANAKO:
		return "ī����";
	case GT_SUWAKO:
		return "������";
	case GT_MINORIKO:
		return "�̳븮��";
	case GT_MIMA:
		return "�̸�";
	case GT_SHINKI:
		return "��Ű";
	case GT_YUUGI:
		return "�����";
	case GT_SHIZUHA:
		return "������";
	case GT_HINA:
		return "����";
	case GT_YUKARI:
		return "��ī��";
	case GT_EIRIN:
		return "���̸�";
	case GT_YUYUKO:
		return "������";
	case GT_SATORI:
		return "���丮";
	case GT_TENSI:
		return "�ٽ�";
	case GT_SEIJA:
		return "������";
	case GT_LILLY:
		return "����";
	case GT_MIKO:
		return "����";
	case GT_OKINA:
		return "��Ű��";
	case GT_JUNKO:
		return "��ȣ";
	}
	return "��";
}
bool GetGodString_is(god_type god)
{
	switch(god)
	{
	case GT_ERROR:
		return true;
	case GT_NONE:
		return true;
	case GT_JOON_AND_SION:
		return true;
	case GT_BYAKUREN:
		return true;
	case GT_KANAKO:
		return false;
	case GT_SUWAKO:
		return false;
	case GT_MINORIKO:
		return false;
	case GT_MIMA:
		return false;
	case GT_SHINKI:
		return false;
	case GT_YUUGI:
		return false;
	case GT_SHIZUHA:
		return false;
	case GT_HINA:
		return false;
	case GT_YUKARI:
		return false;
	case GT_EIRIN:
		return true;
	case GT_YUYUKO:
		return false;
	case GT_SATORI:
		return false;
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		return false;
	case GT_LILLY:
		return false;
	case GT_MIKO:
		return false;
	case GT_OKINA:
		return false;
	case GT_JUNKO:
		return false;
	}
	return true;
}


int GetGodAbandonValue(god_type god)
{
	return 25;
}

int getPietyPercent(int type, int strong) {
	int percen_ = randA(99);

	switch(type)
	{
	default:
	case 0: //randA(2) 66%
		switch(strong)
		{
		default:
		case 1: return percen_<33 ?1:0;
		case 2: return percen_<50 ? 1 : 0;
		case 3: return percen_<75 ? 1 : 0;
		case 4: return percen_<90 ? 1 : 0;
		case 5: return percen_<100 ? 1 : 0;
		}
	case 1: //50%
		switch (strong)
		{
		default:
		case 1: return percen_<25 ? 1 : 0;
		case 2: return percen_<35 ? 1 : 0;
		case 3: return percen_<66 ? 1 : 0;
		case 4: return percen_<75 ? 1 : 0;
		case 5: return percen_<100 ? 1 : 0;
		}

	case 2: //25%
		switch (strong)
		{
		default:
		case 1: return percen_<10 ? 1 : 0;
		case 2: return percen_<20 ? 1 : 0;
		case 3: return percen_<40 ? 1 : 0;
		case 4: return percen_<60 ? 1 : 0;
		case 5: return percen_<100 ? 1 : 0;
		}
	case 3: //���� ����
		switch (strong)
		{
		default:
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 4;
		case 5: return 10;
		}
	}
	return 1;
}

int pietyLevel(int piety)
{
	if(piety<30)
		return 0;
	else if(piety<50)
		return 1;
	else if(piety<75)
		return 2;
	else if(piety<100)
		return 3;
	else if(piety<120)
		return 4;
	else if(piety<160)
		return 5;
	else 
		return 6;
}


bool GetGodAbility(int level, bool plus)
{
	switch(you.god)
	{
	case GT_ERROR:
		return false;
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
		switch (level)
		{
		case 0:
			if (plus)
				printlog("����� �����Ű� ������ ���ַ� �Ҹ�ǰ�� �����ϸ� �Ҿ������.", true, false, false, CL_joon_and_sion);
			break;
		case 1:
			you.Ability(SKL_JOON_AND_SION_1, true, !plus);
			if (plus)
				printlog("����� ���� �ҿ��̳� �ÿ��� ������ �� �ִ�.", true, false, false, CL_joon_and_sion);
			else
				printlog("�� �̻� ����� ���� �ҿ��̳� �ÿ��� ������ �� ����.", true, false, false, CL_joon_and_sion);
			break;
		case 2:
			if (plus)
				printlog("���ǻ��¿��� ���ǵ� �ſ� ���� �Ŀ��� �̿��� ȿ���� ��� �ȴ�.", true, false, false, CL_joon_and_sion);
			else
				printlog("�� �̻� ���ǻ��¿��� �Ŀ��� �̿��� ȿ���� ���� �� ����.", true, false, false, CL_joon_and_sion);
			break;
		case 4:
			if (plus)
				printlog("���ǻ��¿��� ���ǵ� �ſ� ���� �Ҹ�ǰ�� �̿��� ȿ���� ��� �ȴ�.", true, false, false, CL_joon_and_sion);
			else
				printlog("�� �̻� ���ǻ��¿��� �Ҹ�ǰ�� �̿��� ȿ���� ���� �� ����.", true, false, false, CL_joon_and_sion);
			break;
		case 5:
			if (plus)
			{
				printlog("�����Ҷ����� �ѹ��� ���ǵ� ���� �ʻ�⸦ ����� �� �ִ�.", true, false, false, CL_joon_and_sion);
				if (you.god_value[GT_JOON_AND_SION][0] == 1)
					you.Ability(SKL_JOON_AND_SION_2, true, !plus);
				else if (you.god_value[GT_JOON_AND_SION][0] == 2)
					you.Ability(SKL_JOON_AND_SION_3, true, !plus);
			}
			else
				printlog("�� �̻� ���ǵ� ���� �ʻ�⸦ ����� �� ����.", true, false, false, CL_joon_and_sion);
			break;
		case 6:
			if (you.god_value[GT_JOON_AND_SION][0] != 0)
				you.Ability(SKL_JOON_AND_SION_4, true, !plus);
			if (plus)
				printlog("���� ����� ������ �̱� �� �ִ� �����־��� ������ ����� �� �ִ�.", true, false, false, CL_joon_and_sion);
			else
				printlog("�� �̻� �����־��� ������ ����� �� ����.", true, false, false, CL_joon_and_sion);
			break;
		}
		return false;
	case GT_BYAKUREN:
		switch(level)
		{
		case 1:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog("�������� ����� ��� �� �ִ� �������� �Ѱ踦 �÷��ش�.",true,false,false,CL_white_blue);
			else
				printlog("�� �̻� ����� ��� �� �ִ� �������� �Ѱ踦 �÷������ʴ´�.",true,false,false,CL_white_blue);
			break;
		case 2:
			you.remainSpellPoiont+=plus;
			you.Ability(SKL_BYAKUREN_1,true,!plus);
			if(plus)
				printlog("����� ���������� ������ ��ȭ��ų �� �ִ�.",true,false,false,CL_white_blue);
			else
				printlog("�� �̻� �������� ���°�ȭ�� ����� �� ����.",true,false,false,CL_white_blue);
			break;
		case 3:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog("����� ���� ��ȭ�� �ٷ����� ���� �����г�Ƽ�� ������������ �����Ѵ�.",true,false,false,CL_white_blue);
			else
				printlog("���̻� �ٷ°�ȭ�� �ູ�� ���� ���Ѵ�.",true,false,false,CL_white_blue);
			break;
		case 4:
			you.remainSpellPoiont+=plus;
			if(plus)
				printlog("�������� ���� ����� ��ȭ�������� �������ش�.",true,false,false,CL_white_blue);
			else
				printlog("�� �̻� ��ȭ�������� �������� ���Ѵ�.",true,false,false,CL_white_blue);
			break;
		case 5:
			you.remainSpellPoiont+=plus;
			you.Ability(SKL_BYAKUREN_2,true,!plus);
			if(plus)
				printlog("����� ���� �������� �ູ���� ���ΰ��� �������� �޸� �� �ְ� �ȴ�.",true,false,false,CL_white_blue);
			else
				printlog("���̻� ���ΰ��� ������ ����� �� ����.",true,false,false,CL_white_blue);
			break;
		}
		return false;
	case GT_KANAKO:
		switch(level)
		{
		case 1:
			you.Ability(SKL_KANAKO_1,true,!plus);
			if(plus)
				printlog("����� ���������� ��뿡�� ������ �� �ִ�.",true,false,false,CL_help);
			else
				printlog("�� �̻� �������� ������ ����� �� ����.",true,false,false,CL_help);
			break;
		case 3:
			you.Ability(SKL_KANAKO_2,true,!plus);
			if(plus)
				printlog("����� ����� ��ȯ �� �� �ִ�.",true,false,false,CL_help);
			else
				printlog("�� �̻� ����� ��ȯ �� �� ����.",true,false,false,CL_help);
			break;
		case 5:
			you.Ability(SKL_KANAKO_3,true,!plus);
			if(plus)
				printlog("����� ���� �ٶ��� ���� ������ �� �� �ִ�.",true,false,false,CL_help);
			else
				printlog("�� �̻� �ٶ��� ���� ������ �� ����.",true,false,false,CL_help);
			break;
		}
		return false;
	case GT_SUWAKO:
		switch(level)
		{
		case 0:
			if(you.suwako_meet == 0)
			{
				you.god_value[GT_SUWAKO][0] = randA(SWAKO_1_LAST-1);
				you.god_value[GT_SUWAKO][1] = randA(SWAKO_2_LAST-1);
				you.god_value[GT_SUWAKO][2] = randA(SWAKO_3_LAST-1);
				you.god_value[GT_SUWAKO][3] = randA(SWAKO_4_LAST-1);
				you.god_value[GT_SUWAKO][4] = randA(SWAKO_5_LAST-1);
				you.suwako_meet = 1;
			}
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			GetSwakoAbility(level,plus);
			break;
		}
		return false;
	case GT_MINORIKO:
		switch(level)
		{
		case 1:
			if(plus)
				printlog("����� �Ŀ��� �������� ü�°� ����ȸ���ӵ��� ��������.",true,false,false,CL_warning);
			else
				printlog("�� �̻� ü�°� ����ȸ���ӵ��� ���������ʴ´�.",true,false,false,CL_warning);
			break;
		case 2:
			you.Ability(SKL_MINORIKO_1,true,!plus);
			if(plus)
				printlog("����� ���� �����̻�� �ɷ�ġ���ϸ� ȸ���� �� �ִ�.",true,false,false,CL_warning);
			else
				printlog("�� �̻� �����̻�� �ɷ�ġ���ϸ� ȸ���� �� ����.",true,false,false,CL_warning);
			break;
		case 3:
			if(plus)
				printlog("����� ���� ������ ���� ���� �� �ְ� ������ ���� ȸ���Ѵ�.",true,false,false,CL_warning);
			else
				printlog("�� �̻� ������ ���� ���� ���Ѵ�.",true,false,false,CL_warning);
			break;
		case 4:
			you.Ability(SKL_MINORIKO_2,true,!plus);
			if(plus)
				printlog("����� ���� ���İ� P�� �Ҹ��Ͽ� ü���� ũ�� ȸ���� �� �ִ�.",true,false,false,CL_warning);
			else
				printlog("�� �̻� �������� ü���� ȸ���� �� ����.",true,false,false,CL_warning);
			break;
		case 5:
			//if(you.power>=500)
			//{			
			//	you.ResistUpDown(plus,RST_FIRE);
			//	you.ResistUpDown(plus,RST_ICE);
			//}
			if(plus)
				printlog("����� ���� ������ ���� ���� ȭ���� �ñ⿡ ��������.",true,false,false,CL_warning);
			else
				printlog("�� �̻� ������ �Ծ ȭ���� �ñ⿡ �������ʴ�.",true,false,false,CL_warning);
			break;
		}
		return false;
	case GT_MIMA:
		switch(level)
		{
			case 0:
				you.max_mp+=plus;
				if(plus)
					printlog("����� �ִ뿵���� �žӽɿ� ����ؼ� �����Ѵ�.",true,false,false,CL_green);
				else
					printlog("����� �ִ뿵���� �����ߴ�.",true,false,false,CL_green);
				break;
			case 1:
				you.max_mp+=plus;
				if(plus)
					printlog("����� ���� �׿����� ������ ��´�.",true,false,false,CL_green);
				else
					printlog("�� �̻� ���� �׿����� ������ ���� ���Ѵ�.",true,false,false,CL_green);
				break;
			case 2:
				you.max_mp+=plus;
				if(plus)
					printlog("�̸��� ���� �ı����� �� ������ ������ �����Ѵ�.",true,false,false,CL_green);
				else
					printlog("�� �̻� �ı��� ������ �������� ���Ѵ�.",true,false,false,CL_green);
				break;
			case 3:
				mima_gift(BOOK_CONJURE);
				you.max_mp+=plus;
				break;
			case 4:
				you.max_mp+=plus;
				if(plus)
					printlog("�̸��� ���� �ı����� �� ������ �������� �÷��ش�.",true,false,false,CL_green);
				else
					printlog("�� �̻� �ı��� �������� �������� ���Ѵ�.",true,false,false,CL_green);
				break;
			case 5:
				mima_gift(BOOK_TEST_ANNIHILATE);
				you.max_mp+=plus;
				break;
			case 6:
				you.max_mp+=plus;
				break;
		}
		return false;
	case GT_SHINKI:
		switch(level)
		{
			case 1:
				you.Ability(SKL_SHINKI_1,true,!plus);
				if(plus)
					printlog("����� �ϱ� ������ ���� ������ ��ȯ�� �� �ִ�.",true,false,false,CL_white_puple);
				else
					printlog("�� �̻� �ϱ� ������ ���� ������ ��ȯ�� �� ����.",true,false,false,CL_white_puple);
				break;
			case 2:
				you.Ability(SKL_SHINKI_2,true,!plus);
				if(plus)
					printlog("����� ������ �������� ��Ű�� �߱� ������ ��ȯ�� �� �ִ�.",true,false,false,CL_white_puple);
				else
					printlog("�� �̻� �߱� ������ ��ȯ�� �� ����.",true,false,false,CL_white_puple);
				break;
			case 3:
				if(plus)
					printlog("��Ű�� ����� �������� ��ȯ���κ��� �����ش�.",true,false,false,CL_white_puple);
				else
					printlog("�� �̻� �������� ��ȯ���κ��� ��ȣ���� ���Ѵ�.",true,false,false,CL_white_puple);
				break;
			case 4:
				you.Ability(SKL_SHINKI_3,true,!plus);
				if(plus)
					printlog("����� ������ �������� ��Ű�� ��� ������ ��ȯ�� �� �ִ�.",true,false,false,CL_white_puple);
				else
					printlog("�� �̻� ��� ������ ��ȯ�� �� ����.",true,false,false,CL_white_puple);
				break;
			case 5:
				if(plus)
					printlog("���� ����� P�κ��� ���� ��´�.",true,false,false,CL_white_puple);
				else
					printlog("�� �̻� P�κ��� ���� ���� ���Ѵ�.",true,false,false,CL_white_puple);
				break;
		}
		return false;
	case GT_YUUGI:
		switch(level)
		{
		case 0:
			if(plus)
				printlog("����� �������� �� ���� �� �ִ�.",true,false,false,CL_yuigi);
			else
				printlog("�� �̻� ���ص� ������ ���Ѵ�.",true,false,false,CL_yuigi);
			break;
		case 1:
			you.Ability(SKL_YUUGI_1,true,!plus);
			if(plus)
				printlog("����� ������ ���� �ٲ� ���� �� �ִ�.",true,false,false,CL_yuigi);
			else
				printlog("�� �̻� ������ ���� �ٲ� ���� �� ����.",true,false,false,CL_yuigi);
			break;
		case 2:
			you.Ability(SKL_YUUGI_2,true,!plus);
			if(plus)
				printlog("����� ������ ���� ���÷����� �� �� �ִ�.",true,false,false,CL_yuigi);
			else
				printlog("�� �̻� ������ ���� ���÷����� �� �� ����.",true,false,false,CL_yuigi);
			break;
		case 3:
			you.Ability(SKL_YUUGI_3,true,!plus);
			if(plus)
				printlog("����� ���� ���� ���� �� �ִ�.",true,false,false,CL_yuigi);
			else
				printlog("�� �̻� ���� ���� ���� �� ����.",true,false,false,CL_yuigi);
			break;
		case 4:
			you.Ability(SKL_YUUGI_4,true,!plus);
			if(plus)
				printlog("����� ������ ��ȿ�� ��ĥ �� �ִ�.",true,false,false,CL_yuigi);
			else
				printlog("�� �̻� ��ȿ�� �� ����.",true,false,false,CL_yuigi);
			break;
		case 5:
			you.Ability(SKL_YUUGI_5,true,!plus);
			if(plus)
				printlog("����� ���� �ﺸ�ʻ��� ����� �� �ִ�.",true,false,false,CL_yuigi);
			else
				printlog("�� �̻� �ﺸ�ʻ��� ����� �� ����.",true,false,false,CL_yuigi);
			break;
		}
		return false;
	case GT_SHIZUHA:
		switch(level)
		{
			case 0:
				if(plus)
					printlog("�����ϴ� �ῡ�� �� ������ ��ġ�� Ȯ���� ũ�� �ٿ��ش�.",true,false,false,CL_autumn);
				else
					printlog("�� �̻� �����ϴ� ���� ��ħ�� �ٿ����� �ʴ´�.",true,false,false,CL_autumn);
				break;
			case 1:
				if(plus)
					printlog("����� �����ϰ� ������ �� �ִ� ��ǳ�� �����븦 �����.",true,false,false,CL_autumn);
				else
					printlog("�� �̻� ����� �����뿡 ��ǳ�� ������ ���Ѵ�.",true,false,false,CL_autumn);
				break;
			case 2:
				you.Ability(SKL_SIZUHA_1,true,!plus);
				if(plus)
					printlog("����� ��ǳ���� �ִ� ���͵鿡�� ȥ���� �� �� �ִ�.",true,false,false,CL_autumn);
				else
					printlog("�� �̻� ����� ��ǳ���� ���͵鿡�� ȥ���� �� �� ����.",true,false,false,CL_autumn);
				break;
			case 3:
				you.Ability(SKL_SIZUHA_2,true,!plus);
				if(plus)
					printlog("����� �����ִ� ���� ��ǳ ���� ���� �� �ִ�.",true,false,false,CL_autumn);
				else
					printlog("�� �̻� ����� �����ִ� ���� ��ǳ ���� ���� �� ����.",true,false,false,CL_autumn);
				break;
			case 4:
				if(plus)
					printlog("����� ��ǳ ���� ������ �ſ� ������ ������ �� �ִ�.",true,false,false,CL_autumn);
				else
					printlog("�� �̻� ����� ��ǳ ������ ������ ������ �� ����.",true,false,false,CL_autumn);
				break;
			case 6:
				if(you.god_value[GT_SHIZUHA][0]==0)
				{
					you.Ability(SKL_SIZUHA_3,true,!plus);
					if(plus)
						printlog("����� �� �ѹ� ����� ���⿡ ��ǳ�� ���� �Ҿ���� �� �ִ�.",true,false,false,CL_autumn);
					else
						printlog("�� �̻� ����� ����� ���⿡ ��ǳ�� ���� �Ҿ���� �� ����.",true,false,false,CL_autumn);
				}
				break;
		}
		return false;
	case GT_HINA:
		
		switch(level)
		{
		case 0:			
			if(plus)
			{
				for(list<item>::iterator it = you.item_list.begin(); it != you.item_list.end() ; it++)
				{
					it->identify_curse = true;
				}
				printlog("����� ���� �������� ���ָ� Ž���� �� �ִ�.",true,false,false,CL_hina);
			}
			break;
		case 1:
			you.Ability(SKL_HINA_1,true,!plus);
			if(plus)
				printlog("����� ���ְɸ� �������� ���̳ʽ� ��æƮ�� �÷����� �ٲ� �� �ִ�.",true,false,false,CL_hina);
			else
				printlog("�� �̻� ���ְɸ� �������� ��æƮ�� ������ �� ����.",true,false,false,CL_hina);
			break;
		case 2:
			you.Ability(SKL_HINA_2,true,!plus);
			if(plus)
				printlog("����� ���⿡ ���ָ� �ɾ ������ ���� ���� �� �ִ�.",true,false,false,CL_hina);
			else
				printlog("�� �̻� ���⿡ ���ָ� �ɾ ���� ���� �� ����.",true,false,false,CL_hina);
			break;
		case 3:
			you.Ability(SKL_HINA_3,true,!plus);
			if(plus)
				printlog("����� ���� ���ָ� �ɾ ��� �������� �ݻ��ų �� �ִ�.",true,false,false,CL_hina);
			else
				printlog("�� �̻� ���� ���ָ� �ɾ �������� �ݻ��ų �� ����.",true,false,false,CL_hina);
			break;
		case 4:
			you.Ability(SKL_HINA_4,true,!plus);
			if(plus)
				printlog("����� ��ű��� ���ָ� �ɾ ü�°� ������ ȸ���� �� �ִ�.",true,false,false,CL_hina);
			else
				printlog("�� �̻� ��ű��� ���ָ� �ɾ ü�°� ������ ȸ���� �� ����.",true,false,false,CL_hina);
			break;
		case 5:
			if(plus)
				printlog("����� ���� ���ָ� ��Ѹ��� �ٴѴ�.",true,false,false,CL_hina);
			else
				printlog("�� �̻� ���ָ� ��Ѹ��� �ٴ��� �ʴ´�.",true,false,false,CL_hina);
			break;
		case 6:
			if(you.god_value[GT_HINA][0]==0)
			{
				you.Ability(SKL_HINA_5,true,!plus);
				if(plus)
					printlog("����� �� �ѹ� ����� ���⿡ ������ ���� �Ҿ���� �� �ִ�.",true,false,false,CL_hina);
				else
					printlog("�� �̻� ����� ����� ���⿡ ������ ���� �Ҿ���� �� ����.",true,false,false,CL_hina);
			}
			break;
		}
		return false;
	case GT_YUKARI:
		switch(level)
		{
		case 1:
			if(plus)
				printlog("����� ���� �������� ������ ���� �����̵��ȴ�.",true,false,false,CL_yukari);
			else
				printlog("�� �̻� �������� ������ �����̵����� �ʴ´�.",true,false,false,CL_yukari);
			break;
		case 2:
			you.Ability(SKL_YUKARI_1,true,!plus);
			if(plus)
				printlog("����� ���κ��� ��������� ��û�� �� �ִ�.",true,false,false,CL_yukari);
			else
				printlog("�� �̻� ��������� ��û�� �� ����.",true,false,false,CL_yukari);
			break;
		case 3:
			you.Ability(SKL_YUKARI_2,true,!plus);
			if(plus)
				printlog("����� ��踦 Ÿ�� �̵��� �� �ִ�.",true,false,false,CL_yukari);
			else
				printlog("�� �̻� ��踦 Ÿ�� �̵��� �� ����.",true,false,false,CL_yukari);
			break;
		case 4:
			you.Ability(SKL_YUKARI_3,true,!plus);
			if(plus)
				printlog("����� ��踦 ���� �� �ִ�.",true,false,false,CL_yukari);
			else
				printlog("�� �̻� ��踦 ���� �� ����.",true,false,false,CL_yukari);
			break;
		case 5:
			you.Ability(SKL_YUKARI_4,true,!plus);
			if(plus)
				printlog("����� ������ ������ų �� �ִ�.",true,false,false,CL_yukari);
			else
				printlog("�� �̻� ������ ������ų �� ����.",true,false,false,CL_yukari);
			break;
		}
		return false;
	case GT_EIRIN:
		switch(level)
		{
		case 0:
			if(plus)
			{
				printlog("���̸��� �����ۿ��� �÷��ش�. �������������� �⵵�Ͽ� ���۹����� ���� �� �ִ�.",true,false,false,CL_small_danger);
				iden_list.potion_list[PT_POISON].iden = true;
				iden_list.potion_list[PT_DOWN_STAT].iden = true;
				iden_list.potion_list[PT_CONFUSE].iden = true;
				iden_list.potion_list[PT_SLOW].iden = true;
				iden_list.potion_list[PT_PARALYSIS].iden = true;
			}
			else
			{
				printlog("�� �̻� ������ �ۿ��� �÷����� �ʴ´�. ���̻� ���� ������ ���� �� ����.",true,false,false,CL_small_danger);
			}
			break;
		case 1:
			if(plus)
				printlog("����� �����࿡�� ���ο� ���� ��´�.",true,false,false,CL_small_danger);
			else
				printlog("�� �̻� �����࿡�� ���ο� ���� ���� �� ����.",true,false,false,CL_small_danger);
			break;
		case 2:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 1);
			you.Ability(SKL_EIRIN_0,true,!plus);
			if(plus)
				printlog("����� ������ ���� �� �ִ�. ���� �ɷ�ġ���ҹ��࿡�� ���ο� ���� ��´�.",true,false,false,CL_small_danger);
			else
				printlog("�� �̻� ������ ���� �� ����. �ɷ�ġ���ҹ��࿡�� ���ο� ���� ���� �� ����.",true,false,false,CL_small_danger);
			break;
		case 3:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 2);
			you.Ability(SKL_EIRIN_1,true,!plus);
			if(plus)
				printlog("����� ��ü������ �� �� �ִ�. ����� ���� ȥ�����࿡�� ���ο� ���� ��´�.",true,false,false,CL_small_danger);
			else
				printlog("�� �̻� ��ü������ �� �� ����. �� �̻� ȥ�����࿡�� ���ο� ���� ���� �� ����.",true,false,false,CL_small_danger);
			break;
		case 4:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 3);
			if(plus)
				printlog("����� ���ӹ��࿡�� ���ο� ���� ��´�.",true,false,false,CL_small_danger);
			else
				printlog("�� �̻� ���ӹ��࿡�� ���ο� ���� ���� �� ����.",true,false,false,CL_small_danger);
			break;
		case 5:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 4);
			you.Ability(SKL_EIRIN_2,true,!plus);
			if(plus)
				printlog("���� ��޼����� �����ϴ�. ���� ���񹰾࿡�� ���ο� ���� ��´�.",true,false,false,CL_small_danger);
			else
				printlog("���̻� ��޼����� �� �� ����. �� �̻� ���񹰾࿡�� ���ο� ���� ���� �� ����.",true,false,false,CL_small_danger);
			break;
		case 6:
			if(you.s_stat_boost)
				you.SetStatBoost(you.s_stat_boost, 5);
			break;
		}
		return false;
	case GT_YUYUKO:
		switch(level)
		{
		case 1:
			if(you.s_ghost == 0)
			{
				if(plus)
				{
					you.SetGhost(1);
				}
				you.Ability(SKL_YUYUKO_ON,true,plus);
				you.Ability(SKL_YUYUKO_OFF,true,!plus);

			}
			else
			{				
				if(!plus)
					you.SetGhost(0);
				you.Ability(SKL_YUYUKO_OFF,true,!plus);
				you.Ability(SKL_YUYUKO_ON,true,plus);
			}
			if(plus)
				printlog("��� �ֺ��� �׻� ������ �𿩵��.",true,false,false,CL_yuyuko);
			else
				printlog("�� �̻� ��� �ֺ��� ������ �𿩵��� �ʴ´�.",true,false,false,CL_yuyuko);
			break;
		case 2:
			you.Ability(SKL_YUYUKO_1,true,!plus);
			if(plus)
				printlog("������ ���ϴ� ������ �̵���ų �� �ִ�.",true,false,false,CL_yuyuko);
			else
				printlog("�� �̻� ������ �̵���ų �� ����.",true,false,false,CL_yuyuko);
			break;
		case 3:
			you.Ability(SKL_YUYUKO_2,true,!plus);
			if(plus)
				printlog("��õ��� ������ �󵵸� ������ų �� �ִ�.",true,false,false,CL_yuyuko);
			else
				printlog("�� �̻� ������ �󵵸� ������ų �� ����.",true,false,false,CL_yuyuko);
			break;
		case 5:
			you.Ability(SKL_YUYUKO_3,true,!plus);
			if(plus)
				printlog("�� �Ѹ��� ��ȥ�� �ӹ��� �� �ִ�.",true,false,false,CL_yuyuko);
			else
				printlog("�� �̻� ��ȥ�� �ӹ��� �� ����.",true,false,false,CL_yuyuko);
			break;
		}
		return false;
	case GT_SATORI:
		switch(level)
		{
		case 0:
			you.ResistUpDown(plus,RST_INVISIBLE);
			if(plus)
				printlog("����� ���� ������ ������ �� �ִ�.",true,false,false,CL_danger);
			else
				printlog("�� �̻� ������ ������ �� ����.",true,false,false,CL_danger);
			break;
		case 1:
			you.Ability(SKL_SATORI_1,true,!plus);
			if(plus)
				printlog("����� ������ Ʈ��츶�� ������ �� �ִ�.",true,false,false,CL_danger);
			else
				printlog("�� �̻� ������ Ʈ��츶�� ������ �� ����.",true,false,false,CL_danger);
			break;
		case 2:
			if(plus)
				printlog("����� �����κ��� ������ ����� �о �� �ִ�.",true,false,false,CL_danger);
			else
				printlog("�� �̻� �����κ��� ������ ����� ���� ���Ѵ�.",true,false,false,CL_danger);
			break;
		case 3:
			if(plus)
				printlog("����� �ֺ��� ���� ��ô�� ���� �� �ִ�.",true,false,false,CL_danger);
			else
				printlog("�� �̻� �ֺ��� ���� ��ô�� ���� �� ����.",true,false,false,CL_danger);
			break;
		case 4:
			you.Ability(SKL_SATORI_2,true,!plus);
			if(plus)
				printlog("����� ���� ������ �о �� �ִ�.",true,false,false,CL_danger);
			else
				printlog("�� �̻� ������ ���� �� ����.",true,false,false,CL_danger);
			break;
		case 5:
			if(plus)
				printlog("����� ���丮���� ������ ���� �޴� ������ �ֿϵ����̴�.",true,false,false,CL_danger);
			else
				printlog("�� �̻� ���丮���� ����� ���� ���������ʴ´�.",true,false,false,CL_danger);
			break;
		}
		return false;
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		if(level>=1 && level<=5) //������ ���� ��
		{			
			you.StatUpDown(plus?2:-2,STAT_STR);
			you.StatUpDown(plus?2:-2,STAT_INT);
			you.StatUpDown(plus?2:-2,STAT_DEX);
		}
		switch(level)
		{
		case 0:
		{
			you.Ability(SKL_SEIJA_GIFT, true, !plus);
			break;
		}
		case 2:
			if (plus) {
				printlog("�����ڴ� ����� ¡���κ����� ���ָ� ���´�.", true, false, false, CL_seija);
			}
			else {
				printlog("�����ڴ� �� �̻� ¡���κ��� ����� ���� �ʴ´�.", true, false, false, CL_seija);
			}
			break;
		case 3:
			you.Ability(SKL_SEIJA_1,true,!plus);
			if (plus) {
				printlog("����� ��ġ�� ������ �� �ִ�.", true, false, false, CL_seija);
			}
			else {
				printlog("�� �̻� ��ġ�� ������ �� ����.",true,false,false,CL_seija);
		    }
			break;
		case 5:
			you.Ability(SKL_SEIJA_2,true,!plus);
			you.Ability(SKL_SEIJA_GIFT, true, true);
			if(plus)
				printlog("����� ���� ����� �þ߸� ������ �� �ִ�.",true,false,false,CL_seija);
			else
				printlog("�� �̻� ����� �þ߸� ������ �� ����.",true,false,false,CL_seija);
			break;
		}
		return false;
	case GT_LILLY:
		switch(level)
		{
		case 1:
			you.Ability(SKL_LILLY_1,true,!plus);
			you.Ability(SKL_LILLY_2,true,!plus);
			if(plus)
				printlog("����� ���� �������� ����� ������ �� �ִ�.",true,false,false,CL_lilly);
			else
				printlog("�� �̻� ������ ����� ������ �� ����.",true,false,false,CL_lilly);
			if(plus)
				printlog("����� ���� �������� ��ó�� ȣ���� �� �ִ�.",true,false,false,CL_lilly);
			else
				printlog("�� �̻� ������ ȣ���� �� ����.",true,false,false,CL_lilly);
			break;
		case 2:
			you.Ability(SKL_LILLY_1,true,!plus);
			if(plus)
				printlog("����� ���� �Ѹ��� ������ �� ������ �� �ִ�.",true,false,false,CL_lilly);
			break;
		case 3:
			you.Ability(SKL_LILLY_1,true,!plus);
			you.Ability(SKL_LILLY_3,true,!plus);
			if(plus)
				printlog("����� ���� �Ѹ��� ������ �� ������ �� �ִ�.",true,false,false,CL_lilly);
			if(plus)
				printlog("����� ���� ������ ġ�� �� �� �ִ�.",true,false,false,CL_lilly);
			else
				printlog("�� �̻� ������ ġ�� �� �� ����.",true,false,false,CL_lilly);
			break;
		case 4:
			you.Ability(SKL_LILLY_1,true,!plus);
			if(plus)
				printlog("����� ���� �Ѹ��� ������ �� ������ �� �ִ�.",true,false,false,CL_lilly);
			break;
		case 5:
			you.Ability(SKL_LILLY_1,true,!plus);
			you.Ability(SKL_LILLY_4,true,!plus);
			if(plus)
				printlog("����� ������ ���ᰡ �� ������ ������ �� �ִ�.",true,false,false,CL_lilly);
			if(plus)
				printlog("����� ���� �Ͻ������� �ڽ��� ���� �����鿡�� ������ �� �ִ�.",true,false,false,CL_lilly);
			else
				printlog("�� �̻� ������������ ���� �� ����.",true,false,false,CL_lilly);
			break;
		}
		return false;
	case GT_MIKO:
		switch (level)
		{
		case 0:
			you.Ability(SKL_MIKO_1, true, !plus);
			you.Ability(SKL_MIKO_2, true, !plus);
			you.Ability(SKL_MIKO_3, true, !plus);
			you.Ability(SKL_MIKO_4, true, !plus);
			you.Ability(SKL_MIKO_5, true, !plus);
			you.Ability(SKL_MIKO_6, true, !plus);
			break;
		}
		return false;
	case GT_OKINA:
		switch (level)
		{
		case 0:
			if (plus)
				printlog("����� ���� ���� ��������� �ѳ���� ������ �� �ִ�.", true, false, false, CL_okina);
			else
				printlog("�� �̻� ���� ��������� �峪�� �� ����.", true, false, false, CL_okina);
			break;
		case 1:
			you.Ability(SKL_OKINA_1, true, !plus);
			if (plus)
				printlog("����� ���� ���ϴ� ���� ���� ���� �� �ִ�.", true, false, false, CL_okina);
			else
				printlog("�� �̻� ���� ����� �� �� ����.", true, false, false, CL_okina);
			break;
		case 2:
			you.Ability(SKL_OKINA_2, true, !plus);
			if (plus)
				printlog("����� ���� �ָ� ������ ���� ���� ������ �ݾ� ��� �� �ִ�.", true, false, false, CL_okina);
			else
				printlog("�� �̻� ���� ������ ���� �� ����.", true, false, false, CL_okina);
			break;
		case 3:
			you.Ability(SKL_OKINA_3, true, !plus);
			if (plus)
				printlog("����� ���� ���� �� �ڿ� �鵵� ����� �̵��� �� �ִ�.", true, false, false, CL_okina);
			else
				printlog("�� �̻� ���� ��ڿ� �鵵� ���� �� ����.", true, false, false, CL_okina);
			break;
		case 4:
			you.Ability(SKL_OKINA_4, true, !plus);
			if (plus)
				printlog("����� ���� ũ������ ���� ȣ���� �� �ִ�.", true, false, false, CL_okina);
			else
				printlog("�� �̻� ũ������ ���� ȣ���� �� ����.", true, false, false, CL_okina);
			break;
		case 5:
			you.Ability(SKL_OKINA_5, true, !plus);
			if (plus)
				printlog("����� ���� �� ���� ���� ���� ����ĥ �� �ִ�.", true, false, false, CL_okina);
			else
				printlog("�� �̻� �� ���� ������ ����ĥ �� ����.", true, false, false, CL_okina);
			break;
		}
		return false;
	case GT_JUNKO:
		switch (level)
		{
		case 1:
			you.Ability(SKL_JUNKO_1, true, !plus);
			if (plus)
				printlog("����� ���� �ܼ��� ź���� �� �� �ִ�.", true, false, false, CL_junko);
			else
				printlog("�� �̻� ����� �ܼ��� ź���� �� �� ����.", true, false, false, CL_junko);
			break;
		case 2:
			you.Ability(SKL_JUNKO_2, true, !plus);
			if (plus)
				printlog("����� ���� ������ ���� ���� �� �ִ�.", true, false, false, CL_junko);
			else
				printlog("�� �̻� ����� ������ ���� ���� �� ����.", true, false, false, CL_junko);
			break;
		case 4:
			you.Ability(SKL_JUNKO_3, true, !plus);
			if (plus)
				printlog("����� ���� ������ ���Ǹ� ���� �� �ִ�.", true, false, false, CL_junko);
			else
				printlog("�� �̻� ����� ������ ���Ǹ� ���� �� ����.", true, false, false, CL_junko);
			break;
		case 6:
			you.Ability(SKL_JUNKO_4, true, !plus);
			if (plus) {
				printlog("����� ���� ��ȭ�� �� �ִ�.", true, false, false, CL_junko);
				if (you.god_value[GT_JUNKO][0] == 0)
				{
					random_extraction<int> rand_;
					rand_.push(1);//��ų��ȭ
					rand_.push(2);//���׼�ȭ
					rand_.push(3);//���¼�ȭ
					rand_.push(4);//�Ŀ���ȭ
					if (you.char_name.name.compare("���ڿ�"))
						rand_.push(5); //�����ȭ
					rand_.push(6);//����ȭ
					rand_.push(7);//�ý��� ��ȭ 
					you.god_value[GT_JUNKO][0] = rand_.pop();
					you.god_value[GT_JUNKO][1] = rand_.pop();
					you.god_value[GT_JUNKO][2] = rand_.pop();
				}
				MoreWait();
			}
			else
				printlog("�� �̻� ����� ��ȭ�� �� ����.", true, false, false, CL_junko);
			break;
		}
		return false;
	}
	return false;
}

bool GodAccpect_KillMonster(monster* mon_, parent_type type_)
{
	switch(you.god)
	{
	case GT_ERROR:
		return false;
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //���϶�
				printlog("�ҿ°� �ÿ��� ���� ������ ��Ż�ϴ� ���� �⻵�ߴ�.", true, false, false, CL_joon_and_sion);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.GiftCount(1);
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_BYAKUREN:
		return false;
	case GT_KANAKO:
		if (type_ == PRT_PLAYER)
		{
			if (!mon_->isUserAlly())
			{ //���϶�
				printlog("ī���ڴ� ����� ����� �⻵�ߴ�.", true, false, false, CL_help);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.GiftCount(1);
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
			else
			{ //�Ʊ��϶�
				printlog("ī���ڴ� ����� �ൿ�� �г��ߴ�. ��ȸ�϶�!", true, false, false, CL_small_danger);
				you.PietyUpDown(-5);
				return true;
			}
		}
		return false;
	case GT_SUWAKO:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //���϶�
				printlog("�����ڴ� ����� ����� �⻵�ߴ�.", true, false, false, CL_swako);

				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
					}
				}
				if (!you.GetPunish(GT_SUWAKO) && pietyLevel(you.piety) >= 2)
				{
					switch (you.god_value[GT_SUWAKO][1])
					{
					case SWAKO_2_KILL_HP:
						if (randA(200) < you.piety)
						{
							printlog("ü���� ȸ���Ǿ���.", false, false, false, CL_normal);
							you.HpUpDown(randA_1(1 + mon_->level / 2), DR_EFFECT);
						}
						break;
					case SWAKO_2_KILL_MP:
						if (randA(120) < you.piety)
						{
							printlog("������ ȸ���Ǿ���.", false, false, false, CL_normal);
							you.MpUpDown(randA_1(1 + mon_->level / 4));
						}
						break;
					case SWAKO_2_KILL_POWER:
						if (randA(200) < you.piety)
						{
							printlog("�Ŀ��� ȸ���Ǿ���.", false, false, false, CL_normal);
							int value_ = rand_int(3, 5);
							value_ += randA(mon_->level / 4);
							you.PowUpDown(value_);
						}
						break;
					}
				}
				enterlog();
				return true;
			}
		}
		return false;
	case GT_MINORIKO:
		if(mon_->id == MON_LETTY)
		{
			if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
			{
				if(!mon_->isUserAlly())
				{ //���϶�
					printlog("�̳븮�ڴ� ����� ���·� ���ƴ�.\"�ٷ� �װž�!\"",true,false,false,CL_warning);
					you.PietyUpDown(5*isSprint()?5:1);
				}
			}
		}
		return false;
	case GT_MIMA:
		if (type_ == PRT_PLAYER)
		{
			if (!mon_->isUserAlly())
			{ //���϶�
				printlog("�̸��� ����� ����� �⻵�ߴ�.", false, false, false, CL_green);

				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(1, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				if (!you.GetPunish(GT_MIMA) && pietyLevel(you.piety) >= 1)
				{
					if (randA(120) < you.piety)
					{
						printlog("������ ȸ���Ǿ���.", false, false, false, CL_normal);
						you.MpUpDown(randA_1(1 + mon_->level / 3));
					}
				}
				enterlog();
				return return_;
			}
		}
		return false;
	case GT_SHINKI:
		return false;
	case GT_YUUGI:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //���϶�
				printlog("������ ����� �¸��� �⻵�ߴ�.", true, false, false, CL_yuigi);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_SHIZUHA:
		if(pietyLevel(you.piety) >=1)
		{
			rand_rect_iterator rit(mon_->position,2,2);
			int i = randA(1+pietyLevel(you.piety)); 
			for(;!rit.end() && i> 0;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y))
				{	
					int rand_ = randA(1);
					env[current_level].MakeFloorEffect(coord_def(rit->x,rit->y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,rand_int(20,30),&you);
				}
				i--;
			}
			int rand_ = randA(1);
			env[current_level].MakeFloorEffect(coord_def(you.position.x,you.position.y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,3+you.piety/20,&you);
			//�÷��̾� ��ġ���� ������ ��ǳ�� ��������.(�Ϻη� �߹ؿ� ��ǳ��� �÷��̸� ���ص��ǰ� �ϱ�����)
		}
		if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if(!mon_->isUserAlly())
			{ //���϶�
				if(mon_->id == MON_LETTY)
				{
					printlog("�����ϴ� �ڼ��� �ƴ�.\"�Ǹ���\"",true,false,false,CL_autumn);
					you.PietyUpDown(4);
				}
				else
					printlog("�����ϴ� ����� ���� ����ó�� ���������� ���� �⻵�ߴ�.",true,false,false,CL_autumn);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_HINA:
		return false;
	case GT_YUKARI:
		if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if(!mon_->isUserAlly())
			{ //���϶�
				printlog("��ī���� ����� ����� �⻵�ߴ�.",true,false,false,CL_yukari);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_EIRIN:
		if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if(!mon_->isUserAlly())
			{ //���϶�
				{
					bool return_ = false;
					for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
						if (getPietyPercent(2, mon_->SetStrong()))
						{
							you.GiftCount(1);
							you.PietyUpDown(1);
							return_ = true;
						}
					}
					if(return_)
						printlog("���̸��� ����� ���Կ� ������ ������.", true, false, false, CL_small_danger);
					return return_;
				}
			}
		}
		return false;
	case GT_YUYUKO:
		if(mon_->s_ghost)
		{
			if(you.god_value[GT_YUYUKO][0])
			{
				for(auto it = env[you.god_value[GT_YUYUKO][1]].mon_vector.begin();it != env[you.god_value[GT_YUYUKO][1]].mon_vector.end();it++)
				{
					if(it->isLive() && it->map_id == you.god_value[GT_YUYUKO][0])
					{
						it->summon_time = 0;
					}
				}
			}
				
			{
				monster *mon2_ = BaseSummon(mon_->id, -1, false, false,4,&you, mon_->position, SKD_OTHER, -1);
				if(mon2_)
				{

					mon2_->id = MON_ENSLAVE_GHOST;
					mon2_->name.name += "�� ��ȥ";
					mon2_->name.name_type = true;
					printarray(true,false,false,CL_normal,3,mon_->name.name.c_str(),mon_->name.name_do()," ����� ���ᰡ �Ǿ���.");
					you.god_value[GT_YUYUKO][0] = mon2_->map_id;
					you.god_value[GT_YUYUKO][1] = current_level;

					//����ȭ�Ǹ� �ñ�����1�ܰ�����
					if(mon2_->ice_resist<=2)
						mon2_->ice_resist++;
					//�������� �����.
					mon2_->poison_resist=1;
						
					//�׷��� ������ ��������.
					mon2_->LevelUpdown(-2);

					char temp[200];
					sprintf_s(temp,200,"%s%s�����ߴ�.",mon_->name.name.c_str(),mon_->name.name_to(true));
					AddNote(you.turn,CurrentLevelString(),temp,CL_yuyuko);
				}
			}
		}
		else if(type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if(!mon_->isUserAlly())
			{ //���϶�
				printlog("�����ڴ� ����� ����� �⻵�ߴ�.",true,false,false,CL_yuyuko);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_SATORI:
		you.GiftCount(1);
		return false;
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		return false;
	case GT_LILLY:
		return false;
	case GT_MIKO:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //���϶�
				int base = getPietyPercent(3, mon_->SetStrong());
				for (int i = 0; i < (isSprint() ? sprintMulti()*base : base); i++) {
					you.PietyUpDown(1);
				}
				return true;
			}
		}
	case GT_OKINA:
		if (type_ == PRT_PLAYER || type_ == PRT_ALLY)
		{
			if (!mon_->isUserAlly())
			{ //���϶�
				printlog("��Ű���� ����� ����� �⻵�ߴ�.", true, false, false, CL_okina);
				bool return_ = false;
				for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
					if (getPietyPercent(0, mon_->SetStrong()))
					{
						you.PietyUpDown(1);
						return_ = true;
					}
				}
				return return_;
			}
		}
		return false;
	case GT_JUNKO:
		if (!(mon_->flag & M_FLAG_SUMMON))
		{
			if (type_ == PRT_PLAYER)
			{
				if (!mon_->isUserAlly())
				{ //���϶�
					printlog("��ȣ�� ����� ����� �⻵�ߴ�.", true, false, false, CL_junko);
					bool return_ = false;
					for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
						if (getPietyPercent(2, mon_->SetStrong()))
						{
							you.GiftCount(1);
							you.PietyUpDown(1);
							return_ = true;
						}
					}
					return return_;
				}
			}
		}
		return false;
	}
	return false;
}
bool GodAccpect_Entering()
{
	switch(you.god)
	{
	case GT_MINORIKO:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MIMA:
	case GT_SHINKI:	
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
		return false;
	case GT_SEIJA:
		printlog(seija_talk(GT_NONE, 0),true,false,false,CL_seija);
		return true;
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_GetPitem()
{
	switch(you.god)
	{
	case GT_MINORIKO:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (randA(3))
			{
				you.GiftCount(1);
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		return return_;
	}
	case GT_ERROR:
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
	{
		if (you.god_value[GT_JOON_AND_SION][0] == 2 && !you.GetPunish(GT_JOON_AND_SION) && pietyLevel(you.piety) >= 2)
		{
			int hp_ = rand_int(you.GetMaxHp() * 6 / 100, you.GetMaxHp() * 10 / 100) + 1;
			printlog("P�κ��� ȸ���Ͽ���. ", false, false, false, CL_normal);
			you.HpUpDown(hp_, DR_EFFECT);
			return true;
		}
	}
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MIMA:
		return false;
	case GT_SHINKI:	
		if(1)
		{
			if(!you.GetPunish(GT_SHINKI) && pietyLevel(you.piety)>=5)
			{
				int hp_ = rand_int(you.GetMaxHp() *9/100,you.GetMaxHp() *18/100)+1;
				printlog("ȸ���Ǿ���. ",false,false,false,CL_normal);
				you.HpUpDown(hp_, DR_EFFECT);
				you.MpUpDown(randA_1(5));
			}
			bool return_ = false;
			for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
				{
					you.PietyUpDown(1);
					return_ = true;
				}
			}
			return return_;
		}
		break;
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_HPUpDown(int value_,damage_reason reason)
{
	switch(you.god)
	{
	case GT_MINORIKO:		
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
		break;
	case GT_SUWAKO:		
		if(!you.GetPunish(GT_SUWAKO) && pietyLevel(you.piety)>=2)
		{
			switch(you.god_value[GT_SUWAKO][1])
			{
			case SWAKO_2_DEAD_PROTECT:
				if(randA(9)<4 && you.GetHp() <= 0 && value_ < 0)
				{
					if(you.GetHp() -value_>0)
					{
						you.hp-=value_;
						printlog("��ȣ�Ǿ���!",false,false,false,CL_swako);
					}
				}
				break;
			}
		}
		break;
	case GT_MIMA:
	case GT_SHINKI:	
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
		break;
	case GT_YUKARI:
		if(pietyLevel(you.piety)>=1 && you.GetHp() > 0 && value_ < 0)
		{
			int percent_ = value_ *-100 / you.GetMaxHp();
			int a_ = 0;
			if(randA(percent_+a_)>=8+a_)
			{				
				int left_percent_ = you.GetHp() *-100 / you.GetMaxHp();
					
				if(percent_>=rand_int(25,50) && percent_>left_percent_)
				{
					you.Teleport();
					if(env[current_level].isInSight(you.position))
						printlog("����� �ణ ������ ��߳� ���� ��ġë��.",false,false,false,CL_normal);
					else
						printlog("���ڱ� ��� �ֺ��� ��ȭ�ߴ�.",false,false,false,CL_normal);
				}
				else
				{
					you.Blink(30);
				}
			}
		}
		break;
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}

bool GodAccpect_UseSpell(spell_list spell_)
{
	switch(you.god)
	{
	case GT_MINORIKO:		
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MIMA:
	case GT_SHINKI:
		return false;
	case GT_YUUGI:
		printlog("������ ����� ������ �г��ߴ�!",true,false,false,CL_small_danger);
		you.PietyUpDown(-5);
		return false;
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
		if(spell_ == SPL_BLINK || spell_ == SPL_TELEPORT_SELF)
		{			
			printlog("��ī���� ����� ������ ���̸��� ��뿡 �г��ߴ�!",true,false,false,CL_small_danger);
			you.PietyUpDown(-5);
			return false;
		}
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_BYAKUREN:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_Practice(int value, skill_type skill_)
{
	switch(you.god)
	{
	case GT_BYAKUREN:
		/*
		if(skill_ >= SKT_SPELLCASTING && skill_ <= SKT_ALCHEMY && value>randA(40))
		{
			bool return_ = false;
			for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
				{
					you.GiftCount(1);
					you.PietyUpDown(1);
					return_ = true;
				}
			}
			return return_;
		}*/
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_Stair(bool down_, bool new_dungeon_)
{

	switch (you.god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
		return false;
	case GT_MIKO:
	{
		if (new_dungeon_)
		{
			you.PietyUpDown(-200);
			if (down_ && env[current_level].popular == 1) {
				printlog("���ο� ������ �����ϸ鼭 ���ο� �α⵵�� �����Ѵ�.", true, false, false, CL_miko);
				you.PietyUpDown(60, true);
			}
			else {
				printlog("������ �ű�鼭 �α⵵�� �ʱ�ȭ�Ǿ���.", true, false, false, CL_miko);

			}
		}
		else if (down_)
		{
			printlog("���� �ű�鼭 �α⵵�� ���� ��������.", true, false, false, CL_miko);
			you.PietyUpDown(-10);
		}
		else
		{
			printlog("����� Ÿ�� �ö󰡸鼭 �α⵵�� ũ�� ��������", true, false, false, CL_miko);
			you.PietyUpDown(-30);
		}
	}
	break;
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;

}
bool GodAccpect_Explore_100()
{
	switch(you.god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
		return false;
	case GT_HINA:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (60 > randA(100))
			{
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		return return_;
	}
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
		return false;
	case GT_SATORI:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (50 > randA(100))
			{
				you.GiftCount(1);
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		return return_;
	}
	case GT_TENSI:
		if(20>randA(100))
		{//�ٽô� ������Ʈ�� ���?
			you.GiftCount(1);
		}
		return false;
	case GT_SEIJA:
		return false;
	case GT_LILLY:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (50 > randA(100))
			{
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		if (5 > randA(100))
		{
			random_extraction<int> rand_;
			rand_.push(0);
			rand_.push(1);
			rand_.push(2);
			rand_.push(3);
			rand_.push(4);
			for (int i = 0; i < 5; i++)
			{
				int next_ = rand_.pop();
				if (you.god_value[GT_LILLY][next_] == 1)
				{
					for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
					{
						if (it->isLive() && (*it).isUserAlly() && it->map_id == you.lilly_allys[next_].map_id && current_level == you.lilly_allys[next_].floor  &&  env[current_level].isInSight(coord_def(it->position.x, it->position.y)) && it->CanSpeak())
						{
							printlog(fairy_speak(&(*it), you.lilly_allys[next_].personality, FS_NORMAL), true, false, false, CL_normal);
							return true;
						}
					}
				}
			}

		}
		return return_;
	}
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_Exp_get()
{
	switch(you.god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
		return false;
	case GT_SEIJA:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) {
			if (randA(2))
			{
				you.GiftCount(1);
				return_ = true;
			}
		}
		return return_;
	}
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_First_contact()
{
	switch(you.god)
	{
	case GT_BYAKUREN:
	{
		bool return_ = false;
		for (int i = 0; i < (isSprint() ? sprintMulti() : 1); i++) 
		{
			if (randA(7) < 3)
			{
				you.GiftCount(1);
				you.PietyUpDown(1);
				return_ = true;
			}
		}
		return return_;
	}
	return false;
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
		return false;
	case GT_SATORI: //���丮�� �ٽô� ����?
		if(randA(1)==0)
		{
			you.GiftCount(1);
		}
		return false;
	case GT_TENSI:
		if(1)
		{
			if(randA_1(500)<you.CheckTension())
			{
				you.GiftCount(2);
			}
		}
		return false;
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_Abandon(god_type god)
{
	switch(god)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_SEIJA:
		return false;
	case GT_LILLY:		
		{
			int k = 0;
			for(int i = 0; i < 5; i++)
			{
				if(you.god_value[GT_LILLY][i] == 1)
				{
					for(auto it = env[you.lilly_allys[i].floor].mon_vector.begin(); it != env[you.lilly_allys[i].floor].mon_vector.end();it++)
					{
						if(it->isLive() && it->isUserAlly() && it->map_id == you.lilly_allys[i].map_id)
						{
							it->ReturnEnemy();
							k++;
							break;
						}
					}
				}

			}
			if(k>0)
			{
				printarray(true,false,false,CL_danger,1,"������ ����Ͽ� ��� ���� ������ ��ſ��� ���� ���ȴ�!");
			}
		}
		return false;
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
		return false;
	}
	return false;
}
bool GodAccpect_turn(int turn)
{
	if(you.GetPunish(GT_SHIZUHA))
	{
		if(turn>1 && you.prev_position != you.position)
		{
			int rand_ = randA(1);
			env[current_level].MakeFloorEffect(you.prev_position,&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,15,&you);
		}
	}




	switch(you.god)
	{
	case GT_ERROR:
		return false;
	case GT_NONE:
		return false;
	case GT_JOON_AND_SION:
		return false;
	case GT_BYAKUREN:
		return false;
	case GT_KANAKO:
		{		
			for(auto it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && it->GetId() == MON_ONBASIRA && it->isUserAlly() && distan_coord(you.position,it->position) <= 2)
				{
					you.SetSlaying(3);
				}
			}
		}
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SUWAKO:
		{	

			if(you.god == GT_SUWAKO && !you.GetPunish(GT_SUWAKO) && pietyLevel(you.piety)>=2 &&
			you.god_value[GT_SUWAKO][1] == SWAKO_2_SWIM)
			{
				auto tile_ = env[current_level].dgtile[you.position.x][you.position.y].tile;
				if(tile_ == DG_SEA)
					you.SetBuff(BUFFSTAT_EV,BUFF_SUWAKO,8,2);
				else
					you.SetBuff(BUFFSTAT_EV,BUFF_SUWAKO,0,2);
			}
		}
		return false;
	case GT_MINORIKO:
		{
			if(turn%3000 == 0)
			{
				you.PietyUpDown(-1);		
			}
		}
		return false;
	case GT_MIMA:
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SHINKI:
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_YUUGI:
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SHIZUHA:
		{
			if(pietyLevel(you.piety) >=1 && turn>1 && you.prev_position != you.position)
			{
				int rand_ = randA(1);
				env[current_level].MakeFloorEffect(you.prev_position,&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,4+you.piety/10,&you);
			}
			if(turn%2000 == 0)
			{
				you.PietyUpDown(-1);		
			}
		}
		return false;
	case GT_HINA:
		if(pietyLevel(you.piety) >= 5 && !you.GetPunish(GT_HINA))
		{
			int curse_ = 0;
			
			for(equip_type i = ET_FIRST;i!=ET_LAST;i=(equip_type)(i+1))
			{
				if(you.equipment[i])
				{
					if(you.equipment[i]->curse)
						curse_++;
				}
			}
			if(randA(100)<80*curse_/ET_LAST)
			{
				dif_rect_iterator rit(you.position,4,true);
				while(!rit.end())
				{
					coord_def check_pos_ = (*rit);
					
					if(env[current_level].isMove(check_pos_.x, check_pos_.y, false) && env[current_level].isInSight(check_pos_) && you.isSightnonblocked((*rit)))
					{
						env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_CURSE,rand_int(6,8),0,&you);
						break;
					}
					rit++;
				}
			}
		}
		return false;
	case GT_YUKARI:
		if(turn%10 == 0)
		{
			if(1/*randA(100)<20pietyLevel(you.piety) >=1*/)
			{
				dif_rect_iterator rit(you.position,8,true);
				while(!rit.end())
				{
					coord_def check_pos_ = (*rit);

					if(you.s_dimension)
					{
						if(abs(you.god_value[GT_YUKARI][0] - check_pos_.x)>8)
							check_pos_.x += (you.god_value[GT_YUKARI][0] - check_pos_.x)>0?17:-17;
						if(abs(you.god_value[GT_YUKARI][1] - check_pos_.y)>8)
							check_pos_.y += (you.god_value[GT_YUKARI][1] - check_pos_.y)>0?17:-17;
					}


					if(env[current_level].isMove(check_pos_.x, check_pos_.y, false) && env[current_level].isInSight(check_pos_) && you.isSightnonblocked((*rit)))
					{
						textures* t_ = &img_effect_schema[randA(2)];
						env[current_level].MakeFloorEffect(coord_def(check_pos_.x,check_pos_.y),t_,t_,FLOORT_SCHEMA,rand_int(20,30),&you);
						break;
					}
					rit++;
				}
			}
		}

		if(turn%3000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_EIRIN:
		if(turn%4500 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_YUYUKO:
		if(turn%3 == 0)
		{
			if(you.s_ghost && randA(100)<(you.s_ghost>=2?85:5+you.piety/8))
			{
				coord_def c_ = you.position/*+coord_def(rand_int(-6,6),rand_int(-6,6))*/;
				monster *mon_ = BaseSummon(MON_GHOST, rand_int(20,30), false, true,4,&you, c_, SKD_OTHER, -1);
				if(mon_)
				{
					mon_->LevelUpdown(you.level-1,3.0f,1.5f);
					mon_->image = &img_mons_ghost[randA(2)];
				}
			}
		}
		if(turn%1000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_SATORI:
		if(turn%3000 == 0)
		{
			you.PietyUpDown(-1);		
		}
		return false;
	case GT_TENSI:
		if(turn%7 == 0)
		{
			if(randA(1000)<you.CheckTension())
			{
				you.GiftCount(2);
			}
			else if(randA(10)==0)
			{
				you.GiftCount(1);
			}
		}
		return false;
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
		return false;
	case GT_OKINA:
		if (turn % 1000 == 0)
		{
			you.PietyUpDown(-1);
		}
		return false;
	case GT_JUNKO:
		return false;
	}
	return false;
}



int satori_sight()
{
	return pietyLevel(you.piety)*2;
}


void Pray()
{
	if(you.god != GT_NONE)
	{	
		bool sacrifice = false;
		int num = 0;
		for(list<item>::iterator it = env[current_level].item_list.begin();it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++;
			if((*temp).position.x == you.position.x && (*temp).position.y == you.position.y)
			{
				sacrifice = (God_pray(temp))?true:sacrifice;
				num++;
			}
			else if(num)
				break;
		}
		if (!sacrifice) {
			if (you.GetPunish(you.god)) {
				printarray(true, false, false, CL_warning, 3, GetGodString(you.god), GetGodString_is(you.god)?"�� ":"�� ", "�ɱⰡ �����غ��δ�.");
			}
			if (!God_PraySpeak()) {
				printarray(true, false, false, CL_warning, 2, GetGodString(you.god),"���� ����� �⵵����.");
			}
		}
	}
	else
	{
		enterlog();
		dungeon_tile_type type = env[current_level].dgtile[you.position.x][you.position.y].tile;
		if(type == DG_TEMPLE_SUWAKO && isTutorial() && !you.s_poison)
		{
			printlog("�����ڴ� ���ߴ� : �������� �״´ٰ� ��¥ �״°� �ƴϾ�. ��� ����� ���������.",true,false,false,CL_warning);
			printlog("�����ڴ� ���ߴ� : �׷��� ũ���� ���迡�� �״� �͵� ���̶���! ������ ���� �糪��!",true,false,false,CL_warning);
			you.SetPoison(150, 150,true);
		}
		
		if(type >= DG_TEMPLE_FIRST && type <= DG_TEMPLE_LAST)
		{
			printlog("����� ���ܿ� �⵵�� ��ȴ�.",true,false,false,CL_warning);
			MoreWait();


			if(type != DG_TEMPLE_SATORI && you.GetPunish((god_type)(type-DG_TEMPLE_FIRST)))
			{
				printarray(true,false,false,CL_warning,3,GetGodString((god_type)(type-DG_TEMPLE_FIRST)),GetGodString_is((god_type)(type-DG_TEMPLE_FIRST))?"�� ":"�� ","���� ����� �뼭�����ʾҴ�.");


			}
			/*else if (type == DG_TEMPLE_MIKO)
			{
				printlog("�� ���� ����� �Ա��� �޾��ֱ⿣ ���� �ʹ� �ٻڴ�!.",true,false,false,CL_warning);
			}*/
			else
			{
				WaitForSingleObject(mutx, INFINITE);
				deletesub();
				SetDisplayTexture(&img_god_background[(type - DG_TEMPLE_FIRST)]);
				GodInfor((god_type)(type-DG_TEMPLE_FIRST));
				printsub("",true,CL_normal);
				printsub("",true,CL_normal);
				printsub("�ŵ��� �Ƿ��� YŰ��, ����Ϸ��� NŰ�� ������.",true,CL_help);
				changedisplay(DT_SUB_TEXT);
				ReleaseMutex(mutx);
				bool ok_= true;
				while(ok_)
				{			
					int select = waitkeyinput();
					switch(select)
					{
					default:
					case '?':
						break;
					case 'Y':
					case 'y':
						changedisplay(DT_GAME);
						SetDisplayTexture(NULL);
						you.Belief((god_type)(type-DG_TEMPLE_FIRST),15);
						MoreWait();
					case 'N':
					case 'n':
					case VK_ESCAPE:
						ok_ = false;
						break;
					}
				}
				changedisplay(DT_GAME);
				SetDisplayTexture(NULL);
			}
		}
		else
		{
			printlog("����� ���� �ǹ̿� ���� ��� �����ߴ�.",true,false,false,CL_warning);
		}

		//switch(type)
		//{
		//case DG_TEMPLE_SHIKIEIKI:
		//	printlog("��Ű����Ű�� ���ߴ� : �ִ��� ���� �� ������ �������� �������ּ���.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_BYAKUREN:
		//	printlog("������ ���ߴ� : �ƾ�, ũ���� ���� �ȿ� ���� ������.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_KANAKO:
		//	printlog("ī���ڴ� ���ߴ� : �̰��� �ž��� ���� ��ȸ�Դϴ�.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SUWAKO:
		//	if(isNormalGame() || you.s_poison)
		//	{
		//		printlog("�����ڴ� ���ߴ� : ������, ����־�����.",true,false,false,CL_warning);
		//	}
		//	else
		//	{
		//		printlog("�����ڴ� ���ߴ� : �������� �״´ٰ� ��¥ �״°� �ƴϾ�. ��� ����� ���������.",true,false,false,CL_warning);
		//		printlog("�����ڴ� ���ߴ� : �׷��� ũ���� ���迡�� �״� �͵� ���̶���! ������ ���� �糪��!",true,false,false,CL_warning);
		//		you.SetPoison(150,true);
		//	}
		//	break;
		//case DG_TEMPLE_MINORIKO:
		//	printlog("�̳븮�ڴ� ���ߴ� : ����Ž�赵 ���İ�!",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_MIMA:
		//	printlog("�̸��� ���ߴ� : ������� �ڰ��־��µ�, ��� �Ȱ���?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SHINKI:
		//	printlog("��Ű�� ���ߴ� : ���赵 �����̾�...",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_YUUGI:
		//	printlog("������ ���ߴ� : ���� �༮���� ���� ���ڴ°�!",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SHIZUHA:
		//	printlog("�� �鸮���ʴ� �ν����Ÿ��� �Ҹ��� �鸰��.",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_HINA:
		//	printlog("������ ���ߴ� : ���� ���ĳ�! �׶��� �ð��̾�!",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_YUKARI:
		//	printlog("��ī���� ���ߴ� : �� ſ�� �ƴ϶�?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_EIRIN:
		//	printlog("���̸��� ���ߴ� : ���� ���Ѵٸ�, ���� ������ᰡ �Ǵ°� �?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_YUYUKO:
		//	printlog("�����ڴ� ���ߴ� : �̿� �̷��� �Ȱ� ���� ���ݾ�?",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_SATORI:
		//	printlog("���丮�� ���ߴ� : �ֿϵ������� ���� �������...",true,false,false,CL_warning);
		//	break;
		//case DG_TEMPLE_TENSI:
		//	printlog("�ٽô� ��ģ���� ������.",true,false,false,CL_warning);
		//	break;
		//default:
		//	printlog("����� ���� �ǹ̿� ���� ��� �����ߴ�.",true,false,false,CL_warning);
		//	break;
		//}
	}
	you.time_delay += you.GetNormalDelay();
	you.TurnEnd();
	you.SetPrevAction('p');
}



void GodInfor(god_type god)
{
	printsub("                                                    �ž�",true,CL_normal);
	switch(god)
	{
	case GT_SUWAKO:
		printsub("�𸮾� ������ - �������� ����",true,CL_swako);
		printsub("",true,CL_normal);
		printsub("�����ڴ� ��(��)�� â���ϴ� �ɷ��� ���� �������̴�.",true,CL_normal);
		printsub("�����ڴ� ���ڵ鿡�� ���������� �Ǵ��� �ش�.",true,CL_normal);
		printsub("�� ������ ���ڵ��� �پ��� �Ǵ��� ���� �� ������ ���ϴ� �Ǵ��� ������ ���Ѵ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_MIMA:
		printsub("�̸� - �Ƶ��� �޿� ����� �ñ� ����",true,CL_green);
		printsub("",true,CL_normal);
		printsub("�̸��� ��ӽŰ��� ����� �Ƿ��̴�.",true,CL_normal);
		printsub("�ŵ����� �̸��� ������ ���� ������ ������ �ı� ������ �����ް� �����޴´�.",true,CL_normal);
		printsub("Ư�� �׳��� ����� �����ڰ� �Ǿ����� �ñ��� �ı� ������ ����ũ�� �����ްԵȴ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_YUYUKO:
		printsub("���̱����� ������ - ���´����� ���ɼҳ�",true,CL_yuyuko);
		printsub("",true,CL_normal);
		printsub("�����ڴ� ����翡 ��� ���̱������� �ư����̴�.",true,CL_normal);
		printsub("�׳�� ������ ���� �� �� �ִ� ������ �ɷ��� ������ �־ �ŵ��鿡�� ������ ���� �������ش�.",true,CL_normal);
		printsub("�׳��� �ŵ��� �Ǹ� ������ �ٷ�� �ɷ°� ���� ��ȥ���� ���� ���� ���̴�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_JOON_AND_SION:
		printsub("�丮���� �ҿ� & �ÿ� - �����־��� �ڸ�",true, CL_joon_and_sion);
		printsub("",true,CL_normal);
		printsub("����� ����� �ڸ� ������ �ϴ� ���ڿ��� �ҿ��� �������ش�.",true,CL_normal);
		printsub("�ҿ��� ����� �����Ű�� ������, �ÿ��� �ϴ� �ڸ� ����ϰ� ����� �������μ�",true,CL_normal);
		printsub("�ϴ� �͸����ε� �Ҹ�ǰ�� �����ϰ� �Ҿ������ ������ ����� �� ���̴�.",true,CL_normal);
		printsub("�׷����� ���� �ž��Ѵٸ� ���� �����ϴ� ������ ���������� �׳���� �Ǵɵ��� ����ϰ� �ȴ�.", true, CL_normal);
		printsub("�׳���� �Ǵ��� ����������, ���ǿ� ���ÿ� �׿� ���� �׳���� �ҿ ���� ���������̴�.", true, CL_normal);
		printsub("�ŵ����� �ٸ� ������ �׿��� �׵��� ���� �����ϴ� ������ �žӽ��� ���� �� �ִ�.", true, CL_normal);
		printsub("", true, CL_normal);
		break;
	case GT_SHINKI:
		printsub("��Ű - ������ ��",true,CL_white_puple);
		printsub("",true,CL_normal);
		printsub("��Ű�� ������ �������� ���踦 â���� ������ ���̴�.",true,CL_normal);
		printsub("â���� �ɷ��� �̿��ؼ� ��Ű�� �ŵ��鿡�� ������ �������� �����Ѵ�.",true,CL_normal);
		printsub("���� ��Ű�� ����� �������� ��ȯ���κ��� �����ְų� P�� ���������� ü�°� ������ ȸ�������ش�.",true,CL_normal);
		printsub("�������� �̻��� �������� ����� ������ ����� �� �ִ� �� �����ؾߵȴ�.",true,CL_normal);
		printsub("�ŵ����� P���� �ݴ� ������ �žӽ��� ���� �� �ִ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_MINORIKO:
		printsub("��Ű �̳븮�� - ǳ���� ��Ȯ�� ��¡",true,CL_warning);
		printsub("�̳븮�ڴ� ������ ��Ȯ�� ��¡�ϴ� ������ �ŵ����� ǳ������ �����Ѵ�.",true,CL_normal);
		printsub("�ŵ����� �̳븮�ڿ��� ǳ���� ������ �����ް� �ǰ� �������� ü���� ����޴´�.",true,CL_normal);
		printsub("�ŵ����� P���� �ݴ� ������ �žӽ��� ���� �� �ִ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SHIZUHA:
		printsub("��Ű ������ - �ܷο�� ������ ��¡",true,CL_small_danger);
		printsub("",true,CL_normal);
		printsub("��Ű �����ϴ� ��ǳ�� ���̴�.",true,CL_normal);
		printsub("�����ϴ� �ŵ����� ����� ���簨�� ���߾� �����ϰ� �ٴ� �� �ְ� �����ش�.",true,CL_normal);
		printsub("�׳��� �Ǵ��� �ϻ��ڵ鿡�� ū ������ �ָ� �߰����� �г�Ƽ�� ũ�� ������ �� �ִ�.",true,CL_normal);
		printsub("�����ϴ� �ò����� �ڵ��� ��ü�� ����ó�� �������� ���� �⻵�Ѵ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_EIRIN:
		printsub("�߰��ڷ� ���̸� - ���� �γ�",true,CL_small_danger);
		printsub("",true,CL_normal);
		printsub("�׳�� ��� ���� ������ �� �ִ� ���� �ְ��� ���ڷ� õ�� ����̴�.",true,CL_normal);
		printsub("�׳��� �ŵ��� ���� �������� ������� �ްԵǰ� �߰����� ȿ���� ��� �ȴ�.",true,CL_normal);
		printsub("���� �ڽ��� ���� �����ϰų� ���ۿ��� �����ϴ� ������ ġ�ᵵ ����������.",true,CL_normal);
		printsub("�ŵ��� �׳��� �������� �� ������ �� �� �ִٸ� �׸�ŭ�� ������ ���� �� ���� ���̴�.",true,CL_normal);
		printsub("�ŵ��� �̷ο� ������ ������ �⵵�� �Ͽ� ������ ��ġ�ų� ������ ���ô� ������ �žӽ��� ���� �� �ִ�.",true,CL_normal);
		printsub("���� ���ִ� �ƴ����� ���� �׿����� ������ �žӽ��� ���� �� �� �ִ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_KANAKO:
		printsub("�߻�ī ī���� - ���ǰ� ȣ���� ��ȭ",true,CL_help);
		printsub("",true,CL_normal);
		printsub("ī���ڴ� ��(�ϴ�)�� â���ϴ� �ɷ��� ���� ������ ������ �ٶ��� �������� ���� ������ ������� �ִ�.",true,CL_normal);
		printsub("�׳�� ���ڵ鿡�� �ž��� �޴� ������ ������ ���� �ɷ��� �����Ѵ�.",true,CL_normal);
		printsub("Ư�� ��������� ���Ÿ�ź������ �ο�� �ڿ��� ū ������ �� ���̴�.",true,CL_normal);
		printsub("���ڵ��� ��ӵǴ� ������ �׳࿡�� �ž��� ���ľ��Ѵ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_YUKARI:
		printsub("����� ��ī�� - ���ӿ� ���� �䱫",true,CL_yukari);
		printsub("����� ��ī���� ȯ���⿡���� �̸��ִ� ������ ����� �䱫��.",true,CL_normal);
		printsub("��ī���� �Ľ����� ���� �Ǹ� �׳࿡�� ���� ���õ� �ɷ��� ���� �� �ִ�.",true,CL_normal);
		printsub("������ ���̴ɷ��� ���������� �Ǵ��� ������ �ٸ� ���̴ɷ��� �����ϰ�",true,CL_normal);
		printsub("�����ϱ� ���� ������ ���� �ɷ��� ������ �ŵ��� �����ϰ� ������� �ִ�.",true,CL_normal);
		//printsub("�׳��� ������ ��Ű�� �����̶�� Ư���� ������ �ַ� �����ϸ� �׳��� �Ľŵ��� ���⿡�� �����ϰ� �ȴ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_HINA:
		printsub("ī��߸� ���� - �����ִ� �׸��� ���� ��",true,CL_hina);
		printsub("",true,CL_normal);
		printsub("������ ���� ��Ƽ� ����� �����ϴ� ��ӽ��̴�.",true,CL_normal);
		printsub("�׳�κ��� ���� �޾Ƽ� ���ָ� ���� ���ϴ� ������ �׳��� �Ǵ��� ���� �� �ִ�.",true,CL_normal);
		printsub("������ Ž���ϴ� ������ �žӽ��� ���� �� �ִ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SATORI:
		printsub("�ڸ����� ���丮 - ���ɵ� �η����ϴ� �ҳ�",true,CL_danger);
		printsub("",true,CL_normal);
		printsub("���丮�� �������� �������� ������ �д� �䱫�̴�.",true,CL_normal);
		printsub("���丮�� �ϴ´ٴ� ���� �׳��� ���� �ȴٴ� ���͵� ���� �׳��� ���� ���� �� �ְ� �ȴ�.",true,CL_normal);
		printsub("���丮�� ���������̱⶧���� ������ ���� ���õ� �ɷ��� ���� ���� �ʴ´�.",true,CL_normal);
		printsub("�׷��� �׳��� ������ �д� �ɷ����� ������ ���� ������ ��ų� ��ġ�� �˾Ƴ� �� �ִ�.",true,CL_normal);
		printsub("���� ����� ���� �����κ��� Ʈ��츶�� �о�ų� ����� ������ ��°�� �о ����Ҽ��� �ִ�.",true,CL_normal);
		printsub("������ ���Ĵ��� ���� ��� ����� ������ ��������Ƿ� ���ż��� ������ ������� ������ �� ���̴�.",true,CL_normal);
		printsub("�׳��� �ֿϵ������� ������ Ž���ϴ� ������ �׳��� ȣ���� ���� �� �ִ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_YUUGI:
		printsub("ȣ�ñ��� ����� - ���þ����� ���³���",true,CL_yuigi);
		printsub("",true,CL_normal);
		printsub("������ ������ �����ÿ� ��� �ִ� �����̴�. ������ ���³����� ���Ϸ� ������ ���� �ŵ����� �ش�.",true,CL_normal);
		printsub("�׳��� ���� ���� ������ �ϸ鼭 ��븦 ��ġ�ų� ��������� �� ���������� ������ �س� �� �ִ�.",true,CL_normal);
		printsub("���� ������ ������ ��ȿ�� �Ͽ� ��븦 ����� ����ų� ������ �ñر� ���� ����� �� �ְ� �ȴ�.",true,CL_normal);
		printsub("��, ������ �ŵ��� ������ ���� ������ �ο�� ���� �Ⱦ��Ѵ�.",true,CL_normal);
		printsub("�׳��� �žӽ��� �������� �¸��ϴ� ������ ���� �� �ִ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_TENSI:
		printsub("�������� �ٽ� - ������õ�� �ư���",true,CL_tensi);
		printsub("",true,CL_normal);
		printsub("�ٽô� ����õ�� ���ڴ���� õ�� �ư����̴�.",true,CL_normal);
		printsub("�׳�� ������ õ���Ȱ�� �������ϴ��� �� �̺��� ���� �ڽ��� �ϰ����ϴ� �ŵ����� �峭��ó�� ����Ѵ�.",true,CL_normal);
		printsub("�ٽô� �ŵ����� ��� �Ǵɵ� ���������ʴ´�. ��� �ൿ�� �׳��� ������� �̷������. ",true,CL_normal);
		printsub("�ŵ��� �׻� ����õ���� ������ �ݺ��Ͽ� �׳��� ��̸� �ִ������� ����ٸ� ������ ������ ���� �� �ִ�.",true,CL_normal);
		printsub("������ �ŵ��� ������ ������ �ٶ��ٸ� �� �ڽ��� ������ ��ȸ�ϰ� �� ���̴�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_BYAKUREN:
		printsub("������ ���� - ���ε� �븶����",true,CL_white_blue);
		printsub("",true,CL_normal);
		printsub("������ ���迡 ���εǾ��־��� �븶����� ȯ���⿡ ���� ��û縦 ���� �ұ��� ����ħ�� ���Ѵ�.",true,CL_normal);
		printsub("�׳��� Ư��� ����(Ư�� ��ü�ɷ��� �ø��� ����)�̹Ƿ� ���ڵ鿡�� ������ �ַ� ����ģ��.",true,CL_normal);
		printsub("�׳��� �Ǵ����� ���� ������ ������ ��ų� ���� �̵��� �����ϰų� �����г�Ƽ�� ���޴´�.",true,CL_normal);
		printsub("�ŵ��� ������������ ���ο� ������� ������ ������ �žӽ��� ���� �� �ִ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_SEIJA:
		printsub("Ű�� ������ - ������ �Ƹ�������",true,CL_seija);
		printsub("",true,CL_normal);
		printsub("�����ڴ� ��������Ǿ��ִ� �Ƹ�������� �پ��� ���ǵ��� ��� �������̴�.",true,CL_normal);
		printsub("�����ڿ� ���� ��� ������ �׳డ ��ģ ������ �����۵��� ���� ���� �� �ִ�.",true,CL_normal);
		printsub("���� ������ ���� �׳�� �����ڴ� ����� ������ �Ǵ� �� ��ü�� �ְ�� ȯ���� ���̴�.",true,CL_normal);
		printsub("�׷��� �����ڴ� �������� �ŵ��� �̿��� �����̹Ƿ� ����� ���з� ���� ���̰�",true,CL_normal);
		printsub("�׳�� ����� �̿밡ġ�� �������� �������� ���� ���̸� �׳ฦ ������ ������ �ٸ� �ŵ��� ��Ÿ�� ���� ���̴�.",true,CL_normal);
		printsub("�׳�� �ǽ��� ���� ���ڸ� �Ⱦ��ϹǷ� ������ 9�� �Ѿ�� ���̻� �׳ฦ ���� �� ���� �ȴ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_LILLY:
		printsub("���� ȭ��Ʈ - ���� ������ ����",true,CL_lilly);
		printsub("",true,CL_lilly);
		printsub("���� ȭ��Ʈ�� ���� �˸��� �������� �������� �͸����ε� ������ ��ȭ��Ų�ٰ��Ѵ�.",true,CL_normal);
		printsub("�׳�� ������ �Ǹ��� �����Ű�� ���� �����鿡�� �ڽ��� ���� �����ְ��ִ�.",true,CL_normal);
		printsub("�׳ฦ �ϴ� ������ ������ �������� �ڽ��� ����� ������� �� �ִ�.",true,CL_normal);
		printsub("���ᰡ �� ������ ����� ���������� �׾ �ǻ�Ƴ��鼭 ����� ���� ���̴�.",true,CL_normal);
		printsub("����� ���� ����ġ�� �Ϻθ� ���� �����鿡 ��������ϸ� ����ġ�� ���� �������� ��Ű� �Բ� �����Ѵ�. ",true,CL_normal);
		printsub("���� ����ȭ��Ʈ�� �������� �������� �ڹ����� �ٸ� ������ �Ա��� �ź������ʴ´�.",true,CL_normal);
		printsub("����ȭ��Ʈ�� �� ������ Ž���ϴ� ���� �����Ѵ�.",true,CL_normal);
		printsub("",true,CL_normal);
		break;
	case GT_MIKO:
		printsub("������̹̳� ���� - ���ָ� �����ϴ� ���� ����", true, CL_miko);
		printsub("", true, CL_miko);
		printsub("������̹̳� ���ڴ� ������繦�� �������� ����� �д� �ɷ��� �����.", true, CL_normal);
		printsub("�׳ฦ �ϴ� �ŵ��� �žӽ��� �ƴ� �α⵵�� �ڿ����� ����ϰԵȴ�.", true, CL_normal);
		printsub("�α⵵�� ���� �ӵ��� ������ ������ ����� �аų� �������μ� �α⵵�� ���� �� ������", true, CL_normal);
		printsub("���� �ö󰡰ų� ��������� �ٲ�� �α⵵�� �������� �Ǵ��� �α⵵�� ũ�� �Ҹ��ϰ� �ȴ�.", true, CL_normal);
		printsub("������ �Ǵ��� ������ �ݿ������̸� ���ӽð����� ���������� ���� �̵��� ��� �������.", true, CL_normal);
		printsub("", true, CL_miko);
		break;
	case GT_OKINA:
		printsub("��Ÿ�� ��Ű�� - �ñ��� ������", true, CL_okina);
		printsub("", true, CL_okina);
		printsub("��Ÿ�� ��Ű���� ���Ŀ� �����ִ� ������� �ڼ��� ��ü�� �˷��������ʴ�.", true, CL_normal);
		printsub("�׳�� �ڽ��� ���� �ñ� ���ϸ� ã��������, ����� �� ���� �Ҽ��� �ִ�.", true, CL_normal);
		printsub("�׳��� �ŵ��� �Ǵ� ������ �׳��� ���� ����� ���� �̿��� �Ǵ��� ���� �� �ִ�.", true, CL_normal);
		printsub("���� ��������� Ÿ��ٴҼ����ְ�, ���� ��ڿ��� ���ڱ� �����Ҽ��� �ִ�.", true, CL_normal);
		printsub("���� �ٸ� ������� �θ��� ������ ����°� ���ŷ��� ����ø����� �ִ�.", true, CL_normal);
		printsub("�׳�� �������� �¸��Ͽ� ���� ���簨�� �θ� �˸��� ���� �����Ѵ�.", true, CL_normal);
		printsub("", true, CL_okina);
		break;
	case GT_JUNKO:
		printsub("��ȣ", true, CL_junko);
		printsub("", true, CL_junko);
		printsub("��ȣ�� ������ ��ȭ�� �ŷ����� �ڽ��� ������ �������� �ŵ��� �����ϰ� �ִ�.", true, CL_normal);
		printsub("�׳��� �ŵ��� �ȴٸ� �ܼ������� ������ ��ȭ�� �ɷ��� ���� �� �ִ�.", true, CL_normal);
		printsub("�׳��� �Ǵ��� �žӽɵ� �Ҹ����������� ����ϰԵǸ� �Ͻ������� ��ȭ���¿� ������", true, CL_normal);
		printsub("��ȭ �ܰ谡 �ö󰥼��� �Ҹ�ǰ�� ��뿡 ���ѵǴ� �г�Ƽ�� �����.", true, CL_normal);
		printsub("�⺻������ �Ǵɿ� ���� ��ȭ���´� �ð��� ������ ���ƿ����� ��ȣ�� �Ƴ��� �ŵ����Դ� �������� ��ȭ�� ���� �� �ִ�.", true, CL_normal);
		printsub("�׳��� �ູ�� �ʹ� ���̱⿡ �г�Ƽ�� ũ�� ������� ������������ �׿� ����Ҹ��� ���ο� �ູ�� ��������.", true, CL_normal);
		printsub("�׳�� ������ �������� ���̴� ���� ������ ���̴� ���� �����Ѵ�.", true, CL_normal);
		break;
	default:
		printsub("���׽�",true,CL_danger);
		printsub("",true,CL_normal);
		printsub("�� ���� ���״�!",true,CL_normal);
		printsub("���׽��� ���� �÷��̿� ������ ������ �ָ� ��ſ��� ���� ��Ʈ������ �ش�.",true,CL_normal);
		printsub("�� ���� �����ϴ� �͸����ε� ������ ũ������ �� �� ������ ����� ĳ���͸� ������ų���� �𸥴�.",true,CL_normal);
		printsub("���׽��� �г븦 ����������� �����ڿ��� �����ϴ� �� �ۿ� ����.",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("���׽��� ����ũ�ѿ��� ���� ���� ���̴�.",true,CL_danger);
		printsub("",true,CL_normal);
		break;
	}
}


void God_show()
{
	if(you.god == GT_NONE)
	{
		printlog("����� ���� ���� �ϰ� ���� �ʴ�.",true,false,false,CL_normal);
		return;
	}
	deletesub();
	WaitForSingleObject(mutx, INFINITE);
	SetDisplayTexture(&img_god_background[you.god]);
	GodInfor(you.god);
	printsub("",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("�Ǵɵ�:                                                           (���)",true,CL_normal);
	printsub("",true,CL_normal);
	int level_ = pietyLevel(you.piety);
	switch(you.god)
	{
	case GT_ERROR:
		break;
	case GT_NONE:
		break;
	case GT_JOON_AND_SION:
		if (level_ >= 0)
		{
			printsub("����� �����Ű� ������ ���ָ� �ް� �ִ�.                                            (�нú�)", true, CL_joon_and_sion);
			if (you.god_value[GT_JOON_AND_SION][0] != 1) {
				printsub(" �� ����� �Ҹ�ǰ�� ����Ҷ� ���� 2~3���� �ѹ��� �Ҹ��Ѵ�.", true, CL_joon_and_sion);
			}
			else {
				printsub(" �� ����� �Ҹ�ǰ�� ����Ҷ� ������ 2~3���� �ѹ��� �Ҹ��Ѵ�. (��ȭ��)", true, CL_joon);
			}
			if (you.god_value[GT_JOON_AND_SION][0] != 2) {
				printsub(" �� �������� �Ҹ�ǰ�� õõ�� ���������. �Ҹ�ǰ�� ������ ���� Ȯ���� �������.", true, CL_joon_and_sion);
			}
			else {
				printsub(" �� �������� �Ҹ�ǰ�� ���� �ӵ��� ���������. �Ҹ�ǰ�� ������ ������ �������. (��ȭ��)", true, CL_sion);
			}
			printsub("", true, CL_normal);
		}
		if (level_ >= 1 && !you.GetPunish(GT_JOON_AND_SION))
		{
			printsub("����� ��õ��� �ҿ��̳� �ÿ��� ������ �� �ִ�.                                       (��Ƽ��)", true, you.god_value[GT_JOON_AND_SION][0] == 0?CL_joon_and_sion:CL_bad);
			printsub("", true, CL_normal);
		}
		if (level_ >= 2 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] == 1) {
				printsub("�ҿ��� ������ ���ȿ� ��� �������� �����Ǹ� �������� �ٶ����� �Ŀ��� �Ҹ�ȴ�.        (�нú�)", true, CL_joon);
				printsub("", true, CL_normal);
			}
			else if (you.god_value[GT_JOON_AND_SION][0] == 2) {
				printsub("�ÿ��� ������ ���ȿ� �Ŀ��� �ֿ��� �Ŀ��� ������ �ʴ� ��� ü���� ȸ���Ѵ�.           (�нú�)", true, CL_sion);
				printsub("", true, CL_normal);
			}
			else {
				printsub("���Ǹ� �ϰԵǸ� �ҿ��̳� �ÿ��� ����� �Ŀ��� �̿��Ѵ�.                               (�нú�)", true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		if (level_ >= 4 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] == 1) {
				printsub("�ҿ��� ������ ���ȿ� �Ҹ�ǰ�� �����ϸ� ������ ������ ��´�.                          (�нú�)", true, CL_joon);
				printsub("", true, CL_normal);
			}
			else if (you.god_value[GT_JOON_AND_SION][0] == 2) {
				printsub("�ÿ��� ������ ���ȿ� ����� �Ҹ�ǰ�� �뷮���� �Ҵ� ��� ������ ��ȿ�� �Ѵ�.           (�нú�)", true, CL_sion);
				printsub("", true, CL_normal);
			}
			else {
				printsub("���Ǹ� �ϰԵǸ� �ҿ��̳� �ÿ��� ����� �Ҹ�ǰ�� �̿��Ѵ�.                             (�нú�)", true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		if (level_ >= 5 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] == 1) {
				printsub("����� �þ߳� ������ ȥ���� �������� �� �� �ִ�.                               (���ǽ� �ѹ���)", true, CL_joon);
				printsub("", true, CL_normal);
			}
			else if (you.god_value[GT_JOON_AND_SION][0] == 2) {
				printsub("����� �þ߳� ������ ������ �� �Ŀ� �þ߸� ������ �Ȱ��� �Ѹ� �� �ִ�.         (���ǽ� �ѹ���)", true, CL_sion);
				printsub("", true, CL_normal);
			}
			else {
				printsub("���Ǹ� �ϰԵǸ� �ҿ��̳� �ÿ��� ���� �Ǵ��� ����� �� �ִ�.                    (���ǽ� �ѹ���)", true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		if (level_ >= 6 && !you.GetPunish(GT_JOON_AND_SION))
		{
			if (you.god_value[GT_JOON_AND_SION][0] != 0) {
				printsub("����� ������ ��뿡 ���ǽ�Ű�� �ʽ��� ������ ����� �� �ִ�.                         (�ž�)", true, CL_joon_and_sion);
				printsub("", true, CL_normal);
			}
			else {
				printsub("���Ǹ� �ϰԵǸ� �����־��� ������ ����� �� �ִ�.                                       (�ž�)", true, CL_bad);
				printsub("", true, CL_normal);
			}
		}
		break;
	case GT_BYAKUREN:
		if(level_ >= 1 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("�������� ����� ��� �� �ִ� ���������� �Ѱ踦 �ø���.                     (�нú�)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("����� ���������� ������ ��ȭ��ų �� �ִ�.                                   (�ž�)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("����� �ٷ��� ��ȭ�Ǿ� ���� ������ �����г�Ƽ�� ������������ �����Ѵ�.     (�нú�)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("�������� ����� ��ȭ �������� �������ش�.                                  (�нú�)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_BYAKUREN))
		{
			printsub("����� ���������� ������ ��ȭ��ų �� �ִ�.                             (����, �ž�)",true,CL_white_blue);
			printsub("",true,CL_normal);
		}
		break;
	case GT_KANAKO:
		if(level_ >= 1 && !you.GetPunish(GT_KANAKO))
		{
			printsub("����� ī���ڴ��� ������ ������ �� �ִ�.                    (����, �ž�)",true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_KANAKO))
		{
			printsub("����� ī���ڴ��� ����� ������ �� �ִ�.                    (����, �ž�)",true,CL_help);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_KANAKO))
		{
			printsub("����� ī���ڴ��� �ٶ��� ���� �ְ��� �� �ִ�.               (����, �ž�)",true,CL_help);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SUWAKO:
		if(level_ >= 1 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString1((swako_1_power)you.god_value[GT_SUWAKO][0], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString2((swako_2_power)you.god_value[GT_SUWAKO][1], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString3((swako_3_power)you.god_value[GT_SUWAKO][2], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString4((swako_4_power)you.god_value[GT_SUWAKO][3], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SUWAKO))
		{
			printsub(GetSwakoString5((swako_5_power)you.god_value[GT_SUWAKO][4], SWAKO_SIMPLE_INFOR),true,CL_swako);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MINORIKO:
		if(level_ >= 0)
		{
			printsub("�Ŀ��� �������� ������ ���� �� �ְ� �ִ� �Ŀ��� ���� ������ �� �ִ�.       (�нú�)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("����� �Ŀ��� �������������� ü�°� ����ȸ���ӵ��� ��������.               (�нú�)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("�̳븮�ڴ� ��ſ��� �ɸ� �����̻�� �ɷ����ϸ� ȸ�������ش�.              (P, �ž�)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_MINORIKO))
		{ //�̶����� ���� ������ ���ش�.
			printsub("����� ������ �� ���� ���� �� �ְ� ������ ���µ� ���� ȸ���Ѵ�.            (�нú�)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("�̳븮�ڴ� ����� ���� ������ �Ҹ��Ͽ� ü���� ũ�� ȸ���� �� �ִ�.  (P, ����, �ž�)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_MINORIKO))
		{
			printsub("�̳븮�ڴ� ����� ������ ���� ���� �Ͻ������� ��,�ñ������� 1�ܰ� �ش�.    (�нú�)",true,CL_warning);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MIMA:
		if(level_ >= 0 && !you.GetPunish(GT_MIMA))
		{ 
			printsub("�žӽɿ� ����ؼ� �ִ뿵���� �ö󰣴�.                                     (�нú�)",true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_MIMA))
		{
			printsub("���� �׿����� ���� ���⿡ ���� ������ ���� �� �ִ�.                        (�нú�)",true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_MIMA))
		{
			printsub("�̸��� �ı����� �� ������ ������ ������Ų��.                           (�нú�)",true,CL_green);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_MIMA))
		{
			printsub("�̸��� �ı����� �� ������ �������� ������Ų��.                         (�нú�)",true,CL_green);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SHINKI:
		if(level_ >= 1 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("����� �ϱ� ���� ������ ��ȯ�� �� �ִ�.                                    (P, �ž�)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("����� �߱� ������ ��ȯ�� �� �ִ�.                                         (P, �ž�)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("�������� ��ȯ���� �ൿ�� ����Ȯ���� �����Ѵ�.                               (�нú�)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("����� ��� ������ ��ȯ�� �� �ִ�.                                         (P, �ž�)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SHINKI))
		{ 
			printsub("����� P�� �ֿﶧ���� ü�°� ������ ��������.                               (�нú�)",true,CL_white_puple);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUUGI:
		if(level_ >= 0 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("��Ⱑ ���� ���¿��� �ణ�� ü��ȸ���°� ���� ȸ�Ǹ� ��´�.                (�нú�)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("���� 1���� ���� �ٲ㼭 ���� �� �ִ�.                                    (����, �ž�)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("������ ���� ��븦 ��´�. ������ ������� �žӼҸ���� �� �� �ִ�.       (�нú�)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("��븦 ��� ���� ���÷����� �� �� �ִ�.                                    (P, �ž�)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("��븦 ��� ���� ���� �� �ִ�.                                             (P, �ž�)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("�ֺ��� ��븦 ħ����Ű�� ������ ��ȿ�� �� �� �ִ�.                         (P, �ž�)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUUGI))
		{ 
			printsub("������ �ñر�, �ﺸ�ʻ��� �� �� �ִ�.                                      (P, �ž�)",true,CL_yuigi);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SHIZUHA:
		if(level_ >= 0 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("�����ϴ� ������ �ῡ�� ���鼭 ��ġ�� Ȯ���� �ٿ��ش�.           (�нú�)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("����� �����̰ų� ���� �׿����� ��ǳ���� ���븦 �����.         (�нú�)",true,CL_autumn);
			printsub("",true,CL_normal);
			printsub("��ǳ ���� ������ �ſ� �����ϰ� ������ �� �ִ�.                  (�нú�) ",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("����� ��ǳ ���� ���ִ� ��� ���� ȥ���� �� �� �ִ�.        (����, �ž�)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("����� ���� ��ǳ���� �ٲ� �� �ִ�.                        (�ž�)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("����� ��ǳ ���� ������ �ſ� ������ ������ �� �ִ�.             (�нú�)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		if(level_ >= 6 && you.god_value[GT_SHIZUHA][0]==0 && !you.GetPunish(GT_SHIZUHA))
		{
			printsub("����� �� �ѹ� ����� ���⿡ ��ǳ�귣�带 �ο��� �� �ִ�.       (�ѹ���)",true,CL_autumn);
			printsub("",true,CL_normal);
		}
		break;
	case GT_HINA:
		if(level_ >= 0)
		{ 
			printsub("����� �þ߳��� ��� ���ְ� �ɷ��ִ��� Ȯ���ϰ� �ĺ��� �� �ִ�.                (�нú�)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_HINA))
		{ 
			printsub("����� �������� ���ְ� �ɸ� ����� ���̳ʽ� ��æƮ�� �÷����� �ٲ� �� �ִ�.           (P)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_HINA))
		{ 
			printsub("����� ���⿡ ��õ��� ������ ���� ��� ��ȭ ��ų �� �ִ�.                         (����)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_HINA))
		{ 
			printsub("����� ���� ��õ��� ������ ���� ��� ��� ������ �ݻ��ų �� �ִ�.            (����)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_HINA))
		{ 
			printsub("����� ��ű��� ��õ��� ������ ���� ��� ������� ġ�� �� �� �ִ�.                (����)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_HINA))
		{ 
			printsub("����� ���ֵ� �������� ���� ������ ���ָ� ��Ѹ��� �ٴѴ�.                       (�нú�)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		if(level_ >= 6 && you.god_value[GT_HINA][0]==0 && !you.GetPunish(GT_HINA))
		{
			printsub("����� �� �ѹ� ����� ���⿡ ���ֺ귣�带 �ο��� �� �ִ�.						   (�ѹ���)",true,CL_hina);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUKARI:
		if(level_ >= 0 && !you.GetPunish(GT_YUKARI))
		{
			printsub("ƴ���� ����� ���Ѻ���.                                         (�нú�)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_YUKARI))
		{
			printsub("����� ���� �������� ������ �����̵��� �Ͼ��.                (�нú�)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUKARI))
		{
			printsub("����� ƴ���κ��� ��������� ���� �� �ִ�.                  (����, �ž�)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUKARI))
		{
			printsub("����� ƴ���� Ÿ��ٴ� �� �ִ�.                             (����, �ž�)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_YUKARI))
		{
			printsub("����� ��踦 ���� �� �ִ�.                                 (����, �ž�)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUKARI))
		{
			printsub("����� ��õ��� ������ ������ų �� �ִ�.                    (����, �ž�)",true,CL_yukari);
			printsub("",true,CL_normal);
		}
		break;
	case GT_EIRIN:
		if(!you.GetPunish(GT_EIRIN))
		{
			printsub("���̸��� ������� ȿ���� ��½����ش�.                          (�нú�)",true,CL_small_danger);
			printsub("",true,CL_normal);
			printsub("���� ���������� �⵵�ϴ� ������ ���� ������ ���� �� �ִ�.         (����)",true,CL_small_danger);
			printsub("",true,CL_normal);
			if(level_ >= 1)
			{
				printsub("����� ������ ������ ���Ƕ� �߰� ȿ���� �޴´�.                 (�нú�)",true,CL_small_danger);
				printsub(" �������� : �̵��ӵ��� ��������.",true,CL_small_danger);
				if(level_ >= 2)
					printsub(" ���ɷ�ġ���ҹ��� : ü���� ȸ���Ѵ�.",true,CL_small_danger);
				if(level_ >= 3)
					printsub(" ��ȥ������ : ������ ȸ���Ѵ�.",true,CL_small_danger);
				if(level_ >= 4)
					printsub(" �����ӹ��� : ����������.",true,CL_small_danger);
				if(level_ >= 5)
					printsub(" �����񹰾� : ����ð��� �پ��� ������ ����Ѵ�.",true,CL_small_danger);
				entersub();
				printsub("",true,CL_normal);
			}
		}
		if(level_ >= 2 && !you.GetPunish(GT_EIRIN))
		{
			printsub("����� ������ ���� �� �ִ�.                                    (P, ����)",true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_EIRIN))
		{
			printsub("����� ��ü������ ���� �ɷ�ġ�� ������ �� �ִ�.                   (�ž�)",true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_EIRIN))
		{
			printsub("����� ���ۿ��� �밡�� ���� ����� �� �ִ�.              (P, ����, �ž�)",true,CL_small_danger);
			printsub("",true,CL_normal);
		}
		break;
	case GT_YUYUKO:
		if(level_ >= 1 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("����� ������ �ҷ����δ�.                                      (�нú�)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("���ϴ� ��ġ�� ���ɵ��� ���� �� �ִ�.                          (P, ����)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("��õ��� ������ �ҷ����̴� �󵵸� ���� �� �ִ�.            (�ž�, ����)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_YUYUKO))
		{ 
			printsub("�� �Ѹ��� ��ȥ�� ���� �� �ִ�.                             (�ž�, ����)",true,CL_yuyuko);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SATORI:
		if(level_ >= 0 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("����� ������ �� �� �ִ�.                                       (�нú�)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("����� ����� Ʈ��츶�� ��� �� �ִ�.                          (�ž�)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 2 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("����� ���� ���ӿ��� ���� ���¸� �о��.                    (�нú�)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("����� ���� ��ô�� Ž���� �� �ִ�.                              (�нú�)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 4 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("�� �Ѹ��� ������ �Ϻ��ϰ� ������ �� �ִ�.                   (�ð�, �ž�)",true,CL_danger);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SATORI))
		{ 
			printsub("���丮�� ���� ��ſ��� ���̸� �ش�. �����Ҽ��� ���� �ش�.       (�нú�)",true,CL_danger);
			printsub("",true,CL_normal); 
		}
		break;
	case GT_TENSI:
		if(level_ >= 0 && !you.GetPunish(GT_TENSI))
		{ 
			printsub("�ٽ��� �ൿ�� ������ �� ����!                                           ",true,CL_tensi);
			printsub("",true,CL_normal);
		}
		break;
	case GT_SEIJA:
		if(level_ >= 1 && !you.GetPunish(GT_SEIJA))
		{ 
			printsub("����� �����ڷκ��� ������ ��ȭ�ް��ִ�.                        (�нú�)",true,CL_seija);
			printsub("",true,CL_normal);
		}
		if (level_ >= 2 && !you.GetPunish(GT_SEIJA))
		{
			printsub("¡���� ���� �߰����κ��� ����� ���´�.                         (�нú�)", true, CL_seija);
			printsub("", true, CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_SEIJA))
		{
			printsub("���ϴ� ����� ��ġ�� ������ �� �ִ�.                               (P)",true,CL_seija);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_SEIJA))
		{ 
			printsub("��� ��, �Ʊ��� �þ߸� ������ �� �ִ�.                               (P)",true,CL_seija);
			printsub("",true,CL_normal);
		}
		break;
	case GT_LILLY:
		if(level_ >= 1 )
		{ 
			printsub("===����� ���� ����===",true,CL_lilly);
			printsub("",true,CL_normal);
			for(int i = 0; i < min(5,level_); i++)
			{
				char temp[100];
				sprintf_s(temp,100,"%d��° ����: ",i+1);
				printsub(temp,false,CL_warning);
				if(you.god_value[GT_LILLY][i])
				{
					int lenght_ =0;
					if(mondata[you.lilly_allys[i].id].flag & M_FLAG_UNIQUE)
					{
						lenght_ = sprintf_s(temp,100,"%s ",mondata[you.lilly_allys[i].id].name.name.c_str());
						printsub(temp,false,CL_normal);
					}
					else
					{
						lenght_ = sprintf_s(temp,100,"%s(%s) ",fairy_name[you.lilly_allys[i].name].name.c_str(),mondata[you.lilly_allys[i].id].name.name.c_str());
						printsub(temp,false,CL_normal);
					}
					for(;lenght_<25;lenght_++)
						printsub(" ",false,CL_normal);
					lenght_ += printsub("����: ",false,CL_warning);
					sprintf_s(temp,100,"%2d",you.lilly_allys[i].level);
					lenght_ += printsub(temp,false,CL_normal);

					for(;lenght_<40;lenght_++)
						printsub(" ",false,CL_normal);
					printsub("����: ",false,CL_warning);
					sprintf_s(temp,100,"%s",you.god_value[GT_LILLY][i]==1?"����":"��Ȱ�����");
					printsub(temp,true,you.god_value[GT_LILLY][i]==1?CL_white_blue:CL_danger);
				}
				else
				{
					printsub("����",true,CL_bad);
				}
			}
			printsub("",true,CL_normal);
			printsub("",true,CL_normal);
		}
		if(level_ >= 0 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("������ ����ġ�� �����ָ� ���� ������ ����ġ�� ������ ��Ȱ�Ѵ�.  (�нú�)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("����� �������� ����� ������ �� �ִ�.                            (����)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 1 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("����� �������� ��ó�� ȣ���� �� �ִ�.                            (����)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 3 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("����� ���� ������ ġ���� �� �ִ�.                             (P, ����)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		if(level_ >= 5 && !you.GetPunish(GT_LILLY))
		{ 
			printsub("����� �����鿡�� ���� ������ �� �ִ�.                         (P, ����)",true,CL_lilly);
			printsub("",true,CL_normal);
		}
		break;
	case GT_MIKO:
		if (level_ >= 0 && !you.GetPunish(GT_MIKO))
		{
			printsub("�α⵵�� ���� �ൿ�� �� ��� �ö󰣴�.", true, CL_normal);
			printsub("    ���� ���δ�. ���Ҽ��� �� ���� �ö󰣴�.", true, CL_miko);
			printsub("    ��������⸦ �̿��� �þ߳��� ������ ����� ������.", true, CL_miko);
			printsub("    ���ο� ��������� �����Ѵ�.", true, CL_miko);
			printsub("", true, CL_normal);
			printsub("�α⵵�� ���� �ൿ�� �� ��� ��������.", true, CL_normal);
			printsub("    ���� �ű��. �ö󰥼��� �� ���� �α⵵�� ��������.", true, CL_miko);
			printsub("    ��������� �ű��. ��� �α⵵�� ��������.", true, CL_miko);
			printsub("    ������ �Ǵ��� ����Ѵ�.", true, CL_miko);
			printsub("", true, CL_normal);
			printsub("�ֺ��� ����κ��� �α⵵�� ���� �� �ִ�.                 (������ �ѹ���)", true, CL_miko);
			printsub("", true, CL_normal);
			char temp[256];
			sprintf_s(temp, 256, "���� �ӵ��� ������ �����̵��� �� �� �ִ�.                  (�α⵵ %3d%%)", getMikoPiety(0) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(0) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
			sprintf_s(temp, 256, "�ش� ������ �ֺ��� ���ߴ� �ı��� ���� �� �ִ�.             (�α⵵ %3d%%)", getMikoPiety(1) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(1) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
			sprintf_s(temp, 256, "�ش� ������ ���ϴ� ������ ���� �� �ִ�.                    (�α⵵ %3d%%)", getMikoPiety(2) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(2) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
			sprintf_s(temp, 256, "�ش� ������ ���ϴ� �����ɷ��� ��ȭ��ų �� �ִ�.            (�α⵵ %3d%%)", getMikoPiety(3) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(3) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
			sprintf_s(temp, 256, "�ش� �������� �ñ��� �ູ�� ���� �� �ִ�.                  (�α⵵ %3d%%)", getMikoPiety(4) / 2);
			printsub(temp, true, you.piety >= getMikoPiety(4) ? CL_miko : CL_bad);
			printsub("", true, CL_normal);
		}
		break;
	case GT_OKINA:
		if (level_ >= 0 && !you.GetPunish(GT_OKINA))
		{
			printsub("����� ��������� ���� �̵��� ���ð� �����ϴ�.                  (�нú�)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 1 && !you.GetPunish(GT_OKINA))
		{
			printsub("����� ���ϴ� ���� ���� ���� �� �ִ�.                           (P, ����)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 2 && !you.GetPunish(GT_OKINA))
		{
			printsub("����� ���� ������ �ݰ� ��� �� �ִ�.                        (�ž�, ����)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 3 && !you.GetPunish(GT_OKINA))
		{
			printsub("����� ���� ��ڷ� �̵��� �� �ִ�.                           (�ž�, ����)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 4 && !you.GetPunish(GT_OKINA))
		{
			printsub("����� ũ������ ����� �ҷ��� �� �ִ�.                           (�ž�)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		if (level_ >= 5 && !you.GetPunish(GT_OKINA))
		{
			printsub("����� �������� ��ڿ� �ִ� ���� ���� Ż�� �� �� �ִ�.       (�ž�, ����)", true, CL_okina);
			printsub("", true, CL_normal);
		}
		break;
	case GT_JUNKO:
		{

			bool already_pure = you.god_value[GT_JUNKO][3] != 0;
			if (level_ >= 0)
			{
				if (already_pure)
				{
					printsub("����� ��ȣ�� �ູ�� ���� ���������� ��ȭ�Ǿ���.                 (�нú�)", true, CL_junko);
					if (you.god_value[GT_JUNKO][3] == 7)
						printsub(" ������� �Ϻ� �η縶��, ������ ����� �� ����.", true, (you.s_pure_turn && you.s_pure >= 10) ? CL_junko : CL_bad);
					else
						printsub(" ������� ����ī��, �Ϻ� �η縶��, ������ ����� �� ����.", true, (you.s_pure_turn && you.s_pure >= 10) ? CL_junko : CL_bad);
					printsub(" ������� ��� ������ 5 �����Ѵ�.", true, CL_junko);
					printsub("", true, CL_normal);
				}
				else
				{
					printsub("��ȣ�� ���� ���������� ����� �Ͻ������� ��ȭ��Ų��.             (�нú�)", true, CL_junko);
					if (level_ >= 0 && !you.GetPunish(GT_JUNKO))
					{
						printsub(" ��1�ܰ�: ����� ����ī�带 ����� �� ����.", true, (you.s_pure_turn && you.s_pure >= 10) ? CL_junko : CL_bad);
						printsub(" ��2�ܰ�: ����� �Ϻ� �η縶���� ȿ���� ����� �� ����.", true, (you.s_pure_turn && you.s_pure >= 20) ? CL_junko : CL_bad);
						printsub(" ��3�ܰ�: ����� ������ ȿ���� ���� �ʴ´�.", true, (you.s_pure_turn && you.s_pure >= 30) ? CL_junko : CL_bad);
						printsub("", true, CL_normal);
					}
				}
			}
			if (level_ >= 1 && !you.GetPunish(GT_JUNKO))
			{
				printsub("����� �ܼ������� ������ ź���� ���� �� �ִ�.                  (P, ����)", true, already_pure? CL_bad : CL_junko);
				printsub("", true, CL_normal);
			}
			if (level_ >= 2 && !you.GetPunish(GT_JUNKO))
			{
				printsub("����� ������ ���� ���� �� �ִ�.                                  (�ž�)", true, already_pure ? CL_bad : CL_junko);
				printsub("", true, CL_normal);
			}
			if (level_ >= 4 && !you.GetPunish(GT_JUNKO))
			{
				printsub("����� ������ ���Ǹ� ���� �� �ִ�.                                (�ž�)", true, already_pure ? CL_bad : CL_junko);
				printsub("", true, CL_normal);
			}
			if (level_ >= 5 && !you.GetPunish(GT_JUNKO))
			{
				if (already_pure)
				{
					printsub("����� ��ȣ�� �ູ���� ���������� ��ȭ�Ǿ���.", true, CL_junko);
					char temp[100];
					switch (you.god_value[GT_JUNKO][3])
					{
					case 1:
						sprintf_s(temp, 100, " ����ų��ȭ: ����� %s ��ų������ ĳ���� ������ �׻� ����. ", skill_string((skill_type)you.pure_skill));
						printsub(temp, true, CL_junko);
						break;
					case 2:
					{
						sprintf_s(temp, 100, " �����׼�ȭ: ����� %s ������ �鿪�̴�. ", you.GetProperty(TPT_FIRE_IMUNE)?"ȭ��":(you.GetProperty(TPT_COLD_IMUNE) ? "�ñ�" : (you.GetProperty(TPT_ELEC_IMUNE) ? "����" : "����")));
						printsub(temp, true, CL_junko);
						break;
					}
					case 3:
						sprintf_s(temp, 100, " �����¼�ȭ: ����� ü�°� ������ ���Ͻõȴ�. ");
						printsub(temp, true, CL_junko);
						break;
					case 4:
						sprintf_s(temp, 100, " ���Ŀ���ȭ: ����� �׻� Ǯ�Ŀ���. ");
						printsub(temp, true, CL_junko);
						break;
					case 5:
						sprintf_s(temp, 100, " �������ȭ: ����� �߰� ����� �޾Ҵ�. ");
						printsub(temp, true, CL_junko);
						break;
					case 6:
						sprintf_s(temp, 100, " ������ȭ: ����� ������ �ִ� ��� ��ȭ�ߴ�. ");
						printsub(temp, true, CL_junko);
						break;
					case 7:
						sprintf_s(temp, 100, " ���ý��ۼ�ȭ: ����� ����ī�� ����� �㰡�ǰ� ������ �����ӵ��� 3�谡 �Ǿ���. ");
						printsub(temp, true, CL_junko);
						break;
					default:
						printsub(" ���˼����� ���� ��ȭ", true, CL_junko);
						break;
					}
				}
				else
				{
					printsub("����� ��ȣ�� �ູ���� ���������� ��ȭ�� �� �ִ�.               (�ѹ���)", true, CL_junko);
				}
				printsub("", true, CL_normal);
			}
			break;
		}
	}
	changedisplay(DT_SUB_TEXT);
	ReleaseMutex(mutx);
	while(1)
	{
		int key_ = waitkeyinput(true);
		break;
	}
	changedisplay(DT_GAME);
	SetDisplayTexture(NULL);

}
bool God_pray(const list<item>::iterator it)
{
	switch(you.god)
	{
	case GT_ERROR:
		break;
	case GT_NONE:
		break;
	case GT_JOON_AND_SION:
		break;
	case GT_BYAKUREN:
		break;
	case GT_KANAKO:
		//if(it->type == ITM_FOOD && it->value1 == 0)
		//{
		//	printlog("P���� �ұ�տ� �۽ο� �������. ī���ڴ� ������ �޾Ƶ鿴��.",true,false,false,CL_small_danger);
		//	env[current_level].DeleteItem(it);
		//	if(randA(1))
		//	{
		//		you.PietyUpDown(1);	
		//		you.GiftCount(1);
		//	}
		//	return true;		
		//}
		break;
	case GT_SUWAKO:
		break;
	case GT_MINORIKO:
		break;
	case GT_MIMA:
		break;
	case GT_SHINKI:
		break;
	case GT_YUUGI:
		break;
	case GT_SHIZUHA:
		break;
	case GT_HINA:
		break;
	case GT_YUKARI:
		break;
	case GT_EIRIN:
		//if(it->type == ITM_FOOD && it->value1 == 0)
		//{
		//	printlog("P���� �ұ�տ� �۽ο� �������. ���̸��� ������ �޾Ƶ鿴��.",true,false,false,CL_small_danger);
		//	env[current_level].DeleteItem(it);
		//	you.PietyUpDown(1);	
		//	you.GiftCount(1);
		//	return true;		
		//}
		if(it->type == ITM_POTION && iden_list.potion_list[it->value1].iden && isGoodPotion((potion_type)it->value1)>0)
		{
			int per_ = randA(100);
			int result_ = (per_<15)?PT_CONFUSE:((per_<41)?PT_POISON:((per_<67)?PT_SLOW:(per_<93)?PT_DOWN_STAT:PT_PARALYSIS));
			printarray(false,false,false,CL_small_danger,3,it->GetName().c_str(),it->GetNameInfor().name_is(true),randA(2)?(randA(1)?"���⸦ ���� ":"����� ������ ǳ��� "):"���� ���鼭 ");
			it->value1 = result_;
			printarray(true,false,false,CL_small_danger,3,it->GetName().c_str(),it->GetNameInfor().name_by(true),"�ٲ����.");
			printarray(true,false,false,CL_small_danger,1,"���̸��� ������ �����.");
			you.PietyUpDown(it->num * 2);
			you.GiftCount(it->num * 1);
			return true;
		}
		break;
	case GT_YUYUKO:
		break;
	case GT_SATORI:
		break;
	case GT_TENSI:
		break;
	case GT_SEIJA:
		break;
	case GT_LILLY:
		break;
	case GT_MIKO:
		break;
	case GT_OKINA:
		break;
	case GT_JUNKO:
		break;
	}
	return false;		
}
bool god_punish(god_type god)
{
	bool summon_ = false;

	if(wiz_list.wizard_mode == 1)
	{
		printarray(true,false,false,CL_small_danger,1,"***¡��!***");
	}
	switch(god)
	{
	case GT_ERROR:
		break;
	case GT_NONE:
		break;
	case GT_JOON_AND_SION:
	{
		random_extraction<int> rand_;
		rand_.push(0, 50);//�ҿ��� ���� �����ϸ鼭 �Ŀ� ����
		rand_.push(1, 50);//�ÿ��� ���� �����ϸ鼭 ü�� ���� ����
		switch (rand_.pop())
		{
		case 0:
			you.god_value[GT_JOON_AND_SION][0] = 1;
			you.god_value[GT_JOON_AND_SION][1] = rand_int(250, 400);
			you.PowUpDown(-100);
			printarray(true, false, false, CL_white_blue, 1, "�ҿ��� ��ſ��� ������ �����Ͽ���! �Ŀ��� �����Ͽ���!");
			break;
		case 1:
			you.god_value[GT_JOON_AND_SION][0] = 2;
			you.god_value[GT_JOON_AND_SION][1] = rand_int(250, 400);
			you.HpUpDown(-you.GetMaxHp() / 2, DR_EFFECT);
			if (!you.pure_mp)
				you.MpUpDown(-you.max_mp / 2);
			printarray(true, false, false, CL_white_blue, 1, "�ÿ��� ��ſ��� ������ �����Ͽ���! ü�°� ������ �Ҿ���!");
			break;
		}
	}
	break;
	case GT_BYAKUREN:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//�������
			rand_.push(1,25);//���ȵ巹��
			rand_.push(2,25);//���ο�
			switch(rand_.pop())
			{
			case 0:
				you.MpUpDown(!you.pure_skill? -you.GetMaxMp(): -you.GetMaxMp()/2);
				printarray(true,false,false,CL_white_blue,1,"������ �г�� ����� ������ ����Ǿ���!");
				break;
			case 1:
				(randA(1)?you.StatUpDown(-rand_int(1,5),STAT_STR,true):you.StatUpDown(-rand_int(3,7),STAT_INT,true));
				printarray(true,false,false,CL_white_blue,1,"������ �г�� ����� ������ ���ҵǾ���!");
				break;
			case 2:
				you.SetSlow(rand_int(80,100));
				printarray(true,false,false,CL_white_blue,1,"������ �г�� ����� ��������!");
				break;
			}
		}
		break;
	case GT_KANAKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,33);//�ǽ��ʷ���
			rand_.push(1,33);//�¹ٽö�
			rand_.push(2,33);//�� ����
			switch(rand_.pop())
			{
			case 0:	
				{
					printarray(true,false,false,CL_help,1,"ī���ڴ� ��ſ��� ������ �ϰ��� ���ȴ�!");
					int damage_ = you.GetHp()*rand_int(40,80)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY,ATT_SMITE,name_infor("�ǽ��ʷ� ��",true));
					you.damage(temp_att, true);


				}	
				break;
			case 1:
				{
					for(int i = randA(3)+1; i>0 ; i--)
					{
						BaseSummon(MON_ONBASIRA, rand_int(10,30), true, false, 2, NULL, you.position, SKD_OTHER, -1);
					}
					printarray(true,false,false,CL_help,1,"ī���ڴ� ��ſ��� �¹ٽö� �ȾҴ�!");
					env[current_level].MakeNoise(you.position,16,NULL);
					break;
				}
			case 2:
				{
					int max_ = rand_int(3,5);
					deque<monster*> dq;
					for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
					{
						if(it->isLive() && !it->isUserAlly())
						{
							dq.push_back(&(*it));
							max_--;
							if(!max_)
								break;
						}
					}
					rand_shuffle(dq.begin(),dq.end());
					dif_rect_iterator rit(you.position,2,true);
					if(!dq.empty())
					{							
						printarray(true,false,false,CL_help,1,"ī���ڴ� ����� ������ ������ �̲�����!");
						summon_ = true;
						for(int i = 0;!rit.end() && i < dq.size();rit++)
						{
							if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
							{
								dq[i]->SetXY(rit->x,rit->y);
								if(dq[i]->isYourShight())
								{
									dq[i]->AttackedTarget(&you);
								}
								i++;
							}
						}
					}
					else
					{
						printarray(true,false,false,CL_help,1,"ī���ڴ� ����� ������ �̲��������� ������ ���� ������.");
					}
				}
				break;
			}
		}
		break;
	case GT_SUWAKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//����
			rand_.push(1,50);//������
			switch(rand_.pop())
			{
			case 0:	
				{
					you.SetSlow(rand_int(4,20));
					int value_ = rand_int(30, 50);
					value_ += randA(you.level * 10);
					you.SetPoison(value_,300,true);
					rand_rect_iterator rit(you.position,1,1);
					int smoke_ = rand_int(2,5);
					for(int i = 0; !rit.end() && i < smoke_;rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y, true))
						{
							env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_FOG,rand_int(6,12),0,NULL);
							i++;
						}
					}
					env[current_level].MakeSmoke(you.position,img_fog_dark,SMT_FOG,rand_int(6,12),0,&you);
					printarray(true,false,false,CL_swako,1,"�����ڴ� ��ſ��� ���ָ� ���ȴ�!");
				}
				break;
			case 1:
				{
					int i = rand_int(2, 4);
					i += randA(you.level / 6);
					for(; i>0 ; i--)
					{
						if(monster *mon_ = BaseSummon((you.level > 10 && randA(3)==1)?MON_DEAGAMA:MON_FROG, rand_int(60,120), true, true, 2, NULL, you.position, SKD_OTHER, -1))
						{
							if(you.level>5)
								mon_->LevelUpdown(you.level-5);
						}
					}
					summon_ = true;
					printarray(true,false,false,CL_swako,1,"�����ڴ� ��ſ��� �������� ������ ������ �����ߴ�!");
				}
				break;
			}
		}
		break;
	case GT_MINORIKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//�Ŀ�����
			rand_.push(1,25);//ü�°��ҿ� ��
			rand_.push(2,25);//�ɷ�ġ����
			switch(rand_.pop())
			{
			case 0:				
				you.PowUpDown(-min(you.power,500)/2,true);
				printarray(true,false,false,CL_warning,1,"�̳븮�ڴ� ����� ������� ���ӽ��״�!");
				break;
			case 1:
				{
					you.HpUpDown(-max(1, you.GetHp() / 2), DR_EFFECT, NULL);
					you.SetSick(rand_int(80,120));
					printarray(true,false,false,CL_warning,1,"�̳븮�ڴ� ����� �ǰ��� ���Ѿư���!");
					break;
				}
			case 2:
				{
					for(int i=0;i<3;i++)
						you.StatUpDown(-rand_int(1,4),randA(2)?(randA(1)?STAT_STR:STAT_DEX):STAT_INT,true);
					printarray(true,false,false,CL_warning,1,"�̳븮�ڴ� ����� �ɷ�ġ�� ��Ƴ��ȴ�!");
					break;
				}
			}
		}
		break;
	case GT_MIMA:
		{
			random_extraction<int> rand_;
			rand_.push(0,33);//����
			switch(rand_.pop())
			{
			case 0:	
				{
					string str_ = "����";
					textures* tex_ = &img_blast[2];
					attack_type type_ = ATT_NORMAL_BLAST;
					int damage_ = 15+you.level*5;
					switch(randA(5))
					{
					case 0:
						{
						str_ = "ȭ�� ����";
						tex_ = &img_blast[0];
						type_ = ATT_FIRE_BLAST;
						break;
						}
					case 1:
						{
						str_ = "�ϼ� ����";
						tex_ = &img_blast[1];
						type_ = ATT_NORMAL_BLAST;
						damage_ = damage_*4/5;
						break;
					case 2:
						str_ = "���� ����";
						tex_ = &img_blast[2];
						type_ = ATT_ELEC_BLAST;
						break;
						}
					case 3:
						{
						str_ = "�͵� ����";
						tex_ = &img_blast[3];
						type_ = ATT_POISON_BLAST;
						damage_ = damage_*4/5;
						break;
						}
					case 4:
						{
						str_ = "�ñ� ����";
						tex_ = &img_blast[4];
						type_ = ATT_COLD_BLAST;
						break;
						}
					case 5:
						{
						str_ = "����";
						tex_ = &img_blast[5];
						type_ = ATT_COLD_BLAST;
						damage_ = damage_*3/5;
						break;
						}
					}
					printarray(true,false,false,CL_green,3,"�̸��� ������ ",str_.c_str(),"�� ��ſ� �ܳ��ߴ�!");
					attack_infor temp_att(randC(3,damage_/3),damage_,99,NULL,PRT_ENEMY,type_,name_infor(str_.c_str(),true));
					BaseBomb(you.position, tex_,temp_att);
					env[current_level].MakeNoise(you.position,12,NULL);
				}	
				break;
			}
		}
		break;
	case GT_SHINKI:
		{
			random_extraction<int> rand_;
			rand_.push(0,100);//�Ǹ���ȯ
			switch(rand_.pop())
			{
			case 0:
				{
					random_extraction<int> lowmidhigh_[3],perenct_;
					lowmidhigh_[0].push(MON_EVIL_EYE);
					lowmidhigh_[0].push(MON_LITTLE_IMP);
					lowmidhigh_[1].push(MON_LUIZE);
					lowmidhigh_[1].push(MON_ELIS);
					lowmidhigh_[1].push(MON_SARA);
					lowmidhigh_[2].push(MON_YUKI);
					lowmidhigh_[2].push(MON_MAI);
					lowmidhigh_[2].push(MON_YUUGENMAGAN);

					if(you.level<15)	
						perenct_.push(0,30-you.level*2);
					perenct_.push(1,3+you.level);
					if(you.level>13)	
						perenct_.push(2,you.level*3-40);


					int i = rand_int(1,3+you.level/9);
					for(; i>0 ; i--)
					{
						int demon_ = lowmidhigh_[perenct_.choice()].choice();
						if(monster *mon_ = BaseSummon(demon_, rand_int(90,120), true, true, 2, NULL, you.position, SKD_OTHER, -1))
						{
						}
					}
					summon_ = true;
					printarray(true,false,false,CL_white_puple,1,"��Ű�� �������� �������� â���س´�!");
				}
				break;
			}
		}
		break;
	case GT_YUUGI:
		{
			random_extraction<int> rand_;
			rand_.push(0,25);//��
			rand_.push(1,25);//���̾�Ʈ ����
			rand_.push(2,50);//���� ��ȯ
			switch(rand_.pop())
			{
			case 0:			
				printarray(true,false,false,CL_yuigi,1,"����Ⱑ ���� ���� ��ſ��� ������ �Կ���!");	
				you.SetConfuse(rand_int(9,30));
				you.SetDrunken(rand_int(50,100));
				break;
			case 1:
				{
					printarray(true,false,false,CL_yuigi,1,"����Ⱑ ����� ���������!");
					you.Blink(40);
					int damage_ = you.GetHp()*rand_int(30,60)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY, ATT_SMASH,name_infor("���̾�Ʈ����",true));
					you.damage(temp_att, true);
				}
				break;
			case 2:
				{
					printarray(true,false,false,CL_yuigi,1,"����Ⱑ ����� ���ϱ����� ���� ���ϵ��� �ҷ��´�!");
					random_extraction<int> oni_;
					oni_.push(MON_ONI);
					oni_.push(MON_BLUE_ONI);
					int i = rand_int(1+you.level/10,1+you.level/5);
					summon_ = true;
					for(; i>0 ; i--)
					{
						int time_ = rand_int(40,60);
						if(monster *mon_ = BaseSummon(oni_.choice(), time_, true, true, 2, NULL, you.position, SKD_OTHER, -1))
						{
							if(randA(99)<max(0,200-you.level*30))
								mon_->SetSlow(time_);
							if(randA(99)<max(0,you.level*4-28))
								mon_->SetMight(time_);
							if(randA(99)<max(0,you.level*5-65))
								mon_->SetHaste(time_);
						}
					}
				}
				break;
			}
		}
		break;
	case GT_SHIZUHA:
		{
			random_extraction<int> rand_;
			rand_.push(0,33);//ȥ��
			rand_.push(1,33);//�Ͻ�
			rand_.push(2,33);//���ο�
			switch(rand_.pop())
			{
			case 0:			
				printarray(true,false,false,CL_autumn,1,"�����ϴ� ��ſ� ������ ������ �𳯷ȴ�!");	
				you.SetConfuse(rand_int(12,45), true);
				break;
			case 1:
				{				
					rand_rect_iterator rit(you.position,2,2);
					int i = 5+randA(5); 
					for(;!rit.end() && i> 0;rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x,rit->y))
						{	
							int rand_ = randA(1);
							env[current_level].MakeFloorEffect(coord_def(rit->x,rit->y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,rand_int(20,30),&you);
						}
						i--;
					}
					int rand_ = randA(1);
					env[current_level].MakeFloorEffect(coord_def(you.position.x,you.position.y),&img_effect_autumn_leave[rand_*2],&img_effect_autumn_leave[rand_*2+1],FLOORT_AUTUMN,3+you.piety/20,&you);
	
					printarray(true,false,false,CL_autumn,1,"�����ϰ� ����� �� �ڸ� �񷶴�!");
					int damage_ = you.GetHp()*rand_int(30,60)/100;
					attack_infor temp_att(damage_,damage_,99,NULL,PRT_ENEMY,ATT_SMITE,name_infor("�Ͻ�",true));
					you.damage(temp_att, true);
					you.SetBuff(BUFFSTAT_RF,BUFF_AUTUMN_RF,-1,1);
				}
				break;
			case 2:
				{
					printarray(true,false,false,CL_autumn,1,"�����ϰ� ��û�� ������ �Բ� ����� �����ߴ�!");
					env[current_level].MakeNoise(you.position,30,NULL);
					int time_ = rand_int(40,60);
					you.SetGlow(time_);
					you.SetSlow(time_);
				}
				break;
			}
		}
		break;
	case GT_HINA:
		{
			random_extraction<int> rand_;
			rand_.push(0,25);//��
			rand_.push(1,50);//����
			rand_.push(2,25);//ȥ��
			switch(rand_.pop())
			{
			case 0:		
				{
					you.SetSlow(rand_int(4,20));
					int value_ = rand_int(20, 40);
					value_ += randA(you.level * 8);
					you.SetPoison(value_,200,true);
					rand_rect_iterator rit(you.position,1,1);
					int smoke_ = rand_int(3,7);
					for(int i = 0; !rit.end() && i < smoke_;rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y, true))
						{
							env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_CURSE,rand_int(6,12),0,NULL);
							i++;
						}
					}
					env[current_level].MakeSmoke(you.position,img_fog_dark,SMT_CURSE,rand_int(6,12),0,&you);
					printarray(true,false,false,CL_hina,1,"������ ���� ��ſ��� ���� �����ߴ�!");
				}
				break;
			case 1:
				{
					bool curse_ = false;
					deque<int> dq;
					for(int i=ET_FIRST;i<ET_LAST;i++)
					{
						if(i != ET_THROW)
							dq.push_back(i);
					}	
					rand_shuffle(dq.begin(),dq.end());
					printarray(false,false,false,CL_hina,1,"������ ����� ��� ���� �����ߴ�! ");


					for(int i = 0; i<dq.size() ; i++)
					{
						if(you.equipment[dq[i]])
						{
							string before_name = you.equipment[dq[i]]->GetName(); //���ֹޱ��� �̸�
							if(you.equipment[dq[i]]->Curse(true,(equip_type)dq[i]))
							{
								enterlog();
								printlog("�����ϰ� �ִ� ",false,false,false,CL_small_danger);		
								printlog(before_name,false,false,false,CL_small_danger);	
								printlog(you.equipment[dq[i]]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
								printlog("�˰� ������.",true,false,false,CL_small_danger);		
								curse_ = true;
								break;
							}
						}
					}
					if(!curse_)
					{
						printarray(true,false,false,CL_hina,1,"�׷��� �ƹ��ϵ� �Ͼ�� �ʾҴ�.");

					}
				}
				break;
			case 2:
				{
					printarray(true,false,false,CL_autumn,1,"������ ����� ���� ���ȴ�!");	
					you.SetConfuse(rand_int(12,45), true);
					break;
				}
			}
		}
		break;
	case GT_YUKARI:
		{
			random_extraction<int> rand_;
			rand_.push(0,25);//�����̵�
			rand_.push(1,50);//����
			rand_.push(2,25);//ȥ��
			switch(rand_.pop())
			{
			case 0:		
				{
					you.SetConfuse(rand_int(6,18), true);
					you.Teleport();
					printarray(true,false,false,CL_yukari,1,"��ī���� ����� ������ �ڷ���Ʈ ���״�!");
				}
				break;
			case 1:
				{					
					you.SetStasis(rand_int(20,30));
					int max_ = rand_int(2,3);
					deque<monster*> dq;
					for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
					{
						if(it->isLive() && !it->isUserAlly())
						{
							dq.push_back(&(*it));
							max_--;
							if(!max_)
								break;
						}
					}
					rand_shuffle(dq.begin(),dq.end());
					dif_rect_iterator rit(you.position,2,true);
					if(!dq.empty())
					{
						summon_ = true;
						printarray(true,false,false,CL_yukari,1,"��ī���� ����� �ֺ��� ������ ������ �̵����״�!");
						for(int i = 0;!rit.end() && i < dq.size();rit++)
						{
							if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
							{

								dq[i]->SetXY(rit->x,rit->y);
								textures* t_ = &img_effect_schema[randA(2)];
								env[current_level].MakeFloorEffect(coord_def(rit->x,rit->y),t_,t_,FLOORT_SCHEMA,rand_int(20,30),&you);

								if(dq[i]->isYourShight())
								{
									dq[i]->AttackedTarget(&you);
								}
								i++;
							}
						}
					}
					else
					{
						printarray(true,false,false,CL_yukari,1,"��ī���� ����� �����̵��� ���Ҵ�!");
					}
				}
				break;
			case 2:
				{

					printarray(true,false,false,CL_yukari,1,"��ī���� ����� �����ϴ� ������ ���� ��ȯ�ߴ�!");
					summon_ = true;
					int i = rand_int(2+you.level/8,3+you.level/5);
					for(; i>0 ; i--)
					{
						int time_ = rand_int(40,60);
						if(monster *mon_ = BaseSummon(MON_SCHEMA_EYE, time_, true, true, 3, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level,3);
						}
					}
					break;
				}
			}
		}
		break;
	case GT_EIRIN:
		{
			random_extraction<int> rand_;
			rand_.push(0,66);//������̱�
			rand_.push(1,33);//��������
			switch(rand_.pop())
			{
			case 0:
				{
					random_extraction<potion_type> potion_;	
					potion_.push(PT_DOWN_STAT);
					potion_.push(PT_PARALYSIS);
					potion_.push(PT_SLOW);
					potion_.push(PT_CONFUSE);
					potion_.push(PT_POISON);
					potion_type p_ = potion_.choice();
					printarray(true,false,false,CL_small_danger,3,"���̸��� ��ſ��� ������ ",potion_iden_string[p_],"������ �Կ���!");
					drinkpotion(p_, false);
				}
				break;
			case 1:
				{
					printarray(true,false,false,CL_small_danger,1,"���̸��� ����� ���� ������ ������ �ߴ�!");
					you.SetEirinHeal(you.GetMaxHp()*rand_int(70,80)/100,true);
					for(int i=0;i<3;i++)
						you.StatUpDown(-rand_int(1,4),randA(2)?(randA(1)?STAT_STR:STAT_DEX):STAT_INT,true);
				}
				break;
			}
		}
		break;
	case GT_YUYUKO:
		{
			random_extraction<int> rand_;
			rand_.push(0,50);//����
			switch(rand_.pop())
			{
			case 0:
				{
					int i = rand_int(2 + randA(you.level / 10), 5);
					i += randA(you.level/3); 
					for(; i>0 ; i--)
					{
						if(monster *mon_ = BaseSummon(MON_GHOST, rand_int(20,40), true, true, 4, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level-1,4.0f,1.5f);
							mon_->image = &img_mons_ghost[randA(2)];
						}
					}
					summon_ = true;
					printarray(true,false,false,CL_yuyuko,1,"�����ڴ� ����� �ֺ��� ������ �����Ҵ�!");
				}
				break;
			}
		}
		break;
	case GT_SATORI:
		break;
	case GT_TENSI:
		tensi_action();
		break;
	case GT_SEIJA:
		{
			god_type god_ = GT_SEIJA;
				
			while(god_ == GT_SEIJA || god_ == GT_SATORI)
				god_ = (god_type)rand_int(GT_BYAKUREN,GT_LILLY);
			printarray(true,false,false,CL_seija,3,"�����ڴ� ��Ű� ",GetGodString(god_),"�� ���踦 �̰����ߴ�!");
			
			you.PunishUpDown(rand_int(3,4),god_);
		}
		break;
	case GT_LILLY:
		{
			random_extraction<int> rand_;
			rand_.push(0,35);//��ȭ
			rand_.push(1,65);//������ȯ
			switch(rand_.pop())
			{
			case 0:		
				{
					you.SetForceStrong(false, rand_int(20,40),true);
					printarray(true,false,false,CL_lilly,1,"������ ����� ���� ���ѾҴ�!");
				}
				break;
			case 1:
				{
					random_extraction<int> id_;
					id_.push(MON_FAIRY_GREEN,50);
					id_.push(MON_FAIRY_BLUE,30);
					id_.push(MON_FAIRY_RED,20);
					int i =rand_int(3,5); 
					for(; i>0 ; i--)
					{
						int level_ =rand_int(rand_int(1,you.level),you.level); 

						if(monster *mon_ = BaseSummon(id_.choice(), rand_int(60,120), true, true, 3, NULL, you.position, SKD_OTHER, -1))
						{						
							while(level_ > mon_->level)
							{
								mon_->LevelUpdown(1,6.0f,1.0f);
								switch(mon_->id)
								{
								case MON_FAIRY_GREEN:
									if(mon_->level >= 5)
										mon_->ChangeMonster(MON_FAIRY_GREEN_WARRIOR,0);
									break;
								case MON_FAIRY_BLUE:
									if(mon_->level >= 7)
										mon_->ChangeMonster(MON_FAIRY_BLUE_MAGICIAN,0);
									break;
								case MON_FAIRY_RED:
									if(mon_->level >= 8)
										mon_->ChangeMonster(MON_FAIRY_RED_COMMANDER,0);
									break;
								case MON_FAIRY_GREEN_WARRIOR:
									if(mon_->level >= 12)
										mon_->ChangeMonster(MON_FAIRY_HERO,0);
									break;
								case MON_FAIRY_BLUE_MAGICIAN:
									if(mon_->level >= 10)
										mon_->ChangeMonster(MON_FAIRY_SOCERER,0);
									break;
								case MON_FAIRY_RED_COMMANDER:
									if(mon_->level >= 13)
										mon_->ChangeMonster(MON_FAIRY_GREEN_WARRIOR,0);
									break;
								}
							}
							mon_->SetForceStrong(true, 100,false);
						}
					}
					summon_ = true;
					printarray(true,false,false,CL_lilly,1,"������ ��ſ��� �������� ������ ������ ��ȯ�ߴ�!");
				}
				break;
			}
		}
		break;
	case GT_MIKO:
	{
		random_extraction<int> rand_;
		rand_.push(0, 33);//���
		rand_.push(1, 33);//����
		rand_.push(2, 33);//���Ȼ��ѱ�
		int time_ = rand_int(80, 160);
		env[current_level].MakeNoise(you.position, 20, NULL);
		switch (rand_.pop())
		{
		case 0:
		{
			printarray(false, false, false, CL_miko, 1, "���ڴ� ����� ü���� ���Ѿư���! ");
			you.SetBuff(BUFFSTAT_HP, BUFF_DUPLE, -(you.GetMaxHp()/2), time_);
		}
		break;
		case 1:
		{
			printarray(false, false, false, CL_junko, 1, "���ڴ� ����� �������ߴ�! ");
			you.SetSlow(time_);
		}
		break;
		case 2:
		{
			printarray(false, false, false, CL_junko, 1, "���ڴ� ����� ������ ���߾���! ");
			you.SetBuff(BUFFSTAT_RF, BUFF_MIKO_RF_MINUS, -1, time_);
			you.SetBuff(BUFFSTAT_RC, BUFF_MIKO_RC_MINUS, -1, time_);
		}
		break;
		}
	}
	break;
	case GT_OKINA:
		{
			random_extraction<int> rand_;
			rand_.push(0, 50);//����, ����� ��ȯ
			rand_.push(1, 50);//ü��, ���°���
			switch (rand_.pop())
			{
			case 0:
				{
					int isYourSight = 0;
					deque<monster*> dq;
					for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
					{
						if (it->isLive() && !it->isUserAlly())
						{
							if (it->isYourShight()){
								isYourSight++;
							}
						}
					}

					if (isYourSight)
					{
						printarray(true, false, false, CL_okina, 1, "��Ű���� ����� �ҷ��´�!");

						int time_ = rand_int(40, 60);
						if (monster *mon_ = BaseSummon(MON_MAI2, time_, true, true, 3, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level, 6);
						}
						if (monster *mon_ = BaseSummon(MON_SATONO, time_, true, true, 3, NULL, you.position, SKD_OTHER, -1))
						{
							mon_->LevelUpdown(you.level, 6);
						}
						break;
					}
					else
					{
						//�ƹ��� �þ߳��� ������ ����� �θ����ʴ´�(�ǹ̰� ����)
						you.HpUpDown(-you.GetMaxHp() / 2, DR_EFFECT);
						if(!you.pure_mp)
							you.MpUpDown(-you.max_mp / 2);
						printarray(true, false, false, CL_okina, 1, "��Ű���� �г�� ����� ü�°� ������ ����Ǿ���!");
						break;
					}
				}
				break;
			case 1:
				{
					you.HpUpDown(-you.GetMaxHp()/2, DR_EFFECT);
					if (!you.pure_mp)
						you.MpUpDown(-you.max_mp/2);
					printarray(true, false, false, CL_okina, 1, "��Ű���� �г�� ����� ü�°� ������ ����Ǿ���!");
					break;
				}
				break;
			}
		}
		break;
	case GT_JUNKO:
		{
			random_extraction<int> rand_;
			rand_.push(0, 33);//��ȭ
			rand_.push(1, 33);//����
			rand_.push(2, 33);//���Ȼ��ѱ�
			int time_ = rand_int(50, 80);
			you.SetPureTurn(randA(1)?30:20, time_);
			switch (rand_.pop())
			{
			case 0:
			{
				printarray(false, false, false, CL_junko, 1, "��ȣ�� ����� ���� ��ȭ�Ͽ���! ");
				you.SetForceStrong(false, time_, true);
			}
			break;
			case 1:
			{
				printarray(false, false, false, CL_junko, 1, "��ȣ�� ����� �ӵ��� ���ѾҴ�! ");
				you.SetSlow(time_);
			}
			break;
			case 2:
			{
				printarray(false, false, false, CL_junko, 1, "��ȣ�� ����� �ɷ�ġ�� ���ѾҴ�! ");
				for (int i = 0; i<3; i++)
					you.StatUpDown(-rand_int(1, 2), randA(2) ? (randA(1) ? STAT_STR : STAT_DEX) : STAT_INT, true);
			}
			break;
			}
		}
		break;
	}

	if (summon_) {
		if (you.god == GT_SEIJA 
			&& pietyLevel(you.piety) >= 2
			&& !you.GetPunish(GT_SEIJA)) {
			printlog(seija_summon_buff(), true, false, false, CL_seija);
			you.SetHaste(rand_int(20, 40));
		}
	}


	return false;		
}


void createGold(coord_def c, int num) {
	rand_rect_iterator rit(c, 2, 2);
	int i = num;
	for (; !rit.end() && i> 0; rit++)
	{
		if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y))
		{
			int rand_ = randA(2);
			env[current_level].MakeFloorEffect(coord_def(rit->x, rit->y), &img_effect_gold_floor[rand_], &img_effect_gold_floor[rand_],  FLOORT_GOLD, rand_int(20, 30), &you);
		}
		i--;
	}
}

void joonRandomBuff() {
	//����
	//��
	//��ø
	//����
	//AC����
	random_extraction<int> rand_;

	rand_.push(0);
	rand_.push(1);
	rand_.push(2);
	rand_.push(3);
	rand_.push(4);
	//rand_.push(5);

	switch (rand_.pop())
	{
	case 0:
		you.SetHaste(rand_int(30, 60));
		break;
	case 1:
		you.SetMight(rand_int(30, 60));
		break;
	case 2:
		you.SetAgility(rand_int(30, 60));
		break;
	case 3:
		you.SetClever(rand_int(30, 60));
		break;
	case 4:
		printlog("����� �ܴ�������. ", false, false, false, CL_white_blue);
		you.SetBuff(BUFFSTAT_AC, BUFF_JOON_AC, 8, rand_int(30, 60));
		break;
	}
	enterlog();
}
bool sionResurrection() {
	random_extraction<char> rand_;
	for (auto it = you.item_list.begin(); it != you.item_list.end(); it++) {
		if ((*it).type == ITM_POTION || (*it).type == ITM_SCROLL) {
			for(int i = 0; i < it->num; i++)
				rand_.push(it->id);
		}
	}

	if (randA(99) < rand_.GetSize() * 10)
	{
		
		for (int i = 0; i < 10; i++)
		{
			char key_ = rand_.pop();
			list<item>::iterator it;
			for (it = you.item_list.begin(); it != you.item_list.end(); it++)
			{
				if ((*it).id == key_)
				{
					you.DeleteItem(it, 1);
					break;
				}
			}
			if (rand_.GetSize() == 0)
				break;
		}
		return true;
	}
	return false;
}

void godAutoPickUp(god_type god_, bool belive_) {

	switch (god_)
	{
	case GT_BYAKUREN:
	case GT_ERROR:
	case GT_NONE:
	case GT_JOON_AND_SION:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
		break;
	case GT_YUUGI:
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_ALCOHOL] = belive_;
		break;
	case GT_SHIZUHA:
	case GT_HINA:
		break;
	case GT_YUKARI:
		iden_list.autopickup[IDEN_CHECK_SCROLL_START + SCT_BLINK] = !belive_;
		iden_list.autopickup[IDEN_CHECK_SCROLL_START + SCT_TELEPORT] = !belive_;
		//�����̵�
		break;
	case GT_EIRIN:
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_POISON] = belive_;
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_PARALYSIS] = belive_;
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_CONFUSE] = belive_;
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_SLOW] = belive_;
		iden_list.autopickup[IDEN_CHECK_POTION_START + PT_DOWN_STAT] = belive_;
		//���� �� �ֿ�
		break;
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_SEIJA:
	case GT_LILLY:
	case GT_MIKO:
	case GT_OKINA:
	case GT_JUNKO:
	default:
		break;
	}
}


int getMikoPiety(int kind) {
	switch (kind){
		case 0:
			return 4;
		case 1:
			return 10;
		case 2:
			return 30;
		case 3:
			return 100;
		case 4:
			return 200;
	}
	return 0;
}


void printReEnter()
{
	if (you.GetPunish(you.god)) {
		printlog("ȯ���⿡ ���ƿ°� ȯ���Ѵ�!", true, false, false, CL_normal);
		return;
	}
	switch (you.god)
	{
	case GT_BYAKUREN:
		printlog("������: �������. �ŵ���", true, false, false, CL_white_blue);
		break;
	case GT_JOON_AND_SION:
		switch (randA(1))
		{
		case 0:
			printlog("�ҿ�: ��Ǭ�� ������� ��� �о�����ڰ�!", true, false, false, CL_joon);
			break;
		case 1:
			printlog("�ÿ�: �����...", true, false, false, CL_sion);
			break;
		}
		break;
	case GT_KANAKO:
		//�糪������ ��� �ʿ�
		printlog("ī����: ���Ӿ��� ������ �ž��� ���̵��� �Ͽ���!", true, false, false, CL_help);
		break;
	case GT_SUWAKO:
		printlog("������: ������! ��վ�����", true, false, false, CL_swako);
		break;
	case GT_MINORIKO:
		printlog("�̳븮��: �� ���� ������ �ູ��!", true, false, false, CL_warning);
		break;
	case GT_MIMA:
		printlog("�̸�: �е����� ��������!", true, false, false, CL_green);
		break;
	case GT_SHINKI:
		printlog("��Ű���� P�� ��ȥ��!", true, false, false, CL_warning);
		break;
	case GT_YUUGI:
		printlog("�����: �� ���� ��븦 ã�ƶ�!", true, false, false, CL_yuigi);
		break;
	case GT_SHIZUHA:
		printlog("������: �α� �ִ� �༮�� ��� �׿���...", true, false, false, CL_small_danger);
		break;
	case GT_HINA:
		printlog("����: �׷� �׶��۾��� ��� �ϰھ�", true, false, false, CL_hina);
		break;
	case GT_YUKARI:
		printlog("��ī��: ���ƿԱ���", true, false, false, CL_yukari);
		break;
	case GT_EIRIN:
		printlog("���̸�: ���ο� ����ü�� �ʿ�������", true, false, false, CL_small_danger);
		break;
	case GT_YUYUKO:
		printlog("������: ���� ���� �ҷ�?", true, false, false, CL_yuyuko);
		break;
	case GT_SATORI:
		printlog("���丮: ������� �پ� �뼼��. ������ �����ϱ��.", true, false, false, CL_danger);
		break;
	case GT_TENSI:
		printlog("�ٽ�: õ��� ������! �� �� ��հ� ���ٰ���?", true, false, false, CL_tensi);
		break;
	case GT_SEIJA:
		printlog("������: ��, ���������� Ȱ���� ���ô�!", true, false, false, CL_seija);
		break;
	case GT_LILLY:
		printlog("����: ���̿���!", true, false, false, CL_lilly);
		break;
	case GT_MIKO:
		printlog("����: ����� ����� ������ ����!", true, false, false, CL_miko);
		break;
	case GT_OKINA:
		printlog("��Ű��: �� ���迡�� ���� ���ν�Ű���� ", true, false, false, CL_okina);
		break;
	case GT_JUNKO:
		printlog("��ȣ: ��ƿ�, ���� �ִ°�?", true, false, false, CL_junko);
		break;
	case GT_ERROR:
	case GT_NONE:
	default:
		printlog("ȯ���⿡ ���ƿ°� ȯ���Ѵ�!", true, false, false, CL_normal);
		break;
	}


}










bool God_PraySpeak()
{
	int level_ = pietyLevel(you.piety);
	switch (you.god)
	{
	case GT_BYAKUREN:
		switch (level_)
		{
		default:
		case 0:
			printlog("������: �ƾ�, ���� ���迡 ���� ������", true, false, false, CL_white_blue);
			return true;
		case 1:
			printlog("������: �츮 ���� �ΰ��� �䱫�� ���������ʴ´�ϴ�.", true, false, false, CL_white_blue);
			return true;
		case 2:
			printlog("������: ��� ������ ������ �����ϰ� ������.", true, false, false, CL_white_blue);
			return true;
		case 3:
			printlog("������: ����� ����� ����� �����Ŷ��ϴ�.", true, false, false, CL_white_blue);
			return true;
		case 4:
			printlog("������: ��� ������ �����ڶ� ���� �ܷ��ؾ��մϴ�.", true, false, false, CL_white_blue);
			return true;
		case 5:
			printlog("������: ����� ��� �ұ��� ����ħ�� ��ο��� ���ϼ���.", true, false, false, CL_white_blue);
			return true;
		case 6:
			printlog("������: �������. ������ ��ó���� ���ڿ�", true, false, false, CL_white_blue);
			return true;
		}
	case GT_ERROR:
	case GT_NONE:
		return false; 
	case GT_JOON_AND_SION:
		switch (level_)
		{
		default:
		case 0:
			if (randA(1))
				printlog("�ҿ�: ���ο� ȣ��... �ƴ� ���� �Գ�!", true, false, false, CL_joon);
			else
				printlog("�ÿ�: �������...", true, false, false, CL_sion);
			return true;
		case 1:
			if (randA(1))
				printlog("�ҿ�: �� �� ���� �ᵵ �ȴٰ�", true, false, false, CL_joon);
			else
				printlog("�ÿ�: ���� �����?", true, false, false, CL_sion);
			return true;
		case 2:
			if (randA(1))
				printlog("�ҿ�: ���� �� ��ǰ �ڵ���� �������� ���̾�", true, false, false, CL_joon);
			else
				printlog("�ÿ�: �� �������� �츮�� �ϰ��ִ°ž�?", true, false, false, CL_sion);
			return true;
		case 3:
			if (randA(1))
				printlog("�ҿ�: ��? ī�尡 �ʿ���?", true, false, false, CL_joon);
			else
				printlog("�ÿ�: �ҿ��̿������ �?", true, false, false, CL_sion);
			return true;
		case 4:
			if (randA(1))
				printlog("�ҿ�: �Ƴ��� �����ٿ� ��� �����!", true, false, false, CL_joon);
			else
				printlog("�ÿ�: �ֱٿ� ����ĵ� ��ſ�", true, false, false, CL_sion);
			return true;
		case 5:
			if (randA(1))
				printlog("�ҿ�: �츮���̶�� ��θ� �о���� �� �־�!", true, false, false, CL_joon);
			else
				printlog("�ÿ�: ���� ������ �� �� ������?", true, false, false, CL_sion);
			return true;
		case 6:
			printlog("�ҿ�&�ÿ�: �����־��� �ڸ��� ���� ��������! ", false, false, false, CL_joon_and_sion);
			return true;
		}
	case GT_KANAKO:
		if (you.char_name.name.compare("�糪��") == 0)
		{
			printlog("ī����: ������ ��������. �糪��", true, false, false, CL_help);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog("ī����: ���Ӿ��� ������ �ž��� �����ϰŶ�", true, false, false, CL_help);
			return true;
		case 1:
			printlog("ī����: ���� �θ� �̴� �����ΰ�?", true, false, false, CL_help);
			return true;
		case 2:
			printlog("ī����: �ž��� �����ϴ� �ڴ� ��� �����϶�", true, false, false, CL_help);
			return true;
		case 3:
			printlog("ī����: �״��� �žӿ��� �����μ� ��������", true, false, false, CL_help);
			return true;
		case 4:
			printlog("ī����: ���� �ž��� ���� �� ��Ʈ������", true, false, false, CL_help);
			return true;
		case 5:
			printlog("ī����: �Ѷ� ������ ������ �ҷȴ� ��. �� ���� ������������", true, false, false, CL_help);
			return true;
		case 6:
			printlog("ī����: ������ ������ ȭ���̿� ������ ���ư���!", true, false, false, CL_help);
			return true;
		}
	case GT_SUWAKO:
		if (you.char_name.name.compare("�糪��") == 0)
		{
			printlog("������: �䱫��ġ�� �ð��̾� �糪��!", true, false, false, CL_swako);
			return true;
		}
		switch (randA(4))
		{
		default:
		case 0:
			printlog("������: ��? �� �ҷ���?", true, false, false, CL_swako);
			return true;
		case 1:
			printlog("������: �ֱ��� �ŵ����� ���ϴ°� ���ٴϱ�", true, false, false, CL_swako);
			return true;
		case 2:
			printlog("������: ���� ��ӽ��ΰ� ��������~", true, false, false, CL_swako);
			return true;
		case 3:
			printlog("������: �� �� ����϶��~", true, false, false, CL_swako);
			return true;
		case 4:
			printlog("������: ����������, ����� ���� ���״ϱ�", true, false, false, CL_swako);
			return true;
		}
	case GT_MINORIKO:
		switch (level_)
		{
		default:
		case 0:
			printlog("�̳븮��: ��ŵ� ������ ���Ѱž�?", true, false, false, CL_warning);
			return true;
		case 1:
			printlog("�̳븮��: ��Ȯ�� ���ؼ� �׸�ŭ�� ����� �ʿ��Ѱž�", true, false, false, CL_warning);
			return true;
		case 2:
			printlog("�̳븮��: ������ ���� �Ƹ��ٿ� �����̾�!", true, false, false, CL_warning);
			return true;
		case 3:
			printlog("�̳븮��: ���� �� ������ �Ը��� �¾�?", true, false, false, CL_warning);
			return true;
		case 4:
			printlog("�̳븮��: ��� ����ϰ� �ϰ� �ٴ���?", true, false, false, CL_warning);
			return true;
		case 5:
			printlog("�̳븮��: �׾ƿø� ��� ����� ǳ������ �����Ҷ���!", true, false, false, CL_warning);
			return true;
		case 6:
			printlog("�̳븮��: ������ �絵��! ���ư��� ������ �������� �˷���!", true, false, false, CL_warning);
			return true;
		}
	case GT_MIMA:
		if (you.char_name.name.compare("������") == 0)
		{
			printlog("�̸�: �������̳�, �� ������ �־�?", true, false, false, CL_green);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog("�̸�: ���ο� �Ա� ������ΰ�?", true, false, false, CL_green);
			return true;
		case 1:
			printlog("�̸�: ��� �ֱٿ� ���ڴ� �����ʾҾ����� Ư�����̽���", true, false, false, CL_green);
			return true;
		case 2:
			printlog("�̸�: ������ �⺻�� �Ŀ���. ����ε���", true, false, false, CL_green);
			return true;
		case 3:
			printlog("�̸�: �����ʽ�. ���� ������ ���� �̱��.", true, false, false, CL_green);
			return true;
		case 4:
			printlog("�̸�: �� �ñ��� ������ �ñ��Ѱ�?", true, false, false, CL_green);
			return true;
		case 5:
			printlog("�̸�: �� �̻� ���� �������� ������ ����.", true, false, false, CL_green);
			return true;
		case 6:
			printlog("�̸�: ������ ������ ���� �����!", true, false, false, CL_green);
			return true;
		}
	case GT_SHINKI:
		switch (level_)
		{
		default:
		case 0:
			printlog("��Ű���� P�� ��ȥ��! ", true, false, false, CL_warning);
			return true;
		}
	case GT_YUUGI:
		switch (level_)
		{
		default:
		case 0:
			printlog("�����: �� �󸶳� ������?", true, false, false, CL_yuigi);
			return true;
		case 1:
			printlog("�����: ���� ���� �پ ���� ������ ������!", true, false, false, CL_yuigi);
			return true;
		case 2:
			printlog("�����: �� �������� �ϴ� �༮�� �Ⱦ�", true, false, false, CL_yuigi);
			return true;
		case 3:
			printlog("�����: ���� ���� ���� �� �־�?", true, false, false, CL_yuigi);
			return true;
		case 4:
			printlog("�����: �װ� �ο�°� ���� ���� ��ſ!", true, false, false, CL_yuigi);
			return true;
		case 5:
			printlog("�����: ���߿� ���� �ѹ� �ο�����������?", true, false, false, CL_yuigi);
			return true;
		case 6:
			printlog("�����: ������ ���ڸ��� �ʴ����״� �� ��Ƽ� ���ƿ����!", true, false, false, CL_yuigi);
			return true;
		}
	case GT_SHIZUHA:
		switch (level_)
		{
		default:
		case 0:
		case 1:
		case 2:
			printlog("�����ϴ� ������ ����� �����ִ�.", true, false, false, CL_warning);
			return true;
		case 3:
		case 4:
			printlog("�����ϴ� ����� �⵵�� ���� ��������.", true, false, false, CL_warning);
			return true;
		case 5:
			printlog("������: ...���� �츮���� ���ʾ�...", true, false, false, CL_small_danger);
			return true;
		case 6:
			printlog("������: ���� �α���ǥ�� �� ��Ź�Ұ�", true, false, false, CL_small_danger);
			return true;
		}
	case GT_HINA:
		switch (level_)
		{
		default:
		case 0:
			printlog("����: �� ���� ����� ������", true, false, false, CL_hina);
			return true;
		case 1:
			printlog("����: ���ݾ� ���ݾ� �׶��� �س�����", true, false, false, CL_hina);
			return true;
		case 2:
			printlog("����: �׶��� �����ϴ� �༮���� �����ص� ����", true, false, false, CL_hina);
			return true;
		case 3:
			printlog("����: ���� �� ���� ���ָ� �������� ��", true, false, false, CL_hina);
			return true;
		case 4:
			printlog("����: ������ �׵��� ������ ���� �ɾ������ʾҾ�", true, false, false, CL_hina);
			return true;
		case 5:
			printlog("����: ���ָ� ������ �۾��� �ܷο����", true, false, false, CL_hina);
			return true;
		case 6:
			printlog("����: �ʴ� ���� ������ ���� �־��ٰ���?", true, false, false, CL_hina);
			return true;
		}
	case GT_YUKARI:
		if (you.char_name.name.compare("���̹�") == 0)
		{
			printlog("��ī��: ȯ������ ������ ������ ���� ����ϰ�����?", true, false, false, CL_yukari);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog("��ī��: ����� ���� ���ο� �Ľ�?", true, false, false, CL_yukari);
			return true;
		case 1:
			printlog("��ī��: ȯ������ ��� ���� ������", true, false, false, CL_yukari);
			return true;
		case 2:
			printlog("��ī��: ����� �����۾��� �ʿ���", true, false, false, CL_yukari);
			return true;
		case 3:
			printlog("��ī��: ������ ������ �˱����ؼ��� �� ���� ������ �ʿ���", true, false, false, CL_yukari);
			return true;
		case 4:
			printlog("��ī��: ��Ÿ� �ϰ��־�. ������ �ʿ��ϸ� ����", true, false, false, CL_yukari);
			return true;
		case 5:
			printlog("��ī��: �� ���� ������ �� �̻� ����� ������ ���ǹ���", true, false, false, CL_yukari);
			return true;
		case 6:
			printlog("��ī��: ��Ÿ��� �� �� �ִ� ���̾�", true, false, false, CL_yukari);
			return true;
		}
	case GT_EIRIN:
		if (you.char_name.name.compare("���ڿ�") == 0)
		{
			printlog("���̸�: �ֱٿ��� ���ִ԰��� �������� ��������?", true, false, false, CL_small_danger);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
			printlog("���̸�: ���ο� ����ü�� �ʿ���...", true, false, false, CL_small_danger);
			return true;
		case 1:
			printlog("���̸�: �� ���� �Ծ�� ���ۿ��� ������?", true, false, false, CL_small_danger);
			return true;
		case 2:
			printlog("���̸�: �� �� ���� ǥ���� �ʿ���", true, false, false, CL_small_danger);
			return true;
		case 3:
			printlog("���̸�: ���� �˸� �൵ ���� �� �ִ°ž�", true, false, false, CL_small_danger);
			return true;
		case 4:
			printlog("���̸�: ���ۿ��� �η���������. ȿ���� Ȯ����", true, false, false, CL_small_danger);
			return true;
		case 5:
			printlog("���̸�: ���� �� ���̶�� �������������ž�", true, false, false, CL_small_danger);
			return true;
		case 6:
			printlog("���̸�: �̰��� ���� ���ο� ����̾�", true, false, false, CL_small_danger);
			return true;
		}
	case GT_YUYUKO:
		if (you.char_name.name.compare("���ڿ�") == 0)
		{
			printlog("������: �ҷκһ��� ����� �� �� �ϴ°ž�?", true, false, false, CL_yuyuko);
			return true;
		}
		switch (level_)
		{
		default:
		case 0:
		case 1:
			printlog("������: ���ο� �Ĵ��� �����̴�?", true, false, false, CL_yuyuko);
			return true;
		case 2:
		case 3:
			printlog("������: �� �� �����ϰ� �־ ����.", true, false, false, CL_yuyuko);
			return true;
		case 4:
			printlog("������: ������ ������ �Ϳ����ʾ�?", true, false, false, CL_yuyuko);
			return true;
		case 5:
			printlog("������: ģ������ ������ ���?", true, false, false, CL_yuyuko);
			return true;
		case 6:
			printlog("������: ���� �״��� ��ȥ�� �Բ�����", true, false, false, CL_yuyuko);
			return true;
		}
	case GT_SATORI:
		switch (level_)
		{
		default:
		case 0:
		case 1:
			printlog("���丮�� ��ſ��� ū ������ ����. ", true, false, false, CL_warning);
			return true;
		case 2:
			printlog("���丮�� ��ſ��� �̼�������. ", true, false, false, CL_warning);
			return true;
		case 3:
			printlog("���丮: �ֿϵ����� ����� ������ ���� ������.", true, false, false, CL_danger);
			return true;
		case 4:
			printlog("���丮�� ����� ���ٵ����. ", true, false, false, CL_warning);
			return true;
		case 5:
			printlog("���丮: ������ ���� �Ը��� �³���?", true, false, false, CL_danger);
			return true;
		case 6:
			printlog("���丮: ������ ���� ��å�Ϸ� ���� ��������?", true, false, false, CL_danger);
			return true;
		}
	case GT_TENSI:
		switch (randA(9))
		{
		default:
		case 0:
			printlog("�ٽ�: ����! ���� �ٺ�!", true, false, false, CL_tensi);
			return true;
		case 1:
			printlog("�ٽ�: �⵵�ϴ°Ÿ����� ������ �ٶ�°� �ʹ� �̱������� �ʾ�?", true, false, false, CL_tensi);
			return true;
		case 2:
			printlog("�ٽ�: ����ִ� ���� ���°ž�?", true, false, false, CL_tensi);
			return true;
		case 3:
			printlog("�ٽ�: �������� ������ �����Ѻ���...", true, false, false, CL_tensi);
			return true;
		case 4:
			printlog("�ٽ�: �ѹ��� �� �������ϸ� ���� ��������!", true, false, false, CL_tensi);
			return true;
		case 5:
			printlog("�ٽô� ��ſ��� ���� ������.", true, false, false, CL_warning);
			return true;
		case 6:
			printlog("�ٽô� ����� ���� Ű��Ű�� �����ִ�.", true, false, false, CL_warning);
			return true;
		case 7:
			printlog("�ٽô� ����� ���� �����ѵ� ��ǰ�ϰ� �ִ�.", true, false, false, CL_warning);
			return true;
		case 8:
			printlog("�ٽô� ����� �⵵�� �����ߴ�.", true, false, false, CL_warning);
			return true;
		case 9:
			printlog("�ٽô� �갥ġ�� ����� �Ӹ��� ���ȴ�.", true, false, false, CL_warning);
			return true;
		}
	case GT_SEIJA:
		switch (level_)
		{
		default:
		case 0:
		case 1:
			printlog("�����ڴ� ����� �⵵�� �����ߴ�.", true, false, false, CL_warning);
			return true;
		case 2:
			printlog("�����ڴ� ��ſ� ū ������ ����δ�.", true, false, false, CL_warning);
			return true;
		case 3:
			printlog("�������� ǥ���� �״��� �� ���ƺ��δ�.", true, false, false, CL_warning);
			return true;
		case 4:
			printlog("������: ��Ģ�̶� ��Ƴ��´ٸ� �װɷ� �����", true, false, false, CL_seija);
			return true;
		case 5:
			printlog("������: ���������� ��Ȱ�� ������ ���?", true, false, false, CL_seija);
			return true;
		case 6:
			printlog("������: �츰 �ְ��� ��Ʈ�ʾ� ģ��!", true, false, false, CL_seija);
			return true;
		}
	case GT_LILLY:
		return false;
	case GT_MIKO:
		return false;
	case GT_OKINA:
		switch (level_)
		{
		default:
		case 0:
			printlog("��Ű��: �װ� �� ��������� �ô��� �׽�Ʈ�غ��ž�.", true, false, false, CL_okina);
			return true;
		case 1:
			printlog("��Ű��: ������ ����, ���� �׽�Ʈ�� ä���� ��������", true, false, false, CL_okina);
			return true;
		case 2:
			printlog("��Ű��: ���� ����� �׻� �˷����߸� �Ѵ�", true, false, false, CL_okina);
			return true;
		case 3:
			printlog("��Ű��: �� ���� ������ �� ���� �޵��� �ض�", true, false, false, CL_okina);
			return true;
		case 4:
			printlog("��Ű��: ���� ���̿� ������ �ع�����ٱ� �������̴�", true, false, false, CL_okina);
			return true;
		case 5:
			printlog("��Ű��: �Ƿ� �� ���Ͽ� �´� ����α���. �հ��̴�!", true, false, false, CL_okina);
			return true;
		case 6:
			printlog("��Ű��: ����! ������! ���϶�! ����� ������ ������ �޾ƶ�!", true, false, false, CL_okina);
			return true;
		}
	case GT_JUNKO:
		switch (level_)
		{
		default:
		case 0:
			printlog("��ȣ: ��ƿ� �����ִ°�!", true, false, false, CL_junko);
			return true;
		}
	}
	return false;

}