//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: spellcard.h
//
// 내용: 스펠카드 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SPELLCARD_H__
#define  __SPELLCARD_H__


#include "player.h"

struct item_infor;
enum skill_flag;

struct installed_machine_info
{
	installed_machine_type installed_type;
	machine_type source_type;
	int power;
	int max_engineering_level;
	unsigned int equip_mask;
	LOCALIZATION_ENUM_KEY option_name;
	LOCALIZATION_ENUM_KEY effect_name;
};

//
bool evoke_machine(machine_type kind, int power, bool fail_, bool iden_, bool auto_);//fail_은 무조건 실패 iden_은 미식별상태에서 조준실패시 true리턴

float MachineSector(machine_type skill);
void createMachine(int goodbad, int select_, item_infor* t);
LOCALIZATION_ENUM_KEY MachineName(machine_type skill);
int MachineMaxCharge(machine_type skill);
bool IsInstallableMachine(machine_type skill);
installed_machine_type MachineToInstalledType(machine_type skill);
const installed_machine_info* GetInstalledMachineInfo(installed_machine_type machine_);
LOCALIZATION_ENUM_KEY InstalledMachineOptionName(installed_machine_type machine_);
LOCALIZATION_ENUM_KEY InstalledMachineEffectName(installed_machine_type machine_);
int InstalledMachinePower(installed_machine_type machine_);
int InstalledMachineMaxLevel(installed_machine_type machine_);
machine_type RandomBulletMachine();
machine_type RandomInstalledMachineByPower(int min_power_, int max_power_);
bool IsMachineInstallSlot(int slot_);
bool CanInstallMachineAt(installed_machine_type machine_, equip_type slot_);
string InstalledMachineSlotsString(installed_machine_type machine_, const string& lang);
void equipMachine(installed_machine_type machine_, item* item_);
void unequipMachine(installed_machine_type machine_, item* item_);
LOCALIZATION_ENUM_KEY MachineDescription(machine_type machine_);
textures* MachineItemImage(machine_type machine_, bool charged_);

bool base_bomb(int damage, int max_damage, int size, attack_type type, unit* order, name_infor bomb_name, coord_def target);
bool skill_lightning(int power, unit* order, coord_def *start, int& direc, int count);

bool MachineFlagCheck(machine_type skill, skill_flag flag);

#endif // __SPELLCARD_H__
