
#include "PasteCard.h"
#include "Input.h"
#include "Output.h"


PasteCard::PasteCard(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

PasteCard::~PasteCard()
{
}

void PasteCard::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read the "cardPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("Please click on the cell you want to paste the card in");
	pastecellPosition = pIn->GetCellClicked();

	// 3- store the card info in the Card pointer data memeber if there is card in the clicked cell , if not print cell doesnot contain card
	if (pastecellPosition.IsValidCell() == false)
	{
		Cell checkedcell(pastecellPosition);
		if (checkedcell.HasCard() == NULL && checkedcell.HasSnake() == NULL && checkedcell.HasLadder()==NULL)
		{
			pOut->PrintMessage("Cell successfuly Pasted to the cell chosen");
		}
		else
		{
			pOut->PrintMessage("Invaild, Cell already contain GameObject - Please click on one with card");
			return;
		}
	}
	else
	{
		pOut->PrintMessage("Invlaid Cell Clicked , PLease Click on a cell in the Grid");
		return;
	}

	// Make the needed validations on the read parameters  (if cell hsa card or not) (valid cell for example)

	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void PasteCard::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	ReadActionParameters();
	PastedCard=pGrid->GetClipboard();
	pGrid->AddObjectToCell(PastedCard);

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the CopyCard

}
