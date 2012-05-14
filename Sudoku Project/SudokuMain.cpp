/*
 *  SudokuMain.cpp
 *  
 *
 *  Created by Michael Weingert on 12-01-03.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SudokuMain.h"

int runmain()
{	
	/*for (int i= 0 ; i < 8; i++)
	 {
	 SudokuGrid::GetInstance()->SetNum(0, i, (unsigned int)(i+1));
	 }
	 
	 SudokuGrid::GetInstance()->SetNum(1, 0, 4);
	 SudokuGrid::GetInstance()->SetNum(1, 1, 5);
	 SudokuGrid::GetInstance()->SetNum(1, 2, 6);
	 SudokuGrid::GetInstance()->SetNum(2, 0, 7);
	 SudokuGrid::GetInstance()->SetNum(2, 1, 8);
	 
	 SudokuGrid::GetInstance()->SetNum(1, 3, 9);
	 SudokuGrid::GetInstance()->SetNum(1, 5, 8);*/
	
	//Puzzle One test (easy)
	/*
	 SudokuGrid::GetInstance()->SetNum(0, 0, 7);
	 SudokuGrid::GetInstance()->SetNum(0, 1, 9);
	 SudokuGrid::GetInstance()->SetNum(2, 0, 8);
	 
	 SudokuGrid::GetInstance()->SetNum(1, 5, 6);
	 SudokuGrid::GetInstance()->SetNum(2, 4, 3);
	 
	 SudokuGrid::GetInstance()->SetNum(0, 6, 3);
	 SudokuGrid::GetInstance()->SetNum(1, 6, 9);
	 
	 SudokuGrid::GetInstance()->SetNum(2, 7, 7);
	 SudokuGrid::GetInstance()->SetNum(2, 8, 6);
	 
	 SudokuGrid::GetInstance()->SetNum(5, 0, 4);
	 SudokuGrid::GetInstance()->SetNum(4, 2, 5);
	 
	 SudokuGrid::GetInstance()->SetNum(3, 5, 5);
	 SudokuGrid::GetInstance()->SetNum(4, 3, 4);
	 SudokuGrid::GetInstance()->SetNum(4, 4, 1);
	 SudokuGrid::GetInstance()->SetNum(4, 5, 8);
	 SudokuGrid::GetInstance()->SetNum(5, 3, 7);
	 SudokuGrid::GetInstance()->SetNum(4, 6, 7);
	 SudokuGrid::GetInstance()->SetNum(3, 8, 2);
	 
	 SudokuGrid::GetInstance()->SetNum(6, 0, 6);
	 SudokuGrid::GetInstance()->SetNum(6, 1, 1);
	 SudokuGrid::GetInstance()->SetNum(7, 2, 2);
	 SudokuGrid::GetInstance()->SetNum(8, 2, 9);
	 
	 SudokuGrid::GetInstance()->SetNum(7, 3, 3);
	 SudokuGrid::GetInstance()->SetNum(6, 4, 9);
	 SudokuGrid::GetInstance()->SetNum(6, 8, 8);
	 SudokuGrid::GetInstance()->SetNum(8, 7, 5);
	 SudokuGrid::GetInstance()->SetNum(8, 8, 4);
	 */
	
	//Puzzle Two: Hard
	/*
	 SudokuGrid::GetInstance()->SetNum(0, 2, 2);
	 SudokuGrid::GetInstance()->SetNum(1, 1, 9);
	 SudokuGrid::GetInstance()->SetNum(1, 2, 8);
	 SudokuGrid::GetInstance()->SetNum(2, 0, 6);
	 SudokuGrid::GetInstance()->SetNum(2, 1, 7);
	 
	 SudokuGrid::GetInstance()->SetNum(2, 3, 4);
	 SudokuGrid::GetInstance()->SetNum(1, 4, 5);
	 SudokuGrid::GetInstance()->SetNum(0, 4, 3);
	 SudokuGrid::GetInstance()->SetNum(2, 8, 2);
	 
	 SudokuGrid::GetInstance()->SetNum(3, 1, 1);
	 SudokuGrid::GetInstance()->SetNum(4, 0, 9);
	 SudokuGrid::GetInstance()->SetNum(3, 5, 3);
	 SudokuGrid::GetInstance()->SetNum(5, 4, 7);
	 SudokuGrid::GetInstance()->SetNum(5, 7, 8);
	 SudokuGrid::GetInstance()->SetNum(4, 7, 2);
	 SudokuGrid::GetInstance()->SetNum(4, 8, 5);
	 
	 SudokuGrid::GetInstance()->SetNum(8, 0, 4);
	 SudokuGrid::GetInstance()->SetNum(8, 3, 2);
	 SudokuGrid::GetInstance()->SetNum(6, 5, 6);
	 SudokuGrid::GetInstance()->SetNum(7, 5, 1);
	 SudokuGrid::GetInstance()->SetNum(6, 6, 2);
	 SudokuGrid::GetInstance()->SetNum(7, 6, 8);
	 SudokuGrid::GetInstance()->SetNum(6, 7, 9);
	 SudokuGrid::GetInstance()->SetNum(8, 7, 6);
	 SudokuGrid::GetInstance()->SetNum(8, 8, 3);
	 */
	
	//Puzzle Three: Extreme
	SudokuGrid::GetInstance()->SetNum(1, 0, 9);
	SudokuGrid::GetInstance()->SetNum(1, 2, 5);
	SudokuGrid::GetInstance()->SetNum(2, 2, 7);
	SudokuGrid::GetInstance()->SetNum(0, 4, 4);
	SudokuGrid::GetInstance()->SetNum(0, 8, 1);
	SudokuGrid::GetInstance()->SetNum(1, 7, 6);
	
	SudokuGrid::GetInstance()->SetNum(4, 1, 7);
	SudokuGrid::GetInstance()->SetNum(3, 4, 1);
	SudokuGrid::GetInstance()->SetNum(3, 5, 8);
	SudokuGrid::GetInstance()->SetNum(4, 4, 2);
	SudokuGrid::GetInstance()->SetNum(5, 2, 4);
	SudokuGrid::GetInstance()->SetNum(5, 6, 5);
	SudokuGrid::GetInstance()->SetNum(8, 1, 1);
	SudokuGrid::GetInstance()->SetNum(6, 3, 5);
	SudokuGrid::GetInstance()->SetNum(7, 3, 9);
	SudokuGrid::GetInstance()->SetNum(7, 6, 7);
	SudokuGrid::GetInstance()->SetNum(8, 8, 2);
	
	SudokuGrid::GetInstance()->PrintGrid();
	
	//theGrid.Search();
	
	SudokuAI::GetInstance()->AIMain();
	
	SudokuGrid::GetInstance()->PrintGrid();
	
	return 0;
	
}