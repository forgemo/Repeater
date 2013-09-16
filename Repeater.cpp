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