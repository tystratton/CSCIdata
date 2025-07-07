all: main.o BugReport.o
	g++ main.o BugReport.o -o main

main.o: main.cpp BugReport.h priorityQueue.h unorderedLinkedList.h
	g++ -c main.cpp

BugReport.o: BugReport.cpp BugReport.h
	g++ -c BugReport.cpp

clean:
	rm *.o main
