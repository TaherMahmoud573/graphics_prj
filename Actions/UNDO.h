#ifndef _UNDO_H
#define _UNDO_H

#include "action.h"

class UndoAction : public Action
{
private:
	//Parameters for rectangular area to be occupied icon
	int Cx, Cy;	//Center point of the icon
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	UndoAction(ApplicationManager* pApp);
	virtual ~UndoAction(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif