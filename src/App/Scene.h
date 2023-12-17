// Scene.h 
//
// Jeszcze nie wiem co to będzie

#pragma once



namespace golf {


class Scene {

public:
	virtual ~Scene() = default;
	Scene(const Scene &) = default;
	Scene(Scene &&) = default;
	Scene &operator=(const Scene &) = default;
	Scene &operator=(Scene &&) = default;

	// handleInput();
	virtual void update(float deltaT);
	virtual void render();

	virtual void load();

};


}
