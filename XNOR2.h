#ifndef _XNOR2_H
#define _XNOR2_H

#include "Gate.h"

// 2-input XNOR gate
class XNOR2 : public Gate
{
public:
    XNOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
    XNOR2(const GraphicsInfo &r_GfxInfo); // default ctor (defined in XNOR2.cpp)

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