#include "AddCONNECTION.h"
#include "..\ApplicationManager.h"

AddCONNECTION::AddCONNECTION(ApplicationManager* pApp) :Action(pApp)
{
}

AddCONNECTION::~AddCONNECTION(void)
{
}

/*void AddCONNECTION::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Connection: Click to add the connection");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}*/

void AddCONNECTION::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Connection: Click source gate");
    pIn->GetPointClicked(x1, y1);

    pOut->PrintMsg("Connection: Click destination gate");
    pIn->GetPointClicked(x2, y2);

    pOut->ClearStatusBar();
}

void AddCONNECTION::Execute()
{
    //Get Center point of the Gate
    ReadActionParameters();

    GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
    int CompCount = pManager->GetCompCount();
    Component** CompList = pManager->GetCompList();
    OutputPin* srcPin = nullptr;
    InputPin* dstPin = nullptr;
    Output* pOut = pManager->GetOutput();

    /*
    GInfo.x1 = Cx;
    GInfo.y1 = Cy;
    GInfo.x2 = Cx;
    GInfo.y2 = Cy;
    */
    GInfo.x1 = x1;
    GInfo.x2 = x2;
    GInfo.y1 = y1;
    GInfo.y2 = y2;

    for (int i = 0; i < CompCount; i++) {
        GraphicsInfo compParam = CompList[i]->GetParameters();
        if (x1 > compParam.x1 && x1 < compParam.x2 && y1 > compParam.y1 && y1 < compParam.y2) {
            srcPin = CompList[i]->GetOutputPin();
            break;
        }
    }

    // If no source pin found, abort
    if (!srcPin) {
        pOut->PrintMsg("No source component found at the clicked location. Action cancelled.");
        return;
    }

    for (int i = 0; i < CompCount; i++) {
        GraphicsInfo compParam = CompList[i]->GetParameters();
        if (x2 > compParam.x1 && x2 < compParam.x2 && y2 > compParam.y1 && y2 < compParam.y2) {
            dstPin = CompList[i]->GetInputPin();
            break;
        }
    }

    // If no destination pin found, abort
    if (!dstPin) {
        pOut->PrintMsg("No destination component found at the clicked location. Action cancelled.");
        return;
    }

    if (srcPin) { // Add check for safety
        Connection* pA = new Connection(GInfo, srcPin, dstPin);
        pManager->AddComponent(pA);
        srcPin->ConnectTo(pA);
        //dstPin->setComponent(pA);
    }
	pOut->PrintMsg("Connection created.");
}
void AddCONNECTION::Undo()
{
}

void AddCONNECTION::Redo()
{
}

