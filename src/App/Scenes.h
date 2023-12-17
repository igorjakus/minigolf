// Scenes.h 
//
// This header contains all scene class declarations

#pragma once

#include "Agl.h"
#include "Scene.h"

namespace golf {


class BlankScene : public Scene {

public:
	BlankScene();
	~BlankScene() override = default;
	BlankScene(BlankScene &&) = delete;
	BlankScene(const BlankScene &);
	BlankScene &operator=(BlankScene &&) = delete;
	BlankScene &operator=(const BlankScene &) = delete;

	// handleInput() override;
	void update(float deltaT) override;
	void render() override;

	void load() override;

private:
	agl::Shader m_shader;
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	// TEMP
	std::unique_ptr<agl::Object> testObj;
	std::unique_ptr<agl::Texture> testTex;
	
};



}
