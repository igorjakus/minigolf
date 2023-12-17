// Scene.h 
//
// Jeszcze nie wiem co to będzie

#pragma once



namespace golf {


class Scene {

public:
	Scene() = default;
	virtual ~Scene() = default;
	Scene(const Scene &) = default;
	Scene(Scene &&) = default;
	Scene &operator=(const Scene &) = default;
	Scene &operator=(Scene &&) = default;

	// handleInput() = 0;
	virtual void update(float deltaT) = 0;
	virtual void render() = 0;

	virtual void load() = 0;


};


}
