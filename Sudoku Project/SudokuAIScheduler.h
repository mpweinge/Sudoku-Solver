/*
 *  SudokuAISheduler.h
 *  
 *
 *  Created by Michael Weingert on 12-01-08.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SUDOKUAISCHEDULER_H
#define SUDOKUAISCHEDULER_H

#include "Constants.h"

class AITask // for purpose of implementing the priority queue, general priority task
{
public:
	AITask() {};
	~AITask(){};
	virtual void main() {}; // function pointer to the main of the AI task
	virtual void updatePriority(int environmentvariable/*,  ... */) {};
	virtual int getPriority() { return -1; };
	
	//scheduler will be implemented as a heap (priority queue)
	//priorities will be set by the update priority method (minimum one input parameter)
	//The heapify function will call the getPriority method to re-heap
};

class AIScheduler
{
public:
	static AIScheduler* getInstance();
	void UpdateAllPriorities(int environmentvariable/*, ...*/); // will call re-heapify
	AITask* Dequeue();
	int Enqueue(AITask* newTask);
	int newNumber;
	int EnvVar;
	
private:
	AIScheduler();
	void ReHeapify();
	void PrintTree();
	AITask* Heap[NUM_TASKS+1];
	int size;
};

#endif

