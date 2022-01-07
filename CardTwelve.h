#pragma once
#include"Card.h"
#include"CardNine.h"
#include"CardTen.h"
#include"CardEleven.h"

class CardTwelve : public Card
{
	CardNine* owner9;
	CardTen* owner10;
	CardEleven* owner11;

	public:
		CardTwelve(const CellPosition& pos); // A Constructor takes card position

		virtual void Apply(Grid* pGrid, Player* pPlayer);

		virtual ~CardTwelve(); // A Virtual Destructor

		virtual void Save(ofstream& OutFile, ObjType obj);  //Saves the GameObj parameters to the file
		virtual void Load(ifstream& Infile, Grid* pGrid);   //Loads the GameObj parameters to the file

};

