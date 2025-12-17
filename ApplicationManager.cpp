#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddORgate2.h"
#include "Actions\ADDBuff.h"
#include "Actions\ADDINV.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddXORgate3.h"
#include "Actions\AddSwitch.h"
#include "Actions\AddLED.h"
#include "Actions\\select.h"

// include move header
#include "Actions\\Move.h"

//include copy/cut/paste action headers
#include "copy.h"
#include "cut.h"
#include "paste.h"

// Add concrete component headers so dynamic_cast targets are complete types
#include "Components\\AND2.h"
#include "Components\\AND3.h"
#include "Components\\Buff.h"
#include "Components\\INV.h"
#include "Components\\OR2.h"
#include "Components\\NAND2.h"
#include "Components\\NOR2.h"
#include "Components\\XOR2.h"
#include "Components\\XNOR2.h"
#include "Components\\NOR3.h"
#include "Components\\XOR3.h"
#include "Components\\Switch.h"
#include "Components\\LED.h"
#include "Components\\Connection.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	for (int i = 0; i < MaxCompCount; i++)
		CompList[i] = NULL;

	Clipboard = NULL; 

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction();
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
	case ADD_AND_GATE_2:
		pAct = new AddANDgate2(this);
		break;

	case ADD_OR_GATE_2:
		pAct = new AddORgate2(this);
		break;

	case ADD_Buff:
		pAct = new AddBuff(this);
		break;

	case ADD_INV:
		pAct = new AddINV(this);
		break;

	case ADD_NAND_GATE_2:
		pAct = new AddNANDgate2(this);
		break;

	case ADD_NOR_GATE_2:
		pAct = new AddNORgate2(this);
		break;

	case ADD_XOR_GATE_2:
		pAct = new AddXORgate2(this);
		break;

	case ADD_XNOR_GATE_2:
		pAct = new AddXNORgate2(this);
		break;

	case ADD_AND_GATE_3:
		pAct = new AddANDgate3(this);
		break;

	case ADD_NOR_GATE_3:
		pAct = new AddNORgate3(this);
		break;

	case ADD_XOR_GATE_3:
		pAct = new AddXORgate3(this);
		break;

	case ADD_Switch:
		pAct = new AddSwitch(this);
		break;

	case ADD_LED:
		pAct = new AddLED(this);
		break;

	// Copy / Cut / Paste 
	case Copy:
		pAct = new CopyAction(this);
		break;

	case Cut:
		pAct = new CutAction(this);
		break;

	case Paste:
		pAct = new PasteAction(this);
		break;

	// Move
	case MOVE:
		pAct = new MoveAction(this);
		break;

	case SELECT:
		
		pAct = new SelectAction(this);
		break;

	case ADD_CONNECTION:
		//TODO: Create AddConection Action here
		break;
	case EXIT:
		///TODO: create ExitAction here
		break;
	}
	if (pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	// Clear the drawing area first so old component don't remain
	OutputInterface->ClearDrawingArea();

	// Redraw all components in their current positions
	for (int i = 0; i < CompCount; i++)
		if (CompList[i])
			CompList[i]->Draw(OutputInterface);
}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::GetSelectedCompCounts(int& BuffCount, int& InvCount, int& AND3Count, int& AND2Count, int& OR2Count, int& NAND2Count, int& NOR2Count, int& XOR2Count, int& XNOR2Count, int& NOR3Count, int& XOR3Count, int& SwitchCount, int& LedCount, int& ConnectionCount, int& totalSelected, Component*& singleSelectedComp) const
{
	// Initialize all counts to zero
	BuffCount = 0;
	InvCount = 0;
	AND3Count = 0;
	AND2Count = 0;
	OR2Count = 0;
	NAND2Count = 0;
	NOR2Count = 0;
	XOR2Count = 0;
	XNOR2Count = 0;
	NOR3Count = 0;
	XOR3Count = 0;
	SwitchCount = 0;
	LedCount = 0;
	ConnectionCount = 0;
	totalSelected = 0;
	singleSelectedComp = NULL;

	// Loop through all components
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == nullptr) continue;

		if (CompList[i]->IsSelected())
		{
			// Increment total count
			totalSelected++;

			// If we have exactly one selected component so far, store it
			if (totalSelected == 1)
				singleSelectedComp = CompList[i];
			else
				singleSelectedComp = NULL; // More than one component is selected

			// Determine component type (no duplicate checks)
			if (dynamic_cast<AND2*>(CompList[i]) != NULL)
				AND2Count++;
			else if (dynamic_cast<AND3*>(CompList[i]) != NULL)
				AND3Count++;
			else if (dynamic_cast<BUFF*>(CompList[i]) != NULL)
				BuffCount++;
			else if (dynamic_cast<INV*>(CompList[i]) != NULL)
				InvCount++;
			else if (dynamic_cast<OR2*>(CompList[i]) != NULL)
				OR2Count++;
			else if (dynamic_cast<NAND2*>(CompList[i]) != NULL)
				NAND2Count++;
			else if (dynamic_cast<NOR2*>(CompList[i]) != NULL)
				NOR2Count++;
			else if (dynamic_cast<XOR2*>(CompList[i]) != NULL)
				XOR2Count++;
			else if (dynamic_cast<XNOR2*>(CompList[i]) != NULL)
				XNOR2Count++;
			else if (dynamic_cast<NOR3*>(CompList[i]) != NULL)
				NOR3Count++;
			else if (dynamic_cast<XOR3*>(CompList[i]) != NULL)
				XOR3Count++;
			else if (dynamic_cast<Switch*>(CompList[i]) != NULL)
				SwitchCount++;
			else if (dynamic_cast<LED*>(CompList[i]) != NULL)
				LedCount++;
			else if (dynamic_cast<Connection*>(CompList[i]) != NULL)
				ConnectionCount++;
		}
	}
}
void ApplicationManager::UnselectAll()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] && CompList[i]->IsSelected())
			CompList[i]->SetSelected(false);
	}
}
////////////////////////////////////////////////////////////////////
Component* ApplicationManager::GetComp(int x, int y) const
{
	Point P = {0, 0};

	P.x = x;
	P.y = y;

	// Loop through all figures starting from the most recently added (top figure)
	for (int i = CompCount - 1; i >= 0; i--)
	{
		if (CompList[i] && CompList[i]->IsInside(P))
		{
			return CompList[i];  // Return pointer to the figure
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////

bool ApplicationManager::IsAreaFree(const GraphicsInfo& GInfo) const
{
    // Check if the area defined by GInfo overlaps with any existing component
    for (int i = 0; i < CompCount; ++i)
    {
        if (CompList[i] != nullptr)
        {
            GraphicsInfo compGfx = CompList[i]->GetParameters();
            // Check for rectangle overlap
            bool overlapX = !(GInfo.x2 < compGfx.x1 || GInfo.x1 > compGfx.x2);
            bool overlapY = !(GInfo.y2 < compGfx.y1 || GInfo.y1 > compGfx.y2);
            if (overlapX && overlapY)
                return false; // Area is not free
        }
    }
    return true; // Area is free
}

bool ApplicationManager::IsAreaFree(const GraphicsInfo& GInfo, const Component* ignore) const
{
    // Check if the area defined by GInfo overlaps with any existing component
    for (int i = 0; i < CompCount; ++i)
    {
        if (CompList[i] == nullptr) continue;
        if (CompList[i] == ignore) continue; // ignore the component being moved

        GraphicsInfo compGfx = CompList[i]->GetParameters();
        // Check for rectangle overlap
        bool overlapX = !(GInfo.x2 < compGfx.x1 || GInfo.x1 > compGfx.x2);
        bool overlapY = !(GInfo.y2 < compGfx.y1 || GInfo.y1 > compGfx.y2);
        if (overlapX && overlapY)
            return false; // Area is not free
    }
    return true; // Area is free
}

ApplicationManager::~ApplicationManager()
{
	// Delete owned components once
	for (int i = 0; i < CompCount; ++i)
	{
		delete CompList[i];
		CompList[i] = nullptr;
	}
	CompCount = 0;

	// If Clipboard points to a component not in CompList, delete it.
	if (Clipboard)
	{
		bool owned = false;
		delete Clipboard;
		Clipboard = nullptr;
	}

	// Delete Input first (created by Output), then Output
	delete InputInterface;
	InputInterface = nullptr;

	delete OutputInterface;
	OutputInterface = nullptr;
}

// Clipboard management implementations

void ApplicationManager::SetClipboard(Component* pComp)
{
	// Remove old clipboard contents first
	if (Clipboard)
	{
		delete Clipboard;
		Clipboard = nullptr;
	}

	if (pComp == nullptr)
	{
		Clipboard = nullptr;
		return;
	}

	// Create an owned clone of the component so clipboard owns its own copy.
	// Requires Component::Clone(Point) to be declared and implemented in concrete components.
	Point center = pComp->GetCenter();
	Clipboard = pComp->Clone(center);
}

Component* ApplicationManager::GetClipboard() const
{
	return Clipboard;
}

void ApplicationManager::DeleteSelectedComp()
{
	// Remove all selected components from CompList, deleting them and keeping array compact.
	for (int i = 0; i < CompCount; )
	{
		if (CompList[i] && CompList[i]->IsSelected())
		{
			delete CompList[i];
			// Shift remaining items left
			for (int j = i; j < CompCount - 1; ++j)
				CompList[j] = CompList[j + 1];
			CompList[CompCount - 1] = nullptr;
			--CompCount;
			
		}
		else
		{
			++i;
		}
	}
}