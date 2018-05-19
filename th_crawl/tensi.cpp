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


const char* tensi_talk(bool good_, tensi_do_list list_);

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
			attack_infor temp_att(att_,m_att_,99,&you,you.GetParentType(),ATT_NORMAL_BLAST,name_infor("지진",true));
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
								attack_infor temp_att(att_, m_att_, 99, &you, you.GetParentType(), ATT_NORMAL_BLAST, name_infor("텐시", false));
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
		printarray(true,false,false,CL_tensi,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"비상의 기운이 뿜어져나온다.");
		you.equipment[ET_WEAPON]->value5 = WB_WEATHER;
		you.equipment[ET_WEAPON]->value6 = (70+randA(50))*(doing_>0?doing_*2:1);
	}
	else if(you.equipment[ET_WEAPON] && !you.equipment[ET_WEAPON]->isArtifact() && you.equipment[ET_WEAPON]->value5 == WB_WEATHER && you.equipment[ET_WEAPON]->value6>0)
	{
		printarray(true,false,false,CL_tensi,3,you.equipment[ET_WEAPON]->GetName().c_str(),you.equipment[ET_WEAPON]->GetNameInfor().name_is(true),"더욱 비상의 힘이 길어졌다.");
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

const char* tensi_talk(bool good_, tensi_do_list list_)
{
	static char temp[256];
	if(list_ != TENSI_NOTHING && randA(2))
	{//공용대사
		if(good_)
		{
			switch(randA(12))
			{
			case 0:
				return "텐시가 당신에게 호의적인 시선을 주었다.";
			case 1:
				return "텐시의 힘이 당신에게 닿았다.";
			case 2:
				return "텐시: 힘들어보이네!";
			case 3:
				return "텐시: 도와줄게!";
			case 4:
				return "당신은 텐시의 웃음 소리를 들었다.";
			case 5:
				return "텐시가 흥미진진한 시선을 향했다.";
			case 6:
				return "텐시의 박수소리를 들었다.";
			case 7:
				return "당신 주변에 기분 좋은 기운이 감도는것을 느꼈다.";
			case 8:
				return "텐시: 좀 더 즐겁게 해줘!";
			case 9:
				return "텐시: 아직 더 할 수 있지?";
			case 10:
				return "텐시: 힘내!";
			case 11:
				return "텐시의 강력한 힘을 받았다.";
			case 12:
				return "텐시는 흥미진진하게 당신의 모험을 바라보고있다.";
			}
		}
		else
		{
			switch(randA(14))
			{
			case 0:
				return "텐시의 사악한 시선이 느껴진다.";
			case 1:
				return "텐시가 웃기 시작했다.";
			case 2:
				return "텐시가 당신의 모험을 지루하다고 생각했다.";
			case 3:
				return "텐시: 이런건 어떨까?";
			case 4:
				return "텐시: 좀 더 스릴있게 해줄게!";
			case 5:
				return "텐시: 너무 평화롭지 않아?";
			case 6:
				return "텐시의 장난기어린 웃음을 들었다.";
			case 7:
				return "텐시가 당신에게 시련을 주려하고 있다.";
			case 8:
				return "텐시: 지루한 것보단 낫지?";
			case 9:
				return "텐시: 더 화를 내줘!";
			case 10:
				return "텐시: 전력을 다하지 않으면 죽을지도 몰라!";
			case 11:
				return "텐시: 건방져!";
			case 12:
				return "텐시: 지루하잖아!";
			case 13:
				return "텐시: 너무 강한거 아니야?";
			case 14:
				return "텐시: 안전한건 딱 질색이야!";
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
				return "작은 돌이 날라와서 당신의 머리에 맞았다.";
			case 1:
				return "갑자기 바닥이 진동했다.";
			case 2:
				return "텐시: 나랑 이야기 하지 않을래?";
			case 3:
				return "텐시: 좋아하는 음식은 뭐야?";
			case 4:
				return "텐시: 천계는 너무 심심해!";
			case 5:
				return "텐시: 좀 더 대담하게 행동해줘!";
			case 6:
				return "텐시: 난 재미있는걸 보고 싶어!";
			case 7:
				return "텐시: 내가 좀 더 재밌게 해줄 수 있는데";
			case 8:
				return "텐시: 지루하게 하면 알지?";
			case 9:
				return "발에 날카로운 바위가 튀어나와 넘어질뻔했고, 누군가의 웃음소리가 들렸다.";
			case 10:
				return "당신의 바로 옆에 날카로운 요석이 떨어졌다. \"아깝네!\"";
			case 11:
				return "텐시: 이 위에서 희생양들을 바라보고있는게 내 낙이야!";
			case 12:
				return "텐시: 바로 죽진않을거지? 좀 더 버틸 수 있지?";
			case 13:
				return "텐시: 저기저기, 어떻게 죽을지 내기라도 하지 않을래?";
			case 14:
				sprintf_s(temp,256,"텐시: 저번에 지켜보던 아이는 %s에 죽어버렸어.",mondata[randA(MON_MAX-1)].name.name.c_str());
				return temp;
			case 15:
				{
					int rand_name_ = randA(MON_MAX-1);
					sprintf_s(temp,256,"텐시: %s%s 왜 이렇게 %s걸까? ",mondata[rand_name_].name.name.c_str(),mondata[rand_name_].name.name_is(),randA(1)?"터프한":"귀여운");
					return temp;
				}
			case 16:
				return "텐시: 조금만 기다려, 깜짝 파티를 준비하고 있으니까!";
			case 17:
				return "당신의 이마에 조그만 돌이 날라와 부딪혔다.";
			case 18:
				return "텐시: 재밌는 이야기라도 해줘!";
			case 19:
				return "텐시는 당신을 골리기 위한 계획을 세우고 있다.";
			case 20:
				return "텐시는 따분한듯 하품을 했다.";
			}	
		case TENSI_POTION:
			if(good_)
			{
				switch(randA(4))
				{
				case 0:
					return "텐시가 당신에게 새로운 힘을 주었다.";
				case 1:
					return "텐시: 목마르지않아?";
				case 2:
					return "텐시: 이걸로 좀 더 싸워!";
				case 3:
					return "텐시: 아직 더 즐겁게 해줄 수 있지?";
				case 4:
					return "당신은 텐시가 내려준 물약을 받았다.";
				}
			}
			else
			{
				switch(randA(4))
				{
				case 0:
					return "텐시의 웃음소리가 당신의 머리에 울렸다.";
				case 1:
					return "텐시: 우리집 창고 구석에서 발견한 물약이야!";
				case 2:
					return "텐시: 벌이야!";
				case 3:
					return "텐시: 너를 위해 만든 특제 드링크야!";
				case 4:
					return "당신은 텐시에게 억지로 물약을 들이켜졌다.";
				}
			}
		case TENSI_SUMMON:
			if(good_)
			{
				switch(randA(4))
				{
				case 0:
					return "텐시가 당신에게 동료를 내려주었다.";
				case 1:
					return "텐시: 친구가 필요해?";
				case 2:
					return "텐시: 지원군이야!";
				case 3:
					return "텐시: 이거면 도망치지 않아도 되겠지?";
				case 4:
					return "텐시가 당신의 주변에 우호적인 소환물을 소환했다.";
				}
			}
			else
			{
				switch(randA(4))
				{
				case 0:
					return "텐시가 당신에게 적재적인 소환수를 내려보냈다.";
				case 1:
					return "텐시: 싸우지않을거면... 내가 싸우게할거야!";
				case 2:
					return "텐시: 얼마나 강해졌는지 보고 싶어!";
				case 3:
					return "텐시: 너무 우쭐해진거 아니야?";
				case 4:
					return "텐시의 사악한 시선을 느꼈다.";
				}
			}	
		case TENSI_TELE:
			if(good_)
			{
				switch(randA(4))
				{
				case 0:
					return "텐시가 당신의 공간을 뒤흔들었다.";
				case 1:
					return "텐시: 여기보단 안전할거야!";
				case 2:
					return "텐시: 한숨 돌리는건 어때?";
				case 3:
					return "텐시: 좋은 잠자리를 찾아냈어!";
				case 4:
					return "당신은 공간이 일그러지고 있는 걸 느꼈다.";
				}
			}
			else
			{
				switch(randA(4))
				{
				case 0:
					return "텐시가 당신을 또 다른 곳으로 날려보냈다.";
				case 1:
					return "텐시: 이 곳보단 멋진 장소야!";
				case 2:
					return "텐시: 좀 더 재밌는 곳을 알려줄게!";
				case 3:
					return "텐시: 지루하네, 변화를 줘볼까?";
				case 4:
					return "당신은 시야가 핑핑도는 느낌을 받았다.";
				}
			}	
		case TENSI_EARTHQUAKE:
			switch(randA(4))
			{
			case 0:
				return "당신은 대지가 뒤집히는 느낌을 받았다.";
			case 1:
				return "텐시: 갈라져라!";
			case 2:
				return "텐시: 카 크래쉬!";
			case 3:
				return "텐시: 지진이다!";
			case 4:
				return "강력한 지진이 일어났다!";
			}
		case TENSI_MUNYUM:
			switch(randA(4))
			{
			case 0:
				return "당신은 몸이 아주 단단해지는 것을 느꼈다.";
			case 1:
				return "텐시: 이 복숭아 먹어볼래?";
			case 2:
				return "텐시: 천인의 힘이야!";
			case 3:
				return "텐시: 이젠 맞는 것도 안 아플거야!";
			case 4:
				return "텐시가 당신에게 무념무상의 힘을 주었다.";
			}
		case TENSI_BURST:
			switch(randA(2))
			{
			case 0:
				return "텐시: 쾅!";
			case 1:
				return "텐시: 휘말리지 않게 조심해!";
			case 2:
				return "텐시: 이건 어떨까?";
			}
		case TENSI_WEAPON:
			switch(randA(6))
			{
			case 0:
				return "당신의 손에 붉은 기운이 모이기 시작했다.";
			case 1:
				return "텐시: 무기가 볼품없잖아?";
			case 2:
				return "텐시: 조금만 빌려주는거야!";
			case 3:
				return "텐시: 이젠 누구에게도 지지않을걸?";
			case 4:
				return "텐시: 몰래 빌려주는거니까 누구에게 말하지마!";
			case 5:
				return "텐시: 꼭 돌려줘야해?";
			case 6:
				return "텐시: 들키면 이쿠에게 혼나니깐...";
			}
		case TENSI_KANAME:
			if (good_)
			{
				switch (randA(5))
				{
				case 0:
					return "텐시는 당신에게 지원군을 내려주었다.";
				case 1:
					return "텐시: 이게 있다면 지지는 않겠지?";
				case 2:
					return "텐시: 내가 귀여워 하는 애들이야!";
				case 3:
					return "텐시: 애완용 돌이란거 들어봤어?";
				case 4:
					return "텐시: 조심히 다뤄줘!";
				case 5:
					return "텐시: 카나메 판넬!";
				}
			}
			else {
				switch (randA(5))
				{
				case 0:
					return "텐시: 거기서 멀어지는게 좋을거야";
				case 1:
					return "텐시: 돌 침대라고 들어봤어?";
				case 2:
					return "텐시: 내 돌은 사람을 물진않아... 쏘긴 하지만!";
				case 3:
					return "텐시: 여기서 살아갈 수 있을지 시험해봐야겠어!";
				case 4:
					return "텐시: 이번에 새로 만든 스펠카드인데, 시험 좀 해줄래?";
				case 5:
					return "텐시: 사격연습을 해보지않을래? 물론 너가 표적이야!";
				}
			}
		case TENSI_FIELD:
			switch (randA(4))
			{
			case 0:
				return "당신을 중심으로 무언가 거대한 장막이 펼쳐짐을 느꼈다.";
			case 1:
				return "텐시: 새로운 필드가 필요해?";
			case 2:
				return "텐시: 여기서 싸우는게 좀 더 재밌어보이는데!";
			case 3:
				return "텐시: 텐트 좀 펼칠테니까 도와줄래?";
			case 4:
				return "텐시: 좀 더 좋은 환경이 있는데 시험해볼래?";
			}
		case TENSI_BLIND:
			switch (randA(3))
			{
			case 0:
				return "텐시: 한 숨 잘테니까 불 좀 꺼야겠어";
			case 1:
				return "텐시: 너무 밝지않아?";
			case 2:
				return "텐시: 이게 좀 더 재미있을 거 같지않아?";
			case 3:
				return "텐시: 눈에 보이는 것이 전부는 아니야!";
			}
		case TENSI_BUFF_DEBUFF:
			if (good_)
			{
				switch (randA(5))
				{
				case 0:
					return "텐시는 주변의 흐름을 조절했다.";
				case 1:
					return "텐시: 여기까지 해줬는데도 진다면 각오하는게 좋을거야";
				case 2:
					return "텐시: 이번엔 기분이 좋으니까 특별 선물이야!";
				case 3:
					return "텐시: 이게 적이 느려보인다같은거지?";
				case 4:
					return "텐시: 이걸로 충분하려나?";
				case 5:
					return "텐시: 굼벵이 같은 것들!";
				}
			}
			else {
				switch (randA(5))
				{
				case 0:
					return "텐시: 모두에게 변화를 좀 줘볼까?";
				case 1:
					return "텐시: 파티의 시작이야!";
				case 2:
					return "텐시: 뛰어서 도망치는건 재미없으니까, 모두를 빠르게 해보았지!";
				case 3:
					return "텐시: 이제 도망칠 순 없을껄?";
				case 4:
					return "텐시: 너무 쉽게 이길거같으니까, 좀 강화시켜줘봤지!";
				case 5:
					return "텐시: 좀 더 스릴이 있어야겠지?";
				}
			}
		case TENSI_SUCIDE:
			switch (randA(6))
			{
			case 0:
				return "텐시: 좋은 친구들을 소개해줄게!";
			case 1:
				return "텐시: 괜찮은 애들이라고! 좀 강경파인걸 제외하면 말이지";
			case 2:
				return "텐시: 폭파하는거 좋아해?";
			case 3:
				return "텐시: 용맹하지만 아군을 신경쓰지않는게 단점이긴하지";
			case 4:
				return "텐시: 잠깐이지만 사이좋게 지내줘!";
			case 5:
				return "텐시: 자폭특공이란건 잘 이해할 수 없어... 무슨 종교라도 믿는걸까?";
			case 6:
				return "텐시: 주변을 싹 정리하는데는 이만한게 없지!";
			}
		case TENSI_WEATHER_FOG:
			switch (randA(5))
			{
			case 0:
				return "텐시: 오늘의 날씨는 매우 흐리겠습니다.";
			case 1:
				return "텐시: 난 안개낀날은 별로 좋아하지않아.";
			case 2:
				return "텐시: 이런 날씨에서도 싸울 수 있어?";
			case 3:
				return "텐시: 싫다. 습하고 어둡잖아!";
			case 4:
				return "텐시: 몸을 숨기기엔 적당한 날씨지!";
			case 5:
				return "텐시: 기상발현!";
			}
		case TENSI_WEATHER_THUNDER:
			switch (randA(6))
			{
			case 0:
				return "텐시: 오늘의 날씨는 큰 천둥번개가 치겠습니다!";
			case 1:
				return "텐시: 화끈하게 가자고!";
			case 2:
				return "텐시: 번개에 맞을 확률이 얼마나 되지?";
			case 3:
				return "텐시: 이런건 피할 수 없을껄?";
			case 4:
				return "텐시: 입고있는 옷이 절연소재이길 바랄게!";
			case 5:
				return "텐시: 우르릉 쾅쾅!";
			case 6:
				return "텐시: 비상의 검이여! 하늘에 천둥번개를 모아라!";
			}
		case TENSI_WEATHER_SUN:
			switch (randA(6))
			{
			case 0:
				return "텐시: 오늘의 날씨는 구름 한점없이 쨍쨍하겠습니다.";
			case 1:
				return "텐시: 어떻게 던전에 햇빛이 비치는거지? 뭐 어때!";
			case 2:
				return "텐시: 이런 태양빛 아래서 과연 누가 숨을 수 있을까?";
			case 3:
				return "텐시: 잠시 빨래를 말려야하니까!";
			case 4:
				return "텐시: 햇빛이여!";
			case 5:
				return "텐시: 비상의 검으론 이런 것도 할 수 있지!";
			case 6:
				return "텐시: 오늘은 소풍가는 날이야!";
			}	
		}

	}
	return "텐시는 안들리는 목소리로 소근거렸다.";

}