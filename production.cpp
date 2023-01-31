/*
 * production.cpp
 *
 *  Created on: Mar 2, 2021
 *      Author: wduf0
 */

#include "production.h"

//////

production :: production() {
	// TODO Auto-generated constructor stub

}

production :: ~production() {
	// TODO Auto-generated destructor stub
}

//////

bool production :: runProduction(int argc, char* argv[])
{
	bool R = true;

	if(argc <= 1) //no interesting information
	{
		puts("Didn't find any arguments.");
		fflush(stdout);
		R = false;
	}
	else //there is interesting information
	{
		printf("Found %d arguments.\n", argc);
		fflush(stdout);
		bool log = false;
		char logFileName[FILENAMELENGTHALLOWANCE];
		bool upload = false;
		char uploadFileName[FILENAMELENGTHALLOWANCE];

		for(int i = 1; i < argc; i++) //don't want to read argv[0]
		{//argv[i] is a string
			switch(i)
			{
			case 1:
				//this is log file name
				printf("The length of the log file name is %d.\n", strlen(argv[i])); // console wanted %I64d instead of %d
				printf("The proposed log file name is %s.\n", argv[i]);
				if(strlen(argv[i]) >= FILENAMELENGTHALLOWANCE)
				{
					puts("log file name is too long.");
					fflush(stdout);
					R = false;
				}
				else
				{
					strcpy(logFileName, argv[i]);
					printf("Filename was %s.\n", logFileName);
					log = true;
					fflush(stdout);
				}
				break;
			case 2:
				// this is the upload file
				printf("The length of the upload file name is %d.\n", strlen(argv[i])); // console wanted %I64d instead of %d
				printf("The proposed upload file name is %s.\n", argv[i]);
				if(strlen(argv[i]) >= FILENAMELENGTHALLOWANCE)
				{
					puts("upload file name is too long.");
					fflush(stdout);
				}
				else
				{
					strcpy(uploadFileName, argv[i]);
					printf("Filename was %s.\n", uploadFileName);
					upload = true;
					fflush(stdout);
				}
				break;
			default:
				if(!log)
				{
				puts("Unexpected argument count."); fflush(stdout);
				R = false;
				break;
				}
			}//end of switch
		}//end of for loop on argument count

		boardTile** corner = (boardTile**) malloc(64 * sizeof(boardTile*));
		board* checkerBoard = new board(corner, false, 0);
		checkerBoard->initBoard();
		if(upload)
		{
			checkerBoard->uploadBoard(uploadFileName);
		}
		else
		{
			printf("no upload file found.\n");
		}

		int choice = -6;
		bool valid = false;
		gameRecorder* gR = new gameRecorder(logFileName, checkerBoard->getTiles());
		LList* moves = new LList();
		LList* jumps = new LList();
		while(!valid)
		{
			printf("would you like to play with 2 players or against a cpu? (please enter a single integer)\n");
			printf("option 1) 2 players\noption 2) against a cpu\n"); fflush(stdout);
			scanf("%d", &choice);
			if((choice != 1) && (choice != 2))
			{
				printf("invalid answer. please enter an integer 1-2.");
			}
			else
			{
				valid = true;
			}
		}
		int winner = 0;
		if(choice == 1)
		{ // 2 players
			printf("you chose to play with 2 players.\n");
			while(winner == 0)
			{
				checkerBoard->displayBoard();
				moves = checkerBoard->listAllRedMoves();
				jumps = checkerBoard->listAllRedJumps();
				if(!(checkerBoard->jumpRed()))
				{
					checkerBoard->moveRed();
					checkerBoard->displayBoard();
				}
				gR->logTurn(logFileName, checkerBoard->getLastTeam(), checkerBoard->getLastMove(), moves, jumps);
				winner = checkerBoard->isWin();
				if(winner == 0)
				{
					moves = checkerBoard->listAllBlackMoves();
					jumps = checkerBoard->listAllBlackJumps();
					if(!(checkerBoard->jumpBlack()))
					{
						checkerBoard->moveBlack();
						checkerBoard->displayBoard();
					}
					gR->logTurn(logFileName, checkerBoard->getLastTeam(), checkerBoard->getLastMove(), moves, jumps);
					winner = checkerBoard->isWin();
				}
				fflush(stdout);
			}
		} // end of 2 players
		else
		{ // cpu
			printf("you chose to play against a cpu.\n");
			int choice1 = -6;
			bool valid1 = false;
			while(!valid1)
			{
				printf("would you like to move first or second? (please enter a single integer)\n");
				printf("option 1) move first\noption 2) move second\n"); fflush(stdout);
				scanf("%d", &choice1);
				if((choice1 != 1) && (choice1 != 2))
				{
					printf("invalid answer. please enter an integer 1-2.");
				}
				else
				{
					valid1 = true;
				}
			}
			if(choice1 == 2)
			{
				printf("cpu to move first.\n");
				moves = checkerBoard->listAllBlackMoves();
				jumps = checkerBoard->listAllBlackJumps();
				if(!(checkerBoard->cpuJump()))
				{
					checkerBoard->cpuMove();
					checkerBoard->displayBoard(); printf("\n");
				}
				gR->logTurn(logFileName, checkerBoard->getLastTeam(), checkerBoard->getLastMove(), moves, jumps);
			}
			while(winner == 0)
			{
				checkerBoard->displayBoard();
				moves = checkerBoard->listAllRedMoves();
				jumps = checkerBoard->listAllRedJumps();
				if(!(checkerBoard->jumpRed()))
				{
					checkerBoard->moveRed();
					checkerBoard->displayBoard();
				}
				gR->logTurn(logFileName, checkerBoard->getLastTeam(), checkerBoard->getLastMove(), jumps, jumps);
				winner = checkerBoard->isWin();

				if(winner == 0)
				{
					moves = checkerBoard->listAllBlackMoves();
					jumps = checkerBoard->listAllBlackJumps();
					if(!(checkerBoard->cpuJump()))
					{
						checkerBoard->cpuMove();
						checkerBoard->displayBoard(); printf("\n");
					}
					gR->logTurn(logFileName, checkerBoard->getLastTeam(), checkerBoard->getLastMove(), moves, jumps);
					winner = checkerBoard->isWin();
				}
				fflush(stdout);
			}
		}
		if(winner == 1)
		{
			printf("red wins!");
		}
		else
		{
			printf("black wins!");
		}
	} // interesting info

	return R;
}
