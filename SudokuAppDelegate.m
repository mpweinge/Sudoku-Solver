//
//  SudokuAppDelegate.m
//  Sudoku
//
//  Created by Michael Weingert on 12-01-13.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SudokuAppDelegate.h"
#include <ctype.h>

@implementation SudokuAppDelegate

@synthesize SudokuWindow;

@synthesize window;

static SudokuAppDelegate* m_Instance = NULL;

- (id)init
{
	[super init];
	return self;
}

+ (SudokuAppDelegate *) getInstance
{
	if (m_Instance = NULL)
		m_Instance = [[self alloc] init];
	
	return m_Instance;
}

- (void) setNum:(int)row :(int)col :(int)num
{
	[[SudokuWindow cellAtRow:row column:col]setIntValue:num];
}

-(IBAction) buttonClicked:(NSButton* )sender {
	[[SudokuWrapper getInstance] Solve];
}

-(IBAction) textFieldChanged:(NSTextField*)sender {
}

-(IBAction) textFieldChanged2:(NSMatrix*)sender {
	if ([[SudokuWindow cellAtRow:8 column:8]tag] == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			[[SudokuWindow cellAtRow:0 column:i]setTag:i];
			[[SudokuWindow cellAtRow:1 column:i]setTag:(10+i)];
			[[SudokuWindow cellAtRow:2 column:i]setTag:(20+i)];
			[[SudokuWindow cellAtRow:3 column:i]setTag:(30+i)];
			[[SudokuWindow cellAtRow:4 column:i]setTag:(40+i)];
			[[SudokuWindow cellAtRow:5 column:i]setTag:(50+i)];
			[[SudokuWindow cellAtRow:6 column:i]setTag:(60+i)];
			[[SudokuWindow cellAtRow:7 column:i]setTag:(70+i)];
			[[SudokuWindow cellAtRow:8 column:i]setTag:(80+i)];
		}
		
		[[SudokuWrapper getInstance] setObjectiveCObject: SudokuWindow];
	}
	
	//NSLog( @"oh lerdy");
	id theCell = [sender selectedCell];
	int theTag = [theCell tag];
	//NSLog( @"Tag %i", theTag );
	
	NSString* string = [sender stringValue];
	//if (intVal)
	if ([string intValue])
	{
	//	NSLog( @"Num %i", [string intValue]);
		[[SudokuWrapper getInstance] SetSquareNum:(int)(theTag/10):(int)(theTag%10):[string intValue]];
		[[SudokuWrapper getInstance] RunMain];
	}

	else {
	//	NSLog( @"String %s", string );
	}

}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application 
}

@end
