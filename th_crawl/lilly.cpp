//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: lilly.cpp
//
// 내용: 릴리
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "lilly.h"
#include "unit.h"
#include "monster.h"
#include "environment.h"
#include "mon_infor.h"
#include "skill_use.h"


int getMaxFairyName(){return 20;};

LOCALIZATION_ENUM_KEY fairy_name[] =
{
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME1,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME2,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME3,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME4,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME5,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME6,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME7,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME8,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME9,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME10,

	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME11,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME12,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME13,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME14,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME15,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME16,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME17,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME18,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME19,
	LOC_SYSTEM_GOD_LILLY_FAIRY_NAME20
};






string fairy_speak(monster* monster_info, int personal, FAIRY_SPEAK type)
{
	
	switch(monster_info->id)
	{
	case MON_DIEFAIRY:
		switch(type)
		{
		case FS_NORMAL:
				switch(randA(5))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));		
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));			
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
	case MON_SUNNY:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
			break;
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_LUNAR:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));		
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));		
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
			break;
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_STAR:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
			break;
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_CIRNO:		
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_CLOWNPIECE:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_LARVA:
		switch (type)
		{
		case FS_NORMAL:
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	default:
		break;
	}





	switch(personal)
	{
	default:		
	case FP_NORMAL:
		switch (type)
		{
		case FS_NORMAL:
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COMMON_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COMMON_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COMMON_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COMMON_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COMMON_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COMMON_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COMMON_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COMMON_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COMMON_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case FP_SHY:
		switch (type)
		{
		case FS_NORMAL:
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_SHY_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_SHY_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_SHY_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_SHY_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_SHY_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_SHY_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_SHY_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_SHY_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_SHY_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case FP_BRAVE:
		switch (type)
		{
		case FS_NORMAL:
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_BRAVE_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_BRAVE_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_BRAVE_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_BRAVE_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_BRAVE_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_BRAVE_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_BRAVE_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_BRAVE_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_BRAVE_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case FP_COLD:
		switch (type)
		{
		case FS_NORMAL:
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COLD_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COLD_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COLD_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COLD_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COLD_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COLD_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COLD_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COLD_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_COLD_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case FP_ANNOY:
		switch (type)
		{
		case FS_NORMAL:
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_ANNOY_FREIND1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_ANNOY_FREIND2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_ANNOY_FREIND3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_ANNOY_FREIND4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_ANNOY_FREIND5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_ANNOY_FREIND6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		case FS_ENTER:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_ANNOY_ENTER), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_FAIRY_WAR:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_ANNOY_FAIRY_WAR), PlaceHolderHelper(monster_info->GetName()->getName()));
		case FS_REVIVE:
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FAIRY_ANNOY_REVIVE), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	}
	
	return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NORMAL), PlaceHolderHelper(monster_info->GetName()->getName()));

}



void GetFairyExp(int exp)
{
	int enter_ = 0;
	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end();it++)
	{
		for(int i = 0; i<5;i++)
		{
			if(you.god_value[GT_LILLY][i] == 1)
			{
				if(it->isLive() && (*it).isUserAlly() && it->map_id == you.lilly_allys[i].map_id && current_level == you.lilly_allys[i].floor)
				{				
					you.lilly_allys[i].exp += exp;

					while(level_up_value[you.lilly_allys[i].level-1] <= you.lilly_allys[i].exp)
					{
						you.lilly_allys[i].level++;

						while(you.lilly_allys[i].level> it->level)
						{
							it->LevelUpdown(1,6.0f,1.0f);
							if(it->isYourShight())
							{
								LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_LILLY_LEVEL_UP,false,false,false,CL_normal,
									 PlaceHolderHelper(it->name.getName()));
								enter_++;
								if(enter_>=4)
									enterlog();
							}
						}

						int prev_id = it->id;
						switch(it->id)
						{
						case MON_FAIRY_GREEN:
							if(it->level >= 5)
							{
								it->ChangeMonster(MON_FAIRY_GREEN_WARRIOR,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_BLUE:
							if(it->level >= 7)
							{
								it->ChangeMonster(MON_FAIRY_BLUE_MAGICIAN,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_RED:
							if(it->level >= 8)
							{
								it->ChangeMonster(MON_FAIRY_RED_COMMANDER,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_GREEN_WARRIOR:
							if(it->level >= 12)
							{
								it->ChangeMonster(MON_FAIRY_HERO,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_BLUE_MAGICIAN:
							if(it->level >= 10)
							{
								it->ChangeMonster(MON_FAIRY_SOCERER,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_RED_COMMANDER:
							if(it->level >= 13)
							{
								it->ChangeMonster(MON_FAIRY_SUN_FLOWER,M_FLAG_ALLY);
							}
							break;
						case MON_SUNNY:
							if(it->level == 13)
							{
								it->spell_lists.push_back(spell(SPL_LASER,20));
							}
							break;
						case MON_LUNAR:
							if(it->level == 13)
							{
								it->spell_lists.push_back(spell(SPL_SMITE,20));
							}
							break;
						case MON_STAR:
							if(it->level == 13)
							{
								it->spell_lists.push_back(spell(SPL_HASTE_OTHER,20));
							}
							break;
						case MON_DIEFAIRY:
							if(it->level == 13)
							{
								it->spell_lists.push_back(spell(SPL_HEAL_OTHER,20));
							}
							break;
						case MON_LARVA:
							if (it->level == 13)
							{
								it->spell_lists.push_back(spell(SPL_VENOM_BOLT, 20));
							}
							break;
						}
						if(prev_id != it->id)
						{						
							you.lilly_allys[i].id = it->id;
							if(!(it->flag & M_FLAG_UNIQUE))
							{
								it->name = fairy_name[you.lilly_allys[i].name];
							}
							if(it->isYourShight())
							{
								if(enter_>0)
								{
									enterlog();
									enter_ = 0;
								}
								LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_LILLY_CLASS_CHANGE,true,false,false,CL_normal,
									 PlaceHolderHelper(mondata[prev_id].name.getName()), PlaceHolderHelper(mondata[it->id].name.getName()));
							}
						}
					}
				}
			}
		}
	}
	enterlog();
}






