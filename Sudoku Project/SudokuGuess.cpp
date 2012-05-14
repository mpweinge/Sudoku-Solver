/*
 *  SudokuGuess.cpp
 *  
 *
 *  Created by Michael Weingert on 12-01-09.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SudokuGuess.h"

void GuessTree::MakeAGuess()
{
	//First thing we need to do is store the current state
	int numChilds;
	int tempnum;
	tempnum = 0;
	numChilds = 9;
	
	//Now we need to find a square with only two numbers
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (SudokuGrid::GetInstance()->GetNum(i,j) == -1)
			{
				
				tempnum = SudokuGrid::GetInstance()->GetNumSizeLeft(i,j);
		
				if (tempnum < numChilds && tempnum != 0)
				{
					numChilds = tempnum;
					currentNode->posx = i;
					currentNode->posy = j;
				}
				
				
				if (tempnum == 2)
				{
					//we found a good one to guess
					//So now we need to store the current thing and break
					break;
				}
			}
		}
		if (tempnum == 2)
			break;
	}
	
	if (tempnum == 0)
	{
		SudokuGrid::GetInstance()->PrintGrid();
		int k;
		k = 0;
	}
	
	//SudokuGrid::GetInstance()->PrintGrid();
	
	printf("Making a guess at a square with %i numbers at (%i,%i), Depth:%i\n", tempnum, currentNode->posx, currentNode->posy, currentNode->CurrentDepth);
	fflush(stdout);
	
	//Copy the array and store it in current node
	currentNode->GuessGrid = new SudokuGrid(-1, SudokuGrid::GetInstance()->GetNumUnsolvedSquares());
	SudokuGrid::GetInstance()->CopyGrid(currentNode->GuessGrid);
	
	//printf("Failing here really?");
	//fflush(stdout);
	
	
	//So now we need to make child branches, one for each guess
	for (int i = 0; i < tempnum; i++)
	{
		GuessNode* child = new GuessNode();
		currentNode->Children.push_back(child);
		child->parent =currentNode;
		
		child->CurrentDepth = child->parent->CurrentDepth + 1;
		
		//Copy the array and store it in current node
		child->GuessGrid = new SudokuGrid(-1, SudokuGrid::GetInstance()->GetNumUnsolvedSquares());
		SudokuGrid::GetInstance()->CopyGrid(child->GuessGrid);
		
		
		//Set the guess
		int currNum = (*((SudokuGrid::GetInstance())->GetNumsLeft(currentNode->posx,currentNode->posy)))[i];
		child->GuessGrid->SetNum(currentNode->posx, currentNode->posy, 
								currNum);
		child->GuessGrid->EliminateRow(currentNode->posx, currNum);
		//eliminate from column
		child->GuessGrid->EliminateColumn(currentNode->posy, currNum);
		//eliminate from inside box
		child->GuessGrid->EliminateBox(currentNode->posx, currentNode->posy, currNum);
	}
	
	currentNode->numChildren = tempnum;
	currentNode->currGuess = 0;
	
	//Switch to the first guess to make it the current node
	currentNode = currentNode->Children[0];
	
	SudokuGrid::SetInstance(currentNode->GuessGrid);
	
	//SudokuGrid::GetInstance()->PrintGrid();
}

bool GuessTree::ValidateGuess()
{
	bool bIsBadGuess;
	bIsBadGuess = false;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0 ; j < 9; j++)
		{
			if (SudokuGrid::GetInstance()->GetNum(i,j) != -1)
			{
				if (
					SudokuGrid::GetInstance()->SearchRow(i, SudokuGrid::GetInstance()->GetNum(i,j)) ||
					SudokuGrid::GetInstance()->SearchColumn(j, SudokuGrid::GetInstance()->GetNum(i,j)) ||
					SudokuGrid::GetInstance()->SearchBox(i,j, SudokuGrid::GetInstance()->GetNum(i,j))
					)
				{
					//invalid guess, break, 
					bIsBadGuess = true;
					break;
				}
			}
			else 
			{
				if (SudokuGrid::GetInstance()->GetNumSizeLeft(i,j) == 0)
				{
					//hasnt been found yet, and 0 numbers can go there
					bIsBadGuess = true;
					break;
				}
			}

		}
		if (bIsBadGuess)
			break;
	}
	
	//if we got a bad guess, we need to pop up a level in the guess tree
	if (! bIsBadGuess)
		return true;
	
	printf("Oh lerdy, looks like we got a bad guess, Depth:%i\n", currentNode->CurrentDepth);
	fflush(stdout);
	
	currentNode = currentNode->parent;
	//currGuess starts index at 0
	//Traverse back up the tree
	while ( (currentNode->currGuess+1) == currentNode->numChildren)
	{
		currentNode = currentNode->parent;
	}
	
	currentNode->currGuess++;
	currentNode = currentNode->Children[currentNode->currGuess];
	
	//SudokuGrid::GetInstance()->PrintGrid();
	
	SudokuGrid::SetInstance(currentNode->GuessGrid);
	
	//SudokuGrid::GetInstance()->PrintGrid();
	
	return false;
	
}


void GuessTree::InitializeTree()
{
	GuessNode* RootNode = new GuessNode();
	root = RootNode;
	currentNode = root;
	root->parent == NULL;
	root->CurrentDepth = 0;
	
	//let the children and the square array be null for now
}
