#pragma once
#include"Card.h"
class CardTen : public Card
{
	static int Price;
	static int Fees;
	Player* pOwner;
public:

	CardTen (const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual ~CardTen();

	void SetOwner(Player* pPlayer);

	virtual Player* GetOwner();

	virtual int GetPrice();						// A getter for Price

	virtual void Save(ofstream& OutFile, ObjType obj);  //Saves the GameObj parameters to the file
	virtual void Load(ifstream& Infile, Grid* pGrid);   //Loads the GameObj parameters to the file

	virtual void Apply(Grid*, Player*);

};

