//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: dump.cpp
//
// 내용: 덤프하자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <direct.h>
#include <stdio.h>
#include <time.h>
#include <iomanip>
#include "player.h"
#include "display.h"
#include "environment.h"
#include "skill_use.h"
#include "note.h"
#include "god.h"
#include "dump.h"
#include "network.h"
#include "save.h"
#include "replay.h"
#include "mon_infor.h"
#include "tribe.h"

extern const char *version_string;


extern wstring morgue_path_w;



extern display_manager DisplayManager;


action_class::action_class():type(DACT_MELEE),name()
{
	for(int i=0;i<27;i++)
		num[i] = 0;

}

action_class::action_class(dump_action_type type_, string name_, int level_)
	:type(type_), name(name_)
{
	for(int i=0;i<27;i++)
		num[i] = 0;
	num[level_-1] = 1;
}

void action_class::SaveDatas(FILE *fp)
{
	SaveData<dump_action_type>(fp, type);
	
	char temp[100];
	sprintf_s(temp,100,"%s",name.c_str());
	SaveData<char>(fp,*temp, strlen(temp)+1);

	for(int i=0;i<27;i++)
		SaveData<int>(fp, num[i]);	
}
void action_class::LoadDatas(FILE *fp)
{	
	LoadData<dump_action_type>(fp, type);

	char temp[100];
	LoadData<char>(fp, *temp);
	name = temp;

	for(int i=0;i<27;i++)
		LoadData<int>(fp, num[i]);	

}












void makeAsciiDump(map<char, list<string >> *monster_list, char map_[17][17]);

int caculScore()
{
	long base = you.exper; 
	int rune_ = you.haveGoal() + you.ziggurat_level/9;
	if (you.rune[RUNE_SUBTERRANEAN]) //지저와 달의도시는 2개 분량 보너스
		rune_++;
	if (you.rune[RUNE_MOON]) //지저와 달의도시는 2개 분량 보너스
		rune_++;
	//지구랏 9층당 룬1개 수준의 점수
	base += 5000 * you.ziggurat_level;
	base += 10000 * rune_ + 1000* rune_*(rune_ +2);


	if(you.dead_reason == DR_ESCAPE && you.haveOrb())
	{ //클리어 했다.
		base += 6250000000 * (rune_*rune_) / (you.turn + 80000);
	}
	if(you.char_type != UNIQ_START_NONE) //캐릭터 패널티
	{		
		base*=0.7;
	}
	return base;
}



bool Dump(int type, wstring *filename_)
{
	if (ReplayClass.ReplayMode())
		return false;


	ostringstream ss;
	_wmkdir(morgue_path_w.c_str());
	FILE *fp;
	struct tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);

	wchar_t wfilename[256];

	swprintf_s(wfilename, 256, L"%s\\%s-%s-%04d%02d%02d-%02d%02d%02d.txt",
		morgue_path_w.c_str(),
		isNormalGame() ? L"dump" : (isArena() ? L"arena" : L"sprint"),
		ConvertUTF8ToUTF16(you.user_name).c_str(),
		1900 + t.tm_year, t.tm_mon + 1, t.tm_mday,
		t.tm_hour, t.tm_min, t.tm_sec);

    *filename_ = wfilename;
	if(_wfopen_s(&fp, wfilename, L"wt") != 0 || !fp){
		return false;  
	}
	unsigned char utf8_bom[] = { 0xEF, 0xBB, 0xBF };
	fwrite(utf8_bom, sizeof(unsigned char), 3, fp);

	ss << LocalzationManager::formatString(LOC_SYSTEM_DUMP_TITLE, PlaceHolderHelper(version_string)) << "\n\n";

	if (type == 1)
	{
		stringstream death_reason;

		if (wiz_list.wizard_mode == 1)
		{
			ss << "*" << LocalzationManager::locString(LOC_SYSTEM_WIZARD_MODE) << "*\n";
		}
		else if (wiz_list.wizard_mode == 2)
		{
			ss << "*" << LocalzationManager::locString(LOC_SYSTEM_SAVEREMAIN_MODE) << "*\n";
		}
		ss << caculScore() << "    " << LocalzationManager::locString(LOC_SYSTEM_LEVEL) << " " << you.level << " " << LocalzationManager::locString(tribe_type_string[you.tribe]) << LocalzationManager::locString(job_type_string[you.job]) << " " << you.GetCharNameString() << " \"" << you.user_name << "\" (HP " << you.GetHp() << "/" << you.GetMaxHp() << ")\n";
		ss << "             ";
		switch (you.dead_reason)
		{
		case DR_NONE:
		{
			stringstream temp_reason;
			if (you.dead_order)
			{
				temp_reason << "(" << to_string(you.dead_order->damage) << " " << LocalzationManager::locString(LOC_SYSTEM_DAMAGE);
				if (you.dead_order->order)
				{
					temp_reason << "," << you.dead_order->order->GetName()->getName();

				}
				temp_reason << ")";
			}
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_UNKNOWN, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
			break;
		}
		case DR_HITTING:
			if (you.dead_order)
			{
				stringstream temp_reason;
				if (you.dead_order->order)
				{
					temp_reason << you.dead_order->order->GetName()->getName();
				}
				switch (you.dead_order->type)
				{
				case ATT_NONE:
				case ATT_SMITE:
				default:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SMITE_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SMITE, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_SMASH:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SMASH_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SMASH, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_BLOOD:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_BLOOD_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_BLOOD, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_NOISE:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_NOISE_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_NOISE, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_SPEAR:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SPEAR_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SPEAR, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_NORMAL:
				case ATT_S_POISON:
				case ATT_M_POISON:
				case ATT_SICK:
				case ATT_NORMAL_HIT:
				case ATT_CURSE:
				case ATT_WEATHER:
				case ATT_AUTUMN:
				case ATT_CHOAS:
				case ATT_LUNATIC:
				case ATT_SLEEP:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_NORMAL_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_NORMAL, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_HOOF:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_HOOF_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_HOOF, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_VAMP:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_VAMP_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_VAMP, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_VEILING:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_VEILING_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_VEILING, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_RUSH:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_RUSH_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_RUSH, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_WALL:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_WALL_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_WALL, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_PSYCHO:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_PSYCHO_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_PSYCHO, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_STONE_TRAP:
					death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_TRAP, PlaceHolderHelper(CurrentLevelString()));
					break;
				case ATT_THROW_NORMAL:
				case ATT_THROW_WATER:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_TANMAC_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_TANMAC, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_NORMAL_BLAST:
				case ATT_AC_REDUCE_BLAST:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_BLAST_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_BLAST, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_SUN_BLAST:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SUN_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SUN, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_FIRE:
				case ATT_FIRE_WEAK:
				case ATT_THROW_FIRE:
				case ATT_CLOUD_FIRE:
				case ATT_FIRE_BLAST:
				case ATT_FIRE_PYSICAL_BLAST:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_FIRE_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_FIRE, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_COLD:
				case ATT_COLD_WEAK:
				case ATT_THROW_COLD:
				case ATT_CLOUD_COLD:
				case ATT_COLD_BLAST:
				case ATT_COLD_PYSICAL_BLAST:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_COLD_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_COLD, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_ELEC:
				case ATT_ELEC_WEAK:
				case ATT_CLOUD_ELEC:
				case ATT_ELEC_BLAST:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_ELEC_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_ELEC, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_POISON_BLAST:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_POISON_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_POISON, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_CLOUD_NORMAL:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_WIND_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_WIND, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_CLOUD_CURSE:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_CURSE_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_CURSE, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_BURST:
					if (you.dead_order->order) {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_BURST_BY, PlaceHolderHelper(temp_reason.str()));
					} else {
						death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_BURST, PlaceHolderHelper(CurrentLevelString()));
					}
					break;
				case ATT_DROWNING:
					death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_DROWNING), PlaceHolderHelper(CurrentLevelString());
					break;
				}
				death_reason << "(" << to_string(you.dead_order->damage) << " " << LocalzationManager::locString(LOC_SYSTEM_DAMAGE) << ")";
			}
			else {
				death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_UKNOWNDAMAGE, PlaceHolderHelper(CurrentLevelString()));
			}
			break;
		case DR_POISON:
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_ADDICTION, PlaceHolderHelper(CurrentLevelString()));
			break;
		case DR_FIRE:
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_FIRE, PlaceHolderHelper(CurrentLevelString()));
			break;
		case DR_POTION:
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_POTION, PlaceHolderHelper(CurrentLevelString()));
			if (you.dead_order) {
				death_reason << "(" << to_string(you.dead_order->damage) << " " << LocalzationManager::locString(LOC_SYSTEM_DAMAGE) << ")";
			}
			break;
		case DR_QUIT:
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_QUIT, PlaceHolderHelper(CurrentLevelString()));
			break;
		case DR_HUNGRY:
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_HUNGRY, PlaceHolderHelper(CurrentLevelString()));
			break;
		case DR_MIRROR:
			if (you.dead_order && you.dead_order->order) {
				death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_MIRROR_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(you.dead_order->order->GetName()->getName()));
			} else {
				death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_MIRROR, PlaceHolderHelper(CurrentLevelString()));
			}
			if (you.dead_order)
			{
				death_reason << "(" << to_string(you.dead_order->damage) << " " << LocalzationManager::locString(LOC_SYSTEM_DAMAGE) << ")";
			}
			break;
		case DR_MP:
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_JUNKO_MP, PlaceHolderHelper(CurrentLevelString()));
			break;
		case DR_JUNKO:
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_JUNKO_INSTANT, PlaceHolderHelper(CurrentLevelString()));
			break;
		case DR_SLEEP:
			if (you.dead_order && you.dead_order->order) {
				death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SLEEP_BY, PlaceHolderHelper(CurrentLevelString()), PlaceHolderHelper(you.dead_order->order->GetName()->getName()));
			} else {
				death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SLEEP, PlaceHolderHelper(CurrentLevelString()));
			}
			break;
		case DR_GHOST:
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_GHOST, PlaceHolderHelper(CurrentLevelString()));
			break;
		case DR_EFFECT:
			death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_SIDEEFFECT, PlaceHolderHelper(CurrentLevelString()));
			break;
		case DR_ESCAPE:
			if (you.haveOrb()) {
				death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_WIN, PlaceHolderHelper(to_string(you.haveGoal())));
			}
			else if (you.haveGoal()) {
				death_reason << LocalzationManager::formatString(LOC_SYSTEM_DUMP_DEATHREASON_COWARD, PlaceHolderHelper(to_string(you.haveGoal())));
			}
			else {
				death_reason << LocalzationManager::locString(LOC_SYSTEM_DUMP_DEATHREASON_FAIL);
			}
			break;
		}


		ss << death_reason.str() << "\n             ";
		ss << LocalzationManager::locString(LOC_SYSTEM_FINAL_TURN) <<  ' ' << you.turn << "\n\n";

		//스팀 API로 변경
		// sprintf_s(sql_, 256, "'%s'|%d|%d|'%s'|'%s'|'%s'|'%s'|%d|'%s'|%d|'%s'|'%s'", you.user_name.c_str(), you.level, caculScore(), LocalzationManager::locString(tribe_type_string[you.tribe]).c_str(), LocalzationManager::locString(job_type_string[you.job]).c_str(), you.GetCharNameString().c_str(), death_reason.str().c_str(),
		// 	you.turn, (you.god == GT_NONE) ? "" : GetGodString(you.god).c_str(), you.haveGoal(), version_string, isNormalGame() ? "normal" : (isArena() ? "arean" : (isSprint() ? "sprint" : "unknown"))
		// );


	}

	if(!you.GetCharNameString().empty()) {
		ss <<  you.user_name << " (" << LocalzationManager::locString(tribe_type_string[you.tribe]) << ' ' << LocalzationManager::locString(job_type_string[you.job]) << ' ' << you.GetCharNameString() << ")      " << LocalzationManager::locString(LOC_SYSTEM_TURNS) << ": " << you.turn << "      ";
	} 
	else {
		ss <<  you.user_name << " (" << LocalzationManager::locString(tribe_type_string[you.tribe]) << ' ' << LocalzationManager::locString(job_type_string[you.job]) << ")      " << LocalzationManager::locString(LOC_SYSTEM_TURNS) << ": " << you.turn << "      ";
	}


	if (you.god == GT_NONE)
	{
		ss << LocalzationManager::locString(LOC_SYSTEM_AHTEISM) << "\n\n";
	}
	else if (you.god == GT_MIKO) 
	{
		ss << LocalzationManager::locString(LOC_SYSTEM_FAITH) << ": " << GetGodString(you.god) << " (" <<  LocalzationManager::locString(LOC_SYSTEM_POULARITY) << ' ' << you.piety/2 << "%)\n\n";
	}
	else if (you.god == GT_TENSI)
	{
		ss << LocalzationManager::locString(LOC_SYSTEM_FAITH) << ": " << GetGodString(you.god) << "\n\n";
	}
	else
	{
		ss << LocalzationManager::locString(LOC_SYSTEM_FAITH) << ": " << GetGodString(you.god) << ' ' 
			<< (pietyLevel(you.piety)>=1?'*':'.') << (pietyLevel(you.piety)>=2?'*':'.') << (pietyLevel(you.piety)>=3?'*':'.') << (pietyLevel(you.piety)>=4?'*':'.') << (pietyLevel(you.piety)>=5?'*':'.') << (pietyLevel(you.piety)>=6?'*':'.') << "\n\n";
	}
	ss << "HP: " << std::setfill(' ') << std::setw(4) << you.GetHp() << "/" << std::setw(4) << you.GetMaxHp() << "             AC:" << std::setw(4) << you.ac << "             ";
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_STR);
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_STR)) < 4)
		ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_STR)), ' ');
	ss << ":" << you.s_str << "\n";
	
	if (!you.pure_mp)
	{
		ss << "MP: " << std::setw(4) << you.GetMp() << "/" << std::setw(4) << you.GetMaxHp() << "             EV:" << std::setw(4) << you.ev << "             ";
		ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX);
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX)) < 4)
			ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX)), ' ');
		ss << ":" << you.s_dex  << "\n";
	}
	else
	{
		ss << "(" << LocalzationManager::locString(LOC_SYSTEM_MP_PURITY) << ")";

		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_MP_PURITY)) < 24)
		ss << std::string(24-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_MP_PURITY)), ' ');
		ss << "EV:" << std::setw(4) << you.ev << "             ";
		ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX);
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX)) < 4)
			ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_DEX)), ' ');
		ss << ":" << you.s_dex << "\n";
	}
												
	{
		int pow_ = min(you.power, 500);
		ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER) << ": " << pow_ / 100 << '.' << std::setfill('0') << std::setw(2) << pow_ % 100;

		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER)) < 20)
			ss << std::string(20-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER)), ' ');
		ss << "SH:" << std::setfill(' ') << std::setw(4) << you.sh << "             ";
		ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_INT);
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_INT)) < 4)
			ss << std::string(4-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_INT)), ' ');
		ss << ":" << you.s_int << "\n";
	}

	int max_length_fcep = 4;
	max_length_fcep = max(max_length_fcep, PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_FIRE_RESIST)));
	max_length_fcep = max(max_length_fcep, PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_COLD_RESIST)));
	max_length_fcep = max(max_length_fcep, PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_ELEC_RESIST)));
	max_length_fcep = max(max_length_fcep, PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POISON_RESIST)));
	



	int resist_ = you.fire_resist;
	int resist2_ = you.confuse_resist;
	string fire_resist_string = LocalzationManager::locString(LOC_SYSTEM_SHORT_FIRE_RESIST);
	if(PrintCharWidth(fire_resist_string) < max_length_fcep) {
		fire_resist_string = std::string(max_length_fcep-PrintCharWidth(fire_resist_string), ' ') + fire_resist_string;
	}

	int offset1_ = PrintCharWidth(fire_resist_string) +  PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_CONFUSE_RESIST)); 
	ss << fire_resist_string << ": "
		<< ((resist_ >= 100) ? "∞" :
			(resist_ >= 1) ? "+" :
			(resist_ <= -1) ? "-" : ".")
		<< ((resist_ >= 100) ? ' ' :
			(resist_ >= 2) ? '+' :
			(resist_ <= -2) ? '-' : '.')
		<< ((resist_ >= 100) ? ' ' :
			(resist_ >= 3) ? '+' :
			(resist_ <= -3) ? '-' : '.');
	if(offset1_ < 23)
		ss << std::string(23-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_CONFUSE_RESIST) << ": " << (resist2_>=1?'+':(resist2_<=-1?'-':'.'));
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_WEAPON)) < 16)
		ss << std::string(16-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_WEAPON)), ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_WEAPON) << ": ";
	if(you.equipment[ET_WEAPON]) {
		ss << you.equipment[ET_WEAPON]->id << ") " << you.equipment[ET_WEAPON]->GetName() << "\n";
	}
	else {
		ss << LocalzationManager::locString(LOC_SYSTEM_UI_UNARMED) << "\n";
	}
	


	resist_ = you.ice_resist;
	resist2_ = you.invisible_view;
	string ice_resist_string = LocalzationManager::locString(LOC_SYSTEM_SHORT_COLD_RESIST);
	if(PrintCharWidth(ice_resist_string) < max_length_fcep) {
		ice_resist_string = std::string(max_length_fcep-PrintCharWidth(ice_resist_string), ' ') + ice_resist_string;
	}

	offset1_ = PrintCharWidth(ice_resist_string) +  PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_SEE_INVISIBLE)); 
	ss << ice_resist_string << ": " 
		<< ((resist_ >= 100) ? "∞" :
			(resist_ >= 1) ? "+" :
			(resist_ <= -1) ? "-" : ".")
		<< ((resist_ >= 100) ? ' ' :
			(resist_ >= 2) ? '+' :
			(resist_ <= -2) ? '-' : '.')
		<< ((resist_ >= 100) ? ' ' :
			(resist_ >= 3) ? '+' :
			(resist_ <= -3) ? '-' : '.');
	if(offset1_ < 23)
		ss << std::string(23-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_SEE_INVISIBLE) << ": " << (resist2_>=1?'+':(resist2_<=-1?'-':'.'));
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_TANMAC)) < 16)
		ss << std::string(16-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_TANMAC)), ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_TANMAC) << ": ";
	if(you.throw_weapon) {
		ss << you.throw_weapon->id << ") " << you.throw_weapon->GetName() << "\n";
	}
	else {
		ss << LocalzationManager::locString(LOC_SYSTEM_UI_NONE) << "\n";
	}


	
	resist_ = you.elec_resist;
	resist2_ = you.power_keep;
	string elec_resist_string = LocalzationManager::locString(LOC_SYSTEM_SHORT_ELEC_RESIST);
	if(PrintCharWidth(elec_resist_string) < max_length_fcep) {
		elec_resist_string = std::string(max_length_fcep-PrintCharWidth(elec_resist_string), ' ') + elec_resist_string;
	}
	offset1_ = PrintCharWidth(elec_resist_string) +  PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER_KEEP)); 
	ss << elec_resist_string << ": " 
		<< ((resist_ >= 100) ? "∞" :
			(resist_ >= 1) ? "+" :
			(resist_ <= -1) ? "-" : ".")
		<< ((resist_ >= 100) ? ' ' :
			(resist_ >= 2) ? '+' :
			(resist_ <= -2) ? '-' : '.')
		<< ((resist_ >= 100) ? ' ' :
			(resist_ >= 3) ? '+' :
			(resist_ <= -3) ? '-' : '.');
	if(offset1_ < 23)
		ss << std::string(23-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_SHORT_POWER_KEEP) << ": " << (you.power == 1000 ? "∞": (resist2_>=1?"+ ":(resist2_<=-1?"- ":". ")));
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_BODY)) < 15)
		ss << std::string(15-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_BODY)), ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_BODY) << ": ";
	if(you.equipment[ET_ARMOR]) {
		ss << you.equipment[ET_ARMOR]->id << ") " << you.equipment[ET_ARMOR]->GetName() << "\n";
	}
	else {
		ss << (you.isImpossibeEquip(ET_ARMOR, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP)) << "\n";
	}

	
	resist_ = you.poison_resist;
	string poison_resist_string = LocalzationManager::locString(LOC_SYSTEM_SHORT_POISON_RESIST);
	if(PrintCharWidth(poison_resist_string) < max_length_fcep) {
		poison_resist_string = std::string(max_length_fcep-PrintCharWidth(poison_resist_string), ' ') + poison_resist_string;
	}
	offset1_ = PrintCharWidth(poison_resist_string) +  PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_SHIELD)); 
	ss << poison_resist_string << ": " << (resist_>=1?('+'):(resist_<=-1?'-':'.'));
	if(offset1_ < 44)
		ss << std::string(44-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_SHIELD) << ": ";
	if(you.equipment[ET_SHIELD]) {
		ss << you.equipment[ET_SHIELD]->id << ") " << you.equipment[ET_SHIELD]->GetName() << "\n";
	}
	else {
		ss << (you.isImpossibeEquip(ET_SHIELD, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP)) << "\n";
	}





	string resist_text_ = "";
	{
		for (int i = 0; i < 10; i++) {
			if (you.GetResist() > 110 + i * 20) {
				resist_text_ += "#";
			}
			else {
				resist_text_ += ".";
			}
		}
	}
	string magic_resist_string = LocalzationManager::locString(LOC_SYSTEM_SHORT_MAGICRESIST);
	if(PrintCharWidth(magic_resist_string) < 8) {
		magic_resist_string = std::string(8-PrintCharWidth(magic_resist_string), ' ') + magic_resist_string;
	}
	offset1_ = PrintCharWidth(magic_resist_string) + PrintCharWidth(resist_text_) +  PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_HEAD)); 
	ss << magic_resist_string << ": " << resist_text_;
	if(offset1_ < 45)
		ss << std::string(45-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_HEAD) << ": ";
	if(you.equipment[ET_HELMET]) {
		ss << you.equipment[ET_HELMET]->id << ") " << you.equipment[ET_HELMET]->GetName() << "\n";
	}
	else {
		ss << (you.isImpossibeEquip(ET_HELMET, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP)) << "\n";
	}

	offset1_ = PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_CLOAK));
	if(offset1_ < 47)
		ss << std::string(47-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_CLOAK) << ": ";
	if(you.equipment[ET_CLOAK]) {
		ss << you.equipment[ET_CLOAK]->id << ") " << you.equipment[ET_CLOAK]->GetName() << "\n";
	}
	else {
		ss << (you.isImpossibeEquip(ET_CLOAK, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP)) << "\n";
	}


	offset1_ = PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_HAND));
	if(offset1_ < 47)
		ss << std::string(47-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_HAND) << ": ";
	if(you.equipment[ET_GLOVE]) {
		ss << you.equipment[ET_GLOVE]->id << ") " << you.equipment[ET_GLOVE]->GetName() << "\n";
	}
	else {
		ss << (you.isImpossibeEquip(ET_GLOVE, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP)) << "\n";
	}

	offset1_ = PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_FOOT));
	if(offset1_ < 47)
		ss << std::string(47-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_FOOT) << ": ";
	if(you.equipment[ET_BOOTS]) {
		ss << you.equipment[ET_BOOTS]->id << ") " << you.equipment[ET_BOOTS]->GetName() << "\n";
	}
	else {
		ss << (you.isImpossibeEquip(ET_BOOTS, false)?LocalzationManager::locString(LOC_SYSTEM_UI_NONE):LocalzationManager::locString(LOC_SYSTEM_UI_CANT_EQUIP)) << "\n";
	}


	offset1_ = PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_AMULET));
	if(offset1_ < 47)
		ss << std::string(47-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_AMULET) << ": ";
	if(you.equipment[ET_NECK]) {
		ss << you.equipment[ET_NECK]->id << ") " << you.equipment[ET_NECK]->GetName() << "\n";
	}
	else {
		ss << LocalzationManager::locString(LOC_SYSTEM_UI_NONE) << "\n";
	}



	offset1_ = PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_LEFT_RING));
	if(offset1_ < 47)
		ss << std::string(47-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_LEFT_RING) << ": ";
	if(you.equipment[ET_LEFT]) {
		ss << you.equipment[ET_LEFT]->id << ") " << you.equipment[ET_LEFT]->GetName() << "\n";
	}
	else {
		ss << LocalzationManager::locString(LOC_SYSTEM_UI_NONE) << "\n";
	}

	offset1_ = PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_UI_RIGHT_RING));
	if(offset1_ < 47)
		ss << std::string(47-offset1_, ' ');
	ss << LocalzationManager::locString(LOC_SYSTEM_UI_RIGHT_RING) << ": ";
	if(you.equipment[ET_RIGHT]) {
		ss << you.equipment[ET_RIGHT]->id << ") " << you.equipment[ET_RIGHT]->GetName() << "\n";
	}
	else {
		ss << LocalzationManager::locString(LOC_SYSTEM_UI_NONE) << "\n";
	}

	
	ss << "\n" << LocalzationManager::locString(LOC_SYSTEM_ITEM_RUNE_RUNE) << ":";
	int first_rune_ = 0;
	for(int i=0;i<RUNE_HAKUREI_ORB;i++)
	{		
		if(you.rune[i])
		{
			if(first_rune_ !=0)
				ss << ", ";
			ss << LocalzationManager::locString(rune_string[i]);
			first_rune_++;
		}
	}
	ss << "\n";
	if(you.rune[RUNE_HAKUREI_ORB])
	{
		ss << LocalzationManager::locString(LOC_SYSTEM_ITEM_YINYANG);
	}
	else
	{				
		ss << "\n";
	}

	ss << "\n\n\n<" << LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_PROPERTY) << ">\n";

	if (you.property_vector.empty())
	{
		ss << LocalzationManager::locString(LOC_SYSTEM_DISPLAY_MANAGER_NO_PROPERTY) << ">\n";
	}
	else {
		for (auto it = you.property_vector.begin(); it != you.property_vector.end(); it++)
		{
			ss << it->GetInfor() << "\n";
		}
	}

	ss << "\n\n" << LocalzationManager::formatString(LOC_SYSTEM_DUMP_PLACE_IN, PlaceHolderHelper(CurrentLevelString())) << "\n";

	ss << "\n\n\n<" << LocalzationManager::locString(LOC_SYSTEM_INVENTORY) << ">\n"; 

	
	list<item>::iterator first,end;
	first = you.item_list.begin();
	end = you.item_list.end();

	for(item_type_simple i = ITMS_FIRST ;i != ITMS_LAST ; i=(item_type_simple)(i+1))
	{
		bool exist = false;
		list<item>::iterator it;
		for(it = first; it!=end;it++)
		{
			if((*it).isSimpleType(i))
			{
				int equip = you.isequip(it);
				if(!exist)
				{
					ss << "\n" << GetItemTypeSting(i) << "\n";
					exist = true;
				}
				ss  << "  " << (*it).id << " - " << (*it).GetName();
				if(equip) {
					ss  << "(";
					if(equip == 1) {
						ss  << LocalzationManager::locString(LOC_SYSTEM_EQUIP);
					}
					else if(equip == 2) {
						ss  << LocalzationManager::locString(LOC_SYSTEM_LEFT_HAND);
					}
					else  {
						ss  << LocalzationManager::locString(LOC_SYSTEM_RIGHT_HAND);
					}
					ss  << ")";
				}
				ss << "\n";
			}
		}
	}

	ss << "\n\n\n<" << LocalzationManager::locString(LOC_SYSTEM_SKILL) << ">\n"; 

	int skt = 0;
	while(skt < SKT_MAX)
	{
		if (you.pure_skill == skt)
		{
			if(PrintCharWidth(skill_string((skill_type)skt)) < 12) {
				ss << std::string(12-PrintCharWidth(skill_string((skill_type)skt)), ' ');
			}
			ss << skill_string((skill_type)skt);
			ss << ' ' << std::setw(3) << you.GetSkillLevel(skt, false) << " (" <<  LocalzationManager::locString(LOC_SYSTEM_SKILL_JUNKA) << ")\n";
		}
		else if (you.GetSkillLevel(skt, false)) {
			if(PrintCharWidth(skill_string((skill_type)skt)) < 12) {
				ss << std::string(12-PrintCharWidth(skill_string((skill_type)skt)), ' ');
			}
			ss << skill_string((skill_type)skt);
			ss << ' ' << std::setw(3) << you.GetSkillLevel(skt, false) << " (" << GetSkillPercent(you.skill[skt]) << "%)\n";
		}
		skt++;
	}


	ss << "\n\n\n<" << LocalzationManager::locString(LOC_SYSTEM_REMEMBER_MAGIC) << ">\n"; 
	if(you.currentSpellNum) {
		ss << "\n";
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_NAME)) < 34) {
			ss << std::string(34-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_NAME)), ' ');
		}
		ss << LocalzationManager::locString(LOC_SYSTEM_NAME) << " ";
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SCHOOL)) < 20) {
			ss << std::string(20-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_SCHOOL)), ' ');
		}
		ss << LocalzationManager::locString(LOC_SYSTEM_SCHOOL) << " ";
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_FAILURE_RATE)) < 12) {
			ss << std::string(12-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_FAILURE_RATE)), ' ');
		}
		ss << LocalzationManager::locString(LOC_SYSTEM_FAILURE_RATE) << " ";
	}
	for(int i=0;i<52;i++)
	{
		if(you.MemorizeSpell[i])
		{
			spell_list spell_ = (spell_list)you.MemorizeSpell[i];

			ss << "\n" << (char)(i<26?('a'+i):('A'+(i-26))) << " - ";
			if(PrintCharWidth(SpellString(spell_)) < 30) {
				ss << std::string(30-PrintCharWidth(SpellString(spell_)), ' ');
			}
			ss << SpellString(spell_) << " ";
			if(PrintCharWidth(GetSpellSchoolString(spell_)) < 20) {
				ss << std::string(20-PrintCharWidth(GetSpellSchoolString(spell_)), ' ');
			}
			ss << GetSpellSchoolString(spell_) << " ";
			if(PrintCharWidth(to_string(100-you.GetSpellSuccess(spell_))) < 9) {
				ss << std::string(9-PrintCharWidth(to_string(100-you.GetSpellSuccess(spell_))), ' ');
			}
			ss << to_string(100-you.GetSpellSuccess(spell_)) << "%";
		}
	}
	if(you.currentSpellNum) {
		ss << "\n\n" << LocalzationManager::formatString(LOC_SYSTEM_UI_LEARN_SPELL_REMAIN, PlaceHolderHelper(to_string(you.currentSpellNum)), PlaceHolderHelper(to_string(you.remainSpellPoiont))) << "\n"; 
	}
	else {
		ss << "\n" << LocalzationManager::locString(LOC_SYSTEM_UI_NOT_LEARN_SPELL) << "\n"; 
	}


	ss << "\n\n\n";

	

	{
		map<char, list<string >> monster_list;
		char temp_map_[17][17];
		makeAsciiDump(&monster_list,temp_map_);
		for (int y = 0; y < 17; y++) {
			for (int x = 0; x < 17; x++) {
				ss << temp_map_[x][y];
			}
			ss << "\n";
		}
		for (auto it = monster_list.begin(); it != monster_list.end(); it++) {
			ss << it->first << ":";
			boolean first = true;
			for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				if(!first)
					ss << ", ";
				ss << it2->c_str();
				first = false;
			}
			ss << "\n";
		}
	}
	ss << "\n\n\n";

	if(!DisplayManager.text_log.text_list.empty())
	{
		list<text_dummy*>::iterator it;
		it = DisplayManager.text_log.text_list.end();
		it--;
		int view_length = DisplayManager.log_length;
		int i = 15;
		while(i)
		{
			if(it == DisplayManager.text_log.text_list.begin())
				break;
			it--;
			if((*it)->enter)
			{
				i--;
				if(i<=0)
				{
					it++;
					break;
				}
			}
		}
		for(i = 0;i < view_length && it != DisplayManager.text_log.text_list.end();it++)
		{
			ss << ConvertUTF16ToUTF8((*it)->text);
			if((*it)->enter)
			{
				ss << "\n";
			}
		}
	}

	if (type == 1)
	{
		ss << "\n\n\n<" << LocalzationManager::locString(LOC_SYSTEM_DUMP_SPIECIAL_VAULT) << ">\n\n"; 
		for (int i = 0; i < MAXLEVEL; i++)
		{
			if (!env[i].speciel_map_name.empty())
			{
				int k = 0;

				if(PrintCharWidth(CurrentLevelString(i)) < 12) {
					ss << std::string(12-PrintCharWidth(CurrentLevelString(i)), ' ');
				}
				ss << CurrentLevelString(i) << ":";

				for (auto it = env[i].speciel_map_name.begin(); it != env[i].speciel_map_name.end(); )
				{
					ss << (*it);
					it++;
					k++;
					if (it != env[i].speciel_map_name.end())
					{
						ss << ", ";
						if (k % 5 == 0)
						{
							ss << "\n" << std::string(13, ' ');
						}
					}
				}
				ss << "\n";
			}
		}
	}

	ss << "\n\n\n";


	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_TURNS)) < 8) {
		ss << std::string(8-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_TURNS)), ' ');
	}
	ss << LocalzationManager::locString(LOC_SYSTEM_TURNS) << "|";
	if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_PLACE)) < 18) {
		ss << std::string(18-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_PLACE)), ' ');
	}
	ss << LocalzationManager::locString(LOC_SYSTEM_PLACE) << "|";
	ss << LocalzationManager::locString(LOC_SYSTEM_NOTE) << "\n";


	for(list<note_dummy>::iterator it = save_note.note_list.begin(); it != save_note.note_list.end(); it++)
	{
		if(PrintCharWidth(to_string(it->turn)) < 8) {
			ss << std::string(8-PrintCharWidth(to_string(it->turn)), ' ');
		}
		ss << to_string(it->turn) << "|";
		if(PrintCharWidth(it->place) < 18) {
			ss << std::string(18-PrintCharWidth(it->place), ' ');
		}
		ss << it->place << "|";
		ss << it->text << "\n";
	}
	ss << "\n\n\n";

	
	ss << std::string(26, ' '); 
	for(int i=0;i<9;i++) {
		ss << "│ " << std::setw(2) << 1+i*3 << "-" << std::setw(2) << 3+i*3;
	}
	ss << "┃ " << LocalzationManager::locString(LOC_SYSTEM_SUM) << "\n";



	dump_action_type type_ = DACT_NONE;
	for(auto it = you.action_vector.begin(); it != you.action_vector.end(); it++)
	{
		int total_ = 0;
		if(it->type != type_)
		{
			type_ = it->type;

			ss << GetDumpActionString(type_);
			if(PrintCharWidth(GetDumpActionString(type_)) < 26) {
				ss << std::string(26-PrintCharWidth(GetDumpActionString(type_)), '-');
			}

			for(int i=0;i<9;i++)
				ss << "┼------";
			ss << "╂───\n";
		}

		if(PrintCharWidth(it->name) < 26) {
			ss << std::string(26-PrintCharWidth(it->name), ' ');
		}
		ss << it->name;

		for(int i=0;i<9;i++)
		{
			int add_ = it->num[0+i*3]+it->num[1+i*3]+it->num[2+i*3];
			ss << "│" << std::setw(6) << add_;
			total_ += add_;
		}

		ss << "┃" << std::setw(6) << total_ << "\n";
	}




	fprintf_s(fp,"%s",ss.str().c_str());

	fclose(fp);
	return true;
}
string GetDumpActionString(dump_action_type type_)
{
	switch(type_)
	{
	case DACT_MELEE:
		return LocalzationManager::locString(LOC_SYSTEM_DUMP_ACTION_TYPE_MELEE);
	case DACT_SHOOT:
		return LocalzationManager::locString(LOC_SYSTEM_DUMP_ACTION_TYPE_SHOOT);
	case DACT_SPELL:
		return LocalzationManager::locString(LOC_SYSTEM_DUMP_ACTION_TYPE_SPELL);
	case DACT_INVOKE:
		return LocalzationManager::locString(LOC_SYSTEM_DUMP_ACTION_TYPE_INVOKE);
	case DACT_EVOKE:
		return LocalzationManager::locString(LOC_SYSTEM_DUMP_ACTION_TYPE_EVOKE);
	case DACT_USE:
		return LocalzationManager::locString(LOC_SYSTEM_DUMP_ACTION_TYPE_USE);
	default:
		return LocalzationManager::locString(LOC_SYSTEM_DUMP_ACTION_TYPE_ETC);
	}

}

void makeAsciiDump(map<char, list<string >> *monster_list, char map_[17][17]) {
	int x_ = you.position.x - 8;
	int y_ = you.position.y - 8;
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			int c_x_ = i + x_, c_y_ = j + y_;
			if (c_x_ >= 0 && c_y_ >= 0 && c_x_ < DG_MAX_X && c_y_ < DG_MAX_Y)
			{
				if (env[current_level].isInSight(coord_def(c_x_, c_y_))) {
					unit* target_unit = env[current_level].isMonsterPos(c_x_, c_y_);
					if (target_unit != NULL) {
						char mon_dot = target_unit->getAsciiDot();
						map_[i][j] = mon_dot;
						if (!target_unit->isplayer()) {
							monster* target_mon = (monster*)target_unit;
							if (!(target_mon->flag & M_FLAG_UNHARM))
							{
								auto it = monster_list->find(mon_dot);
								if (it == monster_list->end()) {
									list<string> new_list;

									if (target_mon->isUserAlly())
										new_list.push_back(target_mon->name.getName()+"♡");
									else 
										new_list.push_back(target_mon->name.getName());
									(*monster_list)[mon_dot] = new_list;
								}
								else {
									if (target_mon->isUserAlly())
										it->second.push_back(target_mon->name.getName() + "♡");
									else
										it->second.push_back(target_mon->name.getName());
								}
							}
						}
					}
					else {
						map_[i][j] = env[current_level].getAsciiDot(c_x_, c_y_);
					}
				}
				else if ((env[current_level].isExplore(c_x_, c_y_) || env[current_level].isMapping(c_x_, c_y_)))
				{
					map_[i][j] = env[current_level].getAsciiDot(c_x_, c_y_);
				}
				else {
					map_[i][j] = ' ';
				}
			}
			else {
				map_[i][j] = ' ';
			}
		}
	}

}

