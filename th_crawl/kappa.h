//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: kappa.h
//
// 내용: 캇파 협동조합
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __KAPPA_H__
#define  __KAPPA_H__

#include "common.h"

using namespace std;

class monster;
class item;
class unit;

const int KAPPA_MACHINE_POWER_BONUS = 5; //입교시 증가하는 최대 전력
const int KAPPA_TRUST_DECAY_TURN = 2000; //이 턴마다 신뢰도가 1씩 떨어진다.
const int KAPPA_SCRAP_PERCENT = 10; //적이 고철을 흩뿌릴 확률
const int KAPPA_INTRANET_GIFT_TIME = 50; //인트라넷 접속 주기(선물카운트)
const int KAPPA_SELL_USED_TURN1 = 100; //약간 고물
const int KAPPA_SELL_USED_TURN2 = 300;
const int KAPPA_SELL_USED_TURN3 = 500; //중고품
const int KAPPA_PUNISH_MISFIRE_PERCENT = 20;

int kappa_machine_power_bonus();
void kappa_set_power_bonus(bool on_);
bool kappa_is_overdrive();
bool kappa_is_blackout();
bool kappa_machine_misfire();
void kappa_turn();
void kappa_abandon();

bool kappa_scatter_scrap(monster* mon_);
void kappa_pickup_scrap(int num_, bool speak_);
void kappa_add_trust(int value_);

int kappa_sell_trust(int used_turn_);
bool kappa_sell_item(list<item>::iterator it);
bool kappa_punish();

bool kappa_open_intranet(bool speak_);
void kappa_first_intranet();
void kappa_close_intranet(bool speak_);

bool skill_kappa_disassemble(int power, bool short_, unit* order, coord_def target);
bool skill_kappa_intranet(int power, bool short_, unit* order, coord_def target);
bool skill_kappa_charge(int power, bool short_, unit* order, coord_def target);
bool skill_kappa_overdrive(int power, bool short_, unit* order, coord_def target);

#endif // __KAPPA_H__
