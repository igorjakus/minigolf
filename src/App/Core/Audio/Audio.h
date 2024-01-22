#pragma once

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "pch.h"

namespace golf {

	class Audio {
	public:
		Audio();
		~Audio();

		// Play sound once
		void playSound(int number);			  // index in soundEffects
		void playSound(std::string songName); // file name without ext

		// Pause ON/OFF
		void pauseMusicON();
		void pauseMusicOFF();
		void pauseMusicSWITCH();

		// Changing volume by increment set in Audio.cpp macro
		void increaseMusicVolume();
		void decreaseMusicVolume();
		void increaseSoundEffectsVolume();
		void decreaseSoundEffectsVolume();

	private:
		ma_engine musicEngine;
		ma_engine soundEffectsEngine;

		std::vector<std::shared_ptr<ma_sound>> music;
		std::vector<std::shared_ptr<ma_sound>> soundEffects;

		// create map that for every name holds index of sound effect in vector
		std::map<std::string, int> soundsMap;

		bool isMusicThreadActive = true; // for thread safety
		bool isMusicPaused = false; // change it via pauseMusicON/OFF/SWITCH
		bool exitMusic = false; // only destructor change it, stops playMusic thread

		float musicVolume = 0.15f;
		float soundEffectsVolume = 0.5f;

		// Runs on a different thread, plays music
		void playMusic();

		// Init and load sound and check if everything went ok
		void loadSound(ma_sound* sound, std::string soundFilePath, ma_engine* engine);

		// Give ptr to song of particular index
		ma_sound* getSong(int number);
	};
}
