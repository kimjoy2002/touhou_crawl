//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: localization.h
//
// 내용: 다국어 처리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __LOCALIIZATION_H__
#define  __LOCALIIZATION_H__

#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include "enum.h"

using namespace std;


enum LOCALIZATION_TYPE {
	LOCALIZATION_TYPE_ENG,
	LOCALIZATION_TYPE_KOR
};


#define LOCALIZATION_ENUM_LIST \
    X(LOC_NONE) \
    X(LOC_DESCRIPTION_LOS_MON) \
    X(LOC_DESCRIPTION_LOS_NOMON) \
    X(LOC_DESCRIPTION_CONFUSE) \
    X(LOC_DESCRIPTION_DIMENSTION) \
    X(LOC_DESCRIPTION_MAP_DANGER) \
    X(LOC_DESCRIPTION_UNABLE_MOVE) \
    X(LOC_DESCRIPTION_AUTOBATTLE_DANGERHP) \
    X(LOC_DESCRIPTION_AUTOBATTLE_NOMON) \
    X(LOC_DESCRIPTION_LUNATIC_PENALTY) \
    X(LOC_DESCRIPTION_AUTOTRAVEL_BAMBOO) \
    X(LOC_DESCRIPTION_DONE_EXPLORE) \
    X(LOC_DESCRIPTION_REST_START) \
    X(LOC_DESCRIPTION_REST_HP) \
    X(LOC_DESCRIPTION_REST_MP) \
    X(LOC_DESCRIPTION_REST_DONE) \
    X(LOC_SYSTEM_COMMAND) \
    X(LOC_SYSTEM_DESCRIPTION) \
    X(LOC_SYSTEM_EXPLORE) \
    X(LOC_SYSTEM_DANGER) \
    X(LOC_SYSTEM_STAIR_TRAVEL) \
    X(LOC_SYSTEM_MONSTER) \
    X(LOC_SYSTEM_SUCCESS_PERCENT) \
    X(LOC_SYSTEM_IMPOSSIBLE) \
    X(LOC_SYSTEM_TURN) \
    X(LOC_SYSTEM_TURNS) \
    X(LOC_SYSTEM_SLEEP) \
    X(LOC_SYSTEM_REST) \
    X(LOC_SYSTEM_EXPLORING) \
    X(LOC_SYSTEM_CANT_DETECTED) \
    X(LOC_SYSTEM_CONFUSE) \
    X(LOC_SYSTEM_POISON) \
    X(LOC_SYSTEM_MIGHT) \
    X(LOC_SYSTEM_CLEVER) \
    X(LOC_SYSTEM_HASTE) \
    X(LOC_SYSTEM_SLOW) \
    X(LOC_SYSTEM_SUMMONED) \
    X(LOC_SYSTEM_FROZEN) \
    X(LOC_SYSTEM_ALLY) \
    X(LOC_SYSTEM_ELEC) \
    X(LOC_SYSTEM_PARALYSE) \
    X(LOC_SYSTEM_GLOW) \
    X(LOC_SYSTEM_GRAZE) \
    X(LOC_SYSTEM_SILENCE) \
    X(LOC_SYSTEM_SICK) \
    X(LOC_SYSTEM_VEILING) \
    X(LOC_SYSTEM_INVISIVLE) \
    X(LOC_SYSTEM_TELE) \
    X(LOC_SYSTEM_MUTE) \
    X(LOC_SYSTEM_CATCH) \
    X(LOC_SYSTEM_GHOST) \
    X(LOC_SYSTEM_FEAR) \
    X(LOC_SYSTEM_STRONG_FEAR) \
    X(LOC_SYSTEM_MIND_READING) \
    X(LOC_SYSTEM_LUNATIC) \
    X(LOC_SYSTEM_ALLY_CALL) \
    X(LOC_SYSTEM_ENHANCE) \
    X(LOC_SYSTEM_WEAKENING) \
    X(LOC_SYSTEM_CHANGED) \
    X(LOC_SYSTEM_INVINCIBILITY) \
    X(LOC_SYSTEM_HP_VERY_LOW) \
    X(LOC_SYSTEM_HP_LOW) \
    X(LOC_SYSTEM_HP_MIDDLE) \
    X(LOC_SYSTEM_HP_HIGH) \
    X(LOC_SYSTEM_HP_VERY_HIGH) \
    X(LOC_MAX) // 마지막 ENUM

// **ENUM 정의**
enum LOCALIZATION_ENUM_KEY {
#define X(name) name,
    LOCALIZATION_ENUM_LIST
#undef X
};


class LocalzationManager {
private:
// 전역 변수로 사용
	static unordered_map<string, LOCALIZATION_ENUM_KEY> localization_enum_map;
	static unordered_map<LOCALIZATION_ENUM_KEY, string> localization_map;
	static unordered_map<monster_index, string> monster_name_map;

public:
	static void init(LOCALIZATION_TYPE type);

	static string& locString(LOCALIZATION_ENUM_KEY key);

	template<typename... Args>
	static std::string formatString(const std::string& template_str, Args... args) {
		std::vector<std::string> values = {args...};
		return processTags(template_str, values);
	}

	template<typename... Args>
	static std::string formatStringWithKey(LOCALIZATION_ENUM_KEY template_key, Args... args) {
		std::string template_str = locString(template_key);
		std::vector<std::string> values = {args...};
		return processTags(template_str, values);
	}

	static string& monString(monster_index key);

private:
static std::string processTags(const std::string& template_str, const vector<string>& values);
};

#endif // __LOCALIIZATION_H__