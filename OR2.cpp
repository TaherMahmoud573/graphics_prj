#include "OR2.h"
#include "Gate.h"

OR2::OR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(2, r_FanOut)
{
    m_GfxInfo = r_GfxInfo;
}

// Single-argument constructor added to match calls that pass only GraphicsInfo.
// Choose a reasonable default fan-out (1 here). Adjust if your project expects a different default.
OR2::OR2(const GraphicsInfo& r_GfxInfo)
    : Gate(2, 5) // default fan-out
{
    m_GfxInfo = r_GfxInfo;
}


void OR2::Operate()
{
    if (GetInputPinStatus(1) == HIGH || GetInputPinStatus(2) == HIGH)
        m_OutputPin.setStatus(HIGH);
    else
        m_OutputPin.setStatus(LOW);
}

// Function Draw
// Draws 2-input OR gate
void OR2::Draw(Output* pOut)
{
    pOut->DrawOR2(m_GfxInfo, IsSelected());
}

//returns status of outputpin
int OR2::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int OR2::GetInputPinStatus(int n)
{
    return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin to HIGH or LOW
void OR2::setInputPinStatus(int n, STATUS s)
{
    m_InputPins[n - 1].setStatus(s);
}

Component* OR2::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng = {};
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new OR2(ng);
}

string OR2::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    string label = GetLabel();
    if (label.empty()) label = "OR2";
    return "Type: OR2, Label: " + label + ", Center: (" + to_string(cx) + "," + to_string(cy) + ")";
}
