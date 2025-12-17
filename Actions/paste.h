#pragma once
#include "Actions/Action.h"
#include "ApplicationManager.h"

// Class responsible for pasting copied components
class PasteAction : public Action
{
private:
    Point PastePoint; //where the component will be pasted

public:
    PasteAction(ApplicationManager* pApp);
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override {}      // Provide empty implementation
    virtual void Redo() override {}      // Provide empty implementation
};

