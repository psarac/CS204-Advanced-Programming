#include <iostream>
#include <sstream>
#include "psarac_Sarac_Pelinsu_hw5_Deck.h"

using namespace std;

/*****************************************************************************
This function is the constructor of Deck class and when called, it
creates an empty deck.
Input: None
Returns: an empty deck object (deck size is 0 and card array pointer is null)
*****************************************************************************/

Deck::Deck()
{
	deckPtr = NULL;
	deckSize = 0;
}

/*****************************************************************************
This function is the copy constructor of deck class and when called, it
creates a new deck as copy of the deck given as parameter
Input: Deck object to be copied
Returns: new deck object as copy of the deck given as parameter
*****************************************************************************/

/* Begin: code taken from 4.1-advanced-classes.ppt and updated by Pelinsu Sarac */

Deck::Deck(const Deck & copy)
{
	deckPtr = copy.cloneDeck();
	deckSize = copy.deckSize;
}

/*****************************************************************************
This function is a helper function that copies the card array of a deck and
returns a pointer pointing at it. Used at copy constructor.
Input: None
Returns: pointer pointing at a copied card array
*****************************************************************************/

Card* Deck::cloneDeck() const
{
	//if deck to be cloned is empty
	if (deckPtr == NULL)
	{
		return NULL;
	}

	//otherwise, coppying each card to new array
	Card * copyDeck = new Card[deckSize];
	for (int i = 0; i < deckSize; i++)
	{
		copyDeck[i].name = deckPtr[i].name;
		copyDeck[i].energy = deckPtr[i].energy;
	}

	return copyDeck;
}

/*****************************************************************************
This function is a helper function that transforms a deck into a list in string
type. Used in output stream operator.
Input: None
Returns: list form of deck in string type 
*****************************************************************************/

string Deck::toList() const
{
	ostringstream os; //string stream object to store card names and energies
	for (int i = 0; i < deckSize; i++) 
	{
		os << i+1 << ": " << deckPtr[i].name << " - " << deckPtr[i].energy << endl;
	}

	return os.str();
}

/*****************************************************************************
This operator is for putting a Deck object on an output stream as listing of
cards inside the deck.
Input: Output stream object, deck to be displayed
Returns: display of cards in deck as a list 
*****************************************************************************/

ostream & operator << (ostream & os, const Deck & deck)
{
	os << deck.toList();
	return os;
}

/*****************************************************************************
This operator is for assigning a deck object to other one (lhs to rhs).
Input: deck to be assigned
Returns: modified rhs deck as lhs assigned  
*****************************************************************************/

const Deck & Deck::operator=(const Deck & rhs)
{
	if (&rhs != this)
	{
		delete [] deckPtr;
		deckPtr = rhs.cloneDeck();
		deckSize = rhs.deckSize;
	}

	return *this;
}

/*****************************************************************************
This operator is for adding two Deck objects and assign the resulting Deck object 
to the Deck object on the left-hand side of the operator.
Input: deck to be added 
Returns: rhs deck with lhs deck added from the bottom 
*****************************************************************************/

const Deck & Deck::operator+=(const Deck & rhs) 
{
	int newDeckSize = deckSize + rhs.deckSize; //to store new deck size

	//if deck won't be empty
	if (newDeckSize != 0)
	{
		Card * concatenatedDeck = new Card[newDeckSize]; //new card array for the deck
		
		//cards from lhs deck
		for (int i = 0; i < deckSize; i++)
		{
			concatenatedDeck[i].name = deckPtr[i].name;
			concatenatedDeck[i].energy = deckPtr[i].energy;
		}

		Card * rhsTemp = rhs.deckPtr;
		//cards from rhs deck
		for (int j = 0; j < rhs.deckSize; j++)
		{
			concatenatedDeck[j+deckSize].name = rhsTemp[j].name;
			concatenatedDeck[j+deckSize].energy = rhsTemp[j].energy;
		}

		if (deckPtr != NULL)
		{
			delete [] deckPtr;
		}
		deckPtr = concatenatedDeck;

	}

	deckSize = newDeckSize;
	return *this;
}

/*****************************************************************************
This operator is for concatenation of two Deck operands and to return a new
deck without changing the contents of the operands.
Input: decks to be concatenated
Returns: new deck as concatenation of two decks
*****************************************************************************/

Deck operator + (const Deck & lhs, const Deck & rhs)
{
	Deck resultingDeck(lhs); //copy of lhs deck
	resultingDeck += rhs;
	return resultingDeck;
}

/*****************************************************************************
This operator is for adding a card to the bottom of a deck and to return a new
deck without changing the content of deck
Input: card to be added
Returns: new deck with given card added to rhs deck
*****************************************************************************/

Deck Deck::operator + (const Card & rhs) const
{
	Deck resultingDeck; //new deck to store deck and card
	resultingDeck.deckSize = deckSize + 1; //to store new deck size

	Card * resultingArray = new Card[deckSize + 1]; //new card array for new deck
	int i = 0;
	//filling new deck with elements of old
	for (; i < deckSize; i++)
	{
		resultingArray[i].name = deckPtr[i].name;
		resultingArray[i].energy = deckPtr[i].energy;
	}
	//adding the card
	resultingArray[i].name = rhs.name;
	resultingArray[i].energy = rhs.energy;

	resultingDeck.deckPtr = resultingArray;

	return resultingDeck;
}

/* End: code taken from 4.1-advanced-classes.ppt and updated by Pelinsu Sarac */

/*****************************************************************************
This operator is for returning a new deck with given number of cards removed from
top of the deck. If number is larger than size of deck, new deck will be empty.
Input: number of cards to be removed
Returns: new deck with a number of cards removed from top
*****************************************************************************/

Deck Deck::operator - (int rhs) const
{
	Deck resultingDeck; //new deck

	//if more cards to be removed than deck size
	if (deckSize <= rhs)
	{
		resultingDeck.deckPtr = NULL; //then new deck will be empty
		resultingDeck.deckSize = 0;
	}

	//otherwise, new deck will have cards with some of them removed from top
	else
	{
		resultingDeck.deckSize = deckSize - rhs;
		Card * resultingArray = new Card[deckSize-rhs];
		for (int i = 0; i < (deckSize-rhs); i++)
		{
			resultingArray[i].name = deckPtr[i+rhs].name;
			resultingArray[i].energy = deckPtr[i+rhs].energy;
		}
		resultingDeck.deckPtr = resultingArray;
	}

	return resultingDeck;
}

/*****************************************************************************
This function is a helper function that calculates total energy of a deck by
summing card energies. Used at comparison operators.
Input: None
Returns: total energy value
*****************************************************************************/

int Deck::totalEnergy() const
{
	int totalEnergy = 0;
	for (int i = 0; i < deckSize; i++)
	{
		totalEnergy += deckPtr[i].energy;
	}
	return totalEnergy;
}

/* Begin: code taken from clockt.cpp and updated by Pelinsu Sarac */

/*****************************************************************************
This operator returns true if two decks have same amount of total energy, false
otherwise.
Input: deck to be compared in terms of total energy
Returns: true if two decks have same amount of total energy, false
	     otherwise
*****************************************************************************/

bool Deck::operator == (const Deck & rhs) const
{
	return (this->totalEnergy() == rhs.totalEnergy());
}

/*****************************************************************************
This operator returns true if lhs deck has less total energy than rhs deck, false
otherwise.
Input: two decks to be compared in terms of total energy
Returns: true if lhs deck has less total energy than rhs deck, false
		 otherwise
*****************************************************************************/

bool operator < (const Deck & lhs, const Deck & rhs)
{
	return (lhs.totalEnergy() < rhs.totalEnergy());
}

/*****************************************************************************
This operator returns true if deck has more cards than given number, false
otherwise.
Input: number to be compared with size of deck 
Returns: true if deck has more cards than given number, false
		 otherwise
*****************************************************************************/

bool Deck::operator > (int rhs) const
{
	return (this->deckSize > rhs);
}

/* End: code taken from clockt.cpp and updated by Pelinsu Sarac */

/*****************************************************************************
This function is a helper function that returns true if a given card is in deck,
false otherwise.
Input: card to be checked
Returns: true if a given card is in deck, false otherwise
*****************************************************************************/

bool Deck::doesExistIn(const Card & cardToBeChecked) const
{
	if (deckPtr == NULL)
	{
		return false;
	}

	for (int i = 0; i < deckSize; i++)
	{
		if ((deckPtr[i].name == cardToBeChecked.name) && (deckPtr[i].energy == cardToBeChecked.energy))
		{
			return true;
		}
	}

	return false;
}

/*****************************************************************************
This operator returns true if a given card is in given deck, false otherwise.
Input: card to be checked, deck to be checked
Returns: true if a given card is in given deck, false otherwise
*****************************************************************************/

bool operator <= (const Card & lhs, const Deck & rhs)
{
	return (rhs.doesExistIn(lhs));
}

/*****************************************************************************
This operator returns a reference of the card at given index inside the
card array of the deck.
Input: index of a card
Returns: reference of the card with given index inside deck
*****************************************************************************/
/* Begin: code inspired by string class */

Card & Deck::operator[] (int idx) const 
{
	return deckPtr[idx];
}

/* End: code inspired by string class */

/*****************************************************************************
This function is the destructor of the Deck class and when it's called, it 
deallocates the memory used for card array.
Input: None
Returns: deletion of the deck object
*****************************************************************************/

/* Begin: code taken from 4.1-advanced-classes.ppt and updated by Pelinsu Sarac */

Deck::~Deck()
{
	if (deckPtr != NULL)
	{
		delete [] deckPtr; 
	}
}

/* End: code taken from 4.1-advanced-classes.ppt and updated by Pelinsu Sarac */