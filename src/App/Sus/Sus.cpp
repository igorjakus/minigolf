#include "Sus.h"

#include "Agl.h"
#include <iostream>
#include <fstream>
#include "../App/AppData.h"

namespace golf {


	void Sus::LoadAll() {
	
		LoadAllTextures();
		LoadAllAudio();

	}


	void Sus::LoadTexture(const std::string& file) {

		m_Textures.insert({file,agl::Texture("assets/textures/" + file, GL_NEAREST, GL_REPEAT, GL_REPEAT)});

	}


	const agl::Texture* Sus::GetTexture(const std::string& file) const {

		auto item = m_Textures.find(file);
		if (item != m_Textures.end()) {
			return &item->second;
		}
		
		
	}

	void Sus::LoadAllTextures() {
		//zbieranie po kolei z pliku, na razie tylko case 2 tekstur:

		LoadTexture("sponge.png"); //jak jest Sus:: to nie trzeba tu te¿ Sus::
		LoadTexture("white.png");

	}

	void Sus::LoadAllAudio() {

	}



}