#pragma once
#include"Card.h"

class CardSeven : public Card
{


public:
	CardSeven(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer); 

	virtual void Save(ofstream& OutFile, ObjType obj); //Saves the GameObj parameters to the file
	virtual void Load(ifstream& InFile, Grid* pGrid);  //Loads the GameObj parameters to the file

	virtual ~CardSeven(); // A Virtual Destructor

};

