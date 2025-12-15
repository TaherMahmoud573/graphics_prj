#include "InputPin.h"

InputPin::InputPin()
{
	pComp = nullptr;
	pConn = nullptr;}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}

bool InputPin::isConnected() const
{
	return pConn != nullptr;
}

void InputPin::setConnection(Connection* pConnection)
{
	pConn = pConnection;
}

Connection* InputPin::getConnection() const
{
	return pConn;
}