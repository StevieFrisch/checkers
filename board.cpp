/*
 * board.cpp
 *
 *  Created on: Mar 12, 2021
 *      Author: wduf0
 */

#include "board.h"

//////

board :: board(boardTile** tiles, bool lastTeam, moveCoords* lastMove) {
	// TODO Auto-generated constructor stub
	this->tiles = tiles;
	this->lastTeam = lastTeam;
	this->lastMove = lastMove;
}

board :: ~board() {
	// TODO Auto-generated destructor stub
}

//////

boardTile** board :: getTiles()
{
	return this->tiles;
}

bool board :: getLastTeam()
{
	return this->lastTeam;
}

moveCoords* board :: getLastMove()
{
	return this->lastMove;
}

void board :: initBoard()
{ // sets up the board
//	printf(">> starting initBoard()\n");

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{

			boardTile** currentTile = ((this->tiles) + (8 * row) + col); // + col
			boardTile* thisTile = (boardTile*) malloc(sizeof(boardTile));
			piece* thisPiece = (piece*) malloc(sizeof(piece));
			if(((row == 0) && ((col % 2) == 1)) ||
					((row == 1) && ((col % 2) == 0)) ||
					((row == 2) && ((col % 2) == 1)))
			{ // black piece
				thisPiece->setTeam(false);
				thisPiece->setIsKing(false);
				thisTile->hasPiece = true;
			}
			else if(((row == 5) && ((col % 2) == 0)) ||
					((row == 6) && ((col % 2) == 1)) ||
					((row == 7) && ((col % 2) == 0)))
			{ // red piece
				thisPiece->setTeam(true);
				thisPiece->setIsKing(false);
				thisTile->hasPiece = true;
			}
			else
			{
				thisTile->hasPiece = false;
			}
			thisTile->row = row;
			thisTile->col = col;
			thisTile->tilePiece = thisPiece;
			*currentTile = thisTile;
		}
	}

//	printf("<< ending initBoard()\n");
}

void board :: uploadBoard(char* filename)
{ // sets up uploaded board configuration
//	printf(">> starting uploadBoard()\n");

	FILE* fp;
	fp = fopen(filename, "r");

	char str[33];
	for(int i = 0; i < 33; i++)
	{ // transfers the file to a string
		fscanf(fp, "%c", &(str[i]));
	}
	fclose(fp);


	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{

			if((row % 2) != (col % 2))
			{ // if piece is legal
				char thisChar = (str[((8 * row) + col) / 2]);

				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				boardTile* thisTile = (boardTile*) malloc(sizeof(boardTile));
				piece* thisPiece = (piece*) malloc(sizeof(piece));

				if(thisChar == 'p')
				{
					thisPiece->setTeam(true);
					thisPiece->setIsKing(false);
					thisTile->hasPiece = true;
				}
				else if(thisChar == 'k')
				{
					thisPiece->setTeam(true);
					thisPiece->setIsKing(true);
					thisTile->hasPiece = true;
				}
				else if(thisChar == 'P')
				{
					thisPiece->setTeam(false);
					thisPiece->setIsKing(false);
					thisTile->hasPiece = true;
				}
				else if(thisChar == 'K')
				{
					thisPiece->setTeam(false);
					thisPiece->setIsKing(true);
					thisTile->hasPiece = true;
				}
				else if(thisChar == '0')
				{
					thisTile->hasPiece = false;
				}
				thisTile->row = row;
				thisTile->col = col;
				thisTile->tilePiece = thisPiece;
				*currentTile = thisTile;
			}
		}
	}

//	printf("<< ending uploadBoard()\n");
}

char* board :: saveBoard()
{
	char* R = (char*) malloc(32 * sizeof(char));
	printf(">> starting saveBoard()\n");

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			int index = ((8 * row) + col);
			boardTile** currentTile = (this->tiles + index);
			char* currentChar = ((R + (index / 2)));
			if((row % 2) != (col % 2))
			{ // if legal tile
				if((*currentTile)->hasPiece)
				{ // if tile has piece
					if((*currentTile)->tilePiece->getTeam())
					{ // if on red team
						if((*currentTile)->tilePiece->getIsKing())
						{ // if red king
							*currentChar = 'R';
						}
						else
						{ // if red pawn
						*currentChar = 'r';
						}
					}
					else if((*currentTile)->tilePiece->getIsKing())
					{ // if black king
						*currentChar = 'B';
					}
					else
					{ // if black pawn
					*currentChar = 'b';
					}
				}
				else
				{ // if no piece
					*currentChar = '0';
				}
			}
		}
	}

	printf("<< ending saveBoard()\n");
	return R;
}

void board :: displayBoard()
{ // prints the board
//	printf(">> starting displayBoard()\n");

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = (this->tiles + (8 * row) + col);
			if((*currentTile)->hasPiece)
			{
				if((*currentTile)->tilePiece->getTeam())
				{
					if((*currentTile)->tilePiece->getIsKing())
					{
						printf("| R ");
					}
					else
					{
					printf("| r ");
					}
				}
				else if((*currentTile)->tilePiece->getIsKing())
				{
					printf("| B ");
				}
				else
				{
				printf("| b ");
				}
			}
			else if((row % 2) == (col % 2))
			{ // shades in the tiles that cannot be moved to
				printf("|///");
			}
			else
			{
				printf("|   ");
			}
			if(col == 7)
			{
				printf("| %d\n", row);
			}
		}
	}
	printf("  0   1   2   3   4   5   6   7\n");

//	printf("<< ending displayBoard()\n");
}

void board :: updateBoard(int oldRow, int oldCol, int newRow, int newCol)
{ // moves a piece from old coordinates to new coordinates (ASSUMES THAT COORIDNATES ARE VALID)
//	printf(">> starting updateBoard()\n");

	bool isJump = false;
	if(abs(newRow - oldRow) == 2)
	{
	isJump = true;
	}

	piece* movingPiece = (piece*) malloc(sizeof(piece));
	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			if((row == oldRow) && (col == oldCol))
			{
				movingPiece = (*currentTile)->tilePiece;
				(*currentTile)->hasPiece = false;
			}
		}
	}
	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			if((row == newRow) && (col == newCol))
			{
				if((newRow == 0) && (movingPiece->getTeam()))
				{ // if red piece gets to top row
					movingPiece->setIsKing(true);
				}
				else if((newRow == 7) && !(movingPiece->getTeam()))
				{ // if black piece gets to the bottom row
					movingPiece->setIsKing(true);
				}
				(*currentTile)->tilePiece = movingPiece;
				(*currentTile)->hasPiece = true;
			}
		}
	}
	if(isJump)
	{
		if((newRow < oldRow) && (newCol > oldCol))
		{ // ne
			for(int row = 0; row < 8; row++)
			{
				for(int col = 0; col < 8; col++)
				{
					boardTile** currentTile = ((this->tiles) + (8 * row) + col);
					if((row == (oldRow - 1)) && (col == (oldCol + 1)))
					{
						(*currentTile)->hasPiece = false;
					}
				}
			}
		}
		if((newRow < oldRow) && (newCol < oldCol))
		{ // nw
			for(int row = 0; row < 8; row++)
			{
				for(int col = 0; col < 8; col++)
				{
					boardTile** currentTile = ((this->tiles) + (8 * row) + col);
					if((row == (oldRow - 1)) && (col == (oldCol - 1)))
					{
						(*currentTile)->hasPiece = false;
					}
				}
			}
		}
		if((newRow > oldRow) && (newCol < oldCol))
		{ // sw
			for(int row = 0; row < 8; row++)
			{
				for(int col = 0; col < 8; col++)
				{
					boardTile** currentTile = ((this->tiles) + (8 * row) + col);
					if((row == (oldRow + 1)) && (col == (oldCol - 1)))
					{
						(*currentTile)->hasPiece = false;
					}
				}
			}
		}
		if((newRow > oldRow) && (newCol > oldCol))
		{ // se
			for(int row = 0; row < 8; row++)
			{
				for(int col = 0; col < 8; col++)
				{
					boardTile** currentTile = ((this->tiles) + (8 * row) + col);
					if((row == (oldRow + 1)) && (col == (oldCol + 1)))
					{
						(*currentTile)->hasPiece = false;
					}
				}
			}
		}
	}

//	printf("<< ending updateBoard()\n");
}

void board :: displayBoardCoords()
{
//	printf(">> starting displayBoardCoords()\n");

	for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				printf("|%d %d", row, col);
		}
			printf("|\n");
		}

//	printf("<< ending displayBoardCoords()\n");
}

bool board :: redOnTile(int pieceRow, int pieceCol)
{
	bool R = false;
//	printf(">> starting redOnTile()\n");

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			if((row == pieceRow) && (col == pieceCol))
			{
				if((*currentTile)->hasPiece)
				{ // if this tile has a piece
					if((*currentTile)->tilePiece->getTeam())
					{ // if the piece is red
						R = true;
					}
				}
			}
		}
	}

//	printf("<< ending redOnTile()\n");
	return R;
}

bool board :: blackOnTile(int pieceRow, int pieceCol)
{
	bool R = false;
//	printf(">> starting blackOnTile()\n");

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			if((row == pieceRow) && (col == pieceCol))
			{
				if((*currentTile)->hasPiece)
				{ // if this tile has a piece
					if(!((*currentTile)->tilePiece->getTeam()))
					{ // if the piece is black
						R = true;
					}
				}
			}
		}
	}

//	printf("<< ending blackOnTile()\n");
	return R;
}

void board :: moveRed()
{
//	printf(">> starting moveRed()\n");

	printf("red piece row? (please enter an integer 0-7).\n"); fflush(stdout);
	int redRow = -6;
	scanf("%d", &redRow);
	printf("red piece column? (please enter an integer 0-7).\n"); fflush(stdout);
	int redCol = -6;
	scanf("%d", &redCol);

	bool pass1 = redOnTile(redRow, redCol);  // if there is a red piece on the given tile
	if(!pass1)
	{
		printf("no red piece on (%d, %d). please enter valid coordinates.\n", redRow, redCol);
		moveRed();
	}
	else
	{
		bool pass2 = false; // if there are any legal moves for this piece

		boardTile* pieceTile = (boardTile*) malloc(sizeof(boardTile));
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if((row == redRow) && (col == redCol))
				{
					pieceTile = *currentTile;
				}
			}
		}

		LList* redMovesLL = new LList();
		moveCoords* moveNE = (moveCoords*) malloc(sizeof(moveCoords));
		moveNE->oldRow = redRow;
		moveNE->oldCol = redCol;
		moveNE->newRow = (redRow - 1);
		moveNE->newCol = (redCol + 1);
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if((row == moveNE->newRow) && (col == moveNE->newCol))
				{ // if on tile NE of piece
					if((redRow > 0) && (redCol < 7))
					{ // if position is legal
						if((*currentTile)->hasPiece == false)
						{ // if there is no piece on the tile
							redMovesLL->savePayload(moveNE);
							pass2 = true;
						}
					}
				}
			}
		}
		moveCoords* moveNW = (moveCoords*) malloc(sizeof(moveCoords));
		moveNW->oldRow = redRow;
		moveNW->oldCol = redCol;
		moveNW->newRow = (redRow - 1);
		moveNW->newCol = (redCol - 1);
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if((row == moveNW->newRow) && (col == moveNW->newCol))
				{ // if on tile NW of piece
					if((redRow > 0) && (redCol > 0))
					{ // if position is legal
						if((*currentTile)->hasPiece == false)
						{ // if there is no piece on the tile
							redMovesLL->savePayload(moveNW);
							pass2 = true;
						}
					}
				}
			}
		}
		moveCoords* moveSW = (moveCoords*) malloc(sizeof(moveCoords));
		moveSW->oldRow = redRow;
		moveSW->oldCol = redCol;
		moveSW->newRow = (redRow + 1);
		moveSW->newCol = (redCol - 1);
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if(pieceTile->tilePiece->getIsKing())
				{ // if the piece is a king
					if((row == moveSW->newRow) && (col == moveSW->newCol))
					{ // if on tile SW of piece
						if((redRow < 7) && (redCol > 0))
						{ // if position is legal
							if((*currentTile)->hasPiece == false)
							{ // if there is no piece on the tile
								redMovesLL->savePayload(moveSW);
								pass2 = true;
							}
						}
					}
				}
			}
		}
		moveCoords* moveSE = (moveCoords*) malloc(sizeof(moveCoords));
		moveSE->oldRow = redRow;
		moveSE->oldCol = redCol;
		moveSE->newRow = (redRow + 1);
		moveSE->newCol = (redCol + 1);
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if(pieceTile->tilePiece->getIsKing())
				{ // if the piece is a king
					if((row == moveSE->newRow) && (col == moveSE->newCol))
					{ // if on tile SE of piece
						if((redRow < 7) && (redCol < 7))
						{ // if position is legal
							if((*currentTile)->hasPiece == false)
							{ // if there is no piece on the tile
								redMovesLL->savePayload(moveSE);
								pass2 = true;
							}
						}
					}
				}
			}
		}
		if(!pass2)
		{
			printf("no legal moves for the red piece on (%d, %d).\n", redRow, redCol);
			moveRed();
		}
		else
		{
			int L = redMovesLL->length();
			moveCoords* redMovesArr = (moveCoords*) malloc(L * sizeof(moveCoords));
			redMovesLL->extractToArray(redMovesArr);
			bool valid = false;
			while(!valid)
			{
				for(int i = 0; i < L; i++)
				{
					printf("option %d) move red piece at (%d, %d) to (%d, %d)\n", (i + 1), redMovesArr[i].oldRow, redMovesArr[i].oldCol, redMovesArr[i].newRow, redMovesArr[i].newCol);
				}
				printf("please enter the option number you would like.\n"); fflush(stdout);
				int choice = -6;
				scanf("%d", &choice);
				if((0 < choice) && (choice < (L + 1)))
				{
					this->lastTeam = true;
					moveCoords* lastMoveRed = (moveCoords*) malloc(sizeof(moveCoords));
					*lastMoveRed = redMovesArr[choice - 1];
					this->lastMove = lastMoveRed;
					updateBoard(redMovesArr[choice - 1].oldRow, redMovesArr[choice - 1].oldCol, redMovesArr[choice - 1].newRow, redMovesArr[choice - 1].newCol);
					valid = true;
				}
				else
				{
					printf("invalid answer number.\n");
				}
			}
		} // pass2
	} // pass1

//	printf("<< ending moveRed()\n");
}

void board :: moveBlack()
{
//	printf(">> starting moveBlack()\n");

	printf("black piece row? (please enter an integer 0-7).\n"); fflush(stdout);
	int blackRow = -6;
	scanf("%d", &blackRow);
	printf("black piece column? (please enter an integer 0-7).\n"); fflush(stdout);
	int blackCol = -6;
	scanf("%d", &blackCol);

	bool pass1 = blackOnTile(blackRow, blackCol);  // if there is a black piece on the given tile
	if(!pass1)
	{
		printf("no black piece on (%d, %d). please enter valid coordinates.\n", blackRow, blackCol);
		moveBlack();
	}
	else
	{
		bool pass2 = false; // if there are any legal moves for this piece

		boardTile* pieceTile = (boardTile*) malloc(sizeof(boardTile));
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if((row == blackRow) && (col == blackCol))
				{
					pieceTile = *currentTile;
				}
			}
		}

		LList* blackMovesLL = new LList();
		moveCoords* moveNE = (moveCoords*) malloc(sizeof(moveCoords));
		moveNE->oldRow = blackRow;
		moveNE->oldCol = blackCol;
		moveNE->newRow = (blackRow - 1);
		moveNE->newCol = (blackCol + 1);
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if(pieceTile->tilePiece->getIsKing())
				{ // if the piece is a king
					if((row == moveNE->newRow) && (col == moveNE->newCol))
					{ // if on tile NE of piece
						if((blackRow > 0) && (blackCol < 7))
						{ // if position is legal
							if((*currentTile)->hasPiece == false)
							{ // if there is no piece on the tile
								blackMovesLL->savePayload(moveNE);
								pass2 = true;
							}
						}
					}
				}
			}
		}
		moveCoords* moveNW = (moveCoords*) malloc(sizeof(moveCoords));
		moveNW->oldRow = blackRow;
		moveNW->oldCol = blackCol;
		moveNW->newRow = (blackRow - 1);
		moveNW->newCol = (blackCol - 1);
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if(pieceTile->tilePiece->getIsKing())
				{ // if the piece is a king
					if((row == moveNW->newRow) && (col == moveNW->newCol))
					{ // if on tile NW of piece
						if((blackRow > 0) && (blackCol > 0))
						{ // if position is legal
							if((*currentTile)->hasPiece == false)
							{ // if there is no piece on the tile
								blackMovesLL->savePayload(moveNW);
								pass2 = true;
							}
						}
					}
				}
			}
		}
		moveCoords* moveSW = (moveCoords*) malloc(sizeof(moveCoords));
		moveSW->oldRow = blackRow;
		moveSW->oldCol = blackCol;
		moveSW->newRow = (blackRow + 1);
		moveSW->newCol = (blackCol - 1);
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if((row == moveSW->newRow) && (col == moveSW->newCol))
				{ // if on tile SW of piece
					if((blackRow < 7) && (blackCol > 0))
					{ // if position is legal
						if((*currentTile)->hasPiece == false)
						{ // if there is no piece on the tile
							blackMovesLL->savePayload(moveSW);
							pass2 = true;
						}
					}
				}
			}
		}
		moveCoords* moveSE = (moveCoords*) malloc(sizeof(moveCoords));
		moveSE->oldRow = blackRow;
		moveSE->oldCol = blackCol;
		moveSE->newRow = (blackRow + 1);
		moveSE->newCol = (blackCol + 1);
		for(int row = 0; row < 8; row++)
		{
			for(int col = 0; col < 8; col++)
			{
				boardTile** currentTile = ((this->tiles) + (8 * row) + col);
				if((row == moveSE->newRow) && (col == moveSE->newCol))
				{ // if on tile SE of piece
					if((blackRow < 7) && (blackCol < 7))
					{ // if position is legal
						if((*currentTile)->hasPiece == false)
						{ // if there is no piece on the tile
							blackMovesLL->savePayload(moveSE);
							pass2 = true;
						}
					}
				}
			}
		}
		if(!pass2)
		{
			printf("no legal moves for the black piece on (%d, %d).\n", blackRow, blackCol);
			moveBlack();
		}
		else
		{
			int L = blackMovesLL->length();
			moveCoords* blackMovesArr = (moveCoords*) malloc(L * sizeof(moveCoords));
			blackMovesLL->extractToArray(blackMovesArr);
			bool valid = false;
			while(!valid)
			{
				for(int i = 0; i < L; i++)
				{
					printf("option %d) move black piece at (%d, %d) to (%d, %d)\n", (i + 1), blackMovesArr[i].oldRow, blackMovesArr[i].oldCol, blackMovesArr[i].newRow, blackMovesArr[i].newCol);
				}
				printf("please enter the option number you would like.\n"); fflush(stdout);
				int choice = -6;
				scanf("%d", &choice);
				if((0 < choice) && (choice < (L + 1)))
				{
					this->lastTeam = false;
					moveCoords* lastMoveBlack = (moveCoords*) malloc(sizeof(moveCoords));
					*lastMoveBlack = blackMovesArr[choice - 1];
					this->lastMove = lastMoveBlack;
					updateBoard(blackMovesArr[choice - 1].oldRow, blackMovesArr[choice - 1].oldCol, blackMovesArr[choice - 1].newRow, blackMovesArr[choice - 1].newCol);
					valid = true;
				}
				else
				{
					printf("invalid answer number.\n");
				}
			}
		} // pass2
	} // pass1

//	printf("<< ending moveBlack()\n");
}

bool board :: jumpRed()
{
	bool R = false;
//	printf(">> starting jumpRed()\n");

	bool pass1 = false; // if there are any legal jumps

	LList* redJumpsLL = new LList();

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			boardTile* thisTile = *currentTile; // tile being tested
			boardTile* jumpedNETile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedNWTile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedSWTile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedSETile = (boardTile*) malloc(sizeof(boardTile*));
			if(thisTile->hasPiece)
			{ // if this tile has a piece on it
				if(thisTile->tilePiece->getTeam())
				{ // if the piece is red
					for(int row = 0; row < 8; row++)
					{ // get the 4 tiles being jumped over
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile1 = ((this->tiles) + (8 * row) + col);
							if((row == (thisTile->row - 1)) && (col == (thisTile->col + 1)))
							{
								jumpedNETile = (*currentTile1);
							}
							if((row == (thisTile->row - 1)) && (col == (thisTile->col - 1)))
							{
								jumpedNWTile = (*currentTile1);
							}
							if((row == (thisTile->row + 1)) && (col == (thisTile->col - 1)))
							{
								jumpedSWTile = (*currentTile1);
							}
							if((row == (thisTile->row + 1)) && (col == (thisTile->col + 1)))
							{
								jumpedSETile = (*currentTile1);
							}
						}
					}
					for(int row = 0; row < 8; row++)
					{ // for every tile on the board, check if it a red piece with legal jumps
						for(int col = 0; col < 8; col++)
						{
							if((row == thisTile->row) && (col == thisTile->col))
							{ // if on tile being tested
								moveCoords* jumpNE = (moveCoords*) malloc(sizeof(moveCoords));
								jumpNE->oldRow = thisTile->row;
								jumpNE->oldCol = thisTile->col;
								jumpNE->newRow = (thisTile->row - 2);
								jumpNE->newCol = (thisTile->col + 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if((row == jumpNE->newRow) && (col == jumpNE->newCol))
										{ // if on tile NE of piece
											if(jumpedNETile->hasPiece)
											{ // if the tile being jumped has a piece on it
												if(!(jumpedNETile->tilePiece->getTeam()))
												{ // if the piece is black
													if((thisTile->row > 1) && (thisTile->col < 6))
													{ // if position is legal
														if((*currentTile)->hasPiece == false)
														{ // if there is no piece on the tile
															redJumpsLL->savePayload(jumpNE);
															pass1 = true;
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpNW = (moveCoords*) malloc(sizeof(moveCoords));
								jumpNW->oldRow = thisTile->row;
								jumpNW->oldCol = thisTile->col;
								jumpNW->newRow = (thisTile->row - 2);
								jumpNW->newCol = (thisTile->col - 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if((row == jumpNW->newRow) && (col == jumpNW->newCol))
										{ // if on tile NW of piece
											if(jumpedNWTile->hasPiece)
											{ // if the tile being jumped has a piece on it
												if(!(jumpedNWTile->tilePiece->getTeam()))
												{ // if the piece is black
													if((thisTile->row > 1) && (thisTile->col > 1))
													{ // if position is legal
														if((*currentTile)->hasPiece == false)
														{ // if there is no piece on the tile
															redJumpsLL->savePayload(jumpNW);
															pass1 = true;
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpSW = (moveCoords*) malloc(sizeof(moveCoords));
								jumpSW->oldRow = thisTile->row;
								jumpSW->oldCol = thisTile->col;
								jumpSW->newRow = (thisTile->row + 2);
								jumpSW->newCol = (thisTile->col - 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if(thisTile->tilePiece->getIsKing())
										{ // if the piece is a king
											if((row == jumpSW->newRow) && (col == jumpSW->newCol))
											{ // if on tile SW of piece
												if(jumpedSWTile->hasPiece)
												{ // if the tile being jumped has a piece on it
													if(!(jumpedSWTile->tilePiece->getTeam()))
													{ // if the piece is black
														if((thisTile->row < 6) && (thisTile->col > 1))
														{ // if position is legal
															if((*currentTile)->hasPiece == false)
															{ // if there is no piece on the tile
																redJumpsLL->savePayload(jumpSW);
																pass1 = true;
															}
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpSE = (moveCoords*) malloc(sizeof(moveCoords));
								jumpSE->oldRow = thisTile->row;
								jumpSE->oldCol = thisTile->col;
								jumpSE->newRow = (thisTile->row + 2);
								jumpSE->newCol = (thisTile->col + 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if(thisTile->tilePiece->getIsKing())
										{ // if the piece is a king
											if((row == jumpSE->newRow) && (col == jumpSE->newCol))
											{ // if on tile SE of piece
												if(jumpedSETile->hasPiece)
												{ // if the tile being jumped has a piece on it
													if(!(jumpedSETile->tilePiece->getTeam()))
													{ // if the piece is black
														if((thisTile->row < 6) && (thisTile->col < 6))
														{ // if position is legal
															if((*currentTile)->hasPiece == false)
															{ // if there is no piece on the tile
																redJumpsLL->savePayload(jumpSE);
																pass1 = true;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if(!pass1)
	{
		printf("no red jumps found.\n");
	}
	else
	{
		int L = redJumpsLL->length();
		moveCoords* redJumpsArr = (moveCoords*) malloc(L * sizeof(moveCoords));
		redJumpsLL->extractToArray(redJumpsArr);
		if(L == 1)
		{
			printf("one red jump found.\n");
		}
		else
		{
			printf("%d red jumps found.\n", L);
		}
		bool valid = false;
		while(!valid)
		{
			for(int i = 0; i < L; i++)
			{
				printf("option %d) red piece on (%d, %d) jumps to (%d, %d)\n", (i + 1), redJumpsArr[i].oldRow, redJumpsArr[i].oldCol, redJumpsArr[i].newRow, redJumpsArr[i].newCol);
			}
			printf("please enter the option number you would like.\n"); fflush(stdout);
			int choice = -6;
			scanf("%d", &choice);
			if((0 < choice) && (choice < (L + 1)))
			{
				this->lastTeam = true;
				moveCoords* lastMoveRed = (moveCoords*) malloc(sizeof(moveCoords));
				*lastMoveRed = redJumpsArr[choice - 1];
				this->lastMove = lastMoveRed;
				updateBoard(redJumpsArr[choice - 1].oldRow, redJumpsArr[choice - 1].oldCol, redJumpsArr[choice - 1].newRow, redJumpsArr[choice - 1].newCol);
				valid = true;
				R = true;
			}
			else
			{
				printf("invalid answer number.\n");
			}
		}
	} // pass1

//	printf("<< ending jumpRed()\n");
	return R;
}

bool board :: jumpBlack()
{
	bool R = false;
//	printf(">> starting jumpBlack()\n");

	bool pass1 = false; // if there are any legal jumps
	LList* blackJumpsLL = new LList();

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			boardTile* thisTile = *currentTile; // tile being tested
			boardTile* jumpedNETile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedNWTile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedSWTile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedSETile = (boardTile*) malloc(sizeof(boardTile*));
			if(thisTile->hasPiece)
			{ // if this tile has a piece on it
				if(!(thisTile->tilePiece->getTeam()))
				{ // if the piece is black
					for(int row = 0; row < 8; row++)
					{ // get the 4 tiles being jumped over
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile1 = ((this->tiles) + (8 * row) + col);
							if((row == (thisTile->row - 1)) && (col == (thisTile->col + 1)))
							{
								jumpedNETile = (*currentTile1);
							}
							if((row == (thisTile->row - 1)) && (col == (thisTile->col - 1)))
							{
								jumpedNWTile = (*currentTile1);
							}
							if((row == (thisTile->row + 1)) && (col == (thisTile->col - 1)))
							{
								jumpedSWTile = (*currentTile1);
							}
							if((row == (thisTile->row + 1)) && (col == (thisTile->col + 1)))
							{
								jumpedSETile = (*currentTile1);
							}
						}
					}
					for(int row = 0; row < 8; row++)
					{ // for every tile on the board, check if it a black piece with legal jumps
						for(int col = 0; col < 8; col++)
						{
							if((row == thisTile->row) && (col == thisTile->col))
							{ // if on tile being tested
								moveCoords* jumpNE = (moveCoords*) malloc(sizeof(moveCoords));
								jumpNE->oldRow = thisTile->row;
								jumpNE->oldCol = thisTile->col;
								jumpNE->newRow = (thisTile->row - 2);
								jumpNE->newCol = (thisTile->col + 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if(thisTile->tilePiece->getIsKing())
										{ // if the piece is a king
											if((row == jumpNE->newRow) && (col == jumpNE->newCol))
											{ // if on tile NE of piece
												if(jumpedNETile->hasPiece)
												{ // if the tile being jumped has a piece on it
													if(jumpedNETile->tilePiece->getTeam())
													{ // if the piece is black
														if((thisTile->row > 1) && (thisTile->col < 6))
														{ // if position is legal
															if((*currentTile)->hasPiece == false)
															{ // if there is no piece on the tile
																blackJumpsLL->savePayload(jumpNE);
																pass1 = true;
															}
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpNW = (moveCoords*) malloc(sizeof(moveCoords));
								jumpNW->oldRow = thisTile->row;
								jumpNW->oldCol = thisTile->col;
								jumpNW->newRow = (thisTile->row - 2);
								jumpNW->newCol = (thisTile->col - 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if(thisTile->tilePiece->getIsKing())
										{ // if the piece is a king
											if((row == jumpNW->newRow) && (col == jumpNW->newCol))
											{ // if on tile NW of piece
												if(jumpedNWTile->hasPiece)
												{ // if the tile being jumped has a piece on it
													if(jumpedNWTile->tilePiece->getTeam())
													{ // if the piece is black
														if((thisTile->row > 1) && (thisTile->col > 1))
														{ // if position is legal
															if((*currentTile)->hasPiece == false)
															{ // if there is no piece on the tile
																blackJumpsLL->savePayload(jumpNW);
																pass1 = true;
															}
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpSW = (moveCoords*) malloc(sizeof(moveCoords));
								jumpSW->oldRow = thisTile->row;
								jumpSW->oldCol = thisTile->col;
								jumpSW->newRow = (thisTile->row + 2);
								jumpSW->newCol = (thisTile->col - 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if((row == jumpSW->newRow) && (col == jumpSW->newCol))
										{ // if on tile SW of piece
											if(jumpedSWTile->hasPiece)
											{ // if the tile being jumped has a piece on it
												if(jumpedSWTile->tilePiece->getTeam())
												{ // if the piece is black
													if((thisTile->row < 6) && (thisTile->col > 1))
													{ // if position is legal
														if((*currentTile)->hasPiece == false)
														{ // if there is no piece on the tile
															blackJumpsLL->savePayload(jumpSW);
															pass1 = true;
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpSE = (moveCoords*) malloc(sizeof(moveCoords));
								jumpSE->oldRow = thisTile->row;
								jumpSE->oldCol = thisTile->col;
								jumpSE->newRow = (thisTile->row + 2);
								jumpSE->newCol = (thisTile->col + 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if((row == jumpSE->newRow) && (col == jumpSE->newCol))
										{ // if on tile SE of piece
											if(jumpedSETile->hasPiece)
											{ // if the tile being jumped has a piece on it
												if(jumpedSETile->tilePiece->getTeam())
												{ // if the piece is black
													if((thisTile->row < 6) && (thisTile->col < 6))
													{ // if position is legal
														if((*currentTile)->hasPiece == false)
														{ // if there is no piece on the tile
															blackJumpsLL->savePayload(jumpSE);
															pass1 = true;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if(!pass1)
	{
		printf("no black jumps found.\n");
	}
	else
	{
		int L = blackJumpsLL->length();
		moveCoords* blackJumpsArr = (moveCoords*) malloc(L * sizeof(moveCoords));
		blackJumpsLL->extractToArray(blackJumpsArr);
		if(L == 1)
		{
			printf("one black jump found.\n");
		}
		else
		{
			printf("%d black jumps found.\n", L);
		}

		bool valid = false;
		while(!valid)
		{
			for(int i = 0; i < L; i++)
			{
				printf("option %d) black piece on (%d, %d) jumps to (%d, %d)\n", (i + 1), blackJumpsArr[i].oldRow, blackJumpsArr[i].oldCol, blackJumpsArr[i].newRow, blackJumpsArr[i].newCol);
			}
			printf("please enter the option number you would like.\n"); fflush(stdout);
			int choice = -6;
			scanf("%d", &choice);
			if((0 < choice) && (choice < (L + 1)))
			{
				this->lastTeam = false;
				moveCoords* lastMoveBlack = (moveCoords*) malloc(sizeof(moveCoords));
				*lastMoveBlack = blackJumpsArr[choice - 1];
				this->lastMove = lastMoveBlack;
				updateBoard(blackJumpsArr[choice - 1].oldRow, blackJumpsArr[choice - 1].oldCol, blackJumpsArr[choice - 1].newRow, blackJumpsArr[choice - 1].newCol);
				valid = true;
				R = true;
			}
			else
			{
				printf("invalid answer number.\n");
			}
		}
	} // pass1

//	printf("<< ending jumpBlack()\n");
	return R;
}

LList* board :: listAllRedMoves()
{
	LList* R = new LList();
//	printf(">> starting listAllRedMoves()\n");

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			boardTile* thisTile = *currentTile; // tile being tested
			if(thisTile->hasPiece)
			{
				if(thisTile->tilePiece->getTeam())
				{
					moveCoords* moveNE = (moveCoords*) malloc(sizeof(moveCoords));
					moveNE->oldRow = thisTile->row;
					moveNE->oldCol = thisTile->col;
					moveNE->newRow = (thisTile->row - 1);
					moveNE->newCol = (thisTile->col + 1);
					for(int row = 0; row < 8; row++)
					{
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile = ((this->tiles) + (8 * row) + col);
							if((row == moveNE->newRow) && (col == moveNE->newCol))
							{ // if on tile NE of piece
								if((thisTile->row > 0) && (thisTile->col < 7))
								{ // if position is legal
									if((*currentTile)->hasPiece == false)
									{ // if there is no piece on the tile
										R->savePayload(moveNE);
									}
								}
							}
						}
					}
					moveCoords* moveNW = (moveCoords*) malloc(sizeof(moveCoords));
					moveNW->oldRow = thisTile->row;
					moveNW->oldCol = thisTile->col;
					moveNW->newRow = (thisTile->row - 1);
					moveNW->newCol = (thisTile->col - 1);
					for(int row = 0; row < 8; row++)
					{
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile = ((this->tiles) + (8 * row) + col);
							if((row == moveNW->newRow) && (col == moveNW->newCol))
							{ // if on tile NW of piece
								if((thisTile->row > 0) && (thisTile->col > 0))
								{ // if position is legal
									if((*currentTile)->hasPiece == false)
									{ // if there is no piece on the tile
										R->savePayload(moveNW);
									}
								}
							}
						}
					}
					moveCoords* moveSW = (moveCoords*) malloc(sizeof(moveCoords));
					moveSW->oldRow = thisTile->row;
					moveSW->oldCol = thisTile->col;
					moveSW->newRow = (thisTile->row + 1);
					moveSW->newCol = (thisTile->col - 1);
					for(int row = 0; row < 8; row++)
					{
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile = ((this->tiles) + (8 * row) + col);
							if(thisTile->tilePiece->getIsKing())
							{ // if the piece is a king
								if((row == moveSW->newRow) && (col == moveSW->newCol))
								{ // if on tile SW of piece
									if((thisTile->row < 7) && (thisTile->col > 0))
									{ // if position is legal
										if((*currentTile)->hasPiece == false)
										{ // if there is no piece on the tile
											R->savePayload(moveSW);
										}
									}
								}
							}
						}
					}
					moveCoords* moveSE = (moveCoords*) malloc(sizeof(moveCoords));
					moveSE->oldRow = thisTile->row;
					moveSE->oldCol = thisTile->col;
					moveSE->newRow = (thisTile->row + 1);
					moveSE->newCol = (thisTile->col + 1);
					for(int row = 0; row < 8; row++)
					{
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile = ((this->tiles) + (8 * row) + col);
							if(thisTile->tilePiece->getIsKing())
							{ // if the piece is a king
								if((row == moveSE->newRow) && (col == moveSE->newCol))
								{ // if on tile SE of piece
									if((thisTile->row < 7) && (thisTile->col < 7))
									{ // if position is legal
										if((*currentTile)->hasPiece == false)
										{ // if there is no piece on the tile
											R->savePayload(moveSE);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

//	printf("<< ending listAllMoves()\n");
	return R;
}

LList* board :: listAllRedJumps()
{
	LList* R = new LList();
//	printf(">> starting listAllRedJumps()\n");

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			boardTile* thisTile = *currentTile; // tile being tested
			boardTile* jumpedNETile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedNWTile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedSWTile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedSETile = (boardTile*) malloc(sizeof(boardTile*));
			if(thisTile->hasPiece)
			{ // if this tile has a piece on it
				if(thisTile->tilePiece->getTeam())
				{ // if the piece is red
					for(int row = 0; row < 8; row++)
					{ // get the 4 tiles being jumped over
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile1 = ((this->tiles) + (8 * row) + col);
							if((row == (thisTile->row - 1)) && (col == (thisTile->col + 1)))
							{
								jumpedNETile = (*currentTile1);
							}
							if((row == (thisTile->row - 1)) && (col == (thisTile->col - 1)))
							{
								jumpedNWTile = (*currentTile1);
							}
							if((row == (thisTile->row + 1)) && (col == (thisTile->col - 1)))
							{
								jumpedSWTile = (*currentTile1);
							}
							if((row == (thisTile->row + 1)) && (col == (thisTile->col + 1)))
							{
								jumpedSETile = (*currentTile1);
							}
						}
					}
					for(int row = 0; row < 8; row++)
					{ // for every tile on the board, check if it a red piece with legal jumps
						for(int col = 0; col < 8; col++)
						{
							if((row == thisTile->row) && (col == thisTile->col))
							{ // if on tile being tested
								moveCoords* jumpNE = (moveCoords*) malloc(sizeof(moveCoords));
								jumpNE->oldRow = thisTile->row;
								jumpNE->oldCol = thisTile->col;
								jumpNE->newRow = (thisTile->row - 2);
								jumpNE->newCol = (thisTile->col + 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if((row == jumpNE->newRow) && (col == jumpNE->newCol))
										{ // if on tile NE of piece
											if(jumpedNETile->hasPiece)
											{ // if the tile being jumped has a piece on it
												if(!(jumpedNETile->tilePiece->getTeam()))
												{ // if the piece is black
													if((thisTile->row > 1) && (thisTile->col < 6))
													{ // if position is legal
														if((*currentTile)->hasPiece == false)
														{ // if there is no piece on the tile
															R->savePayload(jumpNE);
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpNW = (moveCoords*) malloc(sizeof(moveCoords));
								jumpNW->oldRow = thisTile->row;
								jumpNW->oldCol = thisTile->col;
								jumpNW->newRow = (thisTile->row - 2);
								jumpNW->newCol = (thisTile->col - 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if((row == jumpNW->newRow) && (col == jumpNW->newCol))
										{ // if on tile NW of piece
											if(jumpedNWTile->hasPiece)
											{ // if the tile being jumped has a piece on it
												if(!(jumpedNWTile->tilePiece->getTeam()))
												{ // if the piece is black
													if((thisTile->row > 1) && (thisTile->col > 1))
													{ // if position is legal
														if((*currentTile)->hasPiece == false)
														{ // if there is no piece on the tile
															R->savePayload(jumpNW);
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpSW = (moveCoords*) malloc(sizeof(moveCoords));
								jumpSW->oldRow = thisTile->row;
								jumpSW->oldCol = thisTile->col;
								jumpSW->newRow = (thisTile->row + 2);
								jumpSW->newCol = (thisTile->col - 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if(thisTile->tilePiece->getIsKing())
										{ // if the piece is a king
											if((row == jumpSW->newRow) && (col == jumpSW->newCol))
											{ // if on tile SW of piece
												if(jumpedSWTile->hasPiece)
												{ // if the tile being jumped has a piece on it
													if(!(jumpedSWTile->tilePiece->getTeam()))
													{ // if the piece is black
														if((thisTile->row < 6) && (thisTile->col > 1))
														{ // if position is legal
															if((*currentTile)->hasPiece == false)
															{ // if there is no piece on the tile
																R->savePayload(jumpSW);
															}
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpSE = (moveCoords*) malloc(sizeof(moveCoords));
								jumpSE->oldRow = thisTile->row;
								jumpSE->oldCol = thisTile->col;
								jumpSE->newRow = (thisTile->row + 2);
								jumpSE->newCol = (thisTile->col + 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if(thisTile->tilePiece->getIsKing())
										{ // if the piece is a king
											if((row == jumpSE->newRow) && (col == jumpSE->newCol))
											{ // if on tile SE of piece
												if(jumpedSETile->hasPiece)
												{ // if the tile being jumped has a piece on it
													if(!(jumpedSETile->tilePiece->getTeam()))
													{ // if the piece is black
														if((thisTile->row < 6) && (thisTile->col < 6))
														{ // if position is legal
															if((*currentTile)->hasPiece == false)
															{ // if there is no piece on the tile
																R->savePayload(jumpSE);
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

//	printf("<< ending listAllRedJumps()\n");
	return R;
}

LList* board :: listAllBlackMoves()
{
	LList* R = new LList();
//	printf(">> starting listAllBlackMoves()\n");

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			boardTile* thisTile = *currentTile; // tile being tested
			if(thisTile->hasPiece)
			{
				if(!(thisTile->tilePiece->getTeam()))
				{
					moveCoords* moveNE = (moveCoords*) malloc(sizeof(moveCoords));
					moveNE->oldRow = thisTile->row;
					moveNE->oldCol = thisTile->col;
					moveNE->newRow = (thisTile->row - 1);
					moveNE->newCol = (thisTile->col + 1);
					for(int row = 0; row < 8; row++)
					{
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile = ((this->tiles) + (8 * row) + col);
							if(thisTile->tilePiece->getIsKing())
							{ // if the piece is a king
								if((row == moveNE->newRow) && (col == moveNE->newCol))
								{ // if on tile NE of piece
									if((thisTile->row > 0) && (thisTile->col < 7))
									{ // if position is legal
										if((*currentTile)->hasPiece == false)
										{ // if there is no piece on the tile
											R->savePayload(moveNE);
										}
									}
								}
							}
						}
					}
					moveCoords* moveNW = (moveCoords*) malloc(sizeof(moveCoords));
					moveNW->oldRow = thisTile->row;
					moveNW->oldCol = thisTile->col;
					moveNW->newRow = (thisTile->row - 1);
					moveNW->newCol = (thisTile->col - 1);
					for(int row = 0; row < 8; row++)
					{
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile = ((this->tiles) + (8 * row) + col);
							if(thisTile->tilePiece->getIsKing())
							{ // if the piece is a king
								if((row == moveNW->newRow) && (col == moveNW->newCol))
								{ // if on tile NW of piece
									if((thisTile->row > 0) && (thisTile->col > 0))
									{ // if position is legal
										if((*currentTile)->hasPiece == false)
										{ // if there is no piece on the tile
											R->savePayload(moveNW);
										}
									}
								}
							}
						}
					}
					moveCoords* moveSW = (moveCoords*) malloc(sizeof(moveCoords));
					moveSW->oldRow = thisTile->row;
					moveSW->oldCol = thisTile->col;
					moveSW->newRow = (thisTile->row + 1);
					moveSW->newCol = (thisTile->col - 1);
					for(int row = 0; row < 8; row++)
					{
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile = ((this->tiles) + (8 * row) + col);
							if((row == moveSW->newRow) && (col == moveSW->newCol))
							{ // if on tile SW of piece
								if((thisTile->row < 7) && (thisTile->col > 0))
								{ // if position is legal
									if((*currentTile)->hasPiece == false)
									{ // if there is no piece on the tile
										R->savePayload(moveSW);
									}
								}
							}
						}
					}
					moveCoords* moveSE = (moveCoords*) malloc(sizeof(moveCoords));
					moveSE->oldRow = thisTile->row;
					moveSE->oldCol = thisTile->col;
					moveSE->newRow = (thisTile->row + 1);
					moveSE->newCol = (thisTile->col + 1);
					for(int row = 0; row < 8; row++)
					{
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile = ((this->tiles) + (8 * row) + col);
							if((row == moveSE->newRow) && (col == moveSE->newCol))
							{ // if on tile SE of piece
								if((thisTile->row < 7) && (thisTile->col < 7))
								{ // if position is legal
									if((*currentTile)->hasPiece == false)
									{ // if there is no piece on the tile
										R->savePayload(moveSE);
									}
								}
							}
						}
					}
				}
			}
		}
	}

//	printf("<< ending listAllBlackMoves()\n");
	return R;
}

LList* board :: listAllBlackJumps()
{
	LList* R = new LList();
//	printf(">> starting listAllBlackJumps()\n");

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			boardTile* thisTile = *currentTile; // tile being tested
			boardTile* jumpedNETile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedNWTile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedSWTile = (boardTile*) malloc(sizeof(boardTile*));
			boardTile* jumpedSETile = (boardTile*) malloc(sizeof(boardTile*));
			if(thisTile->hasPiece)
			{ // if this tile has a piece on it
				if(!(thisTile->tilePiece->getTeam()))
				{ // if the piece is black
					for(int row = 0; row < 8; row++)
					{ // get the 4 tiles being jumped over
						for(int col = 0; col < 8; col++)
						{
							boardTile** currentTile1 = ((this->tiles) + (8 * row) + col);
							if((row == (thisTile->row - 1)) && (col == (thisTile->col + 1)))
							{
								jumpedNETile = (*currentTile1);
							}
							if((row == (thisTile->row - 1)) && (col == (thisTile->col - 1)))
							{
								jumpedNWTile = (*currentTile1);
							}
							if((row == (thisTile->row + 1)) && (col == (thisTile->col - 1)))
							{
								jumpedSWTile = (*currentTile1);
							}
							if((row == (thisTile->row + 1)) && (col == (thisTile->col + 1)))
							{
								jumpedSETile = (*currentTile1);
							}
						}
					}
					for(int row = 0; row < 8; row++)
					{ // for every tile on the board, check if it a black piece with legal jumps
						for(int col = 0; col < 8; col++)
						{
							if((row == thisTile->row) && (col == thisTile->col))
							{ // if on tile being tested
								moveCoords* jumpNE = (moveCoords*) malloc(sizeof(moveCoords));
								jumpNE->oldRow = thisTile->row;
								jumpNE->oldCol = thisTile->col;
								jumpNE->newRow = (thisTile->row - 2);
								jumpNE->newCol = (thisTile->col + 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if(thisTile->tilePiece->getIsKing())
										{ // if the piece is a king
											if((row == jumpNE->newRow) && (col == jumpNE->newCol))
											{ // if on tile NE of piece
												if(jumpedNETile->hasPiece)
												{ // if the tile being jumped has a piece on it
													if(jumpedNETile->tilePiece->getTeam())
													{ // if the piece is black
														if((thisTile->row > 1) && (thisTile->col < 6))
														{ // if position is legal
															if((*currentTile)->hasPiece == false)
															{ // if there is no piece on the tile
																R->savePayload(jumpNE);
															}
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpNW = (moveCoords*) malloc(sizeof(moveCoords));
								jumpNW->oldRow = thisTile->row;
								jumpNW->oldCol = thisTile->col;
								jumpNW->newRow = (thisTile->row - 2);
								jumpNW->newCol = (thisTile->col - 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if(thisTile->tilePiece->getIsKing())
										{ // if the piece is a king
											if((row == jumpNW->newRow) && (col == jumpNW->newCol))
											{ // if on tile NW of piece
												if(jumpedNWTile->hasPiece)
												{ // if the tile being jumped has a piece on it
													if(jumpedNWTile->tilePiece->getTeam())
													{ // if the piece is black
														if((thisTile->row > 1) && (thisTile->col > 1))
														{ // if position is legal
															if((*currentTile)->hasPiece == false)
															{ // if there is no piece on the tile
																R->savePayload(jumpNW);
															}
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpSW = (moveCoords*) malloc(sizeof(moveCoords));
								jumpSW->oldRow = thisTile->row;
								jumpSW->oldCol = thisTile->col;
								jumpSW->newRow = (thisTile->row + 2);
								jumpSW->newCol = (thisTile->col - 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if((row == jumpSW->newRow) && (col == jumpSW->newCol))
										{ // if on tile SW of piece
											if(jumpedSWTile->hasPiece)
											{ // if the tile being jumped has a piece on it
												if(jumpedSWTile->tilePiece->getTeam())
												{ // if the piece is black
													if((thisTile->row < 6) && (thisTile->col > 1))
													{ // if position is legal
														if((*currentTile)->hasPiece == false)
														{ // if there is no piece on the tile
															R->savePayload(jumpSW);
														}
													}
												}
											}
										}
									}
								}
								moveCoords* jumpSE = (moveCoords*) malloc(sizeof(moveCoords));
								jumpSE->oldRow = thisTile->row;
								jumpSE->oldCol = thisTile->col;
								jumpSE->newRow = (thisTile->row + 2);
								jumpSE->newCol = (thisTile->col + 2);
								for(int row = 0; row < 8; row++)
								{
									for(int col = 0; col < 8; col++)
									{
										boardTile** currentTile = ((this->tiles) + (8 * row) + col);
										if((row == jumpSE->newRow) && (col == jumpSE->newCol))
										{ // if on tile SE of piece
											if(jumpedSETile->hasPiece)
											{ // if the tile being jumped has a piece on it
												if(jumpedSETile->tilePiece->getTeam())
												{ // if the piece is black
													if((thisTile->row < 6) && (thisTile->col < 6))
													{ // if position is legal
														if((*currentTile)->hasPiece == false)
														{ // if there is no piece on the tile
															R->savePayload(jumpSE);
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

//	printf("<< ending listAllBlackJumps()\n");
	return R;
}

void board :: cpuMove()
{
//	printf(">> starting cpuMove()\n");

	LList* cpuMovesLL = listAllBlackMoves();

	int L = cpuMovesLL->length();

	moveCoords* cpuMovesArr = (moveCoords*) malloc(L * sizeof(moveCoords));
	cpuMovesLL->extractToArray(cpuMovesArr);

	int randChoice = (rand() % L); // random index 1-L

	this->lastTeam = false;
	moveCoords* lastMoveBlack = (moveCoords*) malloc(sizeof(moveCoords));
	*lastMoveBlack = cpuMovesArr[randChoice];
	this->lastMove = lastMoveBlack;

	updateBoard(cpuMovesArr[randChoice].oldRow, cpuMovesArr[randChoice].oldCol, cpuMovesArr[randChoice].newRow, cpuMovesArr[randChoice].newCol);

	printf("cpu moved black piece on (%d, %d) to (%d, %d)\n", cpuMovesArr[randChoice].oldRow, cpuMovesArr[randChoice].oldCol, cpuMovesArr[randChoice].newRow, cpuMovesArr[randChoice].newCol);

//	printf("<< ending cpuMove()\n");
}

bool board :: cpuJump()
{
	bool R = false;;
//	printf(">> starting cpuJump()\n");

	LList* cpuJumpsLL = listAllBlackJumps();

	int L = cpuJumpsLL->length();
	if(L > 0)
	{
		moveCoords* cpuJumpsArr = (moveCoords*) malloc(L * sizeof(moveCoords));
		cpuJumpsLL->extractToArray(cpuJumpsArr);

		int randChoice = (rand() % L); // random index 1-L

		this->lastTeam = false;
		moveCoords* lastMoveBlack = (moveCoords*) malloc(sizeof(moveCoords));
		*lastMoveBlack = cpuJumpsArr[randChoice];
		this->lastMove = lastMoveBlack;

		updateBoard(cpuJumpsArr[randChoice].oldRow, cpuJumpsArr[randChoice].oldCol, cpuJumpsArr[randChoice].newRow, cpuJumpsArr[randChoice].newCol);
		printf("cpu made black piece on (%d, %d) jump to (%d, %d)\n", cpuJumpsArr[randChoice].oldRow, cpuJumpsArr[randChoice].oldCol, cpuJumpsArr[randChoice].newRow, cpuJumpsArr[randChoice].newCol);
		R = true;
	}

//	printf("<< ending cpuJump()\n");
	return R;
}

int board :: isWin()
{
	int R = 0;
//	printf(">> starting isWin()");

	int totalRedPieces = 0;
	int totalBlackPieces = 0;
	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = ((this->tiles) + (8 * row) + col);
			if((*currentTile)->hasPiece)
			{ // if piece is found
				if((*currentTile)->tilePiece->getTeam())
				{ // if red
					totalRedPieces++;
				}
				else
				{
					totalBlackPieces++;
				}
			}
		}
	}
	if(totalRedPieces == 0)
	{
		R = 2;
	}
	if(totalBlackPieces == 0)
	{
		R = 1;
	}

//	printf("<< ending isWin()");
	return R;
}
