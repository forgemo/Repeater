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

#include <Arduino.h>
#include "Repeater.h"


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



unsigned long Repeater::tick(){
	unsigned long currentTime = millis();

	// create a timestamp pointer, pointing to the first array element
	unsigned long *timestamp = mExecutionTimestamps;
	// create a task pointer, pointing to the first array element
	TaskFunction *task = mTasks;

	unsigned long nextTickTimestamp = 0;

	for(int i=0; i<mNumberOfTasks; i++)
	{

		if(currentTime >= *timestamp){
			unsigned long nextDelay = (*task)();	
			currentTime = millis();
			*timestamp = currentTime + nextDelay;
		}

		if(nextTickTimestamp == 0){
			nextTickTimestamp = *timestamp;
		}else{
			nextTickTimestamp = min(nextTickTimestamp, *timestamp);
		}

		// move task pointer to next task in the array
    	task++;
    	// move timestamp pointer to next timestamp in the array
    	timestamp++;
	}

	currentTime = millis();

	unsigned long suggestedDelay = 0;

	if(currentTime < nextTickTimestamp){
		suggestedDelay = nextTickTimestamp - currentTime;
	}

	if(suggestedDelay > 50){
		suggestedDelay = suggestedDelay - 50;
	}else{
		suggestedDelay = 0;
	}

	return suggestedDelay;
}