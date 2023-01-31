#include <iostream>
#include <vector>
#include <fstream>  //for ifstream
#include <sstream>  //for stringstream
#include <string>

using namespace std;

/******************************************************************************
Purpose: This program is Sabanci version of game Wordle - SWordle
		 Made for Sabanci University CS 204 Course HW-1 
Author: Pelinsu Sarac
Date: 13/03/2022
Written on: MS Visual Studio 2012 
******************************************************************************/

/******************************************************************************
This structure is to store a letter from the guess with a color code,
specifying its existance and position in word to be guessed
******************************************************************************/
struct cell
{
 char letter; // letter inside the cell
 char color; // color of the cell
};

//PROTOTYPES:

//extracts the information from a file
void readFile(ifstream & input, int & numOfAttempts, int & numOfLetters, string & wordToBeGuessed);

//prints out the guess matrix
void printMatrix(vector <vector <cell>> & matrix);

//does all input checks on guess in order
bool inputCheckCombined(const string & guess, const string & wordToBeGuessed, int attemptsTaken,
							vector <vector <cell> > & guessMatrix, bool & isGreenLetterFound);

//checks if guess' length matches with the word to be guessed
bool correctLengthCheck (const string & guess, const string & wordToBeGuessed);

//checks if there is an illegal character in the guess
bool illegalCharCheck (const string & guess);

//checks if there are duplicating characters in guess
bool repeatingCharCheck (const string & guess) ;

//checks if a guess was made before 
bool repeatedGuessCheck (vector <vector <cell> > & guessMatrix, const string & guess, int attemptsTaken);

//checks if green letters from previous guesses were used in new guess
bool greenLetterCheck (vector <cell> & lastGuess, const	string & guess);

//updates guess matrix according to a plausible guess
void  updateMatrix(vector<vector<cell>> & guessMatrix, string & guess, string & wordToBeGuessed, 
						int attemptsTaken, bool & isGreenLetterFound);

//transforms a row of guess matrix from cell format to string 
string rowFromCellToString (vector <cell> & row);

int main() 
{
	 /******************************************************************************
	 This part takes a filename from the user repeatedly until file can be opened 
	 successfuly and extracts the number of allowed attempts, word to be guessed
	 and its number of letters from file.
	 Input: filename
	 Returns: number of allowed attempts, word to be guessed, number of letters of 
			  the word
	 ******************************************************************************/
	
	string filename; //name of the file to be read

	cout << "Welcome to SWordle!" << endl;
	cout << "Please enter the file name: ";
	cin >> filename;

	ifstream input; //file object, to be able to read the file 
	input.open(filename.c_str());

	//takes filename again until a valid filename is entered 
	while ( input.fail() )
	{
		cout << "Couldn't find the file!" << endl;
		cout << "Please enter the file name: ";
		cin >> filename;
		input.open(filename.c_str()); 
	}

	int numOfAttempts = 0;	 //number of allowed attempts 
	int numOfLetters = 0;	//number of letters of the word
	string wordToBeGuessed; //word to be guessed by user 

	//extracts the elements above from file
	readFile(input, numOfAttempts, numOfLetters, wordToBeGuessed);

	input.close();


	 /******************************************************************************
	 This part displays the number of allowed attempts and number of letters in the 
	 word to be guessed, then creates a matrix to store guesses with empty cells.
	 Input: the number of allowed attempts, number of letters
	 Returns: matrix to store guesses with empty cells
	 ******************************************************************************/

	cout << "The word that you will guess has " << numOfLetters << " letters and you have " << numOfAttempts << " attempts." << endl;

	//initializes a "number of allowed attempts" by "number of letters" matrix with empty cells

	cell initialCell = { '-', '-' }; //empty cell to be updated
	vector <vector <cell>> guessMatrix (numOfAttempts, vector <cell> (numOfLetters, initialCell)); //matrix to store guesses


	/******************************************************************************
	 This part asks for valid guesses from user, then updates the guess matrix with
	 these guesses and displays it. Process continues until either user enters the
	 correct word or he/she's out of attempts.
	 Input: number of attempts, word to be guessed, guess matrix, guess
	 Returns: updated matrix and appropriate messages for gameplay
	 ******************************************************************************/
 
	bool isCorrectWord = false;		  //flag to track if correct word is entered 
	int attemptsTaken = 0;			  //counter to track used attempts by user 
	bool isGreenLetterFound = false;  //flag to track if any green letter found in guesses
											//and green letter input check is needed

	//asks for guesses until correct word or end of attempts
	for ( ; !isCorrectWord && attemptsTaken < numOfAttempts; ) 
	{
		string guess; //string to store current guess

		//asks for a guess until a valid one is entered 
		do 
		{
			cout << "What's your guess? ";
			cin >> guess;
		} while ( !inputCheckCombined(guess, wordToBeGuessed, attemptsTaken, guessMatrix, isGreenLetterFound) ); 

		//adds new guess to guess matrix with color codes
		updateMatrix(guessMatrix, guess, wordToBeGuessed, attemptsTaken, isGreenLetterFound); 

		//displays current state of guess matrix
		printMatrix(guessMatrix);

		attemptsTaken++; 

		//checks if correct word is entered 
		if (guess == wordToBeGuessed)
		{
			isCorrectWord = true;
		}
	}

	//checks why game ended: due to correct guess or run out of attempts?
	if ( isCorrectWord == true ) 
	{
		cout << "You win!" << endl;
	}
	else if ( isCorrectWord == false && attemptsTaken == numOfAttempts )
	{
		cout << "You lose!" << endl;
	}

	cin.get();
	cin.ignore();

	return 0;
}


/*****************************************************************************
This function extracts the number of attempts allowed, word to be guessed
and number of letters in word to be guessed from the opened file.
Input: file object, number of attempts, number of letters, word to be guessed
Returns: number of attempts, number of letters, word to be guessed
*****************************************************************************/

void readFile(ifstream & input, int & numOfAttempts, int & numOfLetters, string & wordToBeGuessed)
{
	string line1, line2; //strings that each representing a line in file

	//reading first line as number of attempts
	getline(input, line1);
	stringstream streamLine1(line1);
	streamLine1 >> numOfAttempts;

	//reading second line as the word to be guessed 
	getline(input, line2);
	stringstream streamLine2(line2);
	streamLine2 >> wordToBeGuessed;

	//finding the number of letters of the word to be guessed 
	numOfLetters = wordToBeGuessed.length();
}


/*****************************************************************************
This function displays the matrix storing guesses in an ordered and readible 
way for user with the color codes for each letter in each guess.
Input: guess matrix
*****************************************************************************/

/* Begin: code taken from MatrixDemo1.cpp and updated by Pelinsu Sarac */

void printMatrix(vector <vector <cell>> & matrix)
{
	int rows = matrix.size();
	int columns = matrix[0].size();

	for (int i = 0; i < rows; i++) 
	{
		cout << "||";
		for (int j = 0; j < columns; j++) 
		{
			cout << " " << matrix[i][j].letter << " , " << matrix[i][j].color << " ||";
		}
		cout << endl;
	}
}

/* End: code taken from  MatrixDemo1.cpp and updated by Pelinsu Sarac */


/*****************************************************************************
This function evaluates a guess given by user in terms of validness by applying
all input checks in order.
Input: guess, word to be guessed, number of used attempts, guess matrix, green
	   letter flag
Returns: true if guess passes all checks
		 false if guess fails at least one check 
*****************************************************************************/

bool inputCheckCombined(const string & guess, const string & wordToBeGuessed, int attemptsTaken,
							vector <vector <cell> > & guessMatrix, bool & isGreenLetterFound)
{
	//checks if guess has the correct amount of letters 
	if ( !correctLengthCheck (guess, wordToBeGuessed) )
	{
		return false;
	}

	//checks if guess includes any illegal characters
	if ( !illegalCharCheck (guess) )
	{
		return false;
	}

	//checks if guess has any repeating letters 
	if ( !repeatingCharCheck(guess) )
	{
		return false;
	}

	if ( attemptsTaken > 0)   //if previous guesses were done:
	{
		//checks if the same guess was done before 
		if ( !repeatedGuessCheck (guessMatrix, guess, attemptsTaken) ) 
		{
			return false;
		}
	
		//checks if guess includes correct letters in correct positions that found in previous guesses
		if ( isGreenLetterFound && !greenLetterCheck(guessMatrix[attemptsTaken-1], guess) )
		{
			return false;
		}
	}
	

	return true;
}


/*****************************************************************************
This function compares guess entered by user and the word to be guessed in terms
of length and if the guess is too long or too short, it displays an error 
message accordingly.
Input: guess, word to be guessed
Returns: true if guess has same length with word to be guessed
		 false if guess is longer or shorter
*****************************************************************************/

bool correctLengthCheck (const string & guess, const string & wordToBeGuessed) 
{
	//if the guess is longer than word to be guessed
	if ( guess.length() > wordToBeGuessed.length() )
	{
		cout << "The word is too long!" << endl;
		return false;
	}
	//if the guess is shorter than word to be guessed
	else if ( guess.length() < wordToBeGuessed.length() )
	{
		cout << "The word is too short!" << endl;
		return false;
	}
	else //if the guess has same length with word to be guessed
	{
		return true;
	}
}


/*****************************************************************************
This function checks if guess has any illegal characters, in this case any 
character except lowercase letters, in it and if so, it displays an error 
message.
Input: guess
Returns: true if guess has no illegal characters/all lowercase letters
		 false if guess contains illegal characters 
*****************************************************************************/

bool illegalCharCheck (const string & guess) 
{ 
	for (unsigned int i = 0; i < guess.length(); i++) 
	{
		if ( guess.at(i) < 'a' || guess.at(i) > 'z' ) 
		{
			cout << "Your input has illegal letters!" << endl;
			return false;
		}
	}
	return true;
}


/*****************************************************************************
This function checks if guess has any repeating letters in it and if so, it
displays an error message.
Input: guess
Returns: true if guess has no repeating letters
		 false if guess contains a repeating letter 
*****************************************************************************/

bool repeatingCharCheck (const string & guess) 
{
	for (unsigned int i = 0; i < guess.length(); i++)
	{
		char charToBeChecked = guess.at(i);
		if ( guess.find(charToBeChecked) != guess.rfind(charToBeChecked) ) 
		{
			cout << "Your input has a duplicate letter!" << endl;
			return false;
		}
	}
	return true;
}


/*****************************************************************************
This function checks if guess was tried previously and if so, it displays an 
error message.
Input: guess matrix, guess, number of used attempts
Returns: true if guess was not tried before
		 false if guess was tried before  
*****************************************************************************/

bool repeatedGuessCheck (vector <vector <cell> > & guessMatrix, const string & guess, int attemptsTaken)
{
	for (int i = 0; i < attemptsTaken; i++) 
	{
		if ( rowFromCellToString(guessMatrix[i]) == guess ) 
		{
			cout << "You've already tried this word!" << endl;
			return false;
		}
	}
	return true;
}


/*****************************************************************************
This function checks if guess includes correct letters in correct positions/green 
letters that found in previous guesses and if not, it displays an error message.
Input: last row from guess matrix that was updated, guess
Returns: true if guess includes green letters
		 false if guess doesn't include green letters 
*****************************************************************************/

bool greenLetterCheck (vector <cell> & lastGuess, const string & guess)
{
	for (unsigned int i = 0; i < lastGuess.size(); i++)
	{
		if (lastGuess[i].color == 'G' && lastGuess[i].letter != guess.at(i))
		{
			cout << "You did not use the green letter in your word!" << endl;
			return false;
		}
	}
	return true;
}


/*****************************************************************************
This function updates the guess matrix with the new valid guess by inserting 
letters of guess in cells and deciding color codes for each. Color codes are:
	* B: black, letter doesn't exist in word to be guessed
	* Y: yellow, letter exists in word to be guessed but in wrong position
	* G: green, letter exists in word to be guessed and in correct position
In case of green letter, it also turns green letter flag to true.
Input: guess, guess matrix, word to be guessed, number of used attempts,
	   green letter flag
Returns: updated matrix with new guess, current state of green letter flag
*****************************************************************************/

void  updateMatrix(vector<vector<cell>> & guessMatrix, string & guess, string & wordToBeGuessed, 
						int attemptsTaken, bool & isGreenLetterFound)
{
	for (unsigned int i = 0; i < guess.length(); i++)
	{
		char charToBeChecked = guess.at(i); //to track each letter from guess
		guessMatrix[attemptsTaken][i].letter = charToBeChecked; //inserts letter in cell

		//color code check:

		//if letter exists in word to be guessed and in correct position, G
		if (guess.find(charToBeChecked) == wordToBeGuessed.find(charToBeChecked))
		{
			guessMatrix[attemptsTaken][i].color = 'G';

			//making green letter input check available for the next attempt
			if ( !isGreenLetterFound )
			{
				isGreenLetterFound = true;
			}
		}
		//if letter doesn't exist in word to be guessed, B
		else if (wordToBeGuessed.find(charToBeChecked) == string::npos) 
		{
			guessMatrix[attemptsTaken][i].color = 'B';
		}
		else //if letter exists in word to be guessed but in wrong position, Y
		{
			guessMatrix[attemptsTaken][i].color = 'Y';
		}
	}
}


/*****************************************************************************
This function transforms a row of guess matrix from cell format to string, 
giving the ability to compare previous gusses with new guess.
Input: a row from guess matrix 
Returns: guess on that row in string 
*****************************************************************************/

string rowFromCellToString (vector <cell> & row)
{
	string word = ""; //string to hold letters coming from cells

	//extracting each letter one by one from a row
	for (unsigned int i = 0; i < row.size(); i++)
	{
		word += row[i].letter;
	}

	return word;
}