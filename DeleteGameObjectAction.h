#pragma once


#include"Action.h"
#include"GameObject.h"


class DeleteGameObjectAction : public Action
{
	// [Action Parameters]
	CellPosition ObjectPosition;   // 1- cell position of the Object needed to be deleted
	//GameObject* DeletedObject;   // 2- a member of type Gameobject to store data to be delted

	// Note: These parameters should be read in ReadActionParameters()


public:
	DeleteGameObjectAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardPosition, card needed to be cut)

	virtual void Execute(); // Call ReadActionParameters
							// Set the Clipboard
							// delete the card in the cell clicked

	virtual ~DeleteGameObjectAction(); // A Virtual Destructor
};

