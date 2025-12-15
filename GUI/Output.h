#ifndef OUTPUT_H
#define OUTPUT_H
#include "..\Defs.h"
#include "Input.h"
#include <string>

class window; // Forward declaration for window class

class Output
{
private:
    window* pWind; // Pointer to the Graphics Window

public:
    Output();
    Input* CreateInput() const;

    window* CreateWind(int wd, int h, int x, int y) const;
    void ChangeTitle(string Title) const;

    void CreateStatusBar() const;
    void PrintMsg(string msg) const;
    void ClearStatusBar() const;
    void ClearToolBar() const;
    void ClearDrawingArea() const;
    void CreateDesignToolBar() const;
    void CreateSimulationToolBar() const;

    // Components drawing functions
    void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawBUFF(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawINV(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;

    void DrawSwitch(GraphicsInfo r_GfxInfo, bool isOn = false, bool selected = false) const;
    void DrawLED(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawConnection(GraphicsInfo r_GfxInfo, bool selected = false) const;
    void DrawString(int x, int y, string text) const;

    ~Output();
};

#endif