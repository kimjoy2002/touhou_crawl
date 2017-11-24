//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: forbid.cpp
//
// 내용: 금지구역의 설정
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "forbid.h"
#include "environment.h"
#include "save.h"


void forbid::SaveDatas(FILE *fp)
{
	SaveData<int>(fp, position.x);
	SaveData<int>(fp, position.y);
	SaveData<bool>(fp, big);
	SaveData<bool>(fp, change);
	SaveData<int>(fp, stack.size());

	for (int i = stack.size(); i > 0; i--) {
		coord_def pop_ = stack.front();
		SaveData<int>(fp, pop_.x);
		SaveData<int>(fp, pop_.y);
		stack.pop_front();
	}
}
void forbid::LoadDatas(FILE *fp)
{
	LoadData<int>(fp, position.x);
	LoadData<int>(fp, position.y);
	LoadData<bool>(fp, big);
	LoadData<bool>(fp, change);
	int size_ = 0;
	LoadData<int>(fp, size_);

	for (int i = size_; i > 0; i--) {
		coord_def pop_;
		LoadData<int>(fp, pop_.x);
		LoadData<int>(fp, pop_.y);
		stack.push_back(pop_);
	}
}



void forbid::setChange(coord_def position_)
{
	if (!big) {
		if (position == position_)
			change = true;
	}
	else {
		if (distan_coord(position, position_) <= 8 * 8)
		{
			change = true;
		}
	}
}



void forbid::reset()
{
	if (change)
	{
		removeArea();
		if (!big) {
			env[current_level].MakeForbid(position, true, true);
		}
		else {
			env[current_level].MakeForbid(position, 8, true, stack);
		}
		change = false;
	}
}

void forbid::removeArea()
{
	if (!big) {
		env[current_level].MakeForbid(position, true, false);
	}
	else {
		while (!stack.empty()) {
			env[current_level].MakeForbid(stack.back(), stack.back() == position, false);
			stack.pop_back();
		}
	}
}