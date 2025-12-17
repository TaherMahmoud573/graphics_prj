#ifndef _CONNECTION_H
#define _CONNECTION_H

#include "Component.h"
#include "InputPin.h"
#include "OutputPin.h"

class Connection : public Component
{
private:
    OutputPin* SrcPin;   //The Source pin of this connection (an output pin of certain Component)
    InputPin* DstPin;    //The Destination pin of this connection (an input pin of certain Component)

public:
    Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin, InputPin *pDstPin);

    virtual void Operate() override;   //Calculates the output according to the inputs
    virtual void Draw(Output* pOut) override; //for each component to Draw itself

    void setSourcePin(OutputPin *pSrcPin);
    void setDestPin(InputPin *pDstPin);

    // Existing public accessors
    virtual OutputPin* GetOutputPin();
    virtual InputPin* GetInputPin();

    // Add the camelCase accessors that other code expects
    OutputPin* getSourcePin() const;
    InputPin* getDestPin() const;

    virtual int GetOutPinStatus() override;    //returns status of outputpin if LED, return -1
    virtual int GetInputPinStatus(int n) override; //returns status of Inputpin # n if SWITCH, return -1

    virtual void setInputPinStatus(int n, STATUS s) override; //set status of Inputpin # n, to be used by connection class.

    virtual std::string GetInfo() const override;

    // Overrides from Component
    virtual void Move(int dx, int dy) override;
    virtual Point GetCenter() const override;

    // Correct override of Clone for Connection (declaration only - implementation goes to .cpp)
    virtual Component* Clone(Point P) const override;
};

#endif

