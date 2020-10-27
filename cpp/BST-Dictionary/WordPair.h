/*
 * WordPair.h
 * 
 * Description: Models an English word and its translation in another language.
 * 
 * Author: AL
 * Date of last modification: July 2017
 */

#pragma once

#include <string>

using namespace std;

class WordPair {

private:
	string english;
	string translation;
	
public:
	// Constructors
	WordPair() ;
	WordPair(string english) ;
	WordPair(string english, string translation) ;

	// Getters
	string getEnglish() const ;
	string getTranslation() const ;

	// Setters
	void setEnglish(string english) ;
	void setTranslation(string translation) ;

	// Overloaded Operators
	bool operator==(const WordPair& rhs) const;
	bool operator<(const WordPair& rhs) const;

}; // end of WordPair.h