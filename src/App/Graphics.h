#pragma once

#include "Agl.h"
#include "ECS/Component.h"

namespace golf {

class TextureComponent;

class GraphicsLayer {
public:
	GraphicsLayer(agl::Shader& shader, agl::Camera& camera);

	std::shared_ptr<TextureComponent> addTexComponent();

	void render();

private:
	// Niestety nie potrafiłem zrobić z tego std::vector<TextureComponent> - dostawałem najbardziej dzikie seg faulty w egzystencji
	std::vector<std::shared_ptr<TextureComponent>> m_texturedObjects;
	agl::GraphicLayer m_aglLayer;
	
};

class TextureComponent : public Component {
public:
	TextureComponent();

	void kill() override;
	void setTexture(const std::string& name);

private:
	void resync();

	agl::Object m_renderObject;

	friend class GraphicsLayer;
};


}
