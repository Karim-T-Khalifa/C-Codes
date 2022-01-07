#include "CardFour.h"



CardFour::CardFour(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (4 here)
}

CardFour::~CardFour()
{
}

void CardFour::ReadCardParameters(Grid* pGrid)
{


	// Get a Pointer to the Input / Output Interfaces from the Grid
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();



	pOut->PrintMessage("New CardFour, click to continue");
	int x, y;
	pIn->GetPointClicked(x, y);


	// Clear the status bar
	pOut->ClearStatusBar();
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{

	//Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);

	pPlayer->SetPreventFromRolling(true);

}

void CardFour::Save(ofstream& OutFile, ObjType obj)
{
	if (obj == card)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardFour::Load(ifstream& Infile, Grid* pGrid)
{
	int cellNum;
	Infile >> cellNum;
	CellPosition pos(cellNum);
	position = pos;
}
