//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: help.cpp
//
// 내용: 도움말
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"
#include "display.h"
#include "key.h"
#include "note.h"


extern HANDLE mutx;
extern display_manager DisplayManager;

static void SetWikiSearchPrompt(const string& text, D3DCOLOR color = CL_normal)
{
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.sub_text_prompt = text;
	DisplayManager.sub_text_prompt_color = color;
	ReleaseMutex(mutx);
}

static bool InputWikiSearch(char command, string& query)
{
	query.clear();
	int history_pos = (int)you.wiki_search_history.size();
	string draft;
	vector<string> completions;
	size_t completion_pos = 0;
	bool completion_active = false;
	SetWikiSearchPrompt(string(1, command));
	while(true) {
		InputedKey inputedKey;
		int key = waitkeyinput(inputedKey, true);
		if(key == VK_ESCAPE || key == GVK_BUTTON_B || key == GVK_BUTTON_B_LONG || (key == -1 && inputedKey.isRightClick())) {
			SetWikiSearchPrompt("");
			return false;
		}
		if(key == VK_RETURN || key == GVK_BUTTON_A || key == GVK_BUTTON_A_LONG) {
			SetWikiSearchPrompt("");
			return true;
		}
		if(key == VK_UP) {
			if(history_pos == (int)you.wiki_search_history.size()) draft = query;
			if(history_pos > 0) query = you.wiki_search_history[--history_pos];
			completion_active = false;
		} else if(key == VK_DOWN) {
			if(history_pos < (int)you.wiki_search_history.size()) {
				history_pos++;
				query = history_pos == (int)you.wiki_search_history.size() ? draft : you.wiki_search_history[history_pos];
			}
			completion_active = false;
		} else if(key == VK_TAB) {
			if(!query.empty()) {
				if(!completion_active) {
					completions = LocalzationManager::getWikiTitleCompletions(query);
					completion_pos = 0;
					completion_active = !completions.empty();
					if(completion_active) {
						size_t length = completions[0].size();
						for(size_t i=1;i<completions.size();i++) {
							length = min(length, completions[i].size());
							size_t j = 0;
							while(j < length && completions[0][j] == completions[i][j]) j++;
							length = j;
						}
						while(length > 0 && length < completions[0].size() &&
							(static_cast<unsigned char>(completions[0][length]) & 0xC0) == 0x80) length--;
						if(length > query.size()) query = completions[0].substr(0, length);
						else {
							query = completions[0];
							completion_pos = 1;
						}
					}
				} else {
					query = completions[completion_pos % completions.size()];
					completion_pos++;
				}
			}
			if(completions.empty()) {
				SetWikiSearchPrompt(string(1, command) + query + " (0)", CL_small_danger);
				continue;
			}
		} else if(key == VK_BACK) {
			if(!query.empty()) {
				size_t pos = query.size() - 1;
				while(pos > 0 && (query[pos] & 0xC0) == 0x80) --pos;
				query.erase(pos);
			}
			completion_active = false;
			history_pos = (int)you.wiki_search_history.size();
		} else if(key >= 32 && key <= 0xFFFF && key != VK_PRIOR && key != VK_NEXT &&
		key != VK_LEFT && key != VK_RIGHT && key != VK_UP && key != VK_DOWN) {
			string added = ConvertUTF16ToUTF8(wstring(1, static_cast<wchar_t>(key)));
			if(query.size() + added.size() <= players::WIKI_SEARCH_QUERY_MAX) query += added;
			completion_active = false;
			history_pos = (int)you.wiki_search_history.size();
		}
		SetWikiSearchPrompt(string(1, command) + query);
	}
}


void Help_Show()
{
	deletesub();

	bool loop_ = true;
	int input_;
	WaitForSingleObject(mutx, INFINITE);
	printsub("<" + LocalzationManager::locString(LOC_SYSTEM_TOUHOUCRAWL_HELP) + ">",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("?. " + LocalzationManager::locString(LOC_SYSTEM_COMMAND_LIST),true,CL_normal, '?');
	printsub("p. " + LocalzationManager::locString(LOC_SYSTEM_PAD_COMMAND_LIST),true,CL_normal, 'p');
	printsub("c. " + LocalzationManager::locString(LOC_SYSTEM_CHARACTER_HELP),true,CL_normal, 'c');
	printsub("g. " + LocalzationManager::locString(LOC_SYSTEM_GODS_HELP),true,CL_normal, 'g');	
	printsub("h. " + LocalzationManager::locString(LOC_SYSTEM_WIKI_HELP),true,CL_normal, 'h');
	printsub(":. " + LocalzationManager::locString(LOC_SYSTEM_PROCESS_NOTE),true,CL_normal, ':');
	printsub("0. " + LocalzationManager::locString(LOC_SYSTEM_PROCESS_CREDIT),true,CL_normal, '0');
	changedisplay(DT_SUB_TEXT);
	ReleaseMutex(mutx);
	while(loop_)
	{
		InputedKey inputedKey;
		input_ = waitkeyinput(inputedKey,true);
		if(input_ == VK_RETURN || input_ == GVK_BUTTON_A || input_ == GVK_BUTTON_A_LONG) {
			input_ = DisplayManager.positionToChar();
		}

		switch(input_)
		{
		case VK_UP:
			DisplayManager.addPosition(-1);
			continue;
		case VK_DOWN:
			DisplayManager.addPosition(1);
			continue;
		case '?':
		case 'p':
		{
			bool isPadHelp = (input_=='p');
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			if(isPadHelp) {
				printsub("                                   --- " + LocalzationManager::locString(LOC_SYSTEM_PAD_COMMAND_LIST) + " ---",true,CL_normal);
				printsub("",true,CL_normal);
				for(TextHelper text_ : LocalzationManager::getHelpPadCommand()) {
					printsub(text_.text,text_.enter,text_.color);
				}
			} else {
				printsub("                                   --- " + LocalzationManager::locString(LOC_SYSTEM_COMMAND_LIST) + " ---",true,CL_normal);
				printsub("",true,CL_normal);
				for(TextHelper text_ : LocalzationManager::getHelpCommand()) {
					printsub(text_.text,text_.enter,text_.color);
				}
			}
			changedisplay(DT_SUB_TEXT);
			setDisplayMove(DisplayManager.max_y);
			ReleaseMutex(mutx);
			while(loop_)
			{
				InputedKey inputedKey;
				switch(waitkeyinput(inputedKey,true))
				{
				case VK_UP:
					changemove(1);  //위
					break;
				case VK_DOWN:
					changemove(-1); //아래
					break;
				case VK_PRIOR:
				case GVK_LEFT_BUMPER:
					changemove(DisplayManager.log_length);
					break;
				case VK_NEXT:
				case GVK_RIGHT_BUMPER:
					changemove(-DisplayManager.log_length);
					break;
				case -1:
					if(inputedKey.mouse == MKIND_SCROLL_UP) {
						changemove(1);  //아래
						break;
					} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
						changemove(-1);  //위
						break;
					} else if(inputedKey.isRightClick()) {
						//ESC PASSTHORUGH
					}
					else {
						break;
					}
				case VK_ESCAPE:
				case GVK_BUTTON_B:
				case GVK_BUTTON_B_LONG:
					loop_ = false;
					break;
				default:
					break;
				}
			}
			break;
		}
		case 'C':
		case 'c':
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			for(TextHelper text_ : LocalzationManager::getHelpCharacter()) {
				printsub(text_.text,text_.enter,text_.color);
			}
			changedisplay(DT_SUB_TEXT);
			setDisplayMove(DisplayManager.max_y);
			ReleaseMutex(mutx);
			while(loop_)
			{
				InputedKey inputedKey;
				switch(waitkeyinput(inputedKey,true))
				{
				case VK_UP:
					changemove(1);  //위
					break;
				case VK_DOWN:
					changemove(-1); //아래
					break;
				case VK_PRIOR:
				case GVK_LEFT_BUMPER:
					changemove(DisplayManager.log_length);
					break;
				case VK_NEXT:
				case GVK_RIGHT_BUMPER:
					changemove(-DisplayManager.log_length);
					break;
				case -1:
					if(inputedKey.mouse == MKIND_SCROLL_UP) {
						changemove(1);  //아래
						break;
					} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
						changemove(-1);  //위
						break;
					} else if(inputedKey.isRightClick()) {
						//ESC PASSTHORUGH
					}
					else {
						break;
					}
				case VK_ESCAPE:
				case GVK_BUTTON_B:
				case GVK_BUTTON_B_LONG:
					loop_ = false;
					break;
				default:
					break;
				}
			}
			break;
		case 'G':
		case 'g':
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			for(TextHelper text_ : LocalzationManager::getHelpGods()) {
				printsub(text_.text,text_.enter,text_.color);
			}
			changedisplay(DT_SUB_TEXT);
			setDisplayMove(DisplayManager.max_y);
			ReleaseMutex(mutx);
			while(loop_)
			{
				InputedKey inputedKey;
				switch(waitkeyinput(inputedKey,true))
				{
				case VK_UP:
					changemove(1);  //위
					break;
				case VK_DOWN:
					changemove(-1); //아래
					break;
				case VK_PRIOR:
				case GVK_LEFT_BUMPER:
					changemove(DisplayManager.log_length);
					break;
				case VK_NEXT:
				case GVK_RIGHT_BUMPER:
					changemove(-DisplayManager.log_length);
					break;
				case -1:
					if(inputedKey.mouse == MKIND_SCROLL_UP) {
						changemove(1);  //아래
						break;
					} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
						changemove(-1);  //위
						break;
					} else if(inputedKey.isRightClick()) {
						//ESC PASSTHORUGH
					}
					else {
						break;
					}
				case VK_ESCAPE:
				case GVK_BUTTON_B:
				case GVK_BUTTON_B_LONG:
					loop_ = false;
					break;
				default:
					break;
				}
			}
			break;
		case 'H':
		case 'h':
		{
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			DisplayManager.setPosition(0);
			LocalzationManager::printWiki();
			changedisplay(DT_SUB_TEXT);
			setDisplayMove(DisplayManager.max_y);
			ReleaseMutex(mutx);
			string search_query;
			bool search_backward = false;
			int search_line = -1;
			while(loop_)
			{
				InputedKey inputedKey;
				int key_ = waitkeyinput(inputedKey,true);
				SetWikiSearchPrompt("");
				if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
					key_ = DisplayManager.positionToChar();
				}
				if(key_ >= 1000) {
					int line = LocalzationManager::getWikiLine(key_-1000);
					if(line != -1) {
						setDisplayMove(DisplayManager.max_y-line);
						DisplayManager.setPosition(0);
					}
					continue;
				}


				switch(key_)
				{
				case '/':
				case '?':
				{
					string query;
					if(InputWikiSearch(static_cast<char>(key_), query)) {
						if(!query.empty()) {
							search_query = query;
							if(you.wiki_search_history.empty() || you.wiki_search_history.back() != query)
								you.wiki_search_history.push_back(query);
							if(you.wiki_search_history.size() > players::WIKI_SEARCH_HISTORY_MAX)
								you.wiki_search_history.erase(you.wiki_search_history.begin());
						}
						if(!search_query.empty()) {
							search_backward = key_ == '?';
							int line = LocalzationManager::findWikiTitle(search_query, DisplayManager.max_y - DisplayManager.move, search_backward);
							if(line != -1) {
								setDisplayMove(max(0, DisplayManager.max_y - line));
								DisplayManager.setPosition(0);
								search_line = line;
							} else {
								SetWikiSearchPrompt(string(1, static_cast<char>(key_)) + search_query + " (0)", CL_small_danger);
							}
						}
					}
					break;
				}
				case 'n':
				case 'N':
					if(!search_query.empty()) {
						bool backward = key_ == 'n' ? search_backward : !search_backward;
						int line = LocalzationManager::findWikiTitle(search_query, search_line == -1 ? DisplayManager.max_y - DisplayManager.move : search_line, backward);
						if(line != -1) {
							setDisplayMove(max(0, DisplayManager.max_y - line));
							DisplayManager.setPosition(0);
							search_line = line;
						} else {
							SetWikiSearchPrompt(string(1, backward ? '?' : '/') + search_query + " (0)", CL_small_danger);
						}
					}
					break;
				case VK_UP:
					changemove(1);  //위
					DisplayManager.addPosition(0);
					break;
				case VK_DOWN:
					changemove(-1); //아래
					DisplayManager.addPosition(0);
					break;
				case VK_RIGHT:
					DisplayManager.addPosition(1);
					break;
				case VK_LEFT:
					DisplayManager.addPosition(-1);
					break;
				case VK_PRIOR:
				case GVK_LEFT_BUMPER:
					changemove(DisplayManager.log_length);
					break;
				case VK_NEXT:
				case GVK_RIGHT_BUMPER:
					changemove(-DisplayManager.log_length);
					break;
				case -1:
					if(inputedKey.mouse == MKIND_SCROLL_UP) {
						changemove(1);  //아래
						break;
					} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
						changemove(-1);  //위
						break;
					} else if(inputedKey.isRightClick()) {
						//ESC PASSTHORUGH
					}
					else {
						break;
					}
				case VK_ESCAPE:
				case GVK_BUTTON_B:
				case GVK_BUTTON_B_LONG:
					loop_ = false;
					break;
				default:
					break;
				}
			}
			SetWikiSearchPrompt("");
			break;
		}
		case ':':
			{	
				WaitForSingleObject(mutx, INFINITE);
				deletesub();
				ostringstream ss;
				int offset_[2] = {8,20};

				if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_TURNS)) < offset_[0]) {
					ss << string(offset_[0]-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_TURNS)), ' ');
				}
				ss << LocalzationManager::locString(LOC_SYSTEM_TURNS) << '|';
				if(PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_PLACE)) < offset_[1]) {
					ss << string(offset_[1]-PrintCharWidth(LocalzationManager::locString(LOC_SYSTEM_PLACE)), ' ');
				}
				ss << LocalzationManager::locString(LOC_SYSTEM_PLACE) << '|' << LocalzationManager::locString(LOC_SYSTEM_NOTE) << "\n";
				
				printsub(ss.str(),true,CL_normal);
				for(list<note_dummy>::iterator it = save_note.note_list.begin(); it != save_note.note_list.end(); it++)
				{
					ss.str("");
					ss.clear();
					if(PrintCharWidth(to_string(it->turn)) < offset_[0]) {
						ss << string(offset_[0]-PrintCharWidth(to_string(it->turn)), ' ');
					}
					ss << to_string(it->turn) << '|';
					if(PrintCharWidth(it->place) < offset_[1]) {
						ss << string(offset_[1]-PrintCharWidth(it->place), ' ');
					}
					ss << it->place << '|' <<  it->text;
					printsub(ss.str(),true,it->color);
				}
				changedisplay(DT_SUB_TEXT);
				ReleaseMutex(mutx);	
				while(loop_)
				{
					switch(waitkeyinput(inputedKey, true))
					{
					case VK_UP:
						changemove(1);  //위
						break;
					case VK_DOWN:
						changemove(-1); //아래
						break;
					case VK_PRIOR:
					case GVK_LEFT_BUMPER:
						changemove(DisplayManager.log_length);
						break;
					case VK_NEXT:
					case GVK_RIGHT_BUMPER:
						changemove(-DisplayManager.log_length);
						break;						
					case -1:
						if(inputedKey.mouse == MKIND_SCROLL_UP) {
							changemove(1);  //아래
							break;
						} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
							changemove(-1);  //위
							break;
						} else if(inputedKey.isRightClick()) {
							//ESC PASSTHORUGH
						}
						else {
							break;
						}
					case VK_ESCAPE:
				case GVK_BUTTON_B:
				case GVK_BUTTON_B_LONG:
						loop_ = false;
						break;
					default:
						break;
					}
				}
			}
			break;
		case '0':
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			printsub("                                    --- " + LocalzationManager::locString(LOC_SYSTEM_PROCESS_CREDIT) + " ---",true,CL_normal);
			for(TextHelper text_ : LocalzationManager::getHelpCredit()) {
				printsub(text_.text,text_.enter,text_.color);
			}
			changedisplay(DT_SUB_TEXT);
			setDisplayMove(DisplayManager.max_y);
			ReleaseMutex(mutx);
			while(loop_)
			{
				InputedKey inputedKey;
				switch(waitkeyinput(inputedKey,true))
				{
				case VK_UP:
					changemove(1);  //위
					break;
				case VK_DOWN:
					changemove(-1); //아래
					break;
				case VK_PRIOR:
				case GVK_LEFT_BUMPER:
					changemove(DisplayManager.log_length);
					break;
				case VK_NEXT:
				case GVK_RIGHT_BUMPER:
					changemove(-DisplayManager.log_length);
					break;
				case -1:
					if(inputedKey.mouse == MKIND_SCROLL_UP) {
						changemove(1);  //아래
						break;
					} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
						changemove(-1);  //위
						break;
					} else if(inputedKey.isRightClick()) {
						//ESC PASSTHORUGH
					}
					else {
						break;
					}
				case VK_ESCAPE:
				case GVK_BUTTON_B:
				case GVK_BUTTON_B_LONG:
					loop_ = false;
					break;
				default:
					break;
				}
			}
			break;
		case -1:
			if(inputedKey.isRightClick()) {
				//ESC PASSTHORUGH
			}
			else {
				break;
			}
		case VK_ESCAPE:
		case GVK_BUTTON_B:
		case GVK_BUTTON_B_LONG:
			loop_ = false;
			break;
		default:
			break;
		}

	}
		

	changedisplay(DT_GAME);
}

