// Scenes.h 
//
// This header contains all scene class declarations

#pragma once

#include "Scene.h"

namespace golf {


class BlankScene : Scene {
public:
	BlankScene();
	BlankScene(BlankScene &&) = default;
	BlankScene(const BlankScene &) = default;
	BlankScene &operator=(BlankScene &&) = default;
	BlankScene &operator=(const BlankScene &) = default;
	~BlankScene() override;

	// handleInput() override;
	void update(float deltaT) override;
	void render() override;

	void load() override;

private:
	
};



}
