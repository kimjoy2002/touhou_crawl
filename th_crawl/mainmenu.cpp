
#include "d3dUtility.h"
#include "environment.h"
#include "display.h"
#include "key.h"
#include "save.h"
#include "player.h"
#include "beam.h"
#include "monster_texture.h"
#include "map.h"
#include "dump.h"
#include "god.h"
#include "steam_api.h"
#include "throw.h"
#include "skill_use.h"
#include "note.h"
#include "tribe.h"
#include "network.h"
#include "option_manager.h"
#include "replay.h"


extern bool saveexit;

extern HANDLE mutx;
extern display_manager DisplayManager;
extern optionManager option_mg;

extern const char *version_string;
typedef struct menu_input
{
	int input;
	int output;
	string text;
	bool infor;
	bool (*f)(int); 
	int value;
	menu_input(int input_, int output_, string text_, bool infor_, bool (*f_)(int), int value_)
		:input(input_), output(output_), text(text_), infor(infor_),f(f_),value(value_){}
}menu_input;

struct menu_string {
	string text;
	bool enter;
	D3DCOLOR color;
	int clickable;
	menu_string(string text, bool enter, D3DCOLOR color, int clickable = 0): text(text), enter(enter), color(color), clickable(clickable){}
};


class menu
{
	int id; //아이디
	unique_ptr<vector<menu_string>> textmg;

	list<menu_input> input_list;
	
public:
	menu::menu(int id_, unique_ptr<vector<menu_string>>& textmg):id(id_),textmg(std::move(textmg)){}

	
	void input_puls(int input_, int output_, string text_, bool infor_, bool (*f_)(int), int value_)
	{
		input_list.push_back(menu_input(input_, output_, text_, infor_, f_, value_));
	}
	int GetId(){return id;};

	void View()
	{
		string blank(12,' ');
		WaitForSingleObject(mutx, INFINITE);
		deletesub(false);
		printsub("", true, CL_normal);
		printsub("", true, CL_normal);
		printsub("", true, CL_normal);
		bool newline = true;
		for(const auto& text : *textmg) {
			if(newline){
				printsub(blank, false, CL_normal);
				newline = false;
			}
			printsub(text.text, text.enter, text.color, text.clickable);
			if(text.enter)
				newline = true;
		}
		ReleaseMutex(mutx);
	}

	int Check(int input_, bool double_)
	{		
		for(list<menu_input>::iterator it = input_list.begin(); it != input_list.end(); it++)
		{			
			if((*it).input == input_)
			{
				if(double_)
				{
					if((*it).f && (*it).f((*it).value))
						return -2;
					return (*it).output;
				}
				if((*it).text.length() > 0)
				{
					WaitForSingleObject(mutx, INFINITE);
					std::istringstream iss((*it).text);
					std::string line;
					while (std::getline(iss, line)) {
						printsub(line, true, CL_normal);
					}
					ReleaseMutex(mutx);
					if((*it).infor)
					{
						return -1;
					}
					else
					{
						Sleep(300);
						if((*it).f && (*it).f((*it).value))
							return -2;
						return (*it).output;
					}
				}
				else
				{
					if((*it).f && (*it).f((*it).value))
						return -2;
					return (*it).output;
				}
			}
		}
		return -1;
	}
};


extern void start_mainmenu();

class menu_manager
{


	list<menu*> menu_list; 

	
public:
	menu_manager::~menu_manager()
	{
		for(list<menu*>::iterator it = menu_list.begin(); it != menu_list.end(); it++)
			delete(*it);
	}


	void menu_puls(int id_, unique_ptr<vector<menu_string>>& textmg)
	{
		menu_list.push_back(new menu(id_,textmg));
	}


	void menu_input_puls(int id_,int input_, int output_, string text_, bool infor_, bool (*f_)(int), int value_)
	{
		for(list<menu*>::iterator it = menu_list.begin(); it != menu_list.end(); it++)
		{
			if((*it)->GetId() == id_)
			{
				(*it)->input_puls(input_, output_, text_, infor_, f_, value_);
				return;
			}
		}
	}

	bool loop(int first_id)
	{
		int current_id = first_id;

		while(current_id != -2)
		{
			if(current_id == -3) {
				//완전 초기화
				return true;
			}


			for(list<menu*>::iterator it = menu_list.begin(); it != menu_list.end(); it++)
			{
				if((*it)->GetId() == current_id)
				{
					int prev_input_ = -1;						
					int output_ = -1;
					DisplayManager.setPosition(0);
					(*it)->View();
					while(1)
					{
						InputedKey inputedKey;
						int input_ = 0;
						while(1) {
							input_ = waitkeyinput(inputedKey, true);
							if(input_ == VK_UP) {
								DisplayManager.addPosition(-1);
							} else if(input_ == VK_DOWN)  {
								DisplayManager.addPosition(1);
							} else {
								break;
							}
						}

						if(input_ == -1) {
							if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
								if(inputedKey.val1 >= 'a' && inputedKey.val1 <= 'z' ) {
									input_ = inputedKey.val1 + 'A' - 'a';
								} else if(inputedKey.val1 >= 'A' && inputedKey.val1 <= 'Z' ) {
									input_ = inputedKey.val1 - ('A' - 'a');
								} else {
									input_ = inputedKey.val1;
								}
							}
						}
						if(input_ == VK_RETURN || input_ == GVK_BUTTON_A) {
							input_ = DisplayManager.positionToChar();
						}
						else if(input_ == GVK_BUTTON_A_LONG) {
							input_ = std::toupper(DisplayManager.positionToChar());
						}
						else if(input_ == GVK_BUTTON_B || input_ == GVK_BUTTON_B_LONG) {
							input_ = VK_ESCAPE;
						}
						

						(*it)->View();
						// if(input_ == VK_RETURN && prev_input_ != -1)
						// 	output_= (*it)->Check(prev_input_, true);
						// else
						output_= (*it)->Check(input_, prev_input_ == input_);
						if(output_ != -1)
						{
							break;
						}
						prev_input_ = input_;
						//DisplayManager.setPositionToChar(input_);
					}
					current_id = output_;
					break;					
				}
			}
		}
		return false;
	}

};


bool checkSavefile(int value_)
{
	if(ReplayClass.ReplayMode() == true)
		return false;

	if(load_data(save_file[option_mg.getSaveSlot()-1].c_str()))
	{
		steam_mg.setCurrentInfo();
		saveexit = true;
		return true;
	}
	return false;
}

extern vector<int> g_selected;

bool tutorials(int value_)
{
	g_selected[0] = 'b';
	map_list.tutorial = GM_TUTORIAL;
	return true;
}


bool tutorial2(int value_)
{
	g_selected[0] = 'b';
	map_list.tutorial = GM_TUTORIAL2;
	return true;
}


bool sprint1s(int value_)
{
	g_selected[0] = 'c';
	map_list.tutorial = GM_SPRINT1_AREANA;
	return true;
}


bool sprint2s(int value_)
{
	g_selected[0] = 'd';
	map_list.tutorial = GM_SPRINT2_MINISTAGE;
	return false;
}

bool option_menu(int value_);

bool select_fairy(int value_)
{
	g_selected[3] = value_;

	switch (value_)
	{
	case 0:
	default:
		you.tribe = TRI_FAIRY;
		you.job = JOB_WIZARD;
		you.char_type = UNIQ_START_SUNNY;
		you.image = &img_named_sunny;
		break;
	case 1:
		you.tribe = TRI_FAIRY;
		you.job = JOB_CRUSADER;
		you.char_type = UNIQ_START_STAR;
		you.image = &img_named_star;
		break;
	case 2:
		you.tribe = TRI_FAIRY;
		you.job = JOB_ASSASSIN;
		you.char_type = UNIQ_START_LUNA;
		you.image = &img_named_lunar;
		break;
	}
	WaitForSingleObject(mutx, INFINITE);
	printsub("", true, CL_normal);
	printsub("", true, CL_normal);
	printsub(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_KILLTHENALL), true, CL_normal);
	printsub("", true, CL_normal);
	ReleaseMutex(mutx);
	Sleep(300);
	return true;
}
bool select_named(int value_)
{
	g_selected[0] = 'a';
	g_selected[1] = 'a';
	g_selected[2] = value_;
	switch( value_ )
	{
	case 0:						
	default:
		you.tribe = TRI_HUMAN;
		you.job = JOB_SHAMAN;
		you.char_type = UNIQ_START_REIMU;
		you.image = &img_play_reimu;
		break;
	case 1:
		you.tribe = TRI_HUMAN;
		you.job = JOB_WIZARD;
		you.char_type = UNIQ_START_MARISA;
		you.image = &img_play_marisa;
		break;
	case 2:
		you.tribe = TRI_HUMAN;
		you.job = JOB_SHAMAN;
		you.char_type = UNIQ_START_SANAE;
		you.image = &img_play_sanae;
		break;
	case 3:
		you.tribe = TRI_WOLFTENGU;
		you.job = JOB_WARRIOR;
		you.char_type = UNIQ_START_MOMIZI;
		you.image = &img_play_momizi;
		break;
	case 4:
		you.tribe = TRI_YOKAI;
		you.job = JOB_ASSASSIN;
		you.char_type = UNIQ_START_KOISHI;
		you.image = &img_named_koishi;
		break;
	case 5:
		you.tribe = TRI_HUMAN;
		you.job = JOB_MONK;
		you.char_type = UNIQ_START_MOKOU;
		you.image = &img_play_mokou[0];
		break;
	case 6:
		you.tribe = TRI_KAPPA;
		you.job = JOB_ENGINEER;
		you.char_type = UNIQ_START_NITORI;
		you.image = &img_named_nitori;
		break;
	case 7:
		return false;
	}						
	WaitForSingleObject(mutx, INFINITE);
	printsub("", true, CL_normal);
	printsub("", true, CL_normal);
	printsub(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_KILLTHENALL), true, CL_normal);
	printsub("", true, CL_normal);
	ReleaseMutex(mutx);
	Sleep(300);
	return true;
}
bool select_char(int value_)
{
	g_selected[0] = 'a';
	g_selected[1] = 'b';
	g_selected[2] = value_;
	you.tribe = (tribe_type)(value_);
	return false;
}
bool show_help(int value_)
{
	WaitForSingleObject(mutx, INFINITE);
	deletesub();
	for(TextHelper text_ : LocalzationManager::getHelpCharacter()) {
		printsub(text_.text,text_.enter,text_.color);
	}
	changedisplay(DT_SUB_TEXT);
	setDisplayMove(DisplayManager.max_y-LocalzationManager::getHelpCharacterLine(value_));
	ReleaseMutex(mutx);
	bool loop_ = true;
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
			continue;
		}
	}

	WaitForSingleObject(mutx, INFINITE);
	
	ReleaseMutex(mutx);
	return false;
}
bool select_job(int value_)
{
	g_selected[3] = value_;
	you.job = (job_type)(value_);
	int sytle = ((you.tribe == TRI_FAIRY)?3:randA_nonlogic(2));
	int color = randA_nonlogic(10);
	if (you.tribe == TRI_KAPPA)
		color = 10;
	else if (you.tribe == TRI_WOLFTENGU)
		color = 9;
	you.image = &img_playable_character[color][sytle];
	you.char_type = UNIQ_START_NONE;
	return true;
}

bool replay_menu(int value_);
bool save_menu(int value_);

bool quit_menu(int value_)
{
	throw 0;
}


void start_mainmenu()
{
	bool retry_ = true;

	while (retry_) {
		retry_ = false;
		menu_manager m_mgr;
		string tempstr;
		
		unique_ptr<vector<menu_string>> temp = make_unique<vector<menu_string>>();
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME), true, CL_help));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("a - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_GAMESTART), true, CL_normal, 'a'));
		temp->push_back(menu_string("b - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_TUTORIAL), true, CL_normal, 'b'));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MINIGAME), true, CL_help));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("c - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_ARENA), true, CL_normal, 'c'));
		temp->push_back(menu_string("d - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_SPRINT), true, CL_normal, 'd'));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_ETC), true, CL_help));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("e - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_OPTION), true, CL_normal, 'e'));
		temp->push_back(menu_string("s - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_SAVE), true, CL_normal, 's'));
		temp->push_back(menu_string("R - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_REPLAY), true, CL_normal, 'R'));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("X - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_QUIT), true, CL_normal, 'X'));
		m_mgr.menu_puls(0,temp);
		m_mgr.menu_input_puls(0,'a',1,"",false,checkSavefile,0);
		m_mgr.menu_input_puls(0,'b',0,"",false,tutorials,0);
		//m_mgr.menu_input_puls(0,'c',0,"",false,tutorial2,0);
		m_mgr.menu_input_puls(0,'c',0,"",false,sprint1s,0);
		m_mgr.menu_input_puls(0, 'd', 1, "", false, sprint2s, 0);
		m_mgr.menu_input_puls(0,'e',-3,"",false,option_menu,0);
		m_mgr.menu_input_puls(0,'s',0,"",false,save_menu,0);
		m_mgr.menu_input_puls(0,'R',0,"",false,replay_menu,0);
		m_mgr.menu_input_puls(0,'X',0,"",false,quit_menu,0);
		
		temp = make_unique<vector<menu_string>>();
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_SELECT), true, CL_help));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("a - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_EASY), true, CL_normal, 'a'));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("b - " + LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_NORMAL), true, CL_normal, 'b'));
		temp->push_back(menu_string("", true, CL_normal));
		m_mgr.menu_puls(1,temp);
		m_mgr.menu_input_puls(1,'a',2,LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_EASY_SELECT) + "\n",false,NULL,0);
		m_mgr.menu_input_puls(1,'b',3,LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_NORMAL_SELECT) + "\n",false,NULL,0);
		m_mgr.menu_input_puls(1,VK_ESCAPE,0,"",false,NULL,0);

		
		temp = make_unique<vector<menu_string>>();
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_NORMAL), true, CL_help));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));

		LOCALIZATION_ENUM_KEY charlist[8][3] = {
			{LOC_SYSTEM_TRIBE_HUMAN,LOC_SYSTEM_JOB_SHAMAN,LOC_SYSTEM_PLAYER_REIMU},
			{LOC_SYSTEM_TRIBE_HUMAN,LOC_SYSTEM_JOB_WIZARD,LOC_SYSTEM_PLAYER_MARISA},
			{LOC_SYSTEM_TRIBE_HUMAN,LOC_SYSTEM_JOB_SHAMAN,LOC_SYSTEM_PLAYER_SANAE},
			{LOC_SYSTEM_TRIBE_WOLFTENGU,LOC_SYSTEM_JOB_WARRIOR,LOC_SYSTEM_PLAYER_MOMIZI},
			{LOC_SYSTEM_TRIBE_YOUKAI,LOC_SYSTEM_JOB_ASSASSIN,LOC_SYSTEM_PLAYER_KOISHI},
			{LOC_SYSTEM_TRIBE_HUMAN,LOC_SYSTEM_JOB_MONK,LOC_SYSTEM_PLAYER_MOKOU},
			{LOC_SYSTEM_TRIBE_KAPPA,LOC_SYSTEM_JOB_ENGINEER,LOC_SYSTEM_PLAYER_NITORI},
			{LOC_SYSTEM_TRIBE_FAIRY,LOC_NONE,LOC_SYSTEM_PLAYER_THREE_FAIRIES}
		};

		for(int i = 0; i < 8; i++) {
			char hotkey_ = 'a' + i;
			ostringstream ss;
			ss << hotkey_ << " - " << LocalzationManager::locString(charlist[i][0]);
			if(charlist[i][1] != LOC_NONE) {
				ss << " " << LocalzationManager::locString(charlist[i][1]);
			}
			ss << " " << LocalzationManager::locString(charlist[i][2]);
			temp->push_back(menu_string(ss.str(), false, CL_normal, hotkey_));

			if(i%2 == 1) {
				temp->push_back(menu_string("", true, CL_normal));
				temp->push_back(menu_string("", true, CL_normal));
			}
			else if(40 - PrintCharWidth(ss.str()) > 0) {
				temp->push_back(menu_string(string(40 - PrintCharWidth(ss.str()), ' '), false, CL_normal));
			} else {
				temp->push_back(menu_string(" ", false, CL_normal));
			}
		}

		temp->push_back(menu_string("", true, CL_normal));
		m_mgr.menu_puls(2,temp);
		
		
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_REIMU);
		tempstr += " : ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_REIMU1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_REIMU2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_REIMU3);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_REIMU4);
		tempstr += "\n\n\n";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(2,'a',2,tempstr,true,select_named,0);
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_MARISA);
		tempstr += " : ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MARISA1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MARISA2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MARISA3);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MARISA4);
		tempstr += "\n\n\n";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(2,'b',2,tempstr,true,select_named,1);
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_SANAE);
		tempstr += " : ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SANAE1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SANAE2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SANAE3);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SANAE4);
		tempstr += "\n\n\n";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(2,'c',2,tempstr,true,select_named,2);
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_MOMIZI);
		tempstr += " : ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOMIZI1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOMIZI2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOMIZI3);
		tempstr += "\n\n ";	
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOMIZI4);
		tempstr += "\n\n\n";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(2,'d',2,tempstr,true,select_named,3);	
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_KOISHI);
		tempstr += " : ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_KOISHI1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_KOISHI2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_KOISHI3);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_KOISHI4);
		tempstr += "\n\n\n";	
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(2,'e',2,tempstr,true,select_named,4);
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_MOKOU);
		tempstr += " : ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOKOU1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOKOU2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOKOU3);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOKOU4);
		tempstr += "\n\n\n";	
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(2,'f',2,tempstr,true,select_named,5);
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_NITORI);
		tempstr += " : ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_NITORI1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_NITORI2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_NITORI3);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_NITORI4);
		tempstr += "\n\n\n";	
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(2,'g',2,tempstr,true,select_named,6);
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_THREE_FAIRIES);
		tempstr += " : ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_FAIRIES1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_FAIRIES2);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_FAIRIES3);
		tempstr += "\n\n\n";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(2, 'h', 5, tempstr, true, select_named, 7);
		m_mgr.menu_input_puls(2,VK_ESCAPE,1,"",false,NULL,0);

		
		temp = make_unique<vector<menu_string>>();
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_SELECT), true, CL_help));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));

		const int max_tribe = TRI_MAX-1; //요괴 제외
		for(int i=0;i<max_tribe;i++)
		{
			char hotkey_ = 'a' + i;
			ostringstream ss;
			ss << hotkey_ << " - " << LocalzationManager::locString(tribe_type_string[i]);

			temp->push_back(menu_string(ss.str(), false, CL_normal, hotkey_));

			if(i%2 == 1  || i == max_tribe-1) {
				temp->push_back(menu_string("", true, CL_normal));
			}
			else if(23 - PrintCharWidth(ss.str()) > 0) {
				temp->push_back(menu_string(string(23 - PrintCharWidth(ss.str()), ' '), false, CL_normal));
			} else {
				temp->push_back(menu_string(" ", false, CL_normal));
			}
		}
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_SELECT_HELP_APTIT), true, CL_normal, '?'));
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_SELECT_HELP), true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));
		m_mgr.menu_puls(3,temp);


		LOCALIZATION_ENUM_KEY tribelist[max_tribe][2] = {
			{LOC_SYSTEM_TRIBE_HUMAN,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_HUMAN},
			{LOC_SYSTEM_TRIBE_WIZARD,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_WIZARD},
			{LOC_SYSTEM_TRIBE_FAIRY,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_FAIRY},
			{LOC_SYSTEM_TRIBE_CROWTENGU,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_CROWTENGU},
			{LOC_SYSTEM_TRIBE_WOLFTENGU,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_WOLFTENGU},
			{LOC_SYSTEM_TRIBE_KAPPA,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_KAPPA},
			{LOC_SYSTEM_TRIBE_NECOMATA,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_NECOMATA},
			{LOC_SYSTEM_TRIBE_OARFISH,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_OARFISH},
			{LOC_SYSTEM_TRIBE_CHEUKUMOGAMI,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_CHEUKUMOGAMI},
			{LOC_SYSTEM_TRIBE_ONI,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_ONI},
			{LOC_SYSTEM_TRIBE_HALFYOUKAI,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_HALFYOUKAI},
			{LOC_SYSTEM_TRIBE_WRAITH,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_WRAITH},
			{LOC_SYSTEM_TRIBE_VAMPIRE,LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_VAMPIRE}
		};

		for (int i = 0; i < max_tribe; i++) {
			char hotkey_ = 'a' + i;
			tempstr = LocalzationManager::locString(tribelist[i][0]);
			tempstr += ": ";
			tempstr += LocalzationManager::locString(tribelist[i][1]);
			tempstr += "\n\n\n";
			tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
			tempstr += "\n";
			m_mgr.menu_input_puls(3,hotkey_,4,tempstr,true,select_char,i);
			m_mgr.menu_input_puls(3,hotkey_+ 'A'-'a',3,"",false,show_help,i+1);

		}
		m_mgr.menu_input_puls(3,'?',3,"",false,show_help,0);
		m_mgr.menu_input_puls(3,VK_ESCAPE,1,"",false,NULL,0);

		
		
		temp = make_unique<vector<menu_string>>();
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_JOB_SELECT), true, CL_help));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));
		for(int i=0;i<JOB_MAX;i++)
		{
			char hotkey_ = 'a' + i;
			ostringstream ss;
			ss << hotkey_ << " - " << LocalzationManager::locString(job_type_string[i]);
			
			temp->push_back(menu_string(ss.str(), false, CL_normal, hotkey_));

			if(i%2 == 1  || i == JOB_MAX-1) {
				temp->push_back(menu_string("", true, CL_normal));
			}
			else if(23 - PrintCharWidth(ss.str()) > 0) {
				temp->push_back(menu_string(string(23 - PrintCharWidth(ss.str()), ' '), false, CL_normal));
			} else {
				temp->push_back(menu_string(" ", false, CL_normal));
			}
		}
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_JOB_SELECT_HELP), true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));
		m_mgr.menu_puls(4,temp);
		


		LOCALIZATION_ENUM_KEY joblist[21][2] = {
			{LOC_SYSTEM_JOB_WARRIOR,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_WARRIOR},
			{LOC_SYSTEM_JOB_WIZARD,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_WIZARD},
			{LOC_SYSTEM_JOB_SHAMAN,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_SHAMAN},
			{LOC_SYSTEM_JOB_GLADIATOR,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_GLADIATOR},
			{LOC_SYSTEM_JOB_MONK,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_MONK},
			{LOC_SYSTEM_JOB_CRUSADER,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_CRUSADER},
			{LOC_SYSTEM_JOB_BERSERKER,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_BERSERKER},
			{LOC_SYSTEM_JOB_FIRE_WIZARD,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_FIRE_WIZARD},
			{LOC_SYSTEM_JOB_COLD_WIZARD,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_COLD_WIZARD},
			{LOC_SYSTEM_JOB_EARTH_WIZARD,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_EARTH_WIZARD},
			{LOC_SYSTEM_JOB_AIR_WIZARD,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_AIR_WIZARD},
			{LOC_SYSTEM_JOB_SUMMON_WIZARD,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_SUMMON_WIZARD},
			{LOC_SYSTEM_JOB_ALCHEMIST,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_ALCHEMIST},
			{LOC_SYSTEM_JOB_PSYCHOLOGIST,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_PSYCHOLOGIST},
			{LOC_SYSTEM_JOB_REAPER,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_REAPER},
			{LOC_SYSTEM_JOB_FANATIC,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_FANATIC},
			{LOC_SYSTEM_JOB_ASSASSIN,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_ASSASSIN},
			{LOC_SYSTEM_JOB_FARMER,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_FARMER},
			{LOC_SYSTEM_JOB_MADE,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_MADE},
			{LOC_SYSTEM_JOB_ENGINEER,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_ENGINEER},
			{LOC_SYSTEM_JOB_MISSING,LOC_SYSTEM_MAINMENU_MAINGAME_JOB_MISSING}
		};


		for (int i = 0; i < 21; i++) {
			char hotkey_ = 'a' + i;
			tempstr = LocalzationManager::locString(joblist[i][0]);
			tempstr += ": ";
			tempstr += LocalzationManager::locString(joblist[i][1]);
			tempstr += "\n\n\n";
			tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
			tempstr += "\n";
			m_mgr.menu_input_puls(4,hotkey_,5,tempstr,true,select_job,i);
			m_mgr.menu_input_puls(4,hotkey_+ 'A'-'a',4,"",false,show_help,i+1+max_tribe);

		}
		m_mgr.menu_input_puls(3,'?',3,"",false,show_help,0);
		m_mgr.menu_input_puls(4,VK_ESCAPE,3,"",false,NULL,0);


		temp = make_unique<vector<menu_string>>();
		temp->push_back(menu_string(LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SELECT), true, CL_help));
		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));

		LOCALIZATION_ENUM_KEY fariylist[3][3] = {
			{LOC_SYSTEM_TRIBE_FAIRY,LOC_SYSTEM_JOB_WIZARD,LOC_SYSTEM_PLAYER_SUNNY},
			{LOC_SYSTEM_TRIBE_FAIRY,LOC_SYSTEM_JOB_CRUSADER,LOC_SYSTEM_PLAYER_STAR},
			{LOC_SYSTEM_TRIBE_FAIRY,LOC_SYSTEM_JOB_ASSASSIN,LOC_SYSTEM_PLAYER_LUNA}
		};

		for(int i = 0; i < 3; i++) {
			char hotkey_ = 'a' + i;

			ostringstream ss;
			ss << hotkey_ << " - " << LocalzationManager::locString(fariylist[i][0]);
			ss << " " << LocalzationManager::locString(fariylist[i][1]);
			ss << " " << LocalzationManager::locString(fariylist[i][2]);
			temp->push_back(menu_string(ss.str(), true, CL_normal, hotkey_));
			temp->push_back(menu_string("", true, CL_normal));
		}

		temp->push_back(menu_string("", true, CL_normal));
		temp->push_back(menu_string("", true, CL_normal));
		m_mgr.menu_puls(5, temp);




		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_SUNNY);
		tempstr += ": ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_SUNNY1);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_SUNNY2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_SUNNY3);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON3);
		tempstr += "\n\n\n";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(5,'a',6,tempstr,true,select_fairy,0);
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_STAR);
		tempstr += ": ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_STAR1);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_STAR2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_STAR3);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON3);
		tempstr += "\n\n\n";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(5,'b',6,tempstr,true, select_fairy,1);
		tempstr = LocalzationManager::locString(LOC_SYSTEM_PLAYER_LUNA);
		tempstr += ": ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_LUNA1);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_LUNA2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_LUNA3);
		tempstr += "\n\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON1);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON2);
		tempstr += "\n ";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON3);
		tempstr += "\n\n\n";
		tempstr += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		tempstr += "\n";
		m_mgr.menu_input_puls(5, 'c', 6, tempstr, true, select_fairy, 2);
		m_mgr.menu_input_puls(5,VK_ESCAPE,2,"",false,NULL,0);

		changedisplay(DT_SUB_TEXT);

		retry_ = m_mgr.loop(0);
	}
}

