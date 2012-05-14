//
//  SudokuWrapper.h
//  Sudoku
//
//  Created by Michael Weingert on 12-01-18.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ObjectCWrapper.h"

// declare c++ implementation for .mm (Obj-C++) files
#ifdef __cplusplus
class CImplement;
#endif

// declare c++ implementation for .m (Obj-C) files
#ifdef __OBJC__
#ifndef __cplusplus
typedef void CImplement;
#endif
#endif

@interface SudokuWrapper : NSObject <NSApplicationDelegate>{
	CImplement* mImplement;
	NSMatrix* SudokuWindow3;
}

//@property (assign) IBOutlet NSMatrix* SudokuWindow2;

+(SudokuWrapper*)getInstance;
- (id)init;
- (void)SetSquareNum: (int)Row:(int)Col:(int)Num;
- (void)RunMain;
- (void)setObjectiveCObject: (id)Obj;
- (void)Solve;

@end
