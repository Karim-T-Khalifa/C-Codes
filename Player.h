#pragma once

#include "Grid.h"
#include "Cell.h"

class Player
{
	Cell * pCell;		   // pointer to the current Cell of the player

	const int playerNum;   // the player number (from 0 to MaxPlayerCount-1)
	                       // player number does NOT change after construction (const.)

	int stepCount;		   // step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells
	int wallet;		       // player's wallet (how many coins he has -- integer)
	int justRolledDiceNum; // the current dice number which is just rolled by the player
	int turnCount;         // a counter that starts with 0, is incremented with each dice roll
	                       // and reset again when reached 3
	                       // it is used to indicate when to move and when to add to your wallet

	bool RollAnotherDice;        // It is used to indicate if player has the chance to roll another dice		
	bool PreventFromRolling;     // It is used to indicate if player is prevented from rolling the next turn		

	int Prisoncount;             //It is used to count the turns for players in prison		
	bool InPrison;               //It is used to indicate wether the player is in prison or not		

	
public:

	Player(Cell * pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell * cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell

	void SetWallet(int wallet);		// A setter for the wallet
	int GetWallet() const;			// a getter for the wallet

	int GetTurnCount() const;		// A getter for the turnCount

	///TODO: You can add setters and getters for data members here (if needed)
	void SetTurnCount(int turn);             //settter added for the turn count (to be used when resetting before a new game)
	int GetStepCount() const;                 //getter added for the stepCount data member
	void SetStepCount(int step);              //setter added for the stepCount data member

	void SetRollAnotherDice(bool roll);    //setter for RollAnotherDice data member		
	bool GetRollAnotherDice();               //getter forRollAnotherDice data member		
	void SetPreventFromRolling(bool prevent);     //setter for PreventFromRolling data member		
	bool GetPreventFromRolling();        //getter for PreventFromRolling data member		
	int Get_justRolledDiceNum();       //getter for justRolledDiceNum member		
	void SetPrisoncount(int prisoncount);     //setter for Prisoncoutn data member		
	int GetPrisoncount();        //getter for Prisoncount data member		
	void SetInPrison(bool IP);     //setter for InPrison data member		
	bool GetInPrison();        //getter for InPrison data member		


	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its current cell

	// ====== Game Functions ======

	void Move(Grid * pGrid, int diceNumber);	// Moves the Player with the passed diceNumber 
	                                            // and Applies the Game Object's effect (if any) of the end reached cell 
	                                            // for example, if the end cell contains a ladder, take it
	
	void AppendPlayerInfo(string & playersInfo) const; // Appends player's info to the input string, 
	                                                   // for example: P0(wallet, turnCount)

	void ResetForNewGame(Player* p); //called by grid to reset players to square one

};

