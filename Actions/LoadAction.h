#ifndef _LOAD_H
#define _LOAD_H

#include "action.h"
#include <string>
using namespace std;


class LoadAction :
	public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	string filename; // name of the file to save to
public:
	LoadAction(ApplicationManager* pApp);
	virtual ~LoadAction(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif