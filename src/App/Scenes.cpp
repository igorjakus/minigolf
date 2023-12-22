#include "Scenes.h"
#include "Agl.h"
#include <memory>

namespace golf {

BlankScene::BlankScene()
	:m_shader("assets/shaders/DefaultShader.glsl"),
	 m_camera(0.F, 0.F, 1.F, 1.F, 1.F), 
	 m_graphicsLayer(m_shader, m_camera) {

	testTex = std::make_unique<agl::Texture>("assets/textures/white.png", GL_NEAREST, GL_REPEAT, GL_REPEAT);
	testObj = std::make_unique<agl::Object>(agl::Object(1, 1, *testTex, {0, 0}));

	m_graphicsLayer.addObject(*testObj);
	
}

void BlankScene::update([[maybe_unused]]float deltaT) {

}

void BlankScene::render() {
	m_graphicsLayer.draw();
}

void BlankScene::load() {

}



}
