#include "CardSix.h"
#include "Ladder.h"
#include "Snake.h"


CardSix::CardSix(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (6 here)
}

CardSix::~CardSix()
{
}

void CardSix::ReadCardParameters(Grid* pGrid)
{


	// Get a Pointer to the Input / Output Interfaces from the Grid
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();


	
	pOut->PrintMessage("New CardSix, please enter a cell number");
	
	cellNumber = pIn->GetInteger(pOut);


	// A cell number between 1 and 99 should be entered
	while (cellNumber < 1 || cellNumber >99)
	{
		pOut->PrintMessage("Please enter a correct cell number");
		cellNumber = pIn->GetInteger(pOut);
	}
}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{

	//Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);

	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	CellPosition cellPos = cellPos.GetCellPositionFromNum(cellNumber);    // Get cell position of entered cell number 

	pGrid->UpdatePlayerCell(pPlayer, cellNumber);

	Cell* pCell = pPlayer->GetCell();

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

void CardSix::Save(ofstream& OutFile, ObjType obj)
{
	if (obj == card)
	{
		OutFile << cardNumber << " " << position.GetCellNum()<<" " << cellNumber << endl;
	}
}

void CardSix::Load(ifstream& Infile, Grid* pGrid)
{
	int cellNum;
	Infile >> cellNum>> cellNumber;
	CellPosition pos(cellNum);
	position = pos;
}

