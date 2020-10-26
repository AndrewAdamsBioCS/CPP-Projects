/*
* Node.h
*
* Class Description: A template node
*
* Created on: June 20, 2017
* Author: Andrew Adams
*/


#pragma once
using namespace std;

template <class ElementType>
class Node {
	
	private:
		Node<ElementType>* next;	// Pointer to next node
		ElementType data;			// Data held in node

	public:
		//Default constructor
		Node();

		// Parameterized constructor
		Node(ElementType newData);

		// Parameterized constructor
		Node(ElementType newData, Node* theNextNode);

		// Description: Returns the element stored in node as data
		// Time Efficiency: O(1) 
		ElementType getElement();

		// Description: Returns pointer to next node
		// Time Efficiency: O(1)
		Node<ElementType>* getNextNode();

		// Description: Sets pointer to next node
		// Time Efficiency: O(1)
		void setNextNode(Node<ElementType>* nextNode);
		
};


// Default constructor
template <class ElementType>
Node<ElementType>::Node() {
	 next = NULL;
}


// Parameterized constructor accepting ElementType as data
template <class ElementType>
Node<ElementType>::Node(ElementType newData) {

	next = NULL;
	data = newData;
}


// Fully parameterized constructor to set data and next node
template <class ElementType>
Node<ElementType>::Node(ElementType newData, Node* theNextNode) {

	data = newData;
	next = theNextNode;
}


// Description: Returns the element stored in node as data
// Time Efficiency: O(1) 
template <class ElementType>
ElementType Node<ElementType>::getElement() {
	return data;
}


// Description: Returns pointer to next node
// Time Efficiency: O(1) 
template <class ElementType>
Node<ElementType>* Node<ElementType>::getNextNode() {
	return next;
}


// Description: Sets pointer to next node
// Time Efficiency: O(1) 
template <class ElementType>
void Node<ElementType>::setNextNode(Node<ElementType>* nextNode) {
	next = nextNode;
}