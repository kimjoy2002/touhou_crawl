//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: scarlet_under.cpp
//
// 내용: 홍마관 지하실용 (무한 복도)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "scarlet_under.h"
#include "map.h"
#include "event.h"
#include "smoke.h"
#include "floor.h"
#include "mon_infor.h"
#include "item.h"

extern HANDLE mutx;

void setBaseFloorWall(int floor_, dungeon_tile_type floor_tex, dungeon_tile_type wall_tex);

namespace
{
	int floor_div(int value_, int divisor_)
	{
		if(value_ >= 0)
			return value_/divisor_;
		return -((-value_+divisor_-1)/divisor_);
	}

	int floor_mod(int value_, int divisor_)
	{
		int result_ = value_%divisor_;
		return result_ < 0?result_+divisor_:result_;
	}

	unsigned int scarlet_under_hash(int x_, int y_, int seed_, unsigned int salt_)
	{
		unsigned int value_ = (unsigned int)seed_^salt_;
		value_ ^= (unsigned int)x_*0x9e3779b9u;
		value_ ^= (unsigned int)y_*0x85ebca6bu;
		value_ ^= value_ >> 16;
		value_ *= 0x7feb352du;
		value_ ^= value_ >> 15;
		value_ *= 0x846ca68bu;
		return value_^(value_ >> 16);
	}

	int scarlet_under_jitter(int line_, int point_, int max_offset_, int seed_, unsigned int salt_)
	{
		if(line_ == 0 && point_ == 0)
			return 0;
		return (int)(scarlet_under_hash(line_,point_,seed_,salt_)%(max_offset_*2+1))-max_offset_;
	}

	int scarlet_under_grid_offset(int line_, int grid_size_, int seed_, unsigned int salt_)
	{
		if(line_ == 0)
			return 0;
		int max_offset_ = max(1,grid_size_/5);
		return (int)(scarlet_under_hash(line_,0,seed_,salt_)%(max_offset_*2+1))-max_offset_;
	}

	int scarlet_under_line_offset(int line_, int along_, int corridor_width_, int grid_size_,
		int bend_frequency_, int seed_, unsigned int salt_)
	{
		int bend_length_ = grid_size_*max(1,bend_frequency_);
		int phase_ = line_ == 0?0:(int)(scarlet_under_hash(line_,0,seed_,salt_^0x27d4eb2du)%bend_length_);
		int section_ = floor_div(along_+phase_,bend_length_);
		int position_ = floor_mod(along_+phase_,bend_length_);
		int max_offset_ = max(1,(grid_size_-corridor_width_)*2/5);
		int first_ = scarlet_under_jitter(line_,section_,max_offset_,seed_,salt_);
		int second_ = scarlet_under_jitter(line_,section_+1,max_offset_,seed_,salt_);
		return (first_*(bend_length_-position_)+second_*position_)/bend_length_;
	}

	bool scarlet_under_floor(int world_x_, int world_y_, int corridor_width_, int grid_size_,
		int bend_frequency_, int seed_)
	{
		int half_width_ = max(0,corridor_width_/2);
		int horizontal_ = floor_div(world_y_+grid_size_/2,grid_size_);
		for(int line_ = horizontal_-1;line_ <= horizontal_+1;line_++)
		{
			int horizontal_y_ = line_*grid_size_+
				scarlet_under_grid_offset(line_,grid_size_,seed_,0x165667b1u)+
				scarlet_under_line_offset(line_,world_x_,corridor_width_,grid_size_,bend_frequency_,seed_,0x4f1bbcdcu);
			if(abs(world_y_-horizontal_y_) <= half_width_)
				return true;
		}
		int vertical_ = floor_div(world_x_+grid_size_/2,grid_size_);
		for(int line_ = vertical_-1;line_ <= vertical_+1;line_++)
		{
			int vertical_x_ = line_*grid_size_+
				scarlet_under_grid_offset(line_,grid_size_,seed_,0x9e3779b9u)+
				scarlet_under_line_offset(line_,world_y_,corridor_width_,grid_size_,bend_frequency_,seed_,0x94d049bbu);
			if(abs(world_x_-vertical_x_) <= half_width_)
				return true;
		}
		return false;
	}

	dungeon_tile_type scarlet_under_tile(int world_x_, int world_y_, dungeon_tile_type floor_tex_,
		dungeon_tile_type wall_tex_, int corridor_width_, int grid_size_, int bend_frequency_,
		int exit_frequency_, int seed_)
	{
		if(!scarlet_under_floor(world_x_,world_y_,corridor_width_,grid_size_,bend_frequency_,seed_))
			return wall_tex_;
		if(exit_frequency_ > 0 && (abs(world_x_) > grid_size_ || abs(world_y_) > grid_size_) &&
			scarlet_under_hash(world_x_,world_y_,seed_,0xd1b54a35u)%(unsigned int)exit_frequency_ == 0)
			return DG_RETURN_STAIR;
		return floor_tex_;
	}

	bool in_scarlet_under_map(const coord_def& pos_)
	{
		return pos_.x >= 0 && pos_.x < DG_MAX_X && pos_.y >= 0 && pos_.y < DG_MAX_Y;
	}

	bool has_scarlet_under_room(int num)
	{
		for(events& event_ : env[num].event_list)
			if(event_.id == EVL_SCARLET_UNDER_REWARD)
				return true;
		for(monster& mon_ : env[num].mon_vector)
			if(mon_.isLive() && mon_.id == MON_FLAN)
				return true;
		for(item& item_ : env[num].item_list)
			if(item_.type == ITM_GOAL && item_.value1 == RUNE_SCARLET_UNDER)
				return true;
		return false;
	}

	monster* make_scarlet_under_monster(int num, const coord_def& pos_)
	{
		random_extraction<int> rand_monster;
		rand_monster.push(MON_VAMPIER_BAT,4);
		rand_monster.push(MON_MAID_FAIRY,2);
		rand_monster.push(MON_CHUPARCABRA,1);
		if(!you.rune[RUNE_SCARLET_UNDER])
			rand_monster.push(MON_FLAN_AFTERIMAGE,6);

		monster* mon_ = env[num].AddMonster(rand_monster.choice(),
			M_FLAG_WAKE | M_FLAG_NONE_STAIR,pos_);
		if(mon_)
			mon_->state.SetState(MS_NORMAL);
		return mon_;
	}

	events* get_scarlet_under_frontier(int num, events* controller_)
	{
		for(events& event_ : env[num].event_list)
			if(event_.id == EVL_SCARLET_UNDER_FRONTIER)
				return &event_;

		coord_def origin_ = controller_->position;
		env[num].MakeEvent(EVL_SCARLET_UNDER_FRONTIER,
			coord_def(origin_.x,origin_.x+DG_MAX_X-1),EVT_ALWAYS,
			origin_.y,origin_.y+DG_MAX_Y-1);
		return &env[num].event_list.back();
	}

	bool extend_scarlet_under_frontier(int num, events* controller_, const coord_def& offset_,
		coord_def& direction_)
	{
		events* frontier_ = get_scarlet_under_frontier(num,controller_);
		coord_def new_origin_ = controller_->position-offset_;
		int new_left_ = new_origin_.x;
		int new_right_ = new_origin_.x+DG_MAX_X-1;
		int new_top_ = new_origin_.y;
		int new_bottom_ = new_origin_.y+DG_MAX_Y-1;
		bool left_ = new_left_ < frontier_->position.x;
		bool right_ = new_right_ > frontier_->position.y;
		bool top_ = new_top_ < frontier_->count;
		bool bottom_ = new_bottom_ > frontier_->value;

		frontier_->position.x = min(frontier_->position.x,new_left_);
		frontier_->position.y = max(frontier_->position.y,new_right_);
		frontier_->count = min(frontier_->count,new_top_);
		frontier_->value = max(frontier_->value,new_bottom_);

		direction_ = coord_def(0,0);
		if(abs(offset_.x) >= abs(offset_.y))
		{
			if(offset_.x > 0 && left_)
				direction_.x = -1;
			else if(offset_.x < 0 && right_)
				direction_.x = 1;
		}
		if(!direction_.x)
		{
			if(offset_.y > 0 && top_)
				direction_.y = -1;
			else if(offset_.y < 0 && bottom_)
				direction_.y = 1;
		}
		if(!direction_.x && !direction_.y)
		{
			if(left_)
				direction_.x = -1;
			else if(right_)
				direction_.x = 1;
			else if(top_)
				direction_.y = -1;
			else if(bottom_)
				direction_.y = 1;
		}
		return direction_.x || direction_.y;
	}

	coord_def get_scarlet_under_room_position(const coord_def& direction_, int radius_, int grid_size_)
	{
		coord_def result_ = you.position;
		if(direction_.x)
		{
			result_.x = direction_.x < 0?radius_+2:DG_MAX_X-radius_-3;
			result_.y += rand_int(-grid_size_/2,grid_size_/2);
		}
		else if(direction_.y)
		{
			result_.y = direction_.y < 0?radius_+2:DG_MAX_Y-radius_-3;
			result_.x += rand_int(-grid_size_/2,grid_size_/2);
		}
		result_.x = max(radius_+2,min(DG_MAX_X-radius_-3,result_.x));
		result_.y = max(radius_+2,min(DG_MAX_Y-radius_-3,result_.y));
		return result_;
	}

	int get_scarlet_under_room_direction_value(const coord_def& direction_)
	{
		if(direction_.x < 0)
			return 1;
		if(direction_.x > 0)
			return 2;
		if(direction_.y < 0)
			return 3;
		return 4;
	}

	coord_def get_scarlet_under_room_direction(int value_)
	{
		switch(value_)
		{
		case 1:
			return coord_def(-1,0);
		case 2:
			return coord_def(1,0);
		case 3:
			return coord_def(0,-1);
		default:
			return coord_def(0,1);
		}
	}

	bool is_scarlet_under_room_ahead(const coord_def& center_, const coord_def& direction_, int distance_)
	{
		if(direction_.x < 0)
			return you.position.x-center_.x >= distance_;
		if(direction_.x > 0)
			return center_.x-you.position.x >= distance_;
		if(direction_.y < 0)
			return you.position.y-center_.y >= distance_;
		return center_.y-you.position.y >= distance_;
	}

	bool make_scarlet_under_room(int num, events* controller_, const coord_def& direction_,
		int grid_size_, int min_distance_)
	{
		bool rune_complete_ = you.rune[RUNE_SCARLET_UNDER];
		bool flan_complete_ = is_exist_named(MON_FLAN);
		if(rune_complete_ && flan_complete_)
			return false;

		const int radius_ = 10;
		coord_def center_ = get_scarlet_under_room_position(direction_,radius_,grid_size_);
		coord_def world_center_ = center_+controller_->position;
		int center_min_distance_ = min_distance_+radius_;
		if(min_distance_ > 0 &&
			distan_coord(world_center_,coord_def(0,0)) <= center_min_distance_*center_min_distance_)
			return false;
		env[num].MakeEvent(EVL_SCARLET_UNDER_REWARD,center_,EVT_ALWAYS,-1,
			get_scarlet_under_room_direction_value(direction_));
		return true;
	}
}

void map_algorithms_scarlet_under(int num, dungeon_tile_type floor_tex_, dungeon_tile_type wall_tex_,
	int corridor_width_, int grid_size_, int bend_frequency_, int exit_frequency_, int afterimage_count_)
{
	int seed_ = (randA(1000000000)+1)*2;
	coord_def origin_(-DG_MAX_X/2,-DG_MAX_Y/2);
	for(int x_=0;x_<DG_MAX_X;x_++)
	{
		for(int y_=0;y_<DG_MAX_Y;y_++)
		{
			env[num].dgtile[x_][y_].init();
			env[num].dgtile[x_][y_].tile = scarlet_under_tile(x_+origin_.x,y_+origin_.y,
				floor_tex_,wall_tex_,corridor_width_,grid_size_,bend_frequency_,exit_frequency_,seed_/2);
		}
	}

	coord_def center_(DG_MAX_X/2,DG_MAX_Y/2);
	env[num].stair_up[0] = center_;
	env[num].dgtile[center_.x][center_.y].tile = DG_RETURN_STAIR;
	env[num].MakeEvent(21,center_,EVT_SIGHT);
	env[num].MakeEvent(EVL_SCARLET_UNDER,origin_,EVT_ALWAYS,-1,seed_);
	env[num].MakeEvent(EVL_SCARLET_UNDER_FRONTIER,
		coord_def(origin_.x,origin_.x+DG_MAX_X-1),EVT_ALWAYS,
		origin_.y,origin_.y+DG_MAX_Y-1);

	for(int i=0;i<afterimage_count_;i++)
	{
		for(int retry_=0;retry_<100;retry_++)
		{
			coord_def pos_(rand_int(5,DG_MAX_X-6),rand_int(5,DG_MAX_Y-6));
			if(distan_coord(pos_,center_) > 10*10 &&
				env[num].dgtile[pos_.x][pos_.y].tile == floor_tex_ &&
				!env[num].isMonsterPos(pos_.x,pos_.y))
			{
				make_scarlet_under_monster(num,pos_);
				break;
			}
		}
	}
	setBaseFloorWall(num,floor_tex_,wall_tex_);
}

void scarlet_under_count(int num, events* controller_, dungeon_tile_type floor_tex_, dungeon_tile_type wall_tex_,
	int corridor_width_, int grid_size_, int bend_frequency_, int exit_frequency_, int rune_exit_frequency_,
	int room_frequency_, int room_min_distance_, int monster_frequency_)
{
	controller_->count--;
	coord_def offset_(0,0);
	if(you.position.x<8 || you.position.x>DG_MAX_X-9)
		offset_.x = DG_MAX_X/2-you.position.x;
	if(you.position.y<8 || you.position.y>DG_MAX_Y-9)
		offset_.y = DG_MAX_Y/2-you.position.y;
	if(!offset_.x && !offset_.y)
		return;

	WaitForSingleObject(mutx,INFINITE);
	dungeon_tile temp_tile_[DG_MAX_X][DG_MAX_Y];
	for(int x_=0;x_<DG_MAX_X;x_++)
		for(int y_=0;y_<DG_MAX_Y;y_++)
			temp_tile_[x_][y_] = env[num].dgtile[x_][y_];

	coord_def frontier_direction_;
	bool new_frontier_ = extend_scarlet_under_frontier(num,controller_,offset_,frontier_direction_);
	controller_->position -= offset_;
	int seed_ = controller_->value/2;
	int current_exit_frequency_ = you.rune[RUNE_SCARLET_UNDER]?rune_exit_frequency_:exit_frequency_;
	vector<coord_def> new_floor_;
	for(int x_=0;x_<DG_MAX_X;x_++)
	{
		for(int y_=0;y_<DG_MAX_Y;y_++)
		{
			if(offset_.x > x_ || offset_.x <= x_-DG_MAX_X || offset_.y > y_ || offset_.y <= y_-DG_MAX_Y)
			{
				env[num].dgtile[x_][y_].init();
				env[num].dgtile[x_][y_].tile = scarlet_under_tile(x_+controller_->position.x,y_+controller_->position.y,
					floor_tex_,wall_tex_,corridor_width_,grid_size_,bend_frequency_,current_exit_frequency_,seed_);
				if(env[num].dgtile[x_][y_].isMove(false,false,false))
					new_floor_.push_back(coord_def(x_,y_));
			}
			else
			{
				int old_x_ = x_-offset_.x;
				int old_y_ = y_-offset_.y;
				env[num].dgtile[x_][y_] = temp_tile_[old_x_][old_y_];
			}
		}
	}

	you.offsetmove(offset_);
	if(you.s_dimension)
	{
		you.god_value[GT_YUKARI][0] += offset_.x;
		you.god_value[GT_YUKARI][1] += offset_.y;
	}
	for(monster& mon_ : env[num].mon_vector)
	{
		if(!mon_.isLive())
			continue;
		coord_def next_ = mon_.position+offset_;
		if(mon_.id == MON_FLAN && !in_scarlet_under_map(next_))
			unset_exist_named(MON_FLAN);
		mon_.offsetmove(offset_);
	}
	for(smoke& smoke_ : env[num].smoke_list)
		smoke_.offsetmove(offset_);
	for(auto it_=env[num].item_list.begin();it_!=env[num].item_list.end();)
	{
		item* item_ = &(*it_++);
		item_->offsetmove(offset_);
	}
	for(floor_effect& floor_ : env[num].floor_list)
		floor_.offsetmove(offset_);
	for(events& event_ : env[num].event_list)
	{
		if(&event_ == controller_ || event_.id == EVL_SCARLET_UNDER_FRONTIER)
			continue;
		event_.position += offset_;
		if(!in_scarlet_under_map(event_.position))
		{
			event_.id = 24;
			event_.type = EVT_ALWAYS;
		}
	}
	if(new_frontier_)
	{
		for(events& event_ : env[num].event_list)
		{
			if(event_.id != EVL_SCARLET_UNDER_REWARD)
				continue;
			coord_def direction_ = get_scarlet_under_room_direction(event_.value);
			if(event_.count == -2 || !is_scarlet_under_room_ahead(event_.position,direction_,17))
			{
				event_.position = get_scarlet_under_room_position(frontier_direction_,10,grid_size_);
				event_.value = get_scarlet_under_room_direction_value(frontier_direction_);
				event_.count = -1;
			}
		}
	}
	for(int i=0;i<3;i++)
	{
		env[num].stair_up[i] += offset_;
		env[num].stair_down[i] += offset_;
		if(!in_scarlet_under_map(env[num].stair_up[i]))
			env[num].stair_up[i] = coord_def(0,0);
		if(!in_scarlet_under_map(env[num].stair_down[i]))
			env[num].stair_down[i] = coord_def(0,0);
	}
	for(auto it_=env[num].stair_vector.begin();it_!=env[num].stair_vector.end();)
	{
		it_->pos += offset_;
		if(!in_scarlet_under_map(it_->pos))
			it_ = env[num].stair_vector.erase(it_);
		else
			it_++;
	}

	env[num].ClearAllShadow();
	env[num].afterimage_list.clear();
	env[num].ClearEffect();
	env[num].ClearForbid();
	bool room_created_ = false;
	if(new_frontier_ && !has_scarlet_under_room(num) && room_frequency_ > 0 && randA(room_frequency_-1) == 0)
		room_created_ = make_scarlet_under_room(num,controller_,frontier_direction_,grid_size_,room_min_distance_);
	for(const coord_def& pos_ : new_floor_)
	{
		if(!room_created_ && env[num].dgtile[pos_.x][pos_.y].tile == floor_tex_ &&
			monster_frequency_ > 0 && randA(monster_frequency_-1) == 0 &&
			!env[num].isMonsterPos(pos_.x,pos_.y))
			make_scarlet_under_monster(num,pos_);
	}
	env[num].allCalculateAutoTile();
	ReleaseMutex(mutx);
}

int get_scarlet_under_penalty_turn(int num)
{
	for(events& event_ : env[num].event_list)
		if(event_.id == EVL_SCARLET_UNDER)
			return max(0,-event_.count-1);
	return 0;
}

bool scarlet_under_reward(events* event_)
{
	events* controller_ = NULL;
	for(events& check_ : env[current_level].event_list)
		if(check_.id == EVL_SCARLET_UNDER)
		{
			controller_ = &check_;
			break;
		}
	if(!controller_)
		return true;

	const int room_radius_ = 10;
	coord_def room_direction_ = get_scarlet_under_room_direction(event_->value);
	if(!is_scarlet_under_room_ahead(event_->position,room_direction_,room_radius_+7))
	{
		event_->count = -2;
		return false;
	}
	bool discovered_ = false;
	for(int x_ = event_->position.x-room_radius_; x_ <= event_->position.x+room_radius_ && !discovered_; x_++)
	{
		for(int y_ = event_->position.y-room_radius_; y_ <= event_->position.y+room_radius_; y_++)
		{
			coord_def pos_(x_,y_);
			if(in_scarlet_under_map(pos_) &&
				distan_coord(pos_,event_->position) <= room_radius_*room_radius_ &&
				env[current_level].isInSight(pos_))
			{
				discovered_ = true;
				break;
			}
		}
	}
	if(!discovered_)
		return false;

	for(int x_ = event_->position.x-room_radius_; x_ <= event_->position.x+room_radius_; x_++)
	{
		for(int y_ = event_->position.y-room_radius_; y_ <= event_->position.y+room_radius_; y_++)
		{
			coord_def pos_(x_,y_);
			if(in_scarlet_under_map(pos_) &&
				distan_coord(pos_,event_->position) <= room_radius_*room_radius_)
			{
				env[current_level].dgtile[x_][y_].init();
				env[current_level].dgtile[x_][y_].tile = DG_CARPET;
			}
		}
	}
	env[current_level].allCalculateAutoTile();

	if(!is_exist_named(MON_FLAN))
	{
		monster* flan_ = NULL;
		coord_def flan_pos_ = event_->position+coord_def(0,-3);
		for(int radius_=0;radius_<=4 && !flan_;radius_++)
		{
			for(int x_=-radius_;x_<=radius_ && !flan_;x_++)
			{
				for(int y_=-radius_;y_<=radius_;y_++)
				{
					if(max(abs(x_),abs(y_)) != radius_)
						continue;
					coord_def pos_ = flan_pos_+coord_def(x_,y_);
					if(!in_scarlet_under_map(pos_) || pos_ == you.position ||
						env[current_level].dgtile[pos_.x][pos_.y].tile != DG_CARPET ||
						!env[current_level].isMove(pos_,false) || env[current_level].isMonsterPos(pos_.x,pos_.y))
						continue;
					flan_ = env[current_level].AddMonster(MON_FLAN,M_FLAG_WAKE,pos_);
					if(flan_)
					{
						flan_->SetStrong(5);
						flan_->state.SetState(MS_NORMAL);
						set_exist_named(MON_FLAN);
					}
					break;
				}
			}
		}
		if(!flan_)
			return false;
	}

	if(!you.rune[RUNE_SCARLET_UNDER])
	{
		item_infor rune_;
		makeitem(ITM_GOAL,0,&rune_,RUNE_SCARLET_UNDER);
		env[current_level].MakeItem(event_->position,rune_);
	}

	if(controller_->value&1)
		return true;
	controller_->value |= 1;

	const int item_radius_ = 7;
	set<coord_def> used_;
	int item_count_ = 15;
	for(int i=0;i<item_count_;i++)
	{
		for(int retry_=0;retry_<100;retry_++)
		{
			coord_def pos_ = event_->position+coord_def(rand_int(-item_radius_,item_radius_),rand_int(-item_radius_,item_radius_));
			if(!in_scarlet_under_map(pos_) ||
				pos_ == event_->position ||
				distan_coord(pos_,event_->position) > item_radius_*item_radius_ ||
				env[current_level].dgtile[pos_.x][pos_.y].tile != DG_CARPET ||
				!env[current_level].isMove(pos_,false) || used_.find(pos_) != used_.end())
				continue;
			item_infor item_;
			if(!env[current_level].MakeItem(pos_,CreateFloorItem(SCARLET_UNDER_LEVEL_LAST_LEVEL,&item_)))
				continue;
			used_.insert(pos_);
			break;
		}
	}
	return true;
}
