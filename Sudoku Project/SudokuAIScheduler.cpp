/*
 *  SudokuAISheduler.cpp
 *  
 *
 *  Created by Michael Weingert on 12-01-08.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SudokuAIScheduler.h"
#include "assert.h"

#include "stdio.h"

static AIScheduler * Instance;

AIScheduler::AIScheduler()
{
	size = 0;
}

void AIScheduler::UpdateAllPriorities(int environmentvariable/*, ...*/)
{
	for (int i = 1; i < NUM_TASKS; i++) // start heap index at 1 to make re-heap easier
	{
		Heap[i]->updatePriority(environmentvariable/*, ...*/);
	}
	//printf("Update priority?");
	//fflush(stdout);
}

AIScheduler* AIScheduler::getInstance()
{
	if (Instance == NULL)
		Instance = new AIScheduler();
	return Instance;
}

void AIScheduler::PrintTree()
{
	//print
}

void AIScheduler::ReHeapify()
{
	//Because all of the priorities have been changed (presumably), remake tree
	//In future iterations, it may be worthwhile to check to see which have changed
	//And maybe only remake part of the tree
	
	AITask* tempHeap[size+1];
	for (int i = 1; i < size+1; i++)
	{
		//copy over the values from the tree to a temp array
		tempHeap[i] = Heap[i];
	}
	//Add the first element to the tree. This is the root node
	Heap[1] = tempHeap[1];
	int LoopLim = size+1;
	size = 1;
	for (int i = 2; i < LoopLim; i++)
	{
		//Add a node to the end, and then compare it to the parent
		Enqueue(tempHeap[i]);
	}
}

AITask* AIScheduler::Dequeue()
{
	//Take the top node off, put the last element at the top, and then swap it all
	//The way down with the largest child until it is larger than the childs
	
	AITask* tempNode = Heap[1]; // this is what we will return
	
	Heap[1] = Heap[size];
	int Swap = 1;
	int childPriority;
	
	
	if (Heap[Swap*2]->getPriority() > Heap[Swap*2+1]->getPriority() )
	{
		childPriority = Heap[Swap*2]->getPriority();
		Heap[Swap] = Heap[Swap*2];
		//NOTE: MIKEY HARD CODED FOR 3 TREE
		Heap[Swap*2] = Heap[Swap*2+1];
		Swap = Swap*2;
	}
	else
	{
		childPriority = Heap[Swap*2+1]->getPriority();
		Heap[Swap] = Heap[Swap*2+1];
		Swap = Swap*2+1;
	}
	
	//MIKEY HARD CODED FOR 3 TREE
	
	/*while (Heap[Swap]->getPriority() < childPriority)
	{
		//printf("%i, Priority:%i", Swap, childPriority);
		//fflush(stdout);
		//Swap with child
		AITask* swapNode = Heap[Swap];
		if (Heap[Swap*2]->getPriority() > Heap[Swap*2+1]->getPriority() )
		{
			Heap[Swap] = Heap[Swap*2];
			Heap[Swap*2] = swapNode;
			Swap = Swap*2;
		}
		else
		{
			Heap[Swap] = Heap[Swap*2+1];
			Heap[Swap*2+1] = swapNode;
			Swap = Swap*2+1;
		}
				
	}*/
	
	size--;
	
	return tempNode;
			
}
			
int AIScheduler::Enqueue(AITask* newNode)
{
	//Put it at the end, and then swap if its larger than the parent
	//printf("Size %i", size);
	//fflush(stdout);
	size++;
	assert(size < NUM_TASKS+1);
	Heap[size] = newNode;
	
	//printf("Crashing here?");
	//fflush(stdout);
	
	int Swap = size;
	//printf("%i", Swap);
	//fflush(stdout);
	if ((Swap > 1) && (Heap[Swap]->getPriority() > Heap[Swap / 2] ->getPriority()))
	{
		AITask* tempNode = Heap[Swap];
		Heap[Swap] = Heap[Swap / 2];
		Heap[Swap / 2] = tempNode;
	}
	/*
	while ((Swap > 1) && (Heap[Swap]->getPriority() > Heap[Swap / 2] ->getPriority()) )
	{
		AITask* tempNode = Heap[Swap];
		Heap[Swap] = Heap[Swap / 2];
		Heap[Swap / 2] = tempNode;
		Swap = Swap / 2;
		printf("%i", Swap);
		fflush(stdout);
	}*/
	return 1;
}





