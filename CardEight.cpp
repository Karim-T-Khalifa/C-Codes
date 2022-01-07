#include "CardEight.h"
CardEight::CardEight(CellPosition const& pos) : Card(pos)
{
	cardNumber = 8;
}

int CardEight::FreeFees = 0;

void CardEight::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	if (FreeFees == 0)
	{
		pOut->PrintMessage("Please Enter The FreeFees for the prison ");
		int FreeFeesCheck = pIn->GetInteger(pOut);
		while (FreeFeesCheck < 0)
		{
			pOut->PrintMessage("Please enter a positive number for FreeFees for the prison ");
			FreeFeesCheck = pIn->GetInteger(pOut);
		}
		FreeFees = FreeFeesCheck;
	}
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	string Answer = "Empty";
	if (pPlayer->GetWallet() >= FreeFees)
	{
		pOut->PrintMessage("You are going to prison. Would you like to pay the FreeFees? y/n?");   // Checks if player wants to pay the FreeFees
		Answer = pIn->GetSrting(pOut);
		if (Answer != "y" && Answer != "n")
		{
			pOut->PrintMessage("Please enter y for YES and n for NO ");
			Answer = pIn->GetSrting(pOut);
		}
		pOut->ClearStatusBar();
		if (Answer == "y")                                       //Player Pays FreeFees
		{
			pPlayer->SetWallet(pPlayer->GetWallet() - FreeFees);
			pOut->ClearStatusBar();
			return;
		}
		if (Answer == "n")
		{
			pOut->ClearStatusBar();
			return;
		}

	}

	if (Answer == "Empty" || Answer == "n")
	{
		pOut->PrintMessage("You are going to prison and not going to play for 3 turns ");  
		pPlayer->SetInPrison(true);
		pPlayer->SetPreventFromRolling(true);
			if (pPlayer->GetPrisoncount() >3)
			{
				pPlayer->SetPreventFromRolling(false);
				pPlayer->SetInPrison(false);
				pPlayer->SetPrisoncount(0);
			}
		
	}
	pOut->ClearStatusBar();

}

void CardEight::Save(ofstream& OutFile, ObjType obj)  //Saves the GameObj parameters to the file
{
	if (obj == card)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << " " << FreeFees << endl;
	}
}
void CardEight::Load(ifstream& Infile, Grid* pGrid)   //Loads the GameObj parameters to the file
{
	int cellNum;
	Infile >> cellNum >> FreeFees;
	CellPosition pos(cellNum);
	position = pos;
}

CardEight::~CardEight()
{

}