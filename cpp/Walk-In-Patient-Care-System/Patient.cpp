/*
* Patient.cpp
*
* Class Description: Models a walk-in clinic patient.
* Class Invariant: Each patient has a unique care card number.
*                  This care card number must have 10 digits.
*				   This care card number must not be "0000000000".
*                  This care card number cannot be modified.
*
* Created on: May 21, 2017
* Author: Andrew Adams
*/

#include<string>
#include<iostream>
#include "Patient.h"

using namespace std;


// Default Constructor
// Description: Create a patient with a care card number of "0000000000". 
// Postcondition: All data members set to "To be entered", 
//                except the care card number which is set to "0000000000".       
Patient::Patient() {

	// Initialize variables to default values
	careCard = "0000000000";
	name = "To be entered";
	address = "To be entered";
	phone = "To be entered";
	email = "To be entered";
} // end Default Constructor


  // Parameterized Constructor
  // Description: Create a patient with the given care card number.
  // Postcondition: If aCareCard does not have 10 digits, then care card is set to "0000000000".
  //                All other data members set to "To be entered".
Patient::Patient(string aCareCard) {

	// Test if care card length is valid
	if (aCareCard.length() == 10)
		careCard = aCareCard;
	else
		careCard = "0000000000";

	// Set other variables to default values
	name = "To be entered";
	address = "To be entered";
	phone = "To be entered";
	email = "To be entered";
} // end Parameterized Constructor


  // Getters and setters
  // Description: Returns patient's name.
string Patient::getName() const {
	return name;
} // end getName


  // Description: Returns patient's address.
string Patient::getAddress() const {
	return address;
} // end getAddress


  // Description: Returns patient's phone number.
string Patient::getPhone() const {
	return phone;
} // end getPhone


  // Description: Returns patient's email.
string Patient::getEmail() const {
	return email;
} // end getEmail


  // Description: Returns patient's care card number.
string Patient::getCareCard() const {
	return careCard;
} // end getCareCard


  // Description: Sets the patient's name.
void Patient::setName(const string aName) {
	name = aName;
} // end setName


  // Description: Sets the patient's address.
void Patient::setAddress(const string anAddress) {
	address = anAddress;
} // end setAddress


  // Description: Sets the patient's phone number.
void Patient::setPhone(const string aPhone) {
	phone = aPhone;
} // end setPhone


  // Description: Sets the patient's email.
void Patient::setEmail(const string anEmail) {
	email = anEmail;
} // end setEmail


  // Overloaded Operators
  // Description: Comparison operator. Compares "this" Patient object with "rhs" Patient object.
  //              Returns true if both Patient objects have the same care card number.
bool Patient::operator==(const Patient & rhs) {

	// Compare whether care card of "this" Patient object
	// equals care card of Patient object passed in
	if (this->careCard == rhs.careCard)
		return true;
	else
		return false;
} // end operator==


  // Description: Greater than operator. Compares "this" Patient object with "rhs" Patient object.
  //              Returns true if the care card number of "this" Patient object is > the care card number of "rhs" Patient object.
bool Patient::operator>(const Patient & rhs) {

	// Compare whether care card of "this" Patient object
	// is greater than care card of Patient object passed in
	if (this->careCard > rhs.careCard)
		return true;
	else
		return false;
} // end operator>


  // Description: Prints the content of "this" patient.
void Patient::printPatient() {

	// Print all records pertaining to this Patient object
	cout << careCard << ", ";
	cout << "Patient: " << name << ", ";
	cout << address << ", ";
	cout << phone << ", ";
	cout << email << endl;
} // end printPatient
