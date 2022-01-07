#include "CardNine.h"

CardNine ::CardNine(CellPosition const& pos) : Card(pos)
{
	cardNumber = 9;
	pOwner = NULL;
}

int CardNine ::Price = 0;

int CardNine ::Fees = 0;



void CardNine::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	if (Price == 0 && Fees == 0)
	{
		pOut->PrintMessage("Please Enter The Price Of The Station ");
		int PriceCheck = pIn->GetInteger(pOut);
		while (PriceCheck < 0)
		{
			pOut->PrintMessage("Please enter a positive number for price");
			PriceCheck = pIn->GetInteger(pOut);
		}
		Price = PriceCheck;
		pOut->PrintMessage("Please Enter The Fees Of The Station ");
		int FeesCheck = pIn->GetInteger(pOut);
		while (FeesCheck < 0)
		{
			pOut->PrintMessage("Please enter a positive number for price");
			FeesCheck = pIn->GetInteger(pOut);
		}
		Fees = FeesCheck;
		pOut->ClearStatusBar();
	}

}

int CardNine::GetPrice()
{
	return Price;
}

void CardNine::SetOwner(Player* pPlayer)              //Sets all Stations with the same number to the player
{
	pOwner = pPlayer;
}

Player* CardNine::GetOwner()
{
	return pOwner;
}



void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	if (pOwner = NULL)
	{
		if (pPlayer->GetWallet() < Price)                                     //Checks if player has enough coins
		{
			pOut->PrintMessage("Can't Buy Card Due to Insufficient Funds");
			return;
		}
		pOut->PrintMessage("You have reached a Station. Would you like to buy it? y/n?");   // Checks if player wants to buy city
		string Answer = pIn->GetSrting(pOut);
		if (Answer != "y" && Answer != "n")
		{
			pOut->PrintMessage("Please enter y for YES and n for NO ");
			string Answer = pIn->GetSrting(pOut);
		}
		pOut->ClearStatusBar();
		if (Answer == "y")                                       //Player Buys Station
		{
			pPlayer->SetWallet(pPlayer->GetWallet() - Price);
			pOwner = pPlayer;
			pGrid->SetAllOwnerCard9(pPlayer);
			pOut->ClearStatusBar();
			return;
		}
		if (Answer == "n")
		{
			pOut->ClearStatusBar();
			return;
		}
	}
	if (pPlayer == pOwner)                       //if player owns the station
	{
		pOut->PrintMessage("Player is The Owner of This Card. Click to Continue ");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	} 
	else                                        //The station is owned by another player so the player pays the fees
	{
		pOut->PrintMessage("You Have Reached an owned Station. Click to Continue ");
		int x, y;
		pIn->GetPointClicked(x, y);
		pPlayer->SetWallet((pPlayer->GetWallet()) - Fees);	// Deduct the fees from the player's wallet
		pOwner->SetWallet((pOwner->GetWallet()) + Fees);		// Add the fees to the owner's wallet

	}
	pOut->ClearStatusBar();

}

void CardNine::Save(ofstream& OutFile, ObjType obj)  //Saves the GameObj parameters to the file
{
	if (obj == card)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << " " << Price << " " << Fees << endl;
	}
}
void CardNine::Load(ifstream& Infile, Grid* pGrid)   //Loads the GameObj parameters to the file
{
	int cellNum;
	Infile >> cellNum >> Price>> Fees;
	CellPosition pos(cellNum);
	position = pos;
}

CardNine::~CardNine()
{

}