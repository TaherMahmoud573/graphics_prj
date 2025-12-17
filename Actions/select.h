#pragma once  
#include "Actions/Action.h" // Corrected the relative path to match the folder structure  
#include "Components/Component.h"  

class SelectAction : public Action
{
protected:
	Point ClickedP; // clicked point  

	Component* SelectedFig; // Pointer to the selected figure  

public:
	SelectAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo() override {}      // Provide empty implementation
	virtual void Redo() override {}      // Provide empty implementation
};