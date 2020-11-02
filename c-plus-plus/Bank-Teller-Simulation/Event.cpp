/*
* Event.cpp
*
* Class Description: A bank customer event
* Class Invariant: Event type will be "arrival" or "departure".
*				   Transaction length will not be negative.*
* Created on: June 20, 2017
* Author: Andrew Adams
*/

#include <string>
#include <iostream>
#include "Event.h"

using namespace std;


// Default constructor
Event::Event() {
	type = "arrival";
	time = 0;
	length = 0;
}


// Parameterized constructor
Event::Event(string eventType, int eventTime, int eventLength) {

	type = eventType;
	time = eventTime;
	length = eventLength;
}


// Description: Sets event type
// Precondition: Type is "arrival" or "departure"
// Time Efficiency: O(1) 
bool Event::setType(string eventType) {

	bool typeIsSet;

	if(eventType == "arrival" || eventType == "departure") {
		type = eventType;
		typeIsSet = true;
	}
	else
		typeIsSet = false;

	return typeIsSet;
}


// Description: Sets the time event starts
// Precondition: Time is not negative
// Time Efficiency: O(1) 
bool Event::setTime(int eventTime) {

	bool timeIsSet;

	if(eventTime > 0) {
		time = eventTime;
		timeIsSet = true;
	}
	else
		timeIsSet = false;

	return timeIsSet;
}
	

// Description: Sets the length of transaction
// Precondition: Time is not negative
// Time Efficiency: O(1)
bool Event::setLength(int eventLength) {

	bool lengthIsSet;

	if(eventLength > 0) {
		length = eventLength;
		lengthIsSet = true;
	}
	else
		lengthIsSet = false;

	return lengthIsSet;
}


// Description: Returns event type
// Postcondition: Type is not changed
// Time Efficiency: O(1) 
string Event::getType() {
	return type;
}


// Description: Returns time event begins
// Postcondition: Time is not changed
// Time Efficiency: O(1) 
int Event::getTime() {
	return time;
}


// Description: Returns transaction length
// Postcondition: Length is not changed
// Time Efficiency: O(1) 
int Event::getLength() {
	return length;
}


// Description: Overloaded operator to compare
//				customer events
// Postcondition: Returns true is "this" event time is
//				  greater than rhs event time
// Time Efficiency: O(1)
bool Event::operator>(const Event &rhs) {

	if (time > rhs.time)
		return true;
	else
		return false;
}


// Description: Overloaded operator to print customer events
// Postcondition: Event is printed to screen and left unchanged
// Time Efficiency: O(1)
ostream & operator<<(ostream & os, const Event & e) {

	os << e.type << ", " << e.time << ", " << e.length << endl;
	
	return os;
}