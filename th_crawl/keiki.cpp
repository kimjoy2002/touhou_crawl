//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: keiki.cpp
//
// 내용: 케이키 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "keiki.h"
#include "environment.h"
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

haniwa_abil haniwa_abil_list[HANIWA_A_MAX] = {
	{LOC_SYSTEM_HANIWA_A_SWORD_NAME,LOC_SYSTEM_HANIWA_A_SWORD_INFO,HANIWA_T_COMBAT,30,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_DOUBLE_SWORD_NAME,LOC_SYSTEM_HANIWA_A_DOUBLE_SWORD_INFO,HANIWA_T_COMBAT,20,20,{HANIWA_A_SWORD},{},{}},
	{LOC_SYSTEM_HANIWA_A_SPEAR_NAME,LOC_SYSTEM_HANIWA_A_SPEAR_INFO,HANIWA_T_COMBAT,30,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_BOW_NAME,LOC_SYSTEM_HANIWA_A_BOW_INFO,HANIWA_T_COMBAT,30,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_SHIELD1_NAME,LOC_SYSTEM_HANIWA_A_SHIELD1_INFO,HANIWA_T_COMBAT,30,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_SHIELD2_NAME,LOC_SYSTEM_HANIWA_A_SHIELD2_INFO,HANIWA_T_COMBAT,60,20,{HANIWA_A_SHIELD1},{},{}},
	{LOC_SYSTEM_HANIWA_A_EXPLOSION_NAME,LOC_SYSTEM_HANIWA_A_EXPLOSION_INFO,HANIWA_T_COMBAT,15,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_ARMY1_NAME,LOC_SYSTEM_HANIWA_A_ARMY1_INFO,HANIWA_T_COMBAT,60,5,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_ARMY2_NAME,LOC_SYSTEM_HANIWA_A_ARMY2_INFO,HANIWA_T_COMBAT,60,15,{HANIWA_A_ARMY1},{},{}},
	{LOC_SYSTEM_HANIWA_A_CLEAVE_NAME,LOC_SYSTEM_HANIWA_A_CLEAVE_INFO,HANIWA_T_COMBAT,90,5,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_FIRE_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_FIRE_ENCHANT_INFO,HANIWA_T_COMBAT,20,5,{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW},{HANIWA_A_FIRE_ENCHANT,HANIWA_A_COLD_ENCHANT,HANIWA_A_ELEC_ENCHANT,HANIWA_A_POISON_ENCHANT}},
	{LOC_SYSTEM_HANIWA_A_COLD_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_COLD_ENCHANT_INFO,HANIWA_T_COMBAT,20,5,{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW},{HANIWA_A_FIRE_ENCHANT,HANIWA_A_COLD_ENCHANT,HANIWA_A_ELEC_ENCHANT,HANIWA_A_POISON_ENCHANT}},
	{LOC_SYSTEM_HANIWA_A_ELEC_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_ELEC_ENCHANT_INFO,HANIWA_T_COMBAT,20,5,{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW},{HANIWA_A_FIRE_ENCHANT,HANIWA_A_COLD_ENCHANT,HANIWA_A_ELEC_ENCHANT,HANIWA_A_POISON_ENCHANT}},
	{LOC_SYSTEM_HANIWA_A_POISON_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_POISON_ENCHANT_INFO,HANIWA_T_COMBAT,20,5,{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW},{HANIWA_A_FIRE_ENCHANT,HANIWA_A_COLD_ENCHANT,HANIWA_A_ELEC_ENCHANT,HANIWA_A_POISON_ENCHANT}},
	{LOC_SYSTEM_HANIWA_A_SLOW_ENCHANT_NAME,LOC_SYSTEM_HANIWA_A_SLOW_ENCHANT_INFO,HANIWA_T_COMBAT,40,20,{HANIWA_A_POISON_ENCHANT},{},{}},
	{LOC_SYSTEM_HANIWA_A_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_TANMAC_INFO,HANIWA_T_MAGIC,30,30,{},{},{HANIWA_A_SWORD,HANIWA_A_SPEAR,HANIWA_A_BOW}},
	{LOC_SYSTEM_HANIWA_A_FIRE_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_FIRE_TANMAC_INFO,HANIWA_T_MAGIC,20,5,{},{HANIWA_A_TANMAC},{HANIWA_A_FIRE_TANMAC,HANIWA_A_COLD_TANMAC,HANIWA_A_ELEC_TANMAC}},
	{LOC_SYSTEM_HANIWA_A_COLD_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_COLD_TANMAC_INFO,HANIWA_T_MAGIC,20,5,{},{HANIWA_A_TANMAC},{HANIWA_A_FIRE_TANMAC,HANIWA_A_COLD_TANMAC,HANIWA_A_ELEC_TANMAC}},
	{LOC_SYSTEM_HANIWA_A_ELEC_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_ELEC_TANMAC_INFO,HANIWA_T_MAGIC,20,5,{},{HANIWA_A_TANMAC},{HANIWA_A_FIRE_TANMAC,HANIWA_A_COLD_TANMAC,HANIWA_A_ELEC_TANMAC}},
	{LOC_SYSTEM_HANIWA_A_MIDDLE_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_MIDDLE_TANMAC_INFO,HANIWA_T_MAGIC,30,20,{HANIWA_A_TANMAC},{},{}},
	{LOC_SYSTEM_HANIWA_A_BIG_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_BIG_TANMAC_INFO,HANIWA_T_MAGIC,30,20,{HANIWA_A_MIDDLE_TANMAC},{},{}},
	{LOC_SYSTEM_HANIWA_A_BURST_TANMAC_NAME,LOC_SYSTEM_HANIWA_A_BURST_TANMAC_INFO,HANIWA_T_MAGIC,30,10,{},{HANIWA_A_TANMAC},{HANIWA_A_PENTAN}},
	{LOC_SYSTEM_HANIWA_A_BLINK_NAME,LOC_SYSTEM_HANIWA_A_BLINK_INFO,HANIWA_T_MAGIC,20,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_SLOW_NAME,LOC_SYSTEM_HANIWA_A_SLOW_INFO,HANIWA_T_MAGIC,30,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_CONFUSE_NAME,LOC_SYSTEM_HANIWA_A_CONFUSE_INFO,HANIWA_T_MAGIC,30,20,{HANIWA_A_SLOW},{},{}},
	{LOC_SYSTEM_HANIWA_A_PENTAN_NAME,LOC_SYSTEM_HANIWA_A_PENTAN_INFO,HANIWA_T_MAGIC,30,10,{},{HANIWA_A_TANMAC},{HANIWA_A_BURST_TANMAC}},
	{LOC_SYSTEM_HANIWA_A_HASTE_NAME,LOC_SYSTEM_HANIWA_A_HASTE_INFO,HANIWA_T_MAGIC,60,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_MAGICIAN_NAME,LOC_SYSTEM_HANIWA_A_MAGICIAN_INFO,HANIWA_T_MAGIC,50,10,{},{HANIWA_A_TANMAC,HANIWA_A_SLOW},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_P_NAME,LOC_SYSTEM_HANIWA_A_CREATE_P_INFO,HANIWA_T_SUPPORT,30,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_WEAPON_NAME,LOC_SYSTEM_HANIWA_A_CREATE_WEAPON_INFO,HANIWA_T_SUPPORT,30,5,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_WEAPON_ARTIFACT_NAME,LOC_SYSTEM_HANIWA_A_CREATE_WEAPON_ARTIFACT_INFO,HANIWA_T_SUPPORT,90,20,{HANIWA_A_CREATE_WEAPON},{},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_ARMOUR_NAME,LOC_SYSTEM_HANIWA_A_CREATE_ARMOUR_INFO,HANIWA_T_SUPPORT,50,5,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_ARMOUR_ARTIFACT_NAME,LOC_SYSTEM_HANIWA_A_CREATE_ARMOUR_ARTIFACT_INFO,HANIWA_T_SUPPORT,90,20,{HANIWA_A_CREATE_ARMOUR},{},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_POTION_NAME,LOC_SYSTEM_HANIWA_A_CREATE_POTION_INFO,HANIWA_T_SUPPORT,60,5,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_CREATE_SCROLL_NAME,LOC_SYSTEM_HANIWA_A_CREATE_SCROLL_INFO,HANIWA_T_SUPPORT,60,5,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_WARN_NAMED_NAME,LOC_SYSTEM_HANIWA_A_WARN_NAMED_INFO,HANIWA_T_SUPPORT,10,5,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_IDEN_NAME,LOC_SYSTEM_HANIWA_A_IDEN_INFO,HANIWA_T_SUPPORT,10,5,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_HEAL_NAME,LOC_SYSTEM_HANIWA_A_HEAL_INFO,HANIWA_T_SUPPORT,50,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_HARDEN1_NAME,LOC_SYSTEM_HANIWA_A_HARDEN1_INFO,HANIWA_T_COMMON,20,20,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_HARDEN2_NAME,LOC_SYSTEM_HANIWA_A_HARDEN2_INFO,HANIWA_T_COMMON,20,20,{HANIWA_A_HARDEN1},{},{}},
	{LOC_SYSTEM_HANIWA_A_HARDEN3_NAME,LOC_SYSTEM_HANIWA_A_HARDEN3_INFO,HANIWA_T_COMMON,20,20,{HANIWA_A_HARDEN3},{},{}},
	{LOC_SYSTEM_HANIWA_A_FAST_REVIVE_NAME,LOC_SYSTEM_HANIWA_A_FAST_REVIVE_INFO,HANIWA_T_COMMON,30,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_HORSE_NAME,LOC_SYSTEM_HANIWA_A_HORSE_INFO,HANIWA_T_COMMON,60,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_FLY_NAME,LOC_SYSTEM_HANIWA_A_FLY_INFO,HANIWA_T_COMMON,20,10,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_TALK_NAME,LOC_SYSTEM_HANIWA_A_TALK_INFO,HANIWA_T_COMMON,0,1,{},{},{}},
	{LOC_SYSTEM_HANIWA_A_GIRL_NAME,LOC_SYSTEM_HANIWA_A_GIRL_INFO,HANIWA_T_COMMON,0,1,{},{},{}}
};


bool keiki_gift()
{
	int temp = you.Ability(SKL_UPGRADE_HANIWA,true,true);
	
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
    return true;
};


int haniwa_abil::getMaxHaniwa() {
    return 1+(has_abil(HANIWA_A_ARMY1)?1:0)+(has_abil(HANIWA_A_ARMY2)?1:0);
}

random_extraction<haniwa_abil_key> haniwa_abil::getAbleHaniwaAbils() {
    random_extraction<haniwa_abil_key> result;

    int current_cost_ = you.piety;

    if (current_cost_ >= 160) return result;


    for (int i = 0; i < HANIWA_A_MAX; ++i) {
        const haniwa_abil& abil = haniwa_abil_list[i];

        // 이미 배운 능력은 스킵
        if (has_abil(static_cast<haniwa_abil_key>(i)))
            continue;

        // except 조건
        bool excepted = false;
        for (auto& ex : abil.except_abil) {
            if (has_abil(ex)) {
                excepted = true;
                break;
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



haniwa_abil::haniwa_abil(LOCALIZATION_ENUM_KEY name, LOCALIZATION_ENUM_KEY infor, haniwa_abil_type type, int cost, int percent, vector<haniwa_abil_key> must_abil, vector<haniwa_abil_key> need_abil, vector<haniwa_abil_key> except_abil) :
name(name), infor(infor), type(type), cost(cost), percent(percent), must_abil(must_abil), need_abil(need_abil), except_abil(except_abil)
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
	mon->hp = hp_rate*mon->max_hp;

	if(mon->hp < 0)
		mon->hp = 1;
	if(mon->hp > mon->max_hp)
		mon->hp = mon->max_hp;

	for(int i = 0; i<3;i++)
	{
		if(mondata[MON_HANIWA].atk[i])
		{
			mon->atk[i] = mondata[MON_HANIWA].atk[i]+ you.level;
		}
	}

	
	if(!has_abil(HANIWA_A_HORSE)) {
		mon->image = &img_mons_haniwa;
	}
	else {
		mon->image = &img_mons_horse_haniwa;
	}

	if(!has_abil(HANIWA_A_SPEAR)) {
		mon->flag &= M_FLAG_SPEAR_ATTACK;
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
		//	if(has_abil(HANIWA_A_SWORD))
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
	}


}