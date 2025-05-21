
#ifndef  __COMMON_H__
#define  __COMMON_H__


#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <string>
#include <d3d11.h>
#include <time.h>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>
#include <math.h>
#include <set>
#include <DirectXMath.h>
#include <DirectXColors.h>
using namespace std;


#ifndef D3DCOLOR_DEFINED
#define D3DCOLOR_DEFINED
typedef uint32_t D3DCOLOR;

#define D3DCOLOR_RGBA(r,g,b,a) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

inline DirectX::XMVECTOR D3DCOLOR_to_XMVECTOR(D3DCOLOR c) {
    float r = ((c >> 16) & 0xFF) / 255.0f;
    float g = ((c >> 8)  & 0xFF) / 255.0f;
    float b = ((c >> 0)  & 0xFF) / 255.0f;
    float a = ((c >> 24) & 0xFF) / 255.0f;
    return DirectX::XMVectorSet(r, g, b, a);
}
#endif

struct coord_def;

int LoopSelect(int min, int max, int cur);
int CutSelect(int min, int max, int cur);


void rand_seed(unsigned int seed_);
void init_nonlogic_seed(unsigned int seed_);

void log_replay_event(const std::string& message);
void log_message(const char* file, int line, const std::string& message);
#define LOG_MESSAGE(message) log_message(__FILE__, __LINE__, (message))

void init_replay_log();
void log_key_input(const char* file, int line, const std::string& key_name);

#define LOG_KEY_INPUT(key_name) log_key_input(__FILE__, __LINE__, key_name)


float rand_float_impl(const char* file, int line, float min, float max);
#define rand_float(x, y) rand_float_impl(__FILE__, __LINE__, (x), (y))

int rand_int_impl(const char* file, int line, int min, int max);
#define rand_int(x, y) rand_int_impl(__FILE__, __LINE__, (x), (y))
int rand_int_with_nonlogic(int min, int max); //이 무작위는 게임에 영향을 주지않아야함



float GetPositionToAngle(float start_x, float start_y, float target_x, float target_y);

float GetPositionToAngle2(float start_x, float start_y, float target_x, float target_y);

float GetBaseAngle(float angle);

int GetPosToDirec(const coord_def &start, const coord_def &target);
coord_def GetDirecToPos(int pos_);
int GetDirecToChar(int pos_);
int GetAngleToDirec(int angle);

float GetPositionGap(float start_x, float start_y, float target_x, float target_y);
std::set<coord_def> get_forward_5_tiles(coord_def my_pos, coord_def target_pos, bool main_line);
float GetMaxX();

float GetMaxY();

float GetCenterX();

float GetCenterY();
//float round(float x);

float round_down(float x);

float round_up(float x);

float ceil_up(float x);

string float_to_string(float value, int precision = 3);

unsigned char asctonum(char a);
char numtoasc(int a);

int randA(int x); /*0부터 X까지의 랜덤난수 리턴*/

int randA_1(int x); /*1부터 X까지의 랜덤난수 리턴*/

int randA_nonlogic(int x); /*0부터 X까지의 랜덤난수 리턴*/
int randA_1_nonlogic(int x); /*1부터 X까지의 랜덤난수 리턴*/

bool randB(int x, int point); /*0부터 X가 point를 작거나같을때 true리턴*/

int randC(int dice, int x); /*(dice)d(x)*/

template<typename K, typename V>
class OrderedMap {
public:
    void insert(const K& key, const V& value) {
        if (map_.find(key) == map_.end()) {
            entries_.emplace_back(key, value);
            map_[key] = value;
        }
    }

    const std::vector<std::pair<K, V>>& ordered_entries() const {
        return entries_;
    }
    bool empty() {
        return map_.empty();
    }

    V find(const K& key) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            return it->second;
        }
        return V();
    }

private:
    std::vector<std::pair<K, V>> entries_;
    std::unordered_map<K, V> map_;
};



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

wstring ConvertUTF8ToUTF16(const string& utf8Str);
string ConvertUTF16ToUTF8(const wstring& utf16Str);

int PrintCharWidth(const wstring& text);
int PrintCharWidth(const string& text);
wstring PreserveTrailingSpaces(const wstring& text);
vector<string> SplitStringByFontWidth(const wstring& wtext, int firstLength, int nextLength);
vector<string> SplitStringByFontWidth(const string& text, int firstLength, int nextLength);

void replaceAll(string& str, const string& from, const string& to);
#endif // __COMMON_H__