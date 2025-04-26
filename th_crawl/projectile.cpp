//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: projectile.cpp
//
// 내용: 발사처리(발사물 경로 선택과정)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "projectile.h"
#include "throw.h"
#include "key.h"
#include "player.h"
#include "environment.h"
#include "skill_use.h"
#include "mon_infor.h"
#include "floor.h"
#include "debuf.h"
#include "spellcard.h"





void throwstring(list<item>::iterator it, projectile_infor* infor_)
{
	deletelog();
	if(infor_->spell == -2 || infor_->spell == -3 || infor_->spell == -4)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_PROJECTILE_TARGET),true,false,true,CL_help);
	}
	else if(infor_->spell == -1)
	{
		ostringstream ss;
		printlog(LocalzationManager::locString(LOC_SYSTEM_PROJECTILE) + ":",false,false,true,CL_help);
		printlog(it!=you.item_list.end()?it->GetName():LocalzationManager::locString(LOC_SYSTEM_PROJECTILE_NOT_EXIST),false,false,true,it!=you.item_list.end()?it->item_color():CL_danger);
		
		ss << "(i - " << LocalzationManager::locString(LOC_SYSTEM_INVENTORY);
		if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_INVENTORY)) < 10)
			ss << std::string(10-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_INVENTORY)), ' ');
		ss << " (,) - " << LocalzationManager::locString(LOC_SYSTEM_OTTER_PROJECTILE) << ")";
		
		printlog(ss.str(),true,false,true,CL_help);
	}
	else
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_MAGIC) + ":",false,false,true,CL_help);
		printlog(infor_->skill?SkillString((skill_list)infor_->spell):SpellString((spell_list)infor_->spell),true,false,true,CL_help);
	}
}



void refreshPath_before(const coord_def &c, beam_iterator& beam, list<item>::iterator it, projectile_infor* infor_, int m_len_, float sector_)
{
	(infor_->skill) ? SkillFlagCheck((skill_list)infor_->spell, S_FLAG_RECT) : SpellFlagCheck((spell_list)infor_->spell, S_FLAG_RECT);


	if (infor_->smite)
		paintpath(you.search_pos, beam, it, false, infor_, m_len_, sector_);
	if (infor_->spell == -2 && SpellcardFlagCheck((spellcard_evoke_type)infor_->spell, S_FLAG_DEBUF))
	{
		spell_list sp_ = (spell_list)infor_->spell;
		int power_ = min(SpellCap(sp_), you.GetSpellPower(SpellSchool(sp_, 0), SpellSchool(sp_, 1), SpellSchool(sp_, 2)));
		Search_Move(c, false, VT_DEBUF, GetDebufPower(sp_, power_));
	}
	else if (infor_->spell > -2 && infor_->skill == false && SpellFlagCheck((spell_list)infor_->spell, S_FLAG_DEBUF))
	{
		spell_list sp_ = (spell_list)infor_->spell;
		int power_ = min(SpellCap(sp_), you.GetSpellPower(SpellSchool(sp_, 0), SpellSchool(sp_, 1), SpellSchool(sp_, 2)));
		Search_Move(c, false, VT_DEBUF, GetDebufPower(sp_, power_));
	}
	else if (infor_->spell > -2 && infor_->skill == true && SkillFlagCheck((skill_list)infor_->spell, S_FLAG_DEBUF))
	{
		skill_list sp_ = (skill_list)infor_->spell;
		int power_ = min(SkillCap(sp_), SkillPow(sp_));
		Search_Move(c, false, VT_DEBUF, GetDebufPower(sp_, power_));
	}
	else if (infor_->spell > -2 && infor_->skill == true && infor_->spell == SKL_SATORI_2)
	{
		Search_Move(c, false, VT_SATORI);

	}
	else
		Search_Move(c, false, VT_THROW);
	if (!infor_->smite)
		paintpath(you.search_pos, beam, it, false, infor_, m_len_, sector_);
}

bool refreshPath_after(const coord_def &c, beam_iterator& beam, list<item>::iterator it, projectile_infor* infor_, int m_len_, float sector_)
{
	throwstring(it, infor_);
	bool rect_ = (infor_->skill) ? SkillFlagCheck((skill_list)infor_->spell, S_FLAG_RECT) : SpellFlagCheck((spell_list)infor_->spell, S_FLAG_RECT);

	bool good_path = (!infor_->smite)?CheckThrowPath(you.position,you.search_pos,beam):env[current_level].isMove(you.search_pos.x,you.search_pos.y,true);
	int length_ = pow((float)abs(you.search_pos.x-you.position.x),2)+pow((float)abs(you.search_pos.y-you.position.y),2);
	if(length_<3)
		length_ = 1;
	int type_ = rect_?2:1;
	if(type_ == 1 && length_>infor_->length*infor_->length)
		good_path = false;
	else if(type_ == 2 && infor_->length<max(abs(you.search_pos.x-you.position.x) ,abs(you.search_pos.y-you.position.y)))
		good_path = false;


	if(good_path/* && !infor_->smite*/)
		paintpath(you.search_pos, beam, it, true, infor_, m_len_, sector_);
	return good_path;
}


bool refreshPath(const coord_def &c, beam_iterator& beam, list<item>::iterator it, projectile_infor* infor_, int m_len_, float sector_)
{
	refreshPath_before(c, beam,  it, infor_, m_len_, sector_);
	return refreshPath_after(c, beam, it, infor_, m_len_, sector_);
}





int Common_Throw(list<item>::iterator& it, vector<monster>::iterator it2, beam_iterator& beam, projectile_infor* infor_, int m_len_ , float sector_, bool auto_)
{
	you.search_pos = you.position;
	you.search = true;
	bool sukima_ = (infor_->skill)?SkillFlagCheck((skill_list) infor_->spell, S_FLAG_SUKIMA):SpellFlagCheck((spell_list) infor_->spell, S_FLAG_SUKIMA);
	bool other_buff_ = (infor_->skill)?SkillFlagCheck((skill_list) infor_->spell, S_FLAG_OTHER_BUF):SpellFlagCheck((spell_list) infor_->spell, S_FLAG_OTHER_BUF);
	bool rect_ = (infor_->skill)?SkillFlagCheck((skill_list) infor_->spell, S_FLAG_RECT):SpellFlagCheck((spell_list) infor_->spell, S_FLAG_RECT);
	bool no_target_ = (infor_->skill)?SkillFlagCheck((skill_list) infor_->spell, S_FLAG_NO_TARGET):SpellFlagCheck((spell_list) infor_->spell, S_FLAG_NO_TARGET);



	
	if(infor_->isitem && it == you.item_list.end())
	{
		for(it=you.item_list.begin(); it != you.item_list.end(); it++)
		{
			if((*it).can_throw && you.equipment[ET_WEAPON] != &(*it))
				break;
		}
	}

	if(it2 != env[current_level].mon_vector.end())
	{
		if(no_target_ || !(*it2).isLive() || !(*it2).isYourShight())
		{
			it2 = env[current_level].mon_vector.end();
		}
		else
		{
			int length_ = pow((float)abs(it2->position.x-you.position.x),2)+pow((float)abs(it2->position.y-you.position.y),2);
			if(length_<3)
				length_ = 1;
			if(infor_->length)
			{
				int type_ = rect_?2:1;
				if(type_ == 1 && length_ > infor_->length*infor_->length)
					it2 = env[current_level].mon_vector.end();
				else if(type_ == 2 && infor_->length<max(abs(it2->position.x-you.position.x) ,abs(it2->position.y-you.position.y)))
					it2 = env[current_level].mon_vector.end();
			}
		}
	}

	if(!no_target_ && it2 == env[current_level].mon_vector.end())
	{
		if(sukima_)
		{
			for(auto it3=env[current_level].floor_list.begin(); it3 != env[current_level].floor_list.end(); it3++)
			{
				if((*it3).type == FLOORT_SCHEMA && env[current_level].isInSight(it3->position))
				{
					int length_ = pow((float)abs(it3->position.x-you.position.x),2)+pow((float)abs(it3->position.y-you.position.y),2);
					if(length_<3)
						length_ = 1;
					if(!infor_->length || length_ <= infor_->length*infor_->length)
					{						
						it2 = env[current_level].mon_vector.end();
						you.search_pos = it3->position;
						break;
					}
				}
			}
		}
		else
		{
			for(it2=env[current_level].mon_vector.begin(); it2 != env[current_level].mon_vector.end(); it2++)
			{
				if((*it2).isLive() && !((*it2).flag & M_FLAG_UNHARM) && (*it2).isYourShight() && (other_buff_ ^ !(*it2).isUserAlly()) )
				{
					int length_ = pow((float)abs(it2->position.x-you.position.x),2)+pow((float)abs(it2->position.y-you.position.y),2);
					if(length_<3)
						length_ = 1;
					if(!infor_->length)
						break;
					{
						int type_ = rect_?2:1;
						if(type_ == 1 && length_ <= infor_->length*infor_->length)
							break;
						else if(type_ == 2 && infor_->length >= max(abs(it2->position.x-you.position.x) ,abs(it2->position.y-you.position.y)))
							break;
					}
				}
			}
		}
	}
	if(it2 != env[current_level].mon_vector.end())
		you.search_pos = (*it2).position;



	bool good_path = refreshPath(coord_def(you.position.x,you.position.y), beam, it, infor_, m_len_, sector_);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = auto_? VK_RETURN : waitkeyinput(inputedKey);
		switch(key_)
		{
		case 'k':
			good_path = refreshPath(coord_def(you.position.x,you.position.y-1), beam, it, infor_, m_len_, sector_);
			break;
		case 'j':
			good_path = refreshPath(coord_def(you.position.x,you.position.y+1), beam, it, infor_, m_len_, sector_);
			break;
		case 'h':
			good_path = refreshPath(coord_def(you.position.x-1,you.position.y), beam, it, infor_, m_len_, sector_);
			break;
		case 'l':
			good_path = refreshPath(coord_def(you.position.x+1,you.position.y), beam, it, infor_, m_len_, sector_);
			break;
		case 'b':
			good_path = refreshPath(coord_def(you.position.x-1,you.position.y+1), beam, it, infor_, m_len_, sector_);
			break;
		case 'n':
			good_path = refreshPath(coord_def(you.position.x+1,you.position.y+1), beam, it, infor_, m_len_, sector_);
			break;
		case 'y':
			good_path = refreshPath(coord_def(you.position.x-1,you.position.y-1), beam, it, infor_, m_len_, sector_);
			break;
		case 'u':
			good_path = refreshPath(coord_def(you.position.x+1,you.position.y-1), beam, it, infor_, m_len_, sector_);
			break;
		case '+':
		case '=':
			{
				int i = 0;
				while(i < env[current_level].mon_vector.size())
				{
					if(it2 != env[current_level].mon_vector.end())
						it2++;
					if(it2 == env[current_level].mon_vector.end())
						it2 = env[current_level].mon_vector.begin();
					if((*it2).isLive() && (*it2).isYourShight())
					{
						int length_ = pow((float)abs(it2->position.x-you.position.x),2)+pow((float)abs(it2->position.y-you.position.y),2);
						if(length_<3)
							length_ = 1;
						if(!infor_->length || length_ <= infor_->length*infor_->length)
							break;
					}
					i++;
				}
				if(i>=env[current_level].mon_vector.size())
					it2 = env[current_level].mon_vector.end();

				if(it2 != env[current_level].mon_vector.end())
					you.search_pos = (*it2).position;
				good_path = refreshPath(coord_def(you.position.x,you.position.y), beam, it, infor_, m_len_, sector_);
				break;
			}
		case '-':
			{
				int i = 0;
				while(i < env[current_level].mon_vector.size()) //나중에 빠른 던지기 무기로 바꾸기
				{
					if(it2 != env[current_level].mon_vector.begin())
						it2--;
					else if(it2 == env[current_level].mon_vector.begin())
					{
						it2 = env[current_level].mon_vector.end();
						it2--;
					}
					if((*it2).isLive() && (*it2).isYourShight())
					{
						int length_ = pow((float)abs(it2->position.x-you.position.x),2)+pow((float)abs(it2->position.y-you.position.y),2);
						if(length_<3)
							length_ = 1;
						if(!infor_->length || length_ <= infor_->length*infor_->length)
							break;
					}
					i++;
				}
				if(i>= env[current_level].mon_vector.size())
					it2 = env[current_level].mon_vector.end();
				if(it2 != env[current_level].mon_vector.end())
					you.search_pos = (*it2).position;
				good_path = refreshPath(coord_def(you.position.x,you.position.y), beam, it, infor_, m_len_, sector_);
				break;
			}
		case 'v':
			if(unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y))
			{
				if(!unit_->isplayer())
				{
					GetMonsterInfor((monster*)unit_);
					changedisplay(DT_SUB_TEXT);
					waitkeyinput();
					changedisplay(DT_GAME);
				}
			}
			break;

			//아이템 던지기 전용
		case ')':
			if(infor_->isitem)
			{
				int i = 0;
				refreshPath_before(coord_def(you.position.x, you.position.y), beam, it, infor_, m_len_, sector_);
				while(i < you.item_list.size()) //나중에 빠른 던지기 무기로 바꾸기
				{
					if(it != you.item_list.end())
						it++;
					if(it == you.item_list.end())
						it = you.item_list.begin();
					if((*it).can_throw && you.equipment[ET_WEAPON] != &(*it))
						break;
					i++;
				}
				if(i>=you.item_list.size())
					it = you.item_list.end();
				good_path = refreshPath_after(coord_def(you.position.x,you.position.y), beam, it, infor_, m_len_, sector_);
			}
			break;
		case '(':
			if(infor_->isitem)
			{
				int i = 0;
				refreshPath_before(coord_def(you.position.x, you.position.y), beam, it, infor_, m_len_, sector_);
				while(i < you.item_list.size()) //나중에 빠른 던지기 무기로 바꾸기
				{
					if(it != you.item_list.begin())
						it--;
					else if(it == you.item_list.begin())
					{
						it = you.item_list.end();
						it--;
					}
					if((*it).can_throw && you.equipment[ET_WEAPON] != &(*it))
						break;
					i++;
				}
				if(i>=you.item_list.size())
					it = you.item_list.end();
				good_path = refreshPath_after(coord_def(you.position.x,you.position.y), beam, it, infor_, m_len_, sector_);
			}
			break;
		case 'i':
			if(infor_->isitem)
			{
				refreshPath_before(coord_def(you.position.x, you.position.y), beam, it, infor_, m_len_, sector_);
				it = ThrowSelect();
				good_path = refreshPath_after(coord_def(you.position.x,you.position.y), beam, it, infor_, m_len_, sector_);
			}
			break;
		case VK_RETURN:
			paintpath(you.search_pos, beam, it, false, infor_, m_len_, sector_); 
			if (good_path || sukima_ || no_target_)
			{
				deletelog();
				you.search = false;
				return 1;
			}
		case '.':
			paintpath(you.search_pos, beam, it, false, infor_, m_len_, sector_); 
			if(good_path || sukima_)
			{
				deletelog();
				you.search = false;
				return 2;
			}
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				break;
			}
		case VK_ESCAPE:
			deletelog();
			paintpath(you.search_pos, beam, it, false,infor_, m_len_, sector_);
			deletelog();
			you.search = false;
			return 0;
		}
	}
}


int Direc_Throw(int auto_direc_, coord_def* c)
{
	while(1)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_PROJECTILE_DIRECTION),true,false,true,CL_help);
		InputedKey inputedKey;
		int key_= (auto_direc_>0? auto_direc_ :waitkeyinput(inputedKey));
		switch(key_)
		{
		case 'k':
			(*c) = coord_def(you.position.x,you.position.y-1);
			return 'k';
		case 'j':
			(*c) = coord_def(you.position.x,you.position.y+1);
			return 'j';
		case 'h':
			(*c) = coord_def(you.position.x-1,you.position.y);
			return 'h';
		case 'l':
			(*c) = coord_def(you.position.x+1,you.position.y);
			return 'l';
		case 'b':
			(*c) = coord_def(you.position.x-1,you.position.y+1);
			return 'b';
		case 'n':
			(*c) = coord_def(you.position.x+1,you.position.y+1);
			return 'n';
		case 'y':
			(*c) = coord_def(you.position.x-1,you.position.y-1);
			return 'y';
		case 'u':
			(*c) = coord_def(you.position.x+1,you.position.y-1);
			return 'u';
		case VK_RETURN:
			(*c) = coord_def(you.position.x,you.position.y);
			return VK_RETURN;
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				break;
			}
		case VK_ESCAPE:
			deletelog();
			return 0;
		default:
			printlog(LocalzationManager::locString(LOC_SYSTEM_WRONG_CHOOSE),true,false,true,CL_help);
		}
	}
	return 0;
}