#ifndef _PSARAC_SARAC_PELINSU_HW3_TWODLINKEDLIST_H
#define _PSARAC_SARAC_PELINSU_HW3_TWODLINKEDLIST_H
#include <string>
using namespace std;

/******************************************************************************
Purpose: This program is a simple word processor using 2D linked lists
		 Made for Sabanci University CS 204 Course HW-3 
Author: Pelinsu Sarac
Date: 04/04/2022
Written on: MS Visual Studio 2012 
******************************************************************************/

/******************************************************************************
This structure is a node, which is an element of 2D linked list. Holding a character
while pointing to the node on its right and node below it at the same time.
******************************************************************************/

/* Begin: code taken from CS204_Homework3_Spring2022.pdf */
struct node  
{
	char data;
	node *right;
	node *down;
};
/* End: code taken from CS204_Homework3_Spring2022.pdf */

class TwoDLinkedList
{
private:
	node * head; //pointing to head node/first node of 2D linked list

	//displays all words of 2D linked list row by row, starting from bottommost word
	void TwoDLinkedList::displayFullMatrixReversed(node * ptr);

public:
	TwoDLinkedList(); //constructor
	
	//adds a word to 2D linked list according to it's first letter and maintains ascending order
	void add_row_sorted(string word); 

	//displays all words of 2D linked list row by row, starting from topmost word
	void displayFullMatrix(); 
	
	//calls the reverse display function publicly without the need of a parameter
	void displayFullMatrixReversed(); 

	//displays rows only starting with a specific character
	void display_rows_starting_with(char charToBeChecked); 

	//displays columns only starting with a specific character
	void display_cols_starting_with(char charToBeChecked); 

	//deletes rows starting with a specific character and returns number of deleted rows
	int delete_rows_starting_with(char charToBeDeleted); 

	//deletes columns starting with a specific character and returns number of deleted columns
	int delete_cols_starting_with(char charToBeDeletd); 

	//deletes all nodes of a 2D linked list, i.e. clears the list
	void clear(); 
};

#endif