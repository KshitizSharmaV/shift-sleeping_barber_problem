# SHIFT: Sleeping Barber Problem

*Please use only the C++ standard library in your solution\*, and make sure to provide compiling instructions if no build system is provided. You can use any combination of tools and operating systems to solve this problem, but it should be compilable on a standard Linux installation (i.e. with GCC). Additionally, your solution should make use of objected-oriented programming concepts.*

*Please make sure to also add sufficient comments to your code. Defining "sufficient" is up to you.*

*\* E.g. you should use "std::thread" instead of POSIX threads (a.k.a. "pthreads").*

## Problem Description

This problem is about simulating a barber shop with the following characteristics. The barber shop has a waiting room with *M* seats and a separate room with a single barber chair where the barber works. If there are no waiting customers, nor a customer having a haircut, the barber takes a break and sleeps. The moment a customer arrives, s/he wakes the barber up so that they can have their haircut. If another customer arrives while the barber is working, s/he will either sit in the waiting room (if there are available seats) or leave (if no seats are available).

## Implementation Details

The only (command line) input for your program will be the number *M* of seats in the waiting room. The barber needs to be implemented as a thread which runs indefinitely, always performing one of the 3 possible tasks: sleeping, waking up and working. The barber sleeps if there are no awaiting customers.

There must be a thread which is responsible for creating new threads from time to time to simulate new customers arriving in the barber shop. This thread should run an infinite loop creating new threads every 3 seconds. Each created thread need to receive an integer parameter (sequentially incremented) which will serve as the customer ID.

In the beginning of the program, the barber is sleeping and there are no customers in the shop. When a customer arrives, s/he wakes the barber up so that they can have their haircut. The haircut is to be simulated with a thread sleep of *N* seconds, where *N* is a random number between 1 and 5, inclusive (i.e. [1,5]). If a new customer (thread) arrives while the barber is busy, they should wait in one of the seats of the waiting room, if one is available, or leave if none is available. Leaving is simulated by simply terminating the execution of the thread.

## Expected Output

The program must output the following given the current status of the program:

---

**Case 1**

There are no customers having a haircut and the barber is sleeping while waiting for customers. 

```
Barber sleeping
Waiting room:
```

---

**Case 2**

The barber is cutting the hair of customer 12 and customers 13 to 16 are waiting.

```
Barber cutting the hair of customer 12
Waiting room: 13 14 15 16
```

---

**Case 3**

The barber is cutting the hair of customer 12 and customers 15, 16, 17, 19 and 21 are waiting (assuming there are only 5 seats in the waiting room) when customer 22 arrives and ends up leaving because there are no available seats.

```
Barber cutting the hair of customer 12
Waiting room: 15 16 17 19 21
Customer 22 leaving
```

*Note: given the behavior of the program, customers 13, 14, 18 and 20 must have arrived when no seats were available.*

---

The customer number is the argument given when creating the thread, as explained above.

> If you have any specific questions, please contact me at twinkle1@stevens.edu.

> Good luck!
