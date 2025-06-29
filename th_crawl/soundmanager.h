
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
#include <fmod.hpp>
#pragma comment (lib, "dsound")
using namespace std;


class FMODSoundManager {
	float bgmFadeVolume = 1.0f;
	float bgmTargetVolume = 1.0f;
	bool bgmFadingOut = false;
	std::string pendingBgmName;
	std::string lastErrorString;
public:
    FMODSoundManager();
    ~FMODSoundManager();

    void Initialize();
    void Update();
    void addSound(const std::string& name, const std::string& path, bool loop = false);
    void addBgm(const std::string& name, const std::string& path);
	void addBgm(const std::string& name, const std::string& path, unsigned int loopStartMs, unsigned int loopEndMs);
	void loadBgmFromJson(const std::string& filename);
    void playSound(const std::string& name);
    bool playBgm(const std::string& name);
    void stopCurrentBGM(const std::string& except = "");
    void setBgmVolume(int vol); // 0~100
    void setSEVolume(int vol);  // 0~100

private:
    FMOD::System* system;
    std::map<std::string, FMOD::Sound*> soundList;
    std::map<std::string, FMOD::Sound*> bgmList;
    FMOD::Channel* currentBgmChannel;
    std::string currentBgmName;
    int seVolume;
    int bgmVolume;
};



//


extern FMODSoundManager fmodsoundmanager;


void InitSound(HWND windowhandle_);

void SetBgmVolume(int value_);
void SetSEVolume(int value_);

void PlaySE(const char* name);
boolean PlayBGM(const char* name);
void StopCurrentBGM(const char* except = NULL);

void UpdateBGM();

#endif // __SOUND_H__