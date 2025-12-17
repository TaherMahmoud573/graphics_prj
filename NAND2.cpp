#include "NAND2.h"
#include "Gate.h"

// Constructor with GraphicsInfo and FanOut
NAND2::NAND2(const GraphicsInfo& r_GfxInfo, int r_FanOut)
    : Gate(2, r_FanOut) // 2-input NAND gate
{
    m_GfxInfo = r_GfxInfo;
}

// Optionally, if you have a constructor with only GraphicsInfo
NAND2::NAND2(const GraphicsInfo& r_GfxInfo)
    : Gate(2, 1) // Default fan-out to 1 if not specified
{
    m_GfxInfo = r_GfxInfo;
}


void NAND2::Operate()
{
	//caclulate the output status as the NANDing of the two input pins

	//Add you code here

	if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == HIGH)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}


// Function Draw
// Draws 2-input AND gate
void NAND2::Draw(Output* pOut)
{
	// pass selection state
	pOut->DrawNAND2(m_GfxInfo, IsSelected());
}

//returns status of outputpin
int NAND2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NAND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin to HIGH or LOW
void NAND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

string NAND2::GetInfo() const
{
    int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
    int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
    string label = GetLabel();
    if (label.empty()) label = "NAND2";
    return "Type: NAND2, Label: " + label + ", Center: (" + to_string(cx) + "," + to_string(cy) + ")";
}

Component* NAND2::Clone(Point P) const
{
    GraphicsInfo g = GetParameters();
    int w = g.x2 - g.x1;
    int h = g.y2 - g.y1;
    GraphicsInfo ng = {};
    ng.x1 = P.x - w / 2;
    ng.y1 = P.y - h / 2;
    ng.x2 = ng.x1 + w;
    ng.y2 = ng.y1 + h;
    return new NAND2(ng);
}
