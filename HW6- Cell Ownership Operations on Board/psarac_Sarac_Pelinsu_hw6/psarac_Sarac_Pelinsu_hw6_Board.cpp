#include <iostream> 
#include <iomanip>
#include "psarac_Sarac_Pelinsu_hw6_Board.h"

using namespace std;

/* Begin: code taken from 5-templated.ppt and updated by Pelinsu Sarac */

/*****************************************************************************
This function is the constructor of Board class and it initializes an empty
board with given dimensions.
Input: row size, column size
Returns: an empty board
*****************************************************************************/
/* Begin: code taken from 2.2-pointers-linkedlists.ppt and updated by Pelinsu Sarac */

template <class Type>
Board<Type>::Board(int pRow, int pColumn)
{
	//setting dimensions of board
	row = pRow;
	column = pColumn;

	//creating dynamic 2D matrix that represents the board
	boardMatrix = new cell<Type>* [row];

	for (int i = 0; i < row; i++)
	{
		boardMatrix[i] = new cell<Type> [column];

		for (int j = 0; j < column; j++)
		{
			boardMatrix[i][j].ownerID = 0;
		}
	}
}

/* End: code taken from 2.2-pointers-linkedlists.ppt and updated by Pelinsu Sarac */

/*****************************************************************************
This function is the copy constructor of Board class and when called, it
creates a new Board as copy of the Board given as parameter
Input: Board to be copied
Returns: new Board as copy of the Board given as parameter
*****************************************************************************/
/* Begin: code taken from 4.1-advanced-classes.ppt and updated by Pelinsu Sarac */

template <class Type>
Board<Type>::Board(const Board<Type> & copy)
{
	row = copy.row;
	column = copy.column;

	boardMatrix = copy.cloneBoard();
}

/*****************************************************************************
This function is a helper function that copies the dynamic 2D matrix of board
and returns a pointer pointing at it. Used at copy constructor.
Input: None
Returns: pointer to pointer, pointing at a copied dynamic 2D matrix of board
*****************************************************************************/

template <class Type>
cell<Type> ** Board<Type>::cloneBoard() const
{
	cell<Type> ** copyBoard = new cell<Type>* [row];
	
	for (int i = 0; i < row; i++)
	{
		copyBoard[i] = new cell<Type> [column];

		for (int j = 0; j < column; j++)
		{
			copyBoard[i][j].ownerID = boardMatrix[i][j].ownerID;
			copyBoard[i][j].value = boardMatrix[i][j].value;
		}
	}

	return copyBoard;
}

/* End: code taken from 4.1-advanced-classes.ppt and updated by Pelinsu Sarac */

/*****************************************************************************
This function is the destructor of the Board class and when it's called, it 
deallocates the memory used for dynamic 2D matrix of board.
Input: None
Returns: deletion of the Board object
*****************************************************************************/
 /* Begin: code taken from NQueen.cpp and updated by Pelinsu Sarac */

template <class Type>
Board<Type>::~Board()
{
	for (int i = 0; i < row; i++)
	{
		delete [] boardMatrix[i];
		boardMatrix[i] = NULL;
	}

	delete [] boardMatrix;
	boardMatrix = NULL;
}

/* End: code taken from NQueen.cpp and updated by Pelinsu Sarac */

/*****************************************************************************
This function is for displaying current state of board with occupied cells,
indicating who owns which cell and what values are put to them. 
Input: None
Returns: display of the board
*****************************************************************************/

template <class Type>
void Board<Type>::displayBoard() const
{
	cout << "Displaying the board: Each cell is shown as tuple (CURRENT OWNER ID, VALUE):" << endl;

	//column numbers 
	for (int c = 0; c < column; c++)
	{
		cout << "\t" << c; 
	}
	cout << endl;

	//row numbers and cells
	for (int r = 0; r < row; r++)
	{
		cout << r;
		for (int i = 0; i < column; i++)
		{
			cout << "\t" << "(" << boardMatrix[r][i].ownerID << "," << boardMatrix[r][i].value << ")";
		}

		cout << endl;
	}
}

/*****************************************************************************
This function is for updating all cells owned by given player with given value.
Input: player ID, vlaue to be put 
Returns: updated board with given values
*****************************************************************************/

template <class Type>
void Board<Type>::updateBoardCells(int playerID, Type valueToBePut) 
{
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (boardMatrix[r][c].ownerID == playerID)
			{
				boardMatrix[r][c].value = valueToBePut;
			}
		}
	}
}

/*****************************************************************************
This function is to see how many cells are owned by given player.
Input: player ID 
Returns: number of cells owned by given player
*****************************************************************************/

template <class Type>
int Board<Type>::getPlayerCellsCount(int playerID) const
{
	int ownedCells = 0; //to count number of cells owned by the player
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (boardMatrix[r][c].ownerID == playerID)
			{
				ownedCells++;
			}
		}
	}

	return ownedCells;
}

/*****************************************************************************
This function is to see the owner of the cell specified with given row and 
column.
Input: row and column for position of cell
Returns: player ID of owner of the cell
*****************************************************************************/

template <class Type>
int Board<Type>::knowTheOwner(int row, int column) const
{
	return boardMatrix[row][column].ownerID;
}

/*****************************************************************************
This function is for owning a cell by setting ID part of cell to given player 
ID.
Input: row and column for position of cell, player ID as owner
Returns: updated board with newly owned cell
*****************************************************************************/

template <class Type>
void Board<Type>::setIDofCell(int row, int column, int ID)
{
	boardMatrix[row][column].ownerID = ID;
}

/*****************************************************************************
This function is for changing the value part of specified cell with given 
value.
Input: row and column for position of cell, value to be put
Returns: updated board with newly put value
*****************************************************************************/

template <class Type>
void Board<Type>::setValueOfCell(int row, int column, Type valueToBePut)
{
	boardMatrix[row][column].value = valueToBePut;
}

/*****************************************************************************
This function is for accessing the dimensions of the board.
Input: row and column as reference
Returns: row and column as dimensions of board (through reference) 
*****************************************************************************/

template <class Type>
void Board<Type>::getRowColumn(int & r, int & c)
{
	r = row;
	c = column;
}

/* End: code taken from 5-templated.ppt and updated by Pelinsu Sarac */
