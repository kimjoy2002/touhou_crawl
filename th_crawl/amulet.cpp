//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: amulet.cpp
//
// 내용: 부적
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "amulet.h"
#include "common.h"
#include "const.h"
#include "display.h"
#include "player.h"
#include "skill_use.h"
#include "environment.h"
#include "rect.h"
#include "mon_infor.h"
#include "event.h"
#include "soundmanager.h"


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
	"원숭이가 그려진 "
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
	switch (kind)
	{
	case AMT_PERFECT:
		return 2.0f;
	case AMT_OCCULT:
		return 1.5f;
	case AMT_BLOSSOM:
	case AMT_FAITH:
	case AMT_SPIRIT:
	case AMT_GRAZE:
	case AMT_WAVE:
		return 1.0f;
	case AMT_WEATHER:
	case AMT_TIMES:
		return 0.6f;

	}
	return 1.0f;
}
bool isCanCharge(amulet_type kind)
{
	switch (kind) {
	case AMT_FAITH:
	case AMT_PERFECT:
		return false;
	}
	return true;
}
bool isCanEvoke(amulet_type kind)
{
	return true;
}
bool chargingFinish(amulet_type kind, int value)
{
	switch (kind)
	{
	case AMT_GRAZE:
		if (value > 0) {
			you.SetGraze(-1);
			int temp = you.Ability(SKL_GRAZE, false, true, 1);
			if (temp) {
				you.Ability(SKL_GRAZE_OFF, false, false, temp);
			}
			enterlog();
		}
		else {
			int temp = you.Ability(SKL_GRAZE_OFF, false, true, 1);
			if (temp) {
				you.Ability(SKL_GRAZE_OFF, false, false, temp);
				//그레이즈를 조종중이면 그레이즈를 끄지않음
			} else 
			{
				you.s_graze = 0;
			}
		}
		break; 
	case AMT_WAVE:
		if (value > 0) {
			printlog("부적에 의해 영력 회복력이 올라갔다!", true, false, false, CL_blue);
		}
		else {
			printlog("더 이상 부적으로부터 영력 회복력을 받지 못한다.", true, false, false, CL_blue);
		}
		break;
	/*case AMT_WEATHER:
		if (value > 0) {
			printlog("부적에 의해 체력 재생력이 올라갔다!", true, false, false, CL_blue);
		}
		else {
			printlog("더 이상 부적으로부터 재생력을 받지 못한다.", true, false, false, CL_blue);
		}
		break;*/
	case AMT_FAITH:
		if (value > 0) {
			if (you.god == GT_NONE) {
				printlog("당신은 신앙이 없기때문에 모은 신앙심이 하늘로 날라갔다.", true, false, false, CL_blue);
				you.resetAmuletPercent(kind);
			}
			else {
				printlog("부적에 의해 신과 교감하였다!", true, false, false, CL_blue);
				if (you.god != GT_SEIJA)
					you.PietyUpDown(10);
				you.GiftCount(10);
				you.resetAmuletPercent(kind);
			}
		}
		break;
	}
	return true;
}

bool skill_soul_shot(int power, unit* order, coord_def target);
bool recharging_scroll(bool pre_iden_, bool ablity_, bool waste_);
bool skill_summon_occult_nesi(int power, bool short_, unit* order, coord_def target);
bool skill_summon_occult_long(int power, bool short_, unit* order, coord_def target);
bool skill_summon_occult_dish(int pow, bool short_, unit* order, coord_def target);
bool skill_summon_occult_small(int pow, bool short_, unit* order, coord_def target);
bool skill_summon_occult_kunekune(int pow, bool short_, unit* order, coord_def target);
bool skill_abusion(int power, bool short_, unit* order, coord_def target);

bool evokeAmulet(amulet_type kind, int value_) 
{

	switch (kind)
	{
	case AMT_PERFECT:
	case AMT_FAITH:
		//발동하지않음
		break;
	case AMT_BLOSSOM:
		soundmanager.playSound("soul_shot");
		printlog("팡! ", false, false, false, CL_white_blue);
		skill_soul_shot(0, &you, you.position);
		break;
	case AMT_TIMES:
	{
		soundmanager.playSound("buff");
		rand_rect_iterator rand_(you.position,2,2);
		int rand_num_ = rand_int(3, 6);
		while (!rand_.end()) {
			if (env[current_level].isMove(*rand_)) {
				item_infor temp;
				env[current_level].MakeItem(*rand_, makePitem(MON_MOOK, 1, &temp));
				rand_num_--;
				if (rand_num_ == 0)
					break;
			}
			rand_++;
		}
		break;
	}
	case AMT_WAVE:
		soundmanager.playSound("buff");
		printlog("당신은 영력을 회복했다. ", false, false, false, CL_normal);
		you.MpUpDown(rand_int(3, 5) + you.GetMaxMp()*rand_float(0.4f, 0.6f));
		/*if (env[current_level].isBamboo())
		{
			printlog("지형 탐지는 미궁의 죽림에선 효과를 보지 못한다.", true, false, false, CL_normal);
			return false;
		}
		else
		{
			soundmanager.playSound("buff");
			env[current_level].MakeMapping(100);
			printlog("당신은 현재 층을 감지해냈다.", true, false, false, CL_normal);
		}*/
		break;
	case AMT_SPIRIT:
		soundmanager.playSound("buff");
		return recharging_scroll(true, true, false);
		break;
	case AMT_GRAZE:
		soundmanager.playSound("buff");
		you.SetSuperGraze(rand_int(10, 15));
		printlog("당신은 순간적으로 회피에 모든 신경을 쏟는다!", false, false, false, CL_white_blue);
		break;
	case AMT_WEATHER:
		{
			soundmanager.playSound("buff");
			int weather_ = rand_int(1, 3);
			int time_ = rand_int(50, 80);
			you.SetBuff(BUFFSTAT_REGEN, BUFF_DUPLE, 3, time_);
			switch (weather_)
			{
			case 1:
				printlog("한치 앞이 안보이는 짙은 안개가 깔리기 시작했다.", true, false, false, CL_normal);
				you.SetWeather(1, time_);
				break;
			case 2:
				printlog("던전에 많은 비와 천둥번개가 휘몰아치기 시작한다.", true, false, false, CL_normal);
				you.SetWeather(2, time_);
				break;
			case 3:
				printlog("던전에 강한 햇빛이 들기 시작했다.", true, false, false, CL_normal);
				you.SetWeather(3, time_);
				break;
			default:
				break;
			}
		}
		/*soundmanager.playSound("buff");
		printlog("당신은 체력을 회복했다. ", false, false, false, CL_normal);
		you.HpUpDown(rand_int(10, 15) + you.GetMaxHp()*rand_float(0.15f, 0.25f), DR_NONE);*/
		break;
	case AMT_OCCULT:
		soundmanager.playSound("summon");
		skill_abusion(you.level * 5, false, &you, you.position);
		switch (value_)
		{
		case OCT_NESI:
			printlog("오컬트의 힘으로 도시전설 네시가 출현했다!", true, false, false, CL_magic);
			skill_summon_occult_nesi(you.level * 5, false, &you, you.position);
			break;
		case OCT_LONG:
			printlog("오컬트의 힘으로 도시전설 팔척귀신이 출현했다!", true, false, false, CL_magic);
			skill_summon_occult_long(you.level * 5, false, &you, you.position);
			break;
		case OCT_SHORT:
			printlog("오컬트의 힘으로 도시전설 리틀 그린맨들이 출현했다!", true, false, false, CL_magic);
			skill_summon_occult_small(you.level * 5, false, &you, you.position);
			break;
		case OCT_DISH:
			printlog("오컬트의 힘으로 도시전설 반쵸사라야시키가 출현했다!", true, false, false, CL_magic);
			skill_summon_occult_dish(you.level * 5, false, &you, you.position);
			break;
		case OCT_KUNEKUNE:
			printlog("오컬트의 힘으로 도시전설 쿠네쿠네가 출현했다!", true, false, false, CL_magic);
			skill_summon_occult_kunekune(you.level * 5, false, &you, you.position);
			break;
		}
		break;
	}
	return true;
}

const char* getOccultName(occult_type kind)
{
	switch (kind)
	{
	case OCT_NESI:
		return "네시";
	case OCT_LONG:
		return "팔척귀신";
	case OCT_SHORT:
		return "리틀그린맨";
	case OCT_DISH:
		return "반쵸사라야시키";
	case OCT_KUNEKUNE:
		return "쿠네쿠네";
	}
	return "정체불명";
}

bool skill_summon_occult_nesi(int power, bool short_, unit* order, coord_def target) {
	int time_ = rand_int(35, 50);
	dif_rect_iterator drit(order->position, 4, true);
	for (; !drit.end(); drit++)
	{
		if (summon_check(coord_def(drit->x, drit->y), order->position, false, true))
		{
			int flag_ = M_FLAG_SUMMON;
			if (order->isplayer())
				flag_ |= M_FLAG_ALLY;
			int id_ = MON_NESI;

			summon_info s_(order->GetMapId(), SKD_SUMMON_OCCULT, 1);
			if (monster* mon_ = env[current_level].AddMonster_Summon(id_, flag_, (*drit), s_, time_-1))
			{
				mon_->LevelUpdown(min(5,you.level - mondata[MON_NESI].level));
				for (auto spit = mon_->spell_lists.begin(); spit != mon_->spell_lists.end(); spit++)
				{
					spit->percent = spit->percent * (40 + (you.level * 3)) / 100;

				}
				mon_->CheckSightNewTarget();
				rect_iterator rit((*drit), 1, 1);
				
				for (; !rit.end(); rit++)
				{
					if ((*rit) == (*drit) || summon_check(*rit, *drit, false, false)) {
						env[current_level].MakeEvent(EVL_WATER, *rit, EVT_ALWAYS, time_);
					}
				}
				return true;
			}
		}
	}
	return false;
}

bool skill_summon_occult_long(int pow, bool short_, unit* order, coord_def target)
{
	int time_ = rand_int(50, 100);
	bool return_ = false;

	int i = 1;
	for (; i>0; i--)
	{
		if (monster *mon_ = BaseSummon(MON_OCCULT_LONG, time_, true, false, 2, order, target, SKD_SUMMON_OCCULT, 1))
		{
			mon_->LevelUpdown(you.level, 8.0f);
			return_ = true;
		}
	}
	return return_;
}
bool skill_summon_occult_dish(int pow, bool short_, unit* order, coord_def target)
{
	int time_ = rand_int(40, 80);
	bool return_ = false;

	int i = 1;
	for (; i>0; i--)
	{
		if (monster *mon_ = BaseSummon(MON_OCCULT_DISK, time_, true, false, 2, order, target, SKD_SUMMON_OCCULT, 1))
		{
			mon_->LevelUpdown(you.level, 5.0f, 1.2f);
			return_ = true;
		}
	}
	return return_;
}
bool skill_summon_occult_small(int pow, bool short_, unit* order, coord_def target)
{
	int time_ = rand_int(35, 70);
	bool return_ = false;

	int i = rand_int(3,4);
	for (; i>0; i--)
	{
		if (monster *mon_ = BaseSummon(MON_OCCULT_SMALL, time_, true, false, 2, order, target, SKD_SUMMON_OCCULT, 5))
		{
			mon_->LevelUpdown(you.level, 4.0f, 1.5f);
			return_ = true;
		}
	}
	return return_;
}
bool skill_summon_occult_kunekune(int pow, bool short_, unit* order, coord_def target)
{
	int time_ = rand_int(50, 80);
	bool return_ = false;

	int i = 1;
	for (; i>0; i--)
	{
		if (monster *mon_ = BaseSummon(MON_KUNEKUNE, time_, true, true, 4, order, target, SKD_SUMMON_OCCULT, 1))
		{
			mon_->LevelUpdown(you.level, 6.0f);
			return_ = true;
		}
	}
	return return_;
}