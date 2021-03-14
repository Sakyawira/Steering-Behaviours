#pragma once

#include "fmod.hpp" //fmod c++ header

//Sound array size
#define NUM_SOUNDS 15

//Sound identifiers
#define	SOUND_BGM1			0
#define	SOUND_BGM2			1

class Audio
{
public:
	Audio(void);
	virtual ~Audio(void);

	bool Load();
	void Play(int sound_id);
	void Stop(/*int sound_id*/);
	void SmoothStop(int sound_id);
	void StopAll();
	void Update();

	FMOD::System*		audioSystem;			//handle to FMOD engine
	FMOD::Sound*		sounds[NUM_SOUNDS];		//sound that will be loaded and played
	FMOD::Channel*		ambient1Channel;
	FMOD::Channel*		ambient2Channel;
	FMOD::Channel*		sfxChannel;
	FMOD::DSP*			dspSmoothStop;

	FMOD::Sound*		fxThump;
	FMOD::Sound*		trackBackground;
	FMOD_RESULT			result;
};