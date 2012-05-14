Sudoku-Solver
=============

This project solves sudoku puzzles by using a guessing tree. It does some basic filtering using the rules that each number can only appear once in a row, column, and box. If the engine gets stuck, it will make a guess. It will continue down that guess path until it discovers an error (two identical numbers in the same row / column / box). At this point it will back track up the guess tree to the next possible branch. 

It can solve every sudoku puzzle (even non-deterministic ones) in a relatively short time. 

The engine is written in c++ and the front end is written in objective c ( / cocoa).