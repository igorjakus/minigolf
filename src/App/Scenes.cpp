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

	AppData::getSus().LoadListOfTextures({ "popcat.png","sponge.png","white.png" });
	//AppData::getSus().LoadTexture("popcat.png", GL_LINEAR);
	AppData::getSus().GetTexture("test.png");
	testObj = std::make_unique<agl::Object>(agl::Object(1.f, 1.f));
	testObj->setTexture(*AppData::getSus().GetTexture("popcat.png"));
	testObj->setTexture(*AppData::getSus().GetTexture("popcat2.png"));
	m_graphicsLayer.addObject(*testObj);
	
}

void BlankScene::update(float deltaT) {
	timer += deltaT;
	if (timer > 150) {
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




	const int tempX = AppData::getWindow().getWindowSize().x;
	const int tempY = AppData::getWindow().getWindowSize().y;


	m_camera.setSize((float)tempX / (float)tempY, 1.0F);

	AppData::getSus().LoadTexture("sponge.png");

	testObj = std::make_unique<agl::Object>(agl::Object(0.1f, 0.1f, {0, 0}, {255, 255, 255, 255}));
	testObj->setTexture(*AppData::getSus().GetTexture("sponge.png"));
	m_graphicsLayer.addObject(*testObj);
}


void TestScene::update([[maybe_unused]] float deltaT) {
	testObj->setPosition(testObj->getPosition().x + speed * deltaT, 0);
}

void TestScene::render() {
	m_graphicsLayer.draw();
}

}
