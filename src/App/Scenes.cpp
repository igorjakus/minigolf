#include <pch.h>
#include "Scenes.h"
#include "Core/AppData.h"

#include "ECS/Entity.h"
#include "Graphics.h"

#include "physics.h"

#include "Util.hpp"

// Temp:
// NOLINTBEGIN

namespace golf {


// ===============================
// PhysicsTestingScene
// ===============================

PhysicsTestingScene::PhysicsTestingScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {

	const uint tempX = AppData::getWindow().getWindowSize().x;
	const uint tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize(static_cast<float>(tempX) / static_cast<float>(tempY), 1.0F);

	auto visual = std::make_shared<VisualComponent>(&m_graphicsLayer);
	m_kot.addComponent<VisualComponent>(visual);
	m_kot.getComponent<VisualComponent>()->setTexture("popcat");
	m_kot.getTransform()->setScale(0.1f);
	
	auto physics = std::make_shared<DynamicPhysicsComponent>(1,1);
	m_kot.addComponent<DynamicPhysicsComponent>(physics);

}

void PhysicsTestingScene::update([[maybe_unused]]float deltaT) {
	
	if (AppData::getInput().isKeyClicked("UP")) {
		m_kot.getComponent<DynamicPhysicsComponent>()->apply_impulse({0,1,0},{0,0,0});
	}
	if (AppData::getInput().isKeyClicked("DOWN")) {
		m_kot.getComponent<DynamicPhysicsComponent>()->apply_impulse({0,-1,0},{0,0,0});
		
	}
	if (AppData::getInput().isKeyClicked("LEFT")) {
		m_kot.getComponent<DynamicPhysicsComponent>()->apply_impulse({-1,0,0},{0,0,0});
		
	}
	if (AppData::getInput().isKeyClicked("RIGHT")) {
		m_kot.getComponent<DynamicPhysicsComponent>()->apply_impulse({1,0,0},{0,0,0});
		
	}
	m_kot.getComponent<DynamicPhysicsComponent>()->update_positions(deltaT);
}

void PhysicsTestingScene::render() {
	m_graphicsLayer.draw();
}


// ===============================
// BlankScene
// ===============================

BlankScene::BlankScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {

	const uint tempX = AppData::getWindow().getWindowSize().x;
	const uint tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize(static_cast<float>(tempX) / static_cast<float>(tempY), 1.0F);

	auto comp = std::make_shared<VisualComponent>(&m_graphicsLayer);
	m_kot.addComponent<VisualComponent>(comp);
	m_kot.getComponent<VisualComponent>()->setTexture("popcat");
	m_kot.getTransform()->setScale(0.5f);
	// m_kot.getTransform()->xScale = 0.8f;
	// m_kot.getTransform()->yScale = 0.3f;

}

void BlankScene::update(float deltaT) {
	timer += deltaT;
	
	if (AppData::getInput().isKeyClicked("ENTER")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new TestScene()));
		AppData::getSceneManager().nextScene();
	}
	if (AppData::getInput().isKeyClicked("UP")) {
		m_kot.getComponent<VisualComponent>()->setTexture("popcat");
	}
	if (AppData::getInput().isKeyClicked("DOWN")) {
		m_kot.getComponent<VisualComponent>()->setTexture("sponge");
	}
	if (AppData::getInput().isKeyClicked("LEFT")) {
		m_kot2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		m_kot2.getTransform()->setScale(.2f);
	}
	if (AppData::getInput().isKeyClicked("RIGHT")) {
		m_kot2.removeComponent<VisualComponent>();
	}
}

void BlankScene::render() {
	m_graphicsLayer.draw();
}

// ===============================
// TestScene
// ===============================

void BouncyComponent::setVelocity(std::pair<float, float> vel) {
	velocity = vel;
}
void BouncyComponent::setBoundaries(float min1, float max1, float min2, float max2) {
	minX = min1; maxX = max1; minY = min2; maxY = max2;
}

void BouncyComponent::updatePosition(float deltaT) {
	if (!getOwner()) {
		return;
	}
	// uwaga! nie mamy pewności że transform istnieje! (getTransform zwróci nullptr jeśli nie ma właściciela (przypisanego Entity))
	float& x = getTransform()->x;
	float& y = getTransform()->y;
	x += velocity.first * deltaT;
	y += velocity.second * deltaT;
	if (x < minX || x > maxX) {
		velocity.first *= -1;
		x = util::clamp(x, minX, maxX);
		if (getOwner()->hasComponent<VisualComponent>()) { // again powinniśmy się upewniać że komponent do którego chcemy się odwołać wgl istnieje
			getOwner()->getComponent<VisualComponent>()->setTexture("popcat");
		}
	}
	if (y < minY || y > maxY) {
		velocity.second *= -1;
		y = util::clamp(y, minY, maxY);
		if (getOwner()->hasComponent<VisualComponent>()) { // again powinniśmy się upewniać że komponent do którego chcemy się odwołać wgl istnieje
			getOwner()->getComponent<VisualComponent>()->setTexture("sponge");
		}
	}
}

// Faktyczna scena poniżej vvv

TestScene::TestScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {

	size = 100.0f;
	timer = .0f;

	const float tempX = static_cast<float>(AppData::getWindow().getWindowSize().x);
	const float tempY = static_cast<float>(AppData::getWindow().getWindowSize().y);
	m_camera.setSize(tempX, tempY);

	auto graphics = std::make_shared<VisualComponent>(&m_graphicsLayer);
	// Niby można też graphics = std::make_shared<TextureComponent>(); tylko że wtedy ten komponent 
	// nie będzie przypisany do żadnej warstwy graficznej i tym samym nie będzie się wyświetlać
	testObj.addComponent<VisualComponent>(graphics);
	// Można też bezpośrednio wrzucić wynik m_graphicsLayer.addTexComponent() do addComponent() czyli:
	// testObj.addComponent<TextureComponent>(m_graphicsLayer.addTexComponent()); jednak wtedy nie 
	// mamy bezpośredniego wskaźnika na ten komponent i musimy go szukać chcąc z nim coś robić.
	testObj.getComponent<VisualComponent>()->setTexture("popcat");
	// Jeżeli mamy nasz pointer "graphics" to możemy po prostu:
	// graphics->setTexture("popcat");
	// co jest szybsze, tym bardziej że przy powyższej metodzie powinniśmy upewnić się najpierw,
	// że testObj w ogóle posiada TextureComponent poprzez if(testObj.hasComponent<TextureComponent>())
	testObj.getTransform()->setScale(size);
	// Tu po prostu biorę transform naszego obiektu (mamy gwarancje że każdy objekt posiada transform)
	// i ustawiam skalę obietku (pozycja, obrót i skala są przechowywane w trasformie)
	// Uwaga! Transform technicznie rzecz biorąc nie jest komponentem tzn. np. testObj.hasComponent<Transform>()
	// zwróci false

	srand(2137);
	const float spoingSize = 75;
	// Ciekawszy przykład: iterujemy po elementach listy Entity
	for (uint i = 0; i < spoingCount; i++) {
		std::shared_ptr<VisualComponent> tex = std::make_shared<VisualComponent>(&m_graphicsLayer); // Tworzymy komponent tex
		someSpoingbobs[i].addComponent<VisualComponent>(tex); // przypisujemy właściciela komponentu
		tex->setTexture("sponge"); // ustawiamy komponentowi tex texturę jaką ma trzymać

		BouncyComponent& bounce = comps[i];
		someSpoingbobs[i].addComponent<BouncyComponent>(bounce); // przypisujemy właściciela komponentu
		// nadajemy mu jakieś właściwości (losowe)
		float xVel = static_cast<float>(rand() % 300) * (i % 2 == 0 ? 1.f : -1.f);
		float yVel = static_cast<float>(rand() % 500) * (i % 3 == 0 ? 1.f : -1.f);
		comps[i].setVelocity({xVel, yVel});
		comps[i].setBoundaries((tempX - spoingSize) / -2, (tempX - spoingSize) / 2, (tempY - spoingSize) / -2, (tempY - spoingSize) / 2);

		someSpoingbobs[i].getTransform()->setScale(spoingSize); // na koniec zmieniamy skalę każdego entity
	}

}

void TestScene::update(float deltaT) {

	/////////////////////
	/// Input showcase:
	/////////////////////
	//testTex->update(deltaT);
	if (AppData::getInput().isKeyPressed("LEFT")) {
		speed = -100.0f;
	}
	else if (AppData::getInput().isKeyPressed("RIGHT")) {
		speed = 100.0f;
	}
	else {
		speed = .0f;
	}
	testObj.getTransform()->x += speed * deltaT;

	if (AppData::getInput().isKeyClicked("UP")) {
		testObj.getTransform()->y += 50.0f;
		testObj.getComponent<VisualComponent>()->setTexture("popcat");
	}
	else if (AppData::getInput().isKeyClicked("DOWN")) {
		testObj.getTransform()->y -= 50.0f;
		testObj.getComponent<VisualComponent>()->setTexture("sponge");
	}

	if (AppData::getInput().getWheelOffset() != 0.0f) {
		DTL_ENT("{0}", AppData::getInput().getWheelOffset());
	}

	if (AppData::getInput().isLeftMouseClicked()) {
		DTL_ENT("Hello!");
	}
	else if (AppData::getInput().isRightMousePressed()) {
		DTL_ENT("YOOOO");
	}

	AppData::getInput().setMousePosLock(AppData::getInput().isKeyPressed("SPACE"));

	if (AppData::getInput().isMouseLocked()) {
		auto [x, y] = AppData::getInput().getMouseOffset();
		if (x != 0 || y != 0) {
			DTL_ENT("{0}, {0}", x, y);
		}
	}
	else {
		if (AppData::getInput().isKeyClicked("V")) {
			AppData::getInput().toggleMouseVisibility();
		}
	}

	/////////////////////
	/// Utils showcase:
	/////////////////////

	timer += deltaT * 0.3f;
	if (timer >= 1) {
		timer = 0;
	}

	float t = -4 * (timer - 0.5f) * (timer - 0.5f) + 1;
	size = util::lerp(50.0f, 100.0f, sqrtf(t));

	testObj.getTransform()->setScale(size);

	/////////////////////
	/// Components in action
	/////////////////////

	for (auto& comp : comps) { // Iterowanie po Entity jest raczej nieoptymalne. Lepiej jest mieć listę komponentów danego typu i iterować po komponentach
		//if (spoing.hasComponent<BouncyComponent>()) {
		//	spoing.getComponent<BouncyComponent>()->updatePosition(deltaT); // No ale można
		//}
		comp.updatePosition(deltaT);
	}

}

void TestScene::render() {
	m_graphicsLayer.draw();
}

// ===============================
// LevelOneScene
// ===============================

LevelOneScene::LevelOneScene()
	: m_camera(0.f, 0.f, 1.f, 1.f, 1.f),
	m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {
	const float tempX = static_cast<float>(AppData::getWindow().getWindowSize().x);
	const float tempY = static_cast<float>(AppData::getWindow().getWindowSize().y);
	m_camera.setSize(tempX / tempY, 1.0f);

	wallA.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
	wallA.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
	wallA.getTransform()->setPos(0.3f, 0.0f);
	wallA.getTransform()->setScale(0.05f, 0.2f);

	wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
	wallB.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
	wallB.getTransform()->setPos(0.1f, 0.0f);
	wallB.getTransform()->setScale(0.05f, 0.2f);

}

void LevelOneScene::update([[maybe_unused]] float deltaT)
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

void LevelOneScene::render() { m_graphicsLayer.draw(); }

// ===============================
// LevelSelectionScene
// ===============================

LevelSelectionScene::LevelSelectionScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera)
{
	const uint tempX = AppData::getWindow().getWindowSize().x;
	const uint tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize(static_cast<float>(tempX) / static_cast<float>(tempY), 1.0F);
}

void LevelSelectionScene::update([[maybe_unused]] float deltaT)
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
	m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera)
{
	const float tempX = static_cast<float>(AppData::getWindow().getWindowSize().x);
	const float tempY = static_cast<float>(AppData::getWindow().getWindowSize().y);
	m_camera.setSize(tempX / tempY, 1.0f);
}

void LevelTwoScene::update([[maybe_unused]] float deltaT)
{
	if (isFirstUpdate) {
		DTL_INF("level two scene -- click q to quit, r to play again, w to win");
		isFirstUpdate = false;
	}
	//quit
	if (AppData::getInput().isKeyClicked("Q")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
		AppData::getSceneManager().nextScene();
	}
	//play again
	if (AppData::getInput().isKeyClicked("R")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelTwoScene()));
		AppData::getSceneManager().nextScene();
	}

	//won
	if (AppData::getInput().isKeyClicked("W")) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new ResultsScene(100, 2)));
		AppData::getSceneManager().nextScene();
	}
}

void LevelTwoScene::render()
{
	m_graphicsLayer.draw();
}

ResultsScene::ResultsScene(int score, int lvlNumber)
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera), playerScore(score), finishedLevelNumber(lvlNumber)
{
	const float tempX = static_cast<float>(AppData::getWindow().getWindowSize().x);
	const float tempY = static_cast<float>(AppData::getWindow().getWindowSize().y);
	m_camera.setSize(tempX / tempY, 1.0f);
}

void ResultsScene::update([[maybe_unused]] float deltaT)
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
		startLevel(finishedLevelNumber + 1);
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

//NOLINTEND

} // namespace golf
