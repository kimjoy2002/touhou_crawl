//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: monster.h
//
// 내용: 몹의 클래스 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MONSTER_H__
#define  __MONSTER_H__

#include "unit.h"
#include "texture.h"
#include "FSM.h"
#include "Astar.h"
#include "monster_texture.h"
#include "summon.h"

struct item_infor;

struct spell
{
	int num;
	int percent; //percent/100 가 확률
	spell(int num_=0, int percent_=0):num(num_),percent(percent_){}
};



class monster: public unit
{
public:
	int map_id;
	int id;
	int level;
	int exper;
	name_infor name;
	textures *image;
	int hp;
	int hp_recov;
	int max_hp;
	coord_def prev_position;
	coord_def first_position;
	bool prev_sight;
	int ac;
	int ev;
	int atk[3];
	attack_type atk_type[3];
	name_infor atk_name[3];
	int flag;
	int resist;
	int sense;

	int s_poison;
	parent_type poison_reason;
	int s_tele;
	int s_might;
	int s_clever;
	int s_haste;
	int s_confuse;
	int s_slow;
	int s_frozen;
	int s_ally;
	int s_elec;
	int s_paralyse;
	int s_glow;
	int s_graze;
	int s_silence;
	int s_silence_range;
	int s_sick;
	int s_veiling;
	int s_value_veiling;
	int s_invisible;
	bool s_saved;
	int s_mute;
	int s_catch;
	int s_ghost;
	int s_fear;
	int s_mind_reading;
	int s_lunatic;
	int s_neutrality;
	int s_communication;
	int s_exhausted;
	bool force_strong; //강화/약화(위력 2배 1/2배)
	int force_turn; //강화/약화턴
	int s_changed; //둔갑시간. 시간이 지나면 너구리로 돌아온다.
	int s_invincibility;
	int debuf_boost;
	int summon_time;
	parent_type summon_parent;

	
	int poison_resist;
	int fire_resist;
	int ice_resist;
	int elec_resist;
	int confuse_resist;
	int wind_resist;


	int time_delay; //누적되어있는시간
	int speed; //행동시간 (누적되어있는시간/행동시간=행동턴)
	int memory_time; //기억력
	bool first_contact; //이 몬스터를 처음 보았다.
	int strong; //강하기

	int delay_turn; //다른층으로 도망친 턴. 이 턴만큼 회복등등...

	list<coord_def> will_move;
	unit* target;
	int temp_target_map_id; //로딩시 임시로 타겟팅의 아이디를 저장한다.(몬스터 로딩은 선후를 알 수 없으니!)
	coord_def target_pos;
	int direction;

	summon_info sm_info;


	FSMclass state;
	list<spell> spell_lists;
	bool random_spell; //이 몬스터가 고정된 스펠셋을 들고있지않다.
	
	vector<item_infor> item_lists; //드랍하는 아이템목록


	monster();
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	void ReTarget();
	void init();
	bool SetMonster(int map_num_, int map_id_, int id_, int flag_, int time_, coord_def position_, bool init_ = true);
	bool ChangeMonster(int id_, int flag_);
	void FirstContact();
	coord_def GetPrevPos(){return prev_position;};
	coord_def GetFirstPos() { return first_position; };
	int GetHp(){return hp;};
	int GetMaxHp(){return max_hp;};
	void TurnSave();//다른층으로 도망쳤다.
	void TurnLoad();//다른층에서 도망왔다.
	void SetX(int x_);
	void SetY(int y_);
	void SetXY(int x_, int y_);
	void SetXY(coord_def pos_);
	char getAsciiDot();
	void LevelUpdown(int level_, float hp_ = 6.0f, float atk_ = 2.0f);
	void FoundTarget(unit* unit_, int time_);
	int FoundTime();
	void CheckSightNewTarget();
	bool ReturnEnemy();
	const name_infor* GetName();
	const string* GetNameString();
	bool isLive(){return (hp>0);}
	bool isFly();
	bool isSwim();
	bool simple_draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_);
	bool draw(LPD3DXSPRITE pSprite, ID3DXFont* pfont, float x_, float y_);
	bool smartmove(short_move x_mov, short_move y_mov, int num_); //아군이 자리를 잡을 수 있게 길을 비켜주는 인공지능
	int move(short_move x_mov, short_move y_mov, bool only_move);
	int move(const coord_def &c, bool only_move);
	bool offsetmove(const coord_def &c);
	bool OpenDoor(const coord_def &c);
	int longmove();
	int atkmove(int is_sight, bool only_move=false);
	bool isCanMove();
	bool isHaveSpell(spell_list sp);
	int MoveToPos(coord_def pos_, bool only_move);
	bool isView(); //당신이 볼 수 있는지.
	bool isView(const monster* monster_info); //몬스터가 이 몹을 볼 수 있는지.
	bool CanSpeak(); //이 몬스터가 말할 수 있는지(사일런스에 의해서 안막혔는지)
	int calculate_damage(attack_type &type_, int atk, int max_atk, int back_stab);
	void print_damage_message(attack_infor &a, bool back_stab);
	void print_no_damage_message(attack_infor &a);
	bool damage(attack_infor &a, bool perfect_ = false);
	bool dead(parent_type reason_, bool message_, bool remove_ = false); //remove는 증발시키기(아예 경험치나 관련도 없이)
	int action(int delay_);
	void sightcheck(bool is_sight_); //시야에 들어오면 덤빈다.
	void special_action(int delay_, bool smoke_);
	bool SetPoisonReason(parent_type type_);
	bool SetPoison(int poison_, int max_, bool strong_);
	int HpRecoverDelay();
	bool HpRecover(int trun_ = 1);
	int HpUpDown(int value_,damage_reason reason, unit *order_ = false);
	void SetStrong(int strong_) {strong = strong_;};
	bool SetTele(int tele_);
	bool SetMight(int might_);
	bool SetClever(int clever_);
	bool SetAgility(int agility_);
	bool SetHaste(int haste_);
	bool SetConfuse(int confuse_, bool strong_=false);
	bool SetSlow(int slow_);
	bool SetFrozen(int frozen_);
	bool SetCharm(int charm_);
	bool SetElec(int elec_);
	bool SetParalyse(int paralyse_);
	bool SetLevitation(int levitation_);
	bool SetGlow(int glow_, bool no_speak = false);
	bool SetGraze(int graze_);
	bool SetSilence(int silence_, int silence_range_);
	bool SetSick(int sick_);
	bool SetVeiling(int veiling_, int value_);
	bool SetInvisible(int invisible_);
	bool SetMute(int mute_);
	bool SetGhost(int ghost_);
	bool SetSaved(int saved_);
	bool SetSwift(int swift_);
	bool SetFear(int fear_);
	bool SetMindReading(int mind_);
	bool SetLunatic(int lunatic_);
	bool SetNeutrality(int s_neutrality_);
	bool SetCommunication(int s_communication_);
	bool SetExhausted(int s_exhausted_);
	bool SetForceStrong(bool force_, int turn_, bool speak_);
	bool SetInvincibility(int s_invincibility, bool speak_);
	bool SetDebufPlus(int s_debuf_);
	bool SetSleep(int s_sleep_);
	int PlusTimeDelay(int delay_)
	{
		time_delay += delay_;
		return time_delay;
	}
	bool AttackedTarget(unit *order_);
	bool LostTarget()
	{
		state.StateTransition(MSI_LOST);
		return true;
	};
	int GetInvisible();
	bool Blink(int time_);
	bool Teleport();
	int GetResist();
	int GetDetect();
	bool you_detect(); //당신을 감지했는지
	bool isYourShight();
	bool isEnemyUnit(unit* unit_info);
	bool isEnemyMonster(const monster* monster_info); //이 몹이 적인지
	bool isPassedBullet(unit* order);//이 공격이 관통되는지
	bool isAllyMonster(const monster* monster_info); //이 몹이 아군인지
	bool isUserAlly() const; //유저에 친밀한가?
	bool isSightnonblocked(coord_def c); //여기까지 공격이 닿는지
	bool isMonsterSight(coord_def c, boolean okina = false);//해당 위치에 "몬스터"의 시야에 들어왔는가?
	bool CanChase();
	parent_type GetParentType();
	bool isUnique();
	attack_weapon_type GetAttackType();
	int GetSpeed();
	int GetAttack(bool max_);
	int GetAttack(int num_, bool max_);
	int GetHit();
	int GetEv();
	int GetSaved(){return s_saved;};
	int SetStrong() { return strong; };
	bool isSaveSummoner(unit* order);
	int GetWalkDelay(){return GetSpeed();};
	bool GetMindReading(){return (s_mind_reading!=0);};
	int GetExhausted(){return s_exhausted;};
	int GetPoisonResist(){return poison_resist;};
	float GetFireResist(bool cloud_ = false);
	float GetColdResist(bool cloud_ = false);
	float GetElecResist(bool cloud_ = false);
	bool GetCloudResist();
	bool isSimpleState(monster_state_simple state_);
	monster_state_simple GetSimpleState();
	bool GetStateString(monster_state_simple state_, char* string_);
	bool isplayer(){return false;};
	int GetId(){return id;};
	int GetMapId(){return map_id;};
	int GetLevel(){return level;};
};


class shadow
{
public:
	textures *image;
	coord_def position;
	shadow_type type;
	string name;
	shadow():image(NULL),position(),type(SWT_MONSTER),name()
	{}
	shadow(const coord_def &c, textures *t, shadow_type type_= SWT_MONSTER, string name_ = "")
	{position=c;image=t;type=type_;name=name_;};
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
};


class effect
{
public:
	textures *image;
	coord_def position;
	bool over_sight;
	effect():image(NULL),position(),over_sight(false){}
	effect(const coord_def &c, textures *t, bool over_sight_):image(t),position(c),over_sight(over_sight_){};
};

#endif // __MONSTER_H__