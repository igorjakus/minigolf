#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"


// Init engine and check if everything went ok
void initSoundEngine(ma_engine* engine, float volume);

// Init and load sound and check if everything went ok
void loadSound(ma_sound* sound, std::string soundFilePath, ma_engine* engine, float volume);

// Play sound once
void playSound(ma_sound* sound);

// Play sound forever
void playSoundInLoop(ma_sound* sound);

// Maybe will check if everything went ok
void uninitSoundEngine(ma_engine* engine);

// Uninit all sounds previously loaded
void uninitSounds(ma_sound sounds[], const int soundCount);
