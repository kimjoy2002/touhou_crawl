﻿//////////////////////////////////////////////////////////////////////////////////////////////////
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
	printsub("?. " + LocalzationManager::locString(LOC_SYSTEM_COMMAND_LIST),true,CL_normal);
	printsub(":. " + LocalzationManager::locString(LOC_SYSTEM_PROCESS_NOTE),true,CL_normal);
	printsub("0. " + LocalzationManager::locString(LOC_SYSTEM_PROCESS_CREDIT),true,CL_normal);
	changedisplay(DT_SUB_TEXT);
	ReleaseMutex(mutx);
	while(loop_)
	{
		input_ = waitkeyinput(true);
		switch(input_)
		{
		case '?':
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			printsub("                                   --- " + LocalzationManager::locString(LOC_SYSTEM_COMMAND_LIST) + " ---",true,CL_normal);
			printsub("",true,CL_normal);
			for(TextHelper text_ : LocalzationManager::getHelpCommand()) {
				printsub(text_.text,text_.enter,text_.color);
			}
			changedisplay(DT_SUB_TEXT);
			setDisplayMove(DisplayManager.max_y);
			ReleaseMutex(mutx);
			while(1)
			{
				switch(waitkeyinput(true))
				{
				case VK_UP:
					changemove(1);  //위
					continue;
				case VK_DOWN:
					changemove(-1); //아래
					continue;
				case VK_PRIOR:
					changemove(DisplayManager.log_length);
					continue;
				case VK_NEXT:
					changemove(-DisplayManager.log_length);
					continue;
				case VK_ESCAPE:
					loop_ = false;
					break;
				default:
					continue;
				}
				break;
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
				while(1)
				{
					switch(waitkeyinput(true))
					{
					case VK_UP:
						changemove(1);  //위
						continue;
					case VK_DOWN:
						changemove(-1); //아래
						continue;
					case VK_PRIOR:
						changemove(DisplayManager.log_length);
						continue;
					case VK_NEXT:
						changemove(-DisplayManager.log_length);
						continue;
					case VK_ESCAPE:
						loop_ = false;
						break;
					default:
						continue;
					}
					break;
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
			while(1)
			{
				switch(waitkeyinput(true))
				{
				case VK_UP:
					changemove(1);  //위
					continue;
				case VK_DOWN:
					changemove(-1); //아래
					continue;
				case VK_PRIOR:
					changemove(DisplayManager.log_length);
					continue;
				case VK_NEXT:
					changemove(-DisplayManager.log_length);
					continue;
				case VK_ESCAPE:
					loop_ = false;
					break;
				default:
					continue;
				}
				break;
			}
			break;
		case VK_ESCAPE:
			loop_ = false;
			break;
		default:
			break;
		}

	}
		

	changedisplay(DT_GAME);
}

