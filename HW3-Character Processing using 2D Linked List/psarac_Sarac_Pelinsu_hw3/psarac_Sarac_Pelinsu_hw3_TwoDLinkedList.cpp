#include <iostream>
#include "psarac_Sarac_Pelinsu_hw3_TwoDLinkedList.h"

using namespace std;

/*****************************************************************************
This function is the constructor of TwoDLinkedList class and when called, it
creates an empty list.
Input: None
Returns: head (pointer) of an empty 2D linked list as class member
*****************************************************************************/

TwoDLinkedList::TwoDLinkedList()
{
	head = NULL;
}

/*****************************************************************************
This function adds a word to the 2D linked list according to its first letter
while maintaining the ascending order of the list. However, it only checks
first letter and if there is another word in the list starting with same letter,
function adds new word on top of this already existing word.
Input: word to be inserted
Returns: updated 2D linked list with new word inserted
*****************************************************************************/

void TwoDLinkedList::add_row_sorted(string wordToBeInserted)
{
	//transforming word into a 1D linked list
	
	node * wordHead = new node; //head of the word to be inserted
	wordHead->data = wordToBeInserted.at(0); //first letter of the word
	wordHead->right = NULL;
	wordHead->down = NULL;

	node * outerPtr = wordHead; //pointer to add nodes next to head for rest of the word

	//rest of the word being added at the end of head node
	for (unsigned int i = 1; i < wordToBeInserted.length(); i++)
	{
		node * temp = new node;
		temp->data = wordToBeInserted.at(i);
		temp->right = NULL;
		temp->down = NULL;

		outerPtr->right = temp;
		outerPtr = temp;
	}

	outerPtr = head; //to check the first letter of words in 2D linked list

	/* Begin: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */

	//if list is empty 
	if ( head == NULL )
	{
		//new word as the first word
		head = wordHead;
	}

	//if word to be inserted must be placed above the first word
	else if ( wordHead->data < head->data || wordHead->data == head->data )
	{
		node * innerPtr = wordHead; //to go over letters of the word

		//adding new word on top of list by connecting it to rest of the list
		while ( innerPtr != NULL )
		{
			innerPtr->down = outerPtr;
			innerPtr = innerPtr->right;
			outerPtr = outerPtr->right;
		}

		head = wordHead;
	}

	//if word to be inserted must be placed in the middle or to end
	else 
	{
		//finding the word that will come before the new word in the list

		while ( outerPtr->down != NULL && outerPtr->down->data < wordHead->data )
		{
			outerPtr = outerPtr->down;
		}

		//adding new word to list and connecting it to the rest of the list
		node * innerPtr = wordHead;
		while ( outerPtr != NULL )
		{
			innerPtr->down = outerPtr->down;
			outerPtr->down = innerPtr;

			innerPtr = innerPtr->right;
			outerPtr = outerPtr->right;
		}
	}

	/* End: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */
}

/*****************************************************************************
This function displays the words inside the list row by row, starting from the 
topmost word in the list.
Input:  None
Returns: display of words of the list row by row, starting from first
*****************************************************************************/

void TwoDLinkedList::displayFullMatrix()
{
	node * rowPtr = head; //to track the rows i.e. words
	node * columnPtr; //to track to columns i.e. letters of words

	/* Begin: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */

	while ( rowPtr != NULL )
	{
		columnPtr = rowPtr;

		while ( columnPtr != NULL )
		{
			cout << columnPtr->data;
			columnPtr = columnPtr->right;
		}
		cout << endl;
		rowPtr = rowPtr->down;
	}

	/* End: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */
}

/*****************************************************************************
This function displays the words inside the list row by row, starting from the 
bottommost word in the list.
Input:  head (pointer) of a 2D linked list
Returns: display of words of the list row by row, starting from last
*****************************************************************************/

void TwoDLinkedList::displayFullMatrixReversed(node * ptr)
{
	/* Begin: code taken from linkedList.cpp and updated by Pelinsu Sarac */

	//finding the last word of the list
	if ( ptr->down != NULL )
	{
		displayFullMatrixReversed(ptr->down);
	}

	/* End: code taken from linkedList.cpp and updated by Pelinsu Sarac */

	//printing the word
	while ( ptr != NULL )
	{
		cout << ptr->data;
		ptr = ptr->right;
	}
	cout << endl;
}
	
/*****************************************************************************
This function displays the words inside the list in reverse order by calling 
displayFullMatrixReversed function that takes head as parameter
Input:  None
Returns: display of words of the list row by row, starting from last (by calling
	     displayFullMatrixReversed)
*****************************************************************************/

void TwoDLinkedList::displayFullMatrixReversed()
{
	/* Begin: code taken from linkedList.cpp and updated by Pelinsu Sarac */

	if ( head != NULL )
	{
		displayFullMatrixReversed(head);
	}

	/* End: code taken from linkedList.cpp and updated by Pelinsu Sarac */
}

/*****************************************************************************
This function displays the rows starting with a specified character.
Input:  character to be searched as first letter of the rows
Returns: displays the rows starting with specified character
*****************************************************************************/

void TwoDLinkedList::display_rows_starting_with(char charToBeChecked)
{
	node * rowPtr = head; //to track the rows
	node * columnPtr; //to track to columns

	while ( rowPtr != NULL )
	{
		//if row starts with that specified character
		if ( charToBeChecked == rowPtr->data )
		{
			columnPtr = rowPtr;

			/* Begin: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */
			
			//display the row
			while ( columnPtr != NULL )
			{
				cout << columnPtr->data;
				columnPtr = columnPtr->right;
			}
			cout << endl;

			/* End: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */
		}
		rowPtr = rowPtr->down;
	}
}

/*****************************************************************************
This function displays the columns starting with a specified character.
Input:  character to be searched as first letter of the columns
Returns: displays the columns starting with specified character
*****************************************************************************/

void TwoDLinkedList::display_cols_starting_with(char charToBeChecked)
{
	node * columnPtr = head; //to track the columns
	node * rowPtr; //to track the rows

	while ( columnPtr != NULL )
	{
		//if column start with that specified character
		if ( charToBeChecked == columnPtr->data )
		{
			rowPtr = columnPtr;

			/* Begin: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */

			//display the column
			while ( rowPtr != NULL )
			{
				cout << rowPtr->data << endl;
				rowPtr = rowPtr->down;
			}
			cout << endl;

			/* End: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */
		}
		columnPtr = columnPtr->right;
	}
}

/*****************************************************************************
This function deletes rows that start with specified character and returns 
number of deleted rows.
Input: character to be searched as first letter of the rows
Returns: number of deleted rows, updated 2D linked list with deleted rows
*****************************************************************************/

int TwoDLinkedList::delete_rows_starting_with(char charToBeDeleted)
{
	int deletedRowCount = 0; //counter to track number of deleted rows

	node * rowPtr = head;

	while ( rowPtr != NULL )
	{
		//in case of finding the given character at the beginning of a row
		if ( charToBeDeleted == rowPtr->data )
		{
			/* Begin: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */

			//if this row is the first row
			if ( rowPtr == head )
			{
				head = head->down; //moving head one row below
				node * columnPtr = rowPtr;
				rowPtr = rowPtr->down;

				//deleting the row
				node * temp;
				while ( columnPtr != NULL )
				{
					temp = columnPtr->right;
					delete columnPtr;
					columnPtr = temp;
				}

			}

			//if it's in the middle or at the end
			else
			{ 
				node * justBefore = head; //to point one row above the row to be deleted

				while ( justBefore->down != rowPtr )
				{
					justBefore = justBefore->down;
				}

				node * columnPtr = rowPtr; //to track the deletion of row
				rowPtr = rowPtr->down;

				//deleting the row
				while ( justBefore != NULL )
				{
					justBefore->down = columnPtr->down;
					justBefore = justBefore->right;
					delete columnPtr;
					columnPtr = justBefore;
					if (justBefore != NULL)
					{
						columnPtr = justBefore->down;
					}
				}
			}

			/* End: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */

			deletedRowCount++;
		}
		else
		{
			rowPtr= rowPtr->down;
		}
	}
	return deletedRowCount;
}

/*****************************************************************************
This function deletes columns that start with specified character and returns 
number of deleted columns.
Input: character to be searched as first letter of the columns
Returns: number of deleted columns, updated 2D linked list with deleted columns
*****************************************************************************/

int TwoDLinkedList::delete_cols_starting_with(char charToBeDeletd)
{
	int deletedColumnCount = 0; //counter to track number of deleted columns

	node * columnPtr = head;

	while ( columnPtr != NULL )
	{
		//in case of finding the given character at the beginning of a column
		if ( charToBeDeletd == columnPtr->data )
		{
			/* Begin: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */

			//if this column is the first column
			if ( columnPtr == head )
			{
				head = head->right; //moving the head to horizontaly next node
				node * rowPtr = columnPtr;
				columnPtr = columnPtr->right;

				//deleting the column
				node * temp;
				while ( rowPtr != NULL )
				{
					temp = rowPtr->down;
					delete rowPtr;
					rowPtr = temp;
				}
			}

			//if it's in the middle or at the end
			else
			{
				node * justBefore = head; //to point one column before the column to be deleted

				while ( justBefore->right != columnPtr )
				{
					justBefore = justBefore->right;
				}

				node * rowPtr = columnPtr; //to track the deletion of column
				columnPtr = columnPtr->right;

				//deleting the column
				while ( justBefore != NULL )
				{
					justBefore->right = rowPtr->right;
					justBefore = justBefore->down;
					delete rowPtr;
					rowPtr = justBefore;
					if ( justBefore != NULL )
					{
						rowPtr = justBefore->right;
					}
				}
			}

			/* End: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */

			deletedColumnCount++;
		}
		else
		{
			columnPtr = columnPtr->right;
		}
	}
	return deletedColumnCount;
}

/*****************************************************************************
This function deletes a whole 2D linked list by deallocating memory storing the
nodes of the list.
Input:  None
Returns: deletion of list/head pointer as null pointer
*****************************************************************************/

void TwoDLinkedList::clear()
{
	while ( head != NULL )
	{
		node * innerPtr = head;
		head = head->down;

		/* Begin: code taken from 2.2-pointers-linkedlists.ppt and updated by Pelinsu Sarac */
		node * temp;

		while ( innerPtr != NULL )
		{
			temp = innerPtr->right;
			delete innerPtr;
			innerPtr = temp;
		}

		/* End: code taken from 2.2-pointers-linkedlists.ppt and updated by Pelinsu Sarac */
	}
}