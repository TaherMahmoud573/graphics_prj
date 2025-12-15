#include "AddORgate2.h"
#include "..\ApplicationManager.h"

AddORgate2::AddORgate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddORgate2::~AddORgate2(void)
{
}

void AddORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input OR Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddORgate2::Execute()
{
	//Get a Pointer to the Input / Output Interfaces  //New
	Output* pOut = pManager->GetOutput();  //New
	Input* pIn = pManager->GetInput();     //New


	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;


	if (Cx < 0 || Cx > UI.width || Cy < UI.ToolBarHeight + 50 || Cy > UI.height - UI.StatusBarHeight - UI.ToolBarHeight - 50)  //New
	{
		pOut->PrintMsg("Invalid location! Please click inside the drawing area.");

		return;
	}

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	if (!pManager->IsAreaFree(GInfo))                                          //New
	{
		pOut->PrintMsg("Cannot place component here, area is occupied.");
		return;
	}
	OR2* pA = new OR2(GInfo, OR2_FANOUT);
	pManager->AddComponent(pA);
}

void AddORgate2::Undo()
{
}

void AddORgate2::Redo()
{
}

