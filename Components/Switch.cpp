#include "Switch.h"
#include "..\GUI\Output.h" // needed for immediate redraw and UI check

Switch::Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(0, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	switchState = LOW;
}


void Switch::Operate()
{
	//calculate the output status of the Switch
	m_OutputPin.setStatus(switchState);
}


// Function Draw
// Draws Switch
void Switch::Draw(Output* pOut)
{
	pOut->DrawSwitch(m_GfxInfo, (switchState == HIGH), false);
}

//returns status of outputpin
int Switch::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int Switch::GetInputPinStatus(int n)
{
	return -1;	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin to HIGH or LOW
void Switch::setInputPinStatus(int n, STATUS s)
{
}

void Switch::Toggle(Output* pOut)
{
    // Flip state and update its output pin
    if (switchState == LOW) {
        switchState = HIGH;
        m_OutputPin.setStatus(HIGH);
    }
    else {
        switchState = LOW;
        m_OutputPin.setStatus(LOW);
    }

    if (pOut)
    {
        pOut->DrawSwitch(m_GfxInfo, (switchState == HIGH), false);
    }
}
