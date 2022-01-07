#pragma once

#include "Card.h"
#include<fstream>


class CardTwo : public Card
{
	// No data members


public:

	CardTwo(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardTwo

	virtual void Apply(Grid* pGrid, Player* pPlayer); //Moves the player forward to the start of the next ladder in the grid
						
	virtual void Save(ofstream& OutFile, ObjType obj); //Saves the GameObj parameters to the file
	virtual void Load(ifstream& Infile, Grid* pGrid);  //Loads the GameObj parameters to the file

	virtual ~CardTwo(); // A Virtual Destructor
};

