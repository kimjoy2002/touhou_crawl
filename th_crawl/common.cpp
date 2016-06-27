

#include "common.h"


extern POINT MousePoint;

unsigned int random_number = 10;

int LoopSelect(int min, int max, int cur)
{
	if(min	> max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	else if(min == max)
		return min;

	while(!(min <= cur && cur <= max))
	{
		if(cur < min)
			cur+= max-min+1;
		else
			cur-= max-min+1;
	}
	return cur;
}

int CutSelect(int min, int max, int cur)
{
	if(min	> max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	else if(min == max)
		return min;

	return ((cur>max)?max:((cur<min)?min:cur));

}
float rand_float(float min, float max)
{
	if(min == max)
		return min;

	if(min > max)
	{
		float temp = min;
		min = max;
		max = temp;
	}
	//min = (float)(random_number % (int)((max - min)*100 + 1)) /100 + min;
	//random_number = (((random_number*214013L + 2531011L)>>16)&0x7fff);
	min = (float)(rand() % (int)((max - min)*100 + 1)) /100 + min;

	return min;
}

int rand_int(int min, int max)
{
	if(min == max)
		return min;

	if(min > max)
	{
		int temp = min;
		min = max;
		max = temp;
	}
	//min = (random_number % (max - min+1)) + min;

	//random_number = (((random_number*214013L + 2531011L)>>16)&0x7fff);
	min = (rand() % (max - min+1)) + min;


	return min;
}

float GetPositionToAngle(float start_x, float start_y, float target_x, float target_y)
{
	return atan2(target_y - start_y, target_x - start_x) * 180 / D3DX_PI;

}

float GetPositionToAngle2(float start_x, float start_y, float target_x, float target_y)
{
	return atan2(target_y - start_y, target_x - start_x);

}

float GetBaseAngle(float angle)
{
	while(angle <= 0 || angle > 360)
	{
		if(angle <= 0)
			angle += 360;
		if(angle > 360)
			angle -= 360;
	}
	return angle;
}
int GetPosToDirec(const coord_def &start, const coord_def &target)
{
	coord_def c = target-start;
	if(c.abs()<=2)
	{
		switch((c.x+1)*10+c.y+1)
		{
		case 00:
			return 7;
		case 10:
			return 0;
		case 20:
			return 1;
		case 01:
			return 6;
		case 11:
			return 0;
		case 21:
			return 2;
		case 02:
			return 5;
		case 12:
			return 4;
		case 22:
			return 3;
		}
	}
	int angle = (int) GetPositionToAngle(start.x,start.y,target.x,target.y);
	angle = (angle+360)%360;
	return GetAngleToDirec(angle);
}
int GetAngleToDirec(int angle)
{
	if(angle>=22 && angle <67)
		return 3;
	else if(angle>=67 && angle < 112)
		return 4;
	else if(angle>=112 && angle < 157)
		return 5;
	else if(angle>=157 && angle < 202)
		return 6;
	else if(angle>=202 && angle < 247)
		return 7;
	else if(angle>=247 && angle < 292)
		return 0;
	else if(angle>=292 && angle < 337)
		return 1;
	else
		return 2;
}

float GetPositionGap(float start_x, float start_y, float target_x, float target_y)
{
	return sqrt((target_x - start_x)*(target_x - start_x)+ (target_y - start_y)*(target_y - start_y));

}

float GetMaxX()
{
	return (float)WindowWidth;
}

float GetMaxY()
{
	return (float)WindowHeight;
}

float GetCenterX()
{
	return (float)WindowWidth/2;
}

float GetCenterY()
{
	return (float)WindowHeight/2;
}

float round(float x)
{
   return ((x>0) ? floor(x+.5f) : ceil(x-.5f));
}
float round_down(float x)
{
   return ((x>0) ? floor(x+0.25f) : ceil(x-0.75f));
}
float round_up(float x)
{
   return ((x>0) ? floor(x+0.75f) : ceil(x-0.25f));
}
float ceil_up(float x)
{
   return ((x>0) ? floor(x+0.999f) : ceil(x-0.001f));
}
char asctonum(char a)
{
	return (a>='a'&&a<='z')?(a-'a'):((a>='A'&&a<='Z')?(a-'A'+26):0);
}

int randA(int x)
{
	if(x>0)
		return rand_int(0,x);
	else
		return 0;
}

int randA_1(int x)
{
	if(x>1)
		return rand_int(1,x);
	else
		return 1;
}


bool randB(int x, int point)
{
	return (randA(x) <= point);
}

int randC(int dice, int x)
{
	int a=0;
	for(int i=0;i<dice;i++)
		a += randA_1(x);
	return a;
}


int distan_coord(const coord_def& a, const coord_def& b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);

}