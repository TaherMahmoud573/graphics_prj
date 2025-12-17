#include "AND2.h"
#include "Gate.h"

// Constructor with GraphicsInfo and FanOut
AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut)
    : Gate(2, r_FanOut) // 2-input AND gate
{
    m_GfxInfo = r_GfxInfo;
}

// Constructor with only GraphicsInfo parameter
AND2::AND2(const GraphicsInfo& r_GfxInfo)
    : Gate(2, 5) // 2 inputs, default fanout 5 (adjust as needed)
{
    m_GfxInfo = r_GfxInfo;
    // Any additional initialization if needed
}

// Calculates the output of the AND gate
void AND2::Operate()
{
	// Output is HIGH only if both inputs are HIGH
	if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

// Draws 2-input AND gate
void AND2::Draw(Output* pOut)
{
	// pass selection state so Output can draw highlight when selected
	pOut->DrawAND2(m_GfxInfo, IsSelected());
}

// returns status of output pin
int AND2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

// returns status of input pin #n
int AND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus(); // n starts from 1
}

// set status of an input pin to HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

string AND2::GetInfo() const
{
	int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
	int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
	string label = GetLabel();
	if (label.empty()) label = "AND2";
	return "Type: AND2, Label: " + label + ", Center: (" + to_string(cx) + "," + to_string(cy) + ")";
}

Component* AND2::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng = {};
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new AND2(ng);
}
