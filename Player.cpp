#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
            justRolledDiceNum = 0;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	// Make any needed validations
	if (wallet >= 0)
	{
		this->wallet = wallet;
	}
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::SetTurnCount(int turn)
{
	if (turn < 3 && turn > 0)
		turnCount = turn;
}

int Player::GetStepCount() const
{
	return stepCount;
}

void Player::SetStepCount(int step)
{
	if (step > 0 && step < 100)
		stepCount = step;
}



void Player::SetRollAnotherDice(bool roll)
{
	RollAnotherDice = roll;
}

bool Player::GetRollAnotherDice()
{
	return RollAnotherDice;
}

void Player::SetPreventFromRolling(bool prevent)
{
	PreventFromRolling = prevent;
}

bool Player::GetPreventFromRolling()
{
	return PreventFromRolling;
}


int Player::Get_justRolledDiceNum()
{
	return justRolledDiceNum;
}

void Player::SetPrisoncount(int PC)
{
	Prisoncount = PC;
}

int Player::GetPrisoncount()
{
	return Prisoncount;
}

void Player::SetInPrison(bool IP)
{
	InPrison = IP;
}

bool Player::GetInPrison()
{
	return InPrison;
}







// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);

}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once

	turnCount++;

		if (this->InPrison)
	{
		Prisoncount++;
	}

	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)

	if (turnCount == 3)
	{
		wallet = wallet + (10 * justRolledDiceNum);
		turnCount = 0;
		return;
	}
	
	// 3- Set the justRolledDiceNum with the passed diceNumber
	if (PreventFromRolling)
		justRolledDiceNum = 0;
	else
	{
		if (diceNumber >= 1 && diceNumber <= 6)
			justRolledDiceNum = diceNumber;

	}


	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"

            CellPosition pos= pCell->GetCellPosition();
	int newCellNum = pos.GetCellNumFromPosition(pos) + justRolledDiceNum ;
	pos = pCell->GetCellPosition().GetCellPositionFromNum(newCellNum);



		// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
pGrid->UpdatePlayerCell(this, pos);
	// 6- Apply() the game object of the reached cell (if any)    
/// Check first if there is a gameobject in the reached cell if there Apply the gameobject in the cell
            if (this->GetCell()->GetGameObject()!=NULL) 
	{
		this->GetCell()->GetGameObject()->Apply(pGrid, this);
	}

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
if (pos.GetCellNum()>= 99)
	{
		pGrid->SetEndGame(true);
	}

}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

void Player::ResetForNewGame(Player* p)
{
	p->SetWallet(100); //reset wallet to default value of 100
	p->SetTurnCount(0); //player turn returns to player 0
	p->SetStepCount(1); //stepcount is defined as being equivalent to the player's current cell number, hence reset to cell 1
}

