#include <iostream>
#include <string>
#include <fstream> //for ifstream

using namespace std;

/******************************************************************************
Purpose: This program is a simple word processor using linked lists
		 Made for Sabanci University CS 204 Course HW-2 
Author: Pelinsu Sarac
Date: 23/03/2022
Written on: MS Visual Studio 2012 
******************************************************************************/

/******************************************************************************
This structure is a node, which is an element of linked list. Holding a character
and points to the next node at the same time.
******************************************************************************/

/* Begin: code taken from CS204_Homework2_Spring2022_Red_Updated.pdf */

struct node
{
	char ch;
	node * next;
};

/* End: code taken from CS204_Homework2_Spring2022_Red_Updated.pdf */

//PROTOTYPES:

//creates a linked list out of letters included in a file
node * linkedListCreator (ifstream & file); 

//displays the content of a linked list
void DisplayList (node * head);

//deletes/deallocates nodes of a linked list
void DeleteList (node *head);

//checks if given arguments are valid, in this case if they are lowercase letter 
bool lowerLetterCheck (char charToBeChecked);

//finds a node of a linked list with specified character
bool findNode(char charToBeFound, node * & nodeToBeFound, node * head);

//deletes a specified node from a linked list
void DeleteOneNode (node * toBeDeleted, node * & head);

//compares two linked lists and displays the similarity
void Similarity(node * ptr1, node * ptr2);

//deletes all nodes of a linked list with specified character 
void DeleteChar(char charToBeDeleted, node * & listHead, char listNum);

//inserts a node with specified character in a linked list, after a node with another specified character
void InsertChar(char toBeInserted, char comesAfter, node * & listHead, char listNum);


int main()
{
	/******************************************************************************
	 This part takes inputs as two file names repeatedly until both files can be 
	 opened successfully. Then it reads the files and creates two linked lists
	 that consist of letters from the files. Finally, it closes files and displays 
	 the content of the linked lists.
	 Input: two file names
	 Returns: two linked lists (head pointer) with letters from files
	 ******************************************************************************/

	string filename1 = "", filename2 = ""; //file names to be taken from user
	ifstream file1, file2; //file objects to be readed

	//gets a valid file name for file 1
	do
	{
		cout << "Please enter the file 1 name: ";
		cin >> filename1;

		file1.open(filename1.c_str());
	} while ( file1.fail() );

	//gets a valid file name for file 2
	do
	{
		cout << "Please enter the file 2 name: ";
		cin >> filename2;

		file2.open(filename2.c_str());
	} while ( file2.fail() );

	//read files and create linked lists using them
	node * listHead_1 = linkedListCreator(file1);
	node * listHead_2 = linkedListCreator(file2);

	//close the files
	file1.close();
	file2.close();

	//displays the lists
	cout << "List1: ";
	DisplayList(listHead_1);
	cout << endl << "List2: ";
	DisplayList(listHead_2);
	cout << endl << endl;

	/******************************************************************************
	 This part asks for a command and arguments, if any, from user repeatedly until
	 "exit" command is entered. Commands are as follows:
		* del1/del2: deletes all instances of character from a linked list (del1 for
		first list, del2 for second) specified by the argument following command.
		* insert1/insert2: inserts a character specified by first argument in a linked
		list (insert1 for first list, insert2 for second) after first instance of a
		character specified by second argument following command.
		* sim: compares two lists and counts the number of same characters at same
		position.
	 Any other attempts of command will result in "Invalid Command" error and ask for
	 another command. In case of arguments, it also checks wether these arguments are 
	 all lowercase letters or not, if not, it displays an error message. 
	 Input: commands, linked list head pointers
	 Returns: updated lists according to commands, appropriate messages
	 ******************************************************************************/

	string command = ""; //to take and evaluate command from user

	do
	{
		cout << "Enter a command and its corresponding argument(s), if any: ";
		cin >> command;

		//deletion command for first list
		if ( "del1" == command )
		{
			char charToBeDeleted; //to read following argument
			cin >> charToBeDeleted;
			if ( lowerLetterCheck(charToBeDeleted) ) //checks if argument is valid
			{
				//deletes character from first list
				DeleteChar(charToBeDeleted, listHead_1, '1');
			}
		}

		//deletion command for second list
		else if ( "del2" == command )
		{
			char charToBeDeleted; //to read following argument
			cin >> charToBeDeleted;
			if ( lowerLetterCheck(charToBeDeleted) ) //checks if argument is valid
			{
				//deletes character from second list
				DeleteChar(charToBeDeleted, listHead_2, '2');
			}
		}

		//insert command for first list
		else if ( "insert1" == command )
		{
			char toBeInserted, comesAfter; //to read following arguments
			cin >> toBeInserted >> comesAfter;
			if ( lowerLetterCheck(toBeInserted) && lowerLetterCheck(comesAfter) ) //checks if arguments are valid
			{
				//inserts first argument after first instance of second argument
					//in first list
				InsertChar(toBeInserted, comesAfter, listHead_1, '1');
			}
		}

		//insert command for second list
		else if ( "insert2" == command )
		{
			char toBeInserted, comesAfter; //to read following arguments
			cin >> toBeInserted >> comesAfter;
			if ( lowerLetterCheck(toBeInserted) && lowerLetterCheck(comesAfter) ) //checks if arguments are valid 
			{
				//inserts first argument after first instance of second argument
					//in second list
				InsertChar(toBeInserted, comesAfter, listHead_2, '2');
			}
		}

		//command for finding similarity
		else if ( "sim" == command )
		{
			//compares two lists in terms of same letters in same position
			Similarity(listHead_1, listHead_2);
		}

		//command to exit the processor
		else if ( "exit" == command )
		{
			cout << "Clearing the two lists and saying Goodbye!" << endl;

			//deletes both lists 
			DeleteList(listHead_1);
			DeleteList(listHead_2);
			listHead_1 = NULL;
			listHead_2 = NULL;

		}

		//in case of a command attempt other than above
		else 
		{
			cout << "Invalid command." << endl << endl;
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
		}

	} while ( "exit" != command );

	cin.get();
	cin.ignore();

	return 0;
}

/*****************************************************************************
This function creates a linked list that has nodes carrying characters from
a file by reading it and returns its head.
Input: file (as file stream object)
Returns: head (node) pointer of created linked list
*****************************************************************************/

node * linkedListCreator (ifstream & file)
{
	char currentChar; //character from current line of read 

	//reading first line for head of the list
	file.get(currentChar);

	//creating the head node of the list
	node * head = new node;
	head->ch = currentChar;
	head->next = NULL;

	node * ptr = head; //cursor to track the list and not to loose head 

	//inserting rest of the lines into new nodes of linked list 
	while (file.get(currentChar))
	{
		//if current character is a valid letter
		if ( currentChar != '\n' && currentChar != '\t' && currentChar != ' ' )
		{
			//creates new node for new character and links it to list
			node * temp = new node;
			temp->ch = currentChar;
			temp->next = NULL;
			ptr->next = temp;
			ptr = temp;
			temp = NULL; 
		}
	}
	ptr = NULL;  

	return head; //returning head of the list 
}

/*****************************************************************************
This function displays the characters stored by nodes consecutively by traversing
a linked list.
Input:  head (node) pointer of a linked list
Returns: display of characters of list
*****************************************************************************/

/* Begin: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */

void DisplayList (node * head) 
{
	node * ptr = head;
    while (ptr != NULL) 
	{
		cout << ptr ->ch;
		ptr = ptr->next;
	}
}

/* End: code taken from ptrfunc.cpp and updated by Pelinsu Sarac */

/*****************************************************************************
This function deletes a whole linked list by deallocating memory storing the
nodes of the list.
Input:  head (node) pointer of a linked list
Returns: deletion of list/head pointer as null pointer
*****************************************************************************/

/* Begin: code taken from 2.2-pointers-linkedlists.ppt */

void DeleteList (node *head) 
{		
  node *temp;				
  while (head != NULL) {				
      temp = head->next;			
      delete head;
      head = temp;
  }
}

/* End: code taken from 2.2-pointers-linkedlists.ppt */

/*****************************************************************************
This function checks if a given argument is a lowercase letter, which is the
case of validity. Returns true if it's valid, false otherwise
Input: argument to be checked
Returns: true if argument is lowercase letter
		 false if argument is anything else 
*****************************************************************************/
 
bool lowerLetterCheck (char charToBeChecked)
{
	if ( charToBeChecked < 'a' || charToBeChecked > 'z' )
	{
		cout << "Invalid arguments." << endl << endl;
		return false;
	}
	return true;
}

/*****************************************************************************
This function finds the node with specified character in a linked list, if
character exists in the list, and returns a pointer pointing at it by reference.
In case of a find, it also returns true. 
If it cannot find any such node, it returns a null pointer by reference and false.
Input: character to be found, node pointer, head pointer of a list
Returns: node pointer pointing at node with character in case of find (by reference)
		 true if character is found
		 false if character is not found  
*****************************************************************************/

bool findNode(char charToBeFound, node * & nodeToBeFound, node * head)
{
	node * ptr = head; //pointer to traverse over list without loosing the head

	while (ptr != NULL)
	{
		//in case of find:
		if (charToBeFound == ptr->ch)
		{
			nodeToBeFound = ptr; //return pointer pointing at node with character
			return true;
		}
		ptr = ptr->next; //move to next node
	}

	//in case of not found 
	nodeToBeFound = NULL;
	return false;
}

/*****************************************************************************
This function deletes a node form a linked list that is pointed by a pointer
without breaking form of linked list.
Input: node pointer pointing at node to be deleted, head pointer of a linked 
	   list
Returns: updated linked list with deleted node
*****************************************************************************/

/* Begin: code taken from ptrfunc.cpp */

void DeleteOneNode (node * toBeDeleted, node * & head)
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	node * ptr;
		
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{
		head = head->next;
		delete toBeDeleted;
	}
	else  //if the node to be deleted is in the middle or at the end
	{
		ptr = head;
		while (ptr->next != toBeDeleted)
			ptr = ptr->next;
		//after while ptr point to the node just before toBeDeleted

		//connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}

/* End: code taken from ptrfunc.cpp */

/*****************************************************************************
This function compares two linked lists in terms of same characters in same
position, counts such characters and displays this number.
Input: head pointers of two linked lists
Returns: displays number of same characters in same position in two lists
*****************************************************************************/

void Similarity(node * ptr1, node * ptr2)
{
	cout << "Displaying the contents of the two lists:" << endl;
	cout << "List1: ";
	DisplayList(ptr1);
	cout << endl << "List2: ";
	DisplayList(ptr2);
	cout << endl;
	int similarCount = 0; //counter to count same letters at same position 

	while ( ptr1 != NULL && ptr2 != NULL ) //till the end of one of the lists
	{
		//if characters are same, increment the counter
		if ( ptr1->ch == ptr2->ch )
		{
			similarCount++;
		}
		
		//both pointers moves at same time so that we can check same position in both lists 
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}

	cout << "There is/are " << similarCount << " letter(s) matched in the same positions in both lists." << endl << endl;
}

/*****************************************************************************
This function deletes all occurances of a specified character from a linked
list, if this character exists. If not, it displays a message indicating the
situation. 
Input: character to be deleted, head pointer to a linked list, list number
	   (for prompts)
Returns: updated list by deleting all occurances of character (through referenced
	     head pointer)
*****************************************************************************/

void DeleteChar(char charToBeDeleted, node * & listHead, char listNum)
{
	//finds first occurance of character in list
	node * toBeDeleted = NULL;
	bool isFound = findNode (charToBeDeleted, toBeDeleted, listHead);

	//if such character does not exist
	if ( !isFound )
	{
		cout << "No deletion as the value " << charToBeDeleted << " was not found in the list" << endl << endl;
	}

	//if character exists
	else
	{
		cout << "Deleting all occurrences of " << charToBeDeleted << " in List" << listNum << "." << endl;

		node * nextToDeleted = toBeDeleted->next; //to track beginning of rest of the list

		//loops till no occurance of character left
		while ( isFound )
		{
			DeleteOneNode(toBeDeleted, listHead); //deletes the node with character
			//searches next occurance of character in rest of the list 
			isFound = findNode(charToBeDeleted, toBeDeleted, nextToDeleted);
			if ( toBeDeleted != NULL )
			{
				nextToDeleted = toBeDeleted->next;
			}
		}
					
		cout << "The current content of List" << listNum << " is: ";
		DisplayList(listHead);
		cout << endl << endl;
	}
}

/*****************************************************************************
This function inserts a character after first occurance of a specified character
in a linked list. If the specified character does not exist in list, then 
character insertion done at the beginning of list.
Input: character to be inserted, character that insertion will be done after,
	   head pointer of a linked list, list number (for prompts)
Returns: updated list by insertion of character (through referenced head pointer)
*****************************************************************************/

void InsertChar(char toBeInserted, char comesAfter, node * & listHead, char listNum)
{
	cout << "Inserting " << toBeInserted << " after " << comesAfter << " in List" << listNum << "." << endl;

	//finds the node with character that insertion will be done after
	node * nodeComesAfter = NULL;
	bool isFound = findNode(comesAfter, nodeComesAfter, listHead);

	//if such node is not found
	if ( !isFound )
	{
		cout << "The node with " << comesAfter << " value does not exist. Therefore, Inserting " << toBeInserted 
					<< " at the beginning of the list." << endl;

		//insertion of character is done at the beginning of list
		node * temp = new node;
		temp->ch = toBeInserted;
		temp->next = listHead;
		listHead = temp;
		temp = NULL;
	}

	//if such node is found
	else
	{
		cout << "The node with " << toBeInserted<< " has been inserted after the first occurrence of a node with " << comesAfter 
					<< " value." << endl;

		//insertion of the character is done after this node
		node * temp = new node;
		temp->ch = toBeInserted;
		temp->next = nodeComesAfter->next;
		nodeComesAfter->next = temp;
		temp = NULL;
	}
	cout << "The current content of List" << listNum << " is: ";
	DisplayList(listHead);
	cout << endl << endl;
}
