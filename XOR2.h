#ifndef _XOR2_H
#define _XOR2_H

/*
  Class XOR2
  -----------
  represent the 2-input XOR gate
*/

#include "Gate.h"

class XOR2 :public Gate
{
public:
	XOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	// Declare the single-arg ctor; definition lives in XOR2.cpp
	XOR2(const GraphicsInfo& r_GfxInfo);
	virtual void Operate();	//Calculates the output of the XOR gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual std::string GetInfo() const override;
	virtual Component* Clone(Point P) const override;

};

#endif