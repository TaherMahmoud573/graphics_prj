#pragma once
#include "Actions/Action.h"
#include "ApplicationManager.h"
#include "Components/Component.h"

// CutAction: copy the selected component to clipboard and delete it from canvas.
class CutAction : public Action
{
public:
    CutAction(ApplicationManager* pApp);
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override {}
    virtual void Redo() override {}
};

