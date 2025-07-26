/* Program name: graph.h
Author: Ty Stratton
Date last updated: 7/16/2025
Purpose: Time Program Module 6 Assignment 2, learning Graphs*/

#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "unorderedLinkedList.h"
#include "linkedQueue.h"

class graphType
{
public:
    bool isEmpty() const;
    void createGraph(std::string);
    void clearGraph();
    std::string printGraph() const;
    graphType(int size = 0);
    ~graphType();
    std::string depthFirstTraversal();
    std::string dftAtVertex(int vertex);
    std::string breadthFirstTraversal();
    std::string findPath(const std::string &startIP, const std::string &endIP);

protected:
    int maxSize;
    int gSize;
    unorderedLinkedList<int> *graph;
    std::vector<std::string> ipAddresses;

private:
    void dft(int v, bool visited[], std::string &output);
    int getIPIndex(const std::string &ip) const;
    bool dfsPath(int start, int end, std::vector<bool> &visited, std::vector<int> &path);
};

#endif