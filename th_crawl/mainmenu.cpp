
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
	int id; //���̵�
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
	map_list.tutorial = GM_NORMAL;
	if(ReplayClass.ReplayMode() == true)
		return false;

	if(load_data(save_file.c_str()))
	{
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

bool select_fairy(int value_)
{

	switch (value_)
	{
	case 0:
	default:
		you.tribe = TRI_FAIRY;
		you.job = JOB_WIZARD;
		you.char_name.name = "���";
		you.char_name.name_type = false;
		you.image = &img_named_sunny;
		break;
	case 1:
		you.tribe = TRI_FAIRY;
		you.job = JOB_CRUSADER;
		you.char_name.name = "��Ÿ";
		you.char_name.name_type = false;
		you.image = &img_named_star;
		break;
	case 2:
		you.tribe = TRI_FAIRY;
		you.job = JOB_ASSASSIN;
		you.char_name.name = "�糪";
		you.char_name.name_type = false;
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
		you.char_name.name = "���̹�";
		you.char_name.name_type = false;
		you.image = &img_play_reimu;
		break;
	case 1:
		you.tribe = TRI_HUMAN;
		you.job = JOB_WIZARD;
		you.char_name.name = "������";
		you.char_name.name_type = false;
		you.image = &img_play_marisa;
		break;
	case 2:
		you.tribe = TRI_HUMAN;
		you.job = JOB_SHAMAN;
		you.char_name.name = "�糪��";
		you.char_name.name_type = false;
		you.image = &img_play_sanae;
		break;
	case 3:
		you.tribe = TRI_WOLFTENGU;
		you.job = JOB_WARRIOR;
		you.char_name.name = "�����";
		you.char_name.name_type = false;
		you.image = &img_play_momizi;
		break;
	case 4:
		you.tribe = TRI_YOKAI;
		you.job = JOB_ASSASSIN;
		you.char_name.name = "���̽�";
		you.char_name.name_type = false;
		you.image = &img_named_koishi;
		break;
	case 5:
		you.tribe = TRI_HUMAN;
		you.job = JOB_MONK;
		you.char_name.name = "���ڿ�";
		you.char_name.name_type = false;
		you.image = &img_play_mokou[0];
		break;
	case 6:
		you.tribe = TRI_KAPPA;
		you.job = JOB_ENGINEER;
		you.char_name.name = "���丮";
		you.char_name.name_type = false;
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
	you.char_name.name = "";
	return true;
}

bool replay_menu(int value_);


void start_mainmenu()
{
	menu_manager m_mgr;
	string temp;
	
	temp = "���� ����\n\n";
	temp += "a - ���ӽ���\n";
	temp += "b - Ʃ�丮��(�ʽ���)\n";
	temp += "c - Ʃ�丮��(���װ����ڿ�, �ӽ�)\n";	
	temp += "\n\n�̴� ����\n\n";
	temp += "d - �Ʒ���\n";
	temp += "e - ������Ʈ";
	temp += "\n\n\n\n";
	temp += "R - ���÷���";
	m_mgr.menu_puls(0,temp);
	m_mgr.menu_input_puls(0,'a',1,"",false,checkSavefile,0);
	m_mgr.menu_input_puls(0,'b',0,"",false,tutorials,0);
	m_mgr.menu_input_puls(0,'c',0,"",false,tutorial2,0);
	m_mgr.menu_input_puls(0,'d',0,"",false,sprint1s,0);
	m_mgr.menu_input_puls(0, 'e', 1, "", false, sprint2s, 0);
	m_mgr.menu_input_puls(0,'R',0,"",false,replay_menu,0);
	

	temp = "���� ���� �����Ұž�?\n\n\n";
	temp += "a - ���� ĳ���ͷ� �����ϱ� (EASY)\n\n";
	temp += "b - ���� ĳ���� �����ϱ� (NORMAL)\n\n";
	m_mgr.menu_puls(1,temp);
	m_mgr.menu_input_puls(1,'a',2,"���� ���� ���� ��Ź��.\n",false,NULL,0);
	m_mgr.menu_input_puls(1,'b',3,"������. ��������.\n",false,NULL,0);
	m_mgr.menu_input_puls(1,VK_ESCAPE,0,"",false,NULL,0);

	
	temp = "ĳ���͸� �����մϴ�. (��� ���� ĳ���ʹ� ����3���� �����մϴ�)\n\n\n\n";
	temp += "a - �ΰ� ���� ���̹�             e - �䱫 �ϻ��� ���̽�\n\n";
	temp += "b - �ΰ� ������ ������           f - �ΰ� ������ ���ڿ�\n\n";
	temp += "c - �ΰ� ���� �糪��             g - ı�� ����� ���丮\n\n";
	temp += "d - ����ٱ� ���� �����         k - ���� �����\n\n";	
	temp += "\n\n";	
	m_mgr.menu_puls(2,temp);
	temp = " : ��Ƽ���� �� ������. ����� ȣ�ֹ���� ��� ���� ��������!\n";
	temp += " �������ʽ�) ź������ +3, ȸ������ +3\n";
	temp += " ���ʽ�) 24���� ȣ�־ƹķ�, ���� �ϰ� ���������ʴ´�.\n\n";
	temp += " �ʺ�����) f�� ������ �߻��� �� �ֽ��ϴ�. �� �����ϱ����� ������ ���� �����ô�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(2,'a',2,temp,true,select_named,0);
	temp = " : ���Ѱ��� & ��ð�����. ź���� �Ŀ�! �����ڸ��� ������!\n";
	temp += " �������ʽ�) �ֹ��������� +2, �ı��������� +3, ȸ������ +1\n";
	temp += " ���ʽ�) +2,+2 ���ڷ�, ������ ����, �ı��� ����å\n\n";
	temp += " �ʺ�����) zŰ�� ������ ���� MŰ�� ������ ���ϴ�. �׻� 5Ű�� ������ ���� ä��� �ٴսô�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(2,'b',2,temp,true,select_named,1);
	temp = " : ������ & ������ �۷���. �����ڴ��� �������!\n";
	temp += " �������ʽ�) �������� +2, ȸ������ +1, �ߵ����� +3\n";
	temp += " ���ʽ�)  ������ ����ī��(9), ����� ����ī��(9), �����ڸ� �ϰ� �����Ѵ�.\n\n";
	temp += " �ʺ�����) V�� ����ī�尡 ��밡���մϴ�. ������ ����ī��� ���� ���缭 ���ߵ������� �ݽô�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(2,'c',2,temp,true,select_named,2);
	temp = " : �ڵ�Ž�� & �ڵ�������. O�� TAB�� ����� �����������\n";
	temp += " �������ʽ�) ������� +1\n";
	temp += " ���ʽ�) +2,+2 �����, +2 ö����, +2 �߰� �߰���, ��óġ�Ṱ�� 2��, ������ 2��, ������ ����\n\n";	
	temp += " �ʺ�����) tab�� �ڵ�����, o�� �ڵ�Ž������ ���ϰ� ���� �����մϴ�. ���⿣ q�� ������ ���ü���.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(2,'d',2,temp,true,select_named,3);
	temp = " : ����! ����� �ڿ� �־��. ���ǽ��� ������ ��� �ϻ��ض�!\n";
	temp += " �������ʽ�) �ܰ����� +2, ���Ÿ������� +2\n";
	temp += " ���ʽ�) ��������Ư��, �Ŀ�����Ư��, 15���� �����(ȥ���� �����ϴ� ��������)\n\n";
	temp += " �ʺ�����) �������� �ƴҶ� �׻� ������ �� �����Դϴ�. �����ϼ���! �����߿��� ������ Ǯ���ϴ�.\n";
	temp += " �ڰ��ִ� ��븦 ��� �Ͻ��� �ܰ˽�ų�� ����ؼ� ġ������ ū �������� ���ϴ�.\n";	
	temp += " x�� ���� ���¿��� �������� Ŀ���� �ΰ� v�� ������ ������ ��ϴ�. �����Ⱑ �ִ��� Ȯ���ϼ���!\n\n\n";	
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(2,'e',2,temp,true,select_named,4);
	temp = " : �ݿ�! �ΰ� ���丣��. �׾ ��Ƴ��� �����϶�!\n";
	temp += " �������ʽ�) ü�� +20%, �������� +2, ȭ���������� +2\n";
	temp += " ���ʽ�) 2������ ��Ȱ����(9����, 18������ �ٴٸ��� ����)\n\n";
	temp += " �ʺ�����) �׾ 2���� ���ؼ� ��Ȱ�� �����մϴ�. ��Ȱ�Ҷ� ü�°� ������ ȸ���ǰ� �����մϴ�.\n";
	temp += " �����ʰ� 9����, 18������ �ٴٸ��� ��Ȱ�ɷ��� 1���� ������ϴ�. �׷��� �״� �Ϳ� �η�������������!\n\n\n";	
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(2,'f',2,temp,true,select_named,5);
	temp = " : �°�! Ʈ���̾ƽ����� ı��. �������� ������ �����϶�!\n";
	temp += " �������ʽ�) �б����� +2  �ߵ����� +1\n";
	temp += " ���ʽ�) õ ı�Ŀʰ� ���߾��, �׽��� ����Ʈ ������ ��� �����Ѵ�.\n\n";
	temp += " �ʺ�����) V�� �̿��Ͽ� �ߵ����� ��� �����մϴ�. ���߾�ڴ� ��Ÿ� ź���� �߻��մϴ�.\n";
	temp += " �������� ����Ʈ ������ ����ġ�� ��Ƽ� ������ �����մϴ�. 100% ������ ������ VŰ�� �׽ø� ��ݽ�Ű����!\n";
	temp += " �ߵ����� �������� �������� P�� �Ҹ� �ݷ��ϴ� ������ �ݹ��Դϴ�. ������ ���� �οﶧ ����սô�.\n\n\n";	
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(2,'g',2,temp,true,select_named,6);
	temp = " : ����������! ���� �����. ȥ�ں��� ���� �ο���!\n";
	temp += " ���ʽ�) ������ �ϰ� �ٸ� �� ������ ���ᰡ �Ǿ� �����Ѵ�.\n\n\n";
	temp += " �ʺ�����) �׻� ����� �Բ� �ο� �� �ֽ��ϴ�. ����� �׾ ����ġ�� �Դٺ��� ��Ȱ�մϴ�.\n";
	temp += " aŰ�� ���� �Ǵ��� �� �� �ֽ��ϴ�. ���ο� ���� ���Ḧ ��ų� ���Ḧ ȣ���ϸ鼭 �ο�ô�.\n";
	temp += " ���ᰡ ��Ƶ� ��� ����ġ�� �ٸ����ʽ��ϴ�. �ڽ��� ������ �ֿ켱���� ��ŵ�ô�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(2, 'k', 5, temp, true, select_named, 7);
	m_mgr.menu_input_puls(2,VK_ESCAPE,1,"",false,NULL,0);

	
	temp = "������ �����մϴ�.\n\n\n";
	for(int i=0;i<TRI_MAX-1;i++)
	{
		char tempchar[64];
		sprintf_s(tempchar,"%c - %s",'a'+i,tribe_type_string[i]);
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
	temp = "�ΰ�: ����� ���Ȱ� ����� ����. �������� ������.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'a',4,temp,true,select_char,0);
	temp = "����: �������μ��� ������. ���������� ���ϰ� ������ �� �ٷ��.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'b',4,temp,true,select_char,1);
	temp = "����: ���Ҹ����� �ߴٷ����� �ſ� �����ϰ� ������ �۾Ƽ� ���ſ� ������ ���� ���Ѵ�.\n";
	temp += "���� ü��, ���� ����°� ���� ���ڽ��� ��� �����ϸ� ������ �������� �ݰ��ؼ� �޴´�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'c',4,temp,true,select_char,2);
	temp = "ī���ٱ�: ������ ����. ������ �����ɷ°� ���� ��⸶�� ������ ������.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'d',4,temp,true,select_char,3);
	temp = "����ٱ�: 10% ����ü��, ���� ���� ���� ������ ������. ������ �� �� �ٷ��.\n";
	temp += "���� �� ���̸� ��� ������ �������ݿ��� �߰������� �� �� �ִ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'e',4,temp,true,select_char,4);
	temp = "ı��: ���� â��ų ���õ��� ������������ ������ �����ϴ�.\n";
	temp += "�Ұ� ���������� ������ ������ ���� ������ ������. ���� �ſ� ���� �ߵ������� �����.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'f',4,temp,true,select_char,5);
	temp = "���ڸ�Ÿ: ���� �̵��ӵ��� �����, ������ �ڶ��־� �Ǽհ����� ���ϴ�.\n";
	temp += "ü���� ���ϰ� ����,����,���д� �� �ٷ��� ���Ѵ�.\n";
	temp += "�Ӽ������� �� �ٷ����������� ���ݼ�, ���Ÿ���, Ư�� ���̸����� ���ϴ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'g',4,temp,true,select_char,6);
	temp = "����ǻ���: ���� �̵��ӵ��� �������� ���� ü�°� ������ ���� �ܴ������� ��� ���̰� �ִ�.\n";
	temp += "���������� �� ���ڰ� ������ ���������� �������� ���� ������ Ư�⳪�� ����.\n";
	temp += "������ �� �� �ְ� ���������� 1�ܰ� ��� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'h',4,temp,true,select_char,7);
	temp = "�����𰡹�: ������ �۰� �������� ������ �����Ѵ�.\n";
	temp += "�������� ������ ���� ���̰� ���� ������ �׸� ���� ���ϴ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'i',4,temp,true,select_char,8);
	temp = "����: ���� �������� ������������ ����� ������ �� �ٷ��� ���Ѵ�.\n";
	temp += "������ Ŀ�� ���ſ� ������ �������� ü���� ���� ���� �޷��� �߰��������� �ش�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'j',4,temp,true,select_char,9);
	temp = "�ݿ�: ������ ������ ������ ���� �������� �����ذ��鼭\n";
	temp += "�䱫�� Ư���� �����Ǿ� ���� ����������. 4����, 9����, 13����, 18������ Ư���� ��´�.\n";
	temp += "4������ ��� �䱫�� �Ǹ� �̾�޾Ҵ��� �������� ���� Ư���� �ű⿡ ���缭 ����ȴ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'k',4,temp,true,select_char,10);
	temp = "����: �ñ����װ� �������� ��� �����ϰ� ���� ����ġ�� ������.\n";
	temp += "��ü���� ������ ���۴�� �ٸ� ������ ���� ü�������� ������ ���̴�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'l',4,temp,true,select_char,11);
	temp = "�����̾�: ���� ü������°� ���� ����������� ����� ü���� �Ҹ��Ͽ� ������ �� �� �ִ�.\n";
	temp += "���� ����,����,ȸ�������� �������� ����,���������� ���ڴ�. ���������� ��ü������ ������������\n";
	temp += "���ݼ��� �� ���ٷ�� ���̰� ��ȯ�� ������ ����. �����Ⱑ �ְ� P�� �ڿ��Ҹ� ���� ���̴�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(3,'m',4,temp,true,select_char,12);
	m_mgr.menu_input_puls(3,VK_ESCAPE,1,"",false,NULL,0);

	
	temp = "������ �����մϴ�.\n\n\n";
	for(int i=0;i<JOB_MAX;i++)
	{
		char tempchar[64];
		sprintf_s(tempchar,"%c - %s",'a'+i,job_type_string[i]);
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
	temp = "����: �������� ���� ������ ��ȣ�ϴ� �߰� ����\n";
	temp += "������ ����� ���ſ� ����, ������ ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'a',5,temp,true,select_job,0);
	temp = "������: �پ��� ��Ȳ���� ������ �� �ִ� ������ ���� ����Ѵ�.\n";
	temp += "�ʺ� �������� å�� ��� ������ ź���� ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'b',5,temp,true,select_job,1);
	temp = "����: ī������ ����� ī������ ���� ����Ͽ� �����ϴ� �������� �����̴�.\n";
	temp += "����δ� ������(�б�)�� ��� ���ູ�� ī���ڸ� �ϰ� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'c',5,temp,true,select_job,2);
	temp = "������: ���Ÿ��� ������ ���� ì��� ���̺긮�� ȸ��������.\n";
	temp += "������ ����� ��� ź��, �׸��� ���� ���и� ��� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'d',5,temp,true,select_job,3);
	temp = "������: �Ǽհ����� ����� �ִ� ������.\n";
	temp += "�Ǽհ�����ų�� ���� ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'e',5,temp,true,select_job,4);
	temp = "������: ������ ���������� �Ѵ� ì��� ������ ���� ��������.\n";
	temp += "������ ����� �ʺ� �������� å�� ���ϸ��� ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'f',5,temp,true,select_job,5);
	temp = "������: �ش����� �������� �ſ� �������� ��� ��� �����Ѵ�.\n";
	temp = "������ �κ긦���������� ������2���� ��� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'g',5,temp,true,select_job,6);
	temp = "ȭ������: ȭ���� �ٷ�� ȭ�������� ���� �����ϴ� ���Ҹ�����.\n";
	temp += "�ʺ� ȭ�������� å�� ��� �Ҳ��� ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'h',5,temp,true,select_job,7);
	temp = "�ñ����: �ñ⸦ �ٷ�� �ñ⸶���� ���� �����ϴ� ���Ҹ�����.\n";
	temp += "�ʺ� �ñ������ å�� ��� �ñ⸦ ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'i',5,temp,true,select_job,8);
	temp = "��������: ������ �ٷ�� ���������� ���� �����ϴ� ���Ҹ�����.\n";
	temp += "�ʺ� ���������� å�� ��� ���ָ��� ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'j',5,temp,true,select_job,9);
	temp = "������: ���� ���⸦ �ٷ�� ��⸶���� ���� �����ϴ� ���Ҹ�����.\n";
	temp += "�ʺ� �������� å�� ��� ������ ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'k',5,temp,true,select_job,10);
	temp = "��ȯ����: ��ȯ���� �ٷ�� ��ȯ������ ���� �����ϴ� ������.\n";
	temp += "�ʺ� ��ȯ������ å�� ��� ��� ��ȯ�� ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'l',5,temp,true,select_job,11);
	temp = "���ݼ���: ���ݼ��� ����Ͽ� ���������� �ϴ� ������ �� ���ݼ���.\n";
	temp += "�ʺ� ���ݼ����� å�� ��� ���ָ��� ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'m',5,temp,true,select_job,12);
	temp = "�ɸ�����: ��븦 �����ϴ� �ɸ������� ���� ������� ���� ������.\n";
	temp += "�ʺ� �ɸ������� å�� ��� �ָ��� ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'n',5,temp,true,select_job,13);
	temp = "���: ������ ��¡�ϴ� �Ŵ��� ���� ��� �����ϴ� ������ �����.\n";
	temp += "���ֹ��� +3 ���� �κ긦 ���� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'o',5,temp,true,select_job,14);
	temp = "���ŵ�: Ư�� �ſ� ������ ������ ������ �ִ� ���ڵ�.\n";
	temp += "�ٽ� �Ǵ� ��ī���� �ϰ� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'p',5,temp,true,select_job,15);
	temp = "�ϻ���: ���ż��� �ϻ��� �밡��� ���� ����ϰ� ����Ѵ�.\n";
	temp += "�ܰ˰� ��ħ, ���� ����ġ�� ������ �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'q',5,temp,true,select_job,16);
	temp = "���: �츮���� ���� ���� �� �ֵ��� ��縦 �����ô� ����� �е�.\n";
	temp += "������ ����� 3���� ��, �̳븮�ڸ� �ϰ� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'r',5,temp,true,select_job,17);
	temp = "���̵�: �ܰ����� �����°� ���̵��� �⺻ �Ҿ� �ƴѰ���?\n";
	temp += "���ڷ�� 4���� ��ô�� �������� ���̵��� ��, �׸��� ���̵��� �⺻�Ҿ��� ��� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'s',5,temp,true,select_job,18);
	temp = "�����: ������ �� �ٷ�� ���� �����.\n";
	temp += "������ ����� �ñ� ����ī�带 ��� �����Ѵ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'t',5,temp,true,select_job,19);
	temp = "������: �쿬�� ȯ���⿡ �귯������ �츮���̴�?\n";
	temp += "���İ� ���� ������ ��������ʴ� ī�޶� ��� �����Ѵ�.\n";
	temp += "�ƹ��� �ɷµ� ���� ������ �ױ����� ����Կ� ������ �� �� ���� �� ����.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(4,'u',5,temp,true,select_job,20);
	m_mgr.menu_input_puls(4,VK_ESCAPE,3,"",false,NULL,0);

	temp = "ĳ���͸� �����մϴ�. \n\n\n\n";
	temp += "a - ���� ������ ���\n\n";
	temp += "b - ���� ������ ��Ÿ\n\n";
	temp += "c - ���� �ϻ��� �糪\n\n";
	temp += "\n\n\n";
	m_mgr.menu_puls(5, temp);
	temp = "���: 3������ ���� �ٷ�� �޺��� ����.\n\n\n";
	temp += " �������ʽ�) �ֹ��������� +1, �ı��������� +2 \n";
	temp += " ���ʽ�) �糪�� ħ������ ��� ��ȸ���� ��� �����Ѵ�.\n\n";
	temp += " �ʺ�����) ������� ȥ�ڼ� �ο�� ���� �ƴ϶� ���̼� �ο�ϴ�.\n";
	temp += " �����Ҷ��� �ڽ��� ����� ���� �߿��ϴٴ°� ����ϼ���. ������� �׾ ��Ȱ�մϴ�.\n";
	temp += " ���� ȥ�ڰ� �Ǿ������� �Ҹ�ǰ�� �Ƴ���������. ���ᰡ �������� ���� ����մϴ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(5,'a',6,temp,true,select_fairy,0);
	temp = "��Ÿ: 3������ ��ô�� �����ϴ� ������ ����.\n\n\n";
	temp += " �������ʽ�) �������� +1, ȸ������ +1, ���ݼ����� +1 \n";
	temp += " ���ʽ�) ������ Ư���� ������ �����Ѵ�.\n\n";
	temp += " �ʺ�����) ������� ȥ�ڼ� �ο�� ���� �ƴ϶� ���̼� �ο�ϴ�.\n";
	temp += " �����Ҷ��� �ڽ��� ����� ���� �߿��ϴٴ°� ����ϼ���. ������� �׾ ��Ȱ�մϴ�.\n";
	temp += " ���� ȥ�ڰ� �Ǿ������� �Ҹ�ǰ�� �Ƴ���������. ���ᰡ �������� ���� ����մϴ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(5,'b',6,temp,true, select_fairy,1);
	temp = "�糪: 3������ �Ҹ��� ����� �޺��� ����.\n\n\n";
	temp += " �������ʽ�) �ܰ�����+1, �������� +1, ���Ÿ������� +1\n";
	temp += " ���ʽ�) ħ�� �η縶���� 5�� ��� �����Ѵ�.\n\n";
	temp += " �ʺ�����) ������� ȥ�ڼ� �ο�� ���� �ƴ϶� ���̼� �ο�ϴ�.\n";
	temp += " �����Ҷ��� �ڽ��� ����� ���� �߿��ϴٴ°� ����ϼ���. ������� �׾ ��Ȱ�մϴ�.\n";
	temp += " ���� ȥ�ڰ� �Ǿ������� �Ҹ�ǰ�� �Ƴ���������. ���ᰡ �������� ���� ����մϴ�.\n\n\n";
	temp += "���� Ű�� �ѹ� �� �����ų� ���͸� �ļ� �����Ѵ�.\n";
	m_mgr.menu_input_puls(5, 'c', 6, temp, true, select_fairy, 2);





	m_mgr.loop(0);
}

