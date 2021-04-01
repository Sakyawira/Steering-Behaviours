/***********************
  File Name   :   Audio.h
  Description :   Class declaration of audio system using the FMOD library
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
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
	void StopAll();
	void Update();

private:
	FMOD::System*		audioSystem;			// Handle to FMOD engine
	FMOD::Sound*		sounds[NUM_SOUNDS];		// Sound that will be loaded and played
	FMOD::Channel*		bgmChannel;
	FMOD::Channel*		ambientChannel;
	FMOD::Channel*		sfxChannel;
};