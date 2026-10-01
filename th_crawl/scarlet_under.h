//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: scarlet_under.h
//
// 내용: 홍마관 지하실용 (무한 복도)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SCARLET_UNDER_H__
#define __SCARLET_UNDER_H__

#include "enum.h"

class events;

void map_algorithms_scarlet_under(int num, dungeon_tile_type floor_tex_, dungeon_tile_type wall_tex_,
	int corridor_width_, int grid_size_, int bend_frequency_, int exit_frequency_, int afterimage_count_);
void scarlet_under_count(int num, events* controller_, dungeon_tile_type floor_tex_, dungeon_tile_type wall_tex_,
	int corridor_width_, int grid_size_, int bend_frequency_, int exit_frequency_, int rune_exit_frequency_,
	int room_frequency_, int room_min_distance_, int monster_frequency_);
bool scarlet_under_reward(events* event_);
int get_scarlet_under_penalty_turn(int num);

#endif // __SCARLET_UNDER_H__
