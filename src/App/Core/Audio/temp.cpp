#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

#include <thread>
#include <iostream>
#include <string>


// Init engine and check if everything went ok
void init_engine(ma_engine* engine) {
    ma_result result;
    result = ma_engine_init(NULL, engine);

    // Failed to initialize the engine
    if (result != MA_SUCCESS)
        std::cerr << "Failed to initialize the engine!"; // DTL log not ok
    // DTL log ok
}

// Init and load sound and check if everything went ok
void load_sound(ma_sound* sound, std::string soundFilePath, ma_engine* engine) {
    ma_result result;
    result = ma_sound_init_from_file(engine, soundFilePath.c_str(), 0, NULL, NULL, sound);
    if (result != MA_SUCCESS)
        std::cerr << "Failed to initialize the sound!"; // DTL log not ok
    // DTL log ok
}

// Here will be playSound function that *play some sound*
void playSound(ma_engine* engine, std::string soundFilePath) {
    return;
}

// fun
void temp()
{
    ma_engine engine;
    init_engine(&engine);
    
    ma_sound neon;
    std::string soundFilePath = "assets/audio/neon.wav";
    load_sound(&neon, soundFilePath, &engine);

    /* cały dźwięk będzie na osobnym wątku ale nie wiem jeszcze 
       jak rozwiązać problem ze zmianą głośności w czasie trwania programu
       być może po przy byciu w ustawieniach wątek będzie zatrzymywany
       a następnie wznawiany przy wyjściu z ustawień,
       już z odpowiednimi ustawieniami
    */ 
    std::thread SoundThread(playSound, &engine, soundFilePath);
    
    // jak testowałem odpalanie dźwięku to bez getchara od razu się kończy
    // gdzie w dokumentacji nie jest to w żaden sposob rozwiniete
    // a w podanych przykladach autor wykorzystuje getchara
    getchar();
}