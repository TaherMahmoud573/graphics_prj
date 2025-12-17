#include "XOR3.h"
#include "Gate.h"

XOR3::XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(3, r_FanOut)
{
    m_GfxInfo = r_GfxInfo;
}

void XOR3::Operate()
{
    int ones = (GetInputPinStatus(1) == HIGH) + (GetInputPinStatus(2) == HIGH) + (GetInputPinStatus(3) == HIGH);
    m_OutputPin.setStatus((ones % 2) ? HIGH : LOW);
}

// Function Draw
// Draws 3-input XOR gate
void XOR3::Draw(Output* pOut)
{
    //Call output class and pass gate drawing info to it.
    pOut->DrawXOR3(m_GfxInfo, IsSelected());
}

//returns status of outputpin
int XOR3::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin to HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}

Component* XOR3::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng = {};
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    // Pass the correct fan-out value (use the current gate's fan-out)
    return new XOR3(ng, m_OutputPin.GetFanOut());
}

string XOR3::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    string label = GetLabel();
    if (label.empty()) label = "XOR3";
    return "Type: XOR3, Label: " + label + ", Center: (" + to_string(cx) + "," + to_string(cy) + ")";
}

// Function definition for IsInside
bool XOR3::IsInside(Point P) const
{
   
    // Assuming m_GfxInfo has Points x1, y1 top-left and x2, y2 bottom-right
    return (P.x >= m_GfxInfo.x1 && P.x <= m_GfxInfo.x2 &&
            P.y >= m_GfxInfo.y1 && P.y <= m_GfxInfo.y2);
}