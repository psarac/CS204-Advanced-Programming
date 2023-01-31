#ifndef _PSARAC_SARAC_PELINSU_HW6_PLAYER_H
#define _PSARAC_SARAC_PELINSU_HW6_PLAYER_H
#include "psarac_Sarac_Pelinsu_hw6_Board.h"

using namespace std; 

/******************************************************************************
Purpose: This program is an implementation of a player in a board game
		 Made for Sabanci University CS 204 Course HW-6
Author: Pelinsu Sarac
Date: 23/05/2022
Written on: MS Visual Studio 2012 
******************************************************************************/
/* Begin: code taken from 5-templated.ppt and updated by Pelinsu Sarac */

template <class Type> 
class Player
{
private:
	/* Begin: code taken from 4.3-advanced-classes.ppt and updated by Pelinsu Sarac */
	static int numOfPlayers; //to hold the number of players created
	/* End: code taken from 4.3-advanced-classes.ppt and updated by Pelinsu Sarac */

	int playerID; //to hold ID of the player
	Board<Type> & myBoard; //reference board object so that players can share a board

public:
	Player(Board<Type> & board); //constructor
	bool updateCell(int row, int column, Type valueToBePlaced) const; //update a cell with player ID and given value
	void updateMyCells(Type valueToBePlaced) const; //updates all cells owned by the player with given value 
	bool unclaimOwnership(int row, int column) const; //unclaims ownership of the specified cell
	void unclaimOwnerships() const; //unclaims ownership of all cells owned by player
};
/* Begin: code taken from 4.3-advanced-classes.ppt and updated by Pelinsu Sarac */
template <class Type>
int Player<Type>::numOfPlayers = 0;
/* End: code taken from 4.3-advanced-classes.ppt and updated by Pelinsu Sarac */

#include "psarac_Sarac_Pelinsu_hw6_Player.cpp"

/* End: code taken from 5-templated.ppt and updated by Pelinsu Sarac */

#endif