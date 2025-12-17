#include "Buff.h"
#include <string>

using namespace std;

BUFF::BUFF(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void BUFF::Operate()
{
	//caclulate the output status as the BUFFing of the One input pin

	//Add you code here

	if (GetInputPinStatus(1) == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 1-input BUFF gate
void BUFF::Draw(Output* pOut)
{
	// pass selection state
	pOut->DrawBUFF(m_GfxInfo, IsSelected());
}

//returns status of outputpin
int BUFF::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int BUFF::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin to HIGH or LOW
void BUFF::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

string BUFF::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    string label = GetLabel();
    if (label.empty()) label = "BUFF";
    return "Type: BUFF, Label: " + label + ", Center: (" + to_string(cx) + "," + to_string(cy) + ")";
}

Component* BUFF::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng;
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new BUFF(ng);
}