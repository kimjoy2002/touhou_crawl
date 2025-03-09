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


// **ENUM ↔ 문자열 변환 맵 생성 함수**
std::unordered_map<std::string, LOCALIZATION_ENUM_KEY> createEnumMap() {
    std::unordered_map<std::string, LOCALIZATION_ENUM_KEY> map;
#define X(name) map[#name] = name;
    LOCALIZATION_ENUM_LIST
#undef X
    return map;
}

unordered_map<LOCALIZATION_ENUM_KEY, string> LocalzationManager::localization_map;
unordered_map<monster_index, string> LocalzationManager::monster_name_map;
unordered_map<string, LOCALIZATION_ENUM_KEY> LocalzationManager::localization_enum_map = createEnumMap();


void LocalzationManager::init(LOCALIZATION_TYPE type) {
	string filePath;

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

	ifstream file(filePath + "general.txt");
	if (!file) {
		string error_msg = "Error: Cannot open localization file: " + filePath + "general.txt";
		//::MessageBoxA(0, error_msg.c_str(), 0, 0);
		return;
	}

	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		string key, value;

		if (getline(iss, key, ',') && getline(iss, value)) {
			key.erase(key.find_last_not_of(" \t\r\n") + 1);
			value.erase(0, value.find_first_not_of(" \t\r\n"));

			// 자동 매핑된 ENUM 확인
			if (localization_enum_map.count(key)) {
				localization_map[localization_enum_map[key]] = value;
			} else {
				string error_msg = "Warning: Unknown localization key: " + key;
				//::MessageBoxA(0, error_msg.c_str(), 0, 0);
			}
		}
	}
	file.close();
}

string& LocalzationManager::locString(LOCALIZATION_ENUM_KEY key) {
	if(localization_map.find(key) != localization_map.end()) {
		return localization_map[key];
	}
	return localization_map[LOC_NONE];
}

// 태그를 처리하는 함수
string LocalzationManager::processTags(const string& template_str, const vector<string>& values) {
    string result = template_str;
    regex placeholder_regex("\\{(\\d+)\\}");
    smatch match;

    while (regex_search(result, match, placeholder_regex)) {
        int index = stoi(match[1].str());
        if (index < values.size()) {
            result.replace(match.position(), match.length(), values[index]);
        } else {
            result.replace(match.position(), match.length(), ""); 
        }
    }

    return result;
}

string& LocalzationManager::monString(monster_index key) {
	if(monster_name_map.find(key) != monster_name_map.end()) {
		return monster_name_map[key];
	}
	return monster_name_map[MON_REIMUYUKKURI];
}
