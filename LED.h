#ifndef _LED_H
#define _LED_H

/*
  Class LED
  ---------
  represent the LED component (one input pin, no output pin)
*/

#include "Component.h"
#include "InputPin.h"
#include "OutputPin.h"
#include <string>

class LED : public Component
{
private:
	// single input pin for the LED
	InputPin m_InputPin;

public:
	// Construct LED positioned using r_GfxInfo
	LED(const GraphicsInfo& r_GfxInfo);
	LED(const GraphicsInfo& r_GfxInfo, int r_FanOut); // overload to match callers that pass fanout

	// Core behavior
	virtual void Operate() override;	// LED has no internal operation
	virtual void Draw(Output* pOut) override;

	// Pin status accessors / mutators
	virtual int GetOutPinStatus() override;	// LED has no output -> return -1
	virtual int GetInputPinStatus(int n) override;
	virtual void setInputPinStatus(int n, STATUS s) override;

	// Provide access to pins (Component requires these)
	virtual OutputPin* GetOutputPin();	// returns nullptr for LED
	virtual InputPin* GetInputPin();

	// Component metadata
	virtual std::string GetInfo() const override;

	// Cloning
	virtual Component* Clone(Point P) const override;
};

#endif