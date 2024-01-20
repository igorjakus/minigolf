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

        // ZAPEWNE SIE WYKRZACZY POTEM TO
        std::thread musicThread([&]() {
            playMusic();
            });
        // UWAGA UWAGA
        musicThread.detach();
    }

    Audio::~Audio() {
        // uninit engines
        ma_engine_uninit(&musicEngine);
        ma_engine_uninit(&soundEventEngine);

        // uninit sound objects
        for (auto m: music)
            ma_sound_uninit(m.get());
        for (auto s : sounds)
            ma_sound_uninit(s.get());

        // pewnie trzeba isMusicPlaying dac na false ale jakimis lockami pilnowac zeby sie nie wykrzaczylo
        
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
        ma_sound_start(music[number].get());
        while (true); // XD
    }

    void Audio::playSoundInLoop(int number) {
        ma_sound_set_looping(music[number].get(), true);
        ma_sound_start(music[number].get());
        while (true); // XD
        /* cały dźwięk będzie na osobnym wątku ale nie wiem jeszcze
            jak rozwiązać problem ze zmianą głośności w czasie trwania programu
            być może przy byciu w ustawieniach wątek będzie zatrzymywany
            a następnie wznawiany przy wyjściu z ustawień,
            już z odpowiednimi ustawieniami
        */
    }

    void Audio::playMusic() {
        int nr = 1;
        while (isMusicPlaying) {
            if((!ma_sound_is_playing(getSound(nr))))
                ma_sound_start(getSound(nr));
        }
    }

    ma_sound* Audio::getSound(int number) {
        return music[number].get();
    }
}
