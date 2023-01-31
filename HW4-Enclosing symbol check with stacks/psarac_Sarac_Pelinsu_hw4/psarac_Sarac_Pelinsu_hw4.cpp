#include <iostream>
#include <string>
#include <fstream> //for ifstream
#include "psarac_Sarac_Pelinsu_hw4_DynStackHW4.h"

using namespace std;

/******************************************************************************
Purpose: This program is a C++ Program enclosing symbol checker
		 Made for Sabanci University CS 204 Course HW-4 
Author: Pelinsu Sarac
Date: 12/04/2022
Written on: MS Visual Studio 2012 
******************************************************************************/

int main()
{
	/******************************************************************************
	 This part takes a filename from the user repeatedly until file can be opened 
	 successfuly and opens it as a filestream object to be able to read it
	 Input: filename
	 Returns: file as filestream object
	 ******************************************************************************/
	string filename; //name of the file
	ifstream cppFile; //to hold file as filestream object

	cout << "Please enter the file name: ";
	cin >> filename;
	cppFile.open(filename.c_str());

	//asks for filename until a valid one is entered
	while ( cppFile.fail() )
	{
		cout << "File not found." << endl;
		cout << "Please enter the file name: ";
		cin >> filename;
		cppFile.open(filename.c_str());
	}

	/******************************************************************************
	 This part reads the cpp file character by character and tracks opening or closing
	 paranthesis by doing following:
	 - tracks which line is read
	 - if character is an opening paranthesis, stores it in stack with line number
	 - if character is a closing paranthesis, tries to compare it with lastly opened 
	 paranthesis from stack:
		- if stack is empty, displays error message as no paranthesis was opened
		- if stack is not empty, pops the lastly opened paranthesis from stack and 
		compares; if paranthesis matches then it prompts the match with line numbers, 
		if not it displays error message.
	 In case of an error, it stops reading the file.
	 Input: cpp file as filestream object
	 Returns: error messages in case of paranthesis errors, messages about opening and
	 matching paranthesis otherwise; updated paranthesis stack and error flag
	 ******************************************************************************/

	int lineNumber = 1; //to track the curent line 
	char charFromFile; //to track the characters from file
	bool isAnError = false; //flag to stop reading the file if there is an error
	DynStack paranthesisStack; //stack to store opening paranthesis in order

	while (cppFile.get(charFromFile) && !isAnError)
	{
		// in case of finding an opening paranthesis
		if ( '{' == charFromFile || '[' == charFromFile || '(' == charFromFile )
		{
			cout << "Found the opening symbol " << charFromFile << " at line " << lineNumber << endl;

			//stores it in stack with line number
			paranthesisStack.push(charFromFile, lineNumber);
		}

		//in case of finding a closing paranthesis
		else if ( '}' == charFromFile || ']' == charFromFile || ')' == charFromFile )
		{
			//if stack is not empty, meaning there are opening paranthesis found previously
			if ( !paranthesisStack.isEmpty() )
			{
				char lastOpened; //to store lastly opened paranthesis
				int lastOpenedLine = 0; //to store lastly opened paranthesis' line
				paranthesisStack.pop(lastOpened, lastOpenedLine); 

				// in case of opening and closing paranthesis are matching
				if ( ('{' == lastOpened && '}' == charFromFile) || ('[' == lastOpened && ']' == charFromFile) || 
					('(' == lastOpened && ')' == charFromFile) )
				{
					cout << "Found the closing symbol " << charFromFile << " at line " << lineNumber << " which closes the opening symbol " 
						<< lastOpened << " at line " << lastOpenedLine << endl;
				}

				//in case of opening and closing paranthesis aren't matching
				else 
				{
					cout << "ERROR!!! Found the closing symbol " << charFromFile << " at line " << lineNumber 
						<< " but the last unclosed opening symbol is " << lastOpened << " at line " << lastOpenedLine << endl;
					isAnError = true; //an error has been found
				}
			}

			//if stack is empty, meaning there is no unclosed opening paranthesis previously 
			else
			{
				cout << "ERROR!!! Found the closing symbol " << charFromFile << " but there are no unclosed opening symbols!" << endl;
				isAnError = true; //an error has been found
			}
		}

		//if \n is found, meaning that next character to be read will be from next line
		else if ( '\n' == charFromFile )
		{
			lineNumber++; //thus increasing the line number
		}
		
	} 

	/******************************************************************************
	 This part is executed if there are no previous errors found, to check if there
	 are any unclosed paranthesis left in stack. If there are, then it displays them
	 as an error message. If not, then it displays a message indicating that file
	 doesn't have any paranthesis errors.
	 Input: paranthesis stack, error flag 
	 Returns: error message if there are unclosed paranthesis left including the unclosed
	 paranthesis, confirmation message otherwise indicating that file doesn't have any
	 errors
	 ******************************************************************************/

	//if no errors were found previously
	if ( false == isAnError )
	{
		//in case of unclosed paranthesis left inside stack
		if ( !paranthesisStack.isEmpty() )
		{
			cout << "ERROR!!! The following opening symbols were not closed:" << endl;

			char unclosed; //to track unclosed paranthesis
			int unclosedLine; //to track unclosed paranthesis line number

			//displays the unclosed paranthesis one by one
			while ( !paranthesisStack.isEmpty() )
			{
				paranthesisStack.pop(unclosed, unclosedLine);
				cout << " Symbol " << unclosed << " at line " << unclosedLine << endl;
			}
		}

		//in case of empty stack, meaning that there are no unclosed paranthesis left 
		else 
		{
			cout << "File processed successfully. No errors were found." << endl;
		}
	}

	//closing the file and exiting the program
	cppFile.close();

	cin.get();
	cin.ignore();
	return 0;
}