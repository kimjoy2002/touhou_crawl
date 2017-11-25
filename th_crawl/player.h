//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: player.h
//
// 내용: player클래스 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __PLAYER_H__
#define  __PLAYER_H__


#include "unit.h"
#include "texture.h"
#include "item.h"
#include "skill.h"


extern class monster;
extern class beam_iterator;
extern class tribe_property;
extern class action_class;
extern enum tribe_proper_type;
extern enum ALCHEMY_LIST;
extern enum dump_action_type;
extern enum amulet_type;

enum stat_up //스탯버프는 따로 두지않는다. 겹칠 가능성을 위해
{
	BUFFSTAT_STR=0,
	BUFFSTAT_INT,
	BUFFSTAT_DEX,
	BUFFSTAT_HP,
	BUFFSTAT_MP,
	BUFFSTAT_POW,
	BUFFSTAT_AC,
	BUFFSTAT_SH,
	BUFFSTAT_EV,
	BUFFSTAT_ACC,
	BUFFSTAT_DAM,
	BUFFSTAT_RF,
	BUFFSTAT_RC,
	BUFFSTAT_MAX
};

enum buff_type //겹쳐져선 안되는 버프들
{
	BUFF_DUPLE=-1,
	BUFF_TEST=0,
	BUFF_YUKARI,
	BUFF_SUWAKO,
	BUFF_MINORIKO_RF,
	BUFF_MINORIKO_RC,
	BUFF_AUTUMN_RF,
	BUFF_MAX
};
enum action_type
{
	ACTT_NONE,
	ACTT_WALK,
	ACTT_MAX
};

struct buff_class
{
	stat_up stat;
	buff_type id;//-1이 아니면 겹칠경우 겹쳐지지않는다. 
	int value;
	int turn;
	buff_class():stat(BUFFSTAT_STR),id(BUFF_DUPLE),value(0),turn(1){};
	buff_class(stat_up stat_, buff_type id_, int value_, int turn_):stat(stat_),id(id_),value(value_),turn(turn_){};

};

struct punish_struct
{
	int number;
	int turn;
	bool punish;	
	punish_struct():number(0),turn(0),punish(false){};
	punish_struct(int number_, int turn_, bool punish_):number(number_),turn(turn_),punish(punish_){};
};


struct lilly_ally
{
	int map_id;
	int floor;
	int level;
	int exp;
	int id;
	int name;
	int personality;
	int cooldown; //부활시간
	
	lilly_ally():map_id(0),floor(0),level(0),exp(0),id(0),name(0),personality(0),cooldown(0){};
};

struct current_max
{
	int value;
	int maxi;
	current_max(int _value, int _maxi) :value(_value), maxi(_maxi) {};
};


class players: public unit
{
public:
	coord_def prev_position;

	name_infor name;
	name_infor char_name;
	name_infor user_name;
	textures *image;
	tribe_type tribe;
	job_type job;

	int hp;
	int prev_hp[2];
	int max_hp;
	int hp_recov;
	int mp;
	int prev_mp[2];
	int max_mp;
	int mp_recov;
	int power;
	int power_decre;
	int level;
	int exper;
	int exper_recovery;
	int exper_aptit;
	int skill_exper;
	current_max system_exp;
	int ac;
	int ev;
	int sh;
	int real_ac;
	int bonus_ac;
	int real_ev;
	int bonus_ev;
	int real_sh;
	int bonus_sh;
	int s_str;
	int s_dex;
	int s_int;
	int m_str;
	int m_dex;
	int m_int;
	int acc_plus;
	int dam_plus;
	int as_penalty;//아머와 실드 패널티
	int magic_resist;
	int tension_gauge; //텐션 게이지
	bool tension_turn; //이번턴에 이미 텐션을 체크했는가






	bool search;
	coord_def search_pos;
	
	list<buff_class> buff_list;
	list<item> item_list;
	vector<tribe_property> property_vector;
	vector<action_class> action_vector;

	float item_weight;
	float max_item_weight;
	action_type prev_action;

	item* equipment[ET_LAST]; //장착 아이템

	int time_delay; //행동시간
	int speed; //이동속도
	int turn; //턴
	int real_turn; //턴
	int prev_real_turn; //턴
	bool player_move;//플레이어의 움직임이 있었다.
	int explore_map; //탐험한 거리

	char final_item; //마지막에 주운 템
	int final_num; //마지막에 주운 템의 수량
	

	//int hunger;
	//int hunger_per_turn;

	stack<coord_def> will_move; //움직이는 경로

	int auto_pickup;

	interupt_type inter;


	//여기부터 여러상태들
	int s_poison;
	int s_tele;
	int s_might;
	int s_clever;
	int s_agility;
	int s_haste;
	int s_confuse;
	int s_slow;
	int s_frozen;
	int s_elec;
	int s_paralyse;
	int s_levitation;
	int s_glow;
	int s_graze;
	int s_silence;
	int s_silence_range;
	int s_sick;
	int s_veiling;
	int s_value_veiling;
	int s_invisible;
	int s_swift;
	int s_mana_regen;
	int s_superman;
	int s_spellcard;
	int s_slaying;
	int s_autumn;
	int s_wind;
	int s_knife_collect;
	int s_drunken;
	int s_catch;
	int s_ghost;
	int s_dimension;
	int s_timestep;
	int s_mirror;	
	int s_lunatic;
	int s_paradox;
	int s_trans_panalty;
	int s_the_world;
	int s_mana_delay;
	int s_stat_boost;
	int s_stat_boost_value;
	int s_eirin_poison;
	int s_eirin_poison_time;
	int s_exhausted;
	int s_stasis;
	bool force_strong; //강화/약화(위력 2배 1/2배)
	int force_turn; //강화/약화턴
	int s_unluck;
	int s_super_graze;
	int s_none_move;
	int s_night_sight;
	int s_night_sight_turn;
	int s_sleep;

	ALCHEMY_LIST alchemy_buff;
	int alchemy_time;




	int teleport_curse;
	int magician_bonus;
	int poison_resist;
	int fire_resist;
	int ice_resist;
	int elec_resist;
	int confuse_resist;
	int invisible_view;
	int power_keep;
	bool togle_invisible; //스펠카드로만 얻는 투명
	int battle_count; //전투중이다. 공격하면 100부터 시작

	int uniden_poison_resist;
	int uniden_fire_resist;
	int uniden_ice_resist;
	int uniden_elec_resist;
	int uniden_confuse_resist;
	int uniden_invisible_view;
	int uniden_power_keep;


	int total_skill_exp;
	skill_exp_infor skill[SKT_MAX];
	int bonus_skill[SKT_MAX];

	int MemorizeSpell[52];
	int remainSpellPoiont;
	int currentSpellNum;

	int MemorizeSkill[52];
	int MemorizeSkill_num[52];
	int currentSkillNum;

	god_type god;
	int piety;
	int gift_count;
	punish_struct punish[GT_LAST];
	int god_turn;
	int god_value[GT_LAST][5];//이건 신에 따라 적절한 수치로 이용
	lilly_ally lilly_allys[5]; //릴리의 동료
	int suwako_meet; //스와코를 믿은적이 있는지
	int half_youkai[4];//반요 변이 수치
	int rune[RUNE_MAX];

	bool sight_reset;
	int target;
	item *throw_weapon;

	attack_infor *dead_order;
	damage_reason dead_reason;

	players();
	~players();
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	bool isLive();
	bool isFly(){return s_levitation!=0;}
	bool isSwim();
	coord_def GetPrevPos(){return prev_position;};
	void SetX(int x_);
	void SetY(int y_);
	void SetXY(int x_, int y_);
	void SetXY(coord_def pos_);
	void maybeAction();
	coord_def GetDisplayPos();
	int move(short_move x_mov, short_move y_mov);
	int move(const coord_def &c);
	bool offsetmove(const coord_def &c);
	void youAttack(unit* unit_); //누군가를 공격하다.
	int OpenDoor(const coord_def &c, bool no_turn);
	bool GetStatPanalty(){return s_str<=0 ||s_dex<=0 || s_int<=0;};
	void CalcuHP();
	int GetHp(){return hp;};
	int GetMaxHp(){return max_hp;};
	int GetDisplayEv();
	int GetDisplayAc();
	int GetDisplaySh();
	int GetAttack(bool max);
	int GetHit();
	int GetAtkDelay();
	//int GetArmourPanlty();
	//int GetShieldPanlty();
	int ReSetASPanlty(); //새로운 아머실드 패널티를 지정
	int GetPenaltyMinus(int level_);
	int GetThrowAttack(const item* it, bool max_);
	int GetThrowHit(const item* it);
	attack_weapon_type GetAttackType();
	int GetThrowDelay(item_type type_, bool random_ = true);
	int GetSpellDelay();
	int GetNormalDelay();
	int GetWalkDelay();
	int GetSpellPower(int s1_, int s2_, int s3_);
	int GetSpellSuccess(int spell_);
	int GetSpellHungry(int spell_);
	int GetStealth();
	int GetBuffOk(stat_up stat_);//해당스탯 버프가 있으면 true리턴. 보통 display용
	//hunger_type GetHunger();
	int HpRecoverDelay(int delay_ = 0);
	interupt_type HpRecover(int delay_);
	int HpUpDown(int value_,damage_reason reason, unit *order_ = false);
	int MpRecoverDelay(int delay_ = 0,bool set_ = false);
	interupt_type MpRecover(int delay_);
	int MpUpDown(int value_);
	int AcUpDown(int value_, int bonus_);
	int EvUpDown(int value_, int bonus_);
	int ShUpDown(int value_, int bonus_);
	int MRUpDown(int value_)
	{
		magic_resist+=value_;
		return magic_resist;
	}
	int CheckTension();
	void UpDownBuff(stat_up stat_, int value_);
	void doingActionDump(dump_action_type type_, string name_);
	int PowDecreaseDelay(int delay_ = 0);
	interupt_type PowDecrease(int delay_);
	int PowUpDown(int value_, bool big_ = false);
	bool StatUpDown(int value_, stat_type stat_, bool temp_ = false);
	bool ResistUpDown(int value_, resist_type resist_);
	bool UnidenResistUpDown(int value_, resist_type resist_);
	void BonusSkillUpDown(int skill_, int value_);
	//interupt_type HungerApply(int hunger_ = 0);
	int calculate_damage(attack_type &type_, int atk, int max_atk);
	void print_damage_message(attack_infor &a, bool damaged_);
	void print_no_damage_message(attack_infor &a);
	bool damage(attack_infor &a, bool perfect_ = false);
	bool GetExp(int exper_, bool speak_ = true);
	void FairyRevive(bool speak_);
	int getAmuletPercent();
	void ExpRecovery(int exper_);
	void CheckPunish(int delay_);
	int GetNeedExp(int level_);
	bool GiveSkillExp(skill_type skill_, int exp_, bool speak_ = true);
	bool SkillTraining(skill_type skill_, int percent_); // (1/percent_)%
	bool SkillTraining(bool speak);
	bool SetPoisonReason(parent_type type_){return false;};
	bool SetPoison(int poison_, int max_, bool strong_);
	bool SetTele(int tele_);
	bool SetMight(int might_);
	bool SetClever(int clever_);
	bool SetAgility(int agility_);
	bool SetHaste(int haste_);
	bool SetConfuse(int confuse_, bool strong_=false);
	bool SetSlow(int slow_);
	bool SetFrozen(int frozen_);
	bool SetElec(int elec_);
	bool SetParalyse(int paralyse_);
	bool SetLevitation(int levitation_);
	bool SetGlow(int glow_);
	bool SetGraze(int graze_);
	bool SetSilence(int silence_, int silence_range_);
	bool SetSick(int sick_);
	bool SetVeiling(int veiling_, int value_);
	bool SetInvisible(int invisible_);
	bool SetSaved(int saved){return true;};
	bool SetTogleInvisible(bool off_);
	bool SetBattleCount(int count_);
	void ChangeBattleCount(bool on_); //배틀카운터가 켜지거나 꺼질때 처리 
	bool SetSwift(int swift_);
	bool SetManaRegen(int mana_regen_);
	bool SetSuperMan(int superman_);
	bool SetSlaying(int slaying_);
	bool SetAutumn(int autumn_);
	bool SetWind(int s_wind_);
	bool SetDrunken(int s_drunken_);
	bool SetLunatic(int s_lunatic_);
	bool SetCatch(monster* unit_);
	bool SetGhost(int ghost_);
	bool SetDimension(int dimension_);
	bool SetTimeStep(int timestep_);
	bool SetMirror(int mirror_);
	bool SetParadox(int s_paradox_);
	bool SetTransPanalty(int s_trans_panalty_);
	bool SetTheWorld(int s_the_world_);
	bool SetManaDelay(int s_mana_delay_);
	bool SetKnifeCollect(int s_knife_collect_);
	bool SetAlchemyBuff(ALCHEMY_LIST buff_, int time_);
	bool SetSpellcard(int s_spellcard_){s_spellcard= s_spellcard_; return true;};
	bool SetBuff(stat_up stat_, buff_type id_, int value_, int turn_); //true 리턴은 기존의 버프가 있어서 덮어씌웠다.
	bool SetProperty(tribe_proper_type type_, int value_);
	bool SetStatBoost(int sdi_, int value_);
	bool SetEirinHeal(int value_, bool punish_);
	bool SetExhausted(int s_exhausted_);
	bool SetStasis(int s_stasis_);
	bool SetForceStrong(bool force_, int turn_, bool speak_);
	bool SetUnluck(int s_unluck_);
	bool SetSuperGraze(int s_super_graze_);
	bool SetNoneMove(int s_none_move_); 
	bool SetNightSight(int value_, int turn_, bool stong_);
	bool SetSleep(int value_);

	int GetInvisible();
	int GetSaved(){return true;};
	int GetParadox(){return s_paradox;}
	int GetResist();
	int GetSpellcard(){return s_spellcard;};
	int GetProperty(tribe_proper_type type_);
	int GetExhausted(){return s_exhausted;};
	int GetSuperGraze() { return s_super_graze; };
	int GetNoneMove() { return s_none_move; };
	bool GetPunish(god_type god_);
	int GetSkillLevel(int skill_, bool bonus_);
	int DeleteProperty(tribe_proper_type type_);
	bool Teleport();
	bool Blink(int time_);
	bool control_blink(const coord_def &c);
	bool Tele_check(bool preiden_, bool ctele_);
	void LevelUp(bool speak_);
	const name_infor* GetName(){return &name;};
	const string* GetNameString(){return &(name.name);};
	const name_infor* GetCharName(){return &char_name;};
	const string* GetCharNameString(){return &(char_name.name);};
	list<item>::iterator GetThrowIter();
	vector<monster>::iterator GetTargetIter();
	interupt_type resetLOS(bool speak_ = true);
	void MakeLOSPattern();
	interupt_type TurnEnd(bool *item_delete_ = NULL); //0은 딱히일없고, 1이상부터 인터럽트
	bool TraningStealth();
	int additem(item *t, bool speak_ = true);
	bool DeleteItem(const list<item>::iterator it, int num_ = 0);
	bool Eat(char id_);
	bool Drink(char id_);
	bool Evoke(char id_);
	bool Read(char id_);
	bool Memorize(int spell, bool immediately = false);
	int Ability(int skill_, bool god_, bool unset_, int immediately = 0);
	bool Belief(god_type god_, int piety_, bool speak_=true);
	bool StepUpDownPiety(int level_);
	bool PietyUpDown(int piety_, bool absolutely_ = false);
	bool GiftCount(int value_);
	bool PunishUpDown(int punish_, god_type god_ = GT_NONE, bool absolutely_ = false);
	bool Throw(list<item>::iterator it, coord_def target_pos_, bool short_, beam_iterator& beam);
	item* GetItem(char id_);
	list<item>::iterator GetItemIterator(char id_);
	void auto_equip_iden();
	bool isGrazeAmulet();
	void resetAmuletPercent(amulet_type type_);
	bool equip(char id_, equip_type type_, bool speak_ = true);
	bool equip(list<item>::iterator &it, equip_type type_, bool speak_ = true);
	bool equiparmor(char id_, bool speak_ = true);
	bool equipjewerly(char id_);
	bool unequip(char id_);
	bool unequip(list<item>::iterator it, equip_type type_);
	bool possibleunequip(list<item>::iterator it); //장착하고있다면 장비벗기. 장착안해도 실패처리는 아님
	int isequip(list<item>::iterator it);
	int isequip(item* item_);
	int haveGoal();
	int haveOrb();
	bool isImpossibeEquip(equip_type type_, bool massage_);
	bool unequip(equip_type type_, bool force_=false);
	bool unequiparmor(char id_);
	bool unequipjewerly(char id_);
	void equip_stat_change(item *it, equip_type where_, bool equip_bool);
	int GetDelay(){int temp_ = time_delay;time_delay = 0;return temp_;};
	int GetId(){return -1;};
	int GetMapId(){return -2;};
	int GetLevel(){return level;};
	bool isplayer(){return true;};
	int GetPoisonResist(){return poison_resist;};
	float GetFireResist(bool cloud_ = false);
	float GetColdResist(bool cloud_ = false);
	float GetElecResist(bool cloud_ = false);
	bool GetCloudResist();
	void burstCloud(int kind_, int rate_);
	bool isEnemyMonster(const monster* monster_info);
	bool isUserAlly() const {return true;}
	bool isMemorizeSpell(int spell_);
	bool CanMemorizeSpell(int spell_);
	bool isView(){return true;};
	bool isView(const monster* monster_info);
	bool isYourShight(){return true;};	
	bool isSightnonblocked(coord_def c);//보이는 이 위치가 실제로 공격가능한지?(유리벽)
	parent_type GetParentType();
	interupt_type SetInter(interupt_type inter_);

};
void GameOver();

extern players you;

int Move(const coord_def &c); //이동한다.
void Long_Move(const coord_def &c); //길게 이동한다.
void auto_battle();//자동전투
void auto_Move(); //자동으로 이동한다.
void long_rest();

void Search(); //주변을 탐색한다.
void Wide_Search(); //넓은범위를 탐색한다.

void PickUp(); //줍기
void PickUpAll(list<item>::iterator it);
void PickUpSelect(list<item>::iterator it, int num);
bool PickUpNum(list<item>::iterator it, int num, bool no_delay);
int isPick(const item *t); //1 리턴이 ok. 마이너스가 안됨
void iteminfor(bool gameover = false);
void iteminfor_pick();
void turn_skip();
void escape();
void iteminfor_discard();
void fast_discard();
void Eatting();
void Drinking();
//void Spelllcard_Declare();
void Spelllcard_Evoke();
void Reading();
void Equip_Weapon(); //무기장착
void Equip_Armor(); //방어구장착
void Unequip_Armor(); //방어구해제
void Equip_Jewelry(); //장신구장착
void Unequip_Jewelry();
void Close_door();
void Open_door();
void Stair_move(bool down);
void view_log();
void skill_view();
void stat_view();
void Help_Show();
void rune_Show();
void Iden_Show();
void Weapon_Show();
void Armour_Show();
void Amulet_Show();
void Simple_State_Show();
void Experience_Show();
//bool Eat_Power();
void dungeonView();
void run_spell();
void shout();
void auto_pick_onoff(bool auto_);

void wiz_mode();
void save_mode();

bool poison_percent(int value);
int poison_damage(int value);

#endif // __PLAYER_H__