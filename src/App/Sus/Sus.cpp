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

		m_Textures.emplace(std::piecewise_construct,std::forward_as_tuple(file),std::forward_as_tuple("assets/textures/" + file, GL_NEAREST, GL_REPEAT, GL_REPEAT));
		//czemu siê tekstura od razu usuwa???
		
	}

	//std::make_pair<std::string, agl::Texture>(file, { "assets/textures/" + file, GL_NEAREST, GL_REPEAT, GL_REPEAT })


	agl::Texture* Sus::GetTexture(const std::string& file){

		auto item = m_Textures.find(file);
		return &item->second;
		//return &m_Textures[file];
		
	}

	

	void Sus::LoadAllTextures() {
		//zbieranie po kolei z pliku, na razie tylko case 2 tekstur:

		LoadTexture("sponge.png"); //jak jest Sus:: to nie trzeba tu te¿ Sus::
		LoadTexture("white.png");

	}

	void Sus::LoadAllAudio() {

	}



}