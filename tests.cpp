/*
 * tests.cpp
 *
 *  Created on: Mar 2, 2021
 *      Author: wduf0
 */

#include "tests.h"
#include "gameRecorder.h"
#include "LList.h"


//////

tests :: tests() {
	// TODO Auto-generated constructor stub

}

tests :: ~tests() {
	// TODO Auto-generated destructor stub
}

//////

bool tests :: runTests()
{
	bool ok1 = testInitBoard();
	bool ok2 = testUploadBoard();
	bool ok3 = testDisplayBoard();
	bool ok4 = testCpuMove();
	bool ok5 = testCpuJump();
	bool ok6 = testListAllRedMoves();
	bool ok7 = testListAllBlackMoves();
	bool ok8 = testListAllBlackJumps();
	bool ok9 = testListAllRedJumps();
	bool ok10 = testLogBoard();
	bool ok11 = testIsWin();

	return ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7 && ok8 && ok9 && ok10 && ok11;
}

bool tests :: testInitBoard()
{
	bool ok = false;

	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();
	boardTile** thisTile = (corner + 1); // row 0, column 1 is where the first piece is

	if(!((*thisTile)->tilePiece->getTeam()))
	{ // first piece is black
		ok = true;
	}

	if(ok)
	{
		printf("test testInitBoard passed \n");
	}
	else
	{
		printf("test testInitBoard failed \n");
	}

	return ok;
}

bool tests :: testUploadBoard()
{
	bool ok = false;

	FILE* fp;
	fp = fopen("config0.txt", "r");

	char str[33];
	for(int i = 0; i < 32; i++)
	{ // transfers the file to a string
		fscanf(fp, "%c", &(str[i]));
	}
	fclose(fp);


	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);

	cb->uploadBoard(str);

	boardTile** thisTile = (corner + 1); // row 0, column 1 is where the first piece is
	if(!((*thisTile)->tilePiece->getTeam()))
	{ // first piece is black in example config file
		ok = true;
	}

	if(ok)
	{
		printf("test testUploadBoard passed \n");
	}
	else
	{
		printf("test testUploadBoard failed \n");
	}

	return ok;
}

bool tests :: testDisplayBoard()
{
	bool ok = true;

	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();
	boardTile** thisTile = (corner + 1); // row 0, column 1 is where the first piece is
	cb->displayBoard();

	if(!((*thisTile)->tilePiece->getTeam()))
	{ // first piece is black
		ok = true;
	}

	if(ok)
	{
		printf("^ if this displays the board test displayBoard passes \n");
	}
	else
	{
		printf("test testDisplayBoard failed \n");
	}

	return ok;
}

bool tests :: testCpuMove()
{
	bool ok = false;

	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();

	char str[50];
	strcpy(str, "config1.txt");
	cb->uploadBoard(str);

	cb->cpuMove();
	boardTile** thisTile = (corner + 8); // row 0, column 1 is where the first piece is

	if(!(*thisTile)->tilePiece->getTeam())
	{
		ok = true;
		printf("test testCpuMove passed \n");
	}
	else
	{
		printf("test testCpuMove failed \n");
	}

	return ok;
}

bool tests :: testCpuJump()
{
	bool ok = false;

	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();

	char str[50];
	strcpy(str, "config3.txt");
	cb->uploadBoard(str);


	cb->cpuJump();
	boardTile** thisTile = (corner + 20); // row 0, column 1 is where the first piece is

	if(!(*thisTile)->tilePiece->getTeam())
	{
		ok = true;
		printf("test testCpuJump passed \n");
	}
	else
	{
		printf("test testCpuJump failed \n");
	}

	return ok;
}

bool tests :: testListAllRedMoves()
{
	bool ok = false;
	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();

	char str[50];
	strcpy(str, "config2.txt");
	cb->uploadBoard(str);

//	cb->displayBoard();
	LList* list = new LList;
	list = cb->listAllRedMoves();
	int length = list->length();

	printf("%d \n", length);

	if(length == 4)
	{
		ok = true;
		printf("test testListAllRedMoves passed \n");
	}
	else
	{
		printf("test testListAllRedMoves failed \n");
	}

	return ok;
}

bool tests :: testListAllBlackMoves()
{
	bool ok = false;
	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();

	char str[50];
	strcpy(str, "config4.txt");
	cb->uploadBoard(str);

	//	cb->displayBoard();
	LList* list = new LList;
	list = cb->listAllBlackMoves();
	int length = list->length();
	printf("%d \n", length);


	if(length == 4)
	{
		ok = true;
		printf("test testListAllBlackMoves passed \n");
	}
	else
	{
		printf("test testListAllBlackMoves failed \n");
	}

	return ok;
}

bool tests :: testListAllBlackJumps()
{
	bool ok = false;
	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();

	char str[50];
	strcpy(str, "config5.txt");
	cb->uploadBoard(str);


	LList* list = new LList;
	list = cb->listAllBlackJumps();
	int length = list->length();

	printf("%d \n", length);

	if(length == 4)
	{
		ok = true;
		printf("test testListAllBlackJumps passed \n");
	}
	else
	{
		printf("test testListAllBlackJumps failed \n");
	}

	return ok;
}

bool tests :: testListAllRedJumps()
{
	bool ok = false;
	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();

	char str[50];
	strcpy(str, "config6.txt");
	cb->uploadBoard(str);

	LList* list = new LList;
	list = cb->listAllRedJumps();
	int length = list->length();

	printf("%d \n", length);

	if(length == 4)
	{
		ok = true;
		printf("test testListAllRedJumps passed \n");
	}
	else
	{
		printf("test testListAllRedJumps failed \n");
	}

	return ok;
}


bool tests :: testLogBoard()
{
	bool ok = false;

	char str[50];
	strcpy(str, "log1.txt");
	LList* list = new LList();
	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();
	gameRecorder* gr = new gameRecorder(str, cb->getTiles());
	cb->cpuMove();
	cb->displayBoard();
	gr->logTurn(str, cb->getLastTeam(), cb->getLastMove(), list, list);

	FILE* fp;
	fp = fopen(str, "r");
	char found[36];
	for(int i = 0; i < 36; i++)
	{
		fscanf(fp, "%c", &found[i]);
	}
	fclose(fp);

	char newC[50];
	for(int i = 0; i < 27; i++)
	{
		newC[i] = found[i + 9];
	}

	if(strcmp("here is the current board:", newC))
	{
		ok = true;
		printf("test testLogBoard passed. \n");
	}
	else
	{
		printf("test testLogBoard failed. \n");
	}

	return ok;
}


bool tests :: testIsWin()
{
	bool ok = true;
	boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
	board* cb = new board(corner, false, 0);
	cb->initBoard();

	char str[50];
	strcpy(str, "config2.txt");
	cb->uploadBoard(str);
	cb->displayBoard();

	if((cb->isWin() == 1))
	{
		ok = true;
		printf("test testIsWin passed. \n");
	}
	else
	{
		printf("test testIsWin failed. \n");
	}

	return ok;
}





