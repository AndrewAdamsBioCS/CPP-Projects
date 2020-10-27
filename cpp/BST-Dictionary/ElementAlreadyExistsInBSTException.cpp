/*
 * ElementAlreadyExistsInBSTException.cpp
 *
 * Class Description: Defines the exception that is thrown when 
 *                    we are attempting to insert an element
 *                    which is already in the BST data collection ADT class.
 *
 * Author: Inspired from our textbook's authors Frank M. Carrano and Tim Henry.
 *         Copyright (c) 2013 __Pearson Education__. All rights reserved.
 */
 

#include "ElementAlreadyExistsInBSTException.h"  

ElementAlreadyExistsInBSTException::ElementAlreadyExistsInBSTException(const string& message): 
logic_error("ElementAlreadyExistsInBSTException: " + message)
{
}  // end constructor

// End of implementation file.