#include "Scenes.h"

#include "Agl.h"
#include "AppData.h"

namespace golf {

// forward declarations:
class BlankScene;
class TestScene;

// ===============================
// BlankScene
// ===============================

BlankScene::BlankScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F), 
	 m_graphicsLayer(AppData::getGlobalShader(), m_camera) {

	// temp (should also be black (no racism))
	testTex = std::make_unique<agl::Texture>("assets/textures/popcat.png", GL_NEAREST, GL_REPEAT, GL_REPEAT);
	testObj = std::make_unique<agl::Object>(agl::Object(1.f, 1.f));
	testObj->setTexture(*testTex);
	m_graphicsLayer.addObject(*testObj);
	
}

void BlankScene::update(float deltaT) {
	timer += deltaT;
	if (timer > 300) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new TestScene()));
		AppData::getSceneManager().nextScene();
	}
}

void BlankScene::render() {
	m_graphicsLayer.draw();
}


// ===============================
// TestScene
// ===============================

TestScene::TestScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(AppData::getGlobalShader(), m_camera) {

	const int tempX = AppData::getWindow().getWindowSize().x;
	const int tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize((float)tempX / (float)tempY, 1.0F);
	testObj = std::make_unique<agl::Object>(agl::Object(0.1f, 0.1f, {0, 0}, {255, 0, 0, 255}));
	m_graphicsLayer.addObject(*testObj);
}

void TestScene::update([[maybe_unused]] float deltaT) {
	//testObj->setPosition(testObj->getPosition().x + speed * deltaT, 0);
}

void TestScene::render() {
	m_graphicsLayer.draw();
}

}
