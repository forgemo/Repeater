/*
  Repeater.cpp
  Created by Mohammed El Batya, September 16, 2013.
 
  --------------------------------------------------------------------------------
  The MIT License (MIT)
  
  Copyright (c) 2013 Mohammed El Batya

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  --------------------------------------------------------------------------------
*/


//===============================================================================
// Includes
//===============================================================================

#include <Arduino.h>
#include "Repeater.h"


//===============================================================================
// Constructors / Destructor
//===============================================================================

Repeater::Repeater(TaskFunction pTasks[], int pNumberOfTasks){
	mTasks = pTasks;
	mNumberOfTasks = pNumberOfTasks;

	mExecutionTimestamps = new unsigned long[pNumberOfTasks];

	unsigned long currentTime = millis();

	for(int i=0; i<pNumberOfTasks; i++){
		mExecutionTimestamps[i] = currentTime;
	}
}

Repeater::~Repeater(){
	delete [] mExecutionTimestamps;
}

//===============================================================================
// Methods
//===============================================================================

unsigned long Repeater::tick(){

	unsigned long currentTime = millis();

	// Create a timestamp pointer, pointing to the first array element in
	// mExecutionTimestamps.
	unsigned long *timestamp = mExecutionTimestamps;

	// Create a TaskFunction pointer, pointing to the first array element in
	// mTasks.
	TaskFunction *task = mTasks;

	// We will determine further below, when the next call to tick() should happen.
	// This variable will hold the final result. We initialize it with -1, which 
	// leads to a number underflow since it's an unsigned long. It has, therefore,
	// )for the moment) the maximum possible value an unsigned long can hold.
	unsigned long nextTickTimestamp = -1;

	// Repeat <mNumberOfTasks> times to iterate over all elements in mTask and
	// mExecutionTimestamps.
	for(int i=0; i<mNumberOfTasks; i++){

		// If the execution of the current task is due ...
		if(currentTime >= *timestamp){
			// ... execute the current task and store its return value, which is
			// the amount of time to wait until it wants to be called again.
			unsigned long nextDelay = (*task)();

			// Update the currentTime, since the current tasks execution could
			// have taken a considerable amount of time.	
			currentTime = millis();

			// Update the execution timestamp for the current task to it's next
			// desired execution time.
			*timestamp = currentTime + nextDelay;
		}

		// Update nextTickTimestamp to be (after the loop finishes) the earliest 
		// of all next-task-execution timestamp.  
		nextTickTimestamp = min(nextTickTimestamp, *timestamp);
		
		// Move task pointer to next task in the array.
    	task++;
    	// Move timestamp pointer to next timestamp in the array.
    	timestamp++;
	}

	// Update the currentTime again, just to be sure :)
	currentTime = millis();

	// Based on the nextTickTimestamp, we want to suggest an approximate delay to
	// the caller of tick(), until the next call to tick() should happen.  
	// This variable is initialized with 0, which means 'no delay at all', and 
	// will hold the final result.
	unsigned long suggestedDelay = 0;

	// If nextTickTimestamp is in the future, calculate the difference between
	// now and nextTickTimestamp. Store the result in suggestedDelay.
	if(currentTime < nextTickTimestamp){
		suggestedDelay = nextTickTimestamp - currentTime;
	}

	// If the suggestedDelay is longer than 10 milliseconds ...
	if(suggestedDelay > 10){
		// ... reduce it by 10 milliseconds to add a little buffer, ensuring to be
		// called on time.
		suggestedDelay = suggestedDelay - 10;
	}else if(suggestedDelay > 1 && suggestedDelay < 10){
		// If the suggestedDelay is from 2 to 10 milliseconds, we will always suggest
		// a delay of 1 millisecond.
		suggestedDelay = 1;
	} // Otherwise, (for 0 and 1 milliseconds) the suggestedDelay wil be 0.

	return suggestedDelay;
}