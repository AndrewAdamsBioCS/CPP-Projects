/*
* Queue.h
*
* Class Description: A standard queue of fixed capacity using a
*					 circular-array implementation
* Class Invariant: FIFO/LILO. Elements added to back of queue
*				   and removed from front
* Created on: June 20, 2017
* Author: Andrew Adams
*/

#pragma once
#include <iostream>
#include "Event.h"
#include "EmptyDataCollectionException.h"

using namespace std;

template <class ElementType>
class Queue {

	private:
		static const int CAPACITY = 100;		// Fixed capacity of queue
		ElementType elementQueue[CAPACITY];		// Array of queue capacity
		int front;								// Index of front of queue
		int back;								// Index of back of queue
		int elementCount;						// Element count

	public:
		// Constructor
		Queue();

		/******* Public Interface - START - *******/
	        
		// Description: Returns the number of elements in the Queue.
		// (This method eases testing.)
		// Time Efficiency: O(1)
		int getElementCount() const;

		// Description: Returns "true" is this Queue is empty, otherwise "false".
		// Time Efficiency: O(1)
		bool isEmpty() const;
	   
		// Description: Adds newElement to the "back" of this Queue 
		//              (not necessarily the "back" of its data structure) and 
		//              returns "true" if successful, otherwise "false".
		// Time Efficiency: O(1)
		bool enqueue(const ElementType& newElement);

		// Description: Removes the element at the "front" of this Queue 
		//              (not necessarily the "front" of its data structure) and  
		//              returns "true" if successful, otherwise "false".
		// Precondition: This Queue is not empty.
		// Time Efficiency: O(1)
		bool dequeue();
	   
		// Description: Returns (a copy of) the element located at the "front" of this Queue.
		// Precondition: This Queue is not empty.
		// Postcondition: This Queue is unchanged.
		// Exceptions: Throws EmptyDataCollectionException if this Queue is empty.
		// Time Efficiency: O(1)
		ElementType peek() const throw(EmptyDataCollectionException);  

		/******* Public Interface - END - *******/

		// Description: 
		// Precondition: This Queue is not empty.
		// Postcondition: This Queue is unchanged.
		// Time Efficiency: O(n)
		void printQueue();
	      
}; // end Queue



using namespace std;

// Constructor
template <class ElementType>
Queue<ElementType>::Queue() {
	front = 0;
	back = CAPACITY - 1;
	elementCount = 0;
} // end default constructor


// Description: Returns the number of elements in the Queue.
// (This method eases testing.)
// Time Efficiency: O(1)
template <class ElementType>
int Queue<ElementType>::getElementCount() const {
	return elementCount;
}

// Description: Returns "true" is this Queue is empty, otherwise "false".
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::isEmpty() const {

	bool empty;

	if (elementCount == 0)
		empty = true;
	else
		empty = false;

	return empty;
}

// Description: Adds newElement to the "back" of this Queue 
//              (not necessarily the "back" of its data structure) and 
//              returns "true" if successful, otherwise "false".
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::enqueue(const ElementType& newElement) {

	bool isEnqueued;	// True once element is enqueued, false if not

	// Create a "circular" array, in which back and front
	// can loop around as elements are enqueued and dequeued.
	// If queue is not full, then set "back" to next index in
	// array (looping around to index 0 if at the end of the
	// array) and add newElement at the back position
	if (elementCount != CAPACITY) {
		back = (back + 1) % CAPACITY;
		elementQueue[back] = newElement;
		elementCount++;
		isEnqueued = true;
	}
	else
		isEnqueued = false;

	return isEnqueued;
}

// Description: Removes the element at the "front" of this Queue 
//              (not necessarily the "front" of its data structure) and  
//              returns "true" if successful, otherwise "false".
// Precondition: This Queue is not empty.
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::dequeue() {

	bool dequeued;	// True if element dequeued, false if not

	// If array is not empty, dequeue element at "front" by
	// moving front one index position to the right and
	// decrementing elementCount
	if (!isEmpty()) {
		front = (front + 1) % CAPACITY;
		elementCount--;
		dequeued = true;
	}
	else
		dequeued = false;

	return dequeued;
}

// Description: Returns (a copy of) the element located at the "front" of this Queue.
// Precondition: This Queue is not empty.
// Postcondition: This Queue is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType Queue<ElementType>::peek() const throw(EmptyDataCollectionException) {

	// Get element at front of queue
	ElementType peeked;
	peeked = elementQueue[front];

	// Enforce precondition that queue is not empty
	if (isEmpty())
		throw EmptyDataCollectionException("peek() called with empty queue.");

	// Queue is not empty; return front
	return peeked;
}

// Description: Prints contents of queue.
// Precondition: This Queue is not empty.
// Postcondition: This Queue is unchanged.
// Time Efficiency: O(n)
template <class ElementType>
void Queue<ElementType>::printQueue() {

	int printIndex = 0;

	// Starting from "front", while the index of
	// of "front" is less than capacity of the array,
	// print value at that index; once end of array is
	// reached, loop back around to front (index 0) of
	// array and continue printing through array until
	// all elements printed
	for (int i = 0; i < elementCount; i++) {
		if ((front + i) < CAPACITY)
			cout << elementQueue[front + i];
		else {
			cout << elementQueue[printIndex];
			printIndex++;
		}
	}

	if (elementCount == 0)
		cout << endl << "Bank line is empty" << endl;
}

/*
template <class ElementType>
Queue<ElementType>::~Queue() {

}
*/