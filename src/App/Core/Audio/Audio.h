#pragma once

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <vector>
#include <thread> // playing audio is gonna be on another thread

namespace golf {

	class Audio {
	public:
		Audio();
		~Audio();

		// Init engine and check if everything went ok
		void initSoundEngine(ma_engine* engine, float volume);

		// Init and load sound and check if everything went ok
		void loadSound(ma_sound* sound, std::string soundFilePath, ma_engine* engine);

		// Play sound once
		void playSound(int number);

		// Play sound forever
		void playSoundInLoop(int number);

		void playMusic();

		ma_sound* getSound(int number);

	private:
		bool isMusicPlaying;

		ma_engine musicEngine;
		ma_engine soundEventEngine;

		std::vector<std::shared_ptr<ma_sound>> music;
		std::vector<std::shared_ptr<ma_sound>> sounds;
	};
}
