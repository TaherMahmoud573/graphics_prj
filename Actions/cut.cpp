#include "cut.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"
#include "Components/Component.h"

CutAction::CutAction(ApplicationManager* pApp) : Action(pApp) {}

void CutAction::ReadActionParameters()
{ // No parameters to read for cut 

}
void CutAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	int BuffCount, InvCount, AND3Count, AND2Count, OR2Count,
		NAND2Count, NOR2Count, XOR2Count, XNOR2Count, NOR3Count, XOR3Count,
		SwitchCount, LedCount, ConnectionCount, totalSelected;
	Component* singleSelectedComp = NULL;

	pManager->GetSelectedCompCounts(BuffCount, InvCount, AND3Count, AND2Count, OR2Count,
		NAND2Count, NOR2Count, XOR2Count, XNOR2Count, NOR3Count, XOR3Count,
		SwitchCount, LedCount, ConnectionCount, totalSelected, singleSelectedComp);

	if (totalSelected != 1 || singleSelectedComp == NULL)
	{
		pOut->PrintMsg("Please select exactly one component to cut");
		return;
	}

	pManager->SetClipboard(singleSelectedComp);
	pManager->DeleteSelectedComp();
	pOut->PrintMsg("Component cut successfully. Use paste to place it in a new location.");
	pManager->UpdateInterface();

}