#include "Sus.h"

#include "Agl.h"
#include <iostream>
#include <fstream>
#include "../App/AppData.h"
#include <filesystem>

namespace golf {


	void Sus::LoadAll() {
		LoadAllTextures();
		LoadAllAudio();
	}
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
			DTL_WAR("Trying to open non-existing file:(" + file + "). Operation ignored.");
		}
		else {
			m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(file), std::forward_as_tuple("assets/textures/" + file, filter, sWrap, tWrap));
		}
	}

	void Sus::LoadAllTextures() {
		//zbieranie po kolei z pliku, na razie tylko case 3 tekstur:
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


	
	//=====================
	void Sus::LoadAllAudio() {

	}

}