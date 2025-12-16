#include "LoadAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\Components\AND2.h"
#include "..\Components\OR2.h"
#include "..\Components\BUFF.h"
#include "..\Components\INV.h"
#include "..\Components\NAND2.h"
#include "..\Components\NOR2.h"
#include "..\Components\XOR2.h"
#include "..\Components\XNOR2.h"
#include "..\Components\AND3.h"
#include "..\Components\NOR3.h"
#include "..\Components\XOR3.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"
#include "..\Components\Connection.h"

#include <fstream>
#include <sstream>

LoadAction::LoadAction(ApplicationManager* pApp) : Action(pApp), filename("circuit.txt")
{
}

LoadAction::~LoadAction(void)
{
}

void LoadAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Load: enter filename (without extension) or press Enter for default:");
	string input = pIn->GetString(pOut);
	pOut->ClearStatusBar();

	if (!input.empty()) {
		filename = input;
	}

	if (filename.find('.') == string::npos) {
		filename += ".txt";
	}
}

void LoadAction::Execute()
{
	ReadActionParameters();

	pManager->ClearAllComponents();
	pManager->GetOutput()->ClearDrawingArea();

	Output* pOut = pManager->GetOutput();

	std::ifstream ifs(filename.c_str());
	if (!ifs.is_open()) {
		pOut->PrintMsg("Error: Unable to open file for reading: " + filename);
		return;
	}

	int count = 0;
	ifs >> count;
	if (!ifs || count <= 0) {
		pOut->PrintMsg("File format error or empty file.");
		ifs.close();
		return;
	}

	Component** compList = pManager->GetCompList();

	// Allocate arrays to hold connection entries (no vectors or structs)
	int maxEntries = count;
	int* conn_x1 = new int[maxEntries];
	int* conn_y1 = new int[maxEntries];
	int* conn_x2 = new int[maxEntries];
	int* conn_y2 = new int[maxEntries];
	string* conn_type = new string[maxEntries];
	int connCount = 0;

	for (int i = 0; i < count; ++i) {
		string type;
		GraphicsInfo g;
		ifs >> type >> g.x1 >> g.y1 >> g.x2 >> g.y2;
		if (!ifs) {
			pOut->PrintMsg("File read error.");
			// cleanup
			delete[] conn_x1; delete[] conn_y1; delete[] conn_x2; delete[] conn_y2; delete[] conn_type;
			ifs.close();
			return;
		}

		if (type == "CONNECTION") {
			// store primitive connection entry for later processing
			conn_x1[connCount] = g.x1;
			conn_y1[connCount] = g.y1;
			conn_x2[connCount] = g.x2;
			conn_y2[connCount] = g.y2;
			conn_type[connCount] = type;
			++connCount;
			continue;
		}

		Component* pComp = nullptr;

		if (type == "AND2") {
			pComp = new AND2(g, AND2_FANOUT);
		}
		else if (type == "OR2") {
			pComp = new OR2(g, OR2_FANOUT);
		}
		else if (type == "BUFF") {
			pComp = new BUFF(g, Buff_FANOUT);
		}
		else if (type == "INV") {
			pComp = new INV(g, INV_FANOUT);
		}
		else if (type == "NAND2") {
			pComp = new NAND2(g, NAND2_FANOUT);
		}
		else if (type == "NOR2") {
			pComp = new NOR2(g, NOR2_FANOUT);
		}
		else if (type == "XOR2") {
			pComp = new XOR2(g, XOR2_FANOUT);
		}
		else if (type == "XNOR2") {
			pComp = new XNOR2(g, XNOR2_FANOUT);
		}
		else if (type == "AND3") {
			pComp = new AND3(g, AND3_FANOUT);
		}
		else if (type == "NOR3") {
			pComp = new NOR3(g, NOR3_FANOUT);
		}
		else if (type == "XOR3") {
			pComp = new XOR3(g, XOR3_FANOUT);
		}
		else if (type == "SWITCH" || type == "Switch") {
			pComp = new Switch(g, Switch_FANOUT);
		}
		else if (type == "LED") {
			pComp = new LED(g, Switch_FANOUT);
		}
		else {
			std::ostringstream msg;
			msg << "Unknown component type in file: " << type << " (skipped).";
			pOut->PrintMsg(msg.str());
			continue;
		}

		if (pComp) {
			pManager->AddComponent(pComp);
		}
	}

	// Process stored connections using primitive arrays
	for (int idx = 0; idx < connCount; ++idx) {
		GraphicsInfo GInfo;
		GInfo.x1 = conn_x1[idx];
		GInfo.y1 = conn_y1[idx];
		GInfo.x2 = conn_x2[idx];
		GInfo.y2 = conn_y2[idx];

		int CompCount = pManager->GetCompCount();
		Component** CompList = pManager->GetCompList();

		OutputPin* srcPin = nullptr;
		InputPin* dstPin = nullptr;
		int srcIndex = -1, dstIndex = -1;
		int dstInputIndex = -1;

		for (int j = 0; j < CompCount; ++j) {
			GraphicsInfo compParam = CompList[j]->GetParameters();
			if (GInfo.x1 >= compParam.x1 && GInfo.x1 <= compParam.x2 &&
				GInfo.y1 >= compParam.y1 && GInfo.y1 <= compParam.y2) {
				srcPin = CompList[j]->GetOutputPin();
				srcIndex = j;
				break;
			}
		}
		if (!srcPin) {
			pOut->PrintMsg("Warning: Connection source not found. Connection skipped.");
			continue;
		}

		for (int j = 0; j < CompCount; ++j) {
			GraphicsInfo compParam = CompList[j]->GetParameters();
			if (GInfo.x2 >= compParam.x1 && GInfo.x2 <= compParam.x2 &&
				GInfo.y2 >= compParam.y1 && GInfo.y2 <= compParam.y2) {
				InputPin* pins = CompList[j]->GetInputPin();
				int nInputs = CompList[j]->GetNumberOfInputs();
				bool foundFree = false;
				for (int k = 0; k < nInputs; ++k) {
					if (!pins[k].isConnected()) {
						dstPin = &pins[k];
						dstIndex = j;
						dstInputIndex = k;
						foundFree = true;
						break;
					}
				}
				if (!foundFree) {
					pOut->PrintMsg("Warning: Destination has no free input pins. Connection skipped.");
				}
				break;
			}
		}
		if (!dstPin) {
			continue;
		}

		if (srcPin->checkAvailability()) {
			Connection* pConn = new Connection(GInfo, srcPin, dstPin);
			if (!srcPin->ConnectTo(pConn)) {
				pOut->PrintMsg("Warning: Source cannot accept more connections. Connection skipped.");
				delete pConn;
				continue;
			}
			dstPin->setConnection(pConn);
			dstPin->setComponent(pConn);
			pManager->AddComponent(pConn);
			pConn->setSourcePin(srcPin);
			pConn->setDestPin(dstPin);
			pConn->Operate();
		}
		else {
			pOut->PrintMsg("Warning: Source fan-out exceeded. Connection skipped.");
			continue;
		}
	}

	// cleanup allocated arrays
	delete[] conn_x1;
	delete[] conn_y1;
	delete[] conn_x2;
	delete[] conn_y2;
	delete[] conn_type;

	ifs.close();

	pManager->UpdateInterface();
	pOut->PrintMsg("Loaded from " + filename);
}

void LoadAction::Undo()
{
}

void LoadAction::Redo()
{
}