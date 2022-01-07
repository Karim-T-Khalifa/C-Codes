#include "AddSnakeAction.h"
#include "Input.h"
#include "Output.h"
#include "Snake.h"
#include "Ladder.h"



AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();



	///TODO: Make the needed validations on the read parameters
	if (startPos.IsValidCell() == false || endPos.IsValidCell() == false)           ////   Checks if the current cell position (vCell and hCell) both are valid  
	{
		pOut->PrintMessage("Invalid Cells Clicked");
		pOut->ClearStatusBar();
		return;
	}
	if (startPos.HCell() != endPos.HCell())          //// Check if the Snake is vertical 
	{
		pOut->PrintMessage("Invalid Cells ,End cell and start cell are not in the same column");
		pOut->ClearStatusBar();
		return;
	}
	if (endPos.VCell() <= startPos.VCell())         ////  Check if the startPos is less than endPos  
	{
		pOut->PrintMessage("Invalid Cells ,End cell cannot be smaller than start cell");
		pOut->ClearStatusBar();
		return;
	}
	Snake* passedSnake = new Snake(startPos, endPos);            ////  Overlapping Check , new variable of type Snake to store the Cellposition to check if it overlapp 
	if (pGrid->IsOverlapping(passedSnake) == true)
	{
		pOut->PrintMessage("Invalid Cells ,two Snakes cannot overlap");
		pOut->ClearStatusBar();
		return;
	}

	for (int i = startPos.VCell(); i <=endPos.VCell(); i++)     /// As vertical Check was already done before
	{                                        ///   Check that end cell cannot be a start of another ladder, check is made vertically through the Snake
		CellPosition CheckC1(i, endPos.HCell());
		Cell CheckC1cell(CheckC1);
		if (CheckC1cell.HasSnake() != NULL)
		{
			Snake* SnakeCheck = CheckC1cell.HasSnake();
			if (endPos.VCell() == SnakeCheck->GetPosition().VCell() || SnakeCheck->GetEndPosition().VCell() == startPos.VCell())
			{
				pOut->PrintMessage("Invalid Cells ,end cell cannot be a start of another Snake");
				pOut->ClearStatusBar();
				return;
			}
		}
	}

	for (int i = startPos.VCell(); i <= endPos.VCell(); i++)     /// As vertical Check was already done before
	{                                        ///   Check that end cell cannot be a start of another Ladder, check is made vertically through the Snake
		CellPosition CheckC1(i, endPos.HCell());
		Cell CheckC1cell(CheckC1);
		if (CheckC1cell.HasLadder() != NULL)
		{
			Ladder* LadderCheck = CheckC1cell.HasLadder();              
			if (endPos.VCell() == LadderCheck->GetPosition().VCell() || LadderCheck->GetEndPosition().VCell() == startPos.VCell())
			{
				pOut->PrintMessage("Invalid Cells ,end cell cannot be a start of another ladder");
				pOut->ClearStatusBar();
				return;
			}
		}
	}


	if (endPos.VCell() == 0)                            ///  1st Row check
	{
		pOut->PrintMessage("Invalid Cells ,End Cell cannot be in the first row");
		pOut->ClearStatusBar();
		return;
	}

	if (startPos.VCell() == NumVerticalCells)        /// Last Row Check
	{
		pOut->PrintMessage("Invalid Cells ,Start cell cannot be in the last row");
		pOut->ClearStatusBar();
		return;
	}

	if (endPos.VCell() == NumVerticalCells && startPos.HCell() == 0)           ///  First Cell Check
	{
		pOut->PrintMessage("Invalid Cells ,First Cell can not contain Game-Object");
		pOut->ClearStatusBar();
		return;
	}

	CellPosition OverlappCard(startPos.HCell(), startPos.VCell());
	Cell CardCheck(OverlappCard);
	if (CardCheck.HasCard() != NULL)
	{
		pOut->PrintMessage("Invalid, The start cell of the ladder can not be the same of a CARD");
		pOut->ClearStatusBar();
		return;
	}

	// Clear messages
	pOut->ClearStatusBar();
}
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Snake* pSnake = new Snake(startPos, endPos);

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
