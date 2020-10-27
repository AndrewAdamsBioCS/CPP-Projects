/*
 * ElementDoesNotExistInBSTException.cpp
 *
 * Class Description: Defines the exception that is thrown when 
 *                    we are searching for an element
 *                    which is not in the BST data collection ADT class.
 *
 * Author: Inspired from our textbook's authors Frank M. Carrano and Tim Henry.
 *         Copyright (c) 2013 __Pearson Education__. All rights reserved.
 */
 

#include "ElementDoesNotExistInBSTException.h"  

ElementDoesNotExistInBSTException::ElementDoesNotExistInBSTException(const string& message): 
logic_error("ElementDoesNotExistInBSTException: " + message)
{
}  // end constructor

// End of implementation file.