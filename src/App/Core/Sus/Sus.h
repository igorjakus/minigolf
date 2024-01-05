#pragma once

#include "Agl.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <initializer_list>
#include <dtl.h>
#include <filesystem>

namespace golf {

	class Sus {

	public:
		void LoadAll();

		//=====[Textures]=====
		void LoadListOfTextures(std::initializer_list<std::string> files);
		void LoadTexture(const std::string& file, int filter = GL_NEAREST, int sWrap = GL_REPEAT, int tWrap = GL_REPEAT);
		void LoadAllTextures();

		agl::Texture* GetTexture(const std::string& file); 

		void RemoveListOfTextures(std::initializer_list<std::string> files);
		void RemoveTexture(const std::string& file);

		//=====[Shaders]=====
		void LoadShader(const std::string& file);

		agl::Shader* GetShader(const std::string& file);

		agl::Shader* LoadAndGetShader(const std::string& file);
		//===========
		void LoadAllAudio();
		//===========
	private:
		std::map<std::string, agl::Texture> m_Textures;

		std::map<std::string, agl::Shader> m_Shaders;

		std::vector < std::string > CurrentSceneTextures;
		std::vector < std::string > NextSceneTextures;

	};

}