#include "Audio.h"

/***********************
 Description :   Loads main scene and activates loading screen
********************/
Audio::Audio(void)
{
	FMOD::System_Create(&audioSystem);// create an instance of the game engine
	audioSystem->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels (cantidad de sonido simultaneo que puede haber)
}

/***********************
 Description :   Loads main scene and activates loading screen
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
 Description :   Loads main scene and activates loading screen
********************/
bool Audio::Load()
{
	audioSystem->createStream("Resources/Audio/Chase LOOP.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_BGM1]);
	audioSystem->createStream("Resources/Audio/Fire/FIRE_Campfire_Calm_Smooth_01_loop_mono.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_BGM2]);
	return true;
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Audio::Play(int sound_id)
{
	if (sound_id == SOUND_BGM1)
	{
		audioSystem->playSound(sounds[SOUND_BGM1], 0, false, &ambient1Channel);
		ambient1Channel->setVolume(0.25f); //between 0 and 1
	}
	else if (sound_id == SOUND_BGM2) 
	{
		audioSystem->playSound(sounds[SOUND_BGM2], 0, false, &ambient2Channel);
		ambient2Channel->setVolume(0.2f); //between 0 and 1
	}
	else
	{
		audioSystem->playSound(sounds[sound_id], 0, false, &sfxChannel);
		sfxChannel->setVolume(0.1f);
	}
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Audio::Stop(/*int sound_id*/)
{
	//sfxChannel->stop();
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Audio::StopAll()
{
	ambient1Channel->stop();
	ambient2Channel->stop();
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Audio::Update()
{
	audioSystem->update();
}