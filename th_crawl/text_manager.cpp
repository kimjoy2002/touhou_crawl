//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: display.cpp
//
// 내용: 크롤의 출력
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "textureUtility.h"
#include "texture.h"
#include "display.h"
#include "const.h"


extern IDirect3DDevice9* Device; //디바이스포인터
extern IDirect3DVertexBuffer9* g_pVB; //버텍스버퍼포인터
extern D3DXMATRIXA16 g_BaseMatrix; //매트릭스포인터
extern LPD3DXSPRITE g_pSprite; //스프라이트포인터 
extern ID3DXFont* g_pfont;
extern HANDLE mutx;
extern display_manager DisplayManager;

text_manager::~text_manager()
{
	list<text_dummy*>::iterator it;
	for (it=text_list.begin();it!=text_list.end();it++)
	{
		delete *it;
	}
}

bool text_manager::add_text(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_)
{
	WaitForSingleObject(mutx, INFINITE);
	while(!text_list.empty())
	{
		list<text_dummy*>::iterator it;
		it = text_list.end();
		it--;
		if((*it)->temp && !temp_)
		{
			if((*it)->enter)
			{				
				length--;
				if(short_len>0)
				short_len--;
			}
			delete *it;
			text_list.erase(it);
		}
		else
			break;
	}
	text_list.push_back(new text_dummy(text_,enter_,log_,temp_,color_));
	if(enter)
	{
		if(short_len<6)
			short_len++;
		enter = false;
	}
	if(enter_)
	{
		enter = true;
		length++;
	}
	ReleaseMutex(mutx);
	return true;
}

void text_manager::DeleteTemp()
{
	WaitForSingleObject(mutx, INFINITE);
	while(!text_list.empty())
	{
		list<text_dummy*>::iterator it;
		it = text_list.end();
		it--;
		if((*it)->temp)
		{
			if((*it)->enter)
			{				
				length--;
				if(short_len>0)
				short_len--;
			}
			delete *it;
			text_list.erase(it);
		}
		else
			break;
	}
	ReleaseMutex(mutx);
}
void text_manager::SetEnter()
{
	WaitForSingleObject(mutx, INFINITE);
	if(!text_list.empty())
	{
		if(text_list.back()->enter == false)
		{
			text_list.back()->enter = true;
			length++;
		}
	}
	ReleaseMutex(mutx);
}


void text_manager::reset()
{
	WaitForSingleObject(mutx, INFINITE);
	text_list.clear();
	length=0;
	short_len=0;
	ReleaseMutex(mutx);
}

string& SetText()
{
	return DisplayManager.text;
}
void printlog(string text_, bool enter_, bool log_, bool temp_, D3DCOLOR color_)
{
	DisplayManager.text_log.add_text(text_, enter_, log_, temp_, color_);
}
void deletelog()
{
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.text_log.DeleteTemp();
	ReleaseMutex(mutx);
}
void enterlog()
{
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.text_log.SetEnter();
	ReleaseMutex(mutx);
}
void printarray(bool enter_, bool log_, bool temp_, D3DCOLOR color_, int num_, ...)
{
	va_list ap;
	string temp;
	va_start(ap,num_);
	for(int i=0; i < num_; i++)
	{
		temp+=va_arg(ap,char*);
	}
	va_end(ap);
	printlog(temp, enter_, log_, temp_, color_);
}


void printsub(string text_, bool enter_, D3DCOLOR color_)
{
	DisplayManager.text_sub.add_text(text_, enter_, false, false, color_);
}
void deletesub()
{
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.text_sub.reset();
	ReleaseMutex(mutx);
}
void entersub()
{
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.text_sub.SetEnter();
	ReleaseMutex(mutx);
}

void printarraysub(bool enter_, D3DCOLOR color_, int num_, ...)
{
	va_list ap;
	string temp;
	va_start(ap,num_);
	for(int i=0; i < num_; i++)
	{
		temp+=va_arg(ap,char*);
	}
	va_end(ap);
	printlog(temp, enter_, false, false, color_);
}



void SetSpellSight(int sight_, int sight_type_)
{
	WaitForSingleObject(mutx, INFINITE);
	DisplayManager.spell_sight = sight_;

	DisplayManager.sight_type = sight_type_;
	ReleaseMutex(mutx);
}