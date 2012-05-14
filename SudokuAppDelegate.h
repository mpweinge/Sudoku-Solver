//
//  SudokuAppDelegate.h
//  Sudoku
//
//  Created by Michael Weingert on 12-01-13.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "SudokuWrapper.h"

@interface SudokuAppDelegate : NSObject <NSApplicationDelegate> 
{
	NSWindow *window;
	NSMatrix *SudokuWindow;
	SudokuAppDelegate* m_Instance;
}

-(id)init;

-(void) setNum:(int)row:(int)col:(int)num;

+(SudokuAppDelegate*) getInstance;

@property (assign) IBOutlet NSMatrix* SudokuWindow;

@property (assign) IBOutlet NSWindow *window;
- (IBAction) textFieldChanged2:(NSMatrix*)sender;
- (IBAction) buttonClicked:(NSButton *)sender;
- (IBAction) textFieldChanged:(NSTextField* )sender;
@end