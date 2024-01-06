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


	testObj = std::make_unique<agl::Object>(agl::Object(1.f, 1.f));
	testObj->setTexture(*AppData::getSus().GetTexture("popcat.png"));
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

	size = 50.0f;
	timer = .0f;

	const unsigned int tempX = AppData::getWindow().getWindowSize().x;
	const unsigned int tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize((float)tempX,(float)tempY);

	testObj = std::make_unique<agl::Object>(agl::Object(size, size, { 0, 0 }, { 255, 255, 255, 255 }));

	testObj->setTexture(*AppData::getSus().GetTexture("sponge.png"));
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


// ===============================
// LevelOneScene
// ===============================

LevelOneScene::LevelOneScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(AppData::getGlobalShader(), m_camera)
{
	const int tempX = AppData::getWindow().getWindowSize().x;
	const int tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize((float)tempX / (float)tempY, 1.0F);
	WallA = std::make_unique<agl::Object>(agl::Object(0.01f, 0.1f, { -0.5f, 0 } ));
	WallB = std::make_unique<agl::Object>(agl::Object(0.01f, 0.1f, { 0, 0 }));
	WallA->setTexture(*AppData::getSus().GetTexture("sponge.png"));
	WallB->setTexture(*AppData::getSus().GetTexture("sponge.png"));
	m_graphicsLayer.addObject(*WallA);
	m_graphicsLayer.addObject(*WallB);
}

void LevelOneScene::update(float deltaT)
{
	if (isFirstUpdate) {
		DTL_INF("level one scene -- click q to quit, r to play again, w to win");
		isFirstUpdate = false;
	}
	//quit
	if (AppData::getInput().isKeyClicked("Q")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
		AppData::getSceneManager().nextScene();
	}
	//retry
	if (AppData::getInput().isKeyClicked("R")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelOneScene()));
		AppData::getSceneManager().nextScene();
	}
	//won
	if (AppData::getInput().isKeyClicked("W")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new ResultsScene(10, 1)));
		AppData::getSceneManager().nextScene();
	}
	
}

void LevelOneScene::render()
{
	m_graphicsLayer.draw();
}

//NOLINTEND


// ===============================
// LevelSelectionScene
// ===============================

LevelSelectionScene::LevelSelectionScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(AppData::getGlobalShader(), m_camera)
{
	const int tempX = AppData::getWindow().getWindowSize().x;
	const int tempY = AppData::getWindow().getWindowSize().y;
	cokolwiek = std::make_unique<agl::Object>(agl::Object(0.1f, 0.1f, { -0.5f, 0 }));
	m_camera.setSize((float)tempX / (float)tempY, 1.0F);
	m_graphicsLayer.addObject(*cokolwiek);
}

void LevelSelectionScene::update(float deltaT)
{
	if (isFirstUpdate) {
		DTL_INF("level selection scene -- click 1 to play lvl 1, 2 to play lvl 2");
		isFirstUpdate = false;
	}


	if (AppData::getInput().isKeyClicked("1")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelOneScene()));
		AppData::getSceneManager().nextScene();
	}

	if (AppData::getInput().isKeyClicked("2")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelTwoScene()));
		AppData::getSceneManager().nextScene();
	}
}

void LevelSelectionScene::render()
{
	m_graphicsLayer.draw();
}


// ===============================
// LevelTwoScene
// ===============================


LevelTwoScene::LevelTwoScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(AppData::getGlobalShader(), m_camera)
{
	const int tempX = AppData::getWindow().getWindowSize().x;
	const int tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize((float)tempX / (float)tempY, 1.0F);
}

void LevelTwoScene::update(float deltaT)
{
	if (isFirstUpdate) {
		DTL_INF("level two scene -- click q to quit, r to play again");
		isFirstUpdate = false;
	}

	if (AppData::getInput().isKeyClicked("Q")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
		AppData::getSceneManager().nextScene();
	}

	if (AppData::getInput().isKeyClicked("R")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelTwoScene()));
		AppData::getSceneManager().nextScene();
	}
}

void LevelTwoScene::render()
{
	m_graphicsLayer.draw();
}

ResultsScene::ResultsScene(int score, int lvlNumber)
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(AppData::getGlobalShader(), m_camera), playerScore(score), finishedLevelNumber(lvlNumber)
{
	const int tempX = AppData::getWindow().getWindowSize().x;
	const int tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize((float)tempX / (float)tempY, 1.0F);
}

void ResultsScene::update(float deltaT)
{
	if (isFirstUpdate) {
		DTL_INF("results scene -- click q to quit, r to play again, c to continue (next lvl)");
		isFirstUpdate = false;
	}

	//quit
	if (AppData::getInput().isKeyClicked("Q")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
		AppData::getSceneManager().nextScene();
	}

	//play again
	if (AppData::getInput().isKeyClicked("R")) {
		startLevel(finishedLevelNumber);
	}

	//next level

	if (AppData::getInput().isKeyClicked("C")) {
		startLevel(finishedLevelNumber += 1);
	}



}

void ResultsScene::render()
{
	m_graphicsLayer.draw();
}


//funkcja ktora uruchamia odpowiedni poziom
void startLevel(int levelNumber)
{
	if (levelNumber == 1) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelOneScene()));
		AppData::getSceneManager().nextScene();
	}
	if (levelNumber == 2) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelTwoScene()));
		AppData::getSceneManager().nextScene();
	}
}

}
