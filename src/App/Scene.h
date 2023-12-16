// Scene.h 
//
// Jeszcze nie wiem co to będzie

#pragma once

namespace golf {


class Scene {
public:
	Scene();
	Scene(Scene &&) = default;
	Scene(const Scene &) = default;
	Scene &operator=(Scene &&) = default;
	Scene &operator=(const Scene &) = default;
	~Scene();

private:
	
};


}
