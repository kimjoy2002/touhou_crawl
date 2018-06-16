//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: create_item.cpp
//
// ����: �ʿ� �´� �������� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "item.h"
#include "spellcard.h"



extern void Set_X_Y(int &x_, int x, int rand_x, int &y_, int y, int rand_y);

void create_id_to_item(int id, int level);

struct item_group
{
	int id; //������ȣ <- ������ȣ
	int min_level; //�ּҷ��� <- ������ ���� ��
	int max_level; //�ִ뷹�� <- ������ ���� ��
	int percent; //Ȯ��  <- ���� �󵵸� �����Ѵ�.
	int rare; //���
};


item_group item_index[] = //������ ���(�� 2��°�� ������������ ����)
{
	{0,0,SCARLET_LEVEL_LAST_LEVEL,20,1}, //�� ź����
	{1,0,SCARLET_LEVEL_LAST_LEVEL,5,1}, //��Ÿ����(�尩, ����, �����)
	{21,0,SCARLET_LEVEL_LAST_LEVEL,2,1}, //����
	
	
	{2,0,7,70,1}, //�ʹ� �߳����� ���� �����
	{3,0,7,80,1}, //�ʹ� �߳����� ���� �η縶����
	{4,0,7,15,1}, //�ʹ� �߳����� ���� �����
	//{5,0,7,15,1}, //�ʹ� �߳����� ���� �η縶����
	{6,0,7,80,1}, //�ʹݿ� ����
	{7,0,7,20,1}, //�ʹݿ� ��
	{8,0,7,20,1}, //�ʹݿ� ���� ����, �ƹķ���
	{9,0,7,1,1}, //�ʹݿ� ���� ����, �ƹķ���
	{10,0,7,10,1}, //�ʹݿ� ����
	{11,0,7,0,1}, //�ʹݿ� ��ĭ
	{12,0,7,0,1}, //�ʹݿ� ��ĭ
	{26,0,7,5,1},//����ī��
	{27,2,4,2,1},//��Ƽ��Ʈ����
	{28,2,4,2,1},//��Ƽ��Ʈ��
	{29,2,4,2,1},//��Ƽ��Ʈ����
	{30,2,4,1,1},//�ߵ���

	{25,2,SCARLET_LEVEL_LAST_LEVEL,3,1}, //å
	
	{13,5,SCARLET_LEVEL_LAST_LEVEL,70,1}, //�߹� �߳����� ���� �����
	{14,5,SCARLET_LEVEL_LAST_LEVEL,70,1}, //�߹� �߳����� ���� �η縶����
	{15,5,SCARLET_LEVEL_LAST_LEVEL,15,1}, //�߹� �߳����� ���� �����
	//{16,5,SCARLET_LEVEL_LAST_LEVEL,15,1}, //�߹� �߳����� ���� �η縶����
	{17,5,SCARLET_LEVEL_LAST_LEVEL,80,1}, //�߹ݿ� �����(���� ����)
	{18,5,SCARLET_LEVEL_LAST_LEVEL,20,1}, //�߹ݿ� ��
	{19,5,SCARLET_LEVEL_LAST_LEVEL,10,1}, //�߹ݿ� ���� ����, �ƹķ���
	{20,5,SCARLET_LEVEL_LAST_LEVEL,1,1}, //�߹ݿ� ���� ����, �ƹķ���
	{22,5,SCARLET_LEVEL_LAST_LEVEL,10,1}, //�߹ݿ� ����
	{23,5,SCARLET_LEVEL_LAST_LEVEL,0,1}, //�߹ݿ� ��ĭ
	{24,5,SCARLET_LEVEL_LAST_LEVEL,0,1}, //�߹ݿ� ��ĭ
	{26,5,SCARLET_LEVEL_LAST_LEVEL,5,1}, //����ī��
	{27,5,SCARLET_LEVEL_LAST_LEVEL,4,1},//��Ƽ��Ʈ����
	{28,5,SCARLET_LEVEL_LAST_LEVEL,4,1},//��Ƽ��Ʈ��
	{29,5,SCARLET_LEVEL_LAST_LEVEL,4,1},//��Ƽ��Ʈ����
	{30,5,SCARLET_LEVEL_LAST_LEVEL,3,1},//�ߵ���


	{13,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,90,1}, //�߹� �߳����� ���� �����
	{14,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,50,1}, //�߹� �߳����� ���� �η縶����
	{15,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,25,1}, //�߹� �߳����� ���� �����
	{17,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,50,1}, //�߹ݿ� �����(���� ����)
	{18,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,10,1}, //�߹ݿ� ��
	{19,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,10,1}, //�߹ݿ� ���� ����, �ƹķ���
	{20,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,1,1}, //�߹ݿ� ���� ����, �ƹķ���
	{22,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,5,1}, //�߹ݿ� ����
	{23,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,0,1}, //�߹ݿ� ��ĭ
	{24,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,0,1}, //�߹ݿ� ��ĭ
	{26,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,2,1}, //����ī��
	{27,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,3,1},//��Ƽ��Ʈ����
	{28,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,3,1},//��Ƽ��Ʈ��
	{29,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,3,1},//��Ƽ��Ʈ����
	{30,EIENTEI_LEVEL,EIENTEI_LEVEL_LAST_LEVEL,1,1},//�ߵ���

	

	//����
	{13,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,20,1}, //�߹� �߳����� ���� �����
	{14,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,20,1}, //�߹� �߳����� ���� �η縶����
	{17,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,30,1}, //�߹ݿ� �����(���� ����)
	{18,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,30,1}, //�߹ݿ� ��
	{19,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1}, //�߹ݿ� ���� ����, �ƹķ���
	{0,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,20,1}, //�� ź����
	{1,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1}, //��Ÿ����(�尩, ����, �����)
	{21,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,5,1}, //����
	{22,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,8,1}, //�߹ݿ� ����
	{25,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,20,1}, //å
	{26,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,3,1}, //����ī��
	{27,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1},//��Ƽ��Ʈ����
	{28,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1},//��Ƽ��Ʈ��
	{29,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1},//��Ƽ��Ʈ����
	{30,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,15,1},//�ߵ���


	
	//���±�
	{13,DEPTH_LEVEL,DEPTH_LAST_LEVEL,70,1}, //�߹� �߳����� ���� �����
	{14,DEPTH_LEVEL,DEPTH_LAST_LEVEL,70,1}, //�߹� �߳����� ���� �η縶����
	{15,DEPTH_LEVEL,DEPTH_LAST_LEVEL,30,1}, //�߹� �߳����� ���� �����
	{17,DEPTH_LEVEL,DEPTH_LAST_LEVEL,50,1}, //�߹ݿ� �����(���� ����)
	{18,DEPTH_LEVEL,DEPTH_LAST_LEVEL,20,1}, //�߹ݿ� ��
	{19,DEPTH_LEVEL,DEPTH_LAST_LEVEL,10,1}, //�߹ݿ� ���� ����, �ƹķ���
	{0,DEPTH_LEVEL,DEPTH_LAST_LEVEL,20,1}, //�� ź����
	{1,DEPTH_LEVEL,DEPTH_LAST_LEVEL,10,1}, //��Ÿ����(�尩, ����, �����)
	{25,DEPTH_LEVEL,DEPTH_LAST_LEVEL,10,1}, //å
	{26,DEPTH_LEVEL,DEPTH_LAST_LEVEL,3,1}, //����ī��
	{21,DEPTH_LEVEL,DEPTH_LAST_LEVEL,5,1}, //����
	{22,DEPTH_LEVEL,DEPTH_LAST_LEVEL,10,1}, //�߹ݿ� ����
	{27,DEPTH_LEVEL,DEPTH_LAST_LEVEL,4,1},//��Ƽ��Ʈ����
	{28,DEPTH_LEVEL,DEPTH_LAST_LEVEL,4,1},//��Ƽ��Ʈ��
	{29,DEPTH_LEVEL,DEPTH_LAST_LEVEL,4,1},//��Ƽ��Ʈ����
	{30,DEPTH_LEVEL,DEPTH_LAST_LEVEL,4,1},//�ߵ���
	
	//���ǵ���
	{13,MOON_LEVEL,MOON_LAST_LEVEL,50,1}, //�߹� �߳����� ���� �����
	{14,MOON_LEVEL,MOON_LAST_LEVEL,50,1}, //�߹� �߳����� ���� �η縶����
	{17,MOON_LEVEL,MOON_LAST_LEVEL,50,1}, //�߹ݿ� �����(���� ����)
	{18,MOON_LEVEL,MOON_LAST_LEVEL,50,1}, //�߹ݿ� ��
	{19,MOON_LEVEL,MOON_LAST_LEVEL,10,1}, //�߹ݿ� ���� ����, �ƹķ���
	{0,MOON_LEVEL,MOON_LAST_LEVEL,20,1}, //�� ź����
	{1,MOON_LEVEL,MOON_LAST_LEVEL,25,1}, //��Ÿ����(�尩, ����, �����)
	{25,MOON_LEVEL,MOON_LAST_LEVEL,10,1}, //å
	{26,MOON_LEVEL,MOON_LAST_LEVEL,3,1}, //����ī��
	{21,MOON_LEVEL,MOON_LAST_LEVEL,5,1}, //����
	{22,MOON_LEVEL,MOON_LAST_LEVEL,10,1}, //�߹ݿ� ����
	{27,MOON_LEVEL,MOON_LAST_LEVEL,5,1},//��Ƽ��Ʈ����
	{28,MOON_LEVEL,MOON_LAST_LEVEL,20,1},//��Ƽ��Ʈ��
	{29,MOON_LEVEL,MOON_LAST_LEVEL,5,1},//��Ƽ��Ʈ����
	{30,MOON_LEVEL,MOON_LAST_LEVEL,3,1},//�ߵ���
	
	//����
	{13,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,50,1}, //�߹� �߳����� ���� �����
	{14,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,50,1}, //�߹� �߳����� ���� �η縶����
	{17,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,50,1}, //�߹ݿ� �����(���� ����)
	{18,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,20,1}, //�߹ݿ� ��
	{19,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,10,1}, //�߹ݿ� ���� ����, �ƹķ���
	{0,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,20,1}, //�� ź����
	{1,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,10,1}, //��Ÿ����(�尩, ����, �����)
	{25,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,15,1}, //å
	{26,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,3,1}, //����ī��
	{21,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,5,1}, //����
	{22,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,10,1}, //�߹ݿ� ����
	{27,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,10,1},//��Ƽ��Ʈ����
	{28,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,10,1},//��Ƽ��Ʈ��
	{29,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,10,1},//��Ƽ��Ʈ����
	{30,SUBTERRANEAN_LEVEL,SUBTERRANEAN_LEVEL_LAST_LEVEL,3,1},//�ߵ���

	//�ǵ���Ͼ�
	{13,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,60,1}, //�߹� �߳����� ���� �����
	{14,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,50,1}, //�߹� �߳����� ���� �η縶����
	{15,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,10,1}, //�߹� �߳����� ���� �����
	{17,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,60,1}, //�߹ݿ� �����(���� ����)
	{18,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,20,1}, //�߹ݿ� ��
	{19,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,10,1}, //�߹ݿ� ���� ����, �ƹķ���
	{0,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,20,1}, //�� ź����
	{1,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,10,1}, //��Ÿ����(�尩, ����, �����)
	{25,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,10,1}, //å
	{26,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,3,1}, //����ī��
	{21,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,5,1}, //����
	{22,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,10,1}, //�߹ݿ� ����
	{27,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,4,1},//��Ƽ��Ʈ����
	{28,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,4,1},//��Ƽ��Ʈ��
	{29,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,4,1},//��Ƽ��Ʈ����
	{30,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,4,1},//�ߵ���
	

	{-1,0,0,0,0}

};

item_infor& id_to_item(int id, item_infor* item_);


item_infor& CreateFloorItem(int floor, item_infor* item_)
{
	int i = 0, total=0;

	if(you.GetPunish(GT_SATORI) && randA(9)==0)
	{
		//���丮 ¡���߿� ������ ��� ���� �ֿϵ��� �����Ͱ� �ȴ�.
		id_to_item(31, item_);
		return (*item_);
	}
	if(you.s_unluck>3 && randA(you.s_unluck>6?6:12)==0)
	{
		//�����̻��� �ҿ�� Ȯ�������� �������� �ܶ� ���´�.
		random_extraction<int> rand_;
		rand_.push(4);//��������
		rand_.push(9);//���۹���
		id_to_item(rand_.pop(), item_);
		return (*item_);
	}




	vector<item_group*> group;
	group.reserve(128);
	while(item_index[i].id != -1)
	{
		if(item_index[i].min_level<=floor && item_index[i].max_level>=floor && item_index[i].percent)
		{
			group.push_back(&item_index[i]);
			total+=item_index[i].percent;
		}
		else if(item_index[i].min_level > floor)
			break;
		i++;
	}

	int rand_ = randA_1(total);
	vector<item_group*>::iterator it;
	for(it = group.begin(); it != group.end(); it++)
	{
		if(rand_<=(*it)->percent)
		{
			id_to_item((*it)->id, item_);
			return (*item_);
		}
		else
			rand_ -= (*it)->percent;
	
	}
	return (*item_);

}




void create_item(int floor, int num_)
{
	if(num_ == 0)
		return;

	int i = 0, total=0, num = num_?num_:10;
	vector<item_group*> group;
	group.reserve(128);
	while(item_index[i].id != -1)
	{
		if(item_index[i].min_level<=floor && item_index[i].max_level>=floor && item_index[i].percent)
		{
			group.push_back(&item_index[i]);
			total+=item_index[i].percent;
		}
		else if(item_index[i].min_level > floor)
			break;
		i++;
	}

	for(int i = 0; i<num; i++)
	{
		int rand_ = randA_1(total);
		vector<item_group*>::iterator it;

		
		if(you.GetPunish(GT_SATORI) && randA(9)==0)
		{
			//���丮 ¡���߿� ������ ��� ���� �ֿϵ��� �����Ͱ� �ȴ�.
			create_id_to_item(31, floor);
			continue;
		}



		for(it = group.begin(); it != group.end(); it++)
		{
			if(rand_<=(*it)->percent)
			{
				create_id_to_item((*it)->id, floor);
				break;
			}
			else
				rand_ -= (*it)->percent;
	
		}
	}
}


item_infor& id_to_item(int id, item_infor* item_)
{	
	switch(id)
	{
	case 0:
		makeitem(ITM_THROW_TANMAC, 0,item_);
		break;
	case 1:
		makeitem((item_type)rand_int(ITM_ARMOR_HEAD,ITM_ARMOR_BOOT),rand_int(2,-1),item_);
		break;
	case 2: //�� �ʹݹ���
		makeitem(ITM_POTION,randA(1)>0?1:(randA(60)?2:3),item_);
		break;
	case 3: //�� �ʹݽ�ũ��
		makeitem(ITM_SCROLL,randA(2)>0?1:(randA(60)?2:3),item_);
		break;
	case 4: //��� �ʹݹ���
		makeitem(ITM_POTION,-1,item_);
		break;
	case 5: //��� �ʹݽ�ũ��
		makeitem(ITM_SCROLL,-1,item_);
		break;
	case 6: //���� ����
		makeitem((item_type)rand_int(ITM_WEAPON_FIRST,ITM_WEAPON_CLOSE),randA(8)?0:(randA(3)?1:-1),item_);
		break;
	case 7://���� ��
		makeitem((item_type)(ITM_ARMOR_BODY_FIRST+randA(ITM_ARMOR_BODY_LAST-ITM_ARMOR_BODY_FIRST-1)),randA(6)?0:(randA(3)?1:-1),item_);
		break;
	case 8://���� ���� ��ű�
		makeitem(randA(6)?ITM_RING:ITM_AMULET,1,item_);
		break;
	case 9://���� ���� ��ű�
		makeitem(ITM_RING,-1,item_);
		break;
	case 10://���� ����
		makeitem(ITM_ARMOR_SHIELD,randA(4)?0:(randA(3)?1:-1),item_);
		break;

		
	case 13: //�� �߹ݹ���
		makeitem(ITM_POTION,randA(1)>0?1:(randA(30)?2:3),item_);
		break;
	case 14: //�� �߹ݽ�ũ��
		makeitem(ITM_SCROLL,randA(2)>0?1:(randA(30)?2:3),item_);
		break;
	case 15: //��� �߹ݹ���
		makeitem(ITM_POTION,randA(3)?-1:-2,item_);
		break;
	case 16: //��� �߹ݽ�ũ��
		makeitem(ITM_SCROLL,randA(3)?-1:-2,item_);
		break;
	case 17: //�߹� ���� - ��ħ
		makeitem((item_type)rand_int(ITM_WEAPON_FIRST,ITM_WEAPON_CLOSE),randA(4)?0:(randA(6)?1:-1),item_);
		break;
	case 18://�߹� �� - ��ħ
		makeitem((item_type)rand_int(ITM_ARMOR_BODY_FIRST,ITM_ARMOR_BODY_LAST-1),randA(4)?0:(randA(6)?1:-1),item_);
		break;
	case 19://�߹� ���� ��ű�
		makeitem(randA(4)?ITM_RING:ITM_AMULET,randA(2)?2:1,item_);
		break;
	case 20://�߹� ���� ��ű�
		makeitem(ITM_RING,randA(1)?-2:-1,item_);
		break;
	case 21://����
		makeitem(ITM_FOOD,0,item_);
		break;
	case 22://�߹� ����
		makeitem(ITM_ARMOR_SHIELD,randA(4)?0:(randA(6)?1:-1),item_);
		break;
	case 25://å
		makeitem(ITM_BOOK,0,item_);
		break;
	case 26://����ī��
		makeitem(ITM_SPELL,0,item_);
		//index.push_back(createSpellCard(1, 0, item_));
		break;
	case 27://��Ƽ��Ʈ ����
		makeitem((item_type)rand_int(ITM_WEAPON_FIRST,ITM_WEAPON_CLOSE),randA(2)?0:(randA(3)?1:-1),item_);
		item_->artifact = true;
		break;
	case 28://��Ƽ��Ʈ ��
		{
			item_type atype_ = (item_type)rand_int(ITM_ARMOR_BODY_FIRST,ITM_ARMOR_BODY_LAST-1);
			if(randA(1)==0)
				atype_ = (item_type)rand_int(ITM_ARMOR_HEAD,ITM_ARMOR_BOOT);
			makeitem(atype_,randA(2)?0:(randA(3)?1:-1),item_);
			item_->artifact = true;
		}
		break;
	case 29://��Ƽ��Ʈ ����
		makeitem(ITM_RING,randA(9)?1:-1,item_);
		item_->artifact = true;
		break;
	case 30://�ߵ���
		makeitem(ITM_MISCELLANEOUS,1,item_);
		break;
	case 31://���丮
		makeitem(ITM_ETC,1,item_, EIT_SATORI);
		break;
	default:
		break;
	}
	return (*item_);
}

void create_id_to_item(int id, int level)
{
	vector<item_infor> index;
	item_infor temp;


	index.push_back(id_to_item(id, &temp));

	int x = randA(DG_MAX_X-1);
	int y=randA(DG_MAX_Y-1);
	int rand_x=0;
	int rand_y=0;
	int r=2+index.size()/3;
	int k=0;
	for(vector<item_infor>::iterator it=index.begin();it!=index.end();it++)
	{ 
		int x_ = 0, y_ = 0;
		Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_ITEM) || env[level].isStair(x_,y))
		{
			if(it==index.begin())
			{
				x = randA(DG_MAX_X-1);
				y = randA(DG_MAX_Y-1);
			}
			else
			{
				rand_x=rand_int(-r,r);
				rand_y=rand_int(-r,r);
				if(++k%5 == 0)
				{
					r++;
				}
			}
			Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		}
		item* item_ = env[level].MakeItem(coord_def(x_,y_),(*it));
		if((*it).artifact)
		{
			if((item_->type>=ITM_WEAPON_FIRST && item_->type< ITM_WEAPON_LAST)||(item_->type>=ITM_ARMOR_FIRST && item_->type< ITM_ARMOR_LAST)||(item_->type>=ITM_JEWELRY_FIRST && item_->type< ITM_JEWELRY_LAST))
			{ //��Ƽ��Ʈ �����
					MakeArtifact(item_,item_->curse?-1:1);
			}
		}

		k = 0;
		r=2+index.size()/3;
		rand_x=rand_int(-r,r);
		rand_y=rand_int(-r,r);
	}


}