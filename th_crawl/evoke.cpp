//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: evoke.cpp
//
// 내용: 발동템들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "evoke.h"
#include "skill_use.h"
#include "projectile.h"
#include "environment.h"
#include "throw.h"


const char *evoke_string[EVK_MAX]=
{
	"보탑",
	"에어두루마리",
	"몽혼"
};
const bool evoke_string_is[EVK_MAX]=
{
	true,
	false,
	true
};


void MakeEvokeItem(item_infor* t, int kind_)
{	
	if(kind_ == -1 || (kind_<0 && kind_>=EVK_MAX))
		kind_= randA(EVK_MAX-1);

	t->value1 = kind_;
	t->value2 = 0;
	t->value3 = 0;
	t->value4 = 0;
	t->value5 = 0;
	t->value6 = 0;
	t->is_pile = false;
	t->can_throw = false;
	t->image = &img_mons_default;
	t->name.name = evoke_string[kind_];
	t->name.name_type = evoke_string_is[kind_];
	t->weight = 1.0f;
	t->value = 300;
}






bool EvokeFlagCheck(evoke_kind skill, skill_flag flag);
int EvokeLength(evoke_kind skill);
float EvokeSector(evoke_kind skill);
bool EvokeEvokable(evoke_kind kind, bool short_, coord_def &target);



bool evoke_evokable(evoke_kind kind)
{
	if(you.s_confuse)
	{
		printlog("당신은 혼란스럽다.",true,false,false,CL_normal);
		return false;
	}

	if(you.power < Evokeusepower(kind,true))
	{
		printlog("발동하기엔 당신의 P가 모자란다.",true,false,false,CL_small_danger);	
		return false;
	}



	int i=0;
	if(EvokeFlagCheck(kind, S_FLAG_DIREC))
	{
		SetSpellSight(EvokeLength(kind),EvokeFlagCheck(kind, S_FLAG_RECT)?2:1);
		coord_def target_;
		if(Direc_Throw(&target_))
		{
			if(EvokeEvokable(kind, false, target_))
			{
				you.PowUpDown(-1* Evokeusepower(kind,false),true);
				return true;
			}
		}
		else
		{
			return false;
		}

	}
	else if(!EvokeFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		SetSpellSight(EvokeLength(kind),EvokeFlagCheck(kind, S_FLAG_RECT)?2:1);
		beam_iterator beam(you.position,you.position);
		projectile_infor infor(EvokeLength(kind),false,EvokeFlagCheck(kind, S_FLAG_SMITE),-2,false);
		if(int short_ = Common_Throw(you.item_list.end(), you.GetTargetIter(), beam, &infor, EvokeLength(kind), EvokeSector(kind)))
		{
			unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
			you.SetBattleCount(30);
			if(unit_)
				you.youAttack(unit_);
			if(EvokeEvokable(kind, short_ == 2, you.search_pos))
			{
				you.PowUpDown(-1* Evokeusepower(kind,false),true);
				SetSpellSight(0,0);
				return true;
			}
		}
		else
		{
			SetSpellSight(0,0);
			return false;
		}
	}			
	else if(EvokeFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		if(EvokeEvokable(kind, false, you.position))
		{
			you.PowUpDown(-1* Evokeusepower(kind,false),true);
			return true;
		}
	}
	return false;
}

int Evokeusepower(evoke_kind skill, bool max_)
{
	switch(skill)
	{
	case EVK_PAGODA:
		return 10;
	case EVK_AIR_SCROLL:
		return 50;
	case EVK_DREAM_SOUL:
		return 50;
	default:
		return false;
	}
}


bool EvokeFlagCheck(evoke_kind skill, skill_flag flag)
{
	switch(skill)
	{
	case EVK_PAGODA:
		return (S_FLAG_PENETRATE) & flag;
	case EVK_AIR_SCROLL:
	case EVK_DREAM_SOUL:
		return (S_FLAG_IMMEDIATELY) & flag;
	default:
		return false;
	}
}

int EvokeLength(evoke_kind skill)
{
	switch(skill)
	{
	case EVK_PAGODA:
		return 8;
	case EVK_AIR_SCROLL:
	case EVK_DREAM_SOUL:
		return 0;
	default:
		return false;
	}
}
float EvokeSector(evoke_kind skill)
{
	switch(skill)
	{
	case 0:
	default:
		return 0;
	}
}
string DreamSoulMonster(vector<int>& list_, int level_);



bool EvokeEvokable(evoke_kind kind, bool short_, coord_def &target)
{
	if(target == you.position && !EvokeFlagCheck(kind,S_FLAG_SEIF) && !EvokeFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		printlog("자살할거야?",true,false,false,CL_small_danger);	
		return false;
	}
	int level_ = you.skill[SKT_EVOCATE].level;

	
	switch(kind)
	{
	case EVK_PAGODA:
		{
			beam_iterator beam(you.position,target);
			if(CheckThrowPath(you.position,target,beam)){
				beam_infor temp_infor(randC(3,4+level_*2/3),3*(4+level_*2/3),16,&you,you.GetParentType(),EvokeLength(kind),8,BMT_PENETRATE,ATT_THROW_NORMAL,name_infor("레이저",false));
				if(short_)
					temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));
				
				for(int i=0;i<(you.GetParadox()?2:1);i++)
					throwtanmac(rand_int(10,15),beam,temp_infor,NULL);
				you.SetParadox(0); 
				return true;
			}
			return false;	
		}	
	case EVK_AIR_SCROLL:
		{
			printlog("에어두루마리로부터 영력을 얻었다!",false,false,false,CL_normal);
			you.MpUpDown(8+level_/3+randA(3+level_/3));
			//발동0 8~11에서 발동만렙 17~29
			return true;
		}
	case EVK_DREAM_SOUL:
		{
			vector<int> mon_list;
			string s_ =	DreamSoulMonster(mon_list,level_);
			for(auto it = mon_list.begin(); it != mon_list.end(); it++)
			{
				if(BaseSummon((*it), rand_int(50,60), true, false, 2, &you, you.position, SKD_OTHER, -1))
				{

				}
			}
			printarray(true,false,false,CL_normal,3,"당신은 ",s_.c_str(),"의 꿈을 불러냈다!");
			return true;
		}
	}
	return false;
}






string DreamSoulMonster(vector<int>& list_, int level_)
{
	random_extraction<int> branch_list_;
	string msg_;
	if(level_>=0)
		branch_list_.push(0);//요정
	if(level_>=0)
		branch_list_.push(1);//요괴의산
	if(level_>=6)
		branch_list_.push(2);//홍마관
	if(level_>=0)
		branch_list_.push(3);//윳쿠리
	if(level_>=0)
		branch_list_.push(4);//미궁의죽림
	if(level_>=0)
		branch_list_.push(5);//지저
	if(level_>=6)
		branch_list_.push(6);//마계

	int branch_ = branch_list_.pop();


	random_extraction<int> mon_list_;

	int num_ = rand_int(1,3)+randA(level_/13);

	if(num_ == 1)
		level_ = min(27,level_ + 5);


	switch(branch_)
	{
	case 0: //요정
		if(level_<=3)
			mon_list_.push(MON_FAIRY_GREEN,4);
		if(level_<=5)
			mon_list_.push(MON_FAIRY_BLUE,9);
		if(level_<=7)
			mon_list_.push(MON_FAIRY_RED,15);
		if(level_>5 && level_<=15)
			mon_list_.push(MON_FAIRY_GREEN_WARRIOR,15);
		if(level_>7 && level_<=18)
			mon_list_.push(MON_FAIRY_BLUE_MAGICIAN,10);
		if(level_>9 && level_<=21)
			mon_list_.push(MON_FAIRY_RED_COMMANDER,5);
		if(level_>15)
			mon_list_.push(MON_FAIRY_HERO,15);
		if(level_>18)
			mon_list_.push(MON_FAIRY_SOCERER,15);
		if(level_>21)
			mon_list_.push(MON_FAIRY_SUN_FLOWER,5);
		msg_ = "안개의 호수";
		break;
	case 1: //요괴산
		if(level_<=6)
			mon_list_.push(MON_CROW,6);
		if(level_<=13)
			mon_list_.push(MON_KATPA,18);
		if(level_>6 && level_<=15)
			mon_list_.push(MON_FROG,6);
		if(level_>9 && level_<=25)
			mon_list_.push(MON_KATPA_SPEAR,10);
		if(level_>11)
			mon_list_.push(MON_CROW_TENGU,15);
		if(level_>13)
			mon_list_.push(MON_KATPA_WATER_WIZARD,7);
		if(level_>15)
			mon_list_.push(MON_YAMABUSH_TENGU,10);
		if(level_>18)
			mon_list_.push(MON_HANATACA_TENGU,10);
		if(level_>21)
			mon_list_.push(MON_SANPEI_FIGHTER,3);
		msg_ = "요괴의 산";
		break;
	case 2: //홍마관
		if(level_<=13)
			mon_list_.push(MON_HOBGOBRIN,15);
		if(level_<=16)
			mon_list_.push(MON_MAID_FAIRY,8);
		if(level_>9 && level_<=19)
			mon_list_.push(MON_HOBGOBRIN_MAID,10);
		if(level_>13 && level_<=24)
			mon_list_.push(MON_MAGIC_BOOK,8);
		if(level_>16)
			mon_list_.push(MON_HOBGOBRIN_LIBRARIAN,6);
		if(level_>18)
			mon_list_.push(MON_VAMPIER_BAT,10);			
		if(level_>21)
			mon_list_.push(MON_CHUPARCABRA,3);
		msg_ = "홍마관";
		break;
	case 3: //윳쿠리
		if(level_<=9)
			mon_list_.push(MON_REIMUYUKKURI,15);
		if(level_<=16)
			mon_list_.push(MON_MARISAYUKKURI,10);
		if(level_>9 && level_<=24)
			mon_list_.push(MON_AYAYUKKURI,8);
		if(level_>16)
			mon_list_.push(MON_REMILIAYUKKURI,6);
		if(level_>19)
			mon_list_.push(MON_YOUMUYUKKURI,2);
		if(level_>21)
			mon_list_.push(MON_ALICEYUKKURI,2);
		msg_ = "윳쿠리 둥지";
		break;
	case 4: //죽림
		if(level_<=12)
			mon_list_.push(MON_RABBIT,10);
		if(level_>6)
			mon_list_.push(MON_RABIT_SPEAR,5);
		if(level_>9)
			mon_list_.push(MON_RABIT_SPEAR,15);
		if(level_>12)
			mon_list_.push(MON_RABIT_SUPPORT,3);
		if(level_>15)
			mon_list_.push(MON_RABIT_MAGIC,10);
		msg_ = "미궁의 죽림";
		break;
	case 5: //지저
		if(level_<=8)
			mon_list_.push(MON_CROW,6);
		if(level_<=13)
			mon_list_.push(MON_HAUNT,10);
		if(level_>8 && level_<=15)
			mon_list_.push(randA(2)?(randA(1)?MON_WHITE_CAT:MON_BLACK_CAT):MON_ORANGE_CAT,10);
		if(level_>11 && level_<=18)
			mon_list_.push(MON_HELL_CROW,10);
		if(level_>14)
			mon_list_.push(MON_BLOOD_HAUNT,5);
		if(level_>15)
			mon_list_.push(MON_HELL_SPIDER, 10);
		if(level_>18)
			mon_list_.push(randA(1)?MON_ONI:MON_BLUE_ONI,8);
		if(level_>24)
			mon_list_.push(MON_FIRE_CAR,3);				
		msg_ = "지저";
		break;
	case 6: //마계
		if(level_<=12)
			mon_list_.push(MON_EVIL_EYE,10);
		if(level_<=10)
			mon_list_.push(MON_LITTLE_IMP,10);
		if(level_>8)				
			mon_list_.push(MON_SARA,15);
		if(level_>12)		
			mon_list_.push(MON_LUIZE,15);
		if(level_>13)		
			mon_list_.push(MON_ELIS,15);
		if(level_>21)		
			mon_list_.push(MON_YUKI,1);
		if(level_>21)
			mon_list_.push(MON_MAI,1);	
		if(level_>23)		
			mon_list_.push(MON_YUKI,3);
		if(level_>23)
			mon_list_.push(MON_MAI,3);		
		msg_ = "마계";
		break;
	}


	
	for(int i = num_; i > 0; i--)
		list_.push_back(mon_list_.choice());
	return msg_;
}