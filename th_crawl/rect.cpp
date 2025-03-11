//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: rect.cpp
//
// 내용: 사각형 반복자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "rect.h"
#include "rand_shuffle.h"
#include <algorithm>



rect_iterator::rect_iterator(const coord_def &start_, int x_size_, int y_size_):
start(start_),current(start_.x-x_size_,start_.y-y_size_),x_size(x_size_),y_size(y_size_)
{}
coord_def rect_iterator::operator *() const
{
    return current;
}
const coord_def* rect_iterator::operator->() const
{
    return &current;
}
rect_iterator& rect_iterator::operator ++()
{
	current.x++;
	if(current.x>start.x+x_size)
	{
		current.x = start.x-x_size;
		current.y++;		
	}
    return *this;
}
rect_iterator rect_iterator::operator++( int dummy )
{
    const rect_iterator copy = *this;
    ++(*this);
    return (copy);
}
bool rect_iterator::end()
{
	return (current.y>start.y+y_size);
}
bool rect_iterator::isdiagonal()
{
	return (current.x != start.x && current.y != start.y);
}	




rand_rect_iterator::rand_rect_iterator(const coord_def &start_, int x_size_, int y_size_, bool no_inside):
start(start_),current(0),x_size(x_size_),y_size(y_size_)
{
	for(int i=-x_size; i<=x_size; i++)
	{
		for(int j=-y_size; j<=y_size; j++)
		{
			if(!no_inside || j != 0 || i != 0)
				dq.push_back(coord_def(i+start.x,j+start.y));
		}
	}
	rand_shuffle(dq.begin(),dq.end());
}
coord_def rand_rect_iterator::operator *() const
{
	if(!end())
	    return dq[current];
	else
		return coord_def(0,0);
}
const coord_def* rand_rect_iterator::operator->() const
{
	if(!end())
	    return &dq[current];
	else
		return &start;
}
rand_rect_iterator& rand_rect_iterator::operator ++()
{
	current++;
    return *this;
}
rand_rect_iterator rand_rect_iterator::operator++( int dummy )
{
    const rand_rect_iterator copy = *this;
    ++(*this);
    return (copy);
}
bool rand_rect_iterator::end() const
{
	return current == dq.size();
}





dif_rect_iterator::dif_rect_iterator(const coord_def &start_, int distan_, bool random_):
start(start_),current(0),distan(distan_)
{	
	deque<coord_def> temp;
	for(int i=-distan; i<=distan; i++)
	{
		for(int j=-distan; j<=distan; j++)
		{
			if(abs(i)+abs(j) != distan_*2 || distan_ == 0)
				temp.push_back(coord_def(i+start.x,j+start.y));
		}
	}
	rand_shuffle(temp.begin(),temp.end());
	for(unsigned int i=0;i<temp.size();i++)
		dq.push_back(temp[i]);
	if(!random_)
		sort_distan(true);
}
void dif_rect_iterator::sort_distan(bool close_)
{
	sort(dq.begin(), dq.end(),[&](const coord_def &lf, const coord_def &rf)
	{
		return close_?(lf-start).abs() < (rf-start).abs():(lf-start).abs()>(rf-start).abs();
	});
}
coord_def dif_rect_iterator::operator *() const
{
	if(!end())
	    return dq[current];
	else
		return coord_def(0,0);
}
const coord_def* dif_rect_iterator::operator->() const
{
	if(!end())
	    return &dq[current];
	else
		return &start;
}
dif_rect_iterator& dif_rect_iterator::operator ++()
{
	current++;
    return *this;
}
dif_rect_iterator dif_rect_iterator::operator++( int dummy )
{
    const dif_rect_iterator copy = *this;
    ++(*this);
    return (copy);
}
bool dif_rect_iterator::end() const
{
	return current == dq.size();
}