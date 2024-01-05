// Scene.h 
//
// A virtual class that makes a base for all scenes in the game

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

	virtual void update(float deltaT) = 0;
	virtual void render() = 0;

};


}
