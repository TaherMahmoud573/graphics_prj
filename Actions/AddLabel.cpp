#include "AddLabel.h"
#include "ApplicationManager.h"
#include "GUI\Input.h"
#include "GUI\Output.h"

AddLabel::AddLabel(ApplicationManager* pApp)
    : Action(pApp)
{
    pComp = nullptr;
}
void AddLabel::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pComp = nullptr;

    // Loop through all components to find the selected one
    for (int i = 0; i < pManager->GetCompCount(); i++)
    {
        if (pManager->GetComponent(i)->IsSelected())
        {
            pComp = pManager->GetComponent(i);
            break;
        }
    }

    // No selected component
    if (!pComp)
    {
        pOut->PrintMsg("No component selected. Please select a component first.");
        Label = "";
        return;
    }

    // Ask user for label
    pOut->PrintMsg("Enter label (ESC to cancel): ");
    Label = pIn->GetString(pOut);

    pOut->ClearStatusBar();
}
