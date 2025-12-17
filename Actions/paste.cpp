
#include "paste.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include "ApplicationManager.h"
#include "Components/Component.h"

PasteAction::PasteAction(ApplicationManager* pApp) : Action(pApp)
{
    PastePoint.x = 0;
    PastePoint.y = 0;
}

void PasteAction::ReadActionParameters()
{
    // Get pointers to I/O
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Click where you want to paste the component");

    // Read the point selected
    pIn->GetPointClicked(PastePoint.x, PastePoint.y);

    // Clear status bar (consistent with other actions)
    pOut->ClearStatusBar();
}

void PasteAction::Execute()
{
    // Get output interface
    Output* pOut = pManager->GetOutput();

    // Get the component in the application clipboard
    Component* clipboardComp = pManager->GetClipboard();

    if (clipboardComp == NULL)
    {
        pOut->PrintMsg("Clipboard is empty. Copy a component first");
        return;
    }

    // Ask user where to paste
    ReadActionParameters();

    // Create a clone of the clipboard component at the new location.
    // NOTE: this requires a virtual Clone(Point) method on Component that returns a new Component*.
    Component* newComp = clipboardComp->Clone(PastePoint);

    if (newComp != NULL)
    {
        // Unselect current selections, add the new component, select it and refresh UI
        pManager->UnselectAll();
        pManager->AddComponent(newComp);
        newComp->SetSelected(true);

        pOut->PrintMsg("Component pasted successfully");
    }
    else
    {
        pOut->PrintMsg("Error: Could not paste component");
    }

    // Update the interface
    pManager->UpdateInterface();
}