#include "Actions\\select.h"
#include "GUI/Output.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"


SelectAction::SelectAction(ApplicationManager* pApp) : Action(pApp)
{
    SelectedFig = NULL;
    ClickedP.x = 0;
    ClickedP.y = 0;
}


void SelectAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Select a Figure");

    // read the point selected
    pIn->GetPointClicked(ClickedP.x, ClickedP.y);

}

  void SelectAction::Execute()
{
    ReadActionParameters();

    // Get the pointer to input and output
    Output* pOut = pManager->GetOutput();

    // Get the figure at the clicked point (if any)
    Component* clickedComp = pManager->GetComp(ClickedP.x, ClickedP.y);

    // Check if a figure was found
    if (clickedComp != NULL)
    {
        // If the figure is already selected, unselect it
        if (clickedComp->IsSelected())
        {
            clickedComp->SetSelected(false);
            pOut->PrintMsg("Figure unselected");
        }
        else
        {
            // Select the figure without unselecting others
            clickedComp->SetSelected(true);

            // Get info about selected figures and display on status bar
            int BuffCount, InvCount, AND3Count, AND2Count, OR2Count, NAND2Count, NOR2Count, XOR2Count, XNOR2Count, NOR3Count, XOR3Count, SwitchCount, LedCount, ConnectionCount, totalSelected;
            Component* singleSelectedComp = NULL;

            pManager->GetSelectedCompCounts(BuffCount, InvCount, AND3Count, AND2Count, OR2Count, NAND2Count, NOR2Count, XOR2Count, XNOR2Count, NOR3Count, XOR3Count, SwitchCount, LedCount, ConnectionCount, totalSelected, singleSelectedComp);

            if (totalSelected == 1)
            {
                // Only one figure is selected, show its detailed info
                pOut->PrintMsg("Figure selected: " + singleSelectedComp->GetInfo());
            }
            else
            {
                // Multiple figures are selected, show count by type
                string msg = "Selected: ";

                if (AND2Count > 0)
                    msg += to_string(AND2Count) + " 2 input AND gate(s), ";

                if (BuffCount > 0)
                    msg += to_string(BuffCount) + "  Buffer gate(s), ";

                if (InvCount > 0)
                    msg += to_string(InvCount) + " Inverter gate(s), ";

                if (OR2Count > 0)
                    msg += to_string(OR2Count) + " 2 input OR gate(s), ";

                if (AND3Count > 0)
                    msg += to_string(AND3Count) + " 3 input AND gate(s), ";

                if (NAND2Count > 0)
                    msg += to_string(NAND2Count) + " 2 input NAND gate(s), ";

                if (NOR2Count > 0)
                    msg += to_string(NOR2Count) + " 2 input NOR gate(s), ";

                if (XOR2Count > 0)
                    msg += to_string(XOR2Count) + " 2 input XOR gate(s), ";

                if (XNOR2Count > 0)
                    msg += to_string(XNOR2Count) + " 2 input XNOR gate(s), ";

                if (NOR3Count > 0)
                    msg += to_string(NOR3Count) + " 3 input NOR gate(s), ";
                if (XOR3Count > 0)
                    msg += to_string(XOR3Count) + " 3 input XOR gate(s), ";
                if (SwitchCount > 0)
                    msg += to_string(SwitchCount) + " Switch, ";
                if (LedCount > 0)
                    msg += to_string(LedCount) + " LED, ";
                if (ConnectionCount > 0)
                    msg += to_string(ConnectionCount) + " Connections, ";

               


                // Remove the trailing comma and space
                if (msg.length() > 10) // Length of "Selected: "
                    msg = msg.substr(0, msg.length() - 2);

                pOut->PrintMsg(msg);
            }
        }
    }
    else
    {
        // If clicked on empty area, unselect all figures
        pManager->UnselectAll();
        pOut->PrintMsg("All figures unselected");
    }


    // Update the interface to show the selections
    pManager->UpdateInterface();
}