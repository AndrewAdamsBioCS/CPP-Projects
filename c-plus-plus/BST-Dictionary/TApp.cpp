/*
 * TApp.cpp
 * 
 * Description: Translation Application
 *
 * Author: AL
 * Date: July 2017
 */


#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include "BST.h"
#include "WordPair.h"
#include "ElementAlreadyExistsInBSTException.h"
#include "ElementDoesNotExistInBSTException.h"


void display(WordPair& anElement) {
  cout << anElement.getEnglish() << ":" << anElement.getTranslation() << endl;
} // end of display


int main(int argc, char *argv[]) {

  BST<WordPair>* theTranslator = new BST<WordPair>();
    
  string aLine = "";
  string aWord = "";
  string englishW = "";
  string translationW = "";
  string filename = "dataFile.txt";
  string delimiter = ":";
  size_t pos = 0;
  WordPair translated;
 
  
  ifstream myfile (filename);
  if (myfile.is_open()) {
  	cout << "Reading from a file:" << endl; 
    while ( getline (myfile,aLine) )
    {
       //cout << aLine << '\n';   // For debugging purposes
       pos = aLine.find(delimiter);
       englishW = aLine.substr(0, pos);
       aLine.erase(0, pos + delimiter.length());
       translationW = aLine;
       //cout << "Read: " << englishW << ":" << translationW << endl;  // For debugging purposes
       WordPair aWordPair(englishW, translationW);
       //cout << "Read: " <<  aWordPair.getEnglish() << ":" << aWordPair.getTranslation() << endl;  // For debugging purposes
       try {
  	   		theTranslator->insert(aWordPair);
  	   }
  	   catch (ElementAlreadyExistsInBSTException& anException) {
  	       cout << anException.what( ) << " => " <<  aWordPair.getEnglish() << ":" << aWordPair.getTranslation() << endl;
  	   }
    }
    myfile.close();

    // If user entered "Display" at the command line
    if ( ( argc > 1 ) && ( strcmp(argv[1], "Display") == 0) ) {
        // cout << "Printing the Translator:" << endl; // For debugging purposes
        theTranslator->traverseInOrder(display);
    }
    else if (argc == 1) {
       // while user has not entered CTRL+D
       while ( getline(cin, aWord) ) {   
          //cout << "Read: " << aWord << endl; // For debugging purposes
          WordPair aWordPair(aWord);
          //cout << "The word to translate is: " << aWordPair.getEnglish() << ":" << aWordPair.getTranslation() << endl; // For debugging purposes 
          try {
              translated = theTranslator->retrieve(aWordPair);
              cout << translated.getEnglish() << ":" << translated.getTranslation() << endl;
          }
          catch (ElementDoesNotExistInBSTException& anException) {
              cout << "Translation for '" << aWordPair.getEnglish() << "' not found!" << endl;
          }
       }
    }
  }
  else 
    cout << "Unable to open file"; 

  return 0;
}