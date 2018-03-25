
//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sound.h
//
// 내용: 사운드
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SOUND_H__
#define  __SOUND_H__

#include <dsound.h>
#include <math.h>
#include <map>
#include <string>
#pragma comment (lib, "dsound")
using namespace std;


enum
{
	SOUND_BUFFER_MAX = 20
};



class SOUNDBUFFER
{
public:
	IDirectSoundBuffer8* SoundBuffer;
	IDirectSoundBuffer* PlusBuffer[SOUND_BUFFER_MAX];
	bool IsPlaying;
	bool IsLooping;
	bool IsStreaming;
	bool IsOverlab;
	long Volume;
	int Up_time;
	int Down_time;
	int stream_limit; //자동으로 곡이 끊기는 시간
	int play_time; //플레이 함수로 플레이후 지난시간

	SOUNDBUFFER();
	~SOUNDBUFFER();

	void Load(IDirectSound8* Sound, char* WaveFileName, bool Streaming, bool Looping, bool overlab);
	void Unload();
	void BufferUpdate();
	void PlaySound();
	boolean StopSound();
	void SetVolume();

private:
	HMMIO hmmio;
	DWORD WaveSize;
	DWORD BufferSize;
	DWORD DataStart;
	DWORD DataCursor;
	DWORD BytesRead;
};


class SOUNDMANAGER
{
public:
	IDirectSound8* Sound;
	SOUNDBUFFER* stop_bgm;
	SOUNDBUFFER* current_bgm;

	bool bgm_on;
	bool se_on;

	float BackgroundVolume;
	float VoiceVolume;
	float EffectVolume;

	map<std::string, SOUNDBUFFER*> bgmList;
	map<std::string, SOUNDBUFFER*> soundList;


	SOUNDMANAGER();
	~SOUNDMANAGER();

	void Initialize(HWND WindowHandle);
	//void Duplicate(SOUNDBUFFER **buffer_);
	void Update();

	void addSound(const char* name, char* path, bool Looping, bool overlab);
	void addBgm(const char* name, char* path);

	void playSound(const char* name);
	boolean playBgm(const char* name);

	void stopCurrentBGM(const char* except);

	void SetBgmOn(bool on_) { bgm_on = on_; };
	void SetBgmOnOff() { bgm_on = !bgm_on; };
	void SetSeOn(bool on_) { se_on = on_; };
	void SetSeOnOff() { se_on = !se_on; };
};

//
extern SOUNDMANAGER soundmanager;



void InitSound(HWND windowhandle_);

void PlaySE(const char* name);
boolean PlayBGM(const char* name);
void StopBGM(SOUNDBUFFER* sound_);
void StopCurrentBGM(const char* except = NULL);

void UpdateBGM();

#endif // __SOUND_H__