#pragma once

#include "Card.h"
#include"Action.h"


class CutCard : public Action
{
	// [Action Parameters]
	CellPosition cardPosition;   // 1- cell position of the card needed to be cut
	Card* CardCut;            // 2- a member of type card to store data of the cut card

	// Note: These parameters should be read in ReadActionParameters()


public:
	CutCard(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardPosition, card needed to be cut)

	virtual void Execute(); // Call ReadActionParameters
							// Set the Clipboard
	                        // delete the card in the cell clicked

	virtual ~CutCard(); // A Virtual Destructor
};

