#include "Output.h"

#include <string>
using namespace std;

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLACK;
	UI.ConnColor = GREY;
	UI.MsgColor = BLACK;
	UI.BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(BLACK,3);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	// Set the Message offset from the Status Bar
	int MsgX = 0;
	int MsgY = UI.StatusBarHeight;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
void Output::ClearToolBar()const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	pWind->DrawRectangle(0, UI.height - UI.ToolBarHeight - UI.StatusBarHeight - 1, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (design) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight - UI.ToolBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2_M.jpg";
	MenuItemImages[ITM_OR2] = "images\\Menu\\Menu_OR2_M.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit_M.jpg";

	//TODO: Prepare image for each menu item and add it to the list
	MenuItemImages[ITM_Buff] = "images\\Menu\\Menu_BUFF_M.jpg";
	MenuItemImages[ITM_INV] = "images\\Menu\\Menu_INV_M.jpg";
	MenuItemImages[ITM_NAND2] = "images\\Menu\\Menu_NAND2_M.jpg";
	MenuItemImages[ITM_NOR2] = "images\\Menu\\Menu_NOR2_M.jpg";
	MenuItemImages[ITM_XOR2] = "images\\Menu\\Menu_XOR2_M.jpg";
	MenuItemImages[ITM_XNOR2] = "images\\Menu\\Menu_XNOR2_M.jpg";
	MenuItemImages[ITM_AND3] = "images\\Menu\\Menu_AND3_M.jpg";
	MenuItemImages[ITM_NOR3] = "images\\Menu\\Menu_NOR3_M.jpg";
	MenuItemImages[ITM_XOR3] = "images\\Menu\\Menu_XOR3_M.jpg";
	MenuItemImages[ITM_Switch] = "images\\Menu\\Menu_SWITCH_M.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\Menu_LED_M.jpg";
	MenuItemImages[ITM_CONNECTION] = "images\\Menu\\Menu_CONNECT_M.jpg";

	MenuItemImages[ITM_Label] = "images\\Menu\\Menu_LABEL_M.jpg";
	MenuItemImages[ITM_EDIT_Label] = "images\\Menu\\Menu_EDITLABEL_M.jpg";

	MenuItemImages[ITM_SELECT] = "images\\Menu\\Menu_SELECT_M.jpg";
	MenuItemImages[ITM_DEL] = "images\\Menu\\Menu_DELETE_M.jpg";
	MenuItemImages[ITM_MOVE] = "images\\Menu\\Menu_MOVE_M.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\Menu_SAVE_M.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\Menu_LOAD_M.jpg";

	MenuItemImages[ITM_UNDO] = "images\\Menu\\Menu_UNDO_M.jpg";
	MenuItemImages[ITM_REDO] = "images\\Menu\\Menu_REDO_M.jpg";

	MenuItemImages[ITM_SIM_MODE] = "images\\Menu\\Menu_SIMULATION_M.jpg";
	
	//Draw menu item one image at a tim
	for (int i = 0; i < ITM_DSN_CNT/2; i++)
		pWind->DrawImage(MenuItemImages[i], (i * UI.ToolItemWidth) + 40, 0, UI.ToolItemWidth, UI.ToolBarHeight);

	for (int i = ITM_DSN_CNT / 2; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], (i - ITM_DSN_CNT / 2) * UI.ToolItemWidth, UI.height - UI.StatusBarHeight - UI.ToolBarHeight, UI.ToolItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 0);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight - UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight - UI.ToolBarHeight);
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	string MenuItemImages[ITM_SIM_CNT];

	MenuItemImages[ITM_SIM] = "images\\Menu\\Menu_SIM_M.jpg";

	MenuItemImages[ITM_TRUTH] = "images\\Menu\\Menu_TRUTHTABLE_M.jpg";

	MenuItemImages[ITM_Create_TruthTable] = "images\\Menu\\Menu_TRUTHTABLE_M.jpg";    //Create Truth Table of the Circuit-----------------------------------------SM

	MenuItemImages[ITM_Change_Switch] = "images\\Menu\\Menu_CHANGESWITCH_M.jpg";        //Change Switch Status in Simulation Mode-----------------------------------SM

	MenuItemImages[ITM_DSN_MODE] = "images\\Menu\\Menu_DESIGN_M.jpg";

	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], (i * UI.ToolItemWidth) + 4*80, 0, UI.ToolItemWidth, UI.ToolBarHeight);
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}


//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND2_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
	//Hello.
}

//TODO: Add similar functions to draw all components
void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2_M.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.OR2_Width, UI.OR2_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NAND2_Width, UI.NAND2_Height);
}

void Output::DrawBUFF(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_BUFF_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_BUFF_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.BUFF_Width, UI.BUFF_Height);
}

void Output::DrawINV(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_INV_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_INV_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.INV_Width, UI.INV_Height);
}


void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NOR2_Width, UI.NOR2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR2_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XOR2_Width, UI.XOR2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XNOR2_Width, UI.XNOR2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND3_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND3_Width, UI.AND3_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.NOR3_Width, UI.NOR3_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.XOR3_Width, UI.XOR3_Height);
}

void Output::DrawSwitch(GraphicsInfo r_GfxInfo, bool isOn, bool selected) const
{
    string GateImage;

    // Use new ON images when isOn==true, otherwise use existing OFF images.
    if (isOn)
    {
        if (selected)
            GateImage = "Images\\Gates\\Gate_SWITCH_C_Hi_M.jpg";
        else
            GateImage = "Images\\Gates\\Gate_SWITCH_C_M.jpg";
    }
    else
    {
        if (selected)
            GateImage = "Images\\Gates\\Gate_SWITCH_Hi_O_M.jpg"; // existing highlighted OFF image
        else
            GateImage = "Images\\Gates\\Gate_SWITCH_O_M.jpg";    // existing OFF image
    }

    // Draw the chosen image at the switch rectangle
    pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Switch_Width, UI.Switch_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_LED_Hi_M.jpg";
	else
		GateImage = "Images\\Gates\\Gate_LED_M.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.LED_Width, UI.LED_Height);
}

//TODO: Add similar functions to draw all components

void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	//TODO: Add code to draw connection
	if (selected)
		pWind->SetPen(UI.SelectColor, 3);
	else
		pWind->SetPen(UI.ConnColor, 3);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, (r_GfxInfo.x2 + r_GfxInfo.x1)/2, r_GfxInfo.y1);
	pWind->DrawLine((r_GfxInfo.x2 + r_GfxInfo.x1) / 2, r_GfxInfo.y1, (r_GfxInfo.x2 + r_GfxInfo.x1) / 2, r_GfxInfo.y2);
	pWind->DrawLine((r_GfxInfo.x2 + r_GfxInfo.x1) / 2, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
}
void Output::DrawString(int x, int y, string text) const
{
	pWind->SetPen(BLACK, 1);
	pWind->DrawString(x, y, text);
}
Output::~Output()
{
	delete pWind;
}
