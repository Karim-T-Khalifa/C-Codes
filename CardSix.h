#pragma once
#include "Card.h"
#include <fstream>
class CardSix : public Card
{
	//CardSix parameters
	int cellNumber;       //Cell to move to    

	public:

		CardSix(const CellPosition& pos); // A Constructor takes card position

		virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardSix

		virtual void Apply(Grid* pGrid, Player* pPlayer); // Instructs the player to go to a specific cell

		virtual void Save(ofstream& OutFile, ObjType obj);  //Saves the GameObj parameters to the file
		virtual void Load(ifstream& Infile, Grid* pGrid);   //Loads the GameObj parameters to the file

		virtual ~CardSix(); // A Virtual Destructor

	};


