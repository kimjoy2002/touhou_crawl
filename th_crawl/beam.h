//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: beam.h
//
// 내용: 직선 발사물 관련 함수,클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BEAM_H__
#define  __BEAM_H__

#include "common.h"
#include "enum.h"

class beam_iterator
{
	coord_def start;
	coord_def target;
	coord_def current;
	float x_step;
	float y_step;
	float x;
	float y;
	int max_length;
	int cur_length;
	round_type type;
	void SetCurrent(round_type type = RT_FLOOR);

public:
	beam_iterator(const coord_def &start_,const coord_def &target_, round_type type_ = RT_FLOOR);
	coord_def beam_iterator::operator *() const;
	const coord_def* beam_iterator::operator->() const;
	beam_iterator& operator ++ ();
	beam_iterator operator ++ (int);
	void init();
	coord_def start_pos();
	int GetDirec();
	int GetMaxLength(){return max_length;};
	int GetCurLength(){return cur_length;};
	float GetAngle(){
		return atan2((float)target.y-start.y, (float)target.x - start.x); 
	}
	bool end();
};


class close_beam_iterator
{
	coord_def start;
	coord_def target;
	coord_def current;
	char count;
	char pos;
	bool direc;

public:
	close_beam_iterator(const coord_def &start_,const coord_def &target_);
	coord_def close_beam_iterator::operator *() const;
	const coord_def* close_beam_iterator::operator->() const;
	close_beam_iterator& operator ++ ();
	close_beam_iterator operator ++ (int);
	bool end();
};





#endif // __BEAM_H__