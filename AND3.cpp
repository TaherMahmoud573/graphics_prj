#include "AND3.h"
#include "Gate.h"

AND3::AND3(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(3, r_FanOut)
{
    m_GfxInfo = r_GfxInfo;
}

void AND3::Operate()
{
    if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == HIGH && GetInputPinStatus(3) == HIGH)
        m_OutputPin.setStatus(HIGH);
    else
        m_OutputPin.setStatus(LOW);
}

void AND3::Draw(Output* pOut)
{
    pOut->DrawAND3(m_GfxInfo, IsSelected());
}

int AND3::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

int AND3::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();
}

void AND3::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}

Component* AND3::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng = {};   
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new AND3(ng);
}

string AND3::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    string label = GetLabel();
    if (label.empty()) label = "AND3";
    return "Type: AND3, Label: " + label + ", Center: (" + to_string(cx) + "," + to_string(cy) + ")";
}
