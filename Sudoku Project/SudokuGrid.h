/*
 *  SudokuGrid.h
 *  
 *
 *  Created by Michael Weingert on 12-01-03.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include "SudokuSquare.h"
#include "Constants.h"

typedef class SudokuGrid
{
	
	SudokuSquare squareArray[NUM_SQUARES][NUM_SQUARES];
	bool isSolved;
	int numUnsolvedSquares;
	
public:
	void PrintGrid();
	int GetNum(int row, int col);
	void SetNum(int row, int col, unsigned int num);
	
	void MoveNumsToObjC();
	
	static SudokuGrid* GetInstance();
	static void SetInstance(SudokuGrid* NewGrid);
	
	void SetObjCObject(void * objectiveCObject);

	void EliminateRow(int row, int num);
	void EliminateColumn(int column, int num);
	void EliminateBox(int column, int row, int num);

	bool SearchRow(int row, int num);
	bool SearchColumn(int column, int num);
	bool SearchBox(int row, int col, int num);
	
	int GetFirstNum(int row, int col);
	std::vector<int>* GetNumsLeft(int row, int col);
	int GetNumSizeLeft(int row, int col);
	int GetNumUnsolvedSquares();
	
	SudokuGrid(int numSquares);
	SudokuGrid(int numSquares, int NumUnsolvedSquares);
	SudokuGrid();
	
	void CopyGrid(SudokuGrid* NewGrid);
	
	bool IsSolved();
	
private:
	void * objCObject;
};

#endif