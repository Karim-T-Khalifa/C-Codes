#pragma once
#include "Card.h"
#include <fstream>

class CardFour :public Card
{
	// No data members

public:

	CardFour(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardFour

	virtual void Apply(Grid* pGrid, Player* pPlayer); //Prevents the player from rolling the next turn

	virtual void Save(ofstream& OutFile, ObjType obj) ;  //Saves the GameObj parameters to the file
	virtual void Load(ifstream& Infile, Grid* pGrid) ;   //Loads the GameObj parameters to the file

	virtual ~CardFour(); // A Virtual Destructor

};

