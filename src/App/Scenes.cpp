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
	 m_graphicsLayer(AppData::getGlobalShader(), m_camera) {

	// temp (should also be black (no racism))

	AppData::getSus().LoadListOfTextures({ "popcat.png","sponge.png" });

	testObj = m_graphicsLayer.newQuad(1.f, 1.f);
	testObj->setVisual(*AppData::getSus().GetTexture("popcat.png"));
	
}

void BlankScene::update(float deltaT) {
	timer += deltaT;

	if (timer > 1.0f) {
		AppData::getSus().RemoveTexture("popcat.png");

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

	size = 100.0f;
	timer = .0f;

	testObj = m_graphicsLayer.newQuad(1.f, 1.f);

	const unsigned int tempX = AppData::getWindow().getWindowSize().x;
	const unsigned int tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize((float)tempX,(float)tempY);

	testTex = std::make_unique<agl::Animation>("assets/textures/test.png", GL_LINEAR, 97, 0.05f, 10, 10);
	//testTex = std::make_unique<agl::Texture>("assets/textures/test.png", GL_LINEAR);
	//testObj->setVisual(*AppData::getSus().GetTexture("sponge.png"));
	testObj->setVisual(*testTex);
}

void TestScene::update(float deltaT) {

	/////////////////////
	/// Input showcase:
	/////////////////////
	testTex->update(deltaT);
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
