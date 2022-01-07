#include "InputDiceValueAction.h"
#include "Grid.h"
#include "Player.h"

InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) : Action(pApp)
{
}

void InputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	//we need pointers to I/O as follows:
	Input* pIn = pGrid->GetInput();
	Output* pO = pGrid->GetOutput();

	pO->PrintMessage("Enter a dice value (from 1 to 6): ");
	diceVal = pIn->GetInteger(pO); //get integer from user and set dice value to it
	pO->ClearStatusBar(); //clears the status bar after entry

	//need to add a constraint to prevent values greater than 6 or less than 1: 
	while (diceVal > 6 || diceVal < 1)
	{
		pO->PrintMessage("INVALID ENTRY, please try again with a value from 1 to 6:");
		diceVal = pIn->GetInteger(pO);
		pO->ClearStatusBar();
	}
}

void InputDiceValueAction::Execute() //very similar to RollDiceAction
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pO = pGrid->GetOutput();

	//check if the game has ended
	if (pGrid->GetEndGame())
	{
		pO->PrintMessage("Game Over, no more dice values to enter.");
		return;
	}
	//get current player
	Player* currplayer = pGrid->GetCurrentPlayer();
	//move player by the dice value
	currplayer->Move(pGrid, diceVal);
	//advance the current player
	pGrid->AdvanceCurrentPlayer();
}

InputDiceValueAction::~InputDiceValueAction()
{
}
