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
	timer ++;
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

	const unsigned int tempX = AppData::getWindow().getWindowSize().x;
	const unsigned int tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize(static_cast<float>(tempX) / static_cast<float>(tempY), 1.0F);
	testObj = std::make_unique<agl::Object>(agl::Object(0.1f, 0.1f, {0, 0}, {255, 0, 0, 255}));
	m_graphicsLayer.addObject(*testObj);
}

void TestScene::update([[maybe_unused]] float deltaT) {
	if(AppData::getInput().isKeyPressed("LEFT")) {
		speed = -0.001f;
	} else if(AppData::getInput().isKeyPressed("RIGHT")) {
		speed = 0.001f;
	} else {
		speed = .0f;
	}

	if(AppData::getInput().isKeyClicked("UP")) {
		testObj->setPosition(testObj->getPosition().x, testObj->getPosition().y + 0.1f);
	} else if(AppData::getInput().isKeyClicked("DOWN")) {
		testObj->setPosition(testObj->getPosition().x, testObj->getPosition().y - 0.1f);
	}

	if(AppData::getInput().getWheelOffset() != 0.0f) {
		// This obviously doesn't work because we need some lerps and norms and clamps and stuff like that but you get the idea;
		// float scale = AppData::getInput().getWheelOffset();
		// testObj->setScale(testObj->getScale().x * scale, testObj->getScale().y * scale;
		DTL_ENT("{0}", AppData::getInput().getWheelOffset());
	}

	if(AppData::getInput().isLeftMouseClicked()) {
		DTL_ENT("Hello!");
	} else if(AppData::getInput().isRightMousePressed()) {
		DTL_ENT("YOOOO");
	}

	testObj->setPosition(testObj->getPosition().x + speed * deltaT, testObj->getPosition().y);
}

void TestScene::render() {
	m_graphicsLayer.draw();
}

}
