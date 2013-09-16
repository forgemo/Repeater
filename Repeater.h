/*
  Repeater.h - Little task scheduling library for arduino.
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
