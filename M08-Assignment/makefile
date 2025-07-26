all: block.o main
main: main.cpp block.o block.h
	g++ -pedantic-errors -g main.cpp block.o -o main
block.o: block.h block.cpp
	g++ -pedantic-errors -c -g block.cpp -o block.o 