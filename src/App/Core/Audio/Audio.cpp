#include "Audio.h"
#include "dtl.h" // for printing errors
// #include <thread> // playing audio is gonna be on another thread
#include <string> // std::string


// Init engine and check if everything went ok
void initSoundEngine(ma_engine* engine, float volume) {
    ma_result result;
    result = ma_engine_init(NULL, engine);

    // Failed to initialize the engine
    if (result != MA_SUCCESS)
        DTL_ERR("Failed to initialize the engine!");

    ma_engine_set_volume(engine, volume);
}

// Init and load sound and check if everything went ok
void loadSound(ma_sound* sound, std::string soundFilePath, ma_engine* engine, float volume) {
    ma_result result;
    result = ma_sound_init_from_file(engine, soundFilePath.c_str(), 0, NULL, NULL, sound);
    if (result != MA_SUCCESS)
        DTL_ERR("Failed to initialize the sound!");

    ma_sound_set_volume(sound, volume);
}

void playSound(ma_sound* sound) {
    ma_sound_start(sound);
    while (true); // XD
}

void playSoundInLoop(ma_sound* sound) {
    ma_sound_set_looping(sound, true);
    ma_sound_start(sound);
    /* cały dźwięk będzie na osobnym wątku ale nie wiem jeszcze
       jak rozwiązać problem ze zmianą głośności w czasie trwania programu
       być może przy byciu w ustawieniach wątek będzie zatrzymywany
       a następnie wznawiany przy wyjściu z ustawień,
       już z odpowiednimi ustawieniami
    */
    while (true); // XD
}

// Maybe will check if everything went ok
void uninitSoundEngine(ma_engine* engine) {
    ma_engine_uninit(engine);
}

// Uninit all sounds previously loaded
void uninitSounds(ma_sound sounds[], const int soundCount) {
    for (int i = 0; i < soundCount; i++)
        ma_sound_uninit(&sounds[i]);
}
