#include "OpenGridAction.h"
#include "Grid.h"
#include <fstream>
#include "Ladder.h"
#include "Snake.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"

OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp)
{
}

void OpenGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pO = pGrid->GetOutput();
	pO->PrintMessage("Enter the name of the file you want to open:");
	openfile = pIn->GetSrting(pO);
	openfile = openfile + ".txt";
	pO->ClearStatusBar();
}

void OpenGridAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pO = pGrid->GetOutput();

	pGrid->Clear();
	ifstream InFile;
	InFile.open(openfile, ios::in);
	if (InFile.fail()) //check in case the file did not open for loading 
	{
		pGrid->PrintErrorMessage("The file you have entered is corrupt or does not exist, aborting");
		return;
	}
	//GameObject* pObj; //Define a GameObject pointer called pObj
	//load ladders:
	int numladders;
	InFile >> numladders; //Read the first number from the file that represent the number of ladders
	for (int i = 0; i < numladders; i++)
	{
		//pObj = new Ladder();
		//pObj->Load(InFile, pGrid);
		CellPosition Startpos, Endpos;
		Ladder* LoadedLadder = new Ladder(Startpos, Endpos);
		LoadedLadder->Load(InFile, pGrid);
		pGrid->AddObjectToCell(LoadedLadder); //add the corresponding ladder object to the grid using its properties from the loaded file 
	}

	//load snakes:
	int numsnakes;
	InFile >> numsnakes;
	for (int i = 0; i < numsnakes; i++)
	{
		//pObj = new Snake();
		//pObj->Load(InFile, pGrid);
		CellPosition Startpos, Endpos;
		Snake* LoadedSnake = new Snake(Startpos, Endpos);
		LoadedSnake->Load(InFile, pGrid);
		pGrid->AddObjectToCell(LoadedSnake);
	}

	//load cards:
	int numcards;
	InFile >> numcards;
	for (int i = 0; i < numcards; i++)
	{
		int cardnumber;
		InFile >> cardnumber;
		switch (cardnumber) //use switch case due to multitude of cards 1-12
		{
		case 1:CardOne * Loadedcardone;
			Loadedcardone  = new CardOne(0);                   //pObj = new CardOne;
			Loadedcardone->Load(InFile, pGrid);                                                   //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardone);
			break;
		case 2:CardTwo * Loadedcardtwo;
			Loadedcardtwo = new CardTwo(0);                           //pObj = new CardTwo;
			Loadedcardtwo->Load(InFile, pGrid);                              //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardtwo);
			break;
		case 3:CardThree * Loadedcardthree;
			Loadedcardthree = new CardThree(0);                                  // pObj = new CardThree;
			Loadedcardthree->Load(InFile, pGrid);               //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardthree);
			break;
		case 4:CardFour * Loadedcardfour;
			Loadedcardfour = new CardFour(0);               //pObj = new CardFour;
			Loadedcardfour->Load(InFile, pGrid);        //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardfour);
			break;
		case 5:CardFive * Loadedcardfive;
			Loadedcardfive = new CardFive(0);           //pObj = new CardFive;
			Loadedcardfive->Load(InFile, pGrid);             //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardfive);
			break;
		case 6:CardSix * Loadedcardsix;
			Loadedcardsix = new CardSix(0);                  //pObj = new CardSix;
			Loadedcardsix->Load(InFile, pGrid);                                   //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardsix);
			break;
		case 7:CardSeven * Loadedcardseven;
			Loadedcardseven = new CardSeven(0);                                      //pObj = new CardSeven;
			Loadedcardseven->Load(InFile, pGrid);                                                     //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardseven);
			break;
		case 8:CardEight * Loadedcardeight;
			Loadedcardeight = new CardEight(0);                     // pObj = new CardEight;
			Loadedcardeight->Load(InFile, pGrid);                          //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardeight);
			break;
		case 9:CardNine * Loadedcardnine;
			Loadedcardnine = new CardNine(0);                                                     //pObj = new CardNine;
			Loadedcardnine->Load(InFile, pGrid);                                        //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardnine);
			break;
		case 10:CardTen * Loadedcardten;
			Loadedcardten = new CardTen(0);                                        //pObj = new CardTen;
			Loadedcardten->Load(InFile, pGrid);                                            //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardten);
			break;
		case 11:CardEleven * Loadedcardeleven;
			Loadedcardeleven = new CardEleven(0);                                        //pObj = new CardEleven;
			Loadedcardeleven->Load(InFile, pGrid);                                                                   //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardeleven);
			break;
		case 12:CardTwelve * Loadedcardtwelve;
			Loadedcardtwelve = new CardTwelve(0);                                                        //pObj = new CardTwelve;
			Loadedcardtwelve->Load(InFile, pGrid);                             //pObj->Load(InFile, pGrid);
			pGrid->AddObjectToCell(Loadedcardtwelve);
			break;
		}
	}
	InFile.close();
	pO->PrintMessage("Grid loaded successfully, click to continue..");
	pIn->GetCellClicked();
	pO->ClearStatusBar();
}

OpenGridAction::~OpenGridAction()
{}
