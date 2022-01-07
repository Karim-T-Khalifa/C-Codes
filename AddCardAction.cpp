#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"         
#include"CardThree.h"
#include"CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include"CardSeven.h"
#include"CardEight.h"
#include"CardNine.h"
#include"CardTen.h"
#include"CardEleven.h"
#include"CardTwelve.h"
#include "Ladder.h"
#include "Snake.h"

AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("Please Enter cardNumber: ");
	cardNumber = pIn->GetInteger(pOut);
	// 3- Read the "cardPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("Please Click on a cell: ");
	cardPosition = pIn->GetCellClicked();
	// 4- Make the needed validations on the read parameters
	while (cardNumber < 1 || cardNumber>12)
	{
		pOut->PrintMessage("Please enter a valid cardNumber between 1 and 12:");          //if card number invalid asks player to re-enter a valid one
		cardNumber = pIn->GetInteger(pOut);
	}
	while (cardPosition.IsValidCell() == false)
	{
		pOut->PrintMessage("Please click on a valid Cell:");                              //if clicked cell is invalid asks player to re-click a valid one
		cardPosition = pIn->GetCellClicked();
	}
	Ladder* Laddercheck = dynamic_cast<Ladder*>(pGrid->getGameObject(cardPosition));
	Snake* Snakecheck = dynamic_cast<Snake*>(pGrid->getGameObject(cardPosition));
	while (Laddercheck != NULL || Snakecheck != NULL)                                         //Checks if the cell contains a ladder or a snake
	{
		pOut->PrintMessage("Invalid card cell,please enter a new cell: ");
		cardPosition = pIn->GetCellClicked();
		Laddercheck = dynamic_cast<Ladder*>(pGrid->getGameObject(cardPosition));
		Snakecheck = dynamic_cast<Snake*>(pGrid->getGameObject(cardPosition));
	}
	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddCardAction::Execute()
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	AddCardAction::ReadActionParameters();
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card* pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;

		// A- Add the remaining cases
	case 2:
		pCard = new CardTwo(cardPosition);
		break;

	case 3:
		pCard = new CardThree(cardPosition);
		break;

	case 4:
		pCard = new CardFour(cardPosition);
		break;

	case 5:
		pCard = new CardFive(cardPosition);
		break;

	case 6:
		pCard = new CardSix(cardPosition);
		break;

	case 7:
		pCard = new CardSeven(cardPosition);
		break;

	case 8:
		pCard = new CardEight(cardPosition);
		break;

	case 9:
		pCard = new CardNine(cardPosition);
		break;

	case 10:
		pCard = new CardTen(cardPosition);
		break;

	case 11:
		pCard = new CardEleven(cardPosition);
		break;

	case 12:
		pCard = new CardTwelve(cardPosition);
		break;

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pGrid = pManager->GetGrid();
		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		pCard->ReadCardParameters(pGrid);
		// C- Add the card object to the GameObject of its Cell:
		bool AddedCard = pGrid->AddObjectToCell(pCard);        //Adding card to cell and returning true or false

		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (AddedCard == false)
			pGrid->PrintErrorMessage(" Cell already has an object! ");

	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
