/*
* List.cpp
*
* Class Description: List data collection ADT.
* Class Invariant: Data collection with the following characteristics:
*                   - Each element is unique (no duplicates).
*                   - Each element belongs in only one of ten unique arrays
					  corresponding to possible first digits (0 - 9) of identifier number
					- Data structure is expandable in a transparent fashion
*
* Created on: May 24, 2017
* Modified on: June 3, 2017
* Last modified: June 12, 2017
* Author: Andrew Adams
*/

#include <string>
#include "List.h"

using namespace std;

// Default constructor
List::List() {

	// Set total element count to zero, and set capacity of arrays to be created
	totalElementCount = 0;
	capacity = INITIAL_CAPACITY;

	// Set element counts to zero for each inner array of Patients having care cards
	// beginning with the same digit
	for (int i = 0; i < FIRST_DIGITS; i++) {
		elementCountByFirstNum[i] = 0;
	}

	// Set capacity of each inner array of Patients having care cards beginning
	// with the same digit
	for (int i = 0; i < FIRST_DIGITS; i++) {
		capacityByFirstNum[i] = capacity;
	}

	// Fill outer array with pointers to inner arrays of Patient objects;
	// inner arrays will be created when they are first populated by the user,
	// so initially all pointers to them are set to NULL
	for (int i = 0; i < FIRST_DIGITS; i++) {
		elements[i] = NULL;
	}
} // end Default constructor


// Copy constructor
// Description: Creates a deep copy of existing List object.
List::List(const List& listToCopy) {

	// Copy total element count
	totalElementCount = listToCopy.totalElementCount;

	// Copy element counts for each array representing Patients with
	// card numbers beginning with the same digit
	for (int i = 0; i < FIRST_DIGITS; i++) {
		elementCountByFirstNum[i] = listToCopy.elementCountByFirstNum[i];
	}

	// Copy current capacities for each array representing Patients with
	// card numbers beginning with the same digit
	for (int i = 0; i < FIRST_DIGITS; i++) {
		capacityByFirstNum[i] = listToCopy.capacityByFirstNum[i];
	}

	// Copy all List elements into new List
	for (int i = 0; i < FIRST_DIGITS; i++) {

		// Check that inner array exists for Patients with cards beginning
		// with each possible first digit; if no inner array exists, set
		// pointer to NULL for that outer array position.
		if (listToCopy.elements[i]) {

			// Create new inner array for Patients beginning with that digit
			elements[i] = new Patient[capacityByFirstNum[i]];

			// Copy all Patients with same first digit into that array
			for (int j = 0; j < elementCountByFirstNum[i]; j++) {
				elements[i][j] = listToCopy.elements[i][j];
			}
		}
		else
			elements[i] = NULL;
	}
} // end Copy constructor


// Description: Returns the total element count currently stored in List.
int  List::getElementCount() const {

	return totalElementCount;
} // end get ElementCount


// Description: Insert an element.
// Precondition: newElement must not already be in data collection. 
//				 Array must be expanded if at maximum capacity.
// Postcondition: newElement inserted, element counts incremented for
//				  both total elements and elements with same first card digit   
bool List::insert(const Patient& newElement) {

	bool insertUniquePatient = true;	// True if patient is unique and can be inserted
	int sameFirstDigitCount;			// Element count of Patients already in list with
										// same first digit of care card as the Patient in argument
	int sameFirstDigitCapacity;			// Capacity of inner array holding Patients already in list with
										// same first digit of care card as the Patient in argument
	int firstNumber;					// First digit of care card of Patient in argument

	// Get first digit of care card of Patient to be inserted
	firstNumber = getFirstDigit(newElement);
	
	// Get element count and capacity of array holding Patients with same first digit of card
	sameFirstDigitCount = elementCountByFirstNum[firstNumber];
	sameFirstDigitCapacity = capacityByFirstNum[firstNumber];

	// If no Patients have been added yet with same first digit as current Patient,
	// create new array for Patients with that first digit
	if (!elements[firstNumber]){
		elements[firstNumber] = new Patient[capacity];
	}

	// Check if Patient already exists
	for (int i = 0; i < sameFirstDigitCount && insertUniquePatient; i++) {
		if (elements[firstNumber][i] == newElement){
			insertUniquePatient = false;
		}
	}

	// Test if inner array for first digit of care card is full; if so, expand array
	if (sameFirstDigitCount == sameFirstDigitCapacity) {
		expand(firstNumber);
	}

	// If patient is unique, insert patient
	if (insertUniquePatient) {

		int insertIndex = 0;		// Position in list being tested as insertion point
		bool notInserted = true;	// True while sorted position point for Patient has not been found
		
		// While sorted position has not been found, continue stepping through list
		while (notInserted) {
			
			// If insertion index being tested equals the element count, then the end
			// of the list has been reached without encountering a greater care card value,
			// and the Patient object should be inserted at that index
			if (insertIndex != sameFirstDigitCount) {
				
				// If care card at test index is greater than care card of Patient to insert,
				// then shift that value and all values greater than it one index to the right
				if (elements[firstNumber][insertIndex] > newElement) {
					for (int i = sameFirstDigitCount; i > insertIndex; i--) {
						elements[firstNumber][i] = elements[firstNumber][i - 1];
					}
				
					// Insert Patient at test index, increment total element count, 
					// increment element count of inner array, and end test
					elements[firstNumber][insertIndex] = newElement;
					totalElementCount++;
					elementCountByFirstNum[firstNumber]++;
					notInserted = false;
				} // end if
				
				// Test next index
				else
					insertIndex++;
			} // end if

			// Insert patient at index if end of list has been reached,
			// increment total element count, increment inner array count, and end test
			else {
				elements[firstNumber][insertIndex] = newElement;
				elementCountByFirstNum[firstNumber]++;
				totalElementCount++;
				notInserted = false;
			}
		} // end while

	} // end if

	return insertUniquePatient;
} // end insert


// Description: Remove an element. 
// Postcondition: toBeRemoved is removed and elementCount has been decremented.
bool List::remove(const Patient& toBeRemoved) {

	bool removed = false;		// Reflects if remove operation is successful or not
	int firstNumber;			// First digit of care card of Patient in argument
	int firstDigitElementCount;	// Element count of Patients already in list with
								// same first digit of care card as the Patient in argument

	// Get first digit of care card of Patient to be removed
	firstNumber = getFirstDigit(toBeRemoved);

	// Get element count of array holding Patients with same first digit of card
	firstDigitElementCount = elementCountByFirstNum[firstNumber];

	// Search in array for element to be removed
	for (int i = 0; i < firstDigitElementCount && !removed; i++) {
		if (elements[firstNumber][i] == toBeRemoved) {
			
			// For all elements to the right of the element to remove,
			// shift one index to the left
			for (int j = i; j < firstDigitElementCount - 1; j++) {
				elements[firstNumber][j] = elements[firstNumber][j + 1];
			}

			// Decrement element counts, indicate success of removal
			elementCountByFirstNum[firstNumber]--;
			totalElementCount--;
			removed = true;
		} // end if
	}
	
	return removed;
} // end remove


// Description: Remove all elements.
void List::removeAll() {
	// Reset list by returning element count to 0
	totalElementCount = 0;

	for (int i = 0; i < FIRST_DIGITS; i++) {
		elementCountByFirstNum[i] = 0;
	}
} // end removeAll


// Description: Search for target element.
//              Returns a pointer to the element if found,
//              otherwise, returns NULL.
Patient* List::search(const Patient& target) {

	
	Patient* patientFound = NULL;	// Holds address of Patient if found
	int firstNumber;				// First digit of care card of Patient in argument	
	int sameFirstDigitCount;		// Element count of Patients already in list with
									// same first digit of care card as the Patient in argument

	// Get first digit of care card of Patient being searched for
	firstNumber = getFirstDigit(target);

	// Get element count of array holding Patients with same first digit of card
	sameFirstDigitCount = elementCountByFirstNum[firstNumber];

	// Search array for Patient matching the one passed in
	for (int i = 0; i < sameFirstDigitCount && !patientFound; i++) {
		if (elements[firstNumber][i] == target)
			patientFound = &elements[firstNumber][i];
	}

	return patientFound;
} // end search


// Description: Prints all elements stored in List.
void List::printList() {

	// Run through list, printing Patient info for all Patients
	for (int i = 0; i < FIRST_DIGITS; i++) {
		for (int j = 0; j < elementCountByFirstNum[i]; j++) {
			elements[i][j].printPatient();
		}
	}
} // end printList


// Description: Expands inner array of Patients all having care cards beginning with
//				the same first digit when array is full.
// Precondition: Element count of array equals capacity of array.
// Postcondition: New capacity of array is expanded by EXPANSION_FACTOR.
// Time-efficiency: O(1) amortized
void List::expand(int firstNumber) {

	int currentCapacity;	// Current capacitity of array of Patients with care cards beginning
							// with the first digit passed in as argument
	int expandedCapacity;	// Calculated capacity of array when expanded
	
	// Get current capacity of array
	currentCapacity = capacityByFirstNum[firstNumber];

	// Calculate expanded capacity to which array will be resized
	expandedCapacity = currentCapacity * EXPANSION_FACTOR;
	
	// Create new array of Patients with the expanded capacity
	Patient* expandedList;
	expandedList = new Patient[expandedCapacity];

	// Fill new array with values from old array
	for (int i = 0; i < currentCapacity; i++) {
		expandedList[i] = elements[firstNumber][i];
	}

	// Delete the array with the old capacity
	delete[] elements[firstNumber];

	// Set the expanded array as the new inner array for all Patient objects
	// with care cards beginning with that same first digit
	elements[firstNumber] = expandedList;

	// Update capacity
	capacityByFirstNum[firstNumber] = expandedCapacity;

} // end expand


// Description: Determines first digit of Patient care card number.
// Precondition: Patient has valid care card number.
// Postcondition: First digit of care card string is determined and returned
//				  as an integer (0 - 9)
int List::getFirstDigit(const Patient& patient) {

	string careCard = patient.getCareCard();	// Care card number of Patient
	
	// Because care card is a string, the first "digit" will be a char;
	// converted to an int, the numeric representation of a "digit" char
	// may not equal the literal value of the digit, so subtract the
	// the numberic representation of '0' to get the actual value;
	// e.g., in ASCII, numbers start from 48, so '4' = 52,
	// and 52 - '0' = 52 - 48 = 4, which is the actual number we want
	int firstNumber = careCard[0] - '0';

	return firstNumber;
}


// Destructor
List::~List() {

	// Step through outer array, deleting the
	// dynamically allocated inner arrays
	for (int i = 0; i < FIRST_DIGITS; ++i) {
		delete[] elements[i];
	}
}