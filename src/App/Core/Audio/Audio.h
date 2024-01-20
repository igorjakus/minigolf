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
		void playSound(ma_sound* sound);

		// Play sound forever
		void playSoundInLoop(ma_sound* sound);


		//SUS:

		ma_sound* GetSound(int nr);
		void playSound2(std::shared_ptr<ma_sound> sound);

	private:
		ma_engine musicEngine;
		ma_engine soundEventEngine;

		std::vector<std::shared_ptr<ma_sound>> music;
		std::vector<std::shared_ptr<ma_sound>> sounds;
	};
}
