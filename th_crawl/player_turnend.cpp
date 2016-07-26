//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: player_.cpp
//
// 내용: player관련 함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "player.h"
#include "unit.h"
#include "environment.h"
#include "beam.h"
#include "item.h"
#include "dump.h"
#include "potion.h"
#include "scroll.h"
#include "key.h"
#include "save.h"
#include "skill_use.h"
#include "weapon.h"
#include "god.h"
#include "note.h"
#include "spellcard.h"
#include "alchemy.h"
#include "tensi.h"
extern players you;
extern HANDLE mutx;


interupt_type players::TurnEnd(bool *item_delete_)
{
	you.maybeAction();
	WaitForSingleObject(mutx, INFINITE);
	inter = IT_NONE;
	env[current_level].CheckFloor();
	int delay_ = GetDelay();
	if((s_haste || alchemy_buff == ALCT_HASTE) && !s_slow)
		delay_ = delay_*0.7f;
	else if(s_slow && !(s_haste || alchemy_buff == ALCT_HASTE))
		delay_ = delay_*1.5f;

	if(GetStatPanalty()) //스탯패널티
	{
		delay_ = delay_*2.0f;
	}

	if(as_penalty > GetPenaltyMinus(3))
		delay_ *= 2;


	if(s_the_world!=0)
		delay_ = 0;
	prev_action = ACTT_NONE;



	if(s_tele || teleport_curse)
	{
		if(s_tele == 1 || (teleport_curse && !randA(100)))
		{
			Teleport();
			if(env[current_level].isInSight(position))
				printlog("당신은 약간 공간이 어긋난 것을 눈치챘다.",false,false,false,CL_normal);
			else
				printlog("갑자기 당신 주변이 변화했다.",false,false,false,CL_normal);
			SetInter(IT_TELE);
		}
		if(s_tele)
			s_tele--;
	}


	for(list<buff_class>::iterator it=buff_list.begin();it!=buff_list.end();)
	{
		list<buff_class>::iterator temp = it;
		it++;
		if(temp->turn>0){
			temp->turn--;
		}
		else{
			UpDownBuff(temp->stat,-1*temp->value);
			buff_list.erase(temp);
		}
	}

	

	if(s_autumn>0)
	{
		s_autumn --;
	}


	ReleaseMutex(mutx);
	if(you.s_the_world==0 || you.s_the_world==1)
		env[current_level].ActionSmoke(delay_);
	env[current_level].ActionFloor(delay_);
	if(you.s_the_world==0 || you.s_the_world==1)
	{
		env[current_level].ActionMonsterSpecial(delay_);
		if(env[current_level].ActionSmokeEffect())
		{
			inter = IT_SMOKE;
		}
	}
	WaitForSingleObject(mutx, INFINITE);
	SetInter(resetLOS());
	sight_reset = false;
	turn++;
	if(delay_){
		real_turn+=delay_;
		if(player_move){
			prev_real_turn = delay_;
			player_move = false;
		}
		else
			prev_real_turn+=delay_;
	}
	ReleaseMutex(mutx);
	if(env[current_level].ActionItem(delay_))
	{//아이템이 도중 삭제되었다.
		if(item_delete_)
			(*item_delete_) = true;
	}
	if(env[current_level].ActionEvent(delay_))
			SetInter(IT_EVENT);
	WaitForSingleObject(mutx, INFINITE);
	bool p_del = false;
	for(list<item>::iterator it = item_list.begin();it!=item_list.end();)
	{
		if(it->type == ITM_FOOD && it->value1 == 0)
		{
			it->value3--;
			if(it->value3 == 0)
			{
				list<item>::iterator temp = it;
				it++;
				if(!p_del)
				{
					printlog("인벤토리에 있는 P템이 사라졌다.",false,false,false,CL_normal);
					p_del = true;
				}
				DeleteItem(temp);
			}
			else
				it++;
		}
		else if(it->type >=ITM_WEAPON_FIRST && it->type<ITM_WEAPON_LAST && it->value6 > 0)
		{
			it->value6--;
			if(it->value6 == 0)
			{
				switch(it->value5)
				{
				case WB_FIRE:			
					printlog("무기가 타오르는 것을 멈췄다.",true,false,false,CL_normal);
					break;
				case WB_COLD:			
					printlog("무기에서 나오던 냉기가 그쳤다.",true,false,false,CL_normal);
					break;		
				case WB_POISON:			
					printlog("더이상 무기에서 독이 떨어지지 않는다.",true,false,false,CL_normal);	
					break;	
				case WB_CURSE:		
					printlog("무기에서 저주의 힘이 약해졌다.",true,false,false,CL_normal);	
					break;
				case WB_WEATHER	:
					printlog("무기에서 비상의 기운은 더이상 느껴지지않는다.",true,false,false,CL_normal);	
					break;
				case WB_AUTUMN:
					printlog("무기는 더이상 쓸쓸해보이지 않는다.",true,false,false,CL_normal);	
					break;
				case WB_MANA_REGEN:
					printlog("영력의 흐름이 사라졌다.",true,false,false,CL_white_blue);	
					break;
				case WB_FAST_CAST:
					printlog("머리회전이 다시 둔해졌다.",true,false,false,CL_white_blue);	
					break;
				case WB_PROTECT:
					AcUpDown(0,-5);
					printlog("보호가 사라졌다.",true,false,false,CL_white_blue);	
					break;
				default:			
					printlog("방금 무기는 버그에 걸려있다.",true,false,false,CL_danger);	
					break;		
				}
				it->value5 = 0;
			}
			it++;
		}
		else
			it++;
	}
	if(alchemy_buff == ALCT_POISON_BODY)
	{
		for(auto it = env[current_level].mon_vector.begin();it != env[current_level].mon_vector.end(); it++)
		{
			if((you.position.x-it->position.x)*(you.position.x-it->position.x)+(you.position.y-it->position.y)*(you.position.y-it->position.y)<=2)
			{					
				it->SetPoison(5+randA(5), 50, false);
			}
		}
	}

	ReleaseMutex(mutx);
	env[current_level].ActionMonster(delay_);
	WaitForSingleObject(mutx, INFINITE);
	if(sight_reset) //몬스터가 만들어낸 구름에 시야가 가릴 경우가 생길경우
		SetInter(resetLOS()); //굉장히 연산이 많이 들어가는 작업이므로 필요할때만 불러야함
	env[current_level].ClearShadow();
	ReleaseMutex(mutx);
	if(s_poison)
	{
		if(poison_percent(s_poison))
		{
			int damage_;
			damage_ = HpUpDown(-poison_damage(s_poison),DR_POISON);
			if(damage_==-1)
			{
				printlog("독의 데미지를 받고 있다.",false,false,false,CL_normal);
				if(hp<30)					
					SetInter(IT_POISON);
			}
			else if(damage_>=-4)
			{
				printlog("심한 독의 데미지를 받고 있다.",false,false,false,CL_small_danger);
				if(hp<100)					
					SetInter(IT_POISON);
			}
			else
			{
				printlog("매우 심한 독의 데미지를 받고 있다.",false,false,false,CL_danger);
				SetInter(IT_POISON);
			}
		}
		s_poison--;
		if(!s_poison)
			printlog("독이 치료되었다.",false,false,false,CL_good);
		else if(s_poison%30 == 0)
			printlog("독에서 약간 회복되었다.",false,false,false,CL_good);
	}
	WaitForSingleObject(mutx, INFINITE);
	if(s_might)
	{
		s_might--;
		if(!s_might)
		{
			printlog("힘이 원래대로 돌아왔다.",false,false,false,CL_blue);
			StatUpDown(-5, STAT_STR);
			SetInter(IT_STAT);
		}
	}
	if(s_clever)
	{
		s_clever--;
		if(!s_clever)
		{
			printlog("지능이 원래대로 돌아왔다.",false,false,false,CL_blue);
			StatUpDown(-5, STAT_INT);
			SetInter(IT_STAT);
		}
	}
	if(s_agility)
	{
		s_agility--;
		if(!s_agility)
		{
			printlog("민첩이 원래대로 돌아왔다.",false,false,false,CL_blue);
			StatUpDown(-5, STAT_DEX);
			EvUpDown(0,-5);
			SetInter(IT_STAT);
		}
	}
	{
		if(s_str != m_str && randA_1(20000) <= delay_)
		{
			s_str++;
			printlog("잃어버린 힘이 회복되었다.",false,false,false,CL_blue);
		}	
		else if(s_dex != m_dex && randA_1(20000) <= delay_)
		{
			s_dex++;
			printlog("잃어버린 민첩이 회복되었다.",false,false,false,CL_blue);
		}
		else if(s_int != m_int && randA_1(20000) <= delay_)
		{
			s_int++;
			printlog("잃어버린 지능이 회복되었다.",false,false,false,CL_blue);
		}
	}
	if(s_haste)
	{
		s_haste--;
		if(!s_haste && alchemy_buff != ALCT_HASTE)
		{
			printlog("속도가 원래대로 돌아왔다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
		if(s_haste == 10 && (alchemy_buff != ALCT_HASTE || alchemy_time<10))
		{
			printlog("속도가 돌아오고 있다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_wind)
	{
		s_wind--;
		if(!s_wind)
		{
			printlog("당신에게 감겨있던 바람이 빠져나갔다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_knife_collect)
	{
		s_knife_collect--;
		if(!s_knife_collect)
		{
			printlog("더이상 탄막이 자동으로 회수되지 않는다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_drunken)
	{
		s_drunken--;
		if(!s_drunken)
		{
			printlog("당신은 제정신을 차렸다.",false,false,false,CL_white_blue);
			SetInter(IT_STAT);
		}
	}
	if(env[current_level].isViolet(you.position))
		you.SetLunatic(2);
	if(s_lunatic)
	{
		s_lunatic--;
		if(!s_lunatic)
		{
			printlog("당신의 광기는 끝났다.",false,false,false,CL_white_blue);
			SetInter(IT_STAT);
		}
	}
	if(alchemy_time)
	{



		alchemy_time--;
		
		if(alchemy_time == 0)
		{
			alchemyonoff(alchemy_buff,false);
			SetInter(IT_STAT);
			alchemy_buff= ALCT_NONE;
		}
		else if(alchemy_time == 10)
		{
			alchemyalmostoff(alchemy_buff);
		}


	}


	if(s_confuse)
	{
		s_confuse--;
		if(!s_confuse)
		{
			printlog("혼란스러움이 사라졌다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_slow)
	{
		s_slow--;
		if(!s_slow)
		{
			printlog("속도가 원래대로 돌아왔다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_frozen)
	{
		s_frozen--;
		if(!s_frozen)
		{
			printlog("얼어붙었던 몸이 녹았다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_elec)
	{
		int power_=min(SpellCap(SPL_SHOCK),you.GetSpellPower(SpellSchool(SPL_SHOCK,0),SpellSchool(SPL_SHOCK,1),SpellSchool(SPL_SHOCK,2)));
		ReleaseMutex(mutx);
		if(randA(5)<2)
			skill_elec_passive(power_,&you);
		WaitForSingleObject(mutx, INFINITE);
		s_elec--;
		if(!s_elec)
		{
			printlog("방전이 멈췄다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_paralyse)
	{
		s_paralyse--;
		if(!s_paralyse)
		{
			printlog("다시 움직일 수 있게 되었다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_levitation)
	{
		s_levitation--;
		if(!s_levitation)
		{
			printlog("땅에 부드럽게 착지했다.",false,false,false,CL_blue);
			int temp = you.Ability(SKL_LEVITATION_OFF,false,true,1);
			if(temp)
				you.Ability(SKL_LEVITATION,false,false,temp);
			SetInter(IT_STAT);
		}
		if(s_levitation == 10)
		{
			printlog("몸이 무거워지고 있다.",false,false,false,CL_small_danger);
			SetInter(IT_STAT);
		}
	}
	if(s_glow)
	{
		s_glow--;
		if(!s_glow)
		{
			printlog("당신의 몸에서 빛나는 것이 멈췄다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_graze)
	{
		s_graze--;
		if(!s_graze)
		{
			printlog("더 이상 그레이즈를 하지 않는다.",false,false,false,CL_blue);
			int temp = you.Ability(SKL_GRAZE_OFF,false,true,1);
			if(temp)
				you.Ability(SKL_GRAZE,false,false,temp);
			SetInter(IT_STAT);
		}
		if(s_graze == 10)
		{
			printlog("그레이즈가 무뎌지고있다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_silence)
	{
		s_silence--;

		if((s_silence-5)/2 < s_silence_range)
		{
			env[current_level].MakeSilence(position, s_silence_range, false);
			s_silence_range = (s_silence-5)/2 >0 ? (s_silence-5)/2 : 0;
			env[current_level].MakeSilence(position, s_silence_range, true);
		}

		if(!s_silence)
		{
			printlog("소리를 지우는 정적이 사라졌다.",false,false,false,CL_blue);
			env[current_level].MakeSilence(position, s_silence_range, false);
			SetInter(IT_STAT);
		}
	}
	if(s_sick)
	{
		s_sick--;
		if(!s_sick)
		{
			printlog("병이 나았다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_veiling)
	{
		s_veiling--;
		if(!s_veiling)
		{
			printlog("휘감던 바람이 잠잠해졌다.",false,false,false,CL_blue);
			s_value_veiling = 0;
			SetInter(IT_STAT);
		}
	}
	if(s_invisible)
	{
		s_invisible--;
		if(!s_invisible)
		{
			printlog("몸이 다시 불투명해졌다.",false,false,false,CL_blue);
			int temp = you.Ability(SKL_INVISIBLE_OFF,false,true,1);
			if(temp)
				you.Ability(SKL_INVISIBLE,false,false,temp);
			SetInter(IT_STAT);
		}
		if(s_invisible == 10)
		{
			printlog("당신의 투명한 몸이 깜박이고있다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_superman)
	{
		s_superman--;
		s_swift = 0;
		if(!s_superman)
		{
			printlog("당신은 더이상 다리가 빠르지않다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
		if(s_superman == 5)
		{
			printlog("당신의 다리가 무거워지고있다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}

	if(s_eirin_poison_time)
	{
		s_eirin_poison_time--;
		if(s_eirin_poison_time == 11)
		{			
			printlog("치유로 인한 부작용이 시작되었다!",true,false,false,CL_danger);
			enterlog();
			SetInter(IT_STAT);
		}
		if(s_eirin_poison_time>0 && s_eirin_poison_time<=10)
		{
			int damage_ = min(s_eirin_poison,(s_eirin_poison/s_eirin_poison_time+1));
			HpUpDown(-damage_,DR_EFFECT);
			s_eirin_poison -= damage_;
			SetInter(IT_POISON);		
			if(s_eirin_poison<=0)
			{
				s_eirin_poison = 0;
				s_eirin_poison_time = 0;
			}
		}
		//s_eirin_poison;
	}
	
	if(s_exhausted)
	{
		s_exhausted--;
	}	
	if(s_stasis)
	{
		s_stasis--;
		if(!s_stasis)
		{
			printlog("전이 방해가 풀렸다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}



	if(s_slaying)
	{
		s_slaying = 0;
	}
	if(s_spellcard)
	{
		s_spellcard--;
		//if(!s_spellcard)
		//{
		//	printlog("스펠 브레이크!",true,false,false,CL_danger);
		//	if(equipment[ET_NECK])
		//	{
		//		passive_spellcard((spellcard_passive_type)equipment[ET_NECK]->value3, equipment[ET_NECK]->value4, -1, 0);
		//	}
		//	else
		//	{
		//		printlog("[BUG]스펠카드를 끼지않은 채로 스펠선언",true,false,false,CL_danger);
		//	}
		//	SetInter(IT_STAT);
		//}
		//if(s_spellcard == 5)
		//{
		//	printlog("스펠카드의 시간이 거의 다 끝나간다.",false,false,false,CL_small_danger);
		//	SetInter(IT_STAT);
		//}
	}

	if(s_swift)
	{
		s_swift--;
		if(!s_swift)
		{
			printlog("당신은 더이상 다리가 빠르지않다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
		if(s_swift == 10)
		{
			printlog("당신의 다리가 무거워지고있다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_mana_regen)
	{
		s_mana_regen--;
		if(!s_mana_regen)
		{
			printlog("영력회복속도가 정상이 되었다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_ghost>1)
	{
		s_ghost--;
		
		if(s_ghost == 1)
		{
			printlog("유령의 빈도가 정상이 되었다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_mirror)
	{
		s_mirror--;

		if(!s_mirror)
		{
			printlog("데미지 반사가 끝났다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}

	}
	if(s_dimension)
	{
		s_dimension--;
		
		if(s_dimension == 0)
		{			
			resetLOS(false);
			printlog("차원이 원래대로 돌아왔다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_timestep)
	{
		s_timestep--;

		if(s_timestep == 0)
		{
			printlog("당신은 동면을 끝냈다. 아직 잠에서 덜 깼다. ",false,false,false,CL_swako);
			you.SetSlow(rand_int(4,6));
			SetInter(IT_STAT);
		}
	}
	if(s_paradox)
	{
		s_paradox--;
		if(s_paradox == 0)
		{			
			printlog("도플갱어가 사라졌다.",false,false,false,CL_blue);
			SetInter(IT_STAT);
		}
	}
	if(s_the_world)
	{
		s_the_world--;

		if(s_the_world == 1)
		{
			printlog("그리고 시간은 움직이기 시작한다...",false,false,false,CL_small_danger);
			SetInter(IT_STAT);
		}

	}

	if(battle_count)
	{
		battle_count--;
		if(battle_count == 0)
		{
			ChangeBattleCount(false);
		}
	}

	if(!s_sick)
	{
		if(HpRecover(delay_) && inter == IT_NONE)
			SetInter(IT_HP_RECOVER);
	}
	if(MpRecover(delay_) && inter == IT_NONE)
		SetInter(IT_MP_RECOVER);
	

	PowDecrease(delay_);
	if(god != GT_NONE)
		god_turn++;
	ReleaseMutex(mutx);
	GodAccpect_turn(god_turn);
	
	if(mp == max_mp)
	{
		s_mana_delay = 0;
		MpRecoverDelay(0,true);
	}


	WaitForSingleObject(mutx, INFINITE);
	prev_position.set(position.x,position.y);
	TraningStealth();


	ReleaseMutex(mutx);
	//SetInter(HungerApply());
	WaitForSingleObject(mutx, INFINITE);
	tension_turn = false;
	if(wiz_list.wizard_mode == 1)
		CheckTension();
	enterlog();

	ReleaseMutex(mutx);
	if(s_paralyse)
	{
		you.time_delay += you.GetNormalDelay();
		SetInter(TurnEnd());
	}
	
	return inter;
}
bool players::TraningStealth()
{	
	int panlty = equipment[ET_ARMOR]?-equipment[ET_ARMOR]->value2:0;
	//bool bonus = (skill[SKT_BACKSTAB].level > skill[SKT_STEALTH].level);
	if(!randA((200+150*panlty)/*/(bonus?2:1)*/))
	{
		//SkillTraining(SKT_STEALTH,1);
		return true;
	}
	return false;
}


bool players::isEnemyMonster(const monster* monster_info)
{
	return !monster_info->isUserAlly();
}	
bool players::isSightnonblocked(coord_def c)
{
	bool intercept = false;
	for(int i=RT_BEGIN;i!=RT_END;i++)
	{
		int length_ = 8;
		beam_iterator it(position,c,(round_type)i);
		while(!intercept && !it.end())
		{
						
			coord_def check_pos_ = (*it);
						
			if(you.s_dimension)
			{
				if(abs(god_value[0] - check_pos_.x)>8)
					check_pos_.x += (god_value[0] - check_pos_.x)>0?17:-17;
				if(abs(god_value[1] - check_pos_.y)>8)
					check_pos_.y += (god_value[1] - check_pos_.y)>0?17:-17;
			}


			if(length_ == 0) //시야가 다 달았다.
			{
				intercept = true;
				break;
			}
			if(!env[current_level].isMove(check_pos_,true,true))
			{
				intercept = true;
				break;
			}
			it++;
			length_--;
		}
		if(intercept == false)
			break;
		else if(i == RT_END - 1)
		{
			return false; //공격불가능한 위치
		}
		else
			intercept = false;
	}
	return true;
}
bool players::isMemorizeSpell(int spell_)
{
	for(int i=0;i<52;i++)
	{
		if(MemorizeSpell[i] == spell_)
			return true;
	}
	return false;
}
bool players::CanMemorizeSpell(int spell_)
{

	if(spell_ <= SPL_NONE || spell_ > SPL_MAX)
		return false;
	int skill_level_ = SpellLevel((spell_list)spell_);
	
	//if(you.skill[SKT_SPELLCASTING].level == 0)
	//{
	//	return false;
	//}
	if(you.level<skill_level_)
	{
		return false;
	}
	if(you.remainSpellPoiont<skill_level_)
	{
		return false;
	}
	return true;
}
parent_type players::GetParentType()
{
	return PRT_PLAYER;
}
interupt_type players::SetInter(interupt_type inter_)
{
	if(inter < inter_)
		inter = inter_;
	return inter;
}



void deadlog()
{
	{
		char temp[200];	
		if(you.dead_order && you.dead_order->order)
			sprintf_s(temp,200,"%s에게 죽었다.",you.dead_order->order->GetName()->name.c_str());
		else if(you.dead_reason == DR_HUNGRY)
			sprintf_s(temp,200,"굶어죽었다.");
		else if(you.dead_reason == DR_QUIT)
			sprintf_s(temp,200,"게임을 포기했다.");
		else if(you.dead_reason == DR_ESCAPE)
			sprintf_s(temp,200,"던전을 탈출했다.");
		else if(you.dead_reason == DR_POISON)
			sprintf_s(temp,200,"독에 중독되어 죽었다.");
		else if(you.dead_reason == DR_EFFECT)
			sprintf_s(temp,200,"부작용에 의해 죽었다.");
		else
			sprintf_s(temp,200,"죽었다.");
		AddNote(you.turn,CurrentLevelString(),temp,CL_normal);
	}
}

void GameOver()
{			
	if(game_over)
		return;

	if(you.dead_reason != DR_ESCAPE)
		printlog("죽었다...",true,false,false,CL_normal);
	else
		printlog("던전을 탈출했다.",true,false,false,CL_normal);

	printlog("------------다음장------------",true,false,false,CL_normal);

	deadlog();
	string dump_;

	if(isNormalGame())
	{
		for(list<item>::iterator it = you.item_list.begin(); it != you.item_list.end();it++)
		{
			it->Identify();
		}
		WaitForSingleObject(mutx, INFINITE);
		Dump(1,&dump_);
		if(wiz_list.wizard_mode != 2 || you.dead_reason == DR_ESCAPE || you.dead_reason == DR_QUIT)
			delete_file();
		ReleaseMutex(mutx);




	}
	while(1)
	{
		int select = waitkeyinput();
		if(select==VK_RETURN)
		{
			break;
		}
	}
	if(isNormalGame())
	{
		iteminfor(true);
		waitkeyinput(true);
		changedisplay(DT_GAME);
		
		FILE *fp = fopen(dump_.c_str(),"rt");

		if(fp)
		{
			char temp[256];
			
			WaitForSingleObject(mutx, INFINITE);
			ReleaseMutex(mutx);
			deletesub();
			changedisplay(DT_SUB_TEXT);
			for(int i=0;i<26;i++)
			{
				fgets(temp,256,fp);
				//fscanf(fp,"%s",temp);				
				printsub(temp,true,CL_normal);
			}			
			printsub("",true,CL_magic);
			if(you.dead_reason == DR_ESCAPE && you.haveOrb())
			{
				if(wiz_list.wizard_mode == 1)
					printsub("플레이해주셔서 감사합니다! 다음엔 위자드모드없이 도전해봅시다!",true,CL_magic);
				else if(wiz_list.wizard_mode == 2)
					printsub("플레이해주셔서 감사합니다! 다음엔 세이브없이 도전해봅시다!",true,CL_magic);
				else
					printsub("클리어 축하드립니다! 그리고 플레이해주셔서 감사합니다!",true,CL_magic);
			}
			else
			{
				switch(randA(9))
				{
				default:
				case 0:
					printsub("죽음은 또 하나의 시작이다!",true,CL_magic);
					break;
				case 1:
					printsub("패배는 성공의 어머니다!",true,CL_magic);
					break;
				case 2:
					printsub("LOSING IS FUN!",true,CL_magic);
					break;
				case 3:
					printsub("포기하지마라!",true,CL_magic);
					break;
				case 4:
					printsub("지는것을 두려워하지마라!",true,CL_magic);
					break;
				case 5:
					printsub("죽음에도 배울 것이 있다!",true,CL_magic);
					break;
				case 6:
					printsub("실패는 성공의 과정일 뿐이다!",true,CL_magic);
					break;
				case 7:
					printsub("좌절감이 사나에를 키운다!",true,CL_magic);
					break;
				case 8:
					printsub("경험이 자산이다!",true,CL_magic);
					break;
				case 9:
					printsub("경험은 사라지지않는다!",true,CL_magic);
					break;
				}
			}
			printsub("",true,CL_help);
			printsub("기록은 게임의 morgue폴더에 저장되어있습니다.",true,CL_help);
			printsub("",true,CL_help);
			printsub("종료하시려면 Enter나 ESC를 누르세요.",true,CL_help);
			bool end_ = false;
			while(!end_)
			{
				int key_ = waitkeyinput(true);
				switch(key_)
				{
				default:
					break;
				case VK_RETURN:
				case VK_ESCAPE:
					end_ = true;
					break;
				}
			}
			fclose(fp);
		}




	}

	game_over = true;
}


bool poison_percent(int value)
{
	if(value<15)
		return randA(4)==1;
	else if(value<30)
		return randA(2)==1;
	else if(value<45)
		return randA(2)>0;
	else
		return 1;
}
int poison_damage(int value)
{
	if(value<50)
		return 1;
	else if(value<100)
		return randA(1)+1;
	else if(value<125)
		return randA(2)+1;
	else
		return randA(3)+1;
}