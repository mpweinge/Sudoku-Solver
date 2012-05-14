/*
 *  SudokuSquare.h
 *  
 *
 *  Created by Michael Weingert on 12-01-03.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

#include "Constants.h"
#include <vector>

typedef class SudokuSquare
{
	std::vector<int> potNum;
	int Num;
	
public:
	SudokuSquare(int);
	SudokuSquare();
	~SudokuSquare();
	void remove(int num);
	int getNum(void);
	void setNum(unsigned int);
	int getSize();
	int getFirstNum();
	std::vector<int>* getNumsLeft();
	int getNumSizeLeft(); 
	
} ;

#endif