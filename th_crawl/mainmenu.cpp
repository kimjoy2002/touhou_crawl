
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
#include "replay.h"


extern bool saveexit;

extern HANDLE mutx;


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

class menu
{
	int id; //아이디
	string text;

	list<menu_input> input_list;
	
public:
	menu::menu(int id_, string text_):id(id_),text(text_){}

	
	void input_puls(int input_, int output_, string text_, bool infor_, bool (*f_)(int), int value_)
	{
		input_list.push_back(menu_input(input_, output_, text_, infor_, f_, value_));
	}
	int GetId(){return id;};

	void View()
	{
		WaitForSingleObject(mutx, INFINITE);
		SetText() = text;
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
					SetText() += (*it).text;
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
class menu_manager
{


	list<menu*> menu_list; 

	
public:
	menu_manager::~menu_manager()
	{
		for(list<menu*>::iterator it = menu_list.begin(); it != menu_list.end(); it++)
			delete(*it);
	}


	void menu_puls(int id_, string text_)
	{
		menu_list.push_back(new menu(id_,text_));
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

	void loop(int first_id)
	{
		int current_id = first_id;

		while(current_id != -2)
		{
			for(list<menu*>::iterator it = menu_list.begin(); it != menu_list.end(); it++)
			{
				if((*it)->GetId() == current_id)
				{
					int prev_input_ = -1;						
					int output_ = -1;
					(*it)->View();
					while(1)
					{
						int input_ = waitkeyinput();
						(*it)->View();
						if(input_ == VK_RETURN && prev_input_ != -1)
							output_= (*it)->Check(prev_input_, true);
						else
							output_= (*it)->Check(input_, prev_input_ == input_);
						if(output_ != -1)
						{
							break;
						}
						prev_input_ = input_;
					}
					current_id = output_;
					break;					
				}
			}
		}
	}

};


bool checkSavefile(int value_)
{
	if(ReplayClass.ReplayMode() == true)
		return false;

	if(load_data(save_file.c_str()))
	{
		steam_mg.setCurrentInfo();
		saveexit = true;
		return true;
	}
	return false;
}

bool tutorials(int value_)
{
	map_list.tutorial = GM_TUTORIAL;
	return true;
}


bool tutorial2(int value_)
{
	map_list.tutorial = GM_TUTORIAL2;
	return true;
}


bool sprint1s(int value_)
{
	map_list.tutorial = GM_SPRINT1_AREANA;
	return true;
}


bool sprint2s(int value_)
{
	map_list.tutorial = GM_SPRINT2_MINISTAGE;
	return false;
}

bool option_menu(int value_);

bool select_fairy(int value_)
{

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
	SetText() += "\n\n\nKill Them All!\n";
	ReleaseMutex(mutx);
	Sleep(300);
	return true;
}
bool select_named(int value_)
{
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
	SetText() += "\n\n\nKill Them All!\n";
	ReleaseMutex(mutx);
	Sleep(300);
	return true;
}
bool select_char(int value_)
{
	you.tribe = (tribe_type)(value_);
	return false;
}
bool select_job(int value_)
{
	you.job = (job_type)(value_);
	int sytle = ((you.tribe == TRI_FAIRY)?3:randA(2));
	int color = randA(10);
	if (you.tribe == TRI_KAPPA)
		color = 10;
	else if (you.tribe == TRI_WOLFTENGU)
		color = 9;
	you.image = &img_playable_character[color][sytle];
	you.char_type = UNIQ_START_NONE;
	return true;
}

bool replay_menu(int value_);


void start_mainmenu()
{
	menu_manager m_mgr;
	string temp;
	
	temp = LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME);
	temp += "\n\n";
	temp += "a - ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_GAMESTART);
	temp += "\n";
	temp += "b - ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_TUTORIAL);
	temp += "\n";
	temp += "\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MINIGAME);
	temp += "\n\n";
	temp += "c - ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_ARENA);
	temp += "\n";
	temp += "d - ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_SPRINT);
	temp += "\n";
	temp += "\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_ETC);
	temp += "\n\n";
	temp += "e - ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_OPTION);
	temp += "\n";
	temp += "R - ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_REPLAY);
	m_mgr.menu_puls(0,temp);
	m_mgr.menu_input_puls(0,'a',1,"",false,checkSavefile,0);
	m_mgr.menu_input_puls(0,'b',0,"",false,tutorials,0);
	//m_mgr.menu_input_puls(0,'c',0,"",false,tutorial2,0);
	m_mgr.menu_input_puls(0,'c',0,"",false,sprint1s,0);
	m_mgr.menu_input_puls(0, 'd', 1, "", false, sprint2s, 0);
	m_mgr.menu_input_puls(0,'e',0,"",false,option_menu,0);
	m_mgr.menu_input_puls(0,'R',0,"",false,replay_menu,0);
	

	temp = LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_SELECT);
	temp += "\n\n\n";
	temp += "a - ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_EASY);
	temp += "\n\n";
	temp += "b - ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_NORMAL);
	temp += "\n\n";
	m_mgr.menu_puls(1,temp);
	m_mgr.menu_input_puls(1,'a',2,LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_EASY_SELECT) + "\n",false,NULL,0);
	m_mgr.menu_input_puls(1,'b',3,LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_NORMAL_SELECT) + "\n",false,NULL,0);
	m_mgr.menu_input_puls(1,VK_ESCAPE,0,"",false,NULL,0);

	
	temp = LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_MODE_NORMAL);
	temp += "\n\n\n\n";

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

		if(i%2 == 1) {
			ss << "\n\n";
		}
		else if(40 - PrintCharWidth(ss.str()) > 0) {
			ss << string(40 - PrintCharWidth(ss.str()), ' ');
		} else {
			ss << ' ';
		}
		temp += ss.str();
	}

	temp += "\n\n";	
	m_mgr.menu_puls(2,temp);
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_REIMU);
	temp += " : ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_REIMU1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_REIMU2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_REIMU3);
	temp += "\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_REIMU4);
	temp += "\n\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(2,'a',2,temp,true,select_named,0);
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_MARISA);
	temp += " : ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MARISA1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MARISA2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MARISA3);
	temp += "\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MARISA4);
	temp += "\n\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(2,'b',2,temp,true,select_named,1);
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_SANAE);
	temp += " : ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SANAE1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SANAE2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SANAE3);
	temp += "\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SANAE4);
	temp += "\n\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(2,'c',2,temp,true,select_named,2);
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_MOMIZI);
	temp += " : ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOMIZI1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOMIZI2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOMIZI3);
	temp += "\n\n ";	
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOMIZI4);
	temp += "\n\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(2,'d',2,temp,true,select_named,3);	
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_KOISHI);
	temp += " : ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_KOISHI1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_KOISHI2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_KOISHI3);
	temp += "\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_KOISHI4);
	temp += "\n\n\n";	
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(2,'e',2,temp,true,select_named,4);
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_MOKOU);
	temp += " : ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOKOU1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOKOU2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOKOU3);
	temp += "\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_MOKOU4);
	temp += "\n\n\n";	
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(2,'f',2,temp,true,select_named,5);
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_NITORI);
	temp += " : ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_NITORI1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_NITORI2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_NITORI3);
	temp += "\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_NITORI4);
	temp += "\n\n\n";	
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(2,'g',2,temp,true,select_named,6);
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_THREE_FAIRIES);
	temp += " : ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_FAIRIES1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_FAIRIES2);
	temp += "\n\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_FAIRIES3);
	temp += "\n\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(2, 'h', 5, temp, true, select_named, 7);
	m_mgr.menu_input_puls(2,VK_ESCAPE,1,"",false,NULL,0);

	
	temp = LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_TRIBE_SELECT);
	temp += "\n\n\n";
	for(int i=0;i<TRI_MAX-1;i++)
	{
		char tempchar[64];
		sprintf_s(tempchar,"%c - %s",'a'+i,LocalzationManager::locString(tribe_type_string[i]).c_str());
		int remain_num_ = 23-strlen(tempchar);
		temp += tempchar;
		if(i%2 ==0)
		{
			for(int j=0;j<remain_num_;j++)
				temp += " ";
		}
		if(i%2 == 1 || i == TRI_MAX-2)
		{
			temp += "\n";
		}
	}
	temp += "\n\n\n";
	m_mgr.menu_puls(3,temp);



	LOCALIZATION_ENUM_KEY tribelist[13][2] = {
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

	for (int i = 0; i < 13; i++) {
		char hotkey_ = 'a' + i;
		temp = LocalzationManager::locString(tribelist[i][0]);
		temp += ": ";
		temp += LocalzationManager::locString(tribelist[i][1]);
		temp += "\n\n\n";
		temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		temp += "\n";
		m_mgr.menu_input_puls(3,hotkey_,4,temp,true,select_char,i);

	}
	m_mgr.menu_input_puls(3,VK_ESCAPE,1,"",false,NULL,0);

	
	temp = LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_JOB_SELECT);
	temp += "\n\n\n";
	for(int i=0;i<JOB_MAX;i++)
	{
		char tempchar[64];
		sprintf_s(tempchar,"%c - %s",'a'+i,LocalzationManager::locString(job_type_string[i]).c_str());
		int remain_num_ = 23-strlen(tempchar);
		temp += tempchar;
		if(i%2 ==0)
		{
			for(int j=0;j<remain_num_;j++)
				temp += " ";
		}
		if(i%2 == 1 || i == JOB_MAX-1)
		{
			temp += "\n";
		}
	}
	temp += "\n\n\n";
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
		temp = LocalzationManager::locString(joblist[i][0]);
		temp += ": ";
		temp += LocalzationManager::locString(joblist[i][1]);
		temp += "\n\n\n";
		temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
		temp += "\n";
		m_mgr.menu_input_puls(4,hotkey_,5,temp,true,select_job,i);

	}
	m_mgr.menu_input_puls(4,VK_ESCAPE,3,"",false,NULL,0);


	temp = LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_CHAR_SELECT);
	temp += "\n\n\n\n";

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
		ss << "\n\n";
		temp += ss.str();
	}


	temp += "\n\n\n";
	m_mgr.menu_puls(5, temp);




	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_SUNNY);
	temp += ": ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_SUNNY1);
	temp += "\n\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_SUNNY2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_SUNNY3);
	temp += "\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON3);
	temp += "\n\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(5,'a',6,temp,true,select_fairy,0);
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_STAR);
	temp += ": ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_STAR1);
	temp += "\n\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_STAR2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_STAR3);
	temp += "\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON3);
	temp += "\n\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(5,'b',6,temp,true, select_fairy,1);
	temp = LocalzationManager::locString(LOC_SYSTEM_PLAYER_LUNA);
	temp += ": ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_LUNA1);
	temp += "\n\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_LUNA2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_LUNA3);
	temp += "\n\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON1);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON2);
	temp += "\n ";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_MAINGAME_FAIRIES_COMMON3);
	temp += "\n\n\n";
	temp += LocalzationManager::locString(LOC_SYSTEM_MAINMENU_CONTINUE_SAMEKEY);
	temp += "\n";
	m_mgr.menu_input_puls(5, 'c', 6, temp, true, select_fairy, 2);
	m_mgr.menu_input_puls(5,VK_ESCAPE,2,"",false,NULL,0);





	m_mgr.loop(0);
}

