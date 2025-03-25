//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: tensi.cpp
//
// 내용: 텐시 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "tensi.h"
#include "environment.h"
#include "enum.h"
#include "mon_infor.h"
#include "skill_use.h"
#include "beam.h"
#include "god.h"
#include "note.h"
#include "potion.h"
#include "rect.h"
#include "alchemy.h"
#include "weapon.h"
#include "event.h"
#include "soundmanager.h"


string tensi_talk(bool good_, tensi_do_list list_);

int GetHazard()
{
	float total_danger_ = 0; //위험도

	int num_=0; //어느정도 위협이 되는 적의 수
	vector<monster>::iterator it;
	it = env[current_level].mon_vector.begin();
	for(int i=0;i<MON_MAX_IN_FLOOR && it != env[current_level].mon_vector.end() ;i++,it++)
	{
		if((*it).isLive() && env[current_level].isInSight(it->position)/* (*it).isYourShight()*/)
		{
			float danger_ = 0;
			if((*it).flag & M_FLAG_UNHARM)
			{ //무관한 적이다.

			}				
			else if((*it).isUserAlly())
			{ //아군이다. 

			}
			else
			{ //적이다.
				danger_ = 10;
				if((*it).level > you.level)
					danger_ = 800+((*it).level - you.level)*300; //자신보다 레벨이 높으면 위험도 800부터
				else if( you.level - (*it).level <= 6)
					danger_ = 500+70*((*it).level - you.level); //약간 약하다
				//나머지는 거의 의미없는 수준 위험도 1만 준다.

				int min_ = 0;
				if((*it).level>=10)//레벨이 10이상이면 다양한 특수능력때문에 만렙에게도 약간씩 위협을 준다.
					min_ = 100; //최소 위협치 100
				if((*it).level>=13)
					min_ = 200;
				if((*it).level>=15)
					min_ = 300;
				if((*it).level>=20)
					min_ = 500;

				
				
				danger_ = max(danger_,min_);

				if(!you.isSightnonblocked(it->position))
					danger_ = 1;
				//벽등에 막혀있다.
				
				int distant_ = pow((float)abs(it->position.x-you.position.x),2)+pow((float)abs(it->position.y-you.position.y),2);
				bool melee_ = true;//이 몹은 근접몹이다.
				bool smite_ = false;//이 몹은 적과 가로막혀있어도 위협적이다.

				if(!(*it).s_mute || env[current_level].isSilence(it->position))
				{
					for(auto it2 = it->spell_lists.begin();it2!= it->spell_lists.end(); it2++)
					{
						int length_ = SpellLength((spell_list)it2->num);
						if(!length_ || !(distant_ > length_*length_))
						{
							if(SpellFlagCheck((spell_list)it2->num,S_FLAG_RANGE_ATTACK))
							{
								melee_ = false; //원거리 몹이다.
							}		
							//if(SpellFlagCheck((spell_list)it2->num,S_FLAG_RANGE_ATTACK)|| SpellFlagCheck((spell_list)it2->num,S_FLAG_DEBUF))
							//{
							//	//거리가 멀어져있어도 당신에게 위협이 될 가능성이 있음
							//}
							//디버프는 직접적으로 위협이 되지 않는다.
							if(SpellFlagCheck((spell_list)it2->num,S_FLAG_SUMMON) || SpellFlagCheck((spell_list)it2->num,S_FLAG_SMITE))
							{
								//소환과 스마이트
								melee_ = false; //원거리 몹이다.
								smite_ = true;
								break;
							}
						}

					}
				}
				else if(!it->spell_lists.empty())
					danger_ *= 0.5f;
					

				if(melee_)
				{ //밀리몹은 거리에 따라서 보정 
					float mul_ = 1.2f-0.075f*max(abs(you.position.x-it->position.x),abs(you.position.y-it->position.y));
					//가장 멀리 있을때 0.6f 밀착시 1.2임
					danger_*=mul_;
				}
				
				if(!smite_)
				{
					beam_iterator beam(it->position,you.position);
				
					for(beam.init();!beam.end();beam++)
					{
						unit *temp = env[current_level].isMonsterPos((*beam).x,(*beam).y);
						if(temp)
						{			
							if(temp->isLive() && !temp->isEnemyMonster(&(*it)) && !temp->isPassedBullet(&(*it)))
							{
								danger_*=0.5f;
								break;
								//가리고있으면 위험도는 많이 줄어든다.
							}
						}
					}
				}
				else
					danger_*=1.5f; //스마이트몹은 대체로 위험도가 높다.

				if((*it).s_confuse || (*it).s_paralyse || (*it).s_fear) //혼란 마비 공포는 거의 위험도를 높이지않음.
					danger_ *= 0.05f;
				if((*it).s_slow)
					danger_ *= 0.5f;
				if((*it).s_haste)
					danger_ *= 1.5f;
				if((*it).s_invisible && !you.s_invisible)
					danger_ *= 1.5f;
				if((*it).s_might)
					danger_ *= 1.5f;
				if((*it).state.GetState() != MS_ATACK)
					danger_ *= 0.2f; //공격이 아니다.

				danger_ *=  0.5f+0.5f*((float)(*it).hp)/(*it).max_hp;

				
				if((*it).flag & M_FLAG_UNIQUE)
					danger_*=2.0f; //네임드는 위험함

				num_++;
			}

			total_danger_ += danger_;
		}
	}

	if(you.s_paralyse)
		total_danger_ *= 5;
	
	if(you.s_confuse || you.s_lunatic)
		total_danger_ *= 3;

	if (you.s_sleep < 0)
		total_danger_ *= 3;

	if(you.s_slow)
		total_danger_ *= 2;
	
	if(you.s_haste || you.s_pure_haste)
		total_danger_ *= 0.7f;
	if(you.s_might || you.s_clever || you.s_dex)
		total_danger_ *= 0.7f;

	if(((float)you.GetHp())/you.GetMaxHp() <= 0.5f) //체력이 절반이하
		total_danger_ *=  3.0f-2.0f*((float)you.GetHp())/you.GetMaxHp();
	
	if (!you.pure_mp)
	{
		if (you.GetMaxMp() >= 5 && ((float)you.GetMp()) / you.GetMaxMp() <= 0.5f) //마나가 절반이하
			total_danger_ *= 3.0f - 2.0f*((float)you.GetMp()) / you.GetMaxMp();
	}

	if(you.s_the_world)
		total_danger_ *= 0.1f;

	return (int)total_danger_;
}


void tensi_potion(bool good_)
{
	potion_type good_list_[6] = {PT_MIGHT,PT_HASTE,PT_HEAL_WOUND, PT_CLEVER,PT_AGILITY,PT_RECOVER_STAT};
	potion_type bad_list_[5] = {PT_POISON, PT_CONFUSE, PT_SLOW, PT_DOWN_STAT,PT_ALCOHOL};

	potion_type you_drink_ = PT_WATER;
	
	if(good_)
		you_drink_ = good_list_[randA(5)];
	else		
		you_drink_ = bad_list_[randA(4)];


	soundmanager.playSound("potion");
	drinkpotion(you_drink_, false);
}






void tensi_weather(int type_, int good_)
{
	soundmanager.playSound("spellcard");
	switch (type_)
	{
	case 1:
		printlog("한치 앞이 안보이는 짙은 안개가 깔리기 시작했다.", true, false, false, CL_normal);
		you.SetWeather(1, 100);
		break;
	case 2:
		printlog("던전에 많은 비와 천둥번개가 휘몰아치기 시작한다.", true, false, false, CL_normal);
		you.SetWeather(2, 100);
		break;
	case 3:
		printlog("던전에 강한 햇빛이 들기 시작했다.", true, false, false, CL_normal);
		you.SetWeather(3, 100);
		break;
	default:
		break;
	}
}

void tensi_summon(int good_)
{

	vector<int> summon_vector;


	if(you.level<=5)
	{
		summon_vector.push_back(MON_MOOK);
		summon_vector.push_back(MON_CROW);
		summon_vector.push_back(MON_SNAKE);
		summon_vector.push_back(MON_SPIDER);
		summon_vector.push_back(MON_FIREFLY);
	}
	else if(you.level<=10)
	{
		summon_vector.push_back(MON_SNAKE);
		summon_vector.push_back(MON_CRANE);
		summon_vector.push_back(MON_BAKEKASA);
		summon_vector.push_back(MON_FROG);
	}
	else if(you.level<=14)
	{
		summon_vector.push_back(MON_FROG);
		summon_vector.push_back(MON_BLACK_CAT);
		summon_vector.push_back(MON_EAGLE);
		summon_vector.push_back(MON_YAMABIKO);
	}
	else if(you.level<=16)
	{
		summon_vector.push_back(MON_TIGER);
		summon_vector.push_back(MON_RAIJUU);
		summon_vector.push_back(MON_EAGLE);
		summon_vector.push_back(MON_AYAYUKKURI);
	}
	else if(you.level<=20)
	{
		summon_vector.push_back(MON_AYAYUKKURI);
		summon_vector.push_back(MON_REMILIAYUKKURI);
		summon_vector.push_back(MON_RED_UFO);
		summon_vector.push_back(MON_GREEN_UFO);
		summon_vector.push_back(MON_ONI);
	}
	else if(you.level<=24)
	{
		summon_vector.push_back(MON_DRAGON_BABY);
		summon_vector.push_back(MON_YOUMUYUKKURI);
		summon_vector.push_back(MON_NAMAZ);
		summon_vector.push_back(MON_FLOWER_TANK);
		summon_vector.push_back(MON_ONI);
	}
	else
	{
		summon_vector.push_back(MON_DRAGON_BABY);
		summon_vector.push_back(MON_YOUMUYUKKURI);
		summon_vector.push_back(MON_NAMAZ);
		summon_vector.push_back(MON_FLOWER_TANK);
		summon_vector.push_back(MON_ONI);
	}


	if(!summon_vector.empty())
	{
		soundmanager.playSound("summon");
		dif_rect_iterator rit(you.position,2);
		int i = randC(abs(good_),3); 
		for(;!rit.end() && i> 0;rit++)
		{
			if(summon_check(coord_def(rit->x,rit->y), you.position, false, false))
			{
				int flag_=M_FLAG_SUMMON;
				if(good_>0)
					flag_ |= M_FLAG_ALLY;
				int id_ = summon_vector[randA(summon_vector.size()-1)] ;

				summon_info s_(you.GetMapId(),SKD_OTHER,GetSummonMaxNumber(SPL_NONE));
				if (monster* mon_ = env[current_level].AddMonster_Summon(id_, flag_, (*rit), s_, rand_int(100, 200)))
				{

					mon_->CheckSightNewTarget();

				}
				i--;
			}
		}
	}
}

void tensi_kaname(int good_)
{
	soundmanager.playSound("summon");
	for (int i = rand_int(1 + 2 * abs(good_), 1 + 3 * abs(good_));  i> 0; i--)
	{
		int flag_ = M_FLAG_SUMMON;
		if (good_>0)
			flag_ |= M_FLAG_ALLY;
		int id_ = MON_KANAME;

		if (monster* mon_ = BaseSummon(MON_KANAME, rand_int(60, 100), false, true, 4, good_>0?&you:NULL, you.position, SKD_OTHER, -1))
		{
			int fanalty_ = randA(randA(you.level));
			mon_->LevelUpdown(you.level - fanalty_);
			if (mon_->level<7)
				mon_->spell_lists.push_back(spell(SPL_MON_TANMAC_SMALL, 50));
			else if (mon_->level<15)
				mon_->spell_lists.push_back(spell(SPL_MON_TANMAC_MIDDLE, 25));
			else
				mon_->spell_lists.push_back(spell(SPL_MON_TANMAC_MIDDLE, 50));
			mon_->CheckSightNewTarget();
		}
	}

}

void tensi_tele(bool good_)
{
	int max_monster_ = good_?99:0;
	coord_def final(0,0);
	for(int i = 0; i < 20; i++)
	{
		int monster_ = 0;
		coord_def c_;
		while(1)
		{
			int x_ = randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			if(env[current_level].isMove(x_,y_) && !env[current_level].isMonsterPos(x_,y_))
			{
				c_ = coord_def(x_,y_);
				break;
			}
		}
		

		vector<monster>::iterator it;
		it = env[current_level].mon_vector.begin();
		for(int j=0;j<MON_MAX_IN_FLOOR && it != env[current_level].mon_vector.end() ;j++,it++)
		{
			if((*it).isLive() && !(*it).isUserAlly() && (*it).isMonsterSight(c_) )
			{					
				monster_++;
			}
		}
		if(good_ && monster_<max_monster_)
		{
			max_monster_=monster_;
			final = c_;
			if(monster_ == 0)
				break;
		}
		else if(!good_ && monster_>max_monster_)
		{			
			max_monster_=monster_;
			final = c_;
		}
	}
	if(env[current_level].isMove(final.x,final.y) && !env[current_level].isMonsterPos(final.x,final.y))
	{
		soundmanager.playSound("blink");
		env[current_level].MakeSmoke(you.position, img_fog_normal, SMT_NORMAL, 4, 0, &you);
		you.SetXY(final);
	}
	else
	{
		if(wiz_list.wizard_mode == 1)
			printlog("텐시 텔레포트 실패",true,false,false,CL_tensi);
		you.Teleport();
	}
}


void tensi_earthquake(int good_)
{
	for(int i=-8;i<=8;i++)
	{
		for(int j=-8;j<=8;j++)
		{
			coord_def pos = coord_def(i,j)+you.position;
			if(env[current_level].isInSight(pos) && env[current_level].dgtile[pos.x][pos.y].isBreakable())
			{
				if(randA(1)==0)
					env[current_level].changeTile(pos, env[current_level].base_floor);
			}
		}
	}//맵을 파괴한다.

	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if(it->isLive() && env[current_level].isInSight(it->position))
		{
			int att_ = randC(6,10+you.level/3);
			int m_att_ = 6*(10+you.level/3);
			if(it->isFly())
			{
				att_/=2;
				m_att_/=2;
			}
			attack_infor temp_att(att_,m_att_,99,&you,you.GetParentType(),ATT_NORMAL_BLAST,name_infor(LOC_SYSTEM_ATT_EARTHQUAKE));
			it->damage(temp_att, true);
		}
	}//모든 몬스터에게 데미지를 줌

	soundmanager.playSound("earthquake"); 
	env[current_level].MakeNoise(you.position,30,NULL); //거대한 소음을 만든다. 텐시는 아무도 없을때 지진을 쓰기도 하지!
	you.resetLOS();
}
void tensi_munyum(int good_)
{
	soundmanager.playSound("buff");
	you.SetAlchemyBuff(ALCT_STONE_FORM,rand_int(100,200));
	//텐시의 무념무상 버프는 길다!
}
void tensi_burst(int good_)
{
	int num_ = 0;
	for(auto it = env[current_level].mon_vector.begin();; it++)
	{
		coord_def pos_;
		bool is_live = true;
		bool is_ally = true;

		if( it == env[current_level].mon_vector.end())
		{
			if(num_ && good_>0)
			{
				Sleep(300);
				env[current_level].ClearEffect();
				break;
			}
			else
			{
				pos_ = you.position; //안좋은 폭발일경우 플레이어까지 휩쓸릴 수 있다.

			}

		}
		else
		{
			pos_ = it->position;			
			is_live = it->isLive();
			is_ally = it->isUserAlly();
		}



		if(is_live && env[current_level].isInSight(pos_))
		{
			if(good_<0 || (!is_ally))
			{
				vector<coord_def> vt_;
				{
					rect_iterator rit(pos_,1,1);
					for(;!rit.end();rit++)
					{
						if(env[current_level].isMove(rit->x,rit->y) && (good_<0 || *rit != you.position))
						{
							env[current_level].MakeEffect(*rit,&img_blast[randA(5)],false);
							vt_.push_back(*rit);
						}
					}
				}
				for(auto it2 = vt_.begin();it2 != vt_.end();it2++)
				{
					if (env[current_level].isMove(it2->x, it2->y))
					{
						if ((good_ < 0 || *it2 != you.position)) {
							if (unit* hit_ = env[current_level].isMonsterPos(it2->x, it2->y))
							{

								int att_ = randC(3, 8 + you.level / 3);
								int m_att_ = 3 * (8 + you.level / 3);

								if (hit_->isplayer())
								{ //플레이어는 죽지 않을정도만
									if (att_ >= hit_->GetHp())
										att_ = hit_->GetHp() - 1;
								}
								attack_infor temp_att(att_, m_att_, 99, &you, you.GetParentType(), ATT_NORMAL_BLAST, name_infor(LOC_SYSTEM_GOD_TENSI));
								hit_->damage(temp_att, true);
								soundmanager.playSound("bomb");
							}
						}
					}
				}
				Sleep(100);
				num_++;
			}
		}
		if( it == env[current_level].mon_vector.end())
		{
			Sleep(300);
			env[current_level].ClearEffect();
			break;
		}
	}//모든 몬스터에게 데미지를 줌
	
	
	env[current_level].MakeNoise(you.position,16,NULL); //상당한 소음을 만든다.

}


void tensi_weapon(int doing_)
{
	if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && !you.equipment[ET_WEAPON]->value5)
	{
		LocalzationManager::printLogWithKey(LOC_SYSTEM_TENSI_BRAND_WEAPON,true,false,false,CL_tensi,
			PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
		you.equipment[ET_WEAPON]->value5 = WB_WEATHER;
		you.equipment[ET_WEAPON]->value6 = (70+randA(50))*(doing_>0?doing_*2:1);
	}
	else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_WEATHER && you.equipment[ET_WEAPON]->value6>0)
	{
		LocalzationManager::printLogWithKey(LOC_SYSTEM_TENSI_MORE_BRAND_WEAPON,true,false,false,CL_tensi,
			PlaceHolderHelper(you.equipment[ET_WEAPON]->GetName()));
		you.equipment[ET_WEAPON]->value6 += (90+randA(50))*(doing_>0?doing_:1);
	}
	else
	{
		printlog("그러나 아무일도 일어나지 않았다.",true,false,false,CL_normal);
	}
}

void tensi_field(int doing_)
{
	random_extraction<int> rand_;

	if (doing_>0)
	{
		rand_.push(EVL_SANTUARY);
	}
	else 
	{
		rand_.push(EVL_VIOLET);
		rand_.push(EVL_SILENCE);
	}
	env[current_level].MakeEvent(rand_.pop(), you.position, EVT_ALWAYS, rand_int(10, 20));
}
void tensi_blind(int doing_)
{
	soundmanager.playSound("laugh");
	you.SetNightSight(1, rand_int(20,40), true);
}
void tensi_buf_debuf(int doing_)
{
	int time_ = rand_int(20, 30)* abs(doing_);

	int i = 0;
	for (auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
	{
		if (it->isLive() && env[current_level].isInSight(it->position, true))
		{
			if(doing_>0)
				it->SetSlow(time_);
			else
				it->SetHaste(time_);
			i++;
			if (i % 4 == 0)
				enterlog();
		}
	}
}
void tensi_sucide(int doing_)
{
	soundmanager.playSound("summon");
	for (int i = randA_1(you.level/6+1); i> 0; i--)
	{
		int id_ = MON_RABIT_BOMB;
		if (monster* mon_ = BaseSummon(MON_RABIT_BOMB, rand_int(20, 30), false, true, 2, &you, you.position, SKD_OTHER, -1))
		{
			mon_->CheckSightNewTarget();
		}
	}
}
void tensi_action()
{
	string type;
	if(wiz_list.wizard_mode == 1)
	{
		char temp[256];

		sprintf_s(temp,256,"[턴:%d 텐션:%d]",you.turn, you.CheckTension());
	
		printlog(temp,false,false,false,CL_tensi);
		
	}

	int doing_ = 0;
	tensi_do_list action_ = TENSI_NOTHING;

	if(you.CheckTension()+10 < randA(100) || you.GetPunish(GT_TENSI))
	{

		int rand_ = randA(99);

		if(rand_>44+(you.GetPunish(GT_TENSI)?50:0))
		{
			type = "[평화:0]";
			action_ = TENSI_NOTHING;
		}
		else
		{
			type = "[평화:-1]";
			switch(randA(7)){
			case 0:doing_ = -1; action_ =  TENSI_POTION; break;
			case 1:doing_ = rand_int(-1,-2); action_ =  TENSI_SUMMON; break;
			case 2:doing_ = -1; action_ =  TENSI_TELE; break;
			case 3:doing_ = -1; action_ =  TENSI_EARTHQUAKE; break;
			case 4:doing_ = -1; action_ =  TENSI_BURST; break;
			case 5:doing_ = -1; action_ = TENSI_KANAME; break;
			case 6:doing_ = -1; action_ = TENSI_BLIND; break;
			case 7:doing_ = -1; action_ = TENSI_WEATHER_THUNDER; break;
			}
		}
	}
	else
	{
		if(100+randA(4000)<randA(you.CheckTension()) && randA(9)>0)
		{ //텐시의 포텐셜 폭발!	
			type = "[위기:3]";
			switch(randA(8)){
			case 0:doing_ = 1; action_ =  TENSI_EARTHQUAKE; break;
			case 1:doing_ = 2; action_ =  TENSI_SUMMON; break;
			case 2:doing_ = 1; action_ =  TENSI_MUNYUM; break;
			case 3:doing_ = 1; action_ =  TENSI_TELE; break; //텐시는 전투를 좋아하기때문에 텔포는 많이 안쓴다.
			case 4:doing_ = 2; action_ = TENSI_KANAME; break;
			case 5:doing_ = 1; action_ = TENSI_FIELD; break;
			case 6:doing_ = 2; action_ = TENSI_BUFF_DEBUFF; break;
			case 7:doing_ = 2; action_ = TENSI_WEATHER_THUNDER; break;
			case 8:doing_ = 2; action_ = TENSI_WEATHER_FOG; break;
			}
		}
		else if(randA(500)<randA(you.CheckTension()) && randA(5)>0)
		{ //그럭저럭 좋은일
			type = "[위기:2]";
			switch(randA(7)){
			case 0:doing_ = 1; action_ =  TENSI_POTION; break;
			case 1:doing_ = 1; action_ =  TENSI_SUMMON; break;
			case 2:doing_ = 1; action_ =  TENSI_BURST; break;
			case 3:doing_ = 2; action_ =  TENSI_WEAPON; break;
			case 4:doing_ = 1; action_ = TENSI_KANAME; break;
			case 5:doing_ = 1; action_ = TENSI_BUFF_DEBUFF; break;
			case 6:doing_ = 1; action_ = TENSI_WEATHER_THUNDER; break;
			case 7:doing_ = 1; action_ = TENSI_WEATHER_FOG; break;
			}
		}
		else if(randA(100)<randA(you.CheckTension()) && randA(5)>0)
		{ //괜찮네
			type = "[위기:1]";
			switch(randA(3)){
			case 0:doing_ = 1; action_ =  TENSI_POTION; break;
			case 1:doing_ = 1; action_ =  TENSI_BURST; break;
			case 2:doing_ = 1; action_ =  TENSI_WEAPON; break;
			case 3:doing_ = 1; action_ = TENSI_WEATHER_SUN; break;
			}
		}
		else
		{ //운이 나빴어
			type = "[위기:-1]";
			switch(randA(10)){
			case 0:doing_ = -1; action_ =  TENSI_POTION; break;
			case 1:doing_ = -1; action_ =  TENSI_SUMMON; break;
			case 2:doing_ = -1; action_ =  TENSI_TELE; break;
			case 3:doing_ = -1; action_ =  TENSI_BURST; break;
			case 4:doing_ = rand_int(-2,-1); action_ = TENSI_KANAME; break;
			case 5:doing_ = -1; action_ = TENSI_FIELD; break;
			case 6:doing_ = -1; action_ = TENSI_BLIND; break;
			case 7:doing_ = -1; action_ = TENSI_BUFF_DEBUFF; break;
			case 8:doing_ = -1; action_ = TENSI_SUCIDE; break;
			case 9:doing_ = -1; action_ = TENSI_WEATHER_THUNDER; break;
			case 10:doing_ = -1; action_ = TENSI_WEATHER_SUN; break;
			}
		}

	}
	
	if (wiz_list.wizard_mode == 1) {
		printlog(type, false, false, false, CL_tensi);
	}
		

	printlog(tensi_talk(doing_>0, action_),true,false,false,CL_tensi);
	char temp[256];
	switch(action_)
	{
	case TENSI_NOTHING:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp,256,"%s텐시: 아무일도안함. 텐션 %d", type.c_str(), you.CheckTension());
		}
		else {
			sprintf_s(temp, 256, "텐시: 아무일도안함");
		}
		AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		break;
	case TENSI_POTION:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp,256,"%s텐시: 포션. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: %s 포션", (doing_>0) ? "좋은" : "나쁜");
		}
		AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		tensi_potion(doing_>0);
		break;
	case TENSI_SUMMON:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp,256,"%s텐시: 소환. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: %s 소환", (doing_>0)?"우호적":"적대적");
		}
		AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		tensi_summon(doing_);
		break;
	case TENSI_TELE:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp,256,"%s텐시: 텔레포트. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: %s 텔레포트", (doing_>0) ? "안전한" : "위험한");
		}
		AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		tensi_tele(doing_);
		break;
	case TENSI_EARTHQUAKE:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp,256,"%s텐시: 지진. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 지진");
		}
		AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		tensi_earthquake(doing_);
		break;
	case TENSI_MUNYUM:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp,256,"%s텐시: 무념무상. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 무념무상 버프");
		}
		AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		tensi_munyum(doing_);
		break;
	case TENSI_BURST:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp,256,"%s텐시: 폭발. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: %s 폭발", (doing_>0) ? "안전한" : "위험한");
		}
		AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		tensi_burst(doing_);
		break;
	case TENSI_WEAPON:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp,256,"%s텐시: 비상의검. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 비상의검 부여");
		}
		AddNote(you.turn,CurrentLevelString(),temp,CL_tensi);
		tensi_weapon(doing_);
		break;
	case TENSI_KANAME:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp, 256, "%s텐시: 카나메석. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: %s 카나메석 소환", (doing_>0) ? "우호적" : "적대적 ");
		}
		AddNote(you.turn, CurrentLevelString(), temp, CL_tensi);
		tensi_kaname(doing_);
		break;
	case TENSI_FIELD:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp, 256, "%s텐시: 필드생성. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 특수 필드 생성");
		}
		AddNote(you.turn, CurrentLevelString(), temp, CL_tensi);
		tensi_field(doing_);
		break;
	case TENSI_BLIND:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp, 256, "%s텐시: 실명. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 실명");
		}
		AddNote(you.turn, CurrentLevelString(), temp, CL_tensi);
		tensi_blind(doing_);
		break;
	case TENSI_BUFF_DEBUFF:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp, 256, "%s텐시: 광역가속감속. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 광역 %s", (doing_>0) ? "감속" : "가속");
		}
		AddNote(you.turn, CurrentLevelString(), temp, CL_tensi);
		tensi_buf_debuf(doing_);
		break;
	case TENSI_SUCIDE:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp, 256, "%s텐시: 자폭토끼. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 자폭토끼 소환");
		}
		AddNote(you.turn, CurrentLevelString(), temp, CL_tensi);
		tensi_sucide(doing_);
		break;
	case TENSI_WEATHER_FOG:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp, 256, "%s텐시: 안개. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 안개");
		}
		AddNote(you.turn, CurrentLevelString(), temp, CL_tensi);
		tensi_weather(1, doing_);
		break;
	case TENSI_WEATHER_THUNDER:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp, 256, "%s텐시: 번개. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 천둥번개");
		}
		AddNote(you.turn, CurrentLevelString(), temp, CL_tensi);
		tensi_weather(2, doing_);
		break;
	case TENSI_WEATHER_SUN:
		if (wiz_list.wizard_mode == 1)
		{
			sprintf_s(temp, 256, "%s텐시: 쾌청. 텐션 %d 행동 %d", type.c_str(), you.CheckTension(), doing_);
		}
		else {
			sprintf_s(temp, 256, "텐시: 쾌청");
		}
		AddNote(you.turn, CurrentLevelString(), temp, CL_tensi);
		tensi_weather(3, doing_);
		break;
	}
}



attack_type GetWeatherType(unit* unit_, int damage_, int &bonus_damage_)
{
	int type_ = randA_1((int)WTL_MAX);
	if(randA(2)==0)
		type_ = WTL_NONE;
	switch(type_)
	{
	case WTL_FIRE:
		bonus_damage_ +=  unit_->GetFireResist()*(damage_/3);
		type_ = ATT_FIRE;
		break;
	case WTL_COLD:
		bonus_damage_ += unit_->GetColdResist()*damage_/3;
		type_ = ATT_COLD;
		break;
	case WTL_EARTH:
		bonus_damage_ += 9;
		type_ = ATT_NORMAL;
		break;
	case WTL_AIR:
		bonus_damage_ += unit_->GetElecResist()*damage_/3;
		type_ = ATT_ELEC;
		break;
	case WTL_POISON:
		type_ = ATT_S_POISON;
		break;
	case WTL_CHOAS:
		type_ = ATT_CHOAS;
		break;
	default:
		type_ = ATT_NORMAL;
		break;
	}
	return (attack_type)type_;
}


int GetChoas(unit* unit_, int damage_)
{	
	switch(randA(5))
	{
	case 0://WTL_CONFUSE,
		unit_->SetConfuse(5+randA(10));
		break;
	case 1://WTL_MUTE,
		unit_->SetMute(5+randA(10));
		break;
	case 2://WTL_GLOW,
		unit_->SetGlow(5+randA(10));
		break;
	case 3://WTL_TELE,
		unit_->SetTele(rand_int(3,6));
		break;
	case 4://WTL_SICK,
		unit_->SetSick(20+randA(30));
		break;
	case 5://WTL_PARA,
		unit_->SetParalyse(2+randA(5));
		break;
	}
	return 0;
}

string tensi_talk(bool good_, tensi_do_list list_)
{
	static char temp[256];
	if(list_ != TENSI_NOTHING && randA(2))
	{//공용대사
		if(good_)
		{
			switch(randA(12))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD6);
			case 6:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD7);
			case 7:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD8);
			case 8:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD9);
			case 9:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD10);
			case 10:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD11);
			case 11:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD12);
			case 12:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_GOOD13);
			}
		}
		else
		{
			switch(randA(14))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD6);
			case 6:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD7);
			case 7:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD8);
			case 8:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD9);
			case 9:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD10);
			case 10:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD11);
			case 11:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD12);
			case 12:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD13);
			case 13:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD14);
			case 14:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD15);
			}
		}

	}
	else 
	{
		switch(list_)
		{
		case TENSI_NOTHING:
			switch(randA(20))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING6);
			case 6:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING7);
			case 7:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING8);
			case 8:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING9);
			case 9:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING10);
			case 10:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING11);
			case 11:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING12);
			case 12:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING13);
			case 13:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING14);
			case 14:
				return LocalzationManager::formatString(LOC_SYSTEM_TENSI_NOTHING15, PlaceHolderHelper(mondata[randA_nonlogic(MON_MAX-1)].name.getName()));
			case 15:
				return LocalzationManager::formatString(LOC_SYSTEM_TENSI_NOTHING16, PlaceHolderHelper(mondata[randA_nonlogic(MON_MAX-1)].name.getName()));
			case 16:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING17);
			case 17:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING18);
			case 18:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING19);
			case 19:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING20);
			case 20:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_NOTHING11);
			}	
		case TENSI_POTION:
			if(good_)
			{
				switch(randA(4))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_POTION1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_POTION2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_POTION3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_POTION4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_POTION5);
				}
			}
			else
			{
				switch(randA(4))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_POTION1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_POTION2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_POTION3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_POTION4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_POTION5);
				}
			}
		case TENSI_SUMMON:
			if(good_)
			{
				switch(randA(4))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUMMON1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUMMON2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUMMON3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUMMON4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUMMON5);
				}
			}
			else
			{
				switch(randA(4))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_SUMMON1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_SUMMON2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_SUMMON3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_SUMMON4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_SUMMON5);
				}
			}	
		case TENSI_TELE:
			if(good_)
			{
				switch(randA(4))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_TELE1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_TELE2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_TELE3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_TELE4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_TELE5);
				}
			}
			else
			{
				switch(randA(4))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_TELE1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_TELE2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_TELE3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_TELE4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_TELE5);
				}
			}	
		case TENSI_EARTHQUAKE:
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_EARHQUAKE1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_EARHQUAKE2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_EARHQUAKE3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_EARHQUAKE4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_EARHQUAKE5);
			}
		case TENSI_MUNYUM:
			switch(randA(4))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUPERARMOR1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUPERARMOR2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUPERARMOR3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUPERARMOR4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUPERARMOR5);
			}
		case TENSI_BURST:
			switch(randA(2))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BURST1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BURST2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BURST3);
			}
		case TENSI_WEAPON:
			switch(randA(6))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_WEAPON1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_WEAPON2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_WEAPON3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_WEAPON4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_WEAPON5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_WEAPON6);
			case 6:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_WEAPON7);
			}
		case TENSI_KANAME:
			if (good_)
			{
				switch (randA(5))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_KANAME1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_KANAME2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_KANAME3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_KANAME4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_KANAME5);
				case 5:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_KANAME6);
				}
			}
			else {
				switch (randA(5))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_KANAME1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_KANAME2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_KANAME3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_KANAME4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_KANAME5);
				case 5:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_BAD_KANAME6);
				}
			}
		case TENSI_FIELD:
			switch (randA(4))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FIELD1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FIELD2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FIELD3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FIELD4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FIELD5);
			}
		case TENSI_BLIND:
			switch (randA(3))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BLIND1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BLIND2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BLIND3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_BLIND4);
			}
		case TENSI_BUFF_DEBUFF:
			if (good_)
			{
				switch (randA(5))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF5);
				case 5:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF6);
				}
			}
			else {
				switch (randA(5))
				{
				case 0:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF1);
				case 1:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF2);
				case 2:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF3);
				case 3:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF4);
				case 4:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF5);
				case 5:
					return LocalzationManager::locString(LOC_SYSTEM_TENSI_DEBUFF6);
				}
			}
		case TENSI_SUCIDE:
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUCIDE1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUCIDE2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUCIDE3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUCIDE4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUCIDE5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUCIDE6);
			case 6:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUCIDE7);
			}
		case TENSI_WEATHER_FOG:
			switch (randA(5))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FOG1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FOG2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FOG3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FOG4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FOG5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_FOG6);
			}
		case TENSI_WEATHER_THUNDER:
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_THUNDER1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_THUNDER2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_THUNDER3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_THUNDER4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_THUNDER5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_THUNDER6);
			case 6:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_THUNDER7);
			}
		case TENSI_WEATHER_SUN:
			switch (randA(6))
			{
			case 0:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUN1);
			case 1:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUN2);
			case 2:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUN3);
			case 3:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUN4);
			case 4:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUN5);
			case 5:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUN6);
			case 6:
				return LocalzationManager::locString(LOC_SYSTEM_TENSI_SUN7);
			}	
		}

	}
	return "텐시는 안들리는 목소리로 소근거렸다.";

}