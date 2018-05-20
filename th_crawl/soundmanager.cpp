//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sound.cpp
//
// 내용: 사운드- by audiere-1.9.4
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "soundmanager.h"
#include "option_manager.h"
#include <fstream>
using namespace std;

SOUNDMANAGER soundmanager;


SOUNDBUFFER::SOUNDBUFFER()
{
	SoundBuffer = NULL;
	for (int i = 0; i< SOUND_BUFFER_MAX; i++)
		PlusBuffer[i] = NULL;
	IsPlaying = false;
	IsLooping = false;
	IsStreaming = false;
	IsOverlab = false;
	lazy_loading = false;
	quite = false;
	path = "";
	Volume = 100;
	stream_limit = 0;
	Down_time = 100;
	play_time = 0;

	hmmio = NULL;
	WaveSize = 0;
	BufferSize = 0;
	DataStart = 0;
	DataCursor = 0;
	BytesRead = 0;
}

SOUNDBUFFER :: ~SOUNDBUFFER()
{
	if (SoundBuffer != NULL)
	{
		SoundBuffer->Release();
		SoundBuffer = NULL;
	}
	for (int i = 0; i< SOUND_BUFFER_MAX; i++)
	{
		if (PlusBuffer[i] != NULL)
		{
			PlusBuffer[i]->Release();
			PlusBuffer[i] = NULL;
		}
	}

	if (hmmio != NULL)
	{
		mmioClose(hmmio, 0);
		hmmio = NULL;
	}
}
void SOUNDBUFFER::Load(IDirectSound8* Sound, const char* WaveFileName, bool Streaming, bool Looping, bool overlab)
{
	path = WaveFileName;
	ifstream infile;
	infile.open(WaveFileName);
	if (infile.fail())
	{
		return;
	}
	infile.close();

	hmmio = mmioOpen((char*)WaveFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);

	MMCKINFO ckRIFF;
	ZeroMemory(&ckRIFF, sizeof(MMCKINFO));
	ckRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	MMRESULT a = mmioDescend(hmmio, &ckRIFF, NULL, MMIO_FINDRIFF);


	MMCKINFO ckChunk;
	ZeroMemory(&ckChunk, sizeof(MMCKINFO));
	ckChunk.fccType = mmioFOURCC('f', 'm', 't', ' ');
	MMRESULT b = mmioDescend(hmmio, &ckChunk, &ckRIFF, MMIO_FINDCHUNK);


	WAVEFORMATEX WaveFormat;
	ZeroMemory(&WaveFormat, sizeof(WAVEFORMATEX));
	MMRESULT c = mmioRead(hmmio, (char*)&WaveFormat, sizeof(WAVEFORMATEX));

	mmioAscend(hmmio, &ckChunk, 0);
	ckChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	MMRESULT d = mmioDescend(hmmio, &ckChunk, &ckRIFF, MMIO_FINDCHUNK);

	if (Streaming == true)
	{
		WaveSize = ckChunk.cksize;
		BufferSize = WaveFormat.nAvgBytesPerSec;
	}
	else
	{
		WaveSize = ckChunk.cksize;
		BufferSize = ckChunk.cksize;
	}
	DataStart = mmioSeek(hmmio, 0, SEEK_CUR);

	DSBUFFERDESC desc;
	ZeroMemory(&desc, sizeof(DSBUFFERDESC));

	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2;
	desc.lpwfxFormat = &WaveFormat;
	desc.dwBufferBytes = BufferSize;

	IDirectSoundBuffer* tempSoundBuffer;

	Sound->CreateSoundBuffer(&desc, &tempSoundBuffer, NULL);
	tempSoundBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&SoundBuffer);
	tempSoundBuffer->Release();

	void* Ptr;
	DWORD Bytes;

	SoundBuffer->Lock(0, 0, &Ptr, &Bytes, NULL, NULL, DSBLOCK_ENTIREBUFFER);
	mmioRead(hmmio, (char*)Ptr, Bytes);
	SoundBuffer->Unlock(Ptr, Bytes, NULL, NULL);

	DataCursor += Bytes;
	BytesRead += Bytes;

	IsLooping = Looping;
	IsStreaming = Streaming;
	IsOverlab = overlab;

	if (overlab) {
		for (int i = 1; i< SOUND_BUFFER_MAX; i++) {
			Sound->DuplicateSoundBuffer(SoundBuffer, &PlusBuffer[i]);
		}
	}
}

void SOUNDBUFFER::Unload()
{
	if (SoundBuffer != NULL)
	{
		SoundBuffer->Release();
		SoundBuffer = NULL;
	}
	for (int i = 0; i< SOUND_BUFFER_MAX; i++)
	{
		if (PlusBuffer[i] != NULL)
		{
			PlusBuffer[i]->Release();
			PlusBuffer[i] = NULL;
		}
	}
	IsPlaying = false;

	if (hmmio != NULL)
	{
		mmioClose(hmmio, 0);
		hmmio = NULL;
	}

	WaveSize = 0;
	BufferSize = 0;
	DataStart = 0;
	DataCursor = 0;
	BytesRead = 0;
}

void SOUNDBUFFER::BufferUpdate()
{
	if (Down_time < 100)
	{
		if (StopSound())
			return;
		SetVolume();
	}
	if (Up_time < 100)
	{
		Up_time++;
		SetVolume();
	}

	if (!SoundBuffer)
		return;

	if (IsPlaying)
	{
		play_time++;
		if (stream_limit && play_time>stream_limit)
		{
			play_time = 0;
			IsPlaying = false;
		}
	}

	if (IsPlaying)
	{
		if (IsStreaming)
		{
			DWORD CurrentPlayCursor;
			SoundBuffer->GetCurrentPosition(&CurrentPlayCursor, NULL);

			DWORD DataToCopy;
			if (DataCursor < CurrentPlayCursor)
				DataToCopy = CurrentPlayCursor - DataCursor;
			else
				DataToCopy = BufferSize - DataCursor + CurrentPlayCursor;

			void* Ptr1;
			DWORD Bytes1;
			void* Ptr2;
			DWORD Bytes2;

			SoundBuffer->Lock(DataCursor, DataToCopy, &Ptr1, &Bytes1, &Ptr2, &Bytes2, 0);
			BytesRead += Bytes1 + Bytes2;
			if (BytesRead > WaveSize)
			{
				BytesRead = 0;
				mmioSeek(hmmio, DataStart, SEEK_SET);
				memset(Ptr1, 0x00, Bytes1);
				if (Ptr2 != NULL)
					memset(Ptr2, 0x00, Bytes2);

				if (IsLooping == false)
					StopSound();
			}
			else
			{
				mmioRead(hmmio, (char*)Ptr1, Bytes1);
				if (Ptr2 != NULL)
					mmioRead(hmmio, (char*)Ptr2, Bytes2);
			}
			SoundBuffer->Unlock(Ptr1, Bytes1, Ptr2, Bytes2);

			DataCursor += Bytes1 + Bytes2;
			DataCursor %= BufferSize;
		}
	}
	else
	{
		IsPlaying = true;
		StopSound();
	}

}

void SOUNDBUFFER::PlaySound()
{
	if (!SoundBuffer)
		return;

	if(IsStreaming)
		Up_time = 0;
	else
		Up_time = 100;

	Down_time = 100;
	SetVolume();
	IsPlaying = true;
	if (IsOverlab) {
		DWORD state = 0;

		SoundBuffer->GetStatus(&state);
		if (state == DSBSTATUS_PLAYING)
		{
			for (int i = 1; i< SOUND_BUFFER_MAX; i++) {
				PlusBuffer[i]->GetStatus(&state);
				if (state == DSBSTATUS_PLAYING)
					continue;

				if (IsLooping)
					PlusBuffer[i]->Play(0, 0, DSBPLAY_LOOPING);
				else
					PlusBuffer[i]->Play(0, 0, 0);
				break;

			}
			return;
		}
	}

	{
		if (IsLooping)
			SoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
		else
			SoundBuffer->Play(0, 0, 0);
	}
}

boolean SOUNDBUFFER::StopSound()
{
	if (Down_time && IsStreaming) {
		Down_time--;
		return false;
	}
	if (!SoundBuffer)
		return false;


	if (IsStreaming)
	{
		DWORD state = 0;
		SoundBuffer->GetStatus(&state);
		if (!IsPlaying)
			return false;

		void* Ptr1;
		DWORD Bytes1;
		void* Ptr2;
		DWORD Bytes2;

		SoundBuffer->Lock(0, 0, &Ptr1, &Bytes1, &Ptr2, &Bytes2, DSBLOCK_ENTIREBUFFER);

		BytesRead = 0;
		mmioSeek(hmmio, DataStart, SEEK_SET);
		memset(Ptr1, 0x00, Bytes1);
		if (Ptr2 != NULL)
			memset(Ptr2, 0x00, Bytes2);

		SoundBuffer->Unlock(Ptr1, Bytes1, Ptr2, Bytes2);

		DataCursor += Bytes1 + Bytes2;
		DataCursor %= BufferSize;
	}

	IsPlaying = false;
	SoundBuffer->SetCurrentPosition(0);
	SoundBuffer->Stop();
	if (IsOverlab) {
		for (int i = 1; i< SOUND_BUFFER_MAX; i++) {
			PlusBuffer[i]->Stop();
			PlusBuffer[i]->SetCurrentPosition(0);
		}
	}
	return true;
}

void SOUNDBUFFER::SetVolume()
{
	if (Volume > 100)
		Volume = 100;
	if (Volume < 0)
		Volume = 0;
	int Volume_ = Volume * Down_time / 100;
	Volume_ = Volume_ * Up_time / 100;
	if (Volume_ > 100)
		Volume_ = 100;
	if (quite)
		Volume_ = 0;
	if (!SoundBuffer)
		return;


	if (Volume_ == 0)
		SoundBuffer->SetVolume(-10000);
	else
		SoundBuffer->SetVolume((long)((log10((float)Volume_) - 2.0f) * 5000.0f));


	if (IsOverlab) {
		for (int i = 1; i < SOUND_BUFFER_MAX; i++) {
			if (Volume_ == 0)
				PlusBuffer[i]->SetVolume(-10000);
			else
				PlusBuffer[i]->SetVolume((long)((log10((float)Volume_) - 2.0f) * 5000.0f));
		}
	}
}




SOUNDMANAGER::SOUNDMANAGER()
{
	Sound = NULL;

	bgm_on = true;
	se_on = true;
	BackgroundVolume = 0.0f;
	VoiceVolume = 0.0f;
	EffectVolume = 0.0f;
}

SOUNDMANAGER :: ~SOUNDMANAGER()
{
	for (auto it = bgmList.begin(); it != bgmList.end(); it++) {
		if (it->second != NULL) {
			delete it->second;
		}
	}
	for (auto it= soundList.begin();it!= soundList.end();it++) {
		if (it->second != NULL) {
			delete it->second;
		}
	}
	if (Sound != NULL)
	{
		Sound->Release();
		Sound = NULL;
	}
}

void SOUNDMANAGER::Initialize(HWND WindowHandle)
{
	DirectSoundCreate8(NULL, &Sound, NULL);

	Sound->SetCooperativeLevel(WindowHandle, DSSCL_PRIORITY);

	addSound("hit", "sound\\se\\hit.wav", false, true); //ok
	addSound("lowhp", "sound\\se\\lowhp.wav", false, true);  //ok
	addSound("gameover", "sound\\se\\gameover.wav", false, true);  //ok
	addSound("pickup", "sound\\se\\pickup.wav", false, true);  //ok
	addSound("levelup", "sound\\se\\levelup.wav", false, true);  //ok

	addSound("damaged", "sound\\se\\damaged.wav", false, true);  //ok
	addSound("evade", "sound\\se\\evade.wav", false, true); //ok
	addSound("block", "sound\\se\\block.wav", false, true); //ok

	addSound("kill_banashed", "sound\\se\\kill_banashed.wav", false, true); //ok
	addSound("kill", "sound\\se\\kill.wav", false, true);//ok
	addSound("kill_named", "sound\\se\\kill_named.wav", false, true); //ok

	addSound("shoot", "sound\\se\\shoot.wav", false, true); //ok

	addSound("potion", "sound\\se\\potion.wav", false, true); //ok
	addSound("scroll", "sound\\se\\scroll.wav", false, true); //ok
	addSound("equip", "sound\\se\\equip.wav", false, true); //ok


	addSound("stair", "sound\\se\\stair.wav", false, true); //ok
	addSound("spellcard", "sound\\se\\spellcard.wav", false, true); //ok
	addSound("god", "sound\\se\\god.wav", false, true); //ok

	addSound("bomb", "sound\\se\\bomb.wav", false, true); //ok
	addSound("fire", "sound\\se\\fire.wav", false, true); //ok
	addSound("cold", "sound\\se\\cold.wav", false, true); //ok
	addSound("elec", "sound\\se\\elec.wav", false, true); //ok
	addSound("stone", "sound\\se\\stone.wav", false, true); //ok
	addSound("wind", "sound\\se\\wind.wav", false, true); //ok
	addSound("summon", "sound\\se\\summon.wav", false, true); //ok
	addSound("blink", "sound\\se\\blink.wav", false, true); //ok


	addSound("buff", "sound\\se\\buff.wav", false, true); //ok
	addSound("soul_shot", "sound\\se\\soul_shot.wav", false, true); //ok
	addSound("sickle", "sound\\se\\sickle.wav", false, true); //ok
	addSound("namaz", "sound\\se\\namaz.wav", false, true); //ok
	addSound("earthquake", "sound\\se\\earthquake.wav", false, true); //ok
	addSound("howl", "sound\\se\\howl.wav", false, true); //ok
	addSound("timestop", "sound\\se\\timestop.wav", false, true); //ok
	addSound("nuke", "sound\\se\\nuke.wav", false, true);  //ok
	addSound("ufo", "sound\\se\\ufo.wav", false, true); //ok
	addSound("spark", "sound\\se\\spark.wav", false, true); //ok
	addSound("laser", "sound\\se\\laser.wav", false, true); //ok
	addSound("shoot_heavy", "sound\\se\\shoot_heavy.wav", false, true); //ok
	addSound("nyan", "sound\\se\\nyan.wav", false, true); //ok
	addSound("smite", "sound\\se\\smite.wav", false, true); //ok
	addSound("laugh", "sound\\se\\laugh.wav", false, true); //ok
	addSound("step", "sound\\se\\step.wav", false, true); //ok
	addSound("powerup", "sound\\se\\powerup.wav", false, true); //ok
	addSound("throw", "sound\\se\\throw.wav", false, true); //ok
	addSound("debuf", "sound\\se\\debuf.wav", false, true); //ok
	addSound("curse", "sound\\se\\curse.wav", false, true); //ok
	addSound("jump", "sound\\se\\jump.wav", false, true); //ok
	addSound("water", "sound\\se\\water.wav", false, true); //ok
	addSound("warning", "sound\\se\\warning.wav", false, true); //ok
	addSound("charge", "sound\\se\\charge.wav", false, true); //ok
	addSound("camera", "sound\\se\\camera.wav", false, true); //ok
	addSound("rune", "sound\\se\\rune.wav", false, true); //ok
	
	

	addBgm("dungeon", "sound\\bgm\\dungeon.wav");
	addBgm("mistlake", "sound\\bgm\\mistlake.wav");
	addBgm("youkaimountain", "sound\\bgm\\youkaimountain.wav");
	addBgm("scarlet", "sound\\bgm\\scarlet.wav");
	addBgm("bamboo", "sound\\bgm\\bamboo.wav");
	addBgm("depth", "sound\\bgm\\depth.wav");
	addBgm("dream", "sound\\bgm\\dream.wav");
	addBgm("pandemonium", "sound\\bgm\\pandemonium.wav");
	addBgm("subterranean", "sound\\bgm\\subterranean.wav");
	addBgm("hakurei", "sound\\bgm\\hakurei.wav");
	addBgm("sprint", "sound\\bgm\\sprint.wav");
	addBgm("ziggurat", "sound\\bgm\\ziggurat.wav");

}

void SOUNDMANAGER::Update()
{
	if (current_bgm != NULL)
	{
		current_bgm->BufferUpdate();
	}
	if (stop_bgm != NULL && stop_bgm != current_bgm)
	{
		stop_bgm->BufferUpdate();
	}
}


void SOUNDMANAGER::addSound(const char* name, char* path, bool Looping, bool overlab) 
{
	SOUNDBUFFER* new_sound = new SOUNDBUFFER();
	new_sound->lazy_loading = true;
	new_sound->Load(Sound, path, false, Looping, overlab);
	new_sound->Volume = option_mg.getSeVolume();
	new_sound->SetVolume();
	soundList[name] = new_sound;
}
void SOUNDMANAGER::addBgm(const char* name, char* path)
{
	SOUNDBUFFER* new_sound = new SOUNDBUFFER();
	new_sound->lazy_loading = false;
	new_sound->path = path;
	//new_sound->Load(Sound, path, true, true, false); 나중에 로딩한다.
	new_sound->Volume = option_mg.getBgmVolume();
	new_sound->SetVolume();
	bgmList[name] = new_sound;
}

void SOUNDMANAGER::playSound(const char* name) 
{
	SOUNDBUFFER* sound_ = soundList[name];

	if (sound_->lazy_loading == false) {
		sound_->lazy_loading = true;
		sound_->Load(Sound, sound_->path.c_str(), false, false, true);
	}

	if (sound_ && soundmanager.se_on)
	{
		sound_->PlaySound();
		sound_->play_time = 0;
	}
}

boolean SOUNDMANAGER::playBgm(const char* name)
{
	SOUNDBUFFER* sound_ = bgmList[name];

	if (current_bgm == sound_)
		return false;

	if (sound_->lazy_loading == false) {
		sound_->lazy_loading = true;
		sound_->Load(Sound, sound_->path.c_str(), true, true, false);
	}
	if (sound_ && sound_->SoundBuffer && soundmanager.bgm_on)
	{
		sound_->PlaySound();
		sound_->play_time = 0;
		current_bgm = sound_;
		return true;
	}
	return false;
}
void SOUNDMANAGER::stopCurrentBGM(const char* except)
{
	if (except != NULL) {
		SOUNDBUFFER* sound_ = bgmList[except];
		if (current_bgm == sound_)
			return;
	}


	if(current_bgm && current_bgm->SoundBuffer && soundmanager.bgm_on)
	{
		current_bgm->StopSound();
		stop_bgm = current_bgm;
	}
}
void InitSound(HWND windowhandle_)
{
	soundmanager.Initialize(windowhandle_);
}

void PlaySE(const char* name)
{
	soundmanager.playSound(name);
}
boolean PlayBGM(const char* name)
{
	return soundmanager.playBgm(name);
}
void StopBGM(SOUNDBUFFER* sound_)
{
	if (sound_ && sound_->SoundBuffer && soundmanager.bgm_on)
	{
		sound_->StopSound();
	}
}
void VolumeUp()
{
	for (auto it = soundmanager.bgmList.begin(); it != soundmanager.bgmList.end(); it++) {
		it->second->quite = false;
		//it->second->Volume += 10;
		it->second->SetVolume();
	}
	for (auto it = soundmanager.soundList.begin(); it != soundmanager.soundList.end(); it++) {
		it->second->quite = false;
		//it->second->Volume += 10;
		it->second->SetVolume();
	}
}
void VolumeDown()
{
	for (auto it = soundmanager.bgmList.begin(); it != soundmanager.bgmList.end(); it++) {
		it->second->quite = true;
		//it->second->Volume -= 10;
		it->second->SetVolume();
	}
	for (auto it = soundmanager.soundList.begin(); it != soundmanager.soundList.end(); it++) {
		it->second->quite = true;
		//it->second->Volume -= 10;
		it->second->SetVolume();
	}
}
void StopCurrentBGM(const char* except)
{
	soundmanager.stopCurrentBGM(except);
}
void UpdateBGM()
{
	soundmanager.Update();
}