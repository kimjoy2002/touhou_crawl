//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: spellcard.cpp
//
// ����: ����ī�� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "spellcard.h"
#include "skill_use.h"
#include "projectile.h"
#include "environment.h"
#include "throw.h"
#include "debuf.h"
#include "soundmanager.h"
#include "mon_infor.h"
#include "rect.h"
#include "tribe.h"

int GetDebufPower(spell_list skill, int power_);//������� �Ŀ�

extern int map_effect;
bool SpellcardFlagCheck(spellcard_evoke_type skill, skill_flag flag);
int Spellcardusepower(spellcard_evoke_type skill, bool max_);
int SpellcardLength(spellcard_evoke_type skill);
bool EvokeSpellcard(spellcard_evoke_type kind, bool short_, int power, coord_def &target);


bool evoke_spellcard(spellcard_evoke_type kind, int power, bool fail_, bool iden_, bool auto_)
{
	if(you.s_confuse)
	{
		printlog("����� ȥ��������.",true,false,false,CL_normal);
		return false;
	}
	if (you.s_pure_turn && you.s_pure >= 10 && !you.GetProperty(TPT_PURE_SYSTEM))
	{
		printlog("����� ����ī�带 ���⿣ �ʹ� ��ȭ�Ǿ��ִ�.", true, false, false, CL_normal);
		return false;
	}
	//if(you.power < Spellcardusepower(kind,true))
	//{
	//	printlog("������ �����ϱ⿣ ����� P�� ���ڶ���.",true,false,false,CL_small_danger);	
	//	return false;
	//}


	soundmanager.playSound("spellcard");

	int i=0;
	/*if(SpellcardFlagCheck(kind, S_FLAG_DIREC))
	{
		SetSpellSight(SpellcardLength(kind),SpellcardFlagCheck(kind, S_FLAG_RECT)?2:1);
		coord_def target_;
		if(Direc_Throw(&target_))
		{
			if(fail_)
				return true;
			if(EvokeSpellcard(kind, false, power, target_))
			{
				you.PowUpDown(-1* Spellcardusepower(kind,false),true);
				return true;
			}
		}
		else
		{
			if(iden_)
				return false;
			else
				return true;
		}

	}
	else */
	if(!SpellcardFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		SetSpellSight(SpellcardLength(kind),SpellcardFlagCheck(kind, S_FLAG_RECT)?2:1);
		beam_iterator beam(you.position,you.position);
		projectile_infor infor(SpellcardLength(kind),false,SpellcardFlagCheck(kind, S_FLAG_SMITE),-2,false);
		if(int short_ = Common_Throw(you.item_list.end(), you.GetTargetIter(), beam, &infor, SpellcardLength(kind), SpellcardSector(kind), auto_))
		{
			if(fail_)
				return true;
			unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
			you.SetBattleCount(30);
			if(unit_)
				you.youAttack(unit_);
			if(EvokeSpellcard(kind, short_ == 2, power, you.search_pos))
			{
				you.PowUpDown(-1* Spellcardusepower(kind,false),true);
				SetSpellSight(0,0);
				return true;
			}
		}
		else
		{
			SetSpellSight(0,0);
			if(iden_)
				return false;
			else
				return true;
		}
	}			
	else if(SpellcardFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		if(fail_)
			return true;
		if(EvokeSpellcard(kind, false, power, you.position))
		{
			you.PowUpDown(-1* Spellcardusepower(kind,false),true);
			return true;
		}
	}
	return false;
}


void createSpellCard(int goodbad, int select_, item_infor* t)
{
	//����Ʈ�³��߿� �Ӽ� ����ī���..
	//���߿� �Ӽ��� ���� ����ī��, �ߵ� ���� ���� ���� ���� ��ġ ���� �� �� �ٲ㺸��
	//������ ������ ����
	t->value2 = select_!=1?(spellcard_evoke_type)select_:randA(SPC_V_MAX-1);
	t->value1 = SpellcardMaxCharge((spellcard_evoke_type)t->value2)*rand_float(0.2f,1);
	t->value3 = 0;
	t->value4 = 0;
	t->value5 = 0;
	t->value6 = 0;
	t->is_pile = false;
	t->can_throw = false;
	t->image = &img_mons_default;
	t->name.name = "����ī��";
	t->name.name_type = false;
	t->weight = 2.0f;
	t->value = 200;
}


float SpellcardSector(spellcard_evoke_type skill)
{
	switch(skill)
	{
	case SPC_V_FIRE:
		return 0.4f;
	case SPC_V_AIR:
		return 0.4f;
	default:
		return 0;
	}
}


bool SpellcardFlagCheck(spellcard_evoke_type skill, skill_flag flag)
{
	switch(skill)
	{

	case SPC_V_FIRE:
	case SPC_V_ICE:
	case SPC_V_AIR:
		return (S_FLAG_PENETRATE) & flag;
	case SPC_V_EARTH:
		return (0) & flag;
	case SPC_V_INVISIBLE:
		return (S_FLAG_IMMEDIATELY) & flag;
	case SPC_V_METAL:
		return (0)& flag;
	case SPC_V_SUN:
		return (S_FLAG_IMMEDIATELY)& flag;
	default:
		return false;
	}
}


const char* SpellcardName(spellcard_evoke_type skill)
{
	switch(skill)
	{
	case SPC_V_INVISIBLE: //��-����+ȸ��
		return "������ ";
	case SPC_V_FIRE: //ȭ-��������
		return "ȭ���� ";
	case SPC_V_ICE: //��-��������Ʈ
		return "�ñ��� ";
	case SPC_V_AIR: //��-���ĳ���
		return "����� ";
	case SPC_V_METAL://��-
		return "�ݼ��� ";
	case SPC_V_EARTH: //��-���ı�
		return "������ ";
	case SPC_V_SUN://��-�ֺ� ���� ȥ��+��������
		return "�¾��� ";
	default:
		return false;
	}
}
int SpellcardMaxCharge(spellcard_evoke_type skill)
{
	switch(skill)
	{
	case SPC_V_FIRE:
		return 9;
	case SPC_V_ICE:
		return 15;
	case SPC_V_EARTH:
		return 15;
	case SPC_V_AIR:
		return 9;
	case SPC_V_INVISIBLE:
		return 9;
	case SPC_V_METAL:
		return 15;
	case SPC_V_SUN:
		return 9;
	default:
		return false;
	}
}

int Spellcardusepower(spellcard_evoke_type skill, bool max_)
{
	switch(skill)
	{

	case SPC_V_FIRE:
	case SPC_V_ICE:
	case SPC_V_EARTH:
	case SPC_V_AIR:
	case SPC_V_INVISIBLE:
	case SPC_V_METAL:
	case SPC_V_SUN:
		return 0;
	default:
		return false;
	}
}


int SpellcardLength(spellcard_evoke_type skill)
{
	switch(skill)
	{

	case SPC_V_FIRE:
	case SPC_V_ICE:
	case SPC_V_EARTH:
		return 8;
	case SPC_V_AIR:
		return 7;
	case SPC_V_INVISIBLE:
	case SPC_V_SUN:
		return 0;
	case SPC_V_METAL:
		return 6;
	default:
		return false;
	}
}





bool EvokeSpellcard(spellcard_evoke_type kind, bool short_, int power, coord_def &target)
{
	if(target == you.position && !SpellcardFlagCheck(kind,S_FLAG_SEIF) && !SpellcardFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		printlog("�ڻ��Ұž�?",true,false,false,CL_small_danger);	
		return false;
	}


	switch (kind)
	{
	case SPC_V_FIRE:
	{
		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam))
		{
			soundmanager.playSound("fire");
			beam_infor temp_infor(0, 0, 99, &you, you.GetParentType(), SpellcardLength(kind), 8, BMT_PENETRATE, ATT_THROW_FIRE, name_infor("�ҹٴ�", false));
			ThrowSector(0, beam, temp_infor, GetSpellSector(SPL_FIRE_SPREAD), [&](coord_def c_) {
				if (you.isSightnonblocked(c_))
				{
					env[current_level].MakeSmoke(c_, img_fog_fire, SMT_FIRE, rand_int(2, 5) + power / 10, 0, &you);
				}
			}, false);
			return true;
		}
		return false;
	}
	case SPC_V_ICE:
	{
		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam)) {
			beam_infor temp_infor(randC(3, 6 + power / 6), 3 * (6 + power / 6), 16, &you, you.GetParentType(), SpellcardLength(kind), 8, BMT_PENETRATE, ATT_THROW_COLD, name_infor("�ñ�", true));
			if (short_)
				temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));

			for (int i = 0; i < (you.GetParadox() ? 2 : 1); i++) {
				soundmanager.playSound("cold");
				throwtanmac(22, beam, temp_infor, NULL);
			}
			you.SetParadox(0);
			return true;
		}
		return false;
	}
	case SPC_V_EARTH:
	{

		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam)) {

			//beam_infor temp_infor(0,0,15,order,order->GetParentType(),length_,1,BMT_NORMAL,ATT_THROW_NONE_MASSAGE,name_infor("ȭ����",false));
			//coord_def pos = throwtanmac(16,beam,temp_infor,NULL);

			beam_infor temp_infor(randC(2, 4 + power / 8), 2 * (4 + power / 8), 10, &you, you.GetParentType(), SpellcardLength(kind), 1, BMT_WALL, ATT_THROW_NORMAL, name_infor("�ϼ�ź", true));
			if (short_)
				temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));

			for (int k = 0; k < (you.GetParadox() ? 2 : 1); k++)
			{
				soundmanager.playSound("shoot");
				coord_def pos = throwtanmac(26, beam, temp_infor, NULL);
				if (env[current_level].dgtile[pos.x][pos.y].isBreakable())
				{
					soundmanager.playSound("stone");
					for (int i = -1; i <= 1; i++)
						for (int j = -1; j <= 1; j++)
							env[current_level].MakeEffect(coord_def(pos.x + i, pos.y + j), &img_blast[1], false);
					for (int i = -1; i <= 1; i++)
					{
						for (int j = -1; j <= 1; j++)
						{
							if (env[current_level].isMove(pos.x + i, pos.y + j, true))
							{
								if (env[current_level].isInSight(coord_def(pos.x + i, pos.y + j)))
								{
									if (unit* hit_ = env[current_level].isMonsterPos(pos.x + i, pos.y + j))
									{
										attack_infor temp_att(randC(3, 5 + power / 8), 3 * (5 + power / 8), 99, &you, you.GetParentType(), ATT_NORMAL_BLAST, name_infor("�ϼ�����", true));
										hit_->damage(temp_att, true);
									}
								}
							}
							else
							{
								if (env[current_level].dgtile[pos.x + i][pos.y + j].isBreakable())
									env[current_level].changeTile(coord_def(pos.x + i, pos.y + j), env[current_level].base_floor);
							}
						}
					}
					env[current_level].MakeNoise(target, 8, NULL);
				}
				else if (!env[current_level].dgtile[pos.x][pos.y].isMove(true, true, false))
				{
					printarray(true, false, false, CL_normal, 3, "�ϼ�ź�� ", dungeon_tile_tribe_type_string[env[current_level].dgtile[pos.x][pos.y].tile], "�� �ε������� �̵��� ���� �ʾҴ�.");
					env[current_level].MakeNoise(target, 8, NULL);
				}
				Sleep(300);
				env[current_level].ClearEffect();
				you.resetLOS();
			}
			you.SetParadox(0);
			return true;
		}
		return false;
	}
	case SPC_V_AIR:
	{
		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam)) {
			beam_infor temp_infor(randC(3, 3 + power / 12), 3 * (3 + power / 12), 99, &you, you.GetParentType(), SpellcardLength(kind), 8, BMT_NORMAL, ATT_THROW_NORMAL, name_infor("�ٶ�", true));


			for (int i = 0; i < (you.GetParadox() ? 2 : 1); i++)
			{
				soundmanager.playSound("wind");
				ThrowSector(25, beam, temp_infor, SpellcardSector(SPC_V_AIR), [&](coord_def c_) {
					if (unit* unit_ = env[current_level].isMonsterPos(c_.x, c_.y))
					{
						if (you.isSightnonblocked(c_))
						{
							coord_def push_(c_ - you.position + c_);
							beam_iterator beam(c_, push_);

							int knockback = 1 + randA(2+power/50);
							int real_knock_ = 0;
							while (knockback)
							{
								if (env[current_level].isMove(coord_def(beam->x, beam->y), unit_->isFly(), unit_->isSwim(), false))
								{
									if (!env[current_level].isMonsterPos(beam->x, beam->y))
									{
										unit_->SetXY(coord_def(beam->x, beam->y));
										real_knock_++;
									}
								}
								else
									break;
								beam++;
								knockback--;
							}
							if (real_knock_)
							{
								printarray(false, false, false, CL_normal, 3, unit_->GetName()->name.c_str(), unit_->GetName()->name_is(true), "�ٶ��� �з�������.");
							}
						}
					}
				}, true);
				enterlog();
			}
			you.SetParadox(0);


			return true;
		}
		return false;
	}
	case SPC_V_INVISIBLE:
	{
		int value_ = rand_int(20, 30);
		value_ += randA(power / 4);
		you.SetInvisible(value_);
		return true;
	}
	case SPC_V_METAL:
	{
		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam)) {
			beam_infor temp_infor(randC(1, 10 + power / 6), 1 * (10 + power / 6), 14, &you, you.GetParentType(), SpellcardLength(kind), 1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor("ö����", false));
			if (short_)
				temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));

			for (int i = 0; i < (you.GetParadox() ? 6 : 3); i++) {
				soundmanager.playSound("shoot");
				throwtanmac(45, beam, temp_infor, NULL);
			}
			you.SetParadox(0);
			return true;
		}
		return false;
	}
	case SPC_V_SUN:
	{
		printlog("������ ���� �ֺ��� ���߾���! ", true, false, false, CL_warning);
		map_effect = 2;
		Sleep(500);
		map_effect = 0;
		for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it!=env[current_level].mon_vector.end(); it++)
		{	
			if(it->isLive() && env[current_level].isInSight(it->position) && you.isSightnonblocked(it->position))
			{
				int power_ = power;
				if (it->id == MON_REMILIA || it->id == MON_FLAN || it->id == MON_FLAN_BUNSIN ||
					it->id == MON_VAMPIER_BAT) {
					int damage_ = 10 + power_ / 12;
					it->damage(attack_infor(randC(3, damage_), 3 * (damage_), 99, &you, you.GetParentType(), ATT_SUN_BLAST, name_infor("�޺�", true)), true);
					power_ += 100;
				}
				if (it->flag & M_FLAG_INANIMATE)
				{
				}
				else if(it->CalcuateMR(power_))
				{
					int value_ = rand_int(3, 8);
					value_ += randA(power_ / 5);
					it->SetConfuse(value_);
				}
				else if(it->isYourShight())
				{
				}
				int value_ = rand_int(10, 20);
				value_ += randA(power_ / 5);
				it->SetGlow(value_, true);
				it->AttackedTarget(&you);			
			}
		}
		if (you.tribe == TRI_VAMPIRE) {
			int damage_ = 8 + power / 12;
			you.damage(attack_infor(randC(3, damage_), 3 * (damage_), 99, &you, you.GetParentType(), ATT_SUN_BLAST, name_infor("�޺�", true)), true);
		}
		return true;
	}
	default:
		return false;
	}
	return false;
}