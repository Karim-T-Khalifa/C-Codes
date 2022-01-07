#include "NewGameAction.h"
#include "Grid.h"

//according to project description of the NewGameAction it: "Restarts players' positions, wallets, and turn returns to player 0."
// so these are our main execution criteria

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
}

void NewGameAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pO = pGrid->GetOutput();
	//notify user of new game start and get confirmation
	pO->PrintMessage("Click anywhere to start a new game");
	pIn->GetCellClicked();
	pO->ClearStatusBar();
}

void NewGameAction::Execute() //execution will be made through the Grid as it has the PlayerList array, and so it can be easily used with the Mode Switches as well
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	pGrid->NewGame();
}

NewGameAction::~NewGameAction()
{
}


