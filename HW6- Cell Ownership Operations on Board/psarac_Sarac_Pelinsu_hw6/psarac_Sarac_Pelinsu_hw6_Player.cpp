#include <iostream> //may not need
#include "psarac_Sarac_Pelinsu_hw6_Player.h"

using namespace std;

/* Begin: code taken from 5-templated.ppt and updated by Pelinsu Sarac */

/*****************************************************************************
This function is the constructor of Player class, it creates a player with
unique ID and connects the player to the shared board.
Input: board to be shared by players
Returns: a player of the board game
*****************************************************************************/
/* Begin: code taken from 4.3-advanced-classes.ppt and updated by Pelinsu Sarac */

template <class Type>
Player<Type>::Player(Board<Type> & board): myBoard(board)
{ 
	numOfPlayers++;
	playerID = numOfPlayers;	
}

/* End: code taken from 4.3-advanced-classes.ppt and updated by Pelinsu Sarac */

/*****************************************************************************
This function is for claiming a cell with player ID and given value, if cell is
owned by the player or not claimed by any of players before. In such case it
returns true, false otherwise.
Input: row and column to specify the cell, value to be placed 
Returns: True if cell is owned by the player or not claimed by anyone before
		 (and inserts the ID and value inside cell)
		 False otherwise
*****************************************************************************/

template <class Type>
bool Player<Type>::updateCell(int row, int column, Type valueToBePlaced) const
{
	if (myBoard.knowTheOwner(row, column) == playerID || myBoard.knowTheOwner(row, column) == 0)
	{
		myBoard.setIDofCell(row, column, playerID);
		myBoard.setValueOfCell(row, column, valueToBePlaced);
		return true;
	}
	else {return false;}
}

/*****************************************************************************
This function is for updating all cells owned by the player by changing cells'
value to given value.
Input: value to be placed
Returns: updated board with given value
*****************************************************************************/

template <class Type>
void Player<Type>::updateMyCells(Type valueToBePlaced) const
{
	myBoard.updateBoardCells(playerID, valueToBePlaced);
}

/*****************************************************************************
This function is for unclaiming ownership of a cell (ID part of cell goes back 
to 0) specified by row and column, if cell was owned by the player in the first 
place. In such case it returns true, false otherwise.
Input: row and column to specify the cell
Returns: True if the specified cell is owned by the player
		 (and unclaims ownership of cell)
		 False otherwise
*****************************************************************************/

template <class Type>
bool Player<Type>::unclaimOwnership(int row, int column) const
{
	if (myBoard.knowTheOwner(row, column) == playerID)
	{
		myBoard.setIDofCell(row, column, 0);
		return true;
	}
	else {return false;}
}

/*****************************************************************************
This function is to unclaim all cells owned by the player (ID part of cells 
goes back to 0).
Input: None
Returns: updated board with unclaimed cells 
*****************************************************************************/

template <class Type>
void Player<Type>::unclaimOwnerships() const
{
	int row, column;
	myBoard.getRowColumn(row, column);

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (myBoard.knowTheOwner(r,c) == playerID)
			{
				myBoard.setIDofCell(r, c, 0);
			}
		}
	}
}

/* End: code taken from 5-templated.ppt and updated by Pelinsu Sarac */