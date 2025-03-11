
#ifndef  __COMMON_H__
#define  __COMMON_H__


#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <d3dx9.h>
#include <time.h>
#include <vector>
#include <list>
#include <stack>
#include <math.h>
using namespace std;




struct coord_def;

int LoopSelect(int min, int max, int cur);
int CutSelect(int min, int max, int cur);



void rand_seed(unsigned int seed_);



float rand_float(float min, float max);

int rand_int(int min, int max);

float GetPositionToAngle(float start_x, float start_y, float target_x, float target_y);

float GetPositionToAngle2(float start_x, float start_y, float target_x, float target_y);

float GetBaseAngle(float angle);

int GetPosToDirec(const coord_def &start, const coord_def &target);
coord_def GetDirecToPos(int pos_);
int GetAngleToDirec(int angle);

float GetPositionGap(float start_x, float start_y, float target_x, float target_y);

float GetMaxX();

float GetMaxY();

float GetCenterX();

float GetCenterY();

//float round(float x);

float round_down(float x);

float round_up(float x);

float ceil_up(float x);

char asctonum(char a);

int randA(int x); /*0부터 X까지의 랜덤난수 리턴*/

int randA_1(int x); /*1부터 X까지의 랜덤난수 리턴*/

bool randB(int x, int point); /*0부터 X가 point를 작거나같을때 true리턴*/

int randC(int dice, int x); /*(dice)d(x)*/



struct coord_def
{
    int         x;
    int         y;

    explicit coord_def( int x_in = 0, int y_in = 0 ) : x(x_in), y(y_in) { }

    void set(int xi, int yi)
    {
        x = xi;
        y = yi;
    }

    void reset()
    {
        set(0, 0);
    }

    int distance_from(const coord_def &b) const
	{
		return max(std::abs(x-b.x),std::abs(y-b.y));
	}

    bool operator == (const coord_def &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator != (const coord_def &other) const
    {
        return !operator == (other);
    }

    bool operator <  (const coord_def &other) const
    {
        return (x < other.x) || (x == other.x && y < other.y);
    }

    bool operator >  (const coord_def &other) const
    {
        return (x > other.x) || (x == other.x && y > other.y);
    }

    const coord_def &operator += (const coord_def &other)
    {
        x += other.x;
        y += other.y;
        return (*this);
    }

    const coord_def &operator += (int offset)
    {
        x += offset;
        y += offset;
        return (*this);
    }

    const coord_def &operator -= (const coord_def &other)
    {
        x -= other.x;
        y -= other.y;
        return (*this);
    }

    const coord_def &operator -= (int offset)
    {
        x -= offset;
        y -= offset;
        return (*this);
    }

    const coord_def &operator /= (int div)
    {
        x /= div;
        y /= div;
        return (*this);
    }

    const coord_def &operator *= (int mul)
    {
        x *= mul;
        y *= mul;
        return (*this);
    }

    coord_def operator + (const coord_def &other) const
    {
        coord_def copy = *this;
        return (copy += other);
    }

    coord_def operator + (int other) const
    {
        coord_def copy = *this;
        return (copy += other);
    }

    coord_def operator - (const coord_def &other) const
    {
        coord_def copy = *this;
        return (copy -= other);
    }

    coord_def operator -() const
    {
        return (coord_def(0, 0) - *this);
    }

    coord_def operator - (int other) const
    {
        coord_def copy = *this;
        return (copy -= other);
    }

    coord_def operator / (int div) const
    {
        coord_def copy = *this;
        return (copy /= div);
    }

    coord_def operator * (int mul) const
    {
        coord_def copy = *this;
        return (copy *= mul);
    }

    int abs() const
    {
        return (x * x + y * y);
    }


    bool origin() const
    {
        return (!x && !y);
    }

    bool zero() const
    {
        return origin();
    }

    bool equals(const int xi, const int yi) const
    {
        return (xi == x && yi == y);
    }
};


template <typename T>
class random_extraction
{
	vector<T> value;
	vector<int> percent;
	int max_percent;

	
	T pop_base(bool pop_)
	{
		if(value.empty())
			return T();


		int per_ = randA(max_percent-1);
		auto it = value.begin();
		auto it2 = percent.begin();
		for(; it2 !=  percent.end() ;it++,it2++)
		{
			if(per_<(*it2))
			{
				T temp = (*it);
				if(pop_)
				{
					max_percent -= (*it2);
					value.erase(it);
					percent.erase(it2);
				}
				return temp;
			}
			else
			{
				per_-=(*it2);
			}
		}
		return value[0];
	}



public:
	random_extraction():max_percent(0){};
	
	int GetSize()
	{
		return value.size();
	}
	int GetMaxPercent()
	{
		return max_percent;
	}

	int push(T value_, int percent_ = 1) //하나를 넣으면서 
	{
		if(percent_<=0)
			return max_percent;
		value.push_back(value_);
		percent.push_back(percent_);
		max_percent+=percent_;
		return max_percent;
	}
	
	T pop() //하나를 꺼내면서 목록에서 제거
	{
		return pop_base(true);
	}
	
	T choice() //하나를 선택만 함
	{
		return pop_base(false);
	}

};





int distan_coord(const coord_def& a, const coord_def& b);



#endif // __COMMON_H__