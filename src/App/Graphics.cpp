#include <pch.h>
#include "Graphics.h"
#include "App/Core/AppData.h"
#include "dtl.h"

namespace golf  {	


std::shared_ptr<VisualComponent> VisualComponent::create(agl::GraphicLayer& graphicLayer) {
	return std::make_shared<VisualComponent>(&graphicLayer);
}

std::shared_ptr<VisualComponent> VisualComponent::create(agl::GraphicLayer* graphicLayer) {
	return std::make_shared<VisualComponent>(graphicLayer);
}

std::shared_ptr<VisualComponent> VisualComponent::create(GUILayer& gui) {
	return std::make_shared<VisualComponent>(&gui);
}

std::shared_ptr<VisualComponent> VisualComponent::create(GUILayer* gui) {
	return std::make_shared<VisualComponent>(gui);
}

VisualComponent::VisualComponent(agl::GraphicLayer* graphicLayer) 
	: m_ID(graphicLayer->newQuad()), m_GL(graphicLayer) {}

VisualComponent::VisualComponent(GUILayer* gui) 
	: m_ID(gui->getLayer()->newQuad()), m_GL(gui->getLayer()) {}

void VisualComponent::onKill() { m_GL->removeObject(m_ID); }

void VisualComponent::onOwnerSet([[maybe_unused]]Entity *entity) {
	auto* trans = getTransform();
	auto* quad = m_GL->getQuadPtr(m_ID);
	quad->setPosPtr(&trans->x, &trans->y);
	quad->setScalePtr(&trans->xScale, &trans->yScale);
	quad->setRotationPtr(&trans->rot);
}

	void VisualComponent::setTexture(const std::string& name) { m_GL->getQuadPtr(m_ID)->setVisual(AppData::getSus().GetTexture(name)); }
	
	void VisualComponent::setAnimation(const std::string& name) { m_GL->getQuadPtr(m_ID)->setVisual(AppData::getSus().GetAnimation(name)); }

	void VisualComponent::setMask(agl::TextureMask* mask) { m_GL->getQuadPtr(m_ID)->setMask(mask); }
	
	void VisualComponent::setColor(uchar red, uchar green, uchar blue, uchar alpha) { m_GL->getQuadPtr(m_ID)->setColor(red, green, blue, alpha); }
	
	void VisualComponent::setColor(Color color) { m_GL->getQuadPtr(m_ID)->setColor(color); }
	
	void VisualComponent::setTexRepeat(float defxScale, float defyScale) { m_GL->getQuadPtr(m_ID)->setTexRepeat(defxScale, defyScale); }

	void VisualComponent::setTexRepeat(float defScale) { m_GL->getQuadPtr(m_ID)->setTexRepeat(defScale, defScale); }
	
}
