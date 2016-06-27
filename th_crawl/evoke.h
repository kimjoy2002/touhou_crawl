//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: evoke.h
//
// 내용: 발동템들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


enum evoke_kind
{
	EVK_PAGODA,
	EVK_AIR_SCROLL,
	EVK_DREAM_SOUL,
	EVK_MAX
};

extern const char *evoke_string[EVK_MAX];
struct item_infor;


bool evoke_evokable(evoke_kind kind);
int Evokeusepower(evoke_kind skill, bool max_);

void MakeEvokeItem(item_infor* t, int kind_ = -1);