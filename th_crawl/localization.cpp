//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: localization.cpp
//
// ����: �ٱ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "localization.h"
#include <iostream>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>


// **ENUM �� ���ڿ� ��ȯ �� ���� �Լ�**
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

unordered_set<string> LocalzationManager::korean_verbs = {
	"��|��", "��|��", "��|��", "��|��"
};
unordered_set<string> LocalzationManager::english_verbs = {
	"is|are"
};
unordered_set<string> LocalzationManager::english_article = {
	"a|an"
};

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

			// �ڵ� ���ε� ENUM Ȯ��
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


// �±׸� ó���ϴ� �Լ�
string LocalzationManager::processTags(const string& template_str, const vector<PlaceHolderHelper>& values) {
    string result = template_str;
    regex placeholder_regex(R"(\{(\d+)(?::([^}]+))?\})");
    smatch match;

    while (regex_search(result, match, placeholder_regex)) {
		int index = stoi(match[1].str());
		string replacement;

		if (index < values.size()) {
			const PlaceHolderHelper& ph = values[index];
			string value = (ph.key != LOC_NONE) ? locString(ph.key) : ph.name;

			if (match[2].matched) {
				replacement = verb(value, match[2].str(), ph.plural);
			} else {
				replacement = value;
			}
		}

		result.replace(match.position(), match.length(), replacement);
    }

    return result;
}

std::string LocalzationManager::verb(const std::string& text, const std::string& verb, bool plural) {
	//text�ڿ� ���� verb�� ������ �ڵ����� ��ȯ�ؼ� �ڿ� �ٿ��ش�.
	//���� ���������ʴ´ٸ� �׳� �ڿ� verb�� ����
	//����verb�� ����
	//�ڿ� �ٴ°� "��|��", "��|��", "��|��", "��|��", "is|are"
	//�տ� �ٴ°� "a|an"

	//����� ���� �ƹ��͵� �ȸ�Ī�Ǹ� �׳� �ڿ� ���̰�
	//|�������� �յڰ� �ٲ� �����ؾ�


	//����1) text=��� verb=��|�� -> return "�����";
	//����2) text=��� verb=��|�� -> return "�����";
	//����3) text=���� verb=��|�� -> return "������";
	//����4) text=apple verb=a|an -> return "an apple";
	//����5) text=���� verb=�� -> return "������";
	//����6) text=�׽�Ʈ verb=��|�� -> return "�׽�Ʈ��|��";


	size_t delimiter = verb.find('|');
	if (delimiter == string::npos) {
		return text + verb;
	}

	string opt1 = verb.substr(0, delimiter);
	string opt2 = verb.substr(delimiter + 1);

	if (korean_verbs.count(verb)) {
		return text + getCorrectParticle(text, opt1, opt2);
	} else if(korean_verbs.count(opt2 + "|" + opt1)) {
		return text + getCorrectParticle(text, opt2, opt1);
	}

	if (english_verbs.count(verb)) {
		return  getIndefiniteArticle(text, opt1, opt2) + " " + text;
	} else if(english_verbs.count(opt2 + "|" + opt1)) {
		return  getIndefiniteArticle(text, opt2, opt1) + " " + text;
	}
	
	if (english_article.count(verb)) {
		return text + "" + (plural?opt2:opt1);
	} else if(english_article.count(opt2 + "|" + opt1)) {
		return text + "" + (plural?opt1:opt2);
	}

	return text + verb;
}
string& LocalzationManager::monString(monster_index key) {
	if(monster_name_map.find(key) != monster_name_map.end()) {
		return monster_name_map[key];
	}
	return monster_name_map[MON_REIMUYUKKURI];
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