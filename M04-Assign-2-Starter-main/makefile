all: product.o main
main: main.cpp product.o linkedList.h unorderedLinkedList.h linkedListIterator.h
	g++ -pedantic-errors -g main.cpp product.o -o main
product.o: product.h product.cpp
	g++ -pedantic-errors -c -g product.cpp -o product.o