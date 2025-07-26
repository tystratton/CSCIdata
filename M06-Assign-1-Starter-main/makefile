all: burger main 
main: main.cpp burger
	g++ -pedantic-errors -g main.cpp burger -o main
burger: burger.h burger.cpp set.h AVLTree.h binarySearchTree.h binaryTree.h
	g++ -pedantic-errors -g -c burger.cpp -o burger
