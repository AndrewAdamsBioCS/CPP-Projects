/*
 * ElementAlreadyExistsInBSTException.h
 *
 * Class Description: Defines the exception that is thrown when 
 *                    we are attempting to insert an element
 *                    which is already in the BST data collection ADT class.
 *
 * Author: Inspired from our textbook's authors Frank M. Carrano and Tim Henry.
 *         Copyright (c) 2013 __Pearson Education__. All rights reserved.
 */
 
#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class ElementAlreadyExistsInBSTException : public logic_error
{
public:
   ElementAlreadyExistsInBSTException(const string& message = "");
   
}; // end ElementAlreadyExistsInBSTException 