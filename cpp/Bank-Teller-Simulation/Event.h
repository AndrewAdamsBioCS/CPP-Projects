/*
* Event.h
*
* Class Description: A bank customer event
* Class Invariant: Event type will be "arrival" or "departure".
*				   Transaction length will not be negative.*
* Created on: June 20, 2017
* Author: Andrew Adams
*/

#pragma once
#include <string>

using namespace std;

class Event {

	private:
		string type;	// Type of customer event
		int time;		// Time at which event begins
		int length;		// Transaction length of customer

	public:
		//Default constructor
		Event();

		// Parameterized constructor
		Event(string eventType, int eventTime, int eventLength);

		// Description: Sets event type
		// Precondition: Type is "arrival" or "departure"
		// Time Efficiency: O(1) 
		bool setType(string eventType);

		// Description: Sets the time event starts
		// Precondition: Time is not negative
		// Time Efficiency: O(1) 
		bool setTime(int eventTime);

		// Description: Sets the length of transaction
		// Precondition: Time is not negative
		// Time Efficiency: O(1)
		bool setLength(int eventLength);

		// Description: Returns event type
		// Postcondition: Type is not changed
		// Time Efficiency: O(1) 
		string getType();

		// Description: Returns time event begins
		// Postcondition: Time is not changed
		// Time Efficiency: O(1) 
		int getTime();

		// Description: Returns transaction length
		// Postcondition: Length is not changed
		// Time Efficiency: O(1) 
		int getLength();

		// Description: Overloaded operator to compare
		//				customer events
		// Postcondition: Returns true is "this" event time is
		//				  greater than rhs event time
		// Time Efficiency: O(1)
		bool operator>(const Event &rhs);

		// Description: Overloaded operator to print customer events
		// Postcondition: Event is printed to screen and left unchanged
		// Time Efficiency: O(1)
		friend ostream & operator<<(ostream & os, const Event & e);
}; // end Event.h