#include "CardTwelve.h"

CardTwelve::CardTwelve(const CellPosition& pos) : Card(pos)
{
	cardNumber = 12; // set the inherited cardNumber data member with the card number (12 here)
}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	int maxstation = 0;
	if (owner9->GetOwner() == pPlayer)
	{
		if(owner9->GetPrice()>maxstation)
		maxstation = owner9->GetPrice();
	}

	if (owner10->GetOwner() == pPlayer)
	{
		if (owner10->GetPrice() > maxstation)
			maxstation = owner10->GetPrice();
	}
	if (owner11->GetOwner() == pPlayer)
	{
		if (owner11->GetPrice() > maxstation)
			maxstation = owner11->GetPrice();
	}

	if (maxstation != 0)
	{
		Player* Poorestplayer = pGrid->PoorestPlayer();
		if (maxstation == owner9->GetPrice())
		{
			owner9->SetOwner(Poorestplayer);
			pGrid->SetAllOwnerCard9(Poorestplayer);
		}
		if (maxstation == owner10->GetPrice())
		{
			owner10->SetOwner(Poorestplayer);
			pGrid->SetAllOwnerCard10(Poorestplayer);
		}
		if (maxstation == owner10->GetPrice())
		{
			owner10->SetOwner(Poorestplayer);
			pGrid->SetAllOwnerCard11(Poorestplayer);
		}
	}

}

void CardTwelve::Save(ofstream& OutFile, ObjType obj)  //Saves the GameObj parameters to the file
{
	if (obj == card)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}
void CardTwelve::Load(ifstream& Infile, Grid* pGrid)   //Loads the GameObj parameters to the file
{
	int cellNum;
	Infile >> cellNum;
	CellPosition pos(cellNum);
	position = pos;
}

CardTwelve::~CardTwelve()
{

}