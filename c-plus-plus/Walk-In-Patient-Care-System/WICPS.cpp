/*
* WICPS.cpp
*
* Description: User interface for a walk-in clinic patient system.
*			   Displays several menus that user can navigate to add, remove,
*			   and update Patients in the clinic.
*
* Created on: May 24, 2017
* Author: Andrew Adams
*/

#include <iostream>
#include <limits>
#include "List.h"
#include "Patient.h"

using namespace std;


// Declare functions used within main()
string getValidCard();
void modify(List& patientList, string careCard);
void enterNew(List& patientList);
void remove(List& patientList);
void search(List& patientList);
void printAllPatients(List& patientList);



// Description: Displays a menu presenting user with options of Patient system.
int main() {

	List patientList;		// List object for managing Patients in system
	int userChoice = 0;		// Stores user's choice of menu option
	bool quit = false;		// Set to true when user quits

	// Run menu until user chooses to quit
	while (!quit) {

		// Display menu and prompt for user choice
		cout << endl << "[1] Enter new patient" << endl;
		cout << "[2] Remove a patient" << endl;
		cout << "[3] Search for a patient" << endl;
		cout << "[4] Modify a patient's records" << endl;
		cout << "[5] Print all patient records" << endl;
		cout << "[6] Clear all patient records" << endl;
		cout << "[7] Quit" << endl;
		cout << endl << "Please choose option (type number in brackets and press Enter): ";

		// Clear buffer if user inputs anything other than a number
		if (!(cin >> userChoice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		// Call appropriate methods corresponding to user's menu choice,
		// or display error message if choice was not valid menu option
		switch (userChoice) {
		case 1:
			enterNew(patientList);
			break;
		case 2:
			remove(patientList);
			break;
		case 3:
			search(patientList);
			break;
		case 4:
			modify(patientList, getValidCard());
			break;
		case 5:
			printAllPatients(patientList);
			break;
		case 6:
			patientList.removeAll();
			cout << endl << "All patients removed." << endl;
			break;
		case 7:
			quit = true;
			break;
		default:
			cout << endl << "Invalid input. Please try again" << endl;
		}
	}

	return 0;
} // end main





  // Description: Creates a new Patient using care card number entered by user,
  //				and inserts into List; then prompts user to set values for Patient data fields.
  // Precondition: Care card number entered by user must be valid and must not already exist,
  //				 and List must not be full.
  // Postcondition: Patient objected with unique care card has been created and added to List,
  //				  and Patient data fields have been set by user if user has chosen to do so.
void enterNew(List& patientList) {

	string careCard;	// A valid care card number

	// Prompt user for care card number and test its validity
	careCard = getValidCard();

	// Create new Patient with valid care card entered by user
	Patient newPatient(careCard);

	// Attempt to insert patient. If patient is unique and List is not full, insert Patient
	// and give user the option to set/modify Patient data fields. If insertion fails,
	// indicate whether Patient already exists in List or if List is full
	if (patientList.insert(newPatient)) {
		cout << endl << "Successfully entered patient." << endl;
		modify(patientList, careCard);
	}
	else {
		Patient* testIfExists = patientList.search(newPatient);
		if (testIfExists != NULL)
			cout << endl << "Patient already exists." << endl;
		else
			cout << endl << "System full." << endl;
	}
} // end enterNew


  // Description: Displays a menu with choice of Patient fields to set/modify for Patient with
  //				the specified care card.
  // Precondition: Patient must be in List.
  // Postcondition: Patient data is updated according to user choice.
  //				  Care card number is unchanged.
void modify(List& patientList, string careCard) {

	Patient toSearch(careCard);		// Patient with specified care card
	Patient* toModify;				// Pointer to Patient in List to modify
	int userChoice = 0;				// User's choice from menu
	bool quit = false;				// Set to true when user quits
	string updatedField;			// User defined value for any chosen data field to update

	// Search in List for Patient with specified care card, and get pointer to Patient
	toModify = patientList.search(toSearch);

	// If pointer to Patient is NULL, then Patient was not found in List
	if (toModify == NULL)
		cout << endl << "Patient not found." << endl;

	// If patient was found, print their records and display menu of data fields
	// that can be updated (name, address, phone, email) until user quits
	while (!quit && toModify != NULL) {
		cout << endl << "Patient's records: " << endl;
		toModify->printPatient();
		cout << endl << "Choose field to set, or return to Main Menu: " << endl;
		cout << "[1] Name" << endl;
		cout << "[2] Address" << endl;
		cout << "[3] Phone" << endl;
		cout << "[4] Email" << endl;
		cout << "[5] Return to Main Menu" << endl;
		cout << endl << "Type number in brackets and press Enter: ";

		// Clear input buffer if user inputs anything other than a number,
		// and clear input buffer of "new line" character from menu choice
		if (!(cin >> userChoice))
			cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// Call appropriate methods according to user choice
		switch (userChoice) {
		case 1:
			cout << "Enter new name: ";
			getline(cin, updatedField);
			toModify->setName(updatedField);
			break;
		case 2:
			cout << "Enter new address: ";
			getline(cin, updatedField);
			toModify->setAddress(updatedField);
			break;
		case 3:
			cout << "Enter new phone: ";
			getline(cin, updatedField);
			toModify->setPhone(updatedField);
			break;
		case 4:
			cout << "Enter new email: ";
			getline(cin, updatedField);
			toModify->setEmail(updatedField);
			break;
		case 5:
			quit = true;
			break;
		default:
			cout << "That is not a valid option" << endl;
		}
	} // end while
} // end modify


  // Description: Removes user-specified Patient from List
  // Precondition: Specified care card must be valid and must exist in List
  // Postcondition: Patient with specified care card has been removed from List
void remove(List& patientList) {

	string careCard;	// Care card number of Patient to remove

	// Prompt user for valid card number of Patient to remove
	careCard = getValidCard();

	// Create Patient with care card number of Patient to remove
	Patient toRemove(careCard);

	// Remove patient, or print message if patient not found
	if (patientList.remove(toRemove))
		cout << endl << "Patient removed." << endl;
	else
		cout << endl << "Patient not found." << endl;
} // end remove


  // Description: Searches in List for user-specified Patient and displays Patient's records
  // Precondition: Care card of searched Patient must be valid.
  //				 Patient must exist in list.
  // Postcondition: Patient records printed, remain unmodified
void search(List& patientList) {

	Patient* foundPatient;	// Pointer to specified Patient in List
	Patient toSearch;		// Patient to search for

	// Prompt for valid care card of Patient to search for
	toSearch = getValidCard();

	// Get pointer to specified Patient in List
	foundPatient = patientList.search(toSearch);

	// Print patient's records if found; if patient not found, print error
	if (foundPatient != NULL) {
		cout << endl << "Patient found." << endl;
		foundPatient->printPatient();
	}
	else
		cout << endl << "Patient not found." << endl;
} // end search


  // Description: Prints all Patients in List
  // Precondition: List must not be empty
  // Postcondition: All patient records displayed
void printAllPatients(List& patientList) {

	// Check if List is empty; if not, print List contents
	if (patientList.getElementCount() == 0)
		cout << endl << "No patients in system." << endl;
	else {
		cout << endl;
		patientList.printList();
	}
} // end printAllPatients


  // Description: Prompts user for Care Card number and tests if number is valid.
  //				Returns valid Care Card number, or prompts for new number if invalid.
  // Precondition: User-inputted number must be 10 digits and must not equal '0000000000'
  // Postcondition: Care card value returned as valid
string getValidCard() {

	string careCard;				// User-defined care card number
	bool isValidCareCard = false;	// Set to true when entered card number is valid

	// Ignore characters left over in input buffer so that they are not mistaken
	// for current user input
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Prompt user to enter valid care card number until valid number is entered
	while (!isValidCareCard) {
		cout << endl << "Enter Care Card number (10 digits): ";
		getline(cin, careCard);
		
		// Test validity of entered number; quit if valid, or prompt to try again
		if (careCard.length() == 10 && careCard != "0000000000")
			isValidCareCard = true;
		else
			cout << endl << "Invalid Card Card number; please try again.";
	} // end while

	  // return valid care card number
	return careCard;
} // end getValidCard