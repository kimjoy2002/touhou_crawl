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
#include <functional>
#include <regex>
#include "d3dUtility.h"
#include "d3d9types.h"
#include <initializer_list>
#include <vector>
#include "enum.h"
#include "enumMapBuilder.h"

using namespace std;

class PlaceHolderHelper {
public:
    string name;
    LOCALIZATION_ENUM_KEY key = LOC_NONE;
    bool plural = false;
    bool hasColor = false;
    D3DCOLOR color;

    PlaceHolderHelper(const char* name) : name(name){};
    PlaceHolderHelper(const string& name) : name(name){};
    PlaceHolderHelper(string name, bool plural) : name(name), plural(plural){};
    PlaceHolderHelper(LOCALIZATION_ENUM_KEY key) : key(key){};
    PlaceHolderHelper(string name, D3DCOLOR color) : name(name), color(color){hasColor = true;};
    PlaceHolderHelper(LOCALIZATION_ENUM_KEY key, D3DCOLOR color) : name(), color(color){hasColor = true;};
    PlaceHolderHelper(string name, D3DCOLOR color, bool plural) : name(name), plural(plural), color(color){hasColor = true;};
    PlaceHolderHelper(LOCALIZATION_ENUM_KEY key, D3DCOLOR color, bool plural) : name(), plural(plural), color(color){hasColor = true;};
};

class TextHelper {
public:
    string text;
    bool enter;
    D3DCOLOR color;
    TextHelper(string text, bool enter, D3DCOLOR color) : text(std::move(text)), enter(enter), color(color){};
};

struct localizationInfo {
    std::string name;
    std::string font;
};


class LocalzationManager {
private:
    static OrderedMap<string, localizationInfo> localization_type;
// 전역 변수로 사용
	static unordered_map<string, LOCALIZATION_ENUM_KEY> localization_enum_map;
	static unordered_map<LOCALIZATION_ENUM_KEY, string> localization_enum_reverse_map;
	static unordered_map<LOCALIZATION_ENUM_KEY, string> localization_map;
	static unordered_map<string, SPEAK_ENUM_KEY> speak_enum_map;
	static unordered_map<SPEAK_ENUM_KEY, string> speak_map;
    static unordered_map<string, monster_index> monster_enum_map;
    static unordered_map<monster_index, string> monster_enum_reverse_map;
	static unordered_map<monster_index, string> monster_name_map;
	static unordered_map<monster_index, string> monster_description_map;
	static vector<TextHelper> help_command;
	static vector<TextHelper> help_pad_command;
	static vector<TextHelper> help_credit;
	static vector<TextHelper> help_wizard;
	static vector<TextHelper> help_character;
	static vector<int> helpline_character;
	static vector<TextHelper> help_gods;
	static vector<int> helpline_gods;

	static unordered_set<string> korean_verbs;
	static unordered_set<string> english_verbs;
	static unordered_set<string> english_article;

private:
    static D3DCOLOR getColorFromCode(const string& code);
    static D3DCOLOR parseMultiColorLine(const string& line, vector<TextHelper>& outVector, D3DCOLOR currentColor, int current_line, vector<int>* helpline);
    static pair<string, D3DCOLOR> parseColorTag(const string& line);
    static void initFileSimple(const string& path, const string& filename, vector<TextHelper>& saveVector, vector<int>* helpline);

    template<typename EnumType>
    static void initFile(const string& path, const string& filename, unordered_map<string, EnumType>& enum_map, int argument_num, function<void(EnumType, vector<string>, vector<string>)> func) {
        ifstream file(path + filename);
        if (!file) {
            string error_msg = "Error: Cannot open localization file: " + path + filename;
            return;
        }

        string line;
        vector<string> prev_values;
        prev_values.assign(argument_num, "");
        bool first_line = true;
        while (getline(file, line)) {
            if (first_line) {
                //BOM제거
                first_line = false;
                if (!line.empty() && static_cast<unsigned char>(line[0]) == 0xEF &&
                    line.size() >= 3 &&
                    static_cast<unsigned char>(line[1]) == 0xBB &&
                    static_cast<unsigned char>(line[2]) == 0xBF) {
                    line = line.substr(3); // BOM 제거
                }
            }
            istringstream iss(line);
            string key;
            vector<string> values;

            if (!getline(iss, key, ',')) continue;
            key.erase(key.find_last_not_of(" \t\r\n") + 1);

            if (enum_map.count(key) == 0) {
                string error_msg = "Warning: Unknown localization key: " + key;
                continue;
            }

            EnumType enum_key = enum_map[key];


            string value;
            int count = 0;
            size_t pos = 0, prev = 0;
            while (count < argument_num && (pos = line.find(',', prev)) != string::npos) {
                if (count == 0) {
                    prev = pos + 1;
                    ++count;
                    continue;
                }

                string val = line.substr(prev, pos - prev);
                val.erase(0, val.find_first_not_of(" \t\r\n"));
                val.erase(val.find_last_not_of(" \t\r\n") + 1);
                values.push_back(val);
                prev = pos + 1;
                ++count;
            }

            string last = line.substr(prev);
            last.erase(0, last.find_first_not_of(" \t\r\n"));
            last.erase(last.find_last_not_of(" \t\r\n") + 1);
            values.push_back(last);

            while (values.size() < argument_num) {
                values.push_back("");
            }


            func(enum_key, values, prev_values);
            for(int i = 0; i < argument_num; i++) {
                if(values[i] != "") {
                    prev_values[i] = values[i];
                }
            }
        }

        file.close();
    }



public:
    static string current_lang;

    static string baseLang(){return "ENG";};
    static void initLocalization();
	static void init(string type, bool init_);


	static string langString(string key);
	static string getNextLang(string cur);
	static string getCurrentFont();
	static const string& locString(LOCALIZATION_ENUM_KEY key);
	static const string& speakString(SPEAK_ENUM_KEY key);
	static const string& monString(monster_index key);
    static const string& monDecsriptionString(monster_index key);
	static const vector<TextHelper>& getHelpCommand(){return help_command;};
	static const vector<TextHelper>& getHelpPadCommand(){return help_pad_command;};
	static const vector<TextHelper>& getHelpCredit(){return help_credit;};
	static const vector<TextHelper>& getHelpWizard(){return help_wizard;};
	static const vector<TextHelper>& getHelpCharacter(){return help_character;};
	static int getHelpCharacterLine(int index);
	static const vector<TextHelper>& getHelpGods(){return help_gods;};
	static int getHelpGodsLine(int index);
    

    static const string& getMonsterEnumString(monster_index key);
    static monster_index getMonsterEnumKey(const string& str);
    static const string& getLocalizationEnumString(LOCALIZATION_ENUM_KEY key);
    static LOCALIZATION_ENUM_KEY getLocalizationEnumKey(const string& str);

	template<typename... Args>
	static std::string formatString(const std::string& template_str, Args... args) {
		std::vector<PlaceHolderHelper> values = { std::forward<Args>(args)...};
		return processTags(template_str, values);
	}

	template<typename... Args>
	static std::string formatString(monster_index template_key, Args... args) {
		std::string template_str = monString(template_key);
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
        if(template_str.size() == 0)
            return;
        if((template_str.back() == '.' || template_str.back() == '!' || template_str.back() == '?') && enter_ == false) {
            template_str.push_back(' '); //스페이스 보정
        }

        regex split_regex(R"(\{(\d+(?::[^{}]+)?)\}|\{([^{}\d][^{}]*\|[^{}]*)\})");
        std::regex placeholder_regex(R"(\{(\d+(?::[^{}]+)?)\})");
        std::regex randomholder_regex(R"(\{([^{}\d][^{}]*\|[^{}]*)\})");
        smatch match;
		std::vector<PlaceHolderHelper> values = { std::forward<Args>(args)...};
        std::sregex_token_iterator iter(template_str.begin(), template_str.end(), split_regex, {-1, 0});
        std::sregex_token_iterator end;
    

        while (iter != end) {
            std::string token = *iter;
            bool isEnd = (++iter) == end;
            if (std::regex_match(token, match, placeholder_regex)) {
                auto pair_placeholder = extractPlaceholder(token);
                if(!pair_placeholder.first.empty()) {
                    int index = stoi(pair_placeholder.first); 
                    if (index < values.size()) {
                        const PlaceHolderHelper& ph = values[index];
                        string value = (ph.key != LOC_NONE) ? locString(ph.key) : ph.name;
            
                        if (!pair_placeholder.second.empty()) {
                            string verb_ = verb(value, pair_placeholder.second, ph.plural, true);
                            if(!verb_.empty()) {
                                if(verb_.back() == ' ') {
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
            } else if (std::regex_match(token, match, randomholder_regex))  {
                // {A|B|C} 랜덤 선택 처리
                std::string token_inner = match[1].str();
                std::vector<std::string> options;
                std::stringstream ss(token_inner);
                std::string item;
                while (std::getline(ss, item, '|')) {
                    options.push_back(item);
                }
                std::string chosen = options[randA_nonlogic(options.size() - 1)];
                printlog(chosen, isEnd ? enter_ : false, log_, temp_, color_);
            } else {
                printlog(token,isEnd?enter_:false,log_,temp_,color_);
            }
        }
    }



private:
    static std::string processTags(const std::string& template_str, const vector<PlaceHolderHelper>& values);
    static std::string verb(const std::string& text, const std::string& verb, bool plural, bool only_verb);
    static string getCorrectParticle(const string& word, const string& opt1, const string& opt2);
    static string getIndefiniteArticle(const string& word,const string& opt1, const string& opt2);
    static pair<string, string> extractPlaceholder(const string& input);
};

#endif // __LOCALIIZATION_H__