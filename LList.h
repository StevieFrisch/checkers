/*
 * LList.h
 *
 *  Created on: Feb 26, 2021
 *      Author: theresesmith
 */

#ifndef LLIST_H_
#define LLIST_H_

//////

#include "include.h"

//////

typedef struct
{
	int oldRow;
	int oldCol;
	int newRow;
	int newCol;
} moveCoords;
typedef moveCoords Payload;
struct LLNode;
typedef struct LLNode
{
	struct LLNode* next;
	struct LLNode* prev;
	Payload* payP;
}LLNode;

typedef struct backFromDQFIFO
{
	Payload* mp;
	LLNode* newQHead;
}backFromDQFIFO;

//////

class LList {
public:
	LList();
	virtual ~LList();
	LLNode* makeEmptyLinkedList();
	LLNode* removeFromList(Payload* pP);
	void savePayload(Payload* mp);
	bool isEmpty();
	Payload* dequeueLIFO();
	backFromDQFIFO* dequeueFIFO();
	void printHistory();
	int length();
	moveCoords* extractToArray(moveCoords*);

//////

private:
	LLNode* lp;
};

//////

#endif /* LLIST_H_ */
