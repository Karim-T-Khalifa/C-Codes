#pragma once
#include"Card.h"
class CardEight : public Card
{
	static int FreeFees;
public:
	CardEight(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual ~CardEight();

	virtual void Save(ofstream& OutFile, ObjType obj);  //Saves the GameObj parameters to the file
	virtual void Load(ifstream& Infile, Grid* pGrid);   //Loads the GameObj parameters to the file

	virtual void Apply(Grid*, Player*);
};

