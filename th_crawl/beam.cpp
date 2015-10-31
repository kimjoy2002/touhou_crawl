//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: beam.cpp
//
// 내용: 직선 발사물 관련 함수,클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "beam.h"


const coord_def short_pos[8]= {
	coord_def(-1,-1),
	coord_def(0,-1),
	coord_def(1,-1),
	coord_def(1,0),
	coord_def(1,1),
	coord_def(0,1),
	coord_def(-1,1),
	coord_def(-1,0)
};


beam_iterator::beam_iterator(const coord_def &start_,const coord_def &target_, round_type type_)
{
	start = start_;
	target = target_;
	max_length = max(abs(start.x-target.x),abs(start.y-target.y));
	//max_length = sqrt(pow((float)abs(start.x-target.x),2)+pow((float)abs(start.y-target.y),2));	
	cur_length = 1;
	x_step = (float)(target.x-start.x+0.0001f)*cur_length/max_length;
	y_step = (float)(target.y-start.y+0.0001f)*cur_length/max_length;
	x = start.x + x_step;
	y = start.y + y_step;
	type = type_;
	SetCurrent(type);
}


void beam_iterator::SetCurrent(round_type type)
{
	current.x = (type==RT_FLOOR?floor(x):(type==RT_ROUND_DOWN?round_down(x):(type==RT_ROUND?round(x):(type==RT_ROUND_UP?round_up(x):ceil_up(x)))));
	current.y = (type==RT_FLOOR?floor(y):(type==RT_ROUND_DOWN?round_down(y):(type==RT_ROUND?round(y):(type==RT_ROUND_UP?round_up(y):ceil_up(y)))));
}


coord_def beam_iterator::operator *() const
{
    return current;
}
const coord_def* beam_iterator::operator->() const
{
    return &current;
}
beam_iterator& beam_iterator::operator ++()
{
	cur_length++;
	x += x_step;
	y += y_step;
	SetCurrent(type);
    return *this;
}
beam_iterator beam_iterator::operator++( int dummy )
{
    const beam_iterator copy = *this;
    ++(*this);
    return (copy);
}
void beam_iterator::init()
{
	cur_length = 1;
	x = start.x + x_step;
	y = start.y + y_step;
	SetCurrent(type);
}
coord_def beam_iterator::start_pos()
{
	return start;
}
int beam_iterator::GetDirec()
{
	return GetPosToDirec(start,target);
}
bool beam_iterator::end()
{
	return cur_length>=max_length;
}



close_beam_iterator::close_beam_iterator(const coord_def &start_,const coord_def &target_)
{
	start = start_;
	target = target_;
	
	if(target.y<start.y)
	{
		((target.x<start.x)?pos=0:((target.x==start.x)?pos=1:pos=2));
	}
	else if(target.y==start.y)
	{
		((target.x<start.x)?pos=7:((target.x==start.x)?pos=0:pos=3));
	}
	else
	{
		((target.x<start.x)?pos=6:((target.x==start.x)?pos=5:pos=4));
	}
	direc = (abs(target.x-start.x) > abs(target.y-start.y)) ^ (pos%4<=1);
	current = start_ + short_pos[pos];
	
	count = 0;
}
coord_def close_beam_iterator::operator *() const
{
    return current;
}
const coord_def* close_beam_iterator::operator->() const
{
    return &current;
}

close_beam_iterator& close_beam_iterator::operator ++()
{
	count++;
	if(count%2 == direc)
	{
		pos = LoopSelect(0,7,pos+count);
	}
	else
	{
		pos = LoopSelect(0,7,pos-count);
	}
	current = start + short_pos[pos];
    return *this;
}
close_beam_iterator close_beam_iterator::operator++( int dummy )
{
    const close_beam_iterator copy = *this;
    ++(*this);
    return (copy);
}
bool close_beam_iterator::end()
{
	return (count>2);
}