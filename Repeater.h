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

//===============================================================================
// Preprocessor Directives
//===============================================================================


// Prevents including this library twice
#ifndef Repeater_h
#define Repeater_h


//===============================================================================
// Includes
//===============================================================================

#include <Arduino.h>


//===============================================================================
// Typdefs
//===============================================================================

/**
  Defining the type "TaskFunction", which is a function that takes no arguments.
  It returns an unsigned long, representing the time until the next call (in millis).
  
  For example: 
                unsigned long myFunction(){
                  return 1000;
                }
*/
typedef unsigned long (*TaskFunction) ();



//===============================================================================
// Classes
//===============================================================================


/**
  The Repeater class takes an array of TaskFnctions.
  Every time it's tick() method is called, it checks for due TaskFunctions and
  calls them.
*/
class Repeater{
  
  public:

    /**
      Constructs a Repeater instance. 
       
      @param pTasks An array of TasksFunctions.
      @param pArrayLength The length of the pTasks array.
        
    */
    Repeater(TaskFunction pTasks[], int pArrayLength);
    
    /**
      Destructs the Repeater instance. 
     */
    ~Repeater();
   
   /**
      Every time the tick() method is called, the Repeater will call all
      scheduled TaskFunctions that are due.

      @return An unsigned long that describes aproximately the time in
              milliseconds until the next tick() call needs to be done. 
              You may delay your main loop by exactly this amount of time to 
              maximize your energy efficency.  
    */
    unsigned long tick();
   
  private:

    /** 
      The TaskFunction array.
  	*/
    TaskFunction *mTasks;

    /**
      The length of the mTasks array.
  	*/
    int mNumberOfTasks;

    /**
      An array of timestamps.
      A timestamp arrayin this  describes the next execution time the
      TaskFunction in mTasks with the same array index.
    */
  	unsigned long *mExecutionTimestamps;

};


//===============================================================================
// Preprocessor Directives
//===============================================================================

// Finishing the ifndef from above
#endif
