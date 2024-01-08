#include "Graphics.h"
#include "App/Core/AppData.h"
#include "dtl.h"

#include <memory>

namespace golf 
{	
	VisualComponent::VisualComponent(agl::GraphicLayer& graphicLayer) { m_quad = graphicLayer.newQuad(); }
	
	void VisualComponent::setOwner(Entity *entity) {
		Component::setOwner(entity);
		auto trans = getTransform();
		m_quad->setPosPtr(&trans->x, &trans->y);
		m_quad->setScalePtr(&trans->xScale, &trans->yScale);
		m_quad->setRotationPtr(&trans->rot);
	}
	VisualComponent::~VisualComponent()
	{
		DTL_ENT("Vis destroyed");
	}

	void VisualComponent::setTexture(const std::string& name) { m_quad->setVisual(AppData::getSus().GetTexture(name)); }
	
	void VisualComponent::setAnimation([[maybe_unused]] const std::string& name) {/*todo animacje, jak bedzie w nich wspracie w susie*/ }
	
	void VisualComponent::setColor(uchar r, uchar g, uchar b, uchar a) { m_quad->setColor(r, g, b, a); }
	
	void VisualComponent::setColor(Color color) { m_quad->setColor(color); };
}
