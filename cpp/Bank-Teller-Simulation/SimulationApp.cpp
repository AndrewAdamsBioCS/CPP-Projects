/*
* Simulation.cpp
*
* Class Description: A simulation of customers being served at a bank.
*					 The simulation calculates average time spent waiting
*					 in line for all customers.
* Class Invariant: One teller serving one line of bank customers. All initial
*				   inputs are customer arrival events.
* Created on: June 20, 2017
* Author: Andrew Adams
*/

#include <iostream>
#include <iomanip>
#include "Event.h"
#include "Queue.h"
#include "PriorityQueue.h"

using namespace std;


// Declare functions used within main()
void runSimulation(PriorityQueue<Event> eventPriorityQueue);


int main() {

	PriorityQueue<Event> eventPriorityQueue;	// Priority queue for storing arrival events
	Event *arrivalEvent;						// A customer arrival event
	int arrivalTime;							// Time each customer arrives at bank
	int transactionLength;						// Time each customer spends with teller 

	// While there is input, create arrival events based on input and populate priority queue
	// with the arrival events
	while(cin >> arrivalTime >> transactionLength) {
		arrivalEvent = new Event("arrival", arrivalTime, transactionLength);
		eventPriorityQueue.enqueue(*arrivalEvent);
		delete arrivalEvent;
	}

	// Run simulation on priority queue of events
	runSimulation(eventPriorityQueue);

	arrivalEvent = NULL;
	delete arrivalEvent;

	return 0;
}


void runSimulation(PriorityQueue<Event> eventPriorityQueue) {

	Queue<Event> bankLine;			// Queue for storing customers who must wait
	Event *departureEvent;			// A departure event to track when each customer finishes with teller
	Event currentCustomer;			// Customer at front of priority queue
	int departureTime;				// Time each customer is finished with transaction
	int currentTime;				// Current time of event simulation
	int totalCustomers = 0;			// A running total of customers processed
	int totalWaitTime = 0;			// A running total of time customers spent waiting in line
	float avgWait = 0.0;			// The average wait time of all customers
	bool tellerAvailable = true;	// Signifies if teller is available or not

	// Run simulation loop until the priority queue of events is empty
	cout << "Simulation Begins" << endl;
	while (!eventPriorityQueue.isEmpty()) {

		// Get current customer from front of priority queue
		try {
			currentCustomer = eventPriorityQueue.peek();
		}
		catch (EmptyDataCollectionException &anException) {
			cout << "Simulation unsuccessful because " << anException.what() << endl;
		}

		// Set current time equal to time value of front customer event
		currentTime = currentCustomer.getTime();

		// Process event according to whether it is an arrival or departure
		if (currentCustomer.getType() == "arrival") {
			// Process arrival event
			cout << "Processing an arrival event at time:\t" << setw(3) << currentTime << endl;

			// Remove arrival from event priority queue
			eventPriorityQueue.dequeue();

			// If bank line is empty and teller is available, the arriving customer
			// goes straight to the teller; calculate their departure time, add their
			// wait time (which is zero) to the running total of wait times, and create
			// a departure event based on when they will leave teller, then add this
			// departure event to priority queue. If bank line is not empty, add
			// arriving customer to the bank line
			if (bankLine.isEmpty() && tellerAvailable) {
				departureTime = currentTime + currentCustomer.getLength();
				totalWaitTime += 0;
				departureEvent = new Event("departure", departureTime, currentCustomer.getLength());
				eventPriorityQueue.enqueue(*departureEvent);
				delete departureEvent;
				tellerAvailable = false;
			} // end if
			else
				bankLine.enqueue(currentCustomer);
		} // end if
		else {
			// Process departure event
			cout << "Processing a departure event at time:\t" << setw(3) << departureTime << endl;

			// Remove departure from event priority queue, and increment total customer count
			eventPriorityQueue.dequeue();
			totalCustomers++;

			// If there are customers in the bank line, the front customer
			// can now begin their transaction
			if (!bankLine.isEmpty()) {

				// Set current customer to customer at front of line, and dequeue from line
				currentCustomer = bankLine.peek();
				bankLine.dequeue();

				// Calculate their time spent waiting and add it to running total
				totalWaitTime += (currentTime - currentCustomer.getTime());

				// Calculate their departure time, create a departure event, and add it to priority queue
				departureTime = currentTime + currentCustomer.getLength();
				departureEvent = new Event("departure", departureTime, currentCustomer.getLength());
				eventPriorityQueue.enqueue(*departureEvent);
				delete departureEvent;
			} // end if
			else {
				// If there are no customers in line, then teller is available
				tellerAvailable = true;
			}
		}
	} // end while

	cout << "Simulation Ends" << endl;

	// Compute average waiting time of all customers
	avgWait = (float)totalWaitTime / (float)totalCustomers;

	// Print final statistics
	cout << endl << "Final Statistics:" << endl;
	cout << "\tTotal number of people processed: " << totalCustomers << endl;
	cout << "\tAverage amount of time spent waiting: " << avgWait << endl;

	departureEvent = NULL;
	delete departureEvent;
}

