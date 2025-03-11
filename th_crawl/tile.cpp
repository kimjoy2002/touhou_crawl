//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: tile.cpp
//
// 내용: 타일관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"


dot_tile_type dungeon_tile::GetDot()
{
	switch(tile)
	{
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
		return DOT_FLOOR;
	case DG_WALL:
	case DG_GLASS:
	case DG_STATUE:
	case DG_STONE_WALL:
	case DG_RED_WALL:
	case DG_BOOK_WALL:
	case DG_BAMBOO_WALL:
	case DG_METAL_WALL:
	case DG_WALL2:
	case DG_WALL3:
	case DG_PANDE_WALL1:
	case DG_PANDE_WALL2:
	case DG_PANDE_WALL3:
	case DG_PANDE_WALL4:
	case DG_PANDE_WALL5:
	case DG_PANDE_WALL6:
	case DG_PANDE_WALL7:
	case DG_TREE:
	case DG_SUN_FLOWER:
	case DG_HELL_WALL:
		return DOT_WALL;
	case DG_CLOSE_DOOR:
	case DG_OPEN_DOOR:
		return DOT_DOOR;
	case DG_UP_STAIR:
	case DG_RETURN_STAIR:
		return DOT_UP;
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
		return DOT_DOWN;
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
		return DOT_TEMPLE;
	case DG_SEA:
	case DG_LAVA:
		return DOT_SEA;
	default:
		return DOT_FLOOR;
	}
}

