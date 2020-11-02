/*
* List.h
*
* Class Description: A value-oriented List data collection ADT.
* Class Invariant: Data collection with the following characteristics:
*                   - Each element is unique (no duplicates).
*                   - It is sorted by ascending sort order of its elements.
*                   - Its data structure is expandable: when full, it expands to accommodate
*                     new insertion. This is done unbeknown to the client code.
*
* Last modified on: June 12, 2017
* Author: AL / Andrew Adams
*/

#pragma once
#include <string>
#include "Patient.h"

using namespace std;

class List {

private:
	static const int INITIAL_CAPACITY = 2;		// Initial capacity for each array of care card numbers
	static const int FIRST_DIGITS = 10;			// Number of possible first digits (0 - 9)
	static const int EXPANSION_FACTOR = 2;		// Factor by which to expand arrays when needed
	int totalElementCount;						// Total number of Patients in the List
	int elementCountByFirstNum[FIRST_DIGITS];	// Array to hold element counts of each of the separate
												// arrays based on first number of care card
	int capacityByFirstNum[FIRST_DIGITS];		// Array to hold capacities of each of the separate
												// arrays based on first number of care card
	Patient *elements[FIRST_DIGITS];			// Two-dimensional array to hold Patients; outer array holds
												// pointers to 10 inner arrays, one for each possible first
												// digit of Patient care cards
	int capacity;								// Capacity of inner arrays
	
	// Private helper methods
	// Description: Expands inner array of Patients all having care cards beginning with
	//				the same first digit when array is full.
	// Precondition: Element count of array equals capacity of array.
	// Postcondition: New capacity of array is expanded by EXPANSION_FACTOR.
	void expand(int firstNumber);

	// Description: Determines first digit of Patient care card number.
	// Precondition: Patient has valid care card number.
	// Postcondition: First digit of care card string is determined and returned
	//				  as an integer (0 - 9)
	int getFirstDigit(const Patient& patient);

public:
	// Default constructor
	List();

	// Copy constructor
	// Description: Creates deep copy of List object
	List(const List& listToCopy);

	// Destructor
	~List();

	// *** Start of Public Interface ***
	// Note: Public Interface must not be modified.

	// Description: Returns the total element count currently stored in List.
	int  getElementCount() const;

	// Description: Insert an element.
	//              When "this" List is full, its data structure is expanded to accommodate 
	//              a new element. This is done unbeknown to the client code.
	//              If the insertion is successful, true is returned otherwise, false is returned.
	// Precondition: newElement must not already be in data collection.  
	// Postcondition: newElement inserted and the appropriate elementCount has been incremented.	
	bool insert(const Patient& newElement);

	// Description: Remove an element. 
	//              If the removal is successful, true is returned otherwise, false is returned.
	// Postcondition: toBeRemoved is removed, the appropriate elementCount has been decremented.	
	bool remove(const Patient& toBeRemoved);

	// Description: Remove all elements.
	void removeAll();

	// Description: Search for target element and returns a pointer to it if found,
	//              otherwise, returns NULL.
	Patient* search(const Patient& target);

	// Description: Prints all n elements stored in List in sort order and does so in O(n).
	void printList();

	// *** End of Public Interface ***

}; // end List