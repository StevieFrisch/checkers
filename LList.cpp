/*
 * LList.cpp
 *
 *  Created on: Feb 26, 2021
 *      Author: theresesmith
 */

#include "LList.h"

//////

LList :: LList() {
	// TODO Auto-generated constructor stub
	lp = makeEmptyLinkedList();
}

LList :: ~LList() {
	// TODO Auto-generated destructor stub
}

//////

int LList :: length()
{
	int R = 0;

	if(!(lp->payP ==(Payload*) 0))
	{
		//traverse the list, adding for every element
		LLNode* temp = lp;
		while(temp->next)
		{
			R++;
			temp = (LLNode*) temp->next;

		}
		R++;
	}

	return R;
}

moveCoords* LList :: extractToArray(moveCoords* arr)
{
//	puts(">> starting extractToArray()\n");

	if(lp->payP->oldRow == lp->payP->newRow)
	{
		puts("empty list. oldRow == newRow");
	}
	else
	{ //traverse the list, extracting as we go
		LLNode* temp = lp;
		int i = 0;
		while(temp->next)
		{
			arr[i] = *(temp->payP);
			temp = (LLNode*) temp->next;
			i++;
		}
		arr[i] = *(temp->payP);
	}

//	puts("<< ending extractToArray()\n");
	return arr;
}

bool LList :: isEmpty()
{
	bool ans = false;

	if(lp->payP == (Payload*)0)
	{
		ans = true;
	}

	return ans;
}

LLNode* LList :: makeEmptyLinkedList()
{
	LLNode* lp = (LLNode*) malloc(sizeof(LLNode));
	lp->next = (struct LLNode*)0;
	lp->prev = (struct LLNode*)0;
	lp->payP = (Payload*)0;

	return lp;
}

void LList :: savePayload(Payload* mp)
{
	//if the list is empty, then make payP be mp
	//else traverse the list,
	//make a new list element
	//put mp in that
	//attach the new list element to the existing list
	if(isEmpty())
	{
		lp->payP = mp;
	}
	else
	{
		LLNode* temp = lp;
		while(temp->next)
		{
			temp=(LLNode*)temp->next;
		}
		//now temp points to the last element

		//make a new element, attach mp to it, wire up the new element
		LLNode* newList = makeEmptyLinkedList();
		newList->payP = mp;
		temp->next = (struct LLNode*)newList;
		newList->prev = (struct LLNode*) temp;
	}
}

Payload* LList :: dequeueLIFO()
{ // don't need dqLIFO();
	Payload* payP = (Payload*)0;
//	if(isEmpty())
//	{
//		puts("Trying to dequeue from empty.");
//	}
//	else
//	{
//
//		LLNode* temp = lp;
//		while(temp->next)
//		{
//			temp=(LLNode*)temp->next;
//		}
//		//now temp points to the last element
//
//
//		payP = temp->payP;
//		temp->payP = (Payload*)0;
//
//		//remove the last, now empty, element
//		if(temp->prev)
//		{
//			temp=(LLNode*)temp->prev;
//			//free(temp->next);
//
//			temp->next = (struct LLNode*)0;
//		}
//		else
//		{
//			puts("Queue is now empty");
//		}
//		puts("returning from dequeue");fflush(stdout);
//	}
//
	return payP;
}

backFromDQFIFO* LList :: dequeueFIFO()
{ // don't need dqFIFO();
	backFromDQFIFO* fp = (backFromDQFIFO*) malloc(sizeof(backFromDQFIFO));
//	if(lp->next == (struct LLNode*)0)
//	{
//		//list of length 1 or 0
//		fp->newQHead= lp;
//	}
//	else
//	{
//		fp->newQHead= (LLNode*) lp->next;
//	}
//	fp->mp= lp->payP;//all return values are set
//	if(lp->next != (struct LLNode*)0)
//	{
//		//length list is >1
//		free(lp);
//	}

	return fp;
}

void LList :: printHistory()
{ // don't need printHistory();
    puts("Printing history");
    if(lp->payP ==(Payload*)0)
    {
         puts("Empty list");
    }
    else
    {
	    //traverse the list, printing as we go
        LLNode* temp = lp;
        while(temp->next)
        {
            printf("(%d, %d) -> (%d, %d).\n", temp->payP->oldRow, temp->payP->oldCol, temp->payP->newRow, temp->payP->newCol);
            temp = (LLNode*) temp->next;

        }
        printf("(%d, %d) -> (%d, %d).\n", temp->payP->oldRow, temp->payP->oldCol, temp->payP->newRow, temp->payP->newCol);
    }
}

LLNode* LList :: removeFromList(Payload* pP)
{ // don't need removeFromList();
	LLNode* retHead = lp;//only changes if first element gets removed
//	//find the payload
//	//use the structure of a list, namely, list is empty or element followed by list
//	if(isEmpty())
//	{
//		//nothing to do
//	}
//	else
//	{
//		//puts("list is not empty");fflush(stdout);
//		LLNode* altHead = (LLNode*)lp->next;
//		//find the item, if it is there
//		LLNode* temp = lp;
//		bool done = false;
//		while((!done) && temp->next)
//		{
//			//are we there yet?
//			if(temp->payP == pP)
//			{
//				done=true;
//				//puts("found it 1");fflush(stdout);
//			}
//			else
//			{
//				temp=(LLNode*)temp->next;
//			}
//		}
//		//either we are pointing to the correct element, or we are at the end, or both
//		if((temp->payP) == pP)
//		{
//			//puts("found it 2");fflush(stdout);
//			//found it, remove it
//			//are we at the beginning?
//			if(temp == lp)
//			{  //found it at the first element
//				//puts("found it at first element");fflush(stdout);
//				//is the list of length 1?
//				if(!(temp->next))
//				{//if there is no next
//					//remove payload, return empty list
//					lp->payP = (Payload*)0;
//				}
//				else //not of length 1
//				{ //not freeing the Payload, but freeing the first list element
//					//puts("found it at first element of list with length > 1");fflush(stdout);
//					//free(hP);
//					retHead = altHead;
//				}
//			}
//			else //not found at first location in list
//			{
//				//puts("found it not at first element");fflush(stdout);
//				//save the linkages
//				//found element has a next
//				//found element has a prev
//				//participant before has a next
//				//participant after has a prev
//				LLNode* prevPart = (LLNode*) temp->prev;//non-zero because not at first element
//				LLNode* nextPart = (LLNode*) temp->next;//could be zero, if found at last element
//				prevPart->next = (struct LLNode*) nextPart;//RHS is 0 if at end
//				//puts("after setting the next of the previous");fflush(stdout);
//               // printf("Next is %p, %d\n", nextPart, (bool)nextPart);fflush(stdout);
//				if((bool)nextPart)//don't need guarded block if element found at end of list
//				{
//					//puts("before setting the previous of the next");fflush(stdout);
//					nextPart->prev = (struct LLNode*) prevPart;
//
//				}
//				//puts("after handling the  previous of the next");fflush(stdout);
//			}//end of not found at first location
//		}//end of found it
//		else
//		{
//			//didn't find it
//			//puts("did not find it");fflush(stdout);
//			//nothing to do
//		}//end did not find it
//	}
//	//printf("Returning %p\n", retHead); fflush(stdout);

	return retHead;
}
