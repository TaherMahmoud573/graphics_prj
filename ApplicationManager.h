#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface
	Component* Clipboard; // Clipboard to hold a pointer to a copied component

public:
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();

	//Creates an action and executes it
	void ExecuteAction(ActionType);

	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	Component* GetComp(int x, int y) const;

	void GetSelectedCompCounts(int& BuffCount, int& InvCount, int& AND3Count, int& AND2Count, int& OR2Count,
		int& NAND2Count, int& NOR2Count, int& XOR2Count, int& XNOR2Count, int& NOR3Count, int& XOR3Count,
		int& SwitchCount, int& LedCount, int& ConnectionCount, int& totalSelected,
		Component*& singleSelectedComp) const;

	void UnselectAll();

	// Check if the given area is free of components
	bool IsAreaFree(const GraphicsInfo& GInfo) const;

	bool IsAreaFree(const GraphicsInfo& GInfo, const Component* ignore) const;

	// Clipboard management for copy/cut/paste
	//  SetClipboard stores an owned clone of the provided component (ApplicationManager becomes owner)
	//  GetClipboard returns the clipboard pointer 
	
	void SetClipboard(Component* pComp);
	Component* GetClipboard() const;
	void DeleteSelectedComp();

	//destructor
	~ApplicationManager();
};

#endif