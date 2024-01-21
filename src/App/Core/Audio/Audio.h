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

		ma_sound* getSound(int number);

		// later can make a function that changes them
		bool exitMusic;
		bool pauseMusic;

	private:
		ma_engine musicEngine;
		ma_engine soundEventEngine;

		std::vector<std::shared_ptr<ma_sound>> music;
		std::vector<std::shared_ptr<ma_sound>> sounds;

		// only constructor should call it
		// you can stop it by changing exitMusic to true
		void playMusic();
	};
}
