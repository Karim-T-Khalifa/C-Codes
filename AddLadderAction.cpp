#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"


AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

    

	///TODO: Make the needed validations on the read parameters
	if (startPos.IsValidCell() == false || endPos.IsValidCell() == false)           ////   Checks if the current cell position (vCell and hCell) both are valid  
	{
		pOut->PrintMessage("Invalid Cells Clicked");
		pOut->ClearStatusBar();
		return;
	}
	
	/*if (startPos.HCell() != endPos.HCell())          //// Check if the Ladder is vertical
	{
		pOut->PrintMessage("Invalid Cells ,End cell and start cell are not in the same column");
		pOut->ClearStatusBar();
		return;
	}
	if (endPos.VCell() >= startPos.VCell())         ////  Check if the startPos is greater than endPos  
	{
		pOut->PrintMessage("Invalid Cells ,End cell cannot be smaller than start cell");
		pOut->ClearStatusBar();
		return;
	}
	Ladder* passedLadder = new Ladder(startPos, endPos);            ////  new variable of type ladder to store the Cellposition to check if it overlapp 
	if (pGrid->IsOverlapping(passedLadder) == true)
	{
		pOut->PrintMessage("Invalid Cells ,two ladders cannot overlap");
		pOut->ClearStatusBar();
		return;
	}

	for (int i= endPos.VCell();i<= startPos.VCell();i++)     /// As vertical Check was already done before
	{                                        ///   Check that end cell cannot be a start of another ladder , check is made vertically through the Ladder
		CellPosition CheckC1(i, endPos.HCell());
		Cell CheckC1cell(CheckC1);
		if (CheckC1cell.HasLadder() != NULL)
		{
			Ladder* LaddCheck = CheckC1cell.HasLadder();
			if (endPos.VCell() == LaddCheck->GetPosition().VCell() || LaddCheck->GetEndPosition().VCell() ==  startPos.VCell())
			{
				pOut->PrintMessage("Invalid Cells ,end cell cannot be a start of another ladder");
				pOut->ClearStatusBar();
				return;
			}
		}
	}
	                                                       
	for (int i = endPos.VCell(); i <= startPos.VCell(); i++)     /// As vertical Check was already done before
	{                                        ///   Check that end cell cannot be a start of another snake , check is made vertically through the Ladder
		CellPosition CheckC1(i, endPos.HCell());
		Cell CheckC1cell(CheckC1);
		if (CheckC1cell.HasSnake() != NULL)
		{
			Snake* SnakeCheck = CheckC1cell.HasSnake();            
			if (endPos.VCell() == SnakeCheck->GetPosition().VCell() || SnakeCheck->GetEndPosition().VCell()== startPos.VCell())
			{
				pOut->PrintMessage("Invalid Cells ,end cell cannot be a start of another Snake");
				pOut->ClearStatusBar();
				return;
			}
		}
	}


	if (startPos.VCell() == 0)                            ///  1st Row check
	{
		pOut->PrintMessage("Invalid Cells ,Start cell cannot be in the first row");
		pOut->ClearStatusBar();
		return;
	}
	
	if (endPos.VCell() == NumVerticalCells)        /// Last Row Check
	{
		pOut->PrintMessage("Invalid Cells ,End cell cannot be in the last row");
		pOut->ClearStatusBar();
		return;
	}

	if (startPos.VCell() == NumVerticalCells && startPos.HCell() ==0)           ///  First Cell Check
	{
		pOut->PrintMessage("Invalid Cells ,First Cell can not contain Game-Object");
		pOut->ClearStatusBar();
		return;
	}

	CellPosition OverlappCard(startPos.HCell(),startPos.VCell());             /// check if the startcell of the ladder has card
	Cell CardCheck(OverlappCard);
	if (CardCheck.HasCard() != NULL)
	{
		pOut->PrintMessage("Invalid, The start cell of the ladder can not be the same of a CARD");
		pOut->ClearStatusBar();
		return;
	}
	*/
	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
