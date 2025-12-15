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

    GInfo.x1 = x1;
    GInfo.x2 = x2;
    GInfo.y1 = y1;
    GInfo.y2 = y2;

    for (int i = 0; i < CompCount; i++) {
        GraphicsInfo compParam = CompList[i]->GetParameters();
        if (x1 > compParam.x1 && x1 < compParam.x2 && y1 > compParam.y1 && y1 < compParam.y2) {
            srcPin = CompList[i]->GetOutputPin();
            if (!srcPin->checkAvailability()) {
                pOut->PrintMsg("Maximum number of fan outs reached. Source component occupied.");
                return;
            }
			GInfo.x1 = compParam.x2 - 10;
            GInfo.y1 = (compParam.y1 + compParam.y2)/2;
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
            InputPin* pins = CompList[i]->GetInputPin();
            int nInputs = CompList[i]->GetNumberOfInputs();
            bool found = false;
            for (int j = 0; j < nInputs; ++j) {
                if (!pins[j].isConnected()) {
                    dstPin = &pins[j];
                    // compute endpoint for j-th input pin (evenly spaced)
                    /*GInfo.x2 = compParam.x1 + 10;
                    int height = compParam.y2 - compParam.y1;
                    GInfo.y2 = compParam.y1 + (j + 1) * height / (nInputs + 1);
                    found = true;*/

                    int height = (compParam.y2 - compParam.y1) * 0.8;
					int Dy = height / (nInputs + 2);
					GInfo.y2 = height* 0.25 + compParam.y1 + (j + 1) * Dy;
                    GInfo.x2 = compParam.x1 + 20;
                    found = true;

                    break;
                }
            }
            //dstPin = CompList[i]->GetInputPin();
            if (!found) {
                pOut->PrintMsg("Destination component has no free input pins.");
                return;
            }
        }
    }
    
    // If no destination pin found, abort
    if (!dstPin) {
        pOut->PrintMsg("No destination component found at the clicked location. Action cancelled.");
        return;
    }

    if (GInfo.x1 == GInfo.x2 || GInfo.y1 == GInfo.y2) {
        pOut->PrintMsg("Invalid connection points. Action cancelled.");
        return;
	}

    if (GInfo.x1 > GInfo.x2) {
        pOut->PrintMsg("Connections must be drawn from left to right. Action cancelled.");
        return;
    }

    if (srcPin) { // A check for safety
        Connection* pA = new Connection(GInfo, srcPin, dstPin);
        if (!srcPin->ConnectTo(pA)) {
            pOut->PrintMsg("Source cannot accept additional connections. Action cancelled.");
            delete pA;
            return;
        }
        dstPin->setConnection(pA);
        dstPin->setComponent(pA);
        pManager->AddComponent(pA);
        pA->setSourcePin(srcPin);
        pA->setDestPin(dstPin);
        pA->Operate();
        //srcPin->ConnectTo(pA);
	    pOut->PrintMsg("Connection created.");
    }
}
void AddCONNECTION::Undo()
{
}

void AddCONNECTION::Redo()
{
}

