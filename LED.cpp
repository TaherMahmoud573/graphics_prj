#include "LED.h"
#include "../GUI/Output.h"
#include <string>

using namespace std;

// Primary constructor: initialize base Component using initializer list
LED::LED(const GraphicsInfo& r_GfxInfo)
	: Component(r_GfxInfo)
{
	// Associate the input pin with this component and initialize status
	m_InputPin.setComponent(this);
	m_InputPin.setStatus(LOW);
}

// Overload that accepts a fan-out argument to match places that call new LED(ng, fanout)

LED::LED(const GraphicsInfo& r_GfxInfo, int /*r_FanOut*/)
	: Component(r_GfxInfo)
{
	m_InputPin.setComponent(this);
	m_InputPin.setStatus(LOW);
}

void LED::Operate()
{
	// LED does not compute outputs
}

void LED::Draw(Output* pOut)
{
	// pass selection state
	pOut->DrawLED(m_GfxInfo, IsSelected());
}

// LED has no output pin
int LED::GetOutPinStatus()
{
	return -1;
}

// Return status of the single input pin (n is 1-based)
int LED::GetInputPinStatus(int n)
{
	if (n == 1)
		return m_InputPin.getStatus();
	return -1;
}

void LED::setInputPinStatus(int n, STATUS s)
{
	if (n == 1)
		m_InputPin.setStatus(s);
}

// Component interface - LED has no OutputPin
OutputPin* LED::GetOutputPin()
{
	return nullptr;
}

// Return pointer to the LED's input pin
InputPin* LED::GetInputPin()
{
	return &m_InputPin;
}

Component* LED::Clone(Point P) const
{
	GraphicsInfo g = GetParameters();
	int w = g.x2 - g.x1;
	int h = g.y2 - g.y1;
	GraphicsInfo ng = {};
	ng.x1 = P.x - w / 2;
	ng.y1 = P.y - h / 2;
	ng.x2 = ng.x1 + w;
	ng.y2 = ng.y1 + h;
	return new LED(ng);
}

string LED::GetInfo() const
{
	int cx = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
	int cy = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
	string label = GetLabel();
	if (label.empty()) label = "LED";
	return "Type: LED, Label: " + label + ", Center: (" + to_string(cx) + "," + to_string(cy) + ")";
}
