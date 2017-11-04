//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: amulet.h
//
// ����: �ƹķ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __AMULET_H__
#define  __AMULET_H__


enum amulet_type
{
	AMT_PERFECT = 0, //��������, 100%�� �Ǹ� ��Ȱ
	AMT_BLOSSOM, //�����, 100%�� �Ǹ� ���ݹߵ�
	AMT_TIMES, //����, 100%�� �Ǹ� ����
	AMT_FAITH, //�ž�, 100%�� �Ǹ� �ڵ����� �ž� ����
	AMT_WAVE, //����, 100%�� �Ǹ� ���ΰ���
	AMT_SPIRIT, //�ŷ�, 100%�� �Ǹ� ����ī�� ����
	AMT_GRAZE, //�׷�����, 100%�� �Ǹ� �׷��������, �ߵ��� �ټ�ȸ��
	AMT_WEATHER, //����, 100%�� �Ǹ� ü���������. ���� ȸ����밡��
	AMT_MAX,
	AMT_POPULAR, //�α⵵, 100%�� �Ǹ� 
	AMT_OCCULT, //����Ʈ, 100%�� �Ǹ� ��ȯ�� �߹氡�� + ��ȯ�ϱ�
};



extern char *amulet_uniden_string[AMT_MAX+2];
extern const char *amulet_iden_string[AMT_MAX+2];


int isAmuletGotValue(amulet_type amulet_);
amulet_type goodbadamulet(int good_bad);
int isGoodAmulet(amulet_type kind, int value);
bool equipamulet(amulet_type kind, int value); //���ϰ�: �ĺ��� true �̽ĺ��� false
bool unidenequipamulet(amulet_type kind, int value); //���ϰ�: �ĺ��� true �̽ĺ��� false
float getAmuletCharge(amulet_type kind);
bool isCanCharge(amulet_type kind);
bool isCanEvoke(amulet_type kind);
bool chargingFinish(amulet_type kind, int value);
bool evokeAmulet(amulet_type kind);

#endif // __AMULET_H__