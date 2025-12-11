#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	
	static const int	width = 1055, height = 750,	//Window width and height
						wx = 15 , wy = 15,			//Window starting coordinates
						StatusBarHeight = 50,	//Status Bar Height
						ToolBarHeight = 80,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
						SimBarWidth = 80,
						SimItemHeight = 80,
						ToolItemWidth = 80;		//Width of each item in toolbar menu

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Back ground color


	//This should be calculated accurately because it will be used later to create connections between gates
	//For now, we will assume that rect width = 50 and height = 50
	static const int	AND2_Width = 100,		//AND2 Gate Image default width
						AND2_Height = 100,		//AND2 Gate Image default height
						BUFF_Width = 100,
						BUFF_Height = 100,
						INV_Width = 100,
						INV_Height = 100,
						OR2_Width = 100,
						OR2_Height = 100,
						NAND2_Width = 100,
						NAND2_Height = 100,
						NOR2_Width = 100,
						NOR2_Height = 100,
						XOR2_Width = 100,
						XOR2_Height = 100,
						XNOR2_Width = 100,
						XNOR2_Height = 100,
						AND3_Width = 100,
						AND3_Height = 100,
						NOR3_Width = 100,
						NOR3_Height = 100,
						XOR3_Width = 100,
						XOR3_Height = 100,
						Switch_Width = 100,
						Switch_Height = 100,
						LED_Width = 100,
						LED_Height = 100;

}UI;	//create a single global object UI

#endif