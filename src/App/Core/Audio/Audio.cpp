#include "Audio.h"
#include "dtl.h"
#define SOUNDTRACK_PATH "assets/audio/soundtrack/"
#define SOUNDEFFECTS_PATH "assets/audio/effects/"
#define MUSIC_VOLUME 0.25f
#define SOUND_EFFECTS_VOLUME 0.75f

namespace golf {
    Audio::Audio() {
        // init music engine
        if (ma_engine_init(nullptr, &musicEngine) == MA_SUCCESS) {
            ma_engine_set_volume(&musicEngine, MUSIC_VOLUME);
            DTL_INF("AUDIO: Music engine initalized successfully");
        }
        else { DTL_ERR("AUDIO: Failed to initialize music engine!"); }

        // init sound effects engine
        if (ma_engine_init(nullptr, &soundEffectsEngine) == MA_SUCCESS) {
            ma_engine_set_volume(&soundEffectsEngine, SOUND_EFFECTS_VOLUME);
            DTL_INF("AUDIO: Sound effects engine initalized successfully");
        }
        else { DTL_ERR("AUDIO: Failed to initialize sound effects engine!"); }
        
        // load soundtrack
        for (const auto& entry : std::filesystem::directory_iterator(SOUNDTRACK_PATH)) {
            if (std::filesystem::is_regular_file(entry)) {
                music.emplace_back(std::make_shared<ma_sound>());
                loadSound(music.back().get(), entry.path().string(), &musicEngine);
                DTL_INF("AUDIO: Loaded soundtrack file {0}", entry.path().filename());
            }
        }

        // load sound effects
        for (const auto& entry : std::filesystem::directory_iterator(SOUNDEFFECTS_PATH)) {
            if (std::filesystem::is_regular_file(entry)) {
                soundEffects.emplace_back(std::make_shared<ma_sound>());
                loadSound(soundEffects.back().get(), entry.path().string(), &soundEffectsEngine);
                DTL_INF("AUDIO: Loaded sound effects {0}", entry.path().filename());
                soundsMap[entry.path().stem().string()] = static_cast<int>(soundEffects.size() - 1);
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
        for (auto s : soundEffects)
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
        result = ma_sound_init_from_file(engine, soundFilePath.c_str(), 0, nullptr, nullptr, sound);
        if (result != MA_SUCCESS)
            DTL_ERR("AUDIO: Failed to initialize the sound! Path: " + soundFilePath);            
    }

    void Audio::playSound(int number) {
        /* to może nie być bezpieczne, być może trzeba będzie przechowywać czy mamy jeszcze jakieś wątki otwarte
        i dopiero jak się skończą to wtedy uninitować dźwięki i engine*/
        ma_sound_start(soundEffects[static_cast<std::vector<std::shared_ptr<ma_sound> >::size_type>(number)].get());
    }

    void Audio::playSound(std::string songName) { playSound(soundsMap[songName]); }

    void Audio::playMusic() {
        size_t songCount = music.size();
        int songToPlay = 0;
        const int playNTimes = 2;
        int timesPlayedInRow = 1;
        bool isSongPlaying = true;

        while (!exitMusic) {
            isSongPlaying = ma_sound_is_playing(getSong(songToPlay));

            // paused but playing
            if (isMusicPaused && isSongPlaying)
                ma_sound_stop(getSong(songToPlay));

            // not paused and not playing
            else if (!isMusicPaused && !isSongPlaying) {
                if (timesPlayedInRow == playNTimes) {
                    songToPlay = (songToPlay + 1) % static_cast<int>(songCount);
                    timesPlayedInRow = 0;
                }
                timesPlayedInRow++;
                ma_sound_start(getSong(songToPlay));
            }

            // paused but not playing: good
            // not paused but playing: good
        }
        ma_sound_stop(getSong(songToPlay));
    }

    void Audio::pauseMusicON() { isMusicPaused = true; }
    void Audio::pauseMusicOFF() { isMusicPaused = false; }
    void Audio::pauseMusicSWITCH() { isMusicPaused = !isMusicPaused; }

    ma_sound* Audio::getSong(int number) {
        return music[static_cast<std::vector<std::shared_ptr<ma_sound> >::size_type>(number)].get();
    }
}
