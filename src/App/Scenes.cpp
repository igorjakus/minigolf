#include "Scenes.h"
#include "Core/AppData.h"
#include "ECS/Entity.h"
#include "Graphics.h"

#include "Agl.h"

#include <cmath>
#include <cstdlib>
#include <memory>
#include <utility>
#include "Util.hpp"

//Temp:
//NOLINTBEGIN


namespace golf {

// ===============================
// BlankScene
// ===============================

BlankScene::BlankScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F), 
	 m_graphicsLayer(AppData::getGlobalShader(), m_camera) {

	m_kot.addComponent<TextureComponent>(m_graphicsLayer.addTexComponent());
	m_kot.getComponent<TextureComponent>()->setTexture("popcat.png");

	m_kot.getTransform()->setScale(0.5f);
}

void BlankScene::update(float deltaT) {
	timer += deltaT;

	if (timer > 1.0f && timer < 1.01f && m_kot.hasComponent<TextureComponent>()) {
		m_kot.removeComponent<TextureComponent>();
	}

	if (timer > 3.0f) {
		AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new TestScene()));
		AppData::getSceneManager().nextScene();
	}
}

void BlankScene::render() {
	m_graphicsLayer.render();
}


// ===============================
// TestScene
// ===============================

// Przykładowy "skrypt"
class BouncyComponent : public Component {
public:

	void setVelocity(std::pair<float, float> vel) {
		velocity = vel;
	}
	void setBoundaries(float min1, float max1,float min2, float max2) {
		minX = min1; maxX = max1; minY = min2; maxY = max2;
	}

	void updatePosition(float deltaT) {
		float& x = getTransform()->x;
		float& y = getTransform()->y;
		// uwaga! nie mamy pewności że transform istnieje! (getTransform zwróci pusty shared_ptr jeśli nie ma właściciela (przypisanego Entity))
		x += velocity.first * deltaT;
		y += velocity.second * deltaT;
		if(x < minX || x > maxX) {
			velocity.first *= -1;
			x = util::clamp(minX, maxX, x);
			if(getOwner()->hasComponent<TextureComponent>()) { // again powinniśmy się upewniać że komponent do którego chcemy się odwołać wgl istnieje
				getOwner()->getComponent<TextureComponent>()->setTexture("popcat.png");
			}
			kill();
			return; // po kill() nie powinniśmy już pracować nad komponentem
		}
		if(y < minY || y > maxY) {
			velocity.second *= -1;
			y = util::clamp(minX, maxX, y);
		}
	}

private:
	std::pair<float, float> velocity;
	float minX, maxX, minY, maxY;
};

TestScene::TestScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(AppData::getGlobalShader(), m_camera) {

	size = 50.0f;
	timer = .0f;

	const float tempX = static_cast<float>(AppData::getWindow().getWindowSize().x);
	const float tempY = static_cast<float>(AppData::getWindow().getWindowSize().y);
	m_camera.setSize(tempX, tempY);

	std::shared_ptr<TextureComponent> graphics = m_graphicsLayer.addTexComponent();
	// Niby można też graphics = std::make_shared<TextureComponent>(); tylko że wtedy ten komponent 
	// nie będzie przypisany do żadnej warstwy graficznej i tym samym nie będzie się wyświetlać
	testObj.addComponent<TextureComponent>(graphics);
	// Można też bezpośrednio wrzucić wynik m_graphicsLayer.addTexComponent() do addComponent() czyli:
	// testObj.addComponent<TextureComponent>(m_graphicsLayer.addTexComponent()); jednak wtedy nie 
	// mamy bezpośredniego wskaźnika na ten komponent i musimy go szukać chcąc z nim coś robić.
	testObj.getComponent<TextureComponent>()->setTexture("popcat.png");
	// Jeżeli mamy nasz pointer "graphics" to możemy po prostu:
	// graphics->setTexture("popcat.png");
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
	for(uint i = 0; i < spoingCount; i ++) {
		std::shared_ptr<TextureComponent> tex = m_graphicsLayer.addTexComponent(); // Tworzymy komponent tex
		someSpoingbobs[i].addComponent<TextureComponent>(tex); // przypisujemy właściciela komponentu
		tex->setTexture("sponge.png"); // ustawiamy komponentowi tex texturę jaką ma trzymać

		std::shared_ptr<BouncyComponent> bounce = std::make_shared<BouncyComponent>(); // Tworzymy komponent bounce (który w sumie jest skryptem)
		bounce->setVelocity({rand() % 300 * (i % 2 == 0 ? 1 : -1), rand() % 500 * (i % 3 == 0 ? 1 : -1)}); // nadajemy mu jakieś właściwości (losowe)
		bounce->setBoundaries((tempX - spoingSize) / -2, (tempX - spoingSize) / 2, (tempY - spoingSize) / -2, (tempY - spoingSize) / 2);
		someSpoingbobs[i].addComponent<BouncyComponent>(bounce); // przypisujemy właściciela komponentu

		someSpoingbobs[i].getTransform()->setScale(spoingSize); // na koniec zmieniamy skalę każdego entity
	}

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
	testObj.getTransform()->x += speed * deltaT;

	if(AppData::getInput().isKeyClicked("UP")) {
		testObj.getTransform()->y += 50.0f;
		testObj.getComponent<TextureComponent>()->setTexture("popcat.png");
	} else if(AppData::getInput().isKeyClicked("DOWN")) {
		testObj.getTransform()->y -= 50.0f;
		testObj.getComponent<TextureComponent>()->setTexture("sponge.png");
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

	/////////////////////
	/// Utils showcase:
	/////////////////////

	timer += deltaT * 0.3f;
	if(timer >= 1) {
		timer = 0;
	}

	float t = -4 * (timer - 0.5f) * (timer - 0.5f) + 1;
	size = util::lerp(50.0f, 100.0f, sqrtf(t));

	testObj.getTransform()->setScale(size);

	/////////////////////
	/// Components in action
	/////////////////////
	
	for(auto spoing : someSpoingbobs) { // Iterowanie po Entity jest raczej nieoptymalne. Lepiej jest mieć listę komponentów danego typu i iterować po komponentach
		if(spoing.hasComponent<BouncyComponent>()) {
			spoing.getComponent<BouncyComponent>()->updatePosition(deltaT);
		}
	}

}

void TestScene::render() {
	m_graphicsLayer.render();
}


// ===============================
// LevelOneScene
// ===============================

LevelOneScene::LevelOneScene()
	:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
	m_graphicsLayer(AppData::getGlobalShader(), m_camera)
{
	const uint tempX = AppData::getWindow().getWindowSize().x;
	const uint tempY = AppData::getWindow().getWindowSize().y;
	m_camera.setSize(static_cast<float>(tempX) / static_cast<float>(tempY), 1.0F);
	WallA = std::make_unique<agl::Object>(agl::Object(0.01f, 0.1f, { -0.5f, 0 } ));
	WallB = std::make_unique<agl::Object>(agl::Object(0.01f, 0.1f, { 0, 0 }));
	WallA->setTexture(*AppData::getSus().GetTexture("sponge.png"));
	WallB->setTexture(*AppData::getSus().GetTexture("sponge.png"));
	m_graphicsLayer.addObject(*WallA);
	m_graphicsLayer.addObject(*WallB);
}

void LevelOneScene::update([[maybe_unused]] float deltaT)
{
	
}

void LevelOneScene::render()
{
	m_graphicsLayer.draw();
}

//NOLINTEND


}
