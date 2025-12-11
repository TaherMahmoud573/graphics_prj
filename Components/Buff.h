#ifndef _BUFF_H
#define _BUFF_H

/*
  Class BUFF
  -----------
  represent the 1-input BUFFER Gate
*/

#include "Gate.h"

class BUFF :public Gate
{
public:
	BUFF(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the BUFF gate
	virtual void Draw(Output* pOut);	//Draws BUFF

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.


};

#endif