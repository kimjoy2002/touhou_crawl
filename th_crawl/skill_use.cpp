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
#include "evoke.h"


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
			printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_SHOULD_TARGET_ENEMY),true,false,false,CL_normal);	
			return false; //해당 위치에 몬스터가 없다.
		}

		beam_iterator beam(order->position,order->position);
		if(CheckThrowPath(order->position,target,beam))
		{
			beam.init();
			
			if(beam.GetMaxLength() == 1 || env[current_level].isMonsterPos(beam->x,beam->y, &you))
			{				
				printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_TOO_CLOSE),true,false,false,CL_normal);	
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_CANT_CHARGE1),true,false,false,CL_normal);	
						return false;
					}
					you.SetXY(beam->x,beam->y);

					float multy_ = 1.0f; //기도술, 거리 비례해서 데미지를 주자.
					multy_*=(9.0f+temp.GetCurLength())/9; //거리가 6기준으로 1.66배 데미지를 준다.
					//multy_*=(13.0f+pow/5)/13;

					soundmanager.playSound("wind");
					attack_infor temp_att(you.GetAttack(false)*multy_,you.GetAttack(true),you.GetHit()+10,&you,you.GetParentType(),ATT_RUSH,name_infor(LOC_SYSTEM_ATT_RUSH));
					unit_->damage(temp_att,false);
					printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_CHARGE_TO_ENEMY),true,false,false,CL_normal);	
					return true;
				}
				beam++;
			}
			printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_CANT_CHARGE2),true,false,false,CL_normal);
			return false;
		}
		//더이상 마이트는 아니다! 적의 방향으로 돌진한다.
		//you.SetMight(20+randA_1(pow*5));
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_BLOCK_INSIGHT),true,false,false,CL_normal);	
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_CANT_CREATE_POSITION),true,false,false,CL_normal);	

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
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_ALREADY_GRAZE),true,false,false,CL_normal);	

	return false;
}
bool skill_off_graze(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		if (you.isGrazeAmulet()) {
			printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_AMULET_GRAZE), true, false, false, CL_normal);
			return false;
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_GRAZE_STOP),true,false,false,CL_normal);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_ALREADY_LEVITATION),true,false,false,CL_normal);	

	return false;
}
bool skill_off_levitation(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_LEVITATION_STOP),true,false,false,CL_normal);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_ALREADY_INVISIBLE),true,false,false,CL_normal);	

	return false;
}
bool skill_off_invisible(int pow, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_INVISIBLE_STOP),true,false,false,CL_normal);
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
		view_item(IVT_POTION,LOC_SYSTEM_DISPLAY_MANAGER_THROW);
		while(1)
		{
			InputedKey inputedKey;
			int key_ = waitkeyinput(inputedKey,true);
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
							beam_infor temp_infor(randA(power/10),randA(power/10),10,order,order->GetParentType(),length_,1,BMT_PENETRATE,ATT_THROW_NONE_MASSAGE,name_infor(LOC_SYSTEM_ITEM_POTION_POTION));
							
							for(int k=0;k<(order->GetParadox()?2:1);k++)
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
							printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_THIS_IS_NOT_POTION),true,false,false,CL_normal);
							return false;	
						}
					}
				}
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_NOT_EXIST),true,false,false,CL_normal);
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
				view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_THROW);
			else if(key_ == -1) {				
				if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
					int get_item_move_ = getDisplayMove();
					if(iteminfor_(inputedKey.val1, true))
						break;
					rollback_item(IVT_POTION,LOC_SYSTEM_DISPLAY_MANAGER_THROW);
					setDisplayMove(get_item_move_);
				} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
					changemove(-32);  //아래
				} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
					changemove(32);  //위
				} else if(inputedKey.isRightClick()) {
					break;
				}
			}
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_STAT_SELECT) + " ",false,false,false,CL_help);
		printlog(LocalzationManager::locString(LOC_SYSTEM_LEVELUP_STAT_MESSGE_S),false,false,false,CL_help, 'S');
		printlog(", ",false,false,false,CL_help);
		printlog(LocalzationManager::locString(LOC_SYSTEM_LEVELUP_STAT_MESSGE_D),false,false,false,CL_help, 'D');
		printlog(", ",false,false,false,CL_help);
		printlog(LocalzationManager::locString(LOC_SYSTEM_LEVELUP_STAT_MESSGE_I),false,false,false,CL_help, 'I');
		printlog(", ",false,false,false,CL_help);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_STAT_SELECT_RETURN),false,false,false,CL_help, 'R');
		printlog(" ",false,false,false,CL_help);
		startSelection({'S', 'D', 'I', 'R'});
		while(!end_)
		{
			InputedKey inputedKey;
			switch(waitkeyinput(inputedKey))
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
			case 'R':
				stat_ = 0;
				end_ = true;
				break;				
			case -1:
				if(inputedKey.isRightClick()) {
					//ESC PASSTHORUGH
				}
				else {
					break;
				}
			case VK_ESCAPE:
				printlog(LocalzationManager::locString(LOC_SYSTEM_BE_PRUDENT),true,false,false,CL_help);
				endSelection();
				return false;
			}
		}
		endSelection();

		if(you.s_stat_boost == stat_)
		{
			if(stat_)
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_ALREADY_BOOST),false,false,false,CL_normal);
			else
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_FAIL_TO_RECOVERY),false,false,false,CL_normal);

			return false;
		}


		soundmanager.playSound("buff");
		you.SetStatBoost(stat_, max(1,pietyLevel(you.piety)-1));
		if(stat_)
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_BOOST),true,false,false,CL_good);
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_BOOST_RETURN) + " ",false,false,false,CL_help);
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_MAYBE),false,false,false,CL_small_danger);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_HEAL),true,false,false,CL_help);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_EIRIN_HEAL_WARN),true,false,false,CL_danger);
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
					LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
						 PlaceHolderHelper(unit_->GetName()->getName()));
				}
				number_++;
			}
		}
	}
	if(!number_)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_CONFUSE_FAIL),true,false,false,CL_normal);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_AUTUMN_ARMOUR_ARTIFACT),true,false,false,CL_normal);
			return false;
		}
		if(you.equipment[ET_ARMOR]->value5 == AMK_AUTUMN)
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_AUTUMN_ARMOUR_ALREADY),true,false,false,CL_normal);
			return false;
		}
		
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_SHIZUHA_AUTUMN_ARMOUR_YN,false,false,true,CL_help,
			PlaceHolderHelper(you.equipment[ET_ARMOR]->name.getName()));
		printlog(" (",false,false,true,CL_help);
		printlog("y",false,false,true,CL_help, 'y');
		printlog("/",false,false,true,CL_help);
		printlog("n",false,false,true,CL_help, 'n');
		printlog(") ",false,false,true,CL_help);
		startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
		
		
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			break;
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_BE_PRUDENT),true,false,false,CL_help);
			endSelection();
			return false;
		}
		endSelection();
		
		equipArmour((armour_kind)you.equipment[ET_ARMOR]->value5, -1);

		you.equipment[ET_ARMOR]->value5=AMK_AUTUMN;

		equipArmour((armour_kind)you.equipment[ET_ARMOR]->value5, 1);

		you.equipment[ET_ARMOR]->name = name_infor(LOC_SYSTEM_ITEM_ARMOUR_T_AUTUMN,  GetMaterialStringKey((material_kind)(you.equipment[ET_ARMOR]->type-ITM_ARMOR_BODY_ARMOUR_0)));

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
		default:
			break;
		}
		soundmanager.playSound("buff");
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_AUTUMN_ARMOUR),true,false,false,CL_normal);
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_AUTUMN_ARMOUR_UNEQUIP),true,false,false,CL_normal);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_CURE),true,false,false,CL_white_blue);
			return true;
		}
		else{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_CURE_FAIL),true,false,false,CL_normal);
			return false;	
		}

	}
	return false;

}
	
bool skill_minoriko_heal(int pow, bool short_, unit* order, coord_def target)
{		
	view_item(IVT_FOOD,LOC_SYSTEM_DISPLAY_MANAGER_USE);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_FOOD_HEAL),true,false,false,CL_white_blue);
						return true;	
					}
					else
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MINORIKO_FOOD_FAIL),true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_NOT_EXIST),true,false,false,CL_normal);
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
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_USE);
		else if(key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_FOOD,LOC_SYSTEM_DISPLAY_MANAGER_USE);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}

bool skill_yuugi_drink(int pow, bool short_, unit* order, coord_def target)
{
	{
		view_item(IVT_POTION,LOC_SYSTEM_DISPLAY_MANAGER_USE);
		while(1)
		{
			InputedKey inputedKey;
			int key_ = waitkeyinput(inputedKey,true);
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
							printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_THIS_IS_NOT_POTION),true,false,false,CL_normal);
							return false;	
						}
					}
				}
				printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_NOT_EXIST),true,false,false,CL_normal);
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
				view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_USE);
			else if(key_ == -1) {				
				if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
					int get_item_move_ = getDisplayMove();
					if(iteminfor_(inputedKey.val1, true))
						break;
					rollback_item(IVT_POTION,LOC_SYSTEM_DISPLAY_MANAGER_USE);
					setDisplayMove(get_item_move_);
				} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
					changemove(-32);  //아래
				} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
					changemove(32);  //위
				} else if(inputedKey.isRightClick()) {
					break;
				}
			}
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GARMAN_SUPLEX_NOT_ENOUGH_TILE),true,false,false,CL_normal);
				return false;	
			}
			if(env[current_level].isMonsterPos(offset_.x,offset_.y,order))
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GARMAN_SUPLEX_SOMEONE),true,false,false,CL_normal);
				return false;	
			}
			mon_->SetXY(offset_);
			int damage_ = you.GetAttack(false)*10/you.GetAtkDelay()*(1+pow/100.0f)+randC(2,2+pow/20);
			int max_damage_ = you.GetAttack(true)*10/you.GetAtkDelay()*(1+pow/100.0f)+2*(2+pow/20);				

			soundmanager.playSound("stone");
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_GARMAN_SUPLEX) + " ",false,false,false,CL_yuigi);
			attack_infor temp_att(damage_,max_damage_,99,&you,you.GetParentType(),ATT_NORMAL_HIT,name_infor(LOC_SYSTEM_ATT_GERMANSUPLEX));
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
			auto it = you.item_list.end();
			if(Common_Throw(it, you.GetTargetIter(), beam, &infor, throw_length_, 0.0f))
			{		
				int length_ = ceil(sqrt(pow((float)abs(order->position.x-you.search_pos.x),2)+pow((float)abs(order->position.y-you.search_pos.y),2)));
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_THROW) + " ",false,false,false,CL_yuigi);
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
				attack_infor temp_att(randC(3,3+power/15),3*(3+power/15),99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_SHOCKWAVE));

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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_SHOUT) + " ",false,false,false,CL_yuigi);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_SHOUT_FAIL),true,false,false,CL_normal);
		return false;	
	}
	return false;
}
bool skill_yuugi_sambo(int power, bool short_, unit* order, coord_def target)
{
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUUGI_THREE_STEP) + " ",false,false,false,CL_yuigi);
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

								attack_infor temp_att(att_,m_att_,99,order,order->GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_SHOCKWAVE));
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_KOISHI),true,false,false,CL_small_danger);
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
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_MINDREADING_TOO_COMPLEX),true,false,false,CL_small_danger);
				return false;
			}
			if(mon_->id == MON_KOISHI)
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_KOISHI),true,false,false,CL_small_danger);
				return false;
			}
			if(mon_->s_mind_reading)
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_MINDREADING_ALREADY),true,false,false,CL_normal);
				return false;

			}

			int fail_ = 0;
			for(int i=0; i<turn_; i++)
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_MINDREADING),false,false,false,CL_danger);
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
			if(fail_) {
				if(fail_==1) {
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_MINDREADING_INTERRUPT),true,false,false,CL_small_danger);
				}
				else {
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SATORI_MINDREADING_DISAPPREAR),true,false,false,CL_small_danger);
				}
			}
			else
			{
				soundmanager.playSound("debuf");
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
		printlog( LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_PUNISH_MAGIC) ,true,false,false,CL_magic);
	}
	return return_;
}
bool skill_shinki_mid_demon(int power, bool short_, unit* order, coord_def target)
{
	bool return_=false;
	if(monster* mon_=BaseSummon(randA(2)==0?MON_SARA:(randA(1)?MON_LUIZE:MON_ELIS), rand_int(90,120), true, false, 2, order, target, SKD_SUMMON_SHINKI, -1))
	{
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_SUMMON,false,false,false,CL_magic,
			PlaceHolderHelper(mon_->name.getName()));
		if(randA(99)<=3)
		{
			soundmanager.playSound("laugh");
			
			LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_SHINKI_SUMMON_FAIL,false,false,false,CL_danger,
				PlaceHolderHelper(mon_->name.getName()));
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
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_SUMMON,false,false,false,CL_magic,
			PlaceHolderHelper(mon_->name.getName()));
		if(randA(99)<=(id_==MON_YUKI?5:id_==MON_MAI?5:3))
		{
			soundmanager.playSound("laugh");
			LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_SHINKI_SUMMON_FAIL,false,false,false,CL_danger,
				PlaceHolderHelper(mon_->name.getName()));
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GHOST_START),true,false,false,CL_normal);
		you.SetGhost(1);
		int temp = you.Ability(SKL_YUYUKO_ON,true,true,1);
		you.Ability(SKL_YUYUKO_OFF,true,false,temp);
		return true;
	}
	else if(order->isplayer() && you.s_ghost)
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GHOST_ALREADY),true,false,false,CL_normal);	

	return false;
}
bool skill_yuyuko_off(int power, bool short_, unit* order, coord_def target)
{
	if(order->isplayer())
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GHOST_STOP),true,false,false,CL_normal);
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
			LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_YUYUKO_RECALL,true,false,false,CL_normal,
				 PlaceHolderHelper(unit_->GetName()->getName()));
			unit_->AttackedTarget(order);
			return true;
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GHOST_NOT_EXIST), true,false,false,CL_normal);
			return false;
		}
	}
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GHOST_MUST_TARGET_TO_UNIT),true,false,false,CL_normal);
	return false;
}
bool skill_yuyuko_boost(int power, bool short_, unit* order, coord_def target)
{	
	if(order->isplayer())
	{
		soundmanager.playSound("spellcard");
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUYUKO_GHOST_MUST_TARGET_TO_UNIT),true,false,false,CL_white_blue);
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
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_RESIST,true,false,false,CL_normal,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_CANT_CREATE), true,false,false,CL_normal);
					return false;
				}
			}
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_SHOULD_SCHEMA),true,false,false,CL_normal);
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
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_SHOULD_SCHEMA), true,false,false,CL_normal);
					hit_eff->time = 0;
					return true;
				}
				else
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_SHOULD_SCHEMA), true,false,false,CL_normal);
					return false;
				}
			}
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_SHOULD_SCHEMA),true,false,false,CL_normal);
	}
	return false;

}
bool skill_yukari_shield(int power, bool short_, unit* order, coord_def target)
{	
	if(order == &you)
	{
		soundmanager.playSound("buff");
		you.SetBuff(BUFFSTAT_SH,BUFF_YUKARI,15,rand_int(70,100));
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_SHIELD),true,false,false,CL_white_blue);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_DIMENSION_BAMBOO),true,false,false,CL_small_danger);
			return false;
		}
		you.search_pos = target;
		widesearch = true;
		you.search = true;

	
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_DIMENSION_YN),false,false,false,CL_danger);
		printlog(" (",false,false,false,CL_danger);
		printlog("y",false,false,false,CL_danger, 'y');
		printlog("/",false,false,false,CL_danger);
		printlog("n",false,false,false,CL_danger, 'n');
		printlog(") ",false,false,false,CL_danger);
		startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			enterlog();
			endSelection();
			break;
		case 'N':
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_BE_PRUDENT),true,false,false,CL_normal);
			widesearch = false;
			you.search = false;
			endSelection();
			return false;
		}


		widesearch = false;
		you.search = false;

		you.god_value[GT_YUKARI][0] = target.x;
		you.god_value[GT_YUKARI][1] = target.y;
		you.SetDimension(rand_int(50,70));
		soundmanager.playSound("timestop");
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_YUKARI_DIMENSION_FIX),false,false,false,CL_white_blue);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_JUMP) + " " ,false,false,false,CL_normal);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_ALTAR1) + " ",false,false,false,CL_swako);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_ALTAR2),true,false,false,CL_swako);
		you.PietyUpDown(2+randA(2));
		return true;
	}
	else
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_ALTAR_FAIL),true,false,false,CL_small_danger);

	return false;
}
bool skill_swako_water_gun(int power, bool short_, unit* order, coord_def target)
{
	beam_iterator beam(order->position,order->position);
	if(CheckThrowPath(order->position,target,beam))
	{
		beam_infor temp_infor(randA_1(5+power/5),5+power/5,15,order,order->GetParentType(),SkillLength(SKL_SWAKO_WATER_GUN),1,BMT_NORMAL,ATT_THROW_WATER,name_infor(LOC_SYSTEM_ATT_WATERGUN));
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
				LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_SWAWKO_TOUGUE_FULL,true,false,false,CL_normal,
					 PlaceHolderHelper(hit_mon->GetName()->getName()));
				return true;
			}
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_TOUGUE_FAIL),true,false,false,CL_small_danger);

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
			LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_SWAWKO_CURSE_MSG,true,false,false,CL_swako,
				 PlaceHolderHelper(hit_mon->GetName()->getName()));
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
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_SUMMON,false,false,false,CL_magic,
			PlaceHolderHelper(mon_->name.getName()));
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_STATUE_FAIL),true,false,false,CL_small_danger);
	}
	else
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_STATUE_FAIL),true,false,false,CL_small_danger);
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
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SWAWKO_RAIN),true,false,false,CL_magic);	
	
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
	bool return_ = false;
	if (monster* mon_ = BaseSummon(MON_MISYAGUZI, rand_int(90, 120), true, false, 2, order, target, SKD_SUMMON_MISYAGUZI, -1))
	{
		LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_SUMMON,false,false,false,CL_magic,
			PlaceHolderHelper(mon_->name.getName()));

		soundmanager.playSound("summon");
		return_ = true;
		enterlog();
	}
	return return_;
}
bool skill_hina_plusminus(int power, bool short_, unit* order, coord_def target)
{
	view_item(IVT_CURSE_ENCHANT,LOC_SYSTEM_DISPLAY_MANAGER_NORMAL_ITEM);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);
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
									printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_WEAPON_MINUS_TO_PLUS),true,false,false,CL_hina);
									return true;	
								}
								else if(((*it).type>=ITM_ARMOR_FIRST && (*it).type<ITM_ARMOR_LAST) && (it->value4 < 0))
								{
									soundmanager.playSound("curse");
									if(it->value4<0)
										it->Enchant(ET_ARMOR,it->value4*-2);
									printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_ARMOUR_MINUS_TO_PLUS),true,false,false,CL_hina);
								
									return true;	

								}
								else
								{
									printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_ONLY_MINUS),true,false,false,CL_normal);
									return false;	
								}
							}
							else
							{
								printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_ONLY_CURSE),true,false,false,CL_normal);
								return false;	
							}
						}
						else
						{
							printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_CANT_ARTIFACT),true,false,false,CL_normal);
							return false;	
						}
					}
					else
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_INCORRECT_TARGET),true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_NOT_EXIST),true,false,false,CL_normal);
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
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_NORMAL_ITEM);
		else if(key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_CURSE_ENCHANT,LOC_SYSTEM_DISPLAY_MANAGER_NORMAL_ITEM);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_ALREAY_CURSE),true,false,false,CL_normal);
			return false;
		}
		string before_name = you.equipment[ET_WEAPON]->GetName(); //저주받기전 이름
		if(you.equipment[ET_WEAPON]->Curse(true,ET_WEAPON))
		{
			if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
			{
				soundmanager.playSound("curse");
				LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_HINA_ABIL_CURSE_WEAPON,true,false,false,CL_hina,
					 PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
				you.equipment[ET_WEAPON]->value5 = WB_CURSE;
				you.equipment[ET_WEAPON]->value6 = rand_int(80,100);
			}
			else
			{
				soundmanager.playSound("curse");
				LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_HINA_ABIL_CURSE_WEAPON_MIGHT,true,false,false,CL_small_danger,
					 PlaceHolderHelper(before_name));
				you.SetMight(rand_int(80,100));
			}
			return true;
		}
		else
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_CURSE_WEAPON_FAIL),true,false,false,CL_small_danger);
			return false;
		}

	}
	printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_CARRYING_WEAPON),true,false,false,CL_normal);
	return false;
}
bool skill_hina_curse_armour(int power, bool short_, unit* order, coord_def target)
{
	view_item(IVT_UEQ_ARMOR,LOC_SYSTEM_DISPLAY_MANAGER_ARMOUR);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);
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
										LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_HINA_ABIL_CURSE_ARMOUR_MIRROR,true,false,false,CL_small_danger,
											 PlaceHolderHelper(before_name));
										if(i == ET_ARMOR)	
											time_*=3;
										you.SetMirror(time_);
										return true;
									}
									else
									{
										printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_CURSE_ARMOUR_FAIL),true,false,false,CL_small_danger);
										return false;	
									}
								}
								else
								{
									printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_ALREAY_CURSE),true,false,false,CL_normal);
									return false;	
								}
							}
						}
						printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_EQUIP_ITEM),true,false,false,CL_normal);
						return false;	
					}
					else
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_CURSE_ONLY_ARMOUR),true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_NOT_EXIST),true,false,false,CL_normal);
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
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_ARMOUR);
		else if(key_ == -1) {			
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_UEQ_ARMOR,LOC_SYSTEM_DISPLAY_MANAGER_ARMOUR);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}
bool skill_hina_curse_ring(int power, bool short_, unit* order, coord_def target)
{
	view_item(IVT_UEQ_JEWELRY,LOC_SYSTEM_DISPLAY_MANAGER_JEWELRY);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey,true);
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
										LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_HINA_ABIL_CURSE_JEWELRY_HEAL,true,false,false,CL_small_danger,
											 PlaceHolderHelper(before_name));	
										you.HpUpDown(bonus_,DR_NONE);										
										you.MpUpDown(you.max_mp *rand_float(0.3f,0.4f));
										return true;
									}
									else
									{
										printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_CURSE_JEWELRY_FAIL),true,false,false,CL_small_danger);
										return false;
									}
								}
								else
								{
									printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_ALREAY_CURSE),true,false,false,CL_normal);
									return false;	
								}
							}
						}
						printlog(LocalzationManager::locString(LOC_SYSTEM_NOT_EQUIP_ITEM),true,false,false,CL_normal);
						return false;	
					}
					else
					{
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_ABIL_CURSE_ONLY_JEWELRY),true,false,false,CL_normal);
						return false;	
					}
				}
			}
			printlog(LocalzationManager::locString(LOC_SYSTEM_ITEM_NOT_EXIST),true,false,false,CL_normal);
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
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_JEWELRY);
		else if(key_ == -1) {
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_UEQ_JEWELRY,LOC_SYSTEM_DISPLAY_MANAGER_JEWELRY);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE)
			break;
	}
	changedisplay(DT_GAME);
	return false;
}
bool sizuha_autumn_bread(int pow, bool short_, unit* order, coord_def target)
{
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SHIZUHA_AUTUMN_BRAND_YN),false,false,false,CL_danger);
	printlog(" (",false,false,false,CL_danger);
	printlog("y",false,false,false,CL_danger, 'y');
	printlog("/",false,false,false,CL_danger);
	printlog("n",false,false,false,CL_danger, 'n');
	printlog(") ",false,false,false,CL_danger);
	startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
	switch(waitkeyinput())
	{
	case 'Y':
	case 'y':
		enterlog();
		endSelection();
		break;
	case 'N':
	default:
		printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE_EX),true,false,false,CL_normal);
		endSelection();
		return false;
	}

	if(you.equipment[ET_WEAPON]  && (you.equipment[ET_WEAPON]->type>=ITM_WEAPON_FIRST && you.equipment[ET_WEAPON]->type<ITM_WEAPON_LAST) && !you.equipment[ET_WEAPON]->isArtifact())
	{
		soundmanager.playSound("buff");
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_SHIZUHA_AUTUMN_BRAND,true,false,false,CL_autumn,
			 PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
		you.equipment[ET_WEAPON]->value5 = WB_AUTUMN;
		you.equipment[ET_WEAPON]->value6 = -1;
		you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, randA_1(2));
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_GIFT,true,false,false,CL_autumn,
			 PlaceHolderHelper(LOC_SYSTEM_GOD_SHIZUHA));
		you.god_value[GT_SHIZUHA][0] = 1;
		you.Ability(SKL_SIZUHA_3,true,true);
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_CANT_BRAND),true,false,false,CL_normal);
		return false;
	}
	return true;
}
bool hina_curse_bread(int pow, bool short_, unit* order, coord_def target)
{
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_HINA_CURSE_BRAND_YN),false,false,false,CL_danger);
	printlog(" (",false,false,false,CL_danger);
	printlog("y",false,false,false,CL_danger, 'y');
	printlog("/",false,false,false,CL_danger);
	printlog("n",false,false,false,CL_danger, 'n');
	printlog(") ",false,false,false,CL_danger);
	startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
	switch(waitkeyinput())
	{
	case 'Y':
	case 'y':
		enterlog();
		endSelection();
		break;
	case 'N':
	default:
		printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE_EX),true,false,false,CL_normal);
		endSelection();
		return false;
	}

	if(you.equipment[ET_WEAPON]  && (you.equipment[ET_WEAPON]->type>=ITM_WEAPON_FIRST && you.equipment[ET_WEAPON]->type<ITM_WEAPON_LAST) && !you.equipment[ET_WEAPON]->isArtifact())
	{
		soundmanager.playSound("curse");
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_HINA_CURSE_BRAND,true,false,false,CL_hina,
			 PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
		you.equipment[ET_WEAPON]->value5 = WB_CURSE;
		you.equipment[ET_WEAPON]->value6 = -1;
		you.equipment[ET_WEAPON]->Enchant(ET_WEAPON, randA_1(2));
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_GIFT,true,false,false,CL_hina,
			 PlaceHolderHelper(LOC_SYSTEM_GOD_HINA));
		you.god_value[GT_HINA][0] = 1;
		you.Ability(SKL_HINA_5,true,true);
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_CANT_BRAND),true,false,false,CL_normal);
		return false;
	}
	return true;
}

bool skill_breath(int power, bool short_, unit* order, coord_def target)
{
	if(!order || !order->isplayer())
		return false;


	LOCALIZATION_ENUM_KEY key_ = LOC_SYSTEM_SKL_BREATH;
	attack_type type_ = ATT_THROW_COLD;
	int graphic_ = 36;

	switch(you.half_youkai[1])
	{
	case 0:
		key_ = LOC_SYSTEM_SKL_BREATH_FIRE;
		type_ = ATT_THROW_FIRE;
		graphic_ = 36;
		break;
	case 1:
		key_ = LOC_SYSTEM_SKL_BREATH_COLDE;
		type_ = ATT_THROW_COLD;
		graphic_ = 40;
		break;
	case 2:
		key_ = LOC_SYSTEM_SKL_BREATH_ELEC;
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
		beam_infor temp_infor(randC(3,damage_),3*(damage_),20,order,order->GetParentType(),SkillLength(SKL_BREATH),8,BMT_PENETRATE,type_,name_infor(key_));
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
	printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_TORMENT),true,false,false,CL_normal);
	
	for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it!=env[current_level].mon_vector.end(); it++)
	{	
		if(it->isLive() && env[current_level].isInSight(it->position) && order->isSightnonblocked(it->position))
		{
			soundmanager.playSound("sickle");
			it->hp=it->hp/2;	
			it->AttackedTarget(order);
			//int att_ = 13+pow/15;
			//	
			//attack_infor temp_att(randC(5,att_),5*(att_),99,order,order->GetParentType(),ATT_THROW_FREEZING,name_infor(LOC_SYSTEM_ATT_COLD));
			//it->damage(temp_att, true);			
		}
	}
	return true;
}

void abandon_god() {
	bool sanae_ = (you.char_type == UNIQ_START_SANAE) && (you.god == GT_KANAKO || you.god == GT_SUWAKO);
	bool junko_ = you.god_value[GT_JUNKO][3] != 0 && you.god == GT_JUNKO;
	if (sanae_) {
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_ABANDON_SANAE,true,false,false,CL_small_danger,
			 PlaceHolderHelper(GetGodString(you.god)),
			 PlaceHolderHelper(GetGodString(you.god)));
	}
	else if (you.god == GT_SATORI) {
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_ABANDON_SATORI,true,false,false,CL_small_danger,
			PlaceHolderHelper(GetGodString(you.god)));
	} else {
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_ABANDON,true,false,false,CL_danger,
			PlaceHolderHelper(GetGodString(you.god)));
	}

	if (!sanae_)
	{
		you.PunishUpDown(30, you.god, true);
	}

	AddNote(you.turn, CurrentLevelString(), LocalzationManager::formatString(LOC_SYSTEM_NOTE_GOD_ABANDON, PlaceHolderHelper(GetGodString(you.god))), CL_small_danger);

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

}


bool skill_abandon_god(int pow, bool short_, unit* order, coord_def target)
{
	bool sanae_ = (you.char_type == UNIQ_START_SANAE) && (you.god == GT_KANAKO || you.god == GT_SUWAKO);

	bool junko_ = you.god_value[GT_JUNKO][3] != 0 && you.god == GT_JUNKO;
	for (int i = 0; i < (junko_ ? 2 : 1); i++)
	{
		if (i == 1)
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_ABANDON_ASK_PURIFICATION), false, false, false, CL_danger);
		else if (sanae_)
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_ABANDON_ASK_SANAE), false, false, false, CL_danger);
		else
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_ABANDON_ASK), false, false, false, CL_danger);
		printlog(" (",false,false,false,CL_danger);
		printlog("Y",false,false,false,CL_danger, 'Y');
		printlog("/",false,false,false,CL_danger);
		printlog("N",false,false,false,CL_danger, 'N');
		printlog(") ",false,false,false,CL_danger);
		startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
		switch (waitkeyinput())
		{
		case 'Y':
			enterlog();
			endSelection();
			break;
		case 'N':
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_CANCLE_EX), true, false, false, CL_normal);
			endSelection();
			return false;
		}
	}


	return true;
}

bool skill_seija_gift(int pow, bool short_, unit* order, coord_def target)
{
	int loop_ = true;
	god_type next_ = GT_NONE;


	if (you.god_value[GT_SEIJA][2] == 0) {
		//처음 선물을 받을때 선물받을 신을 무작위로 4명 고른다.

		random_extraction<int> rand_god;

		for (int i = GT_FIRST; i < GT_LAST; i++) {
			if (i != GT_SEIJA && !(you.god_value[GT_SEIJA][1] & (1 << i)))
				rand_god.push(i);
		}
		for (int i = 0; i < 4; i++) {
			//4개 랜덤 선택
			you.god_value[GT_SEIJA][2] |= 1 << rand_god.pop();
		}
	}
	printlog("", true, false, true, CL_seija);
	printlog("", true, false, true, CL_seija);
	printlog("", true, false, true, CL_seija);
	printlog("", true, false, true, CL_seija);
	printlog("", true, false, true, CL_seija);
	printlog("", true, false, true, CL_seija);
	printlog("", true, false, true, CL_seija);
	printlog("", true, false, true, CL_seija);


	while(loop_)
	{
		deletelog();
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_ASK),true,false,true,CL_seija);

		int num_ = 0;
		god_type select_[4];
		for (int i = GT_FIRST; i < GT_LAST; i++) {
			if (you.god_value[GT_SEIJA][2] & (1 << i)) {
				ostringstream ss;
				ss << string(1,(char)(num_+'a')) << " - " << seija_god_string(i, 0);
				select_[num_++] = (god_type)i;
				printlog(ss.str(), true, false, true, CL_help,(char)(num_+'a'));
			}
		}
		startSelection({'a', 'b', 'c', 'd', VK_ESCAPE});
		int key_ = waitkeyinput();
		endSelection();


		switch (key_)
		{
		case 'a':
		case 'A':
			next_ = select_[0];
			break;
		case 'b':
		case 'B':
			next_ = select_[1];
			break;
		case 'c':
		case 'C':
			next_ = select_[2];
			break;
		case 'd':
		case 'D':
			next_ = select_[3];
			break;
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_CANCLE), true, false, false, CL_small_danger);
			return false;
		}
		deletelog();
		printlog(seija_god_string(next_, 0), true, false, true, CL_help);
		printlog(seija_god_string(next_, 1), true, false, true, CL_small_danger);
		printlog(seija_god_string(next_, 2), true, false, true, CL_small_danger);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_YN),false,false, true,CL_help);
		printlog(" (",false,false,true,CL_help);
		printlog("y",false,false,true,CL_help, 'y');
		printlog("/",false,false,true,CL_help);
		printlog("n",false,false,true,CL_help, 'n');
		printlog(") ",false,false,true,CL_help);
		startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
		switch(waitkeyinput())
		{
		case 'Y':
		case 'y':
			loop_ = false;
			endSelection();
			break;
		case 'N':
		default:
			loop_ = true;
			endSelection();
			break;
		}

	}

	if(you.god_value[GT_SEIJA][1] & (1 << next_))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_GIFT_ALREADY),true,false,false,CL_normal);
		return false;
	}




	seija_real_gift(next_);
	
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_GIFT_APPEAR),true,false,false,CL_dark_good);

	AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_SEIJA_GIFT, PlaceHolderHelper(GetGodString(next_))),CL_help);
	you.god_value[GT_SEIJA][2] = 0;
	MoreWait();

	you.PunishUpDown(GetGodGiftTime(GT_SEIJA)-1,next_);
	you.gift_count = GetGodGiftTime(GT_SEIJA);
	
	//중복선물방지
	you.god_value[GT_SEIJA][1] |= 1 << next_;  


	printlog(seija_talk(next_, 7-pietyLevel(you.piety)),true,false,false,CL_seija);

	you.StepUpDownPiety(-1);
	
	if(pietyLevel(you.piety) == 0)
	{

		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_ABANDONED,true,false,false,CL_danger,
			PlaceHolderHelper(GetGodString(you.god)));
		

		AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_GOD_ABANDONED, PlaceHolderHelper(GetGodString(you.god))),CL_small_danger);
	
		for(int level_ = pietyLevel(you.piety);level_>=0;level_--)
			GetGodAbility(level_, false);	

		you.Ability(SKL_ABANDON_GOD,true,true);
		you.god = GT_NONE;

		item_infor t;
		env[current_level].MakeItem(you.position, makeitem(ITM_MISCELLANEOUS, 0, &t, EVK_MAGIC_HAMMER));
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_FINAL_GIFT), true, false, false, CL_dark_good);
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
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_SEIJA_ABIL_SWAP,true,false,false,CL_normal,
			 PlaceHolderHelper(hit_mon->GetName()->getName()));
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_ABIL_CATACLYSM),true,false,false,CL_normal);

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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_SEIJA_ABIL_CATACLYSM_FAIL),true,false,false,CL_normal);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_JOIN),true,false,false,CL_normal);
				return false;	
			}

			
			if(monster* hit_mon =(monster*)env[current_level].isMonsterPos(target.x,target.y,order))
			{	


				if(hit_mon->flag & M_FLAG_SUMMON)
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_JOIN_SUMMON),true,false,false,CL_normal);
					return false;	
				}
				if(!(hit_mon->flag & M_FLAG_FAIRY))
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_JOIN_ONLYFAIRY),true,false,false,CL_normal);
					return false;	
				}
				if(hit_mon->id == MON_ZOMBIE_FAIRY)
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_JOIN_ZOMBIEFAIRY),true,false,false,CL_normal);
					return false;
				}
				if(hit_mon->id == MON_MAID_FAIRY)
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_JOIN_MAIDFAIRY),true,false,false,CL_normal);
					return false;
				}
				if (hit_mon->dream)
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_JOIN_DREAM), true, false, false, CL_normal);
					return false;
				}
				if(hit_mon->level > you.level)
				{
					printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_LILLY_INVITE_FAIL_LEVEL, PlaceHolderHelper(to_string(hit_mon->level))),true,false,false,CL_normal);
					return false;
				}
				
				for(int j = 0; j < 5; j++)
				{
					if((you.lilly_allys[j].map_id == hit_mon->map_id && you.lilly_allys[j].floor == current_level) || hit_mon->flag & M_FLAG_ALLY)
					{
						printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_LILLY_ABIL_JOIN_ALREADY),true,false,false,CL_normal);
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
					LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_LILLY_INVITE,true,false,false,CL_normal,
						 PlaceHolderHelper(hit_mon->name.getName()),
						 PlaceHolderHelper(fairy_name[you.lilly_allys[i].name]));
		
					hit_mon->name = name_infor(fairy_name[you.lilly_allys[i].name]);

				}

				if(hit_mon->CanSpeak())
					printlog(fairy_speak(hit_mon, person_, FS_ENTER),true,false,false,CL_normal);
				
				you.god_value[GT_LILLY][i] = 1;
				
				if((hit_mon->flag & M_FLAG_UNIQUE)) //이름 지어주기
				{
					AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_INVITE_FAIRY_UNIQUE, PlaceHolderHelper(hit_mon->name.getName())),CL_lilly);
				}
				else{
					AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_INVITE_FAIRY_UNIQUE, PlaceHolderHelper(hit_mon->name.getName()), PlaceHolderHelper(hit_mon->name.getName())),CL_lilly);
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
								if(hit_mon->id == MON_LUNAR) {
									printlog(LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_BETRAY_LUNAR), PlaceHolderHelper(it->GetName()->getName())),true,false,false,CL_normal);
								}
								else if(hit_mon->id == MON_STAR){
									printlog(LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SUNNY_BETRAY_STAR), PlaceHolderHelper(it->GetName()->getName())),true,false,false,CL_normal);
								}
								break;
							case MON_LUNAR:
								if(hit_mon->id == MON_SUNNY) {
									printlog(LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_BETRAY_SUNNY), PlaceHolderHelper(it->GetName()->getName())),true,false,false,CL_normal);
								}
								else if(hit_mon->id == MON_STAR) {
									printlog(LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_LUNAR_BETRAY_STAR), PlaceHolderHelper(it->GetName()->getName())),true,false,false,CL_normal);
								}
								break;
							case MON_STAR:
								if(hit_mon->id == MON_SUNNY) {
									printlog(LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_BETRAY_SUNNY), PlaceHolderHelper(it->GetName()->getName())),true,false,false,CL_normal);
								}
								else if(hit_mon->id == MON_LUNAR) {
									printlog(LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_STAR_BETRAY_LUNAR), PlaceHolderHelper(it->GetName()->getName())),true,false,false,CL_normal);
								}
							}
						}
					}
				}



				return true;
			}
			else
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_JOIN_NOT_MONSTER),true,false,false,CL_normal);
				return false;	
			}
		}
	}

	
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_JOIN_FULL),true,false,false,CL_normal);	
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_CALL),true,false,false,CL_normal);
		return true;
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_CALL_FAIL),true,false,false,CL_normal);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_HEAL_FAIL),true,false,false,CL_normal);
						return false;
					}
					if(!hit_mon->isUserAlly())
					{						
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_HEAL_NOT_ALLY),true,false,false,CL_normal);
						return false;
					}
					soundmanager.playSound("buff");
					
					hit_mon->HpUpDown(max(1,hit_mon->max_hp*rand_int(10,35)/100),DR_NONE);
					LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_LILLY_ABIL_HEAL,true,false,false,CL_lilly,
						 PlaceHolderHelper(hit_mon->name.getName()));
					return true;
				}
			}
		}	
	}
	
	
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_HEAL_TARGET),true,false,false,CL_normal);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_FAIRY_WAR),true,false,false,CL_lilly);
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

	
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_LILLY_ABIL_FAIRY_WAR_FAIL),true,false,false,CL_normal);
	return false;
}



bool skill_okina_1(int power, bool short_, unit* order, coord_def target)
{
	if (current_level == OKINA_LEVEL){
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_MAKE_DOOR_FAIL), true, false, false, CL_normal);
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
						printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_BLOCK_INSIGHT), true, false, false, CL_normal);
						return false;
					}
					beam++;
				}

				LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_OKINA_ABIL_MAKE_DOOR,true,false,false,CL_okina,
					PlaceHolderHelper(dungeon_tile_tribe_type_string[env[current_level].dgtile[target.x][target.y].tile]));

				soundmanager.playSound("stone");
				env[current_level].changeTile(target, DG_CLOSE_DOOR);
				return true;
			}
			else {
				printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_BLOCK_INSIGHT), true, false, false, CL_normal);
				return false;
			}

		}
		else {
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_MAKE_DOOR_SHOULD_WALL), true, false, false, CL_normal);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_LOCKED_DOOR_ALREADY), false, false, false, CL_normal);
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
						LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_OKINA_ABIL_CLOSE_DOOR_OUT,false,false,false,CL_normal,
							PlaceHolderHelper(unit_->GetName()->getName()));
						unit_->SetXY(rit->x, rit->y);
						attack_infor temp_att(randC(2, 3 + power / 10), 2*( 3 + (power / 10)), 99, unit_, order->GetParentType(), ATT_RUSH, name_infor(LOC_SYSTEM_ATT_DOOR));
						unit_->damage(temp_att, true);
						unit_->SetConfuse(5+randA(5));
						unit_->PlusTimeDelay(-unit_->GetWalkDelay()); //1턴 행동을 쉰다.
						break;
					}

					rit++;
					if (rit.end()) {
						LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_OKINA_ABIL_CLOSE_DOOR_OUT_FAIL,true,false,false,CL_normal,
							PlaceHolderHelper(unit_->GetName()->getName()));
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_LOCKED_DOOR_YOU),true, false, false, CL_okina);
				return true;
			}
		}
		else {
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_TARGET_DOOR), true, false, false, CL_normal);
			return false;
		}
	}
	return false;
}
bool skill_okina_3(int power, bool short_, unit* order, coord_def target)
{
	if (current_level == OKINA_LEVEL){
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDOOR_FAIL), true, false, false, CL_normal);
		return false;
	}
	if (order->isplayer())
	{
		monster* this_unit_ = (monster*)env[current_level].isMonsterPos(target.x, target.y, &you);
		if (!this_unit_ || this_unit_->isUserAlly())
		{
			printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_SHOULD_TARGET_ENEMY), true, false, false, CL_normal);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDOOR_PATH_FAIL), true, false, false, CL_danger);
				return false;
			}

			beam++;

			unit *unit2_ = env[current_level].isMonsterPos(beam->x, beam->y, &you);
			if (unit2_) {
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDOOR_CANT_CREATE), true, false, false, CL_normal);
				return false;
			}
			if (!(env[current_level].dgtile[order->position.x][order->position.y].isFloor() ||
				env[current_level].dgtile[order->position.x][order->position.y].isDoor() ||
				env[current_level].dgtile[order->position.x][order->position.y].isTemple()) &&
				!env[current_level].dgtile[beam->x][beam->y].isBreakable()
				)
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDOOR_CANT_CREATE), true, false, false, CL_normal);
				return false;
			}

			soundmanager.playSound("blink");
			env[current_level].changeTile((*beam), DG_OPEN_DOOR);
			you.SetXY(beam->x, beam->y);
			unit_->LostTarget();
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDOOR), true, false, false, CL_okina);
			return true;
		}
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_BLOCK_INSIGHT), true, false, false, CL_normal);
		return false;
	}
	return false;
}
bool skill_okina_4(int power, bool short_, unit* order, coord_def target)
{
	if (current_level == OKINA_LEVEL){
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDANCER_NO_NEED), true, false, false, CL_normal);
		return false;
	}
	int num_ = 1;
	int id_ = MON_MAI2;
	bool loop_ = true;
	while (loop_) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDANCER_ASK), true, false, false, CL_help);
		printlog("a - " + LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDANCER_ASK_MAI), true, false, false, CL_okina,'a');
		printlog("b - " + LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDANCER_ASK_SATONO), true, false, false, CL_okina, 'b');
		printlog("c - " + LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_BACKDANCER_ASK_BACKDANCERS), true, false, false, CL_okina, 'c');
		
		startSelection({'a', 'b', 'c',VK_ESCAPE});
		InputedKey inputedKey;
		switch (waitkeyinput(inputedKey))
		{
		case 'a':
		case 'A':
			id_ = MON_MAI2;
			loop_ = false;
			endSelection();
			break;
		case 'b':
		case 'B':
			id_ = MON_SATONO;
			loop_ = false;
			endSelection();
			break;
		case 'c':
		case 'C':
			num_ = 2;
			loop_ = false;
			endSelection();
			break;
		default:
			endSelection();
			break;			
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				endSelection();
				break;
			}
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE), true, false, false, CL_normal);
			endSelection();
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
			LocalzationManager::printLogWithKey(LOC_SYSTEM_MAGIC_SUMMON,false,false,false,CL_magic,
				PlaceHolderHelper(mon_->name.getName()));
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
			printlog(LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_MAI2_CHEERING), PlaceHolderHelper(speak_->GetName()->getName())) , true, false, false, CL_normal);
		}
		else if (speak_->GetId() == MON_SATONO) {
			printlog(LocalzationManager::formatString(LocalzationManager::speakString(SPEAK_SATONO_CHEERING), PlaceHolderHelper(speak_->GetName()->getName())) , true, false, false, CL_normal);
		}
	}

	return return_;
}
bool skill_okina_5(int power, bool short_, unit* order, coord_def target)
{
	if (current_level == OKINA_LEVEL){
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_DOOR_ESCAPE_ALREADY), true, false, false, CL_normal);
		return false;
	}

	if (env[current_level].dgtile[order->position.x][order->position.y].isFloor() ||
		env[current_level].dgtile[order->position.x][order->position.y].isDoor() ||
		env[current_level].dgtile[order->position.x][order->position.y].isTemple()) {
		env[current_level].changeTile(order->position, DG_OPEN_DOOR);
	}
	else {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_DOOR_ESCAPE_CANTDOOR), true, false, false, CL_normal);
		return false;
	}

	//log에 오키나레벨로 도착함을 저장
	deque<monster*> dq;
	soundmanager.playSound("blink");
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_OKINA_ABIL_DOOR_ESCAPE), true, false, false, CL_okina);
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
	printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_OKINA_ABIL_DOOR_ESCAPE_WELCOME), true, false, false, CL_normal);

	AddNote(you.turn, CurrentLevelString(current_level), LocalzationManager::formatString(LOC_SYSTEM_NOTE_RUN_AWAY, PlaceHolderHelper(CurrentLevelString(current_level))), CL_normal);
	//you.resetLOS(false);
	return true;
}
bool skill_junko_1(int power, bool short_, unit* order, coord_def target)
{
	if (order->position == target)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_ASK_SUICIDE), true, false, false, CL_small_danger);
		return false;
	}
	beam_iterator beam(order->position, order->position);
	int damage_ = 4 + power / 10;
	int multi_ = 3;
	int hit_ = 10 + power / 15;
	if (CheckThrowPath(order->position, target, beam))
	{
		beam_infor temp_infor(randC(multi_, damage_), multi_ * (damage_), hit_, order, order->GetParentType(), SkillLength(SKL_JUNKO_1), 1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_TANMAC));
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_ABIL_HASTE_FAIL), true, false, false, CL_normal);
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
string getJunkoString(int kind_)
{
	switch (kind_)
	{
	case 1:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_SKILL);
	case 2:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_RESIST);
	case 3:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_MP);
	case 4:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_POWER);
	case 5:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_LIFE);
	case 6:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_ITEM);
	case 7:
		return LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_SYSTEM);
	}

	return LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_BUG);
}
bool skill_junko_4(int power, bool short_, unit* order, coord_def target)
{

	int kind_ = 0;
	bool loop_ = true;
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_INFO), true, false, false, CL_danger);
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_WARN) +" ", false, false, false, CL_danger);
	while (loop_) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_ASK), true, false, false, CL_help);
		printlog("a - " + getJunkoString(you.god_value[GT_JUNKO][0]), true, false, false, CL_junko,'a');
		printlog("b - " + getJunkoString(you.god_value[GT_JUNKO][1]), true, false, false, CL_junko, 'b');
		printlog("c - " + getJunkoString(you.god_value[GT_JUNKO][2]), true, false, false, CL_junko, 'c');
		printlog("d - " + LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_OTHER), true, false, false, CL_junko, 'd');
		
		startSelection({'a', 'b', 'c','d',VK_ESCAPE});
		InputedKey inputedKey;
		switch (waitkeyinput(inputedKey))
		{
		case 'a':
		case 'A':
			kind_ = you.god_value[GT_JUNKO][0];
			loop_ = false;
			endSelection();
			break;
		case 'b':
		case 'B':
			kind_ = you.god_value[GT_JUNKO][1];
			loop_ = false;
			endSelection();
			break;
		case 'c':
		case 'C':
			kind_ = you.god_value[GT_JUNKO][2];
			loop_ = false;
			endSelection();
			break;
		case 'd':
		case 'D':	
		{
			endSelection();
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_REALLY), false, false, false, CL_help);
			printlog(" (",false,false,false,CL_help);
			printlog("y",false,false,false,CL_help, 'y');
			printlog("/",false,false,false,CL_help);
			printlog("n",false,false,false,CL_help, 'n');
			printlog(") ",false,false,false,CL_help);
			startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
			
			switch (waitkeyinput(inputedKey))
			{
			case 'y':
			case 'Y':
				endSelection();
				you.PietyUpDown(-(you.piety-140));
				you.god_value[GT_JUNKO][0] = 0;
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_DELAY), true, false, false, CL_normal);
				return true;
			case -1:
			case 'n':
			case 'N':
			default:
				printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE), true, false, false, CL_normal);
				endSelection();
				return false;
			}
		}
			break;
		default:
			endSelection();
			break;
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				endSelection();
				break;
			}
		case VK_ESCAPE:
			endSelection();
			printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE), true, false, false, CL_normal);
			return false;
		}
	}
	if (kind_ == 0)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_UNKNOWN_SELECT), true, false, false, CL_normal);
		return false;
	}

	switch (kind_)
	{
	case 1: //스킬순화
		while (true)
		{
			view_skill(LOC_SYSTEM_DISPLAY_MANAGER_JUNKO_SKILL);
			int key_ = waitkeyinput(true);
			if ((key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z'))
			{
				int num = (key_ >= 'a' && key_ <= 'z') ? key_ - 'a' : key_ - 'A' + 26;
				if (num < SKT_MAX && you.GetSkillLevel(num, false) < 27 && !you.cannotSkillup(num))
				{
					if (you.skill[num].aptit < 0)
					{
						changedisplay(DT_GAME);
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_SKILL_APTIT), true, false, false, CL_warning);
						MoreWait();
					}
					else
					{
						printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_SKILL_ASK,
						PlaceHolderHelper(skill_string((skill_type)num)),PlaceHolderHelper(to_string(you.GetSkillLevel(num, false)))), false, false, true, CL_danger);
						printlog(" (",false,false,true,CL_danger);
						printlog("y",false,false,true,CL_danger, 'y');
						printlog("/",false,false,true,CL_danger);
						printlog("n",false,false,true,CL_danger, 'n');
						printlog(") ",false,false,true,CL_danger);
						startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
						changedisplay(DT_GAME);

						int key__ = waitkeyinput(true);
						endSelection();
						if (key__ == 'y' || key__ == 'Y')
						{
							you.SetPureSkill(num);
							printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_SKILL_SUCCESS, PlaceHolderHelper(skill_string((skill_type)num))), true, false, false, CL_junko);
							AddNote(you.turn, CurrentLevelString(), LocalzationManager::formatString(LOC_SYSTEM_NOTE_JUNKO_PURIFICATION_SKILL,PlaceHolderHelper(skill_string((skill_type)num))), CL_junko);
							break;
						}
					}
				}
				else
				{
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_SKILL_CANT), true, false, false, CL_normal);
					changedisplay(DT_GAME);
					return false;
				}
			}
			else
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_BE_PRUDENT), true, false, false, CL_normal);
				changedisplay(DT_GAME);
				return false;
			}
		}
		break;
	case 2:
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_RESIST_ASK), true, false, false, CL_junko);
		printlog("a-"+LocalzationManager::locString(LOC_SYSTEM_FIRE_RESIST), false, false, false, CL_junko,'a');
		printlog(" ", false, false, false, CL_junko);
		printlog("b-"+LocalzationManager::locString(LOC_SYSTEM_COLD_RESIST), false, false, false, CL_junko,'b');
		printlog(" ", false, false, false, CL_junko);
		printlog("c-"+LocalzationManager::locString(LOC_SYSTEM_ELEC_RESIST), true, false, false, CL_junko,'c');

		startSelection({'a', 'b', 'c', VK_ESCAPE});
		int key_ = waitkeyinput(true);
		endSelection();
		switch (key_)
		{
		case 'a':
			you.DeleteProperty(TPT_FIRE_RESIST);
			you.SetProperty(TPT_FIRE_IMUNE, 200);
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_RESIST_FIRE), true, false, false, CL_junko);
			AddNote(you.turn, CurrentLevelString(), LocalzationManager::locString(LOC_SYSTEM_NOTE_JUNKO_PURIFICATION_FIRERESIST), CL_junko);
			break;
		case 'b':
			you.DeleteProperty(TPT_COLD_RESIST);
			you.SetProperty(TPT_COLD_IMUNE, 200);
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_RESIST_COLD), true, false, false, CL_junko);
			AddNote(you.turn, CurrentLevelString(), LocalzationManager::locString(LOC_SYSTEM_NOTE_JUNKO_PURIFICATION_COLDRESIST), CL_junko);
			break;
		case 'c':
			you.DeleteProperty(TPT_ELEC_RESIST);
			you.SetProperty(TPT_ELEC_IMUNE, 200);
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_RESIST_ELEC), true, false, false, CL_junko);
			AddNote(you.turn, CurrentLevelString(), LocalzationManager::locString(LOC_SYSTEM_NOTE_JUNKO_PURIFICATION_ELECRESIST), CL_junko);
			break;
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_BE_PRUDENT), true, false, false, CL_normal);
			changedisplay(DT_GAME);
			return false;
		}
		break;
	}
	case 3:
		you.SetProperty(TPT_PURE_MP, 1);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_MP_SUCCESS), true, false, false, CL_junko);
		AddNote(you.turn, CurrentLevelString(), LocalzationManager::locString(LOC_SYSTEM_NOTE_JUNKO_PURIFICATION_MP), CL_junko);
		break;
	case 4:
		you.SetProperty(TPT_PURE_POWER, 1);
		iden_list.autopickup[IDEN_CHECK_ETC_START] = false;
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_POWER_SUCCESS), true, false, false, CL_junko);
		AddNote(you.turn, CurrentLevelString(), LocalzationManager::locString(LOC_SYSTEM_NOTE_JUNKO_PURIFICATION_POWER), CL_junko);
		break;
	case 5:
		you.SetProperty(TPT_PURE_LIFE, 2);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_LIFE_SUCCESS), true, false, false, CL_junko);
		AddNote(you.turn, CurrentLevelString(), LocalzationManager::locString(LOC_SYSTEM_NOTE_JUNKO_PURIFICATION_LIFE), CL_junko);
		break;
	case 6:
		while (1)
		{
			view_item(IVT_PURE_ITEM, LOC_SYSTEM_DISPLAY_MANAGER_JUNKO);
			InputedKey inputedKey;
			int key_ = waitkeyinput(inputedKey,true);
			if ((key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z'))
			{
				item *item_ = you.GetItem(key_);
				if (item_)
				{
					if ((item_->type >= ITM_WEAPON_FIRST && item_->type < ITM_WEAPON_LAST) || (item_->type >= ITM_ARMOR_FIRST && item_->type < ITM_ARMOR_LAST))
					{
						printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_ITEM_WARNING, PlaceHolderHelper(item_->GetName())), false, false, true, CL_small_danger);
						printlog(" (",false,false,true,CL_small_danger);
						printlog("y",false,false,true,CL_small_danger, 'y');
						printlog("/",false,false,true,CL_small_danger);
						printlog("n",false,false,true,CL_small_danger, 'n');
						printlog(") ",false,false,true,CL_small_danger);
						startSelection({SPECIAL_CLINKABLE_Y, SPECIAL_CLINKABLE_N});
						changedisplay(DT_GAME);

						int key__ = waitkeyinput(true);
						endSelection();
						if (key__ == 'y' || key__ == 'Y')
						{
							printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_ITEM_FINISH, PlaceHolderHelper(item_->GetName())), true, false, false, CL_junko);
							AddNote(you.turn, CurrentLevelString(), LocalzationManager::formatString(LOC_SYSTEM_NOTE_JUNKO_PURIFICATION_ITEM, PlaceHolderHelper(item_->GetName())), CL_junko);

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
						printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_ITEM_CANT), true, false, false, CL_normal);
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
				view_item(IVT_SELECT, LOC_SYSTEM_DISPLAY_MANAGER_JUNKO);
			}
			else if(key_ == -1) {
				if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
					int get_item_move_ = getDisplayMove();
					if(iteminfor_(inputedKey.val1, true))
						break;
					rollback_item(IVT_PURE_ITEM,LOC_SYSTEM_DISPLAY_MANAGER_JUNKO);
					setDisplayMove(get_item_move_);
				} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
					changemove(-32);  //아래
				} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
					changemove(32);  //위
				} else if(inputedKey.isRightClick()) {
					printlog(LocalzationManager::locString(LOC_SYSTEM_BE_PRUDENT), true, false, false, CL_normal);
					changedisplay(DT_GAME);
					return false;
				}
			}
			else if (key_ == VK_ESCAPE)
			{
				printlog(LocalzationManager::locString(LOC_SYSTEM_BE_PRUDENT), true, false, false, CL_normal);
				changedisplay(DT_GAME);
				return false;
			}
		}
		changedisplay(DT_GAME);
		break;
	case 7:
		you.SetProperty(TPT_PURE_SYSTEM, 1);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_SYSTEM_SUCCESS), true, false, false, CL_junko);
		AddNote(you.turn, CurrentLevelString(), LocalzationManager::locString(LOC_SYSTEM_NOTE_JUNKO_PURIFICATION_SYSTEM), CL_junko);
		break;
	}




	soundmanager.playSound("levelup");
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JUNKO_PURIFICATION_TALK), true, false, false, CL_junko);
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
	bool short_info =  option_mg.getWidth() < 1000;
	while (loop_) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_ASK), true, false, false, CL_help);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_INFO1), short_info?false:true, false, false, CL_joon);
		if(!short_info)
			printlog("                   ", false, false, false, CL_joon);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_INFO2), true, false, false, CL_joon,'a');
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_INFO3), short_info?false:true, false, false, CL_sion);
		if(!short_info)
			printlog("                   ", false, false, false, CL_sion);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_INFO4), true, false, false, CL_sion,'b');
		
		startSelection({'a', 'b', VK_ESCAPE});
		InputedKey inputedKey;
		switch (waitkeyinput(inputedKey))
		{
		case 'a':
		case 'A':
			god_ = 1;
			loop_ = false;
			endSelection();
			break;
		case 'b':
		case 'B':
			god_ = 2;
			loop_ = false;
			endSelection();
			break;
		default:
			break;
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				endSelection();
				break;
			}
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE), true, false, false, CL_normal);
			endSelection();
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_J_TALK1), true, false, false, CL_joon);
			break;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_J_TALK2), true, false, false, CL_joon);
			break;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_J_TALK3), true, false, false, CL_joon);
			break;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_J_TALK4), true, false, false, CL_joon);
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
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_S_TALK1), true, false, false, CL_sion);
			break;
		case 1:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_S_TALK2), true, false, false, CL_sion);
			break;
		case 2:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_S_TALK3), true, false, false, CL_sion);
			break;
		case 3:
			printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_S_TALK4), true, false, false, CL_sion);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_JOON_AOE), true, false, false, CL_joon);
			} 

			it->SetConfuse(rand_int(5,10)+randA(power/20), true);
			int damage_ = (20 + (you.level * 2))*(power+400.0f)/400;


			attack_infor temp_att(randC(5, damage_/5), damage_, 99, order, order->GetParentType(), ATT_NORMAL_BLAST, name_infor(LOC_SYSTEM_ATT_FIRECRAKER));
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_LOS_NOMON), true, false, false, CL_normal);
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
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_SION_AOE), true, false, false, CL_sion);
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
		beam_infor temp_infor(0, 0, 99, order, order->GetParentType(), SkillLength(SKL_JOON_AND_SION_4), 1, BMT_PENETRATE, ATT_THROW_NONE_DAMAGE, name_infor(LOC_SYSTEM_ATT_SION));

		soundmanager.playSound("wind");
		coord_def c_ = throwtanmac(44, beam, temp_infor, NULL);
		unit* hit_mon = env[current_level].isMonsterPos(c_.x, c_.y, order);
		if (hit_mon && !hit_mon->isplayer())
		{
			monster* mon_ = (monster*)hit_mon;
			if (mon_->flag & M_FLAG_INANIMATE)
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_FAIL,true,false,false,CL_sion,
					 PlaceHolderHelper(hit_mon->GetName()->getName()));
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

			if (monster* mon__ = BaseSummon(MON_SION, 100, true, false, 2, hit_mon, hit_mon->position, SKD_OTHER, -1))
			{
				mon__->s_ally = -1;
				mon__->flag |= M_FLAG_ALLY;
				mon__->SetInvincibility(-1, false);
			}

			if (hit_mon->isYourShight())
			{
				LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_SUCCESS,true,false,false,CL_sion,
					 PlaceHolderHelper(hit_mon->GetName()->getName()));
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
	printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_JOON_AND_SION_POSSESSION_END) + " ", false, false, false, CL_joon_and_sion);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_DRAIN_CRAVING_OLD), true, false, false, CL_normal);
		return false;
	} else if (env[current_level].popular == 0) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_DRAIN_CRAVING_ALREADY), true, false, false, CL_normal);
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
		you.PietyUpDown(piety_);
		printlog(LocalzationManager::formatString(LOC_SYSTEM_GOD_MIKO_DRAIN_CRAVING, PlaceHolderHelper(to_string(ok_))), true, false, false, CL_miko);
		env[current_level].popular = 0;
		soundmanager.playSound("powerup");
		return true;
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_DRAIN_CRAVING_FAIL), true, false, false, CL_normal);
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_ALREADY_FAIL), true, false, false, CL_normal);
		return false;
	}
	else {
		soundmanager.playSound("buff");
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_GIFT,true,false,false,CL_miko,
			 PlaceHolderHelper(LOC_SYSTEM_GOD_MIKO));
		return true;
	}
	return true;
}
bool skill_miko_4(int power, bool short_, unit* order, coord_def target)
{
	int resist_ = 0;
	bool loop_ = true;
	while (loop_) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_RESIST_ASK), true, false, false, CL_miko);

		pair<char,LOCALIZATION_ENUM_KEY> resists[5] = {
			make_pair('a',LOC_SYSTEM_FIRE_RESIST),
			make_pair('b',LOC_SYSTEM_COLD_RESIST),
			make_pair('c',LOC_SYSTEM_ELEC_RESIST),
			make_pair('d',LOC_SYSTEM_POISON_RESIST),
			make_pair('e',LOC_SYSTEM_CONFUSE_RESIST)
		};
		for(int i =0; i<5; i++) {
			ostringstream ss;
			ss << resists[i].first << '-' << LocalzationManager::locString(resists[i].second);
			printlog(ss.str(), false, false, false, CL_miko, resists[i].first);
			if(PrintCharWidth(ss.str()) < 16) {
				printlog(string(16-PrintCharWidth(ss.str()),' '), false, false, false, CL_miko);
			} else {
				printlog(" ", false, false, false, CL_miko);
			}

		}
		startSelection({'a', 'b', 'c', 'd', 'e', VK_ESCAPE});
		InputedKey inputedKey;
		switch (waitkeyinput(inputedKey))
		{
		case 'a':
		case 'A':
			resist_ = 1;
			loop_ = false;
			endSelection();
			break;
		case 'b':
		case 'B':
			resist_ = 2;
			loop_ = false;
			endSelection();
			break;
		case 'c':
		case 'C':
			resist_ = 3;
			loop_ = false;
			endSelection();
			break;
		case 'd':
		case 'D':
			resist_ = 4;
			loop_ = false;
			endSelection();
			break;
		case 'e':
		case 'E':
			resist_ = 5;
			loop_ = false;
			endSelection();
			break;
		default:
			endSelection();
			break;			
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				endSelection();
				break;
			}
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE), true, false, false, CL_normal);
			endSelection();
			return false;
		}
	}
	enterlog();
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_ALREADY_FAIL), true, false, false, CL_normal);
		return false;
	}
	else {
		soundmanager.playSound("buff");
		LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_GIFT,true,false,false,CL_miko,
			 PlaceHolderHelper(LOC_SYSTEM_GOD_MIKO));
		return true;

	}
}
bool skill_miko_5(int power, bool short_, unit* order, coord_def target)
{
	if(you.isSetMikoBuff(0)) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_ALREADY_CLOAK), true, false, false, CL_normal);
		return false;
	}
	int bonus_ = 0;
	bool loop_ = true;
	while (loop_) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_CLOAK_ASK), true, false, false, CL_miko);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_CLOAK_RED), true, false, false, CL_miko, 'a');
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_CLOAK_BLUE), true, false, false, CL_miko, 'b');
		startSelection({'a', 'b', VK_ESCAPE});
		InputedKey inputedKey;
		switch (waitkeyinput(inputedKey))
		{
		case 'a':
		case 'A':
			bonus_ = 1;
			loop_ = false;
			endSelection();
			break;
		case 'b':
		case 'B':
			bonus_ = 2;
			loop_ = false;
			endSelection();
			break;
		default:
		endSelection();
			break;			
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				endSelection();
				break;
			}
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE), true, false, false, CL_normal);
			endSelection();
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
	LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_GIFT,true,false,false,CL_miko,
		 PlaceHolderHelper(LOC_SYSTEM_GOD_MIKO));
	return true;
}
bool skill_miko_6(int power, bool short_, unit* order, coord_def target)
{
	if (you.isSetMikoBuff(1)) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULARITY_BURST_ALREADY), true, false, false, CL_normal);
		return false;
	}
	int bonus_ = 0;
	bool loop_ = true;
	while (loop_) {
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULARITY_BURST_ASK), true, false, false, CL_miko);
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULARITY_BURST_INFO1), true, false, false, CL_miko, 'a');
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULARITY_BURST_INFO2), true, false, false, CL_miko, 'b');
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIKO_POPULARITY_BURST_INFO3), true, false, false, CL_miko, 'c');
		startSelection({'a', 'b', 'c', VK_ESCAPE});
		InputedKey inputedKey;
		switch (waitkeyinput(inputedKey))
		{
		case 'a':
		case 'A':
			bonus_ = 1;
			loop_ = false;
			endSelection();
			break;
		case 'b':
		case 'B':
			bonus_ = 2;
			loop_ = false;
			endSelection();
			break;
		case 'c':
		case 'C':
			bonus_ = 3;
			loop_ = false;
			endSelection();
			break;
		default:
			endSelection();
			break;
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				endSelection();
				break;
			}
		case VK_ESCAPE:
			printlog(LocalzationManager::locString(LOC_SYSTEM_DO_CANCLE), true, false, false, CL_normal);
			endSelection();
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
	LocalzationManager::printLogWithKey(LOC_SYSTEM_GOD_GIFT,true,false,false,CL_miko,
		 PlaceHolderHelper(LOC_SYSTEM_GOD_MIKO));
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
		printlog(LocalzationManager::locString(LOC_SYSTEM_SILENCE_PENALTY),true,false,false,CL_normal);
		return 0;		
	}
	
	if(SkillFlagCheck(skill,S_FLAG_DELAYED) && you.GetExhausted())
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_DELAYED),true,false,false,CL_normal);	
		return false;
	}
	if(randA_1(100) > SkillDiffer(skill))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_SKILL_FAIL),true,false,false,CL_normal);
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
				printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_MIMA_PUNISH_SPELLDOWN),true,false,false,CL_green);
			}
			if(wiz_list.wizard_mode == 1)
			{
				printlog(LocalzationManager::formatString(LOC_SYSTEM_DEBUG_SPELLPOWER, PlaceHolderHelper(to_string(power)),PlaceHolderHelper(to_string(SkillCap(skill)))),true,false,false,CL_help);
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
			default:
				break;
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
	default:
		break;
	}
	return 0;
}


