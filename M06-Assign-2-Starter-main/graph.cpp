/* Program name: graph.cpp
Author: Ty Stratton
Date last updated: 7/16/2025
Purpose: Time Program Module 6 Assignment 2, learning Graphs*/

#include "graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <regex>

bool graphType::isEmpty() const
{
    return gSize == 0;
}

void graphType::createGraph(std::string fileName)
{
    std::ifstream infile;
    char C;

    int vertex;
    int adjacentVertex;

    if (gSize != 0)
    {
        clearGraph();
    }

    infile.open(fileName);

    if (!infile)
    {
        throw std::runtime_error("Cannot open input file.");
    }

    // Clear existing IP addresses
    ipAddresses.clear();
    
    std::string line;
    std::regex ipRegex(R"(\b(?:\d{1,3}\.){3}\d{1,3}\b)");
    
    // Read all lines from file
    std::vector<std::string> lines;
    while (std::getline(infile, line))
    {
        if (!line.empty())
        {
            lines.push_back(line);
        }
    }
    
    // First pass: collect IP addresses
    for (const std::string& line : lines)
    {
        if (std::regex_match(line, ipRegex))
        {
            ipAddresses.push_back(line);
        }
    }
    
    gSize = ipAddresses.size();
    
    // Ensure graph array is large enough
    if (gSize > maxSize)
    {
        // Clear existing graph and reallocate
        delete[] graph;
        maxSize = gSize + 10; // Add some extra space
        graph = new unorderedLinkedList<int>[maxSize];
    }
    
    // Second pass: process adjacency list
    for (const std::string& line : lines)
    {
        if (!std::regex_match(line, ipRegex))
        {
            std::istringstream iss(line);
            int vertex;
            if (iss >> vertex)
            {
                // Add bounds checking for vertex
                if (vertex >= 0 && vertex < gSize && vertex < maxSize)
                {
                    int adj;
                    while (iss >> adj && adj != -999)
                    {
                        // Add bounds checking for adjacent vertex
                        if (adj >= 0 && adj < gSize)
                        {
                            graph[vertex].insert(adj);
                        }
                    }
                }
            }
        }
    }
    
    infile.close();
}

void graphType::clearGraph()
{
    for (int i = 0; i < gSize; i++)
    {
        graph[i].destroyList();
    }
    gSize = 0;
}

std::string graphType::printGraph() const
{
    std::ostringstream out;
    for (int i = 0; i < gSize; i++)
    {
        out << i << " ";
        out << graph[i].print();
        out << std::endl;
    }
    out << std::endl;
    return out.str();
}

graphType::graphType(int size)
{
    maxSize = size;
    gSize = 0;
    graph = new unorderedLinkedList<int>[size];
}

graphType::~graphType()
{
    clearGraph();
    delete[] graph;
}

std::string graphType::depthFirstTraversal()
{
    bool *visited;
    visited = new bool[gSize];
    std::string out = "";
    for (int i = 0; i < gSize; i++)
        visited[i] = false;
    for (int i = 0; i < gSize; i++)
    {
        if (!visited[i])
            dft(i, visited, out);
    }
    delete[] visited;
    return out;
}

std::string graphType::dftAtVertex(int vertex)
{
    bool *visited;
    visited = new bool[gSize];
    for (int i = 0; i < gSize; i++)
        visited[i] = false;
    std::string out = "";
    dft(vertex, visited, out);
    delete[] visited;
    return out;
}

std::string graphType::breadthFirstTraversal()
{
    linkedQueue<int> queue;
    bool *visited;
    visited = new bool[gSize];
    for (int i = 0; i < gSize; i++)
        visited[i] = false;
    std::string out = "";
    linkedListIterator<int> graphIt;
    for (int i = 0; i < gSize; i++)
    {
        if (!visited[i])
        {
            queue.enqueue(i);
            visited[i] = true;
            out = out + " " + std::to_string(i) + " ";
            while (!queue.isEmptyQueue())
            {
                int u = queue.dequeue();
                for (graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
                {
                    int w = *graphIt;
                    if (!visited[w])
                    {
                        queue.enqueue(w);
                        visited[w] = true;
                        out = out + " " + std::to_string(w) + " ";
                    }
                }
            }
        }
    }
    delete[] visited;
    return out;
}

void graphType::dft(int v, bool visited[], std::string &output)
{
    visited[v] = true;
    output = output + " " + std::to_string(v) + " ";
    linkedListIterator<int> graphIt;
    for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
    {
        int w = *graphIt;
        if (!visited[w])
            dft(w, visited, output);
    }
}

std::string graphType::findPath(const std::string &startIP, const std::string &endIP)
{
    int startIndex = getIPIndex(startIP);
    int endIndex = getIPIndex(endIP);

    if (startIndex == -1 || endIndex == -1)
    {
        return "Invalid IP address.";
    }

    std::vector<bool> visited(gSize, false);
    std::vector<int> path;
    
    if (dfsPath(startIndex, endIndex, visited, path))
    {
        std::stringstream ss;
        for (size_t i = 0; i < path.size(); ++i)
        {
            ss << ipAddresses[path[i]];
            if (i < path.size() - 1)
            {
                ss << " -> ";
            }
        }
        return ss.str();
    }

    return "No path was found from " + startIP + " to " + endIP;
}

int graphType::getIPIndex(const std::string &ip) const
{
    for (size_t i = 0; i < ipAddresses.size(); ++i)
    {
        if (ipAddresses[i] == ip)
        {
            return i;
        }
    }
    return -1;
}

bool graphType::dfsPath(int start, int end, std::vector<bool> &visited, std::vector<int> &path)
{
    // Add current node to path
    path.push_back(start);
    visited[start] = true;
    
    // If we reached the destination, return true
    if (start == end)
    {
        return true;
    }
    
    // Explore all adjacent nodes
    linkedListIterator<int> graphIt;
    for (graphIt = graph[start].begin(); graphIt != graph[start].end(); ++graphIt)
    {
        int adjacent = *graphIt;
        if (!visited[adjacent])
        {
            if (dfsPath(adjacent, end, visited, path))
            {
                return true;  // Path found through this adjacent node
            }
        }
    }
    
    // Backtrack: remove current node from path since no path was found through it
    path.pop_back();
    visited[start] = false;  // Allow revisiting this node from other paths
    
    return false;
}
