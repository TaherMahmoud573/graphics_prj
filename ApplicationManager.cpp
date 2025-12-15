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
#include "Actions\AddCONNECTION.h"
#include "Actions\SIMMODE.h"
#include "Actions\DSNMODE.h"
#include "Actions\UNDO.h"
#include "Actions\Simulate.h"
#include "Actions\ChangeSwitch.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction.h"


ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

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
	int x1, y1;
	ActionType ActType = InputInterface->GetUserAction(x1, y1);
	for (int i = 0; i < CompCount; i++) {
		GraphicsInfo compParam = CompList[i]->GetParameters();
		if (x1 > compParam.x1 && x1 < compParam.x2 && y1 > compParam.y1 && y1 < compParam.y2 && CompList[i]->GetType() == "SWITCH") {
			ActType = Change_Switch;
			return ActType;
		}
	}
	return ActType;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);	
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
			
		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			pAct = new AddCONNECTION(this);
			break;
	
		case SIM_MODE:                                    //New
			pAct = new SIMMODE(this);
			break;


		case DSN_MODE:                                    //New
			pAct = new DSNMODE(this);
			break;

		case UNDO:
			pAct = new UndoAction(this);                        //New
			break;

		case SIM:
			pAct = new Simulate(this);                        //New
			break;

		case Change_Switch:
			pAct = new ChangeSwitch(this);
			break;

		case SAVE:
			pAct = new SaveAction(this);
			break;

		case LOAD:
			pAct = new LoadAction(this);
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

	for(int i=0; i<CompCount; i++)
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

bool ApplicationManager::IsAreaFree(const GraphicsInfo& Gfx) const             //New
{
	for (int i = 0; i < CompCount; i++)
	{
		GraphicsInfo old = CompList[i]->GetGraphicsInfo();
		if (CompList[i]->GetType() == "CONNECTION")
			continue;
		bool overlap = !(Gfx.x2 < old.x1 || Gfx.x1 > old.x2 || Gfx.y2 < old.y1 || Gfx.y1 > old.y2);

		if (overlap)
			return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::ClearAllComponents()
{
	for (int i = 0; i < CompCount; ++i) {
		delete CompList[i];
		CompList[i] = nullptr;
	}
	CompCount = 0;
}
////////////////////////////////////////////////////////////////////
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}