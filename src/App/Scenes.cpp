#include "Scenes.h"
#include "Core/AppData.h"

#include <Agl.h>

//Temp:
//NOLINTBEGIN

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
	if (timer > 3.0f) {
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
	m_camera.setSize(static_cast<float>(tempX), static_cast<float>(tempY));
	testObj = std::make_unique<agl::Object>(agl::Object(50.0f, 50.0f, {0, 0}, {255, 0, 0, 255}));
	m_graphicsLayer.addObject(*testObj);
}

void TestScene::update([[maybe_unused]] float deltaT) {
	if(AppData::getInput().isKeyPressed("LEFT")) {
		speed = -50.0f;
	} else if(AppData::getInput().isKeyPressed("RIGHT")) {
		speed = 50.0f;
	} else {
		speed = .0f;
	}

	if(AppData::getInput().isKeyClicked("UP")) {
		testObj->setPosition(testObj->getPosition().x, testObj->getPosition().y + 50.0f);
	} else if(AppData::getInput().isKeyClicked("DOWN")) {
		testObj->setPosition(testObj->getPosition().x, testObj->getPosition().y - 50.0f);
	}

	if(AppData::getInput().getWheelOffset() != 0.0f) {
		// This obviously doesn't work because we need some lerps and norms and clamps and stuff like that but you get the idea
		// float scale = AppData::getInput().getWheelOffset();
		// testObj->setScale(testObj->getScale().x * scale, testObj->getScale().y * scale;
		DTL_ENT("{0}", AppData::getInput().getWheelOffset());
	}

	if(AppData::getInput().isLeftMouseClicked()) {
		DTL_ENT("Hello!");
	} else if(AppData::getInput().isRightMousePressed()) {
		DTL_ENT("YOOOO");
	}

	AppData::getInput().setMousePosLock(AppData::getInput().isKeyPressed("SPACE"));

	if(AppData::getInput().isMouseLocked()) {
		auto[x, y] = AppData::getInput().getMouseOffset();
		if(x != 0 || y != 0) {
			DTL_ENT("{0}, {0}", x, y);
		}
	} else {
		if(AppData::getInput().isKeyClicked("V")) {
			AppData::getInput().toggleMouseVisibility();
		}
	}

	testObj->setPosition(testObj->getPosition().x + speed * deltaT, testObj->getPosition().y);
}

void TestScene::render() {
	m_graphicsLayer.draw();
}

//NOLINTEND

}
