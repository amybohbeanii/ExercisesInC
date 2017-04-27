## Chapter 9

## POSIX threads and mutexes

## As you read Chapter 9, you should compile and run the example code. By the nature of multi-threaded programs, you results will probably be different from mine, possibly in interesting ways.

## Why does each thread have its own stack?

## What does the gcc flag -lpthread do?

## What does the argument of pthread_exit do?

## Normally the same thread that created a thread also waits to join it. What happens if another thread tries to join a thread it did not create?

## What goes wrong if several threads try to increment a shared integer at the same time?

## What does it mean to "lock a mutex"?

## Chapter 10

## Condition variables

## What does it mean to say that a data structure is thread safe?
*  both threads (or more than two) can accessthequeueatthesametime. 
## In the circular buffer implementation of a queue, why is the maximum number of elements in the queue n-1, if n is the size of the array?
* bc thats how circular buffer works, push calls queue_incr which will wrap around to 0 when it gets to end of array 
## If there is no mutex to protect the queue, give an example of a sequence of steps that could leave the queue in an inconsistent state.
* if consumer scheduled first, it finds empty queue, prints error message exits.

## When a thread calls cond_wait, why does it have to unlock the mutex before blocking?
*  If cond_wait did not unlock the mutex before blocking, no other thread would be able to access the queue, no more items could be added, and the queue would always be empty. 
## When a thread returns from cond_wait, what do we know is definitely true? What do we think is probably true?
* DEF TRUE: condition is true
* PROBABLY TRUE: Theres an element in queue
## What happens if you signal a condition variable when there are no waiting threads?
* no effect
## Do you have to lock the mutex to signal a condition variable?
* yes for synchronization
## Does the condition have to be true when you signal a condition variable?
* no 
