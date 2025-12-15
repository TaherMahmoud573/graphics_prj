#include "DSNMODE.h"
#include "..\ApplicationManager.h"

DSNMODE::DSNMODE(ApplicationManager* pApp) :Action(pApp)
{
}

DSNMODE::~DSNMODE(void)
{
}

void DSNMODE::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Design Mode: Click to switch to design mode.");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void DSNMODE::Execute()
{
	//Get a Pointer to the Input / Output Interfaces  //New
	Output* pOut = pManager->GetOutput();  //New
	Input* pIn = pManager->GetInput();     //New


	//Get Center point of the Gate
	ReadActionParameters();

	pOut->ClearToolBar();
	pOut->ClearStatusBar();
	pOut->ClearDrawingArea();
	pOut->PrintMsg("You have switched to Design Mode.");
	UI.AppMode = DESIGN;
	pOut->CreateDesignToolBar();

}

void DSNMODE::Undo()
{
}

void DSNMODE::Redo()
{
}

