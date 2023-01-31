/*
 * piece.cpp
 *
 *  Created on: Mar 12, 2021
 *      Author: wduf0
 */

#include "piece.h"

//////

piece :: piece(bool team, bool isKing) {
	// TODO Auto-generated constructor stub
	this->team = team;
	this->isKing = isKing;
}

piece :: ~piece() {
	// TODO Auto-generated destructor stub
}

//////

bool piece :: getTeam()
{
	return (this->team);
}

void piece :: setTeam(bool myTeam)
{
	this->team = myTeam;
}

bool piece :: getIsKing()
{
	return (this->isKing);
}

void piece :: setIsKing(bool myIsKing)
{
	this->isKing = myIsKing;
}
