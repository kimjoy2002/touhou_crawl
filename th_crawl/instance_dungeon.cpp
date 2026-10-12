//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: instance_dungeon.cpp
//
// 내용: 일회용 인스턴스 서브던전
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "instance_dungeon.h"
#include "map.h"
#include "environment.h"
#include "mon_infor.h"
#include "monster.h"
#include "item.h"
#include "atifact.h"
#include "note.h"
#include "rect.h"
#include "player.h"
#include <algorithm>

instance_dungeon_manager instance_dungeon;

bool PixedMap(map_dummy* map, const char *temp);
const char* common_enter_pattern(map_dummy* map);
void setBaseFloorWall(int floor_, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);
item_infor& id_to_item(int id, item_infor* item_);
int get_unique_to_id(int m_id);

static bool CanChooseFairyTree();
static void make_map_fairy_tree(int floor_, const instance_dungeon_slot& slot_);
static void make_map_temp(int floor_, const instance_dungeon_slot& slot_);

//////////////////////////////////////////////////////////////////////////////////////////////////
// 던전 목록
// {종류, 시기, 이름, 덤프용 이름, 전용 네임드, 맵 생성, 클리어 조건, 선택 조건, 보상 최소, 보상 최대}
//////////////////////////////////////////////////////////////////////////////////////////////////
static const vector<instance_dungeon_infor> instance_dungeon_list = {
	{IDG_FAIRY_TREE, IDT_EARLY, LOC_SYSTEM_DUNGEON_INSTANCE_FAIRY_TREE, "FAIRY_TREE", {MON_SUNNY, MON_LUNAR, MON_STAR}, make_map_fairy_tree, nullptr, CanChooseFairyTree},
	{IDG_DARK_FOREST_PATH, IDT_EARLY, LOC_SYSTEM_DUNGEON_INSTANCE_DARK_FOREST_PATH, "DARK_FOREST_PATH", {}, make_map_temp, nullptr, nullptr},
	{IDG_MAYOIGA, IDT_EARLY, LOC_SYSTEM_DUNGEON_INSTANCE_MAYOIGA, "MAYOIGA", {}, make_map_temp, nullptr, nullptr},
};



//////////////////////////////////////////////////////////////////////////////////////////////////
// 요정이 사는 거목
//////////////////////////////////////////////////////////////////////////////////////////////////

static bool CanChooseFairyTree()
{
	return you.char_type != UNIQ_START_SUNNY && you.char_type != UNIQ_START_STAR && you.char_type != UNIQ_START_LUNA;
}

static void make_map_fairy_tree(int floor_, const instance_dungeon_slot& slot_)
{
	instance_spawn_table table_;
	table_.weak.push(MON_FAIRY_GREEN, 10);
	table_.weak.push(MON_FAIRY_BLUE, 10);
	table_.weak.push(MON_FAIRY_RED, 10);
	table_.all.push(MON_FAIRY_GREEN, 10);
	table_.all.push(MON_FAIRY_BLUE, 10);
	table_.all.push(MON_FAIRY_RED, 10);
	table_.strong.push(MON_FAIRY_GREEN_WARRIOR, 10);
	table_.strong.push(MON_FAIRY_BLUE_MAGICIAN, 10);
	table_.strong.push(MON_FAIRY_RED_COMMANDER, 5);
	table_.item.push(2, 10); //좋은 초반물약
	table_.item.push(3, 10); //좋은 초반스크롤

	vector<coord_def> pos_list_;
	MakeInstanceMapFromPattern(floor_, "\
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\
TTTTTTTTTTTTTTTTTTTTiiiiiTTTTTTTTTTTTTTTTTTTT\
TTTTTTTTTTT____TTTii.....iiTTT____TTTTTTTTTTT\
TTTTTTT_______TTT...........TTT_______TTTTTTT\
TTTT__________TT.............TT__________TTTT\
TT____________TT......S......TT____________TT\
T____________TTT..S.......S..TTT____________T\
T________TTTTTTT.............TTTTTTT________T\
T_____TTTT...TTT.............TTT...TTTT_____T\
T____TTT......TT.............TT......TTT____T\
T___TTT.......TTT...........TTT.......TTT___T\
T___TT.........TTTT.......TTTT.........TT___T\
T___TT......m....TTTT...TTTT....m......TT___T\
T___TT.............TTT+TTT.............TT___T\
T___T....m.M.......+.....+.......M.m....T___T\
T___TT.............T.....T.............TT___T\
T___TT.......m.....T.....T.....m.......TT___T\
T___TTT...........TT.....TT...........TTT___T\
T____TTTT.......TTTT.....TTTT.......TTTT____T\
T______TTTTTTTTTTTTT.....TTTTTTTTTTTTT______T\
T_______________TTTT.....TTTT_______________T\
T_________________TTT...TTT_________________T\
T__________________TT...TT__________________T\
T__________________TT...TT__________________T\
T___________________TT+TT___________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
T___________________________________________T\
TT_________________________________________TT\
TTTT_____________________________________TTTT\
TTTTTTT_______________________________TTTTTTT\
TTTTTTTTTTT_______________________TTTTTTTTTTT\
TTTTTTTTTTTTTTTT______<______TTTTTTTTTTTTTTTT\
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",
		22, 24, DG_FLOOR2, DG_TREE, &pos_list_, &table_);

	const monster_index fairies_[] = { MON_SUNNY, MON_LUNAR, MON_STAR };
	int i = 0;
	for (auto it = pos_list_.begin(); it != pos_list_.end() && i < 3; it++, i++)
		AddInstanceMonster(floor_, fairies_[i], *it);
}

//임시 던전
static void make_map_temp(int floor_, const instance_dungeon_slot& slot_)
{
	dungeon_tile_type floor_tex_ = DG_FLOOR, wall_tex_ = DG_WALL;
	switch (slot_.type)
	{
	default: floor_tex_ = DG_GRASS; wall_tex_ = DG_STONE_WALL; break;
	}
	MakeInstanceMapFromPattern(floor_, "\
#########################\
#...........#...........#\
#..m........#........m..#\
#.....###.......###.....#\
#.....#...........#.....#\
#..........m............#\
#.....#...........#.....#\
#.....###.......###.....#\
#.......................#\
###+####...M.....####+###\
#.......................#\
#.....###.......###.....#\
#.....#...........#.....#\
#..........m............#\
#.....#...........#.....#\
#.....###.......###.....#\
#..m........#........m..#\
#...........<...........#\
#########################",
		12, 9, floor_tex_, wall_tex_);
}



//시기별로 입구가 나올 수 있는 층
static void GetTierFloors(instance_dungeon_tier tier_, vector<int>& floors_)
{
	switch (tier_)
	{
	case IDT_EARLY:
		for (int i = 2; i <= 4; i++)
			floors_.push_back(i);
		break;
	case IDT_MIDDLE:
		floors_.push_back(MISTY_LAKE_LEVEL + 3);
		floors_.push_back(MISTY_LAKE_LEVEL + 4);
		floors_.push_back(YOUKAI_MOUNTAIN_LEVEL);
		if (map_list.dungeon_enter[SCARLET_M].floor != -1)
			floors_.push_back(SCARLET_LEVEL);
		if (map_list.dungeon_enter[FORESTOFMAGIC].floor != -1)
			floors_.push_back(FORESTOFMAGIC_LEVEL);
		break;
	case IDT_LATE:
		for (int i = DEPTH_LEVEL; i <= DEPTH_LEVEL + 3; i++)
			floors_.push_back(i);
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// 공용 함수
//////////////////////////////////////////////////////////////////////////////////////////////////

const instance_dungeon_infor* GetInstanceDungeonInfor(instance_dungeon_type type_)
{
	for (const instance_dungeon_infor& infor_ : instance_dungeon_list)
		if (infor_.type == type_)
			return &infor_;
	return nullptr;
}

int GetInstanceBaseFloor(int floor_)
{
	if (floor_ != INSTANCE_LEVEL)
		return floor_;
	if (instance_dungeon_slot* slot_ = instance_dungeon.GetCurrentSlot())
		return slot_->floor;
	return 0;
}

string GetInstanceDungeonName()
{
	if (instance_dungeon_slot* slot_ = instance_dungeon.GetCurrentSlot())
		if (const instance_dungeon_infor* infor_ = GetInstanceDungeonInfor(slot_->type))
			return LocalzationManager::locString(infor_->name);
	return LocalzationManager::locString(LOC_SYSTEM_DUNGEON_INSTANCE);
}

static instance_spawn_table* current_spawn_table = nullptr; //MakeInstanceMapFromPattern 도중에만 쓰임

int GetInstanceFloorMonster(int floor_, int power_)
{
	if (floor_ == INSTANCE_LEVEL && current_spawn_table)
	{
		instance_spawn_table& table_ = *current_spawn_table;
		switch (power_)
		{
		case GMFF_FLAG_ONLY_WEAK:
			if (table_.weak.GetSize())
				return table_.weak.choice();
			break;
		case GMFF_FLAG_ONLY_STRONG:
			if (table_.strong.GetSize())
				return table_.strong.choice();
			break;
		default:
			break;
		}
		if (table_.all.GetSize())
			return table_.all.choice();
		if (power_ == GMFF_FLAG_ALL && (table_.weak.GetSize() || table_.strong.GetSize()))
		{
			random_extraction<random_extraction<int>*> groups_;
			groups_.push(&table_.weak, table_.weak.GetSize() ? 1 : 0);
			groups_.push(&table_.strong, table_.strong.GetSize() ? 1 : 0);
			return groups_.choice()->choice();
		}
	}
	return getMonsterFromFloor(GetInstanceBaseFloor(floor_), (getMonsterFromFloor_flag)power_);
}

void CreateInstanceFloorItem(int floor_, item_infor* item_)
{
	if (floor_ == INSTANCE_LEVEL && current_spawn_table && current_spawn_table->item.GetSize())
		id_to_item(current_spawn_table->item.choice(), item_);
	else
		CreateFloorItem(GetInstanceBaseFloor(floor_), item_);
}

void MakeInstanceMapFromPattern(int floor_, const char* pattern_, int size_x_, int size_y_,
	dungeon_tile_type floor_tex_, dungeon_tile_type wall_tex_, vector<coord_def>* pos_list_,
	instance_spawn_table* table_)
{
	environment& env_ = env[floor_];
	coord_def center_(DG_MAX_X / 2, DG_MAX_Y / 2);
	for (int x = 0; x < DG_MAX_X; x++)
		for (int y = 0; y < DG_MAX_Y; y++)
			env_.dgtile[x][y].tile = wall_tex_;
	for (int i = 0; i < 3; i++)
	{
		env_.stair_up[i] = coord_def(0, 0);
		env_.stair_down[i] = center_;
	}

	map_dummy map_(floor_, center_, false, size_x_, size_y_, 0, floor_tex_, wall_tex_);
	current_spawn_table = table_;
	PixedMap(&map_, pattern_);
	current_spawn_table = nullptr;
	map_.make_map(env_, false, true);

	//인스턴스 던전의 올라가는 계단은 전부 원래 층으로 돌아가는 계단이다.
	for (int x = 0; x < DG_MAX_X; x++)
		for (int y = 0; y < DG_MAX_Y; y++)
			if (env_.dgtile[x][y].tile == DG_UP_STAIR)
				env_.dgtile[x][y].tile = DG_RETURN_STAIR;
	if (env_.dgtile[env_.stair_up[0].x][env_.stair_up[0].y].tile != DG_RETURN_STAIR)
	{
		env_.stair_up[0] = center_;
		env_.dgtile[center_.x][center_.y].tile = DG_RETURN_STAIR;
	}
	for (int i = 1; i < 3; i++)
		if (env_.dgtile[env_.stair_up[i].x][env_.stair_up[i].y].tile != DG_RETURN_STAIR)
			env_.stair_up[i] = env_.stair_up[0];

	if (pos_list_)
		pos_list_->insert(pos_list_->end(), map_.pos_list.begin(), map_.pos_list.end());
	setBaseFloorWall(floor_, floor_tex_, wall_tex_);
}

monster* AddInstanceMonster(int floor_, int id_, const coord_def& pos_, uint64_t flag_)
{
	environment& env_ = env[floor_];
	for (dif_rect_iterator rit(pos_, 3); !rit.end(); rit++)
	{
		if (!env_.isMove(rit->x, rit->y) || env_.isMonsterPos(rit->x, rit->y) || env_.isStair(rit->x, rit->y))
			continue;
		if (monster* mon_ = env_.AddMonster(id_, flag_, *rit))
		{
			mon_->SetStrong(mon_->isUnique() ? 5 : 1);
			return mon_;
		}
		return nullptr;
	}
	return nullptr;
}

void map_algorithms_instance(int num)
{
	env[num].ClearFloor();
	instance_dungeon_slot* slot_ = instance_dungeon.GetCurrentSlot();
	const instance_dungeon_infor* infor_ = slot_ ? GetInstanceDungeonInfor(slot_->type) : nullptr;
	if (infor_ && infor_->make_map)
	{
		infor_->make_map(num, *slot_);
		return;
	}
	//정보가 없으면 돌아가는 계단만 있는 방
	MakeInstanceMapFromPattern(num, "\
#####\
#...#\
#.<.#\
#...#\
#####", 2, 2, DG_FLOOR, DG_WALL);
}

const char* instance_enter_pattern(map_dummy* map, int index_)
{
	map->sp_tile_list.clear();
	map->sp_tile_list.push_back(DG_INSTANCE_STAIR);
	const char* pattern_ = common_enter_pattern(map);
	map->name = "INSTANCE_ENTER";
	if (instance_dungeon_slot* slot_ = instance_dungeon.GetSlot(index_))
		if (const instance_dungeon_infor* infor_ = GetInstanceDungeonInfor(slot_->type))
			map->name = string("INSTANCE_") + infor_->id_name + "_ENTER";
	return pattern_;
}

static bool DefaultInstanceClear(int floor_, const instance_dungeon_infor* infor_)
{
	for (monster& mon_ : env[floor_].mon_vector)
	{
		if (!mon_.isLive() || mon_.isUserAlly())
			continue;
		if (!infor_->named.empty())
		{
			if (find(infor_->named.begin(), infor_->named.end(), (monster_index)mon_.id) != infor_->named.end())
				return false;
		}
		else if (!(mon_.flag & (M_FLAG_INANIMATE | M_FLAG_NONE_MOVE)))
			return false;
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// instance_dungeon_manager
//////////////////////////////////////////////////////////////////////////////////////////////////

//이 던전의 전용 네임드를 예약할 수 있는지 (이미 다른곳에 나왔거나 볼트에 쓰였으면 불가)
static bool CanReserveNamed(const instance_dungeon_infor& infor_)
{
	for (monster_index id_ : infor_.named)
	{
		int unique_id_ = get_unique_to_id(id_);
		for (const unique_infor& unique_ : unique_list)
		{
			if (unique_.id != unique_id_)
				continue;
			if (unique_.level < 0 || unique_.level >= MAXLEVEL || env[unique_.level].make)
				return false;
		}
	}
	return true;
}

void instance_dungeon_manager::choose(bool old_save_)
{
	slots.clear();
	current = -1;
	if (!isNormalGame())
		return;
	for (int tier_ = 0; tier_ < IDT_MAX; tier_++)
	{
		random_extraction<const instance_dungeon_infor*> types_;
		for (const instance_dungeon_infor& infor_ : instance_dungeon_list)
		{
			if (infor_.tier != tier_)
				continue;
			if (infor_.can_choose && !infor_.can_choose())
				continue;
			if (!CanReserveNamed(infor_))
				continue;
			types_.push(&infor_);
		}
		vector<int> floors_;
		GetTierFloors((instance_dungeon_tier)tier_, floors_);
		if (old_save_) //이미 만들어진 층엔 입구를 넣을 수 없다.
			floors_.erase(remove_if(floors_.begin(), floors_.end(), [](int f) {return env[f].make; }), floors_.end());
		if (types_.GetSize() == 0 || floors_.empty())
			continue;

		const instance_dungeon_infor* infor_ = types_.pop();
		instance_dungeon_slot slot_;
		slot_.type = infor_->type;
		slot_.floor = floors_[randA(floors_.size() - 1)];
		for (monster_index id_ : infor_->named)
			set_exist_named(id_);
		slots.push_back(slot_);
	}
}

void instance_dungeon_manager::init()
{
	choose(false);
}

void instance_dungeon_manager::initForOldSave()
{
	choose(true);
}

void instance_dungeon_manager::SaveDatas(FILE* fp)
{
	const char marker[4] = { 'I', 'D', 'G', '1' };
	fwrite(marker, 1, sizeof(marker), fp);
	int count = (int)slots.size();
	fwrite(&count, sizeof(count), 1, fp);
	for (const instance_dungeon_slot& slot_ : slots)
	{
		int data_[5] = { (int)slot_.type, slot_.floor, slot_.pos.x, slot_.pos.y, (int)slot_.state };
		fwrite(data_, sizeof(int), 5, fp);
	}
	fwrite(&current, sizeof(current), 1, fp);
}

bool instance_dungeon_manager::LoadDatas(FILE* fp)
{
	slots.clear();
	current = -1;
	char marker[4];
	if (fread(marker, 1, sizeof(marker), fp) != sizeof(marker) ||
		marker[0] != 'I' || marker[1] != 'D' || marker[2] != 'G' || marker[3] != '1')
		return false;
	int count = 0;
	if (fread(&count, sizeof(count), 1, fp) != 1 || count <= 0 || count > 100)
		return false;
	vector<int> index_map_;
	for (int i = 0; i < count; i++)
	{
		int data_[5];
		if (fread(data_, sizeof(int), 5, fp) != 5)
			return false;
		index_map_.push_back(-1);
		if (!GetInstanceDungeonInfor((instance_dungeon_type)data_[0]))
			continue;
		instance_dungeon_slot slot_;
		slot_.type = (instance_dungeon_type)data_[0];
		slot_.floor = data_[1];
		slot_.pos = coord_def(data_[2], data_[3]);
		slot_.state = (instance_dungeon_state)data_[4];
		index_map_.back() = (int)slots.size();
		slots.push_back(slot_);
	}
	int current_ = -1;
	if (fread(&current_, sizeof(current_), 1, fp) == 1 && current_ >= 0 && current_ < (int)index_map_.size())
		current = index_map_[current_];
	return true;
}

instance_dungeon_slot* instance_dungeon_manager::GetSlot(int index_)
{
	if (index_ < 0 || index_ >= (int)slots.size())
		return nullptr;
	return &slots[index_];
}

instance_dungeon_slot* instance_dungeon_manager::GetCurrentSlot()
{
	return GetSlot(current);
}

int instance_dungeon_manager::GetSlotIndex(int floor_, const coord_def& pos_)
{
	for (int i = 0; i < (int)slots.size(); i++)
		if (slots[i].floor == floor_ && slots[i].pos == pos_)
			return i;
	return -1;
}

void instance_dungeon_manager::GetEnterPatterns(int floor_, vector<int>& vector_)
{
	for (int i = 0; i < (int)slots.size(); i++)
		if (slots[i].floor == floor_ && slots[i].state == IDS_READY)
			vector_.push_back(INSTANCE_ENTER_PATTERN + i);
}

void instance_dungeon_manager::SetEnterPos(int floor_, int index_, const coord_def& pos_)
{
	if (instance_dungeon_slot* slot_ = GetSlot(index_))
		if (slot_->floor == floor_)
			slot_->pos = pos_;
}

void instance_dungeon_manager::CheckEnterPlaced(int floor_)
{
	environment& env_ = env[floor_];
	for (instance_dungeon_slot& slot_ : slots)
	{
		if (slot_.floor != floor_ || slot_.state != IDS_READY)
			continue;
		if (env_.dgtile[slot_.pos.x][slot_.pos.y].tile != DG_INSTANCE_STAIR)
		{ //입구 볼트가 못 들어갔으면 아무 바닥에나 박는다.
			random_extraction<coord_def> candidates_;
			for (int x = 1; x < DG_MAX_X - 1; x++)
				for (int y = 1; y < DG_MAX_Y - 1; y++)
					if (env_.dgtile[x][y].isFloor() && !(env_.dgtile[x][y].flag & FLAG_NO_STAIR) && !env_.isMonsterPos(x, y))
						candidates_.push(coord_def(x, y));
			if (candidates_.GetSize() == 0)
				continue;
			slot_.pos = candidates_.pop();
			env_.dgtile[slot_.pos.x][slot_.pos.y].tile = DG_INSTANCE_STAIR;
		}
		bool registered_ = false;
		for (const stair_info& stair_ : env_.stair_vector)
			if (stair_.pos == slot_.pos)
				registered_ = true;
		if (!registered_)
			env_.stair_vector.push_back(stair_info(slot_.pos, DG_INSTANCE_STAIR));
	}
}

bool instance_dungeon_manager::CanEnter(int floor_, const coord_def& pos_)
{
	instance_dungeon_slot* slot_ = GetSlot(GetSlotIndex(floor_, pos_));
	return slot_ && slot_->state == IDS_READY;
}

void instance_dungeon_manager::Enter(int floor_, const coord_def& pos_)
{
	current = GetSlotIndex(floor_, pos_);
	if (instance_dungeon_slot* slot_ = GetCurrentSlot())
		slot_->state = IDS_ENTERED;
	env[INSTANCE_LEVEL].make = false; //매번 새로 만든다.
}

void instance_dungeon_manager::Exit()
{
	instance_dungeon_slot* slot_ = GetCurrentSlot();
	if (slot_)
	{
		if (slot_->state == IDS_ENTERED)
			slot_->state = IDS_CLOSED;
		env[INSTANCE_LEVEL].AllySafeClear(slot_->floor, slot_->pos);

		//한번 나오면 입구는 사라진다.
		environment& env_ = env[slot_->floor];
		if (env_.dgtile[slot_->pos.x][slot_->pos.y].tile == DG_INSTANCE_STAIR)
		{
			env_.changeTile(slot_->pos, env_.base_floor);
			coord_def pos_ = slot_->pos;
			env_.stair_vector.erase(remove_if(env_.stair_vector.begin(), env_.stair_vector.end(),
				[pos_](const stair_info& stair_) {return stair_.pos == pos_; }), env_.stair_vector.end());
			printlog(LocalzationManager::locString(LOC_SYSTEM_INSTANCE_DUNGEON_CLOSE), true, false, false, CL_normal);
		}
	}
	env[INSTANCE_LEVEL].ClearFloor();
	env[INSTANCE_LEVEL].make = false;
	current = -1;
}

void instance_dungeon_manager::WizardEnter(instance_dungeon_type type_, int floor_, const coord_def& pos_)
{
	instance_dungeon_slot slot_;
	slot_.type = type_;
	slot_.floor = floor_;
	slot_.pos = pos_;
	slot_.state = IDS_ENTERED;
	slots.push_back(slot_);
	current = (int)slots.size() - 1;
	env[INSTANCE_LEVEL].make = false;
}

void instance_dungeon_manager::TurnEnd()
{
	if (current_level != INSTANCE_LEVEL)
		return;
	instance_dungeon_slot* slot_ = GetCurrentSlot();
	if (!slot_ || slot_->state != IDS_ENTERED)
		return;
	const instance_dungeon_infor* infor_ = GetInstanceDungeonInfor(slot_->type);
	if (!infor_)
		return;
	if (infor_->is_clear ? !infor_->is_clear(current_level) : !DefaultInstanceClear(current_level, infor_))
		return;

	slot_->state = IDS_CLEAR;
}
