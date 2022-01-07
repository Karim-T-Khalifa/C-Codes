#include "CardSeven.h"
#include "Player.h"
#include "Grid.h"
#include "Cell.h"
#include <fstream>

CardSeven::CardSeven(const CellPosition& pos) : Card(pos)
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (7 here)
}


void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Player* closestNextPlayer = pGrid->ReturnNextPlayer();
	if (closestNextPlayer != NULL)
	{
	 // returns pointer to the cell of pPlayer
		CellPosition Position;
		int cellnumber = 1;
		Position = Position.GetCellPositionFromNum(cellnumber); // returns the new cell position of the pPlayer
		pGrid->UpdatePlayerCell(closestNextPlayer, Position); // the effect of card Six
	}
}

void CardSeven::Save(ofstream& OutFile, ObjType obj)
{
	if (obj == card)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardSeven::Load(ifstream& Infile, Grid* pGrid)
{
	int cellNum;
	Infile >> cellNum;
	CellPosition pos(cellNum);
	position = pos;
}
CardSeven::~CardSeven()
{

}
