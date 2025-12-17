#include "NOR3.h"
#include "Gate.h"

// Constructor implementation for NOR3
NOR3::NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut)
    : Gate(3, r_FanOut) // 3-input NOR gate
{
    m_GfxInfo = r_GfxInfo;
    Selected = false;
}

// Define the constructor declared in the header
NOR3::NOR3(const GraphicsInfo& r_GfxInfo)
    : Gate(3, 1) // default fan-out = 1
{
    m_GfxInfo = r_GfxInfo;
    Selected = false;
}

void NOR3::Operate()
{
	//caclulate the output status as the NORing of the three input pins

	//Add you code here
	if (GetInputPinStatus(1) == LOW && GetInputPinStatus(2) == LOW && GetInputPinStatus(3) == LOW)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

// Clone
// Creates a clone of the current component
Component* NOR3::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng = {};
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new NOR3(ng, m_OutputPin.GetFanOut());
}

// Function Draw
// Draws 3-input XNOR gate
void NOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOR3(m_GfxInfo, IsSelected());
}

//returns status of outputpin
int NOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

//returns status of Inputpin #n
int NOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin to HIGH or LOW
void NOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

std::string NOR3::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    std::string label = GetLabel();
    if (label.empty()) label = "NOR3";
    return "Type: NOR3, Label: " + label + ", Center: (" + std::to_string(cx) + "," + std::to_string(cy) + ")";
}