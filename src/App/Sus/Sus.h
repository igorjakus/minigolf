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
		//const na pocz¹tku upewnia siê ¿e nie zmienisz orgina³u, na koñcu: mówi ze nie zmienisz nic w klasie
		//& przekazuje ca³y obiekt; musisz sie upewniac ze nie zmienisz



		void LoadAllTextures();

		//===========
		void LoadAllAudio();






		//===========
	private:
		std::map<std::string, agl::Texture> m_Textures;

	};

}