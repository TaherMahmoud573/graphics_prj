//#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int& x, int& y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetString(Output* pOut)
{
	string userInput = "";
	char c;

	while (true)
	{
		pWind->WaitKeyPress(c);

		// ENTER key (ASCII 13)
		if (c == 13)
		{
			return userInput;
		}

		// esc (ASCII 27)
		if (c == 27)
		{
			return "";
		}

		// Backspace (ASCII 8)
		if (c == 8)
		{
			if (!userInput.empty())
				userInput.pop_back();
		}
		else
		{
			userInput += c;
		}

		// Update the status bar with the current input
		pOut->PrintMsg(userInput);
	}

	return NULL;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check which Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			//int ClickedItemOrder = (x / UI.ToolItemWidth);
			int ClickedItemOrder = ((x + 40) / UI.ToolItemWidth) - 1;
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_EXIT: return EXIT;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_XNOR2: return ADD_XNOR_GATE_2;
			case ITM_Buff: return ADD_Buff;
			case ITM_INV: return ADD_INV;
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_NOR3: return ADD_NOR_GATE_3;
			case ITM_XOR3: return ADD_XOR_GATE_3;




			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight - UI.ToolBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}

		if (y >= UI.height - UI.StatusBarHeight - UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight) {
			
			//int ClickedItemOrder = (x / UI.ToolItemWidth);
			int ClickedItemOrder = ((x + (UI.width - 1.2 * UI.ToolItemWidth)) / UI.ToolItemWidth);

			switch (ClickedItemOrder) {
			case ITM_Switch: return ADD_Switch;
			case ITM_LED: return ADD_LED;
			case ITM_CONNECTION: return ADD_CONNECTION;
			case ITM_Label: return ADD_Label;
			case ITM_EDIT_Label: return EDIT_Label;
			case ITM_SELECT: return SELECT;
			case ITM_DEL: return DEL;
			case ITM_MOVE: return MOVE;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;
			case ITM_SIM_MODE: return SIM_MODE;

			default: return DSN_TOOL;
			}
		}
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{

		if (y >= 0 && y < UI.ToolBarHeight)
		{
			
			//int ClickedItemOrder = ((x - 80 * 4) / UI.ToolItemWidth);
			int ClickedItemOrder;

			if (x > 720 || x < 320)
				ClickedItemOrder = -3;
			else
				ClickedItemOrder = ((x - 80 * 4) / UI.ToolItemWidth);

			switch (ClickedItemOrder)
			{

			case ITM_SIM: return SIM;
			case ITM_TRUTH: return TRUTH;
			case ITM_Create_TruthTable: return Create_TruthTable;
			case ITM_Change_Switch: return Change_Switch;
			case ITM_DSN_MODE: return DSN_MODE;





			default: return DSN_TOOL;


			}

		}

		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;



	}

}



Input::~Input()
{
}