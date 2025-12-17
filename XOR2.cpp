#include "XOR2.h"
#include "Gate.h"

XOR2::XOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(2, r_FanOut)
{
    m_GfxInfo = r_GfxInfo;
}

XOR2::XOR2(const GraphicsInfo& r_GfxInfo) : Gate(2, 5)
{
    m_GfxInfo = r_GfxInfo;
}

void XOR2::Operate()
{
    int a = GetInputPinStatus(1);
    int b = GetInputPinStatus(2);
    m_OutputPin.setStatus((a != b) ? HIGH : LOW);
}

void XOR2::Draw(Output* pOut)
{
    pOut->DrawXOR2(m_GfxInfo, IsSelected());
}

int XOR2::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

int XOR2::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();
}

void XOR2::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}

Component* XOR2::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng = {};
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new XOR2(ng);
}

string XOR2::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    string label = GetLabel();
    if (label.empty()) label = "XOR2";
    return "Type: XOR2, Label: " + label + ", Center: (" + to_string(cx) + "," + to_string(cy) + ")";
}
