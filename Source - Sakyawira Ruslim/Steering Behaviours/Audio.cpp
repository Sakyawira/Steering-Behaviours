#include "Audio.h"

/***********************
 Description :   Initialise the audio engine and channels
********************/
Audio::Audio(void)
{
	// create an instance of the audio engine
	FMOD::System_Create(&audioSystem); 
	// initialise the audio engine with 32 channels
	audioSystem->init(32, FMOD_INIT_NORMAL, 0); 
}

/***********************
 Description :   Unallocate memories used by FMOD
********************/
Audio::~Audio(void)
{
	for (int i = 0; i < NUM_SOUNDS; i++)
	{
		sounds[i]->release();
	}
	audioSystem->release();
}

/***********************
 Description :   Load .wav that will be used throughout the game
********************/
bool Audio::Load()
{
	audioSystem->createStream("Resources/Audio/Chase LOOP.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_BGM1]);
	audioSystem->createStream("Resources/Audio/Fire/FIRE_Campfire_Calm_Smooth_01_loop_mono.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_BGM2]);
	return true;
}

/***********************
 Description :  Start  playing passed in sounds
********************/
void Audio::Play(int sound_id)
{
	if (sound_id == SOUND_BGM1)
	{
		audioSystem->playSound(sounds[SOUND_BGM1], 0, false, &bgmChannel);
		bgmChannel->setVolume(0.25f); //between 0 and 1
	}
	else if (sound_id == SOUND_BGM2) 
	{
		audioSystem->playSound(sounds[SOUND_BGM2], 0, false, &ambientChannel);
		ambientChannel->setVolume(0.2f); //between 0 and 1
	}
	else
	{
		audioSystem->playSound(sounds[sound_id], 0, false, &sfxChannel);
		sfxChannel->setVolume(0.1f);
	}
}

/***********************
 Description :   Stop all existing channel
********************/
void Audio::StopAll()
{
	bgmChannel->stop();
	ambientChannel->stop();
}

/***********************
 Description :   Process the audio engine
********************/
void Audio::Update()
{
	audioSystem->update();
}