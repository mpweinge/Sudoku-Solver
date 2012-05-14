/*
 *  SudokuAI.cpp
 *  
 *
 *  Created by Michael Weingert on 12-01-06.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SudokuAI.h"
#include "SudokuGuess.h"
#include <vector>
#include "SudokuAIScheduler.h"
#include "SudokuAITask.h"

#include "stdio.h"

#define SCHEDULER

static SudokuAI* theInstance;

int newNumber;

SudokuAI* SudokuAI::GetInstance()
{
	if (theInstance	== NULL)
		theInstance = new SudokuAI();
	return theInstance;
}

SudokuAI::SudokuAI()
{
	;
}

void SudokuAI::AIMain()
{
	//Eliminate Numbers
	
	//First item is to search for solved numbers in the sudoku puzzle
	//If we find a number, call eliminate row and eliminate column, and eliminate square
	
	//If there is only one possible number for a location, it is solved
	//If a number can only go in one location in a square, it is solved 
	
	EliminateNumbers();
	//Search for rows missing one number, 
	
#ifndef SCHEDULER
	newNumber = 1;
	while (newNumber)
	{
		newNumber = 0;
		SweepFind();
		//or when you can eliminate all but one number from a square
		BoxScan();
	}
	
	GuessTree * Guess = new GuessTree();
	Guess->InitializeTree();
	
	bool bValGuess;
	bValGuess = true;
	
	//while(! (SudokuGrid::GetInstance()->IsSolved()))
	while( (!(SudokuGrid::GetInstance()->IsSolved())) /*&&bValGuess*/)
	{
		//Time to start making guesses
		if (bValGuess)
			Guess->MakeAGuess();
		
		newNumber = 1;
		while (newNumber)
		{
			newNumber = 0;
			SweepFind();
			//or when you can eliminate all but one number from a square
			BoxScan();
		}
		
		// we got a bad guess
		bValGuess = Guess->ValidateGuess();
		if ( !bValGuess )
		{
			newNumber = 1;
			while (newNumber)
			{
				newNumber = 0;
				SweepFind();
				//or when you can eliminate all but one number from a square
				BoxScan();
			}
		}
		
	}
#else
	//Create the AITasks
	SweepTask* Sweep = new SweepTask(1);
	BoxTask* Box = new BoxTask(1);
	GuessTask* Guess = new GuessTask(0);
	
	AIScheduler::getInstance()->Enqueue(Sweep);
	AIScheduler::getInstance()->Enqueue(Box);
	AIScheduler::getInstance()->Enqueue(Guess);
	
	//AISched->PrintTree();
	
	AITask* currTask; 
	
	while(!(SudokuGrid::GetInstance()->IsSolved()) )
	//for (int i = 0; i < 60; i++)
	{
		currTask = AIScheduler::getInstance()->Dequeue();
		currTask->main();
		AIScheduler::getInstance()->Enqueue(currTask);
		//printf("Loop once");
		//fflush(stdout);
	}
	
	
	
#endif
	
	//Guess->ValidateGuess();
	
	//while (SudokuGrid::GetInstance()->
	
	// this is the first stage of elimination, and the easiest one
	// the second stage involves the doubles pattern and more advanced maneuvers
}

void SudokuAI::EliminateNumbers()
{
	int currNum;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			currNum = SudokuGrid::GetInstance()->GetNum(i,j);
			if (currNum != -1) // because -1 is initial
			{
				//we got a bite
				//eliminate from the row
				printf("Discovered %i at %i,%i\n", currNum, i, j);
				newNumber = 1;
				SudokuGrid::GetInstance()->EliminateRow(i, currNum);
				//eliminate from column
				SudokuGrid::GetInstance()->EliminateColumn(j, currNum);
				//eliminate from inside box
				SudokuGrid::GetInstance()->EliminateBox(i, j, currNum);
			}
			
		}
	}	
}

void SudokuAI::SweepFind()
{
	//Do a sweep to see if there is anything squares left with just one potential number
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9 ; j++)
		{
			if (SudokuGrid::GetInstance()->GetNum(i,j) == -1 && SudokuGrid::GetInstance()->GetNumSizeLeft(i,j) == 1)
			{
				int currNum = SudokuGrid::GetInstance()->GetFirstNum(i,j);
				SudokuGrid::GetInstance()->SetNum(i, j, currNum);
				//we got a bite
				//eliminate from the row
				newNumber = 1;
				//printf("in SWEEP: Discovered %i at %i,%i\n", currNum, i, j);
				SudokuGrid::GetInstance()->EliminateRow(i, currNum);
				//eliminate from column
				SudokuGrid::GetInstance()->EliminateColumn(j, currNum);
				//eliminate from inside box
				SudokuGrid::GetInstance()->EliminateBox(i, j, currNum);
			}
			
		}
	}
}

void SudokuAI::BoxScan()
{
	//In order to do this, create a frequency table for numbers, 
	//We want to know if there are elements with only one possible spot
	//Iterate over each box, and record squares and stuff
	
	//There are 9 boxes, in this position 
	//  0   1   2 
	//  3   4   5
	//  6   7   8
	
	// We will create a frequency table in this shape
	// Frequency, position (x), position(y)
	// If at the end of the scanning, any of the elements have frequency one,
	// The number in the box (see above shape) is equal to taht element
	
	
	
	// Iterating over boxes, top left position is box is [ (i % 3) * 3, (i / 3) * 3 ]
	for (int i = 0 ; i < 9 ; i++)
	{
		//Reset the Frequency Table
		
		for (int j= 0; j < 9; j++)
		{
			FrequencyTable[j][0] = 0;
			FrequencyTable[j][1] = 0;
			FrequencyTable[j][2] = 0;
		}
		
		int left = (int)(i % 3) * 3;
		int top = (int)(i / 3) * 3;
		
		SearchSquare(left, top);
		SearchSquare(left+1, top);
		SearchSquare(left+2, top);
		
		top++;
		
		SearchSquare(left, top);
		SearchSquare(left+1, top);
		SearchSquare(left+2, top);
		
		top++;
		
		SearchSquare(left, top);
		SearchSquare(left+1, top);
		SearchSquare(left+2, top);
		
		//See if any of the items in the frequency table are at 1
		/*printf("FrequencyTable: ");
		for (int j = 0 ; j < 9 ; j++)
		{
			printf("%i POS:%i,%i ", FrequencyTable[j][0], FrequencyTable[j][1], FrequencyTable[j][2]);
		}
		printf("\n");*/
		
		for (int j = 0; j < 9; j++)
		{
			if (FrequencyTable[j][0] == 1) // we got a bite
			{
				int left = FrequencyTable[j][1];
				int top = FrequencyTable[j][2];
				int currNum = j;
				SudokuGrid::GetInstance()->SetNum(left, top, currNum); // set that num
				//eliminate from the row
				//printf("in BOXSCAN: Discovered %i at %i,%i\n", currNum, left, top);
				SudokuGrid::GetInstance()->EliminateRow(left, currNum);
				//eliminate from column
				SudokuGrid::GetInstance()->EliminateColumn(top, currNum);
				//eliminate from inside box
				SudokuGrid::GetInstance()->EliminateBox(left, top, currNum);
			}
		}
	}
}

void SudokuAI::SearchSquare(int left, int top)
{
	if (SudokuGrid::GetInstance()->GetNum(left, top) == -1)
	{
		std::vector<int>* nums = SudokuGrid::GetInstance()->GetNumsLeft(left, top);
		for (int i = 0; i < (*nums).size(); i++)
		{
			FrequencyTable[(*nums)[i]][0]++;
			FrequencyTable[(*nums)[i]][1] = left;
			FrequencyTable[(*nums)[i]][2] = top;
		}
	}
}

void SudokuAI::IdentifyTwoDependency()
{
	//The point of this is to search for when you have two numbers that can only be in two locations. 
	//When this happens, you can eliminate some potential numbers.
	
	/*
	 ie. 
	 | 1 2 3 | 4 5 6 | 7 8 9 |
	 |   5   |       |       |
	 | 7 8   |       | 4   6
	 ------------------------
	 It would normally be not possible to determine any numbers in the far left box
	 However, examining that in the middle row, 4 and 6 can only be in the two boxes
	 Even though 9 can be in any of the 3 available spots, it has to be in the bottom right
	 This is what I call elimination based off two number dependency.
	 
	 This theoretically exists for combinations of three, four, five, etc numbers, 
	 but this begins to become silly.
	 
	 This is an inter-box dependency
	 The same pattern can be established when the two numbers aren't in the same box, but in the same row or column
	 */
	
	/*
	 
	 In order to check for this, we will need to generate a frequency table to test in the box
	 If there are two numbers with a frequency of two, then we need to check if they have a cross dependency,
	 ie. if they are both rotating between the same two squares
	 We need to check for this cross dependency in a row, column, and within a box
	 So we will need, at any given point, three frequency tables
	 */
	
	/*Since we only need to record 2 set of coordinates 
	 The first entry will be the frequency, the second/third entry will be 1 coordinate
	 The fourth/fifth entry will be 2nd set of coordinates*/
	
	int FrequencyTableRow[9][5];
	int FrequencyTableCol[9][5];
	int FrequencyTableBox[9][5];
	
	//Clear the freq table first
	for (int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			FrequencyTableBox[i][j] = -1;
			FrequencyTableCol[i][j] = -1;
			FrequencyTableRow[i][j] = -1;
		}
	}
	
	//Do row and col first (i, k), (k, j)
	for (int i = 0 ; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{ 
			//need to modify search square
			if (SudokuGrid::GetInstance()->GetNum(i, j) == -1)
			{
				//Search square etc. add to all 3 freq tables
			}
		}
	}
}






