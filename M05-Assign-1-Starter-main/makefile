all: product.o main
main: main.cpp product.o binarySearchTree.h binaryTree.h
	g++ -pedantic-errors -g main.cpp product.o -o main
product.o: product.h product.cpp
	g++ -pedantic-errors -c -g product.cpp -o product.o