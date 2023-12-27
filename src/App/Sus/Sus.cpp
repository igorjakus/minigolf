#include "Sus.h"

#include "Agl.h"
#include <iostream>
#include <fstream>

agl::Texture * sus::Load(std::string filePath) { //na razie sciezka, potem bedzie wybieralo typ (dziwek, tekstura) i wystarczy nazwa (np. tekstura, white)


	//loaded_texture = std::make_unique<agl::Texture>("assets/textures/white.png", GL_NEAREST, GL_REPEAT, GL_REPEAT);
	agl::Texture loadedTexture = agl::Texture(filePath, 0,0,0);

	return &loadedTexture;
}