/*
 * production.h
 *
 *  Created on: Mar 2, 2021
 *      Author: wduf0
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_
#define FILENAMELENGTHALLOWANCE 50

//////

#include "include.h"
#include "board.h"
#include "gameRecorder.h"
#include "LList.h"

//////

bool runProduction(int argc, char* argv[]);

//////

class production {
public:
	production();
	virtual ~production();

	bool runProduction(int argc, char* argv[]);
};

//////

#endif /* PRODUCTION_H_ */
