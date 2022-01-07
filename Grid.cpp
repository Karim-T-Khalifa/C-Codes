#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Snake.h" //added as was missing
#include "Player.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}


// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///TODO: Check if CellList[i][j] has a ladder, if yes return it

			Ladder* l = CellList[i][j]->HasLadder();
			if (l != NULL)
				return l;
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

GameObject* Grid::getGameObject(CellPosition& pos)
{
	return CellList[pos.VCell()][pos.HCell()]->GetGameObject();
}

Player* Grid::PoorestPlayer()
{
	Player* PoorestPlayer = NULL;
	int poorestwallet = PlayerList[0]->GetWallet();
	for (int i = 1; i < MaxPlayerCount; i++)
	{
		int CurrentPlayerwallet = PlayerList[i]->GetWallet();
		if (CurrentPlayerwallet < poorestwallet) // Gets the player after the current player	
		{
			poorestwallet = CurrentPlayerwallet;
			PoorestPlayer = PlayerList[i];
		}
	}
	return PoorestPlayer;
}
Player* Grid::ReturnNextPlayer()
{

	Cell* CurrentCell;
	CurrentCell = GetCurrentPlayer()->GetCell(); // returns pointer to the cell of pPlayer
	CellPosition Position;
	Position = CurrentCell->GetCellPosition(); // retrun cellposition of pPlayer
	int currentPlayerCellNum = Position.GetCellNum(); // return cell number of pPlayer

	int  CellnumberOfNextplayer = 99;
	Player* closestNextPlayer = NULL;
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		// GetStepCount() 
		Cell* NextPlayerCell = PlayerList[i]->GetCell();
		int nextPlayerCellNum = NextPlayerCell->GetCellPosition().GetCellNum();
		if (nextPlayerCellNum > currentPlayerCellNum) // Gets the player after the current player
		{
			if (nextPlayerCellNum - currentPlayerCellNum < CellnumberOfNextplayer - currentPlayerCellNum) {
				CellnumberOfNextplayer = nextPlayerCellNum;
				closestNextPlayer = PlayerList[i];
			}

		}

	}
	return closestNextPlayer;
}



int Grid::GetLaddersNum()
{
	int l;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasLadder()) //runs a check on every individual cell for the required gameobject and if found, increments the total number of this gameobject found on the grid so far..
				l++;
		}
	}
	return l;
}

int Grid::GetSnakesNum()
{
	int s;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasSnake())
				s++;
		}
	}
	return s;
}

int Grid::GetCardsNum()
{
	int c;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasCard())
				c++;
		}
	}
	return c;
}

// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

bool Grid::IsOverlapping(GameObject* newObj)const
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject()->IsOverlapping(newObj) == true)
				return true;
		}
	}
	return false;
}



void Grid::SaveAll(ofstream& OutFile, ObjType type)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom to top
	{
		for (int j = 0; j < NumHorizontalCells; j++) // left to right
		{
			if (CellList[i][j]->GetGameObject()) //if there is no game object within the cell then the pointer will be null, hence we check that it is not NULL, and if so we continue with the save operation
			{
				GameObject* tempObj = CellList[i][j]->GetGameObject(); //save this non-NULL gameobject to a temp object
				tempObj->Save(OutFile, type); //call save function of GameObject base class, using the same parameters of SaveAll
			}
		}
	}


}

void Grid::NewGame() //remember our requirement: "Restarts players' positions, wallets, and turn returns to player 0." minimal logic
{
	CellPosition initialPos(1);
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		UpdatePlayerCell(PlayerList[i], initialPos); //calls the UpdatePlayerCell function of the grid to relocate it to our starting position
		PlayerList[i]->ResetForNewGame(PlayerList[i]);
	}
	SetAllOwnerCard9(NULL); //OFFLOAD all card ownerships
	SetAllOwnerCard10(NULL);
	SetAllOwnerCard11(NULL);
	endGame = false; //reset the end of game indicator  
	currPlayerNumber = 0; //set current player number to 0 for the new game; goes along with returning player turn to 0 outside loop
}

void Grid::SetAllOwnerCard9(Player* pOwner)
{
	for (int i = NumVerticalCells -1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			CardNine* Card9 = dynamic_cast<CardNine*>(CellList[i][j]->GetGameObject());
			if (Card9)
				Card9->SetOwner(pOwner);
		}
	}
}

void Grid::SetAllOwnerCard10(Player* pOwner)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			CardTen* Card10 = dynamic_cast<CardTen*>(CellList[i][j]->GetGameObject());
			if (Card10)
				Card10->SetOwner(pOwner);
		}
	}
}

void Grid::SetAllOwnerCard11(Player* pOwner)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			CardEleven* Card11 = dynamic_cast<CardEleven*>(CellList[i][j]->GetGameObject());
			if (Card11)
				Card11->SetOwner(pOwner);
		}
	}
}



void Grid::Clear()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
				GameObject* obj = CellList[i][j]->GetGameObject();
				if (obj != NULL) //check if a game object exists in the current cell
				{
					CellPosition temp = CellList[i][j]->GetCellPosition(); //get the cellposition of the cell
					RemoveObjectFromCell(temp); //remove any existing gameobject within the current cell
				}
		}
	}
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}
