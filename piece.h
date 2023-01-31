/*
 * piece.h
 *
 *  Created on: Mar 12, 2021
 *      Author: wduf0
 */

#ifndef PIECE_H_
#define PIECE_H_

//////

#include "include.h"

//////

class piece {
public:
	piece(bool, bool);
	virtual ~piece();
	bool getTeam();
	void setTeam(bool);
	bool getIsKing();
	void setIsKing(bool);

private:
	bool team; // true = red, false = black
	bool isKing;
};

//////

#endif /* PIECE_H_ */
