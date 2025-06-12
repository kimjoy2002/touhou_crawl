//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: keiki.cpp
//
// 내용: 케이키 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "keiki.h"
#include "key.h"
#include "environment.h"
#include "joypad.h"
#include "scroll.h"
#include "enum.h"
#include "mon_infor.h"
#include "skill_use.h"
#include "beam.h"
#include "god.h"
#include "note.h"
#include "potion.h"
#include "rect.h"
#include "alchemy.h"
#include "weapon.h"
#include "event.h"
#include "soundmanager.h"

//왼손
//HANIWA_A_SWORD, HANIWA_A_SPEAR, HANIWA_A_BOW, HANIWA_A_SHIELD2, HANIWA_A_TANMAC, HANIWA_A_HEAL
//오른손
//HANIWA_A_DOUBLE_SWORD, HANIWA_A_SPEAR, HANIWA_A_BOW, HANIWA_A_SHIELD1

haniwa_abil haniwa_abil_list[HANIWA_A_MAX] = {
	{LOC_SYSTEM_HANIWA_A_SWORD_NAME,LOC_SYSTEM_HANIWA_A_SWORD_INFO,HANIWA_T_COMBAT,30,10,false,{},{},{ HANIWA_A_SPEAR, HANIWA_A_BOW, HANIWA_A_SHIELD2, HANIWA_A_TANMAC, HANIWA_A_HEAL}},
	{LOC_SYSTEM_HANIWA_A_DOUBLE_SWORD_NAME,LOC_SYSTEM_HANIWA_A_DOUBLE_SWORD_INFO,HANIWA_T_COMBAT,20,20,false,{HANIWA_A_SWORD},{},{HANIWA_A_SPEAR, HANIWA_A_BOW, HANIWA_A_SHIELD1}},
	{LOC_SYSTEM_HANIWA_A_SPEAR_NAME,LOC_SYSTEM_HANIWA_A_SPEAR_INFO,HANIWA_T_COMBAT,30,10,false,{},{},{HANIWA_A_SWORD, HANIWA_A_BOW, HANIWA_A_SHIELD1, HANIWA_A_TANMAC, HANIWA_A_HEAL}},
	{LOC_SYSTEM_HANIWA_A_BOW_NAME,LOC_SYSTEM_HANIWA_A_BOW_INFO,HANIWA_T_COMBAT,30,10,false,{},{},{HANIWA_A_SWORD, HANIWA_A_SPEAR, HANIWA_A_SHIELD1, HANIWA_A_TANMAC, HANIWA_A_HEAL}},
	{LOC_SYSTEM_HANIWA_A_SHIELD1_NAME,LOC_SYSTEM_HANIWA_A_SHIELD1_INFO,HANIWA_T_COMBAT,30,10,false,{},{},{HANIWA_A_DOUBLE_SWORD, HANIWA_A_SPEAR, HANIWA_A_BOW}},
	{LOC_SYSTEM_HANIWA_A_SHIELD2_NAME,LOC_SYSTEM_HANIWA_A_SHIELD2_INFO,HANIWA_T_COMBAT,60,20,false,{HANIWA_A_SHIELD1},{},{}},
	{LOC_SYSTEM_HANIWA_A_EXPLOSION_NAME,LOC_SYSTEM_HANIWA_A_EXPLOSION_INFO,HANIWA_T_COMBAT,15,10,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_ARMY1_NAME,LOC_SYSTEM_HANIWA_A_ARMY1_INFO,HANIWA_T_COMBAT,60,5,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_ARMY2_NAME,LOC_SYSTEM_HANIWA_A_ARMY2_INFO,HANIWA_T_COMBAT,60,15,false,{HANIWA_A_ARMY1},{},{}},
	{LOC_SYSTEM_HANIWA_A_CLEAVE_NAME,LOC_SYSTEM_HANIWA_A_CLEAVE_INFO,HANIWA_T_COMBAT,90,5,true,{},{},{HANIWA_A_SPEAR, HANIWA_A_BOW}},
	{LOC_SYSTEM_HANIWA_A_FIRE_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_FIRE_ENCHANT_INFO,HANIWA_T_COMBAT,20,5,false,{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW},{HANIWA_A_COLD_ENCHANT,HANIWA_A_ELEC_ENCHANT,HANIWA_A_POISON_ENCHANT}},
	{LOC_SYSTEM_HANIWA_A_COLD_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_COLD_ENCHANT_INFO,HANIWA_T_COMBAT,20,5,false,{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW},{HANIWA_A_FIRE_ENCHANT,HANIWA_A_ELEC_ENCHANT,HANIWA_A_POISON_ENCHANT}},
	{LOC_SYSTEM_HANIWA_A_ELEC_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_ELEC_ENCHANT_INFO,HANIWA_T_COMBAT,20,5,false,{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW},{HANIWA_A_FIRE_ENCHANT,HANIWA_A_COLD_ENCHANT,HANIWA_A_POISON_ENCHANT}},
	{LOC_SYSTEM_HANIWA_A_POISON_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_POISON_ENCHANT_INFO,HANIWA_T_COMBAT,20,5,false,{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW},{HANIWA_A_FIRE_ENCHANT,HANIWA_A_COLD_ENCHANT,HANIWA_A_ELEC_ENCHANT}},
	{LOC_SYSTEM_HANIWA_A_SLOW_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_SLOW_ENCHANT_INFO,HANIWA_T_COMBAT,40,20,false,{HANIWA_A_POISON_ENCHANT},{},{}},
	{LOC_SYSTEM_HANIWA_A_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_TANMAC_INFO,HANIWA_T_MAGIC,30,30,false,{},{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW}},
	{LOC_SYSTEM_HANIWA_A_FIRE_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_FIRE_TANMAC_INFO,HANIWA_T_MAGIC,20,5,false,{},{HANIWA_A_TANMAC},{HANIWA_A_COLD_TANMAC,HANIWA_A_ELEC_TANMAC}},
	{LOC_SYSTEM_HANIWA_A_COLD_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_COLD_TANMAC_INFO,HANIWA_T_MAGIC,20,5,false,{},{HANIWA_A_TANMAC},{HANIWA_A_FIRE_TANMAC,HANIWA_A_ELEC_TANMAC}},
	{LOC_SYSTEM_HANIWA_A_ELEC_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_ELEC_TANMAC_INFO,HANIWA_T_MAGIC,20,5,false,{},{HANIWA_A_TANMAC},{HANIWA_A_FIRE_TANMAC,HANIWA_A_COLD_TANMAC}},
	{LOC_SYSTEM_HANIWA_A_MIDDLE_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_MIDDLE_TANMAC_INFO,HANIWA_T_MAGIC,30,20,false,{HANIWA_A_TANMAC},{},{}},
	{LOC_SYSTEM_HANIWA_A_BIG_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_BIG_TANMAC_INFO,HANIWA_T_MAGIC,30,20,false,{HANIWA_A_MIDDLE_TANMAC},{},{}},
	{LOC_SYSTEM_HANIWA_A_BURST_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_BURST_TANMAC_INFO,HANIWA_T_MAGIC,30,10,false,{},{HANIWA_A_TANMAC},{HANIWA_A_PENTAN}},
	{LOC_SYSTEM_HANIWA_A_BLINK_NAME,LOC_SYSTEM_HANIWA_A_BLINK_INFO,HANIWA_T_MAGIC,20,10,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_SLOW_NAME,LOC_SYSTEM_HANIWA_A_SLOW_INFO,HANIWA_T_MAGIC,30,10,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_CONFUSE_NAME,LOC_SYSTEM_HANIWA_A_CONFUSE_INFO,HANIWA_T_MAGIC,30,20,false,{HANIWA_A_SLOW},{},{}},
	{LOC_SYSTEM_HANIWA_A_PENTAN_NAME,LOC_SYSTEM_HANIWA_A_PENTAN_INFO,HANIWA_T_MAGIC,30,10,false,{},{HANIWA_A_TANMAC},{HANIWA_A_BURST_TANMAC}},
	{LOC_SYSTEM_HANIWA_A_HASTE_NAME,LOC_SYSTEM_HANIWA_A_HASTE_INFO,HANIWA_T_MAGIC,60,10,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_MAGICIAN_NAME,LOC_SYSTEM_HANIWA_A_MAGICIAN_INFO,HANIWA_T_MAGIC,50,10,true,{},{HANIWA_A_TANMAC,HANIWA_A_SLOW},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_P_NAME,LOC_SYSTEM_HANIWA_A_CREATE_P_INFO,HANIWA_T_SUPPORT,30,10,false,{},{},{HANIWA_A_ARMY1}},
	{LOC_SYSTEM_HANIWA_A_CREATE_WEAPON_NAME,LOC_SYSTEM_HANIWA_A_CREATE_WEAPON_INFO,HANIWA_T_SUPPORT,30,5,false,{},{},{HANIWA_A_ARMY1}},
	{LOC_SYSTEM_HANIWA_A_CREATE_WEAPON_ARTIFACT_NAME,LOC_SYSTEM_HANIWA_A_CREATE_WEAPON_ARTIFACT_INFO,HANIWA_T_SUPPORT,90,20,false,{HANIWA_A_CREATE_WEAPON},{},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_ARMOUR_NAME,LOC_SYSTEM_HANIWA_A_CREATE_ARMOUR_INFO,HANIWA_T_SUPPORT,50,5,false,{},{},{HANIWA_A_ARMY1}},
	{LOC_SYSTEM_HANIWA_A_CREATE_ARMOUR_ARTIFACT_NAME,LOC_SYSTEM_HANIWA_A_CREATE_ARMOUR_ARTIFACT_INFO,HANIWA_T_SUPPORT,90,20,false,{HANIWA_A_CREATE_ARMOUR},{},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_POTION_NAME,LOC_SYSTEM_HANIWA_A_CREATE_POTION_INFO,HANIWA_T_SUPPORT,60,5,false,{},{},{HANIWA_A_ARMY1}},
	{LOC_SYSTEM_HANIWA_A_CREATE_SCROLL_NAME,LOC_SYSTEM_HANIWA_A_CREATE_SCROLL_INFO,HANIWA_T_SUPPORT,60,5,false,{},{},{HANIWA_A_ARMY1}},
	{LOC_SYSTEM_HANIWA_A_WARN_NAMED_NAME,LOC_SYSTEM_HANIWA_A_WARN_NAMED_INFO,HANIWA_T_SUPPORT,10,5,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_IDEN_NAME,LOC_SYSTEM_HANIWA_A_IDEN_INFO,HANIWA_T_SUPPORT,10,5,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_HEAL_NAME,LOC_SYSTEM_HANIWA_A_HEAL_INFO,HANIWA_T_SUPPORT,50,10,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_HARDEN1_NAME,LOC_SYSTEM_HANIWA_A_HARDEN1_INFO,HANIWA_T_COMMON,20,20,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_HARDEN2_NAME,LOC_SYSTEM_HANIWA_A_HARDEN2_INFO,HANIWA_T_COMMON,20,20,false,{HANIWA_A_HARDEN1},{},{}},
	{LOC_SYSTEM_HANIWA_A_HARDEN3_NAME,LOC_SYSTEM_HANIWA_A_HARDEN3_INFO,HANIWA_T_COMMON,20,20,false,{HANIWA_A_HARDEN3},{},{}},
	{LOC_SYSTEM_HANIWA_A_FAST_REVIVE_NAME,LOC_SYSTEM_HANIWA_A_FAST_REVIVE_INFO,HANIWA_T_COMMON,30,10,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_HORSE_NAME,LOC_SYSTEM_HANIWA_A_HORSE_INFO,HANIWA_T_COMMON,60,10,false,{},{},{HANIWA_A_FLY}},
	{LOC_SYSTEM_HANIWA_A_FLY_NAME,LOC_SYSTEM_HANIWA_A_FLY_INFO,HANIWA_T_COMMON,20,10,false,{},{},{HANIWA_A_HORSE}},
	{LOC_SYSTEM_HANIWA_A_TALK_NAME,LOC_SYSTEM_HANIWA_A_TALK_INFO,HANIWA_T_COMMON,0,1,false,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_GIRL_NAME,LOC_SYSTEM_HANIWA_A_GIRL_INFO,HANIWA_T_COMMON,0,1,false,{},{},{}}
};


bool keiki_gift()
{
	bool temp = you.HasAbility(SKL_UPGRADE_HANIWA);
	
	if(!temp)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KEIKI_GIFT_ON) + " ",false,false,false,CL_keiki);
		printlog(LocalzationManager::formatString(joypadUtil::usingPad?LOC_SYSTEM_GOD_KEIKI_GIFT_HELP_PAD:LOC_SYSTEM_GOD_KEIKI_GIFT_HELP, PlaceHolderHelper("a")),true,false,false,CL_help);
		MoreWait();

		you.Ability(SKL_UPGRADE_HANIWA,true,false);
		you.Ability(SKL_DELAY_HANIWA,true,false);
		return true;
	}
	return false;
}

string haniwa_abil::getCostString() {
	if(cost == 0) {
		return LocalzationManager::locString(LOC_SYSTEM_NONE_STRING);
	}
	else if(cost <= 10) {
		return LocalzationManager::locString(LOC_SYSTEM_COST_VERY_LOW);
	} else if(cost <= 20) {
		return LocalzationManager::locString(LOC_SYSTEM_COST_LOW);
	} else if(cost <= 30) {
		return LocalzationManager::locString(LOC_SYSTEM_COST_MIDDLE);
	} else if(cost <= 60) {
		return LocalzationManager::locString(LOC_SYSTEM_COST_HIGH);
	} else {
		return LocalzationManager::locString(LOC_SYSTEM_COST_VERY_HIGH);
	}
}
monster* haniwa_abil::getHaniwa(int haniwa_) {
	for(auto it = env[you.haniwa_allys[haniwa_].floor].mon_vector.begin(); it != env[you.haniwa_allys[haniwa_].floor].mon_vector.end();it++)
	{
		if(it->isLive() && it->map_id == you.haniwa_allys[haniwa_].map_id)
		{
			return &(*it);
		}
	}
	return nullptr;
}
bool haniwa_abil::isEmpty_abil() {
	return you.god_value[GT_KEIKI][0] == 0 && you.god_value[GT_KEIKI][1] == 0;
}
bool haniwa_abil::has_abil(haniwa_abil_key key) {
    int idx = static_cast<int>(key);
    return (idx < 32) ? (( you.god_value[GT_KEIKI][0] >> idx) & 1) : ((you.god_value[GT_KEIKI][1] >> (idx - 32)) & 1);
};

bool haniwa_abil::set_abil(haniwa_abil_key key) {
    int idx = static_cast<int>(key);
    if (idx < 32) {
        you.god_value[GT_KEIKI][0] |= (1 << idx);
    } else if (idx < 64) {
        you.god_value[GT_KEIKI][1] |= (1 << (idx - 32));
    } else {
		return false;
	}

	if(key == HANIWA_A_ARMY1) {
		haniwa_abil::createHaniwa(1, true);
	}
	if(key == HANIWA_A_ARMY2) {
		haniwa_abil::createHaniwa(2, true);
	}

    return true;
};


int haniwa_abil::getMaxHaniwa() {
    return 1+(has_abil(HANIWA_A_ARMY1)?1:0)+(has_abil(HANIWA_A_ARMY2)?1:0);
}

haniwa_abil_type haniwa_abil::currentType() {
	int num_[HANIWA_T_COMMON+1] = {0};
	for(int i = 0; i < HANIWA_A_MAX; i++) {
		if(has_abil((haniwa_abil_key)i)) {
			num_[haniwa_abil_list[i].type]++;
		}
	}


    int max_count = 0;
    int max_count_type = -1;
    bool duplicate = false;

    for (int i = 0; i <= HANIWA_T_COMMON; i++) {
        if (num_[i] > max_count) {
            max_count = num_[i];
            max_count_type = i;
            duplicate = false;
        } else if (num_[i] == max_count && max_count > 0) {
            duplicate = true;
        }
    }

    if (max_count == 0 || duplicate) {
        return HANIWA_T_COMMON;
    }

    return static_cast<haniwa_abil_type>(max_count_type);
}


random_extraction<haniwa_abil_key> haniwa_abil::getAbleHaniwaAbils(int type) {
    random_extraction<haniwa_abil_key> result;

    int current_cost_ = you.piety;
	haniwa_abil_type current_type = currentType();

    if (current_cost_ >= 160) return result;


    for (int i = 0; i < HANIWA_A_MAX; ++i) {
        const haniwa_abil& abil = haniwa_abil_list[i];

        // 이미 배운 능력은 스킵
        if (has_abil(static_cast<haniwa_abil_key>(i)))
            continue;

		if(type != -1 && abil.type != (haniwa_abil_type)type)
            continue;

		if(abil.specific && abil.type != current_type)  {
            continue;
		}

        // except 조건
        bool excepted = false;
        for (auto& ex : abil.except_abil) {
            if (has_abil(ex)) {
                excepted = true;
                break;
            }
        }
		for(int j = 0; j < HANIWA_A_MAX; j++) {
       		if (excepted)
				break;
			if(has_abil((haniwa_abil_key)j)) {
				for (auto& ex : haniwa_abil_list[j].except_abil) {
					if (ex == type) {
						excepted = true;
						break;
					}
				}
			}
		}

        if (excepted) continue;

        // must 조건
        bool missing_must = false;
        for (auto& must : abil.must_abil) {
            if (!has_abil(must)) {
                missing_must = true;
                break;
            }
        }
        if (missing_must) continue;

        // need 조건
        if (!abil.need_abil.empty()) {
            bool has_one_needed = false;
            for (auto& need : abil.need_abil) {
                if (has_abil(need)) {
                    has_one_needed = true;
                    break;
                }
            }
            if (!has_one_needed) continue;
        }

        // 비용 초과 시 제외
        if (abil.cost + current_cost_ > 170)
            continue;

        // 조건을 만족하므로 추가
        result.push(static_cast<haniwa_abil_key>(i), abil.percent);
    }

    return result;
}



haniwa_abil::haniwa_abil(LOCALIZATION_ENUM_KEY name, LOCALIZATION_ENUM_KEY infor, haniwa_abil_type type, int cost, int percent, bool specific, vector<haniwa_abil_key> must_abil, vector<haniwa_abil_key> need_abil, vector<haniwa_abil_key> except_abil) :
name(name), infor(infor), type(type), cost(cost), percent(percent), specific(specific), must_abil(must_abil), need_abil(need_abil), except_abil(except_abil)
{
	
	
}



monster* haniwa_abil::createHaniwa(int index, bool first_) {
	dif_rect_iterator rit(you.position, 2);
	for (; !rit.end(); rit++)
	{
		if (env[current_level].isMove(rit->x, rit->y, true, false) && !env[current_level].isMonsterPos(rit->x, rit->y) && env[current_level].isInSight(coord_def(rit->x, rit->y)) && you.position != (*rit))
		{
            monster *haniwa_ = env[current_level].AddMonster(MON_HANIWA, M_FLAG_ALLY, *rit);
            you.haniwa_allys[index].map_id = haniwa_->map_id;
            you.haniwa_allys[index].floor = current_level;

			upgradeHaniwa(haniwa_);

			if (haniwa_->isYourShight())
			{
				LocalzationManager::printLogWithKey(first_?LOC_SYSTEM_GOD_KEIKI_CREATE:LOC_SYSTEM_GOD_KEIKI_REVIVE,true,false,false,CL_keiki,
					 PlaceHolderHelper(haniwa_->name.getName()));
			}
            return haniwa_;
        }
    }
    return nullptr;
}

void haniwa_abil::upgradeHaniwa(monster* mon) {
	float hp_rate = ((float)mon->hp)/mon->max_hp;

	mon->level = you.level;
	mon->max_hp = mondata[MON_HANIWA].max_hp + you.level*5;
	mon->ac = mondata[MON_HANIWA].ac;
	int att =  mondata[MON_HANIWA].atk[0] + you.level;

	if(has_abil(HANIWA_A_BOW)) {
		att = att*4/3; //33% //근접공격을 안하기에
	}
	if(has_abil(HANIWA_A_DOUBLE_SWORD)) {
		att = att*3/2; //50%
	}
	else if(has_abil(HANIWA_A_SWORD)) {
		att = att*6/5; //20%
	}

	if(has_abil(HANIWA_A_FIRE_ENCHANT) || has_abil(HANIWA_A_COLD_ENCHANT) || has_abil(HANIWA_A_COLD_ENCHANT) || has_abil(HANIWA_A_ELEC_ENCHANT)) {
		att = att*6/5; //20%
	}

	if(has_abil(HANIWA_A_SHIELD1)) {
		mon->max_hp = mon->max_hp*11/10; //10%증가
		mon->ac+=5;
	}
	if(has_abil(HANIWA_A_SHIELD2)) {
		mon->flag |= M_FLAG_SAVE_PLAYER;
		mon->ac+=10;
	}

	if(has_abil(HANIWA_A_HARDEN1)) {
		mon->max_hp = mon->max_hp*13/10; //30%증가
		mon->ac++;
	}
	if(has_abil(HANIWA_A_HARDEN2)) {
		mon->max_hp = mon->max_hp*13/10; //30%증가
		mon->ac+=2;
	}
	if(has_abil(HANIWA_A_HARDEN3)) {
		mon->max_hp = mon->max_hp*14/10; //40%증가
		mon->ac+=3;
	}

	if(has_abil(HANIWA_A_ARMY2)) {
		mon->level = mon->level*2/3+1;
		mon->max_hp = mon->max_hp*2/3+1;
		att = att*2/3+1;
	}
	else if(has_abil(HANIWA_A_ARMY1)) {
		mon->level = mon->level*3/4+1;
		mon->max_hp = mon->max_hp*3/4+1;
		att = att*3/4+1;
	}

	mon->hp = hp_rate*mon->max_hp;

	if(mon->hp < 0)
		mon->hp = 1;
	if(mon->hp > mon->max_hp)
		mon->hp = mon->max_hp;

	for(int i = 0; i<3;i++)
	{
		if(has_abil(HANIWA_A_DOUBLE_SWORD) && i == 1) {
			mon->atk_type[i] = ATT_NORMAL;
			if(has_abil(HANIWA_A_FIRE_ENCHANT)) {
				mon->atk_type[i] = ATT_FIRE;
			} if(has_abil(HANIWA_A_COLD_ENCHANT)) {
				mon->atk_type[i] = ATT_COLD;
			} if(has_abil(HANIWA_A_ELEC_ENCHANT)) {
				mon->atk_type[i] = ATT_ELEC;
			}
			if(has_abil(HANIWA_A_SLOW_ENCHANT)) {
				mon->atk_type[i] = ATT_SLOW_POISON;
			} else if(has_abil(HANIWA_A_POISON_ENCHANT)) {
				mon->atk_type[i] = ATT_S_POISON;
			}
			mon->atk_name[i] = name_infor(LOC_SYSTEM_ATT_NORMAL);
			mon->atk[i] = att;
		}
		else if(mondata[MON_HANIWA].atk[i])
		{
			if(has_abil(HANIWA_A_FIRE_ENCHANT)) {
				mon->atk_type[i] = ATT_FIRE;
			} if(has_abil(HANIWA_A_COLD_ENCHANT)) {
				mon->atk_type[i] = ATT_COLD;
			} if(has_abil(HANIWA_A_ELEC_ENCHANT)) {
				mon->atk_type[i] = ATT_ELEC;
			}
			
			if(has_abil(HANIWA_A_SLOW_ENCHANT)) {
				mon->atk_type[i] = ATT_M_POISON;
			} else if(has_abil(HANIWA_A_POISON_ENCHANT)) {
				mon->atk_type[i] = ATT_S_POISON;
			}
			mon->atk[i] = att;
		}
	}
	mon->spell_lists.clear();

	float spell_rate =has_abil(HANIWA_A_MAGICIAN)?1.2f:1.0f;
	if(has_abil(HANIWA_A_BOW)) {
		mon->spell_lists.push_back(spell(SPL_ARROW, 40));
	}

	if(has_abil(HANIWA_A_BIG_TANMAC)) {
		mon->spell_lists.push_back(spell(SPL_HANIWA_MAGIC_TANMAC3, 25*spell_rate));
	} else if(has_abil(HANIWA_A_MIDDLE_TANMAC)) {
		mon->spell_lists.push_back(spell(SPL_HANIWA_MAGIC_TANMAC2, 25*spell_rate));
	} else if(has_abil(HANIWA_A_TANMAC)) {
		mon->spell_lists.push_back(spell(SPL_HANIWA_MAGIC_TANMAC, 25*spell_rate));
	}

	if(has_abil(HANIWA_A_HASTE)) {
		mon->spell_lists.push_back(spell(SPL_HASTE, 15*spell_rate));
	}

	if(has_abil(HANIWA_A_BLINK)) {
		mon->spell_lists.push_back(spell(SPL_BLINK, 15*spell_rate));
	}

	if(has_abil(HANIWA_A_CONFUSE)) {
		mon->spell_lists.push_back(spell(SPL_CONFUSE, 20*spell_rate));
	}
	else if(has_abil(HANIWA_A_SLOW)) {
		mon->spell_lists.push_back(spell(SPL_SLOW, 20*spell_rate));
	}
	
	if(!has_abil(HANIWA_A_HORSE)) {
		mon->image = &img_mons_haniwa;
	}
	else {
		mon->image = &img_mons_horse_haniwa;
		mon->speed = 7;
	}

	if(has_abil(HANIWA_A_FLY)) {
		mon->walk_speed_bonus = 2;
	}

	if(has_abil(HANIWA_A_BOW) || has_abil(HANIWA_A_MAGICIAN)) {
		mon->flag |= M_FLAG_NO_ATK;
		mon->flag |= M_FLAG_RANGE_ATTACK;
	}

	if(!has_abil(HANIWA_A_SPEAR)) {
		mon->flag |= M_FLAG_SPEAR_ATTACK;
	}
}
void haniwa_abil::upgradeHaniwa() {

	int max_num = haniwa_abil::getMaxHaniwa();
	for(int i = 0; i < max_num; i++) {
		for(auto it = env[you.haniwa_allys[i].floor].mon_vector.begin(); it != env[you.haniwa_allys[i].floor].mon_vector.end();it++)
		{
			if(it->isLive() && it->map_id == you.haniwa_allys[i].map_id)
			{
				upgradeHaniwa(&(*it));
				break;
			}
		}
	}
}


extern shared_ptr<DirectX::SpriteBatch> g_pSprite;
void haniwa_abil::haniwaDraw(float x_, float y_, float scale_) {

	//0: 칼 (R)
	//1: 방패 (L)
	//2: 보조칼 (L)
	//3: 지팡이 (R)
	//4: 헬멧
	//5: 활(LR)
	//6: 창(LR)
	//7: 응급상자(R)
	//8: 황금방패(L)
	//9: 칼 (R, 승마)
	//10: 보조칼 (L, 승마)
	//11: 지팡이 (R, 승마)
	//12: 헬멧 (승마)
	//13: 활 (LR, 승마)
	//14: 창 (LR, 승마)
	//15: 응급상자(R, 승마)
	if(!has_abil(HANIWA_A_HORSE)) {
		if(has_abil(HANIWA_A_SWORD))
			img_mons_haniwa_equipments[0].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		if(has_abil(HANIWA_A_TANMAC))
			img_mons_haniwa_equipments[3].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		else if(has_abil(HANIWA_A_BOW))
			img_mons_haniwa_equipments[5].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		else if(has_abil(HANIWA_A_SPEAR))
			img_mons_haniwa_equipments[6].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		else if(has_abil(HANIWA_A_HEAL))
			img_mons_haniwa_equipments[7].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		
		//왼손
		if(has_abil(HANIWA_A_SHIELD2))
			img_mons_haniwa_equipments[8].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		else if(has_abil(HANIWA_A_SHIELD1))
			img_mons_haniwa_equipments[1].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		else if(has_abil(HANIWA_A_DOUBLE_SWORD))
			img_mons_haniwa_equipments[2].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);

		//머리
		if(has_abil(HANIWA_A_HARDEN1)) 
		{
			img_mons_haniwa_equipments[4].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		}

	} else {
		if(has_abil(HANIWA_A_SWORD))
			img_mons_haniwa_equipments[9].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		else if(has_abil(HANIWA_A_TANMAC))
			img_mons_haniwa_equipments[11].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		else if(has_abil(HANIWA_A_BOW))
			img_mons_haniwa_equipments[13].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		else if(has_abil(HANIWA_A_SPEAR))
			img_mons_haniwa_equipments[14].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		else if(has_abil(HANIWA_A_HEAL))
			img_mons_haniwa_equipments[15].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);

		//왼손
		if(has_abil(HANIWA_A_DOUBLE_SWORD))
			img_mons_haniwa_equipments[10].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
	
		//머리
		if(has_abil(HANIWA_A_HARDEN1)) 
		{
			img_mons_haniwa_equipments[12].draw(g_pSprite, x_, y_,0.0f,scale_,scale_, 255);
		}
	}
}

int haniwa_abil::getGiftCount(int index_) {
	switch(index_) {
	case 0:
		return has_abil(HANIWA_A_CREATE_P)?15:0;
	case 1:
		return has_abil(HANIWA_A_CREATE_WEAPON)?(has_abil(HANIWA_A_CREATE_WEAPON_ARTIFACT)?100:40):0;
	case 2:
		return has_abil(HANIWA_A_CREATE_ARMOUR)?(has_abil(HANIWA_A_CREATE_ARMOUR_ARTIFACT)?120:50):0;
	case 3:
		return has_abil(HANIWA_A_CREATE_POTION)?40:0;
	case 4:
		return has_abil(HANIWA_A_CREATE_SCROLL)?40:0;
	}
	return 0;
}


void han_weapon_gift(bool speak_)
{
	
	random_extraction<int> rand_;

	for(int i=SKT_SHORTBLADE;i<=SKT_SPEAR;i++)
	{
		rand_.push(i-SKT_SHORTBLADE, you.GetSkillLevel(i, true)+1);
	}

	item_infor t;
	item* it = env[current_level].MakeItem(you.position,makeitem((item_type)(rand_.pop()), 1, &t));
	//it->value3 += rand_int(-1,6);
	it->value4 += rand_int(-2,6);
	if(!it->value5 && randA(2)>1)
		it->value5 = GetNewBrand(0); //카나코는 신의 브랜드는 선물하지 않는다.
	if(randA(3) == 0)
		MakeArtifact(it,1);
	if(speak_)
	{
		printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_GIFT_APPEAR),true,false,false,CL_dark_good);

		AddNote(you.turn,CurrentLevelString(),LocalzationManager::formatString(LOC_SYSTEM_NOTE_GOD_GIFT, PlaceHolderHelper(LOC_SYSTEM_GOD_KANAKO)),CL_help);

		MoreWait();
	}
}


void haniwa_abil::increaseGift(int haniwa_, int index_) {
	you.haniwa_allys[haniwa_].item_count[index_]++;
	int require_count_ = getGiftCount(index_);
	if(require_count_ != 0 && require_count_ < you.haniwa_allys[haniwa_].item_count[index_] && you.haniwa_allys[haniwa_].floor == current_level) {
		monster* haniwa_mon_ = getHaniwa(haniwa_);
		if(haniwa_mon_ != nullptr && env[current_level].isInSight(haniwa_mon_->position)) {
			you.haniwa_allys[haniwa_].item_count[index_]-=require_count_;
			switch(index_) {
			case 0:
				if(has_abil(HANIWA_A_CREATE_P)) {
					item_infor temp;
					env[current_level].MakeItem(haniwa_mon_->position, makePitem(MON_MOOK, 1, &temp));
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KEIKI_HANIWA_CREATE_P) + " ", false, false, false, CL_normal);
				}
				break;
			case 1:
				if(has_abil(HANIWA_A_CREATE_WEAPON)) {
					random_extraction<int> rand_;

					for(int i=SKT_SHORTBLADE;i<=SKT_SPEAR;i++)
					{
						rand_.push(i-SKT_SHORTBLADE, you.GetSkillLevel(i, true)+1);
					}

					item_infor t;
					item* it = env[current_level].MakeItem(haniwa_mon_->position,makeitem((item_type)(rand_.pop()), 1, &t));
					it->value4 += rand_int(-2,4);
					if(!it->value5 && randA(2)>1)
						it->value5 = GetNewBrand(0);

					if(has_abil(HANIWA_A_CREATE_WEAPON_ARTIFACT)) {
						MakeArtifact(it,1);
					}

					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KEIKI_HANIWA_CREATE_WEAPON) + " ", false, false, false, CL_normal);
				}
				break;
			case 2:
				if(has_abil(HANIWA_A_CREATE_ARMOUR)) {
					random_extraction<int> rand_;
					rand_.push(0,5); //아머
					rand_.push(1, you.GetSkillLevel(SKT_SHIELD, true)>=1?3:1); //방패
					rand_.push(2,you.equipment[ET_HELMET]==NULL?5:1); //머리
					rand_.push(3,you.equipment[ET_CLOAK]==NULL?5:1); //망토
					rand_.push(4,you.equipment[ET_GLOVE]==NULL?5:1); //손
					rand_.push(5,you.equipment[ET_BOOTS]==NULL?5:1); //발
					item* it = NULL;
					int armour_ = rand_.pop();
					switch(armour_)
					{
					case 0:
						{
							bool dodge_ = (you.GetSkillLevel(SKT_DODGE, true)>you.GetSkillLevel(SKT_ARMOUR, true)*2 || you.GetSkillLevel(SKT_ARMOUR, true) < 5);
							bool heavy_ = (you.GetSkillLevel(SKT_ARMOUR, true)>you.GetSkillLevel(SKT_DODGE, true) *2 || you.GetSkillLevel(SKT_ARMOUR, true) >= 15);
							random_extraction<int> rand2_;

							rand2_.push(ITM_ARMOR_BODY_ARMOUR_0,dodge_?10:1); //로브
							rand2_.push(ITM_ARMOR_BODY_ARMOUR_1,dodge_?8:4); //가죽
							rand2_.push(ITM_ARMOR_BODY_ARMOUR_2,heavy_?8:4); //체인
							rand2_.push(ITM_ARMOR_BODY_ARMOUR_3,heavy_?10:1); //판금
					
							int select_ = rand2_.pop();
							item_infor t;
							it = env[current_level].MakeItem(haniwa_mon_->position,makeitem((item_type)select_, 1, &t,-1));
						}
						break;
					case 1:
						{
							random_extraction<int> rand2_;

							rand2_.push(0, you.GetSkillLevel(SKT_SHIELD, true) <=5?5:1); //버클러
							rand2_.push(28, you.GetSkillLevel(SKT_SHIELD, true) >=10?5:1); //실드
							rand2_.push(30, you.GetSkillLevel(SKT_SHIELD, true) >=20?10:1); //카이트
							
							int select_ = rand2_.pop();
							
							item_infor t;
							it = env[current_level].MakeItem(haniwa_mon_->position,makeitem(ITM_ARMOR_SHIELD, 1, &t,select_));
						}
						break;
					case 2:
					case 3:
					case 4:
					case 5:
						{
							random_extraction<int> rand2_;		
							
							item_infor t;
							it = env[current_level].MakeItem(haniwa_mon_->position,makeitem((item_type)(ITM_ARMOR_HEAD+armour_-2), 1, &t));
						}
						break;
					}
					if(has_abil(HANIWA_A_CREATE_ARMOUR_ARTIFACT)) {
						MakeArtifact(it,1);
					}
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KEIKI_HANIWA_CREATE_ARMOUR) + " ", false, false, false, CL_normal);
				}
				break;
			case 3:
				if(has_abil(HANIWA_A_CREATE_POTION)) {
					potion_type type_= goodbadpotion(randA(2)>1?1:(randA(20)?2:3));
					int num = 1;
					item_infor t;
					for(int i=0;i<num;i++)
						env[current_level].MakeItem(haniwa_mon_->position,makeitem(ITM_POTION, 0, &t,(int)type_));
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KEIKI_HANIWA_CREATE_POTION) + " ", false, false, false, CL_normal);

				}
				break;
			case 4:
				if(has_abil(HANIWA_A_CREATE_SCROLL)) {
					scroll_type type_= goodbadscroll(randA(2)>1?1:(randA(20)?2:3));
					int num = 1;
					item_infor t;
					for(int i=0;i<num;i++)
						env[current_level].MakeItem(haniwa_mon_->position,makeitem(ITM_SCROLL, 0, &t,(int)type_));
					printlog(LocalzationManager::locString(LOC_SYSTEM_GOD_KEIKI_HANIWA_CREATE_SCROLL) + " ", false, false, false, CL_normal);
				}
				break;
			}
		}
	}
}