#include "Background.h"

#include "Core/AppData.h"

namespace golf {

Background::Background()
	:m_camera(0, 0, 1.f, 1.f, 1.f), m_layer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {
	AppData::getInput().attachCamera(&m_camera, 1.f, true, true);

	m_image.addComponent<VisualComponent>(VisualComponent::create(m_layer));
	m_image.getComponent<VisualComponent>()->setTexture("bg");
	m_image.getComponent<VisualComponent>()->setColor(200, 255, 255, 200);
	m_image.getTransform()->setScale(1.5f, 1.f);
}

void Background::render() {
	m_layer.draw();
}

}
