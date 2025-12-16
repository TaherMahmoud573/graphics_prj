#include "Delete.h"
#include "GUI/Output.h"
#include "ApplicationManager.h"

Delete::Delete(ApplicationManager* pApp)
    : Action(pApp)
{
}

void Delete::Execute()
{
    Output* pOut = pManager->GetOutput();

    int CompCount = pManager->GetCompCount(); // existing function
    Component** CompList = pManager->GetCompList(); // get internal array

    // Find the first selected component
    int indexToDelete = -1;
    for (int i = 0; i < CompCount; i++)
    {
        if (CompList[i]->IsSelected())
        {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1)
    {
        pOut->PrintMsg("No component selected to delete.");
        return;
    }

    // Delete the component
    delete CompList[indexToDelete];

    // Shift remaining components
    for (int i = indexToDelete; i < CompCount - 1; i++)
    {
        CompList[i] = CompList[i + 1];
    }

    // Reduce the component count directly
    pManager->SetCompCount(CompCount - 1);

    // Clear the last pointer
    CompList[pManager->GetCompCount()] = nullptr;

    // Update the drawing area
    pManager->UpdateInterface();

    pOut->PrintMsg("Component deleted successfully.");
}
