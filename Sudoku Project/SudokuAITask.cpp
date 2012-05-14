/*
 *  SudokuAITask.cpp
 *  
 *
 *  Created by Michael Weingert on 12-01-12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SudokuAITask.h"
#include "SudokuGuess.h"
#include "SudokuGrid.h"
#include "SudokuAI.h"

bool bSweepRan;
bool bBoxRan;
bool bGuessRan;

SweepTask::SweepTask(int _priority)
{
	bGuessRan = true;
	bSweepRan = true;
	bBoxRan = true;
	priority = _priority;
}

void SweepTask::main()
{
	bSweepRan = false;
	//printf("Sweep Main");
	//fflush(stdout);
	
	//int newNumber;
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
				AIScheduler::getInstance()->newNumber = 1; //-> Need to signal the scheduler here
				//printf("in SWEEP: Discovered %i at %i,%i\n", currNum, i, j);
				//fflush(stdout);
				bSweepRan = true;
				bBoxRan = true;
				
				SudokuGrid::GetInstance()->EliminateRow(i, currNum);
				//eliminate from column
				SudokuGrid::GetInstance()->EliminateColumn(j, currNum);
				//eliminate from inside box
				SudokuGrid::GetInstance()->EliminateBox(i, j, currNum);
			}
			
		}
	}
	
	if (!bBoxRan && !bSweepRan)
	{
		//printf("Guess should be next ... ");
		//fflush(stdout);
		updatePriority(0);
		AIScheduler::getInstance()->UpdateAllPriorities(0); 
	}
	else 
	{
		// so re-heap is called
		updatePriority(1);
		AIScheduler::getInstance()->UpdateAllPriorities(1); 
	}
}

void SweepTask::updatePriority(int envvar)
{
	//This environmental variable is whether a number has been discovered recently
	//will be binary (1 vs 0)
	priority = bSweepRan? envvar*2 : (bGuessRan? envvar:0);
	//printf("Updating Sweep Priority %i", priority);
	//fflush(stdout);
}

BoxTask::BoxTask(int _priority)
{
	priority = _priority;
}

void BoxTask::main()
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
	bBoxRan = false;
	//printf("\nBox Main\n");
	//fflush(stdout);
	
	
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
				bBoxRan = true;
				bSweepRan = true;
				
		//		printf("in BOXSCAN: Discovered %i at %i,%i\n", currNum, left, top);
		//		fflush(stdout);
				SudokuGrid::GetInstance()->EliminateRow(left, currNum);
				//eliminate from column
				SudokuGrid::GetInstance()->EliminateColumn(top, currNum);
				//eliminate from inside box
				SudokuGrid::GetInstance()->EliminateBox(left, top, currNum);
			}
		}
	}
	
	if (!bBoxRan && !bSweepRan)
	{
		//printf("Guess should go next ...");
		//fflush(stdout);
		updatePriority(0);
		AIScheduler::getInstance()->UpdateAllPriorities(0); 
	}
	else 
	{
		// so re-heap is called
		updatePriority(1);
		AIScheduler::getInstance()->UpdateAllPriorities(1); 
	}

}

void BoxTask::SearchSquare(int left, int top)
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

void BoxTask::updatePriority(int envvar)
{
	//This environmental variable is whether a number has been discovered recently
	//will be binary (1 vs 0)
	priority = bBoxRan? envvar*2 : (bGuessRan? envvar:0);
	//printf("Updating Box Priority %i", priority);
	//fflush(stdout);
}

GuessTask::GuessTask(int _priority)
{
	priority = _priority;
	Guess = new GuessTree();
	Guess->InitializeTree();
}

void GuessTask::updatePriority(int _priority)
{
	//printf("Priority: %i", priority);
	//fflush(stdout);
	priority = bBoxRan? 0 : (bSweepRan? 0 : 10); // 10 = arbitrary high number
	//printf("Priority: %i", priority);
	//fflush(stdout);
}

void GuessTask::main()
{
	bGuessRan = true;
	if (! (Guess->ValidateGuess())) //need to make a guess
	{
		bBoxRan = true;
		bSweepRan = true;
		updatePriority(1);
		AIScheduler::getInstance()->UpdateAllPriorities(1); 
	}
	else 
	{
		Guess->MakeAGuess();
		bBoxRan = true;
		bSweepRan = true;
		updatePriority(1);
		AIScheduler::getInstance()->UpdateAllPriorities(1);
	}

}
