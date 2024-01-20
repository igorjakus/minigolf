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

		void LoadAnimation(const std::string& file, int filter= GL_LINEAR, uint frames = 1, float frametime = 1, uint width = 1, uint heigth = 1);

		agl::Animation* GetAnimation(const std::string& file);

		//=====[Level Data File]=====
		class LevelData {
		public:
			LevelData(int HighScore, int Stars, bool isUnlocked);

			int HighScore();
			int StarCount();
			bool IsUnlocked();

			void ChangeHighScore(int nr);
			void ChangeStars(int nr);
			void Unlock(int nr);


		private:
			int highScore;
			int stars;
			bool isUnlocked;
		};


		void LoadLevelFile(int log=false);

		
		bool IsUnlocked(int nr);
		int StarCount(int nr);
		int HighScore(int nr);

		void ChangeHighScore(int nr, int score);
		void ChangeStars(int nr, int stars);
		void Unlock(int nr);
		
		void UpdateSaveFile();

		//TO DO: zapis zmieniony przy ko�cu programu

		//=====[Audio (Igor -_-)]

		//===========
	private:
		std::map<std::string, agl::Texture> m_Textures;

		std::map<std::string, agl::Shader> m_Shaders;

		std::map<std::string, agl::Animation> m_Animations;

		std::map<int, Sus::LevelData> m_Levels;


	};

}
