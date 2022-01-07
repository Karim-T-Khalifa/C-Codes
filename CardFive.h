#pragma once
#include "Card.h"
#include <fstream>
class CardFive : public Card
{
	// No data members

public:

	CardFive(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardFive

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Moves the player backward with the same number of steps that he just rolled

	virtual void Save(ofstream& OutFile, ObjType obj) ;  //Saves the GameObj parameters to the file
	virtual void Load(ifstream& Infile, Grid* pGrid) ;   //Loads the GameObj parameters to the file

	virtual ~CardFive(); // A Virtual Destructor

};

