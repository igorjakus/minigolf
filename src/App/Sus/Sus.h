#pragma once

#include "Agl.h"
#include <iostream>
#include <fstream>
#include <string>

namespace sus {
	agl::Texture LoadTexture(std::string file_path); //na razie sciezka, potem bedzie wybieralo typ (dziwek, tekstura) i wystarczy nazwa (np. tekstura, white)


}