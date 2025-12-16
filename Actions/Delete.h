#pragma once
#include "Actions/Action.h"
#include "Components/Component.h"
#include "ApplicationManager.h"

class Delete : public Action
{
public:
    Delete(ApplicationManager* pApp);
    void ReadActionParameters();
    void Execute();
    void Undo() {}
    void Redo() {}
};

