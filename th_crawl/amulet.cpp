//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: amulet.cpp
//
// 내용: 부적
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "amulet.h"
#include "common.h"

char *amulet_uniden_string[AMT_MAX] =
{
	"쥐가 그려진 ",
	"소가 그려진 ",
	"호랑이가 그려진 ",
	"돼지가 그려진 ",
	"토끼가 그려진 ",
	"뱀이 그려진 ",
	"말이 그려진 ",
	"양이 그려진 ",
	"원숭이가 그려진 ",
	"닭이 그려진 "
};

const char *amulet_iden_string[AMT_MAX] =
{
	"완전무결의 ",
	"삼라결계의 ",
	"각부의 ",
	"신앙의 ",
	"전파의 ",
	"신령의 ",
	"그레이즈의 ",
	"날씨의 ",
	"인기도의 ",
	"오컬트의 "
};



int isAmuletGotValue(amulet_type amulet_)
{
	return 0;
	/*return ( amulet_ == AMT_AC || amulet_ == AMT_EV);*/
}

amulet_type goodbadamulet(int good_bad)
{
	return (amulet_type) randA(AMT_MAX - 1);
}

int isGoodAmulet(amulet_type kind, int value)
{
	return 1;
}

bool equipamulet(amulet_type kind, int value)
{
	return false;
}
bool unidenequipamulet(amulet_type kind, int value)
{
	return false;
}
float getAmuletCharge(amulet_type kind)
{
	return 1.0f;
}
bool isCanCharge(amulet_type kind)
{
	return true;
}