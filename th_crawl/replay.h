//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: replay.h
//
// 내용: 리플레이
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "player.h"
#include <vector>



struct base_infor
{	
     char name[64];
	 char version[32];
	 char infor[256];
     unsigned int rand_num;
	 int starting[4];
};

class replay_class
{
	
	struct ReplayInputEntry {
		DWORD time_;
		int key_;
		InputedKey inputedkey;
	};
public:
	string replay_string;
	base_infor infor;
	bool init;
	bool play;
	bool auto_key;
	FILE *play_fp;
	std::vector<ReplayInputEntry> input_buffer;


	replay_class():replay_string(),init(false),play(false),auto_key(false),play_fp(NULL){};
	~replay_class();
	
	void DeleteRpy();


	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);

	void init_class(std::vector<int>& init_starting);
	void init_replay(const char* name);
	
	bool SaveReplayStart();
	bool SaveReplayInput(DWORD time_, int key_, InputedKey inputedkey);
	bool FlushReplayInput();
	
	bool LoadReplayStart();
	bool LoadReplayInput(DWORD *time_, int *key_, InputedKey& inputedkey);

	bool ReplayMode(){return play;};

	bool StopReplay(string str);
};


extern replay_class ReplayClass;