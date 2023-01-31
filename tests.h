/*
 * tests.h
 *
 *  Created on: Mar 2, 2021
 *      Author: wduf0
 */

#ifndef TESTS_H_
#define TESTS_H_

//////

#include "include.h"
#include "board.h"


//////

bool runTests();

//////

class tests {
public:
	tests();
	virtual ~tests();

	bool runTests();

private:
	/*
	 * test
	 * TODO: REMOVE THIS COMMENT WHEN DONE
	 * some of these test are duplicates and may already be written in another hw by her or us (hw2 and hw3)
	 * it might be worth it to look and see if we can recycle any tests
	 */
	bool testInitBoard();
	bool testUploadBoard();
	bool testDisplayBoard();
	bool testListAllRedMoves();
	bool testListAllBlackMoves();
	bool testListAllRedJumps(); // use kings
	bool testListAllBlackJumps();
	bool testCpuMove(); // test to see that it makes a move
	bool testCpuJump(); // test to see that it makes a move
	bool testIsWin();
	bool testLogBoard();
};


//////

#endif /* TESTS_H_ */
