#include "Sus.h"

#include "Agl.h"
#include <iostream>
#include <fstream>
#include "../App/AppData.h"

std::unique_ptr<agl::Texture> sus::LoadTexture(std::string file) { //na razie sciezka, potem bedzie wybieralo typ (dziwek, tekstura) i wystarczy nazwa (np. tekstura, white)

	std::unique_ptr<agl::Texture> texturePointer = std::make_unique<agl::Texture>("assets/textures/"+file, GL_NEAREST, GL_REPEAT, GL_REPEAT);

	return texturePointer;
}