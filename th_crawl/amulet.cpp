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


LOCALIZATION_ENUM_KEY amulet_uniden_string[AMT_MAX] =
{
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_UNIDEN1,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_UNIDEN2,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_UNIDEN3,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_UNIDEN4,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_UNIDEN5,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_UNIDEN6,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_UNIDEN7,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_UNIDEN8,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_UNIDEN9
};

LOCALIZATION_ENUM_KEY amulet_iden_string[AMT_MAX] =
{
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_PERFECT,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_BLOSSOM,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_TIMES,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_FAITH,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_WAVE,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_SPIRIT,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_GRAZE,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_WEATHER,
	LOC_SYSTEM_ITEM_JEWELRY_AMULET_IDEN_OCCULT
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
		return 3.0f;
	case AMT_OCCULT:
	case AMT_BLOSSOM:
		return 1.5f;
	case AMT_FAITH:
	case AMT_SPIRIT:
	case AMT_GRAZE:
	case AMT_WAVE:
		return 1.0f;
	case AMT_WEATHER:
	case AMT_TIMES:
		return 0.6f;
	default:
		break;
	}
	return 1.0f;
}
bool isCanCharge(amulet_type kind)
{
	switch (kind) {
	case AMT_FAITH:
	case AMT_PERFECT:
	case AMT_TIMES:
		return false;
	default:
		break;
	}
	return true;
}
bool isCanEvoke(amulet_type kind)
{
	switch (kind) {
	case AMT_FAITH:
	case AMT_PERFECT:
	case AMT_TIMES:
		return false;
	default:
		break;
	}
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_WAVE_EQUIP), true, false, false, CL_blue);
		}
		else {
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_WAVE_UNEQUIP), true, false, false, CL_blue);
		}
		break;
	case AMT_FAITH:
		if (value > 0) {
			if (you.god == GT_NONE) {
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_FAITH_CHARGING_FAIL), true, false, false, CL_blue);
				you.resetAmuletPercent(kind, true);
			}
			else {
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_FAITH_CHARGING), true, false, false, CL_blue);
				if (you.god != GT_SEIJA)
					you.PietyUpDown(10);
				you.GiftCount(10);
				you.resetAmuletPercent(kind, true);
			}
		}
		break;
	case AMT_TIMES:
	if (value > 0)
	{
		soundmanager.playSound("buff");
		rand_rect_iterator rand_(you.position,2,2);
		int rand_num_ = rand_int(2, 4);
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
		you.resetAmuletPercent(kind, true);
		break;
	}
	default:
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
	case AMT_TIMES:
		//발동하지않음
		break;
	case AMT_BLOSSOM:
		soundmanager.playSound("soul_shot");
		printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_SCROLL_SOULSHOT) + " ", false, false, false, CL_white_blue);
		skill_soul_shot(0, &you, you.position);
		break;
	case AMT_WAVE:
		soundmanager.playSound("buff");
		printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_WAVE_HEAL) + " ", false, false, false, CL_normal);
		you.MpUpDown(rand_int(3, 5) + you.GetMaxMp()*rand_float(0.4f, 0.6f));
		break;
	case AMT_SPIRIT:
		soundmanager.playSound("buff");
		return recharging_scroll(true, true, false);
		break;
	case AMT_GRAZE:
		soundmanager.playSound("buff");
		you.SetSuperGraze(rand_int(10, 15));
		printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_GRAZE_SUPER), false, false, false, CL_white_blue);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_WEATHER_SMOKE), true, false, false, CL_normal);
				you.SetWeather(1, time_);
				break;
			case 2:
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_WEATHER_RAIN), true, false, false, CL_normal);
				you.SetWeather(2, time_);
				break;
			case 3:
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_WEATHER_SUNNY), true, false, false, CL_normal);
				you.SetWeather(3, time_);
				break;
			default:
				break;
			}
		}
		break;
	case AMT_OCCULT:
		soundmanager.playSound("summon");
		skill_abusion(you.level * 5, false, &you, you.position);
		switch (value_)
		{
		case OCT_NESI:
			printlog(LocalzationManager::formatString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_OCCULT_SUMMON,
				PlaceHolderHelper(LOC_SYSTEM_ITEM_OCCULT_NESI)), true, false, false, CL_magic);
			skill_summon_occult_nesi(you.level * 5, false, &you, you.position);
			break;
		case OCT_LONG:
			printlog(LocalzationManager::formatString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_OCCULT_SUMMON,
				PlaceHolderHelper(LOC_SYSTEM_ITEM_OCCULT_LONG)), true, false, false, CL_magic);
			skill_summon_occult_long(you.level * 5, false, &you, you.position);
			break;
		case OCT_SHORT:
			printlog(LocalzationManager::formatString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_OCCULT_SUMMON_MANY,
				PlaceHolderHelper(LOC_SYSTEM_ITEM_OCCULT_SHORT)), true, false, false, CL_magic);
			skill_summon_occult_small(you.level * 5, false, &you, you.position);
			break;
		case OCT_DISH:
			printlog(LocalzationManager::formatString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_OCCULT_SUMMON,
				PlaceHolderHelper(LOC_SYSTEM_ITEM_OCCULT_DISH)), true, false, false, CL_magic);
			skill_summon_occult_dish(you.level * 5, false, &you, you.position);
			break;
		case OCT_KUNEKUNE:
			printlog(LocalzationManager::formatString(LOC_SYSTEM_ITEM_JEWELRY_AMULET_OCCULT_SUMMON,
				PlaceHolderHelper(LOC_SYSTEM_ITEM_OCCULT_KUNEKUNE)), true, false, false, CL_magic);
			skill_summon_occult_kunekune(you.level * 5, false, &you, you.position);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return true;
}

string getOccultName(occult_type kind)
{
	switch (kind)
	{
	case OCT_NESI:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_OCCULT_NESI);
	case OCT_LONG:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_OCCULT_LONG);
	case OCT_SHORT:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_OCCULT_SHORT);
	case OCT_DISH:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_OCCULT_DISH);
	case OCT_KUNEKUNE:
		return LocalzationManager::locString(LOC_SYSTEM_ITEM_OCCULT_KUNEKUNE);
	default:
		break;
	}
	return LocalzationManager::locString(LOC_SYSTEM_ITEM_OCCULT_UNKNOWN);
}

bool skill_summon_occult_nesi(int power, bool short_, unit* order, coord_def target) {
	int time_ = rand_int(35, 50);
	dif_rect_iterator drit(order->position, 4, true);
	for (; !drit.end(); drit++)
	{
		if (summon_check(coord_def(drit->x, drit->y), order->position, false, true))
		{
			uint64_t flag_ = M_FLAG_SUMMON;
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