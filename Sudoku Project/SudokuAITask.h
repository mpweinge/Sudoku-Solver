/*
 *  SudokuAITask.h
 *  
 *
 *  Created by Michael Weingert on 12-01-12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SUDOKUAITTASK_H
#define SUDOKUAITTASK_H

#include "SudokuAIScheduler.h"
#include "SudokuGuess.h"

class SweepTask: public AITask
{
public:
	SweepTask(int _priority);
	virtual void main();
	virtual void updatePriority(int environmentvariable);
	virtual int getPriority() { return priority; };
private:
	~SweepTask(void){};
	int priority;
	
};

class BoxTask: public AITask
{
public:
	BoxTask(int _priority);
	virtual void main();
	virtual void updatePriority(int environmentvariable);
	virtual int getPriority() { return priority; };
private:
	~BoxTask(void){};
	int FrequencyTable[9][3];
	int priority;
	void SearchSquare(int left, int top);
};

class GuessTask: public AITask
{
public:
	GuessTask(int _priority);
	virtual void main();
	virtual void updatePriority(int environmentvariable);
	virtual int getPriority() { return priority; };
private:
	~GuessTask(void){};
	int priority;
	GuessTree* Guess;
};

#endif