/*
 *  SudokuGrid.cpp
 *  
 *
 *  Created by Michael Weingert on 12-01-03.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SudokuGrid.h"
#include "SudokuSquare.h"
#include "Constants.h"
#include "ObjectCWrapper.h"
//#include "Assert.h"

#include <vector>

static SudokuGrid* theInstance;

SudokuGrid* SudokuGrid::GetInstance()
{
	if (theInstance == NULL)
		theInstance = new SudokuGrid(NUM_SQUARES);
	return theInstance;
}

void SudokuGrid::SetInstance(SudokuGrid* NewGrid)
{
	delete theInstance; // should already be stored somewhere
	theInstance = NewGrid;
}

SudokuGrid::SudokuGrid()
{
	numUnsolvedSquares = 81;
}

SudokuGrid::SudokuGrid(int numSquares)
{
	isSolved = false;
	numUnsolvedSquares = 81;
}

SudokuGrid::SudokuGrid(int numSquares, int NumUnsolvedSquares)
{
	isSolved = false;
	numUnsolvedSquares = NumUnsolvedSquares;
}

void SudokuGrid::SetObjCObject(void * objectiveCObject)
{
	objCObject = objectiveCObject;
}

void SudokuGrid::MoveNumsToObjC()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9 ; j++)
		{
			ObjCSetNum(objCObject, i, j, squareArray[i][j].getNum());
		}
	}
}

void SudokuGrid::PrintGrid()
{
	printf("--------------------------------------------------------\n");
	for (int i = 0 ; i < 9 ; i++)
	{
		for (int j = 0; j < 9 ; j++)
		{
			if ( (j %3 ) == 0)
				printf("|");
			printf(" %4i ", squareArray[i][j].getNum());
			if (j == 8)
				printf("|");
		}
		printf("\n");
		if ( ((i+1) / 3 ) >= 1 && (((i+1) % 3) == 0)) //i+1 because 0- indexed
			printf("--------------------------------------------------------\n");
	}
}

void SudokuGrid::CopyGrid(SudokuGrid* NewGrid)
{
	//Copy the array and store it in current node
	/*for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			NewGrid->SetNum(i,j, squareArray[i][j].getNum());
			//Need to copy the curr nums, etc
		}
	}*/
	*NewGrid = *this;
}

bool SudokuGrid::IsSolved()
{
	return isSolved;
}

int SudokuGrid::GetNumUnsolvedSquares()
{
	return numUnsolvedSquares;
}

int SudokuGrid::GetNum(int row, int col)
{
	//assert( (row < 9) && (col < 9) && (row >= 0) && (col >= 0) );
	return squareArray[row][col].getNum();
}

void SudokuGrid::SetNum(int row, int col, unsigned int num)
{
	//printf("Num: %i", num);
	//fflush(stdout);
	//assert( (num  / 10) < 1 num != -1);
	if (num != -1 && (squareArray[row][col].getNum() == -1))
	{
		squareArray[row][col].setNum(num);
		//printf("NumUnsolvedSquares:%i\n", numUnsolvedSquares);
		numUnsolvedSquares--;
		if (numUnsolvedSquares == 0)
		{
			isSolved = true;
			MoveNumsToObjC();
		}
		
	}
	else 
	{
		squareArray[row][col].setNum(num);
	}
}

std::vector<int>* SudokuGrid::GetNumsLeft(int row, int col)
{
	return squareArray[row][col].getNumsLeft();
}

int SudokuGrid::GetNumSizeLeft(int row, int col)
{
	return squareArray[row][col].getNumSizeLeft();
}

int SudokuGrid::GetFirstNum(int row, int col)
{
	return squareArray[row][col].getFirstNum();
}

void SudokuGrid::EliminateRow(int row, int num)
{
	for (int i = 0; i < 9; i++)
	{
		squareArray[row][i].remove(num); // check vector syntax
	}
}

void SudokuGrid::EliminateColumn(int column, int num)
{
	for (int i = 0; i < 9; i++)
	{
		squareArray[i][column].remove(num); // check vector syntax
	}
}

void SudokuGrid::EliminateBox(int row, int column, int num)
{
	//top left corner is equal to row / 3 (integer division)
	int toprow = (int)(row / 3) * 3;
	int topcol = (int)(column / 3) * 3;
	
	//iterate over all positions in the box
	squareArray[toprow][topcol].remove(num);
	squareArray[toprow+1][topcol].remove(num);
	squareArray[toprow+2][topcol].remove(num);
	
	squareArray[toprow][topcol+1].remove(num);
	squareArray[toprow+1][topcol+1].remove(num);
	squareArray[toprow+2][topcol+1].remove(num);
	
	squareArray[toprow][topcol+2].remove(num);
	squareArray[toprow+1][topcol+2].remove(num);
	squareArray[toprow+2][topcol+2].remove(num);
}

bool SudokuGrid::SearchRow(int row, int num)
{
	int matchCount; //note we will find the original number, so looking for count of 2
	matchCount = 0;
	
	for (int i = 0; i < 9; i++)
	{
		if (squareArray[row][i].getNum() == num) 
		{
			matchCount++;
			if (matchCount == 2)
			{
				//printf("Discovered in Row %i Search, num:%i", row, num);
				//PrintGrid();
				return true;
			}
		}
	}
	return false;
}

bool SudokuGrid::SearchColumn(int column, int num)
{
	int matchCount; //note we will find the original number, so looking for count of 2
	matchCount = 0;
	
	for (int i = 0; i < 9; i++)
	{
		if (squareArray[i][column].getNum() == num) 
		{
			matchCount++;
			if (matchCount == 2)
			{
				printf("Discovered in Col %i Search, num:%i %i", column, num, i);
				return true;
			}
		}
	}
	return false;
}

bool SudokuGrid::SearchBox(int row, int col, int num)
{	
	int matchCount;
	matchCount = 0;
	
	//need to map row, col into a top coordinate
	int toprow = (int)(row / 3) * 3;
	int topcol = (int)(col / 3) * 3;
	
	if (squareArray[toprow][topcol].getNum() == num)
		matchCount++;
	if (squareArray[toprow+1][topcol].getNum() == num)
		matchCount++;
	if(squareArray[toprow+2][topcol].getNum() == num) 
		matchCount++;	
	if(squareArray[toprow][topcol+1].getNum() == num) 
		matchCount++;
	if(squareArray[toprow+1][topcol+1].getNum() == num) 
		matchCount++;
	if(squareArray[toprow+2][topcol+1].getNum() == num) 
		matchCount++;	
	if(squareArray[toprow][topcol+2].getNum() == num)
		matchCount++;
	if(squareArray[toprow+1][topcol+2].getNum() == num )
		matchCount++;
	if(squareArray[toprow+2][topcol+2].getNum() == num )
		matchCount++;
	
	if (matchCount >= 2)
	{
		printf("Discovered in box search Pos:%i,%i, Num: %i", row, col, num);
		return true;
	}
	
	return false;
		
}