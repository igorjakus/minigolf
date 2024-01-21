// Scene.h 
//
// A virtual class that makes a base for all scenes in the game

#pragma once


namespace golf {


class Scene : public std::enable_shared_from_this<Scene> {

public:
	Scene();
	virtual ~Scene() = default;
	Scene(const Scene &) = delete;
	Scene(Scene &&) = delete;
	Scene &operator=(const Scene &) = delete;
	Scene &operator=(Scene &&) = delete;

	virtual void update(float deltaT) = 0;
	virtual void render() = 0;

	uint64_t getCameraSetID();

private:
	uint64_t m_cameraSetID;

};


}
