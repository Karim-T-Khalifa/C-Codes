#include "CardFive.h"
#include "Ladder.h"
#include "Snake.h"

CardFive::CardFive(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (5 here)
}

CardFive::~CardFive()
{
}

void CardFive::ReadCardParameters(Grid* pGrid)
{


	// Get a Pointer to the Input / Output Interfaces from the Grid
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();



	pOut->PrintMessage("New CardFive, Click to continue");
	int x, y;
	pIn->GetPointClicked(x, y);


	// Clear the status bar
	pOut->ClearStatusBar();
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{

	//Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);

	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("You have an extra dice roll, click to continue");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();


	Cell* pCell = pPlayer->GetCell();             //Return pointer to cell of pPlayer
	CellPosition pos = pCell->GetCellPosition();  //Return cell position of pPlayer

	int cellNum = (pos.GetCellNum() - pPlayer->Get_justRolledDiceNum());  //Player moves to this cell number

	pos = pos.GetCellPositionFromNum(cellNum);    // New cell position of cell number

	pGrid->UpdatePlayerCell(pPlayer, cellNum);



	if (pCell->HasLadder())
	{
		(pCell->HasLadder())->Apply(pGrid, pPlayer);
	}

	if (pCell->HasSnake())
	{
		(pCell->HasSnake())->Apply(pGrid, pPlayer);
	}

	if (pCell->HasCard())
	{
		(pCell->HasCard())->Apply(pGrid, pPlayer);
	}
}


void CardFive::Save(ofstream& OutFile, ObjType obj)
{
	if (obj == card)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardFive::Load(ifstream& Infile, Grid* pGrid)
{
	int cellNum;
	Infile >> cellNum;
	CellPosition pos(cellNum);
	position = pos;
}
