#include<pch.h>
#include"Sus.h"
#include"dtl.h"

#define TEXTURE_PATH "assets/textures/"
#define SHADER_PATH "assets/shaders/"
#define ANIMATION_PATH "assets/animation/"
#define LEVELS "assets/data/Levels.txt"

//NOLINTBEGIN

namespace golf 
{
	void Sus::LoadAll() {
		LoadAllTextures();
		LoadAllShaders();
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
		}
		
		if (m_Textures.find(fileName) != m_Textures.end()) {
			DTL_WAR("SUS: Trying to load already loaded texture:({0}). Operation ignored.", file);
		}
		else if (!std::filesystem::exists(TEXTURE_PATH + file) && !std::filesystem::exists(TEXTURE_PATH + fileName+ ".png")) {
			DTL_WAR("SUS: Trying to open non-existing file:({0}{0}). Operation ignored.", TEXTURE_PATH, file);
		}
		else {
			m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(fileName), std::forward_as_tuple(TEXTURE_PATH + fileName + ".png", filter, glm::ivec2(1, 1), sWrap, tWrap));
		}
		DTL_INF("SUS: Texture loaded \"{0}\"", fileName);
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
	//=====[Data File]=====
	void Sus::LoadLevelFile(int log) {
		std::ifstream file(LEVELS);
		std::filesystem::path p = std::filesystem::current_path();
		std::cout << p.relative_path() <<"\n";

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


	//=====================
	void Sus::LoadAllAudio() {

	}
}

//NOLINTEND
