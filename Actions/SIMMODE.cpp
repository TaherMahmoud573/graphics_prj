#include "SIMMODE.h"
#include "..\ApplicationManager.h"

SIMMODE::SIMMODE(ApplicationManager* pApp) :Action(pApp)
{
}

SIMMODE::~SIMMODE(void)
{
}

void SIMMODE::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Simulation Mode: Click to switch to simulation mode.");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void SIMMODE::Execute()
{
	//Get a Pointer to the Input / Output Interfaces  //New
	Output* pOut = pManager->GetOutput();  //New
	Input* pIn = pManager->GetInput();     //New


	//Get Center point of the Gate
	ReadActionParameters();

	pOut->ClearToolBar();
	pOut->ClearStatusBar();
	pOut->ClearDrawingArea();
	pOut->PrintMsg("You have switched to Simulation Mode.");
	UI.AppMode = SIMULATION;
	pOut->CreateSimulationToolBar();

}

void SIMMODE::Undo()
{
}

void SIMMODE::Redo()
{
}

