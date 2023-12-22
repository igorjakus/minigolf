#include "Scenes.h"

#include "Agl.h"
#include "AppData.h"

namespace golf {

BlankScene::BlankScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F), 
	 m_graphicsLayer(AppData::getGlobalShader(), m_camera) {

	// temp
	testTex = std::make_unique<agl::Texture>("assets/textures/white.png", GL_NEAREST, GL_REPEAT, GL_REPEAT);
	testObj = std::make_unique<agl::Object>(agl::Object(0.1, 0.1, *testTex));
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
