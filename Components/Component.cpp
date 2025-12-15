#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
}

Component::Component()
{}

GraphicsInfo Component::GetGraphicsInfo() const         //New
{
	return m_GfxInfo;
}

Component::~Component()
{}

