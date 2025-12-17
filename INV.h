#ifndef _INV_H
#define _INV_H

/*
  Class AND2
  -----------
  represent the 1-input INV gate
*/

#include "Gate.h"

class INV : public Gate
{
public:
	INV(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	INV(const GraphicsInfo& r_GfxInfo); // Add this constructor declaration to match the definition in INV.cpp
	virtual void Operate() override;	//Calculates the output of the INV gate
	virtual void Draw(Output* pOut) override;	//Draws 1-input gate

	virtual int GetOutPinStatus() override;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n) override;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s) override;	//set status of Inputpin # n, to be used by connection class.

	virtual std::string GetInfo() const override;

	// Add these overrides to make INV a concrete class
	virtual OutputPin* GetOutputPin() override;
	virtual InputPin* GetInputPin() override;
	virtual Component* Clone(Point P) const override;
};

#endif