#include "Simulate.h"
#include "..\ApplicationManager.h"
#include "..\Components\LED.h"
#include "..\Components\Connection.h"

Simulate::Simulate(ApplicationManager* pApp) :Action(pApp)
{
}

Simulate::~Simulate(void)
{
}

void Simulate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Simulate: Click to simulate the circuit");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Simulate::Execute()
{
	//Get a Pointer to the Input / Output Interfaces  //New
	//Output* pOut = pManager->GetOutput();  //New
	//Input* pIn = pManager->GetInput();     //New


	//Get Center point of the Gate
	//ReadActionParameters();

	//Calculate the rectangle Corners
	//int Len = UI.AND2_Width;
	//int Wdth = UI.AND2_Height;


	//if (Cx < 0 || Cx > UI.width || Cy < UI.ToolBarHeight + 50 || Cy > UI.height - UI.StatusBarHeight - UI.ToolBarHeight - 50)  //New
	//{
	//	pOut->PrintMsg("Invalid location! Please click inside the drawing area.");

	//	return;
	//}

	//GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	//GInfo.x1 = Cx - Len / 2;
	//GInfo.x2 = Cx + Len / 2;
	//GInfo.y1 = Cy - Wdth / 2;
	//GInfo.y2 = Cy + Wdth / 2;

	//if (!pManager->IsAreaFree(GInfo))                                          //New
	//{
	//	pOut->PrintMsg("Cannot place component here, area is occupied.");
	//	return;
	//}

	//AND2* pA = new AND2(GInfo, AND2_FANOUT);
	//pManager->AddComponent(pA);
	// Get interfaces
	Output* pOut = pManager->GetOutput();

	int CompCount = pManager->GetCompCount();
	Component** CompList = pManager->GetCompList();

	if (CompCount == 0) {
		pOut->PrintMsg("Nothing to simulate.");
		return;
	}

	// Run a few stabilization passes. For each pass:
	//  1) call Operate() on all non-Connection components (gates, switches, LEDs)
	//  2) call Operate() on all Connection components to push outputs into inputs
	// This ensures outputs are computed before connections transfer them to destination pins.
	int passes = CompCount + 2;
	for (int pass = 0; pass < passes; ++pass) {
		// 1) non-connection components
		for (int i = 0; i < CompCount; ++i) {
			Connection* c = dynamic_cast<Connection*>(CompList[i]);
			if (c == nullptr) // not a connection => gate / switch / LED
				CompList[i]->Operate();
		}
		// 2) connection components
		for (int i = 0; i < CompCount; ++i) {
			Connection* c = dynamic_cast<Connection*>(CompList[i]);
			if (c != nullptr)
				c->Operate();
		}
	}

	// Update LEDs' visual/internal state from their input pins
	for (int i = 0; i < CompCount; ++i) {
		LED* led = dynamic_cast<LED*>(CompList[i]);
		if (led) {
			led->UpdateLedState();
		}
	}

	// Redraw updated circuit
	pManager->UpdateInterface();

	pOut->PrintMsg("Simulation completed.");
}

void Simulate::Undo()
{
}

void Simulate::Redo()
{
}

