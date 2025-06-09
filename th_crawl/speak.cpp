//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: speak.cpp
//
// 내용: 몬스터의 대사
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "speak.h"
#include "player.h"
#include "monster.h"


string Get_Speak(int mon_id, monster* monster_info, monster_speak_type type)
{ //투명일때?
	if(type == MST_FOUND)
	{
		return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FOUND), PlaceHolderHelper(monster_info->GetName()->getName()));
	}
	switch(mon_id)
	{
	case MON_REIMUYUKKURI:
	case MON_MARISAYUKKURI:
		if(type == MST_NORMAL)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUKKURI_NORMAL), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;	
	case MON_RUMIA:
		if(type == MST_NORMAL)
		{
			switch(randA(9))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()),PlaceHolderHelper(job_type_string[you.job]),PlaceHolderHelper(tribe_type_string[you.tribe]));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()),PlaceHolderHelper(tribe_type_string[randA(TRI_MAX-1)]));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RUMIA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_MISTIA:
		if(type == MST_NORMAL)
		{
			switch(randA(15))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_MAGIC3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}

		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MISTIA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
	case MON_WRIGGLE:
		if(type == MST_NORMAL)
		{
			switch(randA(10))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 10:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_MAGIC3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_MAGIC4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WRIGGLE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
	case MON_CIRNO:
		if(type == MST_NORMAL)
		{
			switch(randA(9))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_MAGIC3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_MAGIC4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_MAGIC5), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CIRNO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_MEDICINE:
		if(type == MST_NORMAL)
		{
			switch(randA(11))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				if(you.poison_resist>0)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 2:
				if(you.s_poison)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(tribe_type_string[you.tribe]));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL12), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 10:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL13), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 11:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_NORMAL14), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_MAGIC3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEDICINE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_DIEFAIRY:
		if(type == MST_NORMAL)
		{
			switch(randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DIEFAIRY_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KISUME:
		if(type == MST_NORMAL)
		{	
			switch(randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KISUME_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KISUME_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KISUME_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KISUME_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KISUME_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KISUME_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KISUME_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KISUME_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_CHEN:
		if(type == MST_NORMAL)
		{	
			switch(randA(12))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 10:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 11:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL12), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 12:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_NORMAL13), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHEN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KOGASA:
		if(type == MST_NORMAL)
		{	
			switch(randA(12))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 10:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 11:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL12), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 12:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_NORMAL13), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOGASA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_SUNNY:
		if(type == MST_NORMAL)
		{	
			switch(randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				if (monster_info->GetInvisible() && !you.invisible_view)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				if(monster_info->GetInvisible() && !you.invisible_view)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				else if (monster_info->GetInvisible() && you.invisible_view)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_MAGIC3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_LUNAR:
		if(type == MST_NORMAL)
		{	
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_STAR:
		if(type == MST_NORMAL)
		{	
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				if(you.s_invisible || you.togle_invisible)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 4:
				if(you.s_invisible || you.togle_invisible)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 5:
				if(you.s_invisible || you.togle_invisible)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;		
	case MON_YAMABIKO:
		if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMABIKO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		break;
	case MON_KYOUKO:
		if(type == MST_NORMAL)
		{	
			switch(randA(11))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(tribe_type_string[you.tribe]));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 10:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 11:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_NORMAL12), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_MAGIC3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KYOUKO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_FORTUNE_TELLER:
		if(type == MST_NORMAL)
		{	
			switch(randA(9))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FORTUNE_TELLER_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		break;
	case MON_MOMIZI:
		if(type == MST_NORMAL)
		{	
			switch(randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MOMIZI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_AYA:
		if(type == MST_NORMAL)
		{
			{
				switch (you.tribe)
				{
				case TRI_HUMAN:
					switch (randA(8))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL1_H), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL2_H), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL3_H), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL4_H), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL5_H), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL6_H), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL7_H), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 7:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL8_H), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 8:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL9_H), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					break;
				case TRI_CROWTENGU:
					switch (randA(9))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL1_T), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(you.user_name));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL2_T), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL3_T), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL4_T), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL5_T), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL6_T), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL7_T), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 7:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL8_T), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 8:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL9_T), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 9:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL10_T), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					break;
				case TRI_WOLFTENGU:
					switch (randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL1_W), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL2_W), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL3_W), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL4_W), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL5_W), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL6_W), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					break;
				case TRI_KAPPA:
					switch (randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL1_K), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL2_K), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL3_K), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL4_K), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL5_K), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL6_K), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					break;
				case TRI_ONI:
					switch (randA(7))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL1_O), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL2_O), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL3_O), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL4_O), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL5_O), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL6_O), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL7_O), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 7:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL8_O), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					break;
				default://기본대화
					switch (randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					break;
				}
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_CONFUSE5), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AYA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_WAKASAGI:
		if(type == MST_NORMAL)
		{
			switch(randA(7))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_WAKASAGI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_YAMAME:
		if(type == MST_NORMAL)
		{
			switch(randA(8))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				if(you.s_sick)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:				
				if(you.s_sick)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 4:
				if(you.s_sick)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 5:
				if(you.tribe == TRI_KAPPA)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 6:
				if(you.s_sick && you.s_poison)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL12), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL13), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_NORMAL14), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YAMAME_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_NAZRIN:
		if(type == MST_NORMAL)
		{
			switch(randA(9))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				if(you.haveGoal()) //플레이어가 (룬)을 1개이상 들고 있을때
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(tribe_type_string[you.tribe]));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NAZRIN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_YOSIKA:
		if(type == MST_NORMAL)
		{
			switch(randA(7))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOSIKA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_SEKIBANKI:
	case MON_SEKIBANKI_HEAD:
		if(type == MST_NORMAL)
		{
			switch(randA(9))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				if (mon_id == MON_SEKIBANKI_HEAD)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				if (mon_id == MON_SEKIBANKI_HEAD)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(tribe_type_string[randA(TRI_MAX - 1)]));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_NORMAL12), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				if (mon_id == MON_SEKIBANKI_HEAD)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_CONFUSE5), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			if(mon_id == MON_SEKIBANKI_HEAD)
				return "";
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEKIBANKI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_NITORI:		
		if(type == MST_NORMAL)
		{	
			switch(you.tribe)
			{
			case TRI_HUMAN:
				switch(randA(5))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL1_H), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL2_H), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL3_H), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL4_H), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL5_H), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL6_H), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				break;
			case TRI_CROWTENGU:
				switch(randA(6))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL1_T), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL2_T), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL3_T), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL4_T), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL5_T), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL6_T), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL7_T), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				break;
			case TRI_KAPPA:
				switch(randA(6))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL1_K), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL2_K), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL3_K), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL4_K), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL5_K), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL6_K), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL7_K), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				break;
			case TRI_ONI:
				switch(randA(7))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL1_O), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL2_O), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL3_O), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL4_O), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL5_O), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL6_O), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL7_O), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 7:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL8_O), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				break;
			default://기본대화
				switch(randA(7))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					if(you.invisible_view)
					{
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					else
					{
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					if (you.god != GT_NONE)
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
					else
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 7:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				break;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NITORI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KEGERO:
		if(type == MST_NORMAL)
		{
			switch(randA(7))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEGERO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_PARSI:
		//파르시는 크롤의 도날드 포지션. 다양한 던전, 신에 대한 대응 반응.
		if(type == MST_NORMAL)
		{	
			switch(randA(2)) //0은 노말, 1은 신, 2는 던전에 대한 질투
			{
			case 0:
				switch(randA(8))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 7:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 8:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
				}				
				break;
			case 1:
				switch(you.god)
				{
				default:
					switch(randA(0))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_BUG), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_NONE:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_NONE1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_NONE2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_NONE3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_NONE4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_NONE5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_NONE6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_NONE7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_JOON_AND_SION:
					switch(randA(4))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						if (you.god_value[GT_JOON_AND_SION][0] == 1)
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION2), PlaceHolderHelper(monster_info->GetName()->getName()));
						else if (you.god_value[GT_JOON_AND_SION][0] == 2)
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION3), PlaceHolderHelper(monster_info->GetName()->getName()));
						else
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						if (you.god_value[GT_JOON_AND_SION][0] == 1)
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION5), PlaceHolderHelper(monster_info->GetName()->getName()));
						else if (you.god_value[GT_JOON_AND_SION][0] == 2)
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION6), PlaceHolderHelper(monster_info->GetName()->getName()));
						else
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION7), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						if (you.god_value[GT_JOON_AND_SION][0] == 1)
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION8), PlaceHolderHelper(monster_info->GetName()->getName()));
						else if (you.god_value[GT_JOON_AND_SION][0] == 2)
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION9), PlaceHolderHelper(monster_info->GetName()->getName()));
						else
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION10), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						if (you.god_value[GT_JOON_AND_SION][0] == 1)
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION11), PlaceHolderHelper(monster_info->GetName()->getName()));
						else if (you.god_value[GT_JOON_AND_SION][0] == 2)
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION12), PlaceHolderHelper(monster_info->GetName()->getName()));
						else
							return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JOON_AND_SION13), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_BYAKUREN:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_BYAKUREN1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_BYAKUREN2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_BYAKUREN3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_BYAKUREN4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_BYAKUREN5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_BYAKUREN6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_BYAKUREN7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_KANAKO:
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KANAKO1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KANAKO2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KANAKO3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KANAKO4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KANAKO5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KANAKO6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_SUWAKO:
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SUWAKO1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SUWAKO2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SUWAKO3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SUWAKO4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SUWAKO5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SUWAKO6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_MINORIKO:
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MINORIKO1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MINORIKO2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MINORIKO3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MINORIKO4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MINORIKO5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MINORIKO6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_MIMA:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIMA1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIMA2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIMA3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIMA4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIMA5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIMA6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIMA7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_SHINKI:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHINKI1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHINKI2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHINKI3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHINKI4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHINKI5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHINKI6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHINKI7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_YUUGI:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUUGI1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUUGI2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUUGI3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUUGI4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUUGI5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUUGI6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUUGI7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_SHIZUHA:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHIZUHA1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHIZUHA2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHIZUHA3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHIZUHA4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHIZUHA5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHIZUHA6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SHIZUHA7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_HINA:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_HINA1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_HINA2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_HINA3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_HINA4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_HINA5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_HINA6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_HINA7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_YUKARI:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUKARI1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUKARI2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUKARI3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUKARI4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUKARI5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUKARI6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUKARI7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_EIRIN:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_EIRIN1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_EIRIN2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_EIRIN3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_EIRIN4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_EIRIN5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_EIRIN6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_EIRIN7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_YUYUKO:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUYUKO1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUYUKO2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUYUKO3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUYUKO4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUYUKO5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUYUKO6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_YUYUKO7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_SATORI:
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SATORI1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SATORI2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SATORI3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SATORI4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SATORI5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SATORI6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				case GT_TENSI:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_TENSI1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_TENSI2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_TENSI3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_TENSI4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_TENSI5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_TENSI6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_TENSI7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
			case GT_SEIJA:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SEIJA1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SEIJA2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SEIJA3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SEIJA4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SEIJA5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SEIJA6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_SEIJA7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
			case GT_LILLY:
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_LILLY1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_LILLY2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_LILLY3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_LILLY4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_LILLY5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_LILLY6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_LILLY7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
			case GT_MIKO:
				switch (randA(6))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIKO1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIKO2), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIKO3), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIKO4), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIKO5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIKO6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_MIKO7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				break;
			case GT_OKINA:
				switch (randA(6))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_OKINA1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_OKINA2), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_OKINA3), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_OKINA4), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_OKINA5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_OKINA6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_OKINA7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				break;
			case GT_JUNKO:
				switch (randA(7))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO2), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO3), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO4), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO7), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 7:
					switch (you.god_value[GT_JUNKO][3])
					{
					default:
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO8), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO9), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO10), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO11), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO12), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO13), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO14), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 7:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_JUNKO15), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
				}
				break;
				case GT_SHIKIEIKI:
					//TODO) 신구현
					break;
				case GT_KEIKI:
				switch (randA(6))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KEIKI1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KEIKI2), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KEIKI3), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KEIKI4), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KEIKI5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KEIKI6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_GOD_KEIKI7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				break;
				case GT_TENKYUU:
					//TODO) 신구현
					break;
				}
				break;				
			case 2:
				if(current_level<MAX_DUNGEUN_LEVEL){
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}				
				else if(current_level == TEMPLE_LEVEL){
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_TEMPLE1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_TEMPLE2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_TEMPLE3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_TEMPLE4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_TEMPLE5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_TEMPLE6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_TEMPLE7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=MISTY_LAKE_LEVEL && current_level<=MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL) {					
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MISTY_LAKE1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MISTY_LAKE2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MISTY_LAKE3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MISTY_LAKE4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MISTY_LAKE5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MISTY_LAKE6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MISTY_LAKE7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=YOUKAI_MOUNTAIN_LEVEL && current_level<=YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL) {					
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YOUKAI_MOUNTAIN1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YOUKAI_MOUNTAIN2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YOUKAI_MOUNTAIN3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YOUKAI_MOUNTAIN4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YOUKAI_MOUNTAIN5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YOUKAI_MOUNTAIN6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YOUKAI_MOUNTAIN7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=SCARLET_LEVEL && current_level<=SCARLET_LEVEL+MAX_SCARLET_LEVEL) {					
					switch(randA(6))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET7), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=SCARLET_LIBRARY_LEVEL && current_level<=SCARLET_LIBRARY_LEVEL+MAX_SCARLET_LIBRARY_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_LIBRARY1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_LIBRARY2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_LIBRARY3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_LIBRARY4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_LIBRARY5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_LIBRARY6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=SCARLET_UNDER_LEVEL && current_level<=SCARLET_UNDER_LEVEL+MAX_SCARLET_UNDER_LEVEL) {					
					switch(randA(3))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET_UNDER1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET_UNDER2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET_UNDER3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SCARLET_UNDER4), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=BAMBOO_LEVEL && current_level<=BAMBOO_LEVEL+MAX_BAMBOO_LEVEL) {					
					switch(randA(7))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_BAMBOO1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_BAMBOO2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_BAMBOO3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_BAMBOO4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_BAMBOO5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_BAMBOO6), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 6:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_BAMBOO7), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 7:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_BAMBOO8), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=EIENTEI_LEVEL && current_level<=EIENTEI_LEVEL+MAX_EIENTEI_LEVEL) {					
					switch(randA(3))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_EIENTEI1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_EIENTEI2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_EIENTEI3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_EIENTEI4), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=SUBTERRANEAN_LEVEL && current_level<=SUBTERRANEAN_LEVEL+MAX_SUBTERRANEAN_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SUBTERRANEAN1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SUBTERRANEAN2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SUBTERRANEAN3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SUBTERRANEAN4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SUBTERRANEAN5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_SUBTERRANEAN6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=YUKKURI_LEVEL && current_level<=YUKKURI_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YUKKURI1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YUKKURI2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YUKKURI3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YUKKURI4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YUKKURI5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_YUKKURI6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=DEPTH_LEVEL && current_level<=DEPTH_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DEPTH1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DEPTH2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DEPTH3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DEPTH4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DEPTH5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DEPTH6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=DREAM_LEVEL && current_level<=DREAM_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DREAM1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DREAM2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DREAM3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DREAM4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DREAM5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_DREAM6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=MOON_LEVEL && current_level<=MOON_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MOON1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MOON2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MOON3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MOON4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MOON5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_MOON6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=PANDEMONIUM_LEVEL && current_level<=PANDEMONIUM_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_PANDEMONIUM1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_PANDEMONIUM2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_PANDEMONIUM3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_PANDEMONIUM4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_PANDEMONIUM5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_PANDEMONIUM6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if(current_level>=HAKUREI_LEVEL && current_level<=HAKUREI_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_HAKUREI1), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 1:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_HAKUREI2), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 2:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_HAKUREI3), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 3:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_HAKUREI4), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 4:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_HAKUREI5), PlaceHolderHelper(monster_info->GetName()->getName()));
					case 5:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_HAKUREI6), PlaceHolderHelper(monster_info->GetName()->getName()));
					}				
					break;
				}
				else if (current_level == OKINA_LEVEL) {
					switch (randA(0))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_OKINA), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					break;
				}
				else if (current_level == ZIGURRAT_LEVEL) {
					switch (randA(0))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_ZIGURRAT), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					break;
				}
				else {
					switch(randA(0))
					{
					case 0:
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_DUNGEON_BUG), PlaceHolderHelper(monster_info->GetName()->getName()));
					}
					break;
				}				
				break;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PARSI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_BENBEN:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_BENBEN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_YATHASI:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YATHASI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;		
	case MON_ORIN:
		if(type == MST_NORMAL)
		{
			if(you.god == GT_SATORI)
			{
				switch(randA(7))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL1_SATORI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL2_SATORI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL3_SATORI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL4_SATORI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL5_SATORI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL6_SATORI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL7_SATORI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 7:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL8_SATORI), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
			else
			{
				switch(randA(7))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					if (you.tribe != TRI_WRAITH)
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
					else
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					if (you.tribe != TRI_WRAITH)
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
					else
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					if (you.tribe != TRI_WRAITH)
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
					else
						return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 7:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ORIN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_ICHIRIN:
		if(type == MST_NORMAL)
		{
			if(you.god == GT_BYAKUREN)
			{
				switch(randA(4))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL1_BYAKUREN), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL2_BYAKUREN), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL3_BYAKUREN), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL4_BYAKUREN), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL5_BYAKUREN), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
			else
			{
				switch(randA(6))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ICHIRIN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_PACHU:
		if(type == MST_NORMAL)
		{
			switch(randA(10))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(tribe_type_string[you.tribe]));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(tribe_type_string[you.tribe]));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 10:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_MAGIC3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_MAGIC4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_MAGIC5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_MAGIC6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PACHU_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;		
	case MON_KOAKUMA:
		if(type == MST_NORMAL)
		{
			switch(randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOAKUMA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_MEIRIN:
		if(type == MST_NORMAL)
		{
			switch(randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MEIRIN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;	
	case MON_SAKUYA:
		if(type == MST_NORMAL)
		{
			switch(randA(8))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKUYA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;	
	case MON_REMILIA:
		if(type == MST_NORMAL)
		{
			switch(randA(8))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REMILIA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;	
	case MON_KASEN:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				if(you.tribe != TRI_ONI)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				if(you.god != GT_YUUGI)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KASEN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_YUMEKO:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				if (you.god != GT_SHINKI)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				if (you.god != GT_SHINKI)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				if (you.god != GT_SHINKI)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMEKO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_FLAN:
		if(type == MST_NORMAL)
		{
			switch(randA(10)) 
			{
			case 0:
				if (you.tribe == TRI_HUMAN)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				if(you.tribe == TRI_HUMAN)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL12), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 10:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_NORMAL13), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FLAN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_RABIT_SUPPORT:
		if(type == MST_MAGIC)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RABIT_SUPPORT), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_TEWI:
		if(type == MST_NORMAL)
		{
			switch(randA(7))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_CONFUSE4), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TEWI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_CLOWNPIECE:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:		
				if(you.s_lunatic)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:		
				if(you.s_lunatic)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:		
				if(you.s_lunatic)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CLOWNPIECE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_DOREMI:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_DOREMI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_HELL_HOUND:
		if(type == MST_NORMAL)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HELL_HOUND_NORMAL), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HELL_HOUND_MAGIC), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}		
		break;
	case MON_LETTY:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				if (you.god == GT_SHIZUHA || you.god == GT_MINORIKO)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:		
				if(you.god == GT_SHIZUHA || you.god == GT_MINORIKO)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LETTY_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_YORIHIME:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YORIHIME_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_TOYOHIME:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOYOHIME_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_UTSUHO:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				if (you.god != GT_SATORI)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				if (you.god != GT_SATORI)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				if (you.god != GT_SATORI)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UTSUHO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_SUIKA:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:		
				if(you.tribe == TRI_ONI)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 4:						
				if(you.god == GT_YUUGI)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUIKA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_REIMU:
		if (type == MST_NORMAL)
		{
			if (you.char_type == UNIQ_START_REIMU)
			{
				switch (randA(4))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL1_REIMU), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL2_REIMU), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL3_REIMU), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL4_REIMU), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL5_REIMU), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
			else if (you.char_type == UNIQ_START_MARISA)
			{

				switch (randA(5))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL1_MARISA), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL2_MARISA), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL3_MARISA), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL4_MARISA), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL5_MARISA), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL6_MARISA), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
			else if (you.char_type == UNIQ_START_SANAE)
			{

				switch (randA(4))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL1_SANAE), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL2_SANAE), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL3_SANAE), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL4_SANAE), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL5_SANAE), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
			else {
				switch (randA(9))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 7:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 8:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 9:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		else if (type == MST_DEAD)
		{
			switch (randA(11))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD9), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 9:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 10:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD11), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 11:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_REIMU_DEAD12), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		break;
	case MON_ALICE:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ALICE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_SEIRAN:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIRAN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIRAN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIRAN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIRAN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIRAN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIRAN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIRAN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIRAN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIRAN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_RINGO:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_RINGO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_UDONGE:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_UDONGE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KAGUYA:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KAGUYA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_MOKOU:
		break;		
	case MON_TOKIKO:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOKIKO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_TOZIKO:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				if (you.god == GT_MIKO)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				if (you.god == GT_MIKO)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				if (you.god == GT_MIKO)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TOZIKO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_FUTO:
		if(type == MST_NORMAL)
		{
			switch(randA(8))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:		
				if(!you.s_unluck) //흉 버프가 안걸려있을때
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				else // 흉 버프가 걸려있을때
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				if (!you.s_unluck) // 흉 버프가 안걸려있을때
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				else // 흉 버프가 걸려있을때
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				if (you.god == GT_MIKO)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				if (you.god == GT_MIKO)
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
				else
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL10), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL11), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL12), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:	
				if(!you.s_unluck) //흉 버프가 안걸려있을때
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL13), PlaceHolderHelper(monster_info->GetName()->getName()));
				else //흉 버프가 걸려있을때
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_NORMAL14), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_FUTO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_MAMIZO: //사투리 어떻게 쓰냐
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAMIZO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_SEIGA:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SEIGA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_MURASA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				if (you.s_none_move)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 2:
				if (you.s_none_move)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MURASA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KEINE:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				if (you.char_type == UNIQ_START_MOKOU)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else if (you.tribe == TRI_HUMAN)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KEINE2:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KEINE2_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_YOUMU:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YOUMU_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_LYRICA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LYRICA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_MERLIN:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				if (you.s_confuse)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 2:
				if (you.s_confuse)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MERLIN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_LUNASA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				if (you.s_slow)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 2:
				if (you.s_slow)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNASA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KOMACHI:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOMACHI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_IKU:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				if (you.god == GT_TENSI)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 1:
				if (you.god == GT_TENSI)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 2:
				if (you.god == GT_TENSI)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(1))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_MAGIC2), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_IKU_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_LARVA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LARVA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_NEMUNO:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				if (you.tribe == TRI_CROWTENGU || you.tribe == TRI_WOLFTENGU)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NEMUNO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_AUNN:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_MAGIC), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_AUNN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_NARUMI:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(tribe_type_string[you.tribe]));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NARUMI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_MAI2:
		if (type == MST_NORMAL || type == MST_CONFUSE)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAI2_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAI2_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAI2_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAI2_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAI2_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAI2_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAI2_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAI2_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_SATONO:
		if (type == MST_NORMAL || type == MST_CONFUSE)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SATONO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SATONO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SATONO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SATONO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SATONO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SATONO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SATONO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SATONO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KOKORO:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KOKORO1:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO1_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KOKORO2:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO2_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KOKORO3:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KOKORO3_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_SUMIREKO:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				if (you.tribe == TRI_HUMAN)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(tribe_type_string[you.tribe]));
				}
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUMIREKO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_HATATE:
		if (type == MST_NORMAL)
		{
			if (you.char_type == UNIQ_START_MOMIZI) {

				switch (randA(4))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL1_MOMIZI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL2_MOMIZI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL3_MOMIZI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL4_MOMIZI), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL5_MOMIZI), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
			else {
				switch (randA(6))
				{
				case 0:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 1:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 2:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 3:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(tribe_type_string[you.tribe]));
				case 4:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 5:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				case 6:
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HATATE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_EIKA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				if(monster_info->special_value > 0) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:
				if(monster_info->special_value > 0) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(to_string(monster_info->special_value)));
				}
				else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 4:
				if(monster_info->special_value > 0) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()), PlaceHolderHelper(to_string(monster_info->special_value)));
				}
				else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_EIKA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_URUMI:	
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_URUMI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_KUTAKA:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_KUTAKA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_YACHIE:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YACHIE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_MAYUMI:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				if (you.tribe == TRI_HUMAN)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 4:
				if (you.tribe == TRI_HUMAN)
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
				else
				{
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAYUMI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_SAKI:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SAKI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_YUMA:
		if (type == MST_NORMAL)
		{
			switch (randA(8))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 7:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 8:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_YUMA2:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_YUMA2_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;

	case MON_ENOKO:
		if (type == MST_NORMAL)
		{
			switch (randA(4))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				if(you.char_type == UNIQ_START_MARISA) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
				} else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 2:
				if(false) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				} else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:
				if(false) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				} else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 4:
				if(false) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				} else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_ENOKO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;

	case MON_CHIYARI:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				if(you.tribe == TRI_VAMPIRE) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				} else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CHIYARI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_SONBITEN:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SONBITEN_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_HISAMI:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_HISAMI_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	case MON_TSUKASA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		else if (type == MST_PROPOSAL)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_PROPOSAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_PROPOSAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_PROPOSAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_PROPOSAL_ACCEPT)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_PROPOSAL_ACCEPT1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_PROPOSAL_ACCEPT2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TSUKASA_PROPOSAL_ACCEPT3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		break;
	case MON_MIKE:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		else if (type == MST_PROPOSAL)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_PROPOSAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_PROPOSAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_PROPOSAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_PROPOSAL_ACCEPT)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_PROPOSAL_ACCEPT1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_PROPOSAL_ACCEPT2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MIKE_PROPOSAL_ACCEPT3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		break;
	case MON_TAKANE:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				if(you.char_type == UNIQ_START_MARISA) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
				} else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 3:
				if(you.tribe == TRI_KAPPA) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
				} else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 4:
				if(you.char_type == UNIQ_START_MARISA) {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
				} else {
					return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_NORMAL8), PlaceHolderHelper(monster_info->GetName()->getName()));
				}
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_NORMAL9), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		else if (type == MST_PROPOSAL)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_PROPOSAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_PROPOSAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_PROPOSAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_PROPOSAL_ACCEPT)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_PROPOSAL_ACCEPT1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_PROPOSAL_ACCEPT2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_TAKANE_PROPOSAL_ACCEPT3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		break;
	case MON_SANNYO:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_NORMAL1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_NORMAL2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_NORMAL3), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 3:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_NORMAL4), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 4:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_NORMAL5), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 5:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_NORMAL6), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 6:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_NORMAL7), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_CONFUSE1), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 1:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_CONFUSE2), PlaceHolderHelper(monster_info->GetName()->getName()));
			case 2:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_CONFUSE3), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_MAGIC1), PlaceHolderHelper(monster_info->GetName()->getName()));
			}
		}
		else if (type == MST_CAMERA)
		{
			return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SANNYO_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
		}
		break;
	default:
		break;
	}
	if(type == MST_MAGIC)
	{
		return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAGIC), PlaceHolderHelper(monster_info->GetName()->getName()));
	}
	else if (type == MST_CONFUSE) {
		return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CONFUSE), PlaceHolderHelper(monster_info->GetName()->getName()));
	}
	else if (type == MST_CAMERA)
	{
		return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_CAMERA), PlaceHolderHelper(monster_info->GetName()->getName()));
	}
	else if (type == MST_PROPOSAL)
	{
		return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PROPOSAL), PlaceHolderHelper(monster_info->GetName()->getName()));
	}
	else if (type == MST_PROPOSAL_ACCEPT)
	{
		return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_PROPOSAL_ACCEPT), PlaceHolderHelper(monster_info->GetName()->getName()));
	}
	else if (type == MST_DEAD)
	{
		return LocalzationManager::locString(LOC_EMPTYSTRING);
	}
	return LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_NORMAL), PlaceHolderHelper(monster_info->GetName()->getName()));
}