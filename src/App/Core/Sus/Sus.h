#pragma once
#include"Agl.h"

namespace golf {

	class Sus {

	public:
		void LoadAll();

		//=====[Textures]=====
		void LoadListOfTextures(std::initializer_list<std::string> files, int scaleX = 1, int scaleY = 1);

		void LoadTexture(const std::string& file, glm::ivec2 textureRatio = { 1, 1 }, int filter = GL_LINEAR, int sWrap = GL_REPEAT, int tWrap = GL_REPEAT);

		void LoadAllTextures();

		agl::Texture* GetTexture(const std::string& file); 

		void RemoveListOfTextures(std::initializer_list<std::string> files);
		void RemoveTexture(const std::string& file);

		//=====[Shaders]=====
		void LoadShader(const std::string& file);

		agl::Shader* GetShader(const std::string& file);

		agl::Shader* LoadAndGetShader(const std::string& file);

		void LoadAllShaders();
		
		//=====[Animation]=====

		void LoadAnimation(const std::string& file, int filter, uint frames, float frametime, uint width, uint heigth);

		agl::Animation GetAnimation(const std::string& file);



		//=====[Level Data File]=====
		void LoadLevelFile(int log=false);

		bool IsUnlocked(int nr);
		int HighScore(int nr);

		void ChangeHighScore(int nr, int score);
		void Unlock(int nr);

		void UpdateSaveFile();
		//TO DO: zapis zmieniony przy koñcu programu

		//=====[Audio (Igor :3)]
		void LoadAllAudio();


		//===========
	private:
		std::map<std::string, agl::Texture> m_Textures;

		std::map<std::string, agl::Shader> m_Shaders;

		std::map<std::string, agl::Animation> m_Animations;

		std::map<int, std::pair<int,bool>> m_Levels;

	};

}
