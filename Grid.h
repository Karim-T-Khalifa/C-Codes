#pragma once

#include <fstream>
#include "UI_Info.h"
#include "DEFS.h"
#include "Input.h"
#include "Output.h"
#include "CellPosition.h"

// forward declarations (the includes are in the cpp)

enum ObjType { ladder, snake, card }; //ladder corresponds to 0, snake to 1, card to 2..., ALSO it is forward declared so it can be used for the SAVE functions in both Grid & GameObject classes

class Cell;
class GameObject;
class Ladder;
class Snake; //included Snake class as was missing 
class Card;
class Player;

class Grid
{
	Output * pOut;   // A pointer to the Output object
	Input * pIn;     // A pointer to the Input object

	Cell * CellList[NumVerticalCells][NumHorizontalCells];  // An array of "Pointers" to All Cells of the Grid Cells
															// We make it array of pointers not objects because
															// there are NO default constructor for class Cell

	Player* PlayerList[MaxPlayerCount]; // An array of "Pointers" to the Players of the Game (MaxPlayerCount Players)
	int currPlayerNumber;   // The player number that has the turn to play 
							// currPlayerNumber is: from 0 to MaxPlayerCount - 1

	Card * Clipboard;	   // This is used in copy/cut/paste card (should be set in copy/cut and got in paste)

	bool endGame;	       // A boolean indicating if the Game is ended or not (a player reaches the end cell of the grid or not)


public:

	Grid(Input * pIn, Output * pOut);	  // Gives the Grid a Pointer to the Output Object and the Input Object
										  // and makes any needed initializations

	// ========= Adding or Removing GameObjects to Cells =========

	bool AddObjectToCell(GameObject * pNewObject);		 // Adds a GameObject to the Cell of its "position" data member
	                                                     // only if the Cell does NOT already contain an object, 
	                                                     // otherwise return false and don't add

	void RemoveObjectFromCell(const CellPosition & pos); // Removes the GameObject of the Cell of the passed "position"
	                                                     // Note: You may need to change the return type of this function (Think)

	void UpdatePlayerCell(Player * player, const CellPosition & newPosition); // Update the player's pCell with the CellList's Cell pointer of the "newPosition",
	                                                                          // Clears the player's circle from the previous cell
	    																	  // and  Draws it in the new cell

	// ========= Setters and Getters Functions =========

	Input * GetInput() const;	// Gets a Pointer to the Input
	Output * GetOutput() const; // Gets a Pointer to the Output 

	void SetClipboard(Card * card);  // A setter to be used in copy/cut (in order NOT to break class responsibilities)
	Card * GetClipboard() const;	 // A getter to be used in paste (in order NOT to break class responsibilities)

	void SetEndGame(bool endGame);	 // A setter for endGame data member
	bool GetEndGame() const;		 // A getter for endGame data member

	void AdvanceCurrentPlayer();     // Increments the currPlayerNum and if reaches MaxPlayerCount reset to 0 (using %)

	///TODO: add any needed setter/getter "EXCEPT" ANY setters or getters of "CellList" or "PlayerList" (Forbidden for class Responsibilities)
	
	int GetLaddersNum(); //getter for the number of ladders in the grid
	int GetSnakesNum();	//getter for the number of snakes in the grid
	int GetCardsNum();	//getter for the number of cards in the grid



	// ========= Other Getters =========
	
	Player * GetCurrentPlayer() const;	// Gets a Pointer to the Current Player	                                    
	Ladder * GetNextLadder(const CellPosition & position);  // Gets a Pointer to the first Ladder after the passed "position"
	Snake* GetNextSnake(const CellPosition& position);      // Gets a Pointer to the first Snake after the passed "position"	
	Player* ReturnNextPlayer();
	Player* PoorestPlayer();
	void SetAllOwnerCard9(Player* pOwner);
	void SetAllOwnerCard10(Player* pOwner);
	void SetAllOwnerCard11(Player* pOwner);
	GameObject* Grid::getGameObject(CellPosition& pos);

	// ========= User Interface Functions =========

	void UpdateInterface() const;		// It Updates the Grid according to the last state of the game
	                                    // In Design mode, it draws all cells/cards THEN all ladders/snakes THEN all players
	                                    // In Play mode, it only draws the player's info on the right side of the toolbar
	                                    // Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
	                                    //       and the cards/snakes/ladders positions do NOT change already in Play Mode

	void PrintErrorMessage(string msg); // Prints an error message on statusbar, Waits for mouse click then clears statusbar
									    // We added this function once here because it is used many times by other classes

	// ======== Check Functions ===============	
	virtual bool IsOverlapping(GameObject* newObj)const;

	// ======== ACTION Functions ===============	
	void SaveAll(ofstream& OutFile, ObjType obj); //takes the forward-declared enum ObjType parameter to save all objects of a certain type
	void NewGame(); //a function that is called by NewGameAction upon execution to reset playing conditions for the new game
	void Clear(); //a function that clears the grid of all its objects, made for use upon loading

	~Grid(); // A destructor for any needed deallcations
};

