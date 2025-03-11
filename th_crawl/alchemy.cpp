﻿//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: alchemy.cpp
//
// 내용: 연금술 관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "alchemy.h"
#include "player.h"
#include "skill_use.h"



bool players::SetAlchemyBuff(ALCHEMY_LIST buff_, int time_)
{
	if(buff_ == alchemy_buff)
	{
		alchemy_time += time_;
		if(Getalchemytime(buff_)<alchemy_time)
			alchemy_time = Getalchemytime(buff_);
		printlog("당신의 연금술에 의한 버프는 더욱 길어졌다.",false,false,false,CL_white_blue);
	}
	else
	{
		if(alchemy_time)
		{
			alchemyonoff(alchemy_buff,false);
			alchemy_buff = ALCT_NONE;
		}

		alchemy_time = time_;
		if(alchemy_time == 0)
			return false;
		alchemy_buff = buff_;
	
		alchemyonoff(alchemy_buff,true);
	}
	return true;
}
int Getalchemytime(ALCHEMY_LIST list_)
{	
	switch(list_)
	{
	case ALCT_NONE:
	default:
		break;
	case ALCT_STONE_FIST:		
		break;
	case ALCT_DIAMOND_HARDNESS:
		break;
	case ALCT_POISON_BODY:
		break;
	case ALCT_HASTE:
		break;
	case ALCT_STONE_FORM:
		break;
	case ALCT_AUTUMN_BLADE:
		break;
	case ALCT_PHILOSOPHERS_STONE:
		break;
	}
	return 100;
}

void alchemyalmostoff(ALCHEMY_LIST list_)
{	
	switch(list_)
	{
	case ALCT_NONE:
	default:
		break;
	case ALCT_STONE_FIST:		
		break;
	case ALCT_DIAMOND_HARDNESS:
		break;
	case ALCT_POISON_BODY:
		break;
	case ALCT_HASTE:
		if(you.s_haste < 10)
			printlog("속도가 돌아오고 있다.",false,false,false,CL_blue);
		break;
	case ALCT_STONE_FORM:
		printlog("무념무상의 경지가 끝나간다.",false,false,false,CL_blue);
		break;
	case ALCT_AUTUMN_BLADE:
		printlog("손에 감긴 연금술의 힘이 약해지고있다.",false,false,false,CL_blue);
		break;
	case ALCT_PHILOSOPHERS_STONE:
		printlog("현자의 돌은 거의 사라져가고있다.",false,false,false,CL_blue);
		break;
	}
}
void alchemyonoff(ALCHEMY_LIST list_,bool onoff_)
{
	switch(list_)
	{
	case ALCT_NONE:
	default:
		break;
	case ALCT_STONE_FIST:
		if(onoff_)
			printlog("당신의 주먹이 바위처럼 단단해졌다.",true,false,false,CL_white_blue);
		else
			printlog("당신의 주먹은 원래대로 돌아왔다.",false,false,false,CL_blue);
		break;
	case ALCT_DIAMOND_HARDNESS:
		you.UpDownBuff(BUFFSTAT_AC,5*(onoff_?1:-1));
		if(onoff_)
			printlog("당신의 몸은 바위처럼 단단해졌다.",true,false,false,CL_white_blue);
		else
			printlog("당신의 몸은 원래대로 돌아왔다.",false,false,false,CL_blue);
		break;
	case ALCT_POISON_BODY:
		if(onoff_)
			printlog("당신의 몸은 독 기운을 뿜어내기 시작했다.",true,false,false,CL_white_blue);
		else
			printlog("당신의 몸은 더이상 독을 뿜어내지 않는다.",false,false,false,CL_blue);
		break;
	case ALCT_HASTE:
		if(onoff_)
			printlog("당신의 연금술의 힘으로 빨라졌다.",true,false,false,CL_white_blue);
		else if(!you.s_haste)
			printlog("속도가 원래대로 돌아왔다 .",false,false,false,CL_blue);
		break;
	case ALCT_STONE_FORM:
		if(onoff_)
			printlog("당신은 무념무상의 경지에 이르렀다.",true,false,false,CL_white_blue);
		else
			printlog("당신의 무념무상의 경지는 끝났다.",false,false,false,CL_blue);
		break;
	case ALCT_AUTUMN_BLADE:
		if(onoff_)
			printlog("당신은 손에 톱니를 새겨넣었다.",true,false,false,CL_white_blue);
		else
			printlog("당신의 톱니는 사라졌다.",false,false,false,CL_blue);
		break;
	case ALCT_PHILOSOPHERS_STONE:
		you.Ability(SKL_PHILOSOPHERS_1,false,!onoff_);
		you.Ability(SKL_PHILOSOPHERS_2,false,!onoff_);
		you.Ability(SKL_PHILOSOPHERS_3,false,!onoff_);
		you.Ability(SKL_PHILOSOPHERS_4,false,!onoff_);
		you.Ability(SKL_PHILOSOPHERS_5,false,!onoff_);
		if(onoff_)
			printlog("당신은 현자의 돌을 연성해냈다. (a키로 추가 마법을 사용가능)",true,false,false,CL_white_blue);
		else
			printlog("당신의 현자의 돌은 이윽고 사라졌다.",false,false,false,CL_blue);
		break;

	}
}