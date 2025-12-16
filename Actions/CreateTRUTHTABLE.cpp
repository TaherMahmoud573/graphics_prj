#include "CreateTRUTHTABLE.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"
#include <sstream>

CreateTRUTHTABLE::CreateTRUTHTABLE(ApplicationManager* pApp) :Action(pApp)
{
}

CreateTRUTHTABLE::~CreateTRUTHTABLE(void)
{
}

void CreateTRUTHTABLE::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Truth Table: Click where you want the table to appear");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void CreateTRUTHTABLE::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// Get click coordinates
	ReadActionParameters();

	int CompCount = pManager->GetCompCount();
	Component** CompList = pManager->GetCompList();

	// Collect switches and LEDs using plain arrays
	Switch** switches = new Switch*[CompCount];
	int switchCount = 0;
	LED** leds = new LED*[CompCount];
	int ledCount = 0;

	for (int i = 0; i < CompCount; ++i) {
		Component* c = CompList[i];
		if (!c) continue;
		std::string t = c->GetType();
		if (t == "SWITCH") {
			Switch* s = dynamic_cast<Switch*>(c);
			if (s) switches[switchCount++] = s;
		} else if (t == "LED") {
			LED* l = dynamic_cast<LED*>(c);
			if (l) leds[ledCount++] = l;
		}
	}

	if (switchCount == 0 || ledCount == 0) {
		if (switchCount == 0)
			pOut->PrintMsg("Truth Table requires at least one SWITCH.");
		else
			pOut->PrintMsg("Truth Table requires at least one LED.");
		delete[] switches; delete[] leds;
		return;
	}

	// Safety cap
	const int MAX_SWITCHES = 20;
	if (switchCount > MAX_SWITCHES) {
		std::ostringstream ss;
		ss << "Too many switches (" << switchCount << "). Limit is " << MAX_SWITCHES << ".";
		pOut->PrintMsg(ss.str());
		delete[] switches; delete[] leds;
		return;
	}

	// Save original switch states
	int* origStates = new int[switchCount];
	for (int i = 0; i < switchCount; ++i) origStates[i] = switches[i]->GetOutPinStatus();

	pOut->ClearDrawingArea();

	// Header
	std::ostringstream header;
	for (int i = 0; i < switchCount; ++i) {
		if (i) header << " ";
		header << "S" << i;
	}
	header << " |";
	for (int j = 0; j < ledCount; ++j) {
		header << " L" << j;
	}

	const int lineHeight = 18;
	int x = Cx;
	int y = Cy;

	pOut->DrawString(x, y, header.str());
	y += lineHeight;

	// Number of combinations
	unsigned int combos = 1u << switchCount;

	for (unsigned int row = 0; row < combos; ++row) {
		// Set switches according to bits of row (MSB -> S0)
		for (int i = 0; i < switchCount; ++i) {
			int desired = ((row >> (switchCount - 1 - i)) & 1) ? HIGH : LOW;
			if (switches[i]->GetOutPinStatus() != desired) {
				switches[i]->Toggle(nullptr); // toggle without immediate redraw
			}
		}

		// Propagate signals (same technique as Simulate)
		int margin = CompCount + 3;
		for (int it = 0; it < margin; ++it) {
			for (int k = 0; k < CompCount; ++k) {
				if (CompList[k]->GetType() != "CONNECTION")
					CompList[k]->Operate();
			}
			for (int k = 0; k < CompCount; ++k) {
				if (CompList[k]->GetType() == "CONNECTION")
					CompList[k]->Operate();
			}
		}

		// Ensure LED internal state updated
		for (int k = 0; k < CompCount; ++k) {
			LED* l = dynamic_cast<LED*>(CompList[k]);
			if (l) l->UpdateLedState();
		}

		// Build row string
		std::ostringstream rowss;
		for (int i = 0; i < switchCount; ++i) {
			if (i) rowss << " ";
			int s = switches[i]->GetOutPinStatus();
			rowss << (s == HIGH ? '1' : '0');
		}
		rowss << " |";
		for (int j = 0; j < ledCount; ++j) {
			rowss << " ";
			int lv = leds[j]->GetOutPinStatus();
			if (lv == -1 && leds[j]->GetNumberOfInputs() > 0) {
				lv = leds[j]->GetInputPinStatus(1);
			}
			rowss << (lv == HIGH ? '1' : '0');
		}

		pOut->DrawString(x, y, rowss.str());
		y += lineHeight;
	}

	// Restore original switch output statuses (again directly on output pins)		
	for (int i = 0; i < switchCount; ++i) {
		if (switches[i]->GetOutPinStatus() != origStates[i]) {
			switches[i]->Toggle(nullptr);
		}
	}

	// Cleanup
	delete[] origStates;
	delete[] switches;
	delete[] leds;


	pManager->UpdateInterface();
	pOut->PrintMsg("Truth table generated.");
}

void CreateTRUTHTABLE::Undo()
{
}

void CreateTRUTHTABLE::Redo()
{
}

