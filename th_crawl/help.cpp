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
	printsub(":. " + LocalzationManager::locString(LOC_SYSTEM_PROCESS_NOTE),true,CL_normal, ':');
	printsub("0. " + LocalzationManager::locString(LOC_SYSTEM_PROCESS_CREDIT),true,CL_normal, '0');
	changedisplay(DT_SUB_TEXT);
	ReleaseMutex(mutx);
	while(loop_)
	{
		InputedKey inputedKey;
		input_ = waitkeyinput(inputedKey,true);
		switch(input_)
		{
		case '?':
		case 'p':
		{
			bool isPadHelp = (input_=='p');
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			if(isPadHelp) {
				printsub("                                   --- " + LocalzationManager::locString(LOC_SYSTEM_PAD_COMMAND_LIST) + " ---",true,CL_normal);
				printsub("",true,CL_normal);
				for(TextHelper text_ : LocalzationManager::getHelpCommand()) {
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
					changemove(DisplayManager.log_length);
					break;
				case VK_NEXT:
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
					changemove(DisplayManager.log_length);
					break;
				case VK_NEXT:
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
					changemove(DisplayManager.log_length);
					break;
				case VK_NEXT:
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
						changemove(DisplayManager.log_length);
						break;
					case VK_NEXT:
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
					changemove(DisplayManager.log_length);
					break;
				case VK_NEXT:
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

