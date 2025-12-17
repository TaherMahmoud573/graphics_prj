#pragma once
#include "Actions/Action.h"
#include "ApplicationManager.h"
#include "Components/Component.h"

// CopyAction: copy a single selected component into the application clipboard.
class CopyAction : public Action
{
public:
	CopyAction(ApplicationManager* pApp);
	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override {}
	virtual void Redo() override {}
};
