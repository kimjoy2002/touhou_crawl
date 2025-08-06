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
unordered_map<string, SPEAK_ENUM_KEY> LocalzationManager::speak_enum_map = createSpeakEnumMap();
unordered_map<string, monster_index> LocalzationManager::monster_enum_map = createMonsterEnumMap();
unordered_map<monster_index, string> LocalzationManager::monster_enum_reverse_map = createMonsterEnumReverseMap();

unordered_set<string> LocalzationManager::korean_verbs = {
	"은|는", "이|가", "을|를", "과|와", "으로|로", "이라|라", "이다|다", "이고|고"
};
unordered_set<string> LocalzationManager::english_verbs = {
	"is|are"
};
unordered_set<string> LocalzationManager::english_article = {
	"a|an"
};

OrderedMap<string, shared_ptr<LocalzationManager::LocalzationData>> LocalzationManager::localizationVector;

void LocalzationManager::allinit(string type) {
	for (auto it : localization_type.ordered_entries()) {
		LocalzationManager::init(it.first, true);
	}
	current_lang = type;
}

void LocalzationManager::init(string type, bool init_) {
	string filePath;
	string type_ = type;


	if(!localizationVector.has(type))  {
		localizationVector.insert(type, make_shared<LocalzationManager::LocalzationData>());
	}
	if(init_) {
		localizationVector.find(type)->localization_map.clear();
		localizationVector.find(type)->speak_map.clear();
		localizationVector.find(type)->monster_name_map.clear();
		localizationVector.find(type)->monster_description_map.clear();
		localizationVector.find(type)->help_command.clear();
		localizationVector.find(type)->help_credit.clear();
	}
	
	std::transform(type_.begin(), type_.end(), type_.begin(),
		[](unsigned char c) { return std::tolower(c); });
	
	filePath = "./data/localization/" +  type_ + "/";

	initFileSimple(filePath, "help.txt", localizationVector.find(type)->help_command, nullptr);
	initFileSimple(filePath, "help_pad.txt", localizationVector.find(type)->help_pad_command, nullptr);
	initFileSimple(filePath, "credit.txt", localizationVector.find(type)->help_credit, nullptr);
	initFileSimple(filePath, "wizardhelp.txt", localizationVector.find(type)->help_wizard, nullptr);
	initFileSimple(filePath, "character.txt", localizationVector.find(type)->help_character, &localizationVector.find(type)->helpline_character);
	initFileSimple(filePath, "gods.txt", localizationVector.find(type)->help_gods, &localizationVector.find(type)->helpline_gods);
	initFileArtifact(filePath, "artifact.txt", localizationVector.find(type)->randart_name_base, localizationVector.find(type)->randart_name_word);
	parseWikiFile(filePath, "wiki.txt",	localizationVector.find(type)->wiki_redirect, localizationVector.find(type)->wiki_map, localizationVector.find(type)->wikiline, localizationVector.find(type)->wiki_id_matching);

	initFile<LOCALIZATION_ENUM_KEY>(filePath, "general.txt", localization_enum_map, 1, [type](LOCALIZATION_ENUM_KEY key, vector<string> values, vector<string> prev_values) {
		localizationVector.find(type)->localization_map[key] = values[0];
		replaceAll(localizationVector.find(type)->localization_map[key], "\\n", "\n");
	});

	initFile<SPEAK_ENUM_KEY>(filePath, "speak.txt", speak_enum_map, 1, [type](SPEAK_ENUM_KEY key, vector<string> values, vector<string> prev_values) {
		localizationVector.find(type)->speak_map[key] = values[0];
	});

	initFile<monster_index>(filePath, "monsters.txt", monster_enum_map, 2, [type](monster_index key, vector<string> values, vector<string> prev_values) {
		localizationVector.find(type)->monster_name_map[key] = (!values[0].empty())?values[0]:prev_values[0];
		localizationVector.find(type)->monster_description_map[key] = (!values[1].empty())?values[1]:prev_values[1];
		replaceAll(localizationVector.find(type)->monster_description_map[key], "\\n", "\n");
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



void LocalzationManager::initFileArtifact(const string& path, const string& filename, vector<string>& baseVector, vector<string>& wordVector) {
	ifstream file(path + filename);
	if (!file) {
		return;
	}

	baseVector.clear();
	wordVector.clear();
	string line;
	bool first_line = true;
	int current_line = 0;
	int type = 0;
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
		if(line == "--BASE") {
			type = 1;
		} else if (line == "--WORD") {
			type = 2;
		} else if(type == 1) {
			baseVector.push_back(line);
		} else if(type == 2) {
			wordVector.push_back(line);
		}

		current_line++;
	}
}


void LocalzationManager::parsingWikiInfo(string key, string content, unordered_map<string, shared_ptr<vector<WikiHelper>>>& wiki_map, unordered_map<string, int>& wikiline, int& current_line, BiMap& wiki_id_matching) {
	if (!key.empty()) {
		wikiline[key] = current_line;
		current_line+=3; //이름앞뒤
		istringstream ss(content);
		string inner_line;
		shared_ptr<vector<WikiHelper>> parts = make_shared<vector<WikiHelper>>();
		while (getline(ss, inner_line)) {
			size_t pos = 0;
			while (pos < inner_line.size()) {
				if (inner_line[pos] == '{') {
					size_t end = inner_line.find('}', pos);
					if (end != string::npos) {
						string keyword = inner_line.substr(pos + 1, end - pos - 1);
						parts->push_back({ keyword, false, CL_green});
						pos = end + 1;
					} else {
						// 잘못된 형식, 무시
						break;
					}
				} else {
					size_t next = inner_line.find('{', pos);
					string normal_text = inner_line.substr(pos, next - pos);
					parts->push_back({ normal_text, false, CL_normal});
					if (next == string::npos)
						break;
					pos = next;
				}
			}
			// 줄바꿈 구분
			if (!parts->empty()) {
				parts->back().enter = true;
				current_line++;
			}
		}
		int id_ = wiki_id_matching.size();
		wiki_id_matching.insert(id_, key);
		wiki_map[key] = parts;
		current_line+=wiki_enter;
	}
}


void LocalzationManager::parseWikiFile(const string& path, const string& filename,
	unordered_map<string, string>& wiki_redirect,
	unordered_map<string, shared_ptr<vector<WikiHelper>>>& wiki_map,
	unordered_map<string, int>& wikiline,
	BiMap& wiki_id_matching)
{
	ifstream file(path + filename);
	if (!file) return;

	string line;
	bool first_line = true;

	string current_key;
	string current_content;
	vector<string> current_redirects;

	int type_ = 0; //1=키, 2=컨텐츠
	int current_line = 0;
	while (getline(file, line)) {
		if (first_line) {
			first_line = false;
			if (!line.empty() && static_cast<unsigned char>(line[0]) == 0xEF &&
				line.size() >= 3 &&
				static_cast<unsigned char>(line[1]) == 0xBB &&
				static_cast<unsigned char>(line[2]) == 0xBF) {
				line = line.substr(3); //BOM제거
			}
		}

		if (startsWith(line, "==")) {
			if(type_==0) {
				type_ = 1;
			}
			else if(type_ == 1)
			{
				type_ = 2;

			}
			else  if(type_ == 2) {
				type_ = 1;
				parsingWikiInfo(current_key, current_content, wiki_map, wikiline, current_line, wiki_id_matching);
				for(auto redirect_ : current_redirects) {
					wiki_redirect[redirect_] = current_key;
				}
				current_key.clear();
				current_content.clear();
				current_redirects.clear();
			}
			continue;
		} else if(type_ == 1) {

			if (line.find("//") == string::npos && line.find('(') != string::npos && line.find(')') != string::npos) {
				size_t lparen = line.find('(');
				size_t rparen = line.find(')');
				if (lparen != string::npos && rparen != string::npos && rparen > lparen) {
					string key = line.substr(0, lparen);
					key = trim(key);
					current_key = key;

					string redirect_list = line.substr(lparen + 1, rparen - lparen - 1);
					istringstream rs(redirect_list);
					string redirect;
					while (getline(rs, redirect, ',')) {
						current_redirects.push_back(trim(redirect));
					}
				}
			}
			else {
				current_key = trim(line);
			}
		}
		else if(type_ == 2) {
			if(!line.empty())
				current_content += line + "\n";
		}
	}
	parsingWikiInfo(current_key, current_content, wiki_map, wikiline, current_line, wiki_id_matching);
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

string LocalzationManager::getPrevLang(string cur) {
	string prev_;
	for(pair<string, localizationInfo> pair_ : localization_type.ordered_entries()) {
		if(pair_.first == cur && !prev_.empty()){
			return prev_;
		}
		prev_ = pair_.first;
	}
	return prev_;
}

string LocalzationManager::getCurrentFont() {
	return localization_type.find(current_lang).font;
}

const string& LocalzationManager::locString(LOCALIZATION_ENUM_KEY key) { //TODO) {} 문법이 이쓰면 formatString으로 바꾸기
	if(localizationVector.find(current_lang)->localization_map.find(key) != localizationVector.find(current_lang)->localization_map.end()) {
		return localizationVector.find(current_lang)->localization_map[key];
	}
	if(baseLang() != current_lang) {
		if(localizationVector.find(baseLang())->localization_map.find(key) != localizationVector.find(baseLang())->localization_map.end()) {
			return localizationVector.find(baseLang())->localization_map[key];
		}
	}
	return localizationVector.find(current_lang)->localization_map[LOC_NONE];
}


const string& LocalzationManager::locString(string lang, LOCALIZATION_ENUM_KEY key) {
	if(lang == "") {
		lang = current_lang;
	}
	if(localizationVector.find(lang)->localization_map.find(key) != localizationVector.find(lang)->localization_map.end()) {
		return localizationVector.find(lang)->localization_map[key];
	}
	if(baseLang() != lang) {
		if(localizationVector.find(baseLang())->localization_map.find(key) != localizationVector.find(baseLang())->localization_map.end()) {
			return localizationVector.find(baseLang())->localization_map[key];
		}
	}
	return localizationVector.find(lang)->localization_map[LOC_NONE];
}

string LocalzationManager::artifactString(string lang, int artifact_guid) {
	if(lang == "") {
		lang = current_lang;
	}
	int val1 = (artifact_guid >> 16) & 0xFFFF; // 상위 16비트
	int val2 = artifact_guid & 0xFFFF;         // 하위 16비트
	
	string text;
	if(localizationVector.find(lang)->randart_name_base.size() > 0 && localizationVector.find(lang)->randart_name_word.size() > 0) {
		int index_ = val1%localizationVector.find(lang)->randart_name_base.size();
		int index2_ = val2%localizationVector.find(lang)->randart_name_word.size();
		string val1_ = localizationVector.find(lang)->randart_name_base[index_];
		string val2_ = localizationVector.find(lang)->randart_name_word[index2_];
		text = formatString(val1_, val2_);		
		return text;
	}
	else if(localizationVector.find(baseLang())->randart_name_base.size() > 0 && localizationVector.find(baseLang())->randart_name_word.size() > 0) {
		int index_ = val1%localizationVector.find(baseLang())->randart_name_base.size();
		int index2_ = val2%localizationVector.find(baseLang())->randart_name_word.size();
		string val1_ = localizationVector.find(baseLang())->randart_name_base[index_];
		string val2_ = localizationVector.find(baseLang())->randart_name_word[index2_];
		text = formatString(val1_, val2_);		
		return text;
	}
	return "";
}


const string& LocalzationManager::speakString(SPEAK_ENUM_KEY key) {
	if(localizationVector.find(current_lang)->speak_map.find(key) != localizationVector.find(current_lang)->speak_map.end()) {
		return localizationVector.find(current_lang)->speak_map[key];
	}
	if(localizationVector.find(baseLang())->speak_map.find(key) != localizationVector.find(baseLang())->speak_map.end()) {
		return localizationVector.find(baseLang())->speak_map[key];
	}
	return localizationVector.find(current_lang)->speak_map[SPEAK_NORMAL];
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
    string result;
    string::const_iterator searchStart = template_str.cbegin();
    regex placeholder_regex(R"(\{(\d+(?::[^}]+)?)\}|\{([^0-9{:|}]+(?:\|[^0-9{:|}]+)+)\})");
    smatch match;

    while (regex_search(searchStart, template_str.end(), match, placeholder_regex)) {
		result.append(searchStart, match[0].first);

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
			if (!options.empty()) {
				replacement = options[randA_nonlogic(options.size() - 1)];
			}
		}

        result += replacement;
        searchStart = match.suffix().first;
    }
    result.append(searchStart, template_str.cend());
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
	if(localizationVector.find(current_lang)->monster_name_map.find(key) != localizationVector.find(current_lang)->monster_name_map.end()) {
		return localizationVector.find(current_lang)->monster_name_map[key];
	}
	if(localizationVector.find(baseLang())->monster_name_map.find(key) != localizationVector.find(baseLang())->monster_name_map.end()) {
		return localizationVector.find(baseLang())->monster_name_map[key];
	}
	return localizationVector.find(current_lang)->monster_name_map[MON_REIMUYUKKURI];
}
const string& LocalzationManager::monString(string lang, monster_index key) {
	if(lang == "") {
		lang = current_lang;
	}
	if(localizationVector.find(lang)->monster_name_map.find(key) != localizationVector.find(lang)->monster_name_map.end()) {
		return localizationVector.find(lang)->monster_name_map[key];
	}
	if(lang != baseLang()) {
		if(localizationVector.find(baseLang())->monster_name_map.find(key) != localizationVector.find(baseLang())->monster_name_map.end()) {
			return localizationVector.find(baseLang())->monster_name_map[key];
		}
	}
	return localizationVector.find(lang)->monster_name_map[MON_REIMUYUKKURI];
}
const string& LocalzationManager::monDecsriptionString(monster_index key) {
	if(localizationVector.find(current_lang)->monster_description_map.find(key) != localizationVector.find(current_lang)->monster_description_map.end()) {
		return localizationVector.find(current_lang)->monster_description_map[key];
	}
	if(localizationVector.find(baseLang())->monster_description_map.find(key) != localizationVector.find(baseLang())->monster_description_map.end()) {
		return localizationVector.find(baseLang())->monster_description_map[key];
	}
	return localizationVector.find(current_lang)->monster_description_map[MON_REIMUYUKKURI];
}
void LocalzationManager::printWiki() {
	shared_ptr<LocalzationManager::LocalzationData> langData = nullptr;
	if(localizationVector.has(current_lang)) {
		langData = localizationVector.find(current_lang);
	}
	if(langData == nullptr && localizationVector.has(baseLang())) {
		langData = localizationVector.find(baseLang());
	}
	if(langData != nullptr) {
		int id_ = 1;
		langData->wiki_id_matching.clear();
		langData->wikiline.clear();
		for(auto& wiki_entry : langData->wiki_map) {
			langData->wiki_id_matching.insert(id_++, wiki_entry.first);
		}

		int current_line = 0;
		for(auto& wiki_entry : langData->wiki_map) {
			langData->wikiline[wiki_entry.first] = current_line;
			printsub("===============================",true,CL_help);
			printsub(wiki_entry.first,true,CL_normal);
			printsub("===============================",true,CL_help);
			printsub("",true,CL_normal);
			current_line+=4;
			if(wiki_entry.second != nullptr) {
				for(auto& wiki_value : *wiki_entry.second) {
					if(wiki_value.color == CL_normal) {
						printsub(wiki_value.text,wiki_value.enter,wiki_value.color);
					} else {
						int redirect_ = langData->wiki_id_matching.getId(wiki_value.text);
						if(redirect_ > 0) {
							redirect_ += 1000;
							printsub(wiki_value.text,wiki_value.enter,wiki_value.color, redirect_);
						}
						else {
							printsub(wiki_value.text,wiki_value.enter, CL_small_danger);
						}
					}
					if(wiki_value.enter)
						current_line++;
				}
			}
			for(int i = 0; i < wiki_enter; i++)
				printsub("",true,CL_normal);
			current_line+=wiki_enter;
		}
	}
}
int LocalzationManager::getWikiLine(int id) {
	shared_ptr<LocalzationManager::LocalzationData> langData = nullptr;
	if(localizationVector.has(current_lang)) {
		langData = localizationVector.find(current_lang);
	}
	if(langData == nullptr && localizationVector.has(baseLang())) {
		langData = localizationVector.find(baseLang());
	}
	if(langData != nullptr) {
		string redirect_ = langData->wiki_id_matching.getStr(id);
		if(!redirect_.empty() && langData->wikiline.find(redirect_) != langData->wikiline.end()) {
			return langData->wikiline[redirect_];
		}
	}
	return -1;
}
int LocalzationManager::getHelpCharacterLine(int index) {
	if(localizationVector.find(current_lang)->helpline_character.size() > index) {
		return localizationVector.find(current_lang)->helpline_character[index];
	} else {
		return 0;
	}
}
int LocalzationManager::getHelpGodsLine(int index) {
	if(localizationVector.find(current_lang)->helpline_gods.size() > index) {
		return localizationVector.find(current_lang)->helpline_gods[index];
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