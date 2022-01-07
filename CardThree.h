#pragma once

#include "Card.h"
#include <fstream>
class CardThree : public Card
{
	//No data members

public:
	CardThree(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardThree

	virtual void Apply(Grid* pGrid, Player* pPlayer); //Gives the player an extra dice roll

	virtual void Save(ofstream& OutFile, ObjType obj) ;  //Saves the GameObj parameters to the file
	virtual void Load(ifstream& Infile, Grid* pGrid) ;   //Loads the GameObj parameters to the file

	virtual ~CardThree(); // A Virtual Destructor
};
