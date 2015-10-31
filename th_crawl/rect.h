//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: rect.h
//
// 내용: 사각형 반복자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __RECT_H__
#define  __RECT_H__

#include "common.h"
#include "enum.h"

class rect_iterator //원하는 사각형을 출력한다.
{
	coord_def start;
	coord_def current;
	int x_size;
	int y_size;

public:
	rect_iterator(const coord_def &start_, int x_size, int y_size);
	coord_def rect_iterator::operator *() const;
	const coord_def* rect_iterator::operator->() const;
	rect_iterator& operator ++ ();
	rect_iterator operator ++ (int);
	bool end();
	bool isdiagonal();
};



class rand_rect_iterator //특정 범위안을 무작위순서로 추출해낸다.
{
	coord_def start;
	int current;
	int x_size;
	int y_size;
	deque<coord_def> dq;

public:
	rand_rect_iterator(const coord_def &start_, int x_size, int y_size, bool no_inside = true);
	coord_def rand_rect_iterator::operator *() const;
	const coord_def* rand_rect_iterator::operator->() const;
	rand_rect_iterator& operator ++ ();
	rand_rect_iterator operator ++ (int);
	bool end() const; 
};


class dif_rect_iterator //특정 위치부터 점차 퍼지면서 무작위로 추출한다.
{
	coord_def start;
	int current;
	int distan; //중앙으로부터 거리
	deque<coord_def> dq;

public:
	dif_rect_iterator(const coord_def &start_, int distan, bool random_ = false);
	void sort_distan(bool close_); //가까이있는 순서로 정렬
	coord_def dif_rect_iterator::operator *() const;
	const coord_def* dif_rect_iterator::operator->() const;
	dif_rect_iterator& operator ++ ();
	dif_rect_iterator operator ++ (int);
	bool end() const; 
};


#endif // __RECT_H__