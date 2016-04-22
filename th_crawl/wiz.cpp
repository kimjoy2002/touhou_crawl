//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: wiz.cpp
//
// 내용: 위자드모드!!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "smoke.h"
#include "key.h"
#include "mon_infor.h"

#include "spellcard.h"
#include "skill_use.h"
#include "weapon.h"
#include "map.h"

bool wizard_mode = false;


bool skill_summon_bug(int pow, bool short_, unit* order, coord_def target);

void wiz_mode()
{
	printlog("<위자드모드> 어느 명령어?",true,false,false,CL_help);
	wizard_mode = true;
	int key_ = waitkeyinput();
	switch(key_)
	{
	case 'D': //맵밝히기
		for(int i = 0;i<DG_MAX_X;i++)
			for(int j = 0;j<DG_MAX_Y;j++)
				env[current_level].dgtile[i][j].flag = env[current_level].dgtile[i][j].flag | FLAG_MAPPING;
		break;
	case 'f': //연기
		//for(int i = -1;i<2;i++)
		//	for(int j = -1;j<2;j++)
		//		env[current_level].MakeSmoke(coord_def(i+you.position.x,j+you.position.y),img_fog_fire,SMT_NORMAL,10,0,&you);
		MakeCloud(you.position, img_fog_fire, SMT_FIRE, rand_int(8,10), rand_int(8,12), 0,5, &you);
		break;
	case 'A':
		{
			item_infor t;
			makeitem(ITM_SPELL, 0, &t, SPC_V_INVISIBLE);
			env[current_level].MakeItem(you.position,t);

			break;
		}
	case 'H':
		you.HpUpDown(you.max_hp,DR_EFFECT);
		you.MpUpDown(you.max_mp);
		you.PowUpDown(500,true);
		break;
	case 'X':
		you.GetExp(you.GetNeedExp(you.level-1) - you.exper);
		break;
	case '>': //다음층 이동
		if(!environment::isLastFloor(current_level))
		{
			deque<monster*> dq;
			env[current_level+1].EnterMap(0,dq);
			//you.resetLOS(false);
		}
		break;
	case '<': //이전층 이동	
		if(!environment::isFirstFloor(current_level))
		{
			deque<monster*> dq;
			env[current_level-1].EnterMap(0,dq);
			//you.resetLOS(false);
		}
		break;
	case 'G': //던전이동	
		{
		deque<monster*> dq;
		dungeon_level next_ = TEMPLE_LEVEL;
		printlog("어느 던전으로 이동해볼까?",true,false,false,CL_help);
		printlog("D - 던전     T - 신전      L - 안개의 호수     M - 요괴의 산     S - 홍마관",true,false,false,CL_help);
		printlog("B - 홍마관도서관   U - 홍마관지하   A - 미궁의죽림  E - 영원정   Y - 윳쿠리둥지 ",true,false,false,CL_help);
		printlog("P - 짐승길  H - 지령전  R - 꿈의 세계 O - 달의 세계  K - 마계  Z - 하쿠레이신사",true,false,false,CL_help);
		printlog("어느 던전으로 이동해볼까?",true,false,false,CL_help);
		wizard_mode = true;
		key_ = waitkeyinput();
		switch(key_)
		{
			case 'd':
				next_ = (dungeon_level)0;
				break;
			case 'D':
				next_ = MAX_DUNGEUN_LEVEL;
				break;
			case 't':
			case 'T':
				next_ = TEMPLE_LEVEL;
				break;
			case 'l':
				next_ = MISTY_LAKE_LEVEL;
				break;
			case 'L':
				next_ = MISTY_LAKE_LAST_LEVEL;
				break;
			case 'm':
				next_ = YOUKAI_MOUNTAIN_LEVEL;
				break;
			case 'M':
				next_ = YOUKAI_MOUNTAIN_LAST_LEVEL;
				break;
			case 's':
				next_ = SCARLET_LEVEL;
				break;
			case 'S':
				next_ = SCARLET_LEVEL_LAST_LEVEL;
				break;
			case 'b':					
			case 'B':
				next_ = SCARLET_LIBRARY_LEVEL;
				break;	
			case 'u':		
			case 'U':
				next_ = SCARLET_UNDER_LEVEL;
				break;
			case 'a':			
			case 'A':					
				next_ = BAMBOO_LEVEL;
				break;
			case 'e':			
			case 'E':					
				next_ = EIENTEI_LEVEL;
				break;
			case 'h':	
				next_ = SUBTERRANEAN_LEVEL;
				break;		
			case 'H':
				next_ = SUBTERRANEAN_LEVEL_LAST_LEVEL;
				break;	
			case 'y':	
				next_ = YUKKURI_LEVEL;
				break;	
			case 'Y':
				next_ = YUKKURI_LAST_LEVEL;
				break;	
			case 'p':	
				next_ = DEPTH_LEVEL;
				break;	
			case 'P':
				next_ = DEPTH_LAST_LEVEL;
				break;	
			case 'r':	
			case 'R':	
				next_ = DREAM_LEVEL;
				break;	
			case 'o':	
			case 'O':
				next_ = MOON_LEVEL;
				break;					
			case 'k':	
			case 'K':
				next_ = PANDEMONIUM_LEVEL;
				break;	
			case 'z':	
				next_ = HAKUREI_LEVEL;
				break;	
			case 'Z':
				next_ = HAKUREI_LAST_LEVEL;
				break;	
			default:
				return;
		}
		env[next_].EnterMap(0,dq);
		printlog("계단을 내려왔다.",true,false,false,CL_normal);
		//you.resetLOS(false);
		break;
		}
	case 'b':
		you.Blink(40);
		break;
	case 's':
		//skill_summon_bug(10,false,&you,you.position);		
		if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
		{
			printarray(true,false,false,CL_white_blue,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"독을 떨어뜨리기 시작했다.");
			you.equipment[ET_WEAPON]->value5 = WB_AUTUMN;
			you.equipment[ET_WEAPON]->value6 = rand_int(10,20)+30;
		}
		else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_POISON && you.equipment[ET_WEAPON]->value6>0)
		{
			printarray(true,false,false,CL_white_blue,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"더욱 독이 진해졌다.");
			you.equipment[ET_WEAPON]->value6 += rand_int(8,12)+30;
			if(you.equipment[ET_WEAPON]->value6>50)
				you.equipment[ET_WEAPON]->value6 = 50;
		}
		else
		{
			printlog("마법이 듣지 않는다.",true,false,false,CL_normal);
		}
		break;
	case 'w':
		//skill_summon_bug(100,&you,you.position);		
		you.SetBuff((stat_up)rand_int(BUFFSTAT_STR,BUFFSTAT_EV),BUFF_DUPLE,rand_int(-3,3),10);
		break;
	case 'p':
		env[current_level].dgtile[you.position.x][you.position.y].tile = (dungeon_tile_type) rand_int(DG_TEMPLE_FIRST,DG_TEMPLE_LAST);
		break;
	case 'M':
		if(monster* mon_=BaseSummon(MON_BLOOD_HAUNT, 100, false, false, 2, &you, you.position, SKD_OTHER, -1))
		{
			mon_->state.SetState(MS_SLEEP);
			mon_->flag &= ~M_FLAG_SUMMON;
			mon_->ReturnEnemy();
		}
		break;
	case 'm':
		if(monster* mon_=BaseSummon(MON_NIGHTMARE, 100, false, false, 2, &you, you.position, SKD_OTHER, -1))
		{
			mon_->state.SetState(MS_SLEEP);
			mon_->flag &= ~M_FLAG_SUMMON;
			//mon_->ReturnEnemy();
		}
		break;
	case '^':
		you.PietyUpDown(10);
		you.GiftCount(10);
		break;
	case 'C':
		{
			for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
			{
				if(it->isLive())
					it->dead(PRT_PLAYER,false);
			}
			for(list<item>::iterator it = env[current_level].item_list.begin(); it != env[current_level].item_list.end(); it++)
			{
				it->position = you.position;
			}
		}
		break;
	case 'E':
		{
			int prevexp_=0, exp_ = 0;
			for(int i = 0; i <= map_list.dungeon_enter[MISTY_LAKE].floor; i++)
			{
				env[i].MakeMap(true);				
				for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
				{
					if(it->isLive())
						it->dead(PRT_PLAYER,false);
				}
			}
			exp_ = you.exper;
			char temp[200];
			sprintf_s(temp,200,"일반던전 %d층까지 레벨:%d (경험치양 %d)",map_list.dungeon_enter[MISTY_LAKE].floor+1, you.level,exp_-prevexp_);
			printlog(temp,true,false,false,CL_normal);
			prevexp_ = exp_;
				 
			for(int i = MISTY_LAKE_LEVEL; i <= MISTY_LAKE_LAST_LEVEL; i++)
			{
				env[i].MakeMap(true);				
				for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
				{
					if(it->isLive())
						it->dead(PRT_PLAYER,false);
				}
			}
			exp_ = you.exper;
			sprintf_s(temp,200,"안개호수클리어 레벨:%d (경험치양 %d)", you.level,exp_-prevexp_);
			printlog(temp,true,false,false,CL_normal);
			prevexp_ = exp_;


			for(int i = map_list.dungeon_enter[MISTY_LAKE].floor+1; i <= MAX_DUNGEUN_LEVEL; i++)
			{
				env[i].MakeMap(true);				
				for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
				{
					if(it->isLive())
						it->dead(PRT_PLAYER,false);
				}
			}
			exp_ = you.exper;
			sprintf_s(temp,200,"남은던전 클리어 레벨:%d (경험치양 %d)", you.level,exp_-prevexp_);
			printlog(temp,true,false,false,CL_normal);
			prevexp_ = exp_;


			for(int i = YOUKAI_MOUNTAIN_LEVEL; i <= YOUKAI_MOUNTAIN_LAST_LEVEL; i++)
			{
				env[i].MakeMap(true);				
				for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
				{
					if(it->isLive())
						it->dead(PRT_PLAYER,false);
				}
			}
			exp_ = you.exper;
			sprintf_s(temp,200,"요괴의산 클리어 레벨:%d (경험치양 %d)", you.level,exp_-prevexp_);
			printlog(temp,true,false,false,CL_normal);
			prevexp_ = exp_;

			for(int i = SCARLET_LEVEL; i <= SCARLET_LEVEL_LAST_LEVEL; i++)
			{
				env[i].MakeMap(true);				
				for(vector<monster>::iterator it = env[i].mon_vector.begin(); it != env[i].mon_vector.end(); it++)
				{
					if(it->isLive())
						it->dead(PRT_PLAYER,false);
				}
			}
			exp_ = you.exper;
			sprintf_s(temp,200,"홍마관 클리어 레벨:%d (경험치양 %d)", you.level,exp_-prevexp_);
			printlog(temp,true,false,false,CL_normal);
			prevexp_ = exp_;
		}
		break;
	default:
		printlog("없는 명령어",true,false,false,CL_help);
		break;
	}

}