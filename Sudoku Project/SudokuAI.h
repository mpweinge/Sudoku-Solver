/*
 *  SudokuAI.h
 *  
 *
 *  Created by Michael Weingert on 12-01-06.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SudokuGrid.h"

class SudokuAI
{
public: 
	void AIMain();
	static SudokuAI* GetInstance();
private:
	SudokuAI();
	void EliminateNumbers();
	void SweepFind();
	void BoxScan();
	void IdentifyTwoDependency();
	int FrequencyTable[9][3];
	void SearchSquare(int left, int top);
};