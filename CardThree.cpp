#include "CardThree.h"
#include "time.h"

CardThree::CardThree(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (3 here)
}

CardThree::~CardThree()
{
}

void CardThree::ReadCardParameters(Grid* pGrid)
{


	// Get a Pointer to the Input / Output Interfaces from the Grid
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();



	pOut->PrintMessage("New CardThree, Click to continue");
	int x, y;
	pIn->GetPointClicked(x,y);


	// Clear the status bar
	pOut->ClearStatusBar();
}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{

	//Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);

	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("You have an extra dice roll, click to continue");
	int x,y;
	pIn->GetPointClicked(x,y);
	pOut->ClearStatusBar();
	
	// 2- Generate a random number from 1 to 6 
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed

	pPlayer->Move(pGrid, diceNumber);
	
}

void CardThree::Save(ofstream& OutFile, ObjType obj)
{
	if (obj == card)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardThree::Load(ifstream& Infile, Grid* pGrid)
{
	int cellNum;
	Infile >> cellNum;
	CellPosition pos(cellNum);
	position = pos;
}
