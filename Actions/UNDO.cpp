#include "UNDO.h"
#include "..\ApplicationManager.h"

UndoAction::UndoAction(ApplicationManager* pApp) :Action(pApp)
{
}

UndoAction::~UndoAction(void)
{
}

void UndoAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Undo: Click to undo.");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void UndoAction::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput(); 
	Input* pIn = pManager->GetInput();  


	//Get Center point of the Gate
	ReadActionParameters();


}

void UndoAction::Undo()
{
}

void UndoAction::Redo()
{
}

