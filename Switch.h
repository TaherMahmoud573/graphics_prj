#ifndef _Switch_H
#define _Switch_H

/*
  Class Switch
  -----------
  represent a switch (single output)
*/

#include "Gate.h"

class Switch :public Gate
{
public:
	Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	Switch(const GraphicsInfo& r_GfxInfo); // Constructor for cloning
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws the switch

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual Component* Clone(Point P) const override;

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	

	
	virtual void Move(int dx, int dy) override;

	virtual std::string GetInfo() const override;


};


inline void Switch::Move(int dx, int dy)
{
    m_GfxInfo.x1 += dx;
    m_GfxInfo.x2 += dx;
    m_GfxInfo.y1 += dy;
    m_GfxInfo.y2 += dy;
}

#endif