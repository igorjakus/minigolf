#include "Audio.h"
#include "dtl.h" // for printing errors
#include <string> // std::string
#include <thread> // std::vector
#include <filesystem> // std::filesystem
#define SOUNDTRACK_PATH "assets/audio/soundtrack/"
#define SOUNDEFFECTS_PATH "assets/audio/effects/"


namespace golf {
    Audio::Audio() {
        const float MUSIC_VOLUME = 0.5, SOUND_EFFECTS_VOLUME = 0.75;

        // init music engine
        if (ma_engine_init(NULL, &musicEngine) == MA_SUCCESS) {
            ma_engine_set_volume(&musicEngine, MUSIC_VOLUME);
            DTL_INF("Audio: Music engine initalized successfully");
        }
        else DTL_ERR("Audio: Failed to initialize music engine!");

        // init sound effects engine
        if (ma_engine_init(NULL, &soundEffectsEngine) == MA_SUCCESS) {
            ma_engine_set_volume(&soundEffectsEngine, SOUND_EFFECTS_VOLUME);
            DTL_INF("Audio: Sound effects engine initalized successfully");
        }
        else DTL_ERR("Audio: Failed to initialize sound effects engine!");
        
        // load soundtrack
        for (const auto& entry : std::filesystem::directory_iterator(SOUNDTRACK_PATH)) {
            if (std::filesystem::is_regular_file(entry)) {
                music.emplace_back(std::make_shared<ma_sound>());
                loadSound(music.back().get(), entry.path().string(), &musicEngine);
                DTL_INF("Audio: Loaded soundtrack file {0}", entry.path().filename());
            }
        }

        // load sound effects
        for (const auto& entry : std::filesystem::directory_iterator(SOUNDEFFECTS_PATH)) {
            if (std::filesystem::is_regular_file(entry)) {
                sounds.emplace_back(std::make_shared<ma_sound>());
                loadSound(sounds.back().get(), entry.path().string(), &soundEffectsEngine);
                DTL_INF("Audio: Loaded sound effects {0}", entry.path().filename());
            }
        }

        // play music on a different thead
        std::thread musicThread([&]() { playMusic(); });
        musicThread.detach(); // ZAPEWNE SIE WYKRZACZY POTEM TO
    }

    Audio::~Audio() {
        // close playMusic thread
        exitMusic = true; 

        // uninit sound effect engine and sound objects
        ma_engine_uninit(&soundEffectsEngine);
        for (auto s : sounds)
            ma_sound_uninit(s.get());

        // uninit music engine and sound objects
        ma_engine_uninit(&musicEngine);
        for (auto m: music)
            ma_sound_uninit(m.get());
        
        // console info
        DTL_INF("Audio engine and sounds objects terminated successfully");
    }

    // Init and load sound and check if everything went ok
    void Audio::loadSound(ma_sound* sound, std::string soundFilePath, ma_engine* engine) {
        ma_result result;
        result = ma_sound_init_from_file(engine, soundFilePath.c_str(), 0, NULL, NULL, sound);
        if (result != MA_SUCCESS)
            DTL_ERR("Failed to initialize the sound! Path: " + soundFilePath);            
    }

    void Audio::playSound(int number) {
        // to nie jest bezpieczne raczej
        // może trzeba gdzieś przechowywać, że mamy jeszcze jakieś wątki i zanim zamkniemy poczekać aż się skończą
        // i wtedy uninitować dźwięki i engine
        std::thread tmp(ma_sound_start, music[number].get());
        tmp.detach();  
    }

    void Audio::playMusic() {
        size_t songCount = music.size();
        int songToPlay = 0;
        const int playNTimes = 2;
        int timesPlayedInRow = 1;
        bool isSongPlaying = true;

        while (!exitMusic) {
            isSongPlaying = ma_sound_is_playing(getSound(songToPlay));

            // paused but playing
            if (isMusicPaused && isSongPlaying)
                ma_sound_stop(getSound(songToPlay));

            // not paused and not playing
            else if (!isMusicPaused && !isSongPlaying) {
                if (timesPlayedInRow == playNTimes) {
                    songToPlay = (songToPlay + 1) % songCount;
                    timesPlayedInRow = 0;
                }
                timesPlayedInRow++;
                ma_sound_start(getSound(songToPlay));
            }

            // paused but not playing: good
            // not paused but playing: good
        }
        ma_sound_stop(getSound(songToPlay));
    }

    void Audio::pauseMusicON() { isMusicPaused = true; }
    void Audio::pauseMusicOFF() { isMusicPaused = false; }
    void Audio::pauseMusicSWITCH() { isMusicPaused = !isMusicPaused; }

    ma_sound* Audio::getSound(int number) {
        return music[number].get();
    }
}
