#pragma once

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <vector>

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

		// Pause ON/OFF
		void pauseMusicON();
		void pauseMusicOFF();
		void pauseMusicSWITCH();

		ma_sound* getSound(int number);

	private:
		ma_engine musicEngine;
		ma_engine soundEventEngine;

		std::vector<std::shared_ptr<ma_sound>> music;
		std::vector<std::shared_ptr<ma_sound>> sounds;

		bool isMusicPaused = false; // change it via pauseMusicON/OFF/SWITCH
		bool exitMusic = false; // only destructor change it, stops playMusic thread

		void playMusic(); // runs on different thread
	};
}
