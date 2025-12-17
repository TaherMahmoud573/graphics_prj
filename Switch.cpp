#include "Switch.h"
#include "../GUI/Output.h"
#include <string>

Switch::Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut)
    : Gate(0, r_FanOut) // switch has no inputs, only an output pin with given fanout
{
    m_GfxInfo = r_GfxInfo;
    m_OutputPin.setStatus(LOW); // default state OFF
}

Switch::Switch(const GraphicsInfo& r_GfxInfo)
    : Gate(0, Switch_FANOUT) // default fanout from Defs.H
{
    m_GfxInfo = r_GfxInfo;
    m_OutputPin.setStatus(LOW);
}

void Switch::Operate()
{
    // Output is controlled externally (Change Switch action); nothing to compute here.
}

void Switch::Draw(Output* pOut)
{
    pOut->DrawSwitch(m_GfxInfo, IsSelected());
}

int Switch::GetOutPinStatus()
{
    return static_cast<int>(m_OutputPin.getStatus());
}

int Switch::GetInputPinStatus(int /*n*/)
{
    // Switch has no input pins
    return -1;
}

void Switch::setInputPinStatus(int /*n*/, STATUS /*s*/)
{
    // no-op; switch has no input pins
}

Component* Switch::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng = {};
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new Switch(ng);
}

std::string Switch::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    std::string label = GetLabel();
    if (label.empty()) label = "Switch";
    // Cast away constness to call non-const getStatus()
    std::string state = (const_cast<OutputPin&>(m_OutputPin).getStatus() == HIGH) ? "ON" : "OFF";
    return "Type: Switch, Label: " + label + ", Center: (" + std::to_string(cx) + "," + std::to_string(cy) + "), State: " + state;
}
