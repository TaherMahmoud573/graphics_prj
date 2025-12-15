#ifndef _CHANGE_SWITCH_H
#define _CHANGE_SWITCH_H

#include "Action.h"

class ChangeSwitch : public Action
{
private:
	int Cx, Cy;	// click position
public:
	ChangeSwitch(ApplicationManager* pApp);
	virtual ~ChangeSwitch();

	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo() {}
	virtual void Redo() {}
};

#endif