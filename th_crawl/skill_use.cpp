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
#include "option_manager.h"
#include "soundmanager.h"
#include "tribe.h"


extern HANDLE mutx;
extern bool widesearch; //X커맨드용
extern int map_effect;

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

					soundmanager.playSound("wind");
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
		if (BaseSummon(MON_ONBASIRA, 20 + randA_1(pow), true, false, 0, order, target, SKD_SUMMON_ONBASIRA, -1)) {
			soundmanager.playSound("stone");
			return true;
		}
		else
			printlog("생성할 수 없는 위치입니다.",true,false,false,CL_normal);	

	}
	return false;
}

bool skill_kanako_haste(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		soundmanager.playSound("buff");
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
		if (you.isGrazeAmulet()) {
			printlog("아뮬렛의 힘에 의해 그레이즈는 종료 시킬 수 없다.", true, false, false, CL_normal);
			return false;
		}
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
		soundmanager.playSound("buff");
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
	soundmanager.playSound("soul_shot");
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
	length_ = min(length_,SkillLength(SKL_EIRIN_0));
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
								soundmanager.playSound("throw");
								coord_def pos = throwtanmac(27,beam,temp_infor,NULL, false);
								{
									soundmanager.playSound("bomb");
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
				changemove(-option_mg.getHeight());
			}
			else if(key_ == VK_NEXT)
			{
				changemove(option_mg.getHeight());
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


		soundmanager.playSound("buff");
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
		soundmanager.playSound("buff");
		printlog("당신은 에이린의 임시 수혈로 회복되었다.",true,false,false,CL_help);
		printlog("이 수혈은 시간이 지나면 큰 부작용을 불러올것이다!",true,false,false,CL_danger);
		you.SetEirinHeal(you.GetMaxHp()*rand_int(70,80)/100,false);
	}
	return true;
}


bool skill_byakuren_smart(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		soundmanager.playSound("buff");
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
		soundmanager.playSound("buff");
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
	soundmanager.playSound("spellcard");
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
			you.equipment[ET_ARMOR]->equip_image = &img_play_item_body[6];
			break;
		case ITM_ARMOR_BODY_ARMOUR_1:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[2];
			you.equipment[ET_ARMOR]->equip_image = &img_play_item_body[7];
			break;
		case ITM_ARMOR_BODY_ARMOUR_2:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[3];
			you.equipment[ET_ARMOR]->equip_image = &img_play_item_body[8];
			break;
		case ITM_ARMOR_BODY_ARMOUR_3:
			you.equipment[ET_ARMOR]->image = &img_item_autumn_armour[4];
			you.equipment[ET_ARMOR]->equip_image = &img_play_item_body[9];
			break;
		}
		soundmanager.playSound("buff");
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


		if(you.s_str < you.m_str)
		{
			you.StatUpDown(you.m_str-you.s_str,STAT_STR,true);
			up_ = true;
		}
		if(you.s_dex < you.m_dex)
		{
			you.StatUpDown(you.m_dex-you.s_dex,STAT_DEX,true);
			up_ = true;
		}
		if(you.s_int < you.m_int)
		{
			you.StatUpDown(you.m_int-you.s_int,STAT_INT,true);
			up_ = true;
		}
		if(up_)
		{
			soundmanager.playSound("buff");
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
						soundmanager.playSound("buff");
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
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
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
							soundmanager.playSound("potion");
							drinkpotion(PT_ALCOHOL, false);	
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
				changemove(-option_mg.getHeight());
			}
			else if(key_ == VK_NEXT)
			{
				changemove(option_mg.getHeight());
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

			soundmanager.playSound("stone");
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

				soundmanager.playSound("bomb"); 
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
		if(i==0)
			soundmanager.playSound("stone");
		else if (i == 1)
			soundmanager.playSound("bomb");
		else if (i == 2)
			soundmanager.playSound("nuke");



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

		//if(hit_mon->CalcuateMR(GetDebufPower(SKL_SATORI_1,power)))
		int percent_ = randC(2, 100);
		int debuf_pow = GetDebufPower(SKL_SATORI_1, power);
		int base = (hit_mon->GetResist() - debuf_pow);
		int base2 = (hit_mon->GetResist() - (debuf_pow-30));
		
		if (hit_mon->GetMindReading() || base2 < percent_)
		{
			soundmanager.playSound("laugh");
			hit_mon->SetFear(-1);
			you.GetExp(((monster*)hit_mon)->exper / 2);
			env[current_level].SummonClear(((monster*)hit_mon)->map_id);
		}
		else if (base < percent_)
		{
			soundmanager.playSound("laugh");
			hit_mon->SetFear(rand_int(25,40));
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
				if(you.s_confuse || you.s_paralyse || you.s_sleep < 0)
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
				soundmanager.playSound("debuf");
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
		soundmanager.playSound("summon");
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
		if(randA(99)<=3)
		{
			soundmanager.playSound("laugh");
			printarray(false,false,false,CL_danger,2,mon_->name.name.c_str(),"의 기분이 썩 좋아보이지 않는다.");				
			mon_->ReturnEnemy();			
		}
		else {
			soundmanager.playSound("summon");
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
		if(randA(99)<=(id_==MON_YUKI?5:id_==MON_MAI?5:3))
		{
			soundmanager.playSound("laugh");
			printarray(false,false,false,CL_danger,2,mon_->name.name.c_str(),"의 기분이 썩 좋아보이지 않는다.");				
			mon_->ReturnEnemy();			
		}
		else {
			soundmanager.playSound("summon");
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
		soundmanager.playSound("buff");
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
									it->FoundTarget(unit_,it->FoundTime());
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
					dq[i]->FoundTarget( unit_,dq[i]->FoundTime());
				}
				j++;
				i++;
			}
		}
		if(j>0)
		{
			soundmanager.playSound("summon");
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
		soundmanager.playSound("spellcard");
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
		soundmanager.playSound("debuf");
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
					soundmanager.playSound("summon");
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
					soundmanager.playSound("blink");
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
		soundmanager.playSound("buff");
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
		soundmanager.playSound("timestop");
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
			soundmanager.playSound("jump");
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
		soundmanager.playSound("stone");
		env[current_level].changeTile(order->position, DG_TEMPLE_SUWAKO);
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
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			soundmanager.playSound("shoot");
			throwtanmac(14, beam, temp_infor, NULL);
		}
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
				soundmanager.playSound("debuf");
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
			soundmanager.playSound("curse");
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
			if (env[current_level].dgtile[beam->x][beam->y].isBreakable())
				env[current_level].changeTile((*beam), env[current_level].base_floor);
			beam++;
			length_--;
		}
		soundmanager.playSound("stone");
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
	if (return_) {
		soundmanager.playSound("summon");
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
			soundmanager.playSound("stone");
			env[current_level].changeTile(target, DG_STATUE);
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
				env[current_level].changeTile((*rit), DG_SEA);
			}
		}
		rit++;
	}

	soundmanager.playSound("spellcard");
	printarray(true,false,false,CL_magic,1,"당신의 주변이 물바다가 되었다. ");	
	
	return true;
}
bool skill_swako_sleep(int power, bool short_, unit* order, coord_def target)
{
	soundmanager.playSound("spellcard");
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
									soundmanager.playSound("curse");
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
									soundmanager.playSound("curse");
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
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
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
				soundmanager.playSound("curse");
				printarray(true,false,false,CL_hina,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"저주의 힘으로 가득 차있다.");
				you.equipment[ET_WEAPON]->value5 = WB_CURSE;
				you.equipment[ET_WEAPON]->value6 = rand_int(80,100);
			}
			else
			{
				soundmanager.playSound("curse");
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
										soundmanager.playSound("curse");
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
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
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
										soundmanager.playSound("curse");
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
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
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

	if(you.equipment[ET_WEAPON]  && (you.equipment[ET_WEAPON]->type>=ITM_WEAPON_FIRST && you.equipment[ET_WEAPON]->type<ITM_WEAPON_LAST) && !you.equipment[ET_WEAPON]->isArtifact())
	{
		soundmanager.playSound("buff");
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

	if(you.equipment[ET_WEAPON]  && (you.equipment[ET_WEAPON]->type>=ITM_WEAPON_FIRST && you.equipment[ET_WEAPON]->type<ITM_WEAPON_LAST) && !you.equipment[ET_WEAPON]->isArtifact())
	{
		soundmanager.playSound("curse");
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
		
		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			soundmanager.playSound("fire");
			throwtanmac(graphic_, beam, temp_infor, NULL);
		}
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
			soundmanager.playSound("sickle");
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

	bool junko_ = you.god_value[GT_JUNKO][3] != 0 && you.god == GT_JUNKO;
	for (int i = 0; i < (junko_ ? 2 : 1); i++)
	{
		if (i == 1)
			printlog("순호는 이미 순화된 당신을 언제든지 죽일 수 있다. 정말로 죽을거야?(Y/N)", false, false, false, CL_danger);
		else if (sanae_)
			printlog("신을 버리면 당신의 신앙심은 전부 사라질것이다. 진짜로?(Y/N)", false, false, false, CL_danger);
		else
			printlog("신을 버리면 당신은 신의 노여움을 살 것이다. 진짜로?(Y/N)", false, false, false, CL_danger);
		switch (waitkeyinput())
		{
		case 'Y':
		case 'y':
			enterlog();
			break;
		case 'N':
		default:
			printlog(" 취소!", true, false, false, CL_normal);
			return false;
		}
	}



	if (sanae_)
		printarray(true, false, false, CL_danger, 7, "당신은 ", GetGodString(you.god), GetGodString_is(you.god) ? "을 " : "를 ", "버렸다. ", GetGodString(you.god), GetGodString_is(you.god) ? "은 " : "는 ", "당신의 독립을 눈물을 머금고 이해했다.");
	else
		printarray(true, false, false, CL_danger, 4, "당신은 ", GetGodString(you.god), GetGodString_is(you.god) ? "을 " : "를 ", you.god == GT_SATORI ? "버렸다." : "버렸다. 당신의 신은 분노했다!");


	if (!sanae_)
	{
		you.PunishUpDown(30, you.god, true);
	}

	char temp[200];
	sprintf_s(temp, 200, "%s%s 버렸다.", GetGodString(you.god), GetGodString_is(you.god) ? "을" : "를");
	AddNote(you.turn, CurrentLevelString(), temp, CL_small_danger);



	for (int level_ = pietyLevel(you.piety); level_ >= 0; level_--)
		GetGodAbility(level_, false);


	if (you.god == GT_SATORI)
	{
		you.god_value[GT_SATORI][0] = 1;
	}
	if (you.god == GT_SEIJA)
		printlog(seija_talk(GT_NONE, 7), true, false, false, CL_seija);

	GodAccpect_Abandon(you.god);

	you.Ability(SKL_ABANDON_GOD, true, true);
	godAutoPickUp(you.god, false);





	you.god = GT_NONE;

	if (junko_) {
		you.HpUpDown(-you.GetMaxHp(), DR_JUNKO, NULL);
	}


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

		soundmanager.playSound("blink");
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
		soundmanager.playSound("laugh");
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
				soundmanager.playSound("warning");
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

				if(hit_mon->CanSpeak())
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

				if(hit_mon->id == MON_SUNNY || hit_mon->id == MON_LUNAR || hit_mon->id == MON_STAR)
				{//삼월정 특수 대사!					
					for(auto it = env[you.lilly_allys[i].floor].mon_vector.begin(); it != env[you.lilly_allys[i].floor].mon_vector.end();it++)
					{
						if(it->isLive() && (it->id == MON_SUNNY || hit_mon->id == MON_LUNAR || hit_mon->id == MON_STAR) &&
							!(*it).isUserAlly()  &&  env[current_level].isInSight(coord_def(it->position.x,it->position.y)) && it->CanSpeak())
						{

							switch(it->id)
							{
							case MON_SUNNY:
								if(hit_mon->id == MON_LUNAR)
									printarray(true,false,false,CL_normal,3,it->GetName()->name.c_str(),it->GetName()->name_is(true),"외쳤다. \"포기가 빠르다고 루나!\"");
								else if(hit_mon->id == MON_STAR)
									printarray(true,false,false,CL_normal,3,it->GetName()->name.c_str(),it->GetName()->name_is(true),"외쳤다. \"스타?!\"");
								break;
							case MON_LUNAR:
								if(hit_mon->id == MON_SUNNY)
									printarray(true,false,false,CL_normal,3,it->GetName()->name.c_str(),it->GetName()->name_is(true),"외쳤다. \"써니? 농담이지?\"");
								else if(hit_mon->id == MON_STAR)
									printarray(true,false,false,CL_normal,3,it->GetName()->name.c_str(),it->GetName()->name_is(true),"외쳤다. \"어? 스타, 진심이야?\"");
								break;
							case MON_STAR:
								if(hit_mon->id == MON_SUNNY)
									printarray(true,false,false,CL_normal,3,it->GetName()->name.c_str(),it->GetName()->name_is(true),"외쳤다. \"우릴 배신하는거야 써니?\"");
								else if(hit_mon->id == MON_LUNAR)
									printarray(true,false,false,CL_normal,3,it->GetName()->name.c_str(),it->GetName()->name_is(true),"외쳤다. \"속지마 루나!\"");
							}
						}
					}
				}



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
				if(it->isLive() && it->map_id == you.lilly_allys[i].map_id)
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
		soundmanager.playSound("summon");
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
	
	if(monster* hit_mon =(monster*)env[current_level].isMonsterPos(target.x,target.y,order))
	{	
		
		for(int i = 0; i < 5; i++)
		{
			if(you.god_value[GT_LILLY][i]==1)
			{
				if(hit_mon->isLive() && hit_mon->id == you.lilly_allys[i].id && hit_mon->map_id == you.lilly_allys[i].map_id)
				{
					if(hit_mon->hp >= hit_mon->max_hp)
					{
						printarray(true,false,false,CL_normal,1,"이 요정은 이미 체력이 가득 차있다.");
						return false;
					}
					if(!hit_mon->isUserAlly())
					{						
						printarray(true,false,false,CL_normal,1,"이 요정은 지금 당신에게 적대적이다.");
						return false;
					}
					soundmanager.playSound("buff");
					
					hit_mon->HpUpDown(max(1,hit_mon->max_hp*rand_int(10,35)/100),DR_NONE);
					printarray(true,false,false,CL_lilly,3,hit_mon->name.name.c_str(),hit_mon->name.name_is(true),"봄의 기운을 받아 체력이 회복되었다.");
		
					return true;
				}
			}
		}	
	}
	
	
	printarray(true,false,false,CL_normal,1,"동료 요정을 대상으로 선택해야한다.");
	return false;

}
bool skill_lilly_4(int power, bool short_, unit* order, coord_def target)
{
	bool speak_ = false;

	random_extraction<int> rand_;
	rand_.push(0);
	rand_.push(1);
	rand_.push(2);
	rand_.push(3);
	rand_.push(4);
	for(int i = 0; i<5;i++)
	{
		int next_ = rand_.pop();
		if(you.god_value[GT_LILLY][next_] == 1)
		{
			for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end();it++)
			{
				if(it->isLive() && (*it).isUserAlly() && it->map_id == you.lilly_allys[next_].map_id && current_level == you.lilly_allys[next_].floor  &&  env[current_level].isInSight(coord_def(it->position.x,it->position.y)))
				{
					if(!speak_)
					{ 
						printarray(true,false,false,CL_lilly,1,"당신은 자신의 힘을 요정들에게 나눠주었다!");
						if(it->CanSpeak())
							printlog(fairy_speak(&(*it), you.lilly_allys[next_].personality, FS_FAIRY_WAR),true,false,false,CL_normal);
					}
					speak_ = true;
					it->SetForceStrong(true, rand_int(40,60),true);
					break;
				}
			}
		}
	}
	enterlog();
	if(speak_)
	{
		soundmanager.playSound("spellcard");
		you.SetForceStrong(false, rand_int(20,40),true);
		return true;
	}

	
	printarray(true,false,false,CL_normal,1,"주변에 힘을 전달할 동료 요정이 없다.");
	return false;
}



bool skill_okina_1(int power, bool short_, unit* order, coord_def target)
{
	if (current_level == OKINA_LEVEL){
		printlog("이 장소에선 문을 만들 수 없다.", true, false, false, CL_normal);
		return false;
	}
	if (order->isplayer())
	{
		if (env[current_level].dgtile[target.x][target.y].isBreakable() && !env[current_level].dgtile[target.x][target.y].isCloseDoor()) {


			beam_iterator beam(order->position, order->position);
			if (CheckThrowPath(order->position, target, beam))
			{
				beam.init();
				while (!beam.end())
				{
					beam_iterator temp = beam;
					temp++;
					unit *unit_ = env[current_level].isMonsterPos(temp->x, temp->y, &you);
					if (unit_)
					{
						printlog("사이에 장애물이 있다.", true, false, false, CL_normal);
						return false;
					}
					beam++;
				}

				printarray(true, false, false, CL_okina, 3, "당신은 ", dungeon_tile_tribe_type_string[env[current_level].dgtile[target.x][target.y].tile], " 타일을 문으로 만들었다.");

				soundmanager.playSound("stone");
				env[current_level].changeTile(target, DG_CLOSE_DOOR);
				return true;
			}
			else {
				printlog("사이에 장애물이 있다.", true, false, false, CL_normal);
				return false;
			}

		}
		else {
			printlog("벽을 대상으로 써야 한다.", true, false, false, CL_normal);
			return false; //해당 위치에 몬스터가 없다.

		}
	}
	return false;
}
bool skill_okina_2(int power, bool short_, unit* order, coord_def target)
{
	if (order->isplayer())
	{
		unit *unit_ = env[current_level].isMonsterPos(target.x, target.y, &you);
		if (unit_ && unit_->GetId() == MON_CLOSE_DOOR) {
			printlog("이미 잠겨있는 문이다.", false, false, false, CL_normal);
			return false;
		}

		if (env[current_level].dgtile[target.x][target.y].isOpenDoor() || env[current_level].dgtile[target.x][target.y].isCloseDoor()) {

			if (unit_) {

				rand_rect_iterator rit(unit_->position, 1, 1, true);
				while (!rit.end()) {
					unit* unit_hit_ = NULL; //부딪힌 적
					bool hit_ = false; //부딪혔다!

					hit_ = !env[current_level].isMove(coord_def(rit->x, rit->y), unit_->isFly(), unit_->isSwim(), false);
					unit_hit_ = env[current_level].isMonsterPos(rit->x, rit->y);

					if (!hit_ && !unit_hit_) {
						//움직일수도있을때
						printarray(false, false, false, CL_normal, 3, unit_->GetName()->name.c_str(), unit_->GetName()->name_is(true), "문에 밀쳐져 튕겨나갔다!");
						unit_->SetXY(rit->x, rit->y);
						attack_infor temp_att(randC(2, 3 + power / 10), 2*( 3 + (power / 10)), 99, unit_, order->GetParentType(), ATT_RUSH, name_infor("문", true));
						unit_->damage(temp_att, true);
						unit_->SetConfuse(5+randA(5));
						unit_->PlusTimeDelay(-unit_->GetWalkDelay()); //1턴 행동을 쉰다.
						break;
					}

					rit++;
					if (rit.end()) {
						printarray(true, false, false, CL_normal, 4, "밀쳐낼 자리가 없어서 문 위에 있는 ", unit_->GetName()->name.c_str(), unit_->GetName()->name_to(true), "밀쳐낼 수 없다.");
						return false;
					}
				}

			}
			env[current_level].changeTile(target, env[current_level].base_floor, true);
			//적이 서있으면 강제로 비키도록 한다.
			
			if (monster *mon_ = BaseSummon(MON_CLOSE_DOOR, 30 + randA_1(power / 10), true, false, 0, order, target, SKD_OTHER, -1))
			{
				soundmanager.playSound("block");
				mon_->LevelUpdown(you.level, 6);
				printarray(true, false, false, CL_okina, 1, "당신은 문을 강제로 단단하게 잠갔다!");
				return true;
			}
		}
		else {
			printlog("문을 대상으로 사용해야 한다.", true, false, false, CL_normal);
			return false;
		}
	}
	return false;
}
bool skill_okina_3(int power, bool short_, unit* order, coord_def target)
{
	if (current_level == OKINA_LEVEL){
		printlog("이 장소에선 문을 만들 수 없다.", true, false, false, CL_normal);
		return false;
	}
	if (order->isplayer())
	{
		monster* this_unit_ = (monster*)env[current_level].isMonsterPos(target.x, target.y, &you);
		if (!this_unit_ || this_unit_->isUserAlly())
		{
			printlog("적 몬스터를 대상으로 써야한다.", true, false, false, CL_normal);
			return false; //해당 위치에 몬스터가 없다.
		}

		beam_iterator beam(order->position, order->position);
		if (CheckThrowPath(order->position, target, beam))
		{
			while (!beam.end() && !env[current_level].isMonsterPos(beam->x, beam->y, &you))
			{
				beam++;
			}

			unit *unit_ = env[current_level].isMonsterPos(beam->x, beam->y, &you);
			if (!unit_) {
				printlog("해당 적에게 올바른 경로를 설정할 수 없다.", true, false, false, CL_danger);
				return false;
			}

			beam++;

			unit *unit2_ = env[current_level].isMonsterPos(beam->x, beam->y, &you);
			if (unit2_) {
				printlog("적의 등 뒤에 문을 설치할 수 없다.", true, false, false, CL_normal);
				return false;
			}
			if (!(env[current_level].dgtile[order->position.x][order->position.y].isFloor() ||
				env[current_level].dgtile[order->position.x][order->position.y].isDoor() ||
				env[current_level].dgtile[order->position.x][order->position.y].isTemple()) &&
				!env[current_level].dgtile[beam->x][beam->y].isBreakable()
				)
			{
				printlog("적의 등 뒤에 문을 설치할 수 없다.", true, false, false, CL_normal);
				return false;
			}

			soundmanager.playSound("blink");
			env[current_level].changeTile((*beam), DG_OPEN_DOOR);
			you.SetXY(beam->x, beam->y);
			unit_->LostTarget();
			printlog("적의 등 뒤의 문으로 빠져나왔다!", true, false, false, CL_okina);
			return true;
		}
		printlog("사이에 장애물이 있다.", true, false, false, CL_normal);
		return false;
	}
	return false;
}
bool skill_okina_4(int power, bool short_, unit* order, coord_def target)
{
	if (current_level == OKINA_LEVEL){
		printlog("이 곳에서는 백댄서를 소환할 필요가 없다.", true, false, false, CL_normal);
		return false;
	}
	int num_ = 1;
	int id_ = MON_MAI2;
	bool loop_ = true;
	while (loop_) {
		printlog("어느 백댄서를 호출하시겠습니까?", true, false, false, CL_help);
		printlog("a - 테이레이다 마이: 뒤에서 춤추는 것으로 체력을 회복시켜준다.", true, false, false, CL_okina);
		printlog("b -   니시다 사토노: 뒤에서 춤추는 것으로 영력을 회복시켜준다.", true, false, false, CL_okina);
		printlog("c -   백댄서즈 소환: 두명을 모두 소환한다. (신앙심소모 2배)", true, false, false, CL_okina);
		switch (waitkeyinput())
		{
		case 'a':
		case 'A':
			id_ = MON_MAI2;
			loop_ = false;
			break;
		case 'b':
		case 'B':
			id_ = MON_SATONO;
			loop_ = false;
			break;
		case 'c':
		case 'C':
			num_ = 2;
			loop_ = false;
			break;
		default:
			break;
		case VK_ESCAPE:
			printlog("취소하였다.", true, false, false, CL_normal);
			return false;
		}
	}


	bool return_ = false;
	monster* speak_ = NULL;
	for (int i = 0; i < num_; i++) {
		if (monster* mon_ = BaseSummon(id_, rand_int(40, 50), true, false, 2, order, target, id_ == MON_MAI2 ? SKD_SUMMON_MAI : SKD_SUMMON_SATONO, 1))
		{
			if (mon_)
				return_ = true;
			mon_->LevelUpdown(you.level, 6);
			printarray(false, false, false, CL_magic, 3, mon_->name.name.c_str(), mon_->name.name_do(true), "당신에게 소환되었다. ");
			if (!speak_ && mon_->isLive() && (*mon_).isUserAlly() && env[current_level].isInSight(coord_def(mon_->position.x, mon_->position.y)) && mon_->CanSpeak()) {
					speak_ = mon_;
			}
		}
		if (num_ == 2)
		{
			id_ = MON_SATONO;
			you.PietyUpDown(-4);
		}
	}

	enterlog();
	if (speak_)
	{
		soundmanager.playSound("summon");
		if (speak_->GetId() == MON_MAI2) {
			printarray(true, false, false, CL_normal, 3, speak_->GetName()->name.c_str(), speak_->GetName()->name_is(true), "외쳤다. \"그럼 바로 응원을 시작하겠어!\"");
		}
		else if (speak_->GetId() == MON_SATONO) {
			printarray(true, false, false, CL_normal, 3, speak_->GetName()->name.c_str(), speak_->GetName()->name_is(true), "외쳤다. \"뒤에서 응원할게!\"");
		}
	}

	return return_;
}
bool skill_okina_5(int power, bool short_, unit* order, coord_def target)
{
	if (current_level == OKINA_LEVEL){
		printlog("이 곳은 이미 뒷 문의 세계다.", true, false, false, CL_normal);
		return false;
	}

	if (env[current_level].dgtile[order->position.x][order->position.y].isFloor() ||
		env[current_level].dgtile[order->position.x][order->position.y].isDoor() ||
		env[current_level].dgtile[order->position.x][order->position.y].isTemple()) {
		env[current_level].changeTile(order->position, DG_OPEN_DOOR);
	}
	else {
		printlog("이 곳에는 문을 열만한 공간이 없다!", true, false, false, CL_normal);
		return false;
	}

	//log에 오키나레벨로 도착함을 저장
	deque<monster*> dq;
	soundmanager.playSound("blink");
	printlog("당신은 등 뒤의 문을 열고 도망쳤다!", true, false, false, CL_okina);
	for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (it->isLive() && distan_coord(it->position, you.position) <= 2 && it->CanChase())
		{
			dq.push_back(&(*it));
		}
	}
	rand_shuffle(dq.begin(), dq.end());
	MoreWait();
	you.god_value[GT_OKINA][0] = current_level;
	you.god_value[GT_OKINA][1] = you.position.x;
	you.god_value[GT_OKINA][2] = you.position.y;
	env[OKINA_LEVEL].EnterMap(0, dq);
	printarray(true, false, false, CL_normal, 2, "이 곳은 문 뒤의 세계다. ", randA(2)?randA(1)?
		"푹 쉬다 가도록! ":"환영하네! ":"여기는 안전해보인다. ");


	char temp2[200];
	sprintf_s(temp2, 200, "%s로 도망쳤다.", CurrentLevelString(current_level));
	AddNote(you.turn, CurrentLevelString(current_level), temp2, CL_normal);
	//you.resetLOS(false);
	return true;
}
bool skill_junko_1(int power, bool short_, unit* order, coord_def target)
{
	if (order->position == target)
	{
		printlog("자살할거야?", true, false, false, CL_small_danger);
		return false;
	}
	beam_iterator beam(order->position, order->position);
	int damage_ = 4 + power / 10;
	int multi_ = 4;
	int hit_ = 10 + power / 15;
	if (CheckThrowPath(order->position, target, beam))
	{
		beam_infor temp_infor(randC(multi_, damage_), multi_ * (damage_), hit_, order, order->GetParentType(), SkillLength(SKL_JUNKO_1), 1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor("탄막", true));
		if (short_)
			temp_infor.length = ceil(GetPositionGap(order->position.x, order->position.y, target.x, target.y));


		for (int i = 0; i < (order->GetParadox() ? 2 : 1); i++) {
			soundmanager.playSound("shoot");
			throwtanmac(rand_int(10, 15), beam, temp_infor, NULL);
		}
		order->SetParadox(0);
		you.SetPureTurn(5, rand_int(20, 30));
		return true;
	}
	return false;
}
bool skill_junko_2(int power, bool short_, unit* order, coord_def target)
{
	if (order->isplayer())
	{
		soundmanager.playSound("buff");
		int time_ = 25 + power / 5 + randA_1(power / 2);
		you.SetMight(time_);
		you.SetPureTurn(10, time_);
		return true;
	}
	return false;
}

bool skill_junko_3(int power, bool short_, unit* order, coord_def target)
{
	if (order->isplayer())
	{
		bool least_one = false;
		for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
		{
			if (it->isLive() && env[current_level].isInSight(it->position) && !it->isUserAlly())
			{
				least_one = true;
				break;
			}
		}
		if (!least_one)
		{
			printlog("시야에 살의를 표출할 적이 있어야 한다. ", true, false, false, CL_normal);
			return false;
		}
		soundmanager.playSound("buff");
		int time_ = 25 + power / 5 + randA_1(power / 2);
		you.SetPureHaste(time_);
		you.SetPureTurn(20, time_);
		return true;
	}
	return false;
}
const char* getJunkoString(int kind_)
{
	switch (kind_)
	{
	case 1:
		return "스킬순화: 선택한 적성0 이상의 스킬의 레벨이 캐릭터 레벨과 항상 같아진다.";
	case 2:
		return "저항순화: 선택한 속성에 대해 면역이 된다.";
	case 3:
		return "마력순화: 체력과 영력이 동일시 되며 회복력이 합쳐진다.";
	case 4:
		return "파워순화: 항상 풀파워가 되며 떨어지지 않는다.";
	case 5:
		return "생명순화: 추가 목숨을 2개 얻는다.";
	case 6:
		return "장비순화: 선택한 장비의 강화치가 최대 강화치+5가 된다. 아티펙트도 가능.";
	}

	return "버그순화: 버그이므로 이걸 선택하면 안된다.";
}
bool skill_junko_4(int power, bool short_, unit* order, coord_def target)
{

	int kind_ = 0;
	bool loop_ = true;
	printlog("순화의 축복은 권능을 사용할 수 없게되며 영구적인 순화 패널티를 얻게된다.", true, false, false, CL_danger);
	printlog("또한 한번 고른 순화는 되돌릴 수 없다. 신중하게 결정하길!", true, false, false, CL_danger);
	while (loop_) {
		printlog("어떤 능력을 순화하겠습니까?", true, false, false, CL_help);
		printarray(true, false, false, CL_junko, 2, "a - ", getJunkoString(you.god_value[GT_JUNKO][0]));
		printarray(true, false, false, CL_junko, 2, "b - ", getJunkoString(you.god_value[GT_JUNKO][1]));
		printarray(true, false, false, CL_junko, 2, "c - ", getJunkoString(you.god_value[GT_JUNKO][2]));
		switch (waitkeyinput())
		{
		case 'a':
		case 'A':
			kind_ = you.god_value[GT_JUNKO][0];
			loop_ = false;
			break;
		case 'b':
		case 'B':
			kind_ = you.god_value[GT_JUNKO][1];
			loop_ = false;
			break;
		case 'c':
		case 'C':
			kind_ = you.god_value[GT_JUNKO][2];
			loop_ = false;
			break;
		default:
			break;
		case VK_ESCAPE:
			printlog("취소하였다.", true, false, false, CL_normal);
			return false;
		}
	}
	if (kind_ == 0)
	{
		printlog("알 수 없는 선택", true, false, false, CL_normal);
		return false;
	}

	switch (kind_)
	{
	case 1: //스킬순화
		while (true)
		{
			view_skill("어떤 스킬을 순화할거지?");
			int move_ = 1;
			int key_ = waitkeyinput(true);
			if ((key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z'))
			{
				int num = (key_ >= 'a' && key_ <= 'z') ? key_ - 'a' : key_ - 'A' + 26;
				if (num < SKT_MAX && you.GetSkillLevel(num, false) < 27 && !you.cannotSkillup(num))
				{
					if (you.skill[num].aptit < 0)
					{
						changedisplay(DT_GAME);
						printlog("적성이 0이상인 스킬만 선택할 수 있다!", true, false, false, CL_warning);
						MoreWait();
					}
					else
					{
						char temp[100];
						sprintf_s(temp, 100, "정말 %s 스킬을 순화할거야? (현재 레벨 %d) (y/n)", skill_string((skill_type)num), you.GetSkillLevel(num, false));

						printlog(temp, true, false, true, CL_danger);
						changedisplay(DT_GAME);

						int key_ = waitkeyinput(true);
						if (key_ == 'y' || key_ == 'Y')
						{
							you.SetPureSkill(num);
							sprintf_s(temp, 100, "순호는 당신의 %s 스킬을 순화하였다! ", skill_string((skill_type)num));
							printlog(temp, true, false, false, CL_junko);
							sprintf_s(temp, 100, "순호로부터 스킬순화(%s) 축복", skill_string((skill_type)num));
							AddNote(you.turn, CurrentLevelString(), temp, CL_junko);
							break;
						}
					}
				}
				else
				{
					printlog("이 스킬은 순화할 수 없어", true, false, false, CL_normal);
					changedisplay(DT_GAME);
					return false;
				}
			}
			else
			{
				printlog("취소하였다. 신중하게 고민하도록", true, false, false, CL_normal);
				changedisplay(DT_GAME);
				return false;
			}
		}
		break;
	case 2:
	{
		printlog("어떤 저항을 순화할거지?", true, false, false, CL_junko);
		printlog("a-화염 b-냉기 c-전기", true, false, false, CL_junko);

		int key_ = waitkeyinput(true);
		switch (key_)
		{
		case 'a':
			you.DeleteProperty(TPT_FIRE_RESIST);
			you.SetProperty(TPT_FIRE_IMUNE, 200);
			printlog("순호는 당신의 화염에 대한 저항을 순화하였다!", true, false, false, CL_junko);
			AddNote(you.turn, CurrentLevelString(), "순호로부터 저항순화(화염) 축복", CL_junko);
			break;
		case 'b':
			you.DeleteProperty(TPT_COLD_RESIST);
			you.SetProperty(TPT_COLD_IMUNE, 200);
			printlog("순호는 당신의 냉기에 대한 저항을 순화하였다!", true, false, false, CL_junko);
			AddNote(you.turn, CurrentLevelString(), "순호로부터 저항순화(냉기) 축복", CL_junko);
			break;
		case 'c':
			you.DeleteProperty(TPT_ELEC_RESIST);
			you.SetProperty(TPT_ELEC_IMUNE, 200);
			printlog("순호는 당신의 전기에 대한 저항을 순화하였다!", true, false, false, CL_junko);
			AddNote(you.turn, CurrentLevelString(), "순호로부터 저항순화(전기) 축복", CL_junko);
			break;
		default:
			printlog("취소하였다. 신중하게 고민하도록", true, false, false, CL_normal);
			changedisplay(DT_GAME);
			return false;
		}
		break;
	}
	case 3:
		you.SetProperty(TPT_PURE_MP, 1);
		printlog("순호는 당신의 마력을 순화하였다!", true, false, false, CL_junko);
		AddNote(you.turn, CurrentLevelString(), "순호로부터 마력순화 축복", CL_junko);
		break;
	case 4:
		you.SetProperty(TPT_PURE_POWER, 1);
		iden_list.autopickup[IDEN_CHECK_ETC_START] = false;
		printlog("순호는 당신의 파워를 순화하였다!", true, false, false, CL_junko);
		AddNote(you.turn, CurrentLevelString(), "순호로부터 파워순화 축복", CL_junko);
		break;
	case 5:
		you.SetProperty(TPT_PURE_LIFE, 2);
		printlog("순호는 당신의 생명력을 순화하였다!", true, false, false, CL_junko);
		AddNote(you.turn, CurrentLevelString(), "순호로부터 생명순화 축복", CL_junko);
		break;
	case 6:
		while (1)
		{
			view_item(IVT_PURE_ITEM, "무슨 아이템을 순화할거야?");
			int key_ = waitkeyinput(true);
			if ((key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z'))
			{
				item *item_ = you.GetItem(key_);
				if (item_)
				{
					if ((item_->type >= ITM_WEAPON_FIRST && item_->type < ITM_WEAPON_LAST) || (item_->type >= ITM_ARMOR_FIRST && item_->type < ITM_ARMOR_LAST))
					{
						char temp[100];
						sprintf_s(temp, 100, "정말 %s 아이템을 순화할거야? (y/n)", item_->GetName().c_str());
						printlog(temp, true, false, true, CL_small_danger);
						changedisplay(DT_GAME);

						int key_ = waitkeyinput(true);
						if (key_ == 'y' || key_ == 'Y')
						{
							sprintf_s(temp, 100, "순호는 당신의 %s 아이템을 순화하였다! ", item_->GetName().c_str());
							printlog(temp, true, false, false, CL_junko);
							sprintf_s(temp, 100, "순호로부터 아이템순화(%s) 축복", item_->GetName().c_str());
							AddNote(you.turn, CurrentLevelString(), temp, CL_junko);

							if (item_->type >= ITM_WEAPON_FIRST && item_->type < ITM_WEAPON_LAST)
							{
								item_->value4 = 14;
							}
							else if (item_->type >= ITM_ARMOR_FIRST && item_->type < ITM_ARMOR_LAST)
							{
								int value_;
								if (item_->type >= ITM_ARMOR_BODY_FIRST && item_->type < ITM_ARMOR_BODY_LAST)
									value_ = item_->value1 + 5 - item_->value4;
								else if (item_->type == ITM_ARMOR_SHIELD)
									value_ = (item_->value1 <= 4 ? 3 : (item_->value1 <= 8 ? 6 : 9)) - item_->value4;
								else
									value_ = 7 - item_->value4;

								if (item_->type != ITM_ARMOR_SHIELD)
								{
									if (you.equipment[item_->GetArmorType()] == item_)
										you.AcUpDown(0, value_);
								}
								else
								{
									if (you.equipment[item_->GetArmorType()] == item_)
										you.ShUpDown(0, value_);
								}
								item_->value4 += value_;
							}
							item_->curse = false;
							item_->identify_curse = true;
							break;
						}
					}
					else
					{
						printlog("이 아이템은 순화할 수 없다.", true, false, false, CL_normal);
						changedisplay(DT_GAME);
						return false;
					}

				}
			}
			else if (key_ == VK_DOWN)//-----이동키-------
			{
				changemove(32);  //위
			}
			else if (key_ == VK_UP)
			{
				changemove(-32); //아래
			}
			else if (key_ == VK_PRIOR)
			{
				changemove(-option_mg.getHeight());
			}
			else if (key_ == VK_NEXT)
			{
				changemove(option_mg.getHeight());
			}						//-----이동키끝-------
			else if (key_ == '*')
			{
				view_item(IVT_SELECT, "무슨 아이템을 순화할거야?");
			}
			else if (key_ == VK_ESCAPE)
			{
				printlog("취소하였다. 신중하게 고민하도록", true, false, false, CL_normal);
				changedisplay(DT_GAME);
				return false;
			}
		}
		changedisplay(DT_GAME);
		break;
	}




	soundmanager.playSound("levelup");
	printlog("순호: 나의 축복을 받도록 해!", true, false, false, CL_junko);
	you.god_value[GT_JUNKO][3] = kind_;
	you.Ability(SKL_JUNKO_1, true, true);
	you.Ability(SKL_JUNKO_2, true, true);
	you.Ability(SKL_JUNKO_3, true, true);
	you.Ability(SKL_JUNKO_4, true, true);
	you.StatUpDown(5, STAT_STR);
	you.StatUpDown(5, STAT_DEX);
	you.StatUpDown(5, STAT_INT);
	you.SetPureTurn(30, -1);


	return true;
}


bool skill_joon_and_sion_1(int power, bool short_, unit* order, coord_def target)
{
	int god_ = 0;
	bool loop_ = true;
	while (loop_) {
		printlog("어느 신을 빙의할거지?", true, false, false, CL_help);
		printlog("a - 요리가미 죠온: 빙의시 즉시 파워를 가득 채워준다. 다만 해제시엔 낭비된다.", true, false, false, CL_joon);
		printlog("                   또한 소모품을 사용하면 무조건 2~3개씩 낭비한다.", true, false, false, CL_joon);
		printlog("b - 요리가미 시온: 빙의시 즉시 체력과 영력을 회복한다. 버린 소모품이 사라짐.", true, false, false, CL_sion);
		printlog("                   땅에 떨어진 소모품 고갈속도증가. 파워패널티를 받지않는다.", true, false, false, CL_sion);
		switch (waitkeyinput())
		{
		case 'a':
		case 'A':
			god_ = 1;
			loop_ = false;
			break;
		case 'b':
		case 'B':
			god_ = 2;
			loop_ = false;
			break;
		default:
			break;
		case VK_ESCAPE:
			printlog("취소하였다.", true, false, false, CL_normal);
			return false;
		}
	}
	int level_ = pietyLevel(you.piety);
	if (god_ == 1) {
		map_effect = 2;
		Sleep(500);
		map_effect = 0;

		switch (randA(3)) {
		case 0:
			printlog("죠온: 송두리채 빼앗아라!", true, false, false, CL_joon);
			break;
		case 1:
			printlog("죠온: 값 나가는건 모조리 훔쳐!", true, false, false, CL_joon);
			break;
		case 2:
			printlog("죠온: 힘을 줄테니 모두 나에게 바치는거야!", true, false, false, CL_joon);
			break;
		case 3:
			printlog("죠온: 수금 시간이야!", true, false, false, CL_joon);
			break;
		}

		soundmanager.playSound("buff");
		you.god_value[GT_JOON_AND_SION][0] = 1;
		you.god_value[GT_JOON_AND_SION][1] = rand_int(150, 200);
		you.Ability(SKL_JOON_AND_SION_1, true, true);
		you.Ability(SKL_JOON_AND_SION_OFF, true, false);
		if (level_ >= 5 && !you.GetPunish(GT_JOON_AND_SION))
		{
			you.Ability(SKL_JOON_AND_SION_2, true, false);
		}
		if (level_ >= 6 && !you.GetPunish(GT_JOON_AND_SION))
		{
			you.Ability(SKL_JOON_AND_SION_4, true, false);
		}
		you.PowUpDown(500);
	}
	else if (god_ == 2) {
		map_effect = 3;
		Sleep(500);
		map_effect = 0;
		switch (randA(3)) {
		case 0:
			printlog("시온: 자, 이제 베풀어주지 않을래?", true, false, false, CL_sion);
			break;
		case 1:
			printlog("시온: 가난은 더 이상 싫어!", true, false, false, CL_sion);
			break;
		case 2:
			printlog("시온: 최흉최악은 나 혼자로도 충분해!", true, false, false, CL_sion);
			break;
		case 3:
			printlog("시온: 모두가 평등하게 불행한 시대가 올거야", true, false, false, CL_sion);
			break;
		}
		soundmanager.playSound("buff");
		you.god_value[GT_JOON_AND_SION][0] = 2;
		you.god_value[GT_JOON_AND_SION][1] = rand_int(150, 200);
		you.Ability(SKL_JOON_AND_SION_1, true, true);
		you.Ability(SKL_JOON_AND_SION_OFF, true, false);
		if (level_ >= 5 && !you.GetPunish(GT_JOON_AND_SION))
		{
			you.Ability(SKL_JOON_AND_SION_3, true, false);
		}
		if (level_ >= 6 && !you.GetPunish(GT_JOON_AND_SION))
		{
			you.Ability(SKL_JOON_AND_SION_4, true, false);
		}

		int bonus_ = 70 + power/2;
		int heal_ = rand_int(10, 20) + order->GetMaxHp()*rand_float(0.15f, 0.25f);
		heal_ = heal_ * bonus_ / 100;
		order->HpUpDown(heal_ , DR_NONE);

		heal_ = rand_int(5, 10) + order->GetMaxHp()*rand_float(0.2f, 0.4f);
		heal_ = heal_ * bonus_ / 100;
		you.MpUpDown(heal_);
	}

	return true;
}

bool skill_joon_and_sion_2(int power, bool short_, unit* order, coord_def target)
{
	bool ok_ = false;
	int enter_ = 0;
	for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (it->isLive() && !it->isUserAlly() && env[current_level].isInSight(it->position))
		{
			if (!ok_) {
				soundmanager.playSound("bomb");
				map_effect = 2;
				Sleep(500);
				map_effect = 0;
				printlog("화려한 불빛과 폭죽이 주변의 적들에게 몰아친다! ", true, false, false, CL_joon);
			} 

			it->SetConfuse(rand_int(5,10)+randA(power/20), true);
			int damage_ = (20 + (you.level * 2))*(power+400.0f)/400;


			attack_infor temp_att(randC(5, damage_/5), damage_, 99, order, order->GetParentType(), ATT_NORMAL_BLAST, name_infor("폭죽", true));
			it->damage(temp_att, true);
			enter_++;
			if (enter_ == 1)
			{
				enterlog();
				enter_ = 0;
			}
			ok_ = true;
		}
	}
	if (ok_)
	{
		you.Ability(SKL_JOON_AND_SION_2, true, true);
		return true;
	}
	else
	{
		printlog("시야내에 적이 없다.", true, false, false, CL_normal);
		return false;
	}
	return false;
}
bool skill_joon_and_sion_3(int power, bool short_, unit* order, coord_def target)
{
	soundmanager.playSound("curse");
	map_effect = 3;
	Sleep(500);
	map_effect = 0;
	printlog("거대한 불운의 소용돌이가 휘몰아친다! ", true, false, false, CL_sion);
	int enter_ = 0;
	for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (it->isLive() && !it->isUserAlly() && env[current_level].isInSight(it->position))
		{
			it->SetSlow(rand_int(20, 40) + randA(power / 10));
			enter_++;
			if (enter_ == 3)
			{
				enterlog();
				enter_ = 0;
			}
		}
	}
	random_extraction<textures*> rand_t;
	rand_t.push(img_fog_sion[0], 3);
	rand_t.push(img_fog_sion[1], 1);
	rand_t.push(img_fog_sion[2], 1);
	MakeCloud(you.position, rand_t, SMT_SION, rand_int(20, 25), rand_int(50, 70), 10, 0, 5, &you);
	you.Ability(SKL_JOON_AND_SION_3, true, true);
	return true;
}
bool skill_joon_and_sion_4(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position, order->position);
	if (CheckThrowPath(order->position, target, beam))
	{
		beam_infor temp_infor(0, 0, 99, order, order->GetParentType(), SkillLength(SKL_JOON_AND_SION_4), 1, BMT_PENETRATE, ATT_THROW_NONE_DAMAGE, name_infor("시온", true));

		soundmanager.playSound("wind");
		coord_def c_ = throwtanmac(44, beam, temp_infor, NULL);
		unit* hit_mon = env[current_level].isMonsterPos(c_.x, c_.y, order);
		if (hit_mon && !hit_mon->isplayer())
		{
			monster* mon_ = (monster*)hit_mon;
			if (mon_->flag & M_FLAG_INANIMATE)
			{
				printarray(true, false, false, CL_sion, 3, hit_mon->GetName()->name.c_str(), hit_mon->GetName()->name_is(true), "무생물이기에 빙의할 수 없다.");
				return true;
			}
			soundmanager.playSound("smite");
			mon_->level = 1;
			for (int i = 0; i<3; i++)
			{
				if (mondata[mon_->id].atk[i])
				{
					mon_->atk[i] = 2;
				}
			}
			mon_->ac = 0;
			mon_->ev = 5;
			mon_->max_hp = mon_->max_hp / 2;
			if (mon_->max_hp < mon_->hp)
				mon_->hp = mon_->max_hp;
			for (auto it = mon_->spell_lists.begin(); it != mon_->spell_lists.end(); it++)
			{
				it->percent = it->percent / 5;
			}

			if (monster* mon_ = BaseSummon(MON_SION, 100, true, false, 2, hit_mon, hit_mon->position, SKD_OTHER, -1))
			{
				mon_->s_ally = -1;
				mon_->flag |= M_FLAG_ALLY;
				mon_->SetInvincibility(-1, false);
			}

			if (hit_mon->isYourShight())
			{
				printarray(true, false, false, CL_sion, 2, hit_mon->GetName()->name.c_str(), "에 빈곤신이 빙의하였다!");
			}
			hit_mon->AttackedTarget(order);
		}
		if (you.god_value[GT_JOON_AND_SION][0] == 2) {
			//빙의된 신이 시온일때는 죠온으로 바뀐다.
			you.Ability(SKL_JOON_AND_SION_3, true, true);
			you.Ability(SKL_JOON_AND_SION_2, true, false);
			you.god_value[GT_JOON_AND_SION][0] = 1;
		}
		you.Ability(SKL_JOON_AND_SION_4, true, true);
		return true;
	}
	return false;
}
bool skill_joon_and_sion_off(int power, bool short_, unit* order, coord_def target)
{
	printlog("당신의 빙의가 끝났다. ", false, false, false, CL_joon_and_sion);
	if (you.god_value[GT_JOON_AND_SION][0] == 1) {
		if (you.power >= 300)
			you.PowUpDown(-(you.power - 300));
	}
	you.god_value[GT_JOON_AND_SION][0] = 0;
	you.god_value[GT_JOON_AND_SION][1] = -1;
	you.gift_count = GetGodGiftTime(you.god);
	//you.Ability(SKL_JOON_AND_SION_1, true, false);
	you.Ability(SKL_JOON_AND_SION_2, true, true);
	you.Ability(SKL_JOON_AND_SION_3, true, true);
	you.Ability(SKL_JOON_AND_SION_4, true, true);
	you.Ability(SKL_JOON_AND_SION_OFF, true, true);
	return true;
}

bool skill_miko_1(int power, bool short_, unit* order, coord_def target)
{
	if (env[current_level].popular == -1) {
		printlog("이 곳은 인기를 모으기엔 너무 오래된 곳이다.", true, false, false, CL_normal);
		return false;
	} else if (env[current_level].popular == 0) {
		printlog("이 곳은 이미 욕망을 모은 층이다.", true, false, false, CL_normal);
		return false;
	}

	
	int ok_ = 0;
	int piety_ = 0;
	for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (it->isLive() && !it->isUserAlly()
			&& env[current_level].isInSight(it->position)
			&& !(it->flag & M_FLAG_SUMMON)
			&& !(it->flag & M_FLAG_UNHARM))
		{
			ok_++;
			piety_ += it->SetStrong()*2;
		}
	}
	if (ok_ > 0)
	{
		char temp[256];
		sprintf_s(temp, 256, "시야안에 있는 %d명의 욕망을 읽어들였다!", ok_);
		you.PietyUpDown(piety_);
		printlog(temp, true, false, false, CL_miko);
		env[current_level].popular = 0;
		soundmanager.playSound("powerup");
		return true;
	}
	else
	{
		printlog("시야내에 욕망을 읽어낼 적이 없다.", true, false, false, CL_normal);
		return false;
	}
	return false;
}
bool skill_miko_2(int power, bool short_, unit* order, coord_def target)
{
	if (!order->Tele_check(true, false))
		return false;
	if (env[current_level].isInSight(order->position)) {
		soundmanager.playSound("blink");
	}
	order->Blink(25);

	return true;
}
bool skill_miko_3(int power, bool short_, unit* order, coord_def target)
{
	bool already_ = you.SetBuff(BUFFSTAT_HALO, BUFF_MIKO_HALO, 1, -1);
	if (already_)
	{
		printlog("이미 존재하는 저항이다.", true, false, false, CL_normal);
		return false;
	}
	else {
		soundmanager.playSound("buff");
		printlog("미코: 유용하게 쓰도록!", true, false, false, CL_miko);
		return true;
	}
	return true;
}
bool skill_miko_4(int power, bool short_, unit* order, coord_def target)
{
	int resist_ = 0;
	bool loop_ = true;
	while (loop_) {
		printlog("미코: 어느 저항을 얻을거지? 버프는 층을 옮기기전까지 유지된단다.", true, false, false, CL_miko);
		printlog("a - 화염저항    b - 냉기저항    c - 전기저항", true, false, false, CL_miko);
		printlog("d - 독저항      e - 혼란저항", true, false, false, CL_miko);
		switch (waitkeyinput())
		{
		case 'a':
		case 'A':
			resist_ = 1;
			loop_ = false;
			break;
		case 'b':
		case 'B':
			resist_ = 2;
			loop_ = false;
			break;
		case 'c':
		case 'C':
			resist_ = 3;
			loop_ = false;
			break;
		case 'd':
		case 'D':
			resist_ = 4;
			loop_ = false;
			break;
		case 'e':
		case 'E':
			resist_ = 5;
			loop_ = false;
			break;
		default:
			break;
		case VK_ESCAPE:
			printlog("취소하였다.", true, false, false, CL_normal);
			return false;
		}
	}
	bool already_ = false;
	switch (resist_)
	{
	case 1:
		already_ = you.SetBuff(BUFFSTAT_RF, BUFF_MIKO_RF, 1, -1);
		break;
	case 2:
		already_ = you.SetBuff(BUFFSTAT_RC, BUFF_MIKO_RI, 1, -1);
		break;
	case 3:
		already_ = you.SetBuff(BUFFSTAT_RE, BUFF_MIKO_RE, 1, -1);
		break;
	case 4:
		already_ = you.SetBuff(BUFFSTAT_RP, BUFF_MIKO_RP, 1, -1);
		break;
	case 5:
		already_ = you.SetBuff(BUFFSTAT_RCONF, BUFF_MIKO_RC, 1, -1);
		break;
	}
	if (already_)
	{
		printlog("이미 존재하는 저항이다.", true, false, false, CL_normal);
		return false;
	}
	else {
		soundmanager.playSound("buff");
		printlog("미코: 유용하게 쓰도록!", true, false, false, CL_miko);
		return true;

	}
}
bool skill_miko_5(int power, bool short_, unit* order, coord_def target)
{
	if(you.isSetMikoBuff(0)) {
		printlog("이미 이 층에선 망토를 선택했다.", true, false, false, CL_normal);
		return false;
	}
	int bonus_ = 0;
	bool loop_ = true;
	while (loop_) {
		printlog("미코: 어느 망토를 고를건가? 버프는 층을 옮기기전까지 유지된단다.", true, false, false, CL_miko);
		printlog("a - 빨간망토 : 전투력보너스 +6과 체력재생력", true, false, false, CL_miko);
		printlog("b - 파랑망토 : 스펠파워 1.5배 보너스와 영력재생력", true, false, false, CL_miko);
		switch (waitkeyinput())
		{
		case 'a':
		case 'A':
			bonus_ = 1;
			loop_ = false;
			break;
		case 'b':
		case 'B':
			bonus_ = 2;
			loop_ = false;
			break;
		default:
			break;
		case VK_ESCAPE:
			printlog("취소하였다.", true, false, false, CL_normal);
			return false;
		}
	}

	switch (bonus_)
	{
	case 1:
		you.SetBuff(BUFFSTAT_DAM, BUFF_MIKO_DAM, 6, -1);
		you.SetBuff(BUFFSTAT_ACC, BUFF_MIKO_ACC, 6, -1);
		you.SetBuff(BUFFSTAT_REGEN, BUFF_MIKO_REGEN, 1, -1);
		break;
	case 2:
		you.SetBuff(BUFFSTAT_SPL_POW, BUFF_MIKO_SPLPOW, 1, -1);
		you.SetBuff(BUFFSTAT_MREGEN, BUFF_MIKO_MREGEN, 1, -1);
		break;
	}
	soundmanager.playSound("buff");
	printlog("미코: 유용하게 쓰도록!", true, false, false, CL_miko);
	return true;
}
bool skill_miko_6(int power, bool short_, unit* order, coord_def target)
{
	if (you.isSetMikoBuff(1)) {
		printlog("이미 인기 폭발 상태다.", true, false, false, CL_normal);
		return false;
	}
	int bonus_ = 0;
	bool loop_ = true;
	while (loop_) {
		printlog("인기 폭발! 어느 보너스를 얻을건가?", true, false, false, CL_miko);
		printlog("a - 층을 옮기기전까지 체력 2배", true, false, false, CL_miko);
		printlog("b - 층을 옮기기전까지 영력 회복 속도 폭증", true, false, false, CL_miko);
		printlog("c - 층을 옮기기전까지 영구적인 가속", true, false, false, CL_miko);
		switch (waitkeyinput())
		{
		case 'a':
		case 'A':
			bonus_ = 1;
			loop_ = false;
			break;
		case 'b':
		case 'B':
			bonus_ = 2;
			loop_ = false;
			break;
		case 'c':
		case 'C':
			bonus_ = 3;
			loop_ = false;
			break;
		default:
			break;
		case VK_ESCAPE:
			printlog("취소하였다.", true, false, false, CL_normal);
			return false;
		}
	}
	switch (bonus_)
	{
	case 1:
		you.SetBuff(BUFFSTAT_HP, BUFF_MIKO_ULTI, you.GetMaxHp(), -1);
		break;
	case 2:
		you.SetBuff(BUFFSTAT_MREGEN, BUFF_MIKO_ULTI, 5, -1);
		break;
	case 3:
		you.SetBuff(BUFFSTAT_HASTE, BUFF_MIKO_ULTI, 1, -1);
		break;
	}
	soundmanager.playSound("buff");
	printlog("미코: 유용하게 쓰도록!", true, false, false, CL_miko);
	return true;
}


bool skill_jump_attack(int power, bool short_, unit* order, coord_def target);


bool skill_fire_ball(int power, bool short_, unit* order, coord_def target);
bool skill_water_cannon(int power, bool short_, unit* order, coord_def target);
bool skill_air_strike(int power, bool short_, unit* order, coord_def target);	
bool skill_emerald_city(int power, bool short_, unit* order, coord_def target);
bool skill_stone_uplift(int power, bool short_, unit* order, coord_def target);


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
	case SKL_PHILOSOPHERS_1:
	case SKL_PHILOSOPHERS_2:
	case SKL_PHILOSOPHERS_3:
	case SKL_PHILOSOPHERS_4:
	case SKL_PHILOSOPHERS_5:
		{
			power=you.GetSpellPower(SKT_ALCHEMY,SKT_ERROR,SKT_ERROR);
	
			int size_ = (skill == SKL_PHILOSOPHERS_1 || skill == SKL_PHILOSOPHERS_5)?1:0;
			if(!CheckSucide(you.position,target,SkillFlagCheck(skill,S_FLAG_SEIF) || SkillFlagCheck(skill, S_FLAG_IMMEDIATELY),size_,SkillFlagCheck(skill,S_FLAG_SMITE)))
			{
				return false;
			}
			
			if(you.GetPunish(GT_MIMA))
			{
				printlog("미마는 당신이 쓰는 마법의 위력을 반감시켰다!",true,false,false,CL_green);
			}
			if(wiz_list.wizard_mode == 1)
			{
				char temp[50];
				sprintf_s(temp,50,"스펠파워 %d / %d",power,SkillCap(skill));
				printlog(temp,true,false,false,CL_help);
			}

			switch(skill)
			{
			case SKL_PHILOSOPHERS_1:
				return skill_fire_ball(power,short_,&you,target);
				break;
			case SKL_PHILOSOPHERS_2:
				return skill_water_cannon(power,short_,&you,target);
				break;
			case SKL_PHILOSOPHERS_3:
				return skill_air_strike(power,short_,&you,target);	
				break;
			case SKL_PHILOSOPHERS_4:
				return skill_emerald_city(power,short_,&you,target);
				break;
			case SKL_PHILOSOPHERS_5:
				return skill_stone_uplift(power,short_,&you,target);
			}
		}
		break;
	case SKL_OKINA_1:
		return skill_okina_1(power, short_, &you, target);
		break;
	case SKL_OKINA_2:
		return skill_okina_2(power, short_, &you, target);
		break;
	case SKL_OKINA_3:
		return skill_okina_3(power, short_, &you, target);
		break;
	case SKL_OKINA_4:
		return skill_okina_4(power, short_, &you, target);
		break;
	case SKL_OKINA_5:
		return skill_okina_5(power, short_, &you, target);
		break;
	case SKL_JUNKO_1:
		return skill_junko_1(power, short_, &you, target);
		break;
	case SKL_JUNKO_2:
		return skill_junko_2(power, short_, &you, target);
		break;
	case SKL_JUNKO_3:
		return skill_junko_3(power, short_, &you, target);
		break;
	case SKL_JUNKO_4:
		return skill_junko_4(power, short_, &you, target);
		break;
	case SKL_JOON_AND_SION_1:
		return skill_joon_and_sion_1(power, short_, &you, target);
		break;
	case SKL_JOON_AND_SION_2:
		return skill_joon_and_sion_2(power, short_, &you, target);
		break;
	case SKL_JOON_AND_SION_3:
		return skill_joon_and_sion_3(power, short_, &you, target);
		break;
	case SKL_JOON_AND_SION_4:
		return skill_joon_and_sion_4(power, short_, &you, target);
		break;
	case SKL_JOON_AND_SION_OFF:
		return skill_joon_and_sion_off(power, short_, &you, target);
		break;
	case SKL_MIKO_1:
		return skill_miko_1(power, short_, &you, target);
		break;
	case SKL_MIKO_2:
		return skill_miko_2(power, short_, &you, target);
		break;
	case SKL_MIKO_3:
		return skill_miko_3(power, short_, &you, target);
		break;
	case SKL_MIKO_4:
		return skill_miko_4(power, short_, &you, target);
		break;
	case SKL_MIKO_5:
		return skill_miko_5(power, short_, &you, target);
		break;
	case SKL_MIKO_6:
		return skill_miko_6(power, short_, &you, target);
		break;
	}
	return 0;
}


