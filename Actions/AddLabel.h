#pragma once
#include "Actions\Action.h"

class AddLabel : public Action
{
private:
    string Label;      // The label entered by the user
    Component* pComp;  // The selected component to label

public:
    AddLabel(ApplicationManager* pApp);

    void ReadActionParameters(); // Ask user for label
    void Execute();              // Assign label to component

    void Undo() {}   // Optional (not required)
    void Redo() {}   // Optional (not required)
};
