#include "Sus.h"

#include "Agl.h"
#include <iostream>
#include <fstream>
#include "../App/AppData.h"

agl::Texture sus::LoadTexture(std::string file) { //na razie sciezka, potem bedzie wybieralo typ (dziwek, tekstura) i wystarczy nazwa (np. tekstura, white)


	agl::Texture loadedTexture = agl::Texture(file, GL_NEAREST, GL_REPEAT, GL_REPEAT);


	return loadedTexture;
}