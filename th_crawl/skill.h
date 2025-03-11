//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: skill.h
//
// 내용: skill관련
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SKILL_H__
#define  __SKILL_H__

#include "enum.h"
#include "d3dUtility.h"

typedef struct skill_exp_infor
{
	int level;
	int exper;
	int aptit;
	int onoff;
	skill_exp_infor():level(0), exper(0), aptit(100), onoff(0)
	{}
}skill_exp_infor;

int AptCal(int aptitu_);
int need_skill_exp(int level, int aptit);
int exp_to_skill_exp(int level);
int skill_exp_penalty(int total_skill_exp);
char* skill_string(skill_type skill);
int GetSkillPercent(const skill_exp_infor &skill);
int GetMaxSkillExp(const skill_exp_infor &skill);
int GetBaseSkillExp();
//int GetSkillDisplay(int aptit_);
D3DCOLOR GetSkillColor(int aptit_);


extern int aptitude[TRI_MAX][SKT_MAX];
extern int exp_aptitude[TRI_MAX];


#endif // __SKILL_H__