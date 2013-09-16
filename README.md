Repeater
========

A scheduling library for Arduino, which is extremely simple and lightweight. 


The basic idea
--------------

- You define an array of functions.
- You create a `Repeater` that calls these functions repeatedly.
- Every function has to return the milliseconds to wait until it wants be called again.


Features
--------

- Extremely simple and lightweight 
- The `Repeater` dynamically calculates, how long you may `delay()` your main loop between function calls to maximize your energy efficency.


Limits
------

- You can't dynamically add/remeove functions to/from a `Repeater` once it is created. 
- A function call can be delayed by other scheduled functions that take to long. (Non preemptive strategy)
- In your code, you must not make any assumptions about the execution order of scheduled functions. 


Example
=======

This is a fully working Arduino example sketch. It will be followed by a step-by-step explaination.

```cp
#include <Repeater.h>


unsigned long everySecond(){
  Serial.println("1 Second has passed!");
  return 1000;
}

unsigned long everyTwoSeconds(){
  Serial.println("2 Seconds have passed!");
  return 2000;
}


TaskFunction tasks[] = {everySecond, everyTwoSeconds};

Repeater repeater(tasks, 2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(repeater.tick());       
}

```


Step-by-Step
-----------


First, you need to include the library.

```cpp
#include <Repeater.h>
````

----------

Now you need a few functions, that can be scheduled. These functions have to return an `unsigned long` and
take no arguments. Functions that match these criteria are defined as `TaskFunction`. The return value tells the `Repeater` how long it should wait until the `TaskFunction` want's to be called again (in milliseconds).

```cpp
unsigned long everySecond(){
  Serial.println("1 Second has passed!");
  return 1000;
}

unsigned long everyTwoSeconds(){
  Serial.println("2 Seconds have passed!");
  return 2000;
}
```

----------

The next step is to create an array of TaskFunctions that can be passed to the `Repeater`.

```cpp
TaskFunction tasks[] = { everySecond, everyTwoSeconds};
```

----------

Now it's time to create a `Repater`. It's constructor takes two arguments. 
The first agrument is a `TaskFunction` array. The second argument is the number of elements in that array.

```cpp
Repeater repeater(tasks,2);
```

If you don't like the hardcoded `2`, you can get the number of array elements by doing the following calculation. This, however, works only if the array was not passed as a function argument to your code.

```cpp
sizeof(tasks)/sizeof(tasks[0])
```

----------

The last step is to call the Repeaters `tick()` method in your main loop. Every time the `tick()` method is called, the Repeater will call all scheduled TaskFunctions that are due.

The `tick()` method returns an `unsigned long` that describes aproximately the time in milliseconds until the next `tick()` call needs to be done. You may delay your main loop by exactly this amount of time to maximize your energy efficency.


```cpp
void loop() {
  delay(repeater.tick());       
}
```


Disclaimer
----------
- Since I'm a Java Developer, writing C++ code is for me quite unintuitive. Please tell me if I did something stupid or unconventional.
- There are some much more advanced scheduling libraries for Arduino available. This library is not going to compete with them. 
- I want to keep it as stupid and simple as possible.


