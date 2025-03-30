//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: moninfor.cpp
//
// 내용: 몬스터의 정보띄우기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "monster.h"
#include "mon_infor.h"
#include "skill_use.h"
#include "player.h"
#include "debuf.h"

extern HANDLE mutx;


string GetMonsterInfor(monster *it)
{
	string text_ = it->GetNameString();
	text_ += "\n\n";

	if (it->dream) {
		text_ += "꿈의 세계에 살고 있는 주민\n";
		text_ += "환상향의 주민과 똑같이 닮았지만 꿈의 세계에 살고있는 다른 존재.\n";
		text_ += "원본에서 좀 더 욕망에 충실한 성격을 지녔다고 한다.\n";
	}
	else {
		text_+=LocalzationManager::monDecsriptionString((monster_index)it->id);
	}
	text_ += "\n\n\n";

	if(it->id == MON_REIMU)
	{
		char temp[100];
		sprintf_s(temp, 100, "이 레이무는 %d번 컨티뉴했다.\n", max(0,you.reimu_level - 1));
		text_ += temp;
	}

	{
		int mon_level_ = it->level;
		if (it->flag & M_FLAG_UNIQUE)
			mon_level_ += 3;
		int you_level_ = you.level+3;

		if (you_level_ - mon_level_*3 > 3)
			text_ += "이 상대는 무시해도 될 정도로 약해보인다.\n";
		else if (you_level_ - mon_level_*2 > 0)
			text_ += "이 상대는 약해보인다.\n";
		else if (you.level - mon_level_ > 0)
			text_ += "이 상대는 위험해보인다.\n";
		else
			text_ += "이 상대는 아주 위험하다!\n";
	}



	if(it->poison_resist)
	{
		if(it->poison_resist>0)
			text_ += "독에 대한 저항력이 있다.\n";
		else
			text_ += "독에 취약하다.\n";
	}
	if(it->fire_resist)
	{
		if(it->fire_resist==1)
			text_ += "화염에 대한 약간의 저항력이 있다.\n";
		else if(it->fire_resist==2)
			text_ += "화염에 대한 상당한 저항력이 있다.\n";
		else if(it->fire_resist>=3)
			text_ += "화염을 완벽하게 방어한다.\n";
		else
			text_ += "화염에 취약하다.\n";
	}
	if(it->ice_resist)
	{
		if(it->ice_resist==1)
			text_ += "냉기에 대한 약간의 저항력이 있다.\n";
		else if(it->ice_resist==2)
			text_ += "냉기에 대한 상당한 저항력이 있다.\n";
		else if(it->ice_resist>=3)
			text_ += "냉기를 완벽하게 방어한다.\n";
		else
			text_ += "냉기에 취약하다.\n";
	}
	if(it->elec_resist)
	{
		if(it->elec_resist==1)
			text_ += "전기가 잘 통하지 않는다.\n";
		else if(it->elec_resist==2)
			text_ += "전기가 거의 통하지 않는다.\n";
		else if(it->elec_resist>=3)
			text_ += "절연이다.\n";
	}



	if(it->confuse_resist)
	{
		if(it->confuse_resist>0)
			text_ += "혼란과 광기에 대해 면역이 있다.\n";
	}
	if(it->wind_resist)
	{
		if(it->wind_resist>0)
			text_ += "회오리 바람에 면역이 있다.\n";
	}
	if(it->speed != 10)
	{
		if(it->speed<=5)
			text_ += "행동이 매우 빠르다.\n";
		else if(it->speed<=7)
			text_ += "행동이 빠르다.\n";
		else if(it->speed<=9)
			text_ += "행동이 약간 빠르다.\n";
		else if(it->speed<=13)
			text_ += "행동이 약간 느리다.\n";
		else if(it->speed<=18)
			text_ += "행동이 느리다.\n";
		else
			text_ += "행동이 매우 느리다.\n";
	}
	if(it->isFly())
		text_ += "하늘을 날 수 있다.\n";
	if (it->isSwim())
		text_ += "수영을 할 수 있다.\n";
	if(it->flag & M_FLAG_CAN_SEE_INVI)
		text_ += "투명을 볼 수 있다.\n";
	if(it->flag & M_FLAG_INANIMATE)
		text_ += "무생물이다.\n";
	if(it->flag & M_FLAG_RESIST_BLIZARD)
		text_ += "눈보라에 면역이 있다. 달자매의 힘으로\n";
	
	if(it->resist >= 99)
		text_ += "디버프 마법에 대한 면역력이 무한이다.\n";
	else
	{
		text_ += "마법저항: ";
		for (int i = 0; i < 10; i++ ) {
			if (it->GetResist() > 110 + i * 20) {
				text_ += "#";
			}
			else {
				text_ += ".";
			}
		}
		text_ += "\n";
	}
	if (it->flag & M_FLAG_SILENCE)
		text_ += "침묵된 상태에서도 마법이 사용가능하다.\n";


	
	if(it->flag & M_FLAG_SUMMON)
	{
		text_ += "\n\n이 몬스터는 소환된 상태로 시간이 지나면 사라진다. 또한 경험치를 주지도 않는다.\n";
	}
	if (it->dream)
	{
		text_ += "\n이 몬스터는 꿈의 주민이기에 당신의 동료권유나 영혼을 빼앗는 것이 불가능할지도 모른다.\n";
	}

	if(!it->spell_lists.empty())
	{
		text_ += "\n\n\n사용하는 마법\n\n";


		if(!it->isUserAlly() && it->random_spell)
		{
			text_ += "이 몬스터의 마법은 고정되어있지 않다. 무슨 마법을 쓸지 몰라!\n";
		}
		else
		{
			int i = 0;
			char temp[100];
			for(auto its = it->spell_lists.begin(); its != it->spell_lists.end(); its++)
			{
				char sp_char = (i<27)?('a'+i):('A'+i-27);
				spell_list spell_ = (spell_list)its->num;
			
				sprintf_s(temp,100,"%c - %s",sp_char,SpellString(spell_).c_str());
				text_+=temp;
				if(SpellFlagCheck(spell_, S_FLAG_DEBUF))
				{
					int value_ = GetDebufPower(spell_, min(SpellCap(spell_),(it->level-3)*5));
					float percent_ = getDebufPercent (you.GetResist(), value_);
					sprintf_s(temp,100," (%.0f%%)", percent_);
					text_+=temp;

				}

				text_ += "\n";
				i++;
			}
		}

	}


	return text_;

}