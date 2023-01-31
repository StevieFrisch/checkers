	/*
 * gameRecorder.cpp
 *
 *  Created on: Mar 12, 2021
 *      Author: wduf0
 */

#include "gameRecorder.h"

//////

gameRecorder::gameRecorder(char* logFileName, boardTile** corner) {
	// TODO Auto-generated constructor stub
	this->logFileName = logFileName;
	this->corner = corner;

	FILE* fp;
	fp = fopen(this->logFileName, "w");
	fprintf(fp," "); // clears file
	fclose(fp);
}

gameRecorder::~gameRecorder() {
	// TODO Auto-generated destructor stub
}

//////

void gameRecorder :: logTurn(char* filename, bool team, moveCoords* lastMove, LList* moves, LList* jumps)
{
	FILE* fp;
	fp = fopen(this->logFileName, "ab"); // ab = append mode

	fprintf(fp, "\n******\n\nhere is the current board:\n");
	for(int row = 0; row < 8; row++)
	{ // writes board
		for(int col = 0; col < 8; col++)
		{
			boardTile** currentTile = (this->corner + (8 * row) + col);
			if((*currentTile)->hasPiece)
			{
				if((*currentTile)->tilePiece->getTeam())
				{
					if((*currentTile)->tilePiece->getIsKing())
					{
						fprintf(fp, "| R ");
					}
					else
					{
						fprintf(fp, "| r ");
					}
				}
				else if((*currentTile)->tilePiece->getIsKing())
				{
					fprintf(fp, "| B ");
				}
				else
				{
					fprintf(fp, "| b ");
				}
			}
			else if((row % 2) == (col % 2))
			{ // shades in the tiles that cannot be moved to
				fprintf(fp, "|///");
			}
			else
			{
				fprintf(fp, "|   ");
			}
		}
		fprintf(fp, "|\n");
	} // end of writes board
	printf("\n");

	int totalJumps = jumps->length();
	int totalMoves = moves->length();

	if(team)
	{ // writes who moved what
		if(totalJumps > 0)
		{
			fprintf(fp, "red made the piece on (%d, %d) jump to (%d, %d).\n", lastMove->oldRow, lastMove->oldCol, lastMove->newRow, lastMove->newCol);
			fprintf(fp, "red had %d legal jumps that turn", totalJumps);

		}
		else
		{
			fprintf(fp, "red moved piece on (%d, %d) to (%d, %d).\n", lastMove->oldRow, lastMove->oldCol, lastMove->newRow, lastMove->newCol);
			fprintf(fp, "red had %d legal moves that turn", totalMoves);
		}
	}
	else
	{
		if(totalJumps > 0)
		{
			fprintf(fp, "black made the piece on (%d, %d) jump to (%d, %d).\n", lastMove->oldRow, lastMove->oldCol, lastMove->newRow, lastMove->newCol);
			fprintf(fp, "black had %d legal jumps that turn", totalJumps);
		}
		else
		{
			fprintf(fp, "black moved piece on (%d, %d) to (%d, %d).\n", lastMove->oldRow, lastMove->oldCol, lastMove->newRow, lastMove->newCol);
			fprintf(fp, "black had %d legal moves that turn", totalMoves);
		}
	} // end of writing move
	fprintf(fp, "\n");

	fclose(fp);
}
