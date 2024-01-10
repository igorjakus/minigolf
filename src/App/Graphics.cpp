#include "Graphics.h"
#include "App/Core/AppData.h"
#include "dtl.h"

#include <memory>

namespace golf 
{	
	VisualComponent::VisualComponent(agl::GraphicLayer& graphicLayer) : m_quad(graphicLayer.newQuad()) {}
	
	void VisualComponent::onOwnerSet([[maybe_unused]]Entity *entity) {
		auto* trans = getTransform();
		m_quad->setPosPtr(&trans->x, &trans->y);
		m_quad->setScalePtr(&trans->xScale, &trans->yScale);
		m_quad->setRotationPtr(&trans->rot);
	}

	void VisualComponent::setTexture(const std::string& name) {
		m_quad->setVisual(AppData::getSus().GetTexture(name));
	}
	
	void VisualComponent::setAnimation([[maybe_unused]] const std::string& name) {}
	
	void VisualComponent::setColor(uchar red, uchar green, uchar blue, uchar alpha) { m_quad->setColor(red, green, blue, alpha); }
	
	void VisualComponent::setColor(Color color) { m_quad->setColor(color); };
}
