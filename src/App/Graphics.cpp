#include "Graphics.h"
#include "App/Core/AppData.h"
#include "dtl.h"

#include <memory>

namespace golf 
{	
	VisualComponent::VisualComponent(agl::GraphicLayer* graphicLayer) : m_ID(graphicLayer->newQuad()), m_GL(graphicLayer) {}
	
	void VisualComponent::onKill() { m_GL->removeObject(m_ID); }

	void VisualComponent::onOwnerSet([[maybe_unused]]Entity *entity) {
		auto* trans = getTransform();
		auto* quad = m_GL->getQuadPtr(m_ID);
		quad->setPosPtr(&trans->x, &trans->y);
		quad->setScalePtr(&trans->xScale, &trans->yScale);
		quad->setRotationPtr(&trans->rot);
	}

	void VisualComponent::setTexture(const std::string& name) {
		m_GL->getQuadPtr(m_ID)->setVisual(AppData::getSus().GetTexture(name));
	}
	
	void VisualComponent::setAnimation([[maybe_unused]] const std::string& name) {}
	
	void VisualComponent::setColor(uchar r, uchar g, uchar b, uchar a) { m_GL->getQuadPtr(m_ID)->setColor(r, g, b, a); }
	
	void VisualComponent::setColor(Color color) { m_GL->getQuadPtr(m_ID)->setColor(color); };
}
