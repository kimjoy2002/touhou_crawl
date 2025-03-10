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
#include <unordered_set>
#include <regex>
#include "d3dUtility.h"
#include <initializer_list>
#include <vector>
#include "enum.h"

using namespace std;


enum LOCALIZATION_TYPE {
	LOCALIZATION_TYPE_ENG,
	LOCALIZATION_TYPE_KOR
};


#define LOCALIZATION_ENUM_LIST \
    X(LOC_NONE) \
    X(LOC_SYSTEM_LOS_MON) \
    X(LOC_SYSTEM_LOS_NOMON) \
    X(LOC_SYSTEM_CONFUSE_WARNING) \
    X(LOC_SYSTEM_DIMENSTION) \
    X(LOC_SYSTEM_MAP_DANGER) \
    X(LOC_SYSTEM_UNABLE_MOVE) \
    X(LOC_SYSTEM_AUTOBATTLE_DANGERHP) \
    X(LOC_SYSTEM_AUTOBATTLE_NOMON) \
    X(LOC_SYSTEM_LUNATIC_PENALTY) \
    X(LOC_SYSTEM_AUTOTRAVEL_BAMBOO) \
    X(LOC_SYSTEM_DONE_EXPLORE) \
    X(LOC_SYSTEM_REST_START) \
    X(LOC_SYSTEM_REST_HP) \
    X(LOC_SYSTEM_REST_MP) \
    X(LOC_SYSTEM_REST_DONE) \
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
    X(LOC_SYSTEM_SMOKE_NORMAL) \
    X(LOC_SYSTEM_SMOKE_FOG) \
    X(LOC_SYSTEM_SMOKE_FIRE) \
    X(LOC_SYSTEM_SMOKE_COLD) \
    X(LOC_SYSTEM_SMOKE_ELEC) \
    X(LOC_SYSTEM_SMOKE_DARK) \
    X(LOC_SYSTEM_SMOKE_SION) \
    X(LOC_SYSTEM_SMOKE_POISON) \
    X(LOC_SYSTEM_SMOKE_CONFUSE) \
    X(LOC_SYSTEM_SMOKE_SLOW) \
    X(LOC_SYSTEM_SMOKE_TWIST) \
    X(LOC_SYSTEM_SMOKE_WHIRLWIND) \
    X(LOC_SYSTEM_SMOKE_CURSE) \
    X(LOC_SYSTEM_SMOKE_BLIZZARD) \
    X(LOC_SYSTEM_MANY_ITEMS) \
    X(LOC_SYSTEM_TERRAIN_UNSEEN) \
    X(LOC_SYSTEM_TERRAIN) \
    X(LOC_SYSTEM_TERRAIN_SILENCE) \
    X(LOC_SYSTEM_TERRAIN_VIOLET) \
    X(LOC_SYSTEM_TERRAIN_SANCTUARY) \
    X(LOC_SYSTEM_ON_THE_TERRAIN) \
    X(LOC_SYSTEM_ON_THE_ITEM_SINGLE) \
    X(LOC_SYSTEM_ON_THE_ITEM_MULTIPLE) \
    X(LOC_MAX) // 마지막 ENUM

// **ENUM 정의**
enum LOCALIZATION_ENUM_KEY {
#define X(name) name,
    LOCALIZATION_ENUM_LIST
#undef X
};


class PlaceHolderHelper {
public:
    string name;
    LOCALIZATION_ENUM_KEY key = LOC_NONE;
    bool plural = false;
    bool hasColor = false;
    D3DCOLOR color;

    PlaceHolderHelper(const char* name) : name(name){};
    PlaceHolderHelper(string name) : name(name){};
    PlaceHolderHelper(LOCALIZATION_ENUM_KEY key) : key(key){};
    PlaceHolderHelper(string name, D3DCOLOR color) : name(name), color(color){hasColor = true;};
    PlaceHolderHelper(LOCALIZATION_ENUM_KEY key, D3DCOLOR color) : name(name), color(color){hasColor = true;};
    PlaceHolderHelper(string name, D3DCOLOR color, bool plural) : name(name), color(color), plural(plural){hasColor = true;};
    PlaceHolderHelper(LOCALIZATION_ENUM_KEY key, D3DCOLOR color, bool plural) : name(name), color(color), plural(plural){hasColor = true;};
};



class LocalzationManager {
private:
// 전역 변수로 사용
	static unordered_map<string, LOCALIZATION_ENUM_KEY> localization_enum_map;
	static unordered_map<LOCALIZATION_ENUM_KEY, string> localization_map;
	static unordered_map<monster_index, string> monster_name_map;

	static unordered_set<string> korean_verbs;
	static unordered_set<string> english_verbs;
	static unordered_set<string> english_article;

public:
	static void init(LOCALIZATION_TYPE type);

	static string& locString(LOCALIZATION_ENUM_KEY key);

	template<typename... Args>
	static std::string formatString(const std::string& template_str, Args... args) {
		std::vector<PlaceHolderHelper> values = { std::forward<Args>(args)...};
		return processTags(template_str, values);
	}

	template<typename... Args>
	static std::string formatString(LOCALIZATION_ENUM_KEY template_key, Args... args) {
		std::string template_str = locString(template_key);
		std::vector<PlaceHolderHelper> values = { std::forward<Args>(args)...};
		return processTags(template_str, values);
	}

	template<typename... Args>
	static void printLogWithKey(LOCALIZATION_ENUM_KEY template_key, bool enter_, bool log_, bool temp_, D3DCOLOR color_, Args... args) {
        std::string template_str = locString(template_key);
        regex placeholder_regex(R"(\{(\d+)(?::([^}]+))?\})");
        smatch match;
		std::vector<PlaceHolderHelper> values = { std::forward<Args>(args)...};
        std::sregex_token_iterator iter(template_str.begin(), template_str.end(), placeholder_regex, {-1, 0});
        std::sregex_token_iterator end;
    

        while (iter != end) {
            std::string token = *iter;
            bool isEnd = (++iter) == end;
            if(token.length() >= 2 && token[0] == '{', token[token.length()-1]=='}') {
                auto pair_placeholder = extractPlaceholder(token);
                if(!pair_placeholder.first.empty()) {
                    int index = stoi(pair_placeholder.first); 
                    if (index < values.size()) {
                        const PlaceHolderHelper& ph = values[index];
                        string value = (ph.key != LOC_NONE) ? locString(ph.key) : ph.name;
            
                        if (!pair_placeholder.second.empty()) {
                            string verb_ = verb(value, pair_placeholder.second, ph.plural, true);
                            if(verb_.length() > 1) {
                                if(verb_[verb_.length()-1] == ' ') {
                                    printlog(verb_,false,log_,temp_,color_);
                                    printlog(value,isEnd?enter_:false,log_,temp_,ph.hasColor?ph.color:color_);
                                } else {
                                    printlog(value,false,log_,temp_,ph.hasColor?ph.color:color_);
                                    printlog(verb_,isEnd?enter_:false,log_,temp_,color_);
                                }
                            } else {                                
                                printlog(value,isEnd?enter_:false,log_,temp_,ph.hasColor?ph.color:color_);
                            }
                        } else {
                            printlog(value,isEnd?enter_:false,log_,temp_,ph.hasColor?ph.color:color_);
                        }
                    }
                }
            } else {
                printlog(token,isEnd?enter_:false,log_,temp_,color_);
            }
        }
    }


	static string& monString(monster_index key);

private:
    static std::string processTags(const std::string& template_str, const vector<PlaceHolderHelper>& values);
    static std::string verb(const std::string& text, const std::string& verb, bool plural, bool only_verb);
    static string getCorrectParticle(const string& word, const string& opt1, const string& opt2);
    static string getIndefiniteArticle(const string& word,const string& opt1, const string& opt2);
    static pair<string, string> extractPlaceholder(const string& input);
};

#endif // __LOCALIIZATION_H__