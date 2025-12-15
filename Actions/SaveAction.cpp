#include "SaveAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include <fstream>

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp), filename("circuit.txt")
{
}

void SaveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Save: enter filename (without extension) or press Enter for default:");
	string input = pIn->GetString(pOut);
	pOut->ClearStatusBar();

	if (!input.empty()) {
		filename = input;
	}
	// ensure a file extension (use .txt by default)
	if (filename.find('.') == string::npos) {
		filename += ".txt";
	}
}

void SaveAction::Execute()
{
	// get filename from user
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();
	Component** compList = pManager->GetCompList();
	int compCount = pManager->GetCompCount();

	std::ofstream ofs(filename.c_str());
	if (!ofs.is_open()) {
		pOut->PrintMsg("Error: Unable to open file for writing.");
		return;
	}

	// Simple save format: first line = component count
	// then each line: <Type> x1 y1 x2 y2
	ofs << compCount << std::endl;
	for (int i = 0; i < compCount; ++i) {
		GraphicsInfo g = compList[i]->GetParameters();
		ofs << compList[i]->GetType() << " "
			<< g.x1 << " " << g.y1 << " " << g.x2 << " " << g.y2 << std::endl;
	}

	ofs.close();
	pOut->PrintMsg("Saved to " + filename);
}

SaveAction::~SaveAction(void)
{
}

void SaveAction::Undo()
{
}

void SaveAction::Redo()
{
}
