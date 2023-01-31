#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>         // for chrono::system_clock
#include <ctime>		  // for time_t, tm, localtime, mktime
#include <iomanip>  
#include <random>
#include <time.h>
#include "psarac_Sarac_Pelinsu_hw7_HW7PrintQueue.h"

using namespace std;

/******************************************************************************
Purpose: This program is a printer simulation
		 Made for Sabanci University CS 204 Course HW-7
Author: Pelinsu Sarac
Date: 10/06/2022
Written on: MS Visual Studio 2012 
******************************************************************************/

HW7PrintQueue printQueue; //shared queue for print jobs
mutex queueMutex, coutMutex; //mutexes for queue and cout display
int maxPrintJobs, minWaitDuration, maxWaitDuration, minPage, maxPage; 
int printJobID = 0; //to track print job ID's and how many jobs have been done

/*****************************************************************************
This function is a thread-safe random integer generator.
Input: limits of the range that the random number will be coming from (min and max)
Returns: random integer from given range
*****************************************************************************/

/* Begin: code taken from CS204_Homework7_Spring2022.pdf */
int random_range(const int & min, const int & max){
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}
/* End: code taken from CS204_Homework7_Spring2022.pdf */

/*****************************************************************************
This function the path of execution for users of printer. Each user waits for
a random amount of time before first print job they would add to queue, then they
will continue to add to queue until maximum amount of jobs is produced. Each user
also waits for a random amount of time after each addition of job to queue.
Input: user ID
Returns: print job enqueues and displays of enqueue times
*****************************************************************************/

void User(int userID)
{
	//thread sleeps for a random amount of time before first print job 
	int randomWait = random_range(minWaitDuration, maxWaitDuration); 
	/* Begin: code taken from threads7.cpp and updated by Pelinsu Sarac */
	this_thread::sleep_for (chrono::seconds(randomWait)); 
	/* End: code taken from threads7.cpp and updated by Pelinsu Sarac */

	bool ContinueThread = true; //to track if thread must continue to produce more print jobs
	
	/* Begin: code taken from ProducerConsumer.cpp and updated by Pelinsu Sarac */
	while (ContinueThread) 
	{
		queueMutex.lock();
		//if there still more jobs to be created
		if (printJobID < maxPrintJobs)
		{
			//thread adds a new job to queue
			int randomPageNum = random_range(minPage, maxPage); //random amount of pages for print job
			printJobID++; 
			int currentPrintID = printJobID;
			printQueue.enqueue(printJobID, randomPageNum);
			int currentQueueSize = printQueue.getCurrentSize();
			queueMutex.unlock(); 

			//displays when did thread enqueued new job
			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 

			cout <<"User " << userID << " sent new print job with ID " << currentPrintID << " sent to the printer queue, number of pages: " 
				<< randomPageNum << " (print queue size: " << currentQueueSize << ") " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();
		
			//sleep after print job enqueue for a random amount of time
			int randomWait = random_range(minWaitDuration, maxWaitDuration);
			this_thread::sleep_for (chrono::seconds(randomWait));
		}

		//if there is no more job to be created, unlocks mutex and finishes
		else
		{
			queueMutex.unlock();
			ContinueThread = false;
		}
	}
}

/*****************************************************************************
This function the path of execution for printer. It prints (dequeues) the 
maximum amount of print jobs specified by the user at the beginning of program.
It displays when it starts to and ends the print job, while waiting for each
print job for a correlated amount of time with pages of print job in between.
Input: None
Returns: print job deques and displays of start-finish times of print jobs 
*****************************************************************************/

void Printer()
{
	int currentPrintJobID, currentPageNum; //to read job information from queue 
	int counter = 0; //to track if maximum amount of print job is done 

	while (counter < maxPrintJobs)
	{
		//if queue is not empty
		queueMutex.lock();
		if (!printQueue.isEmpty())
		{
			//reads the job information from queue and removes the job 
			printQueue.dequeue(currentPrintJobID, currentPageNum);
			counter++;
			int currentQueueSize = printQueue.getCurrentSize();
			queueMutex.unlock();

			//displays when print job starts
			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<< "The printer started to print the job with ID: " << currentPrintJobID << ", number of pages: " << currentPageNum 
				<< " (queue size is: " << currentQueueSize << ") " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();

			this_thread::sleep_for(chrono::seconds(currentPageNum)); // simulation for print, 1 second for each page

			//displays when print job finishes
			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now());  
			localtime_s(ptm, &tt); 
			cout<< "The printer finished printing the job with ID: " << currentPrintJobID << ", number of pages: " << currentPageNum 
				<< " " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();
		}
		//if queue is empty at that moment, unlocks the mutex so users can add jobs
		else {queueMutex.unlock();}
	}
}
/* End: code taken from ProducerConsumer.cpp and updated by Pelinsu Sarac */

/*****************************************************************************
Main takes the inputs needed for the simulation to start, then initializes and 
joins the user and printer threads. It also displays starting and ending times
of the simulaiton.
Input: Maximum print job, minimum and maximum duration of wait for user, maximum
and minimum number of pages of a print job
Returns: execution of threads/simulation, display of times of start and finish
		of simulation
*****************************************************************************/

int main()
{
	//takes the inputs
	cout << "Please enter the max number of print jobs: ";
	cin >> maxPrintJobs;
	cout << "Please enter the min and max values for the waiting time period (in seconds) after creating a print job:" << endl;
	cout << "Min: ";
	cin >> minWaitDuration;
	cout << "Max: ";
	cin >> maxWaitDuration;
	cout << "Please enter the min and max values for the number of pages in a print job:" << endl;
	cout << "Min number of pages: ";
	cin >> minPage;
	cout << "Max number of pages: ";
	cin >> maxPage;

	/* Begin: code taken from threads8.cpp */
	time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
	struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
	localtime_s(ptm, &tt);  //converting the time structures
	cout << "Simulation starts " << put_time(ptm,"%X") << endl;  //displaying the time
	/* End: code taken from threads8.cpp */

	//starts the threads 
	thread user_1(User, 1);
	thread user_2(User, 2);
	thread user_3(User, 3);
	thread printer(Printer);

	//joins threads, waits for them to finish
	user_1.join();
	user_2.join();
	user_3.join();
	printer.join();

	/* Begin: code taken from ProducerConsumer.cpp */
	tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
	localtime_s(ptm, &tt);  //converting the time structures
	cout << "End of the simulation ends " << put_time(ptm,"%X") << endl;  //displaying the time
	/* End: code taken from ProducerConsumer.cpp */

	cin.get();
	cin.ignore();

	return 0;
}
