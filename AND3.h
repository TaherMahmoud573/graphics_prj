#ifndef _AND3_H
#define _AND3_H

#include "Gate.h"


class AND3 : public Gate
{
public:
	AND3(const GraphicsInfo& r_GfxInfo, int r_FanOut);

	AND3(const GraphicsInfo& r_GfxInfo) : Gate(3, 5) // Default fanout to 5 or any suitable value
	{
		m_GfxInfo = r_GfxInfo;
	}

	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 3-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	virtual std::string GetInfo() const override;
	virtual Component* Clone(Point P) const override;
};


#endif