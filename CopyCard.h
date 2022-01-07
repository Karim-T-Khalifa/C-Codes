#pragma once

#include "Card.h"
#include"Action.h"


class CopyCard : public Action
{
	// [Action Parameters]
	CellPosition cardPosition; // 1- cell position of the card needed to be copied
	Card* CopiedCard;            // 2- a member of type card to store data of the copied card

	// Note: These parameters should be read in ReadActionParameters()
	

public:
	CopyCard(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads action parameters (cardPosition, card to be copied info)

	virtual void Execute(); // Call ReadActionParameters
							// Set the Clipboard

	virtual ~CopyCard(); // A Virtual Destructor
};

