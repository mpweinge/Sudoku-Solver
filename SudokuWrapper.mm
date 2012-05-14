//
//  SudokuWrapper.mm
//  Sudoku
//
//  Created by Michael Weingert on 12-01-18.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SudokuWrapper.h"
//#import "SudokuAppDelegate.h"
#include "./Sudoku Project/SudokuGrid.h"
#include "./Sudoku Project/SudokuAI.h"

//C++ class
class CImplement
{
public:
	CImplement(void)
	{
		
	}
	
	void SetSquare(int row, int col, int num)
	{
		SudokuGrid::GetInstance()->SetNum(row, col, num);
	}
	
	void RunMain()
	{
		SudokuGrid::GetInstance()->PrintGrid();
		//SudokuAI::GetInstance()->AIMain();
		//SudokuGrid::GetInstance()->PrintGrid();
	}
	
	void Solve()
	{
		SudokuAI::GetInstance()->AIMain();
		SudokuGrid::GetInstance()->PrintGrid();
	}
	
	void SetObjectiveCObject(void * Obj)
	{
		SudokuGrid::GetInstance()->SetObjCObject(Obj);
	}
};

@implementation SudokuWrapper

//@synthesize SudokuWindow2;

static SudokuWrapper* m_Instance;

- (id)init
{
	[super init];
	mImplement = new CImplement;
	mImplement->RunMain();
	return self;
}

+ (SudokuWrapper *) getInstance
{
	if (m_Instance == NULL)
		m_Instance = [[self alloc] init];
	
	return m_Instance;
}

- (void) SetSquareNum:(int)Row :(int)Col :(int)Num
{
	mImplement->SetSquare(Row, Col, Num);
}

- (void) RunMain
{
	mImplement->RunMain();
}

- (void) setObjectiveCObject: (id)Obj
{
	mImplement->SetObjectiveCObject(Obj);
	SudokuWindow3 = Obj;
}

- (void) Solve
{
	mImplement->Solve();
}

- (void) setNum:(int)row :(int)col :(int)num
{
	if (SudokuWindow3 == NULL)
	{
		int k;
		k = 0;
	}
	[[SudokuWindow3 cellAtRow:row column:col]setIntValue:num];
}

void ObjCSetNum(void * useless, int row, int col, int num)
{
	[[SudokuWrapper getInstance] setNum:row:col:num];
}
@end
