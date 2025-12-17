#ifndef _XOR3_H
#define _XOR3_H

/*
  Class XOR3
  ---------
  represent the 3-input XOR gate
*/

#include "Gate.h"
#include <string>

class XOR3 : public Gate
{
public:
    XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut);

    // Core behavior
    virtual void Operate() override;    // Calculates the output of the XOR3 gate
    virtual void Draw(Output* pOut) override;   // Draws 3-input gate

    // Pin status accessors / mutators
    virtual int GetOutPinStatus() override;
    virtual int GetInputPinStatus(int n) override;
    virtual void setInputPinStatus(int n, STATUS s) override;

    // Component metadata
    virtual std::string GetInfo() const override;
    virtual bool IsInside(Point P) const override;

    // Cloning (use Gate's pin accessors from base class - no re-declaration needed)
    virtual Component* Clone(Point P) const override;
};

#endif