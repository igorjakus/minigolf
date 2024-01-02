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
	testTex = std::make_unique<agl::Texture>("assets/textures/white.png", GL_NEAREST, GL_REPEAT, GL_REPEAT);
	testObj = std::make_unique<agl::Object>(agl::Object(1, 1, *testTex));
	m_graphicsLayer.addObject(*testObj);
	
}

void BlankScene::update(float deltaT) {
	timer += deltaT;
	if (timer > 3) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new TestScene()));
		AppData::getSceneManager().loadNextScene();
		AppData::getSceneManager().nextScene();
	}
}

void BlankScene::render() {
	m_graphicsLayer.draw();
}

void BlankScene::load() {
	m_loaded = true;
}


// ===============================
// TestScene
// ===============================

TestScene::TestScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(AppData::getGlobalShader(), m_camera) {




	const int tempX = AppData::getWindow().getWindowSize().x;
	const int tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize((float)tempX/(float)tempY, 1.0F);


	//testTex = 
	testObj = std::make_unique<agl::Object>(agl::Object(0.1, 0.1, *testTex)); // <--
	m_graphicsLayer.addObject(*testObj);

}

void TestScene::update([[maybe_unused]] float deltaT) { 
	pos += speed * deltaT;
}

void TestScene::render() {
	testObj->setPosition(pos, 0); //<--
	m_graphicsLayer.draw();
}

void TestScene::load() { //tutaj sus ³aduje potrzebne tekstury
	DTL_INF("loading...");

	


	std::this_thread::sleep_for(std::chrono::seconds(1));
	DTL_INF("loaded scene");
	m_loaded = true;
}

}
