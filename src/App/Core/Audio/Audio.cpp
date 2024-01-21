#include "Audio.h"
#include "dtl.h" // for printing errors
#include <string> // std::string


namespace golf {
    Audio::Audio() {
        const float MUSIC_ENGINE_VOLUME = 0.5, SOUND_EVENT_ENGINE_VOLUME = 0.75;

        // init sound engines
        initSoundEngine(&musicEngine, MUSIC_ENGINE_VOLUME);
        initSoundEngine(&soundEventEngine, SOUND_EVENT_ENGINE_VOLUME);
        
        // load background music files
        std::vector<std::string> musicFiles{ "breakbeat", "house-progresywny", "neon", "ognisko", "spacer_nad_rzeka", "tajny_agent", "zawrot-glowy"};
        for (auto &musicFile: musicFiles) {
            music.emplace_back(std::make_shared<ma_sound>());
            std::string filePath = "assets/audio/" + musicFile + ".mp3";
            loadSound(music.back().get(), filePath, &musicEngine);
        }

        // load sound effects files
        std::vector<std::string> soundFiles{}; // empty for now
        for (auto &soundFile : soundFiles) {
            sounds.emplace_back();
            std::string filePath = "assets/audio/" + soundFile + ".mp3";
            loadSound(sounds.back().get(), filePath, &soundEventEngine);
        }

        // set appropriate bool values
        exitMusic = false;
        pauseMusic = false;

        // ATTENTION!!!
        // ZAPEWNE SIE WYKRZACZY POTEM TO
        std::thread musicThread([&]() { playMusic(); });
        musicThread.detach();
    }

    Audio::~Audio() {
        // indirectly should close playMusic thread
        exitMusic = true;

        // uninit engines
        ma_engine_uninit(&musicEngine);
        ma_engine_uninit(&soundEventEngine);

        // uninit sound objects
        for (auto m: music)
            ma_sound_uninit(m.get());
        for (auto s : sounds)
            ma_sound_uninit(s.get());

        // console info
        DTL_INF("Audio engine and sounds objects terminated successfully");
    }

    // Init engine and check if everything went ok
    void Audio::initSoundEngine(ma_engine* engine, float volume) {
        ma_result result;
        result = ma_engine_init(NULL, engine);

        // Failed to initialize the engine
        if (result != MA_SUCCESS)
            DTL_ERR("Failed to initialize the engine!");

        ma_engine_set_volume(engine, volume);
    }

    // Init and load sound and check if everything went ok
    void Audio::loadSound(ma_sound* sound, std::string soundFilePath, ma_engine* engine) {
        ma_result result;
        result = ma_sound_init_from_file(engine, soundFilePath.c_str(), 0, NULL, NULL, sound);
        if (result != MA_SUCCESS)
            DTL_ERR("Failed to initialize the sound! Path: " + soundFilePath);
        // ma_sound_set_volume(sound, volume); MOŻEMY TO ZMIENIĆ GDYBY PEWNE DŹWIĘKI BYŁY ROZJECHANE W GŁOŚNOŚCI
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
            if (pauseMusic && isSongPlaying)
                ma_sound_stop(getSound(songToPlay));

            // not paused and not playing
            else if (!pauseMusic && !isSongPlaying) {
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

    ma_sound* Audio::getSound(int number) {
        return music[number].get();
    }
}
