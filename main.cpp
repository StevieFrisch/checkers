//============================================================================
// Name        : hw5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "include.h"
#include "tests.h"
#include "production.h"

//////

int main(int argc, char* argv[]) {
	cout << "running main // hw5\n" << endl;

	tests* testsP = new tests();
	if(testsP->runTests())
	{
		cout << "\n\n***ALL TESTS PASSED***\n\n" << endl;
        production* productionP = new production();
        if(productionP->runProduction(argc, argv))
        {
        	cout <<"Production passed." << endl;
        }
        delete(productionP);
	}
	else
	{
		cout <<"Not all tests passed." << endl;
	}
	delete(testsP);

	return 0;
}
