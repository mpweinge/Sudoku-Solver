/*
 *  SudokuSquare.cpp
 *  
 *
 *  Created by Michael Weingert on 12-01-03.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SudokuSquare.h"
#include "Constants.h"

SudokuSquare::SudokuSquare (int numSquares)
{
	for(int i = 1; i < numSquares+1; i++)
		potNum.push_back(i);
	Num = -1;
}

SudokuSquare::SudokuSquare()
{
	for(int i = 1; i < NUM_SQUARES+1; i++)
		potNum.push_back(i);
	Num = -1;
}

SudokuSquare::~SudokuSquare() 
{
	potNum.clear();
}

void SudokuSquare::setNum(unsigned int num)
{
	Num = num;
}

void SudokuSquare::remove(int num)
{
	for (int i = 0 ; i < potNum.size(); i++)
	{
		if (potNum[i] == num)
		{
			potNum.erase(potNum.begin()+i);
			//potNum[i] = potNum[potNum.size()];
			//potNum.pop_back();
			//printf("Nums Left %i", (int)(potNum.size()));
			break;
		}
	}
}

int SudokuSquare::getNum()
{
	return Num;
}

int SudokuSquare::getNumSizeLeft()
{
	return potNum.size();
}

std::vector<int>* SudokuSquare::getNumsLeft()
{
	return &potNum;
}

int SudokuSquare::getFirstNum()
{
	return potNum[0];
}
