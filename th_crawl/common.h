
#ifndef  __COMMON_H__
#define  __COMMON_H__


#include <crtdbg.h> 
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

float rand_float(float min, float max);

int rand_int(int min, int max);

float GetPositionToAngle(float start_x, float start_y, float target_x, float target_y);

float GetPositionToAngle2(float start_x, float start_y, float target_x, float target_y);

float GetBaseAngle(float angle);

int GetPosToDirec(const coord_def &start, const coord_def &target);
int GetAngleToDirec(int angle);

float GetPositionGap(float start_x, float start_y, float target_x, float target_y);

float GetMaxX();

float GetMaxY();

float GetCenterX();

float GetCenterY();

float round(float x);

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

    int distance_from(const coord_def &b) const;

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

int distan_coord(const coord_def& a, const coord_def& b);


//윈도우 정보
const int WindowWidth = 800;
const int WindowHeight = 600;

#endif // __COMMON_H__