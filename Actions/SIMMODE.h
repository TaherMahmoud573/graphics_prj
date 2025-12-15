#ifndef _SIMMODE_H
#define _SIMMODE_H

#include "action.h"

class SIMMODE : public Action
{
private:
	//Parameters for rectangular area to be occupied icon
	int Cx, Cy;	//Center point of the icon
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	SIMMODE(ApplicationManager* pApp);
	virtual ~SIMMODE(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif