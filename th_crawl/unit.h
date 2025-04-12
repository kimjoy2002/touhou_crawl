//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: unit.h
//
// ����: unit����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __UNIT_H__
#define  __UNIT_H__

#include "common.h"
#include "enum.h"
#include "const.h"
#include "display.h"
#include "localization.h"

class unit;
class monster;


class name_infor
{
public:
	monster_index name_key;
	string name;
	bool name_type;
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	const char* name_is(bool blank=false)/*����*/const{return (name_type?(blank?"�� ":"��"):(blank?"�� ":"��"));}
	const char* name_to(bool blank=false)/*����*/const{return (name_type?(blank?"�� ":"��"):(blank?"�� ":"��"));}
	const char* name_do(bool blank=false)/*�̰�*/const{return (name_type?(blank?"�� ":"��"):(blank?"�� ":"��"));}
	const char* name_and(bool blank=false)/*����*/const{return (name_type?(blank?"�� ":"��"):(blank?"�� ":"��"));}
	const char* name_by(bool blank=false)/*���η�*/const{return (name_type?(blank?"���� ":"����"):(blank?"�� ":"��"));}
	name_infor(monster_index name_key){this->name_key=name_key;}
	name_infor(string name_ = "����", bool name_type_ = true){name=name_;name_type=name_type_;}
	name_infor(const name_infor &t){name=t.name;name_type=t.name_type;}
	string getName(){return name;};
};

struct attack_infor
{
	int damage;
	int max_damage;
	int accuracy;
	unit *order;
	parent_type p_type;
	attack_type type;
	name_infor name;
	attack_infor(int damage_,int max_damage_, int accuracy_, unit *order_, parent_type p_type_, attack_type type_,name_infor name_){damage=damage_;max_damage=max_damage_;accuracy=accuracy_;order=order_;p_type=p_type_;type=type_;name = name_;}
};

struct beam_infor
{
	int damage;
	int max_damage;
	int accuracy;
	unit *order;
	parent_type p_type;
	int length; //�����Ÿ�
	int penetrate; //�����
	beam_type type1; //���� Ÿ��. ������, ������Ʈ���
	attack_type type2; //���� �Ӽ�
	name_infor name;
	beam_infor(int damage_, int max_damage_, int accuracy_, unit *order_, parent_type p_type_, int length_, int penetrate_, beam_type type1_, attack_type type2_,name_infor name_){damage=damage_;max_damage=max_damage_;accuracy=accuracy_;length=length_;penetrate=penetrate_;order=order_;p_type=p_type_;type1=type1_;type2=type2_;name = name_;}
};


class unit	
{	
public:
	coord_def position;

	unit():position(0,0){};
	virtual const name_infor* GetName()=0;
	virtual const string* GetNameString()=0;
	virtual int GetHp()=0;
	virtual int GetMaxHp()=0;	
	virtual int GetAttack(bool max_)=0;
	virtual int GetHit()=0;
	virtual coord_def GetPrevPos()=0;
	virtual void SetX(int x_){position.x = x_;};
	virtual void SetY(int y_){position.y = y_;};
	virtual void SetXY(int x_, int y_){position.set(x_,y_);};
	virtual void SetXY(coord_def pos_){SetXY(pos_.x,pos_.y);};
	//virtual int move(short_move x_mov, short_move y_mov)=0;
	//Ư����ġ�� �̵��ϱ�
	//virtual int move(const coord_def &c)=0;
	virtual bool offsetmove(const coord_def &c) = 0; //offset�� ���� ��ȭ������ ���� �̵��Ѵ�. ������ true�� ���� false�� ���� ���
	virtual bool isLive()=0;
	virtual bool isFly()=0;
	virtual bool isSwim()=0;
	virtual bool damage(attack_infor &a, bool perfect_)=0;
	virtual bool isplayer()=0;
	virtual bool isView()=0;
	virtual bool isView(const monster* monster_info)=0;
	virtual bool isYourShight()=0;
	virtual bool SetPoisonReason(parent_type type_)=0;
	virtual bool SetPoison(int poison_, int max_, bool strong_)=0;
	virtual bool SetTele(int tele_)=0;
	virtual bool SetMight(int might_)=0;
	virtual bool SetClever(int clever_)=0;
	virtual bool SetAgility(int agility_)=0;
	virtual bool SetHaste(int haste_)=0;
	virtual bool SetConfuse(int confuse_, bool strong_ = false)=0;
	virtual bool SetSlow(int slow_)=0;
	virtual bool SetFrozen(int frozen_)=0;
	virtual bool SetCharm(int charm_){return false;};
	virtual bool SetElec(int elec_)=0;
	virtual bool SetParalyse(int paralyse_)=0;
	virtual bool SetLevitation(int levitation_)=0;
	virtual bool SetGlow(int glow_, bool no_speak = false)=0;
	virtual bool SetGraze(int graze_)=0;
	virtual bool SetSilence(int silence_, int silence_range_)=0;
	virtual bool SetSick(int sick_)=0;
	virtual bool SetVeiling(int veiling_, int value_)=0;
	virtual bool SetInvisible(int invisible_)=0;	
	virtual bool SetMute(int mute_){return false;};
	virtual bool SetSaved(int saved_)=0;
	virtual bool SetSwift(int swift_)=0;
	virtual bool SetFear(int fear_){return false;};
	virtual bool SetMindReading(int mind_){return false;};
	virtual bool SetTogleInvisible(bool off_){return false;};
	virtual bool SetGhost(int ghost_)=0;
	virtual bool SetLunatic(int s_lunatic_)=0;
	virtual bool SetMirror(int mirror_){return false;};
	virtual bool SetParadox(int s_paradox_){return false;};
	virtual bool SetCommunication(int s_communication_){return false;};
	virtual bool SetExhausted(int s_exhausted_){return false;};
	virtual bool SetStasis(int s_stasis_){return false;};
	virtual bool SetForceStrong(bool force_, int turn_, bool speak_){return false;};
	virtual bool SetSleep(int value_){ return false; };
	bool PositionSwap(unit *other){
		coord_def temp_ = position;
		SetXY(other->position);
		other->SetXY(temp_);	
		return true;
	};

	virtual int PlusTimeDelay(int delay_)
	{ //���� �������ִ� timedelay�� �ø���
		//���ʹ� timedelay�� �þ�� �׸�ŭ �ൿ�� �� �ְ�
		//�÷��̾�� timedelay�� �þ�� �׸�ŭ �ൿ���Ϸ����°Ͱ� ����
		//����� ������ timedelay�� ������ �� �ְ� ��
		return 0;
	}
	virtual bool AttackedTarget(unit *order_){return false;};//���ݹ޴´�.
	virtual bool LostTarget(){return false;};//Ÿ���� �Ҵ´�.
	virtual void CheckSightNewTarget(){return;};//���ο� Ÿ���� ã�´�.


	virtual int GetId()=0;
	virtual int GetMapId()=0; //�÷��̾� -2�� (�߿�!)
	virtual int GetLevel()=0;
	virtual int GetInvisible() = 0;
	virtual int GetSaved() = 0;
	virtual int GetParadox(){return 0;}
	virtual bool isSaveSummoner(unit* order){return false;};
	virtual int GetWalkDelay(){return 10;};
	virtual bool GetMindReading(){return false;};
	virtual int GetExhausted(){return 0;};
	virtual char getAsciiDot() = 0;
	 


	virtual int GetResist() = 0;
	bool CalcuateMR(int power);
	virtual int GetPoisonResist()=0;
	virtual float GetFireResist(bool cloud_ = false)=0;
	virtual float GetColdResist(bool cloud_ = false)=0;
	virtual float GetElecResist(bool cloud_ = false)=0;
	virtual bool GetCloudResist(){return false;};
	virtual bool Blink(int time_)=0;
	virtual bool Tele_check(bool preiden_, bool ctele_){return true;};
	virtual attack_weapon_type GetAttackType()=0;
	virtual int HpUpDown(int value_,damage_reason reason, unit *order_ = false)=0;
	virtual bool isEnemyUnit(unit* unit_info){return unit_info->isUserAlly();};
	virtual bool isEnemyMonster(const monster* monster_info)=0;
	virtual bool isUserAlly() const {return false;}
	virtual bool isPassedBullet(unit* order){return false;}; //�ش� ���� �� ĳ���Ϳ��� ���� ��������.
	virtual parent_type GetParentType() = 0;
	virtual bool isSightnonblocked(coord_def c) = 0;//���̴� �� ��ġ�� ������ ���ݰ�������?(������)
};


#endif // __UNIT_H__