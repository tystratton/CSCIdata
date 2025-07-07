all: sudoku.o
	g++ -pedantic-errors main.cpp sudoku.o -g -o main
sudoku.o: sudoku.h sudoku.cpp
	g++ -pedantic-errors sudoku.cpp -g -o sudoku.o -c
