#pragma once
#include"Agl.h"

namespace golf {

	class Sus {

	public:
		void LoadAll();
		//zastanowic siê jak wgrywaæ tekstury inaczej (aka. zatrzymuje okienko)
		void LoadListOfTextures(std::initializer_list<std::string> files);
		void LoadTexture(const std::string& file, int filter = GL_LINEAR, int sWrap = GL_REPEAT, int tWrap = GL_REPEAT);

		void LoadAllTextures();


		agl::Texture* GetTexture(const std::string& file); 
		

		void RemoveListOfTextures(std::initializer_list<std::string> files);
		void RemoveTexture(const std::string& file);


		//TODO:
		//£adowanie Shaderów (glfw image (?))

		//===========
		void LoadAllAudio();

		//===========
	private:
		std::map<std::string, agl::Texture> m_Textures;
		std::vector<std::string> CurrentSceneTextures;
		std::vector<std::string> NextSceneTextures;

	};

}