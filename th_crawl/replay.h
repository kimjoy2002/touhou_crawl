//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: replay.h
//
// 내용: 리플레이
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "player.h"


struct base_infor
{	
     char name[32];
	 char version[32];
	 char infor[256];
     unsigned int rand_num;
};

class replay_class
{
public:
	string replay_string;
	base_infor infor;
	bool init;
	bool play;
	bool auto_key;
	FILE *play_fp;  


	replay_class():replay_string(),init(false),play(false),auto_key(false),play_fp(NULL){};
	~replay_class();
	
	void DeleteRpy();


	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);

	void init_class();
	void init_replay(const char* name);
	
	bool SaveReplayStart();
	bool SaveReplayInput(DWORD time_, int key_);
	
	bool LoadReplayStart();
	bool LoadReplayInput(DWORD *time_, int *key_);

	bool ReplayMode(){return play;};

	bool StopReplay(const char* str);
};


extern replay_class ReplayClass;