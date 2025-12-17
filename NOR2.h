#ifndef _NOR2_H
#define _NOR2_H

#include "Gate.h"
#include <string>

// 2-input NOR gate
class NOR2 : public Gate
{
public:
    NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
    NOR2(const GraphicsInfo &r_GfxInfo);

    // Basic functionality
    virtual void Operate() override;
    virtual void Draw(Output* pOut) override;

    virtual int GetOutPinStatus() override;
    virtual int GetInputPinStatus(int n) override;
    virtual void setInputPinStatus(int n, STATUS s) override;

    // Cloning and info
    virtual Component* Clone(Point P) const override;
    virtual std::string GetInfo() const override;
};

 #endif