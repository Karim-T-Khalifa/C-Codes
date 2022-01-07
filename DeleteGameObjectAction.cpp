
#include "DeleteGameObjectAction.h"
#include "Input.h"
#include "Output.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

DeleteGameObjectAction::~DeleteGameObjectAction()
{
}

void DeleteGameObjectAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read the "ObjectPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("Please click on the Object you want to delete");
	ObjectPosition = pIn->GetCellClicked();

	// 3- store the card info in the Card pointer data memeber if there is card in the clicked cell , if not print cell doesnot contain card
	if (ObjectPosition.IsValidCell() == false)
	{
		Cell checkedcell(ObjectPosition);
		if (checkedcell.HasCard() != NULL || checkedcell.HasLadder()!=NULL || checkedcell.HasSnake() != NULL)
		{
			pOut->PrintMessage("Object successfully Deleted");
		}
		else
		{
			pOut->PrintMessage("Invaild, Cell doesnot contain Object - Please click on one with Object");
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

void DeleteGameObjectAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	pGrid->RemoveObjectFromCell(ObjectPosition);

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the CutCard

}


