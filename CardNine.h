#pragma once
#include"Card.h"
class CardNine : public Card
{
	static int Price;
	static int Fees;
	Player* pOwner;
public:
 
	CardNine(const CellPosition& pos);
	
	virtual void ReadCardParameters(Grid* pGrid);

	virtual ~CardNine();
	
	void SetOwner(Player* pPlayer);

	virtual Player* GetOwner();

	virtual int GetPrice();						// A getter for Price

	virtual void Save(ofstream& OutFile, ObjType obj);  //Saves the GameObj parameters to the file
	virtual void Load(ifstream& Infile, Grid* pGrid);   //Loads the GameObj parameters to the file
	
	virtual void Apply(Grid*, Player*);

};

