//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: const.cpp
//
// 내용: const관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "const.h"
#include "unit.h"

const char *tribe_type_string[TRI_MAX]=
{
	"인간",
	"마녀",
	"요정",
	"카라스텐구",
	"백랑텐구",
	"캇파",
	"네코마타",
	"용궁의사자",
	"츠쿠모가미",
	"오니",
	"반요",
	"망령",
	"흡혈귀",
	"요괴"
};
const bool tribe_string_back[TRI_MAX]=
{
	true,
	false,
	true,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	true,
	false,
	false
};


const char *job_type_string[JOB_MAX]=
{
	"전사",
	"마법사",
	"무녀",
	"검투사",
	"격투가",
	"마전사",
	"광전사",
	"화염술사",
	"냉기술사",
	"대지술사",
	"대기술사",
	////"수술사",
	"소환술사",
	//"독술사",
	//"전기술사",
	"연금술사",
	"심리학자",
	"사신",
	"광신도",
	"암살자",
	"농부",
	"메이드",
	"기술자",
	"실종자"
};

const bool job_string_back[JOB_MAX]=
{
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false
};


extern const char *dungeon_tile_tribe_type_string[]=
{
	"알수없음",
	"지면",
	"지면",
	"지면",
	"",
	"",//5
	"",
	"",
	"",
	"",
	"",//10
	"",
	"",
	"",
	"",
	"열린문",//15
	"내려가는 계단",
	"올라가는 계단",
	"모든 신전으로 가는 계단",
	"안개호수로 가는 계단",
	"요괴의 산으로 가는 계단",
	"홍마관으로 가는 계단",
	"도서관으로 가는 계단",
	"지하실로 가는 계단",
	"미궁의 죽림을 가는 길",
	"영원정으로 가는 계단",
	"지저로 가는 구멍",	
	"윳쿠리 둥지로 가는 계단",
	"짐승길로 향하는 길",
	"꿈의 세계로 가는 포탈",
	"달의 도시로 가는 길",
	"마계로 가는 포탈",
	"하쿠레이 신사의 계단",
	"입구로 돌아가는 계단",
	"시키에이키의 염마 제단",
	"뱌쿠렌의 명련사 제단",
	"카나코의 분사 제단",
	"스와코의 미샤구지 제단",
	"미노리코의 풍요 제단",
	"미마의 악령 제단",
	"신키의 마신 제단",
	"유우기의 괴력난신 제단",
	"시즈하의 단풍 제단",
	"히나의 재액 제단",
	"유카리의 스키마 제단",
	"에이린의 제단",
	"유유코의 요괴벚꽃 제단",
	"사토리의 제3의눈 제단",
	"텐시의 요석 제단",
	"",



	"돌벽",//50
	"돌벽",
	"붉은벽",
	"책장",
	"밀집된대나무",
	"철벽",
	"닫힌문",
	"유리",
	"석상",
	"깊은물",
};

const char *state_string[] = 
{
	"아사",
	"아사직전",
	"배고픔",
	"허기",
	"", //이 부분은 표시되지않는다.
	"배부름",
	"포식",
	"과식"
};


const D3DCOLOR CL_normal = D3DCOLOR_RGBA(255, 255, 255, 255);
const D3DCOLOR CL_bad = D3DCOLOR_RGBA(100, 100, 100, 255);
const D3DCOLOR CL_verybad = D3DCOLOR_RGBA(50, 50, 50, 255);
const D3DCOLOR CL_none = D3DCOLOR_RGBA(0, 0, 0, 255);
const D3DCOLOR CL_help = D3DCOLOR_RGBA(125, 200, 255, 255);
const D3DCOLOR CL_good = D3DCOLOR_RGBA(0, 255, 0, 255);
const D3DCOLOR CL_dark_good = D3DCOLOR_RGBA(0, 200, 0, 255);
const D3DCOLOR CL_blue = D3DCOLOR_RGBA(0, 50, 255, 255);
const D3DCOLOR CL_white_blue = D3DCOLOR_RGBA(100, 100, 255, 255);
const D3DCOLOR CL_tensi = D3DCOLOR_RGBA(185, 122, 87, 255);
const D3DCOLOR CL_alchemy = D3DCOLOR_RGBA(255, 128, 39, 255);
const D3DCOLOR CL_green = D3DCOLOR_RGBA(0, 200, 0, 255);
const D3DCOLOR CL_yuigi = D3DCOLOR_RGBA(215, 215, 255, 255);
const D3DCOLOR CL_hina = D3DCOLOR_RGBA(0, 200, 0, 255);
const D3DCOLOR CL_warning = D3DCOLOR_RGBA(255, 255, 0, 255); 
const D3DCOLOR CL_small_danger = D3DCOLOR_RGBA(255, 125, 125, 255); 
const D3DCOLOR CL_danger = D3DCOLOR_RGBA(255, 0, 0, 255); 
const D3DCOLOR CL_STAT = D3DCOLOR_XRGB(200,200,200);
const D3DCOLOR CL_speak = D3DCOLOR_RGBA(255, 255, 255, 255);
const D3DCOLOR CL_magic = D3DCOLOR_RGBA(255, 0, 255, 255);
const D3DCOLOR CL_white_puple = D3DCOLOR_RGBA(255, 128, 255, 255);
const D3DCOLOR CL_yuyuko = D3DCOLOR_RGBA(255, 200, 255, 255);
const D3DCOLOR CL_yukari = D3DCOLOR_RGBA(255, 128, 255, 255);
const D3DCOLOR CL_swako = D3DCOLOR_RGBA(125, 200, 255, 255);
const D3DCOLOR CL_autumn = D3DCOLOR_RGBA(255, 128, 39, 255);


const name_infor string_that("그것",true);
const name_infor string_something("무언가",false);

const char *item_weapon_string = "무기";
const char *item_throw_string = "탄막";
const char *item_armor_string = "방어구";
const char *item_potion_string = "물약";
const char *item_food_string = "음식";
const char *item_scroll_string = "두루마리";
const char *item_spell_string = "스펠카드";
const char *item_jewelry_string = "장신구";
const char *item_book_string = "책";
const char *item_miscellaneous_string = "발동";
const char *item_goal_string = "중요";

const int level_up_value[] = {
	10, 
	30,		//20	2
	70,		//40	3
	140,	//70	4
	260,	//120	5
	460,	//200	6
	800,	//340	7
	1400,	//600	8
	2500,	//1100	9
	3700,	//2200	10
	7700,	//4000	11
	15700,	//8000	12
	30000,	//14300	13
	50000,	//20000	14
	75000,	//25000	15
	106000,	//31000	16
	143000,	//37000	17
	186000,	//43000	18
	235000,	//49000	19
	290000,	//55000	20
	351000,	//61000	21
	418000,	//67000	22
	491000,	//73000	23
	570000,	//79000	24
	655000,	//85000	25
	746000,	//91000	26
	-1 //끝
};
