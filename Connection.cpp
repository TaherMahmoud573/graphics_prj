#include "Connection.h"
#include "../GUI/Output.h"
#include <string>

// Constructor
Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin, InputPin *pDstPin)
	: Component(r_GfxInfo), SrcPin(pSrcPin), DstPin(pDstPin)
{
	// Associate pins with this connection where appropriate
	if (DstPin)
		DstPin->setComponent(this);
	
}

// Propagate source output status to the destination input pin
void Connection::Operate()
{
	if (SrcPin && DstPin) {
		STATUS s = SrcPin->getStatus();
		DstPin->setStatus(s);
	}
}

// Draw the connection using the Output interface. Use selection state to highlight.
void Connection::Draw(Output* pOut)
{
	if (!pOut) return;
	// DrawConnection accepts a selected flag; forward current selection state
	pOut->DrawConnection(m_GfxInfo, IsSelected());
}

// Setters for pins
void Connection::setSourcePin(OutputPin *pSrcPin)
{
	SrcPin = pSrcPin;
}

void Connection::setDestPin(InputPin *pDstPin)
{
	DstPin = pDstPin;
	if (DstPin)
		DstPin->setComponent(this);
}

// Accessors for pins
OutputPin* Connection::GetOutputPin()
{
	return SrcPin;
}

InputPin* Connection::GetInputPin()
{
	return DstPin;
}

OutputPin* Connection::getSourcePin() const
{
	return SrcPin;
}

InputPin* Connection::getDestPin() const
{
	return DstPin;
}

// Status helpers
int Connection::GetOutPinStatus()
{
	if (SrcPin)
		return static_cast<int>(SrcPin->getStatus());
	return -1;
}

int Connection::GetInputPinStatus(int /*n*/)
{
	if (DstPin)
		return static_cast<int>(DstPin->getStatus());
	return -1;
}

void Connection::setInputPinStatus(int /*n*/, STATUS s)
{
	// set status on destination pin
	if (DstPin)
		DstPin->setStatus(s);
}

std::string Connection::GetInfo() const
{
	int x1 = m_GfxInfo.x1;
	int y1 = m_GfxInfo.y1;
	int x2 = m_GfxInfo.x2;
	int y2 = m_GfxInfo.y2;
	std::string label = GetLabel();
	if (label.empty()) label = "Connection";
	return "Type: Connection, Label: " + label + ", From: (" + std::to_string(x1) + "," + std::to_string(y1) + ") To: (" + std::to_string(x2) + "," + std::to_string(y2) + ")";
}

// Move connection endpoints by dx,dy (used when moving an entire connection)
void Connection::Move(int dx, int dy)
{
	m_GfxInfo.x1 += dx;
	m_GfxInfo.x2 += dx;
	m_GfxInfo.y1 += dy;
	m_GfxInfo.y2 += dy;
}

Point Connection::GetCenter() const
{
	Point c = { 0, 0 };
	c.x = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
	c.y = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
	return c;
}

// Cloning a connection requires resolving pins in the new context.
// Return nullptr to indicate a connection should not be cloned by generic paste.
Component* Connection::Clone(Point) const
{
	return nullptr;
}
