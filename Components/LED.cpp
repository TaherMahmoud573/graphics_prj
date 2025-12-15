#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	ledState = LOW;
}


void LED::Operate()
{
	//caclulate the output of the LED
	/*if (ledState == LOW)
		{
		m_OutputPin.setStatus(LOW);
	}
	else {
		m_OutputPin.setStatus(HIGH);
	}
	//Add you code here*/

	if (m_InputPins[0].getStatus() == HIGH) {
		ledState = HIGH;
		m_OutputPin.setStatus(HIGH);
	}
	else {
		ledState = LOW;
		m_OutputPin.setStatus(LOW);
	}
}


// Function Draw
// Draws LED
void LED::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	//if (ledState == HIGH && UI.AppMode == SIMULATION)
	//	pOut->DrawLED(m_GfxInfo, (ledState == HIGH), false);
	//else
	//	pOut->DrawLED(m_GfxInfo, (ledState == HIGH), false);

	pOut->DrawLED(m_GfxInfo, (ledState == HIGH), false);
}

//returns status of outputpin
int LED::GetOutPinStatus()
{
	return -1;
}


//returns status of Inputpin #n
int LED::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin to HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void LED::UpdateLedState()
{
	if (m_InputPins[0].getStatus() == HIGH) {
		ledState = HIGH;
	}
	else {
		ledState = LOW;
	}
}
