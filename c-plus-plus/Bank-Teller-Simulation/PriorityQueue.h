/*
* PriorityQueue.h
*
* Class Description: A priority queue; elements at front have highest priority
*					 and elements at back have lowest priority
* Class Invariant: Highest priority is defined as lowest element value, and
*				   elements are therefore sorted in ascending order from front
*				   to back. Elements are always sorted.
* Created on: June 20, 2017
* Author: Andrew Adams
*/

#pragma once
#include "Node.h"
#include "EmptyDataCollectionException.h"

template <class ElementType>
class PriorityQueue {

	private: 
		Node<ElementType> *head;	// Pointer to the front of the queue
		int elementCount;			// Total number of elements in queue

	public:
		// Default constructor
		PriorityQueue();

		// Copy constructor
		PriorityQueue(const PriorityQueue<ElementType>& pQ);

		// Destructor
		~PriorityQueue();

		// Let's put our constructor(s) and destructor (if any) ***here***.

		/******* Public Interface - START - *******/
        
		// Description: Returns the number of elements in the Priority Queue.
		// (This method eases testing.)
		// Time Efficiency: O(1) 
		int getElementCount() const;   
   
		// Description: Returns "true" is this Priority Queue is empty, otherwise "false".
		// Time Efficiency: O(1)
		bool isEmpty() const;
 
		// Description: Inserts newElement in sort order.
		//              It returns "true" if successful, otherwise "false".
		// Precondition: This Priority Queue is sorted.   
		// Postcondition: Once newElement is inserted, this Priority Queue remains sorted.    
		// Time Efficiency: O(n)        
		bool enqueue(const ElementType& newElement);
      
		// Description: Removes the element with the "highest" priority.
		//              It returns "true" if successful, otherwise "false".
		// Precondition: This Priority Queue is not empty.
		// Time Efficiency: O(1) 
		bool dequeue();
    
		// Description: Returns (a copy of) the element with the "highest" priority.
		// Precondition: This Priority Queue is not empty.
		// Postcondition: This Priority Queue is unchanged.
		// Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
		// Time Efficiency: O(1) 
		ElementType peek() const throw(EmptyDataCollectionException);

		// Description: Prints the contents of the priority queue
		// Precondition: This Priority Queue is not empty.
		// Postcondition: This Priority Queue is unchanged.
		// Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
		// Time Efficiency: O(n) 
		void printPriorityQueue();
   
		/******* Public Interface - END - *******/

		// Let's feel free to add other private helper methods to our Priority Queue class.   

}; // end PriorityQueue


using namespace std;


// Default constructor
template <class ElementType>
PriorityQueue<ElementType>::PriorityQueue() {
	head = NULL;
	elementCount = 0;	
}

// Copy constructor to create a deep copy
template <class ElementType>
PriorityQueue<ElementType>::PriorityQueue(const PriorityQueue<ElementType>& pQ) {
	
	// Copy element count
	elementCount = pQ.elementCount;
	
	Node<ElementType>* newCopy;
	Node<ElementType>* prevCopy;
	
	// If linked list to copy is not empty, step through linked list creating
	// new queue that is a copy
	if (pQ.head) {	
		prevCopy = pQ.head;
		newCopy = new Node<ElementType>(prevCopy->getElement(), prevCopy->getNextNode());
		head = newCopy;

		while (newCopy->getNextNode() != NULL) {

			prevCopy = newCopy;
			newCopy = new Node<ElementType>(prevCopy->getNextNode()->getElement(),
				prevCopy->getNextNode()->getNextNode());
			prevCopy->setNextNode(newCopy);
		}
	}

	newCopy = NULL;
	prevCopy = NULL;
	delete newCopy;
	delete prevCopy;
}


// Description: Returns the number of elements in the Priority Queue.
// (This method eases testing.)
// Time Efficiency: O(1) 
template <class ElementType>
int PriorityQueue<ElementType>::getElementCount() const {
	return elementCount;
}


// Description: Returns "true" is this Priority Queue is empty, otherwise "false".
// Time Efficiency: O(1)
template <class ElementType>
bool PriorityQueue<ElementType>::isEmpty() const {
	
	bool isEmpty;

	if (elementCount == 0)
		isEmpty = true;
	else
		isEmpty = false;
	
	return isEmpty;
}


// Description: Inserts newElement in sort order.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is sorted.   
// Postcondition: Once newElement is inserted, this Priority Queue remains sorted.    
// Time Efficiency: O(n)        
template <class ElementType>
bool PriorityQueue<ElementType>::enqueue(const ElementType& newElement) {

	bool isInserted = false;			// False until element is inserted in sort order
	Node<ElementType>* elementToAdd;	// Pointer to a Node which will hold element to insert

	// Create new node containing the element passed in
	elementToAdd = new Node<ElementType>(newElement);

	Node<ElementType>* currentNode;		// Pointer to the current Node being compared
										// to the Node to be inserted
	Node<ElementType>* previousNode;	// Pointer to the Node prior to the current Node
	
	// To begin stepping through queue, current Node is the head and previous node is NULL
	currentNode = head;
	previousNode = NULL;

	// If the head is NULL, then queue is empty; insert new element at front of queue
	if (!head) {
		head = elementToAdd;
		isInserted = true;
		elementCount++;
	} // end if 
	else {
		// Until element is inserted in sort order, and while current Node is not NULL,
		// test if current Node is greater than new element; if greater, insert new element
		// before current Node, otherwise continue stepping through queue
		while (!isInserted && currentNode) {
			if (currentNode->getElement() > newElement) {
				// If current Node is first in the queue, insert new element before it
				// by setting head equal to new element and linking current Node as the
				// next Node after new element 
				if (currentNode == head) {
					head = elementToAdd;
					elementToAdd->setNextNode(currentNode);
					isInserted = true;
					elementCount++;
				} // end if
				else {
					// Insert new element in sorted position in middle of queue
					previousNode->setNextNode(elementToAdd);
					elementToAdd->setNextNode(currentNode);
					isInserted = true;
					elementCount++;
				}
			} // end if 
			else {
				// If current Node is not greater than new element,
				// continue stepping through queue
				previousNode = currentNode;
				currentNode = currentNode->getNextNode();
			}
		} // end while
	}

	// If entire queue was stepped through without new element being inserted,
	// then insert new element at end of queue
	if(!isInserted) {
		previousNode->setNextNode(elementToAdd);
		isInserted = true;
		elementCount++;
	}

	// Delete Nodes created for traversing linked list
	currentNode = NULL;
	previousNode = NULL;	
	delete currentNode;
	delete previousNode;

	return isInserted;
}


// Description: Removes the element with the "highest" priority.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is not empty.
// Time Efficiency: O(1) 
template <class ElementType>
bool PriorityQueue<ElementType>::dequeue() {

	Node<ElementType>* toDequeue;
	bool isDequeued;
	
	// If queue has elements (i.e., head is not NULL), then dequeue
	// front element by setting head equal to the Node after the front Node
	if (head) {
		toDequeue = head;
		head = toDequeue->getNextNode();
		elementCount--;
		isDequeued = true;
	}
	else {
		toDequeue = NULL;
		isDequeued = false;
	}

	delete toDequeue;

	return isDequeued;
}


// Description: Returns (a copy of) the element with the "highest" priority.
// Precondition: This Priority Queue is not empty.
// Postcondition: This Priority Queue is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(1) 
template <class ElementType>
ElementType PriorityQueue<ElementType>::peek() const throw(EmptyDataCollectionException) {

	ElementType peeked;		// Variable to hold element at front of queue

	// Enforce precondition that queue is not empty
	if (isEmpty())
		throw EmptyDataCollectionException("peek() called with empty queue.");
	else
		peeked = head->getElement();

	// Queue is not empty; return front
	return peeked;
}


// Description: Prints elements of priority queue from back to front
// Precondition: This Priority Queue is not empty.
// Postcondition: This Priority Queue is unchanged.
// Time Efficiency: O(n) 
template <class ElementType>
void PriorityQueue<ElementType>::printPriorityQueue() {

	Node<ElementType>* currentNode;	// Current node being printed
	
	// Begin with current node at front/head of queue
	currentNode = head;

	// If head is not NULL (queue not empty) then step through queue,
	// printing element data
	if (head) {
		while (currentNode) {
			cout << currentNode->getElement();
			currentNode = currentNode->getNextNode();
		}
	}
	else
		cout << endl << "Priority queue is empty" << endl;
}


// Destructor
template <class ElementType>
PriorityQueue<ElementType>::~PriorityQueue() {

	// Create pointers for stepping through linked list
	Node<ElementType>* toDelete;
	Node<ElementType>* prev;

	toDelete = head;

	// Starting from head, traverse list, deleting each node
	while (toDelete) {
		prev = toDelete;
		toDelete = toDelete->getNextNode();
		delete prev;
	}

	head = NULL;
	prev = NULL;
	delete head;
	delete prev;
}
