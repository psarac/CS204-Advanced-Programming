#ifndef _PSARAC_SARAC_PELINSU_HW5_DECK_H
#define _PSARAC_SARAC_PELINSU_HW5_DECK_H
#include <string>
using namespace std;

/******************************************************************************
Purpose: This program is an implementation of a trading card game
		 Made for Sabanci University CS 204 Course HW-5
Author: Pelinsu Sarac
Date: 10/05/2022
Written on: MS Visual Studio 2012 
******************************************************************************/

/******************************************************************************
This structure is representing a card with a name and energy value. Cards will
be elements of decks.
******************************************************************************/

struct Card
{
	string name;
	int energy;
};

class Deck
{
private:
	Card * deckPtr; //pointing to an array of cards/content of deck
	int deckSize; //to store deck size/how many cards does deck have
	Card * cloneDeck() const; //helper function that creates a copy of 
								//card array and returns a pointer pointing to it

public:
	Deck(); //constructor
	Deck(const Deck & copy); //copy constructor
	~Deck(); //destructor
	const Deck & operator=(const Deck & rhs); //assignment operator for two decks
	const Deck & operator+=(const Deck & rhs); //incrementation operator for two decks
	Deck operator + (const Card & rhs) const; //operator for adding a card to a deck
	Deck operator - (int rhs) const; //operator to remove an amount of cards from a deck
	Card & operator[] (int idx) const; //index operator
	
	int totalEnergy() const; //helper function to find total energy of a deck
	bool doesExistIn(const Card & cardToBeChecked) const; //helper function to see if a card exists in a deck
	string toList() const; //helper function to display a deck as a list

	bool operator == (const Deck & rhs) const; //operator to check if two decks have same total energy
	bool operator > (int rhs) const; //operator to check if a deck has more cards than a given number
};

//Free Functions:

Deck operator + (const Deck & lhs, const Deck & rhs); //addition operator for two decks
bool operator < (const Deck & lhs, const Deck & rhs); //operator to check if one deck has less energy than other deck
bool operator <= (const Card & lhs, const Deck & rhs); //operator to see if a card exists in a deck
ostream & operator << (ostream & os, const Deck & deck); //output stream operator for decks

#endif