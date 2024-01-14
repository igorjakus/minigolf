#include<pch.h>
#include"Sus.h"
#include"dtl.h"

#define TEXTURE_PATH "assets/textures/"
#define SHADER_PATH "assets/shaders/"
#define ANIMATION_PATH "assets/animation/"
#define LEVELS "assets/data/"

//NOLINTBEGIN

namespace golf 
{
	void Sus::LoadAll() {
		LoadAllTextures();
		LoadAllShaders();
		LoadLevelFile(true);


	}

	//=====[Textures]=====
	void Sus::LoadListOfTextures(std::initializer_list<std::string> files) {
		for (auto file : files) {
			Sus::LoadTexture(file);
		}
	}
	void Sus::LoadTexture(const std::string& file, int filter, int sWrap, int tWrap) {
		//sprawdzanie formatu danej i zmienienie nazwy adekwatnie:
		std::string fileName;
		if (file.std::string::find(".png") != std::string::npos){
			fileName = file.std::string::substr(0, file.std::string::size() - 4);
		}
		else {
			fileName = file;
		}//
		
		if (m_Textures.find(fileName) != m_Textures.end()) {
			DTL_WAR("SUS: Trying to load already loaded texture:({0}). Operation ignored.", file);
		}
		else if (!std::filesystem::exists(TEXTURE_PATH + file) && !std::filesystem::exists(TEXTURE_PATH + fileName+ ".png")) {
			DTL_WAR("SUS: Trying to open non-existing file:({0}{0}). Operation ignored.", TEXTURE_PATH, file);
		}
		else {
			m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(fileName), std::forward_as_tuple(TEXTURE_PATH + fileName + ".png", filter, glm::ivec2(1, 1), sWrap, tWrap));
			DTL_INF("SUS: Texture loaded \"{0}\"", fileName);
		}
	}

	void Sus::LoadAllTextures() {
		std::string temp = TEXTURE_PATH;
		for (const auto& entry : std::filesystem::directory_iterator(TEXTURE_PATH)) {
			if (std::filesystem::is_regular_file(entry)) {
				LoadTexture(entry.path().string().erase(0, temp.length()));
			}
		}
	}

	agl::Texture* Sus::GetTexture(const std::string& file){
		auto item = m_Textures.find(file);
		if (item != m_Textures.end()) {
			return &item->second;
		}
		DTL_WAR("SUS: Trying to get not loaded texture:(" + file + "). Operation ignored.");
		return nullptr;
	}

	void Sus::RemoveListOfTextures(std::initializer_list<std::string> files) {
		for (auto file : files) {
			Sus::RemoveTexture(file);
		}
	}
	void Sus::RemoveTexture(const std::string& file) {
		if (m_Textures.find(file) != m_Textures.end()) {
			m_Textures.erase(file);
		}
		else {
			DTL_WAR("SUS: Trying to remove not loaded texture:({0}). Operation ignored.", file);
		}
	}

	//=====[Shaders]=====

	void Sus::LoadShader(const std::string& file) {
		if (m_Shaders.find(file) != m_Shaders.end()) {
			DTL_WAR("SUS: Trying to load already loaded shader:({0}). Operation ignored.",file);
		}
		else if (!std::filesystem::exists(SHADER_PATH + file)) {
			DTL_WAR("SUS: Trying to open non - existing file : ({0}{0}). Operation ignored.", SHADER_PATH,file);
		}
		else {
			m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(file), std::forward_as_tuple(SHADER_PATH + file));
		}
	}
	
	agl::Shader* Sus::GetShader(const std::string& file) {
		auto item = m_Shaders.find(file);
		if (item != m_Shaders.end()) {
			return &item->second;
		}
		DTL_WAR("SUS: Trying to get not loaded shader:({0}). Operation ignored.", file);
		return nullptr;
	}
	
	agl::Shader* Sus::LoadAndGetShader(const std::string& file) {
		LoadShader(file);
		return(GetShader(file));
	}

	void Sus::LoadAllShaders() {
		std::string temp = SHADER_PATH;
		for (const auto& entry : std::filesystem::directory_iterator(SHADER_PATH)) {
			if (std::filesystem::is_regular_file(entry)) {
				LoadShader(entry.path().string().erase(0, temp.length()));
			}
		}
	}
	//=====[Animations]=====

	void Sus::LoadAnimation(const std::string& file, int filter, uint frames, float frametime, uint width, uint heigth) {
		//sprawdzanie formatu danej i zmienienie nazwy adekwatnie:
		std::string fileName;
		if (file.std::string::find(".png") != std::string::npos) {
			fileName = file.std::string::substr(0, file.std::string::size() - 4);
		}
		else {
			fileName = file;
		}//

		if (m_Animations.find(fileName) != m_Animations.end()) {
			DTL_WAR("SUS: Trying to load already loaded animation:({0}). Operation ignored.", file);
		}
		else if (!std::filesystem::exists(ANIMATION_PATH + file) && !std::filesystem::exists(ANIMATION_PATH + fileName + ".png")) {
			DTL_WAR("SUS: Trying to open non-existing file:({0}{0}). Operation ignored.", ANIMATION_PATH, file);
		}
		else {
			m_Animations.emplace(std::piecewise_construct, std::forward_as_tuple(fileName), std::forward_as_tuple(ANIMATION_PATH + fileName + ".png",
				filter, frames, frametime, width, heigth));
			DTL_INF("SUS: Animation loaded \"{0}\"", fileName);
		}

	}



	//=====[Level Data File]=====

	void Sus::LoadLevelFile(int log) {
		std::string str = "Levels.txt";
		std::ifstream file(LEVELS + str);

		std::string line;
		while (std::getline(file,line)) {
			int nr = std::stoi(line.substr(line.find("Level ") + 6));
			int highScore = std::stoi(line.substr(line.find("HighScore: ") + 11));
			bool isUnlocked = std::stoi(line.substr(line.find("isUnlocked: ") + 12));

			m_Levels.emplace(std::piecewise_construct, std::forward_as_tuple(nr), std::forward_as_tuple(std::make_pair(highScore,isUnlocked)));

			if (log) {
				DTL_INF("SUS: Level {0} loaded; whole line: {0}", nr, line);
			}
		}
		file.close();
	}

	bool Sus::IsUnlocked(int nr) {
		auto item = m_Levels.find(nr);
		if (item != m_Levels.end()) {
			return item->second.second;
		}
		else {
			DTL_WAR("SUS: Level {0} doesn't exist, return 0 :c",nr);
			return 0;
		}
	}
	int Sus::HighScore(int nr) {
		auto item = m_Levels.find(nr);
		if (item != m_Levels.end()) {
			return item->second.first;
		}
		else {
			DTL_WAR("SUS: Level {0} doesn't exist, return 0 :c", nr);
			return 0;
		}
	}

	void Sus::ChangeHighScore(int nr, int score) {
		auto item = m_Levels.find(nr);
		if (item != m_Levels.end()) {
			item->second.first = score;
		}
		else {
			DTL_WAR("SUS: Level {0} doesn't exist, return 0 :c", nr);
		}
	}
	void Sus::Unlock(int nr) {
		auto item = m_Levels.find(nr);
		if (item != m_Levels.end()) {
			item->second.second = 1;
		}
		else {
			DTL_WAR("SUS: Level {0} doesn't exist, return 0 :c", nr);
		}


		//nadpisywac powinien na koniec programu (aktualizacja orgina³u tj) NIE USUWAC NOTATKI
		/*
		auto item = m_Levels.find(nr);
		if (item != m_Levels.end()) {
			std::string str1 = "Levels.txt";
			std::ifstream file(LEVELS + str1);
			std::string str2 = "Temp.txt";
			std::ofstream temp_file(LEVELS + str1);

			std::string line;
			std::string new_line = ":3";

			while (std::getline(file, line)) {
				int level_nr = std::stoi(line.substr(line.find("Level ") + 6));
				if (level_nr == nr) {
					line = new_line;
				}
				temp_file << line << std::endl;
			}
			file.close();
			temp_file.close();


		}
		else {
			DTL_WAR("SUS: Level {0} doesn't exist :c", nr);
			return;
		}
		*/
	}

	void Sus::UpdateSaveFile() {
		std::string path = "../../../assets/data/Levels.txt"; //b³agam Macieju i £ukaszu, nie zabijajcie za to proszê :cc
		std::string path_temp = "../../../assets/data/Temp.txt";

		std::ifstream file(path);
		std::ofstream file_temp(path_temp);
		std::string line;

		int counter = 1;
		auto mapa = m_Levels.find(counter);

		while (std::getline(file, line)) {
			mapa = m_Levels.find(counter);
			file_temp << "Level " << counter <<": HighScore: " << mapa->second.first << ", isUnlocked: " << mapa->second.second << "\n";
			counter++;
		}
		file.close();
		file_temp.close();

		//std::remove("../../../assets/data/Levels.txt");
		//std::rename("../../../assets/data/Temp.txt", "Levels.txt");//za to te¿, na razie dzia³a a bêdê móg³ zrobiæ ³adniej

	}

	//=====================
	void Sus::LoadAllAudio() {

	}
}

//NOLINTEND
