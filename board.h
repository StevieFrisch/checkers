/*
 * board.h
 *
 *  Created on: Mar 12, 2021
 *      Author: wduf0
 */

#ifndef BOARD_H_
#define BOARD_H_

//////

#include "include.h"
#include "piece.h"
#include "LList.h"

//////

typedef struct
{
	int row;
	int col;
	bool hasPiece;
	piece* tilePiece;
} boardTile;

//////

class board {
public:
	board(boardTile**, bool, moveCoords*);
	virtual ~board();

	boardTile** getTiles();
	bool getLastTeam();
	moveCoords* getLastMove();
	void initBoard();
	void uploadBoard(char*); // str
	char* saveBoard();
	void displayBoard();
	void updateBoard(int, int, int , int); // oldRow, oldCol, newRow, newCol
	void displayBoardCoords();
	bool redOnTile(int, int); // pieceRow, pieceCol
	bool blackOnTile(int, int); // pieceRow, pieceCol
	void moveRed();
	void moveBlack();
	bool jumpRed();
	bool jumpBlack();
	LList* listAllRedMoves();
	LList* listAllRedJumps();
	LList* listAllBlackMoves();
	LList* listAllBlackJumps();
	void cpuMove();
	bool cpuJump();
	int isWin(); // 0 = no winner, 1 = red wins, 2 = black wins

private:
	boardTile** tiles;
	bool lastTeam;
	moveCoords* lastMove;
};

//////

#endif /* BOARD_H_ */
