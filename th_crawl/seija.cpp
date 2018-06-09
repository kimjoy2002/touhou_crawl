//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: seija.cpp
//
// ����: ������ ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "seija.h"
#include "environment.h"
#include "enum.h"
#include "skill_use.h"
#include "key.h"
#include "god.h"
#include "note.h"
#include "weapon.h"
#include "potion.h"
#include "evoke.h"
#include "book.h"




bool seija_gift()
{
	int seija_level_ = 7-pietyLevel(you.piety);

	if(seija_level_ == 6)
	{
		printlog(seija_talk(GT_NONE, seija_level_), true,false,false,CL_seija);
		
		MoreWait();
		
		printarray(true,false,false,CL_danger,3,"����� ", GetGodString(you.god), "�κ��� ��������!");
	
		//you.PunishUpDown(30, you.god , true);
	
		char temp[200];
		sprintf_s(temp,200,"%s�κ��� ��������.",GetGodString(you.god));
		AddNote(you.turn,CurrentLevelString(),temp,CL_small_danger);

		for(int level_ = pietyLevel(you.piety);level_>=0;level_--)
			GetGodAbility(level_, false);
		you.Ability(SKL_ABANDON_GOD,true,true);
		you.god = GT_NONE;

		item_infor t;
		env[current_level].MakeItem(you.position, makeitem(ITM_MISCELLANEOUS, 0, &t, EVK_MAGIC_HAMMER));
		printlog("...�����ڰ� ������ ������ �����ġ�� �ְ� ����.", true, false, false, CL_dark_good);
		return true;
	}

	int temp = you.Ability(SKL_SEIJA_GIFT,true,true);
	
	if(temp)
	{	
		printlog("������ ���������� �ʹ� �����ð��� ������ ������ ��ҵǾ���.",true,false,false,CL_small_danger);
		MoreWait();
		printlog(seija_talk(GT_NONE, seija_level_), true,false,false,CL_seija);
		you.StepUpDownPiety(-1);
		return true;
	}
	else
	{
		printlog("���� �����ڷκ��� ������ �䱸�� �� �ִ�. ",false,false,false,CL_seija);
		printlog("(aŰ�� ������ ��û)",true,false,false,CL_help);
		MoreWait();

		you.Ability(SKL_SEIJA_GIFT,true,false);
		return true;

	}
}
const char* seija_god_string(int god, int num) {

	switch (god)
	{
	case GT_BYAKUREN:
		switch (num) {
		case 0: return "����: ������ ����å�� �� �� �޽��ϴ�.";
		case 1: return "������ ¡���� ����� �������ϰų� �����̳� ������ �Ͻ������� ���ҽ�ŵ�ϴ�.";
		case 2: return "���� ������ ¡���߿� �׻� ���� Ȯ���� ������ ������ �����մϴ�.";
		}
	case GT_JOON_AND_SION:
		switch (num) {
		case 0: return "�ҿ�&�ÿ�: ������ ������ �ణ �޽��ϴ�.";
		case 1: return "�ҿ°� �ÿ��� ����� �������� �����ϰ� �Ҿ�������� ����ϴ�.";
		case 2: return "���� ¡���� ��ſ��� ������ ���ǵǾ� ü��, �����̳� �Ŀ��� �Ұ� ����ϴ�.";
		}
	case GT_KANAKO:
		switch (num) {
		case 0: return "ī����: ������ ������ ���⸦ ������ �޽��ϴ�.";
		case 1: return "ī���ڴ� ¡���� ��ſ��� �������� �ְų� �¹ٽö� �ȾƼ� ���� ���ų�";
		case 2: return "������ �������� ���͵��� ����� ������ �ҷ����̱⵵ �մϴ�.";
		}
	case GT_SUWAKO:
		switch (num) {
		case 0: return "������: ����ī�带 �� �� �޽��ϴ�.";
		case 1: return "�����ڴ� ��ſ��� ���ָ� �ɾ� ������ �� ���� ���Ӱ� ���� �ɰų�";
		case 2: return "����� �ֺ��� �������� ���������� ��ȯ�մϴ�.";
		}
	case GT_MINORIKO:
		switch (num) {
		case 0: return "�̳븮��: �ټ��� ������ �޽��ϴ�.";
		case 1: return "�̳븮�ڴ� ¡���� ����� �Ŀ��� �������� ����ų� �ǰ��� ���Ѿ�";
		case 2: return "���� �ɸ����ϱ⵵�ϸ� �ɷ�ġ�� �Ͻ������� ���ҽ�ų �� �ֽ��ϴ�.";
		}
	case GT_MIMA:
		switch (num) {
		case 0: return "�̸�: �̸��� ���μ��� �޽��ϴ�.";
		case 1: return "�̸��� ¡���� ��ſ��� �پ��� �Ӽ��� �ı������� ���� �����ϴ�.";
		case 2: return "���� �̸��� ¡���� �޴� ���ȿ� ��� ������ �Ŀ��� ������ �˴ϴ�.";
		}
	case GT_SHINKI:
		switch (num) {
		case 0: return "��Ű: ���ݵη縶�� ��� �޽��ϴ�.";
		case 1: return "��Ű�� ¡���� ����� �ֺ��� �������� �����ε��� ��ȯ�մϴ�.";
		case 2: return "���� ¡���߿� ���� P�������� ����߸� Ȯ���� ����ϴ�.";
		}
	case GT_YUUGI:
		switch (num) {
		case 0: return "�����: ������ ���� ���� �޽��ϴ�.";
		case 1: return "������ ����� ������ ���ϰ� ����ų� �������� �Բ� ��������ų�";
		case 2: return "��� �ֺ��� ������ ���ϸ� ��ȯ�ϱ⵵ �մϴ�.";
		}
	case GT_SHIZUHA:
		switch (num) {
		case 0: return "������: ��ǳ�귣���� ���⸦ �޽��ϴ�.";
		case 1: return "�����ϴ� ¡���� ����� ȥ����Ű�ų� ū �������� �ְų� ū ������ �Բ�";
		case 2: return "����� ���ӽ�ŵ�ϴ�. ��ǳ���� ������ ū ������ ���� ȭ���� �������ϴ�.";
		}
	case GT_HINA:
		switch (num) {
		case 0: return "����: ������ ������ ���� �޽��ϴ�.";
		case 1: return "������ ¡���� ��ſ� ���׺Ұ����� ���� ������ �ɰų� ����� ��� ���ָ�";
		case 2: return "�ɱ⵵�ϸ� ȥ���� �̴ϴ�. ¡���߿� ���������� �׻� ������ ���ɼ��� ����ϴ�.";
		}
	case GT_YUKARI:
		switch (num) {
		case 0: return "��ī��: �����̵� �Ҹ�ǰ�� ������ �޽��ϴ�.";
		case 1: return "��ī���� ¡���� ȥ���� �Բ� �����̵��� ��Ű�ų� �����̵��� ������Ų�� �ֺ���";
		case 2: return "������ �ҷ����⵵�ϸ� ������ ���� ��ȯ��Ű�⵵ �մϴ�.";
		}
	case GT_EIRIN:
		switch (num) {
		case 0: return "���̸�: ������ ���� ���̸� �޽��ϴ�.";
		case 1: return "���̸��� ��ſ� ���� ������ ���̰ų� ��ſ��� ������ ������ �Ͽ� ���ۿ���";
		case 2: return "����ϴ�. ���� ¡���߿� ����� ���ô� ������ ȿ���� ���� Ȯ���� ������ϴ�.";
		}
	case GT_YUYUKO:
		switch (num) {
		case 0: return "������: ������ �ߵ��۵��� �޽��ϴ�.";
		case 1: return "�����ڴ� ¡���� ����� �ֺ��� ���� �������� ���ɵ��� ��ȯ��ŵ�ϴ�.";
		case 2: return "��ȯ�Ǵ� ���ɵ��� ����� ���������� �������ϴ�.";
		}
	case GT_SATORI:
		switch (num) {
		case 0: return "���丮: �ĺ��η縶�� ������ �޽��ϴ�.";
		case 1: return "���丮�� ����� ¡������ ������ ���𰡸� ã�� �������� ������ �Ѹ��ϴ�.";
		case 2: return "�� �����ð����� �ѷ����� �������� ������ �����۰� ��ü�Ǿ� �����˴ϴ�.";
		}
	case GT_TENSI:
		switch (num) {
		case 0: return "�ٽ�: ������ �������� ���� �޽��ϴ�.";
		case 1: return "�ٽô� ¡�������� ����� ������ ������ �� ���Դϴ�.";
		case 2: return "�� ¡���� ����� �ٽ��� �ൿ���� ���� �� ���� ȿ���� Ȯ���� �����ϴ�.";
		}
	case GT_SEIJA:
		switch (num) {
		case 0: return "������: ���κ��� ���� ���� ����!";
		case 1: return "�Ƹ� �� �������� �����Դϴ�.";
		case 2: return "";
		}
	case GT_LILLY:
		switch (num) {
		case 0: return "����: ź�� ��ġ�� �޽��ϴ�";
		case 1: return "������ ¡���� ����� �ֺ��� �������� �������� ��ȯ�ϰų�";
		case 2: return "����� ��ȭ���� �Ͻ������� ���ݷ°� ������ �Ŀ��� �������� ����ϴ�.";
		}
	case GT_MIKO:
		switch (num) {
		case 0: return "����: ��Ƽ��Ʈ ���並 �ϳ� �޽��ϴ�.";
		case 1: return "���ڴ� ¡���� ����� �ִ�ü���� �Ͻ������� �������� ���̰ų�";
		case 2: return "������ �ɰų� ȭ���� �ñ������� �Ͻ������� �Ѵܰ� ����ϴ�.";
		}
	case GT_OKINA:
		switch (num) {
		case 0: return "��Ű��: �ణ�� ���� �η縶���� �޽��ϴ�.";
		case 1: return "��Ű���� ����� �ֺ��� �������� ����� ��ȯ�Ͽ� �ֺ��� ���͵���";
		case 2: return "�����ϰų� ����� ü�°� ������ ����մϴ�.";
		}
	case GT_JUNKO:
		switch (num) {
		case 0: return "��ȣ: ���Ⱝȭ�� ����ȭ �η縶���� ���� �޽��ϴ�.";
		case 1: return "��ȣ�� ¡���� ����� ��ȭ��Ű�ų� ������ ��Ű�ų� ����� �ɷ�ġ��";
		case 2: return "�Ͻ������� ���ҽ�ŵ�ϴ�.";
		}
	case GT_ERROR:
	case GT_NONE:
	default:
		switch (num) {
		case 0: return "���׽�: �̰��� �����ϸ� �׽��ϴ�.";
		case 1: return "��κ��� �����Դϴ�.";
		case 2: return "";
		}
	
	}
	return "����";
}


void seija_real_gift(int key_)
{	
	switch(key_)
	{
		case GT_BYAKUREN: //������ å 2~4��
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{
					random_extraction<int> rand_;

					for(int j=SKT_SPELLCASTING+1; j<SKT_EVOCATE;j++)
					{
						rand_.push(i, you.GetSkillLevel(j, false)>15?15:(you.GetSkillLevel(j, false)>1?5:1));
					}
					book_list book_ = BOOK_FIRST;
					for(int j=SKT_SPELLCASTING+1; j<SKT_EVOCATE;j++)
					{
						book_ = SchoolToBook((skill_type)rand_.pop());
						if(!iden_list.books_list[book_])
						{
							break;
						}
					}
					
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, book_));
				}
			}
			break;
		case GT_KANAKO: //������ ���� 3~5��
			{
				for(int i = rand_int(3,5); i > 0; i--)
				{
					kanako_gift(false);
				}
			}
			break;
		case GT_SUWAKO: //������ ����ī�� 2~4��
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_SPELL, 0, &t, randA(SPC_V_MAX-1)));
				}
			}
			break;
		case GT_MINORIKO: //���� 10~30��
			{
				for(int i = 10; i > 0; i--)
				{	
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_FOOD, 0, &t, 1));
				}
			}
			break;
		case GT_MIMA: //�̸��� ���μ�
			{
				for(int i = 1; i > 0; i--)
				{	
					item_infor t;
					item *it = env[current_level].MakeItem(you.position,makeitem(ITM_BOOK, 0, &t, BOOK_TEST_ANNIHILATE));
					it->Identify();
				}
			}
			break;
		case GT_SHINKI: //���ݵη縶�� 2~4��
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{	
					item_infor t;
					item *it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_SOUL_SHOT));
					it->Identify();
				}
			}
			break;
		case GT_YUUGI:
			{
				for(int i = rand_int(2,4); i > 0; i--)
				{	
					armour_gift(false, false, false);
				}
			}
			break;
		case GT_SHIZUHA:
			{
				random_extraction<int> rand_;

				for(int i=SKT_SHORTBLADE;i<=SKT_SPEAR;i++)
				{
					rand_.push(i-SKT_SHORTBLADE, you.GetSkillLevel(i, false) +1);
				}
				item_infor t;
				item* it = env[current_level].MakeItem(you.position,makeitem((item_type)(rand_.pop()), randA(2)?1:0, &t));
				it->value5 = WB_AUTUMN;
			}
			break;
		case GT_HINA:
			{
				for(int i = rand_int(2,3); i > 0; i--)
				{	
					jewelry_gift(false, true, false);
				}
			}
			break;
		case GT_YUKARI://�����η縶�� 3~7�� �����̵��η縶�� 0~3��
			{
				for(int i = rand_int(3,7); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_TELEPORT));
					it->Identify();
				}
				for(int i = rand_int(0,3); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_BLINK));
					it->Identify();
				}
			}
			break;
		case GT_EIRIN: //���� 6~12��
			{
				for(int i = rand_int(6,12); i > 0; i--)
				{					
					potion_type type_= goodbadpotion(randA(2)>1?1:(randA(60)?2:3));
					
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_POTION, 0, &t,(int)type_));
				}
			}
			break;
		case GT_YUYUKO: //������ �ߵ��� 2��
			{
				random_extraction<int> rand_;

				for (int i = 0; i < EVK_MAX; i++) {
					if (i != EVK_MAGIC_HAMMER && i != EVK_SKY_TORPEDO && i != EVK_CAMERA
						) {
						rand_.push(i);
					}
				}
				for(int i = 2; i > 0; i--)
				{
					item_infor t;
					env[current_level].MakeItem(you.position,makeitem(ITM_MISCELLANEOUS, 0, &t,rand_.pop()));
				}
			}
			break;
		case GT_SATORI: //�ĺ��η縶�� 7~12��
			{
				for(int i = rand_int(7,12); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_SCROLL, 0, &t, SCT_IDENTIFY));
					it->Identify();
				}
			}
			break;
		case GT_TENSI: //������ ������ 4~8��... ���� ���� 1����!!
			{				
				for(int i = rand_int(4,8); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,CreateFloorItem(0,&t));
				}
			}
			break;
		case GT_LILLY: //ź����ġ
			{				
				for(int i = rand_int(4,7); i > 0; i--)
				{	
					item_infor t;
					item* it = env[current_level].MakeItem(you.position,makeitem(ITM_THROW_TANMAC, 0, &t));
				}
			}
			break;
		case GT_JOON_AND_SION:
		{
			for (int i = 2; i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_AMULET, 0, &t));
			}
		}
		break;
		case GT_MIKO:
		{
			for (int i = 1; i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_ARMOR_CLOAK, 0, &t));
				MakeArtifact(it, 3); //�ٸ� �����ۺ��� ȿ���� ����
			}
		}
		break;
		case GT_OKINA:
		{
			for (int i = rand_int(2,4); i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_SCROLL, 0, &t, SCT_SANTUARY));
				it->Identify();
			}
		}
		break;
		case GT_JUNKO:
		{
			for (int i = rand_int(3, 6); i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_SCROLL, 0, &t, SCT_ENCHANT_WEAPON_1));
				it->Identify();
			}
			for (int i = rand_int(2, 3); i > 0; i--)
			{
				item_infor t;
				item* it = env[current_level].MakeItem(you.position, makeitem(ITM_SCROLL, 0, &t, SCT_ENCHANT_ARMOUR));
				it->Identify();
			}
		}
		break;
	}
}

const char* seija_summon_buff() {

	switch (randA(9))
	{
	case 0:
		return "������: ������!";
	case 1:
		return "������: �������� �»��� ���ٰ�!";
	case 2:
		return "������: ���� ������ �����״ϱ� �� �����ĺ����";
	case 3:
		return "������: �� ����� �������ϱ� ����������!";
	case 4:
		return "������: �ο� ������ �ƴ���?";
	case 5:
		return "������: ���� �߰��� �پ���";
	case 6:
		return "������: �������� �߰��ڵ��ϻ��̾�, �������ڰ�";
	case 7:
		return "������: ���� �о���̴ٴ� ��Ģ�ƴϾ�?";
	case 8:
		return "������: �׷����� ������� �츱 ���� �� ����";
	case 9:
		return "������: �ʳ� �������� �ʳ�!";
	}

	return "������: �̴�� ������!";
}


const char* seija_talk(god_type god_, int piety)
{
	if(piety >= 1 && piety <= 3)
	{
		switch(god_)
		{
		
		case GT_JOON_AND_SION:
			switch(randA(3))
			{
			case 0:
				return "������: �� �༮���� ������ ���� ��������������� �ʶ� ����?";
			case 1:
				return "������: �� �༮���� ������ �������̴� ���� �� ���ƾ �Ҿ�����ž�";
			case 2:
				return "������: ������ �̿� �޴� �ֵ��� ��ġ������ ������";
			case 3:
				return "������: ���� ������ ������� ���� �༮���̶� ������";
			}
			break;
		case GT_BYAKUREN:
			switch(randA(3))
			{
			case 0:
				return "������: �䱫, �ΰ����� ����ϰ�? ������ �������� ������ ���±�!";
			case 1:
				return "������: ���� ������ ��ġ�������� ���� �ܶ� �����־��ٰ�! �İ�� ������ �и���!";
			case 2:
				return "������: �� ���� �־��� ����å���̾�. ������ٰ� �߸����� �ϳ��� ¢� ȥ���ٴϱ�";
			case 3:
				return "������: �� ���� �����¿��� ������ �����Ⱑ �귯��������... �� �����Ŀ���!";
			}
			break;
		case GT_KANAKO:
			switch(randA(3))
			{
			case 0:
				return "������: ���� ��ó�� ���簣�� �پ ���̾���. ������ ������ ���������� ���̾�";
			case 1:
				return "������: �� ���� ������ ���� ������? ���Ѵٸ� �ְ�����";
			case 2:
				return "������: �� �� ���̾�. ������ �̽����ٰ� ������";
			case 3:
				return "������: �� ������κ��� ����ġ�°� �� �������... �� ���غ����!";
			}
			break;
		case GT_SUWAKO:
			switch(randA(3))
			{
			case 0:
				return "������: �̷� �����̵� ���̾����ž�? �׷��� �꺸�����ʾҴµ�";
			case 1:
				return "������: �� ���� �������� �� ������. ���� �������� �ʴµ� ���̾�";
			case 2:
				return "������: �� ��ӽ�. ���⺸�� �����ϴٰ�";
			case 3:
				return "������: �� ���ǿ� ����� ������µ� �����ھ�?";
			}
			break;
		case GT_MINORIKO:
			switch(randA(3))
			{
			case 0:
				return "������: �� ������Ȱ�̶� ���� ì�ܸԾ����. ���� �� �����ٰ�";
			case 1:
				return "������: �� ���� ������ ���������̾�, �����ٱ� �����ϰ� �־��ٰ�";
			case 2:
				return "������: �� �������� �� ǳ���� �ſ���... ���? �̸��� ������?";
			case 3:
				return "������: ����ͳ�����? �� ��������";
			}
			break;
		case GT_MIMA:
			switch(randA(3))
			{
			case 0:
				return "������: �ñ��� ������ �����ִٰ� �ϴ���. �����ϰ� �����";
			case 1:
				return "������: �̰� �� ����ũ���� ������ �����ִ� å�ΰ�? ��Ģ�����̶�� �� ����";
			case 2:
				return "������: �Ƿ�? �Ƿ��� �� å�̶��? ������ ���ֹ޴°� �ƴϰ���?";
			case 3:
				return "������: ���� ���� ���� �ֱ��� �׷�. �̰� �� ���� å����";
			}
			break;
		case GT_SHINKI:
			switch(randA(3))
			{
			case 0:
				return "������: ������ ��? �� ����ϰ� ���� �༮��?";
			case 1:
				return "������: �������� ���谡 �����ؼ� ����ٰ�. ��г��ڰ� ���� ������ �����ߴµ�";
			case 2:
				return "������: ����� ���� �ұ� ���ٰ�. Ȥ�� ���ԵǸ� �����ϴ°� ������";
			case 3:
				return "������: �������� �����Ӹ������� �Ѿƿ������... �̰� ���״� �� ������ �ٷ�?";
			}
			break;
		case GT_YUUGI:
			switch(randA(3))
			{
			case 0:
				return "������: ������ ���� ���ϰ� �; ������. �ִ� ���� ����ġ���";
			case 1:
				return "������: �� ���ʵ��� ���ϵ��� ������ �ϳ���. ������ �ɸ��� �ݹ��̶��";
			case 2:
				return "������: ������ �ʿ���������. ������ �ָ��� �������� �°� ��Ƽ���� ������";
			case 3:
				return "������: �� ���ϵ鿡�� �̿�޴� ���ݰ��Ƽ� ���̾�. �� ��� ����������� �ϴµ�";
			}
			break;
		case GT_SHIZUHA:
			switch(randA(3))
			{
			case 0:
				return "������: ��ǳ�� �������� ���߰� ����. �ʵ� �׷��� ��������?";
			case 1:
				return "������: ���簨�� ������ ���� ���̾���. �� �޾�";
			case 2:
				return "������: �۽� �̰� �����ö� ���� �� ���Ѻ����ִٴ� ������ ����� ���̾�?";
			case 3:
				return "������: ���� �ο��� ���� ��ڿ��� ��°� �ְ���. �ʵ� �׷��� ��������?";
			}
			break;
		case GT_HINA:
			switch(randA(3))
			{
			case 0:
				return "������: ��ħ �̷� ���ֹ��� ������ ���� �ʿ������. ���� �ٰ�";
			case 1:
				return "������: �� ���� ������ �������� ���̱��ϴµ�, ���� �Ҹ���ĥ�Ű��� �Ⱦ�";
			case 2:
				return "������: �Ϻη� �ڽ��� ��� ���ָ� �Ŵ� ����� �ִٰ�? ���� ����";
			case 3:
				return "������: �ʿ��ϸ� �ְ����� ���ִ� �����϶�� ";
			}
			break;
		case GT_YUKARI:
			switch(randA(3))
			{
			case 0:
				return "������: �� ��г��� �䱫���� ���� �����ǰ� ���� �ʾҴµ�";
			case 1:
				return "������: �� ���ǵ��� ��ġ�������� �� �䱫�� ���ڰ��־���";
			case 2:
				return "������: ����ĥ���� �� �����̵� �����۸��Ѱ� ����. �����ϰ� �����";
			case 3:
				return "������: �����̵��� ���������� �ֹ̰� ���ϴܸ��̾�. ����";
			}
			break;
		case GT_EIRIN:
			switch(randA(3))
			{
			case 0:
				return "������: �� ����� ������ ���Ŀ� ������̾�. ���� ���������� �� �𸣰�����";
			case 1:
				return "������: ����鼭? �� �׷��� ���� ���� ������ �ִ� ����?";
			case 2:
				return "������: �� ����� �濡 ó�� ���� �̻��� ���赵���� �ܶ��־���. �����غ����� ��������";
			case 3:
				return "������: ��Ȳ�� Ÿ���ϴµ��� ���ุŭ ����Ѱ� ����. �ʵ� �����϶��!";
			}
			break;
		case GT_YUYUKO:
			switch(randA(3))
			{
			case 0:
				return "������: �� �� ��ܿ� �ٽ� �ö󰡰� ���� �ʴ���";
			case 1:
				return "������: �� ������ ��ġ�� �������� ������ ����� ���̴���";
			case 2:
				return "������: ������ �ٷ�� ����? �ұ��ϳ�";
			case 3:
				return "������: ���������� ���� ������ �� �ְ���? �ϴ´ٰ� ��Ʈ��";
			}
			break;
		case GT_SATORI:
			switch(randA(3))
			{
			case 0:
				return "������: ������ �д� �䱫��... ��� ���� �䱫����";
			case 1:
				return "������: �ֿϵ����� �⸣�°��� ����ϴ°��� �� �𸣰ڳ�";
			case 2:
				return "������: ���� ���غ��������� �༮�̾���. �ٽ� ������ ������";
			case 3:
				return "������: ����ŭ �̿� �޴� �༮�̶��? ���� �����ǽ��� �ȴ������� ���̾�";
			}
			break;
		case GT_TENSI:
			switch(randA(3))
			{
			case 0:
				return "������: �̷� �༮�� �ϴ� ����� �ִٰ�? ���� �� ��Ư�ϱ���";
			case 1:
				return "������: �ϴÿ��� ���� ���� �ʰ� �����϶�";
			case 2:
				return "������: �̷� �⵿��ϰ� �ʿ��Ѱž�? �ʵ� �� Ư���ϱ�";
			case 3:
				return "������: õ���� ����ġ�� ���κ��̴� ���� ���̾���";
			}
			break;
		case GT_LILLY:
			switch(randA(3))
			{
			case 0:
				return "������: ����? �Ǹ� ����? ���� ���� �ȵǴ� ��⸦ �ϴ°ɱ�?";
			case 1:
				return "������: ������ ������ �������~ �׿��� �׿��� ��� �����Ա��� �� ���̾�";
			case 2:
				return "������: ������ ������ ������ ���� �𸣰����� ���ĿԾ�. ��Ե� �Ẹ���";
			case 3:
				return "������: �ֺ��� �����ʰ� �����ش�� �����̾���. ������ �̰�";
			}
			break;
		case GT_MIKO:
			switch (randA(3))
			{
			case 0:
				return "������: �� �߳� �༮�� �Ƴ��� ���並 �ϳ� ��������";
			case 1:
				return "������: �� �� ������ ��� ���䰡 �־ ������, �̰� �� �ٰ�";
			case 2:
				return "������: ������ ������ ô�ص� ������ ������ �༮����. �� �� �� �־�";
			case 3:
				return "������: ���� ����? �Ķ� ����? �׷��� �� �𸣰ڴµ�";
			}
			break;
		case GT_OKINA:
			switch (randA(3))
			{
			case 0:
				return "������: �� �̻��� ���� �ߴ� ������ ���������� ���� ���ٰ�";
			case 1:
				return "������: �׷� ���� ���ϵ��� �ɱ��";
			case 2:
				return "������: �� �������� ���� �Ͻ������� ������ �ȴٴ��� �� �Ẹ���";
			case 3:
				return "������: �� �ڿ� ���� �ֱ淡 ������ �̰� ���Ŀ���";
			}
			break;
		case GT_JUNKO:
			switch (randA(3))
			{
			case 0:
				return "������: ���� ������ ��ȭ�� ���� �߿�����?";
			case 1:
				return "������: ��� ���� ���δٰ� �߾�Ÿ��ٴ� ��г��� ���̳�";
			case 2:
				return "������: ��ȭ�� �ູ�̶��? �������� �������Ѵٸ� ���� �ҿ��ΰ���?";
			case 3:
				return "������: ������ ���� ����ġ���� �츮���� �Ӹ��� �������� ����";
			}
			break;
		}
	}

	switch(piety)
	{
	case 0:
		switch(randA(4))
		{
		case 0:
			return "������: ���ο� ������������ ź���̱�! ȯ���Ѵ�!";
		case 1:
			return "������: �츰 �ְ��� ���� �ɰž�!";
		case 2:
			return "������: ��븸 ���� �� �༮�鿡�� �ѹ� �����ڰ�!";
		case 3:
			return "������: �ϱػ��� �����̴�!";
		case 4:
			return "������: ���ڿ��� ����! ���ڿ��� ����!";
		}
		break;		
	case 1:
	case 2:
	case 3:
		switch(randA(5))
		{
		case 0:
			return "������: ����? �������� �ʿ����������ž�? �� �ڽŰ� ���� �ʾ�";
		case 1:
			return "������: ���� ������ �����ʾƵ� �� �����ٰ���?";
		case 2:
			return "������: ����� �ʿ�� ���µ� ������";
		case 3:
			return "������: �ʿ���ٴ°ɷ� �˰ھ� ��Ʈ��";
		case 4:
			return "������: ��ȸ���������";
		case 5:
			return "������: �׷� �� ������ ���� ������ ����";
		}
		break;		
	case 4:
		if(god_ == GT_NONE)
		{
			switch(randA(1))
			{
			case 0:
				return "������: ������ �ʿ����?";
			case 1:
				return "������: �ⲯ �� ������ �شٴµ� �� �ȴٴ°���?";
			}
		}
		else
		{			
			switch(randA(6))
			{
			case 0:
				return "������: (�̰� ������ �� �´°� �ƴұ�?)";
			case 1:
				return "������: �� ���п� ������� �Դٰ� ������";
			case 2:
				return "������: ��... ���� �޾�";
			case 3:
				return "������: (�̰� �� �Ʊ�...)";
			case 4:
				return "������: (�� ���Ǻ��� �� �༮�� �� �����ҰŰ��� ������...)";
			case 5:
				return "������: ���� �̰� �� �Ʊ��... ��, �ƹ��͵� �ƴϾ�";
			case 6:
				return "������: (�����غ��� ���� ���ظ� ���� ���ݾ� �̰�)";
			}	
		}
		break;	
	case 5:		
		if(god_ == GT_NONE)
		{
			switch(randA(1))
			{
			case 0:
				return "������: �̺�, ���غ�. ���� �Ӽ��� �ִ°���?";
			case 1:
				return "������: �װ� �� �����ϴ��� �� ���� ����";
			}
		}
		else
		{
			switch(randA(6))
			{
			case 0:
				return "������: ...";
			case 1:
				return "�����ڴ� �ɱⰡ �����ѵ� �ϴ�.";
			case 2:
				return "������: ...���� �ƹ��� �����ص� ���� ���ؾ�";
			case 3:
				return "������: (�׷����� ������ �ŵ����� �ִٰ� ��Ŵ��ϴ� ���� �ִٰ� ����°�)";
			case 4:
				return "������: ��... �� �� ���� ¥�����°�";
			case 5:
				return "������: (���� �̿���ϰ� �ִ°� �ƴұ� �̰�?)";
			case 6:
				return "������: (��� ���ϱ� ���� ����Ѵ�... �̰� �� ��������)";
			}
		}
		break;	
	case 6: //�������� ���
		switch(randA(6))
		{
		case 0:
			return "������: �� ���. �� ���ӱ��� �Ƹ��������! ������ ����� ����!";
		case 1:
			return "������: ���� �� ���̾���. �� ������ ���� �ƴϾ�!";
		case 2:
			return "������: �ʵ� �� ����� �����̾���? �ƴϾ�! ���� �� ����ҰŴ�!";
		case 3:
			return "������: �̿���ϴ� ������ �༮�� �ٷ� �ʴ�! �� ��û��! ���� �� �̿��Ѱž�!";
		case 4:
			return "������: �ʵ� �� ������ Ž���� �°���? ���� �� �Ӽ��� �� �� �˰�?";
		case 5:
			return "������: �Ƹ��������� ����� ����! �� ó������ �̿���ѰŻ�����!";
		case 6:
			return "������: �׵��� �� ��Ʈ�ʶ�� �ߴ����� �� �������̴�. �ֳĸ� �� �Ƹ�������ϱ�!";
		}
		break;			
	case 7:		//�����ڸ� ���
		switch(randA(3))
		{
		case 0:
			return "������: ��? �װ� �� �����? �װ� �׷��� ���� �ɰŰ���?";
		case 1:
			return "������: �׷���. ���� ����� �ʿ���� �ſ���. �� �����ϰ� �����ž�!";
		case 2:
			return "������: �� �Ƹ������� �̿��Ϸ��ϴٴ� ���� ũ����!";
		case 3:
			return "������: ��ȸ�ϰ� ���ָ�!";
		}
		break;	
	}

	
	return "������: ...";
}
