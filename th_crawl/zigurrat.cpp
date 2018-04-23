//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: zigurrat.cpp
//
// 내용: 지구랏
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "zigurrat.h"
#include "map.h"
#include "mon_infor.h"
#include "event.h"
#include "note.h"
#include "evoke.h"




void map_algorithms_zigurrat(int num)
{
	int size_x = 15, size_y = 7;


	for (int x = 0; x < DG_MAX_X; x++)
	{
		for (int y = 0; y < DG_MAX_Y; y++)
		{
			int x_ = x - DG_MAX_X / 2;
			int y_ = y - DG_MAX_Y / 2;
			if ((x_*x_) / (size_x*size_x) + (y_*y_) / (size_y*size_y) <= 1) {
				env[num].dgtile[x][y].tile = DG_DREAM_FLOOR;
			}
			else {
				env[num].dgtile[x][y].tile = DG_WALL2;
			}
		}
	}
	int x_ = DG_MAX_X / 2;
	int y_ = DG_MAX_Y / 2;

	env[num].stair_up[0].x = x_;
	env[num].stair_up[0].y = y_;
	env[num].dgtile[x_][y_].tile = DG_RETURN_STAIR;


}