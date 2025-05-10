//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: localization.cpp
//
// 내용: 다국어
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "const.h"
#include "localization.h"
#include "item.h"
#include "god.h"
#include <iostream>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


string LocalzationManager::current_lang = "ENG";
OrderedMap<string, localizationInfo> LocalzationManager::localization_type;
unordered_map<string, LOCALIZATION_ENUM_KEY> LocalzationManager::localization_enum_map = createEnumMap();
unordered_map<LOCALIZATION_ENUM_KEY, string> LocalzationManager::localization_enum_reverse_map = createEnumReverseMap();
unordered_map<LOCALIZATION_ENUM_KEY, string> LocalzationManager::localization_map;
unordered_map<string, SPEAK_ENUM_KEY> LocalzationManager::speak_enum_map = createSpeakEnumMap();
unordered_map<SPEAK_ENUM_KEY, string> LocalzationManager::speak_map;
unordered_map<string, monster_index> LocalzationManager::monster_enum_map = createMonsterEnumMap();
unordered_map<monster_index, string> LocalzationManager::monster_enum_reverse_map = createMonsterEnumReverseMap();
unordered_map<monster_index, string> LocalzationManager::monster_name_map;
unordered_map<monster_index, string> LocalzationManager::monster_description_map;
vector<TextHelper> LocalzationManager::help_command;
vector<TextHelper> LocalzationManager::help_credit;
vector<TextHelper> LocalzationManager::help_wizard;
vector<TextHelper> LocalzationManager::help_character;
vector<int> LocalzationManager::helpline_character;
vector<TextHelper> LocalzationManager::help_gods;
vector<int> LocalzationManager::helpline_gods;

unordered_set<string> LocalzationManager::korean_verbs = {
	"은|는", "이|가", "을|를", "과|와", "으로|로", "이라|라", "이다|다", "이고|고"
};
unordered_set<string> LocalzationManager::english_verbs = {
	"is|are"
};
unordered_set<string> LocalzationManager::english_article = {
	"a|an"
};


void LocalzationManager::init(string type, bool init_) {
	current_lang = type;
	string filePath;

	if(init_) {
		localization_map.clear();
		speak_map.clear();
		monster_name_map.clear();
		monster_description_map.clear();
		help_command.clear();
		help_credit.clear();
	}
	std::transform(type.begin(), type.end(), type.begin(),
		[](unsigned char c) { return std::tolower(c); });
	
	filePath = "./data/localization/" +  type + "/";

	initFileSimple(filePath, "help.txt", help_command, nullptr);
	initFileSimple(filePath, "credit.txt", help_credit, nullptr);
	initFileSimple(filePath, "wizardhelp.txt", help_wizard, nullptr);
	initFileSimple(filePath, "character.txt", help_character, &helpline_character);
	initFileSimple(filePath, "gods.txt", help_gods, &helpline_gods);

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

D3DCOLOR LocalzationManager::getColorFromCode(const string& code) {
	if (code == "§p") return D3DCOLOR_RGBA(220, 150, 150, 255);     // pink
	if (code == "§r") return D3DCOLOR_RGBA(220, 80, 80, 255);     // Red
	if (code == "§R") return D3DCOLOR_RGBA(220, 20, 20, 255);     // *Red*
	if (code == "§g") return D3DCOLOR_RGBA(100, 200, 100, 255);   // Green
	if (code == "§G") return D3DCOLOR_RGBA(20, 220, 20, 255);   // *Green*
	if (code == "§y") return D3DCOLOR_RGBA(240, 200, 100, 255);   // Yellow
	if (code == "§s") return D3DCOLOR_RGBA(150, 150, 240, 255);   // Sky
	if (code == "§b") return D3DCOLOR_RGBA(80, 80, 240, 255);   // Blue
	if (code == "§B") return D3DCOLOR_RGBA(20, 20, 220, 255);   // *Blue*
	if (code == "§m") return D3DCOLOR_RGBA(200, 120, 220, 255);   // Magenta
	if (code == "§c") return D3DCOLOR_RGBA(100, 220, 220, 255);   // Cyan
	if (code == "§w") return D3DCOLOR_RGBA(255, 255, 255, 255);  // White
	return D3DCOLOR_RGBA(255, 255, 255, 255); // Default
}


D3DCOLOR LocalzationManager::parseMultiColorLine(const string& line, vector<TextHelper>& outVector, D3DCOLOR currentColor, int current_line, vector<int>* helpline) {
	size_t i = 0;
	string currentText;

	while (i < line.size()) {
		if(i + 2 < line.size() && line.substr(i, 2) == "§" && line.at(i+2) >= '0' && line.at(i+2) <= '9') {
			if(helpline) {
				//숫자 = 북마크
				if(i + 3 < line.size() && line.at(i+3) >= '0' && line.at(i+3) <= '9') {
					int val = stoi(line.substr(i+2, 2));
					while((*helpline).size() <= val)
						(*helpline).push_back(0);
					(*helpline)[val] = current_line;
					i += 4;
				}
				else {
					int val = 0;
					try {
						val = stoi(line.substr(i+2, 1));
					} catch (...) {
					}
					while((*helpline).size() <= val)
						(*helpline).push_back(0);
					(*helpline)[val] = current_line;
					i += 3;
				}
			}
		}
		else if (i + 2 < line.size() && line.substr(i, 2) == "§") {
			if (!currentText.empty()) {
				outVector.emplace_back(currentText, false, currentColor);
				currentText.clear();
			}
			if(i + 4 < line.size() && line.at(i+2) == '_') { //신 전용 색깔
				int val = 0;
				try {
					val = stoi(line.substr(i+3, 2));
				} catch (...) {
				}
				currentColor = GetGodColor((god_type)val);
				i += 5;
			}
			else {
				string tag = line.substr(i, 3); 
				currentColor = getColorFromCode(tag);
				i += 3;
			}
		} else {
			currentText += line[i++];
		}
	}

	outVector.emplace_back(currentText, true, currentColor);
	return currentColor;
}

void LocalzationManager::initLocalization() {
	string filepath = "./data/localization/language.txt";
	ifstream file(filepath);
	if (file) {
		string line;
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

            vector<string> tokens;
            size_t start = 0, end;
            while ((end = line.find(",", start)) != string::npos) {
                tokens.push_back(line.substr(start, end - start));
                start = end + 1;
            }
            tokens.push_back(line.substr(start)); // 마지막 항목

            if (tokens.size() >= 3) {
                localization_type.insert(tokens[0], localizationInfo{tokens[1], tokens[2]});
            }
		}
	}
	if(localization_type.empty()) {
		//기본값
		localization_type.insert("ENG", {"English", "D2Coding"});
		localization_type.insert("KOR", {"한국어", "D2Coding"});
		if(!file) {
			std::ofstream outfile(filepath, std::ios::binary);
			if (outfile.is_open()) {
				// UTF-8 BOM 쓰기
				unsigned char bom[] = {0xEF, 0xBB, 0xBF};
				outfile.write(reinterpret_cast<const char*>(bom), sizeof(bom));
				
				for (auto it : localization_type.ordered_entries()) {
                    outfile << it.first << "," << it.second.name << "," << it.second.font << "\n";
				}
				outfile.close();
			}
		}
	}	

}

void LocalzationManager::initFileSimple(const string& path, const string& filename, vector<TextHelper>& saveVector, vector<int>* helpline) {
	ifstream file(path + filename);
	if (!file) {
		return;
	}

	saveVector.clear();
	string line;
	bool first_line = true;
	D3DCOLOR color_ = CL_normal;
	int current_line = 0;
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

		color_ = parseMultiColorLine(line, saveVector, color_, current_line, helpline);
		current_line++;
	}
}

string LocalzationManager::langString(string key) {
	return localization_type.find(key).name;
}

string LocalzationManager::getNextLang(string cur) {
	bool next_ = false;
	string first_;
	for(pair<string, localizationInfo> pair_ : localization_type.ordered_entries()) {
		if(first_.empty()){
			first_ = pair_.first;
		}
		if(next_) {
			return pair_.first;
		}
		if(pair_.first == cur) {
			next_ = true;
		}
	}
	return first_;
}
string LocalzationManager::getCurrentFont() {
	return localization_type.find(current_lang).font;
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

const string& LocalzationManager::getMonsterEnumString(monster_index key) {
	if (monster_enum_reverse_map.find(key) != monster_enum_reverse_map.end()) {
		return monster_enum_reverse_map[key];
	}
	return monster_enum_reverse_map[MON_NONE_MONSTER];
}

monster_index LocalzationManager::getMonsterEnumKey(const string& str) {
	if (monster_enum_map.find(str) != monster_enum_map.end()) {
		return monster_enum_map[str];
	}
	return MON_NONE_MONSTER;
}

const string& LocalzationManager::getLocalizationEnumString(LOCALIZATION_ENUM_KEY key) {
	if (localization_enum_reverse_map.find(key) != localization_enum_reverse_map.end()) {
		return localization_enum_reverse_map[key];
	}
	return localization_enum_reverse_map[LOC_NONE];
}

LOCALIZATION_ENUM_KEY LocalzationManager::getLocalizationEnumKey(const string& str) {
	if (localization_enum_map.find(str) != localization_enum_map.end()) {
		return localization_enum_map[str];
	}
	return LOC_NONE;
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

int LocalzationManager::getHelpCharacterLine(int index) {
	if(helpline_character.size() > index) {
		return helpline_character[index];
	} else {
		return 0;
	}
}
int LocalzationManager::getHelpGodsLine(int index) {
	if(helpline_gods.size() > index) {
		return helpline_gods[index];
	} else {
		return 0;
	}
}

string LocalzationManager::getCorrectParticle(const string& word, const string& opt1, const string& opt2) {
    if (word.empty()) return opt1;

    wstring u32str = ConvertUTF8ToUTF16(word);
    for (auto it = u32str.rbegin(); it != u32str.rend(); ++it) {
        wchar_t lastChar = *it;
        if (lastChar == U'\0') continue; // 널 문자 건너뜀
		if (lastChar < 0xAC00 || lastChar > 0xD7A3) {
			return opt1; 
		}

		int localCode = lastChar - 0xAC00; // 가~ 이후
		int jongCode = localCode % 28;

		if (jongCode == 0)
			return opt2;

		if (opt1 == "으" && opt2 == "로")
		{
			if (jongCode == 8) // ㄹ 종성 예외 처리
				return opt2;
		}
   		return opt1;
	}
	return opt1;
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