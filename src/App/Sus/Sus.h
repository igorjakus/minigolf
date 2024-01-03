#pragma once

#include "Agl.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

namespace golf {

	class Sus {

	public:
		void LoadAll();



		void LoadTexture(const std::string& file); //loadtexture jeszcze dla ziemi
		agl::Texture* GetTexture(const std::string& file); 
		//const na pocz�tku upewnia si� �e nie zmienisz orgina�u, na ko�cu: m�wi ze nie zmienisz nic w klasie
		//& przekazuje ca�y obiekt; musisz sie upewniac ze nie zmienisz



		void LoadAllTextures();

		//===========
		void LoadAllAudio();






		//===========
	private:
		std::map<std::string, agl::Texture> m_Textures;

	};

}