/*
 * gameRecorder.h
 *
 *  Created on: Mar 12, 2021
 *      Author: wduf0
 */

#ifndef GAMERECORDER_H_
#define GAMERECORDER_H_

//////

#include "include.h"
#include "board.h"
#include "LList.h"

//////

class gameRecorder {
public:
	gameRecorder(char*, boardTile**);
	virtual ~gameRecorder();

	void logTurn(char*, bool, moveCoords*, LList*, LList*); // filename, team, move, moves, jumps

private:
	boardTile** corner;
	char* logFileName;
};

//////

#endif /* GAMERECORDER_H_ */
