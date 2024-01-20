#include "Audio.h"
#include "dtl.h" // for printing errors
// #include <thread> // playing audio is gonna be on another thread
#include <string> // std::string

// Init engine and check if everything went ok
void initSoundEngine(ma_engine* engine) {
    ma_result result;
    result = ma_engine_init(NULL, engine);

    // Failed to initialize the engine
    if (result != MA_SUCCESS)
        DTL_ERR("Failed to initialize the engine!");

    ma_engine_set_volume(engine, .06f);
}

// Maybe will check if everything went ok
void uninitSoundEngine(ma_engine* engine) {
    ma_engine_uninit(engine);
}

// Maybe will check if everything went ok
void uninitSounds(ma_sound sounds[], const int soundCount) {
    for (int i = 0; i < soundCount; i++)
        ma_sound_uninit(&sounds[i]);
}


// Init and load sound and check if everything went ok
void loadSound(ma_sound* sound, std::string soundFilePath, ma_engine* engine) {
    ma_result result;
    result = ma_sound_init_from_file(engine, soundFilePath.c_str(), 0, NULL, NULL, sound);
    if (result != MA_SUCCESS)
        DTL_ERR("Failed to initialize the sound!");
}

// Here will be playSound function that *play some sound*
void playSound(ma_sound* sound) {
    ma_sound_start(sound);
}

// TODO
void playInLoop() {   
    /* cały dźwięk będzie na osobnym wątku ale nie wiem jeszcze 
       jak rozwiązać problem ze zmianą głośności w czasie trwania programu
       być może po przy byciu w ustawieniach wątek będzie zatrzymywany
       a następnie wznawiany przy wyjściu z ustawień,
       już z odpowiednimi ustawieniami
    */ 
    // std::thread SoundThread(playSound, &sound);
    
    // jak testowałem odpalanie dźwięku to bez getchara od razu się kończy
    // gdzie w dokumentacji nie jest to w żaden sposob rozwiniete
    // a w podanych przykladach autor wykorzystuje getchara
    getchar();
}