#pragma once

#include "Agl.h"
#include <iostream>
#include <fstream>
#include <string>

namespace sus {
	std::unique_ptr<agl::Texture> LoadTexture(std::string file_path); //na razie sciezka, potem bedzie wybieralo typ (dziwek, tekstura) i wystarczy nazwa (np. tekstura, white)


	class Tex {
	public: 
		Tex(std::string file);
		Tex* next;
		Tex* prvs;
		std::unique_ptr<agl::Texture> pTex;
		std::string name;
	
	};

	class RepTex {
	public:
		RepTex();
		void Add(Tex n);

		Tex* first;
		Tex* last;
	};




}