#include "ChangeSwitch.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"
#include "..\Components\Component.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"

ChangeSwitch::ChangeSwitch(ApplicationManager* pApp) : Action(pApp), Cx(0), Cy(0)
{
}

ChangeSwitch::~ChangeSwitch()
{
}

void ChangeSwitch::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Switch toggle: Click on the switch to toggle it");
	pIn->GetPointClicked(Cx, Cy);
	pOut->ClearStatusBar();
}

void ChangeSwitch::Execute()
{
	ReadActionParameters();

	int CompCount = pManager->GetCompCount();
	Component** CompList = pManager->GetCompList();
	Output* pOut = pManager->GetOutput();

	bool toggled = false;

	for (int i = 0; i < CompCount; ++i)
	{
		GraphicsInfo compG = CompList[i]->GetParameters();
		// check if click is inside component rectangle
		if (Cx > compG.x1 && Cx < compG.x2 && Cy > compG.y1 && Cy < compG.y2)
		{
			// try to treat the component as a Switch
			Switch* sw = dynamic_cast<Switch*>(CompList[i]);
			if (sw)
			{
				sw->Toggle();           // flip state and update its output pin
				toggled = true;
				pOut->PrintMsg("Switch toggled.");
				break;
			}
		}
	}

	if (!toggled)
	{
		pOut->PrintMsg("No switch found at the clicked location.");
		return;
	}

	// Propagate signals: call Operate on all components several times to stabilize signals.
	// A simple approach: do CompCount passes (enough for small circuits).
	for (int pass = 0; pass < CompCount; ++pass)
	{
		for (int i = 0; i < CompCount; ++i)
		{
			CompList[i]->Operate();
		}
	}

	// Redraw updated interface
	pManager->UpdateInterface();
}