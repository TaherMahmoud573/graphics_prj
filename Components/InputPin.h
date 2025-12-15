#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Component; //Forward class declaration
class Connection; // forward

class InputPin : public Pin	//inherited from class Pin
{
	Component* pComp; //Component at which this pin is associated
	Connection* pConn; // Connection attached to this input pin (nullptr if free)
public:
	InputPin();
	void setComponent(Component* pCmp);	//sets the component of this input pin
	Component* getComponent();	//returns the component of this input pin
	bool isConnected() const;                // true if an incoming connection is attached
	void setConnection(Connection* pConnection); // attach connection (marks as used)
	Connection* getConnection() const;       // returns attached connection (or nullptr)

};

#endif