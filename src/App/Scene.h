// Scene.h 
//
// Klasa stanowiąca bazę dla wszystkich scen w aplikacji

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

	virtual void load() = 0;
	bool isLoaded();

protected:

	bool m_loaded = false;


};


}
