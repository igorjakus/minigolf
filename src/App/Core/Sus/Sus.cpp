#include "Sus.h"
#include "Agl.h"
#include <dtl.h>

namespace golf {


	void Sus::LoadAll() {
		LoadAllTextures();
		LoadAllAudio();
	}

	//=====[Textures]=====
	void Sus::LoadListOfTextures(std::initializer_list<std::string> files) {
		for (auto file : files) {
			Sus::LoadTexture(file);
		}
	}
	void Sus::LoadTexture(const std::string& file, int filter, int sWrap, int tWrap) {
		if (m_Textures.find(file) != m_Textures.end()) {
			DTL_WAR("Trying to load already loaded texture:("+ file +"). Operation ignored.");
		}
		else if (!std::filesystem::exists("assets/textures/" + file)) {
			DTL_WAR("Trying to open non-existing file:(assets / textures / " + file + "). Operation ignored.");
		}
		else {
			m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(file), std::forward_as_tuple("assets/textures/" + file, filter, sWrap, tWrap));
		}
	}

	void Sus::LoadAllTextures() {
		//zbieranie po kolei z pliku, na razie tylko case 3 tekstur: //nie wiadomo czy bedzie rozwiniety
		LoadTexture("sponge.png");
		LoadTexture("white.png");
		LoadTexture("popcat.png");
	}

	agl::Texture* Sus::GetTexture(const std::string& file){
		auto item = m_Textures.find(file);
		if (item != m_Textures.end()) {
			return &item->second;
		}
		else {
			DTL_WAR("Trying to get not loaded texture:(" + file + "). Operation ignored.");
			return 0;
		}
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
			DTL_WAR("Trying to remove not loaded texture:(" + file + "). Operation ignored.");
		}
	}

	//=====[Textures]=====
	void Sus::LoadShader(const std::string& file) {
		if (m_Shaders.find(file) != m_Shaders.end()) {
			DTL_WAR("Trying to load already loaded shader:(" + file + "). Operation ignored.");
		}
		else if (!std::filesystem::exists("assets/shaders/" + file)) {
			DTL_WAR("Trying to open non - existing file : (assets / shaders /" + file + "). Operation ignored.");
		}
		else {
			m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(file), std::forward_as_tuple("assets/textures/" + file));
		}
	}

	agl::Shader* Sus::GetShader(const std::string& file) {
		auto item = m_Shaders.find(file);
		if (item != m_Shaders.end()) {
			return &item->second;
		}
		else {
			DTL_WAR("Trying to get not loaded texture:(" + file + "). Operation ignored.");
			return 0;
		}
	}

	agl::Shader* Sus::LoadAndGetShader(const std::string& file) {
		LoadShader(file);
		return(GetShader(file));
	}
	
	//=====================
	void Sus::LoadAllAudio() {

	}

}