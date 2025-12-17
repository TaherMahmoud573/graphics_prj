#include "INV.h"
#include "Gate.h"
#include <string>

// Constructor with fanout (already present)
INV::INV(const GraphicsInfo &r_GfxInfo, int r_FanOut) : Gate(1, r_FanOut)
{
    m_GfxInfo = r_GfxInfo;
}

// Single-argument constructor required by callers (e.g. Clone)
INV::INV(const GraphicsInfo& r_GfxInfo) : Gate(1, INV_FANOUT)
{
    m_GfxInfo = r_GfxInfo;
}

void INV::Operate()
{
    if (GetInputPinStatus(1) == HIGH)
        m_OutputPin.setStatus(LOW);
    else
        m_OutputPin.setStatus(HIGH);
}

void INV::Draw(Output* pOut)
{
    pOut->DrawINV(m_GfxInfo, IsSelected());
}

int INV::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

int INV::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();
}

void INV::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}

// Provide the pin accessors declared in the header
OutputPin* INV::GetOutputPin()
{
    return &m_OutputPin;
}

InputPin* INV::GetInputPin()
{
    return m_InputPins;
}

Component* INV::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng;
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new INV(ng);
}

std::string INV::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    std::string label = GetLabel();
    if (label.empty()) label = "INV";
    return "Type: INV, Label: " + label + ", Center: (" + std::to_string(cx) + "," + std::to_string(cy) + ")";
}
