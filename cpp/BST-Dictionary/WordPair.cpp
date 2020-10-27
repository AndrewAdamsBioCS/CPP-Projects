/*
 * WordPair.cpp
 * 
 * Description: Models an English word and its translation in another language.
 * 
 * Author: AL
 * Date of last modification: July 2017
 */
 
#include "WordPair.h"

// Constructors
WordPair::WordPair() {
	english = "";
	translation = "";
}

WordPair::WordPair(string english) {
	this->english = english;
	this->translation = "";
}

WordPair::WordPair(string english, string translation) {
	this->english = english;
	this->translation = translation;
}

// Getters
string WordPair::getEnglish() const {
	return this->english;
}

string WordPair::getTranslation() const {
	return this->translation;
}

// Setters
void WordPair::setEnglish(string english) {
	this->english = english;
}

void WordPair::setTranslation(string translation) {
	this->translation = translation;
}

// Overloaded Operators
bool WordPair::operator==(const WordPair& rhs) const {

	return (this->english.compare(rhs.getEnglish()) ) == 0;
} // end of operator==

bool WordPair::operator<(const WordPair& rhs) const {

	return (this->english.compare(rhs.getEnglish()) ) < 0;
} // end of operator<