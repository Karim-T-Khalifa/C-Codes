#pragma once

#include "Card.h"
#include"Action.h"

class PasteCard : public Action
{
	// [Action Parameters]
	CellPosition pastecellPosition; // 1- cell position of the card needed to be Paste
	Card* PastedCard;            // 2- a member of type card to store data of the Pasted card

	// Note: These parameters should be read in ReadActionParameters()


public:
	PasteCard(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads action parameters (cardPosition, card to be Paste info)

	virtual void Execute(); // Call ReadActionParameters
							// Set the Clipboard

	virtual ~PasteCard(); // A Virtual Destructor
};

