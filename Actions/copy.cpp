#include "copy.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include "Components/Component.h"

// Make sure CopyAction is declared as a class in copy.h and inherits from Action

CopyAction::CopyAction(ApplicationManager* pApp) : Action(pApp) { }

void CopyAction::ReadActionParameters()
{
	// No interactive parameters needed for copy
}

void CopyAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	int BuffCount, InvCount, AND3Count, AND2Count, OR2Count,
		NAND2Count, NOR2Count, XOR2Count, XNOR2Count, NOR3Count, XOR3Count,
		SwitchCount, LedCount, ConnectionCount, totalSelected;
	Component* singleSelectedComp = nullptr;

	pManager->GetSelectedCompCounts(BuffCount, InvCount, AND3Count, AND2Count, OR2Count,
		NAND2Count, NOR2Count, XOR2Count, XNOR2Count, NOR3Count, XOR3Count,
		SwitchCount, LedCount, ConnectionCount, totalSelected, singleSelectedComp);

	if (totalSelected != 1 || singleSelectedComp == nullptr)
	{
		pOut->PrintMsg("Please select exactly one component to copy");
		return;
	}

	// Store a cloned copy in the application clipboard (ApplicationManager will own it)
	pManager->SetClipboard(singleSelectedComp);
	pOut->PrintMsg("Component copied to clipboard");
}