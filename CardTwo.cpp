#include "CardTwo.h"
#include "Ladder.h"


CardTwo::CardTwo(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (2 here)
}

CardTwo::~CardTwo()
{
}

void CardTwo::ReadCardParameters(Grid* pGrid)
{


	// Get a Pointer to the Input / Output Interfaces from the Grid
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();


	pOut->PrintMessage("New CardTwo, click to continue");
	int x, y;
	pIn->GetPointClicked(x, y);
	

	// Clear the status bar
	pOut->ClearStatusBar();
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{


	//Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);    

	Cell* pCell = pPlayer->GetCell();             //Return pointer to cell of pPlayer
	CellPosition pos = pCell->GetCellPosition();  //Return cell position of pPlayer

	if (pGrid->GetNextLadder(pos))
	{
		pGrid->UpdatePlayerCell(pPlayer, ((pGrid->GetNextLadder(pos))->GetPosition()));
	}

	(pGrid->GetNextLadder(pos))->Apply(pGrid, pPlayer);
}

void CardTwo::Save(ofstream& OutFile, ObjType obj)
{
	if (obj == card)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardTwo::Load(ifstream& Infile, Grid* pGrid)
{
	int cellNum;
	Infile >> cellNum;
	CellPosition pos(cellNum);
	position = pos;
}
