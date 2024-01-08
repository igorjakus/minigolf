#include "Scenes.h"
#include "Core/AppData.h"

#include <Agl.h>

#include <cmath>
#include "Util.hpp"

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
	 m_graphicsLayer(*AppData::getSus().LoadAndGetShader("DefaultShader.glsl"), m_camera) {

	// temp (should also be black (no racism))

	AppData::getSus().LoadTexture("sponge");

	AppData::getSus().LoadAllTextures();
	AppData::getSus().LoadAllShaders();



	testObj = std::make_unique<agl::Object>(agl::Object(1.f, 1.f));
	testObj->setTexture(*AppData::getSus().GetTexture("popcat"));
	m_graphicsLayer.addObject(*testObj);
	
}

void BlankScene::update(float deltaT) {
	timer += deltaT;

	if (timer > 3.0f) {
		AppData::getSus().RemoveTexture("popcat");

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


	size = 50.0f;
	timer = .0f;

	const unsigned int tempX = AppData::getWindow().getWindowSize().x;
	const unsigned int tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize((float)tempX,(float)tempY);

	testObj = std::make_unique<agl::Object>(agl::Object(size, size, { 0, 0 }, { 255, 255, 255, 255 }));

	testObj->setTexture(*AppData::getSus().GetTexture("sponge"));
	m_graphicsLayer.addObject(*testObj);
}

void TestScene::update(float deltaT) {

	/////////////////////
	/// Input showcase:
	/////////////////////

	if(AppData::getInput().isKeyPressed("LEFT")) {
		speed = -100.0f;
	} else if(AppData::getInput().isKeyPressed("RIGHT")) {
		speed = 100.0f;
	} else {
		speed = .0f;
	}

	if(AppData::getInput().isKeyClicked("UP")) {
		testObj->setPosition(testObj->getPosition().x, testObj->getPosition().y + 50.0f);
	} else if(AppData::getInput().isKeyClicked("DOWN")) {
		testObj->setPosition(testObj->getPosition().x, testObj->getPosition().y - 50.0f);
	}

	if(AppData::getInput().getWheelOffset() != 0.0f) {
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

	/////////////////////
	/// Utils showcase:
	/////////////////////

	timer += deltaT * 0.3f;
	if(timer >= 1) {
		timer = 0;
	}

	float t = -4 * (timer - 0.5f) * (timer - 0.5f) + 1;
	size = util::lerp(50.0f, 100.0f, sqrtf(t));

	testObj->setScale(size, size);
}

void TestScene::render() {
	m_graphicsLayer.draw();
}

//NOLINTEND

}
