#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v) 
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (v >= 0 && v <= 8)
	{
		vCell = v;
		return true;
	}
	else 
	{
		return false;
	}

	 // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h) 
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (h >= 0 && h <= 10)
	{
		hCell = h;
		return true;
	}
	else
	{
		return false;
	} // this line sould be changed with your implementation
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	///TODO: Implement this function as described in the .h file
	if (vCell >= 0 && vCell<=8 && hCell >= 0 && hCell<=10)
		return true; // this line sould be changed with your implementation
	else
		return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	int v = cellPosition.VCell();
	int h = cellPosition.HCell();
	int c;
	if (v == 8)
	{
		c = h + 1;
		return c;
	}
	else if (v == 7)
	{
		c = h + 12;
		return c;
	}
	else if (v == 6)
	{
		c = h + 23;
		return c;
	}
	else if (v == 5)
	{
		c = h + 34;
		return c;
	}
	else if (v == 4)
	{
		c = h + 45;
		return c;
	}
	else if (v == 3)
	{
		c = h + 56;
		return c;
	}
	else if (v == 2)
	{
		c = h + 67;
		return c;
	}
	else if (v == 1)
	{
		c = h + 78;
		return c;
	}
	else if (v == 0)
	{
		c = h + 89;
		return c;
	}
	 // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file
	int h;
	if ((cellNum >= 1) && (cellNum <= 11))
	{
		h = cellNum - 1;
		position.SetVCell(8);
		position.SetHCell(h);
	}
	else if ((cellNum >= 12) && (cellNum <= 22))
	{
		h = cellNum - 12;
		position.SetVCell(7);
		position.SetHCell(h);
	}
	else if ((cellNum >= 23) && (cellNum <= 33))
	{
		h = cellNum - 23;
		position.SetVCell(6);
		position.SetHCell(h);
	}
	else if ((cellNum >= 34) && (cellNum <= 44))
	{
		h = cellNum - 34;
		position.SetVCell(5);
		position.SetHCell(h);
	}
	else if ((cellNum >= 45) && (cellNum <= 55))
	{
		h = cellNum - 45;
		position.SetVCell(4);
		position.SetHCell(h);
	}
	else if ((cellNum >= 56) && (cellNum <= 66))
	{
		h = cellNum - 56;
		position.SetVCell(3);
		position.SetHCell(h);
	}
	else if ((cellNum >= 67) && (cellNum <= 77))
	{
		h = cellNum - 67;
		position.SetVCell(2);
		position.SetHCell(h);
	}
	else if ((cellNum >= 78) && (cellNum <= 88))
	{
		h = cellNum - 78;
		position.SetVCell(1);
		position.SetHCell(h);
	}
	else if ((cellNum >= 89) && (cellNum <= 99))
	{
		h = cellNum - 89;
		position.SetVCell(0);
		position.SetHCell(h);
	}


	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum (int addedNum)
{
	
	/// TODO: Implement this function as described in the .h file
	int NewCellNum = GetCellNum() + addedNum;
	(*this) = GetCellPositionFromNum(NewCellNum);


	// Note: this function updates the data members (vCell and hCell) of the calling object

}