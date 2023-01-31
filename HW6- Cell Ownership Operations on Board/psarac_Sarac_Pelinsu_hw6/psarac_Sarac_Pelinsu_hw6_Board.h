#ifndef _PSARAC_SARAC_PELINSU_HW6_BOARD_H
#define _PSARAC_SARAC_PELINSU_HW6_BOARD_H

using namespace std; 

/******************************************************************************
Purpose: This program is an implementation of a board in a board game
		 Made for Sabanci University CS 204 Course HW-6
Author: Pelinsu Sarac
Date: 23/05/2022
Written on: MS Visual Studio 2012 
******************************************************************************/

/******************************************************************************
This structure is for storing the information of who owns the cell and what
value is put inside of it for a cell of board.
******************************************************************************/
/* Begin: code taken from 5-templated.ppt and updated by Pelinsu Sarac */

template <class Type>
struct cell
{ 
	int ownerID; 
	Type value; 
};

template <class Type> 
class Board
{
private:
	int row, column; //to store dimensions of board
	cell<Type> ** boardMatrix; //to point at dynamically allocated matrix representing board
	cell<Type> ** cloneBoard() const; //helper for copy construtcor

public:
	Board(int pRow, int pColumn); //parametric constructor 
	Board(const Board<Type> & copy); //copy consturctor 
	~Board(); //destructor

	void displayBoard() const; //displays board
	void updateBoardCells(int playerID, Type valueToBePut); //updates cells owned by player with given value
	int getPlayerCellsCount(int playerID) const; //counts the number of cells owned by a player
	int knowTheOwner(int row, int column) const; //returns who owns the cell specified by given row and column 
	void setIDofCell(int row, int column, int ID); //makes a player owner of the specified cell 
	void setValueOfCell(int row, int column, Type valueToBePut); //puts the given value inside the specified cell
	void getRowColumn(int & r, int & c); //accessor for dimensions of board
};

#include "psarac_Sarac_Pelinsu_hw6_Board.cpp"

/* End: code taken from 5-templated.ppt and updated by Pelinsu Sarac */

#endif