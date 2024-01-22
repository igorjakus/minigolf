#pragma once

#include "ECS/Entity.h"
#include "ECS/Component.h"

#include "Graphics.h"

namespace golf {

class Background {

public:
	Background();

	void render();

private:
	agl::Camera m_camera;
	agl::GraphicLayer m_layer;

	Entity m_image;

};



}
