//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: spellcard.cpp
//
// 내용: 스펠카드 선언
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
#include "key.h"

int GetDebufPower(spell_list skill, int power_);//디버프의 파워

extern int map_effect;
bool MachineFlagCheck(machine_type skill, skill_flag flag);
int MachineUsePower(machine_type skill, bool max_);
int MachineLength(machine_type skill);
bool UseMachine(machine_type kind, bool short_, int power, coord_def &target);


bool evoke_machine(machine_type kind, int power, bool fail_, bool iden_, bool auto_)
{
	if(you.s_confuse)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_CONFUSE_WARNING),true,false,false,CL_normal);
		return false;
	}
	if (you.s_pure_turn && you.s_pure >= 10 && !you.GetProperty(TPT_PURE_SYSTEM))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_PURITY_PENALTY_MACHINE), true, false, false, CL_normal);
		return false;
	}


	if(!MachineFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		while(true)
		{
			SetSpellSight(MachineLength(kind),MachineFlagCheck(kind, S_FLAG_RECT)?2:1);
			beam_iterator beam(you.position,you.position);
			projectile_infor infor(MachineLength(kind),false,MachineFlagCheck(kind, S_FLAG_SMITE),-2,false);
			auto it = you.item_list.end();
			if(int short_ = Common_Throw(it, you.GetTargetIter(), beam, &infor, MachineLength(kind), MachineSector(kind), auto_))
			{
				if(fail_)
				{
					SetSpellSight(0,0);
					return true;
				}
				unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
				you.SetBattleCount(30);
				if(unit_)
					you.youAttack(unit_);
				if(UseMachine(kind, short_ == 2, power, you.search_pos))
				{
					you.PowUpDown(-1* MachineUsePower(kind,false),true);
					SetSpellSight(0,0);
					return true;
				}
				SetSpellSight(0,0);
				if(iden_)
					return false;
				MoreWait();
			}
			else
			{
				SetSpellSight(0,0);
				if(iden_)
					return false;
				bool cancel_ = ynPrompt(LOC_SYSTEM_MACHINE_CANCEL_WASTE_ASK, LOC_EMPTYSTRING, CL_help, false,false,true,true);
				enterlog();
				if(cancel_)
					return true;
			}
			auto_ = false;
		}
	}			
	else if(MachineFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		if(fail_)
			return true;
		if(UseMachine(kind, false, power, you.position))
		{
			you.PowUpDown(-1* MachineUsePower(kind,false),true);
			return true;
		}
	}
	return false;
}


void createMachine(int goodbad, int select_, item_infor* t)
{
	//셀렉트는나중에 속성 스펠카드로..
	//나중에 속성에 따른 스펠카드, 발동 선언에 맞춘 세기 정도 가치 정도 다 잘 바꿔보자
	//지금은 구현이 목적
	t->type = ITM_MACHINE;
	t->value2 = select_!=-1?(machine_type)select_:randA(MCH_MAX-1);
	t->value1 = IsInstallableMachine((machine_type)t->value2) ? 1 :
		MachineMaxCharge((machine_type)t->value2)*rand_float(0.2f,1);
	t->value3 = 0;
	t->value4 = 0;
	t->value5 = 0;
	t->value6 = 0;
	t->is_pile = false;
	t->can_throw = false;
	t->item_tag.clear();
	t->item_tag.push_back(LOC_SYSTEM_TAG_EVOKE);
	t->item_tag.push_back(LOC_SYSTEM_TAG_MACHINE);
	t->image = MachineItemImage((machine_type)t->value2,
		t->value1 > 0 || IsInstallableMachine((machine_type)t->value2));
	t->name = name_infor(LOC_SYSTEM_MACHINE_ITEM);
	t->weight = 2.0f;
	t->value = 200;
}


float MachineSector(machine_type skill)
{
	switch(skill)
	{
	case MCH_FLAMETHROWER:
		return 0.4f;
	case MCH_LARGE_FAN:
		return 0.4f;
	default:
		return 0;
	}
}


bool MachineFlagCheck(machine_type skill, skill_flag flag)
{
	switch(skill)
	{

	case MCH_FLAMETHROWER:
	case MCH_FREEZE_SPRAYER:
	case MCH_LARGE_FAN:
		return (S_FLAG_PENETRATE) & flag;
	case MCH_DRILL:
		return (0) & flag;
	case MCH_OPTICAL_CAMOUFLAGE:
		return (S_FLAG_IMMEDIATELY) & flag;
	case MCH_SCRAP_LAUNCHER:
		return (0)& flag;
	case MCH_SUN_LAMP:
		return (S_FLAG_IMMEDIATELY)& flag;
	default:
		return false;
	}
}


LOCALIZATION_ENUM_KEY MachineName(machine_type skill)
{
	switch(skill)
	{
	case MCH_OPTICAL_CAMOUFLAGE: //월-투명+회피
		return LOC_SYSTEM_MACHINE_OPTICAL_CAMOUFLAGE;
	case MCH_FLAMETHROWER: //화-구름생성
		return LOC_SYSTEM_MACHINE_FLAMETHROWER;
	case MCH_FREEZE_SPRAYER: //수-관통형볼트
		return LOC_SYSTEM_MACHINE_FREEZE_SPRAYER;
	case MCH_LARGE_FAN: //목-밀쳐내기
		return LOC_SYSTEM_MACHINE_LARGE_FAN;
	case MCH_SCRAP_LAUNCHER://금-
		return LOC_SYSTEM_MACHINE_SCRAP_LAUNCHER;
	case MCH_DRILL: //토-벽파괴
		return LOC_SYSTEM_MACHINE_DRILL;
	case MCH_SUN_LAMP://일-주변 몬스터 혼란+투명해제
		return LOC_SYSTEM_MACHINE_SUN_LAMP;
	case MCH_PUNCH:
		return LOC_SYSTEM_MACHINE_PUNCH;
	case MCH_BARRIER_GENERATOR:
		return LOC_SYSTEM_MACHINE_DEFENSE_FRAGMENT;
	case MCH_PHOTON_TORPEDO:
		return LOC_SYSTEM_MACHINE_PHOTON_TORPEDO;
	case MCH_OI_SOUND_SYSTEM:
		return LOC_SYSTEM_MACHINE_OI_SOUND_SYSTEM;
	case MCH_ARMOUR_ASSIST:
		return LOC_SYSTEM_MACHINE_ARMOUR_ASSIST;
	case MCH_AUX_BATTERY:
		return LOC_SYSTEM_MACHINE_AUX_BATTERY;
	case MCH_BLASTER:
		return LOC_SYSTEM_MACHINE_BLASTER;
	case MCH_FLASH_SHIELD:
		return LOC_SYSTEM_MACHINE_FLASH_SHIELD;
	case MCH_COUNTER_WAVE:
		return LOC_SYSTEM_MACHINE_COUNTER_WAVE;
	case MCH_VIBRATION:
		return LOC_SYSTEM_MACHINE_VIBRATION;
	case MCH_ARC_SHOT:
		return LOC_SYSTEM_MACHINE_ARC_SHOT;
	case MCH_WEAPON_PREHEATER:
		return LOC_SYSTEM_MACHINE_WEAPON_PREHEATER;
	case MCH_OFFSET_SHOT:
		return LOC_SYSTEM_MACHINE_OFFSET_SHOT;
	case MCH_EMERGENCY_BARRIER:
		return LOC_SYSTEM_MACHINE_EMERGENCY_BARRIER;
	default:
		return LOC_NONE;
	}
}

LOCALIZATION_ENUM_KEY MachineDescription(machine_type skill)
{
	switch(skill)
	{
	case MCH_FLAMETHROWER:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_FIRE;
	case MCH_FREEZE_SPRAYER:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_ICE;
	case MCH_DRILL:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_EARTH;
	case MCH_LARGE_FAN:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_AIR;
	case MCH_OPTICAL_CAMOUFLAGE:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_INVISIBLE;
	case MCH_SCRAP_LAUNCHER:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_METAL;
	case MCH_SUN_LAMP:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_SUN;
	case MCH_PUNCH:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_PUNCH;
	case MCH_BARRIER_GENERATOR:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_DEFENSE_FRAGMENT;
	case MCH_PHOTON_TORPEDO:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_PHOTON_TORPEDO;
	case MCH_OI_SOUND_SYSTEM:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_OI_SOUND_SYSTEM;
	case MCH_ARMOUR_ASSIST:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_ARMOUR_ASSIST;
	case MCH_AUX_BATTERY:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_AUX_BATTERY;
	case MCH_BLASTER:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_BLASTER;
	case MCH_FLASH_SHIELD:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_FLASH_SHIELD;
	case MCH_COUNTER_WAVE:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_COUNTER_WAVE;
	case MCH_VIBRATION:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_VIBRATION;
	case MCH_ARC_SHOT:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_ARC_SHOT;
	case MCH_WEAPON_PREHEATER:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_WEAPON_PREHEATER;
	case MCH_OFFSET_SHOT:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_OFFSET_SHOT;
	case MCH_EMERGENCY_BARRIER:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_EMERGENCY_BARRIER;
	default:
		return LOC_SYSTEM_ITEM_DESCRIPTION_MACHINE_BUG;
	}
}

textures* MachineItemImage(machine_type machine_, bool charged_)
{
	if(machine_ < 0 || machine_ >= MCH_MAX)
		return &img_item_machine_kind[0];
	return charged_ ? &img_item_machine_kind[machine_] : &img_item_machine_empty_kind[machine_];
}

int MachineMaxCharge(machine_type skill)
{
	switch(skill)
	{
	case MCH_FLAMETHROWER:
		return 9;
	case MCH_FREEZE_SPRAYER:
		return 15;
	case MCH_DRILL:
		return 15;
	case MCH_LARGE_FAN:
		return 9;
	case MCH_OPTICAL_CAMOUFLAGE:
		return 6;
	case MCH_SCRAP_LAUNCHER:
		return 15;
	case MCH_SUN_LAMP:
		return 9;
	default:
		return IsInstallableMachine(skill) ? 1 : 0;
	}
}

static const vector<installed_machine_info>& InstalledMachineInfoList()
{
	static const unsigned int weapon_slot_ = 1u<<ET_WEAPON;
	static const unsigned int all_armour_slots_ =
		(1u<<ET_ARMOR)|(1u<<ET_SHIELD)|(1u<<ET_HELMET)|
		(1u<<ET_CLOAK)|(1u<<ET_GLOVE)|(1u<<ET_BOOTS);
	static const unsigned int all_equipment_slots_ = weapon_slot_|all_armour_slots_;
	//{설치 타입, 기계 종류, 전력, 최대 성능 기계공학 레벨, 설치 가능 부위, 옵션 이름, 효과 설명}
	static const vector<installed_machine_info> list_ = {
		{IMT_PUNCH,MCH_PUNCH,2,8,all_armour_slots_,LOC_SYSTEM_MACHINE_OPTION_PUNCH,LOC_SYSTEM_MACHINE_EFFECT_PUNCH},
		{IMT_OPTICAL_CAMOUFLAGE,MCH_OPTICAL_CAMOUFLAGE,12,0,1u<<ET_CLOAK,LOC_SYSTEM_MACHINE_OPTION_OPTICAL_CAMOUFLAGE,LOC_SYSTEM_MACHINE_EFFECT_OPTICAL_CAMOUFLAGE},
		{IMT_BARRIER_GENERATOR,MCH_BARRIER_GENERATOR,3,0,all_armour_slots_,LOC_SYSTEM_MACHINE_OPTION_DEFENSE_FRAGMENT,LOC_SYSTEM_MACHINE_EFFECT_BARRIER_GENERATOR},
		{IMT_PHOTON_TORPEDO,MCH_PHOTON_TORPEDO,7,20,all_armour_slots_,LOC_SYSTEM_MACHINE_OPTION_PHOTON_TORPEDO,LOC_SYSTEM_MACHINE_EFFECT_PHOTON_TORPEDO},
		{IMT_OI_SOUND_SYSTEM,MCH_OI_SOUND_SYSTEM,13,27,all_equipment_slots_,LOC_SYSTEM_MACHINE_OPTION_OI_SOUND_SYSTEM,LOC_SYSTEM_MACHINE_EFFECT_OI_SOUND_SYSTEM},
		{IMT_ARMOUR_ASSIST,MCH_ARMOUR_ASSIST,9,0,(1u<<ET_ARMOR)|(1u<<ET_SHIELD),LOC_SYSTEM_MACHINE_OPTION_ARMOUR_ASSIST,LOC_SYSTEM_MACHINE_EFFECT_ARMOUR_ASSIST},
		{IMT_AUX_BATTERY,MCH_AUX_BATTERY,0,0,all_equipment_slots_,LOC_SYSTEM_MACHINE_OPTION_AUX_BATTERY,LOC_SYSTEM_MACHINE_EFFECT_AUX_BATTERY},
		{IMT_BLASTER,MCH_BLASTER,7,0,(1u<<ET_ARMOR)|(1u<<ET_BOOTS),LOC_SYSTEM_MACHINE_OPTION_BLASTER,LOC_SYSTEM_MACHINE_EFFECT_BLASTER},
		{IMT_FLASH_SHIELD,MCH_FLASH_SHIELD,6,15,1u<<ET_SHIELD,LOC_SYSTEM_MACHINE_OPTION_FLASH_SHIELD,LOC_SYSTEM_MACHINE_EFFECT_FLASH_SHIELD},
		{IMT_COUNTER_WAVE,MCH_COUNTER_WAVE,9,18,1u<<ET_SHIELD,LOC_SYSTEM_MACHINE_OPTION_COUNTER_WAVE,LOC_SYSTEM_MACHINE_EFFECT_COUNTER_WAVE},
		{IMT_VIBRATION,MCH_VIBRATION,3,0,weapon_slot_,LOC_SYSTEM_MACHINE_OPTION_VIBRATION,LOC_SYSTEM_MACHINE_EFFECT_VIBRATION},
		{IMT_ARC_SHOT,MCH_ARC_SHOT,12,27,weapon_slot_,LOC_SYSTEM_MACHINE_OPTION_ARC_SHOT,LOC_SYSTEM_MACHINE_EFFECT_ARC_SHOT},
		{IMT_WEAPON_PREHEATER,MCH_WEAPON_PREHEATER,18,0,weapon_slot_,LOC_SYSTEM_MACHINE_OPTION_WEAPON_PREHEATER,LOC_SYSTEM_MACHINE_EFFECT_WEAPON_PREHEATER},
		{IMT_OFFSET_SHOT,MCH_OFFSET_SHOT,10,20,weapon_slot_,LOC_SYSTEM_MACHINE_OPTION_OFFSET_SHOT,LOC_SYSTEM_MACHINE_EFFECT_OFFSET_SHOT},
		{IMT_EMERGENCY_BARRIER,MCH_EMERGENCY_BARRIER,15,27,1u<<ET_ARMOR,LOC_SYSTEM_MACHINE_OPTION_EMERGENCY_BARRIER,LOC_SYSTEM_MACHINE_EFFECT_EMERGENCY_BARRIER}
	};
	return list_;
}

bool IsInstallableMachine(machine_type skill)
{
	return MachineToInstalledType(skill) != IMT_NONE;
}

installed_machine_type MachineToInstalledType(machine_type skill)
{
	for(const installed_machine_info& info_ : InstalledMachineInfoList())
		if(info_.source_type == skill)
			return info_.installed_type;
	return IMT_NONE;
}

const installed_machine_info* GetInstalledMachineInfo(installed_machine_type machine_)
{
	for(const installed_machine_info& info_ : InstalledMachineInfoList())
		if(info_.installed_type == machine_)
			return &info_;
	return nullptr;
}

LOCALIZATION_ENUM_KEY InstalledMachineOptionName(installed_machine_type machine_)
{
	const installed_machine_info* info_ = GetInstalledMachineInfo(machine_);
	return info_ ? info_->option_name : LOC_NONE;
}

LOCALIZATION_ENUM_KEY InstalledMachineEffectName(installed_machine_type machine_)
{
	const installed_machine_info* info_ = GetInstalledMachineInfo(machine_);
	return info_ ? info_->effect_name : LOC_NONE;
}

int InstalledMachinePower(installed_machine_type machine_)
{
	const installed_machine_info* info_ = GetInstalledMachineInfo(machine_);
	return info_ ? info_->power : 0;
}

int InstalledMachineMaxLevel(installed_machine_type machine_)
{
	const installed_machine_info* info_ = GetInstalledMachineInfo(machine_);
	return info_ ? info_->max_engineering_level : 0;
}

machine_type RandomBulletMachine()
{
	//설치형이 아닌 탄환형 기계들
	vector<machine_type> list_;
	for(int i = 0; i < MCH_MAX; i++)
		if(!IsInstallableMachine((machine_type)i))
			list_.push_back((machine_type)i);
	return list_[randA(list_.size()-1)];
}

static int InstalledMachineDropPower(const installed_machine_info& info_)
{
	//드랍 등급을 정할때 쓰는 전력. 실제 전력과 다르게 취급할 기계만 따로 처리
	switch(info_.installed_type)
	{
	case IMT_AUX_BATTERY:
		return 7; //보조배터리는 중급(7~12)으로 취급
	default:
		return info_.power;
	}
}

machine_type RandomInstalledMachineByPower(int min_power_, int max_power_)
{
	vector<machine_type> list_;
	for(const installed_machine_info& info_ : InstalledMachineInfoList())
	{
		int power_ = InstalledMachineDropPower(info_);
		if(power_ >= min_power_ && power_ <= max_power_)
			list_.push_back(info_.source_type);
	}
	if(list_.empty())
		return RandomBulletMachine();
	return list_[randA(list_.size()-1)];
}

bool IsMachineInstallSlot(int slot_)
{
	return slot_ == ET_WEAPON || (slot_ >= ET_ARMOR && slot_ < ET_ARMOR_END);
}

bool CanInstallMachineAt(installed_machine_type machine_, equip_type slot_)
{
	if(!IsMachineInstallSlot(slot_))
		return false;
	const installed_machine_info* info_ = GetInstalledMachineInfo(machine_);
	return info_ && (info_->equip_mask & (1u<<slot_)) != 0;
}

void equipMachine(installed_machine_type machine_, item* item_)
{
	switch(machine_)
	{
	case IMT_BARRIER_GENERATOR:
		you.AcUpDown(0,5);
		break;
	case IMT_ARMOUR_ASSIST:
	case IMT_AUX_BATTERY:
		you.ReSetASPanlty();
		break;
	case IMT_OFFSET_SHOT:
	case IMT_COUNTER_WAVE:
		you.ShUpDown(0,you.GetMachineItemSh(machine_,item_));
		break;
	case IMT_PUNCH:
	case IMT_OPTICAL_CAMOUFLAGE:
	case IMT_PHOTON_TORPEDO:
	case IMT_OI_SOUND_SYSTEM:
	case IMT_BLASTER:
	case IMT_FLASH_SHIELD:
	case IMT_VIBRATION:
	case IMT_ARC_SHOT:
	case IMT_WEAPON_PREHEATER:
	case IMT_EMERGENCY_BARRIER:
	case IMT_NONE:
	default:
		break;
	}
}

void unequipMachine(installed_machine_type machine_, item* item_)
{
	switch(machine_)
	{
	case IMT_BARRIER_GENERATOR:
		you.AcUpDown(0,-5);
		break;
	case IMT_ARMOUR_ASSIST:
	case IMT_AUX_BATTERY:
		you.ReSetASPanlty();
		break;
	case IMT_OFFSET_SHOT:
	case IMT_COUNTER_WAVE:
		you.ShUpDown(0,-you.GetMachineItemSh(machine_,item_));
		break;
	case IMT_PUNCH:
	case IMT_OPTICAL_CAMOUFLAGE:
	case IMT_PHOTON_TORPEDO:
	case IMT_OI_SOUND_SYSTEM:
	case IMT_BLASTER:
	case IMT_FLASH_SHIELD:
	case IMT_VIBRATION:
	case IMT_ARC_SHOT:
	case IMT_WEAPON_PREHEATER:
	case IMT_EMERGENCY_BARRIER:
	case IMT_NONE:
	default:
		break;
	}
}

static LOCALIZATION_ENUM_KEY MachineSlotName(equip_type slot_)
{
	switch(slot_)
	{
	case ET_WEAPON: return LOC_SYSTEM_MACHINE_SLOT_WEAPON;
	case ET_ARMOR: return LOC_SYSTEM_MACHINE_SLOT_BODY;
	case ET_SHIELD: return LOC_SYSTEM_MACHINE_SLOT_SHIELD;
	case ET_HELMET: return LOC_SYSTEM_MACHINE_SLOT_HEAD;
	case ET_CLOAK: return LOC_SYSTEM_MACHINE_SLOT_CLOAK;
	case ET_GLOVE: return LOC_SYSTEM_MACHINE_SLOT_GLOVE;
	case ET_BOOTS: return LOC_SYSTEM_MACHINE_SLOT_BOOTS;
	default: return LOC_NONE;
	}
}

string InstalledMachineSlotsString(installed_machine_type machine_, const string& lang)
{
	string result_;
	for(int slot_ = ET_FIRST; slot_ < ET_ARMOR_END; ++slot_)
	{
		if(!CanInstallMachineAt(machine_,(equip_type)slot_))
			continue;
		if(!result_.empty())
			result_ += ", ";
		result_ += LocalzationManager::locString(lang,MachineSlotName((equip_type)slot_));
	}
	return result_;
}

int MachineUsePower(machine_type skill, bool max_)
{
	switch(skill)
	{

	case MCH_FLAMETHROWER:
	case MCH_FREEZE_SPRAYER:
	case MCH_DRILL:
	case MCH_LARGE_FAN:
	case MCH_OPTICAL_CAMOUFLAGE:
	case MCH_SCRAP_LAUNCHER:
	case MCH_SUN_LAMP:
		return 0;
	default:
		return false;
	}
}


int MachineLength(machine_type skill)
{
	switch(skill)
	{

	case MCH_FLAMETHROWER:
	case MCH_FREEZE_SPRAYER:
	case MCH_DRILL:
		return 7;
	case MCH_LARGE_FAN:
		return 6;
	case MCH_OPTICAL_CAMOUFLAGE:
	case MCH_SUN_LAMP:
		return 0;
	case MCH_SCRAP_LAUNCHER:
		return 6;
	default:
		return false;
	}
}





bool UseMachine(machine_type kind, bool short_, int power, coord_def &target)
{
	if(target == you.position && !MachineFlagCheck(kind,S_FLAG_SEIF) && !MachineFlagCheck(kind, S_FLAG_IMMEDIATELY))
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_ASK_SUICIDE),true,false,false,CL_small_danger);	
		return false;
	}


	switch (kind)
	{
	case MCH_FLAMETHROWER:
	{
		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam))
		{
			PlaySE("fire");
			beam_infor temp_infor(0, 0, 99, &you, you.GetParentType(), MachineLength(kind), 8, BMT_PENETRATE, ATT_THROW_FIRE, name_infor(LOC_SYSTEM_ATT_V_FIRE));
			ThrowSector(0, beam, temp_infor, GetSpellSector(SPL_FIRE_SPREAD), [&](coord_def c_) {
				if (you.isSightnonblocked(c_))
				{
					if(randA(60)+ power > 20) {
						env[current_level].MakeSmoke(c_, img_fog_fire, SMT_FIRE, rand_int(1, 5) + power / 15, 0, &you);
					}
				}
			}, false);
			return true;
		}
		return false;
	}
	case MCH_FREEZE_SPRAYER:
	{
		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam)) {
			beam_infor temp_infor(randC(3, 6 + power / 6), 3 * (6 + power / 6), 16, &you, you.GetParentType(), MachineLength(kind), 8, BMT_PENETRATE, ATT_THROW_COLD, name_infor(LOC_SYSTEM_ATT_COLD));
			if (short_)
				temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));

			for (int i = 0; i < (you.GetParadox() ? 2 : 1); i++) {
				PlaySE("cold");
				throwtanmac(22, beam, temp_infor, NULL);
			}
			you.SetParadox(0);
			return true;
		}
		return false;
	}
	case MCH_DRILL:
	{

		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam)) {

			//beam_infor temp_infor(0,0,15,order,order->GetParentType(),length_,1,BMT_NORMAL,ATT_THROW_NONE_MASSAGE,name_infor(LOC_SYSTEM_ATT_FIREBALL));
			//coord_def pos = throwtanmac(16,beam,temp_infor,NULL);

			beam_infor temp_infor(randC(2, 4 + power / 8), 2 * (4 + power / 8), 10, &you, you.GetParentType(), MachineLength(kind), 1, BMT_WALL, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_V_EARTH_SHOT));
			if (short_)
				temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));

			for (int k = 0; k < (you.GetParadox() ? 2 : 1); k++)
			{
				PlaySE("shoot");
				coord_def pos = throwtanmac(26, beam, temp_infor, NULL);
				if (env[current_level].dgtile[pos.x][pos.y].isEffectibleDrill())
				{
					PlaySE("stone");
					for (int i = -1; i <= 1; i++)
						for (int j = -1; j <= 1; j++)
						{
							coord_def effect_pos(pos.x + i, pos.y + j);
							if(effect_pos.x >= 0 && effect_pos.x < DG_MAX_X && effect_pos.y >= 0 && effect_pos.y < DG_MAX_Y)
								env[current_level].MakeEffect(effect_pos, &img_blast[1], false);
						}
					for (int i = -1; i <= 1; i++)
					{
						for (int j = -1; j <= 1; j++)
						{
							coord_def effect_pos(pos.x + i, pos.y + j);
							if(effect_pos.x < 0 || effect_pos.x >= DG_MAX_X || effect_pos.y < 0 || effect_pos.y >= DG_MAX_Y)
								continue;
							if (env[current_level].isMove(effect_pos, true))
							{
								if (env[current_level].isInSight(effect_pos))
								{
									if (unit* hit_ = env[current_level].isMonsterPos(effect_pos.x, effect_pos.y))
									{
										attack_infor temp_att(randC(3, 5 + power / 8), 3 * (5 + power / 8), 99, &you, you.GetParentType(), ATT_NORMAL_BLAST, name_infor(LOC_SYSTEM_ATT_V_EARTH_FRAG));
										hit_->damage(temp_att, true);
									}
								}
							}
							else
							{
								if(i == 0 && j == 0 && env[current_level].dgtile[effect_pos.x][effect_pos.y].isEffectibleDrill()) {
									env[current_level].changeTile(effect_pos, env[current_level].base_floor);
								}
								else if (env[current_level].dgtile[effect_pos.x][effect_pos.y].isBreakable())
									env[current_level].changeTile(effect_pos, env[current_level].base_floor);
							}
						}
					}
					env[current_level].MakeNoise(target, 8, NULL);
				}
				else if (!env[current_level].dgtile[pos.x][pos.y].isMove(true, true, false))
				{
					LocalzationManager::printLogWithKey(LOC_SYSTEM_MACHINE_DRILL_CANT_BREAK,true,false,false,CL_normal,
						 PlaceHolderHelper(dungeon_tile_tribe_type_string[env[current_level].dgtile[pos.x][pos.y].tile]));
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
	case MCH_LARGE_FAN:
	{
		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam)) {
			beam_infor temp_infor(randC(3, 3 + power / 12), 3 * (3 + power / 12), 99, &you, you.GetParentType(), MachineLength(kind), 8, BMT_NORMAL, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_V_AIR));


			for (int i = 0; i < (you.GetParadox() ? 2 : 1); i++)
			{
				PlaySE("wind");
				ThrowSector(25, beam, temp_infor, MachineSector(MCH_LARGE_FAN), [&](coord_def c_) {
					if (unit* unit_ = env[current_level].isMonsterPos(c_.x, c_.y))
					{
						if (!unit_->isImmobile() && you.isSightnonblocked(c_))
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
								LocalzationManager::printLogWithKey(LOC_SYSTEM_MACHINE_LARGE_FAN_EFFECT,false,false,false,CL_normal,
									PlaceHolderHelper(unit_->GetName()->getName()));
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
	case MCH_OPTICAL_CAMOUFLAGE:
		you.SetInvisible(rand_int(20, 30) + randA(power / 4));
		return true;
	case MCH_SCRAP_LAUNCHER:
	{
		beam_iterator beam(you.position, target);
		if (CheckThrowPath(you.position, target, beam)) {
			beam_infor temp_infor(randC(1, 13 + power / 6), 1 * (13 + power / 6), 14, &you, you.GetParentType(), MachineLength(kind), 1, BMT_NORMAL, ATT_THROW_NORMAL, name_infor(LOC_SYSTEM_ATT_V_METAL));
			if (short_)
				temp_infor.length = ceil(GetPositionGap(you.position.x, you.position.y, target.x, target.y));

			for (int i = 0; i < (you.GetParadox() ? 6 : 3); i++) {
				PlaySE("shoot");
				throwtanmac(45, beam, temp_infor, NULL);
			}
			you.SetParadox(0);
			return true;
		}
		return false;
	}
	case MCH_SUN_LAMP:
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_MACHINE_SUN_LAMP_SET), true, false, false, CL_warning);
		map_effect = 2;
		Sleep(500);
		map_effect = 0;
		for(vector<monster>::iterator it = env[current_level].mon_vector.begin(); it!=env[current_level].mon_vector.end(); it++)
		{	
			if(it->isLive() && env[current_level].isInSight(it->position) && you.isSightnonblocked(it->position))
			{
				int power_ = power;
				if (it->id == MON_REMILIA || it->id == MON_FLAN || it->id == MON_FLAN_BUNSIN || it->id == MON_FLAN_AFTERIMAGE ||
					it->id == MON_VAMPIER_BAT) {
					int damage_ = 10 + power_ / 12;
					attack_infor attack_infor_(randC(3, damage_), 3 * (damage_), 99, &you, you.GetParentType(), ATT_SUN_BLAST, name_infor(LOC_SYSTEM_ATT_SUN));
					it->damage(attack_infor_, true);
					power_ += 100;
				}
				if (it->flag & M_FLAG_INANIMATE)
				{
				}
				else if(it->CalcuateMR(power_))
				{
					int turn_ = rand_int(3, 8) + randA(power_ / 5);
					if(it->isUnique()) {
						turn_ = max(1,turn_ / 3);
					}
					it->SetConfuse(turn_);
				}
				else if(it->isYourShight())
				{
				}
				it->SetGlow(rand_int(10, 20) + randA(power_ / 5), true);
				it->AttackedTarget(&you);			
			}
		}
		if (you.tribe == TRI_VAMPIRE) {
			int damage_ = 8 + power / 12;
			attack_infor attack_infor_(randC(3, damage_), 3 * (damage_), 99, &you, you.GetParentType(), ATT_SUN_BLAST, name_infor(LOC_SYSTEM_ATT_SUN));
			you.damage(attack_infor_, true);
		}
		return true;
	}
	default:
		return false;
	}
	return false;
}
