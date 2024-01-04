#pragma once

#include "Agl.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <initializer_list>
#include<dtl.h>
#include <filesystem>

namespace golf {

	class Sus {

	public:
		void LoadAll();


		void LoadListOfTextures(std::initializer_list<std::string> files);

		void LoadTexture(const std::string& file, int filter = GL_NEAREST, int sWrap = GL_REPEAT, int tWrap = GL_REPEAT);







		void LoadAllTextures();


		agl::Texture* GetTexture(const std::string& file); 
		//const na pocz¹tku upewnia siê ¿e nie zmienisz orgina³u, na koñcu: mówi ze nie zmienisz nic w klasie
		//& przekazuje ca³y obiekt; musisz sie upewniac ze nie zmienisz
		void RemoveTexture(const std::string& file);


		

		//===========
		void LoadAllAudio();






		//===========
	private:
		std::map<std::string, agl::Texture> m_Textures;

		std::vector < std::string > CurrentSceneTextures;
		std::vector < std::string > NextSceneTextures;

	};

}