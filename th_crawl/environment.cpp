//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: environment.cpp
//
// 내용: 맵과 게임데이터
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"
#include "const.h"
#include "save.h"
#include "map.h"
#include "rect.h"
#include "event.h"
#include "mon_infor.h"
#include "key.h"
#include "smoke.h"
#include "floor.h"
#include "note.h"
#include "beam.h"
#include "replay.h"
#include "forbid.h"
#include "soundmanager.h"
#include "option_manager.h"
#include "steam_api.h"
#include <set>



environment env[MAXLEVEL];
int current_level=0;
extern HANDLE mutx;

extern optionManager option_mg;
extern POINT MousePoint;



void stair_info::SaveDatas(FILE *fp)
{
	SaveData<coord_def>(fp, pos);
	SaveData<int>(fp, next_floor);

}
void stair_info::LoadDatas(FILE *fp)
{
	LoadData<coord_def>(fp, pos);
	LoadData<int>(fp, next_floor);

}
environment::environment():floor(0), make(false), all_monster_id(1), popular(1),
base_floor(DG_FLOOR), base_wall(DG_WALL)
{
	mon_vector.reserve(MON_MAX_IN_FLOOR);
}


environment::~environment()
{
}
void environment::init() {
	floor = 0;
	make = false;
	all_monster_id = 1;
	popular = 1;
	base_floor = DG_FLOOR;
	base_wall = DG_WALL;
	for(int i = 0; i < DG_MAX_X; i++) {
		for(int j = 0; j < DG_MAX_Y; j++) {
			dgtile[i][j] = dungeon_tile();
		}
	}
	for(int i = 0; i < 3; i++) {
		stair_up[i] = coord_def(0,0);
 		stair_down[i] = coord_def(0,0);
	}
	stair_vector.clear();
	mon_vector.clear();
	mon_vector.reserve(MON_MAX_IN_FLOOR);
	shadow_list.clear();
	item_list.clear();
	effect_list.clear();
	smoke_list.clear();
	floor_list.clear();
	event_list.clear();
	speciel_map_name.clear();
	forbid_list.clear();

}
void environment::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, floor);
	SaveData<bool>(fp, make);
	SaveData<int>(fp, all_monster_id);
	SaveData<int>(fp, popular);
	SaveData<dungeon_tile_type>(fp, base_floor);
	SaveData<dungeon_tile_type>(fp, base_wall);
	SaveData<dungeon_tile>(fp, **dgtile, DG_MAX_X * DG_MAX_Y);
	SaveData<coord_def>(fp, *stair_up, 3);
	SaveData<coord_def>(fp, *stair_down, 3);
	SaveData<int>(fp, stair_vector.size());
	for(auto it=stair_vector.begin();it!=stair_vector.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, mon_vector.size());
	for(vector<monster>::iterator it=mon_vector.begin();it!=mon_vector.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, shadow_list.size());
	for(list<shadow>::iterator it=shadow_list.begin();it!=shadow_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, item_list.size());
	for(list<item>::iterator it=item_list.begin();it!=item_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, smoke_list.size());
	for(list<smoke>::iterator it=smoke_list.begin();it!=smoke_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, floor_list.size());
	for(auto it=floor_list.begin();it!=floor_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, event_list.size());
	for(list<events>::iterator it=event_list.begin();it!=event_list.end();it++)
	{
		(*it).SaveDatas(fp);
	}
	SaveData<int>(fp, speciel_map_name.size());
	for (list<string>::iterator it = speciel_map_name.begin(); it != speciel_map_name.end(); it++)
	{
		char temp[100];
		sprintf_s(temp,100, "%s", (*it).c_str());
		SaveData<char>(fp, *temp, strlen(temp) + 1);
	}
	SaveData<int>(fp, forbid_list.size());
	for (list<forbid>::iterator it = forbid_list.begin(); it != forbid_list.end(); it++)
	{
		(*it).SaveDatas(fp);
	}
}

void environment::LoadDatas(FILE *fp)
{
	mon_vector.clear();
	shadow_list.clear();
	item_list.clear();
	effect_list.clear();
	LoadData<int>(fp, floor);
	LoadData<bool>(fp, make);
	LoadData<int>(fp, all_monster_id);
	LoadData<int>(fp, popular);
	LoadData<dungeon_tile_type>(fp, base_floor);
	LoadData<dungeon_tile_type>(fp, base_wall);
	LoadData<dungeon_tile>(fp, **dgtile);
	LoadData<coord_def>(fp, *stair_up);
	LoadData<coord_def>(fp, *stair_down);
	int size_;
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		stair_info temp(coord_def(),0);
		temp.LoadDatas(fp);
		stair_vector.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		monster temp;
		temp.LoadDatas(fp);
		mon_vector.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		shadow temp;
		temp.LoadDatas(fp);
		shadow_list.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		item temp;
		temp.LoadDatas(fp);
		item_list.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		smoke temp;
		temp.LoadDatas(fp);
		smoke_list.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		floor_effect temp;
		temp.LoadDatas(fp);
		floor_list.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for(int i=0;i<size_;i++)
	{	
		events temp;
		temp.LoadDatas(fp);
		event_list.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for (int i = 0; i<size_; i++)
	{
		char temp[100];
		LoadData<char>(fp, *temp);
		string name = temp;
		speciel_map_name.push_back(temp);
	}
	LoadData<int>(fp, size_);
	for (int i = 0; i<size_; i++)
	{
		forbid temp;
		temp.LoadDatas(fp);
		forbid_list.push_back(temp);
	}
	//----ENV로딩부분에서 임시 타겟팅을 잡아줘야한다.
	
	for(vector<monster>::iterator it=mon_vector.begin();it!=mon_vector.end();it++)
	{
		if((*it).temp_target_map_id !=  -1) //지정할 대상이 있어
		{
			(*it).target = GetMapIDtoUnit((*it).temp_target_map_id);
		}
	}


}
bool environment::MakeMap(bool return_)
{
	if(!make || ((env[floor].isBamboo() || env[floor].isPandemonium() || floor == DREAM_LEVEL || floor == ZIGURRAT_LEVEL) && !return_))
	{
		map_algorithms(floor);
		allCalculateAutoTile();
		if(isNormalGame())
		{
			create_mon(floor, GetLevelMonsterNum(floor,false));
			create_item(floor,  GetLevelMonsterNum(floor,true));

			if (you.god != GT_MIKO) {
				popular = -1;
			}
		}	

		if(floor>=SUBTERRANEAN_LEVEL && floor <= SUBTERRANEAN_LEVEL_LAST_LEVEL)
		{ //지저에선 모두 깨어있다.
			for(auto it = env[floor].mon_vector.begin();it!= env[floor].mon_vector.end(); it++)
			{
				it->state.SetState(MS_NORMAL);
			}
		}
	}
	if(!make)
	{
		switch(floor)
		{
		case 4:
		case 9:
		case MAX_DUNGEUN_LEVEL:
		case TEMPLE_LEVEL:
		case MISTY_LAKE_LEVEL:
		case MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL:
		case YOUKAI_MOUNTAIN_LEVEL:
		case YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL:
		case SCARLET_LEVEL:
		case SCARLET_LEVEL+MAX_SCARLET_LEVEL:
		case SCARLET_LIBRARY_LEVEL:
		case SCARLET_UNDER_LEVEL:
		case BAMBOO_LEVEL:
		case EIENTEI_LEVEL:
		case SUBTERRANEAN_LEVEL:
		case SUBTERRANEAN_LEVEL+MAX_SUBTERRANEAN_LEVEL:
		case YUKKURI_LEVEL:
		case YUKKURI_LEVEL+MAX_YUKKURI_LEVEL:
		case DEPTH_LEVEL:
		case DREAM_LEVEL:
		case MOON_LEVEL:
		case PANDEMONIUM_LEVEL:
		case PANDEMONIUM_LEVEL+1:
		case PANDEMONIUM_LEVEL+2:
		case PANDEMONIUM_LEVEL+3:
		case HAKUREI_LEVEL:
		case HAKUREI_LEVEL+MAX_HAKUREI_LEVEL:
		case ZIGURRAT_LEVEL:
			{
				AddNote(you.turn,CurrentLevelString(floor),LocalzationManager::formatString(LOC_SYSTEM_NOTE_DUNGEON_ENTER, PlaceHolderHelper(CurrentLevelString(floor))), CL_normal);
			}
			break;
		}
		make = true;
		return true;
	}
	else if(floor == ZIGURRAT_LEVEL){
		AddNote(you.turn, CurrentLevelString(floor), LocalzationManager::formatString(LOC_SYSTEM_NOTE_DUNGEON_ENTER, PlaceHolderHelper(CurrentLevelString(floor))), CL_normal);
	}
	return false;
}
void environment::EnterMap(int num_, deque<monster*> &dq, coord_def pos_)
{
	if (floor == current_level) {
	//같은 층끼리 움직이는거라면 몬스터를 끌어오면 안된다.
		dq.clear();
	}
	for(vector<monster>::iterator it =  env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{
		if(it->isLive())
		{
			it->TurnSave();
		}
	}
	for (auto it = env[current_level].item_list.begin(); it != env[current_level].item_list.end(); it++) 
	{
		it->TurnSave();
	}

	int dq_n=0;
	
	bool first_ = MakeMap(false);
	enterBgm(first_);
	WaitForSingleObject(mutx, INFINITE);
	int prev_level = current_level;
	if(you.s_silence)
		env[current_level].MakeSilence(you.position, you.s_silence_range, false);
	env[current_level].popular = -1;
	current_level = floor;

	if(current_level >= PANDEMONIUM_LEVEL && current_level <= PANDEMONIUM_LAST_LEVEL)
	{
		while(1)
		{
			int x_ = randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			if(env[current_level].isMove(x_,y_) && !env[current_level].isMonsterPos(x_,y_))
			{
				you.SetXY(x_,y_);
				break;
			}
		}
	}
	else if(num_>=0 && num_ <3)
		you.SetXY((prev_level>floor && !isLastFloor(floor))?stair_down[num_]:stair_up[num_]);
	else
		you.SetXY(pos_);
	you.prev_position = you.position;
	{
		//미코에 의한 버프 초기화
		you.reSetMikoBuff();
	}
	if(you.s_silence)
		env[current_level].MakeSilence(you.position, you.s_silence_range, true);

	if(monster* temp_unit = (monster*)isMonsterPos(you.position.x,you.position.y,&you))
	{	
		dif_rect_iterator dit(you.position, 3);
		for(;!dit.end();dit++)
		{
			if(env[current_level].isMove(dit->x, dit->y, false) && !env[current_level].isMonsterPos(dit->x,dit->y))
			{
				temp_unit->SetXY(*dit);
				break;
			}
		}
		if(dit.end())
			temp_unit->Teleport();

	}
	
	for(vector<monster>::iterator it =  env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{
		if(it->isLive() && env[current_level].isInSight(it->position))
		{
			it->atkmove(true,true);
			it->atkmove(true,true);
		}
	}


	if(!dq.empty() && !env[floor].isPandemonium())
	{
		dif_rect_iterator dit(you.position, 3);
		for(;!dit.end();dit++)
		{
			if(movingfloor((*dit), prev_level, dq[dq_n]))
			{
					dq_n++;
			}
			if(dq.size() == dq_n)
				break;
		}
	}
	ReleaseMutex(mutx);
	for(vector<monster>::iterator it =  env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{
		if(it->isLive())
		{
			it->TurnLoad();
		}
	}
	for (auto it = env[current_level].item_list.begin(); it != env[current_level].item_list.end(); it++)
	{
		it->TurnLoad();
	}
	if(floor && isNormalGame())
		SaveFile();
	steam_mg.setCurrentInfo();
	you.resetLOS(false);

	if(first_ && current_level > PANDEMONIUM_LEVEL && current_level <= PANDEMONIUM_LAST_LEVEL)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_STAIR_SUBDUNGEON_PANDEMONIUM_RUNE),true,false,false,CL_danger);
		MoreWait();
	}
	
}

bool environment::magicmapping(int x_, int y_)
{
	if(x_<0 || x_>=DG_MAX_X || y_<0 || y_>=DG_MAX_Y)
		return false;
	if(isBamboo())
		return false;

	env[current_level].CheckForbid(coord_def(x_,y_));
		
	switch(dgtile[x_][y_].tile)
	{								
	case DG_TEMPLE_STAIR:									
		map_list.dungeon_enter[TEMPLE].detected = true;
		break;
	case DG_MISTY_LAKE_STAIR:									
		map_list.dungeon_enter[MISTY_LAKE].detected = true;
		break;
	case DG_YOUKAI_MOUNTAIN_STAIR:	
		map_list.dungeon_enter[YOUKAI_MOUNTAIN].detected = true;
		break;
	case DG_SCARLET_STAIR:	
		map_list.dungeon_enter[SCARLET_M].detected = true;		
		break;				
	case DG_SCARLET_L_STAIR:
		map_list.dungeon_enter[SCARLET_L].detected = true;		
		break;				
	case DG_SCARLET_U_STAIR:
		map_list.dungeon_enter[SCARLET_U].detected = true;		
		break;				
	case DG_BAMBOO_STAIR:
		map_list.dungeon_enter[BAMBOO].detected = true;		
		break;				
	case DG_EIENTEI_STAIR:	
		break;				
	case DG_SUBTERRANEAN_STAIR:
		map_list.dungeon_enter[SUBTERRANEAN].detected = true;		
		break;
	case DG_YUKKURI_STAIR:
		map_list.dungeon_enter[YUKKURI_D].detected = true;		
		break;
	case DG_DEPTH_STAIR:
		map_list.dungeon_enter[DEPTH].detected = true;		
		break;
	case DG_DREAM_STAIR:
		map_list.dungeon_enter[DREAM_D].detected = true;		
		break;
	case DG_MOON_STAIR:				
		break;
	case DG_PANDEMONIUM_STAIR:
		map_list.dungeon_enter[PANDEMONIUM].detected = true;		
		break;
	case DG_HAKUREI_STAIR:
		map_list.dungeon_enter[HAKUREI_D].detected = true;		
		break;
	case DG_ZIGURRAT_STAIR:
		map_list.dungeon_enter[ZIGURRAT].detected = true;
		break;
	default:
		break;
	}

	dgtile[x_][y_].flag = dgtile[x_][y_].flag | FLAG_MAPPING;
	return true;
}

int environment::isStair(int x_, int y_)
{
	if(!dgtile[x_][y_].isStair())
		return 0;

	for(int i=0;i<3;i++)
	{
		if(stair_down[i].x == x_ && stair_down[i].y == y_)
			return (i+1);
		if(stair_up[i].x == x_ && stair_up[i].y == y_)
			return -(i+1);
	}
	for(vector<stair_info>::iterator it = stair_vector.begin(); it != stair_vector.end(); it++)
	{
		if(x_ == it->pos.x && y_ == it->pos.y )
			return 5; //임시
	}
	return 0;
}
stair_kind environment::getStairKind(int x_, int y_)
{
	switch (dungeon_tile_type type = dgtile[x_][y_].tile)
	{
	case DG_DOWN_STAIR:
		return STAIR_KIND_DOWN_BASE;
	case DG_TEMPLE_STAIR:
	case DG_MISTY_LAKE_STAIR:
	case DG_YOUKAI_MOUNTAIN_STAIR:
	case DG_SCARLET_STAIR:
	case DG_SCARLET_L_STAIR:
	case DG_SCARLET_U_STAIR:
	case DG_BAMBOO_STAIR:
	case DG_EIENTEI_STAIR:
	case DG_SUBTERRANEAN_STAIR:
	case DG_YUKKURI_STAIR:
	case DG_DEPTH_STAIR:
	case DG_DREAM_STAIR:
	case DG_MOON_STAIR:
	case DG_PANDEMONIUM_STAIR:
	case DG_HAKUREI_STAIR:
	case DG_ZIGURRAT_STAIR:
		return STAIR_KIND_DOWN_SPECIAL;
	case DG_UP_STAIR:
		return STAIR_KIND_UP_BASE;
	case DG_RETURN_STAIR:
		return STAIR_KIND_UP_SPECIAL;
	default:
		return STAIR_KIND_NOT_STAIR;
	}
}
char environment::getAsciiDot(int x_, int y_)
{
	switch (dungeon_tile_type type = dgtile[x_][y_].tile)
	{
	case DG_NONE:
		return ' ';
	case DG_FLOOR:
	case DG_FLOOR2:
	case DG_GRASS:
	case DG_DREAM_FLOOR:
	case DG_PANDE_FLOOR1:
	case DG_PANDE_FLOOR2:
	case DG_PANDE_FLOOR3:
	case DG_PANDE_FLOOR4:
	case DG_PANDE_FLOOR5:
	case DG_PANDE_FLOOR6:
	case DG_PANDE_FLOOR7:
	case DG_DREAM_FLOOR2:
	case DG_HELL_FLOOR:
		return '.';
	case DG_OPEN_DOOR:
		return '/';
	case DG_DOWN_STAIR:
		return '>';
	case DG_UP_STAIR:
		return '<';
	case DG_MISTY_LAKE_STAIR:
	case DG_YOUKAI_MOUNTAIN_STAIR:
	case DG_SCARLET_STAIR:
	case DG_SCARLET_L_STAIR:
	case DG_SCARLET_U_STAIR:
	case DG_BAMBOO_STAIR:
	case DG_EIENTEI_STAIR:
	case DG_SUBTERRANEAN_STAIR:
	case DG_YUKKURI_STAIR:
	case DG_DEPTH_STAIR:
	case DG_DREAM_STAIR:
	case DG_MOON_STAIR:
	case DG_PANDEMONIUM_STAIR:
	case DG_HAKUREI_STAIR:
		return '>';
	case DG_ZIGURRAT_STAIR:
		return '>';
	case DG_RETURN_STAIR:
		return '<';
	case DG_TEMPLE_JOON_AND_SION:
	case DG_TEMPLE_BYAKUREN:
	case DG_TEMPLE_KANAKO:
	case DG_TEMPLE_SUWAKO:
	case DG_TEMPLE_MINORIKO:
	case DG_TEMPLE_MIMA:
	case DG_TEMPLE_SHINKI:
	case DG_TEMPLE_YUUGI:
	case DG_TEMPLE_SHIZUHA:
	case DG_TEMPLE_HINA:
	case DG_TEMPLE_YUKARI:
	case DG_TEMPLE_EIRIN:
	case DG_TEMPLE_YUYUKO:
	case DG_TEMPLE_SATORI:
	case DG_TEMPLE_TENSI:
	case DG_TEMPLE_SEIJA:
	case DG_TEMPLE_LILLY:
	case DG_TEMPLE_MIKO:
	case DG_TEMPLE_OKINA:
	case DG_TEMPLE_JUNKO:
		return '_';
	case DG_WALL:
	case DG_STONE_WALL:
	case DG_RED_WALL:
	case DG_BOOK_WALL:
	case DG_BAMBOO_WALL:
	case DG_PANDE_WALL1:
	case DG_PANDE_WALL2:
	case DG_PANDE_WALL3:
	case DG_PANDE_WALL4:
	case DG_PANDE_WALL5:
	case DG_PANDE_WALL6:
	case DG_PANDE_WALL7:
	case DG_HELL_WALL:
		return '#';
	case DG_TREE:
	case DG_SUN_FLOWER:
		return 'T';
	case DG_METAL_WALL:
		return '#';
	case DG_WALL2:
	case DG_WALL3:
		return '#';
	case DG_CLOSE_DOOR:
		return '+';
	case DG_GLASS:
		return '=';
	case DG_STATUE:
	case DG_STATUE2:
		return '&';
	case DG_SEA:
	case DG_LAVA:
		return '~';
	case DG_OIL:
		return ';';
	case DG_SNOW:
		return '^';
	default:
		return ' ';
	}
}
string environment::getTileHelp(int x_, int y_)
{
	switch(dgtile[x_][y_].tile)
	{
	case DG_DOWN_STAIR:
	case DG_TEMPLE_STAIR:
	case DG_MISTY_LAKE_STAIR:
	case DG_YOUKAI_MOUNTAIN_STAIR:
	case DG_SCARLET_STAIR:
	case DG_SCARLET_L_STAIR:
	case DG_SCARLET_U_STAIR:
	case DG_BAMBOO_STAIR:
	case DG_EIENTEI_STAIR:
	case DG_SUBTERRANEAN_STAIR:
	case DG_YUKKURI_STAIR:
	case DG_DEPTH_STAIR:
	case DG_DREAM_STAIR:
	case DG_MOON_STAIR:
	case DG_PANDEMONIUM_STAIR:
	case DG_HAKUREI_STAIR:
	case DG_ZIGURRAT_STAIR:
		return LocalzationManager::locString(LOC_SYSTEM_TILE_HELP_DOWN);
	case DG_UP_STAIR:
		return floor==0?LocalzationManager::locString(LOC_EMPTYSTRING):LocalzationManager::locString(LOC_SYSTEM_TILE_HELP_UP);
	case DG_RETURN_STAIR:
		return LocalzationManager::locString(LOC_SYSTEM_TILE_HELP_UP);
	case DG_TEMPLE_JOON_AND_SION:
	case DG_TEMPLE_BYAKUREN:
	case DG_TEMPLE_KANAKO:
	case DG_TEMPLE_SUWAKO:
	case DG_TEMPLE_MINORIKO:
	case DG_TEMPLE_MIMA:
	case DG_TEMPLE_SHINKI:
	case DG_TEMPLE_YUUGI:
	case DG_TEMPLE_SHIZUHA:
	case DG_TEMPLE_HINA:
	case DG_TEMPLE_YUKARI:
	case DG_TEMPLE_EIRIN:
	case DG_TEMPLE_YUYUKO:
	case DG_TEMPLE_SATORI:
	case DG_TEMPLE_TENSI:
	case DG_TEMPLE_SEIJA:
	case DG_TEMPLE_LILLY:
	case DG_TEMPLE_MIKO:
	case DG_TEMPLE_OKINA:
	case DG_TEMPLE_JUNKO:
		return LocalzationManager::locString(LOC_SYSTEM_TILE_HELP_PRAY);
	default:
		break;
	}
	return LocalzationManager::locString(LOC_EMPTYSTRING);
}
int environment::getAutoTileNum(unsigned char bit)
{
	switch(bit)
	{
		case 2:
			return 44;
		case 8:
			return 45;
		case 10:
			return 39;
		case 11:
			return 38;
		case 16:
			return 43;
		case 18:
			return 41;
		case 22:
			return 40;
		case 24:
			return 33;
		case 26: 
			return 31;
		case 27:
			return 30;
		case 30:
			return 29;
		case 31:
			return 28;
		case 64: 
			return 42;
		case 66: 
			return 32;
		case 72: 
			return 37;
		case 74: 
			return 27; 
		case 75: 
			return 25;
		case 80:
			return 35;
		case 82: 
			return 19; 
		case 86:
			return 18; 
		case 88: 
			return 23; 
		case 90: 
			return 15; 
		case 91: 
			return 10; 
		case 94: 
			return 13; 
		case 95: 
			return 12; 
		case 104: 
			return 36; 
		case 106: 
			return 26; 
		case 107: 
			return 24; 
		case 120: 
			return 21; 
		case 122: 
			return 5; 
		case 123: 
			return 6; 
		case 126: 
			return 5; 
		case 127: 
			return 4; 
		case 208: 
			return 34; 
		case 210: 
			return 17; 
		case 214: 
			return 16; 
		case 216: 
			return 22; 
		case 218: 
			return 11; 
		case 219: 
			return 10; 
		case 222: 
			return 9; 
		case 223: 
			return 8; 
		case 248: 
			return 20; 
		case 250: 
			return 3; 
		case 251: 
			return 2; 
		case 254: 
			return 1; 
		case 255: 
			return 0;
		case 0: 
			return 46;
	}
	return 0;
}

void environment::calculateAutoTile(coord_def pos, AUTOTILE_KIND kind)
{
	unsigned char autotile_bitmap = 0;
	int i = 0;
	rect_iterator rand(pos, 1, 1);
	while (!rand.end())
	{
		if ((*rand) == pos)
		{
			rand++;
			continue;
		}
		if (((*rand).x < 0 || (*rand).x >= DG_MAX_X || (*rand).y < 0 || (*rand).y >= DG_MAX_Y) ||
			dgtile[(*rand).x][(*rand).y].isAutoTile(kind)
			)
		{
			autotile_bitmap |= 1 << i;
		}
		rand++;
		i++;
	}
	{
		//네 꼭지점은 인접한 타일이 없으면 계산에서 제외해야한다.

		//0 -> 1,3
		//2 -> 1,4
		//5 -> 3,6
		//7 -> 4,6
		if (!(autotile_bitmap & 1 << 1)) {
			autotile_bitmap &= ~(1 << 0);
			autotile_bitmap &= ~(1 << 2);
		}
		if (!(autotile_bitmap & 1 << 3)) {
			autotile_bitmap &= ~(1 << 0);
			autotile_bitmap &= ~(1 << 5);
		}
		if (!(autotile_bitmap & 1 << 4)) {
			autotile_bitmap &= ~(1 << 2);
			autotile_bitmap &= ~(1 << 7);
		}
		if (!(autotile_bitmap & 1 << 6)) {
			autotile_bitmap &= ~(1 << 5);
			autotile_bitmap &= ~(1 << 7);
		}
	}
	dgtile[pos.x][pos.y].autotile_bitmap[kind] = autotile_bitmap;
}


void environment::allCalculateAutoTile()
{
	for (int i = 0; i < AUTOTILE_MAX; i++)
	{
		for (int x = 0; x < DG_MAX_X; x++)
		{
			for (int y = 0; y < DG_MAX_Y; y++)
			{
				calculateAutoTile(coord_def(x, y), (AUTOTILE_KIND)i);
			}
		}
	}
}

void environment::innerDrawTile(shared_ptr<DirectX::SpriteBatch> pSprite, int tile_x, int tile_y, float x, float y, float scale, int count_, D3DCOLOR color_, bool sight)
{
	if (dgtile[tile_x][tile_y].tile == DG_WALL) {
		img_dungeon01[env[current_level].base_floor].draw(pSprite, x, y,0.0f,scale,scale, color_);
		//img_auto_wall[0].draw(pSprite, x, y, color_);
		img_auto_wall[getAutoTileNum(dgtile[tile_x][tile_y].autotile_bitmap[AUTOTILE_WALL])].draw(pSprite, x, y,0.0f,scale,scale, color_);
	}
	else if (dgtile[tile_x][tile_y].tile == DG_METAL_WALL) {
		img_dungeon01[env[current_level].base_floor].draw(pSprite, x, y,0.0f,scale,scale, color_);
		//img_auto_wall[0].draw(pSprite, x, y, color_);
		img_auto_metal_wall[getAutoTileNum(dgtile[tile_x][tile_y].autotile_bitmap[AUTOTILE_WALL])].draw(pSprite, x, y,0.0f,scale,scale, color_);
	}
	else if (dgtile[tile_x][tile_y].tile == DG_STONE_WALL) {
		img_dungeon01[env[current_level].base_floor].draw(pSprite, x, y,0.0f,scale,scale, color_);
		//img_auto_wall[0].draw(pSprite, x, y, color_);
		img_auto_mountain_wall[getAutoTileNum(dgtile[tile_x][tile_y].autotile_bitmap[AUTOTILE_WALL])].draw(pSprite, x, y,0.0f,scale,scale, color_);
	}
	else if (dgtile[tile_x][tile_y].tile == DG_RED_WALL) {
		img_dungeon01[env[current_level].base_floor].draw(pSprite, x, y,0.0f,scale,scale, color_);
		//img_auto_wall[0].draw(pSprite, x, y, color_);
		img_auto_red_wall[getAutoTileNum(dgtile[tile_x][tile_y].autotile_bitmap[AUTOTILE_WALL])].draw(pSprite, x, y,0.0f,scale,scale, color_);
	}
	else if (dgtile[tile_x][tile_y].tile == DG_HELL_WALL) {
		img_dungeon01[env[current_level].base_floor].draw(pSprite, x, y,0.0f,scale,scale, color_);
		//img_auto_wall[0].draw(pSprite, x, y, color_);
		img_auto_hell_wall[getAutoTileNum(dgtile[tile_x][tile_y].autotile_bitmap[AUTOTILE_WALL])].draw(pSprite, x, y,0.0f,scale,scale, color_);
	}
	else if (dgtile[tile_x][tile_y].tile == DG_SEA) {
		img_dungeon01[env[current_level].base_floor].draw(pSprite, x, y,0.0f,scale,scale, color_);
		//img_auto_wall[0].draw(pSprite, x, y, color_);
		img_auto_water[getAutoTileNum(dgtile[tile_x][tile_y].autotile_bitmap[AUTOTILE_WATER])].draw(pSprite, x, y,0.0f,scale,scale, color_);
	}
	else if (dgtile[tile_x][tile_y].tile == DG_LAVA) {
		img_dungeon01[env[current_level].base_floor].draw(pSprite, x, y,0.0f,scale,scale, color_);
		//img_auto_wall[0].draw(pSprite, x, y, color_);
		img_auto_lava[getAutoTileNum(dgtile[tile_x][tile_y].autotile_bitmap[AUTOTILE_WATER])].draw(pSprite, x, y,0.0f,scale,scale, color_);
	}
	else if (dgtile[tile_x][tile_y].tile == DG_OIL) {
		img_dungeon01[env[current_level].base_floor].draw(pSprite, x, y,0.0f,scale,scale, color_);
		//img_auto_wall[0].draw(pSprite, x, y, color_);
		img_auto_oil[getAutoTileNum(dgtile[tile_x][tile_y].autotile_bitmap[AUTOTILE_OIL])].draw(pSprite, x, y,0.0f,scale,scale, color_);
	}
	else if (dgtile[tile_x][tile_y].tile == DG_SNOW) {
		img_dungeon01[env[current_level].base_floor].draw(pSprite, x, y,0.0f,scale,scale, color_);
		//img_auto_wall[0].draw(pSprite, x, y, color_);
		img_auto_snow[getAutoTileNum(dgtile[tile_x][tile_y].autotile_bitmap[AUTOTILE_SNOW])].draw(pSprite, x, y,0.0f,scale,scale, color_);
	}
	else if (!dgtile[tile_x][tile_y].isNormal()) {
		dgtile[tile_x][tile_y].draw(pSprite, x, y, scale, color_, count_);
	}
	else if (dgtile[tile_x][tile_y].tile == DG_SNOWMAN) {
		//특수 예외
		dgtile[tile_x][tile_y].draw(pSprite, DG_SNOWMAN, x, y, scale, color_, count_);
	}
	else {
		dgtile[tile_x][tile_y].draw(pSprite, env[current_level].base_floor, x, y, scale, color_, count_);
	}
}

extern display_manager DisplayManager;
void environment::drawTile(shared_ptr<DirectX::SpriteBatch> pSprite, int tile_x, int tile_y, float x, float y, float scale, int count_, int max_mouseX, bool sight, bool onlyTile, bool draw_mouse)
{
	if (!isExplore(tile_x, tile_y))
	{
		innerDrawTile(pSprite, tile_x, tile_y, x, y, scale, count_, D3DCOLOR_XRGB(160, 160, 255), sight);
	}
	else if (dgtile[tile_x][tile_y].flag & FLAG_LIGHT)
	{
		innerDrawTile(pSprite, tile_x, tile_y, x, y, scale, count_, D3DCOLOR_XRGB(255, 255, 255), sight);
		if(!onlyTile){
			img_effect_gold.draw(pSprite, x, y, 0.0f, scale, scale, 100);
		}
	}
	else if (isInSight(coord_def(tile_x, tile_y)) && sight)
	{
		innerDrawTile(pSprite, tile_x, tile_y, x, y, scale, count_, D3DCOLOR_XRGB(255, 255, 255), sight);
	}
	else
	{
		innerDrawTile(pSprite, tile_x, tile_y, x, y, scale, count_, D3DCOLOR_XRGB(128, 128, 128), sight);
	}

	if (isInSight(coord_def(tile_x, tile_y)) && dgtile[tile_x][tile_y].flag & FLAG_SILENCE)
		img_effect_slience.draw(pSprite, x, y, 0.0f, scale, scale, D3DCOLOR_ARGB(80, 0, 255, 255));
	if (isInSight(coord_def(tile_x, tile_y)) && dgtile[tile_x][tile_y].flag & FLAG_VIOLET)
		img_effect_slience.draw(pSprite, x, y, 0.0f, scale, scale, D3DCOLOR_ARGB(80, 255, 128, 255));
	if (isInSight(coord_def(tile_x, tile_y)) && dgtile[tile_x][tile_y].flag & FLAG_SANCTUARY)
		img_effect_slience.draw(pSprite, x, y, 0.0f, scale, scale, D3DCOLOR_ARGB(80, 255, 255, 0));
	if(!onlyTile && draw_mouse){
		if (MousePoint.x <= max_mouseX &&
			MousePoint.x > x - scale*16 && MousePoint.x <= x + scale*16 &&
		MousePoint.y > y - scale*16 && MousePoint.y <= y+ scale*16
		)
		{
			img_effect_select.draw(pSprite, x, y, 0.0f, scale, scale, D3DCOLOR_ARGB(80, 0, 255, 255));
			if(isClicked(LEFT_CLICK)) {
				g_keyQueue->push(InputedKey(MKIND_MAP,tile_x,tile_y));
			}
			else if(isClicked(RIGHT_CLICK)) {
				g_keyQueue->push(InputedKey(MKIND_MAP_DESCRIPTION,tile_x,tile_y));
			}
			coord_def tile_coorddef(tile_x, tile_y); 

			if(DisplayManager.prev_map_view != tile_coorddef) {
				DisplayManager.prev_map_view = tile_coorddef;
				g_keyQueue->push(InputedKey(MKIND_MAP_CURSOR,tile_x,tile_y));
			}
		}
	}

}
bool environment::changeTile(coord_def c, dungeon_tile_type tile, bool noAutoCacul)
{
	dgtile[c.x][c.y].tile = tile;
	env[current_level].CheckForbid(c);
	if (!noAutoCacul)
	{
		for (int i = 0; i < AUTOTILE_MAX; i++)
		{
			rect_iterator rand(c, 1, 1);
			while (!rand.end())
			{
				if (((*rand).x < 0 || (*rand).x >= DG_MAX_X || (*rand).y < 0 || (*rand).y >= DG_MAX_Y))
				{
					rand++;
					continue;
				}
				calculateAutoTile((*rand), (AUTOTILE_KIND)i);
				rand++;
			}
		}
	}
	return true;
}
int environment::CloseDoor(int x_,int y_)
{
	if(dgtile[x_][y_].isOpenDoor())
	{		
		{
			vector<monster>::iterator it = mon_vector.begin();
			for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
			{
				if((*it).isLive() && (*it).position.x == x_ && (*it).position.y == y_)
				{
					return -1;
				}
			}
		}
		{
			list<item>::iterator it = item_list.begin();
			for(;it != item_list.end() ;it++)
			{
				if((*it).position.x == x_ && (*it).position.y == y_)
				{
					return -1;
				}
			}
		}
		env[current_level].CheckForbid(coord_def(x_, y_));
		dgtile[x_][y_].CloseDoor();
		return 1;
	}
	else
		return 0;
}
monster* environment::AddMonster(int id_, uint64_t flag_, coord_def position_, int time_)
{
	WaitForSingleObject(mutx, INFINITE);
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR;i++,it++)
	{
		if(it == mon_vector.end())
		{
			mon_vector.push_back(monster());
			if(all_monster_id<1)
				all_monster_id = 1;
			ReleaseMutex(mutx);
			mon_vector.back().SetMonster(floor, all_monster_id++, id_, flag_, time_, position_);
			return &(mon_vector.back());
		}
		else if(!(*it).isLive())
		{
			if(all_monster_id<1)
				all_monster_id = 1;
			ReleaseMutex(mutx);
			(*it).SetMonster(floor, all_monster_id++, id_, flag_, time_, position_);
			return &(*it);
		}
	}
	ReleaseMutex(mutx);
	return NULL;
}
monster* environment::AddMonster(monster *mon_, coord_def position_, int time_)
{
	WaitForSingleObject(mutx, INFINITE);
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR;i++,it++)
	{
		if(it == mon_vector.end())
		{
			mon_vector.push_back(*mon_);
			if(all_monster_id<1)
				all_monster_id = 1;
			mon_vector.back().map_id = all_monster_id++;
			mon_vector.back().SetXY(position_);
			mon_vector.back().prev_sight = false;
			ReleaseMutex(mutx);
			return &mon_vector.back();
		}
		else if(!(*it).isLive())
		{
			(*it) = *mon_;
			(*it).map_id = all_monster_id++;
			(*it).SetXY(position_);
			(*it).prev_sight = false;
			ReleaseMutex(mutx);
			return &(*it);
		}
	}
	ReleaseMutex(mutx);
	return nullptr;
}
monster* environment::AddMonster_Summon(int id_, uint64_t flag_, coord_def position_, summon_info &info_, int time_ = 0)
{
	monster* mon_ = AddMonster(id_, flag_, position_, time_);
	if(mon_)
	{
		mon_->sm_info = info_;

		if(mon_->sm_info.summon_id != SKD_OTHER && mon_->sm_info.max_num > 0) //최대 소환수가 정해져있는경우
		{
			vector<monster*> temp_list_;
			for( auto it = mon_vector.begin();it != mon_vector.end();it++)
			{
				if(it->isLive() && it->sm_info.summon_id == mon_->sm_info.summon_id && it->sm_info.parent_map_id == mon_->sm_info.parent_map_id && it->summon_time>0)
				{
					temp_list_.push_back(&(*it));
				}
			}
			if(temp_list_.size() > mon_->sm_info.max_num)
			{
				sort(temp_list_.begin(), temp_list_.end(), 
					[](monster* lt,monster* rt){
					return lt->GetMapId() > rt->GetMapId();
				});
				int remain_ = temp_list_.size() - mon_->sm_info.max_num;
				for(int i = temp_list_.size() - 1; remain_ > 0 ; remain_--)
				{
					temp_list_[i]->summon_time = 0;
				}
			}
		}
	}
	return mon_;
}
void environment::SummonClear(int map_id_)
{
	if(map_id_ >= 0)
	{		
		for( auto it = mon_vector.begin();it != mon_vector.end();it++)
		{
			if(it->isLive() && it->sm_info.parent_map_id == map_id_ && it->summon_time!=0 && IsIndepend_summoner(it->sm_info.summon_id))
			{
				it->summon_time = 0;
			}
		}
	}
}

void environment::MakeShadow(const coord_def &c, textures *t, int original_id_, shadow_type type_, const string &name_)
{
	if(isBamboo())
		return; //죽림에선 만들지 않는다.
	WaitForSingleObject(mutx, INFINITE);
	list<shadow>::iterator it;
	for(it = shadow_list.begin();;it++)
	{
		if(it == shadow_list.end() || (*it).position.y > c.y || ((*it).position.y == c.y && (*it).position.x > c.x) )
		{
			shadow_list.insert(it,shadow(c,t, original_id_,type_,name_));
			ReleaseMutex(mutx);
			return;
		}
		else if((*it).position.y == c.y && (*it).position.x == c.x)
		{
			if((*it).type < type_ )
			{
				shadow_list.insert(it,shadow(c,t, original_id_,type_,name_));
				ReleaseMutex(mutx);
				return;
			}
			else if((*it).type == type_ )
			{
				shadow_list.insert(it,shadow(c,t, original_id_,type_,name_));
				shadow_list.erase(it);
				ReleaseMutex(mutx);
				return;
			}
		}
	}
	ReleaseMutex(mutx);
}


bool environment::MakeSmoke(const coord_def &c, textures *t, smoke_type type_, int time_, int expand_, unit* parent_)
{

	if(!isSmokePos(c.x,c.y) && isMove(c.x,c.y,true))
	{
		parent_type pt_temp = PRT_NEUTRAL;
		if(parent_)
		{
			if(parent_->isplayer())
			{
				pt_temp = PRT_PLAYER;
			}
			else
			{
				pt_temp = PRT_ENEMY;
			}
		}
		WaitForSingleObject(mutx, INFINITE);
		smoke_list.push_back(smoke(c, t, type_, time_, expand_, pt_temp));
		ReleaseMutex(mutx);
		return true;
	}
	return false;
}
bool environment::MakeFloorEffect(const coord_def &c, textures *t, textures *t2, floor_type type_, int time_, unit* parent_)
{
	if(!isMove(c.x,c.y,floor_effect::isFly(type_),floor_effect::isSwim(type_),floor_effect::isNoGround(type_)))
		return false;
	
	parent_type pt_temp = PRT_NEUTRAL;
	if(parent_)
	{
		if(parent_->isplayer())
			pt_temp = PRT_PLAYER;
		else
			pt_temp = PRT_ENEMY;
	}

	if(floor_effect* floor_= isFloorEffectPos(c.x,c.y))
	{
		//그 위치에 이미 floor효과가 있으면 덮어씌운다.
		return floor_->Update(t, t2, type_, time_, pt_temp);
		//상위 이펙트로 덮어씌울수도있어?
	}
	else
	{
		WaitForSingleObject(mutx, INFINITE);
		floor_list.push_back(floor_effect(c, t, t2, type_, time_, pt_temp));
		ReleaseMutex(mutx);
		return true;
	}
	return false;
}


bool environment::MakeEvent(int id_, coord_def position_, event_type type_, int count_, int value)
{
	event_list.push_back(events(id_,position_,type_,count_, value));
	return true;
}

void environment::MakeEffect(const coord_def &c, textures *t, bool over_sight_)
{
	WaitForSingleObject(mutx, INFINITE);
	effect_list.push_back(effect(c,t,over_sight_));
	ReleaseMutex(mutx);
}
void environment::ClearEffect()
{
	WaitForSingleObject(mutx, INFINITE);
	effect_list.clear();
	ReleaseMutex(mutx);
}
void environment::ClearWithoutLaserEffect()
{
	WaitForSingleObject(mutx, INFINITE);
	for(list<effect>::iterator it = effect_list.begin();it !=effect_list.end();) {
		list<effect>::iterator temp = it++;
		if(!(temp->position.x == you.position.x && temp->position.y < you.position.x)) {
			effect_list.erase(temp);
		}
	}
	ReleaseMutex(mutx);
}
void environment::ClearAllShadow()
{
	WaitForSingleObject(mutx, INFINITE);
	shadow_list.clear();
	ReleaseMutex(mutx);
}
void environment::ClearSmoke()
{
	WaitForSingleObject(mutx, INFINITE);
	smoke_list.clear();
	ReleaseMutex(mutx);
}
void environment::ClearForbid()
{
	for (auto it = forbid_list.begin(); it != forbid_list.end(); it++)
		it->removeArea();
	WaitForSingleObject(mutx, INFINITE);
	forbid_list.clear();
	ReleaseMutex(mutx);
}
void environment::ClearEvent()
{
	event_list.clear();
}
void environment::AllySafeClear(int new_floor_, coord_def pos_)
{
	if(new_floor_ == floor)
		return;
	if(you.god == GT_YUYUKO)
	{ //망령이 존재하는가 확인
		for(auto it = mon_vector.begin();it != mon_vector.end();it++)
		{
			if(it->isLive() && (*it).isUserAlly() && it->map_id == you.god_value[GT_YUYUKO][0])
			{//망령이 있으면 new_floor_로 돌려보낸다.
				rand_rect_iterator rect_(pos_,2,2);				
				while(!rect_.end())
				{
					if(env[new_floor_].movingfloor((*rect_), floor, &(*it)))
						break;
					rect_++;
				}
			}
		}
	}
	if(you.god == GT_LILLY)
	{ //요정의 존재 확인
		
		for(int i = 0; i<5;i++)
		{		
			if(you.god_value[GT_LILLY][i] == 1)
			{
				for(auto it = mon_vector.begin();it != mon_vector.end();it++)
				{
					if(it->isLive() && (*it).isUserAlly() && it->map_id == you.lilly_allys[i].map_id && floor == you.lilly_allys[i].floor)
					{
						rand_rect_iterator rect_(pos_,2,2);				
						while(!rect_.end())
						{
							if(env[new_floor_].movingfloor((*rect_), floor, &(*it)))
								break;
							rect_++;
						}
						break;
					}
				}
			}
		}
	}
}
void environment::ClearFloor()
{
	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			dgtile[x][y].tile = DG_FLOOR;
			for (int i = 0; i < AUTOTILE_MAX; i++)
				dgtile[x][y].autotile_bitmap[i] = 0;
			dgtile[x][y].flag = 0;
			dgtile[x][y].silence_count = 0;
			dgtile[x][y].violet_count = 0;
		}
	}
	stair_vector.clear();
	ClearEffect();
	ClearAllShadow();
	ClearEvent();
	ClearSmoke();
	ClearForbid();
	{
		vector<monster>::iterator it;
		it = mon_vector.begin();
		for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
		{
			if((*it).isLive())
			{
				(*it).dead(PRT_NEUTRAL, false, true);
			}
		}
	}
	{
		list<item>::iterator it;
		for(it = item_list.begin();it != item_list.end();)
		{
			list<item>::iterator temp = it++;
			DeleteItem(temp);
		}
	}
	floor_list.clear();
	//make = false;
}
void environment::enterBgm(boolean first_)
{
	if (isShootingSprint()) {
		PlayBGM("stage1");
		return;
	}
	else if (isArena() || isSprint()) {
		PlayBGM("sprint");
		return;
	}
	switch (floor) {
	case 0:
		if (first_) {
			StopCurrentBGM("dungeon");
			PlayBGM("dungeon");
		}
		break;
	case MISTY_LAKE_LEVEL:
		if (first_) {
			StopCurrentBGM("mistlake");
			PlayBGM("mistlake");
		}
		break;
	case YOUKAI_MOUNTAIN_LEVEL:
		StopCurrentBGM("youkaimountain");
		PlayBGM("youkaimountain");
		break;
	case SCARLET_LEVEL:
		StopCurrentBGM("scarlet");
		PlayBGM("scarlet");
		break;
	case BAMBOO_LEVEL:
		StopCurrentBGM("bamboo");
		PlayBGM("bamboo");
		break;
	case DEPTH_LEVEL:
		if (first_) {
			StopCurrentBGM("depth");
			PlayBGM("depth");
		}
		break;
	case DREAM_LEVEL:
		StopCurrentBGM("dream");
		PlayBGM("dream");
		break;
	case PANDEMONIUM_LEVEL:
	case PANDEMONIUM_LEVEL+1:
	case PANDEMONIUM_LEVEL+2:
	case PANDEMONIUM_LEVEL+3:
		StopCurrentBGM("pandemonium");
		PlayBGM("pandemonium");
		break;
	case SUBTERRANEAN_LEVEL:
		StopCurrentBGM("subterranean");
		PlayBGM("subterranean");
		break;
	case HAKUREI_LEVEL:
		StopCurrentBGM("hakurei");
		PlayBGM("hakurei");
		break;
	case ZIGURRAT_LEVEL:
		StopCurrentBGM("ziggurat");
		PlayBGM("ziggurat");
		break;
	}
}
void environment::playBgm() {
	if (isArena())
		PlayBGM("sprint");
	else if (isShootingSprint())
		PlayBGM("stage1");
	else if (isSprint())
		PlayBGM("sprint");
	else if (floor<TEMPLE_LEVEL)
		PlayBGM("dungeon");
	else if (floor == TEMPLE_LEVEL)
		PlayBGM("dungeon");
	else if (floor >= MISTY_LAKE_LEVEL && floor <= MISTY_LAKE_LEVEL + MAX_MISTY_LAKE_LEVEL)
		PlayBGM("mistlake");
	else if (floor >= YOUKAI_MOUNTAIN_LEVEL && floor <= YOUKAI_MOUNTAIN_LEVEL + MAX_YOUKAI_MOUNTAIN_LEVEL)
		PlayBGM("youkaimountain");
	else if (floor >= SCARLET_LEVEL && floor <= SCARLET_LEVEL + MAX_SCARLET_LEVEL)
		PlayBGM("scarlet");
	else if (floor >= SCARLET_LIBRARY_LEVEL && floor <= SCARLET_LIBRARY_LEVEL + MAX_SCARLET_LIBRARY_LEVEL)
		PlayBGM("scarlet");
	else if (floor >= SCARLET_UNDER_LEVEL && floor <= SCARLET_UNDER_LEVEL + MAX_SCARLET_UNDER_LEVEL)
		PlayBGM("scarlet");
	else if (floor >= BAMBOO_LEVEL && floor <= BAMBOO_LEVEL + MAX_BAMBOO_LEVEL)
		PlayBGM("bamboo");
	else if (floor >= EIENTEI_LEVEL && floor <= EIENTEI_LEVEL + MAX_EIENTEI_LEVEL)
		PlayBGM("bamboo");
	else if (floor >= SUBTERRANEAN_LEVEL && floor < SUBTERRANEAN_LEVEL + MAX_SUBTERRANEAN_LEVEL)
		PlayBGM("subterranean");
	else if (floor == SUBTERRANEAN_LEVEL + MAX_SUBTERRANEAN_LEVEL)
		PlayBGM("subterranean");
	else if (floor >= YUKKURI_LEVEL && floor <= YUKKURI_LAST_LEVEL)
		PlayBGM("youkaimountain");
	else if (floor >= DEPTH_LEVEL && floor <= DEPTH_LAST_LEVEL)
		PlayBGM("depth");
	else if (floor >= DREAM_LEVEL && floor <= DREAM_LAST_LEVEL)
		PlayBGM("dream");
	else if (floor >= MOON_LEVEL && floor <= MOON_LAST_LEVEL)
		PlayBGM("dream");
	else if (floor == PANDEMONIUM_LEVEL)
		PlayBGM("pandemonium");
	else if (floor == PANDEMONIUM_LEVEL + 1)
		PlayBGM("pandemonium");
	else if (floor == PANDEMONIUM_LEVEL + 2)
		PlayBGM("pandemonium");
	else if (floor == PANDEMONIUM_LEVEL + 3)
		PlayBGM("pandemonium");
	else if (floor >= HAKUREI_LEVEL && floor <= HAKUREI_LAST_LEVEL)
		PlayBGM("hakurei");
	else if(floor == ZIGURRAT_LEVEL)
		PlayBGM("ziggurat");
	else if (floor == OKINA_LEVEL) {
		if (you.god_value[GT_OKINA][0] != OKINA_LEVEL
			&& you.god_value[GT_OKINA][0] >= 0 &&
			you.god_value[GT_OKINA][0] < MAXLEVEL) {
			env[you.god_value[GT_OKINA][0]].playBgm();
		}
		else
		{
			PlayBGM("dungeon");
		}
	}
	else
		PlayBGM("dungeon");
}
monster* environment::movingfloor(const coord_def &c, int prev_floor_, monster* mon_)
{
	if(isMove(c.x,c.y,mon_->isFly(),mon_->isSwim()) && !isMonsterPos(c.x,c.y) && you.position != c)
	{
		if(monster* temp = AddMonster(mon_, c))
		{/*
			if(temp->s_silence)
				env[current_level].MakeSilence(temp->position, temp->s_silence_range, true);*/
			if(mon_->s_silence)
				env[prev_floor_].MakeSilence(mon_->position, mon_->s_silence_range, false);
			if(temp->id == MON_ENSLAVE_GHOST && you.god == GT_YUYUKO)
			{	
				you.god_value[GT_YUYUKO][0] = temp->map_id;
				you.god_value[GT_YUYUKO][1] = floor;
			}
			for(int i = 0; i<5; i++)
			{
				if(you.god_value[GT_LILLY][i] && you.lilly_allys[i].map_id == mon_->map_id && you.lilly_allys[i].floor == prev_floor_ )
				{
					you.lilly_allys[i].map_id = temp->map_id;
					you.lilly_allys[i].floor = floor;
				}
			}

			mon_->hp = 0;
			env[prev_floor_].SummonClear(mon_->map_id);
			return temp;
		}
	}
	return NULL;
}	

item* environment::AddItem(const coord_def &c, item *t, int num_)
{
	WaitForSingleObject(mutx, INFINITE);
	list<item>::iterator it;
	for(it = item_list.begin();;it++)
	{
		if(it == item_list.end() || (*it).position.y > c.y || ((*it).position.y == c.y && (*it).position.x > c.x) )
		{
			t->position = c;
			it = item_list.insert(it,*t);
			if(num_ && it->is_pile)
			{
				it->weight = (it->weight*num_/it->num);
				it->num = num_;
			}
			if(isShootingSprint()) {
				it->Identify();
			}
			ReleaseMutex(mutx);
			return &(*it);
		}
		else if((*it).position.y == c.y && (*it).position.x == c.x && it->is_pile && it->SameItem(*t))
		{
			it->weight += (num_)?(t->weight*num_/t->num):t->weight;
			it->num += num_?num_:t->num;
			ReleaseMutex(mutx);
			return &(*it);
		}
	}
	ReleaseMutex(mutx);
	return NULL;
}

void environment::AddSpecialMapInfo(string string_)
{
	speciel_map_name.push_back(string_);
}


void environment::DeleteItem(const list<item>::iterator it)
{
	WaitForSingleObject(mutx, INFINITE);
	item_list.erase(it);
	ReleaseMutex(mutx);
}
bool environment::DeleteItem(const item *item_)
{
	list<item>::iterator it;
	for(it = item_list.begin();it != item_list.end();it++)
	{
		if(&(*it) == item_)	
		{
			DeleteItem(it);
			return true;
		}
	}
	return false;
}
void environment::ClearShadow()
{
	WaitForSingleObject(mutx, INFINITE);
	list<shadow>::iterator it;
	for(it = shadow_list.begin();it != shadow_list.end();)
	{
		if(env[current_level].isInSight((*it).position))
		{
			list<shadow>::iterator temp;
			temp = it;
			it++;
			shadow_list.erase(temp);
		}
		else
			it++;
	}
	ReleaseMutex(mutx);
}
void environment::ClearShadow(const coord_def &c, shadow_type type_)
{
	
	list<shadow>::iterator it;
	for(it = shadow_list.begin();it != shadow_list.end();)
	{
		if(it->position == c && it->type == type_)
		{
			WaitForSingleObject(mutx, INFINITE);
			list<shadow>::iterator temp;
			temp = it;
			it++;
			shadow_list.erase(temp);
			ReleaseMutex(mutx);
		}
		else
			it++;
	}
}
void environment::CheckFloor()
{
	list<floor_effect>::iterator it;
	for(it = floor_list.begin();it != floor_list.end() ;)
	{
		list<floor_effect>::iterator temp = it++;
		temp->prev_check();
	}
}
void environment::ActionMonster(int delay_)
{
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && !DisableMove(it->position))
		{
			(*it).action(delay_);
		}
	}
}
void environment::ActionMonsterSpecial(int delay_)
{
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && !DisableMove(it->position))
		{
			(*it).special_action(delay_, true);
		}
	}
}
void environment::ActionSmoke(int delay_)
{
	list<smoke>::iterator it;
	for(it = smoke_list.begin();it != smoke_list.end() ;)
	{
		list<smoke>::iterator temp = it++;
		if(!DisableMove(temp->position) && !temp->action(delay_))
		{
			WaitForSingleObject(mutx, INFINITE);
			smoke_list.erase(temp);
			ReleaseMutex(mutx);
		}
	}
}
void environment::ActionFloor(int delay_)
{
	list<floor_effect>::iterator it;
	for(it = floor_list.begin();it != floor_list.end() ;)
	{
		list<floor_effect>::iterator temp = it++;
		if(!DisableMove(temp->position) && !temp->action(delay_))
		{
			WaitForSingleObject(mutx, INFINITE);
			floor_list.erase(temp);
			ReleaseMutex(mutx);
		}
	}
}
bool environment::ActionEvent(int delay_)
{
	bool return_ = false;
	list<events>::iterator it;
	for(it = event_list.begin();it != event_list.end() ;)
	{
		list<events>::iterator temp = it++;
		if(!DisableMove(temp->position) && !temp->action(delay_))
		{
			event_list.erase(temp);
			return_= true;
		}
	}
	return return_;
}
bool environment::ActionSmokeEffect()
{
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && !DisableMove(it->position))
		{
			if(isSmokePos((*it).position.x,(*it).position.y))
			{
				smoke* temp = isSmokePos2((*it).position.x,(*it).position.y);
				temp->effectSmoke(&(*it));
			}
		}
	}
	if(isSmokePos(you.position.x,you.position.y))
	{
		smoke* temp = isSmokePos2(you.position.x,you.position.y);
		if(temp->effectSmoke(&you))
			return true;
	}
	return false;
}

bool environment::ActionItem(int delay_)
{
	bool stop_ = false;
	list<item>::iterator it;
	it = item_list.begin();
	for(;it != item_list.end() ;)
	{
		item *temp = &(*it);
		it++;
		if(!temp->action(delay_))
			stop_ = true;
	}
	return stop_;
}

bool environment::ShootingTurnEnd(int delay_)
{
	bool stop_ = false;
	if(isShootingSprint()) {
		list<item>::iterator it;
		it = item_list.begin();
		for(;it != item_list.end() ;)
		{
			list<item>::iterator temp = it++;
			if(temp->type == ITM_FOOD && distan_coord(temp->position, you.position) <= 2 ) {
				if (you.additem(&(*temp), true) > 0) {
					env[current_level].DeleteItem(temp);
					stop_ = true;
				}
			}
		}
	}
	return stop_;
}

bool environment::DisableMove(coord_def pos_, bool view_)
{
	int sight_ = 7;
	if(you.s_dimension)
	{
		if(abs(pos_.x - you.god_value[GT_YUKARI][0])>sight_ || abs(pos_.y - you.god_value[GT_YUKARI][1])>sight_)
			return true; //차원고정의 범위 밖에 있다.
	}
	return false;

}
bool environment::MakeSilence(coord_def center_, int length_, bool on_)
{
	length_++;
	for(int i=-length_/2;i<=length_/2;i++) //나중에 원형반복자만들면 고치기?
	{
		for(int j=-length_/2;j<=length_/2;j++)
		{
			if(i*i+j*j<=length_*length_/4)
			{
				if(on_)
					dgtile[center_.x+i][center_.y+j].silence_count++;
				else if(dgtile[center_.x+i][center_.y+j].silence_count>0)
					dgtile[center_.x+i][center_.y+j].silence_count--;

				if(dgtile[center_.x+i][center_.y+j].silence_count)
					dgtile[center_.x+i][center_.y+j].flag |= FLAG_SILENCE;
				else
					dgtile[center_.x+i][center_.y+j].flag &= ~FLAG_SILENCE;
			}
		}
	}
	return true;
	
}

bool environment::MakeViolet(coord_def center_, int length_, bool on_)
{
	length_++;
	for(int i=-length_/2;i<=length_/2;i++) //나중에 원형반복자만들면 고치기?
	{
		for(int j=-length_/2;j<=length_/2;j++)
		{
			if(i*i+j*j<=length_*length_/4)
			{
				if(on_)
					dgtile[center_.x+i][center_.y+j].violet_count++;
				else if(dgtile[center_.x+i][center_.y+j].violet_count>0)
					dgtile[center_.x+i][center_.y+j].violet_count--;

				if(dgtile[center_.x+i][center_.y+j].violet_count)
					dgtile[center_.x+i][center_.y+j].flag |= FLAG_VIOLET;
				else
					dgtile[center_.x+i][center_.y+j].flag &= ~FLAG_VIOLET;
			}
		}
	}
	return true;
}

bool environment::MakeSantuary(coord_def center_, int length_, bool on_)
{
	length_++;
	for (int i = -length_ / 2; i <= length_ / 2; i++) //나중에 원형반복자만들면 고치기?
	{
		for (int j = -length_ / 2; j <= length_ / 2; j++)
		{
			if (i*i + j*j <= length_*length_ / 4)
			{
				if (on_)
					dgtile[center_.x + i][center_.y + j].santuary_count++;
				else if (dgtile[center_.x + i][center_.y + j].santuary_count>0)
					dgtile[center_.x + i][center_.y + j].santuary_count--;

				if (dgtile[center_.x + i][center_.y + j].santuary_count)
					dgtile[center_.x + i][center_.y + j].flag |= FLAG_SANCTUARY;
				else
					dgtile[center_.x + i][center_.y + j].flag &= ~FLAG_SANCTUARY;
			}
		}
	}
	return true;

}


void environment::MakeForbid(coord_def pos,  bool center_, bool on_)
{
	if (on_) {
		if (center_)
			dgtile[pos.x][pos.y].forbid_count2++;
		else
			dgtile[pos.x][pos.y].forbid_count++;

	}
	else if (!center_ && dgtile[pos.x][pos.y].forbid_count > 0) {
		dgtile[pos.x][pos.y].forbid_count--;
	}
	else if (center_ && dgtile[pos.x][pos.y].forbid_count2 > 0) {
		dgtile[pos.x][pos.y].forbid_count2--;
	}

	if (dgtile[pos.x][pos.y].forbid_count
		|| dgtile[pos.x][pos.y].forbid_count2)
		dgtile[pos.x][pos.y].flag |= FLAG_FORBID;
	else
		dgtile[pos.x][pos.y].flag &= ~FLAG_FORBID;


}

bool environment::MakeForbid(coord_def center_, int length_, bool on_, list<coord_def> &stack_)
{
	stack_.clear();
	for (int x = center_.x - length_; x <= center_.x + length_; x++)
	{
		for (int y = center_.y - length_; y <= center_.y + length_; y++)
		{
			if (x >= 0 && y >= 0 && x < DG_MAX_X && y < DG_MAX_Y)
			{
				bool out_of_sight = pow((float)abs(center_.x - x), 2) + pow((float)abs(center_.y - y), 2) > length_*length_;

				bool intercept = false;
				for (int i = RT_BEGIN; i != RT_END; i++)
				{
					coord_def goal_ = coord_def(x, y);
					if (out_of_sight)
					{
						intercept = true;
						break;
					}
					if (distan_coord(center_, goal_) > length_*length_)
					{
						intercept = true;
						break;
					}
					beam_iterator it(center_, goal_, (round_type)i);

					while (!intercept && !it.end())
					{
						coord_def check_pos_ = (*it);
						if ((env[current_level].isExplore(check_pos_.x, check_pos_.y)
							|| env[current_level].isMapping(check_pos_.x, check_pos_.y))
							&& !env[current_level].dgtile[check_pos_.x][check_pos_.y].isSight())
						{
							intercept = true;
							break;
						}
						it++;
					}
					if (intercept == false)
						break;
					else if (i == RT_END - 1)
					{

					}
					else
						intercept = false;
				}
				if (!intercept)
				{
					coord_def pos(x, y);
					MakeForbid(pos, pos == center_, on_);
					stack_.push_back(coord_def(x, y));
				}
			}
		}
	}
	return true;
}
bool environment::AddForbid(coord_def center_)
{
	for (auto it = forbid_list.begin(); it != forbid_list.end(); it++)
	{
		if (it->position == center_)
		{
			if (it->big == true)
			{
				it->removeArea();
				it->big = false;
				it->change = true;
				ResetForbid();
				return true;
			}
			else
			{
				it->removeArea();
				WaitForSingleObject(mutx, INFINITE);
				forbid_list.erase(it);
				ReleaseMutex(mutx);
				ResetForbid();
				return false;
			}
		}
	}
	WaitForSingleObject(mutx, INFINITE);
	forbid_list.push_back(forbid(center_));
	ReleaseMutex(mutx);
	ResetForbid();
	return true;
}
bool environment::CheckForbid(coord_def center_)
{
	for (auto it = forbid_list.begin(); it != forbid_list.end(); it++)
	{
		it->setChange(center_);
	}
	return true;
}
bool environment::ResetForbid()
{
	for (auto it = forbid_list.begin(); it != forbid_list.end(); it++)
	{
		it->reset();
	}
	return true;
}



bool environment::MakeNoise(coord_def center_, int length_, const unit* excep_)
{
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && !(*it).isUserAlly() && !(*it).target && !(*it).isCompleteNeutral() && distan_coord((*it).position, center_) <= length_*length_ && &(*it) != excep_)
		{
			int block_length_ = length_;
			beam_iterator it2((*it).position,center_);
			while(block_length_ && !it2.end())
			{
				if(!env[current_level].isMove((*it2),true,true))
				{
					block_length_-=(isTutorial()  || isSprint() || isArena())?20:2;
					break;
				}
				it2++;
			}
			if(block_length_ > 0 && distan_coord((*it).position, center_) <= block_length_*block_length_)
			{
				(*it).target_pos = center_;
				if((*it).FoundTime() > (*it).memory_time) {
					(*it).memory_time = (*it).FoundTime();
				}
				(*it).state.StateTransition(MSI_NOISE);
			}
		}
	}
	return true;
}
bool environment::PostoCheckSight(coord_def center_, coord_def target_, int lengths_, bool s_dimension_)
{
	int sight_ = 7;
	//나중에 시야처리 루틴은 전부 이걸 호출하도록하자
	bool intercept = false;
	for(int i=RT_BEGIN;i!=RT_END;i++)
	{
		int length_ = lengths_;
		beam_iterator it(center_,target_,(round_type)i);
		while(!intercept && !it.end())
		{
						
			coord_def check_pos_ = (*it);
						
			if(s_dimension_)
			{
				if(abs(you.god_value[GT_YUKARI][0] - check_pos_.x)>sight_)
					check_pos_.x += (you.god_value[GT_YUKARI][0] - check_pos_.x)>0?(sight_*2+1):-(sight_*2+1);
				if(abs(you.god_value[GT_YUKARI][1] - check_pos_.y)>sight_)
					check_pos_.y += (you.god_value[GT_YUKARI][1] - check_pos_.y)>0?(sight_*2+1):-(sight_*2+1);
			}


			if(length_ == 0) //시야가 다 달았다.
			{
				intercept = true;
				break;
			}
			if(!isMove(check_pos_,true,true))
			{
				intercept = true;
				break;
			}
			it++;
			length_--;
		}
		if(intercept == false)
			break;
		else if(i == RT_END - 1)
		{
			return false; 
		}
		else
			intercept = false;
	}
	return true;
}
bool environment::MakeMapping(int percent_)
{
	if(isBamboo())
		return false;

	for(int i = 0;i < DG_MAX_X;i++)
	{
		
		for(int j = 0;j < DG_MAX_Y; j++)
		{
			bool seeing = env[current_level].isSight(coord_def(i,j));

			if(!seeing)
			{	
				for(int x=-1; x<=1;x++)
				{
					for(int y=-1; y<=1;y++)
					{
						if(env[current_level].isSight(coord_def(i+x,j+y)))
						{
							seeing = true;
							x=2;
							y=2;
						}

					}
				}			
			}
			
			if(seeing && percent_>randA(99))
				magicmapping(i,j);
		}
	}

	return true;
	
}
bool environment::MakeMapping(coord_def center_, int length_, bool passed_, int percent_)
{
	
	if(isBamboo())
		return false;

	set<coord_def> cd_set;
	cd_set.insert(center_);
	for(int i=-length_; i<=length_; i++)
	{
		for(int j=-length_; j<=length_; j++)
		{
			int abs_ = coord_def(i,j).abs();
			
			if(passed_ && abs_ < (length_+1)*(length_+1))
			{
				coord_def target_ = center_+coord_def(i,j);
				magicmapping(target_.x,target_.y);
			}
			if(!passed_ && abs_ >= (length_-1)*(length_-1) && abs_ < (length_+1)*(length_+1))
			{
				coord_def target_ = center_+coord_def(i,j);

				bool intercept = false;
				bool fail_ = false;
				for(int i=RT_BEGIN;i!=RT_END;i++)
				{
					int length_ = 8;
					beam_iterator it(center_,target_,(round_type)i);
					while(!intercept && !it.end())
					{
						cd_set.insert(*it);
						if(length_ == 0) //시야가 다 달았다.
						{
							intercept = true;
							break;
						}
						if(!env[current_level].isSight((*it)))
						{
							intercept = true;
							break;
						}
						it++;
						length_--;
					}
					if(intercept == false)
						break;
					else if(i == RT_END - 1)
					{
						fail_ = true;
						break;
					}
					else
						intercept = false;
					if(fail_)
						break;
				}
			}
		}
	}

	for(auto it= cd_set.begin(); it!= cd_set.end(); it++)
	{
		if(percent_>randA(99))
			magicmapping(it->x,it->y);
	}
	return true;
}
bool environment::seeAllMonster()
{
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for (int i = 0; i < MON_MAX_IN_FLOOR && it != mon_vector.end(); i++, it++)
	{
		if ((*it).isLive() && !(*it).isYourShight())
		{
			env[current_level].MakeShadow(it->position, it->image, it->id);
		}
	}
	return true;
}
bool environment::isSilence(coord_def pos_)
{
	return dgtile[pos_.x][pos_.y].flag & FLAG_SILENCE;
}
bool environment::isViolet(coord_def pos_)
{
	return dgtile[pos_.x][pos_.y].flag & FLAG_VIOLET;
}
bool environment::isSanctuary(coord_def pos_)
{
	return dgtile[pos_.x][pos_.y].flag & FLAG_SANCTUARY;
}
unit* environment::isMonsterPos(int x_,int y_, const unit* excep_, int* map_id_)
{
	if(you.position.x == x_ && you.position.y == y_ && excep_ != &you)
		return &you;
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && (*it).position.x == x_ && (*it).position.y == y_ && &(*it) != excep_)
		{
			if(map_id_)
				(*map_id_) = (*it).map_id;
			return &(*it);
		}
	}
	return NULL;
}
shadow* environment::isShadowPos(int x_, int y_)
{
	list<shadow>::iterator it;
	for (it = shadow_list.begin(); it != shadow_list.end();)
	{
		if (it->position.x == x_ && it->position.y == y_) {

			return &(*it);
		}
	}
	return NULL;
}
bool environment::isForbidZone(int x_, int y_)
{
	if (dgtile[x_][y_].flag & FLAG_FORBID)
		return true;
	return false;
}
bool environment::isBlockPos(int x_, int y_)
{
	if (dgtile[x_][y_].flag & FLAG_BLOCK)
		return true;
	return false;
}
bool environment::isSmokePos(int x_,int y_, bool only_fog)
{
	if(dgtile[x_][y_].flag & (only_fog?FLAG_SIGHT_SMOKE:FLAG_SMOKE))
		return true;
	return false;	
}
floor_effect* environment::isFloorEffectPos(int x_,int y_, const floor_effect* excep_)
{
	list<floor_effect>::iterator it;	
	for(it = floor_list.begin();it != floor_list.end() ;it++)
	{
		if(it->position.x == x_ && it->position.y == y_ &&  &(*it) != excep_)
		{
			return &(*it);
		}
	}
	return nullptr;	
}
smoke* environment::isSmokePos2(int x_,int y_, const smoke* excep_)
{
	list<smoke>::iterator it;
	
	for(it = smoke_list.begin();it != smoke_list.end() ;it++)
	{
		if(it->position.x == x_ && it->position.y == y_ &&  &(*it) != excep_)
		{
			return &(*it);
		}
	}
	return NULL;	
}
monster* environment::getRandomMonster(bool except_melee)
{
	random_extraction<monster*> mon_list;
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && (*it).isYourShight())
		{
			if (except_melee &&
				(pow((float)abs(you.position.x - (*it).position.x), 2)
					+ pow((float)abs(you.position.y - (*it).position.y), 2)) <= 2)
				continue;
			mon_list.push(&(*it));
		}
	}
	if (mon_list.GetSize() == 0)
		return NULL;
	return mon_list.pop();
}

int environment::insight_mon(monster_enemy_type type_) //타입은 동맹,적등등.. 나중에 필요하면 조건넣기
{
	int num_=0;
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && (*it).isYourShight())
		{
			if(type_ == MET_ENEMY && ((*it).flag & M_FLAG_UNHARM || (*it).isUserAlly() || (*it).isCompleteNeutral() || (*it).flag & M_FLAG_DECORATE)) {
				if((*it).flag & M_FLAG_DECORATE && !((*it).flag & M_FLAG_UNHARM || (*it).isUserAlly() || (*it).isCompleteNeutral())) {	
					if((*it).isSightnonblocked(you.position)) {
						(*it).flag = (*it).flag & ~M_FLAG_DECORATE; //더 이상 안전하지않음
					} else {
						continue;
					}
				} else {
					continue;
				}
			}
			num_++;
		}
	}
	return num_;
}
monster* environment::close_mon(int x_,int y_, monster_enemy_type type_)
{
	int dis_=999;
	monster* return_=NULL;
	vector<monster>::iterator it;
	it = mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && (*it).isYourShight())
		{
			int dis2_=max(abs((*it).position.x-x_),abs((*it).position.y-y_));
			if(type_ == MET_ENEMY && ((*it).flag & M_FLAG_UNHARM || (*it).isUserAlly()))
				continue;
			if(dis_>dis2_){
				dis_= dis2_;
				return_ = &(*it);
			}
		}
	}

	return return_;
}
void environment::item_view_set()
{
	list<item>::iterator it;
	it = item_list.begin();
	for(;it != item_list.end() ;it++)
	{
		if(env[current_level].isInSight((*it).position))
		{
			(*it).not_find = false;
		}
	}
}

int environment::new_item_interupt()
{
	int num_=0;
	int auto_pick=0;//자동줍기가 뷰에 보일경우
	list<item>::iterator it;
	item *itme_[3];
	it = item_list.begin();
	for(;it != item_list.end() ;it++)
	{
		if((*it).not_find && env[current_level].isInSight((*it).position))
		{
			(*it).income_view();
			if(!Auto_Pick_Up(it)) //자동줍기가 아닐경우 
			{
				if(num_<=2)
					itme_[num_] = &(*it);
				num_++;
			}
			else
			{
				auto_pick++;
			}
		}
		
	}
	if(num_)
	{
		if(num_ == 1) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_FIND_ONE,true,false,false,CL_normal,
				 PlaceHolderHelper(itme_[0]->GetName(), itme_[0]->item_color(), (itme_[0]->num)>1));
		} else if (num_ == 2) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_FIND_TWO,true,false,false,CL_normal,
				 PlaceHolderHelper(itme_[0]->GetName(), itme_[0]->item_color(), (itme_[0]->num)>1),
				 PlaceHolderHelper(itme_[1]->GetName(), itme_[1]->item_color(), (itme_[1]->num)>1));
		} else if (num_ == 3) {
			LocalzationManager::printLogWithKey(LOC_SYSTEM_FIND_THREE,true,false,false,CL_normal,
				 PlaceHolderHelper(itme_[0]->GetName(), itme_[0]->item_color(), (itme_[0]->num)>1),
				 PlaceHolderHelper(itme_[1]->GetName(), itme_[1]->item_color(), (itme_[1]->num)>1),
				 PlaceHolderHelper(itme_[2]->GetName(), itme_[2]->item_color(), (itme_[2]->num)>1));
		}
		else
			printlog(LocalzationManager::locString(LOC_SYSTEM_FIND_MANY),true,false,false,CL_normal);
	}
	else if(auto_pick) //시야에 자동줍기 템이 있을경우 -1을 리턴. 이것은 정지를 일으키진않지만 템을 줍기위해 방향을 바꾼다.
		return -1;
	return num_;
}

item* environment::close_item(vector<item*> &item_vector_)
{
	int dis_=99;
	item* return_ = NULL;
	list<item>::iterator it;
	it = item_list.begin();
	for(;it != item_list.end() ;it++)
	{
		if(env[current_level].isExplore((*it).position.x, (*it).position.y)/*env[current_level].isInSight((*it).position)*/) //이제 시야 밖에 있는 템도 가져가게?
		{
			int dis2_ = max(abs(you.position.x-(*it).position.x),abs(you.position.y-(*it).position.y));
			if(dis2_ && (*it).isautopick())
			{
				item_vector_.push_back(&(*it));

				
				if(dis2_ && dis2_<dis_){
					dis_ = dis2_;
					return_ = &(*it);
				}
			}
		}
		
	}
	sort(item_vector_.begin(),item_vector_.end(),[&](item* left_, item* right_)
	{
		return max(abs(you.position.x-(*left_).position.x),abs(you.position.y-(*left_).position.y)) < max(abs(you.position.x-(*right_).position.x),abs(you.position.y-(*right_).position.y));
	});
	

	return return_;
}
unit* environment::GetMapIDtoUnit(int Map_id_)
{
	if(Map_id_ == -1) //대상없음
		return NULL;
	else if(Map_id_ == -2) //플레이어
		return &you;
	else{
		
		for(vector<monster>::iterator it=mon_vector.begin();it!=mon_vector.end();it++)
		{
			if(it->GetMapId() == Map_id_)
				return &(*it);
		}
	}
	return NULL; //없을수있나?
}

list<item>::iterator environment::GetPositiontoitem(coord_def position_)
{
	for(list<item>::iterator it = item_list.begin();it!=item_list.end();it++)
	{
		if((*it).position.x == position_.x && (*it).position.y == position_.y)
			return it;
	}
	return item_list.end();
}
list<item>::iterator environment::GetPositiontoitemend(coord_def position_)
{
	list<item>::iterator it;
	int a_ = 0;
	for(it = item_list.begin();it!=item_list.end();it++)
	{
		if((*it).position.x == position_.x && (*it).position.y == position_.y)
			a_ = 1;
		else if(a_ == 1)
			break;
	}
	return it;
}


void SaveFile(bool test_)
{ 
	if(ReplayClass.ReplayMode())
		return;

	if(game_over)
		return;
	WaitForSingleObject(mutx, INFINITE);
	FILE *fp;

	std::wstring wfilename = save_file_w[option_mg.getSaveSlot()-1];

    if (_wfopen_s(&fp, wfilename.c_str(), L"wb") != 0 || !fp) {
		std::wstringstream ss;
		ss << L"errno: " << errno << L"\n";

		switch (errno) {
			case EACCES: ss << L"Access denied (EACCES)"; break;
			case EEXIST: ss << L"File exists (EEXIST)"; break;
			case EINVAL: ss << L"Invalid parameter (EINVAL)"; break;
			case ENOENT: ss << L"Path not found (ENOENT)"; break;
			case EMFILE: ss << L"Too many open files (EMFILE)"; break;
			case ENFILE: ss << L"Too many files in system (ENFILE)"; break;
			default: ss << L"Unknown error";
		}

		::MessageBoxW(0, ss.str().c_str(), L"fopen error", MB_OK | MB_ICONERROR);
		ReleaseMutex(mutx);
        return;
    }


	int magic_number = 1999;
	SaveData<int>(fp, magic_number); 
	{
		SaveData<char>(fp,*version_string, strlen(version_string)+1);
	}
	SaveData<int>(fp, current_level);
	//최소한의 정보


	you.SaveDatas(fp);

	for(int i = 0; i < MAXLEVEL; i++)
	{
		env[i].SaveDatas(fp);
	}
	SaveData<Iden_collect>(fp,iden_list);
	SaveData<int>(fp, unique_list.size());
	for(vector<unique_infor>::iterator it=unique_list.begin();it!=unique_list.end();it++)
	{
		SaveData<unique_infor>(fp, (*it));
	}
	SaveData<map_infor>(fp,map_list);
	SaveData<wiz_infor>(fp,wiz_list);
	save_note.SaveDatas(fp);

	ReplayClass.SaveDatas(fp);



	fclose(fp);

	ReleaseMutex(mutx);
}


void LoadFile()
{
	WaitForSingleObject(mutx, INFINITE);
	FILE *fp;

	std::wstring wfilename = save_file_w[option_mg.getSaveSlot()-1];
    if (_wfopen_s(&fp, wfilename.c_str(), L"rb") != 0 || !fp) {
        return;
    }

	int magic_number;
	LoadData<int>(fp, magic_number); //version 1.11부터 매직넘버로 시작한다
	if(magic_number != 1999) {
		//ver1.1에선 첫 int가 1999임
		current_level = magic_number;
		loading_version_string = "ver1.1";
	} else {
		{
			char temp[256];
			LoadData<char>(fp, *temp);
			loading_version_string = temp;
		}
		LoadData<int>(fp, current_level);
	}

	you.LoadDatas(fp);
	for(int i = 0; i < MAXLEVEL; i++)
	{
		env[i].LoadDatas(fp);	
	}
	LoadData<Iden_collect>(fp,iden_list);
	
	unique_list.clear();
	int size_=0;
	LoadData<int>(fp, size_);
	for(int i = 0; i < size_; i++)
	{
		unique_infor temp;
		LoadData<unique_infor>(fp,temp);
		unique_list.push_back(temp);
	}
	LoadData<map_infor>(fp,map_list);
	LoadData<wiz_infor>(fp,wiz_list);
	save_note.LoadDatas(fp);
	
	ReplayClass.LoadDatas(fp);

	


	fclose(fp);
	ReleaseMutex(mutx);
}

float GetDotX(int offset_, int x, int magnification)
{
	return offset_+x*magnification;
}
float GetDotY(int offset_, int y, int magnification)
{
	return offset_+y*magnification;
}

string CurrentLevelString(int level)
{
	ostringstream ss;

	int level_ = level>=0?level:current_level;


	if(isArena())
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_ARENA);
	else if (isSprint())
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SPRINT);
	else if(level_<TEMPLE_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON) << ' ' << LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(level_+1)));
	else if(level_ == TEMPLE_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_TEMPLE);
	else if(level_ >= MISTY_LAKE_LEVEL && level_ <= MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MISTYLAKE) << ' ' << LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(level_+1-MISTY_LAKE_LEVEL)));
	else if(level_ >= YOUKAI_MOUNTAIN_LEVEL && level_ <= YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YOUKAI_MOUNTAIN) << ' ' << LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(level_+1-YOUKAI_MOUNTAIN_LEVEL)));
	else if(level_ >= SCARLET_LEVEL && level_ <= SCARLET_LEVEL+MAX_SCARLET_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET) << ' ' << LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(level_+1-SCARLET_LEVEL)));
	else if(level_ >= SCARLET_LIBRARY_LEVEL && level_ <= SCARLET_LIBRARY_LEVEL+MAX_SCARLET_LIBRARY_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET_LIBRARY);
	else if(level_ >= SCARLET_UNDER_LEVEL && level_ <= SCARLET_UNDER_LEVEL+MAX_SCARLET_UNDER_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SCARLET_UNDER);
	else if(level_ >= BAMBOO_LEVEL && level_ <= BAMBOO_LEVEL+MAX_BAMBOO_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_BAMBOO);
	else if(level_ >= EIENTEI_LEVEL && level_ <= EIENTEI_LEVEL+MAX_EIENTEI_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_EINENTEI);
	else if(level_ >= SUBTERRANEAN_LEVEL && level_ < SUBTERRANEAN_LEVEL+MAX_SUBTERRANEAN_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SUBTERRANEAN) << ' ' << LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(level_+1-SUBTERRANEAN_LEVEL)));
	else if(level_ == SUBTERRANEAN_LEVEL+MAX_SUBTERRANEAN_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_SUBRERRANEAN_LAST);
	else if(level_ >= YUKKURI_LEVEL && level_ <=  YUKKURI_LAST_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_YUKKURI) << ' ' << LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(level_+1-YUKKURI_LEVEL)));
	else if(level_ >= DEPTH_LEVEL && level_ <=  DEPTH_LAST_LEVEL)		
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DEPTH) << ' ' << LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(level_+1-DEPTH_LEVEL)));
	else if(level_ >= DREAM_LEVEL && level_ <=  DREAM_LAST_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_DREAM);
	else if(level_ >= MOON_LEVEL && level_ <=  MOON_LAST_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_MOON);
	else if(level_ == PANDEMONIUM_LEVEL)		
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM);
	else if(level_ == PANDEMONIUM_LEVEL+1)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_HOKKAI);
	else if(level_ == PANDEMONIUM_LEVEL+2)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_FROZEN_FIELD);
	else if(level_ == PANDEMONIUM_LEVEL+3)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_PANDEMONIUM_LAST);
	else if(level_ >= HAKUREI_LEVEL && level_ <=  HAKUREI_LAST_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_HAKUREI) << ' ' << LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(level_+1-HAKUREI_LEVEL)));
	else if (level_ == OKINA_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_OKINA);
	else if (level_ == ZIGURRAT_LEVEL)
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_ZIGURRAT) << ' ' << LocalzationManager::formatString(LOC_SYSTEM_DUNGEON_FLOOR, PlaceHolderHelper(to_string(you.ziggurat_level)));
	else
		ss << LocalzationManager::locString(LOC_SYSTEM_DUNGEON_UKNOWN_DUNGEON);

	return ss.str();
}
int GetLevelMonsterNum(int level, bool item_)
{
	int level_ = level>=0?level:current_level;
	if(!item_)
	{
		float multi_ = 1.0f;

		if (int penalty_turn_ = you.CheckPeanltyTurn(level))
		{
			//1000부터 시작해서 5000턴부터 몬스터 2배
			if (penalty_turn_ >= 1000) {
				multi_ += min(penalty_turn_ - 1000, 4000) / 4000.0f;
			}
		}



		if(level_ == TEMPLE_LEVEL || level_ == BAMBOO_LEVEL)
			return 0* multi_;
		else if(level_ >= DREAM_LEVEL && level_ <= DREAM_LAST_LEVEL)
			return 6 * multi_;
		else if(level_ >= MISTY_LAKE_LEVEL && level_ < MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL)
			return 10;
		else if(level_ == MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL)
			return 15;
		else if(level_ >= YUKKURI_LEVEL && level_ <= YUKKURI_LAST_LEVEL)
			return 18;
		else if(level_ >= DEPTH_LEVEL && level_ <= DEPTH_LAST_LEVEL)
			return 15;
		else if (level_ >= PANDEMONIUM_LEVEL && level_ <= PANDEMONIUM_LAST_LEVEL)
			return 12 * multi_;
		else
			return 9 * multi_;
	}
	else{ //아이템
		if(level_ == TEMPLE_LEVEL || level_ == BAMBOO_LEVEL || level_ == YUKKURI_LAST_LEVEL || level_ == EIENTEI_LEVEL || level_ == MOON_LEVEL)
			return 0;
		if(level_ >= SUBTERRANEAN_LEVEL && level_ <= SUBTERRANEAN_LEVEL_LAST_LEVEL)
			return 0;
		if(level_ >= PANDEMONIUM_LEVEL && level_ <= PANDEMONIUM_LAST_LEVEL)
			return 8;
		else
			return 12;
	}

}

void Noise(coord_def center_, int length_, const unit* excep_)
{

	env[current_level].MakeNoise(center_,length_,excep_);
}