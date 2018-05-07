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
#include "key.h"
#include "soundmanager.h"
#include "weapon.h"
#include "god.h"
#include "rect.h"


const char *evoke_string[EVK_MAX]=
{
	"보탑",
	"에어두루마리",
	"몽혼",
	"4척 매직봄",
	"오쿠리쵸친",
	"공중어뢰",
	"요술망치"
};
const bool evoke_string_is[EVK_MAX]=
{
	true,
	false,
	true,
	true,
	true,
	false,
	false
};


int getEvokeItem() {
	random_extraction<int> random_evoke;

	random_evoke.push(EVK_PAGODA,10);
	random_evoke.push(EVK_AIR_SCROLL, 10);
	random_evoke.push(EVK_BOMB, 10);
	random_evoke.push(EVK_GHOST_BALL, 10);
	//random_evoke.push(EVK_DREAM_SOUL, 2); //안나옴
	return random_evoke.pop();
}

void MakeEvokeItem(item_infor* t, int kind_)
{	
	if(kind_ == -1 || (kind_<0 && kind_>=EVK_MAX))
		kind_= getEvokeItem();

	t->value1 = kind_;
	t->value2 = 0;
	t->value3 = 0;
	t->value4 = 0;
	t->value5 = 0;
	t->value6 = 0;
	t->is_pile = false;
	t->can_throw = false;
	t->image = kind_==EVK_PAGODA?&img_item_evo_pagoda:
	kind_==EVK_AIR_SCROLL?&img_item_evo_air_scroll:
	kind_==EVK_DREAM_SOUL?&img_item_evo_dream_soul:
	kind_ == EVK_BOMB? &img_item_evo_bomb:
	kind_ == EVK_GHOST_BALL? &img_item_evo_ghost_ball:
	kind_ == EVK_SKY_TORPEDO? &img_item_evo_sky_torpedo:
	kind_ == EVK_MAGIC_HAMMER ? &img_item_evo_hammer :
		&img_mons_default;
	t->name.name = evoke_string[kind_];
	t->name.name_type = evoke_string_is[kind_];
	t->weight = 1.0f;
	t->value = 300;
}






bool EvokeFlagCheck(evoke_kind skill, skill_flag flag);
int EvokeLength(evoke_kind skill);
float EvokeSector(evoke_kind skill);
int EvokeSuccece(evoke_kind skill);
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

	if(randA(99) >= EvokeSuccece(kind))
	{		
		printlog("아무런 일도 일어나지 않았다.",true,false,false,CL_normal);	
		return true;
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
		projectile_infor infor(EvokeLength(kind),false,EvokeFlagCheck(kind, S_FLAG_SMITE), kind ==EVK_BOMB?-4: -3,false);
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
			else {
				SetSpellSight(0, 0);
				return false;
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
		return 5;
	case EVK_AIR_SCROLL:
		return 50;
	case EVK_DREAM_SOUL:
		return 50;
	case EVK_BOMB:
		return 30;
	case EVK_GHOST_BALL:
		return you.s_evoke_ghost?0:50;
	case EVK_SKY_TORPEDO:
		return 3;
	case EVK_MAGIC_HAMMER:
		return 100;
	default:
		return false;
	}
}


bool EvokeFlagCheck(evoke_kind skill, skill_flag flag)
{
	switch(skill)
	{
	case EVK_BOMB:
	case EVK_SKY_TORPEDO:
		return false;
	case EVK_PAGODA:
		return (S_FLAG_PENETRATE) & flag;
	case EVK_AIR_SCROLL:
	case EVK_DREAM_SOUL:
	case EVK_GHOST_BALL:
	case EVK_MAGIC_HAMMER:
		return (S_FLAG_IMMEDIATELY) & flag;
	default:
		return false;
	}
}

int EvokeLength(evoke_kind skill)
{
	switch(skill)
	{
	case EVK_BOMB:
		return 6;
	case EVK_PAGODA:
	case EVK_SKY_TORPEDO:
		return 8;
	case EVK_AIR_SCROLL:
	case EVK_DREAM_SOUL:
	case EVK_GHOST_BALL:
	case EVK_MAGIC_HAMMER:
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
int EvokeSuccece(evoke_kind skill)
{
	switch(skill)
	{
	case EVK_AIR_SCROLL:
		return 30+ you.GetSkillLevel(SKT_EVOCATE, true)*7;
	default:
		return 100;
	}


}
void HammerPresent();
void returnHammerItem();
string DreamSoulMonster(vector<int>& list_, int level_);



bool EvokeEvokable(evoke_kind kind, bool short_, coord_def &target)
{
	if(target == you.position && !EvokeFlagCheck(kind,S_FLAG_SEIF) && !EvokeFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		printlog("자살할거야?",true,false,false,CL_small_danger);	
		return false;
	}
	int level_ = you.GetSkillLevel(SKT_EVOCATE, true);
	level_ = max(level_,you.level/3 + you.GetSkillLevel(SKT_EVOCATE, true)*2/3);
	
	switch(kind)
	{
	case EVK_PAGODA:
		{
			beam_iterator beam(you.position,target);
			if(CheckThrowPath(you.position,target,beam)){
				beam_infor temp_infor(randC(3,3+level_*2/3),3*(3+level_*2/3),16 + level_ / 8,&you,you.GetParentType(),EvokeLength(kind),8,BMT_PENETRATE,ATT_THROW_NORMAL,name_infor("레이저",false));
				if(short_)
					temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));

				for (int i = 0; i < (you.GetParadox() ? 2 : 1); i++) {
					soundmanager.playSound("laser");
					throwtanmac(29, beam, temp_infor, NULL);
				}
				you.SetParadox(0); 
				return true;
			}
			return false;	
		}	
	case EVK_AIR_SCROLL:
		{
			soundmanager.playSound("buff");
			printlog("에어두루마리로부터 영력을 얻었다!",false,false,false,CL_normal);
			int value_ = 8 + level_ / 3 + randA(3 + level_ / 3);
			you.MpUpDown(value_);
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
			soundmanager.playSound("summon");
			printarray(true,false,false,CL_normal,3,"당신은 ",s_.c_str(),"의 꿈을 불러냈다!");
			return true;
		}
	case EVK_MAGIC_HAMMER:
		{
			printlog("", true, false, true, CL_seija);
			printlog("", true, false, true, CL_seija);
			printlog("", true, false, true, CL_seija);
			printlog("", true, false, true, CL_seija);
			printlog("", true, false, true, CL_seija);
			printlog("", true, false, true, CL_seija);
			printlog("", true, false, true, CL_seija);
			printlog("", true, false, true, CL_seija);
			bool loop_ = true;
			while (loop_)
			{
				int percent_ = 9;
				int select_ = 0;
				deletelog();
				printlog("요술망치로 무슨 소원을 빌거야?", true, false, true, CL_help);
				printlog("a - 날 회복시켜줘!", true, false, true, CL_normal);
				printlog("b - 날 강하게 만들어줘!", true, false, true, CL_normal);
				printlog("c - 많은 동료를 원해!", true, false, true, CL_normal);
				printlog("d - 보물을 원해!", true, false, true, CL_normal);
				int key_ = waitkeyinput();
				switch (key_) {
					case 'a':
					case 'A':
					{
						if (randA(percent_)) {
							soundmanager.playSound("buff");
							you.HpUpDown(you.GetMaxHp() - you.GetHp(), DR_EFFECT);
							if (!you.pure_mp)
								you.MpUpDown(you.GetMaxMp() - you.GetMp());
							printlog("요술망치가 당신을 최대로 회복시켰다!", true, false, false, CL_good);
							loop_ = false;
						}
						else {
							you.HpUpDown(-you.GetHp() * 2 / 3, DR_EFFECT);
							if (!you.pure_mp)
								you.MpUpDown(-you.GetMp());
							soundmanager.playSound("laugh");
							printlog("요술망치의 마력이 역류하였다! 당신의 체력과 영력이 빨려들었다!", true, false, false, CL_danger);
							loop_ = false;
						}
						break;
					}
					case 'b':
					case 'B':
						if (randA(percent_)) {
							soundmanager.playSound("buff");
							you.SetForceStrong(true, rand_int(30, 60), true);
							printlog("요술망치가 당신을 강하게 만들었다!", true, false, false, CL_good);
							loop_ = false;
						}
						else {
							int time_ = rand_int(30, 60);
							you.SetSlow(time_);
							you.SetForceStrong(false, time_, true);
							soundmanager.playSound("laugh");
							printlog("요술망치의 마력이 역류하였다! 당신은 약해졌다!", true, false, false, CL_danger);
							loop_ = false;
						}
						break;
					case 'c':
					case 'C':
					{
						bool good_ = true;
						if (randA(percent_)) {
							good_ = true;
						}
						else {
							good_ = false;
						}
						int time_ = rand_int(40, 80);
						bool return_ = false;
						int i = rand_int(4, 5);
						for (; i > 0; i--)
						{
							if (monster *mon_ = BaseSummon(MON_OCCULT_SMALL, time_, true, false, 2, &you, target, SKD_SUMMON_OCCULT, 5))
							{
								mon_->LevelUpdown(you.level, 4.0f, 1.5f);
								mon_->s_haste = time_+1;
								if (!good_) {
									mon_->ReturnEnemy();
								}
								mon_->PlusTimeDelay(-2*mon_->GetWalkDelay());
								return_ = true;
							}
						}
						if (good_) {
							soundmanager.playSound("buff");
							printlog("요술망치가 동료들을 불러냈다!", true, false, false, CL_good);
						}
						else {
							soundmanager.playSound("laugh");
							printlog("요술망치의 마력이 역류하였다! 동료가 모두 적대적으로 변했다!", true, false, false, CL_danger);
						}
						loop_ = false;
						break;
					}
					case 'd':
					case 'D':
					{
						if (randA(percent_)) {
							HammerPresent();
							soundmanager.playSound("buff");
							printlog("요술망치가 보물을 만들어냈다!", true, false, false, CL_good);
						}
						else {
							returnHammerItem();
							random_extraction<int> oni_;
							oni_.push(MON_ONI);
							oni_.push(MON_BLUE_ONI);
							int i = rand_int(1 + you.level / 10, 1 + you.level / 5);
							for (; i>0; i--)
							{
								int time_ = rand_int(40, 60);
								if (monster *mon_ = BaseSummon(oni_.choice(), time_, true, true, 2, NULL, you.position, SKD_OTHER, -1))
								{
									if (randA(99)<max(0, 200 - you.level * 30))
										mon_->SetSlow(time_);
									if (randA(99)<max(0, you.level * 4 - 28))
										mon_->SetMight(time_);
									if (randA(99)<max(0, you.level * 5 - 65))
										mon_->SetHaste(time_);
									mon_->PlusTimeDelay(-2 * mon_->GetWalkDelay());
								}
							}
							soundmanager.playSound("laugh");
							printlog("요술망치의 마력이 역류하였다! 보물이 모두 회수되었다!", true, false, false, CL_danger);
						}

						loop_ = false;
						break;
					}
					case VK_ESCAPE:
						printlog("취소했다.", true, false, false, CL_normal);
						return false;
					default:
						break;
				}


			}
			return true;
		}
	case EVK_BOMB:
	{
		beam_iterator beam(you.position, target);
		coord_def final_postion_ = (*beam);
		bool end_ = false;
		while (!end_) {
			if (beam.end()) {
				end_ = true;
			}
			coord_def postion_ = (*beam);
			if (!env[current_level].isMove(postion_, true) || env[current_level].isMonsterPos(postion_.x, postion_.y)) {
				break;
			}
			env[current_level].MakeEffect(postion_, &img_item_evo_bomb, false);
			Sleep(16);
			env[current_level].ClearEffect();
			final_postion_ = postion_;
			beam++;
		}
		if (env[current_level].dgtile[final_postion_.x][final_postion_.y].tile == DG_SEA || 
			env[current_level].dgtile[final_postion_.x][final_postion_.y].tile == DG_LAVA) {
			soundmanager.playSound("water");
			printlog("4척 매직봄은 물에 빠져버렸다. ", true, false, false, CL_normal);

		}
		else if (monster *mon_ = BaseSummon(MON_BOMB, 10, true, false, 2, &you, final_postion_, SKD_OTHER, -1))
		{
			if (level_ > 1)
				mon_->LevelUpdown(level_ - 1, 1.0f);
		}

		return true;
	}
	case EVK_GHOST_BALL:
	{
		soundmanager.playSound("ufo");
		if (you.s_evoke_ghost) {
			printlog("당신은 오쿠리쵸친으로부터 손을 놓았다. ", true, false, false, CL_magic);
			you.PowUpDown(50, true);
			you.SetEvokeGhost(0);
		}
		else {
			printlog("당신은 생명력을 대가로 유령화하였다! 한번 더 발동해서 해제할 수 있다.", true, false, false, CL_magic);
			float bonus_ = 1.0f - (1.0f * level_ / 27);
			int hp_ = min(you.GetHp() -1, you.GetHp() * (0.3f + 0.5f * bonus_));
			you.HpUpDown(-hp_, DR_EFFECT);
			you.PowUpDown(-50, true);
			you.SetEvokeGhost(-1);
		}
	}
	case EVK_SKY_TORPEDO:
	{
		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam)) {
			beam_infor temp_infor(randC(3, 2 + level_ * 3 / 4), 3 * (2 + level_ * 3 / 4), 17+ level_/8, &you, you.GetParentType(), EvokeLength(kind),1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor("공중어뢰", false));
			if (short_)
				temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));

			for (int i = 0; i < (you.GetParadox() ? 2 : 1); i++) {
				soundmanager.playSound("shoot");
				throwtanmac(19, beam, temp_infor, NULL);
			}
			you.SetParadox(0);
			return true;
		}
		return false;
	}
	}
	return false;
}


bool evoke_bomb(int power, bool short_, unit* order, coord_def target)
{
	if (1)
	{
		if (env[current_level].isInSight(order->position)) {
			soundmanager.playSound("nuke");
		}
		textures* t_ = &img_blast[0];
		{
			rect_iterator rit(order->position, 2, 2);

			for (; !rit.end(); rit++)
				if (env[current_level].isMove(rit->x, rit->y, true))
				{
					if (order->isSightnonblocked(*rit))
					{
						env[current_level].MakeEffect(*rit, t_, false);
					}
				}
		}

		{
			rect_iterator rit(order->position, 2, 2);

			for (; !rit.end(); rit++)
			{
				if (env[current_level].isMove(rit->x, rit->y, true))
				{
					if (order->isSightnonblocked(*rit))
					{
						if (unit* hit_ = env[current_level].isMonsterPos(rit->x, rit->y))
						{
							if (hit_ != order)
							{
								int att_ = randC(4, 8 + power / 25);
								int m_att_ = 4 * (8 + power / 25);

								attack_infor temp_att(att_, m_att_, 99, order, order->GetParentType(), ATT_NORMAL_BLAST, name_infor("매직봄", true));
								hit_->damage(temp_att, true);
							}
						}
					}
				}
			}
		}
		Sleep(300);
		env[current_level].ClearEffect();
		return true;
	}
	return false;
}

void HammerPresent() {
	int kind_ = rand_int(1, 3);
	item* it = NULL;
	if (kind_ == 1) {
		random_extraction<int> rand_;

		for (int i = SKT_SHORTBLADE; i <= SKT_SPEAR; i++)
		{
			rand_.push(i - SKT_SHORTBLADE, you.GetSkillLevel(i, true) + 1);
		}

		item_infor t;
		it = env[current_level].MakeItem(you.position, makeitem((item_type)(rand_.pop()), 1, &t));
		it->value4 += rand_int(0, 5);
		if (!it->value5 && randA(2) > 1)
			it->value5 = GetNewBrand(0); //카나코는 신의 브랜드는 선물하지 않는다.
		MakeArtifact(it, 1);
	}
	else if (kind_ == 2) {
		it = armour_gift(false, true);
	}
	else {
		it = jewelry_gift(false, false, true);
	}
	if (it != NULL) {
		//10%의 확률로 회수해간다.
		it->hamme_gift = true;
	}
}


void returnHammerItem() {
	//아이템 회수
	for (int i = 0; i < MAXLEVEL; i++) {
		for (auto it = env[i].item_list.begin(); it != env[i].item_list.end(); ) {
			auto temp = it++;
			if ((*temp).hamme_gift) {
				env[i].DeleteItem(temp);
			}
		}
	}
	for (auto it = you.item_list.begin(); it != you.item_list.end(); ) {
		auto temp = it++;
		if ((*temp).hamme_gift) {

			for (equip_type i = ET_FIRST; i != ET_LAST; i = (equip_type)(i + 1))
			{
				if (you.equipment[i] == &(*temp))
				{
					you.unequip(i, true);
					break;
				}
			}
			you.DeleteItem(temp);
		}
	}
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