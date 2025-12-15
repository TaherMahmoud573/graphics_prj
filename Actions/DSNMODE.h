#ifndef _DSNMODE_H
#define _DSNMODE_H

#include "action.h"

class DSNMODE : public Action
{
private:
	//Parameters for rectangular area to be occupied by the icon
	int Cx, Cy;	//Center point of the icon
	int x1, y1, x2, y2;	//Two corners of the rectangular area
public:
	DSNMODE(ApplicationManager* pApp);
	virtual ~DSNMODE(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif