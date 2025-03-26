//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: localization.cpp
//
// 내용: 다국어
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "localization.h"
#include <iostream>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>


LOCALIZATION_TYPE LocalzationManager::current_lang = LOCALIZATION_TYPE_ENG;
unordered_map<string, LOCALIZATION_ENUM_KEY> LocalzationManager::localization_enum_map = createEnumMap();
unordered_map<LOCALIZATION_ENUM_KEY, string> LocalzationManager::localization_map;
unordered_map<string, SPEAK_ENUM_KEY> LocalzationManager::speak_enum_map = createSpeakEnumMap();
unordered_map<SPEAK_ENUM_KEY, string> LocalzationManager::speak_map;
unordered_map<string, monster_index> LocalzationManager::monster_enum_map = createMonsterEnumMap();
unordered_map<monster_index, string> LocalzationManager::monster_name_map;
unordered_map<monster_index, string> LocalzationManager::monster_description_map;

unordered_set<string> LocalzationManager::korean_verbs = {
	"은|는", "이|가", "을|를", "과|와", "으로|로", "이라|라", "이다|다", "이고|고"
};
unordered_set<string> LocalzationManager::english_verbs = {
	"is|are"
};
unordered_set<string> LocalzationManager::english_article = {
	"a|an"
};


string getLocalizationString(LOCALIZATION_TYPE type) {
	switch(type) 
	{
	case LOCALIZATION_TYPE_ENG:
	default:
		return "ENG";
	case LOCALIZATION_TYPE_KOR:
		return "KOR";
	}
}

void LocalzationManager::init(LOCALIZATION_TYPE type) {
	current_lang = type;
	string filePath;

	localization_map.clear();
	speak_map.clear();
	monster_name_map.clear();
	monster_description_map.clear();
	
	switch (type)
	{
	case LOCALIZATION_TYPE_ENG:
		filePath = "./data/localization/eng/";
		break;
	case LOCALIZATION_TYPE_KOR:
		filePath = "./data/localization/kor/";
		break;
	default:
		break;
	}

	initFile<LOCALIZATION_ENUM_KEY>(filePath, "general.txt", localization_enum_map, 1, [](LOCALIZATION_ENUM_KEY key, vector<string> values, vector<string> prev_values) {
		localization_map[key] = values[0];
		replaceAll(localization_map[key], "\\n", "\n");
	});

	initFile<SPEAK_ENUM_KEY>(filePath, "speak.txt", speak_enum_map, 1, [](SPEAK_ENUM_KEY key, vector<string> values, vector<string> prev_values) {
		speak_map[key] = values[0];
	});

	initFile<monster_index>(filePath, "monsters.txt", monster_enum_map, 2, [](monster_index key, vector<string> values, vector<string> prev_values) {
		monster_name_map[key] = (!values[0].empty())?values[0]:prev_values[0];
		monster_description_map[key] = (!values[1].empty())?values[1]:prev_values[1];
		replaceAll(monster_description_map[key], "\\n", "\n");
	});
}

const string& LocalzationManager::locString(LOCALIZATION_ENUM_KEY key) { //TODO) {} 문법이 이쓰면 formatString으로 바꾸기
	if(localization_map.find(key) != localization_map.end()) {
		return localization_map[key];
	}
	return localization_map[LOC_NONE];
}

const string& LocalzationManager::speakString(SPEAK_ENUM_KEY key) {
	if(speak_map.find(key) != speak_map.end()) {
		return speak_map[key];
	}
	return speak_map[SPEAK_NORMAL];
}


// 태그를 처리하는 함수
string LocalzationManager::processTags(const string& template_str, const vector<PlaceHolderHelper>& values) {
    string result = template_str;
    regex placeholder_regex(R"(\{(\d+(?::[^}]+)?)\}|\{([^0-9{:|}]+(?:\|[^0-9{:|}]+)+)\})");
    smatch match;

    while (regex_search(result, match, placeholder_regex)) {
		string replacement;
		if (match[1].matched) {
			auto pair_placeholder = extractPlaceholder("{" + match[1].str() + "}");
			int index = stoi(pair_placeholder.first);
			if(index < values.size()) {
				const PlaceHolderHelper& ph = values[index];
				string value = (ph.key != LOC_NONE) ? locString(ph.key) : ph.name;

				if (!pair_placeholder.second.empty()) {
					replacement = verb(value, pair_placeholder.second, ph.plural, false);
				} else {
					replacement = value;
				}
			}
		} else if(match[2].matched) {
			std::string token_inner = match[2].str();
			std::vector<std::string> options;
			std::stringstream ss(token_inner);
			std::string item;
			while (std::getline(ss, item, '|')) {
				options.push_back(item);
			}
			replacement = options[randA_nonlogic(options.size() - 1)];
		}

		result.replace(match.position(), match.length(), replacement);
    }

    return result;
}

std::string LocalzationManager::verb(const std::string& text, const std::string& verb, bool plural, bool only_verb) {
	//text뒤에 예약 verb가 있으면 자동으로 변환해서 뒤에 붙여준다.
	//만약 존재하지않는다면 그냥 뒤에 verb를 붙임
	//예약verb의 종류
	//뒤에 붙는거 "은|는", "이|가", "을|를", "와|과", "is|are"
	//앞에 붙는거 "a|an"

	//참고로 위에 아무것도 안매칭되면 그냥 뒤에 붙이고
	//|기준으로 앞뒤가 바뀌어도 동작해야


	//예시1) text=사과 verb=은|는 -> return "사과는";
	//예시2) text=사람 verb=을|를 -> return "사람을";
	//예시3) text=동물 verb=를|을 -> return "동물을";
	//예시4) text=apple verb=a|an -> return "an apple";
	//예시5) text=의자 verb=의 -> return "의자의";
	//예시6) text=테스트 verb=바|보 -> return "테스트바|보";


	size_t delimiter = verb.find('|');
	if (delimiter == string::npos) {
		return only_verb?verb:text + verb;
	}

	string opt1 = verb.substr(0, delimiter);
	string opt2 = verb.substr(delimiter + 1);

	if (korean_verbs.count(verb)) {
		return only_verb?getCorrectParticle(text, opt1, opt2): text + getCorrectParticle(text, opt1, opt2);
	} else if(korean_verbs.count(opt2 + "|" + opt1)) {
		return only_verb?getCorrectParticle(text, opt2, opt1):text + getCorrectParticle(text, opt2, opt1);
	}

	if (english_article.count(verb)) {
		return only_verb?getIndefiniteArticle(text, opt1, opt2) + " ":getIndefiniteArticle(text, opt1, opt2) + " " + text;
	} else if(english_article.count(opt2 + "|" + opt1)) {
		return only_verb?getIndefiniteArticle(text, opt2, opt1) + " ": getIndefiniteArticle(text, opt2, opt1) + " " + text;
	}
	
	if (english_verbs.count(verb)) {
		return only_verb?" " + (plural?opt2:opt1):text + " " + (plural?opt2:opt1);
	} else if(english_verbs.count(opt2 + "|" + opt1)) {
		return only_verb?" " + (plural?opt1:opt2): text + " " + (plural?opt1:opt2);
	}

	return only_verb?verb:text + verb;
}
const string& LocalzationManager::monString(monster_index key) {
	if(monster_name_map.find(key) != monster_name_map.end()) {
		return monster_name_map[key];
	}
	return monster_name_map[MON_REIMUYUKKURI];
}
const string& LocalzationManager::monDecsriptionString(monster_index key) {
	if(monster_description_map.find(key) != monster_description_map.end()) {
		return monster_description_map[key];
	}
	return monster_description_map[MON_REIMUYUKKURI];
}
string LocalzationManager::getCorrectParticle(const string& word, const string& opt1, const string& opt2) {
    if (word.empty()) return opt1;

    unsigned char first = word[word.length() - 2];
    unsigned char second = word[word.length() - 1];

    if (first < 0xB0 || first > 0xC8) {
        return opt1;
    }

    int index = (first - 0xB0) * 94 + (second - 0xA1);

    if (index < 0 || index >= 2350) {
        return opt1; 
    }

    int cho = index / (21 * 28);
    int jung = (index % (21 * 28)) / 28;
    int jong = index % 28;

    return jong?opt2:opt1;
}

string LocalzationManager::getIndefiniteArticle(const string& word,const string& opt1, const string& opt2) {
    char firstChar = tolower(word[0]);
    return (firstChar == 'a' || firstChar == 'e' || firstChar == 'i' || firstChar == 'o' || firstChar == 'u') ? opt2 : opt1;
}

pair<string, string> LocalzationManager::extractPlaceholder(const string& input) {
	if (input.size() < 2 || input.front() != '{' || input.back() != '}') {
		return {"", ""};
	}

	string content = input.substr(1, input.size() - 2);

	size_t colonPos = content.find(':');

	if (colonPos == string::npos) {
		return {content, ""};
	} else {
		return {content.substr(0, colonPos), content.substr(colonPos + 1)};
	}
}