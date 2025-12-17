#include "Component.h"

Component::Component() : m_Label(""), Selected(false)
{
    m_GfxInfo.x1 = m_GfxInfo.y1 = m_GfxInfo.x2 = m_GfxInfo.y2 = 0;
}

Component::Component(const GraphicsInfo& r_GfxInfo) : m_Label(""), m_GfxInfo(r_GfxInfo), Selected(false)
{
}

void Component::SetSelected(bool s) { Selected = s; }
bool Component::IsSelected() const { return Selected; }

void Component::Move(int dx, int dy)
{
    m_GfxInfo.x1 += dx;
    m_GfxInfo.x2 += dx;
    m_GfxInfo.y1 += dy;
    m_GfxInfo.y2 += dy;
}

Point Component::GetCenter() const
{
    Point c = {0, 0};
    c.x = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    c.y = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    return c;
}

string Component::GetLabel() const
{
    return m_Label;
}

bool Component::IsInside(Point P) const
{
    return (P.x >= m_GfxInfo.x1 && P.x <= m_GfxInfo.x2 &&
            P.y >= m_GfxInfo.y1 && P.y <= m_GfxInfo.y2);
}

Component::~Component() {}