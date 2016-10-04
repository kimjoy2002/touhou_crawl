//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: skill_use.cpp
//
// 내용: 사용하는 스킬들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "unit.h"
#include "skill_use.h"
#include "throw.h"
#include "beam.h"
#include "monster.h"
#include "smoke.h"
#include "mon_infor.h"
#include "rect.h"
#include "player.h"
#include "monster_texture.h"
#include "weapon.h"
#include "environment.h"
#include "key.h"
#include "floor.h"
#include "debuf.h"
#include "potion.h"
#include "throw.h"
#include "projectile.h"
#include "event.h"
#include "armour.h"
#include "god.h"
#include "note.h"
#include "rand_shuffle.h"
#include "seija.h"
#include "lilly.h"


extern HANDLE mutx;
extern bool widesearch; //X커맨드용

bool skill_kanako_might(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		monster* unit_ = (monster*)env[current_level].isMonsterPos(target.x,target.y, &you);
		if(!unit_ || unit_->isUserAlly())
		{
			printlog("적 몬스터를 대상으로 써야한다.",true,false,false,CL_normal);	
			return false; //해당 위치에 몬스터가 없다.
		}

		beam_iterator beam(order->position,order->position);
		if(CheckThrowPath(order->position,target,beam))
		{
			beam.init();
			
			if(beam.GetMaxLength() == 1 || env[current_level].isMonsterPos(beam->x,beam->y, &you))
			{				
				printlog("눈 앞의 상대에겐 돌진할 수 없다.",true,false,false,CL_normal);	
				return false;
			}
			while(!beam.end())
			{
				beam_iterator temp = beam;
				temp++;
				unit *unit_ = env[current_level].isMonsterPos(temp->x,temp->y, &you);
				if(temp.end() || unit_)
				{
					if(!env[current_level].dgtile[beam->x][beam->y].isMove(you.isFly(),you.isSwim(),false))
					{
						printlog("해당 위치엔 돌격할 수 없다.",true,false,false,CL_normal);	
						return false;
					}
					you.SetXY(beam->x,beam->y);

					float multy_ = 1.0f; //기도술, 거리 비례해서 데미지를 주자.
					multy_*=(9.0f+temp.GetCurLength())/9; //거리가 6기준으로 1.66배 데미지를 준다.
					//multy_*=(13.0f+pow/5)/13;

					attack_infor temp_att(you.GetAttack(false)*multy_,you.GetAttack(true),you.GetHit()+10,&you,you.GetParentType(),ATT_RUSH,name_infor("돌진",true));
					unit_->damage(temp_att,false);
					printlog("적에게 돌격했다!",true,false,false,CL_normal);	
					return true;
				}
				beam++;
			}
			printlog("돌진할 수 없다.",true,false,false,CL_normal);
			return false;
		}
		//더이상 마이트는 아니다! 적의 방향으로 돌진한다.
		//you.SetMight(20+randA_1(pow*5));
		printlog("사이에 장애물이 있다.",true,false,false,CL_normal);	
		return false;
	}
	return false;
}


bool skill_kanako_2(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if(BaseSummon(MON_ONBASIRA, 20+randA_1(pow), true, false, 0, order, target, SKD_SUMMON_ONBASIRA, -1))
			return true;
		else
			printlog("생성할 수 없는 위치입니다.",true,false,false,CL_normal);	

	}
	return false;
}

bool skill_kanako_haste(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		you.SetWind(50+randA_1(pow));
	}
	return true;
}
bool skill_turn_graze(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer() && !you.s_graze)
	{
		you.SetGraze(-1/*rand_int(15,25)+pow/2*/);
		int temp = you.Ability(SKL_GRAZE,false,true,1);
		you.Ability(SKL_GRAZE_OFF,false,false,temp);
		return true;
	}
	else if(order->isplayer() && you.s_graze)
		printlog("이미 그레이즈도중에 사용할 수 없다.",true,false,false,CL_normal);	

	return false;
}
bool skill_off_graze(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("그레이즈를 멈췄다.",true,false,false,CL_normal);
		you.s_graze = 0;
		int temp = you.Ability(SKL_GRAZE_OFF,false,true,1);
		you.Ability(SKL_GRAZE,false,false,temp);
		return true;
	}
	return false;
}
bool skill_turn_levitation(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer() && !you.s_levitation)
	{
		you.SetLevitation(rand_int(15,25)+pow/2);
		int temp = you.Ability(SKL_LEVITATION,false,true,1);
		you.Ability(SKL_LEVITATION_OFF,false,false,temp);
		return true;
	}
	else if(order->isplayer() && you.s_levitation)
		printlog("이미 비행도중에 사용할 수 없다.",true,false,false,CL_normal);	

	return false;
}
bool skill_off_levitation(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("비행을 멈췄다.",true,false,false,CL_normal);
		you.s_levitation = 0;
		int temp = you.Ability(SKL_LEVITATION_OFF,false,true,1);
		you.Ability(SKL_LEVITATION,false,false,temp);
		return true;
	}
	return false;
}
bool skill_turn_invisible(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer() && !you.s_invisible)
	{
		you.SetInvisible(rand_int(15,25)+pow/2);
		int temp = you.Ability(SKL_INVISIBLE,false,true,1);
		you.Ability(SKL_INVISIBLE_OFF,false,false,temp);
		return true;
	}
	else if(order->isplayer() && you.s_invisible)
		printlog("이미 투명한 도중에 사용할 수 없다.",true,false,false,CL_normal);	

	return false;
}
bool skill_off_invisible(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("다시 보이기 시작했다.",true,false,false,CL_normal);
		you.s_invisible = 0;
		int temp = you.Ability(SKL_INVISIBLE_OFF,false,true,1);
		you.Ability(SKL_INVISIBLE,false,false,temp);
		return true;
	}
	return false;
}

bool skill_soul_shot(int power, unit* order, coord_def target)
{
	for(int i=-2;i<=2;i++)
		for(int j=-2;j<=2;j++)
			if(abs(i)+abs(j)<4 && env[current_level].isMove(order->position.x+i,order->position.y+j,true))
				env[current_level].MakeEffect(coord_def(order->position.x+i,order->position.y+j),&img_blast[3],false);
	for(int i=-2;i<=2;i++)
	{
		for(int j=-2;j<=2;j++)
		{				
			if(abs(i)+abs(j)<4 && (env[current_level].isInSight(order->position+i)) && env[current_level].isMove(order->position.x+i,order->position.y+j,true))
			{
				if(unit* hit_ = env[current_level].isMonsterPos(order->position.x+i,order->position.y+j))
				{
					if(hit_ != order)
						hit_->SetParalyse(rand_int(5,10));
				}
			}
		}
	}
	Sleep(300);
	env[current_level].ClearEffect();

	return false;
}
bool skill_eirin_throw_potion(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	int length_ = ceil(sqrt(pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2)));
	length_ = min(length_,SpellLength(SPL_FIRE_BALL));
	if(CheckThrowPath(order->position,target,beam))
	{
		view_item(IVT_POTION,"무엇을 던지겠습니까?");
		while(1)
		{
			int key_ = waitkeyinput(true);
			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				changedisplay(DT_GAME);
				list<item>::iterator it;
				for(it = you.item_list.begin(); it != you.item_list.end();it++)
				{
					if((*it).id == key_)
					{
						if((*it).type == ITM_POTION)
						{				
							textures *t_ = img_fog_normal;
							smoke_type smoke_ = SMT_FOG;

							switch((*it).value1)
							{
							case PT_POISON:
								t_ = img_fog_poison;
								smoke_ = SMT_POISON;
								break;
							case PT_CONFUSE:
								t_ = img_fog_poison;
								smoke_ = SMT_CONFUSE;
								break;
							case PT_SLOW:
								t_ = img_fog_slow;
								smoke_ = SMT_SLOW;
								break;
							case PT_DOWN_STAT:
								t_ = img_fog_cold;
								smoke_ = SMT_COLD;
								break;
							case PT_PARALYSIS:
								t_ = img_fog_fire;
								smoke_ = SMT_FIRE;
								break;
							}
							beam_infor temp_infor(randA(power/10),randA(power/10),10,order,order->GetParentType(),length_,1,BMT_PENETRATE,ATT_THROW_NONE_MASSAGE,name_infor("물약",true));
							
							for(int i=0;i<(order->GetParadox()?2:1);i++)
							{
								coord_def pos = throwtanmac(27,beam,temp_infor,NULL, false);
								{
									for(int i=-1;i<=1;i++)
										for(int j=-1;j<=1;j++)
											if(env[current_level].isMove(pos.x+i,pos.y+j,true))
												env[current_level].MakeEffect(coord_def(pos.x+i,pos.y+j),t_,false);
									for(int i=-1;i<=1;i++)
										for(int j=-1;j<=1;j++)
												env[current_level].MakeSmoke(coord_def(pos.x+i,pos.y+j),t_,smoke_,rand_int(7+power/8,20+power/8),0,&you);
									Sleep(300);
									env[current_level].ClearEffect();

								}
							}
							order->SetParadox(0); 
							
							you.DeleteItem(it,1);
							return true;	

						}
						else
						{
							printlog("그것은 물약이 아니다.",true,false,false,CL_normal);
							return false;	
						}
					}
				}
				printlog("존재하지 않는 아이템.",true,false,false,CL_normal);
				return false;	
			}
			else if(key_ == VK_DOWN)//-----이동키-------
			{
				changemove(32);  //위
			}
			else if(key_ == VK_UP)
			{
				changemove(-32); //아래
			}
			else if(key_ == VK_PRIOR)
			{
				changemove(-WindowHeight);
			}
			else if(key_ == VK_NEXT)
			{
				changemove(WindowHeight);
			}						//-----이동키끝-------
			else if(key_ == '*')
				view_item(IVT_SELECT,"무엇을 던지겠습니까?");
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
		return false;
	}
	return false;
}

bool skill_eirin_move_stat(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		bool end_ = false;
		int stat_ = 0;
		//어디서부터
		printlog("어느 능력치로 몰아줄거지? (S)tr - 힘  (D)ex - 민첩  (I)nt - 지능 (N) - 제거",true,false,false,CL_help);
		while(!end_)
		{
			switch(waitkeyinput())
			{
			case 'S':
				stat_ = 1;
				end_ = true;
				break;
			case 'D':
				stat_ = 2;
				end_ = true;
				break;
			case 'I':
				stat_ = 3;
				end_ = true;
				break;
			case 'N':
				stat_ = 0;
				end_ = true;
				break;
			case VK_ESCAPE:
				printlog("취소하였다. 신중하게 생각하도록!",true,false,false,CL_help);
				return false;
			}
		}

		if(you.s_stat_boost == stat_)
		{
			if(stat_)
				printlog("당신은 이미 그 능력치로 개조되어있다!",false,false,false,CL_normal);
			else
				printlog("당신은 개조되어있는 몸이 아니다!",false,false,false,CL_normal);

			return false;
		}


		you.SetStatBoost(stat_, max(1,pietyLevel(you.piety)-1));
		if(stat_)
			printarray(true,false,false,CL_good,3,"에이린이 당신의 몸을 더욱 ",stat_==1?"강력":(stat_==2?"민첩":"똑똑"),"해지도록 개조하였다!");
		else
		{
			printlog("에이린은 당신의 몸을 원래대로 되돌렸다. ",false,false,false,CL_help);
			printlog("아마도...",false,false,false,CL_small_danger);
		}
		return true;
	}
	return false;
}

bool skill_eirin_heal(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("당신은 에이린의 임시 수혈로 회복되었다.",true,false,false,CL_help);
		printlog("이 수혈은 시간이 지나면 큰 부작용을 불러올것이다!",true,false,false,CL_danger);
		you.SetEirinHeal(you.max_hp*rand_int(70,80)/100,false);
	}
	return true;
}


bool skill_byakuren_smart(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		int time_ = rand_int(10+randA_1(pow/10),20+randA_1(pow/10));
		you.SetClever(time_);
		you.SetManaRegen(time_);
	}
	return true;
}


bool skill_byakuren_leg(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		int time_ = rand_int(15,15+pow/5);
		you.SetSuperMan(time_);
	}
	return true;
}
bool skill_sizuha_confuse(int pow, bool short_, unit* order, coord_def target)
{
	int number_ = 0;
	for(auto it = env[current_level].floor_list.begin(); it!= env[current_level].floor_list.end(); it++)
	{
		if(it->type == FLOORT_AUTUMN && it->parent == PRT_PLAYER)
		{
			unit* unit_ = env[current_level].isMonsterPos(it->position.x,it->position.y,&you);
			
			if(unit_ && !unit_->isUserAlly())
			{
				if(unit_->CalcuateMR(GetDebufPower(SKL_SIZUHA_1, pow)))
				{
					unit_->SetConfuse(rand_int(5,15)+randA(pow/20));
				}
				else if(unit_->isYourShight())
				{					
					printarray(true,false,false,CL_normal,3,unit_->GetName()->name.c_str(),unit_->GetName()->name_is(true),"저항했다.");
				}
				number_++;
			}
		}
	}
	if(!number_)
	{
		printlog("시야안 단풍위에 있는 적이 없다.",true,false,false,CL_normal);
		return false;
	}
	return true;

}
bool skill_sizuha_autumn_armour(int pow, bool short_, unit* order, coord_def target)
{
	if(you.equipment[ET_ARMOR])
	{
		if(you.equipment[ET_ARMOR]->isArtifact())
		{
			printlog("아티펙트는 변화할 수 없다.",true,false,false,CL_normal);
			return false;
		}
		if(you.equipment[ET_ARMOR]->value5 == AMK_AUTUMN)
		{
			printlog("이 아이템은 이미 단풍으로 되어있다.",true,false,false,CL_normal);
			return false;
		}
			
		
		printarray(true,false,true,CL_help,3,you.equipment[ET_ARMOR]->name.name.c_str(),you.equipment[ET_ARMOR]->name.name_to(true),"단풍방어구로 강화하시겠습니까?(y/n)");
		
		
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			break;
		default:
			printlog("취소하였다. 신중하게 생각하도록!",true,false,false,CL_help);
			return false;
		}
		
		equipArmour((armour_kind)you.equipment[ET_ARMOR]->value5, -1);

		you.equipment[ET_ARMOR]->value5=AMK_AUTUMN;

		equipArmour((armour_kind)you.equipment[ET_ARMOR]->value5, 1);

		
		you.equipment[ET_ARMOR]->name.name = GetMaterialString((material_kind)(you.equipment[ET_ARMOR]->type-ITM_ARMOR_BODY_ARMOUR_0));
		you.equipment[ET_ARMOR]->name.name += " 단풍옷";


		switch(you.equipment[ET_ARMOR]->type)
		{
		case ITM_ARMOR_BODY_ARMOUR_0:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[1];		
			break;
		case ITM_ARMOR_BODY_ARMOUR_1:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[2];	
			break;
		case ITM_ARMOR_BODY_ARMOUR_2:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[3];		
			break;
		case ITM_ARMOR_BODY_ARMOUR_3:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[4];		
			break;
		}
		printlog("당신의 방어구는 커다란 단풍잎으로 변했다!",true,false,false,CL_normal);
	}
	else
	{
		printlog("당신은 방어구를 끼고 있지 않다.",true,false,false,CL_normal);
		return false;
	}
	return true;
}
	
bool skill_minoriko_restore(int pow, bool short_, unit* order, coord_def target)
{
	{
		bool up_ = false;
		
		if(you.s_confuse)
		{
			you.s_confuse = 0;
			up_ = true;
		}
		if(you.s_poison)
		{
			you.s_poison = 0;
			up_ = true;
		}
		if(you.s_sick)
		{
			you.s_sick = 0;
			up_ = true;
		}
		if(you.s_frozen)
		{
			you.s_frozen = 0;
			up_ = true;
		}
		if(you.s_glow)
		{
			you.s_glow = 0;
			up_ = true;
		}
		if(you.s_slow)
		{
			you.s_slow = 0;
			up_ = true;
		}


		if(you.s_str != you.m_str)
		{
			you.StatUpDown(you.m_str-you.s_str,STAT_STR,true);
			up_ = true;
		}
		if(you.s_dex != you.m_dex)
		{
			you.StatUpDown(you.m_dex-you.s_dex,STAT_DEX,true);
			up_ = true;
		}
		if(you.s_int != you.m_int)
		{
			you.StatUpDown(you.m_int-you.s_int,STAT_INT,true);
			up_ = true;
		}
		if(up_)
		{
			printlog("당신은 상태를 회복하였다.",true,false,false,CL_white_blue);
			return true;
		}
		else{
			printlog("당신은 회복할 상태가 없다.",true,false,false,CL_normal);
			return false;	
		}

	}
	return false;

}
	
bool skill_minoriko_heal(int pow, bool short_, unit* order, coord_def target)
{		
	view_item(IVT_FOOD,"무엇을 사용하겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			list<item>::iterator it;
			for(it = you.item_list.begin(); it != you.item_list.end();it++)
			{
				if((*it).id == key_)
				{
					if((*it).type == ITM_FOOD)
					{						
						int bonus_ = (*it).value5 / 10;
						order->HpUpDown(rand_int(10+bonus_,15+bonus_)+order->GetMaxHp()*rand_float(0.15f,0.25f),DR_NONE);
						you.DeleteItem(it,1);
						printlog("음식을 통해 체력을 회복하였다.",true,false,false,CL_white_blue);
						return true;	
					}
					else
					{
						printlog("그것은 음식이 아니다.",true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog("존재하지 않는 아이템.",true,false,false,CL_normal);
			return false;	
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"무엇을 사용하시겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}

bool skill_yuugi_drink(int pow, bool short_, unit* order, coord_def target)
{
	{
		view_item(IVT_POTION,"무엇을 사용하겠습니까?");
		while(1)
		{
			int key_ = waitkeyinput(true);
			if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
			{
				changedisplay(DT_GAME);
				list<item>::iterator it;
				for(it = you.item_list.begin(); it != you.item_list.end();it++)
				{
					if((*it).id == key_)
					{
						if((*it).type == ITM_POTION)
						{	
							drinkpotion(PT_ALCOHOL);	
							you.DeleteItem(it,1);
							return true;	

						}
						else
						{
							printlog("그것은 물약이 아니다.",true,false,false,CL_normal);
							return false;	
						}
					}
				}
				printlog("존재하지 않는 아이템.",true,false,false,CL_normal);
				return false;	
			}
			else if(key_ == VK_DOWN)//-----이동키-------
			{
				changemove(32);  //위
			}
			else if(key_ == VK_UP)
			{
				changemove(-32); //아래
			}
			else if(key_ == VK_PRIOR)
			{
				changemove(-WindowHeight);
			}
			else if(key_ == VK_NEXT)
			{
				changemove(WindowHeight);
			}						//-----이동키끝-------
			else if(key_ == '*')
				view_item(IVT_SELECT,"무엇을 사용하겠습니까?");
			else if(key_ == VK_ESCAPE)
				break;
		}
		changedisplay(DT_GAME);
		return false;
	}
	return false;
}
bool skill_yuugi_german(int pow, bool short_, unit* order, coord_def target)
{
	unit* unit_ = env[current_level].isMonsterPos(target.x,target.y,order);
	if(unit_&& order->isplayer() && !unit_->isplayer())
	{
		monster* mon_ = (monster*)unit_;
		bool no_cost_ = (you.s_catch && mon_->s_catch);
		if(you.isEnemyMonster(mon_))
		{
			coord_def offset_ = you.position+you.position - mon_->position;
			if(!env[current_level].isMove(offset_))
			{
				printlog("적에게 저먼 스플렉스를 걸 지면이 부족하다.",true,false,false,CL_normal);
				return false;	
			}
			if(env[current_level].isMonsterPos(offset_.x,offset_.y,order))
			{
				printlog("저먼 스플렉스를 쓰는데 방해되는 누군가가 있다.",true,false,false,CL_normal);
				return false;	
			}
			mon_->SetXY(offset_);
			int damage_ = you.GetAttack(false)*10/you.GetAtkDelay()*(1+pow/100.0f)+randC(2,2+pow/20);
			int max_damage_ = you.GetAttack(true)*10/you.GetAtkDelay()*(1+pow/100.0f)+2*(2+pow/20);				
			
			printlog("저먼 스플렉스! ",false,false,false,CL_yuigi);
			attack_infor temp_att(damage_,max_damage_,99,&you,you.GetParentType(),ATT_NORMAL_HIT,name_infor("저먼 스플렉스",false));
			unit_->damage(temp_att,true);

			if(!no_cost_)
				you.PietyUpDown(-4);
			return true;
		}
	}
	return false;
}
bool skill_yuugi_throw(int power, bool short_, unit* order, coord_def target)
{
	unit* unit_ = env[current_level].isMonsterPos(target.x,target.y,order);
	if(unit_ && order->isplayer() && !unit_->isplayer())
	{
		monster* mon_ = (monster*)unit_;
		bool no_cost_ = (you.s_catch && mon_->s_catch);
		if(you.isEnemyMonster(mon_))
		{
			int throw_length_ = 7;
			SetSpellSight(throw_length_, 1);
			beam_iterator beam(you.position,you.position);
			projectile_infor infor(throw_length_,false,false,SKL_YUUGI_3_THROW,true);
			int temp_flag = mon_->flag;
			mon_->flag |= M_FLAG_PASSED_ENEMY;
			if(Common_Throw(you.item_list.end(), you.GetTargetIter(), beam, &infor, throw_length_, 0.0f))
			{		
				int length_ = ceil(sqrt(pow((float)abs(order->position.x-you.search_pos.x),2)+pow((float)abs(order->position.y-you.search_pos.y),2)));
				printlog("날라가라! ",false,false,false,CL_yuigi);
				int damage_ = 5+mon_->level+power/10;
				beam_infor temp_infor(randC(1,damage_),damage_,15,order,order->GetParentType(),length_,1,BMT_PENETRATE,ATT_THROW_NORMAL,mon_->name);
				coord_def final_ = throwtanmac(mon_->image,beam,temp_infor,NULL);

				
				dif_rect_iterator rit(final_,3);

				for(;!rit.end();rit++)
				{
					if(!env[current_level].isMove(rit->x, rit->y))
						continue; //움직일수없는 위치	
					if(env[current_level].isMonsterPos(rit->x,rit->y)) 
						continue; //이미 몬스터가 있는 위치

					mon_->SetXY(*rit);
					break;
				}
				attack_infor temp_att(randC(3,3+power/15),3*(3+power/15),99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor("충격파",false));
				BaseBomb(final_, &img_blast[2],temp_att,&you);

				
				mon_->flag = temp_flag;
				if(!no_cost_)
					you.PietyUpDown(-5);
				return true;
			}
			mon_->flag = temp_flag;
		}
	}
	return false;
}
bool skill_yuugi_shout(int pow, bool short_, unit* order, coord_def target)
{
	bool ok_ = false;
	int enter_ = 0;
	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(it->isLive() && env[current_level].isInSight(it->position))
		{
			int offset_ = max(-4,(it->level - you.level));
			if(!ok_)
				printlog("침묵하라! ",false,false,false,CL_yuigi);
			if(randA(10+offset_)>3+offset_ || (you.s_catch && !it->isplayer() && ((monster*)&(*it))->s_catch))
			{
				it->SetMute(rand_int(20+pow/5,40+pow/5));
				enter_++;
				if(enter_==3)
				{
					enterlog();
					enter_ = 0;
				}
			}
			ok_ = true;
		}
	}
	if(ok_)
	{
		return true;
	}
	else
	{
		printlog("포효를 들을 상대가 없다.",true,false,false,CL_normal);
		return false;	
	}
	return false;
}
bool skill_yuugi_sambo(int power, bool short_, unit* order, coord_def target)
{
	printlog("삼보필살! ",false,false,false,CL_yuigi);
	for(int i = 0; i < 3; i++)
	{
		textures* t_ = i==0?&img_blast[4]:i==1?&img_blast[3]:&img_blast[0];
		{
			dif_rect_iterator rit(order->position,2+i);
		
			for(;!rit.end();rit++)
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if(env[current_level].isInSight(*rit) && you.isSightnonblocked(*rit))
					{
						env[current_level].MakeEffect(*rit,t_,false);
					}
				}
		}
		{
			dif_rect_iterator rit(order->position,2+i);
		
			for(;!rit.end();rit++)
			{
				if(env[current_level].isMove(rit->x,rit->y,true))
				{
					if(env[current_level].isInSight(*rit) && you.isSightnonblocked(*rit))
					{
						if(unit* hit_ = env[current_level].isMonsterPos(rit->x,rit->y))
						{	
							if(hit_ != order)
							{
								int att_ = randC(4,4+i+power/20);
								int m_att_ = 4*(4+i+power/20);
								if(you.s_catch && !hit_->isplayer() && ((monster*)hit_)->s_catch)
								{
									att_ *= 2;
									m_att_ *= 2;
								}

								attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor("충격파",false));
								hit_->damage(temp_att, true);
							}
						}
					}
				}
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		you.time_delay += you.GetNormalDelay();
		you.TurnEnd();
		Sleep(100);

	}
	return true;
}
bool skill_satori_trauma(int power, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = env[current_level].isMonsterPos(target.x,target.y,order))
	{
		if(!(hit_mon->isplayer()) && ((monster*)hit_mon)->id == MON_KOISHI)
		{
			printarray(true,false,false,CL_small_danger,1,"동생의 마음은 닫혀있다.");
			return false;
		}

		if(hit_mon->CalcuateMR(GetDebufPower(SKL_SATORI_1,power)))
		{
			

			hit_mon->SetFear(rand_int(15,20));
		}
		else if(hit_mon->isYourShight())
		{					
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
		}
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}
bool skill_satori_mind_reading(int power, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;
	unit* unit_ = env[current_level].isMonsterPos(target.x,target.y,order);
	if(unit_ && order->isplayer() && !unit_->isplayer())
	{
		monster* mon_ = (monster*)unit_;
		if(you.isEnemyMonster(mon_))
		{
			int turn_ = 2+mon_->level/3+mon_->resist*3;

			turn_ = max(1,turn_-you.level/4);

			if(turn_>=20)
			{
				printarray(true,false,false,CL_small_danger,1,"이 상대의 마음은 읽을 수 없다.");
				return false;
			}
			if(mon_->id == MON_KOISHI)
			{
				printarray(true,false,false,CL_small_danger,1,"동생의 마음은 닫혀있다.");
				return false;
			}
			if(mon_->s_mind_reading)
			{
				printarray(true,false,false,CL_normal,1,"이미 마음을 간파한 대상이다.");
				return false;

			}

			int fail_ = 0;
			for(int i=0; i<turn_; i++)
			{
				printarray(false,false,false,CL_danger,1,"마음을 읽는 중... ");
				if(you.s_confuse || you.s_paralyse)
				{
					fail_ = 1;
					break;
				}
				if(!env[current_level].isInSight(mon_->position))
				{
					fail_ = 2;
					break;
				}
				you.time_delay += you.GetNormalDelay();
				you.TurnEnd();
				Sleep(100);
			}
			if(fail_)
				printarray(true,false,false,CL_small_danger,1,fail_==1?"방해를 받아 마음을 읽는데 실패했다.":"대상이 시야에 사라져서 실패했다.");
			else
			{
				//printarray(true,false,false,CL_normal,3,mon_->GetName()->name.c_str(),mon_->GetName()->name_is(true),"마음을 간파당했다.");
				mon_->SetMindReading(1);
			}
			return true;
		}

	}

	return false;
}

bool skill_shinki_low_demon(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;

	for(int i = rand_int(2,3); i>0 ; i--)
	{
		if(BaseSummon((randA(1)?MON_EVIL_EYE:MON_LITTLE_IMP), rand_int(30,50), true, false, 2, order, target, SKD_SUMMON_SHINKI, -1))
			return_ = true;
	}
	if(return_)
	{		
		printarray(true,false,false,CL_magic,1,"마계의 졸개들이 당신에게 소환되었다. ");	
	}
	return return_;
}
bool skill_shinki_mid_demon(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	if(monster* mon_=BaseSummon(randA(2)==0?MON_SARA:(randA(1)?MON_LUIZE:MON_ELIS), rand_int(90,120), true, false, 2, order, target, SKD_SUMMON_SHINKI, -1))
	{			
		printarray(false,false,false,CL_magic,3,mon_->name.name.c_str(),mon_->name.name_do(true),"당신에게 소환되었다. ");		
		if(randA(99)<=8)
		{
			printarray(false,false,false,CL_danger,2,mon_->name.name.c_str(),"의 기분이 썩 좋아보이지 않는다.");				
			mon_->ReturnEnemy();			
		}
		return_ = true;
		enterlog();
	}
	return return_;

} 
bool skill_shinki_high_demon(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	int id_ = randA(3)==0?MON_YUKI:(randA(2)==0?MON_MAI:randA(1)?MON_YUUGENMAGAN:MON_SARIEL);
	if(monster* mon_=BaseSummon(id_, rand_int(90,120), true, false, 2, order, target, SKD_SUMMON_SHINKI, -1))
	{			
		printarray(false,false,false,CL_magic,3,mon_->name.name.c_str(),mon_->name.name_do(true),"당신에게 소환되었다. ");		
		if(randA(99)<=(id_==MON_YUKI?5:id_==MON_MAI?11:8))
		{
			printarray(false,false,false,CL_danger,2,mon_->name.name.c_str(),"의 기분이 썩 좋아보이지 않는다.");				
			mon_->ReturnEnemy();			
		}
		return_ = true;
		enterlog();
	}
	return return_;
} 
bool skill_yuyuko_on(int power, bool short_, unit* order, coord_def target)
{	
	if(order->isplayer() && !you.s_ghost)
	{
		printlog("유령을 불러들이기 시작한다.",true,false,false,CL_normal);
		you.SetGhost(1);
		int temp = you.Ability(SKL_YUYUKO_ON,true,true,1);
		you.Ability(SKL_YUYUKO_OFF,true,false,temp);
		return true;
	}
	else if(order->isplayer() && you.s_ghost)
		printlog("이미 유령을 모으고 있다(버그).",true,false,false,CL_normal);	

	return false;
}
bool skill_yuyuko_off(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog("유령 소환을 멈췄다.",true,false,false,CL_normal);
		you.s_ghost = 0;
		int temp = you.Ability(SKL_YUYUKO_OFF,true,true,1);
		you.Ability(SKL_YUYUKO_ON,true,false,temp);
		return true;
	}
	return false;

}
bool skill_yuyuko_recall(int power, bool short_, unit* order, coord_def target)
{	
	if(!order->isplayer())
		return false;
	unit* unit_ = env[current_level].isMonsterPos(target.x,target.y,order);
	if(unit_ && !unit_->isplayer())
	{
		
		int j=0;
		
		if(you.god_value[GT_YUYUKO][0])
		{
			for(auto it = env[you.god_value[GT_YUYUKO][1]].mon_vector.begin(); j == 0 && it != env[you.god_value[GT_YUYUKO][1]].mon_vector.end();it++)
			{
				if(it->isLive() && (*it).isUserAlly() && it->map_id == you.god_value[GT_YUYUKO][0])
				{
					dif_rect_iterator rit(target,2);
					for(; j == 0 && !rit.end();rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y,it->isFly(),it->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
						{
							if(you.god_value[GT_YUYUKO][1] == current_level)
							{
								it->SetXY(rit->x,rit->y);
								if(unit_){
									it->FoundTarget(unit_,30);
								}
								j++;
							}
							else
							{								
								if(env[current_level].movingfloor((*rit), you.god_value[GT_YUYUKO][1], &(*it)))
								{
									j++;
								}
							}
						}
					}
				}
			}

		}

		deque<monster*> dq;
		for(vector<monster>::iterator it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end();it++)
		{
			if(it->isLive() && it->isUserAlly()  && it->GetId() == MON_GHOST)
			{
				dq.push_back(&(*it));
			}
		}
		rand_shuffle(dq.begin(),dq.end());
		dif_rect_iterator rit(target,2);
		for(int i = 0;!rit.end() && i < dq.size();rit++)
		{
			if(env[current_level].isMove(rit->x, rit->y, dq[i]->isFly(), dq[i]->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
			{
				dq[i]->SetXY(rit->x,rit->y);
				if(dq[i] && unit_){
					dq[i]->FoundTarget( unit_,30);
				}
				j++;
				i++;
			}
		}
		if(j>0)
		{
			printarray(true,false,false,CL_normal,2,unit_->GetName()->name.c_str(),"에게 유령을 내보냈다.");
			unit_->AttackedTarget(order);
			return true;
		}
		else
		{
			printarray(true,false,false,CL_normal,1,"유령이 없다.");
			return false;
		}
	}
	printlog("유닛을 대상으로 사용해야한다.",true,false,false,CL_normal);
	return false;
}
bool skill_yuyuko_boost(int power, bool short_, unit* order, coord_def target)
{	
	if(order->isplayer())
	{
		printlog("당신은 대량의 유령을 불러들이기 시작한다!",true,false,false,CL_white_blue);
		int time_ = rand_int(35,45);
		you.SetGhost(time_);
	}
	return true;

}
bool skill_yuyuko_enslave(int power, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;	
	if(unit* hit_mon = DebufBeam(SKL_YUYUKO_3, order, target))
	{
		/*
	if(unit* hit_mon = env[current_level].isMonsterPos(target.x,target.y,order))
	{*/
		if(1/*hit_mon->CalcuateMR(GetDebufPower(SKL_YUYUKO_3,power))*/)
		{
			if(!hit_mon->SetGhost(rand_int(40,60)))
			{
				return false;
			}
		}
		/*else if(hit_mon->isYourShight())
		{					
			printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_is(true),"저항했다.");
		}*/
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}



bool skill_yukari_supporter(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isInSight(coord_def(target.x,target.y)))
	{
		if(floor_effect* hit_eff = env[current_level].isFloorEffectPos(target.x,target.y))
		{
			if(hit_eff->type == FLOORT_SCHEMA)
			{
				if(monster *mon_ = BaseSummon(MON_SCHEMA_EYE, 40+randA_1(power/10), true, false, 0, order, target, SKD_OTHER, -1))
				{
					mon_->LevelUpdown(you.level,3);
					hit_eff->time = 0;
					return true;
				}
				else
				{
					printarray(true,false,false,CL_normal,1,"생성할 수 없는 위치다.");
					return false;
				}
			}
		}
		printarray(true,false,false,CL_normal,1,"틈새를 대상으로 지정해야한다.");
	}
	return false;

}
bool skill_yukari_schema(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isInSight(coord_def(target.x,target.y)))
	{
		if(floor_effect* hit_eff = env[current_level].isFloorEffectPos(target.x,target.y))
		{
			if(hit_eff->type == FLOORT_SCHEMA)
			{
				if(you.control_blink(target))
				{
					printarray(true,false,false,CL_normal,1,"틈새를 타고 이동하였다.");
					hit_eff->time = 0;
					return true;
				}
				else
				{
					printarray(true,false,false,CL_normal,1,"이동할 수 없는 위치다.");
					return false;
				}
			}
		}
		printarray(true,false,false,CL_normal,1,"틈새를 대상으로 지정해야한다.");
	}
	return false;

}
bool skill_yukari_shield(int power, bool short_, unit* order, coord_def target)
{	
	if(order == &you)
	{
		you.SetBuff(BUFFSTAT_SH,BUFF_YUKARI,15,rand_int(70,100));
		printlog("결계가 당신을 보호하고 있다.",true,false,false,CL_white_blue);
		return true;
	}
	return false;
}
bool skill_yukari_dimension(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if(env[current_level].isBamboo())
		{
			printlog("이 곳에서는 차원을 고정할 수 없다!",true,false,false,CL_small_danger);
			return false;
		}
		you.search_pos = target;
		widesearch = true;
		you.search = true;

	
		printlog("이 위치로 차원을 고정할까? (Y/N)",false,false,false,CL_danger);
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			enterlog();
			break;
		case 'N':
		default:
			printlog(" 취소!",true,false,false,CL_normal);
			widesearch = false;
			you.search = false;
			return false;
		}


		widesearch = false;
		you.search = false;

		you.god_value[GT_YUKARI][0] = target.x;
		you.god_value[GT_YUKARI][1] = target.y;
		you.SetDimension(rand_int(50,70));
		printlog("차원이 고정되었다!",false,false,false,CL_white_blue);
		return true;
	}
	return false;
}



bool skill_swako_jump(int power, bool short_, unit* order, coord_def target)
{
	if(env[current_level].isInSight(target) && you.isSightnonblocked(target))
	{
		if(env[current_level].isMove(target.x,target.y) && !env[current_level].isMonsterPos(target.x,target.y))
		{
			you.SetXY(target.x,target.y);
			printarray(false,false,false,CL_normal,1,"점프! ");
			return true;
		}
	}
	return false;
}
bool skill_swako_temple(int power, bool short_, unit* order, coord_def target)
{	
	auto tile_ = env[current_level].dgtile[order->position.x][order->position.y].tile;

	if(tile_ >= DG_FLOOR && tile_ <= DG_FLOOR_END)
	{		
		env[current_level].dgtile[order->position.x][order->position.y].tile = DG_TEMPLE_SUWAKO;
		printlog("당신은 발밑에 스와코님의 신전을 세웠다. 신앙심이 풍족해지는 것을 느꼈다.",true,false,false,CL_swako);
		you.PietyUpDown(2+randA(2));
		return true;
	}
	else
		printlog("여기엔 신전을 세울 수 없다.",true,false,false,CL_small_danger);

	return false;
}
bool skill_swako_water_gun(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randA_1(5+power/5),5+power/5,15,order,order->GetParentType(),SkillLength(SKL_SWAKO_WATER_GUN),1,BMT_NORMAL,ATT_THROW_WATER,name_infor("물총",true));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(14,beam,temp_infor,NULL);
		order->SetParadox(0); 
		return true;
	}
	return false;
}
bool skill_swako_tongue(int power, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;	
	if(unit* hit_mon = DebufBeam(SKL_SWAKO_TOUGUE, order, target))
	{
		beam_iterator beam(order->position,target);
		if(CheckThrowPath(order->position,target,beam))
		{
			beam.init();

			if(env[current_level].isMove(coord_def(beam->x,beam->y),hit_mon->isFly(),hit_mon->isSwim(),false))
			{
				hit_mon->SetXY(*beam);
				hit_mon->AttackedTarget(order);
				printarray(true,false,false,CL_normal,3,hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_to(true),"끌어 당겼다.");
				return true;
			}
		}
		printlog("끌어 당길 수 없는 위치입니다.",true,false,false,CL_small_danger);

	}
	return false;

}
bool skill_swako_curse(int power, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = env[current_level].isMonsterPos(target.x,target.y,order))
	{
		int level_ = min(10,max(0,order->GetLevel() - hit_mon->GetLevel() + 5));
		if(hit_mon->isYourShight())
		{				
			printarray(false,false,false,CL_swako,2,hit_mon->GetName()->name.c_str(),"에 재앙을 내렸다.");
			hit_mon->SetSlow(rand_int(2,10)+randA(level_*3));
			hit_mon->SetPoison(rand_int(20,35)+randA(level_*4),150,true);
			hit_mon->SetPoisonReason(order->GetParentType());
			hit_mon->AttackedTarget(order);

			
			rand_rect_iterator rit(target,1,1);
			int smoke_ = rand_int(2,3);
			for(int i = 0; !rit.end() && i < smoke_;rit++)
			{
				if(env[current_level].isMove(rit->x, rit->y, true))
				{
					env[current_level].MakeSmoke(*rit,img_fog_dark,SMT_FOG,rand_int(6,12),0,&you);
					i++;
				}
			}
			return true;
		}
	}
	return false;
}
bool skill_swako_digging(int power, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;	
	beam_iterator beam(order->position,target);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam.init();
		int length_ = SkillLength(SKL_SWAKO_DIGGING);
		if(short_)
			length_ = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));

		if(length_ == 0)
			return false;

		while(length_>0)
		{
			if(env[current_level].dgtile[beam->x][beam->y].isBreakable())
				env[current_level].dgtile[beam->x][beam->y].tile = DG_FLOOR;
			beam++;
			length_--;
		}
		return true;
	}

	return false;
}
bool skill_swako_summon_flog(int power, bool short_, unit* order, coord_def target)
{	
	bool return_=false;
	if(monster* mon_=BaseSummon(MON_FROG, rand_int(60,80), true, false, 2, order, target, SKD_SUMMON_SWAKO_FLOG, -1))
	{			
		printarray(false,false,false,CL_magic,3,mon_->name.name.c_str(),mon_->name.name_do(true),"당신에게 소환되었다. ");		
		return_ = true;
		enterlog();
	}
	return return_;
}
bool skill_swako_statue(int power, bool short_, unit* order, coord_def target)
{
	auto tile_ = env[current_level].dgtile[target.x][target.y].tile;

	if(tile_ >= DG_FLOOR && tile_ <= DG_FLOOR_END)
	{		
		if(!env[current_level].isMonsterPos(target.x,target.y))
		{
			env[current_level].dgtile[target.x][target.y].tile = DG_STATUE;
			env[current_level].MakeEvent(EVL_FLOOR, target, EVT_COUNT,rand_int(30,50));
			return true;
		}
		else
			printlog("여기엔 석상을 세울 수 없다.",true,false,false,CL_small_danger);
	}
	else
		printlog("여기엔 석상을 세울 수 없다.",true,false,false,CL_small_danger);
	return false;
}
bool skill_swako_rain(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;

	for(int i = rand_int(3,4); i>0 ; i--)
	{
		if(BaseSummon(MON_FROG, rand_int(30,50), true, true, 3, order, target, SKD_SUMMON_SWAKO_FLOG, -1))
			return_ = true;
	}
	if(BaseSummon(MON_DEAGAMA, rand_int(30,50), true, true, 3, order, target, SKD_SUMMON_SWAKO_FLOG, -1))
		return_ = true;


	dif_rect_iterator rit(target,2);
	while(!rit.end())
	{
		auto tile_ = env[current_level].dgtile[rit->x][rit->y].tile;
		if(tile_ >= DG_FLOOR && tile_ <= DG_FLOOR_END)
		{		
			auto mons_ = env[current_level].isMonsterPos(rit->x,rit->y);
			if(!mons_ || mons_->isFly() || mons_->isSwim())
			{
				env[current_level].dgtile[rit->x][rit->y].tile = DG_SEA;
			}
		}
		rit++;
	}

	printarray(true,false,false,CL_magic,1,"당신의 주변이 물바다가 되었다. ");	
	
	return true;
}
bool skill_swako_sleep(int power, bool short_, unit* order, coord_def target)
{
	you.SetTimeStep(100);
	return true;
}
bool skill_swako_misyaguzi(int power, bool short_, unit* order, coord_def target)
{
	return false;
}
bool skill_hina_plusminus(int power, bool short_, unit* order, coord_def target)
{
	view_item(IVT_CURSE_ENCHANT,"무슨 아이템을 고르시겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			list<item>::iterator it;
			for(it = you.item_list.begin(); it != you.item_list.end();it++)
			{
				if((*it).id == key_)
				{
					if(((*it).type>=ITM_WEAPON_FIRST && (*it).type<ITM_WEAPON_LAST) || ((*it).type>=ITM_ARMOR_FIRST && (*it).type<ITM_ARMOR_LAST))
					{		
						if(!it->isArtifact())
						{
							if(it->curse && it->identify_curse)
							{
								if(((*it).type>=ITM_WEAPON_FIRST && (*it).type<ITM_WEAPON_LAST) && (it->value4 < 0))
								{
									int value4_ = it->value4;
									//if(value3_<0)
									//	it->Enchant(ET_WEAPON, value3_*-2);
									if(value4_<0)
										it->Enchant(ET_WEAPON,value4_*-2);
									printlog("히나는 당신의 무기의 액땜을 해주었다.",true,false,false,CL_hina);
									return true;	
								}
								else if(((*it).type>=ITM_ARMOR_FIRST && (*it).type<ITM_ARMOR_LAST) && (it->value4 < 0))
								{
									if(it->value4<0)
										it->Enchant(ET_ARMOR,it->value4*-2);
									printlog("히나는 당신의 방어구의 액땜을 해주었다.",true,false,false,CL_hina);
								
									return true;	

								}
								else
								{
									printlog("마이너스 인챈트가 되어있는 아이템만 선택할 수 있다.",true,false,false,CL_normal);
									return false;	
								}
							}
							else
							{
								printlog("저주 걸려있는 아이템에만 사용할 수 있다.",true,false,false,CL_normal);
								return false;	
							}
						}
						else
						{
							printlog("아티펙트엔 사용할 수 없다.",true,false,false,CL_normal);
							return false;	
						}
					}
					else
					{
						printlog("올바르지 않은 대상이다.",true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog("존재하지 않는 아이템.",true,false,false,CL_normal);
			return false;	
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"무슨 아이템을 고르시겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}
bool skill_hina_curse_weapon(int power, bool short_, unit* order, coord_def target)
{	
	if(you.equipment[ET_WEAPON])
	{
		if(you.equipment[ET_WEAPON]->curse)
		{
			printlog("이미 저주에 걸려있다.",true,false,false,CL_normal);
			return false;
		}
		string before_name = you.equipment[ET_WEAPON]->GetName(); //저주받기전 이름
		if(you.equipment[ET_WEAPON]->Curse(true,ET_WEAPON))
		{
			if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
			{
				printarray(true,false,false,CL_hina,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"저주의 힘으로 가득 차있다.");
				you.equipment[ET_WEAPON]->value5 = WB_CURSE;
				you.equipment[ET_WEAPON]->value6 = rand_int(80,100);
			}
			else
			{
				printlog("장착하고 있던 ",false,false,false,CL_small_danger);	
				printlog(before_name,false,false,false,CL_small_danger);	
				printlog(you.equipment[ET_WEAPON]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
				printlog("검게 빛나면서 당신에게 신비한 힘이 들어온다.",true,false,false,CL_small_danger);		
				you.SetMight(rand_int(80,100));
			}
			return true;
		}
		else
		{
			printlog("이 무기는 저주를 걸 수 없다.",true,false,false,CL_small_danger);
			return false;
		}

	}
	printlog("무기를 끼고 있어야 된다.",true,false,false,CL_normal);
	return false;
}
bool skill_hina_curse_armour(int power, bool short_, unit* order, coord_def target)
{
	view_item(IVT_UEQ_ARMOR,"무슨 방어구를 고르시겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			list<item>::iterator it;
			for(it = you.item_list.begin(); it != you.item_list.end();it++)
			{
				if((*it).id == key_)
				{
					if(((*it).type>=ITM_ARMOR_FIRST && (*it).type<ITM_ARMOR_LAST))
					{		
						for(equip_type i = ET_ARMOR;i!=ET_ARMOR_END;i=(equip_type)(i+1))
						{
							if(you.equipment[i] && you.equipment[i]->id == key_)
							{
								if(!it->curse && it->identify_curse)
								{
									string before_name = you.equipment[i]->GetName(); //저주받기전 이름
									if(it->Curse(true,i))
									{
										int time_ = rand_int(25,40);
										printlog("장착하고 있던 ",false,false,false,CL_small_danger);	
										printlog(before_name,false,false,false,CL_small_danger);	
										printlog(you.equipment[i]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
										printlog("검게 빛나면서 당신은 모든 데미지를 반사한다.",true,false,false,CL_small_danger);	
										if(i == ET_ARMOR)	
											time_*=3;
										you.SetMirror(time_);
										return true;
									}
									else
									{
										printlog("이 방어구에는 저주를 걸 수 없다.",true,false,false,CL_small_danger);
										return false;	
									}
								}
								else
								{
									printlog("이미 저주에 걸려있다.",true,false,false,CL_normal);
									return false;	
								}
							}
						}
						printlog("그것을 입고 있지 않다!",true,false,false,CL_normal);
						return false;	
					}
					else
					{
						printlog("방어구에만 사용이 가능하다.",true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog("존재하지 않는 아이템.",true,false,false,CL_normal);
			return false;	
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"무슨 방어구를 고르시겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}
bool skill_hina_curse_ring(int power, bool short_, unit* order, coord_def target)
{
	view_item(IVT_UEQ_JEWELRY,"무슨 장신구를 고르시겠습니까?");
	while(1)
	{
		int key_ = waitkeyinput(true);
		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			changedisplay(DT_GAME);
			list<item>::iterator it;
			for(it = you.item_list.begin(); it != you.item_list.end();it++)
			{
				if((*it).id == key_)
				{
					if(((*it).type>=ITM_JEWELRY_FIRST && (*it).type<ITM_JEWELRY_LAST))
					{		
						for(equip_type i = ET_JEWELRY;i!=ET_JEWELRY_END;i=(equip_type)(i+1))
						{
							if(you.equipment[i] && you.equipment[i]->id == key_)
							{
								if(!it->curse && it->identify_curse)
								{
									string before_name = you.equipment[i]->GetName(); //저주받기전 이름
									if(it->Curse(true,i))
									{										
										int bonus_ = rand_int(10,15)+you.GetMaxHp()*rand_float(0.25f,0.35f);
										printlog("장착하고 있던 ",false,false,false,CL_small_danger);	
										printlog(before_name,false,false,false,CL_small_danger);	
										printlog(you.equipment[i]->GetNameInfor().name_do(true),false,false,false,CL_small_danger);
										printlog("검게 빛나면서 당신은 회복한다.",true,false,false,CL_small_danger);											
										you.HpUpDown(bonus_,DR_NONE);										
										you.MpUpDown(you.max_mp *rand_float(0.3f,0.4f));
										return true;
									}
									else
									{
										printlog("이 장신구에는 저주를 걸 수 없다.",true,false,false,CL_small_danger);
										return false;
									}
								}
								else
								{
									printlog("이미 저주에 걸려있다.",true,false,false,CL_normal);
									return false;	
								}
							}
						}
						printlog("그것을 입고 있지 않다!",true,false,false,CL_normal);
						return false;	
					}
					else
					{
						printlog("장신구에만 사용이 가능하다.",true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog("존재하지 않는 아이템.",true,false,false,CL_normal);
			return false;	
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			changemove(32);  //위
		}
		else if(key_ == VK_UP)
		{
			changemove(-32); //아래
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-WindowHeight);
		}
		else if(key_ == VK_NEXT)
		{
			changemove(WindowHeight);
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,"무슨 장신구를 고르시겠습니까?");
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}
bool sizuha_autumn_bread(int pow, bool short_, unit* order, coord_def target)
{
	printlog("딱 한번만 현재 무기에 단풍 브랜드를 부여할 수 있다. 할래?(Y/N)",false,false,false,CL_danger);
	switch(waitkeyinput())
	{
	case 'Y':
	case 'y':
		enterlog();
		break;
	case 'N':
	default:
		printlog(" 취소!",true,false,false,CL_normal);
		return false;
	}

	if(you.equipment[ET_WEAPON]  && (you.equipment[ET_WEAPON]->type>=ITM_WEAPON_FIRST && you.equipment[ET_WEAPON]->type<ITM_WEAPON_LAST) && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
	{
		printarray(true,false,false,CL_autumn,2,you.equipment[ET_WEAPON]->GetName().c_str(),"에서 쓸쓸하고도 종말적인 기운이 느껴진다.");
		you.equipment[ET_WEAPON]->value5 = WB_AUTUMN;
		you.equipment[ET_WEAPON]->value6 = -1;
		you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, randA_1(2));
		printlog("시즈하: 유용하게 쓰도록!",true,false,false,CL_autumn);
		you.god_value[GT_SHIZUHA][0] = 1;
		you.Ability(SKL_SIZUHA_3,true,true);
	}
	else
	{
		printlog("여기엔 부여할 수 없다.",true,false,false,CL_normal);
		return false;
	}
	return true;
}
bool hina_curse_bread(int pow, bool short_, unit* order, coord_def target)
{
	printlog("딱 한번만 현재 무기에 저주 브랜드를 부여할 수 있다. 할래?(Y/N)",false,false,false,CL_danger);
	switch(waitkeyinput())
	{
	case 'Y':
	case 'y':
		enterlog();
		break;
	case 'N':
	default:
		printlog(" 취소!",true,false,false,CL_normal);
		return false;
	}

	if(you.equipment[ET_WEAPON]  && (you.equipment[ET_WEAPON]->type>=ITM_WEAPON_FIRST && you.equipment[ET_WEAPON]->type<ITM_WEAPON_LAST) && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
	{
		printarray(true,false,false,CL_hina,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"저주의 힘으로 가득 차있다.");
		you.equipment[ET_WEAPON]->value5 = WB_CURSE;
		you.equipment[ET_WEAPON]->value6 = -1;
		you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, randA_1(2));
		printlog("히나: 유용하게 쓰도록!",true,false,false,CL_hina);
		you.god_value[GT_HINA][0] = 1;
		you.Ability(SKL_HINA_5,true,true);
	}
	else
	{
		printlog("여기엔 부여할 수 없다.",true,false,false,CL_normal);
		return false;
	}
	return true;
}

bool skill_breath(int power, bool short_, unit* order, coord_def target)
{
	if(!order || !order->isplayer())
		return false;


	string str_ = "브레스";
	attack_type type_ = ATT_THROW_COLD;
	int graphic_ = 36;

	switch(you.half_youkai[1])
	{
	case 0:
		str_ = "화염 브레스";
		type_ = ATT_THROW_FIRE;
		graphic_ = 36;
		break;
	case 1:
		str_ = "냉기 브레스";
		type_ = ATT_THROW_COLD;
		graphic_ = 40;
		break;
	case 2:
		str_ = "전격 브레스";
		type_ = ATT_THROW_ELEC;
		graphic_ = 38;
		break;
	}


	beam_iterator beam(order->position,order->position);
	int length_ = ceil(sqrt(pow((float)abs(order->position.x-target.x),2)+pow((float)abs(order->position.y-target.y),2)));
	length_ = min(length_,SkillLength(SKL_BREATH));
	if(CheckThrowPath(order->position,target,beam))
	{
		int damage_ = 15+power/4;
		beam_infor temp_infor(randC(3,damage_),3*(damage_),20,order,order->GetParentType(),SkillLength(SKL_BREATH),8,BMT_PENETRATE,type_,name_infor(str_,false));
		if(short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));
		
		for(int i=0;i<(order->GetParadox()?2:1);i++)
			throwtanmac(graphic_,beam,temp_infor,NULL);
		order->SetParadox(0); 
		if(order)
		{
			order->SetExhausted(rand_int(10,20));
		}
		return true;
	}
	return false;

}
bool skill_torment(int pow, bool short_, unit* order, coord_def target)
{
	printlog("당신은 지옥의 고통을 불렀다!",true,false,false,CL_normal);
	
	for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it!=env[current_level].mon_vector.end(); it++)
	{	
		if(it->isLive() && env[current_level].isInSight(it->position) && order->isSightnonblocked(it->position))
		{
			it->hp=it->hp/2;	
			it->AttackedTarget(order);
			//int att_ = 13+pow/15;
			//	
			//attack_infor temp_att(randC(5,att_),5*(att_),99,order,order->GetParentType(),ATT_THROW_FREEZING,name_infor("냉기",false));
			//it->damage(temp_att, true);			
		}
	}
	return true;
}


bool skill_abandon_god(int pow, bool short_, unit* order, coord_def target)
{
	bool sanae_ = !you.char_name.name.compare("사나에") && (you.god == GT_KANAKO || you.god == GT_SUWAKO);

	if(sanae_)
		printlog("신을 버리면 당신의 신앙심은 전부 사라질것이다. 진짜로?(Y/N)",false,false,false,CL_danger);
	else
		printlog("신을 버리면 당신은 신의 노여움을 살 것이다. 진짜로?(Y/N)",false,false,false,CL_danger);
	switch(waitkeyinput())
	{
	case 'Y':
	case 'y':
		enterlog();
		break;
	case 'N':
	default:
		printlog(" 취소!",true,false,false,CL_normal);
		return false;
	}
	
	if(sanae_)
		printarray(true,false,false,CL_danger,7,"당신은 ", GetGodString(you.god),GetGodString_is(you.god)?"을 ":"를 ","버렸다. ",GetGodString(you.god),GetGodString_is(you.god)?"은 ":"는 ","당신의 독립을 눈물을 머금고 이해했다.");
	else	
		printarray(true,false,false,CL_danger,4,"당신은 ", GetGodString(you.god),GetGodString_is(you.god)?"을 ":"를 ",you.god==GT_SATORI?"버렸다.":"버렸다. 당신의 신은 분노했다!");
	
	
	if(!sanae_)
	{
		you.PunishUpDown(30, you.god , true);
	}
	
	char temp[200];
	sprintf_s(temp,200,"%s%s 버렸다.",GetGodString(you.god),GetGodString_is(you.god)?"을":"를");
	AddNote(you.turn,CurrentLevelString(),temp,CL_small_danger);
	

	
	for(int level_ = pietyLevel(you.piety);level_>=0;level_--)
		GetGodAbility(level_, false);

	
	if(you.god == GT_SATORI)
	{
		you.god_value[GT_SATORI][0] = 1;
	}
	if(you.god == GT_SEIJA)		
		printlog(seija_talk(GT_NONE, 7),true,false,false,CL_seija);


	you.Ability(SKL_ABANDON_GOD,true,true);






	you.god = GT_NONE;	





	return true;
}

bool skill_seija_gift(int pow, bool short_, unit* order, coord_def target)
{
	int loop_ = true;
	god_type next_ = GT_NONE;
	while(loop_)
	{
		printlog("세이자: 어느 신으로부터 훔친 선물을 줄까? (선택시 자세한 설명이 표시됨)",true,false,false,CL_seija);

		string s_;
		printlog("B - 뱌쿠렌     K - 카나코  W - 스와코   A - 미노리코",true,false,false,CL_help);
		printlog("M - 미마       P - 신키    G - 유우기   Z - 시즈하  H - 히나     Y - 유카리 ",true,false,false,CL_help);
		printlog("E - 에이린     U - 유유코  S - 사토리   T - 텐시    L - 릴리",true,false,false,CL_help);
		printlog("어떤 신의 보물을 달라고할까?",false,false,false,CL_help);
		int key_ = waitkeyinput();


		switch(key_)
		{
			case 'b':
			case 'B':
				next_ = GT_BYAKUREN;
				s_ = "뱌쿠렌을 선택시 무작위 마법책을 몇권 받습니다. 뱌쿠렌로부터 징벌상태가 됩니다!";
				break;
			case 'k':
			case 'K':
				next_ = GT_KANAKO;
				s_ = "카나코를 선택시 무작위 무기를 여럿을 받습니다. 카나코로부터 징벌상태가 됩니다!";
				break;
			case 'w':
			case 'W':
				next_ = GT_SUWAKO;
				s_ = "스와코를 선택시 스펠카드를 몇개 받습니다. 스와코로부터 징벌상태가 됩니다!";
				break;
			case 'a':
			case 'A':
				next_ = GT_MINORIKO;
				s_ = "미노리코를 선택시 다수의 고구마를 받습니다. 미노리코로부터 징벌상태가 됩니다!";
				break;
			case 'm':
			case 'M':
				next_ = GT_MIMA;
				s_ = "미마를 선택시 미마의 봉인서를 받습니다. 미마로부터 징벌상태가 됩니다!";
				break;
			case 'p':
			case 'P':
				next_ = GT_SHINKI;
				s_ = "신키를 선택시 영격두루마리 소량을 받습니다. 신키로부터 징벌상태가 됩니다!";
				break;
			case 'g':
			case 'G':
				next_ = GT_YUUGI;
				s_ = "유우기를 선택시 무작위 방어구를 여럿 받습니다. 유우기로부터 징벌상태가 됩니다!";
				break;
			case 'z':
			case 'Z':
				next_ = GT_SHIZUHA;
				s_ = "시즈하를 선택시 단풍브랜드의 무기를 받습니다. 시즈하로부터 징벌상태가 됩니다!";
				break;
			case 'h':
			case 'H':
				next_ = GT_HINA;
				s_ = "히나를 선택시 무작위 장신구를 여럿 받습니다. 히나로부터 징벌상태가 됩니다!";
				break;
			case 'y':
			case 'Y':
				next_ = GT_YUKARI;
				s_ = "유카리를 선택시 공간이동 소모품여럿을 받습니다. 유카리로부터 징벌상태가 됩니다!";
				break;
			case 'e':
			case 'E':
				next_ = GT_EIRIN;
				s_ = "에이린을 선택시 무작위 물약 더미를 받습니다. 에이린로부터 징벌상태가 됩니다!";
				break;
			case 'u':
			case 'U':
				next_ = GT_YUYUKO;
				s_ = "유유코를 선택시 무작위 발동템을 받습니다. 유유코로부터 징벌상태가 됩니다!";
				break;
			case 's':
			case 'S':
				next_ = GT_SATORI;
				s_ = "사토리를 선택시 식별두루마리 여럿을 받습니다. 사토리로부터 징벌상태가 됩니다!";
				break;
			case 't':
			case 'T':
				next_ = GT_TENSI;
				s_ = "텐시를 선택시 무작위 아이템을 여럿 받습니다. 텐시로부터 징벌상태가 됩니다!";
				break;
			case 'L':
			case 'l':
				next_ = GT_LILLY;
				s_ = "릴리를 선택시 탄막뭉치를 받습니다. 릴리로부터 징벌상태가 됩니다!";
				break;
			default:
				printlog(" 마음이 변하기전에 고르는게 좋을걸?",true,false,false,CL_small_danger);
				return false;
		}
		enterlog();

		printlog(s_,true,false,false,CL_small_danger);
		printlog("이 신의 보물을 요구하겠습니까? (Y/N)",true,false,false,CL_help);
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			loop_ = false;
			break;
		case 'N':
		default:
			loop_ = true;
			break;
		}

	}

	if(you.god_value[GT_SEIJA][1] &= 1 << next_)
	{
		printlog("이미 한번 보물을 받았던 신이다.",true,false,false,CL_normal);
		return false;
	}




	seija_real_gift(next_);
	
	printlog("당신의 발밑에 무언가 나타났다!",true,false,false,CL_dark_good);
	
	char temp[200];
	sprintf_s(temp,200,"세이자에게 선물을 받았다.");
	AddNote(you.turn,CurrentLevelString(),temp,CL_help);
	MoreWait();

	switch(next_)
	{
	case GT_NONE:
	case GT_BYAKUREN:
	case GT_KANAKO:
	case GT_SUWAKO:
	case GT_MINORIKO:
	case GT_MIMA:
	case GT_SHINKI:
	case GT_YUUGI:
	case GT_SHIZUHA:
	case GT_HINA:
	case GT_YUKARI:
	case GT_EIRIN:
	case GT_YUYUKO:
	case GT_SATORI:
	case GT_TENSI:
	case GT_LILLY:
		break;
	}

	you.PunishUpDown(GetGodGiftTime(GT_SEIJA)-1,next_);
	you.gift_count = GetGodGiftTime(GT_SEIJA);
	
	//중복선물방지
	you.god_value[GT_SEIJA][1] |= 1 << next_;  


	printlog(seija_talk(next_, 7-pietyLevel(you.piety)),true,false,false,CL_seija);

	you.StepUpDownPiety(-1);
	
	if(pietyLevel(you.piety) == 0)
	{

		printarray(true,false,false,CL_danger,4,"당신은 ", GetGodString(you.god),GetGodString_is(you.god)?"으로부터 ":"로부터 ","버려졌다.");
		
		char temp[200];
		sprintf_s(temp,200,"%s%s 버려졌다.",GetGodString(you.god),GetGodString_is(you.god)?"으로부터":"로부터");
		AddNote(you.turn,CurrentLevelString(),temp,CL_small_danger);
	
		for(int level_ = pietyLevel(you.piety);level_>=0;level_--)
			GetGodAbility(level_, false);	

		you.Ability(SKL_ABANDON_GOD,true,true);
		you.god = GT_NONE;	

	}

	you.Ability(SKL_SEIJA_GIFT,true,true);

	return true;
}

bool skill_seija_1(int power, bool short_, unit* order, coord_def target)
{
	if(unit* hit_mon = env[current_level].isMonsterPos(target.x,target.y,order))
	{	
		hit_mon->SetXY(you.position.x,you.position.y);
		you.SetXY(target.x,target.y);
		
		printarray(true,false,false,CL_normal,4,"당신은 ", hit_mon->GetName()->name.c_str(),hit_mon->GetName()->name_and(true),"자리를 뒤집었다.");
		hit_mon->AttackedTarget(order);
		return true;
	}
	return false;
}


bool skill_seija_2(int power, bool short_, unit* order, coord_def target)
{
	bool ok_ = false;
	int enter_ = 0;
	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(it->isLive() && env[current_level].isInSight(it->position))
		{
			int offset_ = min(4,max(-4,(you.level - it->level)));
			if(!ok_)
				printlog("세이자는 모두의 시야를 뒤집어버렸다.",true,false,false,CL_normal);

			it->SetConfuse(rand_int(20+2*offset_,5),true);
			it->hp = max(1,it->hp*rand_float(0.3f,0.7f));
			enter_++;
			if(enter_==3)
			{
				enterlog();
				enter_ = 0;
			}
			ok_ = true;
		}
	}
	if(ok_)
	{
		return true;
	}
	else
	{
		printlog("시야내에 뒤집어버릴 상대가 없다.",true,false,false,CL_normal);
		return false;	
	}
	return false;
}

bool skill_lilly_1(int power, bool short_, unit* order, coord_def target)
{
	for(int i = 0; i < 5; i++)
	{
		if(!you.god_value[GT_LILLY][i])
		{
			if(pietyLevel(you.piety) <= i)
			{
				printlog("요정을 동료로 더 권유하려면 신앙심을 더 높여야된다.",true,false,false,CL_normal);
				return false;	
			}

			
			if(monster* hit_mon =(monster*)env[current_level].isMonsterPos(target.x,target.y,order))
			{	


				if(hit_mon->flag & M_FLAG_SUMMON)
				{
					printlog("소환된 몬스터는 권유할 수 없다.",true,false,false,CL_normal);
					return false;	
				}
				if(!(hit_mon->flag & M_FLAG_FAIRY))
				{
					printlog("요정이 아니면 권유할 수 없다.",true,false,false,CL_normal);
					return false;	
				}
				if(hit_mon->id == MON_ZOMBIE_FAIRY)
				{
					printlog("이 요정은 좀비로 취직중이다. 직업을 가진 요정은 권유할 수 없다.",true,false,false,CL_normal);
					return false;
				}
				if(hit_mon->id == MON_MAID_FAIRY)
				{
					printlog("이 요정은 메이드로 취직중이다. 직업을 가진 요정은 권유할 수 없다.",true,false,false,CL_normal);
					return false;
				}
				if(hit_mon->level > you.level)
				{
					char temp[100];
					sprintf_s(temp,100,"이 요정을 권유하려면 %d레벨이상이 되어야한다.",hit_mon->level);
					printlog(temp,true,false,false,CL_normal);
					return false;
				}
				
				for(int j = 0; j < 5; j++)
				{
					if((you.lilly_allys[j].map_id == hit_mon->map_id && you.lilly_allys[j].floor == current_level) || hit_mon->flag & M_FLAG_ALLY)
					{
						printlog("이 요정은 이미 당신의 동료다.",true,false,false,CL_normal);
						return false;
					}
				}

				int person_ = randA(FP_MAX-1);

				you.lilly_allys[i].id = hit_mon->id;
				you.lilly_allys[i].map_id = hit_mon->map_id;
				you.lilly_allys[i].floor = current_level;
				you.lilly_allys[i].level = hit_mon->level;
				you.lilly_allys[i].exp = hit_mon->level<=1?0:level_up_value[hit_mon->level-2];
				bool name_ok = false;
				while(!name_ok)
				{
					name_ok = true;
					you.lilly_allys[i].name = randA(getMaxFairyName()-1);
					for(int j=0;j<5;j++)
					{
						if(i != j && you.god_value[GT_LILLY][j] && you.lilly_allys[i].name == you.lilly_allys[j].name) 
						{
							name_ok = false;
						}
					}
				}
				you.lilly_allys[i].personality = person_;
				you.lilly_allys[i].cooldown = 0;
				
				hit_mon->flag |= M_FLAG_ALLY;
				hit_mon->s_ally = -1;
				hit_mon->state.SetState(MS_FOLLOW);

				if(!(hit_mon->flag & M_FLAG_UNIQUE)) //이름 지어주기
				{
					printarray(true,false,false,CL_normal,6,hit_mon->name.name.c_str(),hit_mon->name.name_is(true),"자신의 이름이 ",fairy_name[you.lilly_allys[i].name].name.c_str(),fairy_name[you.lilly_allys[i].name].name_type?"이라고 ":"라고 ","소개했다.");
		
					hit_mon->name.name = fairy_name[you.lilly_allys[i].name].name;
					hit_mon->name.name_type = fairy_name[you.lilly_allys[i].name].name_type;

				}


				printlog(fairy_speak(hit_mon, person_, FS_ENTER),true,false,false,CL_normal);
				
				you.god_value[GT_LILLY][i] = 1;
				
				if((hit_mon->flag & M_FLAG_UNIQUE)) //이름 지어주기
				{
				char temp[200];
				sprintf_s(temp,200,"%s%s동료가 되었다.",hit_mon->name.name.c_str(),hit_mon->name.name_do(true));
				AddNote(you.turn,CurrentLevelString(),temp,CL_lilly);
				}
				else{					
					char temp[200];
					sprintf_s(temp,200,"%s(%s)%s동료가 되었다.",hit_mon->name.name.c_str(),mondata[hit_mon->id].name.name.c_str(),hit_mon->name.name_do(true));
					AddNote(you.turn,CurrentLevelString(),temp,CL_lilly);
				}

				you.Ability(SKL_LILLY_1,true,true);
				return true;
			}
			else
			{
				printlog("여기엔 몬스터가 없다.",true,false,false,CL_normal);
				return false;	
			}
		}
	}

	
	printlog("더 이상의 권유는 할 수 없다.",true,false,false,CL_normal);	
	you.Ability(SKL_LILLY_1,true,true);
	return false;
}
bool skill_lilly_2(int power, bool short_, unit* order, coord_def target)
{
	if(!order->isplayer())
		return false;
		
	int j=0;
		
	
	for(int i = 0; i < 5; i++)
	{
		if(you.god_value[GT_LILLY][i])
		{
			int k = 0;
			for(auto it = env[you.lilly_allys[i].floor].mon_vector.begin(); k == 0 && it != env[you.lilly_allys[i].floor].mon_vector.end();it++)
			{
				if(it->isLive() && (*it).isUserAlly() && it->map_id == you.lilly_allys[i].map_id)
				{
					dif_rect_iterator rit(target,2);
					for(; k == 0 && !rit.end();rit++)
					{
						if(env[current_level].isMove(rit->x, rit->y,it->isFly(),it->isSwim()) && !env[current_level].isMonsterPos(rit->x,rit->y) &&  env[current_level].isInSight(coord_def(rit->x,rit->y)) && you.position != (*rit))
						{
							if(you.lilly_allys[i].floor == current_level)
							{
								it->SetXY(rit->x,rit->y);
								it->state.SetState(MS_FOLLOW);
								k=1;
								j++;
							}
							else
							{								
								if(env[current_level].movingfloor((*rit), you.lilly_allys[i].floor, &(*it)))
								{
									it->state.SetState(MS_FOLLOW);
									k=1;
									j++;
								}
							}
						}
					}
				}
			}
		}

	}





	if(j>0)
	{
		printarray(true,false,false,CL_normal,1,"요정들을 자신의 주변으로 호출했다!");
		return true;
	}
	else
	{
		printarray(true,false,false,CL_normal,1,"호출할 요정이 없다.");
		return false;
	}


	return false;
}
bool skill_lilly_3(int power, bool short_, unit* order, coord_def target)
{
	return false;
}
bool skill_lilly_4(int power, bool short_, unit* order, coord_def target)
{
	return false;
}

bool skill_jump_attack(int power, bool short_, unit* order, coord_def target);

int UseSkill(skill_list skill, bool short_, coord_def &target)
{
	int power=min(SkillCap(skill),SkillPow(skill));
	if(SkillFlagCheck(skill, S_FLAG_SPEAK) && env[current_level].isSilence(you.position))
	{
		printlog("당신은 소리를 낼 수 없다.",true,false,false,CL_normal);
		return 0;		
	}
	
	if(SkillFlagCheck(skill,S_FLAG_DELAYED) && you.GetExhausted())
	{
		printlog("이 기술을 쓰기엔 피로가 쌓였다.",true,false,false,CL_normal);	
		return false;
	}
	if(randA_1(100) > SkillDiffer(skill))
	{
		printlog("당신은 스킬 사용에 실패했다.",true,false,false,CL_normal);
		return 2;
	}	
	if(!SkillPlusCost(skill,true))
		return 0;
	switch(skill)
	{
	case SKL_KANAKO_1:
		return skill_kanako_might(power,short_,&you,target);
		break;
	case SKL_KANAKO_2:
		return skill_kanako_2(power,short_,&you,target);
		break;
	case SKL_KANAKO_3:
		return skill_kanako_haste(power,short_,&you,target);
		break;
	case SKL_GRAZE:
		return skill_turn_graze(power,short_,&you,target);
		break;
	case SKL_GRAZE_OFF:
		return skill_off_graze(power,short_,&you,target);
		break;
	case SKL_LEVITATION:
		return skill_turn_levitation(power,short_,&you,target);
		break;
	case SKL_LEVITATION_OFF:
		return skill_off_levitation(power,short_,&you,target);
		break;
	case SKL_INVISIBLE:
		return skill_turn_invisible(power,short_,&you,target);
		break;
	case SKL_INVISIBLE_OFF:
		return skill_off_invisible(power,short_,&you,target);
		break;
	case SKL_EIRIN_0:
		return skill_eirin_throw_potion(power,short_,&you,target);
		break;
	case SKL_EIRIN_1:
		return skill_eirin_move_stat(power,short_,&you,target);
		break;
	case SKL_EIRIN_2:
		return skill_eirin_heal(power,short_,&you,target);
		break;
	case SKL_BYAKUREN_1:
		return skill_byakuren_smart(power,short_,&you,target);
		break;
	case SKL_BYAKUREN_2:
		return skill_byakuren_leg(power,short_,&you,target);
		break;
	case SKL_MINORIKO_1:
		return skill_minoriko_restore(power,short_,&you,target);
		break;
	case SKL_MINORIKO_2:
		return skill_minoriko_heal(power,short_,&you,target);
		break;
	case SKL_SIZUHA_1:
		return skill_sizuha_confuse(power,short_,&you,target);
		break;
	case SKL_SIZUHA_2:
		return skill_sizuha_autumn_armour(power,short_,&you,target);
		break;
	case SKL_SIZUHA_3:
		return sizuha_autumn_bread(power,short_,&you,target);
		break;
	case SKL_YUUGI_1:
		return skill_yuugi_drink(power,short_,&you,target);
		break;
	case SKL_YUUGI_2:
		return skill_yuugi_german(power,short_,&you,target);
		break;
	case SKL_YUUGI_3:
		return skill_yuugi_throw(power,short_,&you,target);
		break;
	case SKL_YUUGI_4:
		return skill_yuugi_shout(power,short_,&you,target);
		break;
	case SKL_YUUGI_5:
		return skill_yuugi_sambo(power,short_,&you,target);
		break;
	case SKL_SATORI_1:
		return skill_satori_trauma(power,short_,&you,target);
		break;
	case SKL_SATORI_2:
		return skill_satori_mind_reading(power,short_,&you,target);
		break;
	case SKL_SHINKI_1:
		return skill_shinki_low_demon(power,short_,&you,target);
		break;
	case SKL_SHINKI_2:
		return skill_shinki_mid_demon(power,short_,&you,target);
		break;
	case SKL_SHINKI_3:
		return skill_shinki_high_demon(power,short_,&you,target);
		break;
	case SKL_YUYUKO_ON:
		return skill_yuyuko_on(power,short_,&you,target);
		break;
	case SKL_YUYUKO_OFF:
		return skill_yuyuko_off(power,short_,&you,target);
		break;
	case SKL_YUYUKO_1:
		return skill_yuyuko_recall(power,short_,&you,target);
		break;
	case SKL_YUYUKO_2:
		return skill_yuyuko_boost(power,short_,&you,target);
		break;
	case SKL_YUYUKO_3:
		return skill_yuyuko_enslave(power,short_,&you,target);
		break;		
	case SKL_YUKARI_1:
		return skill_yukari_supporter(power,short_,&you,target);
		break;
	case SKL_YUKARI_2:
		return skill_yukari_schema(power,short_,&you,target);
		break;
	case SKL_YUKARI_3:
		return skill_yukari_shield(power,short_,&you,target);
		break;
	case SKL_YUKARI_4:
		return skill_yukari_dimension(power,short_,&you,target);
		break;
	case SKL_SWAKO_JUMP:
		return skill_swako_jump(power,short_,&you,target);
		break;
	case SKL_SWAKO_TEMPLE:
		return skill_swako_temple(power,short_,&you,target);
		break;
	case SKL_SWAKO_WATER_GUN:
		return skill_swako_water_gun(power,short_,&you,target);
		break;
	case SKL_SWAKO_TOUGUE:
		return skill_swako_tongue(power,short_,&you,target);
		break;
	case SKL_SWAKO_CURSE:
		return skill_swako_curse(power,short_,&you,target);
		break;
	case SKL_SWAKO_DIGGING:
		return skill_swako_digging(power,short_,&you,target);
		break;
	case SKL_SWAKO_SUMMON_FLOG:
		return skill_swako_summon_flog(power,short_,&you,target);
		break;
	case SKL_SWAKO_STATUE:
		return skill_swako_statue(power,short_,&you,target);
		break;
	case SKL_SWAKO_RAIN:
		return skill_swako_rain(power,short_,&you,target);
		break;
	case SKL_SWAKO_SLEEP:
		return skill_swako_sleep(power,short_,&you,target);
		break;
	case SKL_SWAKO_MISYAGUZI:
		return skill_swako_misyaguzi(power,short_,&you,target);
		break;		
	case SKL_HINA_1:
		return skill_hina_plusminus(power,short_,&you,target);
		break;
	case SKL_HINA_2:
		return skill_hina_curse_weapon(power,short_,&you,target);
		break;
	case SKL_HINA_3:
		return skill_hina_curse_armour(power,short_,&you,target);
		break;
	case SKL_HINA_4:
		return skill_hina_curse_ring(power,short_,&you,target);
		break;
	case SKL_HINA_5:
		return hina_curse_bread(power,short_,&you,target);
		break;
	case SKL_JUMPING_ATTACK:
		return skill_jump_attack(power,short_,&you, target);
		break;
	case SKL_BREATH:
		return skill_breath(power,short_,&you, target);
		break;
	case SKL_TORMENT:
		return skill_torment(power,short_,&you, target);
		break;
	case SKL_ABANDON_GOD:
		return skill_abandon_god(power,short_,&you, target);
		break;
	case SKL_SEIJA_GIFT:
		return skill_seija_gift(power,short_,&you, target);
		break;
	case SKL_SEIJA_1:
		return skill_seija_1(power,short_,&you, target);
		break;
	case SKL_SEIJA_2:
		return skill_seija_2(power,short_,&you, target);
		break;
	case SKL_LILLY_1:
		return skill_lilly_1(power,short_,&you, target);
		break;
	case SKL_LILLY_2:
		return skill_lilly_2(power,short_,&you, target);
		break;
	case SKL_LILLY_3:
		return skill_lilly_3(power,short_,&you, target);
		break;
	case SKL_LILLY_4:
		return skill_lilly_4(power,short_,&you, target);
		break;
	}
	return 0;
}


