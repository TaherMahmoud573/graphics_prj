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
	Output* pOut = pManager->GetOutput();

	int CompCount = pManager->GetCompCount();
	Component** CompList = pManager->GetCompList();

	if (CompCount == 0) {
		pOut->PrintMsg("Nothing to simulate.");
		return;
	}
	int margin = CompCount + 3;
	for (int i = 0; i < margin; i++) {
		for (int j = 0; j < CompCount; j++) {
			if (CompList[j]->GetType() != "CONNECTION")
				CompList[j]->Operate();
		}
		for (int j = 0; j < CompCount; j++) {
			if (CompList[j]->GetType() == "CONNECTION")
				CompList[j]->Operate();
		}
	}

	for (int i = 0; i < CompCount; ++i) {
		LED* led = dynamic_cast<LED*>(CompList[i]);
		if (led) {
			led->UpdateLedState();
		}
	}

	pManager->UpdateInterface();
	pOut->PrintMsg("Simulation completed.");
}

void Simulate::Undo()
{
}

void Simulate::Redo()
{
}

