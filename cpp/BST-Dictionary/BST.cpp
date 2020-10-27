/*
* BST.cpp
*
* Description: Data collection Binary Search Tree ADT class.
*              Link-based implementation.
*
* Class invariant: It is always a BST.
*
* Author: AL and Andrew Adams
* Date of last modification: July 2017
*/

#include "BST.h"
#include "ElementAlreadyExistsInBSTException.h"
#include "ElementDoesNotExistInBSTException.h"


// Default constructor
template <class ElementType>
BST<ElementType>::BST() {

	root = NULL;
	elementCount = 0;
}

// Parameterized constructor
template <class ElementType>
BST<ElementType>::BST(ElementType& element) {

	root = new BSTNode<ElementType>(element);
	elementCount = 1;
}

// Copy constructor
template <class ElementType>
BST<ElementType>::BST(const BST<ElementType>& aBST) {

}

// Destructor
template <class ElementType>
BST<ElementType>::~BST() {

}


// BST operations:

// Time efficiency: O(1)
template <class ElementType>
int BST<ElementType>::getElementCount() const {

	return elementCount;
}

// Time efficiency: O(log2 n)
template <class ElementType>
void BST<ElementType>::insert(const ElementType& newElement)
throw(ElementAlreadyExistsInBSTException) {

	BSTNode<ElementType>* newNode;

	newNode = new BSTNode<ElementType>(newElement);


	if (!root) {
		root = newNode;
		elementCount++;
	}
	else
		insertR(newNode->element, root);
	
	

//	delete newNode;
}

// Time efficiency: O(log2 n)
template <class ElementType>
ElementType& BST<ElementType>::retrieve(const ElementType& targetElement)
const throw(ElementDoesNotExistInBSTException) {

//	ElementType* foundElement;

	if (root->element == targetElement) {
		return root->element;
	}
	else {
		if (root->element < targetElement) {
			return retrieveR(targetElement, root->right);
		}
		else {
			return retrieveR(targetElement, root->left);
		}
	}
}

// Time efficiency: O(n)
template <class ElementType>
void BST<ElementType>::traverseInOrder(void visit(ElementType&)) const {
	
	traverseInOrderR(visit, root->left);
	visit(root->element);
	traverseInOrderR(visit, root->right);
}


// Private methods

template <class ElementType>
bool BST<ElementType>::insertR(const ElementType& element,
	BSTNode<ElementType>* current) throw(ElementAlreadyExistsInBSTException) {

	BST<ElementType>* newSubTree;
	ElementType toInsert;
	bool isInserted = false;

	toInsert = element;
	newSubTree = new BST<ElementType>(toInsert);

	if (current->element == element)
		throw ElementAlreadyExistsInBSTException("Element already exists");

	if (current->element < element) {
		if (current->hasRight()) {
			isInserted = insertR(element, current->right);
		}
		else {
			current->right = newSubTree->root;
			elementCount++;
			isInserted = true;
		}
	}
	else {
		if (current->hasLeft()) {
			isInserted = insertR(element, current->left);
		}
		else {
			current->left = newSubTree->root;
			elementCount++;
			isInserted = true;
		}
	}

	return isInserted;
}

template <class ElementType>
ElementType& BST<ElementType>::retrieveR(const ElementType& targetElement,
	BSTNode<ElementType>* current) const throw(ElementDoesNotExistInBSTException) {


	if (!current)
		throw ElementDoesNotExistInBSTException("Element does not exist");

	if (current->element == targetElement) {
		cout << endl << "found element" << endl;
		return current->element;
	}
	else {
		if (current->element < targetElement) {
			cout << endl << "searching right subtree" << endl;
			return retrieveR(targetElement, current->right);
		}
		else {
			cout << endl << "searching left subtree" << endl;
			return retrieveR(targetElement, current->left);
			cout << endl << "recursed back up from left subtree" << endl;
		}
	}
}

template <class ElementType>
void BST<ElementType>::traverseInOrderR(void visit(ElementType&),
	BSTNode<ElementType>* current) const {

	if (current) {
		if (current->hasLeft())
			traverseInOrderR(visit, current->left);
		
		visit(current->element);

		if(current->hasRight())
			traverseInOrderR(visit, current->right);
	}
}