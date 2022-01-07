#include "Ladder.h"
#include<fstream>


Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	///TODO: Do the needed validation
	if (endCellPos.HCell() == startCellPos.HCell() && endCellPos.VCell() < startCellPos.VCell())
	{
		this->endCellPos = endCellPos;
	}

}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	pOut->PrintMessage("You have reached a ladder. Click to continue ...");
	pIn->GetCellClicked();
	pOut->ClearStatusBar();

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

	
}
bool Ladder::IsOverlapping(GameObject* newObj)const
{
	Ladder* passedladder = dynamic_cast <Ladder*> (newObj);
	if (passedladder != NULL)
	{
		if (passedladder->GetPosition().HCell() == this->GetPosition().HCell() || passedladder->GetEndPosition().HCell() == this->GetPosition().HCell())
		{
		if (passedladder->GetEndPosition().VCell() > this->GetEndPosition().VCell() && passedladder->GetEndPosition().VCell() < this->GetPosition().VCell())
		{
			return true;
		}
		else if (passedladder->GetPosition().VCell() > this->GetEndPosition().VCell() && passedladder->GetPosition().VCell() < this->GetPosition().VCell())
		{
			return true;
		}
		else if (passedladder->GetPosition().VCell() == this->GetPosition().VCell() || passedladder->GetEndPosition().VCell() == this->GetPosition().VCell())
		{
			return true;
		}
		else return false;
		}
	}
}

void Ladder::Save(ofstream& OutFile, ObjType Obj)
{
	if (Obj == ladder)
	{
		OutFile << GetPosition().GetCellNum() << " " << GetEndPosition().GetCellNum();
	}
}

void Ladder::Load(ifstream& Infile,Grid* pGrid)
{
	
	int  StartCellNum, EndCellNum;
	Infile >> StartCellNum, EndCellNum;
	CellPosition StartCellpos, EndCellpos;
	Ladder * newpassedLadder = new Ladder(StartCellpos.GetCellPositionFromNum(StartCellNum),EndCellpos.GetCellPositionFromNum(EndCellNum));
	pGrid->AddObjectToCell(newpassedLadder);
	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

Ladder::~Ladder()
{
}
