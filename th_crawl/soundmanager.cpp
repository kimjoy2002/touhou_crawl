//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sound.cpp
//
// 내용: 사운드- by audiere-1.9.4
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "soundmanager.h"
#include "option_manager.h"
#include <fmod_errors.h>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

FMODSoundManager fmodsoundmanager;

FMODSoundManager::FMODSoundManager()
    : system(nullptr), currentBgmChannel(nullptr), seVolume(100), bgmVolume(100) {}

FMODSoundManager::~FMODSoundManager() {
    for (auto& pair : soundList) pair.second->release();
    for (auto& pair : bgmList) pair.second->release();
    if (system) {
        system->close();
        system->release();
    }
}

void FMODSoundManager::Initialize() {
    FMOD::System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, nullptr);

	addSound("hit", "sound\\se\\hit.mp3");
	addSound("lowhp", "sound\\se\\lowhp.mp3");
	addSound("gameover", "sound\\se\\gameover.mp3");
	addSound("pickup", "sound\\se\\pickup.mp3");
	addSound("levelup", "sound\\se\\levelup.mp3");

	addSound("damaged", "sound\\se\\damaged.mp3");
	addSound("evade", "sound\\se\\evade.mp3");
	addSound("block", "sound\\se\\block.mp3");

	addSound("kill_banashed", "sound\\se\\kill_banashed.mp3");
	addSound("kill", "sound\\se\\kill.mp3");
	addSound("kill_named", "sound\\se\\kill_named.mp3");

	addSound("shoot", "sound\\se\\shoot.mp3");

	addSound("potion", "sound\\se\\potion.mp3");
	addSound("scroll", "sound\\se\\scroll.mp3");
	addSound("equip", "sound\\se\\equip.mp3");


	addSound("stair", "sound\\se\\stair.mp3");
	addSound("spellcard", "sound\\se\\spellcard.mp3");
	addSound("god", "sound\\se\\god.mp3");

	addSound("bomb", "sound\\se\\bomb.mp3");
	addSound("fire", "sound\\se\\fire.mp3");
	addSound("cold", "sound\\se\\cold.mp3");
	addSound("elec", "sound\\se\\elec.mp3");
	addSound("stone", "sound\\se\\stone.mp3");
	addSound("wind", "sound\\se\\wind.mp3");
	addSound("summon", "sound\\se\\summon.mp3");
	addSound("blink", "sound\\se\\blink.mp3");


	addSound("buff", "sound\\se\\buff.mp3");
	addSound("soul_shot", "sound\\se\\soul_shot.mp3");
	addSound("sickle", "sound\\se\\sickle.mp3");
	addSound("namaz", "sound\\se\\namaz.mp3");
	addSound("earthquake", "sound\\se\\earthquake.mp3");
	addSound("howl", "sound\\se\\howl.mp3");
	addSound("timestop", "sound\\se\\timestop.mp3");
	addSound("nuke", "sound\\se\\nuke.mp3");
	addSound("ufo", "sound\\se\\ufo.mp3");
	addSound("spark", "sound\\se\\spark.mp3");
	addSound("laser", "sound\\se\\laser.mp3");
	addSound("shoot_heavy", "sound\\se\\shoot_heavy.mp3");
	addSound("nyan", "sound\\se\\nyan.mp3");
	addSound("smite", "sound\\se\\smite.mp3");
	addSound("laugh", "sound\\se\\laugh.mp3");
	addSound("step", "sound\\se\\step.mp3");
	addSound("powerup", "sound\\se\\powerup.mp3");
	addSound("throw", "sound\\se\\throw.mp3");
	addSound("debuf", "sound\\se\\debuf.mp3");
	addSound("curse", "sound\\se\\curse.mp3");
	addSound("jump", "sound\\se\\jump.mp3");
	addSound("water", "sound\\se\\water.mp3");
	addSound("warning", "sound\\se\\warning.mp3");
	addSound("charge", "sound\\se\\charge.mp3");
	addSound("camera", "sound\\se\\camera.mp3");
	addSound("rune", "sound\\se\\rune.mp3");
	addSound("knife", "sound\\se\\knife.mp3");
	addSound("thunder", "sound\\se\\thunder.mp3");
	addSound("door", "sound\\se\\door.mp3");
	addSound("royalflare", "sound\\se\\royalflare.mp3");

    
	loadBgmFromJson("sound\\bgm\\bgm.json");
}

void FMODSoundManager::Update() {
    if (system) system->update();
    // 페이드 처리
    if (currentBgmChannel) {
        if (bgmFadeVolume != bgmTargetVolume) {
            float fadeSpeed = 0.01f; // 조절 가능: 0.01~0.1

            if (bgmFadeVolume < bgmTargetVolume) {
                bgmFadeVolume = std::min(bgmFadeVolume + fadeSpeed, bgmTargetVolume);
            } else {
                bgmFadeVolume = std::max(bgmFadeVolume - fadeSpeed, bgmTargetVolume);
            }

            currentBgmChannel->setVolume(bgmFadeVolume * (bgmVolume / 100.0f)*0.8f);

            if (bgmFadingOut && bgmFadeVolume <= 0.0f) {
                currentBgmChannel->stop();
                currentBgmChannel = nullptr;
                currentBgmName.clear();
                bgmFadingOut = false;
            }
        }
    }

    // 페이드가 완료되었고 예약곡이 있으면 자동 재생
    if (!bgmFadingOut && !pendingBgmName.empty()) {
        std::string next = pendingBgmName;
        pendingBgmName.clear();
        currentBgmName.clear();
        playBgm(next);  // 자동으로 다시 재생 시도
    }
}

void FMODSoundManager::addSound(const std::string& name, const std::string& path, bool loop) {
    FMOD::Sound* sound = nullptr;
    FMOD_RESULT result = system->createSound(path.c_str(), loop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, 0, &sound);
	if(result != FMOD_OK) {
		lastErrorString = FMOD_ErrorString(result);
	}
    soundList[name] = sound;
}

void FMODSoundManager::addBgm(const std::string& name, const std::string& path) {
    FMOD::Sound* bgm = nullptr;
    FMOD_RESULT result = system->createSound(path.c_str(), FMOD_LOOP_NORMAL | FMOD_CREATESTREAM, 0, &bgm);
	if(result != FMOD_OK) {
		lastErrorString = FMOD_ErrorString(result);
	}
    bgmList[name] = bgm;
}

void FMODSoundManager::addBgm(const std::string& name, const std::string& path,
                              unsigned int loopStartMs, unsigned int loopEndMs) {
    FMOD::Sound* bgm = nullptr;
    FMOD_RESULT result = system->createSound(path.c_str(),
        FMOD_LOOP_NORMAL | FMOD_CREATESTREAM, 0, &bgm);

    if (result == FMOD_OK && bgm) {
        // loopStartMs / loopEndMs 단위: 밀리초 → sample 단위로 변환 필요
        // mp3라면 시간 기준으로 직접 지정해도 됨 (MS 단위로)
        bgm->setLoopPoints(loopStartMs, FMOD_TIMEUNIT_MS, loopEndMs, FMOD_TIMEUNIT_MS);
    }

    bgmList[name] = bgm;
}

void FMODSoundManager::loadBgmFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        lastErrorString = "Failed to open BGM config file: " + filename;
        return;
    }

    json j;
    try {
        file >> j;
    } catch (std::exception& e) {
        lastErrorString = "JSON parsing error: ";
        lastErrorString += e.what();
        return;
    }

    for (const auto& entry : j) {
		std::string name = entry["name"].get<std::string>();     // 명시적 형변환
		std::string path = entry["path"].get<std::string>();

        FMOD::Sound* bgm = nullptr;
        FMOD_RESULT result = system->createSound(path.c_str(),
            FMOD_LOOP_NORMAL | FMOD_CREATESTREAM, 0, &bgm);
		if(result != FMOD_OK) {
			lastErrorString = FMOD_ErrorString(result);
		}
        if (result == FMOD_OK && bgm) {
			if (entry.contains("loop_start") && entry.contains("loop_end")) {
				int loopStart = entry["loop_start"].get<int>();
				int loopEnd = entry["loop_end"].get<int>();
				bgm->setLoopPoints(loopStart, FMOD_TIMEUNIT_MS, loopEnd, FMOD_TIMEUNIT_MS);
			}
            bgmList[name] = bgm;
        }
    }
}

void FMODSoundManager::playSound(const std::string& name) {
    auto it = soundList.find(name);
    if (it == soundList.end()) return;

    auto chIt = playingSE.find(name);
    if (chIt != playingSE.end() && chIt->second) {
        bool isPlaying = false;
        chIt->second->isPlaying(&isPlaying);
        if (isPlaying) {
            chIt->second->stop(); // 재시작을 위해 중단
        }
    }


    FMOD::Channel* channel = nullptr;
    FMOD_RESULT result = system->playSound(it->second, 0, false, &channel);
	if(result != FMOD_OK) {
		lastErrorString = FMOD_ErrorString(result);
	}

    if (channel) {
        float vol = seVolume / 100.0f;
        channel->setVolume(vol);
        playingSE[name] = channel;
    }
}

bool FMODSoundManager::playBgm(const std::string& name) {
    if (name == currentBgmName && !bgmFadingOut) return false;


    // 현재 페이드아웃 중이면 예약만 함
    if (bgmFadingOut) {
        pendingBgmName = name;
        return false;
    }

    if (currentBgmChannel) {
        pendingBgmName = name;
        stopCurrentBGM(); // 일단 기존 BGM 페이드 아웃
        return false;
    }

    auto it = bgmList.find(name);
    if (it != bgmList.end()) {
        system->playSound(it->second, 0, true, &currentBgmChannel); // 일시 정지된 상태로 시작
        currentBgmChannel->setVolume(0.0f);  // 시작 볼륨 0
        currentBgmChannel->setPaused(false); // 재생 시작

        currentBgmName = name;
        bgmFadeVolume = 0.0f;
        bgmTargetVolume = 1.0f;
        bgmFadingOut = false;
        return true;
    }
    return false;
}

void FMODSoundManager::stopCurrentBGM(const std::string& except) {
    if (!except.empty() && currentBgmName == except) return;
    if (currentBgmChannel) {
        bgmTargetVolume = 0.0f;
        bgmFadingOut = true;
    }
}

void FMODSoundManager::setBgmVolume(int vol) {
    bgmVolume = vol;
    if (currentBgmChannel) {
        currentBgmChannel->setVolume(bgmVolume / 100.0f*0.8f);
    }
}

void FMODSoundManager::setSEVolume(int vol) {
    seVolume = vol;
}


void InitSound(HWND windowhandle_)
{
	fmodsoundmanager.Initialize();
}

void PlaySE(const char* name)
{
	fmodsoundmanager.playSound(name);
}
boolean PlayBGM(const char* name)
{
	return fmodsoundmanager.playBgm(name);
}
void SetBgmVolume(int value_)
{
	fmodsoundmanager.setBgmVolume(value_);
}

void SetSEVolume(int value_)
{
	fmodsoundmanager.setSEVolume(value_);
}
void StopCurrentBGM(const char* except)
{
	if(except == nullptr) {
		fmodsoundmanager.stopCurrentBGM("");
	} else {
		fmodsoundmanager.stopCurrentBGM(except);
	}
}
void UpdateBGM()
{
	fmodsoundmanager.Update();
}