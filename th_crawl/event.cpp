//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: event.cpp
//
// ����: �̺�Ʈ ó���� ���� �Լ�, Ŭ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "event.h"
#include "environment.h"
#include "save.h"
#include "rect.h"
#include "key.h"
#include "mon_infor.h"
#include "skill_use.h"
#include "floor.h"
#include "beam.h"

int EventOccur(int id, events* event_);

void bamboo_count(int num);
void arena_event(int num);
bool skill_summon_namaz2(int power, bool short_, unit* order, coord_def target);

events::events()
:id(0),position(),type(EVT_ABOVE),prev_sight(false), value(0)
{
}

events::events(int id_, coord_def position_, event_type type_, int count_)
:id(id_),position(position_),type(type_),prev_sight(false), count(count_), value(0)
{
	start();
}



void events::SaveDatas(FILE *fp)
{	
	SaveData<int>(fp, id);
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<event_type>(fp, type);
	SaveData<int>(fp, count);
	SaveData<bool>(fp, prev_sight);
	SaveData<int>(fp, value);
}
void events::LoadDatas(FILE *fp)
{
	LoadData<int>(fp, id);
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<event_type>(fp, type);
	LoadData<int>(fp, count);
	LoadData<bool>(fp, prev_sight);
	LoadData<int>(fp, value);
}

int events::start()
{	
	switch(id)
	{
	case EVL_VIOLET:
		{
			int violet_range = min(10, (count+1) / 2) ;
			env[current_level].MakeViolet(position, violet_range, true);
		}
		break;
	case EVL_SANTUARY:
	{
		int santuary_range = min(10, (count + 1) / 2);
		env[current_level].MakeSantuary(position, santuary_range, true);
	}
	break;
	default:
		break;
	}
	return 0;
}
int events::action(int delay_)
{
	bool is_sight = false;
	if(env[current_level].isInSight(position))
		is_sight = true; //���� ���� ���̴���

	if(count>=0)
	{
		count--;
		if(type == EVT_COUNT && count<=0)
		{			
			if(EventOccur(id,this))
				return 0;
		}
	}
	if(type == EVT_SIGHT && is_sight && !prev_sight)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_ABOVE && position == you.position)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_APPROACH_SMALL && distan_coord(position,you.position)<=2)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_APPROACH_MIDDLE && distan_coord(position,you.position)<=4)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(type == EVT_ALWAYS)
	{
		if(EventOccur(id,this))
			return 0;
	}
	if(is_sight)
		prev_sight = true;
	else if(prev_sight)
		prev_sight = false;
	return 1;
	
}






int EventOccur(int id, events* event_) //1�� �����ϰ� ������
{
	enterlog();
	switch (id)
	{
	case 1:
		printlog("ī���ڴ� ���ߴ� : ���� ������ �� ������ OŰ��, �������� CŰ�� ���� �� ����.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ����Ű�� �о �ڵ����� ���⵵ �Ѵܴ�.", true, false, false, CL_warning);
		return 1;
	case 2:
		printlog("ī���ڴ� ���ߴ� : Ű�е��� ����Ű�� y u b nŰ�� �밢���� ����������.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : oŰ�� ������ Ž�� ���� �������� �ڵ����� �̵�����.", true, false, false, CL_warning);
		return 1;
	case 3:
		printlog("ī���ڴ� ���ߴ� : ,�� g�� ������ �������� �ֿ��� �����غ���.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : wŰ�� ����, WŰ�� ������, iŰ�� ����, dŰ�� �������.", true, false, false, CL_warning);
		return 1;
	case 4:
		printlog("ī���ڴ� ���ߴ� : ũ���� ������ ������ ��������, ������ ���� �ε����� ��.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� ���� 1:1�� �ο�°� �����ϴ� ������� �����Ϸ�.", true, false, false, CL_warning);
		return 1;
	case 5:
		printlog("ī���ڴ� ���ߴ� : �׻� �ο��� �Ŀ� ü���� ä��� ������ ���̷�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : .Ű�� 1�� �޽���, 5Ű�� 100�� �޽��� �� �� �־�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : mŰ�� ������ ������ â���� ���� ��ų ���� ������ ���� �� �־�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : �Ŀ��� �������, �ɷ»��, ���������� ��¿� ������ ����.", true, false, false, CL_warning);
		return 1;
	case 6:
		printlog("ī���ڴ� ���ߴ� : ����� ���������� >Ű, �ö�ö� <Ű�� �ö�� �� �־�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : �̹� ������ ������ ���� ������ ���� ������ ��������.", true, false, false, CL_warning);
		return 1;
	case 7:
		if (you.power > 150)
			you.PowUpDown(-(you.power - 150), true);
		printlog("ī���ڴ� ���ߴ� : �Ŀ��� 2.00���ϰ� �Ǹ� ���ݷ��� �����ع����ܴ�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� ��Ƽ� ������ P���� �԰ų� ������ ���ؼ� ȸ���� ������.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : eŰ�� ������ ���� ������ �Ŀ��� ȸ���� �� �־�.", true, false, false, CL_warning);
		return 1;
	case 8:
		printlog("ī���ڴ� ���ߴ� : ���Ÿ� ������ ������ ������. ������ �ֿ�����.", true, false, false, CL_warning);
		return 1;
	case 9:
		printlog("ī���ڴ� ���ߴ� : ���Ÿ� ���⸦ �������� FŰ�� ������ ���� ���� ���.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : fŰ�� �غ�Ǿ��ִ� ź���� �ٷ� ���� �� �ִܴ�.", true, false, false, CL_warning);
		return 1;
	case 10:
		printlog("ī���ڴ� ���ߴ� : ȿ���� �� �� ���� ��ű��� �η縶����. �ϴ� ����غ���.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : �ϴ� ������ �ֿ��� PŰ�� ������. RŰ�� ���� �� �־�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : �η縶���� �д°� rŰ��. ����â�� �߸� ������ ����غ�.", true, false, false, CL_warning);
		return 1;
	case 11:
		printlog("ī���ڴ� ���ߴ� : ����, ����� ������ ���� ������ �ȵ���. dŰ�� ���� �� �־�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ������ ���̴±�. ������ qŰ�� ���� �� �־�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� �Ա����� ȿ���� �� �� ���� ���� ���� ȿ���� ����.", true, false, false, CL_warning);
		return 1;
	case 12:
		you.GiveSkillExp(SKT_SPELLCASTING, 20, true);
		you.GiveSkillExp(SKT_CONJURE, 100, true);
		printlog("ī���ڴ� ���ߴ� : ������ ������ å���� �ֹ��� ���� ���������.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : �ϴ� å�� �ֿ��� MŰ�� ������ź���� �������.", true, false, false, CL_warning); \
			return 1;
	case 13:
		printlog("ī���ڴ� ���ߴ� : ������ ����ϱ����ؼ� zŰ�� ZŰ�� ������ ����Ҽ��־�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ����� ����������� �Ȱ��ܴ�! �� ���� �������� ��ƺ���.", true, false, false, CL_warning);
		return 1;
	case 14:
		printlog("ī���ڴ� ���ߴ� : <Ű�� �ٽ� �������� �ö� �� �־�.", true, false, false, CL_warning);
		return 1;
	case 15:
		printlog("�ż��� ����� ������ �ִ�.", true, false, false, CL_normal);
		return 1;
	case 16:
		printlog("ī���ڴ� ���ߴ� : �ο�� �Ŀ� 5Ű�� �޽� ����ϰ�����? ���� �ɷȴٸ� Ǯ���.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ������ ã���� ������ pŰ�� �⵵�� �� �� �־�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : �� �����̴ϱ� �ѹ� �Ͼ��. �ϰ��� ^Ű�� ������ ����.", true, false, false, CL_warning);
		return 1;
	case 17:
		printlog("ī���ڴ� ���ߴ� : aŰ�� ������ �Ǵ��� �ѹ� ����ؼ� �ο�����.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : �Ǵ��� ���� �žӽ��� �Ǹ� ���� �þ�Ե���.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : Ư�� �� �Ǵ��� �žӽ��� ������ �Ҹ��ϴϱ� �����ؼ� ��.", true, false, false, CL_warning);
		return 1;
	case 18:
		printlog("ī���ڴ� ���ߴ� : �Ÿ��� �žӽ��� ��� ����� �ٸ��� �Ⱦ��ϴ� �͵� �ִܴ�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� ���� ���� ���϶����� �žӽ��� ���ݾ� �����ܴ�.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : �� ���� ���� ���� ���̸� �ڵ����� �žӽ��� ������.", true, false, false, CL_warning);
		return 1;
	case 19:
		printlog("ī���ڴ� ���ߴ� : �䱫 ����̱���. �Ӹ����� �̸��� ������ ���� ���ӵ����.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���ӵ���� ���� ������ ������. ���ܰ� ����� ��������.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : �׵��� ���� �����۰� ����� Ȱ���ؼ� ���� �� ������ �����غ���.", true, false, false, CL_warning);
		return 1;
	case 20:
		printlog("ī���ڴ� ���ߴ� : Ʃ�丮���� ���⼭ ���̶��� �糪��.", true, false, false, CL_warning);
		printlog("ī���ڴ� ���ߴ� : ���� ���ӿ����� ������ �η����������Ŷ�!", true, false, false, CL_warning);
		return 1;
	case 21:
		printlog("������ ���Ⱑ ��������. �����̶� ������!", true, false, false, CL_small_danger);
		return 1;
	case 22:
		printlog("���� �и� ����� ���ұ�. ���� ������ ��!", true, false, false, CL_help);
		return 1;
	case 23:
		printlog("�� ���� ������ �̱��̱�! �ⱸ�� ã�ƾ� �Ѵ�. �ƴϸ� ���ο� ��Ҹ� ã������..?", true, false, false, CL_small_danger);
		return 1;
	case 24:
		return 1;
	case 25:
		printlog("����ũ�ѿ��� ��� ���⸦ �Ѽ��̳� ������� �� �� �ֽ��ϴ�.", true, false, false, CL_warning);
		printlog("��, ��� ����� ������� �鶧 ȿ���� ���� �������ϴ�.", true, false, false, CL_warning);
		printlog("�ܰ��� ������� �ᵵ �г�Ƽ�� ������ �ٿ�¡�� ��ս� ū �г�Ƽ�� �ֽ��ϴ�.", true, false, false, CL_warning);
		return 1;
	case 26:
		printlog("������� ������ ������ �������ְ� �׿ܿ� �������� ���а� �ֽ��ϴ�.", true, false, false, CL_warning);
		printlog("���ʿ� ������ ���� ����г�Ƽ�� �����Ͽ� �ջ�Ǿ� ����â�� ǥ�õ˴ϴ�.", true, false, false, CL_warning);
		return 1;
	case 27:
		you.GiveSkillExp(SKT_ARMOUR, 1200, true);
		you.GiveSkillExp(SKT_SHIELD, 300, true);
		printlog("�� ����г�Ƽ�� ���� ����,���� ��ų�� ���� ���ҵ˴ϴ�.", true, false, false, CL_warning);
		printlog("�ڼ��� ��ġ�� ������ i�� ������ �ڼ��� ��ġ�� Ȯ���غ�����.", true, false, false, CL_warning);
		return 1;
	case 28:
		printlog("����ũ�ѿ� Ȱ�̳� ��ο�ǰ��� ���Ÿ� ���Ⱑ ������ ��� ������ ���� �� �ֽ��ϴ�.", true, false, false, CL_warning);
		printlog("��ô��ܰ�, ��ô��â, ö���� ����ε� �� �� ������ ��ô�����ε� ��밡���մϴ�.", true, false, false, CL_warning);
		printlog("�Ҹ� ź���� ��ô�� ���� ��� ź�� ��ų�� ������ �޽��ϴ�.", true, false, false, CL_warning);
		return 1;
	case 29:
		printlog("����ũ�ѿ� ����� ������ ���� ��ſ� ����� P��� �������� �����մϴ�.", true, false, false, CL_warning);
		printlog("�ƻ�� ���������ʴ� ��� 2ĭ���Ϸ� �������� �����г�Ƽ�� �ֽ��ϴ�.", true, false, false, CL_warning);
		printlog("��� ���� ����Ȯ���� P���� ����߸��� �̰��� ������ P�� ȸ���˴ϴ�.", true, false, false, CL_warning);
		return 1;
	case 30:
		printlog("����ī��� ������ �ϵ带 ��ü�ϴ� �������Դϴ�.", true, false, false, CL_warning);
		printlog("{�ߵ�}�� ���� ���� P�� �Ҹ��Ͽ� �ߵ��ϴ� �������� ��Ҹ�ߵ����Դϴ�.", true, false, false, CL_warning);
		printlog("�Ѵ� V�� �ߵ��� �����ϸ� �ߵ���ų�� ������ �޾� ���������ϴ�.", true, false, false, CL_warning);
		return 1;
	case 31:
		printlog("������ ������ �ƹķ��� ��ü�Ǵ� �������Դϴ�.", true, false, false, CL_warning);
		printlog("�� ��� ȿ���� ������ ���� ���͸� ������ �ۼ�Ƽ���� ä�����ϴ�.", true, false, false, CL_warning);
		printlog("100%�� �Ǹ� VŰ�� ȿ���� ��밡���մϴ�. �Ϻδ� ���⸸ �ص� ȿ���� �ֽ��ϴ�.", true, false, false, CL_warning);
		return 1;
	case 32:
		printlog("����ũ�ѿ� �� 10���� ���� �ְ� ��Ʈ�� ���� ��ü�ϴ� ������ �Ż簡 �����Ͽ�", true, false, false, CL_warning);
		printlog("��Ʈ�� ���긦 ��ü�ϴ� ������̶� ���� �ֿ��� Ż���ϸ� ���ӿ��� �¸��մϴ�.", true, false, false, CL_warning);
		printlog("���ڶ� ���������� �� ��Ź�帳�ϴ�.", true, false, false, CL_warning);
		return 1;
	case EVL_KISME:
	{
		dif_rect_iterator rit(you.position, 2);
		int i = 1;
		for (; !rit.end() && i > 0; rit++)
		{
			if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
			{
				printlog("�ϴÿ��� Ű���ް� ��������!", true, false, false, CL_small_danger);
				monster *mon_ = env[current_level].AddMonster(MON_KISUME, M_FLAG_EVENT, (*rit));
				mon_->SetStrong(5);
				mon_->PlusTimeDelay(-mon_->GetWalkDelay()); //Ű���޴� �������� �ٷ� ���������ʴ´�.
				MoreWait();
				i--;
			}
		}
	}
	return 1;
	case EVL_SIGHT_P:
	{
		item_infor temp;
		env[current_level].MakeItem(event_->position, makePitem(MON_MOOK, 1, &temp));
	}
	return 1;
	case EVL_FLOOR:
	{
		env[current_level].changeTile(event_->position, env[current_level].base_floor);
	}
	return 1;
	case EVL_DREAM_FLOOR:
	{
		env[current_level].changeTile(event_->position, DG_DREAM_FLOOR);
	}
	return 1;
	case EVL_BAMBOO:
	{
		bamboo_count(current_level);
	}
	return 0;
	case EVL_LUNATICTIME:
	{
		for (int i = -3; i <= 3; i++)
		{
			if (i != 0)
				env[current_level].changeTile(coord_def(event_->position.x + i, event_->position.y + 1), env[current_level].base_floor);
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				env[current_level].changeTile(coord_def(event_->position.x + 4 * (j * 2 - 1), event_->position.y + i * 2), DG_OPEN_DOOR);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i != 1 || j != 1)
					env[current_level].changeTile(coord_def(event_->position.x - 1 + i, event_->position.y + 4 + j), DG_GLASS);
			}
		}
		printlog("It's LUNATIC TIME!!", true, false, false, CL_small_danger);
		env[current_level].MakeNoise(event_->position, 16, NULL);
		you.resetLOS();
		MoreWait();
	}
	return 1;
	case EVL_KOGASA:
	{
		dif_rect_iterator rit(you.position, 2);
		int i = 1;
		for (; !rit.end() && i > 0; rit++)
		{
			if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
			{
				printlog("�ϴÿ��� �ڰ��簡 ��������!", true, false, false, CL_small_danger);
				monster *mon_ = env[current_level].AddMonster(MON_KOGASA, M_FLAG_EVENT, (*rit));
				MoreWait();
				printlog("...�׷��� �ڰ���� ���ٴڿ� �Ӹ����� �ε�����.", true, false, false, CL_normal);
				mon_->SetConfuse(5 + randA(5));
				mon_->SetStrong(5);
				mon_->hp = mon_->hp * 2 / 3;
				i--;
			}
		}
	}
	return 1;
	case EVL_NOISE:
	{
		env[current_level].MakeNoise(event_->position, 8, NULL);
	}
	return 1;
	case EVL_VIOLET:
	{
		int prev_range = min(10, (event_->count + 2) / 2);
		int violet_range = min(10, (event_->count + 1) / 2);
		if (event_->count <= 0)
		{
			env[current_level].MakeViolet(event_->position, prev_range, false);
			return 1;
		}
		else if (prev_range != violet_range)
		{
			env[current_level].MakeViolet(event_->position, prev_range, false);
			env[current_level].MakeViolet(event_->position, violet_range, true);
		}
	}
	return 0;
	case EVL_SANTUARY:
	{
		int prev_range = min(10, (event_->count + 2) / 2);
		int santuary_range = min(10, (event_->count + 1) / 2);
		if (event_->count <= 0)
		{
			env[current_level].MakeSantuary(event_->position, prev_range, false);
			return 1;
		}
		else if (prev_range != santuary_range)
		{
			env[current_level].MakeSantuary(event_->position, prev_range, false);
			env[current_level].MakeSantuary(event_->position, santuary_range, true);
		}
	}
	return 0;
	case EVL_DREAM_MONSTER:
	{
		int arr_[] = { MON_MAC, MON_NIGHTMARE, MON_LUNATIC, MON_BLUE_UFO, MON_MOON_RABIT_ATTACK, MON_MOON_RABIT_SUPPORT, MON_SHEEP
		};
		rand_rect_iterator rit(event_->position, 3, 3);
		int mon_id_ = arr_[randA(6)];
		int i = mon_id_ == MON_SHEEP ? rand_int(3, 4) : (mon_id_ == MON_BLUE_UFO ? 3 : 1);
		int base_ = i;
		for (; !rit.end() && i > 0; rit++)
		{
			if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
			{
				monster *mon_ = env[current_level].AddMonster(mon_id_, 0, (*rit));
				mon_->SetStrong(base_>1?1:3);
				i--;
			}
		}
	}
	return 1;
	case EVL_DREAM_MESSAGE:
	{
		int i = 0;
		for (list<events>::iterator it = env[current_level].event_list.begin(); it != env[current_level].event_list.end(); it++)
		{
			if (it->id == EVL_DREAM_MESSAGE)
				i++;
		}
		switch (i)
		{
		case 5:
			you.resetLOS();
			printlog("���� ���谡 �о����� �����Ѵ�! �ڰ� �ִ� ������ ����� �����Ѵ�!", true, false, false, CL_danger);
			MoreWait();
			break;
		case 4:
			you.resetLOS();
			printlog("���� ���谡 �о����� �ִ�!", true, false, false, CL_danger);
			MoreWait();
			break;
		case 3:
			you.resetLOS();
			printlog("���� ���谡 �� �ٽ� �о�����! ���� �ֹε��� ����� ��ġë��!", true, false, false, CL_danger);
			MoreWait();
			break;
		case 2:
			you.resetLOS();
			printlog("���� ����� ���� ��κ� ���ȴ�! �� ���Ͱ� ����� �����Ѵ�!", true, false, false, CL_danger);
			MoreWait();
			break;
		case 1:
			for (int k = 3; k < DG_MAX_X - 3; k++)
			{
				for (int h = 3; h < DG_MAX_Y - 3; h++)
				{
					if (env[current_level].dgtile[k][h].tile == DG_WALL2)
						env[current_level].changeTile(coord_def(k, h), env[current_level].base_floor);
				}
			}
			{
				for (int i = 0; i < DG_MAX_X; i++)
					for (int j = 0; j < DG_MAX_Y; j++)
						env[current_level].magicmapping(i, j);
			}
			while (1)
			{
				int x_ = randA(DG_MAX_X - 1);
				int y_ = randA(DG_MAX_Y - 1);
				if (!env[current_level].isInSight(coord_def(x_, y_)) && env[current_level].dgtile[x_][y_].isFloor() && !(env[current_level].dgtile[x_][y_].flag & FLAG_NO_STAIR))
				{
					env[current_level].changeTile(coord_def(x_, y_), DG_MOON_STAIR);
					env[current_level].stair_vector.push_back(stair_info(coord_def(x_, y_), MOON_LEVEL));
					rand_rect_iterator rect_it(coord_def(x_,y_),1,1);


					while (!rect_it.end()) {
						env[current_level].changeTile((*rect_it), DG_DREAM_FLOOR2);
						rect_it++;
					}



					beam_iterator beam(coord_def(x_, y_), you.position);

					beam.init();
					while (!beam.end()) {
						env[current_level].changeTile((*beam), DG_DREAM_FLOOR2);
						beam++;
					}
					env[current_level].changeTile((*beam), DG_DREAM_FLOOR2);


					if (!is_exist_named(MON_DOREMI)) {
						monster *mon_ = env[current_level].AddMonster(MON_DOREMI, M_FLAG_EVENT, coord_def(x_, y_));
						mon_->SetStrong(5); 
						set_exist_named(MON_DOREMI);
					}

					break;
				}
			}
			you.resetLOS();
			printlog("���� ����� ������ ����Ǿ���! �޷� ���� ��Ż�� �ִ��� ���� �����Ѵ�!", true, false, false, CL_danger);
			MoreWait();
			env[current_level].MakeEvent(EVL_REGEN, coord_def(0, 0), EVT_ALWAYS, 30);
			break;
		}
	}
	return 1;
	case EVL_AGRO:
		if (event_->count <= 0)
		{
			for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
			{
				if (it->isLive())
				{
					it->AttackedTarget(&you);
				}
			}
		}
		return 1;
	case EVL_REGEN:
	{
		float multi_ = 0.0f;
		if (int penalty_turn_ = you.CheckPeanltyTurn(current_level))
		{
			//1000���� �����ؼ� 5000�Ϻ��� ���� 2��
			if (penalty_turn_ >= 1000) {
				multi_ += min(penalty_turn_ - 1000, 4000) / 4000.0f;
			}
		}
		if (randA(12-5*multi_) == 0)
		{
			int arr_[] = { MON_MAC, MON_NIGHTMARE, MON_LUNATIC, MON_BLUE_UFO, MON_MOON_RABIT_ATTACK, MON_MOON_RABIT_SUPPORT
			};
			int mon_id_ = arr_[randA(5)];

			while (1)
			{
				int x_ = randA(DG_MAX_X - 1);
				int y_ = randA(DG_MAX_Y - 1);
				if (env[current_level].isMove(x_, y_) && !env[current_level].isMonsterPos(x_, y_) && !env[current_level].isInSight(coord_def(x_, y_)))
				{
					monster *mon_ = env[current_level].AddMonster(mon_id_, 0, coord_def(x_, y_));
					mon_->SetStrong(1);
					mon_->AttackedTarget(&you);
					break;
				}
			}

		}

	}
		return 0;
	case EVL_REGEN2:
	{
		float multi_ = 0.0f;
		if (int penalty_turn_ = you.CheckPeanltyTurn(current_level))
		{
			//1000���� �����ؼ� 5000�Ϻ��� ���� 2��
			if (penalty_turn_ >= 1000) {
				multi_ += min(penalty_turn_ - 1000, 4000) / 4000.0f;
			}
		}
		if (randA(50-25*multi_) == 0)
		{
			int arr_[] = { MON_HELL_SPIDER, MON_BLOOD_HAUNT, MON_LANTERN_YOUKAI, MON_HELL_HOUND, MON_ONI, MON_BLUE_ONI
			};
			int mon_id_ = arr_[randA(5)];

			while (1)
			{
				int x_ = randA(DG_MAX_X - 1);
				int y_ = randA(DG_MAX_Y - 1);
				if (env[current_level].isMove(x_, y_) && !env[current_level].isMonsterPos(x_, y_) && !env[current_level].isInSight(coord_def(x_, y_)))
				{
					monster *mon_ = env[current_level].AddMonster(mon_id_, 0, coord_def(x_, y_));
					mon_->SetStrong(1);
					mon_->state.SetState(MS_NORMAL);
					break;
				}
			}

		}
	}
	return 0;
	case EVL_ARENA:
	{
		arena_event(current_level);
	}
	return 0;
	case EVL_NAMAZ:
	{
		int power = min(SpellCap(SPL_SUMMON_NAMAZ), you.GetSpellPower(SpellSchool(SPL_SUMMON_NAMAZ, 0), SpellSchool(SPL_SUMMON_NAMAZ, 1), SpellSchool(SPL_SUMMON_NAMAZ, 2)));
		skill_summon_namaz2(power, false, &you, event_->position);
		return 1;
	}
	return 0;
	case EVL_KOISHI:
	{
		if (event_->count == -1)
		{
			event_->type = EVT_ALWAYS;
			event_->count = 11;
		}
		if (event_->count == 10)
		{
			enterlog();
			printlog("��, �޸���", true, false, false, CL_small_danger);
			MoreWait();
			you.SetInter(IT_EVENT);
		}
		if (event_->count == 5)
		{
			enterlog();
			printlog("����, �����", true, false, false, CL_small_danger);
			MoreWait();
			you.SetInter(IT_EVENT);
		}
		if (event_->count == 0)
		{

			dif_rect_iterator rit(you.position, 2);
			int i = 1;
			for (; !rit.end() && i > 0; rit++)
			{
				if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
				{
					enterlog();
					printlog("�� �ڿ� �־�!", true, false, false, CL_danger);
					MoreWait();
					monster *mon_ = env[current_level].AddMonster(MON_KOISHI, M_FLAG_EVENT, (*rit));
					mon_->PlusTimeDelay(-mon_->GetWalkDelay()); //���̽ô� �������� �ٷ� ���������ʴ´�.
					mon_->SetStrong(5);
					mon_->SetHaste(20 + randA(20));
					return 1;
				}
			}
			enterlog();
			printlog("... ������ �ʴ� ���� �־�", true, false, false, CL_small_danger); //���̽� �������
			MoreWait();
			return 1;
		}
	}
	return 0;
	case EVL_KYOKO:
	{
		monster *kyoko_ = env[current_level].AddMonster(MON_KYOUKO, M_FLAG_EVENT, coord_def(0, -5) + event_->position);

		kyoko_->SetStrong(5);
		for (int i = rand_int(2, 4); i > 0; i--)
		{
			item_infor temp;
			env[current_level].MakeItem(coord_def(rand_int(-1, 1), rand_int(-5, -3)) + event_->position, makePitem(MON_HUMAM_MAN, 1, &temp));
		}

		dif_rect_iterator rit(coord_def(0, -3) + event_->position, 1);
		int i = rand_int(2, 4);
		for (; !rit.end() && i > 0; rit++)
		{
			if (env[current_level].isMove(rit->x, rit->y, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && you.position != (*rit))
			{
				monster *mon_ = env[current_level].AddMonster(MON_HUMAM_MAN, M_FLAG_EVENT | M_FLAG_NETURALY, (*rit));
				mon_->hp = mon_->hp*rand_int(3, 9) / 10;
				mon_->FoundTarget(kyoko_, mon_->FoundTime());
				mon_->s_fear = 20 + randA(20);
				mon_->SetStrong(1);
				i--;
			}
		}
		kyoko_->CheckSightNewTarget();
	}
	return 1;
	case EVL_AUTUMN:
	{
		int rand_ = randA(1);
		env[current_level].MakeFloorEffect(event_->position, &img_effect_autumn_leave[rand_ * 2], &img_effect_autumn_leave[rand_ * 2 + 1], FLOORT_AUTUMN, rand_int(50, 100), NULL);
	}
	return 1;
	case EVL_SUKIMA:
	{
		textures* t_ = &img_effect_schema[randA(2)];
		env[current_level].MakeFloorEffect(event_->position, t_, t_, FLOORT_SCHEMA, 2, NULL);
	}
	return 0;
	case EVL_RUN_FAIRY:
	{
		monster *sunny_ = env[current_level].AddMonster(MON_SUNNY, M_FLAG_EVENT, coord_def(1, 0) + event_->position);
		monster *star_ = env[current_level].AddMonster(MON_STAR, M_FLAG_EVENT, coord_def(-1, 0) + event_->position);
		monster *lunar_ = env[current_level].AddMonster(MON_LUNAR, M_FLAG_EVENT, coord_def(0, 0) + event_->position);

		sunny_->SetStrong(5);
		star_->SetStrong(5);
		lunar_->SetStrong(5);
		sunny_->s_fear = 30 + randA(20);
		star_->s_fear = 30 + randA(20);
		lunar_->s_fear = 30 + randA(20);
		char temp[100];
		sprintf_s(temp, 100, "%s%s���ƴ�. \"������!\"", star_->GetName()->name.c_str(), star_->GetName()->name_is(true));
		printlog(temp, true, false, false, CL_speak);

		sunny_->SetInvisible(10);
		lunar_->s_confuse = 5;
		star_->SetHaste(10);

	}
	return 1;
	case EVL_SCALET_TRAP:
	{
		env[current_level].changeTile(coord_def(event_->position.x - 4, event_->position.y + 1), DG_OPEN_DOOR);
		env[current_level].changeTile(coord_def(event_->position.x - 2, event_->position.y + 1), DG_OPEN_DOOR);
		env[current_level].changeTile(coord_def(event_->position.x - 4, event_->position.y - 1), DG_OPEN_DOOR);
		env[current_level].changeTile(coord_def(event_->position.x - 2, event_->position.y - 1), DG_OPEN_DOOR);

		env[current_level].changeTile(coord_def(event_->position.x + 1, event_->position.y), DG_GLASS);

		printlog("�������۵�. Ĩ���ڸ� ó���϶�!", true, false, false, CL_small_danger);
		env[current_level].MakeNoise(event_->position, 8, NULL);
	}
	return 1;
	case EVL_KOGASATIME:
	{
		for (int i = -3; i <= 3; i++)
		{
			if (i != 0)
				env[current_level].changeTile(coord_def(event_->position.x + i, event_->position.y + 1), env[current_level].base_floor);
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				env[current_level].changeTile(coord_def(event_->position.x + 4 * (j * 2 - 1), event_->position.y + i * 2), DG_OPEN_DOOR);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i != 1 || j != 1)
					env[current_level].changeTile(coord_def(event_->position.x - 1 + i, event_->position.y + 4 + j), DG_GLASS);
			}
		}
		printlog("It's SURPRISE TIME!!", true, false, false, CL_small_danger);
		env[current_level].MakeNoise(event_->position, 16, NULL);
		you.resetLOS();
		MoreWait();
		printlog("...�׷��� �ڰ���� ���� �߸��Ǿ����� ������.", true, false, false, CL_normal);
	}
	return 1;
	case EVL_HOJOK:
	{
		unit* target_unit = env[current_level].isMonsterPos(event_->position.x - 4, event_->position.y - 1);
		if (target_unit)
		{
			env[current_level].changeTile(coord_def(event_->position.x - 4, event_->position.y), env[current_level].base_floor);
			env[current_level].changeTile(coord_def(event_->position.x - 3, event_->position.y), env[current_level].base_floor);
			env[current_level].changeTile(coord_def(event_->position.x - 3, event_->position.y - 1), env[current_level].base_floor);

			you.resetLOS();
			char temp[100];
			sprintf_s(temp, 100, "%s%s���ƴ�. \"��ġ���ָ�!\"", target_unit->GetName()->name.c_str(), target_unit->GetName()->name_is(true));
			printlog(temp, true, false, false, CL_speak);
			target_unit->PlusTimeDelay(-target_unit->GetWalkDelay());
			if (!target_unit->isplayer()) {
				((monster*)target_unit)->FoundTarget(&you, ((monster*)target_unit)->FoundTime());
			}
		}
		target_unit = env[current_level].isMonsterPos(event_->position.x + 4, event_->position.y - 1);
		if (target_unit)
		{
			env[current_level].changeTile(coord_def(event_->position.x + 4, event_->position.y), env[current_level].base_floor);
			env[current_level].changeTile(coord_def(event_->position.x + 3, event_->position.y), env[current_level].base_floor);
			env[current_level].changeTile(coord_def(event_->position.x + 3, event_->position.y - 1), env[current_level].base_floor);

			you.resetLOS();
			char temp[100];
			sprintf_s(temp, 100, "%s%s���ƴ�. \"������ �ð��ֽñ�!\"", target_unit->GetName()->name.c_str(), target_unit->GetName()->name_is(true));
			printlog(temp, true, false, false, CL_speak);
			target_unit->PlusTimeDelay(-target_unit->GetWalkDelay());
			if (!target_unit->isplayer())
				((monster*)target_unit)->FoundTarget(&you, ((monster*)target_unit)->FoundTime());
		}
		return 1;
	}
	case EVL_KOGASA3:
	{
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
				env[current_level].MakeSmoke(coord_def(i + event_->position.x, j + event_->position.y), img_fog_dark, SMT_DARK, rand_int(3, 4), 0, NULL);
		if (distan_coord(you.position, event_->position) <= 2) {
			monster *mon_ = env[current_level].AddMonster(MON_KOGASA, M_FLAG_EVENT, event_->position);
			char temp[100];
			sprintf_s(temp, 100, "%s%s���ƴ�. \"��������...�ݷ�, �ݷ�!\"", mon_->GetName()->name.c_str(), mon_->GetName()->name_is(true));
			printlog(temp, true, false, false, CL_speak);
			env[current_level].MakeNoise(event_->position, 12, NULL);
			you.resetLOS();
			MoreWait();
			printlog("...�ڰ���� �غ��ص� ���⸦ �ʹ� ���̸��ŵ��ϴ�. ", true, false, false, CL_normal);
			mon_->SetSlow(rand_int(30, 40));
			mon_->SetStrong(5);
			return 1;
		}
		return 0;
	}
	case EVL_MEDI:
	{
		for (rect_iterator rlt(event_->position, 1, 1); !rlt.end(); rlt++) {
			if (env[current_level].isInSight((*rlt)))
			{
				monster *medi_ = env[current_level].AddMonster(MON_MEDICINE, M_FLAG_EVENT, event_->position);

				medi_->SetStrong(5);
				medi_->PlusTimeDelay(-4 * medi_->GetWalkDelay());
				for (rect_iterator rlt2(event_->position, 1, 1); !rlt2.end(); rlt2++) {
					if ((*rlt2) != event_->position)
					{
						random_extraction<int> rand_;
						rand_.push(MON_CROW);
						rand_.push(MON_FAIRY_GREEN);
						rand_.push(MON_FAIRY_BLUE);
						rand_.push(MON_FAIRY_RED);
						rand_.push(MON_KATPA);
						monster *mon_ = env[current_level].AddMonster(rand_.pop(), M_FLAG_EVENT | M_FLAG_NETURALY, (*rlt2));

						mon_->FoundTarget(medi_, mon_->FoundTime());
						mon_->s_poison = 100;
						mon_->SetPoisonReason(PRT_NEUTRAL);
						mon_->s_fear = 20 + randA(20);
						mon_->SetStrong(1);
					}

				}
				return 1;
			}
		}
		return 0;
	}
	case EVL_LOCK_DOOR:
	{
		env[current_level].dgtile[event_->position.x][event_->position.y].flag |= FLAG_DONT_DOOR;
		return 1;
	}
	case EVL_SMOKE:
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (randA(6) == 0)
					env[current_level].MakeSmoke(coord_def(i + event_->position.x, j + event_->position.y), img_fog_normal, SMT_FOG, rand_int(3, 4), 0, NULL);
			}
		}
		return 0;
	}
	case EVL_CHEN:
	{
		for (rect_iterator rlt(event_->position, 1, 1); !rlt.end(); rlt++) {
			if (env[current_level].isInSight((*rlt)))
			{
				monster *chen_ = env[current_level].AddMonster(MON_CHEN, M_FLAG_EVENT, event_->position);

				chen_->SetStrong(5);
				chen_->s_confuse = 15;
				for (rect_iterator rlt2(event_->position, 1, 1); !rlt2.end(); rlt2++) {
					if ((*rlt2).x != event_->position.x && (*rlt2).y != event_->position.y)
					{
						random_extraction<int> rand_;
						rand_.push(MON_ORANGE_CAT);
						rand_.push(MON_BLACK_CAT);
						rand_.push(MON_WHITE_CAT);
						monster *mon_ = env[current_level].AddMonster(rand_.pop(), M_FLAG_EVENT, (*rlt2));

						mon_->SetStrong(1); 
						mon_->s_confuse = 15;
					}
				}
				return 1;
			}
		}
		return 0;
	}
	case EVL_BROKEN_NESI:
	{
		monster *nesi_ = env[current_level].AddMonster(MON_NESI, M_FLAG_EVENT, event_->position);
		nesi_->s_confuse = -1;
		nesi_->exper = nesi_->exper / 2;
		nesi_->SetStrong(1);
		return 1;
	}
	case EVL_FIRE_SMOKE:
	{
		if (event_->count % 2)
			env[current_level].MakeSmoke(coord_def(event_->position.x, event_->position.y), img_fog_fire, SMT_FIRE, rand_int(3, 4), 0, NULL);
		return 0;
	}
	case EVL_COLD_SMOKE:
	{
		if (event_->count % 2)
			env[current_level].MakeSmoke(coord_def(event_->position.x, event_->position.y), img_fog_cold, SMT_COLD, rand_int(3, 4), 0, NULL);
		return 0;
	}
	case EVL_SILENCE:
	{
		int prev_range = min(10, (event_->count + 2) / 2);
		int silence_range = min(10, (event_->count + 1) / 2);
		if (event_->count <= 0)
		{
			env[current_level].MakeSilence(event_->position, prev_range, false);
			return 1;
		}
		else if (prev_range != silence_range)
		{
			env[current_level].MakeSilence(event_->position, prev_range, false);
			env[current_level].MakeSilence(event_->position, silence_range, true);
		}
		return 0;
	}
	case EVL_WATER:
	{
		if (env[current_level].dgtile[event_->position.x][event_->position.y].tile != DG_SEA)
		{
			event_->value = env[current_level].dgtile[event_->position.x][event_->position.y].tile;
			env[current_level].changeTile(event_->position, DG_SEA);
		}
		else if (event_->count <= 0)
		{
			env[current_level].changeTile(event_->position, event_->value ? (dungeon_tile_type)event_->value : DG_SEA);
			return 1;
		}
		return 0;
	}
	case EVL_SION_DELETE:
	{
		int num = 0;
		string str_ = "�������� ";
		list<item>::iterator it, first_it;
		for (it = env[current_level].item_list.begin(); it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++;
			if ((*temp).position.x == event_->position.x && (*temp).position.y == event_->position.y)
			{
				str_ = temp->GetName() + temp->GetNameInfor().name_do(true);
				env[current_level].DeleteItem(temp);
				if (!num++)
					first_it = temp;
			}
			else if (num)
				break;
		}
		if (num == 1) {
			printarray(true, false, false, CL_small_danger, 2, str_.c_str(), "�����̰��� �������.");
			you.SetInter(IT_EVENT);
		}
		else if (num > 1) {
			printarray(true, false, false, CL_small_danger, 1, "�����۵��� �����̰��� �������.");
			you.SetInter(IT_EVENT);
		}
		return 1;
	}
	default:
		break;
	}

	return 0;
}