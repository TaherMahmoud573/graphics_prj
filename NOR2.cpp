#include "NOR2.h"
#include <string>

using namespace std;

NOR2::NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut)
    : Gate(2, r_FanOut)
{
    m_GfxInfo.x1 = r_GfxInfo.x1;
    m_GfxInfo.y1 = r_GfxInfo.y1;
    m_GfxInfo.x2 = r_GfxInfo.x2;
    m_GfxInfo.y2 = r_GfxInfo.y2;
}

NOR2::NOR2(const GraphicsInfo &r_GfxInfo)
    : Gate(2, 1) // default fan-out if not provided
{
    m_GfxInfo.x1 = r_GfxInfo.x1;
    m_GfxInfo.y1 = r_GfxInfo.y1;
    m_GfxInfo.x2 = r_GfxInfo.x2;
    m_GfxInfo.y2 = r_GfxInfo.y2;
}

void NOR2::Operate()
{
    // NOR = !(A || B)
    STATUS a = m_InputPins[0].getStatus();
    STATUS b = m_InputPins[1].getStatus();

    if (a == LOW && b == LOW)
        m_OutputPin.setStatus(HIGH);
    else
        m_OutputPin.setStatus(LOW);
}

void NOR2::Draw(Output* pOut)
{
    pOut->DrawNOR2(m_GfxInfo);
}

int NOR2::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

int NOR2::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();
}

void NOR2::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}

Component* NOR2::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng = {};
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new NOR2(ng, m_OutputPin.GetFanOut());
}

std::string NOR2::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    string label = GetLabel();
    if (label.empty()) label = "NOR2";
    return "Type: NOR2, Label: " + label + ", Center: (" + to_string(cx) + "," + to_string(cy) + ")";
}
