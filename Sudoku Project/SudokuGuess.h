/*
 *  SudokuGuess.h
 *  
 *
 *  Created by Michael Weingert on 12-01-09.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

//The implementation to make a guess
//Will create a n-tree where n is the lowest potential num in the grid

#ifndef SUDOKUGUESS_H
#define SUDOKUGUESS_H

#include "Constants.h"
#include "SudokuGrid.h"
#include <vector>

typedef struct GuessNode
{
	GuessNode* parent;
	int numChildren;
	std::vector<GuessNode*> Children;
	SudokuGrid* GuessGrid;
	int CurrentDepth;
	int posx; // the place we guessed when we branched
	int posy; // the place we guessed when we branched
	int currGuess; // for backtracking up the tree when we made a wrong guess
};

class GuessTree
{
	int numGuesses;	
	
public:
	void MakeAGuess();
	void InitializeTree();
	bool ValidateGuess();
	
private:
	GuessNode* root;
	GuessNode* currentNode;
};

#endif
