/*
  Repeater.h - Little task scheduling library for arduino.
  Created by Mohammed El Batya, September 16, 2013.
  Released into the public domain.
*/


// Prevents including the library twice
#ifndef Repeater_h
#define Repeater_h

// Inlcuding Arduino lib
#include <Arduino.h>

// Defining the type "TaskFunction", which is a function that takes no parameters.
// It returns an unsigned long, defining the time until next execution (in millis). 
typedef unsigned long (*TaskFunction) ();


// 
class Repeater{
  public:

    Repeater(TaskFunction pTasks[], int arrayLength);
    ~Repeater();
   
    unsigned long tick();
   
  private:

  	TaskFunction *mTasks;
  	int mNumberOfTasks;
  	unsigned long *mExecutionTimestamps;

};



// Finishing the ifndef from above
#endif
