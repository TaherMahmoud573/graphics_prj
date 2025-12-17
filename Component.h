#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"

//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	bool Selected;	//true if the component is selected.
public:
	explicit Component(const GraphicsInfo& r_GfxInfo);
	Component();	
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself

	virtual int GetOutPinStatus() = 0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n) = 0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s) = 0;	//set status of Inputpin # n, to be used by connection class.
	void SetSelected(bool s);	//select/unselect the figure  
	bool IsSelected() const;	//check whether fig is selected
	virtual string GetInfo() const = 0;

	// Provide a  label getter 
	virtual string GetLabel() const;
 
	virtual bool IsInside(Point P) const;

	// Move the component by dx,dy.
	virtual void Move(int dx, int dy);

	virtual Point GetCenter() const;
	virtual GraphicsInfo GetParameters() const { return m_GfxInfo; }

	// Create a heap-allocated copy of this component positioned such that its center is P.
	// Concrete component classes must implement Clone so paste can create a new instance.
	virtual Component* Clone(Point P) const = 0;

	//Destructor must be virtual
	virtual ~Component();
};
#endif