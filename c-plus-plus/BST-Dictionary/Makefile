all: tApp

tApp: TApp.o BST.h BSTNode.h WordPair.o ElementAlreadyExistsInBSTException.o ElementDoesNotExistInBSTException.o
	g++ -Wall -std=c++11 -o tApp TApp.o WordPair.o ElementAlreadyExistsInBSTException.o ElementDoesNotExistInBSTException.o

TApp.o: TApp.cpp
	g++ -Wall -std=c++11 -c TApp.cpp 
		
WordPair.o: WordPair.h WordPair.cpp
	g++ -Wall -std=c++11 -c WordPair.cpp

ElementDoesNotExistInBSTException.o: ElementDoesNotExistInBSTException.h ElementDoesNotExistInBSTException.cpp
	g++ -Wall -std=c++11 -c ElementDoesNotExistInBSTException.cpp

ElementAlreadyExistsInBSTException.o: ElementAlreadyExistsInBSTException.h ElementAlreadyExistsInBSTException.cpp
	g++ -Wall -std=c++11 -c ElementAlreadyExistsInBSTException.cpp
		
clean:
	rm -f tApp *.o