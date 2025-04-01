//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: enumMapBuilder.cpp
//
// 내용: enum 생성기
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "enumMapBuilder.h"
#include "enum.h"
#include "speak.h"
#include <unordered_map>


std::unordered_map<std::string, monster_index> createMonsterEnumMap() {
    std::unordered_map<std::string, monster_index> map;
    map["MON_NONE_MONSTER"] = MON_NONE_MONSTER;
#define MONLIST_X(name) map[#name] = static_cast<monster_index>(name);
    MONSTER_LIST
#undef MONLIST_X

    return map;
}

std::unordered_map<monster_index, std::string> createMonsterEnumReverseMap() {
    std::unordered_map<monster_index, std::string> map;
    map[MON_NONE_MONSTER] = "MON_NONE_MONSTER";
#define MONLIST_X(name) map[name] = #name;
    MONSTER_LIST
#undef MONLIST_X

    return map;
}

std::unordered_map<std::string, LOCALIZATION_ENUM_KEY> createEnumMap() {
    std::unordered_map<std::string, LOCALIZATION_ENUM_KEY> map;
#define X(name) map[#name] = name;
    LOCALIZATION_ENUM_LIST
#undef X
    return map;
}

std::unordered_map<LOCALIZATION_ENUM_KEY, std::string> createEnumReverseMap() {
    std::unordered_map<LOCALIZATION_ENUM_KEY, std::string> map;

#define X(name) map[name] = #name;
    LOCALIZATION_ENUM_LIST
#undef X

    return map;
}

std::unordered_map<std::string, SPEAK_ENUM_KEY> createSpeakEnumMap() {
    std::unordered_map<std::string, SPEAK_ENUM_KEY> map;

#define SPKLIST_X(name) map[#name] = static_cast<SPEAK_ENUM_KEY>(name);
    SPEAK_LIST
#undef SPKLIST_X

    return map;
}